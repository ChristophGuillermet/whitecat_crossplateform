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

* \file procs_visuels_rebuild1.cpp
* \brief {Redraw fonctions}
* \author Christoph Guillermet
* \version {0.8.6}
* \date {28/04/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions d'actualisation des différents process dans l'interface graphique
*
*   Redraw fonctions in the GUI for the differents core process
*
**/

//sab 29/05/2013 deb ------------------------------------------------------
bool wc_askConfirmWindowIsOpen()
{
    bool f_bool = false;
    for(int i=0; i<63; i++)
    {
        if (window_opened[i]==W_ASKCONFIRM)
        {
            f_bool = true;
            break;
        }
    }
    return f_bool;
}
//sab 29/05/2013 fin ------------------------------------------------------

int detection_over_window()
{
    bool stop_detect=0;
    int window_is=0;
    if(mouse_y>hauteur_ChannelMenu )
    {
        for(int i=0; i<63; i++)
        {
            switch(window_opened[i])
            {
            case W_SAVEREPORT:
                //if( mouse_x>= report_SL_X && mouse_x<= report_SL_X+350 && mouse_y>=report_SL_Y && mouse_y<=report_SL_Y+160)
                if(mouseover_Show_report_save_load ())
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_TRICHROMY:
                if( mouse_x>= xtrichro_window-158 && mouse_x<= xtrichro_window+157+(show_gel_list*gel_size_window) && mouse_y>=ytrichro_window-206  && mouse_y<= ytrichro_window+344)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_NUMPAD:
                if( mouse_x>= xnum_window && mouse_x<= xnum_window+480 && mouse_y>=ynum_window  && mouse_y<= ynum_window+300)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_TRACKINGVIDEO:
                if( mouse_x>= videoX && mouse_x<= videoX+video_size_x+35 && mouse_y>=videoY  && mouse_y<= videoY+video_size_y+500)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_ARTPOLLREPLY:
                if ( mouse_x>=artpoll_replyX && mouse_x<=artpoll_replyX+500 && mouse_y>=artpoll_replyY && mouse_y<=artpoll_replyY+400)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_FADERS :
                if(mouse_y>(YFader-80) && mouse_x<LargeurEspaceFaderSize)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_PATCH:
                if( (index_menu_curve==0 && mouse_x>=xpatch_window && mouse_x<=xpatch_window+450 && mouse_y>=ypatch_window && mouse_y<=ypatch_window+600)
                        || ( index_menu_curve==1 && mouse_x>=xpatch_window && mouse_x<=xpatch_window+450+320 && mouse_y>=ypatch_window && mouse_y<=ypatch_window+600))
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_TIME:
                if (mouse_x>=xtime_window && mouse_x<=xtime_window+370 && mouse_y>=ytime_window && mouse_y<=ytime_window+300)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_SEQUENCIEL:
                if(mouse_x>=xseq_window && mouse_x<=xseq_window+670+(260*show_gridplayer_in_seq) && mouse_y>=yseq_window && mouse_y<=yseq_window+hauteur_globale_sequenciel)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_ASKCONFIRM:
                if(mouse_x>=XConfirm && mouse_x<=XConfirm+400 && mouse_y>=YConfirm && mouse_y<=YConfirm+100 )
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_PLOT:
                if(mouse_x>=x_plot && mouse_x<=x_plot+plot_window_width && mouse_y>=y_plot && mouse_y<=y_plot+plot_window_height )
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_ECHO:
                if(mouse_x>=x_echo && mouse_x<=x_echo+echo_window_x_size && mouse_y>=y_echo && mouse_y<=y_echo+echo_window_y_size )
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_DRAW:
                if(mouse_x>=x_Wdraw && mouse_x<=x_Wdraw+draw_window_x_size && mouse_y>=y_Wdraw && mouse_y<=y_Wdraw+draw_window_y_size )
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_LIST:
                if(mouse_x>=Xlistproj && mouse_x<=Xlistproj+350 && mouse_y>=Ylistproj && mouse_y<=Ylistproj+600)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_SAVE:
                if(mouse_x>=xsave_window && mouse_x<=xsave_window+420 && mouse_y>=ysave_window && mouse_y<=ysave_window+520)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_MAINMENU:
                if(mouse_x>x_mainmenu && mouse_x<=x_mainmenu+size_x_mainmenu && mouse_y>=y_mainmenu && mouse_y<=y_mainmenu+size_y_mainmenu)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_BANGER:
                if(mouse_x>=X_banger && mouse_x<=X_banger+size_X_Banger && mouse_y>=Y_banger && mouse_y<=Y_banger+size_Y_Banger)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_ALARM:
                if( mouse_x>=XAlarm && mouse_x<=XAlarm+300 && mouse_y>=YAlarm && mouse_y<=YAlarm+110)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_AUDIO:
                if(mouse_x>=XAudio && mouse_x<=XAudio+600 && mouse_y>=YAudio && mouse_y<=YAudio+150+(index_nbre_players_visibles*6*20))
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_CFGMENU:
                if(mouse_x>=window_cfgX && mouse_x<=window_cfgX+largeurCFGwindow && mouse_y>=window_cfgY  && mouse_y<=window_cfgY+hauteurCFGwindow+40)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_WIZARD:
                if( mouse_x>=Xwizard && mouse_x<=Xwizard+480 && mouse_y>=Ywizard && mouse_y<=Ywizard+420)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_MINIFADERS:
                if( mouse_x>=xMinifaders-10 && mouse_x<=xMinifaders+700 && mouse_y>=yMinifaders-50 && mouse_y<=yMinifaders+400)
                {
                    window_is=window_opened[i];    //index_over_minifaders=1 index_show_minifaders==1
                    stop_detect=1;
                }
                break;
            case W_CHASERS:
                if( mouse_x>=Xchasers && mouse_x<=Xchasers+620 && mouse_y>=Ychasers && mouse_y<=Ychasers+160+(nbre_track_visualisables*40))
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_MOVER:
                if(mouse_x>=xmover_window && mouse_x<=xmover_window+1000 && mouse_y>=ymover_window-40 && mouse_y<=ymover_window+660)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_iCAT:
                if(mouse_x>=X_gui_iCat && mouse_x<=X_gui_iCat+largeuriCat && mouse_y>=Y_gui_iCat && mouse_y<=Y_gui_iCat+hauteuriCat)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_GRID:
                if( mouse_x>=grider_window_x && mouse_x<=grider_window_x+largeurGrider && mouse_y>=grider_window_y && mouse_y<=grider_window_y+hauteurGrider)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_BAZOOKAT:
                if( mouse_x>=position_x_bazoocat_menus && mouse_x<=position_x_bazoocat_menus+size_x_bazoocat_menus && mouse_y>=position_y_bazoocat_menus && mouse_y<=position_y_bazoocat_menus+size_y_bazoocat_menus)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
            case W_MY_WINDOW:
                if( mouse_x>=my_window_x && mouse_x<=my_window_x+largeur_my_window && mouse_y>=my_window_y && mouse_y<=my_window_y+hauteur_my_window)
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
			//sab 07/08/2016 deb - Hotkeys-window
			case W_ID_WRKSPC_DIR_WINDOW:
                if (wrkspc_dir_window_isMouseOver(mouse_x,mouse_y))
                {
                    window_is=window_opened[i];
                    stop_detect=1;
                }
                break;
			//sab 07/08/2016 fin - Hotkeys-window
            default:
                break;
            }
            if(stop_detect==1)
            {
                break;
            }
        }
    }
    if(stop_detect==0)
    {
        index_over_A_window=0;
    }
    else
    {
        index_over_A_window=1;
        window_bring_to_front(window_is);
    }






    if(index_over_A_window==0 && mouse_y> hauteur_ChannelMenu && mouse_x<560 )
    {
        index_over_channelspace=1;
    }
    else
    {
        index_over_channelspace=0;
    }

    return(window_is);
}


int move_window(int idwindowis)
{
    if(mouseClicLeft.isDown() && window_focus_id==idwindowis && mouse_y>hauteur_ChannelMenu)
    {

//set_mouse_range(mouse_x-10,mouse_x+10, mouse_y-10,mouse_y+10);//pour pas deborder
        switch(window_focus_id)
        {
        case W_SAVEREPORT:
            report_SL_X=mouse_x-(40+15);
            report_SL_Y=mouse_y-25;
            im_moving_a_window=1;
            break;

        case W_TRICHROMY:
            xtrichro_window=mouse_x+100;
            ytrichro_window=mouse_y+180;
//rafraichissement du curseur Hue
            vx =(int) (cos(angle_snap)*125);
            vy =(int) (sin(angle_snap)*125);
            position_curseur_hue_x= xtrichro_window+vx;
            position_curseur_hue_y=ytrichro_window+vy ;
            im_moving_a_window=1;
            break;
        case W_NUMPAD:
            xnum_window=mouse_x-(405+30+15);
            ynum_window=mouse_y-25;
            rafraichissement_padwheel();
            im_moving_a_window=1;
            break;
        case W_TRACKINGVIDEO:
            videoX=mouse_x-(40+15);
            videoY=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_ARTPOLLREPLY:
            artpoll_replyX=mouse_x-470;
            artpoll_replyY=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_FADERS:
// YFader=mouse_y+30+25;//dans visuel faders helas
// im_moving_a_window=1;
            break;
        case W_PATCH:
            xpatch_window=mouse_x-(40+15);
            ypatch_window=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_TIME:
            xtime_window=mouse_x-(40+15);
            ytime_window=mouse_y-25;
//rafraichissement du curseur
            vtimex = (cos(angle_timesnap)*100);
            vtimey = (sin(angle_timesnap)*100);
            position_curseur_time_x= xtime_window+vtimex+150;
            position_curseur_time_y= ytime_window+vtimey+150;
            im_moving_a_window=1;
            break;
        case W_SEQUENCIEL:
            xseq_window=mouse_x-(40+15);
            yseq_window=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_ASKCONFIRM:
            XConfirm=mouse_x-(40+15);
            YConfirm=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_PLOT:
            x_plot=mouse_x-(40+15);
            y_plot=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_ECHO:
            x_echo=mouse_x-(40+15);
            y_echo=mouse_y-25;
            im_moving_a_window=1;
            break;

        case W_MAINMENU:
            x_mainmenu=mouse_x-(40+15);
            y_mainmenu=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_LIST:
            Xlistproj=mouse_x-(40+15);
            Ylistproj=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_SAVE:
            xsave_window=mouse_x-(40+15);
            ysave_window=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_BANGER:
            X_banger=mouse_x-(40+15);
            Y_banger=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_ALARM:
            XAlarm=mouse_x-(40+15);
            YAlarm=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_AUDIO:
            XAudio=mouse_x-(40+15);
            YAudio=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_CFGMENU:
            window_cfgX=mouse_x-(40+15);
            window_cfgY=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_WIZARD://wizard window
            Xwizard=mouse_x-(40+15);
            Ywizard=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_MINIFADERS://minifaders
            xMinifaders=mouse_x-50;
            yMinifaders=mouse_y+25;
            im_moving_a_window=1;
            break;
        case W_CHASERS://chasers
            Xchasers=mouse_x-(40+15);
            Ychasers=mouse_y-20;
            im_moving_a_window=1;
            break;
        case W_MOVER://mover
            xmover_window=mouse_x-(40+15);
            ymover_window=mouse_y+20;
            im_moving_a_window=1;
            break;
        case W_iCAT://iCatbuilder
            X_gui_iCat=mouse_x-(40+15);
            Y_gui_iCat=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_GRID://grid
            grider_window_x=mouse_x-(40+15);
            grider_window_y=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_DRAW:
            x_Wdraw=mouse_x-(40+15);
            y_Wdraw=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_BAZOOKAT:
            position_x_bazoocat_menus=mouse_x-(40+15);
            position_y_bazoocat_menus=mouse_y-25;
            im_moving_a_window=1;
            break;
        case W_MY_WINDOW:
            my_window_x=mouse_x-(40+15);
            my_window_y=mouse_y-25;
            im_moving_a_window=1;
            break;
		//sab 07/08/2016 deb - Hotkeys-window
		case W_ID_WRKSPC_DIR_WINDOW:
            im_moving_a_window=wrkspc_dir_window_moveTo(mouse_x,mouse_y);
            break;
		//sab 07/08/2016 fin - Hotkeys-window
        default:
            break;
        }
    }

    return(0);
}



int MoveCloseBox(int xmv,int ymv, int idwindow)
{

    Circle CloseBox(Vec2D(xmv,ymv),15);
    Circle MoveBox(Vec2D(xmv+40,ymv),15);
    if(window_focus_id==idwindow)
    {
        if(mouse_y>ymv-15 && mouse_y<ymv+15)
        {
            if(mouse_x>xmv-15 && mouse_x<xmv+15)
            {
                CloseBox.Draw(CouleurSurvol);
            }
            else if(mouse_x>xmv+40-15 && mouse_x<xmv+40+15)
            {
                MoveBox.Draw(CouleurSurvol);
                if((mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
                        || mouseClicLeft.isProcessed())
                {
                    MoveBox.Draw(CouleurFader);
                }

            }
        }
    }
    //close draw
    Line (Vec2D(xmv-5,ymv-5),Vec2D(xmv+5,ymv+5)).Draw(CouleurLigne);
    Line (Vec2D(xmv+5,ymv-5),Vec2D(xmv-5,ymv+5)).Draw(CouleurLigne);
    //move draw
    petitchiffre.Print("M",xmv+40-5,ymv+3);
    CloseBox.DrawOutline(CouleurLigne);
    MoveBox.DrawOutline(CouleurLigne);
    return(0);
}


bool no_LeftDragDrop()
{
    return (original_posx==mouse_x && original_posy==mouse_y);

}


int do_logical_MoveCloseBox(int xmv,int ymv, int idwindow)
{

    if(window_focus_id==idwindow)
    {
        if(mouse_y>ymv-15 && mouse_y<ymv+15 && mouse_y>hauteur_ChannelMenu)
        {
            if(mouse_x>xmv-15 && mouse_x<xmv+15)
            {
                //if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed() &&  im_moving_a_window==0 && original_posx==mouse_x && original_posy==mouse_y)
                if(mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed() &&  im_moving_a_window==0 && mouseClicLeft.isNotDrop()) //no_LeftDragDrop())
                {
                    substract_a_window(idwindow);
                    mouseClicLeft.SetProcessed(3);
                }
            }
// else if(((mouse_x>xmv+40-15 && mouse_x<xmv+40+15)|| im_moving_a_window==1)&& (original_posx==mouse_x && original_posy==mouse_y))
            else if(((mouse_x>xmv+40-15 && mouse_x<xmv+40+15)|| im_moving_a_window==1)&& mouseClicLeft.isNotDrop()) //no_LeftDragDrop())
            {
                move_window(idwindow);
            }

        }
    }

    return(0);
}

int logical_channelspace()
{
    if(ClassicalChannelView==1)   //512
    {
        if(mouse_y> ChannelYMenu+hauteur_ChannelMenu)//les menus
        {
            do_logical_ClassicalChannelSpace(XChannels, YChannels,  scroll_channelspace);
        }
    }


    else
    {
        int pos_y_vision=0;
        for(int i=0; i<=nbre_de_vues_circuits; i++)
        {
            if(Channel_View_MODE[i]==1)
            {
                do_logical_Draw_Channel_Preset_Title(XChannels,YChannels+pos_y_vision-(int)(((float)scroll_channelspace)/ ratioview),i);
                pos_y_vision+= 60;
                do_logical_Draw_Channel_Preset_View(XChannels,YChannels+pos_y_vision-(int)(((float)scroll_channelspace)/ ratioview),i);
                pos_y_vision+=((channel_number_of_lines[i])*70)+ hauteur_preset_titre;
            } //pas de scroll
        }
    }

    return(0);
}

//sab 28/06/2014 DEB

/** \brief Mouse Wheel global handle - switch between key press  case
 *
 * \return void
 *
 */
void mouseWheel_handle()
{
    if (mouseScroll.isToBeProcessed() or mouseRoll.isToBeProcessed()) /*(not(mouseScroll.gain()==0))*/
    {
        if (key[KEY_ALT])
        {
            //ALTERATION Des MODES SELECTION (CHANNELS ou ALT+CLIC) - C'est le contrôleur SOUS LA SOURIS qui est prioritaire :: le régisseur regarde son écran
            mouseWheel_handle_onAltOver() ;
        }
        else if (key[KEY_CAPSLOCK])
        {
            //c'est la sélection faite avec (ALT+CLIC) qui bénéficie de la roue en CAPS LOCK où que soit la souris (le régisseur ne regarde pas son écran mais le plateau)
            mouseWheel_handle_forAltClicSelection() ;
        }

        else  // caps off et pas de touche modificatrice
        {
            if (window_focus_id==W_PLOT && light_plot_edit_mode_enable)
            {
                do_logical_Plot_Wheel();
            }
            else if  (window_focus_id==W_BANGER && editing_banger_family)
            {
                do_logical_Banger_Wheel();
            }
            else
                //c'est la sélection de channels qui bénéficie de la roue par défaut où que soit la souris (le régisseur ne regarde pas son écran mais le plateau)
                do_logical_Channel_wheel(); //ex DoMouseLevel();
        }

        if (not key[KEY_LCONTROL]) /**< set to processed if not speed up and nothing sensible to wheel ; otherwise it will repeat all this tests for nothing */
        {
            mouseScroll.SetProcessed() ;
            mouseRoll.SetProcessed() ;
        }
    }
}


/** \brief Mis à jour des niveaux des contrôleurs sélectionnés (par Alt Clic) pour être contrôlés par la roue de la souris quand caps lock est actif
 *
 * \return void
 *
 */
void mouseWheel_handle_forAltClicSelection()
{
    if (mouseScroll.isToBeProcessed())
    {
        mouseScroll.handOverSubscriber();
    }
    if (mouseRoll.isToBeProcessed())
    {
        mouseRoll.handOverSubscriber();
    }
}

/** \brief Mis à jour du niveau du contrôleur sous la souris (si ALT)
 *
 * \return void
 *
 */
void mouseWheel_handle_onAltOver()
{
    int fader_x, fader_y, fader_spacing, fader_quantity, fader_gm_width, fader_leftGM_x, fader_rightGM_x;

    switch(window_focus_id)
    {
    case W_MAINBOARD:
        do_logical_grand_master_wheel(1050, 55, 40);
        do_logical_ChannelScroller_wheel();
        if ( mousePtr.isOverRecSize(10, 40, 555, hauteur_ecran - 40))
        {
            do_logical_Channel_wheel();
        }
        break;
    case W_SAVEREPORT:

        break;
    case W_TRICHROMY:

        break;
    case W_NUMPAD:

        break;
    case W_TRACKINGVIDEO:

        break;
    case W_ARTPOLLREPLY:

        break;
    case W_FADERS :

        fader_x = XFader-((int)(scroll_faderspace*facteur_scroll_fader_space));
        fader_y = YFader;

        fader_spacing = 182 ; //int(150+((190-150)*size_faders));
        fader_quantity = 48;
        fader_gm_width = 40 ; //(int(50*size_faders));

        fader_leftGM_x = fader_x-140 ;
        fader_rightGM_x = fader_x+(fader_quantity*fader_spacing)+50;

        do_logical_grand_master_wheel(fader_leftGM_x, fader_y, fader_gm_width);//x y largeur
        do_logical_grand_master_wheel(fader_rightGM_x, fader_y, fader_gm_width);//x y largeur
        break;
    case W_PATCH:

        break;
    case W_TIME:

        break;
    case W_SEQUENCIEL:

        break;
    case W_ASKCONFIRM:

        break;
    case W_PLOT:
        switch(index_menus_lighting_plot)
        {
        case 0://plan
            do_logical_Plot_Wheel();
            break;
        case 1://shapes

            break;
        case 2://symbols

            break;
        case 3://légende

            break;
        case 4://plan seul

            break;
        default:

            break;
        }
        break;
    case W_ECHO:

        break;
    case W_DRAW:

        break;
    case W_LIST:

        break;
    case W_SAVE:

        break;
    case W_MAINMENU:

        break;
    case W_BANGER:
        do_logical_Banger_Wheel();
        break;
    case W_ALARM:

        break;
    case W_AUDIO:

        break;
    case W_CFGMENU:

        break;
    case W_WIZARD:

        break;
    case W_MINIFADERS:

        break;
    case W_CHASERS:

        break;
    case W_MOVER:

        break;
    case W_iCAT:

        break;
    case W_GRID:

        break;
    case W_MY_WINDOW:

        break;
	//sab 07/08/2016 deb - Hotkeys-window
	case W_ID_WRKSPC_DIR_WINDOW:

            break;
	//sab 07/08/2016 fin - Hotkeys-window
    default:
        break;
    }
}
//sab 28/06/2014 FIN

int check_graphics_mouse_handling()
{

    do_logical_ChannelScroller(ChScrollX, ChScrollY);

    if(index_over_channelspace==1 && window_focus_id==0)
    {
        logical_channelspace();             //classique et custom
    }



    do_logical_grand_master(1050, 55, 40);

//dans la fenetre Banger maintenant. Christoph 31 / 03 / 14
//do_logical_feedback_banger(xVisuBanger,yVisuBanger);


//manquent save menu / wizard / save box / CFG etc...

    if((mouse_x<largeur_ChannelMenu && mouse_y>hauteur_ChannelMenu )||(mouse_x>largeur_ChannelMenu  ))
    {

        switch(window_focus_id)
        {
        case W_SAVEREPORT:
            do_logical_MoveCloseBox(report_SL_X+20,report_SL_Y+25,W_SAVEREPORT);
            break;
        case W_TRICHROMY:
            do_logical_Interface_Trichromie(xtrichro_window,ytrichro_window,125,15);
            do_logical_MoveCloseBox(xtrichro_window+20-158,ytrichro_window+25-206,W_TRICHROMY);
            break;
        case W_NUMPAD:
            do_logical_visual_numeric_pad(xnum_window,ynum_window);
            do_logical_FunctionBoxChannel(xnum_window+405,ynum_window+85,60,30,15);
            do_logical_MoveCloseBox(xnum_window+405,ynum_window+25,W_NUMPAD);
            break;
        case W_TRACKINGVIDEO:
            do_logical_Interface_video_window(videoX,videoY);
            do_logical_MoveCloseBox(videoX+20,videoY+25,W_TRACKINGVIDEO);
            break;
        case W_ARTPOLLREPLY:
            do_logical_MoveCloseBox(artpoll_replyX+435,artpoll_replyY+25,W_ARTPOLLREPLY);
            break;
        case W_FADERS :
            do_logical_FaderSpace(XFader-((int)(scroll_faderspace*facteur_scroll_fader_space)),YFader,int(50*size_faders),int(150+((190-150)*size_faders)),48);//x y / largeurfader / espacement des faders, nbr faders to draw
            break;
        case W_PATCH:
            do_logical_PatchBox(xpatch_window, ypatch_window, Patch_Scroll_Factor);
            if(index_menu_curve==1)
            {
                do_logical_menu_curve(xpatch_window+455, ypatch_window);
            }
            do_logical_MoveCloseBox(xpatch_window+20,ypatch_window+25, W_PATCH);
            break;
        case W_TIME:
            do_logical_Time_Window(xtime_window, ytime_window,100);
            do_logical_MoveCloseBox(xtime_window+20,ytime_window+25,W_TIME);
            break;
        case W_SEQUENCIEL:
            do_logical_Sequenciel_Window(xseq_window, yseq_window,670+(260*show_gridplayer_in_seq),hauteur_globale_sequenciel);
            do_logical_MoveCloseBox(xseq_window+20,yseq_window+25,W_SEQUENCIEL);
            break;
        case W_ASKCONFIRM:
            do_logical_MoveCloseBox(XConfirm+20,YConfirm+25,W_ASKCONFIRM);
            break;
        case W_PLOT:
            do_logical_Plot_window(x_plot,y_plot);
            do_logical_MoveCloseBox(x_plot+20,y_plot+25,W_PLOT);
            break;
        case W_ECHO:
            do_logical_echo_window(x_echo,y_echo);
            do_logical_MoveCloseBox(x_echo+20,y_echo+25,W_ECHO);
            break;
        case W_DRAW:
            do_logical_Draw_Window(x_Wdraw,y_Wdraw);
            do_logical_MoveCloseBox(x_Wdraw+20,y_Wdraw+25, W_DRAW);
            break;
        case W_LIST:
            do_logical_liste_projecteurs(Xlistproj ,Ylistproj);
            do_logical_MoveCloseBox(Xlistproj+20,Ylistproj+25,W_LIST);
            break;
        case W_SAVE:
            do_logical_Save_Menu(xsave_window,ysave_window);
            do_logical_MoveCloseBox(xsave_window+20,ysave_window+25,W_SAVE);
            break;
        case W_MAINMENU:
            do_logical_Menus(x_mainmenu,y_mainmenu);
            do_logical_MoveCloseBox(x_mainmenu+20,y_mainmenu+25,W_MAINMENU);
            break;
        case W_BANGER:
            do_logical_fenetre_banger(X_banger,Y_banger);
            do_logical_MoveCloseBox(X_banger+20,Y_banger+25,W_BANGER);
            break;
        case W_ALARM:

            do_logical_MoveCloseBox(XAlarm+20,YAlarm+25, W_ALARM) ;
            break;
        case W_AUDIO:
            do_logical_fenetre_audio(XAudio,YAudio);
            do_logical_MoveCloseBox(XAudio+20,YAudio+25,W_AUDIO);
            break;
        case W_CFGMENU:
            do_logical_MoveCloseBox(window_cfgX+20,window_cfgY+20,W_CFGMENU);
            break;
        case W_WIZARD:
            do_logical_MoveCloseBox(Xwizard+20,Ywizard+20,W_WIZARD);
            break;
        case W_MINIFADERS:
            mini_faders_panel_core(xMinifaders,yMinifaders,20);
            do_logical_MoveCloseBox(xMinifaders+10,yMinifaders-30,W_MINIFADERS);
            break;
        case W_CHASERS:
            do_logical_fenetre_chasers( Xchasers,Ychasers);
            do_logical_MoveCloseBox(Xchasers+20,Ychasers+20,W_CHASERS);
            break;
        case W_MOVER:

            do_logical_MoveCloseBox(xmover_window+20, ymover_window-20,W_MOVER);
            break;
        case W_iCAT:
            do_logical_MoveCloseBox( X_gui_iCat+20,Y_gui_iCat+20,W_iCAT);
            break;
        case W_GRID:
            do_logical_Grider_Box(grider_window_x, grider_window_y);
            do_logical_MoveCloseBox( grider_window_x+20,grider_window_y+20,W_GRID);
            break;
        case W_MY_WINDOW:
            do_logical_my_window_Box(my_window_x, my_window_y);
            do_logical_MoveCloseBox( my_window_x+20,my_window_y+20,W_MY_WINDOW);
            break;
		//sab 07/08/2016 deb - Hotkeys-window
		case W_ID_WRKSPC_DIR_WINDOW:
            wrkspc_dir_window_mouseLeftHandle();
            break;
		//sab 07/08/2016 fin - Hotkeys-window
        case W_BAZOOKAT:
            do_logical_fenetre_bazookat_menus(position_x_bazoocat_menus, position_y_bazoocat_menus);
            do_logical_MoveCloseBox( position_x_bazoocat_menus+20,position_y_bazoocat_menus+20,W_BAZOOKAT);
            break;
        default:
            break;
        }
    }

    do_logical_ChannelsMenuSelection(ChannelXMenu,ChannelYMenu);

    return(0);
}

