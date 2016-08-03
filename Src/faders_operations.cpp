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

* \file faders_operations.cpp
* \brief {fonctions to assign dock and fonctions for the faders}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour controller les faders et leurs effets
*
*   Fonctions to assign dock and fonctions for the faders
*
 **/


//FADERS

int Unselect_other_docks(int themaster, int thedock)
{
 for (int rdk=0;rdk<core_user_define_nb_docks;rdk++)
 {
 if (rdk!=thedock)
 {DockIsSelected[themaster][rdk]=0;}
 }
 return(0);
}



int  DoTimeToDock(int faa,int docc)
{
for(int o=0;o<4;o++)
{
if(index_type_of_time_to_affect[o]==1)
{
 time_per_dock[faa][docc][o]=((time_minutes*60) + time_secondes + (((float)time_centiemes)/100));
}
}
return(0);
}




int ClearDock(int fad, int dk)
{

 for (int dc=1;dc<514;dc++)
 {
  FaderDockContains[fad][dk][dc]=0;//nettoyage du fader
  FaderDoDmx[fad][dc]=0;//clear du buffer dmx
  show_who_is_in_FADER_DOCK[dc]=0;//debug jacques
  highest_level_comes_from_fader[dc]=0;//debug jacques
 }


 DockTypeIs[fad][dk]=9;//le type est 9 clear rien du tout / 0= circuits normaux


//desafectation de la trichro, specifique pour les affichages des liens dock faders
 if(DockTypeIs[fad][dk]==1)
 {
 for(int i=0;i<8;i++)
 {
  if(colorpreset_linked_to_dock[i][0]==fad && colorpreset_linked_to_dock[i][1]==dk)
  {
  colorpreset_linked_to_dock[i][0]=-1;
  colorpreset_linked_to_dock[i][1]=-1;
  }
 }
 }


 //fgroup
 for(int fg=0;fg<48;fg++)
  {
  fgroup[fad][dk][fg]=0;
  }
  //remise à plat de view
 show_who_is_in_dock (fad, dk);
 //nettoyage temps
   time_minutes=0;
   time_secondes=0;
   time_centiemes=0;
   index_type_of_time_to_affect[0]=1;
   index_type_of_time_to_affect[2]=1;
   DoTimeToDock(fad,dk);
   index_type_of_time_to_affect[0]=0;
   index_type_of_time_to_affect[2]=0;
   index_type_of_time_to_affect[1]=1;
   index_type_of_time_to_affect[3]=1;
   time_minutes=0;
   time_secondes=3;
   time_centiemes=0;
   DoTimeToDock(fad,dk);
   index_type_of_time_to_affect[1]=0;
   index_type_of_time_to_affect[3]=0;
 //nettoyage du descriptif
 strcpy(DockName[fad][dk],"");
 DockName[fad][dk][24]='\0';
 //boucle lfo
 is_dock_for_lfo_selected[fad][dk]=0;
 DockHasAudioVolume[fad][dk]=999;
 DockHasAudioPan[fad][dk]=999;
 DockHasAudioPitch[fad][dk]=999;
 //fx
 ChaserAffectedToDck[fad][dk]=999;
 //grid
 faders_dock_grid_affectation[fad][dk]=-1;
return(0);
}


int affect_echo_to_dock(int echo, int ff, int dd)
{
ClearDock(ff,dd);
DockTypeIs[ff][dd]=16;
echo_affected_to_dock[ff][dd]=echo;
sprintf(string_Last_Order,"Affected DRAW Preset %d To Fader %d Dock %d",echo+1,ff+1, dd+1);
return(0);
}


int  affect_draw_preset_to_dock(int pr,int ff, int dd)
{
ClearDock(ff,dd);
DockTypeIs[ff][dd]=15;
DrawAffectedToDck[ff][dd]=pr;
sprintf(string_Last_Order,"Affected DRAW Preset %d To Fader %d Dock %d",pr+1,ff+1, dd+1);
draw_preset_selected_for_order=0;

return(0);
}

