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

* \file logicals_intres.cpp
* \brief {fonction logique}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions logique d'enregistrement de mémoir et autres
*
*   Logic fonctions for cue record and others
*
 **/


int entetes_confirmation()
{
  //logicals strings
 if(index_do_delete_mem==1)
 {
       int mem_to_delete=0;
       if(numeric_postext>0)
       {
       mem_to_delete=(int)(atof(numeric)*10.0001);
       }
       else if(numeric_postext==0)
       {
       switch(index_blind)
       {
       case 0:
       mem_to_delete=position_onstage;
       break;
       case 1:
       mem_to_delete=position_preset;
       break;
       default: break;
       }
       }
     sprintf(string_confirmation,"Delete Mem %d.%d?", mem_to_delete/10,mem_to_delete%10);
 }

 else if(index_do_create_mem==1)
 {
 int mem_to_create=0;
 if(numeric_postext>0)
   {
   mem_to_create=(int)(atof(numeric)*10.0001);
   }
 else
 {
   for(int l=position_preset/10;l<1000;l++)
   {
   if(MemoiresExistantes[l*10]==0)
   {
    mem_to_create=l*10;
    break;
   }
   }
 }


 if(MemoiresExistantes[mem_to_create]==0)
 {
 if(numeric_postext>0)
   {
 sprintf(string_confirmation,"Create Mem %d.%d ?", mem_to_create/10,mem_to_create%10);
   }
 else  {
 sprintf(string_confirmation,"Add a Memory to CueList  ?");
   }
 }
 else if(MemoiresExistantes[mem_to_create]==1)
{
 sprintf(string_confirmation,"Sure to Over-Record Mem %d.%d ?", mem_to_create/10,mem_to_create%10);
 }
 }

 else if(index_do_create_mem_plus_faders==1)
 {
         int mem_to_create=0;
         if(numeric_postext>0)
           {
           mem_to_create=(int)(atof(numeric)*10.0001);
           }
         else
         {
           for(int l=position_preset/10;l<1000;l++)
           {
           if(MemoiresExistantes[l*10]==0)
           {
            mem_to_create=l*10;
            break;
           }
           }
         }
         if(MemoiresExistantes[mem_to_create]==0)
         {
          if(numeric_postext>0)
           {
         sprintf(string_confirmation,"Create Mem %d.%d ?", mem_to_create/10,mem_to_create%10);
            }
         else  {
         sprintf(string_confirmation,"Add a Memory to CueList  ?");
           }
         }
         else if(MemoiresExistantes[mem_to_create]==1)
         {
         sprintf(string_confirmation,"Sure to Over-Record Mem %d.%d ?", mem_to_create/10,mem_to_create%10);
         }
 }

  else if(index_do_overecord_mem_plus_faders==1)//CTRL F3
 {
     int mem_to_create=0;



     switch(index_blind)
     {
     case 0:
          mem_to_create=position_onstage;
     break;
     case 1:
          mem_to_create=position_preset;
     break;
     default: break;
     }
     sprintf(string_confirmation,"OverRecord Mem %d.%d plus faders ?", mem_to_create/10,mem_to_create%10);
 }

else if(index_copy_mem_in==1)//CTRL c v avec num de mem
   {
        int mem_to_rec=(int)(atof(numeric)*10.0001);
        if(MemoiresExistantes[mem_to_rec]==0)
        {
         sprintf(string_confirmation,"Create Mem %d.%d from Mem %d.%d ?", mem_to_rec/10,mem_to_rec%10,CTRLC_mem_to_copy/10,CTRLC_mem_to_copy%10);
        }
        else
        {
          sprintf(string_confirmation,"! Replace Mem %d.%d by Mem %d.%d ?", mem_to_rec/10,mem_to_rec%10,CTRLC_mem_to_copy/10,CTRLC_mem_to_copy%10);
        }
   }

 else if(index_do_link_membefore==1)
 {
     if(Links_Memoires[mem_before_one]==0)
     {
     sprintf(string_confirmation,"Link Mem %d.%d ?", mem_before_one/10,mem_before_one%10);
     }
     else {sprintf(string_confirmation,"Unlink Mem %d.%d ?", mem_before_one/10,mem_before_one%10);     }
 }

 else if(index_do_link_memonstage==1)
 {
     if(Links_Memoires[position_onstage]==0)
     {
     sprintf(string_confirmation,"Link Mem %d.%d ?", position_onstage/10,position_onstage%10);
     }
     else {sprintf(string_confirmation,"Unlink Mem %d.%d ?", position_onstage/10,position_onstage%10);     }
 }
 else if(index_do_link_memonpreset==1)
 {
     if(Links_Memoires[position_preset]==0)
     {
     sprintf(string_confirmation,"Link Mem %d.%d ?", position_preset/10,position_preset%10);
     }
     else {sprintf(string_confirmation,"Unlink Mem %d.%d ?", position_preset/10,position_preset%10);     }
 }
 else if(index_do_link_memother==1)
 {
     if(Links_Memoires[other_mem_in_loop]==0)
     {
     sprintf(string_confirmation,"Link Mem %d.%d ?", other_mem_in_loop/10,other_mem_in_loop%10);
     }
     else {sprintf(string_confirmation,"Unlink Mem %d.%d ?", other_mem_in_loop/10,other_mem_in_loop%10);     }
 }
 else if(index_do_record_on_faders==1)
 {
     if (numeric_postext==0)
     {
     sprintf(string_confirmation,"Record in Fader %d Dock %d ?", (fader_selected_for_record+1),(dock_selected_for_record+1) );
     }
     else if(numeric_postext>0 )
     {
      int mem_to_load= (int)(atof(numeric)*10.0001);
      sprintf(string_confirmation,"Store in Fader %d Dock %d Mem %d.%d ?", (fader_selected_for_record+1),(dock_selected_for_record+1),mem_to_load/10,mem_to_load%10 );
     }
 }
 else if(index_do_modify_on_faders==1)
 {
 sprintf(string_confirmation,"Modify in Fader %d Dock %d  ?", (fader_selected_for_record+1),(dock_selected_for_record+1));
 }
 else if(index_do_report_on_faders==1)
 {
 sprintf(string_confirmation,"Report all in Fader %d Dock %d  ?",(fader_selected_for_record+1),(dock_selected_for_record+1));
 }
  else if(index_do_affect_color_on_faders==1)
 {
 sprintf(string_confirmation,"Affect Color Wheel %d in Fader %d Dock %d  ?",(dock_color_selected+1),(fader_selected_for_record+1),(dock_selected_for_record+1));
 }
 else if(index_do_dmx_to_dock==1)
 {
 sprintf(string_confirmation,"Affect Dmx In in Fader %d Dock %d  ?",(fader_selected_for_record+1),(dock_selected_for_record+1));
 }
 else if(index_do_artnet_to_dock==1)
 {
 sprintf(string_confirmation,"Affect Art-Net %d in Fader %d Dock %d  ?",select_artnet_to_listen,(fader_selected_for_record+1),(dock_selected_for_record+1));
 }
 else if(index_do_video_to_dock==1)
 {
 sprintf(string_confirmation,"Affect Video Tracking in Fader %d Dock %d  ?",(fader_selected_for_record+1),(dock_selected_for_record+1));
 }
 else if(index_do_affect_color_trichro==1)
 {
   if (couleur_to_affect==0){ sprintf(string_confirmation,"Affect As RED for Color Preset %d  ?",dock_color_selected+1); }
   else if (couleur_to_affect==1){ sprintf(string_confirmation,"Affect As GREEN for Color Preset %d  ?",dock_color_selected+1); }
   else if (couleur_to_affect==2){ sprintf(string_confirmation,"Affect As BLUE for Color Preset %d  ?",dock_color_selected+1); }
   else if (couleur_to_affect==3){ sprintf(string_confirmation,"Affect As YELLOW for Color Preset %d  ?",dock_color_selected+1); }
 }
 else if(index_do_affect_roi==1)
 {
  sprintf(string_confirmation,"Affect To ROI   %d  in %d ?",dock_roi_selected+1,tracking_dock_selected+1);
 }
  else if(index_do_clear_my_roi==1)
 {
  sprintf(string_confirmation,"Clear ROI   %d  in %d?",dock_roi_selected+1,tracking_dock_selected+1);
 }
  else if(index_do_clear_my_video_preset==1)
 {
  sprintf(string_confirmation,"Clear All ROI in Video Preset %d  ?",tracking_dock_to_clean+1);
 }
 else if(index_do_overrecord_mem==1)
 {
  if(index_blind==0)
  {
  sprintf(string_confirmation,"Over Record %d.%d ?",position_onstage/10,position_onstage%10);
  }
  else if(index_blind==1)
  {
  sprintf(string_confirmation,"Over Record %d.%d (Blind) ?",position_preset/10,position_preset%10);
  }
 }
 else if(index_do_clear_dock==1)
 {
   sprintf(string_confirmation,"Clear in Fader %d Dock %d  ?",(fader_selected_for_record+1),(dock_selected_for_record+1));
 }
 else if(index_do_reload_mem==1)
 {
 if(index_blind==0)
 {
  sprintf(string_confirmation,"Reload Mem %d.%d ?",position_onstage/10,position_onstage%10);
 }
 else
 {
  sprintf(string_confirmation,"Reload Mem %d.%d (Blind) ?",position_preset/10,position_preset%10);
 }
 }
 else if(index_do_resurrect_mem==1)
 {
 sprintf(string_confirmation,"Resurect Mem %d.%d ?",mem_to_resurrect/10,mem_to_resurrect%10);
 }
 else if(index_do_clear_on_faders==1)
 {
    sprintf(string_confirmation,"Clear completely content of Fader %d ?",(fader_selected_for_record+1));
 }
 else if(index_do_jump_while_cross==1)
 {
  //christoph 19/12/14
  int tmpmp=(atof(numeric)*10.0001)/10;
  int tmpmp2=(int)(atof(numeric)*10.0001)%10;
  //sprintf(string_confirmation,"Panic Jump to mem %d.%d ?",(int)(atof(numeric)*10.0001)/10,(int)(atof(numeric)*10.0001)%10);
  sprintf(string_confirmation,"Panic Jump to mem %d.%d ?",tmpmp,tmpmp2);
 }

 else if( index_do_export==1)
 {
 switch(index_export_choice)
 {
 case 0:
  sprintf(string_confirmation,"Export ASCII as %s ?", importfile_name);
 break;
 case 3:
  sprintf(string_confirmation,"Export pdf as %s ?", importfile_name);
 break;
 default: break;
 }
 }
 else if( index_do_import==1)
 {
 switch(index_export_choice)
 {
 case 0:
 sprintf(string_confirmation,"Import %s as ASCII ?", importfile_name);
 break;
 case 1:
   sprintf(string_confirmation,"Import %s (schwartzpeter folder)?", importfile_name);
 break;
 case 2:
   sprintf(string_confirmation,"Import %s  as ALQ ?", importfile_name);
 break;
 default: break;
 }
 }

 else if( index_do_saveshow==1)
 {
 sprintf(string_confirmation,"Save Show as %s ?", savefile_name);
 }

 else if( index_do_loadshow==1)
 {
 sprintf(string_confirmation,"Load Show as %s ?", savefile_name);
 }
  else if(index_do_resetshow==1)
 {
 sprintf(string_confirmation,"Reset the actual show in memory ?");
 }
  else if( index_do_freeze==1)
 {
 sprintf(string_confirmation,"Freeze / Unfreeze selected channels ?");
 }

 else if( index_do_clear_patch==1)
 {
 sprintf(string_confirmation,"Clear selected dimmers ?");
 }
 else if( index_do_default_patch==1)
 {
 sprintf(string_confirmation,"Set to default selected dimmers ?");
 }
 else if( index_do_quit_with_save==1)
 {
 sprintf(string_confirmation,"Quit WhiteCat and save ?");
 }
 else if( index_do_quit_without_save==1)
 {
 sprintf(string_confirmation,"Quit WhiteCat without save ?");
 }

 else if(index_do_ask_call_audio_folder==1)
 {
 sprintf(string_confirmation,"Use in /audio, folder %s ?", numeric);
 }

 else if(index_do_audio_to_dock==1)
 {
 switch(audio_type_for_dock_affectation_is)
 {
 case 0:
 sprintf(string_confirmation,"Affect PlayerVolume %d to Fader %d Dock%d  ?",(player_to_affect_to_dock+1),(fader_selected_for_record+1),(dock_selected_for_record+1));
 break;
 case 1:
 sprintf(string_confirmation,"Affect PlayerPan %d to Fader %d Dock%d  ?",(player_to_affect_to_dock+1),(fader_selected_for_record+1),(dock_selected_for_record+1));
 break;
 case 2:
 sprintf(string_confirmation,"Affect PlayerPitch %d to Fader %d Dock%d  ?",(player_to_affect_to_dock+1),(fader_selected_for_record+1),(dock_selected_for_record+1));
 break;
 default: break;
 }
 }

 else if( index_do_clear_lock_preset==1)
 {
   sprintf(string_confirmation,"Clear Lock Preset %d  ?",(lock_preset_selected_for_record+1));

 }

 else if( index_do_banger_memonstage==1)
 {
     sprintf(string_confirmation,"Affect banger %d to memory %d.%d ?", affect_banger_number, position_onstage/10,position_onstage%10 );
 }

 else if( index_do_banger_memonpreset==1)
 {
     sprintf(string_confirmation,"Affect banger %d to memory %d.%d ?", affect_banger_number, position_preset/10,position_preset%10 );
 }

else if( index_do_banger_membeforeone==1)
 {
     sprintf(string_confirmation,"Affect banger %d to memory %d.%d ?", affect_banger_number, mem_before_one/10,mem_before_one%10 );
 }

 else if (index_do_banger_memother==1)
 {
 sprintf(string_confirmation,"Affect banger %d to memory %d.%d ?", affect_banger_number , other_mem_in_loop/10,other_mem_in_loop%10 );
 }


  else if(index_do_wizard_ch==1)
 {
 switch(wizard_amplitude_is_global)
 {
 case 0:
 sprintf(string_confirmation,"Do Wizard CH from Mem %d.%d to Mem %d.%d ?",wizard_from_mem/10,wizard_from_mem%10,wizard_to_mem/10,wizard_to_mem%10);
 break;
 case 1:
 sprintf(string_confirmation,"Do Wizard CH Action on ALL memories ?");
 break;
 default: break;
 }
 }

else if(index_do_wizard_mem==1)
{
 switch(wizard_amplitude_is_global)
 {
 case 0:
 sprintf(string_confirmation,"Do Wizard MEM from Mem %d.%d to Mem %d.%d ?",wizard_from_mem/10,wizard_from_mem%10,wizard_to_mem/10,wizard_to_mem%10);
 break;
 case 1:
 sprintf(string_confirmation,"Do Wizard MEM Action on ALL memories ?");
 break;
 default: break;
 }
}
else if(index_wizard_do_reload_from_disk==1)
{
sprintf(string_confirmation,"Reload from disk ALL memories ?");
}

else if(index_do_record_direct_ch==1)//direct channel
{
switch( multiple_direct_chan)
{
case 0:
 sprintf(string_confirmation,"Affect as Direct Channel to Fader %d dock %d ?",fader_selected_for_record+1,dock_selected_for_record+1);
break;
case 1:
 sprintf(string_confirmation,"Affect x12 Direct Channel to Fader %d dock %d ?",fader_selected_for_record+1,dock_selected_for_record+1);
break;
default:
break;
}
}

else if(index_ask_curv_to_fader==1)//attribution de courbe à un fader
{
 sprintf(string_confirmation,"Affect to Fader %d Curve %d ?",fader_selected_for_record+1,curve_asked_for_fader);

}

else if ( index_re_init_client_artnet==1)
{
 sprintf(string_confirmation,"Re-Init Art-Net Client ?");
}
else if (index_re_init_serveur_artnet==1)
{
 sprintf(string_confirmation,"Re-Init Art-Net Server ?");
}

else if(index_do_affect_fx==1)
{
 sprintf(string_confirmation,"Store Chaser %d in Fader %d Dock %d ?",(chaser_selected+1), (fader_selected_for_record+1),(dock_selected_for_record+1) );
}

else if(index_do_dock_track==1)
{
sprintf(string_confirmation,"Record  Track %d Chaser %d ?",track_selected_for_record+1,chaser_selected_for_record+1 );
}
else if(index_do_report_track==1)
{
sprintf(string_confirmation,"Report in Track %d Chaser %d ?",track_selected_for_record+1,chaser_selected_for_record+1 );
}
else if(index_do_modify_track==1)
{
sprintf(string_confirmation,"Modify Track %d Chaser %d ?",track_selected_for_record+1,chaser_selected_for_record+1 );
}
else if(index_do_clear_track==1)
{
sprintf(string_confirmation,"Clear Track %d Chaser %d ?",track_selected_for_record+1,chaser_selected_for_record+1 );
}
else if(index_do_clear_chaser==1)
{
//sab 02/03/2014 impact  sprintf(string_confirmation,"Clear completely Chaser %d ?",track_selected_for_record+1,chaser_selected_for_record+1 );
 sprintf(string_confirmation,"Clear completely Chaser %d ?",chaser_selected_for_record+1 );
}


else if(index_do_store_chaser_preset==1)
{
sprintf(string_confirmation,"Store ON Preset %d in Chaser %d ?",chaser_preset_selected_for_record+1,chaser_selected_for_record+1 );
}

else if(index_do_clear_chaser_preset==1)
{
sprintf(string_confirmation,"Clear ON Preset %d in Chaser %d ?",chaser_preset_selected_for_record+1,chaser_selected_for_record+1 );
}

else if(index_record_minifader_preset==1)
{
sprintf(string_confirmation,"Record Selection in MiniFaders Preset %d ?",minifader_preset_is+1 );
}


else if(index_clear_minifader_preset==1)
{
sprintf(string_confirmation,"Clear MiniFaders Preset %d ?",minifader_preset_is+1 );
}

else if(index_record_minifader_lockpreset==1)
{
sprintf(string_confirmation,"Record in MiniFaders LockPreset %d ?",minifader_lockpreset_is+1 );
}

else if(index_ask_clear_iCatpage==1)
{
sprintf(string_confirmation,"Clear completely iCat Page %d ?",iCatPageis+1 );
}

else if(index_ask_icat_copyPage==1)
{
sprintf(string_confirmation,"Copy iCatPage %d in Page %d?",iCatPageis+1,iCatPageToCopyIn+1 );

}

else if( index_ask_clear_img_icat==1)
{
sprintf(string_confirmation,"Reset iCat images ? You need access to internet !" );
}

else if (index_ask_iCat_selectiv_clear==1)
{
switch(editing_GUI_type_iCat)
{
case 0:
sprintf(string_confirmation,"Clear selectively: FAMILY NO EDITABLE !!!" );
break;
case 1://sliders
sprintf(string_confirmation,"Clear selectively Sliders in iCatPage %d?",iCatPageis+1 );
break;
case 2://buttons
sprintf(string_confirmation,"Clear selectively Buttons in iCatPage %d?",iCatPageis+1 );
break;
case 3://strings
sprintf(string_confirmation,"Clear selectively Strings in iCatPage %d?",iCatPageis+1 );
break;
default:
sprintf(string_confirmation,"Wrong case");
break;
}
}//fin icat selectiv

//GRID
else if(index_clear_a_grid_step==1)
{
	//sab 02/03/2014 impact ajout %d
sprintf(string_confirmation,"Clear Step %d in Grid %d?",step_grid_to_clear+1, grid_to_clear+1 );
}

else if(index_clear_a_grid==1)
{
sprintf(string_confirmation,"Clear completely Grid %d?",grid_to_clear+1);
}

else if(index_clear_a_grid_serie_step==1)
{
sprintf(string_confirmation,"Clear in Grid %d Steps %d to %d?",grid_to_clear+1,step_grid_to_clear+1 , index_for_grid_stepto+1);
}

else if(index_for_copy_grid==1)
{
switch(index_grid_tostep_or_not)//mode un pas ou mode serie de pas
{
case 0:
sprintf(string_confirmation,"Copy Grid %d Step %d in Grid %d Step %d?",grid_to_clear+1,step_grid_to_clear+1 , destination_grid_for_copy+1,destination_step_for_copy+1);
break;
case 1:
sprintf(string_confirmation,"Copy Grid %d from Step %d to %d in Grid %d Step %d?",grid_to_clear+1,step_grid_to_clear+1 ,from_gridstep_to+1 , destination_grid_for_copy+1,destination_step_for_copy+1);
break;
default: break;
}
}

else if (index_for_insert_grid==1)
{
sprintf(string_confirmation,"Insert in Grid %d Step %d: %d Steps ?",grid_to_clear+1,step_grid_to_clear+1 , destination_step_for_copy+1);

}

else if(index_do_affect_grid_to_fader==1)
{
sprintf(string_confirmation,"Affect to Fader %d Dock %d GridPlayer %d?",fader_selected_for_record+1,dock_selected_for_record+1,gridplayer_to_affect_is+1);
}

else if(index_do_affect_step_gridplayer_to_mem==1)
{
sprintf(string_confirmation,"Affect to Mem %d.%d Step %d in GridPl.1?",index_mem_to_be_affected_by_gpl/10, index_mem_to_be_affected_by_gpl%10,gpl1_affect_step_to_mem);
}

else if(index_do_exclude==1)
{
sprintf(string_confirmation,"Exclude/Re-include channels from GM action?");
}

else if( index_do_affect_fgroup==1)
{
sprintf(string_confirmation,"Affect to Fader %d Dock %d selected faders?",fader_selected_for_record+1,dock_selected_for_record+1);
}

else if( index_do_affect_mover==1)
{
sprintf(string_confirmation,"Affect Mover Output to Fader %d Dock %d ?",fader_selected_for_record+1,dock_selected_for_record+1);
}

else if(  index_ask_delete_symbols_on_calc==1)
{
sprintf(string_confirmation,"Clear Plot layer %d? ",plot_layer_selected+1);
}


else if(index_ask_general_clear_on_plot==1)//clear general
{
switch (index_menus_lighting_plot)
{
case 0://bkgd
sprintf(string_confirmation,"Clear Plot BACKGROUND ? ");
break;
case 1://shapes
sprintf(string_confirmation,"Clear Plot SHAPES ? ");
break;
case 2://symbol
sprintf(string_confirmation,"Clear Plot SYMBOLS? ");
break;
case 3://legend
sprintf(string_confirmation,"Clear Plot LEGEND? ");
break;
default:
break;
}
}

else if(index_do_clear_all_the_patch==1)
{
sprintf(string_confirmation,"CLEAR completly the Patch? ");
}

else if(index_ask_clear_preset_relativ==1)
{
sprintf(string_confirmation,"CLEAR this relativ XY preset ? ");
}


else if(index_ask_record_preset_relativ==1)
{
sprintf(string_confirmation,"RECORD this relativ XY preset ? ");
}


else if(index_ask_modify_preset_relativ==1)
{
sprintf(string_confirmation,"MODIFY this relativ XY preset ? ");
}


else if(index_ask_record_selection_of_view==1)
{
sprintf(string_confirmation,"RECORD Channel View %d ? ",channel_view_is+1);
}


else if(index_ask_modify_selection_of_view==1)
{
sprintf(string_confirmation,"MODIFY Channel View %d ? ",channel_view_is+1);
}


else if(index_ask_clear_selection_of_view==1)
{
sprintf(string_confirmation,"CLEAR Channel View %d ? ",channel_view_is+1);
}

else if(index_ask_report_selection_of_view==1)
{
sprintf(string_confirmation,"REPORT Selected CH to Channel View %d ? ",channel_view_is+1);
}
else if(index_ask_build_view==1)
{

int nummem=(int)(atof(numeric)*10);

switch(channel_view_mode_builder[channel_view_is])//solo ou all
{
case 0:
      // 1 mem // 2 fader
     if(channel_view_type_of_behaviour[channel_view_is]==1)//mem
     {

      if(MemoiresExistantes[nummem]==1)
       {
      sprintf(string_confirmation,"Build Channel View %d from Mem %d.%d ? ",channel_view_is+1, nummem/10,nummem%10);
       }
       else {sprintf(string_confirmation,"Mem %d.%d doesn't exist ! ",nummem/10,nummem%10);}
      }
     else if(channel_view_type_of_behaviour[channel_view_is]==2)//fader
     {
     fader_selected_for_record=nummem/10;
     if(fader_selected_for_record>0 && fader_selected_for_record<49)
     {
     sprintf(string_confirmation,"Build Channel View %d from Fader %d ? ",channel_view_is+1,fader_selected_for_record );
     }
     else {   sprintf(string_confirmation,"Fader number must be between 1 and 48 ! "); }
     }
break;
case 1:
       if(channel_view_type_of_behaviour[channel_view_is]==0)//mem + faders
     {
     	//sab 02/03/2014 impact ajout %d
      sprintf(string_confirmation,"Build Channel View %d from ALL mems and faders? ",channel_view_is+1);
      }
      else if(channel_view_type_of_behaviour[channel_view_is]==1)//mem
     {
     	//sab 02/03/2014 impact ajout %d
      sprintf(string_confirmation,"Build Channel View %d from ALL mems ? ",channel_view_is+1);
      }
     else if(channel_view_type_of_behaviour[channel_view_is]==2)//fader
     {
     sprintf(string_confirmation,"Build Channel View %d from ALL Faders ? ",channel_view_is+1 );
     }
break;
default: break;
}
}

else if(index_ask_clear_a_move==1)
{
    sprintf(string_confirmation,"Clear Move %d? ",move_to_clear );
}

else if(index_ask_reinit_FS_client==1)
{
     sprintf(string_confirmation,"Re-init FS-iCat connexion ? " );
}

else if (ask_clear_draw_preset==1)
{
        sprintf(string_confirmation,"Clear Draw Preset %d? ",draw_prst_to_clear+1 );
}

else  if( index_do_draw_affect_to_dock==1)
{
    sprintf(string_confirmation,"Affect Draw Preset %d to Fader %d Dock %d ? ",draw_preset_selected_for_order+1,fader_selected_for_record+1, dock_selected_for_record+1 );
}


else  if( index_ask_clear_echo_preset==1)
{
    sprintf(string_confirmation,"Clear Echo Preset %d ? ",index_selected_echo_for_manipulation+1 );
}


else  if( index_do_affect_echo_to_dock==1)
{
    sprintf(string_confirmation,"Affect Echo Preset %d to Fader %d Dock %d ? ",echo_selected+1,fader_selected_for_record+1, dock_selected_for_record+1 );
}


else  if( index_ask_copy_banger==1)
{
    sprintf(string_confirmation,"Copy Banger %d to Banger %d ? ",index_banger_selected+1,index_banger_to_copy_in+1 );
}

else if(index_ask_clear_banger==1)
{
    sprintf(string_confirmation,"Clear Banger %d ?" ,index_banger_to_copy_in+1);
}


else  if( index_affect_wave_to_dock==1)
{
    sprintf(string_confirmation,"Affect WAVE Buffer to Fader %d Dock %d ? ",fader_selected_for_record+1, dock_selected_for_record+1 );
}


return(0);
}

