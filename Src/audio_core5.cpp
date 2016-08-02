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

* \file audio_core5.cpp
* \brief {Audio fonctions}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gestion des fonctions Audio
*
*   Audio core fonctions
*
 **/

int Load_audiofiles_cues()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused int it=0;
    char tmp_audio_f[512];
    sprintf(tmp_audio_f,"audio\\%s\\audio_cues_in_out.txt",audio_folder);
	cfg_file = fopen(tmp_audio_f, "rt" );

	if( !cfg_file )
	{	 sprintf(string_save_load_report[idf],"Error on opening %s",tmp_audio_f); b_report_error[idf]=1;	}

	else
    {
         sprintf(string_save_load_report[idf],"audio_cues_in_out.txt opened");
     //premiere ligne les args
        if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	    {sprintf(string_save_load_report[idf],"Error on reading audio_cues_in_out.txt");b_report_error[idf]=1;}

        else {

             //sab 02/03/2014 unused char *tremp;
             int temp_ain[128];
             int temp_aout[128];
             int index_af=0;
             bool index_stop=0;
             for(int u=0;u<127;u++)
             {
	         fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file );
             char tmp_name_f[72];
             sscanf(read_buff_winfil , "%s / %d / %d\n" ,  tmp_name_f,&temp_ain[index_af],&temp_aout[index_af] );

             for(int po=0;po<127;po++)
             {
             if(strcmp(list_audio_files[po],tmp_name_f)==0 && index_stop==0)
             {
             audiofile_cue_in_out_pos[po][0]=temp_ain[index_af];
             audiofile_cue_in_out_pos[po][1]=temp_aout[index_af];
             index_stop=1;index_af++;
             }
             }
             index_stop=0;
             }
     }
    sprintf(string_save_load_report[idf],"audio_cues_in_out.txt readed");
    fclose( cfg_file );
}


return(0);
}

int AffectSoundFile(int player)
{
index_loading_a_sound_file=1;
sprintf(sound_files[player],audiofile_name);
player_has_file_coming_from_pos[player]=audiofile_selected;

switch(player)
{
case 0:
//christoph 14/04/14 avoiding clippling on stop
if(player_is_playing[player]==1){player_ignited[player]=1;player1_do_stop();}
player1=0;
sprintf(soundfile_temp_loader,"audio\\%s\\%s",audio_folder,sound_files[player]);
player1=OpenSound(device,soundfile_temp_loader, index_preloaded_sounds);
if (!player1)
{
sprintf (string_Last_Order,"Can't load Sound %s  !",sound_files[player]);
player_ignited[player]=0; player_is_playing[player]=0;//christoph 11/12/14 bug d.guesdon
}
else
{
player_ignited[player]=1;
if(player_is_playing[player]==1)
{
//christoph 14/04/14 avoiding clippling on stop
// player1->stop();
player1->setPosition(0);player1->play(); }
length_of_file_in_player[player]=(player1->getLength());
player_loop_out_position[player]=length_of_file_in_player[player];
player1->setVolume(((float)player_niveauson[player])/127);
switch(player_is_onloop[player])
 {
 case 0:
 player1->setRepeat(false);
 break;
 case 1:
 player1->setRepeat(true);
 break;
 default: break;
 }
}
break;
case 1:
//christoph 14/04/14 avoiding clippling on stop
if(player_is_playing[player]==1){player_ignited[player]=1;player2_do_stop();}
player2=0;
sprintf(soundfile_temp_loader,"audio\\%s\\%s",audio_folder,sound_files[player]);
player2=OpenSound(device,soundfile_temp_loader, index_preloaded_sounds);
if (!player2)
{
sprintf (string_Last_Order,"Can't load Sound %s  !",sound_files[player]);
player_ignited[player]=0;player_is_playing[player]=0;//christoph 11/12/14 bug d.guesdon

}
else {
player_ignited[player]=1;
if(player_is_playing[player]==1)
{
//christoph 14/04/14 avoiding clippling on stop
//player2->stop();
player2->setPosition(0);player2->play();
}
length_of_file_in_player[player]=(player2->getLength());
player_loop_out_position[player]=length_of_file_in_player[player];
player2->setVolume(((float)player_niveauson[player])/127);
switch(player_is_onloop[player])
 {
 case 0:
 player2->setRepeat(false);
 break;
 case 1:
 player2->setRepeat(true);
 break;
 default: break;
 }
}
break;
case 2:
//christoph 14/04/14 avoiding clippling on stop
if(player_is_playing[player]==1){player_ignited[player]=1;player3_do_stop();}
player3=0;
sprintf(soundfile_temp_loader,"audio\\%s\\%s",audio_folder,sound_files[player]);
player3=OpenSound(device,soundfile_temp_loader, index_preloaded_sounds);
if (!player3)
{
sprintf (string_Last_Order,"Can't load Sound %s  !",sound_files[player]);
player_ignited[player]=0;player_is_playing[player]=0;//christoph 11/12/14 bug d.guesdon
}
else {
player_ignited[player]=1;
if(player_is_playing[player]==1)
    {
//christoph 14/04/14 avoiding clippling on stop
//   player3->stop();
player3->setPosition(0);player3->play();
}
length_of_file_in_player[player]=(player3->getLength());
player_loop_out_position[player]=length_of_file_in_player[player];
player3->setVolume(((float)player_niveauson[player])/127);
switch(player_is_onloop[player])
 {
 case 0:
 player3->setRepeat(false);
 break;
 case 1:
 player3->setRepeat(true);
 break;
 default: break;
 }
}
break;
case 3:
//christoph 14/04/14 avoiding clippling on stop
if(player_is_playing[player]==1){player_ignited[player]=1;player4_do_stop();}
player4=0;
sprintf(soundfile_temp_loader,"audio\\%s\\%s",audio_folder,sound_files[player]);
player4=OpenSound(device,soundfile_temp_loader, index_preloaded_sounds);
if (!player4)
{
sprintf (string_Last_Order,"Can't load Sound %s  !",sound_files[player]);
player_ignited[player]=0;player_is_playing[player]=0;//christoph 11/12/14 bug d.guesdon
}
else {
player_ignited[player]=1;
if(player_is_playing[player]==1)
{
//christoph 14/04/14 avoiding clippling on stop
//player4->stop();
player4->setPosition(0);player4->play();
}
length_of_file_in_player[player]=(player4->getLength());
player_loop_out_position[player]=length_of_file_in_player[player];
player4->setVolume(((float)player_niveauson[player])/127);
switch(player_is_onloop[player])
 {
 case 0:
 player4->setRepeat(false);
 break;
 case 1:
 player4->setRepeat(true);
 break;
 default: break;
 }
}
break;
default:
break;
}
if(player_ignited[player]==1)
{
//init cue in out
if(audiofile_cue_in_out_pos[audiofile_selected][0]<length_of_file_in_player[player])
{
player_seek_position[player]=audiofile_cue_in_out_pos[audiofile_selected][0];
 if(audiofile_cue_in_out_pos[audiofile_selected][1]>audiofile_cue_in_out_pos[audiofile_selected][0])
 {
 player_loop_out_position[player]=audiofile_cue_in_out_pos[audiofile_selected][1];
        if(player_loop_out_position[player]>length_of_file_in_player[player])
        {
        player_loop_out_position[player]=length_of_file_in_player[player];
        }
  }
}
}
index_loading_a_sound_file=0;//permet le rafraichissement des dixièmes

return(0);
}

