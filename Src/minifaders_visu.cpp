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

* \file minifaders_visu.cpp
* \brief {minifaders GUI}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions GUI du dessin de la fenêtre des mini faders
*
*   Minifaders GUI fonctions for the minifaders windows
*
**/

int draw_sign_up(int xs,int ys)
{
    Line(Vec2D(xs+12,ys+5),Vec2D(xs+12,ys+20)).Draw(CouleurLigne);//barre milieu vert
    Line(Vec2D(xs+12,ys+5),Vec2D(xs+5,ys+10)).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+5),Vec2D(xs+19,ys+10)).Draw(CouleurLigne);
    Line(Vec2D(xs+5,ys+5),Vec2D(xs+20,ys+5)).Draw(CouleurLigne);//barre d arret
    return(0);
}
int draw_sign_down(int xs,int ys)
{
    Line(Vec2D(xs+12,ys+2),Vec2D(xs+12,ys+15)).Draw(CouleurLigne);//barre milieu vert
    Line(Vec2D(xs+12,ys+15),Vec2D(xs+5,ys+10)).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+15),Vec2D(xs+19,ys+10)).Draw(CouleurLigne);
    Line(Vec2D(xs+5,ys+15),Vec2D(xs+20,ys+15)).Draw(CouleurLigne);//barre d arret
    return(0);
}
int draw_sign_saw(int xs,int ys)
{
    Line(Vec2D(xs+5,ys+5),Vec2D(Vec2D(xs+10,ys+15))).Draw(CouleurLigne);
    Line(Vec2D(xs+10,ys+15),Vec2D(Vec2D(xs+15,ys+5))).Draw(CouleurLigne);
    Line(Vec2D(xs+15,ys+5),Vec2D(Vec2D(xs+20,ys+15))).Draw(CouleurLigne);
    return(0);
}
int draw_sign_prev(int xs,int ys)
{
    Line(Vec2D(xs,ys+15),Vec2D(Vec2D(xs+12,ys+15))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+10),Vec2D(Vec2D(xs+12,ys+15))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+5),Vec2D(Vec2D(xs+9,ys+10))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+5),Vec2D(Vec2D(xs+15,ys+10))).Draw(CouleurLigne);
    return(0);
}

int draw_sign_next(int xs,int ys)
{
    Line(Vec2D(xs,ys+5),Vec2D(Vec2D(xs+12,ys+5))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+5),Vec2D(Vec2D(xs+12,ys+15))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+15),Vec2D(Vec2D(xs+9,ys+10))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+15),Vec2D(Vec2D(xs+15,ys+10))).Draw(CouleurLigne);
    return(0);
}

int draw_sign_up_down(int xs, int ys)
{
    Line(Vec2D(xs+12,ys+10),Vec2D(Vec2D(xs+12,ys+20))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+20),Vec2D(Vec2D(xs+9,ys+15))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+20),Vec2D(Vec2D(xs+15,ys+15))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+10),Vec2D(Vec2D(xs+12,ys+5))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+5),Vec2D(Vec2D(xs+9,ys+10))).Draw(CouleurLigne);
    Line(Vec2D(xs+12,ys+5),Vec2D(Vec2D(xs+15,ys+10))).Draw(CouleurLigne);
    return(0);
}

int show_fgroup_in_minifaders_window(int xs, int ys, int fad, int dk)
{
    petitpetitchiffre.Print("Fgroup in f", xs+5,ys);
    petitpetitchiffre.Print(ol::ToString(over_minifader+1), xs+65,ys);
    Rect FgOn(Vec2D(xs,ys),Vec2D(10,10));

    for(int u=0; u<8; u++)
    {
        for (int i=0; i<6; i++)
        {
            if(DockTypeIs[fad][dk]==13)
            {
                FgOn.MoveTo(Vec2D(xs+3+(15*i),ys+13+(20*u)));
                FgOn.Draw(CouleurFader.WithAlpha(0.8*fgroup[fad][dk][(u*6)+i]));
            }

            minichiffre.Print(ol::ToString((u*6)+i+1),xs+5+(15*i),ys+20+(20*u));
        }
    }
    return(0);
}


