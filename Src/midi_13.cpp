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

* \file midi_13.cpp
* \brief {midi GUI}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions de dessins du midi dans l'inteface graphique
*
*   Midi GUI fonctions
*
 **/




int do_midi_call_order(int control)
{

fader_selected_for_record=control;
dock_selected_for_record=detect_dock_used(control) ;
//appel par bouton midi des actions sur le dock selectionné
 //maj au 17 juin 2012 Plot version en alpha -> harmonisation des F1 F2 F3 suite au rv beta testeur paris
 if(index_do_dock==1  && index_direct_chan==0   && index_affect_chaser_to_dock==0  && index_affect_time==0 && index_affect_color_to_dock==0 && index_do_affect_net_to_dock==0
 && index_affect_dmxin==0 && index_affect_video_tracking_to_dock==0 && index_affect_audio_to_dock==0 && gridplayer_to_affect_is==-1
 && index_do_fgroup==0 && index_affect_to_dock_mover==0 )
 {
 index_do_record_on_faders=1; index_ask_confirm=1;
 }

   //store direct CH
 else if(index_do_dock==1 && index_direct_chan==1)
 {
 index_do_record_direct_ch=1; index_ask_confirm=1;
 }


 //Store Fgroup dans dock
 else if (  index_do_dock==1 && index_do_fgroup==1)
 {
 index_do_affect_fgroup=1; index_ask_confirm=1;
 }

 //time
 else if( index_do_dock==1 && index_affect_time==1)
 {
 show_im_recording_a_time=1;
 DoTimeToDock(fader_selected_for_record,dock_selected_for_record);
 sprintf(string_Last_Order,">>Time affected to Master %d Dock %d", fader_selected_for_record,dock_selected_for_record);
 index_affect_time=0; index_ask_confirm=1;
 }
 //trichro
 else if(index_do_dock==1 && index_affect_color_to_dock==1)
 {
 index_do_affect_color_on_faders=1; index_ask_confirm=1;
 }
  //Store Chaser dans dock
 else if (index_do_dock==1 && index_affect_chaser_to_dock==1 )
 {
 index_do_affect_fx=1; index_ask_confirm=1;
 }
  //Store Grid dans dock
 else if ( index_do_dock==1 &&  gridplayer_to_affect_is>=0 )
 {
 index_do_affect_grid_to_fader=1; index_ask_confirm=1;
 }

 //video to dock
 else if( index_do_dock==1 && index_affect_video_tracking_to_dock==1)
 {
 index_do_video_to_dock=1; index_ask_confirm=1;
 }
 //audio to dock
 else if( index_do_dock==1 && index_affect_audio_to_dock==1)
 {
 if(player_to_affect_to_dock>=0 && player_to_affect_to_dock<4 )
 {
 index_do_audio_to_dock=1; index_ask_confirm=1;
 }
 }
  //Store Mover dans dock
 else if (  index_do_dock==1 && index_affect_to_dock_mover==1)
 {
 index_do_affect_mover=1; index_ask_confirm=1;
 }

   //Store Draw dans dock
 else if (  index_do_dock==1 && index_affect_draw_to_dock==1)
 {
 index_do_draw_affect_to_dock=1; index_ask_confirm=1;
 }

 //dmx to dock
 else if( index_do_dock==1 && index_affect_dmxin==1)
 {
 index_do_dmx_to_dock=1; index_ask_confirm=1;
 }
 //artnet to dock
 else if(index_do_dock==1 && index_do_affect_net_to_dock==1 )
 {
 index_do_artnet_to_dock=1; index_ask_confirm=1;
 }



 //modify
 else if( index_do_modify==1 )
 {
 index_do_modify_on_faders=1; index_ask_confirm=1;
 }
 //report
  else if( index_do_report==1 )
 {
 index_do_report_on_faders=1; index_ask_confirm=1;
 }
  //clear
 else if( index_main_clear==1 )
 {
 index_do_clear_dock=1;   index_ask_confirm=1;
 }
 //nommage de dock
 else if( index_type==1 )
 {
 for(int tt=0;tt<24;tt++)
 {
 DockName[fader_selected_for_record][dock_selected_for_record ][tt]=numeric[tt];
 }
 DockName[fader_selected_for_record][dock_selected_for_record ][24]='\0';
 index_type=0; reset_numeric_entry();numeric_postext=0;
 sprintf(string_Last_Order,">>On Master %d GIVED A NAME FOR DOCK %d ",fader_selected_for_record,dock_selected_for_record );
 index_ask_confirm=1;
 }

 light_midi_do_order[control]=1.0;
 minifaders_selected[control]=toggle(minifaders_selected[control]);
 return(0);
}

int do_midi_job(int control)
{

//////////////FADERS////////////////////////
if(control<=47)
{
//midi in
//on prend que si en lock et maitre, ou alors sans lock
if((FaderLocked[control]==1 && LockFader_is_FullLevel[control]==1)|| (FaderLocked[control]==0 ))
{

if(midi_levels[control]==127){fader_set_level(control,255);}//pour mettre à full
else {fader_set_level(control,midi_levels[control]*2);}
//Fader[control]=midi_levels[control]*2;
//if(midi_levels[control]==127){Fader[control]=255;}//pour mettre à full
//index_fader_is_manipulated[control]=1;
}
}

if(lfo_mode_is[control]==1 || lfo_mode_is[control]==2 || lfo_cycle_is_on[control]==1)
{
lfo_mode_is[control]=0; lfo_mode_is[control]=0; lfo_cycle_is_on[control]=0;
}
//////////////BOUTONS DOCK + -
//dock -
if(control>=48 && control <96 )
{

               int dockused=detect_dock_used(control-48);
               DockIsSelected[control-48][dockused]=0;
               if (dockused>0)
                {
                DockIsSelected[control-48][dockused]=0;
                dockused--;
                DockIsSelected[control-48][dockused]=1;
                }
               else if (dockused==0)
                {
                DockIsSelected[control-48][dockused]=0;
                dockused=5;//6 docks pos 5
                DockIsSelected[control-48][dockused]=1;
                }
               /* if( enable_launchpad==1)
                {launchpad_impulsion(control,orange);}*/
                rest(midi_keyboard_wait);

}

//dock +
if(control>=96 && control <145 )
{
               int dockused=detect_dock_used(control-96);
               DockIsSelected[control-96][dockused]=0;
               if (dockused<core_user_define_nb_docks-1)
                {
                DockIsSelected[control-96][dockused]=0;
                dockused++;
                DockIsSelected[control-96][dockused]=1;
                }
               else if (dockused==core_user_define_nb_docks-1)
                {
                DockIsSelected[control-96][dockused]=0;
                dockused=0;//6 docks pos 5
                DockIsSelected[control-96][dockused]=1;
                }
               /* if( enable_launchpad==1)
                {launchpad_impulsion(control, orange);}      */
                rest(midi_keyboard_wait);
}
//dock sur CC
//dock - only attributated
if(control>47 && control <=95 && miditable[0][control]==4)
{

               int dockused=detect_dock_used(control-48);
               DockIsSelected[control-48][dockused]=0;

               if((midi_levels[control]>=0 && midi_levels[control]<=5) || (midi_levels[control]>=36 && midi_levels[control]<=41)
                  ||(midi_levels[control]>=72 && midi_levels[control]<=77) ||( midi_levels[control]>=108 && midi_levels[control]<=110 ))
               {dockused=0;}
               if((midi_levels[control]>=6 && midi_levels[control]<=11) || (midi_levels[control]>=42 && midi_levels[control]<=47)
                  || (midi_levels[control]>=78 && midi_levels[control]<=83) || (midi_levels[control]>=111 && midi_levels[control]<=113) )
               {dockused=1;}
               if((midi_levels[control]>=12 && midi_levels[control]<=17) || (midi_levels[control]>=48 && midi_levels[control]<=53)
                  || (midi_levels[control]>=84 && midi_levels[control]<=89) || (midi_levels[control]>=114 && midi_levels[control]<=117) )
               {dockused=2;}
               if((midi_levels[control]>=18 && midi_levels[control]<=23) || ( midi_levels[control]>=54 && midi_levels[control]<=59)
                  || (midi_levels[control]>=90 && midi_levels[control]<=95) || (midi_levels[control]>=118 && midi_levels[control]<=121) )
               {dockused=3;}
               if((midi_levels[control]>=24 && midi_levels[control]<=29) || (midi_levels[control]>=60 && midi_levels[control]<=65)
                  || (midi_levels[control]>=96 && midi_levels[control]<=101) || (midi_levels[control]>=122 && midi_levels[control]<=124) )
               {dockused=4;}
               if((midi_levels[control]>=30 && midi_levels[control]<=35) ||(midi_levels[control]>=66 && midi_levels[control]<=71)
                  || (midi_levels[control]>=102 && midi_levels[control]<=107) || (midi_levels[control]>=125 && midi_levels[control]<=127) )
               {dockused=5;}

               DockIsSelected[control-48][dockused]=1;
                rest(midi_keyboard_wait);
}

if(control==145)//SELECT ALL MINIFADERS
{
for(int i=0;i<core_user_define_nb_faders;i++)
{minifaders_selected[i]=1;}
do_light_minifaders_commands[23]=1;
}

////BOUTTON LOCK
if(control>=146 && control <195)
{
if(FaderLocked[control-146]==1)
{
FaderLocked[control-146]=0;
Fader[control-146]=(unsigned char)((((float)(StateOfFaderBeforeLock[control-146]))/255)*locklevel);
midi_levels[control-146]=(int)(((float)Fader[control-146])/2);
rest(midi_keyboard_wait);
}
else   if(FaderLocked[control-146]==0)
{
FaderLocked[control-146]=1;
StateOfFaderBeforeLock[control-146]=Fader[control-146];
if(StateOfFaderBeforeLock[control-146]==255){LockFader_is_FullLevel[control-146]=1;}
else if(StateOfFaderBeforeLock[control-146]<255){LockFader_is_FullLevel[control-146]=0;}
lfo_cycle_is_on[control-146]=0;//rajout 0.7.6
lfo_mode_is[control-146]=0;
rest(midi_keyboard_wait);
}
}
////SPEED LFO
if(control>=196 && control <245)
{
lfo_speed[control-196]=midi_levels[control];

if(DockTypeIs[control-196][dock_used_by_fader_is[control-196]]==12)//enchassement Grid si slave
{
asservissement_gridplayer(control-196,dock_used_by_fader_is[control-196]);
}

}
/////LFO UP
if(control>=245 && control <294)
{
if(lfo_mode_is[control-245]!=1 && (FaderLocked[control-245]==0 || LockFader_is_FullLevel[control-245]==1))//rajout lock 0.7.6)//up
{
lfo_mode_is[control-245]=1;
faders_in_float[control-245]=Fader[control-245];
}
else
{lfo_mode_is[control-245]=0;}

lfo_cycle_is_on[control-245]=0;
rest(midi_keyboard_wait);
}
//LFO DOWN
if(control>=294 && control <343)
{
if(lfo_mode_is[control-294]!=2 && (FaderLocked[control-294]==0 || LockFader_is_FullLevel[control-294]==1))//rajout lock 0.7.6)//down
{
lfo_mode_is[control-294]=2;
faders_in_float[control-294]=Fader[control-294];
}
else {lfo_mode_is[control-294]=0;}
lfo_cycle_is_on[control-294]=0;
rest(midi_keyboard_wait);
}
//LFO SAW
if(control>=343 && control <392)
{
faders_in_float[control-343]=Fader[control-343];
if(lfo_cycle_is_on[control-343]==0 && (FaderLocked[control-343]==0 || LockFader_is_FullLevel[control-343]==1))//rajout lock 0.7.6)//up
{
lfo_cycle_is_on[control-343]=1;
lfo_running_is_upward[control-343]=1;
lfo_mode_is[control-343]=0;
if(Fader[control-343]>0 && Fader[control-343]<255 ){lfo_running_is_upward[control-343]=1;}
}
else if(lfo_cycle_is_on[control-343]==1)
{
lfo_cycle_is_on[control-343]=0;
}
rest(midi_keyboard_wait);
}
//LFO DOCK-
if(control>=392 && control <441)
{
if (lfo_do_next_step[control-392][0]==0) {lfo_do_next_step[control-392][0]=1;lfo_do_next_step[control-392][1]=0; rest(midi_wait);}
else if (lfo_do_next_step[control-392][0]==1) {lfo_do_next_step[control-392][0]=0; rest(midi_wait);}
}
//LFO DOCK+
if(control>=441 && control <490)
{
if (lfo_do_next_step[control-441][1]==0) {lfo_do_next_step[control-441][1]=1;lfo_do_next_step[control-441][0]=0; rest(midi_wait);}
else if (lfo_do_next_step[control-441][1]==1) {lfo_do_next_step[control-441][1]=0; rest(midi_wait);}
}


//MIDI PONCTUELS
//SEQUENCIEL
if(control==494)
{
do_go_back_function();
rest(midi_keyboard_wait);
}

if(control==495)
{
switch (Midi_Force_Go)
{
case 0:
do_go_function();
break;
case 1:
if(index_go==1){
do_double_go_function();
}
else {do_go_function(); }
index_pause=0;
break;
default: break;
}
if(index_go==1 && index_pause==0)
{
do_send_bang();
}
rest(midi_keyboard_wait);
}

if(control==496)
{
do_double_go_function();
/*if(enable_launchpad==1){launchpad_impulsion(control, red);}   */
if(index_go==1 && index_pause==0)
{
do_send_bang();
}
rest(midi_keyboard_wait);
}

if(control==493)
{
crossfade_speed=midi_levels[control];
prepare_crossfade();
//ventilation_temps_vers_char();//icat
someone_changed_in_time_sequences=1;
//integration gridplayer 1
if(index_link_speed_crossfade_to_gpl1==1)
{
grid_crossfade_speed[0]=crossfade_speed;
midi_levels[1508]=crossfade_speed;
gridder_prepare_cross(0,index_grider_selected[0],index_grider_step_is[0]);
}
}
//X1
if(control==491)
{
if(midi_levels[control]<127 && index_get_back_faders_need_to_be_done==0)
{
niveauX1=midi_levels[control]*2;
}
if(midi_levels[control]==127 && index_get_back_faders_need_to_be_done==0)
{
niveauX1=255;
}
}

if(control==492)//X2
{
if((127-midi_levels[control])<127 && index_get_back_faders_need_to_be_done==0)
{
niveauX2=(127-midi_levels[control])*2;
}
if((127-midi_levels[control])==127 && index_get_back_faders_need_to_be_done==0)
{
niveauX2=255;
}
}

if(midi_levels[491]==127 && (127-midi_levels[492])==0 )
{index_get_back_faders_need_to_be_done=0;}

if(midi_levels[491]==0 && (127-midi_levels[492])==127 && niveauX1==0 && niveauX2==255 )
{
next_mem_crossfade_finished(position_preset);
index_go=0;
if(index_auto_mute_cuelist_speed==1 && crossfade_speed!=64)
{is_raccrochage_midi_remote[493]=1; }
crossfade_speed=64;
if(midi_send_out[493]==1){index_send_midi_out[493]=1;}//remise du speed midi
index_get_back_faders_need_to_be_done=1;
}

//COLOR WHEEL
/*(control==497)
{
//MIS DANS LA FENETRE TRICHRO POUR RAFFRAIHIR LE TRIANGLE

}*/

//TRACKING VIDEO DECAY

if(control==498)
{
index_decay_tracker=midi_levels[498];
refresh_decay();
}


//RAJOUT AU FADERS: L ALLER RETOUR BAS HAUT DES STEPS key on
if(control>=499 && control<548)
{
lfo_cycle_steps[control-499]= toggle(lfo_cycle_steps[control-499]); rest(midi_wait);
}

//ON OFF action grandes commandes AT ZERO
if(control==548)//fader off
{
do_stock_fadersstate(1,0,0,0,0);
for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           Fader[p]=0;
           midi_levels[p]=0;
           index_send_midi_out[p]=1;
           }
           }
/*if(enable_launchpad==1){launchpad_impulsion(control, green);}*/
}

if(control==549)//speed off
{
do_stock_fadersstate(0,1,0,0,0);
      for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           lfo_speed[p]=64;
           midi_levels[196+p]=64;
           index_send_midi_out[196+p]=1;
           }
           }
/*if(enable_launchpad==1){launchpad_impulsion(control, green);}*/
}

if(control==550)//lock off
{
do_stock_fadersstate(0,0,1,0,0);
        for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           FaderLocked[p]=0;
           }
           }
/*if(enable_launchpad==1){launchpad_impulsion(control, green);}*/
}
if(control==551)//lfo off
{
       do_stock_fadersstate(0,0,0,1,0);
       for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           lfo_mode_is[p]=0;//no lfo
           lfo_cycle_is_on[p]=0;//saw
           lfo_cycle_steps[p]=0;
           lfo_do_next_step[p][0]=0;
           lfo_do_next_step[p][1]=0;
           }
           }
/*if(enable_launchpad==1){launchpad_impulsion(control, green);}*/
}
if(control==552)//loop off
{
do_stock_fadersstate(0,0,0,0,1);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           for(int d=0;d<core_user_define_nb_docks;d++)
           {
           is_dock_for_lfo_selected[p][d]=0;
           }
           }
           }
/*if(enable_launchpad==1){launchpad_impulsion(control, green);}*/
}
if(control==553)// ALL OFF
{
do_stock_fadersstate(1,1,1,1,1);
          for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           Fader[p]=0;
           midi_levels[p]=0;
           index_send_midi_out[p]=1;
           lfo_speed[p]=64;
           midi_levels[196+p]=64;
           index_send_midi_out[196+p]=1;
           FaderLocked[p]=0;
           lfo_mode_is[p]=0;//no lfo
           lfo_cycle_is_on[p]=0;//saw
           lfo_cycle_steps[p]=0;
           lfo_do_next_step[p][0]=0;
           lfo_do_next_step[p][1]=0;
           for(int d=0;d<core_user_define_nb_docks;d++)
           {
           is_dock_for_lfo_selected[p][d]=0;
           }
           }
           }
/*if(enable_launchpad==1){launchpad_impulsion(control, green);}*/
}
if(control==554)//midi out off
{
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           midi_send_out[p]=0;//faders
           }
}
/*if(enable_launchpad==1){launchpad_impulsion(control, green);}*/
}
if(control==555)// RECALL
{
do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
}

if(control>=556 && control<605)
{
do_midi_call_order(control-556);
midi_levels[control]=0;//clean de l'état midi pour visu
/*if(enable_launchpad==1){launchpad_impulsion(control,red);}      */
}

