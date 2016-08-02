
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

* \file iCat14.cpp
* \brief {GUI fonctions for iCAT}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour déssiner la fenêtre iCat qui permet de controller whitecat sur un iphone via le logiciel ifantastic
*
*   GUI fonctions for icat a iphone control and gui send via the iFantastic software
*
 **/



//GUI BUILDER

char icat_font_name[25];
int test_font_id=0;


int iCat_slider_doing_X1_is=0;
int iCat_slider_doing_X2_is=0;

int init_iphone_fonts()
{
    sprintf( iphone_fonts[0],"AppleGothic");
    sprintf( iphone_fonts[1],"HiraKakuProN-W6");
    sprintf( iphone_fonts[2],"HiraKakuProN-W3");
    sprintf( iphone_fonts[3],"STHeitiTC-Medium");
    sprintf( iphone_fonts[4],"STHeitiTC-Light");
    sprintf( iphone_fonts[5],"HelveticaNeue-Bold");
    sprintf( iphone_fonts[6],"HelveticaNeue-Bold");


 return(0);
}

int init_iCat_data()
{

for(int i=0;i<48;i++)
{ before_check_button_state[i]=0;check_button_state[i]=0;}
for(int tp=0;tp<fs_max_points;tp++)
{
FS_touch_point_begin[0][tp]=-999;
FS_touch_point_begin[1][tp]=-999;
FS_touch_point_move[0][tp]=-999;
FS_touch_point_move[1][tp]=-999;
FS_touch_point_end[0][tp]=-999;
FS_touch_point_end[1][tp]=-999;
}



 return(0);
}


int fermeture_client_iCat()
{

 	shutdown(sockiCat,2);
    closesocket(sockiCat);
    sprintf(string_Last_Order,">>Closed Fantastick Client");
    client_icat_is_closed=1;
 return(0);
}



int initialisation_clientserveur_iCat()
{
WSADATA wsa;
WSAStartup(MAKEWORD(2,0),&wsa);
sinServiCat.sin_family=AF_INET;
sinServiCat.sin_addr.s_addr= inet_addr(IP_fantastick);

sinServiCat.sin_port=htons(serveurport_iCat);
sockRiCat=socket(AF_INET,SOCK_DGRAM,0);
bind(sockRiCat,(SOCKADDR*)&sinServiCat,sizeof(sinServiCat));
u_long imode = 1;
ioctlsocket(sockRiCat, FIONBIO, &imode);
sinsizeServiCat=sizeof(sinServiCat);
sprintf(string_Last_Order,"Fantastick Server initialized");

memset(fantastick_message,0,sizeof(fantastick_message));
iCat_serveur_is_initialized=1;

	 gethostname(hostnamebuffer, sizeof(hostnamebuffer));
	 phe = gethostbyname(hostnamebuffer);
	  int Ipsearch = 0;
     while((phe->h_addr_list[Ipsearch+1])!=NULL)
     {
     Ipsearch++;
      }
     detection_reseaux();


 //client
siniCat.sin_family=AF_INET;
siniCat.sin_addr.s_addr=inet_addr(specified_fs_ip);
siniCat.sin_port=htons( clientport_iCat);
//préparation de l'envoi
sockiCat=socket(AF_INET,SOCK_DGRAM,0); //On initialise le socket avec SOCK_DGRAM pour dire qu'on est en UDP
bind(sockiCat,(SOCKADDR*)&siniCat,sizeof(siniCat)); //Liaison entre la structure et la socket


sinsizeiCat=sizeof(siniCat);
char test_chaine[32]={"opengl 1"};
nbrbytessendediCat=sendto(sockiCat,  test_chaine,sizeof(test_chaine),0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(test_chaine,"clearmodels");
nbrbytessendediCat=sendto(sockiCat,  test_chaine,sizeof(test_chaine),0,(SOCKADDR*)&siniCat,sinsizeiCat);

client_icat_is_closed=0; index_re_init_clientserveur_icat=0;
return(0);
}

int fermeture_clientserveur_iCat()
{
 	shutdown(sockRiCat,2);
    closesocket(sockRiCat);
    sprintf(string_Last_Order,">>Closed Fantastick server");
    iCat_serveur_is_initialized=0;

    if(client_icat_is_closed==0)
    {fermeture_client_iCat();}
 return(0);
}


int Menu_edition_iCat_sliders(int xed, int yed)
{
char title_iCat_menu[16];

///////////////SLIDER EDITING///////////////////////////////////////////////////
Rect Slider_M(Vec2D(xed-15,yed-10),Vec2D(105,20));
Slider_M.SetRoundness(4);
Slider_M.Draw(CouleurFond.WithAlpha(0.4));
if(editing_GUI_type_iCat==1)
{Slider_M.Draw(CouleurSurvol);}
petitchiffre.Print("Sliders",xed+10,yed+2);
if(mouse_x>xed-15 && mouse_x<xed+90 && mouse_y>yed-10 && mouse_y<yed+10
   && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
if(index_main_clear==1)//clear des sliders selectivement
{
index_ask_iCat_selectiv_clear=1;
index_ask_confirm=1;
}
else
{
if(editing_GUI_type_iCat==1) {editing_GUI_type_iCat=0;}
else editing_GUI_type_iCat=1;
}
mouse_released=1;
}


//NAVIGATION DANS LE SLIDER A EDITER
previous_button_view(xed-15,yed+15,0);
next_button_view(xed+50,yed+15,0);
Rect Slider_F(Vec2D(xed+10,yed+15),Vec2D(35,20));
Slider_F.SetRoundness(4);
Slider_F.Draw(CouleurFond.WithAlpha(0.4));
sprintf(title_iCat_menu,"%d /%d",iCat_select_editing_slider, iCat_nbre_de_sliders[iCatPageis]);
petitpetitchiffre.Print(title_iCat_menu,xed+12,yed+27);

if(mouse_y>yed+15 && mouse_y< yed+35)
{
if(mouse_x>xed-15 && mouse_x<xed+5 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=1;
previous_button_view(xed-15,yed+15,1);
if(iCat_select_editing_slider>0){iCat_select_editing_slider--;}
else{iCat_select_editing_slider=iCat_nbre_de_sliders[iCatPageis];}
mouse_released=1;
}
if(mouse_x>xed+50 && mouse_x<xed+70 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=1;
next_button_view(xed+50,yed+15,1);
if(iCat_select_editing_slider<iCat_nbre_de_sliders[iCatPageis]){iCat_select_editing_slider++;}
else{iCat_select_editing_slider=0;}
mouse_released=1;
}
}

//DEF MAX SLIDERS
case_moins_view(xed+75,yed+15,0);
case_plus_view(xed+75,yed+35,0);

if(mouse_x>xed+75 && mouse_x<xed+90)
{
if(mouse_y>yed+15 && mouse_y<yed+30 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT )
{
editing_GUI_type_iCat=1;
case_moins_view(xed+75,yed+15,1);
if(iCat_nbre_de_sliders[iCatPageis]>0)
{
iCat_nbre_de_sliders[iCatPageis]--;
if(iCat_select_editing_slider>iCat_nbre_de_sliders[iCatPageis]){iCat_select_editing_slider=iCat_nbre_de_sliders[iCatPageis];
}
}
mouse_released=1;
}
if(mouse_y>yed+35 && mouse_y<yed+50 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT )
{
editing_GUI_type_iCat=1;
case_plus_view(xed+75,yed+35,1);
if(iCat_nbre_de_sliders[iCatPageis]<max_sliders_icat){iCat_nbre_de_sliders[iCatPageis]++;}
iCat_select_editing_slider=iCat_nbre_de_sliders[iCatPageis];
mouse_released=1;
}
}


///SPECS SLIDER
char str_type_iCat[16];
sprintf(str_type_iCat,"X: %d Y: %d",iCat_pos_slider[iCatPageis][iCat_select_editing_slider][0],iCat_pos_slider[iCatPageis][iCat_select_editing_slider][1]);
petitpetitchiffre.Print(str_type_iCat,xed-10,yed+47);


//grossuer slider
switch(ratio_iCat_slider[iCatPageis][iCat_select_editing_slider])
{
case 1:
sprintf(str_type_iCat,"small");//abandonné
break;
case 2:
sprintf(str_type_iCat,"med.");
break;
case 3:
sprintf(str_type_iCat,"big");
break;
default:
sprintf(str_type_iCat,"-") ;
break;
}
pulse_bar_view(xed-12,yed+55, str_type_iCat);
if(mouse_x>xed-12 && mouse_x<xed+18 && mouse_y>yed+55 && mouse_y<yed+75 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT  && iCat_select_editing_slider!=0)
{
editing_GUI_type_iCat=1;
ratio_iCat_slider[iCatPageis][iCat_select_editing_slider]++;
if(ratio_iCat_slider[iCatPageis][iCat_select_editing_slider]>3){ratio_iCat_slider[iCatPageis][iCat_select_editing_slider]=1;}
mouse_released=1;
}



switch (iCat_orientation_slider[iCatPageis][iCat_select_editing_slider])
{
case 0:
sprintf(str_type_iCat,"     Vertical");
break;
case 1:
sprintf(str_type_iCat,"   Horizontal");
break;
default: break;
}
toggling_bar_view(xed+20,yed+55, 0,str_type_iCat);

if(mouse_x>xed+20 && mouse_x<xed+80 && mouse_y>yed+55 && mouse_y<yed+75 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT  && iCat_select_editing_slider!=0)
{
editing_GUI_type_iCat=1;
iCat_orientation_slider[iCatPageis][iCat_select_editing_slider]=toggle(iCat_orientation_slider[iCatPageis][iCat_select_editing_slider]);
mouse_released=1;
}



///AFFECTATIONS
char string_temp_familly[25];
petitpetitchiffre.Print("Type:",xed-15,yed+90);
Rect AffectTyp(Vec2D(xed-15,yed+95),Vec2D(100,20));
AffectTyp.SetRoundness(4);
AffectTyp.Draw(CouleurFond.WithAlpha(0.4));
switch(iCat_affectation_slider_type_is[iCatPageis][iCat_select_editing_slider])
{
case 1: //faders  lvl
sprintf(string_temp_familly,"Fader Level:");
break;
case 2://faders speeed
sprintf(string_temp_familly,"Fader Speed:");
break;
case 3://sequenciel
sprintf(string_temp_familly,"Sequences:");
break;
case 4://grand master
sprintf(string_temp_familly,"GrandMaster");
break;
case 5://level wheel
sprintf(string_temp_familly,"Level Wheel");
break;
case 6://mover
sprintf(string_temp_familly,"Mover:");
break;
case 7://draw
sprintf(string_temp_familly,"Draw Press.:");
break;
case 8://draw
sprintf(string_temp_familly,"Draw Decay:");
break;
case 9://draw
sprintf(string_temp_familly,"Draw Ghost:");
break;
case 10://draw
sprintf(string_temp_familly,"Draw Act.Press");
break;
case 11://draw
sprintf(string_temp_familly,"Draw Act.Decay");
break;
case 12://draw
sprintf(string_temp_familly,"Draw Act.Ghost");
break;

default:
sprintf(string_temp_familly,"-");
break;
}
petitpetitchiffre.Print(string_temp_familly,xed-7,yed+107);

//TYPE
if(mouse_x>xed-15 && mouse_x<xed+85 && mouse_y>yed+95 && mouse_y<yed+115 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT  && iCat_select_editing_slider!=0)
{
editing_GUI_type_iCat=1;
iCat_affectation_slider_type_is[iCatPageis][iCat_select_editing_slider]++;
if(iCat_affectation_slider_type_is[iCatPageis][iCat_select_editing_slider]>12){iCat_affectation_slider_type_is[iCatPageis][iCat_select_editing_slider]=0;}
mouse_released=1;
}

//VARIABLE A LA SOURIS

Rect AffectVar(Vec2D(xed+40,yed+120),Vec2D(45,20));
AffectVar.SetRoundness(5);
AffectVar.Draw(CouleurFond.WithAlpha(0.4));
petitpetitchiffre.Print(ol::ToString(iCat_affectation_slider_value_is[iCatPageis][iCat_select_editing_slider]),
                          xed+55,yed+132);

if(mouse_x>xed+40 && mouse_x<xed+85 && mouse_y>yed+120 && mouse_y<yed+140 &&  window_focus_id==W_iCAT )
{
AffectVar.DrawOutline(CouleurLigne);
if(  mouse_button==1 && mouse_released==0 && iCat_select_editing_slider!=0)
{
editing_GUI_type_iCat=1;
int temp_number=atoi(numeric);
reset_numeric_entry();
switch(iCat_affectation_slider_type_is[iCatPageis][iCat_select_editing_slider])
{
case 1: //faders  lvl
if(temp_number>48){temp_number=48;}
break;
case 2://faders speeed
if(temp_number>48){temp_number=48;}
break;
case 4://seq scene et preset et vitesse
if(temp_number>3){temp_number=3;}
break;
case 6:
if(temp_number>16){temp_number=16;}
break;
case 7://draw
if(temp_number>6){temp_number=6;}
break;
case 8://draw
if(temp_number>6){temp_number=6;}
break;
case 9://draw
if(temp_number>6){temp_number=6;}
break;
case 10://draw
if(temp_number>6){temp_number=6;}
break;
case 15://echo
//if(temp_number>6){temp_number=6;}
break;

default:
break;
}
iCat_affectation_slider_value_is[iCatPageis][iCat_select_editing_slider]=temp_number;
mouse_released=1;
}
}

//Sliders DUB
Rect DubB(Vec2D(xed-15,yed+150),Vec2D(30,15));

petitpetitchiffre.Print("Dub",xed-10,yed+160);

DubB.SetRoundness(4);
DubB.Draw(CouleurFond.WithAlpha(0.4));

if(mouse_x>xed-15 && mouse_x<xed+15 && mouse_y>yed+150 && mouse_y<yed+165
   && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=1;
if(iCat_nbre_de_sliders[iCatPageis]<max_sliders_icat)
{
 int iCatrefslider=iCat_select_editing_slider;
 iCat_nbre_de_sliders[iCatPageis]++;
 iCat_select_editing_slider=iCat_nbre_de_sliders[iCatPageis];
 iCat_orientation_slider[iCatPageis][iCat_select_editing_slider] = iCat_orientation_slider[iCatPageis][iCatrefslider] ;
 iCat_pos_slider[iCatPageis][iCat_select_editing_slider][0]=iCat_pos_slider[iCatPageis][iCatrefslider][0]+grid_icat_modulo;
 iCat_pos_slider[iCatPageis][iCat_select_editing_slider][1]=iCat_pos_slider[iCatPageis][iCatrefslider][1]+grid_icat_modulo;
 ratio_iCat_slider[iCatPageis][iCat_select_editing_slider]=ratio_iCat_slider[iCatPageis][iCatrefslider];
 iCat_affectation_slider_type_is[iCatPageis][iCat_select_editing_slider] = iCat_affectation_slider_type_is[iCatPageis][iCatrefslider];
 iCat_affectation_slider_value_is[iCatPageis][iCat_select_editing_slider] = iCat_affectation_slider_value_is[iCatPageis][iCatrefslider];

 sprintf(string_Last_Order,"Dubbed iCat Slider !");
}
 mouse_released=1;
}

 return(0);
}


int Menu_edition_iCat_boutons(int xed, int yed)
{
char title_iCat_menu[16];

///////////////BOUTONS EDITING///////////////////////////////////////////////////
Rect Button_M(Vec2D(xed-15,yed-10),Vec2D(105,20));
Button_M.SetRoundness(4);
Button_M.Draw(CouleurFond.WithAlpha(0.4));
if(editing_GUI_type_iCat==2)
{Button_M.Draw(CouleurSurvol);}
petitchiffre.Print("Buttons",xed+10,yed+2);
if(mouse_x>xed-15 && mouse_x<xed+90 && mouse_y>yed-10 && mouse_y<yed+10
   && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
if(index_main_clear==1)//clear des sliders selectivement
{
index_ask_iCat_selectiv_clear=1;
index_ask_confirm=1;
}
else
{
if(editing_GUI_type_iCat==2) {editing_GUI_type_iCat=0;}
else editing_GUI_type_iCat=2;
}
mouse_released=1;
}


//NAVIGATION DANS LE bouton A EDITER
previous_button_view(xed-15,yed+15,0);
next_button_view(xed+50,yed+15,0);
Rect button_F(Vec2D(xed+10,yed+15),Vec2D(35,20));
button_F.SetRoundness(4);
button_F.Draw(CouleurFond.WithAlpha(0.4));
sprintf(title_iCat_menu,"%d /%d",iCat_select_editing_button, iCat_nbre_de_boutons[iCatPageis]);
petitpetitchiffre.Print(title_iCat_menu,xed+12,yed+27);

if(mouse_y>yed+15 && mouse_y< yed+35)
{
if(mouse_x>xed-15 && mouse_x<xed+5 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=2;
previous_button_view(xed-15,yed+15,1);
if(iCat_select_editing_button>0){iCat_select_editing_button--;}
else{iCat_select_editing_button=iCat_nbre_de_boutons[iCatPageis];}
mouse_released=1;
}
if(mouse_x>xed+50 && mouse_x<xed+70 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=2;
next_button_view(xed+50,yed+15,1);
if(iCat_select_editing_button<iCat_nbre_de_boutons[iCatPageis]){iCat_select_editing_button++;}
else{iCat_select_editing_button=iCat_nbre_de_boutons[iCatPageis];}
mouse_released=1;
}
}

//DEF MAX BOUTONS
case_moins_view(xed+75,yed+15,0);
case_plus_view(xed+75,yed+35,0);

if(mouse_x>xed+75 && mouse_x<xed+90)
{
if(mouse_y>yed+15 && mouse_y<yed+30 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=2;
case_moins_view(xed+75,yed+15,1);
if(iCat_nbre_de_boutons[iCatPageis]>0){iCat_nbre_de_boutons[iCatPageis]--;
if(iCat_select_editing_button>iCat_nbre_de_boutons[iCatPageis]){iCat_select_editing_button=iCat_nbre_de_boutons[iCatPageis];}
}
mouse_released=1;
}
if(mouse_y>yed+35 && mouse_y<yed+50 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT )
{
editing_GUI_type_iCat=2;
case_plus_view(xed+75,yed+35,1);
if(iCat_nbre_de_boutons[iCatPageis]<max_buttons_icat){iCat_nbre_de_boutons[iCatPageis]++;}
iCat_select_editing_button=iCat_nbre_de_boutons[iCatPageis];
mouse_released=1;
}
}


///SPECS BOUTON
char str_type_iCat[16];
sprintf(str_type_iCat,"X: %d Y: %d",iCat_pos_bouton[iCatPageis][iCat_select_editing_button][0],iCat_pos_bouton[iCatPageis][iCat_select_editing_button][1]);
petitpetitchiffre.Print(str_type_iCat,xed-10,yed+47);


//grossuer bouton
switch(ratio_iCat_button[iCatPageis][iCat_select_editing_button])
{
case 1:
sprintf(str_type_iCat,"small");
break;
case 2:
sprintf(str_type_iCat,"med.");
break;
case 3:
sprintf(str_type_iCat,"big");
break;
default:
sprintf(str_type_iCat,"-");
break;
}
pulse_bar_view(xed-12,yed+55, str_type_iCat);
if(mouse_x>xed-12 && mouse_x<xed+18 && mouse_y>yed+55 && mouse_y<yed+75 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT && iCat_select_editing_button!=0)
{
editing_GUI_type_iCat=2;
ratio_iCat_button[iCatPageis][iCat_select_editing_button]++;
if(ratio_iCat_button[iCatPageis][iCat_select_editing_button]>3){ratio_iCat_button[iCatPageis][iCat_select_editing_button]=1;}
mouse_released=1;
}



///type
char string_temp_familly[25];
petitpetitchiffre.Print("Type:",xed-15,yed+90);
Rect AffectTyp(Vec2D(xed-15,yed+95),Vec2D(100,20));
AffectTyp.SetRoundness(4);
AffectTyp.Draw(CouleurFond.WithAlpha(0.4));
switch(iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button])
{
case 0://desafected
sprintf(string_temp_familly,"-");
break;
case 1: //faders
sprintf(string_temp_familly,"Faders:");
break;
case 2://mini faders
sprintf(string_temp_familly,"MiniFaders:");
break;
case 3://sequenciel
sprintf(string_temp_familly,"Sequences:");
break;
case 4://emulate
sprintf(string_temp_familly,"Emulate Kbd:");
break;
case 5: //Bangers
sprintf(string_temp_familly,"Bangers");
break;
case 6: //iCat menus
sprintf(string_temp_familly,"iCat navigation:");
break;
case 7: //draw
sprintf(string_temp_familly,"Draw:");
break;
default:
break;
}
petitpetitchiffre.Print(string_temp_familly,xed-7,yed+107);

//TYPE
if(mouse_x>xed-15 && mouse_x<xed+85 && mouse_y>yed+95 && mouse_y<yed+115 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT && iCat_select_editing_button!=0)
{
editing_GUI_type_iCat=2;
iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button]++;
if(iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button]>7){iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button]=0;}
iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button]=0;
iCat_affectation_bouton_value_is[iCatPageis][iCat_select_editing_button]=0;
mouse_released=1;
}