int all_at_zero_panel_visu(int xf, int yf)
{

    char str_titre[15];
    petitpetitchiffre.Print("AtZero",xf+10,yf+5);
    Rect Commande(Vec2D(xf,yf),Vec2D(50,20));
    Commande.SetRoundness(4);

    for (int u=0; u<8; u++)
    {
        Commande.MoveTo(Vec2D(xf,yf+10+(25*u)));
        Commande.DrawOutline(CouleurLigne.WithAlpha(0.5));
        switch(u)
        {
        case 0:
            sprintf(str_titre,"Faders");
            break;
        case 1:
            sprintf(str_titre,"Speed");
            break;
        case 2:
            sprintf(str_titre,"Lock");
            break;
        case 3:
            sprintf(str_titre,"LFO");
            break;
        case 4:
            sprintf(str_titre,"Loop");
            break;
        case 5:
            sprintf(str_titre,"ALL");
            break;
        case 6:
            sprintf(str_titre,"MidiOut");
            break;
        case 7:
            sprintf(str_titre,"RECALL");
            break;
        default: break;
        }
        if(window_focus_id==W_MINIFADERS && mouse_x>xf && mouse_x<xf+50 && mouse_y>yf+10+(25*u) && mouse_y<yf+30+(25*u))
        {
//midi report
            switch(miditable[0][548+u])
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
            default: break;
            }
            sprintf(string_last_midi_id,"AtZero Command %d is Ch: %d Pitch: %d Type: %s",u, miditable[1][548+u],miditable[2][548+u],thetypinfo);
            //config midi

            if( Midi_Faders_Affectation_Type!=0)
            {

                Commande.DrawOutline(CouleurBlind);
            }

        }

        petitchiffre.Print(str_titre,xf+5,yf+23+(25*u));
    }

    return(0);
}

int mini_faders_panel_visu(int xmf, int ymf, int larg)
{
    Rect FondMiniFaders(Vec2D(xmf-10,ymf-50),Vec2D(700,450));
    FondMiniFaders.SetRoundness(15);
    FondMiniFaders.SetLineWidth(triple_epaisseur_ligne_fader);
    FondMiniFaders.Draw(CouleurFond);
    if(window_focus_id==922)
    {
        FondMiniFaders.DrawOutline(CouleurFader);
    }
    else
    {
        FondMiniFaders.DrawOutline(CouleurLigne);
    }


    neuro.Print("MINIFADERS",xmf+85, ymf-20);

////LE SYSTEME D ORDRES////////////////////////////////////////////////////////
    Rect SelAllFader(Vec2D(xmf+(24*larg)+10,ymf-25),Vec2D(45,20));
    SelAllFader.SetRoundness(4);
    if(do_light_minifaders_commands[23]==1)
    {
        SelAllFader.Draw(CouleurFader);
        do_light_minifaders_commands[23]=0;
    }
    SelAllFader.DrawOutline(CouleurLigne);
    petitchiffre.Print("ALL",xmf+(24*larg)+20,ymf-10);
////////////////////////////////////////////////////////////////////////////
    Rect FaderLittlePrevSel(Vec2D(xmf+(24*larg)+10,ymf),Vec2D(20,20));
    FaderLittlePrevSel.SetRoundness(3);
    FaderLittlePrevSel.DrawOutline(CouleurLigne);
    petitdoomblanc.Print("<",xmf+(24*larg)+15,ymf+15);
    if(do_light_minifaders_commands[0]==1)
    {
        FaderLittlePrevSel.Draw(CouleurFader);
        do_light_minifaders_commands[0]=0;
    }
    Rect FaderLittleNextSel(Vec2D(xmf+(24*larg)+35,ymf),Vec2D(20,20));
    FaderLittleNextSel.SetRoundness(3);
    FaderLittleNextSel.DrawOutline(CouleurLigne);
    petitdoomblanc.Print(">",xmf+(24*larg)+35,ymf+15);
    if(do_light_minifaders_commands[1]==1)
    {
        FaderLittleNextSel.Draw(CouleurFader);
        do_light_minifaders_commands[1]=0;
    }

    Rect SelFader(Vec2D(xmf+(24*larg)+10,ymf+25),Vec2D(45,20));
    SelFader.SetRoundness(4);
    SelFader.DrawOutline(CouleurLigne);
    petitchiffre.Print("select",xmf+(24*larg)+13,ymf+38);
    if(do_light_minifaders_commands[2]==1)
    {
        SelFader.Draw(CouleurFader);
        do_light_minifaders_commands[2]=0;
    }

    Rect UnSelFader(Vec2D(xmf+(24*larg)+10,ymf+50),Vec2D(45,20));
    UnSelFader.SetRoundness(4);
    UnSelFader.DrawOutline(CouleurLigne);
    petitchiffre.Print("unsel.",xmf+(24*larg)+13,ymf+63);
    if(do_light_minifaders_commands[3]==1)
    {
        UnSelFader.Draw(CouleurFader);
        do_light_minifaders_commands[3]=0;
    }



    if(window_focus_id==W_MINIFADERS && mouse_y>ymf-25 && mouse_y<ymf-5 )
    {
        if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+55)
        {
            if( Midi_Faders_Affectation_Type!=0)
            {
                SelAllFader.DrawOutline(CouleurBlind);
            }
//midi report
            switch(miditable[0][96])
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
            default: break;
            }
            sprintf(string_last_midi_id,"Select All is Ch: %d Pitch: %d Type: %s", miditable[1][96],miditable[2][96],thetypinfo);

        }
    }


    if(window_focus_id==W_MINIFADERS && mouse_y>ymf && mouse_y<ymf+20 )
    {
        if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+30)
        {
            if( Midi_Faders_Affectation_Type!=0)
            {
                FaderLittlePrevSel.DrawOutline(CouleurBlind);
            }
//midi report
            switch(miditable[0][774])
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
            default: break;
            }
            sprintf(string_last_midi_id,"Select Previous is Ch: %d Pitch: %d Type: %s", miditable[1][774],miditable[2][774],thetypinfo);

        }
        else if(mouse_x>xmf+(24*larg)+35 && mouse_x<xmf+(24*larg)+55)
        {
            if(Midi_Faders_Affectation_Type!=0)
            {
                FaderLittleNextSel.DrawOutline(CouleurBlind);
            }
//midi report
            switch(miditable[0][775])
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
            default: break;
            }
            sprintf(string_last_midi_id,"Select Next is Ch: %d Pitch: %d Type: %s", miditable[1][775],miditable[2][775],thetypinfo);

        }
    }
