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

* \file hotkey_config_tab.cpp
* \brief {hotkeys service tab configuration - gui draw & logic}
* \author Rui Serge Azevedo Brooks
* \version {0.8.9}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*
*	Fonctions du panneau de configuration "hotkeys" (dessine le panneau, gérer les actions souris & clavier)
*
*/

#include <whc_hk_connector.h>
#include <whc_toolbox.h>

void loadfile_config_hotkey(std::string file_name)
{
    hk_manager.init(file_name) ;
}

void save_config_hotkey()
{
    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\whc_hotkey_user.txt";

    hk_manager.save(user_file);
}

/** \brief l'utilisateur à choisit une fonction a déclencher par un raccourci de son choix
 * : on remplece l'ancien raccourci par le nouveau
 *
 * \return void
 *
 */
void replace_config_hotkey()
{
    hk_manager.replace_link_fct_hk();
	hk_manager.updateFilter(); // recharge la liste pour l'affichage des fonctions de la catégorie choisie
	// si onglet des Bangers : récupérer les noms
	do_refresh_banger_catlist();
}

void hotkey_esc_button_press()
{
    simulate_keypress(KEY_ESC);
    hk_manager.reset_user_choice();
}

void draw_logical_button(int insidePox_X, int insidePos_Y, int label_width, int button_hight, int text_to_border_X, int text_to_border_Y, std::string button_label, bool hasfocus)
{

    Rect Cadre_button_label( Vec2D((insidePox_X),(insidePos_Y)),Vec2D(label_width,button_hight));
    Cadre_button_label.SetRoundness(7.5);
    Cadre_button_label.Draw(CouleurFond.WithAlpha(0.5));

    if(hasfocus) // <<-------------------- FOCUS is ON
    {
        if(mouse_x>(insidePox_X)
                && mouse_x<(insidePox_X + label_width)
                && mouse_y>(insidePos_Y)
                && mouse_y<(insidePos_Y + button_hight) )
        {
            Cadre_button_label.DrawOutline(CouleurLevel);
            Cadre_button_label.Draw(CouleurSurvol);

// Traitement selon la typologie de la fonction logique
//            if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
//            {
//                fctToFire();
//                mouseClicLeft.SetProcessed();
//            }
        }
    }
    petitchiffre.Print( button_label,(insidePox_X+text_to_border_X), (insidePos_Y + button_hight - text_to_border_Y),label_width-2*text_to_border_X,CENTER);
}

//Définition avec argument supp : la fonction à déclencher - fonction de type void non_fonction ()
void draw_logical_button(int insidePox_X, int insidePos_Y, int label_width, int button_hight, int text_to_border_X, int text_to_border_Y, std::string button_label, bool hasfocus, ptrMthd fctToFire)
{

//appel a la fonction générique qui n'a pas en dernier argument la fonction a déclencher
    draw_logical_button(insidePox_X, insidePos_Y, label_width, button_hight, text_to_border_X, text_to_border_Y, button_label, hasfocus);

    if(hasfocus) // <<-------------------- FOCUS is ON
    {
        if(mouse_x>(insidePox_X)
                && mouse_x<(insidePox_X + label_width)
                && mouse_y>(insidePos_Y)
                && mouse_y<(insidePos_Y + button_hight) )
        {
            if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
            {
                fctToFire();
                mouseClicLeft.SetProcessed();
            }
        }
    }
}

//Définition avec argument supp : la fonction à déclencher - fonction de type void non_fonction (string)
void draw_logical_button(int insidePox_X, int insidePos_Y, int label_width, int button_hight, int text_to_border_X, int text_to_border_Y, std::string button_label, bool hasfocus, ptrMthd_string fctToFire, std::string file_name)
{

//appel a la fonction générique qui n'a pas en dernier argument la fonction a déclencher
    draw_logical_button(insidePox_X, insidePos_Y, label_width, button_hight, text_to_border_X, text_to_border_Y, button_label, hasfocus);

    if(hasfocus) // <<-------------------- FOCUS is ON
    {
        if(mouse_x>(insidePox_X)
                && mouse_x<(insidePox_X + label_width)
                && mouse_y>(insidePos_Y)
                && mouse_y<(insidePos_Y + button_hight) )
        {
            if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
            {
                fctToFire(file_name);
                mouseClicLeft.SetProcessed();
            }
        }
    }
}