int ClearFader(int fad)
{

for(int p=0;p<6;p++)
  {
  ClearDock(fader_selected_for_record,p);
  FaderDirectChan[fad][p]=0;
  }
 //mise a plat niveau
 Fader[fad]=0;
 Fader_dampered[fad].fix_all_damper_state_value(Fader[fad]);
 Fader_dampered[fad].set_target_val(Fader[fad]);
 Fader_dampered[fad].set_damper_decay(1.0);
 Fader_dampered[fad].set_damper_dt(0.1);
 FaderLocked[fad]=0;
 LockFader_is_FullLevel[fad]=0;
 StateOfFaderBeforeLock[fad]=0;
 LevelFaderBeforeFlash[fad]=0;
 LevelStopPos[fad]=0;
 PreviousLevelStopPos[fad]=0;
 ActionnateStopOn[fad]=0;
 midi_levels[fad]=0;
 if(midi_send_out[fad]==1)
 {
 index_send_midi_out[fad]=1;
 }
 //dock 0 selected
 DockIsSelected[fad][0]=1;
 Unselect_other_docks(fad,0);
 //lfos
 lfo_speed[fad]=64;
 midi_levels[196+fad]=64;
 if(midi_send_out[196+fad]==1)
 {
 index_send_midi_out[196+fad]=1;
 }
 //les index_lfos
 lfo_mode_is[fad]=0;
 lfo_cycle_is_on[fad]=0;
 lfo_do_next_step[fad][0]=0;
 lfo_do_next_step[fad][1]=0;
 lfo_cycle_steps[fad]=0;
 //direct chan
 beforeloop_for_directch[fad]=0;
 //courbe
 FaderCurves[fad]=0;
 return(0);
}

int record_minifaders_selected_as_fgroup(int fd, int dk)
{
for(int i=0;i<48;i++)
{
if(i!=fd)
{
fgroup[fd][dk][i]= minifaders_selected[i];
minifaders_selected[i]=0;
}
}
 return(0);
}

int affect_selected_faders_to_fgroup(int fd, int dk)
{
 ClearDock(fd,dk);
 DockTypeIs[fd][dk]=13;
 record_minifaders_selected_as_fgroup(fd,dk);
 return(0);
}


int DoDock(int fad, int dk)
{
 ClearDock(fad,dk);

 if(numeric_postext==0)//si pas de chaine de caracteres tapés
 {
 DockTypeIs[fad][dk]=0;//le type est 0, circuits normaux
 if(index_blind==0)
 {
 for (int dc=1;dc<514;dc++)
 {
 FaderDockContains[fad][dk][dc]=0;//nettoyage du fader
 FaderDockContains[fad][dk][dc]=bufferSequenciel[dc];
 //rajout
 bufferSaisie[dc]=0;
 Selected_Channel[dc]=0;
 }
 index_do_dock=0;
 Unselect_other_docks(fad,dk);
 DockIsSelected[fad][dk]=1;
 Fader[fad]=255;
 sprintf(string_Last_Order,">>n Stage Stored in F %d Dock %d",fad+1, dk);
 }

 else if(index_blind==1)
 {
 for (int dc=1;dc<514;dc++)
 {
 FaderDockContains[fad][dk][dc]=bufferBlind[dc];
 }
 index_do_dock=0;
 sprintf(string_Last_Order,">>n Preset Stored in F %d Dock %d",fad+1, dk);
 }
 }
 else if (numeric_postext>0)
 {
 int mem_to_load_in_dock= (int)(atof(numeric)*10.0001);
 if(MemoiresExistantes[mem_to_load_in_dock]==1)
 {
 //ClearDock(fad,dk);
 DockTypeIs[fad][dk]=5;
 int mem_to_load_in_dock= (int)(atof(numeric)*10.0001);
 DockHasMem[fad][dk]=mem_to_load_in_dock;
 reset_numeric_entry();
 sprintf(string_Last_Order,">>n Stored Mem %.1f in F %d Dock %d",(float (mem_to_load_in_dock))/10,fad+1, dk);
 }
 else
 {sprintf(string_Last_Order,">>n Mem %.1f doesn't exist",(float (mem_to_load_in_dock))/10);  }

 }
 return(0);
}



