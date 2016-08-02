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

* \file trichro_core2.cpp
* \brief {Core fonctions for the color whell}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Core fonctions pour la fenêtre de roue de couleur en trichromie
*
*   Core fonctions for the color whell
*
**/

/*BITMAP *bmp_buffer_trichro= create_bitmap(320, 200);
clear_bitmap(bmp_buffer_trichro);
destroy_bitmap(bmp_buffer_trichro);
//blit(bmp, screen, 0, 0, 0, 0, 320, 200);*/


int stock_etat_picker_dans_dockcolor(int dcolor_selected)
{
dock_color_type[dcolor_selected]=index_quadri;
x_y_picker_par_colordock[dcolor_selected][0]=(int)picker_x;
x_y_picker_par_colordock[dcolor_selected][1]=(int)picker_y;
angle_hue_par_colordock[dcolor_selected]=angle_snap;
picker_trichro[dcolor_selected][0]=r_pick;
picker_trichro[dcolor_selected][1]=v_pick;
picker_trichro[dcolor_selected][2]=b_pick;
picker_trichro[dcolor_selected][3]=my_yellow;

return(0);
}


int CounterClockWise ( double Pt0_X, double Pt0_Y, double Pt1_X, double Pt1_Y, double Pt2_X, double Pt2_Y )
{
 double dx1, dx2, dy1, dy2 ;
 /* Calcule les divers produits vectoriels */
 dx1 = Pt1_X - Pt0_X ;
 dy1 = Pt1_Y - Pt0_Y ;
 dx2 = Pt2_X - Pt0_X ;
 dy2 = Pt2_Y - Pt0_Y ;
 /* Verifie si les chiffres sont des zéros */
 if ( fabs(dx1) < ACCURACY_DOUBLE )
    dx1 = 0.0 ;
 if ( fabs(dx2) < ACCURACY_DOUBLE )
    dx2 = 0.0 ;
 if ( fabs(dy1) < ACCURACY_DOUBLE )
    dy1 = 0.0 ;
 if ( fabs(dy2) < ACCURACY_DOUBLE )
    dy2 = 0.0 ;
 /* Teste les conditions */
 if ( (dx1*dy2) > (dy1*dx2) )
     return (+1);
 if ( (dx1*dy2) < (dy1*dx2) )
     return (-1);
 if ( ((dx1*dx2) < 0.0) || ((dy1*dy2) < 0.0) )
     return (-1);
 if ( (dx1*dx1+dy1*dy1) < (dx2*dx2+dy2*dy2) )
     return (+1);
 return (0) ;
}




int do_colors()
{
int lefaderacolorer=colorpreset_linked_to_dock[dock_color_selected][0];
int ledockacolorer=colorpreset_linked_to_dock[dock_color_selected][1];

if(dock_color_type[dock_color_selected]==0)//trichro
{
 for (int  doC=1;doC<514;doC++)
 {
 if(dock_color_channels[dock_color_selected][0][doC]==1)
 {dock_color_buffer_C[dock_color_selected][doC]=my_red;
 FaderDockContains[lefaderacolorer][ledockacolorer][doC] =dock_color_buffer_C[dock_color_selected][doC];
 }
 else  if(dock_color_channels[dock_color_selected][1][doC]==1)
 { dock_color_buffer_C[dock_color_selected][doC]=my_green;
  FaderDockContains[lefaderacolorer][ledockacolorer][doC] =dock_color_buffer_C[dock_color_selected][doC];
 }
 else  if(dock_color_channels[dock_color_selected][2][doC]==1)
 { dock_color_buffer_C[dock_color_selected][doC]=my_blue;
  FaderDockContains[lefaderacolorer][ledockacolorer][doC] =dock_color_buffer_C[dock_color_selected][doC];
 }
 }
}
else if(dock_color_type[dock_color_selected]==1)//quadri, desaturation par le jaune
{
 for (int  doC=1;doC<513;doC++)
 {
 if(dock_color_channels[dock_color_selected][0][doC]==1)
 {dock_color_buffer_C[dock_color_selected][doC]=my_red;
  FaderDockContains[lefaderacolorer][ledockacolorer][doC] =dock_color_buffer_C[dock_color_selected][doC];
 }
 else  if(dock_color_channels[dock_color_selected][1][doC]==1)
 { dock_color_buffer_C[dock_color_selected][doC]=my_green;
  FaderDockContains[lefaderacolorer][ledockacolorer][doC] =dock_color_buffer_C[dock_color_selected][doC];
 }
 else  if(dock_color_channels[dock_color_selected][2][doC]==1)
 { dock_color_buffer_C[dock_color_selected][doC]=my_blue;
  FaderDockContains[lefaderacolorer][ledockacolorer][doC] =dock_color_buffer_C[dock_color_selected][doC];
 }
  else  if(dock_color_channels[dock_color_selected][3][doC]==1)
 { dock_color_buffer_C[dock_color_selected][doC]=my_yellow;
  FaderDockContains[lefaderacolorer][ledockacolorer][doC] =dock_color_buffer_C[dock_color_selected][doC];
 }
 }
}
 return(0);
}


