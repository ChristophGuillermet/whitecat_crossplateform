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

* \file grider_calculs8.cpp
* \brief {calcul fonctions for grid players}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions de calcul pour gérer les grid players
*
*   Calcul fonctions to manage the gridplayers
*
 **/

int affichage_time_format(float time_to_convert)
{
int time_inminutes=(int)(time_to_convert/60)%60;
//int time_insecondes=(int)(time_to_convert)%60;
//int time_indixiemes=(int)(time_to_convert*10)%10;
float fin_du_temps_secondes=time_to_convert-(time_inminutes*60);

sprintf(string_conversion_timeis,"%d..%.2f",time_inminutes,fin_du_temps_secondes);

return(0);
}

int refresh_step_in_player(int grid_number, int num_step, int grider_player)
{
//rafraichir buffer issu du player
for(int chg=0;chg<513;chg++)
{
 buffer_gridder[grider_player][chg]=grid_levels[grid_number][num_step][chg];
}
return(0);
}


int clear_a_grid_step(int grid_number, int num_step)
{
for(int chg=0;chg<513;chg++)
{
 grid_levels[grid_number][num_step][chg]=0;
}
for(int tt=0;tt<4;tt++)
{
grid_times[grid_number][num_step][tt]=0.0;
}
grid_times[grid_number][num_step][1]=default_time;
grid_times[grid_number][num_step][3]=default_time;

grid_goto[grid_number][num_step][0]=-1;
grid_goto[grid_number][num_step][1]=-1;
grid_seekpos[grid_number][num_step]=-1;
grid_stoplay[grid_number][num_step]=0;
grid_count[grid_number][num_step]=0;
grid_counted_times[grid_number][num_step]=0;

sprintf(string_Last_Order,"Cleared Step %d in Grid %d", num_step+1, grid_number+1);

return(0);
}

int clear_part_of_a_grid(int grid_number, int num_stepfrom, int num_stepto)
{
for(int num_step=num_stepfrom;num_step<=num_stepto;num_step++)
{
for(int chg=0;chg<513;chg++)
{
 grid_levels[grid_number][num_step][chg]=0;
}
for(int tt=0;tt<4;tt++)
{
grid_times[grid_number][num_step][tt]=0.0;
}
grid_times[grid_number][num_step][1]=default_time;
grid_times[grid_number][num_step][3]=default_time;
grid_goto[grid_number][num_step][0]=-1;
grid_goto[grid_number][num_step][1]=-1;
grid_seekpos[grid_number][num_step]=-1;
grid_stoplay[grid_number][num_step]=0;
grid_count[grid_number][num_step]=0;
grid_counted_times[grid_number][num_step]=0;
}
return(0);
}


int clear_a_grid(int grid_number)
{
for(int st=0;st<1023;st++)
{
 clear_a_grid_step(grid_number,st);
 sprintf(string_Last_Order,"Cleared Grid %d", grid_number+1);
}
//sab 02/03/2014 sprintf(grider_name[grid_number],"");
strcpy(grider_name[grid_number],"");

return(0);
}

int copy_grid_partially(int from_grid_number, int from_num_step,int to_step_number, int dest_grid_number, int dest_num_step)
{
for(int defil=0;defil<=(to_step_number-from_num_step);defil++)
{
for(int chg=0;chg<513;chg++)
{
 grid_levels[dest_grid_number][dest_num_step+defil][chg]=grid_levels[from_grid_number][from_num_step+defil][chg];
}
for(int tt=0;tt<4;tt++)
{
grid_times[dest_grid_number][dest_num_step+defil][tt]=grid_times[from_grid_number][from_num_step+defil][tt];
}
grid_goto[dest_grid_number][dest_num_step+defil][0]=grid_goto[from_grid_number][from_num_step+defil][0];
grid_goto[dest_grid_number][dest_num_step+defil][1]=grid_goto[from_grid_number][from_num_step+defil][1];
grid_seekpos[dest_grid_number][dest_num_step+defil]=grid_seekpos[from_grid_number][from_num_step+defil];
grid_stoplay[dest_grid_number][dest_num_step+defil]=grid_stoplay[from_grid_number][from_num_step+defil];
grid_count[dest_grid_number][dest_num_step+defil]=grid_count[from_grid_number][from_num_step+defil];
grid_counted_times[dest_grid_number][dest_num_step+defil]=0;
}

return(0);
}


