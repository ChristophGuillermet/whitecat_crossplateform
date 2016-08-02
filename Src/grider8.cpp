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

* \file grider8.cpp
* \brief {GUI fonctions for grid players}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour gérer la fenêtre des grid players
*
*   GUI fonctions to manage windows of the gridplayers
*
 **/

int TheStepBox(int xb,int yb, int num_grid_player)
{

//STEP IS
previous_button_view(xb,yb,0);
Rect StepB(Vec2D(xb+22,yb-5),Vec2D(35,30));
StepB.SetRoundness(4);
StepB.DrawOutline(CouleurLigne.WithAlpha(0.4));
Rect Step127(Vec2D(xb+60,yb-6),Vec2D(20,5));
Step127.SetRoundness(1.0);
Step127.DrawOutline(CouleurLigne.WithAlpha(0.4));
minichiffre.Print(ol::ToString(grid_midi_multiple_for_step_call[num_grid_player]),xb+82,yb);

next_button_view(xb+60,yb,0);
if(window_focus_id==926 )
{
 //Step minus
//sab 0203/2014 IMPACT : if(window_focus_id==W_GRID &&  mouse_x>xb & mouse_x<xb+20 && mouse_y>yb && mouse_y<yb+20 )
if(window_focus_id==W_GRID &&  mouse_x>xb && mouse_x<xb+20 && mouse_y>yb && mouse_y<yb+20 )
{
 if(Midi_Faders_Affectation_Type!=0)
{
char sttmp[24];
sprintf(sttmp,"StepMinus in GridPl.%d",num_grid_player+1);
show_type_midi(1484+num_grid_player,sttmp );
Rect StepMinus(Vec2D(xb,yb),Vec2D(20,20));
StepMinus.SetRoundness(4);
StepMinus.DrawOutline(CouleurBlind);
}
if(mouse_b&1 )
{
  previous_button_view(xb,yb,1);
}
}
//Step plus
//sab 0203/2014 IMPACT : if(window_focus_id==W_GRID && mouse_x>xb+60 & mouse_x<xb+80 && mouse_y>yb && mouse_y<yb+20 )
if(window_focus_id==W_GRID && mouse_x>xb+60 && mouse_x<xb+80 && mouse_y>yb && mouse_y<yb+20 )
{
if(Midi_Faders_Affectation_Type!=0)
{
char sttmp[24];
sprintf(sttmp,"StepPlus in GridPl.%d",num_grid_player+1);
show_type_midi(1488+num_grid_player,sttmp );
Rect StepPlus(Vec2D(xb+60,yb),Vec2D(20,20));
StepPlus.SetRoundness(4);
StepPlus.DrawOutline(CouleurBlind);
}
if(mouse_b&1 )
{
  next_button_view(xb+60,yb,1);
}
}

//set +127 box pour les pas
if(window_focus_id==W_GRID && mouse_x>xb+60 && mouse_x<xb+80 && mouse_y>yb-6 && mouse_y<yb-1)
{
Step127.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0)
 {
 Step127.DrawOutline(CouleurBlind);
 char sttmp[24];
 sprintf(sttmp,"CallStep x7 GridPl.%d",num_grid_player+1);
 show_type_midi(1536+num_grid_player,sttmp );
 }
}
//chargement d'un pas, ou affectation d'un temps ou clear  du pas
//sab 0203/2014 IMPACT : if(window_focus_id==W_GRID && mouse_x>xb+22 & mouse_x<xb+57 && mouse_y>yb-5 && mouse_y<yb-25 )
if(window_focus_id==W_GRID && mouse_x>xb+22 && mouse_x<xb+57 && mouse_y>yb-5 && mouse_y<yb-25 )
{
StepB.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0)
 {
 StepB.DrawOutline(CouleurBlind);
 char sttmp[24];
 sprintf(sttmp,"CallStep x1 GridPl.%d",num_grid_player+1);
 show_type_midi(1532+num_grid_player,sttmp );
 }
}
}
petitchiffre.Print(ol::ToString(index_grider_step_is[num_grid_player]+1),xb+27,yb+14);

 return(0);
}


