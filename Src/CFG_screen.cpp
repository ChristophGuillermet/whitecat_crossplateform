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

* \file CFG_screen.cpp
* \brief {config GUI file}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gère les fonction de la fenetre cfg menu
*
*   GUI fonction of the windows cfg menu
*
 **/


int reload_window_positions()
{

//the_window_text_x
//the_window_text_y=windows_position[0][1];
xpatch_window=windows_position[1][0];
ypatch_window=windows_position[1][1];
xtime_window=windows_position[2][0];
ytime_window=windows_position[2][1];
xseq_window=windows_position[3][0];
yseq_window=windows_position[3][1];
xtrichro_window=windows_position[4][0];
ytrichro_window=windows_position[4][1];
xnum_window=windows_position[5][0];
ynum_window=windows_position[5][1];
videoX=windows_position[6][0];
videoY=windows_position[6][1];
//scroll_faderspace=(float)windows_position[7][0];
YFader=windows_position[7][1];
XAudio=windows_position[8][0];
YAudio=windows_position[8][1];
XGConfig=windows_position[9][0];
YGConfig=windows_position[9][1];
XConfirm=windows_position[10][0];
YConfirm=windows_position[10][1];

grider_window_x=windows_position[11][0];
//sab 02/03/2014 ATTENTION IMPACT - COMMENT CONTROLER FONCTION ? grider_window_y==windows_position[11][1];
grider_window_y=windows_position[11][1];

x_plot=windows_position[12][0];
y_plot=windows_position[12][1];

window_cfgX=windows_position[13][0];
window_cfgY=windows_position[13][1];
Xwizard=windows_position[14][0];
Ywizard=windows_position[14][1];
xMinifaders=windows_position[15][0];
//sab 02/03/2014 ATTENTION IMPACT - COMMENT CONTROLER FONCTION ? yMinifaders==windows_position[15][1];
yMinifaders=windows_position[15][1];

Xchasers=windows_position[16][0];
Ychasers=windows_position[16][1];
xmover_window=windows_position[17][0];
ymover_window=windows_position[17][1];
X_gui_iCat= windows_position[18][0];
Y_gui_iCat= windows_position[18][1];

return(0);
}

int store_window_positions()
{
//windows_position[0][0]=the_window_text_x;
//windows_position[0][1]=the_window_text_y;
windows_position[1][0]=xpatch_window;
windows_position[1][1]=ypatch_window;
windows_position[2][0]=xtime_window;
windows_position[2][1]=ytime_window;
windows_position[3][0]=xseq_window;
windows_position[3][1]=yseq_window;
windows_position[4][0]=xtrichro_window;
windows_position[4][1]=ytrichro_window;
windows_position[5][0]=xnum_window;
windows_position[5][1]=ynum_window;
windows_position[6][0]=videoX;
windows_position[6][1]=videoY;
//windows_position[7][0]=(int)scroll_faderspace;
windows_position[7][1]=YFader;
windows_position[8][0]=XAudio;
windows_position[8][1]=YAudio;
windows_position[9][0]=XGConfig;
windows_position[9][1]=YGConfig;
windows_position[10][0]=XConfirm;
windows_position[10][1]=YConfirm;

windows_position[11][0]=grider_window_x;
windows_position[12][1]=grider_window_y;
windows_position[12][0]=x_plot;
windows_position[12][1]=y_plot;

windows_position[13][0]=window_cfgX;
windows_position[13][1]=window_cfgY;
windows_position[14][0]=Xwizard;
windows_position[14][1]=Ywizard;
windows_position[15][0]=xMinifaders;
windows_position[15][1]=yMinifaders;
windows_position[16][0]=Xchasers;
windows_position[16][1]=Ychasers;
windows_position[17][0]=xmover_window;
windows_position[17][1]=ymover_window;
windows_position[18][0]=X_gui_iCat;
windows_position[18][1]=Y_gui_iCat;
return(0);
}



