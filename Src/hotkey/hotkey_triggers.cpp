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
* \version {0.8.6}
* \date {14/08/2016}

 White Cat - gui - keyboard - hotkeys

*
*	Toutes les fonctions déclenchables par une hotkey si liées - fonction de connection - fonction de chargement du fichier des définitions
*
*/

#include "hotkey_triggers.h"
#include "whc_toolbox.h"
#include "hotkey_std_keyboard.cpp"
#include <windows.h>
#include <iostream>
#include <vector>

void do_bang_trigger(int banger_number)
{
	int index_banger_selected = banger_number - 1 ;
	if 	(index_banger_selected < bangers_number_of)
	{
		        switch(miditable[0][734])
        {
			//midi report
        case 0:
            sprintf(thetypinfo,"Note");
            break;
        case 1:
            sprintf(thetypinfo,"Key On");
            break;
        case 2:
            sprintf(thetypinfo,"Key Off");
            break;
        case 4:
            sprintf(thetypinfo,"Ctrl Change");
            break;
        }
        sprintf(string_last_midi_id,"Bang It Button is Ch: %d Pitch: %d Typ: %s" , miditable[1][734],miditable[2][734],thetypinfo);
        if( Midi_Faders_Affectation_Type!=0 )//config midi
        {
            attribute_midi_solo_affectation(734,Midi_Faders_Affectation_Mode);
            mouseClicLeft.SetProcessed();
        }
        else
        {
            start_time_for_banger[index_banger_selected]=actual_time;
			//4 aout 2010 initalisation  un temps plus long par defaut pour faire partir mes évènements
            end_time_for_banger[index_banger_selected]=default_time_of_the_bang;
			//reset du banger concerné
            for (int o=0; o<6; o++) //reset des évènements
            {
                event_sended[index_banger_selected][o]=0;
                if(bangers_delay[index_banger_selected][o]>end_time_for_banger[index_banger_selected])
                {
                    end_time_for_banger[index_banger_selected]=bangers_delay[index_banger_selected][o];
                }
            }
            bang_is_sended[index_banger_selected]=0;//reset du bang sended is
        }
	}

    }


void hk_trigger_01_save() //01 Sauvegarde générale - Quick save
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

void hk_trigger_02_save_and_quit() //02  Quitter avec sauvegarde - Quit and save
{
    index_ask_confirm=1;
    index_do_quit_with_save=1;
    index_do_quit_without_save=0;

    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\whc_hotkey_user.txt";

    hk_manager.save(user_file);
}

void hk_trigger_03_quit() //03 Quitter sans sauvegarde - Quit without save
{
    for (int i=0; i<12; i++)
    {
        specify_who_to_save_load[i]=0;
    }
    reset_save_load_report_string();
    index_ask_confirm=1;
    index_do_quit_without_save=1;
}

void hk_trigger_04_snapshot_close_windows() //04 Snapshot et extinction des fenêtres - Snapshot and closing windows [SHIFT][PRINT SCREEN]
{
    snapshot_windows();
    close_all_windows();
}

void hk_trigger_05_snapshot_open_windows() //05 Rappel du Snapshot des fenêtres - Recall windows snapshot [CTRL][PRINT SCREEN]
{
    recall_windows();
}

void hk_trigger_06_cycle_forward_open_windows() //06 Circulation dans les principales fenêtres - Cycle forward thru open windows	[PGUP]
{
    sprintf(string_key_id,list_keyname[0]);
    back_window_push_to_front();
}

void hk_trigger_07_cycle_backward_open_windows() //07 Circulation dans les principales fenêtres - Cycle backward thru open windows [PGDOWN]
{
    sprintf(string_key_id,list_keyname[0]);
    front_window_push_to_back();
}

void hk_trigger_08_open_forward_solo_windows() //08 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]
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

void hk_trigger_09_open_backward_solo_windows() //09 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]
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

void hk_trigger_10_Store_mode() // 10;Transverse commands;Store mode;0;0;0;47;[F1]
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

void hk_trigger_11_Modify_mode() // 11;Transverse commands;Modify mode;0;0;0;48;[F2]
{
    index_do_dock=0;
    index_do_report=0;
    index_main_clear=0;
    index_do_modify=toggle(index_do_modify);
}

void hk_trigger_12_Report_mode() //12;Transverse commands;Report mode;0;0;0;49;[F3]
{
    index_do_dock=0;
    index_do_modify=0;
    index_main_clear=0;
    index_do_report=toggle(index_do_report);
}

void hk_trigger_13_Clear_mode() //13;Transverse commands;Clear Mode;0;0;0;50;[F4]
{
    index_do_dock=0;
    index_do_modify=0;
    index_do_report=0;
    index_main_clear=toggle(index_main_clear);
}

void hk_trigger_14_Name() //14;Transverse commands;Name (key input zone);0;0;0;51;[F5]
{
    index_type=toggle(index_type);
    keyboardStorage_numeric_postext=0;
    for (int idx=0; idx<sizeof(numeric); idx++)
	{
		numeric[idx]=0;
	}
    // Mise à jour de la variable d'affichage du contenu de la saisie clavier standard
    sprintf(string_numeric_entry,"<< %s",numeric);
}

void hk_trigger_15_Time()  //15;Transverse commands;Time;0;0;0;52;[F6]
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

void hk_trigger_16_Trichromy() //16;Transverse commands;Trichromy;0;0;0;53;[F7]
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

void hk_trigger_17_Video_Tracking() //17;Transverse commands;Video Tracking;0;0;0;54;[F8]
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

void hk_trigger_18_CueList() //18;Transverse commands;CueList;0;0;0;55;[F9]
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

void hk_trigger_19_Faders() //19;Transverse commands;Faders;0;0;0;56;[F10]
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

void hk_trigger_20_MiniFaders() //20;Transverse commands;MiniFaders;1;0;0;56;[SHIFT]+[F10]
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

void hk_trigger_21_Banger() //21;Transverse commands;Banger;0;0;0;57;[F11]
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

void hk_trigger_22_Blind_mode() //22;Transverse commands;Blind mode;0;1;0;57;[CTRL]+[F11]
{
    index_blind=toggle(index_blind);
}

void hk_trigger_23_CFG_Menu() //23;Transverse commands;CFG Menu;1;0;0;57;[SHIFT]+[F11]
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

void hk_trigger_24_Chasers() //24;Transverse commands;Chasers;1;0;0;3;[SHIFT]+[C]
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

void hk_trigger_25_Mover() //25;Transverse commands;Mover;1;0;0;105;[SHIFT]+[M]
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

void hk_trigger_26_selectedAllChannels() //26;Channels;selected all channels;0;0;0;25;[Y]
{

///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;

}

void hk_trigger_27_unselectedChannels() //27;Channels;unselected channels;0;0;0;21;[U]
{
	key_select_inv();
}

void hk_trigger_28_movingSelectionLeft() //28;Channels;moving selection (left);0;0;0;82;[<-]
{
	key_left();
}

void hk_trigger_29_movingSelectionRight() //29;Channels;moving selection (right);0;0;0;83;[->]
{
	key_right();
}

void hk_trigger_30_fullLevel() //30;Channels;Full level (for the selection);0;0;0;9;[I]
{
			key_full();
}

void hk_trigger_31_levelToZero() //31;Channels;Level to Zero (for the selection);0;0;0;15;[O]
{
			key_at_zero();

}

void hk_trigger_32_plusPercentForTheSelection() //32;Channels;plus % (for the selection);0;0;0;84;[ARROW UP]
{
            key_up();
}

