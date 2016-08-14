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

* \file wrkspc_dir.cpp
* \brief {exemple to create a new module window}
* \author Christoph Guillermet
* \version {0.8.5.2}
* \date {19/02/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Exemple pour créer sa propre fenêtre dans whitecat afin d'ajouter un nouveau module
*
*   Exemple to create a new module window
*
**/


#ifndef WRKSPC_DIR_CLASS_INCLUDED
#define WRKSPC_DIR_CLASS_INCLUDED

#include <wrkspc_dir.h>//ressources juste après whitecat.h

////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTEUR//////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/** \brief Constructor (C writting middewhile)
 *
 * \param none, but should once class "white cat window" defined and class wrkspc_dir inherit from it
 * \return void
 *
 */
void wrkspc_dir ()
{
//données membre liées à future classe whitecat_windows
//constante    wrkspc_dir_window_ID = 928;
    //wrkspc_dir_window_nbrID ; 	//à terme fait doublon avec ID
    //à court terme servira en phase transitoire comme max indice tableaurelatif aux écrans

    wrkspc_dir_window_isListening=false; //pour vos fenetres vous créerez un autre index_booléen
    wrkspc_dir_window_isVisible=false; //pour vos fenetres vous créerez un autre index_booléen

    wrkspc_dir_window_pos_x=400;//pixels
    wrkspc_dir_window_pos_y=400;
    wrkspc_dir_window_width=400;//pixels
    wrkspc_dir_window_height=250;

    strcpy(wrkspc_dir_window_title,"Directory Browser");
	wrkspc_dir_window_title_x =80;
	wrkspc_dir_window_title_y =25;
	wrkspc_dir_window_moveCloseButtons_x =16;
	wrkspc_dir_window_moveCloseButtons_y =16;

    if (wrkspc_dir_window_ID > max_window_identity_is)
    {
        max_window_identity_is = wrkspc_dir_window_ID;
    }
}

////////////////////////////////////////////////////////////////////////////////
//LA LOGIQUE////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/** \brief Says if Mouse is over the window
 * - if true Fire wrkspc_dir_window_mouseIsOver(int mx, int my);
 *
 * \param mouse x position
 * \param mouse y position
 * \return bool
 *
 */
bool wrkspc_dir_window_isMouseOver(int mx, int my)
{
    if (wrkspc_dir_window_isVisible==false)
    {
        wrkspc_dir_window_isFlyOver=false; //just in case
        return wrkspc_dir_window_isVisible ; //can't be flying over the window if not shown
    }
    else if (  (mouse_x>=wrkspc_dir_window_pos_x)
               && (mouse_x<=wrkspc_dir_window_pos_x + wrkspc_dir_window_width)
               && (mouse_y>=wrkspc_dir_window_pos_y)
               && (mouse_y<=wrkspc_dir_window_pos_y + wrkspc_dir_window_height))
    {
        if (wrkspc_dir_window_isFlyOver==false)
        {
            wrkspc_dir_window_mouseIsOver(mx, my);
        }
        return true;
    }

    return false;
}

/** \brief Do what has to be on Mouse is over the window event
 * - set wrkspc_dir_window_isFlyOver to true
 *
 * \param mouse x position
 * \param mouse y position
 * \return void
 *
 */
void wrkspc_dir_window_mouseIsOver(int mx, int my)
{
    wrkspc_dir_window_isFlyOver=true;

    //what else if window is fly over by mouse
}

/** \brief Do what has to be on Focus window event
 * - set wrkspc_dir_window_hasFocus to true
 *
 * \param mouse x position
 * \param mouse y position
 * \return void
 *
 */
void wrkspc_dir_window_getFocus(int mx, int my)
{
    wrkspc_dir_window_hasFocus=true;

    //what else if window get focus --> focus objet of the window under position (mx,my
}

/** \brief Do what has to be on Lose Focus window event
 * - set wrkspc_dir_window_hasFocus to false
 *
 * \param mouse x position
 * \param mouse y position
 * \return void
 *
 */
void wrkspc_dir_window_loseFocus()
{
    wrkspc_dir_window_hasFocus=false;

    //what else if window lose focus --> send event to objet of the window : exemple dropdown will set has retracted etc ...
}

/** \brief New position of the window relative to mouse position
 *
 * \param mouse_xy
 * \param mouse_y
 * \return bool
 *
 */
bool wrkspc_dir_window_moveTo(int mouse_x, int mouse_y)
{
    wrkspc_dir_window_pos_x = mouse_x-(40+15);
    wrkspc_dir_window_pos_y = mouse_y-25;
    return true;
}

/** \brief Solve on mouse left clic event for this window
 *
 * \param none
 * \return void
 *
 */
void wrkspc_dir_window_mouseLeftHandle()
{
    int mx = wrkspc_dir_window_pos_x ;
    int my = wrkspc_dir_window_pos_y ;

    do_logical_MoveCloseBox( wrkspc_dir_window_pos_x+wrkspc_dir_window_moveCloseButtons_x,
                             wrkspc_dir_window_pos_y+wrkspc_dir_window_moveCloseButtons_y,
                             wrkspc_dir_window_ID);

//si pas la fenêtre de Move/Close

    if (window_focus_id==wrkspc_dir_window_ID
	&&  mouseClicLeft.isToBeProcessed())//si focus sur la fenetre
    {
//BOUTON LOOP
        if(mouse_x>mx+260 && mouse_x<mx+280 && mouse_y>my+100 && mouse_y<my+120)
        {
            mouseClicLeft.SetProcessed(); //on encleche le bouton pour pas avoir de double ordre
            my_window_variable_boolean=toggle(my_window_variable_boolean);
        }
//FADERS
        for(int i=0; i<6; i++) //pas de mouse released, c est que pour les boutons
        {
            if(mouse_x>mx+10+(i*35) && mouse_x<mx+30+(i*35) && mouse_y>my+60 && mouse_y<my+207)//10 pixels en haut et en bas en plus
            {
                my_window_fader_value[i] = constrain_data_to_midi_range((my+70+127)-mouse_y);//dans core_6.cpp
            }
        }
	}//fin condition focus

}

///////////////////////////////////////////////////////////////////////////////
//L'AFFICHAGE//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/** \brief Initialisation to do before showing window
 *
 * \return void
 *
 */
void wrkspc_dir_window_initShow()
{
//if some thing to initialise or refresh before windows is shown

    wrkspc_dir_window_isListening=true; //the fact is that the window is starting to leasen for events
    wrkspc_dir_window_getFocus(wrkspc_dir_window_pos_x, wrkspc_dir_window_pos_y) ; //window get focus when open, but no special part is selected
}

/** \brief Cleaning before stop show of window
 *
 * \return void
 *
 */
void wrkspc_dir_window_endShow()
{
//if some thing to do after end of showing the window

    wrkspc_dir_window_isListening  = false; //the fact is that we had stop drawing it so goodbye !
    wrkspc_dir_window_isVisible = false;
}

/** \brief Draw the window and content
 *
 * \return void
 *
 */
void wrkspc_dir_window_show()
{
    wrkspc_dir_window_isVisible = true; //the fact is that we are drawing it now !


    // int mx = wrkspc_dir_window_pos_x ;
    // int my = wrkspc_dir_window_pos_y ;

//la fenêtre en elle même: un rectangle
    Rect windowFrame(Vec2D(wrkspc_dir_window_pos_x,wrkspc_dir_window_pos_y),
                     Vec2D( largeur_my_window,hauteur_my_window));
//facteur d'arrondissement du rectangle
    windowFrame.SetRoundness(15);
    windowFrame.SetLineWidth(double_epaisseur_ligne_fader);
//fond
    windowFrame.Draw(CouleurFond);
//pourtour
    if(wrkspc_dir_window_hasFocus)//si elle est sélectionnée bord orange
    {
        windowFrame.DrawOutline(CouleurFader);
    }
    else
    {
        windowFrame.DrawOutline(CouleurLigne);
    }
    neuro.Print( wrkspc_dir_window_title,
	//petitchiffre.Print(wrkspc_dir_window_title,
                 wrkspc_dir_window_pos_x+wrkspc_dir_window_title_x,
                 wrkspc_dir_window_pos_y+wrkspc_dir_window_title_y);

//position des boutons Move/Close
    MoveCloseBox( wrkspc_dir_window_pos_x+wrkspc_dir_window_moveCloseButtons_x,
                  wrkspc_dir_window_pos_y+wrkspc_dir_window_moveCloseButtons_y,
                  wrkspc_dir_window_ID);

//BOUTON LOOP
    loop_button_view(wrkspc_dir_window_pos_x+260,
                     wrkspc_dir_window_pos_y+100,
                     my_window_variable_boolean);

//FADER d une valeur de 127 pixel

    Rect FaderFrame(Vec2D(wrkspc_dir_window_pos_x, wrkspc_dir_window_pos_y),
                    Vec2D(20,127));
    FaderFrame.SetRoundness(3);

    for(int i=0; i<6; i++)
    {
        petitchiffre.Print(ol::ToString(my_window_fader_value[i] ),
                           wrkspc_dir_window_pos_x+12+(i*35),
                           wrkspc_dir_window_pos_y+58);
        FaderFrame.MoveTo(Vec2D(wrkspc_dir_window_pos_x+10+(i*35),wrkspc_dir_window_pos_y+70));
        Rect FaderLevel(Vec2D(wrkspc_dir_window_pos_x+10+(i*35),wrkspc_dir_window_pos_y+70+127-my_window_fader_value[i] ),
                        Vec2D(20,my_window_fader_value[i] ));
        FaderLevel.SetRoundness(3);
        FaderLevel.Draw(CouleurFader);
        FaderFrame.DrawOutline(CouleurLigne);
    }
    ;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////PLUS RAPIDE ET MOINS DIFFICILE POUR ECRIRE D ABORD/////////
/////////////////////LE CODE AVANT SCINDAGE EN LOGIQUE / VISUEL ////////////////
////////////////////////////////////////////////////////////////////////////////


#endif // WRKSPC_DIR_CLASS_INCLUDED
