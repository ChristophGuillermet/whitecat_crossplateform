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

* \file grand_master.cpp
* \brief {draw the grand master}
* \author Christoph Guillermet
* \version {0.8.6}
* \date {28/04/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions de dessin du grand master
*
*   GUI fonctions for grand master
*
 **/
void do_logical_grand_master_wheel(const int& GMX, const int& GMY, const int& larg)
{
			//à faire : liseré jaune : mousePtr.SetLook(whc_pointer::arrow_wheel);
//sab 28/11/2014 deb
        if((window_focus_id==0 || window_focus_id==906) && index_allow_grand_master==1
		&& mousePtr.isOverRecSize(GMX, GMY, larg, 255))

        {
            if (key[KEY_ALT] && key[KEY_LCONTROL])
            {
                whc_mouseWheel::c_levelSpeedupIncrease(whc_mouseWheel::scroll, niveauGMaster, 255, 0, 1000);
            }
            else if (key[KEY_ALT] )
			{
				whc_mouseWheel::c_levelIncrease(whc_mouseWheel::scroll, niveauGMaster, 255, 0);
				mouseScroll.SetProcessed();
			}
        }
//sab 28/11/2014 fin
}

int do_logical_grand_master(const int& GMX, const int& GMY, const int& larg)
{

//sab 13/12/2014 deb
        if((window_focus_id==0 || window_focus_id==906) && index_allow_grand_master==1
		&& mousePtr.isOverRecSize(GMX, GMY, larg, 255)
		&& mouseClicLeft.isDownToBeProcessed()
		&& key[KEY_ALT] )
		{
			if (not mouseScroll.unsubscribe(niveauGMaster))
			{
				mouseScroll.addSubscriber(niveauGMaster, whc_mouseWheel::slider, 0, 255, whc_mouseWheel::nokey);
			}
			mouseClicLeft.SetProcessed();
		}
		else
//sab 13/12/2014 fin

    if(mouse_x>GMX && mouse_x<GMX+larg && mouse_y>=GMY-5 && mouse_y<=GMY+255)
    {
        if((window_focus_id==0 || window_focus_id==906 )&& mouseClicLeft.isDown() && index_allow_grand_master==1)
        {
            set_mouse_range(GMX, GMY, GMX+larg, GMY+255);//pour pas deborder
//NIVEAU
            niveauGMaster=((GMY+255)-mouse_y);
            if(niveauGMaster>255)
            {
                niveauGMaster=255;
            }
            if(niveauGMaster<0)
            {
                niveauGMaster=0;
            }
            midi_levels[615]=(niveauGMaster/2);
            if(midi_send_out[615]==1)
            {
                index_send_midi_out[615]=1;
            }

//CONFIG MIDI
            if(Midi_Faders_Affectation_Type!=0)//config midi
            {
                attribute_midi_solo_affectation(615,Midi_Faders_Affectation_Mode);

//midi report
                switch(miditable[0][615])
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
                }
                sprintf(string_last_midi_id,"MIDI GRAND MASTER:Ch: %d Pitch: %d Type: %s", miditable[1][615],miditable[2][615],thetypinfo);

                mouseClicLeft.SetProcessed();
            }
        }
    }

//midi out on off
    if(mouse_x>GMX+larg+30-10 && mouse_x<GMX+larg+30+10 && mouse_y>GMY+250-10 && mouse_y<GMY+250+10)
    {
        if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            if(midi_send_out[615]==0)
            {
                midi_send_out[615]=1;
            }
            else if(midi_send_out[615]==1)
            {
                midi_send_out[615]=0;
            }
            mouseClicLeft.SetProcessed();
        }
    }

//raccrochage midi
    raccrochage_midi_logical_vertical_dmx(GMX,GMY,615,larg,255);


    return(0);
}





int grand_master(int GMX, int GMY)
{
//DESSIN Master
    Rect Gma( Vec2D(GMX,GMY), Vec2D(40,255) );//box du fader
    Gma.SetRoundness(15);
    Gma.SetLineWidth(epaisseur_ligne_fader);
    Rect GmaNiv( Vec2D(GMX,((GMY+255)-niveauGMaster)), Vec2D (40,niveauGMaster+2));//niveau fader
    GmaNiv.SetRoundness(15);
    switch(dmx_view)
    {
    case 0:
        sprintf(string_niveauGMaster, "%d",(int)(((float)niveauGMaster)/2.55));
        break;
    case 1:
        sprintf(string_niveauGMaster,"%d", niveauGMaster);
        break;
    }
    GmaNiv.Draw(CouleurBlind);
    //sab 13/12/2014 deb
//    Gma.DrawOutline(CouleurLigne);
	ol::Rgba colorToApply = CouleurLigne ;
	if (mouseScroll.isSubscriber(niveauGMaster))
	{
		colorToApply = CouleurYellow ;
	}
	Gma.DrawOutline(colorToApply);
    //sab 13/12/2014 fin
    neuro.Print(string_niveauGMaster,GMX, GMY-5); //niveau du fader
//bouton midi out

//midi out enclenché ou pas du Grand Master
    Circle BMMidiOut( (GMX+70),(GMY+250), 10);//box du fader
    BMMidiOut.SetLineWidth(epaisseur_ligne_fader);
    if(midi_send_out[615]==1)
    {
        BMMidiOut.Draw(CouleurBlind);
    }
    BMMidiOut.DrawOutline(CouleurLigne);
    Line (Vec2D( GMX+40,GMY+240),Vec2D( GMX+55,GMY+240)).Draw(CouleurLigne);
    Line (Vec2D( GMX+55,GMY+240),Vec2D( GMX+65,GMY+245)).Draw(CouleurLigne);
//////////////////////////////////////

    neuromoyen.Print("Grand Master",GMX-25, GMY+280);
    if(mouse_x>GMX && mouse_x<GMX+40 && mouse_y>=GMY-5 && mouse_y<=GMY+255 && Midi_Faders_Affectation_Type!=0)
    {
//affichage rouge config mùidi
        Gma.DrawOutline(CouleurBlind);
    }

//raccrochage midi
    raccrochage_midi_visuel_vertical_dmx (GMX, GMY, 615,40,255);
    return(0);
}
