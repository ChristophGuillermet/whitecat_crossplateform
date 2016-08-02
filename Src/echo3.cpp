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

* \file echo3.cpp
* \brief {fonctions for the draw module}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour controller le module echo qui permet de controller la lumière à partir de loi physique de gravité ou autre
*
*   Fonctions for controlling the echo module who make the hability to control the light from physical law as gravity or other
*
 **/

int do_bouncing_levels(int ech)
{
//echo_global_params[24][3];Gravity Mass Delta
//echo_levels[24][3][513]; //level GroundLevel

float gravity=echo_global_params[ech][0];
float inertie=echo_global_params[ech][1]/9.8; //( channel mass)
float acceleration=inertie/gravity;
float delta=echo_global_params[ech][2]/9.8;//velocity

//MODE ECHO
if( echo_is_echo_mode[ech]==1)
{

//recopie des niveaux sup
for(int i=1;i<513;i++)
{
if(((float)(FaderDoDmx[(echo_pointing_fader_num[ech]-1)][i]))/255 > echo_levels[ech][0][i-1] )
{
echo_levels[ech][0][i-1]=((float)(FaderDoDmx[(echo_pointing_fader_num[ech]-1)][i]))/255;//((float)(FaderDockContains[f][dock_used_by_fader_is[f]][i]))/255;
//prepa
tmp_echo[ech][i-1]=0.0;
tmp_falling_from_level[ech][i-1]=echo_levels[ech][0][i-1];
echo_way[ech][i-1]=0;
}
}
//lancement
bounce_is_prepared[ech]=1;
do_bounce[ech]=1;
}

//BOUNCING

for(int b=0; b<512; b++)
{

switch(echo_way[ech][b])
{
case 0: //falling
echo_levels[ech][0][b]-=gravity*delta + 0.5*acceleration*(delta*delta)+tmp_echo[ech][b];
tmp_echo[ech][b]+=0.001*gravity;
if(echo_levels[ech][0][b]<=echo_levels[ech][1][b])//ground
{
echo_levels[ech][0][b]=echo_levels[ech][1][b];
tmp_echo[ech][b]=0.0;
tmp_falling_from_level[ech][b]-=inertie;
echo_way[ech][b]=1;
tmp_echo[ech][b]=0.001*gravity;
}

break;
case 1://boucing
echo_levels[ech][0][b]+=gravity*delta + 0.5*acceleration*(delta*delta)+tmp_echo[ech][b];

if(echo_levels[ech][0][b]>tmp_falling_from_level[ech][b])//ground
{
echo_levels[ech][0][b]=tmp_falling_from_level[ech][b];
echo_way[ech][b]=0;
tmp_echo[ech][b]=0.001*gravity;
}
break;
default: break;
}

//ground
if(echo_levels[ech][0][b]<echo_levels[ech][1][b])
{
echo_levels[ech][0][b]=echo_levels[ech][1][b];
if(echo_is_echo_mode[ech]==0) check_echo_bounce_done(ech);
}

}
 return(0);
}

int do_echo()
{

for(int ech=0;ech<=core_user_define_nb_echo-1;ech++)
{
if(do_bounce[ech]==1)
{
do_bouncing_levels(ech);
bounce_is_prepared[ech]=0;
}
else
{
prepare_bounce(ech);
}
}
 return(0);
}



