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

* \file banger_core_8.cpp
* \brief {Bangers fonctions}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gestion des fonctions des banger
*
*   Bangers Core fonctions
*
 **/

int Chrono_Reset()
{
 actual_tickers_chrono=0;
 time_minutes=0;
 time_secondes=0;
 time_centiemes=0;

 angle_timesnap_min=0.0;
angle_timesnap_sec=0.0;
angle_timesnap_dix=0.0;
set_time_cursor_to_time_type(time_wheel_datatype_is);

 return(0);
}



int store_state_of_fader_before_bang(int fader_num)
{
remember_state_of_banged_fader[fader_num][0]=FaderLocked[fader_num];//lock state is
remember_state_of_banged_fader[fader_num][1]=(int)Fader[fader_num];//level is
remember_state_of_banged_fader[fader_num][2]=detect_dock_used(fader_num);//dock is
remember_state_of_banged_fader[fader_num][3]=(int)lfo_speed[fader_num];//lfo level is
remember_state_of_banged_fader[fader_num][4]=is_dock_for_lfo_selected[fader_num][0];//loop dk 0 is
remember_state_of_banged_fader[fader_num][5]=is_dock_for_lfo_selected[fader_num][1];//loop dk 1 is
remember_state_of_banged_fader[fader_num][6]=is_dock_for_lfo_selected[fader_num][2];//loop dk 2 is
remember_state_of_banged_fader[fader_num][7]=is_dock_for_lfo_selected[fader_num][3];//loop dk 3 is
remember_state_of_banged_fader[fader_num][8]=is_dock_for_lfo_selected[fader_num][4];//loop dk 4 is
remember_state_of_banged_fader[fader_num][9]=is_dock_for_lfo_selected[fader_num][5];//loop dk 5 is
remember_state_of_banged_fader[fader_num][10]= lfo_mode_is[fader_num];//0 nothing 1 up 2 down
remember_state_of_banged_fader[fader_num][11]= lfo_cycle_is_on[fader_num];//saw
remember_state_of_banged_fader[fader_num][12]= lfo_cycle_steps[fader_num];//up down
remember_state_of_banged_fader[fader_num][13]=lfo_do_next_step[fader_num][0];//prev dock
remember_state_of_banged_fader[fader_num][14]=lfo_do_next_step[fader_num][1];//next dock
remember_state_of_banged_fader[fader_num][15]=FaderCurves[fader_num];//curves
return(0);
}

int restore_state_of_fader_before_bang(int fader_num)
{
FaderLocked[fader_num]=remember_state_of_banged_fader[fader_num][0];//lock state is
Fader[fader_num]=remember_state_of_banged_fader[fader_num][1];//level is
for(int io=0;io<core_user_define_nb_docks;io++)
{
DockIsSelected[fader_num][io]=0;
}
DockIsSelected[fader_num][remember_state_of_banged_fader[fader_num][2]]=1;//dock is
lfo_speed[fader_num]=remember_state_of_banged_fader[fader_num][3];//lfo level is
is_dock_for_lfo_selected[fader_num][0]=remember_state_of_banged_fader[fader_num][4];//loop dk 0 is
is_dock_for_lfo_selected[fader_num][1]=remember_state_of_banged_fader[fader_num][5];//loop dk 1 is
is_dock_for_lfo_selected[fader_num][2]=remember_state_of_banged_fader[fader_num][6];//loop dk 2 is
is_dock_for_lfo_selected[fader_num][3]=remember_state_of_banged_fader[fader_num][7];//loop dk 3 is
is_dock_for_lfo_selected[fader_num][4]=remember_state_of_banged_fader[fader_num][8];//loop dk 4 is
is_dock_for_lfo_selected[fader_num][5]=remember_state_of_banged_fader[fader_num][9];//loop dk 5 is
lfo_mode_is[fader_num]=remember_state_of_banged_fader[fader_num][10];//0 nothing 1 up 2 down
lfo_cycle_is_on[fader_num]=remember_state_of_banged_fader[fader_num][11];//saw
lfo_cycle_steps[fader_num]=remember_state_of_banged_fader[fader_num][12];//up down
lfo_do_next_step[fader_num][0]=remember_state_of_banged_fader[fader_num][13];//prev dock
lfo_do_next_step[fader_num][1]=remember_state_of_banged_fader[fader_num][14];//next dock
FaderCurves[fader_num]=remember_state_of_banged_fader[fader_num][15];//curves
return(0);
}



int Bang_event_back(int banger_num, int event_num)
{
int the_fader_is=0;
int param1_is=0;
int param2_is=0;

switch (bangers_type[banger_num][event_num])
{
case 1: //fader
the_fader_is=bangers_params[banger_num][event_num][0]-1;
param2_is=bangers_params[banger_num][event_num][1];


if(the_fader_is>=0 && the_fader_is<core_user_define_nb_faders)
{
     switch(bangers_action[banger_num][event_num])
     {
     case 0://lock
     FaderLocked[the_fader_is]=remember_state_of_banged_fader[the_fader_is][0];//lock state is
     switch(FaderLocked[the_fader_is])
     {
     case 0:
     FaderLocked[the_fader_is]=0;
     //remise à plat du niveau
     Fader[the_fader_is]=(unsigned char)((((float)(StateOfFaderBeforeLock[the_fader_is]))/255)*locklevel);
     midi_levels[the_fader_is]=(int)(((float)Fader[the_fader_is])/2);
     break;
     case 1:
     FaderLocked[the_fader_is]=1;
     StateOfFaderBeforeLock[the_fader_is]=Fader[the_fader_is];
     if(StateOfFaderBeforeLock[the_fader_is]==255){LockFader_is_FullLevel[the_fader_is]=1;}
     else if(StateOfFaderBeforeLock[the_fader_is]<255){LockFader_is_FullLevel[the_fader_is]=0;}
     break;
     default: break;
     }
     sprintf(string_event,"BACK:Lock Fader %d",the_fader_is+1);
     break;
     case 1://up devient down
     start_time_for_delays[the_fader_is]=actual_time;
     switch(param2_is)
     {
     case 0:
     lfo_mode_is[the_fader_is]=0;
     break;
     case 1:
     lfo_mode_is[the_fader_is]=2;
     faders_in_float[the_fader_is]=Fader[the_fader_is];
     break;
     default: break;
     }
     lfo_cycle_is_on[the_fader_is]=0;
     sprintf(string_event,"BACK:UP Fader %d",the_fader_is+1);
     break;
     case 2://down devient up
     start_time_for_delays[the_fader_is]=actual_time;
     switch(param2_is)
     {
     case 0:
     lfo_mode_is[the_fader_is]=0;
     break;
     case 1:
     lfo_mode_is[the_fader_is]=1;
     faders_in_float[the_fader_is]=Fader[the_fader_is];
     break;
     default: break;
     }
     lfo_cycle_is_on[the_fader_is]=0;
     sprintf(string_event,"BACK:Down Fader %d",the_fader_is+1);
     break;
     case 3://saw // inversion
     start_time_for_delays[the_fader_is]=actual_time;
     switch(param2_is)
     {
     case 0:
     lfo_mode_is[the_fader_is]=0;
     lfo_cycle_is_on[the_fader_is]=1;
     if(Fader[the_fader_is]>0 && Fader[the_fader_is]<255 ){lfo_running_is_upward[the_fader_is]=1;}
     break;
     case 1:
     lfo_cycle_is_on[the_fader_is]=0;
     lfo_mode_is[the_fader_is]=2;//descente du fader
     break;
     default: break;
     }
     sprintf(string_event,"BACK:Saw Fader %d",the_fader_is+1);
     break;
     case 4://to prev dock devient inversé
      switch(param2_is)
     {
     case 0:
     lfo_do_next_step[the_fader_is][0]=1; lfo_do_next_step[the_fader_is][1]=0;
     break;
     case 1:
     lfo_do_next_step[the_fader_is][0]=0;
     break;
     default: break;
     }
     sprintf(string_event,"BACK:Prev Dock Fader %d",the_fader_is+1);
     break;
     case 5://to next dock
     switch(param2_is)
     {
     case 0:
     lfo_do_next_step[the_fader_is][1]=1;
     lfo_do_next_step[the_fader_is][0]=0;
     break;
     case 1:
     lfo_do_next_step[the_fader_is][1]=0;
     break;
     default: break;
     }
     sprintf(string_event,"BACK:Next Dock Fader %d",the_fader_is+1);
     break;
     case 6://up down
     switch(param2_is)
     {
     case 0:
     lfo_cycle_steps[the_fader_is]=1;
     break;
     case 1:
     lfo_cycle_steps[the_fader_is]=0;
     break;
     default: break;
     }
     sprintf(string_event,"BACK:Up-Down Fader %d",the_fader_is+1);
     break;
     case 7://set dock  looped
     dock_selected_for_record=detect_dock_used(the_fader_is);//utilise en temporaire
     switch(param2_is)
     {
     case 0:
     is_dock_for_lfo_selected[the_fader_is][dock_selected_for_record]=1;
     break;
     case 1:
     is_dock_for_lfo_selected[the_fader_is][dock_selected_for_record]=0;
     break;
     default: break;
     }
     sprintf(string_event,"BACK:Dock looped Fader %d",the_fader_is+1);
     break;
     case 8://set all looped
      switch(param2_is)
      {
      case 0:
      for(int p=0;p<core_user_define_nb_docks;p++)
      {
      is_dock_for_lfo_selected[the_fader_is][p]=1;
      }
      break;
      case 1:
      for(int p=0;p<core_user_define_nb_docks;p++)
      {
      is_dock_for_lfo_selected[the_fader_is][p]=0;
      }
      break;
      default: break;
      }
      sprintf(string_event,"BACK:All Looped Fader %d",the_fader_is+1);
     break;
     case 9://set dock selected is
     if(param2_is>0 && param2_is<7)
     {
      DockIsSelected[the_fader_is][remember_state_of_banged_fader[the_fader_is][2]]=1;
      Unselect_other_docks(the_fader_is, (remember_state_of_banged_fader[the_fader_is][2]));
     }
     sprintf(string_event,"BACK:Select dock Fader %d",the_fader_is+1);
     break;
     case 10://set LFO at
     lfo_speed[the_fader_is]=remember_state_of_banged_fader[the_fader_is][3];
     midi_levels[196+the_fader_is]=remember_state_of_banged_fader[the_fader_is][3];
     index_send_midi_out[196+the_fader_is]=1;

     if(DockTypeIs[the_fader_is][dock_used_by_fader_is[the_fader_is]]==12)//enchassement Grid si slave
     {
     asservissement_gridplayer(the_fader_is,dock_used_by_fader_is[the_fader_is]);
     }
     sprintf(string_event,"BACK:Set Speed Fader %d",the_fader_is+1);
     break;

     case 11://set Fader At
     int niv_transforme;
     switch( dmx_view)
     {
      case 0:
       if(remember_state_of_banged_fader[the_fader_is][1]>=0 && remember_state_of_banged_fader[the_fader_is][1]<=100)
      {
      niv_transforme=(int)((float)(remember_state_of_banged_fader[the_fader_is][1])*2.55);
      if(param2_is==100){niv_transforme=255;}
      }
      break;
      case 1:
      if(remember_state_of_banged_fader[the_fader_is][1]>=0 && remember_state_of_banged_fader[the_fader_is][1]<=255)
      {
      niv_transforme=remember_state_of_banged_fader[the_fader_is][1];
      }
      break;
      default: break;
     }
     /*Fader[the_fader_is]= niv_transforme;
     midi_levels[the_fader_is]= niv_transforme/2;
     index_send_midi_out[the_fader_is]=1;*/
     fader_set_level(the_fader_is,niv_transforme);

     if(lfo_mode_is[the_fader_is]==1 || lfo_mode_is[the_fader_is]==2 || lfo_cycle_is_on[the_fader_is]==1)
     {
     lfo_mode_is[the_fader_is]=0; lfo_mode_is[the_fader_is]=0; lfo_cycle_is_on[the_fader_is]=0;
     }
     sprintf(string_event,"BACK:Set Fader %d",the_fader_is+1);
     break;

     case 12://end pos pour auto mouvement
          StopPosOn[the_fader_is]=1;
          LevelStopPos[the_fader_is]=PreviousLevelStopPos[the_fader_is];
          do_light_setpos[the_fader_is]=1;
          sprintf(string_event,"BACK:SetStopPos at %d Fader %d",PreviousLevelStopPos[the_fader_is],the_fader_is+1);
     break;

     case 13://on off end pos
     if(param2_is==0 || param2_is==1)
     {
     ActionnateStopOn[the_fader_is]=toggle(param2_is);
     do_light_setpos[the_fader_is]=1;
     switch(param2_is)
     {
     case 0:
     sprintf(string_event,"BACK: ENDPOS ON Fader %d",the_fader_is+1);
     break;
     case 1:
     sprintf(string_event,"BACK: ENDPOS OFF Fader %d",the_fader_is+1);
     break;
     default: break;
     }
     }
     break;
     case 14://paste to stage output of faders annulé et récup de l etat de la memoire
     //no back up
     sprintf(string_event,"NO BACK: Paste Fader %d",the_fader_is+1);
     break;
     case 15://set midi out inversee
     switch(param2_is)
      {
      case 0:
      midi_send_out[the_fader_is]=1;
      break;
      case 1:
      midi_send_out[the_fader_is]=0;
      break;
      default: break;
     }
     sprintf(string_event,"BACK:MidiOut Fader %d",the_fader_is+1);
     break;
    case 16://recall back
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
     case 17://recall back
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
     case 18://recall back
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
      case 19://recall back
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
      case 20://recall back
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
      case 21://recall back
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
      case 22://recall back
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
     case 23: // recall n a pas de back
     break;
     case 24://LOCKS PRESET inversé
     param1_is=bangers_params[banger_num][event_num][0]-1;
     do_lock_preset(param1_is);
     break;
     case 25://assign curve  back
     FaderCurves[the_fader_is]=before_bang_FaderCurves[the_fader_is];//pour go back
     sprintf(string_event,"BACK: Fader %d Curve %d",the_fader_is+1,FaderCurves[the_fader_is]+1);
     break;
     case 26://load chaser in activ dock PAS DE BACK
     break;
     case 27://play chaser in activ dock
     if( param2_is==0 || param2_is==1)
     {
     if(DockTypeIs[the_fader_is][(dock_used_by_fader_is[the_fader_is])]==11)
     {
      chaser_is_playing[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=1-param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"BACK: PLAY Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      case 1:
      sprintf(string_event,"BACK: STOP Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      default: break;
      }
     }
     else {sprintf(string_event,"BACK: No Chaser loaded in Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);}
     }
     else { sprintf(string_event,"Play Chaser entry must be 0 or 1s");}
     break;
     case 28://seek chaser in activ dock
     if(DockTypeIs[the_fader_is][(dock_used_by_fader_is[the_fader_is])]==11)
     {
     index_progression_chaser_step[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=previous_index_progression_chaser_step[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])];
     chaser_step_is[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=previous_chaser_step_is[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])];
     sprintf(string_event,"BACK: Seek At Beg Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
     }
     else {sprintf(string_event,"BACK: No Chaser loaded in Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);}
     break;
     case 29://loop chaserin activ dock
     if( param2_is==0 || param2_is==1)
     {
     if(DockTypeIs[the_fader_is][(dock_used_by_fader_is[the_fader_is])]==11)
     {
      chaser_is_in_loop[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=1-param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"BACK: LOOP ON Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      case 1:
      sprintf(string_event,"BACK: LOOP OFF Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      default: break;
      }
     }
     else {sprintf(string_event,"BACK: No Chaser loaded in Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);}
     }
     else { sprintf(string_event,"BACK: LOOP Chaser entry must be 0 or 1");}
     break;

     default:
     break;

}
break;
///////////////FIN FADERS Back///////////////////////////////////////////////////////
//MIDI back//////////////////////////////////////////////////////////////////////////
case 2: //midi send
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];
if((param1_is>=0 && param1_is<=15 ) && (param2_is>=0 && param2_is<=127))
{
//send_my_midi_note( int letype,  int lechannel, int lanote, int lavelocite, int laduree)
    switch(bangers_action[banger_num][event_num])
     {
     case 0://key on 127
     switch (cheat_key_off)
     {
     case 0:
     send_my_midi_note( 2,  param1_is, param2_is, 127, 10);//velocite / duree
     break;
     case 1:
     send_my_midi_note( 1,  param1_is, param2_is, 0, 10);//velocite / duree
     break;
     default: break;
     }
      sprintf(string_event,"BACK:key-on Ch:%d P:%d V:127",param1_is,param2_is);
     break;
     case 1://key on 0
     send_my_midi_note( 1,  param1_is, param2_is, 127, 10);//velocite / duree
     printf(string_event,"BACK:key-on Ch:%d P:%d V:0",param1_is,param2_is);
     break;
     case 2://key off
     send_my_midi_note( 1,  param1_is, param2_is, 127, 10);//velocite / duree
     sprintf(string_event,"BACK:key-on Ch:%d P:%d V:127",param1_is,param2_is);
     break;
     case 3://Ctrl-Change 127
     send_my_midi_note( 4,  param1_is, param2_is, 0, 10);//velocite / duree
     sprintf(string_event,"BACK:ctrl-change Ch:%d P:%d V:0",param1_is,param2_is);
     break;
     case 4://Ctrl-Change 0
     send_my_midi_note( 4,  param1_is, param2_is, 127, 10);//velocite / duree
     sprintf(string_event,"BACK:ctrl-change Ch:%d P:%d V:127",param1_is,param2_is);
     break;
     default:
         break;
     }
}
break;
/////////fin MIDI back///////////////////////////////////////////////////////////////////
////////////DEBUT WINDOWS BACK//////////////////////////////////////////////////////////
case 3:

param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];

    switch(bangers_action[banger_num][event_num])
     {

     case 1://seq BACK
     if(param2_is==1)
      {
      add_a_window(W_SEQUENCIEL);
      sprintf(string_event,"BACK: Sequences Window /ON");
     }
     else
     {
      substract_a_window(W_SEQUENCIEL);
      sprintf(string_event,"BACK: Sequences Window /OFF");
      }
     break;


     case 2://faders BACK
     //-50 parrapport au code des affichages
      if(param1_is>0 && param1_is<7){goto_scroll_faderspace=15;}
      else if(param1_is>6 && param1_is<13){goto_scroll_faderspace=127;}
      else if(param1_is>12 && param1_is<19){goto_scroll_faderspace=236;}
      else if(param1_is>18 && param1_is<25){goto_scroll_faderspace=345;}
      else if(param1_is>24 && param1_is<31){goto_scroll_faderspace=454;}
      else if(param1_is>30 && param1_is<37){goto_scroll_faderspace=563;}
      else if(param1_is>36 && param1_is<43){goto_scroll_faderspace=672;}
      else if(param1_is>42 && param1_is<49){goto_scroll_faderspace=782;}

     if(param2_is==1)
      {
      add_a_window(W_FADERS);
      sprintf(string_event,"BACK: Faders space/ seeing Fader %d /ON",param1_is);
      }
      else
      {
      substract_a_window(W_FADERS);
      sprintf(string_event,"BACK :Faders space/ seeing Fader Dock %d /OFF",param1_is);
      }
     break;

     case 3://minifaders
     if(param2_is==1)
      {
      add_a_window(W_MINIFADERS);
      sprintf(string_event,"BACK: MiniFaders /ON");
      }
      else
      {
      substract_a_window(W_MINIFADERS);
      sprintf(string_event,"BACK :MiniFaders space /OFF");
      }
     break;

     case 4://banger BACK
      if (param1_is>0 && param1_is<128)
      {index_banger_selected=param1_is-1;}
     if(param2_is==1)
      {
      add_a_window(W_BANGER);
      sprintf(string_event,"BACK: Banger Window/ /OFF");
      }
      else
      {
      substract_a_window(W_BANGER);
      sprintf(string_event,"BACK: Banger Window/ /ON");
      }
     break;

     case 5://audio
     if(param2_is==1)
      {
      add_a_window(W_AUDIO);
      sprintf(string_event,"BACK: Audio Window /ON");
      }
      else
      {
      substract_a_window(W_AUDIO);
      sprintf(string_event,"BACK: Audio Window /OFF");
      }
     break;

     case 6://time
     if(param2_is==1)
      {
      add_a_window(W_TIME);
      sprintf(string_event,"BACK: Audio Time /ON");
      }
      else
      {
      substract_a_window(W_TIME);
      sprintf(string_event,"BACK: Time Window /OFF");
      }
     break;

     case 7://audio
     if(param2_is==1)
      {
      add_a_window(W_PLOT);
      sprintf(string_event,"BACK: Plot Window /ON");
      }
      else
      {
      substract_a_window(W_PLOT);
      sprintf(string_event,"BACK: Plot Window /OFF");
      }
     break;

     case 8://audio
     if(param2_is==1)
      {
      add_a_window(W_LIST);
      sprintf(string_event,"BACK: LIST Window /ON");
      }
      else
      {
      substract_a_window(W_LIST);
      sprintf(string_event,"BACK: List Window /OFF");
      }
     break;

     case 9://trichro BACK
     if(param2_is==1)
      {

      dock_color_selected=previous_preset_color;

      add_a_window(W_TRICHROMY);
      load_etat_picker_dans_dockcolor(dock_color_selected);
      sprintf(string_event,"BACK: Trichowindow/ ColorPreset %d /ON",dock_color_selected);
      }
      else
      {
      dock_color_selected=previous_preset_color;
      substract_a_window(W_TRICHROMY);
      load_etat_picker_dans_dockcolor(dock_color_selected);
      sprintf(string_event,"BACK: Trichowindow/ ColorPreset %d /OFF",dock_color_selected);
      }
     break;

     case 10://videotracking BACK
     if(param2_is==1)
      {
      tracking_dock_selected=previous_preset_video;
      add_a_window(W_TRACKINGVIDEO);
      sprintf(string_event,"BACK: Tracking Video/ Tracking Dock %d, /ON",previous_preset_video);
      }
     else
     {
      tracking_dock_selected=previous_preset_video;
      substract_a_window(W_TRACKINGVIDEO);
      sprintf(string_event,"BACK: Tracking Video/ Tracking Dock %d /OFF",previous_preset_video);
      }
     break;

     case 11://chasers
      if(param2_is==1)
      {
      add_a_window(W_CHASERS);
      sprintf(string_event,"BACK: Chasers Window /ON");
      }
      else
      {
      substract_a_window(W_CHASERS);
      sprintf(string_event,"BACK: Chasers Window /OFF");
      }
     break;

     case 12://Gridplayers
     if(param2_is==1)
      {
      add_a_window(W_GRID);
      sprintf(string_event,"BACK: Gridplayers Window /ON");
      }
      else
      {
      substract_a_window(W_GRID);
      sprintf(string_event,"BACK: Gridplayers Window /OFF");
      }
     break;

     case 13://Draw
     if(param2_is==1)
      {
      add_a_window(W_DRAW);
      sprintf(string_event,"BACK: Draw Window /ON");
      }
      else
      {
      substract_a_window(W_DRAW);
      sprintf(string_event,"BACK: Draw Window /OFF");
      }
     break;


     case 14://Echo
     if(param2_is==1)
      {
      add_a_window(W_ECHO);
      sprintf(string_event,"BACK: Echo Window /ON");
      }
      else
      {
      substract_a_window(W_ECHO);
      sprintf(string_event,"BACK: Echo Window /OFF");
      }
     break;

     case 15://mover
     if(param2_is==1)
      {
      add_a_window(W_MOVER);
      sprintf(string_event,"BACK: Mover Window /ON");
      }
      else
      {
      substract_a_window(W_AUDIO);
      sprintf(string_event,"BACK: AudioMover Window /OFF");
      }
     break;

     case 16://numpad
     if(param2_is==1)
      {
      add_a_window(W_NUMPAD);
      sprintf(string_event,"BACK: NumPad Window /ON");
      }
      else
      {
      substract_a_window(W_NUMPAD);
      sprintf(string_event,"BACK: NumPadWindow /OFF");
      }
     break;

     case 17://cfg
     if(param2_is==1)
      {
      add_a_window(W_CFGMENU);
      sprintf(string_event,"BACK: CFG Window /ON");
      }
      else
      {
      substract_a_window(W_CFGMENU);
      sprintf(string_event,"BACK: CFG Window /OFF");
      }
     break;

     case 18://icat
     if(param2_is==1)
      {
      add_a_window(W_iCAT);
      sprintf(string_event,"BACK: iCAT Window /ON");
      }
      else
      {
      substract_a_window(W_iCAT);
      sprintf(string_event,"BACK: iCAT Window /OFF");
      }
     break;

     default:
     break;
     }
break;
///////////////FIN WINDOWS BACK/////////////////////////////////////////////////////////
//ALARMES BACK
case 4:
param2_is=bangers_params[banger_num][event_num][1];
switch(param2_is)
{
case 0:
add_a_window(W_ALARM);
sprintf(string_event,"BACK: Alarm /ON");
break;
case 1:
sprintf(string_THE_alarm,string_alarm[banger_num]);
index_alarm_from_banger_num=banger_num;
substract_a_window(W_ALARM);
sprintf(string_event,"BACK: Alarm /OFF");
break;
default: break;
}
break;
//AUDIO BACK/////////////////////////////////////////////////////////////////
case 5: //param 1 player param 2 action 0 1
param1_is=bangers_params[banger_num][event_num][0]-1;
param2_is=bangers_params[banger_num][event_num][1];
if(param1_is>=0 && param1_is<4)//etait 5 ! aout 2016
{
     switch(bangers_action[banger_num][event_num])
     {
     case 0: //back de clear audio player
     switch(param1_is)//lecteur
     {
     case 0:
     //rechargement du previous fichier
     sprintf(audiofile_name,audiofile_name_was[param1_is]);
     AffectSoundFile(param1_is);
     if(player_ignited[param1_is]==1)
     {
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[616+param1_is]=audio_volume_was[param1_is];
     player1->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[616+param1_is]==1){ index_send_midi_out[616+param1_is]=1;}//VOL

     player_pan[param1_is]=audio_pan_was[param1_is];
     midi_levels[620+param1_is]=audio_pan_was[param1_is];
     player1->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[620+param1_is]==1){ index_send_midi_out[620+param1_is]=1;}//PAN

     player_pitch[param1_is]=audio_pitch_was[param1_is];
     midi_levels[624+param1_is]=audio_pitch_was[param1_is];
     player1->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[624+param1_is]==1){ index_send_midi_out[624+param1_is]=1;}//PICTH

     player1->setPosition(audio_position_was[param1_is]);

     player_seek_position[param1_is]=audio_cue_in_was[param1_is];
     player_loop_out_position[param1_is]=audio_cue_out_was[param1_is];

     if(player_was_playing[param1_is]==1)
     {
     player1->play();
     player_is_playing[param1_is]=(player1->isPlaying());
     }
     if(player_was_onloop[param1_is]==1)
     {
     player1->setRepeat(true);
     player_is_onloop[param1_is]=1;
     }
     else if(player_was_onloopCue[param1_is]==1)
     {
     player1->setRepeat(true);
     player_is_onloopCue[param1_is]=1;
     }
     }
     break;
     case 1:
     //rechargement du previous fichier
     sprintf(audiofile_name,audiofile_name_was[param1_is]);
     AffectSoundFile(param1_is);
     if(player_ignited[param1_is]==1)
     {
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[616+param1_is]=audio_volume_was[param1_is];
     player2->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[616+param1_is]==1){ index_send_midi_out[616+param1_is]=1;}//VOL

     player_pan[param1_is]=audio_pan_was[param1_is];
     midi_levels[620+param1_is]=audio_pan_was[param1_is];
     player2->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[620+param1_is]==1){ index_send_midi_out[620+param1_is]=1;}//PAN

     player_pitch[param1_is]=audio_pitch_was[param1_is];
     midi_levels[624+param1_is]=audio_pitch_was[param1_is];
     player2->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[624+param1_is]==1){ index_send_midi_out[624+param1_is]=1;}//PICTH

     player2->setPosition(audio_position_was[param1_is]);

     player_seek_position[param1_is]=audio_cue_in_was[param1_is];
     player_loop_out_position[param1_is]=audio_cue_out_was[param1_is];

     if(player_was_playing[param1_is]==1)
     {
     player2->play();
     player_is_playing[param1_is]=(player2->isPlaying());
     }
     if(player_was_onloop[param1_is]==1)
     {
     player2->setRepeat(true);
     player_is_onloop[param1_is]=1;
     }
     else if(player_was_onloopCue[param1_is]==1)
     {
     player2->setRepeat(true);
     player_is_onloopCue[param1_is]=1;
     }
     }
     break;
     case 2:
     //rechargement du previous fichier
     sprintf(audiofile_name,audiofile_name_was[param1_is]);
     AffectSoundFile(param1_is);
     if(player_ignited[param1_is]==1)
     {
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[616+param1_is]=audio_volume_was[param1_is];
     player3->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[616+param1_is]==1){ index_send_midi_out[616+param1_is]=1;}//VOL

     player_pan[param1_is]=audio_pan_was[param1_is];
     midi_levels[620+param1_is]=audio_pan_was[param1_is];
     player3->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[620+param1_is]==1){ index_send_midi_out[620+param1_is]=1;}//PAN

     player_pitch[param1_is]=audio_pitch_was[param1_is];
     midi_levels[624+param1_is]=audio_pitch_was[param1_is];
     player3->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[624+param1_is]==1){ index_send_midi_out[624+param1_is]=1;}//PICTH

     player3->setPosition(audio_position_was[param1_is]);

     player_seek_position[param1_is]=audio_cue_in_was[param1_is];
     player_loop_out_position[param1_is]=audio_cue_out_was[param1_is];

     if(player_was_playing[param1_is]==1)
     {
     player3->play();
     player_is_playing[param1_is]=(player3->isPlaying());
     }
     if(player_was_onloop[param1_is]==1)
     {
     player3->setRepeat(true);
     player_is_onloop[param1_is]=1;
     }
     else if(player_was_onloopCue[param1_is]==1)
     {
     player3->setRepeat(true);
     player_is_onloopCue[param1_is]=1;
     }
     }
     break;
     case 3:
     //rechargement du previous fichier
     sprintf(audiofile_name,audiofile_name_was[param1_is]);
     AffectSoundFile(param1_is);
     if(player_ignited[param1_is]==1)
     {
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[616+param1_is]=audio_volume_was[param1_is];
     player4->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[616+param1_is]==1){ index_send_midi_out[616+param1_is]=1;}//VOL

     player_pan[param1_is]=audio_pan_was[param1_is];
     midi_levels[620+param1_is]=audio_pan_was[param1_is];
     player4->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[620+param1_is]==1){ index_send_midi_out[620+param1_is]=1;}//PAN

     player_pitch[param1_is]=audio_pitch_was[param1_is];
     midi_levels[624+param1_is]=audio_pitch_was[param1_is];
     player4->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[624+param1_is]==1){ index_send_midi_out[624+param1_is]=1;}//PICTH

     player4->setPosition(audio_position_was[param1_is]);

     player_seek_position[param1_is]=audio_cue_in_was[param1_is];
     player_loop_out_position[param1_is]=audio_cue_out_was[param1_is];

     if(player_was_playing[param1_is]==1)
     {
     player4->play();
     player_is_playing[param1_is]=(player4->isPlaying());
     }
     if(player_was_onloop[param1_is]==1)
     {
     player4->setRepeat(true);
     player_is_onloop[param1_is]=1;
     }
     else if(player_was_onloopCue[param1_is]==1)
     {
     player4->setRepeat(true);
     player_is_onloopCue[param1_is]=1;
     }
     }
     break;
     default: break;
    }


     sprintf(string_event,"BACK: Reloaded the Cleared Player %d",param1_is);
     break;
     case 1:
     //sprintf(bangers_type_action,"Load in Player");
     sprintf(audiofile_name,audiofile_name_was[param1_is]);
     AffectSoundFile(param1_is);
     sprintf(string_event,"BACK:Affected Audio %d to Player 1",param2_is);
     break;

     case 2://play pause
     //sprintf(bangers_type_action,"SetPlay Player");
     switch(param1_is)//lecteur
     {
          case 0:
          switch(param2_is)
                           {
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {player1_do_stop();
                           player_is_playing[param1_is]=(player1->isPlaying());
                           sprintf(string_event,"BACK: Player 1 STOP");}
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {player1->play();
                           player_is_playing[param1_is]=(player1->isPlaying());
                           sprintf(string_event,"BACK: Player 1 PLAY");}
                           break;
                           default: break;
                           }
          break;
          case 1:
          switch(param2_is)
                           {
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {player2_do_stop();
                           player_is_playing[param1_is]=(player2->isPlaying());
                           sprintf(string_event,"BACK: Player 2 STOP");}
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {player2->play();
                           player_is_playing[param1_is]=(player2->isPlaying());
                           sprintf(string_event,"BACK: Player 2 PLAY");}
                           break;
                           default: break;
                           }
          break;
          case 2:
          switch(param2_is)
                                      {
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {player3_do_stop();
                           player_is_playing[param1_is]=(player3->isPlaying());
                           sprintf(string_event,"BACK: Player 3 STOP");}
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {player3->play();
                           player_is_playing[param1_is]=(player3->isPlaying());
                           sprintf(string_event,"BACK: Player 3 PLAY");}
                           break;
                           default: break;
                           }
          break;
          case 3:
          switch(param2_is)
                           {
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {player4_do_stop();
                           player_is_playing[param1_is]=(player4->isPlaying());
                           sprintf(string_event,"BACK: Player 4 STOP");}
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {player4->play();
                           player_is_playing[param1_is]=(player4->isPlaying());
                           sprintf(string_event,"BACK: Player 4 PLAY");}
                           break;
                           default: break;
                           }
          break;
          default: break;
     }
     break;
     case 3:
     //BACK load and play

     switch(param1_is)//lecteur
     {
          case 0:

                           if(player_ignited[param1_is]==1)
                           {player1_do_stop();
                           player_is_playing[param1_is]=(player1->isPlaying());
                           sprintf(string_event,"BACK: Player 1 STOP");}
          break;

          case 1:

                           if(player_ignited[param1_is]==1)
                           {player2_do_stop();
                           player_is_playing[param1_is]=(player2->isPlaying());
                           sprintf(string_event,"BACK: Player 2 STOP");}
          break;
          case 2:

                           if(player_ignited[param1_is]==1)
                           {player3_do_stop();
                           player_is_playing[param1_is]=(player3->isPlaying());
                           sprintf(string_event,"BACK: Player 3 STOP");}
          break;
          case 3:

                           if(player_ignited[param1_is]==1)
                           {player4_do_stop();
                           player_is_playing[param1_is]=(player4->isPlaying());
                           sprintf(string_event,"BACK: Player 4 STOP");}
          break;
          default:
          break;
       }

     //reload
     sprintf(audiofile_name,audiofile_name_was[param1_is]);
     AffectSoundFile(param1_is);




     break;
     case 4:
