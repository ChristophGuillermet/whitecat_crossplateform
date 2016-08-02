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

* \file list_proj_core.cpp
* \brief {spot list and channels macro core}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions core pour gérer le menu list des projos et channels macro
*
*   Core fonctions for the spot list menu and macro channels
*
 **/

int do_the_macro_of_the_channel(int the_chan, int num_macro)
{
int the_Abanger_num=0;

switch(channel_macro_action[the_chan][num_macro])
{
case 0://-
break;
case 1://Bang Banger
the_Abanger_num=channel_macro_val[the_chan][num_macro][1]-1;
start_time_for_banger[the_Abanger_num]=actual_time;
//4 aout 2010 initalisation  un temps plus long par defaut pour faire partir mes évènements
end_time_for_banger[the_Abanger_num]=default_time_of_the_bang;
//reset du banger concerné
for (int o=0;o<6;o++)//reset des évènements
{
event_sended[the_Abanger_num][o]=0;
if(bangers_delay[the_Abanger_num][o]>end_time_for_banger[the_Abanger_num])
{end_time_for_banger[the_Abanger_num]=bangers_delay[the_Abanger_num][o];}
}
bang_is_sended[the_Abanger_num]=0;//reset du bang sended is
break;
case 2://Load Audio
if(channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8 )//follow pur
{
switch(dmx_view)
{
case 0:
audiofile_selected=(int)(((float)MergerArray[the_chan])/2.55);
if(channel_macro_reaction[the_chan][num_macro]==8){audiofile_selected=100-(int)(((float)MergerArray[the_chan])/2.55);}
if(audiofile_selected<0){audiofile_selected=0;}
if(audiofile_selected>100){audiofile_selected=100;}
break;
case 1:
audiofile_selected=MergerArray[the_chan];
if(channel_macro_reaction[the_chan][num_macro]==8){audiofile_selected=127-audiofile_selected;}
if(audiofile_selected<0){audiofile_selected=0;}
if(audiofile_selected>127){audiofile_selected=127;}
break;
default: break;
}
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
AffectSoundFile(channel_macro_val[the_chan][num_macro][1]-1);
}


break;
case 3://Play A.Pl
if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1)
{
switch(channel_macro_val[the_chan][num_macro][1]-1)
{
case 0://PLAYER 1
 player1->play();
break;
case 1://PLAYER 2
 player2->play();
break;
case 2://PLAYER 3
 player3->play();
break;
case 3://PLAYER 4
 player4->play();
break;
default:
break;
}
}
break;
case 4://Stop A.Pl
if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1)
{
switch(channel_macro_val[the_chan][num_macro][1]-1)
{
case 0://PLAYER 1
 player1->stop();
break;
case 1://PLAYER 2
 player2->stop();
break;
case 2://PLAYER 3
 player3->stop();
break;
case 3://PLAYER 4
 player4->stop();
break;
default:
break;
}
}
break;
case 5://Seek A.Pl
if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1)
{
switch(channel_macro_val[the_chan][num_macro][1]-1)
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
}
break;
case 6://Loop ON A.Pl
if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1)
{
switch(channel_macro_val[the_chan][num_macro][1]-1)
{
case 0://PLAYER 1
 player1->setRepeat(true);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=1;
break;
case 1://PLAYER 2
 player2->setRepeat(true);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=1;
break;
case 2://PLAYER 3
 player3->setRepeat(true);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=1;
break;
case 3://PLAYER 4
 player4->setRepeat(true);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=1;
break;
default: break;
}
}
break;
case 7://Loop Off A.Pl
if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1)
{
switch(channel_macro_val[the_chan][num_macro][1]-1)
{
case 0://PLAYER 1
 player1->setRepeat(false);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=0;
break;
case 1://PLAYER 2
 player2->setRepeat(false);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=0;
break;
case 2://PLAYER 3
 player3->setRepeat(false);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=0;
break;
case 3://PLAYER 4
 player4->setRepeat(false);
 player_is_onloop[channel_macro_val[the_chan][num_macro][1]-1]=0;
break;
default: break;
}
}
break;
case 8://Volume A.Pl
if(channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8 )//follow pur
{
float lev_to_do=((float)MergerArray[the_chan])/255.0;

if(channel_macro_reaction[the_chan][num_macro]==8)
{
lev_to_do=127.0-lev_to_do;
}
if(lev_to_do>1.0){lev_to_do=1.0;}
else if(lev_to_do<0.0){lev_to_do=0.0;}

     if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1 && index_loading_a_sound_file==0)
     {
     switch(channel_macro_val[the_chan][num_macro][1]-1)
     {
     case 0:
     player1->setVolume(lev_to_do);
     break;
     case 1:
     player2->setVolume(lev_to_do);
     break;
     case 2:
     player3->setVolume(lev_to_do);
     break;
     case 3:
     player4->setVolume(lev_to_do);
     break;
     default: break;
     }
     player_niveauson[channel_macro_val[the_chan][num_macro][1]-1]=(int)(lev_to_do*127);
     midi_levels[616+channel_macro_val[the_chan][num_macro][1]-1]=(int)(lev_to_do*127);
     if(midi_send_out[616+channel_macro_val[the_chan][num_macro][1]-1]==1)
     { index_send_midi_out[616+channel_macro_val[the_chan][num_macro][1]-1]=1;}//vol
     }
}
break;
case 9://Pan A.Pl
if(channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8  )//follow pur
{
float pitc_to_do=(((float)MergerArray[the_chan])/255.0)*127.0;

if(channel_macro_reaction[the_chan][num_macro]==8)
{
pitc_to_do=127.0-pitc_to_do;
}

if(pitc_to_do>127.0){pitc_to_do=127.0;}
else if(pitc_to_do<0.0){pitc_to_do=0.0;}

if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1 && index_loading_a_sound_file==0)
{
     switch(channel_macro_val[the_chan][num_macro][1]-1)
     {
     case 0:
     player1->setPan((pitc_to_do-64)/64);

     break;
     case 1:
     player2->setPan((pitc_to_do-64)/64);
     break;
     case 2:
     player3->setPan((pitc_to_do-64)/64);
     break;
     case 3:
     player4->setPan((pitc_to_do-64)/64);
     break;
     default: break;
     }
     player_pan[channel_macro_val[the_chan][num_macro][1]-1]=(int)(pitc_to_do);
     midi_levels[620+channel_macro_val[the_chan][num_macro][1]-1]=(int)(pitc_to_do);
     if(midi_send_out[620+channel_macro_val[the_chan][num_macro][1]-1]==1)
     { index_send_midi_out[620+channel_macro_val[the_chan][num_macro][1]-1]=1;}//vol
}
}
break;
case 10://Pitch A.Pl
if(channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8 )//follow pur
{
float pitc_to_do=0.0;

pitc_to_do=(((float)MergerArray[the_chan])/255.0)*127.0;

if(channel_macro_reaction[the_chan][num_macro]==8)
{
pitc_to_do=127.0-pitc_to_do;
}


if(pitc_to_do>127.0){pitc_to_do=127.0;}
else if(pitc_to_do<0.0){pitc_to_do=0.0;}

if(player_ignited[channel_macro_val[the_chan][num_macro][1]-1]==1 && index_loading_a_sound_file==0)
{
     switch(channel_macro_val[the_chan][num_macro][1]-1)
     {
     case 0:
     player1->setPitchShift(pitc_to_do/64);

     break;
     case 1:
     player2->setPitchShift(pitc_to_do/64);
     break;
     case 2:
     player3->setPitchShift(pitc_to_do/64);
     break;
     case 3:
     player4->setPitchShift(pitc_to_do/64);
     break;
     default: break;
     }
     player_pitch[channel_macro_val[the_chan][num_macro][1]-1]=(int)(pitc_to_do);
     midi_levels[624+channel_macro_val[the_chan][num_macro][1]-1]=(int)(pitc_to_do);
     if(midi_send_out[624+channel_macro_val[the_chan][num_macro][1]-1]==1)
     { index_send_midi_out[624+channel_macro_val[the_chan][num_macro][1]-1]=1;}//vol
}

}
break;
case 11://Midi Ch15 CC
if(channel_macro_reaction[the_chan][num_macro]==8)
{
send_immidiateley_my_midi_cc(4,15,channel_macro_val[the_chan][num_macro][1],(127-(int)((float)MergerArray[the_chan])/2));
}
else
{
send_immidiateley_my_midi_cc(4,15,channel_macro_val[the_chan][num_macro][1],((int)((float)MergerArray[the_chan])/2));
}
break;
case 12://Midi Ch15 KOn
if(channel_macro_reaction[the_chan][num_macro]==8)
{
send_my_midi_note(1, 15, channel_macro_val[the_chan][num_macro][1], (127-(int)((float)MergerArray[the_chan])/2), 10);
}
else
{
send_my_midi_note(1, 15, channel_macro_val[the_chan][num_macro][1], ((int)((float)MergerArray[the_chan])/2), 10);
}
break;
case 13://Midi Ch15 KOff
if(channel_macro_reaction[the_chan][num_macro]==8)
{
send_my_midi_note(2, 15, channel_macro_val[the_chan][num_macro][1], (127-(int)((float)MergerArray[the_chan])/2), 10);
}
else
{
send_my_midi_note(2, 15, channel_macro_val[the_chan][num_macro][1], ((int)((float)MergerArray[the_chan])/2), 10);
}
break;
case 14://FADER LEVEL
if((channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8) && channel_macro_val[the_chan][num_macro][1]>0 && channel_macro_val[the_chan][num_macro][1]<49 )//follow pur
{
int num_f=(channel_macro_val[the_chan][num_macro][1]-1);
fader_set_level(num_f,MergerArray[the_chan]);
//Fader[ num_f]=MergerArray[the_chan]; // original
midi_levels[ num_f]=(int)(MergerArray[the_chan]/2);
if(channel_macro_reaction[the_chan][num_macro]==8)
{
//Fader[ num_f]=255-Fader[ num_f]; //original
fader_set_level(num_f,255-Fader[ num_f]);
midi_levels[ num_f]=127-midi_levels[ num_f];
}

if(midi_send_out[num_f]==1)
{ index_send_midi_out[num_f]=1;}
}
break;
case 15://FADER SPEED
if((channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8) && channel_macro_val[the_chan][num_macro][1]>0 && channel_macro_val[the_chan][num_macro][1]<49 )//follow pur
{
int num_f=(channel_macro_val[the_chan][num_macro][1]-1);
lfo_speed[ num_f]=(int)(MergerArray[the_chan]/2);
midi_levels[196+ num_f]=(int)(MergerArray[the_chan]/2);
if(channel_macro_reaction[the_chan][num_macro]==8)
{
lfo_speed[ num_f]=127-lfo_speed[ num_f];
midi_levels[ num_f]=127-midi_levels[ num_f];
}

if(midi_send_out[196+num_f]==1)
{ index_send_midi_out[196+num_f]=1;}
}
break;
case 16:// Follow Channel
chan_to_manipulate=channel_macro_val[the_chan][num_macro][0];
if((channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8)
&& channel_macro_val[the_chan][num_macro][0]>0 && channel_macro_val[the_chan][num_macro][0]<512
&& channel_macro_val[the_chan][num_macro][1]>0 && channel_macro_val[the_chan][num_macro][1]<49 )//follow pur
{
int num_f=(channel_macro_val[the_chan][num_macro][1]-1);
FaderDockContains[num_f][(dock_used_by_fader_is[num_f])][chan_to_manipulate] = MergerArray[the_chan];
if(channel_macro_reaction[the_chan][num_macro]==8)
{
FaderDockContains[num_f][(dock_used_by_fader_is[num_f])][chan_to_manipulate] = 255-MergerArray[the_chan];
}
}
break;
case 17://follow on seq  with ratio
chan_to_manipulate=channel_macro_val[the_chan][num_macro][0];
if((channel_macro_reaction[the_chan][num_macro]==7 || channel_macro_reaction[the_chan][num_macro]==8)
&& channel_macro_val[the_chan][num_macro][0]>0 && channel_macro_val[the_chan][num_macro][0]<512
)//follow pur
{
bufferSaisie[chan_to_manipulate] =(unsigned char) (((float)(MergerArray[the_chan])/100) * channel_macro_val[the_chan][num_macro][1]) ;
if(channel_macro_reaction[the_chan][num_macro]==8)
{
bufferSaisie[chan_to_manipulate] = (unsigned char) (255-((float)(MergerArray[the_chan])/100) * channel_macro_val[the_chan][num_macro][1]) ;
}
}
break;
default:
break;
}

