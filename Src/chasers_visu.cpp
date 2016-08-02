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

* \file chasers_visu.cpp
* \brief {file for the GUI window of the chasers}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gère les fonction GUI de la fenêtre des chenillards
*
*   GUI fonctions for the chasers
*
 **/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int set_cue_in_view(int xp, int yp, bool state)
{
Rect SetLoopIN(Vec2D(xp,yp),Vec2D(20,20));
SetLoopIN.SetRoundness(4);

if(state==1){SetLoopIN.Draw(CouleurBlind);}

SetLoopIN.DrawOutline(CouleurLigne);
Line(Vec2D(xp,yp),Vec2D(xp+10,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+20,yp),Vec2D(xp+10,yp+10)).Draw(CouleurLigne);
petitpetitchiffre.Print("in",xp+6,yp+17);

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
SetLoopIN.DrawOutline(CouleurBlind);
}
}
return(0);
}


int set_cue_out_view(int xp, int yp, bool state)
{
Rect SetLoopOUT(Vec2D(xp,yp),Vec2D(20,20));
SetLoopOUT.SetRoundness(4);

if(state==1){SetLoopOUT.Draw(CouleurBlind);}

SetLoopOUT.DrawOutline(CouleurLigne);
Line(Vec2D(xp,yp),Vec2D(xp+10,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+20,yp),Vec2D(xp+10,yp+10)).Draw(CouleurLigne);
petitpetitchiffre.Print("out",xp+2,yp+17);

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
SetLoopOUT.DrawOutline(CouleurBlind);
}
}
return(0);
}


int seek_cue_in_view(int xp,int yp, bool state)
{
//Seek cue
Rect SeekCue(Vec2D(xp,yp),Vec2D(20,20));
SeekCue.SetRoundness(4);
SeekCue.DrawOutline(CouleurLigne);
if(state==1){SeekCue.Draw(CouleurBlind);}
Line(Vec2D(xp+16,yp+4),Vec2D(xp+16,yp+16)).Draw(CouleurLigne);
Line(Vec2D(xp+16,yp+4),Vec2D(xp+6,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+6,yp+10),Vec2D(xp+16,yp+16)).Draw(CouleurLigne);
Line(Vec2D(xp+4,yp+4),Vec2D(xp+4,yp+16)).Draw(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
SeekCue.DrawOutline(CouleurBlind);
}
}
return(0);
}

int set_forward_sens_view(int xp, int yp, bool state)
{

Rect FwdSens(Vec2D(xp,yp),Vec2D(20,20));
FwdSens.SetRoundness(4);

if(state==1){FwdSens.Draw(CouleurFader);}
FwdSens.DrawOutline(CouleurLigne);

Line(Vec2D(xp+4,yp+10),Vec2D(xp+18,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+12,yp+7),Vec2D(xp+18,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+12,yp+13),Vec2D(xp+18,yp+10)).Draw(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
FwdSens.DrawOutline(CouleurBlind);
}
}
 return(0);
}


int set_backward_sens_view(int xp, int yp, bool state)
{

Rect BckSens(Vec2D(xp,yp),Vec2D(20,20));
BckSens.SetRoundness(4);

if(state==1){BckSens.Draw(CouleurFader);}
BckSens.DrawOutline(CouleurLigne);

Line(Vec2D(xp+4,yp+10),Vec2D(xp+18,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+10,yp+7),Vec2D(xp+4,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+10,yp+13),Vec2D(xp+4,yp+10)).Draw(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
BckSens.DrawOutline(CouleurBlind);
}
}
 return(0);
}


int set_back_and_forward_sens_view(int xp, int yp, bool state)
{

Rect BckFwdSens(Vec2D(xp,yp),Vec2D(20,20));
BckFwdSens.SetRoundness(4);

if(state==1){BckFwdSens.Draw(CouleurFader);}
BckFwdSens.DrawOutline(CouleurLigne);

Line(Vec2D(xp+2,yp+10),Vec2D(xp+18,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+15,yp+7),Vec2D(xp+18,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+15,yp+13),Vec2D(xp+18,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+6,yp+7),Vec2D(xp+2,yp+10)).Draw(CouleurLigne);
Line(Vec2D(xp+6,yp+13),Vec2D(xp+2,yp+10)).Draw(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
BckFwdSens.DrawOutline(CouleurBlind);
}
}
 return(0);
}




