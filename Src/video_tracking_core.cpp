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

* \file video_tracking_core.cpp
* \brief {Core fonctions for the tracking video}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Core fonctions pour la fenêtre de tracking video
*
*   Core fonctions for the tracking video window
*
**/

#include "opencv2/opencv.hpp"
/*
#include "opencv2/cv/cv.h"
#include "opencv2/highui/highgui.h"
*/
CvCapture* g_capture = NULL;
IplImage* frame;
IplImage* affichage;
IplImage* onech_temoin_prev;
IplImage* onech_temoin;
IplImage* onech_difference;
IplImage* onech_visu;
IplImage* onech_snap_background;
CvCapture* file_capture;
IplImage* frame_played;



int set_default_image_size()
{
    camera_size_array[0][0]=320;
    camera_size_array[0][1]=240;

    camera_size_array[1][0]=640;
    camera_size_array[1][1]=480;

    return(0);
}

/////////////////CONFIG/////////////////////////////////////////////////////////
int Load_Video_Conf()
{
set_default_image_size();

    FILE *video_file = NULL ;
    char read_buff_vid[ 512 ] ;
    //sab 02/03/2014 unused var int it=0;
	video_file = fopen("user\\config_video.txt", "rt" );
	if( !video_file )
	{
	  sprintf(string_save_load_report[idf],"! config_video.txt\n");
	}
//premiere ligne les args
	fgets( read_buff_vid , sizeof( read_buff_vid ) ,video_file );
	fscanf( video_file , "%d\n" ,  &camera_size_settings_is);
	//2eme ligne args
    fgets( read_buff_vid , sizeof( read_buff_vid ) ,video_file );
	fscanf( video_file , "%dx%d %dx%d\n",&camera_size_array[0][0],&camera_size_array[0][1],&camera_size_array[1][0],&camera_size_array[1][1]);
    //3eme ligne
	fgets( read_buff_vid , sizeof( read_buff_vid ) ,video_file );
	fscanf( video_file , "%d %d %d %d %d %d %d\n" , &flip_image,&threshold_on, &erode_mode,&blur_on, &threshold_level,&erode_level,&div_facteur);
	//4eme ligne
	fgets( read_buff_vid , sizeof( read_buff_vid ) ,video_file );
	fscanf( video_file , "%d %d" ,&tracking_dock_selected, &ocv_calcul_mode);


   if(ocv_calcul_mode==0){sprintf(string_ocv_mode,"DIV");}
   else if(ocv_calcul_mode==1){sprintf(string_ocv_mode,"SUB");}
   else if(ocv_calcul_mode==2){sprintf(string_ocv_mode,"AbsD");}

    fclose( video_file );

return(0);
}


int Save_Video_Conf()
{
FILE *fph;
if((fph=fopen("user//config_video.txt","w")))
{
fprintf(fph,"#arguments: index size image");
fprintf(fph,"\n%d",camera_size_settings_is);
fprintf(fph,"\n#arguments: your camera prerecorded size ");
fprintf(fph,"\n%dx%d %dx%d",camera_size_array[0][0],camera_size_array[0][1],camera_size_array[1][0],camera_size_array[1][1]);
fprintf(fph,"\n#arguments: (0-1)flip threshold erode blur (Level) thresh erode div");
fprintf(fph,"\n%d %d %d %d %d %d %d",flip_image,threshold_on, erode_mode,blur_on, threshold_level,erode_level,div_facteur);
fprintf(fph,"\n#arguments: preset ocv_mode");
fprintf(fph,"\n%d %d",tracking_dock_selected, ocv_calcul_mode);
}
fclose(fph);
return(0);
}
 ///////////////////////////////////////////////////////////////////////////////

int set_camera_size()
{
manipulating_camera=1;
mouse_released=1;
video_size_x=camera_size_array[camera_size_settings_is][0];
video_size_y=camera_size_array[camera_size_settings_is][1];

cvSetCaptureProperty( g_capture, CV_CAP_PROP_FRAME_WIDTH ,video_size_x);
cvSetCaptureProperty( g_capture, CV_CAP_PROP_FRAME_HEIGHT,video_size_y);

rest(1000);
manipulating_camera=0;

return(0);
}