//     sprintf(bangers_type_action,"SetLoop Player");

        switch(param1_is)//lecteur
     {
          case 0:
          switch(param2_is)
                           {
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player1->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"BACK: Player 1 Loop OFF");
                           }
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player1->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"BACK: Player 1 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          case 1:
          switch(param2_is)
                           {
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player2->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"BACK: Player 2 Loop OFF");
                           }
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player2->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"BACK: Player 2 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          case 2:
          switch(param2_is)
                                      {
                            case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player3->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"BACK: Player 3 Loop OFF");
                           }
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player3->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"BACK: Player 3 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          case 3:
          switch(param2_is)
                           {
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player4->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"BACK: Player 4 Loop OFF");
                           }
                           break;
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player4->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"BACK: Player 4 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          default: break;
          }

     break;
     case 5:
     //sprintf(bangers_type_action,"Seek Player");
     switch(param1_is)//lecteur
     {
          case 0:
          if(player_ignited[param1_is]==1)
          {player1->setPosition(audio_position_was[param1_is]);
          sprintf(string_event,"BACK: Player 1 SeekToZero");}
          break;
          case 1:
          if(player_ignited[param1_is]==1)
          {player3->setPosition(audio_position_was[param1_is]);
          sprintf(string_event,"BACK: Player 2 SeekToZero");}
          break;
          case 2:
          if(player_ignited[param1_is]==1)
          {player3->setPosition(audio_position_was[param1_is]);
          sprintf(string_event,"BACK: Player 3 SeekToZero");}
          break;
          case 3:
          if(player_ignited[param1_is]==1)
          {player4->setPosition(audio_position_was[param1_is]);
          sprintf(string_event,"BACK: Player 4 SeekToZero");}
          break;
          default: break;
      }
     break;
     case 6:
     //sprintf(bangers_type_action,"SetVolume Player");
     if(player_ignited[param1_is]==1 && param2_is<128 && param2_is>=0)
     {
     switch(param1_is)
     {
     case 0:
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[616]=audio_volume_was[param1_is];
     player1->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[616]==1){ index_send_midi_out[616]=1;}//vol
     sprintf(string_event,"BACK: Player 1 SetVolume at %d", audio_volume_was[param1_is]);
     break;
     case 1:
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[617]=audio_volume_was[param1_is];
     player2->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[617]==1){ index_send_midi_out[617]=1;}//vol
     sprintf(string_event,"BACK: Player 2 SetVolume at %d", audio_volume_was[param1_is]);
     break;
     case 2:
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[618]=audio_volume_was[param1_is];
     if(midi_send_out[618]==1){ index_send_midi_out[618]=1;}//vol
     player3->setVolume(((float)player_niveauson[param1_is])/127);
     sprintf(string_event,"BACK: Player 3 SetVolume at %d", audio_volume_was[param1_is]);
     break;
     case 3:
     player_niveauson[param1_is]=audio_volume_was[param1_is];
     midi_levels[619]=audio_volume_was[param1_is];
     if(midi_send_out[619]==1){ index_send_midi_out[619]=1;}//vol
     player4->setVolume(((float)player_niveauson[param1_is])/127);
     sprintf(string_event,"BACK: Player 4 SetVolume at %d", audio_volume_was[param1_is]);
     break;
     default: break;
     }
     }

     break;
     case 7:
     //sprintf(bangers_type_action,"Set Cue Player");
      if(player_ignited[param1_is]==1)
      {
     switch(param1_is)
     {
     case 0://PLAYER 1
          switch(param2_is)
          {
           case 1:
           player1->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"BACK: Player 1 CUE OFF");
           break;
           case 0:
           player1->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"BACK: Player 1 CUE ON");
           break;
           default: break;
           }
     break;
     case 1://PLAYER 2
          switch(param2_is)
          {
           case 1:
           player2->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"BACK: Player 2 CUE OFF");
           break;
           case 0:
           player2->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"BACK: Player 2 CUE ON");
           break;
           default: break;
           }
     break;
     case 2://PLAYER 3
          switch(param2_is)
          {
           case 1:
           player3->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"BACK: Player 3 CUE OFF");
           break;
           case 0:
           player3->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"BACK: Player 3 CUE ON");
           break;
           default: break;
           }
     break;
     case 3://PLAYER 4
          switch(param2_is)
          {
           case 1:
           player4->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"BACK: Player 4 CUE OFF");
           break;
           case 0:
           player4->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"Player 4 CUE ON");
           break;
           default: break;
           }
     break;
     default: break;
     }
     }
     break;
     case 8:
     //sprintf(bangers_type_action,"Seek to CueIn Pl.");
      if(player_ignited[param1_is]==1 && param2_is==1)//christoph 03/12/14
     {
         switch(param1_is)
     {

       case 0://PLAYER 1
       player1->setPosition(audio_position_was[param1_is]);
       sprintf(string_event,"BACK: Player 1 SeekToCueIn");
       break;
       case 1://PLAYER 2
       player2->setPosition(audio_position_was[param1_is]);
       sprintf(string_event,"BACK: Player 2 SeekToCueIn");
       break;
       case 2://PLAYER 3
       player3->setPosition(audio_position_was[param1_is]);
       sprintf(string_event,"BACK: Player 3 SeekToCueIn");
       break;
       case 3://PLAYER 4
       player4->setPosition(audio_position_was[param1_is]);
       sprintf(string_event,"BACK: Player 4 SeekToCueIn");
       break;
       default: break;
       }
     }
     break;
     case 9:
     //sprintf(bangers_type_action,"SetPan Player");
     if(player_ignited[param1_is]==1 && param2_is<128 && param2_is>=0)
     {
     param2_is=audio_pan_was[param1_is];
     switch(param1_is)
     {
     case 0:
     player_pan[param1_is]=param2_is;
     midi_levels[620]=param2_is;
     player1->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[620]==1){ index_send_midi_out[620]=1;}//PAN
     sprintf(string_event,"BACK: Player 1 SetPan at %d",param2_is);
     break;
     case 1:
     player_pan[param1_is]=param2_is;
     midi_levels[621]=param2_is;
     player2->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[621]==1){ index_send_midi_out[621]=1;}//PAN
     sprintf(string_event,"BACK: Player 2 SetPan at %d",param2_is);
     break;
     case 2:
     player_pan[param1_is]=param2_is;
     midi_levels[622]=param2_is;
     player3->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[622]==1){ index_send_midi_out[622]=1;}//PAN
     sprintf(string_event,"BACK: Player 3 SetPan at %d",param2_is);
     break;
     case 3:
     player_pan[param1_is]=param2_is;
     midi_levels[623]=param2_is;
     player4->setPan(((float)player_pan[param1_is])/127);
     if(midi_send_out[623]==1){ index_send_midi_out[623]=1;}//PAN
     sprintf(string_event,"BACK: Player 4 SetPan at %d",param2_is);
     break;
     default: break;
     }
     }
     break;
     case 10:
     //sprintf(bangers_type_action,"SetPitch Player");
     if(player_ignited[param1_is]==1 && param2_is<128 && param2_is>=0)
     {
      param2_is=audio_pitch_was[param1_is];
     switch(param1_is)
     {
     case 0:
     player_pitch[param1_is]=param2_is;
     midi_levels[624]=param2_is;
     player1->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[624]==1){ index_send_midi_out[624]=1;}//PICTH
     sprintf(string_event,"BACK: Player 1 SetPitch at %d",param2_is);
     break;
     case 1:
     player_pitch[param1_is]=param2_is;
     midi_levels[625]=param2_is;
     player2->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[625]==1){ index_send_midi_out[625]=1;}//PICTH
     sprintf(string_event,"BACK: Player 2 SetPitch at %d",param2_is);
     break;
     case 2:
     player_pitch[param1_is]=param2_is;
     midi_levels[626]=param2_is;
     player3->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[626]==1){ index_send_midi_out[626]=1;}//PICTH
     sprintf(string_event,"BACK: Player 3 SetPitch at %d",param2_is);
     break;
     case 3:
     player_pitch[param1_is]=param2_is;
     midi_levels[627]=param2_is;
     player4->setPitchShift(((float)player_pitch[param1_is])/127);
     if(midi_send_out[627]==1){ index_send_midi_out[627]=1;}//PICTH
     sprintf(string_event,"BACK: Player 4 SetPitch at %d",param2_is);
     break;
     default: break;
     }
     }
     break;
     case 11:
     //sprintf(bangers_type_action,"SetMidiOut Player");
     midi_send_out[616+param1_is]=toggle(param2_is);
     midi_send_out[620+param1_is]=toggle(param2_is);
     midi_send_out[624+param1_is]=toggle(param2_is);
     switch(midi_send_out[616+param1_is])
     {
     case 0:
     sprintf(string_event,"BACK: Player %d SetMidiOut OFF",param1_is);
     break;
     case 1:
     sprintf(string_event,"BACK: Player %d SetMidiOut ON",param1_is);
     break;
     default: break;
     }
     break;
     }
}
break;
default: break;
sprintf(string_Last_Order,">> Banged %d Event %d %s", banger_num+1, event_num+1, string_event);

}

}
return(0);

}




