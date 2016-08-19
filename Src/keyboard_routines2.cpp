
/*-------------------------------------------------------------------------------------------------------------
                                 |
          CWWWWWWWW              | Copyright (C) 2009-2013  Christoph Guillermet
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

* \file keyboard_routines2.cpp
* \brief {keyboard shortcut}
* \author Christoph Guillermet
* \version {0.8.6}
* \date {28/04/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions core pour gérer les raccourcis clavier dans whitecat
*
*   Core fonctions for keyboard shortcut
*
 **/

#include <allegro.h>


int recall_config_page()
{
    switch(config_page_is)
    {
    case 0:
        break;
    case 1:
        index_config_dmx=1;
        break;
    case 2:
        index_config_midi=1;
        break;
    case 3:
        index_config_network=1;
        break;
    case 4:
        index_setup_gfx=1;
        break;
    case 5:
        index_config_arduino=1;
        break;
    case 6:
        index_config_general=1;
        break;
    }
    return(0);
}


int commandes_clavier()//la fonction sprintf tue l acces clavier
{
    if ( keypressed())
    {

        int chi = readkey();
        scan_ascii_is=(chi & 0xff);//prend pas en compte touches fonctions
        scan_allegro_key_is=(chi >> 8);//prend en compte tout le monde mais à redistribuer fr et anglais


        switch (chi >> 8)
        {

        case KEY_INSERT://affectation midi

            if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
            {
                toggle_numerical_midi_way=toggle(toggle_numerical_midi_way);
            }
            else
            {
                Midi_Faders_Affectation_Type++;
                if(Midi_Faders_Affectation_Type>2)
                {
                    Midi_Faders_Affectation_Type=0;
                }
                index_midi_mute=0;
                reset_index_actions();
            }
            break;

        case KEY_ESC://nettoyage chaine de caractere et deselection totale

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

///////////////////////PAGE UP DOWN POUR FENETRES /////////////////////////////
        case KEY_PGUP:
            sprintf(string_key_id,list_keyname[0]);
            key_switch_window_up();
            break;
        case KEY_PGDN:
            sprintf(string_key_id,list_keyname[0]);
            key_switch_window_down();
            break;
//////////////////SPECIAL KEYS ////////////////////////////////////////////////
        case  KEY_TILDE://carré
            if(window_focus_id==W_PLOT)
            {
                light_plot_view_port_drag_mode_enable=toggle(light_plot_view_port_drag_mode_enable);
            }
            break;

        case KEY_F1://dock mode
            if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
            {
                reset_indexs_confirmation();
                index_ask_confirm=1;
                index_do_overrecord_mem=1;
                clear_keybuf();
            }
            else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
            {
//sab 02/03/2014 unused var int mem_to_rec=(int)(atof(numeric)*10);

                reset_indexs_confirmation();
                index_ask_confirm=1;
                index_do_create_mem=1;
            }
            else
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
                    if(index_do_dock==0)
                    {
                        gridplayer_to_affect_is=-1;
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
            break;

        case KEY_F2:
            index_do_dock=0;
            index_do_report=0;
            index_main_clear=0;
            index_do_modify=toggle(index_do_modify);;
            break;

        case KEY_F3:
            if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
            {
                index_do_dock=0;
                index_do_modify=0;
                index_main_clear=0;
                index_do_report=1;
                reset_indexs_confirmation();
                index_ask_confirm=1;
                index_do_overecord_mem_plus_faders=1;
            }
            else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1) //creation mémoires en mode merge Faders / seq
            {
                index_do_dock=0;
                index_do_modify=0;
                index_main_clear=0;
                index_do_report=1;
//sab 02/03/2014 unused var int mem_to_rec=(int)(atof(numeric)*10);
                reset_indexs_confirmation();
                index_ask_confirm=1;
                index_do_create_mem_plus_faders=1;
            }
            else
            {
                index_do_dock=0;
                index_do_modify=0;
                index_main_clear=0;
                index_do_report=toggle(index_do_report);
            }
            break;

        case KEY_F4:
            index_do_dock=0;
            index_do_modify=0;
            index_do_report=0;
            index_main_clear=toggle(index_main_clear);
            break;

        case KEY_F5:
            index_type=toggle(index_type);
            strcpy(numeric,"");
            keyboardStorage_numeric_postext=0;
            break;

        case KEY_F6:
            if(index_time==0)
            {
                add_a_window(W_TIME);
            }
            else
            {
                substract_a_window(W_TIME);
            }
            break;

        case KEY_F7:
            if(index_trichro_window==0)
            {
                add_a_window(W_TRICHROMY);
            }
            else
            {
                substract_a_window(W_TRICHROMY);
            }
            break;

        case KEY_F8:
            if(index_video_window==0)
            {
                add_a_window(W_TRACKINGVIDEO);
            }
            else
            {
                substract_a_window(W_TRACKINGVIDEO);
            }
            break;

        case KEY_F9:
            if(index_window_sequentiel==0)
            {
                ;
                add_a_window(W_SEQUENCIEL);
            }
            else
            {
                substract_a_window(W_SEQUENCIEL);
            }
            break;
        case KEY_F10:
            if (key_shifts & KB_SHIFT_FLAG  || index_false_shift==1) //CONFIG
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
            else
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

            break;

        case KEY_F11:
            if (key_shifts & KB_SHIFT_FLAG  || index_false_shift==1) //CONFIG
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
            else if (key_shifts & KB_CTRL_FLAG  || index_false_control==1 )
            {
                index_blind=toggle(index_blind);
            }
            else
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
            break;

        case KEY_F12://black out

            if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
            {
                index_ask_confirm=1;
                index_do_quit_with_save=1;
            }

            else if (key_shifts & KB_SHIFT_FLAG   || index_false_shift==1)
            {
                for (int i=0; i<12; i++)
                {
                    specify_who_to_save_load[i]=0;
                }
                reset_save_load_report_string();
                index_ask_confirm=1;
                index_do_quit_without_save=1;
            }

            else
            {
                if(index_blind==0)
                {
                    for (int rs=0; rs<513; rs++)
                    {
                        bufferSaisie[rs]=0;
                        Selected_Channel[rs]=0;
                    }
                    sprintf(string_Last_Order,">> Black Out done for On Stage channels");
                }
                else if(index_blind==1)
                {
                    for (int rs=0; rs<513; rs++)
                    {
                        bufferBlind[rs]=0;
                        Selected_Channel[rs]=0;
                    }
                    sprintf(string_Last_Order,">> Black Out done for On Blind channels");
                }

                substract_channel_selection_to_layers_plot();
            }
            break;


        case KEY_UP:
            key_up();
            sprintf(string_key_id,list_keyname[1]);
            break;

        case KEY_DOWN:
            key_down();
            sprintf(string_key_id,list_keyname[2]);
            break;

        case KEY_ENTER :
            key_affectation();
            sprintf(string_key_id,list_keyname[3]);
            break;

        case KEY_ENTER_PAD:
            key_affectation();
            sprintf(string_key_id,list_keyname[4]);
            break;

        case KEY_EQUALS://+
            key_add_ch();
            sprintf(string_key_id,list_keyname[5]);
            break;

        case KEY_PLUS_PAD://+ num
            key_add_ch();
            sprintf(string_key_id,list_keyname[6]);
            break;

        case KEY_MINUS://-
            key_minus_ch();
            sprintf(string_key_id,list_keyname[7]);
            break;

        case KEY_MINUS_PAD://- num
            key_minus_ch();
            sprintf(string_key_id,list_keyname[8]);
            break;


        case KEY_TAB:
            if(keyboardStorage_numeric_postext>0)
            {
                key_thruth();
                sprintf(string_key_id,list_keyname[10]);
            }
            else
            {
                if(window_focus_id==W_PLOT)
                {
                    index_tab_on=toggle(index_tab_on);
                }
            }
            break;
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////TEXT TYPING OR FUNCTIONS CALLING//////////////////////////////////////////

        case KEY_SPACE:
            if (index_type==0)
            {
                key_go();
            }
            else if(index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]=' ';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[11]);
            break;



        case KEY_Q: //lettre a
            if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
            {
                if(index_show_audio_window==0)
                {
                    add_a_window(W_AUDIO);
                }
                else
                {
                    substract_a_window(W_AUDIO);
                }
                reset_audio_indexs_to_dock();
            }
            else
            {

                if(index_type==0)
                {
                    key_presetvideo(0);
                }
                else  if (index_type==1)
                {
                    numeric[keyboardStorage_numeric_postext]='A';
                    keyboardStorage_numeric_postext++;
                }
            }
            sprintf(string_key_id,list_keyname[12]);
            break;
        case KEY_B:
            if (index_type==0)
            {
                key_roi(10);
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='B';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[13]);
            break;

        case KEY_C:
            if (index_type==0)
            {
                if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
                {
                    if(keyboardStorage_numeric_postext==0)
                    {
                        channel_copy();
                    }
                    else
                    {
                        snap_mem_to_copy();
                    }
                }
                else  if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
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
                else
                {
                    key_roi(8);
                }
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='C';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[14]);
            break;

        case KEY_D://dock mode on
            if(index_type==0)
            {
                key_roi(2);
            }
            else if(index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='D';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[15]);
            break;

        case KEY_E:
            if (index_type==0)
            {
                key_presetvideo(2);
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='E';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[16]);
            break;

        case KEY_F:
            if(index_type==0)
            {
                key_roi(3);
            }

            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='F';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[17]);
            break;

        case KEY_G:
            if (index_type==0)
            {
                if ((key_shifts & KB_CTRL_FLAG || index_false_control==1 ) && keyboardStorage_numeric_postext>0)
                {
                    //GET CHANNELS FROM A MEMORY
                    int mem_to_take=(int)(atof(numeric)*10);
                    if(MemoiresExistantes[mem_to_take]==1)
                    {
                        Get_channels_from_memory(mem_to_take);
                    }
                    else
                    {
                        sprintf(string_Last_Order,"Get Sel. channel from %d.%d: mem doesn't exist",mem_to_take/10,mem_to_take%10);
                    }
                }
                else
                {
                    key_roi(4);
                }
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='G';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[18]);
            break;

        case KEY_H:

            if (index_type==0)
            {
                key_roi(5);
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='H';
                keyboardStorage_numeric_postext++;
            }

            sprintf(string_key_id,list_keyname[19]);
            break;

        case KEY_I:
            if(index_type==0) //full
            {
                key_full();
            }
            else if(index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='I';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[20]);
            break;

        case KEY_J:
            if (index_type==0)
            {
                key_time_out();
            }
            if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='J';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[21]);
            break;

        case KEY_K:
            if (index_type==0)
            {
                key_time_in();
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='K';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[22]);
            break;

        case KEY_L://in + out
            if(index_type==0)
            {
                key_time_in_out();
            }
            else if(index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='L';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[23]);
            break;

        case KEY_SEMICOLON:
            if(index_type==0)//le M qui est point en clavier americain
            {
                if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
                {
                    //sab 02/04/2014IMPACT if(index_show_mover_window=0){add_a_window(W_MOVER);}
                    if(index_show_mover_window==0)
                    {
                        add_a_window(W_MOVER);
                    }
                    else
                    {
                        substract_a_window(W_MOVER);
                    }
                }
            }
            else if(index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='M';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[38]);
            break;

        case KEY_N:
            if (index_type==0)
            {
                key_roi(11);
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='N';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[24]);
            break;

        case KEY_O:


            if(index_type==0)
            {
                key_at_zero();
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='O';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[25]);
            break;

        case KEY_P:

            if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
            {
                if(index_patch_window==0)
                {
                    add_a_window(W_PATCH);
                }
                else
                {
                    substract_a_window(W_PATCH);
                }
            }
            else
            {
                if (index_type==0)
                {
                    if(index_visual_pad==0)
                    {
                        add_a_window(W_NUMPAD);
                    }
                    else
                    {
                        substract_a_window(W_NUMPAD);
                    }
                }
                else if (index_type==1)
                {
                    numeric[keyboardStorage_numeric_postext]='P';
                    keyboardStorage_numeric_postext++;
                }
            }
            sprintf(string_key_id,list_keyname[39]);
            break;

        case KEY_A: // lettre Q
            if (index_type==0)
            {
                key_roi(1);
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='Q';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[26]);
            break;

        case KEY_R://report mode on
            if(index_type==0 )
            {
                key_presetvideo(3);;//les banques de tracking cam
            }
            else if(index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='R';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[27]);
            break;

        case KEY_S:
            if (index_type==0)
            {
                if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
                {
                    if(index_is_saving==0)
                    {
                        index_save_global_is=1;
                        index_do_quick_save=1;
                    }
                }
                else
                {
                    key_roi(1);
                }
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='S';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[28]);
            break;

        case KEY_T:
            if(index_type==0)
            {
                key_presetvideo(4);//les banques de tracking cam
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='T';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[29]);
            break;

        case KEY_U://inverse selection
            if (index_type==0)
            {
                key_select_inv();
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='U';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[30]);
            break;

        case KEY_V:
            if (index_type==0)
            {
                if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
                {
                    if(keyboardStorage_numeric_postext==0)
                    {
                        channel_paste();
                    }
                    else//si chiffre de mem tapée
                    {
                        index_copy_mem_in=1;
                        index_ask_confirm=1;

                    }
                }
                else
                {
                    //les aires de tracking cam
                    key_roi(9);
                }
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='V';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[31]);
            break;

        case KEY_Z://w
            if (index_type==0)
            {
                if(key_shifts )
                {
                    key_backward();
                }
                else //les aires de tracking cam
                {
                    key_roi(6);
                }
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='W';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[32]);
            break;

        case KEY_X:
            if (index_type==0)
            {
                if(key_shifts)
                {
                    key_forward();
                }

                else //les aires de tracking cam
                {
                    key_roi(7);
                }
            }
            else  if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='X';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[33]);
            break;

        case KEY_Y://select all

            if (index_type==0)
            {
                key_select_all();
            }
            else if (index_type==1)
            {
                numeric[keyboardStorage_numeric_postext]='Y';
                keyboardStorage_numeric_postext++;
            }
            sprintf(string_key_id,list_keyname[34]);
            break;

        case KEY_W://z
            if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
            {
                //ctrl Z reload mem as recorded
                index_do_reload_mem=1;
                index_ask_confirm=1;
            }
            else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
            {
                //ctrl Z resurrect mem as recorded
                mem_to_resurrect=(int)(atof(numeric)*10);
                index_do_resurrect_mem=1;
                index_ask_confirm=1;
            }
            else
            {
                if (index_type==0 )
                {
                    key_presetvideo(1);//les banques de tracking cam
                }
                else if (index_type==1)
                {
                    numeric[keyboardStorage_numeric_postext]='Z';
                    keyboardStorage_numeric_postext++;
                }
            }
            sprintf(string_key_id,list_keyname[35]);
            break;

        case KEY_LEFT:
            key_left();
            sprintf(string_key_id,list_keyname[36]);
            break;

        case KEY_RIGHT:
            key_right();
            sprintf(string_key_id,list_keyname[37]);
            break;

        case KEY_DEL:
            if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
            {
                reset_indexs_confirmation();
                index_do_delete_mem=1;
                index_ask_confirm=1;
            }
            break;