int do_audio_midi_function_next_prev_track()//christoph 22/04/14
{
for (int i=0;i<4;i++)
{
//prev track
if(audio_do_load_midi_prev_file[i]==1)
{
index_loading_a_sound_file=1;
audiofile_selected=player_has_file_coming_from_pos[i]-1;
if(audiofile_selected<1){audiofile_selected=1;}
player_has_file_coming_from_pos[i]=audiofile_selected;
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(i);
}
audio_do_load_midi_prev_file[i]=0;
index_loading_a_sound_file=0;
}
//next track
if(audio_do_load_midi_next_file[i]==1)
{
index_loading_a_sound_file=1;
audiofile_selected=player_has_file_coming_from_pos[i]+1;
if(audiofile_selected>=audio_number_total_in_folder){audiofile_selected=audio_number_total_in_folder;}
player_has_file_coming_from_pos[i]=audiofile_selected;
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(i);
}
audio_do_load_midi_next_file[i]=0;
index_loading_a_sound_file=0;
}
}


return(0);
}

int sound_core_processing()
{

for(int lect=0;lect<4;lect++)
{
if(player_ignited[lect]==1)
{

switch(lect)
 {
 case 0:
 position_of_file_in_player[lect]=(player1->getPosition());
 show_pitch_value[lect]=(player1->getPitchShift());
 show_pan_value[lect]=(player1->getPan());
 show_player_niveauson[lect]=(player1->getVolume());
 player_is_playing[lect]=(player1->isPlaying());
 break;
 case 1:
 position_of_file_in_player[lect]=(player2->getPosition());
 show_pitch_value[lect]=(player2->getPitchShift());
 show_pan_value[lect]=(player2->getPan());
 show_player_niveauson[lect]=(player2->getVolume());
 player_is_playing[lect]=(player2->isPlaying());
 break;
 case 2:
 position_of_file_in_player[lect]=(player3->getPosition());
 show_pitch_value[lect]=(player3->getPitchShift());
 show_pan_value[lect]=(player3->getPan());
 show_player_niveauson[lect]=(player3->getVolume());
 player_is_playing[lect]=(player3->isPlaying());
 break;
 case 3:
 position_of_file_in_player[lect]=(player4->getPosition());
 show_pitch_value[lect]=(player4->getPitchShift());
 show_pan_value[lect]=(player4->getPan());
 show_player_niveauson[lect]=(player4->getVolume());
 player_is_playing[lect]=(player4->isPlaying());
 break;
 default:
 break;
}

if( player_is_onloop[lect]==1 && player_is_playing[lect]==1 )
{
 if(player_is_onloopCue[lect]==0  && position_of_file_in_player[lect]>=length_of_file_in_player[lect] )
 {//loop  GENERAL
 switch(lect)
 {
 case 0:
 player1->setPosition(0);
 break;
  case 1:
 player2->setPosition(0);
 break;
 case 2:
 player3->setPosition(0);
 break;
 case 3:
 player4->setPosition(0);
 break;
 default:
 break;
 }
 }
 else if( player_is_onloopCue[lect]==1 && position_of_file_in_player[lect]>=player_loop_out_position[lect])
 {//loop out point to inpoint
 switch(lect)
 {
 case 0:
 player1->setPosition(player_seek_position[lect]);
 break;
 case 1:
 player2->setPosition(player_seek_position[lect]);
 break;
 case 2:
 player3->setPosition(player_seek_position[lect]);
 break;
 case 3:
 player4->setPosition(player_seek_position[lect]);
 break;
 default:
 break;
 }
 }
 }

//PAS DE LOOP
if( player_is_onloop[lect]==0)
{
if(position_of_file_in_player[lect]>=length_of_file_in_player[lect])
{
if(audio_autoload[lect]==0 && audio_autopause[lect]==0)//comportement normal
{
 switch(lect)
 {
 case 0:
 player1_do_stop();
 break;
 case 1:
 player2_do_stop();
 break;
 case 2:
 player3_do_stop();
 break;
 case 3:
 player4_do_stop();
 break;
 default:
 break;
 }
 if(player_is_onloopCue[lect]==0 )
 {//loop  GENERAL
                 switch(lect)
                  {
                  case 0:
                  player1->setPosition(0);
                  break;
                  case 1:
                  player2->setPosition(0);
                  break;
                  case 2:
                  player3->setPosition(0);
                  break;
                  case 3:
                  player4->setPosition(0);
                  break;
                  default:
                  break;
                  }
                }
                else if( player_is_onloopCue[lect]==1 )
                {
                //loop out point to inpoint
                switch(lect)
                {
                case 0:
                player1->setPosition(player_seek_position[lect]);
                break;
                case 1:
                player2->setPosition(player_seek_position[lect]);
                break;
                case 2:
                player3->setPosition(player_seek_position[lect]);
                break;
                case 3:
                player4->setPosition(player_seek_position[lect]);
                break;
                default:
                break;
                }
                }
}
else if(audio_autopause[lect]==1)//autostop
{
 switch(lect)
 {
 case 0:
 player1_do_stop();
 break;
 case 1:
 player2_do_stop();
 break;
 case 2:
 player3_do_stop();
 break;
 case 3:
 player4_do_stop();
 break;
 default:
 break;
 }
}

if(audio_autoload[lect]==1)//chargement auto
{
 switch(lect)
 {
 case 0:
 player1_do_stop();
 break;
 case 1:
 player2_do_stop();
 break;
 case 2:
 player3_do_stop();
 break;
 case 3:
 player4_do_stop();
 break;
 default:
 break;
 }
audiofile_selected=player_has_file_coming_from_pos[lect]+1;
if(audiofile_selected>=127){audiofile_selected=126;}
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(lect);
if(audio_autopause[lect]==0)//autostop
{
 switch(lect)
 {
 case 0:
 player1->play();
 break;
 case 1:
 player2->play();
 break;
 case 2:
 player3->play();
 break;
 case 3:
 player4->play();
 break;
 default:
 break;
 }
}
else//autostop
{
 switch(lect)
 {
 case 0:
 //player1->stop();
 player1_do_stop();
 break;
 case 1:
 //player2->stop();
 player2_do_stop();
 break;
 case 2:
 //player3->stop();
 player3_do_stop();
 break;
 case 3:
 //player4->stop();
 player4_do_stop();
 break;
 default:
 break;
 }
}
}

}

}
}
}
}

 return(0);
}


