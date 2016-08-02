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

* \file banger_visu_8.cpp
* \brief {Bangers GUI fonctions}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gestion des fonctions de la fenetre des banger
*
*   Bangers GUI fonctions
*
 **/

int alarm_window()
{
Rect windowAlarm(Vec2D(XAlarm,YAlarm),Vec2D(300,110));
windowAlarm.SetRoundness(15);
windowAlarm.SetLineWidth(triple_epaisseur_ligne_fader);
windowAlarm.Draw(CouleurFond);
windowAlarm.Draw(CouleurBlind.WithAlpha(alpha_blinker));
if(window_focus_id==918)
{windowAlarm.DrawOutline(CouleurFader);}
else{windowAlarm.DrawOutline(CouleurLigne);}
char title_alarm[32];
sprintf(title_alarm,"Alarm from banger number %d",index_alarm_from_banger_num+1);
neuromoyen.Print(title_alarm,XAlarm+80,YAlarm+30);
neuro.Print(string_THE_alarm,XAlarm+20,YAlarm+80);

return(0);
}


int feedback_banger(int xvis, int yvis)
{
char over_banger_is[64];
int banger_overoll=0;
for (int nb=0;nb<8;nb++)
{
for (int lb=0;lb<16;lb++)
{
if((nb)+(lb*8)<core_user_define_nb_bangers)
{
Circle BangerFeedback(Vec2D(xvis+(nb*12)+30,yvis+(lb*12)+30),5);
BangerFeedback.DrawOutline(CouleurLigne.WithAlpha(0.5));
if(bang_is_sended[(nb)+(lb*8)]==0 && (((nb)+(lb*8))<127))//évenement pas encore fini dans son éxécution
{
BangerFeedback.Draw(CouleurBlind.WithAlpha(alpha_blinker));
}


if(window_focus_id==W_BANGER &&  mouse_x>xvis+(nb*12)+25 && mouse_x<xvis+(nb*12)+35 && mouse_y>yvis+(lb*12)+25 && mouse_y<yvis+(lb*12)+35)
{
banger_overoll=(nb)+(lb*8);
if(banger_overoll<127)
{
if( Midi_Faders_Affectation_Type!=0)//config midi
{
BangerFeedback.SetLineWidth(2.0);
BangerFeedback.DrawOutline(CouleurBlind);
char desc_midi_bg[24];
sprintf(desc_midi_bg,"Banger %d",banger_overoll+1);
show_type_midi(1343+banger_overoll,desc_midi_bg );
}
else{BangerFeedback.DrawOutline(CouleurLigne);}

}
}
}
}
}

for(int p=0;p<16;p++)
{
sprintf(over_banger_is,"%d",(p*8)+1);
petitpetitchiffrerouge.Print(over_banger_is,xvis,(yvis+p*12)+35);
}

if(banger_overoll<127)
{
sprintf(over_banger_is,"BANGER %d",banger_overoll+1);
petitpetitchiffre.Print(over_banger_is,xvis,yvis+10);

sprintf(over_banger_is, bangers_name[banger_overoll]);
petitpetitchiffre.Print(over_banger_is,xvis,yvis+20);
}
sprintf(over_banger_is,"Last bang sended: %d",last_banger_sended_manually+1);
petitpetitchiffre.Print(over_banger_is,xvis,yvis+230);
 return(0);
}

int fenetre_banger(int xb,int yb)
{

Rect bang_backg(Vec2D(xb,yb), Vec2D(size_X_Banger,size_Y_Banger));
bang_backg.SetRoundness(15);
bang_backg.SetLineWidth(triple_epaisseur_ligne_fader);
bang_backg.Draw(CouleurFond);
if(window_focus_id==917)
{
bang_backg.DrawOutline(CouleurFader);
}
else
{
 bang_backg.DrawOutline(CouleurLigne);
}

char numev[12]; //car delay dans les parages

neuro.Print( "Banger",(xb+110), (yb+30));
sprintf(numev,"%d",index_banger_selected+1);
neuro.Print(numev,(xb+200), (yb+30));

Rect BangNumBox(Vec2D(xb+190,yb+10),Vec2D(50,25));
BangNumBox.SetRoundness(5);
BangNumBox.DrawOutline(CouleurLigne.WithAlpha(0.3));

if( window_focus_id==917 && mouse_x>xb+190 && mouse_x<xb+240 && mouse_y>yb+10 && mouse_y<yb+35)
{
BangNumBox.DrawOutline(CouleurLigne);
}

Rect GiveNameOfBanger(Vec2D(xb+200,yb+40), Vec2D( 170,30));
GiveNameOfBanger.SetRoundness(7.5);
GiveNameOfBanger.Draw(CouleurSurvol);

petitchiffre.Print( bangers_name[index_banger_selected],(xb+205), (yb+60));

//UP DOWN bangers number selected
Circle BangerPlus(Vec2D(xb+160,yb+55),12);
Circle BangerMinus(Vec2D(xb+120,yb+55),12);

petitchiffre.Print("-",xb+115,yb+58);
petitchiffre.Print("+",xb+155,yb+58);
BangerPlus.DrawOutline(CouleurLigne);
BangerMinus.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0)//config midi
{
if( mouse_x>xb+108 && mouse_x<xb+132 && mouse_y>yb+43 && mouse_y<yb+67)
{BangerMinus.DrawOutline(CouleurBlind);}
if(mouse_x>xb+148 && mouse_x<xb+172 && mouse_y>yb+43 && mouse_y<yb+67)
{BangerPlus.DrawOutline(CouleurBlind);}
}

