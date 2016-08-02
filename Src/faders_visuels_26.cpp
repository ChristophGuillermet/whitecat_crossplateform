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

* \file faders_visuels_26.cpp
* \brief {GUI fonctions for the faders}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour désiner la fenêtre des faders
*
*   Fonctions GUI to draw the faders windows
*
 **/

int fader_damper_commands(int _x,int _y, int fd)
{
Rect DB(Vec2D(_x, _y+20),Vec2D( 20,20 ));
DB.SetRoundness(4);
DB.DrawOutline(CouleurLigne.WithAlpha(0.5));
DB.Draw(CouleurBleuProcedure.WithAlpha(fader_damper_is_on[fd]));
DB.DrawOutline(CouleurLigne.WithAlpha(fader_damper_is_on[fd]));
neuro.Print("~",_x+5,_y+36);

Rect Lev(Vec2D(_x+30, _y+15),Vec2D( 127*(Fader_dampered[fd].getdecay()),12 ));
Rect Flev(Vec2D(_x+30, _y+15),Vec2D( 127,12 ));
Lev.Draw(CouleurConfig);
Flev.DrawOutline(CouleurLigne.WithAlpha(0.5));
minichiffregris.Print("Decay",_x+35,_y+24);
int f=127*Fader_dampered[fd].getdecay();
petitpetitchiffregris.Print(ol::ToString(f),_x+65,_y+24);

Rect levDt(Vec2D(_x+30, _y+35),Vec2D( 127*(Fader_dampered[fd].getdt()*10),12 ));
Rect FDt(Vec2D(_x+30, _y+35),Vec2D( 127,12 ));
levDt.Draw(CouleurConfig);
FDt.DrawOutline(CouleurLigne.WithAlpha(0.5));
minichiffregris.Print("Delta",_x+35,_y+43);
f=127*Fader_dampered[fd].getdt()*10;
petitpetitchiffregris.Print(ol::ToString(f),_x+65,_y+43);


Rect Mod(Vec2D(_x+137, _y),Vec2D( 20,10 ));
Mod.Draw(CouleurConfig.WithAlpha(fader_damper_is_on[fd]));
Mod.DrawOutline(CouleurLigne.WithAlpha(0.5));
minichiffregris.Print(ol::ToString(Fader_dampered[fd].getdampermode()),_x+146,_y+8);


button_midi_out_visu(_x+130,_y+65,fd+1960);//decaybutton_midi_out_visu(_x+150,_y+65,fd+1960);//decay
button_midi_out_visu(_x+150,_y+65,fd+2056);//dt
if(window_focus_id==W_FADERS && Midi_Faders_Affectation_Type!=0)
{
//ON OFF DAMPER
if( mouse_x>_x && mouse_x<_x+20 && mouse_y>_y+20 && mouse_y<_y+40)
{DB.DrawOutline(CouleurBlind);}

//DECAY CONSTANT OF DAMPER ON OFF
if( mouse_x>_x+30 && mouse_x<=_x+157 && mouse_y>_y+15 && mouse_y<_y+27)
{Flev.DrawOutline(CouleurBlind);}
//DET CONSTANT OF DAMPER ON OFF
if( mouse_x>_x+30 && mouse_x<=_x+157 && mouse_y>_y+35 && mouse_y<_y+47)
{FDt.DrawOutline(CouleurBlind);}
//Damper mode
if( mouse_x>_x+137 && mouse_x<_x+157 && mouse_y>_y && mouse_y<_y+10)
{Mod.DrawOutline(CouleurBlind);}
}
return(0);
}


int lfo_fader_functions (int cmptfader, int x, int y, int espacement)
{
    Rect GlobalBut(Vec2D(x, y),Vec2D( 25,25 ));//une seule décla pour un bouton // plus rapide !
    GlobalBut.SetRoundness(5);
    GlobalBut.SetLineWidth(epaisseur_ligne_fader);

//is dock for lfo selected ( do cycle )
    for (int dd=0; dd<core_user_define_nb_docks; dd++)
    {
        Circle SelectedOnLFO( x+(cmptfader*espacement)+150,y+10+(dd*40), 6);

        if (is_dock_for_lfo_selected[cmptfader][dd]==1)
        {
            SelectedOnLFO.Draw(CouleurFader);
        }
        SelectedOnLFO.DrawOutline(CouleurLigne);

    }

//Cadre bouton speed
    Rect LFOSpeedFrame(Vec2D(x+(cmptfader*espacement)-5, y+375),Vec2D( 137, 25) );
    LFOSpeedFrame.SetLineWidth(epaisseur_ligne_fader);
    LFOSpeedFrame.SetRoundness(5);
    LFOSpeedFrame.DrawOutline(CouleurLigne.WithAlpha(0.4));
    Rect LFOSpeed(Vec2D(x+(cmptfader*espacement)-5+lfo_speed[cmptfader], y+375),Vec2D( 10, 25) );
    LFOSpeed.SetLineWidth(tiers_epaisseur_ligne_fader);
    LFOSpeed.SetRoundness(5);
    Line (Vec2D(x+(cmptfader*espacement)+64,y+370),Vec2D(x+(cmptfader*espacement)+64,y+400)).Draw(CouleurLigne);
    petitchiffre.Print(ol::ToString(lfo_speed[cmptfader]-64),x+(cmptfader*espacement)+145,y+380);
    LFOSpeed.Draw(CouleurFader);
    LFOSpeed.DrawOutline(CouleurLigne);


    Circle BMidiOut( x+((cmptfader*espacement)+150),y+397, 10);//box du fader
    BMidiOut.SetLineWidth(epaisseur_ligne_fader);
    BMidiOut.Draw(CouleurBlind.WithAlpha(midi_send_out[cmptfader+196]));
    BMidiOut.DrawOutline(CouleurGrisMoyen);

    raccrochage_midi_visuel_horizontal ( x+(cmptfader*espacement), y+375, 196+cmptfader,127,25);

//SET STOP POSITION
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)-6, y+320));
//flash si affectation
    if(do_light_setpos[cmptfader]==1)
    {
        GlobalBut.Draw(CouleurBlind);
        do_light_setpos[cmptfader]=0;
    }
    GlobalBut.Draw(CouleurSurvol.WithAlpha(ActionnateStopOn[cmptfader]));
    GlobalBut.DrawOutline(CouleurLigne);
    petitpetitchiffre.Print("Stop",x+(cmptfader*espacement)-5,y+330);
    petitpetitchiffre.Print("Pos",x+(cmptfader*espacement-3),y+340);


//SET STOP POSITION GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)-6, y+320));
//UP    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+240));
//DOWN GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+280) );
//CYCLE SAW GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+320);