///ACTIONS ( sous famille de type bouton)

petitpetitchiffre.Print("Action:",xed-15,yed+122);
Rect AffectAct(Vec2D(xed-15,yed+125),Vec2D(100,20));
AffectAct.SetRoundness(4);
AffectAct.Draw(CouleurFond.WithAlpha(0.4));
switch(iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button])
{
case 1: //faders
switch(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button])
     {

      case 1: //fader up
      sprintf(string_temp_familly,"UP");
      break;
      case 2://fader down
      sprintf(string_temp_familly,"DOWN");
      break;
      case 3://Fader saw
      sprintf(string_temp_familly,"SAW");
      break;
      case 4:
      sprintf(string_temp_familly,"ToPREVDock");
      break;
      case 5:
      sprintf(string_temp_familly,"ToNEXTDock");
      break;
      case 6:
      sprintf(string_temp_familly,"Up/Down");
      break;
      case 7:
      sprintf(string_temp_familly,"LOCK");
      break;
      case 8:
      sprintf(string_temp_familly,"FLASH");
      break;

      case 9:
      sprintf(string_temp_familly,"L/Unloop dock");
      break;
      case 10:
      sprintf(string_temp_familly,"L/Unloop all");
      break;
      case 11:
      sprintf(string_temp_familly,"Play embedded");
      break;
      case 12:
      sprintf(string_temp_familly,"Seek embedded");
      break;
      case 13:
      sprintf(string_temp_familly,"Loop embedded");
      break;
      default:
      sprintf(string_temp_familly,"-");
      break;
      }
      //fin faders
break;
case 2://minifaders

     switch(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button])
     {
     case 0://desafected
      sprintf(string_temp_familly,"-");
      break;
      case 1: //fader up
      sprintf(string_temp_familly,"UP");
      break;
      case 2://fader down
      sprintf(string_temp_familly,"DOWN");
      break;
      case 3://Fader saw
      sprintf(string_temp_familly,"SAW");
      break;
      case 4:
      sprintf(string_temp_familly,"ToPREVDock");
      break;
      case 5:
      sprintf(string_temp_familly,"ToNEXTDock");
      break;
      case 6:
      sprintf(string_temp_familly,"Up/Down");
      break;
      case 7:
      sprintf(string_temp_familly,"LOCK");
      break;
      case 8:
      sprintf(string_temp_familly,"FLASH");
      break;
      case 9:
      sprintf(string_temp_familly,"L/Unloop dock");
      break;
      case 10:
      sprintf(string_temp_familly,"L/Unloop all");
      break;
      case 11:
      sprintf(string_temp_familly,"Dock -");
      break;
      case 12:
      sprintf(string_temp_familly,"Dock +");
      break;
      case 13:
      sprintf(string_temp_familly,"Play embedded");
      break;
      case 14:
      sprintf(string_temp_familly,"All at 0");
      break;
      case 15:
      sprintf(string_temp_familly,"SetPos");
      break;
      case 16:
      sprintf(string_temp_familly,"Select MF");
      break;
      case 17:
      sprintf(string_temp_familly,"UnSelect All MF");
      break;
      case 18:
      sprintf(string_temp_familly,"Select All MF");
      break;
      case 19:
      sprintf(string_temp_familly,"Select MF Pst");
      break;
      case 20:
      sprintf(string_temp_familly,"Select Lock Pst");
      break;
      default:
      break;
      }//fin minifaders
break;

case 3://sequences
switch(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button])
     {
     case 0://desafected
      sprintf(string_temp_familly,"-");
      break;
      case 1:
      sprintf(string_temp_familly,"GO");
      break;
      case 2:
      sprintf(string_temp_familly,"GO BACK");
      break;
      case 3://Fader saw
      sprintf(string_temp_familly,"JUMP");
      break;
      case 4:
      sprintf(string_temp_familly,"STAGE -");
      break;
      case 5:
      sprintf(string_temp_familly,"STAGE +");
      break;
      case 6:
      sprintf(string_temp_familly,"PRESET -");
      break;
      case 7:
      sprintf(string_temp_familly,"PRESET +");
      break;
      case 8:
      sprintf(string_temp_familly,"GOTO");
      break;


default:
sprintf(string_temp_familly,"-");
break;
}
break;
//fin sequences
case 4://emulate
     switch(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button])
     {
      case 0:
      sprintf(string_temp_familly,"0");
      break;
      case 1:
      sprintf(string_temp_familly,"1");
      break;
      case 2:
      sprintf(string_temp_familly,"2");
      break;
      case 3:
      sprintf(string_temp_familly,"3");
      break;
      case 4:
      sprintf(string_temp_familly,"4");
      break;
      case 5:
      sprintf(string_temp_familly,"5");
      break;
      case 6:
      sprintf(string_temp_familly,"6");
      break;
      case 7:
      sprintf(string_temp_familly,"7");
      break;
      case 8:
      sprintf(string_temp_familly,"8");
      break;
      case 9:
      sprintf(string_temp_familly,"9");
      break;
      case 10:
      sprintf(string_temp_familly,".");
      break;
      case 11:
      sprintf(string_temp_familly,"PLUS");
      break;
      case 12:
      sprintf(string_temp_familly,"MINUS");
      break;
      case 13:
      sprintf(string_temp_familly,"ALL");
      break;
      case 14:
      sprintf(string_temp_familly,"INV");
      break;
      case 15:
      sprintf(string_temp_familly,"TAB");
      break;
      case 16:
      sprintf(string_temp_familly,"ESC");
      break;
      case 17:
      sprintf(string_temp_familly,"ENT");
      break;
      case 18://FULL
      sprintf(string_temp_familly,"/100");
      break;
      case 19://a ZERO
      sprintf(string_temp_familly,"/0");
      break;
      case 20://backspace
      sprintf(string_temp_familly,"BCKSP");
      break;
      case 21://DEL
      sprintf(string_temp_familly,"DEL");
      break;
      case 22://arrow Up
      sprintf(string_temp_familly,"UP");
      break;
      case 23://arrow down
      sprintf(string_temp_familly,"DOWN");
      break;
      case 24://arrow left
      sprintf(string_temp_familly,"LEFT");
      break;
      case 25://arrow right
      sprintf(string_temp_familly,"RIGHT");
      break;
      case 26:
      sprintf(string_temp_familly,"F1");
      break;
      case 27:
      sprintf(string_temp_familly,"F2");
      break;
      case 28:
      sprintf(string_temp_familly,"F3");
      break;
      case 29:
      sprintf(string_temp_familly,"F4");
      break;
      case 30:
      sprintf(string_temp_familly,"F11");
      break;
      case 31:
      sprintf(string_temp_familly,"F12");
      break;
      case 32:
      sprintf(string_temp_familly,"SHFT");
      break;
      case 33:
      sprintf(string_temp_familly,"CTRL");
      break;
      default:
      sprintf(string_temp_familly,"-");
      break;
     }

break;
//fin emulate
case 5://banger
switch(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button])
     {
      case 0:
      sprintf(string_temp_familly,"-");
      break;
      case 1:
      sprintf(string_temp_familly,"Bang Solo");
      break;
      default:
      sprintf(string_temp_familly,"-");
      break;
      }
break;
case 6://icat commandes
      switch(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button])
     {
      case 0:
      sprintf(string_temp_familly,"-");
      break;
      case 1:
      sprintf(string_temp_familly,"Page -");
      break;
      case 2:
      sprintf(string_temp_familly,"Page +");
      break;
      case 3:
      sprintf(string_temp_familly,"Page Num:");
      break;
      case 4:
      sprintf(string_temp_familly,"Refresh Page");
      break;
      case 5:
      sprintf(string_temp_familly,"Page Orientation");
      break;
      default:
      sprintf(string_temp_familly,"-");
      break;
      }
break;
case 7://draw
      switch(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button])
     {
      case 1:
      sprintf(string_temp_familly,"Activ BrushType");
      break;
      case 2:
      sprintf(string_temp_familly,"Activ Draw Mode");
      break;
      case 3:
      sprintf(string_temp_familly,"Matrix BrushType");
      break;
      case 4:
      sprintf(string_temp_familly,"Matrix Draw Mode");
      break;
      case 5:
      sprintf(string_temp_familly,"Select Matrix Num:");
      break;
      default:
      sprintf(string_temp_familly,"-");
      break;
      }
break;
//fin icat commandes
default:
break;
}
petitpetitchiffre.Print(string_temp_familly,xed-7,yed+137);
//sous famille
if(mouse_x>xed-15 && mouse_x<xed+85 && mouse_y>yed+125 && mouse_y<yed+145 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT  && iCat_select_editing_button!=0)
{
editing_GUI_type_iCat=2;
iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button]++;
iCat_affectation_bouton_value_is[iCatPageis][iCat_select_editing_button]=0;
int max_menu=0;
switch ( iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button])
{
case 1:
     max_menu=13;//faders
break;
case 2://minifaders
     max_menu=20;//minifaders
break;
case 3://seq
     max_menu=8;
break;
case 4://emulate
max_menu=33;
break;
case 5://banger
max_menu=1;
break;
case 6://icat familly
max_menu=5;
break;
case 7://draw familly
max_menu=5;
break;
default:
break;
}
if(iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button]>max_menu){iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button]=0;}
mouse_released=1;
}


//VARIABLE A LA SOURIS
Rect AffectVar(Vec2D(xed+40,yed+150),Vec2D(45,20));
AffectVar.SetRoundness(5);
AffectVar.Draw(CouleurFond.WithAlpha(0.4));
petitpetitchiffre.Print(ol::ToString(iCat_affectation_bouton_value_is[iCatPageis][iCat_select_editing_button]),
                          xed+55,yed+162);

if(mouse_x>xed+40 && mouse_x<xed+85 && mouse_y>yed+150 && mouse_y<yed+170 &&  window_focus_id==W_iCAT )
{
editing_GUI_type_iCat=2;
AffectVar.DrawOutline(CouleurLigne);
if(  mouse_button==1 && mouse_released==0 && iCat_select_editing_button!=0)
{

int temp_number=atoi(numeric);
reset_numeric_entry();
switch(iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button])
{
case 1: //faders
if(temp_number>48){temp_number=48;}
break;
case 2://minifaders
if(temp_number>48){temp_number=48;}
break;
case 4://seq scene et preset et vitesse
if(temp_number>3){temp_number=3;}
break;
case 5://banger
if(temp_number>127){temp_number=127;}
break;
case 7://draw
if(temp_number>6){temp_number=6;}
break;
default:
break;
}
iCat_affectation_bouton_value_is[iCatPageis][iCat_select_editing_button]=temp_number;
mouse_released=1;
}
}


//BOUTON DUB
Rect DubB(Vec2D(xed-15,yed+150),Vec2D(30,15));

petitpetitchiffre.Print("Dub",xed-10,yed+160);

DubB.SetRoundness(4);
DubB.Draw(CouleurFond.WithAlpha(0.4));
if(mouse_x>xed-15 && mouse_x<xed+15 && mouse_y>yed+150 && mouse_y<yed+165
   && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=2;
if(iCat_nbre_de_boutons[iCatPageis]<max_buttons_icat)
{
 int iCatrefbutton=iCat_select_editing_button;
 iCat_nbre_de_boutons[iCatPageis]++;
 iCat_select_editing_button=iCat_nbre_de_boutons[iCatPageis];
 iCat_pos_bouton[iCatPageis][iCat_select_editing_button][0]=iCat_pos_bouton[iCatPageis][iCatrefbutton][0]+grid_icat_modulo;
 iCat_pos_bouton[iCatPageis][iCat_select_editing_button][1]=iCat_pos_bouton[iCatPageis][iCatrefbutton][1]+grid_icat_modulo;
 ratio_iCat_button[iCatPageis][iCat_select_editing_button]=ratio_iCat_button[iCatPageis][iCatrefbutton];
 iCat_affectation_bouton_type_is[iCatPageis][iCat_select_editing_button] = iCat_affectation_bouton_type_is[iCatPageis][iCatrefbutton];
 iCat_affectation_bouton_action_is[iCatPageis][iCat_select_editing_button] = iCat_affectation_bouton_action_is[iCatPageis][iCatrefbutton];
 iCat_affectation_bouton_value_is[iCatPageis][iCat_select_editing_button] = iCat_affectation_bouton_value_is[iCatPageis][iCatrefbutton];
 sprintf(string_Last_Order,"Dubbed iCat Button !");
}
 mouse_released=1;
}

 return(0);
}