//COPY TO////////////////////////////////

Rect CopyTo( Vec2D((xb+280),(yb+10)),Vec2D(90,20));
CopyTo.SetRoundness(7.5);
if(index_copy_banger==1)
{
CopyTo.Draw(CouleurBlind.WithAlpha(alpha_blinker));
}
CopyTo.DrawOutline(CouleurLigne.WithAlpha(0.4));
petitchiffre.Print("Copy To",xb+300 ,yb+22);


//////////////EDIT MODE

Rect BangerEditEnable( Vec2D((xb+410),(yb+10)),Vec2D(50,20));
BangerEditEnable.SetRoundness(7.5);
if(index_enable_edit_banger==1)
{
BangerEditEnable.Draw(CouleurFader);
}
BangerEditEnable.DrawOutline(CouleurLigne);
petitchiffre.Print("edit",xb+420 ,yb+22);

/////////////LOOP ON
Rect BangerLoop( Vec2D((xb+490),(yb+10)),Vec2D(50,20));
BangerLoop.SetRoundness(7.5);
BangerLoop.Draw(CouleurBlind.WithAlpha(alpha_blinker*do_loop_banger[index_banger_selected]));
BangerLoop.DrawOutline(CouleurLigne);
petitchiffre.Print("LOOP!",xb+497 ,yb+23);

Rect BangerTimeLoop( Vec2D((xb+550),(yb+10)),Vec2D(50,20));
BangerTimeLoop.SetRoundness(5);
BangerTimeLoop.Draw(CouleurBleuProcedure);
BangerTimeLoop.DrawOutline(CouleurLigne);
petitchiffre.Print(ol::ToString(time_loop_banger[index_banger_selected]),xb+555 ,yb+23);

//BANG DO IT
Rect BangerIt( Vec2D((xb+410),(yb+40)),Vec2D(60,30));
BangerIt.SetRoundness(7.5);
if(bang_is_sended[index_banger_selected]==0)//si banger en cours de defilement
{
if(index_banger_selected!=Banger_Memoire[position_preset] || (index_banger_selected==Banger_Memoire[position_preset] && index_crossfading==1))
{BangerIt.Draw(CouleurFader.WithAlpha(alpha_blinker));}
}
if(do_light_bang_it==1){BangerIt.Draw(CouleurFader);do_light_bang_it=0;}
BangerIt.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0 )//config midi
{
if(mouse_x>(xb+410) && mouse_x<(xb+460) && mouse_y>(yb+40) && mouse_y<(yb+70))
{BangerIt.DrawOutline(CouleurBlind);}
}
petitchiffre.Print("Bang it !",xb+420 ,yb+59);

petitchiffre.Print("Ev.Type",xb+30,yb+90);
petitchiffre.Print("Action",xb+150,yb+90);
petitchiffre.Print("Val 1",xb+275,yb+90);
petitchiffre.Print("Val 2",xb+325,yb+90);
petitchiffre.Print("Delay",xb+385,yb+90);

char bangers_type_affiche[16];
char bangers_type_action[25];//garder 25 car recopie dedans du texte descriptif


Rect BangEvent(Vec2D(xb,yb),Vec2D(100,20));

Rect BangAction(Vec2D(xb,yb),Vec2D(115,20));

Rect BoxVal1(Vec2D(xb,yb),Vec2D(40,20));

Rect BoxVal2(Vec2D(xb,yb),Vec2D(40,20));

Rect BoxDelay(Vec2D(xb,yb),Vec2D(40,20));

for (int lp=0;lp<6;lp++)//6 ev en bang
{
BangEvent.MoveTo(Vec2D(xb+30,yb+100+(lp*30)));
BangEvent.SetRoundness(5);
BangEvent.Draw(CouleurBleuProcedure);

BangAction.MoveTo(Vec2D(xb+145,yb+100+(lp*30)));
BangAction.SetRoundness(5);
BangAction.Draw(CouleurBleuProcedure);

BoxVal1.MoveTo(Vec2D(xb+270,yb+100+(lp*30)));
BoxVal1.SetRoundness(5);
BoxVal1.Draw(CouleurBleuProcedure);

BoxVal2.MoveTo(Vec2D(xb+320,yb+100+(lp*30)));
BoxVal2.SetRoundness(5);
BoxVal2.Draw(CouleurBleuProcedure);

BoxDelay.MoveTo(Vec2D(xb+380,yb+100+(lp*30)));
BoxDelay.SetRoundness(5);
BoxDelay.Draw(CouleurBleuProcedure);

Circle Bangsolo(Vec2D(xb+450,yb+110+(lp*30)),10);

if(event_sended[index_banger_selected][lp]==1 &&  bang_is_sended[index_banger_selected]==0)
{
Bangsolo.Draw(CouleurSurvol);
}
if(do_light_bang_solo[lp]==1){Bangsolo.Draw(CouleurFader);do_light_bang_solo[lp]=0;}
Bangsolo.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0 )//config midi
{
if(mouse_x>xb+440 && mouse_x<xb+460 && mouse_y>yb+100+(lp*30) && mouse_y<yb+120+(lp*30))
{
Bangsolo.DrawOutline(CouleurBlind);
}
}


