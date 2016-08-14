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

* \file gui_boutons_rebuild1.cpp
* \brief {GUI fonctions to redraw buttons}
* \author Christoph Guillermet
* \version {0.8.6}
* \date {28/04/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour redéssiner les bouttons
*
*   GUI fonctions to redraw buttons
*
 **/

int bouton_on_view(int xp, int yp, bool state)
{
    Rect On(Vec2D(xp,yp),Vec2D(20,20));
    On.SetRoundness(4);
    if(state==1)
    {
        On.Draw(CouleurFader);
    }
    On.DrawOutline(CouleurLigne);
    petitchiffre.Print("ON",xp+1,yp+14);
    if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
    {
        if( Midi_Faders_Affectation_Type!=0)//config midi
        {
            On.DrawOutline(CouleurBlind);
        }
    }

    return(0);
}

//sab 02/03/2014 int bouton_text_view(int xp, int yp,char *dex, bool state)
void bouton_text_view(int xp, int yp,const std::string dex, bool state)
{
    Rect Texn(Vec2D(xp,yp),Vec2D(20,20));
    Texn.SetRoundness(4);
    if(state==1)
    {
        Texn.Draw(CouleurFader);
    }
    Texn.DrawOutline(CouleurLigne);
    petitpetitchiffre.Print(dex,xp+3,yp+14);
    if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
    {
        if( Midi_Faders_Affectation_Type!=0)//config midi
        {
            Texn.DrawOutline(CouleurBlind);
        }
    }
//sab 02/03/2014 return(0);
}


float do_logical_rotatif(int xr, int yr, int Rrayon)
{
    float valeur=0.0;
//if(mouse_x>=xr-Rrayon && mouse_x<=xr+Rrayon && mouse_y>=yr-Rrayon && mouse_y<=yr+Rrayon)
//{
    valeur=(atan2(xr-(mouse_x-xr), yr-(mouse_y-yr)));
//}
    return(valeur);
}

int rotatif(int xr, int yr, int Rrayon, float valeur)
{
    /*
     va utiliser une formule simple pour trouver un angle entre 2 points.

    angleRadian = Math.atan2(px1 - px2, py1 - py2);
    angleDegree = angleRadian * (180 / Math.PI);

    Et une autre formule qui permet de trouver la distance entre 2 points.
    distance= Math.sqrt(px1*px2 + py1*py2);*/
    Circle Rot(Vec2D(xr,yr),Rrayon);

    Rot.SetRadius(Rrayon);
    Rot.RotateBy(1);
//Rot.DrawSlice(CouleurFader,0, (2*PI)-1 );

    Rot.DrawSlice(CouleurFond,0 , ((2*PI)-1) );
    Rot.DrawSlice(CouleurLigne.WithAlpha(0.3),0 , ((2*PI)-1) );
    Rot.SetRadius(Rrayon/1.5);
    Rot.Draw(CouleurFond);
    neuromoyen.Print(ol::ToString(valeur),xr-10,yr+10);

    double Vx, Vy;
    for(double v=-PI ; v<=PI ; v+=(PI/6))
    {
        Vx=cos(v)*Rrayon;
        Vy=sin(v)*Rrayon;
        Line(Vec2D(xr,yr),Vec2D(xr+Vx,yr+Vy)).Draw(CouleurFond);
    }
    Vx=cos(((2*PI)-valeur)-2)*Rrayon;
    Vy=sin(((2*PI)-valeur)-2)*Rrayon;
    Line Curseur(Vec2D(xr,yr),Vec2D(xr+Vx,yr+Vy));
    Curseur.SetLineWidth(Rrayon/5);
    Curseur.Draw(CouleurLigne);
    return(0);
}

int play_button_view(int xp, int yp, bool state)
{
    Rect Play(Vec2D(xp,yp),Vec2D(20,20));
    Play.SetRoundness(4);
    if(state==1)
    {
        Play.Draw(CouleurFader);
    }
    Play.DrawOutline(CouleurLigne);
    Line(Vec2D(xp+6,yp+4),Vec2D(xp+6,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+6,yp+4),Vec2D(xp+16,yp+10)).Draw(CouleurLigne);
    Line(Vec2D(xp+6,yp+16),Vec2D(xp+16,yp+10)).Draw(CouleurLigne);
    if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
    {
        if(Midi_Faders_Affectation_Type!=0)//config midi
        {
            Play.DrawOutline(CouleurBlind);
        }
    }

    return(0);
}

int seek_button_view(int xp,int yp, bool state)
{
//SEEK TO 0
    Rect SeekToZero(Vec2D(xp,yp),Vec2D(20,20));
    SeekToZero.SetRoundness(4);
    Line(Vec2D(xp+16,yp+4),Vec2D(xp+16,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+16,yp+4),Vec2D(xp+6,yp+10)).Draw(CouleurLigne);
    Line(Vec2D(xp+6,yp+10),Vec2D(xp+16,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+4,yp+4),Vec2D(xp+4,yp+16)).Draw(CouleurLigne);
    SeekToZero.DrawOutline(CouleurLigne);
    if(state==1)
    {
        SeekToZero.Draw(CouleurFader);
    }

    if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
    {
        if( Midi_Faders_Affectation_Type!=0)//config midi
        {
            SeekToZero.DrawOutline(CouleurBlind);
        }
    }
    return(0);
}

int loop_button_view(int xp,int yp, bool state)
{
    Rect GeneralLoop(Vec2D(xp,yp),Vec2D(20,20));
    GeneralLoop.SetRoundness(4);
    GeneralLoop.DrawOutline(CouleurLigne);
    if(state==1)
    {
        Circle(Vec2D(xp+10,yp+10),5).Draw(CouleurFader);
    }
    Circle(Vec2D(xp+10,yp+10),5).DrawOutline(CouleurLigne);

    if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
    {
        if( Midi_Faders_Affectation_Type!=0)//config midi
        {
            GeneralLoop.DrawOutline(CouleurBlind);
        }
    }
    return(0);
}


int playstop_button_view(int xp, int yp, bool state)
{
    Rect Play(Vec2D(xp,yp),Vec2D(20,20));
    Play.SetRoundness(4);
    if(state==1)
    {
        Play.Draw(CouleurBlind);
    }
    Play.DrawOutline(CouleurLigne);
    Line(Vec2D(xp+4,yp+4),Vec2D(xp+4,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+6,yp+4),Vec2D(xp+6,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+8,yp+4),Vec2D(xp+8,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+10,yp+4),Vec2D(xp+10,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+10,yp+4),Vec2D(xp+20,yp+10)).Draw(CouleurLigne);
    Line(Vec2D(xp+10,yp+16),Vec2D(xp+20,yp+10)).Draw(CouleurLigne);
    if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
    {
        if(Midi_Faders_Affectation_Type!=0)//config midi
        {
            Play.DrawOutline(CouleurBlind);
        }
    }

    return(0);
}

int autolaunch_button_view(int xp,int yp, bool state)
{
    Rect Autolch(Vec2D(xp,yp),Vec2D(20,20));
    Autolch.SetRoundness(4);
    if(state==1)
    {
        Autolch.Draw(CouleurFader);
    }

    Autolch.DrawOutline(CouleurLigne);

    Line(Vec2D(xp+5,yp+15),Vec2D(xp+15,yp+5)).Draw(CouleurLigne);
    Line(Vec2D(xp+15,yp+5),Vec2D(xp+10,yp+5)).Draw(CouleurLigne);
    Line(Vec2D(xp+15,yp+5),Vec2D(xp+15,yp+10)).Draw(CouleurLigne);

    if(mouse_x>xp && mouse_x<xp+20 && mouse_y>yp && mouse_y<yp+20)
    {
        if( Midi_Faders_Affectation_Type!=0)//config midi
        {
            Autolch.DrawOutline(CouleurBlind);
        }
    }
    return(0);
}

///////////////ICAT////////////////////////////////////////////////////////////

int next_button_view(int xp, int yp, bool state)
{
    Rect NeXtbutt(Vec2D(xp,yp),Vec2D(20,20));
    NeXtbutt.SetRoundness(4);

    NeXtbutt.Draw(CouleurFond.WithAlpha(0.4));
    if(state==1)
    {
        NeXtbutt.Draw(CouleurBlind);
    }
    Line(Vec2D(xp+6,yp+4),Vec2D(xp+6,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+6,yp+4),Vec2D(xp+16,yp+10)).Draw(CouleurLigne);
    Line(Vec2D(xp+6,yp+16),Vec2D(xp+16,yp+10)).Draw(CouleurLigne);

    return(0);
}


int previous_button_view(int xp,int yp, bool state)
{
    Rect PreVbutt(Vec2D(xp,yp),Vec2D(20,20));
    PreVbutt.SetRoundness(4);

    PreVbutt.Draw(CouleurFond.WithAlpha(0.4));
    if(state==1)
    {
        PreVbutt.Draw(CouleurBlind);
    }
    Line(Vec2D(xp+16,yp+4),Vec2D(xp+16,yp+16)).Draw(CouleurLigne);
    Line(Vec2D(xp+16,yp+4),Vec2D(xp+6,yp+10)).Draw(CouleurLigne);
    Line(Vec2D(xp+6,yp+10),Vec2D(xp+16,yp+16)).Draw(CouleurLigne);


    return(0);
}

int case_moins_view(int xp,int yp, bool state)
{
    Rect MoinsC(Vec2D(xp,yp),Vec2D(15,15));
    MoinsC.SetRoundness(2);
    MoinsC.Draw(CouleurFond.WithAlpha(0.4));
    if(state==1)
    {
        MoinsC.Draw(CouleurBlind);
    }
    petitchiffre.Print("-",xp+3,yp+10);
    return(0);
}


int case_plus_view(int xp,int yp, bool state)
{
    Rect PlusC(Vec2D(xp,yp),Vec2D(15,15));
    PlusC.SetRoundness(2);
    PlusC.Draw(CouleurFond.WithAlpha(0.4));
    if(state==1)
    {
        PlusC.Draw(CouleurBlind);
    }
    petitchiffre.Print("+",xp+3,yp+10);
    return(0);
}

//sab 02/03/2014 int toggling_bar_view(int xp,int yp, bool state, char *titre)
void toggling_bar_view(int xp,int yp, bool state, const std::string titre)
{
    Rect toggling_B(Vec2D(xp,yp),Vec2D(70,20));
    toggling_B.SetRoundness(4);
    toggling_B.Draw(CouleurFond.WithAlpha(0.4));
    petitpetitchiffre.Print(titre,xp,yp+12);

//sab 02/03/2014 return(0);
}


int pulse_bar_view(int xp,int yp, char *titre)
{
    Rect pulse_B(Vec2D(xp,yp),Vec2D(30,20));
    pulse_B.SetRoundness(4);
    pulse_B.Draw(CouleurFond.WithAlpha(0.4));
    petitpetitchiffre.Print(titre,xp,yp+12);

    return(0);
}

//////////////MIDI MUTE AFFICHAGES

int raccrochage_midi_logical_vertical_dmx(int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

//midi racroche
    if(mouse_x>Xb+largeur+4 && mouse_x<Xb+largeur+16 && mouse_y>=Yb+hauteur-1 && mouse_y<=Yb+hauteur+11 )
    {
        if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            is_raccrochage_midi_remote[IDmidi]=toggle(is_raccrochage_midi_remote[IDmidi]);
            mouseClicLeft.SetProcessed();
        }
    }
    return(0);
}