//preset locks
if(control>=605 && control<614)
{
do_lock_preset(control-605);
}
//Grand master
if (control==615)
{
if(index_allow_grand_master==1)
{
if(midi_levels[control]<127 )
{
niveauGMaster=midi_levels[control]*2;
}
if(midi_levels[control]==127)
{
niveauGMaster=255;
}
}
}
//AUDIO PLAYERS

for (int bum=0;bum<4;bum++)
{
//616 à 619 faders audio level
if (control==616+bum)
{
player_niveauson[bum]=midi_levels[control];
if(player_ignited[bum]==1)
{
switch(bum)
{
case 0:
player1->setVolume(((float)player_niveauson[bum])/127);
break;
case 1:
player2->setVolume(((float)player_niveauson[bum])/127);
break;
case 2:
player3->setVolume(((float)player_niveauson[bum])/127);
break;
case 3:
player4->setVolume(((float)player_niveauson[bum])/127);
break;
default: break;
}
}
}
//620 à 623 faders audio Pan
if (control==620+bum)
{
if(player_ignited[bum]==1)
{
switch(bum)
{
case 0://PLAYER 1
 player_pan[bum]=midi_levels[control] ;
 if(player_pan[bum]<1){player_pan[bum]=1;}
 else if(player_pan[bum]>127){player_pan[bum]=127;}
 player1->setPan(((float)(player_pan[bum]-64))/63); // -64 /63 OK POUR AVOIR -1.00 +1.00 GAUCHE DROITE
break;
case 1://PLAYER 2
 player_pan[bum]=midi_levels[control];
 if(player_pan[bum]<1){player_pan[bum]=1;}
 else if(player_pan[bum]>127){player_pan[bum]=127;}
 player2->setPan(((float)(player_pan[bum]-64))/63);
break;
case 2://PLAYER 3
 player_pan[bum]=midi_levels[control];
 if(player_pan[bum]<1){player_pan[bum]=1;}
 else if(player_pan[bum]>127){player_pan[bum]=127;}
 player3->setPan(((float)(player_pan[bum]-64))/63);
break;
case 3://PLAYER 4
 player_pan[bum]=midi_levels[control];
 if(player_pan[bum]<1){player_pan[bum]=1;}
 else if(player_pan[bum]>127){player_pan[bum]=127;}
 player4->setPan(((float)(player_pan[bum]-64))/63);
break;
default: break;
}
}
}
//624 à 627 faders audio Pitch
if (control==624+bum)
{
if(player_ignited[bum]==1)
{
switch(bum)
{
case 0://PLAYER 1
 player_pitch[bum]=midi_levels[control];
 if(player_pitch[bum]<1){player_pitch[bum]=1;}
 else if(player_pitch[bum]>127){player_pitch[bum]=127;}
 player1->setPitchShift((((float)player_pitch[bum])/64));
break;
case 1://PLAYER 2
  player_pitch[bum]=midi_levels[control];
 if(player_pitch[bum]<1){player_pitch[bum]=1;}
 else if(player_pitch[bum]>127){player_pitch[bum]=127;}
 player2->setPitchShift((((float)player_pitch[bum])/64));
break;
case 2://PLAYER 3
  player_pitch[bum]=midi_levels[control] ;
 if(player_pitch[bum]<1){player_pitch[bum]=1;}
 else if(player_pitch[bum]>127){player_pitch[bum]=127;}
 player3->setPitchShift((((float)player_pitch[bum])/64));
break;
case 3://PLAYER 4
  player_pitch[bum]=midi_levels[control] ;
 if(player_pitch[bum]<1){player_pitch[bum]=1;}
 else if(player_pitch[bum]>127){player_pitch[bum]=127;}
 player4->setPitchShift((((float)player_pitch[bum])/64));
break;
default: break;
}
}
}

//PLAY des 4 lecteurs
if (control==628+bum)
{
if(player_ignited[bum]==1)
{
switch(bum)
{
case 0://PLAYER 1
 switch(player1->isPlaying())
 {
 case 0:
 player1->play(); player_is_playing[bum]=1;
 break;
 case 1:
 player1_do_stop();player_is_playing[bum]=0;
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2->isPlaying())
 {
 case 0:
 player2->play();    player_is_playing[bum]=1;
 break;
 case 1:
 player2_do_stop();player_is_playing[bum]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3->isPlaying())
 {
 case 0:
 player3->play();    player_is_playing[bum]=1;
 break;
 case 1:
 player3_do_stop();player_is_playing[bum]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4->isPlaying())
 {
 case 0:
 player4->play();     player_is_playing[bum]=1;
 break;
 case 1:
 player4_do_stop();  player_is_playing[bum]=0;
 break;
 default: break;
 }
break;
default: break;
}
}
}
//Seek To Zero des 4 lecteurs
if (control==632+bum)
{
if(player_ignited[bum]==1)
{
switch(bum)
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
midi_show_flash_seektouch[bum]=1;
/*if(enable_launchpad==1){launchpad_impulsion(control, orange);}*/
}
}

//General Loop des 4 lecteurs
if (control==636+bum)
{
if(player_ignited[bum]==1)
{
switch(bum)
{
case 0://PLAYER 1
 switch(player1-> getRepeat())
 {
 case 0:
 player1->setRepeat(true);
 player_is_onloop[bum]=1;
 break;
 case 1:
 player1->setRepeat(false);
 player_is_onloop[bum]=0;
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2-> getRepeat())
 {
 case 0:
 player2->setRepeat(true);
 player_is_onloop[bum]=1;
 break;
 case 1:
 player2->setRepeat(false);
 player_is_onloop[bum]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3-> getRepeat())
 {
 case 0:
 player3->setRepeat(true);
 player_is_onloop[bum]=1;
 break;
 case 1:
 player3->setRepeat(false);
 player_is_onloop[bum]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4-> getRepeat())
 {
 case 0:
 player4->setRepeat(true);
 player_is_onloop[bum]=1;
 break;
 case 1:
 player4->setRepeat(false);
 player_is_onloop[bum]=0;
 break;
 default: break;
 }
break;
default: break;
}
}
}
//Backward des 4 lecteurs
if (control==640+bum)
{
if(player_ignited[bum]==1  && position_of_file_in_player[bum]-100000>0)
{
switch(bum)
{
 case 0://PLAYER 1
    player1->setPosition(position_of_file_in_player[bum]-100000);
    break;
    case 1://PLAYER 2
    player2->setPosition(position_of_file_in_player[bum]-100000);
    break;
    case 2://PLAYER 3
    player3->setPosition(position_of_file_in_player[bum]-1000000);
    break;
    case 3://PLAYER 4
    player4->setPosition(position_of_file_in_player[bum]-100000);
    break;
    default: break;
}
}
midi_show_flash_backwardtouch[bum]=1;
/*if(enable_launchpad==1){launchpad_impulsion(control, orange);}*/
}
//FORward des 4 lecteurs
if (control==644+bum)
{
if(player_ignited[bum]==1 && position_of_file_in_player[bum]+100000<length_of_file_in_player[bum])
{
switch(bum)
{
  case 0://PLAYER 1
    player1->setPosition(position_of_file_in_player[bum]+100000);
    break;
    case 1://PLAYER 2
    player2->setPosition(position_of_file_in_player[bum]+100000);
    break;
    case 2://PLAYER 3
    player3->setPosition(position_of_file_in_player[bum]+100000);
    break;
    case 3://PLAYER 4
    player4->setPosition(position_of_file_in_player[bum]+100000);
    break;
    default: break;
}
}
midi_show_flash_forwardtouch[bum]=1;
/*if(enable_launchpad==1){launchpad_impulsion(control, orange);}*/
}
//CUE SET IN des 4 lecteurs
if (control==648+bum)
{
if(player_ignited[bum]==1 && index_edit_audio==1)
{
switch(bum)
{
case 0://PLAYER 1
if(index_main_clear==0)
{
player_seek_position[bum]=(player1->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else  if(player_loop_out_position[bum]!=player_seek_position[bum]) {player_seek_position[bum]=0;index_main_clear=0;}
break;
case 1://PLAYER 2
if(index_main_clear==0)
{
player_seek_position[bum]=(player2->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else  if(player_loop_out_position[bum]!=player_seek_position[bum]) {player_seek_position[bum]=0;index_main_clear=0;}
break;
case 2://PLAYER 3
if(index_main_clear==0)
{
player_seek_position[bum]=(player3->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else  if(player_loop_out_position[bum]!=player_seek_position[bum]) {player_seek_position[bum]=0;index_main_clear=0;}
break;
case 3://PLAYER 4
if(index_main_clear==0)
{
player_seek_position[bum]=(player4->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else  if(player_loop_out_position[bum]!=player_seek_position[bum]) {player_seek_position[bum]=0;index_main_clear=0;}
break;
default: break;
}
}
midi_show_flash_cueIntouch[bum]=1;
/*if(enable_launchpad==1){launchpad_impulsion(control,red);}*/
}
//CUE SET OUT des 4 lecteurs
if (control==652+bum)
{
if(player_ignited[bum]==1 && index_edit_audio==1)
{
switch(bum)
{

case 0://PLAYER 1
if(index_main_clear==0)
{
player_loop_out_position[bum]=(player1->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else if(player_loop_out_position[bum]!=player_seek_position[bum]) {player_loop_out_position[bum]=(player1->getLength());}
break;
case 1://PLAYER 2
if(index_main_clear==0)
{
player_loop_out_position[bum]=(player2->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else if(player_loop_out_position[bum]!=player_seek_position[bum])  {player_loop_out_position[bum]=(player2->getLength());}
break;
case 2://PLAYER 3
if(index_main_clear==0)
{
player_loop_out_position[bum]=(player3->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else if(player_loop_out_position[bum]!=player_seek_position[bum])  {player_loop_out_position[bum]=(player3->getLength());}
break;
case 3://PLAYER 4
if(index_main_clear==0)
{
player_loop_out_position[bum]=(player4->getPosition());
if(player_loop_out_position[bum]<=player_seek_position[bum]){player_loop_out_position[bum]=player_seek_position[bum]+1;}
}
else  if(player_loop_out_position[bum]!=player_seek_position[bum]) {player_loop_out_position[bum]=(player4->getLength());}
break;
default: break;
}
/*if(enable_launchpad==1){launchpad_impulsion(control, red);}*/
midi_show_flash_cueOuttouch[bum]=1;
}
}
//CUE ON OFF des 4 lecteurs
if (control==656+bum)
{
if(player_ignited[bum]==1)
{
switch(bum)
{
 case 0://PLAYER 1
 switch(player1-> getRepeat())
 {
 case 0:
 player1->setRepeat(true);
 player_is_onloopCue[bum]=1;
 break;
 case 1:
 player1->setRepeat(false);
 player_is_onloopCue[bum]=0;
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2-> getRepeat())
 {
 case 0:
 player2->setRepeat(true);
 player_is_onloopCue[bum]=1;
 break;
 case 1:
 player2->setRepeat(false);
 player_is_onloopCue[bum]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3-> getRepeat())
 {
 case 0:
 player3->setRepeat(true);
 player_is_onloopCue[bum]=1;
 break;
 case 1:
 player3->setRepeat(false);
 player_is_onloopCue[bum]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4-> getRepeat())
 {
 case 0:
 player4->setRepeat(true);
 player_is_onloopCue[bum]=1;
 break;
 case 1:
 player4->setRepeat(false);
 player_is_onloopCue[bum]=0;
 break;
 default: break;
 }
break;
default: break;
}
}
}
//CUE SEEK des 4 lecteurs
if (control==660+bum)
{
if(player_ignited[bum]==1)
{
switch(bum)
{
case 0://PLAYER 1
 player1->setPosition(player_seek_position[bum]);
break;
case 1://PLAYER 2
 player2->setPosition(player_seek_position[bum]);
break;
case 2://PLAYER 3
 player3->setPosition(player_seek_position[bum]);
break;
case 3://PLAYER 4
 player4->setPosition(player_seek_position[bum]);
break;
default: break;
}
midi_show_flash_cueSeektouch[bum]=1;
/*if(enable_launchpad==1){launchpad_impulsion(control, red);}*/
}

}

//fin boucle des 4 lecteurs
}
////////////////NUMPAD MIDI/////////////////////
////////////////WHEEL LEVEL////////////////////
if (control==664)
{
   do_wheel_level_job(midi_levels[664]);
   angle_snap_pad=(((PIknob*2)+angle_correction_wheel) / 128)*midi_levels[664];
   pad_vx = cos(angle_snap_pad)* rayon_wheel_level;
   pad_vy = sin(angle_snap_pad)* rayon_wheel_level;
   position_curseur_pad_x= xnum_window+10+260+pad_vx;
   position_curseur_pad_y=ynum_window+35+pad_vy ;
   index_level_attribue=1;

}
if(control==665){simulate_keypress(KEY_ENTER<<8);}
if(control==666){simulate_keypress(KEY_PLUS_PAD<<8);}
if(control==667){simulate_keypress(KEY_MINUS_PAD<<8);}
if(control==668){simulate_keypress(KEY_UP<<8);}
if(control==669){simulate_keypress(KEY_DOWN<<8);}
if(control==670){simulate_keypress(KEY_0<<8);}
if(control==671){simulate_keypress(KEY_1<<8);}
if(control==672){simulate_keypress(KEY_2<<8);}
if(control==673){simulate_keypress(KEY_3<<8);}
if(control==674){simulate_keypress(KEY_4<<8);}
if(control==675){simulate_keypress(KEY_5<<8);}
if(control==676){simulate_keypress(KEY_6<<8);}
if(control==677){simulate_keypress(KEY_7<<8);}
if(control==678){simulate_keypress(KEY_8<<8);}
if(control==679){simulate_keypress(KEY_9<<8);}
if(control==680){simulate_keypress(KEY_COMMA<<8);}//POINT
if(control==681){simulate_keypress(KEY_ESC<<8);}//ESC
if(control==682){simulate_keypress(KEY_Y<<8);}//ALL
if(control==683){simulate_keypress(KEY_U<<8);}//INV
if(control==684){simulate_keypress(KEY_TAB<<8);}
if(control>=685 && control<=733) //STOPOS FADERS
{
if(index_do_dock==0 && index_main_clear==0)
{
ActionnateStopOn[control-685]=toggle(ActionnateStopOn[control-685]);mouse_released=1;
}

else if(index_do_dock==1 && index_main_clear==0 )
{
if(numeric_postext>0 )//affectation stop pos par chaine de carcatere
{
int lStopPos=999;
    switch(dmx_view)
    {
    case 0:
    lStopPos=(int)((atof(numeric) *2.55) +1);//+1 pour arrondir le %
    break;
    case 1:
    lStopPos=atol(numeric);
    break;
    default: break;
    }
reset_numeric_entry();
if (lStopPos>=0 && lStopPos<=255)
   {
   StopPosOn[control-685]=1;LevelStopPos[control-685]=lStopPos;
   index_do_dock=0;
   do_light_setpos[control-685]=1;
   }
}
else if (numeric_postext==0) //affectation stop pos depuis le cursuer fader
{
StopPosOn[control-685]=1;LevelStopPos[control-685]=Fader[control-685];
index_do_dock=0;
do_light_setpos[control-685]=1;
}
}

else if(index_main_clear==1 && index_do_dock==0)//clear
{
StopPosOn[control-685]=0;
LevelStopPos[control-685]=999;
index_main_clear=0;
do_light_setpos[control-685]=1;
}
}
///////////FENETRE BANGER/////////////////////////////////////////////////////
if (control==734)
{
start_time_for_banger[index_banger_selected]=actual_time;
end_time_for_banger[index_banger_selected]=0;
//reset du banger concerné
for (int o=0;o<6;o++)//reset des évènements
{
event_sended[index_banger_selected][o]=0;
if(bangers_delay[index_banger_selected][o]>end_time_for_banger[index_banger_selected])
{end_time_for_banger[index_banger_selected]=(int)(bangers_delay[index_banger_selected][o]);}
}
bang_is_sended[index_banger_selected]=0;//reset du bang sended is
do_light_bang_it=1;
//rest(midi_keyboard_wait);
/*if(enable_launchpad==1){launchpad_impulsion(control, red);} */
}

if (control>=735 && control<=740)
{
Bang_event(index_banger_selected,control-735);
do_light_bang_solo[control-735]=1;
//rest(midi_keyboard_wait);
/*if(enable_launchpad==1){launchpad_impulsion(control, red);}*/
}
//PLUS MOINS PAGES BANGER
if(control==741)
{
if(index_banger_selected>0){index_banger_selected--;}
/*if(enable_launchpad==1){launchpad_impulsion(control, red);}*/
rest(midi_keyboard_wait);
}
if(control==742)
{
if(index_banger_selected<127){index_banger_selected++;}
/*if(enable_launchpad==1){launchpad_impulsion(control, red);} */
rest(midi_keyboard_wait);
}

//////////////GRANDES COMMANDES APPEL FENETRES//////////////////////////////////
if(control>=743 && control<=757)
{
switch(control)
{
case 743: //DOCK
index_do_modify=0;
index_do_report=0;
index_main_clear=0;
index_do_dock=toggle(index_do_dock);

switch(index_do_dock)
{
case 0:
 sprintf(string_Last_Order,">> Record ready");
break;
case 1:
 sprintf(string_Last_Order,">> No Record");
break;
default: break;
}

switch (window_focus_id)
{
case W_CHASERS:
index_affect_chaser_to_dock=index_do_dock;
break;
case W_GRID:
for(int i=0;i<4;i++)
{
if(index_show_grid_player[i]==1)
{
gridplayer_to_affect_is=i; break;
}
}
break;
case W_MOVER:
index_affect_to_dock_mover=index_do_dock;
break;
case W_DRAW:
index_affect_draw_to_dock=index_do_dock;
break;
case W_ECHO:
index_affect_echo_to_dock=index_do_dock;
break;
case W_TIME:
index_affect_time=index_do_dock;
break;
case W_TRACKINGVIDEO:
index_affect_video_tracking_to_dock=index_do_dock;
break;
case W_TRICHROMY:
index_affect_color_to_dock=index_do_dock;
break;
case W_AUDIO:
index_affect_audio_to_dock=index_do_dock;
player_to_affect_to_dock=0;
audio_type_for_dock_affectation_is=0;
break;
case W_CFGMENU:
if(config_page_is==1) { index_affect_dmxin=index_do_dock; }
else if(config_page_is==3) {index_do_affect_net_to_dock=index_do_dock; }
break;
default:
break;
}

break;
case 744://MODIFY
           if(index_do_modify==0)
                {reset_index_actions();index_do_modify=1;
                sprintf(string_Last_Order,">> Modify ready");
                }
           else if(index_do_modify==1)
                {
                index_do_modify=0;
                sprintf(string_Last_Order,">> No Modify");
                }
break;
case 745://REPORT
           if(index_do_report==0)
                {reset_index_actions();index_do_report=1;
                sprintf(string_Last_Order,">> Report ready");
                }
           else if(index_do_report==1)
                {
                index_do_report=0;
                sprintf(string_Last_Order,">> No Report");
                }
break;
case 746://clear
                 if(index_main_clear==0)
                {reset_index_actions();index_main_clear=1;
                sprintf(string_Last_Order,">> Clear ready");
                }
                 else if(index_main_clear==1)
                {
                index_main_clear=0;
                sprintf(string_Last_Order,">> Clear Report");
                }
break;
case 747:       //NAME
               index_type=toggle(index_type);
               //sab 02/03/2014 sprintf(numeric,"");numeric_postext=0;
               strcpy(numeric,"");
               numeric_postext=0;
break;
case 748://TIME
          if(index_time==0){add_a_window(W_TIME);  }
           else {   substract_a_window(W_TIME); }
break;
case 749:     //TRICHRO
if(index_trichro_window==0){add_a_window(W_TRICHROMY);}
else  { substract_a_window(W_TRICHROMY);  }
break;
case 750://CAMERA
 if(index_video_window==0){ add_a_window(W_TRACKINGVIDEO); }
 else{ substract_a_window(W_TRACKINGVIDEO);}
break;
case 751://SEQUENCIEL
          if(index_window_sequentiel==0){;add_a_window(W_SEQUENCIEL);}
          else {substract_a_window(W_SEQUENCIEL);}
break;
case 752://FADERS
 if(index_show_faders==0){add_a_window(W_FADERS);}
else {substract_a_window(W_FADERS);}
break;
case 753://BANGERS
          if(index_show_banger_window==0)
          {add_a_window(W_BANGER);mouse_level_for_event=mouse_z;mouse_level_for_banger=mouse_z;}
          else {substract_a_window(W_BANGER);}
break;
case 754://BLIND
          index_blind=toggle(index_blind);
break;
case 755://CFG MAIN
 if(index_show_config_window==0){add_a_window(W_CFGMENU);}
else {substract_a_window(W_CFGMENU);}
break;
case 756://AUDIO PLAYERS
if(index_show_audio_window==0){add_a_window(W_AUDIO);}
else {substract_a_window(W_AUDIO);}
reset_audio_indexs_to_dock();
break;
case 757://QUIT
          index_ask_confirm=1;index_do_quit_with_save=1;
break;
}
rest(midi_keyboard_wait);
}


//////////////////FENETRE TIME FUNCTION
if(control>=758 && control<=766)
{
switch(control)
{
case 758://roue
   angle_timesnap=(5.980005 / 128)*midi_levels[758];
   vtimex = cos(angle_timesnap)*100;
   vtimey = sin(angle_timesnap)*100;
   position_curseur_time_x= xtime_window+150+vtimex;
   position_curseur_time_y=ytime_window+150+vtimey ;
   if(time_wheel_datatype_is==0)//minutes
   {
   angle_timesnap_min=angle_timesnap;
   time_minutes=(int)((angle_timesnap_min/5.980005)*60);
   }
   if(time_wheel_datatype_is==1)//secondes
   {
   angle_timesnap_sec=angle_timesnap;
   time_secondes=(int)((angle_timesnap_sec/5.980005)*60);
   }
   if(time_wheel_datatype_is==2)//dixiemes
   {
   angle_timesnap_dix=angle_timesnap;
   time_centiemes=(int)((angle_timesnap_dix/5.980005)*100);
   }
break;
case 759://type de temps
time_wheel_datatype_is++;
if(time_wheel_datatype_is>2){time_wheel_datatype_is=0;}
set_time_cursor_to_time_type(time_wheel_datatype_is);
break;
case 760://delay in
if(index_type_of_time_to_affect[0]==0){index_type_of_time_to_affect[0]=1;}
else if(index_type_of_time_to_affect[0]==1){index_type_of_time_to_affect[0]=0;}
break;
case 761://in
if(index_type_of_time_to_affect[1]==0){index_type_of_time_to_affect[1]=1;}
else if(index_type_of_time_to_affect[1]==1){index_type_of_time_to_affect[1]=0;}
break;
case 762://delay out
if(index_type_of_time_to_affect[2]==0){index_type_of_time_to_affect[2]=1;}
else if(index_type_of_time_to_affect[2]==1){index_type_of_time_to_affect[2]=0;}
break;
case 763://time out button
if(index_type_of_time_to_affect[3]==0){index_type_of_time_to_affect[3]=1;}
else if(index_type_of_time_to_affect[3]==1){index_type_of_time_to_affect[3]=0;}
break;
case 764://affect time button
if(index_affect_time==0){index_affect_time=1;}
else if(index_affect_time==1){index_affect_time=0;}
break;
case 765: //chrono play pause
Chrono_PlayPause();
break;
case 766://chrono reset
Chrono_Reset();
break;
default: break;
}
}

//MOVE FADER SPACE
if(control==767)
{
scroll_faderspace=((920/128)*midi_levels[767])-15;   //920 valeur tres personnelle  //-15 pour avant les faders: group et all at
}

//RAJOUT SEQUENCIEL NAVIG RAPIDE
if(control==768)// create new mem
{
reset_indexs_confirmation();
index_do_create_mem=1;
index_ask_confirm=1;
}
if(control==769)// delete new mem
{
reset_indexs_confirmation();
index_do_delete_mem=1;
index_ask_confirm=1;
}
if(control==770)// stage minus
{
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
refresh_integrated_gridplayer1();
someone_changed_in_sequences=1;//icat
}
if(control==771)// stage plus
{
if(index_go==0 && index_go_back==0 && index_pause==0)
           {
           position_onstage=position_preset;
           }
            else {index_go=0;index_pause=0; index_go_back=0;}
position_onstage=position_preset;
refresh_mem_onstage(position_onstage);
detect_mem_before_one();
detect_mem_preset();
refresh_mem_onpreset(position_preset);
niveauX1=255; niveauX2=0;
refresh_banger_wx();
refresh_integrated_gridplayer1();
someone_changed_in_sequences=1;//icat
}
if(control==772)// preset minus
{
index_go=0;index_pause=0; index_go_back=0;
detect_mem_preset_previous();
refresh_mem_onpreset(position_preset);
niveauX2=0;
someone_changed_in_sequences=1;//icat
}
if(control==773)// preset plus
{
index_go=0;index_pause=0; index_go_back=0;
detect_next_preset();
refresh_mem_onpreset(position_preset);
niveauX2=0;
someone_changed_in_sequences=1;//icat
}


////////////MINIFADERS COMMMAND PANNEL//////////////////////////////////////////

if(control==774)//previous sel
{
position_minifader_selected--;
if(position_minifader_selected<0){position_minifader_selected=48;}
refresh_minifader_state_view_core(position_minifader_selected);
do_light_minifaders_commands[0]=1;
}
if(control==775)//next sel
{
position_minifader_selected++;
if(position_minifader_selected>48){position_minifader_selected=0;}
refresh_minifader_state_view_core(position_minifader_selected);
do_light_minifaders_commands[1]=1;
}
if(control==776 && midi_levels[control]!=0)//select
{
minifaders_selected[position_minifader_selected]=toggle(minifaders_selected[position_minifader_selected]);
do_light_minifaders_commands[2]=1;
}
if(control==777)//unselect
{
for(int l=0;l<core_user_define_nb_faders;l++)
{
minifaders_selected[l]=0;
}
do_light_minifaders_commands[3]=1;
}

if(control==778)//FLASH
{
if(midi_levels[778]>0)
{
 for(int tt=0;tt<core_user_define_nb_faders;tt++)
 {
 if( minifaders_selected[tt]==1  && FaderIsFlash[tt]==0)
 {FaderIsFlash[tt]=1; }
 }
}
else //key on ==0
{
      for(int tn=0;tn<core_user_define_nb_faders;tn++)
      {
      if( minifaders_selected[tn]==1)
      {FaderIsFlash[tn]=0; }
      }
}
}


if(control>778 && control<793)
{
do_action_on_selected_minifaders(control-778);
do_light_minifaders_commands[(control-774)]=1;//decalages
}


if(control>=794 && control<802)//minifaders preset de selection
{
int log=control-794;

for(int olp=0;olp<core_user_define_nb_faders;olp++)
{
minifaders_selected[olp]=minifaders_preset_selection[log][olp];
}
sprintf(string_Last_Order,"Called Fader Selection from Preset %d", log+1);
}

////////SUITE FADERS//////////////////////////

//Loop the dock
if(control>=802 && control<851 )
{
int docktotouch=(dock_used_by_fader_is[control-802]);
is_dock_for_lfo_selected[control-802][docktotouch]=toggle(is_dock_for_lfo_selected[control-802][docktotouch]);
}


//Loop ALL the dock
if(control>=851 && control<900 )
{
bool index_choose_mode_dkloop=0;//0 toggle tt le monde / 1 copie l etat du dck selctionné dans tt le monde

for (int ck=0;ck<core_user_define_nb_docks-1;ck++)
{
if(is_dock_for_lfo_selected[control-851][ck]!=is_dock_for_lfo_selected[control-851][ck+1])
{index_choose_mode_dkloop=1;break;}
}
switch(index_choose_mode_dkloop)
{
case 0:
for(int op=0;op<core_user_define_nb_docks;op++)
{
 is_dock_for_lfo_selected[control-851][op]=toggle(is_dock_for_lfo_selected[control-851][op]);
}
break;
case 1:
//tout le monde prend la valeur du dock selectionné
for(int j=0;j<core_user_define_nb_docks;j++)
{
if(DockIsSelected[control-851][j]==1)
{
int tempval_dockloop=toggle(is_dock_for_lfo_selected[control-851][j]);
for(int k=0;k<core_user_define_nb_docks;k++)
{
is_dock_for_lfo_selected[control-851][k]=toggle(tempval_dockloop);
}
break;
}
}
break;
default: break;
}
}

//FLASH
if(control>=900 && control<949)
{
if(midi_levels[control]>0)
{
 FaderIsFlash[control-900]=toggle(FaderIsFlash[control-900]);// auparavant =1
}
else  //key on ==0
{
 FaderIsFlash[control-900]=0;
}
}

//selection dock color
if(control>=949 && control<957)
{
dock_color_selected=control-949;
load_etat_picker_dans_dockcolor(dock_color_selected);
sprintf(string_Last_Order,">>MIDI Dock Color Selected %d",(dock_color_selected+1));
}

//selection video roi et video tracking preset
if(control>=957 && control<969)//trcaks roi
{
tracking_spaces_on_off[tracking_dock_selected][control-957] =toggle(tracking_spaces_on_off[tracking_dock_selected][control-957]);
}
if(control>=969 && control<974)//tracking preset
{
tracking_dock_selected=control-969;
}


///////////////CHASER SELECTED CONTROLS
/*974 Chaser -
975 Chaser +
976 view track Up
977 view track down
978 Play
979 Seek
980 Loop*/
if(control==974 && midi_levels[control]>0)//chaser selected up
{
chaser_selected--;
if(chaser_selected<0){chaser_selected=core_user_define_nb_chasers-1;}
refresh_chaser_midi_out();
}
if(control==975 && midi_levels[control]>0)//chaser selected down
{
chaser_selected++;
if(chaser_selected>core_user_define_nb_chasers-1){chaser_selected=0;}
refresh_chaser_midi_out();
}
if(control==976 && midi_levels[control]>0)//chaser track up
{
position_affichage_track_num[chaser_selected]--;
if(position_affichage_track_num[chaser_selected]<0){position_affichage_track_num[chaser_selected]=0;}
}
if(control==977 && midi_levels[control]>0)//chaser track down
{
position_affichage_track_num[chaser_selected]++;
if(position_affichage_track_num[chaser_selected]> core_user_define_nb_tracks_per_chasers-nbre_track_visualisables)
{position_affichage_track_num[chaser_selected]= core_user_define_nb_tracks_per_chasers-nbre_track_visualisables;}
}

if(control==978 && midi_levels[control]>0)
{
chaser_is_playing[chaser_selected]=toggle(chaser_is_playing[chaser_selected]);
if(chaser_is_playing[chaser_selected]==1)//snap du temps at beg
{
chaser_start_time[chaser_selected]=actual_time;
}
}

if(control==979 && midi_levels[control]>0)
{
chaser_seek_at_beg(chaser_selected);
}

if(control==980 && midi_levels[control]>0)
{
chaser_is_in_loop[chaser_selected]=toggle(chaser_is_in_loop[chaser_selected]);
switch(chaser_is_in_loop[chaser_selected])
{
case 0:
sprintf(string_Last_Order,">> LOOP OFF Chaser %d",chaser_selected+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON Chaser %d",chaser_selected+1);
break;
default: break;
}
}
/*
981 Forward
982 backward
983 aller retour
984 All
985 Seek
986 Off
987 -> 990 P1 à P4

*/
if(control==981 && midi_levels[control]>0)
{
chaser_way[chaser_selected]=0;
}
if(control==982 && midi_levels[control]>0)
{
chaser_way[chaser_selected]=1;
}
if(control==983 && midi_levels[control]>0)
{
chaser_aller_retour[chaser_selected]=toggle(chaser_aller_retour[chaser_selected]);
}
if(control==984 && midi_levels[control]>0)
{
chaser_select_all_track(chaser_selected);
}
if(control==985 && midi_levels[control]>0)
{
chaser_select_inv_track(chaser_selected);
}
if(control==986 && midi_levels[control]>0)
{
chaser_select_off_all_track(chaser_selected);
}
//Preset  1 à 4
if(control==987 && midi_levels[control]>0)
{
chaser_load_from_preset(chaser_selected,0);
}
if(control==988 && midi_levels[control]>0)
{
chaser_load_from_preset(chaser_selected,1);
}
if(control==989 && midi_levels[control]>0)
{
chaser_load_from_preset(chaser_selected,2);
}
if(control==990 && midi_levels[control]>0)
{
chaser_load_from_preset(chaser_selected,3);
}
/*
991-> 993 Operator Up Stay Down
994 T join / T Std*/

if(control==991 && midi_levels[control]>0)
{
 if(chaser_operator_is!=1){chaser_operator_is=1; }
 else {chaser_operator_is=0;}
}
if(control==992 && midi_levels[control]>0)
{
 if(chaser_operator_is!=2){chaser_operator_is=2;  }
 else {chaser_operator_is=0;}
}
if(control==993 && midi_levels[control]>0)
{
  if(chaser_operator_is!=3){chaser_operator_is=3; }
 else {chaser_operator_is=0;}
}

if(control==994 && midi_levels[control]>0)
{
chaser_time_mode[chaser_selected]=toggle(chaser_time_mode[chaser_selected]);
}
/*
995 Beg Point
996 End Point
997 Pos Timeline*/
if(control==995 )
{
chaser_begin_step_is[chaser_selected]=(int)((36.0/127)*midi_levels[control]);
if(chaser_begin_step_is[chaser_selected]>=chaser_end_step_is[chaser_selected])
{chaser_begin_step_is[chaser_selected]=chaser_end_step_is[chaser_selected]-1;}
if(chaser_begin_step_is[chaser_selected]<0){chaser_begin_step_is[chaser_selected]=0;}
}
if(control==996)
{
chaser_end_step_is[chaser_selected]=(int)((36.0/127)*midi_levels[control]);
if(chaser_end_step_is[chaser_selected]<=chaser_begin_step_is[chaser_selected])
{chaser_end_step_is[chaser_selected]=chaser_begin_step_is[chaser_selected]+1;}
if(chaser_end_step_is[chaser_selected]>nbre_de_cases_par_track){chaser_end_step_is[chaser_selected]=nbre_de_cases_par_track;}
}
if(control==997)
{
chaser_step_is[chaser_selected]=(int)((36.0/127)*midi_levels[control]);
if(chaser_step_is[chaser_selected]<0){chaser_step_is[chaser_selected]=0;}
if(chaser_step_is[chaser_selected]>nbre_de_cases_par_track){chaser_step_is[chaser_selected]=nbre_de_cases_par_track;}
chaser_calcul_step(chaser_selected,0.0);
chaser_calcul_time_joint(chaser_selected);
}

/*998 -> 1022 ON OFF tracks
1023 -> 1047 Level tracks*/
if(control>=998 && control<1023 && midi_levels[control]>0)
{
track_is_on[chaser_selected][control-998]=toggle(track_is_on[chaser_selected][control-998]);
}

if(control>=1023 && control<1048 )
{
track_level[chaser_selected][control-1023]=midi_levels[control];
}


//Chasers Affectation des états des steps à la volée en midi
if(control>=1048 && control<1113 && index_enable_edit_chaser==1 && launchpad_chaser_mode==1)
{
int piste=(int)((float)(control-1048)/8);
int step_of=chaser_step_launchpad[chaser_selected]+ ((control-1048-(piste*8))%8);

if(step_of>=0 && step_of<nbre_de_cases_par_track)
{
if(chaser_step_operation[chaser_selected][piste][step_of]!=chaser_operator_is)
chaser_step_operation[chaser_selected][piste][step_of]=chaser_operator_is;
else
{
chaser_step_operation[chaser_selected][piste][step_of]=0;
}

}
refresh_launchpad_on_chaser();
}

if(control==1113)//launchpad pos minus
{
chaser_step_launchpad[chaser_selected]--;
if(chaser_step_launchpad[chaser_selected]<0){chaser_step_launchpad[chaser_selected]=0;}
}
if(control==1114)//launchpad pos plus
{
chaser_step_launchpad[chaser_selected]++;
if(chaser_step_launchpad[chaser_selected]>nbre_de_cases_par_track-8 ) {chaser_step_launchpad[chaser_selected]=nbre_de_cases_par_track-8;}

}

//commandes faders pour chasers
if(control>=1115 && control <=1163  && midi_levels[control]>0)//Faders: Play embeded chaser
{
int the_chaser;
int the_grid_player;
int the_audio_player;

if ( DockTypeIs[control-1115][dock_used_by_fader_is[control-1115]]==11) the_chaser=ChaserAffectedToDck[control-1115][dock_used_by_fader_is[control-1115]];
else if ( DockTypeIs[control-1115][dock_used_by_fader_is[control-1115]]==12 )  the_grid_player=faders_dock_grid_affectation[control-1115][dock_used_by_fader_is[control-1115]];
else if( DockTypeIs[control-1115][dock_used_by_fader_is[control-1115]]==6 ) the_audio_player=DockHasAudioVolume[control-1115][dock_used_by_fader_is[control-1115]]-1;
else if ( DockTypeIs[control-1115][dock_used_by_fader_is[control-1115]]==7 ) the_audio_player=DockHasAudioPan[control-1115][dock_used_by_fader_is[control-1115]]-1;
else if ( DockTypeIs[control-1115][dock_used_by_fader_is[control-1115]]==8 ) the_audio_player=DockHasAudioPitch[control-1115][dock_used_by_fader_is[control-1115]]-1;

switch(DockTypeIs[control-1115][dock_used_by_fader_is[control-1115]])
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
 player1_do_stop();
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
 player2_do_stop();
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
 player3_do_stop();
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
 player4_do_stop();
 break;
 default: break;
 }
break;
default: break;
}
switch(player_is_playing[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",control-1115+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",control-1115+1,the_audio_player+1);
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
 player1_do_stop();
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
 player2_do_stop();
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
 player3_do_stop();
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
 player4_do_stop();
 break;
 default: break;
 }
break;
default: break;
}

switch(player_is_playing[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",control-1115+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",control-1115+1,the_audio_player+1);
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
 player1_do_stop();
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
 player2_do_stop();
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
 player3_do_stop();
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
 player4_do_stop();
 break;
 default: break;
 }
break;
default: break;
}
switch(player_is_playing[the_audio_player])//inversed by action
{
case 0:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",control-1115+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",control-1115+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Chaser %d",control-1115+1,the_chaser+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Chaser %d",control-1115+1,the_chaser+1);
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
sprintf(string_Last_Order,">> PLAY OFF from Fader %d GridPl %d",control-1115+1,the_grid_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY ON from Fader %d GridPl %d",control-1115+1,the_grid_player+1);
break;
default: break;
}
break;
default:
break;
}

}
if(control>=1164 && control <=1212  && midi_levels[control]>0)//Faders: Seek to beg embeded chaser
{
int the_chaser;
int the_grid_player;
int the_audio_player;

if ( DockTypeIs[control-1164][dock_used_by_fader_is[control-1164]]==11) the_chaser=ChaserAffectedToDck[control-1164][dock_used_by_fader_is[control-1164]];
else if ( DockTypeIs[control-1164][dock_used_by_fader_is[control-1164]]==12 )  the_grid_player=faders_dock_grid_affectation[control-1164][dock_used_by_fader_is[control-1164]];
else if( DockTypeIs[control-1164][dock_used_by_fader_is[control-1164]]==6 ) the_audio_player=DockHasAudioVolume[control-1164][dock_used_by_fader_is[control-1164]]-1;
else if ( DockTypeIs[control-1164][dock_used_by_fader_is[control-1164]]==7 ) the_audio_player=DockHasAudioPan[control-1164][dock_used_by_fader_is[control-1164]]-1;
else if ( DockTypeIs[control-1164][dock_used_by_fader_is[control-1164]]==8 ) the_audio_player=DockHasAudioPitch[control-1164][dock_used_by_fader_is[control-1164]]-1;

switch(DockTypeIs[control-1164][dock_used_by_fader_is[control-1164]])
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
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",control-1164+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",control-1164+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",control-1164+1,the_audio_player+1);
}
break;
case 11://chaser
chaser_seek_at_beg(the_chaser);
sprintf(string_Last_Order,">> Seek To Beg from Fader %d Chaser %d",control-1164+1,the_chaser+1);
break;
case 12://grid
gridplayer_seek(the_grid_player);
sprintf(string_Last_Order,">> Seek from Fader %d GridPl %d",control-1164+1,the_grid_player+1);
break;
default:
break;
}
}


if(control>=1213 && control <=1264  && midi_levels[control]>0)//Faders: Seek to beg embeded chaser
{


int the_chaser;
int the_grid_player;
int the_audio_player;

if ( DockTypeIs[control-1213][dock_used_by_fader_is[control-1213]]==11) the_chaser=ChaserAffectedToDck[control-1213][dock_used_by_fader_is[control-1213]];
else if ( DockTypeIs[control-1213][dock_used_by_fader_is[control-1213]]==12 )  the_grid_player=faders_dock_grid_affectation[control-1213][dock_used_by_fader_is[control-1213]];
else if( DockTypeIs[control-1213][dock_used_by_fader_is[control-1213]]==6 ) the_audio_player=DockHasAudioVolume[control-1213][dock_used_by_fader_is[control-1213]]-1;
else if ( DockTypeIs[control-1213][dock_used_by_fader_is[control-1213]]==7 ) the_audio_player=DockHasAudioPan[control-1213][dock_used_by_fader_is[control-1213]]-1;
else if ( DockTypeIs[control-1213][dock_used_by_fader_is[control-1213]]==8 ) the_audio_player=DockHasAudioPitch[control-1213][dock_used_by_fader_is[control-1213]]-1;

switch(DockTypeIs[control-1213][dock_used_by_fader_is[control-1213]])
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",control-1213+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",control-1213+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",control-1213+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",control-1213+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",control-1213+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",control-1213+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Chaser %d",control-1213+1, the_chaser+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Chaser %d",control-1213+1, the_chaser+1);
break;
default: break;
}
break;
case 12: //grid
grider_autostopmode[the_grid_player]=toggle(grider_autostopmode[the_grid_player]);
switch(grider_autostopmode[the_grid_player])
{
case 0:
sprintf(string_Last_Order,">> AutoStop OFF from Fader %d Gpl %d",control-1213+1, the_grid_player+1);
break;
case 1:
sprintf(string_Last_Order,">> AutoStop ON from Fader %d Gpl %d",control-1213+1, the_grid_player+1);
break;
default: break;
}
break;
default:
break;
}

}

//iCat pages
/*1265 1266 iCatPage - +
1267 ->1274 iCatpage Num
1275 icat Oreintation
1276 icat refresh page construction*/
if(control>=1265 && control<=1276 && enable_iCat==1 && iCat_serveur_is_initialized==1)
{
if(control==1265 &&  midi_levels[control]>0 )
{
         iCatPageis--;
         if(iCatPageis<0){iCatPageis=7;}
         load_iCat_page(iCatPageis);
         do_send_icat_init_page=1;
}
if(control==1266 &&  midi_levels[control]>0 )
{
    iCatPageis++;
    if(iCatPageis>7){iCatPageis=0;}
    load_iCat_page(iCatPageis);
    do_send_icat_init_page=1;
}
if(control>=1267 && control<=1274 &&  midi_levels[control]>0 )    //page num
{
iCatPageis=control-1267;
load_iCat_page(iCatPageis);
do_send_icat_init_page=1;
}
if(control==1275 &&  midi_levels[control]>0 )
{
   iCat_preset_orientation[iCatPageis]++;
   if(iCat_preset_orientation[iCatPageis]>2){iCat_preset_orientation[iCatPageis]=0;}
   if(iCat_preset_orientation[iCatPageis]==0)
   {
    L_tablier_iCat=160;H_tablier_iCat=240;
   }
   else {L_tablier_iCat=240;H_tablier_iCat=160;}
   do_refresh_iCat(iCatPageis);
}
if(control==1276 &&  midi_levels[control]>0)
{
 do_refresh_iCat(iCatPageis);
}
}
//fin bloc icat

//midi Mute
if(control==1277  )
{
 index_midi_mute=toggle(index_midi_mute);

  switch(index_midi_mute)
  {
  case 0:
    for(int y=0;y<3072;y++)
    {
    is_raccrochage_midi_remote[y]=0;
    sprintf(string_Last_Order,">>Midi IN un-muted");
    }
  break;
  case 1:
    for(int y=0;y<3072;y++)
    {
    is_raccrochage_midi_remote[y]=1;
    sprintf(string_Last_Order,">>Midi IN muted");
    }
  break;
  }
}

if(control>=1278 && control<=1325)
{
autolaunch[control-1278]=toggle( autolaunch[control-1278] );
switch (autolaunch[control-1278])
{
case 0:
sprintf(string_Last_Order,">>Autolaunch OFF Fader %d", control-1278);
break;
case 1:
sprintf(string_Last_Order,">>Autolaunch ON Fader %d", control-1278);
break;
}
}


//////////TAP TEMPO/////////////////////////////

if(control==1326)//tap
{
 set_new_time_in_tap_tempo();
}

if (control==1327)//rec tap
{
index_recording_tap_tempo=toggle(index_recording_tap_tempo);
if(index_recording_tap_tempo==1)
{
start_tempo_ticks=actual_time;nbr_steps_tempo=0;tempo_interm=0;
sprintf(string_tap_tempo_average,"Step:   -    Global: -");
sprintf(string_actual_tap_tempo,"Last: ");
sprintf(string_Last_Order,"Tap Tempo Rec ON");
}
else sprintf(string_Last_Order,"Tap Tempo Rec Off");
}

if (control==1328)//set tap tempo into activ chaser
{

if(numeric_postext==0 && index_window_chasers==1)
            {
            set_chaser_tempo_unit(chaser_selected);
            }
            else//si chiffre de chaser tapé
            {
            int chazr=atoi(numeric);
            if(chazr>0 && chazr<127)
            {
            set_chaser_tempo_unit(chazr-1);
            numeric_postext=0;
            reset_numeric_entry();
            }
            }
do_light_send_tap=1;
}

//rajout appels fenêtres
if(control>=1329 && control<1343)
{
switch(control)
{
case 1329://call wizard windod
if(index_show_wizard_window==0){add_a_window(W_WIZARD);}
else {substract_a_window(W_WIZARD);}
break;
case 1330://call save window

 if(index_menu_save==0){add_a_window(W_SAVE);}
 else {substract_a_window(W_SAVE);}
break;
case 1331: // patch
  if(index_patch_window==0){add_a_window(W_PATCH);}
     else {substract_a_window(W_PATCH);}
break;
case 1332: //list
if(index_list_projecteurs==0){add_a_window(W_LIST);}
else {substract_a_window(W_LIST);}
break;
case 1333: //direct CH
if(index_direct_chan==0 && multiple_direct_chan==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_direct_chan=1; index_do_dock=index_direct_chan;
}
else if(index_direct_chan==1 && multiple_direct_chan==0)
{
index_direct_chan=1;
multiple_direct_chan=1;
index_do_dock=1;
}
else if(index_direct_chan==1 && multiple_direct_chan==1)
{
reset_index_actions();
reset_indexs_confirmation();
}
break;
case 1334: // view
 index_inspekt=toggle(index_inspekt);  i_m_over_a_track=0;
break;
case 1335: // freeze
 index_do_freeze=1;
 index_ask_confirm=1;
break;
case 1336: // minifaders
if(index_show_minifaders==0){add_a_window(W_MINIFADERS);}
else {substract_a_window(W_MINIFADERS);}
break;
case 1337: //chasers
if(index_window_chasers==0){add_a_window(W_CHASERS);}
else {substract_a_window(W_CHASERS);}
break;
case 1338: //numeric pad
  if(index_visual_pad==0){add_a_window(W_NUMPAD);}
 else {substract_a_window(W_NUMPAD);}
break;
case 1339: //Mover
	//sab 02/03/2014 IMPACT if(index_show_mover_window=0){add_a_window(W_MOVER);}
 if(index_show_mover_window==0){add_a_window(W_MOVER);}
 else {substract_a_window(W_MOVER);}
break;
case 1340: //grider
 if(index_grider_window==0){add_a_window(W_GRID);}
 else {substract_a_window(W_GRID);}
break;
case 1341: //iCat builder view
if(index_window_gui_iCat==0){add_a_window(W_iCAT);}
else {substract_a_window(W_iCAT);}
break;
case 1342: //help
index_call_help=toggle(index_call_help);
if(index_call_help==1)
{
system("start /max /wait file:///C:/white_cat/doc/export/introduction.htm");
}
index_call_help=0;
break;
default:
break;
}
}
//les 127 bangers en manuel
if(control>=1343 && control<=1470)
{
bang_is_sended[control-1343]=toggle(bang_is_sended[control-1343]);
switch (bang_is_sended[control-1343])
{
case 0://reset des send events et on demarre à la souris le banger
  for (int y=0;y<6;y++){event_sended[control-1343][y]=0;}
  start_time_for_banger[control-1343]=actual_time;

//calcul bang time de fin
for (int y=0;y<6;y++)
{
if(bangers_delay[control-1343][y]> end_time_for_banger[control-1343])
{
end_time_for_banger[control-1343]= bangers_delay[control-1343][y];
}
}
if(end_time_for_banger[control-1343]<default_time_of_the_bang)
{end_time_for_banger[control-1343]=default_time_of_the_bang;}
///////////////////////
last_banger_sended_manually=control-1343;
//bang_is_sended[control-1343]=0;//pierre group laps
break;
case 1://go back sur le banger
for (int y=0;y<6;y++)
{
if(bangers_type[control-1343][y]!=0 )
{
    Bang_event_back(control-1343, y);
    event_sended[control-1343][y]=1;
}
}
bang_is_sended[control-1343]=1;//bloquage de l envoi des autres évènements
break;
}
}

//GRID AFFICHAGE PLAYERS
if(control>=1472 && control<=1475)
{
if(control-1472<=core_user_define_nb_gridplayers)
{
index_show_grid_player[control-1472]=toggle(index_show_grid_player[control-1472]);
}
//recalcul hauteur fenetre
refresh_hauteur_fenetre_grider();
}
//GRID GRID PLUS MOIN STEP PLUS MOINS DANS GRID PLAYER
if(control>=1476 && control<=1479 )//grid minus
{
int num_grider=control-1476;
if(index_grider_selected[num_grider]>0)
{index_grider_selected[num_grider]--;}
}
if(control>=1480 && control<=1483 )//grid plus
{
int num_grider=control-1480;
if(index_grider_selected[num_grider]<127){index_grider_selected[num_grider]++;}
}
if(control>=1484 && control<=1487 )//step minus
{
int num_grider=control-1484;
gridplayer_step_minus(num_grider);
}
if(control>=1488 && control<=1491 )//step plus
{
int num_grider=control-1488;
gridplayer_step_plus(num_grider);
}
if(control>=1492 && control<=1495 )//play gridplayer
{
int num_grider=control-1492;
 grider_is_playing[num_grider]=toggle(grider_is_playing[num_grider]);
 if(grider_is_playing[num_grider]){grid_crossfade_start_time[num_grider]=actual_time;}
}
if(control>=1496 && control<=1499 )// seek gridplayer
{
int num_grider=control-1496;
gridplayer_seek(num_grider);
}
if(control>=1500 && control<=1503 )// autostop gridplayer
{
int num_grider=control-1500;
grider_autostopmode[num_grider]=toggle(grider_autostopmode[num_grider]);
}

if(control>=1504 && control<=1507 )// slave mode
{
int num_grider=control-1504;
grid_player_slave[num_grider]=toggle(grid_player_slave[num_grider]);
}

if(control>=1508 && control<=1511 )// grid accelerometer speed
{
int num_grider=control-1508;
if(grid_player_slave[num_grider]==0 )
{
grid_crossfade_speed[num_grider]=midi_levels[control];
  if(grid_crossfade_speed[num_grider]<0){grid_crossfade_speed[num_grider]=0;}
  else  if(grid_crossfade_speed[num_grider]>127){grid_crossfade_speed[num_grider]=127;}
//integration gridplayer 1
if(num_grider==0 && index_link_speed_crossfade_to_gpl1==1)
{grid_crossfade_speed[num_grider]=crossfade_speed;}
gridder_prepare_cross(num_grider,index_grider_selected[num_grider],index_grider_step_is[num_grider]);
}
}


if(control>=1512 && control<=1515 )////Goto mode
{
int num_grider=control-1512;
 grider_goto_mode[num_grider]=toggle(grider_goto_mode[num_grider]);
}
if(control>=1516 && control<=1519 )//count mode
{
int num_grider=control-1516;
 grider_count_mode[num_grider]=toggle(grider_count_mode[num_grider]);
}

if(control>=1520 && control<=1523)//on off seek
{
int num_grider=control-1520;
grider_seekto_mode[num_grider]=toggle(grider_seekto_mode[num_grider]);
}

if(control>=1524 && control<=1527 )//stoplplay mode
{
int num_grider=control-1524;
grider_stoplay_mode[num_grider]=toggle(grider_stoplay_mode[num_grider]);
}

if(control>=1528 && control<=1531 )//grid is
{
int num_grider=control-1528;
index_grider_selected[num_grider]=midi_levels[control];
}


if(control>=1532 && control<=1535 )//step is +127
{
int num_grider=control-1532;
index_grider_step_is[num_grider]=midi_levels[control]+(grid_midi_multiple_for_step_call[num_grider]*7);
grid_niveauX1[num_grider]=255;
grid_niveauX2[num_grider]=0;
grid_floatX1[num_grider]=grid_niveauX1[num_grider];
grid_floatX2[num_grider]=grid_niveauX2[num_grider];
gridder_prepare_cross(num_grider, index_grider_selected[num_grider], index_grider_step_is[num_grider]);
if(grider_is_playing[num_grider]==1){grid_crossfade_start_time[num_grider]=actual_time;}
}


if(control>=1536 && control<=1539 )//step is *7
{
int num_grider=control-1536;
grid_midi_multiple_for_step_call[num_grider]=midi_levels[control];
}

if(control==1540)//on off asservissement speed sequenciel sur gridplayer 1
{
index_link_speed_crossfade_to_gpl1=toggle(index_link_speed_crossfade_to_gpl1);
if(index_link_speed_crossfade_to_gpl1==1)
{  grid_crossfade_speed[0]=crossfade_speed;
   midi_levels[1508]=crossfade_speed;
}
}

if(control==1541)//do exlcude channels from GM
{
 index_do_exclude=1;
 index_ask_confirm=1;
}

if(control==1542)
{
 index_do_hipass=toggle( index_do_hipass);
 index_inspekt=index_do_hipass;
}

if(control>=1543 && control<=1590)
{
int fad=control-1543;
fader_mode_with_buffers[fad]++;
if(fader_mode_with_buffers[fad]>5){fader_mode_with_buffers[fad]=0;}
}

if(control==1591)
{
auto_reset_crossfade_speed_on_link=toggle(auto_reset_crossfade_speed_on_link);
}

if(control==1592)
{
if(index_do_fgroup==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_do_fgroup=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_do_fgroup;
}


if(control==1593)
{
index_global_midi_send_on_faders=toggle(index_global_midi_send_on_faders);
set_all_faders_midi_out(index_global_midi_send_on_faders);
do_light_midi_send_on_faders=1;
}

///////////////////////////////////////////
///PLOT

if(control>=1594 && control<=1622)
{
if(control==1594)
{
index_plot_window=toggle(index_plot_window);
switch( index_plot_window)
{
case 0:
substract_a_window(W_PLOT);
break;
case 1:
add_a_window(W_PLOT);
break;
default: break;
}
}

else if(control==1595)
{
plot_index_show_levels=toggle(plot_index_show_levels);
}

else if(control==1596)
{
plot_index_show_levels_from_faders=toggle(plot_index_show_levels_from_faders);
}

//selecteur symbols
else if(control==1597)//UP
{
switch(index_menus_lighting_plot)
{
case 1://shapes
 shape_selected_type++;
 if(shape_selected_type>max_shape_type){shape_selected_type=0;}
    if(index_edit_light_plot==1){change_shape_type(shape_selected_type);}
    refresh_shape_factors(shape_selected_type);
break;
case 2://symbols
 symbol_selected_type++;
 if(symbol_selected_type>max_symbol_type){symbol_selected_type=0;}
 if(index_edit_light_plot==1){change_symbol_type(view_plot_calc_number_is,symbol_selected_type);}
break;
default:
break;
}
}

else if(control==1598)//DOWN
{
switch(index_menus_lighting_plot)
{
case 1://shapes
   shape_selected_type--;
   if(shape_selected_type<0){shape_selected_type=max_shape_type;}
   if(index_edit_light_plot==1){change_shape_type(shape_selected_type);}
   refresh_shape_factors(shape_selected_type);
break;
case 2://symbols
symbol_selected_type--;
  if(symbol_selected_type<0){symbol_selected_type=max_symbol_type;}
  if(index_edit_light_plot==1){change_symbol_type(view_plot_calc_number_is,symbol_selected_type);}
break;
default:
break;
}
}

else if(control==1599)//SLIDER
{
switch(index_menus_lighting_plot)
{
case 1://shapes
shape_selected_type= midi_levels[control]/12;
if(shape_selected_type<0){shape_selected_type=0;}
else if(shape_selected_type>max_shape_type){shape_selected_type=max_shape_type;}
break;
case 2://symbols
symbol_selected_type= midi_levels[control];
if(symbol_selected_type<0){symbol_selected_type=0;}
else if(symbol_selected_type>126){symbol_selected_type=126;}
break;
default:
break;
}
}

else if(control==1600)//ADD A SYMBOL
{
switch(index_menus_lighting_plot)
{
case 1://shapes
 add_shape_to_plot(shape_selected_type);
break;
case 2://symbols
 add_a_symbol_to_plot(view_plot_calc_number_is);
 break;
default:
break;
}
}


else if(control==1601)//ROTATE
{
switch(index_menus_lighting_plot)
{
case 1://shapes
angle_shape_selected=((float)midi_levels[control])/127;
if(angle_shape_selected<0.0){angle_shape_selected=0.0;}
if (angle_shape_selected>1.0){angle_shape_selected=1.0;}
affect_angle_to_shapes(angle_shape_selected);
break;
case 2://symbols
angle_projo_selectionne=((float)midi_levels[control])/127;
if(angle_projo_selectionne<0.0){angle_projo_selectionne=0.0;}
if (angle_projo_selectionne>1.0){angle_projo_selectionne=1.0;}
affect_angle_to_symbols(view_plot_calc_number_is,angle_projo_selectionne);
break;
default:
break;
}
}

else if(control==1602)//DUB
{
switch(index_menus_lighting_plot)
{
case 1://shapes
duplicate_selected_shapes();
break;
case 2://symbols
duplicate_selected_symbols(view_plot_calc_number_is);
break;
default:
break;
}
}

else if(control==1603)//DELETE
{
switch(index_menus_lighting_plot)
{
case 1://shapes
delete_selected_shapes();
break;
case 2://symbols
delete_selected_symbols(view_plot_calc_number_is);
break;
default:
break;
}
}

else if(control==1604)//UNSELECT OU SEND TO
{
switch(index_menus_lighting_plot)
{
case 1://shapes
unselect_all_shapes();
break;
case 2://symbols
index_plot_send_to_mode=toggle(index_plot_send_to_mode);
break;
default:
break;
}
}

//les layers
else if(control>=1605 && control<=1608)
{
int calc=control-1605;
if(index_main_clear==0 && index_plot_send_to_mode==0)
{
switch(plot_layer_mode)
{
case 0:
show_calc_number[calc]=toggle(show_calc_number[calc]);
break;
case 1:
for(int j=0;j<4;j++)
{
show_calc_number[j]=0;
}
show_calc_number[calc]=1;
view_plot_calc_number_is=calc;
mouse_released=1;
break;
default: break;
}
plot_generate_appareils_list();
}
else if(index_main_clear==1 && index_plot_send_to_mode==0)
{
plot_layer_selected=calc;
index_ask_delete_symbols_on_calc=1;
index_ask_confirm=1;
}
else if(index_main_clear==0 && index_plot_send_to_mode==1)
{
plot_layer_selected=calc;
send_symbols_from_calc_to_calc(view_plot_calc_number_is,plot_layer_selected)     ;
index_plot_send_to_mode=0;
plot_layer_selected=0;
plot_generate_appareils_list();
}
}

else if(control==1609)//toggle Layer mode
{
plot_layer_mode=toggle(plot_layer_mode);
}

else if(control>=1610 && control<=1614)//les relatifs en édition
{
int rx=control-1610;
switch(mode_relatif_xy_solo)
{
case 0:
adjust_xy_type[rx]=toggle(adjust_xy_type[rx]);
break;
case 1:
for(int j=0;j<5;j++)
{adjust_xy_type[j]=0;}
adjust_xy_type[rx]=1;
break;
}
}

if(control>=1615 && control<=1622)//preset reatifs xy
{
xyrelativ_preset=control-1615;
if(index_main_clear==0)
{
if(index_do_dock==0 )
{affect_preset_xy_to_symbols(xyrelativ_preset);}
else if(index_do_dock==1 )
{
record_preset_xy_from_symbol(xyrelativ_preset);
reset_symbols_selected(view_plot_calc_number_is);
index_do_dock=0;
}
}
else
{
index_ask_clear_preset_relativ=1;
index_ask_confirm=1;
}
plot_light_preset_on_click[xyrelativ_preset]=1.0;
last_xyrelativ_preset=xyrelativ_preset;
xyrelativ_preset=999;
}

}//fin plot

//channels handling

 if(control==1624)//poignee
 {
   scroll_channelspace=midi_levels[control]*2;
 }


if(control==1625)//midi affect
{
Midi_Faders_Affectation_Type++;//0 pas d affectation / 1 solo / 2 x8
if(Midi_Faders_Affectation_Type>2){Midi_Faders_Affectation_Type=0;}
}

if(control==1626)//main menu call
{
index_show_main_menu=toggle(index_show_main_menu);
if( index_show_main_menu==1){add_a_window(W_MAINMENU);}
else {substract_a_window(W_MAINMENU);}
}

if(control==1627)//UP DOWN FADER SPACE
{
YFader=(hauteur_ecran/127)*(127-midi_levels[control]) ;
}

if(control>=1628 && control<= 1643)
{
if(ClassicalChannelView==1)
{ClassicalChannelView=0;if(Channel_View_MODE[control-1628]==0){Channel_View_MODE[control-1628]=1;}}
else
{
Channel_View_MODE[control-1628]=toggle(Channel_View_MODE[control-1628]);
ClassicalChannelView=0;
}
}

if(control==1644)//Classical View
{
ClassicalChannelView=toggle(ClassicalChannelView);
}

if(control==1645)//Sequenciel GOTO
{
int index_atoi=0;
if(numeric_postext>0)
{
index_atoi=(int)(atof(numeric)*10);
if(MemoiresExistantes[index_atoi]==1)
{
position_preset=index_atoi;
refresh_mem_onpreset(position_preset);
reset_numeric_entry();
numeric_postext=0;
}
}
}


//draw
if(control>=1646 && control<=1651)//preset choice
{
draw_preset_selected=control-1646;
recalculate_draw_sizes(draw_preset_selected);
}
if(control==1652)//draw mode
{
draw_mode[draw_preset_selected]++;
if(draw_mode[draw_preset_selected]>3){draw_mode[draw_preset_selected]=0;}
}
if(control==1653)//pressure
{
draw_level_to_do[draw_preset_selected]=((float)(midi_levels[control])/127);
}
if(control==1654)//damper decay factor
{
previous_draw_damper_decay_factor[draw_preset_selected]=draw_damper_decay_factor[draw_preset_selected];
draw_damper_decay_factor[draw_preset_selected]=((float)(midi_levels[control])/127);
}

if(control==1655)//ghost
{
previous_draw_ghost_to_do[draw_preset_selected]=draw_ghost_to_do[draw_preset_selected];
draw_ghost_to_do[draw_preset_selected]=((float)(midi_levels[control])/127);
}

//1656 désaffecté


if(control==1657)//erase drawing
{
draw_erase_drawing(draw_preset_selected);
}

if(control==1658)//brush type
{
draw_brush_type[draw_preset_selected]=toggle(draw_brush_type[draw_preset_selected]);
switch(draw_brush_type[draw_preset_selected])
{
case 0:
sprintf(string_Last_Order,"DOT brush selected");
break;
case 1:
sprintf(string_Last_Order,"GridPlayer selected");
break;
default:
break;
}
}


if(control==1659)//commande fenetre draw
{
index_draw_window=toggle(index_draw_window);
if(index_draw_window==1){add_a_window(W_DRAW);substract_a_window(W_MAINMENU);}
else {substract_a_window(W_DRAW);}
}

if(control==1660)//draw midi x
{
int pr=draw_preset_selected;
draw_centre_x[pr]=(int) ( ((float)midi_levels[control]/127) *(draw_preset_parameters[pr][0]-1));
draw_centre_y[pr]=(int) ( ((float)(127-midi_levels[1661])/127) *(draw_preset_parameters[pr][1]-1));
index_case[pr]=(draw_centre_x[pr]) + (draw_centre_y[pr]*draw_preset_parameters[pr][0]) ;
draw_point_is_traced[pr]=1;
}

if(control==1661)//draw midi y
{
int pr=draw_preset_selected;
draw_centre_x[pr]=(int) ( ((float)midi_levels[1660]/127) *(draw_preset_parameters[pr][0]-1));
draw_centre_y[pr]=(int) ( ((float)(127-midi_levels[control])/127) *(draw_preset_parameters[pr][1]-1));
index_case[pr]=(draw_centre_x[pr]) + (draw_centre_y[pr]*draw_preset_parameters[pr][0]) ;
draw_point_is_traced[pr]=1;
}

//ECHO////////////////////////////////////////////////////////
if(control==1662)//commande fenetre echo
{
index_show_echo_window=toggle(index_show_echo_window);
if(index_show_echo_window==1){add_a_window(W_ECHO);}
else {substract_a_window(W_ECHO);}
}

if(control>=1663 && control<=1685)//les echos presets
{
int index_ec=control-1663;
if(index_main_clear==1)
{
if(index_enable_edit_echo==1)
{
index_selected_echo_for_manipulation=index_ec;
index_ask_clear_echo_preset=1;
index_ask_confirm=1;             //clear_echo_preset(index_selected_echo_for_manipulation);
}
}
else
{
echo_selected=index_ec;
}
}

if(control>=1686 && control<=1690)//les 4 actions de bounce etc
{
switch(control-1686)
{
case 0:
     echo_is_echo_mode[echo_selected]=toggle(echo_is_echo_mode[echo_selected]);
break;
case 1:
     snap_fader_state(echo_selected,echo_pointing_fader_num[echo_selected]-1);
break;
case 2:
     bounce(echo_selected);
break;
case 3:
     snap_kill_and_bounce(echo_selected,echo_pointing_fader_num[echo_selected]-1);
break;
case 4:
     recall_fader_state_echo(echo_pointing_fader_num[echo_selected]-1);
break;
default:
break;
}
}



if(control==1691)//prev chan
{
if(echo_grid_channel_position[echo_selected]>0)
{
echo_grid_channel_position[echo_selected]--;
}
}
if(control==1692)//next chan
{
if(echo_grid_channel_position[echo_selected]<(511-14))
{
echo_grid_channel_position[echo_selected]++;
}
}

//les 3 sliders de paramètre de Echo: Gravity Mass et Energy
if(control>=1693 && control<= 1695)
{
 echo_global_params[echo_selected][control-1693]= (float)(midi_levels[control])/127;
}

if(control==1696)//mode level ou ground pour l édition de channel
{
if(index_main_clear==1 && index_enable_edit_echo==1)
{
switch(echo_channel_manipulate_mode[echo_selected])
{
 case 0://levels
 clear_echo_levels(echo_selected);
 break;
 case 1:
 clear_ground_levels(echo_selected);
 break;
 default: break;
}
index_main_clear=0;
}
else
{
echo_channel_manipulate_mode[echo_selected]=toggle(echo_channel_manipulate_mode[echo_selected]);
}
}

//rajout audioplayers autopause autoload et next previous track
if(control>=1800 && control<=1824)
{
if(control>=1800 && control<=1804)//autoload
{
int lect=control-1800;
audio_autoload[lect]=toggle(audio_autoload[lect]);
}
if(control>=1805 && control<=1808)//autostop
{
int lect=control-1805;
audio_autopause[lect]=toggle(audio_autopause[lect]);
}

if(control>=1809 && control<=1812  )//load file
{
int lect=control-1809;
audiofile_selected=(int)midi_levels[control];
if( audiofile_selected>0  && audiofile_selected<127 )
{

sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(lect);
}
}
}

if(control>=1813 && control<=1816)//prev track
{
int lect=control-1813;
if(player_ignited[lect]==1 && index_loading_a_sound_file==0)
{
/*midi_levels[control]=0;
control=-1;
index_loading_a_sound_file=1;
audiofile_selected=player_has_file_coming_from_pos[lect]-1;
player_has_file_coming_from_pos[lect]=audiofile_selected;
if(audiofile_selected<1){audiofile_selected=1;}
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(lect);
}
*/
//christoph 22/04/14 debugging midi next prev function by outputting it inside the 1/10th second loop
midi_levels[control]=0;
control=-1;
audio_do_load_midi_prev_file[lect]=1;
}
}

if(control>=1817 && control<=1820)//next track
{
int lect=control-1817;
if(player_ignited[lect]==1 && index_loading_a_sound_file==0)
{
/*midi_levels[control]=0;
control=-1;
index_loading_a_sound_file=1;
audiofile_selected=player_has_file_coming_from_pos[lect]+1;
player_has_file_coming_from_pos[lect]=audiofile_selected;
if(audiofile_selected>=audio_number_total_in_folder){audiofile_selected=audio_number_total_in_folder;}
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0 )
{
AffectSoundFile(lect);
}
*/
//christoph 22/04/14 debugging midi next prev function by outputting it inside the 1/10th second loop
midi_levels[control]=0;
control=-1;
audio_do_load_midi_next_file[lect]=1;
}
}
//seek to end
if(control>=1821 && control<=1824)
{
int lect=control-1821;
if(player_ignited[lect]==1 && index_loading_a_sound_file==0)
{
switch(lect)
{
case 0://PLAYER 1
player1->setPosition(length_of_file_in_player[lect]-1000);
break;
case 1://PLAYER 2
 player2->setPosition(length_of_file_in_player[lect]-1000);
break;
case 2://PLAYER 3
 player3->setPosition(length_of_file_in_player[lect]-1000);
break;
case 3://PLAYER 4
 player4->setPosition(length_of_file_in_player[lect]-1000);
break;
default:
break;
}
}
}
}
//Christoph Touch OSC remote control
if(control == 1825 )//check minus
{
     index_false_control= 1;
     index_false_shift=0;
     simulate_keypress(KEY_LEFT<<8);
}
if( control == 1826 )//check plus
{
     index_false_control= 1;
     index_false_shift=0;
     simulate_keypress(KEY_RIGHT<<8);
}
if(control == 1827 )//at full
{
simulate_keypress(KEY_I<<8);index_false_shift=0;index_false_control=0;
}
if(control == 1828 )//at zero
{
simulate_keypress(KEY_O<<8);index_false_shift=0;index_false_control=0;
sprintf(string_Last_Order,"Midi simulate FULL");
}

if(control == 1829 )//window WAVE
{
if(index_wave_menu_window==0){add_a_window(W_WAVE);}
else {substract_a_window(W_WAVE);}
rest(midi_keyboard_wait);
}

if(control>=1830 && control<=1830+63)//arduino analogic on/off
{
int d=control-1830;
ventilate_analog_data[d]=toggle(ventilate_analog_data[d]);
}



//MIDI CLOCK
if(control ==1894)
{
do_clock_level_modification(midi_levels[1894]);

   angle_snap_clock=(((PIknob*2)+angle_correction_wheel) / 128)*midi_levels[1894];
   clock_vx = cos(angle_snap_clock)* rayon_wheel_level;
   clock_vy = sin(angle_snap_clock)* rayon_wheel_level;
   position_curseur_clock_x= window_cfgX+770+clock_vx;
   position_curseur_clock_y=window_cfgY+115+clock_vy ;

}

if(control>=1895 && control <=1911)
{
 //   direct midi clock load
     int cl=control-1895;

     if(bpm_personnal[cl]>0)
     {
         midi_BPM=bpm_personnal[cl];
         ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
         install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);
     }
}

//////DAMPER FADERS /////////////////////////////////////////////////////////

//DAMPER FADER ON OFF 1912
if(control>=1912 && control <=1959)
{
if(fader_damper_is_on[control-1912]==0)
    {
        Fader_dampered[control-1912].fix_all_damper_state_value(Fader[control-1912]);
        Fader_dampered[control-1912].set_target_val(Fader[control-1912]);
    }
    fader_damper_is_on[control-1912]=toggle(fader_damper_is_on[control-1912]);
    if(fader_damper_is_on[control-1912]==1){index_fader_is_manipulated[control-1912]=1;}
}

//DAMPER FADER LEVEL DECAY 1960
if(control>=1960 && control <=2007)
{
    Fader_dampered[control-1960].set_damper_decay((((float)midi_levels[control])/127));
}
//DAMPER FADER MODE 2008
if(control>=2008 && control <=2055)
{
    Fader_dampered[control-2008].set_damper_mode((Fader_dampered[control-2008].getdampermode()+1));
}

//DAMPER DT LEVEL 2056
if(control>=2056 && control <=2113)
{
    Fader_dampered[control-2056].set_damper_dt((((float)midi_levels[control])/127)/10);
}

//WAVE
if(control==2114) //level damper decay wave
{
float u=1.0-((float)(midi_levels[control])/127);
    for(int i=0;i<26;i++)
    {
     Wave_Dampered[i].set_damper_decay(u);
    }
}

if(control==2115) //level damper delta wave
{
float u=(1.0-(((float)midi_levels[control])/127))/10;
    for(int i=0;i<26;i++)
    {
     Wave_Dampered[i].set_damper_dt(u);
    }
}

if(control==2116) //mode damper delta wave bouton
{
    Wave_Dampered[0].set_damper_mode(Wave_Dampered[0].getdampermode()+1);
    int u=Wave_Dampered[0].getdampermode();
    for(int i=1;i<26;i++)
    {
    Wave_Dampered[i].set_damper_mode(u);
    }
}

if(control==2117) //slider du wave wavecontroller
{
        waver_control=((float)midi_levels[control]*2)/10 ;
        waver_control=constrain_int_data_to_this_range(waver_control, 0,26);
        wave_calculations();

}

return(0);
}

int ventilate_midi_to_midiarray()
{
//bool midi_signal_received_is_assigned=0;
for(int i=0;i<3072;i++)//3072 controls midi possible
{
if(midi_needs_no_key_on_key_off[i]==0)//TOUCHE FLASH ne fonctionne que si Key ON
{
if(miditable[0][i]==istyp &&
miditable[1][i]==ischan && miditable[2][i]==ispitch && ischan!=999 && istyp!=999 && ispitch!=999 )
         {
         val_raccrochage_midi[i]=isvel;
         if(index_midi_auto_demute==1 && is_raccrochage_midi_remote[i]==1 && val_raccrochage_midi[i]==midi_levels[i])
         {is_raccrochage_midi_remote[i]=0;}
         if((is_raccrochage_midi_remote[i]==0 )||(( miditable[0][1277]==istyp) && (miditable[1][1277]==ischan) && (miditable[2][1277]==ispitch)))
         {
         midi_levels[i]=isvel;
         do_midi_job(i);
         }
        // midi_signal_received_is_assigned=1;
         }
}
else
{
    if(miditable[1][i]==ischan && miditable[2][i]==ispitch
    && ischan!=999 && istyp!=999 && ispitch!=999
    )//enlevé le typ pour simplifier les histoires de flash
    {
     val_raccrochage_midi[i]=isvel;
     if((is_raccrochage_midi_remote[i]==0) || ((miditable[0][1277]==istyp) && (miditable[1][1277]==ischan) && (miditable[2][1277]==ispitch)))
     {
     midi_levels[i]=isvel;
     do_midi_job(i);
     }
     //midi_signal_received_is_assigned=1;
     }
}



}

//MIDI THRUTH
if(index_midi_global_thruth==1)
    {
    send_immidiateley_my_midi_cc(istyp,ischan,ispitch,isvel);
    }
return(0);
}

int ventilation_midi_sur_crossfade()
{
if(index_get_back_faders_need_to_be_done==0)
{
midi_levels[491]=niveauX1/2;
midi_levels[492]=127-(niveauX2/2);
midi_levels[493]=crossfade_speed;
}
 return(0);
}

int simulate_midi(int letype,int lechan, int lepitch, int lavaleur)
{
istyp=letype;
ischan=lechan;
ispitch=lepitch;
isvel=lavaleur;
ventilate_midi_to_midiarray();
return(0);
}


int add_to_midi_historic()//just a visual monitoring
{

if( position_midi_historic>254)
    {
        position_midi_historic=0;
        for(int i=0;i<255;i++)
        {
        sprintf(midi_historic[i]," ");
        midi_historic_data[i][0]=999;
        midi_historic_data[i][1]=999;
        midi_historic_data[i][2]=999;
        midi_historic_data[i][3]=999;
        }
    }
else{position_midi_historic++;}

midi_historic_data[position_midi_historic][0]=istyp;
midi_historic_data[position_midi_historic][1]=ischan;
midi_historic_data[position_midi_historic][2]=ispitch;
midi_historic_data[position_midi_historic][3]=isvel;
sprintf(midi_historic[position_midi_historic],my_midi_string);
return(0);
}


/* ------------------------------------------------------------------------- */
static char * EvAquire ( MidiEvPtr e)
{

	istyp=(int)EvType(e);
    ischan=(int)Chan(e);
    ispitch=(int)Pitch(e);
    isvel=(int)Vel(e);

 //moniteur mis à jour
    sprintf(typ,TblLibEv[istyp]);
    sprintf (my_midi_original_string, "Raw: Chan:%-2d Pitch:%-2d Vel:%-2d Typ: %s",	ischan,ispitch,isvel, typ);

    //christoph 12/05/15 pour midi twister
    if(cheat_key_off_to_key_on==1 && istyp==2)//key off
    {   istyp=1;
        isvel=0;//écrasement de la vélocité du key off
    }

    //trichage key on vel 0 at key off
    if(cheat_key_off==1 && (istyp==0 || istyp==1) && isvel==0 )//eviter le flash key off
    {
    istyp=2;
    }
    //affinage midi cheat change signal
    switch(midi_change_vel_type[ischan][ispitch])
    {
    case 0:
    break;
    case 1://inversion 0-127>127-0
    tempvel=isvel;
    isvel=127-tempvel;
    break;
    case 2://toggle
    if(isvel>0)
    {
    midi_recognize_on_off[ischan][ispitch]=toggle(midi_recognize_on_off[ischan][ispitch]);
    }
    isvel=127*midi_recognize_on_off[ischan][ispitch];
    break;
    case 3://midi key on vel 0= midi key off
    if((istyp==0 || istyp==1) && isvel==0 )//eviter le flash key off
    {
    istyp=2;
    }
    break;
    case 4://midi key off = midi key on vel 0
    if(istyp==2)  //eviter le flash key off
    {
    istyp=1; isvel=0;
    }
    break;
    case 5://pad to triggers
    if(isvel>0 && isvel<127){isvel=127;}
    break;
    case 6://CC 0 devient Koff pour touch osc
    if(isvel==0){istyp=2;}
    break;
    default:
     break;
    }

    add_to_midi_historic();
    //moniteur mis à jour
    sprintf(typ,TblLibEv[istyp]);
    sprintf (my_midi_string, "%s Ch:%-2d P:%-2d Vel:%-2d ",typ,ischan,ispitch,isvel);

    ventilate_midi_to_midiarray();



    return (0);
}

/* ------------------------------------------------------------------------- */
pascal void Display ( MidiEvPtr e)
{

	//sab 02/03/2014 unused var char s[120];

	if (e) {
		EvAquire (e);

		MidiFreeEv(e);
	}
}


/* ------------------------------------------------------------------------- */
pascal void DisplayTask (short ref)
{

	long n;

	n= MidiCountEvs(ref);
	while (n > 16) {
		MidiFreeEv (MidiGetEv (ref));
		n--;
	}
	while (n--) {
		Display (MidiGetEv (ref));
	}
}

pascal void MSALARMAPI ReceivePolling ( long date, short r, long a, long b, long c)
{

	long n;

	n= MidiCountEvs (r);

	if (n) {
		DisplayTask(r);
		MidiTask (ReceivePolling, date+100, r, a, 0, 0);
	}
	else MidiSetRcvAlarm (r, ReceiveEvents);
}


/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
pascal void MSALARMAPI ReceiveEvents(short r)
{
//nvelle version
	MidiEvPtr ev;
	while ( (ev=MidiGetEv(r)) ){Display(ev);}

}






int PrintSlotsInfosDevices(short driverRef)
{
    TDriverInfos dInfos; TSlotInfos sInfos;

    compt_midi_in=0;
    compt_midi_out=0;//compteurs pour affichages

    compt_first_device_out=0;
    compt_first_device_inout=0;

    if (MidiGetDriverInfos (driverRef, &dInfos))
    {
      short     i;
      SlotRefNum slotRef;

        char temp_device_name[64];
        sprintf(string_nbre_de_devices,"Founded: %d",dInfos.slots);

        for( i = 1; i <= dInfos.slots; i++ )
        {
            slotRef = MidiGetIndSlot(driverRef, i);


            if (MidiGetSlotInfos (slotRef, &sInfos))
            {

            if(sInfos.direction== MidiInputSlot)
            {
            //ok pour avoir l info de connecté ou pas
           if(!MidiIsSlotConnected (0,slotRef )){midi_in_is_connected[i]=0;}
           else{midi_in_is_connected[i]=1;}

           compt_midi_in++;//permet après de definir la position des out

                sprintf(temp_device_name,"%s", sInfos.name);
                strncpy (tableau_peripheriques_in[i],temp_device_name,32);
                tableau_peripheriques_indexs_in[i]=1;//acces au num de slot

                if(do_connect_in[compt_midi_in]==1)
                {
                if(midi_in_is_connected[i]==0)
                {
			    MidiConnectSlot(0,slotRef,1);
                do_connect_in[i]=0;
                }
                else {
			    MidiConnectSlot(0,slotRef,0);
                do_connect_in[i]=0;
                }
                }
            }
             //OUT PUT MIDI LIST
             if(sInfos.direction== MidiOutputSlot)
            {
                 if(!MidiIsSlotConnected (0,slotRef )){midi_out_is_connected[i]=0;}
                 else{midi_out_is_connected[i]=1;}

                compt_midi_out++;

                sprintf(temp_device_name,"%s", sInfos.name);

                strncpy (tableau_peripheriques_out[compt_midi_out],temp_device_name,32);
                tableau_peripheriques_indexs_out[i]=1;//acces au num de slot

                if( compt_first_device_out==0){compt_first_device_out=i;}

                if(do_connect_out[i]==1)
                {
			    if(midi_out_is_connected[i]==0)
			    {
                MidiConnectSlot(0,slotRef,1);//ok connecter
                }
                else
                {
			    MidiConnectSlot(0,slotRef,0);//ok deconnecter
                }
                do_connect_out[i]=0;
                }
              }

            }
        }
    }

return(0);
}




//////////BOITE CHANGEMENT SIGNAUX///////////////////////////////////////////////

int midi_change_signal(int xrep, int yrep)
{

petitchiffre.Print("Change Reaction :",xrep, yrep-15);

sprintf(string_midichan,"Midi Ch: %d",change_vel_midichan_selected);

Rect ChangeCh(Vec2D(xrep+110,yrep-30),Vec2D(80,20));
ChangeCh.SetRoundness(5);
if(mouse_x>xrep+110 && mouse_x<xrep+110+80 && mouse_y>yrep-30 && mouse_y<yrep-30+20)
{
ChangeCh.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
ChangeCh.Draw(CouleurFader);
change_vel_midichan_selected++;
if(change_vel_midichan_selected>15){change_vel_midichan_selected=0;}
mouse_released=1;
}
}
petitchiffre.Print(string_midichan,xrep+120,yrep-17);
ChangeCh.DrawOutline(CouleurLigne);



Rect BackDeroule(Vec2D(xrep,yrep),Vec2D(190,210));
BackDeroule.SetRoundness(15);
BackDeroule.Draw(CouleurFond.WithAlpha(0.3));

for (int y=0;y<10;y++)
{
Rect OverMidi(Vec2D(xrep+5,(yrep+10+(y*20)-10)),Vec2D(140,15));
OverMidi.SetRoundness(7.5);

if(mouse_x>xrep+5 && mouse_x<xrep+5+110 && mouse_y>(yrep+10+(y*20)-10) && mouse_y<(yrep+10+(y*20)+5))
{
OverMidi.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0)
{
midi_change_vel_type[change_vel_midichan_selected][line_midi_changesignal+y]++;
if(midi_change_vel_type[change_vel_midichan_selected][line_midi_changesignal+y]>6)
  {midi_change_vel_type[change_vel_midichan_selected][line_midi_changesignal+y]=0;}
mouse_released=1;
}
}
if(y+line_midi_changesignal<=127)
{

switch(midi_change_vel_type[change_vel_midichan_selected][line_midi_changesignal+y])
{
case 0:
petitpetitchiffre.Print("Normal 0-127",xrep+30,yrep+10+(y*20));
break;
case 1:
OverMidi.Draw(CouleurLock);
petitpetitchiffre.Print("Inversed 127-0",xrep+30,yrep+10+(y*20));
break;
case 2:
OverMidi.Draw(CouleurSurvol);
petitpetitchiffre.Print("Toggle mode",xrep+30,yrep+10+(y*20));
break;
case 3:
OverMidi.Draw(CouleurYellow);
petitpetitchiffre.Print("KOn Vel0 =KOff",xrep+30,yrep+10+(y*20));
break;
case 4:
OverMidi.Draw(CouleurSelection);
petitpetitchiffre.Print("KOff =KOn Vel0",xrep+30,yrep+10+(y*20));
break;
case 5:
OverMidi.Draw(CouleurBleuProcedure);
petitpetitchiffre.Print("Pad To Trigger",xrep+30,yrep+10+(y*20));
break;
case 6:
OverMidi.Draw(CouleurBleuProcedure);
petitpetitchiffre.Print("CC Vel0 =Koff",xrep+30,yrep+10+(y*20));
break;
default:
break;
}
petitpetitchiffre.Print(ol::ToString(line_midi_changesignal+y),xrep+10,yrep+10+(y*20));
}
}

//////////////////UP DOWN LINE save/////////////////////
Circle LineUp(Vec2D(xrep+170,yrep+25),12);
LineUp.Draw(CouleurFond);
Circle LineDown(Vec2D(xrep+170,yrep+185),12);
LineDown.Draw(CouleurFond);
if(mouse_x>xrep+170-12 && mouse_x<xrep+170+12)
{
if(mouse_y>yrep+25-12 && mouse_y<yrep+25+12)
{
LineUp.Draw(CouleurSurvol);
if(mouse_button==1)
{
LineUp.Draw(CouleurFader);
if(line_midi_changesignal>0){line_midi_changesignal--;}
}
}
else if(mouse_y>yrep+185-12 && mouse_y<yrep+185+12)
{
LineDown.Draw(CouleurSurvol);
if(mouse_button==1)
{
LineDown.Draw(CouleurFader);
if(line_midi_changesignal<127){line_midi_changesignal++;}
else (line_midi_changesignal=127);
}
}
}
petitchiffre.Print("-",xrep+166,yrep+30);
petitchiffre.Print("+",xrep+166,yrep+190);
LineUp.DrawOutline(CouleurLigne);
LineDown.DrawOutline(CouleurLigne);



return(0);
}


int midi_list_and_choose_devices()
{
    TDriverInfos infos;
    short ref, i, n = MidiCountDrivers();

     for( i = 1; i <= n; i++ )
     {
        ref = MidiGetIndDriver(i);
        if (MidiGetDriverInfos (ref, &infos )&& infos.slots>0)
            {
            PrintSlotsInfosDevices(ref);
            }
     }
return(0);
}


int midi_historic_part(int _x,int _y)
{
Rect BackV(Vec2D(_x-30,_y),Vec2D(275,275));
BackV.SetRoundness(7.5);
BackV.Draw(CouleurFond.WithAlpha(0.5));
//last signal
petitchiffrerouge.Print(">>", _x-25,_y+20);
petitchiffrerouge.Print(midi_historic[position_midi_historic], _x,_y+20);
for(int i=1;i<24;i++)
{
if(position_midi_historic-i>0)
{


  if(window_focus_id==W_CFGMENU && mouse_x>_x-25 && mouse_x<_x-25+200 && mouse_y>_y+20+(10*i) && mouse_y<_y+30+(10*i))
    {
    Rect OverHist(Vec2D(_x-25,_y+20+(10*i)),Vec2D(200,10));
    OverHist.Draw(CouleurBlind);
        if(mouse_button==1 && mouse_released==0)
        {
            istyp=midi_historic_data[position_midi_historic-i][0];
            ischan=midi_historic_data[position_midi_historic-i][1];
            ispitch=midi_historic_data[position_midi_historic-i][2];
            sprintf(typ,TblLibEv[istyp]);
            sprintf (my_midi_string, "%s Ch:%-2d P:%-2d Vel:%-2d ",typ,ischan,ispitch,isvel);

            mouse_released=1;
        }
    }

  petitchiffre.Print(ol::ToString(position_midi_historic-i), _x-25,_y+30+(10*i));
  petitchiffre.Print(midi_historic[position_midi_historic-i], _x,_y+30+(10*i));
}
}

//////////////////UP DOWN LINE IMPORT/////////////////////
Circle LineUp(Vec2D(_x+220,_y+100),12);
LineUp.Draw(CouleurFond);
Circle LineDown(Vec2D(_x+220,_y+210),12);
LineDown.Draw(CouleurFond);
if(window_focus_id==W_CFGMENU && mouse_x>_x+208 && mouse_x<_x+232)
{
if(mouse_y>_y+88 && mouse_y<_y+112)
{
LineUp.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
if(position_midi_historic<255){position_midi_historic++;}
mouse_released=1;
}
}
else if(mouse_y>_y+198 && mouse_y<_y+222)
{
LineDown.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0)
{
if(position_midi_historic>0){position_midi_historic--;}
mouse_released=1;
}
}
}
petitchiffre.Print("+",_x+216,_y+105);
petitchiffre.Print("-",_x+216,_y+215);
LineUp.DrawOutline(CouleurLigne);
LineDown.DrawOutline(CouleurLigne);