int back_up_fader_if_a_fader_inside(int banger_num)
{
 for (int u=0;u<6;u++)
 {
     if(bangers_type[banger_num][u]==1)
     {
     store_state_of_fader_before_bang((bangers_params[banger_num][u][0]-1));
     }

 }
 return(0);
}



int do_send_bang()//remise à zéro du bang concerné pour le lancement depuis une mémoire
{
if(index_banger_is_on==1 && (Banger_Memoire[position_preset]>0 && Banger_Memoire[position_preset]<128))
{
int banger_to_send=Banger_Memoire[position_preset]-1;
back_up_fader_if_a_fader_inside(banger_to_send);
sprintf(string_Last_Order,">> Banging %d from mem %d.%d",Banger_Memoire[position_preset],position_preset/10,position_preset%10);
start_time_for_banger[banger_to_send]=actual_time;

//reset du banger concerné
for (int o=0;o<6;o++)//reset des évènements
{event_sended[banger_to_send][o]=0;}
bang_is_sended[banger_to_send]=0;//reset de l event si il a été lancé dejà une fois
}

return(0);
}






int Bang_event(int banger_num, int event_num)
{
int param1_is=0;
int param2_is=0;
int the_fader_is=0;
int the_icatpage_is=0;
int numgridpl=0;
int gimick_param1_is=0;//variable clean sans constraiint
//sab 02/03/2014 unused var int numgrid=0;
//sab 02/03/2014 unused var int numstep=0;
switch (bangers_type[banger_num][event_num])
{
case 0:
break;
case 1: //fader
the_fader_is=bangers_params[banger_num][event_num][0]-1;
param2_is=bangers_params[banger_num][event_num][1];
if(the_fader_is>=0 && the_fader_is<core_user_define_nb_faders)
{
     switch(bangers_action[banger_num][event_num])
     {
     case 0://lock
     FaderLocked[the_fader_is]=bangers_params[banger_num][event_num][1];
     do_stock_fadersstate(0,0,1,0,0);
     switch(FaderLocked[the_fader_is])
     {
     case 0:
     FaderLocked[the_fader_is]=0;
     //remise à plat du niveau
     Fader[the_fader_is]=(unsigned char)((((float)(StateOfFaderBeforeLock[the_fader_is]))/255)*locklevel);
     midi_levels[the_fader_is]=(int)(((float)Fader[the_fader_is])/2);
     sprintf(string_event,"UNLOCKED Fader %d",the_fader_is+1);
     break;
     case 1:
     FaderLocked[the_fader_is]=1;
     StateOfFaderBeforeLock[the_fader_is]=Fader[the_fader_is];
     if(StateOfFaderBeforeLock[the_fader_is]==255){LockFader_is_FullLevel[the_fader_is]=1;}
     else if(StateOfFaderBeforeLock[the_fader_is]<255){LockFader_is_FullLevel[the_fader_is]=0;}
     lfo_cycle_is_on[the_fader_is]=0;//rajout 0.7.6
     lfo_mode_is[the_fader_is]=0;
     sprintf(string_event,"LOCKED Fader %d",the_fader_is+1);
     break;
     default:
        break;
     }
     break;
     case 1://up
     do_stock_fadersstate(0,0,0,1,0);
     start_time_for_delays[the_fader_is]=actual_time;
     switch(param2_is)
     {
     case 0:
     lfo_mode_is[the_fader_is]=0;
     sprintf(string_event,"UP Fader %d OFF",the_fader_is+1);
     break;
     case 1:
     if(FaderLocked[the_fader_is]==0 || LockFader_is_FullLevel[the_fader_is]==1)//rajout lock 0.7.6)//down
     {
     lfo_mode_is[the_fader_is]=1;
     faders_in_float[the_fader_is]=Fader[the_fader_is];
     sprintf(string_event,"UP Fader %d ON",the_fader_is+1);
     }
     break;
     default:
        break;
     }
     lfo_cycle_is_on[the_fader_is]=0;
     break;
     case 2://down
     do_stock_fadersstate(0,0,0,1,0);
     start_time_for_delays[the_fader_is]=actual_time;
     switch(param2_is)
     {
     case 0:
     lfo_mode_is[the_fader_is]=0;
     sprintf(string_event,"DOWN Fader %d OFF",the_fader_is+1);
     break;
     case 1:
     if(FaderLocked[the_fader_is]==0 || LockFader_is_FullLevel[the_fader_is]==1)//rajout lock 0.7.6)//down
     {
     lfo_mode_is[the_fader_is]=2;
     faders_in_float[the_fader_is]=Fader[the_fader_is];
     sprintf(string_event,"DOWN Fader %d ON",the_fader_is+1);
     }
     break;
     default:
        break;
     }
     lfo_cycle_is_on[the_fader_is]=0;
     break;
     case 3://saw
     start_time_for_delays[the_fader_is]=actual_time;
     do_stock_fadersstate(0,0,0,1,0);
     switch(param2_is)
     {
     case 0:
     lfo_mode_is[the_fader_is]=0;
     lfo_cycle_is_on[the_fader_is]=0;
     sprintf(string_event,"SAW Fader %d OFF",the_fader_is+1);
     break;
     case 1:
     if(FaderLocked[the_fader_is]==0 || LockFader_is_FullLevel[the_fader_is]==1)//rajout lock 0.7.6)//down
     {
     lfo_cycle_is_on[the_fader_is]=1;
     lfo_mode_is[the_fader_is]=0;
     lfo_running_is_upward[the_fader_is]=1;
     sprintf(string_event,"SAW Fader %d ON",the_fader_is+1);
     }
     break;
     default:
     break;
     }
     break;
     case 4://to prev dock
     do_stock_fadersstate(0,0,0,1,0);
      switch(param2_is)
     {
     case 0:
     lfo_do_next_step[the_fader_is][0]=0;
     sprintf(string_event,"PREV DOCK Fader %d OFF",the_fader_is+1);
     break;
     case 1:
     lfo_do_next_step[the_fader_is][0]=1;lfo_do_next_step[the_fader_is][1]=0;
     sprintf(string_event,"PREV DOCK Fader %d ON",the_fader_is+1);
     break;
     default:
     break;
     }
     break;
     case 5://to next dock
     do_stock_fadersstate(0,0,0,1,0);
     switch(param2_is)
     {
     case 0:
     lfo_do_next_step[the_fader_is][1]=0;
     sprintf(string_event,"NEXT DOCK Fader %d OFF",the_fader_is+1);
     break;
     case 1:
     lfo_do_next_step[the_fader_is][1]=1;lfo_do_next_step[the_fader_is][0]=0; ;
     sprintf(string_event,"NEXT DOCK Fader %d ON",the_fader_is+1);
     break;
     default:
     break;
     }
     break;
     case 6://up down
     do_stock_fadersstate(0,0,0,1,0);
     switch(param2_is)
     {
     case 0:
     lfo_cycle_steps[the_fader_is]=0;
     sprintf(string_event,"CYCLE Fader %d OFF",the_fader_is+1);
     break;
     case 1:
     lfo_cycle_steps[the_fader_is]=1;
     sprintf(string_event,"CYCLE Fader %d ON",the_fader_is+1);
     break;
     default:
     break;
     }
     break;
     case 7://set dock  looped
     do_stock_fadersstate(0,0,0,0,1);
     dock_selected_for_record=detect_dock_used(the_fader_is);//utilise en temporaire
     switch(param2_is)
     {
     case 0:
     is_dock_for_lfo_selected[the_fader_is][dock_selected_for_record]=0;
     sprintf(string_event,"DOCK LOOPED Fader %d OFF",the_fader_is+1);
     break;
     case 1:
     is_dock_for_lfo_selected[the_fader_is][dock_selected_for_record]=1;
     sprintf(string_event,"DOCK LOOPED Fader %d ON",the_fader_is+1);
     break;
     default:
     break;
     }
     break;
     case 8://set all looped
     do_stock_fadersstate(0,0,0,0,1);
      switch(param2_is)
      {
      case 0:
      for(int p=0;p<6;p++)
      {
      is_dock_for_lfo_selected[the_fader_is][p]=0;
      }
      sprintf(string_event,"ALL LOOPED Fader %d OFF",the_fader_is+1);
      break;
      case 1:
      for(int p=0;p<core_user_define_nb_docks;p++)
      {
      is_dock_for_lfo_selected[the_fader_is][p]=1;
      }
      sprintf(string_event,"ALL LOOPED Fader %d ON",the_fader_is+1);
      break;
      default:
      break;
      }
     break;
     case 9://set dock selected is
     if(param2_is>0 && param2_is<7)
     {
      DockIsSelected[the_fader_is][(param2_is-1)]=1;
      Unselect_other_docks(the_fader_is, (param2_is-1));
     }
     sprintf(string_event,"SELECT DOCK %d Fader %d",param2_is,the_fader_is+1);
     break;
     case 10://set LFO at
     if(param2_is>=0 && param2_is<=127)
     {
     do_stock_fadersstate(0,1,0,0,0);
     do_stock_fadersstate(0,1,0,0,0);
     lfo_speed[the_fader_is]=param2_is;
     midi_levels[196+the_fader_is]=param2_is;
     index_send_midi_out[196+the_fader_is]=1;
     if(DockTypeIs[the_fader_is][dock_used_by_fader_is[the_fader_is]]==12)//enchassement Grid si slave
     {
     asservissement_gridplayer(the_fader_is,dock_used_by_fader_is[the_fader_is]);
     }
     }
     sprintf(string_event,"SET SPEED %d Fader %d",param2_is,the_fader_is+1);
     break;
     case 11://set Fader At
     int niv_transforme;
     switch( dmx_view)
     {
      case 0:
       if(param2_is>=0 && param2_is<=100)
      {
      niv_transforme=(int)(((float)(param2_is))*2.55)+1;
      if(param2_is==0){niv_transforme=0;}
      if(param2_is==100){niv_transforme=255;}
      }
      break;
      case 1:
      if(param2_is>=0 && param2_is<=255)
      {
      niv_transforme=param2_is;
      }
      break;
      default:
      break;
     }
     do_stock_fadersstate(1,0,0,0,0);
     fader_set_level(the_fader_is, niv_transforme);
     if(lfo_mode_is[the_fader_is]==1 || lfo_mode_is[the_fader_is]==2 || lfo_cycle_is_on[the_fader_is]==1)
     {
     lfo_mode_is[the_fader_is]=0; lfo_mode_is[the_fader_is]=0; lfo_cycle_is_on[the_fader_is]=0;
     }
     //rafraichissement DChannel
     if(DockTypeIs[the_fader_is][dock_used_by_fader_is[the_fader_is]]==10){index_fader_is_manipulated[the_fader_is]=1;}
     sprintf(string_event,"SET LEVEL %d Fader %d",param2_is,the_fader_is+1);
     break;

     case 12://end pos pour auto mouvement
          int lStopP;
          PreviousLevelStopPos[the_fader_is]=LevelStopPos[the_fader_is];
          switch(dmx_view)
          {
           case 0:
            lStopP=(int)((((float)param2_is) *2.55)+1);//+1 pour arrondir le %
           break;
           case 1:
            lStopP=param2_is;
           break;
           default:
           break;
          }
          if (lStopP>=0 && lStopP<=255)
          {
          StopPosOn[the_fader_is]=1;LevelStopPos[the_fader_is]=lStopP;
          do_light_setpos[the_fader_is]=1;
          sprintf(string_event,"SET ENDPOS %d Fader %d",param2_is,the_fader_is+1);
          }
     break;

     case 13://on off end pos
     if(param2_is==0 || param2_is==1)
     {
     ActionnateStopOn[the_fader_is]=param2_is;
     do_light_setpos[the_fader_is]=1;
     switch(param2_is)
     {
     case 0:
     sprintf(string_event,"ENDPOS OFF Fader %d",the_fader_is+1);
     break;
     case 1:
     sprintf(string_event,"ENDPOS ON Fader %d",the_fader_is+1);
     break;
     default:
     break;
     }
     }
     break;
     case 14://paste to stage output of faders
      for (int dc=1;dc<514;dc++)
      {
      if(FaderDoDmx[the_fader_is][dc]>bufferSaisie[dc])
      {bufferSaisie[dc]=FaderDoDmx[the_fader_is][dc];}
      }
      Fader[the_fader_is]= 0;
      midi_levels[the_fader_is]= 0;
      index_send_midi_out[the_fader_is]=1;
       sprintf(string_event,"PASTED Fader %d",the_fader_is+1);
     break;
     case 15://set midi out
     switch(param2_is)
      {
      case 0:
      midi_send_out[the_fader_is]=0;
       sprintf(string_event,"MIDI OUT Fader %d OFF",the_fader_is+1);
      break;
      case 1:
      midi_send_out[the_fader_is]=1;
       sprintf(string_event,"MIDI OUT Fader %d ON",the_fader_is+1);
      break;
      default:
      break;
      }
     break;
     //ALL AT
     case 16://faders off
           do_stock_fadersstate(1,0,0,0,0);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           Fader[p]=0;
           midi_levels[p]=0;
           index_send_midi_out[p]=1;
           }
     break;
     case 17://speed at zero
           do_stock_fadersstate(0,1,0,0,0);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           lfo_speed[p]=64;
           midi_levels[196+p]=64;
           index_send_midi_out[196+p]=1;
           }
     break;
     case 18://lock off
           do_stock_fadersstate(0,0,1,0,0);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           FaderLocked[p]=0;
           }
     break;
     case 19://lfo off
           do_stock_fadersstate(0,0,0,1,0);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           lfo_mode_is[p]=0;//no lfo
           lfo_cycle_is_on[p]=0;//saw
           lfo_cycle_steps[p]=0;
           lfo_do_next_step[p][0]=0;
           lfo_do_next_step[p][1]=0;
           }
     break;
     case 20://loop off
           do_stock_fadersstate(0,0,0,0,1);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           for(int d=0;d<core_user_define_nb_docks;d++)
           {
           is_dock_for_lfo_selected[p][d]=0;
           }
           }
     break;
     case 21://ALL
           do_stock_fadersstate(1,1,1,1,1);
            for (int p=0;p<core_user_define_nb_faders;p++)
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
     break;
     case 22://midi out
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           midi_send_out[p]=0;//faders
           }
     break;
     case 23://recall
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
     break;
     case 24://LOCKS PRESET
     param1_is=bangers_params[banger_num][event_num][0]-1;
     switch(param2_is)
     {
      case 0:
      for (int ipo=0;ipo<8;ipo++)
      {lock_preset[ipo]=0;}
      lock_preset[param1_is]=0;
      break;
      case 1:
      for (int ipo=0;ipo<8;ipo++)
      {lock_preset[ipo]=0;}
      lock_preset[param1_is]=1;
      break;
      default:
      break;
     }
     break;
     case 25://assign curve
     before_bang_FaderCurves[the_fader_is]=FaderCurves[the_fader_is];//pour go back
     if(param2_is>0 && param2_is<=16)
     {
     FaderCurves[the_fader_is]=param2_is-1;
     }
     else
     {
     param2_is=0;
     FaderCurves[the_fader_is]=param2_is;
     }
     sprintf(string_event,"Assigned Fader %d Curve %d",the_fader_is+1,param2_is);
     break;
     case 26://load chaser in activ dock
     param1_is=bangers_params[banger_num][event_num][0]-1;
     param2_is=bangers_params[banger_num][event_num][1]-1;
     if(param1_is>0 && param1_is<49 && param2_is>0 && param2_is<129)
     {
     ChaserAffectedToDck[param1_is][(dock_used_by_fader_is[param1_is])]=param2_is;
     DockTypeIs[param1_is][(dock_used_by_fader_is[param1_is])]=11;
     view_chaser_affected_to_fader[param2_is][0]=param1_is;
     view_chaser_affected_to_fader[param2_is][1]=dock_used_by_fader_is[param1_is];
     chaser_step_is[param2_is]=chaser_begin_step_is[param2_is];
     sprintf(string_event,"LoadChaser %d in Fader %d Dock %d ", param2_is+1,the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
     }
     else { sprintf(string_event,"LoadChaser in Fader >> Invalid entry");}
     break;
     case 27://play chaser in activ dock
     if( param2_is==0 || param2_is==1)
     {
     if(DockTypeIs[the_fader_is][(dock_used_by_fader_is[the_fader_is])]==11)
     {
      chaser_is_playing[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"STOP Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      case 1:
      chaser_start_time[ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])]]=actual_time;
      //bug olivier marche arriere arrière ligne
      if(chaser_step_is[ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])]]<0){chaser_step_is[ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])]]=0;}
      else if(chaser_step_is[ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])]]>35){chaser_step_is[ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])]]=35;}
      sprintf(string_event,"PLAY Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      default: break;
      }
     }
     else {sprintf(string_event,"No Chaser loaded in Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);}
     }
     else { sprintf(string_event,"Play Chaser entry must be 0 or 1s");}
     break;
     case 28://seek chaser in activ dock
     if(DockTypeIs[the_fader_is][(dock_used_by_fader_is[the_fader_is])]==11)
     {
     previous_chaser_step_is[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=chaser_step_is[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])];
     previous_index_progression_chaser_step[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=index_progression_chaser_step[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])];
     chaser_seek_at_beg((ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])]));
     sprintf(string_event,"Seek At Beg Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
     }
     else {sprintf(string_event,"No Chaser loaded in Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);}
     break;
     case 29://loop chaserin activ dock
     if( param2_is==0 || param2_is==1)
     {
     if(DockTypeIs[the_fader_is][(dock_used_by_fader_is[the_fader_is])]==11)
     {
      chaser_is_in_loop[(ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])])]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"LOOP OFF Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      case 1:
      sprintf(string_event,"LOOP ON Chaser %d in Fader %d Dock %d ",ChaserAffectedToDck[the_fader_is][(dock_used_by_fader_is[param1_is])], the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      default: break;
      }
     }
     else {sprintf(string_event,"No Chaser loaded in Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);}
     }
     else { sprintf(string_event,"LOOP Chaser entry must be 0 or 1");}
     break;
     case 30://autolaunch chaser
      if( param2_is==0 || param2_is==1)
     {
     if(DockTypeIs[the_fader_is][(dock_used_by_fader_is[the_fader_is])]==11)
     {
     autolaunch[the_fader_is]=param2_is;
     }
     }
     switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Autolaunch OFF Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      case 1:
      sprintf(string_event,"Autolaunch ON  Fader %d Dock %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1);
      break;
      default: break;
      }
     break;
     case 31://"Fader: Set as DCH.");
     if( param2_is>0 && param2_is<513)
     {
     DockTypeIs[the_fader_is][dock_used_by_fader_is[param1_is]]=10;
     FaderDirectChan[the_fader_is][dock_used_by_fader_is[param1_is]]=param2_is;
     sprintf(string_event,"Fader %d Dock %d as Direct CH %d ", the_fader_is+1,dock_used_by_fader_is[param1_is]+1, param2_is);
     }
     break;
     case 32://"Fader: Set CH Full");
     if( param2_is>1 && param2_is<513)
     {
     DockTypeIs[the_fader_is][dock_used_by_fader_is[param1_is]]=0;
     FaderDockContains[the_fader_is][dock_used_by_fader_is[param1_is]][param2_is]=255;
     sprintf(string_event,"Fader %d Dock %d CH %d At Full", the_fader_is+1,dock_used_by_fader_is[param1_is]+1, param2_is);
     }
     break;
     case 33://"Fader: Set CH At 0");
     if( param2_is>1 && param2_is<513)
     {
     DockTypeIs[the_fader_is][dock_used_by_fader_is[param1_is]]=0;
     FaderDockContains[the_fader_is][dock_used_by_fader_is[param1_is]][param2_is]=0;
     sprintf(string_event,"Fader %d Dock %d CH %d At Full", the_fader_is+1,dock_used_by_fader_is[param1_is]+1, param2_is);
     }
     break;
     case 34://"Damper On/Off"
     if( param2_is==0 ||  param2_is==1)
     {
     if(fader_damper_is_on[the_fader_is]==0)
        {
        Fader_dampered[the_fader_is].fix_all_damper_state_value(Fader[the_fader_is]);
        Fader_dampered[the_fader_is].set_target_val(Fader[the_fader_is]);
        index_fader_is_manipulated[the_fader_is]=1;
        sprintf(string_event,"Fader %d Damper Off", the_fader_is+1);
        }
     else
        {sprintf(string_event,"Fader %d Damper On", the_fader_is+1);}
     fader_damper_is_on[the_fader_is]=param2_is;
     }
     break;
     case 35://"Damper SetDecay"
     if( param2_is>=0 &&  param2_is<=127)
     {
     Fader_dampered[the_fader_is].set_damper_decay((((float)param2_is)/127));
     sprintf(string_event,"Fader %d Damper Decay at %d level", the_fader_is+1, param2_is);
     }
     break;
     case 36://"Damper SetDelta"
     if( param2_is>=0 &&  param2_is<=127)
     {
     Fader_dampered[the_fader_is].set_damper_dt((((float)param2_is)/127));
     sprintf(string_event,"Fader %d Damper Delta at %d level", the_fader_is+1, param2_is);
     }
     break;
     case 37://"Damper Mode"
     if( param2_is>=0 &&  param2_is<=max_damper_mode)
     {
     Fader_dampered[the_fader_is].set_damper_mode(param2_is);
     sprintf(string_event,"Fader %d Damper Mode is %d", the_fader_is+1, param2_is);
     }
     break;
     case 38://Dock --
     for(int i=0;i<6;i++)
     {
      if(DockIsSelected[the_fader_is][i]==1)
      {
          DockIsSelected[the_fader_is][i]=0;
          if(i>0){DockIsSelected[the_fader_is][i-1]=1;}
          else if(i==0){DockIsSelected[the_fader_is][5]=1;}
          break;
      }
     }
     sprintf(string_event,"Fader %d Dock --", the_fader_is+1);
     break;
     case 39://Dock ++
     for(int i=0;i<6;i++)
     {
      if(DockIsSelected[the_fader_is][i]==1)
      {
          DockIsSelected[the_fader_is][i]=0;
          if(i<5){DockIsSelected[the_fader_is][i+1]=1;}
          else if(i==5){DockIsSelected[the_fader_is][0]=1;}
          break;
      }
     }
     sprintf(string_event,"Fader %d Dock ++", the_fader_is+1);
     break;
     case 40://FX MODE
         if(param2_is>=0 && param2_is<=5)
         // 0 NORMAL / 1 OFF RENDERING / 2 SUBSTRACT / 3 ADDITIF / 4 SCREEN / 5 EXCLUSION
         {
         fader_mode_with_buffers[the_fader_is]=param2_is;
         switch(param2_is)
             {
                 case 0:
                    sprintf(string_event,"Fader %d FX Normal", the_fader_is+1);
                 break;
                 case 1:
                    sprintf(string_event,"Fader %d FX OFF", the_fader_is+1);
                 break;
                 case 2:
                    sprintf(string_event,"Fader %d FX Substract", the_fader_is+1);
                 break;
                 case 3:
                    sprintf(string_event,"Fader %d FX Add", the_fader_is+1);
                 break;
                 case 4:
                    sprintf(string_event,"Fader %d FX Screen", the_fader_is+1);
                 break;
                 case 5:
                    sprintf(string_event,"Fader %d FX Exclusion", the_fader_is+1);
                 break;
                 default:
                 break;
             }
         }



     break;
     case 41://Buffer is
         if(param2_is>1){param2_is=1;}
         fader_fx_route[the_fader_is]=param2_is;// 1 Buffer séquenciel / 0 Buffer faders
         switch(fader_fx_route[the_fader_is])
         {
         case 0:
              sprintf(string_event,"Fader %d render to Faders", the_fader_is+1);
         break;
         case 1:
              sprintf(string_event,"Fader %d render to Cuelist", the_fader_is+1);
         break;
         }
     default:
     break;
    }
}
break;
///////////////FIN FADERS///////////////////////////////////////////////////////
//MIDI//////////////////////////////////////////////////////////////////////////
case 2: //midi send
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];
if(bangers_action[banger_num][event_num]<=23)//calibration CH max 15 et PITCH max 127 pour envoyer des arguments au midiclock rate
//if((param1_is>=0 && param1_is<=15 ) && (param2_is>=0 && param2_is<=127))
{
if(param1_is>15){param1_is=15;}
if(param2_is>127){param1_is=127;}
}
//send_my_midi_note( int letype,  int lechannel, int lanote, int lavelocite, int laduree)
switch(bangers_action[banger_num][event_num])
     {
     case 0://key on 127
      send_my_midi_note( 1,  param1_is, param2_is, 127, 10);//velocite / duree
      sprintf(string_event,"KEY-ON Ch:%d P:%d V:127",param1_is,param2_is);
     break;
     case 1://key on 0
      send_my_midi_note( 1,  param1_is, param2_is, 0, 10);//velocite / duree
      sprintf(string_event,"KEY-ON Ch:%d P:%d V:0",param1_is,param2_is);
     break;
     case 2://key off
     send_my_midi_note( 2,  param1_is, param2_is, 127, 10);//velocite / duree
     sprintf(string_event,"KEY-OFF Ch:%d P:%d V:127",param1_is,param2_is);
     break;
     case 3://Ctrl-Change 127
     send_my_midi_note( 4,  param1_is, param2_is, 127, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:%d P:%d V:127",param1_is,param2_is);
     break;
     case 4://Ctrl-Change 0
     send_my_midi_note( 4,  param1_is, param2_is, 0, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:0 P:%d V:%d",param1_is,param2_is);
     break;
     case 5://Ctrl-Change Ch0
     send_my_midi_note( 4,  0, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:0 P:%d V:%d",param1_is,param2_is);
     break;
     case 6://Ctrl-Change Ch1
     send_my_midi_note( 4,  1, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:1 P:%d V:%d",param1_is,param2_is);
     break;
     case 7://Ctrl-Change Ch2
     send_my_midi_note( 4,  2, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:2 P:%d V:%d",param1_is,param2_is);
     break;
     case 8://Ctrl-Change Ch3
     send_my_midi_note( 4,  3, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:3 P:%d V:%d",param1_is,param2_is);
     break;
     case 9://Ctrl-Change Ch4
     send_my_midi_note( 4,  4, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:4 P:%d V:%d",param1_is,param2_is);
     break;
     case 10://Ctrl-Change Ch5
     send_my_midi_note( 4,  5, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:5 P:%d V:%d",param1_is,param2_is);
     break;
     case 11://Ctrl-Change Ch6
     send_my_midi_note( 4,  6, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:6 P:%d V:%d",param1_is,param2_is);
     break;
     case 12://Ctrl-Change Ch7
     send_my_midi_note( 4,  7, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:7 P:%d V:%d",param1_is,param2_is);
     break;
     case 13://Ctrl-Change Ch8
     send_my_midi_note( 4,  8, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:8 P:%d V:%d",param1_is,param2_is);
     break;
     case 14://Ctrl-Change Ch9
     send_my_midi_note( 4,  9, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:9 P:%d V:%d",param1_is,param2_is);
     break;
     case 15://Ctrl-Change Ch10
     send_my_midi_note( 4,  10, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:10 P:%d V:%d",param1_is,param2_is);
     break;
     case 16://Ctrl-Change Ch11
     send_my_midi_note( 4,  11, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:11 P:%d V:%d",param1_is,param2_is);
     break;
     case 17://Ctrl-Change Ch12
     send_my_midi_note( 4,  12, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:12 P:%d V:%d",param1_is,param2_is);
     break;
     case 18://Ctrl-Change Ch13
     send_my_midi_note( 4,  13, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:13 P:%d V:%d",param1_is,param2_is);
     break;
     case 19://Ctrl-Change Ch14
     send_my_midi_note( 4,  14, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:14 P:%d V:%d",param1_is,param2_is);
     break;
     case 20://Ctrl-Change Ch15
     send_my_midi_note( 4,  15, param1_is, param2_is, 10);//velocite / duree
     sprintf(string_event,"CTRL-CHANGE Ch:15 P:%d V:%d",param1_is,param2_is);
     break;
     case 21://mid out des pastilles faders et speed
     if(param2_is==0)
     {
     index_global_midi_send_on_faders=param2_is;
     sprintf(string_event,"Midi Out on Faders LFos OFF");
     }
     else{
     index_global_midi_send_on_faders=1;
     sprintf(string_event,"Midi Out on Faders LFos ON");
     }
     set_all_faders_midi_out(index_global_midi_send_on_faders);
     do_light_midi_send_on_faders=1;
     break;
     case 22://midi out sur faders chasers
     if(param2_is==0)
     {
     for (int p=1023;p<1047;p++)
           {
           midi_send_out[p]=0;//chaser tracks
           }
     refresh_midi_chasers=0;set_refresh_mode_for_chaser(0);
      sprintf(string_event,"Midi Out Chasers Tracks OFF");
     }
     else
     {refresh_midi_chasers=1;set_refresh_mode_for_chaser(1);
          for (int p=1023;p<1047;p++)
           {
           midi_send_out[p]=1;//chaser tracks
           }
     sprintf(string_event,"Midi Out Chasers Tracks ON");
     }
     break;
     case 23://refresh et send de toutes les commandes
     for(int i=0;i<3072;i++)
     {
     index_send_midi_out[i]=1;
     }
     sprintf(string_event,"Resend all Midi states !");
     break;
     case 24:
     index_midi_clock_on=1;
     sprintf(string_event,"MidiClock ON !");
     break;
     case 25:
     index_midi_clock_on=0;
     sprintf(string_event,"MidiClock OFF !");
     break;
     case 26:
     if(param1_is>0)
     {
     midi_BPM=param1_is;
     ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
     install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);
     sprintf(string_event,"MidiClock at RATE %d BPM", midi_BPM);
     }
     break;
     case 27:
     midi_send_type_message(typeStart);
     sprintf(string_event,"Midi Msg START");
     break;
     case 28:
     midi_send_type_message(typeStop);
     sprintf(string_event,"Midi Msg STOP");
     break;
     case 29:
     midi_send_type_message(typeContinue);
     sprintf(string_event,"Midi Msg CONTINUE");
     break;
     case 30:
     midi_send_program_change(param1_is,param2_is);
     sprintf(string_event,"Midi Prg Change %d CH %d",param2_is, param1_is);
     break;
     default:
     break;
     }
break;
/////////fin MIDI///////////////////////////////////////////////////////////////////
////////////DEBUT WINDOWS//////////////////////////////////////////////////////////
case 3:
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];

switch(bangers_action[banger_num][event_num])
{
     case 1://seq
     if(param2_is==0)
      {
      substract_a_window(W_SEQUENCIEL);
      sprintf(string_event,"Sequences Window /OFF");
      }
      else
      {
      add_a_window(W_SEQUENCIEL);
      sprintf(string_event,"Sequences Window /ON");
      }
     break;

     case 2://faders
     //-50 parrapport au code des affichages
      if(param1_is>0 && param1_is<7){scroll_faderspace=15;}
      else if(param1_is>6 && param1_is<13){scroll_faderspace=127;}
      else if(param1_is>12 && param1_is<19){scroll_faderspace=236;}
      else if(param1_is>18 && param1_is<25){scroll_faderspace=345;}
      else if(param1_is>24 && param1_is<31){scroll_faderspace=454;}
      else if(param1_is>30 && param1_is<37){scroll_faderspace=563;}
      else if(param1_is>36 && param1_is<43){scroll_faderspace=672;}
      else if(param1_is>42 && param1_is<49){scroll_faderspace=782;}

     if(param2_is==0)
      {
      substract_a_window(W_FADERS);
      sprintf(string_event,"Faders space/ seeing Fader %d /OFF",param1_is);
      }
      else
      {
      add_a_window(W_FADERS);
      sprintf(string_event,"Faders space/ seeing Fader Dock %d /ON",param1_is);
      }
     break;

     case 3://minifaders
      if(param2_is==0)
      {
      substract_a_window(W_MINIFADERS);
      sprintf(string_event,"MiniFaders /OFF");
      }
      else
      {
      add_a_window(W_MINIFADERS);
      sprintf(string_event,"MiniFaders /ON");
      }
     break;

     case 4://banger
      if (param1_is>0 && param1_is<128)
      {index_banger_selected=param1_is-1;}
      if(param2_is==0)
      {
      substract_a_window(W_BANGER);
      sprintf(string_event,"Banger Window/ OFF");
      }
      else
      {
      add_a_window(W_BANGER);
      sprintf(string_event,"Banger Window/ ON");
      }
     break;

     case 5://audio
     if(param2_is==0)
      {
      substract_a_window(W_AUDIO);
      sprintf(string_event,"Audio Window /OFF");
      }
      else
      {
      add_a_window(W_AUDIO);
      sprintf(string_event,"Audio Window /ON");
      }
     break;

    case 6://Time
    if(param2_is==0)
      {
      substract_a_window(W_TIME);
      sprintf(string_event,"Time Window /OFF");
      }
      else
      {
      add_a_window(W_TIME);
      sprintf(string_event,"Time Window /ON");
      }
     break;


    case 7://PLOT
    if(param2_is==0)
      {
      substract_a_window(W_PLOT);
      sprintf(string_event,"Plot Window /OFF");
      }
      else
      {
      add_a_window(W_PLOT);
      sprintf(string_event,"Plot Window /ON");
      }
     break;

    case 8://LIST
    if(param2_is==0)
      {
      substract_a_window(W_LIST);
      sprintf(string_event,"List Window /OFF");
      }
      else
      {
      add_a_window(W_LIST);
      sprintf(string_event,"List Window /ON");
      }
     break;


     case 9://trichro
      if(param2_is==0)
      {
      previous_preset_color=dock_color_selected;
      dock_color_selected=param1_is-1;
      if(dock_color_selected<0 || dock_color_selected>7)
      {
      dock_color_selected=0;
      }
      substract_a_window(W_TRICHROMY);
      load_etat_picker_dans_dockcolor(dock_color_selected);
      sprintf(string_event,"Trichowindow/ ColorPreset %d /OFF",param1_is);
      }
      else
      {
      previous_preset_color=dock_color_selected;
      dock_color_selected=param1_is-1;
      if(dock_color_selected<0 || dock_color_selected>7)
      {
      dock_color_selected=0;
      }
      add_a_window(W_TRICHROMY);
      load_etat_picker_dans_dockcolor(dock_color_selected);
      sprintf(string_event,"Trichrowindow/ ColorPreset %d /ON",param1_is);
      }
     break;

     case 10://videotracking
     if(param2_is==0)
      {
      previous_preset_video=tracking_dock_selected;
      tracking_dock_selected=param1_is-1;
      if(tracking_dock_selected<0 || tracking_dock_selected>5)
      {
      tracking_dock_selected=0;
      }
      substract_a_window(W_TRACKINGVIDEO);
      sprintf(string_event,"Tracking Video/ Tracking Dock %d, /OFF",param1_is);
      }
      else
      {
      previous_preset_video=tracking_dock_selected;
      tracking_dock_selected=param1_is-1;
      if(tracking_dock_selected<0 || tracking_dock_selected>5)
      {
      tracking_dock_selected=0;
      }
      add_a_window(W_TRACKINGVIDEO);
      sprintf(string_event,"Tracking Video/ Tracking Dock %d /ON",param1_is);
      }
     break;

     case 11://chasers
     if(param1_is>0 && param1_is<core_user_define_nb_chasers-1)
     {chaser_selected=param1_is-1;}
     if(param2_is==0)
      {
      substract_a_window(W_CHASERS);
      sprintf(string_event,"Chaser Window /OFF / Ch.Sel: %d", param1_is);
      }
     else
     {
      add_a_window(W_CHASERS);
      sprintf(string_event,"Chaser Window /ON / Ch.Sel: %d", param1_is);
      }
     break;

     case 12://gridplayers
     if(param2_is==0)
      {
      substract_a_window(W_GRID);
      sprintf(string_event,"GridPlayers /OFF");
      }
     else
      {
      add_a_window(W_GRID);
      sprintf(string_event,"GridPlayers /ON");
      }
     break;


     case 13://draw
     if(param2_is==0)
      {
      substract_a_window(W_DRAW);
      sprintf(string_event,"Draw Window /OFF");
      }
     else
     {
      add_a_window(W_DRAW);
      if(param1_is>0 && param1_is<=6)
      {
      draw_preset_selected=param1_is;
      }
      sprintf(string_event,"Draw Window /ON");
     }
     break;

     case 14://echo
     if(param2_is==0)
      {
      substract_a_window(W_ECHO);
      sprintf(string_event,"Echo Window /OFF");
     }
     else
     {
      add_a_window(W_ECHO);
      if(param1_is>0 && param1_is<=24)
      {
      echo_selected=param1_is;
      }
      sprintf(string_event,"Echo Window /ON");
      }
     break;


     case 15://MOver
     if(param2_is==0)
      {
      substract_a_window(W_MOVER);
      sprintf(string_event,"Mover Window /OFF");
     }
     else
     {
      add_a_window(W_MOVER);
      sprintf(string_event,"Mover Window /ON");
      }
     break;


     case 16://numpad
     if(param2_is==0)
      {
      substract_a_window(W_NUMPAD);
      sprintf(string_event,"NumPad Window /OFF");
     }
     else
     {
      add_a_window(W_NUMPAD);
      sprintf(string_event,"NumPad Window /ON");
      }
     break;


     case 17://cfg
     if(param2_is==0)
      {
      substract_a_window(W_CFGMENU);
      sprintf(string_event,"CFG Window /OFF");
     }
     else
     {
      add_a_window(W_CFGMENU);
      sprintf(string_event,"CFG Window /ON");
      }
     break;


     case 18://icat
     if(param2_is==0)
      {
      substract_a_window(W_iCAT);
      sprintf(string_event,"iCAT Window /OFF");
     }
     else
     {
      add_a_window(W_iCAT);
      sprintf(string_event,"iCAT Window /ON");
      }
     break;


     default:
     break;
     }
break;
///////////////FIN WINDOWS/////////////////////////////////////////////////////////
//ALARMES
case 4:
param2_is=bangers_params[banger_num][event_num][1];
switch(param2_is)
{
case 0:
substract_a_window(W_ALARM);
sprintf(string_event,"Alarm /OFF");
break;
case 1:
sprintf(string_THE_alarm,string_alarm[banger_num]);
index_alarm_from_banger_num=banger_num;
add_a_window(W_ALARM);
sprintf(string_event,"Alarm /ON");
break;
default:
break;
}
break;

//AUDIO/////////////////////////////////////////////////////////////////////////
case 5: //param 1 player param 2 action 0 1
param1_is=bangers_params[banger_num][event_num][0]-1;
param2_is=bangers_params[banger_num][event_num][1];
if(param1_is>=0 && param1_is<4)//etait 5 ! aout 2016
{
     switch(bangers_action[banger_num][event_num])
     {
     case 0://clear player
     if(player_ignited[param1_is]==1)
     {
     //archivage
     sprintf(audiofile_name_was[param1_is],sound_files[param1_is]);
     audio_volume_was[param1_is]= player_niveauson[param1_is];
     audio_pan_was[param1_is]=player_pan[param1_is];
     audio_pitch_was[param1_is]=player_pitch[param1_is];
     player_was_playing[param1_is]=  player_is_playing[param1_is];
     player_was_onloopCue[param1_is]= player_is_onloopCue[param1_is];
     player_was_onloop[param1_is]= player_is_onloop[param1_is];
     audio_position_was[param1_is]=position_of_file_in_player[param1_is];
     audio_cue_in_was[param1_is]=player_seek_position[param1_is];
     audio_cue_out_was[param1_is]=player_loop_out_position[param1_is];
     //action
     player_pan[param1_is]=64;
     player_pitch[param1_is]=64;
     player_niveauson[param1_is]=64;

      switch (param1_is )
      {
      case 0:
      player1_do_stop();
      player_is_playing[param1_is]=(player1->isPlaying());
      player1->setPitchShift((((float)player_pitch[param1_is])/64));
      player1->setPan(((float)(player_pan[param1_is]-64))/63);
      player1->setRepeat(false);
      player1->setVolume(((float)player_niveauson[param1_is])/127);
      break;
      case 1:
      player2_do_stop();
      player_is_playing[param1_is]=(player2->isPlaying());
      player2->setPitchShift((((float)player_pitch[param1_is])/64));
      player2->setPan(((float)(player_pan[param1_is]-64))/63);
      player2->setRepeat(false);
      player2->setVolume(((float)player_niveauson[param1_is])/127);
      break;
      case 2:
      player3_do_stop();
      player_is_playing[param1_is]=(player3->isPlaying());
      player3->setPitchShift((((float)player_pitch[param1_is])/64));
      player3->setPan(((float)(player_pan[param1_is]-64))/63);
      player3->setRepeat(false);
      player3->setVolume(((float)player_niveauson[param1_is])/127);
      break;
      case 3:
      player4_do_stop();
      player_is_playing[param1_is]=(player4->isPlaying());
      player4->setPitchShift((((float)player_pitch[param1_is])/64));
      player4->setPan(((float)(player_pan[param1_is]-64))/63);
      player4->setRepeat(false);
      player4->setVolume(((float)player_niveauson[param1_is])/127);
      break;
      default: break;
      }

     strcpy(audiofile_name,"");
     AffectSoundFile(param1_is);
     player_ignited[param1_is]=0;
     player_is_onloop[param1_is]=0;
     midi_levels[616+param1_is]=player_niveauson[param1_is];
     if(midi_send_out[616+param1_is]==1){ index_send_midi_out[616+param1_is]=1;}//vol
     midi_levels[620+param1_is]=player_pan[param1_is];
     if(midi_send_out[620+param1_is]==1){ index_send_midi_out[620+param1_is]=1;}//pan
     midi_levels[624+param1_is]=player_pitch[param1_is];
     if(midi_send_out[624+param1_is]==1){ index_send_midi_out[624+param1_is]=1;}//pitch

     sprintf(string_event,"Cleared Player %d",param1_is);
     }
     break;
     case 1:
     sprintf(audiofile_name_was[param1_is],sound_files[param1_is]);
     //sprintf(bangers_type_action,"Load in Player");
     sprintf(audiofile_name,list_audio_files[param2_is]);
     //debug christoph 11/12/14
     audiofile_selected=param2_is;
     //
     AffectSoundFile(param1_is);

     player_seek_position[param1_is]=audiofile_cue_in_out_pos[param2_is][0];
     player_loop_out_position[param1_is]=audiofile_cue_in_out_pos[param2_is][1];
     sprintf(string_event,"Affected Audio %d to Player %d",param2_is,param1_is);
     break;

     case 2://play pause
     //sprintf(bangers_type_action,"SetPlay Player");
     switch(param1_is)//lecteur
     {
          case 0:
          switch(param2_is)
                           {
                           case 0:
                           if(player_ignited[param1_is]==1){player1_do_stop();sprintf(string_event,"Player 1 STOP");}
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1){player1->play();sprintf(string_event,"Player 1 PLAY");}
                           break;
                           default: break;
                           }
          break;
          case 1:
          switch(param2_is)
                           {
                           case 0:
                           if(player_ignited[param1_is]==1){player2_do_stop();sprintf(string_event,"Player 2 STOP");}
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1){player2->play();sprintf(string_event,"Player 2 PLAY");}
                           break;
                           default: break;
                           }
          break;
          case 2:
          switch(param2_is)
                                      {
                           case 0:
                           if(player_ignited[param1_is]==1){player3_do_stop();sprintf(string_event,"Player 3 STOP");}
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1){player3->play();sprintf(string_event,"Player 3 PLAY");}
                           break;
                           default: break;
                           }
          break;
          case 3:
          switch(param2_is)
                           {
                           case 0:
                           if(player_ignited[param1_is]==1){player4_do_stop();sprintf(string_event,"Player 4 STOP");}
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1){player4->play();sprintf(string_event,"Player 4 PLAY");}
                           break;
                           default: break;
                           }
          break;
          default: break;
     }
     break;

     case 3:
     //load and play
     sprintf(audiofile_name_was[param1_is],sound_files[param1_is]);
     //sprintf(bangers_type_action,"Load in Player");
     sprintf(audiofile_name,list_audio_files[param2_is]);
    //debug christoph 11/12/14
     audiofile_selected=param2_is;
     //
     AffectSoundFile(param1_is);
     player_seek_position[param1_is]=audiofile_cue_in_out_pos[param2_is][0];
     player_loop_out_position[param1_is]=audiofile_cue_in_out_pos[param2_is][1];
     sprintf(string_event,"Affected Audio %d to Player %d",param2_is,param1_is);

     switch(param1_is)//lecteur
     {
          case 0:
          if(player_ignited[param1_is]==1){player1->play();sprintf(string_event,"Player 1 PLAY");}
          break;
          case 1:
          if(player_ignited[param1_is]==1){player2->play();sprintf(string_event,"Player 2 PLAY");}
          break;
          case 2:
          if(player_ignited[param1_is]==1){player3->play();sprintf(string_event,"Player 3 PLAY");}
          break;
          case 3:
          if(player_ignited[param1_is]==1){player4->play();sprintf(string_event,"Player 4 PLAY");}
          break;
          default: break;
     }

     break;
     case 4:
//     sprintf(bangers_type_action,"SetLoop Player");

        switch(param1_is)//lecteur
     {
          case 0:
          switch(param2_is)
                           {
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player1->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"Player 1 Loop OFF");
                           }
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player1->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"Player 1 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          case 1:
          switch(param2_is)
                           {
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player2->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"Player 2 Loop OFF");
                           }
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player2->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"Player 2 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          case 2:
          switch(param2_is)
                          {
                            case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player3->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"Player 3 Loop OFF");
                           }
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player3->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"Player 3 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          case 3:
          switch(param2_is)
                           {
                           case 0:
                           if(player_ignited[param1_is]==1)
                           {
                           player4->setRepeat(false);
                           player_is_onloop[param1_is]=0;
                           sprintf(string_event,"Player 4 Loop OFF");
                           }
                           break;
                           case 1:
                           if(player_ignited[param1_is]==1)
                           {
                           player4->setRepeat(true);
                           player_is_onloop[param1_is]=1;
                           sprintf(string_event,"Player 4 Loop ON");
                           }
                           break;
                           default: break;
                           }
          break;
          default: break;
          }

     break;
     case 5:
     //sprintf(bangers_type_action,"Seek Player");
     switch(param1_is)//lecteur
     {
          case 0:
          if(player_ignited[param1_is]==1)
          {audio_position_was[param1_is]=position_of_file_in_player[param1_is];
          player1->setPosition(0); sprintf(string_event,"Player 1 SeekToZero");}
          break;
          case 1:
          if(player_ignited[param1_is]==1)
          {audio_position_was[param1_is]=position_of_file_in_player[param1_is];
          player2->setPosition(0); sprintf(string_event,"Player 2 SeekToZero");}
          break;
          case 2:
          if(player_ignited[param1_is]==1)
          {audio_position_was[param1_is]=position_of_file_in_player[param1_is];
          player3->setPosition(0); sprintf(string_event,"Player 3 SeekToZero");}
          break;
          case 3:
          if(player_ignited[param1_is]==1)
          {audio_position_was[param1_is]=position_of_file_in_player[param1_is];
          player4->setPosition(0); sprintf(string_event,"Player 4 SeekToZero");}
          break;
          default: break;
      }
      midi_show_flash_seektouch[param1_is]=1;
     break;
     case 6:
     //sprintf(bangers_type_action,"SetVolume Player");
     if(player_ignited[param1_is]==1 && param2_is<128 && param2_is>=0)
     {
     audio_volume_was[param1_is]=player_niveauson[param1_is];
     switch(param1_is)
     {
     case 0:
     player_niveauson[param1_is]=param2_is;
     midi_levels[616]=param2_is;
     player1->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[616]==1){ index_send_midi_out[616]=1;}//vol
     sprintf(string_event,"Player 1 SetVolume at %d", param2_is);
     break;
     case 1:
     player_niveauson[param1_is]=param2_is;
     midi_levels[617]=param2_is;
     player2->setVolume(((float)player_niveauson[param1_is])/127);
     if(midi_send_out[617]==1){ index_send_midi_out[617]=1;}//vol
     sprintf(string_event,"Player 2 SetVolume at %d", param2_is);
     break;
     case 2:
     player_niveauson[param1_is]=param2_is;
     midi_levels[618]=param2_is;
     if(midi_send_out[618]==1){ index_send_midi_out[618]=1;}//vol
     player3->setVolume(((float)player_niveauson[param1_is])/127);
     sprintf(string_event,"Player 3 SetVolume at %d", param2_is);
     break;
     case 3:
     player_niveauson[param1_is]=param2_is;
     midi_levels[619]=param2_is;
     if(midi_send_out[619]==1){ index_send_midi_out[619]=1;}//vol
     player4->setVolume(((float)player_niveauson[param1_is])/127);
     sprintf(string_event,"Player 4 SetVolume at %d", param2_is);
     break;
     default: break;
     }
     }
     break;
     case 7:
     //sprintf(bangers_type_action,"Set Cue Player");
     if(player_ignited[param1_is]==1)
     {
     switch(param1_is)
     {
     case 0://PLAYER 1
          switch(param2_is)
          {
           case 0:
           player1->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"Player 1 CUE OFF");
           break;
           case 1:
           player1->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"Player 1 CUE ON");
           break;
           default: break;
           }
     break;
     case 1://PLAYER 2
          switch(param2_is)
          {
           case 0:
           player2->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"Player 2 CUE OFF");
           break;
           case 1:
           player2->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"Player 2 CUE ON");
           break;
           default: break;
           }
     break;
     case 2://PLAYER 3
          switch(param2_is)
          {
           case 0:
           player3->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"Player 3 CUE OFF");
           break;
           case 1:
           player3->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"Player 3 CUE ON");
           break;
           default: break;
           }
     break;
     case 3://PLAYER 4
          switch(param2_is)
          {
           case 0:
           player4->setRepeat(false);
           player_is_onloopCue[param1_is]=0;
           sprintf(string_event,"Player 4 CUE OFF");
           break;
           case 1:
           player4->setRepeat(true);
           player_is_onloopCue[param1_is]=1;
           sprintf(string_event,"Player 4 CUE ON");
           break;
           default: break;
           }
     break;
     default: break;
     }
     }
     break;
     case 8:
     if(player_ignited[param1_is]==1 && param2_is==1)
     {
     audio_position_was[param1_is]=position_of_file_in_player[param1_is];
     //sprintf(bangers_type_action,"Seek to CueIn Pl.");
     switch(param1_is)
     {
       case 0://PLAYER 1
       player1->setPosition(player_seek_position[param1_is]);
       sprintf(string_event,"Player 1 SeekToCueIn");
       break;
       case 1://PLAYER 2
       player2->setPosition(player_seek_position[param1_is]);
       sprintf(string_event,"Player 2 SeekToCueIn");
       break;
       case 2://PLAYER 3
       player3->setPosition(player_seek_position[param1_is]);
       sprintf(string_event,"Player 3 SeekToCueIn");
       break;
       case 3://PLAYER 4
       player4->setPosition(player_seek_position[param1_is]);
       sprintf(string_event,"Player 4 SeekToCueIn");
       break;
       default: break;
       }
     }
     break;
     case 9:
     //sprintf(bangers_type_action,"SetPan Player");
     if(player_ignited[param1_is]==1 && param2_is<128 && param2_is>=0)
     {
     audio_pan_was[param1_is]=player_pan[param1_is];
     switch(param1_is)
     {
     case 0:
     player_pan[param1_is]=param2_is;
     midi_levels[620]=param2_is;
     player1->setPan(((float)player_pan[param1_is]-64)/63);
     if(midi_send_out[620]==1){ index_send_midi_out[620]=1;}//PAN
     sprintf(string_event,"Player 1 SetPan at %d",param2_is);
     break;
     case 1:
     player_pan[param1_is]=param2_is;
     midi_levels[621]=param2_is;
     player2->setPan(((float)player_pan[param1_is]-64)/63);
     if(midi_send_out[621]==1){ index_send_midi_out[621]=1;}//PAN
     sprintf(string_event,"Player 2 SetPan at %d",param2_is);
     break;
     case 2:
     player_pan[param1_is]=param2_is;
     midi_levels[622]=param2_is;
     player3->setPan(((float)player_pan[param1_is]-64)/63);
     if(midi_send_out[622]==1){ index_send_midi_out[622]=1;}//PAN
     sprintf(string_event,"Player 3 SetPan at %d",param2_is);
     break;
     case 3:
     player_pan[param1_is]=param2_is;
     midi_levels[623]=param2_is;
     player4->setPan(((float)player_pan[param1_is]-64)/63);
     if(midi_send_out[623]==1){ index_send_midi_out[623]=1;}//PAN
     sprintf(string_event,"Player 4 SetPan at %d",param2_is);
     break;
     default: break;
     }
     }
     break;
     case 10:
     //sprintf(bangers_type_action,"SetPitch Player");
     if(player_ignited[param1_is]==1 && param2_is<128 && param2_is>=0)
     {
     audio_pitch_was[param1_is]=player_pitch[param1_is];
     switch(param1_is)
     {
     case 0:
     player_pitch[param1_is]=param2_is;
     midi_levels[624]=param2_is;
     player1->setPitchShift(((float)player_pitch[param1_is])/64);
     if(midi_send_out[624]==1){ index_send_midi_out[624]=1;}//PICTH
     sprintf(string_event,"Player 1 SetPitch at %d",param2_is);
     break;
     case 1:
     player_pitch[param1_is]=param2_is;
     midi_levels[625]=param2_is;
     player2->setPitchShift(((float)player_pitch[param1_is])/64);
     if(midi_send_out[625]==1){ index_send_midi_out[625]=1;}//PICTH
     sprintf(string_event,"Player 2 SetPitch at %d",param2_is);
     break;
     case 2:
     player_pitch[param1_is]=param2_is;
     midi_levels[626]=param2_is;
     player3->setPitchShift(((float)player_pitch[param1_is])/64);
     if(midi_send_out[626]==1){ index_send_midi_out[626]=1;}//PICTH
     sprintf(string_event,"Player 3 SetPitch at %d",param2_is);
     break;
     case 3:
     player_pitch[param1_is]=param2_is;
     midi_levels[627]=param2_is;
     player4->setPitchShift(((float)player_pitch[param1_is])/64);
     if(midi_send_out[627]==1){ index_send_midi_out[627]=1;}//PICTH
     sprintf(string_event,"Player 4 SetPitch at %d",param2_is);
     break;
     default: break;
     }
     }
     break;
     case 11:     //"Prev.Tr. Player");
     audiofile_selected=player_has_file_coming_from_pos[param1_is]-1;
     if(audiofile_selected<1){audiofile_selected=1;}
     sprintf(audiofile_name,list_audio_files[audiofile_selected]);
     if(strcmp (audiofile_name,"")!=0)
     {
     AffectSoundFile(param1_is);
     }
     break;
     case 12:     //"Next.Tr. Player");
     audiofile_selected=player_has_file_coming_from_pos[param1_is]+1;
     if(audiofile_selected>=127){audiofile_selected=126;}
     sprintf(audiofile_name,list_audio_files[audiofile_selected]);
     if(strcmp (audiofile_name,"")!=0)
     {
     AffectSoundFile(param1_is);
     }
     break;
     case 13:     //"AutoLoad Player");
     if(param2_is==0 || param2_is==1)
     {
     audio_autoload[param1_is]=param2_is;
     }
     switch(param2_is)
     {
     case 0:
     sprintf(string_event,"Player %d Autoload OFF",param1_is);
     break;
     case 1:
     sprintf(string_event,"Player %d Autoload ON",param1_is);
     break;
     default: break;
     }
     break;
     case 14:     //"AutoPause Player");
     if(param2_is==0 || param2_is==1)
     {
     audio_autopause[param1_is]=param2_is;
     }
     break;
     case 15:
     //sprintf(bangers_type_action,"SetMidiOut Player");
     midi_send_out[616+param1_is]=param2_is;
     midi_send_out[620+param1_is]=param2_is;
     midi_send_out[624+param1_is]=param2_is;
     switch(param2_is)
     {
     case 0:
     sprintf(string_event,"Player %d SetMidiOut OFF",param1_is);
     break;
     case 1:
     sprintf(string_event,"Player %d SetMidiOut ON",param1_is);
     break;
     default: break;
     }
     break;
     default:
     break;
     }
}
break;//fin audio

//SEQUENCES/////////////////////////////////////////////////////////////////////


case 6:
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];
memoire_asked_in_bang=(param1_is*10)+param2_is;
switch(bangers_action[banger_num][event_num])
     {
     case 0:  //ontsage mem
     if(MemoiresExistantes[memoire_asked_in_bang]==1)
     {
     position_onstage= memoire_asked_in_bang;
     refresh_mem_onstage(position_onstage);
     detect_mem_before_one();
     detect_mem_preset();
     refresh_mem_onpreset(position_preset);
     sprintf(string_event,"load onstage mem %d.%d",position_onstage/10,position_onstage%10);
     refresh_integrated_gridplayer1();
     }
     else {sprintf(string_event,"mem %d.%d doesn't exist !",position_onstage/10,position_onstage%10);}
     break;
     case 1: //preset mem
     if(MemoiresExistantes[memoire_asked_in_bang]==1)
     {
     position_preset= memoire_asked_in_bang;
     refresh_mem_onpreset(position_preset);
     ratio_X1X2_together=ratio_cross_manuel[position_preset];
     sprintf(string_event,"load in preset mem %d.%d",position_preset/10,position_preset%10);
     refresh_integrated_gridplayer1();
     }
     else {sprintf(string_event,"Mem %d.%d doesn't exist !",position_preset/10,position_preset%10);}
     break;
     case 2://set speed at
     if(param1_is>=0 && param1_is<128)
     {
     crossfade_speed=param1_is;
     sprintf(string_event,"set speed at %d ",param1_is);
     }
     else  sprintf(string_event,"speed not good !!! ");
     break;
     case 3://Set Link
     if(param1_is>0){param1_is=1;}
     switch(param1_is)
     {
     case 0:
     index_link_is_on=0;
      sprintf(string_event,"Link off ");
     break;
     case 1:
     index_link_is_on=1;
      sprintf(string_event,"Link on ");
     break;
     default: break;
     }
     break;
     case 4://Set Banger mode sequenciel
     if(param1_is>0){param1_is=1;}
     switch(param1_is)
     {
     case 0:
     index_banger_is_on=0;
     sprintf(string_event,"Banger off ");
     break;
     case 1:
     index_banger_is_on=1;
     sprintf(string_event,"Banger on ");
     break;
     default: break;
     }
     break;
     case 5://refresh stage
     refresh_stage();
     sprintf(string_event,"Stage reloaded ");
     break;
     case 6://refresh preset
     refresh_mem_onpreset(position_preset);
      sprintf(string_event,"Preset reloaded ");
     break;
     case 7:// Go
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
     break;
     case 8:// blind mode
     if(param2_is<2)
      {index_blind= param2_is;}
     break;
     default:
     break;
     }