//select
    if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+55 && window_focus_id==922)
    {
        if(mouse_y>ymf+25 && mouse_y<ymf+45 )
        {
            if(Midi_Faders_Affectation_Type!=0)
            {
                SelFader.DrawOutline(CouleurBlind);
            }

//midi report
            switch(miditable[0][776])
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
            default: break;
            }
            sprintf(string_last_midi_id,"Select is Ch: %d Pitch: %d Type: %s", miditable[1][776],miditable[2][776],thetypinfo);

        }
        else if(mouse_y>ymf+50 && mouse_y<ymf+70 )
        {

            if( Midi_Faders_Affectation_Type!=0)
            {
                UnSelFader.DrawOutline(CouleurBlind);
            }
//midi report
            switch(miditable[0][777])
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
            default: break;
            }
            sprintf(string_last_midi_id,"UnSelect is Ch: %d Pitch: %d Type: %s", miditable[1][777],miditable[2][777],thetypinfo);


        }
    }


/////////////////LES ACTIONS////////////////////////////////////////////////////
    Rect FaderLittleCmd(Vec2D(xmf,ymf),Vec2D(20,20));
    FaderLittleCmd.SetRoundness(3);
    for(int lu=0; lu<5; lu++)
    {
        for(int llu=0; llu<3; llu++)
        {
            int numcom=(lu*3)+llu;
            FaderLittleCmd.MoveTo(Vec2D(xmf+(24*larg)+70+(lu*25),ymf+(llu*25)));

            if(do_light_minifaders_commands[numcom+4]==1)
            {
                FaderLittleCmd.Draw(CouleurFader);
                do_light_minifaders_commands[numcom+4]=0;
            }
            FaderLittleCmd.DrawOutline(CouleurLigne);

//mouse action:
            if(mouse_x>xmf+(24*larg)+70+(lu*25) && mouse_x<xmf+(24*larg)+90+(lu*25) && mouse_y>ymf+(llu*25) && mouse_y<ymf+(llu*25)+20)
            {

                if(Midi_Faders_Affectation_Type!=0)
                {
                    FaderLittleCmd.DrawOutline(CouleurBlind);
                }
//midi report
                switch(miditable[0][778+numcom])
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
                default: break;
                }
                char tmp_c[36];
                switch(numcom)
                {
                case 0:
                    sprintf(tmp_c,"Flash");
                    break;
                case 1:
                    sprintf(tmp_c,"Lock");
                    break;
                case 2:
                    sprintf(tmp_c,"Loop");
                    break;
                case 3:
                    sprintf(tmp_c,"Lfo UP");
                    break;
                case 4:
                    sprintf(tmp_c,"Lfo DOWN");
                    break;
                case 5:
                    sprintf(tmp_c,"Lfo SAW");
                    break;
                case 6:
                    sprintf(tmp_c,"All Dock Looped");
                    break;
                case 7:
                    sprintf(tmp_c,"All at 0");
                    break;
                case 8:
                    sprintf(tmp_c,"Set Pos");
                    break;
                case 9:
                    sprintf(tmp_c,"To Prev Dock");
                    break;
                case 10:
                    sprintf(tmp_c,"To Next Dock");
                    break;
                case 11:
                    sprintf(tmp_c,"Up and Down");
                    break;
                case 12:
                    sprintf(tmp_c,"Sel Prev Dock");
                    break;
                case 13:
                    sprintf(tmp_c,"Sel Next Dock");
                    break;
                case 14:
                    sprintf(tmp_c,"Play Chaser");
                    break;
                default: break;
                }

                sprintf(string_last_midi_id,"%s is Ch: %d Pitch: %d Type: %s",tmp_c, miditable[1][778+numcom],miditable[2][778+numcom],thetypinfo);

                if(numcom==0 && window_focus_id==W_MINIFADERS)//flash
                {
//BLOCK FLASHqui doit etre dans boucle principale et pas dans le core qui checke la souris
                    if(  mouse_button==1 &&  mouse_released==0)
                    {
                        if( Midi_Faders_Affectation_Type!=0)
                        {
                            attribute_midi_solo_affectation(778+numcom,1);
                            mouse_released=1;
                        }
                        else
                        {
                            for(int tt=0; tt<core_user_define_nb_faders; tt++)
                            {
                                if( minifaders_selected[tt]==1  && FaderIsFlash[tt]==0)
                                {
                                    FaderIsFlash[tt]=1;
                                }
                            }
                        }
                    }
                    else if(mouse_released==1 && midi_levels[778]==0)
                    {
                        for(int tn=0; tn<core_user_define_nb_faders; tn++)
                        {
                            if( minifaders_selected[tn]==1)
                            {
                                FaderIsFlash[tn]=0;
                            }
                        }
                    }
//FIN BLOCK FLASH
                }
            }
//affichages

            if(numcom== 0)//flash
            {
                petitchiffre.Print("FL",xmf+(24*larg)+70+(lu*25)+4,ymf+(llu*25)+14);
            }
            else if (numcom==1)
            {
                petitchiffre.Print("LcK",xmf+(24*larg)+70+(lu*25)+2,ymf+(llu*25)+14);
            }
            else if (numcom==2)
            {
                //loop one
                Circle OLLoop(Vec2D((xmf+(24*larg)+70+(lu*25)+10),(ymf+(llu*25)+10)),5);
                OLLoop.Draw(CouleurFader);
                OLLoop.DrawOutline(CouleurLigne);
            }
            else if (numcom==3)
            {
                //up
                draw_sign_up(xmf+(24*larg)+68+(lu*25),ymf+(llu*25));
            }
            else if (numcom==4)
            {
                //down
                draw_sign_down(xmf+(24*larg)+68+(lu*25),ymf+(llu*25));
            }
            else if (numcom==5)
            {
                //saw
                draw_sign_saw(xmf+(24*larg)+68+(lu*25),ymf+(llu*25));
            }
            else if (numcom==6)
            {
                //loop all
                Circle OLLoopA(Vec2D((xmf+(24*larg)+80+(lu*25)),(ymf+(llu*25)+5)),2);
                OLLoopA.Draw(CouleurFader);
                OLLoopA.DrawOutline(CouleurLigne);
                OLLoopA.MoveBy(Vec2D(0,5));
                OLLoopA.Draw(CouleurFader);
                OLLoopA.DrawOutline(CouleurLigne);
                OLLoopA.MoveBy(Vec2D(0,5));
                OLLoopA.Draw(CouleurFader);
                OLLoopA.DrawOutline(CouleurLigne);
            }
            else if (numcom==7)
            {
                //All:AllAt0
                petitchiffre.Print("X",xmf+(24*larg)+76+(lu*25),ymf+(llu*25)+14);
            }
            else if (numcom==8)
            {
                //set pos
                petitpetitchiffre.Print("set",xmf+(24*larg)+72+(lu*25),ymf+(llu*25)+10);
                petitpetitchiffre.Print("Po",xmf+(24*larg)+76+(lu*25),ymf+(llu*25)+19);
            }
            else if (numcom==9)
            {
                //move to prev dock
                draw_sign_prev(xmf+(24*larg)+68+(lu*25),ymf+(llu*25));
            }
            else if (numcom==10)
            {
                //move next dock
                draw_sign_next(xmf+(24*larg)+68+(lu*25),ymf+(llu*25));
            }
            else if (numcom==11)
            {
                //aller retour
                draw_sign_up_down(xmf+(24*larg)+68+(lu*25),ymf+(llu*25)-2);
            }
            else if(numcom==12)
            {
                //minus dock
                petitpetitchiffre.Print("D-",xmf+(24*larg)+74+(lu*25),ymf+(llu*25)+12);
            }
            else if(numcom==13)
            {
                //+ dock
                petitpetitchiffre.Print("D+",xmf+(24*larg)+74+(lu*25),ymf+(llu*25)+12);
            }
            else if(numcom==14)
            {
//play chaser embeded
                Line(Vec2D(xmf+(24*larg)+76+(lu*25),ymf+(llu*25)+4),Vec2D(xmf+(24*larg)+76+(lu*25),ymf+(llu*25)+16)).Draw(CouleurLigne);
                Line(Vec2D(xmf+(24*larg)+76+(lu*25),ymf+(llu*25)+4),Vec2D(xmf+(24*larg)+86+(lu*25),ymf+(llu*25)+10)).Draw(CouleurLigne);
                Line(Vec2D(xmf+(24*larg)+76+(lu*25),ymf+(llu*25)+16),Vec2D(xmf+(24*larg)+86+(lu*25),ymf+(llu*25)+10)).Draw(CouleurLigne);
            }


        }
    }

