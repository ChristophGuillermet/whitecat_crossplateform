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

* \file chasers_core_5.cpp
* \brief {file for the core of the chasers}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gère les fonction core des chenillards
*
*   Core fonctions for the chasers
*
 **/

int refresh_chaser_midi_out()
{

//timeline
midi_levels[995]=(int)(((float)(chaser_begin_step_is[chaser_selected])/36)*127);
index_send_midi_out[995]=1;
midi_levels[996]=(int)(((float)(chaser_end_step_is[chaser_selected])/36)*127);
index_send_midi_out[996]=1;
midi_levels[997]=(int)(((float)(chaser_step_is[chaser_selected])/36)*127);
index_send_midi_out[997]=1;
//levels
for(int num_track=0;num_track<23;num_track++)
{
midi_levels[1023+num_track]=track_level[chaser_selected][num_track];
midi_levels[998+num_track]=127*track_is_on[chaser_selected][num_track];
index_send_midi_out[1023+num_track]=1;
index_send_midi_out[998+num_track]=1;
}
//loop
midi_levels[980]=chaser_is_in_loop[chaser_selected]*127;

if(chaser_way[chaser_selected]==0)////forward
{midi_levels[981]=127;midi_levels[982]=0;midi_levels[983]=0;}
else if(chaser_way[chaser_selected]==1)//backward
{midi_levels[981]=0;midi_levels[982]=127;midi_levels[983]=0;}

index_send_midi_out[980]=1;
index_send_midi_out[981]=1;
index_send_midi_out[982]=1;
index_send_midi_out[983]=1;
return(0);
}

int set_refresh_mode_for_chaser(bool value)
{
midi_send_out[995]=value;
midi_send_out[996]=value;
midi_send_out[997]=value;
for(int num_track=0;num_track<23;num_track++)//on off hors launchpad
{
midi_send_out[998+num_track]=1;
}
return(0);
}

int refresh_launchpad_on_chaser()
{
//etats des follow steps
if( launchpad_chaser_mode==1)
{

for(int trk=0;trk<chaser_midi_rows ;trk++)
{


for(int pas=0;pas<8;pas++)
{
previous_color_on_chaser[trk][pas]=launchpad_color_defined[(1048+(trk*8)+pas)];
switch(chaser_step_operation[chaser_selected][position_affichage_track_num[chaser_selected]+trk][chaser_step_launchpad[chaser_selected]+pas])
{
case 0:
launchpad_color_defined[(1048+(trk*8)+pas)]=0;
break;
case 1:
launchpad_color_defined[(1048+(trk*8)+pas)]=lch_orange_fonce;
break;
case 2:
launchpad_color_defined[(1048+(trk*8)+pas)]=lch_green;
break;
case 3:
launchpad_color_defined[(1048+(trk*8)+pas)]=lch_red;
break;
default: break;
}
//correcteur curseur
int correcteur=0;
switch(chaser_way[chaser_selected])
{
case 0:
correcteur=+1;
break;
case 1:
correcteur=-1;
break;
default: break;
}

//position curseur
if((chaser_step_launchpad[chaser_selected]+pas)==chaser_step_is[chaser_selected]+correcteur)
{launchpad_color_defined[(1048+pas)]=lch_yellow;}//curseur toujours sur première ligne

if(previous_color_on_chaser[trk][pas]!=launchpad_color_defined[(1048+(trk*8)+pas)])
{
midi_launchpad_state_before[(1048+(trk*8)+pas)]=0;
midi_launchpad_state[(1048+(trk*8)+pas)]=1;
}
}
}
}
 return(0);
}


int chaser_calcul_time_joint(int numchaser)
{
//calcul des positions contigues se ressemblant
if(chaser_time_mode[numchaser]==1)
{

switch(chaser_way[numchaser])
{
case 0://Avant
for(int trk=0;trk< core_user_define_nb_tracks_per_chasers;trk++)
{
count_steps_for_fades[numchaser][trk]=1;//reset

for(int pos_step=chaser_step_is[numchaser];pos_step<nbre_de_cases_par_track;pos_step++)
{
if(chaser_step_operation[numchaser][trk][pos_step-1]!=chaser_step_operation[numchaser][trk][pos_step]
&& chaser_step_operation[numchaser][trk][pos_step]!=0 && chaser_step_operation[numchaser][trk][pos_step]!=2)//sauf Stay et Rien
{
joint_begin_step[numchaser][trk]=pos_step;
}
for(int pstst=joint_begin_step[numchaser][trk]; pstst<nbre_de_cases_par_track;pstst++)
{
if(chaser_step_operation[numchaser][trk][pstst]!=chaser_step_operation[numchaser][trk][(joint_begin_step[numchaser][trk])])
{
joint_end_step[numchaser][trk]=pstst;
joint_nbr_step[numchaser][trk]=joint_end_step[numchaser][trk]-joint_begin_step[numchaser][trk];
break;
}
}

if(chaser_step_operation[numchaser][trk][pos_step]==chaser_step_operation[numchaser][trk][pos_step+1]
&& chaser_step_operation[numchaser][trk][pos_step]!=0 && chaser_step_operation[numchaser][trk][pos_step]!=2)//sauf Stay et Rien
{
count_steps_for_fades[numchaser][trk]++;
}
else{break;}
}
}
break;
case 1: // arrière
for(int trk=0;trk< core_user_define_nb_tracks_per_chasers;trk++)
{
count_steps_for_fades[numchaser][trk]=1;//reset

for(int pos_step=chaser_step_is[numchaser];pos_step>0;pos_step--)
{
if(chaser_step_operation[numchaser][trk][pos_step+1]!=chaser_step_operation[numchaser][trk][pos_step]
&& chaser_step_operation[numchaser][trk][pos_step]!=0 && chaser_step_operation[numchaser][trk][pos_step]!=2)//sauf Stay et Rien
{
joint_begin_step[numchaser][trk]=pos_step;
}
for(int pstst=joint_begin_step[numchaser][trk]; pstst>=0;pstst--)
{
if(chaser_step_operation[numchaser][trk][pstst]!=chaser_step_operation[numchaser][trk][(joint_begin_step[numchaser][trk])])
{
joint_end_step[numchaser][trk]=pstst;
joint_nbr_step[numchaser][trk]=joint_begin_step[numchaser][trk]-joint_end_step[numchaser][trk];
break;
}
}

if(chaser_step_operation[numchaser][trk][pos_step]==chaser_step_operation[numchaser][trk][pos_step-1]
&& chaser_step_operation[numchaser][trk][pos_step]!=0 && chaser_step_operation[numchaser][trk][pos_step]!=2)//sauf Stay et Rien
{
count_steps_for_fades[numchaser][trk]++;
}
else{break;}
}
}
break;
default: break;
}
}
return(0);
}


