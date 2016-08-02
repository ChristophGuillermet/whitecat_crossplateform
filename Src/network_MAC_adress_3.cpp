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

* \file network_MAC_adress_3.cpp
* \brief {MAC Adress of all the network interfaces of the computer}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonction pour scanner et afficher les adresse Mac des différentes cartes réseaux de l'ordinateur
*
*   fonctions to scan and show the different mac adress on the computer
*
**/

int Box_IP_routing ( int macx, int macy)
{

    Rect Rescan(Vec2D(macx+130,macy-67),Vec2D(60,20));
    Rescan.SetRoundness(4);
    Rescan.Draw(CouleurFond.WithAlpha(0.4));
    Rescan.DrawOutline(CouleurLigne.WithAlpha(0.5));
    petitchiffre.Print("Rescan",macx+135,macy-55);

    if(window_focus_id==W_CFGMENU && mouse_x>macx+130 && mouse_x<macx+130+60 && mouse_y>macy-67 && mouse_y<macy-47)
    {
     Rescan.DrawOutline(CouleurLigne);
     if(mouse_button==1 && mouse_released==0)
     {
     //adresse locale et nom de machine
     gethostname(hostnamebuffer, sizeof(hostnamebuffer));
     phe = gethostbyname(hostnamebuffer);

     int Ipsearch = 0;
     while((phe->h_addr_list[Ipsearch+1])!=NULL)
     {
      Ipsearch++;
     }
     detection_reseaux();
     mouse_released=1;
     }
    }

    Rect IPAdapt(Vec2D(macx-10,macy-40),Vec2D(200,200));
    IPAdapt.SetRoundness(7.5);
    IPAdapt.Draw(CouleurFond.WithAlpha(0.2));


   petitchiffre.Print("IP ROUTING",macx,macy-30);
    petitchiffre.Print("Art-Net",macx+100,macy-30);
    petitchiffre.Print("in",macx+100,macy-15);
    petitchiffre.Print("out",macx+125,macy-15);

    petitchiffre.Print("iCat",macx+155,macy-25);

   Rect ArtnetBIn(Vec2D(macx+200,macy-25),Vec2D(10,10));
   Rect ArtnetBOut(Vec2D(macx+200,macy-25),Vec2D(10,10));
   Rect FS(Vec2D(macx+200,macy-25),Vec2D(10,10));

    for (int u=0;u<8;u++)
    {
    Rect NetworkSelect(Vec2D(macx,macy-15+(u*20)),Vec2D(90,20));
    NetworkSelect.SetRoundness(7.5);

    ArtnetBIn.MoveTo(Vec2D(macx+100,macy+(u*20)-10));
    ArtnetBIn.DrawOutline(CouleurLigne.WithAlpha(0.3));


    ArtnetBOut.MoveTo(Vec2D(macx+130,macy+(u*20)-10));
    ArtnetBOut.DrawOutline(CouleurLigne.WithAlpha(0.3));

    FS.MoveTo(Vec2D(macx+165,macy+(u*20)-10));
    FS.DrawOutline(CouleurLigne.WithAlpha(0.3));

     if(strcmp(IP_artnet_IN,IP_detected_dmxOUT[u])==0)
    {
     ArtnetBIn.Draw(CouleurFader);
    }

    if(strcmp(IP_artnet_OUT,IP_detected_dmxOUT[u])==0)
    {
     ArtnetBOut.Draw(CouleurGreen);
    }

    if(strcmp(IP_fantastick,IP_detected_dmxOUT[u])==0)
    {
     FS.Draw(CouleurBlind);
    }
    if(mouse_y>  macy-10+(u*20)&& mouse_y<macy+(u*20)  && window_focus_id==W_CFGMENU)
    {

    if(mouse_x>macx+100 && mouse_x<macx+110 )
    {
    if(mouse_button==1 && mouse_released==0 && strcmp(IP_detected_dmxOUT[u],"-")==1)
    {
    sprintf(IP_artnet_IN,IP_detected_dmxOUT[u]);
    index_re_init_serveur_artnet=1;
    mouse_released=1;
    }
    }


    else if(mouse_x>macx+130 && mouse_x<macx+140 )
    {
    if(mouse_button==1 && mouse_released==0 && strcmp(IP_detected_dmxOUT[u],"-")==1)
    {
    sprintf(IP_artnet_OUT,IP_detected_dmxOUT[u]);
    index_re_init_client_artnet=1;
    index_ask_confirm=1;
    mouse_released=1;
    }
    }

    else if(mouse_x>macx+165 && mouse_x<macx+175 )
    {
    if(mouse_button==1 && mouse_released==0 && strcmp(IP_detected_dmxOUT[u],"-")==1)
    {
    sprintf(IP_fantastick,IP_detected_dmxOUT[u]);
    index_ask_reinit_FS_client=1;
    index_ask_confirm=1;
    mouse_released=1;
    }
    }

    }




   petitchiffre.Print(IP_detected_dmxOUT[u],macx,macy+(20*u));
   }

return(0);
}