int copy_step_to_step(int from_grid_number, int from_num_step, int dest_grid_number, int dest_num_step)
{
for(int chg=0;chg<513;chg++)
{
 grid_levels[dest_grid_number][dest_num_step][chg]=grid_levels[from_grid_number][from_num_step][chg];
}
for(int tt=0;tt<4;tt++)
{
grid_times[dest_grid_number][dest_num_step][tt]=grid_times[from_grid_number][from_num_step][tt];
}
grid_goto[dest_grid_number][dest_num_step][0]=grid_goto[from_grid_number][from_num_step][0];
grid_goto[dest_grid_number][dest_num_step][1]=grid_goto[from_grid_number][from_num_step][1];
grid_seekpos[dest_grid_number][dest_num_step]=grid_seekpos[from_grid_number][from_num_step];
grid_stoplay[dest_grid_number][dest_num_step]=grid_stoplay[from_grid_number][from_num_step];
grid_count[dest_grid_number][dest_num_step]=grid_count[from_grid_number][from_num_step];
grid_counted_times[dest_grid_number][dest_num_step]=0;
 return(0);
}


int insert_steps(int dest_grid_number, int from_num_step,  int dest_nbr_step)
{

unsigned char  buffer_temp_grd[1024][513];
float tmp_grid_times[1024][4];
int tmp_grid_goto[1024][2];//0 grid 1 step
int tmp_grid_seekpos[1024];//step seek pos
bool tmp_grid_stoplay[1024];//1=pause
int tmp_grid_count[1024];
//recopie des tableaux

for(int st=0;st<1023;st++)
{
for(int chg=0;chg<513;chg++)
{
 buffer_temp_grd[st][chg]=grid_levels[dest_grid_number][st][chg];
}
for(int tt=0;tt<4;tt++)
{
tmp_grid_times[st][tt]=grid_times[dest_grid_number][st][tt];
}
tmp_grid_goto[st][0]=grid_goto[dest_grid_number][st][0];
tmp_grid_goto[st][1]=grid_goto[dest_grid_number][st][1];
tmp_grid_seekpos[st]=grid_seekpos[dest_grid_number][st];
tmp_grid_stoplay[st]=grid_stoplay[dest_grid_number][st];
tmp_grid_count[st]=grid_count[dest_grid_number][st];
}


//insert
for(int st=from_num_step;st<1023;st++)
{
if(st+dest_nbr_step+1<1024)//protection des tableaux
{
for(int chg=0;chg<513;chg++)
{
grid_levels[dest_grid_number][st+dest_nbr_step+1][chg]=buffer_temp_grd[st][chg];
}
for(int tt=0;tt<4;tt++)
{
grid_times[dest_grid_number][st+dest_nbr_step+1][tt]=tmp_grid_times[st][tt];
}
grid_goto[dest_grid_number][st+dest_nbr_step+1][0]=tmp_grid_goto[st][0];
grid_goto[dest_grid_number][st+dest_nbr_step+1][1]=tmp_grid_goto[st][1];
grid_seekpos[dest_grid_number][st+dest_nbr_step+1]=tmp_grid_seekpos[st];
grid_stoplay[dest_grid_number][st+dest_nbr_step+1]=tmp_grid_stoplay[st];
grid_count[dest_grid_number][st+dest_nbr_step+1]=tmp_grid_count[st];
}
}

//Effacement de la plage décalée// ok
clear_part_of_a_grid(dest_grid_number, from_num_step+1,  from_num_step+dest_nbr_step+1);

 return(0);
}