int TheGrid_commands ( int xb, int yb, int num_grid_player)
{

//affichage progression transfert
 Rect BackSt(Vec2D(xb,yb-5),Vec2D(63,10));
 Rect BackPreset(Vec2D(xb,yb+10),Vec2D(63,10));
 BackSt.DrawOutline(CouleurLigne.WithAlpha(0.2));
 BackPreset.DrawOutline(CouleurLigne.WithAlpha(0.2));
 Rect ActStage(Vec2D(xb,yb-5),Vec2D(grid_niveauX1[num_grid_player]/4,10));
 ActStage.Draw(CouleurNiveau.WithAlpha(0.7));
 ActStage.Draw(CouleurLigne.WithAlpha(0.5));
 Rect ActPreset(Vec2D(xb,yb+10),Vec2D(grid_niveauX2[num_grid_player]/4,10));
 ActPreset.Draw(CouleurSurvol);
 ActPreset.Draw(CouleurLigne.WithAlpha(0.5));
if(grider_is_playing[num_grid_player]==1)
{
if(actual_time<(grid_crossfade_start_time[num_grid_player]+grid_delay_out[num_grid_player]))
{
BackSt.Draw(CouleurBlind.WithAlpha(alpha_blinker));
}
if(actual_time<(grid_crossfade_start_time[num_grid_player]+grid_delay_in[num_grid_player]))
{
BackPreset.Draw(CouleurBlind.WithAlpha(alpha_blinker));
}
}
 //accélérometer du player
 Rect AcelGrid(Vec2D(xb,yb+30),Vec2D(127,10));
 AcelGrid.DrawOutline(CouleurLigne.WithAlpha(0.5));
 Rect AccelB(Vec2D(xb+grid_crossfade_speed[num_grid_player]-5,yb+30),Vec2D(10,10));
 AccelB.SetRoundness(2.0);
 AccelB.Draw(CouleurFader);
 Line(Vec2D(xb+64,yb+25),Vec2D(xb+64,yb+45)).DrawOutline(CouleurLigne);
 minichiffre.Print(ol::ToString(grid_crossfade_speed[num_grid_player]),xb+130,yb+35);
if(window_focus_id==W_GRID)
{
 if(mouse_x>xb-5 && mouse_x<xb+127+5 && mouse_y>=yb+30 && mouse_y<=yb+40 )
 {
  AcelGrid.DrawOutline(CouleurLigne);
 if( Midi_Faders_Affectation_Type!=0)
 {
char sttmp[24];
sprintf(sttmp,"Speed GridPl.%d",num_grid_player+1);
show_type_midi(1508+num_grid_player,sttmp );
AcelGrid.DrawOutline(CouleurBlind);
 }
 }
}
 petitpetitchiffre.Print(string_time_in_grider[num_grid_player],xb+70,yb+1);
 petitpetitchiffrerouge.Print(string_time_in_grider_next_step[num_grid_player],xb+70,yb+12);
//next step
 petitpetitchiffrerouge.Print(string_next_step_to[num_grid_player],xb+70,yb+25);

 ////////////////SLAVE MODE////////////////////////////////////////////////////

 Rect SlaveB(Vec2D(xb+150,yb+25),Vec2D(40,15));
 SlaveB.SetRoundness(0.5);

if(window_focus_id==W_GRID )
{
if(mouse_x>xb+150 && mouse_x<xb+150+40 && mouse_y>yb+25 && mouse_y<yb+40)
{
 SlaveB.DrawOutline(CouleurLigne);
 if( Midi_Faders_Affectation_Type!=0)
 {
char sttmp[24];
sprintf(sttmp,"Slave in GridPl.%d",num_grid_player+1);
show_type_midi(1504+num_grid_player,sttmp );
SlaveB.DrawOutline(CouleurBlind);
 }
}
}

 SlaveB.Draw(CouleurFader.WithAlpha(grid_player_slave[num_grid_player]));
 SlaveB.DrawOutline(CouleurLigne.WithAlpha(0.2));
 petitpetitchiffre.Print("Slave",xb+155,yb+35);

 /////////////////MODES ET DEFINE AU STEP
 Rect CadreStep(Vec2D(xb+15,yb+50),Vec2D(180,100));
 CadreStep.SetRoundness(5.0);
 CadreStep.Draw(CouleurLigne.WithAlpha(0.1));

 petitpetitchiffre.Print("Step Macros",xb+20, yb+60);
 petitpetitchiffre.Print("Grid",xb+110,yb+60);
 petitpetitchiffre.Print("Step",xb+155,yb+60);
 Rect GridGotoB(Vec2D(xb+105,yb+70),Vec2D(30,15));
 GridGotoB.SetRoundness(0.5);
 GridGotoB.DrawOutline(CouleurLigne.WithAlpha(0.2));

 Rect StepGotoB(Vec2D(xb+150,yb+70),Vec2D(40,15));
 StepGotoB.SetRoundness(0.5);
 StepGotoB.DrawOutline(CouleurLigne.WithAlpha(0.2));

 Rect CountB(Vec2D(xb+150,yb+90),Vec2D(40,15));
 CountB.SetRoundness(0.5);
 CountB.DrawOutline(CouleurLigne.WithAlpha(0.2));

 Rect StepSeekB(Vec2D(xb+150,yb+110),Vec2D(40,15));
 StepSeekB.SetRoundness(0.5);
 StepSeekB.DrawOutline(CouleurLigne.WithAlpha(0.2));

 Rect StopPlayB(Vec2D(xb+100,yb+130),Vec2D(90,15));
 StopPlayB.SetRoundness(0.5);

 char sttmp[24];

 for(int sp=0;sp<4;sp++)
 {
 Rect OnOffSp(Vec2D(xb,yb+70+(sp*20)),Vec2D(10,10));
 OnOffSp.SetRoundness(0.2);
 switch(sp)
 {
 case 0:
 OnOffSp.Draw(CouleurBlind.WithAlpha(grider_goto_mode[num_grid_player]));
 petitpetitchiffre.Print("GoTo",xb+20, yb+80+(sp*20));
 sprintf(sttmp,"GotoMode GridPl.%d",num_grid_player+1);
 petitpetitchiffre.Print(ol::ToString(grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][0]+1),xb+110,yb+80+(sp*20));
 petitpetitchiffre.Print(ol::ToString(grid_goto[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]][1]+1),xb+155,yb+80+(sp*20));
 break;
 case 1:
 OnOffSp.Draw(CouleurBlind.WithAlpha(grider_count_mode[num_grid_player]));
 petitpetitchiffre.Print("Count",xb+20, yb+80+(sp*20));
 sprintf(sttmp,"CountMode GridPl.%d",num_grid_player+1);
 petitpetitchiffre.Print(string_grid_count[num_grid_player],xb+55, yb+80+(sp*20));
 petitpetitchiffre.Print(ol::ToString(grid_count[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]),xb+155,yb+80+(sp*20));
 break;
 case 2:
 OnOffSp.Draw(CouleurBlind.WithAlpha(grider_seekto_mode[num_grid_player]));
 petitpetitchiffre.Print("SeekStep",xb+20, yb+80+(sp*20));
 sprintf(sttmp,"SeekStepMode GridPl.%d",num_grid_player+1);
 petitpetitchiffre.Print(ol::ToString(grid_seekpos[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]+1),xb+155,yb+80+(sp*20));
 break;
 case 3:
 OnOffSp.Draw(CouleurBlind.WithAlpha(grider_stoplay_mode[num_grid_player]));
 petitpetitchiffre.Print("StopPlay",xb+20, yb+80+(sp*20));
 sprintf(sttmp,"StopPlayMode GridPl.%d",num_grid_player+1);
 StopPlayB.Draw(CouleurBlind.WithAlpha(grid_stoplay[index_grider_selected[num_grid_player]][index_grider_step_is[num_grid_player]]));
 StopPlayB.DrawOutline(CouleurLigne.WithAlpha(0.5));
 break;
 default:
 break;
 }

 OnOffSp.DrawOutline(CouleurLigne.WithAlpha(0.5));

 if((window_focus_id==W_GRID || (num_grid_player==0 && window_focus_id==909)) && mouse_x>xb && mouse_x<xb+10 && mouse_y>yb+70+(sp*20) && mouse_y<yb+80+(sp*20))
 {
 if( Midi_Faders_Affectation_Type!=0)
 {
 show_type_midi(1512+(sp*4)+num_grid_player,sttmp );
 OnOffSp.SetLineWidth(2.0);
 OnOffSp.DrawOutline(CouleurBlind);
 }

 }

 }

 //Goto Grid num