break;

/////CHASERS/////////////
case 7://chaser
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];

switch(bangers_action[banger_num][event_num])
{
      case 0://call num chaser in chaser window
      if(param1_is>0 && param1_is<core_user_define_nb_chasers)
      {
      chaser_selected=param1_is-1;
      sprintf(string_event,"Chaser %d in Ch.Window",param1_is);
      }
      break;
      case 1://play chaser
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && (param2_is==0 || param2_is==1))
      {
      chaser_is_playing[param1_is-1]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Chaser %d PLAY OFF",param1_is);
      break;
      case 1:
      sprintf(string_event,"Chaser %d PLAY ON",param1_is);
      chaser_start_time[param1_is-1]=actual_time;
      //bug olivier marche arriere arrière ligne
      if(chaser_step_is[param1_is-1]<0){chaser_step_is[param1_is-1]=0;}
      else if(chaser_step_is[param1_is-1]>35){chaser_step_is[param1_is-1]=35;}
      break;
      default: break;
      }
      }
      break;
      case 2://seek chaser
      if(param1_is>0 && param1_is<core_user_define_nb_chasers)
      {
      chaser_seek_at_beg(param1_is-1);
      sprintf(string_event,"Chaser %d SEEK at beg",param1_is);
      }
      break;
      case 3://loop chaser
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && (param2_is==0 || param2_is==1))
      {
      chaser_is_in_loop[param1_is-1]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Chaser %d LOOP OFF",param1_is);
      break;
      case 1:
      sprintf(string_event,"Chaser %d LOOP ON",param1_is);
      break;
      default: break;
      }
      }
      break;
      case 4://way chaser
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && (param2_is==0 || param2_is==1))
      {
      chaser_way[param1_is-1]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Chaser %d FORWARD way",param1_is);
      break;
      case 1:
      sprintf(string_event,"Chaser %d BACKWARD way",param1_is);
      break;
      default: break;
      }
      }
      break;
      case 5://aller retour chaser
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && (param2_is==0 || param2_is==1))
      {
      chaser_aller_retour[param1_is-1]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Chaser %d OFF aller-retour",param1_is);
      break;
      case 1:
      sprintf(string_event,"Chaser %d ON aller-retour",param1_is);
      break;
      default: break;
      }
      }
      break;
      case 6://timemode chaser_time_mode
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && (param2_is==0 || param2_is==1))
      {
      chaser_time_mode[param1_is-1]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Chaser %d Time-STD",param1_is);
      break;
      case 1:
      sprintf(string_event,"Chaser %d TimeJoin ",param1_is);
      break;
      default: break;
      }
      }
      break;
      case 7://slaviness index_slave_chaser_to_accelerometre
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && (param2_is==0 || param2_is==1))
      {
      index_slave_chaser_to_accelerometre[param1_is-1]=param2_is;
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Chaser %d Slaviness OFF",param1_is);
      break;
      case 1:
      sprintf(string_event,"Chaser %d Slaviness ON",param1_is);
      break;
      default: break;
      }
      }
      break;
      case 8://Beg P  chaser_begin_step_is
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && param2_is>0 && param2_is<37 && param2_is<=chaser_end_step_is[param1_is-1])
      {
      chaser_begin_step_is[param1_is-1]=param2_is-1;
      sprintf(string_event,"Chaser %d Set BegStep %d",param1_is,param2_is);
      }
      break;
      case 9://End P  chaser_end_step_is
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && param2_is>0 && param2_is<37 && param2_is>=chaser_begin_step_is[param1_is-1])
      {
      chaser_end_step_is[param1_is-1]=param2_is-1;
      sprintf(string_event," Chaser %d Set EndStep %d",param1_is,param2_is);
      }
      break;
      case 10://Position  chaser_step_is
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && param2_is>0 && param2_is<37)
      {
      chaser_step_is[param1_is-1]=param2_is-1;
      sprintf(string_event,"Chaser %d StepPosition Is %d ",param1_is,param2_is);
      }
      break;
      case 11://toogle a track
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && param2_is>0 && param2_is<25)
      {
      track_is_on[param1_is-1][param2_is-1]=toggle(track_is_on[param1_is-1][param2_is-1]);
      switch(track_is_on[param1_is-1][param2_is-1])
      {
      case 0:
      sprintf(string_event,"Chaser %d Track %d OFF",param1_is,param2_is);
      break;
      case 1:
      sprintf(string_event,"Chaser %d Track %d ON ",param1_is,param2_is);
      break;
      default: break;
      }
      }
      break;
      case 12://ALL ON OFF
      if(param1_is>0 && param1_is<core_user_define_nb_chasers)
      {
      chaser_select_all_track(param1_is-1);
      sprintf(string_event,"Chaser %d ALL ON/OFF ",param1_is);
      }
      break;
      case 13://INV ON OFF
      if(param1_is>0 && param1_is<core_user_define_nb_chasers)
      {
      chaser_select_inv_track(param1_is-1);
      sprintf(string_event,"Chaser %d INV ON/OFF ",param1_is);
      }
      break;
      case 14://ALL OFF
      if(param1_is>0 && param1_is<core_user_define_nb_chasers)
      {
      chaser_select_off_all_track(param1_is-1);
      sprintf(string_event,"Chaser %d ALL ON/OFF ",param1_is);
      }
      break;
      case 15://call preset
      if(param1_is>0 && param1_is<core_user_define_nb_chasers && param2_is>0 && param2_is<5)
      {
      chaser_load_from_preset(param1_is-1, param2_is-1);
      sprintf(string_event,"Chaser %d ON/OFF Preset %d",param1_is,param2_is);
      }
      break;
      case 16://level track
      if(param1_is>0 && param1_is<core_user_define_nb_tracks_per_chasers && param2_is>=0 && param2_is<core_user_define_nb_chasers)
      {
      track_level[chaser_selected][param1_is-1]=param2_is;
      sprintf(string_event,"Selected Chaser track %d at Level %d",param1_is,param2_is);
      }
      break;
      default: break;
      }
