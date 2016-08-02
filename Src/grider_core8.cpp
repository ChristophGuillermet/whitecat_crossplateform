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

* \file grider_core8.cpp
* \brief {Core fonctions for grid players}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions core pour gérer les grid players
*
*   Core fonctions to manage the gridplayers
*
 **/

int do_logical_TheStepBox(int xb,int yb, int num_grid_player)
{

//STEP IS

//Step minus
//sab 02/03/2014 IMPACT ? if(mouse_x>xb & mouse_x<xb+20 && mouse_y>yb && mouse_y<yb+20 )
if(mouse_x>xb && mouse_x<xb+20 && mouse_y>yb && mouse_y<yb+20 )
{
if( mouse_released==0)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1484+num_grid_player,Midi_Faders_Affectation_Mode);
}
else
{
  gridplayer_step_minus(num_grid_player);
 }
  mouse_released=1;
}
}
 //Step plus
//sab 02/03/2014 IMPACT if(mouse_x>xb+60 & mouse_x<xb+60+20 && mouse_y>yb && mouse_y<yb+20 )
if(mouse_x>xb+60 && mouse_x<xb+60+20 && mouse_y>yb && mouse_y<yb+20 )
{
if( mouse_released==0)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1488+num_grid_player,Midi_Faders_Affectation_Mode);
}
else
{
  gridplayer_step_plus(num_grid_player);
}
  mouse_released=1;
 }
}