return(0);
}

int midipage_affectation(int cfg_midiX,int cfg_midiY, int largeurCFGmidi,int hauteurCFGmidi)
{


/////////////////////////////////////////////////////////////////////////
///////////MANUAL INPUT

  Rect MidiChBox( Vec2D(cfg_midiX+80,cfg_midiY+150), Vec2D ( 70,30));
  MidiChBox.SetRoundness(7.5);
  MidiChBox.SetLineWidth(epaisseur_ligne_fader);
  MidiChBox.Draw(CouleurFond.WithAlpha(0.7));


  Rect MidiPitchBox( Vec2D(cfg_midiX+160,cfg_midiY+150), Vec2D ( 100,30));
  MidiPitchBox.SetRoundness(7.5);
  MidiPitchBox.SetLineWidth(epaisseur_ligne_fader);
  MidiPitchBox.Draw(CouleurFond.WithAlpha(0.7));

  Rect MidiTypeBox( Vec2D(cfg_midiX+160,cfg_midiY+190), Vec2D ( 100,30));
  MidiTypeBox.SetRoundness(7.5);
  MidiTypeBox.SetLineWidth(epaisseur_ligne_fader);
  MidiTypeBox.Draw(CouleurFond.WithAlpha(0.7));
//set fake midi chan
if(mouse_x> cfg_midiX+80 && mouse_x< cfg_midiX+150 && mouse_y> cfg_midiY+150 && mouse_y<cfg_midiY+150+30  && window_focus_id==920)
{
MidiChBox.DrawOutline(CouleurLigne);
if(mouse_button==1 &&  mouse_released==0 )
{
MidiChBox.Draw(CouleurFader);
fakemidichan=atol(numeric);
if(fakemidichan>15 || fakemidichan<0)
{
fakemidichan=0;
sprintf(string_Last_Order,"A midi channel is from 0 to 15");
}
numeric_postext=0;
reset_numeric_entry();
mouse_released=1;
}
}
//set fake midi picth
 if(mouse_x> cfg_midiX+160 && mouse_x< cfg_midiX+260 && mouse_y> cfg_midiY+150 && mouse_y<cfg_midiY+180  && window_focus_id==920)
{
MidiPitchBox.DrawOutline(CouleurLigne);
if(mouse_button==1 &&  mouse_released==0 )
{
MidiPitchBox.Draw(CouleurFader);
fakemidipitch=atol(numeric);
if(fakemidipitch>127 || fakemidipitch<0)
{
fakemidipitch=1;
sprintf(string_Last_Order,"A midi pitch is from 0 to 127");
}
numeric_postext=0;
reset_numeric_entry();
}
mouse_released=1;
}
//Fake miditype
if(mouse_x> cfg_midiX+160 && mouse_x< cfg_midiX+260 && mouse_y> cfg_midiY+190 && mouse_y<cfg_midiY+190+30  && window_focus_id==920)
{
MidiTypeBox.DrawOutline(CouleurLigne);
if(mouse_button==1 &&  mouse_released==0 )
{
MidiTypeBox.Draw(CouleurFader);
if(fakemiditype==1){fakemiditype=2;}
else if(fakemiditype==2){fakemiditype=4;}
else if(fakemiditype==4){fakemiditype=1;}
mouse_released=1;
}
}

petitchiffre.Print("CH:",cfg_midiX+90,cfg_midiY+170);
petitchiffre.Print(ol::ToString(fakemidichan),cfg_midiX+115,cfg_midiY+170);
petitchiffre.Print("PITCH:",cfg_midiX+170,cfg_midiY+170);
petitchiffre.Print(ol::ToString(fakemidipitch),cfg_midiX+230,cfg_midiY+170);
petitchiffre.Print("TYPE:",cfg_midiX+90,cfg_midiY+210);
if(fakemiditype==1){petitchiffre.Print("Key On",cfg_midiX+175,cfg_midiY+210);}
else if(fakemiditype==2){petitchiffre.Print("Key Off",cfg_midiX+175,cfg_midiY+210);}
else if(fakemiditype==4){petitchiffre.Print("Ctrl Change",cfg_midiX+175,cfg_midiY+210);}




//MODES: 0 affectation normale 1 Reset 2 your input
for (int i=1;i<4;i++)
{
     Rect MidiModeBox( Vec2D(cfg_midiX+10,cfg_midiY+50+(i*25)), Vec2D ( 60,15));
     MidiModeBox.SetRoundness(7.5);
     MidiModeBox.SetLineWidth(epaisseur_ligne_fader);
     MidiModeBox.Draw(CouleurFond.WithAlpha(0.5));

switch(i)
    {
    case 1://autoclose affectation
    petitchiffre.Print("Midi Affectation Auto-Close (recommanded)",cfg_midiX+90,cfg_midiY+60+(i*25));
    MidiModeBox.Draw(CouleurFader.WithAlpha(index_midi_affectation_autoclose));
    if(mouse_x>cfg_midiX+10 && mouse_x<cfg_midiX+70 && mouse_y>cfg_midiY+50+(i*25) && mouse_y<cfg_midiY+50+(i*25)+15  && window_focus_id==920)
    {
    if(mouse_button==1 &&  mouse_released==0 )
    {
    index_midi_affectation_autoclose=toggle(index_midi_affectation_autoclose);
    mouse_released=1;
    }
    }
    break;
    case 2://clear mode
    petitchiffre.Print("Clear !",cfg_midiX+90,cfg_midiY+60+(i*25));
    if(Midi_Faders_Affectation_Mode==1){MidiModeBox.Draw(CouleurFader);}
    if(mouse_x>cfg_midiX+10 && mouse_x<cfg_midiX+70 && mouse_y>cfg_midiY+50+(i*25) && mouse_y<cfg_midiY+50+(i*25)+15  && window_focus_id==920)
    {
    if(mouse_button==1 &&  mouse_released==0 )
    {
    if(Midi_Faders_Affectation_Mode!=0 ){Midi_Faders_Affectation_Mode=0;}
    else {Midi_Faders_Affectation_Mode=1;}
    mouse_released=1;
    }
    }
    break;
    case 3://midi cheat
    petitchiffre.Print("Fake Midi Input:",cfg_midiX+90,cfg_midiY+60+(i*25));
    if(Midi_Faders_Affectation_Mode==2){MidiModeBox.Draw(CouleurFader);}
     if(mouse_x>cfg_midiX+10 && mouse_x<cfg_midiX+70 && mouse_y>cfg_midiY+50+(i*25) && mouse_y<cfg_midiY+50+(i*25)+15  && window_focus_id==920)
    {
    if(mouse_button==1 &&  mouse_released==0 )
    {
    if(Midi_Faders_Affectation_Mode==2 ){Midi_Faders_Affectation_Mode=0;}
    else {Midi_Faders_Affectation_Mode=2;}
    mouse_released=1;
    }
    }
    break;
    default:
    break;
    }
/*
if(mouse_x>cfg_midiX+10 && mouse_x<cfg_midiX+70 && mouse_y>cfg_midiY+50+(i*25) && mouse_y<cfg_midiY+50+(i*25)+15  && window_focus_id==920)
{
MidiModeBox.Draw(CouleurFond);
if(mouse_button==1 &&  mouse_released==0 )
{
MidiModeBox.Draw(CouleurSurvol);
if(Midi_Faders_Affectation_Mode==i){Midi_Faders_Affectation_Mode=0;}
else{Midi_Faders_Affectation_Mode=i;}
mouse_released=1;
}
}
if(i==1)
{
petitchiffre.Print("Clear !",cfg_midiX+90,cfg_midiY+60+(i*25));
}
if(i==3)
{
petitchiffre.Print("Fake Midi Input:",cfg_midiX+90,cfg_midiY+60+(i*25));
}

if(Midi_Faders_Affectation_Mode==i)
{
MidiModeBox.Draw(CouleurFader);
}
*/
}


///////////MIDI NUMERIC TOGGLE MODE
Rect MidiTogBox( Vec2D(cfg_midiX+10,cfg_midiY+40), Vec2D ( 60,25));
MidiTogBox.SetRoundness(7.5);
MidiTogBox.SetLineWidth(epaisseur_ligne_fader);
MidiTogBox.Draw(CouleurFond.WithAlpha(0.5));

if(mouse_x>cfg_midiX+10 && mouse_x<cfg_midiX+70 && mouse_y>cfg_midiY+40 && mouse_y<cfg_midiY+40+25  && window_focus_id==920)
{
MidiTogBox.DrawOutline(CouleurFader);
if(mouse_button==1 &&  mouse_released==0 )
{
if(toggle_numerical_midi_way==0){toggle_numerical_midi_way=1;}
else if(toggle_numerical_midi_way==1){toggle_numerical_midi_way=0;}
mouse_released=1;
}
}
if(toggle_numerical_midi_way==1)
{
MidiTogBox.Draw(CouleurSurvol);
petitchiffre.Print("Chan.",cfg_midiX+20,cfg_midiY+55);
}
else if(toggle_numerical_midi_way==0)
{
petitchiffre.Print("Pitch",cfg_midiX+20,cfg_midiY+55);
}

petitchiffre.Print("Numerical Serial Way",cfg_midiX+90,cfg_midiY+55);
//////////////////////////////////////////////////////////////////////////////////

//Midi affect button ID 1625

petitchiffre.Print("MIDI AFFECT Button:",cfg_midiX+20,cfg_midiY+255);

MidiTypeBox.MoveTo(Vec2D(cfg_midiX+160,cfg_midiY+235));
MidiTypeBox.Draw(CouleurFond.WithAlpha(0.7));
switch(miditable[0][1625])
 {
  case 0: petitchiffre.Print("Note",cfg_midiX+170,cfg_midiY+255);break;
  case 1: petitchiffre.Print("Key On",cfg_midiX+170,cfg_midiY+255);break;
  case 2: petitchiffre.Print("Key Off",cfg_midiX+170,cfg_midiY+255);break;
  case 4: petitchiffre.Print("Ctrl Change",cfg_midiX+170,cfg_midiY+255);break;
  default: petitchiffre.Print("-",cfg_midiX+170,cfg_midiY+255);break;
}

MidiChBox.MoveTo(Vec2D(cfg_midiX+290,cfg_midiY+235));
MidiChBox.Draw(CouleurFond.WithAlpha(0.7));
petitchiffre.Print("CH.:",cfg_midiX+300,cfg_midiY+255);
petitchiffre.Print(ol::ToString(miditable[1][1625]),cfg_midiX+330,cfg_midiY+255);

MidiPitchBox.MoveTo(Vec2D(cfg_midiX+380,cfg_midiY+235));
MidiPitchBox.Draw(CouleurFond.WithAlpha(0.7));
petitchiffre.Print("Pitch:",cfg_midiX+390,cfg_midiY+255);
petitchiffre.Print(ol::ToString(miditable[2][1625]),cfg_midiX+430,cfg_midiY+255);

if(window_focus_id==W_CFGMENU && mouse_y>cfg_midiY+235 && mouse_y<cfg_midiY+265 && mouse_button==1 && mouse_released==0)
{
    if(mouse_x>cfg_midiX+160 && mouse_x<cfg_midiX+260)//Type
    {
    MidiTypeBox.DrawOutline(CouleurLigne.WithAlpha(0.5));
    switch(miditable[0][1625])
    {
    case 0: miditable[0][1625]=1;break;
    case 1: miditable[0][1625]=2;break;
    case 2: miditable[0][1625]=4;break;
    case 4: miditable[0][1625]=0;break;
    default: miditable[0][1625]=0;break;
    }
    }
    else if(mouse_x>cfg_midiX+290 && mouse_x<cfg_midiX+350 && numeric_postext>0)//CH
    {
    MidiChBox.DrawOutline(CouleurLigne.WithAlpha(0.5));
    if(atoi(numeric)<16)
    {   miditable[1][1625]=atoi(numeric);reset_numeric_entry();}
    }
    else if(mouse_x>cfg_midiX+380 && mouse_x<cfg_midiX+480 && numeric_postext>0)//PITCH
    {
    MidiPitchBox.DrawOutline(CouleurLigne.WithAlpha(0.5));
    if(atoi(numeric)<128)
    {   miditable[2][1625]=atoi(numeric); reset_numeric_entry();}
    }
    mouse_released=1;
}


petitpetitchiffre.Print(string_last_midi_id,cfg_midiX+250, cfg_midiY+55);//midi in


midi_historic_part(cfg_midiX+575, cfg_midiY+10);//monitoring input
return(0);
}
///////////////////////////////////////////////////////////////////////////////
int refresh_launchpad_color_callibration()
{
lch_orange=launchpad_color[0];//63;
lch_green=launchpad_color[1];//60;
lch_yellow=launchpad_color[2];//62;
lch_red=launchpad_color[3];//15;
lch_ambre=launchpad_color[4];//31;
lch_orange_fonce=launchpad_color[5];//30;
//redeifinition des couleurs
define_colors();

 return(0);
}


