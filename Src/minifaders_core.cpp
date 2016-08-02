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

* \file minifaders_core.cpp
* \brief {minifaders Core}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions core de la gestion des mini faders
*
*   Minifaders Core fonctions
*
**/



int all_at_zero_panel_core(int xf, int yf)
{


for (int u=0;u<8;u++)
{

if(mouse_x>xf && mouse_x<xf+50 && mouse_y>yf+10+(25*u) && mouse_y<yf+10+(25*u)+20 && mouse_released==0)
{


if( Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(548+u, 2);
}
 else
 {

  switch(u)
  {
           case 0://faders off
           do_stock_fadersstate(1,0,0,0,0);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           fader_set_level(p,0);
           /*Fader[p]=0;
           midi_levels[p]=0;
           index_send_midi_out[p]=1;*/
           }
           }
           break;
           case 1://speed at zero
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
           break;
           case 2://lock off
           do_stock_fadersstate(0,0,1,0,0);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           FaderLocked[p]=0;
           }
           }
           break;
           case 3://lfo off
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
           break;
           case 4://loop off
           do_stock_fadersstate(0,0,0,0,1);
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           for(int d=0;d<6;d++)
           {
           is_dock_for_lfo_selected[p][d]=0;
           }
           }
           }
           break;
           case 5://ALL
           do_stock_fadersstate(1,1,1,1,1);
            for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           /*Fader[p]=0;
           midi_levels[p]=0;
           index_send_midi_out[p]=1;*/
           fader_set_level(p,0);
           lfo_speed[p]=64;
           midi_levels[196+p]=64;
           index_send_midi_out[196+p]=1;
           FaderLocked[p]=0;
           lfo_mode_is[p]=0;//no lfo
           lfo_cycle_is_on[p]=0;//saw
           lfo_cycle_steps[p]=0;
           lfo_do_next_step[p][0]=0;
           lfo_do_next_step[p][1]=0;
           for(int d=0;d<6;d++)
           {
           is_dock_for_lfo_selected[p][d]=0;
           }
           }
           }
           break;
           case 6://midi out
           for (int p=0;p<core_user_define_nb_faders;p++)
           {
           if(minifaders_selected[p]==1)
           {
           midi_send_out[p]=0;//faders
           }
           }
           break;
           case 7://recall
           do_recall_fadersstate( stockage_all_at_zero_state[0],stockage_all_at_zero_state[1],
           stockage_all_at_zero_state[2],stockage_all_at_zero_state[3],stockage_all_at_zero_state[4]);
           break;
           default: break;
  }

 }
 mouse_released=1;
 }

}

return(0);
}





int mini_faders_panel_core(int xmf, int ymf, int larg)
{

if(mouse_y>ymf && mouse_y<ymf+20 )
{

if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+30)
{
if( Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(774,1);
}
else
{
position_minifader_selected--;
if(position_minifader_selected<0){position_minifader_selected=core_user_define_nb_faders;}
refresh_minifader_state_view_core(position_minifader_selected);
mouse_released=1;
}
}

else if(mouse_x>xmf+(24*larg)+35 && mouse_x<xmf+(24*larg)+55)
{
if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(775,1);
}
else
{
position_minifader_selected++;
if(position_minifader_selected>core_user_define_nb_faders){position_minifader_selected=0;}
refresh_minifader_state_view_core(position_minifader_selected);
mouse_released=1;
}
}
}


//SELECT ALL
if(mouse_y>ymf-25 && mouse_y<ymf-5 )
{
if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+55)
{
if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(145,1);
}
else
{
for(int i=0;i<core_user_define_nb_faders;i++)
{minifaders_selected[i]=1;}
}
}
}





 //select
if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+55 )
{

if(mouse_y>ymf+25 && mouse_y<ymf+45 && mouse_released==0 )
{
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(776,1);
mouse_released=1;
}
else
{
minifaders_selected[position_minifader_selected]=toggle(minifaders_selected[position_minifader_selected]);
mouse_released=1;
}
}