int raccrochage_midi_visuel_vertical_dmx (int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

    Circle BMidiRaccroche(Xb+largeur+10,Yb+hauteur+5, 6);//raccroche midi
    if(is_raccrochage_midi_remote[IDmidi]==1)
    {
        BMidiRaccroche.Draw(CouleurFader);
//affichage niveau
        Line MonNiveauMidi(Vec2D(Xb,(Yb+hauteur) -(val_raccrochage_midi[IDmidi]*2)),Vec2D(Xb+largeur+10,(Yb+hauteur) - (val_raccrochage_midi[IDmidi]*2)));
        MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
        MonNiveauMidi.Draw(CouleurLigne);

        Line MaJonction(Vec2D(Xb+largeur+10,(Yb+hauteur)),Vec2D(Xb+largeur+10,(Yb+hauteur) - (val_raccrochage_midi[IDmidi]*2)));
        MaJonction.SetLineWidth(epaisseur_ligne_fader);
        MaJonction.Draw(CouleurFond,CouleurLigne);

    }
    BMidiRaccroche.DrawOutline(CouleurLigne);
    return(0);
}


int raccrochage_midi_visuel_vertical_dmx_inverted (int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

    Circle BMidiRaccroche(Xb+largeur+10,Yb+hauteur+5, 6);//raccroche midi
    if(is_raccrochage_midi_remote[IDmidi]==1)
    {
        BMidiRaccroche.Draw(CouleurFader);
//affichage niveau
        Line MonNiveauMidi(Vec2D(Xb,Yb+(val_raccrochage_midi[IDmidi]*2)),Vec2D(Xb+largeur+10,Yb+(val_raccrochage_midi[IDmidi]*2)));
        MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
        MonNiveauMidi.Draw(CouleurLigne);

        Line MaJonction(Vec2D(Xb+largeur+10,Yb+hauteur),Vec2D(Xb+largeur+10,Yb+(val_raccrochage_midi[IDmidi]*2)));
        MaJonction.SetLineWidth(epaisseur_ligne_fader);
        MaJonction.Draw(CouleurFond,CouleurLigne);

    }
    BMidiRaccroche.DrawOutline(CouleurLigne);
    return(0);
}
///////////////////////////////////////////////////////////////////////////////////
int raccrochage_midi_logical_vertical(int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

//midi racroche
    if(mouse_x>Xb+largeur+6 && mouse_x<Xb+largeur+14 && mouse_y>=Yb+hauteur-1 && mouse_y<=Yb+hauteur+9)
    {
        if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            is_raccrochage_midi_remote[IDmidi]=toggle(is_raccrochage_midi_remote[IDmidi]);
            mouseClicLeft.SetProcessed();
        }
    }
    return(0);
}

