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

* \file channels_10_visu.cpp
* \brief {GUI file for the dmx channels}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gère les fonction GUI de l'affichage des channels dmx
*
*   GUI fonctions for the dmx channels
*
 **/



int ChannelScroller( int ScrollX, int ScrollY)
{
    Line( Vec2D( ScrollX, ScrollY ), Vec2D( ScrollX,ScrollY+250)).Draw( CouleurLigne );



//sab 02/03/2014 unused var float yvy=0;
    float positiony=0;
//sab 02/03/2014 unused var int nbre_preset=0;


    switch(ClassicalChannelView)
    {
    case 0:
        // YChannels+pos_y_vision-(int)(scroll_channelspace* facteur_scroll_channel_space),i);


        for(int i=0; i<nbre_de_vues_circuits; i++)
        {
            if(Channel_View_MODE[i]==1)
            {
                Line( Vec2D(ScrollX,ScrollY+positiony), Vec2D( ScrollX+5,ScrollY+positiony)).Draw( CouleurLigne );
                minichiffre.Print( channel_view_Name[i],ScrollX+6,(int)(ScrollY+positiony));
                positiony=(ratioview*scroll_pos_preset[i]);

            }

        }

        break;
    case 1:
        Line( Vec2D(ScrollX,ScrollY), Vec2D( ScrollX+10,ScrollY)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "  1 -48" ,ScrollX+25,ScrollY );
        Line( Vec2D(ScrollX,ScrollY+25), Vec2D( ScrollX+10,ScrollY+25)).Draw( CouleurLigne );
        petitpetitchiffre.Print( " 49 -96" ,ScrollX+25,ScrollY+25 );
        Line( Vec2D(ScrollX,ScrollY+50), Vec2D( ScrollX+10,ScrollY+50)).Draw( CouleurLigne );
        petitpetitchiffre.Print( " 97-144" ,ScrollX+25,ScrollY+50 );
        Line( Vec2D(ScrollX,ScrollY+75), Vec2D( ScrollX+10,ScrollY+75)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "145-192" ,ScrollX+25,ScrollY+75 );
        Line( Vec2D(ScrollX,ScrollY+100), Vec2D( ScrollX+10,ScrollY+100)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "193-240" ,ScrollX+25,ScrollY+100 );
        Line( Vec2D(ScrollX,ScrollY+125), Vec2D( ScrollX+10,ScrollY+125)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "241-288" ,ScrollX+25,ScrollY+125 );
        Line( Vec2D(ScrollX,ScrollY+150), Vec2D( ScrollX+10,ScrollY+150)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "289-336" ,ScrollX+25,ScrollY+150 );
        Line( Vec2D(ScrollX,ScrollY+175), Vec2D( ScrollX+10,ScrollY+175)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "337-384" ,ScrollX+25,ScrollY+175 );
        Line( Vec2D(ScrollX,ScrollY+200), Vec2D( ScrollX+10,ScrollY+200)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "385-432" ,ScrollX+25,ScrollY+200 );
        Line( Vec2D(ScrollX,ScrollY+225), Vec2D( ScrollX+10,ScrollY+225)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "433-480" ,ScrollX+25,ScrollY+225 );
        Line( Vec2D(ScrollX,ScrollY+250), Vec2D( ScrollX+10,ScrollY+250)).Draw( CouleurLigne );
        petitpetitchiffre.Print( "  ->512" ,ScrollX+25,ScrollY+250 );
        break;
        default: break;
    }

    Rect Curseur_ScrollChannel(Vec2D(ScrollX-10,ScrollY+scroll_channelspace-10),Vec2D(100,20));
    Curseur_ScrollChannel.SetRoundness(10);
    Curseur_ScrollChannel.SetLineWidth(epaisseur_ligne_fader);
    Curseur_ScrollChannel.DrawOutline(CouleurFader);

    if(Midi_Faders_Affectation_Type!=0  && mouse_x>ScrollX-10 && mouse_x<ScrollX+90 && mouse_y>ScrollY+scroll_channelspace && mouse_y<ScrollY+scroll_channelspace+20)
    {
        Curseur_ScrollChannel.DrawOutline(CouleurBlind);
        show_type_midi(1624,"Channels Handle" );
    }


    refresh_positions_preset_view_poignee();
    return(0);
}