else if(mouse_y>ymf+50 && mouse_y<ymf+70 && mouse_released==0 )
{
if( Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(777,1);
 }
else
{
for(int l=0;l<core_user_define_nb_faders;l++)
{
minifaders_selected[l]=0;
}
}
mouse_released=1;
}
}

///////////////LES ACTIONS////////////////////////////////////////////////////
for(int lu=0;lu<5;lu++)
{
for(int llu=0;llu<3;llu++)
{
int numcom=(lu*3)+llu;
//mouse action:
if(mouse_x>xmf+(24*larg)+70+(lu*25) && mouse_x<xmf+(24*larg)+70+(lu*25)+20 && mouse_y>ymf+(llu*25) && mouse_y<ymf+(llu*25)+20)
{
char tmp_c[36];
switch(numcom)
{
case 0:
sprintf(tmp_c,"Flash");
break;
case 1:
sprintf(tmp_c,"Lock");
break;
case 2:
sprintf(tmp_c,"Loop");
break;
case 3:
sprintf(tmp_c,"Lfo UP");
break;
case 4:
sprintf(tmp_c,"Lfo DOWN");
break;
case 5:
sprintf(tmp_c,"Lfo SAW");
break;
case 6:
sprintf(tmp_c,"All Dock Looped");
break;
case 7:
sprintf(tmp_c,"All at 0");
break;
case 8:
sprintf(tmp_c,"Set Pos");
break;
case 9:
sprintf(tmp_c,"To Prev Dock");
break;
case 10:
sprintf(tmp_c,"To Next Dock");
break;
case 11:
sprintf(tmp_c,"Up and Down");
break;
case 12:
sprintf(tmp_c,"Sel Prev Dock");
break;
case 13:
sprintf(tmp_c,"Sel Next Dock");
break;
case 14:
sprintf(tmp_c,"Play Embedded");
break;
default:
                    strcpy(tmp_c,"");
break;
}

sprintf(string_last_midi_id,"%s is Ch: %d Pitch: %d Type: %s",tmp_c, miditable[1][778+numcom],miditable[2][778+numcom],thetypinfo);

if(numcom!=0 )// hors flash
{
if( Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(778+numcom,1);
 }

else
{
do_action_on_selected_minifaders(numcom);
mouse_released=1;
}
}


}



}
}

//les presets de sélections de faders//////////////////////////////////////////////////////////

for(int lg=0;lg<8;lg++)
{

if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+10+20 && mouse_y>ymf+90+(lg*25) && mouse_y<ymf+90+(lg*25)+20)
{

if(Midi_Faders_Affectation_Type!=0)
{
 //midi report
 switch(miditable[0][794+lg])
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
  sprintf(string_last_midi_id,"FaderPreset %d is Ch: %d Pitch: %d Type: %s",lg+1, miditable[1][794+lg],miditable[2][794+lg],thetypinfo);

 if(Midi_Faders_Affectation_Type==1)
 {attribute_midi_solo_affectation(794+lg,1);}
 else if(Midi_Faders_Affectation_Type==2)
 {
 attribute_midi_to_control(794, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
 }
}
else
{
if(index_do_dock==1)
{
minifader_preset_is=lg;
index_record_minifader_preset=1;
index_ask_confirm=1;
}
else if(index_main_clear==1)
{
minifader_preset_is=lg;
index_clear_minifader_preset=1;
index_ask_confirm=1;
}
else //selection souris normale
{
for(int olp=0;olp<core_user_define_nb_faders;olp++)
{minifaders_selected[olp]=minifaders_preset_selection[lg][olp];}
sprintf(string_Last_Order,"Called Fader Selection from Preset %d", lg+1);
}

}
}
}
////////////Les locks presets///////////////////////////////////////////////////