break;
case 8://minifaders
the_fader_is=bangers_params[banger_num][event_num][0]-1;
param2_is=bangers_params[banger_num][event_num][1];
if(param1_is>=0 && param1_is<core_user_define_nb_faders && param2_is>=0 && param2_is<=1 )
{
switch(bangers_action[banger_num][event_num])
{
      case 0://"Select Num."
      minifaders_selected[the_fader_is]=param2_is;
      if(param2_is==1)      sprintf(string_event,"Sel.Minifader %d ON",the_fader_is+1);
      else if (param2_is==0)      sprintf(string_event,"Sel.Minifader %d OFF",the_fader_is+1);
      break;
      case 1://"Select All"
      if(param2_is==0)
       {for(int i=0;i<core_user_define_nb_faders;i++)
       {minifaders_selected[i]=0;}sprintf(string_event,"Unselected ALL Minifaders"); }
      else if(param2_is==1)
       {for(int i=0;i<core_user_define_nb_faders;i++)
       {minifaders_selected[i]=1;}sprintf(string_event,"Selected ALL Minifaders"); }
      break;
      case 2://"Selected Flash"
      for(int tt=0;tt<core_user_define_nb_faders;tt++)
      {
      if( minifaders_selected[tt]==1)
      {FaderIsFlash[tt]=param2_is;}
      }
      switch(param2_is)
      {
      case 0:
      sprintf(string_event,"Selected Minif. FLASH OFF");
      break;
      case 1:
      sprintf(string_event,"Selected Minif. FLASH ON");
      break;
      default: break;
      }
      break;
      case 3://"Selected Lock"
      do_action_on_selected_minifaders(1);
      sprintf(string_event,"Toggled LOCK Minif. Selected");
      break;
      case 4://"Selected Loop"
      do_action_on_selected_minifaders(2);
      sprintf(string_event,"Toggled LOOP Minif. Selected");
      break;
      case 5://"Selected Up");
      do_action_on_selected_minifaders(3);
      sprintf(string_event,"Toggled UP Minif. Selected");
      break;
      case 6://"Selected Down");
      do_action_on_selected_minifaders(4);
      sprintf(string_event,"Toggled DOWN Minif. Selected");
      break;
      case 7://"Selected Saw");
      do_action_on_selected_minifaders(5);
      sprintf(string_event,"Toggled SAW Minif. Selected");
      break;
      case 8://"Selected All Loop");
      do_action_on_selected_minifaders(6);
      sprintf(string_event,"Toggled ALL LOOP Minif. Selected");
      break;
      case 9://"Selected All At");
      do_action_on_selected_minifaders(7);
      sprintf(string_event,"ALL AT Minif. Selected");
      break;
      case 10://"Selected Set Pos.");
      do_action_on_selected_minifaders(8);
      sprintf(string_event,"Toggled STOPPOS Minif. Selected");
      break;
      case 11://"Selected ToPrev");
      do_action_on_selected_minifaders(9);
      sprintf(string_event,"ToPREV Minif. Selected");
      break;
      case 12://"Selected ToNext");
      do_action_on_selected_minifaders(10);
      sprintf(string_event,"ToNEXT Minif. Selected");
      break;
      case 13://"Selected Up&Down");
      do_action_on_selected_minifaders(11);
      sprintf(string_event,"Toggled UP&DOWN Minif. Selected");
      break;
      case 14://"Selected Dock -");
      do_action_on_selected_minifaders(12);
      sprintf(string_event,"Dock - Minif. Selected");
      break;
      case 15://"Selected Dock +");
      do_action_on_selected_minifaders(13);
      sprintf(string_event,"Dock + Minif. Selected");
      break;
      case 16://"Selected PlayChaser");
      do_action_on_selected_minifaders(14);
      sprintf(string_event,"PlayCHASER Minif. Selected");
      break;
      case 17://"Minifader Preset");
      if(the_fader_is>=0 && the_fader_is<8)
      {
      for(int olp=0;olp<core_user_define_nb_faders;olp++)
      {minifaders_selected[olp]=minifaders_preset_selection[the_fader_is][olp];}
      sprintf(string_Last_Order,"Called MiniF.Preset %d", the_fader_is+1);
      }
      break;
      default: break;
}
}
break;
case 9://icat
the_icatpage_is=bangers_params[banger_num][event_num][0]-1;
     switch(bangers_action[banger_num][event_num])
     {
      case 0://"Select Page Num");
      if(the_icatpage_is>=0 && the_icatpage_is<=7)
      {
      iCatPageis=the_icatpage_is;
      if (enable_iCat==1 && iCat_serveur_is_initialized==1)
      {
      load_iCat_page(iCatPageis);
      do_send_icat_init_page=1;
      }
      sprintf(string_event,"Called iCat page %d",  iCatPageis+1);
      }
      break;
      case 1://"Select Page -");
      iCatPageis--;
         if(iCatPageis<0){iCatPageis=7;}
         if (enable_iCat==1 && iCat_serveur_is_initialized==1)
         {
         load_iCat_page(iCatPageis);
         do_send_icat_init_page=1;
         }
          sprintf(string_event,"Called iCat Page -");
      break;
      case 2://"Select Page +");
      iCatPageis++;
      if (enable_iCat==1 && iCat_serveur_is_initialized==1)
      {
      if(iCatPageis>7){iCatPageis=0;}
      load_iCat_page(iCatPageis);
      do_send_icat_init_page=1;
      }
       sprintf(string_event,"Called iCat Page +");
      break;
      case 3://"Refresh Page");
      if (enable_iCat==1 && iCat_serveur_is_initialized==1)
      {
       do_refresh_iCat(iCatPageis);
       }
        sprintf(string_event,"Refreshed iCat Page");
      break;
      case 4://"Toggle Orientation");
      iCat_preset_orientation[iCatPageis]++;
      if(iCat_preset_orientation[iCatPageis]>2){iCat_preset_orientation[iCatPageis]=0;}
      if(iCat_preset_orientation[iCatPageis]==0)
      {
      L_tablier_iCat=160;H_tablier_iCat=240;
      }
      else {L_tablier_iCat=240;H_tablier_iCat=160;}
      if (enable_iCat==1 && iCat_serveur_is_initialized==1)
      {
      do_refresh_iCat(iCatPageis);
      }
       sprintf(string_event,"Toggled orientation iCat Page");
      break;
      default:
      break;
      }