if(window_focus_id==W_GRID  && index_enable_edit_Grider==1)
{
if( mouse_x>xb+105 && mouse_x<xb+135 && mouse_y>yb+70 && mouse_y<yb+85 )
 {
 GridGotoB.DrawOutline(CouleurLigne);
 }
 //Goto step num
if( mouse_x>xb+150 && mouse_x<xb+190 && mouse_y>yb+70 && mouse_y<yb+85 )
 {
 StepGotoB.DrawOutline(CouleurLigne);
 }
 //Count num
if( mouse_x>xb+150 && mouse_x<xb+190 && mouse_y>yb+90 && mouse_y<yb+105  )
 {
 CountB.DrawOutline(CouleurLigne);
 }
 //Seek step num
if( mouse_x>xb+150 && mouse_x<xb+190 && mouse_y>yb+110 && mouse_y<yb+125  )
 {
 StepSeekB.DrawOutline(CouleurLigne);
 }
if(mouse_x>xb+100 && mouse_x<xb+190 && mouse_y>yb+130 && mouse_y<yb+145 )
{
StopPlayB.DrawOutline(CouleurLigne);
}
}
return(0);
}

int TheGrid_divers( int xb, int yb, int num_grid_player)
{
 Rect AffectToDocB(Vec2D(xb+60,yb),Vec2D(50,30));
 AffectToDocB.SetRoundness(5);
 AffectToDocB.SetLineWidth(tiers_epaisseur_ligne_fader);
 if(num_grid_player==gridplayer_to_affect_is)
 { AffectToDocB.Draw(CouleurFader);}
 AffectToDocB.DrawOutline(CouleurLigne.WithAlpha(0.3));

 petitpetitchiffre.Print("Affect",xb+65,yb+12);
 petitpetitchiffre.Print("ToDock",xb+65,yb+22);


  ////////EDITING MODE/////////////////////////

 Rect ToStepMB(Vec2D(xb,yb+45),Vec2D(10,10));
 ToStepMB.Draw(CouleurBlind.WithAlpha(alpha_blinker*to_step_editing_mode[num_grid_player]));
 ToStepMB.DrawOutline(CouleurLigne.WithAlpha(0.5));
 petitpetitchiffre.Print("ToStep",xb+15,yb+48);
 petitpetitchiffre.Print(" Mode",xb+15,yb+58);
 minichiffre.Print("Step",xb+65,yb+40);
 Rect StepToB(Vec2D(xb+60,yb+45),Vec2D(40,15));
 StepToB.SetRoundness(0.5);
 StepToB.DrawOutline(CouleurLigne.WithAlpha(0.2));
 petitpetitchiffre.Print(ol::ToString(index_StepTo[num_grid_player]+1),xb+65,yb+55);


 ///////////COPY TO ////////////////////////////////////////////////////////////
 Line(Vec2D(xb,yb+68),Vec2D(xb+110,yb+68)).Draw(CouleurLigne.WithAlpha(0.5));



 Rect CopyB(Vec2D(xb,yb+75),Vec2D(50,15));
 CopyB.SetRoundness(4.0);
 CopyB.Draw(CouleurSurvol.WithAlpha(0.5));

 petitpetitchiffre.Print("CopyTo",xb+5,yb+85);

 Rect InsB(Vec2D(xb+55,yb+75),Vec2D(50,15));
 InsB.SetRoundness(4.0);
 InsB.Draw(CouleurSurvol.WithAlpha(0.5));
 petitpetitchiffre.Print("Insert",xb+60,yb+85);


 Rect GridCopyB(Vec2D(xb,yb+95),Vec2D(30,15));
 GridCopyB.SetRoundness(0.5);
 GridCopyB.DrawOutline(CouleurLigne.WithAlpha(0.2));

 Rect StepCopyB(Vec2D(xb+45,yb+95),Vec2D(40,15));
 StepCopyB.SetRoundness(0.5);
 StepCopyB.DrawOutline(CouleurLigne.WithAlpha(0.2));

 petitpetitchiffre.Print(ol::ToString( index_Grid_copyto[num_grid_player][0]+1),xb+5,yb+105);
 petitpetitchiffre.Print(ol::ToString( index_Grid_copyto[num_grid_player][1]+1),xb+50,yb+105);





 if(window_focus_id==W_GRID && index_enable_edit_Grider==1 )
 {
 //to step mode
 if( mouse_x>xb && mouse_x<xb+100 && mouse_y>yb+45 && mouse_y<yb+55)
 {
 ToStepMB.DrawOutline(CouleurLigne);
 }
 //tostep
 if( mouse_x>xb+60 && mouse_x<xb+100 && mouse_y>yb+45 && mouse_y<yb+60)
 {
 StepToB.DrawOutline(CouleurLigne);
 }
 //copy mode
 if(mouse_x>xb && mouse_x<xb+50 && mouse_y>yb+75 && mouse_y<yb+90 )
 {
  CopyB.DrawOutline(CouleurFader);
 }
 //insert mode
 if(mouse_x>xb+55 && mouse_x<xb+105 && mouse_y>yb+75 && mouse_y<yb+90 )
 {
  InsB.DrawOutline(CouleurFader);
 }
 //grid   entry
 if(mouse_x>xb && mouse_x<xb+30 && mouse_y>yb+95 && mouse_y<yb+105 )
 {
 GridCopyB.DrawOutline(CouleurLigne);
 }
 //step entry
 if(mouse_x>xb+45 && mouse_x<xb+85 && mouse_y>yb+95 && mouse_y<yb+105 )
 {
 StepCopyB.DrawOutline(CouleurLigne);
 }
 }
  char sttmp[24];

if(num_grid_player==0 )
{
Rect BoxLink(Vec2D(xb, yb+115),Vec2D(105,15));
BoxLink.Draw(CouleurFader.WithAlpha(index_link_speed_crossfade_to_gpl1));
BoxLink.DrawOutline(CouleurLigne.WithAlpha(0.5));
petitchiffre.Print("Speed is CueList",xb+2,yb+125);
if(window_focus_id==W_GRID && mouse_x>xb && mouse_x<xb+105 && mouse_y>yb+115 && mouse_y<yb+130)
 {
 if( Midi_Faders_Affectation_Type!=0)
 {

 sprintf(sttmp,"Speed is CueList GPl.1");
 show_type_midi(1540,sttmp );
 BoxLink.DrawOutline(CouleurBlind);
 }

 }
}

Rect GetDraw(Vec2D(xb, yb+135),Vec2D(105,15));
GetDraw.DrawOutline(CouleurLigne.WithAlpha(0.5));
petitchiffre.Print("Snap Fader",xb+7,yb+145);
neuromoyen.Print(ol::ToString(GplSnapFader[num_grid_player]+1),xb+80,yb+146);


 if(window_focus_id==W_GRID && index_enable_edit_Grider==1 )
 {
 //to step mode
 if( mouse_x>xb && mouse_x<xb+105 && mouse_y>yb+135 && mouse_y<yb+150)
 {
 GetDraw.DrawOutline(CouleurLigne);
 }
 }
return(0);
}