int bouton_track_up(int xp, int yp,bool state)
{
Rect Btrack_up(Vec2D(xp,yp),Vec2D(40,20));
Btrack_up.SetRoundness(4);
if(state==1){ Btrack_up.Draw(CouleurFader);}
Btrack_up.DrawOutline(CouleurLigne);
Line(Vec2D(xp,yp+20),Vec2D(xp+40,yp+5)).Draw(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+40 && mouse_y>yp && mouse_y<yp+20)
{
if(Midi_Faders_Affectation_Type!=0)//config midi
{
Btrack_up.DrawOutline(CouleurBlind);
}
}

return(0);
}



int bouton_track_stay(int xp, int yp,bool state)
{
Rect Btrack_stay(Vec2D(xp,yp),Vec2D(40,20));
Btrack_stay.SetRoundness(4);
if(state==1){ Btrack_stay.Draw(CouleurGreen);}
Btrack_stay.DrawOutline(CouleurLigne);
Line(Vec2D(xp,yp+5),Vec2D(xp+40,yp+5)).Draw(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+40 && mouse_y>yp && mouse_y<yp+20)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
Btrack_stay.DrawOutline(CouleurBlind);
}
}

return(0);
}


int bouton_track_down(int xp, int yp,bool state)
{
Rect Btrack_stay(Vec2D(xp,yp),Vec2D(40,20));
Btrack_stay.SetRoundness(4);
if(state==1){ Btrack_stay.Draw(CouleurRed);}
Btrack_stay.DrawOutline(CouleurLigne);
Line(Vec2D(xp,yp+5),Vec2D(xp+40,yp+20)).Draw(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+40 && mouse_y>yp && mouse_y<yp+20)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
Btrack_stay.DrawOutline(CouleurBlind);
}
}

return(0);
}


///////////////////////////////////////////////////////////////////////////////
int bouton_view_track_downup(int xcha, int ycha, bool state)
{

Circle tChazeMinus(Vec2D(xcha+20,ycha+25),12);
Circle tChazePlus(Vec2D(xcha+20,ycha+55),12);
//up triangle
Line(Vec2D(xcha+12,ycha+30),Vec2D(xcha+28,ycha+30)).Draw(CouleurLigne);
Line(Vec2D(xcha+12,ycha+30),Vec2D(xcha+20,ycha+16)).Draw(CouleurLigne);
Line(Vec2D(xcha+28,ycha+30),Vec2D(xcha+20,ycha+16)).Draw(CouleurLigne);

//down triangle
Line(Vec2D(xcha+12,ycha+49),Vec2D(xcha+28,ycha+49)).Draw(CouleurLigne);
Line(Vec2D(xcha+12,ycha+49),Vec2D(xcha+20,ycha+63)).Draw(CouleurLigne);
Line(Vec2D(xcha+28,ycha+49),Vec2D(xcha+20,ycha+63)).Draw(CouleurLigne);

//petitchiffre.Print("-",xcha+17,ycha+28);
//petitchiffre.Print("+",xcha+17,ycha+58);

tChazePlus.DrawOutline(CouleurLigne);
tChazeMinus.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0  && window_focus_id==923)//config midi
{
if( mouse_x>xcha+8 && mouse_x<xcha+32 && mouse_y>ycha+13 && mouse_y<ycha+37)
{tChazeMinus.DrawOutline(CouleurBlind);}
if(mouse_x>xcha+8 && mouse_x<xcha+32 && mouse_y>ycha+43 && mouse_y<ycha+67)
{tChazePlus.DrawOutline(CouleurBlind);}
}

return(0);
}