int Menu_edition_iCat_strings(int xed, int yed)
{
char title_iCat_menu[16];

///////////////BOUTONS EDITING///////////////////////////////////////////////////
Rect String_M(Vec2D(xed-15,yed-10),Vec2D(105,20));
String_M.SetRoundness(4);
String_M.Draw(CouleurFond.WithAlpha(0.4));
if(editing_GUI_type_iCat==3)
{String_M.Draw(CouleurSurvol);}
petitchiffre.Print("Strings",xed+10,yed+2);
if(mouse_x>xed-15 && mouse_x<xed+90 && mouse_y>yed-10 && mouse_y<yed+10
   && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
if(index_main_clear==1)//clear des sliders selectivement
{
index_ask_iCat_selectiv_clear=1;
index_ask_confirm=1;
}
else
{
if(editing_GUI_type_iCat==3) {editing_GUI_type_iCat=0;}
else editing_GUI_type_iCat=3;
}
mouse_released=1;
}


//NAVIGATION DANS LE bouton A EDITER
previous_button_view(xed-15,yed+15,0);
next_button_view(xed+50,yed+15,0);
Rect string_F(Vec2D(xed+10,yed+15),Vec2D(35,20));
string_F.SetRoundness(4);
string_F.Draw(CouleurFond.WithAlpha(0.4));
sprintf(title_iCat_menu,"%d /%d",iCat_select_editing_string, iCat_nbre_de_strings[iCatPageis]);
petitpetitchiffre.Print(title_iCat_menu,xed+12,yed+27);

if(mouse_y>yed+15 && mouse_y< yed+35)
{
if(mouse_x>xed-15 && mouse_x<xed+5 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=3;
previous_button_view(xed-15,yed+15,1);
if(iCat_select_editing_string>0){iCat_select_editing_string--;}
else{iCat_select_editing_string=iCat_nbre_de_strings[iCatPageis];}
mouse_released=1;
}
if(mouse_x>xed+50 && mouse_x<xed+70 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=3;
next_button_view(xed+50,yed+15,1);
if(iCat_select_editing_string<iCat_nbre_de_strings[iCatPageis]){iCat_select_editing_string++;}
else{iCat_select_editing_string=iCat_nbre_de_strings[iCatPageis];}
mouse_released=1;
}
}

//DEF MAX strigs
case_moins_view(xed+75,yed+15,0);
case_plus_view(xed+75,yed+35,0);

if(mouse_x>xed+75 && mouse_x<xed+90)
{
if(mouse_y>yed+15 && mouse_y<yed+30 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
editing_GUI_type_iCat=3;
case_moins_view(xed+75,yed+15,1);
if(iCat_nbre_de_strings[iCatPageis]>0){iCat_nbre_de_strings[iCatPageis]--;
if(iCat_select_editing_string>iCat_nbre_de_strings[iCatPageis]){iCat_select_editing_string=iCat_nbre_de_strings[iCatPageis];}
}
mouse_released=1;
}
if(mouse_y>yed+35 && mouse_y<yed+50 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT )
{
editing_GUI_type_iCat=3;
case_plus_view(xed+75,yed+35,1);
if(iCat_nbre_de_strings[iCatPageis]<max_string_icat){iCat_nbre_de_strings[iCatPageis]++;}
iCat_select_editing_string=iCat_nbre_de_strings[iCatPageis];
mouse_released=1;
}
}


///SPECS String
char str_type_iCat[16];
sprintf(str_type_iCat,"X: %d Y: %d",iCat_pos_string[iCatPageis][iCat_select_editing_string][0],iCat_pos_string[iCatPageis][iCat_select_editing_string][1]);
petitpetitchiffre.Print(str_type_iCat,xed-10,yed+47);


//grossuer bouton
switch(ratio_iCat_string[iCatPageis][iCat_select_editing_string])
{
case 1:
sprintf(str_type_iCat,"small");
break;
case 2:
sprintf(str_type_iCat,"med.");
break;
case 3:
sprintf(str_type_iCat,"big");
break;
default:
sprintf(str_type_iCat,"-");
break;
}
pulse_bar_view(xed-12,yed+55, str_type_iCat);
if(mouse_x>xed-12 && mouse_x<xed+18 && mouse_y>yed+55 && mouse_y<yed+75 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT  && iCat_select_editing_string!=0)
{
editing_GUI_type_iCat=3;
ratio_iCat_string[iCatPageis][iCat_select_editing_string]++;
if(ratio_iCat_string[iCatPageis][iCat_select_editing_string]>3){ratio_iCat_string[iCatPageis][iCat_select_editing_string]=1;}
mouse_released=1;
}



///type
char string_temp_familly[25];
petitpetitchiffre.Print("Type:",xed-15,yed+90);
Rect AffectTyp(Vec2D(xed-15,yed+95),Vec2D(100,20));
AffectTyp.SetRoundness(4);
AffectTyp.Draw(CouleurFond.WithAlpha(0.4));
switch(iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string])
{
case 0://desafected
sprintf(string_temp_familly,"-");
break;
case 1: //Feedback
sprintf(string_temp_familly,"Feedback:");
break;
case 2: //sequenciel
sprintf(string_temp_familly,"Sequences:");
break;
default:
break;
}
petitpetitchiffre.Print(string_temp_familly,xed-7,yed+107);

//TYPE
if(mouse_x>xed-15 && mouse_x<xed+85 && mouse_y>yed+95 && mouse_y<yed+115 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT  && iCat_select_editing_string!=0)
{
editing_GUI_type_iCat=3;
iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string]++;
if(iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string]>2){iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string]=0;}
iCat_affectation_string_action_is[iCatPageis][iCat_select_editing_string]=0;
mouse_released=1;
}



///ACTIONS ( sous famille de type bouton)

petitpetitchiffre.Print("Action:",xed-15,yed+122);
Rect AffectAct(Vec2D(xed-15,yed+125),Vec2D(100,20));
AffectAct.SetRoundness(4);
AffectAct.Draw(CouleurFond.WithAlpha(0.4));
switch(iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string])
{
case 0://desafected
sprintf(string_temp_familly,"-");
break;
case 1: //Feedback

     switch(iCat_affectation_string_action_is[iCatPageis][iCat_select_editing_string])
     {
     case 0://desafected
      sprintf(string_temp_familly,"-");
      break;
      case 1: //input
      sprintf(string_temp_familly,"Input");
      break;
      case 2://last ch
      sprintf(string_temp_familly,"Last CH.");
      break;
      case 3://dimmers
      sprintf(string_temp_familly,"DIM.");
      break;
      case 4://last order
      sprintf(string_temp_familly,"Last Order");
      break;
      case 5:
      sprintf(string_temp_familly,"Confirm");
      break;
      default:
      break;
      }

break;
//fin feedback

case 2://sequences
    switch(iCat_affectation_string_action_is[iCatPageis][iCat_select_editing_string])
     {
     case 0://desafected
      sprintf(string_temp_familly,"-");
      break;
      case 1: //X1
      sprintf(string_temp_familly,"Stage");
      break;
      case 2://X2
      sprintf(string_temp_familly,"Preset");
      break;
      case 3://Before 1
      sprintf(string_temp_familly,"Mem. Before 1");
      break;
      case 4://Mem +
      sprintf(string_temp_familly,"Mem. After 1");
      break;
      default:
      break;
      }
break; //fin  stringsequences
default:
break;
}
petitpetitchiffre.Print(string_temp_familly,xed-7,yed+137);
//sous famille
if(mouse_x>xed-15 && mouse_x<xed+85 && mouse_y>yed+125 && mouse_y<yed+145 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT  && iCat_select_editing_string!=0)
{
editing_GUI_type_iCat=3;
iCat_affectation_string_action_is[iCatPageis][iCat_select_editing_string]++;
int max_menu=0;
switch ( iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string])
{
case 1:
     max_menu=4;//feedbacks strings
break;
case 2:
     max_menu=4;//sequencieal strings
break;
default:
break;
}
if(iCat_affectation_string_action_is[iCatPageis][iCat_select_editing_string]>max_menu){iCat_affectation_string_action_is[iCatPageis][iCat_select_editing_string]=0;}
mouse_released=1;
}

//VARIABLE A LA SOURIS
if(iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string]==2 )
{//que pour sequenciel
Rect AffectVar(Vec2D(xed+40,yed+150),Vec2D(45,20));
AffectVar.SetRoundness(5);
AffectVar.Draw(CouleurFond.WithAlpha(0.4));
petitpetitchiffre.Print(ol::ToString(iCat_affectation_string_value_is[iCatPageis][iCat_select_editing_string]),
                          xed+55,yed+162);

if(mouse_x>xed+40 && mouse_x<xed+40+45 && mouse_y>yed+150 && mouse_y<yed+150+20 &&  window_focus_id==W_iCAT )
{
editing_GUI_type_iCat=3;
AffectVar.DrawOutline(CouleurLigne);
if(  mouse_button==1 && mouse_released==0 && iCat_select_editing_string!=0)
{
int temp_number=atoi(numeric);
reset_numeric_entry();
switch(iCat_affectation_string_type_is[iCatPageis][iCat_select_editing_string])
{
case 2: //Mem after
if(temp_number>12){temp_number=12;}
break;
default:
break;
}
iCat_affectation_string_value_is[iCatPageis][iCat_select_editing_string]=temp_number;
mouse_released=1;
}
}
}




 return(0);
}

int Point_Viewing(int macx,int macy)
{

   char info_point[64];
   sprintf(info_point,"Accelerometer: %.3f %.3f %.3f",fs_accelerometer[0],fs_accelerometer[1],fs_accelerometer[2]);
   petitpetitchiffre.Print(info_point,macx,macy);

   petitchiffrerouge.Print("Points:",macx,macy+10);
   for(int poin=0;poin<fs_max_points;poin++)
   {
   sprintf(info_point,"%d/B:%d-%d M:%d-%d E:%d-%d",(poin+1),
                                 FS_touch_point_begin[0][poin],FS_touch_point_begin[1][poin],
                                 FS_touch_point_move[0][poin],FS_touch_point_move[1][poin],
                                 FS_touch_point_end[0][poin],FS_touch_point_end[0][poin]);
   petitpetitchiffre.Print(info_point,macx,macy+20+(poin*12));
   }
return(0);
}


int Tablier_GUI_editor( int gx, int gy)
{
   Point_Viewing(gx+10,gy+10);
 //tablier d'édition
   Rect InterFS(Vec2D(gx,gy),Vec2D(L_tablier_iCat,H_tablier_iCat));
   InterFS.SetRoundness(5);
   InterFS.SetLineWidth(demi_epaisseur_ligne_fader);
   InterFS.Draw(CouleurFond.WithAlpha(0.8));
   InterFS.DrawOutline(CouleurLigne);
   //affichage sliders
   if(iCat_nbre_de_sliders[iCatPageis]>0)
   {
   for(int sl=1;sl<iCat_nbre_de_sliders[iCatPageis]+1;sl++)
   {
//vertical
          if(iCat_orientation_slider[iCatPageis][sl]==0)
                          {l_sl=iCatSlidersizeX; h_sl=iCatSlidersizeY;}
                          //horizontal
          else
                 { l_sl=iCatSlidersizeY;h_sl=iCatSlidersizeX;}
//affichage si dans tablier
if(iCat_pos_slider[iCatPageis][sl][0]<L_tablier_iCat &&  iCat_pos_slider[iCatPageis][sl][1]<H_tablier_iCat)
{
            Rect Slider_Big(Vec2D(gx+iCat_pos_slider[iCatPageis][sl][0],gy+iCat_pos_slider[iCatPageis][sl][1]),
             Vec2D((l_sl*ratio_iCat_slider[iCatPageis][sl])/2,(h_sl*ratio_iCat_slider[iCatPageis][sl])/2));//la size est divisee par 2
             //par rapport vision global dasn tablier
           if(slider_is_touched[iCatPageis][sl]==1){Slider_Big.Draw(CouleurFader); }
          Slider_Big.DrawOutline(CouleurLigne);
          petitpetitchiffre.Print(ol::ToString(sl),gx+iCat_pos_slider[iCatPageis][sl][0],gy+iCat_pos_slider[iCatPageis][sl][1]);
          if(editing_GUI_type_iCat==1 && iCat_select_editing_slider==sl)
          {
          Slider_Big.SetLineWidth(4.0);
          Slider_Big.DrawOutline(CouleurSurvol);
          }
}

   }
   }

      //affichage boutons
   if(iCat_nbre_de_boutons[iCatPageis]>0)
   {
   for(int sl=1;sl<iCat_nbre_de_boutons[iCatPageis]+1;sl++)
   {
//affichage boutons que si dans tablier
 if(iCat_pos_bouton[iCatPageis][sl][0]<L_tablier_iCat &&  iCat_pos_bouton[iCatPageis][sl][1]<H_tablier_iCat)
{

            Rect Bouton_Big(
            Vec2D( gx+iCat_pos_bouton[iCatPageis][sl][0],gy+iCat_pos_bouton[iCatPageis][sl][1]),
            Vec2D((largueur_bouton*ratio_iCat_button[iCatPageis][sl])/2,(largueur_bouton*ratio_iCat_button[iCatPageis][sl])/2));//boutons carrés
          if(button_is_touched[iCatPageis][sl]==1){Bouton_Big.Draw(CouleurFader); }
          Bouton_Big.DrawOutline(CouleurLigne);
          petitpetitchiffre.Print(ol::ToString(sl),gx+iCat_pos_bouton[iCatPageis][sl][0],gy+iCat_pos_bouton[iCatPageis][sl][1]);
          if(editing_GUI_type_iCat==2 && iCat_select_editing_button==sl)
          {
          Bouton_Big.SetLineWidth(4.0);
          Bouton_Big.DrawOutline(CouleurSurvol);
          }
}
   }
   }
     //affichage strings
   if(iCat_nbre_de_strings[iCatPageis]>0)
   {
   for(int sl=1;sl<iCat_nbre_de_strings[iCatPageis]+1;sl++)
   {
//affichage strings que si dans tablier
 if(iCat_pos_string[iCatPageis][sl][0]<L_tablier_iCat &&  iCat_pos_string[iCatPageis][sl][1]<H_tablier_iCat)
{

            Rect String_Big(
            Vec2D( gx+iCat_pos_string[iCatPageis][sl][0],gy+iCat_pos_string[iCatPageis][sl][1]),
            Vec2D((largeur_string*ratio_iCat_string[iCatPageis][sl])/2,(hauteur_string*ratio_iCat_string[iCatPageis][sl])/2));//boutons carrés

          String_Big.DrawOutline(CouleurLigne);
          petitpetitchiffre.Print(ol::ToString(sl),gx+iCat_pos_string[iCatPageis][sl][0],gy+iCat_pos_string[iCatPageis][sl][1]);
          if(editing_GUI_type_iCat==3 && iCat_select_editing_string==sl)
          {
          String_Big.SetLineWidth(4.0);
          String_Big.DrawOutline(CouleurSurvol);
          }

}
   }
   }

       //affichage  zone
   if(iCat_nbre_de_tracking_zone[iCatPageis]>0)
   {
   for(int sl=1;sl<iCat_nbre_de_tracking_zone[iCatPageis]+1;sl++)
   {
//affichage strings que si dans tablier
 if(iCat_pos_trackzone[iCatPageis][sl][0]<L_tablier_iCat &&  iCat_pos_trackzone[iCatPageis][sl][1]<H_tablier_iCat)
{

            Rect Trck_Big(
            Vec2D( gx+iCat_pos_trackzone[iCatPageis][sl][0],gy+iCat_pos_trackzone[iCatPageis][sl][1]),
            Vec2D((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl])/2,(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl])/2));//boutons carrés

          Trck_Big.DrawOutline(CouleurLigne);
          petitpetitchiffre.Print(ol::ToString(sl),gx+iCat_pos_trackzone[iCatPageis][sl][0],gy+iCat_pos_trackzone[iCatPageis][sl][1]);
          if(editing_GUI_type_iCat==4 && iCat_select_tracking_zone==sl)
          {
          Trck_Big.SetLineWidth(4.0);
          Trck_Big.DrawOutline(CouleurSurvol);
          }
}
   }
   }


   if(mouse_x>gx && mouse_x<gx+L_tablier_iCat && mouse_y>gy && mouse_y<gy+H_tablier_iCat
      && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
   {
   //manipulation
   switch(editing_GUI_type_iCat)
   {
   case 1://s/liders
   if(iCat_select_editing_slider>0)
   {
   iCat_pos_slider[iCatPageis][iCat_select_editing_slider][0]=(mouse_x-gx)-((mouse_x-gx)%grid_icat_modulo);
   iCat_pos_slider[iCatPageis][iCat_select_editing_slider][1]=(mouse_y-gy)-((mouse_y-gy)%grid_icat_modulo);
   }
   break;
   case 2://buttons
   if(iCat_select_editing_button>0)
   {
   iCat_pos_bouton[iCatPageis][iCat_select_editing_button][0]=(mouse_x-gx)-((mouse_x-gx)%grid_icat_modulo);
   iCat_pos_bouton[iCatPageis][iCat_select_editing_button][1]=(mouse_y-gy)-((mouse_y-gy)%grid_icat_modulo);
   }
   break;
   case 3://strings
   if(iCat_select_editing_string>0)
   {
   iCat_pos_string[iCatPageis][iCat_select_editing_string][0]=(mouse_x-gx)-((mouse_x-gx)%grid_icat_modulo);
   iCat_pos_string[iCatPageis][iCat_select_editing_string][1]=(mouse_y-gy)-((mouse_y-gy)%grid_icat_modulo);
   }
   break;
   case 4://tracking zone
   if(iCat_select_tracking_zone>0)
   {
   iCat_pos_trackzone[iCatPageis][iCat_select_tracking_zone][0]=(mouse_x-gx)-((mouse_x-gx)%grid_icat_modulo);
   iCat_pos_trackzone[iCatPageis][iCat_select_tracking_zone][1]=(mouse_y-gy)-((mouse_y-gy)%grid_icat_modulo);
   }
   break;
   default:
   break;
   }
   }



 return(0);
}