//set +127 box pour les pas
if(mouse_x>xb+60 && mouse_x<xb+60+20 && mouse_y>yb-6 && mouse_y<yb-6+5)
{
if( mouse_released==0)
 {
 if( Midi_Faders_Affectation_Type!=0)//config midi
 {
 attribute_midi_solo_affectation(1536+num_grid_player,Midi_Faders_Affectation_Mode);
 }
 mouse_released=1;
}
}
//chargement d'un pas, ou affectation d'un temps ou clear  du pas
//sab 02/03/2014 IMPACT ? if(mouse_x>xb+22 & mouse_x<xb+22+35 && mouse_y>yb-5 && mouse_y<yb-5+30 )
if(mouse_x>xb+22 && mouse_x<xb+22+35 && mouse_y>yb-5 && mouse_y<yb-5+30 )
 {
if( mouse_released==0)
 {
 if( Midi_Faders_Affectation_Type!=0)//config midi
 {
 attribute_midi_solo_affectation(1532+num_grid_player,Midi_Faders_Affectation_Mode);
 }
 else
 {
 if(numeric_postext>0 && index_affect_time==0 && index_main_clear==0 && index_do_dock==0 )
                      {
                      int step_to_affect_to_grid=0;
                      step_to_affect_to_grid=atoi(numeric);
                      if(step_to_affect_to_grid>0 && step_to_affect_to_grid<1024)
                      {
                       index_grider_step_is[num_grid_player]=step_to_affect_to_grid-1;
                       if(grider_seekto_mode[num_grid_player]==1 && grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]>0 )//seek position
                       {index_grider_seek_pos[num_grid_player]=grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]];}
                      }
                      reset_numeric_entry();
                      }
 else if (numeric_postext>0  && index_do_dock==1 && index_enable_edit_Grider==1)//charge mem
 {
  int offset=grider_begin_channel_is-1;
  int mem_to_affect_to_grid=0;
  mem_to_affect_to_grid=int(atof(numeric)*10);

  if(MemoiresExistantes[mem_to_affect_to_grid]==1)
  {
   for(int i=offset;i<513;i++)////A REVOIR COMME SUR EN DESSOUS
   {
   if(i+1<513)
   {
   grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][i-offset-1]=Memoires[mem_to_affect_to_grid][i];
   }
   }
   reset_numeric_entry();
   index_do_dock=0;
  }
 }
 else if (index_do_dock==1 && numeric_postext==0 && index_enable_edit_Grider==1)//charge circuits
 {
 int ofset=grider_begin_channel_is-1;
 if(index_affect_time==0)
 {
 switch(index_blind)
 {
 case 0:
  for(int i=ofset;i<513;i++)//OK FEVRIER 2015
 {
  grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][i-1-ofset]=bufferSaisie[i];
  bufferSaisie[i]=0;
 }
 break;
  case 1:
  for(int i=1;i<513;i++)
 {
  grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][i-1-ofset]=bufferBlind[i];
  bufferBlind[i]=0;
 }
 break;
 default: break;
 }
 }
  else if(index_affect_time==1 )
 {
 switch(to_step_editing_mode[num_grid_player])
 {
 case 0:
                      for(int ty=0;ty<4;ty++)
                      {
                      if(index_type_of_time_to_affect[ty]==1)
                      {
                      grid_times[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][ty]=
                      (time_minutes*60)+time_secondes+(0.01*time_centiemes);
                      }
                      }
                      gridder_prepare_cross(num_grid_player, index_grider_selected[num_grid_player], index_grider_step_is[num_grid_player]);
 break;
 case 1://step to step mode
 if(index_grider_step_is[index_grider_selected[num_grid_player]]<index_StepTo[num_grid_player])
 {
 for(int st=index_grider_step_is[num_grid_player];st<=index_StepTo[num_grid_player];st++)
 {
                       for(int ty=0;ty<4;ty++)
                      {
                      if(index_type_of_time_to_affect[ty]==1)
                      {
                      grid_times[index_grider_selected[num_grid_player]][st][ty]=
                      (time_minutes*60)+time_secondes+(0.01*time_centiemes);
                      }
                      }
 }
 }
 break;
 default: break;
 }
 index_affect_time=0;
 }

 index_do_dock=0;
 }
 else if(index_do_modify==1 && index_enable_edit_Grider==1)
 {
 switch(index_blind)
 {
 case 0:
  for(int i=1;i<513;i++)
 {
  if(Selected_Channel[i]==1)
  {
  grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][i-1]=bufferSaisie[i];
  bufferSaisie[i]=0;
 }
 }
 break;
  case 1:
  for(int i=1;i<513;i++)
 {
 if(Selected_Channel[i]==1)
 {
  grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][i-1]=bufferBlind[i];
  bufferBlind[i]=0;
 }
 }
 break;
 default: break;
 }
 index_do_modify=0;
 }

 else if(index_do_report==1 && index_enable_edit_Grider==1)
 {

 for (int u=1;u<513;u++)
 {
 if(bufferSequenciel[u] >= bufferFaders[u])
 {
  grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][u-1]
 =  bufferSequenciel[u];
 }
 if(bufferFaders[u]>bufferSequenciel[u])
 {
grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][u-1]=bufferFaders[u];
 }
 Selected_Channel[u]=0;
 }

 index_do_report=0;
 }

 else if(index_main_clear==1 && index_affect_time==0 && index_enable_edit_Grider==1 )
 {
 grid_to_clear=index_grider_selected[num_grid_player];

  switch(to_step_editing_mode[num_grid_player])
 {
 case 0:
 step_grid_to_clear=index_grider_step_is[num_grid_player];
 index_ask_confirm=1;
 index_clear_a_grid_step=1;
 break;
 case 1:
 index_ask_confirm=1;
 step_grid_to_clear=index_grider_step_is[num_grid_player];
 index_clear_a_grid_serie_step=1;
 index_for_grid_stepto=index_StepTo[num_grid_player];
 break;
 default: break;
 }
 }
 }
 mouse_released=1;
 }

}

 return(0);
}



int do_logical_TheGrid_commands ( int xb, int yb, int num_grid_player)
{

//accélérometer du player
if(mouse_x>xb-5 && mouse_x<xb+127+5 && mouse_y>=yb+30 && mouse_y<=yb+30+10 )
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1508+num_grid_player,Midi_Faders_Affectation_Mode);
}
else
{
 if(grid_player_slave[num_grid_player]==0)
 {
  set_mouse_range(xb-5,yb+30,xb+127+5,yb+30+10);
  grid_crossfade_speed[num_grid_player]=mouse_x-xb;
  if(grid_crossfade_speed[num_grid_player]<0){grid_crossfade_speed[num_grid_player]=0;}
  else  if(grid_crossfade_speed[num_grid_player]>127){grid_crossfade_speed[num_grid_player]=127;}
  //integration gridplayer 1 au sequenciel
  if(index_link_speed_crossfade_to_gpl1==1 && num_grid_player==0)
  {
   grid_crossfade_speed[0]=crossfade_speed;
   midi_levels[1508]=crossfade_speed;
  }
  gridder_prepare_cross(num_grid_player,index_grider_selected[num_grid_player],index_grider_step_is[num_grid_player]);
 }
}
}