break;
case 10: //chrono
     switch(bangers_action[banger_num][event_num])
     {
      case 0://reset
      Chrono_Reset();
      sprintf(string_event,"Reseted Chrono");
      break;
      case 1://play pause
      switch(bangers_params[banger_num][event_num][0])
      {
      case 0:
      index_play_chrono=0;
      sprintf(string_Last_Order,"Paused Chrono");
      break;
      case 1:
      index_play_chrono=1;
      sprintf(string_event,"Played Chrono");
      break;
      default: break;
      }
      break;
      case 2:
      if(bangers_params[banger_num][event_num][0]>=0 && bangers_params[banger_num][event_num][0]<3)
      {time_wheel_datatype_is=bangers_params[banger_num][event_num][0];
      sprintf(string_event,"Setted Chrono Page %d",bangers_params[banger_num][event_num][0]);
      }
      break;
      default:
      break;
      }
break;
case 11://set channel
bang_the_chan_is=bangers_params[banger_num][event_num][0];
bang_val_the_chan_is=bangers_params[banger_num][event_num][1];
if(bang_the_chan_is>0 && bang_the_chan_is<513)
{
     switch(bangers_action[banger_num][event_num])
     {
      case 0://"/100 Set At");
      switch(index_blind)
      {
       case 0:
       bufferSaisie[bang_the_chan_is]=(int)(( (float)bang_val_the_chan_is*2.55)+1);// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       if(bufferSaisie[bang_the_chan_is]>=255){bufferSaisie[bang_the_chan_is]=255;}
       break;
       case 1:
       bufferBlind[bang_the_chan_is]=(int)(( (float)bang_val_the_chan_is*2.55)+1);// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       if(bufferBlind[bang_the_chan_is]>=255){bufferBlind[bang_the_chan_is]=255;}
       break;
       default: break;
      }
      sprintf(string_event,"SetChan %d at %d/100",bang_the_chan_is,bang_val_the_chan_is);
      break;
      case 1://"/100 Set +");
      switch(index_blind)
      {
       case 0:
       if(bufferSaisie[bang_the_chan_is]+(int)(( (float)bang_val_the_chan_is*2.55)+1)<255)
       {
       bufferSaisie[bang_the_chan_is]+=(int)(( (float)bang_val_the_chan_is*2.55)+1);// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       }
       else
       {bufferSaisie[bang_the_chan_is]=255;}
       break;
       case 1:
       if(bufferBlind[bang_the_chan_is]+(int)(( (float)bang_val_the_chan_is*2.55)+1)<255)
       {
       bufferBlind[bang_the_chan_is]+=(int)(( (float)bang_val_the_chan_is*2.55)+1);
       }
       else {bufferBlind[bang_the_chan_is]=255;}
       break;
       default: break;
      }
      sprintf(string_event,"SetChan %d + %d/100",bang_the_chan_is,bang_val_the_chan_is);
      break;
      case 2://"/100 Set -");
      switch(index_blind)
      {
       case 0:
       if( bufferSaisie[bang_the_chan_is]-(int)(( (float)bang_val_the_chan_is*2.55)+1)>0)
       {
       bufferSaisie[bang_the_chan_is]-=(int)(( (float)bang_val_the_chan_is*2.55)+1);// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       }
       else {bufferSaisie[bang_the_chan_is]=0;}
       break;
       case 1:
       if(bufferBlind[bang_the_chan_is]-(int)(( (float)bang_val_the_chan_is*2.55)+1)>0)
       {
       bufferBlind[bang_the_chan_is]-=(int)(( (float)bang_val_the_chan_is*2.55)+1);// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       }
       else
      {bufferBlind[bang_the_chan_is]=0;}
       break;
       default: break;
      }
      sprintf(string_event,"SetChan %d - %d/100",bang_the_chan_is,bang_val_the_chan_is);

      break;
      case 3://"/255 Set At");
      switch(index_blind)
      {
       case 0:
       bufferSaisie[bang_the_chan_is]=bang_val_the_chan_is;// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       if(bufferSaisie[bang_the_chan_is]>=255){bufferSaisie[bang_the_chan_is]=255;}
       break;
       case 1:
       bufferBlind[bang_the_chan_is]=bang_val_the_chan_is;// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       if(bufferBlind[bang_the_chan_is]>=255){bufferBlind[bang_the_chan_is]=255;}
       break;
       default: break;
      }
      sprintf(string_event,"SetChan %d at %d/255",bang_the_chan_is,bang_val_the_chan_is);
      break;
      case 4://"/255 Set +")
      switch(index_blind)
      {
       case 0:
       if( bufferSaisie[bang_the_chan_is]+bang_val_the_chan_is<255)
       {
       bufferSaisie[bang_the_chan_is]+=bang_val_the_chan_is;// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       }
       else {bufferSaisie[bang_the_chan_is]=255;}
       break;
       case 1:
       if( bufferBlind[bang_the_chan_is]+bang_val_the_chan_is<255)
       {
       bufferBlind[bang_the_chan_is]+=bang_val_the_chan_is;// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       }
       else {bufferBlind[bang_the_chan_is]=255;}
       break;
       default: break;
      }
      sprintf(string_event,"SetChan %d + %d/255",bang_the_chan_is,bang_val_the_chan_is);
      break;
      case 5://"/255 Set -");
      switch(index_blind)
      {
       case 0:
       if(bufferSaisie[bang_the_chan_is]-bang_val_the_chan_is>0)
       {
       bufferSaisie[bang_the_chan_is]-=bang_val_the_chan_is;// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       }
       else {bufferSaisie[bang_the_chan_is]=0;}
       break;
       case 1:
       if(bufferBlind[bang_the_chan_is]-bang_val_the_chan_is>0)
       {
       bufferBlind[bang_the_chan_is]-=bang_val_the_chan_is;// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
       }
       else {bufferBlind[bang_the_chan_is]=0;}
       break;
       default: break;
      }
      sprintf(string_event,"SetChan %d - %d/255",bang_the_chan_is,bang_val_the_chan_is);
      break;
      case 6://"Macro ON"
      if(bang_val_the_chan_is>0 && bang_val_the_chan_is<5)
      {
      macro_channel_on[bang_the_chan_is][bang_val_the_chan_is-1]=1;
      sprintf(string_event,"SetChan %d - Macro %d ON",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 7://"Macro OFF"
      if(bang_val_the_chan_is>0 && bang_val_the_chan_is<5)
      {
      macro_channel_on[bang_the_chan_is][bang_val_the_chan_is-1]=0;
      sprintf(string_event,"SetChan %d - Macro %d OFF",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 8://"Macro1 from to ON"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i<= bang_val_the_chan_is; i++)
      macro_channel_on[i][0]=1;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro1 ON",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 9://"Macro2 from to ON"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i<= bang_val_the_chan_is; i++)
      macro_channel_on[i][1]=1;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro2 ON",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 10://"Macro3 from to ON"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i<= bang_val_the_chan_is; i++)
      macro_channel_on[i][2]=1;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro3 ON",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 11://"Macro4 from to ON"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i<= bang_val_the_chan_is; i++)
      macro_channel_on[i][3]=1;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro4 ON",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 12://"Macro1 from to Off"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i<= bang_val_the_chan_is; i++)
      macro_channel_on[i][0]=0;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro1 OFF",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 13://"Macro2 from to Off"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i< bang_val_the_chan_is; i++)
      macro_channel_on[i][1]=0;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro2 OFF",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 14://"Macro3 from to Off"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i<= bang_val_the_chan_is; i++)
      macro_channel_on[i][2]=0;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro3 OFF",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      case 15://"Macro4 from to Off"
      if(bang_the_chan_is>0 && bang_the_chan_is<=512 && bang_val_the_chan_is>0 && bang_val_the_chan_is<=512)
      {
      for (int i=bang_the_chan_is; i<= bang_val_the_chan_is; i++)
      macro_channel_on[i][3]=0;
      sprintf(string_event,"SetFrom %d To %d Chan - Macro4 OFF",bang_the_chan_is,bang_val_the_chan_is);
      }
      break;
      default:
      break;
      }
}
break;

case 12:
if( bangers_params[banger_num][event_num][0]>0 &&  bangers_params[banger_num][event_num][0]<=127
&& ( bangers_params[banger_num][event_num][1]==0 || bangers_params[banger_num][event_num][1]==1) )

{
param1_is=bangers_params[banger_num][event_num][0]-1;
param2_is=bangers_params[banger_num][event_num][1];
     //bool bang_is_sended[128];//le bang est exécuté si = 0, si déjà exécuté, donc non actif =1
     switch(bangers_action[banger_num][event_num])
     {
      case 0://"On/Off");
      bang_is_sended[param1_is]=1-param2_is;
      switch(param2_is)
      {
      case 0:
           sprintf(string_event,"SetBanger %d OFF",param1_is+1);
      break;
      case 1:
      start_time_for_banger[param1_is]=actual_time;
     end_time_for_banger[param1_is]=default_time_of_the_bang;
     for (int o=0;o<6;o++)//reset des évènements
     {
     event_sended[param1_is][o]=0;
     if(bangers_delay[param1_is][o]>end_time_for_banger[param1_is])
     {end_time_for_banger[param1_is]=bangers_delay[param1_is][o];}
     }
      break;
      default: break;
      }
      break;
      case 1://"RollBack"); > go back
      if( bangers_params[banger_num][event_num][0]>0 &&  bangers_params[banger_num][event_num][0]<=127 )
     {
      param1_is=bangers_params[banger_num][event_num][0]-1;
      for (int y=0;y<6;y++)
      {
      if(bangers_type[param1_is][y]!=0 )
      {
      Bang_event_back(param1_is, y);
      event_sended[param1_is][y]=1;
      }
      }
      bang_is_sended[param1_is]=1;//bloquage de l envoi des autres évènements
      }
      break;
      case 2://banger loop on
      do_loop_banger[param1_is]=1;
      ticker_loop_banger[param1_is]=0;
      if(do_loop_banger[param1_is]==1)
      {
      start_time_for_banger[param1_is]=actual_time;
      end_time_for_banger[param1_is]=default_time_of_the_bang;
      //reset du banger concerné
      for (int o=0;o<6;o++)//reset des évènements
      {
      event_sended[param1_is][o]=0;
      if(bangers_delay[param1_is][o]>end_time_for_banger[param1_is])
      {end_time_for_banger[param1_is]=bangers_delay[param1_is][o];}
      }
      bang_is_sended[param1_is]=0;//reset du bang sended is
      }
      break;
      case 3://banger loop off
      do_loop_banger[param1_is]=0;
      bang_is_sended[param1_is]=1;
      break;
      default:
      break;
      }
}
break;


case 13://midi mute
    param1_is=bangers_params[banger_num][event_num][0]-1;
    param2_is=bangers_params[banger_num][event_num][1];
    if(param2_is==0 || param2_is==1)
    {
     switch(bangers_action[banger_num][event_num])
     {
     case 0://,"[GLOBAL]");
     for(int i=0;i<3072;i++)
     {
     is_raccrochage_midi_remote[i]=param2_is;
     }
     index_midi_mute=param2_is;
     break;
     case 1://"GrandMaster");
     is_raccrochage_midi_remote[615]=param2_is;
     break;
     case 2://"Fader");
     if(param1_is>=0 && param1_is<core_user_define_nb_faders)
     {
     is_raccrochage_midi_remote[param1_is]=param2_is;
     }
     break;
     case 3://"LFO");
     if(param1_is>=0 && param1_is<core_user_define_nb_faders)
     {
     is_raccrochage_midi_remote[196+param1_is]=param2_is;
     }
     break;
     case 4://sequenciel
     if(param1_is>=0 && param1_is<3)//0= X1 1= X2  2= Lfo
     {
     is_raccrochage_midi_remote[491+param1_is]=param2_is;
     }
     break;
     case 5://"Trichromy");
     is_raccrochage_midi_remote[497]=param2_is;
     break;
     case 6://"VideoTracking");
     is_raccrochage_midi_remote[498]=param2_is;
     break;
     case 7://"Audio Level");
     is_raccrochage_midi_remote[616+param1_is]=param2_is;
     break;
     case 8://"Audio Pan");
     is_raccrochage_midi_remote[624+param1_is]=param2_is;
     break;
     case 9://,"Audio Pitch");
     is_raccrochage_midi_remote[620+param1_is]=param2_is;
     break;

     default:
     break;
     }
     }
break;
case 14://Grid


param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];

switch(bangers_action[banger_num][event_num])
     {
     case 0://"1-Load&Play");
     numgridpl=0;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     gridder_prepare_cross(numgridpl, index_grider_selected[numgridpl], index_grider_step_is[numgridpl]);
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     grid_crossfade_start_time[numgridpl]=actual_time;
     grider_is_playing[numgridpl]=1;
     sprintf(string_event,"Load&Play %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 1://"2-Load&Play");
     numgridpl=1;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     gridder_prepare_cross(numgridpl, index_grider_selected[numgridpl], index_grider_step_is[numgridpl]);
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     grid_crossfade_start_time[numgridpl]=actual_time;
     grider_is_playing[numgridpl]=1;
     sprintf(string_event,"Load&Play %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 2://"3-Load&Play");
     numgridpl=2;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     gridder_prepare_cross(numgridpl, index_grider_selected[numgridpl], index_grider_step_is[numgridpl]);
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     grid_crossfade_start_time[numgridpl]=actual_time;
     grider_is_playing[numgridpl]=1;
     sprintf(string_event,"Load&Play %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 3://"4-Load&Play"); //grid step
     numgridpl=3;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     gridder_prepare_cross(numgridpl, index_grider_selected[numgridpl], index_grider_step_is[numgridpl]);
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     grid_crossfade_start_time[numgridpl]=actual_time;
     grider_is_playing[numgridpl]=1;
     sprintf(string_event,"Load&Play %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 4://"1-Stop&Load");    //grid step
     numgridpl=0;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     sprintf(string_event,"Stop&Load %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 5://"2-Stop&Load");
     numgridpl=1;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     sprintf(string_event,"Stop&Load %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 6://"3-Stop&Load");
     numgridpl=2;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     sprintf(string_event,"Stop&Load %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 7://"4-Stop&Load");
     numgridpl=3;
     grider_is_playing[numgridpl]=0;
     if(param1_is>0 && param1_is<128 && param2_is>0 && param2_is<1024)
     {
     index_grider_selected[numgridpl]=param1_is-1;
     index_grider_step_is[numgridpl]=param2_is-1;
     if(grider_seekto_mode[numgridpl]==1)//seek position
     {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}
     }
     grid_niveauX1[numgridpl]=255;
     grid_niveauX2[numgridpl]=0;
     grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
     grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
     sprintf(string_event,"Stop&Load %d Grid %d Step %d",numgridpl+1, param1_is,param2_is);
     break;
     case 8://"Play/Pause");   //Player ON/OFF
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is==0 || param2_is ==1)
     {
     grider_is_playing[numgridpl]=param2_is;
     if(grider_is_playing[numgridpl]==1)
     {
     grid_crossfade_start_time[numgridpl]=actual_time;
     sprintf(string_event,"Play GridPl %d",numgridpl+1);
     }
     else {sprintf(string_event,"Stop GridPl %d",numgridpl+1);}
     }
     }
     break;
     case 9://"Seek");     //bang
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     //+1 bug detected christoph 21/04/14
      index_grider_step_is[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]]+1;
      if(grider_seekto_mode[numgridpl]==1)//seek position
      {index_grider_seek_pos[numgridpl]=grid_seekpos[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]];}

      gridder_prepare_cross(numgridpl,index_grider_selected[numgridpl],index_grider_step_is[numgridpl]);
      grid_niveauX1[numgridpl]=255;
      grid_niveauX2[numgridpl]=0;
      grid_floatX1[numgridpl]=grid_niveauX1[numgridpl];
      grid_floatX2[numgridpl]=grid_niveauX2[numgridpl];
      sprintf(string_event,"Seek GridPl %d to Step %d",numgridpl+1, index_grider_step_is[numgridpl]+1);
     }
     break;
     case 10://"Autostop");
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is==0 || param2_is ==1)
     {
     grider_autostopmode[numgridpl]=param2_is;
     if(param2_is==1){sprintf(string_event,"GridPl %d Autostop /On",numgridpl+1);}
     else{sprintf(string_event,"GridPl %d Autostop /Off",numgridpl+1);}
     }
     }
     break;
     case 11://,"Macro Goto");
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is==0 || param2_is ==1)
     {
     grider_goto_mode[numgridpl]=param2_is;
      if(param2_is==1){sprintf(string_event,"GridPl %d MacroGoto /On",numgridpl+1);}
     else{sprintf(string_event,"GridPl %d MacroGoto /Off",numgridpl+1);}
     }
     }
     break;
     case 12://"Macro Seek");
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is==0 || param2_is ==1)
     {
     grider_seekto_mode[numgridpl]=param2_is;
     if(param2_is==1){sprintf(string_event,"GridPl %d MacroSeek /On",numgridpl+1);}
     else{sprintf(string_event,"GridPl %d MacroSeek /Off",numgridpl+1);}
     }
     }
     break;
     case 13://"Macro StopPlay");
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is==0 || param2_is ==1)
     {
     grider_stoplay_mode[numgridpl]=param2_is;
     if(param2_is==1){sprintf(string_event,"GridPl %d MacroStopPlay /On",numgridpl+1);}
     else{sprintf(string_event,"GridPl %d MacroStopPlay /Off",numgridpl+1);}
     }
     }
     break;
     case 14://"Set Seek");     //player seek
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is>0 && param2_is <1024)
     {
     index_grider_seek_pos[numgridpl]=param2_is;
     sprintf(string_event,"GridPl %d Set Seek in %d",numgridpl+1,param2_is);
     }
     }
     break;
     case 15://"Set Accel."); //player 0-127
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is>=0 && param2_is <=127)
     {
     grid_crossfade_speed[numgridpl]=param2_is;
     sprintf(string_event,"GridPl %d Set Accel at %d",numgridpl+1,param2_is);
     }
     }
     break;
     case 16://"Slave Mode");
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is==0 || param2_is ==1)
     {
     grid_player_slave[numgridpl]=param2_is;
     if(param2_is==1){sprintf(string_event,"GridPl %d Slave /On",numgridpl+1);}
     else{sprintf(string_event,"GridPl %d Slave /Off",numgridpl+1);}
     }
     }
     break;
     case 17://snap fader
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     if(param2_is>0 && param2_is<49)
     {
     GplSnapFader[numgridpl]=param2_is-1;
      for(int i=0;i<513;i++)
      {
     if(i+grider_begin_channel_is+1<513)
      {
      grid_levels[index_grider_selected[numgridpl]][index_grider_step_is[numgridpl]][i]=FaderDoDmx[(GplSnapFader[numgridpl])][i+grider_begin_channel_is];
      }
      }
     sprintf(string_event,"GridPl %d SnapFader %d",numgridpl+1, param2_is);
     }
     }
     break;
     case 18://"Next Step"); //GPL STP
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     gridplayer_step_plus( numgridpl);
     }
     break;
     case 19://"Previous Step"); //GPL Stp
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     gridplayer_step_minus(numgridpl);
     }
     break;
     case 20://christoph 21/04/14 set loop point to seek step for live recording options
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     grid_goto[(index_grider_selected[numgridpl])][(index_grider_step_is[numgridpl])][0]=index_grider_selected[numgridpl]; //actual gridp in gridplayer
     grid_goto[(index_grider_selected[numgridpl])][(index_grider_step_is[numgridpl])][1]=index_grider_seek_pos[numgridpl];//seek step
     }
     break;
     case 21://christoph 21/04/14 redefine actual step as seek step to create loop easely for live recording options
     if(param1_is>0 && param1_is<5)
     {
     numgridpl=param1_is-1;
     index_grider_seek_pos[numgridpl]=index_grider_step_is[numgridpl];//redefine seek step on the fly
     }
      sprintf(string_event,"Redefined SeekPts as %d in Grid %d",index_grider_seek_pos[numgridpl]+1, index_grider_selected[numgridpl]+1);

     break;
     case 22: //christoph 21/04/14  clear seek points
     if(param1_is>0 && param1_is<5)
     {
     for(int i=0;i<1023;i++)
     {
     grid_seekpos[index_grider_selected[numgridpl]][i]=0;
     }
     }
     sprintf(string_event,"GridPl %d Cleared SeekPts in %d", numgridpl, index_grider_selected[numgridpl]+1);
     break;
     case 23: //christoph 25/03/15  clear grid number for recording
     if(param1_is>0 && param1_is<5)
     {
       grid_to_clear=index_grider_selected[numgridpl];
       clear_a_grid(grid_to_clear);
       sprintf(string_event,"GridPl %d Cleared Grid %d", numgridpl, grid_to_clear+1);
     }
     break;
     default:
     break;
     }
