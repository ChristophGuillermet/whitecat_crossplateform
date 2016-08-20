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

* \file whc_hk_connector.cpp
* \brief {hotkeys service - object - link apply & input to manage hotkey service}
* \author Rui Serge Azevedo Brooks
* \version {1.0.0}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*
*	Objet de service gérant les liens entre raccourcis et fonctions internes à déclencher
*
*/

#include "whc_hk_connector.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables Globales à la classe (static) partagée par toutes les instances ...
// ''manager'' est déclaré comme variable global dans Whitecat, mais ça inclus c_list et c_catlist : même type d'objet - tous partagent les var & fct static
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// les public (accessibles directement depuis l'extérieur de l'objet ... à manipuler avec attention pour éviter toute erreur
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int whc_hk_connector::c_nbr = 0;
std::vector<whc_hk_connector> whc_hk_connector::c_list;
std::vector<whc_hk_connector> whc_hk_connector::c_catlist;
std::vector <char*> whc_hk_connector::c_filter ;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// les private (accessibles éventuellement depuis l'extérieur de l'objet par des fonctions ... pour éviter toute erreur
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool whc_hk_connector::c_hk_user_madeChanges=false;
bool whc_hk_connector::c_hk_user_update_isOn=false ; // on lit pour mettre à jour un lien : ne rien déclencher en attendant confirmation ou ESC
bool whc_hk_connector::c_hk_user_hasToConfirmChoice=false;
int whc_hk_connector::c_hk_user_hasSelect_applyId=0 ;
whc_hk_apply whc_hk_connector::c_user_other_func_allready_link_to_hotkey;
whc_hk_input whc_hk_connector::c_user_signature ;
whc_hk_apply whc_hk_connector::c_trigger_fired ;
bool * whc_hk_connector::c_ptr_inputIsOn;
bool whc_hk_connector::c_hk_service_isInit=false;
int whc_hk_connector::c_filter_idx=0;

// objet non terminé whc_report whc_hk_connector::c_report;

whc_hk_connector::whc_hk_connector()
{
    //ctor
    c_nbr++;
}

whc_hk_connector::whc_hk_connector(whc_hk_apply fonctionality, whc_hk_input signature)
{
    //ctor
    m_fonctionality = fonctionality ;
    m_signature = signature;
    c_nbr++;
}

whc_hk_connector::~whc_hk_connector()
{
    //dtor
    c_nbr--;
}

void whc_hk_connector::user_start_update_link(int val)
{
    c_hk_user_update_isOn=true;
    c_hk_user_hasSelect_applyId=val;
}