int operations_confirmation()
{
   if(index_do_delete_mem==1)
   {
   int mem_to_delete=0;
   if(numeric_postext>0)
   {
   mem_to_delete=(int)(atof(numeric)*10.0001);
   }
   else if(numeric_postext==0)
   {
   switch(index_blind)
   {
   case 0:
   mem_to_delete=position_onstage;
   break;
   case 1:
   mem_to_delete=position_preset;
   break;
   default: break;
   }
   }
   delete_memory(mem_to_delete);
   }

   else if(index_do_create_mem==1)
   {
   int mem_to_rec=0;
   if(numeric_postext>0)
   {
   mem_to_rec=(int)(atof(numeric)*10.0001);
   }
   else
   {
   for(int l=position_preset/10;l<1000;l++)
   {
   if(MemoiresExistantes[l*10]==0)
   {
    mem_to_rec=l*10;
    break;
   }
   }
   }
   create_memory(mem_to_rec);
   }

   else if(index_do_create_mem_plus_faders==1)
   {
   int mem_to_rec=0;
   if(numeric_postext>0)
   {
   mem_to_rec=(int)(atof(numeric)*10.0001);
   }
   else
   {
   for(int l=position_preset/10;l<1000;l++)
   {
   if(MemoiresExistantes[l*10]==0)
   {
    mem_to_rec=l*10;
    break;
   }
   }
   }
   create_memory_plus_faders(mem_to_rec);
   }

   else if(index_copy_mem_in==1)//CTRL c v avec num de mem
   {
    int mem_to_rec=(int)(atof(numeric)*10.0001);
    if(mem_to_rec>0 && mem_to_rec<9999)
    {
     copy_mem_in(mem_to_rec);
     strcpy(numeric,"");
     numeric_postext=0;
    }
    refresh_mem_onpreset(position_preset);someone_changed_in_sequences=1;//icat
   }


   else if(index_do_overecord_mem_plus_faders==1)//CTRL F3
   {
    int mem_to_overrec=0;
    switch(index_blind)
    {
    case 0:
      mem_to_overrec=position_onstage;
    break;
     case 1:
      mem_to_overrec=position_preset;
     break;
     default: break;
     }
   overrecord_memory_plus_faders(mem_to_overrec);
   }

   else if(index_do_link_memonstage==1)
   {
   Links_Memoires[position_onstage]=toggle(Links_Memoires[position_onstage]);
   someone_changed_in_sequences=1;//icat
   }

   else if(index_do_link_memonpreset==1)
   {
   Links_Memoires[position_preset]=toggle(Links_Memoires[position_preset]);
   someone_changed_in_sequences=1;//icat
   }

    else if(index_do_link_membefore==1)
   {
   Links_Memoires[mem_before_one]=toggle(Links_Memoires[mem_before_one]);
   someone_changed_in_sequences=1;//icat
   }

   else if(index_do_link_memother==1)
   {
   Links_Memoires[other_mem_in_loop]=toggle(Links_Memoires[other_mem_in_loop]);
   if(other_mem_in_loop==mem_after_one)
   {
    someone_changed_in_sequences=1;//icat
   }
   }

   else if(index_do_record_on_faders==1)
   {
   DoDock(fader_selected_for_record,dock_selected_for_record);
   }

   else if(index_do_modify_on_faders==1)
   {
   DoModify(fader_selected_for_record,dock_selected_for_record);
   }

   else if(index_do_report_on_faders==1)
   {
   DoReport(fader_selected_for_record,dock_selected_for_record);
   }

   else if(index_do_affect_color_on_faders==1)
   {
   ClearDock(fader_selected_for_record,dock_selected_for_record);
   affect_color_to_dock(fader_selected_for_record,dock_selected_for_record)  ;
   index_affect_color_to_dock=0;
   }

   else if(index_do_dmx_to_dock==1)
   {
    affect_dmxIN_to_dock(fader_selected_for_record,dock_selected_for_record)  ;
    index_affect_dmxin=0;
   }

   else if(index_do_artnet_to_dock==1)
   {
   affect_network_to_dock(fader_selected_for_record,dock_selected_for_record);
   index_do_affect_net_to_dock=0;
   select_artnet_to_listen=0;
   }

   else if(index_do_video_to_dock==1)
   {
   affect_video_tracking_to_dock(fader_selected_for_record,dock_selected_for_record);
   index_affect_video_tracking_to_dock=0;
   }

   else if(index_do_affect_color_trichro==1)
   {
   affect_color_to(dock_color_selected,couleur_to_affect);
   }

   else if(index_do_affect_roi==1)
   {
   affect_to_tracker(tracking_dock_selected,dock_roi_selected);
   }

   else if(index_do_clear_my_roi==1)
   {
   set_to_default_my_roi(tracking_dock_selected,dock_roi_selected);tracker_clearmode=0;
   }

   else if(index_do_clear_my_video_preset==1)
   {
   set_to_default_this_tracker(tracking_dock_to_clean);
   tracker_clearmode=0;
   }

    else if(index_do_overrecord_mem==1)
   {
   if(index_blind==0)
   {record_memory(position_onstage);}
   else if (index_blind==1)
   {record_memory(position_preset);}
   }

   else if(index_do_clear_dock==1)
   {
   ClearDock(fader_selected_for_record,dock_selected_for_record);
   }

   else if(index_do_clear_on_faders==1)
   {
   ClearFader(fader_selected_for_record);
   }

   else if (index_do_reload_mem==1)
   {
   if(index_blind==0){refresh_mem_onstage(position_onstage); }
   else if(index_blind==1){refresh_mem_onpreset(position_preset);}
   }
   else if (index_do_resurrect_mem==1)
   {
   MemoiresExistantes[mem_to_resurrect]=1;
   detect_mem_before_one();
   detect_mem_preset();
   refresh_mem_onpreset(position_preset);
   }
   else if(index_do_jump_while_cross==1)
   {
   do_load_mem_preset_while_crossfade((int)(atof(numeric)*10.0001));//panic jump preset
   }


 else if( index_do_export==1)
 {
 switch(index_export_choice)
 {
 case 0://ASCII
 if(isASCII==1)
 {

 do_ASCII_export();
 scan_importfolder("ascii");
 strcpy(importfile_name,"");
 strcpy(string_typeexport_view,"");
 index_menu_save=0;
 sprintf(string_Last_Order,">>ASCII export done");
 isASCII=0; isPdf=0;  isSchwz=0;isAlq=0;
 }
  else {sprintf(string_Last_Order,">>This file is not an ASCII type file (.ASC) !");}
 break;

 case 3://PDF
 if(isPdf==1)
 {
 do_pdf_export();
 scan_importfolder("pdf");
 strcpy(importfile_name,"");
 strcpy(string_typeexport_view,"");
 sprintf(string_Last_Order,">>PDF export done");
 index_menu_save=0;
 isASCII=0; isPdf=0;  isSchwz=0;isAlq=0;
 }
 else {sprintf(string_Last_Order,">>This file is not a pdf type file (.PDF) !");}
 break;
 default: break;
 }
 }

 else if( index_do_import==1)
 {
 switch(index_export_choice)
 {
 case 0://ASCII
 if(isASCII==1)
 {
 reset_save_load_report_string();
 reset_show();
 do_ASCII_import();
 sprintf(my_show_is_coming_from,"Loaded from ASCII %s",importfile_name);//pour retracer d ou vient la conduite
 strcpy(importfile_name,"");
 strcpy(string_typeexport_view,"");
 sprintf(string_Last_Order,">>ASCII import done");
 index_menu_save=0;   isASCII=0; isPdf=0;  isSchwz=0;
 isAlq=0;

 index_show_save_load_report=1;there_is_change_on_show_save_state=1;
 }
 else {sprintf(string_Last_Order,">>This file is not an ASCII type file (.ASC) !");}
 break;
 case 1://Schwz
 if(isSchwz==1)
 {
 reset_save_load_report_string();
 reset_show();
 do_Schwartzpeter_import();
 sprintf(my_show_is_coming_from,"Loaded from SCHWZ %s",importfile_name);//pour retracer d ou vient la conduite
 strcpy(importfile_name,"");
 strcpy(string_typeexport_view,"");
 sprintf(string_Last_Order,">>SCHARTZPETER import done");
 index_menu_save=0;   isASCII=0; isPdf=0; isSchwz=0;
 isAlq=0;
 index_show_save_load_report=1;there_is_change_on_show_save_state=1;
 }
 else {sprintf(string_Last_Order,">>This file is not a schwartzpeter FOLDER !");}
 break;
 case 2://Alq
 if(isAlq==1)
 {
 reset_save_load_report_string();
 reset_show();
 do_Alq_import();
 sprintf(my_show_is_coming_from,"Loaded from ASCII ALQ %s",importfile_name);//pour retracer d ou vient la conduite
 strcpy(importfile_name,"");
 strcpy(string_typeexport_view,"");
 sprintf(string_Last_Order,">>Alq import done");
 index_menu_save=0;
 isASCII=0; isPdf=0; isSchwz=0; isAlq=0;
  index_show_save_load_report=1;there_is_change_on_show_save_state=1;
 }
 else {sprintf(string_Last_Order,">>This file is not a Strand ASCII type file (.ALQ) !");}
 break;
 default: break;
 }
}

 else if( index_do_saveshow==1)
 {
 reset_save_load_report_string();
 save_the_show(savefile_name);
 strcpy(savefile_name,"");
 index_type=0; index_menu_save=0;   isASCII=0; isPdf=0; isSchwz=0;isAlq=0;
 substract_a_window(W_SAVE);
 }

 else if( index_do_loadshow==1)
 {
 reset_save_load_report_string();
 load_the_show(savefile_name); index_menu_save=0;   index_type=0;
 isASCII=0; isPdf=0; isSchwz=0;isAlq=0;
 strcpy(string_typeexport_view,"");
 substract_a_window(W_SAVE);
 }

 else if(index_do_resetshow==1)
 {
 GlobInit();
 strcpy(string_typeexport_view,"");
 sprintf(string_Last_Order,">>Reset of show in memory done");

 }


 else if(index_do_freeze==1)
 {
 for (int fz=1;fz<514;fz++)
 {
 if(Selected_Channel[fz]==1)
 {
 if(freeze_array[fz]==0)
 {
     if(bufferSequenciel[fz]>=bufferFaders[fz])
    {
      freeze_state[fz]=bufferSequenciel[fz];
    }
    if(bufferFaders[fz]>bufferSequenciel[fz])
    {
      freeze_state[fz]=bufferFaders[fz];
    }
}
 else {bufferSaisie[fz]=freeze_state[fz];}
 freeze_array[fz]=toggle(freeze_array[fz]);
 }

 }
 }



 else if( index_do_clear_patch==1)
 {
 patch_clear_selected();
 patch_unselect_all_dimmers();
 generate_channel_view_list_from_patched_circuits();
 }
 else if( index_do_default_patch==1)
 {
 patch_to_default_selected();
 patch_unselect_all_dimmers();
 generate_channel_view_list_from_patched_circuits();
 }
 else if( index_do_quit_with_save==1)
 {
 index_quit=1;
 }
 else if(index_do_quit_without_save==1)
 {
 set_all_saves_indexes_at(0);
 reset_save_load_report_string();
 index_please_do_not_save=1;
 index_quit=1;
 }

else if( index_do_ask_call_audio_folder==1)
{
sprintf(audio_folder,"                        ");
for(int p=0;p<24;p++)
{
        if(numeric[p]==' '){audio_folder[p]='\0';break;}
        else {audio_folder[p]=numeric[p];}
}

reset_numeric_entry();
index_type=0;
sprintf(rep,"%s\\",mondirectory);
chdir (rep);
scan_audiofolder();
}

else if(index_do_audio_to_dock==1)
{
affect_audio_control_to_dock(fader_selected_for_record,dock_selected_for_record);
}



else if(index_do_clear_lock_preset==1)
{
for(int f=0;f<48;f++)
 {
 FaderLocked_Preset[lock_preset_selected_for_record][f]=0;
 StateOfFaderBeforeLock_Preset[lock_preset_selected_for_record][f]=0;
 LockFader_is_FullLevel_Preset[lock_preset_selected_for_record][f]=0;
 }
 master_lock_preset[lock_preset_selected_for_record]=0;
 index_main_clear=0;
}


else if( index_do_banger_memonstage==1)
{
Banger_Memoire[position_onstage]=affect_banger_number;
reset_numeric_entry();
sprintf(string_Last_Order,">> Attributed banger %d to memory %d.%d", affect_banger_number, position_onstage/10,position_onstage%10 );
}
else if( index_do_banger_memonpreset==1)
{
Banger_Memoire[position_preset]=affect_banger_number;
reset_numeric_entry();
sprintf(string_Last_Order,">> Attributed banger %d to memory %d.%d", affect_banger_number, position_preset/10,position_preset%10 );
}
else if( index_do_banger_membeforeone==1)
{
Banger_Memoire[mem_before_one]=affect_banger_number;
reset_numeric_entry();
sprintf(string_Last_Order,">> Attributed banger %d to memory %d.%d", affect_banger_number, mem_before_one/10,mem_before_one%10 );
}
else if(index_do_banger_memother==1)
{
Banger_Memoire[other_mem_in_loop]=affect_banger_number;
reset_numeric_entry();
sprintf(string_Last_Order,">> Attributed banger %d to memory %d.%d", affect_banger_number, other_mem_in_loop/10,other_mem_in_loop%10 );

}

else if(index_do_wizard_ch==1)
{
do_wizard_ch();
sprintf(string_Last_Order,">> Wizard CH done");
}

else if(index_do_wizard_mem==1)
{
do_wizard_mem();
sprintf(string_Last_Order,">> Wizard MEM done");
}

else if(index_wizard_do_reload_from_disk==1)
{
do_wizard_reload_from_disk();
sprintf(string_Last_Order,">> Show reloaded from disk");
}




else if(index_do_record_direct_ch==1)
{
do_direct_channel(fader_selected_for_record,dock_selected_for_record);
}


else if(index_ask_curv_to_fader==1)
{
FaderCurves[fader_selected_for_record]=curve_asked_for_fader-1;
sprintf(string_Last_Order,">> Affected curve %d to Fader %d",curve_asked_for_fader, fader_selected_for_record+1);
}


else if(index_re_init_client_artnet==1)
{
fermeture_client_artnet();
initialisation_client_artnet();
}

else if (index_re_init_serveur_artnet==1)
{
fermeture_serveur_artnet();
initialisation_serveur_artnet();
}


else if(index_do_affect_fx==1)
{
affect_chaser_to_dock(chaser_selected,   fader_selected_for_record, dock_selected_for_record  );
}


else if( index_do_dock_track==1)
{
DoDockChaserTrack(chaser_selected_for_record,track_selected_for_record);
}
else if( index_do_report_track==1)
{
DoReportChaserTrack(chaser_selected_for_record,track_selected_for_record);
}

else if( index_do_modify_track==1)
{
DoModifyChaserTrack(chaser_selected_for_record,track_selected_for_record);
}

else if( index_do_clear_track==1)
{
DoClearChaserTrack(chaser_selected_for_record,track_selected_for_record);
}
else if( index_do_clear_chaser==1)
{
DoClearAChaser(chaser_selected_for_record);
}

else if(index_do_store_chaser_preset==1)
{
chaser_store_in_preset(chaser_selected_for_record ,chaser_preset_selected_for_record);
}

else if(index_do_clear_chaser_preset==1)
{
chaser_clear_preset(chaser_selected_for_record ,chaser_preset_selected_for_record);
}

else if(index_record_minifader_preset==1)
{
minifader_selection_record(minifader_preset_is);
}

else if(index_clear_minifader_preset==1)
{
minifader_selection_clear(minifader_preset_is);
}


else if(index_record_minifader_lockpreset==1)
{
minifader_lockselection_record(minifader_lockpreset_is);
}

else if(index_ask_clear_iCatpage==1)
{
clear_iCat_page(iCatPageis);
}

else if(index_ask_icat_copyPage==1)
{
copy_iCatPage(iCatPageis,iCatPageToCopyIn);
}

else if(index_ask_clear_img_icat==1)
{
reset_and_recall_iCat_images();
}

else if(index_ask_iCat_selectiv_clear==1)
{
switch (editing_GUI_type_iCat)
{
case 1:
clear_iCat_sliders(iCatPageis);
break;
case 2:
clear_iCat_buttons(iCatPageis);
break;
case 3:
clear_iCat_strings(iCatPageis);
break;
default:
break;
}
}//fin selectiv clean

//GRIDER
else if(index_clear_a_grid_step==1)
{
clear_a_grid_step(grid_to_clear,step_grid_to_clear);
}

else if(index_clear_a_grid==1)
{
clear_a_grid(grid_to_clear);
}

else if(index_clear_a_grid_serie_step==1)
{
clear_part_of_a_grid(grid_to_clear,step_grid_to_clear , index_for_grid_stepto);
}

else if(index_for_copy_grid==1)
{
switch(index_grid_tostep_or_not)
{
case 0:
copy_step_to_step(grid_to_clear,step_grid_to_clear,destination_grid_for_copy,destination_step_for_copy);
break;
case 1:
copy_grid_partially(grid_to_clear,step_grid_to_clear,from_gridstep_to,destination_grid_for_copy,destination_step_for_copy);
break;
default: break;
}
}

else if(index_for_insert_grid==1)
{
insert_steps(grid_to_clear,step_grid_to_clear,destination_step_for_copy);
}

else if(index_do_affect_grid_to_fader==1)
{
DockTypeIs[fader_selected_for_record][dock_selected_for_record]=12;
faders_dock_grid_affectation[fader_selected_for_record][dock_selected_for_record]=gridplayer_to_affect_is;
}


else if(index_do_affect_step_gridplayer_to_mem==1)
{
set_from_seq_gridplayer1_next_step[index_mem_to_be_affected_by_gpl]= gpl1_affect_step_to_mem-1;
gpl1_affect_step_to_mem=0;
}




else if(index_do_exclude==1)
{
exclude_reinclude_channels_from_grand_master_action();
}

else if( index_do_affect_fgroup==1)
{
affect_selected_faders_to_fgroup(fader_selected_for_record,dock_selected_for_record);
}


else if( index_do_affect_mover==1)
{
affect_mover_to_fader(fader_selected_for_record,dock_selected_for_record);
index_affect_to_dock_mover=0;
index_do_affect_mover=0;
}

else if (  index_ask_delete_symbols_on_calc==1)
{
clear_calc(plot_layer_selected);
plot_layer_selected=0;
index_main_clear=0;
}

else if(index_ask_general_clear_on_plot==1)//clear general
{

switch (index_menus_lighting_plot)
{
case 0://bkgd
set_plot_background_to_default();
break;
case 1://shapes
for(int i=0;i<nbre_symbol_per_layer;i++)
{
clear_shape_slot(i);
}
nbre_shapes_on_plot=0;
number_of_shapes_groups=0;
break;
case 2://symbol
for(int i=0;i<3;i++)
{
clear_calc(i);
}
break;
case 3://legend
//clear_legend();
break;
default:
break;
}

}

else if(index_do_clear_all_the_patch==1)
{
 clear_completely_the_patch();
 generate_channel_view_list_from_patched_circuits();
}

else if(index_ask_clear_preset_relativ==1)
{
 clear_xyrelativ_preset(xyrelativ_preset)  ;
}

else if(index_ask_record_selection_of_view==1)
{
record_selection_in(channel_view_is);
Channel_View_MODE[channel_view_is]=1;
index_ask_record_selection_of_view=0;
}


else if(index_ask_modify_selection_of_view==1)
{
modify_selection_in(channel_view_is);
Channel_View_MODE[channel_view_is]=1;
index_ask_modify_selection_of_view=0;
}

else if(index_ask_report_selection_of_view==1)
{
report_selection_in(channel_view_is);
index_ask_report_selection_of_view=0;
}

else if(index_ask_clear_selection_of_view==1)
{
clear_selection_in(channel_view_is);
Channel_View_MODE[channel_view_is]=0;
index_ask_clear_selection_of_view=0;
}


else if(index_ask_build_view==1)
{

int nummem=(int)(atof(numeric)*10);

switch(channel_view_mode_builder[channel_view_is])//all ou solo
{
case 0:
      // 1 mem // 2 fader
     if(channel_view_type_of_behaviour[channel_view_is]==1)//mem
     {
     build_preset_view_from_mem(nummem,channel_view_is);
     }
     else if(channel_view_type_of_behaviour[channel_view_is]==2)//fader
     {
     fader_selected_for_record=nummem/10;
     if(fader_selected_for_record>0 && fader_selected_for_record<49)
     {
     build_preset_view_from_fader(fader_selected_for_record,channel_view_is);
     }
     }
break;
case 1:
      if(channel_view_type_of_behaviour[channel_view_is]==0)//mem + faders
      {
      build_preset_view_from_all_existing_mems_and_faders(channel_view_is);
      }
      else if(channel_view_type_of_behaviour[channel_view_is]==1)//mem
     {
      build_preset_view_from_all_existing_mems(channel_view_is);
      }
     else if(channel_view_type_of_behaviour[channel_view_is]==2)//fader
     {
     build_preset_view_from_all_faders(channel_view_is);
     }
break;
default: break;
}
channel_view_type_of_behaviour[channel_view_is]=0;
channel_view_mode_builder[channel_view_is]=0;
}


else if(index_ask_clear_a_move==1)
{
    Clear_the_Move(move_to_clear);
}

else if(index_ask_reinit_FS_client==1)
{
   index_re_init_clientserveur_icat=1;
}


else if (ask_clear_draw_preset==1)
{
  clear_draw_preset(draw_prst_to_clear);
}


else  if( index_do_draw_affect_to_dock==1)
{
  affect_draw_preset_to_dock(draw_preset_selected_for_order,fader_selected_for_record, dock_selected_for_record);
}



else  if( index_ask_clear_echo_preset==1)
{
   clear_echo_preset(index_selected_echo_for_manipulation);
}


else  if(index_do_affect_echo_to_dock==1)
{
   affect_echo_to_dock(echo_selected,fader_selected_for_record, dock_selected_for_record);
}

else  if( index_ask_copy_banger==1)
{
    copy_banger(index_banger_selected,index_banger_to_copy_in);
}


else if(index_ask_clear_banger==1)
{
     clear_banger(index_banger_to_copy_in);
     sprintf(string_Last_Order,"Cleared Banger %d", index_banger_to_copy_in+1);
}

else if(index_affect_wave_to_dock==1)
{
    affect_wave_to_dock(fader_selected_for_record, dock_selected_for_record);
    sprintf(string_Last_Order,"Affected WAVE buffer to F % Dock %d", fader_selected_for_record, dock_selected_for_record);
}

   reset_indexs_confirmation();
   reset_numeric_entry();


 return(0);
}







