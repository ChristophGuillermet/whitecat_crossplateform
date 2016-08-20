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

* \file Core_6.cpp
* \brief {Global fonctions for the core of whitecat}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Gère la plupart des fonctions global du coeur de whitecat
*
*   Global fonctions for the core of whitecat
*
 **/


int reset_numeric_entry()
{
    sprintf(numeric,"                        ");
    numeric_postext=0;
    numeric[numeric_postext]='\0';
    return(0);
}
///////////////////////////////////////////////////////////////////////////////


void write_text_to_log_file( const std::string &text )
{
    std::ofstream log_file(
        "log_file.txt", std::ios_base::out | std::ios_base::app );

    log_file << text ;    log_file << "\n";
}


void clear_log_file()
{
     std::ofstream log_file("log_file.txt", std::ios_base::out | std::ios_base::trunc );

    char buff[20];
    struct tm *sTm;

    time_t now = time (0);
    sTm = localtime (&now);

    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    write_text_to_log_file( buff);

}


int return_lowest(int data1, int data2)
{
 int lowest_is;
 if (data1>data2){lowest_is=data2;}
 else {lowest_is=data1;}
 return(lowest_is);
}


int return_highest(int data1, int data2)
{
 int highest_is;
 if (data1>data2){highest_is=data1;}
 else {highest_is=data2;}
 return(highest_is);
}




int constrain_data_to_dmx_range(int valeur)
{
    if(valeur<0)
    {
        valeur=0;
    }
    if(valeur>255)
    {
        valeur=255;
    }
    return(valeur);
}


int constrain_data_to_midi_range(int valeur)
{
    if(valeur<0)
    {
        valeur=0;
    }
    if(valeur>127)
    {
        valeur=127;
    }
    return(valeur);
}



//18/07/2015
int unselect_ch_and_symbols()
{
             for (int ci=1;ci<514;ci++)
             {  Selected_Channel[ci]=0;
                for(int calc=0;calc<4;calc++)
                    {
                         for (int i=0;i<nbre_symbol_per_layer;i++)
                        {symbol_is_selected[calc][i]=0;}
                    }
             }
             last_ch_selected=0;
             index_type=0;index_level_attribue=0;



    return(0);
}


int reset_temp_state_for_channel_macros_launch()
{
 for(int i=0;i<514;i++)
 {
     previous_state_of_outputted_channels[i]=-1;
 }
return(0);
}

int fader_set_level(int cmptfader, int val)
{
switch(fader_damper_is_on[cmptfader])
{
case 0:
Fader[cmptfader]=val;
midi_levels[cmptfader]=(Fader[cmptfader]/2);
Fader_dampered[cmptfader].fix_all_damper_state_value(val);
Fader_dampered[cmptfader].set_target_val(val);
break;
case 1:
Fader_dampered[cmptfader].set_target_val(val);
index_fader_is_manipulated[cmptfader]=1;
break;
default:
break;
}

index_fader_is_manipulated[cmptfader]=1;midi_levels[cmptfader]=(Fader[cmptfader]/2);
if(midi_send_out[cmptfader]==1){ index_send_midi_out[cmptfader]=1;}
return(0);
}


//christoph 14/04/14 avoiding clippling on stop
int player1_do_stop()//fade out to avoid clipping in sound when stopping
{
float value_lecteur=(((float)player_niveauson[0])/127);
for(float i=value_lecteur*30; i>0.0;i--)
{
if(i>=0.0){player1->setVolume(i/30);}
}
player1->setVolume(0.0);
player1->stop();
for(float i=value_lecteur*30; i<1.0;i++)
{
if(i<1.0){player1->setVolume(i/30);}
}
player1->setVolume(value_lecteur);
return(0);
}

int player2_do_stop()//fade out to avoid clipping in sound when stopping
{
float value_lecteur=(((float)player_niveauson[1])/127);
for(float i=value_lecteur*30; i>0.0;i--)
{
if(i>=0.0){player2->setVolume(i/30);}
}
player2->setVolume(0.0);
player2->stop();
for(float i=value_lecteur*30; i<1.0;i++)
{
if(i<1.0){player2->setVolume(i/30);}
}
player2->setVolume(value_lecteur);
return(0);
}

int player3_do_stop()//fade out to avoid clipping in sound when stopping
{
float value_lecteur=(((float)player_niveauson[2])/127);
for(float i=value_lecteur*30; i>0.0;i--)
{
if(i>=0.0){player3->setVolume(i/30);}
}
player3->setVolume(0.0);
player3->stop();
for(float i=value_lecteur*30; i<1.0;i++)
{
if(i<1.0){player3->setVolume(i/30);}
}
player3->setVolume(value_lecteur);
return(0);
}
int player4_do_stop()//fade out to avoid clipping in sound when stopping
{
float value_lecteur=(((float)player_niveauson[3])/127);
for(float i=value_lecteur*30; i>0.0;i--)
{
if(i>=0.0){player4->setVolume(i/30);}
}
player4->setVolume(0.0);
player4->stop();
for(float i=value_lecteur*30; i<1.0;i++)
{
if(i<1.0){player4->setVolume(i/30);}
}
player4->setVolume(value_lecteur);
return(0);
}


bool check_channel_is_patched(int ch)
{
    bool the_ch_is_patched=0;
    for (int cpatch=1; cpatch<513; cpatch++)
    {
        if(Patch[cpatch]==ch)
        {
            the_ch_is_patched=1;
        }
    }
    return(the_ch_is_patched);
}

int constrain_int_data_to_this_range(int data, int min, int max)
{
    if(data<min)
    {
        data=min;
    }
    if(data>max)
    {
        data=max;
    }
    return(data);
}

//wave

int set_new_values_in_wave()
{
int _index=0;
for(int i=waver_control;i<26;i++)//vers la droite
{
        if(lead_brush_reading[brush_selected]+_index<26)
            {
            Wave_Dampered[i].set_target_val(255*brush_slots[brush_selected][lead_brush_reading[brush_selected]+_index]);
            _index++;
            }
            if(lead_brush_reading[brush_selected]+_index>=26)
            {break;}
}


_index=0;
for(int i=waver_control;i>=0;i--)//vers la gauche
{

            if(lead_brush_reading[brush_selected]-_index<0)//protection
            {break;}
            if(lead_brush_reading[brush_selected]-_index>=0)
            {
            Wave_Dampered[i].set_target_val(255*brush_slots[brush_selected][lead_brush_reading[brush_selected]-_index]);
            _index++;
            }
}
return(0);
}


int clear_wave_buffer()
{
for(int i=0; i<512;i++)
    {
       buffer_wave[i]=0;
    }
return(0);
}



int clear_wave_brush(int preset)
{
for(int i=0; i<26;i++)
    {
       brush_slots[preset][i]=0.0;
    }
return(0);
}
int clear_wave_slots()
{
for(int i=0;i<26;i++)
{
    Wave_Dampered[i].set_target_val(0.0);
}
return(0);
}

int wave_calculations()
{

  if(previous_waver_control!=waver_control)
  {
   set_new_values_in_wave();
   previous_waver_control=waver_control;
  }

return(0);
}

int seek_to_beg_wave()
{
clear_wave_slots();
waver_control=0;
set_new_values_in_wave();
previous_waver_control=waver_control;
return(0);
}

int check_echo_bounce_done(int ech)
{
    bool someone_bouncing=0;
    for(int i=0; i<512; i++)
    {
        if(echo_levels[ech][0][i]!=echo_levels[ech][1][i] )
        {
            someone_bouncing=1;
            break;
        }
    }
    if(someone_bouncing==0)
    {
        do_bounce[ech]=0;
    }
    return(0);
}


int prepare_bounce(int ech)
{

    for(int i=0; i<512; i++)
    {
        tmp_echo[ech][i]=0.0;
        tmp_falling_from_level[ech][i]=echo_levels[ech][0][i];
        echo_way[ech][i]=0;
    }
    bounce_is_prepared[ech]=1;
    return(0);
}



int recall_channel_state_in_an_echo(int ech)
{

    for(int i=0; i<512; i++)
    {
        echo_levels[ech][0][i]=snap_echo_to_recall[ech][i];
    }
    prepare_bounce(ech);
    sprintf(string_Last_Order,"Reloaded channel state in Echo %d",ech+1);
    return(0);
}


int  snap_fader_state(int echo, int f)
{
    if(f>0 && f<=48 && calculation_on_faders_done==1)
    {
        for(int i=1; i<513; i++)
        {
            if(((float)(FaderDoDmx[f][i]))/255>=echo_levels[echo][1][i-1])//si plancher
            {
                echo_levels[echo][0][i-1]=((float)(FaderDoDmx[f][i]))/255;//((float)(FaderDockContains[f][dock_used_by_fader_is[f]][i]))/255;
                snap_echo_to_recall[echo][i-1]=echo_levels[echo][0][i-1];
            }
        }
        if(Fader[f]!=0)
        {
            fader_before_bounce[f]=Fader[f];
        }
        recall_channel_state_in_an_echo(echo);
        prepare_bounce(echo);
    }
    return(0);
}


int snap_kill_and_bounce(int echo, int f)
{
    if(f>0 && f<=48 )
    {
        snap_fader_state(echo, f) ;

        //si le fader est en train de jouer en LFO, christoph 19/12/14
        if( lfo_mode_is[f]!=0){lfo_mode_is[f]=0;}
        if ( lfo_cycle_is_on[f]!=0){lfo_cycle_is_on[f]=0;}

        Fader[f]=0;
        do_bounce[echo]=0;
        bounce_is_prepared[echo]=0;
        prepare_bounce(echo);
        do_bounce[echo]=1;
    }
    return(0);
}


int record_channel_ch_state_in_an_echo(int ech, int cha)//par circuit
{

    snap_echo_to_recall[ech][cha]=echo_levels[ech][0][cha];

    sprintf(string_Last_Order,"Snaped and stored channel %d state in Echo %d",cha+1,ech+1);
    return(0);
}

int record_channel_state_in_an_echo(int ech)
{
    for(int i=0; i<512; i++)
    {
        snap_echo_to_recall[ech][i]=echo_levels[ech][0][i];
    }
    sprintf(string_Last_Order,"Snaped and stored channel state in Echo %d",ech+1);
    return(0);
}

int clear_banger(int bg)
{
    bang_is_sended[bg]=1;
//sab 02/03/2014 sprintf(bangers_name[bg],"");
    strcpy(bangers_name[bg],"");

    bangers_name[bg][24]='\n';

    do_loop_banger[bg]=0;
    time_loop_banger[bg]=0.0;
    ticker_loop_banger[bg]=0;
//sab 02/03/2014 sprintf(string_alarm[bg],"");
    strcpy(string_alarm[bg],"");

    for(int dd=0; dd<6; dd++)
    {
        bangers_type[bg][dd]=0;//127 bangers // 6 events par banger
        bangers_action[bg][dd]=0;//num action demandée
        bangers_params[bg][dd][0]=0;//0 param1 / 1 param2
        bangers_params[bg][dd][1]=0;
        bangers_delay[bg][dd]=0.0;//delays
    }

    return(0);
}



int recall_fader_state_echo(int f)
{
    Fader[f]=fader_before_bounce[f];
    return(0);
}

int clear_echo_levels(int ech)
{

    for(int i=0; i<512; i++)
    {
        echo_levels[ech][0][i]=0.0;
    }

    return(0);
}

int clear_ground_levels(int ech)
{
    for(int i=0; i<512; i++)
    {
        echo_levels[ech][1][i]=0.0;
    }


    return(0);
}

int clear_echo_preset(int ech)
{
    echo_pointing_fader_num[ech]=1;

    echo_is_echo_mode[ech]=0;

    echo_global_params[ech][0]=0.5;//gravity
    echo_global_params[ech][1]=1.0;//mass
    echo_global_params[ech][2]=0.2;//energy
    echo_channel_manipulate_mode[ech]=0;// 0 level up, 1 mass , 2 ground
    echo_grid_channel_position[ech]=0;

    for(int i=0; i<512; i++)
    {
        echo_levels[ech][0][i]=0.0;
        echo_levels[ech][1][i]=0.0;
        tmp_echo[ech][i]=0.0;
        echo_way[ech][i]=0;
        tmp_falling_from_level[ech][i]=0.0;
        snap_echo_to_recall[ech][i]=0.0;
    }
    do_bounce[ech]=0;//déclencheur

    for (int f=0; f<48; f++)
    {
        fader_before_bounce[f]=Fader[f];
    }




    return(0);
}



int Draw_point_and_perform_level_on_area_NEW(int pr, int position_x, int position_y)
{


    draw_centre_x[pr]=( position_x/draw_largeur_case[pr]);
    draw_centre_y[pr]=(position_y/draw_hauteur_case[pr]);


    index_case[pr]=(draw_centre_x[pr]) + (draw_centre_y[pr]*draw_preset_parameters[pr][0]) ;

    if(index_do_dock==0 && index_main_clear==0 )
    {
        dragging_draw=1;
    }

//affectaction des circuits
    else if(index_do_dock==1 && index_main_clear==0 )
    {
        if(index_enable_edit_Draw==1 && mouse_released==0)
        {
            draw_preset_channel_routing[pr][index_case[pr]]=atoi(numeric);
            if(draw_preset_channel_routing[pr][index_case[pr]]>512)
            {
                draw_preset_channel_routing[pr][index_case[pr]]=512;
            }
            else if(draw_preset_channel_routing[pr][index_case[pr]]<0)
            {
                draw_preset_channel_routing[pr][index_case[pr]]=0;
            }
            int idpos=0;

            switch(draw_channel_recording_mode) //4 modes: 0 solo - 1 until end of line - 2 until end of col - 3 until end of matrix
            {
            case 1://end of line
                for(int pos=index_case[pr]; pos<draw_preset_parameters[pr][0]+ ((position_y/draw_hauteur_case[pr])*draw_preset_parameters[pr][0]) ; pos++)
                {
                    draw_preset_channel_routing[pr][pos]=draw_preset_channel_routing[pr][index_case[pr]]+idpos;
                    if(draw_preset_channel_routing[pr][pos]>512)
                    {
                        draw_preset_channel_routing[pr][pos]=512;
                    }
                    idpos++;
                }
                break;
            case 2://end of col
                for(int pos=draw_centre_y[pr]; pos<draw_preset_parameters[draw_preset_selected][1] ; pos++)
                {
                    draw_preset_channel_routing[pr][index_case[pr]+(pos*draw_preset_parameters[pr][0])]=draw_preset_channel_routing[pr][index_case[pr]]+idpos;
                    if(draw_preset_channel_routing[pr][pos]>512)
                    {
                        draw_preset_channel_routing[pr][pos]=512;
                    }
                    idpos++;
                }
                break;
            case 3://all grid from position
                for(int pos=index_case[pr]; pos<(draw_preset_parameters[pr][0]*draw_preset_parameters[pr][1]) ; pos++)
                {
                    draw_preset_channel_routing[pr][pos]=draw_preset_channel_routing[pr][index_case[pr]]+idpos;
                    if(draw_preset_channel_routing[pr][pos]>512)
                    {
                        draw_preset_channel_routing[pr][pos]=512;
                    }
                    idpos++;
                }
                break;
            default:
                break;
            }
            reset_numeric_entry();
            index_do_dock=0;
            mouse_released=1;
        }
    }
//désaffectation des circuits
    else if(index_do_dock==0 && index_main_clear==1 )
    {
        if(index_enable_edit_Draw==1 && mouse_released==0)
        {
            draw_preset_channel_routing[pr][index_case[pr]]=0;
            //sab 02/03/2014 unused var int idpos=0;

            switch(draw_channel_recording_mode) //4 modes: 0 solo - 1 until end of line - 2 until end of col - 3 until end of matrix
            {
            case 1://end of line
                for(int pos=index_case[pr]; pos<draw_preset_parameters[pr][0]+ ((position_y/draw_hauteur_case[pr])*draw_preset_parameters[pr][0]) ; pos++)
                {
                    draw_preset_channel_routing[pr][pos]=0;
                }
                break;
            case 2://end of col
                for(int pos=draw_centre_y[pr]; pos<draw_preset_parameters[pr][1] ; pos++)
                {
                    draw_preset_channel_routing[pr][index_case[pr]+(pos*draw_preset_parameters[pr][0])]=0;
                }
                break;
            case 3://all grid from position
                for(int pos=index_case[pr]; pos<(draw_preset_parameters[pr][0]*draw_preset_parameters[pr][1]) ; pos++)
                {
                    draw_preset_channel_routing[pr][pos]=0;
                }
                break;
            default:
                break;
            }
            index_main_clear=0;
            mouse_released=1;
        }
    }


    return(0);
}

int recalculate_draw_sizes(int  preset)
{
    draw_largeur_case[preset]=555/draw_preset_parameters[preset][0];
    draw_hauteur_case[preset]=430/draw_preset_parameters[preset][1];
    draw_modulo_largeur_case[preset]=draw_tracking_aera_size_x%draw_preset_parameters[preset][0];
    draw_modulo_hauteur_case[preset]=draw_tracking_aera_size_y%draw_preset_parameters[preset][1];
    draw_tracking_aera_size_x=(draw_largeur_case[preset]*draw_preset_parameters[preset][0])+ draw_modulo_largeur_case[preset];
    draw_tracking_aera_size_y=(draw_hauteur_case[preset]*draw_preset_parameters[preset][1])+ draw_modulo_hauteur_case[preset];
    return(0);
}



int draw_erase_drawing(int p)
{
//clear_bitmap(Draw0);
    for(int ch=0; ch<500; ch++)
    {
        draw_preset_levels[p][ch]=0.0;
    }
    sprintf(string_Last_Order,"Erased Drawing %d",p+1);
    return(0);
}

int clear_draw_preset(int p)
{
    draw_preset_parameters[p][0]=6;
    draw_preset_parameters[p][1]=4;
    recalculate_draw_sizes(p);
    draw_level_to_do[p]=0.1;
    draw_damper_decay_factor[p]=0.1;
    draw_ghost_to_do[p]=0.01;

    draw_mode[p]=0;

    for(int ch=0; ch<500; ch++)
    {
        draw_preset_levels[p][ch]=0.0;
        draw_preset_channel_routing[p][ch]=0;
    }


    index_case[p]=0;
    draw_centre_x[p]=0;
    draw_centre_y[p]=0;


    draw_get_gpl[p]=4;
    draw_offset_gpl[p]=1;


    sprintf(string_Last_Order,"Cleared DRAW Preset %d",p+1);
    return(0);
}


int copy_banger(int source,int dest)
{
    if(index_banger_to_copy_in!=-999)
    {
        sprintf(bangers_name[dest],bangers_name[source]);
        sprintf(string_alarm[dest],string_alarm[source]);
        for(int i=0; i<6; i++)
        {
            bangers_type[dest][i]=bangers_type[source][i];
            bangers_action[dest][i]=bangers_action[source][i];
            bangers_params[dest][i][0]=bangers_params[source][i][0];
            bangers_params[dest][i][1]=bangers_params[source][i][1];
            bangers_delay[dest][i]=bangers_delay[source][i];

        }
        sprintf(string_Last_Order,"Copyed Banger %d in Banger %d", source+1, dest+1);
        index_banger_to_copy_in=-999;
        index_copy_banger=0;
    }
    return(0);
}

int reset_index_actions()
{
    index_do_dock=0;
    index_do_report=0;
    index_do_modify=0;
    index_main_clear=0;

    index_affect_chaser_to_dock=0;
    index_affect_color_to_dock=0;
    index_affect_time=0;
    index_affect_color_to_dock=0;
    index_do_affect_net_to_dock=0 ;
    index_affect_dmxin=0;
    index_affect_video_tracking_to_dock=0;
    index_affect_audio_to_dock=0;

    index_do_fgroup=0;
    index_affect_to_dock_mover=0;
    index_direct_chan=0;
    multiple_direct_chan=0;
    index_affect_draw_to_dock=0;
    index_affect_echo_to_dock=0;
    index_affect_wave_to_dock=0;


    return(0);
}



int reset_indexs_confirmation()
{
    index_do_dock=0;
    index_do_modify=0;
    index_do_report=0;
    index_do_delete_mem=0;
    index_do_create_mem=0;
    index_do_create_mem_plus_faders=0;
    index_do_overecord_mem_plus_faders=0;
    index_do_link_memonstage=0;
    index_do_link_memonpreset=0;
    index_do_link_membefore=0;
    index_do_link_memother=0;
    index_do_record_on_faders=0;
    index_do_modify_on_faders=0;
    index_do_report_on_faders=0;
    index_do_affect_color_on_faders=0;
    index_do_dmx_to_dock=0;
    index_do_artnet_to_dock=0;
    index_do_video_to_dock=0;
//boutons d affect dans les fenetres
    index_do_affect_net_to_dock=0;
//index_config_affect_artnet=0;//artnet

    index_affect_video_tracking_to_dock=0;
    index_affect_dmxin=0;
    index_affect_color_to_dock=0;

    index_record_minifader_preset=0;
    index_clear_minifader_preset=0;
    index_record_minifader_lockpreset=0;
//couleurs de la trichro
    index_do_affect_color_trichro=0;
//channels des roi
    index_do_affect_roi=0;
    index_do_clear_my_roi=0;
    index_do_clear_my_video_preset=0;
//overrecord
    index_do_overrecord_mem=0;
    index_copy_mem_in=0;
//clear index
    index_main_clear=0;
    index_do_clear_dock=0;
    index_do_clear_on_faders=0;
//
    index_do_reload_mem=0;
    index_do_resurrect_mem=0;
//panic jump by keyboard mem
    index_do_jump_while_cross=0;

//exports imports
    index_do_export=0;
    index_do_import=0;
//save classical
    index_do_saveshow=0;
    index_do_loadshow=0;
//reset in memory
    index_do_resetshow=0;
//freeze
    index_do_freeze=0;

//patch
    index_do_clear_patch=0;
    index_do_default_patch=0;
//quit
    index_do_quit_with_save=0;
    index_do_quit_without_save=0;
//audio folder
    index_do_ask_call_audio_folder=0;
    index_do_audio_to_dock=0;
//lock preset
    index_do_clear_lock_preset=0;
//banger
    index_do_banger_memonstage=0;
    index_do_banger_memonpreset=0;
    index_do_banger_membeforeone=0;
    index_do_banger_memother=0;

    //wizard
    index_do_wizard_ch=0;
    index_do_wizard_mem=0;
    index_wizard_do_reload_from_disk=0;
    //direct ch
    index_do_record_direct_ch=0;

    //affectation courbe à un fader
    index_ask_curv_to_fader=0;
    index_re_init_client_artnet=0;
    index_re_init_serveur_artnet=0;

    //affect FX a dock
    index_do_affect_fx=0;

    //chasers
    index_do_dock_track=0;
    index_do_clear_track=0;
    index_do_report_track=0;
    index_do_modify_track=0;
    index_do_clear_chaser=0;
    index_do_store_chaser_preset=0;
    index_do_clear_chaser_preset=0;

    //icat
    index_ask_clear_iCatpage=0;
    index_ask_icat_copyPage=0;
    index_ask_clear_img_icat=0;
    index_ask_iCat_selectiv_clear=0;
    index_false_shift=0;
    index_false_control=0;

    //grider
    index_clear_a_grid_step=0;
    index_clear_a_grid=0;
    grid_to_clear=0;
    step_grid_to_clear=0;
    index_clear_a_grid_serie_step=0;
    index_for_grid_stepto=0;
    index_for_copy_grid=0;
    index_for_insert_grid=0;
    destination_grid_for_copy=0;
    destination_step_for_copy=0;
    index_grid_tostep_or_not=0;
    from_gridstep_to=0;
    gridplayer_to_affect_is=-1;

    index_do_affect_grid_to_fader=0;

    index_do_affect_step_gridplayer_to_mem=0;
    index_mem_to_be_affected_by_gpl=0;

    index_do_exclude=0;
    index_do_affect_fgroup=0;

    index_do_clear_all_the_patch=0;

    index_ask_build_view=0;
    index_do_build_view=0;
    channel_view_is=0;


    index_ask_clear_selection_of_view=0;
    index_ask_record_selection_of_view=0;
    index_ask_modify_selection_of_view=0;
    channel_view_is=0;
    index_ask_report_selection_of_view=0;

    index_ask_clear_a_move=0;
    index_ask_reinit_FS_client=0;

    ask_clear_draw_preset=0;
    index_do_draw_affect_to_dock=0;

    //echo
    index_ask_clear_echo_preset=0;
    index_do_affect_echo_to_dock=0;

    //wave
    index_affect_wave_to_dock=0;

    index_ask_copy_banger=0;
    index_ask_clear_banger=0;

    //sab 02/03/2014 sprintf(string_confirmation,"");
    strcpy(string_confirmation,"");
    return(0);
}

int  affect_wave_to_dock(int fd,int dd)
{
  DockTypeIs[fd][dd]=17;//WAVE
  return(0);
}

int do_clock_level_modification(int level)
{
switch(clocklevel_absolutemode)
{
case 0://relatif
    if(level<64){
    midi_BPM+=relativ_encoder_midi_clock_value;
    ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
    install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);}
    else if(level>64){
    midi_BPM-=relativ_encoder_midi_clock_value;
    if(midi_BPM<=0){midi_BPM=relativ_encoder_midi_clock_value;}
    ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
    install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);
    }
break;
case 1://absolute , on récupère de toute facon le niveau midi comme base
    midi_BPM=relativ_encoder_midi_clock_value*level;
    if(midi_BPM<=0){midi_BPM=relativ_encoder_midi_clock_value;}
    ticker_midi_clock_rate=BPM_TO_TIMER(24 * midi_BPM);
    install_int_ex(ticker_midi_clock , ticker_midi_clock_rate);
break;
default:
break;
}

return(0);
}

int reset_channel_first_dimmer_list()
{
    for (int ch=1; ch<513; ch++)
    {
        for(int d=0; d<4; d++)
        {
            show_first_dim_array[ch][d]=0;
        }
        show_more_than_one_dim[ch]=0;
    }
    return(0);
}

int generate_channel_preview_patch_list()//affichage du premier grada
{
    reset_channel_first_dimmer_list();

    for (int ch=1; ch<513; ch++)
    {
        int index=0;
        for(int d=1; d<513; d++)
        {
            if(Patch[d]==ch  )
            {
                bool tem=0;
                if(index>3)
                {
                    tem=1;
                }
                switch(tem)
                {
                case 0:
                    show_first_dim_array[ch][index]=d;
                    index++;
                    break;
                case 1:
                    show_more_than_one_dim[ch]=1;
                    break;
                default:
                break;
                }
            }


        }
    }
    return(0);
}