////////////////SLAVE MODE////////////////////////////////////////////////////
if(mouse_x>xb+150 && mouse_x<xb+150+40 && mouse_y>yb+25 && mouse_y<yb+25+15)
{
if(mouse_released==0)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1504+num_grid_player,Midi_Faders_Affectation_Mode);
}
else
{
grid_player_slave[num_grid_player]=toggle(grid_player_slave[num_grid_player]);
}
mouse_released=1;
}
}




for(int sp=0;sp<4;sp++)
{
if( mouse_x>xb && mouse_x<xb+10 && mouse_y>yb+70+(sp*20) && mouse_y<yb+70+(sp*20)+10 )
{
if( mouse_released==0 )
{
 if( Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1512+(sp*4)+num_grid_player,Midi_Faders_Affectation_Mode);
 }
 else
 {
 switch(sp)
 {
 case 0:
 grider_goto_mode[num_grid_player]=toggle(grider_goto_mode[num_grid_player]);
 break;
 case 1:
 grider_count_mode[num_grid_player]=toggle(grider_count_mode[num_grid_player]);
 break;
 case 2:
 grider_seekto_mode[num_grid_player]=toggle(grider_seekto_mode[num_grid_player]);
 break;
 case 3:
 grider_stoplay_mode[num_grid_player]=toggle(grider_stoplay_mode[num_grid_player]);
 break;
 default:
 break;
 }
 }
 mouse_released=1;
}
}
}//fin boucle4

//Goto Grid num
if( index_enable_edit_Grider==1  && mouse_x>xb+105 && mouse_x<xb+105+30 && mouse_y>yb+70 && mouse_y<yb+70+15 )
{
 if(  mouse_released==0 )
 {
 grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][0]=atoi(numeric)-1;
 if(grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][0]<0)
 {grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][0]=-1;}//désaffectation
 if(grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][0]>127)
 {grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][0]=127;}
 reset_numeric_entry();
 mouse_released=1;
 }
}
//Goto step num
if(index_enable_edit_Grider==1  &&  mouse_x>xb+150 && mouse_x<xb+150+40 && mouse_y>yb+70 && mouse_y<yb+70+15 )
{
if( mouse_released==0)
 {
  grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][1]=atoi(numeric)-1;
 if(grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][1]<0)
 {grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][1]=-1;}//désaffectation
 if(grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][1]>1023)
 {grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][1]=1023;}
 reset_numeric_entry();
 mouse_released=1;
 }
}

//count num
if( index_enable_edit_Grider==1  && mouse_x>xb+150 && mouse_x<xb+150+40 && mouse_y>yb+90 && mouse_y<yb+90+15  )
{
if( mouse_released==0)
 {
 grid_count[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]=atoi(numeric);
 if(grid_count[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]<0)
 {
 grid_count[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]=0;
 }
 reset_numeric_entry();
 mouse_released=1;
 }
}


//Seek step num
if( index_enable_edit_Grider==1  && mouse_x>xb+150 && mouse_x<xb+150+40 && mouse_y>yb+110 && mouse_y<yb+110+15  )
{
if( mouse_released==0)
 {
  grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]=atoi(numeric)-1;
 if(grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]<0)
 {grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]=-1;}//désaffectation
 if(grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]>1023)
 {grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]=1023;}
 reset_numeric_entry();
 mouse_released=1;
 }
}

//Stoplay button
if( index_enable_edit_Grider==1  && mouse_x>xb+100 && mouse_x<xb+100+90 && mouse_y>yb+130 && mouse_y<yb+130+15 && mouse_b&1 && mouse_released==0)
{
 grid_stoplay[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]=toggle(grid_stoplay[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]);
 mouse_released=1;
}
return(0);
}