int whc_hk_connector::collect()
{
    if ( keypressed())
    {
        int isreadkey = readkey();
        int tmp_scancode=(isreadkey >> 8);
        while ( keypressed())
        {
            int clearbuff = readkey();
        }

        //update last user keyboard input
        c_user_signature = whc_hk_input::c_scan(tmp_scancode);

        bool hotkey_isReserved = false ;

//---------------------------------------------------------------------------------------------
        // Liste des touches qui ne peuvent pas être utilisées dans un shortcut :
        // sans une des deux touches de modification Ctrl ou Alt
        //-- Une combinaison avec shift seul est interdite (ex. : shift tab)
//        if (not(c_user_signature.ctrl() || c_user_signature.alt()))
//        {
//            switch (tmp_scancode)
//            {
//            case KEY_TAB:
//                hotkey_isReserved = true ;
//                break;
//            default:
//                break;
//			}
//        }
//---------------------------------------------------------------------------------------------
        // Liste des touches qui ne peuvent pas être utilisées dans un shortcut sans modification
        // (sans une des trois touches de modification)
        if (not(c_user_signature.ctrl() || c_user_signature.shift() || c_user_signature.alt()))
        {
            switch (tmp_scancode)
            {
            case KEY_BACKSPACE:		//pour effacer la saisie
            case KEY_ESC:			//pour quitter le mode de saisie
            case KEY_ENTER:			//pour affecter la saisie
            case KEY_ENTER_PAD:
            case KEY_DEL_PAD: 		// c'est pris pour = '.'
            case KEY_0_PAD...KEY_9_PAD:
            case KEY_0...KEY_9:
                hotkey_isReserved = true ;
                break;
            default:
                break;
            }
        }

        bool theInputIsOn;
        theInputIsOn = *c_ptr_inputIsOn ;
        if (theInputIsOn
		// mode de saisie texte activée actuellement (NAME) : l'alphabet lui est réservé
                && (not(c_user_signature.ctrl() || c_user_signature.alt()) || c_user_signature.shift() ))
        {
            switch (tmp_scancode)
            {
            case KEY_A...KEY_Z:
            case KEY_SPACE:
                hotkey_isReserved = true ;
                break;
            default:
                break;
            }
        }

        //ré-init
        whc_hk_apply neutre ;
        c_trigger_fired = neutre ;

        if ((not hotkey_isReserved)	    	// signature de hotkey autorisée
		&& c_hk_service_isInit) 			// service is proprely initiate (data read)
        {
            if(c_hk_user_hasSelect_applyId >0)
			// c_hk_user_hasSelect_applyId = l'utilisateur a sélectionné une fonction pour lui associer une nouvelle hotkey
            {
                //search if user_signature is allready associate to a fonctionality
                whc_hk_apply fctlink = search_fct(c_user_signature);

                if (fctlink.id()==c_hk_user_hasSelect_applyId) // this signature is allready associated to the aim fonctionnality
                {
                    link_fct_hk(c_hk_user_hasSelect_applyId,c_user_signature);
                    user_redefine_hk_link_init() ;
                }
                else if (fctlink.id()==-1) // this signature is not used by any other fonctionnality
                {
                    link_fct_hk(c_hk_user_hasSelect_applyId,c_user_signature);
                    user_redefine_hk_link_init() ;
                    updateFilter();
                    c_hk_user_madeChanges=true;   // pour faire apparaître le save button
                }
                else   //la hotkey choisie par l'ulisateur est déjà associée à une autre fonction : demander confirmation de l'association
                {
                    c_user_other_func_allready_link_to_hotkey = fctlink ;
                    c_hk_user_hasToConfirmChoice = true ;
                }
            }
            else //pas de fonction a associer à une hotkey dans config
            {
                user_redefine_hk_link_init() ;
                return shortcutprocess(isreadkey);
            }


        }
        else if (tmp_scancode == KEY_ESC)
        {
            if(c_hk_user_hasSelect_applyId >0)
            {
                //abandon définition
                user_redefine_hk_link_init() ;
                return -1 ; //isreadkey was used - not to be used by command language
            }
            else return isreadkey ;   // ESC d'autre chose --> on passe la main à la saisie de WhiteCat
        }
        else return isreadkey ;  // pas de hotkey - pas de définition en cours --> on passe la main à la saisie de texte/chiffre

    }
    else return -1 ; //no isreadkey - nothing to be used by command language

}

int whc_hk_connector::shortcutprocess(int isreadkey)
{
    //search if signature is known in subscription list
    whc_hk_apply fctlink = search_fct(c_user_signature);
    if (fctlink.id()>0)
    {
        void (*fctptr)(void);       			/*déclaration du pointeur*/
        fctptr = fctlink.processOnHotkey();   	/*Initialisation*/
        if (fctptr!=nullptr)
        {
            fctptr();  /* Execution de la méthode */
            c_trigger_fired = fctlink ;
        }
        whc_hk_input neutre ;
        //c_user_signature = neutre ;
        return -1 ;
    }
    else
        return isreadkey;
}

whc_hk_apply whc_hk_connector::search_fct(whc_hk_input signature)
{
    int i = c_list.size();

    while (i>0)
    {
        i--;
        whc_hk_apply list_fonctionality ;
        whc_hk_input list_signature ;
        whc_hk_connector* hotkey;
        hotkey = &whc_hk_connector::c_list[i];
        list_fonctionality = hotkey->fonctionality();
        list_signature     = hotkey->signature();

        if ((list_signature.alt()      == signature.alt())
                &&  (list_signature.ctrl()     == signature.ctrl())
                &&  (list_signature.shift()    == signature.shift())
                &&  (list_signature.scancode() == signature.scancode()))
        {
            i=0;
            return list_fonctionality ;
        }
    }
    whc_hk_apply null_fct ;
    return null_fct ;
}

void whc_hk_connector::connect_fct(int fctid, ptrMthd fctptr)
{
    int i = c_list.size();

    while (i>0)
    {
        i--;
        whc_hk_connector* hotkey ;
        hotkey = &whc_hk_connector::c_list[i] ;
        whc_hk_apply fonctionality ;
        whc_hk_input signature ;
        fonctionality = hotkey->fonctionality() ;
        signature = hotkey->signature() ;

        if (fonctionality.id()==fctid)
        {
            fonctionality.SetprocessOnHotkey(fctptr);
            whc_hk_connector::c_list[i].Setfonctionality(fonctionality);
            //whc_hk_connector::c_list[i].Setsignature(signature);
            i=0;
        }
    }
}

