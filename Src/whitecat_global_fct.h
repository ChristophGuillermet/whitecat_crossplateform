
/*

   Déclaration des fonctions implantées dans : arduino_6_UNO.cpp

*/

int do_arduino_config(int cfg_X, int cfg_Y) ;

/*

   Déclaration des fonctions implantées dans : arduino_core_6_UNO.cpp

*/

int  do_arduino_draw_input() ;

/*

   Déclaration des fonctions implantées dans : arduino_device_core.cpp

*/

int arduino_init(int device) ;
int arduino_close(int device) ;

/*

   Déclaration des fonctions implantées dans : audio_core5.cpp

*/

int Load_audiofiles_cues() ;

/*

   Déclaration des fonctions implantées dans : audio_visu4.cpp

*/

int fader_niveau_son(int xp, int yp, int numero) ;
int lecteur_audio( int xp, int yp, int numero) ;

/*

   Déclaration des fonctions implantées dans : banger_core_8.cpp

*/

int Chrono_Reset() ;
int store_state_of_fader_before_bang(int fader_num) ;
int restore_state_of_fader_before_bang(int fader_num) ;
int Bang_event_back(int banger_num, int event_num) ;

/*

   Déclaration des fonctions implantées dans : banger_visu_8.cpp

*/

int alarm_window() ;

/*

   Déclaration des fonctions implantées dans : bazooKAT.cpp

*/

int fenetre_bazookat_menus(int x_menus,int y_menus) ;
int do_logical_fenetre_bazookat_menus(int x_menus,int y_menus) ;

/*

   Déclaration des fonctions implantées dans : Call_everybody_5.cpp

*/

int reset_other_index_cfg() ;
int do_logical_FunctionBoxChannel(int fx,int fy, int flarg, int fhaut, int space) ;
int FunctionBoxChannel(int fx,int fy, int flarg, int fhaut, int space) ;
int do_logical_Menus( int xmenu, int ymenu) ;
int Menus( int xmenu, int ymenu) ;

/*

   Déclaration des fonctions implantées dans : CFG_config_panel_8.cpp

*/

int init_kbd_custom() ;
int do_keyboard_config( int x_cfg,int y_cfg, int largeur_cfg, int hauteur_cfg) ;
int do_keyboard_conf(int cfgnetw_X, int cfgnetw_Y) ;
int do_core_config( int x_cfg_sc,int y_cfg_sc, int largeur_cfg_sc, int hauteur_cfg_sc) ;

/*

   Déclaration des fonctions implantées dans : CFG_screen.cpp

*/

int reload_window_positions() ;
int store_window_positions() ;
int do_screen_config( int x_cfg_sc,int y_cfg_sc, int largeur_cfg_sc, int hauteur_cfg_sc) ;

/*

   Déclaration des fonctions implantées dans : channels_10_visu.cpp

*/

int ChannelScroller( int ScrollX, int ScrollY) ;
int ClassicalChannelSpace( int xchan, int ychan,  int scroll) ;

/*

   Déclaration des fonctions implantées dans : channels_9_core.cpp

*/

int snap_channels_selection_array() ;
int channel_copy() ;
int channel_paste() ;

/*

   Déclaration des fonctions implantées dans : chasers_core_5.cpp

*/

int refresh_chaser_midi_out() ;

/*

   Déclaration des fonctions implantées dans : chasers_visu.cpp

*/

int set_cue_in_view(int xp, int yp, bool state) ;

/*

   Déclaration des fonctions implantées dans : CORE_6.cpp

*/

int reset_numeric_entry() ;
void write_text_to_log_file( const std::string &text ) ;
void clear_log_file() ;
int return_lowest(int data1, int data2) ;


/*

   Déclaration des fonctions implantées dans : dmx_enttec_pro_FTDI.cpp

*/

void FTDI_ClosePort() ;
int FTDI_ListDevices() ;
int FTDI_SendData(int label, unsigned char *data, int length) ;
int FTDI_ReceiveData(int label, unsigned char *data, unsigned int expected_length) ;
void FTDI_PurgeBuffer() ;
uint16_t FTDI_OpenDevice(int device_num) ;

