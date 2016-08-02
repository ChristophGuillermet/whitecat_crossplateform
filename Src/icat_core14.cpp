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

* \file icat_core14.cpp
* \brief {Core fonctions for iCAT}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions core pour iCat qui permet de controller whitecat sur un iphone via le logiciel ifantastic
*
*   Core fonctions for icat a iphone control and gui send via the iFantastic software
*
 **/


int recalculate_iCatBuilder_window_size()
{

switch(surface_type)
{
case 0://iPOD
   if(iCat_preset_orientation[iCatPageis]==0)
   {
    L_tablier_iCat=160;H_tablier_iCat=240;
   }
   else {L_tablier_iCat=240;H_tablier_iCat=160;}
largeuriCat=650;
hauteuriCat=320 + H_tablier_iCat;
break;
case 1://iPAD
   if(iCat_preset_orientation[iCatPageis]==0)
   {
    L_tablier_iCat=384;H_tablier_iCat=512;
   }
   else {
   L_tablier_iCat=512;H_tablier_iCat=384;
   }
largeuriCat=650;
hauteuriCat=320 + H_tablier_iCat;
break;
default:
break;
}

 return(0);
}



int reset_previous_levels_infos()
{
//faders
for(int f=0;f<48;f++)
{
  Fader_before[f]=255;
  before_dock_used_by_fader_is[f]=-1;
  OldFaderLockProc[f]=255;
  before_is_dock_for_lfo_selected[f]=-1;
  before_lfo_speed[f]=-1;
}
//crossfade
 before_niveauX1 =-1;
 before_niveauX2=-1;
 before_crossfade_speed=-1;
//GM
 previous_niveauGMaster=-1;
 previous_absolute_level_wheel=-1;
//Mover
for(int f=0;f<48;f++)
{
 before_mover_params[f][0]=-1;
 before_mover_params[f][1]=-1;
}
//draw
for(int pr=0;pr<6;pr++)
{
 previous_draw_level_to_do[pr]=-1;
 previous_draw_damper_decay_factor[pr]=-1;
 previous_draw_ghost_to_do[pr]=-1;
}



 return(0);
}

int load_iCat_page ( int preset_page_iCat)
{

iCatPageis=preset_page_iCat;
recalculate_iCatBuilder_window_size();
if(iCat_select_editing_slider>iCat_nbre_de_sliders[preset_page_iCat])
{
iCat_select_editing_slider=iCat_nbre_de_sliders[preset_page_iCat];
if(iCat_select_editing_slider>max_sliders_icat){iCat_select_editing_slider=0;}
}
if(iCat_select_editing_button>iCat_nbre_de_boutons[preset_page_iCat])
{
iCat_select_editing_button=iCat_nbre_de_boutons[preset_page_iCat];
if(iCat_select_editing_button>max_buttons_icat){iCat_select_editing_button=0;}
}
if(iCat_select_editing_string>iCat_nbre_de_strings[preset_page_iCat])
{
iCat_select_editing_string=iCat_nbre_de_strings[preset_page_iCat];
if(iCat_select_editing_string>max_string_icat){iCat_select_editing_string=0;}
}
if(iCat_select_tracking_zone>iCat_nbre_de_tracking_zone[preset_page_iCat])
{
iCat_select_tracking_zone=iCat_nbre_de_tracking_zone[preset_page_iCat];
if(iCat_select_tracking_zone>max_zones_icat){iCat_select_tracking_zone=0;}
}
nbrbytessendediCat=sendto(sockiCat, "clearmodels",sizeof("clearmodels"),0,(SOCKADDR*)&siniCat,sinsizeiCat); //dans routine laod avant appel du rafraichissement

sprintf(string_Last_Order,"Loaded iCat page %d",preset_page_iCat+1);


return(0);
}

int refresh_continuously_iCat_trackerzones()
{
//ok les valeurs
//sab 02/03/2014 unused var int numfad=0;
int aire=0;
int x1=0;
int y1=0;
//envois des données
char string_mf_id[16];
for(int i=1;i<iCat_nbre_de_tracking_zone[iCatPageis]+1;i++)
{
switch(iCat_trackzone_type_is[iCatPageis][i])
{
case 1://mover
 pos_iCat_tracker[iCatPageis][i][0]=mover_params[0][0];
 pos_iCat_tracker[iCatPageis][i][1]=mover_params[1][0];

if(previous_pos_iCat_tracker[iCatPageis][i][0]!=pos_iCat_tracker[iCatPageis][i][0] || previous_pos_iCat_tracker[iCatPageis][i][1]!=pos_iCat_tracker[iCatPageis][i][1])
{
sprintf(StrOrderToiCat,"model trackPosition%d position %d %d 0",i,
        (iCat_pos_trackzone[iCatPageis][i][0]*2)+((pos_iCat_tracker[iCatPageis][i][0]/2)*ratio_iCat_trackzone[iCatPageis][i]),
        (iCat_pos_trackzone[iCatPageis][i][1]*2)+((pos_iCat_tracker[iCatPageis][i][1]/2)*ratio_iCat_trackzone[iCatPageis][i]));

nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(string_mf_id,"%d-%d",pos_iCat_tracker[iCatPageis][i][0],pos_iCat_tracker[iCatPageis][i][1]);
sprintf(StrOrderToiCat,"model trackTextPos%d text %s",i,string_mf_id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

previous_pos_iCat_tracker[iCatPageis][i][0]=pos_iCat_tracker[iCatPageis][i][0] ;
previous_pos_iCat_tracker[iCatPageis][i][1]=pos_iCat_tracker[iCatPageis][i][1] ;
}
break;
case 2://draw"Draw Activ");



if(previous_pos_iCat_tracker[iCatPageis][i][0]!=pos_iCat_tracker[iCatPageis][i][0] || previous_pos_iCat_tracker[iCatPageis][i][1]!=pos_iCat_tracker[iCatPageis][i][1])
{
//chaque aire déclarée
for(int lign=0;lign<draw_preset_parameters[draw_preset_selected][1];lign++)
{
for(int col=0;col<draw_preset_parameters[draw_preset_selected][0];col++)
{
int coordonnee=col+(lign*draw_preset_parameters[draw_preset_selected][0]);
sprintf(StrOrderToiCat,"model DrawAera%dOffstet%d color 0. %.1f %.1f",i,coordonnee,
draw_preset_levels[draw_preset_selected][coordonnee]*1.0,draw_preset_levels[draw_preset_selected][coordonnee]*0.8);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
}
}

x1=iCat_pos_trackzone[iCatPageis][i][0];
y1=iCat_pos_trackzone[iCatPageis][i][1];
//curseur
sprintf(StrOrderToiCat,"model DrawAera%dCurseur xyz %d %d -0.5 %d %d -0.5 %d %d -0.5 %d %d -0.5",
i,
(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0])*draw_centre_x[draw_preset_selected] ),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1])*draw_centre_y[draw_preset_selected] ),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected])),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1]) *draw_centre_y[draw_preset_selected]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

break;
case 3://draw"Draw Matrix num");
aire=iCat_trackzone_affectation_is[iCatPageis][i]-1;
//if(index_case[aire]!=previous_index_case[aire])

if(previous_pos_iCat_tracker[iCatPageis][i][0]!=pos_iCat_tracker[iCatPageis][i][0] || previous_pos_iCat_tracker[iCatPageis][i][1]!=pos_iCat_tracker[iCatPageis][i][1])
{
//chaque aire déclarée
for(int lign=0;lign<draw_preset_parameters[aire][1];lign++)
{
for(int col=0;col<draw_preset_parameters[aire][0];col++)
{
int coordonnee=col+(lign*draw_preset_parameters[aire][0]);
sprintf(StrOrderToiCat,"model DrawSelAera%dOffstet%d color 0. %.1f %.1f",i,coordonnee,
draw_preset_levels[aire][coordonnee]*1.0,draw_preset_levels[aire][coordonnee]*0.8);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
}
}

x1=iCat_pos_trackzone[iCatPageis][i][0];
y1=iCat_pos_trackzone[iCatPageis][i][1];
//curseur
sprintf(StrOrderToiCat,"model DrawAera%dCurseur xyz %d %d -0.5 %d %d -0.5 %d %d -0.5 %d %d -0.5",
i,
(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0])*draw_centre_x[draw_preset_selected] ),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1])*draw_centre_y[draw_preset_selected] ),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected])),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][i])/draw_preset_parameters[draw_preset_selected][1]) *draw_centre_y[draw_preset_selected]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


break;
default:
break;
}

index_refresh_valeursTRCK_continous=0;
}
 return(0);
}