int set_image_caches()
{

frame=cvQueryFrame(g_capture);
frame    = cvCreateImage(cvSize(video_size_x,video_size_y), IPL_DEPTH_8U ,3);// 8 bits 3 couches color
affichage   =  cvCreateImage(cvSize(video_size_x,video_size_y), IPL_DEPTH_8U ,1);// 8 bits 1 couches color AFFICHAGE final
onech_temoin=cvCreateImage(cvSize(video_size_x,video_size_y), IPL_DEPTH_8U ,1);
onech_difference=cvCreateImage(cvSize(video_size_x,video_size_y), IPL_DEPTH_8U ,1);
onech_snap_background=cvCreateImage(cvSize(video_size_x,video_size_y), IPL_DEPTH_8U ,1);


return(0);
}

int InitVideo()
{
g_capture= cvCreateCameraCapture(0); //selection manuelle // 0 toutescvCaptureFromCAM(0);

if(g_capture!=0)
{
fps_video_rate=cvGetCaptureProperty( g_capture, CV_CAP_PROP_FPS);
set_camera_size();
set_image_caches();
camera_is_on=1;
sprintf(string_Last_Order,">>Camera %d x %d FPS: %d ", video_size_x,video_size_y,fps_video_rate) ;
}

else {sprintf(string_Last_Order,">>No Camera recognized !");}
save_load_print_to_screen(string_Last_Order);
return(0);
}

int CloseVideo()
{
 if(g_capture!=0)
 {
 cvReleaseCapture(&g_capture);
 }
 sprintf(string_Last_Order,">>Camera Closed");
 camera_is_on=0;
 return(0);
}

int Snap_Background()
{
    cvCvtColor(frame,onech_snap_background,CV_BGR2GRAY);
    index_snap_background=0;
return(0);
}

///////////////////////////////////////////////////////////////////////////////

int Filter_Image(int xorigin, int yorigin, int largeurRoi, int hauteurRoi)
{
cvSetImageROI(onech_snap_background,cvRect(xorigin,yorigin,largeurRoi,hauteurRoi));
cvSetImageROI(onech_temoin,cvRect(xorigin,yorigin,largeurRoi,hauteurRoi));
cvSetImageROI(onech_difference,cvRect(xorigin,yorigin,largeurRoi,hauteurRoi));
cvSetImageROI(affichage,cvRect(xorigin,yorigin,largeurRoi,hauteurRoi));

//CALCUL
if(ocv_calcul_mode==0)//MODE BACKGROUND SUPPRESSION
{
cvDiv(onech_temoin,onech_snap_background,onech_difference,div_facteur);
if(blur_on==1){cvSmooth(onech_difference,onech_difference,CV_BLUR,3,3,0,0);}
if(threshold_on==1)
{cvThreshold(onech_difference,onech_difference,threshold_level,255,CV_THRESH_BINARY);}

pixels_changed=(cvCountNonZero(onech_difference));
}

else if(ocv_calcul_mode==1)//MODE NORMAL THERSHOLD ONLY
{
if(blur_on==1)
{
cvSmooth(onech_temoin,onech_temoin,CV_BLUR,3,3,0,0);
}
if(threshold_on==1)
{
cvThreshold(onech_temoin,onech_temoin,threshold_level,255,CV_THRESH_BINARY);
}
pixels_changed=(cvCountNonZero(onech_temoin));
}

if(pixels_changed>=old_pixels_changed){nbre_pixels_changed=pixels_changed-old_pixels_changed;}
else if(pixels_changed<old_pixels_changed){nbre_pixels_changed=old_pixels_changed-pixels_changed;}

old_pixels_changed=pixels_changed;

cvResetImageROI(onech_temoin);
cvResetImageROI(onech_difference);
cvResetImageROI(affichage);
cvResetImageROI(onech_snap_background);

//calcul du ratio du tracker
int fract_pix=(int)((float)(largeurRoi*hauteurRoi)/255);;
int indicateur_pixels=(int)(((float)pixels_changed)/fract_pix);
if(indicateur_pixels>255){indicateur_pixels=255;}
else if(indicateur_pixels<0){indicateur_pixels=0;}

return(indicateur_pixels);
}