void whc_hk_connector::init(std::string fic_name)
{
    std::vector<whc_hk_connector> clear_list;
    c_list.swap(clear_list);
// sqlite3   if (fic_name.substr(fic_name.size() - 3) == ".db")
//    {
//        load_db(fic_name);
//    }
//    else
    {
        load(fic_name);
    }

    c_filter_idx=0;
    updateFilter();
}

void whc_hk_connector::load(std::string fic_name)
{
    c_hk_service_isInit=false;
    std::ifstream fic_stream(fic_name.c_str(), std::ios::in);

    if (not(fic_stream.fail()))
    {
        std::string ligne ;
        whc_toolbox tool;
        while(getline(fic_stream, ligne))
        {
            int tmp_id;
            std::string tmp_module;
            std::string tmp_description;
            bool tmp_shift;
            bool tmp_ctrl;
            bool tmp_alt;
            int  tmp_scancode;
            std::string tmp_wording;

            std::vector<std::string> tokens = tool.split_string(ligne,';');

            if (tokens.size()>=8)
            {
                tmp_id               = tool.string_to_int (tokens[0]);
                tmp_module           = tokens[1] ;
                tmp_description      = tokens[2] ;
                tmp_shift            = (tool.string_to_int (tokens[3])==1);
                tmp_ctrl             = (tool.string_to_int (tokens[4])==1);
                tmp_alt              = (tool.string_to_int (tokens[5])==1);
                tmp_scancode         = tool.string_to_int (tokens[6]);
                tmp_wording          = tokens[7] ;

                whc_hk_input signature( tmp_shift,  tmp_ctrl,  tmp_alt,  tmp_scancode) ;
                whc_hk_apply fonctionality(tmp_id, tmp_module, tmp_description, nullptr) ;
                c_list.push_back(whc_hk_connector(fonctionality, signature));
            }
        }
        c_hk_service_isInit=true;
        fic_stream.close();
    }
}

void whc_hk_connector::save(std::string fic_name)
{
    if (c_hk_user_madeChanges && c_hk_service_isInit)  // l'utilisateur a changer la mapping et le service a été initialisé
    {
        c_hk_user_madeChanges=false;

        std::ofstream fic_stream(fic_name.c_str(), std::ios::out | std::ios::trunc);

        if (not(fic_stream.fail()))
        {
            whc_toolbox tool;

            int idx_back = c_list.size();
            int list_size = idx_back ;

            while (idx_back>0)
            {
                int idx_forward = list_size - idx_back;
                idx_back--;

                whc_hk_apply list_fonctionality ;
                whc_hk_input list_signature ;
                whc_hk_connector* hotkey;
                hotkey = &whc_hk_connector::c_list[idx_forward];
                list_fonctionality = hotkey->fonctionality();
                list_signature     = hotkey->signature();

                std::string ligne ;
                ligne += tool.int_to_string(list_fonctionality.id());
                ligne +=";" ;
                ligne += list_fonctionality.module();
                ligne +=";" ;
                ligne += list_fonctionality.description();
                ligne +=";" ;
                ligne += tool.bool_to_string(list_signature.shift());
                ligne +=";" ;
                ligne += tool.bool_to_string(list_signature.ctrl());
                ligne +=";" ;
                ligne += tool.bool_to_string(list_signature.alt());
                ligne +=";" ;
                ligne += tool.int_to_string(list_signature.scancode());
                ligne +=";" ;
                ligne += list_signature.wording();
                ligne +=";" ;

                fic_stream << ligne << std::endl ;
            }
            fic_stream.close();
        }
    }

}

void whc_hk_connector::link_fct_hk(int fctid, whc_hk_input signature)
{
    int idx_back = c_list.size();

    while (idx_back>0)
    {
        idx_back--;
        whc_hk_connector* hotkey ;
        hotkey = &whc_hk_connector::c_list[idx_back] ;
        whc_hk_apply fonctionality ;
        fonctionality = hotkey->fonctionality() ;

        if (fonctionality.id()==fctid)
        {
            whc_hk_connector::c_list[idx_back].Setsignature(signature);
            idx_back=0;
        }
    }
}

