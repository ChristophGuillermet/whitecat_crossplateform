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

* \file Call_everybody_5.cpp
* \brief {no idea}
* \author Christoph Guillermet
* \version {0.8.6}
* \date {28/04/2014}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Aucune idée à quoi sert ce fichier
*
*   No idea what it does
*
 **/

int reset_other_index_cfg()
{
    index_config_dmx=0;
    index_config_midi=0;
    index_config_arduino=0;
    index_setup_gfx=0;
    index_do_affect_net_to_dock=0;
    index_config_network=0;
    receive_from_trichro=0;
    index_show_config_window=0;
    return(0);
}


int do_logical_FunctionBoxChannel(int fx,int fy, int flarg, int fhaut, int space)
{
    for (int df=0; df<5; df++)
    {
        if (mouse_x>=fx && mouse_x<=fx+flarg && mouse_y>=(fy + (df*fhaut)+ (space*df)) && mouse_y<=(fy+fhaut + (df*fhaut)+ (space*df)) && mouseClicLeft.isToBeProcessed() )
        {

            switch (df)
            {
            case 0: //select all
                if( Midi_Faders_Affectation_Type!=0)//config midi
                {
                    switch(miditable[0][682])
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
                    }
                    sprintf(string_last_midi_id,"NumPad ALL is Ch: %d Pitch: %d Typ: %s" ,miditable[1][682],miditable[2][682],thetypinfo);
                    attribute_midi_solo_affectation(682,Midi_Faders_Affectation_Mode);
                }
                else
                {
                    simulate_keypress(KEY_Y<<8);
                }
                break;
            case 1://inverse sel
                if( Midi_Faders_Affectation_Type!=0)//config midi
                {
                    switch(miditable[0][683])
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
                    }
                    sprintf(string_last_midi_id,"NumPad INV is Ch: %d Pitch: %d Typ: %s" ,miditable[1][683],miditable[2][683],thetypinfo);
                    attribute_midi_solo_affectation(683,Midi_Faders_Affectation_Mode);
                }
                else
                {
                    simulate_keypress(KEY_U<<8);
                }
                break;

            case 2: //to channel funct
                if(Midi_Faders_Affectation_Type!=0)//config midi
                {
                    switch(miditable[0][684])
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
                    }
                    sprintf(string_last_midi_id,"NumPad Thru is Ch: %d Pitch: %d Typ: %s" ,miditable[1][684],miditable[2][684],thetypinfo);
                    attribute_midi_solo_affectation(684,Midi_Faders_Affectation_Mode);
                }
                else
                {
                    simulate_keypress(KEY_TAB<<8);
                }
                break;
            case 3:
                channel_copy();
                break;
            case 4:
                channel_paste();
                break;
            }
            mouseClicLeft.SetProcessed();
        }
    }
    return(0);
}


int FunctionBoxChannel(int fx,int fy, int flarg, int fhaut, int space)
{
    for (int df=0; df<5; df++)
    {
        Rect FunctionChThr(Vec2D(fx, fy + (df*fhaut)+ (space*df)), Vec2D ( flarg,fhaut));
        FunctionChThr.SetRoundness(10);
        FunctionChThr.SetLineWidth(epaisseur_ligne_fader);
        FunctionChThr.DrawOutline(CouleurLigne);
        if( Midi_Faders_Affectation_Type!=0)//config midi
        {
            if(mouse_x>fx && mouse_x<fx+flarg && mouse_y>fy + (df*fhaut)+ (space*df) && mouse_y<fy + (df*fhaut)+ (space*df)+fhaut)
            {
                FunctionChThr.DrawOutline(CouleurBlind);
            }
        }
        switch(df)
        {
        case 0:
            petitchiffre.Print("  ALL",fx+5, fy+15 + (df*fhaut)+ (space*df));
            petitpetitchiffre.Print(" Y",fx+40, fy+25 + (df*fhaut)+ (space*df));
            break;
        case 1:
            petitchiffre.Print("  INV",fx+5, fy+15 + (df*fhaut)+ (space*df));
            petitpetitchiffre.Print(" U",fx+40, fy+25 + (df*fhaut)+ (space*df));
            break;
        case 2:
            petitchiffre.Print(" THRU",fx+5, fy+15 + (df*fhaut)+ (space*df));
            petitpetitchiffre.Print("Tab",fx+40, fy+25 + (df*fhaut)+ (space*df));
            break;
        case 3:
            petitchiffre.Print("  COPY",fx+5, fy+15 + (df*fhaut)+ (space*df));
            petitpetitchiffre.Print(" Ctrl-C",fx+20, fy+25 + (df*fhaut)+ (space*df));
            break;
        case 4:
            petitchiffre.Print("  PASTE",fx+5, fy+15 + (df*fhaut)+ (space*df));
            petitpetitchiffre.Print(" Ctrl-V",fx+20, fy+25 + (df*fhaut)+ (space*df));
            break;


        }

    }
    return(0);
}





