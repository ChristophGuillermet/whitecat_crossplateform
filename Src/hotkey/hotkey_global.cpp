#include "hotkey_global.h"
#include "whc_toolbox.h"
#include <windows.h>

void whc_hk_save() //01 Sauvegarde générale - Quick save
{
    if(index_is_saving==0)
    {
        index_save_global_is=1;
        index_do_quick_save=1;
    }

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\hotkey_user.whc";

    hk_manager.save(user_file);
}

void whc_hk_save_and_quit() //02  Quitter avec sauvegarde - Quit and save
{
    index_ask_confirm=1;
    index_do_quit_with_save=1;
    index_do_quit_without_save=0;

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\hotkey_user.whc";

    hk_manager.save(user_file);
}

void whc_hk_quit() //03 Quitter sans sauvegarde - Quit without save
{
    for (int i=0; i<12; i++)
    {
        specify_who_to_save_load[i]=0;
    }
    reset_save_load_report_string();
    index_ask_confirm=1;
    index_do_quit_without_save=1;
}

void whc_hk_snapshot_close_windows() //04 Snapshot et extinction des fenêtres - Snapshot and closing windows [SHIFT][PRINT SCREEN]
{
    snapshot_windows();
    close_all_windows();
}

void whc_hk_snapshot_open_windows() //05 Rappel du Snapshot des fenêtres - Recall windows snapshot [CTRL][PRINT SCREEN]
{
    recall_windows();
}

void whc_hk_cycle_forward_open_windows() //06 Circulation dans les principales fenêtres - Cycle forward thru open windows	[PGUP]
{
    sprintf(string_key_id,list_keyname[0]);
    back_window_push_to_front();
}

void whc_hk_cycle_backward_open_windows() //07 Circulation dans les principales fenêtres - Cycle backward thru open windows [PGDOWN]
{
    sprintf(string_key_id,list_keyname[0]);
    front_window_push_to_back();
}

void whc_hk_open_forward_solo_windows() //08 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]
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

void whc_hk_open_backward_solo_windows() //09 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]
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

void whc_hk_Store_mode() // 10;Transverse commands;Store mode;0;0;0;47;[F1]
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

void whc_hk_Modify_mode() // 11;Transverse commands;Modify mode;0;0;0;48;[F2]
{
    index_do_dock=0;
    index_do_report=0;
    index_main_clear=0;
    index_do_modify=toggle(index_do_modify);
}

void whc_hk_Report_mode() //12;Transverse commands;Report mode;0;0;0;49;[F3]
{
    index_do_dock=0;
    index_do_modify=0;
    index_main_clear=0;
    index_do_report=toggle(index_do_report);
}

void whc_hk_Clear_mode() //13;Transverse commands;Clear Mode;0;0;0;50;[F4]
{
    index_do_dock=0;
    index_do_modify=0;
    index_do_report=0;
    index_main_clear=toggle(index_main_clear);
}

void whc_hk_Name() //14;Transverse commands;Name (key input zone);0;0;0;51;[F5]
{
    index_type=toggle(index_type);
    strcpy(numeric,"");
    keyboardStorage_numeric_postext=0;
}

void whc_hk_Time()  //15;Transverse commands;Time;0;0;0;52;[F6]
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

void whc_hk_Trichromy() //16;Transverse commands;Trichromy;0;0;0;53;[F7]
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

void whc_hk_Video_Tracking() //17;Transverse commands;Video Tracking;0;0;0;54;[F8]
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

void whc_hk_CueList() //18;Transverse commands;CueList;0;0;0;55;[F9]
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

void whc_hk_Faders() //19;Transverse commands;Faders;0;0;0;56;[F10]
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

void whc_hk_MiniFaders() //20;Transverse commands;MiniFaders;1;0;0;56;[SHIFT]+[F10]
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

void whc_hk_Banger() //21;Transverse commands;Banger;0;0;0;57;[F11]
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

void whc_hk_Blind_mode() //22;Transverse commands;Blind mode;0;1;0;57;[CTRL]+[F11]
{
    index_blind=toggle(index_blind);
}

void whc_hk_CFG_Menu() //23;Transverse commands;CFG Menu;1;0;0;57;[SHIFT]+[F11]
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

void whc_hk_Chasers() //24;Transverse commands;Chasers;1;0;0;3;[SHIFT]+[C]
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

void whc_hk_Mover() //25;Transverse commands;Mover;1;0;0;105;[SHIFT]+[M]
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

void whc_hk_main_init()
{

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\hotkey_user.whc";
    std::string init_file  = path + "\\ressources\\hotkey_init.whc";

    if (tool.fileexist(user_file))
    {
        hk_manager.init(user_file) ;
    }
    else hk_manager.init(init_file) ;

    hk_manager.link_keyFocusIndicator(index_type);
    //hk_manager.link_reportManager(???);

    hk_manager.connect_fct(1,&whc_hk_save);
    hk_manager.connect_fct(2,&whc_hk_save_and_quit);
    hk_manager.connect_fct(3,&whc_hk_quit);
    hk_manager.connect_fct(4,&whc_hk_snapshot_close_windows);
    hk_manager.connect_fct(5,&whc_hk_snapshot_open_windows);
    hk_manager.connect_fct(6,&whc_hk_cycle_forward_open_windows);
    hk_manager.connect_fct(7,&whc_hk_cycle_backward_open_windows);
    hk_manager.connect_fct(8,&whc_hk_open_forward_solo_windows);
    hk_manager.connect_fct(9,&whc_hk_open_backward_solo_windows);
    hk_manager.connect_fct(10,&whc_hk_Store_mode);
    hk_manager.connect_fct(11,&whc_hk_Modify_mode);
    hk_manager.connect_fct(12,&whc_hk_Report_mode);
    hk_manager.connect_fct(13,&whc_hk_Clear_mode);
    hk_manager.connect_fct(14,&whc_hk_Name);
    hk_manager.connect_fct(15,&whc_hk_Time);
    hk_manager.connect_fct(16,&whc_hk_Trichromy);
    hk_manager.connect_fct(17,&whc_hk_Video_Tracking);
    hk_manager.connect_fct(18,&whc_hk_CueList);
    hk_manager.connect_fct(19,&whc_hk_Faders);
    hk_manager.connect_fct(20,&whc_hk_MiniFaders);
    hk_manager.connect_fct(21,&whc_hk_Banger);
    hk_manager.connect_fct(22,&whc_hk_Blind_mode);
    hk_manager.connect_fct(23,&whc_hk_CFG_Menu);
    hk_manager.connect_fct(24,&whc_hk_Chasers);
    hk_manager.connect_fct(25,&whc_hk_Mover);
}