void hk_trigger_33_minusPercentForTheSelection() //33;Channels;minus % (for the selection);0;0;0;85;[ARROW DOWN]
{
            key_down();
}
//
void hk_trigger_34_Check_Channel_left()     //34;Channels;Check Channel left;0;1;0;82;[CTRL]+[<-]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;

}
//
void hk_trigger_35_Check_Channel_right()     //35;Channels;Check Channel right;0;1;0;83;[CTRL]+[->]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;

}
//
void hk_trigger_36_Copy_to_the_Clipboard_Select_channels()     //36;Channels;Copy to the Clipboard Select channels;0;1;0;3;[CTRL]+[C]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;

}
//
void hk_trigger_37_Paste_channels_from_clipboard()     //37;Channels;Paste channels from clipboard;0;1;0;22;[CTRL]+[V]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;

}
//
void hk_trigger_38_Get_Import_channels_from_a_memory()     //38;Channels;Get (Import channels from a memory);0;1;0;7;[CTRL]+[G]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_39_Memory_recording_deleting___Create_or_over_record_a_memory_number()     //39;CueList and memories;Memory recording/deleting - Create or over record a memory number;1;0;0;47;[SHIFT]+[F1]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_40_Memory_recording_deleting___Create_memory_adding_the_faders()     //40;CueList and memories;Memory recording/deleting - Create memory adding the faders;1;0;0;49;[SHIFT]+[F3]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_41_Memory_recording_deleting___Delete_memory()     //41;CueList and memories;Memory recording/deleting - Delete memory;1;0;0;77;[SHIFT]+[F3]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_42_Memory_recording_deleting___Over_record_on_stage_or_blind()     //42;CueList and memories;Memory recording/deleting - Over record on stage or blind;0;1;0;47;[CTRL]+[F1]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_43_Memory_recording_deleting___Over_record_on_stage_or_blind_with_faders()     //43;CueList and memories;Memory recording/deleting - Over record on stage or blind with faders;0;1;0;49;[CTRL]+[F3]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_44_Memory_recording_deleting___Reload_a_memory()     //44;CueList and memories;Memory recording/deleting - Reload a memory;0;1;0;23;[CTRL]+[Z]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_45_Memory_recording_deleting___Reload_a_deleted_mem()     //45;CueList and memories;Memory recording/deleting - Reload a deleted mem;1;0;0;23;[SHIFT]+[Z]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_46_GET_level_of_selected_channels_from_memory()     //46;CueList and memories;GET level of selected channels from memory;0;1;0;7;[CTRL]+[G]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_47_Navigating_thru_memories___Previous_mem_on_stage()     //47;CueList and memories;Navigating thru memories - Previous mem on stage;0;1;0;26;[CTRL]+[W]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_48_Navigating_thru_memories___Next_mem_on_stage()     //48;CueList and memories;Navigating thru memories - Next mem on stage;0;1;0;24;[CTRL]+[X]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_49_Navigating_thru_memories___Previous_mem_on_preset()     //49;CueList and memories;Navigating thru memories - Previous mem on preset;1;0;0;26;[SHIFT]+[W]
{
///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_50_Navigating_thru_memories___Next_mem_on_preset()     //50;CueList and memories;Navigating thru memories - Next mem on preset;1;0;0;24;[SHIFT]+[X]
{
      ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_51_Crossfade_GO_PAUSE()     //51;CueList and memories;Crossfade GO/PAUSE;0;0;0;75;[SPACE]
{
      ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_52_Crossfade_GO_BACK()     //52;CueList and memories;Crossfade GO BACK;0;1;0;75;[CTRL]+[SPACE]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_53_Crossfade_DOUBLE_GO()     //53;CueList and memories;Crossfade DOUBLE GO;1;0;0;75;[SHIFT]+[SPACE]
{
  ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_54_Patch()     //54;Transverse commands;Patch;1;0;0;16;[SHIFT]+[P]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_55_Numpad()     //55;Transverse commands;Numpad;0;0;0;16;[P]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_56_Dimmers_selection___select_all_dimmers()     //56;Patch;Dimmers selection - select all dimmers;1;0;0;25;[SHIFT]+[Y]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_57_Dimmers_selection___unselect_all_dimmers()     //57;Patch;Dimmers selection - unselect all dimmers;1;0;0;21;[SHIFT]+[U]
{
   ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_58_Check_Dimmer___left()     //58;Patch;Check Dimmer - (left);1;0;0;82;[SHIFT]+[<-]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_59_Check_Dimmer___right()     //59;Patch;Check Dimmer - (right);1;0;0;83;[SHIFT]+[->]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_60_Select_Presets_1()     //60;VideoTracking;Select Presets 1;0;0;0;26;[W]
{
  ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_61_Select_Presets_2()     //61;VideoTracking;Select Presets 2;0;0;0;24;[X]
{
   ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_62_Select_Presets_3()     //62;VideoTracking;Select Presets 3;0;0;0;3;[C]
{
  ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_63_Select_Presets_4()     //63;VideoTracking;Select Presets 4;0;0;0;22;[V]
{
    ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_64_Select_Presets_5()     //64;VideoTracking;Select Presets 5;0;0;0;2;[B]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_65_Select_Presets_6()     //65;VideoTracking;Select Presets 6;0;0;0;14;[N]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_66_Select_roi_1()     //66;VideoTracking;Select roi 1;0;0;0;17;[A]
{
   ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_67_Select_roi_2()     //67;VideoTracking;Select roi 2;0;0;0;23;[Z]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_68_Select_roi_3()     //68;VideoTracking;Select roi 3;0;0;0;5;[E]
{
  ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_69_Select_roi_4()     //69;VideoTracking;Select roi 4;0;0;0;18;[R]
{
  ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_70_Select_roi_5()     //70;VideoTracking;Select roi 5;0;0;0;20;[T]
{
      ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_71_Select_roi_6()     //71;VideoTracking;Select roi 6;0;0;0;25;[Y]
{
   ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_72_Select_roi_7()     //72;VideoTracking;Select roi 7;0;0;0;1;[Q]
{
  ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_73_Select_roi_8()     //73;VideoTracking;Select roi 8;0;0;0;19;[S]
{
 ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_74_Select_roi_9()     //74;VideoTracking;Select roi 9;0;0;0;4;[D]
{
    ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_75_Select_roi_10()     //75;VideoTracking;Select roi 10;0;0;0;6;[F]
{
  ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_76_Select_roi_11()     //76;VideoTracking;Select roi 11;0;0;0;7;[G]
{
   ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_77_Select_roi_12()     //77;VideoTracking;Select roi 12;0;0;0;8;[H]
{
    ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   /// --- ///  TODO   ///
	sprintf(string_numeric_entry,"<< %s","HOTKEY TRIGGER A IMPLANTER");
	keyboardStorage_numeric_postext=25;
}
//
void hk_trigger_78_Bang_01()     //78;Bangers;Bang 01;0;0;0;0;--unset--
{
      do_bang_trigger(1);
}
//
void hk_trigger_79_Bang_02()     //79;Bangers;Bang 02;0;0;0;0;--unset--
{
      do_bang_trigger(2);
}
//
void hk_trigger_80_Bang_03()     //80;Bangers;Bang 03;0;0;0;0;--unset--
{
      do_bang_trigger(3);
}
//
void hk_trigger_81_Bang_04()     //81;Bangers;Bang 04;0;0;0;0;--unset--
{
      do_bang_trigger(4);
}
//
void hk_trigger_82_Bang_05()     //82;Bangers;Bang 05;0;0;0;0;--unset--
{
      do_bang_trigger(5);
}
//
void hk_trigger_83_Bang_06()     //83;Bangers;Bang 06;0;0;0;0;--unset--
{
      do_bang_trigger(6);
}
//
void hk_trigger_84_Bang_07()     //84;Bangers;Bang 07;0;0;0;0;--unset--
{
      do_bang_trigger(7);
}
//
void hk_trigger_85_Bang_08()     //85;Bangers;Bang 08;0;0;0;0;--unset--
{
      do_bang_trigger(8);
}
//
void hk_trigger_86_Bang_09()     //86;Bangers;Bang 09;0;0;0;0;--unset--
{
      do_bang_trigger(9);
}
//
void hk_trigger_87_Bang_10()     //87;Bangers;Bang 10;0;0;0;0;--unset--
{
      do_bang_trigger(10);
}
//
void hk_trigger_88_Bang_11()     //88;Bangers;Bang 11;0;0;0;0;--unset--
{
      do_bang_trigger(11);
}
//
void hk_trigger_89_Bang_12()     //89;Bangers;Bang 12;0;0;0;0;--unset--
{
      do_bang_trigger(12);
}
//
void hk_trigger_90_Bang_13()     //90;Bangers;Bang 13;0;0;0;0;--unset--
{
      do_bang_trigger(13);
}
//
void hk_trigger_91_Bang_14()     //91;Bangers;Bang 14;0;0;0;0;--unset--
{
      do_bang_trigger(14);
}
//
void hk_trigger_92_Bang_15()     //92;Bangers;Bang 15;0;0;0;0;--unset--
{
      do_bang_trigger(15);
}
//
void hk_trigger_93_Bang_16()     //93;Bangers;Bang 16;0;0;0;0;--unset--
{
      do_bang_trigger(16);
}
//
void hk_trigger_94_Bang_17()     //94;Bangers;Bang 17;0;0;0;0;--unset--
{
      do_bang_trigger(17);
}
//
void hk_trigger_95_Bang_18()     //95;Bangers;Bang 18;0;0;0;0;--unset--
{
      do_bang_trigger(18);
}
//
void hk_trigger_96_Bang_19()     //96;Bangers;Bang 19;0;0;0;0;--unset--
{
      do_bang_trigger(19);
}
//
void hk_trigger_97_Bang_20()     //97;Bangers;Bang 20;0;0;0;0;--unset--
{
      do_bang_trigger(20);
}
//
void hk_trigger_98_Bang_21()     //98;Bangers;Bang 21;0;0;0;0;--unset--
{
      do_bang_trigger(21);
}
//
void hk_trigger_99_Bang_22()     //99;Bangers;Bang 22;0;0;0;0;--unset--
{
      do_bang_trigger(22);
}
//
void hk_trigger_100_Bang_23()     //100;Bangers;Bang 23;0;0;0;0;--unset--
{
      do_bang_trigger(23);
}
//
void hk_trigger_101_Bang_24()     //101;Bangers;Bang 24;0;0;0;0;--unset--
{
      do_bang_trigger(24);
}
//
void hk_trigger_102_Bang_25()     //102;Bangers;Bang 25;0;0;0;0;--unset--
{
      do_bang_trigger(25);
}
//
void hk_trigger_103_Bang_26()     //103;Bangers;Bang 26;0;0;0;0;--unset--
{
      do_bang_trigger(26);
}
//
void hk_trigger_104_Bang_27()     //104;Bangers;Bang 27;0;0;0;0;--unset--
{
      do_bang_trigger(27);
}
//
void hk_trigger_105_Bang_28()     //105;Bangers;Bang 28;0;0;0;0;--unset--
{
      do_bang_trigger(28);
}
//
void hk_trigger_106_Bang_29()     //106;Bangers;Bang 29;0;0;0;0;--unset--
{
      do_bang_trigger(29);
}
//
void hk_trigger_107_Bang_30()     //107;Bangers;Bang 30;0;0;0;0;--unset--
{
      do_bang_trigger(30);
}
//
void hk_trigger_108_Bang_31()     //108;Bangers;Bang 31;0;0;0;0;--unset--
{
      do_bang_trigger(31);
}
//
void hk_trigger_109_Bang_32()     //109;Bangers;Bang 32;0;0;0;0;--unset--
{
      do_bang_trigger(32);
}
//
void hk_trigger_110_Bang_33()     //110;Bangers;Bang 33;0;0;0;0;--unset--
{
      do_bang_trigger(33);
}
//
void hk_trigger_111_Bang_34()     //111;Bangers;Bang 34;0;0;0;0;--unset--
{
      do_bang_trigger(34);
}
//
void hk_trigger_112_Bang_35()     //112;Bangers;Bang 35;0;0;0;0;--unset--
{
      do_bang_trigger(35);
}
//
void hk_trigger_113_Bang_36()     //113;Bangers;Bang 36;0;0;0;0;--unset--
{
      do_bang_trigger(36);
}
//
void hk_trigger_114_Bang_37()     //114;Bangers;Bang 37;0;0;0;0;--unset--
{
      do_bang_trigger(37);
}
//
void hk_trigger_115_Bang_38()     //115;Bangers;Bang 38;0;0;0;0;--unset--
{
      do_bang_trigger(38);
}
//
void hk_trigger_116_Bang_39()     //116;Bangers;Bang 39;0;0;0;0;--unset--
{
      do_bang_trigger(39);
}
//
void hk_trigger_117_Bang_40()     //117;Bangers;Bang 40;0;0;0;0;--unset--
{
      do_bang_trigger(40);
}
//
void hk_trigger_118_Bang_41()     //118;Bangers;Bang 41;0;0;0;0;--unset--
{
      do_bang_trigger(41);
}
//
void hk_trigger_119_Bang_42()     //119;Bangers;Bang 42;0;0;0;0;--unset--
{
      do_bang_trigger(42);
}
//
void hk_trigger_120_Bang_43()     //120;Bangers;Bang 43;0;0;0;0;--unset--
{
      do_bang_trigger(43);
}
//
void hk_trigger_121_Bang_44()     //121;Bangers;Bang 44;0;0;0;0;--unset--
{
      do_bang_trigger(44);
}
//
void hk_trigger_122_Bang_45()     //122;Bangers;Bang 45;0;0;0;0;--unset--
{
      do_bang_trigger(45);
}
//
void hk_trigger_123_Bang_46()     //123;Bangers;Bang 46;0;0;0;0;--unset--
{
      do_bang_trigger(46);
}
//
void hk_trigger_124_Bang_47()     //124;Bangers;Bang 47;0;0;0;0;--unset--
{
      do_bang_trigger(47);
}
//
void hk_trigger_125_Bang_48()     //125;Bangers;Bang 48;0;0;0;0;--unset--
{
      do_bang_trigger(48);
}
//
void hk_trigger_126_Bang_49()     //126;Bangers;Bang 49;0;0;0;0;--unset--
{
      do_bang_trigger(49);
}
//
void hk_trigger_127_Bang_50()     //127;Bangers;Bang 50;0;0;0;0;--unset--
{
      do_bang_trigger(50);
}
//
void hk_trigger_128_Bang_51()     //128;Bangers;Bang 51;0;0;0;0;--unset--
{
      do_bang_trigger(51);
}
//
void hk_trigger_129_Bang_52()     //129;Bangers;Bang 52;0;0;0;0;--unset--
{
      do_bang_trigger(52);
}
//
void hk_trigger_130_Bang_53()     //130;Bangers;Bang 53;0;0;0;0;--unset--
{
      do_bang_trigger(53);
}
//
void hk_trigger_131_Bang_54()     //131;Bangers;Bang 54;0;0;0;0;--unset--
{
      do_bang_trigger(54);
}
//
void hk_trigger_132_Bang_55()     //132;Bangers;Bang 55;0;0;0;0;--unset--
{
      do_bang_trigger(55);
}
//
void hk_trigger_133_Bang_56()     //133;Bangers;Bang 56;0;0;0;0;--unset--
{
      do_bang_trigger(56);
}
//
void hk_trigger_134_Bang_57()     //134;Bangers;Bang 57;0;0;0;0;--unset--
{
      do_bang_trigger(57);
}
//
void hk_trigger_135_Bang_58()     //135;Bangers;Bang 58;0;0;0;0;--unset--
{
      do_bang_trigger(58);
}
//
void hk_trigger_136_Bang_59()     //136;Bangers;Bang 59;0;0;0;0;--unset--
{
      do_bang_trigger(59);
}
//
void hk_trigger_137_Bang_60()     //137;Bangers;Bang 60;0;0;0;0;--unset--
{
      do_bang_trigger(60);
}
//
void hk_trigger_138_Bang_61()     //138;Bangers;Bang 61;0;0;0;0;--unset--
{
      do_bang_trigger(61);
}
//
void hk_trigger_139_Bang_62()     //139;Bangers;Bang 62;0;0;0;0;--unset--
{
      do_bang_trigger(62);
}
//
void hk_trigger_140_Bang_63()     //140;Bangers;Bang 63;0;0;0;0;--unset--
{
      do_bang_trigger(63);
}
//
void hk_trigger_141_Bang_64()     //141;Bangers;Bang 64;0;0;0;0;--unset--
{
      do_bang_trigger(64);
}
//
void hk_trigger_142_Bang_65()     //142;Bangers;Bang 65;0;0;0;0;--unset--
{
      do_bang_trigger(65);
}
//
void hk_trigger_143_Bang_66()     //143;Bangers;Bang 66;0;0;0;0;--unset--
{
      do_bang_trigger(66);
}
//
void hk_trigger_144_Bang_67()     //144;Bangers;Bang 67;0;0;0;0;--unset--
{
      do_bang_trigger(67);
}
//
void hk_trigger_145_Bang_68()     //145;Bangers;Bang 68;0;0;0;0;--unset--
{
      do_bang_trigger(68);
}
//
void hk_trigger_146_Bang_69()     //146;Bangers;Bang 69;0;0;0;0;--unset--
{
      do_bang_trigger(69);
}
//
void hk_trigger_147_Bang_70()     //147;Bangers;Bang 70;0;0;0;0;--unset--
{
      do_bang_trigger(70);
}
//
void hk_trigger_148_Bang_71()     //148;Bangers;Bang 71;0;0;0;0;--unset--
{
      do_bang_trigger(71);
}
//
void hk_trigger_149_Bang_72()     //149;Bangers;Bang 72;0;0;0;0;--unset--
{
      do_bang_trigger(72);
}
//
void hk_trigger_150_Bang_73()     //150;Bangers;Bang 73;0;0;0;0;--unset--
{
      do_bang_trigger(73);
}
//
void hk_trigger_151_Bang_74()     //151;Bangers;Bang 74;0;0;0;0;--unset--
{
      do_bang_trigger(74);
}
//
void hk_trigger_152_Bang_75()     //152;Bangers;Bang 75;0;0;0;0;--unset--
{
      do_bang_trigger(75);
}
//
void hk_trigger_153_Bang_76()     //153;Bangers;Bang 76;0;0;0;0;--unset--
{
      do_bang_trigger(76);
}
//
void hk_trigger_154_Bang_77()     //154;Bangers;Bang 77;0;0;0;0;--unset--
{
      do_bang_trigger(77);
}
//
void hk_trigger_155_Bang_78()     //155;Bangers;Bang 78;0;0;0;0;--unset--
{
      do_bang_trigger(78);
}
//
void hk_trigger_156_Bang_79()     //156;Bangers;Bang 79;0;0;0;0;--unset--
{
      do_bang_trigger(79);
}
//
void hk_trigger_157_Bang_80()     //157;Bangers;Bang 80;0;0;0;0;--unset--
{
      do_bang_trigger(80);
}
//
void hk_trigger_158_Bang_81()     //158;Bangers;Bang 81;0;0;0;0;--unset--
{
      do_bang_trigger(81);
}
//
void hk_trigger_159_Bang_82()     //159;Bangers;Bang 82;0;0;0;0;--unset--
{
      do_bang_trigger(82);
}
//
void hk_trigger_160_Bang_83()     //160;Bangers;Bang 83;0;0;0;0;--unset--
{
      do_bang_trigger(83);
}
//
void hk_trigger_161_Bang_84()     //161;Bangers;Bang 84;0;0;0;0;--unset--
{
      do_bang_trigger(84);
}
//
void hk_trigger_162_Bang_85()     //162;Bangers;Bang 85;0;0;0;0;--unset--
{
      do_bang_trigger(85);
}
//
void hk_trigger_163_Bang_86()     //163;Bangers;Bang 86;0;0;0;0;--unset--
{
      do_bang_trigger(86);
}
//
void hk_trigger_164_Bang_87()     //164;Bangers;Bang 87;0;0;0;0;--unset--
{
      do_bang_trigger(87);
}
//
void hk_trigger_165_Bang_88()     //165;Bangers;Bang 88;0;0;0;0;--unset--
{
      do_bang_trigger(88);
}
//
void hk_trigger_166_Bang_89()     //166;Bangers;Bang 89;0;0;0;0;--unset--
{
      do_bang_trigger(89);
}
//
void hk_trigger_167_Bang_90()     //167;Bangers;Bang 90;0;0;0;0;--unset--
{
      do_bang_trigger(90);
}
//
void hk_trigger_168_Bang_91()     //168;Bangers;Bang 91;0;0;0;0;--unset--
{
      do_bang_trigger(91);
}
//
void hk_trigger_169_Bang_92()     //169;Bangers;Bang 92;0;0;0;0;--unset--
{
      do_bang_trigger(92);
}
//
void hk_trigger_170_Bang_93()     //170;Bangers;Bang 93;0;0;0;0;--unset--
{
      do_bang_trigger(93);
}
//
void hk_trigger_171_Bang_94()     //171;Bangers;Bang 94;0;0;0;0;--unset--
{
      do_bang_trigger(94);
}
//
void hk_trigger_172_Bang_95()     //172;Bangers;Bang 95;0;0;0;0;--unset--
{
      do_bang_trigger(95);
}
//
void hk_trigger_173_Bang_96()     //173;Bangers;Bang 96;0;0;0;0;--unset--
{
      do_bang_trigger(96);
}
//
void hk_trigger_174_Bang_97()     //174;Bangers;Bang 97;0;0;0;0;--unset--
{
      do_bang_trigger(97);
}
//
void hk_trigger_175_Bang_98()     //175;Bangers;Bang 98;0;0;0;0;--unset--
{
      do_bang_trigger(98);
}
//
void hk_trigger_176_Bang_99()     //176;Bangers;Bang 99;0;0;0;0;--unset--
{
      do_bang_trigger(99);
}
//
void hk_trigger_177_Bang_100()     //177;Bangers;Bang 100;0;0;0;0;--unset--
{
      do_bang_trigger(100);
}
//
void hk_trigger_178_Bang_101()     //178;Bangers;Bang 101;0;0;0;0;--unset--
{
      do_bang_trigger(101);
}
//
void hk_trigger_179_Bang_102()     //179;Bangers;Bang 102;0;0;0;0;--unset--
{
      do_bang_trigger(102);
}
//
void hk_trigger_180_Bang_103()     //180;Bangers;Bang 103;0;0;0;0;--unset--
{
      do_bang_trigger(103);
}
//
void hk_trigger_181_Bang_104()     //181;Bangers;Bang 104;0;0;0;0;--unset--
{
      do_bang_trigger(104);
}
//
void hk_trigger_182_Bang_105()     //182;Bangers;Bang 105;0;0;0;0;--unset--
{
      do_bang_trigger(105);
}
//
void hk_trigger_183_Bang_106()     //183;Bangers;Bang 106;0;0;0;0;--unset--
{
      do_bang_trigger(106);
}
//
void hk_trigger_184_Bang_107()     //184;Bangers;Bang 107;0;0;0;0;--unset--
{
      do_bang_trigger(107);
}
//
void hk_trigger_185_Bang_108()     //185;Bangers;Bang 108;0;0;0;0;--unset--
{
      do_bang_trigger(108);
}
//
void hk_trigger_186_Bang_109()     //186;Bangers;Bang 109;0;0;0;0;--unset--
{
      do_bang_trigger(109);
}
//
void hk_trigger_187_Bang_110()     //187;Bangers;Bang 110;0;0;0;0;--unset--
{
      do_bang_trigger(110);
}
//
void hk_trigger_188_Bang_111()     //188;Bangers;Bang 111;0;0;0;0;--unset--
{
      do_bang_trigger(111);
}
//
void hk_trigger_189_Bang_112()     //189;Bangers;Bang 112;0;0;0;0;--unset--
{
      do_bang_trigger(112);
}
//
void hk_trigger_190_Bang_113()     //190;Bangers;Bang 113;0;0;0;0;--unset--
{
      do_bang_trigger(113);
}
//
void hk_trigger_191_Bang_114()     //191;Bangers;Bang 114;0;0;0;0;--unset--
{
      do_bang_trigger(114);
}
//
void hk_trigger_192_Bang_115()     //192;Bangers;Bang 115;0;0;0;0;--unset--
{
      do_bang_trigger(115);
}
//
void hk_trigger_193_Bang_116()     //193;Bangers;Bang 116;0;0;0;0;--unset--
{
      do_bang_trigger(116);
}
//
void hk_trigger_194_Bang_117()     //194;Bangers;Bang 117;0;0;0;0;--unset--
{
      do_bang_trigger(117);
}
//
void hk_trigger_195_Bang_118()     //195;Bangers;Bang 118;0;0;0;0;--unset--
{
      do_bang_trigger(118);
}
//
void hk_trigger_196_Bang_119()     //196;Bangers;Bang 119;0;0;0;0;--unset--
{
      do_bang_trigger(119);
}
//
void hk_trigger_197_Bang_120()     //197;Bangers;Bang 120;0;0;0;0;--unset--
{
      do_bang_trigger(120);
}
//
void hk_trigger_198_Bang_121()     //198;Bangers;Bang 121;0;0;0;0;--unset--
{
      do_bang_trigger(121);
}
//
void hk_trigger_199_Bang_122()     //199;Bangers;Bang 122;0;0;0;0;--unset--
{
      do_bang_trigger(122);
}
//
void hk_trigger_200_Bang_123()     //200;Bangers;Bang 123;0;0;0;0;--unset--
{
      do_bang_trigger(123);
}
//
void hk_trigger_201_Bang_124()     //201;Bangers;Bang 124;0;0;0;0;--unset--
{
      do_bang_trigger(124);
}
//
void hk_trigger_202_Bang_125()     //202;Bangers;Bang 125;0;0;0;0;--unset--
{
      do_bang_trigger(125);
}
//
void hk_trigger_203_Bang_126()     //203;Bangers;Bang 126;0;0;0;0;--unset--
{
      do_bang_trigger(126);
}
//
void hk_trigger_204_Bang_127()     //204;Bangers;Bang 127;0;0;0;0;--unset--
{
      do_bang_trigger(127);
}
//
void hk_trigger_205_Bang_128()     //205;Bangers;Bang 128;0;0;0;0;--unset--
{
      do_bang_trigger(128);
}
//
void hk_trigger_206_Bang_129()     //206;Bangers;Bang 129;0;0;0;0;--unset--
{
      do_bang_trigger(129);
}
//
void hk_trigger_207_Bang_130()     //207;Bangers;Bang 130;0;0;0;0;--unset--
{
      do_bang_trigger(130);
}
//
void hk_trigger_208_Bang_131()     //208;Bangers;Bang 131;0;0;0;0;--unset--
{
      do_bang_trigger(131);
}
//
void hk_trigger_209_Bang_132()     //209;Bangers;Bang 132;0;0;0;0;--unset--
{
      do_bang_trigger(132);
}
//
void hk_trigger_210_Bang_133()     //210;Bangers;Bang 133;0;0;0;0;--unset--
{
      do_bang_trigger(133);
}
//
void hk_trigger_211_Bang_134()     //211;Bangers;Bang 134;0;0;0;0;--unset--
{
      do_bang_trigger(134);
}
//
void hk_trigger_212_Bang_135()     //212;Bangers;Bang 135;0;0;0;0;--unset--
{
      do_bang_trigger(135);
}
//
void hk_trigger_213_Bang_136()     //213;Bangers;Bang 136;0;0;0;0;--unset--
{
      do_bang_trigger(136);
}
//
void hk_trigger_214_Bang_137()     //214;Bangers;Bang 137;0;0;0;0;--unset--
{
      do_bang_trigger(137);
}
//
void hk_trigger_215_Bang_138()     //215;Bangers;Bang 138;0;0;0;0;--unset--
{
      do_bang_trigger(138);
}
//
void hk_trigger_216_Bang_139()     //216;Bangers;Bang 139;0;0;0;0;--unset--
{
      do_bang_trigger(139);
}
//
void hk_trigger_217_Bang_140()     //217;Bangers;Bang 140;0;0;0;0;--unset--
{
      do_bang_trigger(140);
}
//
void hk_trigger_218_Bang_141()     //218;Bangers;Bang 141;0;0;0;0;--unset--
{
      do_bang_trigger(141);
}
//
void hk_trigger_219_Bang_142()     //219;Bangers;Bang 142;0;0;0;0;--unset--
{
      do_bang_trigger(142);
}
//
void hk_trigger_220_Bang_143()     //220;Bangers;Bang 143;0;0;0;0;--unset--
{
      do_bang_trigger(143);
}
//
void hk_trigger_221_Bang_144()     //221;Bangers;Bang 144;0;0;0;0;--unset--
{
      do_bang_trigger(144);
}
//
void hk_trigger_222_Bang_145()     //222;Bangers;Bang 145;0;0;0;0;--unset--
{
      do_bang_trigger(145);
}
//
void hk_trigger_223_Bang_146()     //223;Bangers;Bang 146;0;0;0;0;--unset--
{
      do_bang_trigger(146);
}
//
void hk_trigger_224_Bang_147()     //224;Bangers;Bang 147;0;0;0;0;--unset--
{
      do_bang_trigger(147);
}
//
void hk_trigger_225_Bang_148()     //225;Bangers;Bang 148;0;0;0;0;--unset--
{
      do_bang_trigger(148);
}
//
void hk_trigger_226_Bang_149()     //226;Bangers;Bang 149;0;0;0;0;--unset--
{
      do_bang_trigger(149);
}
//
void hk_trigger_227_Bang_150()     //227;Bangers;Bang 150;0;0;0;0;--unset--
{
      do_bang_trigger(150);
}
//
void hk_trigger_228_Bang_151()     //228;Bangers;Bang 151;0;0;0;0;--unset--
{
      do_bang_trigger(151);
}
//
void hk_trigger_229_Bang_152()     //229;Bangers;Bang 152;0;0;0;0;--unset--
{
      do_bang_trigger(152);
}
//
void hk_trigger_230_Bang_153()     //230;Bangers;Bang 153;0;0;0;0;--unset--
{
      do_bang_trigger(153);
}
//
void hk_trigger_231_Bang_154()     //231;Bangers;Bang 154;0;0;0;0;--unset--
{
      do_bang_trigger(154);
}
//
void hk_trigger_232_Bang_155()     //232;Bangers;Bang 155;0;0;0;0;--unset--
{
      do_bang_trigger(155);
}
//
void hk_trigger_233_Bang_156()     //233;Bangers;Bang 156;0;0;0;0;--unset--
{
      do_bang_trigger(156);
}
//
void hk_trigger_234_Bang_157()     //234;Bangers;Bang 157;0;0;0;0;--unset--
{
      do_bang_trigger(157);
}
//
void hk_trigger_235_Bang_158()     //235;Bangers;Bang 158;0;0;0;0;--unset--
{
      do_bang_trigger(158);
}
//
void hk_trigger_236_Bang_159()     //236;Bangers;Bang 159;0;0;0;0;--unset--
{
      do_bang_trigger(159);
}
//
void hk_trigger_237_Bang_160()     //237;Bangers;Bang 160;0;0;0;0;--unset--
{
      do_bang_trigger(160);
}
//
void hk_trigger_238_Bang_161()     //238;Bangers;Bang 161;0;0;0;0;--unset--
{
      do_bang_trigger(161);
}
//
void hk_trigger_239_Bang_162()     //239;Bangers;Bang 162;0;0;0;0;--unset--
{
      do_bang_trigger(162);
}
//
void hk_trigger_240_Bang_163()     //240;Bangers;Bang 163;0;0;0;0;--unset--
{
      do_bang_trigger(163);
}
//
void hk_trigger_241_Bang_164()     //241;Bangers;Bang 164;0;0;0;0;--unset--
{
      do_bang_trigger(164);
}
//
void hk_trigger_242_Bang_165()     //242;Bangers;Bang 165;0;0;0;0;--unset--
{
      do_bang_trigger(165);
}
//
void hk_trigger_243_Bang_166()     //243;Bangers;Bang 166;0;0;0;0;--unset--
{
      do_bang_trigger(166);
}
//
void hk_trigger_244_Bang_167()     //244;Bangers;Bang 167;0;0;0;0;--unset--
{
      do_bang_trigger(167);
}
//
void hk_trigger_245_Bang_168()     //245;Bangers;Bang 168;0;0;0;0;--unset--
{
      do_bang_trigger(168);
}
//
void hk_trigger_246_Bang_169()     //246;Bangers;Bang 169;0;0;0;0;--unset--
{
      do_bang_trigger(169);
}
//
void hk_trigger_247_Bang_170()     //247;Bangers;Bang 170;0;0;0;0;--unset--
{
      do_bang_trigger(170);
}
//
void hk_trigger_248_Bang_171()     //248;Bangers;Bang 171;0;0;0;0;--unset--
{
      do_bang_trigger(171);
}
//
void hk_trigger_249_Bang_172()     //249;Bangers;Bang 172;0;0;0;0;--unset--
{
      do_bang_trigger(172);
}
//
void hk_trigger_250_Bang_173()     //250;Bangers;Bang 173;0;0;0;0;--unset--
{
      do_bang_trigger(173);
}
//
void hk_trigger_251_Bang_174()     //251;Bangers;Bang 174;0;0;0;0;--unset--
{
      do_bang_trigger(174);
}
//
void hk_trigger_252_Bang_175()     //252;Bangers;Bang 175;0;0;0;0;--unset--
{
      do_bang_trigger(175);
}
//
void hk_trigger_253_Bang_176()     //253;Bangers;Bang 176;0;0;0;0;--unset--
{
      do_bang_trigger(176);
}
//
void hk_trigger_254_Bang_177()     //254;Bangers;Bang 177;0;0;0;0;--unset--
{
      do_bang_trigger(177);
}
//
void hk_trigger_255_Bang_178()     //255;Bangers;Bang 178;0;0;0;0;--unset--
{
      do_bang_trigger(178);
}
//
void hk_trigger_256_Bang_179()     //256;Bangers;Bang 179;0;0;0;0;--unset--
{
      do_bang_trigger(179);
}
//
void hk_trigger_257_Bang_180()     //257;Bangers;Bang 180;0;0;0;0;--unset--
{
      do_bang_trigger(180);
}
//
void hk_trigger_258_Bang_181()     //258;Bangers;Bang 181;0;0;0;0;--unset--
{
      do_bang_trigger(181);
}
//
void hk_trigger_259_Bang_182()     //259;Bangers;Bang 182;0;0;0;0;--unset--
{
      do_bang_trigger(182);
}
//
void hk_trigger_260_Bang_183()     //260;Bangers;Bang 183;0;0;0;0;--unset--
{
      do_bang_trigger(183);
}
//
void hk_trigger_261_Bang_184()     //261;Bangers;Bang 184;0;0;0;0;--unset--
{
      do_bang_trigger(184);
}
//
void hk_trigger_262_Bang_185()     //262;Bangers;Bang 185;0;0;0;0;--unset--
{
      do_bang_trigger(185);
}
//
void hk_trigger_263_Bang_186()     //263;Bangers;Bang 186;0;0;0;0;--unset--
{
      do_bang_trigger(186);
}
//
void hk_trigger_264_Bang_187()     //264;Bangers;Bang 187;0;0;0;0;--unset--
{
      do_bang_trigger(187);
}
//
void hk_trigger_265_Bang_188()     //265;Bangers;Bang 188;0;0;0;0;--unset--
{
      do_bang_trigger(188);
}
//
void hk_trigger_266_Bang_189()     //266;Bangers;Bang 189;0;0;0;0;--unset--
{
      do_bang_trigger(189);
}
//
void hk_trigger_267_Bang_190()     //267;Bangers;Bang 190;0;0;0;0;--unset--
{
      do_bang_trigger(190);
}
//
void hk_trigger_268_Bang_191()     //268;Bangers;Bang 191;0;0;0;0;--unset--
{
      do_bang_trigger(191);
}
//
void hk_trigger_269_Bang_192()     //269;Bangers;Bang 192;0;0;0;0;--unset--
{
      do_bang_trigger(192);
}
//
void hk_trigger_270_Bang_193()     //270;Bangers;Bang 193;0;0;0;0;--unset--
{
      do_bang_trigger(193);
}
//
void hk_trigger_271_Bang_194()     //271;Bangers;Bang 194;0;0;0;0;--unset--
{
      do_bang_trigger(194);
}
//
void hk_trigger_272_Bang_195()     //272;Bangers;Bang 195;0;0;0;0;--unset--
{
      do_bang_trigger(195);
}
//
void hk_trigger_273_Bang_196()     //273;Bangers;Bang 196;0;0;0;0;--unset--
{
      do_bang_trigger(196);
}
//
void hk_trigger_274_Bang_197()     //274;Bangers;Bang 197;0;0;0;0;--unset--
{
      do_bang_trigger(197);
}
//
void hk_trigger_275_Bang_198()     //275;Bangers;Bang 198;0;0;0;0;--unset--
{
      do_bang_trigger(198);
}
//
void hk_trigger_276_Bang_199()     //276;Bangers;Bang 199;0;0;0;0;--unset--
{
      do_bang_trigger(199);
}
//
void hk_trigger_277_Bang_200()     //277;Bangers;Bang 200;0;0;0;0;--unset--
{
      do_bang_trigger(200);
}
//
void hk_trigger_278_Bang_201()     //278;Bangers;Bang 201;0;0;0;0;--unset--
{
      do_bang_trigger(201);
}
//
void hk_trigger_279_Bang_202()     //279;Bangers;Bang 202;0;0;0;0;--unset--
{
      do_bang_trigger(202);
}
//
void hk_trigger_280_Bang_203()     //280;Bangers;Bang 203;0;0;0;0;--unset--
{
      do_bang_trigger(203);
}
//
void hk_trigger_281_Bang_204()     //281;Bangers;Bang 204;0;0;0;0;--unset--
{
      do_bang_trigger(204);
}
//
void hk_trigger_282_Bang_205()     //282;Bangers;Bang 205;0;0;0;0;--unset--
{
      do_bang_trigger(205);
}
//
void hk_trigger_283_Bang_206()     //283;Bangers;Bang 206;0;0;0;0;--unset--
{
      do_bang_trigger(206);
}
//
void hk_trigger_284_Bang_207()     //284;Bangers;Bang 207;0;0;0;0;--unset--
{
      do_bang_trigger(207);
}
//
void hk_trigger_285_Bang_208()     //285;Bangers;Bang 208;0;0;0;0;--unset--
{
      do_bang_trigger(208);
}
//
void hk_trigger_286_Bang_209()     //286;Bangers;Bang 209;0;0;0;0;--unset--
{
      do_bang_trigger(209);
}
//
void hk_trigger_287_Bang_210()     //287;Bangers;Bang 210;0;0;0;0;--unset--
{
      do_bang_trigger(210);
}
//
void hk_trigger_288_Bang_211()     //288;Bangers;Bang 211;0;0;0;0;--unset--
{
      do_bang_trigger(211);
}
//
void hk_trigger_289_Bang_212()     //289;Bangers;Bang 212;0;0;0;0;--unset--
{
      do_bang_trigger(212);
}
//
void hk_trigger_290_Bang_213()     //290;Bangers;Bang 213;0;0;0;0;--unset--
{
      do_bang_trigger(213);
}
//
void hk_trigger_291_Bang_214()     //291;Bangers;Bang 214;0;0;0;0;--unset--
{
      do_bang_trigger(214);
}
//
void hk_trigger_292_Bang_215()     //292;Bangers;Bang 215;0;0;0;0;--unset--
{
      do_bang_trigger(215);
}
//
void hk_trigger_293_Bang_216()     //293;Bangers;Bang 216;0;0;0;0;--unset--
{
      do_bang_trigger(216);
}
//
void hk_trigger_294_Bang_217()     //294;Bangers;Bang 217;0;0;0;0;--unset--
{
      do_bang_trigger(217);
}
//
void hk_trigger_295_Bang_218()     //295;Bangers;Bang 218;0;0;0;0;--unset--
{
      do_bang_trigger(218);
}
//
void hk_trigger_296_Bang_219()     //296;Bangers;Bang 219;0;0;0;0;--unset--
{
      do_bang_trigger(219);
}
//
void hk_trigger_297_Bang_220()     //297;Bangers;Bang 220;0;0;0;0;--unset--
{
      do_bang_trigger(220);
}
//
void hk_trigger_298_Bang_221()     //298;Bangers;Bang 221;0;0;0;0;--unset--
{
      do_bang_trigger(221);
}
//
void hk_trigger_299_Bang_222()     //299;Bangers;Bang 222;0;0;0;0;--unset--
{
      do_bang_trigger(222);
}
//
void hk_trigger_300_Bang_223()     //300;Bangers;Bang 223;0;0;0;0;--unset--
{
      do_bang_trigger(223);
}
//
void hk_trigger_301_Bang_224()     //301;Bangers;Bang 224;0;0;0;0;--unset--
{
      do_bang_trigger(224);
}
//
void hk_trigger_302_Bang_225()     //302;Bangers;Bang 225;0;0;0;0;--unset--
{
      do_bang_trigger(225);
}
//
void hk_trigger_303_Bang_226()     //303;Bangers;Bang 226;0;0;0;0;--unset--
{
      do_bang_trigger(226);
}
//
void hk_trigger_304_Bang_227()     //304;Bangers;Bang 227;0;0;0;0;--unset--
{
      do_bang_trigger(227);
}
//
void hk_trigger_305_Bang_228()     //305;Bangers;Bang 228;0;0;0;0;--unset--
{
      do_bang_trigger(228);
}
//
void hk_trigger_306_Bang_229()     //306;Bangers;Bang 229;0;0;0;0;--unset--
{
      do_bang_trigger(229);
}
//
void hk_trigger_307_Bang_230()     //307;Bangers;Bang 230;0;0;0;0;--unset--
{
      do_bang_trigger(230);
}
//
void hk_trigger_308_Bang_231()     //308;Bangers;Bang 231;0;0;0;0;--unset--
{
      do_bang_trigger(231);
}
//
void hk_trigger_309_Bang_232()     //309;Bangers;Bang 232;0;0;0;0;--unset--
{
      do_bang_trigger(232);
}
//
void hk_trigger_310_Bang_233()     //310;Bangers;Bang 233;0;0;0;0;--unset--
{
      do_bang_trigger(233);
}
//
void hk_trigger_311_Bang_234()     //311;Bangers;Bang 234;0;0;0;0;--unset--
{
      do_bang_trigger(234);
}
//
void hk_trigger_312_Bang_235()     //312;Bangers;Bang 235;0;0;0;0;--unset--
{
      do_bang_trigger(235);
}
//
void hk_trigger_313_Bang_236()     //313;Bangers;Bang 236;0;0;0;0;--unset--
{
      do_bang_trigger(236);
}
//
void hk_trigger_314_Bang_237()     //314;Bangers;Bang 237;0;0;0;0;--unset--
{
      do_bang_trigger(237);
}
//
void hk_trigger_315_Bang_238()     //315;Bangers;Bang 238;0;0;0;0;--unset--
{
      do_bang_trigger(238);
}
//
void hk_trigger_316_Bang_239()     //316;Bangers;Bang 239;0;0;0;0;--unset--
{
      do_bang_trigger(239);
}
//
void hk_trigger_317_Bang_240()     //317;Bangers;Bang 240;0;0;0;0;--unset--
{
      do_bang_trigger(240);
}
//
void hk_trigger_318_Bang_241()     //318;Bangers;Bang 241;0;0;0;0;--unset--
{
      do_bang_trigger(241);
}
//
void hk_trigger_319_Bang_242()     //319;Bangers;Bang 242;0;0;0;0;--unset--
{
      do_bang_trigger(242);
}
//
void hk_trigger_320_Bang_243()     //320;Bangers;Bang 243;0;0;0;0;--unset--
{
      do_bang_trigger(243);
}
//
void hk_trigger_321_Bang_244()     //321;Bangers;Bang 244;0;0;0;0;--unset--
{
      do_bang_trigger(244);
}
//
void hk_trigger_322_Bang_245()     //322;Bangers;Bang 245;0;0;0;0;--unset--
{
      do_bang_trigger(245);
}
//
void hk_trigger_323_Bang_246()     //323;Bangers;Bang 246;0;0;0;0;--unset--
{
      do_bang_trigger(246);
}
//
void hk_trigger_324_Bang_247()     //324;Bangers;Bang 247;0;0;0;0;--unset--
{
      do_bang_trigger(247);
}
//
void hk_trigger_325_Bang_248()     //325;Bangers;Bang 248;0;0;0;0;--unset--
{
      do_bang_trigger(248);
}
//
void hk_trigger_326_Bang_249()     //326;Bangers;Bang 249;0;0;0;0;--unset--
{
      do_bang_trigger(249);
}
//
void hk_trigger_327_Bang_250()     //327;Bangers;Bang 250;0;0;0;0;--unset--
{
      do_bang_trigger(250);
}
//
void hk_trigger_328_Bang_251()     //328;Bangers;Bang 251;0;0;0;0;--unset--
{
      do_bang_trigger(251);
}
//
void hk_trigger_329_Bang_252()     //329;Bangers;Bang 252;0;0;0;0;--unset--
{
      do_bang_trigger(252);
}
//
void hk_trigger_330_Bang_253()     //330;Bangers;Bang 253;0;0;0;0;--unset--
{
      do_bang_trigger(253);
}
//
void hk_trigger_331_Bang_254()     //331;Bangers;Bang 254;0;0;0;0;--unset--
{
      do_bang_trigger(254);
}
//
void hk_trigger_332_Bang_255()     //332;Bangers;Bang 255;0;0;0;0;--unset--
{
      do_bang_trigger(255);
}
//

void whc_hotkeys_init(std::string user_dir_file, std::string ressources_dir_file)
{


	// allegro specific
	//override_config_data ("keyboard=FR"); -- TODO définir le mappage des claviers US et FR dans des data

    // ATTENTION si la déclaration de index_type change il faut en faire de même avec son homonyme c_inputIsOn
    hk_manager.link_keyFocusIndicator(&index_type); // lie c_inputIsOn à index_type via l'adresses mémoire : pour connaitre l'état de index_type sans qu'il soit dans l'objet
    // index_type = la saisie numérique / NAME est active

	// Initilisation des filtres = catégories de la 2d colonne du fichier lu pour définir les hotkeys
	// doit être fait avant chargement du fichier pour permettre l'intialisation du filtrage de la liste
	hk_manager.c_filter.clear();
	hk_manager.c_filter.push_back("Global functions");
    hk_manager.c_filter.push_back("Transverse commands");
    hk_manager.c_filter.push_back("Channels");
    hk_manager.c_filter.push_back("CueList and memories");
    hk_manager.c_filter.push_back("Patch");
	hk_manager.c_filter.push_back("VideoTracking");
	hk_manager.c_filter.push_back("Bangers");
	//--- test --- on peut rajouter facilement une catégorie & onglet : hk_manager.c_filter.push_back("Bidon");

	// Limite double emplois - permet d'avoir des libellés plus courts pour l'affichage et d'autres plus "parlant" dans le fichier
	libelle_tab_config_hotkeys.push_back("Global");
    libelle_tab_config_hotkeys.push_back("Transverse");
    libelle_tab_config_hotkeys.push_back("Channels");
    libelle_tab_config_hotkeys.push_back("CueList");
    libelle_tab_config_hotkeys.push_back("Patch");
    libelle_tab_config_hotkeys.push_back("Video");
    libelle_tab_config_hotkeys.push_back("Banger");
    //--- test --- on peut rajouter facilement une catégorie & onglet : libelle_tab_config_hotkeys.push_back("bidon");
    //
    // tableau (vecteur) d'index qui permet de savoir quel onglet est affiché, tous init à faux
    index_active_tab_config_hotkeys.resize(libelle_tab_config_hotkeys.size(),false);
    index_active_tab_config_hotkeys.at(0)=true;  // 1er onglet à vrai pour qu'il s'affiche.
	//
    whc_toolbox tool;
    std::string path = tool.executablePath();
    std::string user_file  = path + "\\user\\" + user_dir_file; // ou .db si sqlite3 implanté
    std::string strd_file  = path + "\\ressources\\" + ressources_dir_file;
	// le fichier utilisateur est prioritaire
	// (le fichier spectacle le sera  plus )
	// TODO : possibilité de charger un fichier spécifique à un spectacle pour le maping des bangers
	// 			--> pb à la sauvegarde : il faut savoir si on enregistre pour le spectacle ou pour profil génrique utilisateur :
	//				passera par ajout d'un indicteur pour connaitre son chox  / case à cocher dans config à ajouter / suvegarde de ce choix
    if (tool.fileexist(user_file))
    {
        hk_manager.init(user_file) ;
    }
    else hk_manager.init(strd_file) ;
	//
    hk_manager.connect_fct(1,&hk_trigger_01_save);
    hk_manager.connect_fct(2,&hk_trigger_02_save_and_quit);
    hk_manager.connect_fct(3,&hk_trigger_03_quit);
    hk_manager.connect_fct(4,&hk_trigger_04_snapshot_close_windows);
    hk_manager.connect_fct(5,&hk_trigger_05_snapshot_open_windows);
    hk_manager.connect_fct(6,&hk_trigger_06_cycle_forward_open_windows);
    hk_manager.connect_fct(7,&hk_trigger_07_cycle_backward_open_windows);
    hk_manager.connect_fct(8,&hk_trigger_08_open_forward_solo_windows);
    hk_manager.connect_fct(9,&hk_trigger_09_open_backward_solo_windows);
    hk_manager.connect_fct(10,&hk_trigger_10_Store_mode);
    hk_manager.connect_fct(11,&hk_trigger_11_Modify_mode);
    hk_manager.connect_fct(12,&hk_trigger_12_Report_mode);
    hk_manager.connect_fct(13,&hk_trigger_13_Clear_mode);
    hk_manager.connect_fct(14,&hk_trigger_14_Name);
    hk_manager.connect_fct(15,&hk_trigger_15_Time);
    hk_manager.connect_fct(16,&hk_trigger_16_Trichromy);
    hk_manager.connect_fct(17,&hk_trigger_17_Video_Tracking);
    hk_manager.connect_fct(18,&hk_trigger_18_CueList);
    hk_manager.connect_fct(19,&hk_trigger_19_Faders);
    hk_manager.connect_fct(20,&hk_trigger_20_MiniFaders);
    hk_manager.connect_fct(21,&hk_trigger_21_Banger);
    hk_manager.connect_fct(22,&hk_trigger_22_Blind_mode);
    hk_manager.connect_fct(23,&hk_trigger_23_CFG_Menu);
    hk_manager.connect_fct(24,&hk_trigger_24_Chasers);
    hk_manager.connect_fct(25,&hk_trigger_25_Mover);
    hk_manager.connect_fct(26,&hk_trigger_26_selectedAllChannels);
	hk_manager.connect_fct(27,&hk_trigger_27_unselectedChannels);
	hk_manager.connect_fct(28,&hk_trigger_28_movingSelectionLeft);
	hk_manager.connect_fct(29,&hk_trigger_29_movingSelectionRight);
	hk_manager.connect_fct(30,&hk_trigger_30_fullLevel);
	hk_manager.connect_fct(31,&hk_trigger_31_levelToZero);
	hk_manager.connect_fct(32,&hk_trigger_32_plusPercentForTheSelection); //32;Channels;plus % (for the selection);0;0;0;84;[ARROW UP]
	hk_manager.connect_fct(33,&hk_trigger_33_minusPercentForTheSelection); //33;Channels;minus % (for the selection);0;0;0;85;[ARROW DOWN]
	hk_manager.connect_fct(34,&hk_trigger_34_Check_Channel_left); //34;Channels;Check Channel left;0;1;0;82;[CTRL]+[<-
	hk_manager.connect_fct(35,&hk_trigger_35_Check_Channel_right); //35;Channels;Check Channel right;0;1;0;83;[CTRL]+[->
	hk_manager.connect_fct(36,&hk_trigger_36_Copy_to_the_Clipboard_Select_channels); //36;Channels;Copy to the Clipboard Select channels;0;1;0;3;[CTRL]+[C
	hk_manager.connect_fct(37,&hk_trigger_37_Paste_channels_from_clipboard); //37;Channels;Paste channels from clipboard;0;1;0;22;[CTRL]+[V
	hk_manager.connect_fct(38,&hk_trigger_38_Get_Import_channels_from_a_memory); //38;Channels;Get (Import channels from a memory);0;1;0;7;[CTRL]+[G
	hk_manager.connect_fct(39,&hk_trigger_39_Memory_recording_deleting___Create_or_over_record_a_memory_number); //39;CueList and memories;Memory recording
	hk_manager.connect_fct(40,&hk_trigger_40_Memory_recording_deleting___Create_memory_adding_the_faders); //40;CueList and memories;Memory recording
	hk_manager.connect_fct(41,&hk_trigger_41_Memory_recording_deleting___Delete_memory); //41;CueList and memories;Memory recording
	hk_manager.connect_fct(42,&hk_trigger_42_Memory_recording_deleting___Over_record_on_stage_or_blind); //42;CueList and memories;Memory recording
	hk_manager.connect_fct(43,&hk_trigger_43_Memory_recording_deleting___Over_record_on_stage_or_blind_with_faders); //43;CueList and memories;Memory recording
	hk_manager.connect_fct(44,&hk_trigger_44_Memory_recording_deleting___Reload_a_memory); //44;CueList and memories;Memory recording
	hk_manager.connect_fct(45,&hk_trigger_45_Memory_recording_deleting___Reload_a_deleted_mem); //45;CueList and memories;Memory recording
	hk_manager.connect_fct(46,&hk_trigger_46_GET_level_of_selected_channels_from_memory); //46;CueList and memories;GET level of selected channels from memory;0;1;0;7;[CTRL]+[G
	hk_manager.connect_fct(47,&hk_trigger_47_Navigating_thru_memories___Previous_mem_on_stage); //47;CueList and memories;Navigating thru memories - Previous mem on stage;0;1;0;26;[CTRL]+[W
	hk_manager.connect_fct(48,&hk_trigger_48_Navigating_thru_memories___Next_mem_on_stage); //48;CueList and memories;Navigating thru memories - Next mem on stage;0;1;0;24;[CTRL]+[X
	hk_manager.connect_fct(49,&hk_trigger_49_Navigating_thru_memories___Previous_mem_on_preset); //49;CueList and memories;Navigating thru memories - Previous mem on preset;1;0;0;26;[SHIFT]+[W
	hk_manager.connect_fct(50,&hk_trigger_50_Navigating_thru_memories___Next_mem_on_preset); //50;CueList and memories;Navigating thru memories - Next mem on preset;1;0;0;24;[SHIFT]+[X
	hk_manager.connect_fct(51,&hk_trigger_51_Crossfade_GO_PAUSE); //51;CueList and memories;Crossfade GO
	hk_manager.connect_fct(52,&hk_trigger_52_Crossfade_GO_BACK); //52;CueList and memories;Crossfade GO BACK;0;1;0;75;[CTRL]+[SPACE
	hk_manager.connect_fct(53,&hk_trigger_53_Crossfade_DOUBLE_GO); //53;CueList and memories;Crossfade DOUBLE GO;1;0;0;75;[SHIFT]+[SPACE
	hk_manager.connect_fct(54,&hk_trigger_54_Patch); //54;Transverse commands;Patch;1;0;0;16;[SHIFT]+[P
	hk_manager.connect_fct(55,&hk_trigger_55_Numpad); //55;Transverse commands;Numpad;0;0;0;16;[P
	hk_manager.connect_fct(56,&hk_trigger_56_Dimmers_selection___select_all_dimmers); //56;Patch;Dimmers selection - select all dimmers;1;0;0;25;[SHIFT]+[Y
	hk_manager.connect_fct(57,&hk_trigger_57_Dimmers_selection___unselect_all_dimmers); //57;Patch;Dimmers selection - unselect all dimmers;1;0;0;21;[SHIFT]+[U
	hk_manager.connect_fct(58,&hk_trigger_58_Check_Dimmer___left); //58;Patch;Check Dimmer - (left);1;0;0;82;[SHIFT]+[<-
	hk_manager.connect_fct(59,&hk_trigger_59_Check_Dimmer___right); //59;Patch;Check Dimmer - (right);1;0;0;83;[SHIFT]+[->
	hk_manager.connect_fct(60,&hk_trigger_60_Select_Presets_1); //60;VideoTracking;Select Presets 1;0;0;0;26;[W
	hk_manager.connect_fct(61,&hk_trigger_61_Select_Presets_2); //61;VideoTracking;Select Presets 2;0;0;0;24;[X
	hk_manager.connect_fct(62,&hk_trigger_62_Select_Presets_3); //62;VideoTracking;Select Presets 3;0;0;0;3;[C
	hk_manager.connect_fct(63,&hk_trigger_63_Select_Presets_4); //63;VideoTracking;Select Presets 4;0;0;0;22;[V
	hk_manager.connect_fct(64,&hk_trigger_64_Select_Presets_5); //64;VideoTracking;Select Presets 5;0;0;0;2;[B
	hk_manager.connect_fct(65,&hk_trigger_65_Select_Presets_6); //65;VideoTracking;Select Presets 6;0;0;0;14;[N
	hk_manager.connect_fct(66,&hk_trigger_66_Select_roi_1); //66;VideoTracking;Select roi 1;0;0;0;17;[A
	hk_manager.connect_fct(67,&hk_trigger_67_Select_roi_2); //67;VideoTracking;Select roi 2;0;0;0;23;[Z
	hk_manager.connect_fct(68,&hk_trigger_68_Select_roi_3); //68;VideoTracking;Select roi 3;0;0;0;5;[E
	hk_manager.connect_fct(69,&hk_trigger_69_Select_roi_4); //69;VideoTracking;Select roi 4;0;0;0;18;[R
	hk_manager.connect_fct(70,&hk_trigger_70_Select_roi_5); //70;VideoTracking;Select roi 5;0;0;0;20;[T
	hk_manager.connect_fct(71,&hk_trigger_71_Select_roi_6); //71;VideoTracking;Select roi 6;0;0;0;25;[Y
	hk_manager.connect_fct(72,&hk_trigger_72_Select_roi_7); //72;VideoTracking;Select roi 7;0;0;0;1;[Q
	hk_manager.connect_fct(73,&hk_trigger_73_Select_roi_8); //73;VideoTracking;Select roi 8;0;0;0;19;[S
	hk_manager.connect_fct(74,&hk_trigger_74_Select_roi_9); //74;VideoTracking;Select roi 9;0;0;0;4;[D
	hk_manager.connect_fct(75,&hk_trigger_75_Select_roi_10); //75;VideoTracking;Select roi 10;0;0;0;6;[F
	hk_manager.connect_fct(76,&hk_trigger_76_Select_roi_11); //76;VideoTracking;Select roi 11;0;0;0;7;[G
	hk_manager.connect_fct(77,&hk_trigger_77_Select_roi_12); //77;VideoTracking;Select roi 12;0;0;0;8;[H

	hk_manager.connect_fct(78,&hk_trigger_78_Bang_01); //78;Bangers;Bang 01;0;0;0;0;--unset-
	hk_manager.connect_fct(79,&hk_trigger_79_Bang_02); //79;Bangers;Bang 02;0;0;0;0;--unset-
	hk_manager.connect_fct(80,&hk_trigger_80_Bang_03); //80;Bangers;Bang 03;0;0;0;0;--unset-
	hk_manager.connect_fct(81,&hk_trigger_81_Bang_04); //81;Bangers;Bang 04;0;0;0;0;--unset-
	hk_manager.connect_fct(82,&hk_trigger_82_Bang_05); //82;Bangers;Bang 05;0;0;0;0;--unset-
	hk_manager.connect_fct(83,&hk_trigger_83_Bang_06); //83;Bangers;Bang 06;0;0;0;0;--unset-
	hk_manager.connect_fct(84,&hk_trigger_84_Bang_07); //84;Bangers;Bang 07;0;0;0;0;--unset-
	hk_manager.connect_fct(85,&hk_trigger_85_Bang_08); //85;Bangers;Bang 08;0;0;0;0;--unset-
	hk_manager.connect_fct(86,&hk_trigger_86_Bang_09); //86;Bangers;Bang 09;0;0;0;0;--unset-
	hk_manager.connect_fct(87,&hk_trigger_87_Bang_10); //87;Bangers;Bang 10;0;0;0;0;--unset-
	hk_manager.connect_fct(88,&hk_trigger_88_Bang_11); //88;Bangers;Bang 11;0;0;0;0;--unset-
	hk_manager.connect_fct(89,&hk_trigger_89_Bang_12); //89;Bangers;Bang 12;0;0;0;0;--unset-
	hk_manager.connect_fct(90,&hk_trigger_90_Bang_13); //90;Bangers;Bang 13;0;0;0;0;--unset-
	hk_manager.connect_fct(91,&hk_trigger_91_Bang_14); //91;Bangers;Bang 14;0;0;0;0;--unset-
	hk_manager.connect_fct(92,&hk_trigger_92_Bang_15); //92;Bangers;Bang 15;0;0;0;0;--unset-
	hk_manager.connect_fct(93,&hk_trigger_93_Bang_16); //93;Bangers;Bang 16;0;0;0;0;--unset-
	hk_manager.connect_fct(94,&hk_trigger_94_Bang_17); //94;Bangers;Bang 17;0;0;0;0;--unset-
	hk_manager.connect_fct(95,&hk_trigger_95_Bang_18); //95;Bangers;Bang 18;0;0;0;0;--unset-
	hk_manager.connect_fct(96,&hk_trigger_96_Bang_19); //96;Bangers;Bang 19;0;0;0;0;--unset-
	hk_manager.connect_fct(97,&hk_trigger_97_Bang_20); //97;Bangers;Bang 20;0;0;0;0;--unset-
	hk_manager.connect_fct(98,&hk_trigger_98_Bang_21); //98;Bangers;Bang 21;0;0;0;0;--unset-
	hk_manager.connect_fct(99,&hk_trigger_99_Bang_22); //99;Bangers;Bang 22;0;0;0;0;--unset-
	hk_manager.connect_fct(100,&hk_trigger_100_Bang_23); //100;Bangers;Bang 23;0;0;0;0;--unset-
	hk_manager.connect_fct(101,&hk_trigger_101_Bang_24); //101;Bangers;Bang 24;0;0;0;0;--unset-
	hk_manager.connect_fct(102,&hk_trigger_102_Bang_25); //102;Bangers;Bang 25;0;0;0;0;--unset-
	hk_manager.connect_fct(103,&hk_trigger_103_Bang_26); //103;Bangers;Bang 26;0;0;0;0;--unset-
	hk_manager.connect_fct(104,&hk_trigger_104_Bang_27); //104;Bangers;Bang 27;0;0;0;0;--unset-
	hk_manager.connect_fct(105,&hk_trigger_105_Bang_28); //105;Bangers;Bang 28;0;0;0;0;--unset-
	hk_manager.connect_fct(106,&hk_trigger_106_Bang_29); //106;Bangers;Bang 29;0;0;0;0;--unset-
	hk_manager.connect_fct(107,&hk_trigger_107_Bang_30); //107;Bangers;Bang 30;0;0;0;0;--unset-
	hk_manager.connect_fct(108,&hk_trigger_108_Bang_31); //108;Bangers;Bang 31;0;0;0;0;--unset-
	hk_manager.connect_fct(109,&hk_trigger_109_Bang_32); //109;Bangers;Bang 32;0;0;0;0;--unset-
	hk_manager.connect_fct(110,&hk_trigger_110_Bang_33); //110;Bangers;Bang 33;0;0;0;0;--unset-
	hk_manager.connect_fct(111,&hk_trigger_111_Bang_34); //111;Bangers;Bang 34;0;0;0;0;--unset-
	hk_manager.connect_fct(112,&hk_trigger_112_Bang_35); //112;Bangers;Bang 35;0;0;0;0;--unset-
	hk_manager.connect_fct(113,&hk_trigger_113_Bang_36); //113;Bangers;Bang 36;0;0;0;0;--unset-
	hk_manager.connect_fct(114,&hk_trigger_114_Bang_37); //114;Bangers;Bang 37;0;0;0;0;--unset-
	hk_manager.connect_fct(115,&hk_trigger_115_Bang_38); //115;Bangers;Bang 38;0;0;0;0;--unset-
	hk_manager.connect_fct(116,&hk_trigger_116_Bang_39); //116;Bangers;Bang 39;0;0;0;0;--unset-
	hk_manager.connect_fct(117,&hk_trigger_117_Bang_40); //117;Bangers;Bang 40;0;0;0;0;--unset-
	hk_manager.connect_fct(118,&hk_trigger_118_Bang_41); //118;Bangers;Bang 41;0;0;0;0;--unset-
	hk_manager.connect_fct(119,&hk_trigger_119_Bang_42); //119;Bangers;Bang 42;0;0;0;0;--unset-
	hk_manager.connect_fct(120,&hk_trigger_120_Bang_43); //120;Bangers;Bang 43;0;0;0;0;--unset-
	hk_manager.connect_fct(121,&hk_trigger_121_Bang_44); //121;Bangers;Bang 44;0;0;0;0;--unset-
	hk_manager.connect_fct(122,&hk_trigger_122_Bang_45); //122;Bangers;Bang 45;0;0;0;0;--unset-
	hk_manager.connect_fct(123,&hk_trigger_123_Bang_46); //123;Bangers;Bang 46;0;0;0;0;--unset-
	hk_manager.connect_fct(124,&hk_trigger_124_Bang_47); //124;Bangers;Bang 47;0;0;0;0;--unset-
	hk_manager.connect_fct(125,&hk_trigger_125_Bang_48); //125;Bangers;Bang 48;0;0;0;0;--unset-
	hk_manager.connect_fct(126,&hk_trigger_126_Bang_49); //126;Bangers;Bang 49;0;0;0;0;--unset-
	hk_manager.connect_fct(127,&hk_trigger_127_Bang_50); //127;Bangers;Bang 50;0;0;0;0;--unset-
	hk_manager.connect_fct(128,&hk_trigger_128_Bang_51); //128;Bangers;Bang 51;0;0;0;0;--unset-
	hk_manager.connect_fct(129,&hk_trigger_129_Bang_52); //129;Bangers;Bang 52;0;0;0;0;--unset-
	hk_manager.connect_fct(130,&hk_trigger_130_Bang_53); //130;Bangers;Bang 53;0;0;0;0;--unset-
	hk_manager.connect_fct(131,&hk_trigger_131_Bang_54); //131;Bangers;Bang 54;0;0;0;0;--unset-
	hk_manager.connect_fct(132,&hk_trigger_132_Bang_55); //132;Bangers;Bang 55;0;0;0;0;--unset-
	hk_manager.connect_fct(133,&hk_trigger_133_Bang_56); //133;Bangers;Bang 56;0;0;0;0;--unset-
	hk_manager.connect_fct(134,&hk_trigger_134_Bang_57); //134;Bangers;Bang 57;0;0;0;0;--unset-
	hk_manager.connect_fct(135,&hk_trigger_135_Bang_58); //135;Bangers;Bang 58;0;0;0;0;--unset-
	hk_manager.connect_fct(136,&hk_trigger_136_Bang_59); //136;Bangers;Bang 59;0;0;0;0;--unset-
	hk_manager.connect_fct(137,&hk_trigger_137_Bang_60); //137;Bangers;Bang 60;0;0;0;0;--unset-
	hk_manager.connect_fct(138,&hk_trigger_138_Bang_61); //138;Bangers;Bang 61;0;0;0;0;--unset-
	hk_manager.connect_fct(139,&hk_trigger_139_Bang_62); //139;Bangers;Bang 62;0;0;0;0;--unset-
	hk_manager.connect_fct(140,&hk_trigger_140_Bang_63); //140;Bangers;Bang 63;0;0;0;0;--unset-
	hk_manager.connect_fct(141,&hk_trigger_141_Bang_64); //141;Bangers;Bang 64;0;0;0;0;--unset-
	hk_manager.connect_fct(142,&hk_trigger_142_Bang_65); //142;Bangers;Bang 65;0;0;0;0;--unset-
	hk_manager.connect_fct(143,&hk_trigger_143_Bang_66); //143;Bangers;Bang 66;0;0;0;0;--unset-
	hk_manager.connect_fct(144,&hk_trigger_144_Bang_67); //144;Bangers;Bang 67;0;0;0;0;--unset-
	hk_manager.connect_fct(145,&hk_trigger_145_Bang_68); //145;Bangers;Bang 68;0;0;0;0;--unset-
	hk_manager.connect_fct(146,&hk_trigger_146_Bang_69); //146;Bangers;Bang 69;0;0;0;0;--unset-
	hk_manager.connect_fct(147,&hk_trigger_147_Bang_70); //147;Bangers;Bang 70;0;0;0;0;--unset-
	hk_manager.connect_fct(148,&hk_trigger_148_Bang_71); //148;Bangers;Bang 71;0;0;0;0;--unset-
	hk_manager.connect_fct(149,&hk_trigger_149_Bang_72); //149;Bangers;Bang 72;0;0;0;0;--unset-
	hk_manager.connect_fct(150,&hk_trigger_150_Bang_73); //150;Bangers;Bang 73;0;0;0;0;--unset-
	hk_manager.connect_fct(151,&hk_trigger_151_Bang_74); //151;Bangers;Bang 74;0;0;0;0;--unset-
	hk_manager.connect_fct(152,&hk_trigger_152_Bang_75); //152;Bangers;Bang 75;0;0;0;0;--unset-
	hk_manager.connect_fct(153,&hk_trigger_153_Bang_76); //153;Bangers;Bang 76;0;0;0;0;--unset-
	hk_manager.connect_fct(154,&hk_trigger_154_Bang_77); //154;Bangers;Bang 77;0;0;0;0;--unset-
	hk_manager.connect_fct(155,&hk_trigger_155_Bang_78); //155;Bangers;Bang 78;0;0;0;0;--unset-
	hk_manager.connect_fct(156,&hk_trigger_156_Bang_79); //156;Bangers;Bang 79;0;0;0;0;--unset-
	hk_manager.connect_fct(157,&hk_trigger_157_Bang_80); //157;Bangers;Bang 80;0;0;0;0;--unset-
	hk_manager.connect_fct(158,&hk_trigger_158_Bang_81); //158;Bangers;Bang 81;0;0;0;0;--unset-
	hk_manager.connect_fct(159,&hk_trigger_159_Bang_82); //159;Bangers;Bang 82;0;0;0;0;--unset-
	hk_manager.connect_fct(160,&hk_trigger_160_Bang_83); //160;Bangers;Bang 83;0;0;0;0;--unset-
	hk_manager.connect_fct(161,&hk_trigger_161_Bang_84); //161;Bangers;Bang 84;0;0;0;0;--unset-
	hk_manager.connect_fct(162,&hk_trigger_162_Bang_85); //162;Bangers;Bang 85;0;0;0;0;--unset-
	hk_manager.connect_fct(163,&hk_trigger_163_Bang_86); //163;Bangers;Bang 86;0;0;0;0;--unset-
	hk_manager.connect_fct(164,&hk_trigger_164_Bang_87); //164;Bangers;Bang 87;0;0;0;0;--unset-
	hk_manager.connect_fct(165,&hk_trigger_165_Bang_88); //165;Bangers;Bang 88;0;0;0;0;--unset-
	hk_manager.connect_fct(166,&hk_trigger_166_Bang_89); //166;Bangers;Bang 89;0;0;0;0;--unset-
	hk_manager.connect_fct(167,&hk_trigger_167_Bang_90); //167;Bangers;Bang 90;0;0;0;0;--unset-
	hk_manager.connect_fct(168,&hk_trigger_168_Bang_91); //168;Bangers;Bang 91;0;0;0;0;--unset-
	hk_manager.connect_fct(169,&hk_trigger_169_Bang_92); //169;Bangers;Bang 92;0;0;0;0;--unset-
	hk_manager.connect_fct(170,&hk_trigger_170_Bang_93); //170;Bangers;Bang 93;0;0;0;0;--unset-
	hk_manager.connect_fct(171,&hk_trigger_171_Bang_94); //171;Bangers;Bang 94;0;0;0;0;--unset-
	hk_manager.connect_fct(172,&hk_trigger_172_Bang_95); //172;Bangers;Bang 95;0;0;0;0;--unset-
	hk_manager.connect_fct(173,&hk_trigger_173_Bang_96); //173;Bangers;Bang 96;0;0;0;0;--unset-
	hk_manager.connect_fct(174,&hk_trigger_174_Bang_97); //174;Bangers;Bang 97;0;0;0;0;--unset-
	hk_manager.connect_fct(175,&hk_trigger_175_Bang_98); //175;Bangers;Bang 98;0;0;0;0;--unset-
	hk_manager.connect_fct(176,&hk_trigger_176_Bang_99); //176;Bangers;Bang 99;0;0;0;0;--unset-
	hk_manager.connect_fct(177,&hk_trigger_177_Bang_100); //177;Bangers;Bang 100;0;0;0;0;--unset-
	hk_manager.connect_fct(178,&hk_trigger_178_Bang_101); //178;Bangers;Bang 101;0;0;0;0;--unset-
	hk_manager.connect_fct(179,&hk_trigger_179_Bang_102); //179;Bangers;Bang 102;0;0;0;0;--unset-
	hk_manager.connect_fct(180,&hk_trigger_180_Bang_103); //180;Bangers;Bang 103;0;0;0;0;--unset-
	hk_manager.connect_fct(181,&hk_trigger_181_Bang_104); //181;Bangers;Bang 104;0;0;0;0;--unset-
	hk_manager.connect_fct(182,&hk_trigger_182_Bang_105); //182;Bangers;Bang 105;0;0;0;0;--unset-
	hk_manager.connect_fct(183,&hk_trigger_183_Bang_106); //183;Bangers;Bang 106;0;0;0;0;--unset-
	hk_manager.connect_fct(184,&hk_trigger_184_Bang_107); //184;Bangers;Bang 107;0;0;0;0;--unset-
	hk_manager.connect_fct(185,&hk_trigger_185_Bang_108); //185;Bangers;Bang 108;0;0;0;0;--unset-
	hk_manager.connect_fct(186,&hk_trigger_186_Bang_109); //186;Bangers;Bang 109;0;0;0;0;--unset-
	hk_manager.connect_fct(187,&hk_trigger_187_Bang_110); //187;Bangers;Bang 110;0;0;0;0;--unset-
	hk_manager.connect_fct(188,&hk_trigger_188_Bang_111); //188;Bangers;Bang 111;0;0;0;0;--unset-
	hk_manager.connect_fct(189,&hk_trigger_189_Bang_112); //189;Bangers;Bang 112;0;0;0;0;--unset-
	hk_manager.connect_fct(190,&hk_trigger_190_Bang_113); //190;Bangers;Bang 113;0;0;0;0;--unset-
	hk_manager.connect_fct(191,&hk_trigger_191_Bang_114); //191;Bangers;Bang 114;0;0;0;0;--unset-
	hk_manager.connect_fct(192,&hk_trigger_192_Bang_115); //192;Bangers;Bang 115;0;0;0;0;--unset-
	hk_manager.connect_fct(193,&hk_trigger_193_Bang_116); //193;Bangers;Bang 116;0;0;0;0;--unset-
	hk_manager.connect_fct(194,&hk_trigger_194_Bang_117); //194;Bangers;Bang 117;0;0;0;0;--unset-
	hk_manager.connect_fct(195,&hk_trigger_195_Bang_118); //195;Bangers;Bang 118;0;0;0;0;--unset-
	hk_manager.connect_fct(196,&hk_trigger_196_Bang_119); //196;Bangers;Bang 119;0;0;0;0;--unset-
	hk_manager.connect_fct(197,&hk_trigger_197_Bang_120); //197;Bangers;Bang 120;0;0;0;0;--unset-
	hk_manager.connect_fct(198,&hk_trigger_198_Bang_121); //198;Bangers;Bang 121;0;0;0;0;--unset-
	hk_manager.connect_fct(199,&hk_trigger_199_Bang_122); //199;Bangers;Bang 122;0;0;0;0;--unset-
	hk_manager.connect_fct(200,&hk_trigger_200_Bang_123); //200;Bangers;Bang 123;0;0;0;0;--unset-
	hk_manager.connect_fct(201,&hk_trigger_201_Bang_124); //201;Bangers;Bang 124;0;0;0;0;--unset-
	hk_manager.connect_fct(202,&hk_trigger_202_Bang_125); //202;Bangers;Bang 125;0;0;0;0;--unset-
	hk_manager.connect_fct(203,&hk_trigger_203_Bang_126); //203;Bangers;Bang 126;0;0;0;0;--unset-
	hk_manager.connect_fct(204,&hk_trigger_204_Bang_127); //204;Bangers;Bang 127;0;0;0;0;--unset-
	hk_manager.connect_fct(205,&hk_trigger_205_Bang_128); //205;Bangers;Bang 128;0;0;0;0;--unset-
	hk_manager.connect_fct(206,&hk_trigger_206_Bang_129); //206;Bangers;Bang 129;0;0;0;0;--unset-
	hk_manager.connect_fct(207,&hk_trigger_207_Bang_130); //207;Bangers;Bang 130;0;0;0;0;--unset-
	hk_manager.connect_fct(208,&hk_trigger_208_Bang_131); //208;Bangers;Bang 131;0;0;0;0;--unset-
	hk_manager.connect_fct(209,&hk_trigger_209_Bang_132); //209;Bangers;Bang 132;0;0;0;0;--unset-
	hk_manager.connect_fct(210,&hk_trigger_210_Bang_133); //210;Bangers;Bang 133;0;0;0;0;--unset-
	hk_manager.connect_fct(211,&hk_trigger_211_Bang_134); //211;Bangers;Bang 134;0;0;0;0;--unset-
	hk_manager.connect_fct(212,&hk_trigger_212_Bang_135); //212;Bangers;Bang 135;0;0;0;0;--unset-
	hk_manager.connect_fct(213,&hk_trigger_213_Bang_136); //213;Bangers;Bang 136;0;0;0;0;--unset-
	hk_manager.connect_fct(214,&hk_trigger_214_Bang_137); //214;Bangers;Bang 137;0;0;0;0;--unset-
	hk_manager.connect_fct(215,&hk_trigger_215_Bang_138); //215;Bangers;Bang 138;0;0;0;0;--unset-
	hk_manager.connect_fct(216,&hk_trigger_216_Bang_139); //216;Bangers;Bang 139;0;0;0;0;--unset-
	hk_manager.connect_fct(217,&hk_trigger_217_Bang_140); //217;Bangers;Bang 140;0;0;0;0;--unset-
	hk_manager.connect_fct(218,&hk_trigger_218_Bang_141); //218;Bangers;Bang 141;0;0;0;0;--unset-
	hk_manager.connect_fct(219,&hk_trigger_219_Bang_142); //219;Bangers;Bang 142;0;0;0;0;--unset-
	hk_manager.connect_fct(220,&hk_trigger_220_Bang_143); //220;Bangers;Bang 143;0;0;0;0;--unset-
	hk_manager.connect_fct(221,&hk_trigger_221_Bang_144); //221;Bangers;Bang 144;0;0;0;0;--unset-
	hk_manager.connect_fct(222,&hk_trigger_222_Bang_145); //222;Bangers;Bang 145;0;0;0;0;--unset-
	hk_manager.connect_fct(223,&hk_trigger_223_Bang_146); //223;Bangers;Bang 146;0;0;0;0;--unset-
	hk_manager.connect_fct(224,&hk_trigger_224_Bang_147); //224;Bangers;Bang 147;0;0;0;0;--unset-
	hk_manager.connect_fct(225,&hk_trigger_225_Bang_148); //225;Bangers;Bang 148;0;0;0;0;--unset-
	hk_manager.connect_fct(226,&hk_trigger_226_Bang_149); //226;Bangers;Bang 149;0;0;0;0;--unset-
	hk_manager.connect_fct(227,&hk_trigger_227_Bang_150); //227;Bangers;Bang 150;0;0;0;0;--unset-
	hk_manager.connect_fct(228,&hk_trigger_228_Bang_151); //228;Bangers;Bang 151;0;0;0;0;--unset-
	hk_manager.connect_fct(229,&hk_trigger_229_Bang_152); //229;Bangers;Bang 152;0;0;0;0;--unset-
	hk_manager.connect_fct(230,&hk_trigger_230_Bang_153); //230;Bangers;Bang 153;0;0;0;0;--unset-
	hk_manager.connect_fct(231,&hk_trigger_231_Bang_154); //231;Bangers;Bang 154;0;0;0;0;--unset-
	hk_manager.connect_fct(232,&hk_trigger_232_Bang_155); //232;Bangers;Bang 155;0;0;0;0;--unset-
	hk_manager.connect_fct(233,&hk_trigger_233_Bang_156); //233;Bangers;Bang 156;0;0;0;0;--unset-
	hk_manager.connect_fct(234,&hk_trigger_234_Bang_157); //234;Bangers;Bang 157;0;0;0;0;--unset-
	hk_manager.connect_fct(235,&hk_trigger_235_Bang_158); //235;Bangers;Bang 158;0;0;0;0;--unset-
	hk_manager.connect_fct(236,&hk_trigger_236_Bang_159); //236;Bangers;Bang 159;0;0;0;0;--unset-
	hk_manager.connect_fct(237,&hk_trigger_237_Bang_160); //237;Bangers;Bang 160;0;0;0;0;--unset-
	hk_manager.connect_fct(238,&hk_trigger_238_Bang_161); //238;Bangers;Bang 161;0;0;0;0;--unset-
	hk_manager.connect_fct(239,&hk_trigger_239_Bang_162); //239;Bangers;Bang 162;0;0;0;0;--unset-
	hk_manager.connect_fct(240,&hk_trigger_240_Bang_163); //240;Bangers;Bang 163;0;0;0;0;--unset-
	hk_manager.connect_fct(241,&hk_trigger_241_Bang_164); //241;Bangers;Bang 164;0;0;0;0;--unset-
	hk_manager.connect_fct(242,&hk_trigger_242_Bang_165); //242;Bangers;Bang 165;0;0;0;0;--unset-
	hk_manager.connect_fct(243,&hk_trigger_243_Bang_166); //243;Bangers;Bang 166;0;0;0;0;--unset-
	hk_manager.connect_fct(244,&hk_trigger_244_Bang_167); //244;Bangers;Bang 167;0;0;0;0;--unset-
	hk_manager.connect_fct(245,&hk_trigger_245_Bang_168); //245;Bangers;Bang 168;0;0;0;0;--unset-
	hk_manager.connect_fct(246,&hk_trigger_246_Bang_169); //246;Bangers;Bang 169;0;0;0;0;--unset-
	hk_manager.connect_fct(247,&hk_trigger_247_Bang_170); //247;Bangers;Bang 170;0;0;0;0;--unset-
	hk_manager.connect_fct(248,&hk_trigger_248_Bang_171); //248;Bangers;Bang 171;0;0;0;0;--unset-
	hk_manager.connect_fct(249,&hk_trigger_249_Bang_172); //249;Bangers;Bang 172;0;0;0;0;--unset-
	hk_manager.connect_fct(250,&hk_trigger_250_Bang_173); //250;Bangers;Bang 173;0;0;0;0;--unset-
	hk_manager.connect_fct(251,&hk_trigger_251_Bang_174); //251;Bangers;Bang 174;0;0;0;0;--unset-
	hk_manager.connect_fct(252,&hk_trigger_252_Bang_175); //252;Bangers;Bang 175;0;0;0;0;--unset-
	hk_manager.connect_fct(253,&hk_trigger_253_Bang_176); //253;Bangers;Bang 176;0;0;0;0;--unset-
	hk_manager.connect_fct(254,&hk_trigger_254_Bang_177); //254;Bangers;Bang 177;0;0;0;0;--unset-
	hk_manager.connect_fct(255,&hk_trigger_255_Bang_178); //255;Bangers;Bang 178;0;0;0;0;--unset-
	hk_manager.connect_fct(256,&hk_trigger_256_Bang_179); //256;Bangers;Bang 179;0;0;0;0;--unset-
	hk_manager.connect_fct(257,&hk_trigger_257_Bang_180); //257;Bangers;Bang 180;0;0;0;0;--unset-
	hk_manager.connect_fct(258,&hk_trigger_258_Bang_181); //258;Bangers;Bang 181;0;0;0;0;--unset-
	hk_manager.connect_fct(259,&hk_trigger_259_Bang_182); //259;Bangers;Bang 182;0;0;0;0;--unset-
	hk_manager.connect_fct(260,&hk_trigger_260_Bang_183); //260;Bangers;Bang 183;0;0;0;0;--unset-
	hk_manager.connect_fct(261,&hk_trigger_261_Bang_184); //261;Bangers;Bang 184;0;0;0;0;--unset-
	hk_manager.connect_fct(262,&hk_trigger_262_Bang_185); //262;Bangers;Bang 185;0;0;0;0;--unset-
	hk_manager.connect_fct(263,&hk_trigger_263_Bang_186); //263;Bangers;Bang 186;0;0;0;0;--unset-
	hk_manager.connect_fct(264,&hk_trigger_264_Bang_187); //264;Bangers;Bang 187;0;0;0;0;--unset-
	hk_manager.connect_fct(265,&hk_trigger_265_Bang_188); //265;Bangers;Bang 188;0;0;0;0;--unset-
	hk_manager.connect_fct(266,&hk_trigger_266_Bang_189); //266;Bangers;Bang 189;0;0;0;0;--unset-
	hk_manager.connect_fct(267,&hk_trigger_267_Bang_190); //267;Bangers;Bang 190;0;0;0;0;--unset-
	hk_manager.connect_fct(268,&hk_trigger_268_Bang_191); //268;Bangers;Bang 191;0;0;0;0;--unset-
	hk_manager.connect_fct(269,&hk_trigger_269_Bang_192); //269;Bangers;Bang 192;0;0;0;0;--unset-
	hk_manager.connect_fct(270,&hk_trigger_270_Bang_193); //270;Bangers;Bang 193;0;0;0;0;--unset-
	hk_manager.connect_fct(271,&hk_trigger_271_Bang_194); //271;Bangers;Bang 194;0;0;0;0;--unset-
	hk_manager.connect_fct(272,&hk_trigger_272_Bang_195); //272;Bangers;Bang 195;0;0;0;0;--unset-
	hk_manager.connect_fct(273,&hk_trigger_273_Bang_196); //273;Bangers;Bang 196;0;0;0;0;--unset-
	hk_manager.connect_fct(274,&hk_trigger_274_Bang_197); //274;Bangers;Bang 197;0;0;0;0;--unset-
	hk_manager.connect_fct(275,&hk_trigger_275_Bang_198); //275;Bangers;Bang 198;0;0;0;0;--unset-
	hk_manager.connect_fct(276,&hk_trigger_276_Bang_199); //276;Bangers;Bang 199;0;0;0;0;--unset-
	hk_manager.connect_fct(277,&hk_trigger_277_Bang_200); //277;Bangers;Bang 200;0;0;0;0;--unset-
	hk_manager.connect_fct(278,&hk_trigger_278_Bang_201); //278;Bangers;Bang 201;0;0;0;0;--unset-
	hk_manager.connect_fct(279,&hk_trigger_279_Bang_202); //279;Bangers;Bang 202;0;0;0;0;--unset-
	hk_manager.connect_fct(280,&hk_trigger_280_Bang_203); //280;Bangers;Bang 203;0;0;0;0;--unset-
	hk_manager.connect_fct(281,&hk_trigger_281_Bang_204); //281;Bangers;Bang 204;0;0;0;0;--unset-
	hk_manager.connect_fct(282,&hk_trigger_282_Bang_205); //282;Bangers;Bang 205;0;0;0;0;--unset-
	hk_manager.connect_fct(283,&hk_trigger_283_Bang_206); //283;Bangers;Bang 206;0;0;0;0;--unset-
	hk_manager.connect_fct(284,&hk_trigger_284_Bang_207); //284;Bangers;Bang 207;0;0;0;0;--unset-
	hk_manager.connect_fct(285,&hk_trigger_285_Bang_208); //285;Bangers;Bang 208;0;0;0;0;--unset-
	hk_manager.connect_fct(286,&hk_trigger_286_Bang_209); //286;Bangers;Bang 209;0;0;0;0;--unset-
	hk_manager.connect_fct(287,&hk_trigger_287_Bang_210); //287;Bangers;Bang 210;0;0;0;0;--unset-
	hk_manager.connect_fct(288,&hk_trigger_288_Bang_211); //288;Bangers;Bang 211;0;0;0;0;--unset-
	hk_manager.connect_fct(289,&hk_trigger_289_Bang_212); //289;Bangers;Bang 212;0;0;0;0;--unset-
	hk_manager.connect_fct(290,&hk_trigger_290_Bang_213); //290;Bangers;Bang 213;0;0;0;0;--unset-
	hk_manager.connect_fct(291,&hk_trigger_291_Bang_214); //291;Bangers;Bang 214;0;0;0;0;--unset-
	hk_manager.connect_fct(292,&hk_trigger_292_Bang_215); //292;Bangers;Bang 215;0;0;0;0;--unset-
	hk_manager.connect_fct(293,&hk_trigger_293_Bang_216); //293;Bangers;Bang 216;0;0;0;0;--unset-
	hk_manager.connect_fct(294,&hk_trigger_294_Bang_217); //294;Bangers;Bang 217;0;0;0;0;--unset-
	hk_manager.connect_fct(295,&hk_trigger_295_Bang_218); //295;Bangers;Bang 218;0;0;0;0;--unset-
	hk_manager.connect_fct(296,&hk_trigger_296_Bang_219); //296;Bangers;Bang 219;0;0;0;0;--unset-
	hk_manager.connect_fct(297,&hk_trigger_297_Bang_220); //297;Bangers;Bang 220;0;0;0;0;--unset-
	hk_manager.connect_fct(298,&hk_trigger_298_Bang_221); //298;Bangers;Bang 221;0;0;0;0;--unset-
	hk_manager.connect_fct(299,&hk_trigger_299_Bang_222); //299;Bangers;Bang 222;0;0;0;0;--unset-
	hk_manager.connect_fct(300,&hk_trigger_300_Bang_223); //300;Bangers;Bang 223;0;0;0;0;--unset-
	hk_manager.connect_fct(301,&hk_trigger_301_Bang_224); //301;Bangers;Bang 224;0;0;0;0;--unset-
	hk_manager.connect_fct(302,&hk_trigger_302_Bang_225); //302;Bangers;Bang 225;0;0;0;0;--unset-
	hk_manager.connect_fct(303,&hk_trigger_303_Bang_226); //303;Bangers;Bang 226;0;0;0;0;--unset-
	hk_manager.connect_fct(304,&hk_trigger_304_Bang_227); //304;Bangers;Bang 227;0;0;0;0;--unset-
	hk_manager.connect_fct(305,&hk_trigger_305_Bang_228); //305;Bangers;Bang 228;0;0;0;0;--unset-
	hk_manager.connect_fct(306,&hk_trigger_306_Bang_229); //306;Bangers;Bang 229;0;0;0;0;--unset-
	hk_manager.connect_fct(307,&hk_trigger_307_Bang_230); //307;Bangers;Bang 230;0;0;0;0;--unset-
	hk_manager.connect_fct(308,&hk_trigger_308_Bang_231); //308;Bangers;Bang 231;0;0;0;0;--unset-
	hk_manager.connect_fct(309,&hk_trigger_309_Bang_232); //309;Bangers;Bang 232;0;0;0;0;--unset-
	hk_manager.connect_fct(310,&hk_trigger_310_Bang_233); //310;Bangers;Bang 233;0;0;0;0;--unset-
	hk_manager.connect_fct(311,&hk_trigger_311_Bang_234); //311;Bangers;Bang 234;0;0;0;0;--unset-
	hk_manager.connect_fct(312,&hk_trigger_312_Bang_235); //312;Bangers;Bang 235;0;0;0;0;--unset-
	hk_manager.connect_fct(313,&hk_trigger_313_Bang_236); //313;Bangers;Bang 236;0;0;0;0;--unset-
	hk_manager.connect_fct(314,&hk_trigger_314_Bang_237); //314;Bangers;Bang 237;0;0;0;0;--unset-
	hk_manager.connect_fct(315,&hk_trigger_315_Bang_238); //315;Bangers;Bang 238;0;0;0;0;--unset-
	hk_manager.connect_fct(316,&hk_trigger_316_Bang_239); //316;Bangers;Bang 239;0;0;0;0;--unset-
	hk_manager.connect_fct(317,&hk_trigger_317_Bang_240); //317;Bangers;Bang 240;0;0;0;0;--unset-
	hk_manager.connect_fct(318,&hk_trigger_318_Bang_241); //318;Bangers;Bang 241;0;0;0;0;--unset-
	hk_manager.connect_fct(319,&hk_trigger_319_Bang_242); //319;Bangers;Bang 242;0;0;0;0;--unset-
	hk_manager.connect_fct(320,&hk_trigger_320_Bang_243); //320;Bangers;Bang 243;0;0;0;0;--unset-
	hk_manager.connect_fct(321,&hk_trigger_321_Bang_244); //321;Bangers;Bang 244;0;0;0;0;--unset-
	hk_manager.connect_fct(322,&hk_trigger_322_Bang_245); //322;Bangers;Bang 245;0;0;0;0;--unset-
	hk_manager.connect_fct(323,&hk_trigger_323_Bang_246); //323;Bangers;Bang 246;0;0;0;0;--unset-
	hk_manager.connect_fct(324,&hk_trigger_324_Bang_247); //324;Bangers;Bang 247;0;0;0;0;--unset-
	hk_manager.connect_fct(325,&hk_trigger_325_Bang_248); //325;Bangers;Bang 248;0;0;0;0;--unset-
	hk_manager.connect_fct(326,&hk_trigger_326_Bang_249); //326;Bangers;Bang 249;0;0;0;0;--unset-
	hk_manager.connect_fct(327,&hk_trigger_327_Bang_250); //327;Bangers;Bang 250;0;0;0;0;--unset-
	hk_manager.connect_fct(328,&hk_trigger_328_Bang_251); //328;Bangers;Bang 251;0;0;0;0;--unset-
	hk_manager.connect_fct(329,&hk_trigger_329_Bang_252); //329;Bangers;Bang 252;0;0;0;0;--unset-
	hk_manager.connect_fct(330,&hk_trigger_330_Bang_253); //330;Bangers;Bang 253;0;0;0;0;--unset-
	hk_manager.connect_fct(331,&hk_trigger_331_Bang_254); //331;Bangers;Bang 254;0;0;0;0;--unset-
	hk_manager.connect_fct(332,&hk_trigger_332_Bang_255); //332;Bangers;Bang 255;0;0;0;0;--unset-


	// !! - déclarer la fonction dans le header correspondant
}