int TheGrid_matrix ( int xb, int yb,int num_grid_player)
{
int grid_selected=index_grider_selected[num_grid_player];
int gr_st_selected=index_grider_step_is[num_grid_player];

for (int co=0;co<=grider_nb_col;co++)
{
Line(Vec2D(xb+(co*15),yb),Vec2D(xb+(co*15),yb+(grider_nb_row*15))).Draw(CouleurLigne.WithAlpha(0.5));
}

for(int lo=0;lo<=grider_nb_row;lo++)
{
Line(Vec2D(xb,yb+(lo*15)),Vec2D(xb+(grider_nb_col*15),yb+(lo*15))).Draw(CouleurLigne.WithAlpha(0.5));
}

int tmpx=0;
int tmpy=0;
int tempfu=0;
//sab 02/03/2014 unused var int templo=0;
for(int fu=0;fu<grider_nb_col;fu++)
{
for(int lo=0;lo<grider_nb_row;lo++)
{
tmpx=xb+(fu*15);
tmpy=yb+(lo*15);
tempfu=(fu+(lo*grider_nb_col));
Rect QuadCh(Vec2D(tmpx,tmpy),Vec2D(15,15));
if(grid_levels[grid_selected][gr_st_selected][(fu+(lo*grider_nb_col))]==255)
{
QuadCh.Draw(CouleurFader);
}
else if(grid_levels[grid_selected][gr_st_selected][tempfu]>0 && grid_levels[grid_selected][gr_st_selected][tempfu]<255)
{
QuadCh.Draw(CouleurGreen.WithAlpha(3*(1.0/255.0)*(grid_levels[grid_selected][gr_st_selected][tempfu])));
}
//step précedent, info
if(grid_levels[grid_selected][gr_st_selected-1][tempfu]>0)
{
Rect QuadPrev(Vec2D(tmpx,tmpy),Vec2D(5,5));
QuadPrev.Draw(CouleurSurvol);
}
if(grid_levels[grid_in_preset[num_grid_player][0]][grid_in_preset[num_grid_player][1]][tempfu]>0)
{
Rect QuadNext(Vec2D(tmpx+10,tmpy),Vec2D(5,5));
QuadNext.Draw(CouleurLigne);
}
}
}

Rect ShowOffset(Vec2D(0,0),Vec2D(15,15));
for(int pr=0;pr<6;pr++)
{
 if( draw_brush_type[pr]==1 && draw_get_gpl[pr]==num_grid_player+1)//si GPL tracké depuis DRAW
 {
 ShowOffset.MoveTo(Vec2D(xb+ (((draw_offset_gpl[pr]-1)%grider_nb_col)*15) , yb+ (((draw_offset_gpl[pr]-1)/grider_nb_col)*15)   ));
 ShowOffset.SetLineWidth(2.0);
 ShowOffset.DrawOutline(CouleurLevel);
 minichiffre.Print(ol::ToString(pr+1), xb+ (((draw_offset_gpl[pr]-1)%grider_nb_col)*15) , yb+ (((draw_offset_gpl[pr]-1)/grider_nb_col)*15)+7);
 }
}

if(window_focus_id==W_GRID )
{
if(mouse_x>=xb && mouse_x<=xb+(grider_nb_col*15) && mouse_y>=yb && mouse_y<=yb+(grider_nb_row*15))
{
int unite=((mouse_x-xb)/15)+1;
int dizaine=((mouse_y-yb)/15);

position_grid_editing=(dizaine*grider_nb_col)+unite-1;
temoin_over_grid_channel=position_grid_editing+grider_begin_channel_is;
Rect Backchiffres(Vec2D(mouse_x-5, mouse_y-25),Vec2D(40,25));
Backchiffres.SetRoundness(5);
Backchiffres.Draw(CouleurFond.WithAlpha(0.4));
//affichage circuit + valeur
petitchiffre.Print(ol::ToString(temoin_over_grid_channel),mouse_x,mouse_y-15);
if(grid_levels[grid_selected][gr_st_selected][temoin_over_grid_channel-1]>0)
{
char tmp_st[36];
switch(dmx_view)
{
case 0:
//petitpetitchiffre.Print(ol::ToString((int)(((float)grid_levels[grid_selected][gr_st_selected][temoin_over_grid_channel-1])/2.55)),mouse_x+10,mouse_y-5);
sprintf(tmp_st,"OverChan: %d Level: %d",temoin_over_grid_channel,(int)(((float)grid_levels[grid_selected][gr_st_selected][temoin_over_grid_channel-1])/2.55));
break;
case 1:
//petitpetitchiffre.Print(ol::ToString(grid_levels[grid_selected][gr_st_selected][temoin_over_grid_channel-1]),mouse_x+10,mouse_y-5);
sprintf(tmp_st,"OverChan: %d Level: %d",temoin_over_grid_channel,grid_levels[grid_selected][gr_st_selected][temoin_over_grid_channel-1]);
break;
default: break;
}
neuromoyen.Print(tmp_st,mouse_x+10,mouse_y-5);
}

}
}

return(0);
}