int fenetre_confirm()
{
 entetes_confirmation();

 Rect FenetreConfirm(Vec2D(XConfirm,YConfirm),Vec2D(400,100));
 FenetreConfirm.SetRoundness(15);
 FenetreConfirm.SetLineWidth(epaisseur_ligne_fader*3);
 FenetreConfirm.Draw(CouleurFond);
 FenetreConfirm.Draw(CouleurBlind.WithAlpha(alpha_blinker));
 if(window_focus_id==W_ASKCONFIRM)
 {
  FenetreConfirm.DrawOutline(CouleurFader);
 }
 else { FenetreConfirm.DrawOutline(CouleurLigne);}

 neuromoyen.Print( string_confirmation,XConfirm+110,YConfirm+10+18, 250,  JUSTIFY);


 Rect EscBox(Vec2D(XConfirm+110,YConfirm+60),Vec2D(70,30));
 EscBox.SetRoundness(7.5);
 EscBox.Draw(CouleurFond);

 if(mouse_x>XConfirm+110 && mouse_x<XConfirm+110+70 && mouse_y>YConfirm+60 && mouse_y<YConfirm+60+30 && window_focus_id==W_ASKCONFIRM)
 {
 EscBox.Draw(CouleurFader);
 if(mouse_button==1 && mouse_released==0)
 {
 reset_indexs_confirmation();
 reset_index_actions();
 substract_a_window(W_ASKCONFIRM);
 substract_a_window(previous_window_focus_id);
 mouse_released=1;
 window_focus_id=previous_window_focus_id;
 add_a_window(window_focus_id);
 }
 }
 EscBox.DrawOutline(CouleurLigne);
 petitchiffre.Print("ESC",XConfirm+110+18, YConfirm+60+18);

  Rect OkBox(Vec2D(XConfirm+240,YConfirm+60),Vec2D(70,30));
  OkBox.SetRoundness(7.5);
  OkBox.Draw(CouleurFond);
  if(mouse_x>XConfirm+240 && mouse_x<XConfirm+240+70 && mouse_y>YConfirm+60 && mouse_y<YConfirm+60+30  && window_focus_id==W_ASKCONFIRM)
  {
  OkBox.Draw(CouleurFader);
  if(mouse_button==1 && mouse_released==0)
  {
  operations_confirmation();
  reset_index_actions();
  reset_indexs_confirmation();
  mouse_released=1;
  substract_a_window(W_ASKCONFIRM);
  window_focus_id=previous_window_focus_id;
  add_a_window(window_focus_id);
  }
  }
 OkBox.DrawOutline(CouleurLigne);
 petitchiffre.Print("OK",XConfirm+245+18, YConfirm+60+18);

 //by pass des confirmations
 if(expert_mode==1)
 {
  operations_confirmation();
  reset_index_actions();
  reset_indexs_confirmation();
  mouse_released=1;
  substract_a_window(W_ASKCONFIRM);
  window_focus_id=previous_window_focus_id;
 }

 return(0);
}