void draw_logical_hotkey_config_inactive (int cfg_X,int cfg_Y )
{

    std::string last_keyinput = "Last key input : " + hk_manager.c_user_signature.wording();
    neuromoyen.Print(last_keyinput,	cfg_X+largeurCFGwindow -20 - 14 * last_keyinput.size(),	cfg_Y+ 30, 14 * last_keyinput.size(),	RIGHT);

    int panel_start_x = cfg_X + 240;
    int panel_start_y = cfg_Y + 80;
    int panel_largeur = largeurCFGwindow-260;

    neuro.Print("User's hotkey service is inactive",									panel_start_x,	panel_start_y, 		panel_largeur, RIGHT);

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\whc_hotkey_user.txt" ; // ou .db si sqlite3 implanté
    std::string strd_file  = path + "\\ressources\\whc_hotkey_standard.txt"  ;

    if ((not tool.fileexist(user_file)) && (not tool.fileexist(strd_file)))
    {

        neuromoyen.Print(" It needs standard definition file or your definition file : ",	panel_start_x,	panel_start_y + 30 , panel_largeur, RIGHT);
        neuromoyen.Print("  \\ressources\\whc_hotkey_standard.txt",								panel_start_x,	panel_start_y + 50 , panel_largeur, RIGHT);
        neuromoyen.Print("  \\user\\whc_hotkey_user.txt",										panel_start_x,	panel_start_y + 70 , panel_largeur, RIGHT);
    }
    else // un des deux fichiers a été mis en place
    {

        std::string file_name;
        std::string load_button_label ;

        if(tool.fileexist(user_file))
        {
            file_name = user_file ;
            load_button_label = "Load user's definition file" ;
        }
        else //(tool.fileexist(strd_file)
        {
            file_name = strd_file;
            load_button_label = "Load standard definition file" ;
        }
        //Lien pour lire les fichiers
        int load_button_hauteur = 20 ;
        int load_button_bord_x = 5 ;
        int load_button_bord_y = 5 ;
        int load_button_largeur = load_button_label.size()*10 + 2*load_button_bord_x ;
        int load_button_pos_X = panel_start_x + panel_largeur - load_button_largeur - 10;
        int load_button_pos_Y = panel_start_y + 30;

        draw_logical_button(load_button_pos_X, load_button_pos_Y,
                            load_button_largeur, load_button_hauteur, load_button_bord_x, load_button_bord_y, load_button_label,
                            (window_focus_id==W_CFGMENU && index_config_tab_hotkeys==true), &loadfile_config_hotkey, file_name ); // hk_manager.init(strd_file) ;

    }


}

void draw_logical_hotkey_config_update (int cfg_X,int cfg_Y )
{
    Rgba gray( 0.5, 0.5, 0.5 );
    Rect Cadre_msg( Vec2D ( cfg_X , cfg_Y ),
                    Vec2D ( largeurCFGwindow, hauteurCFGwindow));
    Cadre_msg.SetRoundness(7.5);
    Cadre_msg.Draw(gray.WithAlpha(0.5));

    int panel_horizon = cfg_Y + hauteurCFGwindow/2 ;
    int panel_start_x = cfg_X + 250;
    int panel_largeur = largeurCFGwindow-250;
    int panel_middle = cfg_X + panel_largeur/2 ;


    neuro.Print("Input an hotkey for : " + hk_manager.current_choice_fct_description(),					panel_start_x,	panel_horizon - 72, panel_largeur, CENTER);
    neuro.Print("Current hotkey  : " + hk_manager.current_choice_fct_accessible_with (),				panel_start_x,	panel_horizon - 30, panel_largeur, CENTER);
    neuromoyen.Print("Last valide input will be nominate (some hotkey are not allowed - see the wiki)",	panel_start_x,	panel_horizon - 05, panel_largeur, CENTER);
    if (hk_manager.waiting_user_confirmation_on_a_choice())
    {
        neuro.Print("This hotkey " + hk_manager.c_user_signature.wording(),										panel_start_x,	panel_horizon + 25, panel_largeur, CENTER);
        neuro.Print("is allready asign to " + hk_manager.other_func_allready_link_to_hotkey(),			panel_start_x,	panel_horizon + 45, panel_largeur, CENTER);

        //Lien pour forcer la mise à jour
        std::string replace_button_label = "Unset previous and Set new" ; // "Replace anyway";
        int replace_button_hauteur = 20 ;
        int replace_button_bord_x = 5 ;
        int replace_button_bord_y = 5 ;
        int replace_button_largeur = replace_button_label.size()*10 + 2*replace_button_bord_x ;
        int replace_button_pos_X = panel_middle - replace_button_largeur/2;
        int replace_button_pos_Y = panel_horizon + 75;

        draw_logical_button(replace_button_pos_X, replace_button_pos_Y,
                            replace_button_largeur, replace_button_hauteur, replace_button_bord_x, replace_button_bord_y, replace_button_label,
                            (window_focus_id==W_CFGMENU && index_config_tab_hotkeys==true), &replace_config_hotkey);

    }
    {
        //Lien pour déclencher ESC
        std::string ESC_button_label = "ESC to abort" ;
        int ESC_button_hauteur = 20 ;
        int ESC_button_bord_x = 5 ;
        int ESC_button_bord_y = 5 ;
        int ESC_button_largeur = ESC_button_label.size()*10 + 2*ESC_button_bord_x ;
        int ESC_button_pos_X = cfg_X + largeurCFGwindow - ESC_button_largeur - 15;
        int ESC_button_pos_Y = cfg_Y + 15 ;

        draw_logical_button(ESC_button_pos_X, ESC_button_pos_Y,
                            ESC_button_largeur, ESC_button_hauteur, ESC_button_bord_x, ESC_button_bord_y, ESC_button_label,
                            (window_focus_id==W_CFGMENU && index_config_tab_hotkeys==true), &hotkey_esc_button_press);

    }
}