int raccrochage_midi_visuel_vertical (int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

    Circle BMidiRaccroche(Xb+largeur+10,Yb+hauteur+5, 4);//raccroche midi
    if(is_raccrochage_midi_remote[IDmidi]==1)
    {
        BMidiRaccroche.Draw(CouleurFader);
//affichage niveau
        Line MonNiveauMidi(Vec2D(Xb,(Yb+hauteur) -val_raccrochage_midi[IDmidi]),Vec2D(Xb+largeur+10,(Yb+hauteur) - val_raccrochage_midi[IDmidi]));
        MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
        MonNiveauMidi.Draw(CouleurLigne);

        Line MaJonction(Vec2D(Xb+largeur+10,(Yb+hauteur)),Vec2D(Xb+largeur+10,(Yb+hauteur) - val_raccrochage_midi[IDmidi]));
        MaJonction.SetLineWidth(epaisseur_ligne_fader);
        MaJonction.Draw(CouleurFond.WithAlpha(0.0),CouleurLigne);

    }
    BMidiRaccroche.DrawOutline(CouleurLigne);
    return(0);
}


int raccrochage_midi_logical_horizontal_audio(int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

//midi racroche
    if(mouse_x>Xb+largeur+7 && mouse_x<Xb+largeur+13 && mouse_y>=Yb+hauteur+12 && mouse_y<=Yb+hauteur+18 )
    {
        if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            is_raccrochage_midi_remote[IDmidi]=toggle(is_raccrochage_midi_remote[IDmidi]);
            mouseClicLeft.SetProcessed();
        }
    }
    return(0);
}