int do_logical_Menus( int xmenu, int ymenu)
{
    if(window_focus_id==W_MAINMENU)
    {
//AUTOCLOSE
        if(mouse_x> xmenu+330 && mouse_x< xmenu+360 && mouse_y>ymenu+8  && mouse_y<ymenu+23 && mouseClicLeft.isDown() && mouseClicLeft.isToBeProcessed())
        {
            index_text_auto_close=toggle(index_text_auto_close);
            mouseClicLeft.SetProcessed();
        }


        int IDmidi=0;
        int IDcommand=0;
        char nom_commande[24];
        char raccourci_commande[24];
        bool stae=0;
        for(int cl=0; cl<6; cl++) //sab - 07/08/2015 MOD (5 -> 6)-
        {
            switch(cl)
            {
            case 0://sequenciel window
                IDmidi=751;
                IDcommand=cl;
                sprintf(nom_commande,"CueList");
                sprintf(raccourci_commande,"F9");
                stae=index_window_sequentiel;
                break;
            case 1://time
                IDmidi=748;
                IDcommand=cl;
                sprintf(nom_commande,"Time");
                sprintf(raccourci_commande,"F6");
                stae=index_time;
                break;
            case 2://banger
                IDmidi=753;
                IDcommand=cl;
                sprintf(nom_commande,"Banger");
                sprintf(raccourci_commande,"F11");
                stae=index_show_banger_window;
                break;
            case 3://wizard
                IDmidi=1329;
                IDcommand=cl;
                sprintf(nom_commande,"Wizard");
                sprintf(raccourci_commande,"-");
                stae= index_show_wizard_window;
                break;
            case 4://save
                IDmidi=1330;
                IDcommand=cl;
                strcpy(nom_commande,"Save");
                strcpy(raccourci_commande,"");
                stae=index_menu_save;
                break;
			//sab - 07/08/2015 DEB - Hotkeys -
            case 5://test sab répertoire
                IDmidi=menu_window_addbutton_wrkspc_dir_IDmidi; // +1 par rapport dernière commande ! n° de commande midi à ajouter dans le tableau affectations midi
                IDcommand=cl;
                strcpy(nom_commande,menu_window_addbutton_wrkspc_dir_Name);
                strcpy(raccourci_commande,menu_window_addbutton_wrkspc_dir_Shortcut);
                stae= wrkspc_dir_window_isListening;
                break;
			//sab - 07/08/2015 FIN - Hotkeys -
            default:
                break;
            }
            command_button_logical(xmenu+10,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi,IDcommand);// int x, inty ,bool state, char *textedesc, int midiaffectation
        }



//2ème colonne Circuit relatif
        for(int cl=0; cl<6; cl++)
        {
            switch(cl)
            {
            case 0:
                IDmidi=1331;
                IDcommand=cl+10;
                sprintf(nom_commande,"Patch");
                sprintf(raccourci_commande,"Shift-P");
                stae=index_patch_window;
                break;
            case 1:
                IDmidi=1332;
                IDcommand=cl+10;
                strcpy(nom_commande,"List");
                strcpy(raccourci_commande,"");
                stae=index_list_projecteurs;
                break;
            case 2:
                IDmidi=1594;
                IDcommand=cl+10;
                strcpy(nom_commande,"Light Plot");
                strcpy(raccourci_commande,"");
                stae=index_plot_window;
                break;
            case 3:
                IDmidi=1335;
                IDcommand=cl+10;
                strcpy(nom_commande,"Freeze");
                strcpy(raccourci_commande,"");
                stae=index_do_freeze;
                break;
            case 4:
                IDmidi=1541;
                IDcommand=cl+10;
                strcpy(nom_commande,"Exclude");
                strcpy(raccourci_commande,"");
                stae=index_do_exclude;
                break;
            case 5://my window
                IDmidi=2047; // c est la derniere commande midi, a changer et  définir voir tableau affectations midi
                IDcommand=cl+10;
                strcpy(nom_commande,"MY WINDOW");
                strcpy(raccourci_commande,"");
                stae= index_my_window;
                break;
            default:
                break;
            }
            command_button_logical(xmenu+80,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi,IDcommand);// int x, inty ,bool state, char *textedesc, int midiaffectation
        }


//3ème colonne grands blocs
        for(int cl=0; cl<6; cl++)
        {
            switch(cl)
            {
            case 0:
                IDmidi=752;
                IDcommand=cl+20;
                sprintf(nom_commande,"Faders");
                sprintf(raccourci_commande,"F10");
                stae=index_show_faders;
                break;
            case 1:
                IDmidi=1336;
                IDcommand=cl+20;
                sprintf(nom_commande,"MiniFaders");
                sprintf(raccourci_commande,"Shift-F10");
                stae=index_show_minifaders;
                break;
            case 2:
                IDmidi=749;
                IDcommand=cl+20;
                sprintf(nom_commande,"Trichromy");
                sprintf(raccourci_commande,"F7");
                stae=index_trichro_window;
                break;
            case 3:
                IDmidi=1337;
                IDcommand=cl+20;
                sprintf(nom_commande,"Chasers");
                sprintf(raccourci_commande,"Shift-C");
                stae=index_window_chasers;
                break;
            case 4:
                IDmidi=1340;
                IDcommand=cl+20;
                strcpy(nom_commande,"GridPl.");
                strcpy(raccourci_commande,"");
                stae=index_grider_window;
                break;
            case 5:
                IDmidi=1829;
                IDcommand=cl+20;
                strcpy(nom_commande,"BazooKAT");
                strcpy(raccourci_commande,"");
                stae=index_bazoocat_menu_window;
                break;
            default:
                break;
            }
            command_button_logical(xmenu+150,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi,IDcommand);// int x, inty ,bool state, char *textedesc, int midiaffectation
        }



//4ème colonne grands blocs
        for(int cl=0; cl<6; cl++)
        {
            switch(cl)
            {
            case 0:
                IDmidi=750;
                IDcommand=cl+30;
                sprintf(nom_commande,"Track.Vid.");
                sprintf(raccourci_commande,"F8");
                stae=index_video_window;
                break;
            case 1:
                IDmidi=1339;
                IDcommand=cl+30;
                strcpy(nom_commande,"Mover");
                strcpy(raccourci_commande,"");
                stae=index_show_mover_window;
                break;
            case 2:
                IDmidi=1662;
                IDcommand=cl+30;
                strcpy(nom_commande,"ECHO");
                strcpy(raccourci_commande,"");
                stae=index_show_echo_window;
                break;
            case 3:
                IDmidi=756;
                IDcommand=cl+30;
                sprintf(nom_commande,"AudioPl.");
                sprintf(raccourci_commande,"Ctrl-A");
                stae=index_show_audio_window;
                break;
            case 4:
                IDmidi=747;
                IDcommand=cl+30;
                sprintf(nom_commande,"Name");
                sprintf(raccourci_commande,"F5");
                stae=index_type;
                break;
            case 5:
                IDmidi=1659;
                IDcommand=cl+30;
                strcpy(nom_commande,"Draw");
                strcpy(raccourci_commande,"");
                break;
            default:
                break;
            }
            command_button_logical(xmenu+220,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi,IDcommand);// int x, inty ,bool state, char *textedesc, int midiaffectation
        }



//5ème colonne grands blocs
        for(int cl=0; cl<5; cl++)
        {
            switch(cl)
            {
            case 0:
                IDmidi=755;
                IDcommand=cl+40;
                sprintf(nom_commande,"CFG-Menu");
                sprintf(raccourci_commande,"Shift-F11");
                stae=index_show_config_window;
                break;
            case 1:
                IDmidi=1341;
                IDcommand=cl+40;
                strcpy(nom_commande,"iCat Builder");
                strcpy(raccourci_commande,"");
                stae=index_window_gui_iCat;
                break;
            case 2:
                IDmidi=1338;
                IDcommand=cl+40;
                sprintf(nom_commande,"N-Pad");
                sprintf(raccourci_commande,"P");
                stae=index_visual_pad;
                break;
            case 3:
                IDmidi=1342;
                IDcommand=cl+40;
                strcpy(nom_commande,"Help");
                strcpy(raccourci_commande,"");
                stae=index_call_help;
                break;
            case 4:
                IDmidi=757;
                IDcommand=cl+40;
                sprintf(nom_commande,"QUIT");
                sprintf(raccourci_commande,"CTRL-F12");
                stae=index_do_quit_with_save;
                break;
            default:
                break;
            }
            command_button_logical(xmenu+290,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi,IDcommand);// int x, inty ,bool state, char *textedesc, int midiaffectation
        }
//fin condition focus + souris
    }
    return(0);
}


