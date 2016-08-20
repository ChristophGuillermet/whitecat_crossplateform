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

* \file save_show_13.cpp
* \brief {save and load fonctions}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions de sauvegarde et de rappel
*
*   Save and Load fonctions
*
**/

//modes d enregistrement
const char file_save_preset[24]={"save_personnal_cfg.whc"};
unsigned int save_preset_size=80*4;//bool preset_specify_who_to_save_load[80][4];
const char file_save_pdf[24]={"save_pdf_cfg.whc"};
unsigned int save_pdf_size=36;//bool specify_who_to_save_PDF[36];


////FADERS
const char file_faders_state[24]={"fader_state.whc"};
unsigned int faders_saving_size=48;//usnigned char Fader[48]
const char file_dock_selected[24]={"fader_dock_select.whc"};
unsigned int dock_selected_size=48*6;//bool DockIsSelected[48][6];
const char file_dock_type[24]={"fader_dock_type.whc"};
unsigned int dock_type_size=48*6;//unsigned char DockTypeIs[48][6];
const char file_dock_net[24]={"fader_dock_net.whc"};
unsigned int dock_net_size=48*6; //unsigned char DockNetIs[48][6]; // numero Universe artnet(0 à 15)
const char file_dock_name[24]={"fader_dock_name.whc"};
unsigned int dock_name_size=48*6*25;//char DockName[48][6][25];
const char file_dock_channels[24]={"fader_dock_channels.whc"};
unsigned int dock_channels_size=48*6*514;//unsigned char FaderDockContains[48][6][514];
const char file_fader_locked[24]={"fader_locked.whc"};
unsigned int fader_locked_size=48;//bool FaderLocked[48];
const char file_fader_locked_full[24]={"fader_locked_full.whc"};
unsigned int fader_locked_full_size=48;//bool LockFader_is_FullLevel[48];
const char file_fader_before_lock[24]={"fader_before_lock.whc"};
unsigned int fader_before_lock_size=48;//unsigned char StateOfFaderBeforeLock[48];/
const char file_color_to_dock[24]={"fader_color_to_dock.whc"};
unsigned int fader_color_to_dock_size=16;//int colorpreset_linked_to_dock[8][2];
const char file_mem_to_dock[24]={"fader_mems_to_dock.whc"};
unsigned int fader_mem_to_dock_size=48*6;//int DockHasMem[48][6];
const char file_lock_preset_is[24]={"faders_lockpr_is.whc"};
unsigned int fader_lock_preset_is_size=8;//bool lock_preset[8];
const char file_lock_preset_state[24]={"faders_lockpr_state.whc"};
unsigned int fader_lock_preset_state_size=8*48;//bool FaderLocked_Preset[8][48];
const char file_lock_preset_masteris[24]={"faders_lockpr_mst.whc"};
unsigned int fader_lock_preset_masteris_size=8*48;//bool LockFader_is_FullLevel_Preset[8][48];
const char file_lock_preset_levels[24]={"faders_lockpr_lvl.whc"};
unsigned int fader_lock_preset_levels_size=8*48;//unsigned char StateOfFaderBeforeLock_Preset[8][48];
const char file_direct_channel[24]={"faders_direct_chan.whc"};
unsigned int fader_direct_chan_size=48*6;//int FaderDirectChan[48][6];
const char file_fader_audio[24]={"faders_audio.whc"};
unsigned int fader_audio_size=3*48*6;
/*
int DockHasAudioVolume[48][6];
int DockHasAudioPan[48][6];
int DockHasAudioPitch[48][6];*/
const char file_fader_stoppos_levels[24]={"faders_stopos_lvl.whc"};
unsigned int fader_stoppos_size=48;//unsigned char LevelStopPos[48];
const char file_fader_stoppos_is[24]={"faders_bstopos.whc"};
unsigned int fader_stopposB_size=48;//bool ActionnateStopOn[48]; // au cahrgement bien verifier les activations
const char file_fader_ston_is[24]={"faders_StOn.whc"};
unsigned int fader_ston_size=48;//bool StopPosOn[48]; //
const char file_fader_curve[24]={"faders_curve.whc"};
unsigned int fader_curve_size=48;//int FaderCurves[48]; //
const char file_fader_preset_selection[24]={"faders_prst_sel.whc"};
unsigned int fader_prst_sel_size=8*48;//bool minifaders_preset_selection[8][48];
const char file_chaser_to_fader[24]={"faders_chaser.whc"};
unsigned int fader_chaser_to_fader_size=48*6;//int ChaserAffectedToDck[48][6]
const char file_fader_chas_autolaunch[24]={"faders_chaz_auto.whc"};
unsigned int fader_chas_autolaucnh_size=48;//bool autolaunch[48]
const char file_fader_grid_affect[24]={"faders_grid_affect.whc"};
unsigned int fader_grid_affect_size=48*6;//int faders_dock_grid_affectation[48][6];
const char file_fader_fx[24]={"faders_fx.whc"};
unsigned int fader_fx_size=48;//int fader_mode_with_buffers[48]
const char file_fader_route_fx[24]={"faders_route_fx.whc"};
unsigned int fader_route_fx_size=48;//bool fader_fx_route[48];
const char file_fader_fgroup[24]={"faders_fgroups.whc"};
unsigned int fader_fgroup_size=48*6*48;//bool fgroup[48][6][48];
const char file_fader_draw[24]={"faders_draw.whc"};
unsigned int fader_draw_size=48*6;//int DrawAffectedToDck[48][6];//contenu des draws dans les docks
const char file_fader_echo[24]={"faders_echo.whc"};
unsigned int fader_echo_size=48*6;//int echo_affected_to_dock[48][6];//
const char file_fader_damper_on[24]={"faders_damper_on.whc"};
unsigned int fader_damper_on_size=48;//bool fader_damper_is_on[48]//
const char file_fader_damper_typ[24]={"faders_damper_typ.whc"};
unsigned int fader_damper_typ_size=48;//1x 48 tmp tableau set mod
const char file_fader_damper_levels[24]={"faders_damper_lvls.whc"};
int fader_damper_levels_size=96;//2x48 tmp 2 tableaux pour set decay et set dt en valeur 0 - 127

////COLORS
const char file_dock_color_type[24]={"dockcolor_typ.whc"};
unsigned int dock_color_type_size=8;//bool dock_color_type[8];//0 trichro 1 mode quadri
const char file_dock_color_xy[24]={"dockcolor_xy.whc"};
unsigned int dock_color_xy_size=8*2;//int x_y_picker_par_colordock[8][2];//stockage des coordonnes du picker par coordonnées
const char file_dock_color_angle[24]={"dockcolor_angle.whc"};
unsigned int dock_color_angle_size=8;//float angle_hue_par_colordock[8];//picker par coordonnées angles
const char file_dock_color_picker[24]={"dockcolor_picker.whc"};
unsigned int dock_color_picker_size=8*4;//int picker_trichro[8][4];//stockage des niveaux RVB YELLOW
const char file_dock_color_ch[24]={"dockcolor_ch.whc"};
unsigned int dock_color_ch_size=8*4*514;//bool dock_color_channels[8][4][514];//trichro sur curcuits
const char file_dock_color_buffer[24]={"dockcolor_buffer.whc"};
unsigned int dock_color_buffer_size=8*514;//unsigned char dock_color_buffer_C[8][514];//resultat dans buffers separés
/////VIDEO
const char file_video_description[24]={"videos_description.whc"};
unsigned int video_description_size=25*64;//char annote_my_video[25][64];
const char file_video_channels[24]={"video_channels.whc"};
unsigned int video_channels_size=6*12*512;//bool tracking_contents[6][12][512];//channel affectationconst char file_video_xy[24]={"video_xy.whc"};
const char file_video_xy[24]={"video_xy.whc"};
unsigned int video_xy_size=6*12*4;//int tracking_coordonates[6][12][4];//dock selected / tracker / x y largeur x largeur y
const char file_video_spaces_on[24]={"video_spaces_on.whc"};
unsigned int video_spaces_on_size=6*12;//bool tracking_spaces_on_off[6][12];//dock selected / tracker
const char file_camera_modes[24]={"camera_modes.whc"};
unsigned int camera_modes_size=8*16;//int camera_modes_and_settings[8][16];//ocv_calcul_mode /levels
//PATCH
const char file_patch_channels[24]={"patch_channels.whc"};
unsigned int patch_channels_size=514;//int Patch[514];
const char file_patch_ltp[24]={"patch_ltp.whc"};
unsigned int patch_ltp_size=514;//bool dimmer_type[514]; //0=HTP= 1 LTP
const char file_patch_curves[24]={"patch_curves.whc"};
unsigned int patch_curves_size=514;//int curves[513];
const char file_curve_ctrl_pt[24]={"curves_ctrl.whc"};
unsigned int curve_ctrl_size=16*8*2;//int curve_ctrl_pt[16][8][2];
const char file_curve_spline_level[24]={"curves_spline_level.whc"};
unsigned int curve_spline_level_size=16;//int the_curve_spline_level[16];
const char file_curve_matrix[24]={"curves_matrix.whc"};
unsigned int curve_matrix_size=16*256;//int curve_report[16][256];
//MIDI
const char file_midi_affectation[24]={"midi_affectation.whc"};
unsigned int midi_affectation_size=3*3072;//int miditable[3][3072];
const char file_midi_send_out[24]={"midi_send_out.whc"};
unsigned int midi_send_out_size=3072;//bool midi_send_out[3072];
const char file_midi_properties[24]={"midi_properties.whc"};
unsigned int midi_properties_size=16*128;//int midi_change_vel_type[16][128]
const char file_midi_clock[24]={"midi_clock.whc"};
int midi_clock_size=16;//int bpm_personnal[16]

//LFOS
const char file_dock_times[24]={"dock_times.whc"};
unsigned int dock_times_size=49*6*4;//float time_per_dock[49][6][4];//WAIT IN- IN - WAIT OUT- OUT -
const char file_is_for_loop_selected[24]={"dock_loop.whc"};
unsigned int size_is_for_loop_selected=49*6;//bool is_dock_for_lfo_selected[49][6]; // selection nbre de cycle du LFO loop
const char file_lfo_speed[24]={"lfo_speed.whc"};
unsigned int size_lfo_speed=49;//int lfo_speed[49];
const char file_lfo_mode_is[24]={"lfo_mode.whc"};
unsigned int size_lfo_mode_is=49;//int lfo_mode_is[49];// //0 NO LFO- 1 UP ONCE - 2 DOWN ONCE
const char file_lfo_cycle_on[24]={"lfo_cycle.whc"};
unsigned int size_lfo_cycle_on=49;//bool lfo_cycle_is_on[49];// SAW up down
const char file_lfo_do_next_step[24]={"lfo_next_step.whc"};
unsigned int size_lfo_do_next_step=49*2;//bool lfo_do_next_step[49][2]; // 0 backward 1 forward
const char file_lfo_loop_step[24]={"lfo_loop_step.whc"};
unsigned int size_lfo_loop_step=49;//bool bool lfo_cycle_steps[49];
//MEMOIRES
const char file_mem_existantes[24]={"memories_exists.whc"};
unsigned int mem_existantes_size=10000;
const char file_memories[24]={"memories.whc"};
unsigned int memories_size=10000*514;
const char file_text_mems[24]={"memories_txt.whc"};
unsigned int text_mems_size=10000*25;
const char file_text_annots[24]={"memories_notes.whc"};
unsigned int text_annots_size=10000*25;
const char file_times_mem[24]={"memories_times.whc"};
unsigned int times_mems_size=10000*4;
const char file_link_mem[24]={"memories_links.whc"};
unsigned int link_mem_size=10000;
const char file_banger_call_in_mem[24]={"memories_bangs.whc"};
unsigned int bang_mem_size=10000;
const char file_manual_ratio_mem[24]={"memories_manual.whc"};
unsigned int ratio_mem_size=10000;
const char file_mem_detruites[24]={"memories_isdeleted.whc"};
unsigned int mem_deleted_size=10000;
const char file_mem_exclues[24]={"memories_excluded.whc"};
unsigned int mem_exclues_size=10000;

///REPORT DE LA CONF FENETRES ALLUMEES / DMX VIEW ETC
const char file_divers_index[24]={"indexs.whc"};//les indexs dmx_view, fenetres allumées, etc...
unsigned int index_size=128;

const char file_windows[24]={"windows.whc"};
unsigned int windows_size=72;//int window_opened[64];//la liste des fenetres ouvertes
//POSITIONS FENETRES
const char file_pos_fenetres[24]={"user_windows.whc"};//position user etc...
unsigned int index_pos_fenetre_size=24*2;
//COLOR PROFILE USER
const char file_color_profile[24]={"user_color_profile.whc"};//position user etc...
unsigned int color_profile_size=12*3;

//LISTE PROJECTEURS et vues
const char file_spotlist[24]={"spots_list.whc"};//position user etc...
unsigned int spotlist_size=514*25;

const char file_chview_ch[24]={"ch_views_ch.whc"};//VIEW CHANNEL
unsigned int chview_ch_size=514*nbre_de_vues_circuits;//int Channel_View_ROUTING[16][514];
const char file_chview_name[24]={"ch_views_name.whc"};//VIEW CHANNEL
unsigned int chview_name_size=25*nbre_de_vues_circuits;//char channel_view_Name[16][25];
const char file_chview_linktype[24]={"ch_views_lnkt.whc"};//VIEW CHANNEL
unsigned int chview_linktype_size=nbre_de_vues_circuits;//int channel_view_link_type[16];//0:no link 1:memory 2: fader
const char file_chview_linkref[24]={"ch_views_lnkr.whc"};//VIEW CHANNEL
unsigned int chview_linkref_size=nbre_de_vues_circuits;//int channel_viex_link_ref[16];//num de mem ou de fader. desaffectation=-1;
const char file_chview_view[24]={"ch_views_view.whc"};//VIEW CHANNEL
unsigned int chview_view_size=nbre_de_vues_circuits;//int bool Channel_View_MODE[16];//les 16 indexes de vision

//channel macros
const char file_chan_macro_on[24]={"chan_macro_onoff.whc"};//
unsigned int chan_macro_on_size=514*4; //bool macro_channel_on[514][4]

const char file_chan_macro_reaction[24]={"chan_macro_reac.whc"};//
unsigned int chan_macro_reaction_size=514*4; //int channel_macro_reaction[514][4];

const char file_chan_macro_action[24]={"chan_macro_act.whc"};//
unsigned int chan_macro_action_size=514*4; //int channel_macro_action[514][4];

const char file_chan_macro_val[24]={"chan_macro_val.whc"};//
unsigned int chan_macro_val_size=514*4*2; //int channel_macro_val[514][4][2];




//FREEZE STATE
const char file_dofreeze[24]={"ch_dofreeze.whc"};//position user etc...
unsigned int dofreeze_size=514;
const char file_freeze_state[24]={"ch_freezestate.whc"};//position user etc...
unsigned int freezestate_size=514;
const char file_excluded_chan[24]={"ch_exclude_GM.whc"};//exclusion de l'action du grand master
unsigned int excluded_chan_size=514; //bool Channels_excluded_from_grand_master[514];
//////////BANGER///////////////////////////////////////
const char file_bangers_names[24]={"banger_names.whc"};//
unsigned int banger_name_size=128*25;//char bangers_name[128][25];//128 bangers
const char file_bangers_types[24]={"banger_types.whc"};//
unsigned int banger_types_size=128*6;//int bangers_type[128][6];//128 bangers // 6 events par banger
const char file_bangers_actions[24]={"banger_actions.whc"};//
unsigned int banger_actions_size=128*6;//int bangers_action[128][6];//num action demandée
const char file_bangers_values[24]={"banger_values.whc"};//
unsigned int banger_values_size=128*6*2;//int bangers_params[128][6][2];//0 param1 / 1 param2
const char file_bangers_times[24]={"banger_times.whc"};//
unsigned int banger_times_size=128*6*2;//int bangers_delay[128][6];//delays
const char file_bangers_alarms[24]={"banger_alarms.whc"};//
unsigned int banger_alarm_size=128*25;//char string_alarm[128][25];//une alarm par banger
const char file_bangers_loop[24]={"banger_doloop.whc"};//
unsigned int banger_loop_size=128;//bool do_loop_banger[128]
const char file_bangers_looptime[24]={"banger_looptime.whc"};//
unsigned int banger_looptime_size=128;//bool time_loop_banger[128]
///////////ARDUINO///////////////////////////////
const char file_arduino_dig_typ[24]={"arduino_IO_typ.whc"};//
unsigned int arduino_dig_typ_size=128;//int arduino_digital_type[128]
const char file_arduino_dig_affect[24]={"arduino_IO_aff.whc"};//
unsigned int arduino_dig_aff_size=128*2;//arduino_digital_function_input[128][2];//Action // Val
const char file_arduino_an_typ[24]={"arduino_AN_typ.whc"};//
unsigned int arduino_an_typ_size=64;//int arduino_analog_function_input[64];
const char file_arduino_an_aff[24]={"arduino_AN_aff.whc"};//
unsigned int arduino_an_aff_size=64;//int arduino_analog_attribution_input[64];
const char file_arduino_an_on[24]={"arduino_AN_ON.whc"};//
unsigned int arduino_an_on_size=64;//bool ventilate_analog_data[64];
const char file_arduino_pwm_aff[24]={"arduino_PWM_typ.whc"};//
unsigned int arduino_pwm_aff_size=36*2;//int arduino_pwm_function_input[36][2];//Action // Val  fader
const char file_arduino_dig_out[24]={"arduino_PWM_typ.whc"};//
unsigned int arduino_dig_out_size=128*2;//int int arduino_digital_function_output[128][2];//Action // Val  ch/fader
const char file_arduino_kalman_param[24]={"arduino_Kalman.whc"};//
unsigned int arduino_kalman_param_size=128*3;//double kalman_params[3][analog_limit];
const char file_arduino_kalman_on[24]={"arduino_Kalman_on.whc"};//
unsigned int arduino_kalman_on_size=12;//bool kalman_is_on[analog_limit];

////////////////CHASERS//////////////////////////////
const char file_chaser_name[24]={"chaser_name.whc"};
unsigned int chaser_name_size=128*25;//char chaser_name[128][25];
const char file_chaser_timeunit[24]={"chaser_timeunit.whc"};
unsigned int chaser_timeunit_size=128;//float time_unit[128];
const char file_chaser_stepop[24]={"chaser_step_op.whc"};
unsigned int chaser_stepop_size=128*24*36;//int chaser_step_operation[128][24][36];//0= rien 1= up 2= stay 3=down
const char file_chaser_play[24]={"chaser_playing.whc"};
unsigned int chaser_isplaying_size=128;//bool chaser_is_playing[128];
const char file_chaser_loop[24]={"chaser_loop.whc"};
unsigned int chaser_loop_size=128;//bool chaser_is_in_loop[128];
const char file_chaser_way[24]={"chaser_way.whc"};
unsigned int chaser_way_size=128;//bool chaser_way[128];//0= left to right 1= right to left
const char file_chaser_allerretour[24]={"chaser_allerretour.whc"};
unsigned int chaser_allerretour_size=128;//bool chaser_aller_retour[128];//
const char file_chaser_trackon[24]={"chaser_track_on.whc"};
unsigned int chaser_trackon_size=128*24;//bool track_is_on[128][24];
const char file_chaser_tracklevel[24]={"chaser_track_level.whc"};
unsigned int chaser_track_level_size=128*24;//int track_level[128][24];
const char file_chaser_trackview[24]={"chaser_trackview.whc"};
unsigned int chaser_trackview_size=128;//int position_affichage_track_num[128];
const char file_chaser_tracktype[24]={"chaser_tracktype.whc"};
unsigned int chaser_tracktype_size=128*24;//int TrackTypeIs[128][24];
const char file_chaser_trackcontent[24]={"chaser_trackcontent.whc"};
unsigned int chaser_trackcontent_size=128*24*514;//int  TrackContains[128][24][514];
const char file_chaser_stepis[24]={"chaser_stepis.whc"};
unsigned int chaser_stepis_size=128;//int chaser_step_is[128]
const char file_chaser_beginstep[24]={"chaser_step_beg.whc"};
unsigned int chaser_stepbeg_size=128;//int chaser_begin_step_is[128]
const char file_chaser_endstep[24]={"chaser_step_end.whc"};
unsigned int chaser_stepend_size=128;//int chaser_end_step_is[128]
const char file_chaser_timemode[24]={"chaser_timemode.whc"};
unsigned int chaser_timemode_size=128;//bool chaser_time_mode[128];
const char file_chaser_lastaffect[24]={"chaser_last_affect.whc"};
unsigned int chaser_lastaffect_size=128*2;//int view_chaser_affected_to_fader[128][2];
const char file_chaser_trrackname[24]={"chaser_tracksname.whc"};
unsigned int chaser_tracksname_size=128*24*25;//char chaser_track_name[128][24][25];
const char file_chaser_presets[24]={"chaser_presets.whc"};
unsigned int chaser_presets_size=128*4*24;//bool chaser_preset[128][4][24];
const char file_chaser_lchpad_pos[24]={"chaser_lchpad_pos.whc"};
unsigned int chaser_lchpad_pos_size=128;//int chaser_step_launchpad[128];
const char file_chaser_acceleroslave[24]={"chaser_accelslave.whc"};
unsigned int chaser_acceleroslave_size=128;//bool index_slave_chaser_to_accelerometre[128];
const char file_chaser_has_mem[24]={"chaser_has_mem.whc"};
unsigned int chaser_has_mem_size=128*24;//int TrackHasMem[128][24];
//////////////KEYBOARD ASCII MAPING///////////////////////////////////////////
const char file_kbd_ascii_map[24]={"kbd_map_ascii.whc"};//
unsigned int kbd_ascii_map_size=128;//int mapping_temporaire[128];//la table de reroutage


///audio
const char file_audio_autoloadpause[24]={"audio_autoloadpause.whc"};//
unsigned int audio_autoloadpause_size=2*4;// bool audio_autoload[4]; bool audio_autopause[4];//
const char file_audio_filenumber[24]={"audio_filenumber.whc"};//
unsigned int audio_filenumber_size=4;//int player_has_file_coming_from_pos[4];//position 1 à 127
const char file_audio_playerposition[24]={"audio_plposition.whc"};//
unsigned int audio_playerposition_size=4;//player_position_on_save[4]

/////////////////ICAT//////////////////////////////////////////////////
const char file_icat_nbsliders[24]={"icat_nbsliders.whc"}; //int iCat_nbre_de_sliders[8];
unsigned int icat_nbsliders_size=8;
const char file_icat_posliders[24]={"icat_posliders.whc"}; //int iCat_pos_slider[8][24][2];//x y
unsigned int icat_posliders_size=8*48*2;
const char file_icat_orsliders[24]={"icat_orsliders.whc"}; //bool iCat_orientation_slider[8][24];//0 vertical 1 horizontal
unsigned int icat_orsliders_size=8*48;
const char file_icat_typsliders[24]={"icat_typsliders.whc"}; //int iCat_affectation_slider_type_is[8][24];//type 1 faders, 2 sequentiel, 3 audio family
unsigned int icat_typsliders_size=8*48;
const char file_icat_valsliders[24]={"icat_valsliders.whc"}; //int iCat_affectation_slider_value_is[8][24];//valeur de la famille 1/48 stage/preset/accel
unsigned int icat_valsliders_size=8*48;
const char file_icat_size_sliders[24]={"icat_sizesliders.whc"};//int ratio_iCat_slider[8][24];//multiplicateur des proportions de sliders. 1 / 2 / 3
unsigned int icat_sizesliders_size=8*48;
const char file_icat_orientpage[24]={"icat_or_page.whc"};//int iCat_preset_orientation[8];
unsigned int icat_orpage_size=8;


const char file_icat_nbbutton[24]={"icat_nbbutton.whc"}; //int iCat_nbre_de_boutons[8];//max 48 par preset
unsigned int icat_nbbutton_size=8;
const char file_icat_pobutton[24]={"icat_pobutton.whc"}; //int iCat_pos_bouton[8][48][2];//x y
unsigned int icat_pobutton_size=8*48*2;
const char file_icat_size_buttons[24]={"icat_sizebutton.whc"};//int ratio_iCat_button[8][48];//multiplicateur des proportions du bouton. 1 / 2 / 3
unsigned int icat_sizebuttons_size=8*48;
const char file_icat_typbutton[24]={"icat_typbutton.whc"}; //int iCat_affectation_bouton_type_is[8][48];//type faders, sequentiel, audio family
unsigned int icat_typbutton_size=8*48;
const char file_icat_actbutton[24]={"icat_actbutton.whc"}; //int iCat_affectation_bouton_action_is[8][48];//action par type: UP DOWN GO GO BACK etc
unsigned int icat_actbutton_size=8*48;
const char file_icat_valbutton[24]={"icat_valbutton.whc"}; //int iCat_affectation_bouton_value_is[8][48];//valeur de la famille 1/48 stage/preset/accel etc
unsigned int icat_valbutton_size=8*48;


const char file_icat_nbstr[24]={"icat_nbstrings.whc"}; //int iCat_nbre_de_strings[8];//max 24
unsigned int icat_nbstr_size=8;
const char file_icat_posstr[24]={"icat_posstring.whc"}; //int iCat_pos_string[8][24][2];//x y
unsigned int icat_posstr_size=8*24*2;
const char file_icat_sizestr[24]={"icat_sizestr.whc"}; //int ratio_iCat_string[8][24];//multiplicateur des proportions du bouton. 1 / 2 / 3
unsigned int icat_sizestr_size=8*24;
const char file_icat_typstr[24]={"icat_typstr.whc"}; //int iCat_affectation_string_type_is[8][24];//type string: feedback / sequenciel mems
unsigned int icat_typstr_size=8*24;
const char file_icat_actstr[24]={"icat_actstr.whc"}; //int iCat_affectation_string_action_is[8][24];//
unsigned int icat_actstr_size=8*24;
const char file_icat_valstr[24]={"icat_valstr.whc"}; //int iCat_affectation_string_value_is[8][24];
unsigned int icat_valstr_size=8*24;


const char file_icat_nbzon[24]={"icat_nbtrckz.whc"}; //int  iCat_nbre_de_tracking_zone[8];//max 8
unsigned int icat_nbzon_size=8;
const char file_icat_poszon[24]={"icat_postrckz.whc"}; //int iCat_pos_trackzone[8][8][2];//x y
unsigned int icat_poszon_size=8*8*2;
const char file_icat_sizezon[24]={"icat_sizetrckz.whc"}; //int ratio_iCat_trackzone[8][8];//multiplicateur des proportions du bouton. 1 / 2 / 3
unsigned int icat_sizezon_size=8*8;
const char file_icat_typzon[24]={"icat_typtrckz.whc"}; //int iCat_trackzone_type_is[8][8];//type: fadre speed mover x mover y
unsigned int icat_typzon_size=8*8;
const char file_icat_valzon[24]={"icat_valtrckz.whc"}; //int iCat_trackzone_affectation_is[8][8];
unsigned int icat_valzon_size=8*8;
const char file_icat_posTRCKzon[24]={"icat_posTRCK.whc"}; //int pos_iCat_tracker[8][8][2];
unsigned int icat_posTRCKzon_size=8*8*2;
//////////////////TRACKER///////////////////////////////////////////////////////