//les presets de sélections de faders//////////////////////////////////////////////////////////
    petitpetitchiffre.Print("Pst",xmf+(24*larg)+10,ymf+85);


    Rect FaderPstCmd(Vec2D(xmf,ymf),Vec2D(20,20));
    FaderPstCmd.SetRoundness(3);
    for(int lg=0; lg<8; lg++)
    {
        FaderPstCmd.MoveTo(Vec2D(xmf+(24*larg)+10,ymf+90+(lg*25)));


        if(mf_preset_selected_is==lg && minifader_preset_is_empty[lg]==0)
        {
            FaderPstCmd.Draw(CouleurFader);
        }
        FaderPstCmd.DrawOutline(CouleurLigne);

        petitpetitchiffre.Print(ol::ToString(lg+1),xmf+(24*larg)+17,ymf+102+(lg*25));
        if(minifader_preset_is_empty[lg]==1)
        {
            petitpetitchiffre.Print("-",xmf+(24*larg)+12,ymf+109+(lg*25));
        }
        if(mouse_x>xmf+(24*larg)+10 && mouse_x<xmf+(24*larg)+30 && mouse_y>ymf+90+(lg*25) && mouse_y<ymf+110+(lg*25))
        {

            if(Midi_Faders_Affectation_Type!=0)
            {
                FaderPstCmd.DrawOutline(CouleurBlind);
            }


        }
    }