int check_presence_of_a_channel_in_views( int idch)
{
    bool reponse=0;
    for(int v=0; v<nbre_de_vues_circuits; v++)
    {
        if(Channel_View_MODE[v]==1)
        {
            for(int c=0; c<channel_number_in_View[v]; c++)
            {
                if(Channel_View_ROUTING[v][c]==idch)
                {
                    reponse=1;
                    break;
                }
            }
        }
        if(reponse==1)
        {
            break;
        }
    }
    return(reponse);
}

int check_wich_channel_is_in_view(int idch)//pour srcoll bar
{
    bool reponse=0;
    int prs=0;
    for(int v=0; v<nbre_de_vues_circuits; v++)
    {
        if(Channel_View_MODE[v]==1)
        {
            for(int c=0; c<channel_number_in_View[v]; c++)
            {
                if(Channel_View_ROUTING[v][c]==idch)
                {
                    reponse=1;
                    prs=v;
                    break;
                }
            }
        }
        if(reponse==1)
        {
            break;
        }
    }
    return(prs);

}

int check_presence_of_any_channel_in_A_view(int v)
{
    bool reponse=0;

    if(Channel_View_MODE[v]==1)
    {
        for(int c=0; c<channel_number_in_View[v]; c++)
        {
            if(Selected_Channel[(Channel_View_ROUTING[v][c])]==1)
            {
                reponse=1;
                break;
            }
        }
    }
    return(reponse);
}


int check_presence_of_A_channel_in_A_view(int v, int ch)
{
    bool reponse=0;

    for(int c=0; c<channel_number_in_View[v]; c++)
    {
        if(Channel_View_ROUTING[v][c]==ch)
        {
            reponse=1;
            break;
        }
    }

    return(reponse);
}

int detect_last_activ_channel_in_activ_view(int v)
{
    int id=Channel_View_ROUTING[v][(channel_number_in_View[v]-1)];

    return(id);
}


int toggle (int index_to_toggle)
{
    switch(index_to_toggle)
    {
    case 0:
        index_to_toggle=1;
        break;
    case 1:
        index_to_toggle=0;
        break;
    default:
        index_to_toggle=0;
        break;
    }
    return(index_to_toggle);
}



int bounce(int b)
{

    recall_channel_state_in_an_echo(b);
    do_bounce[b]=1;

    return(0);
}



int count_number_of_channels_in_view(int view_is)
{
    int indexCH=0;
    for(int i=0; i<513; i++)
    {
        if(Channel_View_ROUTING[view_is][i]>0 )
        {
            indexCH++;
        }
    }
    channel_number_in_View[view_is]=indexCH;
    channel_number_of_lines[view_is]=(int)(((float)indexCH)/12);
    if(indexCH%12>0)
    {
        channel_number_of_lines[view_is]+=1;
    }
    return(0);
}

int refresh_positions_preset_view_poignee()
{


    total_pixel_vision=0;

//calcul du nombre de pixel total totale
    for(int i=0; i<nbre_de_vues_circuits; i++)
    {
        if(Channel_View_MODE[i]==1)
        {
            total_pixel_vision+=(70*channel_number_of_lines[i])+ hauteur_preset_titre;
            scroll_pos_preset[i]= total_pixel_vision;
        }
    }

    ratioview=270.0/total_pixel_vision;
    return(0);
}



int clear_selection_in(int view_is)//groupes de vues
{
    for(int i=0; i<513; i++)
    {
        Channel_View_ROUTING[view_is][i]=0;
    }
    count_number_of_channels_in_view(view_is);
    return(0);
}

int  build_preset_view_from_mem( int me, int view_is)
{
    if(MemoiresExistantes[me]==1)
    {
        clear_selection_in( view_is) ;
        int pos=0;
        for (int l=1; l<512; l++)
        {
            if(Memoires[me][l]>0)
            {
                Channel_View_ROUTING[view_is][pos]=l;
                pos++;
            }
        }
        count_number_of_channels_in_view(view_is);
        sprintf(channel_view_Name[view_is],"Mem %d.%d", me/10,me%10);
    }
    return(0);
}

int build_preset_view_from_fader( int f, int view_is)
{
    clear_selection_in( view_is) ;
    int pos=0;
    for (int l=1; l<512; l++)
    {
        if((int)(FaderDockContains[f-1][(dock_used_by_fader_is[f-1])][l])>0)
        {
            Channel_View_ROUTING[view_is][pos]=l;
            pos++;
        }
    }

    count_number_of_channels_in_view(view_is);
    sprintf(channel_view_Name[view_is],"Fader %d", f);
    return(0);
}

int reorder_channel_view_list_of_channels(int view_is)
{

    bool presence_of_channel[513];
    for (int l=0; l<=channel_number_in_View[view_is]; l++)
    {
        if(Channel_View_ROUTING[view_is][l]>0)
        {
            presence_of_channel[(Channel_View_ROUTING[view_is][l])]=1;
        }
    }

    int pos=0;
    for (int l=0; l<=channel_number_in_View[view_is]; l++)
    {
        if(presence_of_channel[l]==1)
        {
            Channel_View_ROUTING[view_is][pos]=l;
            pos++;
        }
    }

    return(0);
}

int build_preset_view_from_all_existing_mems(int view_is)
{


    bool selectio_on[513];

    for (int l=0; l<512; l++)
    {
        selectio_on[l]=0;
    }

    for(int me=0; me<9999; me++)
    {
        if(MemoiresExistantes[me]==1)
        {

            for (int l=1; l<512; l++)
            {
                if((int)(Memoires[me][l])!=0)
                {
                    selectio_on[l]=1;
                }
            }
        }
    }
    clear_selection_in( view_is) ;
    int pos=0;
    for (int l=1; l<512; l++)
    {
        if(selectio_on[l]==1)
        {
            Channel_View_ROUTING[view_is][pos]=l;
            pos++;
        }
    }
    count_number_of_channels_in_view(view_is);
    reorder_channel_view_list_of_channels(view_is);
    sprintf(channel_view_Name[view_is],"All Mems");
    return(0);
}

int build_preset_view_from_all_faders(int view_is)
{
    clear_selection_in( view_is) ;
    int pos=0;
    for(int f=0; f<48; f++)
    {
        for (int l=1; l<512; l++)
        {
            for(int dd=0; dd<6; dd++)
            {
                if((int)(FaderDockContains[f][dd][l])>0)
                {
                    Channel_View_ROUTING[view_is][pos]=l;
                    pos++;
                }
            }
        }
    }

    count_number_of_channels_in_view(view_is);
    reorder_channel_view_list_of_channels(view_is);
    sprintf(channel_view_Name[view_is],"All Faders");
    return(0);
}


int build_preset_view_from_all_existing_mems_and_faders(int view_is)
{
    clear_selection_in( view_is) ;

    bool selectio_on[513];

    for (int l=0; l<512; l++)
    {
        selectio_on[l]=0;
    }
//memoires
    for(int me=0; me<9999; me++)
    {
        if(MemoiresExistantes[me]==1)
        {

            for (int l=1; l<512; l++)
            {
                if((int)(Memoires[me][l])!=0)
                {
                    selectio_on[l]=1;
                }
            }
        }
    }
//faders
    for(int f=0; f<48; f++)
    {
        for (int l=1; l<512; l++)
        {
            for(int dd=0; dd<6; dd++)
            {
                if((int)(FaderDockContains[f][dd][l])>0)
                {
                    selectio_on[l]=1;
                }
            }
        }
    }

    int pos=0;
    for (int l=1; l<512; l++)
    {
        if(selectio_on[l]==1)
        {
            Channel_View_ROUTING[view_is][pos]=l;
            pos++;
        }
    }
    count_number_of_channels_in_view(view_is);
    reorder_channel_view_list_of_channels(view_is);
    sprintf(channel_view_Name[view_is],"All Mems and Faders");
    return(0);
}

int report_selection_in(int view_is)
{

    for (int v=1; v<nbre_de_vues_circuits; v++)
    {
        for(int ch=0; ch<512; ch++)
        {
            if( Selected_Channel[(Channel_View_ROUTING[v][ch])]==1)
            {
                Channel_View_ROUTING[v][ch]=0;
            }
        }
    }




    clear_selection_in( view_is) ;
    int pos=0;
    for (int l=1; l<514; l++)
    {
        if(Selected_Channel[l]==1)
        {
            Channel_View_ROUTING[view_is][pos]=l;
            pos++;
        }
    }
    sprintf(channel_view_Name[view_is],"Reported View");

    for (int vf=1; vf<nbre_de_vues_circuits; vf++)
    {
        count_number_of_channels_in_view(vf);
        reorder_channel_view_list_of_channels(vf);
    }
    return(0);
}

int generate_channel_view_list_from_patched_circuits()
{
    clear_selection_in(0);
    int index=0;
    bool nopatchit=0;
    for(int ch=1; ch<513; ch++)
    {
        for (int i=1; i<513; i++)
        {
            if(Patch[i]==ch)
            {
                for(int u=0; u<513; u++)
                {
                    if(Channel_View_ROUTING[0][u]==ch)
                    {
                        nopatchit=1;
                        break;
                    }
                }
                if(nopatchit==0)
                {
                    Channel_View_ROUTING[0][index]=ch;
                    index++;
                }
            }
        }
        nopatchit=0;
    }
    count_number_of_channels_in_view(0);

    generate_channel_preview_patch_list();
    return(0);
}



int record_selection_in(int view_is)//groupes de vues
{
    clear_selection_in(view_is);

    int index=0;
    for(int i=1; i<514; i++)
    {
        if(Selected_Channel[i]==1)
        {
            Channel_View_ROUTING[view_is][index]=i;
            index++;
            Selected_Channel[i]=0;
        }
    }
    count_number_of_channels_in_view(view_is);
    return(0);
}



int modify_selection_in(int view_is)//groupes de vues
{
    bool temp_selv[514];

    for(int i=0; i<514; i++)
    {
        temp_selv[i]=0;
    }

    for(int i=0; i<514; i++)
    {
        if(Channel_View_ROUTING[view_is][i]>0)
        {
            temp_selv[(Channel_View_ROUTING[view_is][i])]=1;
        }
    }

    for(int i=1; i<514; i++)
    {
        if(Selected_Channel[i]==1)
        {
            temp_selv[i]=toggle(temp_selv[i]);
        }
    }

    clear_selection_in(view_is);

    int index_ch=0;
//clear d'un circuit existant sélectionné
    for(int i=1; i<514; i++)
    {
        if(temp_selv[i]==1)
        {
            Channel_View_ROUTING[view_is][index_ch]=i;
            index_ch++;
        }
    }


    count_number_of_channels_in_view(view_is);


    return(0);
}


int clear_plot_legend()
{

    for(int i=0; i<39; i++)
    {
        sprintf(plot_renseignements[i],"-");
    }
    sprintf(plot_renseignements[0],"TITRE DU SPECTACLE");
    sprintf(plot_renseignements[1],"COMPAGNIE");
    sprintf(plot_renseignements[19],"1 CARRE 1 METRE");
    sprintf(plot_renseignements[20],"LightPlan generated by");
    sprintf(plot_renseignements[21],"WhiteCat LightingBoard");

    return(0);
}


int affect_mover_to_fader(int thefader, int thedock)
{
    DockTypeIs[thefader][thedock]=14;
    return(0);
}

int reset_error_on_save_load()
{
    for (int f=0; f<256; f++)
    {
        b_report_error[f]=0;
    }
    there_is_an_error_on_save_load=0;
    return(0);
}

int detect_error_on_save_load()
{
    for (int f=0; f<256; f++)
    {
        if( b_report_error[f]==1)
        {
            there_is_an_error_on_save_load=1;
            break;
        }
    }
    return(0);
}

int clear_report_string()
{
    for(int i=0; i<256 ; i++)
    {
        sprintf(string_save_load_report[i],"-");
    }
    reset_error_on_save_load();
    return(0);
}

int clear_xyrelativ_preset(int pr)
{
    for(int i=0; i<5; i++)
    {
        plot_relativxy_preset[pr][i][0]=0;
        plot_relativxy_preset[pr][i][1]=0;
    }
    return(0);
}

int affect_preset_xy_to_symbols(int pr)
{
    for(int i=0; i<nbre_symbol_per_layer-1 ; i++)
    {
        if(symbol_is_selected[view_plot_calc_number_is][i]==1)
        {
            for(int j=0; j<5; j++)
            {
                relatif_plot_xy[view_plot_calc_number_is][i][j][0]=plot_relativxy_preset[pr][j][0];
                relatif_plot_xy[view_plot_calc_number_is][i][j][1]=plot_relativxy_preset[pr][j][1];
            }
        }
    }

    return(0);
}
int record_preset_xy_from_symbol(int pr)
{
    for(int i=0; i<5; i++)
    {
        plot_relativxy_preset[pr][i][0]=relatif_plot_xy[view_plot_calc_number_is][last_selected_symbol_is][i][0];
        plot_relativxy_preset[pr][i][1]=relatif_plot_xy[view_plot_calc_number_is][last_selected_symbol_is][i][1];
    }
    return(0);
}



int clear_completely_the_patch()
{
    for(int i=0; i<514; i++)
    {
        Patch[i]=0;
        curves[i]=0;
        dimmer_type[i]=0;
    }
    //modif 18/12/14 merci rui serge
     for(int pl=0;pl<128;pl++)
    {
    snapshot_symbol_dimmer_is[pl]=0;
    for(int c=0; c<4; c++)
        {
            symbol_dimmer_is[c][pl]=0;
        }
    }
    return(0);
}

int show_title()
{
    logo.Blit((largeur_ecran/2)-150,(hauteur_ecran/2));//ne s'affiche que en 32 bits
    neuroTitle.Print("WHITE CAT", (largeur_ecran/2)-200,(hauteur_ecran/2)-200);
    neuromoyen.Print(nickname_version, (largeur_ecran/2)+200,(hauteur_ecran/2)-260);
    neuro.Print("http://www.le-chat-noir-numerique.fr", (largeur_ecran/2)-160,(hauteur_ecran/2)-170);
    petitchiffre.Print("(c)christoph guillermet", (largeur_ecran/2)-55,(hauteur_ecran/2)-150);
    petitpetitchiffre.Print(versionis, (largeur_ecran/2)-70,(hauteur_ecran/2)-120);

    return(0);
}


int load_plan_of_theatre( char name_of_plan[256], bool rescan_width_eight)
{

    char temp_namePlot[272];

    sprintf(temp_namePlot,"plans\\%s",name_of_plan);

    LightPlanBitmapMain.Load(temp_namePlot);


    if(rescan_width_eight==1)
    {
        taille_relative_plan_theatre[0]= LightPlanBitmapMain.Width();
        taille_relative_plan_theatre[1]= LightPlanBitmapMain.Height();
    }
    ratio_lock_plot_scale=(float)(taille_relative_plan_theatre[0])/(float)(taille_relative_plan_theatre[1]);

    return(0);
}


int set_plot_background_to_default()
{
    sprintf(Name_of_plane_is,"defaultplot.jpg");
    load_plan_of_theatre(Name_of_plane_is, 1);
    position_relative_plan_theatre[0]=taille_relative_plan_theatre[0]/2;
    position_relative_plan_theatre[1]=taille_relative_plan_theatre[1]/2;
    orientation_plan_theatre=0.0;
    alpha_plan=1.0;
    plot_view_port_x=0;
    plot_view_port_y=0;

    for(int i=0; i<127; i++) //pour rafraichissement au chargement dans la liste des plans
    {
        if(strcmp( Name_of_plane_is,list_import_plans[i])==0)
        {
            importplan_selected=i;
        }
    }
    return(0);
}

int  refresh_shape_factors(int shapetype)
{

//affichage shape
    switch(shapetype)
    {
    case 0:    //curtain
        general_shape_size_to_apply=50.0;
        break;
    case 1:     //ligne  plain
        general_shape_size_to_apply=12.0;
        break;
    case 2:     //stripline 1
        general_shape_size_to_apply=20.0;
        break;
    case 3:     //stripline 2
        general_shape_size_to_apply=20.0;
        break;
    case 4:     //stripline 3
        general_shape_size_to_apply=20.0;
        break;
    case 5:     //stripline 4
        general_shape_size_to_apply=20.0;
        break;
    case 6:     //stripline 5
        general_shape_size_to_apply=20.0;
        break;
    case 7://plot_draw_rectangle(int plotx1, int ploty1, int shapesizex, int shapesizey, float shaperotation, float alphashape, float roundedshape, int colorpattern, bool isselected)
        general_shape_size_to_apply=12.0;
        break;
    case 8://plot_draw_circle(int plotx1, int ploty1, float sizeshape,  float alphashape,   int colorpattern, bool isselected)
        general_shape_size_to_apply=6.0;
        break;
    case 9://plot_draw_slice(int plotx1, int ploty1, float sizeshape, float opening_angle, float shaperotation, float alphashape,   int colorpattern, bool isselected)
        general_shape_size_to_apply=10.0;
        break;
    case 10://polygon
        general_shape_size_to_apply=10.0;
        break;
    case 11://texts
        general_shape_size_to_apply=10.0;
        break;
    default:
        general_shape_size_to_apply=10.0;
        break;
    }
    return(0);
}



int set_all_faders_midi_out(bool state)
{
    for(int i=0; i<48; i++) //faders
    {
        midi_send_out[i]=state;
        if(state==1)
        {
            index_send_midi_out[i]=1;
        }
    }
    for(int i=196; i<(196+48); i++) //LFO
    {
        midi_send_out[i]=state;
        if(state==1)
        {
            index_send_midi_out[i]=1;
        }
    }



    return(0);
}

int refresh_all_midi_out_faders()
{

    for(int i=0; i<48; i++) //faders
    {
            index_send_midi_out[i]=1;
    }

    for(int i=196; i<(196+48); i++) //LFO
    {
            index_send_midi_out[i]=1;
    }

    for (int i=1960; i<2007;i++ )//decay
    {
            index_send_midi_out[i]=1;
    }

    for (int i=2056 ; i <2113; i++)//dt
    {
            index_send_midi_out[i]=1;
    }


    //trichro wheel
    index_send_midi_out[497]=1;

    //tracking video decay
    index_send_midi_out[498]=1;

    return(0);
}

int reset_window_opened_indexes()
{
    for(int i=0; i<63; i++)
    {
        temp_report_window[i]=0;
        window_opened[i]=0;
    }
    return(0);
}












int constrain_banger_type(int lp)
{
//famille categorie banger
    if(bangers_type[index_banger_selected][lp]>19)
    {
        bangers_type[index_banger_selected][lp]=0;
    }
    return(0);
}

int constrain_banger_param(int lp)
{
    switch (bangers_type[index_banger_selected][lp])
    {
    case 0://rien
        bangers_action[index_banger_selected][lp]=0;
        break;
    case 1://faders
        if(bangers_action[index_banger_selected][lp]>41)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 2://midi send
        if(bangers_action[index_banger_selected][lp]>30)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 3://windows
        if(bangers_action[index_banger_selected][lp]>18)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 4://alarmes
        if(index_type==1 && index_enable_edit_banger==1)
        {
            for(int tt=0; tt<24; tt++)
            {
                string_alarm[index_banger_selected][tt]=numeric[tt];
            }
            string_alarm[index_banger_selected][24]='\0';
            reset_numeric_entry();
            numeric_postext=0;
            sprintf(string_Last_Order,">>GIVED NAME ALARM FOR BANGER %d ",index_banger_selected+1);
        }
        break;
    case 5://audio
        if(bangers_action[index_banger_selected][lp]>15)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 6: //sequenciel
        if(bangers_action[index_banger_selected][lp]>8)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 7://chaser window
        if(bangers_action[index_banger_selected][lp]>16)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 8://minifaders
        if(bangers_action[index_banger_selected][lp]>17)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 9://icat
        if(bangers_action[index_banger_selected][lp]>4)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 10://chrono
        if(bangers_action[index_banger_selected][lp]>2)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 11://set channel
        if(bangers_action[index_banger_selected][lp]>15)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 12://set banger
        if(bangers_action[index_banger_selected][lp]>3)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 13://midi mute
        if(bangers_action[index_banger_selected][lp]>9)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 14://grid
        if(bangers_action[index_banger_selected][lp]>23)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 15://hardware
        if(bangers_action[index_banger_selected][lp]>3)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 16://emulate kbd
        if(bangers_action[index_banger_selected][lp]>62)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 17://draw
        if(bangers_action[index_banger_selected][lp]>10)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 18://echo
        if(bangers_action[index_banger_selected][lp]>25)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    case 19://wave
        if(bangers_action[index_banger_selected][lp]>12)
        {
            bangers_action[index_banger_selected][lp]=0;
        }
        break;
    default:
    break;
    }

    return(0);
}

int reset_banger_params( int banger_selected, int event)
{
//bangers_params[banger_selected][ event][0]=0;//0 param1 pas reseté pour garder le fader
    bangers_params[banger_selected][ event][1]=0;//1 param2
    bangers_delay[banger_selected][ event]=0.0;//delays
    return(0);
}

int reset_banger_event( int banger_selected, int event)
{
    bangers_action[banger_selected][ event]=0;
    reset_banger_params(banger_selected,event);
    return(0);
}


int reset_audio_indexs_to_dock()
{
    index_affect_audio_to_dock=0;
    player_to_affect_to_dock=999;
    audio_type_for_dock_affectation_is=999;
    return(0);
}



bool set_all_saves_indexes_at(bool val)
{
    for (int i=0; i<72; i++)
    {
        specify_who_to_save_load[i]=val;
    }
    return(0);
}

int reset_modified_levels_in_crossfade()
{
    for(int i=0; i<513; i++)
    {
        channel_level_mofification_while_crossfade[i]=0;
    }
    return(0);
}

int exclude_reinclude_channels_from_grand_master_action()
{
    for (int i=1; i<513; i++)
    {
        if(Selected_Channel[i]==1)
        {
            Channels_excluded_from_grand_master[i]=toggle(Channels_excluded_from_grand_master[i]);
        }
    }
    return(0);
}




int set_new_time_in_tap_tempo()
{
    if(index_recording_tap_tempo==1)
    {
        nbr_steps_tempo++;

        if(nbr_steps_tempo>max_temp_tempo)
        {
            start_tempo_ticks=actual_time-ticks_tap_tempo[max_temp_tempo];
            nbr_steps_tempo=1;
            tempo_interm=0;
        }

        ticks_tap_tempo[nbr_steps_tempo]=actual_time-start_tempo_ticks;

        start_tempo_ticks=actual_time;//report de l'actuel temps

        tempo_interm+=ticks_tap_tempo[nbr_steps_tempo];

        tap_tempo_average=(((float)(tempo_interm))/nbr_steps_tempo) /BPS_RATE;

        sprintf(string_tap_tempo_average,"Step: %d  Global: %.2f",nbr_steps_tempo,tap_tempo_average);
        sprintf(string_actual_tap_tempo,"Last:%.2f",((float)ticks_tap_tempo[nbr_steps_tempo])/BPS_RATE);
        do_light_tap_tempo=1;
    }
    return(0);
}

int refresh_hauteur_fenetre_grider()
{
    index_nbre_griderplayers_visibles=0;
    for(int yo=0; yo<core_user_define_nb_gridplayers; yo++)
    {
        if(index_show_grid_player[yo]==1)
        {
            index_nbre_griderplayers_visibles++;
        }
    }
    switch(show_global_view_grider)
    {
    case 0:
        hauteurGlobalGridviewer=0;
        break;
    case 1:
        hauteurGlobalGridviewer=100+(grider_nb_row*size_preview_case);
        break;
    default:
    break;
    }
    if(grider_nb_row>=10)
    {
        grider_facteur_hauteur=grider_nb_row;
    }
    else
    {
        grider_facteur_hauteur=10;
    }
    hauteurGrider=50+(index_nbre_griderplayers_visibles*(60+(grider_facteur_hauteur*size_grille)))+hauteurGlobalGridviewer;
    return(0);
}

int reset_window_positions()
{
    x_mainmenu=300;
    y_mainmenu=200;
    xpatch_window=500;
    ypatch_window=200;
    xtime_window=100;
    ytime_window=200;
    xseq_window=500;
    yseq_window=200;
    xtrichro_window=600;
    ytrichro_window=200;
    xnum_window=300;
    ynum_window=200;
    videoX=600;
    videoY=200;
    YFader=500;
    XAudio=100;
    YAudio=200;
    XConfirm=300;
    YConfirm=300;
    window_focus_id=0;//config par defaut la roue de culeur
    window_cfgX=100;
    window_cfgY=200;
    Xwizard=100;
    Ywizard=200;
    xMinifaders=600;
    yMinifaders=200;
    Xlistproj=300;
    Ylistproj=200;
    Xchasers=100;
    Ychasers=200;
    xmover_window=100;
    ymover_window=200;
    X_gui_iCat= 300 ;
    Y_gui_iCat= 200 ;
    grider_window_x=200;
    grider_window_y=200;
    x_plot=100;
    y_plot=200;
    x_Wdraw=100;
    y_Wdraw=200;
    x_echo=100;
    y_echo=200;
    return(0);
}