return(0);
}




int do_channels_macro()
{
for(int i=1;i<513;i++)
{

  for(int evo=0;evo<4;evo++)
  {
    if(macro_channel_on[i][evo]==1 && MergerArray[i]!=previous_state_of_outputted_channels[i])
    {
   bool is_ok_for_condition=0;
   switch(channel_macro_reaction[i][evo])//condition
   {
   case 0:
   //nothing
   break;
   case 1://>=
   if(MergerArray[i]>=channel_macro_val[i][evo][0] ){is_ok_for_condition=1;}
   break;
   case 2://>
    if(MergerArray[i]>channel_macro_val[i][evo][0] ){is_ok_for_condition=1;}
   break;
   case 3://==
    if(MergerArray[i]==channel_macro_val[i][evo][0] ){is_ok_for_condition=1;}
   break;
   case 4://!=
    if(MergerArray[i]!=channel_macro_val[i][evo][0] ){is_ok_for_condition=1;}
   break;
   case 5://<=
    if(MergerArray[i]<=channel_macro_val[i][evo][0] ){is_ok_for_condition=1;}
   break;
   case 6://<
    if(MergerArray[i]<channel_macro_val[i][evo][0] ){is_ok_for_condition=1;}
   break;
   case 7://Follow
   is_ok_for_condition=1;
   break;
   case 8://Follow inv
   is_ok_for_condition=1;
   break;
   default:
   break;
   }
   if(is_ok_for_condition==1)
   {
   do_the_macro_of_the_channel(i,evo);
   sprintf(string_Last_Order,"Channel %d: Macro %d !",i, evo+1);
   }
     //fin macro on et diff  d etat
   }
    //fin check macro on   x 4
  }
  previous_state_of_outputted_channels[i]=MergerArray[i];//stockage pour declenchements
}
//fin 512 circuits

return(0);
}