int Control_Audio_thruth_faders(int ff, int dd, int typ)//typ 0 vol / 1 pan / 2 pitch
{
int player_to_remote=0;
int vol_to_send=(255- curve_report[(FaderCurves[ff])][(Fader[ff])])/2;
if(vol_to_send>127){vol_to_send=127;}

switch(typ)
{
case 0://VOLUME
     player_to_remote=DockHasAudioVolume[ff][dd]-1;
     player_niveauson[player_to_remote]=vol_to_send;
     midi_levels[616+player_to_remote]=vol_to_send;
     if(player_ignited[player_to_remote]==1 && index_loading_a_sound_file==0)
     {
     switch(player_to_remote)
     {
     case 0:
     player1->setVolume(((float)player_niveauson[player_to_remote])/127);
     break;
     case 1:
     player2->setVolume(((float)player_niveauson[player_to_remote])/127);
     break;
     case 2:
     player3->setVolume(((float)player_niveauson[player_to_remote])/127);
     break;
     case 3:
     player4->setVolume(((float)player_niveauson[player_to_remote])/127);
     break;
     default: break;
     }
     }
break;
case 1://PAN
     player_to_remote=DockHasAudioPan[ff][dd]-1;
     player_pan[player_to_remote]=vol_to_send;
     midi_levels[620+player_to_remote]=vol_to_send;
     if(player_ignited[player_to_remote]==1 && index_loading_a_sound_file==0)
     {
     switch(player_to_remote)
     {
     case 0://PLAYER 1
     player1->setPan(((float)(player_pan[player_to_remote]-64))/63); // -64 /63 OK POUR AVOIR -1.00 +1.00 GAUCHE DROITE
     break;
     case 1://PLAYER 2
     player2->setPan(((float)(player_pan[player_to_remote]-64))/63);
     break;
     case 2://PLAYER 3
     player3->setPan(((float)(player_pan[player_to_remote]-64))/63);
     break;
     case 3://PLAYER 4
     player4->setPan(((float)(player_pan[player_to_remote]-64))/63);
     break;
     default: break;
     }
     }
break;
case 2://PITCH
     player_to_remote=DockHasAudioPitch[ff][dd]-1;
     player_pitch[player_to_remote]=vol_to_send;
     midi_levels[624+player_to_remote]=vol_to_send;
     if(player_ignited[player_to_remote]==1 && index_loading_a_sound_file==0)
     {
     switch(player_to_remote)
     {
     case 0://PLAYER 1
     player1->setPitchShift((((float)player_pitch[player_to_remote])/64));
     break;
     case 1://PLAYER 2
     player2->setPitchShift((((float)player_pitch[player_to_remote])/64));
     break;
     case 2://PLAYER 3
     player3->setPitchShift((((float)player_pitch[player_to_remote])/64));
     break;
     case 3://PLAYER 4
     player4->setPitchShift((((float)player_pitch[player_to_remote])/64));
     break;
     default: break;
     }
     }
break;
default: break;
}


return(0);
}