int bouton_view_launchpad_pos(int xcha, int ycha, bool state)
{

Circle LchChazeMinus(Vec2D(xcha+20,ycha+25),12);
Circle LchChazePlus(Vec2D(xcha+50,ycha+25),12);
//left triangle
Line(Vec2D(xcha+12,ycha+25),Vec2D(xcha+24,ycha+30)).Draw(CouleurLigne);
Line(Vec2D(xcha+12,ycha+25),Vec2D(xcha+24,ycha+20)).Draw(CouleurLigne);
Line(Vec2D(xcha+24,ycha+20),Vec2D(xcha+24,ycha+30)).Draw(CouleurLigne);
//right triangle
Line(Vec2D(xcha+45,ycha+30),Vec2D(xcha+56,ycha+25)).Draw(CouleurLigne);
Line(Vec2D(xcha+56,ycha+25),Vec2D(xcha+45,ycha+20)).Draw(CouleurLigne);
Line(Vec2D(xcha+45,ycha+20),Vec2D(xcha+45,ycha+30)).Draw(CouleurLigne);

LchChazePlus.DrawOutline(CouleurLigne);
LchChazeMinus.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0 && window_focus_id==923)//config midi
{
if( mouse_x>xcha+8 && mouse_x<xcha+32 && mouse_y>ycha+13 && mouse_y<ycha+37)
{LchChazeMinus.DrawOutline(CouleurBlind);}
if(mouse_x>xcha+38 && mouse_x<xcha+62 && mouse_y>ycha+13 && mouse_y<ycha+37)
{LchChazePlus.DrawOutline(CouleurBlind);}
}

return(0);
}




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int Track_draw(int xp, int yp,int num_track)
{

//track selected
Rect Btrack_sel(Vec2D(xp,yp),Vec2D(20,20));
Btrack_sel.SetRoundness(4);
Btrack_sel.SetLineWidth(1);


if( track_is_on[chaser_selected][num_track]==1){Btrack_sel.Draw(CouleurGreen);}
Btrack_sel.DrawOutline(CouleurLigne);

if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
Btrack_sel.DrawOutline(CouleurBlind);
}
if(index_inspekt==1)//si au dessus de view, inspection
{
i_m_over_a_track=1;for(int pm=1;pm<513;pm++){over_track_show_channel[pm]= TrackContains[chaser_selected][num_track][pm];}
}
}


petitchiffre.Print(ol::ToString(num_track+1),xp+5,yp+13);
petitpetitchiffregris.Print(chaser_track_name[chaser_selected][num_track],xp+30,yp+22);
if(TrackTypeIs[chaser_selected][num_track]==1)
{
char str_ty[16];
sprintf(str_ty,"Mem. %.1f",(float (TrackHasMem[chaser_selected][num_track])/10));
petitpetitchiffrerouge.Print(str_ty,xp+30,yp+32);
}
//master
Rect track_fader(Vec2D(xp+30,yp),Vec2D(127,10));
Rect track_levelview(Vec2D(xp+30,yp),Vec2D(track_level[chaser_selected][num_track],10));

track_levelview.Draw(CouleurFader);

if(mouse_x>=xp+30 && mouse_x<=xp+157 && mouse_y>yp && mouse_y<yp+10 && Midi_Faders_Affectation_Type!=0)//config midi
{
 track_fader.DrawOutline(CouleurRed);//midi affect
}
else
{
 track_fader.DrawOutline(CouleurLigne);
}
petitpetitchiffre.Print(ol::ToString(track_level[chaser_selected][num_track]),xp+190,yp+25);

char temp_steppos[32];
sprintf(temp_steppos,"Time-Joint:B:%d E:%d R:%d", joint_begin_step[chaser_selected][num_track]+1, joint_end_step[chaser_selected][num_track]+1, count_steps_for_fades[chaser_selected][num_track]);
petitpetitchiffregris.Print(temp_steppos,xp+240,yp+25);


Circle BMidiOut( xp+180,yp+22, 5);//box du fader
if(midi_send_out[1023+num_track]==1)
{
BMidiOut.Draw(CouleurBlind);
}
BMidiOut.DrawOutline(CouleurLigne);