int Get_channels_from_memory(int the_mem)
{
    for(int p=1; p<513; p++)
    {
        if (Selected_Channel[p]==1)
        {
            switch(index_blind)
            {
            case 0:
                bufferSaisie[p]=Memoires[the_mem][p];
                break;
            case 1:
                bufferBlind[p]=Memoires[the_mem][p];
                break;
            default:
            break;
            }
        }
    }
//sab 02/03/2014 sprintf(numeric,"");
    strcpy(numeric,"");
    numeric_postext=0;
    sprintf(string_Last_Order,"Got selected channel from %d.%d",the_mem/10,the_mem%10);
    return(0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int search_and_desaffect_previous_midi_signal(int typaction)
{

    if (typaction==1)//1/1
    {
        for (int i=0; i<3072; i++)
        {
            if (miditable[0][i]==istyp && miditable[1][i]==ischan && miditable[2][i]==ispitch) //0.8.2.2
            {
                miditable[0][i]=999;
                miditable[1][i]=999;
                miditable[2][i]=999;
                midi_launchpad_state[i]=0;

            }
        }
    }
// 8 en ordre numérique
    else if(typaction==2 )
    {
        switch(toggle_numerical_midi_way)
        {
        case 0:
            for(int h=0; h<8; h++)
            {
                for (int i=0; i<3072; i++)
                {
                    if (miditable[0][i]==istyp && miditable[1][i]==ischan && miditable[2][i]==ispitch+h)
                    {
                        miditable[0][i]=999;
                        miditable[1][i]=999;
                        miditable[2][i]=999;
                        midi_launchpad_state[i]=0;
                    }
                }
            }
            break;
// 8 en ordre channel
        case 1:
            for(int h=0; h<8; h++)
            {
                for (int i=0; i<3072; i++)
                {
                    if (miditable[0][i]==istyp && miditable[1][i]==ischan+h && miditable[2][i]==ispitch)

                    {
                        miditable[0][i]=999;
                        miditable[1][i]=999;
                        miditable[2][i]=999;
                        midi_launchpad_state[i]=0;
                    }
                }
            }
            break;
        default:
        break;
        }
    }


    return(0);
}


int reset_index_affect_midi()
{
    Midi_Faders_Affectation_Type=0;
    return(0);
}

//sab 02/03/2014 int show_type_midi(int control, char *command)
void show_type_midi(int control, const std::string command)
{

    switch(miditable[0][control])
    {
//midi report
    case 0:
        sprintf(thetypinfo,"Note");
        break;
    case 1:
        sprintf(thetypinfo,"K.On");
        break;
    case 2:
        sprintf(thetypinfo,"K.Off");
        break;
    case 4:
        sprintf(thetypinfo,"C.Change");
        break;
    default:
//sab 02/03/2014 sprintf(thetypinfo,"");
        strcpy(thetypinfo,"");
        break;
    }
    sprintf(string_last_midi_id,"%s selected is Ch: %d Pitch: %d Typ: %s" ,command.c_str(), miditable[1][control],miditable[2][control],thetypinfo);
    sprintf(string_shortview_midi,"%s %d/%d",thetypinfo ,miditable[1][control],miditable[2][control]);
//sab 02/03/2014     return(0);
}



int attribute_midi_to_control(int faderis, int typaction, int modeaction)
{

    if(index_midi_auto_desaffect==1)
    {
        search_and_desaffect_previous_midi_signal(typaction);   //bug desaffectation
    }
//////////////////////////////////////
    if(modeaction==1)//reset
    {
        istyp=999;
        ischan=999;
        ispitch=999;
        modeaction=0;
    }

    if(modeaction==2)//generated fake midi
    {
        istyp=fakemiditype;
        ischan=fakemidichan;
        ispitch=fakemidipitch;
        modeaction=0;
    }
////////////////////////////////////

    if(typaction==1 )//1/1
    {
        if(ischan<16 && ispitch<128)
        {
            miditable[0][faderis]=istyp;
            miditable[1][faderis]=ischan;
            miditable[2][faderis]=ispitch;
        }
    }

    if(typaction==2)//1/8
    {
        if(ischan<16 && ispitch<128)
        {
            switch(toggle_numerical_midi_way)//numeric pitch
            {
            case 0:
                for(int h=0; h<8; h++)
                {
                    miditable[0][faderis+h]=istyp;
                    miditable[1][faderis+h]=ischan;
                    miditable[2][faderis+h]=ispitch+h;
                }
                break;
            case 1: //numeric channel
                for(int h=0; h<8; h++)
                {
                    miditable[0][faderis+h]=istyp;
                    miditable[1][faderis+h]=ischan+h;
                    miditable[2][faderis+h]=ispitch;
                }
                break;
            default:break;
            }
        }
    }

//midi affect auto close
if( index_midi_affectation_autoclose==1)
    {Midi_Faders_Affectation_Type=0;}


    return(0);
}

int attribute_midi_solo_affectation(int faderis, int modeaction)
{

    if(index_midi_auto_desaffect==1)
    {
        search_and_desaffect_previous_midi_signal(1);   //bug desaffectation
    }


    if(Midi_Faders_Affectation_Mode==1)//reset
    {
        istyp=999;
        ischan=999;
        ispitch=999;
        Midi_Faders_Affectation_Mode=0;//modeaction=0;
    }
    else if(Midi_Faders_Affectation_Mode==2)//generated fake midi
    {
        if(ischan<16 && ispitch<128)
        {
            istyp=fakemiditype;
            ischan=fakemidichan;
            ispitch=fakemidipitch;
            Midi_Faders_Affectation_Mode=0;//modeaction=0;
        }
    }

    if(ischan<16 && ispitch<128)
    {
        miditable[0][faderis]=istyp;
        miditable[1][faderis]=ischan;
        miditable[2][faderis]=ispitch;
//modeaction=0;
    }

//midi affect auto close
if( index_midi_affectation_autoclose==1)
    {Midi_Faders_Affectation_Type=0;}

    return(0);
}





int process_assign_to_core(int coreis)
{
    char tmpmondirectory[200];
    get_executable_name(tmpmondirectory,sizeof(mondirectory)); //recup du path complet
    char nom_exe[200];
    sprintf(nom_exe, get_filename(tmpmondirectory));//recup du nom de l exe
    char tmp_order_call[512];
    sprintf(tmp_order_call,"%s\\utils\\Process.exe %s -a %d", mondirectory, nom_exe, coreis);
    system(tmp_order_call);//lancement system
    sprintf(string_Last_Order,">>Assigned %s to Core %d", nom_exe, coreis);
    return(0);
}



int reset_and_recall_iCat_images()
{
    if (enable_iCat==1 && iCat_serveur_is_initialized==1)
    {

        nbrbytessendediCat=sendto(sockiCat, "clearmodels",sizeof("clearmodels"),0,(SOCKADDR*)&siniCat,sinsizeiCat);
//effacage total
        nbrbytessendediCat=sendto(sockiCat, "clearimagecache",sizeof("clearimagecache"),0,(SOCKADDR*)&siniCat,sinsizeiCat);

        char name_library[128][25];
//init tableau noms fichiers
        sprintf(name_library[0],"lfo_up_off.jpg");
        sprintf(name_library[1],"lfo_up_on.jpg");
        sprintf(name_library[2],"lfo_down_off.jpg");
        sprintf(name_library[3],"lfo_down_on.jpg");
        sprintf(name_library[4],"lfo_saw_off.jpg");
        sprintf(name_library[5],"lfo_saw_on.jpg");
        sprintf(name_library[6],"lfo_prev_off.jpg");
        sprintf(name_library[7],"lfo_prev_on.jpg");
        sprintf(name_library[8],"lfo_next_off.jpg");
        sprintf(name_library[9],"lfo_next_on.jpg");
        sprintf(name_library[10],"lfo_ar_off.jpg");
        sprintf(name_library[11],"lfo_ar_on.jpg");
        sprintf(name_library[12],"lock_off.jpg");
        sprintf(name_library[13],"lock_on.jpg");
        sprintf(name_library[14],"lfo_flash_off.jpg");
        sprintf(name_library[15],"lfo_flash_on.jpg");
        sprintf(name_library[16],"play_off.jpg");
        sprintf(name_library[17],"play_on.jpg");
        sprintf(name_library[18],"loop_off.jpg");
        sprintf(name_library[19],"loop_on.jpg");
        sprintf(name_library[20],"loopall_off.jpg");
        sprintf(name_library[21],"loopall_on.jpg");
        sprintf(name_library[22],"seek_off.jpg");

        sprintf(name_library[23],"autogo_view.jpg");
//minifaders
        sprintf(name_library[24],"bt_dockminus.jpg");
        sprintf(name_library[25],"bt_dockplus.jpg");
        sprintf(name_library[26],"at_zero.jpg");
        sprintf(name_library[27],"mf_setpos.jpg");
        sprintf(name_library[28],"bt_carre_vide.png");
        sprintf(name_library[29],"mf_bt_carre_vide.png");
        sprintf(name_library[30],"mf_lfo_up_off.jpg");
        sprintf(name_library[31],"mf_lfo_up_on.jpg");
        sprintf(name_library[32],"mf_lfo_down_off.jpg");
        sprintf(name_library[33],"mf_lfo_down_on.jpg");
        sprintf(name_library[34],"mf_lfo_saw_off.jpg");
        sprintf(name_library[35],"mf_lfo_saw_on.jpg");
        sprintf(name_library[36],"mf_lfo_prev_off.jpg");
        sprintf(name_library[37],"mf_lfo_prev_on.jpg");
        sprintf(name_library[38],"mf_lfo_next_off.jpg");
        sprintf(name_library[39],"mf_lfo_next_on.jpg");
        sprintf(name_library[40],"mf_lfo_ar_off.jpg");
        sprintf(name_library[41],"mf_lfo_ar_on.jpg");
        sprintf(name_library[42],"mf_lock_off.jpg");
        sprintf(name_library[43],"mf_lock_on.jpg");
        sprintf(name_library[44],"mf_lfo_flash_off.jpg");
        sprintf(name_library[45],"mf_lfo_flash_on.jpg");
        sprintf(name_library[46],"mf_play_off.jpg");
        sprintf(name_library[47],"mf_play_on.jpg");
        sprintf(name_library[48],"mf_loop_off.jpg");
        sprintf(name_library[49],"mf_loop_on.jpg");
        sprintf(name_library[50],"mf_loopall_off.jpg");
        sprintf(name_library[51],"mf_loopall_on.jpg");
        sprintf(name_library[52],"mf_seek_off.jpg");
        sprintf(name_library[53],"mf_lck_pst.png");
        sprintf(name_library[54],"mf_sel_pst.png");


//sequences
        sprintf(name_library[55],"button.jpg");
        sprintf(name_library[56],"jump_off.jpg");

        sprintf(name_library[57],"go_off.jpg");
        sprintf(name_library[58],"go_on.jpg");
        sprintf(name_library[59],"goback_off.jpg");
        sprintf(name_library[60],"goback_on.jpg");
        sprintf(name_library[61],"go_on.jpg");


        sprintf(name_library[62],"bt_iCat.png");
        sprintf(name_library[63],"rond_off.jpg");
        sprintf(name_library[64],"rond_on.jpg");
        sprintf(name_library[65],"rond_banger_off.png");
        sprintf(name_library[66],"rond_banger_on.png");

        sprintf(name_library[67],"draw_point.jpg");
        sprintf(name_library[68],"draw_line.jpg");
        sprintf(name_library[69],"draw_cross.jpg");
        sprintf(name_library[70],"draw_cross_ex.jpg");
        sprintf(name_library[71],"draw_trian_plain.jpg");
        sprintf(name_library[72],"draw_trian_outl.jpg");
        sprintf(name_library[73],"draw_circle_plain.jpg");
        sprintf(name_library[74],"draw_circle_outl.jpg");
        sprintf(name_library[75],"draw_square_plain.jpg");
        sprintf(name_library[76],"draw_square_outl.jpg");
        sprintf(name_library[77],"draw_rect_plain.jpg");
        sprintf(name_library[78],"draw_rect_outl.jpg");
        sprintf(name_library[79],"draw_mode_draw.jpg");
        sprintf(name_library[80],"draw_mode_erase.jpg");
        sprintf(name_library[81],"draw_mode_solo.jpg");
        sprintf(name_library[82],"draw_mode_ghost.jpg");

        sprintf(name_library[83],"draw_preset_selected.png");
        sprintf(name_library[84],"draw_preset_vide.png");

        sprintf(name_library[85],"finished");

//boutons
        for(int loopi=0; loopi<85; loopi++)
        {
            sprintf(StrOrderToiCat,"model button%d image http://www.le-chat-noir-numerique.fr/iCat/%s",loopi,name_library[loopi]);
            nbrbytessendediCat=sendto(sockiCat, StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
//rest(10);
        }

        sprintf(StrOrderToiCat,"model slider0d image http://www.le-chat-noir-numerique.fr/iCat/slider.jpg");
        nbrbytessendediCat=sendto(sockiCat, StrOrderToiCat,strlen(StrOrderToiCat)+1,0,(SOCKADDR*)&siniCat,sinsizeiCat);
        //fin confition enbabled and initiated

        nbrbytessendediCat=sendto(sockiCat, "opengl 1",sizeof("opengl 0"),0,(SOCKADDR*)&siniCat,sinsizeiCat);
        nbrbytessendediCat=sendto(sockiCat, "opengl 1",sizeof("opengl 1"),0,(SOCKADDR*)&siniCat,sinsizeiCat);

    }
    return(0);
}


int copy_iCatPage(int pagesource, int pagedest)
{
    iCat_preset_orientation[pagedest]=iCat_preset_orientation[pagesource];

//sliders
    iCat_nbre_de_sliders[pagedest]=iCat_nbre_de_sliders[pagesource];
    for(int i=0; i<24; i++)
    {
        iCat_pos_slider[pagedest][i][0]=iCat_pos_slider[pagesource][i][0];
        iCat_pos_slider[pagedest][i][1]=iCat_pos_slider[pagesource][i][1];
        iCat_orientation_slider[pagedest][i]=iCat_orientation_slider[pagesource][i];
        iCat_affectation_slider_type_is[pagedest][i]=iCat_affectation_slider_type_is[pagesource][i];
        iCat_affectation_slider_value_is[pagedest][i]=iCat_affectation_slider_value_is[pagesource][i];
        ratio_iCat_slider[pagedest][i]=ratio_iCat_slider[pagesource][i];
    }

    iCat_nbre_de_boutons[pagedest]=iCat_nbre_de_boutons[pagesource];
    for(int nbl=0; nbl<48; nbl++)
    {
        iCat_pos_bouton[pagedest][nbl][0]=iCat_pos_bouton[pagesource][nbl][0];
        iCat_pos_bouton[pagedest][nbl][1]=iCat_pos_bouton[pagesource][nbl][1];
        iCat_affectation_bouton_type_is[pagedest][nbl]=iCat_affectation_bouton_type_is[pagesource][nbl];
        iCat_affectation_bouton_action_is[pagedest][nbl]=iCat_affectation_bouton_action_is[pagesource][nbl];
        iCat_affectation_bouton_value_is[pagedest][nbl]=iCat_affectation_bouton_value_is[pagesource][nbl];
        ratio_iCat_button[pagedest][nbl]=ratio_iCat_button[pagesource][nbl];//multiplicateur des proportions de s boutons. 1 / 2 / 3
    }


    iCat_nbre_de_strings[pagedest]=iCat_nbre_de_strings[pagesource];
    for(int nbl=0; nbl<24; nbl++)
    {
        iCat_pos_string[pagedest][nbl][0]=iCat_pos_string[pagesource][nbl][0];
        iCat_pos_string[pagedest][nbl][1]=iCat_pos_string[pagesource][nbl][1];
        iCat_affectation_string_type_is[pagedest][nbl]=iCat_affectation_string_type_is[pagesource][nbl];
        iCat_affectation_string_action_is[pagedest][nbl]=iCat_affectation_string_action_is[pagesource][nbl];
        ratio_iCat_string[pagedest][nbl]=ratio_iCat_string[pagesource][nbl];//multiplicateur des proportions de s boutons. 1 / 2 / 3
    }

    iCat_nbre_de_tracking_zone[pagedest]=iCat_nbre_de_tracking_zone[pagesource];
    for(int nbl=0; nbl<4; nbl++)
    {
        iCat_pos_trackzone[pagedest][nbl][0]=iCat_pos_trackzone[pagesource][nbl][0];
        iCat_pos_trackzone[pagedest][nbl][1]=iCat_pos_trackzone[pagesource][nbl][1];
        iCat_trackzone_type_is[pagedest][nbl]=iCat_trackzone_type_is[pagesource][nbl];
        iCat_trackzone_type_is[pagedest][nbl]=iCat_trackzone_type_is[pagesource][nbl];
        iCat_trackzone_affectation_is[pagedest][nbl]=iCat_trackzone_affectation_is[pagesource][nbl];
        iCat_trackzone_affectation_is[pagedest][nbl]=iCat_trackzone_affectation_is[pagesource][nbl];
        iCat_affectation_string_action_is[pagedest][nbl]=iCat_affectation_string_action_is[pagesource][nbl];
        ratio_iCat_trackzone[pagedest][nbl]=ratio_iCat_trackzone[pagesource][nbl];//multiplicateur des proportions de s boutons. 1 / 2 / 3
    }



    iCat_select_editing_button=0;
    iCat_select_editing_slider=0;
    iCat_select_editing_string=0;
    iCat_select_tracking_zone=0;

    sprintf(string_Last_Order,"Copied iCat page %d in page %d",pagesource+1, pagedest+1);
    index_icat_copyPage=0;

    return(0);
}

int clear_iCat_sliders( int preset_page_iCat)
{
//sliders
    iCat_nbre_de_sliders[preset_page_iCat]=0;
    for(int i=0; i<max_sliders_icat; i++)
    {
        iCat_pos_slider[preset_page_iCat][i][0]=0;
        iCat_pos_slider[preset_page_iCat][i][1]=0;
        iCat_orientation_slider[preset_page_iCat][i]=0;
        iCat_affectation_slider_type_is[preset_page_iCat][i]=0;
        iCat_affectation_slider_value_is[preset_page_iCat][i]=0;
        ratio_iCat_slider[preset_page_iCat][i]=2;
        slider_is_touched[preset_page_iCat][i]=0;
        before_slider_is_touched[preset_page_iCat][i]=0;
        slider_is_controlled_by_point[preset_page_iCat][i]=0;
        level_from_touch[preset_page_iCat][i]=0;
    }
    iCat_select_editing_slider=0;
    return(0);
}

int clear_iCat_buttons( int preset_page_iCat)
{

    iCat_nbre_de_boutons[preset_page_iCat]=0;
    for(int nbl=0; nbl<max_buttons_icat; nbl++)
    {
        iCat_pos_bouton[preset_page_iCat][nbl][0]=0;
        iCat_pos_bouton[preset_page_iCat][nbl][1]=0;
        iCat_affectation_bouton_type_is[preset_page_iCat][nbl]=0;//type 1 faders, 2 sequentiel, 3 audio family
        iCat_affectation_bouton_action_is[preset_page_iCat][nbl]=0;//sous famille, les actions
        iCat_affectation_bouton_value_is[preset_page_iCat][nbl]=0;//valeur de la famille 1/48 stage/preset/accel
        ratio_iCat_button[preset_page_iCat][nbl]=2;//multiplicateur des proportions de s boutons. 1 / 2 / 3
    }
    iCat_select_editing_button=0;
    return(0);
}

int clear_iCat_strings( int preset_page_iCat)
{
    iCat_nbre_de_strings[preset_page_iCat]=0;
    for(int nbl=0; nbl<max_string_icat; nbl++)
    {
        iCat_pos_string[preset_page_iCat][nbl][0]=0;
        iCat_pos_string[preset_page_iCat][nbl][1]=0;
        iCat_affectation_string_type_is[preset_page_iCat][nbl]=0;//type 1 faders, 2 sequentiel, 3 audio family
        iCat_affectation_string_action_is[preset_page_iCat][nbl]=0;//sous famille, les actions
        ratio_iCat_string[preset_page_iCat][nbl]=2;//multiplicateur des proportions de s boutons. 1 / 2 / 3
    }
    iCat_select_editing_string=0;
    return(0);
}


int clear_iCat_trackingzone(int preset_page_iCat)
{
    iCat_nbre_de_tracking_zone[preset_page_iCat]=0;
    for(int nbl=0; nbl<max_zones_icat; nbl++)
    {
        iCat_pos_trackzone[preset_page_iCat][nbl][0]=0;
        iCat_pos_trackzone[preset_page_iCat][nbl][1]=0;
        iCat_trackzone_type_is[preset_page_iCat][nbl]=0;
        iCat_trackzone_affectation_is[preset_page_iCat][nbl]=0;
        iCat_affectation_string_action_is[preset_page_iCat][nbl]=0;
        ratio_iCat_trackzone[preset_page_iCat][nbl]=0;//multiplicateur des proportions de s boutons. 1 / 2 / 3
    }

    iCat_select_tracking_zone=0;

    return(0);
}

int clear_iCat_page ( int preset_page_iCat)
{
    clear_iCat_sliders( preset_page_iCat);
    clear_iCat_buttons( preset_page_iCat);
    clear_iCat_strings( preset_page_iCat);
    clear_iCat_trackingzone( preset_page_iCat);



    sprintf(string_Last_Order,"Cleared iCat page %d",preset_page_iCat+1);
    do_send_icat_init_page=1;
    return(0);
}



int detect_actual_master_lock_is()
{
    for(int u=0; u<core_user_define_nb_faders; u++)
    {
        if(LockFader_is_FullLevel[u]==1)
        {
            actual_master_lock=u;
            break;
        }
    }
    return(0);
}



//sab 02/03/2014 int save_load_print_to_screen(char string_print_to_screen[64])
void save_load_print_to_screen(const std::string label)
{
    const std::string string_print_to_screen = label.substr (0,64);

    if(index_do_quick_save==0)
    {
        show_title();
    }
    Rect nameAera( Vec2D( ((largeur_ecran/2)-200),((hauteur_ecran/2)-100)), Vec2D ( 400,70));
    nameAera.SetRoundness(15);
    nameAera.SetLineWidth(epaisseur_ligne_fader*3);
    nameAera.Draw(CouleurSurvol);
    nameAera.DrawOutline(CouleurLigne);
    neuro.Print(string_print_to_screen,((largeur_ecran/2)-150),((hauteur_ecran/2)-60));

    write_text_to_log_file("");
    write_text_to_log_file(string_print_to_screen);
    write_text_to_log_file(rep);
    Canvas::Refresh();
}

int minifader_selection_record(int mf_preset_is)
{
    for(int olp=0; olp<core_user_define_nb_faders; olp++)
    {
        minifaders_preset_selection[mf_preset_is][olp]=minifaders_selected[olp];
    }
    index_do_dock=0;
    sprintf(string_Last_Order,"Recorded Fader Selection in Preset %d", mf_preset_is+1);
    return(0);
}

int minifader_selection_clear(int mf_preset_is)
{
    for(int olp=0; olp<core_user_define_nb_faders; olp++)
    {
        minifaders_preset_selection[mf_preset_is][olp]=0;
    }
    index_main_clear=0;
    sprintf(string_Last_Order,"Cleared Fader Selection in Preset %d", mf_preset_is+1);
    return(0);
}

int minifader_lockselection_record(int mf_preset_is)
{
    for(int f=0; f<core_user_define_nb_faders; f++)
    {
        FaderLocked_Preset[ mf_preset_is][f]=0;        //reset des états avant stockage
        StateOfFaderBeforeLock_Preset[ mf_preset_is][f]=0;
        LockFader_is_FullLevel_Preset[ mf_preset_is][f]=0;
        if ( FaderLocked[f]==1)
        {
            FaderLocked_Preset[ mf_preset_is][f]=FaderLocked[f];
            StateOfFaderBeforeLock_Preset[ mf_preset_is][f]=StateOfFaderBeforeLock[f];
            LockFader_is_FullLevel_Preset[ mf_preset_is][f]=LockFader_is_FullLevel[f];
        }
    }
//extinction des autres
    for (int ipo=0; ipo<8; ipo++)
    {
        lock_preset[ipo]=0;
    }
    lock_preset[ mf_preset_is]=1;

    index_do_dock=0;
    sprintf(string_Last_Order,">> Lock State %d recorded", mf_preset_is+1);
    return(0);
}



int refresh_stage()
{
    for (int l=1; l<512; l++)
    {
        bufferSaisie[l]=Memoires[position_onstage][l];
    }
    return(0);
}

int reset_indexes_conf()//menu setup cfg
{
    index_config_general=0;
    index_config_dmx=0;
    index_config_midi=0;
    index_config_network=0;
    index_setup_gfx=0;
    index_config_arduino=0;
    index_config_core=0;
    index_affect_dmxin=0;
    Midi_Faders_Affectation_Type=0;//pour ne pas affecter quoi que ce soit en midi
    Midi_Faders_Affectation_Mode=0;
    //do_affectation_on_midi_affect_itself=0;//pour affectation midi on itself
    return(0);
}



int button_midi_out_core(int xmi, int ymi, int control)
{
    if(mouse_x>xmi-10 && mouse_x<xmi+10  && mouse_y>ymi-10 && mouse_y<ymi+10)
    {
        midi_send_out[control]=toggle(midi_send_out[control]);
        mouse_released=1;
    }
    return(0);
}

int button_midi_out_visu(int xmi, int ymi, int control)
{
//midi out enclenché ou pas FADER
    Circle BMidiOut( xmi,ymi, 10);//box du fader
    BMidiOut.SetLineWidth(epaisseur_ligne_fader);

    if(midi_send_out[control]==1)
    {
        BMidiOut.Draw(CouleurBlind);
    }
    BMidiOut.DrawOutline(CouleurLigne.WithAlpha(0.5));

    return(0);
}


int show_who_is_in_dock (int fader, int thedokis)
{
//recherche juste, n' affiche pas
    for(int doloop=1; doloop<514; doloop++)
    {
        if( FaderDockContains[fader][thedokis][doloop]==0)
        {
            show_who_is_in_FADER_DOCK[doloop]=0;
        }
        else if( FaderDockContains[fader][thedokis][doloop]>0)
        {
            show_who_is_in_FADER_DOCK[doloop]=1;
        }
    }

//midi report

    switch (miditable[0][fader])
    {
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
     default:break;
    }

    sprintf(string_last_midi_id,"FADER is Ch: %d Pitch: %d Typ: %s" , miditable[1][fader],miditable[2][fader],thetypinfo);


    if(thedokis==0 || thedokis==1) //up down button
    {

        switch (miditable[0][48+fader+(thedokis*48)])
        {
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
            default: break;
        }

        sprintf(string_last_midi_id,"DOCK is Ch: %d Pitch: %d Type: %s", miditable[1][48+fader+(thedokis*48)],miditable[2][48+fader+(thedokis*48)],thetypinfo);
    }

    sprintf(string_last_over_dock,">>Last Over Dock: Fader %d Dock %d", fader+1,thedokis+1);
    over_fader=fader;
    over_dock=thedokis;

    return(0);
}


int reset_check_grada_overide_dimmers()
{
    for (int i=0; i<513; i++)
    {
        patch_overide[i]=0;
    }
    return(0);
}

int reset_all_bangers()//for load show and stop all running bangers
{
    for (int i=0; i<127; i++)
    {
        bang_is_sended[i]=1;//pour ne pas envoyer le banger
        for(int eventnum=0; eventnum<6; eventnum++)
        {
            event_sended[i][eventnum]=0;//reset des envois
        }
    }
    return(0);
}

int reset_save_load_report_string()
{
    for (int o=0; o<255; o++)
    {
        sprintf(string_save_load_report[o],"-");
        b_report_error[o]=0;
    }
    return(0);
}


int scan_audiofolder()
{

    //reset
    for (int o=0; o<128; o++)
    {
//sab 02/03/2014     sprintf(list_audio_files[o],"");
        strcpy(list_audio_files[o],"");
    }
    //detection
    struct al_ffblk f;
    bool isSomeone=0;
    int nrbe_de_fichiers=0;
    sprintf(rep_audio,"%s\\audio\\%s\\",mondirectory,audio_folder);
    chdir(rep_audio);

    if(!al_findfirst("*.*",&f,-1))
    {
        while(!al_findnext(&f))
        {//18/6/2015 correction christoph  unsigned int a
            int f_name_len = strlen(f.name);
            for(int a=0; a< f_name_len; a++)
            {
                //19/12/14 correction christoph ruiserge
                if(f.name[a]=='.' && a<=f_name_len-3)
                {
                    if((f.name[a+1]=='W' &&  f.name[a+2]=='A' &&  f.name[a+3]=='V')
                            ||(f.name[a+1]=='w' &&  f.name[a+2]=='a' &&  f.name[a+3]=='v')
                            ||(f.name[a+1]=='M' &&  f.name[a+2]=='P' &&  f.name[a+3]=='3')
                            ||(f.name[a+1]=='m' &&  f.name[a+2]=='p' &&  f.name[a+3]=='3')
                      )
                    {
                        isSomeone=true;
                        break;
                    }
                    else
                    {
                        isSomeone=false;
                    }
                }
            }
            // we've found a directory!
            if(isSomeone && nrbe_de_fichiers<128)
            {
                sprintf(list_audio_files[nrbe_de_fichiers+1],f.name);
                nrbe_de_fichiers++;
            }
        }
    }
    al_findclose(&f);
    audio_number_total_in_folder=nrbe_de_fichiers;
//REROLL
    sprintf(rep,"%s\\",mondirectory);
    chdir (rep);
    return(0);
}

int snapshot_windows()
{
    recall_windows_focus_id=window_focus_id;
    recall_windows_onoff[1]=index_type;
    recall_windows_onoff[2]=index_list_projecteurs;
    recall_windows_onoff[3]=index_trichro_window;
    recall_windows_onoff[4]=index_visual_pad;
    recall_windows_onoff[5]=index_video_window;
    recall_windows_onoff[6]=index_show_artpoll_reply_content;
    recall_windows_onoff[7]=index_show_faders;
    recall_windows_onoff[8]=index_patch_window;
    recall_windows_onoff[9]=index_time;
    recall_windows_onoff[10]=index_window_sequentiel;
    recall_windows_onoff[11]=index_show_banger_window;
    recall_windows_onoff[12]=index_menu_save;
    recall_windows_onoff[13]=index_grider_window;
    recall_windows_onoff[14]=index_show_minifaders;
    recall_windows_onoff[15]=index_window_chasers;
    recall_windows_onoff[16]=index_plot_window;
    recall_windows_onoff[17]=index_show_main_menu;
    recall_windows_onoff[18]=index_show_mover_window;
    recall_windows_onoff[19]=index_window_gui_iCat;
    recall_windows_onoff[20]=index_show_echo_window;
    recall_windows_onoff[21]=index_show_audio_window;
    recall_windows_onoff[22]=index_show_config_window;
    recall_windows_onoff[23]=index_show_wizard_window;





    return(0);
}

int close_all_windows()
{
    index_type=0;
    index_list_projecteurs=0;
    index_trichro_window=0;
    index_visual_pad=0;
    index_video_window=0;
    index_show_artpoll_reply_content=0;
    index_list_pro_devices=0;
    index_patch_window=0;
    index_time=0;
    index_window_sequentiel=0;
    index_show_banger_window=0;
    index_menu_save=0;
    index_show_faders=0;
    index_show_minifaders=0;
    index_window_chasers=0;
    index_grider_window=0;
    index_plot_window=0;
    index_show_main_menu=0;
    index_show_mover_window=0;
    index_show_echo_window=0;
    index_show_audio_window=0;
    index_show_config_window=0;
    index_show_wizard_window=0;
    index_window_gui_iCat=0;
    index_my_window=0;//sample
    window_focus_id=0;
    return(0);
}

int write_window_indexes_from_list_of_windows()
{
    close_all_windows();
    for(int i=0; i<63; i++)
    {
        switch(window_opened[i])
        {
        case W_SAVEREPORT:
            break;
        case W_TRICHROMY:
            index_trichro_window=1;
            break;
        case W_NUMPAD:
            index_visual_pad=1;
            break;
        case W_TRACKINGVIDEO:
            index_video_window=1;
            break;
        case W_ARTPOLLREPLY:
            index_show_artpoll_reply_content=1;
            break;
        case W_FADERS :
            index_show_faders=1;
            break;
        case W_PATCH:
            index_patch_window=1;
            break;
        case W_TIME:
            index_time=1;
            break;
        case W_SEQUENCIEL:
            index_window_sequentiel=1;
            break;
        case W_ASKCONFIRM:
            //nothing
            break;
        case W_PLOT:
            index_plot_window=1;
            break;
        case W_ECHO:
            index_show_echo_window=1;
            break;
        case W_LIST:
            index_list_projecteurs=1;
            break;
        case W_SAVE:
            index_menu_save=1;
            break;
        case W_MAINMENU:
            index_show_main_menu=1;
            break;
        case W_BANGER:
            index_show_banger_window=1;
            break;
        case W_ALARM:
            break;
        case W_AUDIO:
            index_show_audio_window=1;
            break;
        case W_CFGMENU:
            index_show_config_window=1;
            break;
        case W_WIZARD:
            index_show_wizard_window=1;
            break;
        case W_MINIFADERS:
            index_show_minifaders=1;
            break;
        case W_CHASERS:
            index_window_chasers=1;
            break;
        case W_MOVER:
            index_show_mover_window=1;
            break;
        case W_iCAT:
            index_window_gui_iCat=1;
            break;
        case W_GRID:
            index_grider_window=1;
            break;
        case W_MY_WINDOW:
            index_my_window=1;
            break;
        default:
            break;
        }
    }
    return(0);
}



int rafraichissement_clockwheel()
{

   clock_vx = cos(angle_snap_clock)* rayon_wheel_level;
   clock_vy = sin(angle_snap_clock)* rayon_wheel_level;
   position_curseur_clock_x= window_cfgX+770+clock_vx;
   position_curseur_clock_y=window_cfgY+115+clock_vy ;


return(0);
}

int recall_windows()
{
    window_focus_id=recall_windows_focus_id;
    index_type=recall_windows_onoff[1];
    index_list_projecteurs=recall_windows_onoff[2];
    index_trichro_window=recall_windows_onoff[3];
    index_visual_pad=recall_windows_onoff[4];
    index_video_window=recall_windows_onoff[5];
    index_show_artpoll_reply_content=recall_windows_onoff[6];
    index_show_faders=recall_windows_onoff[7];
    index_patch_window=recall_windows_onoff[8];
    index_time=recall_windows_onoff[9];
    index_window_sequentiel=recall_windows_onoff[10];
    index_show_banger_window=recall_windows_onoff[11];
    index_menu_save=recall_windows_onoff[12];
    index_grider_window=recall_windows_onoff[13];
    index_show_minifaders=recall_windows_onoff[14];
    index_window_chasers=recall_windows_onoff[15];
    index_plot_window=recall_windows_onoff[16];
    index_show_main_menu=recall_windows_onoff[17];
    index_show_mover_window=recall_windows_onoff[18];
    index_show_echo_window=recall_windows_onoff[20];
    index_show_audio_window=recall_windows_onoff[21];
    index_show_config_window=recall_windows_onoff[22];
    index_show_wizard_window=recall_windows_onoff[23];

    return(0);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////


int refresh_time_cursor()
{
    vtimex = cos(time_angle)*100;//timerayon
    vtimey = sin(time_angle)*100;
    position_curseur_time_x= xtime_window+150+vtimex;
    position_curseur_time_y=ytime_window+150+vtimey ;
    return(0);
}

//fenetre de Time affectation et prise de chrono
int set_time_cursor_to_time_type(int the_time_wheel_datatype)
{
    switch(time_wheel_datatype_is)
    {
    case 0://minutes
        angle_timesnap=angle_timesnap_min;
        break;
    case 1://secondes
        angle_timesnap=angle_timesnap_sec;
        break;
    case 2://dixiemes
        angle_timesnap=angle_timesnap_dix;
        break;
     default:break;
    }
    time_angle=angle_timesnap;
    refresh_time_cursor();

//pb sur les minutes et secondes, ajustage manuel
    if(time_wheel_datatype_is==0) {}
    if(time_wheel_datatype_is==1)
    {
        angle_timesnap_sec+=(5.980005/60/2);
    }
    return(0);
}

int read_time_string_entry()
{
time_minutes=0;
time_secondes=0;
time_centiemes=0;

int position_minutes=0;// dans chaine


char str_tmp[24];
sprintf(str_tmp, numeric);

//lecture d'une chaine minutes / secondes / centiemes ou bien secondes / centiemes
if(numeric[0]!='.')//si la chaine n'est pas des centiemes de secondes)
{
//sortir les minutes
for(int i=0;i<23;i++)
{
if(str_tmp[i]=='.' && str_tmp[i+1]=='.' && numeric[0]!='.')
{
char tmp_tmp[24];
sprintf(tmp_tmp,numeric);
tmp_tmp[i]='\0';
time_minutes=atoi(tmp_tmp);
position_minutes=i+1;
}
}
sprintf(str_tmp,"%s", "");
//expurgation chaine des minutes
for(int i=0;i<(24-position_minutes);i++)
{
str_tmp[i]=numeric[position_minutes+i];
}
//report secondes centiemes
char chaine_multiple[2][8];
char *pch;
pch = strtok (str_tmp,".");
int pass=0;
 while (pch != NULL)
  {
    sprintf(chaine_multiple[pass],pch);
    pch = strtok (NULL, ".");
    pass++;
  }

time_secondes=atoi(chaine_multiple[0]);
time_centiemes=atoi(chaine_multiple[1]);
}

else if (numeric[0]=='.')//centiemes appelés uniquement
{
char cent_t[4];
for (int i=0;i<4;i++)
{
cent_t[i]=numeric[i+1];
time_centiemes=atoi(cent_t);
}
}

sprintf(string_Last_Order,"Your entry: %d min %d sec %d 1/100", time_minutes, time_secondes, time_centiemes);
reset_numeric_entry();

if(time_minutes>59){time_minutes=59;}
if(time_secondes>59){time_secondes=59;}
if(time_centiemes>99){time_centiemes=99;}

//report des angles popur garder la mesure en fin de chrono.
angle_timesnap_min=((float)(time_minutes)/59)*5.980005;//=(int)((angle_timesnap_min/6.280005)*63);
angle_timesnap_sec=((float)(time_secondes)/59)*5.980005;//=(int)((angle_timesnap_sec/((PI*360) / 180))*63);
angle_timesnap_dix=((float)(time_centiemes)/99)*5.980005;//=(int)((angle_timesnap_dix/6.280005)*10);
//pb sur les minutes et secondes, ajustage manuel
//if(time_wheel_datatype_is==0){angle_timesnap_min+=(5.980005/59/2);}
//if(time_wheel_datatype_is==1){angle_timesnap_sec+=((PI*360) / 180);}

set_time_cursor_to_time_type(time_wheel_datatype_is);

return(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
int reset_midi_receiver_array()
{
    istyp=0;//pour les retorus launchpad !
    ischan=999;
    ispitch=999;

    return(0);
}
//////////////////////////////////////////////////////////////////////////////
int detect_master_lock(int mo)
{


    for(int p=0; p<core_user_define_nb_faders; p++)
    {
        if(LockFader_is_FullLevel_Preset[mo][p]==1)
        {
            master_lock_preset[mo]=p+1;//l info d affichage est mise directement en + 1 pour permettre le 0
//de la desaffectation
            break;
        }
    }

    return(0);
}

int do_lock_preset(int num_preset)
{
    lock_preset[num_preset]=toggle(lock_preset[num_preset]);
    if(lock_preset[num_preset]==1)
    {
        for (int ipo=0; ipo<8; ipo++)
        {
            lock_preset[ipo]=0;
        }
        lock_preset[num_preset]=1;
        for (int f=0; f<core_user_define_nb_faders; f++)
        {
            /*ancienne version: le master fader pas mis à full
            FaderLocked[f]=FaderLocked_Preset[ num_preset][f];
            StateOfFaderBeforeLock[f]=StateOfFaderBeforeLock_Preset[num_preset][f];
            LockFader_is_FullLevel[f]=LockFader_is_FullLevel_Preset[num_preset][f];*/
            if(LockFader_is_FullLevel_Preset[num_preset][f]==1)
            {
                Fader[f]=255;
                midi_levels[f]=127;
                if(midi_send_out[f]==1)
                {
                    index_send_midi_out[f]=1;
                }
                StateOfFaderBeforeLock[f]=255;
            }
            else //rajout 0.7.6
            {
                lfo_cycle_is_on[f]=0;
                lfo_mode_is[f]=0;
            }
            FaderLocked[f]=FaderLocked_Preset[ num_preset][f];
            StateOfFaderBeforeLock[f]=Fader[f];
            LockFader_is_FullLevel[f]=LockFader_is_FullLevel_Preset[num_preset][f];
        }
    }
    else  if(lock_preset[num_preset]==0)
    {
        for (int f=0; f<core_user_define_nb_faders; f++)
        {
            FaderLocked[f]=0;
        }
    }
    return(0);
}

int do_stock_fadersstate(bool fads, bool speeds, bool locks, bool lfos, bool loops)
{
    stockage_all_at_zero_state[0]=fads;
    stockage_all_at_zero_state[1]=speeds;
    stockage_all_at_zero_state[2]=locks;
    stockage_all_at_zero_state[3]=lfos;
    stockage_all_at_zero_state[4]=loops;
//reset  des infos
    for (int pe=0; pe<core_user_define_nb_faders; pe++)
    {
        SnapFader[pe]=0;
        Snaplfo_speed[pe]=64;
        SnapFaderLocked[pe]=0;
        Snaplfo_mode_is[pe]=0;//no lfo
        Snaplfo_cycle_is_on[pe]=0;//saw
        Snaplfo_cycle_steps[pe]=0;
        Snaplfo_do_next_step[pe][0]=0;
        Snaplfo_do_next_step[pe][1]=0;
        for(int d=0; d<core_user_define_nb_docks; d++)
        {
            Snapis_dock_for_lfo_selected[pe][d]=0;
        }
    }

//stockage
    for (int p=0; p<core_user_define_nb_faders; p++)
    {
        if(fads==1)
        {
            SnapFader[p]=Fader[p];
        }
        if(speeds==1)
        {
            Snaplfo_speed[p]=lfo_speed[p];
        }
        if(locks==1)
        {
            SnapFaderLocked[p]=FaderLocked[p];
        }
        if(lfos==1)
        {
            Snaplfo_mode_is[p]=lfo_mode_is[p];//no lfo
            Snaplfo_cycle_is_on[p]=lfo_cycle_is_on[p];//saw
            Snaplfo_cycle_is_on[p]=lfo_cycle_steps[p];
            Snaplfo_do_next_step[p][0]=lfo_do_next_step[p][0];
            Snaplfo_do_next_step[p][1]=lfo_do_next_step[p][1];
        }
        //sab 02/03/2014 ATTENTION CHANGE COMPORTEMENT - COMMENT TESTER ? if(loops=1)
        if(loops==1)
        {
            for(int d=0; d<core_user_define_nb_docks; d++)
            {
                Snapis_dock_for_lfo_selected[p][d]=is_dock_for_lfo_selected[p][d];
            }
        }
    }
    sprintf(string_Last_Order,">>All at Zero: pasted previous state");
    reset_midi_receiver_array();
    return(0);
}


int do_recall_fadersstate(bool fads, bool speeds, bool locks, bool lfos, bool loops)
{
    for (int p=0; p<core_user_define_nb_faders; p++)
    {
        if(minifaders_selected[p]==1)
        {
            if(fads==1)
            {
                fader_set_level(p,SnapFader[p]);
                /*Fader[p]=SnapFader[p];
                midi_levels[p]=(int)((float)(SnapFader[p])/2);
                index_send_midi_out[p]=1;*/
            }
            if(speeds==1)
            {
                lfo_speed[p]=Snaplfo_speed[p];
                midi_levels[196+p]=Snaplfo_speed[p];
                index_send_midi_out[196+p]=1;
            }
            if(locks==1)
            {
                FaderLocked[p]=SnapFaderLocked[p];
            }
            if(lfos==1)
            {
                lfo_mode_is[p]=Snaplfo_mode_is[p];//no lfo
                lfo_cycle_is_on[p]=Snaplfo_cycle_is_on[p];//saw
                lfo_cycle_steps[p]=Snaplfo_cycle_is_on[p];
                lfo_do_next_step[p][0]=Snaplfo_do_next_step[p][0];
                lfo_do_next_step[p][1]=Snaplfo_do_next_step[p][1];
            }
            //sab 02/03/2014 ATTENTION CHANGE COMPORTEMENT - COMMENT TESTER ? if(loops=1)
            if(loops==1)
            {
                for(int d=0; d<core_user_define_nb_docks; d++)
                {
                    is_dock_for_lfo_selected[p][d]=Snapis_dock_for_lfo_selected[p][d];
                }
            }
        }
    }
    sprintf(string_Last_Order,">>All at Zero: recall done");

    stockage_all_at_zero_state[0]=0;
    stockage_all_at_zero_state[1]=0;
    stockage_all_at_zero_state[2]=0;
    stockage_all_at_zero_state[3]=0;
    stockage_all_at_zero_state[4]=0;

    return(0);
}


////////////////////////////////////////////////////////////////////////////////

int dessafect_index_curves()
{
    index_reset_curve=0;
    index_square_curve=0;
    index_fluo_curve=0;
    index_preheat_curve=0;
    return(0);
}

int reconstruct_plot_dimmer_list_from_patch()
{
    for(int c=0; c<4; c++)
    {

        for(int s=1; s<=nbre_symbols_on_plot[c]; s++)
        {
            for(int p=0; p<513; p++)
            {
                if(Patch[p]==symbol_channel_is[c][s])
                {
                    symbol_dimmer_is[c][s]=p;
                }
            }

        }
    }
    return(0);
}

int patch_straight()
{
    for(int i=0; i<513; i++)
    {
        Patch[i]=i;
    }
    if(index_build_patch_from_plot==1)
    {
        reconstruct_plot_dimmer_list_from_patch();
    }
    return(0);
}



int patch_select_all_dimmers()
{
    for(int i=0; i<513; i++)
    {
        Dimmers_selected[i]=1;
    }
    return(0);
}

int  patch_clear_selected()
{
    for(int i=0; i<513; i++)
    {
        if(Dimmers_selected[i]==1)
        {
            Patch[i]=0;
            curves[i]=0;
            if(index_build_patch_from_plot==1)
            {
                for(int c=0; c<4; c++)
                {
                    for(int s=1; s<=nbre_symbols_on_plot[c]; s++)
                    {
                        if(symbol_dimmer_is[c][s]==i)
                        {
                            symbol_dimmer_is[c][s]=0;
                        }
                    }
                }
            }
        }
    }

    return(0);
}




int patch_to_default_selected()
{
    for(int i=0; i<513; i++)
    {
        if(Dimmers_selected[i]==1)
        {
            Patch[i]=i;
            curves[i]=0;
        }
    }
    if(index_build_patch_from_plot==1)
    {
        reconstruct_plot_dimmer_list_from_patch();
    }
    return(0);
}



int set_channel_scroll( int ch)
{
    switch (ClassicalChannelView)
    {
    case 0:
    {
        int pr=check_wich_channel_is_in_view(ch);
        scroll_channelspace=(int)(ratioview*scroll_pos_preset[pr-1]);
        break;
    }
    case 1:
    {
        if(ch>0 && ch<48)
        {
            scroll_channelspace=0;
        }
        else  if(ch>=48 && ch<97)
        {
            scroll_channelspace=23;
        }
        else  if(ch>=97 && ch<145)
        {
            scroll_channelspace=47;
        }
        else  if(ch>=145 && ch<193)
        {
            scroll_channelspace=70;
        }
        else  if(ch>=193 && ch<241)
        {
            scroll_channelspace=95;
        }
        else  if(ch>=241 && ch<289)
        {
            scroll_channelspace=117;
        }
        else  if(ch>=289 && ch<337)
        {
            scroll_channelspace=141;
        }
        else  if(ch>=337 && ch<385)
        {
            scroll_channelspace=163;
        }
        else  if(ch>=385 && ch<433)
        {
            scroll_channelspace=187;
        }
        else  if(ch>=433 && ch<481)
        {
            scroll_channelspace=210;
        }
        else  if(ch>=481)
        {
            scroll_channelspace=236;
        }
        break;
         default:break;
    }
    }
    return(0);
}

int set_patch_scroll( int dim)
{
    if(dim>0 && dim<55)
    {
        scroller_patch=1;
    }
    else  if(dim>=55 && dim<103)
    {
        scroller_patch=22;
    }
    else  if(dim>=103 && dim<151)
    {
        scroller_patch=42;
    }
    else  if(dim>=151 && dim<193)
    {
        scroller_patch=60;
    }
    else  if(dim>=193 && dim<247)
    {
        scroller_patch=78;
    }
    else  if(dim>=247 && dim<295)
    {
        scroller_patch=99;
    }
    else  if(dim>=295 && dim<349)
    {
        scroller_patch=118;
    }
    else  if(dim>=349 && dim<397)
    {
        scroller_patch=140;
    }
    else  if(dim>=397 && dim<445)
    {
        scroller_patch=159;
    }
    else  if(dim>=445 && dim<493)
    {
        scroller_patch=178;
    }
    else  if(dim>=493)
    {
        scroller_patch=198;
    }
    return(0);
}

//les faders reportes dans le tableau midi
int load_Fader_state_to_midi_array()
{
    for(int i=0; i<core_user_define_nb_faders; i++)
    {
//faders
        midi_levels[i]=(Fader[i]/2);
//lfo speed
        midi_levels[i+196]=(lfo_speed[i]);
    }


    return(0);
}


short midi_send_program_change(int lechannel, short prg_)
{
     MidiEvPtr eMid;
    if ((eMid = MidiNewEv(typeProgChange)))
    {
        Port(eMid) = 0;
        Chan(eMid) = lechannel;
        MidiSetField(eMid,0,prg_);
        MidiSendIm(myRefNum, eMid);

    }
    return(0);
}

int send_my_midi_note( int letype,  int lechannel, int lanote, int lavelocite, int laduree)
{
    MidiEvPtr eMid;
    if ((eMid = MidiNewEv(letype)))
    {
        Port(eMid) = 0;
        Chan(eMid) = lechannel;
        Pitch(eMid)= lanote;
        Vel(eMid)  = lavelocite;
        Dur(eMid)= laduree;
        MidiSendIm(myRefNum, eMid);

    }
    return(0);
}

int send_my_midi_note_delayed( int letype,  int lechannel, int lanote, int lavelocite, int laduree, int delay)
{
    MidiEvPtr eMid;
    long  dt = MidiGetTime();
    if ((eMid = MidiNewEv(letype)))
    {
        Port(eMid) = 0;
        Chan(eMid) = lechannel;
        Pitch(eMid)= lanote;
        Vel(eMid)  = lavelocite;
        Dur(eMid)= laduree;
        MidiSendAt(myRefNum, MidiCopyEv(eMid), dt+delay);

    }
    return(0);
}


int send_immidiateley_my_midi_cc( int letype,  int lechannel, int lanote, int lavelocite)
{
    MidiEvPtr eIMid;

    if ((eIMid = MidiNewEv(letype)))
    {
        Port(eIMid) = 0;
        Chan(eIMid) = lechannel;
        Pitch(eIMid)= lanote;
        Vel(eIMid)  = lavelocite;
        //Dur(eIMid)= 10;
        MidiSendIm(myRefNum, eIMid);
    }

    return(0);
}

int midi_send_type_message(int msgmidi)
{
     MidiEvPtr eIMid;
        if ((eIMid = MidiNewEv(msgmidi)))
        {
        Port(eIMid) = 0;
        /*Chan(eIMid) = 0;
        Pitch(eIMid)= 0;
        Vel(eIMid)  = 0;*/
        MidiSendIm(myRefNum, eIMid);
        }
  return(0);
}

int emit_midi_out()
{


//Midi out sur faders
    for(int i=0; i<3072; i++)
    {
        if(midi_send_out[i]==1 && index_send_midi_out[i]==1 )
        {
            if(miditable[0][i]<128 && miditable[1][i]<128 && miditable[2][i]<128)
            {
                send_immidiateley_my_midi_cc(miditable[0][i],miditable[1][i],miditable[2][i],midi_levels[i]);
                index_send_midi_out[i]=0;
            }
        }
    }

return(0);
}

int load_etat_picker_dans_dockcolor(int dcolor_selected )
{
    index_quadri=dock_color_type[dcolor_selected];
    picker_x=x_y_picker_par_colordock[dcolor_selected][0];
    picker_y=x_y_picker_par_colordock[dcolor_selected][1];
    angle_snap=angle_hue_par_colordock[dcolor_selected];

    vx = cos(angle_snap)*125;
    vy = sin(angle_snap)*125;
    position_curseur_hue_x= xtrichro_window+vx;
    position_curseur_hue_y=ytrichro_window+vy ;

    r_pick=picker_trichro[dcolor_selected][0];
    v_pick=picker_trichro[dcolor_selected][1];
    b_pick=picker_trichro[dcolor_selected][2];
    my_yellow=picker_trichro[dcolor_selected][3];
    midi_levels[497]=(int)(angle_snap/((PI*360) / (180*127)));
    if(midi_send_out[497]==1)
    {
        index_send_midi_out[497]=1;
    }
    return(0);
}


int refresh_ocv_settings()
{
//int
    threshold_level=camera_modes_and_settings[ocv_calcul_mode][0];
    erode_level=camera_modes_and_settings[ocv_calcul_mode][1];
    div_facteur=camera_modes_and_settings[ocv_calcul_mode][2];
//booleens
    threshold_on=camera_modes_and_settings[ocv_calcul_mode][8];
    erode_mode=camera_modes_and_settings[ocv_calcul_mode][9];
    blur_on=camera_modes_and_settings[ocv_calcul_mode][10];
    return(0);
}



int refresh_decay()
{
    if(index_decay_tracker<0)
    {
        index_decay_tracker=0;
    }
    else if(index_decay_tracker>127)
    {
        index_decay_tracker=127;
    }
    tracker_decay_constant=(float)(index_decay_tracker)/127;
    return(0);
}


int LoadWhiteCatColorProfil()
{
    if (config_color_style_is==0)//defaut
    {
        CouleurFond=CouleurFondDefaut;
        CouleurLigne=CouleurLigneDefaut;
        CouleurFader=CouleurFaderDefaut;
        CouleurPatch=CouleurPatchDefaut;
        CouleurSurvol=CouleurSurvolDefaut;
        CouleurLevel=CouleurLevelDefaut;
        CouleurSelection=CouleurSelectionDefaut;
        CouleurNiveau=CouleurNiveauDefaut;
        CouleurConfig=CouleurConfigDefaut;
        CouleurBleuProcedure=CouleurBleuProcedureDefaut;
        CouleurBlind=CouleurBlindDefaut;
        CouleurLock=CouleurLockDefaut;
    }
    else if(config_color_style_is==1)//gris classique
    {
        CouleurFond=CouleurGrisClair;
        CouleurLigne=CouleurNoir;
        CouleurFader=CouleurGrisAnthracite;
        CouleurPatch=CouleurNoir;
        CouleurSurvol=CouleurGrisMoyen;
        CouleurLevel=CouleurNoir;
        CouleurSelection=CouleurBlanc;
        CouleurNiveau=CouleurNoir;
        CouleurConfig=CouleurGrisAnthracite;
        CouleurBleuProcedure=CouleurNoir;
        CouleurBlind=Rgba::RED;
        CouleurLock=CouleurBlanc;
        petitchiffre.SetColor(Rgba::BLACK);
        petitpetitchiffre.SetColor(Rgba::BLACK);
        petitchiffrenoir.SetColor(Rgba::WHITE);
        circuitlevel.SetColor(Rgba::WHITE);
        circuitfaderlevel.SetColor(CouleurGrisAnthracite);
    }

    else if(config_color_style_is==2)//bleuté
    {
        CouleurFond=CouleurBleu1;
        CouleurLigne=CouleurBlanc;
        CouleurFader=CouleurBleu6;
        CouleurPatch=CouleurNoir;
        CouleurSurvol=CouleurBleu6;
        CouleurLevel=CouleurBleu4;
        CouleurSelection=CouleurBlanc;
        CouleurNiveau=CouleurBlanc;
        CouleurConfig=CouleurBleu4;
        CouleurBleuProcedure=CouleurBleu2;
        CouleurBlind=Rgba::RED;
        CouleurLock=CouleurBleu8;
    }

    else if(config_color_style_is==3)//dicrete
    {
        CouleurFond=Discrete1;
        CouleurLigne=Discrete2;
        CouleurFader=Discrete3;
        CouleurPatch=Discrete4;
        CouleurSurvol=Discrete5;
        CouleurLevel=Discrete6;
        CouleurSelection=Discrete7;
        CouleurNiveau=Discrete8;
        CouleurConfig=Discrete9;
        CouleurBleuProcedure=Discrete10;
        CouleurBlind=Discrete11;
        CouleurLock=Discrete12;
    }


    else if(config_color_style_is==4)//dmatrix
    {
        CouleurFond=Matrix1;
        CouleurLigne=Matrix2;
        CouleurFader=Matrix3;
        CouleurPatch=Matrix4;
        CouleurSurvol=Matrix5;
        CouleurLevel=Matrix6;
        CouleurSelection=Matrix7;
        CouleurNiveau=Matrix8;
        CouleurConfig=Matrix9;
        CouleurBleuProcedure=Matrix10;
        CouleurBlind=Matrix11;
        CouleurLock=Matrix12;
    }

    else if(config_color_style_is==5)//user
    {
        CouleurFond=CouleurUser1;
        CouleurLigne=CouleurUser2;
        CouleurFader=CouleurUser3;
        CouleurPatch=CouleurUser4;
        CouleurSurvol=CouleurUser5;
        CouleurLevel=CouleurUser6;
        CouleurSelection=CouleurUser7;
        CouleurNiveau=CouleurUser8;
        CouleurConfig=CouleurUser9;
        CouleurBleuProcedure=CouleurUser10;
        CouleurBlind=CouleurUser11;
        CouleurLock=CouleurUser12;
    }
    doom.SetColor( CouleurLigne );
    doomblanc.SetColor( CouleurLigne );
    petitdoomblanc.SetColor( CouleurLigne );
    neuro.SetColor( CouleurLigne );
    neuromoyen.SetColor( CouleurLigne );
    petitchiffre.SetColor( CouleurLigne );
    petitpetitchiffre.SetColor( CouleurLigne );
    neuroTitle.SetColor( CouleurLigne );
    doomrouge.SetColor( CouleurBlind );
    petitpetitchiffrerouge.SetColor( CouleurBlind );
    petitchiffrerouge.SetColor( CouleurBlind );
    circuitblindlevel.SetColor( CouleurBlind );
    circuitlevel.SetColor( CouleurLevel );
    petitchiffrenoir.SetColor( CouleurFond );
    petitdoomInspekt.SetColor( CouleurFader );
    circuitfaderlevel.SetColor( CouleurFader );
    return(0);
}

int record_memory(int mem_is)
{
    for (int u=1; u<514; u++)
    {
        if(index_blind==0)
        {
            Memoires[mem_is][u]=bufferSequenciel[u];
        }
        else if(index_blind==1)
        {
            Memoires[mem_is][u]=bufferBlind[u];
        }
    }
    //christoph 18/07/2015
    unselect_ch_and_symbols();
    ratio_cross_manuel[mem_is]=ratio_X1X2_together;
    return(0);
}


int refresh_mem_onstage(int mem_is)
{
    for (int u=1; u<514; u++)
    {
        bufferSaisie[u]=Memoires[mem_is][u];
    }
    return(0);
}


int record_memory_plus_faders(int mem_is)
{
    if(index_blind==0)
    {

        for (int u=1; u<514; u++)
        {
            if(bufferSequenciel[u] >bufferFaders[u])
            {
                Memoires[mem_is][u]=bufferSequenciel[u];
            }
            if(bufferSequenciel[u] <=bufferFaders[u])
            {
                Memoires[mem_is][u]=bufferFaders[u];
            }
         }
         //christoph 18/07/2015
         unselect_ch_and_symbols();
//refresh stage
        refresh_mem_onstage(mem_is);


        sprintf(string_Last_Order,">>Created mem %.1f from faders and stage ", ((float)mem_is)/10);
    }
    else if(index_blind==1)
    {
        sprintf(string_Last_Order,">>[SHIFT-F3] only for on stage recording");
    }
    ratio_cross_manuel[mem_is]=ratio_X1X2_together;



    return(0);
}

int overrecord_memory_plus_faders(int mem_is)
{
    if(index_blind==0)
    {

        for (int u=1; u<514; u++)
        {
            if(bufferSequenciel[u] >bufferFaders[u])
            {
                Memoires[mem_is][u]=bufferSequenciel[u];
            }
            if(bufferSequenciel[u] <=bufferFaders[u])
            {
                Memoires[mem_is][u]=bufferFaders[u];
            }
        }
        //christoph 18/07/2015
        unselect_ch_and_symbols();


        refresh_mem_onstage(mem_is);
        sprintf(string_Last_Order,">>Over-recorded mem %.1f from faders and stage ", ((float)mem_is)/10);
    }
    else if(index_blind==1)
    {
        sprintf(string_Last_Order,">>[CTRL-F3] only for on stage recording");
    }
    ratio_cross_manuel[mem_is]=ratio_X1X2_together;



    return(0);
}




int snap_mem_to_copy()
{
    CTRLC_mem_to_copy=(int)(atof(numeric)*10.0001);
    sprintf(string_Last_Order,"Mem. To Copy: %d.%d", CTRLC_mem_to_copy/10,CTRLC_mem_to_copy%10);
    reset_numeric_entry();
    return(0);
}

int copy_mem_in(int mem_n)//recopie d une memoire dans l autre
{
    MemoiresExistantes[mem_n]=1;
    for(int i=1; i<513; i++)
    {
        Memoires[mem_n][i]=Memoires[CTRLC_mem_to_copy][i];
    }
    sprintf(descriptif_memoires[mem_n],descriptif_memoires[CTRLC_mem_to_copy]);
    sprintf(annotation_memoires[mem_n],annotation_memoires[CTRLC_mem_to_copy]);
    Times_Memoires[mem_n][0]=Times_Memoires[CTRLC_mem_to_copy][0];
    Times_Memoires[mem_n][1]=Times_Memoires[CTRLC_mem_to_copy][1];
    Times_Memoires[mem_n][2]=Times_Memoires[CTRLC_mem_to_copy][2];
    Times_Memoires[mem_n][3]=Times_Memoires[CTRLC_mem_to_copy][3];
    Links_Memoires[mem_n]=Links_Memoires[CTRLC_mem_to_copy];
    Banger_Memoire[mem_n]=Banger_Memoire[CTRLC_mem_to_copy];
    sprintf(string_Last_Order,"Copyed in Mem. %d.%d Mem. %d.%d", mem_n/10,mem_n%10,CTRLC_mem_to_copy/10,CTRLC_mem_to_copy%10);
//sab 02/03/2014 sprintf(numeric,"");
    strcpy(numeric,"");

    numeric_postext=0;
    return(0);
}











int prepare_crossfade()
{
    if(crossfade_speed<64)
    {
        fraction_X2_in= 255.0/ (Times_Memoires[position_preset][1]*(((float)BPS_RATE)*(64.0/crossfade_speed)));
        fraction_X1_out=  255.0/ (Times_Memoires[position_preset][3]*(((float)BPS_RATE)*(64.0/crossfade_speed)));
        crossfade_time_delay_in=(int)(Times_Memoires[position_preset][0]*(((float)BPS_RATE)*(64.0/crossfade_speed)));
        crossfade_time_delay_out=(int)(Times_Memoires[position_preset][2]*(((float)BPS_RATE)*(64.0/crossfade_speed)));
    }
    else if(crossfade_speed==64)
    {
        fraction_X2_in= 255.0/ (Times_Memoires[position_preset][1]*BPS_RATE);
        fraction_X1_out= 255.0/ (Times_Memoires[position_preset][3]*BPS_RATE);
        crossfade_time_delay_in=(int) (Times_Memoires[position_preset][0]*BPS_RATE);
        crossfade_time_delay_out=(int)(Times_Memoires[position_preset][2]*BPS_RATE);
    }
    else if(crossfade_speed>64)
    {
        fraction_X2_in= 255.0/ ((Times_Memoires[position_preset][1]- ( (Times_Memoires[position_preset][1] /64) * (crossfade_speed-63)))*BPS_RATE); //-62 evite un passage de temps pas bon, cf curseur
        fraction_X1_out=  255.0/ ((Times_Memoires[position_preset][3]- ( (Times_Memoires[position_preset][3] /64) * (crossfade_speed-63)))*BPS_RATE);
        crossfade_time_delay_in= (int) ((Times_Memoires[position_preset][0]- ( (Times_Memoires[position_preset][0] /64) * (crossfade_speed-63)))*BPS_RATE); //-62 evite un passage de temps pas bon, cf curseur
        crossfade_time_delay_out= (int) ((Times_Memoires[position_preset][2]- ( (Times_Memoires[position_preset][2] /64) * (crossfade_speed-63)))*BPS_RATE);
    }


    return(0);
}


int detect_mem_before_one()
{
    bool turn=0;
    for (int k=position_onstage-1; k>=0; k--)
    {
        if(k==0  && turn==0)
        {
            k=9999;
            turn=1;
        }
        if(MemoiresExistantes[k]==1 && MemoiresExclues[k]==0)
        {
            mem_before_one=k;
            break;
        }
    }
    return(0);
}


int detect_mem_preset()
{
    bool turn=0;
    for (int k=position_onstage+1; k<10000; k++)
    {
        if(k>=9999 && turn==0)
        {
            k=0;
            turn=1;
        }
        if(MemoiresExistantes[k]==1 && MemoiresExclues[k]==0)
        {
            position_preset=k;
            break;
        }
    }
    return(0);
}


int detect_next_mem(int mem_to_detect)//pour import ascii Anton 4 avril 2015
{
    for (int k=mem_to_detect+1; k<10000; ++k)
    {
        if(k>=9999)
        {
    return(0);
        }
        if(MemoiresExistantes[k]==1)
        {
            return k;
        }
    }
    return(0);
}


int detect_mem_preset_previous()
{
    bool turn=0;
    for (int p=(position_preset-1); p>=0; p--)
    {
        if(p==0 && turn==0)
        {
            p=9999;
            turn=1;
        }
        if (MemoiresExistantes[p]==1)
        {
            position_preset=p;
            break;
        }
    }
    return(0);
}

int detect_next_preset()
{
    bool turn=0;
    for (int p=(position_preset+1); p<10000; p++)
    {
        if(p>=9999 && turn==0)
        {
            p=0;
            turn=1;
        }
        if (MemoiresExistantes[p]==1 && MemoiresExclues[p]==0)
        {
            position_preset=p;
            break;
        }
    }
    return(0);
}


int refresh_mem_onpreset(int mem_is)
{
    for (int u=1; u<514; u++)
    {
        bufferBlind[u]=Memoires[mem_is][u];
    }
    ratio_X1X2_together=ratio_cross_manuel[mem_is];
    return(0);
}



int create_memory(int mem_to_create)
{
    if ( mem_to_create>10000)
    {
        sprintf(string_Last_Order,"a Mem can't be > to 1000");
    }

    else
    {
        MemoiresExistantes[mem_to_create]=1;
        sprintf(string_Last_Order,"Mem %d.%d created", mem_to_create/10, mem_to_create%10);
        Times_Memoires[mem_to_create][0]=0.0;
        Times_Memoires[mem_to_create][2]=0.0;
        Times_Memoires[mem_to_create][1]=default_time;
        Times_Memoires[mem_to_create][3]=default_time;
        ratio_cross_manuel[mem_to_create]=0;
//sab 02/03/2014 sprintf --> strcpy
        strcpy(descriptif_memoires[mem_to_create],"");
        strcpy(annotation_memoires[mem_to_create],"");

        Links_Memoires[mem_to_create]=0;
        Banger_Memoire[mem_to_create]=0;
        MemoiresExclues[mem_to_create]=0;
        record_memory(mem_to_create);

        if(index_blind==0)
        {
            position_onstage=mem_to_create;
            detect_mem_before_one();
            detect_mem_preset();
            refresh_mem_onpreset(position_preset);
        }
        else if (index_blind==1)
        {
            position_preset=mem_to_create;
        }

    }

    ratio_X1X2_together=0;
    return(0);
}



int create_memory_plus_faders(int mem_to_create)
{
    if ( mem_to_create>10000)
    {
        sprintf(string_Last_Order,"a Mem can't be > to 1000");
    }

    else
    {
        MemoiresExistantes[mem_to_create]=1;
        sprintf(string_Last_Order,"Mem %d.%d created", mem_to_create/10, mem_to_create%10);
        Times_Memoires[mem_to_create][0]=0.0;
        Times_Memoires[mem_to_create][2]=0.0;
        Times_Memoires[mem_to_create][1]=default_time;
        Times_Memoires[mem_to_create][3]=default_time;
        ratio_cross_manuel[mem_to_create]=0;
//sab 02/03/2014 sprintf --> strcpy
        strcpy(descriptif_memoires[mem_to_create],"");
        strcpy(annotation_memoires[mem_to_create],"");

        Links_Memoires[mem_to_create]=0;
        Banger_Memoire[mem_to_create]=0;
        MemoiresExclues[mem_to_create]=0;
        record_memory_plus_faders(mem_to_create);

        if(index_blind==0)
        {
            position_onstage=mem_to_create;
            detect_mem_before_one();
            detect_mem_preset();
            refresh_mem_onpreset(position_preset);
        }

    }

    ratio_X1X2_together=0;
    return(0);
}

int delete_memory(int mem_to_delete)
{
    sprintf(string_confirmation,"Delete Mem %d.%d ?", mem_to_delete/10,mem_to_delete%10);

    if (  mem_to_delete>10000)
    {
        sprintf(string_Last_Order,"a Mem to be deleted > to 1000");
    }
    else
    {
        if(MemoiresExistantes[mem_to_delete]==1)
        {
            MemoiresExistantes[mem_to_delete]=0;
            MemoiresDetruites[mem_to_delete]=1;
            sprintf(string_Last_Order,"Mem %d.%d deleted", mem_to_delete/10,mem_to_delete%10);
        }
        else if (MemoiresExistantes[mem_to_delete]==0)
        {
            sprintf(string_Last_Order,"Mem %d.%d do not exist", mem_to_delete/10,mem_to_delete%10);
        }
    }

    return(0);
}


int refresh_integrated_gridplayer1()
{
    if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_onstage]!=-1 )
    {
        index_grider_step_is[0]=set_from_seq_gridplayer1_next_step[position_onstage];
        grider_is_playing[0]=0;
        grid_niveauX1[0]=255;
        grid_niveauX2[0]=0;
        grid_floatX1[0]=255;
        grid_floatX2[0]=0;
        gridder_prepare_cross(0, index_grider_selected[0], index_grider_step_is[0]);
    }
    return(0);
}


int do_load_mem_preset_while_crossfade(int mem_is)
{
    index_go=0;
    index_pause=0;
    index_go_back=0;
    for (int op=1; op<514; op++)
    {
        bufferSaisie[op]=bufferSequenciel[op];
    }
    niveauX1=255;
    niveauX2=0;
    crossfade_speed=64;
    position_preset=mem_is;
    refresh_mem_onpreset(mem_is);
    prepare_crossfade();
    floatX1=niveauX1;
    floatX2=niveauX2;
    index_go=1;
    refresh_integrated_gridplayer1();
    return(0);
}

int do_double_go_function()
{
    index_go=0;
    index_pause=0;
    index_go_back=0;
    for (int op=1; op<514; op++)
    {
        bufferSaisie[op]=bufferSequenciel[op];
    }
    niveauX1=255;
    niveauX2=0;
    crossfade_speed=64;
    reset_modified_levels_in_crossfade();
    for(int ipo=position_preset+1; ipo<10000; ipo++)
    {
        if(ipo>=9999)
        {
            ipo=0;
        }
        if(MemoiresExistantes[ipo]==1)
        {
            position_preset=ipo;
            break;
        }
    }
    refresh_mem_onpreset(position_preset);
    prepare_crossfade();
    floatX1=niveauX1;
    floatX2=niveauX2;
    index_go=1;
    refresh_integrated_gridplayer1();
    if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_preset]!=-1 )
    {
        grid_in_preset[0][0]=index_grider_selected[0];
        grid_in_preset[0][1]=set_from_seq_gridplayer1_next_step[position_preset]-1;
        if(grider_is_playing[0]==0 && set_from_seq_gridplayer1_next_step[position_preset]!=-1 )
        {
            gridder_prepare_cross(0,index_grider_selected[0],set_from_seq_gridplayer1_next_step[position_preset]-1);
            grider_is_playing[0]=1;
            grid_crossfade_start_time[0]=actual_time;
        }
    }
    return(0);
}

int do_go_back_function()
{
    if(index_go_back==0 && index_go==0 && index_pause==0)
    {
        for (int op=1; op<514; op++)
        {
            bufferSaisie[op]=bufferSequenciel[op];
        }
        niveauX1=255;
        niveauX2=0;
        position_preset=mem_before_one;
        refresh_mem_onpreset(position_preset);
        prepare_crossfade();
        floatX1=niveauX1;
        floatX2=niveauX2;
        index_go=1;
//integration du gridplayer 1
        if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_preset]!=-1 )
        {
            grid_in_preset[0][0]=index_grider_selected[0];
            grid_in_preset[0][1]=set_from_seq_gridplayer1_next_step[position_onstage]-1;
            if(grider_is_playing[0]==0 && set_from_seq_gridplayer1_next_step[position_preset]!=-1 )
            {
                gridder_prepare_cross(0,index_grider_selected[0],set_from_seq_gridplayer1_next_step[position_preset]-1);
                grider_is_playing[0]=1;
                grid_crossfade_start_time[0]=actual_time;
            }
        }
    }
    else if(index_go_back==0 && index_go==1)
    {
        index_go_back=1;
        index_go=0;
        index_pause=0;
    }
    else if(index_go_back==1 && index_pause==0)
    {
        index_pause=1;
    }
    else if(index_go_back==1 && index_pause==1)
    {
        index_pause=0;
    }
    return(0);
}