//calcul data dmx
int gridder_prepare_cross(int grid_pl, int gr_actual_grid, int gr_actual_step)
{

//prepa qui est le step d après
switch(grider_goto_mode[grid_pl])
{
case 0:
//asservissement au sequenciel
if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_preset]!=-1 && grid_pl==0)
{
grid_in_preset[grid_pl][0]=gr_actual_grid ;
grid_in_preset[grid_pl][1]=set_from_seq_gridplayer1_next_step[position_preset];
}
else
{
grid_in_preset[grid_pl][0]=gr_actual_grid ;
grid_in_preset[grid_pl][1]=gr_actual_step+1;
}
break;
case 1:
if(grid_goto[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][0]>=0
&& grid_goto[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][1]>=0)//0 = step 1. désafecté val=-1
{

if( grider_count_mode[grid_pl]==1 &&  grid_count[gr_actual_grid][gr_actual_step]>0
&& grid_counted_times[gr_actual_grid][gr_actual_step]>grid_count[gr_actual_grid][gr_actual_step]-1)
{
grid_in_preset[grid_pl][0]=gr_actual_grid ;
grid_in_preset[grid_pl][1]=gr_actual_step+1;
}
else
{
//goto normal original
grid_in_preset[grid_pl][0]=grid_goto[gr_actual_grid][gr_actual_step][0] ;
grid_in_preset[grid_pl][1]=grid_goto[gr_actual_grid][gr_actual_step][1] ;
}

}
else
{
//asservissement au sequenciel
if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_preset]!=-1 && grid_pl==0 && index_go==0 && index_go_back==0 && index_pause==0)
{
grid_in_preset[grid_pl][0]=gr_actual_grid ;
grid_in_preset[grid_pl][1]=set_from_seq_gridplayer1_next_step[position_preset];
}
else
{
grid_in_preset[grid_pl][0]=gr_actual_grid ;
grid_in_preset[grid_pl][1]=gr_actual_step+1 ;
if(grid_in_preset[grid_pl][1]>1023){grid_in_preset[grid_pl][1]=1023;}
}
}
break;
default:
break;
}

float in_speed,out_speed, in_speed_preset, out_speed_preset;
float delay_in_speed, delay_out_speed, delay_in_speed_preset, delay_out_speed_preset;
char the_in[12];
char the_out[12];

char the_delay_in[12];
char the_delay_out[12];

char the_in_preset[12];
char the_out_preset[12];

char the_delay_in_preset[12];
char the_delay_out_preset[12];
//
if(grid_crossfade_speed[grid_pl]<64)
{
grid_fraction_X2_in[grid_pl]= 255.0/ (grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][1]*(((float)BPS_RATE)*(64.0/grid_crossfade_speed[grid_pl])));
grid_fraction_X1_out[grid_pl]=  255.0/ (grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][3]*(((float)BPS_RATE)*(64.0/grid_crossfade_speed[grid_pl])));
in_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][1]*(64.0/grid_crossfade_speed[grid_pl]);
out_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][3]*(64.0/grid_crossfade_speed[grid_pl]);
delay_in_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][0]*(64.0/grid_crossfade_speed[grid_pl]);
delay_out_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][2]*(64.0/grid_crossfade_speed[grid_pl]);

in_speed_preset=grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][1]*(64.0/grid_crossfade_speed[grid_pl]);
out_speed_preset= grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][3]*(64.0/grid_crossfade_speed[grid_pl]);
delay_in_speed_preset=grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][0]*(64.0/grid_crossfade_speed[grid_pl]);
delay_out_speed_preset= grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][2]*(64.0/grid_crossfade_speed[grid_pl]);
}
else if(grid_crossfade_speed[grid_pl]==64)
{
grid_fraction_X2_in[grid_pl]= 255.0/ (grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][1]*BPS_RATE);
grid_fraction_X1_out[grid_pl]= 255.0/ (grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][3]*BPS_RATE);
in_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][1];
out_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][3];
delay_in_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][0];
delay_out_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][2];