/*

   Déclaration des fonctions implantées dans : dmx_ftdi_IN_test_enttec_pro.cpp

*/

void FTDI_ClosePort() ;
int FTDI_ListDevices() ;
int FTDI_SendData(int label, unsigned char *data, int length) ;
int FTDI_ReceiveData(int label, unsigned char *data, unsigned int expected_length) ;
void FTDI_PurgeBuffer() ;
uint16_t FTDI_OpenDevice(int device_num) ;

/*

   Déclaration des fonctions implantées dans : dmx_functions_13.cpp

*/

int Init_dmx_interface() ;
int Close_dmx_interface() ;
int check_if_dmx_change() ;
int SendData_to_interface() ;

/*

   Déclaration des fonctions implantées dans : dmx_functions_14.cpp

*/

int Init_A_specific_dmx_interface(int i) ;
int Init_dmx_interface() ;
int Close_A_specific_dmx_interface(int i) ;
int check_if_dmx_change() ;
int SendData_to_interface() ;

/*

   Déclaration des fonctions implantées dans : dmx_sunlite.cpp

*/

int open_sunlite() ;

/*

   Déclaration des fonctions implantées dans : Draw3.cpp

*/

int snap_state_of_draw_grid(int pr) ;

/*

   Déclaration des fonctions implantées dans : echo3.cpp

*/

int do_bouncing_levels(int ech) ;
int do_echo() ;
int do_logical_Echo_Aera(int xe, int ye) ;
int do_logical_echo_window(int xe, int ye) ;

/*

   Déclaration des fonctions implantées dans : faders_core_24.cpp

*/

int indicate_wich_fader_is_the_highest() ;
int asservissement_gridplayer(int cmptfader, int dk) ;
int DoLock(int masterfader, int locklevel) ;

/*

   Déclaration des fonctions implantées dans : faders_operations.cpp

*/

int Unselect_other_docks(int themaster, int thedock) ;

/*

   Déclaration des fonctions implantées dans : faders_visuels_26.cpp

*/

int fader_damper_commands(int _x,int _y, int fd) ;

/*

   Déclaration des fonctions implantées dans : generate_strings_arrays.cpp

*/

int generate_help_file_engl() ;
int generate_help_file_fr() ;

/*

   Déclaration des fonctions implantées dans : gestionaire_fenetres2.cpp

*/

int reset_config_indexes() ;
int clear_non_desired_values_in_window_list() ;

/*

   Déclaration des fonctions implantées dans : grand_master.cpp

*/

int do_logical_grand_master(int GMX, int GMY, int larg) ;

/*

   Déclaration des fonctions implantées dans : graphics_rebuild1.cpp

*/

int RetourInfos(int x_info,int y_info) ;

/*

   Déclaration des fonctions implantées dans : grider8.cpp

*/

int TheStepBox(int xb,int yb, int num_grid_player) ;
int TheGrid_commands ( int xb, int yb, int num_grid_player) ;
int TheGrid_divers( int xb, int yb, int num_grid_player) ;

/*

   Déclaration des fonctions implantées dans : grider_calculs8.cpp

*/

int affichage_time_format(float time_in_sec) ;
int refresh_step_in_player(int grid_number, int num_step, int grider_player) ;
int clear_a_grid_step(int grid_number, int num_step) ;
int clear_part_of_a_grid(int grid_number, int num_stepfrom, int num_stepto) ;
int clear_a_grid(int grid_number) ;
int copy_grid_partially(int from_grid_number, int from_num_step,int to_step_number, int dest_grid_number, int dest_num_step) ;
int copy_step_to_step(int from_grid_number, int from_num_step, int dest_grid_number, int dest_num_step) ;
int insert_steps(int dest_grid_number, int from_num_step,  int dest_nbr_step) ;
int gridder_prepare_cross(int grid_pl, int gr_actual_grid, int gr_actual_step) ;

/*

   Déclaration des fonctions implantées dans : grider_core8.cpp

*/

int do_logical_TheStepBox(int xb,int yb, int num_grid_player) ;

/*

   Déclaration des fonctions implantées dans : gui_boutons_rebuild1.cpp

*/

