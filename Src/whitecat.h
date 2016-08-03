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

* \file whitecat.h
* \brief {header file for all the global variable in whitecat}
* \author Christoph Guillermet
* \version {0.8.8}
* \date {09/06/2016}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Header qui contient toutes les variables globales déclarées dans whitecat
*
*   Header for all the global variables used in whitecat
*
*/

#include "Crossplateform.h"



char versionis[72]={"ALPHA 0.8.8 - 2 AOUT 2016"};
char nickname_version[48]={"ARDUINO POWER"};

bool init_done=0;//démarrage pour éviter envoyer data pdt procedure d initialisation
/////////////////////REPERTOIRE/////////////////////////////////////////////////
char rep[1024];//repertoire avec arborescence complete du fichier
//sab 02/03/2014 char mondirectory[200];//endroit de l exe
/** Directory where is the executable file - Répertoire où se trouve l'exécutable **/
char mondirectory[512];
char working_nameis[120];
char rep_saves[10]={"saves\\"};
char nomduspectacle[48]={"last_save\\"};
char video_folder[256];
char my_show_is_coming_from[128]={"default"};

bool there_is_change_on_show_save_state=0;

int adapater_is_selected=-1; // numero d adaptateur selectionne pour adresse mac
bool right_click_for_menu=0;

////////////////////////////////////////////////////////////////////////////////
int index_liste_kbd_custom=0;
char kbd_custom[256][2];

/////////////////////////////////////////////////////////////////////////////////
enum WINDOW
{
W_SAVEREPORT=900,
W_DRAW=901,
W_TRICHROMY=902,
W_NUMPAD=903,
W_TRACKINGVIDEO=904,
W_ARTPOLLREPLY=905,
W_FADERS=906,
W_PATCH=907,
W_TIME=908,
W_SEQUENCIEL=909,
W_WAVE=910,
W_ASKCONFIRM=911,
W_PLOT=912,
W_ECHO=913,
W_LIST=914,
W_SAVE=915,
W_MAINMENU=916,
W_BANGER=917,
W_ALARM=918,
W_AUDIO=919,
W_CFGMENU=920,
W_WIZARD=921,
W_MINIFADERS=922,
W_CHASERS=923,
W_MOVER=924,
W_iCAT=925,
W_GRID=926,
W_MY_WINDOW=927
};
int max_window_identity_is=927;
int index_to_navigate_between_window=0;

int window_opened[72];//la liste des fenetres ouvertes modification en 0.4.1 d un size 64 en size 72,
//y compris dans save_show.cpp
int nbre_fenetre_actives=0;
int temp_report_window[72];


volatile int ticks_dixieme_for_icat_and_draw=0;
volatile int before_ticks_dixieme_for_icat_and_draw=0;
////////////////////AFFICHAGE///////////////////////////////////////////////////
int largeur_ecran=1368;
int hauteur_ecran=800;
int visu_performances[32];
Bitmap logo;
float myalpha=0.0;
float myalphachan=0.0;
float angle_souris=0.0,transparence_souris=1.0;
int config_color_style_is=0;
float size_faders=0.8;
//screens
int index_fullscreen=0;
int posX_mainwindow=0;//placement fenetre sur bureau
int posY_mainwindow=0;
int index_report_customs[128]; //report des fentres on off, du view dmx, theme couleur etc etc
//BOXES
float epaisseur_ligne_fader=2.0;
float demi_epaisseur_ligne_fader=1.0;
float tiers_epaisseur_ligne_fader=2.0/3;
float sizefader_epaisseur_ligne_fader=2.0*0.8;
float double_epaisseur_ligne_fader=2.0*2;
float triple_epaisseur_ligne_fader=2.0*3;
//Affichage
bool index_specify_size=0;
bool index_set_pos=0;
int windows_position[24][2];
int index_color_user_to_affect=0;
int index_color_user_selected=0;
bool receive_from_trichro=0;
float couleurs_user[12][3];
char descriptif_colors_user_conf[32];
char tmp_time[24];
//variables globales d'affichage
char string_Last_Order[256];
char string_xy_mouse[12];
char string_display_fps[5];
char string_display_dmx_params[64];
char string_niveau[4];
char string_channel[3];
char string_function[8];
/////////////////////////
bool recall_windows_onoff[24];
int recall_windows_focus_id=0;
/////////////////////////
float facteur_scroll_fader_space=10.0;
int XGConfig=670;
int YGConfig=250;


//Visuels move window

bool index_click_move_trichro=0;
bool  index_click_move_visualpad=0;

bool index_click_move_video=0;
bool index_click_move_patch=0;
bool index_click_move_time=0;
bool index_click_move_sequentiel=0;
bool index_click_move_artpollreply=0;
bool index_click_move_faderspace=0;

bool index_click_move_confirmwindow=0;
bool index_click_move_configbox=0;
bool index_clik_move_listproj=0;
bool index_click_move_save_menu=0;
bool index_click_move_savereportwindow=0;//report

bool index_click_move_banger_window=0;
bool index_click_move_cfg_window=0;

volatile bool index_snap_color_wheel_levels=0;
int previous_trichro_wheel=0;
//GEL LIST in TRICHROMY
//GUI
int gel_size_window=400;
bool show_gel_list=1;
int gel_position[4];
int call_ref_number=0;//appel clavier
//gel list trichro 0 Lee 1 Rosco 2 Gamcolor 3 Apollo
int index_gel_type_selected=0;
int refs_of_gels[4][10000]; //numerical reference
char name_of_gels[4][10000][96];//nom des gels
int rvb_of_gels[4][10000][3];//rvb of gels
float gel_transimission[4][10000];
int gel_position_selected[4];
bool show_designer_list=0;
bool index_use_transmission=0;

////////////////////RETOUR INFOS////////////////////////////////////////////////
char string_debug[120];
int scroll_y_info=0;

////////////////////APPELS/ MENUS////////////////////////////////////////////
bool index_quit=0;
bool index_main_function=1;

bool index_do_dock=0;  //do dock
bool index_do_report=0; // report de tout sur scène dans un master a full
bool index_do_modify=0; // des circuits selectionnés only. ne detruit pas le reste
bool index_main_clear=0;
bool index_type=0;
bool index_inspekt=0;//voir les etiquettes et qui controle qui
bool index_trichro_window=0; //indicateur affichage menu trichro
bool index_visual_pad=0;
bool index_video_window=0;
bool index_patch_window=0;
bool index_do_quick_save=0;
bool index_show_faders=0;
//////////////////////OVER WINDOW////////////////////////////////////////////////
bool index_over_A_window=0;
bool index_over_faderspace=0;
bool index_over_channelspace=0;
bool index_over_function_call=0; // pour eviter de clicker dans les faders quand on est en zone functions ( boutons du menu gauche)

////////////////////DMX/////////////////////////////////////////////////////////
unsigned char DmxBlock[514];
unsigned char DmxBlockPatch[514];
unsigned char artnet_backup[514];
bool do_send_on_change=0;

bool client_artnet_is_closed=0;
//refonte avril 2016 mode d interfaces DMX
const int NB_INTERFACES=6;
bool do_DMX_out[NB_INTERFACES];//transfert de myDMXinterfaceis à un tableau pour allumer différentes interfaces
bool index_init_dmx_ok[NB_INTERFACES];//pour lancer le data ou pas au lancement
//sur un tableau concerne UNIQUEMENT 2 et 3 OPEN ET PRO EN OUT
int dmx_ports_com[NB_INTERFACES];
bool auto_detect_com_port[NB_INTERFACES];

////////////////////FADERS//////////////////////////////////////////////////////
int max_faders=48;
float scroll_faderspace=0.0;
float facteur_scroll_channel_space=10.0;
float deltaTime=0.0;
int goto_scroll_faderspace=0;
//Damper effect
float scroll_target_val = 0.0;
float scroll_damp_constant = 0.1;
float scroll_spring_constant = 1;
float scroll_val = 0; //value
float scroll_val_vel = 0; //velocity
const float scroll_dt = 0.1;
bool index_stop_move=0;
float light_midi_do_order[48];
int XFader=200;
int YFader=400;

int LargeurEspaceFaderSize=largeur_ecran;
bool index_moving_fader_space=0;
bool index_moving_x_slide=0;
bool index_moving_y_slide=0;

int dock_used_by_fader_is[48];
int previous_dock_used[48];//pour autolaunch sur banger, dock + - et animations
//RETOUR ARRIERE : plante chargement contenu dépasse max attendu  :-( - fichier icat  à creuser  surement dans la lecture //sab 02/03/2014 ATTENTION IMPACT - COMMENT CONTROLER FONCTION ? unsigned char --> unsigned int
unsigned char Fader[48];
unsigned char Fader_before[48];//pour icat
unsigned char Fader_previous[48];//pour chasers autolaunch. très certainement à re organiser les backups d 'états de manière plus générale

bool DockIsSelected[48][6];

//sab 02/03/2014 ATTENTION IMPACT - COMMENT CONTROLER FONCTION ? unsigned char --> unsigned int
//christoph 22/04/14 -> unsigneed char back
unsigned char DockTypeIs[48][6];//0: dock de niveau normal // 1: linké au couleurs de la trichro
// 2:artnet IN // 3: DMX IN //4 video // 5 memoire // 6 lecteur audio volume 7 pan 8 picth / 9 :vide et clearé / 10: direct chan mode
// 11:FX // 12: Grid // 13: groupe de faders // 14:Mover // 15: Draw // 16: echo
unsigned char DockNetIs[48][6]; // numero Universe artnet(0 à 15) ou Config Port UDP(0 à 5) to listen

char string_docktypnet[8];//affiche du numero artnet ou udp, variable string
char string_docktypmem[8];
char string_docktypaudiovol[8];
char string_docktypaudiopan[8];
char string_docktypaudiopicth[8];
char string_docktypdchan[8];
char string_docktypfx[8];

int ChaserAffectedToDck[48][6];//contenu des chasers dans les docks
int actual_master_lock=0;//master lock utodetcet unique ( un seul M)
int colorpreset_linked_to_dock[8][2];//colorpreset// num fader puis num dock
char string_docktypvideo[8];
char DockName[48][6][25];
unsigned char FaderDockContains[48][6][514];
unsigned char FaderDoDmx[49][514];//la sortie de chaque fader // passé à 49 pour éviter debordement pointeur ECHO SNAP 19/12/14
bool show_who_is_in_FADER_DOCK[514];//pour affichage de qui est dans le dock
bool FaderLocked[48];
unsigned char OldFaderLockProc[48];//pour lancer le midi send out, prend dernier etat fader lors du lock et compare
int locklevel=0;
bool lock_preset[8];//lock preset activé ou pas
int lock_preset_selected_for_record=0; // pour menu confirm
bool FaderLocked_Preset[8][48];
bool LockFader_is_FullLevel_Preset[8][48];
unsigned char StateOfFaderBeforeLock_Preset[8][48];
int master_lock_preset[8];//pour affichage de qui est le master lock
unsigned char StateOfFaderBeforeLock[48];//stockage des niveaux
bool LockFader_is_FullLevel[48];//indicateur du 255 qui fait apparaitre un indice visuel
int  highest_level_comes_from_fader[514];
int DockHasMem[48][6];// linkage des memoires dans les docks
//LFO
bool is_dock_for_lfo_selected[49][6]; // selection nbre de cycle du LFO loop
float time_per_dock[49][6][4];//WAIT IN- IN - WAIT OUT- OUT -
int lfo_mode_is[49];// //0 NO LFO- 1 UP ONCE - 2 DOWN ONCE
bool lfo_cycle_is_on[49];// SAW up down
bool lfo_cycle_steps[49];
char string_time_is_in_the_dock[49][60];
float fraction_lfo_in[49];
float fraction_lfo_out[49];
float faders_in_float[49];
int lfo_speed[49];
int before_lfo_speed[49];
bool lfo_running_is_upward[49];
bool lfo_do_next_step[49][2]; // 0 backward 1 forwar
bool index_lfoing[49]; // pour locker sur un lfo plusieurs masters
int time_delay_in[49];
int time_delay_out[49];
int start_time_for_delays[49];
int actual_time;
//StopPOs
bool StopPosOn[48];
//sab 02/03/2014 ATTENTION IMPACT - COMMENT CONTROLER FONCTION ? unsigned char --> unsigned int
unsigned int LevelStopPos[48];
unsigned int PreviousLevelStopPos[48];//pour banger back

