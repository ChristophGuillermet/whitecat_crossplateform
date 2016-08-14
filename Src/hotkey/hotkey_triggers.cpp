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

* \file hotkey_triggers.cpp
* \brief {hotkeys service - globals actions that can be trigger if linked to a hotkey}
* \author Rui Serge Azevedo Brooks
* \version {0.8.9}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*
*	Toutes les fonctions déclenchables par une hotkey si liées - fonction de connection - fonction de chargement du fichier des définitions
*
*/

#include "hotkey_triggers.h"
#include "whc_toolbox.h"
#include <windows.h>

void hotkey_assign_to_save() //01 Sauvegarde générale - Quick save
{
    if(index_is_saving==0)
    {
        index_save_global_is=1;
        index_do_quick_save=1;
    }

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\whc_hotkey_user.txt";

    hk_manager.save(user_file);
}

void hotkey_assign_to_save_and_quit() //02  Quitter avec sauvegarde - Quit and save
{
    index_ask_confirm=1;
    index_do_quit_with_save=1;
    index_do_quit_without_save=0;

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\whc_hotkey_user.txt";

    hk_manager.save(user_file);
}

void hotkey_assign_to_quit() //03 Quitter sans sauvegarde - Quit without save
{
    for (int i=0; i<12; i++)
    {
        specify_who_to_save_load[i]=0;
    }
    reset_save_load_report_string();
    index_ask_confirm=1;
    index_do_quit_without_save=1;
}

void hotkey_assign_to_snapshot_close_windows() //04 Snapshot et extinction des fenêtres - Snapshot and closing windows [SHIFT][PRINT SCREEN]
{
    snapshot_windows();
    close_all_windows();
}

void hotkey_assign_to_snapshot_open_windows() //05 Rappel du Snapshot des fenêtres - Recall windows snapshot [CTRL][PRINT SCREEN]
{
    recall_windows();
}

void hotkey_assign_to_cycle_forward_open_windows() //06 Circulation dans les principales fenêtres - Cycle forward thru open windows	[PGUP]
{
    sprintf(string_key_id,list_keyname[0]);
    back_window_push_to_front();
}

void hotkey_assign_to_cycle_backward_open_windows() //07 Circulation dans les principales fenêtres - Cycle backward thru open windows [PGDOWN]
{
    sprintf(string_key_id,list_keyname[0]);
    front_window_push_to_back();
}

void hotkey_assign_to_open_forward_solo_windows() //08 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]
{
    pos_focus_window=window_focus_id;
    substract_a_window(pos_focus_window);
    if(pos_focus_window<900)
    {
        pos_focus_window=899;
    }
    pos_focus_window++;
    if(pos_focus_window>max_window_identity_is)
    {
        pos_focus_window=900;
    }
    add_a_window(pos_focus_window);
}

void hotkey_assign_to_open_backward_solo_windows() //09 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]
{
    pos_focus_window=window_focus_id;
    substract_a_window(pos_focus_window);
    pos_focus_window--;
    if(pos_focus_window<900)
    {
        pos_focus_window=max_window_identity_is;
    }
    if(pos_focus_window>max_window_identity_is)
    {
        pos_focus_window=900;
    }
    add_a_window(pos_focus_window);
}

void hotkey_assign_to_Store_mode() // 10;Transverse commands;Store mode;0;0;0;47;[F1]
{
    index_do_report=0;
    index_do_modify=0;
    index_main_clear=0;
    index_do_dock=toggle(index_do_dock);

    switch (window_focus_id)
    {
    case W_CHASERS:
        index_affect_chaser_to_dock=index_do_dock;
        break;
    case W_GRID:
        for(int i=0; i<4; i++)
        {
            if(index_show_grid_player[i]==1)
            {
                gridplayer_to_affect_is=i;
                break;
            }
        }
        break;
    case W_MOVER:
        index_affect_to_dock_mover=index_do_dock;
        break;
    case W_DRAW:
        index_affect_draw_to_dock=index_do_dock;
        break;
    case W_ECHO:
        index_affect_echo_to_dock=index_do_dock;
        break;
    case W_TIME:
        index_affect_time=index_do_dock;
        break;
    case W_TRACKINGVIDEO:
        index_affect_video_tracking_to_dock=index_do_dock;
        break;
    case W_TRICHROMY:
        index_affect_color_to_dock=index_do_dock;
        break;
    case W_AUDIO:
        index_affect_audio_to_dock=index_do_dock;
        player_to_affect_to_dock=0;
        audio_type_for_dock_affectation_is=0;
        break;
    case W_CFGMENU:
        if(config_page_is==1)
        {
            index_affect_dmxin=index_do_dock;
        }
        else if(config_page_is==3)
        {
            index_do_affect_net_to_dock=index_do_dock;
        }
        break;
    default:
        break;
    }
}