////////////Les locks presets///////////////////////////////////////////////////
    petitpetitchiffre.Print("LckPst",xmf+(24*larg)+30,ymf+85);
    Rect Lock(Vec2D(xmf,ymf),Vec2D(20,20));
    Lock.SetRoundness(3);

    for(int lck=0; lck<8; lck++)
    {
        Lock.MoveTo(Vec2D(xmf+(24*larg)+35,ymf+90+(lck*25)));
        Lock.DrawOutline(CouleurLock);

        if(lock_preset[lck]==1)
        {
            Lock.Draw(CouleurLock);
        }
        petitpetitchiffre.Print(ol::ToString(lck+1),xmf+(24*larg)+38,ymf+102+(lck*25));
        detect_master_lock(lck);
        char mast[8];
        sprintf(mast,"%d",master_lock_preset[lck]);
        petitpetitchiffrerouge.Print(mast,xmf+(24*larg)+46,ymf+107+(lck*25));

        if(mouse_x>xmf+(24*larg)+35 && mouse_x<xmf+(24*larg)+55 && mouse_y>ymf+90+(lck*25) && mouse_y<ymf+110+(lck*25))
        {

            if( Midi_Faders_Affectation_Type!=0)
            {
                Lock.DrawOutline(CouleurBlind);
            }



        }
    }
/////////////////ALL AT 0///////////////////////////////////////////////////////
    all_at_zero_panel_visu((xmf+24*larg)+60,ymf+80);


    midi_send_faders_button_visuel((xmf+24*larg)+140,ymf-40);
//affichage fgroup space
    show_fgroup_in_minifaders_window((xmf+24*larg)+115,ymf+85,over_minifader,dock_used_by_fader_is[over_minifader]);


///////////////affichage contenu dock survole///////////////////////////////////////////////////
    Rect FaderDescr(Vec2D(xmf+(24*larg)+5,ymf+290),Vec2D(160,100));
    FaderDescr.SetRoundness(6);
    FaderDescr.Draw(CouleurSurvol.WithAlpha(0.5));
    for (int iog=0; iog<10; iog++)
    {
        petitpetitchiffre.Print(str_minifader_feedback[iog],xmf+(24*larg)+10,ymf+305+(iog*10));
    }