int ClassicalChannelSpace( int xchan, int ychan,  int scroll)//les 512 circuits
{
    int num_circ=0;
    char chan_is[6];
    int xposch=0;
    int ypos_ch=0;
    int ypos_l=0;
//sab 02/03/2014 unused var bool showfrompreset=0;
    int showisup=0;//0 = equal 1= is up 2=is down

    float myalpha_channel=0.0;
    int maxchan_per_ligne=13;


    Rect ChannelRect(Vec2D(xchan,ypos_l),Vec2D(40,65));
    ChannelRect.SetRoundness(10);
    ChannelRect.SetLineWidth(epaisseur_ligne_fader);
    Rect LevelOverdock(Vec2D(xchan,ypos_l),Vec2D(35,13));
    Rect LevelOverTrack(Vec2D(xchan,ypos_l),Vec2D(35,13));
    Rect LevelModified(Vec2D(xchan,ypos_l),Vec2D(20,13));


    for (int l=0; l<43; l++)
    {
        if (l==42)
        {
            maxchan_per_ligne=9;   //derniere ligne à 512
        }

//on affiche et actionne que si les données
//sont dans la fenetre de l espace circuit cad si la ligne et son incréments sont inferieurs au y de l espace fader // AFFICHAGE ONLY SELECTION PLUS BAS
        if
        (
            (index_show_faders==0 && ((((ychan*l)+ 40 - (int)((float)(scroll)* Ch_Scroll_Factor))>0)&&(((ychan*l) + 60 - (int)((float)(scroll)* Ch_Scroll_Factor))<hauteur_ecran)))
            ||
            (index_show_faders==1 && ((((ychan*l)+ 40 - (int)((float)(scroll)* Ch_Scroll_Factor))>0)&&(((ychan*l) + 60 - (int)((float)(scroll)* Ch_Scroll_Factor))<YFader)))
        )
        {
            for (int c=1; c<maxchan_per_ligne; c++)
            {
                num_circ=c+(l*12);
                xposch=45*c;
                ypos_ch= (int)((float)(scroll)* Ch_Scroll_Factor);
                ypos_l=ychan*l;

                if((ypos_l -ypos_ch)>-140 && ypos_l+ 40 -ypos_ch<hauteur_ecran)//condition d'affichage
                {

                    ChannelRect.MoveTo(Vec2D(((xchan-5) + (xposch)),((ypos_l)+ 40 -ypos_ch)));

                    unsigned char circuittoshow=bufferSequenciel[num_circ] ;
                    showisup=0;

                    if  (bufferSequenciel[num_circ] < bufferBlind[num_circ])
                    {
                        showisup=1;
                    }
                    else if  (bufferSequenciel[num_circ] > bufferBlind[num_circ])
                    {
                        showisup=2;
                    }

//affichage valeur % ou dmx + BUFFER SAISIE
                    if(circuittoshow>0) // FORMULE MAGIQUE
                    {
                        myalpha_channel=((float)circuittoshow/255);
                        ChannelRect.Draw(CouleurNiveau.WithAlpha(myalpha_channel/2));
                    }

//NIVEAUX MIS PAR LES  FADERS Buffer general
                    if(bufferFaders[num_circ]>0) // FORMULE MAGIQUE
                    {
                        myalpha_channel=((float)bufferFaders[num_circ]/255);
                        ChannelRect.Draw(CouleurFader.WithAlpha(myalpha_channel/2));
                    }

//BLIND
                    switch(index_blind)//differencec avec mem enregistrée
                    {
                    case 0:
                        if(bufferSaisie[num_circ]!=Memoires[position_onstage][num_circ] && index_blink_change_memories==1)
                        {
                            ChannelRect.Draw(CouleurNiveau.WithAlpha(alpha_blinker));
                        }
                        break;
                    case 1:
//difference avec mem enregistrée
                        if(bufferBlind[num_circ]!=Memoires[position_preset][num_circ]  && index_blink_change_memories==1)
                        {
                            ChannelRect.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                        }
                        break;
                        default: break;
                    }



//Affichage circuits
                    if(c<100)
                    {
                        sprintf(chan_is," %d",num_circ);
                        petitchiffre.Print(chan_is ,(xchan + (xposch)),((ypos_l) + 50 -ypos_ch ),CENTER);
                    }
                    else if(c>=100)
                    {
                        sprintf(chan_is,"%d",num_circ);
                        petitchiffre.Print(chan_is ,((xchan + (xposch))-5),((ypos_l) + 50 - ypos_ch ),CENTER);
                    }


///////////////////////
                    switch(showisup)
                    {
                    case 1:
                        petitpetitchiffre.Print("+", (xchan + 15+(xposch)),((ypos_l) + 70 -ypos_ch),RIGHT );
                        break;
                    case 2:
                        petitpetitchiffre.Print("-", (xchan + 15+(xposch)),((ypos_l) + 70 -ypos_ch),RIGHT );
                        break;
                    default: break;
                    }
///////////////////////

                    if(index_inspekt==1)
                    {
//Affiche du dernier dock survolé
                        if (show_who_is_in_FADER_DOCK[num_circ]==1 )
                        {
                            ChannelRect.DrawOutline(CouleurFader);
//affichage du niveau du dock survolé
                            LevelOverdock.MoveTo(Vec2D(((xchan-5) + (xposch))+15,((ypos_l)+ 92 - ypos_ch)));
                            LevelOverdock.Draw(CouleurFader);
                        }
//affichage du master  qui envoie le plus haut niveau au circuit
                        if(highest_level_comes_from_fader[num_circ]>0)//si le highest level exist : valeur faders de 1 à 48 quand attribué
                        {
                            petitdoomInspekt.Print(ol::ToString(highest_level_comes_from_fader[num_circ]) ,((xchan + (xposch))+15),((ypos_l) + 72 - ypos_ch),CENTER);
                        }
                        if(i_m_over_a_track==1 && over_track_show_channel[num_circ]>0)
                        {
                            ChannelRect.DrawOutline(CouleurGreen);
                            LevelOverTrack.MoveTo(Vec2D(((xchan-5) + (xposch))-15,((ypos_l)+ 92 - ypos_ch)));
                            LevelOverTrack.Draw(CouleurGreen);
                        }
                    }


////////////////////////
                    switch (dmx_view)
                    {
//affichage %
                    case 0:
                        if(circuittoshow>0)
                        {
                            circuitlevel.Print(ol::ToString((int) (((float)(circuittoshow) /2.55))) ,(xchan + (xposch)),((ypos_l) + 80 - ypos_ch),CENTER );
                        }
//
                        if(bufferFaders[num_circ]>0)
                        {
                            circuitfaderlevel.Print(ol::ToString((int) (((float)(bufferFaders[num_circ]) /2.55))) ,(xchan + (xposch)),((ypos_l) + 90 - ypos_ch),CENTER );
                        }
//blind
                        if( index_blind==1 && bufferBlind[num_circ]>0)
                        {
                            circuitblindlevel.Print(ol::ToString((int) (((float)(bufferBlind[num_circ]) /2.55))) ,(xchan + (xposch)),((ypos_l) + 100 - ypos_ch),CENTER );
                        }
//affichage niveau inspekt fader
                        if(index_inspekt==1 && show_who_is_in_FADER_DOCK[num_circ]==1)
                        {
                            petitpetitchiffre.Print(ol::ToString((int)(((float)(FaderDockContains[over_fader][over_dock][num_circ]) /2.55))) ,(xchan + (xposch))+15,((ypos_l) + 100 -ypos_ch),CENTER );
                        }
//inspekt track
                        if(index_inspekt==1 && i_m_over_a_track==1 && over_track_show_channel[num_circ]>0)
                        {
                            petitpetitchiffre.Print(ol::ToString((int)(float(over_track_show_channel[num_circ]) /2.55)) ,(xchan + (xposch))-15,((ypos_l) + 100 -ypos_ch),CENTER );
                        }


//freeze
                        if(freeze_array[num_circ]==1)
                        {
                            ChannelRect.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                            petitchiffre.Print(ol::ToString((int) (((float)(freeze_state[num_circ]) /2.55))) ,(xchan + (xposch))+10,((ypos_l) + 70 - ypos_ch),CENTER );
                        }


                        break;

//affichage 255
                    case 1:
                        if(circuittoshow>0)
                        {
                            circuitlevel.Print(ol::ToString((int)circuittoshow) ,(xchan + (xposch)),((ypos_l) + 80 - ypos_ch),CENTER );
                        }
                        if(bufferFaders[num_circ]>0)
                        {
                            circuitfaderlevel.Print(ol::ToString((int)(bufferFaders[num_circ])) ,(xchan + (xposch)),((ypos_l) + 90 - ypos_ch),CENTER );
                        }
//blind
                        if(index_blind==1 && bufferBlind[num_circ]>0 )
                        {
                            circuitblindlevel.Print(ol::ToString((int)(bufferBlind[num_circ])) ,(xchan + (xposch)),((ypos_l) + 100 - ypos_ch),CENTER );
                        }
//affichage niveau inspekt fader
                        if(index_inspekt==1 && show_who_is_in_FADER_DOCK[num_circ]==1)
                        {
                            petitpetitchiffre.Print(ol::ToString((int)(FaderDockContains[over_fader][over_dock][num_circ])) ,(xchan + (xposch))+15,((ypos_l) + 100 -ypos_ch),CENTER );
                        }
//inspekt track
                        if(index_inspekt==1 && i_m_over_a_track==1)
                        {
                            petitpetitchiffre.Print(ol::ToString(over_track_show_channel[num_circ]) ,(xchan + (xposch))-15,((ypos_l) + 100 -ypos_ch),CENTER );
                        }


//freeze
                        if(freeze_array[num_circ]==1)
                        {
                            ChannelRect.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                            petitchiffre.Print(ol::ToString((int)(freeze_state[num_circ])) ,(xchan + (xposch))+10,((ypos_l) + 70 - ypos_ch),CENTER );
                        }
                        break;
                        default: break;
                    }

                    if(num_circ==go_channel_is && index_go==1 && index_pause==0)
                    {
                        ChannelRect.Draw(CouleurGreen.WithAlpha(alpha_blinker));
                        minidoomblanc.Print("GO",(xchan + (xposch)),((ypos_l) + 80 - ypos_ch),CENTER );
                    }

                    if(num_circ==pause_channel_is && index_go==1 && index_pause==1)
                    {
                        ChannelRect.Draw(CouleurYellow.WithAlpha(alpha_blinker));
                        minidoomblanc.Print("PAUSE",(xchan + (xposch))-10,((ypos_l) + 80 - ypos_ch),CENTER );
                    }

//exclude from GM action
                    if(Channels_excluded_from_grand_master[num_circ]==1)
                    {
                        Circle CircleExcluded(xchan + xposch+26,ypos_l + 52 - ypos_ch, 3);
                        CircleExcluded.DrawOutline(CouleurBlind);
                    }

                    if(channel_is_touched_by_fader_fx[num_circ]==1)
                    {
                        Circle CircleTouchedbyFx(xchan + xposch+26,ypos_l + 61 - ypos_ch , 3);
                        switch(channel_is_touched_by_fader_type_fx[num_circ])
                        {
                        case 0://normal HTP
                            CircleTouchedbyFx.Draw(CouleurFader);
                            break;
                        case 1://off
                            CircleTouchedbyFx.Draw(CouleurFond);
                            break;
                        case 2://minus
                            CircleTouchedbyFx.Draw(CouleurRougePur);
                            break;
                        case 3://add
                            CircleTouchedbyFx.Draw(CouleurLigne);
                            break;
                        case 4://screen
                            CircleTouchedbyFx.Draw(CouleurLevel);
                            break;
                        case 5://exclusion
                            CircleTouchedbyFx.Draw(CouleurBleuProcedure);
                            break;
                        default:
                            break;
                        }
                        minichiffre.Print(ol::ToString(channel_is_touched_by_fader_number[num_circ]+1),xchan + xposch+30,ypos_l + 60 - ypos_ch );
                        CircleTouchedbyFx.DrawOutline(CouleurLigne);
                    }

//Affiche Selected
                    if (Selected_Channel[num_circ]==1)
                    {
                        ChannelRect.DrawOutline(CouleurLigne);
                    }

//etiquette niveau correction
                    if(channel_level_mofification_while_crossfade[num_circ]!=0)
                    {
                        LevelModified.MoveTo(Vec2D(xchan+xposch+20,((ypos_l)+ 70 - ypos_ch)));
                        LevelModified.Draw(CouleurBlind);
                        switch (dmx_view)
                        {
//affichage %
                        case 0:
                            petitpetitchiffre.Print(ol::ToString((int) (((float)(channel_level_mofification_while_crossfade[num_circ]) /2.55))),(xchan + xposch+25),((ypos_l) + 80 - ypos_ch),RIGHT );
                            break;
                        case 1:
                            petitpetitchiffre.Print(ol::ToString(channel_level_mofification_while_crossfade[num_circ]),(xchan + xposch+25),((ypos_l) + 80 - ypos_ch),RIGHT );
                            break;
                        default: break;
                        }
                    }


//premier dimmer patché
                    if(index_show_first_dim==1)
                    {
                        for(int llo=0; llo<4; llo++)
                        {
                            if(show_first_dim_array[num_circ][llo]!=0)
                            {
                                petitdoomrouge.Print(ol::ToString(show_first_dim_array[num_circ][llo]),(xchan + xposch +5),((ypos_l) + 75 - ypos_ch+(llo*10)));
                            }
                        }
                        if(show_more_than_one_dim[num_circ]==1)
                        {
                            petitdoomrouge.Print("+",(xchan + xposch +20),((ypos_l) + 60 - ypos_ch+2));
                        }
                    }

                }//fin condition d'affichage

            }
        }
    }
    return(0);
}