int ThePlayCommands(int xb, int yb, int num_grider)
{
 play_button_view(xb+10,yb,grider_is_playing[num_grider]);
 seek_button_view(xb+40,yb,0);
 minichiffre.Print(ol::ToString(index_grider_seek_pos[num_grider]+1),xb+65,yb);
 playstop_button_view(xb+70,yb,grider_autostopmode[num_grider]);

 if(window_focus_id==W_GRID && mouse_y>yb && mouse_y<yb+20 )
 {
 if(mouse_x>xb+10 && mouse_x<xb+30 )// PLAY GRID
 {
 char sttmp[24];
 sprintf(sttmp,"Play GridPl.%d",num_grider+1);
 show_type_midi(1492+num_grider,sttmp );

 }
 else if(mouse_x>xb+40 && mouse_x<xb+60 )//SEEK GRID
 {
  char sttmp[24];
 sprintf(sttmp,"Seek GridPl.%d",num_grider+1);
 show_type_midi(1496+num_grider,sttmp );
 if(mouse_b&1)
 {
 seek_button_view(xb+40,yb,1);
 }
 }



else if(mouse_x>xb+70 && mouse_x<xb+90 )//AUTO STOP PLAY GRID
 {
 char sttmp[24];
 sprintf(sttmp,"AutoStop GridPl.%d",num_grider+1);
 show_type_midi(1500+num_grider,sttmp );
 }
}//fin check y
 return(0);
}