int chaser_calcul_step(int numchaser, float ratio_for_no_reset)
{
chaser_start_of_step[numchaser]=actual_time+((time_unit[numchaser]*((float)BPS_RATE))*ratio_for_no_reset);
chaser_end_of_step[numchaser]=actual_time+((time_unit[numchaser]*chaser_slaviness[numchaser])*((float)BPS_RATE));
chaser_time_position[numchaser]=actual_time;
refresh_launchpad_on_chaser();
return(0);
}


int do_chaser()
{
for(int nch=0;nch<core_user_define_nb_chasers;nch++)
{

if(index_slave_chaser_to_accelerometre[nch]==1)
{
chaser_slaviness[nch]=((127-(float)lfo_speed[(view_chaser_affected_to_fader[nch][0])])/127.0);

if(chaser_slaviness[nch]==0.0){chaser_slaviness[nch]=0.01;}

}
else {chaser_slaviness[nch]=1.0;}


//refresh chasers buffers
for(int io=1;io<513;io++)
{
MergerBufferChasers[nch][io]=0;
}
if(chaser_is_playing[nch]==1)
{
//calcul de la position///////////////////////////////////////////////////////////
switch(chaser_way[nch])
{
case 0://avant
    chaser_time_position[nch]++;

    if(chaser_time_position[nch]>=chaser_end_of_step[nch])
    {
    chaser_calcul_step(nch,0.0);
    chaser_step_is[nch]++;
    if(chaser_step_is[nch]>chaser_end_step_is[nch] )
    {
    switch(chaser_is_in_loop[nch])
        {
        case 0:
        chaser_is_playing[nch]=0;
        break;
        case 1:
            switch( chaser_aller_retour[nch])
                    {
                    case 0:
                    chaser_step_is[nch]=chaser_begin_step_is[nch];
                    break;
                    case 1:
                    chaser_step_is[nch]--;
                    chaser_way[nch]=toggle(chaser_way[nch]);
                    break;
                    default: break;
                    }
        break;
        default: break;
        }
    }
    chaser_calcul_time_joint(nch);
    }
    index_progression_chaser_step[nch]=((chaser_time_position[nch]-chaser_start_of_step[nch])/((chaser_end_of_step[nch]-chaser_start_of_step[nch])/chaser_slaviness[nch]));
break;
case 1://arrière
chaser_time_position[nch]++;
if(chaser_time_position[nch]>=chaser_end_of_step[nch])
{
chaser_calcul_step(nch,0.0);
chaser_step_is[nch]--;
if(chaser_step_is[nch]<chaser_begin_step_is[nch])
{
switch(chaser_is_in_loop[nch])
{
case 0:
chaser_is_playing[nch]=0;
break;
case 1:
switch( chaser_aller_retour[nch])
{
case 0:
chaser_step_is[nch]=chaser_end_step_is[nch];
break;
case 1:
chaser_step_is[nch]++;
chaser_way[nch]=toggle(chaser_way[nch]);
break;
default: break;
}
break;
default: break;
}
}

chaser_calcul_time_joint(nch);
}
index_progression_chaser_step[nch]=((chaser_time_position[nch]-chaser_start_of_step[nch])/((chaser_end_of_step[nch]-chaser_start_of_step[nch])/chaser_slaviness[nch]));
break;
default: break;
}
}//fin if track is on
//contenu relié à une mémoire

//calcul des états de circuits///////////////////////////////////////////////////////////


for(int trkis=0;trkis<core_user_define_nb_tracks_per_chasers;trkis++)
{
//rafraichissement si memoire
if(TrackTypeIs[nch][trkis]==1)//si une mémoire embarquée
{
for(int u=1;u<513;u++)
{
TrackContains[nch][trkis][u]= Memoires[(TrackHasMem[nch][trkis])][u];
for(int ui=0;ui<core_user_define_nb_tracks_per_chasers;ui++)
{
TracksBuffer[nch][trkis][ui]=0;
}
}
}

if(track_is_on[nch][trkis]==1)
{
switch(chaser_step_operation[nch][trkis][(chaser_step_is[nch])])
{
case 0://rien
for(int io=1;io<513;io++)
{
TracksBuffer[nch][trkis][io]=0;
}
break;
case 1://up
switch(chaser_time_mode[nch])
{
case 0://mode solo
for(int io=1;io<513;io++)
{
TracksBuffer[nch][trkis][io]=(int)((((float) TrackContains[nch][trkis][io])/127*track_level[nch][trkis])*index_progression_chaser_step[nch]);
}
break;
case 1://mode joint
for(int io=1;io<513;io++)
{
TracksBuffer[nch][trkis][io]=(int)(((((float) TrackContains[nch][trkis][io])/127*track_level[nch][trkis])
*((1.0/joint_nbr_step[nch][trkis]) * (joint_nbr_step[nch][trkis]-count_steps_for_fades[nch][trkis])) ))//calcul de la base des steps
+(int)(((((float) TrackContains[nch][trkis][io])/127*track_level[nch][trkis])/joint_nbr_step[nch][trkis])*index_progression_chaser_step[nch]);
;
}
break;
default: break;
}
break;
case 2://stay
for(int io=1;io<513;io++)
{
TracksBuffer[nch][trkis][io]= (int)((((float)TrackContains[nch][trkis][io])/127)*track_level[nch][trkis]);
}
break;
case 3://down
switch(chaser_time_mode[nch])
{
case 0://mode solo
for(int io=1;io<513;io++)
{
TracksBuffer[nch][trkis][io]=(int)((((float) TrackContains[nch][trkis][io])/127)*track_level[nch][trkis]*(1-index_progression_chaser_step[nch]));
}
break;
case 1://mode joint
for(int io=1;io<513;io++)
{
TracksBuffer[nch][trkis][io]=(int)(((((float) TrackContains[nch][trkis][io])/127*track_level[nch][trkis])
*(1-(((1.0/joint_nbr_step[nch][trkis]) * (joint_nbr_step[nch][trkis]-count_steps_for_fades[nch][trkis])) ))//calcul de la base des steps
-(int)(((((float) TrackContains[nch][trkis][io])/127*track_level[nch][trkis])/joint_nbr_step[nch][trkis])*index_progression_chaser_step[nch])));
;
}
break;
default: break;
}
break;
default: break;
}

//MERGE ALL  TRACKS OF A CHASER
 for (int j=1;j<513;j++)
       {
        MergerBufferChasers[nch][j]=Tmax(MergerBufferChasers[nch][j],TracksBuffer[nch][trkis][j]);
       }
}
}

}


 return(0);
}