int report_gels_to_rvb_trichro(int manufacturer, int gel_position)
{

switch(index_use_transmission)
{
case 0:
    my_red=rvb_of_gels[manufacturer][gel_position][0];
    my_green=rvb_of_gels[manufacturer][gel_position][1];
    my_blue=rvb_of_gels[manufacturer][gel_position][2];
break;
case 1://use transmission data
    my_red=(int)((((float)rvb_of_gels[manufacturer][gel_position][0])/100)*gel_transimission[manufacturer][gel_position]);
    my_green=(int)((((float)rvb_of_gels[manufacturer][gel_position][1])/100)*gel_transimission[manufacturer][gel_position]);
    my_blue=(int)((((float)rvb_of_gels[manufacturer][gel_position][2])/100)*gel_transimission[manufacturer][gel_position]);
break;
default: break;
}
do_colors();
sprintf(string_Last_Order,">>Gel list Called Position %d / ref %d",gel_position,refs_of_gels[manufacturer][gel_position]);
return(0);
}

int trichro_back_buffer(int xchroma, int ychroma, int rayon, int largeurchroma)//calcul et couleurs dans les 10eme de sec.
{
clear_bitmap(bmp_buffer_trichro);
int coord[4];
for (hcl=0.0; hcl<360.0; hcl+=0.4)
{
     xcl = cos(hcl*PI/180.0)*(rayon+16);
	 ycl = sin(hcl*PI/180.0)*(rayon+16);

	 hsv_to_rgb(hcl, 1.0, 1.0, &rcl, &gcl, &bcl);

	 coord[0]=xchroma;
     coord[1]=ychroma;
     coord[2]=(int)(xchroma+xcl);
     coord[3]=(int)(ychroma+ycl);
//	 Line(Vec2D(xchroma,ychroma),Vec2D(xchroma+xcl,ychroma+ycl)).Draw(Rgba(rcl,gcl,bcl));
 polygon(bmp_buffer_trichro, 2, coord, makecol(rcl,gcl,bcl));
}

//Circle MasqueNoir(Vec2D(xchroma,ychroma),rayon-16);
//MasqueNoir.Draw(CouleurFond);
circlefill(bmp_buffer_trichro,  xchroma,ychroma, rayon-16, makecol(0,0,0));

for(angle = 0 ; angle <(PI*360) / 180  ; angle+=0.1)//radians
{
   vx = cos(angle)*rayon;
   vy = sin(angle)*rayon;
   if(mouse_x>xtrichro_window+vx-16  && mouse_x< xtrichro_window+vx+16 && mouse_y>ytrichro_window+vy-16 && mouse_y<ytrichro_window+vy+16
      && mouse_button==1 && window_focus_id==902)

   {

   angle_snap=angle;//angle rotation roue couleur
   position_curseur_hue_x= xtrichro_window+vx;//affichage
   position_curseur_hue_y=ytrichro_window+vy ;//affichage
   cref=getpixel(bmp_buffer_trichro,(int)(xchroma+vx),(int)(ychroma+vy));
    r_pick=getr(cref);
    v_pick=getg(cref);
    b_pick=getb(cref);

   stock_etat_picker_dans_dockcolor(dock_color_selected);
   do_colors();//ventilation des niveaux pickés ainsi que distrib dans faders et docks
    midi_levels[497]=(int)(angle_snap/((PI*360) / (180*127)));
    if(midi_send_out[497]==1){index_send_midi_out[497]=1;}
    index_snap_color_wheel_levels=1;
    mouse_released=1;
   }

}


//attaque midi
if (miditable[0][497]==istyp && miditable[1][497]==ischan && miditable[2][497]==ispitch)
{
  angle_snap=((PI*360) / (180*127))*midi_levels[497];
  vx = cos(angle_snap)*125;
  vy = sin(angle_snap)*125;
  position_curseur_hue_x= xtrichro_window+vx;
  position_curseur_hue_y=ytrichro_window+vy ;
  cref=getpixel(bmp_buffer_trichro,(int)(xchroma+vx),(int)(ychroma+vy));
  r_pick=getr(cref);
  v_pick=getg(cref);
  b_pick=getb(cref);
  stock_etat_picker_dans_dockcolor(dock_color_selected);
  do_colors();//ventilation des niveaux pickés ainsi que distrib dans faders et docks
  if (midi_levels[497]!=previous_trichro_wheel)
  {
      index_snap_color_wheel_levels=1;
      previous_trichro_wheel=midi_levels[497];
  }
}
//triangle
	V3D_f v1 =
	{
		xchroma+vxd, ychroma+vyd, 0,
		0., 0.,
		makecol(0, 0, 0) // black vertex
	};
	V3D_f v2 =
	{
		xchroma+vxw, ychroma+vyw, 0,
		0., 0.,
		makecol(255, 255, 255) // white vertex
	};
	V3D_f v3 =
	{
		xchroma+vxh, ychroma+vyh, 0,
		0., 0.,
		makecol(r_pick, v_pick, b_pick) // color vertex
	};


	triangle3d_f(bmp_buffer_trichro, POLYTYPE_GCOL, NULL, &v1, &v2, &v3);


//definir si on est dans l aire du triangle
//(angle (Pa-1 Pa-2) * angle (Pa-2 Pa-3) * angle (Pa-3 Pa-1)) resultat pos ou neg
float angle1, angle2,angle3;
angle1=CounterClockWise(mouse_x,mouse_y,xtrichro_window+vxd, ytrichro_window+vyd,xtrichro_window+vxh, ytrichro_window+vyh) ; //Pa1-Pa2
angle2=CounterClockWise(mouse_x,mouse_y,xtrichro_window+vxh, ytrichro_window+vyh,xtrichro_window+vxw, ytrichro_window+vyw);//Pa2 - Pa3
angle3=CounterClockWise(mouse_x,mouse_y,xtrichro_window+vxw, ytrichro_window+vyw, xtrichro_window+vxd, ytrichro_window+vyd);//Pa3-Pa1

if((angle1*angle2*angle3) <=0 ) //dans le triangle formé par la souris et les 3 points du triangle
{


if(mouse_b&1 && mouse_x>xtrichro_window+vxd && mouse_x<xtrichro_window+vxw && mouse_y>ytrichro_window+vyd && mouse_y<ytrichro_window+vyh && window_focus_id==902)
{
picker_x=mouse_x-xtrichro_window;
picker_y=mouse_y-ytrichro_window;
stock_etat_picker_dans_dockcolor(dock_color_selected);
do_colors();//ventilation des niveaux pickés ainsi que distrib dans faders et docks
index_snap_color_wheel_levels=1;
}

}


if(   index_snap_color_wheel_levels==1)//take measurement on mouse or midi
{
if(getpixel(bmp_buffer_trichro,(int)(xchroma+picker_x),(int)(ychroma+picker_y))!=0)
{colorpicker=getpixel(bmp_buffer_trichro,(int)(xchroma+picker_x),(int)(ychroma+picker_y));}

my_red=getr(colorpicker);
my_green=getg(colorpicker);
my_blue=getb(colorpicker);

if (index_quadri==1)
{
   float hue, saturation, value;
   rgb_to_hsv(my_red, my_green, my_blue, &hue, &saturation, &value);
   //saturation: plus il y en a , moins de jaune il y a
   my_yellow=(int)(255-(255*saturation));
}
do_colors();//ventilation des niveaux pickés ainsi que distrib dans faders et docks
index_snap_color_wheel_levels=0;
}
return(0);
}


