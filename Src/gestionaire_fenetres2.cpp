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

* \file gestionaire_fenetres2.cpp
* \brief {GUI fonctions to manage windows in whitecat}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour gérer les différentes fenêtres dans whitecat
*
*   GUI fonctions to manage windows in whitecat
*
 **/

int reset_config_indexes()
{
index_config_dmx=0;
index_config_midi=0;
index_config_network=0;
index_setup_gfx=0;
index_config_arduino=0;
index_config_general=0;
index_config_core=0;
 return(0);
}

int clear_non_desired_values_in_window_list()
{
for(int i=0;i<72;i++)
{
if(window_opened[i] >max_window_identity_is+1){window_opened[i]=0;window_opened[i]=0;} //+1 règle bug de rwanoux et jaques alpha 0.8.3
if(window_opened[i] <900){window_opened[i]=0;}
}
 return(0);
}


int initialisation_tableau_windows()
{
for(int i=0;i<63;i++)
 {
  window_opened[i]=0;
  temp_report_window[i]=0;
}
 return(0);
}

int check_nbre_opened_windows()
{

int nbre_windows=0;
for(int i=0;i<63;i++)
{
/*Christoph 11/04/14 Begin replace */
if(window_opened[i]>=900 && window_opened[i]<=max_window_identity_is)
{
nbre_windows++;
}
}
 return(nbre_windows);
}

int add_a_window(int id)
{
/* sab 05/03/2014 begin replace */
    int push_front_into_window_opened[72];
    int next_free_pos;
    next_free_pos=0;
    push_front_into_window_opened[next_free_pos]=id; // window is added on the top
    window_focus_id=id; // window is added on the top = it gets the focus
 //All open window are kept openin the same order (function to be rewritten with window_opened as a deque)
 //if window added on the top, it is on the list, we skip it (no duplicate in the list)
    for(int old_pos=0; old_pos<72; old_pos++)
    {
        if((window_opened[old_pos]!=id)  //id is already at the first place
                && (window_opened[old_pos]!=0)
                && (next_free_pos<72))    // don't overflow
        {
            next_free_pos= next_free_pos+1;
            push_front_into_window_opened[next_free_pos]=window_opened[old_pos];
        }
    }
    // Clean last unuse new position
    if ((next_free_pos+1)<72)
    {
        for(int i=(next_free_pos+1); i<72; i++)
        {
            push_front_into_window_opened[i]=0;
        }
    }
    //copy
    for(int i=0; i<72; i++) //both are 72 occurences long
    {
        window_opened[i] = push_front_into_window_opened[i];
    }
/* sab 05/03/2014 end replace */

 switch(id)
 {
 case W_SAVEREPORT:
      index_show_save_load_report=1;
 break;

 case W_TRICHROMY:
      index_trichro_window=1;index_affect_color_to_dock=0;
 break;
 case W_NUMPAD:
      index_visual_pad=1;
 break;
 case W_TRACKINGVIDEO:
      index_video_window=1;
 break;
 case W_ARTPOLLREPLY:
 break;
 case W_FADERS:
      index_show_faders=1;
 break;
 case W_WAVE:
     index_wave_menu_window=1;index_affect_wave_to_dock=0;
 break;
 case W_PATCH:
      index_patch_window=1;index_enable_curve_editing=0;
      index_patch_overide=0;
      reset_check_grada_overide_dimmers();
 break;
 case W_TIME:
      index_time=1;
 break;
 case W_SEQUENCIEL:
      index_window_sequentiel=1;
 break;
 case W_ASKCONFIRM:
       index_ask_confirm=1;
 break;
 case W_PLOT:
      index_plot_window=1;refresh_shape_factors(shape_selected_type);
 break;
 case W_ECHO:
  index_show_echo_window=1;
 break;
 case W_DRAW:
  index_draw_window=1;
 break;
 case W_LIST:
      index_list_projecteurs=1;
 break;
 case W_SAVE:
       index_menu_save=1;
       scan_importfolder("");scan_savesfolder();
       index_save_global_is=1;
       for (int r=0;r<72;r++)
       {
       specify_who_to_save_load[r]=1;
       }
 break;
 case W_MAINMENU:
      index_show_main_menu=1;
 break;
 case W_BANGER:
      index_show_banger_window=1;
 break;
 case W_ALARM:
 break;
 case W_AUDIO:
      index_show_audio_window=1;reset_audio_indexs_to_dock();
 break;
 case W_CFGMENU:
      reset_config_indexes();

      switch(config_page_is)
      {
        case 1:
             index_config_dmx=1;
        break;
        case 2:
             index_config_midi=1;
        break;
        case 3:
             index_config_network=1;
        break;
        case 4:
             index_setup_gfx=1;
        break;
        case 5:
             index_config_arduino=1;
        break;
        case 6:
             index_config_general=1;
        break;
        case 7:
             index_config_core=1;
        break;
        default:
        break;
      }
      index_show_config_window=1;
 break;
 case W_WIZARD:
      index_show_wizard_window=1;
 break;
 case W_MINIFADERS:
      index_show_minifaders=1;
 break;
 case W_CHASERS:
      index_affect_chaser_to_dock=0;
      index_window_chasers=1;
 break;
 case W_MOVER:
    index_show_mover_window=1; index_mouse_is_tracking=0;
 break;
 case W_iCAT:
      index_window_gui_iCat=1;
 break;
 case W_GRID:
      index_grider_window=1;
      for(int i=0;i<4;i++)
      {grid_affect_to_dock[i]=0;}
 break;
 case W_MY_WINDOW:
      index_my_window=1;
 break;
 default:
 break;
}
nbre_fenetre_actives++;
clear_non_desired_values_in_window_list();

return(0);
}
//substract in CORE

int initiate_windows()
{

 for(int i=0;i<63;i++)
 {
  if(window_opened[i]>=900)
  {add_a_window(window_opened[i]);}
 }
 window_focus_id=window_opened[0];

 return(0);
}


int window_bring_to_front(int num_window)
{
int temp_window[64];
for(int i=0;i<63;i++)
{
temp_window[i]=window_opened[i];
}
int pos=1;
for(int i=0;i<63;i++)
{
if(temp_window[i]>=900 && temp_window[i]!=num_window)
{
 window_opened[pos]=temp_window[i];
 pos++;
}
else{window_opened[pos]=0;}//enlevage des doublons

if( window_opened[pos]==num_window)   {window_opened[pos]=0;}//enlevement des doublons sur vauban
}
window_opened[0]=num_window;
window_focus_id=num_window;
return(num_window);
}



int check_save_load_report_window()
{
switch(index_show_save_load_report)
{
case 0:
substract_a_window(W_SAVEREPORT);
break;
case 1:
add_a_window(W_SAVEREPORT);
break;
default: break;
}
return(0);
}
