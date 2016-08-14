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

* \file hotkey_triggers.h
* \brief {Declaration of global functions of White Cat - global for hotkeys management}
* \author Rui Serge Azevedo Brooks from Christoph Guillermet's original sources
* \version {0.8.9.0}
* \date {01/02/2015}

 White Cat - hotkey

*   Déclaration des méthodes des raccourcis clavier de White Cat
*
*
*/

#ifndef WHC_HOTKEY_FCT_H
#define WHC_HOTKEY_FCT_H

	// global - hotkey
    void whc_hk_save(); //01 Sauvegarde générale - Quick save
    void whc_hk_save_and_quit(); //02  Quitter avec sauvegarde - Quit and save
    void whc_hk_quit(); //03 Quitter sans sauvegarde - Quit without sav
    void whc_hk_snapshot_close_windows(); //04 Snapshot et extinction des fenêtres - Snapshot and closing windows [SHIFT][PRINT SCREEN]
	void whc_hk_snapshot_open_windows(); //05 Rappel du Snapshot des fenêtres - Recall windows snapshot [CTRL][PRINT SCREEN]
	void whc_hk_cycle_forward_open_windows(); //06 Circulation dans les principales fenêtres - Cycle forward thru open windows	[PGUP]
	void whc_hk_cycle_backward_open_windows(); //07 Circulation dans les principales fenêtres - Cycle backward thru open windows [PGDOWN]
	void whc_hk_open_forward_solo_windows(); //08 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]
	void whc_hk_open_backward_solo_windows(); //09 Appel solo dans les principales fenêtres - Open windows in solo mode [CTRL][PGDOWN]

    void whc_hk_Store_mode(); // 10;Transverse commands;Store mode;0;0;0;47;[F1]
	void whc_hk_Modify_mode(); // 11;Transverse commands;Modify mode;0;0;0;48;[F2]
	void whc_hk_Report_mode(); //12;Transverse commands;Report mode;0;0;0;49;[F3]
	void whc_hk_Clear_mode(); //13;Transverse commands;Clear Mode;0;0;0;50;[F4]
	void whc_hk_Name(); //14;Transverse commands;Name (key input zone);0;0;0;51;[F5]
	void whc_hk_Time(); //15;Transverse commands;Time;0;0;0;52;[F6]
	void whc_hk_Trichromy(); //16;Transverse commands;Trichromy;0;0;0;53;[F7]
	void whc_hk_Video_Tracking(); //17;Transverse commands;Video Tracking;0;0;0;54;[F8]
	void whc_hk_CueList(); //18;Transverse commands;CueList;0;0;0;55;[F9]
	void whc_hk_Faders(); //19;Transverse commands;Faders;0;0;0;56;[F10]
	void whc_hk_MiniFaders(); //20;Transverse commands;MiniFaders;1;0;0;56;[SHIFT]+[F10]
	void whc_hk_Banger(); //21;Transverse commands;Banger;0;0;0;57;[F11]
	void whc_hk_Blind_mode(); //22;Transverse commands;Blind mode;0;1;0;57;[CTRL]+[F11]
	void whc_hk_CFG_Menu(); //23;Transverse commands;CFG Menu;1;0;0;57;[SHIFT]+[F11]
	void whc_hk_Chasers(); //24;Transverse commands;Chasers;1;0;0;3;[SHIFT]+[C]
	void whc_hk_Mover(); //25;Transverse commands;Mover;1;0;0;105;[SHIFT]+[M]