int do_logical_Echo_Aera(int xe, int ye)
{
if(window_focus_id==W_ECHO)
{

int echochanis=0;
float mouse_y_level=0.0;

for (int sh=0;sh<15;sh++)
{
if( mouse_x>xe+25+(sh*30) && mouse_x<xe+55+(sh*30) && mouse_y>=ye-5 && mouse_y<=ye+135)
{
echochanis=echo_grid_channel_position[echo_selected]+sh;
if(index_enable_edit_echo==1 )
{
dragging_channel_in_echo=1;
//mouse_y_level=((float)constrain_data_to_midi_range(mouse_y-ye))/127.0;
mouse_y_level=1.0-((float)constrain_data_to_midi_range(mouse_y-ye))/127.0;
echo_levels[echo_selected][(echo_channel_manipulate_mode[echo_selected])][echochanis]=mouse_y_level;
if(echo_channel_manipulate_mode[echo_selected]==0)
{
tmp_falling_from_level[echo_selected][echochanis]=echo_levels[echo_selected][0][echochanis];
}
record_channel_ch_state_in_an_echo(echo_selected,echochanis);
}
}
}

//fleches
if(dragging_channel_in_echo==0)
{
//Prev
if( mouse_x>xe && mouse_x<xe+25 && mouse_y>ye && mouse_y<ye+127 && mouse_released==0 )
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1691,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(echo_grid_channel_position[echo_selected]>0)
{
echo_grid_channel_position[echo_selected]--;
mouse_released=1;
}
}
}
//next
else if( mouse_x>xe+475 && mouse_x<xe+475+25 && mouse_y>ye && mouse_y<ye+127 && mouse_released==0 )
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1692,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
if(echo_grid_channel_position[echo_selected]<(511-14))
{
echo_grid_channel_position[echo_selected]++;
mouse_released=1;
}
}
}


}
}
return(0);
}


int do_logical_echo_window(int xe, int ye)
{
if(window_focus_id==W_ECHO && dragging_channel_in_echo==0 && mouse_button==1)
{

//edit
if( mouse_released==0 && mouse_x>xe+610 && mouse_x<xe+610+50 && mouse_y>ye+10 && mouse_y<ye+10+20 )
{
index_enable_edit_echo=toggle(index_enable_edit_echo);
mouse_released=1;
}


int index_ec=0;
//SElection presets
for(int le=0;le<3;le++)
{
for(int cel=0;cel<8;cel++)
{
index_ec=cel+(le*8);
if( mouse_x> xe+180+(40*cel) && mouse_x<xe+180+(40*cel)+30 && mouse_y>ye+10+(le*25) && mouse_y<ye+10+(le*25)+20)
{
if( mouse_released==0 )
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
 attribute_midi_to_control(1663+index_ec,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
else
{
if(index_main_clear==1)
{
if(index_enable_edit_echo==1)
{
index_selected_echo_for_manipulation=index_ec;
index_ask_clear_echo_preset=1;
index_ask_confirm=1;             //clear_echo_preset(index_selected_echo_for_manipulation);
}
}

else
{
echo_selected=index_ec;

}
}
mouse_released=1;
}
}
}
}


//Set ChanPos
if( mouse_x>xe+615 && mouse_x<xe+615+40 && mouse_y>ye+65 && mouse_y<ye+65+20 && mouse_released==0 && dragging_channel_in_echo==0 && numeric_postext>0)
 {
 echo_grid_channel_position[echo_selected]=atoi(numeric)-1;
 echo_grid_channel_position[echo_selected]= constrain_int_data_to_this_range(echo_grid_channel_position[echo_selected],0,511-14);
 reset_numeric_entry();
 numeric_postext=0;
 mouse_released=1;
 }


//ECHO ACTION PANNEL

for (int n=0;n<5;n++)
{
//actions
if(mouse_x>xe+30 && mouse_x<xe+30+115 && mouse_y>ye+50+(n*30) && mouse_y<ye+50+30+(n*30))
{
if( mouse_released==0 )
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1686+n,Midi_Faders_Affectation_Mode);
}
else
{
switch(n)
{
case 0:
     echo_is_echo_mode[echo_selected]=toggle(echo_is_echo_mode[echo_selected]);
     do_bounce[echo_selected]=echo_is_echo_mode[echo_selected];
break;
case 1:
     snap_fader_state(echo_selected,echo_pointing_fader_num[echo_selected]-1);
break;
case 2:
     bounce(echo_selected);
break;
case 3:
     snap_kill_and_bounce(echo_selected,echo_pointing_fader_num[echo_selected]-1);
break;
case 4:
     recall_fader_state_echo(echo_pointing_fader_num[echo_selected]-1);
break;
default:
break;
}
}
mouse_released=1;
}

}
}