int midi_launchpad_colors(int cfg_midiX,int cfg_midiY)
{
char temp_str_lch[36];
petitchiffre.Print("Launchpad",cfg_midiX,cfg_midiY-2);
petitchiffre.Print("Colors",cfg_midiX,cfg_midiY+10);
for(int pm=0;pm<6;pm++)
{
sprintf(temp_str_lch,"Col.%d",pm+1);
petitpetitchiffre.Print(temp_str_lch,cfg_midiX,cfg_midiY+35+(pm*25));
sprintf(temp_str_lch,"%d",launchpad_color[pm]);
Rect LaunchCol(Vec2D(cfg_midiX+40,cfg_midiY+20+(pm*25)),Vec2D(40,20));
LaunchCol.SetRoundness(7.5);
LaunchCol.Draw(CouleurFond.WithAlpha(0.5));
petitpetitchiffre.Print(temp_str_lch,cfg_midiX+50,cfg_midiY+35+(pm*25));

if(mouse_x>cfg_midiX+40 && mouse_x<cfg_midiX+40+40 && mouse_y>cfg_midiY+25+(pm*25) && mouse_y<cfg_midiY+25+(pm*25)+20)
{
LaunchCol.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0)
{
int temp_collauch=atol(numeric);
reset_numeric_entry();
if(temp_collauch>=0 && temp_collauch<=127)
{
launchpad_color[pm]=temp_collauch;
refresh_launchpad_color_callibration();
}
mouse_released=1;
}
}

}

