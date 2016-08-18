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

* \file wh_hk_manage.h
* \brief {header file for hotkeys service }
* \author Rui Serge Azevedo Brooks
* \version {0.8.9}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*   Variables et fonctions gérant les liens entre hotkeys et fonctions à déclencher
*   Fonctions de gestion d'initialisation, mises à jour sur demande de l'utiliateur
*
*
*/

#ifndef WHC_HK_MANAGE_H
#define WHC_HK_MANAGE_H

//Allegro
#include <allegro/keyboard.h>
//Container C compatible
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
// gestion de base de données désactivée #include <sqlite3.h>
//
#include <whc_hk_input.h>
#include <whc_hk_apply.h>
// objet non terminé #include <whc_report.h>

#include <whc_toolbox.h>

class whc_hk_manage
{
    typedef void (*ptrMthd)(void);  // les fonctions à fournir pour la connection doivent être du type "void nom_fct ()"

public:
    int static c_nbr;
    std::vector<whc_hk_manage> static c_list;		/**<  liste de toutes les fonctions avec leurs hotkeys associées */
    std::vector<whc_hk_manage> static c_catlist;  	/**<  liste limitée à la catégorie sélectionnée */
    whc_hk_input static c_user_signature ;

    bool static * c_ptr_inputIsOn; // (variable associée par référence de la variable externe) la zone de saisie texte est ouverte : elle est prioritaire

//	objet non terminé	whc_report static c_report;

    /** Default constructor */
    whc_hk_manage();
    whc_hk_manage(whc_hk_apply fonctionality, whc_hk_input signature);
    /** Default destructor */
    virtual ~whc_hk_manage();

    whc_hk_apply fonctionality()
    {
        return m_fonctionality;
    }
    void Setfonctionality(const whc_hk_apply &val)
    {
        m_fonctionality = val;
    }

    whc_hk_input signature()
    {
        return m_signature;
    }
    void Setsignature(const whc_hk_input &val)
    {
        m_signature = val;
    }

    static whc_hk_input user_signature()
    {
        return c_user_signature;
    }
    static void Setuser_signature(const whc_hk_input &val)
    {
        c_user_signature = val;
    }
    static int user_hasSelectThisFunc()
    {
        return c_hk_user_hasSelect_applyId;
    }

    //static std::string last_hk_wording() ; //{c_user_signature.wording();}

	static int filterIdx(){return c_filter_idx;}
	static void setfilterIdx(int val){c_filter_idx=val;}

    static void reset_user_choice()
    {
        c_hk_user_hasSelect_applyId=0;
    }

    static bool waiting_user_confirmation_on_a_choice ()
    {
        return c_hk_user_hasToConfirmChoice;
    }

    static whc_hk_apply user_conflictfunc()
    {
        return c_user_other_func_allready_link_to_hotkey;
    }

    std::string current_choice_fct_description ()
    {
        if (c_hk_user_hasSelect_applyId >0)
        {
            return this->c_list[this->user_hasSelectThisFunc()-1].fonctionality().description();
        }
        else
        {
            return " ## none ##";
        }
    }

    std::string current_choice_fct_accessible_with ()
    {
        if (c_hk_user_hasSelect_applyId >0)
        {
            return this->c_list[this->user_hasSelectThisFunc()-1].signature().wording();
        }
        else
        {
            return " ## unset ##";
        }

    }

    static std::string other_func_allready_link_to_hotkey()
    {
        return c_user_other_func_allready_link_to_hotkey.description();
    }

    static bool hk_user_update_isOn()
    {
        return c_hk_user_update_isOn ;
    }

    static bool hk_user_madeChanges()
    {
        return c_hk_user_madeChanges;
    }

    static void user_redefine_hk_link_init();
    static int categoryNbr(){return c_nbr_category;}

    static void link_keyFocusIndicator(bool * ptr_val)
    {
        c_ptr_inputIsOn = ptr_val ;
    }
    // c_ptr_inputIsOn devient "synonyme" de la variable passée par référence : elles lisent et modifient le même contenu mémoire

    int collect();
    void user_start_update_link(int val);

    void updateFilter();

    int shortcutprocess(int isreadkey);
    whc_hk_apply search_fct(whc_hk_input signature);
    static bool hk_service_isInit()
    {
        return c_hk_service_isInit;
    }
    void init(std::string fic_name);
    void load(std::string fic_name);
    void save(std::string fic_name);
    void connect_fct(int fctid, ptrMthd fctptr);
    void link_fct_hk(int fctid, whc_hk_input signature);
    void replace_link_fct_hk();

    void load_db(std::string fic_name);
    static int read_db_row(void *NotUsed, int argc, char **argv, char **azColName);

protected:
private:
    whc_hk_apply m_fonctionality ;
    whc_hk_input m_signature ;
//static = (une seule fois ne mémoire) en commun à toutes les instances (objets) de hotkey - idem pour les fonctions static aussi bien privé, public etc.
    whc_hk_apply static c_user_other_func_allready_link_to_hotkey ; // in case of conflict for a signature
    bool static c_hk_service_isInit;
    bool static c_hk_user_madeChanges;
    bool static c_hk_user_update_isOn ; // on lit pour mettre à jour un lien : ne rien déclencher en attendant confirmation ou ESC
    bool static c_hk_user_hasToConfirmChoice ; // on demande confirmation, si signature déjà attribuée à une autre fonction
    int static c_hk_user_hasSelect_applyId ; // fonctionality->id() = l'utilisateur a sélectionné une fonction pour lui associer une nouvelle hotkey
    int static c_filter_idx;
    int static c_nbr_category ;
};

#endif // WHC_HK_MANAGE_H