int show_who_is_in_dock_color(int dockCol, int couleur)
{
for (int co=1;co<513;co++)
{
show_who_is_in_FADER_DOCK[co]=dock_color_channels[dockCol][couleur][co];
}

return(0);
}

int do_logical_Interface_Trichromie(int xchroma, int ychroma, int rayon, int largeurchroma)
{

/////////////////TRICHRO / QUADRI CHOOSE//////////////////////////////////////

if(mouse_x>xchroma-60 && mouse_x<xchroma+80 && mouse_y>ychroma-190 && mouse_y<ychroma-160)
{

if(index_quadri==0){index_quadri=1;dock_color_type[dock_color_selected]=1;}
else if(index_quadri==1){index_quadri=0;dock_color_type[dock_color_selected]=0;}
mouse_released=1;
}


//GEL LIST BUTTON
if(mouse_x>xchroma+90 && mouse_x<xchroma+150 && mouse_y>ychroma-185 && mouse_y<ychroma-165)
{
show_gel_list=toggle(show_gel_list);
mouse_released=1;
}

/////////////////////AFFECTATION ON / OFF AUX DOCKS FADERS///////////////////////////

if(mouse_x>xchroma+20 && mouse_x<xchroma+150 && mouse_y>ychroma+300 && mouse_y< ychroma+330)
{
if(index_affect_color_to_dock==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_affect_color_to_dock=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_affect_color_to_dock;
mouse_released=1;
}
/////////////////////////////////////////////////////////////////////////////////

//////////////////////ROUE DE COULEUR//////////////////////////////////////////////////////

//AFFECTATION MIDI
if( Midi_Faders_Affectation_Type!=0)//config midi
  {
  //midi report
  switch(miditable[0][497])
  {
  case 0: sprintf(thetypinfo,"Note");break;
  case 1: sprintf(thetypinfo,"Key On");break;
  case 2: sprintf(thetypinfo,"Key Off");break;
  case 4: sprintf(thetypinfo,"Ctrl Change");break;
  default: break;
  }
  sprintf(string_last_midi_id,"COLOR WHEEL FADER is Ch: %d Pitch: %d Typ: %s" , miditable[1][497],miditable[2][497],thetypinfo);

  if(mouse_x>xchroma-140 && mouse_x<xchroma+140 && mouse_y>ychroma-140 && mouse_y<ychroma+140)
  {
    attribute_midi_solo_affectation(497,Midi_Faders_Affectation_Mode);
    mouse_released=1;
   }
}


/////////////////////DOCKING DES COULEURS////////////////////////////////////////
//emplacement des box pour actions de storage RVB sur 6 presets

//affectation des circuits aux RVB Y

if(mouse_y>ychroma+165 && mouse_y<ychroma+185)
{
if(mouse_x> xchroma-130 && mouse_x< xchroma-80 )//RED
{
if (index_inspekt==1){show_who_is_in_dock_color(dock_color_selected,0);}
couleur_to_affect=0;
bool there_is_asel_chan=0;

switch(index_paste_on_the_fly)
{
case 0:
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1)
{there_is_asel_chan=1;break;}
}

if(there_is_asel_chan==1 && (index_do_dock==1|| index_do_modify==1 || index_do_report==1))
{index_do_affect_color_trichro=1;index_ask_confirm=1;}

else {index_do_affect_color_trichro=0;index_ask_confirm=0;sprintf(string_Last_Order,"No channel selected to store as color");}
break;
case 1:
if(index_blind==0)
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferSaisie[p]=my_red;}
}
}
else
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferBlind[p]=my_red;}
}
}
sprintf(string_Last_Order,"Pasted On the Fly RED result");
break;
default: break;
}
mouse_released=1;
}