petitchiffre.Print("Chaser:",cfg_midiX,cfg_midiY+190);
petitchiffre.Print("Rows",cfg_midiX,cfg_midiY+205);
Rect LaunchRows(Vec2D(cfg_midiX+40,cfg_midiY+190),Vec2D(40,20));
LaunchRows.SetRoundness(7.5);
LaunchRows.Draw(CouleurFond.WithAlpha(0.5));
petitpetitchiffre.Print(ol::ToString(chaser_midi_rows),cfg_midiX+55,cfg_midiY+205);

if(mouse_x>cfg_midiX+40 && mouse_x<cfg_midiX+40+40 && mouse_y>cfg_midiY+190 && mouse_y<cfg_midiY+205)
{
LaunchRows.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0)
{
chaser_midi_rows=atol(numeric);
reset_numeric_entry();
if(chaser_midi_rows<1){chaser_midi_rows=1;}
if( chaser_midi_rows>8){chaser_midi_rows=8;}
mouse_released=1;
}
}
return(0);
}

////////////////////////////////////////////////////////////////////////////////
int clock_wheel (int xw,int yw, int rayon_k, float angle_correction)
{
Circle (Vec2D(xw,yw), rayon_k+5).DrawOutline(CouleurLigne);
Circle (Vec2D(xw,yw), rayon_k-5).DrawOutline(CouleurLigne);

Circle(Vec2D(position_curseur_clock_x,position_curseur_clock_y),5).Draw(CouleurBlind);


petitpetitchiffre.Print(ol::ToString(midi_levels[1894]),xw-5,yw+12);

//AFFECTATION MIDI
if( Midi_Faders_Affectation_Type!=0)//config midi
  {
  if(mouse_x>xw-rayon_k-5 && mouse_x<xw+rayon_k+5 && mouse_y>yw-rayon_k-5 && mouse_y<yw+rayon_k+5)
  {
  Circle (Vec2D(xw,yw), rayon_k+5).DrawOutline(CouleurBlind);
  if(mouse_button==1 && mouse_released==0)
  {
  Circle (Vec2D(xw,yw), rayon_k+5).Draw(CouleurBlind);
  }
  }
}

//toggle mode Relativ / absolute
Rect WheelMode(Vec2D(xw+rayon_k+10,yw-rayon_k),Vec2D(15,15));
WheelMode.SetRoundness(3);

switch(clocklevel_absolutemode)
{
case 0:
WheelMode.Draw(CouleurLock);
petitchiffre.Print("R",xw+rayon_k+13,yw-rayon_k+12);
break;
case 1:
WheelMode.Draw(CouleurSurvol);
petitchiffre.Print("A",xw+rayon_k+13,yw-rayon_k+12);
break;
default: break;
}
WheelMode.DrawOutline(CouleurLigne);

//midi out
Line (Vec2D(xw+rayon_k,yw+rayon_k-3),Vec2D(xw+rayon_k+7,yw+rayon_k+7)).Draw(CouleurLigne);
Circle MidiOutW(Vec2D(xw+rayon_k+10,yw+rayon_k+10),7);
if(midi_send_out[1894]==1){MidiOutW.Draw(CouleurBlind);}

MidiOutW.DrawOutline(CouleurLigne);


//AFFECTATION MIDI
if(window_focus_id==W_CFGMENU && mouse_button==1 && mouse_released==0)
{
//SOURIS OK
for( float clock_angle = 0.0+angle_correction ; clock_angle <(PIknob*2)+angle_correction  ; clock_angle+=0.01)//radians
{
   clock_vx = cos(clock_angle)* rayon_k;
   clock_vy = sin(clock_angle)* rayon_k;
   if(mouse_x>xw+clock_vx-5  && mouse_x<xw+clock_vx+5 && mouse_y>yw+clock_vy-5 && mouse_y<yw+clock_vy+5 )
   {
   angle_snap_clock=clock_angle;//angle rotation niveaux
   position_curseur_clock_x= xw+clock_vx;
   position_curseur_clock_y=yw+clock_vy ;
   midi_levels[1894]=(int)(((angle_snap_clock-angle_correction)/(PIknob*2))*128);
   do_clock_level_modification(midi_levels[1894]);
   if(midi_send_out[1894]==1){index_send_midi_out[1894]=1;}

   }
}


if(Midi_Faders_Affectation_Type!=0)//config midi
  {
  //midi report
  switch(miditable[0][1894])
  {
  case 0: sprintf(thetypinfo,"Note");break;
  case 1: sprintf(thetypinfo,"Key On");break;
  case 2: sprintf(thetypinfo,"Key Off");break;
  case 4: sprintf(thetypinfo,"Ctrl Change");break;
  default:break;
  }
  sprintf(string_last_midi_id,"CLOCK LEVEL WHEEL is Ch: %d Pitch: %d Typ: %s" , miditable[1][1894],miditable[2][1894],thetypinfo);

  if(mouse_x>xw-rayon_k-5 && mouse_x<xw+rayon_k+5 && mouse_y>yw-rayon_k-5 && mouse_y<yw+rayon_k+5)
  {

  attribute_midi_solo_affectation(1894,Midi_Faders_Affectation_Mode);
  mouse_released=1;
  }

}

//toggle mode Relativ / absolute

if(mouse_x>xw+rayon_k+10 && mouse_x<xw+rayon_k+10+15 && mouse_y>yw-rayon_k && mouse_y<yw-rayon_k+15)
{
clocklevel_absolutemode=toggle(clocklevel_absolutemode);
mouse_released=1;
}
//midi out

if(mouse_x>xw+rayon_k+10-7 && mouse_x<xw+rayon_k+10+7 && mouse_y>yw+rayon_k+10-7 && mouse_y<yw+rayon_k+10+7)
{
midi_send_out[1894]=toggle(midi_send_out[1894]);
mouse_released=1;
}
}
return(0);
}