int do_logical_Move_Tracker(int dock_selected,int tracker_selected)
{
if(mouse_x>videoX+15 && mouse_x<(videoX+15+video_size_x) && mouse_y>videoY+61 && mouse_y<(videoY+video_size_y+61))
{
  tracking_coordonates[dock_selected][tracker_selected][0]= mouse_x-(videoX+15)-(tracking_coordonates[dock_selected][tracker_selected][2]/2 );
  tracking_coordonates[dock_selected][tracker_selected][1]= mouse_y-(videoY+61)-(tracking_coordonates[dock_selected][tracker_selected][3]/2 ) ;
}
sprintf(string_tracker_edited_dat,"X: %d Y: %d Size X: %d Size Y: %d",tracking_coordonates[dock_selected][tracker_selected][0],tracking_coordonates[dock_selected][tracker_selected][1],tracking_coordonates[dock_selected][tracker_selected][2],tracking_coordonates[dock_selected][tracker_selected][3]);
return(0);
}

int do_logical_Edit_Tracker_Size(int dock_selected, int tracker_selected)
{
if(mouse_x>videoX+tracking_coordonates[dock_selected][tracker_selected][0] && mouse_x<(videoX+15+video_size_x) && mouse_y>videoY+61+tracking_coordonates[dock_selected][tracker_selected][1] && mouse_y<(videoY+video_size_y+61))
{
 tracking_coordonates[dock_selected][tracker_selected][2]= mouse_x-((videoX+15)+tracking_coordonates[dock_selected][tracker_selected][0]) ;
 tracking_coordonates[dock_selected][tracker_selected][3]= mouse_y-((videoY+61)+tracking_coordonates[dock_selected][tracker_selected][1]) ;
 if( tracking_coordonates[dock_selected][tracker_selected][2]<1){tracking_coordonates[dock_selected][tracker_selected][2]=1;}
 if( tracking_coordonates[dock_selected][tracker_selected][3]<1){tracking_coordonates[dock_selected][tracker_selected][3]=1;}
}
sprintf(string_tracker_edited_dat,"X: %d Y: %d Size X: %d Size Y: %d",tracking_coordonates[dock_selected][tracker_selected][0],tracking_coordonates[dock_selected][tracker_selected][1],tracking_coordonates[dock_selected][tracker_selected][2],tracking_coordonates[dock_selected][tracker_selected][3]);
return(0);
}


int ventilation_video_trackers()
{
for(int aff_ch_trt=0;aff_ch_trt<512;aff_ch_trt++)
{
for (int Tr=0;Tr<12;Tr++)
{
if(tracking_spaces_on_off[tracking_dock_selected][Tr]==1)
{
if( tracking_contents[tracking_dock_selected][Tr][aff_ch_trt]==1)
{
buffer_tracker[aff_ch_trt]=tracker_level[tracking_dock_selected][Tr];}
}
}
}
 return(0);
}


int Trackers()
{
index_count_trackers=0;
float tracker_vel;

for (int Tr=0;Tr<12;Tr++)
{
if(tracking_spaces_on_off[tracking_dock_selected][Tr]==1)
{
index_count_trackers++;
tracker_target_val[tracking_dock_selected][Tr]=Filter_Image(tracking_coordonates[tracking_dock_selected][Tr][0],tracking_coordonates[tracking_dock_selected][Tr][1], tracking_coordonates[tracking_dock_selected][Tr][2], tracking_coordonates[tracking_dock_selected][Tr][3]+1) ;
tracker_vel = (tracker_target_val[tracking_dock_selected][Tr] - tracker_val[tracking_dock_selected][Tr])*tracker_decay_constant;
if(tracker_decay_constant<1)
{
tracker_val[tracking_dock_selected][Tr] += ((tracker_vel*tracker_dt)*0.1);
}
else {tracker_val[tracking_dock_selected][Tr] += (tracker_vel*tracker_dt);}
tracker_level[tracking_dock_selected][Tr]=(int)(tracker_val[tracking_dock_selected][Tr]);
}
}
return(0);
}