bool ActionnateStopOn[48];//activation du mode stop on
bool do_light_setpos[48];

//courbe dans faders
int FaderCurves[48];
int  before_bang_FaderCurves[48]; //pour goback banger
bool index_ask_curv_to_fader=0;
int curve_asked_for_fader=0;

bool autolaunch[48];//déclenchement des embarqué au montage de potard

bool fader_damper_is_on[48];

////////////////////////////////////////////////////////////////////////////////
///MODE DIRECT CHANNEL POUR LES FADERS
int FaderDirectChan[48][6];
unsigned char beforeloop_for_directch[48];
bool index_direct_chan=0;
bool index_do_record_direct_ch=0;
bool index_fader_is_manipulated[48];//si 1, le niveau du circuit est retranscrit par le fader

bool multiple_direct_chan=0;//affectation rafale des direct chan 0 solo / *12 = 1 /
//mini faders panels
bool index_show_minifaders=0;
bool index_over_minifaders=0;
bool index_click_move_minifaderswindow=0;
int xMinifaders=580;
int yMinifaders=420;
bool minifaders_selected[48];
int position_minifader_selected=0;
char report_minifader_str[64];
char str_tmp_minidock_dock[16];
char str_minifader_feedback[16][64];
bool FaderIsFlash[48];//flash or not
bool FaderIsFlashBefore[48];//flash or not procedure rappel du niveau before
unsigned char LevelFaderBeforeFlash[48];
bool minifaders_preset_selection[8][48];
int mf_preset_selected_is=0;//match selection et oresets
bool minifader_preset_is_empty[8];//check

int before_dock_used_by_fader_is[48];//pour raffraichir icat
bool do_light_minifaders_commands[24];
bool index_record_minifader_preset=0;
bool index_clear_minifader_preset=0;
bool index_record_minifader_lockpreset=0;
int minifader_preset_is=0;
int minifader_lockpreset_is=0;
int over_minifader=0;
/////////////////////////////CHANNELS///////////////////////////////////////////
int scroll_channelspace=0;
int dmx_view=0;//0 pourcentage 1 dmx
unsigned char bufferSaisie[514]; // le 0 n est pas pris, le 512 est en  513
unsigned char bufferBlind[514];
unsigned char bufferFaders[514];
unsigned char bufferSequenciel[514];
unsigned char bufferCopyPaste[514];
unsigned char buffer_affichage_valeurs_sequenciel[514];
unsigned char bufferPourcentStepdefaultlevel[514];//buffer tampon pour simplifier les steps levels en % ou dmx


bool SelectedForCopyPaste[514];
bool Selected_Channel[514];
bool Temp_Selected_Channel[514];//pour selection chainee souris ( comme ds schwz)
int last_ch_selected=0;
int check_channel_level=255;
int previous_ch_selected=0;
bool index_blind=0;
char string_last_over_dock[36];
char string_secondary_feeback[64];
bool index_ch_thruth=0;
int default_step_level=1;
bool index_level_attribue=0;//pour deselection lors d une resaisie nouvelle
///////////////////TRICHRO//////////////////////////////////////////////////////

bool index_affect_color_to_dock=0;
int dock_color_selected=0;
BITMAP *bmp_buffer_trichro;
char string_dock_col_sel[36];
//////////////////////MEMOIRES//////////////////////////////////////////////////
int mem_to_resurrect=0;
int CTRLC_mem_to_copy=0;//pour CTRL C CTRL V avec numeros
bool index_copy_mem_in=0;//ask confirm


//////////////////////TEXT ENTRY////////////////////////////////////////////////
char string_numeric_entry[36];

int numeric_postext=0;
float numeric_entry=0.0;
char numeric[25];
int maxchar_numeric=24;
int idchannel;

//////////////////////UTILITIES///////////////////////////////////////
int xBoxutilities=580;
int yBoxutilities=290;

/////////////////CONFIG//////////////////////////////////////////////////
char string_config[15];
char string_title_panel_config[36];
bool index_save_config=0;
//artnet
bool index_artnet_receiver=0;

bool index_art_polling=0;
char tmp_ip_artnet[17];

//dmx

int window_cfgX=10;
int window_cfgY=25;
int largeurCFGwindow=830;
int hauteurCFGwindow=290;
//config pannel
int select_artnet_to_listen=0;
bool index_do_affect_net_to_dock=0;// affecter ou pas dans le dock le type de net
//POLL
volatile int ticks_poll = 0;
int window_proc_x=300, window_proc_y=150;
//globales
bool index_affect_dmxin=0;
bool index_affect_video_tracking_to_dock=0;
bool index_snap_background=0;
//CONFIGS
bool index_config_dmx=0;
bool index_config_midi=0;
bool index_config_arduino=0;
bool index_setup_gfx=0;
bool index_config_network=0;
bool index_config_general=0;//main general du setup // 1 car ouverture à l allumage
//////////////////PATCH//////////////////////////////////////////////////////////
int xpatch_window=200;
int ypatch_window=100;
int scroller_patch=1;
float  Patch_Scroll_Factor=25.0;
int iddim=0;
bool index_affect_patch=0;
bool index_menu_curve=0;
bool index_reset_curve=0;
bool index_square_curve=0;
bool index_fluo_curve=0;
bool index_preheat_curve=0;
bool Dimmers_selected[514];
int Patch[514];
bool dimmer_type[514]; //0=HTP= 1 LTP
unsigned char MergerArray[514];
char string_monitor_patch[1024];
bool index_patch_affect_is_done=0;
int last_dim_selected=0;
int dimmer_check_level=192;
//Curves splines
bool index_writing_curve=0;
float curve_spline_level=0.0;//report en float
int curve_selected=0;
int the_curve_spline_level[16];
int curve_report[16][256];
int index_curve_spline_level=0;//pixels de l editeur
bool index_enable_curve_editing=0;
int curves[514];//bug ?514 était en 513
int curve_ctrl_pt[16][8][2]; //5 pts de controls (  pour caller 1er et dernier dummy)
int diam_curve_node=10;//diametre de la poignee pour saisie du curve_node
typedef struct curve_node
{
   int x, y;
   fixed tangent;
} curve_node;
#define MAX_curve_nodeS    8
curve_node curve_nodes[MAX_curve_nodeS];
int curve_node_count=0;
fixed curve_curviness;
typedef struct NODE
{
   int x, y;
   fixed tangent;
} NODE;

#define MAX_NODES    49
NODE nodes[MAX_NODES];
int node_count;
fixed curviness;
bool show_control_points=0;
int actual_step_node=0;
int next_step_node=0;
int numero_de_dock_goto_spline=1;

////////////////////////VIDEO //////////////////////////////////////////////////
double image_recording_size;
double image_recorded_size;
int fps_video_rate=30;
int default_fps_video_rate=12;
int recup_val_pix_video=0;
bool ocvfilter_is_on=0;//acces reglages images oCV
int ocv_calcul_mode=0;
char string_ocv_mode[8];
int threshold_level=65;
int erode_level=0;
int div_facteur=1;
char string_threshold_is[24];
char string_erode_is[24];
char string_blur_is[24];
char string_div_is[24];
int flip_image=1;
int threshold_on=1;
int erode_mode=0;
int blur_on=0;
double pixels_changed=0;
double old_pixels_changed=0;
double nbre_pixels_changed=0;
float ratio_pixels_changed=0.0;

int camera_size_settings_is=0;// nouveau système selection de taille image
int camera_size_array[2][2]; // x y size à définir 320x240 640x480
int camera_fps_settings_is=0;// nouveau systeme selection fps en index
bool manipulating_camera=0;//pour éviter de planter lectrue ecriture de données

int camera_modes_and_settings[8][16];//ocv_calcul_mode /levels
float level_visu=1.0;
int index_count_trackers=0;
int frame_video_x, frame_video_y;
int video_size_x=320 , video_size_y=200;
bool camera_is_on=0;
int camera_on_open=0;
int camera_original_fps_is=15;
float display_fps;
//6 tracking docks // 12 espaces de tracking par tracking dock//
int tracking_coordonates[6][12][4];//dock selected / tracker / x y largeur x largeur y
bool tracking_contents[6][12][512];//channel affectation
int buffer_tracker[514];
int tracker_level[6][12];
int tracker_to_edit=0;
//smooth
float tracker_target_val[6][12];
float tracker_val[6][12];
float tracker_decay_constant =1;
float tracker_dt = 1;
int index_decay_tracker=10;
bool edit_tracker=0; //size
bool move_tracker=0; //x y
bool tracker_clearmode=0;
bool view_levels_tracker=1;
int videoX=860, videoY=20;
int default_videoX=860, default_videoY=20;
char string_tracker_edited_dat[48];
//tracking cam
//6 tracking docks // 12 espaces de tracking par tracking dock//
int tracking_dock_selected=0;
bool tracking_spaces_on_off[6][12];//dock selected / tracker

////////////////////VIDEO AVI///////////////////////////////////////////////////
char list_my_video[25][16];//24 videos
char annote_my_video[25][64];//24 videos
int nbre_de_videos=0;

///////////////////CHANNELS////////////////////////////////////////////////////

int XChannels=-20, YChannels=70;
int ChScrollX=580, ChScrollY=50; //scroller ascenceur
float Ch_Scroll_Factor=12.0;
int last_scroll_mouse_for_chan=0;
bool index_moving_channel_scroller=0;
char string_last_ch[36];

///////////////DMX ENTTEC PRO//////////////////////////////////////////////////

int enttecpro_detectX=485, enttecpro_detectY=110;
bool index_list_pro_devices=0;
char DevFoundedEnttecPro[64];
int number_of_enttec_pro_devices=0;
bool index_init_EnttecPROIN_ok=0;
int istheresomeone_in_enttecpro=0;//VCOM OUT
int vcom_inposition_is=0;//VCOM IN

///////////////////////NUMERIC PAD//////////////////////////////////////////////
int xnum_window=900,ynum_window=60;
int default_xnum_window=900,default_ynum_window=60;//xy de la window par defaut
int rayon_wheel_level=20;
float angle_correction_wheel= 1.0; // faire un quart de toour vers la droite
float pad_vx;
float pad_vy;
float angle_snap_pad;
float position_curseur_pad_x;
float position_curseur_pad_y;
int wheellevel_absolutemode=0;
int previous_level_wheel=1;
int absolute_level_wheel=0;//icat
int previous_absolute_level_wheel=0;//icat

////////////////////////TIME CHRONO///////////////////////////////////////////

float position_curseur_time_x;//=1242,
float position_curseur_time_y;//=228;//pour intialisation au demarage de l api
float time_angle;
float angle_timesnap;
float   vtimex,vtimey;
int actual_tickers_chrono=0;
char visu_chrono_str[64];
char visu_big_chrono[36];

char string_tap_tempo_average[36];
char string_actual_tap_tempo[36];
bool index_recording_tap_tempo=0;
bool do_light_tap_tempo=0;//index affcihage frappe tempo
bool do_light_send_tap=0;
int start_tempo_ticks=0;
float tap_tempo_average=0.0;
int nbr_steps_tempo=1;//doit etre 1 et pas 0 pour pas provoquer de NIL
int max_temp_tempo=12;
int ticks_tap_tempo[16];
int tempo_interm=0;//pur addition des ticks

bool index_show_chrono=1;//pour affichage chrono discret
////////////////////////THRICHRO////////////////////////////////////////////////