sprintf(numev,"%d",lp+1);
petitpetitchiffre.Print(numev,xb+10,yb+110+(lp*30));
//au dessus type ev
if(window_focus_id==W_BANGER && index_enable_edit_banger==1)
{

if( mouse_x>xb+30 && mouse_x<xb+130 && mouse_y>yb+100+(lp*30) && mouse_y<yb+120+(lp*30) )
{

editing_banger_family=1;editing_banger_action=0;
BangEvent.DrawOutline(CouleurLigne.WithAlpha(0.5));
over_banger_event=lp+1;
over_family=0;
}
//change type action
else if(mouse_x>xb+150 && mouse_x<xb+250 && mouse_y>yb+100+(lp*30) && mouse_y<yb+120+(lp*30) )
{
BangAction.DrawOutline(CouleurLigne.WithAlpha(0.5));

editing_banger_action=1;editing_banger_family=0;
over_banger_action=lp+1;
over_family=1;
}

}


petitpetitchiffre.Print(ol::ToString(over_banger_event),xb+30,yb+60);
petitpetitchiffre.Print(ol::ToString(over_banger_action),xb+60,yb+60);

//affichage genres types
switch(bangers_type[index_banger_selected][lp])
{
case 0:
     sprintf(bangers_type_affiche,"-");
     sprintf(bangers_type_action,"-");
break;
case 1:
     sprintf(bangers_type_affiche,"Faders");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"Lock");
     break;
     case 1:
     sprintf(bangers_type_action,"Up");
     break;
     case 2:
     sprintf(bangers_type_action,"Down");
     break;
     case 3:
     sprintf(bangers_type_action,"Saw");
     break;
     case 4:
     sprintf(bangers_type_action,"To Prev.Dock");
     break;
     case 5:
     sprintf(bangers_type_action,"To Next Dock");
     break;
     case 6:
     sprintf(bangers_type_action,"Up/Down loop");
     break;
     case 7:
     sprintf(bangers_type_action,"Set Dock Looped");
     break;
     case 8:
     sprintf(bangers_type_action,"Set All Looped");
     break;
     case 9:
     sprintf(bangers_type_action,"Set Dock Is");
     break;
     case 10:
     sprintf(bangers_type_action,"Set LFO at");
     break;
     case 11:
     sprintf(bangers_type_action,"Set Fader at");
     break;
     case 12:
     sprintf(bangers_type_action,"SetStopPos at");
     break;
     case 13:
     sprintf(bangers_type_action,"StopPos ON/OFF");
     break;
     case 14:
     sprintf(bangers_type_action,"Paste to Seq.");
     break;
     case 15:
     sprintf(bangers_type_action,"Fader MidiOut");
     break;
     case 16:
     sprintf(bangers_type_action,"ALL  : Faders at 0");
     break;
     case 17:
     sprintf(bangers_type_action,"ALL  : Speed at 0");
     break;
     case 18:
     sprintf(bangers_type_action,"ALL  : Lock at 0");
     break;
     case 19:
     sprintf(bangers_type_action,"ALL  : LFO at 0");
     break;
     case 20:
     sprintf(bangers_type_action,"ALL  : Loop at 0");
     break;
     case 21:
     sprintf(bangers_type_action,"ALL  : All at 0");
     break;
     case 22:
     sprintf(bangers_type_action,"ALL  : MidiOut at 0");
     break;
     case 23:
     sprintf(bangers_type_action,"ALL : RECALL");
     break;
     case 24:
     sprintf(bangers_type_action,"Lock Preset");
     break;
     case 25:
     sprintf(bangers_type_action,"Fader: Set Curve");
     break;
     case 26:
     sprintf(bangers_type_action,"Fader: LoadChaser");
     break;
     case 27:
     sprintf(bangers_type_action,"Fader: PlayChaser");
     break;
     case 28:
     sprintf(bangers_type_action,"Fader: SeekChaser");
     break;
     case 29:
     sprintf(bangers_type_action,"Fader: LoopChaser");
     break;
     case 30:
     sprintf(bangers_type_action,"Fader: Autol.Chaser");
     break;
     case 31:
     sprintf(bangers_type_action,"Fader: Set DCH.");
     break;
     case 32:
     sprintf(bangers_type_action,"Fader: SetCH Full");
     break;
     case 33:
     sprintf(bangers_type_action,"Fader: SetCH 0");
     break;
     case 34:
     sprintf(bangers_type_action,"Damper On/Off");
     break;
     case 35:
     sprintf(bangers_type_action,"Damper SetDecay");
     break;
     case 36:
     sprintf(bangers_type_action,"Damper SetDelta");
     break;
     case 37:
     sprintf(bangers_type_action,"Damper Mode");
     break;
     case 38:
     sprintf(bangers_type_action,"Dock --");
     break;
     case 39:
     sprintf(bangers_type_action,"Dock ++");
     break;
     case 40://FX MODE
     sprintf(bangers_type_action,"FX mode");
     break;
     case 41://buffer
     sprintf(bangers_type_action,"Render Buffer");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