int chaser_clear_preset(int numchaser, int presettrk)
{
for(int tr=0;tr<core_user_define_nb_tracks_per_chasers;tr++)
{
chaser_preset[numchaser][presettrk][tr] =0;    //bool chaser_preset[128][4][24];
}
return(0);
}

int DoClearChaserTrack(int numchaser, int numtrack)
{
 for (int dc=1;dc<514;dc++)
 {
 TrackContains[numchaser][numtrack][dc]=0;//nettoyage du fader
 }
 for(int p=0;p<nbre_de_cases_par_track;p++)
 {
 chaser_step_operation[numchaser][numtrack][p]=0;
 track_is_on[numchaser][numtrack]=1;
 track_level[numchaser][numtrack]=127;
 TrackTypeIs[numchaser][numtrack]=0;
 strcpy(chaser_track_name[numchaser][numtrack],"");
 }
sprintf(string_Last_Order,">> Cleared Track %d Chaser %d",numtrack+1,numchaser+1);
 return(0);
}

int DoClearAChaser(int numchaser)
{
chaser_operator_is=0;
time_unit[numchaser]=1.0;
strcpy(chaser_name[numchaser],"");
chaser_is_playing[numchaser]=0;
chaser_is_in_loop[numchaser]=0;
chaser_way[numchaser]=0;
chaser_aller_retour[numchaser]=0;
position_affichage_track_num[numchaser]=0;
view_chaser_affected_to_fader[numchaser][0]=999;
view_chaser_affected_to_fader[numchaser][1]=999;
chaser_step_is[numchaser]=0;
chaser_begin_step_is[numchaser]=0;
chaser_end_step_is[numchaser]=nbre_de_cases_par_track;
chaser_time_mode[numchaser]=0;

for(int pt=0;pt<4;pt++)
{
chaser_clear_preset(numchaser,pt);
}

for(int o=0;o<core_user_define_nb_tracks_per_chasers;o++)
{
 DoClearChaserTrack(numchaser,o);
}


sprintf(string_Last_Order,">> Cleared Chaser %d",numchaser+1);
 return(0);
}

int DoDockChaserTrack(int numchaser, int numtrack)
{

 if(numeric_postext==0)//si pas de chaine de caracteres tapés
 {
 TrackTypeIs[numchaser][numtrack]=0;//le type est 0, circuits normaux
 if(index_blind==0)
 {
 for (int dc=1;dc<514;dc++)
 {
 TrackContains[numchaser][numtrack][dc]=0;//nettoyage du fader
 TrackContains[numchaser][numtrack][dc]=bufferSequenciel[dc];
 //rajout
 Selected_Channel[dc]=0;
 }
 index_do_dock=0;
 sprintf(string_Last_Order,">>n Stage Stored in Chaser %d Track %d",numchaser+1, numtrack+1);
 }

 else if(index_blind==1)
 {
 for (int dc=1;dc<514;dc++)
 {
 TrackContains[numchaser][numtrack][dc]=bufferBlind[dc];
 }
 index_do_dock=0;
 sprintf(string_Last_Order,">>n Preset Stored in Chaser %d Track %d",numchaser+1, numtrack+1);
 }
 }
 else if (numeric_postext>0)
 {
 int mem_to_load_in_chaser= (int)(atof(numeric)*10.0001);
 if(MemoiresExistantes[mem_to_load_in_chaser]==1)
 {
 DoClearChaserTrack(numchaser,numtrack);
 TrackTypeIs[numchaser][numtrack]=1;
 mem_to_load_in_chaser= (int)(atof(numeric)*10.0001);
 TrackHasMem[numchaser][numtrack]=mem_to_load_in_chaser;
 sprintf(chaser_track_name[numchaser][numtrack],descriptif_memoires[mem_to_load_in_chaser]);
 reset_numeric_entry();
 sprintf(string_Last_Order,">>n Stored Mem %.1f in Chaser %d Track %d",(float (mem_to_load_in_chaser))/10,numchaser+1,numtrack+1);
 mem_to_load_in_chaser= 0;
 }
 else
 {sprintf(string_Last_Order,">>n Mem %.1f doesn't exist",(float (mem_to_load_in_chaser))/10);  }

 }
 return(0);
}




int chaser_load_from_preset(int numchaser, int presettrk)
{
for(int tr=0;tr<core_user_define_nb_tracks_per_chasers;tr++)
{
track_is_on[numchaser][tr]=chaser_preset[numchaser][presettrk][tr];    //bool chaser_preset[128][4][24];
}
sprintf(string_Last_Order,">> Loaded ON Tracks from Preset %d in Chaser %d ",presettrk+1,numchaser+1);
return(0);
}

int chaser_store_in_preset(int numchaser, int presettrk)
{
for(int tr=0;tr<core_user_define_nb_tracks_per_chasers;tr++)
{
chaser_preset[numchaser][presettrk][tr] =track_is_on[numchaser][tr];    //bool chaser_preset[128][4][24];
}
sprintf(string_Last_Order,">> Stored ON Tracks from Chaser %d in Preset %d",numchaser+1,presettrk+1);
 return(0);
}


int DoModifyChaserTrack(int numchaser, int numtrack)
{


 TrackTypeIs[numchaser][numtrack]=0;//le type est 0, circuits normaux
 if(index_blind==0)
 {
 for (int dc=1;dc<514;dc++)
 {
 if(Selected_Channel[dc]==1)
 {
 TrackContains[numchaser][numtrack][dc]=bufferSequenciel[dc];
 //rajout
 Selected_Channel[dc]=0;
 }
 }
 index_do_modify=0;
 sprintf(string_Last_Order,">>n Modified Chaser %d Track %d",numchaser+1, numtrack+1);
 }

 else if(index_blind==1)
 {
 for (int dc=1;dc<514;dc++)
 {
 if(Selected_Channel[dc]==1)
 {
 TrackContains[numchaser][numtrack][dc]=bufferBlind[dc];
 }
 }
 index_do_modify=0;
 sprintf(string_Last_Order,">> Modified from Preset Chaser %d Track %d",numchaser+1, numtrack+1);
 }

 return(0);
}