int refresh_continuously_iCat_sliders()
{
////////////////////SLIDERS/////////////////////////////////////////////////////

//niveaux index_refresh_valeurs_continous==1 chgt oage preset icat


int numfad=0;
int drawpr=0;
for(int i=1;i<iCat_nbre_de_sliders[iCatPageis]+1;i++)
{
switch(iCat_affectation_slider_type_is[iCatPageis][i])
{
case 1://Fader
     numfad=iCat_affectation_slider_value_is[iCatPageis][i]-1;
     if(Fader_before[numfad]!=Fader[numfad] || before_dock_used_by_fader_is[numfad]!=dock_used_by_fader_is[numfad]
     || OldFaderLockProc[numfad]!=FaderLocked[numfad] ||  before_is_dock_for_lfo_selected[numfad]!= is_dock_for_lfo_selected[numfad][dock_used_by_fader_is[numfad]]
     || index_refresh_valeurs_continous==1
     )
     {
     if(iCat_affectation_slider_value_is[iCatPageis][i]==(numfad+1) && numfad>=0 )
        {
        //////////VALEUR FADERS
        switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((float)(Fader[numfad])/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((float)(Fader[numfad])/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        //afffichage niveau + loop dock
       if(dmx_view==0){
       //dock loop
       if(is_dock_for_lfo_selected[numfad][dock_used_by_fader_is[numfad]]==1)
       {
       sprintf(StrOrderToiCat, "model tlev%d text %d *",i, (int)((float)(Fader[numfad])/2.55));
       }
       else
       {
       sprintf(StrOrderToiCat, "model tlev%d text %d",i, (int)((float)(Fader[numfad])/2.55));
       }
       }
       else {
       //dock loop
       if(is_dock_for_lfo_selected[numfad][dock_used_by_fader_is[numfad]]==1)
       {
       sprintf(StrOrderToiCat, "model tlev%d text %d *",i, Fader[numfad]);
       }
       else
       {
       sprintf(StrOrderToiCat, "model tlev%d text %d",i, Fader[numfad]);
       }
       }
       nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

        /////////TEXT DOCK
           sprintf(StrOrderToiCat, "model tdes%d text %s",i,DockName[numfad][dock_used_by_fader_is[numfad]] );
           nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        //COULEUE FADER
         col_fader_r=0.9, col_fader_g=0.5, col_fader_b=0.0;

              switch(DockTypeIs[numfad][(dock_used_by_fader_is[numfad])])
              {
               case 6://audio vol
               col_fader_r=0.0, col_fader_g=0.0, col_fader_b=0.6;
               break;
               case 7://audio pan
               col_fader_r=0.0, col_fader_g=0.0, col_fader_b=0.6;
               break;
               case 8://audio pitch
               col_fader_r=0.0, col_fader_g=0.0, col_fader_b=0.6;
               break;
               case 11://fx
               col_fader_r=0.0, col_fader_g=0.8, col_fader_b=0.0;
               break;
               case 12://grid
               col_fader_r=1.0, col_fader_g=0.0, col_fader_b=0.0;
               break;
               case 13://fx group
               col_fader_r=0.8, col_fader_g=0.8, col_fader_b=0.0;
               break;
               case 14://mover
               col_fader_r=0.5, col_fader_g=0.0, col_fader_b=0.7;
               break;
               case 15://draw
               col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
               break;
               case 16://echo
               col_fader_r=0.2, col_fader_g=0.6, col_fader_b=1.0;
               break;
               default://faders oranges
               col_fader_r=0.9, col_fader_g=0.5, col_fader_b=0.0;
               break;
              }

           if(FaderLocked[numfad]==1)
           //locké
           { col_fader_r=0.0, col_fader_g=0.4, col_fader_b=0.2; }
           sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",i, col_fader_r, col_fader_g, col_fader_b);

           }
           nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

Fader_before[numfad]=Fader[numfad];
before_dock_used_by_fader_is[numfad]=dock_used_by_fader_is[numfad];
OldFaderLockProc[numfad]=FaderLocked[numfad];
before_is_dock_for_lfo_selected[numfad]=is_dock_for_lfo_selected[numfad][dock_used_by_fader_is[numfad]];
}


break;
/////END  FADERS
case 2://accelerometre des faders
numfad=iCat_affectation_slider_value_is[iCatPageis][i]-1;
if(iCat_affectation_slider_value_is[iCatPageis][i]==(numfad+1) && ( before_lfo_speed[numfad]!=lfo_speed[numfad] || index_refresh_valeurs_continous==1))
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((float)(lfo_speed[numfad]))*ratio_iCat_slider[iCatPageis][i]);
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((float)(lfo_speed[numfad]))*ratio_iCat_slider[iCatPageis][i]);
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i, lfo_speed[numfad]-64 );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
before_lfo_speed[numfad]=lfo_speed[numfad];
}
break;


case 3://SEQUENCIEL
if( niveauX1!=before_niveauX1 || niveauX2!=before_niveauX2 || crossfade_speed!=before_crossfade_speed  || index_refresh_valeurs_continous==1  )
{
    int valA;


     switch(iCat_affectation_slider_value_is[iCatPageis][i])
     {
     case 0://x  1
     valA=niveauX1;
     col_fader_r=0.0; col_fader_g=0.5; col_fader_b=0.6;
     before_niveauX1=niveauX1;
     break;
     case 1://x  2
     valA=255-niveauX2;
     col_fader_r=0.6; col_fader_g=0.0; col_fader_b=0.0;
     before_niveauX2=niveauX2;
     break;
     case 2://accel seq
     valA=crossfade_speed*2;
     someone_changed_in_time_sequences=1;
     col_fader_r=0.9; col_fader_g=0.5; col_fader_b=0.0;
     before_crossfade_speed=crossfade_speed;
     break;
     default:
     break;
     }

     switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(valA/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(valA/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        default: break;
        }

        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        if(dmx_view==0){
        sprintf(StrOrderToiCat, "model tlev%d text %d",i, (int)((float)(valA)/2.55));
        if(iCat_affectation_slider_value_is[iCatPageis][i]==1)//X2
        {sprintf(StrOrderToiCat, "model tlev%d text %d",i, (int)((float)(255-valA)/2.55)); }
        }
        else {sprintf(StrOrderToiCat, "model tlev%d text %d",i, valA);
        if(iCat_affectation_slider_value_is[iCatPageis][i]==1)//X2
        {sprintf(StrOrderToiCat, "model tlev%d text %d",i, 255-valA); }
        }
        if(iCat_affectation_slider_value_is[iCatPageis][i]==2)//accelero sequenciel
        {sprintf(StrOrderToiCat, "model tlev%d text %d",i, (valA/2)-64); }

        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        //COULEUR FADER
         sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",i, col_fader_r, col_fader_g, col_fader_b);
         nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

}


break;
case 4://GrandMaster
if(niveauGMaster!=previous_niveauGMaster || index_refresh_valeurs_continous==1)
{
             //////////VALEUR FADERS
        switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((float)(niveauGMaster)/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((float)(niveauGMaster)/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        if(dmx_view==0){
        sprintf(StrOrderToiCat, "model tlev%d text %d",i, (int)((float)(niveauGMaster)/2.55)); }
        else {sprintf(StrOrderToiCat, "model tlev%d text %d",i, niveauGMaster); }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        //COULEUE FADER
         col_fader_r=0.7, col_fader_g=0.0, col_fader_b=0.0;
         sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",i,col_fader_r,col_fader_g,col_fader_b);
         nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
previous_niveauGMaster=niveauGMaster;
}
break;
case 5://level wheel
if(absolute_level_wheel!=previous_absolute_level_wheel || index_refresh_valeurs_continous==1)
{
        switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((float)(absolute_level_wheel)/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((float)(absolute_level_wheel)/2)*ratio_iCat_slider[iCatPageis][i]);
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        if(dmx_view==0){
        sprintf(StrOrderToiCat, "model tlev%d text %d",i, (int)((float)(absolute_level_wheel)/2.55)); }
        else {sprintf(StrOrderToiCat, "model tlev%d text %d",i, absolute_level_wheel); }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        //COULEUE FADER
         col_fader_r=0.0, col_fader_g=0.7, col_fader_b=0.7;
         sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",i,col_fader_r,col_fader_g,col_fader_b);
         nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
         previous_absolute_level_wheel=absolute_level_wheel;
}
break;
case 6://mover params
numfad=iCat_affectation_slider_value_is[iCatPageis][i]-1;
if(numfad>=0 && numfad<16  )
{
if(tracker_16b_edit==0 )
{
if(before_mover_params[numfad][0]!=mover_params[numfad][0] )
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((float)(mover_params[numfad][0]/2))*ratio_iCat_slider[iCatPageis][i]);
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((float)(mover_params[numfad][0]/2))*ratio_iCat_slider[iCatPageis][i]);
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i, mover_params[numfad][0] );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}

}
else if(tracker_16b_edit==1 )
{
if(before_mover_params[numfad][1]!=mover_params[numfad][1] )
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((float)(mover_params[numfad][1]/2))*ratio_iCat_slider[iCatPageis][i]);
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((float)(mover_params[numfad][1]/2))*ratio_iCat_slider[iCatPageis][i]);
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i, mover_params[numfad][1] );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
}