case 2:
     sprintf(bangers_type_affiche,"Send Midi");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"Key-On V:127");
     break;
     case 1:
     sprintf(bangers_type_action,"Key-On V:0");
     break;
     case 2:
     sprintf(bangers_type_action,"Key-Off V:127");
     break;
     case 3:
     sprintf(bangers_type_action,"Ctrl-Change V:127");
     break;
     case 4:
     sprintf(bangers_type_action,"Ctrl-Change V:0");
     break;
     case 5:
     sprintf(bangers_type_action,"Ctrl-Change Ch:0");
     break;
     case 6:
     sprintf(bangers_type_action,"Ctrl-Change Ch:1");
     break;
     case 7:
     sprintf(bangers_type_action,"Ctrl-Change Ch:2");
     break;
     case 8:
     sprintf(bangers_type_action,"Ctrl-Change Ch:3");
     break;
     case 9:
     sprintf(bangers_type_action,"Ctrl-Change Ch:4");
     break;
     case 10:
     sprintf(bangers_type_action,"Ctrl-Change Ch:5");
     break;
     case 11:
     sprintf(bangers_type_action,"Ctrl-Change Ch:6");
     break;
     case 12:
     sprintf(bangers_type_action,"Ctrl-Change Ch:7");
     break;
     case 13:
     sprintf(bangers_type_action,"Ctrl-Change Ch:8");
     break;
     case 14:
     sprintf(bangers_type_action,"Ctrl-Change Ch:9");
     break;
     case 15:
     sprintf(bangers_type_action,"Ctrl-Change Ch:10");
     break;
     case 16:
     sprintf(bangers_type_action,"Ctrl-Change Ch:11");
     break;
     case 17:
     sprintf(bangers_type_action,"Ctrl-Change Ch:12");
     break;
     case 18:
     sprintf(bangers_type_action,"Ctrl-Change Ch:13");
     break;
     case 19:
     sprintf(bangers_type_action,"Ctrl-Change Ch:14");
     break;
     case 20:
     sprintf(bangers_type_action,"Ctrl-Change Ch:15");
     break;
     case 21:
     sprintf(bangers_type_action,"Set Faders/Sp Out");
     break;
     case 22:
     sprintf(bangers_type_action,"Set ChasersTr Out");
     break;
     case 23:
     sprintf(bangers_type_action,"Re-emit ALL Out");
     break;
     case 24:
     sprintf(bangers_type_action,"MidiClock ON");
     break;
     case 25:
     sprintf(bangers_type_action,"MidiClock OFF");
     break;
     case 26:
     sprintf(bangers_type_action,"MidiClock RATE");
     break;
     case 27:
     sprintf(bangers_type_action,"Msg START");
     break;
     case 28:
     sprintf(bangers_type_action,"Msg STOP");
     break;
     case 29:
     sprintf(bangers_type_action,"Msg CONTINUE");
     break;
     case 30:
     sprintf(bangers_type_action,"Send Prg Change");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
case 3:
     sprintf(bangers_type_affiche,"Windows");
          switch(bangers_action[index_banger_selected][lp])
     {
     case 1:
     sprintf(bangers_type_action,"Sequences");
     break;
     case 2:
     sprintf(bangers_type_action,"Fader space");
     break;
     case 3:
     sprintf(bangers_type_action,"MiniFaders");
     break;
     case 4:
     sprintf(bangers_type_action,"Banger");
     break;
     case 5:
     sprintf(bangers_type_action,"Audio Players");
     break;
     case 6:
     sprintf(bangers_type_action,"Time Window");
     break;
     case 7:
     sprintf(bangers_type_action,"Plot Window");
     break;
     case 8:
     sprintf(bangers_type_action,"List Window");
     break;
     case 9:
     sprintf(bangers_type_action,"Trichromy");
     break;
     case 10:
     sprintf(bangers_type_action,"Video-tracking");
     break;
     case 11:
     sprintf(bangers_type_action,"Chasers Window");
     break;
     case 12:
     sprintf(bangers_type_action,"GridPlayers");
     break;
     case 13:
     sprintf(bangers_type_action,"Draw Window");
     break;
     case 14:
     sprintf(bangers_type_action,"Echo Window");
     break;
     case 15:
     sprintf(bangers_type_action,"Mover Window");
     break;
     case 16:
     sprintf(bangers_type_action,"NumPad Window");
     break;
     case 17:
     sprintf(bangers_type_action,"CFG MENU");
     break;
     case 18:
     sprintf(bangers_type_action,"iCAT Builder");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
case 4:
     sprintf(bangers_type_affiche,"Alarm");
     sprintf(bangers_type_action,string_alarm[index_banger_selected]);
break;
case 5:
     sprintf(bangers_type_affiche,"AudioPlayers");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"Clear Player");
     break;
     case 1:
     sprintf(bangers_type_action,"Load in Player");
     break;
     case 2:
     sprintf(bangers_type_action,"SetPlay Player");
     break;
     case 3:
     sprintf(bangers_type_action,"Load & Play");
     break;
     case 4:
     sprintf(bangers_type_action,"SetLoop Player");
     break;
     case 5:
     sprintf(bangers_type_action,"Seek Player");
     break;
     case 6:
      sprintf(bangers_type_action,"SetVolume Player");
     break;
     case 7:
     sprintf(bangers_type_action,"Set Cue Player");
     break;
     case 8:
     sprintf(bangers_type_action,"Seek to CueIn Pl.");
     break;
     case 9:
      sprintf(bangers_type_action,"SetPan Player");
     break;
     case 10:
     sprintf(bangers_type_action,"SetPitch Player");
     break;
     case 11:
     sprintf(bangers_type_action,"Prev.Tr. Player");
     break;
     case 12:
     sprintf(bangers_type_action,"Next.Tr. Player");
     break;
     case 13:
     sprintf(bangers_type_action,"AutoLoad Player");
     break;
     case 14:
     sprintf(bangers_type_action,"AutoPause Player");
     break;
     case 15:
     sprintf(bangers_type_action,"SetMidiOut Player");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