int do_logical_TheGrid_matrix ( int xb, int yb,int sizecase, int num_grid_player)
{
int grid_selected=index_grider_selected[num_grid_player];
int gr_st_selected=index_grider_step_is[num_grid_player];

if(index_enable_edit_Grider==1 && mouse_x>=xb && mouse_x<=xb+(grider_nb_col*sizecase) && mouse_y>=yb && mouse_y<=yb+(grider_nb_row*sizecase))
{
if( mouse_released==0)
{
if(numeric_postext==0)
{
if(grid_levels[index_grider_selected[num_grid_player]][gr_st_selected][position_grid_editing]==0)
{grid_levels[grid_selected][gr_st_selected][position_grid_editing]=255;}
else if(grid_levels[grid_selected][gr_st_selected][position_grid_editing]==255
|| grid_levels[index_grider_selected[num_grid_player]][gr_st_selected][position_grid_editing]>0 )
{grid_levels[grid_selected][gr_st_selected][position_grid_editing]=0;}
}
else if(numeric_postext>0)
{
int lev_to_attr_to_grid=0;
lev_to_attr_to_grid=atoi(numeric);
switch(dmx_view)
{
case 0://pourcent
if(lev_to_attr_to_grid>0)
{
grid_levels[grid_selected][gr_st_selected][position_grid_editing]=
(int)(((float)(lev_to_attr_to_grid) *2.55) +1);// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
}
else {grid_levels[grid_selected][gr_st_selected][position_grid_editing]=0;}
break;
case 1://dmx
if(lev_to_attr_to_grid>=0 && lev_to_attr_to_grid<=255)
{
grid_levels[grid_selected][gr_st_selected][position_grid_editing]=lev_to_attr_to_grid;
}
break;
default: break;
}

}
reset_numeric_entry();
mouse_released=1;
}
}

return(0);
}