int raccrochage_midi_visuel_horizontal_audio (int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

    Circle BMidiRaccroche(Xb+largeur+10,Yb+hauteur+15, 3);//raccroche midi
    if(is_raccrochage_midi_remote[IDmidi]==1)
    {

//affichage niveau
        Line MonNiveauMidi(Vec2D(Xb+val_raccrochage_midi[IDmidi],Yb ),Vec2D(Xb+val_raccrochage_midi[IDmidi],(Yb+hauteur)+15 ));
        MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
        MonNiveauMidi.Draw(CouleurLigne);

        Line MaJonction(Vec2D(Xb+val_raccrochage_midi[IDmidi],(Yb+hauteur)+15),Vec2D(Xb+largeur+7,(Yb+hauteur)+15));
        MaJonction.SetLineWidth(epaisseur_ligne_fader);
        MaJonction.Draw(CouleurLigne,CouleurConfig);
        BMidiRaccroche.Draw(CouleurFader);
    }
    BMidiRaccroche.DrawOutline(CouleurLigne);
    return(0);
}



///////////////////////////////////////////////////////////////////////////////////

int raccrochage_midi_logical_horizontal(int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

//midi racroche
    if(mouse_x>Xb+largeur+4 && mouse_x<Xb+largeur+16 && mouse_y>=Yb+hauteur+9 && mouse_y<=Yb+hauteur+21 )
    {
        if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            is_raccrochage_midi_remote[IDmidi]=toggle(is_raccrochage_midi_remote[IDmidi]);
            mouseClicLeft.SetProcessed();
        }
    }
    return(0);
}




int raccrochage_midi_visuel_horizontal (int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

    Circle BMidiRaccroche(Xb+largeur+10,Yb+hauteur+15, 6);//raccroche midi
    if(is_raccrochage_midi_remote[IDmidi]==1)
    {

//affichage niveau
        Line MonNiveauMidi(Vec2D(Xb+val_raccrochage_midi[IDmidi],Yb ),Vec2D(Xb+val_raccrochage_midi[IDmidi],(Yb+hauteur)+15 ));
        MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
        MonNiveauMidi.Draw(CouleurLigne);

        Line MaJonction(Vec2D(Xb+val_raccrochage_midi[IDmidi],(Yb+hauteur)+15),Vec2D(Xb+largeur+4,(Yb+hauteur)+15));
        MaJonction.SetLineWidth(epaisseur_ligne_fader);
        MaJonction.Draw(CouleurLigne,CouleurFond);
        BMidiRaccroche.Draw(CouleurFader);
    }
    BMidiRaccroche.DrawOutline(CouleurLigne);
    return(0);
}


int raccrochage_midi_logical_horizontal_little(int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

//midi racroche
    if(mouse_x>Xb+largeur+7 && mouse_x<Xb+largeur+14 && mouse_y>=Yb+hauteur+11 && mouse_y<=Yb+hauteur+18 )
    {
        if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            is_raccrochage_midi_remote[IDmidi]=toggle(is_raccrochage_midi_remote[IDmidi]);
            mouseClicLeft.SetProcessed();
        }
    }
    return(0);
}



int raccrochage_midi_visuel_horizontal_little (int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

    Circle BMidiRaccroche(Xb+largeur+10,Yb+hauteur+15, 4);//raccroche midi
    if(is_raccrochage_midi_remote[IDmidi]==1)
    {

//affichage niveau
        Line MonNiveauMidi(Vec2D(Xb+val_raccrochage_midi[IDmidi],Yb ),Vec2D(Xb+val_raccrochage_midi[IDmidi],(Yb+hauteur)+15 ));
        MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
        MonNiveauMidi.Draw(CouleurLigne);

        Line MaJonction(Vec2D(Xb+val_raccrochage_midi[IDmidi],(Yb+hauteur)+15),Vec2D(Xb+largeur+6,(Yb+hauteur)+15));
        MaJonction.SetLineWidth(epaisseur_ligne_fader);
        MaJonction.Draw(CouleurLigne,CouleurFond);
        BMidiRaccroche.Draw(CouleurFader);
    }
    BMidiRaccroche.DrawOutline(CouleurLigne);
    return(0);
}