int Draw_Channel_Preset_Title(int xchan, int ychan, int prst_v)
{

    Rect Background_title(Vec2D(xchan+40,ychan),Vec2D(210,20));
    Background_title.SetRoundness(5);
    Background_title.Draw(CouleurLigne.WithAlpha(0.05));

    neuromoyen.Print( ol::ToString(prst_v+1), xchan+25,ychan+15);
    petitpetitchiffre.Print(ol::ToString(channel_number_in_View[prst_v]),xchan+35,ychan+5);
    neuromoyen.Print( channel_view_Name[prst_v], xchan+45,ychan+15);
    Line(Vec2D(xchan,ychan+25),Vec2D(xchan+600,ychan+25)).Draw(CouleurLigne);


    Rect Build(Vec2D(xchan+520,ychan),Vec2D(55,20));
    Build.SetRoundness(3);

    if(prst_v!=0)//pas la vue patchée
    {
        Rect M(Vec2D(xchan+435,ychan),Vec2D(20,20));
        M.SetRoundness(3);
        Rect F(Vec2D(xchan+460,ychan),Vec2D(20,20));
        F.SetRoundness(3);

        if(channel_view_mode_builder[prst_v]==1 && channel_view_type_of_behaviour[prst_v]==0)
        {
            M.Draw(CouleurBlind);
            F.Draw(CouleurFader);
        }

        switch(channel_view_type_of_behaviour[prst_v])
        {
        case 1:
            M.Draw(CouleurBlind);
            break;
        case 2:
            F.Draw(CouleurFader);
            break;
        default:
            break;
        }

        M.DrawOutline(CouleurLigne.WithAlpha(0.5));
        petitpetitchiffregris.Print("M",xchan+440,ychan+13);


        F.DrawOutline(CouleurLigne.WithAlpha(0.5));
        petitpetitchiffregris.Print("F",xchan+467,ychan+13);


        Rect All(Vec2D(xchan+485,ychan),Vec2D(30,20));
        All.SetRoundness(3);
        All.Draw(CouleurBlind.WithAlpha( channel_view_mode_builder[prst_v]));
        All.DrawOutline(CouleurLigne.WithAlpha(0.5));
        petitpetitchiffregris.Print("ALL",xchan+490,ychan+13);



        Build.DrawOutline(CouleurLigne.WithAlpha(0.5));
        petitpetitchiffregris.Print("Build View",xchan+524,ychan+13);

    }


    if(window_focus_id==0 )
    {
        if(mouse_y>ychan && mouse_y<ychan+20  )
        {
//TITRE VIEW
            if(mouse_x> xchan+40 && mouse_x<xchan+250)
            {
                Background_title.DrawOutline(CouleurLigne);
            }

//do build
            else if(mouse_x>  xchan+520 && mouse_x<xchan+575 && prst_v!=0 )
            {
                Build.DrawOutline(CouleurFader.WithAlpha(0.5));
                //logique a garder inside sinon ca plante grave !
                if(mouse_button==1 && mouse_released==0)
                {
                    channel_view_is=prst_v;
                    if(index_do_dock==1)
                    {
                        if(channel_view_type_of_behaviour[channel_view_is]==0 &&  channel_view_mode_builder[channel_view_is]==0)
                        {
                            index_ask_record_selection_of_view=1 ;
                            index_ask_confirm=1;
                            mouse_released=1;
                        }
                        else
                        {
                            index_ask_build_view=1;
                            index_ask_confirm=1;
                            mouse_released=1;
                        }
                    }

                    else if(index_do_modify==1)
                    {
                        index_ask_modify_selection_of_view=1 ;
                        index_ask_confirm=1;
                        mouse_released=1;
                    }
                    else if(index_do_report==1)
                    {
                        index_ask_report_selection_of_view=1;
                        index_ask_confirm=1;
                        mouse_released=1;
                    }
                    else if(index_main_clear==1)
                    {
                        index_ask_clear_selection_of_view=1;
                        index_ask_confirm=1;
                        mouse_released=1;
                    }
                }
            }

        }
    }

    return(0);
}