int Menus( int xmenu, int ymenu)
{
    Rect MyMainMenu(Vec2D(xmenu,ymenu),Vec2D(size_x_mainmenu,size_y_mainmenu));
    MyMainMenu.SetRoundness(15);
    MyMainMenu.Draw(CouleurFond);
    MyMainMenu.SetLineWidth(5);
    if(window_focus_id==W_MAINMENU)
    {
        MyMainMenu.DrawOutline(CouleurFader);
    }
    else
    {
        MyMainMenu.DrawOutline(CouleurLigne);
    }
    neuro.Print("MENUS",xmenu+100,ymenu+30);


// TEXT autoclose
    Rect Autoclose( Vec2D( xmenu+330,ymenu+8), Vec2D ( 30,15));
    Autoclose.SetRoundness(5);
    Autoclose.Draw(CouleurBlind.WithAlpha(index_text_auto_close));
    Autoclose.DrawOutline(CouleurLigne);
    petitchiffre.Print("Text",xmenu+295, ymenu+20);
    petitchiffre.Print("AutoClose",xmenu+295, ymenu+34);
    petitchiffre.Print("XX",xmenu+337, ymenu+20);




    int IDmidi=0;
//02/043/2014 unused var int IDcommand=0;
    char nom_commande[24];
    char raccourci_commande[24];
    bool stae=0;




//1ere colonne Sequenciel relatif
    for(int cl=0; cl<6; cl++) 			//sab - 07/08/2016 MOD (5 -> 6) - Hotkeys-window
    {
        switch(cl)
        {
        case 0://sequenciel window
            IDmidi=751;
//02/03/2014 unused var IDcommand=cl+10;
            sprintf(nom_commande,"CUELIST");
            sprintf(raccourci_commande,"F9");
            stae=index_window_sequentiel;
            break;
        case 1://time
            IDmidi=748;
//02/03/2014 unused var IDcommand=cl+10;
            sprintf(nom_commande,"TIME");
            sprintf(raccourci_commande,"F6");
            stae=index_time;
            break;
        case 2://banger
            IDmidi=753;
//02/03/2014 unused var IDcommand=cl+10;
            sprintf(nom_commande,"BANGER");
            sprintf(raccourci_commande,"F11");
            stae=index_show_banger_window;
            break;
        case 3://wizard
            IDmidi=1329;
//02/03/2014 unused var IDcommand=cl+10;
            strcpy(nom_commande,"WIZARD");
            strcpy(raccourci_commande,"");
            stae= index_show_wizard_window;
            break;
        case 4://save
            IDmidi=1330;
//02/03/2014 unused var IDcommand=cl+10;
            strcpy(nom_commande,"SAVE");
            strcpy(raccourci_commande,"");
            stae=index_menu_save;
            break;
		//sab - 07/08/2016 DEB - -window
        case 5://test sab <-- 5 = 0 + 5 = (menu_window_addbutton_wrkspc_dir_GridCol -1 ) + menu_window_addbutton_wrkspc_dir_GridLig
            IDmidi=menu_window_addbutton_wrkspc_dir_IDmidi; // +1 par rapport dernière commande ! n° de commande midi à ajouter dans le tableau affectations midi
            strcpy(nom_commande,menu_window_addbutton_wrkspc_dir_Name);
            strcpy(raccourci_commande,menu_window_addbutton_wrkspc_dir_Shortcut);
            stae= wrkspc_dir_window_isListening;
		//sab - 07/08/2016 FIN - -window

        default:
            break;
        }
        command_button_view(xmenu+10,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi);// int x, inty ,bool state, char *textedesc, int midiaffectation
    }

//2ème colonne Circuit relatif
    for(int cl=0; cl<6; cl++)
    {
        switch(cl)
        {
        case 0:
            IDmidi=1331;
//02/043/2014 unused var IDcommand=cl+10;
            sprintf(nom_commande,"PATCH");
            sprintf(raccourci_commande,"Shift-P");
            stae=index_patch_window;
            break;
        case 1:
            IDmidi=1332;
//02/03/2014 unused var IDcommand=cl+10;
            strcpy(nom_commande,"LIST");
            strcpy(raccourci_commande,"");
            stae=index_list_projecteurs;
            break;
        case 2:
            IDmidi=1594;
//02/03/2014 unused var IDcommand=cl+30;
            strcpy(nom_commande,"LIGHT PLOT");
            strcpy(raccourci_commande,"");
            stae=index_plot_window;
            break;
        case 3:
            IDmidi=1335;
//02/03/2014 unused var IDcommand=cl+10;
            strcpy(nom_commande,"Freeze");
            strcpy(raccourci_commande,"");
            stae=index_do_freeze;
            break;
        case 4:
            IDmidi=1541;
//02/03/2014 unused var IDcommand=cl+10;
            strcpy(nom_commande,"Exclude");
            strcpy(raccourci_commande,"");
            stae=index_do_exclude;
            break;
        case 5://my window
            IDmidi=2047; //a re définir voir tableau affectations midi
//02/03/2014 unused var IDcommand=cl+10;
            strcpy(nom_commande,"MY WINDOW");
            strcpy(raccourci_commande,"");
            stae= index_my_window;
            break;
        default:
            break;
        }
        command_button_view(xmenu+80,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi);// int x, inty ,bool state, char *textedesc, int midiaffectation
    }


//3ème colonne grands blocs
    for(int cl=0; cl<6; cl++)
    {
        switch(cl)
        {
        case 0:
            IDmidi=752;
//02/043/2014 unused var IDcommand=cl+20;
            sprintf(nom_commande,"FADERS");
            sprintf(raccourci_commande,"F10");
            stae=index_show_faders;
            break;
        case 1:
            IDmidi=1336;
//02/03/2014 unused var IDcommand=cl+20;
            sprintf(nom_commande,"MiniFaders");
            sprintf(raccourci_commande,"Shift-F10");
            stae=index_show_minifaders;
            break;
        case 2:
            IDmidi=749;
//02/03/2014 unused var IDcommand=cl+20;
            sprintf(nom_commande,"Trichromy");
            sprintf(raccourci_commande,"F7");
            stae=index_trichro_window;
            break;
        case 3:
            IDmidi=1337;
//02/03/2014 unused var IDcommand=cl+20;
            sprintf(nom_commande,"CHASERS");
            sprintf(raccourci_commande,"Shift-C");
            stae=index_window_chasers;
            break;
        case 4:
            IDmidi=1340;
//02/03/2014 unused var IDcommand=cl+30;
            strcpy(nom_commande,"GRID PL.");
            strcpy(raccourci_commande,"");
            stae=index_grider_window;
            break;
        case 5:
            IDmidi=1829;
            strcpy(nom_commande,"BazooKAT");
            strcpy(raccourci_commande,"");
            stae=index_bazoocat_menu_window;
            break;
        default:
            break;
        }
        command_button_view(xmenu+150,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi);// int x, inty ,bool state, char *textedesc, int midiaffectation
    }


//4ème colonne grands blocs
    for(int cl=0; cl<6; cl++)
    {
        switch(cl)
        {
        case 0:
            IDmidi=750;
//02/043/2014 unused var IDcommand=cl+20;
            sprintf(nom_commande,"Track.Vid.");
            sprintf(raccourci_commande,"F8");
            stae=index_video_window;
            break;
        case 1:
            IDmidi=1339;
//02/03/2014 unused var IDcommand=cl+30;
            strcpy(nom_commande,"Mover");
            strcpy(raccourci_commande,"");
            stae=index_show_mover_window;
            break;
        case 2:
            IDmidi=1662;
//02/03/2014 unused var IDcommand=cl+30;
            strcpy(nom_commande,"ECHO");
            strcpy(raccourci_commande,"");
            stae=index_show_echo_window;
            break;
        case 3:
            IDmidi=756;
//02/03/2014 unused var IDcommand=cl+30;
            sprintf(nom_commande,"AUDIO PL.");
            sprintf(raccourci_commande,"Ctrl-A");
            stae=index_show_audio_window;
            break;
        case 4:
            IDmidi=747;
//02/03/2014 unused var IDcommand=cl+30;
            sprintf(nom_commande,"NAME");
            sprintf(raccourci_commande,"F5");
            stae=index_type;
            break;
        case 5:
            IDmidi=1659;
//02/03/2014 unused var IDcommand=cl+30;
            strcpy(nom_commande,"DRAW");
            strcpy(raccourci_commande,"");
            stae=index_draw_window;
            break;
        default:
            break;
        }
        command_button_view(xmenu+220,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi);// int x, inty ,bool state, char *textedesc, int midiaffectation
    }

//5ème colonne grands blocs
    for(int cl=0; cl<5; cl++)
    {
        switch(cl)
        {
        case 0:
            IDmidi=755;
//02/043/2014 unused var IDcommand=cl+40;
            sprintf(nom_commande,"CFG-Menu");
            sprintf(raccourci_commande,"Shift-F11");
            stae=index_show_config_window;
            break;

        case 1:
            IDmidi=1341;
//02/03/2014 unused var IDcommand=cl+30;
            strcpy(nom_commande,"iCat Builder");
            strcpy(raccourci_commande,"");
            stae=index_window_gui_iCat;
            break;
        case 2:
            IDmidi=1338;
//02/03/2014 unused var IDcommand=cl+30;
            sprintf(nom_commande,"N-Pad");
            sprintf(raccourci_commande,"P");
            stae=index_visual_pad;
            break;
        case 3:
            IDmidi=1342;
//02/03/2014 unused var IDcommand=cl+40;
            strcpy(nom_commande,"Help");
            strcpy(raccourci_commande,"");
            stae=index_call_help;
            break;
        case 4:
            IDmidi=757;
//02/03/2014 unused var IDcommand=cl+40;
            sprintf(nom_commande,"QUIT");
            sprintf(raccourci_commande,"Ctrl-F12");
            stae=index_do_quit_with_save;
            break;
        default:
            break;
        }
        command_button_view(xmenu+290,ymenu+50+(cl*25),stae,nom_commande,raccourci_commande,IDmidi);// int x, inty ,bool state, char *textedesc, int midiaffectation
    }

    return(0);
}