void whc_hk_connector::replace_link_fct_hk()
{
    bool oldisclear = false ;
    bool newisset = false ;

    int idx_back = c_list.size();

    while (idx_back>0)
    {
        idx_back--;
        whc_hk_connector* hotkey ;
        hotkey = &whc_hk_connector::c_list[idx_back] ;
        whc_hk_apply fonctionality ;
        fonctionality = hotkey->fonctionality() ;

        if (fonctionality.id()==c_hk_user_hasSelect_applyId)
        {
            whc_hk_connector::c_list[idx_back].Setsignature(c_user_signature);  //set new link
            newisset = true;
            if (oldisclear) idx_back=0; //both action done
        }

        if (fonctionality.id()==c_user_other_func_allready_link_to_hotkey.id())
        {
            whc_hk_input null_signature;
            whc_hk_connector::c_list[idx_back].Setsignature(null_signature); //clear old link
            oldisclear = true;
            if (newisset) idx_back=0;  //both action done
        }
    }

    c_hk_user_madeChanges=true;
    user_redefine_hk_link_init();
}

void whc_hk_connector::user_redefine_hk_link_init()
{
    whc_hk_apply null_fct ;

    c_hk_user_hasSelect_applyId   = -1 ;    // fonctionality->id()
    c_hk_user_hasToConfirmChoice = false ; // on demande confirmation, si signature déjà attribuée à une autre fonction
    c_user_other_func_allready_link_to_hotkey = null_fct ;
    c_hk_user_update_isOn	= false;
    //surtout pas réinit c_user_signature
}

// sqlite3
//void whc_hk_connector::load_db(std::string fic_name)
//{
//    int db_rc ;
//    char *zErrMsg = 0;
//    sqlite3 *hotkey_db;
//    db_rc = sqlite3_open(fic_name.c_str(), &hotkey_db);
//
//    if (db_rc)
//    {
//        fprintf(stderr, "Can't open hotkey data %s %s\n", fic_name.c_str(), sqlite3_errmsg(hotkey_db));
//    }
//
//    else // not fail
//    {
//        sqlite3_stmt *ppStmt;
//        const char *pzTail;
//
//        db_rc = sqlite3_exec(hotkey_db, "select * from hotkey", read_db_row, 0, &zErrMsg);
//
//        if( db_rc != SQLITE_OK )
//        {
//            fprintf(stderr, "SQL error opening hotkey data : %s %i\n", fic_name.c_str(), db_rc);
//
//        }
//    }
//    sqlite3_close(hotkey_db);
//}

int whc_hk_connector::read_db_row(void *NotUsed, int row_nbr_col, char **row_data_col, char **db_ColName)
{
    if (row_nbr_col>=8)
    {
        int tmp_id;
        std::string tmp_module;
        std::string tmp_description;
        bool tmp_shift;
        bool tmp_ctrl;
        bool tmp_alt;
        int  tmp_scancode;
        std::string tmp_wording;
        whc_toolbox tool;

        tmp_id               = tool.string_to_int (row_data_col[0]);
        tmp_module           = row_data_col[1] ;
        tmp_description      = row_data_col[2] ;
        tmp_shift            = (tool.string_to_int (row_data_col[3])==1);
        tmp_ctrl             = (tool.string_to_int (row_data_col[4])==1);
        tmp_alt              = (tool.string_to_int (row_data_col[5])==1);
        tmp_scancode         = tool.string_to_int (row_data_col[6]);
        tmp_wording          = row_data_col[7] ;

        whc_hk_input signature( tmp_shift,  tmp_ctrl,  tmp_alt,  tmp_scancode) ;
        whc_hk_apply fonctionality(tmp_id, tmp_module, tmp_description, nullptr) ;
        c_list.push_back(whc_hk_connector(fonctionality, signature));


        int i;
        FILE * pFile;
        pFile = fopen ("hotkey-cr-lecture.txt","a");
        for(i=0; i<8; i++)
        {
            fprintf (pFile, "%s = %s\n", db_ColName[i], row_data_col[i] ? row_data_col[i] : "NULL");
        }
        fprintf (pFile, "\n");
    }

    return 0;
}

void whc_hk_connector::updateFilter()
{
    c_catlist.clear();

    if(c_filter_idx>(c_filter.size()-1))
    {
        c_filter_idx=0;
    }

    int idx_back = c_list.size();
    while (idx_back>0)
    {
        idx_back--;
        whc_hk_connector* hotkey ;
        hotkey = &whc_hk_connector::c_list.at(idx_back) ;
        whc_hk_apply fonctionality ;
        fonctionality = hotkey->fonctionality() ;

        if (fonctionality.module()==c_filter.at(c_filter_idx))
        {
            c_catlist.push_back(c_list.at(idx_back));
        }
    }
    if (c_catlist.size()>0)
    {
        std::reverse(c_catlist.begin(),c_catlist.end());
    }
}

void whc_hk_connector::changeDescription(whc_hk_connector* ptr_hk_manage, std::string newdescription )
{
	ptr_hk_manage->m_fonctionality.Setdescription(newdescription);
}