int Channel_macros_core(int xlist, int ylist)
{
int temp_mini;
int temp_limit;
if(index_edit_listproj==1 && mouse_released==0 && window_focus_id==914 && last_ch_selected!=0)
{
for(int i=0;i<nbre_macros_per_channel;i++)
{
if( mouse_y>ylist+25+(25*i) && mouse_y<ylist+25+(25*i)+20 )
{

//comportement
if(mouse_x>xlist && mouse_x<xlist+80  )
{
if(channel_macro_reaction[last_ch_selected][i]<max_channel_macro_reaction)
{channel_macro_reaction[last_ch_selected][i]++;}
else {channel_macro_reaction[last_ch_selected][i]=0;}
mouse_released=1;
}

//Val 1
else if(mouse_x>xlist+90 && mouse_x<xlist+90+40 )
{

int temp_val=atoi(numeric);

if(channel_macro_reaction[last_ch_selected][i]<7)
{
switch(dmx_view)
{
case 0:
if(temp_val>=0 && temp_val<=100)
{
channel_macro_val[last_ch_selected][i][0]=(int)((temp_val *2.55) +1);
if(channel_macro_val[last_ch_selected][i][0]==1){channel_macro_val[last_ch_selected][i][0]=0;}
reset_numeric_entry();
}
break;
case 1:
if(temp_val>=0 && temp_val<=255)
{
channel_macro_val[last_ch_selected][i][0]=temp_val;
reset_numeric_entry();
}
break;
default: break;
}
}

else if(channel_macro_reaction[last_ch_selected][i]>=7) //follow channel
{
temp_mini=1;
temp_limit=512;
if(temp_val>=temp_mini && temp_val<=temp_limit)
{
channel_macro_val[last_ch_selected][i][0]=temp_val;
reset_numeric_entry();
}
}

mouse_released=1;
}

//action
else if(mouse_x>xlist+140 && mouse_x<xlist+140+80  )
{
if(channel_macro_action[last_ch_selected][i]<max_channel_macro_action)
{channel_macro_action[last_ch_selected][i]++;}
else {channel_macro_action[last_ch_selected][i]=0;}
mouse_released=1;
}


//valeur 2
else if(mouse_x>xlist+230 && mouse_x<xlist+230+40 )
{
int temp_val=atoi(numeric);
switch(channel_macro_action[last_ch_selected][i])
{
case 0:
break;
case 1:
temp_mini=1;
temp_limit=127;
break;
case 2:
temp_mini=1;
temp_limit=4;
break;
case 3:
temp_mini=1;
temp_limit=4;
break;
case 4:
temp_mini=1;
temp_limit=4;
break;
case 5:
temp_mini=1;
temp_limit=4;;
break;
case 6:
temp_mini=1;
temp_limit=4;
break;
case 7:
temp_mini=1;
temp_limit=4;
break;
case 8:
temp_mini=1;
temp_limit=4;
break;
case 9:
temp_mini=1;
temp_limit=4;
break;
case 10:
temp_mini=0;
temp_limit=127;
break;
case 11:
temp_mini=0;
temp_limit=127;
break;
case 12:
temp_mini=0;
temp_limit=127;
break;
case 13:
temp_mini=0;
temp_limit=127;
break;
case 14:
temp_mini=1;
temp_limit=48;
break;
case 15:
temp_mini=1;
temp_limit=48;
break;
case 16:
temp_mini=1;
temp_limit=48;
break;
case 17:
temp_mini=1;
temp_limit=100;
break;
default:
break;
}
if(temp_val>=temp_mini&& temp_val<=temp_limit)
{
channel_macro_val[last_ch_selected][i][1]=temp_val;
reset_numeric_entry();
}
mouse_released=1;
}

//on off de la macro
if(mouse_x>xlist+280 && mouse_x<xlist+280+35  )
{
macro_channel_on[last_ch_selected][i]=toggle(macro_channel_on[last_ch_selected][i]);
mouse_released=1;
}

}

}
}
return(0);
}



