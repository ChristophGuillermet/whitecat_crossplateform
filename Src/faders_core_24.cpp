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

* \file faders_core_24.cpp
* \brief {Core fonctions for the faders}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour controller les faders et leurs effets
*
*   Fonctions for controlling the faders and their effects
*
 **/

int indicate_wich_fader_is_the_highest()
{
for(int ig=1;ig<514;ig++)
{
int temp_highest=0;
for (int fd=0;fd<core_user_define_nb_faders;fd++)
{
if (FaderDoDmx[fd][ig]>temp_highest)
{
temp_highest=FaderDoDmx[fd][ig];
highest_level_comes_from_fader[ig]= fd+1;
}
}
}
return(0);
}


int asservissement_gridplayer(int cmptfader, int dk)
{
int the_gr= faders_dock_grid_affectation[cmptfader][dk];
if(grid_player_slave[the_gr]==1)
{
grid_crossfade_speed[the_gr]=lfo_speed[cmptfader];
gridder_prepare_cross(the_gr, index_grider_selected[the_gr], index_grider_step_is[the_gr]);
}
return(0);
}


int DoLock(int masterfader, int locklevel)
{
 for ( int fi=0;fi<core_user_define_nb_faders;fi++)
 {
 OldFaderLockProc[fi]=Fader[fi];
 if(FaderLocked[fi]==1 && fi!=masterfader)
 {
 Fader[fi]=(unsigned char)((((float)(StateOfFaderBeforeLock[fi]))/255)*locklevel);
 midi_levels[fi]=(int)(((float)Fader[fi])/2);
 if( OldFaderLockProc[fi]!=Fader[fi])
 {
 index_send_midi_out[fi]=1;
 }
 //direct ch
 if(DockTypeIs[fi][dock_used_by_fader_is[fi]]==10){index_fader_is_manipulated[fi]=1;}
 }
 }
 return(0);
}