const char file_mover_mem[24]={"mover_mems.whc"};
const char file_mover_mem16b[24]={"mover_mems_16b.whc"};
unsigned int mover_mem_saving_size=32*48*2;
const char file_asservis_mem[24]={"asservis_mems.whc"};
unsigned int mover_asservis_saving_size=32*48*16;
const char file_mover_numbersteps[24]={"mover_stepsmax.whc"};
const char file_mover_stepis[24]={"mover_stepis.whc"};
unsigned int mover_little_32file_size=32;
const char file_mover_time[24]={"mover_times.whc"};//stockage des temps par time
unsigned int mover_time_size=32*48;
int valeurs_diverses[32]; //pour stocker petites valeurs en sauvegarde ( pb lecture fp)
const char file_mover_divers[24]={"mover_divers.whc"};
const char file_mover_spline_ratio[24]={"mover_spline.whc"};
const char file_mover_autostop[24]={"mover_autostop.whc"};
unsigned int mover_autostop_size=32*48;
const char file_mover_goto[24]={"mover_goto.whc"};
unsigned int mover_goto_size=32*48;
const char file_mover_into[24]={"mover_into.whc"};
const char file_mover_params[24]={"mover_params.whc"};
unsigned int mover_param_size=32;//int mover_params_adresses[32];
/////////////GRID////////////////////////////////////////////////////////////////

//les grilles en plusieurs fichiers, beaucoup trop lourds les datas en écriture chargement !
const char file_grid_levels_1[24]={"grids_levels_1.whc"};
const char file_grid_levels_2[24]={"grids_levels_2.whc"};
const char file_grid_levels_3[24]={"grids_levels_3.whc"};
const char file_grid_levels_4[24]={"grids_levels_4.whc"};
unsigned int grid_levels_size=32*1024*513;//unsigned char grid_levels[128][1024][513];128/4

const char file_grid_times[24]={"grids_times.whc"};
unsigned int grid_times_size=128*1024*4;//float grid_times[128][1024][4];//0=DIN 1=IN 2=DOUT 3=OUT
const char file_grid_goto[24]={"grids_goto.whc"};
unsigned int grid_goto_size=128*1024*2;//int grid_goto[128][1024][2];//0 grid 1 step
const char file_grid_seekpos[24]={"grids_seekpos.whc"};
unsigned int grid_seekpos_size=128*1024;//int grid_seekpos[128][1024];//step seek pos
const char file_grid_stoplay[24]={"grids_stoplay.whc"};
unsigned int grid_stoplay_size=128*1024;//bool grid_stoplay[128][1024];//1=pause
const char file_grid_names[24]={"grids_names.whc"};
unsigned int grid_names_size=128*25;//char grider_name[128][25];

//les grids players
const char file_gridpl_grid[24]={"gridpl_grid.whc"};
//int index_grider_selected[4];
const char file_gridpl_step[24]={"gridpl_step.whc"};
//int index_grider_step_is[4];
const char file_gridpl_autost[24]={"gridpl_autost.whc"};
//bool grider_autostopmode[4];
const char file_gridpl_goto[24]={"gridpl_goto.whc"};
//bool grider_goto_mode[4];
const char file_gridpl_seekto[24]={"gridpl_seekto.whc"};
//bool grider_seekto_mode[4];
const char file_gridpl_stpl[24]={"gridpl_stpl.whc"};
//bool grider_stoplay_mode[4];reset_error_on_save_load();
const char file_gridpl_slave[24]={"gridpl_slave.whc"};
//bool grid_player_slave[4];
const char file_gridpl_show[24]={"gridpl_show.whc"};
//bool index_show_grid_player[4];
const char file_gridpl_accel[24]={"gridpl_accel.whc"};
//int grid_crossfade_speed[4];
const char file_gridpl_countmod[24]={"gridpl_count.whc"};
//bool grider_count_mode[4];
unsigned int gridpl_size=4;//une seule et meme taille pour les 4 players
const char file_gridpl_crosslv[24]={"gridpl_crosslv.whc"};
unsigned int gridpl_croslv_size=4*2;//int grid_niveauX1[pl]=255;grid_niveauX2[pl]=0; puis report en grid_floatX1[pl]=255.0 et grid_floatX2[pl]=0;
const char file_grid_in_mems[24]={"gridpl1_in_mems.whc"};
unsigned int grid_in_mems_size=10000;
const char file_gridpl_snapfader[24]={"gridpl_snapfader.whc"};
unsigned int gridpl_snapfader_size=4;//int GplSnapFader[4];;

const char file_grid_count[24]={"grid_count.whc"};
unsigned int grid_count_size=1024*128;//int grid_count[128][1024];
const char file_grided_count[24]={"grid_counted.whc"};
unsigned int grid_counted_size=1024*128;//int grid_counted_times[128][1024];//index de comptage fait



//la config
const char file_grider_conf[24]={"grider_conf.whc"};
unsigned int grider_conf_size=3;//int grider_conf[3];//begin chan X Y col row

//PLOT
//librairies symbol
const char file_lib_sizes_symbol[24]={"plot_lib_sizes.whc"};
unsigned int lib_sizes_symbol_size=127;//float size_symbol[127];
const char file_lib_names_symbol[24]={"plot_lib_names.whc"};
unsigned int lib_names_symbol_size=127*25;//char symbol_nickname[127][25];
//plot
const char file_plot_angles[24]={"plot_angles.whc"};
unsigned int plot_angle_size=4*nbre_symbol_per_layer;//float angle_symbol[4][nbre_symbol_per_layer];
const char file_plot_positions[24]={"plot_positions.whc"};
unsigned int plot_positions_size=4*nbre_symbol_per_layer*2;//int pos_symbol[4][nbre_symbol_per_layer][2];
const char file_plot_nbr_symbols[24]={"plot_nbr_symbols.whc"};
unsigned int plot_nbr_symbols_size=4;//int nbre_symbols_on_plot[4];
const char file_plot_typ[24]={"plot_typ.whc"};
unsigned int plot_typ_size=4*nbre_symbol_per_layer;//int symbol_type[4][nbre_symbol_per_layer];
const char file_plot_chan[24]={"plot_chan.whc"};
unsigned int plot_chan_size=4*nbre_symbol_per_layer;//int symbol_channel_is[4][nbre_symbol_per_layer];
const char file_plot_dim[24]={"plot_dim.whc"};
unsigned int plot_dim_size=4*nbre_symbol_per_layer;//int symbol_dimmer_is[4][nbre_symbol_per_layer];
const char file_plot_gels[24]={"plot_gels.whc"};
unsigned int plot_gels_size=4*nbre_symbol_per_layer*3;//int gelat[4][nbre_symbol_per_layer][3];
const char file_plot_gels_t[24]={"plot_gels_t.whc"};
unsigned int plot_gels_t_size=4*nbre_symbol_per_layer*3;//int gelat_family[4][nbre_symbol_per_layer][3];
const char file_plot_view[24]={"plot_view.whc"};
unsigned int plot_view_size=4;//bool show_calc_number[4];
const char file_plot_options_view[24]={"plot_opt_view.whc"};
unsigned int plot_view_options_size=12;//bool plot_show_options[12];//affichage du circuit, etc etc)
const char file_plot_opt_xy[24]={"plot_opt_xy.whc"};
unsigned int plot_opt_xy_size=4*nbre_symbol_per_layer*4*2;//relatif_plot_xy[4][nbre_symbol_per_layer][4][2];

const char file_plot_shape_type[24]={"plot_shape_type.whc"};
unsigned int plot_shape_type_size=nbre_symbol_per_layer;//int shape_type[nbre_symbol_per_layer];
const char file_plot_shape_attr[24]={"plot_shape_attr.whc"};
unsigned int plot_shape_attr_size=nbre_symbol_per_layer*5;//float shape_attributes[nbre_symbol_per_layer][5];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
const char file_plot_shape_pos[24]={"plot_shape_pos.whc"};
unsigned int plot_shape_pos_size=nbre_symbol_per_layer*4;//int shape_position[nbre_symbol_per_layer][4];//pour les lignes
const char file_plot_shape_legend_name[24]={"plot_shape_names.whc"};
unsigned int plot_shape_legend_name_size=nbre_symbol_per_layer*25;//char shape_legend_name[nbre_symbol_per_layer][25];
const char file_plot_shape_relativ_xy[24]={"plot_shape_r_xy.whc"};
unsigned int plot_shape_relativ_xy_size=nbre_symbol_per_layer*2;//int shape_relativ_position_legend_name[nbre_symbol_per_layer][2];
const char file_plot_shape_color_type[24]={"plot_shape_color.whc"};
unsigned int plot_shape_color_type_size=nbre_symbol_per_layer;//int shape_color_type[nbre_symbol_per_layer];
const char file_plot_shape_groups[24]={"plot_shapes_groups.whc"};
unsigned int plot_shape_groups_size=nbre_symbol_per_layer;//int shape_groups[nbre_symbol_per_layer]
const char file_plot_symbols_relativgroups[24]={"plot_symb_xygroups.whc"};
unsigned int plot_symbols_relativgroups_size=8*4*2;//int plot_relativxy_preset[8][4][2];
const char file_plot_symbols_notes[24]={"plot_symb_notes.whc"};
unsigned int plot_symbols_notes_size=4*nbre_symbol_per_layer*4*25;//char symbol_note[4][nbre_symbol_per_layer][4][25];
const char file_plot_legend[24]={"plot_legend.whc"};
unsigned int plot_legend_size=40*25;//char plot_renseignements[40][25];
const char file_plot_symb_linked[24]={"plot_symblink.whc"};
unsigned int plot_symb_linked_size=4*nbre_symbol_per_layer;//int symbol_is_linked_to[4][nbre_symbol_per_layer];//couplage de projos


//DRAW
const char file_draw_presetsz[24]={"draw_presetsz.whc"};
unsigned int draw_presetsz_size=6*2;//int draw_preset_parameters[6][2];//grilles de max 25x20 Taille nbre col nbre lignes
const char file_draw_levels[24]={"draw_levels.whc"};
unsigned int draw_levels_size=6*500;//float draw_preset_levels[6][500];
const char file_draw_chrouting[24]={"draw_chrouting.whc"};
unsigned int draw_chrouting_size=6*500;//int draw_preset_channel_routing[6][500];

//ECHO
const char file_echo_pointing_fader[24]={"echo_take_fader.whc"};
unsigned int echo_pointing_fader_size=24;//int echo_pointing_fader_num[24];//le fader pointé
const char file_echo_echo_mode[24]={"echo_echo_mode.whc"};
unsigned int echo_echo_mode_size=24;//bool echo_is_echo_mode[24];//0= bounce mode 1= continuous Echo mode
const char file_echo_global_param[24]={"echo_global_specs.whc"};
unsigned int echo_global_param_size=24*3;//float echo_global_params[24][3];
const char file_echo_channel_man_mode[24]={"echo_channel_mode.whc"};
unsigned int echo_channel_man_mode_size=24;//bool echo_channel_manipulate_mode[24];// 0 level up, 1 ground
const char file_echo_chan_pos[24]={"echo_chan_pos.whc"};//
unsigned int echo_chan_pos_size=24;//int echo_grid_channel_position[24];
const char file_echo_levels[24]={"echo_levels.whc"};
unsigned int echo_levels_size=24*2*513;//float echo_levels[24][3][513];
const char file_echo_bounce[24]={"echo_bouncing.whc"};
unsigned int echo_bounce_size=24;//bool do_bounce[24]
const char file_echo_presets[24]={"echo_presets.whc"};
unsigned int echo_presets_size=24*513;//float snap_echo_to_recall[24][513];


//WAVE
const char file_wave_ch_slots[24]={"wave_channels.whc"};
int wave_ch_slots_size=26*4;//int channel_slots[4][26];
const char file_wave_brush_slots[24]={"wave_brush.whc"};
int wave_brush_slots_size=26*4;//float brush_slots[4][26];
const char file_wave_brush_pr[24]={"wave_brush_pr.whc"};
int wave_brush_pr_size=4;//int lead_brush_reading[4];
const char file_wave_damp_decay[24]={"wave_dampers.whc"};
int wave_damp_decay_size=2;//2 float delte et decay reporté sur les 26
////////////////////////////////////////////////////////////////////////////////
/**
Set Global mondirectory : Execution directory
 - Détermine mondirectory : le répertoire d'exécution
**/
void On_Open_name_of_directory()
{
//sab 02/03/2014    get_executable_name(mondirectory,sizeof(mondirectory));
//sab 02/03/2014    replace_filename(mondirectory,mondirectory,"",sizeof(mondirectory));
	char localTempChar[512];
	get_executable_name(localTempChar,sizeof(localTempChar));
	replace_filename(localTempChar,localTempChar,"\0",sizeof(localTempChar));
	strcpy(mondirectory,localTempChar) ;
}





int get_current_time()
{
      time_t timestamp;
      struct tm * t;
      timestamp = time(NULL);
      t = localtime(&timestamp);


      sprintf(tmp_time,"%02uh %02umin %02usec", t->tm_hour, t->tm_min, t->tm_sec);

 return(0);
}


int load_gel_list_numerical()
{
//sprintf(rep,"%s\\",mondirectory);
//chdir(rep);
sprintf(rep,"%s\\ressources",mondirectory);
chdir(rep);
volatile bool index_ok=1;
char line [256];
char tmp_name_of_mark[72];
char tmp_name_of_gel[96];
int tmp_ref=0;
int tmprvb[3];
int index_type_of_gel=-1;
int marker_de_gel[4];
float transmission=-1;;
for(int i=0;i<4;i++)
{
marker_de_gel[i]=0;
}

FILE *f=NULL;


if ((f=fopen("gel_list_num_order.txt", "rt"))== NULL)
{
    sprintf(string_save_load_report[0],"Error opening %s","gel_list_num_order.txt"); b_report_error[0]=1;
    idf++;
}
else
    {
	do {
		if (fgets(line,256,f)!=NULL)
		{
		sscanf(line,"%s\t%d\t%s\t%d\t%d\t%d\t%f\n",&tmp_name_of_mark,&tmp_ref,&tmp_name_of_gel,&tmprvb[0],&tmprvb[1],&tmprvb[2],&transmission);

        if(strcmp(tmp_name_of_mark,"Lee")==0){index_type_of_gel=0;}
        if(strcmp(tmp_name_of_mark,"Rosco")==0){index_type_of_gel=1;}
        if(strcmp(tmp_name_of_mark,"GamColor")==0){index_type_of_gel=2;}
        if(strcmp(tmp_name_of_mark,"Apollo")==0){index_type_of_gel=3;}

        if(marker_de_gel[index_type_of_gel]<10000 && index_type_of_gel>=0 && index_type_of_gel<=3 )
        {

        refs_of_gels[index_type_of_gel][marker_de_gel[index_type_of_gel]]=tmp_ref; //numerical reference
        sprintf(name_of_gels[index_type_of_gel][marker_de_gel[index_type_of_gel]],tmp_name_of_gel);//nom des gels
        for(int i=0;i<3;i++)
        {
            rvb_of_gels[index_type_of_gel][(marker_de_gel[index_type_of_gel])][i]=tmprvb[i];//rvb of gels
        }
        gel_transimission[index_type_of_gel][marker_de_gel[index_type_of_gel]]=transmission;
        marker_de_gel[index_type_of_gel]++;
        }
        //reset values
        transmission=-1;
        if(strcmp(line,"ENDDATA")==0){index_ok=0;}
		}
		else break;
	}
	while (index_ok!=0);

}

sprintf(rep,"%s\\",mondirectory);
chdir(rep);
return(0);
}



int Show_report_save_load()
{
Rect Report_Save_Load(Vec2D(report_SL_X, report_SL_Y), Vec2D( 350,160));
Report_Save_Load.SetRoundness(15);
Report_Save_Load.SetLineWidth(epaisseur_ligne_fader*3);
Report_Save_Load.Draw(CouleurFond);
Report_Save_Load.DrawOutline(CouleurLigne);
if(window_focus_id==W_SAVEREPORT){Report_Save_Load.DrawOutline(CouleurFader);}

//+ minus debug
//Plus Minus buttons debug show
Rect MinusPosMyRep(Vec2D(report_SL_X+290,report_SL_Y+76),Vec2D(50,20));
MinusPosMyRep.SetRoundness(7.5);
MinusPosMyRep.SetLineWidth(epaisseur_ligne_fader);
Rect PlusPosMyRep(Vec2D(report_SL_X+290,report_SL_Y+106),Vec2D(50,20));
PlusPosMyRep.SetRoundness(7.5);
PlusPosMyRep.SetLineWidth(epaisseur_ligne_fader);

for(int co=0;co<10;co++)
{
Rect AlarmFile(Vec2D((report_SL_X+5),(report_SL_Y+52+(10*co))),Vec2D(300,12));
AlarmFile.SetRoundness(5);
if(b_report_error[co+position_view_line]==1)
{
 AlarmFile.Draw(Rgba::RED.WithAlpha(alpha_blinker));
}
petitchiffre.Print( ol::ToString(co+position_view_line),(report_SL_X+5), (report_SL_Y+60+(10*co)));
petitchiffre.Print( string_save_load_report[co+position_view_line],(report_SL_X+30), (report_SL_Y+60+(10*co)));
}

MinusPosMyRep.Draw(CouleurFond);
PlusPosMyRep.Draw(CouleurFond);
if(window_focus_id==W_SAVEREPORT)
{
if(mouse_x>report_SL_X+290 && mouse_x<report_SL_X+340)
{

//-
 if( mouse_y>report_SL_Y+76 && mouse_y<report_SL_Y+96)
 {
  MinusPosMyRep.Draw(CouleurSurvol);
  if(mouse_button==1 &&  mouse_released==0 )
  {
  MinusPosMyRep.Draw(CouleurFader);
  position_view_line-=5;
  if(position_view_line<0) {position_view_line=0;  }
  }
 }
//+
 if( mouse_y>report_SL_Y+106 && mouse_y<report_SL_Y+136)
 {
  PlusPosMyRep.Draw(CouleurSurvol);
  if(mouse_button==1 &&  mouse_released==0 )
  {
  PlusPosMyRep.Draw(CouleurFader);
  position_view_line+=5;
  if(position_view_line>(255-10)) {position_view_line=(255-10);  }
  }
 }

}

}

MinusPosMyRep.DrawOutline(CouleurLigne);
PlusPosMyRep.DrawOutline(CouleurLigne);
petitchiffre.Print("line -",report_SL_X+300, report_SL_Y+90);
petitchiffre.Print("line +",report_SL_X+300, report_SL_Y+120);




petitchiffre.Print( mondirectory,(report_SL_X+10+90), (report_SL_Y+20));
petitchiffre.Print( nomduspectacle,(report_SL_X+10+90), (report_SL_Y+35));


return(0);
}




int load_onstart_config()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("user/config_onstart.txt", "rt" );
	if( !cfg_file )
	{
	 sprintf(string_save_load_report[idf],"!config_onstart.txt");
	}
	else
	{
    //premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! config_onstart.txt");
	}

	fscanf( cfg_file , "%d / %d / %d / %d /\n" ,  &camera_on_open, &open_arduino_on_open , &enable_iCat, &expert_mode);

	fclose( cfg_file );
    }
return(0);
}

int load_screen_config()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("user/config_screens.txt", "rt" );
	if( !cfg_file )
	{
	 sprintf(string_save_load_report[idf],"!config_screens.txt");
	}
	else
	{
    //premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! config_screens.txt");
	}

	fscanf( cfg_file , "%d / %d %d / %d %d /\n" ,  &index_fullscreen, &largeur_ecran, &hauteur_ecran, &posX_mainwindow, &posY_mainwindow);

	fclose( cfg_file );
    }

return(0);
}



int load_core_config()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("user/config_core.txt", "rt" );
	if( !cfg_file )
	{
	 sprintf(string_save_load_report[idf],"!config_core.txt");
	}
	else
	{
    //premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! config_core.txt");
	}
	else
	{
	fscanf( cfg_file , "%d / %d / %d / %d / %d / %d / %d /\n"  , &core_user_define_nb_faders, &core_user_define_nb_docks , &core_user_define_nb_chasers, &core_user_define_nb_tracks_per_chasers, &core_user_define_nb_gridplayers, &core_user_define_nb_bangers, &core_user_define_nb_echo);
    }
    //deuxieme ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! config_core.txt");
	}
	else
	{
	fscanf( cfg_file , "%d / %d / %d / %d / %d / %d / %d / %d / %d /\n"  ,&core_do_calculations[0],&core_do_calculations[1],&core_do_calculations[2],
    &core_do_calculations[3],&core_do_calculations[4],&core_do_calculations[5],&core_do_calculations[6],&core_do_calculations[7],&core_do_calculations[8]  );
    }
    //troisieme ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! config_core.txt");
	}
	else
	{
    fscanf( cfg_file , "%d / %d /\n",&BPS_RATE,&dmxINrate);
    }

	fclose( cfg_file );
    }
return(0);
}


int Save_Core_Config()
{
FILE *fpp;
if((fpp=fopen("user/config_core.txt","w")))//etait wb
{
fprintf(fpp,"#arguments: nb_faders / nb_docks / nb_chasers/ nb_tracks per chasers / nb_gridplayers / nb_bangers /\n");
fprintf(fpp, "%d / %d / %d / %d / %d / %d / %d /\n" , core_user_define_nb_faders, core_user_define_nb_docks ,core_user_define_nb_chasers,
core_user_define_nb_tracks_per_chasers,core_user_define_nb_gridplayers,core_user_define_nb_bangers,core_user_define_nb_echo);
fprintf(fpp,"#arguments: do faders (0-1) /do cuelist (0-1) / do bangers (0-1)/ do trichro (0-1) / do videotracking (0-1) / do chasers (0/1) / do Grid (0-1) /\n");
fprintf(fpp, "%d / %d / %d / %d / %d / %d / %d / %d / %d /\n" ,core_do_calculations[0],core_do_calculations[1],core_do_calculations[2],
    core_do_calculations[3],core_do_calculations[4],core_do_calculations[5],core_do_calculations[6],core_do_calculations[7], core_do_calculations[8]  );
fprintf(fpp,"#arguments: BPS RATE (25-200, should be 50) / DMX IN RATE (25-50) / \n");
fprintf(fpp, "%d / %d /\n",BPS_RATE,dmxINrate);
fclose(fpp);  sprintf(string_save_load_report[idf],"Saved config_core.txt");

}



if( !fpp )
	{
	 sprintf(string_save_load_report[idf],"!user/config_core.txt");
   }
return(0);
}




int Save_onstart_Config()
{
FILE *fpp;
if((fpp=fopen("user/config_onstart.txt","w")))//etait wb
{
fprintf(fpp,"#arguments:values 0-1: open camera / open arduino / open iCat server / expert_mode /\n");
fprintf(fpp, "%d / %d / %d / %d /\n" ,  camera_on_open, open_arduino_on_open , enable_iCat, expert_mode);
fclose(fpp);  sprintf(string_save_load_report[idf],"Saved config_onstart.txt");
}


if( !fpp )
	{
	 sprintf(string_save_load_report[idf],"!user/config_onstart.txt");
   }
return(0);
}


int Save_Screen_Config()
{
FILE *fpp;
if((fpp=fopen("user/config_screens.txt","w")))//etait wb
{
fprintf(fpp,"#arguments: fullscreen / largeur_ecran / hauteur_ecran / pos_x / pos_y\n");
fprintf(fpp, "%d / %d %d / %d %d /\n" , index_fullscreen, largeur_ecran, hauteur_ecran, posX_mainwindow, posY_mainwindow);
fclose(fpp);  sprintf(string_save_load_report[idf],"Saved config_screen.txt");
}


if( !fpp )
	{
	 sprintf(string_save_load_report[idf],"!user/config_screens.txt");
   }
return(0);
}


int Save_Launchpad_RetroLight()
{
FILE *fpp;
if((fpp=fopen("user/launchpad_lighting.txt","w")))//etait wb
{
fprintf(fpp,"#arguments: orange / green / yellow / red  / ambre / dark orange /\n");
fprintf(fpp, "%d / %d / %d / %d / %d / %d /\n" ,  lch_orange, lch_green, lch_yellow, lch_red, lch_ambre, lch_orange_fonce);
fclose(fpp);  sprintf(string_save_load_report[idf],"Saved launchpad_lighting.txt");
}

if( !fpp )
	{
	 sprintf(string_save_load_report[idf],"!user/launchpad_lighting.txt");
   }
return(0);
}


int Load_Launchpad_RetroLight()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("user/launchpad_lighting.txt", "rt" );
	if( !cfg_file )
	{
	 sprintf(string_save_load_report[idf],"! launchpad_lighting.txt");
	}
	else
	{
    //premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! launchpad_lighting.txt");
	}

	fscanf( cfg_file ,  "%d / %d / %d / %d / %d / %d /\n" ,  &lch_orange, &lch_green, &lch_yellow, &lch_red, &lch_ambre, &lch_orange_fonce);

	fclose( cfg_file );
    }

    launchpad_color[0]=lch_orange;//63;
    launchpad_color[1]=lch_green;//60;
    launchpad_color[2]=lch_yellow;//62;
    launchpad_color[3]=lch_red;//15;
    launchpad_color[4]=lch_ambre;//31;
    launchpad_color[5]=lch_orange_fonce;//30;
return(0);
}


int save_draw_preset_config()
{

FILE *fpp;
if((fpp=fopen("draw_presets_states.txt","w")))//etait wb
{
fprintf(fpp,"#DRAW PRESET CONFIGURATION\n");

for(int i=0;i<6;i++)
{
fprintf(fpp,"#arguments Preset %d:MODE (0 to 3) / LEVEL (float) / TILT (float)/ SIZE (float)/ GHOST (float) / BRUSH TYPE (int) /\n",i+1);
fprintf(fpp,"#arguments 2ndLine :GPL NUM ( 1 to 4 ) / Offset ( 1 to 513 ) / position point / col / row /\n");
fprintf(fpp, "M %d / %f / %f / %f / %d /\n",draw_mode[i],draw_level_to_do[i],draw_damper_decay_factor[i],draw_ghost_to_do[i],draw_brush_type[i]);
fprintf(fpp, "G %d / %d / %d / %d / %d /\n",draw_get_gpl[i],draw_offset_gpl[i], index_case[i],draw_centre_x[i], draw_centre_y[i]);
}
fclose(fpp);
sprintf(string_save_load_report[idf],"Saved draw_presets_states.txt");
}
if( !fpp )
	{
	 sprintf(string_save_load_report[idf],"!draw_presets_states.txt");
   }



return(0);
}