int do_screen_config( int x_cfg_sc,int y_cfg_sc, int largeur_cfg_sc, int hauteur_cfg_sc)
{
//////////////////SCREEN SIZE//////////////////////////////////////////////////
Rect EncadreScreen(Vec2D(x_cfg_sc+10,y_cfg_sc+40),Vec2D(200,230));
EncadreScreen.SetRoundness(7.5);
EncadreScreen.SetLineWidth(epaisseur_ligne_fader);

petitchiffre.Print("SIZE -need restart- " ,(x_cfg_sc+20), (y_cfg_sc+60));

for (int lps=0;lps<2;lps++)
{
Rect screen_mode(Vec2D( x_cfg_sc+20,y_cfg_sc+75+(lps*30)),Vec2D(55,15));
screen_mode.SetRoundness(5);
screen_mode.Draw(CouleurFond.WithAlpha(0.5));
//FULLSCREEN or WINDOWED
if(lps==0)
{
petitchiffre.Print("Fullscreen " ,(x_cfg_sc+85), y_cfg_sc+85+(lps*30));
if(mouse_x>x_cfg_sc+20 && mouse_x<x_cfg_sc+75 && mouse_y>y_cfg_sc+75+(lps*30) && mouse_y<y_cfg_sc+90+(lps*30)  && window_focus_id==920)
{
screen_mode.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
if(index_fullscreen==0) {index_fullscreen=1;index_specify_size=0;largeur_ecran= GetSystemMetrics(SM_CXVIRTUALSCREEN);
hauteur_ecran = GetSystemMetrics(SM_CYVIRTUALSCREEN);}
else if (index_fullscreen==1) {index_fullscreen=0;}
mouse_released=1;
}
}
if(index_fullscreen==1)
{screen_mode.Draw(CouleurFader);}
}

//SPECIFY SIZE
else if(lps==1)
{
petitchiffre.Print("Set new size: " ,(x_cfg_sc+85), y_cfg_sc+50+35+(lps*30));
if(mouse_x>x_cfg_sc+20 && mouse_x<x_cfg_sc+75 && mouse_y>y_cfg_sc+75+(lps*30) && mouse_y<y_cfg_sc+90+(lps*30)  && window_focus_id==920)
{
screen_mode.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
if(index_specify_size==0)
{
index_specify_size=1;
index_fullscreen=0;
}
else if (index_specify_size==1) {index_specify_size=0;}
mouse_released=1;
}
}
if(index_specify_size==1)
{screen_mode.Draw(CouleurFader);}
}

}


Rect boxlargeur(Vec2D((x_cfg_sc+100),y_cfg_sc+130),Vec2D(65,30));
boxlargeur.SetRoundness(7.5);
boxlargeur.Draw(CouleurFond.WithAlpha(0.5));


Rect boxhauteur(Vec2D((x_cfg_sc+100),y_cfg_sc+165),Vec2D(65,30));
boxhauteur.SetRoundness(7.5);
boxhauteur.Draw(CouleurFond.WithAlpha(0.5));

if(mouse_x>(x_cfg_sc+100) && mouse_x<(x_cfg_sc+165) && window_focus_id==920)
{
if(mouse_y> y_cfg_sc+130 && mouse_y<y_cfg_sc+160)
{
boxlargeur.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0 && index_specify_size==1)
{
if(atoi(numeric)>=1024)
{
largeur_ecran=atoi(numeric);
reset_numeric_entry();
}
else {sprintf(string_Last_Order,"Screen Width must be at minimum 1024 px");}
mouse_released=1;
}
}
if(mouse_y> y_cfg_sc+165 && mouse_y<y_cfg_sc+195)
{
boxhauteur.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0 && index_specify_size==1)
{
if(atoi(numeric)>=600)
{
hauteur_ecran=atoi(numeric);
reset_numeric_entry();
}
else {sprintf(string_Last_Order,"Screen Height must be at minimum 600 px");}
mouse_released=1;
}
}
}
petitchiffre.Print("Width: " ,(x_cfg_sc+40), y_cfg_sc+150);
petitchiffre.Print(ol::ToString(largeur_ecran) ,(x_cfg_sc+120), y_cfg_sc+150);
petitchiffre.Print("Height: " ,(x_cfg_sc+40), y_cfg_sc+185);
petitchiffre.Print(ol::ToString(hauteur_ecran) ,(x_cfg_sc+120), y_cfg_sc+185);
EncadreScreen.DrawOutline(CouleurLigne);

/////////////////////WINDOW POS///////////////////////////////////////////////////

Rect EncadrePos(Vec2D(x_cfg_sc+10+230,y_cfg_sc+40),Vec2D(200,230));
EncadrePos.SetRoundness(7.5);
EncadrePos.SetLineWidth(epaisseur_ligne_fader);
petitchiffre.Print("POSITIONS " ,(x_cfg_sc+250), (y_cfg_sc+60));

