#include "whc_hk_manage.h"


//initialistion des variables statiques communes à tous les objets de la classe
int whc_hk_manage::c_nbr = 0;
std::vector<whc_hk_manage> whc_hk_manage::c_list;
std::vector<whc_hk_manage> whc_hk_manage::c_catlist;
bool whc_hk_manage::c_hk_user_madeChanges=false;
bool whc_hk_manage::c_hk_user_update_isOn=false ; // on lit pour mettre à jour un lien : ne rien déclencher en attendant confirmation ou ESC
bool whc_hk_manage::c_hk_user_hasToConfirmChoice=false;
int whc_hk_manage::c_hk_user_hasSelect_applyId=0 ;
whc_hk_apply whc_hk_manage::c_user_other_func_allready_link_to_hotkey;
whc_hk_input whc_hk_manage::c_user_signature ;
bool* whc_hk_manage::c_inputIsOn;
bool whc_hk_manage::c_hk_service_isInit=false;
int whc_hk_manage::c_filter_idx=0;

// objet non terminé whc_report whc_hk_manage::c_report;

whc_hk_manage::whc_hk_manage()
{
    //ctor
    c_nbr++;
}

whc_hk_manage::whc_hk_manage(whc_hk_apply fonctionality, whc_hk_input signature)
{
    //ctor
    m_fonctionality = fonctionality ;
    m_signature = signature;
    c_nbr++;
}

whc_hk_manage::~whc_hk_manage()
{
    //dtor
    c_nbr--;
}

void whc_hk_manage::user_start_update_link(int val)
{
    c_hk_user_update_isOn=true;
    c_hk_user_hasSelect_applyId=val;
}

int whc_hk_manage::collect()
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

        bool hotkey_signature_isAllowed = true ;

        // shortcut : pas de signature avec pavé num simple ou shift
        // ni tab ni backspace ni enter
        if (not(c_user_signature.ctrl() || c_user_signature.alt()))
        {
            switch (tmp_scancode)
            {
            case KEY_TAB:
            case KEY_BACKSPACE:
            case KEY_ENTER:
            case KEY_ENTER_PAD:
            case KEY_DEL_PAD: // numeric pad
            case KEY_PLUS_PAD:
            case KEY_MINUS_PAD:
            case KEY_SLASH_PAD:
            case KEY_ASTERISK:
            case KEY_0_PAD:
            case KEY_1_PAD:
            case KEY_2_PAD:
            case KEY_3_PAD:
            case KEY_4_PAD:
            case KEY_5_PAD:
            case KEY_6_PAD:
            case KEY_7_PAD:
            case KEY_8_PAD:
            case KEY_9_PAD:
            case KEY_0:
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
                hotkey_signature_isAllowed = false ;
                break;
            default:
                break;
            }
        }

        if (c_inputIsOn && hotkey_signature_isAllowed && c_hk_service_isInit) //no command language input is on, and not reserve signature an service is proprely initiate
        {
            if (not(tmp_scancode == KEY_ESC)) //pas de raccourci clavier si Esc ou si input
            {
                if(c_hk_user_hasSelect_applyId >0) // c_hk_user_hasSelect_applyId = l'utilisateur a sélectionné une fonction pour lui associer une nouvelle hotkey
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
                        updateFilter(c_filter_idx);
                        c_hk_user_madeChanges=true;   // pour faire apparaître le save button
                    }
                    else   //la hotkey choisie par l'ulisateur est déjà associée à une autre fonction : demander confirmation de l'association
                    {
                        c_user_other_func_allready_link_to_hotkey = fctlink ;
                        c_hk_user_hasToConfirmChoice = true ;
                    }
                }
                else //pas de fonction a asocier à une hotkey
                {
                    user_redefine_hk_link_init() ;
                    return shortcutprocess(isreadkey);
                }
            }
            else //ESC
            {
                if(c_hk_user_hasSelect_applyId >0)
                {
                    //abandon définition
                    user_redefine_hk_link_init() ;
                    return -1 ; //isreadkey was used - not to be used by command language
                }
            }
        }
        return isreadkey ;
    }
    else return -1 ; //no isreadkey - nothing to be used by command language

}

int whc_hk_manage::shortcutprocess(int isreadkey)
{
    //search if signature is known in subscription list
    whc_hk_apply fctlink = search_fct(c_user_signature);
    if (fctlink.id()>0)
    {
        void (*fctptr)(void);       /*déclaration du pointeur*/
        fctptr = fctlink.processOnHotkey();   /*Initialisation*/
        if (fctptr!=nullptr)
        {
            fctptr();  /* Execution de la méthode */
        }
        whc_hk_input neutre ;
        c_user_signature = neutre ;
        return -1 ;
    }
    else
        return isreadkey;
}