int do_logical_TheGrid_divers( int xb, int yb, int num_grid_player)
{
//affect to dock
 if(mouse_x>xb+60 && mouse_x<xb+60+50 && mouse_y>yb && mouse_y<yb+30 &&  mouse_released==0)
 {

  index_do_dock=index_affect_color_to_dock;
  if(num_grid_player==gridplayer_to_affect_is)
  {
  reset_index_actions();
  index_do_dock=0;
  }
  else  {
        reset_index_actions();
        reset_indexs_confirmation();
        gridplayer_to_affect_is=num_grid_player;
        index_do_dock=1;
        }


  mouse_released=1;
 }

 if(  index_enable_edit_Grider==1 && mouse_x>xb && mouse_x<xb+10 && mouse_y>yb+45 && mouse_y<yb+45+10 && mouse_released==0)
 {
 to_step_editing_mode[num_grid_player]=toggle(to_step_editing_mode[num_grid_player]);
 mouse_released=1;
 }

 if( index_enable_edit_Grider==1 && mouse_x>xb+60 && mouse_x<xb+60+40 && mouse_y>yb+45 && mouse_y<yb+45+15 && mouse_released==0  )
 {
 int tempstepto=atoi(numeric)-1;
 if(tempstepto>index_grider_step_is[num_grid_player] && tempstepto<1023)
 {index_StepTo[num_grid_player]=tempstepto;}
 reset_numeric_entry();
 mouse_released=1;
 }

 ///////////COPY TO ////////////////////////////////////////////////////////////



 //copy mode
 if(  index_enable_edit_Grider==1 && mouse_x>xb && mouse_x<xb+50 && mouse_y>yb+75 && mouse_y<yb+75+15 && mouse_released==0)
 {
  index_for_copy_grid=1;
  index_grid_tostep_or_not=to_step_editing_mode[num_grid_player];
  from_gridstep_to=index_StepTo[num_grid_player];
  destination_grid_for_copy= index_Grid_copyto[num_grid_player][0];
  destination_step_for_copy= index_Grid_copyto[num_grid_player][1];
  grid_to_clear=index_grider_selected[num_grid_player];       //utilisé pour menus confirm
  step_grid_to_clear=index_grider_step_is[num_grid_player]; //utilisé pour les menus confirm
  index_ask_confirm=1;
  mouse_released=1;
 }

  //insert mode
 if( index_enable_edit_Grider==1 &&  mouse_x>xb+55 && mouse_x<xb+55+50 && mouse_y>yb+75 && mouse_y<yb+75+15 )
 {
  index_for_insert_grid=1;
  destination_step_for_copy= index_Grid_copyto[num_grid_player][1];//le nombre de steps à insérer après la position actuelle
  grid_to_clear=index_grider_selected[num_grid_player];       //utilisé pour menus confirm
  step_grid_to_clear=index_grider_step_is[num_grid_player]; //utilisé pour les menus confirm
  index_ask_confirm=1;
  mouse_released=1;
 }
 //grid   entry
 if(index_enable_edit_Grider==1 && mouse_x>xb && mouse_x<xb+30 && mouse_y>yb+95 && mouse_y<yb+95+15 && mouse_released==0)
 {
 int tempstepto=atoi(numeric)-1;
 if(tempstepto>=0 && tempstepto<127)
 {index_Grid_copyto[num_grid_player][0]=tempstepto;}
  reset_numeric_entry();
  mouse_released=1;
 }
 //step entry
 if(index_enable_edit_Grider==1 && mouse_x>xb+45 && mouse_x<xb+45+40 && mouse_y>yb+95 && mouse_y<yb+95+15 && mouse_released==0 )
 {
  int tempstepto=atoi(numeric)-1;
 if(tempstepto>=0 && tempstepto<1023)
 {index_Grid_copyto[num_grid_player][1]=tempstepto;}
  reset_numeric_entry();
  mouse_released=1;
  }

  //snap fader
 if( index_enable_edit_Grider==1  &&  mouse_x>xb && mouse_x<xb+105 && mouse_y>yb+135 && mouse_y<yb+135+15 && mouse_released==0)
 {
 if(index_do_dock==1 && numeric_postext>0)
 {
 int getfad=atoi(numeric)-1;
 if(getfad>=0 && getfad<48)
 {GplSnapFader[num_grid_player]=getfad;}
 reset_numeric_entry();
  mouse_released=1;
  index_do_dock=0;
  }
  else//enregistrement
  {
  for(int i=0;i<513;i++)
   {
   if(i+grider_begin_channel_is+1<513)
   {
   grid_levels[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][i]=FaderDoDmx[(GplSnapFader[num_grid_player])][i+grider_begin_channel_is];
   }
   }
   mouse_released=1;
  }
 }



if(num_grid_player==0 )//asservissement speed au séquenciel
{
if(mouse_x>xb && mouse_x<xb+105 && mouse_y>yb+115 && mouse_y<yb+115+15 && mouse_released==0)
{
if(Midi_Faders_Affectation_Type!=0)
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

int do_logical_ThePlayCommands(int xb, int yb, int num_grider)
{
//ligne des commandes
if(mouse_y>yb && mouse_y<yb+20 )
{
 if(mouse_x>xb+10 && mouse_x<xb+10+20 )// PLAY GRID
 {
 if(mouse_released==0)
 {
 if(Midi_Faders_Affectation_Type!=0)//config midi
 {
 attribute_midi_solo_affectation(1492+num_grider,Midi_Faders_Affectation_Mode);
 }
 else
 {
 grider_is_playing[num_grider]=toggle(grider_is_playing[num_grider]);
 if(grider_is_playing[num_grider]==1){grid_crossfade_start_time[num_grider]=actual_time;}
 }
 mouse_released=1;
 }
 }
 else if(mouse_x>xb+40 && mouse_x<xb+40+20 )//SEEK GRID
 {
 if(mouse_released==0)
 {
 if( Midi_Faders_Affectation_Type!=0)//config midi
 {
 attribute_midi_solo_affectation(1496+num_grider,Midi_Faders_Affectation_Mode);
 }
 else
 {
 gridplayer_seek(num_grider);
 }
  mouse_released=1;
 }
}


else if(mouse_x>xb+70 && mouse_x<xb+70+20 )//AUTO STOP PLAY GRID
 {
 if(mouse_released==0)
 {
 if(Midi_Faders_Affectation_Type!=0)//config midi
 {
 attribute_midi_solo_affectation(1500+num_grider,Midi_Faders_Affectation_Mode);
 }
 else
 {
 grider_autostopmode[num_grider]=toggle(grider_autostopmode[num_grider]);
 }
 mouse_released=1;
 }
 }
}//fin check y
return(0);
}

int do_logical_TheCallGridBox(int xb, int yb, int num_grider)
{

if(mouse_x>xb+10 && mouse_x<xb+10+50 && mouse_y>yb && mouse_y<yb+20)
{
if(mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1528+num_grider,Midi_Faders_Affectation_Mode);
}
else
{
if(numeric_postext>0)
{
int temp_num_grid=atoi(numeric);
if(temp_num_grid>0 && temp_num_grid<128)
{
//rajout
bool was_playing=grider_is_playing[num_grider];
grider_is_playing[num_grider]=0;
grid_niveauX1[num_grider]=255;
grid_niveauX2[num_grider]=0;
grid_floatX1[num_grider]=255.0;
grid_floatX2[num_grider]=0.0;
grid_fraction_X2_in[num_grider]=0.0;
grid_fraction_X1_out[num_grider]=0.0;

index_grider_selected[num_grider]=temp_num_grid-1;//avant modif du 5 nov que cette ligne la

//rajout
index_grider_step_is[num_grider]=0;
//chargement à la volée rafraichissement grid
gridder_prepare_cross(num_grider, index_grider_selected[num_grider], index_grider_step_is[num_grider]);


if(grider_seekto_mode[num_grider]==1 && grid_seekpos[index_grider_selected[num_grider]][index_grider_step_is[num_grider]]>0)//seek position original fonction
  {index_grider_seek_pos[num_grider]=grid_seekpos[index_grider_selected[num_grider]][index_grider_step_is[num_grider]];}

//rajout
if(was_playing==1){grider_is_playing[num_grider]=1;}

reset_numeric_entry();
}
}
else if(index_main_clear==1)
{
 grid_to_clear=index_grider_selected[num_grider];
 step_grid_to_clear=index_grider_step_is[index_grider_selected[num_grider]];
 index_ask_confirm=1;
 index_clear_a_grid=1;
}
}
mouse_released=1;
}
}

if(mouse_x>xb+70 && mouse_x<xb+70+170 && mouse_y>yb && mouse_y<yb+20 && index_type==1 && mouse_released==0)
{
 for(int tt=0;tt<24;tt++)
 {
 grider_name[index_grider_selected[num_grider]][tt]=numeric[tt];
 }
 grider_name[index_grider_selected[num_grider]][24]='\0';
 reset_numeric_entry();numeric_postext=0; if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
}

//UP DOWN griders number selected

if(mouse_x>xb+265-12 && mouse_x<xb+265+12 && mouse_y>yb+10-12 && mouse_y<yb+10+12)
{

if(mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1476+num_grider,Midi_Faders_Affectation_Mode);
}
else
{
if(index_grider_selected[num_grider]>0)
{index_grider_selected[num_grider]--;}
}
 mouse_released=1;
}
}