#define ACCURACY_DOUBLE  1.e-06
int xtrichro_window=1128,ytrichro_window=350;
int default_xtrichro_window=1128,default_ytrichro_window=350;//xy de la window par defaut
//les 8 colors docks et leurs données
bool dock_color_type[8];//0 trichro 1 mode quadri
int x_y_picker_par_colordock[8][2];//stockage des coordonnes du picker par coordonnées
float angle_hue_par_colordock[8];//picker par coordonnées angles
int picker_trichro[8][4];//stockage des niveaux RVB YELLOW
unsigned char dock_color_buffer_C[8][514];//resultat dans buffers separés
bool index_quadri=0; //0 mode trichro 1 mode quadri jaune
bool dock_color_channels[8][4][514];//trichro sur curcuits
float position_curseur_hue_x;//=1242,
float position_curseur_hue_y;//=228;//pour intialisation au demarage de l api
float angle;
float angle_snap;
float   vx,vy;
float   vxh =0;// cos(angle* PI/180)*(rayon-15); //hue triangle position
float   vyh =100;// sin(angle* PI/180)*(rayon-15);
float vxd=-90;//cos((angle+120)* PI/180)*(rayon-15);//Dark position
float   vyd=-50;// sin((angle+120)* PI/180)*(rayon-15);
float  vxw=90;// cos((angle+240)* PI/180)*(rayon-15);//white position
float   vyw=-50;// sin((angle+240)* PI/180)*(rayon-15);
//le hue general
int cref=0;
int r_pick=255,b_pick=0,v_pick=0;
//le choix dans le triangle
float picker_x, picker_y, last_picker_x,last_picker_y;
int my_red, my_blue, my_green, my_yellow; //valeurs servant à l asservissement des circuits
int colorpicker;//cref du triangle
//Variables roue de  maison
double xcl, ycl;
int rcl, gcl, bcl;
float hcl, ccl;

/////////////////////functions call//////////////////////////////////////////
char string_name_button[15];
char string_raccourci[5];
//////////////////////SAVE LOAD/////////////////////////////////////////////////
bool index_save_mode_export_or_binary=0;//met la fenetre save en mode export=1 ou binary classic=0
int idf=0;//curseur position retour info save load
bool specify_who_to_save_load[80];//72 d utiliser max
bool preset_specify_who_to_save_load[80][4];
bool index_save_global_is=1; // 1 global 0 detailled
//coordonnees fenetre save load
int report_SL_X=30 ;
int report_SL_Y=40 ;
int default_report_SL_X=30 ;
int default_report_SL_Y=30 ;
bool there_is_an_error_on_save_load=0;
bool index_show_save_load_report=0;
bool b_report_error[256];
char string_save_load_report[256][64];//256 slot de report de 64 char
int position_view_line=0; //pour defilement affichage
char string_typeexport_view[24];
bool index_is_saving=0;//pour eviter de planter les pointeurs en faisant deux saves simulatnnés
int timer_save_tmp=0;
int temps_sauvegarde_tmp=15*60;//secondes
bool index_please_do_not_save=0;
/////////////SAVE MENU//////////////////////
//EXPORTS IMPORTS
int index_export_choice=0;
char list_import_files[128][72];
int line_import=0;
int importfile_selected=0;//num de ligne selectionné
char importfile_name[72];
bool enable_export=0;// pour les choix schwz / pdf / txt / ascii
bool enable_import=0;
////BINARIES
char list_save_files[128][72];
int line_save=0;
int savefile_selected=0;//num de ligne selectionné
char savefile_name[72];

//////////////////////MIDI/:////////////////////////////////////////////////////
bool index_midi_mute=0;
bool index_auto_mute_cuelist_speed=0;
int index_midi_auto_desaffect=0;
short		myRefNum; // application reference number
MidiFilterPtr	myFilter; // events filter
//MidiName AppliName = "white cat";
bool index_midi_clock_on=0;

char TblLibEv[256][20];
char my_midi_string[64];
char midi_historic[256][64];//affichage
int midi_historic_data[256][4];//stockage
int position_midi_historic=0;

char my_midi_original_string[64];
char my_midi_out_string[128];
char tableau_peripheriques_in[32][64];//ordonnees nom
bool tableau_peripheriques_indexs_in[16];
char tableau_peripheriques_out[32][64];//ordonnees nom
bool tableau_peripheriques_indexs_out[16];
char string_nbre_de_devices[32];
int compt_midi_in=0;
int compt_midi_out=0;
int compt_first_device_out=0;
int compt_first_device_inout=0;
int nbre_devices_in=0;
int nbre_devices_out=0;
int do_connect_out[32];
bool midi_out_is_connected[32];
int do_connect_in[16];
bool midi_in_is_connected[32];
bool index_midi_global_thruth=0;
char typ[50];
int midi_keyboard_wait=100;
int midi_wait=150;
int duree_note=10;
char string_last_midi_id[128];
char string_shortview_midi[24];//affichage over souris
//char string_fader_contains_midi[128];
//char string_dock_contains_midi[128];
int isport=0 ; int ischan=0 ; int ispitch=0; int isvel=0;
int istyp=0;
byte isrefnum=0;
int miditable[3][3072];
int   over_fader=0, over_dock=0; // survol d un fader ou d un dock pour visualisation des circuits et de leur niveau
//[3] : 0 typ 1 Chan 2 Pitch
//[512]: 0-48: faders / 49-96: Dock - 97-145: Dock + / 146- 194
int midi_levels[3072];
bool midi_send_out[3072];//atribué ou pas
bool index_send_midi_out[3072];//index booleen pour lancer l ordre depuis la boucle
bool index_global_midi_send_on_faders=0;//enclenche l envoi global ou pas des midi out sur tous les faders donnee non sauvegardée, car c est un impulse
bool do_light_midi_send_on_faders=0;
int midi_page=0;
//bool do_affectation_on_midi_affect_itself=0;
int Midi_Faders_Affectation_Type=0;
//0 ne rien faire
//1 faders 1 à 1
//2 faders serie 8x
int Midi_Faders_Affectation_Mode=0;
//0=affectation normale
//1=reset
//2=utiliser entree clavier ou souris (pas de detection)
bool toggle_numerical_midi_way=0;
//0 numerique sur pitch
//1 numerique sur midi ch ( 0->8)
int fakemidichan=0; //les entrees d affectations en manuel
int fakemidipitch=1;
int fakemiditype=4;

bool index_midi_affectation_autoclose=1; //when at 1, midi affectation once done is disable, to avoid errors
/////////////////
char thetypinfo[12];//affciahge dans midi conf du type en lettres
int type_of_midi_button=0; //0=fader 1 = dock button   2= lock button 3= midi out on off button  4=speed lfo function
// 5= boutton normal
bool cheat_key_off=0;//key on vel 0 = key off
bool cheat_key_off_to_key_on=1;//key off vel 127 ou autre= key on vel 0, filtre general 12/05/15 christoph mf twister sequencer

int bpm_personnal[16];
int relativ_encoder_midi_clock_value=10;//for cc increment in live of BPM
bool clocklevel_absolutemode=0;
int clock_level_is=0;
float clock_vx;
float clock_vy;
float angle_snap_clock;
float position_curseur_clock_x;
float position_curseur_clock_y;
/////////////////////////////////////////////////////////////////////////////////
bool is_raccrochage_midi_remote[3072];
int val_raccrochage_midi[3072];//valeur recue


bool refresh_midi_chasers=0;

bool index_midi_auto_demute=0;//index demute quand curseur arrivé
bool index_midi_mute_on_lfo=0;// au déclenchement d'un LFO, mute solo l'entrée en question
////////////////////////TIME////////////////////////////////////////////////////
bool index_time=0;//affichage fenetre time
int xtime_window=100;
int ytime_window=100;
bool index_play_chrono=0;
bool index_type_of_time_to_affect[4];//0=DIN 1=IN 2=DOUT 3=OUT
int time_centiemes=0;
int time_secondes=0;
int time_minutes=0;
bool index_affect_time=0;
bool show_im_recording_a_time=0;
int time_wheel_datatype_is=1;// 0=minutes 1=secondes  2=secondes
float angle_timesnap_min=0.0;
float angle_timesnap_sec=0.0;
float angle_timesnap_dix=0.0;
char string_conversion_timeis[12];//pour affichage des temps ans le sequenciel et faders
//affichages des temps sequenciel
char string_time_memonstage[4][52];
//cross à faire = cross_in ventilation_temps_vers_char
char string_time_mem8after[35][4][52];
//////////////////////SEQUENTIEL////////////////////////////////////////////////
bool index_window_sequentiel=0;
int xseq_window=50;
int yseq_window=10;
int nbre_memoires_visualisables_en_preset=8;
int hauteur_globale_sequenciel=180+(35*(nbre_memoires_visualisables_en_preset+1))+35;
bool MemoiresExistantes[10000];
unsigned char Memoires[10000][514];
int position_onstage=0;
int position_preset=0;
int mem_before_one=0;
int other_mem_in_loop=0;
char descriptif_memoires[10000][25];
char annotation_memoires[10000][25];
bool MemoiresExclues[10000];
char string_ratio_x1x2[4];
char str_crossfade_speed_is[6];
bool index_text_auto_close=0;
float Times_Memoires[10000][4];//0=DIN 1=IN 2=DOUT 3=OUT
bool Links_Memoires[10000];
bool index_link_is_on=0;
int  index_blink_change_memories=0;// si on demande d afficher les changements entre sequenciel modifie ( sc-preset) et les mémoires
float default_time=3.0;
int niveauX1=255;
int niveauX2=0;
bool call_preset=0;// pour call on stage ou en preset de memoire
bool call_stage=0;
char string_mem_before_one[6];
char string_mem_onstage[6];
char string_mem_preset[6];
char string_next_mem[6];
//cross manuel
bool index_x1_x2_together=1;
int ratio_X1X2_together=0;
int remapX1[255];
int remapX2[255];
//cross fade
bool index_go=0;
bool index_pause=0;
bool index_go_back=0;
int crossfade_start_time=0;
int crossfade_elapsed_time=0;
int crossfade_done_time=0;
int crossfade_speed=64;
bool auto_reset_crossfade_speed_on_link=0;
float floatX1=0.0;
float floatX2=0.0;
float fraction_X2_in=0.0;
float fraction_X1_out=0.0;
int crossfade_time_delay_in=0;
int crossfade_time_delay_out=0;
float fraction_goback_X2_in=0.0;
float fraction_goback_X1_out=0.0;
float alpha_blinker=0.0;
float alpha_smooth_blinker=0.0;
float default_time_back=3.0;
int ratio_cross_manuel[10000];
bool index_get_back_faders_need_to_be_done=0;//pour crossfade manuel en midi
char cross_to_come[52];
char cross_din[12];
char cross_in[12];
char cross_dout[12];
char cross_out[12];
//time left affichage sur crossfade
float report_dIn=0.0;
float report_In=0.0;
float report_dOut=0.0;
float report_Out=0.0;
float time_left=0.0;
float totalTimeCrossfade=0.0;
char string_time_left_is[52];
char string_total_time_is[52];
char string_last_copy_mem[25];
////////////////////////////////////////////////////////////////////////////////
//MENU SAVE
bool index_menu_save=0;
int xsave_window=200;
int ysave_window=200;
///////////////////Confirm box//////////////////////////////////////////////////
int XConfirm=100;
int YConfirm=100;
bool index_ask_confirm=0;
bool previous_index_ask_confirm=0;
char string_confirmation[128];

bool index_do_delete_mem=0;
bool index_do_create_mem=0;
bool index_do_create_mem_plus_faders=0;//shift f3
bool index_do_overecord_mem_plus_faders=0;//ctrl f3
bool index_do_link_memonstage=0;
bool index_do_link_memonpreset=0;
bool index_do_link_membefore=0;
bool index_do_link_memother=0;
bool index_do_record_on_faders=0;
bool index_do_modify_on_faders=0;
bool index_do_report_on_faders=0;
bool  index_do_affect_color_on_faders=0;
bool index_do_dmx_to_dock=0;
bool index_do_artnet_to_dock=0;
bool index_do_video_to_dock=0;
int  fader_selected_for_record=0;
int dock_selected_for_record=0;
bool index_do_affect_color_trichro=0;
int couleur_to_affect=0;
bool index_do_affect_roi=0;
bool index_do_clear_my_roi=0;
bool index_do_clear_my_video_preset=0;
int dock_roi_selected=0;
int tracking_dock_to_clean=0;
bool index_do_overrecord_mem=0;
bool index_do_clear_dock=0;
bool index_do_clear_on_faders=0;
bool index_do_reload_mem=0;
bool index_do_resurrect_mem=0;
bool index_do_jump_while_cross=0;
bool index_do_export=0;
bool index_do_import=0;
bool index_do_saveshow=0;
bool index_do_loadshow=0;
bool index_do_resetshow=0;
bool index_do_freeze=0;