////////////////////////////////////////////////////////////////////////////////
/////////////////////////LES 48 FADERS/////////////////////////////////////////
    int hmfd=200;//hauteur d une ligne de 24 faders

    Rect FaderSelB(Vec2D(xmf,ymf),Vec2D(larg-2,15));
    FaderSelB.SetRoundness(3);
    Rect FxMode(Vec2D(xmf,ymf),Vec2D(larg-2,5));
    Rect FaderLittle(Vec2D(xmf,ymf),Vec2D(larg-5,127));
    FaderLittle.SetRoundness(3);
    Rect FlashTouch(Vec2D(xmf,ymf),Vec2D(larg-5,10));
    FlashTouch.SetRoundness(3);
    Rect DB(Vec2D(xmf, ymf+20),Vec2D( larg-5,7 ));
    DB.SetRoundness(1);


    for(int cmptfader=0; cmptfader<max_faders/2; cmptfader++)
    {
        for(int lfad=0; lfad<2; lfad++)
        {
            if(cmptfader+(lfad*24)<=core_user_define_nb_faders-1)//limitation nbre faders
            {
                FaderSelB.MoveTo(Vec2D(xmf+(cmptfader*larg)-1,ymf+(lfad*hmfd)-2));

                FaderSelB.Draw(CouleurLigne.WithAlpha(0.3));

//mode compositing
                FxMode.MoveTo(Vec2D(xmf+(cmptfader*larg)-1,ymf+(lfad*hmfd)-12));
                switch(fader_mode_with_buffers[cmptfader+(lfad*24)])
                {
                case 0://normal HTP
                    FxMode.Draw(CouleurFader);
                    break;
                case 1://off
                    FxMode.Draw(CouleurFond);
                    break;
                case 2://minus
                    FxMode.Draw(CouleurRougePur);
                    break;
                case 3://add
                    FxMode.Draw(CouleurLigne);
                    break;
                case 4://screen
                    FxMode.Draw(CouleurLevel);
                    break;
                case 5://exclusion
                    FxMode.Draw(CouleurBleuProcedure.WithAlpha(0.7));
                    break;
                default:
                    break;
                }


                if(  window_focus_id==W_MINIFADERS && Midi_Faders_Affectation_Type!=0
                        && mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg && mouse_y>(ymf+(lfad*hmfd))-12  && mouse_y<(ymf+(lfad*hmfd))-7 )
                {
                    char temp_str_tr[72];
                    sprintf(temp_str_tr,"Fx mode on fader %d",cmptfader+(lfad*24)+1);
                    show_type_midi(1543+cmptfader+(lfad*24),temp_str_tr );
                    FxMode.DrawOutline(CouleurBlind);
                }

                if(position_minifader_selected==(cmptfader+(lfad*24)))
                {
                    FaderSelB.DrawOutline(CouleurLigne);
                }

                FaderLittle.MoveTo(Vec2D(xmf+(cmptfader*larg),ymf+20+(lfad*hmfd)));
                int niveau=(int)Fader[cmptfader+(lfad*24)];
                Rect FaderLittleNiveau( Vec2D(  xmf+(cmptfader*larg),(ymf+127)+20+(lfad*hmfd) - (niveau/2)), Vec2D ( larg-5,(niveau/2)));//niveau fader
                FaderLittleNiveau.SetRoundness(4);
                myalpha=((float)niveau/255);

                if(FaderLocked[cmptfader+(lfad*24)]==0)
                {
                    switch(DockTypeIs[cmptfader+(lfad*24)][(dock_used_by_fader_is[cmptfader +(lfad*24)])])
                    {
                    default:
                        FaderLittleNiveau.Draw(CouleurFader.WithAlpha(myalpha));
                        break;
                    case 6://audio
                        FaderLittleNiveau.Draw(CouleurNiveau);
                        break;
                    case 7:
                        FaderLittleNiveau.Draw(CouleurNiveau);
                        break;
                    case 8:
                        FaderLittleNiveau.Draw(CouleurNiveau);
                        break;
                    case 11://chaser
                        if (chaser_is_playing[ChaserAffectedToDck[cmptfader+(lfad*24)][dock_used_by_fader_is[cmptfader+(lfad*24)]]]==0)
                        {
                            FaderLittleNiveau.Draw(CouleurGreen);
                        }
                        else
                        {
                            FaderLittleNiveau.Draw(CouleurGreen.WithAlpha(alpha_blinker));
                        }
                        break;
                    case 12:
                        if(grider_is_playing[faders_dock_grid_affectation[cmptfader+(lfad*24)][dock_used_by_fader_is[cmptfader+(lfad*24)]]]==0)
                        {
                            FaderLittleNiveau.Draw(CouleurBlind);
                        }
                        else
                        {
                            FaderLittleNiveau.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                        }
                        break;
                    case 13://Fgroup
                        FaderLittleNiveau.Draw(CouleurYellowFgroup);
                        break;
                    case 14://mover
                        FaderLittleNiveau.Draw( CouleurSelection);
                        break;
                    case 15://draw
                        FaderLittleNiveau.Draw(CouleurLevel);
                        break;
                    case 16://echo
                        FaderLittleNiveau.Draw(Discrete8);
                        break;
                    }
                }
                else//fader locké
                {
                    FaderLittleNiveau.Draw(CouleurLock.WithAlpha(myalpha*2));//couleur en vert emeraude
                    if(LockFader_is_FullLevel[cmptfader+(lfad*24)]==1 && actual_master_lock==cmptfader+(lfad*24))
                    {
                        //marker rouge rouge du niveau at full lors lockage
                        petitchiffrerouge.Print("m",xmf+(cmptfader*larg)+3, ymf+35+(lfad*hmfd) );
                    }
                }
                FaderLittle.DrawOutline(CouleurLigne.WithAlpha(0.6));

//si dock actif du fader vide
                if(  DockTypeIs[cmptfader+(lfad*24)] [dock_used_by_fader_is[cmptfader+(lfad*24)]]== 9 )
                {
                    neuromoyen.Print("-" ,xmf+(cmptfader*larg)+3, ymf+60+(lfad*hmfd) );
                }

//raccrochage midi

                if(is_raccrochage_midi_remote[cmptfader +(lfad*24)]==1)
                {
//affichage niveau
                    Line MonNiveauMidi(Vec2D(xmf+(cmptfader*larg),ymf+20+(lfad*hmfd)+127 -val_raccrochage_midi[cmptfader +(lfad*24)]),Vec2D(xmf+(cmptfader*larg)+larg-5,ymf+20+(lfad*hmfd)+127 -val_raccrochage_midi[cmptfader +(lfad*24)]));
                    MonNiveauMidi.SetLineWidth(epaisseur_ligne_fader);
                    MonNiveauMidi.Draw(CouleurLigne);
                }


                FaderSelB.Draw(CouleurBlind.WithAlpha( minifaders_selected[cmptfader +(lfad*24)]));

                petitdoomInspekt.Print(ol::ToString(cmptfader+1 +(lfad*24)),xmf+(cmptfader*larg), ymf+10+(lfad*hmfd));

                switch(dmx_view)
                {
                case 0:
                    if(FaderLocked[cmptfader+(lfad*24)]==1)
                    {
                        petitpetitchiffrerouge.Print(ol::ToString((int)((float)(StateOfFaderBeforeLock[cmptfader +(lfad*24)])/2.55)),xmf+(cmptfader*larg),ymf+170+(lfad*hmfd));
                    }
                    sprintf(string_niveau, "%d",(int)(((float)niveau)/2.55));
                    break;
                case 1:
                    sprintf(string_niveau,"%d", niveau);
                    if(FaderLocked[cmptfader+(lfad*24)]==1)
                    {
                        petitpetitchiffrerouge.Print(ol::ToString((int)StateOfFaderBeforeLock[cmptfader +(lfad*24)]),xmf+(cmptfader*larg),ymf+170+(lfad*hmfd));
                    }
                    break;
                default: break;
                }
                if(Fader[cmptfader +(lfad*24)]>0)
                {
                    petitpetitchiffre.Print(string_niveau,xmf+(cmptfader*larg),ymf+160+(lfad*hmfd));
                }

///////////////////////affichage stop pos POS ET BARRE /////////////////////////////
                if(StopPosOn[cmptfader+(lfad*24)]==1)
                {
                    /*sab 02/03/2014 unused var
                    int nivstopos=0;
                    switch(dmx_view)
                    {
                    case 0:
                    nivstopos= (int) (((float)LevelStopPos[cmptfader+(lfad*24)])/2.55);
                    break;
                    case 1:
                    nivstopos=LevelStopPos[cmptfader+(lfad*24)];
                    break;
                    }
                    */

//ON OFF
                    switch(ActionnateStopOn[cmptfader+(lfad*24)])
                    {
                    case 0:
                        Line(Vec2D(xmf+(cmptfader*larg),(ymf+20+127+(lfad*hmfd) - (LevelStopPos[cmptfader+(lfad*24)]/2))),Vec2D(xmf+(cmptfader*larg)+larg-5,(ymf+20+127+(lfad*hmfd) - (LevelStopPos[cmptfader+(lfad*24)]/2)))).Draw(CouleurLigne);
                        petitpetitchiffre.Print(string_fader_stop_pos[cmptfader],xmf+(cmptfader*larg)+2,(ymf+127+20 - (LevelStopPos[cmptfader+(lfad*24)]/2)));
                        break;
                    case 1:
                        Line(Vec2D(xmf+(cmptfader*larg),(ymf+20+127 - (LevelStopPos[cmptfader+(lfad*24)]/2))),Vec2D(xmf+(cmptfader*larg)+larg-5,(ymf+127+20 - (LevelStopPos[cmptfader+(lfad*24)]/2)))).Draw(CouleurBlind);
                        petitpetitchiffrerouge.Print(string_fader_stop_pos[cmptfader],xmf+(cmptfader*larg)+2,(ymf+127+20 - (LevelStopPos[cmptfader+(lfad*24)]/2)));
                        break;
                    default: break;
                    }
                }
///////////SELECTION SOURIS SUR FADERS NUMEROS/////////////////////////////////////////////////////////
                if(  window_focus_id==W_MINIFADERS && mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg && mouse_y>(ymf+(lfad*hmfd))  && mouse_y<(ymf+15+(lfad*hmfd)) )
                {
                    FaderSelB.DrawOutline(CouleurFader);
                    over_minifader=cmptfader +(lfad*24);
                }

//Damper
DB.MoveTo(Vec2D(xmf+(cmptfader*larg),ymf+165+(lfad*hmfd)));
DB.DrawOutline(CouleurLigne.WithAlpha(0.5));
DB.Draw(CouleurBleuProcedure.WithAlpha(fader_damper_is_on[cmptfader +(lfad*24)]));
petitpetitchiffre.Print("~",xmf+(cmptfader*larg)+4,ymf+171+(lfad*hmfd));
if(Midi_Faders_Affectation_Type!=0 && mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg-5 && mouse_y>ymf+165+(lfad*hmfd) && mouse_y<ymf+173+(lfad*hmfd))
{
 DB.DrawOutline(CouleurBlind);
}
//Flash du Fader//////////////////////////////////////////////////////////////////
                FlashTouch.MoveTo(Vec2D(xmf+(cmptfader*larg),ymf+175+(lfad*hmfd)));
                FlashTouch.SetRoundness(3);
                FlashTouch.Draw(CouleurBlind.WithAlpha(0.5));

                if(FaderIsFlash[cmptfader +(lfad*24)]==1)
                {
                    FlashTouch.Draw(CouleurFader);
                }

//flash ou pas
            if( window_focus_id==W_MINIFADERS && mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg-5 && mouse_y>ymf+175+(lfad*hmfd) && mouse_y<ymf+185+(lfad*hmfd))
                {
                    if(mouse_button==1 && FaderIsFlash[cmptfader +(lfad*24)]==0 && mouse_released==0)
                    {
                        FaderIsFlash[cmptfader +(lfad*24)]=1;
                        refresh_minifader_state_view_core(cmptfader +(lfad*24));
                    }
                    if(mouse_released==1)
                    {
                        FaderIsFlash[cmptfader +(lfad*24)]=0;
                    }
                }

////INDICATIONS EN SUP
                petitpetitchiffre.Print(ol::ToString(dock_used_by_fader_is[cmptfader +(lfad*24)]+1),xmf+(cmptfader*larg)+4,ymf+184+(lfad*hmfd));

                Circle DLLoop(Vec2D((xmf+(cmptfader*larg)+12),(ymf+177+(lfad*hmfd))),2);
                DLLoop.Draw(CouleurFader.WithAlpha(is_dock_for_lfo_selected[cmptfader +(lfad*24)][dock_used_by_fader_is[cmptfader +(lfad*24)]]));


//MANIP DU MINI FADER/////////////////////////////////////////////////////////////
                if(  window_focus_id==W_MINIFADERS && mouse_x>xmf+(cmptfader*larg) && mouse_x<xmf+(cmptfader*larg)+larg && mouse_y>(ymf+15+(lfad*hmfd))  && mouse_y<(ymf+147+(lfad*hmfd)) )
                {
///////////////////////////////////////////////////////////////////////////////
//affichage des infos over Fader
                    over_minifader=cmptfader+(lfad*24);
///SI EN MODE AFFECT MIDI

                    if( Midi_Faders_Affectation_Type!=0)
                    {
                        switch(miditable[0][cmptfader+(lfad*24)])
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
                        default: break;
                        }
                        sprintf(string_last_midi_id,"Fader %d is Ch: %d Pitch: %d Typ: %s" , over_minifader+1,miditable[1][ over_minifader],miditable[2][ over_minifader],thetypinfo);

                        FaderLittle.DrawOutline(CouleurBlind);
                    }
//////////////////////////////////////////////////////////////////////////////

                }
            }//fin limitation core_user_define_nb_faders
        }//fin doublage des faders
    }
////////FIN DES 48 POTARDS//////////////////////////////////////////////////////


    return(0);
}
