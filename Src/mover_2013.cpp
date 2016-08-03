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

* \file mover_2013.cpp
* \brief {pan and tilt for motor spot}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Ajout d'une fenêtre permettant le déplacement en pan tilt des projecteurs asservis
*
*   Add pan tilt fonctions for motor fader
*
**/

//TRACKER POUR LYRES ET MIRROIRS



///////////////////////////////////////////////////////////////////////////////
int reset_memoires()
{
for(int j=0;j<32;j++)
{
for (int i=0;i<48;i++)
{
dock_move_xy[j][i][0]=0;
dock_move_xy[j][i][1]=0;
dock_time[j][i]=0;
for(int z=0;z<16;z++)
{
dock_asservis[j][i][z]=0;
}
}
dock_move_actual_step[j]=1;// le step actuel
dock_moves_contains_steps[j]=1; // le nombre de steps contenus

spline_ratio[j]=0.0;//pour chaque spline
x_val_at_beg[j]=0.0; y_val_at_beg[j]=0.0;
x_val_at_end[j]=0.0; y_val_at_end[j]=0.0;
x_fract[j]=0.0;y_fract[j]=0.0;
}
return(0);
}

////////////////////////////////////////////////////////////////////////////////
int ClearGotoStep(int move_selected)
{
 GotoMoves[move_selected][dock_move_actual_step[move_selected]]=0;
 return(0);
}

int ClearIntoStep(int move_selected)
{
 Moves_Inpoint[move_selected]=1;
 return(0);
}




///////////////////////////////////////////////////////////////////////////////
int convert_bytes_to_int( BYTE bHaut, BYTE bBas)
{
  int v16= bBas + (bHaut*256);
  return(v16);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Move_refresh_xy(int move_selected)
{


 mover_params[0][0]=dock_move_xy[move_selected][(dock_move_actual_step[move_selected])][0];
 mover_params[1][0]=dock_move_xy[move_selected][(dock_move_actual_step[move_selected])][1];

if (tracker_mode==1)
 {
 mover_params[0][1]=dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][0] ;
 mover_params[1][1]=dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][1] ;
 }
 mover_params[2][0]=dock_asservis[move_selected][(dock_move_actual_step[move_selected])][0];
 mover_params[3][0]=dock_asservis[move_selected][(dock_move_actual_step[move_selected])][1];
 mover_params[4][0]=dock_asservis[dock_move_selected][(dock_move_actual_step[dock_move_selected])][2];

 Tracker_speedlevel=(int)(((float)dock_time[move_selected][(dock_move_actual_step[move_selected])]/BPS_RATE)*8);

  if (move_auto_stop[move_selected][dock_move_actual_step[move_selected]]==1)
  {index_cycle=0;}

 return(0);
}
////////////////////////////////////////////////////////////////////////////////
int prepare_move_values(int move_selected)//prepa du crossfade
{
if(tracker_mode==0)
{
x_val_at_beg[move_selected]=(float)mover_params[0][0];
y_val_at_beg[move_selected]=(float)mover_params[1][0];
}
if (tracker_mode==1)
{
x_val_at_beg[move_selected]=(float)convert_bytes_to_int(mover_params[0][0],mover_params[0][1]);
y_val_at_beg[move_selected]=(float)convert_bytes_to_int(mover_params[1][0],mover_params[1][1]);
}

iris_at_beg[move_selected]=(float)mover_params[2][0];
focus_at_beg[move_selected]=(float)mover_params[3][0];
zoom_at_beg[move_selected]=(float)mover_params[4][0];
//SANS GOTO
if(GotoMoves[move_selected][dock_move_actual_step[move_selected]]==0)
{
if(index_move_forward==1)
{
index_move_back=0;
if(dock_move_actual_step[move_selected]<dock_moves_contains_steps[move_selected]+1)
{   next_step[move_selected]=(dock_move_actual_step[move_selected]+1);}
else {next_step[move_selected]=1;}

if (dock_move_actual_step[move_selected]<dock_moves_contains_steps[move_selected])
{
if(tracker_mode==0)
{
x_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(next_step[move_selected])][0];
y_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(next_step[move_selected])][1];
}
else if(tracker_mode==1)
{
x_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(next_step[move_selected])][0],dock_move_xy_16b[move_selected][(next_step[move_selected])][0]);
y_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(next_step[move_selected])][1],dock_move_xy_16b[move_selected][(next_step[move_selected])][1]);
}

iris_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][0];
focus_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][1];
zoom_at_end[move_selected]=(float)dock_asservis[dock_move_selected][(next_step[move_selected])][2];
}

else if (dock_move_actual_step[move_selected]==dock_moves_contains_steps[move_selected])//pas une redite, permet de revenir en cross vers pos 0
{
if(tracker_mode==0)
{
x_val_at_end[move_selected]=(float)dock_move_xy[move_selected][1][0];//pas 1
y_val_at_end[move_selected]=(float)dock_move_xy[move_selected][1][1];//pas 1
}
else if(tracker_mode==1)
{
x_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][1][0],dock_move_xy_16b[move_selected][1][0]);//pas 1
y_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][1][1],dock_move_xy_16b[move_selected][1][1]);//pas 1
}
iris_at_end[move_selected]=(float)dock_asservis[move_selected][1][0];
focus_at_end[move_selected]=(float)dock_asservis[move_selected][1][1];
zoom_at_end[move_selected]=(float)dock_asservis[move_selected][1][2];;
}
}
if(index_move_back==1)
{
index_move_forward=0;
if(dock_move_actual_step[move_selected]>1)
{   next_step[move_selected]=(dock_move_actual_step[move_selected]-1);}
else {next_step[move_selected]=dock_moves_contains_steps[move_selected];}

if (dock_move_actual_step[move_selected]>1)
{
if(tracker_mode==0)
{
x_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(next_step[move_selected])][0];
y_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(next_step[move_selected])][1];
}
else if(tracker_mode==1)
{
x_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(next_step[move_selected])][0],dock_move_xy_16b[move_selected][(next_step[move_selected])][0]);
y_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(next_step[move_selected])][1],dock_move_xy_16b[move_selected][(next_step[move_selected])][1]);
}
iris_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][0];
focus_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][1];
zoom_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][2];
}
if (dock_move_actual_step[move_selected]==1)//pas une redite, permet de revenir en cross vers pos 1
{
if(tracker_mode==0)
{
x_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][0];
y_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][1];
}
else if (tracker_mode==1)
{
x_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][0],dock_move_xy_16b[move_selected][(dock_moves_contains_steps[move_selected])][0]);
y_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][1],dock_move_xy_16b[move_selected][(dock_moves_contains_steps[move_selected])][1]);
}
iris_at_end[move_selected]=(float)dock_asservis[move_selected][(dock_moves_contains_steps[move_selected])][0];
focus_at_end[move_selected]=(float)dock_asservis[move_selected][(dock_moves_contains_steps[move_selected])][1];
zoom_at_end[move_selected]=(float)dock_asservis[move_selected][(dock_moves_contains_steps[move_selected])][2];
}
}
}
//AVEC GOTO
if(GotoMoves[move_selected][dock_move_actual_step[move_selected]]!=0)
{
next_step[move_selected]=Moves_Inpoint[(GotoMoves[move_selected][dock_move_actual_step[move_selected]])];

if(index_move_forward==1)
{
index_move_back=0;
if(tracker_mode==0)
{
x_val_at_end[move_selected]=(float)dock_move_xy[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][0];
y_val_at_end[move_selected]=(float)dock_move_xy[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][1];
}
else if(tracker_mode==1)
{
x_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][0],dock_move_xy_16b[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][0]);
y_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][1],dock_move_xy_16b[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][1]);
}
iris_at_end[move_selected]=(float)dock_asservis[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][0];
focus_at_end[move_selected]=(float)dock_asservis[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][1];
zoom_at_end[move_selected]=(float)dock_asservis[GotoMoves[move_selected][dock_move_actual_step[move_selected]]][next_step[move_selected]][2];
}
if(index_move_back==1)
{
index_move_forward=0;
if(dock_move_actual_step[move_selected]>1)
{   next_step[move_selected]=(dock_move_actual_step[move_selected]-1);}
else {next_step[move_selected]=dock_moves_contains_steps[move_selected];}

if (dock_move_actual_step[move_selected]>1)
{
if(tracker_mode==0)
{
x_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(next_step[move_selected])][0];
y_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(next_step[move_selected])][1];
}
else if(tracker_mode==1)
{
x_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(next_step[move_selected])][0],dock_move_xy_16b[move_selected][(next_step[move_selected])][0]);
y_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(next_step[move_selected])][1],dock_move_xy_16b[move_selected][(next_step[move_selected])][1]);
}
iris_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][0];
focus_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][1];
zoom_at_end[move_selected]=(float)dock_asservis[move_selected][(next_step[move_selected])][2];
}
if (dock_move_actual_step[move_selected]==1)//pas une redite, permet de revenir en cross vers pos 1
{
if(tracker_mode==0)
{
x_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][0];
y_val_at_end[move_selected]=(float)dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][1];
}
else if(tracker_mode==1)
{
x_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][0],dock_move_xy_16b[move_selected][(dock_moves_contains_steps[move_selected])][0]);
y_val_at_end[move_selected]=(float)convert_bytes_to_int(dock_move_xy[move_selected][(dock_moves_contains_steps[move_selected])][1],dock_move_xy_16b[move_selected][(dock_moves_contains_steps[move_selected])][1]);
}
iris_at_end[move_selected]=(float)dock_asservis[move_selected][(dock_moves_contains_steps[move_selected])][0];
focus_at_end[move_selected]=(float)dock_asservis[move_selected][(dock_moves_contains_steps[move_selected])][1];
zoom_at_end[move_selected]=(float)dock_asservis[move_selected][(dock_moves_contains_steps[move_selected])][2];
}
}

}