void hotkey_assign_to_Modify_mode() // 11;Transverse commands;Modify mode;0;0;0;48;[F2]
{
    index_do_dock=0;
    index_do_report=0;
    index_main_clear=0;
    index_do_modify=toggle(index_do_modify);
}

void hotkey_assign_to_Report_mode() //12;Transverse commands;Report mode;0;0;0;49;[F3]
{
    index_do_dock=0;
    index_do_modify=0;
    index_main_clear=0;
    index_do_report=toggle(index_do_report);
}

void hotkey_assign_to_Clear_mode() //13;Transverse commands;Clear Mode;0;0;0;50;[F4]
{
    index_do_dock=0;
    index_do_modify=0;
    index_do_report=0;
    index_main_clear=toggle(index_main_clear);
}

void hotkey_assign_to_Name() //14;Transverse commands;Name (key input zone);0;0;0;51;[F5]
{
    index_type=toggle(index_type);
    strcpy(numeric,"");
    keyboardStorage_numeric_postext=0;
}

void hotkey_assign_to_Time()  //15;Transverse commands;Time;0;0;0;52;[F6]
{
    if(index_time==0)
    {
        add_a_window(W_TIME);
    }
    else
    {
        substract_a_window(W_TIME);
    }
}

void hotkey_assign_to_Trichromy() //16;Transverse commands;Trichromy;0;0;0;53;[F7]
{
    if(index_trichro_window==0)
    {
        add_a_window(W_TRICHROMY);
    }
    else
    {
        substract_a_window(W_TRICHROMY);
    }
}

void hotkey_assign_to_Video_Tracking() //17;Transverse commands;Video Tracking;0;0;0;54;[F8]
{
    if(index_video_window==0)
    {
        add_a_window(W_TRACKINGVIDEO);
    }
    else
    {
        substract_a_window(W_TRACKINGVIDEO);
    }
}

void hotkey_assign_to_CueList() //18;Transverse commands;CueList;0;0;0;55;[F9]
{
    if(index_window_sequentiel==0)
    {
        add_a_window(W_SEQUENCIEL);
    }
    else
    {
        substract_a_window(W_SEQUENCIEL);
    }
}

void hotkey_assign_to_Faders() //19;Transverse commands;Faders;0;0;0;56;[F10]
{
    if(index_show_faders==0)
    {
        add_a_window(W_FADERS);
    }
    else
    {
        substract_a_window(W_FADERS);
    }
}

void hotkey_assign_to_MiniFaders() //20;Transverse commands;MiniFaders;1;0;0;56;[SHIFT]+[F10]
{
    if(index_show_minifaders==0)
    {
        add_a_window(W_MINIFADERS);
    }
    else
    {
        substract_a_window(W_MINIFADERS);
    }
}

void hotkey_assign_to_Banger() //21;Transverse commands;Banger;0;0;0;57;[F11]
{
    if(index_show_banger_window==0)
    {
        add_a_window(W_BANGER);
        mouse_level_for_event=mouse_z;
        mouse_level_for_banger=mouse_z;
    }
    else
    {
        substract_a_window(W_BANGER);
    }
}

void hotkey_assign_to_Blind_mode() //22;Transverse commands;Blind mode;0;1;0;57;[CTRL]+[F11]
{
    index_blind=toggle(index_blind);
}

void hotkey_assign_to_CFG_Menu() //23;Transverse commands;CFG Menu;1;0;0;57;[SHIFT]+[F11]
{
    if(index_show_config_window==0)
    {
        add_a_window(W_CFGMENU);
    }
    else
    {
        substract_a_window(W_CFGMENU);
    }
}

void hotkey_assign_to_Chasers() //24;Transverse commands;Chasers;1;0;0;3;[SHIFT]+[C]
{
    if(index_window_chasers==0)
    {
        add_a_window(W_CHASERS);
    }
    else
    {
        substract_a_window(W_CHASERS);
    }
}

void hotkey_assign_to_Mover() //25;Transverse commands;Mover;1;0;0;105;[SHIFT]+[M]
{
    if(index_show_mover_window==0)
    {
        add_a_window(W_MOVER);
    }
    else
    {
        substract_a_window(W_MOVER);
    }
}

void hotkey_assign_to_selectedAllChannels() //26;Channels;selected all channels;0;0;0;25;[Y]
{
	key_select_all();
}