raccrochage_midi_visuel_horizontal_little (xp+30,yp,1023+num_track, 127, 10);
//////Affichage cases
for(int chcase=0;chcase<nbre_de_cases_par_track;chcase++)
{
Rect TCase(Vec2D(xp+170+(chcase*12),yp),Vec2D(12,12));
switch(chaser_step_operation[chaser_selected][num_track][chcase])
{
 case 0:
 TCase.Draw(CouleurLigne.WithAlpha(0.2));
 break;
 case 1:
 TCase.Draw(CouleurFader);
 break;
 case 2:
 TCase.Draw(CouleurGreen);
 break;
 case 3:
 TCase.Draw(CouleurRed);
 break;
 default: break;
}
TCase.DrawOutline(CouleurFond);


//Affichage des cases launchpad
if( launchpad_chaser_mode==1)
{
if(num_track-position_affichage_track_num[chaser_selected]<chaser_midi_rows)
{
if( chcase>=chaser_step_launchpad[chaser_selected] && chcase<chaser_step_launchpad[chaser_selected]+8 )
{
if(Midi_Faders_Affectation_Type!=0 )//config midi
{
TCase.DrawOutline(CouleurBlind);
}
else {
TCase.DrawOutline(CouleurLigne);}
}


}
}
}
return(0);
}










int chaser_window(int xcha,int ycha)
{


Rect ChaserPanel(Vec2D(xcha,  ycha), Vec2D( 620,(160+(nbre_track_visualisables*40))));
ChaserPanel.SetRoundness(15);
ChaserPanel.SetLineWidth(triple_epaisseur_ligne_fader);
ChaserPanel.Draw(CouleurFond);
if(window_focus_id==W_CHASERS)
{
ChaserPanel.DrawOutline(CouleurFader);
}
else {ChaserPanel.DrawOutline(CouleurLigne); }
neuro.Print("CHASERS",xcha+100,ycha+30);



//////PARTIE GENERALE DU CHASER///////////////////////////////////////////////

//UP DOWN bangers number selected
Circle ChazePlus(Vec2D(xcha+300,ycha+25),12);
Circle ChazeMinus(Vec2D(xcha+220,ycha+25),12);

petitchiffre.Print("-",xcha+217,ycha+28);
petitchiffre.Print("+",xcha+295,ycha+28);
neuro.Print(ol::ToString(chaser_selected+1),xcha+250,ycha+32);
ChazePlus.DrawOutline(CouleurLigne);
ChazeMinus.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0  && window_focus_id==923)//config midi
{
if( mouse_x>xcha+208 && mouse_x<xcha+232 && mouse_y>ycha+13 && mouse_y<ycha+37)
{ChazeMinus.DrawOutline(CouleurBlind);}
if(mouse_x>xcha+288 && mouse_x<xcha+312 && mouse_y>ycha+13 && mouse_y<ycha+37)
{ChazePlus.DrawOutline(CouleurBlind);}
}

//////////////////////TEXT////////////////////////////////////////////


Rect GiveNameOfchaser(Vec2D(xcha+330,ycha+10), Vec2D( 185,30));
GiveNameOfchaser.SetRoundness(7.5);
GiveNameOfchaser.Draw(CouleurSurvol);

petitchiffre.Print( chaser_name[chaser_selected],(xcha+335), (ycha+30));

//////////////EDIT MODE

Rect ChazeEditEnable( Vec2D((xcha+560),(ycha+10)),Vec2D(50,20));
ChazeEditEnable.SetRoundness(7.5);
if(index_enable_edit_chaser==1)
{
ChazeEditEnable.Draw(CouleurFader);
}
ChazeEditEnable.DrawOutline(CouleurLigne);
petitchiffre.Print("edit",xcha+570 ,ycha+22);

////////////////////////////



////////////////////////////////boutons d action de la lecture globale du chaser
//play
play_button_view(xcha+10,ycha+50,chaser_is_playing[chaser_selected]);

//seek to begin
if(mouse_x>xcha+40 && mouse_x<xcha+60 && mouse_y>ycha+50 && mouse_y<ycha+70 && window_focus_id==923 && mouse_button==1 && mouse_released==0)
{
seek_button_view(xcha+40,ycha+50,1);//seek , affichage avant le bouton
mouse_released=1;
}
seek_button_view(xcha+40,ycha+50,0);


//loop
loop_button_view(xcha+70,ycha+50,chaser_is_in_loop[chaser_selected]);



//forward sens