int load_draw_preset_config()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
	cfg_file = fopen("draw_presets_states.txt", "rt" );
	if( !cfg_file )
	{
	 sprintf(string_save_load_report[idf],"!draw_presets_states.txt");
	}

	else
	{

	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{ sprintf(string_save_load_report[idf],"! draw_presets_states.txt");}

    for(int i=0;i<6;i++)
    {

	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{ sprintf(string_save_load_report[idf],"! draw_presets_states.txt");}

   	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{ sprintf(string_save_load_report[idf],"! draw_presets_states.txt");}

    fscanf( cfg_file , "M %d / %f / %f / %f / %d /\n" , &draw_mode[i], &draw_level_to_do[i], &draw_damper_decay_factor[i] ,&draw_ghost_to_do[i], &draw_brush_type[i]);

    fscanf( cfg_file , "G %d / %d / %d / %d / %d /\n" ,&draw_get_gpl[i],&draw_offset_gpl[i], &index_case[i], &draw_centre_x[i], &draw_centre_y[i]);

    previous_draw_mode[i]=draw_mode[i];
    draw_get_gpl[i]=constrain_int_data_to_this_range(draw_get_gpl[i],1,4);
    draw_offset_gpl[i]=constrain_int_data_to_this_range(draw_offset_gpl[i],1,512);

    if(draw_level_to_do[i]>1.0){draw_level_to_do[i]=1.0;}
    if(draw_damper_decay_factor[i]>1.0){draw_damper_decay_factor[i]=1.0;}
    if(draw_ghost_to_do[i]>1.0){draw_ghost_to_do[i]=1.0;}

    }
    fclose( cfg_file );
    }

return(0);
}


int Save_Arduino_Config()//pas en user mais dans un spectacle
{
FILE *fpp;
if((fpp=fopen("arduino.txt","w")))//etait wb
{
fprintf(fpp,"#arguments:COM PORT / BAUDRATE / REQUEST RATE / MAX IO / MAX ANALOG /\n");
fprintf(fpp, "%d / %d / %d / %d / %d /\n" ,  arduino_com0, arduino_baud_rate0, ARDUINO_RATE, arduino_max_digital, arduino_max_analog );
fclose(fpp);  sprintf(string_save_load_report[idf],"Saved arduino.txt");
}
if( !fpp )
	{
	 sprintf(string_save_load_report[idf],"!arduino.txt");
   }


return(0);
}


int load_arduino_config()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("arduino.txt", "rt" );
	if( !cfg_file )
	{
	 sprintf(string_save_load_report[idf],"!arduino.txt");
	}
	else
	{
    //premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! arduino.txt");
	}

fscanf( cfg_file , "%d / %d / %d / %d / %d /\n" ,  &arduino_com0, &arduino_baud_rate0, &ARDUINO_RATE, &arduino_max_digital,  &arduino_max_analog );
	fclose( cfg_file );
    }
return(0);
}


//user: windows
int Load_Window_Conf()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("config_windows.txt", "rt" );
	if( !cfg_file )
	{
	 sprintf(string_save_load_report[idf],"!config_windows.txt");
	}
else
{
//premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! config_windows.txt");
	}
	fscanf( cfg_file , "%d %d / %d %d / %d %d / %d %d /\n" ,  &xtrichro_window, &ytrichro_window, &xnum_window,&ynum_window,&videoX,&videoY, &xpatch_window, &ypatch_window);
//2eme ligne
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error reading config_windows.txt");
	}
    fscanf( cfg_file , "%d %d / %d %d / %d %d /\n" ,  &report_SL_X, &report_SL_Y , &xtime_window, &ytime_window,&xseq_window, &yseq_window);
//3eme ligne
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error reading config_windows.txt");
	}
    fscanf( cfg_file ,"%d / %d %d / %d %d /\n",&YFader, &XConfirm, &YConfirm, &xsave_window, &ysave_window );
//4eme ligne
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error reading config_windows.txt");
	}
    fscanf( cfg_file ,"%d %d / %d %d / %d %d / %d %d /\n",&XAlarm,&YAlarm,&XAudio,&YAudio, &window_cfgX, &window_cfgY, &X_banger, &Y_banger);
//5eme ligne
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error reading config_windows.txt");
	}
    fscanf( cfg_file ,"%d %d / %d %d / %d %d / %d %d / %d %d /\n",&Xwizard,&Ywizard,&xMinifaders,&yMinifaders, &Xlistproj, &Ylistproj, &Xchasers, &Ychasers,&xmover_window, &ymover_window);

//6eme ligne
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error reading config_windows.txt");
	}
    fscanf( cfg_file ,"%d %d / %d %d / %d %d / %d %d / %d %d / %d %d /\n",&X_gui_iCat,&Y_gui_iCat,&grider_window_x,&grider_window_y, &x_plot, &y_plot, &x_mainmenu, &y_mainmenu , &x_Wdraw, &y_Wdraw, &x_echo, &y_echo);


	fclose( cfg_file );
}
return(0);
}


int Load_Sequenciel_Conf()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("sequenciel.txt", "rt" );
	if( !cfg_file )
	{	 sprintf(string_save_load_report[idf],"Error on opening Sequenciel.txt"); b_report_error[idf]=1;	}
	else {
    sprintf(string_save_load_report[idf],"Sequenciel.txt opened");
//premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{     sprintf(string_save_load_report[idf],"Error on reading Sequenciel.txt");b_report_error[idf]=1; 	}
    else {sprintf(string_save_load_report[idf],"Sequenciel.txt readed");}
	fscanf( cfg_file , "%d / %d / %d / %d / %d /\n" ,  &position_onstage, &position_preset, &niveauX1, &niveauX2, &crossfade_speed);
    fscanf( cfg_file , "%f /\n" ,  &default_time);
    fscanf( cfg_file , "%d %d /\n" ,  &go_channel_is, &pause_channel_is);
	fclose( cfg_file );
	}
midi_levels[491]=niveauX1/2;
midi_levels[492]=127-(niveauX2/2);
midi_levels[493]=crossfade_speed;
   if(go_channel_is<1 || ( go_channel_is> 512)){go_channel_is=0;}
   if(pause_channel_is<1 || ( pause_channel_is> 512)){pause_channel_is=0;}
return(0);
}

int Load_setup_conf()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("user/general_set_up.txt", "rt" );
	if( !cfg_file )
	{	 sprintf(string_save_load_report[idf],"Error on opening user/general_set_up.txt"); b_report_error[idf]=1;	}
	else {
    sprintf(string_save_load_report[idf],"user/general_set_up.txt opened");
//premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{     sprintf(string_save_load_report[idf],"Error on reading user/general_set_up.txt");b_report_error[idf]=1; 	}
    else {sprintf(string_save_load_report[idf],"user/general_set_up.txt readed");}
	fscanf( cfg_file , "%d / %d / %d / %d / %d / %d / %d / %d / %f /\n" , &default_step_level, &wheellevel_absolutemode, &check_channel_level,
                     &dimmer_check_level, &index_blink_change_memories, &index_midi_auto_desaffect, &dmx_view, &index_preloaded_sounds, &default_time_of_the_bang);
//2eme ligne
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error reading general_set_up.txt");
	}
    fscanf( cfg_file , "%d / %d / %d /\n",&automatic_time_for_save, &index_nbre_players_visibles, &LargeurEspaceFaderSize);

	fclose( cfg_file );
	}

if(LargeurEspaceFaderSize<1024 ){LargeurEspaceFaderSize=1024;}
if(LargeurEspaceFaderSize>largeur_ecran){LargeurEspaceFaderSize=largeur_ecran;}

return(0);
}

int Save_setup_conf()
{
FILE *fpi;
if((fpi=fopen("user/general_set_up.txt","w")))//etait wb
{
fprintf(fpi,"#arguments: default step level / level wheel absolute mode / channel check level / dimmer check level / blink on mem change /  midi auto desaffect / dmx view / preloaded sounds / bang stay time\n");
fprintf(fpi,"%d / %d / %d / %d / %d / %d / %d / %d / %.1f /\n",default_step_level, wheellevel_absolutemode, check_channel_level, dimmer_check_level,
                                                             index_blink_change_memories, index_midi_auto_desaffect, dmx_view, index_preloaded_sounds,  default_time_of_the_bang);
fprintf(fpi,"#arguments: autosave time in sec / nbr audioplayers / fader space width /\n");
fprintf(fpi,"%d / %d / %d /\n",automatic_time_for_save, index_nbre_players_visibles, LargeurEspaceFaderSize);
fclose(fpi);
}

sprintf(string_save_load_report[idf],"Saved /general_set_up.txt");
return(0);
}



int Save_Plot_Plan_config()
{
FILE *fpp;
if((fpp=fopen("plot_plan_config.txt","w")))//etait wb
{
fprintf(fpp,"#arguments: Name_of_the_plan.jpg\n");
fprintf(fpp, "%s\n" , Name_of_plane_is);
fprintf(fpp,"#arguments: position X / position Y / size X / size Y / Orientation / Alpha / Lock proportions / Global Library Size /\n");
fprintf(fpp, "%d / %d / %d / %d / %f / %f / %d / %f /\n" ,position_relative_plan_theatre[0],position_relative_plan_theatre[1],taille_relative_plan_theatre[0],taille_relative_plan_theatre[1],orientation_plan_theatre,alpha_plan,lock_background_proportions, global_symbol_size);
fprintf(fpp,"#arguments: Grid Scale / Plot Window size X / Plot Window size X / Plot Viewport X / Plot Viewport Y / Line Color / Background Color / Number of shapes present / Show shapes id / Grid Type / Alpha Grid / Alpha Shapes / Plan ratio / SoloMode xy relativs /\n");
fprintf(fpp, "%d / %d / %d / %d / %d / %f / %f / %d / %d / %d / %f / %f / %f / %d /\n",plot_quadrillage_size,plot_window_x_size,plot_window_y_size, plot_view_port_x, plot_view_port_y, Color_plotline, Color_plotfill, nbre_shapes_on_plot, index_show_shape_id, plot_grid_type,alpha_grille, general_alpha_for_shape, ratio_lock_plot_scale, mode_relatif_xy_solo);
fclose(fpp);  sprintf(string_save_load_report[idf],"plot_plan_config.txt.txt");
}


if( !fpp )
	{
	 sprintf(string_save_load_report[idf],"!plot_plan_config.txt");
   }
return(0);
}


int Load_Plot_Plan_config()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("plot_plan_config.txt", "rt" );
	if( !cfg_file )
	{	 sprintf(string_save_load_report[idf],"Error on opening plot_plan_config.txt"); b_report_error[idf]=1;	}
	else
    {
    //lecture ouverture fichier ok
    sprintf(string_save_load_report[idf],"plot_plan_config.txt opened");

//premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{     sprintf(string_save_load_report[idf],"Error on reading plot_plan_config.txt");b_report_error[idf]=1; 	}
    else {sprintf(string_save_load_report[idf],"plot_plan_config.txt readed");}
//2eme ligne
	//sab 05/08/2016 deb - nom du plan avec espace mets un bazar dans la lecture des datas de plot ( pb de scanf )
                    //fscanf( cfg_file , "%s\n" , Name_of_plane_is);
                    Name_of_plane_is [0]=0;
                    if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
                    {
                     sprintf(string_save_load_report[idf],"Error plot_plan_config.txt");
                    }
                    else
                    {
                     whc_toolbox tool ;
                     tool.copy_until_eol(Name_of_plane_is,sizeof( Name_of_plane_is ),read_buff_winfil);
                    }
                    //sab 05/08/2016 fin
//args
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error plot_plan_config.txt");
	}
//4eme
    fscanf( cfg_file , "%d / %d / %d / %d / %f / %f / %d / %f /\n" ,&position_relative_plan_theatre[0],&position_relative_plan_theatre[1],&taille_relative_plan_theatre[0],&taille_relative_plan_theatre[1],&orientation_plan_theatre,&alpha_plan, &lock_background_proportions, &global_symbol_size);
//args
	if( !fgets( read_buff_winfil, sizeof( read_buff_winfil ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"Error plot_plan_config.txt");
	}
//6eme
    fscanf( cfg_file , "%d / %d / %d / %d / %d / %f / %f / %d / %d / %d / %f / %f / %f / %d /\n",&plot_quadrillage_size,&plot_window_x_size,&plot_window_y_size, &plot_view_port_x, &plot_view_port_y, &Color_plotline, &Color_plotfill, &nbre_shapes_on_plot, &index_show_shape_id, &plot_grid_type, &alpha_grille, &general_alpha_for_shape, &ratio_lock_plot_scale, &mode_relatif_xy_solo);

	fclose( cfg_file );
	}

if(plot_window_x_size<840){plot_window_x_size=840;}
if(plot_window_y_size<plot_minimum_y_size){plot_window_y_size=plot_minimum_y_size;}
if(plot_quadrillage_size<0){plot_quadrillage_size=0;}
else if(plot_quadrillage_size>100){plot_quadrillage_size=100;}
Rgba TmpPlotColor (Color_plotline,Color_plotline,Color_plotline);
CouleurPlotLine=TmpPlotColor;
Rgba TmpPlotColor2 (Color_plotfill,Color_plotfill,Color_plotfill);
CouleurPlotFill=TmpPlotColor2;
return(0);
}


int write_indexes()
{
index_report_customs[0]=auto_reset_crossfade_speed_on_link;
index_report_customs[1]=nbre_memoires_visualisables_en_preset;
index_report_customs[2]=index_midi_global_thruth;
index_report_customs[3]=refresh_midi_chasers;
index_report_customs[4]=view_plot_calc_number_is;
index_report_customs[5]=index_menus_lighting_plot;
index_report_customs[6]=symbol_selected_type;
index_report_customs[7]=shape_selected_type;
index_report_customs[8]=legend_view;//plot
index_report_customs[9]=ClassicalChannelView;//512 circuits mode
index_report_customs[10]=index_config_dmx;
index_report_customs[11]=index_config_midi;
index_report_customs[12]=index_config_arduino;
index_report_customs[13]=midi_page;
index_report_customs[14]=config_color_style_is;
index_report_customs[15]=index_link_is_on;
index_report_customs[16]=index_decay_tracker;
index_report_customs[17]=adapater_is_selected;
index_report_customs[18]=index_build_patch_from_plot;
index_report_customs[19]=index_menu_curve;
index_report_customs[20]=index_show_first_dim;
index_report_customs[21]=cheat_key_off;
index_report_customs[22]=(int)scroll_faderspace;
index_report_customs[23]=draw_preset_selected;
index_report_customs[24]=index_banger_is_on;
index_report_customs[25]=index_banger_selected;
index_report_customs[26]=index_save_mode_export_or_binary;
index_report_customs[27]=index_allow_sunlite_dmxIN;// dmx in position sunlite
index_report_customs[28]=index_config_general;
index_report_customs[29]=niveauGMaster;//grand master
index_report_customs[30]=cheat_key_off_to_key_on;
index_report_customs[31]=clocklevel_absolutemode;//midi clock add level
index_report_customs[32]=echo_selected;
index_report_customs[33]=index_allow_multicore;
index_report_customs[34]=allow_artnet_in;
index_report_customs[35]=window_focus_id;
index_report_customs[36]=recall_windows_focus_id;
index_report_customs[37]=index_config_network;
index_report_customs[38]=index_setup_gfx;
index_report_customs[39]=core_to_assign;
index_report_customs[40]=index_midi_clock_on;
index_report_customs[41]=midi_BPM;
index_report_customs[42]=show_global_view_grider;
index_report_customs[43]=enable_launchpad;
index_report_customs[44]=relativ_encoder_midi_clock_value;
index_report_customs[45]=config_page_is;
index_report_customs[46]=index_midi_affectation_autoclose;
index_report_customs[47]=index_show_chrono;
index_report_customs[48]=nbre_track_visualisables;
index_report_customs[49]=chaser_operator_is;
index_report_customs[50]=chaser_selected;
index_report_customs[51]=index_affichage_digit_time_unit;//affichage des unités après virgule
index_report_customs[52]=launchpad_chaser_mode;
index_report_customs[53]=index_enable_edit_chaser;
index_report_customs[54]=chaser_midi_rows;
index_report_customs[55]=line_list_is;
index_report_customs[56]=waver_control;
index_report_customs[57]=wave_channel_preset_selected;
index_report_customs[58]=brush_selected;
index_report_customs[59]=iCatPageis;
index_report_customs[60]=surface_type;
index_report_customs[61]=grid_icat_modulo;
index_report_customs[62]=index_midi_auto_demute;
index_report_customs[63]=index_midi_mute_on_lfo;
index_report_customs[64]=index_text_auto_close;
index_report_customs[65]=index_config_core;
index_report_customs[66]=show_gridplayer_in_seq;
index_report_customs[67]=index_auto_mute_cuelist_speed;
index_report_customs[68]=Midi_Force_Go;
index_report_customs[69]=BPM_WAVE_RATE;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sab 08/2016 - HOT KEYS -- DEB ANCRAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    index_report_customs[70]=index_config_tab_hotkeys;// sab 12/08/2016 Fenêtre des config - onglet des hot keys
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sab 08/2016 - HOT KEYS -- FIN ANCRAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

return(0);
}

int load_indexes()
{
auto_reset_crossfade_speed_on_link=index_report_customs[0];
nbre_memoires_visualisables_en_preset=index_report_customs[1];
index_midi_global_thruth=index_report_customs[2];
refresh_midi_chasers=index_report_customs[3];
view_plot_calc_number_is=index_report_customs[4];
index_menus_lighting_plot=index_report_customs[5];
symbol_selected_type=index_report_customs[6];
shape_selected_type=index_report_customs[7];
legend_view=index_report_customs[8];
ClassicalChannelView=index_report_customs[9];
index_config_dmx=index_report_customs[10];
index_config_midi=index_report_customs[11];
index_config_arduino=index_report_customs[12];
midi_page=index_report_customs[13];
config_color_style_is=index_report_customs[14];
index_link_is_on=index_report_customs[15];
index_decay_tracker=index_report_customs[16];
adapater_is_selected=index_report_customs[17];
index_build_patch_from_plot=index_report_customs[18];
index_menu_curve=index_report_customs[19];
index_show_first_dim=index_report_customs[20];
cheat_key_off=index_report_customs[21];
scroll_faderspace=index_report_customs[22];
draw_preset_selected=index_report_customs[23];
index_banger_is_on=index_report_customs[24];
index_banger_selected=index_report_customs[25];
index_save_mode_export_or_binary=index_report_customs[26];
index_allow_sunlite_dmxIN=index_report_customs[27];//sunlite
index_config_general=index_report_customs[28];
niveauGMaster=index_report_customs[29];//grand master
cheat_key_off_to_key_on=index_report_customs[30];
clocklevel_absolutemode=index_report_customs[31];//midiclock midi mode
echo_selected=index_report_customs[32];
index_allow_multicore=index_report_customs[33];
allow_artnet_in=index_report_customs[34];
window_focus_id=index_report_customs[35];
recall_windows_focus_id=index_report_customs[36];
index_config_network=index_report_customs[37];
index_setup_gfx=index_report_customs[38];
core_to_assign=index_report_customs[39];
index_midi_clock_on=index_report_customs[40];
midi_BPM=index_report_customs[41];
show_global_view_grider=index_report_customs[42];
enable_launchpad=index_report_customs[43];
relativ_encoder_midi_clock_value=index_report_customs[44];
config_page_is=index_report_customs[45];
index_midi_affectation_autoclose=index_report_customs[46];
index_show_chrono=index_report_customs[47];
nbre_track_visualisables=index_report_customs[48];
chaser_operator_is=index_report_customs[49];
chaser_selected=index_report_customs[50];
index_affichage_digit_time_unit=index_report_customs[51];
launchpad_chaser_mode=index_report_customs[52];
index_enable_edit_chaser=index_report_customs[53];
chaser_midi_rows=index_report_customs[54];
line_list_is=index_report_customs[55];
waver_control=constrain_int_data_to_this_range(index_report_customs[56],0,26);
wave_channel_preset_selected=constrain_int_data_to_this_range(index_report_customs[57],0,26);
brush_selected=constrain_int_data_to_this_range(index_report_customs[58],0,26);
iCatPageis=index_report_customs[59];
surface_type=index_report_customs[60];
grid_icat_modulo=index_report_customs[61];
index_midi_auto_demute=index_report_customs[62];
index_midi_mute_on_lfo=index_report_customs[63];
index_text_auto_close=index_report_customs[64];
index_config_core=index_report_customs[65];
show_gridplayer_in_seq=index_report_customs[66];
index_auto_mute_cuelist_speed=index_report_customs[67];
Midi_Force_Go=index_report_customs[68];
BPM_WAVE_RATE=constrain_int_data_to_this_range(index_report_customs[69],1,6000);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sab 08/2016 - HOT KEYS -- DEB ANCRAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    index_config_tab_hotkeys=index_report_customs[70]; // sab 12/08/2016 Fenêtre des config - onglet des hot keys
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sab 08/2016 - HOT KEYS -- FIN ANCRAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//icat
 if(surface_type==0){L_tablier_iCat=240; H_tablier_iCat=160;}
   else {L_tablier_iCat=512; H_tablier_iCat=384;}
   if(grid_icat_modulo<1){grid_icat_modulo=1;}

if(niveauGMaster<255){midi_levels[615]=(niveauGMaster/2);}
else if(niveauGMaster==255){midi_levels[615]=127;}



if(index_allow_multicore==1 && core_to_assign>0 && core_to_assign<9)
{process_assign_to_core(core_to_assign);}

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
case 7:
index_config_core=1;
break;
}

//nbre memoires sequenciel
if(nbre_memoires_visualisables_en_preset<5){nbre_memoires_visualisables_en_preset=5;}
hauteur_globale_sequenciel=180+(35*(nbre_memoires_visualisables_en_preset+1))+35;

//chaser midi refresh window
set_refresh_mode_for_chaser(refresh_midi_chasers);

//rafraichissement tracking video decay
midi_levels[498]=index_decay_tracker;index_send_midi_out[498]=1;

//mid clock
if(midi_BPM<=0){midi_BPM=120;}
ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);
if(relativ_encoder_midi_clock_value<=0){relativ_encoder_midi_clock_value=1;}

return(0);
}


int load_show_coming_from()
{

    FILE *cfg_file = NULL ;
    //sab 02/03/2014 unused var char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("user/show_coming_from.txt", "rt" );
	if( !cfg_file )
	{	 sprintf(string_save_load_report[idf],"Error on opening user/show_coming_from.txt"); b_report_error[idf]=1;	}
	else {
    sprintf(string_save_load_report[idf],"user/show_coming_from.txt opened");}
	fgets( my_show_is_coming_from , sizeof( my_show_is_coming_from ) ,cfg_file ) ;
	fclose( cfg_file );
    sprintf(string_save_load_report[idf],"loaded show_coming_from.txt");

 return(0);
}


int Save_Window_Conf()
{
//reset_error_on_save_load();

FILE *fpi;
if((fpi=fopen("config_windows.txt","w")))//etait wb
{
fprintf(fpi,"#arguments: X Y position of windows: Colors / Numeric / Video / Patch /\n");
fprintf(fpi,"%d %d / %d  %d / %d %d / %d %d /\n",xtrichro_window , ytrichro_window , xnum_window , ynum_window , videoX , videoY, xpatch_window, ypatch_window);
fprintf(fpi,"#arguments:  Save Load Report / Time / Sequenciel /\n");
fprintf(fpi,"%d %d / %d %d / %d %d /\n",report_SL_X,report_SL_Y, xtime_window, ytime_window, xseq_window, yseq_window);
fprintf(fpi,"#arguments:   FadersSpace(Y only) / Config window / Confirm Box / MiniSeq / Save Window\n");
fprintf(fpi,"%d / %d %d / %d %d /\n",YFader, XConfirm, YConfirm,xsave_window, ysave_window );
fprintf(fpi,"#arguments: X Y position of windows: Help Window / Alarm window / Config window / Banger\n");
fprintf(fpi,"%d %d / %d %d / %d %d / %d %d /\n",XAlarm,YAlarm,XAudio,YAudio, window_cfgX, window_cfgY, X_banger,Y_banger);
fprintf(fpi,"#arguments: X Y position of windows: Wizard window/ Minifaders / List / Chasers\n");
fprintf(fpi,"%d %d / %d  %d / %d %d / %d %d / %d %d /\n",Xwizard,Ywizard,xMinifaders, yMinifaders, Xlistproj, Ylistproj, Xchasers, Ychasers, xmover_window, ymover_window);
fprintf(fpi,"#arguments: X Y position of windows: iCatBuilder / Grider / Plot / Main Menu / Draw / Echo /\n");
fprintf(fpi,"%d %d / %d %d / %d %d / %d %d / %d %d / %d %d /\n",X_gui_iCat,Y_gui_iCat,grider_window_x,grider_window_y, x_plot, y_plot, x_mainmenu, y_mainmenu, x_Wdraw,y_Wdraw,x_echo,y_echo);

fclose(fpi);
}
sprintf(string_save_load_report[idf],"Saved config_windows.txt");

return(0);
}




int Load_User_Profile()
{

FILE *fpA;

if ((fpA=fopen(file_color_profile, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_color_profile);}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_color_profile);
if (fread( couleurs_user, sizeof(float), color_profile_size, fpA) !=color_profile_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_color_profile);}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_color_profile);
fclose(fpA);
}
 for(int tmp=0;tmp<12;tmp++)
 {
  Rgba TmpColor (couleurs_user[tmp][0],couleurs_user[tmp][1],couleurs_user[tmp][2]);

  switch (tmp)
 {
 case 0:
 CouleurUser1=TmpColor;
 break;
 case 1:
 CouleurUser2=TmpColor;
 break;
 case 2:
 CouleurUser3=TmpColor;
 break;
 case 3:
 CouleurUser4=TmpColor;
 break;
 case 4:
 CouleurUser5=TmpColor;
 break;
 case 5:
 CouleurUser6=TmpColor;
 break;
 case 6:
 CouleurUser7=TmpColor;
 break;
 case 7:
 CouleurUser8=TmpColor;
 break;
 case 8:
 CouleurUser9=TmpColor;
 break;
 case 9:
 CouleurUser10=TmpColor;
 break;
 case 10:
 CouleurUser11=TmpColor;
 break;
 case 11:
 CouleurUser12=TmpColor;
 break;
 }
}
return(0);
}


int Save_Sequenciel_Conf()
{
FILE *fpo;
if((fpo=fopen("sequenciel.txt","w")))
{
fprintf(fpo,"#arguments: mem_on_stage*10 / mem_on_preset*10 / master_stage / master_preset / speed /\n");
fprintf(fpo,"%d / %d / %d / %d / %d /\n",position_onstage, position_preset,niveauX1,niveauX2,crossfade_speed);
fprintf(fpo,"%.1f /\n",default_time);
fprintf(fpo,"%d %d /\n", go_channel_is,pause_channel_is);
sprintf(string_save_load_report[idf],"Saved sequenciel.txt");
fclose(fpo); }
else {sprintf(string_save_load_report[idf],"Error on sequenciel.txt");b_report_error[idf]=1;}

return(0);
}

int Save_audiofiles_cues()
{
FILE *fpo;
char tmp_audio_f[512];
sprintf(tmp_audio_f,"audio\\%s\\audio_cues_in_out.txt",audio_folder);
if((fpo=fopen(tmp_audio_f,"w")))
{
fprintf(fpo,"#arguments: audiofilename / cuein / cueout\n");
for(int i=1;i<127;i++)
{
if(strcmp(list_audio_files[i],"")!=0)//si aps iren en nom de fichier
{
fprintf(fpo,"%s / %d / %d\n",list_audio_files[i],audiofile_cue_in_out_pos[i][0],audiofile_cue_in_out_pos[i][1]);
}
}
sprintf(string_save_load_report[idf],"Saved %s",tmp_audio_f);
fclose(fpo);
}

else {sprintf(string_save_load_report[idf],"Error on audio_cues_in_out.txt");b_report_error[idf]=1;}


 return(0);
}


