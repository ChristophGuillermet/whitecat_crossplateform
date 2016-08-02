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

* \file sequentiel_6_core.cpp
* \brief {Core fonctions for the cuelist}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Core fonctions pour la fenêtre des memoires
*
*   Core fonctions for the cuelist
*
**/

int call_mem_onstage()
{
int mem_to_call=(int)(atof(numeric)*10.0001);
if (mem_to_call>10000)
{sprintf(string_Last_Order,"a Mem can't be > to 1000");}
else
{
if(MemoiresExistantes[mem_to_call]==0)
{
sprintf(string_Last_Order,"Mem %d.%d doesn't exist", mem_to_call/10,mem_to_call%10);
}
if (MemoiresExistantes[mem_to_call]==1 && mem_to_call!=0)//eviter cherger mem 0 en clickant vide
{
sprintf(string_Last_Order,"Loaded %d.%d on Stage", mem_to_call/10,mem_to_call%10);
position_onstage=mem_to_call;
refresh_mem_onstage(position_onstage);
detect_mem_before_one();
detect_mem_preset();
refresh_mem_onpreset(position_preset);
}
if (MemoiresExistantes[mem_to_call]==1 && mem_to_call==0)//eviter cherger mem 0 en clickant vide
{
sprintf(string_Last_Order,"Mem 0.0 can't be loaded on Stage");
}
}
reset_numeric_entry();
someone_changed_in_sequences=1;//icat
return(0);
}




int affect_time_from_chrono_to_mem(int mem_to_set_time)
{
//0=DIN 1=IN 2=DOUT 3=OUT    // le out concernant la mémoire précédente
for(int ty=0;ty<4;ty++)
{
 if(index_type_of_time_to_affect[ty]==1)
 {Times_Memoires[mem_to_set_time][ty]= (time_minutes*60)+time_secondes+ ((float)time_centiemes)/100; }
}
show_im_recording_a_time=1;
someone_changed_in_sequences=1;//icat
 return(0);
}