int midi_clock_part(int _x,int _y)
{
  //midiclock view

 petitchiffre.Print("MIDI CLOCK SIGNAL:", _x,_y);
 Rect Button(Vec2D(_x,_y+15),Vec2D(50,20));
 Button.SetRoundness(4.5);
 Button.DrawOutline(CouleurBlanc);
 petitchiffre.Print("MIDI CLOCK", _x+70,_y+28);
 switch(index_midi_clock_on)
 {
    case 0:
     petitchiffre.Print("/Off", _x+5,_y+28);
    break;
    case 1:
     petitchiffre.Print("/ON", _x+5,_y+28);
    break;
    default: break;
 }

 Rect BPm_(Vec2D(_x,_y+45),Vec2D(60,20));
 BPm_.SetRoundness(4.5);
 BPm_.Draw(CouleurFond.WithAlpha(0.5));
 BPm_.DrawOutline(CouleurLigne.WithAlpha(0.3));
 petitchiffre.Print("BPM", _x+70,_y+58);
 petitchiffre.Print(ol::ToString(midi_BPM), _x+5,_y+58);

//relativ_encoder_midi_clock_value
clock_wheel (_x+200,_y+20, rayon_wheel_level,angle_correction_wheel);

//increment clock wheel
Rect BPm_c(Vec2D(_x+120,_y+45),Vec2D(30,20));
 BPm_c.SetRoundness(4.5);
 BPm_c.Draw(CouleurFond.WithAlpha(0.5));
 BPm_c.DrawOutline(CouleurLigne.WithAlpha(0.3));
 petitchiffre.Print("Clock+", _x+160,_y+58);
 petitchiffre.Print(ol::ToString(relativ_encoder_midi_clock_value), _x+125,_y+58);
 if(window_focus_id==W_CFGMENU && mouse_x>_x+120 && mouse_x<_x+150 && mouse_y>_y+45 && mouse_y<_y+65 && mouse_button==1 && mouse_released==0)
    {
    if(numeric_postext>0 && atoi(numeric)>0)
    {
    relativ_encoder_midi_clock_value=atoi(numeric);
    reset_numeric_entry();
    }
    mouse_released=1;
    }


//personal midi bpm rates
for(int i=0;i<4;i++)
{
    for (int j=0;j<4;j++)
    {
    BPm_.MoveTo(Vec2D(_x+(65*j),_y+75+(30*i)));
    BPm_.Draw(CouleurFond.WithAlpha(0.5));
    BPm_.DrawOutline(CouleurLigne.WithAlpha(0.3));
    petitchiffre.Print(ol::ToString(bpm_personnal[j+(i*4)]),_x+5+(65*j),_y+90+(30*i));
    if(Midi_Faders_Affectation_Type!=0 && window_focus_id==W_CFGMENU && mouse_x>_x+(65*j) && mouse_x<_x+(65*j)+60 && mouse_y>_y+75+(30*i) && mouse_y<_y+75+(30*i)+20 )
    {  BPm_.DrawOutline(CouleurBlind);}
    if(window_focus_id==W_CFGMENU && mouse_x>_x+(65*j) && mouse_x<_x+(65*j)+60 && mouse_y>_y+75+(30*i) && mouse_y<_y+75+(30*i)+20 && mouse_button==1 && mouse_released==0)
    {
    //affectation midi
    //AFFECTATION MIDI
if(Midi_Faders_Affectation_Type!=0)//config midi
  {
  //midi report
  BPm_.DrawOutline(CouleurBlind);
  switch(miditable[0][664])
  {
  case 0: sprintf(thetypinfo,"Note");break;
  case 1: sprintf(thetypinfo,"Key On");break;
  case 2: sprintf(thetypinfo,"Key Off");break;
  case 4: sprintf(thetypinfo,"Ctrl Change");break;
  default: break;
  }
  sprintf(string_last_midi_id,"CLOCK LOAD is Ch: %d Pitch: %d Typ: %s" , miditable[1][1895+j+(i*4)],miditable[2][1895+j+(i*4)],thetypinfo);

  if(Midi_Faders_Affectation_Type==1)
  {
       attribute_midi_solo_affectation(1895+j+(i*4),Midi_Faders_Affectation_Mode);
  }
  else if(Midi_Faders_Affectation_Type==2)
  {attribute_midi_to_control(1895+j+(i*4), Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);}

  }

  else{

    if(numeric_postext>0 && atoi(numeric)>0)
    {
    bpm_personnal[j+(i*4)]=atoi(numeric);
    reset_numeric_entry();
    }
    else
    {
    midi_BPM=bpm_personnal[j+(i*4)];
    ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
    install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);
    reset_numeric_entry();
    }
    }
    mouse_released=1;
    }
    }
}