int do_go_function()
{

    if(index_go==0)
    {
        index_go=1;
        index_go_back=0;
        crossfade_start_time=actual_time;
        index_pause=0;
//integration du gridplayer 1
        if(show_gridplayer_in_seq==1)
        {
            grid_in_preset[0][0]=index_grider_selected[0];
            grid_in_preset[0][1]=set_from_seq_gridplayer1_next_step[position_preset]-1;
            if(grider_is_playing[0]==0 && set_from_seq_gridplayer1_next_step[position_preset]!=-1
                    && set_from_seq_gridplayer1_next_step[position_preset]!=index_grider_step_is[0])
            {
                gridder_prepare_cross(0,index_grider_selected[0],set_from_seq_gridplayer1_next_step[position_preset]-1);
                grider_is_playing[0]=1;
                grid_crossfade_start_time[0]=actual_time;
            }
        }
    }

    else if(index_go==1 && index_pause==0)
    {
        index_pause=1;
        if(crossfade_time_delay_in>(actual_time-crossfade_start_time))
        {
            crossfade_time_delay_in-=actual_time-crossfade_start_time;
        };
        if(crossfade_time_delay_out>(actual_time-crossfade_start_time))
        {
            crossfade_time_delay_out-=actual_time-crossfade_start_time;
        };
//integration du gridplayer 1
        if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_preset]!=-1)
        {
            grid_in_preset[0][0]=index_grider_selected[0];
            grid_in_preset[0][1]=set_from_seq_gridplayer1_next_step[position_preset]-1;
            if(grider_is_playing[0]==1 )
            {
                grider_is_playing[0]=0;
                if(grid_delay_in[0]>(actual_time-grid_crossfade_start_time[0]))
                {
                    grid_delay_in[0]-=actual_time-grid_crossfade_start_time[0];
                };
                if(grid_delay_out[0]>(actual_time-grid_crossfade_start_time[0]))
                {
                    grid_delay_out[0]-=actual_time-grid_crossfade_start_time[0];
                }
            }
        }
    }
    else if(index_go==1 && index_pause==1)
    {
        crossfade_start_time=actual_time;
        index_pause=0;
        if(crossfade_time_delay_in>(actual_time-crossfade_start_time))
        {
            crossfade_time_delay_in-=actual_time-crossfade_start_time;
        }
        if(crossfade_time_delay_in<0)
        {
            crossfade_time_delay_in=0;
        }
        if(crossfade_time_delay_out>(actual_time-crossfade_start_time))
        {
            crossfade_time_delay_out-=actual_time-crossfade_start_time;
        };
        if(crossfade_time_delay_out<0)
        {
            crossfade_time_delay_out=0;
        }
//integration du gridplayer 1
        if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_preset]!=-1 && grider_is_playing[0]==0)
        {
            grid_in_preset[0][0]=index_grider_selected[0];
            grid_in_preset[0][1]=set_from_seq_gridplayer1_next_step[position_preset]-1;
            gridder_prepare_cross(0,index_grider_selected[0],set_from_seq_gridplayer1_next_step[position_preset]-1);
            grider_is_playing[0]=1;
            if(grid_delay_in[0]>(actual_time-grid_crossfade_start_time[0]))
            {
                grid_delay_in[0]-=actual_time-grid_crossfade_start_time[0];
            }
            if(grid_delay_in[0]<0)
            {
                grid_delay_in[0]=0;
            }
            if(grid_delay_out[0]>(actual_time-grid_crossfade_start_time[0]))
            {
                grid_delay_out[0]-=actual_time-grid_crossfade_start_time[0];
            };
            if(grid_delay_out[0]<0)
            {
                grid_delay_out[0]=0;
            }
        }
    }
    return(0);
}