int  Menu_edition_tracking_zone(int xed,int yed)
{
 char title_iCat_menu[16];

///////////////TRACING ZONE EDITING///////////////////////////////////////////////////
Rect Button_M(Vec2D(xed-15,yed-10),Vec2D(105,20));
Button_M.SetRoundness(4);
Button_M.Draw(CouleurFond.WithAlpha(0.4));
if(editing_GUI_type_iCat==4)
{Button_M.Draw(CouleurSurvol);}
petitchiffre.Print("Tracking Zones",xed-10,yed+2);
if(mouse_x>xed-15 && mouse_x<xed+90 && mouse_y>yed-10 && mouse_y<yed+10
   && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
if(index_main_clear==1)//clear des sliders selectivement
{
index_ask_iCat_selectiv_clear=1;
index_ask_confirm=1;
}
else
{
if(editing_GUI_type_iCat==4) {editing_GUI_type_iCat=0;}
else editing_GUI_type_iCat=4;
}
mouse_released=1;
}


//NAVIGATION DANS LE bouton A EDITER
previous_button_view(xed-15,yed+15,0);
next_button_view(xed+50,yed+15,0);
Rect button_F(Vec2D(xed+10,yed+15),Vec2D(35,20));
button_F.SetRoundness(4);
button_F.Draw(CouleurFond.WithAlpha(0.4));
sprintf(title_iCat_menu,"%d /%d",iCat_select_tracking_zone, iCat_nbre_de_tracking_zone[iCatPageis]);
petitpetitchiffre.Print(title_iCat_menu,xed+12,yed+27);

if(mouse_y>yed+15 && mouse_y< yed+35)
{
if(mouse_x>xed-15 && mouse_x<xed+5 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
previous_button_view(xed-15,yed+15,1);
if(iCat_select_tracking_zone>0){iCat_select_tracking_zone--;}
else{iCat_select_tracking_zone=iCat_nbre_de_tracking_zone[iCatPageis];}
mouse_released=1;
}
if(mouse_x>xed+50 && mouse_x<xed+70 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT)
{
next_button_view(xed+50,yed+15,1);
if(iCat_select_tracking_zone<iCat_nbre_de_tracking_zone[iCatPageis]){iCat_select_tracking_zone++;}
else{iCat_select_tracking_zone=iCat_nbre_de_tracking_zone[iCatPageis];}
mouse_released=1;
}
}

//DEF MAX BOUTONS
case_moins_view(xed+75,yed+15,0);
case_plus_view(xed+75,yed+35,0);

if(mouse_x>xed+75 && mouse_x<xed+90)
{
if(mouse_y>yed+15 && mouse_y<yed+30 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT && editing_GUI_type_iCat==4)
{
case_moins_view(xed+75,yed+15,1);
if(iCat_nbre_de_tracking_zone[iCatPageis]>0){iCat_nbre_de_tracking_zone[iCatPageis]--;
if(iCat_select_tracking_zone>iCat_nbre_de_tracking_zone[iCatPageis]){iCat_select_tracking_zone=iCat_nbre_de_tracking_zone[iCatPageis];}
}
mouse_released=1;
}
if(mouse_y>yed+35 && mouse_y<yed+50 && mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT && editing_GUI_type_iCat==4)
{
case_plus_view(xed+75,yed+35,1);
if(iCat_nbre_de_tracking_zone[iCatPageis]<max_zones_icat){iCat_nbre_de_tracking_zone[iCatPageis]++;}
iCat_select_tracking_zone=iCat_nbre_de_tracking_zone[iCatPageis];
mouse_released=1;
}
}


///SPECS zone
char str_type_iCat[16];
sprintf(str_type_iCat,"X: %d Y: %d",iCat_pos_trackzone[iCatPageis][iCat_select_tracking_zone][0],iCat_pos_trackzone[iCatPageis][iCat_select_tracking_zone][1]);
petitpetitchiffre.Print(str_type_iCat,xed-10,yed+47);


//grossuer zone
switch(ratio_iCat_trackzone[iCatPageis][iCat_select_tracking_zone])
{
case 1:
sprintf(str_type_iCat,"small");
break;
case 2:
sprintf(str_type_iCat,"med.");
break;
case 3:
sprintf(str_type_iCat,"big");
break;
case 4:
sprintf(str_type_iCat,"B I G");
break;
default:
sprintf(str_type_iCat,"-");
break;
}
pulse_bar_view(xed-12,yed+55, str_type_iCat);
if(mouse_x>xed-12 && mouse_x<xed+18 && mouse_y>yed+55 && mouse_y<yed+75 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT && editing_GUI_type_iCat==4 && iCat_select_tracking_zone!=0)
{
ratio_iCat_trackzone[iCatPageis][iCat_select_tracking_zone]++;
if(ratio_iCat_trackzone[iCatPageis][iCat_select_tracking_zone]>4){ratio_iCat_trackzone[iCatPageis][iCat_select_tracking_zone]=0;}
mouse_released=1;
}



///type
char string_temp_familly[25];
Rect AffectTyp(Vec2D(xed-15,yed+95),Vec2D(100,20));
AffectTyp.SetRoundness(4);
AffectTyp.Draw(CouleurFond.WithAlpha(0.4));
switch(iCat_trackzone_type_is[iCatPageis][iCat_select_tracking_zone] )//mover
{
case 0://desafected
sprintf(string_temp_familly,"-");
break;
case 1://mover
sprintf(string_temp_familly,"Mover");
break;
case 2://draw
sprintf(string_temp_familly,"Draw Activ");
break;
case 3://draw
sprintf(string_temp_familly,"Draw Matrix");
break;
default:
break;
}
petitpetitchiffre.Print(string_temp_familly,xed-7,yed+107);

//TYPE
if(mouse_x>xed-15 && mouse_x<xed+85 && mouse_y>yed+95 && mouse_y<yed+115 &&
   mouse_button==1 && mouse_released==0 && window_focus_id==W_iCAT && editing_GUI_type_iCat==4 && iCat_select_tracking_zone!=0)
{
iCat_trackzone_type_is[iCatPageis][iCat_select_tracking_zone]++;
if(iCat_trackzone_type_is[iCatPageis][iCat_select_tracking_zone]>3){iCat_trackzone_type_is[iCatPageis][iCat_select_tracking_zone]=0;}
mouse_released=1;
}

//VARIABLES A LA SOURIS
//X
Rect AffectVar(Vec2D(xed+40,yed+120),Vec2D(45,20));
AffectVar.SetRoundness(5);
AffectVar.Draw(CouleurFond.WithAlpha(0.4));
petitpetitchiffre.Print(ol::ToString(iCat_trackzone_affectation_is[iCatPageis][iCat_select_tracking_zone]),
                          xed+55,yed+132);

if(mouse_x>xed+40 && mouse_x<xed+85 && mouse_y>yed+120 && mouse_y<yed+140 &&  window_focus_id==W_iCAT && editing_GUI_type_iCat==4)
{
AffectVar.DrawOutline(CouleurLigne);
if(  mouse_button==1 && mouse_released==0 && iCat_select_tracking_zone!=0)
{
int temp_number=atoi(numeric);

switch(iCat_trackzone_type_is[iCatPageis][iCat_select_tracking_zone])
{
case 1: // tracker move
if(temp_number>48)
{temp_number=48;}
iCat_trackzone_affectation_is[iCatPageis][iCat_select_tracking_zone]=temp_number;reset_numeric_entry();
break;
case 3:
if(temp_number>6)
{temp_number=6;}
iCat_trackzone_affectation_is[iCatPageis][iCat_select_tracking_zone]=temp_number;reset_numeric_entry();
break;
default:
break;
}

mouse_released=1;
}
}

 return(0);
}