int bouton_on_view(int xp, int yp, bool state) ;

/*

   Déclaration des fonctions implantées dans : help_2.cpp

*/

int HelpWindow(int xhelp, int yhelp) ;

/*

   Déclaration des fonctions implantées dans : iCat14.cpp

*/

int init_iphone_fonts() ;
int init_iCat_data() ;

/*

   Déclaration des fonctions implantées dans : icat_core14.cpp

*/

int recalculate_iCatBuilder_window_size() ;

/*

   Déclaration des fonctions implantées dans : keyboard_functions2.cpp

*/

int generation_Tableau_noms_clavier_FR() ;
int check_channel_minus() ;

/*

   Déclaration des fonctions implantées dans : keyboard_routines2.cpp

*/

int recall_config_page() ;
int commandes_clavier() ;

/*

   Déclaration des fonctions implantées dans : list_proj_core.cpp

*/

int do_the_macro_of_the_channel(int the_chan, int num_macro) ;

/*

   Déclaration des fonctions implantées dans : list_proj_visu.cpp

*/

int Channel_macros_visu(int xlist, int ylist) ;

/*

   Déclaration des fonctions implantées dans : logicals_intres.cpp

*/

int entetes_confirmation() ;

/*

   Déclaration des fonctions implantées dans : MAIN_febrier_2014.cpp

*/

int time_doing() ;

/*

   Déclaration des fonctions implantées dans : MAIN_fevrier_2014.cpp

*/

int time_doing() ;

/*

   Déclaration des fonctions implantées dans : MAIN_janv_2014_opensource_kbd.cpp

*/

void ticker_midi_clock() ;
void ticker_WAVE() ;

/*

   Déclaration des fonctions implantées dans : midi_13.cpp

*/

int do_midi_call_order(int control) ;
int do_midi_job(int control) ;

/*

   Déclaration des fonctions implantées dans : midi_CORE.cpp

*/


/*

   Déclaration des fonctions implantées dans : midi_launchpad.cpp

*/

int define_colors() ;
int launchpad_set_led(int control, int color) ;
int launchpad_set_bool_value(int control,int value) ;

/*

   Déclaration des fonctions implantées dans : minifaders_core.cpp

*/

int all_at_zero_panel_core(int xf, int yf) ;
int mini_faders_panel_core(int xmf, int ymf, int larg) ;

/*

   Déclaration des fonctions implantées dans : minifaders_visu.cpp

*/

int draw_sign_up(int xs,int ys) ;
int draw_sign_down(int xs,int ys) ;
int draw_sign_saw(int xs,int ys) ;
int draw_sign_prev(int xs,int ys) ;
int draw_sign_next(int xs,int ys) ;
int draw_sign_up_down(int xs, int ys) ;
int show_fgroup_in_minifaders_window(int xs, int ys, int fad, int dk) ;
int all_at_zero_panel_visu(int xf, int yf) ;
int mini_faders_panel_visu(int xmf, int ymf, int larg) ;

/*

   Déclaration des fonctions implantées dans : mover_2013.cpp

*/

int reset_memoires() ;
int ClearGotoStep(int move_selected) ;
int ClearIntoStep(int move_selected) ;
int convert_bytes_to_int( BYTE bHaut, BYTE bBas) ;
int Move_refresh_xy(int move_selected) ;

/*

   Déclaration des fonctions implantées dans : mover_spline6.cpp

*/

fixed node_dist(NODE n1, NODE n2) ;
NODE dummy_node(NODE node, NODE prev) ;
void calc_tangents(void) ;
void get_control_points(NODE n1, NODE n2, int points[8]) ;
void get_control_points_backward(NODE n1, NODE n2, int points[8]) ;
void draw_spline(NODE n1, NODE n2) ;
int draw_splines(int move_selected) ;
int ShowSpline(int move_selected) ;

/*

   Déclaration des fonctions implantées dans : my_window_file_sample.cpp

*/

int do_logical_my_window_Box(int mx, int my) ;

/*

   Déclaration des fonctions implantées dans : network_artnet_3.cpp

*/