for(int lck=0;lck<8;lck++)
{

if(mouse_x>xmf+(24*larg)+35 && mouse_x<xmf+(24*larg)+35+20 && mouse_y>ymf+90+(lck*25) && mouse_y<ymf+90+(lck*25)+20)
{

if( Midi_Faders_Affectation_Type!=0)
{

     //midi report
 switch(miditable[0][605+lck])
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
  sprintf(string_last_midi_id,"Lock Preset %d is Ch: %d Pitch: %d Type: %s",lck+1, miditable[1][605+lck],miditable[2][605+lck],thetypinfo);

  if(Midi_Faders_Affectation_Type==1)
 {attribute_midi_solo_affectation(605+lck,1);}
 else if(Midi_Faders_Affectation_Type==2)
 {
 attribute_midi_to_control(605, Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
 }
}

else
 {

 if(index_do_dock==1)
 {

 minifader_lockpreset_is=lck;
 index_record_minifader_lockpreset=1;
 index_ask_confirm=1;
 }

 else  if(index_main_clear==1)
 {

 reset_indexs_confirmation();
 lock_preset_selected_for_record=lck;
 index_do_clear_lock_preset=1;
 index_ask_confirm=1;
 sprintf(string_Last_Order,">> Lock State %d cleared",lck+1);
 }
 else
 {
 do_lock_preset(lck);
 sprintf(string_Last_Order,">> Lock State %d called ",lck+1);
 }
mouse_released=1;
}
}
}


/////////////////ALL AT 0///////////////////////////////////////////////////////
all_at_zero_panel_core((xmf+24*larg)+60,ymf+80);

midi_send_faders_button_logical((xmf+24*larg)+140,ymf-40,W_MINIFADERS);


////////////////////////////////////////////////////////////////////////////////
/////////////////////////LES 48 POTARDS/////////////////////////////////////////
int hmfd=200;//hauteur d une ligne de 24 faders
for(int cmptfader=0; cmptfader<max_faders/2; cmptfader++)
{
for(int lfad=0;lfad<2;lfad++)
{

if(cmptfader+(lfad*24)<=core_user_define_nb_faders-1)//limitation nbre faders
{

////FX MODE

if(  window_focus_id==922 && mouse_released==0 && mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg && mouse_y>(ymf+(lfad*hmfd))-12  && mouse_y<(ymf+(lfad*hmfd))-12+5 )
{
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_to_control(1543+cmptfader+(lfad*24), Midi_Faders_Affectation_Type,  Midi_Faders_Affectation_Mode);
}
else
{
  fader_mode_with_buffers[cmptfader+(lfad*24)]++;
 if(fader_mode_with_buffers[cmptfader+(lfad*24)]>5){fader_mode_with_buffers[cmptfader+(lfad*24)]=0;}
}
mouse_released=1;
}

///////////SELECTION SOURIS SUR  NUMEROS AU DESSUS FADERS/////////////////////////////////////////////////////////
if( mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg && mouse_y>(ymf+(lfad*hmfd))  && mouse_y<(ymf+15+(lfad*hmfd)) )
{
position_minifader_selected=cmptfader+(lfad*24);

int dock_selected_is=detect_dock_used(position_minifader_selected);


//SELECTION
if(index_do_dock==0 && index_do_modify==0  && index_type==0    && index_main_clear==0 )
{
 minifaders_selected[position_minifader_selected]=toggle(minifaders_selected[position_minifader_selected]);
 if(index_inspekt==1)//affichage qui dans dock si VIEW activé
 {
 show_who_is_in_dock( position_minifader_selected,   detect_dock_used(position_minifader_selected));
 }
 mouse_released=1;
}


 //store normal
 if(index_do_dock==1 && index_direct_chan==0   && index_affect_chaser_to_dock==0  && index_affect_time==0 && index_affect_color_to_dock==0 && index_do_affect_net_to_dock==0
 && index_affect_dmxin==0 && index_affect_video_tracking_to_dock==0 && index_affect_audio_to_dock==0 && gridplayer_to_affect_is==-1
 && index_do_fgroup==0 && index_affect_to_dock_mover==0 && index_affect_draw_to_dock==0 &&  index_affect_echo_to_dock==0 && index_affect_wave_to_dock==0)
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_record_on_faders=1;
 index_ask_confirm=1;
 }

 //store group fader
 else if(index_do_dock==1 && index_do_fgroup==1 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 bool index_there_is_fader_selected=0;
 for(int io=0;io<48;io++)
 {
 if(minifaders_selected[io]==1){index_there_is_fader_selected=1;break;}
 }
 if(index_there_is_fader_selected==1)
 {
 index_do_affect_fgroup=1;
 index_ask_confirm=1;
 }
 else{sprintf(string_Last_Order,"No minifaders selected");}
 }

  //affect time
 else if (index_do_dock==1 && index_affect_time==1 )
 {
 show_im_recording_a_time=1;
 DoTimeToDock(position_minifader_selected,dock_selected_is);
 sprintf(string_Last_Order,">>Time affected to Master %d Dock %d", position_minifader_selected+1,dock_selected_is);
 //index_affect_time=0; DEBUG Fevrier 2015 time affectation was not working on minifaders
 }
 //color dock
 else if(index_do_dock==1 && index_affect_color_to_dock==1 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_affect_color_on_faders=1;
 index_ask_confirm=1;
 }
 //dmx to dock
 else if(index_do_dock==1 && index_affect_dmxin==1 ) // affect couleurs dans dock
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_dmx_to_dock=1;
 index_ask_confirm=1;
 }
 //artnet to dock
 else if(index_do_dock==1 && index_do_affect_net_to_dock==1 ) // affect Network IN dans dock
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_artnet_to_dock=1;
 index_ask_confirm=1;
 }
 //video to dock
 else if(index_do_dock==1 && index_affect_video_tracking_to_dock==1) // affect Network IN dans dock
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_video_to_dock=1;
 index_ask_confirm=1;
 }
 //audio to dock
 else if(index_do_dock==1 &&  index_affect_audio_to_dock==1) // affect audio controls dans dock
 {
 if(player_to_affect_to_dock>=0 && player_to_affect_to_dock<4 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_audio_to_dock=1;
 index_ask_confirm=1;
 }
 }

 //store direct CH
 else if(index_do_dock==1 && index_direct_chan==1 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_record_direct_ch=1;
 index_ask_confirm=1;
 }
 //store FX
 else if(index_do_dock==1 && index_affect_chaser_to_dock==1)
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_affect_fx=1;
 index_ask_confirm=1;
 }
 //store Grid
 else if(index_do_dock==1 &&  gridplayer_to_affect_is>=0 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_affect_grid_to_fader=1;
 index_ask_confirm=1;
 }


  //Store Mover dans dock
 else if (  index_do_dock==1 && index_affect_to_dock_mover==1)
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_affect_mover=1;
 index_ask_confirm=1;
 }


 //draw
 else if(index_do_dock==1 && index_affect_draw_to_dock==1)
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 draw_preset_selected_for_order=draw_preset_selected;
 index_do_draw_affect_to_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
  //echo
 else if(index_do_dock==1 && index_affect_echo_to_dock==1)
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_affect_echo_to_dock=1;
 index_ask_confirm=1;
 mouse_released=1;
 }