//UP
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+240));
    GlobalBut.DrawOutline(CouleurLigne);
//DOWN
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+280) );
    GlobalBut.DrawOutline(CouleurLigne);
//CYCLE SAW
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+320) );
    GlobalBut.DrawOutline(CouleurLigne);


    switch(lfo_mode_is[cmptfader])
    {
    case 1:
        GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+240));
        GlobalBut.Draw(CouleurFader);
        break;
    case 2:
        GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+280) );
        GlobalBut.Draw(CouleurFader);
        break;
    default:
        break;
    }
//SAW
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+320) );
    GlobalBut.Draw(CouleurFader.WithAlpha(lfo_cycle_is_on[cmptfader]));

//icones en vectoriel
//up
    Line(Vec2D(x+(cmptfader*espacement)+117,y+245),Vec2D(Vec2D(x+(cmptfader*espacement)+117,y+260))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+117,y+245),Vec2D(Vec2D(x+(cmptfader*espacement)+110,y+250))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+117,y+245),Vec2D(Vec2D(x+(cmptfader*espacement)+124,y+250))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+110,y+245),Vec2D(Vec2D(x+(cmptfader*espacement)+125,y+245))).Draw(CouleurLigne);
//down
    Line(Vec2D(x+(cmptfader*espacement)+117,y+285),Vec2D(Vec2D(x+(cmptfader*espacement)+117,y+300))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+110,y+295),Vec2D(Vec2D(x+(cmptfader*espacement)+117,y+300))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+124,y+295),Vec2D(Vec2D(x+(cmptfader*espacement)+117,y+300))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+110,y+300),Vec2D(Vec2D(x+(cmptfader*espacement)+125,y+300))).Draw(CouleurLigne);
//saw
    Line(Vec2D(x+(cmptfader*espacement)+110,y+325),Vec2D(Vec2D(x+(cmptfader*espacement)+115,y+340))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+115,y+340),Vec2D(Vec2D(x+(cmptfader*espacement)+120,y+325))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+120,y+325),Vec2D(Vec2D(x+(cmptfader*espacement)+125,y+340))).Draw(CouleurLigne);


//CYCLE NEXT FORWRD
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+35, y+320));
    GlobalBut.Draw(CouleurFader.WithAlpha(lfo_cycle_steps[cmptfader]));
    GlobalBut.DrawOutline(CouleurLigne);
//LFO NEXT STEP BACKWARD
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+70, y+280));
    GlobalBut.Draw(CouleurFader.WithAlpha(lfo_do_next_step[cmptfader][0]));
    GlobalBut.DrawOutline(CouleurLigne);
//LFO NEXT STEP FORWARD
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+70, y+320));
    GlobalBut.Draw(CouleurFader.WithAlpha(lfo_do_next_step[cmptfader][1]));
    GlobalBut.DrawOutline(CouleurLigne);



//icone next step forward
    Line(Vec2D(x+(cmptfader*espacement)+75,y+330),Vec2D(Vec2D(x+(cmptfader*espacement)+87,y+330))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+87,y+330),Vec2D(Vec2D(x+(cmptfader*espacement)+87,y+340))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+87,y+340),Vec2D(Vec2D(x+(cmptfader*espacement)+84,y+335))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+87,y+340),Vec2D(Vec2D(x+(cmptfader*espacement)+90,y+335))).Draw(CouleurLigne);
//icone next step backward
    Line(Vec2D(x+(cmptfader*espacement)+75,y+295),Vec2D(Vec2D(x+(cmptfader*espacement)+87,y+295))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+87,y+295),Vec2D(Vec2D(x+(cmptfader*espacement)+87,y+285))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+87,y+285),Vec2D(Vec2D(x+(cmptfader*espacement)+84,y+290))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+87,y+285),Vec2D(Vec2D(x+(cmptfader*espacement)+90,y+290))).Draw(CouleurLigne);
//liaison steps
    Line(Vec2D(x+(cmptfader*espacement)+83,y+305),Vec2D(Vec2D(x+(cmptfader*espacement)+83,y+320))).Draw(CouleurLigne);

//icone cycle steps up and down
    Line(Vec2D(x+(cmptfader*espacement)+47,y+330),Vec2D(Vec2D(x+(cmptfader*espacement)+47,y+340))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+47,y+340),Vec2D(Vec2D(x+(cmptfader*espacement)+44,y+335))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+47,y+340),Vec2D(Vec2D(x+(cmptfader*espacement)+50,y+335))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+47,y+330),Vec2D(Vec2D(x+(cmptfader*espacement)+47,y+325))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+47,y+325),Vec2D(Vec2D(x+(cmptfader*espacement)+44,y+330))).Draw(CouleurLigne);
    Line(Vec2D(x+(cmptfader*espacement)+47,y+325),Vec2D(Vec2D(x+(cmptfader*espacement)+50,y+330))).Draw(CouleurLigne);
//liaison steps
    Line(Vec2D(x+(cmptfader*espacement)+60,y+332),Vec2D(Vec2D(x+(cmptfader*espacement)+70,y+332))).Draw(CouleurLigne);

/////////////Rajout LOOP / LOOP ALL / FLASH

//LFOButtonLoop
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+138, y+240));
    GlobalBut.Draw(CouleurFader.WithAlpha(is_dock_for_lfo_selected[cmptfader][dock_used_by_fader_is[cmptfader]]));
    GlobalBut.DrawOutline(CouleurLigne);

//LFOButtonALLLoop
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+138, y+280));
    GlobalBut.DrawOutline(CouleurLigne);

//LFOButtonFlash
    GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+138, y+320));
    GlobalBut.Draw(CouleurFader.WithAlpha(FaderIsFlash[cmptfader]));
    GlobalBut.DrawOutline(CouleurLigne);