bool index_do_clear_patch=0;
bool index_do_default_patch=0;
bool index_do_quit_with_save=0;
bool index_do_quit_without_save=0;
bool index_do_ask_call_audio_folder=0;
bool  index_do_clear_lock_preset=0;
bool index_do_banger_memonstage=0;
bool index_do_banger_memonpreset=0;
bool index_do_banger_membeforeone=0;
bool index_do_banger_memother=0; // les 8 autres memoires
/////////////////////////////////FENTRE LISTE PROJOS//////////////////////////
bool index_list_projecteurs=1;
bool index_edit_listproj=0;
char descriptif_projecteurs[514][25];
int Xlistproj=300;
int Ylistproj=100;
int line_list_is=0;
char listnum[12];
/////////////////ARTNET///////////////////////////////////////////////////////
const short MaxNumPorts  = 1;//4
const short MaxExNumPorts = 32;
const short ShortNameLength  = 18;
const short LongNameLength  = 64;
const short NodeReportLength =64;
const short PortNameLength= 32;
const short MaxDataLength = 512 - 1 ; // 0..511

char ArtPollBuffer[14];
char ArtPollReplyBuffer[240];//ok pour la largeur
char ReceivedArtPollBuffer[14];
char ReceivedArtPollReplyBuffer[240];
char ArtShortName [ShortNameLength]= {"white_cat"};
char ArtLongName[LongNameLength]= {"a PC Lighting Application "};
char ArtNodeReport[NodeReportLength]= {"Is everything ok ?"};
int index_broadcast=0;

int count_artopoll_received=0;
///RECEPTION ART-NET
bool receiving_bytes=0;//pour savoir si je recois du monde sur le socket
bool ArtDetected=0;
//analyse artnet indexs
bool is_artnet=0;
bool is_opcode_is_dmx=0;
bool is_opcode_is_polling=0;
int is_artnet_version_i1, is_artnet_version_i2;
int seq_artnet=0; int artnet_physical=0;
int incoming_universe;// recuperer num de universe
char artnet_message[530];
char artpollreply_message[250];
unsigned char ArtNet_16xUniverse_Receiving[514][17];
bool index_serveur_artnet_on=0;
bool index_listen_for_artnet=1;
//bool index_allow_to_write_universe[17];
bool index_show_artpoll_reply_content=0;
int artpoll_replyX= 485, artpoll_replyY=110;
char PollReplyIs[16][128];//affichage
char nodefirmware_versinfo[12];
char shortname_device[18];
char subnetis[12];//modif aout 2016 était 6, donc overflow par sprintf dans network artnet 3
char paste_reply[16][100];
char ip_artnet[17];
char string_ip[30];
char my_ip_is[4];//report pour artnet poll reply

//client
SOCKET sockartnet;
SOCKADDR_IN sinS;
int sinsize;
//serveur
SOCKET sock;
SOCKADDR_IN sinServ;
int sinsizeServ;
/////////////////////////
struct hostent * phe;
char FAR hostnamebuffer[64] ;
char broadcast='1';
int nbrbytessended=0;
int bytesreceived=0;
//int defaultport_artnet=0x1936;
int serveurport_artnet=6454;
int clientport_artnet=6454;

char tmp_udp_chain[600];
short HeaderLength = 17;
short DataLength=512;
int Dim (HeaderLength + DataLength) ;//largeur de l envoi
int Univers=0;
bool index_do_light_diode_artnet=0;

bool artnet_serveur_is_initialized=0;
//////////////////RESEAUX DETECTION////////////////////////////////////////////
char IP_detected_dmxOUT[8][24];

char IP_artnet_IN[24];
char IP_artnet_OUT[24];
char IP_fantastick[24];

int network_OUT_is_selected=0;//amene a disparaitre

bool index_re_init_client_artnet=0;
bool index_re_init_serveur_artnet=0;

bool index_re_init_clientserveur_icat=0;

bool index_ask_reinit_FS_client=0;
///////////////////////COULEURS ET POLICES//////////////////////////////////////
Rgba CouleurFond;
Rgba CouleurLigne;
Rgba CouleurFader;
Rgba CouleurPatch;
Rgba CouleurSurvol;
Rgba CouleurLevel;
Rgba CouleurSelection;
Rgba CouleurNiveau;
Rgba CouleurBlind;
Rgba CouleurLock;
Rgba CouleurConfig;
Rgba CouleurBleuProcedure;
Rgba CouleurYellow(0.6,0.6,0.0);
Rgba CouleurYellowFgroup(1.0,0.7,0.0);
Rgba CouleurGreen(0.0,0.6,0.0);
Rgba CouleurRed(0.6,0.0,0.0);
Rgba CouleurRougePur(1.0,0.0,0.0);
Rgba CouleurFondDefaut(0.0,0.0,0.0);
Rgba CouleurLigneDefaut(1.0,1.0,1.0);
Rgba CouleurFaderDefaut(1.0,0.4,0.0);
Rgba CouleurPatchDefaut(1.0,0.2,0.0);
Rgba CouleurSurvolDefaut(0.8,0.0,0.0);
Rgba CouleurLevelDefaut(0.5,0.7,0.6);
Rgba CouleurSelectionDefaut(0.5,0.0,0.7);
Rgba CouleurNiveauDefaut(0.1,0.0,0.7);
Rgba CouleurBlindDefaut(1.0,0.0,0.0);
Rgba CouleurLockDefaut(0.0,0.4,0.2);
Rgba CouleurConfigDefaut(0.1,0.1,0.3);
Rgba CouleurBleuProcedureDefaut(0.0,0.2,0.5);

Rgba CouleurBlanc(1.0,1.0,1.0);
Rgba CouleurGrisTresClair(0.8,0.8,0.8);
Rgba CouleurGrisClair(0.6,0.6,0.6);
Rgba CouleurGrisMoyen(0.4,0.4,0.4);
Rgba CouleurGrisAnthracite(0.2,0.2,0.2);
Rgba CouleurNoir(0.0,0.0,0.0);

Rgba CouleurBleu10(0.1,0.1,1.0);
Rgba CouleurBleu8(0.1,0.1,0.8);
Rgba CouleurBleu6(0.1,0.1,0.6);
Rgba CouleurBleu4(0.1,0.1,0.4);
Rgba CouleurBleu2(0.1,0.1,0.2);
Rgba CouleurBleu1(0.0,0.0,0.1);

Rgba Discrete1(0.023529,0.023529,0.082353);
Rgba Discrete2(0.2,0.2,0.4);
Rgba Discrete3(0.6,0.6,0.7);
Rgba Discrete4(0.6,0.8,0.7);
Rgba Discrete5(0.7,0.3,0.4);
Rgba Discrete6(0.9,0.0,0.0);
Rgba Discrete7(0.1,0.8,0.0);
Rgba Discrete8(0.2,0.4,0.8);
Rgba Discrete9(0.2,0.2,0.3);
Rgba Discrete10(0.8,0.7,0.7);
Rgba Discrete11(0.9,0.0,0.8);
Rgba Discrete12(0.2,0.3,0.2);

Rgba Matrix1(0.0,0.1,0.0);
Rgba Matrix2(0.0,1.0,0.0);
Rgba Matrix3(0.0,0.8,0.0);
Rgba Matrix4(0.0,0.2,0.0);
Rgba Matrix5(0.0,0.9,0.0);
Rgba Matrix6(0.0,1.0,0.0);
Rgba Matrix7(0.0,0.9,0.0);
Rgba Matrix8(0.0,1.0,0.0);
Rgba Matrix9(0.0,0.2,0.0);
Rgba Matrix10(0.0,0.3,0.0);
Rgba Matrix11(0.6,0.9,0.0);
Rgba Matrix12(0.2,0.7,0.2);

Rgba CouleurUserLoop;
Rgba CouleurUser1;
Rgba CouleurUser2;
Rgba CouleurUser3;
Rgba CouleurUser4;
Rgba CouleurUser5;
Rgba CouleurUser6;
Rgba CouleurUser7;
Rgba CouleurUser8;
Rgba CouleurUser9;
Rgba CouleurUser10;
Rgba CouleurUser11;
Rgba CouleurUser12;


Rgba CouleurPreviewHue;
Rgba CouleurPreviewChroma;

TextRenderer axaxax12;
TextRenderer doom;
TextRenderer doomblanc;
TextRenderer petitdoomblanc;
TextRenderer minidoomblanc;
TextRenderer doomrouge;
TextRenderer neuro;
TextRenderer neuromoyen;
TextRenderer petitchiffre;
TextRenderer circuitlevel;
TextRenderer circuitfaderlevel;
TextRenderer circuitblindlevel;
TextRenderer petitpetitchiffre;
TextRenderer petitpetitchiffregris;
TextRenderer petitpetitchiffrerouge;
TextRenderer petitchiffrerouge;
TextRenderer petitchiffrenoir;
TextRenderer petitdoomInspekt;
TextRenderer petitdoomrouge;
TextRenderer neuroTitle;
TextRenderer minichiffre;
TextRenderer minichiffregris;
TextRenderer minichiffrerouge;
TextRenderer minichiffrenoir;
//IMPORT SCHWZ////////////////////////////////////////////////////////////////////////
char f_cues[25]={"cues.dat"};
char f_boolcues[25]={"bool_cues.dat"};
char f_autogo[25]={"autogo.dat"};
char f_times[25]={"times.dat"};
char f_patch[25]={"patch.dat"};
char f_descriptif[25]={"descriptif.dat"};
char f_shadow_sub[30]={"shadows_subs.dat"};
int SchwzMemoires[121][5011];
bool Schwzautogo[5011];
float SchwzMemTime[5011][4];
bool SchwzMemoiresExistantes[5011];
char Schwzdescriptif_mem[5011][13];
int SchwzPatch[513];
int Schwzshadow_sub[8][5][121];

//sab 02/03/2014 unsigned
unsigned int SchwzMemoires_size= 121*5011;
unsigned int SchwzMemTime_size= 5011*4;
unsigned int SchwzPatch_size=513*1;
unsigned int SchwzMemoiresExistantes_size=5011*1;
unsigned int Schwzautogo_size=5011*1;
unsigned int Schwzdescriptif_size=5011*13;
unsigned int Schwzsize_of_shadow_sub=40*121;

bool isSchwz=0, isASCII=0, isPdf=0, isAlq=0;


bool specify_who_to_save_PDF[36];

///////////////////FREEZE//////////////////////////////////////////////////////////
bool freeze_array[514];
unsigned char freeze_state[514];
///////////////////////////FADERS SNAPSHOTS GENERAL//////////////////////////////////
unsigned char SnapFader[49];
bool SnapFaderLocked[49];
bool Snapis_dock_for_lfo_selected[49][6];
int Snaplfo_mode_is[49];// //0 NO LFO- 1 UP ONCE - 2 DOWN ONCE
bool Snaplfo_cycle_is_on[49];// SAW up down
bool Snaplfo_cycle_steps[49];
bool Snaplfo_do_next_step[49][2]; // 0 backward 1 forward
int Snaplfo_speed[49];
bool stockage_all_at_zero_state[6];//stockage de l action menée

///////////////////////////////////BANGER///////////////////////////////////////
int X_banger=100;
int Y_banger=100;
int size_X_Banger=610;
int size_Y_Banger=300;
bool index_show_banger_window=0;
int index_over_banger_window=0;
bool index_banger_is_on=0;//on off du mode
int index_banger_selected=0;
bool index_enable_edit_banger=0;
char string_event[72];//debug debordement de tableau 18/12/14 christoph ruiserge
int Banger_Memoire[10000];//le banger affecté à une mémoire
char bangers_name[128][25];//128 bangers
int bangers_type[128][6];//128 bangers // 6 events par banger
int bangers_action[128][6];//num action demandée
int bangers_params[128][6][2];//0 param1 / 1 param2
float bangers_delay[128][6];//delays
int start_time_for_banger[128];//debut de start time
float end_time_for_banger[128];
bool event_sended[128][6];// une fois que l evenement est lancé est mis en 1
bool bang_is_sended[128];//le bang est exécuté si = 0, si déjà exécuté, donc non actif =1