int diodes_artnet(int x_diods, int y_diods) ;
int light_temoin_universe(int incoming_artnet, int x_diods, int y_diods) ;
int light_temoin_emission(int outgoing_artnet, int x_diods, int y_diods) ;
int reset_poll_list() ;

/*

   Déclaration des fonctions implantées dans : network_MAC_adress_3.cpp

*/

int Box_IP_routing ( int macx, int macy) ;
int do_artnet_affect_config(int cfgnetw_X, int cfgnetw_Y) ;

/*

   Déclaration des fonctions implantées dans : numpad_core.cpp

*/

int do_wheel_level_job(int levelwheelis) ;

/*

   Déclaration des fonctions implantées dans : numpad_visuel.cpp

*/

int rafraichissement_padwheel() ;
int level_wheel (int xw,int yw, int rayon_k, float angle_correction) ;

/*

   Déclaration des fonctions implantées dans : patch_core.cpp

*/

int do_curve_affectation() ;

/*

   Déclaration des fonctions implantées dans : patch_splines_2.cpp

*/

fixed curve_node_dist(curve_node n1, curve_node n2) ;
curve_node dummy_curve_node(curve_node curve_Node, curve_node prev) ;
void curve_calc_tangents(void) ;
void curve_get_control_points(curve_node n1, curve_node n2, int points[8]) ;
int write_curve() ;

/*

   Déclaration des fonctions implantées dans : patch_visu.cpp

*/

int menu_curve(int XCurv, int YCurv) ;

/*

   Déclaration des fonctions implantées dans : plot.cpp

*/

int scan_planfolder() ;

/*

   Déclaration des fonctions implantées dans : plot9.cpp

*/

