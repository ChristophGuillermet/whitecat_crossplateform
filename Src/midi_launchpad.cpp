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

* \file midi_launchpad.cpp
* \brief {midi launchpad send info}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour configurer le retour vers le launchpad of Novation
*
*   Midi Core fonctions to configure the return to the launchpad Novation
*
**/

int define_colors()
{
for(int g=0;g<3072;g++)
{
launchpad_color_defined[g]=8;
launchpad_is_a_cycling_effect[g]=0;
}

//faders
for(int i=0;i<48;i++)
{
 launchpad_color_defined[i+146]=lch_green;//lock
 launchpad_color_defined[i+245]=lch_orange;//UP
 launchpad_color_defined[i+294]=lch_orange;//DOWN
 launchpad_color_defined[i+343]=lch_orange;//SAW
 launchpad_is_a_cycling_effect[i+245]=1;
 launchpad_is_a_cycling_effect[i+294]=1;
 launchpad_is_a_cycling_effect[i+343]=1;
 launchpad_color_defined[i+392]=lch_ambre;//PREVDOCK
 launchpad_color_defined[i+441]=lch_ambre;//NEXTDOCK
 launchpad_color_defined[i+499]=lch_ambre;//UPDOWNDOCK
 launchpad_color_defined[i+685]=lch_red;//STOPPOS
 launchpad_color_defined[i+802]=lch_orange_fonce;//Loop One
 launchpad_color_defined[i+851]=lch_orange_fonce;//Loop All
 launchpad_color_defined[i+900]=lch_orange;//FLASH
 launchpad_color_defined[1115+i]=lch_orange;//Play Chaser
 launchpad_color_defined[1164+i]=lch_orange;//Seek Chaser
 launchpad_color_defined[1213+i]=lch_orange;//loop Chaser
}

////PLAYERS AUDIO///////////////////////////////////
for(int pl=0;pl<4;pl++)
{
launchpad_color_defined[628+pl]=lch_red; //play
launchpad_color_defined[636+pl]=lch_orange; //general loop
launchpad_color_defined[656+pl]=lch_red; //cueloop
}
//////////////////////BANGER//////////////////////
launchpad_color_defined[734]=lch_red;

////////////GRANDES COMMANDES//////////////////////////////
for(int i=0;i<15;i++)
{
launchpad_color_defined[743+i]=lch_orange;
}
//exception surcharge
launchpad_color_defined[754]=lch_red;//blind

for(int p=0;p<4;p++)//time
{
launchpad_color_defined[760+p]=lch_orange_fonce;
}

for(int co=0;co<8;co++)//dock color
{
launchpad_color_defined[949+co]=lch_orange_fonce;
}
for(int o=0;o<12;o++)//tracking space
{
launchpad_color_defined[957+o]=lch_orange_fonce;
}


for(int op=0;op<5;op++)//tracking dock
{
launchpad_color_defined[969+op]=lch_yellow;
}

//794 -> 801 preset minifaders
for(int op=0;op<8;op++)//tracking dock
{
launchpad_color_defined[794+op]=lch_orange;
}


//chasers selected
launchpad_color_defined[978]=lch_orange;//Play
launchpad_color_defined[980]=lch_orange;//loop
launchpad_color_defined[981]=lch_orange;//Forward
launchpad_color_defined[982]=lch_orange;//backward
launchpad_color_defined[983]=lch_orange;//aller retour
launchpad_color_defined[991]=lch_orange;//Up Op
launchpad_color_defined[992]=lch_green;//Stay Op
launchpad_color_defined[993]=lch_red;//Down Op
launchpad_color_defined[994]=lch_orange;//Tjoin STd Mode

for(int yo=0;yo<24;yo++)
{
launchpad_color_defined[998+yo]=lch_green;    //on off des tracks
}

//iCat preset
for(int yo=0;yo<8;yo++)
{
launchpad_color_defined[1267+yo]=lch_orange_fonce;    //on iCat preset
}

launchpad_color_defined[1277]=lch_red;    //midi mute general

//appels de fenetres en midi nouveau systeme menu interface générale
for(int io=0;io<25;io++)
{
launchpad_color_defined[io+1329]=lch_orange;
}
//exceptions:
launchpad_color_defined[1333]=lch_orange_fonce; //direct CH
launchpad_color_defined[1334]=lch_orange_fonce; //view
launchpad_color_defined[754]=lch_red;//blind

//gridplayers
for(int io=0;io<4;io++)
{
launchpad_color_defined[io+1472]=lch_red;//on off affichage players
launchpad_color_defined[io+1492]=lch_orange;//play player
launchpad_color_defined[io+1500]=lch_red;//autostop mode
launchpad_color_defined[io+1504]=lch_orange_fonce;//slave
launchpad_color_defined[io+1512]=lch_red;//macro goto
launchpad_color_defined[io+1516]=lch_red;//macro count
launchpad_color_defined[io+1520]=lch_red;//macro seek pos
launchpad_color_defined[io+1524]=lch_red;//stopplay macro
}
launchpad_color_defined[1540]=lch_orange;//on off asservissement sequenciel gpl1

launchpad_color_defined[1591]=lch_red;//on off reset accelerometre on crossfade done

 return(0);
}