if( window_focus_id==W_CFGMENU)
{
//on off
  if( mouse_x>_x && mouse_x<_x+50 && mouse_y>_y+15 && mouse_y<_y+35 && mouse_button==1 && mouse_released==0)
 {
 index_midi_clock_on=toggle(index_midi_clock_on);
 mouse_released=1;
 }
//BPM
 if(mouse_x>_x && mouse_x<_x+60 && mouse_y>_y+45 && mouse_y<_y+65 && mouse_button==1 && mouse_released==0)
 {
  BPm_.DrawOutline(CouleurLigne);
  if(atoi(numeric)>0)
  {
  midi_BPM= atoi(numeric);
  ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
  install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);
  reset_numeric_entry();
  mouse_released=1;
 }
 }
}

 return(0);
}



int midipage_preset_and_options(int cfg_midiX,int cfg_midiY, int largeurCFGmidi,int hauteurCFGmidi)
{
//affichage signal
petitchiffrerouge.Print( my_midi_original_string,cfg_midiX+470,cfg_midiY+17);
petitchiffre.Print( my_midi_string,cfg_midiX+500,cfg_midiY+32);
for(int pm=0;pm<8;pm++)
{
Rect MidiOption(Vec2D(cfg_midiX+20,cfg_midiY+45+(pm*30)),Vec2D(55,20));
MidiOption.SetRoundness(7.5);
MidiOption.Draw(CouleurFond.WithAlpha(0.5));
if(mouse_x>cfg_midiX+20 && mouse_x<cfg_midiX+20+55 && mouse_y>cfg_midiY+45+(pm*30) && mouse_y<cfg_midiY+45+20+(pm*30)  && window_focus_id==920)
{
MidiOption.Draw(CouleurSurvol) ;
if(mouse_button==1 && mouse_released==0)
{
switch(pm)
{
case 0:
cheat_key_off=toggle(cheat_key_off);
break;
case 1:
cheat_key_off_to_key_on=toggle(cheat_key_off_to_key_on);
break;
case 2:
index_midi_auto_desaffect=toggle(index_midi_auto_desaffect);
break;
case 3://auto demute
index_midi_auto_demute=toggle(index_midi_auto_demute);
break;
case 4://mute on LFO
index_midi_mute_on_lfo=toggle(index_midi_mute_on_lfo);
break;
case 5://automute speed midi on cuelist
index_auto_mute_cuelist_speed=toggle(index_auto_mute_cuelist_speed);
break;
case 6:
enable_launchpad=toggle(enable_launchpad);
if(enable_launchpad==1){ reset_launchpad();}
break;
case 7:
index_midi_global_thruth=toggle(index_midi_global_thruth);
break;
default:
break;
}
mouse_released=1;
}
}
switch(pm)
{
case 0:
MidiOption.Draw(CouleurFader.WithAlpha(cheat_key_off)) ;
petitpetitchiffre.Print("Key-On Vel 0 = Key-Off",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
case 1:
MidiOption.Draw(CouleurFader.WithAlpha(cheat_key_off_to_key_on)) ;
petitpetitchiffre.Print("Key-Off = Key-On Vel 0",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
case 2:
MidiOption.Draw(CouleurFader.WithAlpha(index_midi_auto_desaffect)) ;
petitpetitchiffre.Print("Auto-Desaffectation",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
case 3://auto demute
MidiOption.Draw(CouleurFader.WithAlpha(index_midi_auto_demute)) ;
petitpetitchiffre.Print("Auto-demute",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
case 4://mute on LFO
MidiOption.Draw(CouleurFader.WithAlpha(index_midi_mute_on_lfo)) ;
petitpetitchiffre.Print("Mute on LFO",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
case 5:
MidiOption.Draw(CouleurFader.WithAlpha(index_auto_mute_cuelist_speed)) ;
petitpetitchiffre.Print("Auto-mute Cuelist Speed",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
case 6:
MidiOption.Draw(CouleurFader.WithAlpha(enable_launchpad)) ;
petitpetitchiffre.Print("To LAUNCHPAD",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
case 7:
MidiOption.Draw(CouleurFader.WithAlpha(index_midi_global_thruth)) ;
petitpetitchiffre.Print("Midi THRU",cfg_midiX+80,cfg_midiY+57+(pm*30));
break;
default: break;
}
}

midi_launchpad_colors(cfg_midiX+230,cfg_midiY+60);
midi_change_signal(cfg_midiX+355, cfg_midiY+70);


midi_clock_part(cfg_midiX+570, cfg_midiY+55);//on off midi clock and BPM


return(0);
}

int midipage_devices(int cfg_midiX,int cfg_midiY, int largeurCFGmidi,int hauteurCFGmidi)
{

    char string_midi_device_in[64];
    char string_midi_device_out[64];


    midi_list_and_choose_devices();

    Rect MidiInDev( Vec2D(cfg_midiX+15,cfg_midiY+40), Vec2D ( 400,240));
    MidiInDev.SetRoundness(5);
    MidiInDev.Draw(CouleurFond);


    Rect MidiOutDev( Vec2D(cfg_midiX+420,cfg_midiY+40), Vec2D ( 400,240));
    MidiOutDev.SetRoundness(5);
    MidiOutDev.Draw(CouleurFond);

    //midi INPUT
    for (int i=1;i<=compt_midi_in;i++)
    {
    if(compt_midi_in<=16)
    {
    if (i<=8)
    {

     Rect MidiDeviceBox( Vec2D(cfg_midiX+20,cfg_midiY+15+(i*30)), Vec2D ( 190,25));
     MidiDeviceBox.SetRoundness(7.5);
     MidiDeviceBox.SetLineWidth(epaisseur_ligne_fader);
     if( window_focus_id==920)
     {
     if(mouse_x>cfg_midiX+20 && mouse_x<cfg_midiX+220 && mouse_y>cfg_midiY+15+(i*30) && mouse_y<cfg_midiY+45+(i*30))
     {
     MidiDeviceBox.Draw(CouleurBleuProcedure);
     if(mouse_button==1 &&  mouse_released==0 )
     {
      MidiDeviceBox.Draw(CouleurFader);
      if( do_connect_in[i]==0){ do_connect_in[i]=1;  }
      mouse_released=1;
     }
     }
     }
      if(midi_in_is_connected[i]==1)
      {MidiDeviceBox.DrawOutline(CouleurLevel);}
      sprintf(string_midi_device_in,"%s",tableau_peripheriques_in[i]);
      petitpetitchiffre.Print(string_midi_device_in,cfg_midiX+25,cfg_midiY+30+(i*30));
    }
    else if(i>8)//deuxieme colonne
    {
     Rect MidiDeviceBox( Vec2D(cfg_midiX+220,cfg_midiY+15+((i-8)*30)), Vec2D ( 190,25));
     MidiDeviceBox.SetRoundness(7.5);
     MidiDeviceBox.SetLineWidth(epaisseur_ligne_fader);
     if( window_focus_id==920)
     {
     if(mouse_x>cfg_midiX+230 && mouse_x<cfg_midiX+380 && mouse_y>cfg_midiY+15+((i-8)*30) && mouse_y<cfg_midiY+45+((i-8)*30))
     {
     MidiDeviceBox.Draw(CouleurBleuProcedure);

     if(mouse_button==1 &&  mouse_released==0 )
     {
      MidiDeviceBox.Draw(CouleurFader);
      do_connect_in[i]=1;
      mouse_released=1;
     }
     }
     }
      if(midi_in_is_connected[i]==1)
      {MidiDeviceBox.DrawOutline(CouleurLevel);}
      sprintf(string_midi_device_in,tableau_peripheriques_in[i]);
      petitpetitchiffre.Print(string_midi_device_in,cfg_midiX+225,cfg_midiY+30+((i-8)*30));
    }
    }
    }

  // MIDI OUTPUT
    for (int j=1;j<=compt_midi_out;j++)
    {

    if(compt_midi_out<=16)
    {
    if(j<=8)
    {
     Rect MidiDeviceBox( Vec2D(cfg_midiX+420,cfg_midiY+15+(j*30)), Vec2D ( 190,25));
     MidiDeviceBox.SetRoundness(7.5);
     MidiDeviceBox.SetLineWidth(epaisseur_ligne_fader);
     if( window_focus_id==920)
     {
     if(mouse_x>cfg_midiX+420 && mouse_x<cfg_midiX+620 && mouse_y>cfg_midiY+15+(j*30) && mouse_y<cfg_midiY+45+(j*30))
     {
     MidiDeviceBox.Draw(CouleurBlind.WithAlpha(0.5));
     if(mouse_button==1 &&  mouse_released==0 )
     {
      MidiDeviceBox.Draw(CouleurFader);
      if( do_connect_out[j+compt_midi_in]==0){ do_connect_out[j+compt_midi_in]=1;  }
      mouse_released=1;
     }
     }
     }
     if (midi_out_is_connected[j+compt_midi_in]== 1)
      {MidiDeviceBox.DrawOutline(CouleurBlind);}

     sprintf(string_midi_device_out,"%s",tableau_peripheriques_out[j]);
     petitpetitchiffre.Print(string_midi_device_out,cfg_midiX+425,cfg_midiY+30+(j*30));
    }

    else if(j>8)//deuxieme colonne
    {
     Rect MidiDeviceBox( Vec2D(cfg_midiX+620,cfg_midiY+15+((j-8)*30)), Vec2D ( 190,25));
     MidiDeviceBox.SetRoundness(7.5);
     MidiDeviceBox.SetLineWidth(epaisseur_ligne_fader);
     if( window_focus_id==920)
     {
     if(mouse_x>cfg_midiX+620 && mouse_x<cfg_midiX+820 && mouse_y>cfg_midiY+15+((j-8)*30) && mouse_y<cfg_midiY+45+((j-8)*30))
     {
     MidiDeviceBox.Draw(CouleurBlind.WithAlpha(0.5));
     if(mouse_button==1 &&  mouse_released==0 )
     {
      MidiDeviceBox.Draw(CouleurFader);
      if( do_connect_out[j+compt_midi_in]==0){ do_connect_out[j+compt_midi_in]=1;  }
      mouse_released=1;
     }
     }
     }
     if (midi_out_is_connected[j+compt_midi_in]== 1)
      {MidiDeviceBox.DrawOutline(CouleurBlind);}

      sprintf(string_midi_device_out,tableau_peripheriques_out[j]);
      petitpetitchiffre.Print(string_midi_device_out,cfg_midiX+625,cfg_midiY+30+((j-8)*30));
    }
    }
    }



    Rect LabelIn(Vec2D(cfg_midiX+372,cfg_midiY+30),Vec2D(40,20));
    LabelIn.Draw(CouleurBleuProcedure);
    petitchiffre.Print("INPUT",cfg_midiX+375,cfg_midiY+43);

    Rect LabelOut(Vec2D(cfg_midiX+768,cfg_midiY+30),Vec2D(50,20));
    LabelOut.Draw(CouleurBlind.WithAlpha(0.5));
    petitchiffre.Print("OUTPUT",cfg_midiX+770,cfg_midiY+43);



 ///RESCAN

    Rect MidiRescanDriver( Vec2D(cfg_midiX+720,cfg_midiY), Vec2D ( 70,25));
    MidiRescanDriver.SetRoundness(7.5);
    MidiRescanDriver.Draw(CouleurFond.WithAlpha(0.7));
    if( window_focus_id==920)
    {
    if(mouse_x>cfg_midiX+720 && mouse_x<cfg_midiX+720+70 && mouse_y>cfg_midiY && mouse_y<cfg_midiY+25)
    {
    MidiRescanDriver.Draw(CouleurSurvol);
    if(mouse_button==1 && mouse_released==0)
    {
    MidiRescanDriver.Draw(CouleurFader);
    QuitMidi() ;

    InitMidi();//init pose souci . au chargement de white cat init pause souci des que ouv de fichiers
    mouse_released=1;
    }
    }
    }
    petitchiffre.Print("Rescan",cfg_midiX+730,cfg_midiY+15);
    MidiRescanDriver.DrawOutline(CouleurLigne);

 return(0);
}


int do_midi_config(int cfg_midiX,int cfg_midiY, int largeurCFGmidi,int hauteurCFGmidi)
{

for(int pp=0;pp<3;pp++)
{
Rect MidiMenu( Vec2D(cfg_midiX+20+(pp*150),cfg_midiY+1), Vec2D ( 140,35));
     MidiMenu.SetRoundness(7.5);
     MidiMenu.SetLineWidth(epaisseur_ligne_fader/2);
     MidiMenu.Draw(CouleurFond.WithAlpha(0.2));
//selection des pages
if( window_focus_id==920)
{
if(mouse_y>cfg_midiY+1 && mouse_y<cfg_midiY+35)
{
if(mouse_x>cfg_midiX+20+(pp*150) && mouse_x<cfg_midiX+20+(pp*150)+140)
{
     MidiMenu.Draw(CouleurFond.WithAlpha(0.5));
     if(mouse_button==1 &&  mouse_released==0 ){midi_page=pp; mouse_released=1;}
}
}
}
//bouton devices
if(pp==0)
{
  petitchiffre.Print("MIDI DEVICES",cfg_midiX+30+(pp*150),cfg_midiY+20);
}

//bouton config load preset
else if(pp==1)
{
  petitchiffre.Print("OPTIONS / PRESETS",cfg_midiX+30+(pp*150),cfg_midiY+20);
}
//bouton config Faders de 1 à 48
else if(pp==2)
{
  petitchiffre.Print("MIDI AFFECT",cfg_midiX+30+(pp*150),cfg_midiY+20);
}

  if(midi_page==pp){MidiMenu.DrawOutline(CouleurLigne);}
}




  if(midi_page==0){midipage_devices(cfg_midiX,cfg_midiY+10,largeurCFGmidi,hauteurCFGmidi);}

  if(midi_page==1){midipage_preset_and_options(cfg_midiX,cfg_midiY,largeurCFGmidi,hauteurCFGmidi);}

  if(midi_page==2){midipage_affectation(cfg_midiX,cfg_midiY,largeurCFGmidi,hauteurCFGmidi);}

return(0);
}