//PREPAS FRACTIONS
//x y prep fract
if(x_val_at_beg[move_selected]>x_val_at_end[move_selected])
{
x_fract[move_selected]=(x_val_at_beg[move_selected] - x_val_at_end[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
else if (x_val_at_beg[move_selected]<x_val_at_end[move_selected])
{
x_fract[move_selected]=(x_val_at_end[move_selected] - x_val_at_beg[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}

if(y_val_at_beg[move_selected]>y_val_at_end[move_selected])
{
y_fract[move_selected]=(y_val_at_beg[move_selected] - y_val_at_end[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
else if (y_val_at_beg[move_selected]<y_val_at_end[move_selected])
{
y_fract[move_selected]=( y_val_at_end[move_selected] - y_val_at_beg[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
//iris prep fract
if(iris_at_beg[move_selected]>iris_at_end[move_selected])
{
iris_fract[move_selected]=(iris_at_beg[move_selected] - iris_at_end[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
else if (iris_at_beg[move_selected]<iris_at_end[move_selected])
{
iris_fract[move_selected]=(iris_at_end[move_selected] - iris_at_beg[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
//focus prep fract
if(focus_at_beg[move_selected]>focus_at_end[move_selected])
{
focus_fract[move_selected]=(focus_at_beg[move_selected] - focus_at_end[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
else if (focus_at_beg[move_selected]<focus_at_end[move_selected])
{
focus_fract[move_selected]=(focus_at_end[move_selected] - focus_at_beg[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
//zoom prep fract
if(zoom_at_beg[move_selected]>zoom_at_end[move_selected])
{
zoom_fract[move_selected]=(zoom_at_beg[move_selected] - zoom_at_end[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}
else if (zoom_at_beg[move_selected]<zoom_at_end[move_selected])
{
zoom_fract[move_selected]=(zoom_at_end[move_selected] - zoom_at_beg[move_selected])/ dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])];
}


move_start_value=ticks_move;
move_end_value=(move_start_value + dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])]);

if (index_spline==1)
{
Prepare_Cross_Spline(dock_move_selected);
}

return(0);
}


////////////////////////////////////////////////////////////////////////////////
int Clear_the_Move(int move_selected)
{
for(int i=0;i<48;i++)
{
dock_move_xy[move_selected][i][0]=127;
dock_move_xy[move_selected][i][1]=127;
dock_move_xy_16b[move_selected][i][0]=127;
dock_move_xy_16b[move_selected][i][1]=127;
dock_time[move_selected][i]=0;
move_auto_stop[move_selected][i]=0;
dock_time[dock_move_selected][i]=1000;
GotoMoves[move_selected][i]=0;
for(int dd=0;dd<16;dd++)
{
dock_asservis[move_selected][(dock_move_actual_step[move_selected])][dd]=0;
}
}
x_val_at_beg[move_selected]=0.0;
y_val_at_beg[move_selected]=0.0;
x_val_at_end[move_selected]=0.0;
y_val_at_end[move_selected]=0.0;
x_fract[move_selected]=0.0;
y_fract[move_selected]=0.0;
spline_ratio[move_selected]=0.0;
dock_move_actual_step[move_selected]=1;
dock_moves_contains_steps[move_selected]=1;
Moves_Inpoint[move_selected]=1;

//remise à plat de l index
index_main_clear=0;
return(0);
}

int Move_AddStep(int move_selected)
{
int temp_move_list[48][2];
int temp_move_list_16b[48][2];
int temp_asservis_list[48][16];
int temp_time_list[48];
bool temp_autostop[48];

for(int cp=0;cp<48;cp++)
{
temp_move_list[cp][0]=dock_move_xy[move_selected][cp][0];
temp_move_list[cp][1]=dock_move_xy[move_selected][cp][1];
temp_move_list_16b[cp][0]=dock_move_xy_16b[move_selected][cp][0];
temp_move_list_16b[cp][1]=dock_move_xy_16b[move_selected][cp][1];
temp_time_list[cp]=dock_time[move_selected][cp];
temp_autostop[cp]=move_auto_stop[move_selected][cp];
for (int dd=0;dd<16;dd++)
{
temp_asservis_list[cp][dd]=dock_asservis[move_selected][cp][dd];//iris zoom etc
}
}

//insertion et décalages sont intégrés dès le départ
if(dock_moves_contains_steps[move_selected]<48)
{
dock_moves_contains_steps[move_selected]+=1;
for (int mov=dock_move_actual_step[move_selected]; mov<=dock_moves_contains_steps[move_selected];mov++)
{
dock_move_xy[move_selected][mov+1][0]=temp_move_list[mov][0];
dock_move_xy[move_selected][mov+1][1]=temp_move_list[mov][1];
dock_move_xy_16b[move_selected][mov+1][0]=temp_move_list_16b[mov][0];
dock_move_xy_16b[move_selected][mov+1][1]=temp_move_list_16b[mov][1];
dock_time[move_selected][mov+1]=temp_time_list[mov];
move_auto_stop[move_selected][mov+1]=temp_autostop[mov];
for (int dd=0;dd<16;dd++)
{
dock_asservis[move_selected][mov+1][dd]=temp_asservis_list[mov][dd];//iris zoom etc
}
}

dock_move_actual_step[move_selected]+=1;
dock_move_xy[move_selected][(dock_move_actual_step[move_selected])][0]=mover_params[0][0];
dock_move_xy[move_selected][(dock_move_actual_step[move_selected])][1]=mover_params[1][0];
dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][0]=mover_params[0][1];
dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][1]=mover_params[1][1];
dock_time[move_selected][(dock_move_actual_step[move_selected])]=(int)(Tracker_speed_is*BPS_RATE);
dock_asservis[move_selected][(dock_move_actual_step[move_selected])][0]=mover_params[2][0];
dock_asservis[move_selected][(dock_move_actual_step[move_selected])][1]=mover_params[3][0];
dock_asservis[move_selected][(dock_move_actual_step[move_selected])][2]=mover_params[4][0];
move_auto_stop[move_selected][(dock_move_actual_step[move_selected])]=0;
}

return(0);
}

int Move_RecStep(int move_selected)
{

dock_move_xy[move_selected][(dock_move_actual_step[move_selected])][0]=mover_params[0][0];
dock_move_xy[move_selected][(dock_move_actual_step[move_selected])][1]=mover_params[1][0];

if(tracker_mode==1)//16 bits
{
 dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][0]=mover_params[0][1];
 dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][1]=mover_params[1][1];
}
dock_asservis[move_selected][(dock_move_actual_step[move_selected])][0]=mover_params[2][0];
dock_asservis[move_selected][(dock_move_actual_step[move_selected])][1]=mover_params[3][0];
dock_asservis[move_selected][(dock_move_actual_step[move_selected])][2]=mover_params[4][0];
dock_time[move_selected][(dock_move_actual_step[move_selected])]=(int)(Tracker_speed_is*BPS_RATE);

return(0);
}

int Move_DelStep(int move_selected)
{
//destruction et décalages sont intégrés dès le départ
if(dock_moves_contains_steps[move_selected]>0)
{
for (int mv=dock_move_actual_step[move_selected]; mv<dock_moves_contains_steps[move_selected];mv++)
{
dock_move_xy[move_selected][mv][0]=dock_move_xy[move_selected][mv+1][0];
dock_move_xy[move_selected][mv][1]=dock_move_xy[move_selected][mv+1][1];
dock_move_xy_16b[move_selected][mv][0]=dock_move_xy_16b[move_selected][mv+1][0];
dock_move_xy_16b[move_selected][mv][1]=dock_move_xy_16b[move_selected][mv+1][1];
dock_asservis[move_selected][mv][0]=dock_asservis[move_selected][mv+1][0];  //iris
dock_asservis[move_selected][mv][1]=dock_asservis[move_selected][mv+1][1];  //focus
dock_asservis[move_selected][mv][2]=dock_asservis[move_selected][mv+1][2]; //zoom
dock_time[move_selected][mv]=dock_time[move_selected][mv+1];
move_auto_stop[move_selected][mv]=move_auto_stop[move_selected][mv+1];
}
dock_moves_contains_steps[move_selected]-=1;
if (dock_move_actual_step[move_selected]>1 ){dock_move_actual_step[move_selected]-=1;}
else if( dock_move_actual_step[move_selected]==1){dock_move_actual_step[move_selected]=dock_moves_contains_steps[move_selected];}
}
Move_refresh_xy(move_selected);
return(0);
}


int Move_StepBackward(int move_selected)
{
if (dock_move_actual_step[move_selected]>1)
{
dock_move_actual_step[move_selected]--;
}
else if (dock_move_actual_step[move_selected]==1)
{
dock_move_actual_step[move_selected]=dock_moves_contains_steps[move_selected];
}
Move_refresh_xy(move_selected);

return(0);
}

int Move_StepForward(int move_selected)
{
if (dock_move_actual_step[move_selected]<dock_moves_contains_steps[move_selected])
{
dock_move_actual_step[move_selected]++;
}
else if (dock_move_actual_step[move_selected]==dock_moves_contains_steps[move_selected])
{
dock_move_actual_step[move_selected]=1;
}
Move_refresh_xy(move_selected);
return(0);
}


int Move_Autostop(int move_selected)
{
if(move_auto_stop[move_selected][dock_move_actual_step[move_selected]]==0)
{move_auto_stop[move_selected][dock_move_actual_step[move_selected]]=1;}
else if (move_auto_stop[move_selected][dock_move_actual_step[move_selected]]==1)
{move_auto_stop[move_selected][dock_move_actual_step[move_selected]]=0;}
return(0);
}

int MoveAffectGoto(int move_from, int move_to)
{
GotoMoves[move_from][dock_move_actual_step[move_from]]=move_to;
index_goto_record=0;
return(0);
}


int inversion_of_axes()
{
if(invX_on==1)
{
buffer_moving_head[xadress]=255-mover_params[0][0];
if(tracker_mode==1){buffer_moving_head[xadress+1]=255-mover_params[0][1];   }
}
else if(invX_on==0)
{
buffer_moving_head[xadress]=mover_params[0][0];
if(tracker_mode==1){buffer_moving_head[xadress+1]=mover_params[0][1];   }
}
if(invY_on==1)
{
buffer_moving_head[yadress]=255-mover_params[1][0];
if(tracker_mode==1){buffer_moving_head[yadress+1]=255-mover_params[1][1];   }
}
else if(invY_on==0)
{
buffer_moving_head[yadress]=mover_params[1][0];
if(tracker_mode==1){buffer_moving_head[yadress+1]=mover_params[1][1];   }
}
 return(0);
}

int SetAllParams(int move_selected)
{
if (tracker_mode==1)
 {
 mover_params[0][1]=dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][0] ;
 mover_params[1][1]=dock_move_xy_16b[move_selected][(dock_move_actual_step[move_selected])][1] ;
 }

for (int o=1; o<dock_moves_contains_steps[move_selected]+1;o++)
{
for(int param=2;param<16;param++)
{
if(param_selected[param]==1)
{dock_asservis[move_selected][o][param-2]=mover_params[param][0] ;}

}
}
return(0);
}

int ImportMoveInMyDock(int move_selected)
{
for (int cop=1;cop<dock_moves_contains_steps[move_selected]+1;cop++)
{
Move_AddStep(dock_move_selected);
dock_move_xy[dock_move_selected][(dock_move_actual_step[dock_move_selected])][0]=dock_move_xy[move_selected][cop][0];
dock_move_xy[dock_move_selected][(dock_move_actual_step[dock_move_selected])][1]=dock_move_xy[move_selected][cop][1];
dock_move_xy_16b[dock_move_selected][(dock_move_actual_step[dock_move_selected])][0]=dock_move_xy_16b[move_selected][cop][0];
dock_move_xy_16b[dock_move_selected][(dock_move_actual_step[dock_move_selected])][1]=dock_move_xy_16b[move_selected][cop][1];
dock_asservis[dock_move_selected][(dock_move_actual_step[dock_move_selected])][0]=dock_asservis[move_selected][cop][0];
dock_asservis[dock_move_selected][(dock_move_actual_step[dock_move_selected])][1]=dock_asservis[move_selected][cop][1];
dock_asservis[dock_move_selected][(dock_move_actual_step[dock_move_selected])][2]=dock_asservis[move_selected][cop][2];
dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])]=dock_time[move_selected][cop];
}
Move_refresh_xy(dock_move_selected);
return(0);
}


int TimeShift(int move_selected)
{

int total_deplacement=0;
int report_temp_deplacement_x=0;
int report_temp_deplacement_y=0;
int amplitude[48];
int last_amplitude=0;//(mvt de loop)
float fraction_pixel_temps=0;
for (int o=1; o<dock_moves_contains_steps[move_selected];o++)
{
report_temp_deplacement_x=dock_move_xy[move_selected][o][0]-dock_move_xy[move_selected][o+1][0];
report_temp_deplacement_y=dock_move_xy[move_selected][o][1]-dock_move_xy[move_selected][o+1][1];
if(report_temp_deplacement_x<0)
{report_temp_deplacement_x=-(report_temp_deplacement_x);}
if(report_temp_deplacement_y<0)
{report_temp_deplacement_y=-(report_temp_deplacement_y);}
if(report_temp_deplacement_x>report_temp_deplacement_y){amplitude[o]=report_temp_deplacement_x;}
else {amplitude[o]=report_temp_deplacement_y;}
total_deplacement+=amplitude[o];
}
//loop debut fin
report_temp_deplacement_x=dock_move_xy[move_selected][dock_moves_contains_steps[move_selected]][0]-dock_move_xy[move_selected][1][0];
report_temp_deplacement_y=dock_move_xy[move_selected][dock_moves_contains_steps[move_selected]][1]-dock_move_xy[move_selected][1][1];
if(report_temp_deplacement_x<0)
{report_temp_deplacement_x=-(report_temp_deplacement_x);}
if(report_temp_deplacement_y<0)
{report_temp_deplacement_y=-(report_temp_deplacement_y);}
if(report_temp_deplacement_x>report_temp_deplacement_y){last_amplitude=report_temp_deplacement_x;}
else {last_amplitude=report_temp_deplacement_y;}
total_deplacement+=last_amplitude;

Tracker_speed_is=((float)Tracker_speedlevel)/8; // secondes
fraction_pixel_temps=(Tracker_speed_is*BPS_RATE)/total_deplacement;

//ventilation // le plus 1 est pour inclure le dernier mouvement
for (int r=1;r<dock_moves_contains_steps[move_selected];r++)
{
dock_time[move_selected][r]=(int)(amplitude[r]*fraction_pixel_temps);
}
dock_time[move_selected][dock_moves_contains_steps[move_selected]]=(int)(last_amplitude*fraction_pixel_temps);

sprintf(string_time_shift,"total_pixel_shift %d",total_deplacement);
index_time_shift=0;
Tracker_speedlevel=(int)(((float)dock_time[move_selected][dock_move_actual_step[move_selected]]/BPS_RATE)*8);

return(0);
}

int Print_Points(int move_selected)
{

    for(int dms=1;dms<dock_moves_contains_steps[move_selected]+1;dms++)
    {
    Circle CercleShowPoint( Vec2D(dock_move_xy[move_selected][dms][0]+xmover_window+20, dock_move_xy[move_selected][dms][1]+ymover_window+20), 4 );
    Rect ShowInPoint(Vec2D (dock_move_xy[move_selected][dms][0]+xmover_window+12, dock_move_xy[move_selected][dms][1]+ymover_window+12), Vec2D ( 16,16));

    if(dms==Moves_Inpoint[move_selected]){ShowInPoint.Draw(CouleurLock);}
    CercleShowPoint.Draw(Rgba::WHITE);
    petitchiffre.Print(ol::ToString(dms), dock_move_xy[move_selected][dms][0]+xmover_window+30, dock_move_xy[move_selected][dms][1]+ymover_window+30);
    }

 return(0);
}

int reset_mover_buffer()
{
 for(int i=0;i<512;i++)
 {
 buffer_moving_head[i]=0;
 }
 return(0);
}

int param_editor(int xt, int yt)
{
neuromoyen.Print("Move Params", xt, yt-10);

char string_para[5][16];
sprintf(string_para[0],"X");
sprintf(string_para[1],"Y");
sprintf(string_para[2],"Iris");
sprintf(string_para[3],"Focus");
sprintf(string_para[4],"Zoom");
for(int dv=0;dv<5;dv++)
{
Rect ParamN(Vec2D( xt+60,yt+5+(dv*15)),Vec2D(30,12));
Rect LevelFrame(Vec2D(xt+180,yt+5+(dv*15)),Vec2D(255,10));
LevelFrame.SetRoundness(5);
if(window_focus_id==W_MOVER && index_do_dock==1 && mouse_x>xt+60 && mouse_x<xt+60+30 && mouse_y>yt+5+(dv*15) && mouse_y<yt+5+(dv*15)+10  && mouse_button==1 && mouse_released==0)
{
ParamN.Draw(CouleurBlind);

int adress_to_attribute=atoi(numeric);
if(adress_to_attribute>0 && adress_to_attribute<513)
{

mover_params_adresses[dv]=adress_to_attribute;
switch(dv)
{
case 0:
xadress=adress_to_attribute;
break;
case 1:
yadress=adress_to_attribute;
break;
case 2:
irisadress=adress_to_attribute;
break;
case 3:
focusadress=adress_to_attribute;
break;
case 4:
zoomadress=adress_to_attribute;
break;
default:
break;
}
reset_mover_buffer();
reset_numeric_entry();numeric_postext=0;
mouse_released=1;
}

}


minichiffre.Print(string_para[dv], xt, yt+15+(dv*15));
int v_tmp=0;
switch(dv)
{
case 0:
minichiffre.Print(ol::ToString(xadress), xt+65,yt+15+(dv*15));
if(tracker_16b_edit==0) {v_tmp=mover_params[0][0];}
else { v_tmp=mover_params[0][1];}

break;
case 1:
minichiffre.Print(ol::ToString(yadress), xt+65,yt+15+(dv*15));
if(tracker_16b_edit==0) {v_tmp=mover_params[1][0];}
else { v_tmp=mover_params[1][1];}
break;
case 2:
minichiffre.Print(ol::ToString(irisadress), xt+65,yt+15+(dv*15));
if(tracker_16b_edit==0) {v_tmp=mover_params[2][0];}
else { v_tmp=mover_params[2][1];}
break;
case 3:
minichiffre.Print(ol::ToString(focusadress), xt+65, yt+15+(dv*15));
if(tracker_16b_edit==0) {v_tmp=mover_params[3][0];}
else { v_tmp=mover_params[3][1];}
break;
case 4:
minichiffre.Print(ol::ToString(zoomadress), xt+65, yt+15+(dv*15));

if(tracker_16b_edit==0) {v_tmp=mover_params[4][0]; }
else { v_tmp=mover_params[4][1];}
break;
default:
break;
}
ParamN.DrawOutline(CouleurLigne);
Rect Level(Vec2D(xt+180,yt+5+(dv*15)),Vec2D(v_tmp,10));
Level.SetRoundness(5);
Level.Draw(CouleurFader.WithAlpha(0.7));
LevelFrame.DrawOutline(CouleurLigne.WithAlpha(0.3));

sprintf(string_param_mover_is,"%d %d", mover_params[dv][0], mover_params[dv][1]);
minichiffre.Print(string_param_mover_is,xt+110,  yt+15+(dv*15));


if(window_focus_id==W_MOVER && mouse_x> xt+180-10 && mouse_x< xt+180+255+10 && mouse_y>=yt+5+(dv*15) && mouse_y<yt+5+(dv*15)+10 && mouse_button==1)
{
set_mouse_range(xt+180-10,yt+5+(dv*15), xt+180+255+10, yt+5+(dv*15)+10);//liberation du curseur souris
int valeur=mouse_x-(xt+180-10);
valeur=constrain_data_to_dmx_range(valeur);
switch(dv)
{
case 0:
if(tracker_16b_edit==0)
{
mover_params[0][0]=valeur;
}
else //fine
{
mover_params[0][1]=valeur;
}
break;

case 1:
if(tracker_16b_edit==0)
{
mover_params[1][0]=valeur;
}
else //fine
{
mover_params[1][1]=valeur;
}
break;

case 2:
if(tracker_16b_edit==0)
{
mover_params[2][0]=valeur;
}
else //fine
{
mover_params[2][1]=valeur;
}
break;

case 3:
if(tracker_16b_edit==0)
{
mover_params[3][0]=valeur;
}
else //fine
{
mover_params[3][1]=valeur;
}
break;

case 4:
if(tracker_16b_edit==0)
{
mover_params[4][0]=valeur;
}
else //fine
{
mover_params[4][1]=valeur;
}
break;
default:
break;
}
}
//hors XY
if(dv>=2)
{
Rect AllowCopyParams(Vec2D(xt+445,yt+5+(dv*15)),Vec2D(10,10));
AllowCopyParams.Draw(CouleurFader.WithAlpha(param_selected[dv]));
AllowCopyParams.DrawOutline(CouleurLigne.WithAlpha(0.3));
if(window_focus_id==W_MOVER && mouse_x>xt+445 && mouse_x<xt+445+10 && mouse_y>yt+5+(dv*15) && mouse_y<yt+5+(dv*15)+10 && mouse_button==1 && mouse_released==0)
{
param_selected[dv]=toggle(param_selected[dv]);
mouse_released=1;
}
}

}
//fin boucle des lignes


//IRIS zoom REMISE A PLAT//////////////////////////////////////////////
//COPIE D UN ETAT DANS UNE BANQUE/////////////////////////////////////////////////////////
Rect ShiftIris(Vec2D(xt+5,yt+130),Vec2D(100,20));
ShiftIris.SetRoundness(4);
ShiftIris.Draw(CouleurFader.WithAlpha(index_copy_params));
ShiftIris.DrawOutline(Rgba::WHITE);
petitchiffre.Print("Set To Bank",xt+15, yt+143);


if(window_focus_id==W_MOVER && mouse_x>xt+5 && mouse_x<xt+5+100 && mouse_y>yt+130 && mouse_y<yt+130+20)
{
if(mouse_button==1  && index_mouse_is_tracking==0 && mouse_released==0 )
{
index_copy_params=toggle(index_copy_params); mouse_released=1;
}
}





 return(0);
}


int mover_box(int x_track,int y_track)
{

int track_aera_x=x_track+20, track_aera_y=y_track+20;
Tracker_speed_is=((float)Tracker_speedlevel)/8;

//background window
Rect TrckBackground(Vec2D (x_track, y_track-40 ), Vec2D ( 1000,660));
TrckBackground.SetRoundness(15);
TrckBackground.Draw(CouleurFond);

TrckBackground.SetLineWidth(triple_epaisseur_ligne_fader);
TrckBackground.DrawOutline(Rgba::WHITE);
if(window_focus_id==W_MOVER)
{
TrckBackground.DrawOutline(CouleurFader);
}

neuro.Print("MOVER",x_track+100, y_track-10);

//border
Rect BorderTrckWindow(Vec2D(track_aera_x-10,track_aera_y-10),Vec2D(275,275));
BorderTrckWindow.SetRoundness(15);
BorderTrckWindow.SetLineWidth(demi_epaisseur_ligne_fader);
BorderTrckWindow.DrawOutline(Rgba::WHITE);

//tracking zone
Rect TrckWindow(Vec2D(track_aera_x,track_aera_y),Vec2D(255,255));
TrckWindow.SetRoundness(7.5);
TrckWindow.SetLineWidth(demi_epaisseur_ligne_fader);


//affichage du tracker

 Circle monTracker( Vec2D(mover_params[0][0]+track_aera_x, mover_params[1][0]+track_aera_y), 10 );
 monTracker.SetLineWidth(epaisseur_ligne_fader);

//affichage du tracker fine ( 16 bits)
 Circle monTrackerfine( Vec2D(mover_params[0][1]+track_aera_x, mover_params[1][1]+track_aera_y), 10 );
 monTrackerfine.SetLineWidth(epaisseur_ligne_fader);

if(tracker_16b_edit==0){TrckWindow.Draw( CouleurSelection); }
else if(tracker_16b_edit==1)
{TrckWindow.Draw(CouleurBleuProcedure.WithAlpha(0.5));
 monTrackerfine.DrawOutline( Rgba::YELLOW );}


//mire
Line(Vec2D(track_aera_x+127,track_aera_y), Vec2D( track_aera_x+127,track_aera_y+255)).Draw(CouleurLigne);
Line(Vec2D(track_aera_x,track_aera_y+127), Vec2D( track_aera_x+255,track_aera_y+127)).Draw(CouleurLigne);
Circle CercleMire( Vec2D(track_aera_x+127, track_aera_y+127), 127 );
CercleMire.DrawOutline( Rgba::WHITE );


//affichage ZERO POINT
 Circle CercleZeroPoint( Vec2D(position_defaut[0]+track_aera_x+127,position_defaut[1]+track_aera_y+127), 6 );
 CercleZeroPoint.Draw(Rgba::BLACK.WithAlpha(0.3));




/////////////////////zoom IRIS/////////////////////////////////////////////////
if(tracker_16b_edit==0)
{
Circle CercleShowIris( Vec2D(track_aera_x+127,track_aera_y+127), (int)(mover_params[2][0]/2) );
CercleShowIris.Draw(Rgba::WHITE.WithAlpha(0.2));
Circle CercleShowFocus( Vec2D(track_aera_x+127,track_aera_y+127), (int)(mover_params[3][0]/2) );
CercleShowFocus.Draw(Rgba::BLUE.WithAlpha(0.2));
Circle CercleShowZoom( Vec2D(track_aera_x+127,track_aera_y+127), (int)(mover_params[4][0]/2) );
CercleShowZoom.SetLineWidth(demi_epaisseur_ligne_fader);
CercleShowZoom.DrawOutline(Rgba::BLACK);
}
else if(tracker_16b_edit==1)
{
Circle CercleShowIris( Vec2D(track_aera_x+127,track_aera_y+127), (int)(mover_params[2][1]/2) );
CercleShowIris.Draw(Rgba::WHITE.WithAlpha(0.2));
Circle CercleShowFocus( Vec2D(track_aera_x+127,track_aera_y+127), (int)(mover_params[3][1]/2) );
CercleShowFocus.Draw(Rgba::BLUE.WithAlpha(0.2));
Circle CercleShowZoom( Vec2D(track_aera_x+127,track_aera_y+127), (int)(mover_params[4][1]/2) );
CercleShowZoom.SetLineWidth(demi_epaisseur_ligne_fader);
CercleShowZoom.DrawOutline(Rgba::BLACK);
}


 //over tracker
 if(window_focus_id==W_MOVER && mouse_x>=track_aera_x && mouse_x<=track_aera_x+255 && mouse_y>=track_aera_y && mouse_y<=track_aera_y+255 )
{
if(tracker_16b_edit==0)
{
monTracker.Draw( Rgba::RED );
if(mouse_button==1)
{

index_move_crossfade_is_on=0;
 index_move_back=0;
 index_move_forward=0;
index_mouse_is_tracking=1;

if(lockX_on==0 ){mover_params[0][0]=mouse_x-track_aera_x;}
if(lockY_on==0){mover_params[1][0]=mouse_y-track_aera_y;}


}
}
else if(tracker_16b_edit==1)
{
monTrackerfine.Draw( Rgba::YELLOW );
if(mouse_button==1)
{
index_mouse_is_tracking=1;
if(lockX_on==0){mover_params[0][1]=mouse_x-track_aera_x;}
if(lockY_on==0){mover_params[1][1]=mouse_y-track_aera_y;}
}
}
}


 if(index_spline==1)
{

ShowSpline(dock_move_selected);
}


//SPEED SLIDER
//FADER
Rect SliderFaderSpeed( Vec2D( x_track+420,y_track+350 ), Vec2D ( 50,255));//box du fader
SliderFaderSpeed.SetRoundness(15);
SliderFaderSpeed.SetLineWidth(epaisseur_ligne_fader);
Rect LevelFaderSpeed( Vec2D( x_track+420,y_track+350+255-Tracker_speedlevel ), Vec2D ( 50,Tracker_speedlevel));//box du fader
LevelFaderSpeed.SetRoundness(15);
LevelFaderSpeed.SetLineWidth(epaisseur_ligne_fader);
if(window_focus_id==W_MOVER && mouse_x>x_track+420 && mouse_x<x_track+470 && mouse_y>y_track+350 && mouse_y<=y_track+350+255)
{
if(mouse_button==1  && index_mouse_is_tracking==0 )
{
Tracker_speedlevel=(y_track+350+255)-mouse_y;
Tracker_speed_is=((float)Tracker_speedlevel)/8;
dock_time[dock_move_selected][dock_move_actual_step[dock_move_selected]]=(int)(Tracker_speed_is*BPS_RATE);
}
}
if(index_move_crossfade_is_on==0)
{
LevelFaderSpeed.Draw(CouleurNiveau);
color_cycling=0.0;
}
else if(index_move_crossfade_is_on==1)
{
if(color_cycling<=0.95)
{
color_cycling+=0.05;}
else {color_cycling=0.05;}
Rgba Cycling(1.0,0.0+color_cycling,0.0);
LevelFaderSpeed.Draw(Cycling);
}
SliderFaderSpeed.DrawOutline(Rgba::WHITE);
petitchiffre.Print("STEP",x_track+427, y_track+305);
petitchiffre.Print("SPEED",x_track+425, y_track+320);
sprintf(string_seconds_Tracker_speed_is,"%.1f sec.",Tracker_speed_is);
petitchiffre.Print(string_seconds_Tracker_speed_is,x_track+425, y_track+335);

////////////////////////Menu de Steps///////////////////////////////////////////

for (int lopt=0;lopt<4;lopt++)
{
//ligne1
Rect StepActionL1(Vec2D(x_track+20+(lopt*40),track_aera_y+275),Vec2D(30,20));

//ligne2
Rect StepActionL2(Vec2D(x_track+20+(lopt*40),track_aera_y+305),Vec2D(30,20));

switch(lopt)
{
case 0:
sprintf(string_titre_stepsL1,"Add");sprintf(string_titre_stepsL2," <<<");
StepActionL1.DrawOutline(Rgba::WHITE);
StepActionL2.DrawOutline(Rgba::WHITE);
break;
case 1:
sprintf(string_titre_stepsL1," Rec");sprintf(string_titre_stepsL2," >>>");
StepActionL1.DrawOutline(Rgba::WHITE);
StepActionL2.DrawOutline(Rgba::WHITE);
break;
case 2:
sprintf(string_titre_stepsL1," Del"); sprintf(string_titre_stepsL2,"S.CYC");
if (move_auto_stop[dock_move_selected][dock_move_actual_step[dock_move_selected]]==1)
{StepActionL2.Draw(Rgba::RED);}
StepActionL1.DrawOutline(Rgba::WHITE);
StepActionL2.DrawOutline(Rgba::WHITE);
break;
case 3:
sprintf(string_titre_stepsL1,"  %d",Moves_Inpoint[dock_move_selected]); sprintf(string_titre_stepsL2,"  %d",GotoMoves[dock_move_selected][(dock_move_actual_step[dock_move_selected])]);
if(Moves_Inpoint[dock_move_selected]==dock_move_actual_step[dock_move_selected])
{StepActionL1.Draw(CouleurLock.WithAlpha(0.5));}
if(GotoMoves[dock_move_selected][(dock_move_actual_step[dock_move_selected])]!=0)
{StepActionL2.Draw(CouleurBlind.WithAlpha(0.5));}
if(index_goto_record==1)
{StepActionL2.Draw(CouleurFader.WithAlpha(alpha_blinker));}
StepActionL1.DrawOutline(CouleurLock);
StepActionL2.DrawOutline(CouleurBlind);
break;
default: break;
}
//ligne 1 des actions sur steps
if( window_focus_id==W_MOVER && mouse_x>x_track+20+(lopt*40) && mouse_x<x_track+20+30+(lopt*40) && mouse_y>track_aera_y+275 && mouse_y<track_aera_y+295)
{
if(mouse_button==1 && mouse_released==0 && index_mouse_is_tracking==0 )
{
switch(lopt)
{
case 0:
Move_AddStep(dock_move_selected);
break;
case 1:
Move_RecStep(dock_move_selected);
break;
case 2:
Move_DelStep(dock_move_selected);
break;
case 3:
if(  index_main_clear==0 && index_goto_record==0)
{Moves_Inpoint[dock_move_selected]=dock_move_actual_step[dock_move_selected];}
else if(  index_goto_record==0 && index_main_clear==1)
{ClearIntoStep(dock_move_selected);index_main_clear=0;}
break;
default: break;
}
mouse_released=1;
}
}
//ligne 2 des actions sur steps
if(window_focus_id==W_MOVER && mouse_x>x_track+20+(lopt*40) && mouse_x<x_track+20+30+(lopt*40) && mouse_y>track_aera_y+305 && mouse_y<track_aera_y+325)
{
if(mouse_button==1 && mouse_released==0 && index_mouse_is_tracking==0  )
{
switch(lopt)
{
case 0:
Move_StepBackward(dock_move_selected);
break;
case 1:
Move_StepForward(dock_move_selected);
break;
case 2:
Move_Autostop(dock_move_selected);
break;
case 3:
if(  index_main_clear==0)
{
if(index_goto_record==0){index_goto_record=1;index_main_clear=0; }
else  if(index_goto_record==1){index_goto_record=0;}
}
else if( index_main_clear==1)
{
ClearGotoStep(dock_move_selected);
index_main_clear=0;
}
break;
default: break;
}
mouse_released=1;
}
}

petitchiffre.Print(string_titre_stepsL1,x_track+20+(lopt*40), track_aera_y+288);
petitchiffre.Print(string_titre_stepsL2,x_track+20+(lopt*40), track_aera_y+318);
}




//Affichage des pas
sprintf(string_dock_selection,"Bank %d : Step %d / %d ",dock_move_selected,dock_move_actual_step[dock_move_selected],dock_moves_contains_steps[dock_move_selected] );
neuromoyen.Print(string_dock_selection, x_track+180,y_track+310);
if(index_move_crossfade_is_on==1)
{
if (next_step[dock_move_selected]!=1 || next_step[dock_move_selected]!=dock_moves_contains_steps[dock_move_selected]+1)
{
if(GotoMoves[dock_move_selected][dock_move_actual_step[dock_move_selected]]==0)
{
sprintf(string_dock_selection2,">> to step %d Bank %d",next_step[dock_move_selected],dock_move_selected );
if(next_step[dock_move_selected]>dock_moves_contains_steps[dock_move_selected])
{
sprintf(string_dock_selection2,">> to step 1" );
}
}
if(GotoMoves[dock_move_selected][dock_move_actual_step[dock_move_selected]]!=0)
{
sprintf(string_dock_selection2,">> GOTO step %d Bank %d",Moves_Inpoint[(GotoMoves[dock_move_selected][dock_move_actual_step[dock_move_selected]])],GotoMoves[dock_move_selected][dock_move_actual_step[dock_move_selected]] );
}
}
neuromoyen.Print(string_dock_selection2, x_track+180,y_track+340);
}



//PLAY BACK
Rect PlayBackMove( Vec2D( x_track+20,y_track+360 ), Vec2D ( 60,25));//box du fader
PlayBackMove.SetRoundness(4);

if( window_focus_id==W_MOVER && mouse_x>x_track+20 && mouse_x<x_track+20+60 && mouse_y>y_track+360 && mouse_y<y_track+385)
{
 PlayBackMove.Draw(CouleurSurvol);
 if(mouse_button==1  && mouse_released==0 && index_mouse_is_tracking==0 )
 {
 if(index_move_back==0 )
 {
 if(index_move_forward==1)//si dejà cross en cours, permet de recaler la position
 {  index_move_forward=0;
    dock_move_actual_step[dock_move_selected]++;
    if(dock_move_actual_step[dock_move_selected]>dock_moves_contains_steps[dock_move_selected])
    {dock_move_actual_step[dock_move_selected]=1;}
 }
 index_move_back=1; index_move_crossfade_is_on=1;
 }

 else //stop du move
 {
 index_move_crossfade_is_on=0; index_move_forward=0; index_move_back=0;
 }
 prepare_move_values(dock_move_selected);
 mouse_released=1;
 }
}
if(index_move_back==1){PlayBackMove.Draw(CouleurFader); }
PlayBackMove.DrawOutline(Rgba::WHITE);
petitchiffre.Print("GO BACK",x_track+25, y_track+375);

//PLAY GO
Rect PlayGoMove( Vec2D( x_track+100,y_track+360 ), Vec2D ( 60,25));//box du fader
PlayGoMove.SetRoundness(4);

if( window_focus_id==W_MOVER && mouse_x>x_track+100 && mouse_x<x_track+100+60 && mouse_y>y_track+360 && mouse_y<y_track+385)
{
 PlayGoMove.Draw(CouleurSurvol);
 if(mouse_button==1  && mouse_released==0 && index_mouse_is_tracking==0 )
 {
 if(index_move_crossfade_is_on==0)
 {
 index_move_back=0;
 index_move_forward=1; index_move_crossfade_is_on=1;
 prepare_move_values(dock_move_selected);
 }
 else
 {
 index_move_crossfade_is_on=0;    index_move_forward=0;
 }
 mouse_released=1;
 }
}
if(index_move_forward==1){PlayGoMove.Draw(CouleurFader); }
PlayGoMove.DrawOutline(Rgba::WHITE);
petitchiffre.Print("GO",x_track+120, y_track+375);


//CYCLE OR NOT CYCLE
Rect CycleMove( Vec2D( x_track+180,y_track+360 ), Vec2D ( 60,25));//box du fader
CycleMove.SetRoundness(4);

if(window_focus_id==W_MOVER && mouse_x>x_track+180 && mouse_x<x_track+240 && mouse_y>y_track+360 && mouse_y<y_track+385)
{
 if(mouse_button==1  && mouse_released==0 && index_mouse_is_tracking==0 )
 {
 index_cycle=toggle(index_cycle);
 mouse_released=1;
 }
}
if(index_cycle==1){CycleMove.Draw(CouleurBlind.WithAlpha(alpha_blinker)); }
CycleMove.DrawOutline(Rgba::WHITE);
petitchiffre.Print("CYCLE",x_track+190, y_track+375);





/////////////SPLINE//////////////////////////////////////////////////////////////////////////////
Rect SplineOn( Vec2D( x_track+260,y_track+360 ), Vec2D ( 60,25));//box du fader
SplineOn.SetRoundness(4);
SplineOn.Draw(CouleurFader.WithAlpha(index_spline));
if(window_focus_id==W_MOVER && mouse_x>x_track+260 && mouse_x<x_track+320 && mouse_y>y_track+360 && mouse_y<y_track+385)
{
if(mouse_button==1  && mouse_released==0 && index_mouse_is_tracking==0 )
{
index_spline=toggle(index_spline);mouse_released=1;
}
}

SplineOn.DrawOutline(Rgba::WHITE);
petitchiffre.Print(" SPLINE",x_track+260, y_track+375);

sprintf(string_spline_ratio,"  %.2f",spline_ratio[dock_move_selected]*-1);

petitpetitchiffre.Print(string_spline_ratio,x_track+340,y_track+365);
//spline ratio
Rect SliderFaderSpline( Vec2D( x_track+230,y_track+400 ), Vec2D ( 127,20));//box du fader
SliderFaderSpline.SetRoundness(3);
Rect LevelFaderSpline( Vec2D( x_track+230,y_track+400) , Vec2D ( Tracker_splinelevel,20));//box du fader
LevelFaderSpline.SetRoundness(3);

//SLIDER SPLINE
if(window_focus_id==W_MOVER && mouse_x>=x_track+230-10 && mouse_x<=x_track+230+127+10 && mouse_y>=y_track+400 && mouse_y<=y_track+420)
{
if(mouse_button==1  && index_mouse_is_tracking==0  )
{
int data=mouse_x-(x_track+230);
Tracker_splinelevel=constrain_data_to_midi_range(data);
spline_ratio[dock_move_selected]=Tracker_splinelevel/127.0;
}
}

LevelFaderSpline.Draw(CouleurLock);
SliderFaderSpline.DrawOutline(Rgba::WHITE);
Line(Vec2D(x_track+230+63,y_track+400), Vec2D(x_track+230+63,y_track+400+20)).Draw(CouleurLigne);
Line(Vec2D(x_track+230+65,y_track+400), Vec2D(x_track+230+65,y_track+400+20)).Draw(CouleurLigne);

///////////////////////TIME SHIFT REDISTRIBUTION //////////////////////////////////////////////
Rect Timeshift(Vec2D(x_track+300,y_track+490),Vec2D(70,20));
Timeshift.SetRoundness(3);


if(window_focus_id==W_MOVER && mouse_x>x_track+300 && mouse_x<x_track+300+70 && mouse_y>y_track+490 && mouse_y<y_track+490+20)
{
Timeshift.Draw(CouleurSurvol);
if(mouse_button==1 && mouse_released==0 && index_mouse_is_tracking==0 )
{
index_time_shift=toggle(index_time_shift);
mouse_released=1;
}
}

Timeshift.Draw(CouleurFader.WithAlpha(index_time_shift));

Timeshift.DrawOutline(Rgba::WHITE);
petitchiffre.Print("TimeShift",x_track+305, y_track+505);




/////////////////////////DOCKS MOVE////////////////////////////////////////////////////////////////////
petitchiffre.Print("Banks of moves:",x_track+300,y_track-10);
for(int dkmov=0;dkmov<5;dkmov++)
{
for(int dkline=0;dkline<6;dkline++)
{
Rect DockMove( Vec2D( x_track+300+(dkmov*40),y_track+(dkline*30) ), Vec2D ( 30,25));//box du fader
DockMove.SetRoundness(5);
//DockMove.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_MOVER && mouse_x> x_track+300+(dkmov*40) && mouse_x< x_track+330+(dkmov*40) && mouse_y>y_track+(dkline*30) && mouse_y<y_track+25+(dkline*30))
{
  DockMove.Draw(CouleurSurvol);
  if(mouse_button==1  && mouse_released==0)//index_mouse_is_tracking==0 )
  {
  if(index_main_clear==0 && index_goto_record==0 && index_time_shift==0 && index_copy_params==0 )
  {
  dock_move_selected=(dkmov+(dkline*5)+1);
  Tracker_speedlevel=(int)(((float)dock_time[dock_move_selected][(dock_move_actual_step[dock_move_selected])]/BPS_RATE)*8);
  Tracker_splinelevel=(int)((spline_ratio[dock_move_selected]+1)*100);
  }
  else if(index_main_clear==1 && index_goto_record==0 && index_time_shift==0 && index_copy_params==0 )
  {
   index_ask_clear_a_move=1;
   move_to_clear=dkmov+(dkline*5)+1;
   index_ask_confirm=1;
  }
  else if(index_goto_record==1 && index_main_clear==0 && index_time_shift==0  && index_copy_params==0 )
  {
  if(dock_move_selected!=(dkmov+(dkline*5)+1)) { MoveAffectGoto(dock_move_selected,(dkmov+(dkline*5)+1));}
  else { MoveAffectGoto(dock_move_selected,0);}
  }

  else if(index_time_shift==1 && index_main_clear==0 && index_goto_record==0  && index_copy_params==0 )
  {
  TimeShift(dock_move_selected);
  }
  else if(index_copy_params==1 &&  index_time_shift==0 && index_main_clear==0 && index_goto_record==0 )
  {
  SetAllParams(dkmov+(dkline*5)+1);
  index_copy_params=0;
  }

  mouse_released=1;
  }
}

if(dock_move_selected==(dkmov+(dkline*5)+1))
{DockMove.Draw(CouleurFader);}

petitchiffre.Print(ol::ToString(dkmov+(dkline*5)+1), x_track+310+(dkmov*40),y_track+15+(dkline*30));
DockMove.DrawOutline(Rgba::WHITE);
}
}

//////////////////////////DEVICE ADRESSES//////////////////////////////////////////////////////////////////
//les relatifs
param_editor(x_track+530,y_track);


/////////////////////////////////////////////////////////////////////////////////
//mis ici pour cause de visibilité avec splines
if(index_show_points==1)
{
Print_Points(dock_move_selected);
}



//affichage au dessus du tracker
  monTracker.DrawOutline( Rgba::WHITE );











///////////////////////////AFFCECT TO DOCK///////////////////////////////////////
Rect AffectToDock( Vec2D( x_track+310,y_track+250 ), Vec2D ( 150,25));//box du fader
AffectToDock.SetRoundness(7.5);
AffectToDock.Draw(CouleurFader.WithAlpha(index_affect_to_dock_mover));
AffectToDock.DrawOutline(CouleurLigne);

petitchiffre.Print("Affect Mover to Dock",x_track+315,y_track+265);
if(window_focus_id==W_MOVER && mouse_x>x_track+310 && mouse_x<x_track+310+150 && mouse_y>y_track+250 && mouse_y<y_track+250+25 && mouse_button==1 && mouse_released==0)
{
 if(index_affect_to_dock_mover==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_affect_to_dock_mover=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_affect_to_dock_mover;
 mouse_released=1;
}



//TOGGLE 8 / 16 BITS
Rect BitMode(Vec2D(track_aera_x+20,track_aera_y+380),Vec2D(60,25));
BitMode.SetRoundness(7.5);
BitMode.SetLineWidth(epaisseur_ligne_fader);
sprintf(string_tracker_coordonates,">> X: %d - Y: %d", buffer_moving_head[xadress],buffer_moving_head[yadress]);

if(window_focus_id==W_MOVER && mouse_x>track_aera_x+20 && mouse_x< track_aera_x+80 && mouse_y>track_aera_y+380 && mouse_y<track_aera_y+405)
{
 if(mouse_button==1  && mouse_released==0 && index_mouse_is_tracking==0 )
 {
 tracker_mode=toggle(tracker_mode);   mouse_released=1;
 }
}
if (tracker_mode==0)
{
sprintf(string_tracker_mode," 8 Bits");
}
else if (tracker_mode==1)
{
BitMode.Draw(CouleurFader);
sprintf(string_tracker_coordonates_fine,">> X: %d - Y: %d ", buffer_moving_head[xadress+1], buffer_moving_head[yadress+1]);
sprintf(string_tracker_mode,"16 Bits")  ;
petitchiffre.Print(string_tracker_coordonates_fine,x_track+110, y_track+450);
v16viewX=convert_bytes_to_int(mover_params[0][0], mover_params[0][1]);
 v16viewY=convert_bytes_to_int(mover_params[1][0], mover_params[1][1]);
 sprintf(string_view_16bits_coordonates,"16 bits : X: %d  / Y: %d", v16viewX,v16viewY);
petitchiffre.Print(string_view_16bits_coordonates,x_track+230,y_track+450);
}
BitMode.DrawOutline(Rgba::WHITE);
petitchiffre.Print(string_tracker_mode,x_track+45, y_track+415);
petitchiffre.Print(string_tracker_coordonates,x_track+110, y_track+415);


//EDIT FINE ON OFF
Rect EditFine(Vec2D(track_aera_x+20,track_aera_y+415),Vec2D(60,25));
EditFine.SetRoundness(7.5);
EditFine.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_MOVER && mouse_x>track_aera_x+20 && mouse_x< track_aera_x+80 && mouse_y>track_aera_y+415 && mouse_y<track_aera_y+440)
{
 EditFine.Draw(CouleurSurvol);
 if(mouse_button==1 && mouse_released==0  && index_mouse_is_tracking==0 && tracker_mode==1)
 {
tracker_16b_edit=toggle(tracker_16b_edit);mouse_released=1;
 }
}
if (tracker_16b_edit==1)
{EditFine.Draw(CouleurFader);}
petitchiffre.Print("Edit 16b",x_track+45, y_track+450);
EditFine.DrawOutline(Rgba::WHITE);

// LOCK X ou Y
Rect LockX(Vec2D(track_aera_x+20,track_aera_y+460),Vec2D(60,25));
LockX.SetRoundness(7.5);
LockX.SetLineWidth(epaisseur_ligne_fader);
Rect LockY(Vec2D(track_aera_x+100,track_aera_y+460),Vec2D(60,25));
LockY.SetRoundness(7.5);
LockY.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_MOVER && mouse_y>track_aera_y+460 && mouse_y<track_aera_y+485)
{
if(mouse_x>track_aera_x+20 && mouse_x<track_aera_x+80)
{
if(mouse_button==1 && mouse_released==0 && index_mouse_is_tracking==0 )
{
lockX_on=toggle(lockX_on);mouse_released=1;
}
}
if(mouse_x>track_aera_x+100 && mouse_x<track_aera_x+160)
{
if(mouse_button==1 && mouse_released==0 && index_mouse_is_tracking==0 )
{
lockY_on=toggle(lockY_on);mouse_released=1;
}
}
}
if(lockX_on==1){LockX.Draw(CouleurFader); }
if(lockY_on==1){LockY.Draw(CouleurFader); }
petitchiffre.Print("lock X",x_track+50, y_track+495);
petitchiffre.Print("lock Y",x_track+130, y_track+495);
LockX.DrawOutline(Rgba::WHITE);
LockY.DrawOutline(Rgba::WHITE);

///////////// A AFFECTER AU DEVICE ///////////////////

// INVERSE X Y DATA
Rect InvX(Vec2D(track_aera_x+20,track_aera_y+500),Vec2D(60,25));
InvX.SetRoundness(7.5);
InvX.SetLineWidth(epaisseur_ligne_fader);
Rect InvY(Vec2D(track_aera_x+100,track_aera_y+500),Vec2D(60,25));
InvY.SetRoundness(7.5);
InvY.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_MOVER && mouse_y>track_aera_y+500 && mouse_y<track_aera_y+525)
{
if(mouse_x>track_aera_x+20 && mouse_x<track_aera_x+80)
{
if(mouse_button==1 && mouse_released==0 && index_mouse_is_tracking==0 )
{
invX_on=toggle(invX_on);mouse_released=1;
}
}
if(mouse_x>track_aera_x+100 && mouse_x<track_aera_x+160)
{
if(mouse_button==1 && mouse_released==0 && index_mouse_is_tracking==0 )
{
invY_on=toggle(invY_on);mouse_released=1;
}
}
}


if(invX_on==1){InvX.Draw(CouleurFader); }
if(invY_on==1){InvY.Draw(CouleurFader); }

petitchiffre.Print("Inv X",x_track+50, y_track+535);
petitchiffre.Print("Inv Y",x_track+130, y_track+535);
InvX.DrawOutline(Rgba::WHITE);
InvY.DrawOutline(Rgba::WHITE);


// OFFSET position_defaut[2]
Rect ZeroPoint(Vec2D(x_track+40,y_track+566),Vec2D(140,25));
ZeroPoint.SetRoundness(7.5);
ZeroPoint.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_MOVER && mouse_x>x_track+40 && mouse_x<x_track+180 && mouse_y>y_track+566 && mouse_y<y_track+591)
{
if(mouse_button==1  && index_do_dock==1 &&  mouse_released==0 && index_mouse_is_tracking==0 )
{
position_defaut[0]=mover_params[0][0]-127;
position_defaut[1]=mover_params[1][0]-127;
sprintf(string_zero_point_is,"Offset X %d Y %d",position_defaut[0],position_defaut[1]);
mouse_released=1;
}
}

ZeroPoint.DrawOutline(Rgba::WHITE);
petitchiffre.Print("Set Offset",x_track+80, y_track+580);
petitchiffre.Print(string_zero_point_is,x_track+60, y_track+610);


 return(0);
}

/////////////////////////////////////////////////////////////////////////////////

int Move_do_crossfade(int move_selected)//crossfades
{

 if (index_move_crossfade_is_on==1)
 {
 move_elapsed_time=move_current_time-move_start_value;
 if(move_current_time<move_end_value)
 {
 //8bits
 if(tracker_mode==0)
 {
 if(index_spline==0)
 {
 //égalités
 if(x_val_at_beg[move_selected]==x_val_at_end[move_selected])
 {
 mover_params[0][0]=(int)x_val_at_end[move_selected];
 }
 if(y_val_at_beg[move_selected]==y_val_at_end[move_selected])
 {
 mover_params[1][0]=(int)y_val_at_end[move_selected];
 }
 //beg > end
 if(x_val_at_beg[move_selected]>x_val_at_end[move_selected])
 {
 mover_params[0][0]=(int)(x_val_at_beg[move_selected]-(x_fract[move_selected]*move_elapsed_time));
 }
 if(y_val_at_beg[move_selected]>y_val_at_end[move_selected])
 {
 mover_params[1][0]=(int)(y_val_at_beg[move_selected]-(y_fract[move_selected]*move_elapsed_time));
 }
 //beg<end
 if(x_val_at_beg[move_selected]<x_val_at_end[move_selected])
 {
 mover_params[0][0]=(int)(x_val_at_beg[move_selected]+(x_fract[move_selected]*move_elapsed_time));
 }
 if(y_val_at_beg[move_selected]<y_val_at_end[move_selected])
 {
 mover_params[1][0]=(int)(y_val_at_beg[move_selected]+(y_fract[move_selected]*move_elapsed_time));
 }
 }
 else if(index_spline==1)
 {
 mover_params[0][0]=my_spline_path_X[(int)(actual_spline_tick)]-(xmover_window+20);
 mover_params[1][0]=my_spline_path_Y[(int)(actual_spline_tick)]-(ymover_window+20);
 if(mover_params[0][0]<0){mover_params[0][0]=0;}
 else if(mover_params[0][0]>255){mover_params[0][0]=255;}
 if(mover_params[1][0]<0){mover_params[1][0]=0;}
 else if(mover_params[1][0]>255){mover_params[1][0]=255;}
 }
 }//8 bits end

 //16 BITS
 if(tracker_mode==1)
 {
 if(index_spline==0)
 {
 //égalités
 if(x_val_at_beg[move_selected]==x_val_at_end[move_selected])
 {
 mover_params[0][0]=((int)x_val_at_end[move_selected])>>8;
 mover_params[0][1]=((int)x_val_at_end[move_selected])& 0X00FF;
 }
 if(y_val_at_beg[move_selected]==y_val_at_end[move_selected])
 {
 mover_params[1][0]=((int)y_val_at_end[move_selected])>>8;
 mover_params[1][1]=(((int)y_val_at_end[move_selected]))& 0X00FF;
 }
 //beg > end
 if(x_val_at_beg[move_selected]>x_val_at_end[move_selected])
 {
 mover_params[0][0]=((int)(x_val_at_beg[move_selected]-(x_fract[move_selected]*move_elapsed_time)))>>8 ;
 mover_params[0][1]=((int)(x_val_at_beg[move_selected]-(x_fract[move_selected]*move_elapsed_time)))& 0X00FF;
 }
 if(y_val_at_beg[move_selected]>y_val_at_end[move_selected])
 {
 mover_params[1][0]=((int)(y_val_at_beg[move_selected]-(y_fract[move_selected]*move_elapsed_time)))>>8;
 mover_params[1][1]=((int)(y_val_at_beg[move_selected]-(y_fract[move_selected]*move_elapsed_time)))& 0X00FF;
 }
 //beg<end
 if(x_val_at_beg[move_selected]<x_val_at_end[move_selected])
 {
 mover_params[0][0]=((int)(x_val_at_beg[move_selected]+(x_fract[move_selected]*move_elapsed_time)))>>8;
 mover_params[0][1]=((int)(x_val_at_beg[move_selected]+(x_fract[move_selected]*move_elapsed_time)))& 0X00FF;
 }
 if(y_val_at_beg[move_selected]<y_val_at_end[move_selected])
 {
 mover_params[1][0]=((int)(y_val_at_beg[move_selected]+(y_fract[move_selected]*move_elapsed_time)))>>8;
 mover_params[1][1]=((int)(y_val_at_beg[move_selected]+(y_fract[move_selected]*move_elapsed_time)))& 0X00FF;
 }
 }
 else if(index_spline==1)
 {
 mover_params[0][0]=my_spline_path_X[(int)(actual_spline_tick)]-(xmover_window+20);
 mover_params[1][0]=my_spline_path_Y[(int)(actual_spline_tick)]-(ymover_window+20);
 if(mover_params[0][0]<0){mover_params[0][0]=0;}
 else if(mover_params[0][0]>255){mover_params[0][0]=255;}
 if(mover_params[1][0]<0){mover_params[1][0]=0;}
 else if(mover_params[1][0]>255){mover_params[1][0]=255;}
 }
 }//16 bits end




 //la suite des datas normaux
 //egalités
  if(iris_at_beg[move_selected]==iris_at_end[move_selected])
 {
 mover_params[2][0]=(int)iris_at_end[move_selected];
 }
 if(focus_at_beg[move_selected]==focus_at_end[move_selected])
 {
 mover_params[3][0]=(int)focus_at_end[move_selected];
 }
 if(zoom_at_beg[move_selected]==zoom_at_end[move_selected])
 {
 mover_params[4][0]=(int)zoom_at_end[move_selected];
 }
 //beg>end
   if(iris_at_beg[move_selected]>iris_at_end[move_selected])
 {
 mover_params[2][0]=(int)(iris_at_beg[move_selected]-(iris_fract[move_selected]*move_elapsed_time));
 }
  if(focus_at_beg[move_selected]>focus_at_end[move_selected])
 {
 mover_params[3][0]=(int)(focus_at_beg[move_selected]-(focus_fract[move_selected]*move_elapsed_time));
 }
  if(zoom_at_beg[move_selected]>zoom_at_end[move_selected])
 {
 mover_params[4][0]=(int)(zoom_at_beg[move_selected]-(zoom_fract[move_selected]*move_elapsed_time));
 }
 //beg<end
 if(iris_at_beg[move_selected]<iris_at_end[move_selected])
 {
 mover_params[2][0]=(int)(iris_at_beg[move_selected]+(iris_fract[move_selected]*move_elapsed_time));
 }
  if(focus_at_beg[move_selected]<focus_at_end[move_selected])
 {
 mover_params[3][0]=(int)(focus_at_beg[move_selected]+(focus_fract[move_selected]*move_elapsed_time));
 }
  if(zoom_at_beg[move_selected]<zoom_at_end[move_selected])
 {
 mover_params[4][0]=(int)(zoom_at_beg[move_selected]+(zoom_fract[move_selected]*move_elapsed_time));
 }
 }

 //Depassement des ticks et fin crossfade
 if(move_current_time>move_end_value)
 {
 if(GotoMoves[move_selected][dock_move_actual_step[move_selected]]!=0 && index_move_back==0)
 {
 dock_move_selected=GotoMoves[move_selected][dock_move_actual_step[move_selected]];
 move_selected=dock_move_selected;
 dock_move_actual_step[move_selected]=Moves_Inpoint[move_selected]-1;
 if(dock_move_actual_step[move_selected]<0){dock_move_actual_step[move_selected]=dock_moves_contains_steps[move_selected];}
 }
if(tracker_mode==0)//not spline
 {
  mover_params[0][0]=(int)x_val_at_end[move_selected];
  if (mover_params[0][0]<0) {mover_params[0][0]=0;}
  else if (mover_params[0][0] >255){mover_params[0][0]=255;}
  mover_params[1][0]=(int) y_val_at_end[move_selected];
  if (mover_params[1][0]<0) {mover_params[1][0]=0;}
  else if (mover_params[1][0] >255){mover_params[1][0]=255;}
  if (mover_params[2][0]<0) {mover_params[2][0]=0;}
  else if (mover_params[2][0] >255){mover_params[2][0]=255;}
   if (mover_params[3][0]<0) {mover_params[3][0]=0;}
  else if (mover_params[3][0] >255){mover_params[3][0]=255;}
  if (mover_params[4][0]<0) {mover_params[4][0]=0;}
  else if (mover_params[4][0] >255){mover_params[4][0]=255;}
 }
else if(tracker_mode==1)//spline
{
  mover_params[0][0]=((int)x_val_at_end[move_selected])>>8 ;

  if (mover_params[0][0]<0) {mover_params[0][0]=0;}
  else if (mover_params[0][0] >255){mover_params[0][0]=255;}

  mover_params[1][0]=((int) y_val_at_end[move_selected])>>8;

  if (mover_params[1][0]<0) {mover_params[1][0]=0;}
  else if (mover_params[1][0] >255){mover_params[1][0]=255;}

  mover_params[0][1]=((int)x_val_at_end[move_selected])& 0X00FF;
  mover_params[1][1]=((int)y_val_at_end[move_selected])& 0X00FF;
  if (mover_params[2][0]<0) {mover_params[2][0]=0;}
  else if (mover_params[2][0] >255){mover_params[2][0]=255;}
   if (mover_params[3][0]<0) {mover_params[3][0]=0;}
  else if (mover_params[3][0] >255){mover_params[3][0]=255;}
   if (mover_params[4][0]<0) {mover_params[4][0]=0;}
  else if (mover_params[4][0] >255){mover_params[4][0]=255;}
}

 //rafraichissement du pas
  if(index_move_forward==1)
  {
  Move_StepForward(dock_move_selected);
  }
  else if(index_move_back==1)
  {
  Move_StepBackward(dock_move_selected);
  }
 //continuation du mouvement ou pas
  if(index_cycle==0)
  {
  index_move_crossfade_is_on=0;
  if(index_move_forward==1)
  {index_move_forward=0; }
  else if(index_move_back==1)
  {index_move_back=0;}
  }
  if(index_cycle==1)
  {
  prepare_move_values(dock_move_selected);

  }


 }

 }

 return(0);
}


int ventilation_niveaux_mover()
{
 inversion_of_axes();//X et Y

buffer_moving_head[irisadress]=mover_params[2][0];
buffer_moving_head[focusadress]=mover_params[3][0];
buffer_moving_head[zoomadress]=mover_params[4][0];



 return(0);
}