//faire wave

 //modify
 else if( index_do_modify==1 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_modify_on_faders=1;
 index_ask_confirm=1;
 }


  //report
 if( index_do_report==1 && index_type==0 && index_do_dock==0 && index_do_modify==0 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_report_on_faders=1;
 index_ask_confirm=1;
 sprintf(string_Last_Order,"Report");
 }

 //nommage de dock
 else if( index_type==1 && index_do_dock==0 && index_do_report==0 && index_do_modify==0   && numeric_postext!=0 )
 {
 for(int tt=0;tt<24;tt++)
 {
 DockName[position_minifader_selected][dock_selected_is][tt]=numeric[tt];
 }
 DockName[position_minifader_selected][dock_selected_is][24]='\0';
 reset_numeric_entry();numeric_postext=0;
 if(index_text_auto_close==1){index_type=0;}
 sprintf(string_Last_Order,">>On Master %d GIVED A NAME FOR DOCK %d ", position_minifader_selected+1,dock_selected_is+1);
 }

  //clear
 else if(index_main_clear==1 )
 {
 fader_selected_for_record=position_minifader_selected;
 dock_selected_for_record=dock_selected_is;
 index_do_clear_dock=1;
 index_ask_confirm=1;
 }


refresh_minifader_state_view_core(position_minifader_selected);
}