int DoModify(int fad, int dk)
{
 if(index_blind==0)
 {
 for (int dc=1;dc<514;dc++)
 {
 if(Selected_Channel[dc]==1)
 {
 FaderDockContains[fad][dk][dc]=bufferSaisie[dc];
 bufferSaisie[dc]=0;
 Selected_Channel[dc]=0;
 }
 }
 index_do_modify=0;
 }

 else if(index_blind==1)
 {
 for (int dc=1;dc<514;dc++)
 {
 if(Selected_Channel[dc]==1)
 {FaderDockContains[fad][dk][dc]=bufferBlind[dc];}
 }
 index_do_modify=0;
 }
 DockTypeIs[fad][dk]=0;


 return(0);
}




int DoReport(int fad, int dk)
{


 DockTypeIs[fad][dk]=0;//le type est 0, circuits normaux
 for (int u=1;u<514;u++)
 {
 FaderDockContains[fad][dk][u]=bufferSaisie[u];
 if(bufferFaders[u]>FaderDockContains[fad][dk][u]){FaderDockContains[fad][dk][u]=bufferFaders[u];}
 }
 for (int x=1;x<514;x++)
 {
 bufferSaisie[x]=0;
 bufferBlind[x]=0;
 Selected_Channel[x]=0;
 }

 for (int fder=0;fder<core_user_define_nb_faders;fder++)
 {
 Fader[fder]=0;
 }
 Unselect_other_docks(fad,dk);
 DockIsSelected[fad][dk]=1;
 Fader[fad]=255;
 index_do_report=0;
 return(0);
}



int affect_color_to_dock(int fa, int doc)
{
ClearDock(fa,doc);
DockTypeIs[fa][doc]=1;//le type est 1, il est rempli avec une couleur
colorpreset_linked_to_dock[dock_color_selected][0]=fa;// num fader
colorpreset_linked_to_dock[dock_color_selected][1]=doc;//num dock
return(0);
}

int affect_network_to_dock(int faa, int docc)
{
ClearDock(faa,docc);
DockTypeIs[faa][docc]=2;
DockNetIs[faa][docc]=select_artnet_to_listen; // numero univ
return(0);
}

int affect_dmxIN_to_dock(int faa, int docc)
{
ClearDock(faa,docc);
DockTypeIs[faa][docc]=3;
return(0);
}

int  affect_video_tracking_to_dock(int faa, int docc)
{
ClearDock(faa,docc);
DockTypeIs[faa][docc]=4;
return(0);
}

int affect_audio_control_to_dock(int faa, int docc)
{
//clean first
DockHasAudioVolume[faa][docc]=0;
DockHasAudioPan[faa][docc]=0;
DockHasAudioPitch[faa][docc]=0;
ClearDock(faa,docc);
switch(audio_type_for_dock_affectation_is)
{
case 0:
DockTypeIs[faa][docc]=6;//volume
DockHasAudioVolume[faa][docc]=player_to_affect_to_dock+1;
break;
case 1:
DockTypeIs[faa][docc]=7;//pan
DockHasAudioPan[faa][docc]=player_to_affect_to_dock+1;
break;
case 2:
DockTypeIs[faa][docc]=8;//picth
DockHasAudioPitch[faa][docc]=player_to_affect_to_dock+1;
break;
default: break;
}
player_to_affect_to_dock=999;
audio_type_for_dock_affectation_is=999;

return(0);
}


int affect_chaser_to_dock(int chas,  int fd,int dk )
{
ClearDock(fd,dk);
ChaserAffectedToDck[fd][dk]=chas;
DockTypeIs[fd][dk]=11;
view_chaser_affected_to_fader[chas][0]=fd;//pour affichage chaser selected dans fenetre
view_chaser_affected_to_fader[chas][1]=dk;//pour affichage chaser selected dans fenetre
return(0);
}