//Fader point to
if( mouse_x>xe+70 && mouse_x<xe+70+45 && mouse_y>ye+200 && mouse_y<ye+200+35 && mouse_released==0 && numeric_postext>0)
{
echo_pointing_fader_num[echo_selected]=constrain_int_data_to_this_range(atoi(numeric),1,48);
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}


////AFFECT TO DOCK
if( mouse_released==0 && mouse_x>xe+10 && mouse_x<xe+10+110 && mouse_y>ye+245 && mouse_y<ye+245+20  )
{
if(index_affect_echo_to_dock==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_affect_echo_to_dock=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_affect_echo_to_dock;
mouse_released=1;
}


//manipulate channel params Level mode / ground mode
if( mouse_released==0 && mouse_x>xe+500 && mouse_x<xe+500+70 && mouse_y>ye+10 && mouse_y<ye+10+20)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1696,Midi_Faders_Affectation_Mode);
}
else
{
if(index_main_clear==1 && index_enable_edit_echo==1)
{
switch(echo_channel_manipulate_mode[echo_selected])
{
 case 0://levels
 clear_echo_levels(echo_selected);
 break;
 case 1:
 clear_ground_levels(echo_selected);
 break;
 default: break;
}
index_main_clear=0;
}
else
{
echo_channel_manipulate_mode[echo_selected]=toggle(echo_channel_manipulate_mode[echo_selected]);
}
}
mouse_released=1;
}






//les Trois parametres globaux: gravite masse energy
for (int cl=0;cl<3;cl++)
{

if(mouse_x>=xe+155+(cl*180) && mouse_x<=xe+155+(cl*180)+130 && mouse_y>=ye+255 && mouse_y<=ye+255+10)
{
if(  mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
attribute_midi_solo_affectation(1693+cl,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
echo_global_params[echo_selected][cl]= (float)(constrain_data_to_midi_range(mouse_x-( xe+155+(cl*180))))/127;
midi_levels[1693+cl]=(int)(echo_global_params[echo_selected][cl]*127);
}
}
}
//midi out
if( mouse_released==0 && mouse_x>=xe+290+(cl*180) && mouse_x<=xe+290+(cl*180)+10 && mouse_y>=ye+260 && mouse_y<=ye+265+10)
{
 midi_send_out[1693+cl]=toggle(midi_send_out[1693+cl]);
 mouse_released=1;
}

}//fin des 3 sliders



}
//hors du dragging 0
do_logical_Echo_Aera(xe+155,ye+95);
return(0);
}



