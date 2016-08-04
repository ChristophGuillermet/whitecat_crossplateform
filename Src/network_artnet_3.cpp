/*-------------------------------------------------------------------------------------------------------------
                                 |
          CWWWWWWWW              | Copyright (C) 2009-2013  Christoph Guillermet
       WWWWWWWWWWWWWWW           |
     WWWWWWWWWWWWWWWWWWW         | This file is part of White Cat.
    WWWWWWWWWWWWWWWWWCWWWW       |
   WWWWWWWWWWWWWWWWW tWWWWW      | White Cat is free software: you can redistribute it and/or modify
  WWWW   WWWWWWWWWW  tWWWWWW     | it under the terms of the GNU General Public License as published by
 WWWWWt              tWWWWWWa    | the Free Software Foundation, either version 2 of the License, or
 WWWWWW               WWWWWWW    | (at your option) any later version.
WWWWWWWW              WWWWWWW    |
WWWWWWWW               WWWWWWW   | White Cat is distributed in the hope that it will be useful,
WWWWWWW               WWWWWWWW   | but WITHOUT ANY WARRANTY; without even the implied warranty of
WWWWWWW      CWWW    W WWWWWWW   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
WWWWWWW            aW  WWWWWWW   | GNU General Public License for more details.
WWWWWWWW           C  WWWWWWWW   |
 WWWWWWWW            CWWWWWWW    | You should have received a copy of the GNU General Public License
 WWWWWWWWW          WWWWWWWWW    | along with White Cat.  If not, see <http://www.gnu.org/licenses/>.
  WWWWWWWWWWC    CWWWWWWWWWW     |
   WWWWWWWWWWWWWWWWWWWWWWWW      |
    WWWWWWWWWWWWWWWWWWWWWW       |
      WWWWWWWWWWWWWWWWWWa        |
        WWWWWWWWWWWWWWW          |
           WWWWWWWWt             |
                                 |
---------------------------------------------------------------------------------------------------------------*/

/**

* \file network_artnet_3.cpp
* \brief {artnet fonctions to send dmx via UDP protocool}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonction artnet pour envoyer le dmx sur le réseaux en UDP
*
*   Artnet fonctions to send dmx on the network via UDP protocool
*
**/

#include<winsock2.h>
//#pragma comment(lib,"ws2_32.lib")

// convert from shorts to bytes and back again
#define short_get_high_byte(x) ((HIGH_BYTE & x) >> 8)
#define short_get_low_byte(x)  (LOW_BYTE & x)

#define bytes_to_short(h,l) ( ((h << 8) & 0xff00) | (l & 0x00FF) );



char ArtDmxBuffer[530];
short OemUser = 0x00ff ; //developpment code only
short ProtocolVersion= 14;
short OpPoll= 0x2000;//Poll
short OpPollReply= 0x2100;//ArtPollReply
short OpPollFpReply= 0x2200;//Reply from four play
short OpOutput= 0x5000 ;//output
short OpAdress= 0x6000;//programm node settings
short OpInput=0x7000 ;//setup dmx input enables

short StyleNode = 0; // Responder is a Node (DMX <-> Ethernet Device)
short StyleServer  = 1 ;// Lighting console or similar



const char ArtNetHead[8] = {65, 114, 116, 45, 78, 101, 116, 0};

unsigned char OpHbyteReceive=0;
unsigned char OpLbyteReceive=0;
unsigned char UniversHbyte[17];
unsigned char UniversLbyte[17];
unsigned char OpPollRHbyte=0;
unsigned char OpPollRLbyte=0;
unsigned char OpPollHbyte=0;
unsigned char OpPollLbyte=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//afficheur artnet IN

int diodes_artnet(int x_diods, int y_diods)
{
petitchiffre.Print("Art-Net:" ,x_diods, y_diods);
for(int dd=0;dd<16;dd++)
{
Circle myartnet_diode_vide( x_diods+10+(dd*20), y_diods+10, 5.0, 5.0 );
myartnet_diode_vide.DrawOutline(CouleurLigne.WithAlpha(0.2));
}
return(0);
}