//GLOBAS

int Unselect_all_channels()
{
   for (int ci=1;ci<514;ci++)
  {Selected_Channel[ci]=0;}
   return(0);
}

//COLORS

int affect_color_to(int dockC_sel,int couleur)
{
if(index_do_dock==1)
{
for (int co=1;co<513;co++)
{
dock_color_channels[dockC_sel][couleur][co]=Selected_Channel[co];
}
index_do_dock=0;
}
else if(index_do_modify==1)
{
for (int co=1;co<513;co++)
{
if(dock_color_channels[dockC_sel][couleur][co]==1 && Selected_Channel[co]==1)
{dock_color_channels[dockC_sel][couleur][co]=0;}
else if(dock_color_channels[dockC_sel][couleur][co]==0 && Selected_Channel[co]==1)
{dock_color_channels[dockC_sel][couleur][co]=1;}
}
index_do_modify=0;
}

if(index_do_report==1)
{
for (int co=1;co<513;co++)
{
if(bufferSaisie[co]>0 || bufferFaders[co]>0){dock_color_channels[dockC_sel][couleur][co]=1;}
else {dock_color_channels[dockC_sel][couleur][co]=0;}
}
index_do_report=0;
}
Unselect_all_channels();
return(0);
}

/////////////////VIDEO


int affect_to_tracker(int dock_selected,int tracker_selected)
{
if(index_do_dock==1)
{
for(int affe=1;affe<512;affe++)
{
tracking_contents[dock_selected][tracker_selected][affe]=Selected_Channel[affe];
}
index_do_dock=0;
}

else if(index_do_modify==1)
{
for(int affe=1;affe<512;affe++)
{
if(Selected_Channel[affe]==1)
{
if(tracking_contents[dock_selected][tracker_selected][affe]==1){tracking_contents[dock_selected][tracker_selected][affe]=0;}
else if(tracking_contents[dock_selected][tracker_selected][affe]==0){tracking_contents[dock_selected][tracker_selected][affe]=1;}

}
}
Unselect_all_channels();
index_do_modify=0;
}

else if(index_do_report==1)
{
for(int affe=1;affe<512;affe++)
{
tracking_contents[dock_selected][tracker_selected][affe]=0;
if(bufferSaisie[affe]>0 || bufferFaders[affe]>0){tracking_contents[dock_selected][tracker_selected][affe]=1;}
}
Unselect_all_channels();
index_do_report=0;
}
sprintf(string_Last_Order,">>Affected CH to Tracker %d TrackingDock %d",dock_selected,tracker_selected);
return(0);
}


int do_direct_channel(int fad,int dk)
{
if(numeric_postext>0)
{
last_ch_selected=atoi(numeric);
reset_numeric_entry();
numeric_postext=0;
}

if(last_ch_selected>0 && last_ch_selected<513)
{
ClearDock(fad,dk);
switch(multiple_direct_chan)
{
case 0:
DockTypeIs[fad][dk]=10;//direct channel mode
FaderDirectChan[fad][dk]=last_ch_selected;
//report dans dock
sprintf( DockName[fad][dk], descriptif_projecteurs[last_ch_selected]);
sprintf(string_Last_Order,">>Direct Channel x1 done");
break;
case 1:
for(int l=0;l<12;l++)
{
if(fad+l<core_user_define_nb_faders)
{
DockTypeIs[fad+l][dk]=10;//direct channel mode
FaderDirectChan[fad+l][dk]=last_ch_selected+l;
//report dans dock
sprintf( DockName[fad+l][dk], descriptif_projecteurs[last_ch_selected+l]);
}
}
sprintf(string_Last_Order,">>Direct Channel x12 done");
break;
default:
break;
}
}
else
{
sprintf(string_Last_Order,">>Direct Channel: Please select a channel !");
}
return(0);
}