//26;Channels;selected all channels;0;0;0;25;[Y]
//27;Channels;unselected channels;0;0;0;21;[U]
//28;Channels;moving selection (left);0;0;0;82;[<-]
//29;Channels;moving selection (right);0;0;0;83;[->]
//30;Channels;Full level (for the selection);0;0;0;9;[I]
//31;Channels;Level to Zero (for the selection);0;0;0;15;[O]
//32;Channels;plus % (for the selection);0;0;0;84;[ARROW UP]
//33;Channels;minus % (for the selection);0;0;0;85;[ARROW DOWN]
//34;Channels;Check Channel left;0;1;0;82;[CTRL]+[<-]
//35;Channels;Check Channel right;0;1;0;83;[CTRL]+[->]
//36;Channels;Copy to the Clipboard Select channels;0;1;0;3;[CTRL]+[C]
//37;Channels;Paste channels from clipboard;0;1;0;22;[CTRL]+[V]
//38;Channels;Get (Import channels from a memory);0;1;0;7;[CTRL]+[G]
//39;CueList and memories;Memory recording/deleting - Create or over record a memory number;1;0;0;47;[SHIFT]+[F1]
//40;CueList and memories;Memory recording/deleting - Create memory adding the faders;1;0;0;49;[SHIFT]+[F3]
//41;CueList and memories;Memory recording/deleting - Delete memory;1;0;0;77;[SHIFT]+[F3]
//42;CueList and memories;Memory recording/deleting - Over record on stage or blind;0;1;0;47;[CTRL]+[F1]
//43;CueList and memories;Memory recording/deleting - Over record on stage or blind with faders;0;1;0;49;[CTRL]+[F3]
//44;CueList and memories;Memory recording/deleting - Reload a memory;0;1;0;23;[CTRL]+[Z]
//45;CueList and memories;Memory recording/deleting - Reload a deleted mem;1;0;0;23;[SHIFT]+[Z]
//46;CueList and memories;GET level of selected channels from memory;0;1;0;7;[CTRL]+[G]
//47;CueList and memories;Navigating thru memories - Previous mem on stage;0;1;0;26;[CTRL]+[W]
//48;CueList and memories;Navigating thru memories - Next mem on stage;0;1;0;24;[CTRL]+[X]
//49;CueList and memories;Navigating thru memories - Previous mem on preset;1;0;0;26;[SHIFT]+[W]
//50;CueList and memories;Navigating thru memories - Next mem on preset;1;0;0;24;[SHIFT]+[X]
//51;CueList and memories;Crossfade GO/PAUSE;0;0;0;75;[SPACE]
//52;CueList and memories;Crossfade GO BACK;0;1;0;75;[CTRL]+[SPACE]
//53;CueList and memories;Crossfade DOUBLE GO;1;0;0;75;[SHIFT]+[SPACE]
//54;Transverse commands;Patch;1;0;0;16;[SHIFT]+[P]
//55;Transverse commands;Numpad;0;0;0;16;[P]
//56;Patch;Dimmers selection - select all dimmers;1;0;0;25;[SHIFT]+[Y]
//57;Patch;Dimmers selection - unselect all dimmers;1;0;0;21;[SHIFT]+[U]
//58;Patch;Check Dimmer - (left);1;0;0;82;[SHIFT]+[<-]
//59;Patch;Check Dimmer - (right);1;0;0;83;[SHIFT]+[->]
//60;VideoTracking;Select Presets 1;0;0;0;26;[W]
//61;VideoTracking;Select Presets 2;0;0;0;24;[X]
//62;VideoTracking;Select Presets 3;0;0;0;3;[C]
//63;VideoTracking;Select Presets 4;0;0;0;22;[V]
//64;VideoTracking;Select Presets 5;0;0;0;2;[B]
//65;VideoTracking;Select Presets 6;0;0;0;14;[N]
//66;VideoTracking;Select roi 1;0;0;0;17;[A]
//67;VideoTracking;Select roi 2;0;0;0;23;[Z]
//68;VideoTracking;Select roi 3;0;0;0;5;[E]
//69;VideoTracking;Select roi 4;0;0;0;18;[R]
//70;VideoTracking;Select roi 5;0;0;0;20;[T]
//71;VideoTracking;Select roi 6;0;0;0;25;[Y]
//72;VideoTracking;Select roi 7;0;0;0;1;[Q]
//73;VideoTracking;Select roi 8;0;0;0;19;[S]
//74;VideoTracking;Select roi 9;0;0;0;4;[D]
//75;VideoTracking;Select roi 10;0;0;0;6;[F]
//76;VideoTracking;Select roi 11;0;0;0;7;[G]
//77;VideoTracking;Select roi 12;0;0;0;8;[H]
    //
    void whc_hotkeys_init();

#endif // WHC_HOTKEY_FCT_H