int Echo_Aera(int xe, int ye)
{
//Aera channels
Rect Aera(Vec2D(xe,ye),Vec2D(500,127));
Aera.SetRoundness(4);
Aera.Draw(Discrete8);

Rect PreviousChan(Vec2D(xe,ye),Vec2D(25,127));
PreviousChan.SetRoundness(4);
Line(Vec2D(xe+5,ye+64),Vec2D(xe+15,ye+54)).Draw(CouleurLigne);
Line(Vec2D(xe+15,ye+54),Vec2D(xe+15,ye+74)).Draw(CouleurLigne);
Line(Vec2D(xe+15,ye+74),Vec2D(xe+5,ye+64)).Draw(CouleurLigne);


Rect NextChan(Vec2D(xe+475,ye),Vec2D(25,127));
NextChan.SetRoundness(4);
Line(Vec2D(xe+490,ye+64),Vec2D(xe+480,ye+54)).Draw(CouleurLigne);
Line(Vec2D(xe+480,ye+54),Vec2D(xe+480,ye+74)).Draw(CouleurLigne);
Line(Vec2D(xe+480,ye+74),Vec2D(xe+490,ye+64)).Draw(CouleurLigne);


Rect ChanEcho(Vec2D(xe+475,ye),Vec2D(30,6));





int echochanis=0;
//sab 02/03/2014 unused var float mouse_y_level=0.0;

for (int sh=0;sh<15;sh++)
{
Line(Vec2D(xe+25+(sh*30),ye),Vec2D(xe+25+(sh*30),ye+127)).Draw(CouleurLigne.WithAlpha(0.7));

echochanis=echo_grid_channel_position[echo_selected]+sh;


//ground
Rect MassE(Vec2D(xe+25+(sh*30),ye+(127*(1.0-echo_levels[echo_selected][1][echochanis]))),Vec2D(30,echo_levels[echo_selected][1][echochanis]*127));
MassE.Draw(Discrete2);

//enregistrement level de départ
ChanEcho.MoveTo(Vec2D(xe+25+(sh*30),ye+127-(snap_echo_to_recall[echo_selected][echochanis]*127)));
ChanEcho.Draw(CouleurFond.WithAlpha(0.3));

//niveau
ChanEcho.MoveTo(Vec2D(xe+25+(sh*30),ye+127-(echo_levels[echo_selected][0][echochanis]*127)));
ChanEcho.Draw(CouleurLigne);

petitchiffrenoir.Print(ol::ToString(echochanis+1),xe+30+(sh*30),ye+10);

if(window_focus_id==W_ECHO && mouse_x>xe+25+(sh*30) && mouse_x<xe+55+(sh*30) && mouse_y>=ye-5 && mouse_y<=ye+135)
{
echo_over_channel=echo_grid_channel_position[echo_selected]+sh;
}

}
Line(Vec2D(xe+25+450,ye),Vec2D(xe+475,ye+127)).Draw(CouleurLigne.WithAlpha(0.7));




char tcmp[24];
//fleches
if(window_focus_id==W_ECHO && dragging_channel_in_echo==0)
{
//Prev
if( mouse_x>xe && mouse_x<xe+25 && mouse_y>ye && mouse_y<ye+127)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
sprintf(tcmp,"Echo Previous Chan");
show_type_midi(1691, tcmp);
PreviousChan.DrawOutline(CouleurBlind);
}
else
{PreviousChan.DrawOutline(CouleurLigne.WithAlpha(0.5));}
}
//next
else if( mouse_x>xe+475 && mouse_x<xe+500 && mouse_y>ye && mouse_y<ye+127)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
sprintf(tcmp,"Echo next Chan");
show_type_midi(1692, tcmp);
NextChan.DrawOutline(CouleurBlind);
}
else {NextChan.DrawOutline(CouleurLigne.WithAlpha(0.5));  }
}
}

return(0);
}

