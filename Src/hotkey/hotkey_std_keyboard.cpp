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

* \file hotkey_std_keyboard.cpp
* \brief {hotkeys service - standards keyboard inputs}
* \author Rui Serge Azevedo Brooks
* \version {0.8.9}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*
*	Toutes les saisies non associées à un raccourci clavier (saisie de chiffre, nom ...)
*
*/


void entree_clavier_standard(int isreadkey)
{
    int key_scancode=(isreadkey >> 8);
    if (key_scancode>26 && key_scancode<37) // 0 à 9 du haut de clavier
    {
        key_scancode += 10 ; 				// 0 à 9 du numpad ... pour la transco de scancode_to_name
    }
    char const *keyname = scancode_to_name(key_scancode);
    std::string keyname_char = std::string(keyname);

    char keyboardStorage_char[1] ;
    strncpy(keyboardStorage_char,
            keyname_char.c_str(),
            sizeof(keyboardStorage_char));

    switch (key_scancode)
    {
    case KEY_A...KEY_Z:
        if (index_type==1)
        {
            numeric[keyboardStorage_numeric_postext]=keyboardStorage_char[0];
            keyboardStorage_numeric_postext++;
        }

    case KEY_0...KEY_9:
    case KEY_0_PAD...KEY_9_PAD:
        numeric[keyboardStorage_numeric_postext]=keyboardStorage_char[0];
        keyboardStorage_numeric_postext++;
        break;

    case KEY_COMMA:					// virgule
    case KEY_DEL_PAD:				// supprime sur le numpad
        numeric[keyboardStorage_numeric_postext]='.';
        keyboardStorage_numeric_postext++;
        break;

    case KEY_BACKSPACE:
        numeric[keyboardStorage_numeric_postext]=' ';
        keyboardStorage_numeric_postext--;
        if (keyboardStorage_numeric_postext<0)
        {
            keyboardStorage_numeric_postext=0;
        }
        break;

	case KEY_ENTER:
		key_affectation();
		break;

	case KEY_ENTER_PAD:
		key_affectation();
		break;

    case KEY_ESC:					//nettoyage chaine de caractères et désélection totale

        reset_indexs_confirmation();
        reset_index_actions();
        key_unselect_ch();

        Midi_Faders_Affectation_Type=0;

        if(window_focus_id==W_ASKCONFIRM)
        {
            substract_a_window(W_ASKCONFIRM);
            substract_a_window(previous_window_focus_id);
            mouseClicLeft.SetProcessed();
            window_focus_id=previous_window_focus_id;
            add_a_window(window_focus_id);
        }
        sprintf(string_key_id,list_keyname[9]);
        break;

    default:
        break;
    }
    /// si la saisie NAME est active : ne pas dépasser le tableau en la mémoire
    if (keyboardStorage_numeric_postext>maxchar_numeric)
    {
        numeric[keyboardStorage_numeric_postext]=0;
        keyboardStorage_numeric_postext=maxchar_numeric-1;
    }
}

void hotkey_management_hook()
{
    if (hk_manager.hk_service_isInit())
    {
        int isreadkey = hk_manager.collect();
        if (isreadkey>0) // dans les cas : keypressed + pas un raccourcis clavier ou une définition
        {
            //gestion des saisies NAME et numerique qui ne sont pas traitées comme des hotkeys
            entree_clavier_standard(isreadkey);
        }
    }
    else
    {
        //appeler l'implantation standard sinon on perd tout contrôle clavier
        int rc = commandes_clavier() ;

    }
}