///////////////////////////////////////////////////////////////////////////////////////////

int raccrochage_midi_logical_circulaire(int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

//midi racroche
    if(mouse_x>Xb+largeur+4 && mouse_x<Xb+largeur+16 && mouse_y>=Yb+hauteur+9 && mouse_y<=Yb+hauteur+21 )
    {
        if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            is_raccrochage_midi_remote[IDmidi]=toggle(is_raccrochage_midi_remote[IDmidi]);
            mouseClicLeft.SetProcessed();
        }
    }
    return(0);
}


int raccrochage_midi_visuel_circulaire (int Xb, int Yb, int IDmidi, int largeur, int hauteur)
{

    Circle BMidiRaccroche(Xb+largeur,Yb+hauteur+15, 6);//raccroche midi
    if(is_raccrochage_midi_remote[IDmidi]==1)
    {
        BMidiRaccroche.Draw(CouleurFader);
//affichage niveau
//attaque midi

        float tmp_angle_snap=((PI*360) / (22860))*val_raccrochage_midi[IDmidi];//((PI*360) / (180*127))*val_raccrochage_midi[IDmidi];
        float tmp_vx = cos(tmp_angle_snap)*125;
        float tmp_vy = sin(tmp_angle_snap)*125;
        float tmp_position_curseur_hue_x= xtrichro_window+tmp_vx;
        float tmp_position_curseur_hue_y=ytrichro_window+tmp_vy ;


//affichage du pointeur de hue
        Circle monCurseurHue( Vec2D(tmp_position_curseur_hue_x, tmp_position_curseur_hue_y), 10 );
        monCurseurHue.Draw( CouleurFond );
        Line MonNiveauMidi(Vec2D(Xb+largeur-6,Yb+hauteur+15 ),Vec2D(tmp_position_curseur_hue_x,Yb+hauteur+15 ));
        MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
        MonNiveauMidi.Draw(CouleurFond,CouleurLigne);

        Line MaJonction(Vec2D(tmp_position_curseur_hue_x,Yb+hauteur+15),Vec2D(tmp_position_curseur_hue_x,tmp_position_curseur_hue_y));
        MaJonction.SetLineWidth(epaisseur_ligne_fader);
        MaJonction.Draw(CouleurLigne,CouleurFond);

    }
    BMidiRaccroche.DrawOutline(CouleurLigne);
    return(0);
}

////////////////MIDI MUTE GLOBAL////////////////





int midi_send_faders_button_logical(int Xb, int Yb, int id_window)
{
    if(window_focus_id==id_window)
    {
        if(mouse_x>Xb && mouse_x<Xb+60 && mouse_y>Yb && mouse_y<Yb+20 && mouseClicLeft.isToBeProcessed())
        {
            //config midi
            if(Midi_Faders_Affectation_Type!=0)
            {
                attribute_midi_solo_affectation(1593,Midi_Faders_Affectation_Type);
                mouseClicLeft.SetProcessed();
            }
            else
            {
                index_global_midi_send_on_faders=toggle(index_global_midi_send_on_faders);
                set_all_faders_midi_out(index_global_midi_send_on_faders);
                do_light_midi_send_on_faders=1;
                mouseClicLeft.SetProcessed();
            }
        }
    }
    return(0);
}


int midi_send_faders_button_visuel(int Xb, int Yb)
{
    Rect MidiMute_B(Vec2D(Xb,Yb),Vec2D(60,20));
    MidiMute_B.SetRoundness(4);

    MidiMute_B.DrawOutline(CouleurLigne);

    petitpetitchiffre.Print("Midi Out",Xb+8,Yb+8);
    petitpetitchiffre.Print("faders",Xb+10,Yb+18);
    if(Midi_Faders_Affectation_Type!=0)
    {
        MidiMute_B.DrawOutline(CouleurBlind);
        if(do_light_midi_send_on_faders==1)
        {
            MidiMute_B.Draw(CouleurFader);
            do_light_midi_send_on_faders=0;
        }
    }
    if(mouse_x>Xb && mouse_x<Xb+60 && mouse_y>Yb && mouse_y<Yb+20)
    {
        show_type_midi(1593, "MidiOUT Faders");
    }
    return(0);
}