int DoReportChaserTrack(int numchaser, int numtrack)
{
 for (int u=1;u<514;u++)
 {
 TrackContains[numchaser][numtrack][u]=bufferSaisie[u];
 if(bufferFaders[u]>TrackContains[numchaser][numtrack][u]){TrackContains[numchaser][numtrack][u]=bufferFaders[u];}
 }
 for (int x=1;x<514;x++)
 {
 bufferSaisie[x]=0;
 bufferBlind[x]=0;
 Selected_Channel[x]=0;
 }

 for (int fder=0;fder<48;fder++)
 {
 if(view_chaser_affected_to_fader[numchaser][0]!=fder)
 {
 Fader[fder]=0;
 }
 }


 return(0);
}

int chaser_seek_at_beg(int numchase)
{
switch(chaser_way[numchase])
{
case 0:
chaser_step_is[numchase]=chaser_begin_step_is[numchase];
break;
case 1:
chaser_step_is[numchase]=chaser_end_step_is[numchase];
break;
default: break;
}
index_progression_chaser_step[numchase]=0.0;
chaser_calcul_step(numchase,0.0);
chaser_calcul_time_joint(numchase);
sprintf(string_Last_Order,">> SEEK to Begin Position Chaser %d",numchase+1);
return(0);
}

int chaser_select_all_track(int numchase)
{
for (int co=0;co<core_user_define_nb_tracks_per_chasers;co++)
{
track_is_on[numchase][co]=1;
}
sprintf(string_Last_Order,">> ALL tracks ON in Chaser %d",numchase+1);
 return(0);
}

int chaser_select_off_all_track(int numchase)
{
for (int co=0;co<core_user_define_nb_tracks_per_chasers;co++)
{
track_is_on[numchase][co]=0;
}
sprintf(string_Last_Order,">> ALL tracks OFF in Chaser %d",numchase+1);
 return(0);
}
int chaser_select_inv_track(int numchase)
{
for (int co=0;co<core_user_define_nb_tracks_per_chasers;co++)
{
track_is_on[numchase][co]=toggle(track_is_on[numchase][co]);
}
sprintf(string_Last_Order,">> INVERSE ON-OFF tracks in Chaser %d",numchase+1);
return(0);
}

int chaser_select_no_track(int numchase)
{
for (int co=0;co<core_user_define_nb_tracks_per_chasers;co++)
{
track_is_on[numchase][co]=0;
}
sprintf(string_Last_Order,">> UnSelected ALL tracks in Chaser %d",numchase+1);
 return(0);
}


int bouton_view_track_downup_core(int xcha, int ycha, bool state)
{
if( mouse_x>xcha+20-12 && mouse_x<xcha+20+12 && mouse_y>ycha+25-12 && mouse_y<ycha+25+12)
{
show_type_midi(976, "View Track UP");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(976,Midi_Faders_Affectation_Mode);
}
else
{
position_affichage_track_num[chaser_selected]--;
if(position_affichage_track_num[chaser_selected]<0){position_affichage_track_num[chaser_selected]=0;}
}
mouse_released=1;
}
if(mouse_x>xcha+20-12 && mouse_x<xcha+20+12 && mouse_y>ycha+55-12 && mouse_y<ycha+55+12)
{
show_type_midi(977, "View Track DOWN");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(977,Midi_Faders_Affectation_Mode);
}
else
{
position_affichage_track_num[chaser_selected]++;
if(position_affichage_track_num[chaser_selected]> core_user_define_nb_tracks_per_chasers-nbre_track_visualisables)
{position_affichage_track_num[chaser_selected]= core_user_define_nb_tracks_per_chasers-nbre_track_visualisables;}
mouse_released=1;
}
}
return(0);
}


int bouton_view_launchpad_pos_core(int xcha, int ycha, bool state)
{
//launchpad position remote

if( mouse_x>xcha+20-12 && mouse_x<xcha+20+12 && mouse_y>ycha+25-12 && mouse_y<ycha+25+12)
{
show_type_midi(1113, "Launchpad Ctrl Pos Minus");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1113,Midi_Faders_Affectation_Mode);
}
else
{
chaser_step_launchpad[chaser_selected]--;
if(chaser_step_launchpad[chaser_selected]<0){chaser_step_launchpad[chaser_selected]=0;}
}
mouse_released=1;
}
if(mouse_x>xcha+50-12 && mouse_x<xcha+50+12 && mouse_y>ycha+25-12 && mouse_y<ycha+25+12)
{
show_type_midi(1114, "Launchpad Ctrl Pos Plus");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1114,Midi_Faders_Affectation_Mode);
}
else
{
chaser_step_launchpad[chaser_selected]++;
if(chaser_step_launchpad[chaser_selected]>nbre_de_cases_par_track-8 ) {chaser_step_launchpad[chaser_selected]=nbre_de_cases_par_track-8;}
}
mouse_released=1;
}
return(0);
}
////////////////////////////////////////////////////////////////////////////////

int Track_draw_logical(int xp, int yp,int num_track)
{

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
char temp_str_tr[72];
sprintf(temp_str_tr,"Chaser Track ON %d",num_track);
show_type_midi(998+num_track,temp_str_tr );
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_to_control(998+num_track, Midi_Faders_Affectation_Type,  Midi_Faders_Affectation_Mode);
}
else
{
if(index_do_dock==0 && index_main_clear==0 && index_do_modify==0 && index_do_report==0 && index_type==0)
{
track_is_on[chaser_selected][num_track]=toggle(track_is_on[chaser_selected][num_track]);

midi_levels[998+num_track]=track_is_on[chaser_selected][num_track]*127;
midi_send_out[998+num_track]=1;
}
if(index_enable_edit_chaser==1)
{
if(index_do_dock==1  && index_main_clear==0 && index_do_modify==0 && index_do_report==0 && index_type==0)
{
chaser_selected_for_record=chaser_selected;
track_selected_for_record=num_track;
index_do_dock_track=1;
index_ask_confirm=1;
}
else if(index_main_clear==0  && index_do_dock==0 && index_do_modify==1 && index_do_report==0 && index_type==0)
{
chaser_selected_for_record=chaser_selected;
track_selected_for_record=num_track;
index_do_modify_track=1;
index_ask_confirm=1;
}
else if(index_main_clear==0  && index_do_dock==0 && index_do_modify==0 && index_do_report==1 && index_type==0)
{
chaser_selected_for_record=chaser_selected;
track_selected_for_record=num_track;
index_do_report_track=1;
index_ask_confirm=1;
}
else if(index_main_clear==1  && index_do_dock==0 && index_do_modify==0 && index_do_report==0 && index_type==0)
{
chaser_selected_for_record=chaser_selected;
track_selected_for_record=num_track;
index_do_clear_track=1;
index_ask_confirm=1;
}
else if(index_main_clear==0  && index_do_dock==0 && index_do_modify==0 && index_do_report==0 && index_type==1)
{
sprintf(chaser_track_name[chaser_selected][num_track],numeric);
reset_numeric_entry();
if(index_text_auto_close==1){index_type=0;}
}
}
mouse_released=1;
}
}