void ShowSupportedAudioDevices()
{
std::vector<audiere::AudioDeviceDesc> devices;
audiere::GetSupportedAudioDevices(devices);

for(unsigned int i=0;i<devices.size();i++)
{
sprintf(list_audio_device[i],"%s-%s",devices[i].name.c_str(),devices[i].description.c_str());
}
}


int InitSound()
{
  ShowSupportedAudioDevices();
  device=OpenDevice(0);// s ouvre automatiquement en winmm

  if (!device) {
    sprintf (string_Last_Order,"No Sound Device available !");
  }
else
  {  //affiche le device
  sprintf(audio_device_name,device->getName());
  }


 for(int i=0;i<4;i++)
 {
 player_pitch[i]=64;
 player_pan[i]=64;
 player_niveauson[i]=127;
 audio_rate[i]=44100;
 }


 return(0);
}


int do_logical_fader_niveau_son(int xp, int yp, int numero)
{

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>=yp && mouse_y<=yp+127)
{
//midi report
  if (miditable[0][616+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][616+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][616+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][616+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"VolumePlayer %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][616+numero],miditable[2][616+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(616+numero,Midi_Faders_Affectation_Mode);
}
else
{
player_niveauson[numero]=(YAudio+70+(numero*140)+127)-mouse_y;
if(player_ignited[numero]==1)
{
switch(numero)
{
case 0:
player1->setVolume(((float)player_niveauson[numero])/127);
break;
case 1:
player2->setVolume(((float)player_niveauson[numero])/127);
break;
case 2:
player3->setVolume(((float)player_niveauson[numero])/127);
break;
case 3:
player4->setVolume(((float)player_niveauson[numero])/127);
break;
default: break;
}
midi_levels[616+numero]=player_niveauson[numero];
if(midi_send_out[616+numero]==1){ index_send_midi_out[616+numero]=1;}//vol
}
}
}


if(mouse_x>xp+30 && mouse_x<xp+42 && mouse_y> yp+112 && mouse_y<yp+126)
{
//Volume pan et pitch sont en send back
midi_send_out[616+numero]=toggle(midi_send_out[616+numero]);
midi_send_out[620+numero]=midi_send_out[616+numero];
midi_send_out[624+numero]=midi_send_out[616+numero];
mouse_released=1;
}


raccrochage_midi_logical_vertical(xp,yp,616+numero,20,127);
return(0);
}

int do_logical_lecteur_audio( int xp, int yp, int numero)
{

if(mouse_x>xp && mouse_x<xp+200 && mouse_y>yp && mouse_y<yp+20)
{
AffectSoundFile(numero);
mouse_released=1;
}

//PLAY / Pause

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp+30 && mouse_y<yp+30+20)
{

//midi report
  if (miditable[0][628+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][628+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][628+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][628+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"Play Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][628+numero],miditable[2][628+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(628+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else {

if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
 switch(player1->isPlaying())
 {
 case 0:
 player1->play();
 break;
 case 1:
 //player1->stop();
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
 //player2->stop();
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
 //player3->stop();
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
 //player4->stop();
 player4_do_stop();
 break;
 default: break;
 }
break;
default: break;
}
}
 mouse_released=1;
}
}