int Load_Audio_Conf()
{
    FILE *cfg_file = NULL ;
    char read_buff_winfil[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	cfg_file = fopen("audio_conf.txt", "rt" );
	if( !cfg_file )
	{	 sprintf(string_save_load_report[idf],"Error on opening Sequenciel.txt"); b_report_error[idf]=1;	}
	else {
    sprintf(string_save_load_report[idf],"audio_conf.txt opened");
//premiere ligne les args
	if( !fgets( read_buff_winfil , sizeof( read_buff_winfil ) ,cfg_file ) )
	{     sprintf(string_save_load_report[idf],"Error on reading audio_conf.txt");b_report_error[idf]=1; 	}
    else {sprintf(string_save_load_report[idf],"audio_conf.txt readed");}
	fscanf( cfg_file , "%s\n" ,  audio_folder);
	fclose( cfg_file );
    }


return(0);
}


int Save_Audio_Conf()
{
FILE *fpo;
if((fpo=fopen("audio_conf.txt","w")))
{
fprintf(fpo,"#arguments: audiofolder\n");
fprintf(fpo,"%s\n",audio_folder);
sprintf(string_save_load_report[idf],"Saved audio_conf.txt");
fclose(fpo);
}
else {sprintf(string_save_load_report[idf],"Error on audio_conf.txt");b_report_error[idf]=1; fclose(fpo);}

return(0);
}

//save
int Save_Show()
{
index_is_saving=1;

save_load_print_to_screen("Saving ...");

//index_show_save_load_report=1;
sprintf(rep,"%s\%s\%s",mondirectory,rep_saves,nomduspectacle);
//LPSECURITY_ATTRIBUTES attr;
//attr=NULL;
//CreateDirectory(rep,attr);
mkdir (rep);
//chmod (rep,0777);
chdir (rep);
clear_report_string();
idf=0;
//sprintf(string_debug,"entree:%s", rep);
//////////////////////VERSION IS//////////////////////////////////////////////
FILE *fpo=NULL;
if((fpo=fopen("whitecat_version.txt","w")))
{

fprintf(fpo,"%s\n",versionis);
sprintf(string_save_load_report[idf],"Saved whitecat_version.txt");
}
else {sprintf(string_save_load_report[idf],"Error on whitecat_version.txt");b_report_error[idf]=1; }
fclose(fpo);

 idf++;
////////////////////////////////////////////////////////////////////////////////
rest(10);

FILE *fp=NULL;








if(specify_who_to_save_load[0]==1) ///MEMOIRES////////////////////////////////////////////////////////////
{
if ((fp=fopen( file_mem_existantes, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mem_existantes); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_mem_existantes);
if (fwrite(MemoiresExistantes, sizeof(bool),mem_existantes_size, fp) !=  mem_existantes_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_mem_existantes); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mem_existantes);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_memories, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_memories); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_memories);
if (fwrite(Memoires, sizeof(unsigned char),memories_size, fp) !=  memories_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_memories); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_memories);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_text_mems, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_text_mems); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_text_mems);
if (fwrite(descriptif_memoires, sizeof(char),text_mems_size, fp) !=  text_mems_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_text_mems); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_text_mems);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_text_annots, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_text_annots); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_text_annots);
if (fwrite(annotation_memoires, sizeof(char),text_annots_size, fp) !=  text_annots_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_text_annots); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_text_annots);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mem_detruites, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mem_detruites); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_mem_detruites);
if (fwrite(MemoiresDetruites, sizeof(bool),mem_deleted_size, fp) !=  mem_deleted_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mem_detruites); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_mem_detruites);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mem_exclues, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mem_exclues); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_mem_exclues);
if (fwrite(MemoiresExclues, sizeof(bool),mem_exclues_size, fp) !=  mem_exclues_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mem_exclues); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_mem_exclues);
fclose(fp);
}
 idf++;


Save_Sequenciel_Conf();
 idf++;
}

if(specify_who_to_save_load[1]==1) ///////////MEMOIRES TIMES///////////////////////////////////////////////
{
if ((fp=fopen( file_times_mem, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_times_mem); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_times_mem);
if (fwrite(Times_Memoires, sizeof(float),times_mems_size, fp) !=  times_mems_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_times_mem); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_times_mem);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[2]==1)  ///////////MEMOIRES LINKS //////////////////////////////////////////////
{
if ((fp=fopen( file_link_mem, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_link_mem); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_link_mem);
if (fwrite(Links_Memoires, sizeof(bool),link_mem_size, fp) !=  link_mem_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_link_mem); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_link_mem);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[3]==1) ///////////MEMOIRES: nums de bangers affectés//////////////////////////
{
if ((fp=fopen( file_banger_call_in_mem, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_banger_call_in_mem); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_banger_call_in_mem);
if (fwrite(Banger_Memoire, sizeof(int),bang_mem_size, fp) !=  bang_mem_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_banger_call_in_mem); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_banger_call_in_mem);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[4]==1) /////////////MEMOIRES: manual ratio/////////////////////////////////////
{
if ((fp=fopen( file_manual_ratio_mem, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_manual_ratio_mem); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_manual_ratio_mem);
if (fwrite(ratio_cross_manuel, sizeof(int),ratio_mem_size, fp) !=  ratio_mem_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_manual_ratio_mem); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_manual_ratio_mem);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[5]==1)  ////////////Channels LIST//////////////////////////////////////////////
{
if ((fp=fopen(file_spotlist, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_spotlist); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_spotlist);
if (fwrite( descriptif_projecteurs, sizeof(char),spotlist_size, fp) !=  spotlist_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_spotlist); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_spotlist);
fclose(fp);
}
 idf++;


 if ((fp=fopen(file_chan_macro_on, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_on); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chan_macro_on);
if (fwrite(  macro_channel_on, sizeof(bool),chan_macro_on_size, fp) !=  chan_macro_on_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chan_macro_on); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chan_macro_on);
fclose(fp);
}
 idf++;


  if ((fp=fopen(file_chan_macro_reaction, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_reaction); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chan_macro_reaction);
if (fwrite(  channel_macro_reaction, sizeof(int),chan_macro_reaction_size, fp) !=  chan_macro_reaction_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chan_macro_reaction); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chan_macro_reaction);
fclose(fp);
}
 idf++;



   if ((fp=fopen(file_chan_macro_action, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_action); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chan_macro_action);
if (fwrite(  channel_macro_action, sizeof(int),chan_macro_action_size, fp) !=  chan_macro_action_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chan_macro_action); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chan_macro_action);
fclose(fp);
}
 idf++;

  if ((fp=fopen(file_chan_macro_val, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_val); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chan_macro_val);
if (fwrite(  channel_macro_val, sizeof(int),chan_macro_val_size, fp) !=  chan_macro_val_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chan_macro_val); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chan_macro_val);
fclose(fp);
}
 idf++;

  if ((fp=fopen(file_chview_ch, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_ch); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chview_ch);
if (fwrite(  Channel_View_ROUTING, sizeof(int),chview_ch_size, fp) !=  chview_ch_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chview_ch); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chview_ch);
fclose(fp);
}
 idf++;

  if ((fp=fopen(file_chview_name, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_name); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chview_name);
if (fwrite(  channel_view_Name, sizeof(char),chview_name_size, fp) !=  chview_name_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chview_name); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chview_name);
fclose(fp);
}
 idf++;

   if ((fp=fopen(file_chview_linktype, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_linktype); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chview_linktype);
if (fwrite(  channel_view_link_type, sizeof(int), chview_linktype_size, fp) !=  chview_linktype_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chview_linktype); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chview_linktype);
fclose(fp);
}
 idf++;


    if ((fp=fopen(file_chview_linkref, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_linkref); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chview_linkref);
if (fwrite(  channel_view_link_ref, sizeof(int), chview_linkref_size, fp) !=  chview_linkref_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chview_linkref); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chview_linkref);
fclose(fp);
}
 idf++;


  if ((fp=fopen(file_chview_view, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_view); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chview_view);
if (fwrite(  Channel_View_MODE, sizeof(bool), chview_view_size, fp) !=  chview_view_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chview_view); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chview_view);
fclose(fp);
}
 idf++;

 //fin list
}


if(specify_who_to_save_load[6]==1)  ////////////Channels Direct Chan///////////////////////////////////////
{
if ((fp=fopen( file_direct_channel, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_direct_channel); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_direct_channel);
if (fwrite(FaderDirectChan, sizeof(int),fader_direct_chan_size, fp) != fader_direct_chan_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_direct_channel); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_direct_channel);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[7]==1)  ////////////FREEZE STATE//////////////////////////////////////////////////
{
if ((fp=fopen(file_dofreeze, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dofreeze); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_dofreeze);
if (fwrite( freeze_array, sizeof(bool), dofreeze_size, fp) !=   dofreeze_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dofreeze); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dofreeze);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_freeze_state, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_freeze_state); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_freeze_state);
if (fwrite( freeze_state, sizeof(unsigned char), freezestate_size, fp) !=   freezestate_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_freeze_state); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_freeze_state);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_excluded_chan, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_excluded_chan); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_excluded_chan);
if (fwrite(Channels_excluded_from_grand_master, sizeof(bool), excluded_chan_size, fp) !=   excluded_chan_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_excluded_chan); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_excluded_chan);
fclose(fp);
}
 idf++;

}




if(specify_who_to_save_load[8]==1)  /////PATCH CHANNELS ////////////////////////////////////////////////////
{
if ((fp=fopen( file_patch_channels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_patch_channels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_patch_channels);
if (fwrite(Patch, sizeof(int),patch_channels_size, fp) != patch_channels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_patch_channels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_patch_channels);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[9]==1)  /////PATCH LTP / HTP////////////////////////////////////////////////////
{
if ((fp=fopen( file_patch_ltp, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_patch_ltp); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_patch_ltp);
if (fwrite(dimmer_type, sizeof(bool),patch_ltp_size, fp) != patch_ltp_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_patch_ltp); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_patch_ltp);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_patch_curves, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_patch_curves); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_patch_curves);
if (fwrite(curves, sizeof(int),patch_curves_size, fp) != patch_curves_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_patch_curves); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_patch_curves);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[10]==1)  //////PATCH CURVES/////////////////////////////////////////////////////
{
if ((fp=fopen( file_curve_ctrl_pt, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_curve_ctrl_pt); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_curve_ctrl_pt);
if (fwrite(curve_ctrl_pt, sizeof(int),curve_ctrl_size, fp) != curve_ctrl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_curve_ctrl_pt); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_curve_ctrl_pt);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_curve_spline_level, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_curve_spline_level); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_curve_spline_level);
if (fwrite(the_curve_spline_level, sizeof(int),curve_spline_level_size, fp) != curve_spline_level_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_curve_spline_level); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_curve_spline_level);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_curve_matrix, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_curve_matrix); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_curve_matrix);
if (fwrite(curve_report, sizeof(int),curve_matrix_size, fp) != curve_matrix_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_curve_matrix); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_curve_matrix);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[11]==1)  //////////////BANGER///////////////////////////////////////////////////
{
if ((fp=fopen(file_bangers_names, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_names); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_names);
if (fwrite( bangers_name, sizeof(char), banger_name_size, fp) !=   banger_name_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_names); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_bangers_names);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_bangers_types, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_types); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_types);
if (fwrite( bangers_type, sizeof(int),banger_types_size, fp) !=   banger_types_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_types); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_bangers_types);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_bangers_actions, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_actions); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_actions);
if (fwrite( bangers_action, sizeof(int),banger_actions_size, fp) !=  banger_actions_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_actions); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_bangers_actions);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_bangers_values, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_values); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_values);
if (fwrite( bangers_params, sizeof(int), banger_values_size, fp) !=   banger_values_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_values); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_bangers_values);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_bangers_times, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_times); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_times);
if (fwrite( bangers_delay, sizeof(float), banger_times_size, fp) !=  banger_times_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_times); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_bangers_times);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_bangers_alarms, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_bangers_alarms); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_alarms);
if (fwrite(string_alarm, sizeof(char), banger_alarm_size, fp) != banger_alarm_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_alarms); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_bangers_alarms);
fclose(fp);
}
 idf++;
if ((fp=fopen(file_bangers_loop, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_bangers_loop); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_loop);
if (fwrite(do_loop_banger, sizeof(bool), banger_loop_size, fp) != banger_loop_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_loop); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_bangers_loop);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_bangers_looptime, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_bangers_looptime); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_bangers_looptime);
if (fwrite(time_loop_banger, sizeof(float), banger_looptime_size, fp) != banger_looptime_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_bangers_looptime); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_bangers_looptime);
fclose(fp);
}
 idf++;

}

if(specify_who_to_save_load[12]==1) /////////////FADERS contents///////////////////////////////////////////
{
if ((fp=fopen( file_faders_state, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_faders_state); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_faders_state);
if (fwrite(Fader, sizeof(unsigned char), faders_saving_size, fp) != faders_saving_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_faders_state); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_faders_state);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_dock_selected, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_selected); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_selected);
if (fwrite(DockIsSelected, sizeof(bool), dock_selected_size, fp) != dock_selected_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_selected); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_selected);
fclose(fp);
}

 idf++;
if ((fp=fopen( file_dock_type, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_type); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_type);
if (fwrite(DockTypeIs, sizeof(unsigned char), dock_type_size, fp) != dock_type_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_type); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_type);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_dock_net, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_net); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_net);
if (fwrite(DockNetIs, sizeof(unsigned char), dock_net_size, fp) != dock_net_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_net); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_net);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_dock_name, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_name); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_name);
if (fwrite(DockName, sizeof(char), dock_name_size, fp) != dock_name_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_name); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_name);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_dock_channels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_channels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_channels);
if (fwrite(FaderDockContains, sizeof(unsigned char), dock_channels_size, fp) != dock_channels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_channels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_channels);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_fader_locked, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_locked); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_locked);
if (fwrite(FaderLocked, sizeof(bool), fader_locked_size, fp) != fader_locked_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_locked); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_fader_locked);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_fader_locked_full, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_locked_full); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_locked_full);
if (fwrite(LockFader_is_FullLevel, sizeof(bool), fader_locked_full_size, fp) != fader_locked_full_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_locked_full); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_fader_locked_full);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_fader_before_lock, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_before_lock); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_before_lock);
if (fwrite(StateOfFaderBeforeLock, sizeof(unsigned char), fader_before_lock_size, fp) != fader_before_lock_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_before_lock); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_fader_before_lock);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_color_to_dock, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_color_to_dock); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_color_to_dock);
if (fwrite(colorpreset_linked_to_dock, sizeof(int), fader_color_to_dock_size, fp) != fader_color_to_dock_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_color_to_dock); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_color_to_dock);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_fader_audio, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_audio); b_report_error[idf]=1;}
else
{
int temp_array_audio[48*3][6];
for(int u=0;u<48;u++)
{
for(int l=0;l<6;l++)
{
temp_array_audio[u][l]=DockHasAudioVolume[u][l];
temp_array_audio[u+48][l]=DockHasAudioPan[u][l];
temp_array_audio[u+96][l]=DockHasAudioPitch[u][l];
}
}
sprintf(string_save_load_report[idf],"Opened file %s",file_fader_audio);
if (fwrite(temp_array_audio, sizeof(int), fader_audio_size, fp) != fader_audio_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_audio); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_audio);
fclose(fp);
}
idf++;


if ((fp=fopen( file_chaser_to_fader, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_to_fader); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chaser_to_fader);
if (fwrite( ChaserAffectedToDck, sizeof(int),fader_chaser_to_fader_size, fp) != fader_chaser_to_fader_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_to_fader); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_to_fader);
fclose(fp);
}
 idf++;


if ((fp=fopen(  file_mem_to_dock, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mem_to_dock); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mem_to_dock);
if (fwrite(DockHasMem, sizeof(int), fader_mem_to_dock_size, fp) != fader_mem_to_dock_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_mem_to_dock); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_mem_to_dock);
fclose(fp);
}
 idf++;

if ((fp=fopen(  file_fader_fx, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_fx); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_fx);
if (fwrite(fader_mode_with_buffers, sizeof(int), fader_fx_size, fp) != fader_fx_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_fader_fx); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_fx);
fclose(fp);
}
 idf++;


if ((fp=fopen(  file_fader_route_fx, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_route_fx); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_route_fx);
if (fwrite(fader_fx_route, sizeof(bool), fader_route_fx_size, fp) != fader_route_fx_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_fader_route_fx); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_route_fx);
fclose(fp);
}
 idf++;

if ((fp=fopen(  file_fader_fgroup, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_fgroup); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_fgroup);
if (fwrite(fgroup, sizeof(bool),fader_fgroup_size, fp) !=fader_fgroup_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_fgroup); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_fgroup);
fclose(fp);
}
 idf++;

if ((fp=fopen(  file_fader_draw, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_draw); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_draw);
if (fwrite(DrawAffectedToDck, sizeof(int),fader_draw_size, fp) !=fader_draw_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_draw); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_draw);
fclose(fp);
}
 idf++;


if ((fp=fopen(  file_fader_echo, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_echo); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_echo);
if (fwrite(echo_affected_to_dock, sizeof(int),fader_echo_size, fp) !=fader_echo_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_echo); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_echo);
fclose(fp);
}
idf++;

//Damper
if ((fp=fopen(  file_fader_damper_on, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_damper_on); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_damper_on);
if (fwrite(fader_damper_is_on, sizeof(bool),fader_damper_on_size, fp) !=fader_damper_on_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_damper_on); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_damper_on);
fclose(fp);
}
idf++;

int tmp_typ[48];
for(int i=0;i<48;i++)
{
    tmp_typ[i]=Fader_dampered[i].getdampermode();
}
if ((fp=fopen(  file_fader_damper_typ, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_damper_typ); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_damper_typ);
if (fwrite(tmp_typ, sizeof(int),fader_damper_typ_size, fp) !=fader_damper_typ_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_damper_typ); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_damper_typ);
fclose(fp);
}
idf++;

float tmp_data[96];
for(int i=0;i<48;i++)
{
    tmp_data[i]=Fader_dampered[i].getdecay();
    tmp_data[i+48]=Fader_dampered[i].getdt();
}
if ((fp=fopen(  file_fader_damper_levels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_fader_damper_levels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_fader_damper_levels);
if (fwrite(tmp_data, sizeof(float),fader_damper_levels_size, fp) !=fader_damper_levels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_damper_levels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_fader_damper_levels);
fclose(fp);
}
idf++;


/*const char file_fader_damper_on[24]={"faders_damper_on.whc"};
unsigned int fader_damper_on_size=48;//bool fader_damper_is_on[48]//
const char file_fader_damper_typ[24]={"faders_damper_typ.whc"};
unsigned int fader_damper_typ_size=48;//1x 48 tmp tableau set mod
const char file_fader_damper_levels[24]={"faders_damper_lvls.whc"};
int fader_damper_levels=96;//2x48 tmp 2 tableaux pour set decay et set dt en valeur 0 - 127*/


for(int i=0;i<48;i++)
{
    if(fader_damper_is_on[i]==1)
    {
     Fader_dampered[i].fix_all_damper_state_value(Fader[i]);
     Fader_dampered[i].set_target_val(Fader[i]);
    }
}

}

if(specify_who_to_save_load[13]==1)  //Faders LFOS//////////////////////////////////////////////////////////////////
{
if ((fp=fopen( file_dock_times, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_dock_times); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_times);
if (fwrite(time_per_dock, sizeof(float),dock_times_size, fp) != dock_times_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_dock_times); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_dock_times);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_is_for_loop_selected, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_is_for_loop_selected); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_is_for_loop_selected);
if (fwrite(is_dock_for_lfo_selected, sizeof(bool),size_is_for_loop_selected, fp) != size_is_for_loop_selected)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_is_for_loop_selected); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_is_for_loop_selected);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lfo_speed, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_lfo_speed); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_lfo_speed);
if (fwrite(lfo_speed, sizeof(int),size_lfo_speed, fp) != size_lfo_speed)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_lfo_speed); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_lfo_speed);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lfo_mode_is, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lfo_mode_is); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_lfo_mode_is);
if (fwrite(lfo_mode_is, sizeof(int),size_lfo_mode_is, fp) !=  size_lfo_mode_is)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lfo_mode_is); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lfo_mode_is);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lfo_cycle_on, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lfo_cycle_on); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_lfo_cycle_on);
if (fwrite(lfo_cycle_is_on, sizeof(bool),size_lfo_cycle_on, fp) !=  size_lfo_cycle_on)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lfo_cycle_on); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lfo_cycle_on);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lfo_do_next_step, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lfo_do_next_step); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_lfo_do_next_step);
if (fwrite(lfo_do_next_step, sizeof(bool),size_lfo_do_next_step, fp) !=  size_lfo_do_next_step)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lfo_do_next_step); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lfo_do_next_step);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lfo_loop_step, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lfo_loop_step); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_lfo_loop_step);
if (fwrite(lfo_cycle_steps, sizeof(bool),size_lfo_loop_step, fp) !=  size_lfo_loop_step)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lfo_loop_step); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lfo_loop_step);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_fader_stoppos_levels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_stoppos_levels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_fader_stoppos_levels);
if (fwrite(LevelStopPos, sizeof(unsigned char),fader_stoppos_size, fp) !=  fader_stoppos_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_stoppos_levels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_stoppos_levels);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_fader_stoppos_is, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_stoppos_is); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_fader_stoppos_is);
if (fwrite(ActionnateStopOn, sizeof(bool),fader_stopposB_size, fp) != fader_stopposB_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_stoppos_is); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_stoppos_is);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_fader_ston_is, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_ston_is); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_fader_ston_is);
if (fwrite(StopPosOn, sizeof(bool),fader_ston_size, fp) != fader_ston_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_ston_is); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_ston_is);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_fader_chas_autolaunch, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_chas_autolaunch); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_fader_chas_autolaunch);
if (fwrite(autolaunch, sizeof(bool),fader_chas_autolaucnh_size, fp) !=fader_chas_autolaucnh_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_fader_chas_autolaunch); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_chas_autolaunch);
fclose(fp);
}
 idf++;

//grid affectation
if ((fp=fopen( file_fader_grid_affect, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_grid_affect); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_fader_grid_affect);
if (fwrite(faders_dock_grid_affectation, sizeof(int),fader_grid_affect_size, fp) !=fader_grid_affect_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_fader_grid_affect); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_grid_affect);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[14]==1) ////////FADER CURVES///////////////////////////////////////////////////
{
if ((fp=fopen( file_fader_curve, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_curve); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_fader_curve);
if (fwrite(FaderCurves, sizeof(int),fader_curve_size, fp) != fader_curve_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_curve); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_curve);
fclose(fp);
}
 idf++;
}
if(specify_who_to_save_load[15]==1)  ///////Minifaders Presets et LOCKS Presets////////////////////////////////////
{
if ((fp=fopen( file_fader_preset_selection, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_preset_selection); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_fader_preset_selection);
if (fwrite(minifaders_preset_selection, sizeof(bool),fader_prst_sel_size, fp) != fader_prst_sel_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_fader_preset_selection); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_fader_preset_selection);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lock_preset_is, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_is); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_lock_preset_is);
if (fwrite(lock_preset, sizeof(bool), fader_lock_preset_is_size, fp) != fader_lock_preset_is_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lock_preset_is); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lock_preset_is);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lock_preset_state, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_state); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_lock_preset_state);
if (fwrite(FaderLocked_Preset, sizeof(bool), fader_lock_preset_state_size, fp) != fader_lock_preset_state_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lock_preset_state); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lock_preset_state);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lock_preset_masteris, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_masteris); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_lock_preset_masteris);
if (fwrite(LockFader_is_FullLevel_Preset, sizeof(bool), fader_lock_preset_masteris_size, fp) != fader_lock_preset_masteris_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lock_preset_masteris); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_lock_preset_masteris);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_lock_preset_levels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_levels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_lock_preset_levels);
if (fwrite(StateOfFaderBeforeLock_Preset, sizeof(unsigned char), fader_lock_preset_levels_size, fp) != fader_lock_preset_levels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lock_preset_levels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_lock_preset_levels);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[16]==1) ///////////////////////////////////CHASERS//////////////////////////////
{
if ((fp=fopen( file_chaser_name, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_name); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_name);
if (fwrite(chaser_name, sizeof(char),chaser_name_size, fp) != chaser_name_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_name); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chaser_name);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_timeunit, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_timeunit); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_timeunit);
if (fwrite(time_unit, sizeof(float),chaser_timeunit_size, fp) !=chaser_timeunit_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_timeunit); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chaser_timeunit);
fclose(fp);
}
 idf++;



if ((fp=fopen(file_chaser_stepop, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_stepop); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_stepop);
if (fwrite( chaser_step_operation, sizeof(int),chaser_stepop_size, fp) !=chaser_stepop_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_stepop); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_stepop);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_chaser_play, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_play); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_play);
if (fwrite( chaser_is_playing, sizeof(bool),chaser_isplaying_size, fp) !=chaser_isplaying_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_play); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_play);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_chaser_loop, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_loop); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_loop);
if (fwrite( chaser_is_in_loop, sizeof(bool), chaser_loop_size, fp) != chaser_loop_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_loop); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_loop);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_way, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_way); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_chaser_way);
if (fwrite( chaser_way, sizeof(bool),chaser_way_size, fp) != chaser_way_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chaser_way); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chaser_way);
fclose(fp);
}
 idf++;