void do_hotkey_config_liste_pagination (int cfg_X,int cfg_Y)
{

    if (hk_manager.hk_user_madeChanges())   //
    {
        std::string tmp_label 	= "Save cfg" ;
        int tmp_size 			= tmp_label.size() * 10 ;
        draw_logical_button((cfg_X + largeurCFGwindow - tmp_size - 15 ), (cfg_Y + hauteurCFGwindow - 110 ),
                            tmp_size, 20, 5, 5,
                            tmp_label, (window_focus_id==W_CFGMENU && index_config_tab_hotkeys==true), &save_config_hotkey);
    }
    // flèche vers le haut
    if (num_page_list_hotkeys>0)
    {
        int fleche_pointe_x = cfg_X + largeurCFGwindow - 50 ;
        int fleche_pointe_y = cfg_Y + hauteurCFGwindow - 60 ;

        if (mouse_x		>	fleche_pointe_x
                && mouse_x	< 	(fleche_pointe_x + 20)
                && mouse_y	> 	(fleche_pointe_y - 20)
                && mouse_y 	< 	(fleche_pointe_y ))
        {
            Rect Cadre_ligne(	Vec2D (	fleche_pointe_x,
                                        fleche_pointe_y),
                                Vec2D ( 20, -20));
            Cadre_ligne.Draw(CouleurSurvol);
            if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed()
                    && window_focus_id==W_CFGMENU
                    && index_config_tab_hotkeys==true)
            {
                num_page_list_hotkeys--;
                if (num_page_list_hotkeys<0)
                {
                    num_page_list_hotkeys=0;
                }
                mouseClicLeft.SetProcessed();
            }
        }

        std::vector< Vec2D > vertices ;
        vertices.push_back(Vec2D (	fleche_pointe_x, fleche_pointe_y ));
        vertices.push_back(Vec2D (	fleche_pointe_x+20, fleche_pointe_y+0 ));
        vertices.push_back(Vec2D (	fleche_pointe_x+10, fleche_pointe_y-20 ));
        vertices.push_back(Vec2D (	fleche_pointe_x, fleche_pointe_y ));

        Poly fleche_haut(vertices);
        fleche_haut.Draw(CouleurLigne);
    }

    //numéros de page
    int max_page_visu=(int)ceil(hk_manager.c_catlist.size()/10)+1;
    int num_page_visu=num_page_list_hotkeys+1;

    std::string pagination = whc_toolbox::int_to_string(num_page_visu) +" / "+ whc_toolbox::int_to_string(max_page_visu);
    petitpetitchiffre.Print(pagination,	cfg_X + largeurCFGwindow - 60, cfg_Y + hauteurCFGwindow - 50, 40, CENTER);


    // flèche vers le bas
    if (num_page_list_hotkeys<max_page_visu-1)
    {
        int fleche_pointe_x = cfg_X + largeurCFGwindow - 50 ;
        int fleche_pointe_y = cfg_Y + hauteurCFGwindow - 45 ;

        if (mouse_x		>	fleche_pointe_x
                && mouse_x	< 	(fleche_pointe_x + 20)
                && mouse_y	> 	(fleche_pointe_y)
                && mouse_y 	< 	(fleche_pointe_y + 20))
        {
            Rect Cadre_ligne(	Vec2D (	fleche_pointe_x,
                                        fleche_pointe_y),
                                Vec2D ( 20, 20));
            Cadre_ligne.Draw(CouleurSurvol);
            if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed()
                    && window_focus_id==W_CFGMENU
                    && index_config_tab_hotkeys==true)
            {
                num_page_list_hotkeys++;
                if (num_page_list_hotkeys >= max_page_visu)
                {
                    num_page_list_hotkeys=max_page_visu-1;
                }
                mouseClicLeft.SetProcessed();
            }
        }

        std::vector< Vec2D > vertices ;
        vertices.push_back(Vec2D (	fleche_pointe_x, fleche_pointe_y ));
        vertices.push_back(Vec2D (	fleche_pointe_x+10, fleche_pointe_y+20 ));
        vertices.push_back(Vec2D (	fleche_pointe_x+20, fleche_pointe_y+0 ));
        vertices.push_back(Vec2D (	fleche_pointe_x, fleche_pointe_y ));

        Poly fleche_haut(vertices);
        fleche_haut.Draw(CouleurLigne);
    }

}