case 6:
     sprintf(bangers_type_affiche,"Sequences");
     switch(bangers_action[index_banger_selected][lp])
     {
      case 0://stage jump
      sprintf(bangers_type_action,"SetMem onStage");
      break;
      case 1://preset jump
      sprintf(bangers_type_action,"SetMem onPreset");
      break;
      case 2://set Speed
      sprintf(bangers_type_action,"SetSpeed at");
      break;
      case 3://Set Link
      sprintf(bangers_type_action,"SetLink On");
      break;
      case 4://Set Banger
      sprintf(bangers_type_action,"SetBanger On");
      break;
      case 5://refresh
      sprintf(bangers_type_action,"Reload Stage");
      break;
      case 6://refresh
      sprintf(bangers_type_action,"Reload Preset");
      break;
      case 7://refresh
      sprintf(bangers_type_action,"GO");
      break;
      case 8://set Blind
      sprintf(bangers_type_action,"Set Blind");
      break;
      default:
      sprintf(bangers_type_action,"-");
      break;
     }

break;

case 7:
     sprintf(bangers_type_affiche,"Chasers");
     switch(bangers_action[index_banger_selected][lp])
     {
      case 0://call num chaser
      sprintf(bangers_type_action,"Ch.Sel. Is");
      break;
      case 1://play chaser
      sprintf(bangers_type_action,"Play");
      break;
      case 2://seek chaser
      sprintf(bangers_type_action,"Seek");
      break;
      case 3://loop chaser
      sprintf(bangers_type_action,"Loop");
      break;
      case 4://way chaser
      sprintf(bangers_type_action,"Way");
      break;
      case 5://aller retour chaser
      sprintf(bangers_type_action,"Aller-Retour");
      break;
      case 6://timemode
      sprintf(bangers_type_action,"Time Mode");
      break;
      case 7://slaviness
      sprintf(bangers_type_action,"Slave");
      break;
      case 8://Beg P
      sprintf(bangers_type_action,"Set Beg Point");
      break;
      case 9://End P
      sprintf(bangers_type_action,"Set End Point");
      break;
      case 10://Position
      sprintf(bangers_type_action,"Set Position");
      break;
      case 11://toggle track
      sprintf(bangers_type_action,"Toggle Track");
      break;
      case 12://ALL ON OFF
      sprintf(bangers_type_action,"ALL ON");
      break;
      case 13://INV ON OFF
      sprintf(bangers_type_action,"ON INV");
      break;
      case 14://ALL OFF
      sprintf(bangers_type_action,"ALL OFF");
      break;
      case 15://call preset
      sprintf(bangers_type_action,"ON Preset");
      break;
      case 16://level track
      sprintf(bangers_type_action,"Ch.Sel. Level Track");
      break;
      default:
      sprintf(bangers_type_action,"-");
      break;
      }
break;
case 8:
     sprintf(bangers_type_affiche,"MiniFaders");
     switch(bangers_action[index_banger_selected][lp])
     {
      case 0:
      sprintf(bangers_type_action,"Select Num.");
      break;
      case 1:
      sprintf(bangers_type_action,"Select All");
      break;
      case 2:
      sprintf(bangers_type_action,"Sel. Flash");
      break;
      case 3:
      sprintf(bangers_type_action,"Sel. Tog.Lock");
      break;
      case 4:
      sprintf(bangers_type_action,"Sel. Tog.Loop");
      break;
      case 5:
      sprintf(bangers_type_action,"Sel. Tog.Up");
      break;
      case 6:
      sprintf(bangers_type_action,"Sel. Tog.Down");
      break;
      case 7:
      sprintf(bangers_type_action,"Sel. Tog.Saw");
      break;
      case 8:
      sprintf(bangers_type_action,"Sel. Tog. AllLoop");
      break;
      case 9:
      sprintf(bangers_type_action,"Sel. AllAt");
      break;
      case 10:
      sprintf(bangers_type_action,"Sel. Tog.StopPos.");
      break;
      case 11:
      sprintf(bangers_type_action,"Sel. ToPrev");
      break;
      case 12:
      sprintf(bangers_type_action,"Sel. ToNext");
      break;
      case 13:
      sprintf(bangers_type_action,"Sel. Tog.Up/Down");
      break;
      case 14:
      sprintf(bangers_type_action,"Sel. Dock -");
      break;
      case 15:
      sprintf(bangers_type_action,"Sel. Dock +");
      break;
      case 16:
      sprintf(bangers_type_action,"Sel. PlayChaser");
      break;
      case 17:
      sprintf(bangers_type_action,"Minifader Preset");
      break;
      default:
      sprintf(bangers_type_action,"-");
      break;
      }
break;
case 9:
     sprintf(bangers_type_affiche,"iCat");
     switch(bangers_action[index_banger_selected][lp])
     {
      case 0:
      sprintf(bangers_type_action,"Select Page Num");
      break;
      case 1:
      sprintf(bangers_type_action,"Select Page -");
      break;
      case 2:
      sprintf(bangers_type_action,"Select Page +");
      break;
      case 3:
      sprintf(bangers_type_action,"Refresh Page");
      break;
      case 4:
      sprintf(bangers_type_action,"Toggle Orientation");
      break;
      default:
      sprintf(bangers_type_action,"-");
      break;
      }
break;
case 10: //chrono
    sprintf(bangers_type_affiche,"Chrono");
     switch(bangers_action[index_banger_selected][lp])
     {
      case 0:
      sprintf(bangers_type_action,"Clear Chrono");
      break;
      case 1:
      sprintf(bangers_type_action,"Play Chrono");
      break;
      case 2:
      sprintf(bangers_type_action,"Set Chrono Page");
      break;
      default:
      sprintf(bangers_type_action,"-");
      break;
      }