////////TRACK LEVEL////////////////////////////////////////////////////////////////

if(mouse_x>=xp+30 && mouse_x<=xp+30+127 && mouse_y>yp && mouse_y<yp+10)
{
char temp_str_tr[72];
sprintf(temp_str_tr,"Chaser Track LEVEL %d",num_track);
show_type_midi(1023+num_track,temp_str_tr );
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_to_control(1023+num_track, Midi_Faders_Affectation_Type,  Midi_Faders_Affectation_Mode);
}
else
{
set_mouse_range(xp+30 ,yp,xp+30 +127 , yp+10);//pour pas deborder
track_level[chaser_selected][num_track]= mouse_x-(Xchasers+30+5);
if(track_level[chaser_selected][num_track]<0){track_level[chaser_selected][num_track]=0;}
if(track_level[chaser_selected][num_track]>127){track_level[chaser_selected][num_track]=127;}
midi_levels[1023+num_track]=track_level[chaser_selected][num_track];
if(midi_send_out[1023+num_track]==1){index_send_midi_out[1023+num_track]=1;}
}
}

if(mouse_x>=xp+180-5 && mouse_x<=xp+180+5 && mouse_y>yp+22-5 && mouse_y<yp+22+5)
{
midi_send_out[1023+num_track]=toggle(midi_send_out[1023+num_track]);
mouse_released=1;
}


raccrochage_midi_logical_horizontal_little (xp+30,yp,1023+num_track, 127, 10);

//type de mouvement dans le step
if(index_enable_edit_chaser==1)
{
for(int chcase=0;chcase<nbre_de_cases_par_track;chcase++)
{
if(mouse_x>xp+170+(chcase*12) && mouse_x<xp+170+(chcase*12)+12 && mouse_y>yp && mouse_y<yp+12)
{
if(chaser_step_operation[chaser_selected][num_track][chcase]!=chaser_operator_is)//si op different on affecte
{chaser_step_operation[chaser_selected][num_track][chcase]=chaser_operator_is;}
else//sinon on toggle on off l operator
{
chaser_step_operation[chaser_selected][num_track][chcase]=0;
}
refresh_launchpad_on_chaser();
mouse_released=1;
}
}
}



//suivi de la time line en midi

if( launchpad_chaser_mode==1)
{
char tmp_str_stp[36];
if(num_track-position_affichage_track_num[chaser_selected]<chaser_midi_rows)
{
for(int chcase=0;chcase<nbre_de_cases_par_track;chcase++)
{
if(mouse_x>xp+170+(chcase*12) && mouse_x<xp+170+(chcase*12)+12 && mouse_y>yp && mouse_y<yp+12)
{
switch(chaser_way[chaser_selected])
{
case 0:
if( chcase>=chaser_step_is[chaser_selected] && chcase<chaser_step_is[chaser_selected]+8 )
{
sprintf(tmp_str_stp,"Step %d Chaser Row %d" ,chcase-chaser_step_is[chaser_selected]+1,num_track-position_affichage_track_num[chaser_selected]+1 );
show_type_midi(1048+(chcase-chaser_step_is[chaser_selected])+((num_track-position_affichage_track_num[chaser_selected])*8), tmp_str_stp);
if(Midi_Faders_Affectation_Type!=0 )//config midi
{
attribute_midi_to_control(1048+(chcase-chaser_step_is[chaser_selected])+((num_track-position_affichage_track_num[chaser_selected])*8), Midi_Faders_Affectation_Type,  Midi_Faders_Affectation_Mode);
}
}
break;
case 1:
if( chcase>chaser_step_is[chaser_selected]-8 && chcase<=chaser_step_is[chaser_selected] )
{
sprintf(tmp_str_stp,"Step %d Chaser Row %d" ,(chcase-(chaser_step_is[chaser_selected]-8)),num_track-position_affichage_track_num[chaser_selected]+1 );
show_type_midi(1048+((chcase-(chaser_step_is[chaser_selected]-8))-1)+((num_track-position_affichage_track_num[chaser_selected])*8), tmp_str_stp);
if(Midi_Faders_Affectation_Type!=0 )//config midi
{
attribute_midi_to_control(1048+((chcase-(chaser_step_is[chaser_selected]-8))-1)+((num_track-position_affichage_track_num[chaser_selected])*8), Midi_Faders_Affectation_Type,  Midi_Faders_Affectation_Mode);
}
}
break;
default: break;
}
}
}
}
}

return(0);
}


int do_logical_fenetre_chasers(int xcha,int ycha)
{


//////PARTIE GENERALE DU CHASER///////////////////////////////////////////////

//UP DOWN chasers number selected


if( mouse_x>xcha+220-12 && mouse_x<xcha+220+12 && mouse_y>ycha+25-12 && mouse_y<ycha+25+12  )
{
show_type_midi(974, "Previous CHASER");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(974,Midi_Faders_Affectation_Mode);
}
else
{
chaser_selected--;
if(chaser_selected<0){chaser_selected=core_user_define_nb_chasers-1;}
refresh_chaser_midi_out();
}
mouse_released=1;
}
if(mouse_x>xcha+300-12 && mouse_x<xcha+300+12 && mouse_y>ycha+25-12 && mouse_y<ycha+25+12 )
{
show_type_midi(975, "Next CHASER");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(975,Midi_Faders_Affectation_Mode);
}
else
{
chaser_selected++;
if(chaser_selected>core_user_define_nb_chasers-1){chaser_selected=0;}
refresh_chaser_midi_out();
}
mouse_released=1;
}
//////////////////////TEXT////////////////////////////////////////////