int light_temoin_universe(int incoming_artnet, int x_diods, int y_diods)
{
Circle myartnet_temoin(x_diods+10+(incoming_artnet*20), y_diods+10, 5.0, 5.0 );
myartnet_temoin.Draw( CouleurFader.WithAlpha(alpha_blinker) );
return(0);
}

int light_temoin_emission(int outgoing_artnet, int x_diods, int y_diods)
{
Circle myartnet_temoin(x_diods+10+(outgoing_artnet*20), y_diods+10, 5.0, 5.0 );
myartnet_temoin.Draw( CouleurGreen.WithAlpha(alpha_blinker) );
return(0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//box artpollreply received
int reset_poll_list()
{
for(int rt=0;rt<16;rt++)//etait 17 aout 2016
{strcpy(PollReplyIs[rt],"");}
count_artopoll_received=0;
return(0);
}


int show_artpoll_reply(int apr_X, int apr_Y)
{

Rect ArtPollReplyPanel(Vec2D(apr_X,  apr_Y), Vec2D( 500,250));
ArtPollReplyPanel.SetRoundness(15);
ArtPollReplyPanel.Draw(CouleurFond.WithAlpha(0.9));
ArtPollReplyPanel.DrawOutline(CouleurLigne);
petitchiffre.Print( "ARTPOLLREPLY from ( up to 16 devices ):",(apr_X+10), (apr_Y+20));

for(int co=0;co<16;co++)//etait 17 aout 2016
{
petitchiffre.Print( PollReplyIs[co],(apr_X+10), (apr_Y+40+(10*co)));
}

return(0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int init_artnet_variables()
{

 OpHbyteReceive=(unsigned  char) (OpOutput>>8);
 OpLbyteReceive= (unsigned char) (OpOutput);
 OpPollRHbyte=(unsigned  char) (OpPollReply>>8);
 OpPollRLbyte= (unsigned char) (OpPollReply);
 OpPollHbyte=(unsigned  char) (OpPoll>>8);
 OpPollLbyte=OpPoll;
 return(0);
}


 int  DoArtPollReply()
{
   nbrbytessended=sendto(sockartnet, ArtPollReplyBuffer,sizeof( ArtPollReplyBuffer),0,(SOCKADDR*)&sinS,sinsize);
   sprintf(string_Last_Order,">>Polled !");

   return(0);
}


int ReceiveArtDmx()
{
 if( artnet_message[0]==ArtNetHead[0] && artnet_message[1]==ArtNetHead[1] && artnet_message[2]==ArtNetHead[2] && artnet_message[3]==ArtNetHead[3]
 && artnet_message[4]==ArtNetHead[4]  && artnet_message[5]==ArtNetHead[5]  && artnet_message[6]==ArtNetHead[6]  && artnet_message[7]==ArtNetHead[7] )
 {is_artnet=1;}

 if( OpLbyteReceive==artnet_message[8] && OpHbyteReceive==artnet_message[9]  )
  {
   is_opcode_is_dmx=1;
   //pour recup si besoin
   is_artnet_version_i1=artnet_message[10]; is_artnet_version_i2=artnet_message[11];
   seq_artnet=artnet_message[12];//0
   artnet_physical=artnet_message[13];//0
   }
 else if( artnet_message[8]==OpPollLbyte && artnet_message[9]==OpPollHbyte  )
  {
   is_opcode_is_polling=1;
  }

 if(is_artnet==1 && is_opcode_is_dmx==1 )
 {
 incoming_universe= bytes_to_short(artnet_message[15],artnet_message[14]);//extraction de l'univers
 index_do_light_diode_artnet=1;

 for (int    p=0;p<512;p++)
 {ArtNet_16xUniverse_Receiving[p+1][incoming_universe]=artnet_message[p+HeaderLength+1];}
  //reinit
 is_artnet=0;is_opcode_is_dmx=0; is_artnet_version_i1=0; is_artnet_version_i2=0;
 incoming_universe=999;//reinit hors écran

 }

 else if (is_artnet==1 && is_opcode_is_polling==1 )
 {
  DoArtPollReply();
  is_opcode_is_polling=0;is_artnet=0;
 }

 return(0);
}





/////////////////CONFIG/////////////////////////////////////////////////////////
int load_artnet_conf()
{
    //variables chargement config
FILE *cfg_file = NULL ;
char read_buff[ 512 ] ;


    //sab 0/03/2014 unused int it=0;
	cfg_file = fopen("user\\config_artnet.txt", "rt" );
	if( !cfg_file )
	{
	 printf("\nPb à ouverture de config_artnet.txt\n");
     return 1;
	}
//premiere ligne les args
	if( !fgets( read_buff , sizeof( read_buff ) , cfg_file ) )
	{
     printf("\nErreur lors de la lecture de la première ligne de commentaires\n");
     return 1;
	}


fscanf( cfg_file , "%d %d /\n" ,  &index_broadcast , &Univers  );
/* on saute la ligne de commentaire */
fgets( read_buff , sizeof( read_buff ) , cfg_file );
//deuxieme ligne des args
fscanf( cfg_file  , "%s\n" , ip_artnet );

fclose( cfg_file );
return(0);
}


int save_artnet_conf()
{
FILE *fp;
char rep_conf_dmx[1024];
sprintf(rep_conf_dmx,"%s\\user\\config_artnet.txt",mondirectory);
if((fp=fopen(rep_conf_dmx,"w")))
{
fprintf(fp,"#arguments: broadcast (1) ou unicast (0) // puis Univers Dmx surlequel envoyer ( 0 à 15)");
fprintf(fp,"\n%d %d",index_broadcast,Univers);
fprintf(fp,"\n#arguments: si en broadcast: l'adresse doit etre de type X.X.X. / si en unicast X.X.X.X");
fprintf(fp,"\n%s",ip_artnet);
}
fclose(fp);
return(0);
}
//////////////////CLIENT////////////////////////////////////////////////////////

int detection_reseaux()
{
//ip artnet
for(int u=0;u<8;u++)
{
sprintf(IP_detected_dmxOUT[u],"-");
}

struct in_addr **addr_list;
addr_list = (struct in_addr **)phe->h_addr_list;


for(int p=0;addr_list[p]!=NULL;p++)
{
sprintf(IP_detected_dmxOUT[p] ,inet_ntoa(*addr_list[p]));
}

//sprintf(IP_detected_dmxOUT[7],"..1.");

return(0);
}

int initialisation_serveur_artnet()
{
    WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);

	sinServ.sin_family=AF_INET;
    sinServ.sin_addr.s_addr=inet_addr(IP_artnet_IN);
    sinServ.sin_port=htons(serveurport_artnet);
	sock=socket(AF_INET,SOCK_DGRAM,0);
	bind(sock,(SOCKADDR*)&sinServ,sizeof(sinServ));
	u_long imode = 1;
	ioctlsocket(sock, FIONBIO, &imode);
	 sinsizeServ=sizeof(sinServ);
	 sprintf(string_Last_Order,"Art-Net Server initialized");
	 memset(artnet_message,0,sizeof(artnet_message));
	 gethostname(hostnamebuffer, sizeof(hostnamebuffer));
	 phe = gethostbyname(hostnamebuffer);
	  int Ipsearch = 0;
     while((phe->h_addr_list[Ipsearch+1])!=NULL)
     {
     Ipsearch++;
      }
     detection_reseaux();

memcpy(&sinServ.sin_addr.s_addr, phe->h_addr_list[network_OUT_is_selected], phe->h_length);

artnet_serveur_is_initialized=1;
return(0);
}

int fermeture_serveur_artnet()
{
 	shutdown(sock,2);
    closesocket(sock);
    sprintf(string_Last_Order,">>Closed Art-Net serveur");
    artnet_serveur_is_initialized=0;
 return(0);
}

//bug remonté par jacques
int detection_mise_en_place_carte_reseaux()
{
WSADATA wsa;
WSAStartup(MAKEWORD(2,0),&wsa);
//adresse locale et nom de machine
 gethostname(hostnamebuffer, sizeof(hostnamebuffer));
 phe = gethostbyname(hostnamebuffer);

 int Ipsearch = 0;
 while((phe->h_addr_list[Ipsearch+1])!=NULL)
 {
 Ipsearch++;
 }
 detection_reseaux();
return(0);
}



int initialisation_client_artnet()
{
detection_mise_en_place_carte_reseaux();
/*
WSADATA wsa;
WSAStartup(MAKEWORD(2,0),&wsa);

//adresse locale et nom de machine
 gethostname(hostnamebuffer, sizeof(hostnamebuffer));
 phe = gethostbyname(hostnamebuffer);

 int Ipsearch = 0;
 while((phe->h_addr_list[Ipsearch+1])!=NULL)
 {
 Ipsearch++;
 }
 detection_reseaux();
*/
/*
memcpy(&sinS.sin_addr.s_addr, phe->h_addr_list[network_OUT_is_selected], phe->h_length);

 sprintf(string_ip,inet_ntoa(sinS.sin_addr));

 //extraction en tableau de 4 char

 sscanf (string_ip, "%d.%d.%d.%d", my_ip_is, my_ip_is + 1,
                       my_ip_is + 2, my_ip_is + 3);

//               printf ("\nI am: %d.%d.%d.%d\n", (unsigned char)my_ip_is[0], (unsigned char)my_ip_is[1],
//                      (unsigned char)my_ip_is[2],(unsigned char)my_ip_is[3]);

*/

//On informe la structure
sinS.sin_family=AF_INET;
sinS.sin_addr.s_addr=inet_addr(ip_artnet);
sinS.sin_port=htons( clientport_artnet);
//préparation de l'envoi

sockartnet=socket(AF_INET,SOCK_DGRAM,0); //On initialise le socket avec SOCK_DGRAM pour dire qu'on est en UDP

if(index_broadcast==1)//init broadcast mode, sinon est en unicast
{
 if (setsockopt(sockartnet, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof broadcast) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }
}

bind(sockartnet,(SOCKADDR*)&sinS,sizeof(sinS)); //Liaison entre la structure et la socket


 //non-blocking mode setting avec ioctlsocket
u_long imode = 1;
ioctlsocket( sockartnet, FIONBIO, &imode);

sinsize=sizeof(sinS);


sprintf(string_Last_Order,">>Init Art-net OK:  %s /port: %d", ip_artnet,clientport_artnet);

if (index_broadcast==1)
	{
	sprintf(string_display_dmx_params,"ART-NET: Broadcast to network %s Univ. %d",ip_artnet, Univers);
    }
else if (index_broadcast==0)
	{
	sprintf(string_display_dmx_params,"ART-NET: Unicast to %s Univ. %d",ip_artnet, Univers);
    }
client_artnet_is_closed=0;
return(0);
}

int fermeture_client_artnet()
{
 	shutdown(sockartnet,2);
    closesocket(sockartnet);
    sprintf(string_Last_Order,">>Closed Art-Net Client");
    client_artnet_is_closed=1;
 return(0);
}





int ConstructArtPoll()
{
 for (int i=0;i<7;i++)
 {
 ArtPollBuffer[i]=ArtNetHead[i];
 }
 //opérateur
  //Opcode low byte first
  unsigned char OpPollHbyteSend=(unsigned  char) (OpPoll>>8);
  unsigned char OpPollLbyteSend= (unsigned char) (OpPoll);
  ArtPollBuffer[8]=OpPollLbyteSend;
  ArtPollBuffer[9]=OpPollHbyteSend;
 //protocole
  ArtPollBuffer[10]=0;
  ArtPollBuffer[11]=14;
  //talk to me
  //ArtPollBuffer[12]=0;
  ArtPollBuffer[12]=0x00000001;//ook
 // ArtPollBuffer[12]=0x00000011;
  // bit 0 = not used
  //   Prev def was bit 0 = 0 if reply is broadcast
  // 	            bit 0 = 1 if reply is to server IP
  // All replies are noe broadcast as this feature caused too many
  // tech support calls
  // bit 1 = 0 then Node only replies when polled
  // bit 1 = 1 then Node sends reply when it needs to

  //filler ending packet
  ArtPollBuffer[13]=0;
  return(0);
}

int ArtDmx()
{
    //preparation pour tests
    for (int i=0;i<7;i++)
    {
    ArtDmxBuffer[i]=ArtNetHead[i];
    }
    //Opcode low byte first
     unsigned char OpHbyteSend=(unsigned  char) (OpOutput>>8);
     unsigned char OpLbyteSend= (unsigned char) (OpOutput);
     ArtDmxBuffer[8]=OpLbyteSend;
     ArtDmxBuffer[9]=OpHbyteSend;
     //protocole
     ArtDmxBuffer[10]=0;
     ArtDmxBuffer[11]=14;
     //pas de sequence
     ArtDmxBuffer[12]=0;
     //physical
     ArtDmxBuffer[13] = 0;
     // universe (two bytes)
     unsigned char UHbyte=(unsigned  char) (Univers>>8);
     unsigned char ULbyte= (unsigned char) (Univers);
     ArtDmxBuffer[14]=ULbyte;//ou 0
     ArtDmxBuffer[15]=UHbyte;
     //data length
     unsigned char DHbyte=(unsigned  char) (DataLength>>8);
     unsigned char DLbyte= (unsigned char) (DataLength);
     ArtDmxBuffer[16] = DHbyte;
     ArtDmxBuffer[17] = DLbyte;

     for (int t=HeaderLength+1;t<Dim;t++)
     {
     ArtDmxBuffer[t]=DmxBlock[t-HeaderLength];
     }

    return(0);
}


int ConstructArtPollReply ()//size 250
{

 for (int i=0;i<7;i++)
 {
 ArtPollReplyBuffer[i]=ArtNetHead[i];
 }
 //opérateur
  unsigned char OpPollRHbyte=(unsigned  char) (OpPollReply>>8);
  unsigned char OpPollRLbyte= (unsigned char) (OpPollReply);
 ArtPollReplyBuffer[8]=OpPollRLbyte;
 ArtPollReplyBuffer[9]=OpPollRHbyte;
 //adresse ethernet de cette machine
 ArtPollReplyBuffer[10]=(unsigned char)my_ip_is[0];
 ArtPollReplyBuffer[11]=(unsigned char)my_ip_is[1];
 ArtPollReplyBuffer[12]=(unsigned char)my_ip_is[2];
 ArtPollReplyBuffer[13]=(unsigned char)my_ip_is[3];
 //2 bytes pour le port artnet
 ArtPollReplyBuffer[14]= (unsigned char)(clientport_artnet);
 ArtPollReplyBuffer[15]= (unsigned char)(clientport_artnet>>8);

//version
ArtPollReplyBuffer[16]=0;
ArtPollReplyBuffer[17]=14;
//subswitch
ArtPollReplyBuffer[18]=0;
ArtPollReplyBuffer[19]=0; //Sub NET (0-15)
//oem firmware
ArtPollReplyBuffer[20]=(unsigned char)(OemUser>>8);
ArtPollReplyBuffer[21]=(unsigned char)(OemUser);

//ubea version firmware
ArtPollReplyBuffer[22]=0;//none
//status
// bit 0 = 0 UBEA not present
// bit 0 = 1 UBEA present
// bit 1 = 0 Not capable of RDM (Uni-directional DMX)
// bit 1 = 1 Capable of RDM (Bi-directional DMX)
// bit 2 = 0 Booted from flash (normal boot)
// bit 2 = 1 Booted from ROM (possible error condition)
// bit 3 = Not used
// bit 54 = 00 Universe programming authority unknown
// bit 54 = 01 Universe programming authority set by front panel controls
// bit 54 = 10 Universe programming authority set by network
// bit 76 = 00 Indicators Normal
// bit 76 = 01 Indicators Locate
// bit 76 = 10 Indicators Mute

ArtPollReplyBuffer[23]=0;
//Reserved for ESTA manufacturer id lo, zero for now

ArtPollReplyBuffer[24]=0;
ArtPollReplyBuffer[25]=0;
//les noms du artnode
for (int i=26;i<(26+ShortNameLength-1);i++)// le petit nom fait 18
{
 ArtPollReplyBuffer[i]= ArtShortName[(i-26)]  ;
}
for (int it=44;it<(44+LongNameLength-1);it++)// le petit nom fait 64
{
 ArtPollReplyBuffer[it]= ArtLongName[(it-44)]  ;
}
for (int it=108;it<(108+NodeReportLength-1);it++)// le node report fait 64
{
 ArtPollReplyBuffer[it]= ArtNodeReport[(it-108)]  ;
}
//nombre de ports supportés
ArtPollReplyBuffer[172]=0; //hi
ArtPollReplyBuffer[173]=4; //low If num i/p ports is dif to output ports, return biggest
//PortTypes ( 1 to MaxNumports) as bytes
// bit 7 is output
// bit 6 is input
// bits 0-5 are protocol number (0= DMX, 1=MIDI)
// for DMX-Hub ={0xc0,0xc0,0xc0,0xc0};
ArtPollReplyBuffer[174]=0;//port 1 type
ArtPollReplyBuffer[175]=0;//port 2 type
ArtPollReplyBuffer[176]=0;//port 3 type
ArtPollReplyBuffer[177]=0;//port 4 type
//Good Input ( 1 to maxnumports)
// bit 7 is data received
// bit 6 is data includes test packets
// bit 5 is data includes SIP's
// bit 4 is data includes text
// bit 3 set is input is disabled
// bit 2 is receive errors
// bit 1-0 not used, transmitted as zero.
// Don't test for zero!
ArtPollReplyBuffer[178]=0;//port 1 type
ArtPollReplyBuffer[179]=0;//port 2 type
ArtPollReplyBuffer[180]=0;//port 3 type
ArtPollReplyBuffer[181]=0;//port 4 type
//Good Outpit ( 1 to nummaxports)
// bit 7 is data is transmitting
// bit 6 is data includes test packets
// bit 5 is data includes SIP's
// bit 4 is data includes text
// bit 3 output is merging data.
// bit 2 set if DMX output short detected on power up
// bit 1 set if DMX output merge mode is LTP
// bit 0 not used, transmitted as zero.
ArtPollReplyBuffer[182]=0;//port 1 type
ArtPollReplyBuffer[183]=0;//port 2 type
ArtPollReplyBuffer[184]=0;//port 3 type
ArtPollReplyBuffer[185]=0;//port 4 type
//Swin ( 1 to nummaxport)
// Low nibble is the port input
// address wheel for this port. On
// DMX-Hub, this is the front panel
//  rotary switch.
// Hi Nibble is the Sub-net
// This byte shows to which of 256 universes, the
// data belongs
ArtPollReplyBuffer[186]=0;//port 1 type
ArtPollReplyBuffer[187]=0;//port 2 type
ArtPollReplyBuffer[188]=0;//port 3 type
ArtPollReplyBuffer[189]=0;//port 4 type
//Swout ( 1 to num max port)
// Low nibble is the port output
// address wheel for this port. On
// DMX-Hub, this is the front panel
//  rotary switch.
// Hi Nibble is the Sub-net
// This byte shows to which of 256 universes, the
// data belongs
ArtPollReplyBuffer[190]=0;//port 1 type
ArtPollReplyBuffer[191]=0;//port 2 type
ArtPollReplyBuffer[192]=0;//port 3 type
ArtPollReplyBuffer[193]=0;//port 4 type
//SW Video
// Low nibble is the value of the video
// output channel
ArtPollReplyBuffer[194]=0;
//SwMacro
// Bit 0 is Macro input 1
// Bit 7 is Macro input 8
// Only implemented if OEM bit 15 set.
// Netgate XT contains this implementation
// Any change in state of a bit will
//  cause a transmission.
// Server should not assume that only
//  one bit has changed.
// The Node is responsible for debounce
ArtPollReplyBuffer[195]=0;
//SwRemote
// Bit 0 is Remote input 1
// Bit 7 is Remote input 8
// Only implemented if OEM bit 15 set.
// Netgate XT contains this implementation
// Any change in state of a bit will
//  cause a transmission.
// Server should not assume that only
//  one bit has changed.
// The Node is responsible for debounce
ArtPollReplyBuffer[196]=0;
//spare bytes nothing inside
ArtPollReplyBuffer[197]=0;
ArtPollReplyBuffer[198]=0;
ArtPollReplyBuffer[199]=0;

//STYLE
ArtPollReplyBuffer[200]=StyleServer;
//MAC ADRESS, 0 IF UNAVAIBLE
ArtPollReplyBuffer[201]=0;
ArtPollReplyBuffer[202]=0;
ArtPollReplyBuffer[203]=0;
ArtPollReplyBuffer[204]=0;
ArtPollReplyBuffer[205]=0;
ArtPollReplyBuffer[206]=0;

for (int fill=207;fill<(207+32);fill++)
{ArtPollReplyBuffer[fill]=0;}
//END OF SIGNAL
ArtPollReplyBuffer[239]=255;

return(0);
}
//////////////////////////////////////////////////////////////////////////

int  AnalyseArtPollReply()
{
index_show_artpoll_reply_content=1;
bool index_is_artnet=0;
bool index_is_artpollRep=0;


if( artpollreply_message[0]==ArtNetHead[0] && artpollreply_message[1]==ArtNetHead[1] && artpollreply_message[2]==ArtNetHead[2] && artpollreply_message[3]==ArtNetHead[3]
 && artpollreply_message[4]==ArtNetHead[4]  && artpollreply_message[5]==ArtNetHead[5]  && artpollreply_message[6]==ArtNetHead[6]  && artpollreply_message[7]==ArtNetHead[7] )
 {index_is_artnet=1;}



if(artpollreply_message[8]==OpPollRLbyte && artpollreply_message[9]==OpPollRHbyte)//L 8 H 9
{index_is_artpollRep=1;}


if(index_is_artnet==1 && index_is_artpollRep==1)
{
sprintf(string_Last_Order,">>Received ArtPollReply %d",count_artopoll_received);
count_artopoll_received++;
//sprintf(paste_reply[count_artopoll_received], artpollreply_message);

sprintf(nodefirmware_versinfo,"v.  %d . %d",(unsigned char) artpollreply_message[16],(unsigned char) artpollreply_message[17]);

sprintf(subnetis,"SubNet %d",(unsigned char) artpollreply_message[19]);


for (int ish=0;ish<18;ish++)
{shortname_device[ish]=artpollreply_message[26+ish];}


sprintf(PollReplyIs[count_artopoll_received],"-/IP %d  . %d . %d . %d  / %s / %s / %s",(unsigned char)artpollreply_message[10],(unsigned char)artpollreply_message[11],
(unsigned char)artpollreply_message[12],(unsigned char)artpollreply_message[13],shortname_device,subnetis,nodefirmware_versinfo);


}

return(0);
}
///////////////////////////////////////////////////////////////////////