int patch_unselect_all_dimmers()
{
    for(int i=0; i<513; i++)
    {
        Dimmers_selected[i]=0;
    }
    return(0);
}


int build_default_curve(int curve)
{
    mouse_released=1;

//points
    for (int pt=1; pt<MAX_curve_nodeS-1; pt++)
    {
        curve_ctrl_pt[curve][pt][0]=(int)((((float)255)/6) *pt);
        curve_ctrl_pt[curve][pt][1]=255-(int)((((float)255)/6) *pt);
    }
    curve_ctrl_pt[curve][1][0]=0;
    curve_ctrl_pt[curve][1][1]=255;//point 1 en 0 0
    curve_ctrl_pt[curve][5][0]=255;
    curve_ctrl_pt[curve][5][1]=0;//point 5 en 255 255

    curve_ctrl_pt[curve][6][0]=255;
    curve_ctrl_pt[curve][6][1]=0;//point 5 en 255 255

    the_curve_spline_level[curve]=168;
    index_curve_spline_level=168;
    curve_spline_level=(((float)index_curve_spline_level)/127)-1;
    curve_node_count=6;
    curve_curviness = ftofix(curve_spline_level);


    curve_spline_level=(((float)index_curve_spline_level)/127)-1;

    for (int i=0;i<255;i++)
    {
    curve_report[curve][i]=255-i;
    }

    view_curve_after_draw();
    return(0);
}