//Flash
    if( window_focus_id==W_FADERS && mouse_x>x+(cmptfader*espacement)+138 && mouse_x<x+(cmptfader*espacement)+163
            && mouse_y> y+320 && mouse_y< y+345)
    {
//BLOCK FLASH qui doit etre dans boucle principale et pas dans le core qui checke la souris
        if(mouse_button==1 &&  mouse_released==0)
        {
            if( Midi_Faders_Affectation_Type==0)
            {
                if(FaderIsFlash[cmptfader]==0)
                {
                    FaderIsFlash[cmptfader]=1;
                }
            }
            else
            {
                attribute_midi_to_control(900+cmptfader,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
                mouse_released=1;
            }
        }
        else if(mouse_released==1 && FaderIsFlash[cmptfader]==1 && Midi_Faders_Affectation_Type==0)
        {
            fader_set_level(cmptfader,0);
            FaderIsFlash[cmptfader]=0;
            midi_levels[900+cmptfader]=0;
        }

//FIN BLOCK FLASH

    }
//graphisme boutons

    Circle SelectedOneLFO(x+(cmptfader*espacement)+150,y+253,4);
    SelectedOneLFO.DrawOutline(CouleurLigne);

    Circle SelectedAllLFOOneA(x+(cmptfader*espacement)+150,y+286,3);
    Circle SelectedAllLFOOneB(x+(cmptfader*espacement)+150,y+293,3);
    Circle SelectedAllLFOOneC(x+(cmptfader*espacement)+150,y+300,3);

    SelectedAllLFOOneA.DrawOutline(CouleurLigne);
    SelectedAllLFOOneB.DrawOutline(CouleurLigne);
    SelectedAllLFOOneC.DrawOutline(CouleurLigne);
    neuromoyen.Print("FL",x+(cmptfader*espacement)+142,y+337);


    if(window_focus_id==W_FADERS)
    {

        if( Midi_Faders_Affectation_Type!=0)
        {
//sab 02/03/2014 IMPACT if( mouse_x>x+(cmptfader*espacement)-5 && mouse_x<x+(cmptfader*espacement)+132 & mouse_y>y+375 && mouse_y<y+400)
            if( mouse_x>x+(cmptfader*espacement)-5 && mouse_x<x+(cmptfader*espacement)+132 && mouse_y>y+375 && mouse_y<y+400)
            {
                LFOSpeedFrame.DrawOutline(CouleurBlind);
                LFOSpeed.Draw(CouleurBlind);
            }
            else if(mouse_x> (x+(cmptfader*espacement)-6) && mouse_x<(x+(cmptfader*espacement)+19) && mouse_y>(y+320) && mouse_y<(y+345) )
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)-6, y+320));
                GlobalBut.DrawOutline(CouleurBlind);
            }
            else if(mouse_x>x+(cmptfader*espacement)+105 && mouse_x<x+(cmptfader*espacement)+130 && mouse_y> y+240 && mouse_y< y+265)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+240));
                GlobalBut.DrawOutline(CouleurBlind);
            }
            else if(mouse_x>x+(cmptfader*espacement)+105 && mouse_x<x+(cmptfader*espacement)+130 && mouse_y> y+280 && mouse_y< y+305)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+280) );
                GlobalBut.DrawOutline(CouleurBlind);
            }
            else if(mouse_x>x+(cmptfader*espacement)+105 && mouse_x<x+(cmptfader*espacement)+130 && mouse_y> y+320 && mouse_y< y+345)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+105, y+320) );
                GlobalBut.DrawOutline(CouleurBlind);
            }

            else if(mouse_x>x+(cmptfader*espacement)+70 && mouse_x<x+(cmptfader*espacement)+95 && mouse_y>y+280 && mouse_y<y+305)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+70, y+280));
                GlobalBut.DrawOutline(CouleurBlind);
            }
            else if(mouse_x>x+(cmptfader*espacement)+70 && mouse_x<x+(cmptfader*espacement)+95 && mouse_y>y+320 && mouse_y<y+345)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+70, y+320));
                GlobalBut.DrawOutline(CouleurBlind);
            }
            else if(mouse_x>x+(cmptfader*espacement)+35 && mouse_x<x+(cmptfader*espacement)+60 && mouse_y>y+320 && mouse_y<y+345)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+35, y+320));
                GlobalBut.DrawOutline(CouleurBlind);
            }


            else if(mouse_x>x+(cmptfader*espacement)+138 && mouse_x<x+(cmptfader*espacement)+153 && mouse_y> y+240 && mouse_y< y+265)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+138, y+240));
                GlobalBut.DrawOutline(CouleurBlind);
            }
            else if(mouse_x>x+(cmptfader*espacement)+138 && mouse_x<x+(cmptfader*espacement)+153 && mouse_y> y+280 && mouse_y< y+305)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+138, y+280));
                GlobalBut.DrawOutline(CouleurBlind);
            }
            else if(mouse_x>x+(cmptfader*espacement)+138 && mouse_x<x+(cmptfader*espacement)+153 && mouse_y> y+320 && mouse_y< y+345)
            {
                GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)+138, y+320));
                GlobalBut.DrawOutline(CouleurBlind);
            }
        }//fin affect midi

//flash si record pos avaible pour STOP POSITION
        if(mouse_x> (x+(cmptfader*espacement)-6) && mouse_x<(x+(cmptfader*espacement)+19) && mouse_y>(y+320) && mouse_y<(y+345)
                && (index_do_dock==1 || index_main_clear==1) )
        {
            GlobalBut.MoveTo(Vec2D(x+(cmptfader*espacement)-6, y+320));
            GlobalBut.Draw(CouleurBlind.WithAlpha(alpha_blinker));
        }

    }




    return(0);
}