int BoxGuiBuilder_iCat ( int gx, int gy)
{

   Rect backFS(Vec2D(gx,gy),Vec2D(largeuriCat,hauteuriCat));
   backFS.SetRoundness(5);
   backFS.SetLineWidth(triple_epaisseur_ligne_fader);
   backFS.Draw(CouleurConfig);
   if( window_focus_id==W_iCAT)
   {
   backFS.DrawOutline(CouleurFader);
   }
   else {backFS.DrawOutline(CouleurLigne);}
   neuro.Print( "FantaStick-iCat Interface Builder",(gx+100), (gy+25));


//LIGNE DES OPTIONS
//surface iPOD/iPAD
switch(surface_type)
{
case 0:
toggling_bar_view(gx+20,gy+40, iCat_preset_orientation[iCatPageis], "   iPOD ");
break;
case 1:
toggling_bar_view(gx+20,gy+40, iCat_preset_orientation[iCatPageis], "   iPAD ");
break;
default:
break;
}
if(mouse_x>gx+20 && mouse_x<gx+90 && mouse_y>gy+40 && mouse_y<gy+60 && window_focus_id==W_iCAT && im_moving_a_window==0 )
{
      if( mouse_button==1 && mouse_released==0)
      {
      surface_type++;
      if(surface_type>1){surface_type=0;}
      recalculate_iCatBuilder_window_size();
      mouse_released=1;
      }
}


//orientation du preset
char tmpch[24];
switch(iCat_preset_orientation[iCatPageis])
{
 case 0:
 sprintf(tmpch,"    Vertical");
 break;
  case 1:
 sprintf(tmpch," Horizontal 1");
 break;
  case 2:
 sprintf(tmpch," Horizontal 2");
 break;
 default:
 sprintf(tmpch,"-");
 break;
}

toggling_bar_view(gx+100,gy+40, iCat_preset_orientation[iCatPageis], tmpch);

Rect iCatPresetO(Vec2D(gx+100,gy+40),Vec2D(70,20));
iCatPresetO.SetRoundness(5);
   if(mouse_x>gx+100 && mouse_x<gx+170 && mouse_y>gy+40 && mouse_y<gy+60 && window_focus_id==W_iCAT && im_moving_a_window==0)
   {
    if( Midi_Faders_Affectation_Type!=0)
    {
    iCatPresetO.DrawOutline(CouleurBlind);
    //midi report
     switch(miditable[0][1275])
    {
    case 0:
    sprintf(thetypinfo,"Note");
    break;
    case 1:
    sprintf(thetypinfo,"Key On");
    break;
    case 2:
    sprintf(thetypinfo,"Key Off");
    break;
    case 4:
    sprintf(thetypinfo,"Ctrl Change");
    break;
    default: break;
    }
    sprintf(string_last_midi_id,"iCat Page Orientation is Ch: %d Pitch: %d Type: %s", miditable[1][1275],miditable[2][1275],thetypinfo);
  if(mouse_button==1 && mouse_released==0)
  {
  attribute_midi_to_control(1275,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
  mouse_released=1;
  }

  }
    else
    {
    if( mouse_button==1 && mouse_released==0)
    {

   iCat_preset_orientation[iCatPageis]++;
   if(iCat_preset_orientation[iCatPageis]>2){iCat_preset_orientation[iCatPageis]=0;}
   recalculate_iCatBuilder_window_size();

   do_refresh_iCat(iCatPageis);
   mouse_released=1;
   }
}
}


//modulo grid
Rect AffectModulo(Vec2D(gx+180,gy+40),Vec2D(45,20));
AffectModulo.SetRoundness(5);
AffectModulo.Draw(CouleurFond.WithAlpha(0.4));
petitchiffre.Print("%", gx+185,gy+52);
petitpetitchiffre.Print(ol::ToString(grid_icat_modulo), gx+200,gy+52);

if(mouse_x>gx+180 && mouse_x<gx+225 && mouse_y>gy+40 && mouse_y<gy+60 &&  window_focus_id==W_iCAT)
{
AffectModulo.DrawOutline(CouleurLigne);
if(  mouse_button==1 && mouse_released==0 )
{
int temp_number=atoi(numeric);
grid_icat_modulo=temp_number;
if(grid_icat_modulo<1){grid_icat_modulo=1;}
else if(grid_icat_modulo>50){grid_icat_modulo=50;}
reset_numeric_entry();
mouse_released=1;
}
}


//copy Page
Rect CopyB(Vec2D(gx+240,gy+40),Vec2D(45,20));
CopyB.SetRoundness(5);
CopyB.Draw(CouleurFond.WithAlpha(0.4));
if(index_icat_copyPage==1)
{
CopyB.Draw(CouleurFader);
}
petitpetitchiffre.Print("Copy", gx+245,gy+40+12);

if(mouse_x>gx+240 && mouse_x<gx+285 && mouse_y>gy+40 && mouse_y<gy+60 &&  window_focus_id==W_iCAT)
{
if(  mouse_button==1 && mouse_released==0 )
{
index_icat_copyPage=toggle(index_icat_copyPage);
iCatPageToCopyIn=iCatPageis;
mouse_released=1;
}
}



//refresh
toggling_bar_view(gx+300,gy+40, iCat_preset_orientation[iCatPageis], "  Refresh");
Rect iCatPresetR(Vec2D(gx+300,gy+40),Vec2D(70,20));
iCatPresetR.SetRoundness(5);
if(mouse_x>gx+300 && mouse_x<gx+370 && mouse_y>gy+40 && mouse_y<gy+60 && window_focus_id==W_iCAT )
      {
    if( Midi_Faders_Affectation_Type!=0)
    {
    iCatPresetR.DrawOutline(CouleurBlind);
    //midi report
     switch(miditable[0][1276])
    {
    case 0:
    sprintf(thetypinfo,"Note");
    break;
    case 1:
    sprintf(thetypinfo,"Key On");
    break;
    case 2:
    sprintf(thetypinfo,"Key Off");
    break;
    case 4:
    sprintf(thetypinfo,"Ctrl Change");
    break;
    default: break;
    }
    sprintf(string_last_midi_id,"iCat Page Refresh is Ch: %d Pitch: %d Type: %s", miditable[1][1276],miditable[2][1276],thetypinfo);
  if(mouse_button==1 && mouse_released==0)
  {
  attribute_midi_to_control(1276,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
  mouse_released=1;
  }

  }
    else
    {
    if( mouse_button==1 && mouse_released==0)
    {
   do_refresh_iCat(iCatPageis);
   mouse_released=1;
   }
}
}

//PRESETS MINUS ET PLUS
   Rect iCatPresetM(Vec2D(gx+380,gy+40),Vec2D(50,20));
    iCatPresetM.SetRoundness(7.5);
    iCatPresetM.Draw(CouleurFond.WithAlpha(0.5));
    petitpetitchiffre.Print("-",gx+400,gy+53);
    if(mouse_x> gx+380 && mouse_x<gx+430 && mouse_y>gy+40 && mouse_y<gy+60 && window_focus_id==W_iCAT)
    {
    if( Midi_Faders_Affectation_Type!=0)
    {
     iCatPresetM.DrawOutline(CouleurBlind);

    //midi report
     switch(miditable[0][1265])
    {
    case 0:
    sprintf(thetypinfo,"Note");
    break;
    case 1:
    sprintf(thetypinfo,"Key On");
    break;
    case 2:
    sprintf(thetypinfo,"Key Off");
    break;
    case 4:
    sprintf(thetypinfo,"Ctrl Change");
    break;
    default: break;
    }
    sprintf(string_last_midi_id,"iCat Page Minus is Ch: %d Pitch: %d Type: %s", miditable[1][1265],miditable[2][1265],thetypinfo);
  if(mouse_button==1 && mouse_released==0)
  {
  attribute_midi_to_control(1265,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
  mouse_released=1;
  }

  }
    else
    {
     if( mouse_button==1 && mouse_released==0)
     {   iCatPageis--;
         if(iCatPageis<0){iCatPageis=7;}
         load_iCat_page(iCatPageis);
         do_send_icat_init_page=1;
         mouse_released=1;
     }
     }
    }

    Rect iCatPresetP(Vec2D(gx+440,gy+40),Vec2D(50,20));
    iCatPresetP.SetRoundness(7.5);
    iCatPresetP.Draw(CouleurFond.WithAlpha(0.5));
    petitpetitchiffre.Print("+",gx+460,gy+53);
    if(mouse_x> gx+440 && mouse_x<gx+490 && mouse_y>gy+40 && mouse_y<gy+60  && window_focus_id==W_iCAT)
    {
    if(Midi_Faders_Affectation_Type!=0)
    {
    iCatPresetP.DrawOutline(CouleurBlind);
    //midi report
     switch(miditable[0][1266])
    {
    case 0:
    sprintf(thetypinfo,"Note");
    break;
    case 1:
    sprintf(thetypinfo,"Key On");
    break;
    case 2:
    sprintf(thetypinfo,"Key Off");
    break;
    case 4:
    sprintf(thetypinfo,"Ctrl Change");
    break;
    default: break;
    }
    sprintf(string_last_midi_id,"iCat Page Plus is Ch: %d Pitch: %d Type: %s", miditable[1][1266],miditable[2][1266],thetypinfo);
  if(mouse_button==1 && mouse_released==0)
  {
  attribute_midi_to_control(1266,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
  mouse_released=1;
  }

  }
    else
    {
    if( mouse_button==1 && mouse_released==0)
    {
    iCatPageis++;
    if(iCatPageis>7){iCatPageis=0;}
    load_iCat_page(iCatPageis);
    do_send_icat_init_page=1;
    mouse_released=1;
    }
    }
}


//APPELS DES 8 PAGES DE PRESET
   for(int o=0;o<8;o++)//8 docks pages iCat
   {
    Rect iCatPreset(Vec2D(gx+20+(o*60),gy+70),Vec2D(50,20));
    iCatPreset.SetRoundness(7.5);
    iCatPreset.SetLineWidth(tiers_epaisseur_ligne_fader);
    if( iCatPageis==o){iCatPreset.Draw(CouleurFader);}
    else {iCatPreset.Draw(CouleurFond.WithAlpha(0.5));}
    petitpetitchiffre.Print(ol::ToString(o+1),gx+42+(o*60),gy+83);
    if(mouse_x> gx+20+(o*60) && mouse_x<gx+70+(o*60) && mouse_y>gy+70 && mouse_y<gy+90  && window_focus_id==W_iCAT)
    {
    if( Midi_Faders_Affectation_Type!=0)
    {
    iCatPreset.DrawOutline(CouleurBlind);
    //midi report
     switch(miditable[0][1267+o])
    {
    case 0:
    sprintf(thetypinfo,"Note");
    break;
    case 1:
    sprintf(thetypinfo,"Key On");
    break;
    case 2:
    sprintf(thetypinfo,"Key Off");
    break;
    case 4:
    sprintf(thetypinfo,"Ctrl Change");
    break;
    default: break;
    }
    sprintf(string_last_midi_id,"iCat Page %d is Ch: %d Pitch: %d Type: %s",o+1, miditable[1][1267+o],miditable[2][1267+o],thetypinfo);
  if(mouse_button==1 && mouse_released==0)
  {
  attribute_midi_to_control(1267+o,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
  mouse_released=1;
  }

  }
    else
    {
    if( mouse_button==1 && mouse_released==0)
    {

    if(index_main_clear==1 && index_icat_copyPage==0)
    {
    iCatPageis=o;
    index_ask_confirm=1;
    index_ask_clear_iCatpage=1;
    }
    else if(index_icat_copyPage==1)
    {
    iCatPageToCopyIn=o;
    index_ask_confirm=1;
    index_ask_icat_copyPage=1;
    }
    else
    {
    iCatPageis=o;
    load_iCat_page(iCatPageis);
    do_send_icat_init_page=1;
    }

    mouse_released=1;
    }
   }
   }
}



   Tablier_GUI_editor(gx+20,gy+100);
   Menu_edition_iCat_sliders(gx+20,gy+H_tablier_iCat+130);
   Menu_edition_iCat_boutons(gx+150,gy+H_tablier_iCat+130);
   Menu_edition_iCat_strings(gx+280,gy+H_tablier_iCat+130);
   Menu_edition_tracking_zone(gx+410,gy+H_tablier_iCat+130);


 return(0);
}












/////////////////////CFG////////////////////////////////////////////////////////
int BoxiCat ( int macx, int macy)
{
   petitchiffre.Print("FANTASTICK-iCAT",macx, macy-50);
   petitpetitchiffrerouge.Print(FS_IP,macx,macy-35);
   //message raw
   petitpetitchiffre.Print("RAW data:",macx,macy-25);
   petitpetitchiffre.Print(FS_BUFFER,macx,macy-15);

   petitchiffre.Print("IP:",macx,macy);
   Rect ipFS(Vec2D(macx+20,macy-12),Vec2D(110,25));
   ipFS.SetRoundness(5);
   ipFS.Draw(CouleurFond.WithAlpha(0.5));
   petitchiffre.Print(specified_fs_ip,macx+25,macy);

   if(window_focus_id==W_CFGMENU && mouse_x>macx+20 && mouse_x<macx+130 && mouse_y>macy-12 && mouse_y<macy+13)
   {
    ipFS.DrawOutline(CouleurLigne);
    if(mouse_button==1 && mouse_released==0)
    {
    if(iCat_serveur_is_initialized==1)
    {
    fermeture_clientserveur_iCat();
    }
    for (int i=0;i<17;i++)
    {specified_fs_ip[i]= numeric[i];}
    reset_numeric_entry();
    initialisation_clientserveur_iCat();
    mouse_released=1;
    }
   }

   petitchiffre.Print("Server port:",macx,macy+30);
   Rect pservFS(Vec2D(macx+75,macy+15),Vec2D(50,25));
   pservFS.SetRoundness(5);
   pservFS.Draw(CouleurFond.WithAlpha(0.5));
   petitchiffre.Print(ol::ToString(serveurport_iCat),macx+80,macy+30);

   if(window_focus_id==W_CFGMENU && mouse_x>macx+75 && mouse_x<macx+125 && mouse_y>macy+15 && mouse_y<macy+40)
   {
    pservFS.DrawOutline(CouleurLigne);
    if(mouse_button==1 && mouse_released==0)
    {
    if(iCat_serveur_is_initialized==1)
    {
    fermeture_clientserveur_iCat();
    }
    serveurport_iCat=atoi(numeric);
    reset_numeric_entry();
    initialisation_clientserveur_iCat();
    mouse_released=1;
    }
   }

   petitchiffre.Print("Client port:",macx,macy+60);
   Rect pclFS(Vec2D(macx+75,macy+45),Vec2D(50,25));
   pclFS.SetRoundness(5);
   pclFS.Draw(CouleurFond.WithAlpha(0.5));
   petitchiffre.Print(ol::ToString(clientport_iCat),macx+80,macy+60);

   if(window_focus_id==W_CFGMENU && mouse_x>macx+75 && mouse_x<macx+125  && mouse_y>macy+45 && mouse_y<macy+70)
   {
    pclFS.DrawOutline(CouleurLigne);
    if(mouse_button==1 && mouse_released==0)
    {
    if(iCat_serveur_is_initialized==1)
    {
    fermeture_clientserveur_iCat();
    }
    clientport_iCat=atoi(numeric);
    reset_numeric_entry();
    initialisation_clientserveur_iCat();
    mouse_released=1;
    }
   }


   petitchiffre.Print("Iterations:",macx,macy+90);
   Rect itFS(Vec2D(macx+75,macy+75),Vec2D(50,25));
   itFS.SetRoundness(5);
   itFS.Draw(CouleurFond.WithAlpha(0.5));
   petitchiffre.Print(ol::ToString(nbre_d_envois_de_l_info),macx+80,macy+90);

   if(window_focus_id==W_CFGMENU && mouse_x>macx+75 && mouse_x<macx+125  && mouse_y>macy+75 && mouse_y<macy+100)
   {
    itFS.DrawOutline(CouleurLigne);
    if(mouse_button==1 && mouse_released==0)
    {
    nbre_d_envois_de_l_info=atoi(numeric);
    if(nbre_d_envois_de_l_info<1){nbre_d_envois_de_l_info=1;}
    reset_numeric_entry();
    mouse_released=1;
    }
   }

   //reset FS reload images
   petitchiffre.Print("Reload gfx:",macx,macy+120);
   Rect resFS(Vec2D(macx+75,macy+105),Vec2D(50,20));
   resFS.SetRoundness(5);
   resFS.Draw(CouleurFond.WithAlpha(0.5));

   if(window_focus_id==W_CFGMENU && mouse_x>macx+75 && mouse_x<macx+125  && mouse_y>macy+105 && mouse_y<macy+125)
   {
    resFS.Draw(CouleurBlind.WithAlpha(alpha_blinker));
    if(mouse_button==1 && mouse_released==0)
    {
    index_ask_confirm=1;
    index_ask_clear_img_icat=1;
    mouse_released=1;
    }
   }



   return(0);
}

int reset_button(int page, int but, int tp)
{
button_is_touched[page][but]=0;
button_is_controlled_by_point[page][but]=0;
FS_touch_point_begin[0][tp]=-999;FS_touch_point_begin[1][tp]=-999;
FS_touch_point_end[0][tp]=-999;FS_touch_point_end[1][tp]=-999;
FS_touch_point_move[0][tp]=-999;FS_touch_point_move[1][tp]=-999;
return(0);
}


int check_button( int tp)
{

int fsBx=FS_touch_point_begin[0][tp];
int fsBy=FS_touch_point_begin[1][tp];
//sab 02/03/2014 unused var int fsMx=FS_touch_point_move[0][tp];
//sab 02/03/2014 unused var int fsMy=FS_touch_point_move[1][tp];
int fsEx=FS_touch_point_end[0][tp];
int fsEy=FS_touch_point_end[1][tp];

int fsTestX2=0; int fsTestY2=0;

for(int bt=1;bt<iCat_nbre_de_boutons[iCatPageis]+1;bt++)
{

fsTestX2=(iCat_pos_bouton[iCatPageis][bt][0]*2)+(largueur_bouton*ratio_iCat_button[iCatPageis][bt]);
fsTestY2=(iCat_pos_bouton[iCatPageis][bt][1]*2)+(largueur_bouton*ratio_iCat_button[iCatPageis][bt]);
/* original avec appui = action
if (  fsBx>=(iCat_pos_bouton[iCatPageis][bt][0]*2) && fsBx<=fsTestX2 && fsBy>=(iCat_pos_bouton[iCatPageis][bt][1]*2) && fsBy<=fsTestY2 )
{
button_is_touched[iCatPageis][bt]=1;
button_is_controlled_by_point[iCatPageis][bt]=tp;
}
if ( fsEx>=(iCat_pos_bouton[iCatPageis][bt][0]*2) && fsEx<=fsTestX2 && fsEy>=(iCat_pos_bouton[iCatPageis][bt][1]*2) && fsEy<=fsTestY2 )
{
button_is_touched[iCatPageis][bt]=0;
button_is_controlled_by_point[iCatPageis][bt]=tp;
FS_touch_point_end[0][tp]=-999;FS_touch_point_end[1][tp]=-999;
}
*/
//modification janvier 2014 sur enlevage du doigt = action
if (  fsBx>=(iCat_pos_bouton[iCatPageis][bt][0]*2) && fsBx<=fsTestX2 && fsBy>=(iCat_pos_bouton[iCatPageis][bt][1]*2) && fsBy<=fsTestY2 )
{
button_is_touched[iCatPageis][bt]=0;FS_touch_point_end[0][tp]=-999;FS_touch_point_end[1][tp]=-999;
}
if ( fsEx>=(iCat_pos_bouton[iCatPageis][bt][0]*2) && fsEx<=fsTestX2 && fsEy>=(iCat_pos_bouton[iCatPageis][bt][1]*2) && fsEy<=fsTestY2 )
{
button_is_touched[iCatPageis][bt]=1;
button_is_controlled_by_point[iCatPageis][bt]=tp;
}
//do the job///////////////////////////////////////////////////////


if(button_is_touched[iCatPageis][bt]==1 && button_is_controlled_by_point[iCatPageis][bt]==tp  )
{
int fis=0;
bool index_choose_mode_dkloop=0;//0 toggle tt le monde / 1 copie l etat du dck selctionné dans tt le monde
int the_chaser=0;
int the_audio_player=0;
int the_grid_player=0;
int banger_back_is=0;
int action_minif=0;
int dock_selected_is=0;
int bangeriCat=0;

switch(iCat_affectation_bouton_type_is[iCatPageis][bt])
{
case 0:
break;
case 1://faders
fis=(iCat_affectation_bouton_value_is[iCatPageis][bt]-1);

if(DockTypeIs[fis][dock_used_by_fader_is[fis]]==11 || DockTypeIs[fis][dock_used_by_fader_is[fis]]==12
|| DockTypeIs[fis][dock_used_by_fader_is[fis]]==6 || DockTypeIs[fis][dock_used_by_fader_is[fis]]==7 || DockTypeIs[fis][dock_used_by_fader_is[fis]]==8  )

{

if ( DockTypeIs[fis][dock_used_by_fader_is[fis]]==11) the_chaser=ChaserAffectedToDck[fis][dock_used_by_fader_is[fis]];
else if ( DockTypeIs[fis][dock_used_by_fader_is[fis]]==12 )  the_grid_player=faders_dock_grid_affectation[fis][dock_used_by_fader_is[fis]];
else if( DockTypeIs[fis][dock_used_by_fader_is[fis]]==6 ) the_audio_player=DockHasAudioVolume[fis][dock_used_by_fader_is[fis]]-1;
else if ( DockTypeIs[fis][dock_used_by_fader_is[fis]]==7 ) the_audio_player=DockHasAudioPan[fis][dock_used_by_fader_is[fis]]-1;
else if ( DockTypeIs[fis][dock_used_by_fader_is[fis]]==8 ) the_audio_player=DockHasAudioPitch[fis][dock_used_by_fader_is[fis]]-1;
}

     switch(iCat_affectation_bouton_action_is[iCatPageis][bt])
     {
      case 0://desafected
      break;
      case 1: //"UP");
      //for delays
      start_time_for_delays[fis]=actual_time;
      if(lfo_mode_is[fis]!=1)//up
      {
      lfo_mode_is[fis]=1;
      faders_in_float[fis]=Fader[fis];
      }
      else {lfo_mode_is[fis]=0;}
      lfo_cycle_is_on[fis]=0;
      reset_button(iCatPageis,bt, tp);
      break;
      case 2://"DOWN");
      //for delays
      start_time_for_delays[fis]=actual_time;
      if(lfo_mode_is[fis]!=2)//down
      {
      lfo_mode_is[fis]=2;
      faders_in_float[fis]=Fader[fis];
      }
      else {lfo_mode_is[fis]=0;}
      lfo_cycle_is_on[fis]=0;
      reset_button(iCatPageis,bt, tp);
      break;
      case 3://"SAW");
      start_time_for_delays[fis]=actual_time;
      faders_in_float[fis]=Fader[fis];
      if(lfo_cycle_is_on[fis]==0)//
      {
      lfo_cycle_is_on[fis]=1;
      lfo_mode_is[fis]=0;
      //bug saw at 0 / 1
      lfo_running_is_upward[fis]=1;
      }
      else if(lfo_cycle_is_on[fis]==1)
      {
      lfo_cycle_is_on[fis]=0;
      }
      reset_button(iCatPageis,bt, tp);
      break;
      case 4://ToPREVDock");
      if (lfo_do_next_step[fis][0]==0) {lfo_do_next_step[fis][0]=1;lfo_do_next_step[fis][1]=0;}
      else if (lfo_do_next_step[fis][0]==1) {lfo_do_next_step[fis][0]=0; }
      reset_button(iCatPageis,bt, tp);
      break;
      case 5://ToNEXTDock");
      if (lfo_do_next_step[fis][1]==0) {lfo_do_next_step[fis][1]=1;lfo_do_next_step[fis][0]=0; ;}
      else if (lfo_do_next_step[fis][1]==1) {lfo_do_next_step[fis][1]=0; }
      reset_button(iCatPageis,bt, tp);
      break;
      case 6://Up/Down");
      lfo_cycle_steps[fis]= toggle(lfo_cycle_steps[fis]);
      reset_button(iCatPageis,bt, tp);
      break;
      case 7://LOCK");
      switch(FaderLocked[fis])
      {
      case 0:
      FaderLocked[fis]=1;
      StateOfFaderBeforeLock[fis]=Fader[fis];
      if(StateOfFaderBeforeLock[fis]==255){LockFader_is_FullLevel[fis]=1;}
      else if(StateOfFaderBeforeLock[fis]<255){LockFader_is_FullLevel[fis]=0;}
      if(LockFader_is_FullLevel[fis]==0)//quand mis en lock et pas full level rajout 0.7.6
      {
      lfo_mode_is[fis]=0;
      lfo_cycle_is_on[fis]=0;
      }
      break;
      case 1:
      FaderLocked[fis]=0;
      //remise à plat du niveau
      fader_set_level(fis,(unsigned char)((((float)(StateOfFaderBeforeLock[fis]))/255)*locklevel));
      /*
      Fader[fis]=(unsigned char)((((float)(StateOfFaderBeforeLock[fis]))/255)*locklevel);
      midi_levels[fis]=(int)(((float)Fader[fis])/2);*/
      break;
      default: break;
      }
      reset_button(iCatPageis,bt, tp);
      break;
      case 8://FLASH");
      if(FaderIsFlash[fis]==0)
      {FaderIsFlash[fis]=1;}
      break;

      case 9://L/Unloop dock");
      is_dock_for_lfo_selected[fis][dock_used_by_fader_is[fis]]=toggle(is_dock_for_lfo_selected[fis][dock_used_by_fader_is[fis]]);
      reset_button(iCatPageis,bt, tp);
      break;
      case 10://L/Unloop all");

      for (int ck=0;ck<5;ck++)
      {
      if(is_dock_for_lfo_selected[fis][ck]!=is_dock_for_lfo_selected[fis][ck+1])
      {index_choose_mode_dkloop=1;break;}
      }
      switch(index_choose_mode_dkloop)
      {
      case 0:
      for(int op=0;op<6;op++)
      {
       is_dock_for_lfo_selected[fis][op]=toggle(is_dock_for_lfo_selected[fis][op]);
      }
      break;
      case 1:
      //tout le monde prend la valeur du dock selectionné
      for(int j=0;j<6;j++)
      {
      if(DockIsSelected[fis][j]==1)
      {
      int tempval_dockloop=toggle(is_dock_for_lfo_selected[fis][j]);
      for(int k=0;k<6;k++)
      {
      is_dock_for_lfo_selected[fis][k]=toggle(tempval_dockloop);
      }
      break;
      }
      }
      break;
      default: break;
      }
      reset_button(iCatPageis,bt, tp);
      break;
      case 11://Play eCHASER");

switch(DockTypeIs[fis][dock_used_by_fader_is[fis]])
{
case 6://vol
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 switch(player1->isPlaying())
 {
 case 0:
 player1->play();
 break;
 case 1:
 player1->stop();
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2->isPlaying())
 {
 case 0:
 player2->play();
 break;
 case 1:
 player2->stop();
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3->isPlaying())
 {
 case 0:
 player3->play();
 break;
 case 1:
 player3->stop();
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4->isPlaying())
 {
 case 0:
 player4->play();
 break;
 case 1:
 player4->stop();
 break;
 default: break;
 }
break;
default: break;
}
switch(player_is_playing[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
default: break;
}
}
break;
case 7://pan
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 switch(player1->isPlaying())
 {
 case 0:
 player1->play();
 break;
 case 1:
 player1->stop();
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2->isPlaying())
 {
 case 0:
 player2->play();
 break;
 case 1:
 player2->stop();
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3->isPlaying())
 {
 case 0:
 player3->play();
 break;
 case 1:
 player3->stop();
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4->isPlaying())
 {
 case 0:
 player4->play();
 break;
 case 1:
 player4->stop();
 break;
 default: break;
 }
break;
default: break;
}
switch(player_is_playing[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
default: break;
}
}
break;
case 8://pitch
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 switch(player1->isPlaying())
 {
 case 0:
 player1->play();
 break;
 case 1:
 player1->stop();
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2->isPlaying())
 {
 case 0:
 player2->play();
 break;
 case 1:
 player2->stop();
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3->isPlaying())
 {
 case 0:
 player3->play();
 break;
 case 1:
 player3->stop();
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4->isPlaying())
 {
 case 0:
 player4->play();
 break;
 case 1:
 player4->stop();
 break;
 default: break;
 }
break;
default: break;
}
switch(player_is_playing[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
default: break;
}
}
break;
case 11://chaser
chaser_is_playing[the_chaser]=toggle(chaser_is_playing[the_chaser]);
if(chaser_is_playing[the_chaser]==1)//snap du temps at beg
{
chaser_start_time[the_chaser]=actual_time;
//bug olivier marche arriere arrière ligne
if(chaser_step_is[chaser_selected]<0){chaser_step_is[chaser_selected]=0;}
else if(chaser_step_is[chaser_selected]>35){chaser_step_is[chaser_selected]=35;}
}
switch(chaser_is_playing[the_chaser])
{
case 0:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Chaser %d",fis+1,the_chaser+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Chaser %d",fis+1,the_chaser+1);
break;
default: break;
}
break;
case 12://grid
grider_is_playing[the_grid_player]=toggle(grider_is_playing[the_grid_player]);
if(grider_is_playing[the_grid_player]==1){grid_crossfade_start_time[the_grid_player]=actual_time;}
switch(player_is_playing[the_grid_player])
{
case 0:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d GridPl %d",fis+1,the_grid_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY ON from Fader %d GridPl %d",fis+1,the_grid_player+1);
break;
default: break;
}
break;
default:
break;
}


//
      reset_button(iCatPageis,bt, tp);
      break;
      case 12://seek embedded
switch(DockTypeIs[fis][dock_used_by_fader_is[fis]])
{
case 6://vol
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 player1->setPosition(0);
break;
case 1://PLAYER 2
 player2->setPosition(0);
break;
case 2://PLAYER 3
 player3->setPosition(0);
break;
case 3://PLAYER 4
 player4->setPosition(0);
break;
default: break;
}
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",fis+1,the_audio_player+1);
}
break;
case 7://pan
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 player1->setPosition(0);
break;
case 1://PLAYER 2
 player2->setPosition(0);
break;
case 2://PLAYER 3
 player3->setPosition(0);
break;
case 3://PLAYER 4
 player4->setPosition(0);
break;
default: break;
}
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",fis+1,the_audio_player+1);
}
break;
case 8://pitch
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
if(player_is_onloopCue[0]==0  ){player1->setPosition(0);}
else
{player1->setPosition(player_seek_position[0]);}
break;
case 1://PLAYER 2
if(player_is_onloopCue[1]==0  ){player2->setPosition(0);}
else
{player2->setPosition(player_seek_position[1]);}
break;
case 2://PLAYER 3
player3->stop();
if(player_is_onloopCue[2]==0  ){player1->setPosition(0);}
else
{player3->setPosition(player_seek_position[2]);}
break;
case 3://PLAYER 4
if(player_is_onloopCue[3]==0  ){player4->setPosition(0);}
else
{player4->setPosition(player_seek_position[3]);}
break;
default: break;
}
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",fis+1,the_audio_player+1);
}
break;
case 11://chaser
chaser_seek_at_beg(the_chaser);
sprintf(string_Last_Order,">> Seek To Beg from Fader %d Chaser %d",fis+1,the_chaser+1);
break;
case 12://grid
gridplayer_seek(the_grid_player);
sprintf(string_Last_Order,">> Seek from Fader %d GridPl %d",fis+1,the_grid_player+1);
break;
default:
break;
}
      reset_button(iCatPageis,bt, tp);
      break;
      case 13://loop eCHASER