break;
case 15://HARDWARE
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];

    switch(bangers_action[banger_num][event_num])
     {
     case 0://"Arduino ON/Off"
     if(param2_is==0 || param2_is ==1)
     {
     if(param2_is==0)
     {
     arduino_close(0);
     arduino_device_0_is_ignited=0;
     sprintf(string_event,"Arduino COM %d /Off",param1_is);
     }
     else if(param2_is==1)
     {
     arduino_com0=param1_is;arduino_init(0);
      sprintf(string_event,"Arduino COM %d /On",param1_is);
     }
     }
     break;
     case 1://"Arduino Baudrate"
     if(param2_is==300 || param2_is==1200 || param2_is==2400 || param2_is==4800 || param2_is==9600 ||
     param2_is==14400 || param2_is==19200 || param2_is==28800 || param2_is==38400 || param2_is==57600 || param2_is==115200)
     {
     if(arduino_device_0_is_ignited==1){arduino_close(0);}
     arduino_baud_rate0=param2_is;
     arduino_init(0);
     sprintf(string_event,"Arduino BaudRate %d",param2_is);
     }
     break;
     case 2://on off analog input
     if(param1_is>=0 && param1_is<63)//était à 64 analog limit aout 2016
     {
         if(param2_is!=0)
         {
         param2_is=1;
         sprintf(string_event,"Arduino Analog %d ON",param1_is);
         }
         else {sprintf(string_event,"Arduino Analog %d OFF",param1_is);}
         ventilate_analog_data[param1_is-1]=param2_is;
     }
     break;
     case 3://rescan midi
        QuitMidi() ;
        InitMidi();
        sprintf(string_event,"Midi Rescan done !");
     break;
     default:
     break;
     }
break;
case 16://emulate KBD

 switch(bangers_action[banger_num][event_num])
     {
     case 0://"Kbd A");
     simulate_keypress(KEY_Q<<8);
     break;
     case 1://"Kbd B");
     simulate_keypress(KEY_B<<8);
     break;
     case 2://"Kbd C");
     simulate_keypress(KEY_C<<8);
     break;
     case 3://"Kbd D");
     simulate_keypress(KEY_D<<8);
     break;
      case 4://"Kbd E");
      simulate_keypress(KEY_E<<8);
     break;
      case 5://"Kbd F");
      simulate_keypress(KEY_F<<8);
     break;
      case 6://"Kbd G");
      simulate_keypress(KEY_G<<8);
     break;
      case 7://"Kbd H");
      simulate_keypress(KEY_H<<8);
     break;
      case 8://"Kbd I");
      simulate_keypress(KEY_I<<8);
     break;
      case 9://"Kbd J");
      simulate_keypress(KEY_J<<8);
     break;
      case 10://"Kbd K");
      simulate_keypress(KEY_K<<8);
     break;
      case 11://"Kbd L");
      simulate_keypress(KEY_L<<8);
     break;
      case 12://"Kbd M");
      simulate_keypress(KEY_SEMICOLON<<8);
     break;
      case 13://"Kbd N");
      simulate_keypress(KEY_N<<8);
     break;
      case 14://"Kbd O");
      simulate_keypress(KEY_O<<8);
     break;
      case 15://"Kbd P");
      simulate_keypress(KEY_P<<8);
     break;
      case 16://"Kbd Q");
      simulate_keypress(KEY_A<<8);
     break;
      case 17://"Kbd R");
      simulate_keypress(KEY_R<<8);
     break;
      case 18://"Kbd S");
      simulate_keypress(KEY_S<<8);
     break;
      case 19://"Kbd T");
      simulate_keypress(KEY_T<<8);
     break;
      case 20://"Kbd U");
      simulate_keypress(KEY_U<<8);
     break;
      case 21://"Kbd V");
      simulate_keypress(KEY_V<<8);
     break;
      case 22://"Kbd W");
      simulate_keypress(KEY_Z<<8);
     break;
      case 23://"Kbd X");
     simulate_keypress(KEY_X<<8);
     break;
      case 24://"Kbd Y");
     simulate_keypress(KEY_Y<<8);
     break;
      case 25://"Kbd Z");
       simulate_keypress(KEY_W<<8);
     break;
     case 26://"Kbd SPACE");
     simulate_keypress(KEY_SPACE<<8);
     break;

     case 27://"Kbd DOT");
     simulate_keypress(KEY_COMMA<<8);
     break;

      case 28://"Kbd 0");
      simulate_keypress(KEY_0<<8);
     break;
      case 29://"Kbd 1");
      simulate_keypress(KEY_1<<8);
     break;
      case 30://"Kbd 2");
      simulate_keypress(KEY_2<<8);
     break;
      case 31://"Kbd 3");
      simulate_keypress(KEY_3<<8);
     break;
      case 32://"Kbd 4");
      simulate_keypress(KEY_4<<8);
     break;
      case 33://"Kbd 5");
      simulate_keypress(KEY_5<<8);
     break;
      case 34://"Kbd 6");
      simulate_keypress(KEY_6<<8);
     break;
      case 35://"Kbd 7");
      simulate_keypress(KEY_7<<8);
     break;
      case 36://"Kbd 8");
      simulate_keypress(KEY_8<<8);
     break;
      case 37://"Kbd 9");
      simulate_keypress(KEY_9<<8);
     break;

      case 38://"Kbd SHIFT");
      index_false_shift=  toggle(index_false_shift);
      index_false_control=0;
     break;
      case 39://"Kbd CTRL");
      index_false_control=  toggle(index_false_control);
      index_false_shift=0;
     break;
      case 40://"Kbd ESC");
      simulate_keypress(KEY_ESC<<8);
     break;
      case 41://"Kbd F1");
            simulate_keypress(KEY_F1 << 8);
     break;
      case 42://"Kbd F2");
            simulate_keypress(KEY_F2 << 8);
     break;
      case 43://"Kbd F3");
            simulate_keypress(KEY_F3 << 8);
     break;
      case 44://"Kbd F4");
            simulate_keypress(KEY_F4 << 8);
     break;
     case 45://"Kbd F5");
           simulate_keypress(KEY_F5 << 8);
     break;
     case 46://"Kbd F6");
           simulate_keypress(KEY_F6 << 8);
     break;
     case 47://"Kbd F7");
           simulate_keypress(KEY_F7 << 8);
     break;
     case 48://"Kbd F8");
           simulate_keypress(KEY_F8 << 8);
     break;
     case 49://"Kbd F9");
           simulate_keypress(KEY_F9 << 8);
     break;
     case 50://"Kbd F10");
           simulate_keypress(KEY_F10 << 8);
     break;
     case 51://"Kbd F11");
           simulate_keypress(KEY_F11 << 8);
     break;
     case 52://"Kbd F12");
           simulate_keypress(KEY_F12 << 8);
     break;
     case 53://"Kbd ENTER");
     simulate_keypress(KEY_ENTER<<8);
     break;
     case 54://"Kbd BCKSP");
     simulate_keypress(KEY_BACKSPACE << 8);
     break;
     case 55://"Kbd TAB");
     simulate_keypress(KEY_TAB<<8);
     break;
     case 56://"Kbd PLUS");
     simulate_keypress(KEY_PLUS_PAD<<8);
     break;
     case 57://"Kbd MINUS");
     simulate_keypress(KEY_MINUS_PAD<<8);
     break;
     case 58://"Kbd Arrow LEFT");
        simulate_keypress(KEY_LEFT<<8);
     break;
     case 59://"Kbd Arrow RIGHT");
        simulate_keypress(KEY_RIGHT<<8);
     break;
     case 60://"Kbd Arrow UP");
     simulate_keypress(KEY_UP<<8);
     break;
     case 61://"Kbd Arrow DOWN");
     simulate_keypress(KEY_DOWN<<8);
     break;
     case 62://"Kbd Arrow DEL");
     simulate_keypress(KEY_DEL<<8);
     break;
     default:
     break;
     }
break;
case 17://DRAW
param1_is=bangers_params[banger_num][event_num][0]-1;
param2_is=bangers_params[banger_num][event_num][1];
if(param1_is>=0 && param1_is<6)//etait <=6 aout 2016
{
     switch(bangers_action[banger_num][event_num])
     {
     case 0://"Select Matrix");
     draw_preset_selected=param1_is;
     recalculate_draw_sizes(param1_is);
     sprintf(string_event,"Draw Matrix %d selected",param1_is+1);
     break;
     case 1://"Set Brush");
     draw_brush_type[param1_is]=param2_is;
     if (draw_brush_type[param1_is]>1){draw_brush_type[param1_is]=1;}
     sprintf(string_event,"DrawBrush %d on Matrix %d",param2_is, param1_is+1);
     break;
     case 2://"Set DrawMode");
     draw_mode[param1_is]=param2_is;
     if (draw_mode[param1_is]>3){draw_mode[param1_is]=3;}
     sprintf(string_event,"DrawMode %d on Matrix %d",param2_is, param1_is+1);
     break;
     case 3://"Set Pressure");
     draw_level_to_do[param1_is]=(float)(constrain_data_to_midi_range(param2_is))/127;
      sprintf(string_event,"Draw Pressure %d on Matrix %d",param2_is, param1_is+1);
     break;
     case 4://"Set Angle");
     draw_damper_decay_factor[param1_is]=(float)(constrain_data_to_midi_range(param2_is))/127;
     sprintf(string_event,"Draw Angle %d on Matrix %d",param2_is, param1_is+1);
     break;
     case 5://"Set Ghost");
     draw_ghost_to_do[param1_is]=(float)(constrain_data_to_midi_range(param2_is))/127;
     sprintf(string_event,"Draw Ghost %d on Matrix %d",param2_is, param1_is+1);
     break;
     case 6://set GPL
     draw_get_gpl[param1_is]= constrain_int_data_to_this_range(param2_is,1,4) ;
     sprintf(string_event,"Draw %d SetGPL %d",param1_is+1, param2_is);
     break;
     case 7://set Offset
     draw_offset_gpl[param1_is]= constrain_int_data_to_this_range(param2_is,1,512);
     sprintf(string_event,"Draw %d SetOffset %d",param1_is+1, param2_is);
     break;
     case 8://clear drawing number
     draw_erase_drawing(param1_is);
     sprintf(string_event,"Draw %d Clear !",param1_is+1);
     break;
     case 9://"Snap Fader");
     if(param2_is>0 && param2_is<49)
     {
     for (int i=0;i< 500;i++)
     {
     if(draw_preset_channel_routing[param1_is][i]>0)
     {
     draw_preset_levels[param1_is][i]=((float)(FaderDoDmx[param2_is-1][draw_preset_channel_routing[param1_is][i]]))/255.0  ;
     }
     }
     }
     break;
     case 10://"Snap GridPl.");
    if(param2_is>0 && param2_is<5)
     {
     for (int i=0;i< 500;i++)
     {
     if(draw_preset_channel_routing[param1_is][i]>0 &&  i+grider_begin_channel_is+1<513 )
     {
     draw_preset_levels[param1_is][i]=((float)(buffer_gridder[param2_is-1][ draw_preset_channel_routing[param1_is][i]-grider_begin_channel_is ]))/255.0  ;
     }
     }
     }
     break;
     default:
     break;
     }
}
break;
case 18://ECHO
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];

     switch(bangers_action[banger_num][event_num])
     {
     case 0://"Select Echo");
     if(param1_is>0 && param1_is<25)
     {
     echo_selected=param1_is-1;
     sprintf(string_event,"Echo Selected %d",param1_is);
     }
     break;
     case 1://S.Set Fader");
     if(param1_is>0 && param1_is<49)
     {
     echo_pointing_fader_num[echo_selected]=param1_is;
     sprintf(string_event,"SetFader %d on Echo selected",param1_is);
     }
     break;
     case 2://S.ChanMode ");
     if(param2_is>=0 && param2_is<2)
     {
     echo_channel_manipulate_mode[echo_selected]=param2_is;
     sprintf(string_event,"SetChannelMode %d on Echo selected",param2_is);
     }
     break;
     case 3://"S.SetChan /255");
     if(param1_is>0 && param1_is<513 && param2_is < 255)
     {
      echo_levels[echo_selected][ ( echo_channel_manipulate_mode[echo_selected]) ] [param1_is]= ((float)param2_is) /255;
      sprintf(string_event,"SetChan %d at %d on Echo selected",param1_is,param2_is);
     }
     break;
     case 4://"S.SetChan /100");
     if(param1_is>0 && param1_is<513 && param2_is < 255)
     {
      echo_levels[echo_selected][ ( echo_channel_manipulate_mode[echo_selected]) ] [param1_is]= ((float)param2_is) /100;
      sprintf(string_event,"SetChan %d at %d on Echo selected",param1_is,param2_is);
     }
     break;
     case 5://Echo Mode");
     if(param2_is>=0 && param2_is<2)
     {
     echo_is_echo_mode[echo_selected]=param2_is;
     sprintf(string_event,"EchoMode is %d on Echo selected",param2_is);
     }
     break;
     case 6://S.SnapFader");
      snap_fader_state(echo_selected,echo_pointing_fader_num[echo_selected]-1);
      sprintf(string_event,"SnapFader %d on Echo selected",echo_pointing_fader_num[echo_selected]-1);
     break;
     case 7://S bounce !
       bounce(echo_selected);
       sprintf(string_event,"Bounce on Echo selected");
     break;
     case 8://S Snap kill bounce
      snap_kill_and_bounce(echo_selected,echo_pointing_fader_num[echo_selected]-1);
      sprintf(string_event,"S-K-B fader %d on Echo selected",echo_pointing_fader_num[echo_selected]-1);
     break;
     case 9://S recall fader
      recall_fader_state_echo(echo_pointing_fader_num[echo_selected]-1);
      sprintf(string_event,"Recall fader %d on Echo selected",echo_pointing_fader_num[echo_selected]-1);
     break;
     case 10://S.SetGravity
     if(param2_is>=0 && param2_is<128 )
     {
      echo_global_params[echo_selected][0]=((float)param2_is)/127.0;
      sprintf(string_event,"SetGravity %d on Echo selected",param2_is);
     }
     break;
     case 11://"S.SetMass");
     if(param2_is>=0 && param2_is<128 )
     {
      echo_global_params[echo_selected][1]=((float)param2_is)/127.0;
      sprintf(string_event,"SetMass %d on Echo selected",param2_is);
     }
     break;
     case 12://"S.SetEnergy");
     if(param2_is>=0 && param2_is<128 )
     {
      echo_global_params[echo_selected][2]=((float)param2_is)/127.0;
      sprintf(string_event,"SetEnergy %d on Echo selected",param2_is);
     }
     break;
     case 13://"S.SetChanPos");
     if(param2_is>0 && param2_is<513 )
     {
      echo_grid_channel_position[echo_selected]=param2_is-1;
      if(param2_is-1>(511-14)){echo_grid_channel_position[param1_is-1]=511-14;}
      sprintf(string_event,"SetChanPos %d on Echo selected",param2_is);
     }
     break;
     case 14://"E.EchoMode");
     if(param1_is>0 && param1_is<25 && param2_is>=0 && param2_is<2)
     {
     echo_is_echo_mode[param1_is-1]=param2_is;
     sprintf(string_event,"SetEchoMode %d on Echo %d",param2_is,param1_is);
     }
     break;
     case 15://"E.SetFader");
     if(param1_is>0 && param1_is<25 && param2_is>0 && param2_is<49)
     {
     echo_pointing_fader_num[param1_is-1]=param2_is;
      sprintf(string_event,"SetFader %d on Echo %d",param2_is,param1_is);
     }
     break;
     case 16://"E.SnapFader");
     if(param1_is>0 && param1_is<25 )
     {
     snap_fader_state(param1_is-1,echo_pointing_fader_num[param1_is-1]-1);
     sprintf(string_event,"SnapFader on Echo %d",param1_is);
     }
     break;
     case 17://"E.Bounce !");
     if(param1_is>0 && param1_is<25 )
     {bounce(param1_is-1);
      sprintf(string_event,"Bounce Echo %d",param1_is);
     }
     break;
     case 18://"E. S-K-B !");
     if(param1_is>0 && param1_is<25 )
     {
     snap_kill_and_bounce(param1_is-1,echo_pointing_fader_num[param1_is-1]-1);
      sprintf(string_event,"S-K-B fader %d on Echo %d",echo_pointing_fader_num[param1_is-1],param1_is);
     }
     break;
     case 19://"E.BackFader");
     if(param1_is>0 && param1_is<25 )
     {
     recall_fader_state_echo(echo_pointing_fader_num[param1_is-1]-1);
     sprintf(string_event,"Recall fader %d on Echo %d",echo_pointing_fader_num[param1_is-1],param1_is);
     }
     break;
     case 20://"E.ChanMode");
     if(param1_is>0 && param1_is<25 && param2_is>=0 && param2_is<2)
     {
     echo_channel_manipulate_mode[param1_is-1]=param2_is;
     sprintf(string_event,"SetChanmode %d on Echo %d",param2_is,param1_is);
     }
     break;
     case 21://"E.SetGravity");
     if(param1_is>0 && param1_is<25 &&  param2_is>=0 && param2_is<128 )
     {
      echo_global_params[param1_is-1][0]=((float)param2_is)/127.0;
      sprintf(string_event,"SetGravity at %d on Echo %d",param2_is,param1_is);
     }

     break;
     case 22://"E.SetMass");
     if(param1_is>0 && param1_is<25 && param2_is>=0 && param2_is<128 )
     {
      echo_global_params[param1_is-1][1]=((float)param2_is)/127.0;
      sprintf(string_event,"SetMass at %d on Echo %d",param2_is,param1_is);
     }

     break;
     case 23://"E.SetEnergy");
     if(param1_is>0 && param1_is<25 &&  param2_is>=0 && param2_is<128 )
     {
      echo_global_params[param1_is-1][2]=((float)param2_is)/127.0;
      sprintf(string_event,"SetEnergy at %d on Echo %d",param2_is,param1_is);
     }

     break;
     case 24://"E.SetChanPos");
     if(param1_is>0 && param1_is<25 && param2_is>0 && param2_is<513 )
     {

      echo_grid_channel_position[param1_is-1]= param2_is-1;
      if(param2_is-1>(511-14)){echo_grid_channel_position[param1_is-1]=511-14;}
      sprintf(string_event,"SetChanPos %d on Echo %d",param2_is,param1_is);

     }

     break;
     case 25://"E.Clear Echo");
     if(param1_is>0 && param1_is<25 )
     {
      clear_echo_preset(param1_is-1);
      sprintf(string_event,"Clear Echo %d",param1_is);
     }

     break;
     default:
     break;
     }
