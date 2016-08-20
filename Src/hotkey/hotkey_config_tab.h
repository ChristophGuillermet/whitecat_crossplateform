/*-------------------------------------------------------------------------------------------------------------
                                 |
          CWWWWWWWW              | Copyright (C) 2009-2016  Christoph Guillermet
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

* \file hotkey_config_tab.h
* \brief {header file for hotkeys configuration tab pannel }
* \author Rui Serge Azevedo Brooks
* \version {1.0.0}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*   Variables globales du panneau de configuration des hotkeys
*
*
*
*/

#ifndef HOTKEY_CONFIG_TAB_H
#define HOTKEY_CONFIG_TAB_H

    std::vector <bool> index_active_tab_config_hotkeys; 									/**< état d'activité de chaque onglet latéral dans le panneau de configuration des hotkeys */
    std::vector <char*> libelle_tab_config_hotkeys ;   	/**< libellé des onglets latéraux = nom des catégories dans le fichier */
    int num_page_list_hotkeys=0;

	typedef void (*ptrMthd)(void);					/**< pour définir les fonctions à passer comme argument dans des fonctions - fonctions de type "void nom_fonction ()" */
	typedef void (*ptrMthd_string)(std::string);	/**< pour définir les fonctions à passer comme argument dans des fonctions - fonctions de type "void nom_fonction (std::string)" */
	typedef void (*ptrMthd_int)(int);				/**< pour définir les fonctions à passer comme argument dans des fonctions - fonctions de type "void nom_fonction (int)" */


/*

   Déclaration des fonctions implantées dans : hotkey_config_tab.cpp

*/

void loadfile_config_hotkey(std::string file_name) ;
void save_config_hotkey() ;
void replace_config_hotkey() ;
void hotkey_esc_button_press() ;
void draw_logical_button(int insidePox_X, int insidePos_Y, int label_width, int button_hight, int text_to_border_X, int text_to_border_Y, std::string button_label, bool hasfocus) ;
void draw_logical_button(int insidePox_X, int insidePos_Y, int label_width, int button_hight, int text_to_border_X, int text_to_border_Y, std::string button_label, bool hasfocus, ptrMthd fctToFire) ;
void draw_logical_button(int insidePox_X, int insidePos_Y, int label_width, int button_hight, int text_to_border_X, int text_to_border_Y, std::string button_label, bool hasfocus, ptrMthd_string fctToFire, std::string file_name) ;
void draw_logical_hotkey_config_inactive (int cfg_X,int cfg_Y ) ;
void draw_logical_hotkey_config_update (int cfg_X,int cfg_Y ) ;
void do_hotkey_config_liste_pagination (int cfg_X,int cfg_Y) ;
void do_refresh_banger_catlist() ;

#endif // HOTKEY_CONFIG_TAB_H