//////////////////////ENTREES NUMERIQUES COMMUNES//////////////////////////////////////////

        case KEY_0:
            numeric[keyboardStorage_numeric_postext]='0';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_0_PAD:
            numeric[keyboardStorage_numeric_postext]='0';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_1:
            numeric[keyboardStorage_numeric_postext]='1';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_1_PAD:
            numeric[keyboardStorage_numeric_postext]='1';
            keyboardStorage_numeric_postext++;
            break;

        case KEY_2:
            numeric[keyboardStorage_numeric_postext]='2';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_2_PAD:
            numeric[keyboardStorage_numeric_postext]='2';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_3:
            numeric[keyboardStorage_numeric_postext]='3';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_3_PAD:
            numeric[keyboardStorage_numeric_postext]='3';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_4:
            numeric[keyboardStorage_numeric_postext]='4';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_4_PAD:
            numeric[keyboardStorage_numeric_postext]='4';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_5:
            numeric[keyboardStorage_numeric_postext]='5';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_5_PAD:
            numeric[keyboardStorage_numeric_postext]='5';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_6:
            numeric[keyboardStorage_numeric_postext]='6';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_6_PAD:
            numeric[keyboardStorage_numeric_postext]='6';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_7:
            numeric[keyboardStorage_numeric_postext]='7';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_7_PAD:
            numeric[keyboardStorage_numeric_postext]='7';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_8:
            numeric[keyboardStorage_numeric_postext]='8';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_8_PAD:
            numeric[keyboardStorage_numeric_postext]='8';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_9:
            numeric[keyboardStorage_numeric_postext]='9';
            keyboardStorage_numeric_postext++;
            break;
        case KEY_9_PAD:
            numeric[keyboardStorage_numeric_postext]='9';
            keyboardStorage_numeric_postext++;
            break;

        case KEY_COMMA:
            numeric[keyboardStorage_numeric_postext]='.';
            keyboardStorage_numeric_postext++;
            break;

        case  KEY_DEL_PAD:
            numeric[keyboardStorage_numeric_postext]='.';
            keyboardStorage_numeric_postext++;
            break;

        case  KEY_M:
            numeric[keyboardStorage_numeric_postext]='.';
            keyboardStorage_numeric_postext++;
            break;


        case KEY_BACKSPACE:
            numeric[keyboardStorage_numeric_postext]=' ';
            keyboardStorage_numeric_postext--;
            numeric[keyboardStorage_numeric_postext]=' ';
            if (keyboardStorage_numeric_postext<0)
            {
                keyboardStorage_numeric_postext=0;
            }
            break;