int do_logical_liste_projecteurs(int xlist,int ylist)
{


for(int co=1;co<List_view_nbre_channels;co++)
{
if(mouse_x>(xlist+60) && mouse_x<(xlist+60)+185 && mouse_y>(ylist+50+(25*co))-15 && mouse_y<(ylist+50+(25*co)+8))
{
if(co+line_list_is<513)
{

if(index_type==1 && index_edit_listproj==1)
{
for(int tt=0;tt<24;tt++)
{
descriptif_projecteurs[co+line_list_is][tt]=numeric[tt];
}
descriptif_projecteurs[co+line_list_is][24]='\0';
reset_numeric_entry();
if(index_text_auto_close==1){index_type=0;}

//MAJ d'un fader en DCH
for(int fa=0;fa<48;fa++)
{
for(int dk=0;dk<6;dk++)
{
if( DockTypeIs[fa][dk]==10 && FaderDirectChan[fa][dk]==co+line_list_is)
{
sprintf(DockName[fa][dk],descriptif_projecteurs[last_ch_selected]);
}
}
}
mouse_released=1;
}
else
{
if(index_level_attribue==1)//pour déselection auto
{
for(int y=1;y<512;y++)
{
Selected_Channel[y]=0;
last_ch_selected=0;
}
index_level_attribue=0;
if(index_plot_window==1){substract_channel_selection_to_layers_plot();}
}

 if (index_ch_thruth==0)//selection normale
 {
Selected_Channel[co+line_list_is]=1-(Temp_Selected_Channel[co+line_list_is]); //chainage mouse released sorti
last_ch_selected=co+line_list_is;
 if(index_plot_window==1){add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();}
 }
else if (index_ch_thruth==1)//selection thruth
 {
 Channel_select_thruth(last_ch_selected,co+line_list_is);
 index_ch_thruth=0;
  if(index_plot_window==1){add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();}
 mouse_released=1;
 }
}
}
}
}

if(mouse_x>xlist+290 && mouse_x<xlist+330)
{

//edit
 if( mouse_y>ylist+16 && mouse_y<ylist+36)
 {

  index_edit_listproj=toggle(index_edit_listproj);
  mouse_released=1;
 }
//-
 if( mouse_y>ylist+51 && mouse_y<ylist+71)
 {
  line_list_is-=1;
  if(line_list_is<0) {line_list_is=0;  }
  mouse_released=1;
  }

//+
 if( mouse_y>ylist+81 && mouse_y<ylist+101)
 {
  if(line_list_is<513){line_list_is+=1;  }
  if(line_list_is>513) {line_list_is=513;  }
  mouse_released=1;
  }
}
//ascenceur
if(mouse_x>xlist+270 && mouse_x<xlist+330 && mouse_y>ylist+145 && mouse_y<ylist+150)
{

line_list_is=((mouse_y-ylist-146)/5);
}

else if( mouse_x>xlist+270 && mouse_x<xlist+330 && mouse_y>=ylist+150 && mouse_y<ylist+407)
{
line_list_is=(mouse_y-ylist-149)*2;
if(line_list_is<1){line_list_is=1;}
else if(line_list_is>513){line_list_is=513;}
}


Channel_macros_core(xlist+10,ylist+470);


 return(0);
}