else if (mouse_x> xchroma-65 && mouse_x< xchroma-15 )//GREEN
{
if (index_inspekt==1){show_who_is_in_dock_color(dock_color_selected,1);}
couleur_to_affect=1;
bool there_is_asel_chan=0;
switch(index_paste_on_the_fly)
{
case 0:
for(int p=1;p<513;p++)
{if(Selected_Channel[p]==1){there_is_asel_chan=1;break;}}
if(there_is_asel_chan==1 && (index_do_dock==1|| index_do_modify==1 || index_do_report==1))
{index_do_affect_color_trichro=1;index_ask_confirm=1;}
else {sprintf(string_Last_Order,"No channel selected to store as color");}
break;
case 1:
if(index_blind==0)
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferSaisie[p]=my_green;}
}
}
else
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferBlind[p]=my_green;}
}
}
sprintf(string_Last_Order,"Pasted On the Fly GREEN result");
break;
default: break;
}
mouse_released=1;
}

else if (mouse_x> xchroma && mouse_x< xchroma+50 )//BLUE
{
if (index_inspekt==1){show_who_is_in_dock_color(dock_color_selected,2);}

couleur_to_affect=2;
bool there_is_asel_chan=0;
switch(index_paste_on_the_fly)
{
case 0:
for(int p=1;p<513;p++)
{if(Selected_Channel[p]==1){there_is_asel_chan=1;break;}}
if(there_is_asel_chan==1 && (index_do_dock==1|| index_do_modify==1 || index_do_report==1)){index_do_affect_color_trichro=1;index_ask_confirm=1;}
else {sprintf(string_Last_Order,"No channel selected to store as color");}
break;
case 1:
if(index_blind==0)
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferSaisie[p]=my_blue;}
}
}
else
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferBlind[p]=my_blue;}
}
}
sprintf(string_Last_Order,"Pasted On the Fly BLUE result");
break;
default: break;
}
mouse_released=1;
}