break;

case 19://WAVE
param1_is=bangers_params[banger_num][event_num][0];
param2_is=bangers_params[banger_num][event_num][1];

     switch(bangers_action[banger_num][event_num])
     {
     case 0://set controler_wave
        param1_is=constrain_int_data_to_this_range(param1_is-1,0,25);
        waver_control=param1_is;
        midi_levels[2117]=waver_control*5;
        clear_wave_slots();
        previous_waver_control=waver_control-1;
        wave_calculations();
     break;
     case 1://set pos brush
         param1_is=constrain_int_data_to_this_range(param1_is-1,0,25);
         lead_brush_reading[brush_selected]=param1_is;
         set_new_values_in_wave();
         previous_lead_brush_reading[brush_selected]=lead_brush_reading[brush_selected];
     break;
     case 2://set channel preset
        param1_is=constrain_int_data_to_this_range(param1_is-1,0,3);
        wave_channel_preset_selected=param1_is;
     break;
     case 3://set brush preset
         param1_is=constrain_int_data_to_this_range(param1_is-1,0,3);
         brush_selected=param1_is;
         set_new_values_in_wave();
     break;
     case 4://set decay
           param1_is=constrain_int_data_to_this_range(param1_is,0,127);
           for(int i=0;i<26;i++)
           {
           Wave_Dampered[i].set_damper_decay((((float)(param1_is))/127));
           }
            midi_levels[2114]=param1_is;
            index_send_midi_out[2114]=1;
     break;
     case 5://set delta
         param1_is=constrain_int_data_to_this_range(param1_is-1,0,127);
          param1_is=constrain_int_data_to_this_range(param1_is,0,127);
           for(int i=0;i<26;i++)
           {
           Wave_Dampered[i].set_damper_dt((((float)(param1_is))/127)/10);
           }
            midi_levels[2115]=param1_is;
            index_send_midi_out[2115]=1;
     break;
     case 6://set damper mode
         param1_is=constrain_int_data_to_this_range(param1_is,0,2);
         for(int i=0;i<26;i++)
                {
                Wave_Dampered[i].set_damper_mode(param1_is);
                }
     break;
     case 7://clear slots
        clear_wave_slots();
     break;
     case 8://clear brush
         clear_wave_brush(brush_selected);
     break;
     case 9://clear buffer
         clear_wave_buffer();
     break;
     case 10://play
        param1_is=constrain_int_data_to_this_range(param1_is,0,1);
        wave_play_state=param1_is;
     break;
     case 11://seek
          seek_to_beg_wave();
     break;
     case 12://set BPM
         param1_is=constrain_int_data_to_this_range(param1_is,1,6000);
         BPM_WAVE_RATE=param1_is;
         install_int_ex(ticker_WAVE ,BPM_TO_TIMER(BPM_WAVE_RATE));
     break;
     default:
     break;
     }
break;
default:
break;
}

sprintf(string_Last_Order,">>Banged Bang.%d : Ev.%d / %s",banger_num+1, event_num+1, string_event);


return(0);
}




int do_loop_bang(int banger_is)
{
ticker_loop_banger[banger_is]++;
//verifier ok calcul *10000
if(do_loop_banger[banger_is]==1 && time_loop_banger[banger_is]>0.0 && ticker_loop_banger[banger_is]>time_loop_banger[banger_is]*10000)
{
  for (int y=0;y<6;y++){event_sended[banger_is][y]=0;}
  bang_is_sended[banger_is]=0;
  start_time_for_banger[banger_is]=actual_time;
  ticker_loop_banger[banger_is]=0;
}
 return(0);
}

int do_bang(int banger_is)
{
if(banger_is<127 && bang_is_sended[banger_is]==0 )
{
end_time_for_banger[banger_is]=0;//reinit pour pierre groupe laps
//calcul bang time de fin
for (int y=0;y<6;y++)
{
if(bangers_delay[banger_is][y]> end_time_for_banger[banger_is])
{
end_time_for_banger[banger_is]= bangers_delay[banger_is][y];
}
}
if(end_time_for_banger[banger_is]<default_time_of_the_bang)
{end_time_for_banger[banger_is]=default_time_of_the_bang;}
///////////////////////


for (int y=0;y<6;y++)
{
if(bangers_type[banger_is][y]!=0)
{

if(actual_time>start_time_for_banger[banger_is]+ (bangers_delay[banger_is][y]*BPS_RATE) && event_sended[banger_is][y]==0)
{
    Bang_event(banger_is, y);
    event_sended[banger_is][y]=1;
}
}
}

if(actual_time>(start_time_for_banger[banger_is]+ (end_time_for_banger[banger_is]*BPS_RATE)))//rajout de +50 pour visualisation send dernier event
{
bang_is_sended[banger_is]=1;
}

}
return(0);
}



int do_go_back_bang(int banger_is)
{
if(bang_is_sended[banger_is]==0 )//|| (bang_is_sended[banger_is]==1 && index_go_back==1 && banger_is==Banger_Memoire[position_preset])si bang pas fini, ou si fini mais present dans un crossfade
{
for (int y=0;y<6;y++)
{
if(bangers_type[banger_is][y]!=0 )
{
    Bang_event_back(banger_is, y);
    event_sended[banger_is][y]=1;
}
}
bang_is_sended[banger_is]=1;//bloquage de l envoi des autres évènements
}

return(0);
}


int do_logical_feedback_banger(int xvis, int yvis)
{
int banger_overoll=0;
if(window_focus_id==917 )
{
for (int nb=0;nb<8;nb++)
{
for (int lb=0;lb<16;lb++)
{
if((nb)+(lb*8)<core_user_define_nb_bangers)
{
if( mouse_x>xvis+(nb*12)+30-5 && mouse_x<xvis+(nb*12)+30+5 && mouse_y>yvis+(lb*12)+30-5 && mouse_y<yvis+(lb*12)+30+5)
{
banger_overoll=(nb)+(lb*8);

if(banger_overoll<127 && banger_overoll>=0)
{
if(mouse_button==1 && mouse_released==0)
{
if(Midi_Faders_Affectation_Type!=0 )//config midi
{
attribute_midi_to_control(1343+banger_overoll, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
else
{
if(index_copy_banger==1)
{
index_ask_copy_banger=1;
index_ask_confirm=1;
index_banger_to_copy_in=banger_overoll;
mouse_released=1;
}
else
{
bang_is_sended[banger_overoll]=toggle(bang_is_sended[banger_overoll]);
switch (bang_is_sended[banger_overoll])
{
case 0://reset des send events et on demarre à la souris le banger
  for (int y=0;y<6;y++){event_sended[banger_overoll][y]=0;}
  start_time_for_banger[banger_overoll]=actual_time;

//calcul bang time de fin
for (int y=0;y<6;y++)
{
if(bangers_delay[banger_overoll][y]> end_time_for_banger[banger_overoll])
{
end_time_for_banger[banger_overoll]= bangers_delay[banger_overoll][y];
}
}
if(end_time_for_banger[banger_overoll]<default_time_of_the_bang)
{end_time_for_banger[banger_overoll]=default_time_of_the_bang;}
///////////////////////

last_banger_sended_manually=banger_overoll;
break;
case 1://go back sur le banger
for (int y=0;y<6;y++)
{
if(bangers_type[banger_overoll][y]!=0 )
{
    Bang_event_back(banger_overoll, y);
    event_sended[banger_overoll][y]=1;
}
}
bang_is_sended[banger_overoll]=1;//bloquage de l envoi des autres évènements
break;
default: break;
}
}
}
mouse_released=1;
}
}
}
}
}
}
}
 return(0);
}


int do_logical_fenetre_banger(int xb,int yb)
{

//num banger
if( mouse_x>xb+190 && mouse_x<xb+190+50 && mouse_y>yb+10 && mouse_y<yb+10+25)
{
if(index_main_clear==0)
{
 int dat=atoi(numeric);
 if(dat>0 && dat <=127)
 {
 index_banger_selected=dat-1;
 reset_numeric_entry();
 }
}
else
{
 index_ask_clear_banger=1;
 index_banger_to_copy_in=index_banger_selected;
 index_ask_confirm=1;
}
 mouse_released=1;
}

//UP DOWN bangers number selected
//BANGER ++
if(mouse_x>xb+160-12 && mouse_x<xb+160+12 && mouse_y>yb+55-12 && mouse_y<yb+55+12)
{

switch(miditable[0][742])
{
//midi report
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
sprintf(string_last_midi_id,"Banger Plus is Ch: %d Pitch: %d Typ: %s",miditable[1][742],miditable[2][742],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(742,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_banger_selected<126){index_banger_selected++;}
else {index_banger_selected=0;}
mouse_released=1;
}
}
//BANGER --
if( mouse_x>xb+120-12 && mouse_x<xb+120+12 && mouse_y>yb+55-12 && mouse_y<yb+55+12)
{

switch(miditable[0][741])
{
//midi report
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
sprintf(string_last_midi_id,"Banger Minus is Ch: %d Pitch: %d Typ: %s",miditable[1][741],miditable[2][741],thetypinfo);
if(Midi_Faders_Affectation_Type!=0 )//config midi
{
attribute_midi_solo_affectation(741,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_banger_selected>0){index_banger_selected--;}
else{index_banger_selected=126;}
mouse_released=1;
}
}
//COPY TO////////////////////////////////////////////////////////////////////////
if(mouse_x>(xb+280) && mouse_x<(xb+280+90) && mouse_y>(yb+10) && mouse_y<(yb+10+20))
{
index_copy_banger=toggle(index_copy_banger);
mouse_released=1;
}

//EDIT MODE
if(mouse_x>(xb+410) && mouse_x<(xb+410+50) && mouse_y>(yb+10) && mouse_y<(yb+10+20))
{
index_enable_edit_banger=toggle(index_enable_edit_banger);
mouse_released=1;
}

//mise en boucle
if(mouse_x>(xb+490) && mouse_x<(xb+540) && mouse_y>(yb+10) && mouse_y<(yb+30))
{
do_loop_banger[index_banger_selected]=toggle(do_loop_banger[index_banger_selected]);
ticker_loop_banger[index_banger_selected]=0;
if(do_loop_banger[index_banger_selected]==1)
{
start_time_for_banger[index_banger_selected]=actual_time;
//4 aout 2010 initalisation  un temps plus long par defaut pour faire partir mes évènements
end_time_for_banger[index_banger_selected]=default_time_of_the_bang;
//reset du banger concerné
for (int o=0;o<6;o++)//reset des évènements
{
event_sended[index_banger_selected][o]=0;
if(bangers_delay[index_banger_selected][o]>end_time_for_banger[index_banger_selected])
{end_time_for_banger[index_banger_selected]=bangers_delay[index_banger_selected][o];}
}
bang_is_sended[index_banger_selected]=0;//reset du bang sended is
}
mouse_released=1;
}
//temps de boucle
if(mouse_x>(xb+550) && mouse_x<(xb+600) && mouse_y>(yb+10) && mouse_y<(yb+30))
{
time_loop_banger[index_banger_selected]=atof(numeric);
reset_numeric_entry();
mouse_released=1;
}

//BANG DO IT

if(mouse_x>(xb+410) && mouse_x<(xb+410+50) && mouse_y>(yb+40) && mouse_y<(yb+40+30))
{

switch(miditable[0][734])
{
//midi report
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
sprintf(string_last_midi_id,"Bang It Button is Ch: %d Pitch: %d Typ: %s" , miditable[1][734],miditable[2][734],thetypinfo);
if( Midi_Faders_Affectation_Type!=0 )//config midi
{
attribute_midi_solo_affectation(734,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
start_time_for_banger[index_banger_selected]=actual_time;
//4 aout 2010 initalisation  un temps plus long par defaut pour faire partir mes évènements
end_time_for_banger[index_banger_selected]=default_time_of_the_bang;
//reset du banger concerné
for (int o=0;o<6;o++)//reset des évènements
{
event_sended[index_banger_selected][o]=0;
if(bangers_delay[index_banger_selected][o]>end_time_for_banger[index_banger_selected])
{end_time_for_banger[index_banger_selected]=bangers_delay[index_banger_selected][o];}
}
bang_is_sended[index_banger_selected]=0;//reset du bang sended is
//
mouse_released=1;
}
}

//affectation nom du banger
if(mouse_x>xb+200 && mouse_x<xb+320 && mouse_y> (yb+40) && mouse_y< (yb+40)+30 && index_enable_edit_banger==1)
{
 for(int tt=0;tt<24;tt++)
 {
 bangers_name[index_banger_selected][tt]=numeric[tt];
 }
 bangers_name[index_banger_selected][24]='\0';
  reset_numeric_entry();numeric_postext=0; if(index_text_auto_close==1){index_type=0;}
 sprintf(string_Last_Order,">>GIVED A NAME FOR BANGER %d ",index_banger_selected+1);
mouse_released=1;
}



for (int lp=0;lp<6;lp++)//6 ev en bang
{

//bang solo!
if(mouse_x>xb+450-10 && mouse_x<xb+450+10 && mouse_y>yb+110+(lp*30)-10 && mouse_y<yb+110+(lp*30)+10)
{

switch(miditable[0][735+lp])
{
//midi report
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
sprintf(string_last_midi_id,"BangSolo %d is Ch: %d Pitch: %d Typ: %s",lp+1 , miditable[1][735+lp],miditable[2][735+lp],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(735+lp,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(mouse_released==0)
{
Bang_event(index_banger_selected,lp);
mouse_released=1;
}
}
}

//change type d'ev
if(window_focus_id==917 && mouse_x>xb+30 && mouse_x<xb+30+100 && mouse_y>yb+100+(lp*30) && mouse_y<yb+100+(lp*30)+20 && index_enable_edit_banger==1)
{
bangers_type[index_banger_selected][lp]++;
reset_banger_event(index_banger_selected,lp);
constrain_banger_type(lp);
mouse_released=1;
}

//change type action
if(window_focus_id==917 && mouse_x>xb+150 && mouse_x<xb+150+100 && mouse_y>yb+100+(lp*30) && mouse_y<yb+100+(lp*30)+20 && index_enable_edit_banger==1 )
{
bangers_action[index_banger_selected][lp]++;
reset_banger_params(index_banger_selected,lp);
constrain_banger_param(lp);
mouse_released=1;
}

//affectaction datas
//val 1
if(mouse_x>xb+270 && mouse_x<xb+270+40 && mouse_y>yb+100+(lp*30) && mouse_y<yb+100+(lp*30)+20 && index_enable_edit_banger==1)
{
bangers_params[index_banger_selected][lp][0]=atol(numeric);
reset_numeric_entry();
mouse_released=1;
}
//val 2
if(mouse_x>xb+320 && mouse_x<xb+320+40 && mouse_y>yb+100+(lp*30) && mouse_y<yb+100+(lp*30)+20 && index_enable_edit_banger==1)
{
bangers_params[index_banger_selected][lp][1]=atol(numeric);
reset_numeric_entry();
mouse_released=1;
}
//delay
if(mouse_x>xb+380 && mouse_x<xb+380+40 && mouse_y>yb+100+(lp*30) && mouse_y<yb+100+(lp*30)+20 && index_enable_edit_banger==1)
{
bangers_delay[index_banger_selected][lp]=atof(numeric);
reset_numeric_entry();
mouse_released=1;
}

}


do_logical_feedback_banger(xb+480,yb+50);

return(0);
}


int refresh_banger_wx()
{
           //BANGER
           if(index_banger_is_on==1)//pour navigation rapide
           {

           //back du stage precedent a fabriquer

           //stage
           if(Banger_Memoire[position_onstage]>0 && Banger_Memoire[position_onstage]<128)
           {

           //effacement des autres bangers

           for (int p=0; p<128;p++)
           {
              bang_is_sended[p]=1;
              for (int y=0;y<6;y++){event_sended[p][y]=0;}
           }

           //envoi d un coup des events concerné par le crossfade
           for (int o=0;o<6;o++)
           {  Bang_event(Banger_Memoire[position_onstage]-1, o);}
           }



           }
           //
 return(0);
}