int TheCallGridBox(int xb, int yb, int num_grider)
{
Rect GriderNum(Vec2D(xb+10,yb),Vec2D(50,20));
GriderNum.SetRoundness(5);
GriderNum.DrawOutline(CouleurLigne.WithAlpha(0.5));
neuromoyen.Print(ol::ToString(index_grider_selected[num_grider]+1),(xb+20), (yb+15));

if(mouse_x>xb+10 && mouse_x<xb+60 && mouse_y>yb && mouse_y<yb+20
&& window_focus_id==W_GRID  )
{
GriderNum.DrawOutline(CouleurLigne);
if(Midi_Faders_Affectation_Type!=0)
{
GriderNum.DrawOutline(CouleurBlind);
char sttmp[24];
sprintf(sttmp,"CallGrid in GridPl.%d",num_grider+1);
show_type_midi(1524+num_grider,sttmp );
}
}

Rect GiveNameOfGrider(Vec2D(xb+70,yb), Vec2D( 170,20));
GiveNameOfGrider.SetRoundness(7.5);
GiveNameOfGrider.DrawOutline(CouleurLigne.WithAlpha(0.5));
petitchiffre.Print( grider_name[index_grider_selected[num_grider]],(xb+75), (yb+15));
if(  window_focus_id==W_GRID && mouse_x>xb+70 && mouse_x<xb+250 && mouse_y>yb && mouse_y<yb+20 && index_type==1 )
{
GiveNameOfGrider.DrawOutline(CouleurLigne);
}

//UP DOWN griders number selected
Circle GriderPlus(Vec2D(xb+295,yb+10),12);
Circle GriderMinus(Vec2D(xb+265,yb+10),12);

petitchiffre.Print("-",xb+260,yb+13);
petitchiffre.Print("+",xb+290,yb+13);
GriderPlus.DrawOutline(CouleurLigne);
GriderMinus.DrawOutline(CouleurLigne);

if( window_focus_id==W_GRID )
{

if(mouse_x>xb+253 && mouse_x<xb+277 && mouse_y>yb-2 && mouse_y<yb+22)
{
if(Midi_Faders_Affectation_Type!=0)
{
char sttmp[24];
sprintf(sttmp,"Minus Grid in GridPl.%d",num_grider+1);
show_type_midi(1476+num_grider,sttmp );
GriderMinus.DrawOutline(CouleurBlind);
}
}

if( mouse_x>xb+283 && mouse_x<xb+307 && mouse_y>yb-2 && mouse_y<yb+22)
{
if( Midi_Faders_Affectation_Type!=0)
{
char sttmp[24];
sprintf(sttmp,"Plus Grid in GridPl.%d",num_grider+1);
show_type_midi(1480+num_grider,sttmp );
GriderPlus.DrawOutline(CouleurBlind);
}
}
}
return(0);
}

int Grid_player(int xb, int yb, int num_grider)
{
Line(Vec2D(xb+10,yb-10),Vec2D(xb+largeurGrider, yb-10)).Draw(CouleurLigne);
neuromoyen.Print("GridPlayer",xb+500,yb+15);
neuro.Print(ol::ToString(num_grider+1),xb+578,yb+17);

TheCallGridBox(xb,yb,num_grider);
TheStepBox(xb+315,yb, num_grider);
ThePlayCommands(xb+400,yb,num_grider);



TheGrid_commands(xb+20,yb+35,num_grider);//pos x, posy y, num player
TheGrid_divers(xb+220,yb+30,num_grider);//pos x, posy y, num player
TheGrid_matrix(xb+340,yb+35,num_grider);//pos x pos y taille de case num player

return(0);
}

/////////////////////////////////////////////////////////////////////////////////