else if (mouse_x> xchroma+65 && mouse_x< xchroma+115 )//YELLOW
{
if (index_inspekt==1){show_who_is_in_dock_color(dock_color_selected,3);}
couleur_to_affect=3;
bool there_is_asel_chan=0;
switch(index_paste_on_the_fly)
{
case 0:
for(int p=1;p<513;p++)
{if(Selected_Channel[p]==1){there_is_asel_chan=1;break;}}
if(there_is_asel_chan==1&& (index_do_dock==1|| index_do_modify==1 || index_do_report==1)){index_do_affect_color_trichro=1;index_ask_confirm=1;}
else {sprintf(string_Last_Order,"No channel selected to store as color");}
break;
case 1:
if(index_blind==0)
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferSaisie[p]=my_yellow;}
}
}
else
{
for(int p=1;p<513;p++)
{
if(Selected_Channel[p]==1){bufferBlind[p]=my_yellow;}
}
}
sprintf(string_Last_Order,"Pasted On the Fly YELLOW result");
break;
default: break;
}
mouse_released=1;
}
}


//midi out de la roue

if(mouse_x> xchroma+140-10 && mouse_x< xchroma+140+10 && mouse_y>ychroma+110-10 && mouse_y<ychroma+110+10)
{

  if(midi_send_out[497]==0){midi_send_out[497]=1; }
  else if(midi_send_out[497]==1){midi_send_out[497]=0; }
  mouse_released=1;
  }

raccrochage_midi_logical_circulaire (xchroma-6, ychroma, 497, 125, 125);



//premiere rangee de dock colors