break;
case 11://set channel
    sprintf(bangers_type_affiche,"SetChannel");
     switch(bangers_action[index_banger_selected][lp])
     {
      case 0:
      sprintf(bangers_type_action,"/100 Set At");
      break;
      case 1:
      sprintf(bangers_type_action,"/100 Set +");
      break;
      case 2:
      sprintf(bangers_type_action,"/100 Set -");
      break;
      case 3:
      sprintf(bangers_type_action,"/255 Set At");
      break;
      case 4:
      sprintf(bangers_type_action,"/255 Set +");
      break;
      case 5:
      sprintf(bangers_type_action,"/255 Set -");
      break;
      case 6:
      sprintf(bangers_type_action,"Macro ON");
      break;
      case 7:
      sprintf(bangers_type_action,"Macro OFF");
      break;
      case 8:
      sprintf(bangers_type_action,"FromTo Macro1 ON");
      break;
      case 9:
      sprintf(bangers_type_action,"FromTo Macro2 ON");
      break;
      case 10:
      sprintf(bangers_type_action,"FromTo Macro3 ON");
      break;
      case 11:
      sprintf(bangers_type_action,"FromTo Macro4 ON");
      break;
      case 12:
      sprintf(bangers_type_action,"FromTo Macro1 OFF");
      break;
      case 13:
      sprintf(bangers_type_action,"FromTo Macro2 OFF");
      break;
      case 14:
      sprintf(bangers_type_action,"FromTo Macro3 OFF");
      break;
      case 15:
      sprintf(bangers_type_action,"FromTo Macro4 OFF");
      break;
      default:
      sprintf(bangers_type_action,"-");
      break;
      }
break;

case 12://set banger
     sprintf(bangers_type_affiche,"SetBanger");
     switch(bangers_action[index_banger_selected][lp])
     {
      case 0:
      sprintf(bangers_type_action,"On/Off");
      break;
      case 1:
      sprintf(bangers_type_action,"RollBack");
      break;
      case 2:
      sprintf(bangers_type_action,"Loop ON");
      break;
      case 3:
      sprintf(bangers_type_action,"Loop OFF");
      break;
      default:
      break;
      }

break;

case 13://midi mute
     sprintf(bangers_type_affiche,"MidiMute");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"[GLOBAL]");
     break;
     case 1:
     sprintf(bangers_type_action,"GrandMaster");
     break;
     case 2:
     sprintf(bangers_type_action,"Fader");
     break;
     case 3:
     sprintf(bangers_type_action,"LFO");
     break;
     case 4:
     sprintf(bangers_type_action,"Sequences");
     break;
     case 5:
     sprintf(bangers_type_action,"Trichromy");
     break;
     case 6:
     sprintf(bangers_type_action,"VideoTracking");
     break;
     case 7:
     sprintf(bangers_type_action,"Audio Level");
     break;
     case 8:
     sprintf(bangers_type_action,"Audio Pan");
     break;
     case 9:
     sprintf(bangers_type_action,"Audio Pitch");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
case 14://Grid
sprintf(bangers_type_affiche,"GridPlayer");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"1-Load&Play");
     break;
     case 1:
     sprintf(bangers_type_action,"2-Load&Play");
     break;
     case 2:
     sprintf(bangers_type_action,"3-Load&Play");
     break;
     case 3:
     sprintf(bangers_type_action,"4-Load&Play"); //grid step
     break;
     case 4:
     sprintf(bangers_type_action,"1-Stop&Load");    //grid step
     break;
     case 5:
     sprintf(bangers_type_action,"2-Stop&Load");
     break;
     case 6:
     sprintf(bangers_type_action,"3-Stop&Load");
     break;
     case 7:
     sprintf(bangers_type_action,"4-Stop&Load");
     break;
     case 8:
     sprintf(bangers_type_action,"Play/Pause");   //Player ON/OFF
     break;
     case 9:
     sprintf(bangers_type_action,"Seek");     //bang
     break;
     case 10:
     sprintf(bangers_type_action,"Autostop");
     break;
     case 11:
     sprintf(bangers_type_action,"Macro Goto");
     break;
     case 12:
     sprintf(bangers_type_action,"Macro Seek");
     break;
     case 13:
     sprintf(bangers_type_action,"Macro StopPlay");
     break;
     case 14:
     sprintf(bangers_type_action,"Set Seek");     //player seek
     break;
     case 15:
     sprintf(bangers_type_action,"Set Accel."); //player 0-127
     break;
     case 16:
     sprintf(bangers_type_action,"Set Slave"); //player ON/OFF
     break;
     case 17:
     sprintf(bangers_type_action,"SnapFader"); //player ON/OFF
     break;
     case 18:
     sprintf(bangers_type_action,"Next Step"); //GPL STP
     break;
     case 19:
     sprintf(bangers_type_action,"Previous Step"); //GPL Stp
     break;
     case 20:
     sprintf(bangers_type_action,"Goto=SeekStep"); //Goto position take seek step reference
     break;
     case 21:
     sprintf(bangers_type_action,"Def.as SeekSt."); //Actual step is define as seekstep
     break;
     case 22:
     sprintf(bangers_type_action,"Clear SeekSteps!"); //clear all seek steps
     break;
     case 23:
     sprintf(bangers_type_action,"Clear Grid in GPL !!!"); //clear all grid
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
case 15://Hardware
sprintf(bangers_type_affiche,"Hardware");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"Arduino ON/Off");
     break;
     case 1:
     sprintf(bangers_type_action,"Arduino Baudrate");
     break;
     case 2:
     sprintf(bangers_type_action,"Analog input ON");
     break;
     case 3:
     sprintf(bangers_type_action,"Rescan Midi");
     break;
     default:
     break;
     }
