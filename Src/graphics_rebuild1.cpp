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

* \file graphics_rebuild1.cpp
* \brief {GUI fonctions to redraw graphics}
* \author Christoph Guillermet
* \version {0.8.6}
* \date {28/04/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour redéssiner l'interface graphique
*
*   GUI fonctions to redraw graphics
*
 **/

int RetourInfos(int x_info,int y_info)
{

    neuro.Print(string_numeric_entry,x_info,y_info+15);//input chaine clavier numerique
    petitchiffre.Print(string_last_ch,x_info,y_info+30);//input last ch selected
    petitchiffre.Print(string_last_copy_mem,x_info+170,y_info+30);

    Rect VisuHue(Vec2D(x_info+290,y_info+15),Vec2D(30,20));
    Rgba CouleurPreviewHue(r_pick,v_pick,b_pick,255);
    VisuHue.Draw(CouleurPreviewHue);
    Rgba CouleurPreviewChroma(my_red,my_green,my_blue,255);
    Rect VisuChroma(Vec2D(x_info+325,y_info+15),Vec2D(30,20));
    VisuChroma.Draw(CouleurPreviewChroma);
    petitpetitchiffre.Print(string_dock_col_sel,x_info+293,y_info+30);

    petitchiffre.Print(string_secondary_feeback,x_info,y_info+45);//
    petitchiffrerouge.Print(string_display_dmx_params,x_info,y_info+60);
    petitchiffre.Print(">>MIDI IN:",x_info, y_info+75);//midi in
    petitchiffre.Print(my_midi_string,x_info+70, y_info+75);//midi in

    petitchiffre.Print("Time Is:",x_info,y_info+90);
    petitchiffre.Print(tmp_time,x_info+60,y_info+90);
    sprintf(visu_chrono_str,"Chrono: %d..%d.%d",time_minutes,time_secondes, time_centiemes);
    petitchiffre.Print(visu_chrono_str,x_info+170,y_info+90);
    petitchiffrerouge.Print(string_Last_Order,x_info, y_info+105);//last order
    diodes_artnet(x_info,y_info+120);
    if(index_do_light_diode_artnet==1)
    {
        light_temoin_universe(incoming_universe,x_info,y_info+120);
        index_do_light_diode_artnet=0;
    }
    if((myDMXinterfaceis==1 && index_init_dmx_ok==1) || index_artnet_doubledmx==1)
    {
        light_temoin_emission(Univers,x_info,y_info+120);
    }

    return(0);
}

int show_windows_list_id(int x_info, int y_info)
{
    petitpetitchiffre.Print("Nb.W.:",x_info,y_info);
    petitpetitchiffre.Print(ol::ToString(nbre_fenetre_actives),x_info+35,y_info);
    for(int i=0; i<63; i++)
    {
        if(window_opened[i]>0 && window_opened[i]<max_window_identity_is)
        {
            petitpetitchiffre.Print(ol::ToString(window_opened[i]),x_info,y_info+10+(i*10));
        }
    }
    return(0);
}



int Boxes()
{
    ChannelScroller(ChScrollX, ChScrollY);

    if(ClassicalChannelView ==1)
    {
        Canvas::SetClipping(0,ChannelYMenu+hauteur_ChannelMenu,largeur_ecran,hauteur_ecran);
        ClassicalChannelSpace(XChannels, YChannels,  scroll_channelspace);// x y espacement latéral // espacement vertical // scrolling down
        Canvas::DisableClipping();
    }

    else
    {
//sab 02/03/2014 unused var int index_posView=0;
        int pos_y_vision=0;
        Canvas::SetClipping(XChannels,ChannelYMenu+hauteur_ChannelMenu ,XChannels+600 , hauteur_ecran);
        for(int i=0; i<nbre_de_vues_circuits; i++)
        {
            if(Channel_View_MODE[i]==1 )
            {
                Draw_Channel_Preset_Title(XChannels, YChannels+pos_y_vision-(int)(((float)scroll_channelspace)/ ratioview),i);
                pos_y_vision+= 60;
                Draw_Channel_Preset_View(XChannels, YChannels+pos_y_vision-(int)(((float)scroll_channelspace)/ ratioview), i);
                pos_y_vision+=((channel_number_of_lines[i])* (70))+ hauteur_preset_titre;
            }
        }
        Canvas::DisableClipping();
    }


    RetourInfos(680,40);
    //20/11/2014 sab - dev log
    debug_log_show_test_log(680,40);

//mis dans la fenetre banger Christoph 30/03/14
//feedback_banger(xVisuBanger,yVisuBanger);
    grand_master(1050, 55);//x y largeur
    show_windows_list_id(1100, 50);//debug windows

    petitchiffre.Print(nickname_version,680,195);

    petitchiffre.Print(string_debug,680, 210);

//focus window
    petitchiffre.Print("Focus: ",680,220);
    petitchiffre.Print(ol::ToString(window_focus_id),730,220);
    petitchiffre.Print("Over Window: ",680,230);
    petitchiffre.Print(ol::ToString(index_over_A_window),770,230);
//retour sauvegarde
    Rect RetourConduite(Vec2D(680,240),Vec2D(270,40));
    RetourConduite.SetRoundness(5);
    RetourConduite.Draw(CouleurBlind.WithAlpha(0.5));
    RetourConduite.DrawOutline(CouleurLigne);
    petitchiffre.Print("Last_save / SAVE:",685,255);
    petitchiffre.Print(my_show_is_coming_from,685,270);

//visualisation retour faux shift faux ctrl de banger ou de iCat
    Rect False(Vec2D(970,240),Vec2D(55,15));
    False.Draw(CouleurBlind.WithAlpha(index_false_shift*alpha_blinker));
    False.DrawOutline(CouleurLigne.WithAlpha(0.5));
    petitchiffre.Print("F-Shift",975,252);

    False.MoveTo(Vec2D(970,265));
    False.Draw(CouleurBlind.WithAlpha(index_false_control*alpha_blinker));
    False.DrawOutline(CouleurLigne.WithAlpha(0.5));
    petitchiffre.Print("F-Ctrl",980,277);

//////////////AFFICHAGES CONDITIONNES//////////////////////////////////////////////
//sab 18/01/2014 deb
    if(not(window_focus_id==W_MAINBOARD) && mainboard_ifNotFocus_veil)
    {
        Rgba veil( 1.0, 1.0, 1.0, 0.09 );
        Rect veilMainboard(0, 0, largeur_ecran, hauteur_ecran);
        veilMainboard.Draw(veil);
    }
//sab 18/01/2014 fin

    for (int f=63; f>=0; f--)
    {

        switch (window_opened[f])
        {
        case W_SAVEREPORT:
            Show_report_save_load();
            MoveCloseBox(report_SL_X+20,report_SL_Y+25,W_SAVEREPORT);
            break;
        case W_TRICHROMY:
            Interface_Trichromie(xtrichro_window,ytrichro_window,125,15);
            MoveCloseBox(xtrichro_window+20-158,ytrichro_window+25-206,W_TRICHROMY);
            break;
        case W_NUMPAD:
            visual_numeric_pad(xnum_window,ynum_window);
            FunctionBoxChannel(xnum_window+405,ynum_window+85,60,30,15);//x y largeurbox hauteur largeur box separateurspace);
            MoveCloseBox(xnum_window+405,ynum_window+25,W_NUMPAD);
            break;
        case W_TRACKINGVIDEO:
            Interface_video_window(videoX,videoY);
            MoveCloseBox(videoX+20,videoY+25,W_TRACKINGVIDEO);
            break;
        case W_ARTPOLLREPLY:
            show_artpoll_reply(artpoll_replyX,artpoll_replyY);
            MoveCloseBox(artpoll_replyX+435,artpoll_replyY+25,W_ARTPOLLREPLY);
            break;
        case W_FADERS :
            FaderSpace(XFader-((int)(scroll_faderspace*facteur_scroll_fader_space)),YFader,182,max_faders);//x y / largeurfader / espacement des faders, nbr faders to draw
            break;
        case W_PATCH:
            PatchBox(xpatch_window, ypatch_window, Patch_Scroll_Factor);
            MoveCloseBox(xpatch_window+20,ypatch_window+25, W_PATCH);
            break;
        case W_ECHO:
            echo_window(x_echo,y_echo);
            MoveCloseBox(x_echo+20,y_echo+25,W_ECHO);
            break;
        case W_DRAW:
            Draw_Window(x_Wdraw,y_Wdraw);
            MoveCloseBox(x_Wdraw+20,y_Wdraw+25, W_DRAW);
            break;
        case W_TIME:
            Time_Window(xtime_window, ytime_window,100);
            MoveCloseBox(xtime_window+20,ytime_window+25,W_TIME);
            break;
        case W_SEQUENCIEL:
            Sequenciel_Window(xseq_window, yseq_window,670+(260*show_gridplayer_in_seq),hauteur_globale_sequenciel);
            MoveCloseBox(xseq_window+20,yseq_window+25,W_SEQUENCIEL);
            break;
        case W_MAINMENU:
            Menus(x_mainmenu,y_mainmenu);
            MoveCloseBox(x_mainmenu+20,y_mainmenu+25,W_MAINMENU);
            break;
        case W_ASKCONFIRM:
            fenetre_confirm();
            MoveCloseBox(XConfirm+20,YConfirm+25,W_ASKCONFIRM);
            break;
        case W_PLOT:
            Plot_window(x_plot,y_plot);
            MoveCloseBox(x_plot+20,y_plot+25,W_PLOT);
            break;
        case W_LIST:
            liste_projecteurs(Xlistproj ,Ylistproj);
            MoveCloseBox(Xlistproj+20,Ylistproj+25,W_LIST);
            break;
        case W_SAVE:
            Save_Menu(xsave_window,ysave_window);
            MoveCloseBox(xsave_window+20,ysave_window+25,W_SAVE);
            break;
        case W_BAZOOKAT:
            fenetre_bazookat_menus(position_x_bazoocat_menus,position_y_bazoocat_menus);
            MoveCloseBox(position_x_bazoocat_menus+20,position_y_bazoocat_menus+25,W_BAZOOKAT);
            break;
        case W_BANGER:
            fenetre_banger(X_banger,Y_banger);
            MoveCloseBox(X_banger+20,Y_banger+25,W_BANGER);
            break;
        case W_ALARM:
            alarm_window();
            MoveCloseBox(XAlarm+20,YAlarm+25, W_ALARM) ;
            break;
        case W_AUDIO:
            fenetre_audio(XAudio,YAudio);
            MoveCloseBox(XAudio+20,YAudio+25,W_AUDIO);
            break;
        case W_CFGMENU:
            config_general_menu();
            MoveCloseBox(window_cfgX+20,window_cfgY+20,W_CFGMENU);
            break;
        case W_WIZARD:
            fenetre_wizard(Xwizard,Ywizard);
            MoveCloseBox(Xwizard+20,Ywizard+20,W_WIZARD);
            break;
        case W_MINIFADERS:
            mini_faders_panel_visu(xMinifaders,yMinifaders,20);
            MoveCloseBox(xMinifaders+10,yMinifaders-30,W_MINIFADERS);
            break;
        case W_CHASERS:
            chaser_window( Xchasers,Ychasers);
            MoveCloseBox(Xchasers+20,Ychasers+20,W_CHASERS);
            break;
        case W_MOVER:
            mover_box(xmover_window, ymover_window);
            MoveCloseBox(xmover_window+20, ymover_window-20,W_MOVER);
            break;
        case W_iCAT:
            BoxGuiBuilder_iCat( X_gui_iCat, Y_gui_iCat);
            MoveCloseBox( X_gui_iCat+20,Y_gui_iCat+20,W_iCAT);
            break;
        case W_GRID:
            Grider_Box(grider_window_x, grider_window_y);
            MoveCloseBox( grider_window_x+20,grider_window_y+20,W_GRID);
            break;
        case W_MY_WINDOW:
            my_window_Box(my_window_x, my_window_y);
            MoveCloseBox( my_window_x+20,my_window_y+20,W_MY_WINDOW);
            break;
		//sab 07/08/2016 deb -
        case W_ID_WRKSPC_DIR_WINDOW:
            wrkspc_dir_window_show();
            MoveCloseBox( wrkspc_dir_window_pos_x+20,wrkspc_dir_window_pos_y+20,W_ID_WRKSPC_DIR_WINDOW);
            break;
		//sab 07/08/2016 fin -
        default:
            break;
        }
    }


    ChannelsMenuSelection(ChannelXMenu,ChannelYMenu);//menu par dessus


//over windows if text
    if(keyboardStorage_numeric_postext>0 || index_type==1)
    {
        Rect nameAera( Vec2D( 670, 27), Vec2D ( 380,40));
        nameAera.SetRoundness(15);
        nameAera.SetLineWidth(triple_epaisseur_ligne_fader);
        nameAera.Draw(CouleurFader.WithAlpha(index_type));
        Rect UnderText(Vec2D(670,32),Vec2D((keyboardStorage_numeric_postext*14)+50,30));
        UnderText.SetRoundness(7.5);
        UnderText.Draw(CouleurFond);
        UnderText.Draw(CouleurLigne.WithAlpha(0.1));
        UnderText.DrawOutline(CouleurFader);
        neuro.Print(string_numeric_entry,680,55);//input chaine clavier numerique
    }
/////////////////////////////////

    return(0);

}

//sab 02/03/2014 int  Procedure(char procedure_title[64],char procedure_subtitle[120])
void  Procedure(const std::string title,const std::string subtitle)
{
    const std::string procedure_title 		= title.substr (0,64);
    const std::string procedure_subtitle 	= subtitle.substr (0,120);

    Rect ProcedureAera( Vec2D( window_proc_x, window_proc_y), Vec2D ( 400,70));
    ProcedureAera.SetRoundness(15);
    ProcedureAera.Draw(CouleurBleuProcedure);
    ProcedureAera.DrawOutline(CouleurLigne);
    neuro.Print(procedure_title, window_proc_x+120,window_proc_y+20);
    petitchiffre.Print( procedure_subtitle,window_proc_x+20, window_proc_y+45);
//sab 02/03/2014 return(0);
}

int DoMouse()
{
    float fx, fy;

    fx = (mouse_x-1);
    fy = (mouse_y-1);
    V3D_f mousev1 =
    {
        fx,fy, 0.,
        0., 0.,
        makecol(255, 127, 0) // black vertex
    };

    fx = (mouse_x+20);
    fy = (mouse_y+30);
    V3D_f mousev2 =
    {
        fx,fy, 0.,
        0., 0.,
        makecol(125, 0, 0) // white vertex
    };

    fx = (mouse_x+30);
    fy = (mouse_y+10);
    V3D_f mousev3 =
    {
        fx,fy, 0.,
        0., 0.,
        makecol(125, 0,0) // color vertex
    };



    triangle3d_f(screen, POLYTYPE_GCOL, NULL, &mousev1, &mousev2, &mousev3);



    Line( Vec2D( mouse_x-1,mouse_y-1), Vec2D( mouse_x+20,mouse_y+30),2.0).Draw( CouleurLigne );
    Line( Vec2D( mouse_x+20,mouse_y+30), Vec2D( mouse_x+30,mouse_y+10),2.0).Draw( CouleurLigne );
    Line( Vec2D( mouse_x+30,mouse_y+10), Vec2D( mouse_x-1,mouse_y-1),2.0).Draw(CouleurLigne);

//18/01/2015 sab deb
//    if(Midi_Faders_Affectation_Type!=0  )
//    {
//        neuromoyen.Print( string_shortview_midi, mouse_x-20,mouse_y+40);
//    };
//18/01/2015 sab fin

    return(0);
}