for (int dock_color=0;dock_color<4;dock_color++)
{
if(mouse_x>xchroma-130+(65*dock_color) && mouse_x<xchroma-80+(65*dock_color) && mouse_y>ychroma+215 && mouse_y<ychroma+235)
{
if( Midi_Faders_Affectation_Type!=0)
{
if(dock_color==0 && Midi_Faders_Affectation_Type==2)
{attribute_midi_to_control(949,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);}
else{attribute_midi_solo_affectation(949+dock_color, Midi_Faders_Affectation_Mode);}
}
else
{
dock_color_selected=dock_color;
load_etat_picker_dans_dockcolor(dock_color_selected);
sprintf(string_Last_Order,">>Dock Color Selected %d",(dock_color_selected+1));
mouse_released=1;
}
}
}
//deuxième rangee de dockcolors
for (int dock_colortwo=0;dock_colortwo<4;dock_colortwo++)
{
if(mouse_x>xchroma-130+(65*dock_colortwo) && mouse_x<xchroma-80+(65*dock_colortwo) && mouse_y>ychroma+255 && mouse_y<ychroma+275)
{
if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(949+(dock_colortwo+4), Midi_Faders_Affectation_Mode);
}
else
{
dock_color_selected=dock_colortwo+4;
load_etat_picker_dans_dockcolor(dock_color_selected);
sprintf(string_Last_Order,">>Dock Color Selected %d",dock_color_selected+1);
mouse_released=1;
}
}
}

//PASTE ON THE FLY
if(mouse_x>xchroma-150 && mouse_x<xchroma-20 && mouse_y>ychroma+300 && mouse_y< ychroma+330)
{
if(mouse_b&1 &&  mouse_released==0 && window_focus_id==902)
{
index_paste_on_the_fly=toggle(index_paste_on_the_fly);
mouse_released=1;
}
}


//GEL LIST
if(show_gel_list==1)
{

if(mouse_x>xchroma+180 && mouse_x<xchroma+250 && mouse_y>ychroma-185 && mouse_y<ychroma-165)
{
index_gel_type_selected++;
if(index_gel_type_selected>3)index_gel_type_selected=0;
mouse_released=1;
}
//numeric or designer list
if(mouse_x>xchroma+260 && mouse_x<xchroma+330 && mouse_y>ychroma-185 && mouse_y<ychroma-165)
{
show_designer_list=toggle(show_designer_list);
switch(show_designer_list)
{
case 0://numerical order
break;
case 1://designer order
break;
default: break;
}
mouse_released=1;
}

//saisie d une ref de gelat
if(mouse_x>xchroma+340 && mouse_x<xchroma+390 && mouse_y>ychroma-185 && mouse_y<ychroma-165)
{
call_ref_number=atoi(numeric);
mouse_released=1;
if(call_ref_number<10000 && call_ref_number!=0)
{

//repositionnemennt de la liste
for (int i=0;i<10000;i++)
{
if(refs_of_gels[index_gel_type_selected][i]==call_ref_number )
{
gel_position[index_gel_type_selected]=i;
report_gels_to_rvb_trichro(index_gel_type_selected,gel_position[index_gel_type_selected]);
break;
}
}
reset_numeric_entry();
}

}
//+ - Index gelatine
if(mouse_y>ychroma-187 && mouse_y<ychroma-163)
{
//- index
if(mouse_x>xchroma+398 && mouse_x<xchroma+422)
{
if(gel_position[index_gel_type_selected]>10)gel_position[index_gel_type_selected]-=10;
mouse_released=1;
}
//+ index
if(mouse_x>xchroma+428 && mouse_x<xchroma+452)
{
if(gel_position[index_gel_type_selected]<10000-10)gel_position[index_gel_type_selected]+=10;
mouse_released=1;
}
}

//Transmission calculation
if(mouse_x>xchroma+510 && mouse_x<xchroma+550 && mouse_y>ychroma-185 && mouse_y<ychroma-165)
{
index_use_transmission=toggle(index_use_transmission);
mouse_released=1;
}

//sélection gel
for(int i=0;i<30;i++)
{
if( mouse_x>xchroma+175 && mouse_x<xchroma+485 && mouse_y>ychroma-150+(i*16) && mouse_y<ychroma-134+(i*16) )
{
call_ref_number=refs_of_gels[index_gel_type_selected][gel_position[index_gel_type_selected]+i];
report_gels_to_rvb_trichro(index_gel_type_selected,gel_position[index_gel_type_selected]+i);
mouse_released=1;
}
}
//fin gel list
}


return(0);
}
/////////////////////////////////////////////////////////////////