//SEEK TO 0

if(mouse_x>xp+25 && mouse_x<xp+45 && mouse_y>yp+30 && mouse_y<yp+30+20)
{

//midi report
  if (miditable[0][628+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][628+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][628+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][628+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"Play Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][632+numero],miditable[2][632+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(632+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(player_ignited[numero]==1)
{
switch(numero)
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
 mouse_released=1;
}
}




//GENERAL LOOP

if(mouse_x>xp+50 && mouse_x<xp+70 && mouse_y>yp+30 && mouse_y<yp+30+20)
{

//midi report
  if (miditable[0][636+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][636+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][636+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][636+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"Loop Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][636+numero],miditable[2][636+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(636+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else {

if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
 switch(player1-> getRepeat())
 {
 case 0:
 player1->setRepeat(true);
 player_is_onloop[numero]=1;
 break;
 case 1:
 player1->setRepeat(false);
 player_is_onloop[numero]=0;
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2-> getRepeat())
 {
 case 0:
 player2->setRepeat(true);
 player_is_onloop[numero]=1;
 break;
 case 1:
 player2->setRepeat(false);
 player_is_onloop[numero]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3-> getRepeat())
 {
 case 0:
 player3->setRepeat(true);
 player_is_onloop[numero]=1;
 break;
 case 1:
 player3->setRepeat(false);
 player_is_onloop[numero]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4-> getRepeat())
 {
 case 0:
 player4->setRepeat(true);
 player_is_onloop[numero]=1;
 break;
 case 1:
 player4->setRepeat(false);
 player_is_onloop[numero]=0;
 break;
 default: break;
 }
break;
default: break;
}
mouse_released=1;
}
}
}


///seek to end

if(mouse_x>xp+75 && mouse_x<xp+75+20 && mouse_y>yp+30 && mouse_y<yp+30+20)
{

//midi report
  if (miditable[0][1821+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][1821+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][1821+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][1821+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"SeekToEnd %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][1821+numero],miditable[2][1821+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(1821+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(player_ignited[numero]==1 && index_loading_a_sound_file==0)
{
switch(numero)
{
case 0://PLAYER 1
player1->setPosition(length_of_file_in_player[numero]-1000);
break;
case 1://PLAYER 2
 player2->setPosition(length_of_file_in_player[numero]-1000);
break;
case 2://PLAYER 3
 player3->setPosition(length_of_file_in_player[numero]-1000);
break;
case 3://PLAYER 4
 player4->setPosition(length_of_file_in_player[numero]-1000);
break;
default:
break;
}
}
 mouse_released=1;
}
}



//Backward position

if(mouse_x>xp && mouse_x<xp+28 && mouse_y>yp+60 && mouse_y<yp+60+16)
{

//midi report
  if (miditable[0][640+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][640+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][640+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][640+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"Backward Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][640+numero],miditable[2][640+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(640+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else {

   if(player_ignited[numero]==1 && position_of_file_in_player[numero]-100000>0)
   {
   switch(numero)
   {
   case 0://PLAYER 1
    player1->setPosition(position_of_file_in_player[numero]-100000);
    break;
    case 1://PLAYER 2
    player2->setPosition(position_of_file_in_player[numero]-100000);
    break;
    case 2://PLAYER 3
    player3->setPosition(position_of_file_in_player[numero]-1000000);
    break;
    case 3://PLAYER 4
    player4->setPosition(position_of_file_in_player[numero]-100000);
    break;
    default: break;
   }
   mouse_released=1;
   }

}
}

//Forward position
if(mouse_x>xp+35 && mouse_x<xp+35+28 && mouse_y>yp+60 && mouse_y<yp+60+16)
{

//midi report
  if (miditable[0][644+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][644+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][644+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][644+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"Forward Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][644+numero],miditable[2][644+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{

attribute_midi_solo_affectation(644+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else {

   if(player_ignited[numero]==1 && position_of_file_in_player[numero]+100000<length_of_file_in_player[numero])
   {
   switch(numero)
   {
   case 0://PLAYER 1
    player1->setPosition(position_of_file_in_player[numero]+100000);
    break;
    case 1://PLAYER 2
    player2->setPosition(position_of_file_in_player[numero]+100000);
    break;
    case 2://PLAYER 3
    player3->setPosition(position_of_file_in_player[numero]+100000);
    break;
    case 3://PLAYER 4
    player4->setPosition(position_of_file_in_player[numero]+100000);
    break;
    default: break;
   }
   mouse_released=1;
   }

}
}


//prev track
if(mouse_x>xp && mouse_x<xp+45 && mouse_y>yp+85 && mouse_y<yp+85+16)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1813+numero,Midi_Faders_Affectation_Mode);
}
else
{
audiofile_selected=player_has_file_coming_from_pos[numero]-1;
if(audiofile_selected<1){audiofile_selected=1;}
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(numero);
}
}
mouse_released=1;
}

//next track

if(mouse_x>xp+50 && mouse_x<xp+50+45 && mouse_y>yp+85 && mouse_y<yp+85+16)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1817+numero,Midi_Faders_Affectation_Mode);
}
else
{
audiofile_selected=player_has_file_coming_from_pos[numero]+1;
if(audiofile_selected>=127){audiofile_selected=126;}
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(numero);
}
}
mouse_released=1;
}