if ((fp=fopen(  file_chaser_allerretour, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_chaser_allerretour); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_chaser_allerretour);
if (fwrite( chaser_aller_retour, sizeof(bool),chaser_allerretour_size, fp) != chaser_allerretour_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",   file_chaser_allerretour); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_chaser_allerretour);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_chaser_trackon, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_trackon); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_trackon);
if (fwrite( track_is_on, sizeof(bool),chaser_trackon_size, fp) != chaser_trackon_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chaser_trackon); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_trackon);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_tracklevel, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_tracklevel); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_tracklevel);
if (fwrite( track_level, sizeof(int),chaser_track_level_size, fp) != chaser_track_level_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_chaser_tracklevel); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_tracklevel);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_trackview, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_trackview); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_trackview);
if (fwrite( position_affichage_track_num, sizeof(int),chaser_trackview_size, fp) != chaser_trackview_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_trackview); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_trackview);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_tracktype, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_tracktype); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_tracktype);
if (fwrite( TrackTypeIs, sizeof(int),chaser_tracktype_size, fp) != chaser_tracktype_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_tracktype); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_tracktype);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_chaser_trackcontent, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_trackcontent); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_trackcontent);
if (fwrite(  TrackContains, sizeof(int),chaser_trackcontent_size, fp) != chaser_trackcontent_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_trackcontent); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_trackcontent);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_stepis, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_stepis); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_stepis);
if (fwrite(  chaser_step_is, sizeof(int),chaser_stepis_size, fp) != chaser_stepis_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_stepis); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_stepis);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_beginstep, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_beginstep); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_beginstep);
if (fwrite( chaser_begin_step_is, sizeof(int),chaser_stepbeg_size, fp) != chaser_stepbeg_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_beginstep); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_beginstep);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_endstep, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_endstep); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_chaser_endstep);
if (fwrite(chaser_end_step_is, sizeof(int),chaser_stepend_size, fp) !=chaser_stepend_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_endstep); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chaser_endstep);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_chaser_timemode, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_timemode); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_timemode);
if (fwrite(chaser_time_mode, sizeof(bool),chaser_timemode_size, fp) !=chaser_timemode_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_chaser_timemode); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_chaser_timemode);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_chaser_lastaffect, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_lastaffect); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_lastaffect);
if (fwrite( view_chaser_affected_to_fader, sizeof(int),chaser_lastaffect_size, fp) !=chaser_lastaffect_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_lastaffect); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_lastaffect);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_trrackname, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_trrackname); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_trrackname);
if (fwrite( chaser_track_name, sizeof(char),chaser_tracksname_size, fp) !=chaser_tracksname_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_trrackname); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_trrackname);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_chaser_presets, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_presets); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_presets);
if (fwrite( chaser_preset, sizeof(bool),chaser_presets_size, fp) !=chaser_presets_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_presets); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_presets);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_chaser_lchpad_pos, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_lchpad_pos); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_lchpad_pos);
if (fwrite( chaser_step_launchpad, sizeof(int),chaser_lchpad_pos_size, fp) !=chaser_lchpad_pos_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_lchpad_pos); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_lchpad_pos);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_chaser_acceleroslave, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_acceleroslave); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_acceleroslave);
if (fwrite( index_slave_chaser_to_accelerometre, sizeof(bool),chaser_acceleroslave_size, fp) !=chaser_acceleroslave_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_acceleroslave); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_acceleroslave);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_chaser_has_mem, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_has_mem); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_chaser_has_mem);
if (fwrite( TrackHasMem, sizeof(int),chaser_has_mem_size, fp) !=chaser_has_mem_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_chaser_has_mem); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_chaser_has_mem);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[17]==1)  ///////MIDI AFFECTATION/////////////////////////////////////////////////////////////
{
if ((fp=fopen( file_midi_affectation, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_midi_affectation); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_midi_affectation);
if (fwrite(miditable, sizeof(int),midi_affectation_size, fp) != midi_affectation_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_midi_affectation); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_midi_affectation);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_midi_send_out, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_midi_send_out); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_midi_send_out);
if (fwrite(midi_send_out, sizeof(bool),midi_send_out_size, fp) != midi_send_out_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_midi_send_out); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_midi_send_out);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[18]==1)  ////////////MIDI cheat midi ///////////////////////////////////////////
{
if ((fp=fopen( file_midi_properties, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_midi_properties); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_midi_properties);
if (fwrite(midi_change_vel_type, sizeof(int),midi_properties_size, fp) != midi_properties_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_midi_properties); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_midi_properties);
fclose(fp);
}


if ((fp=fopen( file_midi_clock, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_midi_clock); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_midi_clock);
if(fwrite (bpm_personnal, sizeof(int),midi_clock_size, fp) != midi_clock_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_midi_clock); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_midi_clock);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[19]==1)  ///////////////////TRICHRO////////////////////////////////////////////////
{
if ((fp=fopen( file_dock_color_type, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_type); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_type);
if (fwrite(dock_color_type, sizeof(bool), dock_color_type_size, fp) != dock_color_type_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_color_type); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_color_type);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_dock_color_xy, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_xy); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_xy);
if (fwrite(x_y_picker_par_colordock, sizeof(int), dock_color_xy_size, fp) != dock_color_xy_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_color_xy); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_color_xy);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_dock_color_angle, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_angle); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_angle);
if (fwrite(angle_hue_par_colordock, sizeof(float), dock_color_angle_size, fp) != dock_color_angle_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_color_angle); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_color_angle);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_dock_color_picker, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_picker); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_picker);
if (fwrite(picker_trichro, sizeof(int), dock_color_picker_size, fp) != dock_color_picker_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_color_picker); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_color_picker);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_dock_color_ch, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_ch); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_dock_color_ch);
if (fwrite(dock_color_channels, sizeof(bool), dock_color_ch_size, fp) != dock_color_ch_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_color_ch); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_color_ch);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_dock_color_buffer, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_buffer); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_dock_color_buffer);
if (fwrite(dock_color_buffer_C, sizeof(unsigned char), dock_color_buffer_size, fp) != dock_color_buffer_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_dock_color_buffer); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_dock_color_buffer);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[20]==1)  //////////VIDEO TRACKING //////////////////////////////////////////////
{
if ((fp=fopen( file_video_channels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_video_channels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_video_channels);
if (fwrite(tracking_contents, sizeof(bool), video_channels_size, fp) != video_channels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_video_channels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_video_channels);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_video_xy, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_video_xy); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_video_xy);
if (fwrite(tracking_coordonates, sizeof(int), video_xy_size, fp) != video_xy_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_video_xy); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_video_xy);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_video_spaces_on, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_video_spaces_on); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_video_spaces_on);
if (fwrite(tracking_spaces_on_off, sizeof(bool), video_spaces_on_size, fp) != video_spaces_on_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_video_spaces_on); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_video_spaces_on);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_camera_modes, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_camera_modes); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_camera_modes);
if (fwrite(camera_modes_and_settings, sizeof(int), camera_modes_size, fp) != camera_modes_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_camera_modes); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_camera_modes);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[21]==1)  //ARDUINO//////////////////////////////////////////////////////////
{
if ((fp=fopen( file_arduino_dig_typ, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_dig_typ); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_dig_typ);
if (fwrite(  arduino_digital_type, sizeof(int),arduino_dig_typ_size, fp) !=  arduino_dig_typ_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_arduino_dig_typ); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_arduino_dig_typ);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_arduino_dig_affect, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_dig_affect); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_dig_affect);
if (fwrite(  arduino_digital_function_input, sizeof(int),arduino_dig_aff_size, fp) !=  arduino_dig_aff_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_arduino_dig_affect); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_arduino_dig_affect);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_arduino_an_typ, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_an_typ); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_an_typ);
if (fwrite(  arduino_analog_function_input, sizeof(int),arduino_an_typ_size, fp) !=  arduino_an_typ_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_arduino_an_typ); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_arduino_an_typ);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_arduino_an_aff, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_an_aff); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_an_aff);
if (fwrite( arduino_analog_attribution_input, sizeof(int),arduino_an_aff_size, fp) !=  arduino_an_aff_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_arduino_an_aff); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_arduino_an_aff);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_arduino_an_on, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_an_on); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_an_on);
if (fwrite( ventilate_analog_data, sizeof(bool),arduino_an_on_size, fp) !=  arduino_an_on_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_arduino_an_on); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_arduino_an_on);
fclose(fp);
}
 idf++;



if ((fp=fopen( file_arduino_dig_out, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_dig_out); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_dig_out);
if (fwrite( arduino_digital_function_output, sizeof(int),arduino_dig_out_size, fp) != arduino_dig_out_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_arduino_dig_out); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_arduino_dig_out);
fclose(fp);
}
idf++;


if ((fp=fopen( file_arduino_kalman_param, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_kalman_param); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_kalman_param);
if (fwrite(  kalman_params, sizeof(double),arduino_kalman_param_size, fp) != arduino_kalman_param_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_arduino_kalman_param); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_arduino_kalman_param);
fclose(fp);
}
idf++;

if ((fp=fopen( file_arduino_kalman_on, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_kalman_on); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_arduino_kalman_on);
if (fwrite(  kalman_is_on, sizeof(bool),arduino_kalman_on_size, fp) != arduino_kalman_on_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_arduino_kalman_on); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_arduino_kalman_on);
fclose(fp);
}
idf++;

Save_Arduino_Config();
 idf++;
}

if(specify_who_to_save_load[22]==1)  ////////////AUDIO CONF/////////////////////////////////////////////////
{
//autoload autopause
bool temp_audio_array[8];
for(int i=0;i<4;i++)
{
temp_audio_array[i]=audio_autoload[i];
temp_audio_array[i+4]=audio_autopause[i];
}
if ((fp=fopen( file_audio_autoloadpause, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_audio_autoloadpause); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_audio_autoloadpause);
if (fwrite( temp_audio_array, sizeof(bool),audio_autoloadpause_size, fp) != audio_autoloadpause_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_audio_autoloadpause); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_audio_autoloadpause);
fclose(fp);
}
idf++;

//file number
if ((fp=fopen( file_audio_filenumber, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_audio_filenumber); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_audio_filenumber);
if (fwrite( player_has_file_coming_from_pos, sizeof(int),audio_filenumber_size, fp) != audio_filenumber_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_audio_filenumber); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_audio_filenumber);
fclose(fp);
}
idf++;

//player position
for(int i=0;i<4;i++)
{
player_position_on_save[i]= position_of_file_in_player[i];
}
if ((fp=fopen( file_audio_playerposition, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_audio_playerposition); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_audio_playerposition);
if (fwrite( player_position_on_save, sizeof(int),audio_playerposition_size, fp) != audio_playerposition_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_audio_playerposition); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_audio_playerposition);
fclose(fp);
}
idf++;




Save_Audio_Conf()  ;
idf++;
}


if(specify_who_to_save_load[23]==1)  //////////iCAT///////////////////////////////////////////////////////
{

if ((fp=fopen( file_icat_nbsliders, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_nbsliders); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_icat_nbsliders);
if (fwrite( iCat_nbre_de_sliders, sizeof(int), icat_nbsliders_size, fp) != icat_nbsliders_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_nbsliders); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_icat_nbsliders);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_icat_posliders, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_posliders); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_icat_posliders);
if (fwrite(  iCat_pos_slider, sizeof(int),icat_posliders_size, fp) != icat_posliders_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_icat_posliders); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_posliders);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_icat_orsliders, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_orsliders); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_icat_orsliders);
if (fwrite(  iCat_orientation_slider, sizeof(bool),icat_orsliders_size, fp) !=icat_orsliders_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_orsliders); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_orsliders);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_typsliders, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_typsliders); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_icat_typsliders);
if (fwrite(  iCat_affectation_slider_type_is, sizeof(int),icat_typsliders_size, fp) !=icat_typsliders_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_typsliders); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_typsliders);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_valsliders, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_valsliders); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_icat_valsliders);
if (fwrite( iCat_affectation_slider_value_is, sizeof(int),icat_valsliders_size, fp) !=icat_valsliders_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_valsliders); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_valsliders);
fclose(fp);
}
 idf++;


if ((fp=fopen(file_icat_size_sliders, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_size_sliders); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_icat_size_sliders);
if (fwrite( ratio_iCat_slider, sizeof(int),icat_sizesliders_size, fp) !=icat_sizesliders_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_size_sliders); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_size_sliders);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_orientpage, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_orientpage); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_icat_orientpage);
if (fwrite( iCat_preset_orientation, sizeof(int),icat_orpage_size, fp) !=icat_orpage_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_orientpage); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_orientpage);
fclose(fp);
}
 idf++;


//boutons
if ((fp=fopen(file_icat_nbbutton, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_nbbutton); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_icat_nbbutton);
if (fwrite( iCat_nbre_de_boutons, sizeof(int),icat_nbbutton_size, fp) !=icat_nbbutton_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_nbbutton); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_nbbutton);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_pobutton, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_pobutton); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_pobutton);
if (fwrite( iCat_pos_bouton, sizeof(int),icat_pobutton_size, fp) !=icat_pobutton_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_pobutton); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_icat_pobutton);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_size_buttons, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_size_buttons); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_size_buttons);
if (fwrite( ratio_iCat_button, sizeof(int),icat_sizebuttons_size, fp) !=icat_sizebuttons_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_size_buttons); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_icat_size_buttons);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_icat_typbutton, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_typbutton); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_icat_typbutton);
if (fwrite(  iCat_affectation_bouton_type_is, sizeof(int), icat_typbutton_size, fp) != icat_typbutton_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_typbutton); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_typbutton);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_actbutton, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_actbutton); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_actbutton);
if (fwrite( iCat_affectation_bouton_action_is, sizeof(int),icat_actbutton_size, fp) !=icat_actbutton_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_actbutton); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_icat_actbutton);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_valbutton, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_valbutton); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_valbutton);
if (fwrite( iCat_affectation_bouton_value_is, sizeof(int),icat_valbutton_size, fp) !=icat_valbutton_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_valbutton); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_valbutton);
fclose(fp);
}
 idf++;

//strings
if ((fp=fopen(file_icat_nbstr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_nbstr); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_nbstr);
if (fwrite( iCat_nbre_de_strings, sizeof(int),icat_nbstr_size, fp) !=icat_nbstr_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_nbstr); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_nbstr);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_posstr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_posstr); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_posstr);
if (fwrite( iCat_pos_string, sizeof(int),icat_posstr_size, fp) !=icat_posstr_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_posstr); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_posstr);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_sizestr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_sizestr); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_sizestr);
if (fwrite( ratio_iCat_string, sizeof(int),icat_sizestr_size, fp) !=icat_sizestr_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_sizestr); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_sizestr);
fclose(fp);
}
 idf++;


if ((fp=fopen(file_icat_typstr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_typstr); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_typstr);
if (fwrite(iCat_affectation_string_type_is, sizeof(int),icat_typstr_size, fp) !=icat_typstr_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_typstr); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_typstr);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_actstr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_actstr); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_actstr);
if (fwrite(iCat_affectation_string_action_is, sizeof(int),icat_actstr_size, fp) !=icat_actstr_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_icat_actstr); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_actstr);
fclose(fp);
}
 idf++;

if ((fp=fopen(file_icat_valstr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_valstr); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_valstr);
if (fwrite(iCat_affectation_string_value_is, sizeof(int),icat_valstr_size, fp) !=icat_valstr_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_valstr); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_valstr);
fclose(fp);
}
 idf++;

 if ((fp=fopen(file_icat_nbzon, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_nbzon); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_nbzon);
if (fwrite(iCat_nbre_de_tracking_zone, sizeof(int),icat_nbzon_size, fp) !=icat_nbzon_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_nbzon); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_nbzon);
fclose(fp);
}
 idf++;

  if ((fp=fopen(file_icat_poszon, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_poszon); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_poszon);
if (fwrite(iCat_pos_trackzone, sizeof(int),icat_poszon_size, fp) !=icat_poszon_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_poszon); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_poszon);
fclose(fp);
}
 idf++;

 if ((fp=fopen(file_icat_sizezon, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_sizezon); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_sizezon);
if (fwrite(ratio_iCat_trackzone, sizeof(int),icat_sizezon_size, fp) !=icat_sizezon_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_sizezon); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_sizezon);
fclose(fp);
}
 idf++;

  if ((fp=fopen(file_icat_typzon, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_typzon); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_typzon);
if (fwrite(iCat_trackzone_type_is, sizeof(int),icat_typzon_size, fp) !=icat_typzon_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_typzon); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_typzon);
fclose(fp);
}
 idf++;


   if ((fp=fopen(file_icat_valzon, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_valzon); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_valzon);
if (fwrite(iCat_trackzone_affectation_is, sizeof(int),icat_valzon_size, fp) !=icat_valzon_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_valzon); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_valzon);
fclose(fp);
}
 idf++;



   if ((fp=fopen(file_icat_posTRCKzon, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_posTRCKzon); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_icat_posTRCKzon);
if (fwrite( pos_iCat_tracker, sizeof(int),icat_posTRCKzon_size, fp) !=icat_posTRCKzon_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",file_icat_posTRCKzon); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_icat_posTRCKzon);
fclose(fp);
}
 idf++;


}

if(specify_who_to_save_load[24]==1)  //POS WINDOWS USER/////////////////////////////////////////////////////
{
if ((fp=fopen( file_pos_fenetres, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_pos_fenetres); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_pos_fenetres);
if (fwrite(windows_position, sizeof(int),index_pos_fenetre_size, fp) !=  index_pos_fenetre_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_pos_fenetres); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_pos_fenetres);
fclose(fp);
}
 idf++;
Save_Window_Conf();//position

 idf++;
 //window conf
 if ((fp=fopen( file_windows, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_windows); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_windows);
if (fwrite(window_opened, sizeof(int),windows_size, fp) != windows_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_windows); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_windows);
fclose(fp);
}
idf++;

}

if(specify_who_to_save_load[25]==1)  //USER COLOR PROFILE//////////////////////////////////////////////////
{
if ((fp=fopen( file_color_profile, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_color_profile); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_color_profile);
if (fwrite( couleurs_user, sizeof(float),color_profile_size, fp) !=  color_profile_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_color_profile); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_color_profile);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[26]==1)  //KBD ASCII MAPING/////////////////////////////////////////////////////
{
if ((fp=fopen( file_kbd_ascii_map, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_kbd_ascii_map); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_kbd_ascii_map);
if (fwrite( mapping_temporaire, sizeof(int),kbd_ascii_map_size, fp) !=kbd_ascii_map_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_kbd_ascii_map); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",file_kbd_ascii_map);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[27]==1)   //////////INDEXES/////////////////////////////////////////////////////
{
write_indexes();//preparation du tableau

if ((fp=fopen( file_divers_index, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_divers_index); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_divers_index);
if (fwrite(index_report_customs, sizeof(int),index_size, fp) !=  index_size)
{ sprintf(string_save_load_report[idf],"Error writting %s",  file_divers_index); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s",  file_divers_index);
fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[28]==1)  ////////////MOVER////////////////////////////////////////////////////////
{
///////////////mems////////////////////////////////////////////////////////////
if ((fp=fopen( file_mover_mem, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mover_mem); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_mem);
if (fwrite(dock_move_xy, sizeof(int), mover_mem_saving_size, fp) != mover_mem_saving_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_mem); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_mem);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mover_mem16b, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mover_mem16b);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_mem16b);
if (fwrite(dock_move_xy_16b, sizeof(int), mover_mem_saving_size, fp) != mover_mem_saving_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_mem16b);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_mem16b);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mover_numbersteps, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mover_numbersteps);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_numbersteps);
if (fwrite(dock_moves_contains_steps, sizeof(int), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_numbersteps);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_numbersteps);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mover_stepis, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mover_stepis);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_stepis);
if (fwrite(dock_move_actual_step, sizeof(int), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_stepis);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_stepis);
fclose(fp);
}
 idf++;


valeurs_diverses[0]=invX_on;
valeurs_diverses[1]=invY_on;
valeurs_diverses[2]=Tracker_speedlevel;
valeurs_diverses[3]=dock_move_selected;
/*valeurs_diverses[4]=scale_x_index;
valeurs_diverses[5]=scale_y_index;
valeurs_diverses[6]=scale_x_end_index;
valeurs_diverses[7]=scale_y_end_index;
valeurs_diverses[8]=index_rescale_signal;
valeurs_diverses[9]=joy_sensitivity;*/
//valeurs_diverses[10]=iris_on;
//valeurs_diverses[11]=joystick_on;
//valeurs_diverses[12]=allow_slider_for_sensitivity;
valeurs_diverses[13]=position_defaut[0];
valeurs_diverses[14]=position_defaut[1];
valeurs_diverses[15]=index_spline;

if ((fp=fopen( file_mover_divers, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mover_divers);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_divers);
if (fwrite(valeurs_diverses, sizeof(int), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_divers);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_divers);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mover_spline_ratio, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_mover_spline_ratio);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_spline_ratio);
if (fwrite(spline_ratio, sizeof(float), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_spline_ratio);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_spline_ratio);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_asservis_mem, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_asservis_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_asservis_mem);
if (fwrite(dock_asservis, sizeof(int), mover_asservis_saving_size, fp) != mover_asservis_saving_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_asservis_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_asservis_mem);
fclose(fp);
}
 idf++;


if ((fp=fopen( file_mover_time, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_mover_time);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_time);
if (fwrite(dock_time, sizeof(int), mover_time_size, fp) != mover_time_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_time);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_time);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mover_autostop, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_mover_autostop);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_autostop);
if (fwrite(move_auto_stop, sizeof(bool), mover_autostop_size, fp) != mover_autostop_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_autostop);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_autostop);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mover_goto, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_mover_goto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_goto);
if (fwrite(GotoMoves, sizeof(int), mover_goto_size, fp) != mover_goto_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_goto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_goto);
fclose(fp);
}
 idf++;

if ((fp=fopen( file_mover_into, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_mover_into);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_into);
if (fwrite(Moves_Inpoint, sizeof(int), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_into);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_into);
fclose(fp);
}
 idf++;

 if ((fp=fopen( file_mover_params, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_mover_params);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_mover_params);
if (fwrite(mover_params_adresses, sizeof(int), mover_param_size, fp) != mover_param_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_mover_params);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_mover_params);
fclose(fp);
}
 idf++;



}

////////////////////////////////////////Grid////////////////////////////////////

if(specify_who_to_save_load[29]==1)
{
//les grilles
/*
if ((fp=fopen( file_grid_levels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_levels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_levels);
if (fwrite(grid_levels, sizeof(unsigned char), grid_levels_size, fp) != grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_levels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_levels);
fclose(fp);
}
idf++; */

//les grilles paquées en 4 fichiers

for(int iu=0;iu<32;iu++)
{
for (int st=0;st<1024;st++)
{
for (int ct=0;ct<513;ct++)
{
temp_grid_levels_for_save[iu][st][ct]=grid_levels[iu][st][ct];
}
}
}

if ((fp=fopen( file_grid_levels_1, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_levels_1);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_levels_1);
if (fwrite(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) != grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_levels_1);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_levels_1);
fclose(fp);
}
idf++;

for(int i=0;i<32;i++)
{
for (int s=0;s<1024;s++)
{
for (int c=0;c<513;c++)
{
temp_grid_levels_for_save[i][s][c]=grid_levels[32+i][s][c];
}
}
}
if ((fp=fopen( file_grid_levels_2, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_levels_2);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_levels_2);
if (fwrite(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) != grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_levels_2);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_levels_2);
fclose(fp);
}
idf++;
for(int i=0;i<32;i++)
{
for (int s=0;s<1024;s++)
{
for (int c=0;c<513;c++)
{
temp_grid_levels_for_save[i][s][c]=grid_levels[64+i][s][c];
}
}
}
if ((fp=fopen( file_grid_levels_3, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_levels_3);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_levels_3);
if (fwrite(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) != grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_levels_3);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_levels_3);
fclose(fp);
}
idf++;
for(int i=0;i<32;i++)
{
for (int s=0;s<1024;s++)
{
for (int c=0;c<513;c++)
{
temp_grid_levels_for_save[i][s][c]=grid_levels[96+i][s][c];
}
}
}
if ((fp=fopen( file_grid_levels_4, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_levels_4);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_levels_4);
if (fwrite(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) != grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_levels_4);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_levels_4);
fclose(fp);
}
idf++;
//fin des 4 grid levels

if ((fp=fopen( file_grid_times, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_times);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_times);
if (fwrite(grid_times, sizeof(float), grid_times_size, fp) != grid_times_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_times);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_times);
fclose(fp);
}
idf++;
if ((fp=fopen( file_grid_goto, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_goto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_goto);
if (fwrite(grid_goto, sizeof(int), grid_goto_size, fp) != grid_goto_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_goto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_goto);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_grid_seekpos, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_seekpos);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_seekpos);
if (fwrite(grid_seekpos, sizeof(int), grid_seekpos_size, fp) != grid_seekpos_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_seekpos);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_seekpos);
fclose(fp);
}
 idf++;
 if ((fp=fopen( file_grid_stoplay, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_stoplay);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_stoplay);
if (fwrite(grid_stoplay, sizeof(bool), grid_stoplay_size, fp) != grid_stoplay_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_stoplay);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_stoplay);
fclose(fp);
}
 idf++;
  if ((fp=fopen( file_grid_names, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_names);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_names);
if (fwrite(grider_name, sizeof(char), grid_names_size, fp) != grid_names_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_names);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_names);
fclose(fp);
}
 idf++;

//les grids players
if ((fp=fopen( file_gridpl_grid, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_grid);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_grid);
if (fwrite(index_grider_selected, sizeof(int), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_grid);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_grid);
fclose(fp);
}
 idf++;
if ((fp=fopen( file_gridpl_step, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_step);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_step);
if (fwrite(index_grider_step_is, sizeof(int), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_step);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_step);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_autost, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_autost);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_autost);
if (fwrite(grider_autostopmode, sizeof(bool), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_autost);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_autost);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_goto, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_goto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_goto);
if (fwrite(grider_goto_mode, sizeof(bool), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_goto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_goto);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_seekto, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_seekto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_seekto);
if (fwrite(grider_seekto_mode, sizeof(bool), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_seekto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_seekto);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_stpl, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_stpl);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_stpl);
if (fwrite(grider_stoplay_mode, sizeof(bool), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_stpl);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_stpl);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_slave, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_slave);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_slave);
if (fwrite(grid_player_slave, sizeof(bool), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_slave);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_slave);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_show, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_show);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_show);
if (fwrite( index_show_grid_player, sizeof(bool), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_show);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_show);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_accel, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_accel);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_accel);
if (fwrite( grid_crossfade_speed, sizeof(int), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_accel);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_accel);
fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_countmod, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_countmod);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_countmod);
if (fwrite( grider_count_mode, sizeof(bool), gridpl_size, fp) != gridpl_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_countmod);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_countmod);
fclose(fp);
}
idf++;

if ((fp=fopen( file_gridpl_snapfader, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_snapfader);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_snapfader);
if (fwrite( GplSnapFader, sizeof(int), gridpl_snapfader_size, fp) != gridpl_snapfader_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_snapfader);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_snapfader);
fclose(fp);
}
idf++;

//grider conf
int grider_conf[3];
grider_conf[0]=grider_begin_channel_is;
grider_conf[1]=grider_nb_col;
grider_conf[2]=grider_nb_row;
if ((fp=fopen( file_grider_conf, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grider_conf);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grider_conf);
if (fwrite( grider_conf, sizeof(int), grider_conf_size, fp) != grider_conf_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grider_conf);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grider_conf);
fclose(fp);
}
idf++;

int grider_report_cross[8];
for(int gr=0;gr<4;gr++)
{
grider_report_cross[gr]=grid_niveauX1[gr];
grider_report_cross[gr+4]=grid_niveauX2[gr];
}
if ((fp=fopen(file_gridpl_crosslv, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_gridpl_crosslv);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_gridpl_crosslv);
if (fwrite( grider_report_cross, sizeof(int), gridpl_croslv_size, fp) != gridpl_croslv_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_gridpl_crosslv);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_gridpl_crosslv);
fclose(fp);
}
idf++;


if ((fp=fopen(file_grid_count, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_count);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_count);
if (fwrite( grid_count, sizeof(int), grid_count_size, fp) !=grid_count_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_count);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_count);
fclose(fp);
}
idf++;

if ((fp=fopen(file_grided_count, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grided_count);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grided_count);
if (fwrite( grid_counted_times, sizeof(int), grid_counted_size, fp) !=grid_counted_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grided_count);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grided_count);
fclose(fp);
}
idf++;


}//fin grid

//GRIDPLAYER 1 in MEMS