int MoveFaderSpace(int ydelimitation)
{
    Line myLine( Vec2D( 0, ydelimitation ), Vec2D( largeur_ecran,ydelimitation));
    myLine.SetLineWidth(triple_epaisseur_ligne_fader);
    if(window_focus_id==906)
    {
        myLine.Draw( CouleurFader );
    }
    else
    {
        myLine.Draw( CouleurLigne );
    }

    Rect Curseur_ScrollFader(Vec2D((int)(scroll_faderspace),ydelimitation-5),Vec2D(100,30));
    Curseur_ScrollFader.SetRoundness(10);
    Curseur_ScrollFader.SetLineWidth(double_epaisseur_ligne_fader);
    Line Delimitation(Vec2D(scroll_faderspace+50,ydelimitation-5),Vec2D(scroll_faderspace+50,ydelimitation+25));
    Delimitation.SetLineWidth(double_epaisseur_ligne_fader);

    Curseur_ScrollFader.Draw(CouleurFond);
    Delimitation.Draw( CouleurFader);
    Curseur_ScrollFader.DrawOutline(CouleurFader);

    if(mouse_y>=ydelimitation-5 && mouse_y<=ydelimitation+35 &&  window_focus_id==W_FADERS)
    {

//AFFECTATION MIDI Fader ONLY
        if(  Midi_Faders_Affectation_Type!=0 )
        {
            Curseur_ScrollFader.DrawOutline(CouleurBlind);

            if(  mouse_x>scroll_faderspace && mouse_x<scroll_faderspace+50  )
            {

                //midi report
                switch(miditable[0][767])
                {
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
                    sprintf(thetypinfo,"-");
                    break;
                }
                sprintf(string_last_midi_id,"MoveFaderSpace LR is Ch: %d Pitch: %d Typ: %s" , miditable[1][767],miditable[2][767],thetypinfo);
            }
        }
//UP DOWN
        if(  mouse_x>scroll_faderspace+50 && mouse_x<scroll_faderspace+100  )
        {
            //midi report
            switch(miditable[0][1635])
            {
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
                sprintf(thetypinfo,"-");
                break;
            }
            sprintf(string_last_midi_id,"MoveFaderSpace UP is Ch: %d Pitch: %d Typ: %s" , miditable[1][1635],miditable[2][1635],thetypinfo);
        }
    }


    if(index_moving_x_slide==1)
    {
        Canvas::SetClipping((int)(scroll_faderspace),ydelimitation-5,(int)(scroll_faderspace+50),30);
        Curseur_ScrollFader.Draw(CouleurFader.WithAlpha(index_moving_x_slide));
        Canvas::DisableClipping();
    }
    else if(index_moving_y_slide==1)
    {
        Canvas::SetClipping((int)(scroll_faderspace+50),ydelimitation-5,(int)(scroll_faderspace+100),30);
        Curseur_ScrollFader.Draw(CouleurFader.WithAlpha(index_moving_y_slide));
        Canvas::DisableClipping();
    }
    petitchiffre.Print("<< >>",(int)(scroll_faderspace+10),ydelimitation+15);

//affichage reperes
    Line( Vec2D( 65, ydelimitation ), Vec2D( 65,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 177, ydelimitation ), Vec2D( 177,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 286, ydelimitation ), Vec2D( 286,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 395, ydelimitation ), Vec2D( 395,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 504, ydelimitation ), Vec2D( 504,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 613, ydelimitation ), Vec2D( 613,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 722, ydelimitation ), Vec2D( 722,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 832, ydelimitation ), Vec2D( 832,ydelimitation+10)).Draw( CouleurLigne );
    Line( Vec2D( 885, ydelimitation ), Vec2D( 885,ydelimitation+10)).Draw( CouleurLigne );

    petitchiffre.Print( "1-6" ,75,ydelimitation+15 );
    petitchiffre.Print( "7-12" ,187,ydelimitation+15);
    petitchiffre.Print( "13-18" ,296,ydelimitation+15);
    petitchiffre.Print( "19-24" ,405,ydelimitation+15);
    petitchiffre.Print( "25-30" ,514,ydelimitation+15);
    petitchiffre.Print( "31-36" ,623,ydelimitation+15);
    petitchiffre.Print( "37-42" ,732,ydelimitation+15);
    petitchiffre.Print( "43-48" ,842,ydelimitation+15);





    return(0);
}

int Touche_Midi_Mute(int xmute, int ymute)
{
    Rect BmidiMute(Vec2D(xmute,ymute),Vec2D(int(72),25));
    BmidiMute.SetRoundness(7.5);
    BmidiMute.SetLineWidth(epaisseur_ligne_fader);

    BmidiMute.Draw(CouleurFader.WithAlpha(alpha_blinker*index_midi_mute));
    BmidiMute.DrawOutline(CouleurLigne);
    petitchiffre.Print("Mute MidiIN",xmute+3,ymute+15);
    return(0);
}

////////////////////////////////////////////////////////////////////////////////
int Lock_Preset_Call(int xf,int yf)
{
    int calcul_visu=0;
    neuro.Print("Lock Presets",xf-15,yf-30);

    for (int cm=0; cm<2; cm++)
    {
        for (int ll=0; ll<4; ll++)
        {
            Rect LockBt(Vec2D(xf+(cm*55)-5,yf+(ll*55)),Vec2D(45,45));
            LockBt.SetRoundness(5);
            LockBt.SetLineWidth(epaisseur_ligne_fader);

            calcul_visu=cm+(2*ll);

            LockBt.Draw(CouleurLock.WithAlpha(lock_preset[calcul_visu]));
            LockBt.DrawOutline(CouleurLigne);

            if(window_focus_id==W_MINIFADERS && Midi_Faders_Affectation_Type!=0 && mouse_x>xf+(cm*55)-5 && mouse_x<xf+(cm*55)+40 && mouse_y>yf+(ll*55) && mouse_y<yf+(ll*55)+45)
            {
//config midi
                LockBt.DrawOutline(CouleurBlind);
            }



            petitdoomblanc.Print(ol::ToString(calcul_visu+1),xf+(cm*55)+10,yf+(ll*55)+25);


            petitchiffre.Print(ol::ToString(master_lock_preset[calcul_visu]),xf+(cm*55)+20,yf+(ll*55)+40);

        }
    }

    return(0);
}

///////////////////////////////////////////////////////////////////////////////
int Commandes_faders_generales(int xf, int yf)
{
//sab 02/03/2014 unused var char str_titre[15];
    neuro.Print("All At Zero",xf-10,yf-30);
    Rect Commande(Vec2D(xf,yf),Vec2D(72,25));
    Commande.SetRoundness(7.5);
    Commande.SetLineWidth(epaisseur_ligne_fader);

    for (int u=0; u<8; u++)
    {
        Commande.MoveTo(Vec2D(xf,yf+(50*u)));
        Commande.DrawOutline(CouleurLigne);
        switch(u)
        {
        case 0:
            petitchiffre.Print("Faders",xf+5,yf+15+(50*u));
            break;
        case 1:
            petitchiffre.Print("Speed",xf+5,yf+15+(50*u));
            break;
        case 2:
            petitchiffre.Print("Lock",xf+5,yf+15+(50*u));
            break;
        case 3:
            petitchiffre.Print("LFO",xf+5,yf+15+(50*u));
            break;
        case 4:
            petitchiffre.Print("Loop",xf+5,yf+15+(50*u));
            break;
        case 5:
            petitchiffre.Print("ALL",xf+5,yf+15+(50*u));
            break;
        case 6:
            petitchiffre.Print("MidiOut",xf+5,yf+15+(50*u));
            break;
        case 7:
            petitchiffre.Print("RECALL",xf+5,yf+15+(50*u));
            break;
        default: break;
        }

        if(window_focus_id==W_MINIFADERS && Midi_Faders_Affectation_Type!=0 && mouse_x>xf && mouse_x<xf+72 && mouse_y>yf+(50*u) && mouse_y<yf+(50*u)+25)
        {
            Commande.DrawOutline(CouleurBlind);
        }


    }

    return(0);
}