int launchpad_set_led(int control, int color)
{
if(miditable[0][control]<5 && miditable[1][control]<128 && miditable[2][control]<128)//pour éviter d'envoyer une note inexistante et de planter midishare
{
send_my_midi_note(miditable[0][control],miditable[1][control],miditable[2][control],color, 25);
}
 return(0);
}




int launchpad_set_bool_value(int control,int value)
{
if(value==0)
{midi_launchpad_state[control]=0;}
else if(value>0) {midi_launchpad_state[control]=1;}
return(0);
}


int launchpad_set_zero_value(int control)//extinction led
{
midi_launchpad_state[control]=0;
return(0);
}



int launchpad_refresh_buffer_led()
{
//check des conditions de lecture des etats
///////////////////FADERS////////////////////////////////////////////////////////
for(int i=0;i<48;i++)
{
//LOCK
midi_launchpad_state[i+146]=FaderLocked[i];
//NOTHING
if(lfo_mode_is[i]==0){midi_launchpad_state[i+245]=0; midi_launchpad_state[i+294]=0; midi_launchpad_state[i+343]=0;}
//UP
else if(lfo_mode_is[i]==1){midi_launchpad_state[i+245]=1; midi_launchpad_state[i+294]=0; midi_launchpad_state[i+343]=0;}
//DOWN
else if(lfo_mode_is[i]==2){midi_launchpad_state[i+294]=1;midi_launchpad_state[i+245]=0;midi_launchpad_state[i+343]=0;}
//SAW
if(lfo_cycle_is_on[i]==1){midi_launchpad_state[i+343]=1;midi_launchpad_state[i+294]=0;midi_launchpad_state[i+245]=0;}
//PREV DOCK CYCLE
midi_launchpad_state[i+392]=lfo_do_next_step[i][0];
//NEXT DOCK CYCLE
midi_launchpad_state[i+441]=lfo_do_next_step[i][1];
//UP AND DOWN CYCLE
midi_launchpad_state[i+499]=lfo_cycle_steps[i];
//STOPPOS
midi_launchpad_state[i+685]=ActionnateStopOn[i];
//FLASH
midi_launchpad_state[i+900]=FaderIsFlash[i];
//One Loop
midi_launchpad_state[i+802]=is_dock_for_lfo_selected[i][(dock_used_by_fader_is[i])];
//All Loop
if( is_dock_for_lfo_selected[i][0]==1 && is_dock_for_lfo_selected[i][1]==1 && is_dock_for_lfo_selected[i][2]==1 &&
is_dock_for_lfo_selected[i][3]==1 && is_dock_for_lfo_selected[i][4]==1 && is_dock_for_lfo_selected[i][5]==1 )
{midi_launchpad_state[i+851]=1;}else {midi_launchpad_state[i+851]=0;}
//chaser embeded in Fader:

midi_launchpad_state[i+1115]=chaser_is_playing[ChaserAffectedToDck[i][dock_used_by_fader_is[i]]];//Play
midi_launchpad_state[i+1213]=chaser_is_in_loop[ChaserAffectedToDck[i][dock_used_by_fader_is[i]]];//loop
}

/////////SEQUENCIEL//////////////////////////////
if(index_go==1)
{
switch(index_pause)
{
case 0:
midi_launchpad_state[495]=1;
launchpad_is_a_cycling_effect[495]=0;
launchpad_color_defined[495]=lch_red;
break;
case 1:
midi_launchpad_state[495]=1;
launchpad_is_a_cycling_effect[495]=1;
launchpad_color_defined[495]=lch_red;
break;
default: break;
}
}
else if(index_go==0)
{
midi_launchpad_state[495]=0;
launchpad_is_a_cycling_effect[495]=0;
}

if(index_go_back==1)
{
midi_launchpad_state[494]=1;
launchpad_color_defined[494]=lch_red;
}
else {midi_launchpad_state[494]=0;}

//locks presets////////////////////////////////////
for(int lc=0;lc<5;lc++)
{
launchpad_color_defined[605+lc]=lch_green;
midi_launchpad_state[605+lc]=lock_preset[lc];
}

////PLAYERS AUDIO///////////////////////////////////
for(int pl=0;pl<4;pl++)
{
midi_launchpad_state[628+pl]=player_is_playing[pl];
midi_launchpad_state[636+pl]=player_is_onloop[pl];
midi_launchpad_state[656+pl]=player_is_onloopCue[pl];
}
/////BANGER///////////////////////////////////////////
midi_launchpad_state[734]=1-bang_is_sended[index_banger_selected];
if(bang_is_sended[index_banger_selected]==0){launchpad_is_a_cycling_effect[734]=1;}


/////////////GRANDES COMMANDES/////////////////////////
midi_launchpad_state[743]=index_do_dock;
midi_launchpad_state[744]=index_do_modify;
midi_launchpad_state[745]=index_do_report;
midi_launchpad_state[746]=index_main_clear;
midi_launchpad_state[747]=index_type;
midi_launchpad_state[748]=index_time;
midi_launchpad_state[749]=index_trichro_window;
midi_launchpad_state[750]=index_video_window;
midi_launchpad_state[751]=index_window_sequentiel;
midi_launchpad_state[752]=index_show_faders;
midi_launchpad_state[753]=index_show_banger_window;
midi_launchpad_state[754]=index_blind;
midi_launchpad_state[755]=index_show_config_window;
midi_launchpad_state[756]=index_show_audio_window;
/////////////////////////////////////////////////////////////////////////////////

//////////FENETRE TIME/////////////////////////////////////////////////////////
for(int p=0;p<4;p++)
{
midi_launchpad_state[760+p]=index_type_of_time_to_affect[p] ;
}
////////////DOCK COLORS DE TRICHROMY/////////////////////////////////////////
for (int co=0;co<8;co++)
{
if(dock_color_selected!=co){midi_launchpad_state[949+co]=0;}else{midi_launchpad_state[949+co]=1;}
}


//trcking space
for(int u=0;u<12;u++)
{
midi_launchpad_state[957+u]=tracking_spaces_on_off[tracking_dock_selected][u];
}
//tracking dock
for(int d=0;d<5;d++)
{
if(tracking_dock_selected!=d){midi_launchpad_state[969+d]=0;}else{midi_launchpad_state[969+d]=1;}
}

for(int op=0;op<8;op++)//presets minifaders
{
if(mf_preset_selected_is==op && minifader_preset_is_empty[op]==0){midi_launchpad_state[794+op]=1;}
else{midi_launchpad_state[794+op]=0;}
}
////CHASER SELECTED
midi_launchpad_state[978]=chaser_is_playing[chaser_selected];
midi_launchpad_state[980]=chaser_is_in_loop[chaser_selected];
switch (chaser_way[chaser_selected])
{
case 0:
midi_launchpad_state[981]=1; midi_launchpad_state[982]=0;
break;
case 1:
midi_launchpad_state[981]=0; midi_launchpad_state[982]=1;
break;
default: break;
}
midi_launchpad_state[983]=chaser_aller_retour[chaser_selected];
midi_launchpad_state[994]=chaser_time_mode[chaser_selected];

switch (chaser_operator_is)
{
case 0:
midi_launchpad_state[991]=0;
midi_launchpad_state[992]=0;
midi_launchpad_state[993]=0;
break;
case 1:
midi_launchpad_state[991]=1;
midi_launchpad_state[992]=0;
midi_launchpad_state[993]=0;
break;
case 2:
midi_launchpad_state[991]=0;
midi_launchpad_state[992]=1;
midi_launchpad_state[993]=0;
break;
case 3:
midi_launchpad_state[991]=0;
midi_launchpad_state[992]=0;
midi_launchpad_state[993]=1;
break;
default: break;
}


for(int yo=0;yo<24;yo++)
{
midi_launchpad_state[998+yo]=track_is_on[chaser_selected][yo];    //on off des tracks

}

//iCat preset
for(int yo=0;yo<8;yo++)
{
if(yo==iCatPageis){midi_launchpad_state[1267+yo]=1;} //on iCat preset
else {midi_launchpad_state[1267+yo]=0;}
}

midi_launchpad_state[1277]=index_midi_mute;    //midi mute general

//grandes commandes rajouts

midi_launchpad_state[1329]=index_show_wizard_window;
midi_launchpad_state[1330]=index_menu_save ;
midi_launchpad_state[1331]=index_patch_window ;
midi_launchpad_state[1332]=index_list_projecteurs ;
midi_launchpad_state[1333]=index_direct_chan ;
midi_launchpad_state[1334]=index_inspekt ;
midi_launchpad_state[1335]=index_do_freeze ;
midi_launchpad_state[1336]=index_show_minifaders ;
midi_launchpad_state[1337]=index_window_chasers ;
midi_launchpad_state[1338]=index_visual_pad ;
midi_launchpad_state[1339]=index_show_mover_window ;
midi_launchpad_state[1340]=index_grider_window ;
midi_launchpad_state[1341]=index_window_gui_iCat;
//midi_launchpad_state[1342]=index_help_window;


//gridplayers
for(int io=0;io<4;io++)
{
midi_launchpad_state[io+1472]=index_show_grid_player[io];//on off affichage players
midi_launchpad_state[io+1492]=grider_is_playing[io];//play player
midi_launchpad_state[io+1500]=grider_autostopmode[io];//autostop mode
midi_launchpad_state[io+1504]=grid_player_slave[io];//slave
midi_launchpad_state[io+1512]=grider_goto_mode[io];//macro goto
midi_launchpad_state[io+1516]=grider_count_mode[io];//macro count
midi_launchpad_state[io+1520]=grider_seekto_mode[io];//macro seek pos
midi_launchpad_state[io+1524]=grider_stoplay_mode[io];//stopplay macro
}
midi_launchpad_state[1540]=index_link_speed_crossfade_to_gpl1;//on off asservissement sequenciel gpl1

midi_launchpad_state[1591]=auto_reset_crossfade_speed_on_link;//auto reset crossfade speed
////////////////////////////////////////////////////////////////////////////////
///////////////////RETRO ALLUMAGE DES LEDS//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

for(int l=0;l<3072;l++)
{
if(midi_launchpad_state[l]!=midi_launchpad_state_before[l])
{
switch(midi_launchpad_state[l])
{
case 0:
temp_launchpad=8;
break;
case 1:
temp_launchpad= launchpad_color_defined[l];
break;
default: break;
}
if(miditable[0][l]<5 && miditable[1][l]<128 && miditable[2][l]<128)
{//mode led fixe
send_my_midi_note(miditable[0][l],miditable[1][l],miditable[2][l],temp_launchpad,1);//etait 10 en temps
}
midi_launchpad_state_before[l]=midi_launchpad_state[l];
}
}

return(0);
}

int reset_launchpad()
{
//init des couleurs de leds fonction des fonctions
define_colors();
//reset to default
send_my_midi_note(4,0,0,0,10);
//maping xy
send_my_midi_note_delayed(4,0,0,1,10,10);
//rafraichissement des états des leds à l ouverture
launchpad_refresh_buffer_led();
//mise en palce buffer 1
//launchpad_buffer=0;
//send_my_midi_note_delayed(4,0,49,1,10,10);//buffer 0

return(0);
}