////////////////////MISE EN MEMOIRES DES FENETRES ET TOGGLE/////////////////////
        case KEY_PRTSCR:
            key_printscreen();
            break;

        default:

            break;
        }
        for(int u=0; u<nbre_key_persos; u++)
        {
//keys persos
            if( (int)(chi & 0xff)==mapping_temporaire[u])
            {
                switch(u)
                {
                case 0://AT level
                    key_affectation();
                    sprintf(string_key_id,"At Level");//max 16 char
                    break;
                case 1://CH+
                    key_add_ch();
                    sprintf(string_key_id,"Ch +");//max 16 char
                    break;
                case 2://CH-
                    key_minus_ch();
                    sprintf(string_key_id,"Ch -");//max 16 char
                    break;
                case 3://CH THRUTH
                    key_thruth();
                    sprintf(string_key_id,"To Ch");//max 16 char
                    break;
                case 4://CLEAR
                    key_unselect_ch();
                    sprintf(string_key_id,"Clear");//max 16 char
                    break;
                default:
                    break;
                }
            }
        }




//protections

        if (keyboardStorage_numeric_postext>maxchar_numeric)
        {
            numeric[keyboardStorage_numeric_postext]=' ';
            keyboardStorage_numeric_postext=maxchar_numeric-1;
        }

        if (keyboardStorage_numeric_postext<0)
        {
            keyboardStorage_numeric_postext=0;
        }



    }
    sprintf(string_numeric_entry,"<< %s",numeric);


//CTRL-S
    if(index_do_quick_save==1 )
    {
        Save_Show();
        sprintf(string_Last_Order,">> Show Saved at %s", tmp_time);
        index_do_quick_save=0;
    }

    poll_keyboard();

    return(0);
}