if(index_enable_edit_chaser==1 && index_type==1 && mouse_x>xcha+330 && mouse_x<xcha+330+185 && mouse_y>ycha+10 && mouse_y<ycha+10+30)
{
sprintf(chaser_name[chaser_selected],numeric);
reset_numeric_entry();if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
}
//////////////EDIT MODE
if(mouse_x>xcha+560 && mouse_x<xcha+560+50 && mouse_y>ycha+10 && mouse_y<ycha+10+20 )
{
if(mouse_button==1 && mouse_released==0)
{
index_enable_edit_chaser=toggle(index_enable_edit_chaser);
mouse_released=1;
}
}

////////////////////////////////boutons d action de la lecture globale du chaser
//play
if(mouse_x>xcha+10 && mouse_x<xcha+10+20 && mouse_y>ycha+50 && mouse_y<ycha+50+20  && mouse_released==0)
{
show_type_midi(978, "Play Selected CHASER");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(978,Midi_Faders_Affectation_Mode);
}
else
{
chaser_is_playing[chaser_selected]=toggle(chaser_is_playing[chaser_selected]);
if(chaser_is_playing[chaser_selected]==1)//snap du temps at beg
{
chaser_start_time[chaser_selected]=actual_time;
//bug olivier marche arriere arrière ligne
if(chaser_step_is[chaser_selected]<0){chaser_step_is[chaser_selected]=0;}
else if(chaser_step_is[chaser_selected]>35){chaser_step_is[chaser_selected]=35;}
}
}
mouse_released=1;
}
//seek to begin
if(mouse_x>xcha+40 && mouse_x<xcha+40+20 && mouse_y>ycha+50 && mouse_y<ycha+50+20  && mouse_button==1 && mouse_released==0)
{
show_type_midi(979, "Seek to Beg Selected CHASER");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(979,Midi_Faders_Affectation_Mode);
}
else
{
chaser_seek_at_beg(chaser_selected);
}
mouse_released=1;
}

//loop
if(mouse_x>xcha+70 && mouse_x<xcha+70+20 && mouse_y>ycha+50 && mouse_y<ycha+50+20  && mouse_button==1 && mouse_released==0)
{
show_type_midi(980, "Loop Selected CHASER");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(980,Midi_Faders_Affectation_Mode);
}
else
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
mouse_released=1;
}





//forward sens
if(mouse_x>xcha+110 && mouse_x<xcha+110+20 && mouse_y>ycha+50 && mouse_y<ycha+50+20 && mouse_released==0)
{
show_type_midi(981, "Chaser Forward WAY");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(981,Midi_Faders_Affectation_Mode);
}
else
{
chaser_way[chaser_selected]=0;
sprintf(string_Last_Order,">> FORWARD WAY Chaser %d",chaser_selected+1);
}
mouse_released=1;
}


//backward sens
if(mouse_x>xcha+140 && mouse_x<xcha+140+20 && mouse_y>ycha+50 && mouse_y<ycha+50+20&& mouse_released==0)
{
show_type_midi(982, "Chaser Backward WAY");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(982,Midi_Faders_Affectation_Mode);
}
else
{
chaser_way[chaser_selected]=1;
sprintf(string_Last_Order,">> BACKWARD WAY Chaser %d",chaser_selected+1);
}
mouse_released=1;
}


//backward and forward sens
if(mouse_x>xcha+170 && mouse_x<xcha+170+20 && mouse_y>ycha+50 && mouse_y<ycha+50+20 && mouse_released==0)
{
show_type_midi(983, "Chaser ALLER-RETOUR WAY");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(983,Midi_Faders_Affectation_Mode);
}
else
{
chaser_aller_retour[chaser_selected]=toggle(chaser_aller_retour[chaser_selected]);
sprintf(string_Last_Order,">> ALLER-RETOUR WAY Chaser %d",chaser_selected+1);
}
mouse_released=1;
}


////AFFECT TO DOCK
if(mouse_x>xcha+430 && mouse_x<xcha+430+110 && mouse_y>ycha+80 && mouse_y<ycha+80+20  && mouse_released==0)
{
if(index_affect_chaser_to_dock==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_affect_chaser_to_dock=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_affect_chaser_to_dock;
mouse_released=1;
}


/////////////ACTIONS SUR ON TRACK ET SELECTIONS
if(mouse_x>xcha+10 && mouse_x<xcha+10+20 && mouse_y>ycha+80 && mouse_y<ycha+80+20 )
{
show_type_midi(984, "Chaser ON/OFF ALL tracks");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(984,Midi_Faders_Affectation_Mode);
}
else
{
//action Select ALL tracks
chaser_select_all_track(chaser_selected);
}
mouse_released=1;
}


//selections//////////////////////////////////////////////////
if(mouse_x>xcha+40 && mouse_x<xcha+40+20 && mouse_y>ycha+80 && mouse_y<ycha+80+20 )
{
//action Select INV tracks
show_type_midi(985, "Chaser ON/OFF Inversed Tracks");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(985,Midi_Faders_Affectation_Mode);
}
else
{
chaser_select_inv_track(chaser_selected);
}
mouse_released=1;
}

if(mouse_x>xcha+70 && mouse_x<xcha+70+20 && mouse_y>ycha+80 && mouse_y<ycha+80+20 )
{
//action Select OFF ALL tracks
show_type_midi(986, "Chaser ALL OFF Tracks");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(986,Midi_Faders_Affectation_Mode);
}
else
{
chaser_select_off_all_track(chaser_selected);
}
mouse_released=1;
}





/////////////////presets de selection////////////////////////////////////////
for(int po=0;po<4;po++)
{
if(mouse_x>xcha+110+(po*30) && mouse_x<xcha+110+(po*30)+20 && mouse_y>ycha+80 && mouse_y<ycha+80+20 )
{
char tlp_str[64];
sprintf(tlp_str,"Chaser Track Preset %d in Chaser %d", po+1, chaser_selected+1);
show_type_midi(987+po,tlp_str );
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(987+po,Midi_Faders_Affectation_Mode);
}
else
{
if(index_do_dock==0 && index_main_clear==0)
{
chaser_load_from_preset(chaser_selected,po);
mouse_released=1;
}
if(index_enable_edit_chaser==1)
{
if(index_do_dock==1 && index_main_clear==0)
{
chaser_selected_for_record=chaser_selected;
chaser_preset_selected_for_record=po;
index_do_store_chaser_preset=1;
index_ask_confirm=1;
mouse_released=1;
}
else if( index_main_clear==1 && index_do_dock==0 )
{
chaser_selected_for_record=chaser_selected;
chaser_preset_selected_for_record=po;
index_do_clear_chaser_preset=1;
index_ask_confirm=1;
mouse_released=1;
}
}
}

}
}


                               ////////////////////Time unit////////////////////////////////////////