void do_refresh_banger_catlist()
{
	// TODO : sur changement du nom de Banger
	if (hk_manager.c_catlist.size()>0)
	{
		std::string triggers_module = hk_manager.c_catlist.at(0).fonctionality().module();
		if (triggers_module=="Bangers")
		{
			for (int num_ligne; num_ligne < hk_manager.c_catlist.size(); num_ligne++ )
			{
				int banger_num = -1;
				std::string triggers_name = hk_manager.c_catlist.at(num_ligne).fonctionality().description();
				std::string banger_name = triggers_name ;

				std::vector<std::string> tokens = whc_toolbox::split_string(triggers_name.substr(0,triggers_name.size()),' ');
				if (tokens.size()>0)
				{
					if (tokens[0]=="Bang")  //dans le fichier de déclaration
					{
//						try {
							banger_num = whc_toolbox::string_to_int(tokens[1]);
							if (banger_num <=bangers_number_of)
							{
								std::string tmp (bangers_name [banger_num-1]) ;
								banger_name = triggers_name + " ( " + whc_toolbox::trim(tmp) + ")";
							}
//						}
//						catch (const std::overflow_error& e) {
//							 std::cout << "hotkey config nom des bangers (1) : "; //
//							 std::cout << e.what();
//						} catch (const std::runtime_error& e) {
//							std::cout << "hotkey config nom des bangers (2) : "; //
//							std::cout << e.what();
//						} catch (const std::exception& e) {
//							std::cout << "hotkey config nom des bangers (3) : "; //
//							std::cout << e.what();
//						} catch (...) {
//							std::cout << "hotkey config nom des bangers (4) : "; //
//						}
					}
				}

				if (banger_num > 0)
				{
					hk_manager.changeDescription(&hk_manager.c_catlist.at(num_ligne), banger_name);
				}
			}
		}
	}

}