int GlobalGridViewer(int xb, int yb)
{
//appel de grille
Line(Vec2D(xb,yb),Vec2D(xb+largeurGrider,yb)).Draw(CouleurLigne);
neuromoyen.Print("Grid",xb,yb+23);
Rect GriderNum(Vec2D(xb+40,yb+10),Vec2D(50,20));
GriderNum.SetRoundness(5);
GriderNum.DrawOutline(CouleurLigne.WithAlpha(0.5));
neuromoyen.Print(ol::ToString(grid_selected_for_view +1),(xb+50), (yb+23));
if(window_focus_id==W_GRID && mouse_x>xb+40 && mouse_x<xb+90 && mouse_y>yb+10 && mouse_y<yb+30 )
{
GriderNum.DrawOutline(CouleurLigne);
}

neuromoyen.Print("Step",xb+110,yb+23);
Rect GriderSt(Vec2D(xb+150,yb+10),Vec2D(50,20));
GriderSt.SetRoundness(5);
GriderSt.DrawOutline(CouleurLigne.WithAlpha(0.5));
neuromoyen.Print(ol::ToString(grid_step_view+1),(xb+160), (yb+23));
if(window_focus_id==W_GRID && mouse_x>xb+150 && mouse_x<xb+200 && mouse_y>yb+10 && mouse_y<yb+30 )
{
GriderSt.DrawOutline(CouleurLigne);
}

//déplacement dans les pas
previous_button_view(xb+220,yb+10,0);
next_button_view(xb+250,yb+10,0);

int def_nombre_grilles_previsu=largeurGrider/((grider_nb_col*5)+20);
//ajustements visuels
if(def_nombre_grilles_previsu==10){def_nombre_grilles_previsu-=2;}
else if(def_nombre_grilles_previsu>10 && def_nombre_grilles_previsu<18){def_nombre_grilles_previsu-=1;}
else if(def_nombre_grilles_previsu>15){def_nombre_grilles_previsu-=2;}


int tmpx=0;
int tmpy=0;
int tempfu=0;
//sab 0203/2014 unused var int templo=0;
int tempstep=0;
int tmpblx=0;
int tmpbly=0;

for(int pos=0;pos<def_nombre_grilles_previsu;pos++)
{


if(grid_step_view+pos<1023)
{
for (int co=0;co<=grider_nb_col;co++)
{
Line(Vec2D(20+xb+(co*5)+(pos*grider_nb_col*5)+(20*pos),yb+40),Vec2D(20+xb+(co*5)+(pos*grider_nb_col*5)+(20*pos),yb+40+(grider_nb_row*5))).Draw(CouleurLigne.WithAlpha(0.5));
}

for(int lo=0;lo<=grider_nb_row;lo++)
{
Line(Vec2D(20+xb+(pos*grider_nb_col*5)+(20*pos),yb+40+(lo*5)),Vec2D(20+xb+(pos*grider_nb_col*5)+(grider_nb_col*5)+(20*pos),yb+40+(lo*5))).Draw(CouleurLigne.WithAlpha(0.5));
}

for(int fu=0;fu<grider_nb_col;fu++)
{
for(int lo=0;lo<grider_nb_row;lo++)
{
tmpx=20+xb+(fu*5)+(pos*grider_nb_col*5)+(20*pos);
tmpy=yb+40+(lo*5);
tempfu=fu+(lo*grider_nb_col);
//sab 0203/2014 unused var templo=0;
tempstep=grid_step_view+pos;
tmpblx=20+xb+(pos*grider_nb_col*5)+(20*pos);
tmpbly=yb+60+(grider_nb_row*5);
//affichage delays
if(grid_times[grid_selected_for_view][grid_step_view+pos][0]>0 || grid_times[grid_step_view+pos][tempstep][2]>0)
{
minichiffrerouge.Print(string_grid_view_timing_global[pos],tmpblx,yb+38);
}

if(grid_levels[grid_selected_for_view][tempstep][tempfu]==255)
{
Rect QuadChF(Vec2D(tmpx,tmpy),Vec2D(5,5));
QuadChF.Draw(CouleurFader);
}
else if(grid_levels[grid_selected_for_view][tempstep][tempfu]>0
&& grid_levels[grid_selected_for_view][grid_step_view+pos][tempfu]<255)
{
Rect QuadCh(Vec2D(tmpx,tmpy),Vec2D(5,5));
QuadCh.Draw(CouleurGreen);
}
}
}
neuromoyen.Print(ol::ToString(tempstep+1),tmpblx,tmpbly);
Rect AutoStopB(Vec2D(tmpblx+40,tmpbly-10),Vec2D(30,10));
AutoStopB.Draw(CouleurBlind.WithAlpha(grid_stoplay[grid_selected_for_view][tempstep]));

minichiffre.Print(string_grid_view_timing_global[pos],tmpblx,tmpbly+10);
minichiffregris.Print("Goto",tmpblx,tmpbly+20);
minichiffregris.Print(ol::ToString(grid_goto[grid_selected_for_view][tempstep][0]+1),20+tmpblx,tmpbly+20);
minichiffregris.Print(ol::ToString(grid_goto[grid_selected_for_view][tempstep][1]+1),40+tmpblx,tmpbly+20);
minichiffregris.Print("Seek",tmpblx,tmpbly+30);
minichiffregris.Print(ol::ToString(grid_seekpos[grid_selected_for_view][tempstep]+1),40+tmpblx,tmpbly+30);



//fin condition max 1023 steps
}
//fin boucle des affichages de la grille
}



return(0);
}

////////////////////////////////////////////////////////////////////////////////