//0.8.5.9 ticker to loop a banger
bool do_loop_banger[128];
float time_loop_banger[128];
volatile int ticker_loop_banger[128];//to store ticks and enclench timers on loop


char keyname[256][16];//nom des touches


bool  bang_in_mem_is_sended=0; //pour les envois dans les memoires, un seul index
int remember_state_of_banged_fader[49][24];
int memoire_asked_in_bang=0;
char string_alarm[128][25];//une alarm par banger
char string_THE_alarm[25];//Etait 30 . 27/10/2010 Lanion
bool index_show_alarm=0;
bool index_over_alarm=0;
int XAlarm=300;
int YAlarm=200;
bool index_click_move_alarm=0;
int index_alarm_from_banger_num=0;
///automations goback variable
int previous_preset_color=0;
int previous_preset_video=0;
int affect_banger_number=0;//var globale d affetation aux memoires
bool index_crossfading=0;
//affcihage depuis midi
bool do_light_bang_it=0;
bool do_light_bang_solo[6];

//visu banger et action depuis main panel
int xVisuBanger=1050;
int yVisuBanger=40;
float default_time_of_the_bang=1.0;//secondes
int last_banger_sended_manually=0;
int bang_the_chan_is=0;//temporaire pour set_channel dans banger
int bang_val_the_chan_is=0;//val à attribuer temp banger set chan


bool editing_banger_family=0;
bool editing_banger_action=0;


bool index_ask_copy_banger=0;
bool index_copy_banger=0;
int index_banger_to_copy_in=-999;

bool index_ask_clear_banger=0;
///////////GRAND MASTER////////////////////////////////////////////////////////
int niveauGMaster=255;
int previous_niveauGMaster=0;
char string_niveauGMaster[4];
bool index_allow_grand_master=1;
//DMX///////////////////////////////////////////////////////////////////////

bool index_allow_sunlite_dmxIN=0;//pour réception ou pas de IN
bool index_is_siudi_8C=0;//pour envoi on change ou pas
char string_sunlite_is[32];
bool do_send_dmx_on_change=0;//pour envoi data sur nterfaces dmx si changement de data
bool do_send_dmx_on_change_siudi=0;//pour 5 et 6c

bool index_patch_overide=0;
bool patch_overide[513];//check gradas
bool allow_artnet_in=0;
//////////////////////////////////////////////////////////////////////////////////

////SOUND AUDIERE//////////////////////////////////////////////////////////////////
AudioDevicePtr device;

OutputStreamPtr player1;
OutputStreamPtr player2;
OutputStreamPtr player3;
OutputStreamPtr player4;

bool starting_wcat=0;//démarrage

char audio_device_name[256];
char list_audio_device[16][256];
bool index_show_audio_window=0;
int index_nbre_players_visibles=2;
bool index_over_audio=0;
bool index_click_move_audio_window=0;
int XAudio=20;
int YAudio=20;
char list_audio_files[128][72];//128 audio files possibles
int line_audio=0;
int audiofile_selected=0;//pour affectation a un lecteur
char audiofile_name[72];
char rep_audio[256];
char audio_folder[25]={"demo"};
char temp_audio_folder[25];
char sound_files[4][72];
char soundfile_temp_loader[256+72];
int  index_preloaded_sounds=1;//pas chargés
int length_of_file_in_player[4];
int position_of_file_in_player[4];
int player_loop_out_position[4];
int player_seek_position[4];

//christoph 22/04/14 debugging midi next prev function by outputting it inside the 1/10th second loop
bool audio_do_load_midi_prev_file[4];
bool audio_do_load_midi_next_file[4];

int audiofile_cue_in_out_pos[128][2]; // les 128 files du repertoire

int audio_number_total_in_folder=0; // nbre de fichiers audios

bool player_ignited[4];
bool player_is_playing[4];
bool player_is_onloopCue[4];//cue
bool player_is_onloop[4];//0 à Length du media

int player_pitch[4]; //position de 0 à 12
float show_pitch_value[4];
int player_pan[4];
float show_pan_value[4];

int player_niveauson[4];
float show_player_niveauson[4];

int sample_rate[4];
int sample_nbr_ch[4];
bool index_edit_audio=0;
//int hauteur_lecteur=140; enlevé mis en direct dans le code
int audio_rate[4];//frame rate une fois eu le getformat
bool index_loading_a_sound_file=0; //pour boucle rafraichissement 1/10eme des infos
//envoi affichage si commande midi
bool midi_show_flash_seektouch[4];
bool midi_show_flash_backwardtouch[4];
bool midi_show_flash_forwardtouch[4];
bool midi_show_flash_cueIntouch[4];
bool midi_show_flash_cueOuttouch[4];
bool midi_show_flash_cueSeektouch[4];
//procedure back pour banger avec audio
char audiofile_name_was[4][72];
int audio_position_was[4];
int audio_volume_was[4];
int audio_pan_was[4];
int audio_pitch_was[4];
int  audio_cue_in_was[4];
int  audio_cue_out_was[4];
bool player_was_playing[4];
bool player_was_onloopCue[4];//cue
bool player_was_onloop[4];

bool index_affect_audio_to_dock=0;//on off du mode
int player_to_affect_to_dock=999;
int audio_type_for_dock_affectation_is=999; // 0 volume 1 pan 2 pitch
bool index_do_audio_to_dock=0;
int DockHasAudioVolume[48][6];
int DockHasAudioPan[48][6];
int DockHasAudioPitch[48][6];
int Player_is_piloted_by_fader[4][4];//pour aller retour entre faders et fader audio


char time_is_for_fileCueIn[4][64];
char time_is_for_fileCueOut[4][64];
char time_is_for_filePos[4][64];
char time_is_for_fileTotal[4][64];
char string_niveauson[4][16];
char string_pitch[4][12];//affichage boucle lecteurs
char string_pan[4][12]; //affichage boucle lecteurs
char string_fader_stop_pos[48][4];
bool audio_autoload[4];//faire une liste défilant
bool audio_autopause[4];//
int player_has_file_coming_from_pos[4];//position 1 à 127
int player_position_on_save[4];//pour stockae de position_of_file_in_player[i]=player_position_on_save[i];
////////////////CONFIG////////////////////////////////////////
bool index_show_config_window=0;
int config_page_is=0;
/////////////FOCUS WINDOW////////////////////////////////////
int window_focus_id=0;//900+id fenetre
int previous_window_focus_id=0;//pour le confirm

int pos_focus_window=0;

bool im_moving_a_window=0;//index poru lros de déplacement
int last_window_founded=0;


//////////////WIZARD /////////////////////////
int Xwizard=100;
int Ywizard=100;
bool index_show_wizard_window=0;
bool index_over_wizard_window=0;
bool index_click_move_wizardwindow=0;
bool index_wizard_ch_mode=1;

//////////////WIZARD CH/////////////////////////
int wizard_action=0; // 0 Set at level / 1 Add / 2 Reduce / 3 exchange
bool wizard_amplitude_is_global=1;
int wizard_level_is=5;
int wizard_from_mem=0;
int wizard_to_mem=0;
int number_inchannels=0;
int number_outchannels=0;
bool index_do_wizard_ch=0;
bool wizard_buffer_in[514];
char tmp_wizbuffer[2160];//buffer temporariare ou tout recevoir
char show_buff_wizIN[37][73];
int position_ligne_wizard_in=0;
//exchange:
bool wizard_buffer_out[514];
char show_buff_wizOUT[37][73];
int position_ligne_wizard_out=0;

////////////WIZARD MEM//////////////////////////
int wizard_action_mem=0;
int position_ligne_wizard_mem=0;//visualisation buffer memoires inspeketes dans wizard mem
bool index_do_wizard_mem=0;
int nbre_de_mems_manipulees=0;
int mode_rebuild=0; //0 digit 1 unit 2 dizaines
int variable_wizard_mem=0;
bool Wiz_MemoiresExistantes[10000];
unsigned char Wiz_Memoires[10000][514];
float Wiz_Times_Memoires[10000][4];
bool Wiz_Links_Memoires[10000];
int Wiz_Banger_Memoire[10000];
char Wiz_descriptif_memoires[10000][25];
char Wiz_annotation_memoires[10000][25];
bool MemoiresDetruites[10000];
bool index_wizard_do_reload_from_disk=0;

/////////////keyboard affectation//////////////////////////////////////////////
int scan_ascii_is=0;
int scan_allegro_key_is=0;
char string_clavier_is[72];
char list_keyname[128][16];//nom des fonction
char string_key_id[16];
int mapping_temporaire[128];//la table de reroutage
int nbre_key_persos=5;
////////////MIDI CHANGE SIGNAL////////////////////////////////////////////////
int line_midi_changesignal=0;
char string_midichan[16];
int change_vel_midichan_selected=0;
int midi_change_vel_type[16][128];//type de transformation de signal:0=nothing
// 1=inverse // 2=Toggle
int tempvel=0;//val de stockage de isvel
bool midi_recognize_on_off[16][128];//CH PITCH VAL
////////////sauvegardes automatiques//////////////////////////////////////////
int automatic_time_for_save=10;
int do_save_at_time=10000;
int last_time_for_save_was=0;

/////////////MULTI CORE PROCESS/////////////////
bool index_allow_multicore=0;
int core_to_assign=0;


//////ARDUINO/////////////////////////////////
int open_arduino_on_open=0;
char string_Arduino_status[128];
int arduino_max_devices=1;


int nBytesReadArduino0=0;
int nBytesSendtoArduino=0;

int arduino_com0=4;
int arduino_baud_rate0=9600;//9600 ok sur 6 ana 13 io //11400 ùega 54 IO
bool arduino_device_0_is_ignited=0;


#define digital_limit 127
#define analog_limit 63
#define pwm_limit 35


unsigned char input_str_arduino[digital_limit];//chaine input data from arduino (analog and digital)



int digital_data_from_arduino[digital_limit];//tableau des datas gardé tres large au cas ou grande extension
int previous_digital_data_from_arduino[digital_limit];
int arduino_max_digital=13;
int analog_data_from_arduino[analog_limit];//tableau des datas gardé tres large au cas ou grande extension
int previous_analog_data_from_arduino[analog_limit];
bool ventilate_analog_data[analog_limit];//pour muter demuter les entrées arduino
int arduino_max_analog=5;
bool digital_data_is_switch[digital_limit];//pour comportements switch
bool snap_dig_for_switch[digital_limit];

bool kalman_is_on[analog_limit];
double kalman_params[3][analog_limit];
int Kalman_selected=0;

int digital_data_to_arduino[digital_limit];
int previous_digital_data_to_arduino[digital_limit];

int arduino_digital_type[digital_limit];//0= desaffecté 1= input 2= output 3= PWM
int arduino_digital_function_input[digital_limit][2];//Action // Val
int arduino_analog_function_input[analog_limit];//0-rien 1-fader 2 Seq 3 trichro 4 video 5 master
int arduino_analog_attribution_input[analog_limit];//Val 1-48 ou sequenciel 123
int position_line_io=0;
int position_line_ana=0;
bool arduino_simulating_midi=0;//pour bypasser le EV pointeur de midishare

int arduino_digital_function_output[digital_limit][2];//Action // Val

int pwm_data_to_arduino[pwm_limit];
int previous_pwm_data_to_arduino[pwm_limit];

/////////////////////MIDI LAUNCHPAD RETOUR VISUEL D INFOS///////////////////////
bool enable_launchpad=0;
int midi_duree_launchpad=10;
int temp_launchpad=0;//pour envoyer niveau dans tooutes les instructions en level sans se rajouter bp de code
bool midi_launchpad_state[3072];
bool midi_launchpad_state_before[3072];
bool launchpad_impulse_type_is[3072];
int launchpad_color_defined[3072];
int launchpad_color[16];//16 couleurs customisables
int lch_orange=63;
int lch_green=60;
int lch_yellow=62;
int lch_red=15;
int lch_ambre=31;
int lch_orange_fonce=30;
int facteur_cycling=0;//-1 à +1
bool entered_main=0;
bool launchpad_is_a_cycling_effect[3072];//faire fader les leds
bool midi_needs_no_key_on_key_off[3072];
bool launchpad_buffer=0;
////////////////////////////////////////////////////////////////////////////////
char list_midi_affect[3072][36];