in_speed_preset=grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][1];
out_speed_preset= grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][3];
delay_in_speed_preset=grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][0];
delay_out_speed_preset= grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][2];
}
else if(grid_crossfade_speed[grid_pl]>64)
{
float correcteur=(127.0-grid_crossfade_speed[grid_pl])/(grid_crossfade_speed[grid_pl]/3);
grid_fraction_X2_in[grid_pl]= 255.0/ (grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][1]*((((float)(BPS_RATE))*correcteur)/(grid_crossfade_speed[grid_pl]-62))); //-62 evite un passage de temps pas bon, cf curseur
grid_fraction_X1_out[grid_pl]=  255.0/ (grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][3]*((((float)(BPS_RATE))*correcteur)/(grid_crossfade_speed[grid_pl]-62)));
in_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][1]*(correcteur/(grid_crossfade_speed[grid_pl]-62)) ;
out_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][3]*(correcteur/(grid_crossfade_speed[grid_pl]-62));
delay_in_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][0]*(correcteur/(grid_crossfade_speed[grid_pl]-62)) ;
delay_out_speed=grid_times[(index_grider_selected[grid_pl])][(index_grider_step_is[grid_pl])][2]*(correcteur/(grid_crossfade_speed[grid_pl]-62));

in_speed_preset=grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][1]*(correcteur/(grid_crossfade_speed[grid_pl]-62)) ;
out_speed_preset= grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][3]*(correcteur/(grid_crossfade_speed[grid_pl]-62));
delay_in_speed_preset=grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][0]*(correcteur/(grid_crossfade_speed[grid_pl]-62)) ;
delay_out_speed_preset= grid_times[(grid_in_preset[grid_pl][0])][(grid_in_preset[grid_pl][1])][2]*(correcteur/(grid_crossfade_speed[grid_pl]-62));

}


affichage_time_format(in_speed);//in
sprintf(the_in,string_conversion_timeis);
affichage_time_format(out_speed);//out
sprintf(the_out,string_conversion_timeis);
affichage_time_format(delay_in_speed);//din
sprintf(the_delay_in,string_conversion_timeis);
affichage_time_format(delay_out_speed);//dout
sprintf(the_delay_out,string_conversion_timeis);


if(delay_in_speed>0 && delay_out_speed>0)
{
sprintf(string_time_in_grider[grid_pl],"%s- IN:%s / %s -OUT:%s ",the_delay_in,the_in,the_delay_out,the_out);
}
else if (delay_in_speed>0 && delay_out_speed==0)
{
sprintf(string_time_in_grider[grid_pl],"%s- IN:%s / OUT:%s ",the_delay_in,the_in,the_out);
}
else if (delay_in_speed==0 && delay_out_speed>0)
{
sprintf(string_time_in_grider[grid_pl],"IN:%s / %s -OUT:%s ",the_in,the_delay_out,the_out);
}
else
{
sprintf(string_time_in_grider[grid_pl],"IN:%s / OUT:%s ",the_in,the_out);
}


affichage_time_format(in_speed_preset);//in
sprintf(the_in_preset,string_conversion_timeis);
affichage_time_format(out_speed_preset);//out
sprintf(the_out_preset,string_conversion_timeis);
affichage_time_format(delay_in_speed_preset);//din
sprintf(the_delay_in_preset,string_conversion_timeis);
affichage_time_format(delay_out_speed_preset);//dout
sprintf(the_delay_out_preset,string_conversion_timeis);

if(delay_in_speed_preset>0 && delay_out_speed_preset>0)
{
sprintf(string_time_in_grider_next_step[grid_pl],"%s- IN:%s / %s -OUT:%s ",the_delay_in_preset,the_in_preset,the_delay_out_preset,the_out_preset);
}
else if (delay_in_speed_preset>0 && delay_out_speed_preset==0)
{
sprintf(string_time_in_grider_next_step[grid_pl],"%s- IN:%s / OUT:%s ",the_delay_in_preset,the_in_preset,the_out_preset);
}
else if (delay_in_speed_preset==0 && delay_out_speed_preset>0)
{
sprintf(string_time_in_grider_next_step[grid_pl],"IN:%s / %s -OUT:%s ",the_in_preset,the_delay_out_preset,the_out_preset);
}
else
{
sprintf(string_time_in_grider_next_step[grid_pl],"IN:%s / OUT:%s ",the_in_preset,the_out_preset);
}

grid_delay_in[grid_pl]=int(delay_in_speed_preset*BPS_RATE);
grid_delay_out[grid_pl]=int(delay_out_speed_preset*BPS_RATE);