if( mouse_x>xb+295-12 && mouse_x<xb+295+12 && mouse_y>yb+10-12 && mouse_y<yb+10+12)
{

if( mouse_released==0)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1480+num_grider,Midi_Faders_Affectation_Mode);
}
else
{
if(index_grider_selected[num_grider]<127){index_grider_selected[num_grider]++;}
}
mouse_released=1;
}
}
return(0);
}


int do_logical_Grid_player(int xb, int yb, int num_grider)
{

do_logical_TheCallGridBox(xb,yb,num_grider);

do_logical_TheStepBox(xb+315,yb, num_grider);
do_logical_ThePlayCommands(xb+400,yb,num_grider);




do_logical_TheGrid_commands(xb+20,yb+35,num_grider);//pos x, posy y, num player
do_logical_TheGrid_divers(xb+20+200,yb+30,num_grider);//pos x, posy y, num player
do_logical_TheGrid_matrix(xb+20+320,yb+35,size_grille,num_grider);//pos x pos y taille de case num player

return(0);
}





int do_logical_GlobalGridViewer(int xb, int yb, int taillecase)
{
//appel de grille

if(mouse_x>xb+40 && mouse_x<xb+40+50 && mouse_y>yb+10 && mouse_y<yb+10+20  )
{
if(mouse_released==0)
{
if(numeric_postext>0)
{
int temp_num_grid=atoi(numeric);
if(temp_num_grid>0 && temp_num_grid<128)
{
grid_selected_for_view  =temp_num_grid-1;
reset_numeric_entry();
}
}
}
mouse_released=1;
}


if(mouse_x>xb+150 && mouse_x<xb+150+50 && mouse_y>yb+10 && mouse_y<yb+10+20 )
{
if( mouse_released==0)
{
if(numeric_postext>0)
{
int temp_num_grid=atoi(numeric);
if(temp_num_grid>0 && temp_num_grid<1024)
{
grid_step_view =temp_num_grid-1;
reset_numeric_entry();
}
}
mouse_released=1;
}
}

//déplacement dans les pas

if(mouse_x>xb+220 && mouse_x<xb+220+20 && mouse_y>yb+10 && mouse_y<yb+10+20)
{
if( mouse_released==0)
{
grid_step_view--;
if(grid_step_view<0){grid_step_view=0;}
mouse_released=1;
}
}
if(mouse_x>xb+250 && mouse_x<xb+250+20 && mouse_y>yb+10 && mouse_y<yb+10+20)
{
if( mouse_released==0)
{
grid_step_view++;
if(grid_step_view>1022){grid_step_view=1022;}
mouse_released=1;
}
}

return(0);
}