//NUM FICHIER
if(mouse_x>xp+70 && mouse_x<xp+70+40 && mouse_y>yp+55 && mouse_y<yp+55+25)
{
 if (miditable[0][1809+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][1809+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][1809+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][1809+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"LOAD FILE Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][1809+numero],miditable[2][1809+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1809+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(numeric_postext==0)
{
audiofile_selected=player_has_file_coming_from_pos[numero]+1;
if(audiofile_selected>=127){audiofile_selected=126;}
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(numero);
}
}
else if(numeric_postext>0)
{
int nu=atoi(numeric);
if(nu<127  && nu>0)
{
audiofile_selected=nu;
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
if(strcmp (audiofile_name,"")!=0)
{
AffectSoundFile(numero);
}
reset_numeric_entry();numeric_postext=0;
}
}
}
mouse_released=1;
}







//audio_auto_load
if(mouse_x>xp && mouse_x<xp+28 && mouse_y>yp+110 && mouse_y<yp+110+16)
{
 if (miditable[0][1800+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][1800+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][1800+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][1800+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"AUTOLOAD Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][1800+numero],miditable[2][1800+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(1800+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else
{
audio_autoload[numero]=toggle(audio_autoload[numero]);
mouse_released=1;
}
}

//autopause

if(mouse_x>xp+35 && mouse_x<xp+35+40 && mouse_y>yp+110 && mouse_y<yp+110+16)
{
 if (miditable[0][1805+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][1805+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][1805+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][1805+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"AUTOSTOP Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][1805+numero],miditable[2][1805+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(1805+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
audio_autopause[numero]=toggle(audio_autopause[numero]);
mouse_released=1;
}
}


//SET cue IN

if(mouse_x>xp+210 && mouse_x<xp+240 && mouse_y>yp && mouse_y<yp+20)
{

//midi report
  if (miditable[0][648+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][648+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][648+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][648+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"SetCueIn Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][648+numero],miditable[2][648+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(648+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else {
if(index_edit_audio==1 )
{
if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
if(index_main_clear==0)
{
player_seek_position[numero]=(player1->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}

}
else  if(player_loop_out_position[numero]!=player_seek_position[numero]) {player_seek_position[numero]=0;index_main_clear=0;}
break;
case 1://PLAYER 2
if(index_main_clear==0)
{
player_seek_position[numero]=(player2->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}
}
else  if(player_loop_out_position[numero]!=player_seek_position[numero]) {player_seek_position[numero]=0;index_main_clear=0;}
break;
case 2://PLAYER 3
if(index_main_clear==0)
{
player_seek_position[numero]=(player3->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}
}
else  if(player_loop_out_position[numero]!=player_seek_position[numero]) {player_seek_position[numero]=0;index_main_clear=0;}
break;
case 3://PLAYER 4
if(index_main_clear==0)
{
player_seek_position[numero]=(player4->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}
}
else  if(player_loop_out_position[numero]!=player_seek_position[numero]) {player_seek_position[numero]=0;index_main_clear=0;}
break;
default: break;
}
audiofile_cue_in_out_pos[(player_has_file_coming_from_pos[numero])][0]=player_seek_position[numero];
}
 mouse_released=1;
}
}
}

//SET cue out

if(mouse_x>xp+235 && mouse_x<xp+255 && mouse_y>yp && mouse_y<yp+20)
{

//midi report
  if (miditable[0][652+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][652+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][652+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][652+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"SetCueOut Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][652+numero],miditable[2][652+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(652+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else {
if(index_edit_audio==1 )
{
if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
if(index_main_clear==0)
{
player_loop_out_position[numero]=(player1->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}
}
else if(player_loop_out_position[numero]!=player_seek_position[numero]) {player_loop_out_position[numero]=(player1->getLength());}
break;
case 1://PLAYER 2
if(index_main_clear==0)
{
player_loop_out_position[numero]=(player2->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}
}
else if(player_loop_out_position[numero]!=player_seek_position[numero])  {player_loop_out_position[numero]=(player2->getLength());}
break;
case 2://PLAYER 3
if(index_main_clear==0)
{
player_loop_out_position[numero]=(player3->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}
}
else if(player_loop_out_position[numero]!=player_seek_position[numero])  {player_loop_out_position[numero]=(player3->getLength());}
break;
case 3://PLAYER 4
if(index_main_clear==0)
{
player_loop_out_position[numero]=(player4->getPosition());
if(player_loop_out_position[numero]<=player_seek_position[numero]){player_loop_out_position[numero]=player_seek_position[numero]+1;}
}
else  if(player_loop_out_position[numero]!=player_seek_position[numero]) {player_loop_out_position[numero]=(player4->getLength());}
break;
default: break;
}
audiofile_cue_in_out_pos[(player_has_file_coming_from_pos[numero])][1]=player_loop_out_position[numero];
}
mouse_released=1;
}
}
}
//CUE ON OFF

if(mouse_x>xp+260 && mouse_x<xp+280 && mouse_y>yp && mouse_y<yp+20)
{


//midi report
  if (miditable[0][656+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][656+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][656+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][656+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"SetCueOut Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][656+numero],miditable[2][656+numero],thetypinfo);
if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(656+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else {
if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
 switch(player1-> getRepeat())
 {
 case 0:
 player1->setRepeat(true);
 player_is_onloopCue[numero]=1;
 break;
 case 1:
 player1->setRepeat(false);
 player_is_onloopCue[numero]=0;
 break;
 default: break;
 }
break;
case 1://PLAYER 2
 switch(player2-> getRepeat())
 {
 case 0:
 player2->setRepeat(true);
 player_is_onloopCue[numero]=1;
 break;
 case 1:
 player2->setRepeat(false);
 player_is_onloopCue[numero]=0;
 break;
 default: break;
 }
break;
case 2://PLAYER 3
 switch(player3-> getRepeat())
 {
 case 0:
 player3->setRepeat(true);
 player_is_onloopCue[numero]=1;
 break;
 case 1:
 player3->setRepeat(false);
 player_is_onloopCue[numero]=0;
 break;
 default: break;
 }
break;
case 3://PLAYER 4
 switch(player4-> getRepeat())
 {
 case 0:
 player4->setRepeat(true);
 player_is_onloopCue[numero]=1;
 break;
 case 1:
 player4->setRepeat(false);
 player_is_onloopCue[numero]=0;
 break;
 default: break;
 }
break;
default: break;
}
}
 mouse_released=1;
}
}

//Seek cue

if(mouse_x>xp+210 && mouse_x<xp+230 && mouse_y>yp+30 && mouse_y<yp+50)
{

//midi report
  if (miditable[0][660+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][660+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][660+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][660+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"SetCueOut Player %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][660+numero],miditable[2][660+numero],thetypinfo);
if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(660+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else {

if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
 player1->setPosition(player_seek_position[numero]);
break;
case 1://PLAYER 2
 player2->setPosition(player_seek_position[numero]);
break;
case 2://PLAYER 3
 player3->setPosition(player_seek_position[numero]);
break;
case 3://PLAYER 4
 player4->setPosition(player_seek_position[numero]);
break;
default: break;
}
}
 mouse_released=1;
}
}




//Pitch

if(mouse_x>xp+120+player_pitch[numero] && mouse_x<xp+150+player_pitch[numero] && mouse_y>yp+110 && mouse_y<yp+110+10)
{

//midi report
  if (miditable[0][624+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][624+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][624+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][624+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"PitchPlayer %d  is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][624+numero],miditable[2][624+numero],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(624+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else {

if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
 player_pitch[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pitch[numero]<1){player_pitch[numero]=1;}
 else if(player_pitch[numero]>127){player_pitch[numero]=127;}
 player1->setPitchShift((((float)player_pitch[numero])/64));
break;
case 1://PLAYER 2
  player_pitch[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pitch[numero]<1){player_pitch[numero]=1;}
 else if(player_pitch[numero]>127){player_pitch[numero]=127;}
 player2->setPitchShift((((float)player_pitch[numero])/64));
break;
case 2://PLAYER 3
  player_pitch[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pitch[numero]<1){player_pitch[numero]=1;}
 else if(player_pitch[numero]>127){player_pitch[numero]=127;}
 player3->setPitchShift((((float)player_pitch[numero])/64));
break;
case 3://PLAYER 4
  player_pitch[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pitch[numero]<1){player_pitch[numero]=1;}
 else if(player_pitch[numero]>127){player_pitch[numero]=127;}
 player4->setPitchShift((((float)player_pitch[numero])/64));
break;
default: break;
}
}
}

midi_levels[624+numero]=player_pitch[numero];
if(midi_send_out[624+numero]==1){ index_send_midi_out[624+numero]=1;}//pitch
}
raccrochage_midi_logical_horizontal_audio (xp+130, yp+100, 620+numero, 127,10);

//Pan

if(mouse_x>xp+120+player_pan[numero] && mouse_x<xp+150+player_pan[numero] && mouse_y>yp+85 && mouse_y<yp+85+10)
{

//midi report
  if (miditable[0][620+numero]==0){sprintf(thetypinfo,"Note");}
  if(miditable[0][620+numero]==1){sprintf(thetypinfo,"Key On");}
  if (miditable[0][620+numero]==2){sprintf(thetypinfo,"Key Off");}
  if (miditable[0][620+numero]==4){sprintf(thetypinfo,"Ctrl Change");}
  sprintf(string_last_midi_id,"PanPlayer %d is Ch: %d Pitch: %d Typ: %s" , numero, miditable[1][620+numero],miditable[2][620+numero],thetypinfo);
if(Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(620+numero,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else {
if(player_ignited[numero]==1)
{
switch(numero)
{
case 0://PLAYER 1
 player_pan[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pan[numero]<1){player_pan[numero]=1;}
 else if(player_pan[numero]>127){player_pan[numero]=127;}
 player1->setPan(((float)(player_pan[numero]-64))/63); // -64 /63 OK POUR AVOIR -1.00 +1.00 GAUCHE DROITE
break;
case 1://PLAYER 2
 player_pan[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pan[numero]<1){player_pan[numero]=1;}
 else if(player_pan[numero]>127){player_pan[numero]=127;}
 player2->setPan(((float)(player_pan[numero]-64))/63);
break;
case 2://PLAYER 3
 player_pan[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pan[numero]<1){player_pan[numero]=1;}
 else if(player_pan[numero]>127){player_pan[numero]=127;}
 player3->setPan(((float)(player_pan[numero]-64))/63);
break;
case 3://PLAYER 4
 player_pan[numero]=(mouse_x- (XAudio+5+120))-10 ;
 if(player_pan[numero]<1){player_pan[numero]=1;}
 else if(player_pan[numero]>127){player_pan[numero]=127;}
 player4->setPan(((float)(player_pan[numero]-64))/63);
break;
default: break;
}
}
}
midi_levels[620+numero]=player_pan[numero];
if(midi_send_out[620+numero]==1){ index_send_midi_out[620+numero]=1;}//pan

}

raccrochage_midi_logical_horizontal_audio (xp+130, yp+80, 624+numero, 127,10);
//les faders son
do_logical_fader_niveau_son(xp+290,yp,numero);
return(0);
}


int do_logical_fenetre_audio(int xb,int yb)
{

if(mouse_x>xb+350 && mouse_x<xb+590 && mouse_y>yb+10 && mouse_y<yb+40)
{
if(index_type==1 )
{
index_ask_confirm=1;
index_do_ask_call_audio_folder=1;
mouse_released=1;
}
}

//////////////////////LISTE sons///////////////////////////////////////

for (int y=1;y<(index_nbre_players_visibles*6* 24);y++)
{

if(mouse_x>xb+355 && mouse_x<xb+355+150 && mouse_y>(yb+45+(y*20)-12) && mouse_y<(yb+45+(y*20)+3))
{
audiofile_selected=(y+line_audio);
sprintf(audiofile_name,list_audio_files[audiofile_selected]);
mouse_released=1;
}
}

//////////////////UP DOWN LINE IMPORT/////////////////////

if(mouse_x>xb+570-12 && mouse_x<xb+570+12)
{
if(mouse_y>yb+65-12 && mouse_y<yb+65+12)
{
if(line_audio>0){line_audio--;mouse_released=1;}
}
if(mouse_y>yb+(index_nbre_players_visibles*6* 20)-7 && mouse_y<yb+(index_nbre_players_visibles*6* 20)+5)
{
if(line_audio+24<128){line_audio++;mouse_released=1;}
}
}

//RESCAN FOLDER

    if(mouse_x>xb+230 && mouse_x<xb+230+50 && mouse_y>yb+10 && mouse_y<yb+10+20)
    {
    mouse_released=1;
    scan_audiofolder();
   // Save_audiofiles_cues();
    Load_audiofiles_cues();

    }
 ////////////////////////////////////////////////////////////////////////////////
//EDIT ON OFF

    if(mouse_x>xb+230 && mouse_x<xb+230+50 && mouse_y>yb+40 && mouse_y<yb+40+20)
    {
    index_edit_audio=toggle(index_edit_audio);
    mouse_released=1;
    }



//////LES LECTEURS//////////////////////////////////////////////////////////////
for(int lop=0;lop<index_nbre_players_visibles;lop++)
{
do_logical_lecteur_audio(xb+5,yb+70+(lop*140),lop);
}

//////L AFFECTATION AUX FADERS//////////////////////////////////////////////////

if(mouse_x>xb+440 && mouse_x<xb+440+140 && mouse_y>yb+55+(index_nbre_players_visibles*6*20) && mouse_y<yb+55+(index_nbre_players_visibles*6*20)+20)
{
if(index_affect_audio_to_dock==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_affect_audio_to_dock=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_affect_audio_to_dock;
mouse_released=1;

}

for(int pl=0;pl<index_nbre_players_visibles;pl++)
{
for (int co=0;co<3;co++)
{

 if(index_affect_audio_to_dock==1 && mouse_x>xb+460+(pl*30) && mouse_x<xb+460+(pl*30)+20 && mouse_y>yb+90+(index_nbre_players_visibles*6*20)+(co*20) && mouse_y<yb+90+(index_nbre_players_visibles*6*20)+(co*20)+15)
 {

 player_to_affect_to_dock=pl;
 audio_type_for_dock_affectation_is=co; // 0 volume 1 pan 2 pitch
 mouse_released=0;

 }
}
}


return(0);
}