void do_hotkey_config_liste (int cfg_X,int cfg_Y)
{
    std::string last_keyinput = "Last key input : " + hk_manager.c_user_signature.wording();
    neuromoyen.Print(last_keyinput,	cfg_X+largeurCFGwindow -20 - 14 * last_keyinput.size(),	cfg_Y+ 30, 14 * last_keyinput.size(),	RIGHT);

    std::string trigger_fired = "Trigger fired : " + hk_manager.c_trigger_fired.description();
    neuromoyen.Print(trigger_fired,	cfg_X+largeurCFGwindow -20 - 14 * trigger_fired.size(),	cfg_Y+ 45, 14 * trigger_fired.size(),	RIGHT);

    int nbr_hk = hk_manager.c_catlist.size();
    //Canvas::SetClipping( cfg_X, cfg_Y, largeurCFGwindow, hauteurCFGwindow - 35);

    int deb_liste_ligne = num_page_list_hotkeys * 10;
    int fin_liste_ligne = deb_liste_ligne + 10 ;
    if  (fin_liste_ligne > nbr_hk)
    {
        fin_liste_ligne=nbr_hk;
    }

    for (int num_ligne=deb_liste_ligne; num_ligne<fin_liste_ligne; num_ligne++)
    {
        int num_ligne_visu = num_ligne - deb_liste_ligne;

        if (mouse_x		>	(cfg_X+ 150)
                && mouse_x	< 	(cfg_X+ 150+375)
                && mouse_y	> 	(cfg_Y+ 70 + num_ligne_visu * 20 - 10)
                && mouse_y 	< 	(cfg_Y+ 70 + num_ligne_visu * 20 + 10))
        {
            Rect Cadre_ligne(	Vec2D (	cfg_X+ 150,
                                        cfg_Y+ 70 + num_ligne_visu * 20 - 15),
                                Vec2D ( 380, 20));
            Cadre_ligne.SetRoundness(7.5);
            Cadre_ligne.Draw(CouleurSurvol);

            if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed()
                    && window_focus_id==W_CFGMENU
                    && index_config_tab_hotkeys==true)
            {
                int visu_line_to_list_idx = num_ligne_visu + ((num_page_list_hotkeys) * 10);
                int update_hotkey_idx = hk_manager.c_catlist.at(visu_line_to_list_idx).fonctionality().id();
                hk_manager.user_start_update_link(update_hotkey_idx);
            }
        }

		// --- Spécial Banger --- DEB --
		// on le fait à chaque affichage : le faire juste au changement d'onglet ou nom
		//do_refresh_banger_catlist();
		// --- Spécial Banger --- FIN
		std::string triggers_name = hk_manager.c_catlist.at(num_ligne).fonctionality().description();
        petitpetitchiffre.Print(triggers_name,									cfg_X+ 150,	cfg_Y+ 70 + num_ligne_visu * 20, 375, RIGHT);
        neuromoyen.Print(hk_manager.c_catlist.at(num_ligne).signature().wording(),	cfg_X+ 555,	cfg_Y+ 70 + num_ligne_visu * 20);

    }
    //Canvas::DisableClipping();

    do_hotkey_config_liste_pagination(cfg_X, cfg_Y);
}

bool mouseOver_hotkey_config_tab(int cfg_X,int cfg_Y, int tabNum, int largeur_espace_onglet_au_bord, int largeur_onglet, int hauteur_espace_onglet_au_bord, int hauteur_onglet, int hauteur_espace_entre_onglet)
{
    return  (window_focus_id==W_CFGMENU
             && index_config_tab_hotkeys
             && mouse_x > window_cfgX + largeur_espace_onglet_au_bord
             && mouse_x < window_cfgX + largeur_espace_onglet_au_bord + largeur_onglet
             && mouse_y > window_cfgY + hauteur_espace_onglet_au_bord                  + (tabNum+1) * (hauteur_onglet + hauteur_espace_entre_onglet)
             && mouse_y < window_cfgY + hauteur_espace_onglet_au_bord + hauteur_onglet + (tabNum+1) * (hauteur_onglet + hauteur_espace_entre_onglet));
}