int Draw_Channel_Preset_View(int xchan, int ychan,  int prst_v)
{


    int num_circ=0;
    char chan_is[6];
    int xposch=0;
    int ypos_ch=0;
//sab 02/03/2014 unused var int ypos_l=0;
//sab 02/03/2014 unused var bool showfrompreset=0;
    int showisup=0;//0 = equal 1= is up 2=is down

    float myalpha_channel=0.0;
    int maxchan_per_ligne=12;
    int nbre_lignes=channel_number_of_lines[prst_v];



    Rect ChannelRect(Vec2D(xchan, ypos_ch),Vec2D(40,65));
    ChannelRect.SetRoundness(10);
    ChannelRect.SetLineWidth(epaisseur_ligne_fader);
    Rect LevelOverdock(Vec2D(xchan, ypos_ch),Vec2D(35,13));
    Rect LevelOverTrack(Vec2D(xchan,ypos_ch),Vec2D(35,13));
    Rect LevelModified(Vec2D(xchan,ypos_ch),Vec2D(20,13));


//neuromoyen.Print(ol::ToString( nbre_lignes) ,xchan+400,ychan-40);
    for (int l=0; l<=nbre_lignes; l++)
    {
        if (l==nbre_lignes)
        {
            maxchan_per_ligne=channel_number_in_View[prst_v]%12;
        }

        for (int c=1; c<=maxchan_per_ligne; c++)
        {

            num_circ=Channel_View_ROUTING[prst_v][c+(l*12)-1];

            if(num_circ!=0 && num_circ<513)
            {

                xposch=45*c;
                ypos_ch=ychan+(l*(70));

                if(ypos_ch>-30 && ypos_ch<hauteur_ecran)//condition affichage
                {

                    ChannelRect.MoveTo(Vec2D(((xchan-5) + (xposch)), ypos_ch));

                    unsigned char circuittoshow=bufferSequenciel[num_circ] ;
                    showisup=0;

                    if  (bufferSequenciel[num_circ] < bufferBlind[num_circ])
                    {
                        showisup=1;
                    }
                    else if  (bufferSequenciel[num_circ] > bufferBlind[num_circ])
                    {
                        showisup=2;
                    }

//affichage valeur % ou dmx + BUFFER SAISIE
                    if(circuittoshow>0) // FORMULE MAGIQUE
                    {
                        myalpha_channel=((float)circuittoshow/255);
                        ChannelRect.Draw(CouleurNiveau.WithAlpha(myalpha_channel/2));
                    }

//NIVEAUX MIS PAR LES  FADERS Buffer general
                    if(bufferFaders[num_circ]>0) // FORMULE MAGIQUE
                    {
                        myalpha_channel=((float)bufferFaders[num_circ]/255);
                        ChannelRect.Draw(CouleurFader.WithAlpha(myalpha_channel/2));
                    }

//BLIND
                    switch(index_blind)//differencec avec mem enregistrée
                    {
                    case 0:
                        if(bufferSaisie[num_circ]!=Memoires[position_onstage][num_circ] && index_blink_change_memories==1)
                        {
                            ChannelRect.Draw(CouleurNiveau.WithAlpha(alpha_blinker));
                        }
                        break;
                    case 1:
//difference avec mem enregistrée
                        if(bufferBlind[num_circ]!=Memoires[position_preset][num_circ]  && index_blink_change_memories==1)
                        {
                            ChannelRect.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                        }
                        break;
                    default: break;
                    }



//Affichage circuits
                    if(c<100)
                    {
                        sprintf(chan_is," %d",num_circ);
                        petitchiffre.Print(chan_is ,(xchan + (xposch)),ypos_ch +10,CENTER);
                    }
                    else if(c>=100)
                    {
                        sprintf(chan_is,"%d",num_circ);
                        petitchiffre.Print(chan_is ,((xchan + (xposch))-5),ypos_ch +10,CENTER);
                    }


///////////////////////
                    switch(showisup)
                    {
                    case 1:
                        petitpetitchiffre.Print("+", (xchan + 15+(xposch)),ypos_ch+30,RIGHT );
                        break;
                    case 2:
                        petitpetitchiffre.Print("-", (xchan + 15+(xposch)),ypos_ch+30,RIGHT );
                        break;
                    default: break;
                    }
///////////////////////

                    if(index_inspekt==1)
                    {
//Affiche du dernier dock survolé
                        if (show_who_is_in_FADER_DOCK[num_circ]==1 )
                        {
                            ChannelRect.DrawOutline(CouleurFader);
//affichage du niveau du dock survolé
                            LevelOverdock.MoveTo(Vec2D(((xchan-5) + (xposch))+15, ypos_ch+52));
                            LevelOverdock.Draw(CouleurFader);
                        }
//affichage du master  qui envoie le plus haut niveau au circuit
                        if(highest_level_comes_from_fader[num_circ]>0)//si le highest level exist : valeur faders de 1 à 48 quand attribué
                        {
                            petitdoomInspekt.Print(ol::ToString(highest_level_comes_from_fader[num_circ]) ,((xchan + (xposch))+15),ypos_ch+32,CENTER);
                        }
                        if(i_m_over_a_track==1 && over_track_show_channel[num_circ]>0)
                        {
                            ChannelRect.DrawOutline(CouleurGreen);
                            LevelOverTrack.MoveTo(Vec2D(((xchan-5) + (xposch))-15,ypos_ch+52));
                            LevelOverTrack.Draw(CouleurGreen);
                        }
                    }


////////////////////////
                    switch (dmx_view)
                    {
//affichage %
                    case 0:
                        if(circuittoshow>0)
                        {
                            circuitlevel.Print(ol::ToString((int) (((float)(circuittoshow) /2.55))) ,(xchan + (xposch)), ypos_ch+40,CENTER );
                        }
//
                        if(bufferFaders[num_circ]>0)
                        {
                            circuitfaderlevel.Print(ol::ToString((int) (((float)(bufferFaders[num_circ]) /2.55))) ,(xchan + (xposch)),ypos_ch+50,CENTER );
                        }
//blind
                        if( index_blind==1 && bufferBlind[num_circ]>0)
                        {
                            circuitblindlevel.Print(ol::ToString((int) (((float)(bufferBlind[num_circ]) /2.55))) ,(xchan + (xposch)),ypos_ch+60,CENTER );
                        }
//affichage niveau inspekt fader
                        if(index_inspekt==1 && show_who_is_in_FADER_DOCK[num_circ]==1)
                        {
                            petitpetitchiffre.Print(ol::ToString((int)(((float)(FaderDockContains[over_fader][over_dock][num_circ]) /2.55))) ,(xchan + (xposch))+15,ypos_ch+60,CENTER );
                        }
//inspekt track
                        if(index_inspekt==1 && i_m_over_a_track==1 && over_track_show_channel[num_circ]>0)
                        {
                            petitpetitchiffre.Print(ol::ToString((int)(float(over_track_show_channel[num_circ]) /2.55)) ,(xchan + (xposch))-15,ypos_ch+60,CENTER );
                        }


//freeze
                        if(freeze_array[num_circ]==1)
                        {
                            ChannelRect.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                            petitchiffre.Print(ol::ToString((int) (((float)(freeze_state[num_circ]) /2.55))) ,(xchan + (xposch))+10, ypos_ch+30,CENTER );
                        }

                        break;

//affichage 255
                    case 1:
                        if(circuittoshow>0)
                        {
                            circuitlevel.Print(ol::ToString((int)circuittoshow) ,(xchan + (xposch)),ypos_ch+40,CENTER );
                        }
                        if(bufferFaders[num_circ]>0)
                        {
                            circuitfaderlevel.Print(ol::ToString((int)(bufferFaders[num_circ])) ,(xchan + (xposch)),ypos_ch+50,CENTER );
                        }
//blind
                        if(index_blind==1 && bufferBlind[num_circ]>0 )
                        {
                            circuitblindlevel.Print(ol::ToString((int)(bufferBlind[num_circ])) ,(xchan + (xposch)), ypos_ch+60,CENTER );
                        }
//affichage niveau inspekt fader
                        if(index_inspekt==1 && show_who_is_in_FADER_DOCK[num_circ]==1)
                        {
                            petitpetitchiffre.Print(ol::ToString((int)(FaderDockContains[over_fader][over_dock][num_circ])) ,(xchan + (xposch))+15,ypos_ch+60,CENTER );
                        }
//inspekt track
                        if(index_inspekt==1 && i_m_over_a_track==1)
                        {
                            petitpetitchiffre.Print(ol::ToString(over_track_show_channel[num_circ]) ,(xchan + (xposch))-15,ypos_ch+60,CENTER );
                        }


//freeze
                        if(freeze_array[num_circ]==1)
                        {
                            ChannelRect.Draw(CouleurBlind.WithAlpha(alpha_blinker));
                            petitchiffre.Print(ol::ToString((int)(freeze_state[num_circ])) ,(xchan + (xposch))+10,ypos_ch+30,CENTER );
                        }
                        break;
                        default: break;
                    }

                    if(num_circ==go_channel_is && index_go==1 && index_pause==0)
                    {
                        ChannelRect.Draw(CouleurGreen.WithAlpha(alpha_blinker));
                        minidoomblanc.Print("GO",(xchan + (xposch)),ypos_ch+40,CENTER );
                    }

                    if(num_circ==pause_channel_is && index_go==1 && index_pause==1)
                    {
                        ChannelRect.Draw(CouleurYellow.WithAlpha(alpha_blinker));
                        minidoomblanc.Print("PAUSE",(xchan + (xposch))-10,ypos_ch+40,CENTER );
                    }

//exclude from GM action
                    if(Channels_excluded_from_grand_master[num_circ]==1)
                    {
                        Circle CircleExcluded(xchan + xposch+26, ypos_ch +11, 3);
                        CircleExcluded.DrawOutline(CouleurBlind);
                    }

                    if(channel_is_touched_by_fader_fx[num_circ]==1)
                    {
                        Circle CircleTouchedbyFx(xchan + xposch+26, ypos_ch +20, 3);
                        switch(channel_is_touched_by_fader_type_fx[num_circ])
                        {
                        case 0://normal HTP
                            CircleTouchedbyFx.Draw(CouleurFader);
                            break;
                        case 1://off
                            CircleTouchedbyFx.Draw(CouleurFond);
                            break;
                        case 2://minus
                            CircleTouchedbyFx.Draw(CouleurRougePur);
                            break;
                        case 3://add
                            CircleTouchedbyFx.Draw(CouleurLigne);
                            break;
                        case 4://screen
                            CircleTouchedbyFx.Draw(CouleurLevel);
                            break;
                        case 5://exclusion
                            CircleTouchedbyFx.Draw(CouleurBleuProcedure);
                            break;
                        default:
                            break;
                        }
                        minichiffre.Print(ol::ToString(channel_is_touched_by_fader_number[num_circ]+1),xchan + xposch+30,ypos_ch+20 );
                        CircleTouchedbyFx.DrawOutline(CouleurLigne);
                    }

//Affiche Selected
                    if (Selected_Channel[num_circ]==1)
                    {
                        ChannelRect.DrawOutline(CouleurLigne);
                    }


//etiquette niveau correction
                    if(channel_level_mofification_while_crossfade[num_circ]!=0)
                    {
                        LevelModified.MoveTo(Vec2D(xchan+xposch+20,ypos_ch+30));
                        LevelModified.Draw(CouleurBlind);
                        switch (dmx_view)
                        {
//affichage %
                        case 0:
                            petitpetitchiffre.Print(ol::ToString((int) (((float)(channel_level_mofification_while_crossfade[num_circ]) /2.55))),(xchan + xposch+25),ypos_ch+40,RIGHT );
                            break;
                        case 1:
                            petitpetitchiffre.Print(ol::ToString(channel_level_mofification_while_crossfade[num_circ]),(xchan + xposch+25),ypos_ch+40,RIGHT );
                            break;
                        default: break;
                        }
                    }

//premier dimmer patché
                    if(index_show_first_dim==1)
                    {
                        for(int llo=0; llo<4; llo++)
                        {
                            if(show_first_dim_array[num_circ][llo]!=0)
                            {
                                petitdoomrouge.Print(ol::ToString(show_first_dim_array[num_circ][llo]),(xchan + xposch +5), ypos_ch+35+(llo*10));
                            }
                        }
                        if(show_more_than_one_dim[num_circ]==1)
                        {
                            petitdoomrouge.Print("+",(xchan + xposch +20), ypos_ch+23);
                        }
                    }

                }//fin condition affichage

            }
        }
    }


    return(0);
}