int draw_channel_of_symbol( int calc, int symb, int plotx, int ploty) ;
int draw_gels_of_a_symbol(int calc, int symb, int plotx, int ploty) ;
int draw_line_to_channel_of_symbol(int x1, int y1, int x2, int y2, int way) ;
int plot_draw_symbol_pc( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_fresnel( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol , int plot_calc_number_is) ;
int plot_draw_symbol_decoupe_etc_1(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_decoupe_etc_2(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_decoupe_etc_3(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_decoupe_1(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_decoupe_2(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_decoupe_3(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Par_1( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Par_2( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Par_3( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Par_4( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Horiziode_assym( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Horiziode_sym( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_BT( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_T8( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Blinder( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_Svoboda( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_ACL( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_fluo_little(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_fluo_big(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_FollowSpot1(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_FollowSpot2(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_VP1(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_VP2(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_slideprojector(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_retroprojector(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_barndoors(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_top_hat(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_color_extender(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_colorchanger(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_jalousie(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_iris(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_goboholder(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_shutter(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_motorized_mirror(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_platine_de_sol(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_littlestand(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_bigstand(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int  plot_draw_symbol_barre_de_couplage(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_echelle(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_pont50_1m(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_pont50_3m(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_pont50_jonction(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_pont30_1m(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_pont30_3m(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_pont30_jonction(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_smokemachine(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_fogmachine(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_direct(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_serviceligth(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_draw_symbol_dimmerline(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is) ;
int plot_print_neutral_symbol(int s, int plotx, int ploty) ;
int plot_symbol_list(int plotx,int ploty) ;
int plot_draw_shape_line(int plotx1, int ploty1, int plotx2, int ploty2, float sizeshape,  float alphashape, int colorpattern, bool isselected) ;
int plot_draw_shape_stripline(float plotx1, float ploty1, float plotx2, float ploty2, float sizeshape,  float alphag,int typeofline,int colorpattern, bool isselected, bool show_handle) ;
int plot_draw_rectangle(int plotx1, int ploty1, float shapesizex, float shapesizey, float shaperotation, float alphashape, int colorpattern, bool isselected) ;
int plot_draw_shape_curtain(int plotx1, int ploty1, int plotx2, int ploty2, float sizeshape,  float alphashape,int colorpattern, bool isselected) ;
int plot_draw_circle(int plotx1, int ploty1, float sizeshape,  float alphashape,   int colorpattern, bool isselected) ;
int plot_draw_slice(int plotx1, int ploty1, float sizeshape, float opening_angle, float shaperotation, float alphashape,   int colorpattern, bool isselected) ;
int plot_draw_polygon(int plotx1, int ploty1, float sizeshape, float shaperotation,int numPoints,  float alphashape,   int colorpattern, bool isselected) ;
void plot_draw_text(int plotx,int ploty, int fontsize,int fonttype,  const std::string label,float alphatext, bool isselected) ;
int plot_shape_list(int plotx,int ploty) ;
int shape_edition(int plotx, int ploty) ;
int symbol_edition_options(int plotx, int ploty) ;

/*

   Déclaration des fonctions implantées dans : plot_core9.cpp

*/

int do_a_screen_capture() ;
int do_plot_screen_capture(char capturename[25]) ;

/*

   Déclaration des fonctions implantées dans : procs_visuels_rebuild1.cpp

*/

bool wc_askConfirmWindowIsOpen() ;
int detection_over_window() ;

/*

   Déclaration des fonctions implantées dans : saves_export_import.cpp

*/

int do_reset_all_listproj() ;
int do_ASCII_import() ;

/*

   Déclaration des fonctions implantées dans : saves_export_pdf2.cpp

*/



/*

   Déclaration des fonctions implantées dans : saves_menu_8.cpp

*/

int scan_savesfolder() ;
void scan_importfolder(const char* subdir) ;
int choose_personnal_preset_binary_save_load(int xs,int ys) ;
int do_logical_choose_personnal_preset_binary_save_load(int xs,int ys) ;
int check_import_type() ;

/*

   Déclaration des fonctions implantées dans : save_show_13 REFONTE PAS OK.cpp

*/

void On_Open_name_of_directory() ;
int get_current_time() ;
int load_gel_list_numerical() ;

/*

   Déclaration des fonctions implantées dans : save_show_13.cpp

*/

void On_Open_name_of_directory() ;
int get_current_time() ;
int load_gel_list_numerical() ;

/*

   Déclaration des fonctions implantées dans : sequentiel_6_core.cpp

*/

int call_mem_onstage() ;

/*

   Déclaration des fonctions implantées dans : sequentiel_7_visu.cpp

*/

int refresh_vision_memories( int x_seq, int y_seq) ;

/*

   Déclaration des fonctions implantées dans : time_core_3.cpp

*/

int Chrono_PlayPause() ;
int do_logical_Time_Window(int xtime, int ytime, int timerayon) ;

/*

   Déclaration des fonctions implantées dans : time_visu_3.cpp

*/

int print_time_reperes(int the_time_wheel_datatype) ;
int show_foreground_chrono(int xtime, int ytime) ;
int Time_Window(int xtime, int ytime, int timerayon) ;

/*

   Déclaration des fonctions implantées dans : tracker_main14nov.cpp

*/

void Load_Fonts() ;

/*

   Déclaration des fonctions implantées dans : trichro_core2.cpp

*/

int stock_etat_picker_dans_dockcolor(int dcolor_selected) ;
int CounterClockWise ( double Pt0_X, double Pt0_Y, double Pt1_X, double Pt1_Y, double Pt2_X, double Pt2_Y ) ;
int do_colors() ;

/*

   Déclaration des fonctions implantées dans : trichro_visu2.cpp

*/

int Interface_Trichromie(int xchroma, int ychroma, int rayon, int largeurchroma) ;

/*

   Déclaration des fonctions implantées dans : video_tracking_core.cpp

*/

int set_default_image_size() ;
int Load_Video_Conf() ;

/*

   Déclaration des fonctions implantées dans : video_tracking_visu.cpp

*/

int ShowTrackers() ;
int Set_Filtering_Image() ;

/*

   Déclaration des fonctions implantées dans : wave.cpp

*/

int fenetre_wave_menus(int x_menus,int y_menus) ;

/*

   Déclaration des fonctions implantées dans : wizard.cpp

*/

int clear_wizard_store_ch_in() ;

/*

   Déclaration des fonctions implantées dans : wizard_operations.cpp

*/

int wizard_detect_unused_channels(int wizard_from_mem, int wizard_to_mem) ;
int wizard_calcul_nbre_de_mem() ;