if(specify_who_to_save_load[30]==1)
{
if ((fp=fopen(file_grid_in_mems, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_grid_in_mems);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_grid_in_mems);
if (fwrite( set_from_seq_gridplayer1_next_step, sizeof(int),grid_in_mems_size, fp) !=grid_in_mems_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_grid_in_mems);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_grid_in_mems);
fclose(fp);
}
idf++;
}
rest(10);

//////////PLOT

if(specify_who_to_save_load[31]==1)
{
if ((fp=fopen(file_lib_sizes_symbol, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_lib_sizes_symbol);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_lib_sizes_symbol);
if (fwrite(  size_symbol, sizeof(float),lib_sizes_symbol_size, fp) !=lib_sizes_symbol_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lib_sizes_symbol);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lib_sizes_symbol);
fclose(fp);
}
idf++;
if ((fp=fopen(file_lib_names_symbol, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_lib_names_symbol);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_lib_names_symbol);
if (fwrite(  symbol_nickname, sizeof(char),lib_names_symbol_size, fp) !=lib_names_symbol_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_lib_names_symbol);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_lib_names_symbol);
fclose(fp);
}
idf++;
if ((fp=fopen(file_plot_angles, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_angles);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_angles);
if (fwrite(  angle_symbol, sizeof(float),plot_angle_size, fp) !=plot_angle_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_angles);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_angles);
fclose(fp);
}
idf++;
if ((fp=fopen(file_plot_positions, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_positions);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_positions);
if (fwrite(  pos_symbol, sizeof(int),plot_positions_size, fp) !=plot_positions_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_positions);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_positions);
fclose(fp);
}
idf++;
if ((fp=fopen(file_plot_nbr_symbols, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_nbr_symbols);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_angles);
if (fwrite(  nbre_symbols_on_plot, sizeof(int),plot_nbr_symbols_size, fp) !=plot_nbr_symbols_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_nbr_symbols);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_nbr_symbols);
fclose(fp);
}
idf++;
if ((fp=fopen(file_plot_typ, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_typ);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_typ);
if (fwrite(  symbol_type, sizeof(int),plot_typ_size, fp) !=plot_typ_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_typ);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_typ);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_chan, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_chan);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_chan);
if (fwrite(  symbol_channel_is, sizeof(int),plot_chan_size, fp) !=plot_chan_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_chan);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_chan);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_dim, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_dim);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_dim);
if (fwrite(  symbol_dimmer_is, sizeof(int),plot_dim_size, fp) !=plot_dim_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_dim);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_dim);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_gels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_gels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_gels);
if (fwrite(  gelat, sizeof(int),plot_gels_size, fp) !=plot_gels_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_gels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_gels);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_gels_t, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_gels_t);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_gels_t);
if (fwrite(  gelat_family, sizeof(int),plot_gels_t_size, fp) !=plot_gels_t_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_gels_t);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_gels_t);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_view, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_view);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_view);
if (fwrite(  show_calc_number, sizeof(bool),plot_view_size, fp) !=plot_view_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_view);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_view);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_options_view, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_options_view);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_options_view);
if (fwrite(  plot_show_options, sizeof(bool),plot_view_options_size, fp) !=plot_view_options_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_options_view);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_options_view);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_opt_xy, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_opt_xy);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_opt_xy);
if (fwrite( relatif_plot_xy, sizeof(int),plot_opt_xy_size, fp) !=plot_opt_xy_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_opt_xy);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_opt_xy);
fclose(fp);
}
idf++;


if ((fp=fopen(file_plot_shape_type, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_type);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_shape_type);
if (fwrite( shape_type, sizeof(int),plot_shape_type_size, fp) !=plot_shape_type_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_shape_type);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_shape_type);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_attr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_attr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_shape_attr);
if (fwrite( shape_attributes, sizeof(float),plot_shape_attr_size, fp) !=plot_shape_attr_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_shape_attr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_shape_attr);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_pos, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_pos);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_shape_pos);
if (fwrite( shape_position, sizeof(int),plot_shape_pos_size, fp) !=plot_shape_pos_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_shape_pos);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_shape_pos);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_legend_name, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_legend_name);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_shape_legend_name);
if (fwrite( shape_legend_name, sizeof(char),plot_shape_legend_name_size, fp) !=plot_shape_legend_name_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_shape_legend_name);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_shape_legend_name);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_relativ_xy, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_relativ_xy);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_shape_relativ_xy);
if (fwrite( shape_relativ_position_legend_name, sizeof(int),plot_shape_relativ_xy_size, fp) !=plot_shape_relativ_xy_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_shape_relativ_xy);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_shape_relativ_xy);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_color_type, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_color_type);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_shape_color_type);
if (fwrite( shape_color_type, sizeof(int),plot_shape_color_type_size, fp) !=plot_shape_color_type_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_shape_color_type);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_shape_color_type);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_groups, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_groups);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_shape_groups);
if (fwrite( shape_groups, sizeof(int),plot_shape_groups_size, fp) !=plot_shape_groups_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_shape_groups);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_shape_groups);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_symbols_relativgroups, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_symbols_relativgroups);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_symbols_relativgroups);
if (fwrite( plot_relativxy_preset, sizeof(int),plot_symbols_relativgroups_size, fp) !=plot_symbols_relativgroups_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_symbols_relativgroups);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_symbols_relativgroups);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_symbols_notes, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_symbols_notes);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_symbols_notes);
if (fwrite( symbol_note, sizeof(char),plot_symbols_notes_size, fp) !=plot_symbols_notes_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_symbols_notes);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_symbols_notes);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_legend, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_legend);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_legend);
if (fwrite( plot_renseignements, sizeof(char),plot_legend_size, fp) !=plot_legend_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_legend);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_legend);
fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_symb_linked, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_symb_linked);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_plot_symb_linked);
if (fwrite( symbol_is_linked_to, sizeof(int),plot_symb_linked_size, fp) !=plot_symb_linked_size)
{ sprintf(string_save_load_report[idf],"Error writting %s", file_plot_symb_linked);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_plot_symb_linked);
fclose(fp);
}
idf++;

Save_Plot_Plan_config();
idf++;
}

/////DRAW
if(specify_who_to_save_load[32]==1)
{
if ((fp=fopen( file_draw_presetsz, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_draw_presetsz); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_draw_presetsz);
if (fwrite(draw_preset_parameters, sizeof(int),draw_presetsz_size, fp) !=  draw_presetsz_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_draw_presetsz); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_draw_presetsz);
fclose(fp);
}
idf++;

if ((fp=fopen( file_draw_levels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_draw_levels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_draw_levels);
if (fwrite(draw_preset_levels, sizeof(float),draw_levels_size, fp) !=  draw_levels_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_draw_levels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_draw_levels);
fclose(fp);
}
idf++;

if ((fp=fopen( file_draw_chrouting, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_draw_chrouting); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_draw_chrouting);
if (fwrite(draw_preset_channel_routing, sizeof(int),draw_chrouting_size, fp) !=  draw_chrouting_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_draw_chrouting); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_draw_chrouting);
fclose(fp);
}
idf++;


save_draw_preset_config();
idf++;

}


//ECHO
if(specify_who_to_save_load[33]==1)
{
if ((fp=fopen( file_echo_pointing_fader, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_pointing_fader); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_pointing_fader);
if (fwrite(echo_pointing_fader_num, sizeof(int),echo_pointing_fader_size, fp) !=  echo_pointing_fader_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_pointing_fader); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_pointing_fader);
fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_echo_mode, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_echo_mode); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_echo_mode);
if (fwrite(echo_is_echo_mode, sizeof(bool),echo_echo_mode_size, fp) !=  echo_echo_mode_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_echo_mode); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_echo_mode);
fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_global_param, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_global_param); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_global_param);
if (fwrite(echo_global_params, sizeof(float),echo_global_param_size, fp) !=  echo_global_param_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_global_param); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_global_param);
fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_channel_man_mode, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_channel_man_mode); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_channel_man_mode);
if (fwrite(echo_channel_manipulate_mode, sizeof(bool),echo_channel_man_mode_size, fp) !=  echo_channel_man_mode_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_channel_man_mode); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_channel_man_mode);
fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_chan_pos, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_chan_pos); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_chan_pos);
if (fwrite(echo_grid_channel_position, sizeof(int),echo_chan_pos_size, fp) !=  echo_chan_pos_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_chan_pos); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_chan_pos);
fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_levels, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_levels); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_levels);
if (fwrite(echo_levels, sizeof(float),echo_levels_size, fp) !=  echo_levels_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_levels); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_levels);
fclose(fp);
}
idf++;


if ((fp=fopen( file_echo_bounce, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_bounce); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_bounce);
if (fwrite(do_bounce, sizeof(bool),echo_bounce_size, fp) !=  echo_bounce_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_bounce); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_bounce);
fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_presets, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_presets); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_echo_presets);
if (fwrite(snap_echo_to_recall, sizeof(float),echo_presets_size, fp) !=  echo_presets_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_echo_presets); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_echo_presets);
fclose(fp);
}
idf++;
}


//WAVE
if(specify_who_to_save_load[34]==1)
{
if ((fp=fopen( file_wave_ch_slots, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_ch_slots); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_wave_ch_slots);
if (fwrite(channel_slots, sizeof(int),wave_ch_slots_size, fp) !=  wave_ch_slots_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_wave_ch_slots); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_wave_ch_slots);
fclose(fp);
}
idf++;

if ((fp=fopen( file_wave_brush_slots, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_brush_slots); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_wave_brush_slots);
if (fwrite(brush_slots, sizeof(float),wave_brush_slots_size, fp) !=  wave_brush_slots_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_wave_brush_slots); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_wave_brush_slots);
fclose(fp);
}
idf++;

if ((fp=fopen( file_wave_brush_pr, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_brush_pr); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_wave_brush_pr);
if (fwrite(lead_brush_reading, sizeof(int),wave_brush_pr_size, fp) !=  wave_brush_pr_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_wave_brush_pr); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_wave_brush_pr);
fclose(fp);
}
idf++;

float tmp_fl[2];
tmp_fl[0]=Wave_Dampered[0].getdecay();
tmp_fl[1]=Wave_Dampered[0].getdt();


if ((fp=fopen( file_wave_damp_decay, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_damp_decay); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_wave_damp_decay);
if (fwrite(tmp_fl, sizeof(float),wave_damp_decay_size, fp) !=  wave_damp_decay_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_wave_damp_decay); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_wave_damp_decay);
fclose(fp);
}


}


//personnal presets
if(specify_who_to_save_load[35]==1)
{

if ((fp=fopen( file_save_preset, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_save_preset); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_save_preset);
if (fwrite(preset_specify_who_to_save_load, sizeof(bool),save_preset_size, fp) !=  save_preset_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_save_preset); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_save_preset);
fclose(fp);
}
idf++;

if ((fp=fopen( file_save_pdf, "wb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_save_pdf); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",  file_save_pdf);
if (fwrite(specify_who_to_save_PDF, sizeof(bool),save_pdf_size, fp) !=  save_pdf_size)
{
sprintf(string_save_load_report[idf],"Error writting %s", file_save_pdf); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Saved file %s", file_save_pdf);
fclose(fp);
}
idf++;

}


//reroll
strcpy(rep,"");
sprintf(rep,"%s",mondirectory);
chdir (rep);

//hors boucle
Save_Launchpad_RetroLight();

if(specify_who_to_save_load[22]==1)
{Save_audiofiles_cues(); idf++; }
//reroll
strcpy(rep,"");
sprintf(rep,"%s",mondirectory);
chdir (rep);
detect_error_on_save_load();
if(there_is_an_error_on_save_load==1){index_show_save_load_report=1;} else {index_show_save_load_report=0;}

index_is_saving=0;
return(0);
}


int Load_Show()
{
sprintf(rep,"");
rest(10);
sprintf(rep,"%s\%s\%s",mondirectory,rep_saves,nomduspectacle);
chdir (rep);
FILE *fp;
reset_error_on_save_load();
reset_all_bangers();
clear_report_string();
idf=0;
//POUR RAFRAICHIR CORRECTEMENT LES VARIABLES DE POSITIONS DE FENETRES ( TIME WHEEL COLOR WHEEL) AVANT CALCULS

//christoph 18/05/15
GlobInit();
Load_Window_Conf();

if(specify_who_to_save_load[0]==1)//MEMOIRES/////////////////////////////////
{

save_load_print_to_screen("Loading Memories");
if ((fp=fopen( file_mem_existantes, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mem_existantes);  b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_mem_existantes);
if (fread(MemoiresExistantes, sizeof(bool),mem_existantes_size, fp) !=mem_existantes_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mem_existantes);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mem_existantes);
fclose(fp);
}

idf++;
if ((fp=fopen( file_memories, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_memories);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_memories);
if (fread(Memoires, sizeof(unsigned char), memories_size, fp) != memories_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_memories);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_memories);
fclose(fp);
}
idf++;
if ((fp=fopen(  file_text_mems, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_text_mems);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_text_mems);
if (fread(descriptif_memoires, sizeof(char), text_mems_size, fp) != text_mems_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_text_mems);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_text_mems);
fclose(fp);
}
idf++;
if ((fp=fopen(  file_text_annots, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_text_annots);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_text_annots);
if (fread(annotation_memoires, sizeof(char), text_annots_size, fp) != text_annots_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_text_annots);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_text_annots);
fclose(fp);
}
idf++;

if ((fp=fopen(  file_mem_detruites, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mem_detruites);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_mem_detruites);
if (fread(MemoiresDetruites, sizeof(bool), mem_deleted_size, fp) != mem_deleted_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mem_detruites);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_mem_detruites);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_mem_exclues, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_mem_exclues);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_mem_exclues);
if (fread(MemoiresExclues, sizeof(bool), mem_exclues_size, fp) != mem_exclues_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mem_exclues);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_mem_exclues);
 fclose(fp);
}
idf++;

Load_Sequenciel_Conf();
idf++;


//rafraichissement potards midi
index_send_midi_out[491]=1;
index_send_midi_out[492]=1;
index_send_midi_out[493]=1;
emit_midi_out();
rest(10);
}


if(specify_who_to_save_load[1]==1)///////MEMOIRES TIMES/////////////////////////
{
if ((fp=fopen(  file_times_mem, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_times_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_times_mem);
if (fread(Times_Memoires, sizeof(float), times_mems_size, fp) != times_mems_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_times_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_times_mem);
 fclose(fp);
}
idf++;
}


if(specify_who_to_save_load[2]==1)/////MEMOIRES LINKS///////////////////////////
{
if ((fp=fopen(  file_link_mem, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_link_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_link_mem);
if (fread(Links_Memoires, sizeof(bool), link_mem_size, fp) != link_mem_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_link_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_link_mem);
 fclose(fp);
}
idf++;
}

if(specify_who_to_save_load[3]==1)/////MEMOIRES BANGER///////////////////////////
{
if ((fp=fopen(  file_banger_call_in_mem, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_banger_call_in_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_banger_call_in_mem);
if (fread( Banger_Memoire, sizeof(int), bang_mem_size, fp) != bang_mem_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_banger_call_in_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_banger_call_in_mem);
 fclose(fp);
}
idf++;
}

if(specify_who_to_save_load[4]==1)/////MEMOIRES ratio manuel////////////////////
{
if ((fp=fopen(  file_manual_ratio_mem, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_manual_ratio_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_manual_ratio_mem);
if (fread(ratio_cross_manuel, sizeof(int), ratio_mem_size, fp) != ratio_mem_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_manual_ratio_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_manual_ratio_mem);
 fclose(fp);
}
idf++;
}


if(specify_who_to_save_load[5]==1)//channels LIST////////////////////
{
if ((fp=fopen(  file_spotlist, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_spotlist);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_spotlist);
if (fread(descriptif_projecteurs, sizeof(char), spotlist_size, fp) !=spotlist_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_spotlist);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_spotlist);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chan_macro_on, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_on);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chan_macro_on);
if (fread(macro_channel_on, sizeof(bool), chan_macro_on_size, fp) !=chan_macro_on_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chan_macro_on);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chan_macro_on);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chan_macro_reaction, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_reaction);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chan_macro_reaction);
if (fread(channel_macro_reaction, sizeof(int), chan_macro_reaction_size, fp) !=chan_macro_reaction_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chan_macro_reaction);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chan_macro_reaction);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chan_macro_action, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_action);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chan_macro_reaction);
if (fread(channel_macro_action, sizeof(int), chan_macro_action_size, fp) !=chan_macro_action_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chan_macro_action);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chan_macro_action);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chan_macro_val, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chan_macro_val);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chan_macro_val);
if (fread(channel_macro_val, sizeof(int), chan_macro_val_size, fp) !=chan_macro_val_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chan_macro_val);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chan_macro_val);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chview_ch, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_ch);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chview_ch);
if (fread(Channel_View_ROUTING, sizeof(int), chview_ch_size, fp) !=chview_ch_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chview_ch);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chview_ch);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chview_name, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_name);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chview_name);
if (fread( channel_view_Name, sizeof(char), chview_name_size, fp) !=chview_name_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chview_name);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chview_name);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chview_linktype, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_linktype);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chview_linktype);
if (fread( channel_view_link_type, sizeof(int), chview_linktype_size, fp) !=chview_linktype_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chview_linktype);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chview_linktype);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chview_linkref, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_linkref);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chview_linkref);
if (fread( channel_view_link_ref, sizeof(int), chview_linkref_size, fp) !=chview_linkref_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chview_linkref);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chview_linkref);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chview_view, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chview_view);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chview_view);
if (fread( Channel_View_MODE, sizeof(bool), chview_view_size, fp) !=chview_view_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chview_view);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chview_view);
 fclose(fp);
}
idf++;


for(int i=0;i<nbre_de_vues_circuits;i++)
{
count_number_of_channels_in_view(i);
}

//Fin list
}

if(specify_who_to_save_load[6]==1)/////Channels Direct Channels/////////////////
{
if ((fp=fopen(  file_direct_channel, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_direct_channel);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",    file_direct_channel);
if (fread(FaderDirectChan, sizeof(int), fader_direct_chan_size, fp) != fader_direct_chan_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_direct_channel);b_report_error[idf]=1;}
else {sprintf(string_save_load_report[idf],"Loaded file %s", file_direct_channel);}
 fclose(fp);
//mise à plat d init si souci
for(int i=0;i<48;i++)
{
for (int j=0;j<6;j++)
{
if(FaderDirectChan[i][j]<1){FaderDirectChan[i][j]=1;}
if(FaderDirectChan[i][j]>512){FaderDirectChan[i][j]=512;}
}
}
}
idf++;
}


if(specify_who_to_save_load[7]==1)/////Channels Freeze/////////////////////////
{
if ((fp=fopen(  file_dofreeze, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dofreeze);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_dofreeze);
if (fread(freeze_array, sizeof(bool), dofreeze_size, fp) !=dofreeze_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dofreeze);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_dofreeze);
 fclose(fp);
}
idf++;
if ((fp=fopen(  file_freeze_state, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_freeze_state);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_freeze_state);
if (fread(freeze_state, sizeof(unsigned char), freezestate_size, fp) !=freezestate_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_freeze_state);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_freeze_state);
 fclose(fp);
}
idf++;
if ((fp=fopen(  file_excluded_chan, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_excluded_chan);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_excluded_chan);
if (fread(Channels_excluded_from_grand_master, sizeof(bool), excluded_chan_size, fp) !=excluded_chan_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_excluded_chan);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_excluded_chan);
 fclose(fp);
}
idf++;

}

if(specify_who_to_save_load[8]==1)/////Patch circuits/////////////////////////////////
{
save_load_print_to_screen("Loading Patch");
if ((fp=fopen( file_patch_channels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_patch_channels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_patch_channels);
if (fread(Patch, sizeof(int),patch_channels_size, fp) !=patch_channels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_patch_channels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_patch_channels);
 fclose(fp);
}
generate_channel_view_list_from_patched_circuits();
idf++;
}


if(specify_who_to_save_load[9]==1)/////Patch LTP-HTP/////////////////////////////////
{
if ((fp=fopen(file_patch_ltp, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_patch_ltp);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_patch_ltp);
if (fread(dimmer_type, sizeof(bool),patch_ltp_size, fp) !=patch_ltp_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_patch_ltp);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_patch_ltp);
 fclose(fp);
}
idf++;
}


if(specify_who_to_save_load[10]==1)/////Patch curves///////////////////////////
{
if ((fp=fopen(file_patch_curves, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_patch_curves);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_patch_curves);
if (fread(curves, sizeof(int),patch_curves_size, fp) !=patch_curves_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_patch_curves);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_patch_curves);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_curve_ctrl_pt, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_curve_ctrl_pt);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_curve_ctrl_pt);
if (fread(curve_ctrl_pt, sizeof(int),curve_ctrl_size, fp) !=curve_ctrl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_curve_ctrl_pt);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_curve_ctrl_pt);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_curve_spline_level, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_curve_spline_level);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_curve_spline_level);
if (fread(the_curve_spline_level, sizeof(int),curve_spline_level_size, fp) !=curve_spline_level_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_curve_spline_level);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_curve_spline_level);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_curve_matrix, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_curve_matrix);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_curve_matrix);
if (fread(curve_report, sizeof(int),curve_matrix_size, fp) !=curve_matrix_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_curve_matrix);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_curve_matrix);
 fclose(fp);
}
index_curve_spline_level=the_curve_spline_level[curve_selected];
idf++;
rest(10);
}




if(specify_who_to_save_load[11]==1)/////Banger//////////////////////////////////
{
if ((fp=fopen( file_bangers_names, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_names);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_names);
if (fread(bangers_name, sizeof(char), banger_name_size, fp) !=banger_name_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_names);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_names);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_bangers_types, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_types);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_types);
if (fread(bangers_type, sizeof(int), banger_types_size, fp) !=banger_types_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_types);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_types);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_bangers_actions, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_actions);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_actions);
if (fread(bangers_action, sizeof(int), banger_actions_size, fp) !=banger_actions_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_actions);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_actions);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_bangers_values, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_values);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_values);
if (fread(bangers_params, sizeof(int), banger_values_size, fp) !=banger_values_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_values);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_values);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_bangers_times, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_values);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_times);
if (fread(bangers_delay, sizeof(float), banger_times_size, fp) !=banger_times_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_times);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_times);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_bangers_alarms, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_alarms);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_alarms);
if (fread(string_alarm, sizeof(char), banger_alarm_size, fp) !=banger_alarm_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_alarms);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_alarms);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_bangers_loop, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_loop);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_loop);
if (fread(do_loop_banger, sizeof(bool), banger_loop_size, fp) !=banger_loop_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_loop);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_loop);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_bangers_looptime, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_bangers_looptime);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_bangers_looptime);
if (fread(time_loop_banger, sizeof(float), banger_looptime_size, fp) !=banger_looptime_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_bangers_looptime);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_bangers_looptime);
 fclose(fp);
}
idf++;

}


if(specify_who_to_save_load[12]==1) ////FADERS CONTENT//////////////////////////
{
save_load_print_to_screen("Loading Faders");



if ((fp=fopen(file_dock_selected, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_selected);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_dock_selected);
if (fread(DockIsSelected, sizeof(bool),dock_selected_size, fp) !=dock_selected_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_selected);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_selected);
 fclose(fp);
}

idf++;
if ((fp=fopen(file_dock_type, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_type);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_dock_type);
if (fread(DockTypeIs, sizeof(unsigned char),dock_type_size, fp) !=dock_type_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_type);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_type);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_dock_net, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_net);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_dock_net);
if (fread(DockNetIs, sizeof(unsigned char),dock_net_size, fp) !=dock_net_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_net);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_net);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_dock_name, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_name);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_dock_name);
if (fread(DockName, sizeof(char),dock_name_size, fp) !=dock_name_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_name);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_name);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_dock_channels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_channels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_dock_channels);
if (fread(FaderDockContains, sizeof(unsigned char),dock_channels_size, fp) !=dock_channels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_channels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_channels);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_fader_locked, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_locked);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_locked);
if (fread(FaderLocked, sizeof(bool),fader_locked_size, fp) !=fader_locked_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_locked);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_fader_locked);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_fader_locked_full, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_locked_full);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_locked_full);
if (fread(LockFader_is_FullLevel, sizeof(bool),fader_locked_full_size, fp) !=fader_locked_full_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_locked_full);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_fader_locked_full);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_fader_before_lock, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_before_lock);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_before_lock);
if (fread(StateOfFaderBeforeLock, sizeof(unsigned char),fader_before_lock_size, fp) !=fader_before_lock_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_before_lock);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_fader_before_lock);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_color_to_dock, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_color_to_dock);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_color_to_dock);
if (fread(colorpreset_linked_to_dock, sizeof(int),fader_color_to_dock_size, fp) !=fader_color_to_dock_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_color_to_dock);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_color_to_dock);
 fclose(fp);
}
idf++;
//Audio dans faders
if ((fp=fopen( file_fader_audio, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_fader_audio);b_report_error[idf]=1;}
else
{
int temp_array_audio[48*3][6];
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_audio);
if (fread(temp_array_audio, sizeof(int),fader_audio_size, fp) !=fader_audio_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_fader_audio);b_report_error[idf]=1;}
else
{sprintf(string_save_load_report[idf],"Loaded file %s", file_fader_audio);
//rafraichissement tableau
for(int u=0;u<48;u++)
{
for(int l=0;l<6;l++)
{
DockHasAudioVolume[u][l]=temp_array_audio[u][l];
DockHasAudioPan[u][l]=temp_array_audio[u+48][l];
DockHasAudioPitch[u][l]=temp_array_audio[u+96][l];
}
}
}
 fclose(fp);
}
//
idf++;

if ((fp=fopen( file_chaser_to_fader, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_to_fader);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_chaser_to_fader);
if (fread(ChaserAffectedToDck, sizeof(int),fader_chaser_to_fader_size, fp) !=fader_chaser_to_fader_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_to_fader);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_to_fader);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_mem_to_dock, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_mem_to_dock);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_mem_to_dock);
if (fread(DockHasMem, sizeof(int),fader_mem_to_dock_size, fp) !=fader_mem_to_dock_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mem_to_dock);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mem_to_dock);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_fader_grid_affect, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_grid_affect);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_grid_affect);
if (fread(faders_dock_grid_affectation, sizeof(int),fader_grid_affect_size, fp) !=fader_grid_affect_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_grid_affect);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_fader_grid_affect);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_fader_fx, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_fx);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_fx);
if (fread(fader_mode_with_buffers, sizeof(int),fader_fx_size, fp) !=fader_fx_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_fx);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_fader_fx);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_fader_route_fx, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_route_fx);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_route_fx);
if (fread(fader_fx_route, sizeof(bool),fader_route_fx_size, fp) !=fader_route_fx_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_route_fx);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_fader_route_fx);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_fader_fgroup, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_fgroup);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_fader_fgroup);
if (fread(fgroup, sizeof(bool),fader_fgroup_size, fp) !=fader_fgroup_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_fgroup);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_fgroup);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_fader_draw, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_draw);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_fader_draw);
if (fread(DrawAffectedToDck, sizeof(int),fader_draw_size, fp) !=fader_draw_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_draw);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_draw);
 fclose(fp);
}
idf++;
recalculate_draw_sizes(draw_preset_selected);