int do_logical_Grider_Box(int xb, int yb)
{

/////////////nbre Gridplayers affichage///////////////////////////

for(int o=0;o<core_user_define_nb_gridplayers;o++)
{
if( mouse_x>xb+540+(o*15) && mouse_x<xb+540+(o*15)+10 && mouse_y>yb+20 && mouse_y<yb+20+10)
{
if( mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1472+o,Midi_Faders_Affectation_Mode);
}
else
{
index_show_grid_player[o]=toggle(index_show_grid_player[o]);
refresh_hauteur_fenetre_grider();
}
mouse_released=1;
}
}
}
//paramètres de grid
if( mouse_y>yb+15 && mouse_y<yb+15+20 )
{
//////def chan begin
if(mouse_x>xb+245 && mouse_x<xb+245+40 &&  index_enable_edit_Grider==1)//chan edit
{
if(mouse_released==0 )
{
int temp_begchan=atoi(numeric);
if(temp_begchan>0 && temp_begchan<512)
{
grider_begin_channel_is=temp_begchan;
}
reset_numeric_entry();
mouse_released=1;
}
}
if(mouse_x>xb+315 && mouse_x<xb+315+40 &&  index_enable_edit_Grider==1 )//col edit
{
if(mouse_released==0)
{
int temp_col=atoi(numeric);
if(temp_col>0 && temp_col<=24)
{
grider_nb_col=temp_col;
}
reset_numeric_entry();
mouse_released=1;
}
}
if(mouse_x>xb+385 && mouse_x<xb+385+40 &&  index_enable_edit_Grider==1)//rows edit
{

if(mouse_released==0 )
{
int temp_row=atoi(numeric);
if(temp_row>0 && temp_row<=24)
{
grider_nb_row=temp_row;
refresh_hauteur_fenetre_grider();
}
reset_numeric_entry();
mouse_released=1;
}
}
if(mouse_x>xb+430 && mouse_x<xb+430+50)//edit mode
{
if(mouse_released==0 )
{
index_enable_edit_Grider=toggle(index_enable_edit_Grider);
if(index_enable_edit_Grider==0)
{
for(int i=0;i<4;i++)
{
to_step_editing_mode[i]=0;
}
}
mouse_released=1;
}

}
}

//Global grid viewer

////Affichage viewer
switch(show_global_view_grider)
{
case 0:
hauteurGlobalGridviewer=0;
break;
case 1:
hauteurGlobalGridviewer=100+(grider_nb_row*size_preview_case);
do_logical_GlobalGridViewer(xb,yb+40,size_preview_case);  //x y taille de previsu de la grille
break;
default: break;
}

if(mouse_x>xb+495 && mouse_x<xb+495+40 && mouse_y>yb+20 && mouse_y<yb+20+10)
{
show_global_view_grider=toggle(show_global_view_grider);
refresh_hauteur_fenetre_grider();
mouse_released=1;
}


//AFFICHAGE DES GRID PLAYERS

int numerodeplayer_affiche=0;
for(int yo=0;yo<core_user_define_nb_gridplayers;yo++)
{
if(index_show_grid_player[yo]==1)
{
do_logical_Grid_player(xb, yb+50+hauteurGlobalGridviewer+(numerodeplayer_affiche*(60+(grider_facteur_hauteur*size_grille))), yo);
numerodeplayer_affiche++;
}
}

return(0);
}