int echo_window(int xe, int ye)
{
Rect EchoBckgd(Vec2D(xe,  ye), Vec2D( echo_window_x_size,echo_window_y_size));
EchoBckgd.SetRoundness(15);
EchoBckgd.SetLineWidth(triple_epaisseur_ligne_fader);
EchoBckgd.Draw(CouleurFond);

if(window_focus_id==W_ECHO)
{
EchoBckgd.DrawOutline(CouleurFader);
}
else {EchoBckgd.DrawOutline(CouleurLigne); }
neuro.Print("ECHO",xe+100,ye+30);

//EDIT
Rect GriderEditEnable( Vec2D((xe+610),(ye+10)),Vec2D(50,20));
GriderEditEnable.SetRoundness(5);
if(index_enable_edit_echo==1)
{
GriderEditEnable.Draw(CouleurFader);
}
GriderEditEnable.DrawOutline(CouleurLigne.WithAlpha(0.5));
petitchiffre.Print("edit",xe+620 ,ye+22);


neuro.Print(ol::ToString(echo_over_channel+1),xe+625 ,ye+55);

char tcmp[24];

switch(dmx_view)
{
case 1:
sprintf(tcmp,"Level %.2f - %d",echo_levels[echo_selected][0][echo_over_channel],(int)( echo_levels[echo_selected][0][echo_over_channel]*255));
break;
case 0:
sprintf(tcmp,"Level %.2f - %d",echo_levels[echo_selected][0][echo_over_channel],(int)( echo_levels[echo_selected][0][echo_over_channel]*100));
break;
default: break;
}
petitchiffre.Print(tcmp,xe+500 ,ye+45);

switch(dmx_view)
{
case 1:
sprintf(tcmp,"Ground %.2f - %d",echo_levels[echo_selected][1][echo_over_channel],(int)( echo_levels[echo_selected][1][echo_over_channel]*255));
break;
case 0:
sprintf(tcmp,"Ground %.2f - %d",echo_levels[echo_selected][1][echo_over_channel],(int)( echo_levels[echo_selected][1][echo_over_channel]*100));
break;
default: break;
}
petitchiffre.Print(tcmp,xe+500 ,ye+70);

//sab 02/03/2014 sprintf(tcmp,"");
strcpy(tcmp,"");

int index_ec=0;

//ECHO presets



Rect EchoPreset(Vec2D(xe+10,ye+10),Vec2D(30,15));
EchoPreset.SetRoundness(4);
for(int le=0;le<3;le++)
{
for(int cel=0;cel<8;cel++)
{
index_ec=cel+(le*8);
EchoPreset.MoveTo(Vec2D(xe+180+(cel*40),ye+10+(le*25)));
if(echo_selected==index_ec){EchoPreset.Draw(CouleurFader);}
EchoPreset.DrawOutline(CouleurLigne.WithAlpha(0.5));
petitchiffre.Print(ol::ToString(index_ec+1),xe+188+(cel*40),ye+20+(le*25));


if(window_focus_id==W_ECHO && dragging_channel_in_echo==0 && mouse_x> xe+180+(40*cel) && mouse_x<xe+210+(40*cel) && mouse_y>ye+10+(le*25) && mouse_y<ye+30+(le*25))
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
sprintf(tcmp,"Echo Preset %d",index_ec+1);
show_type_midi(1663+index_ec, tcmp);
EchoPreset.DrawOutline(CouleurBlind);
}
}
}
}


 Rect SetChannpos(Vec2D(xe+615,ye+65),Vec2D(40,20));
 SetChannpos.SetRoundness(5);
 SetChannpos.Draw(Discrete2);
 SetChannpos.DrawOutline(CouleurLigne.WithAlpha(0.4));
 petitchiffre.Print(ol::ToString(echo_grid_channel_position[echo_selected]+1),xe+625,ye+78);

 if(window_focus_id==W_ECHO && mouse_x>xe+615 && mouse_x<xe+655 && mouse_y>ye+65 && mouse_y<ye+85)
 {
 SetChannpos.DrawOutline(CouleurLigne.WithAlpha(0.7));
 }

//ECHO ACTION PANNEL
Rect Action(Vec2D(xe+10,ye+40),Vec2D(115,20));
Action.SetRoundness(4);
for (int n=0;n<5;n++)
{
Action.MoveTo(Vec2D(xe+10,ye+50+(n*30)));
Action.DrawOutline(CouleurLigne.WithAlpha(0.5));
switch(n)
{
case 0:
     Action.Draw(CouleurFader.WithAlpha(echo_is_echo_mode[echo_selected]));
     petitchiffre.Print("ECHO FADER",xe+30,ye+62+(n*30));
     sprintf(tcmp,"ECHO FADER");
break;
case 1:
     petitchiffre.Print("SNAP FADER",xe+30,ye+62+(n*30));
     sprintf(tcmp,"SNAP FADER");
break;
case 2:

     Action.Draw(CouleurFader.WithAlpha(do_bounce[echo_selected]));
     petitchiffre.Print("BOUNCE !",xe+35,ye+62+(n*30));
     sprintf(tcmp,"BOUNCE !");
break;
case 3:
     petitchiffre.Print("SNAP-KILL-BOUNCE",xe+11,ye+62+(n*30));
     sprintf(tcmp,"SNAP-KILL-BOUNCE");
break;
case 4:
     petitchiffre.Print("GET BACK FADER",xe+15,ye+62+(n*30));
     sprintf(tcmp,"GET BACK FADER");
break;
default:
break;
}

//actions
if(window_focus_id==W_ECHO && dragging_channel_in_echo==0  && mouse_x>xe+30 && mouse_x<xe+145 && mouse_y>ye+50+(n*30) && mouse_y<ye+80+(n*30))
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
show_type_midi(1686+n, tcmp);
Action.DrawOutline(CouleurBlind);
}


}
}