int Grider_Box(int xb, int yb)
{
Rect GriderBack(Vec2D(xb,yb),Vec2D(largeurGrider,hauteurGrider));
GriderBack.SetRoundness(15);
GriderBack.SetLineWidth(triple_epaisseur_ligne_fader);
GriderBack.Draw(CouleurFond);
if(window_focus_id==926)
{
GriderBack.DrawOutline(CouleurFader);
}
else
{
GriderBack.DrawOutline(CouleurLigne);
}


neuro.Print( "Grid",(xb+90), (yb+15));
neuro.Print( "Players",(xb+90), (yb+35));

//definition debut chan du grider
Rect BackGriderChan(Vec2D(xb+245,yb+15),Vec2D(40,20));
BackGriderChan.SetRoundness(4);
BackGriderChan.Draw(CouleurBleuProcedure.WithAlpha(0.5));
petitchiffre.Print("Beg.Chan.",xb+180,yb+30);
petitchiffre.Print(ol::ToString(grider_begin_channel_is),xb+250,yb+30);

//def number row and cols
Rect BackGriderCol(Vec2D(xb+315,yb+15),Vec2D(30,20));
BackGriderCol.SetRoundness(4);
BackGriderCol.Draw(CouleurBleuProcedure.WithAlpha(0.5));
petitchiffre.Print("Col.:",xb+290,yb+30);
petitchiffre.Print(ol::ToString(grider_nb_col),xb+320,yb+30);

Rect BackGriderRow(Vec2D(xb+385,yb+15),Vec2D(30,20));
BackGriderRow.SetRoundness(4);
BackGriderRow.Draw(CouleurBleuProcedure.WithAlpha(0.5));
petitchiffre.Print("Rows:",xb+347,yb+30);
petitchiffre.Print(ol::ToString(grider_nb_row),xb+390,yb+30);

//////////////EDIT MODE///////////////////////////////
Rect GriderEditEnable( Vec2D((xb+430),(yb+15)),Vec2D(50,20));
GriderEditEnable.SetRoundness(7.5);
if(index_enable_edit_Grider==1)
{
GriderEditEnable.Draw(CouleurFader);
}
GriderEditEnable.DrawOutline(CouleurLigne);
petitchiffre.Print("edit",xb+440 ,yb+27);

/////////////nbre Gridplayers affichage///////////////////////////
petitpetitchiffre.Print("GridPlayers",xb+535,yb+13);
for(int o=0;o<core_user_define_nb_gridplayers;o++)
{
Rect ShowGridB(Vec2D(xb+540+(o*15),yb+20),Vec2D(10,10));
if(index_show_grid_player[o]==1)
{ShowGridB.Draw(CouleurFader);}
ShowGridB.DrawOutline(CouleurLigne.WithAlpha(0.7));
if(window_focus_id==W_GRID  && mouse_x>xb+540+(o*15) && mouse_x<xb+540+(o*15)+10 && mouse_y>yb+20 && mouse_y<yb+30)
{
if(Midi_Faders_Affectation_Type!=0)
{
char sttmp[24];
sprintf(sttmp,"View GridPlayer %d",o+1);
show_type_midi(1472+o,sttmp );
ShowGridB.SetLineWidth(2.0);
ShowGridB.DrawOutline(CouleurBlind);
}
}
}

if( window_focus_id==W_GRID  && mouse_y>yb+15 && mouse_y<yb+35)
{
if(mouse_x>xb+245 && mouse_x<xb+285 &&  index_enable_edit_Grider==1)//chan edit
{
BackGriderChan.DrawOutline(CouleurLigne);
}
if(mouse_x>xb+315 && mouse_x<xb+355 &&  index_enable_edit_Grider==1)//col edit
{
BackGriderCol.DrawOutline(CouleurLigne);
}
if(mouse_x>xb+385 && mouse_x<xb+425 &&  index_enable_edit_Grider==1)//rows edit
{
BackGriderRow.DrawOutline(CouleurLigne);
}
}




//Global grid viewer
petitpetitchiffre.Print("View",xb+495,yb+13);
Rect AllowGridViewerB(Vec2D(xb+495,yb+20),Vec2D(40,10));
AllowGridViewerB.Draw(CouleurFader.WithAlpha(show_global_view_grider));
AllowGridViewerB.DrawOutline(CouleurLigne);

if( window_focus_id==W_GRID && mouse_b&1 && mouse_released==0)
{
if(mouse_x>xb+495 && mouse_x<xb+535 && mouse_y>yb+20 && mouse_y<yb+30)
{
show_global_view_grider=toggle(show_global_view_grider);
refresh_hauteur_fenetre_grider();
mouse_released=1;
}
}


if(show_global_view_grider==1)
 {GlobalGridViewer(xb,yb+40); }

 //AFFICHAGE DES GRID PLAYERS
int numerodeplayer_affiche=0;
for(int yo=0;yo<core_user_define_nb_gridplayers;yo++)
{
if(index_show_grid_player[yo]==1)
{
Grid_player(xb, yb+50+hauteurGlobalGridviewer+(numerodeplayer_affiche*(60+(grider_facteur_hauteur*size_grille))), yo);
numerodeplayer_affiche++;
}
}

return(0);
}