////////////////////////////////////////////////////////////////////////////////
int set_to_default_my_roi(int dkprpreset, int dkpr)
{
    if(dkpr<6)
    {
        tracking_coordonates[dkprpreset][dkpr][0]=25+(40*dkpr);//x
        tracking_coordonates[dkprpreset][dkpr][1]=100;//y
        tracking_coordonates[dkprpreset][dkpr][2]=25;//largeur
        tracking_coordonates[dkprpreset][dkpr][3]=25;//hauteur
    }
    else if(dkpr>=6)
    {
        tracking_coordonates[dkprpreset][dkpr][0]=25+(40*(dkpr-6));//x
        tracking_coordonates[dkprpreset][dkpr][1]=150;//y
        tracking_coordonates[dkprpreset][dkpr][2]=25;//largeur
        tracking_coordonates[dkprpreset][dkpr][3]=25;//hauteur
    }

    for(int affe=1; affe<512; affe++)//était 513 aout 2016
    {
        tracking_contents[dkprpreset][dkpr][affe]=0;
    }
    return(0);
}

int set_to_default_my_trackers()
{
    for (int dokTr=0; dokTr<6; dokTr++)
    {
        set_to_default_my_roi(dokTr,dokTr);
        set_to_default_my_roi(dokTr,dokTr+6);
    }
    return(0);
}


int set_to_default_this_tracker(int Tcker)
{
    for (int dokTr=0; dokTr<6; dokTr++)
    {
        set_to_default_my_roi(Tcker,dokTr);
        set_to_default_my_roi(Tcker,dokTr+6);
    }
    return(0);
}

////////////////////////////////////////////////////////////////////////////////

int write_show_coming_from()
{
    FILE *fpi;
    if((fpi=fopen("user/show_coming_from.txt","w")))//etait wb
    {
        fprintf(fpi,"%s",my_show_is_coming_from);
    }
    fclose(fpi);
    return(0);
}


int scan_for_free_dock()
{
    bool someone_inside=0;
    for (int f=0; f<core_user_define_nb_faders; f++)
    {
        for (int d=0; d<core_user_define_nb_docks; d++)
        {
            someone_inside=0;
            for(int c=0; c<513; c++)
            {
                if (FaderDockContains[f][d][c]>0)
                {
                    someone_inside=1;
                    break;
                }
            }
            if(someone_inside==0)
            {
                DockTypeIs[f][d]=9;
            }
            else if(someone_inside==1)
            {
                DockTypeIs[f][d]=0;
            }
        }

    }
    return(0);
}




int detect_dock_used(int numfad)
{
    int thedockused=0;
    for (int tt=0; tt<core_user_define_nb_docks; tt++)
    {
        if ( DockIsSelected[numfad][tt]==1)
        {
            thedockused=tt;
            break;
        }
    }
    return(thedockused);
}


int refresh_minifader_state_view_core(int cmptfader)
{
    sprintf(str_minifader_feedback[0],"Fader %d:",cmptfader+1);
    int dokmin=dock_used_by_fader_is[cmptfader];
    sprintf(str_minifader_feedback[2],DockName[cmptfader][dokmin]);
    switch(DockTypeIs[cmptfader][dokmin])
    {
    case 0:
        sprintf(str_tmp_minidock_dock,"Channels");
        break;
//types des docks
    case 1://si le doc est relié aux trichro
        sprintf(str_tmp_minidock_dock,"Color");
        break;
    case 2://si le doc est relié à un artnet
        sprintf(str_tmp_minidock_dock, "Art-%d",DockNetIs[cmptfader][dokmin]);
        break;
    case 3://si le doc recoit le dmxIN
        sprintf(str_tmp_minidock_dock,"Dmx-In");
        break;
    case 4://si le doc recoit le tracking video
        sprintf(str_tmp_minidock_dock,"Video");
        break;
    case 5://si le doc contient une memoire
        sprintf(str_tmp_minidock_dock,"Mem.%.1f",(((float)(DockHasMem[cmptfader][dokmin]))/10));
        sprintf(str_minifader_feedback[2],descriptif_memoires[(DockHasMem[cmptfader][dokmin])]);
        break;
    case 6://audio Player Volume
        sprintf(str_tmp_minidock_dock,"Vol.%d",(DockHasAudioVolume[cmptfader][dokmin]));
        break;
    case 7://audio Player Pan
        sprintf(str_tmp_minidock_dock,"Pan.%d",(DockHasAudioPan[cmptfader][dokmin]));
        break;
    case 8:
        sprintf(str_tmp_minidock_dock,"Pitch.%d",(DockHasAudioPitch[cmptfader][dokmin]));
        break;
    case 9://no content
        sprintf(str_tmp_minidock_dock,"-no name-");
        break;
    case 10://DC
        sprintf(str_tmp_minidock_dock,"DC.%d",(FaderDirectChan[cmptfader][dokmin]));
        break;
    case 11://chaser
        sprintf(str_tmp_minidock_dock,"Chaser.%d",(ChaserAffectedToDck[cmptfader][dokmin]+1));
        break;
    case 12:
        sprintf(str_tmp_minidock_dock,"GridPl.%d",(faders_dock_grid_affectation[cmptfader][dokmin]+1));
        break;
     default:break;
    }
    sprintf(str_minifader_feedback[1],"Dock %d %s",(dokmin+1),str_tmp_minidock_dock);

    sprintf(str_minifader_feedback[3],"Speed: %d", lfo_speed[cmptfader]);

    switch(lfo_mode_is[cmptfader])
    {
    case 0:
        sprintf(report_minifader_str,"Status: No Move");
        break;
    case 1:
        sprintf(report_minifader_str,"Status: Up");
        break;
    case 2:
        sprintf(report_minifader_str,"Status: Down");
        break;
    default: break;
    }

    if(lfo_mode_is[cmptfader]==0 && lfo_cycle_is_on[cmptfader]==1)
    {
        sprintf(report_minifader_str,"Status: Saw");
    }

    if(is_dock_for_lfo_selected[cmptfader][dokmin]==1)
    {
        strcat(report_minifader_str," [Loop]");
    }
    sprintf(str_minifader_feedback[4],report_minifader_str);
//sab 02/03/2014 sprintf(report_minifader_str,"");//clear
    strcpy(report_minifader_str,"");

    if(lfo_do_next_step[cmptfader][0]==1)
    {
        sprintf(str_minifader_feedback[5],"ToPrev. Dock");
    }
    else if(lfo_do_next_step[cmptfader][1]==1)
    {
        sprintf(str_minifader_feedback[6],"ToNext Dock");
    }
    if(lfo_cycle_steps[cmptfader]==1)
    {
        sprintf(str_minifader_feedback[7],"UpAndDown Docks");
    }

//affichage temps

    sprintf(str_minifader_feedback[8],string_time_is_in_the_dock[cmptfader]);

    if(StopPosOn[cmptfader]==1)
    {
        int niv=0;
        switch(dmx_view)
        {
        case 0:
            niv= (int) (((float)LevelStopPos[cmptfader])/2.55);
            break;
        case 1:
            niv=LevelStopPos[cmptfader];
            break;
         default:break;
        }
        sprintf(string_fader_stop_pos[cmptfader],"%d",niv);
        sprintf(str_minifader_feedback[9],"Stop Pos ON: %d",niv);
    }
//sab 02/03/2014 else if(StopPosOn[cmptfader]==0){sprintf(str_minifader_feedback[9],"");}
    else if(StopPosOn[cmptfader]==0)
    {
        strcpy(str_minifader_feedback[9],"");
    }
    return(0);
}



int do_action_on_selected_minifaders(int action)
{
//variables pas incluable ds double boucle
    bool index_choose_mode_dkloop=0;//0 toggle tt le monde / 1 copie l etat du dck selctionné dans tt le monde
    //sab 02/03/2014 unsued var int tpdkval=0;
    int dockused=0;

    for(int cmptfader=0; cmptfader<max_faders; cmptfader++)
    {
        if( minifaders_selected[cmptfader]==1)
        {
            switch(action)
            {
            case 0://flash
//mis a part a cause gestion souris
                break;
            case 1://lock
                switch(FaderLocked[cmptfader])
                {
                case 0:
                    FaderLocked[cmptfader]=1;
                    StateOfFaderBeforeLock[cmptfader]=Fader[cmptfader];
                    if(StateOfFaderBeforeLock[cmptfader]==255)
                    {
                        LockFader_is_FullLevel[cmptfader]=1;
                    }
                    else if(StateOfFaderBeforeLock[cmptfader]<255)
                    {
                        LockFader_is_FullLevel[cmptfader]=0;
                    }
                    sprintf(string_Last_Order,">> LOCKED Fader %d",cmptfader+1);
                    if(LockFader_is_FullLevel[cmptfader]==0)//quand mis en lock et pas full level rajout 0.7.6
                    {
                        lfo_mode_is[cmptfader]=0;
                        lfo_cycle_is_on[cmptfader]=0;
                    }
                    break;
                case 1:
                    FaderLocked[cmptfader]=0;
                    //remise à plat du niveau
                    Fader[cmptfader]=(unsigned char)((((float)(StateOfFaderBeforeLock[cmptfader]))/255)*locklevel);
                    midi_levels[cmptfader]=(int)(((float)Fader[cmptfader])/2);
                    sprintf(string_Last_Order,">> UNLOCKED Fader %d",cmptfader+1);
                    break;
                 default:break;
                }
                break;
            case 2://loop on off
                for(int j=0; j<core_user_define_nb_docks; j++)
                {
                    if(DockIsSelected[cmptfader][j]==1)
                    {
                        is_dock_for_lfo_selected[cmptfader][j]=toggle(is_dock_for_lfo_selected[cmptfader][j]);
                        break;
                    }
                }
                break;
            case 3://UP
                if(FaderLocked[cmptfader]==0 || LockFader_is_FullLevel[cmptfader]==1)
                {
//for delays
                    start_time_for_delays[cmptfader]=actual_time;
//
                    if(lfo_mode_is[cmptfader]!=1)//up
                    {
                        lfo_mode_is[cmptfader]=1;
                        faders_in_float[cmptfader]=Fader[cmptfader];
                        if(index_midi_mute_on_lfo==1)
                        {
                            is_raccrochage_midi_remote[cmptfader]=1;
                        }
                    }
                    else
                    {
                        lfo_mode_is[cmptfader]=0;
                    }
                    lfo_cycle_is_on[cmptfader]=0;
                }
                break;
            case 4://DOWN
                if(FaderLocked[cmptfader]==0 || LockFader_is_FullLevel[cmptfader]==1)
                {
//for delays
                    start_time_for_delays[cmptfader]=actual_time;
//
                    if(lfo_mode_is[cmptfader]!=2)//down
                    {
                        lfo_mode_is[cmptfader]=2;
                        faders_in_float[cmptfader]=Fader[cmptfader];
                        if(index_midi_mute_on_lfo==1)
                        {
                            is_raccrochage_midi_remote[cmptfader]=1;
                        }
                    }
                    else
                    {
                        lfo_mode_is[cmptfader]=0;
                    }
                    lfo_cycle_is_on[cmptfader]=0;
                }
                break;
            case 5://SAW
                if(FaderLocked[cmptfader]==0 || LockFader_is_FullLevel[cmptfader]==1)
                {
//for delays
                    start_time_for_delays[cmptfader]=actual_time;
//
                    faders_in_float[cmptfader]=Fader[cmptfader];
                    if(lfo_cycle_is_on[cmptfader]==0)//
                    {
                        lfo_cycle_is_on[cmptfader]=1;
                        lfo_mode_is[cmptfader]=0;
                        lfo_running_is_upward[cmptfader]=1;
                        if(index_midi_mute_on_lfo==1)
                        {
                            is_raccrochage_midi_remote[cmptfader]=1;
                        }
                    }
                    else if(lfo_cycle_is_on[cmptfader]==1)
                    {
                        lfo_cycle_is_on[cmptfader]=0;
                    }
                }
                break;
            case 6://Loop all
                for (int ck=0; ck<5; ck++)
                {
                    if(is_dock_for_lfo_selected[cmptfader][ck]!=is_dock_for_lfo_selected[cmptfader][ck+1])
                    {
                        index_choose_mode_dkloop=1;
                        break;
                    }
                }
                switch(index_choose_mode_dkloop)
                {
                case 0:
                    for(int op=0; op<core_user_define_nb_docks; op++)
                    {
                        is_dock_for_lfo_selected[cmptfader][op]=toggle(is_dock_for_lfo_selected[cmptfader][op]);
                    }
                    break;
                case 1:
//tout le monde prend la valeur du dock selectionné
                    for(int j=0; j<core_user_define_nb_docks; j++)
                    {
                        if(DockIsSelected[cmptfader][j]==1)
                        {
                            int tempval_dockloop=toggle(is_dock_for_lfo_selected[cmptfader][j]);
                            for(int k=0; k<core_user_define_nb_docks; k++)
                            {
                                is_dock_for_lfo_selected[cmptfader][k]=toggle(tempval_dockloop);
                            }
                            break;
                        }
                    }
                    break;
                    default:break;

                }
                break;
            case 7://all at zero
                do_stock_fadersstate(1,1,1,1,1);

                Fader[cmptfader]=0;
                midi_levels[cmptfader]=0;
                index_send_midi_out[cmptfader]=1;
                lfo_speed[cmptfader]=64;
                midi_levels[196+cmptfader]=64;
                index_send_midi_out[196+cmptfader]=1;
                FaderLocked[cmptfader]=0;
                lfo_mode_is[cmptfader]=0;//no lfo
                lfo_cycle_is_on[cmptfader]=0;//saw
                lfo_cycle_steps[cmptfader]=0;
                lfo_do_next_step[cmptfader][0]=0;
                lfo_do_next_step[cmptfader][1]=0;
                for(int d=0; d<core_user_define_nb_docks; d++)
                {
                    is_dock_for_lfo_selected[cmptfader][d]=0;
                }

            break;

            case 8://Set pos job

                if(index_do_dock==0 && index_main_clear==0)
                {
                    ActionnateStopOn[cmptfader]=toggle(ActionnateStopOn[cmptfader]);
                    mouse_released=1;
                }

                else if(index_do_dock==1 && index_main_clear==0 )
                {
                    if(numeric_postext>0 )//affectation stop pos par chaine de carcatere
                    {
                        int lStopPos=999;
                        switch(dmx_view)
                        {
                        case 0:
                            lStopPos=(int)((atof(numeric) *2.55) +1);//+1 pour arrondir le %
                            break;
                        case 1:
                            lStopPos=atol(numeric);
                            break;
                         default:break;
                        }
                        reset_numeric_entry();
                        if (lStopPos>=0 && lStopPos<=255)
                        {
                            StopPosOn[cmptfader]=1;
                            LevelStopPos[cmptfader]=lStopPos;
                            index_do_dock=0;
                            do_light_setpos[cmptfader]=1;
                        }
                    }
                    else if (numeric_postext==0) //affectation stop pos depuis le cursuer fader
                    {
                        StopPosOn[cmptfader]=1;
                        LevelStopPos[cmptfader]=Fader[cmptfader];
                        index_do_dock=0;
                        do_light_setpos[cmptfader]=1;
                    }
                }

                else if(index_main_clear==1 && index_do_dock==0)//clear
                {
                    StopPosOn[cmptfader]=0;
                    LevelStopPos[cmptfader]=999;
                    index_main_clear=0;
                    do_light_setpos[cmptfader]=1;
                }
                break;
            case 9://PrEV DOCK MODE
                if (lfo_do_next_step[cmptfader][0]==0)
                {
                    lfo_do_next_step[cmptfader][0]=1;
                    lfo_do_next_step[cmptfader][1]=0;
                }
                else if (lfo_do_next_step[cmptfader][0]==1)
                {
                    lfo_do_next_step[cmptfader][0]=0;
                }
                break;
            case 10://NEXT DOCK MODE
                if (lfo_do_next_step[cmptfader][1]==0)
                {
                    lfo_do_next_step[cmptfader][1]=1;
                    lfo_do_next_step[cmptfader][0]=0; ;
                }
                else if (lfo_do_next_step[cmptfader][1]==1)
                {
                    lfo_do_next_step[cmptfader][1]=0;
                }
                break;
            case 11://VA ET VIENT
                lfo_cycle_steps[cmptfader]= toggle(lfo_cycle_steps[cmptfader]);
                break;
            case 12: //dock minus
                dockused=detect_dock_used(cmptfader);
                DockIsSelected[cmptfader][dockused]=0;
                if (dockused>0)
                {
                    DockIsSelected[cmptfader][dockused]=0;
                    dockused--;
                    DockIsSelected[cmptfader][dockused]=1;
                }
                else if (dockused==0)
                {
                    DockIsSelected[cmptfader][dockused]=0;
                    dockused=5;//6 docks pos 5
                    DockIsSelected[cmptfader][dockused]=1;
                }

                break;
            case 13: // dock plus
                dockused=detect_dock_used(cmptfader);
                DockIsSelected[cmptfader][dockused]=0;
                if (dockused<5)
                {
                    DockIsSelected[cmptfader][dockused]=0;
                    dockused++;
                    DockIsSelected[cmptfader][dockused]=1;
                }
                else if (dockused==5)
                {
                    DockIsSelected[cmptfader][dockused]=0;
                    dockused=0;//6 docks pos 5
                    DockIsSelected[cmptfader][dockused]=1;
                }

                break;
            case 14: //play embeded
                int the_chaser;
                int the_grid_player;
                int the_audio_player;

                if(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==11 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==12
                        || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==6 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==7 || DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==8  )

                {

                    if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==11) the_chaser=ChaserAffectedToDck[cmptfader][dock_used_by_fader_is[cmptfader]];
                    else if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==12 )  the_grid_player=faders_dock_grid_affectation[cmptfader][dock_used_by_fader_is[cmptfader]];
                    else if( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==6 ) the_audio_player=DockHasAudioVolume[cmptfader][dock_used_by_fader_is[cmptfader]]-1;
                    else if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==7 ) the_audio_player=DockHasAudioPan[cmptfader][dock_used_by_fader_is[cmptfader]]-1;
                    else if ( DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]]==8 ) the_audio_player=DockHasAudioPitch[cmptfader][dock_used_by_fader_is[cmptfader]]-1;

                    switch(DockTypeIs[cmptfader][dock_used_by_fader_is[cmptfader]])
                    {
                    case 6://vol
                        if(player_ignited[the_audio_player]==1)
                        {
                            switch(the_audio_player)
                            {
                            case 0://PLAYER 1
                                switch(player1->isPlaying())
                                {
                                case 0:
                                    player1->play();
                                    break;
                                case 1:
                                    //player1->stop();
                                    player1_do_stop();
                                    break;
                                     default:break;
                                }
                                break;
                            case 1://PLAYER 2
                                switch(player2->isPlaying())
                                {
                                case 0:
                                    player2->play();
                                    break;
                                case 1:
                                    //player2->stop();
                                    player2_do_stop();
                                    break;
                                     default:break;
                                }
                                break;
                            case 2://PLAYER 3
                                switch(player3->isPlaying())
                                {
                                case 0:
                                    player3->play();
                                    break;
                                case 1:
                                    //player3->stop();
                                    player3_do_stop();
                                    break;
                                     default:break;
                                }
                                break;
                            case 3://PLAYER 4
                                switch(player4->isPlaying())
                                {
                                case 0:
                                    player4->play();
                                    break;
                                case 1:
                                    //player4->stop();
                                    player4_do_stop();
                                    break;
                                     default:break;
                                }
                                break;
                                default: break;
                            }
                            switch(player_is_playing[the_audio_player])//inversed by action
                            {
                            case 0:
                                sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
                                break;
                            case 1:
                                sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
                                break;
                                 default:break;
                            }
                        }
                        break;
                    case 7://pan
                        if(player_ignited[the_audio_player]==1)
                        {
                            switch(the_audio_player)
                            {
                            case 0://PLAYER 1
                                switch(player1->isPlaying())
                                {
                                case 0:
                                    player1->play();
                                    break;
                                case 1:
                                    //player1->stop();
                                    player1_do_stop();
                                    break;
                                 default:break;
                                }
                                break;
                            case 1://PLAYER 2
                                switch(player2->isPlaying())
                                {
                                case 0:
                                    player2->play();
                                    break;
                                case 1:
                                    //player2->stop();
                                    player2_do_stop();
                                    break;
                                 default:break;
                                }
                                break;
                            case 2://PLAYER 3
                                switch(player3->isPlaying())
                                {
                                case 0:
                                    player3->play();
                                    break;
                                case 1:
                                    //player3->stop();
                                    player3_do_stop();
                                    break;
                                     default:break;
                                }
                                break;
                            case 3://PLAYER 4
                                switch(player4->isPlaying())
                                {
                                case 0:
                                    player4->play();
                                    break;
                                case 1:
                                    //player4->stop();
                                    player4_do_stop();
                                    break;
                                     default:break;
                                }
                                break;
                                default: break;
                            }
                            switch(player_is_playing[the_audio_player])//inversed by action
                            {
                            case 0:
                                sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
                                break;
                            case 1:
                                sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
                                break;
                                 default:break;
                            }
                        }
                        break;
                    case 8://pitch
                        if(player_ignited[the_audio_player]==1)
                        {
                            switch(the_audio_player)
                            {
                            case 0://PLAYER 1
                                switch(player1->isPlaying())
                                {
                                case 0:
                                    player1->play();
                                    break;
                                case 1:
                                    //player1->stop();
                                    player1_do_stop();
                                    break;
                                 default:break;
                                }
                                break;
                            case 1://PLAYER 2
                                switch(player2->isPlaying())
                                {
                                case 0:
                                    player2->play();
                                    break;
                                case 1:
                                    //player2->stop();
                                    player2_do_stop();
                                    break;
                                     default:break;
                                }
                                break;
                            case 2://PLAYER 3
                                switch(player3->isPlaying())
                                {
                                case 0:
                                    player3->play();
                                    break;
                                case 1:
                                    //player3->stop();
                                    player3_do_stop();
                                    break;
                                 default:break;
                                }
                                break;

                            case 3://PLAYER 4
                                switch(player4->isPlaying())
                                {
                                case 0:
                                    player4->play();
                                    break;
                                case 1:
                                    //player4->stop();
                                    player4_do_stop();
                                    break;
                                 default:break;
                                }
                                break;
                                 default:break;
                            }
                            switch(player_is_playing[the_audio_player])//inversed by action
                            {
                            case 0:
                                sprintf(string_Last_Order,">> PLAY ON from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
                                break;
                            case 1:
                                sprintf(string_Last_Order,">> PLAY OFF from Fader %d Audio %d",cmptfader+1,the_audio_player+1);
                                break;
                                 default:break;
                            }
                        }
                        break;
                    case 11://chaser
                        chaser_is_playing[the_chaser]=toggle(chaser_is_playing[the_chaser]);
                        if(chaser_is_playing[the_chaser]==1)//snap du temps at beg
                        {
                            chaser_start_time[the_chaser]=actual_time;
//bug olivier marche arriere arrière ligne
                            if(chaser_step_is[chaser_selected]<0)
                            {
                                chaser_step_is[chaser_selected]=0;
                            }
                            else if(chaser_step_is[chaser_selected]>35)
                            {
                                chaser_step_is[chaser_selected]=35;
                            }
                        }
                        switch(chaser_is_playing[the_chaser])
                        {
                        case 0:
                            sprintf(string_Last_Order,">> PLAY OFF from Fader %d Chaser %d",cmptfader+1,the_chaser+1);
                            break;
                        case 1:
                            sprintf(string_Last_Order,">> PLAY ON from Fader %d Chaser %d",cmptfader+1,the_chaser+1);
                            break;
                             default:break;
                        }
                        break;
                    case 12://grid
                        grider_is_playing[the_grid_player]=toggle(grider_is_playing[the_grid_player]);
                        if(grider_is_playing[the_grid_player]==1)
                        {
                            grid_crossfade_start_time[the_grid_player]=actual_time;
                        }
                        switch(player_is_playing[the_grid_player])
                        {
                        case 0:
                            sprintf(string_Last_Order,">> PLAY OFF from Fader %d GridPl %d",cmptfader+1,the_grid_player+1);
                            break;
                        case 1:
                            sprintf(string_Last_Order,">> PLAY ON from Fader %d GridPl %d",cmptfader+1,the_grid_player+1);
                            break;
                             default:break;
                        }
                        break;
                    default:
                    break;
                    }
                }

                break;
            default:
                break;
            }
        }

    }
    return(0);
}

int match_minifaders()
{
//presets
    mf_preset_selected_is=-999;
    for(int prt=0; prt<8; prt++)
    {
        int index_presetmf=0;
        for(int cmptfader=0; cmptfader<core_user_define_nb_faders; cmptfader++)
        {
            if(minifaders_preset_selection[prt][cmptfader]==minifaders_selected[cmptfader])
            {
                index_presetmf++;
            }
            if(index_presetmf==core_user_define_nb_faders)
            {
                mf_preset_selected_is=prt;
                break;
            }
        }
    }
//detect empty
    for(int prt=0; prt<8; prt++)
    {
        int index_presetmf=0;
        for(int cmptfader=0; cmptfader<core_user_define_nb_faders; cmptfader++)
        {
            if(minifaders_preset_selection[prt][cmptfader]==0)
            {
                index_presetmf++;
            }
        }
        if(index_presetmf==core_user_define_nb_faders)
        {
            minifader_preset_is_empty[prt]=1;
        }
        else
        {
            minifader_preset_is_empty[prt]=0;
        }
    }
    return(0);
}



int affect_time_entry_to_mem(int index_t,int mem_set_to_time)
{
    if(numeric_postext>0)
    {
        read_time_string_entry();
        Times_Memoires[mem_set_to_time][index_t]=(time_minutes*60)+time_secondes+(0.01*time_centiemes);
    }

    someone_changed_in_sequences=1;//icat
    return(0);
}