void draw_logical_hotkey_config_tab (int cfg_X,int cfg_Y)
{

    int largeur_onglet = 200 ;
    //int largeur_espace_entre_onglet= 0;

    //Variables globales : largeurCFGwindow, hauteurCFGwindow

    int hauteur_onglet( floor ( hauteurCFGwindow / (hk_manager.c_filter.size() -1) ) );
    hauteur_onglet = hauteur_onglet - 10;
    int hauteur_espace_entre_onglet = 0;

    int largeur_espace_onglet_au_bord = 8;
    int hauteur_espace_onglet_au_bord = 8;
    int hauteur_font = 12 ;
    int largeur_texte_au_bord  = 5;
    int hauteur_texte_au_bord  = (hauteur_onglet / 2) + (hauteur_font / 2) ;

    for (int tab_idx=0; tab_idx < hk_manager.c_filter.size(); tab_idx++)
    {

        Rect Cadre_Onglet(Vec2D ( cfg_X + largeur_espace_onglet_au_bord,
                                  cfg_Y + hauteur_espace_onglet_au_bord + tab_idx * (hauteur_onglet + hauteur_espace_entre_onglet)),
                          Vec2D ( largeur_onglet, hauteur_onglet));
        Cadre_Onglet.SetRoundness(7.5);
        Cadre_Onglet.SetLineWidth(epaisseur_ligne_fader/2);
        Cadre_Onglet.DrawOutline(CouleurLigne);//CouleurBlind

        if(tab_idx==hk_manager.filterIdx())
        {
            Cadre_Onglet.Draw(CouleurConfig.WithAlpha(0.5));
        }
        else
        {
            Cadre_Onglet.Draw(CouleurBleuProcedure.WithAlpha(0.8));
        }

        if((hk_manager.hk_user_update_isOn()!=true) && // pas de mouse effect si en attente de saisie d'une hotkey pou redefinir le lien avec une fonction
                mouseOver_hotkey_config_tab(cfg_X, cfg_Y, tab_idx, largeur_espace_onglet_au_bord, largeur_onglet, hauteur_espace_onglet_au_bord, hauteur_onglet, hauteur_espace_entre_onglet))
        {
            if(tab_idx!=hk_manager.filterIdx())
            {
                Cadre_Onglet.Draw(CouleurSurvol);
            }
            if(mouseClicLeft.isDown()
                    && mouseClicLeft.isToBeProcessed()
                    && window_focus_id==W_CFGMENU
                    && index_config_tab_hotkeys)
            {
                for (int idx_reset=0; idx_reset < hk_manager.c_filter.size(); idx_reset++)
                {
                    index_active_tab_config_hotkeys.at(idx_reset)=false;
                    //idem index_active_tab_config_hotkeys[idx_reset] mais avec détéction de dépassement de capacitée

                }
                index_active_tab_config_hotkeys.at(tab_idx)=true;
                hk_manager.setfilterIdx(tab_idx);

                num_page_list_hotkeys=0; // la liste va être rechargée
                hk_manager.updateFilter(); // recharge la liste pour l'affichage des fonctions de la catégorie choisie

                // si onglet des Bangers : récupérer les noms
				do_refresh_banger_catlist();

				mouseClicLeft.SetProcessed();
            }
        }
        neuromoyen.Print(libelle_tab_config_hotkeys.at(tab_idx),
                         cfg_X + largeur_espace_onglet_au_bord + largeur_texte_au_bord,
                         cfg_Y + hauteur_espace_onglet_au_bord + hauteur_texte_au_bord + (tab_idx) * (hauteur_onglet + hauteur_espace_entre_onglet));

    }

	int detail_visuel=0;
	if (hk_manager.filterIdx()>0){detail_visuel=1; } // ajustement d'un pixel sur les onglets en dehors du 1er
    Rect Cadre_List(	Vec2D ( (cfg_X + largeur_espace_onglet_au_bord + ((largeur_onglet/3)*2)), //pour recouvrir droite des onglets
                                (cfg_Y + hauteur_espace_onglet_au_bord + detail_visuel)),
                        Vec2D ( largeurCFGwindow - (2 * largeur_espace_onglet_au_bord) - ((largeur_onglet/3)*2), //pour recouvrir droite des onglets
                                hauteurCFGwindow - (2 * hauteur_espace_onglet_au_bord) - 2 * detail_visuel));

    Cadre_List.SetRoundness(7.5);
    Cadre_List.SetLineWidth(epaisseur_ligne_fader/2);
    Cadre_List.DrawOutline(CouleurLigne);//CouleurBlind
    Cadre_List.Draw(CouleurConfig.WithAlpha(1));
//pour effacer la ligne entre le cadre et l'onglet actif
    Rect CleanLine( Vec2D ( cfg_X + largeur_espace_onglet_au_bord + (largeur_onglet/2),
							cfg_Y + hauteur_espace_onglet_au_bord + hk_manager.filterIdx() * (hauteur_onglet + hauteur_espace_entre_onglet)),
					Vec2D ( largeur_onglet, hauteur_onglet - epaisseur_ligne_fader/2 ) );
    CleanLine.Draw(CouleurConfig.WithAlpha(1));
}

void do_hotkey_config (int cfg_X,int cfg_Y)
{
    draw_logical_hotkey_config_tab( cfg_X,cfg_Y);

    if (hk_manager.hk_user_update_isOn()==true)
    {
        draw_logical_hotkey_config_update (cfg_X,cfg_Y);
    }
    else if (not hk_manager.hk_service_isInit())
    {
        draw_logical_hotkey_config_inactive (cfg_X,cfg_Y);
    }
    else
    {
        do_hotkey_config_liste( cfg_X,cfg_Y);
    }
}