sprintf( string_next_step_to[grid_pl],"%d - %d ", grid_in_preset[grid_pl][0]+1,grid_in_preset[grid_pl][1]+1);
return(0);
}


int do_grid()
{
int gr_grille=0;
int gr_step=0;

int gr_grille_pr=0;
int gr_step_pr=0;

for(int grid_pl=0;grid_pl<core_user_define_nb_gridplayers;grid_pl++)
{
gr_grille=index_grider_selected[grid_pl];
gr_step=index_grider_step_is[grid_pl];

gr_grille_pr=grid_in_preset[grid_pl][0];
gr_step_pr=grid_in_preset[grid_pl][1];

for(int cg=0;cg<512;cg++)
{

if(grid_levels[gr_grille][gr_step][cg]>grid_levels[gr_grille_pr][gr_step_pr][cg])
{
buffer_gridder[grid_pl][cg]=
grid_levels[gr_grille_pr][gr_step_pr][cg]
 + (unsigned char)((((float)(grid_levels[gr_grille][gr_step][cg]-grid_levels[gr_grille_pr][gr_step_pr][cg])/255)*grid_niveauX1[grid_pl])) ;
}
if(grid_levels[gr_grille][gr_step][cg]<grid_levels[gr_grille_pr][gr_step_pr][cg])
{
buffer_gridder[grid_pl][cg]=
grid_levels[gr_grille][gr_step][cg]
+ (unsigned char)((((float)(grid_levels[gr_grille_pr][gr_step_pr][cg]-grid_levels[gr_grille][gr_step][cg])/255)*grid_niveauX2[grid_pl])) ;
}
if(grid_levels[gr_grille][gr_step][cg]==grid_levels[gr_grille_pr][gr_step_pr][cg])
{
buffer_gridder[grid_pl][cg]=grid_levels[gr_grille_pr][gr_step_pr][cg];
}
}
//bug grid sur temps decales out    ALGO RIGINAL
//buffer_gridder[grid_pl][cg]=(unsigned char)((((float)grid_levels[gr_grille][gr_step][cg])/255)*grid_niveauX1[grid_pl]
//+(((float)grid_levels[grid_in_preset[grid_pl][0]][grid_in_preset[grid_pl][1]][cg])/255)*grid_niveauX2[grid_pl]);




switch(grider_is_playing[grid_pl])
{
case 0:
gridder_prepare_cross(grid_pl,gr_grille,gr_step);
break;
case 1:
if(actual_time>(grid_crossfade_start_time[grid_pl]+grid_delay_out[grid_pl]))
{
grid_floatX1[grid_pl]-=grid_fraction_X1_out[grid_pl];
if(grid_floatX1[grid_pl]<0.0){grid_floatX1[grid_pl]=0.0;}
grid_niveauX1[grid_pl]=(int)grid_floatX1[grid_pl];
}
if(actual_time>(grid_crossfade_start_time[grid_pl]+grid_delay_in[grid_pl]))
{
grid_floatX2[grid_pl]+=grid_fraction_X2_in[grid_pl];
if(grid_floatX2[grid_pl]>255.0){grid_floatX2[grid_pl]=255.0;}
grid_niveauX2[grid_pl]=(int)grid_floatX2[grid_pl];
}
if(grid_niveauX1[grid_pl]==0 && grid_niveauX2[grid_pl]==255)
{
index_grider_selected[grid_pl]=grid_in_preset[grid_pl][0];
index_grider_step_is[grid_pl]=grid_in_preset[grid_pl][1];
grid_delay_in[grid_pl]=0;
grid_delay_out[grid_pl]=0;

if(grid_in_preset[grid_pl][1]>1023){index_grider_step_is[grid_pl]=1023;}
gridder_prepare_cross(grid_pl,index_grider_selected[grid_pl],index_grider_step_is[grid_pl]);
grid_niveauX1[grid_pl]=255;
grid_niveauX2[grid_pl]=0;
grid_floatX1[grid_pl]=grid_niveauX1[grid_pl];
grid_floatX2[grid_pl]=grid_niveauX2[grid_pl];

//stop mode on, step en tant que stop ou //stopplay enclenché
if((grider_stoplay_mode[grid_pl]==1 && grid_stoplay[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]]==1)
||grider_autostopmode[grid_pl]==1)
{grider_is_playing[grid_pl]=0;}
else//start time recalcul
{
grid_crossfade_start_time[grid_pl]=actual_time;
}
//def seek step
if(grider_seekto_mode[grid_pl]==1 && grid_seekpos[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]]>0)//seek position
  {index_grider_seek_pos[grid_pl]=grid_seekpos[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]];}
//rajout comptage count
if( grider_count_mode[grid_pl]==1 &&  grid_count[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]]>0)
{
grid_counted_times[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]]++;
sprintf( string_grid_count[grid_pl],"%d/%d from S.%d",  grid_counted_times[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]],grid_count[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]], index_grider_step_is[grid_pl]+1);
if(grid_counted_times[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]]>grid_count[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]])
{
//sab 02/03/2014 sprintf( string_grid_count[grid_pl],"");
strcpy( string_grid_count[grid_pl],"");

grid_counted_times[index_grider_selected[grid_pl]][index_grider_step_is[grid_pl]]=0;
}
}

}
break;
default:
break;
}
}

 return(0);
}