//sab 02/03/2014 int command_button_view( int xcom, int ycom, int isstate, char *desc, char *shortcut, int IDmidi)
void command_button_view( int xcom, int ycom, int isstate, const std::string desc, const std::string shortcut, int IDmidi)
{
    Rect Command(Vec2D(xcom,ycom),Vec2D(65,20));
    Command.SetRoundness(5);
    Command.Draw(CouleurFond.WithAlpha(0.5));

    switch(IDmidi)
    {
    case 754: //Blind
        if(isstate==1)
        {
            Command.Draw(CouleurSurvol.WithAlpha(alpha_blinker));
        }
        Command.DrawOutline(CouleurBlind);
        break;
    case 1335://freeze
        if(isstate==1)
        {
            Command.Draw(CouleurBlind.WithAlpha(alpha_blinker));
        }
        Command.DrawOutline(CouleurBlind);
        break;
    case 1541://exclude
        if(isstate==1)
        {
            Command.Draw(CouleurBlind.WithAlpha(alpha_blinker));
        }
        Command.DrawOutline(CouleurBlind);
        break;
    case 1277: //MIdi Mute
        if(isstate==1)
        {
            Command.Draw(CouleurFader.WithAlpha(alpha_blinker));
        }
        Command.DrawOutline(CouleurLigne);
        Command.DrawOutline(CouleurBleuProcedure.WithAlpha(0.5));
        break;
    case 1333://direct Ch
        if(isstate==1)
        {
            Command.Draw(CouleurFader);
        }
        if( multiple_direct_chan==1)
        {
            Command.Draw(CouleurBlind);
        }
        Command.DrawOutline(CouleurFader);
        break;
    case 1334://View
        if(isstate==1)
        {
            Command.Draw(CouleurFader);
        }
        Command.DrawOutline(CouleurFader);
        break;
    case 1542://hipass
        if( index_do_hipass==1)
        {
            Command.Draw(CouleurFader.WithAlpha(alpha_blinker));
        }
        Command.DrawOutline(CouleurFader);
        break;
    case 1592://Fgroup
        if(isstate==1)
        {
            Command.Draw(CouleurYellowFgroup);
        }
        Command.DrawOutline(CouleurFader);
        break;
    case 1625: //MIdi affect
        switch(isstate)
        {
        case 1:
            Command.Draw(CouleurLigne);
            Command.Draw(CouleurBleuProcedure.WithAlpha(alpha_blinker));
            break;
        case 2:
            Command.Draw(CouleurLigne);
            Command.Draw(CouleurBlind.WithAlpha(alpha_blinker));
            break;
        default:
            Command.DrawOutline(CouleurLigne);
            Command.DrawOutline(CouleurBleuProcedure.WithAlpha(0.5));
            break;
        }
        break;
    case 1593:
        if(do_light_midi_send_on_faders==1)
        {
            Command.Draw(CouleurFader);
            do_light_midi_send_on_faders=0;
        }
        Command.DrawOutline(CouleurLigne);
        Command.DrawOutline(CouleurBleuProcedure.WithAlpha(0.5));
        break;
    case 2047://exemple My window
        if(isstate==1)
        {
            Command.Draw(CouleurFader);
        }
        Command.DrawOutline(CouleurLigne);
        Command.DrawOutline(CouleurBleuProcedure.WithAlpha(alpha_blinker));  //animation qui est faite dans le fichier main
//chercher alpha_blinker ....
        break;
    default:
        if(isstate==1)
        {
            Command.Draw(CouleurFader);
        }
        Command.DrawOutline(CouleurLigne.WithAlpha(0.8));
        break;
    }

    if ( ( (window_focus_id==0 && index_over_A_window==0 )|| window_focus_id==W_MAINMENU) && mouse_x>xcom && mouse_x<xcom+60 && mouse_y>ycom && mouse_y<ycom+20)
    {
        if(Midi_Faders_Affectation_Type!=0 && IDmidi!=1625)
        {
            show_type_midi(IDmidi, desc);
            Command.DrawOutline(CouleurBlind);
        }
    }

    petitpetitchiffre.Print(desc,xcom+5,ycom+12);
//sab 02/03/2014 return(0);
}

//sab 02/03/2014 int command_button_logical( int xcom, int ycom, int isstate, char *desc, char *raccourci, int IDmidi, int thecommand)
void command_button_logical( int xcom, int ycom, int isstate, const std::string desc, const std::string raccourci, int IDmidi, int thecommand)
{
    if((window_focus_id==0 || window_focus_id==W_MAINMENU || window_focus_id==W_PLOT) && mouse_x>xcom && mouse_x<xcom+65 && mouse_y>ycom && mouse_y<ycom+20  && mouseClicLeft.isToBeProcessed())
    {
        if( Midi_Faders_Affectation_Type!=0)
        {
            if( IDmidi!=1625)
            {
                attribute_midi_solo_affectation(IDmidi,1);
            }
            else if( IDmidi==1625)
            {
                if(do_affectation_on_midi_affect_itself==1 )
                {
                    attribute_midi_solo_affectation(IDmidi,1);
                }
                else
                {
                    Midi_Faders_Affectation_Type++;
                    if(Midi_Faders_Affectation_Type>2)
                    {
                        Midi_Faders_Affectation_Type=0;
                    }
                    index_midi_mute=0;
                    reset_index_actions();
                }
            }

        }

        else
        {
            switch (thecommand)//permet de faire un toggle du bon index
            {
//1ere colonne
            case 0://sequenciel
                if(index_window_sequentiel==0)
                {
                    ;
                    add_a_window(W_SEQUENCIEL);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_SEQUENCIEL);
                }

                break;
            case 1://time
                if(index_time==0)
                {
                    add_a_window(W_TIME);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_TIME);
                }
                break;
            case 2://banger
                if(index_show_banger_window==0)
                {
                    add_a_window(W_BANGER);
                    mouse_level_for_event=mouse_z;
                    mouse_level_for_banger=mouse_z;
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_BANGER);
                }
                break;
            case 3://wizard
                if(index_show_wizard_window==0)
                {
                    add_a_window(W_WIZARD);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_WIZARD);
                }
                break;
            case 4://save

                if(index_menu_save==0)
                {
                    add_a_window(W_SAVE);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_SAVE);
                }
                break;
            //sab 07/08/2016 deb - Hotkeys-window
            case 5://hotkey

                if(wrkspc_dir_window_isListening==false)
                {
                    add_a_window(W_ID_WRKSPC_DIR_WINDOW);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_ID_WRKSPC_DIR_WINDOW);
                }
                break;
			//sab 07/08/2016 fin - Hotkeys-window

