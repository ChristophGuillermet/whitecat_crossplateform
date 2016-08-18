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
* \version {0.8.9}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*   Variables globales du panneau de configuration des hotkeys
*
*
*
*/

#ifndef HOTKEY_CONFIG_TAB_H
#define HOTKEY_CONFIG_TAB_H

    int nbr_tab_config_hotkeys = 7;												/**< nombre de onglets latéraux dans le panneau de configuration des hotkeys */
	bool index_active_tab_config_hotkeys[7]; 									/**< état d'activité de chaque onglet latéral dans le panneau de configuration des hotkeys */
    std::vector <char*> libelle_tab_config_hotkeys (nbr_tab_config_hotkeys);   	/**< libellé des onglets latéraux = nom des catégories dans le fichier */
    int num_page_list_hotkeys=0;

#endif // HOTKEY_CONFIG_TAB_H