int ChannelsMenuSelection(int chx, int chy)
{
    Rect Barre(Vec2D(chx,chy),Vec2D(largeur_ChannelMenu,hauteur_ChannelMenu));
    Barre.Draw(CouleurFond);
    neuromoyen.Print("Ch.View:",chx,chy+13);
    Rect Classical(Vec2D(chx+70,chy+1),Vec2D(60,18));
    Classical.SetRoundness(5.0);
    Classical.Draw(CouleurFader.WithAlpha(ClassicalChannelView));
    Classical.DrawOutline(CouleurLigne.WithAlpha(0.4));
    petitchiffre.Print("Classical", chx+75,chy+14);

    if(window_focus_id==0 && Midi_Faders_Affectation_Type!=0 && mouse_x>chx+70 && mouse_x<chx+130 && mouse_y>chy+1 && mouse_y<chy+19)
    {
        Classical.DrawOutline(CouleurBlind);
        show_type_midi(1644,"Classical Channel View");
    }


    Rect ChooseChannelView(Vec2D(chx+80,chy+5),Vec2D(10,10));
    char tmp_hain[24];
    for(int lv=0; lv<2; lv++)
    {
        for(int i=0; i<8; i++)
        {
            ChooseChannelView.MoveTo(Vec2D(chx+140+(i*15),chy+1+(15*lv)));
            ChooseChannelView.Draw(CouleurNiveau.WithAlpha(Channel_View_MODE[i+(lv*8)]));
            ChooseChannelView.DrawOutline(CouleurLigne.WithAlpha(0.4));
            minichiffre.Print(ol::ToString(i+(lv*8)+1),chx+142+(i*15),chy+(15*lv)+8);
            if(window_focus_id==0 && Midi_Faders_Affectation_Type!=0 && mouse_x>chx+140+(i*15) && mouse_x<chx+150+(i*15) && mouse_y>chy+1+(15*lv) && mouse_y<chy+11+(15*lv))
            {
                ChooseChannelView.DrawOutline(CouleurBlind);
                sprintf(tmp_hain,"Channel View %d",i+(lv*8)+1);
                show_type_midi(1628+(i+(lv*8)),tmp_hain);
            }
        }
    }


    command_button_view(chx+270,chy+1,index_blind,"BLIND","Shift-F10",754);// int x, inty ,bool state, char *textedesc, int midiaffectation
    switch(multiple_direct_chan)
    {
    case 0:
        command_button_view(chx+340,chy+1,index_direct_chan,"Direct CH.","",1333);
        break;
    case 1:
        command_button_view(chx+340,chy+1,index_direct_chan,"Direct x12","",1333);
        break;
    default: break;
    }

    command_button_view(chx+410,chy+1,index_inspekt,"View","",1334);// int x, inty ,bool state, char *textedesc, int midiaffectation
    command_button_view(chx+480,chy+1,index_do_hipass,"HiPass","",1542);// int x, inty ,bool state, char *textedesc, int midiaffectation
    command_button_view(chx+550,chy+1,index_do_fgroup,"FGroup","",1592);// int x, inty ,bool state, char *textedesc, int midiaffectation

    switch(Midi_Faders_Affectation_Type)
    {
    case 0:
        command_button_view(chx+620,chy+1,Midi_Faders_Affectation_Type,"MidiAffect","",1625);// int x, inty ,bool state, char *textedesc, int midiaffectation
        break;
    case 1:
        command_button_view(chx+620,chy+1,Midi_Faders_Affectation_Type,"MidiAff.X1","",1625);// int x, inty ,bool state, char *textedesc, int midiaffectation
        break;
    case 2:
        command_button_view(chx+620,chy+1,Midi_Faders_Affectation_Type,"MidiAff.X8","",1625);// int x, inty ,bool state, char *textedesc, int midiaffectation
        if(toggle_numerical_midi_way==0)
        {
        minidoomblanc.Print("P",chx+670,chy+25);
         }
        else
        {
        minidoomblanc.Print("CH",chx+670,chy+25);
        }
        break;
    default:
        break;
    }
    command_button_view(chx+690,chy+1,index_midi_mute,"MidiMute","",1277);// int x, inty ,bool state, char *textedesc, int midiaffectation
    command_button_view(chx+760,chy+1,index_global_midi_send_on_faders,"M.Out Fad.","",1593);// int x, inty ,bool state, char *textedesc, int midiaffectation

    command_button_view(chx+830,chy+1,index_do_dock,"STORE","F1",743);// int x, inty ,bool state, char *textedesc, int midiaffectation
    command_button_view(chx+900,chy+1,index_do_modify,"MODIFY","F2",744);
    command_button_view(chx+970,chy+1,index_do_report,"REPORT","F3",745);
    command_button_view(chx+1040,chy+1,index_main_clear,"CLEAR","F4",746);
    command_button_view(chx+1110,chy+1,index_show_main_menu,"MENUS","RIGHT CLICK",1634);

//ligne fin du menu
    Line(Vec2D(chx,chy+hauteur_ChannelMenu),Vec2D(chx+largeur_ChannelMenu,chy+hauteur_ChannelMenu)).Draw(CouleurLigne);

    return(0);
}