break;
case 16://emulate KBD
sprintf(bangers_type_affiche,"Emulate Kbd");
 switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"Kbd A");
     break;
     case 1:
     sprintf(bangers_type_action,"Kbd B");
     break;
     case 2:
     sprintf(bangers_type_action,"Kbd C");
     break;
     case 3:
     sprintf(bangers_type_action,"Kbd D");
     break;
      case 4:
     sprintf(bangers_type_action,"Kbd E");
     break;
      case 5:
     sprintf(bangers_type_action,"Kbd F");
     break;
      case 6:
     sprintf(bangers_type_action,"Kbd G");
     break;
      case 7:
     sprintf(bangers_type_action,"Kbd H");
     break;
      case 8:
     sprintf(bangers_type_action,"Kbd I");
     break;
      case 9:
     sprintf(bangers_type_action,"Kbd J");
     break;
      case 10:
     sprintf(bangers_type_action,"Kbd K");
     break;
      case 11:
     sprintf(bangers_type_action,"Kbd L");
     break;
      case 12:
     sprintf(bangers_type_action,"Kbd M");
     break;
      case 13:
     sprintf(bangers_type_action,"Kbd N");
     break;
      case 14:
     sprintf(bangers_type_action,"Kbd O");
     break;
      case 15:
     sprintf(bangers_type_action,"Kbd P");
     break;
      case 16:
     sprintf(bangers_type_action,"Kbd Q");
     break;
      case 17:
     sprintf(bangers_type_action,"Kbd R");
     break;
      case 18:
     sprintf(bangers_type_action,"Kbd S");
     break;
      case 19:
     sprintf(bangers_type_action,"Kbd T");
     break;
      case 20:
     sprintf(bangers_type_action,"Kbd U");
     break;
      case 21:
     sprintf(bangers_type_action,"Kbd V");
     break;
      case 22:
     sprintf(bangers_type_action,"Kbd W");
     break;
      case 23:
     sprintf(bangers_type_action,"Kbd X");
     break;
      case 24:
     sprintf(bangers_type_action,"Kbd Y");
     break;
      case 25:
     sprintf(bangers_type_action,"Kbd Z");
     break;

     case 26:
     sprintf(bangers_type_action,"Kbd SPACE");
     break;

     case 27:
     sprintf(bangers_type_action,"Kbd DOT");
     break;

      case 28:
     sprintf(bangers_type_action,"Kbd 0");
     break;
      case 29:
     sprintf(bangers_type_action,"Kbd 1");
     break;
      case 30:
     sprintf(bangers_type_action,"Kbd 2");
     break;
      case 31:
     sprintf(bangers_type_action,"Kbd 3");
     break;
      case 32:
     sprintf(bangers_type_action,"Kbd 4");
     break;
      case 33:
     sprintf(bangers_type_action,"Kbd 5");
     break;
      case 34:
     sprintf(bangers_type_action,"Kbd 6");
     break;
      case 35:
     sprintf(bangers_type_action,"Kbd 7");
     break;
      case 36:
     sprintf(bangers_type_action,"Kbd 8");
     break;
      case 37:
     sprintf(bangers_type_action,"Kbd 9");
     break;

      case 38:
     sprintf(bangers_type_action,"Kbd SHIFT");
     break;
      case 39:
     sprintf(bangers_type_action,"Kbd CTRL");
     break;
      case 40:
     sprintf(bangers_type_action,"Kbd ESC");
     break;
      case 41:
     sprintf(bangers_type_action,"Kbd F1");
     break;
      case 42:
     sprintf(bangers_type_action,"Kbd F2");
     break;
      case 43:
     sprintf(bangers_type_action,"Kbd F3");
     break;
      case 44:
     sprintf(bangers_type_action,"Kbd F4");
     break;
     case 45:
     sprintf(bangers_type_action,"Kbd F5");
     break;
     case 46:
     sprintf(bangers_type_action,"Kbd F6");
     break;
     case 47:
     sprintf(bangers_type_action,"Kbd F7");
     break;
     case 48:
     sprintf(bangers_type_action,"Kbd F8");
     break;
     case 49:
     sprintf(bangers_type_action,"Kbd F9");
     break;
     case 50:
     sprintf(bangers_type_action,"Kbd F10");
     break;
     case 51:
     sprintf(bangers_type_action,"Kbd F11");
     break;
     case 52:
     sprintf(bangers_type_action,"Kbd F12");
     break;
     case 53:
     sprintf(bangers_type_action,"Kbd ENTER");
     break;
     case 54:
     sprintf(bangers_type_action,"Kbd Bcksp");
     break;
     case 55:
     sprintf(bangers_type_action,"Kbd Tab");
     break;
     case 56:
     sprintf(bangers_type_action,"Kbd PLUS");
     break;
     case 57:
     sprintf(bangers_type_action,"Kbd MINUS");
     break;
     case 58:
     sprintf(bangers_type_action,"Kbd Arrow LEFT");
     break;
     case 59:
     sprintf(bangers_type_action,"Kbd Arrow RIGHT");
     break;
     case 60:
     sprintf(bangers_type_action,"Kbd Arrow UP");
     break;
     case 61:
     sprintf(bangers_type_action,"Kbd Arrow DOWN");
     break;
     case 62:
     sprintf(bangers_type_action,"Kbd Arrow DEL");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