int do_logical_Set_Filtering_Image()
{
if(mouse_x>=videoX+40 && mouse_x<=videoX+295)
{

if(mouse_y>videoY+70 && mouse_y<videoY+120)
{
threshold_level=mouse_x-(videoX+40);
camera_modes_and_settings[ocv_calcul_mode][0]=threshold_level;
}

if(mouse_y>videoY+130 && mouse_y<videoY+180)
{
erode_level=((mouse_x-(videoX+40))/25);
camera_modes_and_settings[ocv_calcul_mode][1]=erode_level;
}

if(ocv_calcul_mode==0)
{
if(mouse_y>videoY+180 && mouse_y<videoY+230)
{
div_facteur=(mouse_x-(videoX+40));
camera_modes_and_settings[ocv_calcul_mode][2]=div_facteur;
}
}

}

//on off des functions

if(mouse_y> videoY+video_size_y+110 && mouse_y< videoY+video_size_y+110+25)
{
if(mouse_x>videoX+30 && mouse_x<videoX+90 )
{
flip_image=toggle(flip_image);
mouse_released=1;
}

if(mouse_x>videoX+100 && mouse_x<videoX+160 )
{
threshold_on=toggle(threshold_on);
camera_modes_and_settings[ocv_calcul_mode][8]=threshold_on;
mouse_released=1;
}

if(mouse_x>videoX+170 && mouse_x<videoX+230 )
{
erode_mode=toggle(erode_mode);
camera_modes_and_settings[ocv_calcul_mode][9]=erode_mode;
mouse_released=1;
}

if(mouse_x>videoX+240 && mouse_x<videoX+300 )
{
blur_on=toggle(blur_on);
camera_modes_and_settings[ocv_calcul_mode][10]=blur_on;
mouse_released=1;
}

}

return(0);
}