//2eme colonne
            case 10://patch
                if(index_patch_window==0)
                {
                    add_a_window(W_PATCH);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_PATCH);
                }
                break;
            case 11://list
                if(index_list_projecteurs==0)
                {
                    add_a_window(W_LIST);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_LIST);
                }
                break;
            case 12://plot
                if(index_plot_window==0)
                {
                    add_a_window(W_PLOT);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_PLOT);
                }
                break;
            case 13://freeze
                index_do_freeze=1;
                index_ask_confirm=1;
                break;
            case 14://do excude channels from GM
                index_do_exclude=1;
                index_ask_confirm=1;
                break;
            case 15://MY_WINDOW
                if(index_my_window==0)
                {
                    add_a_window(W_MY_WINDOW);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_MY_WINDOW);
                }
                break;

//3eme colonne
            case 20://Faders
                if(index_show_faders==0)
                {
                    add_a_window(W_FADERS);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_FADERS);
                }
                break;
            case 21://minifaders
                if(index_show_minifaders==0)
                {
                    add_a_window(W_MINIFADERS);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_MINIFADERS);
                }
                break;
            case 22://trichromy
                if(index_trichro_window==0)
                {
                    add_a_window(W_TRICHROMY);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_TRICHROMY);
                }
                break;
            case 23://chasers
                if(index_window_chasers==0)
                {
                    add_a_window(W_CHASERS);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_CHASERS);
                }
                break;
            case 24://grider
                if(index_grider_window==0)
                {
                    add_a_window(W_GRID);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_GRID);
                }
                break;
            case 25:
                if(index_bazoocat_menu_window==0)
                {
                    add_a_window(W_BAZOOKAT);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_BAZOOKAT);
                }
                break;


//4eme colonne

            case 30://tracking
                if(index_video_window==0)
                {
                    add_a_window(W_TRACKINGVIDEO);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_TRACKINGVIDEO);
                }
                break;

            case 31://mover
                if(index_show_mover_window==0)
                {
                    add_a_window(W_MOVER);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_MOVER);
                }
                break;
            case 32://echo
                if(index_show_echo_window==0)
                {
                    add_a_window(W_ECHO);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_ECHO);
                }
                break;
            case 33://audioplayers
                if(index_show_audio_window==0)
                {
                    add_a_window(W_AUDIO);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_AUDIO);
                }
                reset_audio_indexs_to_dock();
                break;
            case 34://name
                index_type=toggle(index_type);
                strcpy(numeric,"");
                keyboardStorage_numeric_postext=0;
                break;
            case 35://draw
                if(index_draw_window==0)
                {
                    add_a_window(W_DRAW);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_DRAW);
                }
                break;

//5eme colonne
            case 40://CFG MENU
                if(index_show_config_window==0)
                {
                    add_a_window(W_CFGMENU);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_CFGMENU);
                }
                break;
            case 41://iCat
                if(index_window_gui_iCat==0)
                {
                    add_a_window(W_iCAT);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_iCAT);
                }
                break;
            case 42: //npad
                if(index_visual_pad==0)
                {
                    add_a_window(W_NUMPAD);
                    substract_a_window(W_MAINMENU);
                }
                else
                {
                    substract_a_window(W_NUMPAD);
                }
                break;
            case 43://help
                index_call_help=toggle(index_call_help);
                if(index_call_help==1)
                {
                    char txtsp[1024];
//sprintf(txtsp,"start /max file://%sdoc/export/introduction.htm",mondirectory);
//system("start /max file://C:/white_cat/doc/export/introduction.htm");};
                    sprintf(txtsp,"iexplore www.le-chat-noir-numerique.fr/whitecat/dokuwiki/doku.php");
                    system(txtsp);
                    index_call_help=0;
                    substract_a_window(W_MAINMENU);
                }
                break;
            case 44://quit
                index_ask_confirm=1;
                index_do_quit_with_save=1;
                break;