if ((fp=fopen(file_fader_echo, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_echo);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_fader_echo);
if (fread(echo_affected_to_dock, sizeof(int),fader_echo_size, fp) !=fader_echo_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_echo);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_echo);
 fclose(fp);
}
idf++;

//DAMPER faders
if ((fp=fopen(file_fader_damper_on, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_damper_on);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_fader_damper_on);
if (fread(fader_damper_is_on, sizeof(bool),fader_damper_on_size, fp) !=fader_damper_on_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_damper_on);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_damper_on);
 fclose(fp);
}
idf++;

int tmp_typ[48];
if ((fp=fopen(file_fader_damper_typ, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_damper_typ);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_fader_damper_typ);
if (fread(tmp_typ, sizeof(int),fader_damper_typ_size, fp) !=fader_damper_typ_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_damper_typ);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_damper_typ);
 fclose(fp);
}
idf++;
for(int i=0;i<48;i++)
{
Fader_dampered[i].set_damper_mode(tmp_typ[i]);
}

float tmp_data[96];
if ((fp=fopen(file_fader_damper_levels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_damper_levels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_fader_damper_levels);
if (fread(tmp_data, sizeof(float),fader_damper_levels_size, fp) !=fader_damper_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_fader_damper_levels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_damper_levels);
 fclose(fp);
}
idf++;
for(int i=0;i<48;i++)
{
Fader_dampered[i].set_damper_decay(tmp_data[i]);
midi_levels[1960+i]=(int)(tmp_data[i]*127);
Fader_dampered[i].set_damper_dt(tmp_data[i+48]);
midi_levels[2056+i]=(int)(tmp_data[i+48]*127);
}
/*const char file_fader_damper_on[24]={"faders_damper_on.whc"};
unsigned int fader_damper_on_size=48;//bool fader_damper_is_on[48]//
const char file_fader_damper_typ[24]={"faders_damper_typ.whc"};
unsigned int fader_damper_typ_size=48;//1x 48 tmp tableau set mod
const char file_fader_damper_levels[24]={"faders_damper_lvls.whc"};
int fader_damper_levels=96;//2x48 tmp 2 tableaux pour set decay et set dt en valeur 0 - 127*/

if ((fp=fopen(file_faders_state, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_faders_state);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_faders_state);
if (fread(Fader, sizeof(unsigned char),faders_saving_size, fp) !=faders_saving_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_faders_state);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_faders_state);
 fclose(fp);
}

for(int i=0; i<48;i++)//maj des faders
{
     Fader_dampered[i].fix_all_damper_state_value(Fader[i]);
     Fader_dampered[i].set_target_val(Fader[i]);
     fader_set_level(i,Fader[i]);
}

idf++;


}


if(specify_who_to_save_load[13]==1) ////FADERS LFOs//////////////////////////
{
save_load_print_to_screen("Loading LFO's");

if ((fp=fopen(file_dock_times, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_dock_times);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_dock_times);
if (fread(time_per_dock, sizeof(float),dock_times_size, fp) !=dock_times_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_dock_times);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_dock_times);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_is_for_loop_selected, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_is_for_loop_selected);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_is_for_loop_selected);
if (fread(is_dock_for_lfo_selected, sizeof(bool),size_is_for_loop_selected, fp) !=size_is_for_loop_selected)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_is_for_loop_selected);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_is_for_loop_selected);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_lfo_speed, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lfo_speed);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_lfo_speed);
if (fread(lfo_speed, sizeof(int),size_lfo_speed, fp) != size_lfo_speed)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_lfo_speed);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_lfo_speed);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_lfo_mode_is, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_lfo_mode_is);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_lfo_mode_is);
if (fread(lfo_mode_is, sizeof(int),size_lfo_mode_is, fp) !=size_lfo_mode_is)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_lfo_mode_is);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_lfo_mode_is);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_lfo_cycle_on, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_lfo_cycle_on);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_lfo_cycle_on);
if (fread(lfo_cycle_is_on, sizeof(bool),size_lfo_cycle_on, fp) !=size_lfo_cycle_on)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_lfo_cycle_on);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_lfo_cycle_on);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_lfo_do_next_step, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_lfo_do_next_step);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_lfo_do_next_step);
if (fread(lfo_do_next_step, sizeof(bool),size_lfo_do_next_step, fp) !=size_lfo_do_next_step)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_lfo_do_next_step);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_lfo_do_next_step);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_lfo_loop_step, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_lfo_loop_step);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_lfo_loop_step);
if (fread(lfo_cycle_steps, sizeof(bool),size_lfo_loop_step, fp) !=size_lfo_loop_step)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_lfo_loop_step);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_lfo_loop_step);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_fader_stoppos_levels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_stoppos_levels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_stoppos_levels);
if (fread(LevelStopPos, sizeof(unsigned char),fader_stoppos_size, fp) !=fader_stoppos_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_fader_stoppos_levels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_stoppos_levels);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_fader_stoppos_is, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_stoppos_is);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_stoppos_is);
if (fread(ActionnateStopOn, sizeof(bool),fader_stopposB_size, fp) !=fader_stopposB_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_fader_stoppos_is);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_stoppos_is);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_fader_ston_is, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_ston_is);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_ston_is);
if (fread(StopPosOn, sizeof(bool),fader_ston_size, fp) !=fader_ston_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_fader_ston_is);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_ston_is);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_fader_chas_autolaunch, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_chas_autolaunch);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_chas_autolaunch);
if (fread( autolaunch, sizeof(bool),fader_chas_autolaucnh_size, fp) !=fader_chas_autolaucnh_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_fader_chas_autolaunch);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_chas_autolaunch);
 fclose(fp);
}
idf++;


}

if(specify_who_to_save_load[14]==1) ////FADERS Curves/////////////////////////
{
if ((fp=fopen(file_fader_curve, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_curve);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_curve);
if (fread(FaderCurves, sizeof(int),fader_curve_size, fp) !=fader_curve_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_fader_curve);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_curve);
 fclose(fp);
}
idf++;
}


if(specify_who_to_save_load[15]==1) ////FADERS Preset and LOCK PST//////////////////////////
{
if ((fp=fopen( file_lock_preset_is, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_is);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_lock_preset_is);
if (fread(lock_preset, sizeof(bool),fader_lock_preset_is_size, fp) !=fader_lock_preset_is_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_lock_preset_is);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_lock_preset_is);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_lock_preset_state, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_state);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_lock_preset_state);
if (fread(FaderLocked_Preset, sizeof(bool),fader_lock_preset_state_size, fp) !=fader_lock_preset_state_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_lock_preset_state);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_lock_preset_state);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_lock_preset_masteris, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_masteris);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_lock_preset_masteris);
if (fread(LockFader_is_FullLevel_Preset, sizeof(bool),fader_lock_preset_masteris_size, fp) !=fader_lock_preset_masteris_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_lock_preset_masteris);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_lock_preset_masteris);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_lock_preset_levels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lock_preset_levels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_lock_preset_levels);
if (fread(StateOfFaderBeforeLock_Preset, sizeof(unsigned char),fader_lock_preset_levels_size, fp) !=fader_lock_preset_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_lock_preset_levels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_lock_preset_levels);
 fclose(fp);
}
idf++;

for(int d=0;d<8;d++)//detect preset and load state
{
if(lock_preset[d]==1)
{
do_lock_preset(d); break;
}
}
if ((fp=fopen(file_fader_preset_selection, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_fader_preset_selection);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_fader_preset_selection);
if (fread(minifaders_preset_selection, sizeof(bool),fader_prst_sel_size, fp) !=fader_prst_sel_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_fader_preset_selection);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_fader_preset_selection);
 fclose(fp);
}

idf++;
rest(10);
}




if(specify_who_to_save_load[16]==1)/////////////CHASERS/////////////////////////
{
if ((fp=fopen(  file_chaser_name, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_name);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chaser_name);
if (fread(chaser_name, sizeof(char), chaser_name_size, fp) !=chaser_name_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_name);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_name);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chaser_timeunit, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_timeunit);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chaser_timeunit);
if (fread(time_unit, sizeof(float), chaser_timeunit_size, fp) !=chaser_timeunit_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_timeunit);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_timeunit);
 fclose(fp);
}
idf++;


if ((fp=fopen(  file_chaser_stepop, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_stepop);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_chaser_stepop);
if (fread(chaser_step_operation, sizeof(int),chaser_stepop_size, fp) !=chaser_stepop_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_stepop);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_stepop);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chaser_play, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_play);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_play);
if (fread(chaser_is_playing, sizeof(bool),chaser_isplaying_size, fp) !=chaser_isplaying_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_play);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_play);
 fclose(fp);
}
idf++;


if ((fp=fopen(  file_chaser_loop, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_loop);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_chaser_loop);
if (fread(chaser_is_in_loop, sizeof(bool),chaser_loop_size, fp) !=chaser_loop_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_loop);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_loop);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chaser_way, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_way);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_chaser_way);
if (fread(chaser_way, sizeof(bool), chaser_way_size, fp) != chaser_way_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_way);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_way);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_chaser_allerretour, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_allerretour);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_chaser_allerretour);
if (fread(chaser_aller_retour, sizeof(bool),chaser_allerretour_size, fp) != chaser_allerretour_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_chaser_allerretour);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_allerretour);
 fclose(fp);
}
idf++;






if ((fp=fopen(   file_chaser_trackon, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_trackon);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_trackon);
if (fread(track_is_on, sizeof(bool), chaser_trackon_size, fp) != chaser_trackon_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_trackon);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_trackon);
 fclose(fp);
}
idf++;


if ((fp=fopen(   file_chaser_tracklevel, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_tracklevel);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_tracklevel);
if (fread(track_level, sizeof(int), chaser_track_level_size, fp) != chaser_track_level_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_tracklevel);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_tracklevel);
 fclose(fp);
}
idf++;

if ((fp=fopen(   file_chaser_trackview, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_trackview);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_trackview);
if (fread( position_affichage_track_num, sizeof(int),chaser_trackview_size, fp) != chaser_trackview_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_trackview);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_trackview);
 fclose(fp);
}
idf++;


if ((fp=fopen(   file_chaser_tracktype, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_tracktype);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_tracktype);
if (fread(TrackTypeIs, sizeof(int),chaser_tracktype_size, fp) !=chaser_tracktype_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_tracktype);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_tracktype);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_chaser_trackcontent, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_trackcontent);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_trackcontent);
if (fread( TrackContains, sizeof(int), chaser_trackcontent_size, fp) != chaser_trackcontent_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_chaser_trackcontent);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_trackcontent);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_chaser_stepis, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_stepis);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_chaser_stepis);
if (fread(chaser_step_is, sizeof(int), chaser_stepis_size, fp) != chaser_stepis_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_stepis);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_stepis);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_chaser_beginstep, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_beginstep);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_chaser_beginstep);
if (fread(chaser_begin_step_is, sizeof(int),chaser_stepbeg_size, fp) != chaser_stepbeg_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_beginstep);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_beginstep);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_chaser_endstep, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_endstep);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_chaser_endstep);
if (fread(chaser_end_step_is, sizeof(int),chaser_stepend_size, fp) !=chaser_stepend_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_endstep);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_endstep);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_chaser_timemode, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_timemode);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_chaser_timemode);
if (fread(chaser_time_mode, sizeof(bool),chaser_timemode_size, fp) !=chaser_timemode_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_timemode);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_timemode);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_chaser_lastaffect, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_lastaffect);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_chaser_lastaffect);
if (fread(view_chaser_affected_to_fader, sizeof(int), chaser_lastaffect_size, fp) != chaser_lastaffect_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_lastaffect);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_lastaffect);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_chaser_trrackname, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_trrackname);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_chaser_trrackname);
if (fread(chaser_track_name, sizeof(char), chaser_tracksname_size, fp) != chaser_tracksname_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_trrackname);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_trrackname);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_chaser_presets, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_chaser_presets);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_chaser_presets);
if (fread(chaser_preset, sizeof(bool), chaser_presets_size, fp) != chaser_presets_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_chaser_presets);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_chaser_presets);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_chaser_lchpad_pos, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_chaser_lchpad_pos);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_chaser_lchpad_pos);
if (fread( chaser_step_launchpad, sizeof(int), chaser_lchpad_pos_size, fp) != chaser_lchpad_pos_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_lchpad_pos);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_chaser_lchpad_pos);
 fclose(fp);
}
idf++;


if ((fp=fopen(  file_chaser_acceleroslave, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_chaser_acceleroslave);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_acceleroslave);
if (fread(index_slave_chaser_to_accelerometre, sizeof(bool), chaser_acceleroslave_size, fp) != chaser_acceleroslave_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_acceleroslave);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_chaser_acceleroslave);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_chaser_has_mem, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_chaser_has_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_chaser_has_mem);
if (fread(TrackHasMem, sizeof(int), chaser_has_mem_size, fp) != chaser_has_mem_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_chaser_has_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_chaser_has_mem);
 fclose(fp);
}
idf++;

}


if(specify_who_to_save_load[17]==1) /////////////MIDI AFFECTATION///////////////
{

save_load_print_to_screen("Loading Midi Config");
//QuitMidi() ;
//InitMidi();//init avant les appels de fichiers
//midi_init_sepecial_case_key_on();
if ((fp=fopen(file_midi_affectation, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_midi_affectation);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_midi_affectation);
if (fread(miditable, sizeof(int),midi_affectation_size, fp) !=midi_affectation_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_midi_affectation);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_midi_affectation);
 fclose(fp);
}
idf++;
if ((fp=fopen(file_midi_send_out, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_midi_send_out);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_midi_send_out);
if (fread(midi_send_out, sizeof(bool),midi_send_out_size, fp) !=midi_send_out_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_midi_send_out);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_midi_send_out);
 fclose(fp);
}
idf++;
load_Fader_state_to_midi_array();//report des valeurs Faders dans le tableau midi_levels
}


if(specify_who_to_save_load[18]==1) /////////////MIDI cheat///////////////
{
if ((fp=fopen(file_midi_properties, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_midi_properties);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_midi_properties);
if (fread( midi_change_vel_type, sizeof(int),midi_properties_size, fp) !=midi_properties_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_midi_properties);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_midi_properties);
 fclose(fp);
}

if ((fp=fopen(file_midi_clock, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_midi_clock);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_midi_clock);
if (fread( bpm_personnal, sizeof(int),midi_clock_size, fp) !=midi_clock_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",   file_midi_clock);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_midi_clock);
 fclose(fp);
}



idf++;

rest(10);
}

if(specify_who_to_save_load[19]==1)//////////TRICHRO////////////////////////////
{
save_load_print_to_screen("Loading Trichromy");

if ((fp=fopen( file_dock_color_type, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_type);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_type);
if (fread(dock_color_type, sizeof(bool), dock_color_type_size, fp) != dock_color_type_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_color_type);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_color_type);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_dock_color_xy, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_xy);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_xy);
if (fread(x_y_picker_par_colordock, sizeof(int), dock_color_xy_size, fp) != dock_color_xy_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_color_xy);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_color_xy);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_dock_color_angle, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_angle);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_angle);
if (fread(angle_hue_par_colordock, sizeof(float), dock_color_angle_size, fp) != dock_color_angle_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_color_angle);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_color_angle);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_dock_color_picker, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_picker);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s", file_dock_color_picker);
if (fread(picker_trichro, sizeof(int), dock_color_picker_size, fp) != dock_color_picker_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_color_picker);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_color_picker);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_dock_color_ch, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_ch);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_dock_color_ch);
if (fread(dock_color_channels, sizeof(bool), dock_color_ch_size, fp) != dock_color_ch_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_color_ch);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_color_ch);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_dock_color_buffer, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_dock_color_buffer);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",file_dock_color_buffer);
if (fread(dock_color_buffer_C, sizeof(unsigned char), dock_color_buffer_size, fp) != dock_color_buffer_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_dock_color_buffer);b_report_error[idf]=1;}
else  sprintf(string_save_load_report[idf],"Loaded file %s", file_dock_color_buffer);
 fclose(fp);
}
idf++;
 load_etat_picker_dans_dockcolor(0);//rafraichissement du premier dock color
  //puis mise à l afihage ok du curseur hue
  vx = cos(angle_snap)*125;
  vy = sin(angle_snap)*125;
  position_curseur_hue_x= xtrichro_window+vx;
  position_curseur_hue_y=ytrichro_window+vy ;
 rest(10);
}
////////////////////////////////////////////////////////////////////////////////
//////////////VIDEO TRACKING////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_load[20]==1)/////////////TRACKING VIDEO//////////////////
{
save_load_print_to_screen("Loading Video Tracking");

if ((fp=fopen( file_video_channels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_video_channels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_video_channels);
if (fread( tracking_contents, sizeof(bool),video_channels_size, fp) !=video_channels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_video_channels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_video_channels);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_video_xy, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_video_xy);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_video_xy);
if (fread( tracking_coordonates, sizeof(int),video_xy_size, fp) !=video_xy_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_video_xy);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_video_xy);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_video_spaces_on, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_video_spaces_on);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_video_spaces_on);
if (fread(tracking_spaces_on_off, sizeof(bool),video_spaces_on_size, fp) !=video_spaces_on_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_video_spaces_on);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_video_spaces_on);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_camera_modes, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_camera_modes);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_camera_modes);
if (fread(camera_modes_and_settings, sizeof(int),camera_modes_size, fp) !=camera_modes_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_camera_modes);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_camera_modes);
 fclose(fp);
}
idf++;
refresh_ocv_settings();

}

///////////////////TIME////////////////////////////////////////////////////////
//pour pos curseur
refresh_time_cursor();

////////////////////////////////////////////////////////////////////////////////


if(specify_who_to_save_load[27]==1)/////////////////INDEXES/////////////////////
{
if ((fp=fopen(  file_divers_index, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_divers_index);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_divers_index);
if (fread(index_report_customs, sizeof(int), index_size, fp) != index_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_divers_index);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_divers_index);
 fclose(fp);
}
idf++;
}

if(specify_who_to_save_load[24]==1)/////POS window user////////////////////////////////////////
{
if ((fp=fopen(  file_pos_fenetres, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_pos_fenetres);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_pos_fenetres);
if (fread(windows_position, sizeof(int), index_pos_fenetre_size, fp) !=index_pos_fenetre_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_pos_fenetres);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_pos_fenetres);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_windows, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_windows);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_windows);
if (fread( window_opened, sizeof(int), windows_size, fp) !=windows_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_windows);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_windows);
 fclose(fp);
}
idf++;

write_window_indexes_from_list_of_windows();
rest(10);
}
load_indexes();

refresh_decay();
Load_User_Profile();

if(specify_who_to_save_load[22]==1)//AUDIO CONF//////////////////////////////////
{

Load_Audio_Conf();
idf++;

//audio autoload autopause

bool temp_audio_array[8];
if ((fp=fopen(  file_audio_autoloadpause, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_audio_autoloadpause);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_audio_autoloadpause);
if (fread( temp_audio_array, sizeof(bool), audio_autoloadpause_size, fp) !=audio_autoloadpause_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_audio_autoloadpause);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_audio_autoloadpause);
 fclose(fp);
}

for(int i=0;i<4;i++)
{
 audio_autoload[i]=temp_audio_array[i];
 audio_autopause[i]=temp_audio_array[i+4];
}
idf++;

//audio file number
if ((fp=fopen(  file_audio_filenumber, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_audio_filenumber);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_audio_filenumber);
if (fread( player_has_file_coming_from_pos, sizeof(int), audio_filenumber_size, fp) !=audio_filenumber_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_audio_filenumber);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_audio_filenumber);
 fclose(fp);
}


idf++;
//position player

if ((fp=fopen(  file_audio_playerposition, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_audio_playerposition);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_audio_playerposition);
if (fread( player_position_on_save, sizeof(int), audio_playerposition_size, fp) !=audio_playerposition_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_audio_playerposition);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_audio_playerposition);
 fclose(fp);
}


idf++;

}

if(specify_who_to_save_load[21]==1)///ARDUINO////////////////////////////////////
{
load_arduino_config();

if ((fp=fopen(  file_arduino_dig_typ, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_dig_typ);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",   file_arduino_dig_typ);
if (fread(arduino_digital_type, sizeof(int), arduino_dig_typ_size, fp) !=arduino_dig_typ_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_dig_typ);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_arduino_dig_typ);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_arduino_dig_affect, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_dig_affect);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_arduino_dig_affect);
if (fread(arduino_digital_function_input, sizeof(int), arduino_dig_aff_size, fp) !=arduino_dig_aff_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_dig_affect);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_arduino_dig_affect);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_arduino_an_typ, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_an_typ);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_arduino_an_typ);
if (fread(arduino_analog_function_input, sizeof(int), arduino_an_typ_size, fp) !=arduino_an_typ_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_an_typ);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_arduino_an_typ);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_arduino_an_aff, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_an_aff);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_arduino_an_aff);
if (fread(arduino_analog_attribution_input, sizeof(int),arduino_an_aff_size, fp) !=arduino_an_aff_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_an_aff);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_arduino_an_aff);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_arduino_an_on, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_arduino_an_on);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_arduino_an_on);
if (fread(ventilate_analog_data, sizeof(bool),arduino_an_on_size, fp) !=arduino_an_on_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_an_on);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_arduino_an_on);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_arduino_dig_out, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_dig_out);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_arduino_dig_out);
if (fread( arduino_digital_function_output, sizeof(int),arduino_dig_out_size, fp) !=arduino_dig_out_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_dig_out);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_arduino_dig_out);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_arduino_kalman_param, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_kalman_param);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_arduino_kalman_param);
if (fread( kalman_params, sizeof(double),arduino_kalman_param_size, fp) !=arduino_kalman_param_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_kalman_param);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_arduino_kalman_param);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_arduino_kalman_on, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_arduino_kalman_on);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_arduino_kalman_on);
if (fread( kalman_is_on, sizeof(bool),arduino_kalman_on_size, fp) !=arduino_kalman_on_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_arduino_kalman_on);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_arduino_kalman_on);
 fclose(fp);
}
idf++;


}


if(specify_who_to_save_load[25]==1)  ///USER COLOR PROFILE//////////////////////////////////////////////////
{
if ((fp=fopen( file_color_profile, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_color_profile); b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opened file %s",   file_color_profile);
if (fread( couleurs_user, sizeof(int),color_profile_size, fp) !=  color_profile_size)
{ sprintf(string_save_load_report[idf],"Error reading %s",  file_color_profile); b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_color_profile);
 fclose(fp);
}
 idf++;
}

if(specify_who_to_save_load[26]==1)//////clavier ascii remaping/////////////////
{
if ((fp=fopen(  file_kbd_ascii_map, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_kbd_ascii_map);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_kbd_ascii_map);
if (fread(mapping_temporaire, sizeof(int),kbd_ascii_map_size, fp) !=kbd_ascii_map_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_kbd_ascii_map);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_kbd_ascii_map);
 fclose(fp);
}
idf++;
}


if(specify_who_to_save_load[23]==1)////////ICAT//////////////////////////////////
{
if ((fp=fopen(  file_icat_nbsliders, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_nbsliders);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_icat_nbsliders);
if (fread(iCat_nbre_de_sliders, sizeof(int),icat_nbsliders_size, fp) !=icat_nbsliders_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_icat_nbsliders);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_icat_nbsliders);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_icat_posliders, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_posliders);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_icat_posliders);
if (fread(iCat_pos_slider, sizeof(int),icat_posliders_size, fp) !=icat_posliders_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_icat_posliders);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_icat_posliders);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_icat_orsliders, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_orsliders);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_icat_orsliders);
if (fread(iCat_orientation_slider, sizeof(bool),icat_orsliders_size, fp) !=icat_orsliders_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_icat_orsliders);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_icat_orsliders);
 fclose(fp);
}
idf++;

if ((fp=fopen(  file_icat_typsliders, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_typsliders);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_icat_typsliders);
if (fread(iCat_affectation_slider_type_is  , sizeof(int),icat_typsliders_size, fp) !=icat_typsliders_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_icat_typsliders);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_icat_typsliders);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_valsliders, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_icat_valsliders);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_icat_valsliders);
if (fread( iCat_affectation_slider_value_is, sizeof(int),icat_valsliders_size, fp) !=icat_valsliders_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_icat_valsliders);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_icat_valsliders);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_size_sliders, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_size_sliders);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_size_sliders);
if (fread( ratio_iCat_slider, sizeof(int),icat_sizesliders_size, fp) !=icat_sizesliders_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_size_sliders);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_size_sliders);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_orientpage, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_orientpage);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_orientpage);
if (fread(  iCat_preset_orientation, sizeof(int),icat_orpage_size, fp) !=icat_orpage_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_orientpage);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_orientpage);
 fclose(fp);
}
idf++;

if(iCat_preset_orientation[iCatPageis]==0)
   {
    L_tablier_iCat=160;H_tablier_iCat=240;
   }
   else {L_tablier_iCat=240;H_tablier_iCat=160;}

//buttons


if ((fp=fopen( file_icat_nbbutton, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_nbbutton);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_nbbutton);
if (fread( iCat_nbre_de_boutons, sizeof(int),icat_nbbutton_size, fp) !=icat_nbbutton_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_nbbutton);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_nbbutton);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_pobutton, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_pobutton);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_pobutton);
if (fread(  iCat_pos_bouton, sizeof(int),icat_pobutton_size, fp) !=icat_pobutton_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_pobutton);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_pobutton);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_size_buttons, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_size_buttons);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_size_buttons);
if (fread(   ratio_iCat_button, sizeof(int),icat_sizebuttons_size, fp) !=icat_sizebuttons_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_size_buttons);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_size_buttons);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_typbutton, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_typbutton);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_typbutton);
if (fread(   iCat_affectation_bouton_type_is, sizeof(int),icat_typbutton_size, fp) !=icat_typbutton_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_typbutton);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_typbutton);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_actbutton, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_actbutton);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_actbutton);
if (fread(  iCat_affectation_bouton_action_is, sizeof(int),icat_actbutton_size, fp) !=icat_actbutton_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_actbutton);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_actbutton);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_valbutton, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_valbutton);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_valbutton);
if (fread(  iCat_affectation_bouton_value_is, sizeof(int),icat_valbutton_size, fp) !=icat_valbutton_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_valbutton);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_valbutton);
 fclose(fp);
}
idf++;


//strings
if ((fp=fopen( file_icat_nbstr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_nbstr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_nbstr);
if (fread(  iCat_nbre_de_strings, sizeof(int),icat_nbstr_size, fp) !=icat_nbstr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_nbstr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_nbstr);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_posstr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_posstr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_posstr);
if (fread(  iCat_pos_string, sizeof(int),icat_posstr_size, fp) !=icat_posstr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_posstr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_posstr);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_sizestr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_sizestr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_sizestr);
if (fread( ratio_iCat_string, sizeof(int),icat_sizestr_size, fp) !=icat_sizestr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_sizestr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_sizestr);
 fclose(fp);
}
idf++;