petitchiffre.Print("FADER",xe+10,ye+218);
Rect FBox(Vec2D(xe+70,ye+200),Vec2D(45,35));
FBox.SetRoundness(5);
FBox.DrawOutline(CouleurLigne.WithAlpha(0.5));

neuro.Print(ol::ToString(echo_pointing_fader_num[echo_selected]),xe+80,ye+220);

if(window_focus_id==W_ECHO && mouse_x>xe+70 && mouse_x<xe+115 && mouse_y>ye+200 && mouse_y<ye+235)
{
FBox.DrawOutline(CouleurLigne);

}

////AFFECT TO DOCK
Rect Affecttodock(Vec2D(xe+10,ye+245), Vec2D(110,20));
Affecttodock.SetRoundness(7.5);
if(index_affect_echo_to_dock==1){Affecttodock.Draw(CouleurFader);}
Affecttodock.DrawOutline(CouleurLigne.WithAlpha(0.5));

petitchiffre.Print( "Affect To Dock",(xe+20), (ye+258));





//manipulate channel params

//ECHO ACTION PANNEL
Rect ActionTyp(Vec2D(xe+500,ye+10),Vec2D(70,20));
ActionTyp.SetRoundness(4);


switch(echo_channel_manipulate_mode[echo_selected])
{
case 0:
     ActionTyp.Draw(Discrete8);
     petitchiffre.Print("CH.LEVEL",xe+507,ye+22);
     sprintf(tcmp,"CH.LEVEL");
break;
case 1:
     ActionTyp.Draw(Discrete2);
     petitchiffre.Print("CH.GRND",xe+507,ye+22);
     sprintf(tcmp,"CH.GROUND");
break;
default: break;
}

ActionTyp.DrawOutline(CouleurLigne.WithAlpha(0.5));


if(window_focus_id==W_ECHO && mouse_x>xe+500 && mouse_x<xe+570 && mouse_y>ye+10&& mouse_y<ye+30)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
show_type_midi(1696, tcmp);
ActionTyp.DrawOutline(CouleurBlind);
}
}





Echo_Aera(xe+155,ye+95);


Rect Frame(Vec2D(xe+185,ye+255),Vec2D(127,10));
float tmp_lev=0;


Circle BMidiOut(xe+316,ye+255, 5);


char mid_lev[8];
for (int cl=0;cl<3;cl++)
{
tmp_lev=echo_global_params[echo_selected][cl];
switch(cl)
{
 case 0:
 sprintf(tcmp,"Gravity:     %.2f",tmp_lev);
 break;
 case 1:
 sprintf(tcmp,"Mass:        %.2f",tmp_lev);
 break;
 case 2:
 sprintf(tcmp,"Energy: %.2f",tmp_lev);
 break;
 default:
  //sab 02/03/2014 sprintf(tcmp,"");
  strcpy(tcmp,"");
 break;
}
sprintf(mid_lev,"%d",(int)(tmp_lev*127));
Rect LevelF(Vec2D(xe+155+(cl*180),ye+255),Vec2D(tmp_lev*127,10));
LevelF.Draw(Discrete8);
Frame.MoveTo(Vec2D(xe+155+(cl*180),ye+255));
Frame.DrawOutline(CouleurLigne.WithAlpha(0.5));
petitchiffre.Print(tcmp,xe+155+(cl*180),ye+248);
BMidiOut.MoveTo(Vec2D(xe+295+(cl*180),ye+265));
if(midi_send_out[1693+cl]==1)
{
BMidiOut.Draw(CouleurBlind);
}
BMidiOut.DrawOutline(CouleurGrisMoyen);
petitchiffrerouge.Print(mid_lev,xe+286+(cl*180),ye+252);

if(window_focus_id==W_ECHO && mouse_x>=xe+155+(cl*180) && mouse_x<=xe+285+(cl*180) && mouse_y>=ye+255 && mouse_y<=ye+265)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
show_type_midi(1693+cl, tcmp);
Frame.DrawOutline(CouleurBlind);
}

}


}



return(0);
}