if(mouse_x>xcha+245 && mouse_x<xcha+245+50 && mouse_y>ycha+50 && mouse_y<ycha+50+20)
{
time_unit[chaser_selected]=atof(numeric);
if(time_unit[chaser_selected]<=0.0001){time_unit[chaser_selected]=0.0001;}
reset_numeric_entry();
mouse_released=1;
}

if(mouse_x>xcha+305 && mouse_x<xcha+305+30 && mouse_y>ycha+50 && mouse_y<ycha+50+20)
{
show_type_midi(994,"Chaser Time TYPE" );
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(994,Midi_Faders_Affectation_Mode);
}
else
{
chaser_time_mode[chaser_selected]=toggle(chaser_time_mode[chaser_selected]);
}
mouse_released=1;
}

                 ////////////////////CHASER OPERATOR/////////////////////////////////////
//up
if(mouse_x>xcha+245 && mouse_x<xcha+245+40 && mouse_y>ycha+80 && mouse_y<ycha+80+20)
{
show_type_midi(991, "Chaser Set Position FADE IN");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(991,Midi_Faders_Affectation_Mode);
}
else
{
 if(chaser_operator_is!=1){chaser_operator_is=1; }
 else {chaser_operator_is=0;}
 }
mouse_released=1;
}
//stay
if(mouse_x>xcha+295 && mouse_x<xcha+295+40 && mouse_y>ycha+80 && mouse_y<ycha+80+20)
{
show_type_midi(992, "Chaser Set Position STAY");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(992,Midi_Faders_Affectation_Mode);
}
else
{
 if(chaser_operator_is!=2){chaser_operator_is=2;  }
 else {chaser_operator_is=0;}
}
mouse_released=1;
}
//down
if(mouse_x>xcha+345 && mouse_x<xcha+345+40 && mouse_y>ycha+80 && mouse_y<ycha+80+20)
{
show_type_midi(993, "Chaser Set Position FADE OUT");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(993,Midi_Faders_Affectation_Mode);
}
else
{
 if(chaser_operator_is!=3){chaser_operator_is=3; }
 else {chaser_operator_is=0;}
 }
mouse_released=1;
}

                                 ///TIMELINE
//IN POINT
if(mouse_x>xcha+175 && mouse_x<xcha+175+(nbre_de_cases_par_track*12) && mouse_y>ycha+115 && mouse_y<ycha+115+12)
{
show_type_midi(995, "Chaser Set BEGIN POINT");
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(995,Midi_Faders_Affectation_Mode);
}
else
{
set_mouse_range(xcha+175,ycha+115,xcha+175+(nbre_de_cases_par_track*12) , ycha+115+12);//pour pas deborder
chaser_begin_step_is[chaser_selected]=(int)(((float)(mouse_x- (xcha+175)))/12);
if(chaser_begin_step_is[chaser_selected]>=chaser_end_step_is[chaser_selected])
{chaser_begin_step_is[chaser_selected]=chaser_end_step_is[chaser_selected]-1;}
if(chaser_begin_step_is[chaser_selected]<0){chaser_begin_step_is[chaser_selected]=0;}
midi_levels[995]=(int)(((float)(chaser_begin_step_is[chaser_selected])/36)*127);
index_send_midi_out[995]=1;
}
}
//OUT POINT
if(mouse_x>xcha+175 && mouse_x<xcha+175+(nbre_de_cases_par_track*12) && mouse_y>ycha+127 && mouse_y<ycha+127+12)
{
show_type_midi(996, "Chaser Set END POINT");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(996,Midi_Faders_Affectation_Mode);
}
else
{
set_mouse_range(xcha+175,ycha+127,xcha+175+(nbre_de_cases_par_track*12) , ycha+127+12);//pour pas deborder
chaser_end_step_is[chaser_selected]=(int)(((float)(mouse_x- (xcha+175)))/12);
if(chaser_end_step_is[chaser_selected]<=chaser_begin_step_is[chaser_selected])
{chaser_end_step_is[chaser_selected]=chaser_begin_step_is[chaser_selected]+1;}
if(chaser_end_step_is[chaser_selected]>nbre_de_cases_par_track){chaser_end_step_is[chaser_selected]=nbre_de_cases_par_track;}
midi_levels[996]=(int)(((float)(chaser_end_step_is[chaser_selected])/36)*127);
index_send_midi_out[996]=1;
}
}


//TImeline position curseur
if(mouse_x>xcha+175 && mouse_x<xcha+175+(nbre_de_cases_par_track*12) && mouse_y>ycha+145 && mouse_y<ycha+145+10)
{
show_type_midi(997, "Chaser Set TIMELINE POSITION");
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(997,Midi_Faders_Affectation_Mode);
}
else
{
set_mouse_range(xcha+175,ycha+145,xcha+175+(nbre_de_cases_par_track*12) , ycha+145+10);//pour pas deborder
chaser_step_is[chaser_selected]=(int)((mouse_x-( Xchasers+175))/12);
chaser_calcul_step(chaser_selected,12.0/(float)((mouse_x-( Xchasers+175))/12));
chaser_calcul_time_joint(chaser_selected);
midi_levels[997]=(int)(((float)(chaser_step_is[chaser_selected])/36)*127);
index_send_midi_out[997]=1;
sprintf(string_Last_Order,"Chaser %d Time Line move to step %d",chaser_selected+1,chaser_step_is[chaser_selected]+1);
}
}
////////////////////////UP DOWN POS TRACK///////////////////////////////////
/////////////////////VIEW TRACK BUTTON////////////////////////////////////////////////
bouton_view_track_downup_core(xcha+580, ycha+35,0);

/////////////////////TRACK//////////////////////////////////////////////////
for(int track_num=0;track_num<nbre_track_visualisables;track_num++)
{
Track_draw_logical(xcha+5,ycha+165+(track_num*40),position_affichage_track_num[chaser_selected]+track_num);
}

//asservissement à la vitesse de l acceleromètre du fader
if(mouse_x>xcha+345 && mouse_x<xcha+345+40 && mouse_y>ycha+50 && mouse_y<ycha+50+20)
{
index_slave_chaser_to_accelerometre[chaser_selected]=toggle(index_slave_chaser_to_accelerometre[chaser_selected]);
mouse_released=1;
}
//allow launchpad
if(mouse_x>xcha+410 && mouse_x<xcha+410+40 && mouse_y>ycha+50 && mouse_y<ycha+50+20)
{
launchpad_chaser_mode=toggle(launchpad_chaser_mode);
mouse_released=1;
}
if(launchpad_chaser_mode==1)
{
bouton_view_launchpad_pos_core(xcha+450, ycha+35,0);
}