if ((fp=fopen( file_icat_typstr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_typstr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_typstr);
if (fread( iCat_affectation_string_type_is, sizeof(int),icat_typstr_size, fp) !=icat_typstr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_typstr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_typstr);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_actstr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_actstr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_actstr);
if (fread(  iCat_affectation_string_action_is, sizeof(int),icat_actstr_size, fp) !=icat_actstr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_actstr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_actstr);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_valstr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_valstr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_actstr);
if (fread(   iCat_affectation_string_value_is, sizeof(int),icat_valstr_size, fp) !=icat_valstr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_valstr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_valstr);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_nbzon, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_nbzon);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_nbzon);
if (fread(  iCat_nbre_de_tracking_zone, sizeof(int),icat_nbzon_size, fp) !=icat_nbzon_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_nbzon);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_nbzon);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_poszon, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_poszon);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_poszon);
if (fread(  iCat_pos_trackzone, sizeof(int),icat_poszon_size, fp) !=icat_poszon_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_poszon);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_poszon);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_sizezon, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_sizezon);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_sizezon);
if (fread(  ratio_iCat_trackzone, sizeof(int),icat_sizezon_size, fp) !=icat_sizezon_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_sizezon);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_sizezon);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_icat_typzon, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_typzon);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_typzon);
if (fread(  iCat_trackzone_type_is, sizeof(int),icat_typzon_size, fp) !=icat_typzon_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_typzon);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_typzon);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_valzon, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_valzon);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_valzon);
if (fread(  iCat_trackzone_affectation_is, sizeof(int),icat_valzon_size, fp) !=icat_valzon_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_valzon);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_valzon);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_icat_posTRCKzon, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_icat_posTRCKzon);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_icat_posTRCKzon);
if (fread( pos_iCat_tracker, sizeof(int),icat_posTRCKzon_size, fp) !=icat_posTRCKzon_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",file_icat_posTRCKzon);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",file_icat_posTRCKzon);
 fclose(fp);
}
idf++;



}

if(specify_who_to_save_load[28]==1) //////////MOVER//////////////////////////////
{
if ((fp=fopen( file_mover_mem, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_mover_mem);
if (fread(dock_move_xy, sizeof(int),mover_mem_saving_size, fp) !=mover_mem_saving_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_mover_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_mover_mem);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_mover_mem16b, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_mem16b);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_mover_mem16b);
if (fread(dock_move_xy_16b, sizeof(int),mover_mem_saving_size, fp) !=mover_mem_saving_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s",  file_mover_mem16b);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s",  file_mover_mem16b);
 fclose(fp);
}
idf++;
//nb steps
if ((fp=fopen( file_mover_numbersteps, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_numbersteps);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_mover_numbersteps);
if (fread(dock_moves_contains_steps, sizeof(int), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_numbersteps);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_numbersteps);
 fclose(fp);
}
idf++;
//actual step is
if ((fp=fopen( file_mover_stepis, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_stepis);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_mover_stepis);
if (fread(dock_move_actual_step, sizeof(int), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_stepis);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_stepis);
 fclose(fp);
}
idf++;
//divers
if ((fp=fopen( file_mover_divers, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_divers);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_mover_divers);
if (fread(valeurs_diverses, sizeof(int), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_divers);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_divers);
 fclose(fp);
}
idf++;
//ratio spline
if ((fp=fopen( file_mover_spline_ratio, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_spline_ratio);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_mover_spline_ratio);
if (fread(spline_ratio, sizeof(float), mover_little_32file_size, fp) != mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_spline_ratio);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_spline_ratio);
 fclose(fp);
}
idf++;
//iris flous divers parametres asservis
if ((fp=fopen( file_asservis_mem, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_asservis_mem);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_asservis_mem);
if (fread(dock_asservis, sizeof(float), mover_asservis_saving_size, fp) != mover_asservis_saving_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_asservis_mem);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_asservis_mem);
 fclose(fp);
}
idf++;
//times
if ((fp=fopen( file_mover_time, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_time);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_mover_time);
if (fread(dock_time, sizeof(float), mover_time_size, fp) != mover_time_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_time);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_time);
 fclose(fp);
}
idf++;
//autostop
if ((fp=fopen( file_mover_autostop, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_autostop);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_mover_autostop);
if (fread(move_auto_stop, sizeof(bool), mover_autostop_size, fp) != mover_autostop_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_autostop);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_autostop);
 fclose(fp);
}
idf++;
//gotos
if ((fp=fopen( file_mover_goto, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_goto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_mover_goto);
if (fread(GotoMoves, sizeof(int), mover_goto_size, fp) != mover_goto_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_goto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_goto);
 fclose(fp);
}
idf++;
//intos
if ((fp=fopen( file_mover_into, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_into);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_mover_into);
if (fread(Moves_Inpoint, sizeof(int), mover_little_32file_size, fp) !=mover_little_32file_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_into);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_into);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_mover_params, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_mover_params);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_mover_params);
if (fread(mover_params_adresses, sizeof(int), mover_param_size, fp) !=mover_param_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_mover_params);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_mover_params);
 fclose(fp);
}
idf++;

xadress=mover_params_adresses[0];
yadress=mover_params_adresses[1];
irisadress=mover_params_adresses[2];
focusadress=mover_params_adresses[3];
zoomadress=mover_params_adresses[4];
invX_on=valeurs_diverses[0];
invY_on=valeurs_diverses[1];
Tracker_speedlevel=valeurs_diverses[2];
dock_move_selected=valeurs_diverses[3];
/*
scale_x_index=valeurs_diverses[4];
scale_y_index=valeurs_diverses[5];
scale_x_end_index=valeurs_diverses[6];
scale_y_end_index=valeurs_diverses[7];
index_rescale_signal=valeurs_diverses[8];*/
//joy_sensitivity=valeurs_diverses[9];
//if(joy_sensitivity<=0){joy_sensitivity=1;}
//iris_on=valeurs_diverses[10];
//joystick_on=valeurs_diverses[11];
//allow_slider_for_sensitivity=valeurs_diverses[12];
position_defaut[0]=valeurs_diverses[13];
position_defaut[1]=valeurs_diverses[14];
index_spline=valeurs_diverses[15];

Tracker_splinelevel=(int)((spline_ratio[dock_move_selected]+1)*100);
sprintf(string_zero_point_is,"Offset X %d Y %d",position_defaut[0],position_defaut[1]);

mover_params[2][0]=dock_asservis[dock_move_selected][(dock_move_actual_step[dock_move_selected])][0];
mover_params[3][0]=dock_asservis[dock_move_selected][(dock_move_actual_step[dock_move_selected])][1];
mover_params[4][0]=dock_asservis[dock_move_selected][(dock_move_actual_step[dock_move_selected])][2];


mover_params[0][0]=dock_move_xy[dock_move_selected][(dock_move_actual_step[dock_move_selected])][0];
mover_params[1][0]=dock_move_xy[dock_move_selected][(dock_move_actual_step[dock_move_selected])][1];
rest(10);
}

////////////GRID////////////////////////////////////////////////////////////////
if(specify_who_to_save_load[29]==1)
{


if ((fp=fopen( file_grid_levels_1, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_levels_1);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_levels_1);
if (fread(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) !=grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_levels_1);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_levels_1);
 fclose(fp);
}
idf++;
for(int i=0;i<32;i++)
{
for (int s=0;s<1024;s++)
{
for (int c=0;c<513;c++)
{
grid_levels[i][s][c]=temp_grid_levels_for_save[i][s][c];
}
}
}

if ((fp=fopen( file_grid_levels_2, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_levels_2);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_levels_2);
if (fread(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) !=grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_levels_2);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_levels_2);
 fclose(fp);
}
idf++;
for(int i=0;i<32;i++)
{
for (int s=0;s<1024;s++)
{
for (int c=0;c<513;c++)
{
grid_levels[i+32][s][c]=temp_grid_levels_for_save[i][s][c];
}
}
}
if ((fp=fopen( file_grid_levels_3, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_levels_3);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_levels_3);
if (fread(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) !=grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_levels_3);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_levels_3);
 fclose(fp);
}
idf++;
for(int i=0;i<32;i++)
{
for (int s=0;s<1024;s++)
{
for (int c=0;c<513;c++)
{
grid_levels[i+64][s][c]=temp_grid_levels_for_save[i][s][c];
}
}
}
if ((fp=fopen( file_grid_levels_4, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_levels_4);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_levels_4);
if (fread(temp_grid_levels_for_save, sizeof(unsigned char), grid_levels_size, fp) !=grid_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_levels_4);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_levels_4);
 fclose(fp);
}
idf++;
for(int i=0;i<32;i++)
{
for (int s=0;s<1024;s++)
{
for (int c=0;c<513;c++)
{
grid_levels[i+96][s][c]=temp_grid_levels_for_save[i][s][c];
}
}
}


//fin du groupedes grids levels




if ((fp=fopen( file_grid_times, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_times);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_times);
if (fread(grid_times, sizeof(float), grid_times_size, fp) !=grid_times_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_times);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_times);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_grid_goto, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_goto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_goto);
if (fread(grid_goto, sizeof(int), grid_goto_size, fp) !=grid_goto_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_goto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_goto);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_grid_seekpos, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_seekpos);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_seekpos);
if (fread(grid_seekpos, sizeof(int), grid_seekpos_size, fp) !=grid_seekpos_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_seekpos);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_seekpos);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_grid_stoplay, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_stoplay);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_stoplay);
if (fread(grid_stoplay, sizeof(bool), grid_stoplay_size, fp) !=grid_stoplay_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_stoplay);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_stoplay);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_grid_names, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",  file_grid_names);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_names);
if (fread(grider_name, sizeof(char), grid_names_size, fp) !=grid_names_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_names);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_names);
 fclose(fp);
}
idf++;

//les grids players
if ((fp=fopen( file_gridpl_grid, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_grid);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_grid);
if (fread(index_grider_selected, sizeof(int),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_grid);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_grid);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_step, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_step);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_step);
if (fread(index_grider_step_is, sizeof(int),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_step);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_step);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_autost, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_autost);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_autost);
if (fread(grider_autostopmode, sizeof(bool),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_autost);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_autost);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_goto, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_goto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_goto);
if (fread(grider_goto_mode, sizeof(bool),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_goto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_goto);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_seekto, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_seekto);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_seekto);
if (fread(grider_seekto_mode, sizeof(bool),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_seekto);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_seekto);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_stpl, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_stpl);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_stpl);
if (fread(grider_stoplay_mode, sizeof(bool),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_stpl);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_stpl);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_slave, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_slave);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_slave);
if (fread(grid_player_slave, sizeof(bool),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_slave);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_slave);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_show, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_show);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_show);
if (fread(index_show_grid_player, sizeof(bool),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_show);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_show);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_accel, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_accel);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_accel);
if (fread(grid_crossfade_speed, sizeof(int),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_accel);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_accel);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_gridpl_countmod, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_countmod);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_countmod);
if (fread(grider_count_mode, sizeof(bool),gridpl_size, fp) !=gridpl_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_countmod);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_countmod);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_gridpl_snapfader, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_snapfader);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_snapfader);
if (fread(GplSnapFader, sizeof(int),gridpl_snapfader_size, fp) !=gridpl_snapfader_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_snapfader);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_snapfader);
 fclose(fp);
}
idf++;


//grider conf
int grider_conf[3];
if ((fp=fopen( file_grider_conf, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_grider_conf);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grider_conf);
if (fread(grider_conf, sizeof(int),grider_conf_size, fp) !=grider_conf_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grider_conf);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grider_conf);
 fclose(fp);
}
idf++;
grider_begin_channel_is=grider_conf[0];
grider_nb_col=grider_conf[1];
grider_nb_row=grider_conf[2];

if(grider_nb_col>24){grider_nb_col=8;}
if(grider_nb_row>24){grider_nb_row=8;}
if(grider_begin_channel_is>512){grider_begin_channel_is=1;}

int grider_report_cross[8];

if ((fp=fopen( file_gridpl_crosslv, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_gridpl_crosslv);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_gridpl_crosslv);
if (fread(grider_report_cross, sizeof(int),gridpl_croslv_size, fp) !=gridpl_croslv_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_gridpl_crosslv);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_gridpl_crosslv);
 fclose(fp);
}
for(int gr=0;gr<4;gr++)
{
grid_niveauX1[gr]=grider_report_cross[gr];
grid_niveauX2[gr]=grider_report_cross[gr+4];//debug christoph ruiserge sur état crossfade 18/12/14
grid_floatX1[gr]=(float)grid_niveauX1[gr];
grid_floatX2[gr]=(float)grid_niveauX2[gr];
}
idf++;
if ((fp=fopen( file_grid_count, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_grid_count);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_grid_count);
if (fread(grid_count, sizeof(int),grid_count_size, fp) !=grid_count_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_count);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_count);
 fclose(fp);
}
idf++;
if ((fp=fopen( file_grided_count, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_grided_count);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_grided_count);
if (fread(grid_counted_times, sizeof(int),grid_counted_size, fp) !=grid_counted_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grided_count);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grided_count);
 fclose(fp);
}
idf++;

refresh_hauteur_fenetre_grider();
}//fin grid

//GRIDPLAYER 1 in MEMS
if(specify_who_to_save_load[30]==1)
{

if ((fp=fopen( file_grid_in_mems, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_grid_in_mems);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_grid_in_mems);
if (fread(set_from_seq_gridplayer1_next_step, sizeof(int),grid_in_mems_size, fp) !=grid_in_mems_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_grid_in_mems);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_grid_in_mems);
 fclose(fp);
}
idf++;
}




//personnal save preset
if(specify_who_to_save_load[35]==1)
{

if ((fp=fopen( file_save_preset, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_save_preset);  b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_save_preset);
if (fread(preset_specify_who_to_save_load, sizeof(bool),save_preset_size, fp) !=save_preset_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_save_preset);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_save_preset);
fclose(fp);
}

idf++;

if ((fp=fopen( file_save_pdf, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_save_pdf);  b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",  file_save_pdf);
if (fread(specify_who_to_save_PDF, sizeof(bool),save_pdf_size, fp) !=save_pdf_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_save_pdf);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_save_pdf);
fclose(fp);
}

idf++;
}


//DRAW
if(specify_who_to_save_load[32]==1)
{

if ((fp=fopen( file_draw_presetsz, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_draw_presetsz);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_draw_presetsz);
if (fread( draw_preset_parameters, sizeof(int),draw_presetsz_size, fp) !=draw_presetsz_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_draw_presetsz);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_draw_presetsz);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_draw_levels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_draw_levels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_draw_levels);
if (fread( draw_preset_levels, sizeof(float),draw_levels_size, fp) !=draw_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_draw_levels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_draw_levels);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_draw_chrouting, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_draw_chrouting);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_draw_chrouting);
if (fread( draw_preset_channel_routing, sizeof(int),draw_chrouting_size, fp) !=draw_chrouting_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_draw_chrouting);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_draw_chrouting);
fclose(fp);
}
idf++;

load_draw_preset_config();
idf++;
}

//ECHO
if(specify_who_to_save_load[33]==1)
{

if ((fp=fopen( file_echo_pointing_fader, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_pointing_fader);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_pointing_fader);
if (fread( echo_pointing_fader_num, sizeof(int),echo_pointing_fader_size, fp) !=echo_pointing_fader_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_pointing_fader);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_pointing_fader);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_echo_mode, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_echo_mode);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_echo_mode);
if (fread( echo_is_echo_mode, sizeof(bool),echo_echo_mode_size, fp) !=echo_echo_mode_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_echo_mode);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_echo_mode);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_global_param, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_global_param);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_global_param);
if (fread( echo_global_params, sizeof(float),echo_global_param_size, fp) !=echo_global_param_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_global_param);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_global_param);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_channel_man_mode, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_channel_man_mode);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_channel_man_mode);
if (fread( echo_channel_manipulate_mode, sizeof(bool),echo_channel_man_mode_size, fp) !=echo_channel_man_mode_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_channel_man_mode);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_channel_man_mode);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_chan_pos, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_chan_pos);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_chan_pos);
if (fread( echo_grid_channel_position, sizeof(int),echo_chan_pos_size, fp) !=echo_chan_pos_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_chan_pos);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_chan_pos);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_levels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_levels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_levels);
if (fread( echo_levels, sizeof(float),echo_levels_size, fp) !=echo_levels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_levels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_levels);
 fclose(fp);
}
idf++;


if ((fp=fopen( file_echo_bounce, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_bounce);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_bounce);
if (fread( do_bounce, sizeof(bool),echo_bounce_size, fp) !=echo_bounce_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_bounce);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_bounce);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_echo_presets, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_echo_presets);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_echo_presets);
if (fread( snap_echo_to_recall, sizeof(float),echo_presets_size, fp) !=echo_presets_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_echo_presets);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_echo_presets);
 fclose(fp);
}
idf++;

}


//WAVE
if(specify_who_to_save_load[34]==1)
{

if ((fp=fopen( file_wave_ch_slots, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_ch_slots);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_wave_ch_slots);
if (fread( channel_slots, sizeof(int),wave_ch_slots_size, fp) !=wave_ch_slots_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_wave_ch_slots);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_wave_ch_slots);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_wave_brush_slots, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_brush_slots);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_wave_brush_slots);
if (fread( brush_slots, sizeof(float),wave_brush_slots_size, fp) !=wave_brush_slots_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_wave_brush_slots);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_wave_brush_slots);
 fclose(fp);
}
idf++;

if ((fp=fopen( file_wave_brush_pr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_brush_pr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_wave_brush_pr);
if (fread( lead_brush_reading, sizeof(int),wave_brush_pr_size, fp) !=wave_brush_pr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_wave_brush_pr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_wave_brush_pr);
 fclose(fp);
}
idf++;


float tmp_fl[2];
if ((fp=fopen( file_wave_damp_decay, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_wave_damp_decay);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_wave_damp_decay);
if (fread( tmp_fl, sizeof(float),wave_damp_decay_size, fp) !=wave_damp_decay_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_wave_damp_decay);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_wave_damp_decay);
 fclose(fp);
}

for(int i=0;i<26;i++)
    {
    Wave_Dampered[i].set_damper_decay(tmp_fl[0]);
    Wave_Dampered[i].set_damper_dt(tmp_fl[1]);
    }
set_new_values_in_wave();
idf++;
}
//////LIGHTING PLOT en dernier because repertoires
if(specify_who_to_save_load[31]==1)
{

if ((fp=fopen( file_lib_sizes_symbol, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lib_sizes_symbol);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_lib_sizes_symbol);
if (fread( size_symbol, sizeof(float),lib_sizes_symbol_size, fp) !=lib_sizes_symbol_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_lib_sizes_symbol);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_lib_sizes_symbol);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_lib_names_symbol, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s", file_lib_names_symbol);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s", file_lib_names_symbol);
if (fread( symbol_nickname, sizeof(char),lib_names_symbol_size, fp) !=lib_names_symbol_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_lib_names_symbol);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_lib_names_symbol);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_angles, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_angles);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_angles);
if (fread( angle_symbol, sizeof(float),plot_angle_size, fp) !=plot_angle_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_angles);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_angles);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_positions, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_positions);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_positions);
if (fread( pos_symbol, sizeof(int),plot_positions_size, fp) !=plot_positions_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_positions);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_positions);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_plot_nbr_symbols, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_nbr_symbols);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_nbr_symbols);
if (fread(nbre_symbols_on_plot, sizeof(int),plot_nbr_symbols_size, fp) !=plot_nbr_symbols_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_nbr_symbols);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_nbr_symbols);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_typ, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_typ);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_typ);
if (fread(symbol_type, sizeof(int),plot_typ_size, fp) !=plot_typ_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_typ);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_typ);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_chan, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_chan);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_chan);
if (fread(symbol_channel_is, sizeof(int),plot_chan_size, fp) !=plot_chan_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_chan);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_chan);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_dim, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_dim);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_dim);
if (fread(symbol_dimmer_is, sizeof(int),plot_dim_size, fp) !=plot_dim_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_dim);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_dim);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_gels, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_gels);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_gels);
if (fread(gelat, sizeof(int),plot_gels_size, fp) !=plot_gels_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_gels);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_gels);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_gels_t, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_gels_t);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_gels_t);
if (fread(gelat_family, sizeof(int),plot_gels_t_size, fp) !=plot_gels_t_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_gels_t);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_gels_t);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_view, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_view);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_gels_t);
if (fread(show_calc_number, sizeof(bool),plot_view_size, fp) !=plot_view_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_view);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_view);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_options_view, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_options_view);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_options_view);
if (fread( plot_show_options, sizeof(bool),plot_view_options_size, fp) !=plot_view_options_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_options_view);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_options_view);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_opt_xy, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_opt_xy);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_options_view);
if (fread( relatif_plot_xy, sizeof(int),plot_opt_xy_size, fp) !=plot_opt_xy_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_opt_xy);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_opt_xy);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_type, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_type);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_shape_type);
if (fread( shape_type, sizeof(int),plot_shape_type_size, fp) !=plot_shape_type_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_shape_type);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_shape_type);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_attr, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_attr);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_shape_attr);
if (fread( shape_attributes, sizeof(float),plot_shape_attr_size, fp) !=plot_shape_attr_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_shape_attr);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_shape_attr);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_pos, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_pos);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_shape_pos);
if (fread( shape_position, sizeof(int),plot_shape_pos_size, fp) !=plot_shape_pos_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_shape_pos);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_shape_pos);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_legend_name, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_legend_name);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_shape_legend_name);
if (fread( shape_legend_name, sizeof(char),plot_shape_legend_name_size, fp) !=plot_shape_legend_name_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_shape_legend_name);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_shape_legend_name);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_relativ_xy, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_relativ_xy);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_shape_relativ_xy);
if (fread( shape_relativ_position_legend_name, sizeof(int),plot_shape_relativ_xy_size, fp) !=plot_shape_relativ_xy_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_shape_relativ_xy);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_shape_relativ_xy);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_color_type, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_color_type);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_shape_color_type);
if (fread( shape_color_type, sizeof(int),plot_shape_color_type_size, fp) !=plot_shape_color_type_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_shape_color_type);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_shape_color_type);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_shape_groups, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_shape_groups);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_shape_groups);
if (fread( shape_groups, sizeof(int),plot_shape_groups_size, fp) !=plot_shape_groups_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_shape_groups);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_shape_groups);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_symbols_relativgroups, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_symbols_relativgroups);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_symbols_relativgroups);
if (fread(  plot_relativxy_preset, sizeof(int),plot_symbols_relativgroups_size, fp) !=plot_symbols_relativgroups_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_symbols_relativgroups);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_symbols_relativgroups);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_plot_symbols_notes, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_symbols_notes);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_symbols_notes);
if (fread( symbol_note, sizeof(char),plot_symbols_notes_size, fp) !=plot_symbols_notes_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_symbols_notes);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_symbols_notes);
 fclose(fp);
}
idf++;


if ((fp=fopen(file_plot_legend, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_legend);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_legend);
if (fread(plot_renseignements, sizeof(char),plot_legend_size, fp) !=plot_legend_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_legend);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_legend);
 fclose(fp);
}
idf++;

if ((fp=fopen(file_plot_symb_linked, "rb"))==NULL)
{ sprintf(string_save_load_report[idf],"Error opening file %s",file_plot_symb_linked);b_report_error[idf]=1;}
else
{
sprintf(string_save_load_report[idf],"Opening file %s",file_plot_symb_linked);
if (fread(symbol_is_linked_to, sizeof(int),plot_symb_linked_size, fp) !=plot_symb_linked_size)
{ sprintf(string_save_load_report[idf],"Error Loaded %s", file_plot_symb_linked);b_report_error[idf]=1;}
else sprintf(string_save_load_report[idf],"Loaded file %s", file_plot_legend);
 fclose(fp);
}
idf++;


plot_generate_appareils_list();
//wave
    midi_send_out[2115]=midi_send_out[2114];
    midi_send_out[2117]=midi_send_out[2114];
//refresh midi out to motorized surfaces
refresh_all_midi_out_faders();


sprintf(rep,"%s",mondirectory);
chdir (rep);
scan_planfolder();
sprintf(rep,"%s\%s\%s",mondirectory,rep_saves,nomduspectacle);
chdir (rep);


Load_Plot_Plan_config();
if(index_menus_lighting_plot==4 )
{position_plan_x=0;}
idf++;

load_plan_of_theatre(Name_of_plane_is, 0);


//plot venant de load_indexes
if(view_plot_calc_number_is>3){view_plot_calc_number_is=3;}
show_calc_number[view_plot_calc_number_is]=1;
}




LoadWhiteCatColorProfil();// pas de fichiers, juste raffraichissement
rest(10);

//reroll à garder pour pas larguer midishare
sprintf(rep,"%s",mondirectory);
chdir (rep);

Load_Launchpad_RetroLight();

if(specify_who_to_save_load[22]==1)
{
scan_audiofolder();
Load_audiofiles_cues();
sprintf(rep,"%s",mondirectory);
chdir (rep);

for(int i=0;i<4;i++)
{
 audiofile_selected=player_has_file_coming_from_pos[i];
 sprintf(audiofile_name,list_audio_files[audiofile_selected]);
 if(strcmp (audiofile_name,"")!=0)
 {
 AffectSoundFile(i);
 }

rest(10);
}

}

refresh_mem_onstage(position_onstage);
refresh_mem_onpreset(position_preset);
detect_mem_before_one();
detect_error_on_save_load();
Show_report_save_load();


initiate_windows();


if(there_is_an_error_on_save_load==1){index_show_save_load_report=1;there_is_change_on_show_save_state=1;    } else {index_show_save_load_report=0;there_is_change_on_show_save_state=0;    }


return(0);
}


int save_the_show(char name_of_show[48])
{
index_is_saving=1;
char vieux_nomduspectacle[48];
sprintf(vieux_nomduspectacle, nomduspectacle);

sprintf(nomduspectacle,name_of_show);
Save_Show();
save_load_print_to_screen("Saving Arduino Conf");
sprintf(string_Last_Order,">> Saved %s  at %s",nomduspectacle,tmp_time);
timer_save_tmp=0;
sprintf(my_show_is_coming_from,"Saved in %s",nomduspectacle);//pour retracer d ou vient la conduite
idf++;
write_show_coming_from();
sprintf(nomduspectacle,vieux_nomduspectacle);
index_is_saving=0;
return(0);
}


int load_the_show(char name_of_show[48])
{
index_is_saving=1;
char vieux_nomduspectacle[48];
sprintf(vieux_nomduspectacle, nomduspectacle);
sprintf(nomduspectacle,name_of_show);
Load_Show();
sprintf(string_Last_Order,">> Loaded %s  at %s",name_of_show,tmp_time);
timer_save_tmp=0;
sprintf(nomduspectacle,vieux_nomduspectacle);
index_is_saving=0;
index_show_save_load_report=1;
sprintf(my_show_is_coming_from,"Loaded from in %s",name_of_show);//pour retracer d ou vient la conduite
write_show_coming_from();
return(0);
}

int do_wizard_reload_from_disk()
{
index_save_global_is=0;
set_all_saves_indexes_at(0);
specify_who_to_save_load[0]=1;//memories
specify_who_to_save_load[1]=1;
specify_who_to_save_load[2]=1;
specify_who_to_save_load[3]=1;
specify_who_to_save_load[4]=1;
index_is_saving=1;
Load_Show();
timer_save_tmp=0;
index_is_saving=0;
//remise en etat du systeme
set_all_saves_indexes_at(1);
index_save_global_is=1;

return(0);
}