//MANIP DU MINI FADER/////////////////////////////////////////////////////////////
if( mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg && mouse_y>(ymf+15+(lfad*hmfd))  && mouse_y<(ymf+20+127+(lfad*hmfd)) )
{

position_minifader_selected=cmptfader+(lfad*24);
refresh_minifader_state_view_core(cmptfader+(lfad*24));
if(index_inspekt==1){ //affichage qui dans dock si VIEW activé
show_who_is_in_dock( cmptfader+(lfad*24),   detect_dock_used(cmptfader+(lfad*24)));
}
set_mouse_range(xmf+(cmptfader*larg), ymf+20+(lfad*hmfd), xmf+(cmptfader*larg)+larg, ymf+20+127+(lfad*hmfd));//pour pas deborder
//click niveau fader
if( index_main_clear==0)
{
//NIVEAU
//Fader[cmptfader+(lfad*24)]=((ymf+127+20+(lfad*hmfd))-mouse_y)*2;
//midi_levels[cmptfader+(lfad*24)]=((ymf+127+20+(lfad*hmfd))-mouse_y);//desafffceté pour trouver pb

int val=((ymf+127+20+(lfad*hmfd))-mouse_y)*2;
fader_set_level(cmptfader+(lfad*24),val);
//if(Fader[cmptfader+(lfad*24)]>=254){Fader[cmptfader+(lfad*24)]=255;midi_levels[cmptfader+(lfad*24)]=127;}

//index_fader_is_manipulated[cmptfader+(lfad*24)]=1;
//if(midi_send_out[cmptfader+(lfad*24)]==1){ index_send_midi_out[cmptfader+(lfad*24)]=1;}
if(lfo_mode_is[cmptfader+(lfad*24)]==1 || lfo_mode_is[cmptfader+(lfad*24)]==2 || lfo_cycle_is_on[cmptfader+(lfad*24)]==1)
{
lfo_mode_is[cmptfader+(lfad*24)]=0; lfo_mode_is[cmptfader+(lfad*24)]=0; lfo_cycle_is_on[cmptfader+(lfad*24)]=0;
}
//CONFIG MIDI

if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_to_control(cmptfader+(lfad*24), Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
}
//NETTOYAGE DE FADER ET DOCK
if(index_main_clear==1)//clear de tous les dock du fader
{
 fader_selected_for_record=cmptfader+(lfad*24);
 index_do_clear_on_faders=1;
 index_ask_confirm=1;
 mouse_released=1  ;
}
}

//damper on off
if(mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg-5 && mouse_y>ymf+165+(lfad*hmfd) && mouse_y<ymf+173+(lfad*hmfd))
{
                    if(mouse_button==1 && mouse_released==0)
                    {
                    int fd=cmptfader+(lfad*24);
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
                        else { index_fader_is_manipulated[fd]=1;}
                        fader_damper_is_on[fd]=toggle(fader_damper_is_on[fd]);

                        }
                    mouse_released=1;
                    }

}

}//fin limitation nb faders user define
}//fin doublage des faders
}
////////FIN DES 48 POTARDS//////////////////////////////////////////////////////

return(0);
}