if(chaser_way[chaser_selected]==0)
{set_forward_sens_view(xcha+110,ycha+50,1);}
else {set_forward_sens_view(xcha+110,ycha+50,0);}

//backward sens

if(chaser_way[chaser_selected]==1)
{set_backward_sens_view(xcha+140,ycha+50,1);}
else {set_backward_sens_view(xcha+140,ycha+50,0);}


//backward and forward sens

if(chaser_aller_retour[chaser_selected]==1)
{set_back_and_forward_sens_view(xcha+170,ycha+50,1);}
else {set_back_and_forward_sens_view(xcha+170,ycha+50,0);}



///AFFECT TO DOCK/////////////////////////////////////////////////////
char temp_str_chi[36];
sprintf(temp_str_chi,"Last Affect: Fader %d Dock %d",view_chaser_affected_to_fader[chaser_selected][0]+1,view_chaser_affected_to_fader[chaser_selected][1]+1);
petitpetitchiffregris.Print(temp_str_chi,xcha+5,ycha+120);
sprintf(temp_str_chi,"Step Is: %d   Evolution: %.2f",chaser_step_is[chaser_selected]+1,index_progression_chaser_step[chaser_selected]);
petitpetitchiffregris.Print(temp_str_chi,xcha+5,ycha+137);
sprintf(temp_str_chi,"Chaser LFO Slaviness: %.2f",chaser_slaviness[chaser_selected]);
petitpetitchiffregris.Print(temp_str_chi,xcha+5,ycha+150);

Rect Affectchaser(Vec2D(xcha+430,ycha+80), Vec2D(110,20));
Affectchaser.SetRoundness(7.5);
if(index_affect_chaser_to_dock==1){Affectchaser.Draw(CouleurFader);}
Affectchaser.DrawOutline(CouleurLigne);

petitchiffre.Print( "Affect To Dock",(xcha+440), (ycha+95));



/////////////ACTIONS SUR ON TRACK ET SELECTIONS
if(mouse_x>xcha+10 && mouse_x<xcha+30 && mouse_y>ycha+80 && mouse_y<ycha+100 && window_focus_id==923)
{
if(mouse_button==1 && mouse_released==0)
{
bouton_text_view(xcha+10, ycha+80,"all", 1);
}
}
bouton_text_view(xcha+10, ycha+80,"all", 0);


//selections//////////////////////////////////////////////////
if(mouse_x>xcha+40 && mouse_x<xcha+60 && mouse_y>ycha+80 && mouse_y<ycha+100 && window_focus_id==923)
{
if(mouse_button==1 && mouse_released==0)
{
bouton_text_view(xcha+40, ycha+80,"inv", 1);
}
}
bouton_text_view(xcha+40, ycha+80,"inv", 0);


if(mouse_x>xcha+70 && mouse_x<xcha+90 && mouse_y>ycha+80 && mouse_y<ycha+100 && window_focus_id==923)
{
if(mouse_button==1 && mouse_released==0)
{
bouton_text_view(xcha+70, ycha+80,"off", 1);
}
}
bouton_text_view(xcha+70, ycha+80,"off", 0);





/////////////////presets de selection////////////////////////////////////////
char tl[8];
for(int po=0;po<4;po++)
{
sprintf(tl,"P%d",po+1);
if(mouse_x>xcha+110+(po*30) && mouse_x<xcha+150+(po*30) && mouse_y>ycha+80 && mouse_y<ycha+100 && window_focus_id==923)
{
if(mouse_button==1 && mouse_released==0)
{
bouton_text_view(xcha+110+(po*30), ycha+80,tl, 1);
}
}
bouton_text_view(xcha+110+(po*30), ycha+80,tl, 0);
}
/////////////////OPTIONS

Rect RelyToFaderMode(Vec2D(xcha+345,ycha+50),Vec2D(40,20));
RelyToFaderMode.SetRoundness(5);
if(index_slave_chaser_to_accelerometre[chaser_selected]==1)
{RelyToFaderMode.Draw(CouleurFader);  }
RelyToFaderMode.DrawOutline(CouleurLigne);
petitpetitchiffre.Print("Slave",xcha+350,ycha+65);