for (int lpos=0;lpos<4;lpos++)
{
Rect pos_mode(Vec2D( x_cfg_sc+250,y_cfg_sc+75+(lpos*30)),Vec2D(55,15));
pos_mode.SetRoundness(5);
pos_mode.Draw(CouleurFond.WithAlpha(0.5));
//reset windows general
if(lpos==0)
{
petitchiffre.Print("Reset Internal" ,(x_cfg_sc+325), y_cfg_sc+50+35+(lpos*30));
petitchiffre.Print("         Windows" ,(x_cfg_sc+325), y_cfg_sc+50+35+(lpos*30)+15);
if(mouse_x>x_cfg_sc+250 && mouse_x<x_cfg_sc+305 && mouse_y>y_cfg_sc+75+(lpos*30) && mouse_y<y_cfg_sc+90+(lpos*30)  && window_focus_id==920)
{
pos_mode.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
pos_mode.Draw(CouleurFader);
reset_window_positions();
mouse_released=1;
}
}
}
//record custom
else if(lpos==1)
{
petitchiffre.Print("Record Pos" ,(x_cfg_sc+325), y_cfg_sc+85+(lpos*30));
if(mouse_x>x_cfg_sc+250 && mouse_x<x_cfg_sc+305 && mouse_y>y_cfg_sc+75+(lpos*30) && mouse_y<y_cfg_sc+90+(lpos*30) && window_focus_id==920)
{
pos_mode.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
pos_mode.Draw(CouleurFader);
store_window_positions();
mouse_released=1;
}
}
}
//load custom
else if(lpos==2)
{
petitchiffre.Print("Reload Pos" ,(x_cfg_sc+325), y_cfg_sc+85+(lpos*30));
if(mouse_x>x_cfg_sc+250 && mouse_x<x_cfg_sc+305 && mouse_y>y_cfg_sc+75+(lpos*30) && mouse_y<y_cfg_sc+90+(lpos*30) && window_focus_id==920)
{
pos_mode.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
pos_mode.Draw(CouleurFader);
reload_window_positions();
mouse_released=1;
}
}
}
//set position
else if(lpos==3)
{
petitchiffre.Print("Program Position" ,(x_cfg_sc+325), y_cfg_sc+85+(lpos*30));
if(mouse_x>x_cfg_sc+250 && mouse_x<x_cfg_sc+305 && mouse_y>y_cfg_sc+75+(lpos*30) && mouse_y<y_cfg_sc+90+(lpos*30) && window_focus_id==920)
{
pos_mode.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
if(index_set_pos==0){index_set_pos=1;}
else if(index_set_pos==1){index_set_pos=0;}
mouse_released=1;
}
}
if(index_set_pos==1){pos_mode.Draw(CouleurFader);}
}
}
EncadrePos.DrawOutline(CouleurLigne);

Rect boxposx(Vec2D((x_cfg_sc+330),y_cfg_sc+190),Vec2D(65,30));
boxposx.SetRoundness(7.5);
boxposx.Draw(CouleurFond.WithAlpha(0.5));

Rect boxposy(Vec2D((x_cfg_sc+330),y_cfg_sc+225),Vec2D(65,30));
boxposy.SetRoundness(7.5);
boxposy.Draw(CouleurFond.WithAlpha(0.5));

if(mouse_x>(x_cfg_sc+330) && mouse_x<(x_cfg_sc+395) && window_focus_id==920)
{
if(mouse_y> y_cfg_sc+190 && mouse_y<y_cfg_sc+220)
{
boxposx.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0 && index_set_pos==1)
{
posX_mainwindow=atoi(numeric);
reset_numeric_entry();
mouse_released=1;
}
}
if(mouse_y> y_cfg_sc+225 && mouse_y<y_cfg_sc+255)
{
boxposy.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0 && index_set_pos==1)
{
posY_mainwindow=atoi(numeric);
reset_numeric_entry();
mouse_released=1;
}
}
}