int do_logical_fader_damper_commands(int _x,int _y, int fd)
{

if(window_focus_id==W_FADERS)
{
//ON OFF DAMPER
if( mouse_x>_x && mouse_x<_x+20 && mouse_y>_y+20 && mouse_y<_y+40)
{
if(mouse_button==1 && mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0 )
{
attribute_midi_to_control((1912+fd), Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
else
{
    if(fader_damper_is_on[fd]==0)
    {
        Fader_dampered[fd].fix_all_damper_state_value(Fader[fd]);
        Fader_dampered[fd].set_target_val(Fader[fd]);

    }
    fader_damper_is_on[fd]=toggle(fader_damper_is_on[fd]);

}
mouse_released=1;
}
if( Midi_Faders_Affectation_Type!=0)
{
//midi report
 switch(miditable[0][1912+fd])
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
  sprintf(string_last_midi_id,"Damper ON/OFF is Ch: %d Pitch: %d Type: %s", miditable[1][1912+fd],miditable[2][1912+fd],thetypinfo);
}
}

//DECAY CONSTANT OF DAMPER
if( mouse_x>_x+30 && mouse_x<=_x+157 && mouse_y>_y+15 && mouse_y<_y+27)
{

if( mouse_button==1 )
{
if( Midi_Faders_Affectation_Type!=0 && mouse_released==0)
{
attribute_midi_to_control((1960+fd), Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
    set_mouse_range(_x+30, _y+15, _x+157, _y+27);
    Fader_dampered[fd].set_damper_decay(1.0-(((float)(_x+157-mouse_x))/127));
    midi_levels[1960+fd]=127-(_x+157-mouse_x);
    index_send_midi_out[1960+fd]=1;
}
}
if( Midi_Faders_Affectation_Type!=0)
{
//midi report
 switch(miditable[0][1960+fd])
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
  sprintf(string_last_midi_id,"Damper Decay is Ch: %d Pitch: %d Type: %s", miditable[1][1960+fd],miditable[2][1960+fd],thetypinfo);
}

}

//DT CONSTANT OF DAMPER
if( mouse_x>_x+30 && mouse_x<=_x+157 && mouse_y>_y+35 && mouse_y<_y+47)
{

if( mouse_button==1 )
{
if( Midi_Faders_Affectation_Type!=0 && mouse_released==0)
{
attribute_midi_to_control((2056+fd), Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
    set_mouse_range(_x+30, _y+35, _x+157, _y+47);
    Fader_dampered[fd].set_damper_dt((1.0-(((float)(_x+157-mouse_x))/127))/10);
    midi_levels[2056+fd]=127-(_x+157-mouse_x);
    index_send_midi_out[2056+fd]=1;
}
}
if( Midi_Faders_Affectation_Type!=0)
{
//midi report
 switch(miditable[0][2056+fd])
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
  sprintf(string_last_midi_id,"Damper DT is Ch: %d Pitch: %d Type: %s", miditable[1][2056+fd],miditable[2][2056+fd],thetypinfo);
}

}


//Damper mode
if( mouse_x>_x+137 && mouse_x<_x+157 && mouse_y>_y && mouse_y<_y+10)
{
if(mouse_button==1 && mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0 )
{
attribute_midi_to_control((2008+fd), Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
else
{
    Fader_dampered[fd].set_damper_mode((Fader_dampered[fd].getdampermode()+1));
    mouse_released=1;
}
}
if( Midi_Faders_Affectation_Type!=0)
{
//midi report
 switch(miditable[0][2008+fd])
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
  sprintf(string_last_midi_id,"Damper Mode is Ch: %d Pitch: %d Type: %s", miditable[1][2008+fd],miditable[2][2008+fd],thetypinfo);
}
}

//midi out
button_midi_out_core(_x+130,_y+65,(fd+1960));//DECAY
button_midi_out_core(_x+150,_y+65,(fd+2056));//DT

}

/*
if( mouse_x>_x+147 && mouse_x<_x+160 && mouse_y>_y+55 && mouse_y<_y+65 && mouse_button==1 && mouse_released==0)
{
midi_send_out[fd+1960]=toggle(midi_send_out[fd+1960]);
mouse_released=1;
}*/
return(0);
}

////////////////////////////////////////////////////////////////////////////
int do_logical_Lock_Preset_Call(int xf,int yf)
{
int calcul_lock=0;

for (int cm=0;cm<2;cm++)
{
 for (int ll=0;ll<4;ll++)
 {

 calcul_lock=cm+(2*ll);

 if(mouse_x>xf+(cm*55)-5 && mouse_x<xf+(cm*55)+40 && mouse_y>yf+(ll*55) && mouse_y<yf+(ll*55)+45)
 {


 //midi report
 switch(miditable[0][605+calcul_lock])
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
  sprintf(string_last_midi_id,"Lock Preset %d is Ch: %d Pitch: %d Type: %s",calcul_lock+1, miditable[1][605+calcul_lock],miditable[2][605+calcul_lock],thetypinfo);

 //config midi
  if( Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_to_control(605+calcul_lock,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
 mouse_released=1;

 }
 else
 {

 if(index_do_dock==1)
 {
 for(int f=0;f<core_user_define_nb_faders;f++)
 {
 FaderLocked_Preset[calcul_lock][f]=0;        //reset des états avant stockage
 StateOfFaderBeforeLock_Preset[calcul_lock][f]=0;
 LockFader_is_FullLevel_Preset[calcul_lock][f]=0;
 if ( FaderLocked[f]==1)
 {
 FaderLocked_Preset[calcul_lock][f]=FaderLocked[f];
 StateOfFaderBeforeLock_Preset[calcul_lock][f]=StateOfFaderBeforeLock[f];
 LockFader_is_FullLevel_Preset[calcul_lock][f]=LockFader_is_FullLevel[f];
 }
 }
 //extinction des autres
 for (int ipo=0;ipo<8;ipo++)
 {lock_preset[ipo]=0;}
 lock_preset[calcul_lock]=1;

 index_do_dock=0;
 sprintf(string_Last_Order,">> Lock State %d recorded",calcul_lock+1);
 }
 else  if(index_main_clear==1)
 {

 reset_indexs_confirmation();
 lock_preset_selected_for_record=calcul_lock;
 index_do_clear_lock_preset=1;
 index_ask_confirm=1;
 sprintf(string_Last_Order,">> Lock State %d cleared",calcul_lock+1);
 }
 else
 {
 do_lock_preset(calcul_lock);
 sprintf(string_Last_Order,">> Lock State %d called ",calcul_lock+1);
 }
 mouse_released=1;
 }
 }


}
}

return(0);
}



int do_logical_lfo_fader_functions (int cmptfader, int x, int y,int largeur, int espacement)
{

//is dock for lfo selected ( do cycle )
for (int dd=0;dd<core_user_define_nb_docks;dd++)
{

if(mouse_x>x+(cmptfader*espacement)+(largeur*size_faders)+100+10-6 && mouse_x<x+(cmptfader*espacement)+(largeur*size_faders)+100+10+6
&& mouse_y>y+10-6+(dd*40) && mouse_y<y+10+6+(dd*40))
{

if(is_dock_for_lfo_selected[cmptfader][dd]==0)
{is_dock_for_lfo_selected[cmptfader][dd]=1; }
else if (is_dock_for_lfo_selected[cmptfader][dd]==1)
{is_dock_for_lfo_selected[cmptfader][dd]=0;}
mouse_released=1;

}

//Cadre bouton speed

if(mouse_x>x+(cmptfader*espacement)-5 && mouse_x<x+(cmptfader*espacement)+127+5
&& mouse_y>y+375 && mouse_y<y+375+ (largeur/2))
{
//midi report
switch (miditable[0][196+cmptfader])
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
sprintf(string_last_midi_id,"LFO SPEED is Ch: %d Pitch: %d Typ: %s" , miditable[1][196+cmptfader],miditable[2][196+cmptfader],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)

{
attribute_midi_to_control(196+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else {
set_mouse_range(x+(cmptfader*espacement), y+375, x+(cmptfader*espacement)+127+5, y+375+ (largeur/2));//pour pas deborder
lfo_speed[cmptfader]=mouse_x-(x+(cmptfader*espacement));
if(lfo_speed[cmptfader]<0){lfo_speed[cmptfader]=0;}
if(lfo_speed[cmptfader]>127){lfo_speed[cmptfader]=127;}



if(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==12)//enchassement Grid si slave
{
asservissement_gridplayer(cmptfader,dock_used_by_fader_is[cmptfader]);
}
midi_levels[196+cmptfader]=lfo_speed[cmptfader];
index_send_midi_out[196+cmptfader]=1;
}
}


raccrochage_midi_logical_horizontal ( x+(cmptfader*espacement), y+375, 196+cmptfader,127,largeur/2);

if(mouse_x> (x+(cmptfader*espacement)+140 )&& (mouse_x<x+(cmptfader*espacement)+160) && mouse_y>(y+397-10) && mouse_y< (y+397+10))
{
if(mouse_button==1 && mouse_released==0)
{
midi_send_out[cmptfader+196]=toggle(midi_send_out[cmptfader+196]);
mouse_released=1;
}
}
//LFOS BUTTONS
//SET STOP POSITION
if(mouse_x> (x+(cmptfader*espacement)-6) && mouse_x<(x+(cmptfader*espacement)-6 + (largeur/2)) && mouse_y>(y+320) && mouse_y<(y+320 + (largeur/2))
&& mouse_released==0)
{
//midi report
switch (miditable[0][685+cmptfader])
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
sprintf(string_last_midi_id,"StopPos is Ch: %d Pitch: %d Typ: %s" , miditable[1][685+cmptfader],miditable[2][685+cmptfader],thetypinfo);


if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_to_control(685+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_do_dock==0 && index_main_clear==0)
{
ActionnateStopOn[cmptfader]=toggle(ActionnateStopOn[cmptfader]);mouse_released=1;
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
   StopPosOn[cmptfader]=1;LevelStopPos[cmptfader]=lStopPos;
   index_do_dock=0;
   do_light_setpos[cmptfader]=1;
   }
}
else if (numeric_postext==0) //affectation stop pos depuis le cursuer fader
{
StopPosOn[cmptfader]=1;LevelStopPos[cmptfader]=Fader[cmptfader];
index_do_dock=0;
do_light_setpos[cmptfader]=1;
}
}

else if(index_main_clear==1 && index_do_dock==0)//clear
{
StopPosOn[cmptfader]=0;
LevelStopPos[cmptfader]=999;
index_main_clear=0;
do_light_setpos[cmptfader]=1;
}
}
mouse_released=1;
}

//UP
if(mouse_x>x+(cmptfader*espacement)+105 && mouse_x<x+(cmptfader*espacement)+105+(largeur/2)
&& mouse_y> y+240 && mouse_y< y+240+(largeur/2) )
{
//midi report
switch (miditable[0][245+cmptfader])
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
  sprintf(string_last_midi_id,"LFO UP is Ch: %d Pitch: %d Typ: %s" , miditable[1][245+cmptfader],miditable[2][245+cmptfader],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_to_control(245+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else{
if(mouse_released==0 && (FaderLocked[cmptfader]==0 || LockFader_is_FullLevel[cmptfader]==1))//rajout lock 0.7.6
{
//for delays
start_time_for_delays[cmptfader]=actual_time;
//
if(lfo_mode_is[cmptfader]!=1)//up
{
lfo_mode_is[cmptfader]=1;
faders_in_float[cmptfader]=Fader[cmptfader];
if(index_midi_mute_on_lfo==1){is_raccrochage_midi_remote[cmptfader]=1;}
}
else {lfo_mode_is[cmptfader]=0;}
lfo_cycle_is_on[cmptfader]=0;
}
mouse_released=1;
}
}
//DOWN
if(mouse_x>x+(cmptfader*espacement)+105 && mouse_x<x+(cmptfader*espacement)+105+(largeur/2)
&& mouse_y> y+280 && mouse_y< y+280+(largeur/2))
{
//midi report
switch (miditable[0][294+cmptfader])
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
  sprintf(string_last_midi_id,"LFO DOWN is Ch: %d Pitch: %d Typ: %s" , miditable[1][294+cmptfader],miditable[2][294+cmptfader],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
if(mouse_released==0 )
{
attribute_midi_to_control(294+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
}
else{
if( mouse_released==0 && (FaderLocked[cmptfader]==0 || LockFader_is_FullLevel[cmptfader]==1))//rajout lock 0.7.6
{
//for delays
start_time_for_delays[cmptfader]=actual_time;
//
if(lfo_mode_is[cmptfader]!=2)//down
{
lfo_mode_is[cmptfader]=2;
faders_in_float[cmptfader]=Fader[cmptfader];
if(index_midi_mute_on_lfo==1){is_raccrochage_midi_remote[cmptfader]=1;}
}
else {lfo_mode_is[cmptfader]=0;}
lfo_cycle_is_on[cmptfader]=0;
mouse_released=1;
}
}
}
//saw ON
if(mouse_x>x+(cmptfader*espacement)+105 && mouse_x<x+(cmptfader*espacement)+105+(largeur/2)
&& mouse_y> y+320 && mouse_y< y+320+(largeur/2)&& window_focus_id==906)
{
//midi report
switch (miditable[0][343+cmptfader])
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
  sprintf(string_last_midi_id,"LFO SAW is Ch: %d Pitch: %d Typ: %s" , miditable[1][343+cmptfader],miditable[2][343+cmptfader],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
if(mouse_released==0 )
{
attribute_midi_to_control(343+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
}
else{
if(mouse_released==0 && (FaderLocked[cmptfader]==0 || LockFader_is_FullLevel[cmptfader]==1))//rajout lock 0.7.6
{
//for delays
start_time_for_delays[cmptfader]=actual_time;
//
faders_in_float[cmptfader]=Fader[cmptfader];
if(lfo_cycle_is_on[cmptfader]==0)//
{
lfo_cycle_is_on[cmptfader]=1;
lfo_mode_is[cmptfader]=0;
lfo_running_is_upward[cmptfader]=1;
if(index_midi_mute_on_lfo==1){is_raccrochage_midi_remote[cmptfader]=1;}
}
else if(lfo_cycle_is_on[cmptfader]==1)
{
lfo_cycle_is_on[cmptfader]=0;
}
mouse_released=1;
}
}
}
//STEPS
//backward
if(mouse_x>x+(cmptfader*espacement)+70 && mouse_x<x+(cmptfader*espacement)+70+(largeur/2) &&
mouse_y>y+280 && mouse_y<y+280+(largeur/2))
{
//midi report
 switch (miditable[0][392+cmptfader])
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
  sprintf(string_last_midi_id,"LFO DOCK MINUS is Ch: %d Pitch: %d Typ: %s" , miditable[1][392+cmptfader],miditable[2][392+cmptfader],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
if(mouse_released==0 )
{
attribute_midi_to_control(392+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
}
else{
if(mouse_released==0 )
{
if (lfo_do_next_step[cmptfader][0]==0) {lfo_do_next_step[cmptfader][0]=1;lfo_do_next_step[cmptfader][1]=0;}
else if (lfo_do_next_step[cmptfader][0]==1) {lfo_do_next_step[cmptfader][0]=0; }
mouse_released=1;
}
}
}

//forward

if(mouse_x>x+(cmptfader*espacement)+70 && mouse_x<x+(cmptfader*espacement)+70+(largeur/2) &&
mouse_y>y+320 && mouse_y<y+320+(largeur/2))
{
switch (miditable[0][441+cmptfader])
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
  sprintf(string_last_midi_id,"LFO DOCK PLUS is Ch: %d Pitch: %d Typ: %s" , miditable[1][441+cmptfader],miditable[2][441+cmptfader],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
if(mouse_released==0 )
{

attribute_midi_to_control(441+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
}
else{
if(mouse_released==0 )
{
if (lfo_do_next_step[cmptfader][1]==0) {lfo_do_next_step[cmptfader][1]=1;lfo_do_next_step[cmptfader][0]=0; ;}
else if (lfo_do_next_step[cmptfader][1]==1) {lfo_do_next_step[cmptfader][1]=0; }
mouse_released=1;
}
}
}
//LOOP UP DOWN


if(mouse_x>x+(cmptfader*espacement)+35 && mouse_x<x+(cmptfader*espacement)+35+(largeur/2) && mouse_y>y+320 && mouse_y<y+320+(largeur/2))
{
//midi report
switch (miditable[0][499+cmptfader])
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
  sprintf(string_last_midi_id,"LFO LOOP STEPS is Ch: %d Pitch: %d Typ: %s" , miditable[1][499+cmptfader],miditable[2][499+cmptfader],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
if(mouse_released==0 )
{
attribute_midi_to_control(499+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
}
else{
if(mouse_released==0)
{
lfo_cycle_steps[cmptfader]= toggle(lfo_cycle_steps[cmptfader]);
mouse_released=1;
}
}
}

//Loop
if(mouse_x>x+(cmptfader*espacement)+138 && mouse_x<x+(cmptfader*espacement)+138+(largeur/2) && mouse_y> y+240 && mouse_y< y+240+(largeur/2))
{
//midi report
switch (miditable[0][802+cmptfader])
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
sprintf(string_last_midi_id,"LFO LOOP ONE is Ch: %d Pitch: %d Typ: %s" , miditable[1][802+cmptfader],miditable[2][802+cmptfader],thetypinfo);

if( Midi_Faders_Affectation_Type!=0 )
{
if(mouse_released==0 )
{
attribute_midi_to_control(802+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
}
else
{
if(mouse_released==0 )
{
int docktotouch=(dock_used_by_fader_is[cmptfader]);
is_dock_for_lfo_selected[cmptfader][docktotouch]=toggle(is_dock_for_lfo_selected[cmptfader][docktotouch]);
mouse_released=1;
}
}
}
//Loop All
if(mouse_x>x+(cmptfader*espacement)+138 && mouse_x<x+(cmptfader*espacement)+138+(largeur/2)&& mouse_y> y+280 && mouse_y< y+280+(largeur/2))
{
//midi report
switch (miditable[0][851+cmptfader])
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
sprintf(string_last_midi_id,"LFO LOOP ALL is Ch: %d Pitch: %d Typ: %s" , miditable[1][851+cmptfader],miditable[2][851+cmptfader],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
if(mouse_released==0 )
{
attribute_midi_to_control(851+cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
}
else
{
if(mouse_released==0)
{
bool index_choose_mode_dkloop=0;//0 toggle tt le monde / 1 copie l etat du dck selctionné dans tt le monde

for (int ck=0;ck<core_user_define_nb_docks-1;ck++)
{
if(is_dock_for_lfo_selected[cmptfader][ck]!=is_dock_for_lfo_selected[cmptfader][ck+1])
{index_choose_mode_dkloop=1;break;}
}
switch(index_choose_mode_dkloop)
{
case 0:
for(int op=0;op<core_user_define_nb_docks;op++)
{
 is_dock_for_lfo_selected[cmptfader][op]=toggle(is_dock_for_lfo_selected[cmptfader][op]);
}
break;
case 1:
//tout le monde prend la valeur du dock selectionné
for(int j=0;j<core_user_define_nb_docks;j++)
{
if(DockIsSelected[cmptfader][j]==1)
{
int tempval_dockloop=toggle(is_dock_for_lfo_selected[cmptfader][j]);
for(int k=0;k<core_user_define_nb_docks;k++)
{
is_dock_for_lfo_selected[cmptfader][k]=toggle(tempval_dockloop);
}
break;
}
}
break;
default: break;
}
mouse_released=1;
}
}
}
//le Flash est mis dans le troncon principal car souci avec mouse_released




}
return(0);
}

////////////////////////////////////////////////////////////////////////////

int do_logical_MoveFaderSpace(int ydelimitation)
{
if( window_focus_id==W_FADERS && mouse_x< LargeurEspaceFaderSize && mouse_y>=ydelimitation-5 && mouse_y<=ydelimitation+35  )
{

if( Midi_Faders_Affectation_Type!=0)
    {
    if(mouse_button==1 && mouse_released==0 &&  window_focus_id==W_FADERS)
    {
     if(  mouse_x>scroll_faderspace+50 && mouse_x<scroll_faderspace+100  )//deplacement Y
    {attribute_midi_solo_affectation(1627,Midi_Faders_Affectation_Mode);}
    else if  (  mouse_x>scroll_faderspace && mouse_x<scroll_faderspace+50  )//deplacement X
    {attribute_midi_solo_affectation(767,Midi_Faders_Affectation_Mode);}
    mouse_released=1;
    }
    }
else
{
index_moving_fader_space=1;
if(index_moving_y_slide==0 && ( mouse_x<scroll_faderspace+50 || mouse_x>scroll_faderspace+100) )
   {
   index_moving_x_slide=1;   index_moving_y_slide=0;
   }
if(index_moving_x_slide==0 &&  mouse_x>scroll_faderspace+50 && mouse_x<scroll_faderspace+100 )//handle vetical
 {
   index_moving_y_slide=1;   index_moving_x_slide=0;
 }

}
}


if(index_moving_x_slide==1) {scroll_faderspace=mouse_x-25;}
else if(index_moving_y_slide==1) {YFader=mouse_y+30+25; }

return(0);
}





int do_logical_Touche_Midi_Mute(int xmute, int ymute)
{

 if(mouse_x>xmute && mouse_x<xmute+(90*size_faders) && mouse_y>ymute && mouse_y<ymute+25 && mouse_released==0)
 {
 index_midi_mute=toggle(index_midi_mute);
 if(index_midi_mute==1){sprintf(string_Last_Order,">>Midi IN muted");}
 else {sprintf(string_Last_Order,">>Midi IN un-muted");}
 mouse_released=1;
 }

return(0);
}


int do_logical_FaderSpace(int x, int y,int largeur, int espacement, int nbr_fader)
{
if(index_moving_fader_space==0)
{
for (int cmptfader=0;cmptfader<nbr_fader;cmptfader++)
{
//on affiche et actionne que si les données sont dans l espace de l ecran
if(((x+(cmptfader*espacement)+espacement)>0)&& ((x+(cmptfader*espacement)+largeur)< LargeurEspaceFaderSize))
{
//route FX
/////FX
if(mouse_released==0 && mouse_x>x+(cmptfader*espacement)+(largeur+20) && mouse_x<x+(cmptfader*espacement)+(largeur+20)+10 && mouse_y>=y-30 && mouse_y<=y-20)
{
fader_fx_route[cmptfader]=toggle(fader_fx_route[cmptfader]);
mouse_released=1;
}

// NORMAL / SUBTRACT / ect....
if(mouse_released==0 && mouse_x>x+(cmptfader*espacement)+(largeur+35) && mouse_x<x+(cmptfader*espacement)+(largeur+35)+largeur && mouse_y>=y-30 && mouse_y<=y-20)
{
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_to_control(1543+cmptfader, Midi_Faders_Affectation_Type,  Midi_Faders_Affectation_Mode);
}
else
{
  fader_mode_with_buffers[cmptfader]++;
 if(fader_mode_with_buffers[cmptfader]>5){fader_mode_with_buffers[cmptfader]=0;}
}
mouse_released=1;
}
//////////////AU DESSUS FADER////////////////////////////////////////////////////
if(mouse_x>x+(cmptfader*espacement) && mouse_x<x+(cmptfader*espacement)+largeur && mouse_y>=y && mouse_y<=y+255)
{
 //affichage qui dans dock si VIEW activé
show_who_is_in_dock( cmptfader,   detect_dock_used(cmptfader));
set_mouse_range(x+(cmptfader*espacement), y, x+(cmptfader*espacement)+largeur, y+255);//pour pas deborder
//click niveau fader
if( index_main_clear==0)
{
//NIVEAU
int val=((y+255)-mouse_y);
fader_set_level(cmptfader,val);
index_fader_is_manipulated[cmptfader]=1;
if(midi_send_out[cmptfader]==1){ index_send_midi_out[cmptfader]=1;}
if(lfo_mode_is[cmptfader]==1 || lfo_mode_is[cmptfader]==2 || lfo_cycle_is_on[cmptfader]==1)
{
lfo_mode_is[cmptfader]=0; lfo_mode_is[cmptfader]=0; lfo_cycle_is_on[cmptfader]=0;
}
//midi report
 switch(miditable[0][cmptfader])
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
  sprintf(string_last_midi_id,"Fader is Ch: %d Pitch: %d Type: %s", miditable[1][cmptfader],miditable[2][cmptfader],thetypinfo);

//CONFIG MIDI
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_to_control(cmptfader, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
}
//NETTOYAGE DE FADER ET DOCK
if(index_main_clear==1)//clear de tous les dock du fader
{
 fader_selected_for_record=cmptfader;
 index_do_clear_on_faders=1;
 index_ask_confirm=1;
 mouse_released=1  ;
}
}

if(mouse_x>x+(cmptfader*espacement)+largeur+95 && mouse_x<x+(cmptfader*espacement)+largeur+95+15 &&
mouse_y>y-35 && mouse_y<y-35+15 )
{
 //midi report
 switch(miditable[0][556+cmptfader])
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
  sprintf(string_last_midi_id,"MIDI DO ORDER BUTTON:Ch: %d Pitch: %d Type: %s", miditable[1][556+cmptfader],miditable[2][556+cmptfader],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_to_control(cmptfader+556, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
}
///////////////////////////////////////////////////////////////////////////////
//Docks Preset
for (int dd=0;dd<core_user_define_nb_docks;dd++)
{

if (DockIsSelected[cmptfader][dd]==1)
{

 if(DockTypeIs[cmptfader][dd]==5)
  {
  for(int tt=0;tt<24;tt++)
  {
  DockName[cmptfader][dd][tt]=descriptif_memoires[(DockHasMem[cmptfader][dd])][tt] ;
  }
  DockName[cmptfader][dd][24]='\0';
  }


}

//action sur dock
if(mouse_x>=(x+(cmptfader*espacement)+(largeur+30)) && mouse_x<=(x+(cmptfader*espacement)+(largeur+80))
   && mouse_y>=(y + (dd*40)) && mouse_y<=(y + (dd*40)+20)
   && index_over_function_call==0 )
 {
// show_who_is_in_dock(cmptfader,dd);  //mise en affichage sélection de qui est dans le dock


 //selection dock
 if(index_do_dock==0 && index_do_modify==0  && index_type==0    && index_main_clear==0 )
 {
   DockIsSelected[cmptfader][dd]=1;
   Unselect_other_docks(cmptfader, dd);
   mouse_released=1;
 }
 //nommage de dock
 else if( index_type==1)
 {
 for(int tt=0;tt<24;tt++)
 {
 DockName[cmptfader][dd][tt]=numeric[tt];
 }
 DockName[cmptfader][dd][24]='\0';
 reset_numeric_entry();numeric_postext=0; if(index_text_auto_close==1){index_type=0;}

 //MAJ d'un fader en DCH

 if( DockTypeIs[cmptfader][dd]==10 )
 {
 sprintf(descriptif_projecteurs[(FaderDirectChan[cmptfader][dd])],DockName[cmptfader][dd]);
 }
 sprintf(string_Last_Order,">>On Master %d GIVED A NAME FOR DOCK %d ", cmptfader+1,dd);
 mouse_released=1;
 }

 //store normal
 else if(index_do_dock==1 && index_direct_chan==0   && index_affect_chaser_to_dock==0  && index_affect_time==0 && index_affect_color_to_dock==0 && index_do_affect_net_to_dock==0
 && index_affect_dmxin==0 && index_affect_video_tracking_to_dock==0 && index_affect_audio_to_dock==0 && gridplayer_to_affect_is==-1
 && index_do_fgroup==0 && index_affect_to_dock_mover==0 && index_affect_draw_to_dock==0 &&  index_affect_echo_to_dock==0 && index_affect_wave_to_dock==0)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_record_on_faders=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
  //store direct CH
 else if(index_do_dock==1 && index_direct_chan==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;

 index_do_record_direct_ch=1;
 index_ask_confirm=1;
 mouse_released=1;
 }


 //Store Fgroup dans dock
 else if (  index_do_dock==1 && index_do_fgroup==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_affect_fgroup=1;
 index_ask_confirm=1;
 }

 //time
 else if( index_do_dock==1 && index_affect_time==1)
 {
 show_im_recording_a_time=1;
 DoTimeToDock(cmptfader,dd);
 sprintf(string_Last_Order,">>Time affected to Master %d Dock %d", cmptfader+1,dd);
 index_affect_time=0;
 mouse_released=1;
 }
 //trichro
 else if(index_do_dock==1 && index_affect_color_to_dock==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_affect_color_on_faders=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
  //Store Chaser dans dock
 else if (index_do_dock==1 && index_affect_chaser_to_dock==1 )
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_affect_fx=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
  //Store Grid dans dock
 else if ( index_do_dock==1 &&  gridplayer_to_affect_is>=0 )
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_affect_grid_to_fader=1;
 index_ask_confirm=1;
 }

 //video to dock
 else if( index_do_dock==1 && index_affect_video_tracking_to_dock==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_video_to_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
 //audio to dock
 else if( index_do_dock==1 && index_affect_audio_to_dock==1)
 {
 if(player_to_affect_to_dock>=0 && player_to_affect_to_dock<4 )
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_audio_to_dock=1;
 index_ask_confirm=1;
 }
 mouse_released=1;
 }
  //Store Mover dans dock
 else if (  index_do_dock==1 && index_affect_to_dock_mover==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_affect_mover=1;
 index_ask_confirm=1;
 }
 //dmx to dock
 else if( index_do_dock==1 && index_affect_dmxin==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_dmx_to_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
 //artnet to dock
 else if(index_do_dock==1 && index_do_affect_net_to_dock==1 )
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_artnet_to_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
 //draw
 else if(index_do_dock==1 && index_affect_draw_to_dock==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 draw_preset_selected_for_order=draw_preset_selected;
 index_do_draw_affect_to_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
  //echo
 else if(index_do_dock==1 && index_affect_echo_to_dock==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_affect_echo_to_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
 //Wave
 else if(index_do_dock==1 && index_affect_wave_to_dock==1)
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_ask_confirm=1;
 mouse_released=1;
 }
 //modify
 else if( index_do_modify==1 )
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_modify_on_faders=1;
 index_ask_confirm=1;
 mouse_released=1;
 }

  //report
 if( index_do_report==1 && index_type==0 && index_do_dock==0 && index_do_modify==0 )
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_report_on_faders=1;
 index_ask_confirm=1;
 mouse_released=1;
 }

  //clear
 else if(index_main_clear==1 )
 {
 fader_selected_for_record=cmptfader;
 dock_selected_for_record=dd;
 index_do_clear_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }


 //config midi
 else if(Midi_Faders_Affectation_Type!=0 && dd<2)
 {
 attribute_midi_to_control(cmptfader+48+(dd*48), Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
 mouse_released=1;
 }

}


}

//////////////////////////////////
//MIDI OUT
if(mouse_x> x+((cmptfader*espacement)+(largeur+30)-10) && mouse_x< x+((cmptfader*espacement)+(largeur+30)+10)
&& mouse_y>y+250-10 && mouse_y<y+250+10 )
{

  if(midi_send_out[cmptfader]==0){midi_send_out[cmptfader]=1; }
  else if(midi_send_out[cmptfader]==1){midi_send_out[cmptfader]=0; }
  //midi_send_out[cmptfader+196]= midi_send_out[cmptfader];//LFOS
  mouse_released=1;
}

//RACCROCHE MIDI
raccrochage_midi_logical_vertical_dmx(x+(cmptfader*espacement),y,cmptfader,largeur,255);
//////////////////////////////////////////////////////
if(mouse_y>(y+280) && mouse_y<(y+280+(largeur/2)+7) && mouse_x>x+(cmptfader*espacement) && mouse_x<(x+largeur+(cmptfader*espacement))
 )
{
 //midi report
 switch(miditable[0][146+cmptfader])
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
  sprintf(string_last_midi_id,"LOCK is Ch: %d Pitch: %d Type: %s", miditable[1][146+cmptfader],miditable[2][146+cmptfader],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_to_control(cmptfader+146, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
 mouse_released=1;
 }
  //action lock on/off
  else
  {
  switch(FaderLocked[cmptfader])
  {
   case 0:
   FaderLocked[cmptfader]=1;
   StateOfFaderBeforeLock[cmptfader]=Fader[cmptfader];
   if(StateOfFaderBeforeLock[cmptfader]==255){LockFader_is_FullLevel[cmptfader]=1;}
   else if(StateOfFaderBeforeLock[cmptfader]<255){LockFader_is_FullLevel[cmptfader]=0;}
   sprintf(string_Last_Order,">> LOCKED Fader %d",cmptfader+1);
   if(LockFader_is_FullLevel[cmptfader]==0)//quand mis en lock et pas full level rajout 0.7.6
   {
   lfo_mode_is[cmptfader]=0;
   lfo_cycle_is_on[cmptfader]=0;
   }
   break;
   case 1:
   FaderLocked[cmptfader]=0;
   //remise à plat du niveau
   Fader[cmptfader]=(unsigned char)((((float)(StateOfFaderBeforeLock[cmptfader]))/255)*locklevel);
   midi_levels[cmptfader]=(int)(((float)Fader[cmptfader])/2);
   sprintf(string_Last_Order,">> UNLOCKED Fader %d",cmptfader+1);
   break;
  default: break;
   }
   mouse_released=1;
  }

}

//attribution courbe
if(mouse_x>x+(cmptfader*espacement)-10 && mouse_x<x+(cmptfader*espacement)-10+20 && mouse_y>y+410 && mouse_y<y+410+20)
{

if(index_do_dock==1)
{
fader_selected_for_record=cmptfader;
curve_asked_for_fader=atoi(numeric);
if(curve_asked_for_fader>16 || curve_asked_for_fader<1)
{
curve_asked_for_fader=16;
}
index_ask_curv_to_fader=1;
index_ask_confirm=1;
mouse_released=1;
}

}

do_logical_lfo_fader_functions(cmptfader, x-((int)(largeur-(largeur*size_faders))), y,50,espacement);

}

//commande embeded
int the_chaser;
int the_grid_player;
int the_audio_player;

if(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==11 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==12
|| DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==6 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==7 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==8  )

{

if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==11) the_chaser=ChaserAffectedToDck[cmptfader][dock_used_by_fader_is[cmptfader]];
else if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==12 )  the_grid_player=faders_dock_grid_affectation[cmptfader][dock_used_by_fader_is[cmptfader]];
else if( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==6 ) the_audio_player=DockHasAudioVolume[cmptfader][dock_used_by_fader_is[cmptfader]]-1;
else if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==7 ) the_audio_player=DockHasAudioPan[cmptfader][dock_used_by_fader_is[cmptfader]]-1;
else if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==8 ) the_audio_player=DockHasAudioPitch[cmptfader][dock_used_by_fader_is[cmptfader]]-1;

//Play
if(mouse_x>x+(cmptfader*espacement)+20 && mouse_x<x+(cmptfader*espacement)+20+20 && mouse_y>y+410 && mouse_y<y+410+20   && mouse_released==0)
{
show_type_midi(1115+cmptfader, "Play embeded");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1115+cmptfader,Midi_Faders_Affectation_Mode);
}
else
{
switch(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]])
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
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> PLAY OFF from Fader %d Chaser %d",cmptfader+1,the_chaser+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY ON from Fader %d Chaser %d",cmptfader+1,the_chaser+1);
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
sprintf(string_Last_Order,">> PLAY OFF from Fader %d GridPl %d",cmptfader+1,the_grid_player+1);
break;
case 1:
sprintf(string_Last_Order,">> PLAY ON from Fader %d GridPl %d",cmptfader+1,the_grid_player+1);
break;
default: break;
}
break;
default:
break;
}

}
mouse_released=1;
}


//Seek to Beg
if(mouse_x>x+(cmptfader*espacement)+45 && mouse_x<x+(cmptfader*espacement)+65 && mouse_y>y+410 && mouse_y<y+410+20  && mouse_button==1 && mouse_released==0)
{
show_type_midi(1164+cmptfader, "Seek to Beg embedded");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1164+cmptfader,Midi_Faders_Affectation_Mode);
}
else
{
switch(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]])
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
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> Seek from Fader %d AudioPl %d",cmptfader+1,the_audio_player+1);
}
break;
case 11://chaser
chaser_seek_at_beg(the_chaser);
sprintf(string_Last_Order,">> Seek To Beg from Fader %d Chaser %d",cmptfader+1,the_chaser+1);
break;
case 12://grid
gridplayer_seek(the_grid_player);
sprintf(string_Last_Order,">> Seek from Fader %d GridPl %d",cmptfader+1,the_grid_player+1);
break;
default:
break;
}
}

mouse_released=1;
}

//loop
if(mouse_x>x+(cmptfader*espacement)+70 && mouse_x<x+(cmptfader*espacement)+70+20 && mouse_y>y+410 && mouse_y<y+410+20 && mouse_button==1 && mouse_released==0)
{
show_type_midi(1213+cmptfader, "Loop Selected CHASER");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1213+cmptfader,Midi_Faders_Affectation_Mode);
}
else
{
switch(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]])
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
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
sprintf(string_Last_Order,">> LOOP OFF from Fader %d Chaser %d",cmptfader+1, the_chaser+1);
break;
case 1:
sprintf(string_Last_Order,">> LOOP ON from Fader %d Chaser %d",cmptfader+1, the_chaser+1);
break;
default: break;
}
break;
case 12: //grid
grider_autostopmode[the_grid_player]=toggle(grider_autostopmode[the_grid_player]);
switch(grider_autostopmode[the_grid_player])
{
case 0:
sprintf(string_Last_Order,">> AutoStop OFF from Fader %d Gpl %d",cmptfader+1, the_grid_player+1);
break;
case 1:
sprintf(string_Last_Order,">> AutoStop ON from Fader %d Gpl %d",cmptfader+1, the_grid_player+1);
break;
default: break;
}
break;
default:
break;
}
}

mouse_released=1;
}

//AUTOLAUNCH
if(mouse_x>x+(cmptfader*espacement)+95 && mouse_x<x+(cmptfader*espacement)+95+20 && mouse_y>y+410 && mouse_y<y+410+20  && mouse_button==1 && mouse_released==0)
{
show_type_midi(1278+cmptfader, "Autolaunch Selected");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1278+cmptfader,Midi_Faders_Affectation_Mode);
}
else
{
autolaunch[cmptfader]=toggle( autolaunch[cmptfader] );
switch(autolaunch[cmptfader])
{
case 0:
sprintf(string_Last_Order,">> AUTOLAUNCH OFF Fader %d",cmptfader+1);
break;
case 1:
sprintf(string_Last_Order,">> AUTOLAUNCH ON Fader %d",cmptfader+1);
break;
default: break;
}
}

mouse_released=1;
}



}//fin si chaser embeded

//Damper mode

do_logical_fader_damper_commands(x+(cmptfader*espacement)-10,y+440, cmptfader );


}
//fin des 48
}//fin de la condition moving fader space


do_logical_MoveFaderSpace(y-70);// fonction pour se deplacer sur les 48 masters

return(0);
}