/////////////////////////////////////////////////////////////////////////////////
//extras hors menus déroulants ext
            case 100:
                plot_index_show_levels=toggle(plot_index_show_levels);
                break;
            case 101:
                plot_index_show_levels_from_faders=toggle(plot_index_show_levels_from_faders);
                break;

            case 102: //dock
                if(index_do_dock==0)
                {
                    reset_index_actions();
                }
                index_do_dock=toggle(index_do_dock);

                switch (window_focus_id)
                {
                case W_CHASERS:
                    index_affect_chaser_to_dock=index_do_dock;
                    break;
                case W_GRID:
                    for(int i=0; i<4; i++)
                    {
                        if(index_show_grid_player[i]==1)
                        {
                            gridplayer_to_affect_is=i;
                            break;
                        }
                    }
                    break;
                case W_MOVER:
                    index_affect_to_dock_mover=index_do_dock;
                    break;
                case W_DRAW:
                    index_affect_draw_to_dock=index_do_dock;
                    break;
                case W_ECHO:
                    index_affect_echo_to_dock=index_do_dock;
                    break;
                case W_TIME:
                    index_affect_time=index_do_dock;
                    break;
                case W_TRACKINGVIDEO:
                    index_affect_video_tracking_to_dock=index_do_dock;
                    break;
                case W_TRICHROMY:
                    index_affect_color_to_dock=index_do_dock;
                    break;
                case W_AUDIO:
                    index_affect_audio_to_dock=index_do_dock;
                    player_to_affect_to_dock=0;
                    audio_type_for_dock_affectation_is=0;
                    break;
                case W_CFGMENU:
                    if(config_page_is==1)
                    {
                        index_affect_dmxin=index_do_dock;
                    }
                    else if(config_page_is==3)
                    {
                        index_do_affect_net_to_dock=index_do_dock;
                    }
                    break;
                default:
                    break;
                }

                break;
            case 103: //modify
                if(index_do_modify==0)
                {
                    reset_index_actions();
                }
                index_do_modify=toggle(index_do_modify);
                break;
            case 104://report
                if(index_do_report==0)
                {
                    reset_index_actions();
                }
                index_do_report=toggle(index_do_report);
                break;
            case 105://clear
                if(index_main_clear==0)
                {
                    reset_index_actions();
                }
                index_main_clear=toggle(index_main_clear);
                break;
            case 106://midi affect solo
                Midi_Faders_Affectation_Type++;
                if(Midi_Faders_Affectation_Type>2)
                {
                    Midi_Faders_Affectation_Type=0;
                }
                index_midi_mute=0;
                reset_index_actions();
                break;
            case 107://midi mute
                reset_index_actions();
                index_midi_mute=toggle(index_midi_mute);
                if(index_midi_mute==1)
                {
                    for(int y=0; y<2048; y++)
                    {
                        is_raccrochage_midi_remote[y]=1;
                    }
                    sprintf(string_Last_Order,">>Midi IN muted");
                }
                else
                {
                    for(int y=0; y<2048; y++)
                    {
                        is_raccrochage_midi_remote[y]=0;
                    }
                    sprintf(string_Last_Order,">>Midi IN un-muted");
                }
                break;
            case 108://MAIN MENU
                if(mouseClicLeft.isToBeProcessed())
                {

                    mouseClicLeft.SetProcessed();
                    switch(index_show_main_menu)
                    {
                    case 0:
                        add_a_window(W_MAINMENU);
                        index_show_main_menu=1;
                        break;
                    case 1:
                        substract_a_window(W_MAINMENU);
                        index_show_main_menu=0;
                        break;
                    default:
                        break;
                    }

                }
                break;
            case 109://Midi refresh fader send out
                index_global_midi_send_on_faders=toggle(index_global_midi_send_on_faders);
                set_all_faders_midi_out(index_global_midi_send_on_faders);
                do_light_midi_send_on_faders=1;
                break;
            case 110://BLIND
                index_blind=toggle(index_blind);
                break;
            case 111: //direct CH
                if(index_direct_chan==0 && multiple_direct_chan==0)
                {
                    reset_index_actions();
                    reset_indexs_confirmation();
                    index_direct_chan=1;
                    index_do_dock=index_direct_chan;
                }
                else if(index_direct_chan==1 && multiple_direct_chan==0)
                {
                    index_direct_chan=1;
                    multiple_direct_chan=1;
                    index_do_dock=1;
                }
                else if(index_direct_chan==1 && multiple_direct_chan==1)
                {
                    reset_index_actions();
                    reset_indexs_confirmation();
                }

                break;
            case 112: // view
                index_inspekt=toggle(index_inspekt);
                i_m_over_a_track=0;
                break;
            case 113://HIPASS
                index_do_hipass=toggle( index_do_hipass);
                index_inspekt=index_do_hipass;
                break;
            case 114://FGROUP
                if(index_do_fgroup==0)
                {
                    reset_index_actions();
                    reset_indexs_confirmation();
                    index_do_fgroup=1;
                }
                else
                {
                    reset_index_actions();
                }
                index_do_dock=index_do_fgroup;
                break;
            default:
                break;
            }
        }

        if(index_show_main_menu==1 )
        {
            window_bring_to_front(W_MAINMENU);
        }
        mouseClicLeft.SetProcessed();
    }




//sab 02/03/2014  return(0);
}

