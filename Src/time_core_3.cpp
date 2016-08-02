
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

* \file time_core_3.cpp
* \brief {Core fonctions for the time window}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Core fonctions pour la fenêtre time
*
*   Core fonctions for the time window
*
**/


int Chrono_PlayPause()
{
index_play_chrono=toggle(index_play_chrono);
return(0);
}


int do_logical_Time_Window(int xtime, int ytime, int timerayon)
{

//////////////////////ROUE DE TEMPS//////////////////////////////////////////////////////
//affectation midi

if( Midi_Faders_Affectation_Type!=0)
{
if(mouse_x>xtime+150  && mouse_x< xtime+150+100 && mouse_y>ytime+150 && mouse_y<ytime+150+100 )
 {
 //midi report
  switch(miditable[0][758])
  {
  case 0: sprintf(thetypinfo,"Note");break;
  case 1: sprintf(thetypinfo,"Key On");break;
  case 2: sprintf(thetypinfo,"Key Off");break;
  case 4: sprintf(thetypinfo,"Ctrl Change");break;
  default: break;
  }
  sprintf(string_last_midi_id,"TIMEWHEEL FADER is Ch: %d Pitch: %d Typ: %s" , miditable[1][758],miditable[2][758],thetypinfo);

  attribute_midi_solo_affectation(758,Midi_Faders_Affectation_Mode);
  mouse_released=1;
 }
}
/////////////////////////////////////////////////////////////////////////////////////////
if(index_play_chrono==0 )
{
for(time_angle = 0 ; time_angle <5.980005; time_angle+=0.01)//radians
{
   vtimex = cos(time_angle)*timerayon;
   vtimey = sin(time_angle)*timerayon;

   if(mouse_x>xtime+vtimex+150-15  && mouse_x< xtime+vtimex+150+15 && mouse_y>ytime+vtimey+150-15 && mouse_y<ytime+vtimey+150+15 )
   {

   actual_tickers_chrono=0;//reset du chrono
   angle_timesnap=time_angle;//angle rotation roue time
   position_curseur_time_x= xtime+150+vtimex;
   position_curseur_time_y=ytime+150+vtimey ;
   midi_levels[758]=(int)((angle_timesnap/5.980005)* 128);

   if(midi_send_out[758]==1){index_send_midi_out[758]=1;}

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

   }
}
}




//////////////////////////CHRONO//////////////////////////////////////////////////
//big chrono foreground

if(mouse_x>xtime+20 && mouse_x<xtime+30 && mouse_y>ytime+280 && mouse_y<ytime+290 && mouse_button==1 && mouse_released==0)
{
index_show_chrono=toggle(index_show_chrono);
mouse_released=1;
}

////////////////////////////////////////////////////////////////////////////////////
if(mouse_x>xtime+140-15 && mouse_x<xtime+140+15 && mouse_y>ytime+190-15 && mouse_y<ytime+190+15)
{

switch(miditable[0][765])
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
sprintf(string_last_midi_id,"ChronoPlay is Ch: %d Pitch: %d Typ: %s",miditable[1][765],miditable[2][765],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(765,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
Chrono_PlayPause();
mouse_released=1;
}
}

if(mouse_x>xtime+180-8 && mouse_x<xtime+180+8 && mouse_y>ytime+200-8 && mouse_y<ytime+200+8)
{

switch(miditable[0][766])
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
sprintf(string_last_midi_id,"ChronoReset is Ch: %d Pitch: %d Typ: %s",miditable[1][766],miditable[2][766],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(766,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
Chrono_Reset();
mouse_released=1;
}
}

///////////////////////CHOIX DE SELECTION ROUE= SECONDES ou MINUTES ou HEURES


if(mouse_x>xtime+120 && mouse_x<xtime+180 && mouse_y>ytime+80 && mouse_y<ytime+100)
{

switch(miditable[0][759])
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
sprintf(string_last_midi_id,"TimeType is Ch: %d Pitch: %d Typ: %s",miditable[1][759],miditable[2][759],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(759,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
time_wheel_datatype_is++;
if(time_wheel_datatype_is>2){time_wheel_datatype_is=0;}
set_time_cursor_to_time_type(time_wheel_datatype_is);
mouse_released=1;
}
}



/////////////////////////CASES D' AFFECTATION AUX DOCK ET MEMOIRES

//la selection des modes de temps in out din dout
if(mouse_x>xtime+300 && mouse_x<xtime+350)
{
//DIN
if(mouse_y>ytime+120 && mouse_y<ytime+150)
{

switch(miditable[0][760])
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
sprintf(string_last_midi_id,"DelayIn Button is Ch: %d Pitch: %d Typ: %s",miditable[1][760],miditable[2][760],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(760,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_type_of_time_to_affect[0]==0){index_type_of_time_to_affect[0]=1;}
else if(index_type_of_time_to_affect[0]==1){index_type_of_time_to_affect[0]=0;}
mouse_released=1;
}
}
//IN
if(mouse_y>ytime+20 && mouse_y<ytime+50)
{

switch(miditable[0][761])
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
sprintf(string_last_midi_id,"In Button is Ch: %d Pitch: %d Typ: %s",miditable[1][761],miditable[2][761],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(761,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_type_of_time_to_affect[1]==0){index_type_of_time_to_affect[1]=1;}
else if(index_type_of_time_to_affect[1]==1){index_type_of_time_to_affect[1]=0;}
mouse_released=1;
}
}
//DOUT
if(mouse_y>ytime+170 && mouse_y<ytime+200)
{

switch(miditable[0][762])
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
sprintf(string_last_midi_id,"DelayOut Button is Ch: %d Pitch: %d Typ: %s",miditable[1][762],miditable[2][762],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(762,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_type_of_time_to_affect[2]==0){index_type_of_time_to_affect[2]=1;}
else if(index_type_of_time_to_affect[2]==1){index_type_of_time_to_affect[2]=0;}
mouse_released=1;
}
}
//OUT
if(mouse_y>ytime+70 && mouse_y<ytime+100)
{

switch(miditable[0][763])
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
sprintf(string_last_midi_id,"Out Button is Ch: %d Pitch: %d Typ: %s",miditable[1][763],miditable[2][763],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(763,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_type_of_time_to_affect[3]==0){index_type_of_time_to_affect[3]=1;}
else if(index_type_of_time_to_affect[3]==1){index_type_of_time_to_affect[3]=0;}
mouse_released=1;
}
}
}

///TAP TEMPO sending
if(mouse_x>xtime+265 && mouse_x<xtime+265+15 && mouse_y>ytime+210 && mouse_y<ytime+210+15)
{

switch(miditable[0][1328])
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
sprintf(string_last_midi_id,"Send Tap is Ch: %d Pitch: %d Typ: %s",miditable[1][1328],miditable[2][1328],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(1328,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(numeric_postext==0 && index_window_chasers==1)
            {
            set_chaser_tempo_unit(chaser_selected);
            }
            else//si chiffre de chaser tapé
            {
            int chazr=atoi(numeric);
            if(chazr>0 && chazr<128)
            {
            set_chaser_tempo_unit(chazr-1);
            numeric_postext=0;
            reset_numeric_entry();
            }
            }
            mouse_released=1;
do_light_send_tap=1;
}

}



///TAP TEMPO reoording
if(mouse_x>xtime+285 && mouse_x<xtime+285+15 && mouse_y>ytime+210 && mouse_y<ytime+210+15)
{

switch(miditable[0][1327])
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
sprintf(string_last_midi_id,"Record Tap is Ch: %d Pitch: %d Typ: %s",miditable[1][1327],miditable[2][1327],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(1327,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
index_recording_tap_tempo=toggle(index_recording_tap_tempo);
if(index_recording_tap_tempo==1)
{
start_tempo_ticks=actual_time;nbr_steps_tempo=0;tempo_interm=0;
sprintf(string_tap_tempo_average,"Step:   -    Global: -");
sprintf(string_actual_tap_tempo,"Last: ");
sprintf(string_Last_Order,"Tap Tempo Rec ON");
}
else{sprintf(string_Last_Order,"Tap Tempo Rec Off");}
mouse_released=1;
}


}


//tap button tempo
if(mouse_x>xtime+310 && mouse_x<xtime+310+40 && mouse_y>ytime+210 && mouse_y<ytime+210+30)
{

switch(miditable[0][1326])
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
sprintf(string_last_midi_id,"Tap Tempo is Ch: %d Pitch: %d Typ: %s",miditable[1][1326],miditable[2][1326],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(1326,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
set_new_time_in_tap_tempo();
mouse_released=1;
}
}


//AFFECT TIME
if(mouse_x>xtime+280 && mouse_x<xtime+350 && mouse_y>ytime+260 && mouse_y<ytime+290)
{

switch(miditable[0][764])
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
sprintf(string_last_midi_id,"Affect Time Button is Ch: %d Pitch: %d Typ: %s",miditable[1][764],miditable[2][764],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(764,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(index_affect_time==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_affect_time=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_affect_time;
mouse_released=1;
}
}


button_midi_out_core( xtime+250, ytime+250,758);

return(0);
}