int FaderSpace(int x, int y, int espacement,int nbr_fader)
{
    Rect BackgroundFaderSpace(Vec2D(-20,y-80),Vec2D(LargeurEspaceFaderSize+20,hauteur_ecran));

    BackgroundFaderSpace.SetLineWidth(5.0);
    BackgroundFaderSpace.SetRoundness(15);
    BackgroundFaderSpace.Draw(CouleurFond);
    if(LargeurEspaceFaderSize!=largeur_ecran)
    {
        if(window_focus_id==W_FADERS)
        {
            BackgroundFaderSpace.DrawOutline(CouleurFader);
        }
        else
        {
            BackgroundFaderSpace.DrawOutline(CouleurLigne);
        }
    }

    Canvas::SetClipping(0,y-80,LargeurEspaceFaderSize,hauteur_ecran);

    for (int cmptfader=0; cmptfader<core_user_define_nb_faders; cmptfader++)
    {
//on affiche et actionne que si les données sont dans l espace de l ecran
        if(((x+(cmptfader*espacement)+espacement)>0)&& ((x+(cmptfader*espacement))<LargeurEspaceFaderSize))
        {
            int niveau=(int)Fader[cmptfader];
            myalpha=((float)niveau/255);
            switch(dmx_view)
            {
            case 0:
                if(FaderLocked[cmptfader]==1)
                {
                    petitchiffrerouge.Print(ol::ToString((int)((float)(StateOfFaderBeforeLock[cmptfader])/2.55)),x+(cmptfader*espacement)+12,y+273);
                }
                sprintf(string_niveau, "%d",(int)(((float)niveau)/2.55));
                break;
            case 1:
                sprintf(string_niveau,"%d", niveau);
                if(FaderLocked[cmptfader]==1)
                {
                    petitchiffrerouge.Print(ol::ToString((int)StateOfFaderBeforeLock[cmptfader]),x+(cmptfader*espacement)+12,y+273);
                }
                break;
            default: break;
            }
            sprintf(string_channel,"%d", cmptfader+1);

/////FX
            Rect RouteMdeFx(Vec2D(x+(cmptfader*espacement)+60, y-30),Vec2D(10,10));
            switch(fader_fx_route[cmptfader])
            {
            case 0://espace faders
                RouteMdeFx.Draw(CouleurFader);
                break;
            case 1://espace séquenciel
                RouteMdeFx.Draw(CouleurNiveau.WithAlpha(0.5));
                break;
            default: break;
            }
            RouteMdeFx.DrawOutline(CouleurLigne.WithAlpha(0.5));

// NORMAL / EXCLUDED FROM BUFFER FADER / SUBTRACT / ADDITIF /
            Rect Mode_buffer_data(Vec2D(x+(cmptfader*espacement)+75, y-30),Vec2D(40,10));
            Mode_buffer_data.SetRoundness(0.2);
//sab 02/03/2014 unused var char temp_dex[16];
            switch(fader_mode_with_buffers[cmptfader])
            {
            case 0://normal HTP
                Mode_buffer_data.Draw(CouleurFader);
                petitpetitchiffre.Print("",x+(cmptfader*espacement)+70, y-10);
                break;
            case 1://off
                Mode_buffer_data.Draw(CouleurFond);
                petitpetitchiffre.Print("     off",x+(cmptfader*espacement)+70, y-10);
                break;
            case 2://minus
                Mode_buffer_data.Draw(CouleurRougePur);
                petitpetitchiffre.Print("subtract",x+(cmptfader*espacement)+70, y-10);
                break;
            case 3://add
                Mode_buffer_data.Draw(CouleurLigne);
                petitpetitchiffre.Print("    add",x+(cmptfader*espacement)+70, y-10);
                break;
            case 4://screen
                Mode_buffer_data.Draw(CouleurLevel);
                petitpetitchiffre.Print("  screen",x+(cmptfader*espacement)+70, y-10);
                break;
            case 5://exclusion
                Mode_buffer_data.Draw(CouleurBleuProcedure);
                petitpetitchiffre.Print(" exclusion",x+(cmptfader*espacement)+70, y-10);
                break;
            default:
                break;
            }
            Mode_buffer_data.DrawOutline(CouleurLigne.WithAlpha(0.3));



//DESSIN FADER
            Rect FaderB( Vec2D( x+(cmptfader*espacement),y+2), Vec2D ( 40,255));//box du fader
            FaderB.SetRoundness(15);
            FaderB.SetLineWidth(epaisseur_ligne_fader);

            Rect FaderNiveau( Vec2D(  x+(cmptfader*espacement),(y+255) - niveau), Vec2D ( 40,niveau+2));//niveau fader
            FaderNiveau.SetRoundness(15);
//separateur
            Line(Vec2D(x+(cmptfader*espacement)-20,y-50),Vec2D(x+(cmptfader*espacement)-20,y+400)).Draw(CouleurLigne);
            if(FaderLocked[cmptfader]==0)
            {
//affichage du fader
                switch(DockTypeIs[cmptfader][(dock_used_by_fader_is[cmptfader])])
                {
                default:
                    FaderNiveau.Draw(CouleurFader.WithAlpha(myalpha));
                    break;
                case 11://Fx
                    if(chaser_is_playing[ChaserAffectedToDck[cmptfader][dock_used_by_fader_is[cmptfader]]]==0)FaderNiveau.Draw(CouleurGreen);
                    else FaderNiveau.Draw(CouleurGreen.WithAlpha(alpha_blinker));
                    break;
                case 12://Grid
                    if(grider_is_playing[faders_dock_grid_affectation[cmptfader][dock_used_by_fader_is[cmptfader]]]==0)  FaderNiveau.Draw(CouleurBlind);
                    else FaderNiveau.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                    break;
                case 13://Fgroup
                    FaderNiveau.Draw(CouleurYellowFgroup);
                    break;
                case 14://mover
                    FaderNiveau.Draw( CouleurSelection);
                    break;
                case 15://draw
                    FaderNiveau.Draw(CouleurLevel);
                    break;
                case 16://echo
                    FaderNiveau.Draw(Discrete8);
                    break;
                case 17://wave
                    FaderNiveau.Draw(CouleurBleu2);
                    break;
                }
            }
            else//fader locké
            {
                FaderNiveau.Draw(CouleurLock.WithAlpha(myalpha*2));//couleur en vert emeraude
                if(LockFader_is_FullLevel[cmptfader]==1 && actual_master_lock==cmptfader)
                {
                    //marker rouge rouge du niveau at full lors lockage
                    doomrouge.Print("m",x+11+(cmptfader*espacement), y+35);
                }
            }
            FaderB.DrawOutline(CouleurLigne);


///////////////////////////////////////////////////////////////////////////////
//Midireceive Midi do order ( attribution des F1 F3 Clear etc par midi sur le dock sélectionné)
            Rect Midireceive( Vec2D( x+(cmptfader*espacement)+135,y-35), Vec2D ( 15,15));//box du boutton assignation rapide
            Midireceive.SetRoundness(4);
            Midireceive.SetLineWidth(epaisseur_ligne_fader);

            Midireceive.Draw(CouleurFader.WithAlpha(light_midi_do_order[cmptfader]));//quand midi allumé
            if(light_midi_do_order[cmptfader]>0.0)
            {
                light_midi_do_order[cmptfader]-=0.2;
            }
            petitpetitchiffre.Print("V",x+(cmptfader*espacement)+138,y-25);

            Midireceive.DrawOutline(CouleurLigne);


///////////////////////////////////////////////////////////////////////////////
//Docks Preset
            Rect Dock(Vec2D(x, y ), Vec2D ( 50,20));
            Dock.SetRoundness(8);
            Dock.SetLineWidth(sizefader_epaisseur_ligne_fader);
            for (int dd=0; dd<core_user_define_nb_docks; dd++)
            {
                Dock.MoveTo(Vec2D(x+((cmptfader*espacement)+70), y + (dd*40)));
                petitpetitchiffre.Print(ol::ToString(dd+1),x+(cmptfader*espacement)+55, y + 15+(dd*40));
                if(window_focus_id==W_FADERS && mouse_x>=(x+(cmptfader*espacement)+70) && mouse_x<=(x+(cmptfader*espacement)+120)
                        && mouse_y>=(y + (dd*40)) && mouse_y<=(y + (dd*40)+20)
                        && index_over_function_call==0 )
                {
                    show_who_is_in_dock(cmptfader,dd);  //mise en affichage sélection de qui est dans le dock
                }
                if (DockIsSelected[cmptfader][dd]==1)
                {
                    if(FaderLocked[cmptfader]==0)
                    {
                        Dock.Draw(CouleurFader);
                    }
                    else if(FaderLocked[cmptfader]==1)
                    {
                        Dock.Draw(CouleurLock);
                    }
                    if(DockTypeIs[cmptfader][dd]==5)
                    {
                        for(int tt=0; tt<24; tt++)
                        {
                            DockName[cmptfader][dd][tt]=descriptif_memoires[(DockHasMem[cmptfader][dd])][tt] ;
                        }
                        DockName[cmptfader][dd][24]='\0';
                    }
                    else if(DockTypeIs[cmptfader][dd]==6 || DockTypeIs[cmptfader][dd]==7 || DockTypeIs[cmptfader][dd]==8)
                    {
                        Dock.Draw(CouleurNiveau);
                        FaderNiveau.Draw(CouleurNiveau);
                        switch(FaderLocked[cmptfader])
                        {
                        case 0:
                            FaderB.DrawOutline(CouleurLigne);
                            break;
                        case 1:
                            FaderB.DrawOutline(CouleurLock);
                            break;
                        default: break;
                        }
                    }
                    else if(DockTypeIs[cmptfader][dd]==11)//chaser
                    {
                        for(int tt=0; tt<24; tt++)
                        {
                            DockName[cmptfader][dd][tt]=chaser_name[(ChaserAffectedToDck[cmptfader][dd])][tt] ;
                        }
                        DockName[cmptfader][dd][24]='\0';
                        Dock.Draw(CouleurGreen);
                    }
                    else if(DockTypeIs[cmptfader][dd]==12)//Grid
                    {
                        for(int tt=0; tt<24; tt++)
                        {
                            DockName[cmptfader][dd][tt]=grider_name[index_grider_selected[faders_dock_grid_affectation[cmptfader][dd]]][tt] ;
                        }
                        DockName[cmptfader][dd][24]='\0';
                        Dock.Draw(CouleurBlind);
                    }
                    else if(DockTypeIs[cmptfader][dd]==13)//Fgroup
                    {
                        Dock.Draw(CouleurYellowFgroup);
                    }
                    else if(DockTypeIs[cmptfader][dd]==14)//mover
                    {
                        Dock.Draw(CouleurSelection);
                    }
                    else if(DockTypeIs[cmptfader][dd]==15)//draw
                    {
                        Dock.Draw(CouleurLevel);
                    }

                    else if(DockTypeIs[cmptfader][dd]==16)//echo
                    {
                        Dock.Draw( Discrete8);
                    }

                    else if(DockTypeIs[cmptfader][dd]==17)//echo
                    {
                        Dock.Draw(CouleurBleu2);
                    }

                    petitpetitchiffre.Print( DockName[cmptfader][dd],x+(cmptfader*espacement)-5,y-10 ) ;
                }



                switch(DockTypeIs[cmptfader][dd])
                {
//types des docks
                case 1://si le doc est relié aux trichro
                    petitchiffre.Print("Color",x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 2://si le doc est relié à un artnet
                    sprintf( string_docktypnet,"Art-%d",DockNetIs[cmptfader][dd]);
                    petitchiffre.Print(string_docktypnet,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 3://si le doc recoit le dmxIN
                    sprintf( string_docktypnet,"Dmx-In");
                    petitchiffre.Print(string_docktypnet,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 4://si le doc recoit le tracking video
                    sprintf( string_docktypvideo,"Video");
                    petitchiffre.Print(string_docktypvideo,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 5://si le doc contient une memoire
                    sprintf( string_docktypmem,"%.1f",(((float)(DockHasMem[cmptfader][dd]))/10));
                    petitchiffre.Print(string_docktypmem,x+((cmptfader*espacement)+92),  y +15+ (dd*40));
                    if(MemoiresExistantes[DockHasMem[cmptfader][dd]] ==0)//si mem detruite plus tard affichage d un pb d affcetation
                    {
                        Dock.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                    }
                    break;
                case 6://audio Player Volume
                    sprintf( string_docktypaudiovol,"Vol.%d",(DockHasAudioVolume[cmptfader][dd]));
                    petitchiffre.Print(string_docktypaudiovol,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 7://audio Player Pan
                    sprintf( string_docktypaudiopan,"Pan.%d",(DockHasAudioPan[cmptfader][dd]));
                    petitchiffre.Print(string_docktypaudiopan,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 8:
                    sprintf( string_docktypaudiopicth,"Pitch.%d",(DockHasAudioPitch[cmptfader][dd]));
                    petitchiffre.Print(string_docktypaudiopicth,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 9://no content
                    petitchiffre.Print("-",x+((cmptfader*espacement)+92),  y +15+ (dd*40));
                    break;
                case 10://direct chan
                    sprintf( string_docktypdchan,"DC.%d",(FaderDirectChan[cmptfader][dd]));
                    petitchiffre.Print(string_docktypdchan,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 11://fx
                    sprintf( string_docktypfx,"FX.%d",(ChaserAffectedToDck[cmptfader][dd]+1));
                    petitchiffre.Print(string_docktypfx,x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 12://grid
                    sprintf( string_docktypfx,"Grid P.%d",(faders_dock_grid_affectation[cmptfader][dd]+1));
                    petitchiffre.Print(string_docktypfx,x+((cmptfader*espacement)+75),  y +15+ (dd*40));
                    break;
                case 13://fgroup
                    petitchiffrerouge.Print("Fgroup",x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 14://mover
                    petitchiffre.Print("Mover",x+((cmptfader*espacement)+77),  y +15+ (dd*40));
                    break;
                case 15://draw
                    sprintf( string_docktypfx,"Draw %d",(DrawAffectedToDck[cmptfader][dd]+1));
                    petitchiffre.Print(string_docktypfx,x+((cmptfader*espacement)+75),  y +15+ (dd*40));
                    break;
                case 16://echo
                    sprintf( string_docktypfx,"Echo %d",(echo_affected_to_dock[cmptfader][dd]+1));
                    petitchiffre.Print(string_docktypfx,x+((cmptfader*espacement)+75),  y +15+ (dd*40));
                    break;
                case 17://WaVE
                    petitchiffre.Print("WAVE",x+((cmptfader*espacement)+75),  y +15+ (dd*40));
                    break;
                default:
                    break;
                }

                Dock.DrawOutline(CouleurLigne);
//affichage pour dock + - en midi
                if(window_focus_id==W_FADERS && Midi_Faders_Affectation_Type!=0 && mouse_x>=(x+(cmptfader*espacement)+70) && mouse_x<=(x+(cmptfader*espacement)+120)
                        && mouse_y>=(y + (dd*40)) && mouse_y<=(y + (dd*40)+20) && (dd==0 || dd==1))
                {
                    Dock.DrawOutline(CouleurBlind);
                }


            }


///////////////////////affichage stop pos POS ET BARRE /////////////////////////////
            if(StopPosOn[cmptfader]==1)
            {
                int niv=0;
                switch(dmx_view)
                {
                case 0:
                    niv= (int) (((float)LevelStopPos[cmptfader])/2.55);
                    break;
                case 1:
                    niv=LevelStopPos[cmptfader];
                    break;
                default: break;
                }
//ON OFF
                switch(ActionnateStopOn[cmptfader])
                {
                case 0:
                    Line(Vec2D(x+(cmptfader*espacement),(y+255) - LevelStopPos[cmptfader]),Vec2D(x+(cmptfader*espacement)+40,(y+255) - LevelStopPos[cmptfader])).Draw(CouleurLigne);
                    petitpetitchiffre.Print(ol::ToString(niv),x+(cmptfader*espacement)+20,(y+255) - LevelStopPos[cmptfader]);
                    break;
                case 1:
                    Line(Vec2D(x+(cmptfader*espacement),(y+255) - LevelStopPos[cmptfader]),Vec2D(x+(cmptfader*espacement)+40,(y+255) - LevelStopPos[cmptfader])).Draw(CouleurBlind);
                    petitpetitchiffrerouge.Print(ol::ToString(niv),x+(cmptfader*espacement)+20,(y+255) - LevelStopPos[cmptfader]);
                    break;
                default: break;
                }
            }
//lettrages du chiffre de fader
            neuro.Print(string_niveau ,x+(cmptfader*espacement), y-25); //niveau du fader

            doom.Print(string_channel,x+(cmptfader*espacement)+70, y-40);
//modes speciaux

//LOCK BUTTON
            Rect LockButton( Vec2D( x+(cmptfader*espacement),y+280), Vec2D ( 40,25));//box du lock button
            LockButton.SetRoundness(6);
            LockButton.SetLineWidth(epaisseur_ligne_fader);

            LockButton.Draw(CouleurLock.WithAlpha(FaderLocked[cmptfader]));


//////////////////////////////////////////////////////////////////////////////////




//midi out enclenché ou pas FADER
            Circle BMidiOut( x+((cmptfader*espacement)+70),y+250, 10);//box du fader
            BMidiOut.SetLineWidth(epaisseur_ligne_fader);
            BMidiOut.Draw(CouleurBlind.WithAlpha(midi_send_out[cmptfader]));
            BMidiOut.DrawOutline(CouleurLigne);
//raccrochage midi
            raccrochage_midi_visuel_vertical_dmx ( x+(cmptfader*espacement), y, cmptfader,40,255);




//liaison visuelle au fader du cercle midi out
            Line (Vec2D( x+(cmptfader*espacement)+40,y+240),Vec2D( x+(cmptfader*espacement)+55,y+240)).Draw(CouleurLigne);
            Line (Vec2D( x+(cmptfader*espacement)+55,y+240),Vec2D( x+(cmptfader*espacement)+65,y+245)).Draw(CouleurLigne);
//////////////////////////////////////
            petitchiffre.Print("Lock",x+8+(cmptfader*espacement), y+295);
            LockButton.DrawOutline(CouleurLigne);




            lfo_fader_functions(cmptfader, x-8, y,espacement);

            petitpetitchiffre.Print( string_time_is_in_the_dock[cmptfader],x+(cmptfader*espacement)-20,y+365);


/////////////////COURBE DU FADER////////////////////////////////////////////////
            Rect CurveOn (Vec2D(x+(cmptfader*espacement)-10,y+410),Vec2D(20,20));

            CurveOn.SetRoundness(4);
            CurveOn.SetLineWidth(demi_epaisseur_ligne_fader);
            CurveOn.DrawOutline(CouleurLigne);
            petitpetitchiffre.Print( "C.",x+(cmptfader*espacement)-10,y+420);
            petitpetitchiffre.Print( ol::ToString(FaderCurves[cmptfader]+1),x+(cmptfader*espacement),y+425);

//commande embeded
            if(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==11 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==12
                    || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==6 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==7 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==8  )
            {
                switch(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]])
                {
                case 6://VOLUME
//Play
                    play_button_view(x+(cmptfader*espacement)+20,y+410,
                                     player_is_playing[ DockHasAudioVolume[cmptfader][dock_used_by_fader_is[cmptfader]]-1] );
//Seek to Beg
                    if(mouse_x>x+(cmptfader*espacement)+45 && mouse_x<x+(cmptfader*espacement)+70 && mouse_y>y+410 && mouse_y<y+430 && mouse_button==1 && mouse_released==0)
                    {
                        seek_button_view(x+(cmptfader*espacement)+45,y+410,1);//seek , affichage avant le bouton
                        mouse_released=1;
                    }
                    seek_button_view(x+(cmptfader*espacement)+45,y+410,0);
//LOOP chaser
                    loop_button_view(x+(cmptfader*espacement)+70,y+410,player_is_onloop[ DockHasAudioVolume[cmptfader][dock_used_by_fader_is[cmptfader]]-1] );
//autolaunch chaser
                    autolaunch_button_view(x+(cmptfader*espacement)+95,y+410,autolaunch[cmptfader]);
                    break;
                case 7://PAN
//Play
                    play_button_view(x+(cmptfader*espacement)+20,y+410,
                                     player_is_playing[ DockHasAudioPan[cmptfader][dock_used_by_fader_is[cmptfader]]-1] );
//Seek to Beg
                    if(mouse_x>x+(cmptfader*espacement)+45 && mouse_x<x+(cmptfader*espacement)+70 && mouse_y>y+410 && mouse_y<y+430 && mouse_button==1 && mouse_released==0)
                    {
                        seek_button_view(x+(cmptfader*espacement)+45,y+410,1);//seek , affichage avant le bouton
                        mouse_released=1;
                    }
                    seek_button_view(x+(cmptfader*espacement)+45,y+410,0);
//LOOP chaser
                    loop_button_view(x+(cmptfader*espacement)+70,y+410,player_is_onloop[ DockHasAudioPan[cmptfader][dock_used_by_fader_is[cmptfader]]-1] );
//autolaunch chaser
                    autolaunch_button_view(x+(cmptfader*espacement)+95,y+410,autolaunch[cmptfader]);
                    break;
                case 8://PITCH
//Play
                    play_button_view(x+(cmptfader*espacement)+20,y+410,
                                     player_is_playing[ DockHasAudioPitch[cmptfader][dock_used_by_fader_is[cmptfader]]-1] );
//Seek to Beg
                    if(mouse_x>x+(cmptfader*espacement)+45 && mouse_x<x+(cmptfader*espacement)+70 && mouse_y>y+410 && mouse_y<y+410+20 && mouse_button==1 && mouse_released==0)
                    {
                        seek_button_view(x+(cmptfader*espacement)+45,y+410,1);//seek , affichage avant le bouton
                        mouse_released=1;
                    }
                    seek_button_view(x+(cmptfader*espacement)+45,y+410,0);
//LOOP chaser
                    loop_button_view(x+(cmptfader*espacement)+70,y+410,player_is_onloop[ DockHasAudioPitch[cmptfader][dock_used_by_fader_is[cmptfader]]-1] );
//autolaunch chaser
                    autolaunch_button_view(x+(cmptfader*espacement)+95,y+410,autolaunch[cmptfader]);
                    break;
                case 11://CHASERS
//Play
                    play_button_view(x+(cmptfader*espacement)+20,y+410,
                                     chaser_is_playing[ChaserAffectedToDck[cmptfader][dock_used_by_fader_is[cmptfader]]]);
//Seek to Beg
                    if(mouse_x>x+(cmptfader*espacement)+45 && mouse_x<x+(cmptfader*espacement)+70 && mouse_y>y+410 && mouse_y<y+430 && mouse_button==1 && mouse_released==0)
                    {
                        seek_button_view(x+(cmptfader*espacement)+45,y+410,1);//seek , affichage avant le bouton
                        mouse_released=1;
                    }
                    seek_button_view(x+(cmptfader*espacement)+45,y+410,0);
//LOOP chaser
                    loop_button_view(x+(cmptfader*espacement)+70,y+410,chaser_is_in_loop[ChaserAffectedToDck[cmptfader][dock_used_by_fader_is[cmptfader]]]);
//autolaunch chaser
                    autolaunch_button_view(x+(cmptfader*espacement)+95,y+410,autolaunch[cmptfader]);
                    break;
                case 12://GRIDPLAYER
                    play_button_view(x+(cmptfader*espacement)+20,y+410,
                                     grider_is_playing[faders_dock_grid_affectation[cmptfader][dock_used_by_fader_is[cmptfader]]]);
//Seek to Beg
                    if(mouse_x>x+(cmptfader*espacement)+45 && mouse_x<x+(cmptfader*espacement)+70 && mouse_y>y+410 && mouse_y<y+410+20 && mouse_button==1 && mouse_released==0)
                    {
                        seek_button_view(x+(cmptfader*espacement)+45,y+410,1);//seek , affichage avant le bouton
                        mouse_released=1;
                    }
                    seek_button_view(x+(cmptfader*espacement)+45,y+410,0);
//StopPlay
                    playstop_button_view(x+(cmptfader*espacement)+70,y+410,grider_autostopmode[faders_dock_grid_affectation[cmptfader][dock_used_by_fader_is[cmptfader]]]);
//autolaunch chaser
                    autolaunch_button_view(x+(cmptfader*espacement)+95,y+410,autolaunch[cmptfader]);
                    break;
                default:
                    break;
                }
            }//fin si chaser embeded


            if(window_focus_id==W_FADERS && Midi_Faders_Affectation_Type!=0 )
            {
                if(mouse_x>x+(cmptfader*espacement)+75 && mouse_x<x+(cmptfader*espacement)+115 && mouse_y> y-30 && mouse_y<y-20 )
                {
                    char temp_str_tr[72];
                    sprintf(temp_str_tr,"Fx mode on fader %d",cmptfader+1);
                    show_type_midi(1543+cmptfader,temp_str_tr );
                    Mode_buffer_data.DrawOutline(CouleurBlind);
                }
                else if( mouse_x>x+(cmptfader*espacement)+135 && mouse_x<x+(cmptfader*espacement)+150 &&
                         mouse_y>y-35 && mouse_y<y-20 )
                {
                    Midireceive.DrawOutline(CouleurBlind);
                }
                else if( mouse_x>x+(cmptfader*espacement) && mouse_x<x+(cmptfader*espacement)+40
                         && mouse_y>y+2 && mouse_y<y+257)
                {
                    FaderB.DrawOutline(CouleurBlind);
                }
                else if( mouse_y>(y+280) && mouse_y<(y+300) && mouse_x>x+(cmptfader*espacement) && mouse_x<(x+40+(cmptfader*espacement)))
                {
                    LockButton.DrawOutline(CouleurBlind);
                }

            }

fader_damper_commands(x+(cmptfader*espacement)-10,y+440, cmptfader );
//fin des 48
        }
    }




    MoveFaderSpace(y-70);// fonction pour se deplacer sur les 48 masters

    Canvas::DisableClipping();
    return(0);
}