//refresh midi

if(mouse_x>xcha+520 && mouse_x<xcha+520+40 && mouse_y>ycha+50 && mouse_y<ycha+50+20 && mouse_released==0)
{
refresh_midi_chasers=toggle( refresh_midi_chasers);
set_refresh_mode_for_chaser(refresh_midi_chasers);
mouse_released=1;
}

 return(0);
}


int set_chaser_tempo_unit( int the_chas)
{
time_unit[the_chas]=tap_tempo_average;
if(time_unit[the_chas]<=0.0001){time_unit[the_chas]=0.0001;}
sprintf(string_Last_Order,"Received Tap Tempo in Chaser %d", the_chas+1);
return(0);
}


int do_autolaunch()
{
for (int cmptfader=0;cmptfader<48;cmptfader++)
{
  //autolaunch embedded
  if(autolaunch[cmptfader]==1   )
  {

    if(( Fader[cmptfader]!=Fader_previous[cmptfader]) || ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] ) )
   {


   //commande embeded
   int the_chaser;
   int the_grid_player;
   int the_audio_player;
        switch(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]])
        {
        case 6://vol
        the_audio_player=DockHasAudioVolume[cmptfader][dock_used_by_fader_is[cmptfader]]-1;

if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
if  (Fader[cmptfader]==0)
{
player1->stop();
if(player_is_onloopCue[0]==0  ){player1->setPosition(0);}
else
{player1->setPosition(player_seek_position[0]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] ))  player1->play();
break;
case 1://player 2
if  (Fader[cmptfader]==0)
{
player2->stop();
if(player_is_onloopCue[1]==0  ){player2->setPosition(0);}
else
{player2->setPosition(player_seek_position[1]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player2->play();
break;
case 2://player 3
if  (Fader[cmptfader]==0)
{
player3->stop();
if(player_is_onloopCue[2]==0  ){player1->setPosition(0);}
else
{player3->setPosition(player_seek_position[2]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player3->play();
break;
case 3://PLAYER 4
if  (Fader[cmptfader]==0)
{
player4->stop();
if(player_is_onloopCue[3]==0  ){player4->setPosition(0);}
else
{player4->setPosition(player_seek_position[3]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player4->play();
break;
default: break;
}
}
break;
case 7://pan
the_audio_player=DockHasAudioPan[cmptfader][dock_used_by_fader_is[cmptfader]]-1;
if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
if  (Fader[cmptfader]==0)
{
player1->stop();
if(player_is_onloopCue[0]==0  ){player1->setPosition(0);}
else
{player1->setPosition(player_seek_position[0]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] ))  player1->play();
break;
case 1://player 2
if  (Fader[cmptfader]==0)
{
player2->stop();
if(player_is_onloopCue[1]==0  ){player2->setPosition(0);}
else
{player2->setPosition(player_seek_position[1]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player2->play();
break;
case 2://player 3
if  (Fader[cmptfader]==0)
{
player3->stop();
if(player_is_onloopCue[2]==0  ){player1->setPosition(0);}
else
{player3->setPosition(player_seek_position[2]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player3->play();
break;
case 3://PLAYER 4
if  (Fader[cmptfader]==0)
{
player4->stop();
if(player_is_onloopCue[3]==0  ){player4->setPosition(0);}
else
{player4->setPosition(player_seek_position[3]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player4->play();
break;
default: break;
}
}
        break;
        case 8://pitch
        the_audio_player=DockHasAudioPitch[cmptfader][dock_used_by_fader_is[cmptfader]]-1;

if(player_ignited[the_audio_player]==1)
{
switch(the_audio_player)
{
case 0://PLAYER 1
if  (Fader[cmptfader]==0)
{
player1->stop();
if(player_is_onloopCue[0]==0  ){player1->setPosition(0);}
else
{player1->setPosition(player_seek_position[0]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] ))  player1->play();
break;
case 1://player 2
if  (Fader[cmptfader]==0)
{
player2->stop();
if(player_is_onloopCue[1]==0  ){player2->setPosition(0);}
else
{player2->setPosition(player_seek_position[1]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player2->play();
break;
case 2://player 3
if  (Fader[cmptfader]==0)
{
player3->stop();
if(player_is_onloopCue[2]==0  ){player1->setPosition(0);}
else
{player3->setPosition(player_seek_position[2]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player3->play();
break;
case 3://PLAYER 4
if  (Fader[cmptfader]==0)
{
player4->stop();
if(player_is_onloopCue[3]==0  ){player4->setPosition(0);}
else
{player4->setPosition(player_seek_position[3]);}
}
if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )) player4->play();
break;
default: break;
}
}
        break;
case 11://chasers
        the_chaser=ChaserAffectedToDck[cmptfader][dock_used_by_fader_is[cmptfader]];
        if  (Fader[cmptfader]==0) {chaser_is_playing[the_chaser]=0; chaser_seek_at_beg(the_chaser); }
        if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 ) || ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] )){chaser_is_playing[the_chaser]=1; }
break;
case 12://gridplayer
the_grid_player=faders_dock_grid_affectation[cmptfader][dock_used_by_fader_is[cmptfader]];
 if  (Fader[cmptfader]==0)
 {
 grider_is_playing[the_grid_player]=0;
 gridplayer_seek(the_grid_player);
 }
 if((Fader_previous[cmptfader]==0 && Fader[cmptfader]>0 )|| ( previous_dock_used[cmptfader]!=dock_used_by_fader_is[cmptfader] ))
 {grider_is_playing[the_grid_player]=1;grid_crossfade_start_time[the_grid_player]=actual_time;}
break;
default:
break;
       }
   }
   }

Fader_previous[cmptfader]=Fader[cmptfader];
previous_dock_used[cmptfader]=dock_used_by_fader_is[cmptfader];
}

 return(0);
}

int refresh_chaser_window_timeline_for_midi_out()
{
if( refresh_midi_chasers==1 && (int)(((float)(chaser_step_is[chaser_selected])/36)*127)!=midi_levels[997])
{
midi_levels[997]=(int)(((float)(chaser_step_is[chaser_selected])/36)*127);
index_send_midi_out[997]=1;
}
 return(0);
}