void hotkey_assign_to_unselectedChannels() //27;Channels;unselected channels;0;0;0;21;[U]
{
	key_select_inv();
}

void hotkey_assign_to_movingSelectionLeft() //28;Channels;moving selection (left);0;0;0;82;[<-]
{
	key_left();
}

void hotkey_assign_to_movingSelectionRight() //29;Channels;moving selection (right);0;0;0;83;[->]
{
	key_right();
}

void hotkey_assign_to_fullLevel() //30;Channels;Full level (for the selection);0;0;0;9;[I]
{
			key_full();
}

void hotkey_assign_to_levelToZero() //31;Channels;Level to Zero (for the selection);0;0;0;15;[O]
{
			key_at_zero();

}

void hotkey_assign_to_plusPercentForTheSelection() //32;Channels;plus % (for the selection);0;0;0;84;[ARROW UP]
{
            key_up();
}

void hotkey_assign_to_minusPercentForTheSelection() //33;Channels;minus % (for the selection);0;0;0;85;[ARROW DOWN]
{
            key_down();
}


void whc_hotkeys_init(std::string user_dir_file, std::string ressources_dir_file)
{

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\" + user_dir_file; // ou .db si sqlite3 implanté
    std::string strd_file  = path + "\\ressources\\" + ressources_dir_file;

    if (tool.fileexist(user_file))
    {
        hk_manager.init(user_file) ;
    }
    else hk_manager.init(strd_file) ;

    hk_manager.link_keyFocusIndicator(index_type);


    hk_manager.connect_fct(1,&hotkey_assign_to_save);
    hk_manager.connect_fct(2,&hotkey_assign_to_save_and_quit);
    hk_manager.connect_fct(3,&hotkey_assign_to_quit);
    hk_manager.connect_fct(4,&hotkey_assign_to_snapshot_close_windows);
    hk_manager.connect_fct(5,&hotkey_assign_to_snapshot_open_windows);
    hk_manager.connect_fct(6,&hotkey_assign_to_cycle_forward_open_windows);
    hk_manager.connect_fct(7,&hotkey_assign_to_cycle_backward_open_windows);
    hk_manager.connect_fct(8,&hotkey_assign_to_open_forward_solo_windows);
    hk_manager.connect_fct(9,&hotkey_assign_to_open_backward_solo_windows);
    hk_manager.connect_fct(10,&hotkey_assign_to_Store_mode);
    hk_manager.connect_fct(11,&hotkey_assign_to_Modify_mode);
    hk_manager.connect_fct(12,&hotkey_assign_to_Report_mode);
    hk_manager.connect_fct(13,&hotkey_assign_to_Clear_mode);
    hk_manager.connect_fct(14,&hotkey_assign_to_Name);
    hk_manager.connect_fct(15,&hotkey_assign_to_Time);
    hk_manager.connect_fct(16,&hotkey_assign_to_Trichromy);
    hk_manager.connect_fct(17,&hotkey_assign_to_Video_Tracking);
    hk_manager.connect_fct(18,&hotkey_assign_to_CueList);
    hk_manager.connect_fct(19,&hotkey_assign_to_Faders);
    hk_manager.connect_fct(20,&hotkey_assign_to_MiniFaders);
    hk_manager.connect_fct(21,&hotkey_assign_to_Banger);
    hk_manager.connect_fct(22,&hotkey_assign_to_Blind_mode);
    hk_manager.connect_fct(23,&hotkey_assign_to_CFG_Menu);
    hk_manager.connect_fct(24,&hotkey_assign_to_Chasers);
    hk_manager.connect_fct(25,&hotkey_assign_to_Mover);
    hk_manager.connect_fct(26,&hotkey_assign_to_selectedAllChannels);
	hk_manager.connect_fct(27,&hotkey_assign_to_unselectedChannels);
	hk_manager.connect_fct(28,&hotkey_assign_to_movingSelectionLeft);
	hk_manager.connect_fct(29,&hotkey_assign_to_movingSelectionRight);
	hk_manager.connect_fct(30,&hotkey_assign_to_fullLevel);
	hk_manager.connect_fct(31,&hotkey_assign_to_levelToZero);
	hk_manager.connect_fct(32,&hotkey_assign_to_plusPercentForTheSelection); //32;Channels;plus % (for the selection);0;0;0;84;[ARROW UP]
	hk_manager.connect_fct(33,&hotkey_assign_to_minusPercentForTheSelection); //33;Channels;minus % (for the selection);0;0;0;85;[ARROW DOWN]



	// !! - déclarer la fonction dans le header correspondant
}
