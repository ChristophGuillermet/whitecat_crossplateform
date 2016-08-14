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

* \file wrksp_dir.h
* \brief {header file for exemple to create a new module window}
* \author Christoph Guillermet
* \version {0.8.5.2}
* \date {19/02/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Exemple pour cr�er sa propre fen�tre dans whitecat afin d'ajouter un nouveau module
*
*   Exemple to create a new module window
*

* ///////////////////////////////////////////////////////////////////////////////////////////////////
* /////////////////CREER UNE FENETRE C EST LE PLUS .... NEBULEUX ////////////////////////////////////
* ////////////////////PETIT PAS A PAS EN MODE TUNNEL/////////////////////////////////////////////////
* //////////////////////////////////////////////////////////////////////////////////////////////////

* Dans un premier temps vous pouvez directement modifier My_window_file_sample.cpp .
* C est un gabarit actif dans whitecat. Passer � ce moment directement au point 5 pour essayer.
* Par contre vous avez besoin de transformer wrksp_dir en votre_module, ou d'ajouter une fen�tre,
* suivez les manipulations des points 1 � 4



* /////////////////////CREER UNE FENETRE VIERGE/////////////////////////////////////////////////////
*
* 1. DEFINIR UNE NOUVELLE ID DE FENETRE
*
* whitecat.h -> WINDOW{} -> max_window_identity_is
* ------------------------------------------------
* D�finir dans enum WINDOW{} l'ID unique de la fen�tre
* max_window_identity_is = plus grand valeur possible de enum WINDOW{}
* L'ID de My_Window est 927
*
*	--> objet whitecat_window : ID donn�e membre constant (initi� � la construction et plus modifiable)
*                               max_window_identity_is donn�e membre statique
*                               (partag�e par tous les objets window : unique pour la classe :
*                                  - init � 0 dans la port� globale
*                                  - puis � chaque cr�ation si ID > max_window_identity_is alors max_window_identity_is = ID
*
* 2. CREER L OUVERTURE FERMETURE DE FENETRE PAR L INDEX BOOLEEN. MODIFIER LES FONCTIONS
* D OUVERTURE FERMETURES DE FENETRES
*
* Bool�en g�rant l'activation et l'�coute aux �v�nements
* ------------------------------------------------------
* Indicateur bool�en pr�cisant que la fen�tre est active et qu'il faut traiter les �v�nements la concernant
* fen�tre wrkspc_dir --> wrkspc_dir_window_isListening  (� l'�coute)
*                        wrkspc_dir_window_isVisible (affich�e)
*
*
* gestionnaire_fenetres2.cpp -> add_a_window()
* --------------------------------------------
* Ouverture de fen�tre ( et mettre des choses logiques si besoin  d'initialisation des donn�es par ex )
*
* case par WINDOW{ID} :
* fen�tre wrkspc_dir --> case W_WRKSPC_DIR
* 							wrkspc_dir_window_initShow() : initialisation ou refresh des donn�es avant affichage
* 							wrkspc_dir_window_isListening=true
*
*
* gestion_fenetres2.cpp -> substract_a_window()
* ---------------------------------------------
* Fermeture de la fen�tre ( et mettre des choses logiques si besoin )
*
* case par WINDOW{ID} :
* fen�tre wrkspc_dir --> case W_WRKSPC_DIR
*                             wrkspc_dir_window_endShow()
*                             wrkspc_dir_window_isListening=false
*                             wrkspc_dir_window_isVisible=false
*
* 3. AJOUT D'UN BOUTON D'APPEL DANS LA FENETRE MENU
*
* Le menu est constitu� de 2 boucles enchass�es l'une dans l'autre: colonnes et lignes.
* Si vous rajoutez un autre bouton/entr�e au menu,
*           il faudra changer la boucle de la colonne correspondante
*           dans les fonctions l'utilisant
*                - logique
*                - et affichage (la logique est s�par�e de l'affichage pour la performance ).
*
*           donc pour la boucle d'une colone
*                la boucle des lignes for(int cl=0;cl<5;cl++) deviendra for(int cl=0;cl<6;cl++)
*
* exemple "case 15" est "my window" :: 15  = bouton en 5�me ligne + (2�me colonne -1)x10
* Identifiant des boutons de la 1�re colonne =  0 + num de ligne dans colonne
*                               2de colonne = 10 ...idem...
*                              3�me colonne = 20 ...idem...
*  Identifiant (menu_window_addbutton_wrkspc_dir_GridCol - 1)x10 + menu_window_addbutton_wrkspc_dir_GridCol
*
* (Menu window) call_everybody_5.cpp -> do_logical_menus()
* --------------------------------------------------------
* IMidi = identifiant midi est mis � 2047 (pour My Window) TEMPORAIREMENT
* Cet identifiant doit �tre attribu� de mani�re unique :
* 			il faut regarder ce qui n est pas d�j� attribu� dans
* 							  midi_13.cpp -> fonction do_midi_call_order(int control) o� control est l 'identifiant midi (de la commande)
*                             -------------------------------------------------------
*           voir et mettre � jour la liste affectation_midi.txt dans les sources
*                                          --------------------
* cette fonction appelle toutes celles g�rant individuellement la r�action au clic de chaque bouton
* (ci-apr�s gui_boutons_rebuild1.cpp -> command_button_logical )
*
* (Menu window) call_everybody_5.cpp -> Menus()
*----------------------------------------------
* Affichage des boutons du menu
* Modifier la bonne colonne du  for(int cl=0;cl<max_ligne;cl++)
*
* noter que dans Menus() et dans do_logical_menus() stae est notre bool�en wrkspc_dir_window_isListening
*
* Si vous avez besoin d'agrandir la fen�tre des menus, notamment en hauteur, vous trouverez dans whitecat.h
* int size_x_mainmenu=365;
* int size_y_mainmenu=200;
*
* (Menu window) gui_boutons_rebuild1.cpp -> command_button_logical()
*-------------------------------------------------------------------
* Gestion du click par bouton du menu / selon l'identifiant dans la liste des boutons du menu ((num col-1)*10 + num lig)
*
* case par (identifiant dans la liste des boutons du menu) :
* fen�tre wrkspc_dir --> 05
*
* (Menu window) gui_boutons_rebuild1.cpp -> command_button_view ()
*-----------------------------------------------------------------
* par contre (shame on me) c est l'id midi qui est prise en compte comme identifiant. car je checkais des cas sp�cifiques.
* (les commandes du haut notamment)
*
* case par (identifiant midi du bouton du menu) :
* fen�tre wrkspc_dir --> 2047
*
* /////////////////////DESSINER LA FENETRE VIERGE////////////////////////////////////////
*
* Ok, on arrive au bout de la purge.
*
* On va avoir besoin de variables globales pour avoir la position de la fenetre et sa taille:
* d�clarer dans le fichier d'include:
*
*
* //la position
* int wrkspc_dir_window_pos_x=100;//pixels
* int wrkspc_dir_window_pos_y=100;
* //la taille
* int wrkspc_dir_window_width=400;//pixels
* int wrkspc_dir_window_height=250;
*
*
4. MODIFIER LES FICHIERS DEDIEZ  AU TRAITEMENT DE LA LOGIQUE et A L AFFICHAGE:
*
* proc_visuels_rebuild1.cpp -> detection_over_window()
* ----------------------------------------------------
* fonction d�terminant si la fen�tre est survol�e par la sourie
* (cette fonction appel�e sur le click sourie sauf si fen�tre message en attente de r�ponse)
* ... elle positione le focus / retire le focus
*
* case par WINDOW{ID} :
* fen�tre wrkspc_dir --> wrkspc_dir_window_isMouseOver ()
*
* proc_visuels_rebuild1.cpp -> move_window(int idwindowis)
* --------------------------------------------------------
* ... � analyser plus avant = trichro entre autre : vx =(int) (cos(angle_snap)*125);
*
* case par WINDOW{ID} :
* fen�tre wrkspc_dir --> wrkspc_dir_window_MoveTo ()
*
*
* proc_visuels_rebuild1.cpp -> check_graphics_mouse_handling()
* ------------------------------------------------------------
//ca c est votre fonction pour definir ce qui se passe au click souris
*
* case par WINDOW{ID} :
* fen�tre wrkspc_dir --> wrkspc_dir_window_mouseLeftHandle ()
*
* *********************************************************************************************
*   Vous verrez que dans les sources de whitecat il ya un fichier _visu et un fichier _core.
*     Pour faire simple les fonctions appel�es vont aller dans votre fichier wrkspc_dir.cpp
* *********************************************************************************************
*
* graphic_rebuild1 -> Boxes()
* ---------------------------
* ENFIN c est l� ou est fait l'affichage
*
* case par WINDOW{ID} :
* fen�tre wrkspc_dir --> wrkspc_dir_window_show ()
*
* 5. ENFIN ECRIRE VOTRE FENETRE dans wrkspc_dir_file_sample.cpp
*
* Ok. Comme s�parer la logique de l'affichage c est un peu tordu, vous pouvez aussi ne rien mettre dans do_logical_wrkspc_dir_Box(int mw_x, int mw_y)
et �crire logique et visu d'abord dans wrkspc_dir_Box(int mw_x, int mw_y) puis nettoyer, en ne laissant que la logique dans la logique, et la visu dans la visu
*
* vous pouvez aller dans  wrkspc_dir_file_sample.cpp
* la doc d open layer (la lib graphique opengl) est dans le dossier doc_ol
*
* banger_visu et banger_core sont des bons exemples d affichage, logique
* faders_visu faders_core aussi
* gridplayer aussi
*
**/


#ifndef WRKSPC_DIR_H_INCLUDED
#define WRKSPC_DIR_H_INCLUDED

int do_logical_MoveCloseBox(int,int,int); //sera d�finit + tard dans proc_visuels_rebuld1.cpp
int loop_button_view(int,int,bool);//sera d�finit + tard dans gui_boutons_rebuild1.cpp
int MoveCloseBox(int,int,int); //sera procs_visuels_rebuild1.cpp

//Donn�es membres � h�riter de la future class white cat window (init dans le constructeur)
const int wrkspc_dir_window_ID = 928;
int wrkspc_dir_window_nbrID = 0; //fait doublon avec ID � terme
bool wrkspc_dir_window_isListening; //pour vos fenetres vous cr�erez un autre index_bool�en
bool wrkspc_dir_window_isVisible; //pour vos fenetres vous cr�erez un autre index_bool�en
bool wrkspc_dir_window_isFlyOver;
bool wrkspc_dir_window_hasFocus;

int  wrkspc_dir_window_pos_x=200;//pixels
int  wrkspc_dir_window_pos_y=200;
int  wrkspc_dir_window_width=400;//pixels
int  wrkspc_dir_window_height=400;
char wrkspc_dir_window_title[64];
int  wrkspc_dir_window_title_x;
int  wrkspc_dir_window_title_y;
int  wrkspc_dir_window_moveCloseButtons_x;
int  wrkspc_dir_window_moveCloseButtons_y;

//Donn�es membres sp�cifique � la classe wrkspc_dir (init dans le constructeur)
bool wrkspc_dir_variable_boolean=0;
int wrkspc_dir_fader_value[6];

//le constructeur de l'objet
void wrkspc_dir ();

//fonctions membres � h�riter de la future class white cat window
void wrkspc_dir_window_initShow();
void wrkspc_dir_window_show(int, int);
void wrkspc_dir_window_endShow();
bool wrkspc_dir_window_isMouseOver(int,int);
void wrkspc_dir_window_mouseIsOver(int, int);
void wrkspc_dir_window_getFocus(int, int);
void wrkspc_dir_window_loseFocus();
bool wrkspc_dir_window_moveTo(int, int);
void wrkspc_dir_window_mouseLeftHandle();

//Param�tres � fournir � la cr�ation de la fen�tre Menu � l'ajout du bouton
const int  menu_window_addbutton_wrkspc_dir_IDmidi=2048; 		// ! pas report� et enregistr� dans la gestion midi
const char menu_window_addbutton_wrkspc_dir_Name[]="Directory";
const int menu_window_addbutton_wrkspc_dir_GridCol = 1; 		// colonne o� le bouton sera plac� sur l'�cran menu
const int menu_window_addbutton_wrkspc_dir_GridLin = 5; 		// ligne   o� le bouton sera plac� sur l'�cran menu
const char menu_window_addbutton_wrkspc_dir_Shortcut[]="Shift-R";


#endif // WRKSPC_DIR_H_INCLUDED