whc_hk_apply whc_hk_manage::search_fct(whc_hk_input signature)
{
    int i = c_list.size();

    while (i>0)
    {
        i--;
        whc_hk_apply list_fonctionality ;
        whc_hk_input list_signature ;
        whc_hk_manage* hotkey;
        hotkey = &whc_hk_manage::c_list[i];
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

void whc_hk_manage::connect_fct(int fctid, ptrMthd fctptr)
{
    int i = c_list.size();

    while (i>0)
    {
        i--;
        whc_hk_manage* hotkey ;
        hotkey = &whc_hk_manage::c_list[i] ;
        whc_hk_apply fonctionality ;
        whc_hk_input signature ;
        fonctionality = hotkey->fonctionality() ;
        signature = hotkey->signature() ;

        if (fonctionality.id()==fctid)
        {
            fonctionality.SetprocessOnHotkey(fctptr);
            whc_hk_manage::c_list[i].Setfonctionality(fonctionality);
            //whc_hk_manage::c_list[i].Setsignature(signature);
            i=0;
        }
    }
}

void whc_hk_manage::init(std::string fic_name)
{
    std::vector<whc_hk_manage> clear_list;
    c_list.swap(clear_list);
// sqlite3   if (fic_name.substr(fic_name.size() - 3) == ".db")
//    {
//        load_db(fic_name);
//    }
//    else
    {
        load(fic_name);
    }
}

void whc_hk_manage::load(std::string fic_name)
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
                c_list.push_back(whc_hk_manage(fonctionality, signature));
            }
        }
        c_hk_service_isInit=true;
        fic_stream.close();
    }
}

void whc_hk_manage::save(std::string fic_name)
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
                whc_hk_manage* hotkey;
                hotkey = &whc_hk_manage::c_list[idx_forward];
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

void whc_hk_manage::link_fct_hk(int fctid, whc_hk_input signature)
{
    int idx_back = c_list.size();

    while (idx_back>0)
    {
        idx_back--;
        whc_hk_manage* hotkey ;
        hotkey = &whc_hk_manage::c_list[idx_back] ;
        whc_hk_apply fonctionality ;
        fonctionality = hotkey->fonctionality() ;

        if (fonctionality.id()==fctid)
        {
            whc_hk_manage::c_list[idx_back].Setsignature(signature);
            idx_back=0;
        }
    }
}

void whc_hk_manage::replace_link_fct_hk()
{
    bool oldisclear = false ;
    bool newisset = false ;

    int idx_back = c_list.size();

    while (idx_back>0)
    {
        idx_back--;
        whc_hk_manage* hotkey ;
        hotkey = &whc_hk_manage::c_list[idx_back] ;
        whc_hk_apply fonctionality ;
        fonctionality = hotkey->fonctionality() ;

        if (fonctionality.id()==c_hk_user_hasSelect_applyId)
        {
            whc_hk_manage::c_list[idx_back].Setsignature(c_user_signature);  //set new link
            newisset = true;
            if (oldisclear) idx_back=0; //both action done
        }

        if (fonctionality.id()==c_user_other_func_allready_link_to_hotkey.id())
        {
            whc_hk_input null_signature;
            whc_hk_manage::c_list[idx_back].Setsignature(null_signature); //clear old link
            oldisclear = true;
            if (newisset) idx_back=0;  //both action done
        }
    }

	c_hk_user_madeChanges=true;
    user_redefine_hk_link_init();
}

void whc_hk_manage::user_redefine_hk_link_init()
{
    whc_hk_apply null_fct ;

    c_hk_user_hasSelect_applyId   = -1 ;    // fonctionality->id()
    c_hk_user_hasToConfirmChoice = false ; // on demande confirmation, si signature déjà attribuée à une autre fonction
    c_user_other_func_allready_link_to_hotkey = null_fct ;
    c_hk_user_update_isOn	= false;
    //surtout pas réinit c_user_signature
}

// sqlite3
//void whc_hk_manage::load_db(std::string fic_name)
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

int whc_hk_manage::read_db_row(void *NotUsed, int row_nbr_col, char **row_data_col, char **db_ColName)
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
        c_list.push_back(whc_hk_manage(fonctionality, signature));


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

void whc_hk_manage::updateFilter(int tab_idx)
{
	c_catlist.clear();
	c_filter_idx=tab_idx;

	int nbr_category = 6;
    std::vector <char*> filter (nbr_category);
    filter[0]= "Global functions";
    filter[1]= "Transverse commands";
    filter[2]= "Channels";
    filter[3]= "CueList and memories";
    filter[4]= "Patch";
    filter[5]= "VideoTracking";

    if(not(c_filter_idx<nbr_category)){c_filter_idx=0;}

    int idx_back = c_list.size();
	while (idx_back>0)
	{
		idx_back--;
		whc_hk_manage* hotkey ;
		hotkey = &whc_hk_manage::c_list[idx_back] ;
		whc_hk_apply fonctionality ;
		fonctionality = hotkey->fonctionality() ;

		if (fonctionality.module()==filter[c_filter_idx])
		{
			c_catlist.push_back(c_list[idx_back]);
		}
	}
	if (c_catlist.size()>0)
	{
		std::reverse(c_catlist.begin(),c_catlist.end());
	}
}