//DRAW
case 17:
     sprintf(bangers_type_affiche,"Draw");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"Select Matrix");
     break;
     case 1:
     sprintf(bangers_type_action,"Set Brush");
     break;
     case 2:
     sprintf(bangers_type_action,"Set DrawMode");
     break;
     case 3:
     sprintf(bangers_type_action,"Set Pressure");
     break;
     case 4:
     sprintf(bangers_type_action,"Set Damper");
     break;
     case 5:
     sprintf(bangers_type_action,"Set Ghost");
     break;
     case 6:
     sprintf(bangers_type_action,"Set GPL");
     break;
     case 7:
     sprintf(bangers_type_action,"Set Offset");
     break;
     case 8:
     sprintf(bangers_type_action,"Clear Drawing");
     break;
     case 9:
     sprintf(bangers_type_action,"Snap Fader");
     break;
     case 10:
     sprintf(bangers_type_action,"Snap GridPl.");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;
case 18:
     sprintf(bangers_type_affiche,"Echo");
     switch(bangers_action[index_banger_selected][lp])
     {
     case 0:
     sprintf(bangers_type_action,"Select Echo");
     break;
     case 1:
     sprintf(bangers_type_action,"S.Set Fader");
     break;
     case 2:
     sprintf(bangers_type_action,"S.ChanMode ");
     break;
     case 3:
     sprintf(bangers_type_action,"S.SetChan /255");
     break;
     case 4:
     sprintf(bangers_type_action,"S.SetChan /100");
     break;
     case 5:
     sprintf(bangers_type_action,"S.Echo Mode");
     break;
     case 6:
     sprintf(bangers_type_action,"S.SnapFader");
     break;
     case 7:
     sprintf(bangers_type_action,"S.Bounce !");
     break;
     case 8:
     sprintf(bangers_type_action,"S. S-K-B !");
     break;
     case 9:
     sprintf(bangers_type_action,"S.BackFader");
     break;
     case 10:
     sprintf(bangers_type_action,"S.SetGravity");
     break;
     case 11:
     sprintf(bangers_type_action,"S.SetMass");
     break;
     case 12:
     sprintf(bangers_type_action,"S.SetEnergy");
     break;
     case 13:
     sprintf(bangers_type_action,"S.SetChanPos");
     break;
     case 14:
     sprintf(bangers_type_action,"E.EchoMode");
     break;
     case 15:
     sprintf(bangers_type_action,"E.SetFader");
     break;
     case 16:
     sprintf(bangers_type_action,"E.SnapFader");
     break;
     case 17:
     sprintf(bangers_type_action,"E.Bounce !");
     break;
     case 18:
     sprintf(bangers_type_action,"E. S-K-B !");
     break;
     case 19:
     sprintf(bangers_type_action,"E.BackFader");
     break;
     case 20:
     sprintf(bangers_type_action,"E.ChanMode");
     break;
     case 21:
     sprintf(bangers_type_action,"E.SetGravity");
     break;
     case 22:
     sprintf(bangers_type_action,"E.SetMass");
     break;
     case 23:
     sprintf(bangers_type_action,"E.SetEnergy");
     break;
     case 24:
     sprintf(bangers_type_action,"E.SetChanPos");
     break;
     case 25:
     sprintf(bangers_type_action,"E.ClearEcho");
     break;
     default:
     sprintf(bangers_type_action,"-");
     break;
     }
break;

case 19://WAVE
sprintf(bangers_type_affiche,"Wave");
switch(bangers_action[index_banger_selected][lp])
     {
     case 0://set controler_wave
     sprintf(bangers_type_action,"Set Slider");
     break;
     case 1://set pos brush
     sprintf(bangers_type_action,"Set Pos Brush");
     break;
     case 2://set channel preset
     sprintf(bangers_type_action,"Set Chan.Pr");
     break;
     case 3://set brush preset
     sprintf(bangers_type_action,"Set Brush Pr");
     break;
     case 4://set decay
     sprintf(bangers_type_action,"Set Decay");
     break;
     case 5://set delta
     sprintf(bangers_type_action,"Set Delta");
     break;
     case 6://set damper mode
     sprintf(bangers_type_action,"Set Damper Mod");
     break;
     case 7://clear slots
     sprintf(bangers_type_action,"Clear Wave");
     break;
     case 8://clear brush
     sprintf(bangers_type_action,"Clear Brush");
     break;
     case 9://clear buffer
     sprintf(bangers_type_action,"Clear Buffer");
     break;
     case 10://play
     sprintf(bangers_type_action,"Set Play");
     break;
     case 11://seek
     sprintf(bangers_type_action,"Seek");
     break;
     case 12://set BPM
     sprintf(bangers_type_action,"Set BPM");
     break;
     default:
     break;
     }
break;
default:
break;
}



petitchiffre.Print(bangers_type_affiche,xb+40,yb+113+(lp*30));


sprintf(numev,"%d",bangers_params[index_banger_selected][lp][0]);//val 1
petitchiffre.Print(numev,xb+275,yb+113+(lp*30));

//si alarme, pour voir bien le descriptif du texte
if(bangers_type[index_banger_selected][lp]==4)
{
Rect BoxAlarm(Vec2D(xb+145,yb+100+(lp*30)),Vec2D(170,20));
BoxAlarm.SetRoundness(5);
BoxAlarm.Draw(CouleurBleuProcedure);
}
petitchiffre.Print(bangers_type_action,xb+150,yb+113+(lp*30));
sprintf(numev,"%d",bangers_params[index_banger_selected][lp][1]);//val 2
petitchiffre.Print(numev,xb+325,yb+113+(lp*30));
sprintf(numev,"%.1f",bangers_delay[index_banger_selected][lp]);//delay
petitchiffre.Print(numev,xb+385,yb+113+(lp*30));

}


feedback_banger(xb+480,yb+50);
return(0);
}