//////////////////////////CHASERS//////////////////////////////////////////////
bool index_window_chasers=0;
int index_affichage_digit_time_unit=0;//digit du nombre de chiffres après virgule

int Xchasers=100;
int Ychasers=300;
bool index_over_chasers=0;
bool index_click_move_chasers=0;
int chaser_selected=0;//dans la fenetre  chaser
bool index_enable_edit_chaser=0;
bool index_affect_chaser_to_dock=0;
bool index_do_affect_fx=0;//pour logical intres
int nbre_track_visualisables=4;
int nbre_de_cases_par_track=36;
int nbre_tracks_par_chaser=24;//a garder pour les initiaisation en glob init, ne sert plus c ets core_user_define_nb_tracks_per_chasers
int chaser_operator_is=0;

char chaser_name[128][25];
char chaser_track_name[128][24][25];
float time_unit[128];

int chaser_step_operation[128][24][36];//0= rien 1= up 2= stay 3=down
bool chaser_is_playing[128];
bool chaser_is_in_loop[128];
bool chaser_way[128];//0= left to right 1= right to left
bool chaser_aller_retour[128];
bool track_is_on[128][24];
int track_level[128][24];
int position_affichage_track_num[128];
int TrackTypeIs[128][24];//0 circuits normaux 1//memoire
int  TrackContains[128][24][514];//contenu
int TracksBuffer[128][24][514];//le report des calculs
int MergerBufferChasers[128][514];//le merge des chasers


float index_progression_chaser_step[128];//pour crossfade et affichage
float previous_index_progression_chaser_step[128];//pour Back banger
int chaser_begin_step_is[128];//debut boucle
int chaser_end_step_is[128];//fin boucle
bool chaser_time_mode[128];//le type de calcul du temps pour le chaser: cases jointes ou pas

int chaser_time_position[128];//position du curseur sur le déroulé du chaser: TImeline
int chaser_start_time[128];//ticks actual time of chaser
float chaser_start_of_step[128];
float chaser_end_of_step[128];
int chaser_step_is[128];//position du step pour l affichage visuel
int previous_chaser_step_is[128];//pour banger back

int count_steps_for_fades[128][24];//compteur des cases équivalentes pour calcul des fades IN OUT sur plusieurs cases
int joint_begin_step[128][24];//report du nombre de step egaux lorsque le chaser tourne ( permet la fraction en Joint mode)
int joint_end_step[128][24];//report du nombre de step egaux lorsque le chaser tourne ( permet la fractioon
int joint_nbr_step[128][24];//report du nbre de step du time joint

int chaser_selected_for_record=0;//pour confirmations
int track_selected_for_record=0;//pour confirmations
int chaser_preset_selected_for_record=0;//pour confirmations

bool index_do_dock_track=0;
bool index_do_clear_track=0;
bool index_do_report_track=0;
bool index_do_modify_track=0;
bool index_do_clear_chaser=0;
bool index_do_store_chaser_preset=0;
bool index_do_clear_chaser_preset=0;

int view_chaser_affected_to_fader[128][2];//enregistrement de la derniere affectation du chaser
bool index_slave_chaser_to_accelerometre[128];//asservissement à l accélérometre du dernier fader affecté

float chaser_slaviness[128];
float previous_chaser_slaviness[128];
bool chaser_preset[128][4][24];

bool launchpad_chaser_mode=0;
int chaser_midi_rows=4;//nbre de lignes utilisées pour le lauchpad en attaque midi des tracks
int previous_color_on_chaser[8][8];
int chaser_step_launchpad[128];//position de la grille de 8 par chaser en X

int mem_to_load_in_chaser=0;
bool index_do_store_mem_in_chaser=0;
int TrackHasMem[128][24];
//visualisation en mode view
int over_track_show_channel[514];
bool i_m_over_a_track=0;

char string_param_mover_is[76];





///////////MOVER//////////////////////////////////////////////////////////////
bool index_show_mover_window=0;
bool index_over_mover=0;
bool index_click_move_mover=0;

bool index_affect_to_dock_mover=0;
bool  index_do_affect_mover=0;//pour confirm ask

volatile float actual_spline_tick=0.0;

volatile int ticks_move = 0;
// convert from shorts to bytes and back again
#define short_get_high_byte(x) ((HIGH_BYTE & x) >> 8)
#define short_get_low_byte(x)  (LOW_BYTE & x)
#define bytes_to_short(h,l) ( ((h << 8) & 0xff00) | (l & 0x00FF) );


int xmover_window=100, ymover_window=100;


char string_tracker_mode[8];
char string_tracker_coordonates[24];
char string_view_16bits_coordonates[64];
int v16viewX=0, v16viewY=0;

char string_tracker_coordonates_fine[24];
char string_titre_stepsL1[8];
char string_titre_stepsL2[8];
char string_dock_selection[64];
char string_dock_selection2[64];
char string_seconds_Tracker_speed_is[16];
char string_x_y_rescaled[32];
char string_spline_ratio[24];

bool tracker_mode=1; //0 = 8 bits - 1= 16 bits


bool lockX_on=0, lockY_on=0; // lock or not le mouvement x ou y
bool invX_on=0, invY_on=0; // inversion 0-255 du data a envoyer


bool index_mouse_is_tracking=0;//pour eviter de selectionner d autres action spednant tracking a la souris

bool index_ask_clear_a_move=0;
int move_to_clear=0;
bool index_cycle=0;
bool index_move_crossfade_is_on=0;
bool index_move_back=0;
bool index_move_forward=0;
float x_val_at_beg[32], y_val_at_beg[32];
float x_val_at_end[32], y_val_at_end[32];
float x_fract[32],y_fract[32];
int move_start_value=0;
int move_elapsed_time=0;
int move_current_time=0;
int move_end_value=0;
int next_step[32];



int xadress=1; int yadress=3;
int Tracker_speedlevel=127; //vitesse mouvements
float Tracker_speed_is=0.0;
int dock_move_selected=1;//nuemro du dock selectionne
int dock_move_xy[32][48][2]; // les 48 steps des 31 docks sur les x et y. 8 bits
int dock_move_xy_16b[32][48][2];//le 16bits
int dock_time[32][48];
int dock_move_actual_step[32];// le step actuel
int dock_moves_contains_steps[32]; // le nombre de steps contenus

int dock_asservis[32][48][16];//iris flous, etc....
int position_defaut[2];
bool move_auto_stop[32][48];
bool index_show_points=1;
bool index_spline=0;
float spline_ratio[32];//pour chaque spline
int Tracker_splinelevel=0;//slider
float spline_tick_fraction=0;//pour cross en spline

bool index_goto_record=0;
int GotoMoves[32][48];
int Moves_Inpoint[32];
bool index_into_record=0;

float color_cycling=0.0; //pour affichage couleur speed cross en cours


bool index_saved=0;

unsigned char buffer_moving_head[512];
int scale_tracker[256][2];


int buffer_moving_head_rescaled[512];


char string_zero_point_is[24];

int irisadress=30;
int focusadress=32;
int zoomadress=30;

int mover_params_adresses[32];

float iris_at_beg[32];
float iris_at_end[32];
float iris_fract[32];
float focus_at_beg[32];
float focus_at_end[32];
float focus_fract[32];

float zoom_fract[32];
float zoom_at_end[32];
float zoom_at_beg[32];




bool index_time_shift=0; // redistribution du temps sur un dock
char string_time_shift[64];

bool index_copy_params=0; // affectation d un iris et d un focus fixes à un dock
bool param_selected[48];//selection pour set to bank
int mover_params[48][2];//16 données dont X Y iris zoom etc [0]=8 bits [1] donnee en 16 bits
int before_mover_params[48][2];


bool tracker_16b_edit=0; // pour souris sur tracker aera= Fine et iris etc...

////////// ICAT //////////
int enable_iCat=0;
bool receiving_bytes_iCat=0;//pour visu data in
bool index_window_gui_iCat=0;
char iphone_fonts[12][25];//12 fonts possibles


//sur meme adresse IP que sélectionnée
char fantastick_message[64];

char FS_BUFFER[64];
char FS_IP[64];// received
char specified_fs_ip[17]={"192.168.1.13"};
int FS_touch_point_begin[2][12];// 0=x 1=y 12 points
int FS_touch_point_move[2][12];// 0=x 1=y 12 points
int FS_touch_point_stationnary[2][12];// 0=x 1=y 12 points
int FS_touch_point_end[2][12];// 0=x 1=y 12 points
int fs_max_points=5;//max 12 dans la structure
float fs_accelerometer[3];

/*
int FS_sensibilite_touche[12];//nombre de doigts
int valeur_sensibilite=200;
*/
int nbre_icat_points_detectes=0;//detectes par ipod
int before_nbre_icat_points_detectes=0;


int nbre_d_envois_de_l_info=1;//iterations udp

char StrOrderToiCat[96];

bool refresh_icatpage_please=0;//index en cas de besoin de rafraichir toute la page

//client
SOCKET sockiCat;
SOCKADDR_IN siniCat;
int sinsizeiCat;
bool client_icat_is_closed=1;
//serveur
SOCKET sockRiCat;
SOCKADDR_IN sinServiCat;
int sinsizeServiCat;
bool iCat_serveur_is_initialized=0;
/////////////////////////
int nbrbytessendediCat=0;
int bytesreceivediCat=0;
int serveurport_iCat=6661;
int clientport_iCat=6662;


int X_gui_iCat= 20 ;
int Y_gui_iCat =20 ;

bool index_re_init_FS_client=0;// rajouté pour nouvelle mouture reseaux

bool index_click_move_iCat=0;

int surface_type=0;//0 = i pod 240*160 1=ipad resolution de drawing dans la gui

//résolution ipod touch 3-4: 380*240
//resolution ipod touch 4: 960*480
//res Ipad 1 et 2: 1024 * 768
//on divise par 2 pour la GUI

int L_tablier_iCat=240;
int H_tablier_iCat=160;

int largeuriCat=540;
int hauteuriCat=540;

bool index_icat_copyPage=0;//pour copier une page sur l'autre
int iCatPageToCopyIn=0;
int index_ask_icat_copyPage=0;

bool index_ask_iCat_selectiv_clear=0;

int l_sl=0; int h_sl=0; //pour largeur hauteur iCat sliders
int grid_icat_modulo=10;
int iCatPageis=0;//page preset iCat
int oldiCatPageis=-1;//pour infos affichage num de page icat
int editing_GUI_type_iCat=0; //0= pas d'edit d objet 1=slider 2=bouton 3=strings
bool do_send_icat_init_page=0;//envoi des messages

bool index_ask_clear_iCatpage=0;

//tableau créé en 24 mais on utilise 8
int max_sliders_icat=47;//voir avec les tableaux, mais pas au dessus de 23
int iCat_preset_orientation[8];

int iCat_select_editing_slider=0;
int iCat_nbre_de_sliders[8];//max 8 par 8 preset
int iCat_pos_slider[8][48][2];//x y
bool iCat_orientation_slider[8][48];//0 vertical 1 horizontal
int iCat_affectation_slider_type_is[8][48];//type 1 faders, 2 fader speed, 3 sequenciel   /  4 grand master
int iCat_affectation_slider_value_is[8][48];//valeur de la famille 1/48 / speed fader/ stage/preset/accel
int ratio_iCat_slider[8][48];//multiplicateur des proportions de sliders. 1 / 2 / 3
bool slider_is_touched[8][48];
bool before_slider_is_touched[8][48];
int slider_is_controlled_by_point[8][48];
int level_from_touch[8][48];

int iCatSlidersizeX= 16;//16
int iCatSlidersizeY= 128;//128
float col_fader_r=0.0, col_fader_g=0.5, col_fader_b=0.6;  //couelur affichages faders icat
int before_niveauX1=0, before_niveauX2=0, before_crossfade_speed=0;

bool before_is_dock_for_lfo_selected[48];

bool check_button_state[48];//test des états des boutons de la page
bool before_check_button_state[48];