before_mover_params[numfad][0]=mover_params[numfad][0];
before_mover_params[numfad][1]=mover_params[numfad][1];
}
break;
case 7: //Draw Pressure
drawpr=iCat_affectation_slider_value_is[iCatPageis][i]-1;
if( draw_level_to_do[drawpr]!=previous_draw_level_to_do[drawpr] || index_refresh_valeurs_continous==1)
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((draw_level_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((draw_level_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i,(int) ( draw_level_to_do[drawpr]*127) );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
break;
case 8: //Draw Decay
drawpr=iCat_affectation_slider_value_is[iCatPageis][i]-1;
if( draw_damper_decay_factor[drawpr]!=previous_draw_damper_decay_factor[drawpr] || index_refresh_valeurs_continous==1)
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((draw_damper_decay_factor[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((draw_damper_decay_factor[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i,(int) ( draw_damper_decay_factor[drawpr]*127) );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
break;

case 9: //Draw Ghost
drawpr=iCat_affectation_slider_value_is[iCatPageis][i]-1;
if( draw_ghost_to_do[drawpr]!=previous_draw_ghost_to_do[drawpr] || index_refresh_valeurs_continous==1)
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((draw_ghost_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((draw_ghost_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i,(int) ( draw_ghost_to_do[drawpr]*127) );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
break;

case 10: //Draw Pressure Activ
drawpr=draw_preset_selected;
if( draw_level_to_do[drawpr]!=previous_draw_level_to_do[drawpr] || index_refresh_valeurs_continous==1 || draw_preset_selected!=previous_draw_preset_selected)
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((draw_level_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((draw_level_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i,(int) ( draw_level_to_do[drawpr]*127) );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model t%d text P%d",i, draw_preset_selected+1);
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
break;
case 11: //Draw decay selected
drawpr=draw_preset_selected;
if( draw_damper_decay_factor[drawpr]!=previous_draw_damper_decay_factor[drawpr] || index_refresh_valeurs_continous==1 || draw_preset_selected!=previous_draw_preset_selected)
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((draw_damper_decay_factor[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((draw_damper_decay_factor[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i,(int) ( draw_damper_decay_factor[drawpr]*127) );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model t%d text D%d",i, draw_preset_selected+1);
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
break;
case 12: //Draw Ghost
drawpr=draw_preset_selected;
if( draw_ghost_to_do[drawpr]!=previous_draw_ghost_to_do[drawpr] || index_refresh_valeurs_continous==1  || draw_preset_selected!=previous_draw_preset_selected)
{
      switch (iCat_orientation_slider[iCatPageis][i])
        {
        case 0://vertical
        sprintf(StrOrderToiCat,"model level%d position 0 -%d 0",i,(int)((draw_ghost_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        case 1://horizontal
        sprintf(StrOrderToiCat,"model level%d position %d 0 0",i,(int)((draw_ghost_to_do[drawpr]*127)*ratio_iCat_slider[iCatPageis][i]));
        break;
        default: break;
        }
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model tlev%d text %d",i,(int) ( draw_ghost_to_do[drawpr]*127) );
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        sprintf(StrOrderToiCat, "model t%d text G%d",i, draw_preset_selected+1);
        nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
break;

default:
break;
}
}
index_refresh_valeurs_continous=0;

//specific a draw:
for(int i=0; i<6;i++)
{
           previous_draw_level_to_do[i]=draw_level_to_do[i];
           previous_draw_damper_decay_factor[i]=draw_damper_decay_factor[i];
           previous_draw_ghost_to_do[i]=draw_ghost_to_do[i];
}
return(0);
}

int refresh_check_buttons()
{

 for(int i=0;i<48;i++)
 {
  before_check_button_state[i]=1-before_check_button_state[i];
 }
return(0);
}

int refresh_continuously_iCat_buttons()
{
/////////////////////////////////////////////////////////////////////////////
//////////////////////CHECK BUTTONS

//sab 02/03/2014 unused var int the_chaser=999;
//sab 02/03/2014 unused var int the_grid_player=999;
//sab 02/03/2014 unused var int the_audio_player=999;
int fis;
for (int ck=1;ck<iCat_nbre_de_boutons[iCatPageis]+1;ck++)//bouton des faders
{
switch(iCat_affectation_bouton_type_is[iCatPageis][ck])
{
case 1: //faders

fis=iCat_affectation_bouton_value_is[iCatPageis][ck]-1;
fis=(constrain_int_data_to_this_range(fis,0,47));
     switch(iCat_affectation_bouton_action_is[iCatPageis][ck])
     {
      case 1: //fader up
      if(lfo_mode_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]==1)
      {check_button_state[ck]=1;
      if(index_midi_mute_on_lfo==1){is_raccrochage_midi_remote[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]=1;}
      }
      else {check_button_state[ck]=0;}
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_up_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_up_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 2://fader down
      if(lfo_mode_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]==2)
      {check_button_state[ck]=1;
      if(index_midi_mute_on_lfo==1){is_raccrochage_midi_remote[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]=1;}
      }
      else {check_button_state[ck]=0;}
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_down_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_down_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 3://Fader saw
      check_button_state[ck]=lfo_cycle_is_on[iCat_affectation_bouton_value_is[iCatPageis][ck]-1];
      if(lfo_cycle_is_on[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]==1)
      {if(index_midi_mute_on_lfo==1){is_raccrochage_midi_remote[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]=1;}}
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_saw_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_saw_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 4://ToPREVDock");
      check_button_state[ck]=lfo_do_next_step[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][0];
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_prev_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_prev_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 5://ToNEXTDock
      check_button_state[ck]=lfo_do_next_step[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][1];
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_next_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_next_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 6://Up/Down
      check_button_state[ck]=lfo_cycle_steps[iCat_affectation_bouton_value_is[iCatPageis][ck]-1];
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_ar_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_ar_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 7://LOCK
      check_button_state[ck]=FaderLocked[iCat_affectation_bouton_value_is[iCatPageis][ck]-1];
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lock_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lock_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 8://FLASH
      check_button_state[ck]=FaderIsFlash[iCat_affectation_bouton_value_is[iCatPageis][ck]-1];
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_flash_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_flash_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 9://loop a dock
      check_button_state[ck]=
      is_dock_for_lfo_selected[fis][(dock_used_by_fader_is[fis])];
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/loop_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/loop_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;

      case 11://Play embeded

      switch(DockTypeIs[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]])
      {
      case 6:
      check_button_state[ck]= player_is_playing[DockHasAudioVolume[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]-1];
      break;
      case 7:
      check_button_state[ck]= player_is_playing[DockHasAudioPan[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]-1];
      break;
      case 8:
      check_button_state[ck]= player_is_playing[DockHasAudioPitch[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]-1];
      break;
      case 11:
      check_button_state[ck]= chaser_is_playing[ChaserAffectedToDck[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]];
      break;
      case 12:
      check_button_state[ck]= grider_is_playing[faders_dock_grid_affectation[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]];
      break;
      default: break;
      }

      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/play_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/play_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      case 13://Loop chaser
      fis=iCat_affectation_bouton_value_is[iCatPageis][ck]-1;

      switch(DockTypeIs[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]])
      {
      case 6:
      check_button_state[ck]=  player_is_onloop[DockHasAudioVolume[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]-1];
      break;
      case 7:
      check_button_state[ck]=  player_is_onloop[DockHasAudioPan[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]-1];
      break;
      case 8:
      check_button_state[ck]=  player_is_onloop[DockHasAudioPitch[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]-1];
      break;
      case 11:
      check_button_state[ck]= chaser_is_in_loop[ChaserAffectedToDck[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]];
      break;
      case 12:
      check_button_state[ck]= grider_autostopmode[faders_dock_grid_affectation[iCat_affectation_bouton_value_is[iCatPageis][ck]-1][dock_used_by_fader_is[iCat_affectation_bouton_value_is[iCatPageis][ck]-1]]];
      break;
      default: break;
      }
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/loop_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/loop_on.jpg",ck);
      break;
      default: break;
      }
      }
      break;
      default:
      strcpy(StrOrderToiCat,"");
      break;
      }

break;
//fin faders

case 2://minifaders
int num_mf;
     switch(iCat_affectation_bouton_action_is[iCatPageis][ck])
     {
//rien a checker dans les états, sauf la sélection déselection de minifaders
       case 16:
       num_mf=iCat_affectation_bouton_value_is[iCatPageis][ck]-1;
       if(num_mf>=0 && num_mf<48)
       {
       check_button_state[ck]= minifaders_selected[num_mf] ;
                    if(before_check_button_state[ck]!=check_button_state[ck])
                    {
                      switch(check_button_state[ck])
                      {
                       case 0:
                       sprintf(StrOrderToiCat,"model MFnum%d color 1.0 1.0 1.0",ck);
                       break;
                       case 1:
                       sprintf(StrOrderToiCat,"model MFnum%d color 1.0 0.0 0.0",ck);
                       break;
                       default: break;
                     }
                   }
      }
      break;
      case 20://lock preset
      num_mf=iCat_affectation_bouton_value_is[iCatPageis][ck]-1;
       if(num_mf>=0 && num_mf<8)
       {
       check_button_state[ck]= lock_preset[num_mf] ;
                    if(before_check_button_state[ck]!=check_button_state[ck])
                    {
                      switch(check_button_state[ck])
                      {
                       case 0:
                       sprintf(StrOrderToiCat,"model MFnum%d color 1.0 1.0 1.0",ck);
                       break;
                       case 1:
                       sprintf(StrOrderToiCat,"model MFnum%d color 0.0 0.4 0.3",ck);
                       break;
                       default: break;
                     }
                   }
      }
      break;
   default:
   break;
   }

break;
////FIN minifaders



case 3://sequences
switch(iCat_affectation_bouton_action_is[iCatPageis][ck])
     {
      case 0://desafected
      break;
      case 1: //GO
      check_button_state[ck]=index_go ;

      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(index_go)
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/go_off.jpg",ck);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/go_on.jpg",ck);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      default: break;
      }
      }

      if(index_pause==1 && index_go_back==0)
      {
      sprintf(StrOrderToiCat, "model tBut%d color %.1f 0.0 0.0",ck,1.0);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      else
      {
      sprintf(StrOrderToiCat, "model tBut%d color 1.0 1.0 1.0",ck);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      break;
      case 2://GO BACK
      check_button_state[ck]=index_go_back ;
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
      switch(check_button_state[ck])
      {
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/goback_off.jpg",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/goback_on.jpg",ck);
      break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      if( index_go_back==1)
      {
      switch(index_pause)
      {
      case 0:
      sprintf(StrOrderToiCat, "model tBut%d color 1.0 1.0 1.0",ck);
      break;
      case 1:
      sprintf(StrOrderToiCat, "model tBut%d color 1.0 0.0 0.0",ck);
      break;
      default:
      break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      }
      break;
      default:
      break;
      }
break;
//Fin sequences

case 4://EMULATE

     switch(iCat_affectation_bouton_action_is[iCatPageis][ck])
     {
      case 26://"F1");
      check_button_state[ck]=index_do_dock ;
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
       switch( index_do_dock)
      {
      case 0: sprintf(StrOrderToiCat, "model SimB%d color 1.0 1.0 1.0",ck); break;
      case 1: sprintf(StrOrderToiCat, "model SimB%d color 1.0 0.0 0.0",ck); break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      break;
      case 27://"F2");
      check_button_state[ck]=index_do_modify ;
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
       switch( index_do_modify)
      {
      case 0: sprintf(StrOrderToiCat, "model SimB%d color 1.0 1.0 1.0",ck); break;
      case 1: sprintf(StrOrderToiCat, "model SimB%d color 1.0 0.0 0.0",ck); break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      break;
      case 28://"F3");
      check_button_state[ck]=index_do_report ;
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
       switch( index_do_report)
      {
      case 0: sprintf(StrOrderToiCat, "model SimB%d color 1.0 1.0 1.0",ck); break;
      case 1: sprintf(StrOrderToiCat, "model SimB%d color 1.0 0.0 0.0",ck); break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      break;
      case 29://"F4");
      check_button_state[ck]=index_main_clear ;
      if(before_check_button_state[ck]!=check_button_state[ck])
      {
       switch( index_main_clear)
      {
      case 0: sprintf(StrOrderToiCat, "model SimB%d color 1.0 1.0 1.0",ck); break;
      case 1: sprintf(StrOrderToiCat, "model SimB%d color 1.0 0.0 0.0",ck); break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      break;
      case 30://"F11");
      break;
      case 31://"F12");
      break;
      case 32://"SHFT");
      switch( index_false_shift)
      {
      case 0: sprintf(StrOrderToiCat, "model SimB%d color 1.0 1.0 1.0",ck); break;
      case 1: sprintf(StrOrderToiCat, "model SimB%d color 1.0 0.0 0.0",ck); break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      case 33://"CTRL");
      switch( index_false_control)
      {
      case 0: sprintf(StrOrderToiCat, "model SimB%d color 1.0 1.0 1.0",ck); break;
      case 1: sprintf(StrOrderToiCat, "model SimB%d color 1.0 0.0 0.0",ck); break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;


      default://
      break;
     }


break;
case 5://banger
switch(iCat_affectation_bouton_action_is[iCatPageis][ck])
     {
     case 0:
     break;
     case 1://bang solo
     check_button_state[ck]=bang_is_sended[(iCat_affectation_bouton_value_is[iCatPageis][ck]-1)];
     if(before_check_button_state[ck]!=check_button_state[ck])
     {
     switch(check_button_state[ck])
      {
      case 1:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/rond_banger_off.png",ck);
      break;
      case 0:
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/rond_banger_on.png",ck);
      break;
      default: break;
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
     default:
     break;
     }


break;

//Fin emulate
case 6://icat commandes
 switch(iCat_affectation_bouton_action_is[iCatPageis][ck])
     {
     case 3://page iCat num selectionnnee
     if(iCatPageis!=oldiCatPageis)
     {
     if(iCatPageis==iCat_affectation_bouton_value_is[iCatPageis][ck]-1)
     {
     sprintf(StrOrderToiCat, "model SimB%d color 1.0 0.0 0.0",ck) ;
     }
     else {sprintf(StrOrderToiCat, "model SimB%d color 1.0 1.0 1.0",ck);}
     nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
     }
     oldiCatPageis=iCatPageis;
     break;
     default://
     break;
     }
break;
case 7://draw

      switch(iCat_affectation_bouton_action_is[iCatPageis][ck])
      {
       case 1://"Brush Type" selected
      if(draw_brush_type[draw_preset_selected]!=previous_draw_brush_type[draw_preset_selected] || draw_preset_selected!=previous_draw_preset_selected )
      {
         switch(draw_brush_type[draw_preset_selected])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_point.jpg",ck);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_gpl.jpg",ck);
         break;
         default:
         break;
         }
         nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }

      break;
      case 2://draw_mode selected
      if(draw_mode[draw_preset_selected]!=previous_draw_mode[draw_preset_selected] || draw_preset_selected!=previous_draw_preset_selected)
      {
      switch(draw_mode[draw_preset_selected])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_draw.jpg",ck);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_erase.jpg",ck);
         break;
         case 2:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_solo.jpg",ck);
         break;
         case 3:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_ghost.jpg",ck);
         break;
         default:
         break;
         }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }

      break;

      case 3://"Brush Type" par valeur de matrice
      if(draw_brush_type[(iCat_affectation_bouton_value_is[iCatPageis][ck]-1)]!=previous_draw_brush_type[(iCat_affectation_bouton_value_is[iCatPageis][ck]-1)] || draw_preset_selected!=previous_draw_preset_selected)
      {
         switch(draw_brush_type[(iCat_affectation_bouton_value_is[iCatPageis][ck]-1)])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_point.jpg",ck);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_gpl.jpg",ck);
         break;
         default:
         break;
         }
         nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      break;
      case 4://draw_mode par valeur de matrice
      if(draw_mode[(iCat_affectation_bouton_value_is[iCatPageis][ck]-1)]!=previous_draw_mode[(iCat_affectation_bouton_value_is[iCatPageis][ck]-1)] || draw_preset_selected!=previous_draw_preset_selected)
      {
      switch(draw_mode[(iCat_affectation_bouton_value_is[iCatPageis][ck]-1)])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_draw.jpg",ck);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_erase.jpg",ck);
         break;
         case 2:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_solo.jpg",ck);
         break;
         case 3:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_ghost.jpg",ck);
         break;
         default:
         break;
         }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      break;

      case 5://preset matrix
      if(draw_preset_selected!=previous_draw_preset_selected)
      {
      if( (iCat_affectation_bouton_value_is[iCatPageis][ck]-1 )==draw_preset_selected )
      {
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_preset_selected.png",ck);
      }
      else {sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_preset_vide.png",ck);}
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      //rafraichissement de la page icat des déclarations car les tailles de colonnes les circuits  etc changent !
      refresh_icatpage_please=1;;
      }

      //pas de previous ici car il y a plusieurs presets
      break;
      default:
      break;
      }
break;
default:
break;
}



if(before_check_button_state[ck]!=check_button_state[ck])
{
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
before_check_button_state[ck]=check_button_state[ck];
}

//hors boucle des boutons
previous_draw_preset_selected=draw_preset_selected;
for(int i=0;i<6;i++)
{
previous_draw_brush_type[i]=draw_brush_type[i];
previous_draw_mode[i]=draw_mode[i];
}
 return(0);
}




int To_iCat_DrawSlider(int id, int x1,int y1, int affectation, int valeur_sl)
{

int draw_largeur=0; int draw_hauteur=0;
sprintf(StrOrderToiCat,"model slider%d image http://www.le-chat-noir-numerique.fr/iCat/slider.jpg",id);
nbrbytessendediCat=sendto(sockiCat,StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

switch ( iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model slider%d scale %.1f %d 0",id,0.125*(ratio_iCat_slider[iCatPageis][id]),(ratio_iCat_slider[iCatPageis][id]));//0.125=1/16 * largeur 8
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
draw_largeur=iCatSlidersizeX; draw_hauteur=iCatSlidersizeY;
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model slider%d rotate 0 90 0",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat,"model slider%d scale %d %.1f 0",id,(ratio_iCat_slider[iCatPageis][id]),0.125*(ratio_iCat_slider[iCatPageis][id]));//0.125=1/16 * largeur 8
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
draw_largeur=iCatSlidersizeY; draw_hauteur=iCatSlidersizeX;
break;
default: break;
}

sprintf(StrOrderToiCat,"model slider%d position %d %d 0",id, (x1*2)+((draw_largeur*ratio_iCat_slider[iCatPageis][id])/2), (y1*2)+((draw_hauteur*ratio_iCat_slider[iCatPageis][id])/2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

float col_fader_r=0.9, col_fader_g=0.5, col_fader_b=0.0;
int value=0;
switch(affectation)
{
case 1://faders
if(valeur_sl>=0 && valeur_sl<=48)
{
switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

if(FaderLocked[valeur_sl-1]==0)
{
  switch(DockTypeIs[valeur_sl-1][(dock_used_by_fader_is[valeur_sl-1])])
  {
               case 6://audio vol
               col_fader_r=0.0, col_fader_g=0.0, col_fader_b=0.6;
               break;
               case 7://audio pan
               col_fader_r=0.0, col_fader_g=0.0, col_fader_b=0.6;
               break;
               case 8://audio pitch
               col_fader_r=0.0, col_fader_g=0.0, col_fader_b=0.6;
               break;
               case 11://fx
               col_fader_r=0.0, col_fader_g=0.8, col_fader_b=0.0;
               break;
               case 12://grid
               col_fader_r=1.0, col_fader_g=0.0, col_fader_b=0.0;
               break;
               case 13://fx group
               col_fader_r=0.8, col_fader_g=0.8, col_fader_b=0.0;
               break;
               case 14://mover
               col_fader_r=0.5, col_fader_g=0.0, col_fader_b=0.7;
               break;
               case 15://draw
               col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
               break;
               case 16://echo
               col_fader_r=0.2, col_fader_g=0.6, col_fader_b=1.0;
               break;
               default://faders oranges
               col_fader_r=0.9, col_fader_g=0.5, col_fader_b=0.0;
               break;
  }
}
else
{//locké
  col_fader_r=0.0, col_fader_g=0.4, col_fader_b=0.2;
}


sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id, col_fader_r, col_fader_g, col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//num de slider
sprintf(StrOrderToiCat, "model t%d text %d",id, valeur_sl);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(5*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//afffichage niveau + loop dock
if(dmx_view==0){
//dock loop
if(is_dock_for_lfo_selected[valeur_sl-1][dock_used_by_fader_is[valeur_sl-1]]==1)
{
sprintf(StrOrderToiCat, "model tlev%d text %d *",id, (int)((float)(Fader[valeur_sl-1])/2.55));
}
else
{
sprintf(StrOrderToiCat, "model tlev%d text %d",id, (int)((float)(Fader[valeur_sl-1])/2.55));
}
}
else {
//dock loop
if(is_dock_for_lfo_selected[valeur_sl-1][dock_used_by_fader_is[valeur_sl-1]]==1)
{
sprintf(StrOrderToiCat, "model tlev%d text %d *",id, Fader[valeur_sl]);
}
else
{
sprintf(StrOrderToiCat, "model tlev%d text %d",id, Fader[valeur_sl]);
}
}
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat, "model tdes%d text %s",id,DockName[valeur_sl-1][dock_used_by_fader_is[valeur_sl-1]] );
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tdes%d position %d %d 0",id, (x1*2)-5, (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tdes%d rotate -90 0 0 1",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tdes%d font %s",id,iphone_fonts[5]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tdes%d fontsize 15",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


}
break;

case 2://speed fader
if(valeur_sl>=0 && valeur_sl<=48)
{
switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
col_fader_r=0.9, col_fader_g=0.5, col_fader_b=0.0;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id, col_fader_r, col_fader_g, col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//num acelero
sprintf(StrOrderToiCat, "model t%d text S.%d",id, valeur_sl);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 16",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//niveau accel
sprintf(StrOrderToiCat, "model tlev%d text %d",id, lfo_speed[valeur_sl-1]-64);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
}
break;

case 3://sequenciel /1: stage /2: preset /3: accelero
switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//x1 x2 accel description
switch(iCat_affectation_slider_value_is[iCatPageis][id])
{
case 0:
sprintf(StrOrderToiCat, "model t%d text St",id);
break;
case 1:
sprintf(StrOrderToiCat, "model t%d text Pst",id);
break;
case 2:
sprintf(StrOrderToiCat, "model t%d text Sp",id);
break;
default: break;
}
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

break;

case 4://grand master

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUE FADER
col_fader_r=0.7, col_fader_g=0.0, col_fader_b=0.0;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//text
sprintf(StrOrderToiCat, "model t%d text GM",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(10*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;

case 5://level wheel

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUE FADER
col_fader_r=0.0, col_fader_g=0.7, col_fader_b=0.7;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//text
sprintf(StrOrderToiCat, "model t%d text LvA",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(10*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//affichage niveau
if(dmx_view==0){
        sprintf(StrOrderToiCat, "model tlev%d text %d",id, (int)((float)(absolute_level_wheel)/2.55)); }
        else {sprintf(StrOrderToiCat, "model tlev%d text %d",id, absolute_level_wheel); }
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;

case 6://mover params


switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUE FADER
col_fader_r=0.5, col_fader_g=0.0, col_fader_b=0.7;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//text
sprintf(StrOrderToiCat, "model t%d text MoV%d",id, id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tl%d position %d %d 0",id, (x1*2)-(10*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


switch(tracker_16b_edit)
{
case 0:
 value= mover_params[valeur_sl-1][0];
break;
case 1:
 value= mover_params[valeur_sl-1][1];
break;
default: break;
}
//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d text %d",id,value);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

break;

case 7: //DRAW PRESSURE

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUR FADER
col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//text
sprintf(StrOrderToiCat, "model t%d text P%d",id, iCat_affectation_slider_value_is[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(5*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d text %d",id,(int)(draw_level_to_do[(iCat_affectation_slider_value_is[iCatPageis][id]-1)]*127));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 8: //DRAW ANGLE

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUR FADER
col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//text
sprintf(StrOrderToiCat, "model t%d text D%d",id, iCat_affectation_slider_value_is[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(5*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d text %d",id,(int)(draw_damper_decay_factor[(iCat_affectation_slider_value_is[iCatPageis][id]-1)]*127));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 9: //DRAW Ghost

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUR FADER
col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//text
sprintf(StrOrderToiCat, "model t%d text G%d",id, iCat_affectation_slider_value_is[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(5*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d text %d",id,(int)(draw_ghost_to_do[(iCat_affectation_slider_value_is[iCatPageis][id]-1)]*127));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;

//ACTIFS

case 10: //DRAW PRESSURE SELECTED

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUR FADER
col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//text
sprintf(StrOrderToiCat, "model t%d text P%d",id, draw_preset_selected+1);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(5*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d text %d",id,(int)(draw_level_to_do[draw_preset_selected]*127));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 11: //DRAW ANGLE SELECTED

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUR FADER
col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//text
sprintf(StrOrderToiCat, "model t%d text D%d",id, draw_preset_selected+1);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(5*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d text %d",id,(int)(draw_damper_decay_factor[draw_preset_selected]*127));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 12: //DRAW Ghost

switch (iCat_orientation_slider[iCatPageis][id])
{
case 0://vertical
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]),
(x1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]),(y1*2)+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
case 1://horizontal
sprintf(StrOrderToiCat,"model level%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),(x1*2),(y1*2)+(iCatSlidersizeX*ratio_iCat_slider[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;
default: break;
}
sprintf(StrOrderToiCat,"model level%d width 100",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//COULEUR FADER
col_fader_r=0.0, col_fader_g=1.0, col_fader_b=0.9;
sprintf(StrOrderToiCat,"model level%d color %.1f %.1f %.1f",id,col_fader_r,col_fader_g,col_fader_b);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//text
sprintf(StrOrderToiCat, "model t%d text G%d",id, draw_preset_selected+1);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d position %d %d 0",id, (x1*2)-(5*ratio_iCat_slider[iCatPageis][id]), (y1*2)-5);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d font %s",id,iphone_fonts[6]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model t%d fontsize 20",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage niveau
sprintf(StrOrderToiCat, "model tlev%d text %d",id,(int)(draw_ghost_to_do[draw_preset_selected]*127));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+(10*ratio_iCat_slider[iCatPageis][id]), (y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tlev%d fontsize 12",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;


default:
break;
}

//affichages connexes: déplcement des affichages, si horizontal
if( iCat_orientation_slider[iCatPageis][id]==1)
{
  sprintf(StrOrderToiCat, "model t%d position %d %d 0",id,(x1*2)+10+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]), (y1*2)+(5*ratio_iCat_slider[iCatPageis][id]));
  nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
  sprintf(StrOrderToiCat, "model tlev%d position %d %d 0",id,(x1*2)+10+(iCatSlidersizeY*ratio_iCat_slider[iCatPageis][id]), (y1*2)+(15*ratio_iCat_slider[iCatPageis][id]));
  nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
  sprintf(StrOrderToiCat, "model tdes%d rotate 0 0 0 1",id);
  nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
  sprintf(StrOrderToiCat, "model tdes%d position %d %d 0",id,(x1*2), (y1*2));
  nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

}




return(0);
}







int To_iCat_DrawButton(int id, int x1,int y1, int affectation, int action, int valeur_b)
{
char string_temp_familly[25];
char string_temp_id[25];
char string_mf_id[25];
int decalagex=0;
int decalagey=0;
switch(iCat_affectation_bouton_type_is[iCatPageis][id])
{
case 0://desafected
sprintf(string_temp_familly,"-");
break;
case 1: //faders
sprintf(string_temp_id,"%d",iCat_affectation_bouton_value_is[iCatPageis][id]);
     switch(iCat_affectation_bouton_action_is[iCatPageis][id])
     {
     case 0://desafected
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/button.jpg",id);
      break;
      case 1: //fader up
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_up_off.jpg",id);
      break;
      case 2://fader down
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_down_off.jpg",id);
      break;
      case 3://Fader saw
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_saw_off.jpg",id);
      break;
      case 4://prev dock
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_prev_off.jpg",id);
      break;
      case 5://next dock
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_next_off.jpg",id);
      break;
      case 6://aller retour
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_ar_off.jpg",id);
      break;
      case 7://lock
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lock_off.jpg",id);
      break;
      case 8://flash
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/lfo_flash_off.jpg",id);
      break;

      case 9://loop a dock
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/loop_off.jpg",id);
      break;
      case 10://loop all dock
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/loopall_off.jpg",id);
      break;
      case 11://play embeded chaser
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/play_off.jpg",id);
      break;
      case 12://seek embeded chaser
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/seek_off.jpg",id);
      break;
      case 13://loop embeded chaser
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/loop_off.jpg",id);
      break;
      default:
      break;
      }
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//affichage param button
sprintf(StrOrderToiCat,"model tBut%d text %s",id,string_temp_id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d position %d %d 0",id,(x1*2)+(2*ratio_iCat_button[iCatPageis][id]), (y1*2)+(ratio_iCat_button[iCatPageis][id]*(largueur_bouton)));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d font %s",id,iphone_fonts[5]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d fontsize %d",id, 10*ratio_iCat_button[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

break;
      //fin faders

     case 2://minifaders
     switch(iCat_affectation_bouton_action_is[iCatPageis][id])
     {
     case 0://desafected
      break;
      case 1: //fader up
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lfo_up_off.jpg",id);
      break;
      case 2://fader down
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lfo_down_off.jpg",id);
      break;
      case 3://Fader saw
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lfo_saw_off.jpg",id);
      break;
      case 4://"ToPREVDoid");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lfo_prev_off.jpg",id);
      break;
      case 5://"ToNEXTDoid");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lfo_next_off.jpg",id);
      break;
      case 6://"Up/Down");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lfo_ar_off.jpg",id);
      break;
      case 7://"LOCK");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lock_off.jpg",id);
      break;
      case 8://"FLASH");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lfo_flash_off.jpg",id);
      break;
      case 9://"L/Unloop doid");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_loop_off.jpg",id);
      break;
      case 10://"L/Unloop all");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_loopall_off.jpg",id);
      break;
      case 11://"Dock -");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_bt_dockminus.jpg",id);
      break;
      case 12://"Dock +");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_bt_dockplus.jpg",id);
      break;
      case 13://"Play eCHASER");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_play_off.jpg",id);
      break;
      case 14://all at 0
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/at_zero.jpg",id);
      break;
      case 15://Set pos
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_setpos.jpg",id);
      break;
      case 16://"Select M.Fader");
      sprintf(string_mf_id,"%d",iCat_affectation_bouton_value_is[iCatPageis][id]);
      sprintf(StrOrderToiCat,"model MFnum%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton))/2)-10, (y1*2)+((ratio_iCat_button[iCatPageis][id]*(20+largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d fontsize %d",id, 18*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_bt_carre_vide.png",id);
      break;
      case 17://Unselect all
      sprintf(string_mf_id,"UnS");
      sprintf(StrOrderToiCat,"model MFnum%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton-20))/2), (y1*2)+10+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d fontsize %d",id, 12*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_bt_carre_vide.png",id);
      break;
      case 18://select all
      sprintf(string_mf_id,"ALL");
      sprintf(StrOrderToiCat,"model MFnum%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton-20))/2), (y1*2)+10+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d fontsize %d",id, 12*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_bt_carre_vide.png",id);
      break;
      case 19://"Select M.FaderPst");
      sprintf(string_temp_id,"MF.pst");
      sprintf(string_mf_id,"%d",iCat_affectation_bouton_value_is[iCatPageis][id]);
      sprintf(StrOrderToiCat,"model MFnum%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton))/2)-10, (y1*2)+((ratio_iCat_button[iCatPageis][id]*(20+largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d fontsize %d",id, 18*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_sel_pst.png",id);
      break;
      case 20://"Select Lock preset");
      sprintf(string_temp_id,"LCK.pst");
      sprintf(string_mf_id,"%d",iCat_affectation_bouton_value_is[iCatPageis][id]);
      sprintf(StrOrderToiCat,"model MFnum%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton))/2)-10, (y1*2)+((ratio_iCat_button[iCatPageis][id]*(20+largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model MFnum%d fontsize %d",id, 18*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/mf_lck_pst.png",id);
      break;

      default:
      break;
      }
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage param button
sprintf(StrOrderToiCat, "model tBut%d position %d %d 0",id,(x1*2), (y1*2)+20+(ratio_iCat_button[iCatPageis][id]*(largueur_bouton+5)));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d fontsize %d",id, 10*ratio_iCat_button[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      break;
//fin minifaders
      case 3://sequences
      decalagey=0;decalagex=0;
      switch(iCat_affectation_bouton_action_is[iCatPageis][id])
     {
      case 1:
      sprintf(string_temp_id,"GO");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/go_off.jpg",id);
      decalagex=7;
      decalagey=30;
      break;
      case 2:
      sprintf(string_temp_id,"Back");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/goback_off.jpg",id);
      decalagey=30;
      decalagex=5;
      break;
      case 3:
      strcpy(string_temp_id,"");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/jump_off.jpg",id);
      decalagey=30;
      decalagex=5;
      break;
      case 4:
      sprintf(string_temp_id,"St-");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/bt_carre_vide.png",id);
      decalagex=10;decalagey=5;
      break;
      case 5:
      sprintf(string_temp_id,"St+");
       sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/bt_carre_vide.png",id);
      decalagex=10;decalagey=5;
      break;
      case 6:
      sprintf(string_temp_id,"PsT -");
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/bt_carre_vide.png",id);
      decalagex=5; decalagey=5;
      break;
      case 7:
      sprintf(string_temp_id,"PsT +");
       sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/bt_carre_vide.png",id);
      decalagex=5;decalagey=5;
      break;
      case 8:
      sprintf(string_temp_id,"Goto");
       sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/bt_carre_vide.png",id);
      decalagex=5;decalagey=5;
      break;
      default:
      strcpy(string_temp_id,"");
      break;
      }
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage param button
sprintf(StrOrderToiCat,"model tBut%d text %s",id,string_temp_id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d position %d %d 0",id,(x1*2)+(  decalagex*ratio_iCat_button[iCatPageis][id]), (y1*2)+(ratio_iCat_button[iCatPageis][id]*((largueur_bouton/2)+ decalagey)));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model tBut%d fontsize %d",id, 10*ratio_iCat_button[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

break;
//fin sequences

//emulate Kbd
case 4:
decalagex=0;

     switch(iCat_affectation_bouton_action_is[iCatPageis][id])
     {
      case 0:
      sprintf(string_mf_id,"0");
      break;
      case 1:
      sprintf(string_mf_id,"1");
      break;
      case 2:
      sprintf(string_mf_id,"2");
      break;
      case 3:
      sprintf(string_mf_id,"3");
      break;
      case 4:
      sprintf(string_mf_id,"4");
      break;
      case 5:
      sprintf(string_mf_id,"5");
      break;
      case 6:
      sprintf(string_mf_id,"6");
      break;
      case 7:
      sprintf(string_mf_id,"7");
      break;
      case 8:
      sprintf(string_mf_id,"8");
      break;
      case 9:
      sprintf(string_mf_id,"9");
      break;
      case 10:
      sprintf(string_mf_id,".");
      break;
      case 11:
      sprintf(string_mf_id,"+");
      break;
      case 12:
      sprintf(string_mf_id,"-");
      break;
      case 13:
      sprintf(string_mf_id,"ALL");
      decalagex=10;
      break;
      case 14:
      sprintf(string_mf_id,"INV");
      decalagex=10;
      break;
      case 15:
      sprintf(string_mf_id,"TAB");
      decalagex=10;
      break;
      case 16:
      sprintf(string_mf_id,"ESC");
      decalagex=10;
      break;
      case 17:
      sprintf(string_mf_id,"ENT");
      decalagex=10;
      break;
      case 18:
      sprintf(string_mf_id,"/100");
      decalagex=15;
      break;
      case 19:
      sprintf(string_mf_id,"/0");
      break;
      case 20://backspace
      sprintf(string_mf_id,"BCKS");
      decalagex=20;
      break;
      case 21://DEL
      sprintf(string_mf_id,"DEL");
      decalagex=10;
      break;
      case 22://arrow Up
      sprintf(string_mf_id,"UP");
      break;
      case 23://arrow down
      sprintf(string_mf_id,"DWN");
      decalagex=15;
      break;
      case 24://arrow left
      sprintf(string_mf_id,"LEFT");
      decalagex=15;
      break;
      case 25://arrow right
      sprintf(string_mf_id,"RGHT");
      decalagex=15;
      break;
      case 26:
      sprintf(string_mf_id,"F1");
      break;
      case 27:
      sprintf(string_mf_id,"F2");
      break;
      case 28:
      sprintf(string_mf_id,"F3");
      break;
      case 29:
      sprintf(string_mf_id,"F4");
      break;
      case 30:
      sprintf(string_mf_id,"F11");
      break;
      case 31:
      sprintf(string_mf_id,"F12");
      break;
      case 32:
      sprintf(string_mf_id,"SHFT");
      decalagex=15;
      break;
      case 33:
      sprintf(string_mf_id,"CTRL");
      decalagex=15;
      break;
      default:
      break;
     }

      sprintf(StrOrderToiCat,"model SimB%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton-10-decalagex))/2), (y1*2)+((10+(ratio_iCat_button[iCatPageis][id]*largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d fontsize %d",id, 10*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/bt_carre_vide.png",id);
break;
//fin emulate
case 5://banger
      decalagex=0;
      sprintf(string_mf_id,"%d",iCat_affectation_bouton_value_is[iCatPageis][id]);
      sprintf(StrOrderToiCat,"model SimB%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton-15-decalagex))/2), (y1*2)+((20+(ratio_iCat_button[iCatPageis][id]*largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d fontsize %d",id, 10*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      decalagex=largueur_bouton;
      sprintf(StrOrderToiCat,"model DescB%d text %s",id,bangers_name[(iCat_affectation_bouton_value_is[iCatPageis][id]-1)]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model DescB%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton-decalagex))/2), (y1*2)+((20+(ratio_iCat_button[iCatPageis][id]*largueur_bouton))));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model DescB%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model DescB%d fontsize %d",id, 5*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/rond_banger_off.png",id);


break;

case 6://icat commandes
      switch(iCat_affectation_bouton_action_is[iCatPageis][id])
     {
      case 1:
      sprintf(string_mf_id,"-");
      break;
      case 2:
      sprintf(string_mf_id,"+");
      break;
      case 3:
      sprintf(string_mf_id,"%d",iCat_affectation_bouton_value_is[iCatPageis][id]);
      break;
      case 4:
      sprintf(string_mf_id,"R");
      break;
      case 5:
      sprintf(string_mf_id,"O");
      break;
      default:
      break;
      }

      sprintf(StrOrderToiCat,"model SimB%d text %s",id,string_mf_id);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d position %d %d 0",id,(x1*2)+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton))/2), (y1*2)+15+((ratio_iCat_button[iCatPageis][id]*(largueur_bouton))/2));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model SimB%d fontsize %d",id, 20*ratio_iCat_button[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/bt_iCat.png",id);
break;
case 7://DRAW

      switch(iCat_affectation_bouton_action_is[iCatPageis][id])
      {
      case 1://"Brush Type"); selected
         switch(draw_brush_type[draw_preset_selected])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_point.jpg",id);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_gpl.jpg",id);
         break;
         default:
         break;
         }
      break;
      case 2://draw_mode selected
      switch(draw_mode[draw_preset_selected])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_draw.jpg",id);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_erase.jpg",id);
         break;
         case 2:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_solo.jpg",id);
         break;
         case 3:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_ghost.jpg",id);
         break;
         default:
         break;
         }
      break;
            case 3://"Brush Type"); by matrice
         switch(draw_brush_type[(iCat_affectation_bouton_value_is[iCatPageis][id]-1)])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_point.jpg",id);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_gpl.jpg",id);
         break;
         default:
         break;
         }
      break;
      case 4://draw_mode by matrice
      switch(draw_mode[(iCat_affectation_bouton_value_is[iCatPageis][id])])
         {
         case 0:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_draw.jpg",id);
         break;
         case 1:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_erase.jpg",id);
         break;
         case 2:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_solo.jpg",id);
         break;
         case 3:
         sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_mode_ghost.jpg",id);
         break;
         default:
         break;
         }
      break;
      case 5://preset draw

      if(iCat_affectation_bouton_value_is[iCatPageis][id]-1==draw_preset_selected)
      {
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_preset_selected.png",id);
      }
      else
      {
      sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/draw_preset_vide.png",id);
      }
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat,"model TDrawPst%d text %d",id,iCat_affectation_bouton_value_is[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat, StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      sprintf(StrOrderToiCat, "model TDrawPst%d position %d %d 0",id,(x1*2)+(2*ratio_iCat_button[iCatPageis][id]), (y1*2)+(ratio_iCat_button[iCatPageis][id]*(largueur_bouton)));
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model TDrawPst%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(StrOrderToiCat, "model TDrawPst%d fontsize %d",id, 18*ratio_iCat_button[iCatPageis][id]);

      break;
      default:
      break;
      }
break;
default:
break;
}

nbrbytessendediCat=sendto(sockiCat,StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model button%d scale %.1f %.1f 0",id, 0.25*ratio_iCat_button[iCatPageis][id], 0.25*ratio_iCat_button[iCatPageis][id]);//0.25=128/32
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat,"model button%d position %d %d 0",id,  (x1*2)+((largueur_bouton*ratio_iCat_button[iCatPageis][id])/2), (y1*2)+((largueur_bouton*ratio_iCat_button[iCatPageis][id])/2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

return(0);
}

int To_iCat_DrawTrackingZone(int id, int x1,int y1, int xtrackertodraw, int ytrackertodraw)
{
int aire=0;


switch(iCat_trackzone_type_is[iCatPageis][id])
{
case 1://MOver

//cible
sprintf(StrOrderToiCat,"model trackzoneE%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/2),
(x1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]),(y1*2)+((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat,"model trackzoneE%d color 0.4, 0.4, 0.4",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model trackzoneF%d xyz %d %d 0 %d %d 0",id,
(x1*2)+((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/2), (y1*2),
(x1*2)+((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/2),(y1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat,"model trackzoneF%d color 0.4, 0.4, 0.4",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model trackPosition%d image http://www.le-chat-noir-numerique.fr/iCat/rond_banger_on.png",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat,"model trackPosition%d scale %.1f %.1f 0",id, 0.2*ratio_iCat_trackzone[iCatPageis][id], 0.2*ratio_iCat_trackzone[iCatPageis][id]);//0.25=128/32
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model trackPosition%d position %d %d 0",id,(x1*2)+xtrackertodraw, (y1*2)+ytrackertodraw);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
char string_mf_id[16];
sprintf(string_mf_id,"%d-%d",xtrackertodraw,ytrackertodraw);
sprintf(StrOrderToiCat,"model trackTextPos%d text %s",id,string_mf_id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model trackTextPos%d position %d %d 0",id,(x1*2), (y1*2)-(1*ratio_iCat_trackzone[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model trackTextPos%d font %s",id,iphone_fonts[5]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model trackTextPos%d fontsize %d",id, 10*ratio_iCat_trackzone[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
break;

case 2://draw"Draw Activ");
sprintf(StrOrderToiCat,"model DrawAera%dTitle text %s",id,"Draw Activ");
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model DrawAera%dTitle position %d %d 0",id,(x1*2), (y1*2)-(1*ratio_iCat_trackzone[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model DrawAera%dTitle font %s",id,iphone_fonts[5]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model DrawAera%dTitle fontsize %d",id, 8*ratio_iCat_trackzone[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);



//chaque aire déclarée
for(int lign=0;lign<draw_preset_parameters[draw_preset_selected][1];lign++)
{
for(int col=0;col<draw_preset_parameters[draw_preset_selected][0];col++)
{
int coordonnee=col+(lign*draw_preset_parameters[draw_preset_selected][0]);
sprintf(StrOrderToiCat,"model DrawAera%dOffstet%d xyz %d %d -1 %d %d -1 %d %d -1 %d %d -1",
id,coordonnee,
(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *col),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *lign),

(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *col),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(lign+1)),

(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(col+1)),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(lign+1)),

(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(col+1)),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(lign)));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model DrawAera%dOffstet%d render triangle_fan",id,coordonnee);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model DrawAera%dOffstet%d color 0. %.1f %.1f",id,coordonnee,
draw_preset_levels[draw_preset_selected][coordonnee]*1.0,draw_preset_levels[draw_preset_selected][coordonnee]*0.8);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(StrOrderToiCat,"model track%dNumCh%d text %d",id,coordonnee,draw_preset_channel_routing[draw_preset_selected][coordonnee]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat, "model track%dNumCh%d position %d %d 0",id,coordonnee,
(x1*2)+(int)(( (float)(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *col),
(y1*2)+(7*ratio_iCat_trackzone[iCatPageis][id])+(int)(( (float)(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(lign)) );

nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model track%dNumCh%d font %s",id,coordonnee,iphone_fonts[5]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model track%dNumCh%d fontsize %d",id,coordonnee, 6*ratio_iCat_trackzone[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


}
}



//curseur
sprintf(StrOrderToiCat,"model DrawAera%dCurseur xyz %d %d -0.5 %d %d -0.5 %d %d -0.5 %d %d -0.5",
id,
(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0])*draw_centre_x[draw_preset_selected] ),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1])*draw_centre_y[draw_preset_selected] ),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected])),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *draw_centre_y[draw_preset_selected]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(StrOrderToiCat,"model DrawAera%dCurseur render triangle_strip",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(StrOrderToiCat,"model DrawAera%dCurseur color 1.0 0. 0.",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);




break;
case 3://draw"Draw Matrix num");

aire=iCat_trackzone_affectation_is[iCatPageis][id]-1;
sprintf(StrOrderToiCat,"model DrawAera%dTitle text Draw Num %d",id,iCat_trackzone_affectation_is[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model DrawAera%dTitle position %d %d 0",id,(x1*2), (y1*2)-(1*ratio_iCat_trackzone[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model DrawAera%dTitle font %s",id,iphone_fonts[5]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model DrawAera%dTitle fontsize %d",id, 8*ratio_iCat_trackzone[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


for(int lign=0;lign<draw_preset_parameters[aire][1];lign++)
{
for(int col=0;col<draw_preset_parameters[aire][0];col++)
{
int coordonnee=col+(lign*draw_preset_parameters[aire][0]);
sprintf(StrOrderToiCat,"model DrawSelAera%dOffstet%d xyz %d %d -1 %d %d -1 %d %d -1 %d %d -1",
id,coordonnee,
(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][0]) *col),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][1]) *lign),

(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][0]) *col),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][1]) *(lign+1)),

(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][0]) *(col+1)),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][1]) *(lign+1)),

(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][0]) *(col+1)),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][1]) *(lign)));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model DrawSelAera%dOffstet%d render triangle_fan",id,coordonnee);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model DrawSelAera%dOffstet%d color 0. %.1f %.1f",id,coordonnee,
draw_preset_levels[aire][coordonnee]*1.0,draw_preset_levels[aire][coordonnee]*0.8);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(StrOrderToiCat,"model track%dNumCh%d text %d",id,coordonnee,draw_preset_channel_routing[aire][coordonnee]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat, "model track%dNumCh%d position %d %d 0",id,coordonnee,
(x1*2)+(int)(( (float)(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][0]) *col),
(y1*2)+(7*ratio_iCat_trackzone[iCatPageis][id])+(int)(( (float)(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[aire][1]) *(lign)) );

nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model track%dNumCh%d font %s",id,coordonnee,iphone_fonts[5]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat, "model track%dNumCh%d fontsize %d",id,coordonnee, 6*ratio_iCat_trackzone[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


}
}



//curseur
sprintf(StrOrderToiCat,"model DrawAera%dCurseur xyz %d %d -0.5 %d %d -0.5 %d %d -0.5 %d %d -0.5",
id,
(x1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0])*draw_centre_x[draw_preset_selected] ),
(y1*2)+(( (largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1])*draw_centre_y[draw_preset_selected] ),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected])),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *(draw_centre_y[draw_preset_selected]+1)),

(x1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][0]) *(draw_centre_x[draw_preset_selected]+1)),
(y1*2)+( ((largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id])/draw_preset_parameters[draw_preset_selected][1]) *draw_centre_y[draw_preset_selected]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(StrOrderToiCat,"model DrawAera%dCurseur render triangle_strip",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


sprintf(StrOrderToiCat,"model DrawAera%dCurseur color 1.0 0. 0.",id);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);




break;
default:
break;
}


//carré pourtour
sprintf(StrOrderToiCat,"model trackzoneA%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2),
(x1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]),(y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model trackzoneB%d xyz %d %d 0 %d %d 0",id,
(x1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]), (y1*2),
(x1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]),(y1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model trackzoneC%d xyz %d %d 0 %d %d 0",id,
(x1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]), (y1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]),
(x1*2),(y1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

sprintf(StrOrderToiCat,"model trackzoneD%d xyz %d %d 0 %d %d 0",id,
(x1*2), (y1*2)+(largeur_trackzone*ratio_iCat_trackzone[iCatPageis][id]),
(x1*2),(y1*2));
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


 return(0);
}

int To_iCat_DrawString(int id, int x1,int y1, int affectation, int action)
{
char string_to_send[296];
switch(iCat_affectation_string_type_is[iCatPageis][id])
{
case 1: //Feedback

     switch(iCat_affectation_string_action_is[iCatPageis][id])
     {
      case 1: //input
      sprintf(string_to_send,"model Str%d text -%s",id,string_numeric_entry);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      case 2://last ch
      sprintf(string_to_send,"model Str%d text -%s",id,string_last_ch);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      case 3://dimmers
      sprintf(string_to_send,"model Str%d text -%s",id,string_secondary_feeback);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      case 4://last order
      sprintf(string_to_send,"model Str%d text -%s",id,string_Last_Order);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      case 5://confirm string
      sprintf(string_to_send,"model Str%d text -%s",id,string_confirmation);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      default:
      strcpy(string_to_send,"");
      break;
      }
sprintf(string_to_send, "model Str%d position %d %d 0",id,(x1*2), (y1*2)+ ((12*2*ratio_iCat_string[iCatPageis][id])/2));
nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(string_to_send, "model Str%d font %s",id,iphone_fonts[0]);
nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(string_to_send, "model Str%d fontsize %d",id, 12*ratio_iCat_string[iCatPageis][id]);
nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);


      //fin feedback
break;
case 2: //string sequences
strcpy(string_to_send,"");
     switch(iCat_affectation_string_action_is[iCatPageis][id])
     {
     case 1://Stage
     //num
      sprintf(string_to_send,"model Str%d text %s",id,string_mem_onstage);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d position %d %d 0",id,(x1*2), (y1*2)+ ((14*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d fontsize %d",id, 14*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send,"model Str%d color 0.0 0.5 0.6",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //autogo
      if(Links_Memoires[position_onstage]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(x1*2)+(60*ratio_iCat_string[iCatPageis][id]), (y1*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[position_onstage]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d position %d %d 0",id,(x1*2), (y1*2)+ ((14*ratio_iCat_string[iCatPageis][id])+(12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d font %s",id,iphone_fonts[0]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d fontsize %d",id, 10*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      //time
      sprintf(string_to_send,"model StrTime%d text D.Out: %s OUT: %s  ",id,cross_dout,cross_out);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrTime%d position %d %d 0",id,(x1*2), (y1*2)+ ((24*ratio_iCat_string[iCatPageis][id])+(12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrTime%d font %s",id,iphone_fonts[0]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrTime%d fontsize %d",id, 10*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

     break;
     case 2://preset
     //num
      sprintf(string_to_send,"model Str%d text %s",id,string_mem_preset);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d position %d %d 0",id,(x1*2), (y1*2)+ ((14*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d fontsize %d",id, 14*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send,"model Str%d color 0.6 0.0 0.0",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
            //autogo
      if(Links_Memoires[position_preset]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(x1*2)+(60*ratio_iCat_string[iCatPageis][id]), (y1*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[position_preset]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d position %d %d 0",id,(x1*2), (y1*2)+ ((14*ratio_iCat_string[iCatPageis][id])+(12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d font %s",id,iphone_fonts[0]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d fontsize %d",id, 10*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //annotation
      sprintf(string_to_send,"model StrAnn%d text %s",id,annotation_memoires[position_preset]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrAnn%d position %d %d 0",id,(x1*2), (y1*2)+ ((24*ratio_iCat_string[iCatPageis][id])+(12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrAnn%d font %s",id,iphone_fonts[0]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrAnn%d fontsize %d",id, 10*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //time
      sprintf(string_to_send,"model StrTime%d text D.In: %s IN: %s  ",id,cross_din,cross_in);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrTime%d position %d %d 0",id,(x1*2), (y1*2)+ ((34*ratio_iCat_string[iCatPageis][id])+(12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrTime%d font %s",id,iphone_fonts[0]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrTime%d fontsize %d",id, 10*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
     break;
     case 3://mem before one
      //num
      sprintf(string_to_send,"model Str%d text %s",id,string_mem_before_one);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d position %d %d 0",id,(x1*2), (y1*2)+ ((12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Strc%d fontsize %d",id, 12*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send,"model Str%d color 1.0 1.0 1.0",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //autogo
      if(Links_Memoires[mem_before_one]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(x1*2)+(60*ratio_iCat_string[iCatPageis][id]), (y1*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
          //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[mem_before_one]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d position %d %d 0",id,(x1*2), (y1*2)+ ((12*ratio_iCat_string[iCatPageis][id])+(12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d font %s",id,iphone_fonts[0]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d fontsize %d",id, 10*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

      break;
      case 4://mem after one

      mem_after_one=0;
      for(int memsearch=position_preset+1; memsearch<10000;memsearch++)
      {
      if(MemoiresExistantes[memsearch]==1 )
      {
      mem_after_one=memsearch;
      //num
      sprintf(string_to_send,"model Str%d text %d.%d",id,mem_after_one/10,mem_after_one%10);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d position %d %d 0",id,(x1*2), (y1*2)+ ((12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Str%d font %s",id,iphone_fonts[5]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Strc%d fontsize %d",id, 12*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send,"model Str%d color 1.0 1.0 1.0",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
            //autogo
      if(Links_Memoires[mem_after_one]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(x1*2)+(60*ratio_iCat_string[iCatPageis][id]), (y1*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[mem_after_one]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d position %d %d 0",id,(x1*2), (y1*2)+ ((12*ratio_iCat_string[iCatPageis][id])+(12*2*ratio_iCat_string[iCatPageis][id])/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d font %s",id,iphone_fonts[0]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model StrDesc%d fontsize %d",id, 10*ratio_iCat_string[iCatPageis][id]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      }
      }

      break;
      default:
      break;
      }

break;
//fin string seq
default:
break;
}

return(0);
}







int Fantastick_check_string()
{
char string_to_send[256+36];
for(int id=1;id<iCat_nbre_de_strings[iCatPageis]+1;id++)
{
switch(iCat_affectation_string_type_is[iCatPageis][id])
     {
     case 1://INPUTS
     switch(iCat_affectation_string_action_is[iCatPageis][id])
     {
      case 1: //input
      if(previous_numeric_postext!=numeric_postext)
      {
      sprintf(string_to_send,"model Str%d text %s",id,string_numeric_entry);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      previous_numeric_postext=numeric_postext;
      break;
      case 2://last ch
      if(previous_last_ch_selected!=last_ch_selected)
      {
      sprintf(string_to_send,"model Str%d text >>Last Ch.selected: %d",id,last_ch_selected);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      previous_last_ch_selected=last_ch_selected;
      break;
      case 3://dimmers
      if(previous_last_dim_selected!=last_dim_selected)
      {
      sprintf(string_to_send,"model Str%d text %s",id,string_secondary_feeback);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      previous_last_dim_selected=last_dim_selected;
      break;
      case 4://last order
      if(strcmp(string_Last_Order,previous_string_Last_Order)!=0)
      {
      sprintf(string_to_send,"model Str%d text %s",id,string_Last_Order);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      sprintf(previous_string_Last_Order,string_Last_Order);
      break;
      case 5://confirm
      if(strcmp(string_confirmation,previous_string_confirmation)!=0)
      {
      sprintf(string_to_send,"model Str%d text %s",id,string_confirmation);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      sprintf(previous_string_confirmation,string_confirmation);
      break;
      default:
      strcpy(string_to_send,"");
      break;
      }
      break;
      //fin inputs
      case 2: // sequenciel
     if(someone_changed_in_sequences==1)
     {
     //ventilation_temps_vers_char();//pour sytrings din dout etc
     strcpy(string_to_send,"");
      switch(iCat_affectation_string_action_is[iCatPageis][id])
      {
      case 1://Stage
     //num
      sprintf(string_to_send,"model Str%d text %d.%d",id,position_onstage/10,position_onstage%10);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //autogo
      if(Links_Memoires[position_onstage]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(iCat_pos_string[iCatPageis][id][0]*2)+(60*ratio_iCat_string[iCatPageis][id]), (iCat_pos_string[iCatPageis][id][1]*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      else
      {
      sprintf(string_to_send, "model Autogo%d position -999 -999 0",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[position_onstage]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //time
      sprintf(string_to_send,"model StrTime%d text D.Out: %s OUT: %s  ",id,cross_dout,cross_out);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
     break;
     case 2://preset
     //num
      sprintf(string_to_send,"model Str%d text %d.%d",id,position_preset/10,position_preset%10);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //autogo
      if(Links_Memoires[position_preset]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(iCat_pos_string[iCatPageis][id][0]*2)+(60*ratio_iCat_string[iCatPageis][id]), (iCat_pos_string[iCatPageis][id][1]*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      else
      {
      sprintf(string_to_send, "model Autogo%d position -999 -999 0",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[position_preset]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //annotation
      sprintf(string_to_send,"model StrAnn%d text %s",id,annotation_memoires[position_preset]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //time
      sprintf(string_to_send,"model StrTime%d text D.In: %s IN: %s  ",id,cross_din,cross_in);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
     break;
     case 3://mem before one
      //num
      sprintf(string_to_send,"model Str%d text %d.%d",id,mem_before_one/10,mem_before_one%10);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //autogo
      if(Links_Memoires[mem_before_one]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(iCat_pos_string[iCatPageis][id][0]*2)+(60*ratio_iCat_string[iCatPageis][id]), (iCat_pos_string[iCatPageis][id][1]*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      else
      {
      sprintf(string_to_send, "model Autogo%d position -999 -999 0",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
       //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[mem_before_one]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      case 4://mem after one
      mem_after_one=0;
      for(int memsearch=position_preset+1; memsearch<10000;memsearch++)
      {
      if(MemoiresExistantes[memsearch]==1 )
      {
      mem_after_one=memsearch;
      //num
      sprintf(string_to_send,"model Str%d text %d.%d",id,mem_after_one/10,mem_after_one%10);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      //autogo
      if(Links_Memoires[mem_after_one]==1)
      {
      sprintf(string_to_send,"model Autogo%d image http://www.le-chat-noir-numerique.fr/iCat/autogo_view.jpg",id);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d position %d %d 0",id,(iCat_pos_string[iCatPageis][id][0]*2)+(60*ratio_iCat_string[iCatPageis][id]), (iCat_pos_string[iCatPageis][id][1]*2)+(5*ratio_iCat_string[iCatPageis][id]));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      sprintf(string_to_send, "model Autogo%d scale %.1f %.1f 0",id,((float)ratio_iCat_string[iCatPageis][id]/2),((float)ratio_iCat_string[iCatPageis][id]/2));
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      else
      {
      sprintf(string_to_send, "model Autogo%d position -999 -999 0",id);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      }
      //desc
      sprintf(string_to_send,"model StrDesc%d text %s",id,descriptif_memoires[mem_after_one]);
      nbrbytessendediCat=sendto(sockiCat,  string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
      break;
      }
      }
      break;
      default:
      break;
      }
      }//fin si someone_changed_in_sequences

      //times changed
      if(someone_changed_in_time_sequences==1)//uniquement affichage time crossfade
      {
      strcpy(string_to_send,"");
      switch(iCat_affectation_string_action_is[iCatPageis][id])
      {
      case 1://Stage
      //time
      sprintf(string_to_send,"model StrTime%d text D.Out: %s OUT: %s  ",id,cross_dout,cross_out);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
     break;
     case 2://preset
      //time
      sprintf(string_to_send,"model StrTime%d text D.In: %s IN: %s  ",id,cross_din,cross_in);
      nbrbytessendediCat=sendto(sockiCat, string_to_send,strlen(string_to_send)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
     break;
     default:
     break;
      }
      }
      break;
      default:
      break;

}
}
someone_changed_in_sequences=0;
someone_changed_in_time_sequences=0;
return(0);
}








int do_refresh_iCat(int iCatPage)
{
finished_to_send_orders_to_iCat=0;
index_false_shift=0; index_false_control=0;//pour éviter les pbs lors des changements de pages avec une commande shift toujours active

//clear models sortis de refresh


recalculate_iCatBuilder_window_size();




for(int u=0;u<nbre_d_envois_de_l_info;u++)
{

nbrbytessendediCat=sendto(sockiCat,  "opengl 1",sizeof("opengl 1"),0,(SOCKADDR*)&siniCat,sinsizeiCat);
sprintf(StrOrderToiCat,"orientation %d",iCat_preset_orientation[iCatPageis]);
nbrbytessendediCat=sendto(sockiCat,  StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);

//affichage sliders
   for(int sl=1;sl<iCat_nbre_de_sliders[iCatPageis]+1;sl++)
      {
          To_iCat_DrawSlider(sl,iCat_pos_slider[iCatPageis][sl][0],iCat_pos_slider[iCatPageis][sl][1],
          iCat_affectation_slider_type_is[iCatPageis][sl],iCat_affectation_slider_value_is[iCatPageis][sl]);

      }
      for(int bl=1;bl<iCat_nbre_de_boutons[iCatPageis]+1;bl++)
      {
      To_iCat_DrawButton(bl,iCat_pos_bouton[iCatPageis][bl][0],iCat_pos_bouton[iCatPageis][bl][1],
          iCat_affectation_bouton_type_is[iCatPageis][bl], iCat_affectation_bouton_action_is[iCatPageis][bl],iCat_affectation_bouton_value_is[iCatPageis][bl]);
      }
      for(int bl=1;bl<iCat_nbre_de_strings[iCatPageis]+1;bl++)
      {
      To_iCat_DrawString(bl,iCat_pos_string[iCatPageis][bl][0],iCat_pos_string[iCatPageis][bl][1],
          iCat_affectation_string_type_is[iCatPageis][bl], iCat_affectation_string_action_is[iCatPageis][bl]);
      }
      for(int bl=1;bl<iCat_nbre_de_tracking_zone[iCatPageis]+1;bl++)
      {
      To_iCat_DrawTrackingZone(bl,iCat_pos_trackzone[iCatPageis][bl][0],iCat_pos_trackzone[iCatPageis][bl][1],
       pos_iCat_tracker[iCatPageis][bl][0], pos_iCat_tracker[iCatPageis][bl][1] );
      }

}

index_refresh_valeurs_continous=1;
refresh_continuously_iCat_sliders();//MAJ niveaux
refresh_continuously_iCat_buttons();
index_refresh_valeursTRCK_continous=1;
refresh_continuously_iCat_trackerzones();
someone_changed_in_sequences=1;//icat
someone_changed_in_time_sequences=1;
Fantastick_check_string();
index_refresh_valeursTRCK_continous=0;
index_refresh_valeurs_continous=0;
finished_to_send_orders_to_iCat=1;

return(0);
}