switch(DockTypeIs[fis][dock_used_by_fader_is[fis]])
{
case 6://vol the_audio_player
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 switch(player1-> getRepeat())
 {
 case 0:
 player1->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player1->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
}
break;
case 1://PLAYER 2
 switch(player2-> getRepeat())
 {
 case 0:
 player2->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player2->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3-> getRepeat())
 {
 case 0:
 player3->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player3->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4-> getRepeat())
 {
 case 0:
 player4->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player4->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
default: break;
}

switch(player_is_onloop[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
default: break;
}

}
break;
case 7://pan
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 switch(player1-> getRepeat())
 {
 case 0:
 player1->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player1->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2-> getRepeat())
 {
 case 0:
 player2->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player2->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3-> getRepeat())
 {
 case 0:
 player3->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player3->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4-> getRepeat())
 {
 case 0:
 player4->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player4->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
default: break;
}

switch(player_is_onloop[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
default: break;
}

}
break;
case 8://pitch
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
 switch(player1-> getRepeat())
 {
 case 0:
 player1->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player1->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2-> getRepeat())
 {
 case 0:
 player2->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player2->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3-> getRepeat())
 {
 case 0:
 player3->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player3->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4-> getRepeat())
 {
 case 0:
 player4->setRepeat(true);
 player_is_onloop[the_audio_player]=1;
 break;
 case 1:
 player4->setRepeat(false);
 player_is_onloop[the_audio_player]=0;
 break;
 default: break;
 }
break;
default: break;
}

switch(player_is_onloop[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",fis+1,the_audio_player+1);
break;
default: break;
}

}
break;
case 11: //chaser
chaser_is_in_loop[the_chaser]=toggle(chaser_is_in_loop[the_chaser]);
switch(chaser_is_in_loop[the_chaser])
{
case 0:
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Chaser %d",fis+1, the_chaser+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Chaser %d",fis+1, the_chaser+1);
break;
default: break;
}
break;
case 12: //grid
grider_autostopmode[the_grid_player]=toggle(grider_autostopmode[the_grid_player]);
switch(grider_autostopmode[the_grid_player])
{
case 0:
sprintf(string_Last_Order,">> AutoStop OFF from Fader %d Gpl %d",fis+1, the_grid_player+1);
break;
case 1:
sprintf(string_Last_Order,">> AutoStop ON from Fader %d Gpl %d",fis+1, the_grid_player+1);
break;
default: break;
}
break;
default:
break;
}
      reset_button(iCatPageis,bt, tp);
      break;
      default:
      break;
      }

      //fin faders
break;
//////////////////////////////////////////////////////////////////////////////
case 2://minifaders
switch(iCat_affectation_bouton_action_is[iCatPageis][bt])
{
      case 1: //fader up
      action_minif=3;
      reset_button(iCatPageis,bt, tp);
      break;
      case 2://fader down
      action_minif=4;
      reset_button(iCatPageis,bt, tp);
      break;
      case 3://Fader saw
      action_minif=5;
      reset_button(iCatPageis,bt, tp);
      break;
      case 4://"ToPREVDoid");
      action_minif=9;
      reset_button(iCatPageis,bt, tp);
      break;
      case 5://"ToNEXTDoid");
      action_minif=10;
      reset_button(iCatPageis,bt, tp);
      break;
      case 6://"Up/Down");
      action_minif=11;
      reset_button(iCatPageis,bt, tp);
      break;
      case 7://"LOck");
      action_minif=1;
      reset_button(iCatPageis,bt, tp);
      break;
      case 8://"FLASH");action_minif=0
      action_minif=0;
      for(int tt=0;tt<47;tt++)
      {
      if( minifaders_selected[tt]==1 && FaderIsFlash[tt]==0)
      {FaderIsFlash[tt]=1;}
      }
      break;
      case 9://"L/Unloop dock");
      action_minif=2;
      reset_button(iCatPageis,bt, tp);
      break;
      case 10://"L/Unloop all");
      action_minif=6;
      reset_button(iCatPageis,bt, tp);
      break;
      case 11://"Dock -");
      action_minif=12;
      reset_button(iCatPageis,bt, tp);
      break;
      case 12://"Dock +");
      action_minif=13;
      reset_button(iCatPageis,bt, tp);
      break;
      case 13://"Play eCHASER");
      action_minif=14;
      reset_button(iCatPageis,bt, tp);
      break;
      case 14://all at 0
      action_minif=7;
      reset_button(iCatPageis,bt, tp);
      break;
      case 15://Set pos
      action_minif=8;
      break;
      case 16://"Select M.Fader");
      minifaders_selected[iCat_affectation_bouton_value_is[iCatPageis][bt]-1]=toggle(minifaders_selected[iCat_affectation_bouton_value_is[iCatPageis][bt]-1]);

      switch(minifaders_selected[iCat_affectation_bouton_value_is[iCatPageis][bt]-1])
      {
      case 0:
      sprintf(string_Last_Order,"Minifader %d UN selected",iCat_affectation_bouton_value_is[iCatPageis][bt]);
      break;
      case 1:
      sprintf(string_Last_Order,"Minifader %d SELected",iCat_affectation_bouton_value_is[iCatPageis][bt]);
      break;
      default: break;
      }
      dock_selected_is=detect_dock_used(iCat_affectation_bouton_value_is[iCatPageis][bt]-1);


      if(minifaders_selected[iCat_affectation_bouton_value_is[iCatPageis][bt]-1] ==1 && index_do_dock==1 && index_direct_chan==0)
      {
        fader_selected_for_record=iCat_affectation_bouton_value_is[iCatPageis][bt]-1;
        dock_selected_for_record=dock_selected_is;
        index_do_record_on_faders=1;
        index_ask_confirm=1;
      }
       //report
       else if( index_do_report==1 && index_type==0 && index_do_dock==0 && index_do_modify==0 )
      {
      fader_selected_for_record=iCat_affectation_bouton_value_is[iCatPageis][bt]-1;
       dock_selected_for_record=dock_selected_is;
        index_do_report_on_faders=1;
         index_ask_confirm=1;
          sprintf(string_Last_Order,"Report");
           }

         //modify
          else if( index_do_modify==1 )
           {
            fader_selected_for_record=iCat_affectation_bouton_value_is[iCatPageis][bt]-1;
             dock_selected_for_record=dock_selected_is;
              index_do_modify_on_faders=1;
               index_ask_confirm=1;
                }

  //clear
   else if(index_main_clear==1 )
    {
     fader_selected_for_record=iCat_affectation_bouton_value_is[iCatPageis][bt]-1;
      dock_selected_for_record=dock_selected_is;
       index_do_clear_dock=1;
       index_ask_confirm=1;
       }
      reset_button(iCatPageis,bt, tp);
      break;
      case 17://"Unselect All");
      for(int tt=0;tt<48;tt++)
      {
       minifaders_selected[tt]=0;
      }
      sprintf(string_Last_Order,"Minifaders ALL UNselected");
      break;
      case 18://"Select All");
      for(int tt=0;tt<48;tt++)
      {
       minifaders_selected[tt]=1;
      }
      sprintf(string_Last_Order,"Minifaders ALL SELected");
      break;
      case 19://"Select M.Fader Pst");
      if(iCat_affectation_bouton_value_is[iCatPageis][bt]-1 >=0 && iCat_affectation_bouton_value_is[iCatPageis][bt]-1<8)
      {
      for(int olp=0;olp<48;olp++)
      {minifaders_selected[olp]=minifaders_preset_selection[(iCat_affectation_bouton_value_is[iCatPageis][bt]-1)][olp];}
      }
      sprintf(string_Last_Order,"Minifaders Preset %d SELected",iCat_affectation_bouton_value_is[iCatPageis][bt]);
      reset_button(iCatPageis,bt, tp);
      break;
      case 20://locks presets
      do_lock_preset(iCat_affectation_bouton_value_is[iCatPageis][bt]-1);
      reset_button(iCatPageis,bt, tp);
      break;
default:
break;
}

do_action_on_selected_minifaders(action_minif);