int do_sprintf_job()//report du calcul des affichages de temps dans la boucle des 10ème de scondes
{

    if (MemoiresExistantes[mem_before_one]==1)
    {
        sprintf(string_mem_before_one,"%d.%d",mem_before_one/10, mem_before_one%10);
    }
    else
    {
        sprintf(string_mem_before_one,"-");
    }

    sprintf(string_ratio_x1x2,"%.2f",((255.0-ratio_X1X2_together)/255));
    sprintf(str_crossfade_speed_is,"%d",crossfade_speed-64);

    float val_accel=0.0;

//position onstage
    affichage_time_format(Times_Memoires[position_onstage][0]);//dout
    sprintf(string_time_memonstage[0],string_conversion_timeis);
    affichage_time_format(Times_Memoires[position_onstage][2]);//dIn
    sprintf(string_time_memonstage[2],string_conversion_timeis);
    affichage_time_format(Times_Memoires[position_onstage][3]);//in
    sprintf(string_time_memonstage[3],string_conversion_timeis);
    affichage_time_format(Times_Memoires[position_onstage][1]);//out
    sprintf(string_time_memonstage[1],string_conversion_timeis);
//positionpreset > cross à venir
//temps d entree( enregistré dans le préset)
    if(Times_Memoires[position_preset][0]>0.00)
    {
        if(crossfade_speed<64)
        {
            affichage_time_format(Times_Memoires[position_preset][0]*(64.0/crossfade_speed));
        }
        else if(crossfade_speed==64)
        {
            affichage_time_format(Times_Memoires[position_preset][0]);
        }
        else if(crossfade_speed>64)
        {
            val_accel=Times_Memoires[position_preset][0]- ( (Times_Memoires[position_preset][0] /64) * (crossfade_speed-63));
            affichage_time_format(val_accel);
        }
        sprintf(cross_din,string_conversion_timeis);
    }
//sab 02/03/2014 else {sprintf(cross_din,"");}
    else
    {
        strcpy(cross_din,"");
    }


//temps de delay sortie ( enregistré dans le préset)
    if(Times_Memoires[position_preset][2]>0.00)
    {
        if(crossfade_speed<64)
        {
            affichage_time_format(Times_Memoires[position_preset][2]*(64.0/crossfade_speed));
        }
        else if(crossfade_speed==64)
        {
            affichage_time_format(Times_Memoires[position_preset][2]);
        }
        else if(crossfade_speed>64)
        {
            val_accel=Times_Memoires[position_preset][2]- ( (Times_Memoires[position_preset][2] /64) * (crossfade_speed-63));
            affichage_time_format(val_accel);
        }
        sprintf(cross_dout,string_conversion_timeis);
    }
//sab 02/03/2014 else {sprintf(cross_dout,"");}
    else
    {
        strcpy(cross_dout,"");
    }

//affichages temps IN et OUT
    if(crossfade_speed<64)
    {
        affichage_time_format(Times_Memoires[position_preset][1]*(64.0/crossfade_speed));
        sprintf(cross_in,string_conversion_timeis);
        affichage_time_format(Times_Memoires[position_preset][3]*(64.0/crossfade_speed));
        sprintf(cross_out,string_conversion_timeis);

        report_dIn=(Times_Memoires[position_preset][0]*(64.0/crossfade_speed));
        report_In=(Times_Memoires[position_preset][1]*(64.0/crossfade_speed));
        report_dOut=(Times_Memoires[position_preset][2]*(64.0/crossfade_speed));
        report_Out=(Times_Memoires[position_preset][3]*(64.0/crossfade_speed));

    }
    else if(crossfade_speed==64)
    {
        affichage_time_format(Times_Memoires[position_preset][1]);
        sprintf(cross_in,string_conversion_timeis);
        affichage_time_format(Times_Memoires[position_preset][3]);
        sprintf(cross_out,string_conversion_timeis);

        report_dIn=(Times_Memoires[position_preset][0]);
        report_In=(Times_Memoires[position_preset][1]);
        report_dOut=(Times_Memoires[position_preset][2]);
        report_Out=(Times_Memoires[position_preset][3]);

    }
    else if(crossfade_speed>64)
    {
        val_accel=Times_Memoires[position_preset][1]- ( (Times_Memoires[position_preset][1] /64) * (crossfade_speed-63));
        affichage_time_format(val_accel);
        sprintf(cross_in,string_conversion_timeis);
        val_accel=Times_Memoires[position_preset][3]- ( (Times_Memoires[position_preset][3] /64) * (crossfade_speed-63));
        affichage_time_format(val_accel);
        sprintf(cross_out,string_conversion_timeis);

        report_dIn=
            ((Times_Memoires[position_preset][0]- ( (Times_Memoires[position_preset][0] /64) * (crossfade_speed-63))));
        report_In=
            ((Times_Memoires[position_preset][1]- ( (Times_Memoires[position_preset][1] /64) * (crossfade_speed-63))));

        report_dOut=
            ((Times_Memoires[position_preset][2]- ( (Times_Memoires[position_preset][2] /64) * (crossfade_speed-63))));
        report_Out=
            ((Times_Memoires[position_preset][3]- ( (Times_Memoires[position_preset][3] /64) * (crossfade_speed-63))));

    }


    if(((report_dOut+report_Out)>=(report_dIn+ report_In))&&((report_dOut+report_Out)>=(report_dIn+ report_Out))&&((report_dOut+report_Out)>=(report_dOut+report_In)))
    {
        totalTimeCrossfade= (report_dOut+report_Out);
    }
    if(((report_dIn+ report_In)>=(report_dOut+report_Out))&&((report_dIn+ report_In)>=(report_dIn+ report_Out))&&((report_dIn+ report_In)>=(report_dOut+report_In)))
    {
        totalTimeCrossfade= (report_dIn+ report_In);
    }
    if(((report_dIn+ report_Out)>=(report_dIn+ report_In))&&((report_dIn+ report_Out)>=(report_dOut+report_Out))&&((report_dIn+ report_Out)>=(report_dOut+report_In)))
    {
        totalTimeCrossfade= (report_dIn+ report_Out);
    }
    if(((report_dOut+report_In)>=(report_dIn+ report_In))&&((report_dOut+report_In)>=(report_dIn+ report_Out))&&((report_dOut+report_In)>=(report_dOut+report_Out)))
    {
        totalTimeCrossfade= (report_dOut+report_In);
    }

    affichage_time_format(totalTimeCrossfade);
    sprintf(string_total_time_is,"%s",string_conversion_timeis);

    if((index_go==1 || index_go_back==1)&& index_pause==0)
    {
            //sab 27/01/2015 deb
        //Affichage du temps du crossfade en cours : l'affichage du temps restant, commence souvent à moins "quelque chose".
        //time_left=((crossfade_done_time-totalTimeCrossfade)/BPS_RATE);
        //affichage_time_format(time_left);
                //sprintf(string_time_left_is,"%s",string_conversion_timeis);

        float f_time_left = totalTimeCrossfade - float (crossfade_done_time) / BPS_RATE ;
        affichage_time_format(f_time_left);
        sprintf(string_time_left_is,"%s",string_conversion_timeis);

        //sab 27/01/2015 fin
    }


//8 MEMOIRES SUIVANTES
    int index_nbre_mem_visues=0;
    //sab 02/03/2014 unsued var int last_mem_visue=0;
    for(int memsearch=position_preset+1; memsearch<10000; memsearch++)
    {
        if(MemoiresExistantes[memsearch]==1 && index_nbre_mem_visues<nbre_memoires_visualisables_en_preset)
        {
            index_nbre_mem_visues++;
            for(int tt=0; tt<4; tt++)
            {
                affichage_time_format(Times_Memoires[memsearch][tt]);
                sprintf(string_time_mem8after[index_nbre_mem_visues][tt],string_conversion_timeis);
            }

            if(index_nbre_mem_visues>=nbre_memoires_visualisables_en_preset)
            {
                break;
            }

        }
    }


///////////Faders
    float in_speed,out_speed, delay_in_speed, delay_out_speed;
    char the_del_in[12];
    char the_in[12];
    char the_del_out[12];
    char the_out[12];
    int  dd=0;
    for(int cmptfader=0; cmptfader<core_user_define_nb_faders; cmptfader++)
    {
        dd=dock_used_by_fader_is[cmptfader];

        if(lfo_speed[cmptfader]<64)
        {
            delay_in_speed=(time_per_dock[cmptfader][dd][0]*(64.0/lfo_speed[cmptfader]));
            delay_out_speed=(time_per_dock[cmptfader][dd][2]*(64.0/lfo_speed[cmptfader]));
            in_speed=(time_per_dock[cmptfader][dd][1]*(64.0/lfo_speed[cmptfader]));
            out_speed=(time_per_dock[cmptfader][dd][3]*(64.0/lfo_speed[cmptfader]));
        }
        else if(lfo_speed[cmptfader]==64)
        {
            delay_in_speed=time_per_dock[cmptfader][dd][0];
            delay_out_speed=time_per_dock[cmptfader][dd][2];
            in_speed=time_per_dock[cmptfader][dd][1];
            out_speed=time_per_dock[cmptfader][dd][3];
        }
        else if(lfo_speed[cmptfader]>64)
        {
            delay_in_speed=((time_per_dock[cmptfader][dd][0]*3)/(lfo_speed[cmptfader]-62));
            delay_out_speed=((time_per_dock[cmptfader][dd][2]*3)/(lfo_speed[cmptfader]-62));
            in_speed=((time_per_dock[cmptfader][dd][1]*3)/(lfo_speed[cmptfader]-62));
            out_speed=((time_per_dock[cmptfader][dd][3]*3)/(lfo_speed[cmptfader]-62));
        }


        affichage_time_format(delay_in_speed);
        sprintf(the_del_in,string_conversion_timeis);
        affichage_time_format(in_speed);
        sprintf(the_in,string_conversion_timeis);
        affichage_time_format(delay_out_speed);
        sprintf(the_del_out,string_conversion_timeis);
        affichage_time_format(out_speed);
        sprintf(the_out,string_conversion_timeis);

        if(delay_in_speed>0 && delay_out_speed>0)
        {
            sprintf(string_time_is_in_the_dock[cmptfader],"%s- IN:%s / %s -OUT:%s ",the_del_in,the_in,the_del_out,the_out);
        }
        else if (delay_in_speed>0 && delay_out_speed==0)
        {
            sprintf(string_time_is_in_the_dock[cmptfader],"%s- IN:%s / OUT:%s ",the_del_in,the_in,the_out);
        }
        else if (delay_in_speed==0 && delay_out_speed>0)
        {
            sprintf(string_time_is_in_the_dock[cmptfader],"IN:%s / %s -OUT:%s ",the_in,the_del_out,the_out);
        }
        else
        {
            sprintf(string_time_is_in_the_dock[cmptfader],"        IN:%s / OUT:%s ",the_in,the_out);
        }

    }
    sprintf(string_dock_col_sel,"Col.%d",dock_color_selected+1);

    for(int o=0; o<8; o++)
    {
        detect_master_lock(o);
    }



//timings grid viewer // concerne la grille d affichage.

    for(int gr=0; gr<23; gr++)
    {
        in_speed=grid_times[grid_selected_for_view][grid_step_view+gr][1];
        affichage_time_format(in_speed);//in
        sprintf(the_in,string_conversion_timeis);
        out_speed= grid_times[grid_selected_for_view][grid_step_view+gr][3];
        affichage_time_format(out_speed);//out
        sprintf(the_out,string_conversion_timeis);
        sprintf(string_grid_view_timing_global[gr],"%s / %s",the_in,the_out);

        delay_in_speed=grid_times[grid_selected_for_view][grid_step_view+gr][0];
        affichage_time_format(delay_in_speed);//in
        sprintf(the_del_in,string_conversion_timeis);
        delay_out_speed= grid_times[grid_selected_for_view][grid_step_view+gr][2];
        affichage_time_format(delay_out_speed);//out
        sprintf(the_del_out,string_conversion_timeis);
        sprintf(string_grid_view_timing_global_delays[gr],"%s / %s",the_del_in,the_del_out);
    }

//audio players
    for(int numero=0; numero<index_nbre_players_visibles; numero++)
    {
        sprintf(string_niveauson[numero],"%0.2f",show_player_niveauson[numero]);
        sprintf(string_pitch[numero],"Pitch %0.2f",show_pitch_value[numero]);
        sprintf(string_pan[numero],"Pan %0.2f",show_pan_value[numero]);
        sprintf(time_is_for_fileCueIn[numero],"In: %.1f",(((float)player_seek_position[numero])/audio_rate[numero]));
        sprintf(time_is_for_fileCueOut[numero],"Out: %.1f",(((float)player_loop_out_position[numero])/audio_rate[numero]));
        sprintf(time_is_for_filePos[numero],"Pos: %.1f",(((float)position_of_file_in_player[numero])/audio_rate[numero]));
        sprintf(time_is_for_fileTotal[numero],"Total: %.1f",(((float)length_of_file_in_player[numero])/audio_rate[numero]));
    }

    return(0);
}