petitchiffre.Print("X: " ,(x_cfg_sc+300), y_cfg_sc+210);
petitchiffre.Print(ol::ToString(posX_mainwindow) ,(x_cfg_sc+350), y_cfg_sc+210);
petitchiffre.Print("Y: " ,(x_cfg_sc+300), y_cfg_sc+245);
petitchiffre.Print(ol::ToString(posY_mainwindow) ,(x_cfg_sc+350), y_cfg_sc+245);
EncadreScreen.DrawOutline(CouleurLigne);

//////////////////////COLOR THEME/////////////////////////////////////////////


Rect EncadreTheme(Vec2D(x_cfg_sc+470,y_cfg_sc+40),Vec2D(350,230));
EncadreTheme.SetRoundness(7.5);
EncadreTheme.SetLineWidth(epaisseur_ligne_fader);
petitchiffre.Print("COLOR THEMES " ,(x_cfg_sc+500), (y_cfg_sc+60));

for (int thp=0;thp<6;thp++)
{
Rect theme_mode(Vec2D( x_cfg_sc+480,y_cfg_sc+75+(thp*30)),Vec2D(55,15));
theme_mode.SetRoundness(5);
theme_mode.Draw(CouleurFond.WithAlpha(0.5));
if(thp==0)
{
petitchiffre.Print("Black 70's" ,(x_cfg_sc+550), y_cfg_sc+85+(thp*30));
}
else if(thp==1)
{
petitchiffre.Print("Classic Grey" ,(x_cfg_sc+550), y_cfg_sc+85+(thp*30));
}
else if(thp==2)
{
petitchiffre.Print("Electric Night" ,(x_cfg_sc+550), y_cfg_sc+85+(thp*30));
}
else if(thp==3)
{
petitchiffre.Print("Discrete" ,(x_cfg_sc+550), y_cfg_sc+85+(thp*30));
}
else if(thp==4)
{
petitchiffre.Print("Matrix" ,(x_cfg_sc+550), y_cfg_sc+85+(thp*30));
}
else if(thp==5)
{
petitchiffre.Print("User Colors :" ,(x_cfg_sc+550), y_cfg_sc+85+(thp*30));
}

if(mouse_x>x_cfg_sc+480 && mouse_x<x_cfg_sc+535 && mouse_y>y_cfg_sc+65+(thp*30) && mouse_y<y_cfg_sc+90+(thp*30) && window_focus_id==920)
{
theme_mode.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
config_color_style_is=thp;
LoadWhiteCatColorProfil();
mouse_released=1;
}
}
if(config_color_style_is==thp){theme_mode.Draw(CouleurFader);}
}

///////////////////////////////////////////////////////////////////////////
//selection et affectation user
Rect theme_receive(Vec2D( x_cfg_sc+665,y_cfg_sc+105),Vec2D(55,15));
theme_receive.SetRoundness(5);
theme_receive.Draw(CouleurFond.WithAlpha(0.5));
petitchiffre.Print("Receive" ,(x_cfg_sc+730),y_cfg_sc+105);
petitchiffre.Print("Trichromy" ,(x_cfg_sc+730),y_cfg_sc+120);

if(mouse_x> x_cfg_sc+665 && mouse_x< x_cfg_sc+720 && mouse_y>y_cfg_sc+105 && mouse_y<y_cfg_sc+120 && window_focus_id==920)
{
theme_receive.Draw(CouleurSurvol);
 if(mouse_button==1 && mouse_released==0)
 {
 if( receive_from_trichro==0){receive_from_trichro=1;}
 else if( receive_from_trichro==1){receive_from_trichro=0;}
 mouse_released=1;
 }
}

if(receive_from_trichro==1){theme_receive.Draw(CouleurFader);}