int largueur_bouton=32;
int max_buttons_icat=47;//max 48 par preset/ pas au dessus de 47
int iCat_select_editing_button=0;
int iCat_nbre_de_boutons[8];//max 48 par preset
int iCat_pos_bouton[8][48][2];//x y
int ratio_iCat_button[8][48];//multiplicateur des proportions du bouton. 1 / 2 / 3
int iCat_affectation_bouton_type_is[8][48];//type faders, sequentiel, audio family
int iCat_affectation_bouton_action_is[8][48];//action par type: UP DOWN GO GO BACK etc
int iCat_affectation_bouton_value_is[8][48];//valeur de la famille 1/48 stage/preset/accel etc
bool button_is_touched[8][48];
bool previous_button_is_touched[8][48];
int button_is_controlled_by_point[8][48];

bool index_refresh_valeurs_continous=0;//pour changement de preset
bool finished_to_send_orders_to_iCat=0;//permet d eviter le telescopage des ordres et la disparition de paquets
bool index_refresh_valeursTRCK_continous=0;//pour rafraichissementt

bool  index_false_shift=0;
bool  index_false_control=0;


int iCat_select_tracking_zone=0;
int  iCat_nbre_de_tracking_zone[8];//max 8 par page
const int max_zones_icat=7;
int iCat_pos_trackzone[8][8][2];//x y
int ratio_iCat_trackzone[8][8];//multiplicateur des proportions du bouton. 1 / 2 / 3
int iCat_trackzone_type_is[8][8];// MOVER number
int iCat_trackzone_affectation_is[8][8];
int pos_iCat_tracker[8][8][2];
int previous_pos_iCat_tracker[8][8][2];

bool zone_is_touched[8][8];
bool previous_zone_is_touched[8][8];
int zone_is_controlled_by_point[8][8];
int largeur_trackzone=128;

int largeur_string=176;
int hauteur_string=24;
int max_string_icat=23;//max 24 pas au dessus de 23
int iCat_nbre_de_strings[8];//max 24
int iCat_select_editing_string=0;
int iCat_pos_string[8][24][2];//x y
int ratio_iCat_string[8][24];//multiplicateur des proportions du bouton. 1 / 2 / 3
int iCat_affectation_string_type_is[8][24];//type string: feedback / sequenciel mems
int iCat_affectation_string_action_is[8][24];//
int iCat_affectation_string_value_is[8][24];//affectations valeurs sequeciels strings

int previous_numeric_postext=0;//pour rafraichissement string icat
int previous_last_ch_selected=0;
int previous_last_dim_selected=0;
char previous_string_Last_Order[256];
char previous_string_confirmation[128];

bool  index_ask_clear_img_icat=0;//reset des images et rechargement global

int previous_mem_before_one=0;
int mem_after_one=0;
bool someone_changed_in_sequences=0;
bool someone_changed_in_time_sequences=0;//specifique affichage du temps de crossfade

int go_channel_is=0;
int pause_channel_is=0; //pause channel blink on pause in cuelist

bool index_monitor_key_esc=0;

//////////////////

bool index_show_shortcuts=1;
bool index_call_help=0;

//////////GRIDER 24*24 matrice evailable//////////////////

bool index_grider_window=0;

bool index_click_move_Grider=0;
bool index_over_Grider=0;
int grider_window_x=100;
int grider_window_y=100;
int grider_begin_channel_is=1;
int grider_nb_col=20;
int grider_nb_row=10;

bool index_enable_edit_Grider=0;
int size_grille=15;

//previsu d une grid sans edition
int hauteurGlobalGridviewer=100;
bool show_global_view_grider=0;
int grid_selected_for_view=0;//grid
int grid_step_view=0;//step
char string_grid_view_timing_global[24][60];//visu de 24 steps avec timings
char string_grid_view_timing_global_delays[24][60];//visu de 24 steps avec timings delays
char string_grid_count[4][24];
int size_preview_case=5;


int index_nbre_griderplayers_visibles=0;

int index_grider_selected[4];
int index_grider_step_is[4];
int index_grider_seek_pos[4];
bool grider_is_playing[4];
bool grider_autostopmode[4];//le lecteur
bool index_show_grid_player[4];
//options d enclenchement des calculs
bool grider_goto_mode[4];
bool grider_seekto_mode[4];
bool grider_stoplay_mode[4];
bool grider_count_mode[4];
int grid_count[128][1024];
int grid_counted_times[128][1024];//index de comptage fait
bool to_step_editing_mode[4];
int index_StepTo[4];
int index_Grid_copyto[4][2];//0 grid 1 step
bool grid_player_slave[4];
bool grid_affect_to_dock[4];


int largeurGrider=710;
int grider_facteur_hauteur=10;
int hauteurGrider=50+(index_nbre_players_visibles*(30+(grider_facteur_hauteur*size_grille)))+hauteurGlobalGridviewer;

int position_grid_editing;//pour encodage des cases over case= position de case // sert pour les 4 grid players

int  temoin_over_grid_channel=0;//channel pas pos de grid

char grider_name[128][25];
unsigned char grid_levels[128][1024][513];//grid number // steps // 24*24 les cases max
unsigned char temp_grid_levels_for_save[32][1024][513];//pour sauvegarde
float grid_times[128][1024][4];//0=DIN 1=IN 2=DOUT 3=OUT  // ATTENTION NO DELAY !!!!
int grid_goto[128][1024][2];//0 grid 1 step
int grid_seekpos[128][1024];//step seek pos
bool grid_stoplay[128][1024];//1=pause

char string_time_in_grider[4][60];//onstage
char string_time_in_grider_next_step[4][60];//report conversion fait 52

char string_next_step_to[4][48];
//pour confirmation actions
bool index_clear_a_grid_step=0;
bool index_clear_a_grid=0;
bool index_clear_a_grid_serie_step=0;
int grid_to_clear=0;
int step_grid_to_clear=0;
int index_for_grid_stepto=0;
bool index_for_copy_grid=0;
bool index_for_insert_grid=0;
int destination_grid_for_copy=0;
int destination_step_for_copy=0;
bool index_grid_tostep_or_not=0;
int from_gridstep_to=0;
bool index_do_affect_grid_to_fader=0;

int gridplayer_to_affect_is=-1;//desafecté
int faders_dock_grid_affectation[48][6];//grid


int grid_midi_multiple_for_step_call[4];//pourappel des 1024 pas en midi
int GplSnapFader[4];

//les 4 players crossfades
unsigned char buffer_gridder[4][513];

int grid_crossfade_start_time[4];
int grid_end_time[4];
int grid_crossfade_speed[4];
int grid_niveauX1[4];
int grid_niveauX2[4];
float grid_floatX1[4];
float grid_floatX2[4];
float grid_fraction_X2_in[4];
float grid_fraction_X1_out[4];
int grid_in_preset[4][2];//0 la grille 1 le step

float tempIN[4], tempOUT[4];
int grid_delay_in[4], grid_delay_out[4];
//liaison Gridplayer MEM seuqenciel
int set_from_seq_gridplayer1_next_step[10000];
bool index_do_affect_step_gridplayer_to_mem=0;
int index_mem_to_be_affected_by_gpl=0;
int gpl1_affect_step_to_mem=0;
bool show_gridplayer_in_seq=0;//pour le sequenciel
bool index_link_speed_crossfade_to_gpl1=0;
///////////// CORE PROCESSS ///////////////
bool index_config_core=0;
int core_user_define_nb_faders=48;
int core_user_define_nb_docks=6;
int core_user_define_nb_chasers=128;
int core_user_define_nb_tracks_per_chasers=24;
int core_user_define_nb_gridplayers=4;
int core_user_define_nb_bangers=128;
int core_do_calculations[24];

//////////////////////////////////////
int mouse_level_for_banger=0;
int mouse_level_for_event=0;
/////////windows list//////////////////
int window_order[60];
int prev_window_focus_id=0;

//exclusion de circuits
bool Channels_excluded_from_grand_master[514];
bool index_do_exclude=0;

bool Midi_Force_Go=0;

//trichro
bool index_paste_on_the_fly=0;

//highpass / prio
bool index_do_hipass=0;
int FaderManipulating=0;

//nouvelle structure de groupe de faders
int fader_mode_with_buffers[48];// 0 NORMAL / 1 OFF RENDERING / 2 SUBSTRACT / 3 ADDITIF / 4 SCREEN / 5 EXCLUSION
bool fader_fx_route[48];/// 1 Buffer séquenciel / 0 Buffer faders
bool channel_is_touched_by_fader_fx[513];
int channel_is_touched_by_fader_number[513];
int channel_is_touched_by_fader_type_fx[513];

int channel_level_mofification_while_crossfade[513];//correcteur en crossfade

int over_banger_event=0;
int over_banger_action=0;
bool over_family=0;//0 event 1 action

bool index_do_fgroup=0;//assignation de groups de faders record dock typ 13
bool  index_do_affect_fgroup=0;
bool fgroup[48][6][48];//fader dock isingroupaffected=1

int List_view_nbre_channels=17;
int nbre_macros_per_channel=4;
bool macro_channel_on[514][4];
int channel_macro_reaction[514][4];
int channel_macro_action[514][4];
int channel_macro_val[514][4][2];
int max_channel_macro_reaction=8;
int max_channel_macro_action=17;
unsigned char previous_state_of_outputted_channels[514];
int chan_to_manipulate=0;

///window plot
bool index_plot_window=0;
int x_plot=100;
int y_plot=100;
int plot_window_x_size=1024;
int plot_window_y_size=750;
int plot_minimum_y_size=570;
int plot_nbre_col=10;//nbre colones plot bckgrd recalcule tt le temps
int plot_nbre_lin=10;
int plot_quadrillage_size=50;
int position_plan_x=230;//plan dessin
int position_plan_y=50;//plan dessin
bool index_edit_symbol_plot=0;
bool index_edit_light_plot=1;


int index_menus_lighting_plot=0;//0 bckgs 1 shape 2 symbol 3 legend 4 working space

int plot_viewpoint_xy[2];//deplacement relatif de tout le plan


Rgba CouleurPlotLine(0.0,0.0,0.0);
Rgba CouleurPlotFill(0.6,0.6,0.6);

int symbol_selected_type=0;
int max_symbol_type=66;
float size_symbol[127];
char symbol_nickname[127][25];
float angle_projo_selectionne=0.0;

int symbol_id_to_select=0;

//128 symbols possibles par page x4
const int nbre_symbol_per_layer=128;
bool show_calc_number[4];
short view_plot_calc_number_is=0;//num edition du calc
bool plot_layer_mode=0;//0 calc, 1 solo
int nbre_symbols_on_plot[4];

int symbol_type[4][nbre_symbol_per_layer];
bool symbol_is_selected[4][nbre_symbol_per_layer];
float angle_symbol[4][nbre_symbol_per_layer];
int pos_symbol[4][nbre_symbol_per_layer][2];
int stored_plot_position[nbre_symbol_per_layer][2];//stockages position temporaires en edition
int symbol_is_linked_to[4][nbre_symbol_per_layer];//couplage de projos

char symbol_note[4][nbre_symbol_per_layer][4][25];
//move dans le plan
bool index_click_inside_plot=0;
int plot_original_mouse_x=0;
int plot_original_mouse_y=0;
int plot_facteur_move_x=0;
int plot_facteur_move_y=0;

bool plot_show_options[12];//affichage du circuit, etc etc)

bool plot_delete_selection[nbre_symbol_per_layer];

bool plot_name_text_size=0;

int symbol_channel_is[4][nbre_symbol_per_layer];
int symbol_dimmer_is[4][nbre_symbol_per_layer];
int nbre_gelats_manufact=3; //0: LEE 1: ROSCO 2: GAMCOLOR 3: Apollo
int gelat[4][nbre_symbol_per_layer][3];//3 slots de gelat par symbol
int gelat_family[4][nbre_symbol_per_layer][3];//3 slots de gelat par symbol

int last_selected_symbol_is=0;

char temp_plot_info[8];

bool index_edit_relativ_xy=0;//pour dire qu on va editer
bool index_click_inside_relativ_xy=0;//click dans la zone
int relatif_plot_xy[4][nbre_symbol_per_layer][5][2];//calc / Symbols / Famille / X Y / rajout textes persos
bool adjust_xy_type[5];

int temp_relatif_plot_xy_array[nbre_symbol_per_layer][5][2];//pour prise de mesure
int rlativ_xm=0;
int rlativ_ym=0;

bool index_plot_send_to_mode=0;//envoyer vers un autre calque

bool index_ask_delete_symbols_on_calc=0;