////////////////////Time unit////////////////////////////////////////
char temp_tunit[24];
Rect Tunit(Vec2D(xcha+245,ycha+50),Vec2D(50,20));
Tunit.SetRoundness(5);
if(mouse_x>xcha+245 && mouse_x<xcha+295 && mouse_y>ycha+50 && mouse_y<ycha+70)
{
Tunit.Draw(CouleurBleuProcedure.WithAlpha(0.4));
}
Tunit.DrawOutline(CouleurLigne);


switch(index_affichage_digit_time_unit)
{
case 0:
sprintf(temp_tunit,"T.Unit:       %.1f",time_unit[chaser_selected]*chaser_slaviness[chaser_selected]);
break;
case 1:
sprintf(temp_tunit,"T.Unit:      %.2f",time_unit[chaser_selected]*chaser_slaviness[chaser_selected]);
break;
case 2:
sprintf(temp_tunit,"T.Unit:     %.3f",time_unit[chaser_selected]*chaser_slaviness[chaser_selected]);
break;
case 3:
sprintf(temp_tunit,"T.Unit:    %.4f",time_unit[chaser_selected]*chaser_slaviness[chaser_selected]);
break;
default: break;
}

petitpetitchiffre.Print(temp_tunit,xcha+200,ycha+64);

///time joint mode//////////////////////////////////////////////////////

Rect TMode(Vec2D(xcha+305,ycha+50),Vec2D(30,20));
TMode.SetRoundness(5);
if(chaser_time_mode[chaser_selected]==1)
{
TMode.Draw(CouleurFader);
petitpetitchiffre.Print("TJoin",xcha+306,ycha+65);
}
else {petitpetitchiffre.Print("T.Std",xcha+305,ycha+65);}
TMode.DrawOutline(CouleurLigne);
/////////////////////CHASER OPERATOR/////////////////////////////////////

switch (chaser_operator_is)
{
case 1://up
bouton_track_up(xcha+245, ycha+80, 1);
bouton_track_stay(xcha+295, ycha+80, 0);
bouton_track_down(xcha+345, ycha+80, 0);
break;
case 2://stay
bouton_track_up(xcha+245, ycha+80, 0);
bouton_track_stay(xcha+295, ycha+80, 1);
bouton_track_down(xcha+345, ycha+80, 0);
break;
case 3: //down
bouton_track_up(xcha+245, ycha+80, 0);
bouton_track_stay(xcha+295, ycha+80, 0);
bouton_track_down(xcha+345, ycha+80, 1);
break;
default:
bouton_track_up(xcha+245, ycha+80, 0);
bouton_track_stay(xcha+295, ycha+80, 0);
bouton_track_down(xcha+345, ycha+80, 0);
break;
}



//BEGIN POINT // END POINT
Rect CurseurBeginPoint(Vec2D(xcha+175+(chaser_begin_step_is[chaser_selected]*12),ycha+115),Vec2D(12,12));
CurseurBeginPoint.Draw(CouleurFader);
if( Midi_Faders_Affectation_Type!=0 && mouse_x>xcha+175+(chaser_begin_step_is[chaser_selected]*12) && mouse_x<xcha+187+(chaser_begin_step_is[chaser_selected]*12)
&& mouse_y>ycha+115 && mouse_y<ycha+127)//config midi
{
CurseurBeginPoint.SetLineWidth(2);
CurseurBeginPoint.DrawOutline(CouleurRed);
}
Rect CurseurEndPoint(Vec2D(xcha+175+(chaser_end_step_is[chaser_selected]*12),ycha+127),Vec2D(12,12));
CurseurEndPoint.Draw(CouleurRed);
if( Midi_Faders_Affectation_Type!=0 && mouse_x>xcha+175+(chaser_end_step_is[chaser_selected]*12) && mouse_x<xcha+187+(chaser_end_step_is[chaser_selected]*12)
&& mouse_y>ycha+127 && mouse_y<ycha+139)//config midi
{
CurseurEndPoint.SetLineWidth(2);
CurseurEndPoint.Draw(CouleurFond);
CurseurEndPoint.DrawOutline(CouleurRed);
}

/////////////////////VIEW TRACK BUTTON////////////////////////////////////////////////
bouton_view_track_downup(xcha+580, ycha+35, 0);
int upsidedown=1;