int remember_config_page()
{
    if(index_config_dmx==1)
    {
        config_page_is=1;
    }
    else if(index_config_midi==1)
    {
        config_page_is=2;
    }
    else if(index_config_network==1)
    {
        config_page_is=3;
    }
    else if(index_setup_gfx==1)
    {
        config_page_is=4;
    }
    else if(index_config_arduino==1)
    {
        config_page_is=5;
    }
    else if(index_config_general==1)
    {
        config_page_is=6;
    }
    else if(index_config_core==1)
    {
        config_page_is=7;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sab 08/2016 - HOT KEYS -- DEB ANCRAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// sab 12/08/2016 - Onglet des Hot Keys ////////////////////////////////////////////
    else if(index_config_tab_hotkeys==1)
    {
        config_page_is=8;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sab 08/2016 - HOT KEYS -- FIN ANCRAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return(0);
}


int window_who_is_on_top()
{
    int id_on_top=0;
    for(int i=0; i<63; i++)
    {
        if(window_opened[i]>=900)
        {
            id_on_top=i;
            break;
        }
    }
    return(window_opened[id_on_top]);
}



int substract_a_window(int id)
{
/* christoph 11/04/2014 begin replace */
    int erase_window_opened[64];
    int next_free_pos;
    next_free_pos=0;
//function to rewritte with window_opened as a deque
//All open window are kept open in same order, just taking off the deque "id" window
    for(int old_pos=0; old_pos<63; old_pos++)
    {
        if((window_opened[old_pos]!=id)  //id has been erase from the deque
  && (window_opened[old_pos]!=0)  //shouldn't hapen
  && (next_free_pos<63))    // don't overflow
        {
            erase_window_opened[next_free_pos]=window_opened[old_pos];
            next_free_pos = next_free_pos+1;
        }
    }
    // Clean last unuse new position
    if ((next_free_pos+1)<63)
    {
        for(int i=(next_free_pos+1); i<63; i++)
        {
            erase_window_opened[i]=0;
        }
    }
    //copy
 for(int i=0; i<63; i++) //both are 72 occurences long
    {
  window_opened[i] = erase_window_opened[i];
    }
    //first window get focus
    window_focus_id=window_opened[0];
/* sab 05/03/2014 end replace */

   reset_index_actions();

    switch(id)
    {
    case W_SAVEREPORT:
        index_show_save_load_report=0;
        break;
    case W_TRICHROMY:
        index_trichro_window=0;
        index_affect_color_to_dock=0;
        break;
    case W_NUMPAD:
        index_visual_pad=0;
        break;
    case W_TRACKINGVIDEO:
        index_video_window=0;
        index_affect_video_tracking_to_dock=0;
        break;
    case W_ARTPOLLREPLY:
        index_show_artpoll_reply_content=0;
        break;
    case W_FADERS:
        index_show_faders=0;
        break;
    case W_PATCH:
        index_patch_window=0;
        index_enable_curve_editing=0;
        patch_unselect_all_dimmers();
        index_patch_overide=0;
        index_patch_affect_is_done=0;
        reset_check_grada_overide_dimmers();
        break;
    case W_TIME:
        reset_index_actions();
        index_time=0;
        index_affect_time=0;
        break;
    case W_SEQUENCIEL:
        index_window_sequentiel=0;
        break;
    case W_ASKCONFIRM:
        index_ask_confirm=0;
        reset_indexs_confirmation();
        window_focus_id=previous_window_focus_id;
        break;
    case W_PLOT:
        index_plot_window=0;
        index_plot_send_to_mode=0;
        index_editing_theatre_plan=0;
        break;
    case W_DRAW:
        index_draw_window=0;
        break;
    case W_ECHO:
        index_show_echo_window=0;
        break;
    case W_LIST:
        index_list_projecteurs=0;
        break;
    case W_SAVE:
        index_menu_save=0;
        break;
    case W_MAINMENU:
        index_show_main_menu=0;
        break;
    case W_BANGER:
        index_show_banger_window=0;
        over_banger_event=0;
        over_banger_action=0;
        over_family=0;
        position_mouse_z(0);  //reset
        mouse_level_for_event=mouse_z;
        mouse_level_for_banger=mouse_z;
        break;
    case W_ALARM:
        break;
    case W_AUDIO:
        index_show_audio_window=0;
        reset_audio_indexs_to_dock();
        index_affect_audio_to_dock=0;
        break;
    case W_CFGMENU:
        index_show_config_window=0;
        index_affect_dmxin=0;
        Midi_Faders_Affectation_Type=0;//pour ne pas affecter quoi que ce soit en midi
        Midi_Faders_Affectation_Mode=0;

        remember_config_page();
        //do_affectation_on_midi_affect_itself=0;
        break;
    case W_WIZARD:
        index_show_wizard_window=0;
        break;
    case W_MINIFADERS:
        index_show_minifaders=0;
        break;
    case W_CHASERS:
        index_affect_chaser_to_dock=0;
        index_window_chasers=0;
        break;
    case W_MOVER:
        index_show_mover_window=0;
        index_mouse_is_tracking=0;
        break;
    case W_iCAT:
        index_window_gui_iCat=0;
        break;
    case W_GRID:
        index_grider_window=0;
        index_do_affect_grid_to_fader=0;
        for(int i=0; i<4; i++)
        {
            grid_affect_to_dock[i]=0;
        }
        break;
    case W_WAVE:
        index_wave_menu_window=0;
        index_affect_wave_to_dock=0;
        break;
    case W_MY_WINDOW:
        index_my_window=0;
        break;
    default:
        break;
    }

nbre_fenetre_actives--;

if (nbre_fenetre_actives<=0){nbre_fenetre_actives=0;window_focus_id=0;}

return(0);
}

int clear_ip_artnet()
{
    //ip artnet
    for(int u=0; u<8; u++)
    {
        sprintf(IP_detected_dmxOUT[u],"-");
    }

return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////
int GlobInit()
{
    index_menu_save=1;
    for(int i=0; i<24; i++)
    {
        core_do_calculations[i]=1;
    }

    clear_ip_artnet();
/////////////////////////////////////////
    if(specify_who_to_save_load[0]==1)//memoires ///////////////////////////////////
    {


        for (int m=0; m<9999; m++)
        {
            MemoiresExistantes[m]=0;
            MemoiresDetruites[m]=0;
            MemoiresExclues[m]=0;
            nbre_de_mems_manipulees=0;
//sab 02/03/2014 sprintf --> strcpy
            strcpy(descriptif_memoires[m],"");
            strcpy(annotation_memoires[m],"");

            descriptif_memoires[m][24]='\n';
            annotation_memoires[m][24]='\n';
            for(int i=0; i<514; i++)
            {
                Memoires[m][i]=0;
            }
        }
        position_onstage=10;
        position_preset=10;
        MemoiresExistantes[10]=1;
    }

    if(specify_who_to_save_load[1]==1)//memoires times /////////////////////////////
    {
        for (int m=0; m<9999; m++)
        {
            Times_Memoires[m][0]=0.0;
            Times_Memoires[m][2]=0.0;
            Times_Memoires[m][1]=default_time;
            Times_Memoires[m][3]=default_time;
        }
    }

    if(specify_who_to_save_load[2]==1)//memoires links//////////////////////////////
    {
        for (int m=0; m<9999; m++)
        {
            Links_Memoires[m]=0;
        }
    }

    if(specify_who_to_save_load[3]==1)//memoires banger in mem//////////////////////
    {
        for (int m=0; m<9999; m++)
        {
            Banger_Memoire[m]=0;
        }
    }


    if(specify_who_to_save_load[4]==1)//memoires  ratio manuel//////////////////////
    {
        for (int m=0; m<9999; m++)
        {
            ratio_cross_manuel[m]=0;
        }
    }




    if(specify_who_to_save_load[5]==1)//channels LIST///////////////////////////////
    {
        for(int io=0; io<514; io++)
        {
//sab 02/03/2014 sprintf(descriptif_projecteurs[io],"");
            strcpy(descriptif_projecteurs[io],"");

            descriptif_projecteurs[io][24]='\n';
            previous_state_of_outputted_channels[io]=-1;//18/12/14 christoph pour rafraichissement macros a ouv whitecat
            for(int macr=0; macr<4; macr++)
            {
                macro_channel_on[io][macr]=0;
                channel_macro_reaction[io][macr]=0;
                channel_macro_action[io][macr]=0;
                channel_macro_val[io][macr][0]=0;
                channel_macro_val[io][macr][1]=0;
            }

            for(int view_is=0; view_is<nbre_de_vues_circuits; view_is++)
            {
                Channel_View_ROUTING[view_is][io]=0;
            }
        }
        line_list_is=0;



        for(int i=0; i<nbre_de_vues_circuits; i++)
        {
            sprintf(channel_view_Name[i],"CHANNEL VIEW %d", i+1);
            channel_view_link_type[i]=0;
            channel_view_link_ref[i]=0;
            sprintf(channel_view_Name[i],"CHANNEL VIEW %d",i+1);
            channel_number_in_View[i]=0;
            channel_number_of_lines[i]=0;
            Channel_View_MODE[i]=0;
        }
        ClassicalChannelView=1;
        sprintf(channel_view_Name[0],"PATCHED CHANNELS");
//fin list
    }

    if(specify_who_to_save_load[6]==1)//channels directCh///////////////////////////
    {
        for(int fd=0; fd<48; fd++)
        {
            for(int dk=0; dk<6; dk++)
            {
                if(DockTypeIs[fd][dk]==10)
                {
                    DockTypeIs[fd][dk]=9;
                }
            }
        }
    }


    if(specify_who_to_save_load[7]==1)//channels freeze exclude/////////////////////////////
    {
        for(int io=0; io<514; io++)
        {
            freeze_array[io]=0;
            freeze_state[io]=0;
            Channels_excluded_from_grand_master[io]=0;
        }
    }


    if(specify_who_to_save_load[8]==1)//patch  circuits/////////////////////////////
    {
        for(int i=0; i<514; i++)
        {
            Patch[i]=i;
            for(int llo=0; llo<4; llo++)
            {
                show_first_dim_array[i][llo]=0;
            }
            show_first_dim_array[i][0]=i;
        }
    }

    if(specify_who_to_save_load[9]==1)//patch HTP/LTP//////////////////////////////
    {
        for(int i=0; i<514; i++)
        {
            dimmer_type[i]=0;
        }
        generate_channel_view_list_from_patched_circuits();
    }

    if(specify_who_to_save_load[10]==1)//patch curves///////////////////////////////
    {
        for(int i=0; i<514; i++)
        {
            curves[i]=0;
        }
    }

    if(specify_who_to_save_load[11]==1)///banger////////////////////////////////////
    {
        for (int bg=0; bg<127; bg++) //127 max=126++
        {
            clear_banger(bg);
        }
    }


    if(specify_who_to_save_load[12]==1)//faders contents////////////////////////////
    {
        for (int in=0; in<48; in++)
        {
            Fader[in]=0;
            Fader_dampered[in].fix_all_damper_state_value(Fader[in]);
            Fader_dampered[in].set_target_val(Fader[in]);
            Fader_dampered[in].set_damper_decay(1.0);
            Fader_dampered[in].set_damper_dt(0.1);
            FaderLocked[in]=0;
            LockFader_is_FullLevel[in]=0;
            StateOfFaderBeforeLock[in]=0;
            fader_mode_with_buffers[in]=0;//fx
            fader_fx_route[in]=0;
            autolaunch[in]=0;

            for(int dd=0; dd<6; dd++)
            {
                DockTypeIs[in][dd]=9;
                DockIsSelected[in][dd]=0;//alls dock not selected
                DockHasMem[in][dd]=0;
//sab 02/03/2014 sprintf(DockName[in][dd],"");
                strcpy(DockName[in][dd],"");

                DockName[in][dd][24]='\n';
                DrawAffectedToDck[in][dd]=0;
                for(int c=0; c<514; c++)
                {
                    FaderDockContains[in][dd][c]=0;
                }
            }
            DockIsSelected[in][0]=1;//dock 1 enclenché
            dock_used_by_fader_is[in]=0;
        }
    }


    if(specify_who_to_save_load[13]==1)//faders lfos  + times//////////////////////
    {
        for (int in=0; in<48; in++)
        {
            lfo_mode_is[in]=0;
            lfo_cycle_is_on[in]=0;
            lfo_cycle_steps[in]=0;
            lfo_running_is_upward[in]=0;
            lfo_do_next_step[in][0]=0;
            lfo_do_next_step[in][1]=0; // 0 backward 1 forward
            StopPosOn[in]=0;
            LevelStopPos[in]=0;
            PreviousLevelStopPos[in]=0;//pour banger back
            ActionnateStopOn[in]=0;//activation du mode stop on
            lfo_speed[in]=64;
            do_light_setpos[in]=0;
            FaderIsFlash[in]=0;
            FaderIsFlashBefore[in]=0;
            LevelFaderBeforeFlash[in]=0;
            for(int dd=0; dd<6; dd++)
            {
                is_dock_for_lfo_selected[in][dd]=0;
                DockHasMem[in][dd]=0;
                time_per_dock[in][dd][0]=0.0;
                time_per_dock[in][dd][2]=0.0;
                time_per_dock[in][dd][1]=default_time; //IN default
                time_per_dock[in][dd][3]=default_time; //OUT default
            }
        }
    }


    if(specify_who_to_save_load[14]==1)//faders curves//////////////////////////////
    {
        for (int in=0; in<48; in++)
        {
            FaderCurves[in]=0;
        }
    }

    if(specify_who_to_save_load[15]==1)//faders Presets locks minifaders pst////////
    {
        for (int in=0; in<48; in++)
        {
            minifaders_selected[in]=0;
//dock presets
            for(int dp=0; dp<8; dp++)
            {
                FaderLocked_Preset[dp][in]=0;
                StateOfFaderBeforeLock_Preset[dp][in]=0;
                LockFader_is_FullLevel_Preset[dp][in]=0;
                master_lock_preset[dp]=0;
                minifaders_preset_selection[dp][in]=0;
            }
        }
        position_minifader_selected=0;
    }

    if(specify_who_to_save_load[16]==1)//chasers////////////////////////////////////
    {
        for (int l=0; l<128; l++)
        {
//sab 02/03/2014 sprintf(chaser_name[l],"");
            strcpy(chaser_name[l],"");

            time_unit[l]=1.0;
            chaser_is_playing[l]=0;
            chaser_is_in_loop[l]=0;
            chaser_aller_retour[l]=0;
            chaser_step_is[l]=0;
            chaser_way[l]=0;
            chaser_begin_step_is[l]=0;
            chaser_end_step_is[l]=35;
            position_affichage_track_num[l]=0;
            chaser_step_launchpad[l]=0;
            view_chaser_affected_to_fader[l][0]=999;
            view_chaser_affected_to_fader[l][1]=999;
            index_slave_chaser_to_accelerometre[l]=0;
            for(int tr=0; tr<nbre_tracks_par_chaser; tr++)
            {
                track_is_on[l][tr]=0;
                track_level[l][tr]=127;
                TrackTypeIs[l][tr]=0;
                TrackHasMem[l][tr]=0;
//sab 02/03/2014 sprintf(chaser_track_name[l][tr],"");
                strcpy(chaser_track_name[l][tr],"");

                chaser_track_name[l][tr][24]='\n';
                for(int ste=0; ste<nbre_de_cases_par_track; ste++)
                {
                    chaser_step_operation[l][tr][ste]=0;
                }
            }
        }
    }



    if(specify_who_to_save_load[17]==1)//midi affect////////////////////////////////
    {
        for(int mi=0; mi<3072; mi++)
        {
            miditable[0][mi]=999;
            miditable[1][mi]=999;
            miditable[2][mi]=999;
            midi_levels[mi]=0;
            midi_send_out[mi]=0;//atribué ou pas
            index_send_midi_out[mi]=0;
            is_raccrochage_midi_remote[mi]=0;
            val_raccrochage_midi[mi]=0;
        }
    }

    if(specify_who_to_save_load[18]==1)//midi cheat////////////////////////////////
    {
        for (int li=0; li<16; li++)
        {
            for(int u=0; u<128; u++)
            {
                midi_change_vel_type[li][u]=0;
                midi_recognize_on_off[li][u]=0;
            }
        }

        //midi clock personnal
        bpm_personnal[0]=160;
        bpm_personnal[1]=140;
        bpm_personnal[2]=120;
        bpm_personnal[3]=100;
        bpm_personnal[4]=90;
        bpm_personnal[5]=80;
        bpm_personnal[6]=70;
        bpm_personnal[7]=60;
        bpm_personnal[8]=50;
        bpm_personnal[9]=40;
        bpm_personnal[10]=30;
        bpm_personnal[11]=20;
        bpm_personnal[12]=10;
        bpm_personnal[13]=5;
        bpm_personnal[14]=2;
        bpm_personnal[15]=1;
    }


    if(specify_who_to_save_load[19]==1)//trichro/////////////////////////////////////
    {
        for(int i=0; i<8; i++)
        {
            colorpreset_linked_to_dock[i][0]=-1;
            colorpreset_linked_to_dock[i][1]=-1;
            dock_color_type[i]=0;
            angle_hue_par_colordock[i]=0.1;
            picker_trichro[i][0]=0;
            picker_trichro[i][1]=0;
            picker_trichro[i][2]=0;
            picker_trichro[i][3]=0;
            for (int c=0; c<514; c++)
            {
                dock_color_channels[i][0][c]=0;
                dock_color_channels[i][1][c]=0;
                dock_color_channels[i][2][c]=0;
                dock_color_channels[i][3][c]=0;
            }
        }
    }


    if(specify_who_to_save_load[20]==1)//video tracking//////////////////////////////
    {
        ocv_calcul_mode=1;
        tracking_dock_selected=0;
        for (int c=0; c<6; c++)
        {
            set_to_default_this_tracker(c);
            tracker_clearmode=0;

            for(int u=0; u<12; u++)
            {
                tracker_level[c][u]=0;
                tracking_spaces_on_off[c][u]=0;
            }
        }
    }




    if(specify_who_to_save_load[21]==1)//arduino/////////////////////////////////////
    {

        for(int i=0; i<digital_limit; i++)
        {
            arduino_digital_type[i]=0;
            arduino_digital_function_input[i][0]=0;
            arduino_digital_function_input[i][1]=0;
            arduino_digital_function_output[i][0]=0;
            arduino_digital_function_output[i][1]=0;
        }
        for(int i=0; i<analog_limit; i++)
        {
            arduino_analog_function_input[i]=0;
            arduino_analog_attribution_input[i]=0;
        }

        arduino_baud_rate0=14400;
        arduino_max_digital=13;
        arduino_max_analog=5;

    }

    if(specify_who_to_save_load[22]==1)//AudioConf////////////////////////////////////////
    {
        //
        sprintf(audio_folder,"demo");
        for(int i=0; i<4; i++)
        {
            audio_autoload[i]=0;
            audio_autopause[i]=0;
            player_has_file_coming_from_pos[i]=0;
            player_position_on_save[i]=0;
        }
    }

    if(specify_who_to_save_load[23]==1)//iCat////////////////////////////////////////
    {
        for(int nbp=0; nbp<8; nbp++)
        {
            clear_iCat_page(nbp);
        }
    }

    if(specify_who_to_save_load[24]==1)//windows////////////////////////////////////
    {
        index_trichro_window=0;
        index_video_window=0;
        index_video_window=0;
        index_patch_window=0;
        index_type=0;
        index_visual_pad=0;
        index_time=0;
        index_window_sequentiel=0;
        index_config_midi=0;
        midi_page=0;
        index_list_projecteurs=0;
        index_menu_save=0;
        scroll_faderspace=0;
        index_show_faders=0;
        index_config_general=0;
        index_show_audio_window=0;
        index_config_network=0;
        index_show_config_window=0;
        index_show_wizard_window=0;
        index_show_minifaders=0;
        index_window_chasers=0;
        config_page_is=0;

        index_show_mover_window=0;
        index_window_gui_iCat=0;
        window_focus_id=0;
        recall_windows_focus_id=0;
        config_page_is=0;
        index_config_dmx=1;
        index_config_arduino=0;
        reset_window_positions();
        reset_window_opened_indexes();

    }


    if(specify_who_to_save_load[25]==1)//color profile//////////////////////////////
    {
        config_color_style_is=0;
        LoadWhiteCatColorProfil();
    }


    if(specify_who_to_save_load[26]==1)//mapping keyboard///////////////////////////
    {
        for(int map=0; map<128; map++)
        {
            mapping_temporaire[map]=999;
        }
    }


    if(specify_who_to_save_load[27]==1)//indexes////////////////////////////////////
    {
//une partie des indexes mis dans les windows
        index_allow_grand_master=1;
        config_color_style_is=0;
        index_link_is_on=1;
        index_decay_tracker=0;
        cheat_key_off=0;
        index_banger_is_on=1;
        index_banger_selected=0;
        index_show_banger_window=0;
        index_allow_sunlite_dmxIN=0;//sunlite
        niveauGMaster=255;//grand master
        index_allow_multicore=0;
        allow_artnet_in=0;
        index_setup_gfx=0;
        core_to_assign=0;

        enable_launchpad=0;
        nbre_track_visualisables=8;
        chaser_operator_is=0;
        chaser_selected=0;
        index_affichage_digit_time_unit=2;
        launchpad_chaser_mode=0;
        index_enable_edit_chaser=0;
        chaser_midi_rows=8;
        line_list_is=0;
        iCatPageis=0;

        surface_type=0;//icat
        L_tablier_iCat=240;
        H_tablier_iCat=160;
        grid_icat_modulo=5;
    }


//manque MOVER 28


    if(specify_who_to_save_load[29]==1)//Grid////////////////////////////////////
    {
//reset des grilles
        for(int y=0; y<127; y++)
        {
            clear_a_grid(y);
        }
        //sab 02/03/2014 unsued var int grider_begin_channel_is=1;
        //sab 02/03/2014 unsued var int grider_nb_col=12;
        //sab 02/03/2014 unsued var int grider_nb_row=10;
        index_clear_a_grid_step=0;
        index_clear_a_grid=0;
        grid_to_clear=0;
        step_grid_to_clear=0;
        index_clear_a_grid_serie_step=0;
        index_for_grid_stepto=0;
        index_for_copy_grid=0;
        destination_grid_for_copy=0;
        destination_step_for_copy=0;
        index_grid_tostep_or_not=0;
        from_gridstep_to=0;
        gridplayer_to_affect_is=-1;
//reset des players
        for(int pl=0; pl<4; pl++)
        {
            index_grider_selected[pl]=1;
            index_grider_step_is[pl]=1;
            grider_is_playing[pl]=0;
            grider_autostopmode[pl]=0;
            grider_goto_mode[pl]=1;
            grider_seekto_mode[pl]=1;
            grider_stoplay_mode[pl]=1;
            to_step_editing_mode[pl]=0;
            index_StepTo[pl]=0;
            index_Grid_copyto[pl][0]=0;//0 grid 1 step
            index_Grid_copyto[pl][1]=0;
            grid_player_slave[pl]=0;
            grid_crossfade_speed[pl]=64;
            grid_niveauX1[pl]=255;
            grid_niveauX2[pl]=0;
            grid_floatX1[pl]=255.0;
            grid_floatX2[pl]=0;
            GplSnapFader[pl]=0;
        }
    }

    if(specify_who_to_save_load[30]==1)//Grid in mems////////////////////////////////////
    {
        for (int m=0; m<10000; m++)
        {
            set_from_seq_gridplayer1_next_step[m]=-1;
        }
    }


    if(specify_who_to_save_load[31]==1)//PLOT////////////////////////////////////
    {
        size_symbol[0]=0.3;//pc500
        sprintf(symbol_nickname[0],"PC 650w");
        plot_ecartement_legende[0]=40;
        size_symbol[1]=0.5;//pc1Kw
        sprintf(symbol_nickname[1],"PC 1kw");
        plot_ecartement_legende[1]=40;
        size_symbol[2]=0.7;//pc2kw
        sprintf(symbol_nickname[2],"PC 2kw");
        plot_ecartement_legende[2]=40;
        size_symbol[3]=0.5;//fresnel 1kw
        sprintf(symbol_nickname[3],"Fresnel 1kw");
        plot_ecartement_legende[3]=40;
        size_symbol[4]=0.7;//fresnel 2Kw
        sprintf(symbol_nickname[4],"Fresnel 2kw");
        plot_ecartement_legende[4]=40;
        size_symbol[5]=1.0;//fersnel 5kw
        sprintf(symbol_nickname[5],"Fresnel 5kw");
        plot_ecartement_legende[5]=40;
        size_symbol[6]=0.4;//source four
        sprintf(symbol_nickname[6],"SourceFour 26°");
        plot_ecartement_legende[6]=80;
        size_symbol[7]=0.4;//source four
        sprintf(symbol_nickname[7],"Source Four 36°");
        plot_ecartement_legende[7]=80;
        size_symbol[8]=0.4;//source four
        sprintf(symbol_nickname[8],"Source Four 50°");
        plot_ecartement_legende[8]=80;
        size_symbol[9]=0.7;//dec 1kw longue
        sprintf(symbol_nickname[9],"Dec 611SX");
        plot_ecartement_legende[9]=80;
        size_symbol[10]=0.7;//dec 1Kw  med
        sprintf(symbol_nickname[10],"Dec 614SX");
        plot_ecartement_legende[10]=80;
        size_symbol[11]=0.7;//dec 1kw   wide
        sprintf(symbol_nickname[11],"Dec 613SX");
        plot_ecartement_legende[11]=80;
        size_symbol[12]=1.0;//dec 2kw  longue
        sprintf(symbol_nickname[12],"Dec 711S");
        plot_ecartement_legende[12]=80;
        size_symbol[13]=1.0;//dec 2Kw  med
        sprintf(symbol_nickname[13],"Dec 714SX");
        plot_ecartement_legende[13]=80;
        size_symbol[14]=1.0;//dec 2kw   wide
        sprintf(symbol_nickname[14],"Dec 713SX");
        plot_ecartement_legende[14]=80;
        size_symbol[15]=0.8;//Par64 cp60
        sprintf(symbol_nickname[15],"Par64 CP60");
        plot_ecartement_legende[15]=40;
        size_symbol[16]=0.8;//Par64 cp61
        sprintf(symbol_nickname[16],"Par64 CP61");
        plot_ecartement_legende[16]=40;
        size_symbol[17]=0.8;//Par64 cp62
        sprintf(symbol_nickname[17],"Par64 CP62");
        plot_ecartement_legende[17]=40;
        size_symbol[18]=0.8;//Par64 cp95
        sprintf(symbol_nickname[18],"Par64 CP95");
        plot_ecartement_legende[18]=40;
        size_symbol[19]=0.5;//Par56 cp60
        sprintf(symbol_nickname[19],"Par56 NSP");
        plot_ecartement_legende[19]=40;
        size_symbol[20]=0.5;//Par56 cp61
        sprintf(symbol_nickname[20],"Par56 MFL");
        plot_ecartement_legende[20]=40;
        size_symbol[21]=0.5;//Par56 cp62
        sprintf(symbol_nickname[21],"Par56 WFL");
        plot_ecartement_legende[21]=40;
        size_symbol[22]=0.4;//Par36
        sprintf(symbol_nickname[22],"Par36");
        plot_ecartement_legende[22]=40;
        size_symbol[23]=0.3;//Par20
        sprintf(symbol_nickname[23],"Par20");
        plot_ecartement_legende[23]=40;
        size_symbol[24]=0.2;//Par16
        sprintf(symbol_nickname[24],"Par16");
        plot_ecartement_legende[24]=40;
        size_symbol[25]=1.0;//assy
        sprintf(symbol_nickname[25],"Cycliode");
        plot_ecartement_legende[25]=40;
        size_symbol[26]=1.0;//sym
        sprintf(symbol_nickname[26],"Horiziode");
        plot_ecartement_legende[26]=40;
        size_symbol[27]=0.5;//hallogene chantier
        sprintf(symbol_nickname[27],"500W Floodlight");
        plot_ecartement_legende[27]=40;
        size_symbol[28]=0.5;//BT250
        sprintf(symbol_nickname[28],"BT 250w");
        plot_ecartement_legende[28]=40;
        size_symbol[29]=0.8;//BT500
        sprintf(symbol_nickname[29],"BT 500w");
        plot_ecartement_legende[29]=40;
        size_symbol[30]=0.5;//rampe T8
        sprintf(symbol_nickname[30],"T8");
        plot_ecartement_legende[30]=20;
        size_symbol[31]=0.5;//Blinder
        sprintf(symbol_nickname[31],"Blinder");
        plot_ecartement_legende[41]=40;
        size_symbol[32]=0.8;//Svob
        sprintf(symbol_nickname[32],"Svoboda");
        plot_ecartement_legende[32]=60;
        size_symbol[33]=0.7;//ACL
        sprintf(symbol_nickname[33],"ACL");
        plot_ecartement_legende[33]=40;
        size_symbol[34]=0.7;//FLUOS
        sprintf(symbol_nickname[34],"Fluorescent 60cm");
        plot_ecartement_legende[34]=15;
        size_symbol[35]=0.7;//FLUOS
        sprintf(symbol_nickname[35],"Fluorescent 120cm");
        plot_ecartement_legende[35]=15;
        size_symbol[36]=0.6;//Follow Spot
        sprintf(symbol_nickname[36],"Follow Spot 575w");
        plot_ecartement_legende[36]=90;
        size_symbol[37]=0.8;//Follow Spot
        sprintf(symbol_nickname[37],"Follow Spot 1200w");
        plot_ecartement_legende[37]=110;
        size_symbol[38]=0.7;//VP
        sprintf(symbol_nickname[38],"Video Projector 1");
        plot_ecartement_legende[38]=40;
        size_symbol[39]=0.8;//VP
        sprintf(symbol_nickname[39],"Video Projector 2");
        plot_ecartement_legende[39]=75;
        size_symbol[40]=0.8;//Slide Projector
        sprintf(symbol_nickname[40],"Slide Projector");
        plot_ecartement_legende[40]=40;
        size_symbol[40]=0.9;//rétro projecteur
        sprintf(symbol_nickname[41],"OverHead");
        plot_ecartement_legende[41]=60;


        size_symbol[42]=0.7;//accessoire
        sprintf(symbol_nickname[42],"BarnDoors");
        plot_ecartement_legende[42]=30;
        size_symbol[43]=0.4;//accessoire
        sprintf(symbol_nickname[43],"TopHat");
        plot_ecartement_legende[43]=20;
        size_symbol[44]=0.7;//accessoire
        sprintf(symbol_nickname[44],"Color Extender");
        plot_ecartement_legende[44]=30;
        size_symbol[45]=0.7;//accessoire
        sprintf(symbol_nickname[45],"Color Changer");
        plot_ecartement_legende[45]=15;
        size_symbol[46]=0.7;//accessoire
        sprintf(symbol_nickname[46],"Louvers");
        plot_ecartement_legende[46]=15;

        size_symbol[47]=0.3;//accessoire
        sprintf(symbol_nickname[47],"Iris");
        plot_ecartement_legende[47]=20;
        size_symbol[48]=0.3;//accessoire
        sprintf(symbol_nickname[48],"Gobo Holder");
        plot_ecartement_legende[48]=70;
        size_symbol[49]=0.3;//accessoire
        sprintf(symbol_nickname[49],"Shutter");
        plot_ecartement_legende[49]=50;
        size_symbol[50]=0.3;//accessoire
        sprintf(symbol_nickname[50],"Motorized mirror");
        plot_ecartement_legende[50]=50;

        size_symbol[51]=0.5;//Machine à fumée
        sprintf(symbol_nickname[51],"Smoke machine");
        plot_ecartement_legende[51]=30;
        size_symbol[52]=0.5;//Machine à fumée
        sprintf(symbol_nickname[52],"Fog machine");
        plot_ecartement_legende[52]=20;

        size_symbol[53]=0.5;//Dimmer
        sprintf(symbol_nickname[53],"Dimmer Plug");
        plot_ecartement_legende[53]=60;
        size_symbol[54]=0.5;//Direct
        sprintf(symbol_nickname[54],"Direct Plug");
        plot_ecartement_legende[54]=40;
        size_symbol[55]=0.5;//Services
        sprintf(symbol_nickname[55],"Running Light");
        plot_ecartement_legende[55]=40;

        size_symbol[56]=0.7;//platine de sol
        sprintf(symbol_nickname[56],"Mounting Plate");
        plot_ecartement_legende[56]=60;
        size_symbol[57]=0.5;//petit pied
        sprintf(symbol_nickname[57],"Simple Little Stand");
        plot_ecartement_legende[57]=200;
        size_symbol[58]=0.5;//grand pied
        sprintf(symbol_nickname[58],"Big Stand 3,5m");
        plot_ecartement_legende[58]=200;
        size_symbol[59]=0.5;//Barre de couplage
        sprintf(symbol_nickname[59],"Cross Bar");
        plot_ecartement_legende[59]=20;
        size_symbol[60]=0.7;//échelle
        sprintf(symbol_nickname[60],"Ladder");
        plot_ecartement_legende[60]=240;

        size_symbol[61]=0.5;//Pont solo 50
        sprintf(symbol_nickname[61],"Truss 1m diam 50cm");
        plot_ecartement_legende[61]=92;
        size_symbol[62]=0.5;//Pont 3m 50
        sprintf(symbol_nickname[62],"Truss 3m diam 50cm");
        plot_ecartement_legende[62]=292;
        size_symbol[63]=0.5;//Pont solo 50
        sprintf(symbol_nickname[63],"Truss Junction diam 50cm");
        plot_ecartement_legende[63]=42;
        size_symbol[64]=0.5;//Pont solo 50
        sprintf(symbol_nickname[64],"Truss 1m diam 30cm");
        plot_ecartement_legende[64]=92;
        size_symbol[65]=0.5;//Pont 3m 50
        sprintf(symbol_nickname[65],"Truss 3m diam 30cm");
        plot_ecartement_legende[65]=292;
        size_symbol[66]=0.5;//Pont solo 50
        sprintf(symbol_nickname[66],"Truss Junction diam 30cm");
        plot_ecartement_legende[66]=22;



        sprintf(shape_nickname[0],"Curtain");
        sprintf(shape_nickname[1],"Plain Line");
        sprintf(shape_nickname[2],"Stippled Lines 1");
        sprintf(shape_nickname[3],"Stippled Lines 2");
        sprintf(shape_nickname[4],"Stippled Lines 3");
        sprintf(shape_nickname[5],"Stippled Lines 4");
        sprintf(shape_nickname[6],"Stippled Lines 5");
        sprintf(shape_nickname[7],"Rectangle");
        sprintf(shape_nickname[8],"Circle");
        sprintf(shape_nickname[9],"Circle Slice");
        sprintf(shape_nickname[10],"Polygon");
        sprintf(shape_nickname[11],"Text");




        for(int calc=0; calc<4; calc++)
        {
            nbre_symbols_on_plot[calc]=0;
            for (int s=0; s<nbre_symbol_per_layer; s++)
            {
                symbol_type[calc][s]=999;
                symbol_is_selected[calc][s]=0;
                angle_symbol[calc][s]=0.0;
                pos_symbol[calc][s][0]=0;
                pos_symbol[calc][s][1]=0;
                stored_plot_position[s][0]=0;
                stored_plot_position[s][1]=0;
                symbol_channel_is[calc][s]=0;
                symbol_dimmer_is[calc][s]=0;
                gelat[calc][s][0]=0;
                gelat[calc][s][1]=0;
                gelat[calc][s][2]=0;
                gelat_family[calc][s][0]=0;
                gelat_family[calc][s][1]=0;
                gelat_family[calc][s][2]=0;
                symbol_is_linked_to[calc][s]=0;
//sab 02/23/2014 warning: zero-length ms_printf format string [-Wformat-zero-length]|
//correction sprintf --> strcpy
                strcpy(symbol_note[calc][s][0],"");
                strcpy(symbol_note[calc][s][1],"");
                strcpy(symbol_note[calc][s][2],"");
                strcpy(symbol_note[calc][s][3],"");

//relatif_plot_xy[4][nbre_symbol_per_layer][4][2];//calc / Symbols / Famille / X Y
                for(int opt=0; opt<5; opt++)
                {
                    relatif_plot_xy[calc][s][opt][0]=0;
                    relatif_plot_xy[calc][s][opt][1]=0;
                }
            }
        }
        for(int t=0; t<5; t++)
        {
            adjust_xy_type[t]=0;
        }
        adjust_xy_type[0]=1;
        position_relative_plan_theatre[0]=(x_plot+position_plan_x);
        position_relative_plan_theatre[1]=(y_plot+position_plan_y);


//shapes
        nbre_shapes_on_plot=0;
        number_of_shapes_groups=0;
        for (int s=0; s<nbre_symbol_per_layer; s++)
        {
            shape_selected[s]=0;
            shape_type[s]=0;
            shape_attributes[s][0]=10.0;//size G
            shape_attributes[s][1]=0.0;//angle rot
            shape_attributes[s][2]=1.0;//size x
            shape_attributes[s][3]=10.0;//size y
            shape_attributes[s][4]=0.1;//opening angle
            shape_groups[s]=0;
            for(int i=0; i<4; i++)
            {
                shape_position[s][i]=0;//pour les lignes
            }
//sab 02/03/2014 sprintf(shape_legend_name[s],"");
            strcpy(shape_legend_name[s],"");

            shape_legend_name[s][24]='\0';
            shape_relativ_position_legend_name[s][0]=0;
            shape_relativ_position_legend_name[s][1]=0;
            shape_color_type[s]=0;
        }

//legende

        clear_plot_legend();
        generate_channel_view_list_from_patched_circuits();

    }



    if(specify_who_to_save_load[32]==1)//DRAW
    {
        for(int p=0; p<6; p++)
        {
            clear_draw_preset(p);
        }
    }

    if(specify_who_to_save_load[33]==1)//ECHO
    {
        for(int p=0; p<24; p++)
        {
            clear_echo_preset(p);
        }
    }

   //////////////WAVE//////////////////////////
   for(int i=0;i<26;i++)
   {
           // Wave_Dampered[i].fix_all_damper_state_value(Fader[in]);
           // Wave_Dampered[i].set_target_val(Fader[in]);
            Wave_Dampered[i].set_damper_decay(1.0);
            Wave_Dampered[i].set_damper_dt(0.1);
   }


///////////////////////////////////////////////////////////////

    if(specify_who_to_save_load[35]==1)//preset de sauvegarde personnalises
    {
        for(int p=0; p<80; p++)
        {
            for(int o=0; o<3; o++)
            {
                preset_specify_who_to_save_load[p][o]=0;
            }
        }
        for(int i=0; i<36; i++)
        {
            specify_who_to_save_PDF[i]=0;
        }
    }



////////////////////////////////////////////
///////////REINIT DES TABLEAUX TEMP/////////////
    for(int i=0; i<514; i++)
    {
        bufferSaisie[i]=0;
        bufferFaders[i]=0;
        bufferBlind[i]=0;
        Selected_Channel[i]=0;
        Dimmers_selected[i]=0;
        DmxBlock[i]=0;
        MergerArray[i]=0;
        buffer_tracker[i]=0;
        highest_level_comes_from_fader[i]=0;
        show_who_is_in_FADER_DOCK[i]=0;
    }

    bool show_is_virgin_=1;
    for(int iu=0; iu<72; iu++)
    {
        if(specify_who_to_save_load[iu]==0)
        {
            show_is_virgin_=0;
            break;
        }
    }

    if(show_is_virgin_==1)
    {
        sprintf(my_show_is_coming_from,"A complete New show");
        write_show_coming_from();
        set_all_saves_indexes_at(1);
    }
/////////////////////////////////////////////
//sauvegarde chargement, en tout dernier
    //set_all_saves_indexes_at(1); // a cassé le chargement sélectif 3 mars 2016
    index_menu_save=0;
    substract_a_window(W_SAVE);
    return(0);
}

int reset_show()
{
    set_all_saves_indexes_at(1);
    clear_report_string();
    GlobInit();
    return(0);
}


int substract_channel_selection_to_layers_plot()
{
int tmp_ch=0;
for(int l=0;l<4;l++)
{
for(int i=0;i<=nbre_symbols_on_plot[l];i++)
{
tmp_ch=symbol_channel_is[l][i];
if(Selected_Channel[tmp_ch]==0)
{
symbol_is_selected[l][i]= 0;
}
}
}
return(0);
}