int call_mem_onpreset()
{

int mem_to_call=(int)(atof(numeric)*10.0001);
if ( mem_to_call>10000)
{sprintf(string_Last_Order,"a Mem can't be > to 1000");}
else
{
if(MemoiresExistantes[mem_to_call]==0)
{
sprintf(string_Last_Order,"Mem %d.%d doesn't exist", mem_to_call/10,mem_to_call%10);
}
else if (MemoiresExistantes[mem_to_call]==1)
{
sprintf(string_Last_Order,"Loaded %d.%d on preset", mem_to_call/10,mem_to_call%10);
position_preset=mem_to_call;
refresh_mem_onpreset(position_preset);
ratio_X1X2_together=ratio_cross_manuel[mem_to_call];
}
}
reset_numeric_entry();
someone_changed_in_sequences=1;//icat

return(0);
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////

int next_mem_crossfade_finished(int mem_is_now_onstage)
{
position_onstage=mem_is_now_onstage;
for (int a=0;a<514;a++)
{
bufferSaisie[a]=bufferBlind[a];
}
detect_mem_preset();
refresh_mem_onpreset(position_preset);
detect_mem_before_one();
niveauX1=255; niveauX2=0;
if(midi_send_out[493]==1){index_send_midi_out[493]=1;}
someone_changed_in_sequences=1;//icat
return(0);
}

int do_call_time_and_rec_f1_f2_f3(int mem_is)
{
if(numeric_postext>0 && index_affect_time==0 && index_do_dock==0 && index_do_modify==0 && index_do_report==0 )
{
if(call_stage==1){call_mem_onstage();}
else if(call_preset==1)
{
if(index_go==1 || index_pause==1)//double entree en cours de crossfade
{
for (int po=1;po<514;po++)
{
bufferSaisie[po]=bufferSequenciel[po];
}
niveauX1=255;
niveauX2=0;
prepare_crossfade();
floatX1=niveauX1;
floatX2=niveauX2;
}
call_mem_onpreset();
}
}

else if(index_affect_time==1 && index_do_dock==1 && numeric_postext==0 )//si la fenetre time est ouverte
{
affect_time_from_chrono_to_mem(mem_is);
}

else if( index_do_dock==1 && index_affect_time==0 )
{
 for (int dc=1;dc<514;dc++)
 {
 if(call_stage==1){Memoires[position_onstage][dc]=0;  }
 if(index_blind==0)
 {
 Memoires[mem_is][dc]=bufferSequenciel[dc];
 }
 else if(index_blind==1)
 {
 Memoires[mem_is][dc]=bufferBlind[dc];
 }
 Selected_Channel[dc]=0;
 }
 index_do_dock=0;
 ratio_cross_manuel[mem_is]= ratio_X1X2_together;
}
else if( index_do_dock==0 && index_do_modify==1 && index_do_report==0 && index_affect_time==0 )
{
 for (int dc=1;dc<514;dc++)
 {
 if(Selected_Channel[dc]==1)
 {
 if(index_blind==0)
 {
 Memoires[mem_is][dc]=bufferSequenciel[dc];
 }
 else if(index_blind==1)
 {
  Memoires[mem_is][dc]=bufferBlind[dc];
 }
 Selected_Channel[dc]=0;
 }
 }
 index_do_modify=0;
 ratio_cross_manuel[mem_is]= ratio_X1X2_together;
}
else if( index_do_dock==0 && index_do_modify==0 && index_do_report==1 && index_affect_time==0 )
{
if(index_blind==0)
 {
 for (int dc=1;dc<514;dc++)
 {
 if(bufferFaders[dc]>bufferSequenciel[dc]){Memoires[mem_is][dc]=bufferFaders[dc];}
 else { Memoires[mem_is][dc]=bufferSequenciel[dc]; }
 Selected_Channel[dc]=0;
 }
 for (int u=0;u<49;u++)
 {Fader[u]=0;}
 }
 else if(index_blind==1)
 {
 sprintf(string_Last_Order,">>Report concerns only on stage mode");
 }
 index_do_report=0;
 ratio_cross_manuel[mem_is]= ratio_X1X2_together;
}


return(0);
}


int do_logical_refresh_vision_memories( int x_seq, int y_seq)
{
//Manipulation en stage
if(mouse_y>y_seq+110 && mouse_y<y_seq+140)
{
if(mouse_x> x_seq+10 && mouse_x<x_seq+50)//DELAYS
{
affect_time_entry_to_mem(2,position_preset);
mouse_released=1;
}
if(mouse_x> x_seq+50 && mouse_x<x_seq+110)//IN OUT
{
affect_time_entry_to_mem(3,position_preset);
mouse_released=1;
}
if(mouse_x> x_seq+110 && mouse_x<x_seq+170)//MEMS
{
if(index_go==0 && index_pause==0 && index_go_back==0 )
{

call_stage=1;call_preset=0;
do_call_time_and_rec_f1_f2_f3(position_onstage);
mouse_released=1;
}
}
if(mouse_x> x_seq+170 && mouse_x<x_seq+180)//exclude mem from cuelist
{
MemoiresExclues[position_onstage]=toggle(MemoiresExclues[position_onstage]);
mouse_released=1;
}

if(mouse_x> x_seq+185 && mouse_x<x_seq+185+40)//LINKS
{
reset_indexs_confirmation();
index_do_link_memonstage=1;
index_ask_confirm=1;
mouse_released=1;
}
if(mouse_x> x_seq+225 && mouse_x<x_seq+265)//BANGER
{
affect_banger_number=atol(numeric);
if(affect_banger_number>=0 && affect_banger_number<128)
{
reset_indexs_confirmation();
index_do_banger_memonstage=1;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: banger is between 1 and 127, 0 to desaffect !");}
}

if(mouse_x> x_seq+275 && mouse_x<x_seq+300)//Gridplayer
{
gpl1_affect_step_to_mem=atoi(numeric);
if(gpl1_affect_step_to_mem>=0 && gpl1_affect_step_to_mem<=1024)
{
reset_indexs_confirmation();
index_do_affect_step_gridplayer_to_mem=1;
index_mem_to_be_affected_by_gpl=position_onstage;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: step is between 1 and 1024, 0 to desaffect !");}
}

if(mouse_x> x_seq+310 && mouse_x<x_seq+470)//TEXT DECRIPTION
{

if(index_type==1)
{

if(mouse_y>y_seq+110 && mouse_y<y_seq+110+15)
{
for(int tt=0;tt<24;tt++)
{
descriptif_memoires[position_onstage][tt]=numeric[tt];
}
descriptif_memoires[position_onstage][24]='\0';
}
else
{
for(int tt=0;tt<24;tt++)
{
annotation_memoires[position_onstage][tt]=numeric[tt];
}
annotation_memoires[position_onstage][24]='\0';
}

reset_numeric_entry();numeric_postext=0;
someone_changed_in_sequences=1;//icat
mouse_released=1;
}
if(index_text_auto_close==1){index_type=0;}

}
}

//Manipulation en preset
if(mouse_y>y_seq+140 && mouse_y<y_seq+170)
{
if(mouse_x> x_seq+10 && mouse_x<x_seq+50)//DELAYS
{
affect_time_entry_to_mem(0,position_preset);
mouse_released=1;
}
if(mouse_x> x_seq+50 && mouse_x<x_seq+110)//IN OUT
{
affect_time_entry_to_mem(1,position_preset);
mouse_released=1;
}
if(mouse_x> x_seq+110 && mouse_x<x_seq+170)//MEMS
{
if(index_go==0 && index_pause==0 && index_go_back==0 )//pas de cross en cours
{

call_preset=1;call_stage=0;
do_call_time_and_rec_f1_f2_f3(position_preset);

mouse_released=1;
}
else if((index_go==1 || index_pause==1 ) && index_go_back==0 ) //cross ou pause en cours
{
 reset_indexs_confirmation();
 index_do_jump_while_cross=1;
 index_ask_confirm=1;
 mouse_released=1;
}
}
if(mouse_x> x_seq+170 && mouse_x<x_seq+180)//exclude mem from cuelist
{
MemoiresExclues[position_preset]=toggle(MemoiresExclues[position_preset]);
mouse_released=1;
}

if(mouse_x> x_seq+185  && mouse_x<x_seq+180+35)//LINKS
{
reset_indexs_confirmation();
index_do_link_memonpreset=1;
index_ask_confirm=1;
mouse_released=1;
}
if(mouse_x> x_seq+225 && mouse_x<x_seq+265)//BANGER
{
affect_banger_number=atol(numeric);
if(affect_banger_number>=0 && affect_banger_number<128)
{
reset_indexs_confirmation();
index_do_banger_memonpreset=1;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: banger is between 1 and 127 !");}
}
if(mouse_x> x_seq+275 && mouse_x<x_seq+300)//Gridplayer
{
gpl1_affect_step_to_mem=atoi(numeric);
if(gpl1_affect_step_to_mem>=0 && gpl1_affect_step_to_mem<1024)
{
reset_indexs_confirmation();
index_do_affect_step_gridplayer_to_mem=1;
index_mem_to_be_affected_by_gpl=position_preset;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: step is between 1 and 1023, 0 to desaffect !");}
}
if(mouse_x> x_seq+310 && mouse_x<x_seq+470)//TEXT DECRIPTION
{
if(index_type==1)
{
if(mouse_y>y_seq+140 && mouse_y<y_seq+155)
{
for(int tt=0;tt<24;tt++)
{
descriptif_memoires[position_preset][tt]=numeric[tt];
}
descriptif_memoires[position_preset][24]='\0';
}
else
{
for(int tt=0;tt<24;tt++)
{
annotation_memoires[position_preset][tt]=numeric[tt];
}
annotation_memoires[position_preset][24]='\0';
}
someone_changed_in_sequences=1;//icat
reset_numeric_entry();numeric_postext=0;if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
}

}
}
//MANIPULATIONS MEM BEFORE ONE
if(mouse_y>y_seq+80 && mouse_y< y_seq+100)
{
if(mouse_x> x_seq+170 && mouse_x<x_seq+180)//exclude mem from cuelist
{
MemoiresExclues[mem_before_one]=toggle(MemoiresExclues[mem_before_one]);
mouse_released=1;
}

if(mouse_x> x_seq+185  && mouse_x<x_seq+180+35)//LINKS
{
reset_indexs_confirmation();
index_do_link_membefore=1;
index_ask_confirm=1;
mouse_released=1;
}

if(mouse_x> x_seq+225 && mouse_x<x_seq+265)//BANGER
{
affect_banger_number=atol(numeric);
if(affect_banger_number>=0 && affect_banger_number<128)
{
reset_indexs_confirmation();
index_do_banger_membeforeone=1;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: banger is between 1 and 127 !");}
}
if(mouse_x> x_seq+275 && mouse_x<x_seq+300)//Gridplayer
{
gpl1_affect_step_to_mem=atoi(numeric);
if(gpl1_affect_step_to_mem>=0 && gpl1_affect_step_to_mem<1024)
{
reset_indexs_confirmation();
index_do_affect_step_gridplayer_to_mem=1;
index_mem_to_be_affected_by_gpl=mem_before_one;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: step is between 1 and 1023, 0 to desaffect !");}
}
if(mouse_x> x_seq+310 && mouse_x<x_seq+470)//TEXT DECRIPTION
{
if(index_type==1)
{
if(mouse_y>y_seq+80 && mouse_y<y_seq+95)
{
for(int tt=0;tt<24;tt++)
{
descriptif_memoires[mem_before_one][tt]=numeric[tt];
}
descriptif_memoires[mem_before_one][24]='\0';
}
else
{
for(int tt=0;tt<24;tt++)
{
annotation_memoires[mem_before_one][tt]=numeric[tt];
}
annotation_memoires[mem_before_one][24]='\0';
}
reset_numeric_entry();numeric_postext=0;if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
}
}
}


//LES MEMOIRES SUIVANTES USER DEFINED
int index_nbre_mem_visues=0;
//sab 02/03/2014  unused var int last_mem_visue=0;
for(int memsearch=position_preset+1; memsearch<10000;memsearch++)
{
if(memsearch>=9999){memsearch=0;}
if(MemoiresExistantes[memsearch]==1 && index_nbre_mem_visues<nbre_memoires_visualisables_en_preset)
{
index_nbre_mem_visues++;

///ACTIONS
if(mouse_y>y_seq+145+(35*index_nbre_mem_visues)  && mouse_y< y_seq+145+30+(35*index_nbre_mem_visues))
{

if(mouse_x> x_seq+110 && mouse_x<x_seq+170)//MEMS
{
call_stage=0; call_preset=0;
do_call_time_and_rec_f1_f2_f3(memsearch);
mouse_released=1;
}
if(mouse_x> x_seq+170 && mouse_x<x_seq+180)//exclude mem from cuelist
{
MemoiresExclues[memsearch]=toggle(MemoiresExclues[memsearch]);
mouse_released=1;
}

if(mouse_x> x_seq+185  && mouse_x<x_seq+180+35)//LINKS
{
other_mem_in_loop=memsearch;
reset_indexs_confirmation();
index_do_link_memother=1;
index_ask_confirm=1;
mouse_released=1;
}
if(mouse_x> x_seq+225 && mouse_x<x_seq+265)//BANGER
{
affect_banger_number=atol(numeric);
if(affect_banger_number>=0 && affect_banger_number<128)
{
other_mem_in_loop=memsearch;
reset_indexs_confirmation();
index_do_banger_memother=1;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: banger is between 1 and 127 !");}
}
if(mouse_x> x_seq+275 && mouse_x<x_seq+300)//Gridplayer
{
gpl1_affect_step_to_mem=atoi(numeric);
if(gpl1_affect_step_to_mem>=0 && gpl1_affect_step_to_mem<1024)
{
reset_indexs_confirmation();
index_do_affect_step_gridplayer_to_mem=1;
index_mem_to_be_affected_by_gpl=memsearch;
index_ask_confirm=1;
mouse_released=1;
}
else {sprintf(string_Last_Order,">> Wrong entry: step is between 1 and 1023, 0 to desaffect !");}
}
if(mouse_x> x_seq+310 && mouse_x<x_seq+470)//TEXT DECRIPTION
{
if(index_type==1)
{

if(mouse_y> y_seq+140+(35*index_nbre_mem_visues) && mouse_y < y_seq+140+(35*index_nbre_mem_visues)+15)
{
for(int tt=0;tt<24;tt++)
{
descriptif_memoires[memsearch][tt]=numeric[tt];
}
descriptif_memoires[memsearch][24]='\0';
}
else
{
for(int tt=0;tt<24;tt++)
{
annotation_memoires[memsearch][tt]=numeric[tt];
}
annotation_memoires[memsearch][24]='\0';
}
reset_numeric_entry();numeric_postext=0;if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
}
}
}

if(index_nbre_mem_visues>=nbre_memoires_visualisables_en_preset){break;}

}
}

return(0);
}


int do_logical_x1_x2(int x_seq,int y_seq)
{

/////////////////////////////////////CROSSFADE MANUEL/////////////////////////////

if(mouse_y>=y_seq+60 && mouse_y<=y_seq+100+255)//-20 +20
{
///////////////////X///////////////////////////////////////////////////////////
if(mouse_x> x_seq+480 && mouse_x< x_seq+480+45)
{


switch(miditable[0][491])
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
sprintf(string_last_midi_id,"STAGE Fader is Ch: %d Pitch: %d Typ: %s" , miditable[1][491],miditable[2][491],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(491,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
set_mouse_range(x_seq+480, y_seq+60, x_seq+480+45, y_seq+100+255);//pour pas deborder
index_go=0; index_go_back=0; index_pause=0;
niveauX1=(y_seq+80+255)-mouse_y;
if(niveauX1<0){niveauX1=0;}
if(niveauX1>255){niveauX1=255;}
if(midi_send_out[491]==1){index_send_midi_out[491]=1;}
if(index_x1_x2_together==1)
{
if(((255.0-ratio_X1X2_together)/255)==1.0){niveauX2=(255-niveauX1);}
else {niveauX2=remapX2[(255-niveauX1)];}
if(niveauX2<0){niveauX2=0;}
if(niveauX2>255){niveauX2=255;}
if(midi_send_out[492]==1){index_send_midi_out[492]=1;}
}
}
}

////////////////////X2////////////////////////////////////////////////////////////////
else if(mouse_x> x_seq+580 && mouse_x< x_seq+580+45)
{


//midi report
switch(miditable[0][492])
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
sprintf(string_last_midi_id,"Preset Fader is Ch: %d Pitch: %d Typ: %s" , miditable[1][492],miditable[2][492],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(492,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
set_mouse_range(x_seq+580, y_seq+60, x_seq+580+45, y_seq+100+255);//pour pas deborder
index_go=0; index_go_back=0; index_pause=0;
niveauX2=(-1)*(mouse_y-(y_seq+80+255));
if(niveauX2<0){niveauX2=0;}
if(niveauX2>255){niveauX2=255;}
if(midi_send_out[492]==1){index_send_midi_out[492]=1;}
if(index_x1_x2_together==1)
{
if(((255.0-ratio_X1X2_together)/255)==1.0){niveauX1=(255-niveauX2);}
else { niveauX1=255-remapX1[niveauX2];     }
if(niveauX1<0){niveauX1=0;}
if(niveauX1>255){niveauX1=255;}
if (niveauX2==255){niveauX1=0;}//report à zero
if(midi_send_out[491]==1){index_send_midi_out[491]=1;}
}
}
}

if(niveauX1==0 && niveauX2==255)
{
index_go=0; index_go_back=0; index_pause=0;
next_mem_crossfade_finished(position_preset);
index_x1_x2_together=1;
mouse_released=1;
}
}


raccrochage_midi_logical_vertical_dmx ( x_seq+480, (y_seq+80), 491, 45, 255);//X1
raccrochage_midi_logical_vertical_dmx ( x_seq+580, (y_seq+80), 492, 45, 255);//X2 séparés car inversés pour l'affichage etc

//TOGETHER
if(mouse_x> x_seq+540 && mouse_x< x_seq+540+50 && mouse_y>y_seq+50 && mouse_y<y_seq+50+20)
{
if(index_x1_x2_together==0){index_x1_x2_together=1;}
else {index_x1_x2_together=0;}
mouse_released=1;
}
//ratio
if(mouse_x> x_seq+535 && mouse_x< x_seq+575 && mouse_y>y_seq+80 && mouse_y<y_seq+350)
{
ratio_X1X2_together=(int)((mouse_y)-(y_seq+80+255));
float fract_remplaX1=(255.0-ratio_X1X2_together)/255;
float remapis=255.0;
float fract_remplaX2=(255.0-ratio_X1X2_together)/255;
for(int mop=255;mop>=0;mop--)
{
remapis-=fract_remplaX1;
if (remapis>255){remapX1[mop]=255;}
else if(remapis<0){remapX1[mop]=0;}
else
{
remapX1[mop]=(int)(remapis);
}
}
for(int mop=0;mop<256;mop++)
{
remapis+=fract_remplaX2;
if (remapis>255){remapX2[mop]=255;}
else if(remapis<0){remapX2[mop]=0;}
else {remapX2[mop]=(int)(remapis);  }
}
//christoph 15/12/14 debug go déclenché par manip ratio (??? why ???) + enregistrement auto du ratio
index_go=0;
ratio_cross_manuel[position_preset]=ratio_X1X2_together;
}

//GO
if(mouse_x>x_seq+534 && mouse_x<x_seq+574 && mouse_y>y_seq+355 && mouse_y<y_seq+395)
{
//midi report
 switch(miditable[0][495])
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
default:
break;
}
sprintf(string_last_midi_id,"GO is Ch: %d Pitch: %d Typ: %s" , miditable[1][495],miditable[2][495],thetypinfo);
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(495,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
do_go_function();
if(index_go==1 && index_pause==0)
{
do_send_bang();
}
mouse_released=1;
}
}


//////////////go back

if(mouse_x>x_seq+490+14-20 && mouse_x<x_seq+490+14+20 && mouse_y>y_seq+80+255+40-20 && mouse_y<y_seq+80+255+40+20)
{

//midi report
switch(miditable[0][494])
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
  sprintf(string_last_midi_id,"GO BACK is Ch: %d Pitch: %d Typ: %s" , miditable[1][494],miditable[2][494],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(494,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else
{
do_go_back_function();
int banger_back_is=Banger_Memoire[position_preset]-1;
do_go_back_bang(banger_back_is);
mouse_released=1;
}
}


//////////////double go

if(mouse_x>x_seq+590+14-20 && mouse_x<x_seq+590+14+20 && mouse_y>y_seq+80+255+40-20 && mouse_y<y_seq+80+255+40+20)
{


//midi report
switch(miditable[0][496])
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
  sprintf(string_last_midi_id,"GO BACK is Ch: %d Pitch: %d Typ: %s" , miditable[1][496],miditable[2][496],thetypinfo);
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(496,Midi_Faders_Affectation_Mode);
mouse_released=1;
}

else
{
do_double_go_function();
if(index_go==1 && index_pause==0)
{
do_send_bang();
}
mouse_released=1;
}
}

/////////////////////ACCELEROMETRE

if(mouse_x>=x_seq+490 && mouse_x<=x_seq+490+127 && mouse_y>y_seq+405 && mouse_y<y_seq+405+(45/2))
{



switch(miditable[0][493])
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
sprintf(string_last_midi_id,"SpeedFader is Ch: %d Pitch: %d Typ: %s" , miditable[1][493],miditable[2][493],thetypinfo);

if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(493,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
set_mouse_range(x_seq+490, y_seq+405, x_seq+490+127, y_seq+405+(45/2));//pour pas deborder
crossfade_speed=mouse_x-(x_seq+490);
if(crossfade_speed<0){crossfade_speed=0;}
if(crossfade_speed>127){crossfade_speed=127;}
//integration gridplayer 1
if(index_link_speed_crossfade_to_gpl1==1)
{
grid_crossfade_speed[0]=crossfade_speed;
midi_levels[1508]=crossfade_speed;
gridder_prepare_cross(0,index_grider_selected[0],index_grider_step_is[0]);
}

if(midi_send_out[493]==1){index_send_midi_out[493]=1;}
prepare_crossfade();
//ventilation_temps_vers_char();//icat
someone_changed_in_time_sequences=1;//icat
}
}

//midi out des x1 et x2

if(mouse_x> x_seq+655-10 && mouse_x<  x_seq+655+10 && mouse_y>y_seq+340-10 && mouse_y<y_seq+340+10)
{

  if(midi_send_out[491]==0){midi_send_out[491]=1; }
  else if(midi_send_out[491]==1){midi_send_out[491]=0; }
  //report pour x2 et speed crossfade
  midi_send_out[492]=midi_send_out[491];
  mouse_released=1;
}


//MIDI OUT DU SPEED

if(mouse_x> x_seq+655-10 && mouse_x<  x_seq+655+10 && mouse_y>y_seq+340-10+85 && mouse_y<y_seq+340+10+85)
{
  if(midi_send_out[493]==0){midi_send_out[493]=1; }
  else if(midi_send_out[493]==1){midi_send_out[493]=0; }
  mouse_released=1;
}

raccrochage_midi_logical_horizontal ( x_seq+490, y_seq+405, 493,127,13);

//auto reset on link
if(mouse_x> x_seq+548 && mouse_x<  x_seq+548+15 && mouse_y>y_seq+435 && mouse_y<y_seq+435+15)
{
if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(1591,Midi_Faders_Affectation_Mode);
}
else
{
auto_reset_crossfade_speed_on_link=toggle(auto_reset_crossfade_speed_on_link);
}
mouse_released=1;
}
return(0);
}



int do_logical_Sequenciel_Window(int xseq, int yseq,int largeur_seq,int hauteur_seq)
{

do_logical_refresh_vision_memories(xseq,yseq);
do_logical_x1_x2(xseq,yseq-25);

////////////////////MENUS///////////////////////////////////////////////////////
//options hautes

///alink
if(mouse_x>xseq+180 && mouse_x<xseq+180+35 && mouse_y>yseq+50 && mouse_y<yseq+50+15)
{
if(index_link_is_on==0){index_link_is_on=1;}
else if(index_link_is_on==1){index_link_is_on=0;}
mouse_released=1;
}

///banger
if(mouse_x>xseq+223 && mouse_x<xseq+263 && mouse_y>yseq+50 && mouse_y<yseq+50+15)
{
index_banger_is_on=toggle(index_banger_is_on);
mouse_released=1;
}

//grid player 1 embeded
if(mouse_x>xseq+275 && mouse_x<xseq+275+30 && mouse_y>yseq+50 && mouse_y<yseq+50+15 )
{
show_gridplayer_in_seq=toggle(show_gridplayer_in_seq);
mouse_released=1;
}



/////menus bas
int rangee_y= yseq+180+(35*(nbre_memoires_visualisables_en_preset+1));
int index_atoi=0;
for (int op=0;op<7;op++)
{
///actions mouse
if(mouse_x>xseq+20+(op*60) && mouse_x<xseq+20+(op*60)+50 && mouse_y>rangee_y && mouse_y<rangee_y+20)
{
switch(op)
{
case 0:         //create
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(768,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
reset_indexs_confirmation();
index_do_create_mem=1;
index_ask_confirm=1;
}
break;
case 1://delete mem
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(769,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
reset_indexs_confirmation();
index_do_delete_mem=1;
index_ask_confirm=1;
}
break;
case 2://stage minus
if(  Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(770,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
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
}
break;
case 3://stage +
if(  Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(771,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{

 if(index_go==0 && index_go_back==0 && index_pause==0)
           {
           position_onstage=position_preset;
           }
            else {index_go=0;index_pause=0; index_go_back=0;}

refresh_mem_onstage(position_onstage);
detect_mem_before_one();
detect_mem_preset();
refresh_mem_onpreset(position_preset);
niveauX1=255; niveauX2=0;
refresh_banger_wx();
refresh_integrated_gridplayer1();
}
break;
case 4://preset -
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(772,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
index_go=0;index_pause=0; index_go_back=0;
detect_mem_preset_previous();
refresh_mem_onpreset(position_preset);
niveauX2=0;
}
break;
case 5://preset +
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(773,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
index_go=0;index_pause=0; index_go_back=0;
detect_next_preset();
refresh_mem_onpreset(position_preset);
niveauX2=0;
}
break;
case 6://goto
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1645,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
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
break;

default:
break;
}//fin des switch
mouse_released=1;
}
}

//grid player 1 embarqué
if(show_gridplayer_in_seq==1)
{

//UP DOWN griders number selected

if(mouse_x>xseq+880-12 && mouse_x<xseq+880+12 && mouse_y>yseq+40-12 && mouse_y<yseq+40+12)
{

if(mouse_released==0)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1476,Midi_Faders_Affectation_Mode);
}
else
{
if(index_grider_selected[0]>0)
{index_grider_selected[0]--;}
}
 mouse_released=1;
}
}


if( mouse_x>xseq+910-12 && mouse_x<xseq+910+12 && mouse_y>yseq+40-12 && mouse_y<yseq+40+12)
{

if( mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1480,Midi_Faders_Affectation_Mode);
}
else
{
if(index_grider_selected[0]<127){index_grider_selected[0]++;}
}
mouse_released=1;
}
}

do_logical_TheStepBox(xseq+660,yseq+90,0);
do_logical_ThePlayCommands(xseq+760,yseq+90,0);
do_logical_TheGrid_commands(xseq+660,yseq+130,0);//pos x, posy y, num player

if(mouse_x>xseq+690 && mouse_x<xseq+690+105 && mouse_y>yseq+295 && mouse_y<yseq+295+15 && mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1540,Midi_Faders_Affectation_Mode);
}

else
{
index_link_speed_crossfade_to_gpl1=toggle(index_link_speed_crossfade_to_gpl1);
if(index_link_speed_crossfade_to_gpl1==1)
{  grid_crossfade_speed[0]=crossfade_speed;
   midi_levels[1508]=crossfade_speed;
}
}
mouse_released=1;
}
}


return(0);
}