break;
//////////////////////////////////////////////////////////////////////////////
case 3://sequenciel
reset_button(iCatPageis,bt, tp);  //reset pour eviter la frappe répétitive
if(before_check_button_state[bt]==0)
{
before_check_button_state[bt]=1;
switch(iCat_affectation_bouton_action_is[iCatPageis][bt])
     {
      case 1: //"GO");
      do_go_function();
      if(index_go==1 && index_pause==0)
      {
      do_send_bang();
      }
      reset_button(iCatPageis,bt, tp);
      break;
      case 2://"GO BACK");
      do_go_back_function();
      banger_back_is=Banger_Memoire[position_preset]-1;
      do_go_back_bang(banger_back_is);
      reset_button(iCatPageis,bt, tp);
      break;
      case 3://"JUMP");
      do_double_go_function();
      if(index_go==1 && index_pause==0)
      {
      do_send_bang();
      }
      reset_button(iCatPageis,bt, tp);
      break;
      case 4://"STAGE -");
      if(index_go==0 && index_go_back==0 && index_pause==0)
           {
           position_onstage=mem_before_one;
           }
           else {index_go=0;index_pause=0; index_go_back=0;}

           refresh_mem_onstage(position_onstage);
           detect_mem_before_one();
           detect_mem_preset();
           refresh_mem_onpreset(position_preset);
           niveauX1=255; niveauX2=0;
           refresh_banger_wx();
      reset_button(iCatPageis,bt, tp);
      someone_changed_in_sequences=1;
      break;
      case 5://"STAGE +");
      if(index_go==0 && index_go_back==0 && index_pause==0)
           {
           position_onstage=position_preset;
           }
            else {index_go=0;index_pause=0; index_go_back=0;}

           refresh_mem_onstage(position_onstage);
           detect_mem_before_one();
           detect_mem_preset();
           refresh_mem_onpreset(position_preset);
           niveauX1=255; niveauX2=0;
           refresh_banger_wx();
      reset_button(iCatPageis,bt, tp);
      someone_changed_in_sequences=1;
      break;
      case 6://"PRESET -");
      index_go=0;index_pause=0; index_go_back=0;
      detect_mem_preset_previous();
      refresh_mem_onpreset(position_preset);
      niveauX2=0;
      reset_button(iCatPageis,bt, tp);
      someone_changed_in_sequences=1;
      break;
      case 7://"PRESET +");
      index_go=0;index_pause=0; index_go_back=0;
      detect_next_preset();
      refresh_mem_onpreset(position_preset);
      niveauX2=0;
      reset_button(iCatPageis,bt, tp);
      someone_changed_in_sequences=1;
      break;
      case 8://GOTO
      if(numeric_postext>0)
      {
      if(MemoiresExistantes[(int)(atof(numeric)*10)]==1)
      {
      position_preset=(int)(atof(numeric)*10);
      refresh_mem_onpreset(position_preset);
      reset_numeric_entry();
      numeric_postext=0;
            reset_button(iCatPageis,bt, tp);
      someone_changed_in_sequences=1;
      }
      }
      break;
default:
break;
}
}
break;
//fin sequenciel
//////////////////////////////////////////////////////////////////////////////
case 4:
//emulate
clear_keybuf();
reset_button(iCatPageis,bt, tp);  //reset pour eviter la frappe répétitive
if(before_check_button_state[bt]==0)
{
before_check_button_state[bt]=1;
     switch(iCat_affectation_bouton_action_is[iCatPageis][bt])
     {
      case 0://"0");
      simulate_keypress(KEY_0 << 8);
      break;
      case 1://"1");
      simulate_keypress(KEY_1 << 8);
      break;
      case 2://"2");
      simulate_keypress(KEY_2 << 8);
      break;
      case 3://"3");
      simulate_keypress(KEY_3 << 8);
      break;
      case 4://"4");
      simulate_keypress(KEY_4 << 8);
      break;
      case 5://"5");
      simulate_keypress(KEY_5 << 8);
      break;
      case 6://"6");
      simulate_keypress(KEY_6 << 8);
      break;
      case 7://"7");
      simulate_keypress(KEY_7 << 8);
      break;
      case 8://"8");
      simulate_keypress(KEY_8 << 8);
      break;
      case 9://"9");
      simulate_keypress(KEY_9 << 8);
      break;
      case 10://".");
      simulate_keypress(KEY_COMMA<< 8);
      break;
      case 11://"PLUS");
      simulate_keypress(KEY_PLUS_PAD << 8);
      break;
      case 12://"MINUS");
      simulate_keypress(KEY_MINUS << 8);
      break;
      case 13://"ALL");
      simulate_keypress(KEY_Y << 8);
      break;
      case 14://"INV");
      simulate_keypress(KEY_U << 8);
      break;
      case 15://"TAB");
      simulate_keypress(KEY_TAB << 8);
      break;
      case 16://"ESC");
      simulate_keypress(KEY_ESC << 8);
      break;
      case 17://"ENT");
      simulate_keypress(KEY_ENTER << 8);
      break;
      case 18://FULL
      simulate_keypress(KEY_I << 8);
      break;
      case 19://a ZERO
      simulate_keypress(KEY_O << 8);
      break;
      case 20://backspace
      simulate_keypress(KEY_BACKSPACE << 8);
      break;
      case 21://DEL
      simulate_keypress(KEY_DEL << 8);
      break;
      case 22://arrow Up
      simulate_keypress(KEY_UP << 8);
      break;
      case 23://arrow down
      simulate_keypress(KEY_DOWN << 8);
      break;
      case 24://arrow left
      simulate_keypress(KEY_LEFT << 8);
      break;
      case 25://arrow right
      simulate_keypress(KEY_RIGHT << 8);
      break;
      case 26://"F1");
      simulate_keypress(KEY_F1 << 8);
      break;
      case 27://"F2");
      simulate_keypress(KEY_F2 << 8);
      break;
      case 28://"F3");
      simulate_keypress(KEY_F3 << 8);
      break;
      case 29://"F4");
      simulate_keypress(KEY_F4 << 8);
      break;
      case 30://"F11");
      simulate_keypress(KEY_F11 << 8);
      break;
      case 31://"F12");
      simulate_keypress(KEY_F12 << 8);
      break;
      case 32://"SHFT");
      index_false_shift=  toggle(index_false_shift);
      index_false_control=0;
      break;
      case 33://"CTRL");
      index_false_control=  toggle(index_false_control);
      index_false_shift=0;
      break;
      default://
      break;
     }

reset_button(iCatPageis,bt, tp);
}
break;
//fin emulate
case 5://banger


bangeriCat=iCat_affectation_bouton_value_is[iCatPageis][bt]-1;

if( bangeriCat>=0 && bangeriCat<127  )
{
bang_is_sended[bangeriCat]=toggle(bang_is_sended[bangeriCat]);
switch (bang_is_sended[bangeriCat])
{
case 0://reset des send events et on demarre à la souris le banger
  for (int y=0;y<6;y++){event_sended[bangeriCat][y]=0;}
  start_time_for_banger[bangeriCat]=actual_time;
//calcul bang time de fin
for (int y=0;y<6;y++)
{
if(bangers_delay[bangeriCat][y]> end_time_for_banger[bangeriCat])
{
end_time_for_banger[bangeriCat]= bangers_delay[bangeriCat][y];
}
}
if(end_time_for_banger[bangeriCat]<default_time_of_the_bang)
{end_time_for_banger[bangeriCat]=default_time_of_the_bang;}
last_banger_sended_manually=bangeriCat;
reset_button(iCatPageis,bt, tp);
break;
case 1://go back sur le banger
for (int y=0;y<6;y++)
{
if(bangers_type[bangeriCat][y]!=0 )
{
    Bang_event_back(bangeriCat, y);
    event_sended[bangeriCat][y]=1;
}
}
bang_is_sended[bangeriCat]=1;//bloquage de l envoi des autres évènements
reset_button(iCatPageis,bt, tp);
break;
default:
break;
}
}

break;

case 6://icat commandes
if(finished_to_send_orders_to_iCat==1)
{
      switch(iCat_affectation_bouton_action_is[iCatPageis][bt])
     {
      case 1://page --
      reset_button(iCatPageis,bt, tp); //avant car on reset la donnée du bouton par icatpageis !
      iCatPageis--;
      if(iCatPageis<0)
      {
      iCatPageis=7;
      }
      init_iCat_data();
      load_iCat_page(iCatPageis);
      do_send_icat_init_page=1;

      /*nbrbytessendediCat=sendto(sockiCat, "clearmodels",sizeof("clearmodels"),0,(SOCKADDR*)&siniCat,sinsizeiCat); //dans routine laod avant appel du rafraichissement
      do_refresh_iCat(iCatPageis);*/

      break;
      case 2://page ++
      reset_button(iCatPageis,bt, tp);
      iCatPageis++;
      if(iCatPageis>7)
      {
      iCatPageis=0;
      }
      init_iCat_data();
      load_iCat_page(iCatPageis);
      do_send_icat_init_page=1;

      /*nbrbytessendediCat=sendto(sockiCat, "clearmodels",sizeof("clearmodels"),0,(SOCKADDR*)&siniCat,sinsizeiCat); //dans routine laod avant appel du rafraichissement
      do_refresh_iCat(iCatPageis);*/

      break;
      case 3://page num
      reset_button(iCatPageis,bt, tp);
  //    if(iCat_affectation_bouton_value_is[iCatPageis][bt]>0 && iCat_affectation_bouton_value_is[iCatPageis][bt]<9)
  //

      iCatPageis=iCat_affectation_bouton_value_is[iCatPageis][bt]-1;
      iCatPageis=constrain_int_data_to_this_range(iCatPageis,0,7);
      init_iCat_data();
      load_iCat_page(iCatPageis);
      do_send_icat_init_page=1;

      break;
      case 4: //refresh
      reset_button(iCatPageis,bt, tp);
      do_refresh_iCat(iCatPageis);
      break;
      case 5://page Orientation
      reset_button(iCatPageis,bt, tp);
      iCat_preset_orientation[iCatPageis]++;
      if(iCat_preset_orientation[iCatPageis]>2){iCat_preset_orientation[iCatPageis]=0;}
      do_refresh_iCat(iCatPageis);
      break;
      default:
      break;
      }
}
//fin commandes iCat
break;
case 7://DRAW
//     reset_button(iCatPageis,bt, tp);

      switch(iCat_affectation_bouton_action_is[iCatPageis][bt])
      {
      case 1://"Brush Type" selected
      draw_brush_type[draw_preset_selected]=toggle(draw_brush_type[draw_preset_selected]);
      reset_button(iCatPageis,bt, tp);
      break;
      case 2://draw_mode selected
      draw_mode[draw_preset_selected]++;
      if(draw_mode[draw_preset_selected]>3){draw_mode[draw_preset_selected]=0;}
      reset_button(iCatPageis,bt, tp);
      break;
      case 3://"Brush Type" par valeur de matrice
      draw_brush_type[(iCat_affectation_bouton_value_is[iCatPageis][bt]-1)]=toggle(draw_brush_type[(iCat_affectation_bouton_value_is[iCatPageis][bt]-1)]);
      reset_button(iCatPageis,bt, tp);
      break;
      case 4://draw_mode par valeur de matrice
      draw_mode[(iCat_affectation_bouton_value_is[iCatPageis][bt]-1)]++;
      if(draw_mode[(iCat_affectation_bouton_value_is[iCatPageis][bt]-1)]>3){draw_mode[(iCat_affectation_bouton_value_is[iCatPageis][bt]-1)]=0;}
      reset_button(iCatPageis,bt, tp);
      break;
      case 5://preset matrix
      draw_preset_selected=(iCat_affectation_bouton_value_is[iCatPageis][bt]-1);
      recalculate_draw_sizes(draw_preset_selected);
      reset_button(iCatPageis,bt, tp);
      break;
      default:
      break;
      }
break;
default:
break;
}
/*fsBx=-999;
fsBy=-999;
fsMx=-999;
fsMy=-999;
fsEx=-999;
fsEy=-999;
fsTestX2=-999; fsTestY2=-999;        */
}

//relachement de boutons pour les flashs previous pour laisser la souris agir
else if(button_is_touched[iCatPageis][bt]==0 && previous_button_is_touched[iCatPageis][bt]==1 && button_is_controlled_by_point[iCatPageis][bt]==tp )
{
//flash fader solo
if(iCat_affectation_bouton_type_is[iCatPageis][bt]==1 && iCat_affectation_bouton_action_is[iCatPageis][bt]==8)
{
FaderIsFlash[iCat_affectation_bouton_value_is[iCatPageis][bt]-1] =0;
}
//flash minifaders
if(iCat_affectation_bouton_type_is[iCatPageis][bt]==2 && iCat_affectation_bouton_action_is[iCatPageis][bt]==8)
{
for(int tt=0;tt<47;tt++)
      {
      if( minifaders_selected[tt]==1 && FaderIsFlash[tt]==1 )
      {FaderIsFlash[tt]=0;}
      }
}
reset_button(iCatPageis,bt, tp);
}
//pour le flash
previous_button_is_touched[iCatPageis][bt]=button_is_touched[iCatPageis][bt];
}


return(0);
}



int check_slider( int tp)
{
int fsBx=FS_touch_point_begin[0][tp];
int fsBy=FS_touch_point_begin[1][tp];
int fsMx=FS_touch_point_move[0][tp];
int fsMy=FS_touch_point_move[1][tp];
//sab 02/03/2014 unused var int fsEx=FS_touch_point_end[0][tp];
//sab 02/03/2014 unused var int fsEy=FS_touch_point_end[1][tp];

int fsTestX2=0; int fsTestY2=0;

for(int sl=1;sl<iCat_nbre_de_sliders[iCatPageis]+1;sl++)
{
switch (iCat_orientation_slider[iCatPageis][sl])
{
case 0:
fsTestX2=(iCat_pos_slider[iCatPageis][sl][0]*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][sl]);
fsTestY2=(iCat_pos_slider[iCatPageis][sl][1]*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][sl]);
break;
case 1:
fsTestX2=(iCat_pos_slider[iCatPageis][sl][0]*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][sl]);
fsTestY2=(iCat_pos_slider[iCatPageis][sl][1]*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][sl]);
break;
default: break;
}
if ( fsBx>=(iCat_pos_slider[iCatPageis][sl][0]*2)-10 && fsBx<=fsTestX2+10 && fsBy>=(iCat_pos_slider[iCatPageis][sl][1]*2)-10 && fsBy<=fsTestY2+10 )
{
slider_is_touched[iCatPageis][sl]=1;
slider_is_controlled_by_point[iCatPageis][sl]=tp;
}
if(slider_is_touched[iCatPageis][sl]==1 && slider_is_controlled_by_point[iCatPageis][sl]==tp)
{
switch (iCat_orientation_slider[iCatPageis][sl])
{
case 0://vertical
level_from_touch[iCatPageis][sl]=(iCat_pos_slider[iCatPageis][sl][1]*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][sl])-fsMy;
break;
case 1://horizontal
level_from_touch[iCatPageis][sl]=fsMx-(iCat_pos_slider[iCatPageis][sl][0]*2);
break;
default: break;
}
//level_from_touch[iCatPageis][sl]=(level_from_touch[iCatPageis][sl]/3)*ratio_iCat_slider[iCatPageis][sl];
switch(ratio_iCat_slider[iCatPageis][sl])
{
case 1:
level_from_touch[iCatPageis][sl]*=2;
break;
case 3:
level_from_touch[iCatPageis][sl]=(level_from_touch[iCatPageis][sl]/3)*2;
break;
default:
break;
}
level_from_touch[iCatPageis][sl]=constrain_data_to_dmx_range(level_from_touch[iCatPageis][sl]);