/////////POSITION TIME LINE + IN OUT POINT VIEW//////////////////////////////////////////////////
for(int chcase=0;chcase<nbre_de_cases_par_track;chcase++)
{
upsidedown=toggle(upsidedown);
Line(Vec2D(xcha+175+(chcase*12),ycha+115),Vec2D(xcha+175+(chcase*12),ycha+135)).Draw(CouleurLigne.WithAlpha(0.2));
petitpetitchiffre.Print(ol::ToString(chcase+1),xcha+175+(chcase*12),ycha+123+(upsidedown*12));
}
Line(Vec2D(xcha+10,ycha+125),Vec2D(xcha+590,ycha+125)).Draw(CouleurLigne.WithAlpha(0.3));





////////////////////////TRACK/////////////////////////////////////////////

for(int track_num=0;track_num<nbre_track_visualisables;track_num++)
{
Track_draw(xcha+5,ycha+165+(track_num*40),position_affichage_track_num[chaser_selected]+track_num);
}


//CURSEUR TIME
Rect TimelineChaser(Vec2D(xcha+175,ycha+145),Vec2D(36*12,10));
TimelineChaser.Draw(CouleurLigne.WithAlpha(0.2));
if( Midi_Faders_Affectation_Type!=0)//config midi
{
if(mouse_x>xcha+175 && mouse_x<xcha+175+(nbre_de_cases_par_track*12) && mouse_y>ycha+145 && mouse_y<ycha+155)
{
TimelineChaser.DrawOutline(CouleurBlind);

}
}



int id_way=0;
switch(chaser_way[chaser_selected])
{
case 0://FORWARD
id_way=1;
Line(Vec2D(xcha+175+(chaser_step_is[chaser_selected]*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+115),Vec2D(xcha+175+(chaser_step_is[chaser_selected]*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+145+(nbre_track_visualisables*40))).Draw(CouleurFader);
Line(Vec2D(xcha+176+(chaser_step_is[chaser_selected]*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+115),Vec2D(xcha+176+(chaser_step_is[chaser_selected]*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+145+(nbre_track_visualisables*40))).Draw(CouleurFader);

break;
case 1://BACKWARD
id_way=-1;
Line(Vec2D(xcha+175+((chaser_step_is[chaser_selected]+1)*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+115),Vec2D(xcha+175+((chaser_step_is[chaser_selected]+1)*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+145+(nbre_track_visualisables*40))).Draw(CouleurFader);
Line(Vec2D(xcha+176+((chaser_step_is[chaser_selected]+1)*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+115),Vec2D(xcha+176+((chaser_step_is[chaser_selected]+1)*12)+(index_progression_chaser_step[chaser_selected]*12*id_way),ycha+145+(nbre_track_visualisables*40))).Draw(CouleurFader);
break;
default: break;
}


Rect PosCurseur(Vec2D(xcha+175+(chaser_step_is[chaser_selected]*12)+(12*index_progression_chaser_step[chaser_selected]*id_way),ycha+145),Vec2D(12,10));
PosCurseur.Draw(CouleurLigne.WithAlpha(0.3));



////////LAUNCHPAD

Rect LaunchpadAllowB(Vec2D(xcha+410,ycha+50),Vec2D(40,20));
LaunchpadAllowB.SetRoundness(5);
if( launchpad_chaser_mode==1)
{
LaunchpadAllowB.Draw(CouleurFader);
bouton_view_launchpad_pos(xcha+450, ycha+35,0);
}
LaunchpadAllowB.DrawOutline(CouleurLigne);
petitpetitchiffre.Print("LchPad",xcha+411,ycha+65);


//refresh midi
Rect refreshMidiB(Vec2D(xcha+520,ycha+50),Vec2D(40,20));
refreshMidiB.SetRoundness(5);
refreshMidiB.Draw(CouleurSurvol.WithAlpha( refresh_midi_chasers));
refreshMidiB.DrawOutline(CouleurLigne);
petitpetitchiffre.Print("Refresh",xcha+520,ycha+58);
petitpetitchiffre.Print("Midi",xcha+527,ycha+67);

return(0);
}