int plot_layer_selected=0;//pour confirm

float global_symbol_size=1.0;

//SNPASHOT pour manipulations sur un calque:
bool snapshot_symbol_is_selected[nbre_symbol_per_layer];
int snapshot_symbol_type[nbre_symbol_per_layer];
float snapshot_angle_symbol[nbre_symbol_per_layer];
int snapshot_pos_symbol[nbre_symbol_per_layer][2];
int snapshot_symbol_channel_is[nbre_symbol_per_layer];
int snapshot_symbol_dimmer_is[nbre_symbol_per_layer];
int snapshot_gelat[nbre_symbol_per_layer][4];
int snapshot_gelat_family[nbre_symbol_per_layer][4];
int snapshot_relatif_plot_xy[nbre_symbol_per_layer][5][2];
char snapshot_symbol_note[nbre_symbol_per_layer][4][25];
int snapshot_symbol_is_linked_to[nbre_symbol_per_layer];

bool index_build_patch_from_plot=1;

Bitmap LightPlanBitmapMain;
int position_relative_plan_theatre[2];
int taille_relative_plan_theatre[2];

float orientation_plan_theatre;

int old_position_relative_plan_theatre[2];
int old_taille_relative_plan_theatre[2];


bool index_editing_theatre_plan=0;
int original_posx=0;
int original_posy=0;
int moving_plan_relativ_x=0;
int moving_plan_relativ_y=0;

int editing_plan_data_type=0;

char Name_of_plane_is[256];
char list_import_plans[127][256];//menu d affichage des list de plans
int importplan_selected=0;
int line_importplan=0;

float alpha_plan=1.0;
bool editing_plot_sizey=0;
bool editing_plot_sizex=0;
int moving_size_relativ_x=0;
int moving_size_relativ_y=0;
int old_plot_sizex=0;
int old_plot_sizey=0;
int plot_view_port_x=0;
int plot_view_port_y=0;
int previous_plot_view_port_x=0;
int previous_plot_view_port_y=0;
bool index_move_plot_view_port=0;
bool plot_editing_color_background=0;
bool plot_editing_color_line=0;



bool plot_index_show_levels=1;
bool plot_index_show_levels_from_faders=1;

int plot_grid_type=0;//0 petits ppoints, 1 ligne pleine)
float alpha_grille=0.5;

float Color_plotline=0.0;
float Color_plotfill=0.5;

int nbre_shapes_on_plot=0;

const short max_shape_type=11;
char shape_nickname[max_shape_type+1][25];//12 Shapes

int lock_background_proportions=0;

int shape_selected_type=0;
float general_shape_size_to_apply=1.0;
float angle_shape_selected=0.0;
int color_pattern_selected=0;
float opening_angle_selected=0.8;
bool index_adjusting_shape_x=0;
bool index_adjusting_shape_y=0;
float shape_rect_size_x=2.0;
float shape_rect_size_y=4.0;
float temp_shape_rect_size_x=2.0;
float temp_shape_rect_size_y=4.0;

char temp_shape_legend_name[25];

float general_alpha_for_shape=1.0;

int shape_type[nbre_symbol_per_layer];
float shape_attributes[nbre_symbol_per_layer][5];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
int shape_position[nbre_symbol_per_layer][4];//pour les lignes
char shape_legend_name[nbre_symbol_per_layer][25];
int shape_relativ_position_legend_name[nbre_symbol_per_layer][2];
int shape_color_type[nbre_symbol_per_layer];
int shape_groups[nbre_symbol_per_layer];

bool shape_selected[nbre_symbol_per_layer];

bool handle_selected_for_line_editing=0;//0 = x1 y1 1= x2 y2
int stored_plot_shape_position[nbre_symbol_per_layer][4];//temp pour bougeage

bool index_ask_general_clear_on_plot=0;//pour confirm logical
int editing_shape_line_number=0;
int index_show_shape_id=0;
int index_last_shape_selected=0;
int nbre_branches_polygon=6;



//snapshot
bool snap_shape_selected[nbre_symbol_per_layer];
int snap_shape_type[nbre_symbol_per_layer];
float snap_shape_attributes[nbre_symbol_per_layer][5];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
int snap_shape_position[nbre_symbol_per_layer][4];//pour les lignes
char snap_shape_legend_name[nbre_symbol_per_layer][25];
int snap_shape_relativ_position_legend_name[nbre_symbol_per_layer][2];
int snap_shape_color_type[nbre_symbol_per_layer];
int snap_shape_groups[nbre_symbol_per_layer];
int shape_id_to_select=0;

int temp_shape_relativ_position_legend_name[nbre_symbol_per_layer][2];

int fonttype_selected=0;
TextRenderer PlotTextRenderer;

float ratio_lock_plot_scale=1.0;
bool index_do_clear_all_the_patch=0;
bool index_ask_clear_preset_relativ=0;
bool index_ask_modify_preset_relativ=0;
bool index_ask_record_preset_relativ=0;

int xyrelativ_preset=999;

int plot_relativxy_preset[8][4][2];
int mode_relatif_xy_solo=0;

int number_of_shapes_groups=0;

//legend
int legend_position_x=0;
int legend_position_y=0;
int legend_size_y=600;

int plot_list_appareils[127];
bool plot_show_typ_appareil[127];
int plot_ecartement_legende[127];
int nbre_symbols_differents_sur_plot=0;

int index_list_appareils_pour_la_legende[127];

int plot_correcteur_portx=0; int plot_correcteur_porty=0;
char plot_renseignements[40][25];

bool legend_view=1;//affichage legende par liste projos ou affichage symboles

int tmp_gel_list[5][1000][127];//gel manufacturer /  ref max 1000 /  symbol /
char Geo[1000][48];
char GelTyp[12];
char Appareil[25];
int nbre_ligne_pour_gelats=0;

bool index_do_a_screen_capture=0;
bool index_do_a_plot_screen_capture=0;

char plot_name_of_capture[25];
float index_show_button_export=0.0;//bouton affichage
float plot_light_preset_on_click[8];
int last_xyrelativ_preset=0;

bool index_tab_on=0;//pour sélection groupée souris
///////////AFFICHAGES DIVERS CHANNEL SPACE/////////////////////////////////////

bool ClassicalChannelView=1;
int ChannelXMenu=0,ChannelYMenu=0;
int hauteur_ChannelMenu=30;
int largeur_ChannelMenu=1180;
const int nbre_de_vues_circuits=16;
int hauteur_preset_titre=30;

bool Channel_View_MODE[nbre_de_vues_circuits];//les 16 indexes de vision
int Channel_View_ROUTING[nbre_de_vues_circuits][514];
int channel_view_is=0;//0 pas touché car sortie du patch

char channel_view_Name[nbre_de_vues_circuits][25];
int channel_view_link_type[nbre_de_vues_circuits];//0:no link 1:memory 2: fader
int channel_view_link_ref[nbre_de_vues_circuits];//num de mem ou de fader. desaffectation=-1;

int channel_view_type_of_behaviour[nbre_de_vues_circuits];//0 normal view // 1 mem // 2 fader
bool channel_view_mode_builder[nbre_de_vues_circuits];// 0 solo // 1 ALL

int channel_number_in_View[nbre_de_vues_circuits];
int channel_number_of_lines[nbre_de_vues_circuits];
bool index_ask_record_selection_of_view=0;
bool index_ask_modify_selection_of_view=0;
bool index_ask_clear_selection_of_view=0;
bool index_ask_report_selection_of_view=0;

bool index_ask_build_view=0;
bool index_do_build_view=0;

int total_pixel_vision=0;
float ratioview=270.0/total_pixel_vision;

int scroll_pos_preset[nbre_de_vues_circuits];//affichage vision

bool index_show_main_menu=0;//main menu par click droit
int x_mainmenu=0, y_mainmenu=0;
int size_x_mainmenu=365;
int size_y_mainmenu=200;



int expert_mode=0;//confirmations ou pas de record etc...
bool index_show_first_dim=0;
int show_first_dim_array[514][4];//pour affichage du premier grada patché au circuit
bool show_more_than_one_dim[514];



char descriptif_network_adapter[8][256];


/////////////DRAW///////////////////////////////////////////////////////////////

int x_Wdraw=100;
int y_Wdraw=100;
int draw_window_x_size=600;
int draw_window_y_size=610;

int draw_tracking_aera_size_x=555;
int draw_tracking_aera_size_y=430;

//bool drawing_bitmap=0;
bool index_draw_window=0;


bool ask_clear_draw_preset=0;
int draw_prst_to_clear=0;
int drawing_on_index_case;
int previous_index_case[6];
int index_case[6];

bool index_enable_edit_Draw=0;

int draw_preset_parameters[6][2];//grilles de max 25x20 Taille nbre col nbre lignes


int draw_largeur_case[6];
int draw_hauteur_case[6];
int draw_modulo_largeur_case[6];
int draw_modulo_hauteur_case[6];

float draw_preset_levels[6][500];
bool draw_snap_preset_levels[6][500]; //superieur à zero: allumé
int draw_preset_channel_routing[6][500];

int draw_preset_selected=0;
int previous_draw_preset_selected=-1;//icat

int draw_brush_type[6]; //point / GPL
int draw_mode[6];//0= draw 1= erase 2= solo 3=ghost
float draw_level_to_do[6];
float draw_damper_decay_factor[6];
float draw_ghost_to_do[6];

bool draw_point_is_traced[6];//pour curseur maintenu ipad ou souris et routines de up down etc

bool previous_draw_brush_type[6];
int previous_draw_mode[6];
float previous_draw_level_to_do[6];
float previous_draw_damper_decay_factor[6];
float previous_draw_ghost_to_do[6];

int draw_centre_x[6];
int draw_centre_y[6];

int DrawAffectedToDck[48][6];//contenu des draws dans les docks

bool index_affect_draw_to_dock=0;

int draw_channel_recording_mode=0;//draw erase solo reverse

int draw_preset_selected_for_order=0;

bool index_do_draw_affect_to_dock=0;
bool dragging_draw=0;

volatile bool merging_gpl_in_draw=0;

int draw_get_gpl[6];
int draw_offset_gpl[6];

int draw_arduino_xy[4];


//rajout version fevrier 2015 Variables de calculs damper decay
float damper_target_val=0.0;
float damper_val=0.0;
float damper_vel=0.0;

////ECHO
bool index_show_echo_window=0;


int x_echo=100;
int y_echo=100;
int echo_window_x_size=675;
int echo_window_y_size=285;

bool index_enable_edit_echo=0;


bool index_affect_echo_to_dock=0;
bool  index_do_affect_echo_to_dock=0;
int index_selected_echo_for_manipulation=0;

bool index_ask_clear_echo_preset=0;
int echo_over_channel=0;
bool dragging_channel_in_echo=0;

int echo_affected_to_dock[48][6];


int core_user_define_nb_echo=23;

int echo_selected=0;


int echo_pointing_fader_num[24];//le fader pointé
bool echo_is_echo_mode[24];//0= bounce mode 1= continuous Echo mode
float echo_global_params[24][3];
bool echo_channel_manipulate_mode[24];// 0 level up, 1 ground
int echo_grid_channel_position[24];
float echo_levels[24][2][513];
bool do_bounce[24];//déclencheur


float tmp_echo[24][513];
bool echo_way[24][513];
float tmp_falling_from_level[24][513];
bool bounce_is_prepared[24];
int fader_before_bounce[48];

float snap_echo_to_recall[24][513];


//WAVE/////////////////////////////////

bool index_wave_menu_window=0;
int size_x_wave_menus=350;
int size_y_wave_menus=300;
int position_x_wave_menus=100;
int position_y_wave_menus=100;
bool index_click_move_wave_window=0;


bool index_affect_wave_to_dock=0;

int waver_control=16;//la donnée qui pilote la vague
int previous_waver_control=15;
int wave_channel_preset_selected=0;
int channel_slots[4][26];//4 presets de circuits prévus
int brush_selected=0;
float brush_slots[4][26];//4 presets de brosse
int lead_brush_reading[4];
int previous_lead_brush_reading[4];
int buffer_wave[513]; //le buffer de 512 circuits à rendre dans un fader
bool there_is_a_previous_wave_higher_level[513];
bool wave_play_state=0;