int gridplayer_step_minus(int num_grid_player)
{
  index_grider_step_is[num_grid_player]--;
  if(index_grider_step_is[num_grid_player]<0){index_grider_step_is[num_grid_player]=0;}
  grid_niveauX1[num_grid_player]=255;
  grid_niveauX2[num_grid_player]=0;
  grid_floatX1[num_grid_player]=grid_niveauX1[num_grid_player];
  grid_floatX2[num_grid_player]=grid_niveauX2[num_grid_player];
  gridder_prepare_cross(num_grid_player, index_grider_selected[num_grid_player], index_grider_step_is[num_grid_player]);
  if(grider_seekto_mode[num_grid_player]==1 && grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]>0 )//seek position
  {index_grider_seek_pos[num_grid_player]=grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]];}
  grid_counted_times[index_grider_selected[num_grid_player]] [index_grider_step_is[num_grid_player]]=0;
return(0);
}

int gridplayer_step_plus(int num_grid_player)
{
  index_grider_step_is[num_grid_player]++;
  if(index_grider_step_is[num_grid_player]>1023){index_grider_step_is[num_grid_player]=1023;}
  grid_niveauX1[num_grid_player]=255;
  grid_niveauX2[num_grid_player]=0;
  grid_floatX1[num_grid_player]=grid_niveauX1[num_grid_player];
  grid_floatX2[num_grid_player]=grid_niveauX2[num_grid_player];
  gridder_prepare_cross(num_grid_player, index_grider_selected[num_grid_player], index_grider_step_is[num_grid_player]);
  if(grider_seekto_mode[num_grid_player]==1 && grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]>0 )//seek position
  {index_grider_seek_pos[num_grid_player]=grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]];}
  grid_counted_times[index_grider_selected[num_grid_player]] [index_grider_step_is[num_grid_player]]=0;
 return(0);
}

int gridplayer_seek(int num_grider)
{
 if(index_grider_seek_pos[num_grider]<0){index_grider_seek_pos[num_grider]=0;}
 index_grider_step_is[num_grider]=index_grider_seek_pos[num_grider];

/* if(grider_seekto_mode[num_grider]==1 && grid_seekpos[index_grider_selected[num_grider]][index_grider_step_is[num_grider]]>0 )//seek position
 {index_grider_seek_pos[num_grider]=grid_seekpos[index_grider_selected[num_grider]][index_grider_step_is[num_grider]];}
 else {index_grider_seek_pos[num_grider]=1;}*/
 gridder_prepare_cross(num_grider,index_grider_selected[num_grider],index_grider_step_is[num_grider]);
 grid_niveauX1[num_grider]=255;
 grid_niveauX2[num_grider]=0;
 grid_floatX1[num_grider]=grid_niveauX1[num_grider];
 grid_floatX2[num_grider]=grid_niveauX2[num_grider];
 grid_counted_times[index_grider_selected[num_grider]] [index_grider_step_is[num_grider]]=0;
 return(0);
}