//////////////////ARTNET NETWORK IN///////////////////////////////////////////////

int do_artnet_affect_config(int cfgnetw_X, int cfgnetw_Y)
{


petitchiffre.Print("ArtNet IN is :",(cfgnetw_X), (cfgnetw_Y));

Rect AllowIn(Vec2D((cfgnetw_X+140), cfgnetw_Y-13),Vec2D(50,20));
AllowIn.SetRoundness(7.5);
AllowIn.Draw(CouleurFond.WithAlpha(0.5));

switch(allow_artnet_in)
{
case 0:
petitchiffre.Print("/Off",(cfgnetw_X+150), (cfgnetw_Y));
break;
case 1:
AllowIn.Draw(CouleurFader);
petitchiffre.Print("/On",(cfgnetw_X+155), (cfgnetw_Y));
break;
default: break;
}

if(mouse_x>cfgnetw_X+140 && mouse_x<cfgnetw_X+190 && mouse_y> cfgnetw_Y-13 && mouse_y< cfgnetw_Y+7  && window_focus_id==W_CFGMENU )
{
AllowIn.DrawOutline(CouleurNiveau);
if(mouse_button==1 && mouse_released==0)
{
allow_artnet_in=toggle(allow_artnet_in);
switch(allow_artnet_in)
{
case 0:
     fermeture_serveur_artnet();
break;
case 1:
     initialisation_serveur_artnet();
break;
default: break;
}
mouse_released=1;
}
}



///////////////////////////////////////////////////////////////////////////////
Rect AffectToDockN(Vec2D(cfgnetw_X, cfgnetw_Y+17),Vec2D(100,15));
AffectToDockN.SetRoundness(4);
AffectToDockN.Draw(CouleurBlind.WithAlpha(alpha_blinker*index_do_affect_net_to_dock));
AffectToDockN.DrawOutline(CouleurLigne.WithAlpha(0.7));

petitchiffre.Print("Affect to dock",(cfgnetw_X+5), (cfgnetw_Y+27));

if(window_focus_id==W_CFGMENU && mouse_x>cfgnetw_X && mouse_x<cfgnetw_X+100 && mouse_y>cfgnetw_Y+17 && mouse_y<cfgnetw_Y+17+15 && mouse_button==1 && mouse_released==0)
{
index_do_affect_net_to_dock=toggle(index_do_affect_net_to_dock);
index_do_dock=index_do_affect_net_to_dock;
mouse_released=1;
}

Rect AffectD(Vec2D(cfgnetw_X+140, cfgnetw_Y+12),Vec2D(50,25));
AffectD.SetRoundness(7.5);
AffectD.Draw(CouleurFond.WithAlpha(0.5));

petitchiffre.Print(ol::ToString(select_artnet_to_listen),cfgnetw_X+160, cfgnetw_Y+27);

if(window_focus_id==W_CFGMENU && mouse_x>cfgnetw_X+140 && mouse_x<cfgnetw_X+190 && mouse_y>cfgnetw_Y+25 && mouse_y<cfgnetw_Y+47 )
{
AffectD.DrawOutline(CouleurLigne.WithAlpha(0.6));
if(mouse_button==1 && mouse_released==0   )
{
int nu=atoi(numeric);
reset_numeric_entry();
numeric_postext=0;
if(nu>=0 && nu<=15)
{
select_artnet_to_listen=nu;
}
else{sprintf(string_Last_Order,"Universe must be from 0 to 15");}
}
mouse_released=1;
}


return(0);
}