//repartition du niveau
switch(iCat_affectation_slider_type_is[iCatPageis][sl])
{
case 1://niveaux faders
    fader_set_level((iCat_affectation_slider_value_is[iCatPageis][sl]-1),level_from_touch[iCatPageis][sl]);
/*Fader[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=level_from_touch[iCatPageis][sl];
index_fader_is_manipulated[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=1;
midi_levels[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]==1){ index_send_midi_out[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=1;}
*/
if(lfo_mode_is[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]==1 || lfo_mode_is[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]==2 || lfo_cycle_is_on[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]==1)
{
lfo_mode_is[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=0;
lfo_mode_is[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=0;
lfo_cycle_is_on[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=0;

}

break;
case 2://speed accelerometre faders
lfo_speed[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=level_from_touch[iCatPageis][sl]/2;

index_send_midi_out[196+(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=1;

if(DockTypeIs[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)][dock_used_by_fader_is[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]]==12)//enchassement Grid si slave
{
asservissement_gridplayer((iCat_affectation_slider_value_is[iCatPageis][sl]-1),dock_used_by_fader_is[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]);
}
midi_levels[196+(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=lfo_speed[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)];

break;
case 3://sequenciel 0: stage 1: preset 2: accelerometre
     switch(iCat_affectation_slider_value_is[iCatPageis][sl])
     {
     case 0://sx1
     index_go=0; index_go_back=0; index_pause=0;
     niveauX1=level_from_touch[iCatPageis][sl];
     iCat_slider_doing_X1_is=sl;
     midi_levels[491]=level_from_touch[iCatPageis][sl]/2;
     if(midi_send_out[491]==1){ index_send_midi_out[491]=1;}

     break;
     case 1://x2
     index_go=0; index_go_back=0; index_pause=0;
     niveauX2=255-level_from_touch[iCatPageis][sl];
     iCat_slider_doing_X2_is=sl;
     midi_levels[492]=127-(level_from_touch[iCatPageis][sl]/2);
     if(midi_send_out[492]==1){ index_send_midi_out[492]=1;}

     break;
     case 2:
     crossfade_speed= level_from_touch[iCatPageis][sl]/2;
     prepare_crossfade();
     if(crossfade_speed<0){crossfade_speed=0;}
     if(crossfade_speed>127){crossfade_speed=127;}
     midi_levels[493]=level_from_touch[iCatPageis][sl];
     if(midi_send_out[493]==1){ index_send_midi_out[493]=1;}

    //rafraichissement seq non uniquement en release sinon ca bloque
     break;
     default:
     break;
     }

break;
case 4://grand master
if(index_allow_grand_master==1)
{
niveauGMaster=level_from_touch[iCatPageis][sl];
if(niveauGMaster<0){niveauGMaster=0;}
if(niveauGMaster>255){niveauGMaster=255;}
midi_levels[615]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[615]==1){ index_send_midi_out[615]=1;}
}
break;
case 5://level wheel
if(wheellevel_absolutemode==1)//mode absolu
{
int levelwheelis=level_from_touch[iCatPageis][sl];
if(levelwheelis<0){levelwheelis=0;}
if(levelwheelis>255){levelwheelis=255;}
for (int tc=1;tc<514;tc++)
{
if (Selected_Channel[tc]==1 && index_blind==0)
{
bufferSaisie[tc]=levelwheelis;
}
else if (Selected_Channel[tc]==1 && index_blind==1)
{
bufferBlind[tc]=levelwheelis;
}
}
absolute_level_wheel=levelwheelis;

midi_levels[664]=levelwheelis/2;
if(midi_send_out[664]==1){index_send_midi_out[664]=1;}
}
break;

case 6://MOVER
if( tracker_16b_edit==0)
{
mover_params[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)][0]=level_from_touch[iCatPageis][sl];
}
else
{
mover_params[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)][1]=level_from_touch[iCatPageis][sl];
}
midi_levels[1700+(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[1700+(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]==1){ index_send_midi_out[1700+(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=1;}
break;

case 7: //DRAW PRESSURE
draw_level_to_do[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=((float)(level_from_touch[iCatPageis][sl])/2)/127.0;
if((iCat_affectation_slider_value_is[iCatPageis][sl]-1)==draw_preset_selected)
{
midi_levels[1653]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[1653]==1){ index_send_midi_out[1653]=1;}
}
break;
case 8: //DRAW decay
draw_damper_decay_factor[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=((float)(level_from_touch[iCatPageis][sl])/2)/127.0;
if((iCat_affectation_slider_value_is[iCatPageis][sl]-1)==draw_preset_selected)
{
midi_levels[1654]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[1654]==1){ index_send_midi_out[1654]=1;}
}
break;
case 9: //DRAW GHOST
draw_ghost_to_do[(iCat_affectation_slider_value_is[iCatPageis][sl]-1)]=((float)(level_from_touch[iCatPageis][sl])/2)/127.0;
if((iCat_affectation_slider_value_is[iCatPageis][sl]-1)==draw_preset_selected)
{
midi_levels[1656]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[1656]==1){ index_send_midi_out[1656]=1;}
}
break;
case 10: //DRAW PRESSURE SELECTED
draw_level_to_do[draw_preset_selected]=((float)(level_from_touch[iCatPageis][sl])/2)/127.0;
midi_levels[1653]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[1653]==1){ index_send_midi_out[1653]=1;}
break;
case 11: //DRAW DECAY
draw_damper_decay_factor[draw_preset_selected]=((float)(level_from_touch[iCatPageis][sl])/2)/127.0;
midi_levels[1654]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[1654]==1){ index_send_midi_out[1654]=1;}
break;
case 12: //DRAW GHOST
draw_ghost_to_do[draw_preset_selected]=((float)(level_from_touch[iCatPageis][sl])/2)/127.0;
midi_levels[1656]=level_from_touch[iCatPageis][sl]/2;
if(midi_send_out[1656]==1){ index_send_midi_out[1656]=1;}
break;

default:
break;
}

}


//verif du crossfade done après les checks de touchs, important à garder hors de sswitch cases
if(niveauX1==0 && niveauX2==255
   && slider_is_touched[iCatPageis][iCat_slider_doing_X1_is]==0 &&  slider_is_touched[iCatPageis][iCat_slider_doing_X2_is]==0)
{
     index_go=0; index_go_back=0; index_pause=0;
     next_mem_crossfade_finished(position_preset);
     niveauX1=255; niveauX2=0;floatX1=niveauX1; floatX2=niveauX2;
     crossfade_speed=64;
     crossfade_done_time=0;
     midi_levels[491]=127; midi_levels[492]=127;midi_levels[493]=crossfade_speed;
     if(midi_send_out[491]==1){ index_send_midi_out[491]=1;}
     if(midi_send_out[492]==1){ index_send_midi_out[492]=1;}
     if(midi_send_out[493]==1){ index_send_midi_out[493]=1;}
     index_x1_x2_together=1;
}

//affichage du touch
if(slider_is_touched[iCatPageis][sl]!=before_slider_is_touched[iCatPageis][sl])
{
switch(slider_is_touched[iCatPageis][sl])
{
case 0:
sprintf(StrOrderToiCat, "model t%d color 1.0 1.0 1.0",sl);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1:
sprintf(StrOrderToiCat, "model t%d color 1.0 0.0 0.0",sl);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
}
before_slider_is_touched[iCatPageis][sl]=slider_is_touched[iCatPageis][sl];
}
return(0);
}




int check_tracker_zone( int tp)
{
int fsBx=FS_touch_point_begin[0][tp];
int fsBy=FS_touch_point_begin[1][tp];
int fsMx=FS_touch_point_move[0][tp];
int fsMy=FS_touch_point_move[1][tp];
int fsEx=FS_touch_point_end[0][tp];
int fsEy=FS_touch_point_end[1][tp];

int fsTestX2=0; int fsTestY2=0;

for(int sl=1;sl< iCat_nbre_de_tracking_zone[iCatPageis]+1;sl++)
{

fsTestX2=(iCat_pos_trackzone[iCatPageis][sl][0]*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
fsTestY2=(iCat_pos_trackzone[iCatPageis][sl][1]*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);


if ( fsBx>=(iCat_pos_trackzone[iCatPageis][sl][0]*2)-10 && fsBx<=fsTestX2+10 && fsBy>=(iCat_pos_trackzone[iCatPageis][sl][1]*2)-10 && fsBy<=fsTestY2+10 )
{
zone_is_touched[iCatPageis][sl]=1;
zone_is_controlled_by_point[iCatPageis][sl]=tp;
}



if((fsMx==fsEx && fsMy==fsEy) || (fsBx==fsEx && fsBy==fsEy) )//pour la relache n egale pas 0
{
zone_is_touched[iCatPageis][sl]=0;
if(dragging_draw==0 )//si pas de la souris
{
switch(iCat_trackzone_type_is[iCatPageis][sl])
{
case 2://draw activ
  draw_point_is_traced[draw_preset_selected]=0;
break;
case 3://draw specific num
 draw_point_is_traced[iCat_trackzone_affectation_is[iCatPageis][sl]-1]=0;
break;
default:
break;
}
}

}


if(zone_is_touched[iCatPageis][sl]==1 && zone_is_controlled_by_point[iCatPageis][sl]==tp)
{
int pr=0;
float ratiox=0.0;
float ratioy=0.0;

switch(iCat_trackzone_type_is[iCatPageis][sl])
{
case 1://MOVER

index_move_crossfade_is_on=0;
index_move_crossfade_is_on=0;
index_move_back=0;
index_move_forward=0;
if(lockX_on==0 )
{
pos_iCat_tracker[iCatPageis][sl][0]=(iCat_pos_trackzone[iCatPageis][sl][0]*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl])-fsMx;
switch(ratio_iCat_trackzone[iCatPageis][sl])
{
case 1: //small
pos_iCat_tracker[iCatPageis][sl][0]*=2;
break;
//case 2: //ratio 1. pas touche
//break:
case 3: //big
pos_iCat_tracker[iCatPageis][sl][0]=(pos_iCat_tracker[iCatPageis][sl][0]/3)*2;
break;
case 4: //BIG
pos_iCat_tracker[iCatPageis][sl][0]=(int)(pos_iCat_tracker[iCatPageis][sl][0]/2);
break;
default:
break;
}
pos_iCat_tracker[iCatPageis][sl][0]=constrain_data_to_dmx_range(pos_iCat_tracker[iCatPageis][sl][0]);
mover_params[0][0]=255-pos_iCat_tracker[iCatPageis][sl][0];
}

if(lockY_on==0 )
{
pos_iCat_tracker[iCatPageis][sl][1]=(iCat_pos_trackzone[iCatPageis][sl][1]*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl])-fsMy;
switch(ratio_iCat_trackzone[iCatPageis][sl])
{
case 1: //small
pos_iCat_tracker[iCatPageis][sl][1]*=2;
break;
case 3:    //big
pos_iCat_tracker[iCatPageis][sl][1]=(pos_iCat_tracker[iCatPageis][sl][1]/3)*2;
break;
case 4: //BIG
pos_iCat_tracker[iCatPageis][sl][1]=(int)(pos_iCat_tracker[iCatPageis][sl][1]/2);
break;
default:
break;
}
pos_iCat_tracker[iCatPageis][sl][1]=constrain_data_to_dmx_range(pos_iCat_tracker[iCatPageis][sl][1]);
mover_params[1][0]=255-pos_iCat_tracker[iCatPageis][sl][1];
}
break;
case 2://draw activ

if(iCat_preset_orientation[iCatPageis]==0)
   {
    ratiox=((float)draw_tracking_aera_size_y)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
    ratioy=((float)draw_tracking_aera_size_x)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
   }
   else
   {
   ratiox=((float)draw_tracking_aera_size_x)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
   ratioy=((float)draw_tracking_aera_size_y)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
   }

pos_iCat_tracker[iCatPageis][sl][0]=(int)((fsMx-(iCat_pos_trackzone[iCatPageis][sl][0]*2))*ratiox);
pos_iCat_tracker[iCatPageis][sl][1]=(int)((fsMy-(iCat_pos_trackzone[iCatPageis][sl][1]*2))*ratioy);

pos_iCat_tracker[iCatPageis][sl][0]=constrain_int_data_to_this_range(pos_iCat_tracker[iCatPageis][sl][0], 0,draw_tracking_aera_size_x );
pos_iCat_tracker[iCatPageis][sl][1]=constrain_int_data_to_this_range(pos_iCat_tracker[iCatPageis][sl][1], 0,draw_tracking_aera_size_y );

pr=draw_preset_selected;

if(pos_iCat_tracker[iCatPageis][sl][0]>(draw_largeur_case[pr]*draw_preset_parameters[pr][0]))
{pos_iCat_tracker[iCatPageis][sl][0]=(draw_largeur_case[pr]*draw_preset_parameters[pr][0])-1;}
if(pos_iCat_tracker[iCatPageis][sl][1]>(draw_hauteur_case[pr]*draw_preset_parameters[pr][1]))
{pos_iCat_tracker[iCatPageis][sl][1]=(draw_hauteur_case[pr]*draw_preset_parameters[pr][1])-1;}

if( ticks_dixieme_for_icat_and_draw!=before_ticks_dixieme_for_icat_and_draw)
{
draw_point_is_traced[pr]=1;
Draw_point_and_perform_level_on_area_NEW(draw_preset_selected,pos_iCat_tracker[iCatPageis][sl][0],pos_iCat_tracker[iCatPageis][sl][1]);
before_ticks_dixieme_for_icat_and_draw=ticks_dixieme_for_icat_and_draw;
}
break;
case 3://draw num
if(iCat_preset_orientation[iCatPageis]==0)
   {
    ratiox=((float)draw_tracking_aera_size_y)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
    ratioy=((float)draw_tracking_aera_size_x)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
   }
   else
   {
   ratiox=((float)draw_tracking_aera_size_x)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
   ratioy=((float)draw_tracking_aera_size_y)/(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][sl]);
   }

pos_iCat_tracker[iCatPageis][sl][0]=(int)((fsMx-(iCat_pos_trackzone[iCatPageis][sl][0]*2))*ratiox);
pos_iCat_tracker[iCatPageis][sl][1]=(int)((fsMy-(iCat_pos_trackzone[iCatPageis][sl][1]*2))*ratioy);


pos_iCat_tracker[iCatPageis][sl][0]=constrain_int_data_to_this_range(pos_iCat_tracker[iCatPageis][sl][0], 0,draw_tracking_aera_size_x);
pos_iCat_tracker[iCatPageis][sl][1]=constrain_int_data_to_this_range(pos_iCat_tracker[iCatPageis][sl][1], 0,draw_tracking_aera_size_y);

pr=iCat_trackzone_affectation_is[iCatPageis][sl]-1;

if(pos_iCat_tracker[iCatPageis][sl][0]>(draw_largeur_case[pr]*draw_preset_parameters[pr][0]))
{pos_iCat_tracker[iCatPageis][sl][0]=(draw_largeur_case[pr]*draw_preset_parameters[pr][0])-1;}
if(pos_iCat_tracker[iCatPageis][sl][1]>(draw_hauteur_case[pr]*draw_preset_parameters[pr][1]))
{pos_iCat_tracker[iCatPageis][sl][1]=(draw_hauteur_case[pr]*draw_preset_parameters[pr][1])-1;}

if( ticks_dixieme_for_icat_and_draw!=before_ticks_dixieme_for_icat_and_draw)
{
draw_point_is_traced[pr]=1;
Draw_point_and_perform_level_on_area_NEW(draw_preset_selected,pos_iCat_tracker[iCatPageis][sl][0],pos_iCat_tracker[iCatPageis][sl][1]);
before_ticks_dixieme_for_icat_and_draw=ticks_dixieme_for_icat_and_draw;
}
break;
default:
break;
}
//zone touchee end
}




//fin check zones
}

return(0);
}




int DoJobFantastickTouch()
{

for(int tp=0;tp<fs_max_points+1;tp++)//nbre detectes virés, car si on lache un potard en cours on est plus au nombre de points limités en pos
{
check_button(tp);     //d'abord les boutons pou éviter d avoir des blocages avec les sliders
check_slider(tp);
check_tracker_zone(tp);
}

return(0);
}


int ReceiveFantastick()
{
if(fantastick_message[0]=='I' &&  fantastick_message[1] =='P')
{
 fantastick_message[bytesreceivediCat]='\0';
 sprintf(FS_IP,fantastick_message);
}


int fsid=0, fsx=0, fsy=0;

     if( fantastick_message[0]=='M' ||  fantastick_message[0]=='B' ||  fantastick_message[0]=='E'
     || fantastick_message[0]=='S'
     || fantastick_message[0]=='A' ||  fantastick_message[0]=='X')
     {
      fantastick_message[bytesreceivediCat]='\0';
      sprintf(FS_BUFFER,fantastick_message);
      switch( fantastick_message[0])
      {
      case 'A':
      sscanf(FS_BUFFER,"A %f %f %f",&fs_accelerometer[0],&fs_accelerometer[1],&fs_accelerometer[2]);
      break;

      case 'B':
      sscanf(FS_BUFFER,"B %d %d %d",&fsx, &fsy, &fsid);
      FS_touch_point_begin[0][fsid-1]=fsx;
      FS_touch_point_begin[1][fsid-1]=fsy;
      FS_touch_point_move[0][fsid-1]=fsx;
      FS_touch_point_move[1][fsid-1]=fsy;
      break;
      case 'M':
      sscanf(FS_BUFFER,"M %d %d %d",&fsx, &fsy, &fsid);
      FS_touch_point_move[0][fsid-1]=fsx;
      FS_touch_point_move[1][fsid-1]=fsy;
      break;
      case 'S':
      sscanf(FS_BUFFER,"S %d %d %d",&fsx, &fsy, &fsid);
      FS_touch_point_stationnary[0][fsid-1]=fsx;
      FS_touch_point_stationnary[1][fsid-1]=fsy;
      break;
      case 'E':
      sscanf(FS_BUFFER,"E %d %d %d",&fsx, &fsy, &fsid);
      FS_touch_point_end[0][fsid-1]=fsx;
      FS_touch_point_end[1][fsid-1]=fsy;
      for(int t=0;t<iCat_nbre_de_sliders[iCatPageis]+1;t++)
      {
      if(slider_is_controlled_by_point[iCatPageis][t]==fsid-1)
      {
      slider_is_touched[iCatPageis][t]=0;
      slider_is_controlled_by_point[iCatPageis][t]=0;
      //reset du touch
      FS_touch_point_begin[0][fsid-1]=-999;
      FS_touch_point_begin[1][fsid-1]=-999;
      FS_touch_point_move[0][fsid-1]=-999;
      FS_touch_point_move[1][fsid-1]=-999;
      }
      }
      break;
      case 'X':
      sscanf(FS_BUFFER,"X %d",&nbre_icat_points_detectes);
      if(nbre_icat_points_detectes==0)
      {
      for(int p=0;p<fs_max_points+1;p++)
      {
      FS_touch_point_begin[0][p]=-999;
      FS_touch_point_begin[1][p]=-999;
      FS_touch_point_move[0][p]=-999;
      FS_touch_point_move[1][p]=-999;
      FS_touch_point_end[0][p]=-999;
      FS_touch_point_end[1][p]=-999;
      }
      }

      before_nbre_icat_points_detectes=nbre_icat_points_detectes;
      break;
      default: break;
      }
     }


 return(0);
}