int show_who_is_in_ROI_as_channel(int roipreset, int dock_tracker_selected)
{
for (int co=1;co<513;co++)
{
show_who_is_in_FADER_DOCK[co]= tracking_contents[roipreset][dock_tracker_selected][co];
}
return(0);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int do_logical_Interface_video_window(int WindowVideoX,int WindowVideoY)
{

//SIZE CALIBRATION///////////////////////////////////////////////////////////////
for (int i=0;i<2;i++)
{
if(mouse_x>WindowVideoX+90+(i*60) && mouse_x<WindowVideoX+140+(i*60)&& mouse_y> WindowVideoY+10 && mouse_y< WindowVideoY+25)//SIZE
{
camera_size_settings_is=i;
if(mouse_released==0)
{
set_camera_size();
set_image_caches();
mouse_released=1;
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////
//tracking zones

for (int ct=0;ct<6;ct++)
{
//selection on off des tracks spaces
if(mouse_x> WindowVideoX+20+(ct*60) && mouse_x< WindowVideoX+70+(ct*60))
{
//ligne 1
        if(mouse_y>WindowVideoY+frame_video_y+200 && mouse_y<WindowVideoY+frame_video_y+230)
        {
        if( Midi_Faders_Affectation_Type!=0)
        {
        if(ct<4 && Midi_Faders_Affectation_Type==2)
        {attribute_midi_to_control(957+ct,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);}
        else {attribute_midi_solo_affectation(957+ct,1);}
        }
        else
        {

        if(index_inspekt==1){show_who_is_in_ROI_as_channel(tracking_dock_selected,ct);}
        if(edit_tracker==0 && move_tracker==0 && tracker_clearmode==0 && index_do_dock==0 && index_do_modify==0 && index_do_report==0)
        {
        tracking_spaces_on_off[tracking_dock_selected][ct]=toggle(tracking_spaces_on_off[tracking_dock_selected][ct]);
        }
        //affectation channels
        else if(edit_tracker==0 && move_tracker==0 && tracker_clearmode==0 && (  index_do_dock==1 || index_do_modify==1 || index_do_report==1))
        {
        dock_roi_selected=ct;
        index_do_affect_roi=1;
        index_ask_confirm=1;
        }

        else if(tracker_clearmode==0 && (edit_tracker==1 || move_tracker==1))
        {
        tracker_to_edit=ct;
        tracking_spaces_on_off[tracking_dock_selected][tracker_to_edit]=1;
        }
        else if(tracker_clearmode==1)
        {
        dock_roi_selected=ct;
        index_do_clear_my_roi=1;
        index_ask_confirm=1;
        }
        mouse_released=1;
        }
        }

        //ligne 2
        if(mouse_y>WindowVideoY+frame_video_y+250 && mouse_y<WindowVideoY+frame_video_y+280)
        {

        if(Midi_Faders_Affectation_Type!=0)
        {
        attribute_midi_solo_affectation(957+ct+6,1);
        }
        else
        {
        if(index_inspekt==1){show_who_is_in_ROI_as_channel(tracking_dock_selected,ct+6);}
        if(edit_tracker==0 && move_tracker==0 && tracker_clearmode==0 && index_do_dock==0 && index_do_modify==0 && index_do_report==0)
        {
        tracking_spaces_on_off[tracking_dock_selected][ct+6]=toggle(tracking_spaces_on_off[tracking_dock_selected][ct+6]);
        }
        //affectation channels
        else if(edit_tracker==0 && move_tracker==0 && tracker_clearmode==0 && (  index_do_dock==1 || index_do_modify==1 || index_do_report==1))
        {
        dock_roi_selected=ct+6;
        index_do_affect_roi=1;
        index_ask_confirm=1;
        }

        else if(tracker_clearmode==0 && (edit_tracker==1 || move_tracker==1))
        {
        tracker_to_edit=ct+6;
        tracking_spaces_on_off[tracking_dock_selected][tracker_to_edit]=1;
        }
        else if(tracker_clearmode==1)
        {
        dock_roi_selected=ct+6;
        index_do_clear_my_roi=1;
        index_ask_confirm=1;
        }
        mouse_released=1;
        }
        }
        }
}


///////////////OPTIONS///////////////////////////////////////////////////////////////
//mode
if(mouse_x>WindowVideoX+30 && mouse_x<WindowVideoX+90 && mouse_y>WindowVideoY+frame_video_y+150 && mouse_y<WindowVideoY+frame_video_y+150+30)
{
ocv_calcul_mode++;
if(ocv_calcul_mode>1){ocv_calcul_mode=0;}
refresh_ocv_settings();
mouse_released=1;
}

//snap
if(mouse_x>WindowVideoX+100 && mouse_x<WindowVideoX+100+60 && mouse_y>WindowVideoY+frame_video_y+150 && mouse_y<WindowVideoY+frame_video_y+150+30)
{
index_snap_background=1;
Snap_Background();
mouse_released=1;
}

//FILTERING IMAGE ACCESS MENU ////////////////////////////////////////////////////////////////
if(ocvfilter_is_on==1)
{
do_logical_Set_Filtering_Image();
}
//on off ocvfilters menu image
if(mouse_x>WindowVideoX+180 && mouse_x<WindowVideoX+280 && mouse_y> WindowVideoY+frame_video_y+140 && mouse_y< WindowVideoY+frame_video_y+180)
{
ocvfilter_is_on=toggle(ocvfilter_is_on);
mouse_released=1;
}

////clear mode
if(mouse_x>WindowVideoX+300 && mouse_x<WindowVideoX+360 && mouse_y>WindowVideoY+frame_video_y+150 && mouse_y<WindowVideoY+frame_video_y+150+30)
{
if(tracker_clearmode==1){tracker_clearmode=0;}
else if(tracker_clearmode==0){tracker_clearmode=1;move_tracker=0;edit_tracker=0;}
mouse_released=1;
}

//presets zones
for (int ct=0;ct<5;ct++)
{
if(mouse_x>WindowVideoX+20+(ct*70) && mouse_x<WindowVideoX+80+(ct*70) && mouse_y>WindowVideoY+frame_video_y+370 && mouse_y<WindowVideoY+frame_video_y+400)
{

if( Midi_Faders_Affectation_Type!=0)
{
attribute_midi_solo_affectation(969+ct,1);
}
else
{
switch (tracker_clearmode)
{
case 0:
tracking_dock_selected=ct;
break;
case 1:
tracking_dock_to_clean=ct;
index_do_clear_my_video_preset=1;
index_ask_confirm=1;
break;
default: break;
}
mouse_released=1;
}
}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//boutons de mode
//tracking zones

if(mouse_y>WindowVideoY+frame_video_y+300 && mouse_y<WindowVideoY+frame_video_y+330)
{

//edit
if(mouse_x>WindowVideoX+30 && mouse_x<WindowVideoX+90)
{
switch(edit_tracker)
{
case 0:
move_tracker=0;edit_tracker=1;tracker_clearmode=0;
break;
case 1:
edit_tracker=0;
break;
default: break;
}
mouse_released=1;
}

//move
if(mouse_x>WindowVideoX+110 && mouse_x<WindowVideoX+170)
{
switch(move_tracker)
{
case 0:
edit_tracker=0;move_tracker=1;tracker_clearmode=0;
break;
case 1:
move_tracker=0;
break;
default: break;
}
mouse_released=1;
}
}
///////////////////////////////////////////////////////

if(edit_tracker==1)
{
ocvfilter_is_on=0;
do_logical_Edit_Tracker_Size(tracking_dock_selected,tracker_to_edit);
}


if(move_tracker==1)
{
ocvfilter_is_on=0;
do_logical_Move_Tracker(tracking_dock_selected,tracker_to_edit);
}



//INDEX DECAY TRACKER

if(mouse_x>=videoX+200-20 && mouse_x<=videoX+200+127+20 && mouse_y>videoY+frame_video_y+310 && mouse_y<videoY+frame_video_y+310+30)
{
//midi report
switch(miditable[0][498])
{
  case 0: sprintf(thetypinfo,"Note");break;
  case 1: sprintf(thetypinfo,"Key On");break;
  case 2: sprintf(thetypinfo,"Key Off");break;
  case 4: sprintf(thetypinfo,"Ctrl Change");break;
  default: break;
}
sprintf(string_last_midi_id,"DECAY is Ch: %d Pitch: %d Typ: %s" , miditable[1][498],miditable[2][498],thetypinfo);

if( Midi_Faders_Affectation_Type!=0)//config midi
{
type_of_midi_button=4;
attribute_midi_solo_affectation(498,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
index_decay_tracker=mouse_x-(videoX+200);
refresh_decay();
midi_levels[498]=index_decay_tracker;
if(midi_send_out[498]==1){index_send_midi_out[498]=1;}
}
}

//midi out
if(mouse_x> (videoX+365-10) && mouse_x<(videoX+365+10)
&& mouse_y>(videoY+frame_video_y+350-10) && mouse_y<(videoY+frame_video_y+350+10))
{

midi_send_out[498]=toggle(midi_send_out[498]);
mouse_released=1;
}
raccrochage_midi_logical_horizontal (videoX+200,videoY+frame_video_y+310, 498,127,30);


//AFFECT MODE POUR DOCKS
if(mouse_x>videoX+(frame_video_y/2)-25 && mouse_x<videoX+(frame_video_y/2)-25+130 && mouse_y>videoY+frame_video_y+417 && mouse_y< videoY+frame_video_y+447)
{
 if(index_affect_video_tracking_to_dock==0)
{
reset_index_actions();
reset_indexs_confirmation();
index_affect_video_tracking_to_dock=1;
}
else
{
reset_index_actions();
}
index_do_dock=index_affect_video_tracking_to_dock;
mouse_released=1;
}


return(0);
}