for (int lg=0;lg<3;lg++)
{
 for   (int cl=0;cl<4;cl++)
 {
 Rect ColUser(Vec2D(x_cfg_sc+660+(cl*40),y_cfg_sc+140+(lg*40)),Vec2D(30,30));
 ColUser.SetRoundness(5);
 index_color_user_to_affect=cl+(lg*4);   ;

 switch (index_color_user_to_affect)
 {
 case 0:
 CouleurUserLoop=CouleurUser1;
 break;
 case 1:
 CouleurUserLoop=CouleurUser2;
 break;
 case 2:
 CouleurUserLoop=CouleurUser3;
 break;
 case 3:
 CouleurUserLoop=CouleurUser4;
 break;
 case 4:
 CouleurUserLoop=CouleurUser5;
 break;
 case 5:
 CouleurUserLoop=CouleurUser6;
 break;
 case 6:
 CouleurUserLoop=CouleurUser7;
 break;
 case 7:
 CouleurUserLoop=CouleurUser8;
 break;
 case 8:
 CouleurUserLoop=CouleurUser9;
 break;
 case 9:
 CouleurUserLoop=CouleurUser10;
 break;
 case 10:
 CouleurUserLoop=CouleurUser11;
 break;
 case 11:
 CouleurUserLoop=CouleurUser12;
 break;
 default: break;
 }
 ColUser.Draw(CouleurUserLoop);

 if(mouse_x>x_cfg_sc+660+(cl*40) && mouse_x<x_cfg_sc+690+(cl*40) && mouse_y>y_cfg_sc+140+(lg*40) && mouse_y<y_cfg_sc+170+(lg*40) && window_focus_id==920)
 {
 if(mouse_button==1 && mouse_released==0)
 {
 index_color_user_selected=cl+(lg*4);
 mouse_released=1;
 }
 }
 ColUser.DrawOutline(CouleurLigne);
 if(index_color_user_to_affect==index_color_user_selected)
 {
 ColUser.SetLineWidth(epaisseur_ligne_fader);
 ColUser.DrawOutline(CouleurFader);
 }
}
}
//ventilation couleurs
 if(receive_from_trichro==1 && index_affect_color_to_dock==1)
 {
  couleurs_user[index_color_user_selected][0]=float(my_red)/255;
  couleurs_user[index_color_user_selected][1]=float(my_green)/255;
  couleurs_user[index_color_user_selected][2]=float(my_blue)/255;

  Rgba TmpColor (couleurs_user[index_color_user_selected][0],couleurs_user[index_color_user_selected][1],couleurs_user[index_color_user_selected][2]);

  switch (index_color_user_selected)
 {
 case 0:
 CouleurUser1=TmpColor;
 sprintf(descriptif_colors_user_conf,"Your color is:Background");
 break;
 case 1:
 CouleurUser2=TmpColor;
 sprintf(descriptif_colors_user_conf,"Your color is:Lines");
 break;
 case 2:
 CouleurUser3=TmpColor;
 sprintf(descriptif_colors_user_conf,"Your color is:Fader");
 break;
 case 3:
 sprintf(descriptif_colors_user_conf,"Your color is:Selected");
 CouleurUser4=TmpColor;
 break;
 case 4:
 sprintf(descriptif_colors_user_conf,"Your color is:On mouse over");
 CouleurUser5=TmpColor;
 break;
 case 5:
 sprintf(descriptif_colors_user_conf,"Your color is:Levels");
 CouleurUser6=TmpColor;
 break;
 case 6:
 sprintf(descriptif_colors_user_conf,"Your color is:Selection");
 CouleurUser7=TmpColor;
 break;
 case 7:
 sprintf(descriptif_colors_user_conf,"Your color is:Back levels");
 CouleurUser8=TmpColor;
 break;
 case 8:
 sprintf(descriptif_colors_user_conf,"Your color is:Blind");
 CouleurUser9=TmpColor;
 break;
 case 9:
 sprintf(descriptif_colors_user_conf,"Your color is:Lock");
 CouleurUser10=TmpColor;
 break;
 case 10:
 sprintf(descriptif_colors_user_conf,"Your color is:Config");
 CouleurUser11=TmpColor;
 break;
 case 11:
 sprintf(descriptif_colors_user_conf,"Your color is:Procedure");
 CouleurUser12=TmpColor;
 break;
 default: break;
 }
 LoadWhiteCatColorProfil();
}

petitchiffre.Print(descriptif_colors_user_conf,x_cfg_sc+660,y_cfg_sc+70);
EncadreTheme.DrawOutline(CouleurLigne);

//////////////////SCREEN SIZE//////////////////////////////////////////////////
Rect EncadreUseCol(Vec2D(x_cfg_sc+655,y_cfg_sc+90),Vec2D(160,170));
EncadreUseCol.SetRoundness(7.5);
EncadreUseCol.SetLineWidth(demi_epaisseur_ligne_fader);
EncadreUseCol.DrawOutline(CouleurLigne);

Line(Vec2D(x_cfg_sc+655,y_cfg_sc+230),Vec2D(x_cfg_sc+630,y_cfg_sc+230)).Draw(CouleurLigne);

return(0);
}
