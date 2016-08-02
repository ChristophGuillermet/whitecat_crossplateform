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

* \file video_tracking_visu.cpp
* \brief {GUI fonctions for the tracking video}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   GUI fonctions pour la fenêtre de tracking video
*
*   GUI fonctions for the tracking video window
*
**/

int ShowTrackers()
{
char num_tr[4];
 for (int Tr=0;Tr<12;Tr++)
{
if(tracking_spaces_on_off[tracking_dock_selected][Tr]==1)
{
Rect Tracker(Vec2D (videoX+tracking_coordonates[tracking_dock_selected][Tr][0]+15, videoY+tracking_coordonates[tracking_dock_selected][Tr][1]+61 ),
             Vec2D (tracking_coordonates[tracking_dock_selected][Tr][2],tracking_coordonates[tracking_dock_selected][Tr][3]));
sprintf(num_tr,"%d",Tr+1);
circuitlevel.Print(num_tr,videoX+tracking_coordonates[tracking_dock_selected][Tr][0]+20,videoY+tracking_coordonates[tracking_dock_selected][Tr][1]+75);
Tracker.DrawOutline(CouleurFader);

if(tracker_to_edit==Tr && (edit_tracker==1 || move_tracker==1))
{
Tracker.DrawOutline(CouleurBlind);
petitchiffrerouge.Print(num_tr,videoX+tracking_coordonates[tracking_dock_selected][Tr][0]+10,videoY+tracking_coordonates[tracking_dock_selected][Tr][1]+55);
Rect Background_Editor(Vec2D(videoX+15, videoY+70),Vec2D(video_size_x,40));
Background_Editor.SetRoundness(7.5);
Background_Editor.Draw(CouleurFond.WithAlpha(0.4));
petitchiffrerouge.Print(string_tracker_edited_dat,videoX+20,videoY+90);
}
}
}

return(0);
}

int Set_Filtering_Image()
{

int hauteur_cadre_filter_image=0;
if(ocv_calcul_mode==0)
{hauteur_cadre_filter_image=180;}
else{hauteur_cadre_filter_image=130;}

Rect Background_Thres(Vec2D(videoX+30, videoY+70),Vec2D(265,hauteur_cadre_filter_image));
Background_Thres.SetRoundness(5);
Background_Thres.Draw(CouleurFond.WithAlpha(0.3));

Line(videoX+40, videoY+100,videoX+277,videoY+100,2.0).Draw( CouleurSurvol);
Rect Curseur_Thres(Vec2D(videoX+20+threshold_level, videoY+90),Vec2D(40,25));
Curseur_Thres.SetRoundness(7.5);
Curseur_Thres.Draw(CouleurSurvol);

Line(videoX+40, videoY+160,videoX+277,videoY+160,2.0).Draw( CouleurSurvol);
Rect Curseur_Erode(Vec2D(videoX+20+(erode_level*25), videoY+150),Vec2D(40,25));
Curseur_Erode.SetRoundness(7.5);
Curseur_Erode.Draw(CouleurSurvol);


Rect Curseur_div(Vec2D(videoX+20+(div_facteur), videoY+210),Vec2D(40,25));
Curseur_div.SetRoundness(7.5);
if(ocv_calcul_mode==0)
{
Line(videoX+40, videoY+220,videoX+277,videoY+220,2.0).Draw( CouleurSurvol);
Curseur_div.Draw(CouleurSurvol);
}

sprintf(string_threshold_is,"Threshold: %d / 255 :",threshold_level);
petitchiffre.Print(string_threshold_is, videoX+35,videoY+85);
sprintf(string_erode_is,"Erode: %d / 10 :",erode_level);
petitchiffre.Print(string_erode_is, videoX+35,videoY+140);
if(ocv_calcul_mode==0)
{
sprintf(string_div_is,"Div amount: %d / 255 :",div_facteur);
petitchiffre.Print(string_div_is, videoX+35,videoY+200);
}


//on off des functions
Rect OnFlip(Vec2D(videoX+30, videoY+video_size_y+110),Vec2D(60,25));
OnFlip.SetRoundness(7.5);
OnFlip.SetLineWidth(epaisseur_ligne_fader);
OnFlip.Draw(CouleurFond);

Rect OnThreshold(Vec2D(videoX+100, videoY+video_size_y+110),Vec2D(60,25));
OnThreshold.SetRoundness(7.5);
OnThreshold.SetLineWidth(epaisseur_ligne_fader);
OnThreshold.Draw(CouleurFond);

Rect ModeErode(Vec2D(videoX+170, videoY+video_size_y+110),Vec2D(60,25));
ModeErode.SetRoundness(7.5);
ModeErode.SetLineWidth(epaisseur_ligne_fader);
ModeErode.Draw(CouleurFond);

Rect OnOffBlur(Vec2D(videoX+240, videoY+video_size_y+110),Vec2D(60,25));
OnOffBlur.SetRoundness(7.5);
OnOffBlur.SetLineWidth(epaisseur_ligne_fader);
OnOffBlur.Draw(CouleurFond);



if(flip_image==1){OnFlip.Draw(CouleurFader);}
if(threshold_on==1){OnThreshold.Draw(CouleurFader);}
if(erode_mode==1){ModeErode.Draw(CouleurFader);}
if(blur_on==1){OnOffBlur.Draw(CouleurFader);}

petitchiffre.Print("FLIP",videoX+40, videoY+video_size_y+125);
petitchiffre.Print("THRES.",videoX+105, videoY+video_size_y+125);
petitchiffre.Print("EROD",videoX+180, videoY+video_size_y+125);
petitchiffre.Print("BLUR",videoX+250, videoY+video_size_y+125);

OnFlip.DrawOutline(CouleurLigne);
OnThreshold.DrawOutline(CouleurLigne);
ModeErode.DrawOutline(CouleurLigne);
OnOffBlur.DrawOutline(CouleurLigne);

return(0);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int tracking_print_to_screen()
{
//cadre image définit pixel blanc : ne pas supprimer
Rect backim(Vec2D(videoX+15,videoY+61),Vec2D(video_size_x,video_size_y));
backim.DrawOutline(CouleurLigne);
//AFFICHAGE CAM et calculs///////////////////////////////////////////////////////////
if(g_capture!=0 && camera_is_on==1 && manipulating_camera==0  )
{
                   frame = cvQueryFrame(g_capture);

                   if(flip_image==1)
                   {cvConvertImage(frame,frame,CV_CVTIMG_FLIP);}
                   cvCvtColor(frame,onech_temoin,CV_BGR2GRAY);//recup dans un grayscale du actual frame

                   Trackers();

                   cvAddWeighted(onech_temoin,1.0,onech_difference,1.0,0.0,onech_temoin);
                   cvCopy(onech_temoin,affichage);//opencv2.0


Point::StartFastDrawing();

                   for(int pix_x=0; pix_x<video_size_x;pix_x++)
                   {
                   for(int pix_y=0;pix_y<video_size_y;pix_y++)
                   {
                   recup_val_pix_video=(int)cvGetReal1D(affichage,pix_x+(pix_y*video_size_x));
                   Rgba CouleurPixel(recup_val_pix_video,recup_val_pix_video,recup_val_pix_video);
                   Point( Vec2D(videoX+15+pix_x,videoY+61+pix_y)).DrawFast(CouleurPixel);
                   }
                   }
Point::FinishFastDrawing();
}
 return(0);
}


int Interface_video_window(int WindowVideoX,int WindowVideoY)
{
//background window
if(video_size_x>320 && video_size_y>240)//taille de l image video grabée
{
frame_video_x=video_size_x; frame_video_y=video_size_y;
}
else {frame_video_x=345; frame_video_y=240;}

//background window
Rect VideoBackground(Vec2D ( WindowVideoX, WindowVideoY ), Vec2D ( frame_video_x+35,frame_video_y+460));
VideoBackground.SetRoundness(15);
VideoBackground.SetLineWidth(triple_epaisseur_ligne_fader);
VideoBackground.Draw(CouleurFond);
if(window_focus_id==904)
{
VideoBackground.DrawOutline(CouleurFader);
}
else
{
VideoBackground.DrawOutline(CouleurLigne);
}

// SIZE CALIBRATION///////////////////////////////////////////////////////////////

Rect FrameT(Vec2D(WindowVideoX, WindowVideoY), Vec2D (50,15));

char stmp[16];
for (int i=0;i<2;i++)
{
FrameT.MoveTo(Vec2D(WindowVideoX+90+(i*60), WindowVideoY+10));
if(i==camera_size_settings_is){FrameT.DrawOutline(CouleurFader);}
FrameT.DrawOutline(CouleurLigne.WithAlpha(0.5));
sprintf(stmp,"%dx%d", camera_size_array[i][0],camera_size_array[i][1]);
minichiffre.Print(stmp, WindowVideoX+95+(i*60),WindowVideoY+20);
}

sprintf(stmp,"FPS: %d",fps_video_rate);
petitchiffre.Print(stmp,WindowVideoX+300,WindowVideoY+20);
/////////////////////////////////////////////////////////////////////////////

if(manipulating_camera==0)
{
tracking_print_to_screen();
ShowTrackers();
}
//affichage des niveaux issus trackers
char chif_ttr[4];
for(int trZ=0;trZ<6;trZ++)
{
sprintf(chif_ttr,"%d",tracker_level[tracking_dock_selected][trZ]);
petitchiffre.Print(chif_ttr,videoX+30+(trZ*60),videoY+61+video_size_y+15);
sprintf(chif_ttr,"%d",tracker_level[tracking_dock_selected][trZ+6]);
petitchiffre.Print(chif_ttr,videoX+30+(trZ*60),videoY+61+video_size_y+35);
}


//tracking zones
for (int ct=0;ct<6;ct++)
{
//ligne 1
Rect Tracker(Vec2D(WindowVideoX+20+(ct*60), WindowVideoY+frame_video_y+200), Vec2D ( 50,30));
Tracker.SetRoundness(10);
Tracker.SetLineWidth(epaisseur_ligne_fader);
Tracker.DrawOutline(CouleurLigne);
if(tracking_spaces_on_off[tracking_dock_selected][ct]==1)
{
Tracker.Draw(CouleurFader);
 if(tracker_to_edit==ct && (edit_tracker==1 || move_tracker==1))
 {Tracker.Draw(CouleurBlind);}
 Tracker.DrawOutline(CouleurFader);
}

//ligne2
Rect TrackerTwo(Vec2D(WindowVideoX+20+(ct*60), WindowVideoY+frame_video_y+250), Vec2D ( 50,30));
TrackerTwo.SetRoundness(10);
TrackerTwo.SetLineWidth(epaisseur_ligne_fader);
TrackerTwo.DrawOutline(CouleurLigne);
if(tracking_spaces_on_off[tracking_dock_selected][ct+6]==1)
{
TrackerTwo.Draw(CouleurFader);
 if(tracker_to_edit==(ct+6) && (edit_tracker==1 || move_tracker==1) )
 {TrackerTwo.Draw(CouleurBlind);}
 TrackerTwo.DrawOutline(CouleurFader);
}
sprintf(chif_ttr,"%d",ct+1);
petitchiffre.Print(chif_ttr,WindowVideoX+35+(ct*60),WindowVideoY+frame_video_y+220);
sprintf(chif_ttr,"%d",ct+7);
petitchiffre.Print(chif_ttr,WindowVideoX+35+(ct*60),WindowVideoY+frame_video_y+270);

if( Midi_Faders_Affectation_Type!=0)
{
if(mouse_x> WindowVideoX+20+(ct*60) && mouse_x< WindowVideoX+70+(ct*60))
{
        if(mouse_y>WindowVideoY+frame_video_y+200 && mouse_y<WindowVideoY+frame_video_y+230)
        {
        Tracker.DrawOutline(CouleurBlind);
        }
        else if(mouse_y>WindowVideoY+frame_video_y+250 && mouse_y<WindowVideoY+frame_video_y+280)
        {TrackerTwo.DrawOutline(CouleurBlind);}
}
}
}

///////////////OPTIONS///////////////////////////////////////////////////////////////
//mode
Rect OcvMode(Vec2D(WindowVideoX+30, WindowVideoY+frame_video_y+150),Vec2D(60,30));
OcvMode.SetRoundness(7.5);
OcvMode.SetLineWidth(epaisseur_ligne_fader);
OcvMode.Draw(CouleurFond);
switch (ocv_calcul_mode)
{
case 0:
OcvMode.Draw(CouleurFader);
sprintf(string_ocv_mode,"SUPPR.");
break;
case 1:
sprintf(string_ocv_mode," NONE");
break;
default: break;
}
petitchiffre.Print(string_ocv_mode,WindowVideoX+35,WindowVideoY+frame_video_y+170);
OcvMode.DrawOutline(CouleurLigne);

Rect TakeSnap(Vec2D (WindowVideoX+100, WindowVideoY+frame_video_y+150 ), Vec2D (60,30));
TakeSnap.SetRoundness(7.5);
TakeSnap.SetLineWidth(epaisseur_ligne_fader);
TakeSnap.DrawOutline(CouleurLigne);
petitchiffre.Print("SNAP",WindowVideoX+110,WindowVideoY+frame_video_y+170);

//FILTERING IMAGE ACCESS MENU ////////////////////////////////////////////////////////////////
Rect FilteringOn(Vec2D(WindowVideoX+180, WindowVideoY+frame_video_y+150), Vec2D ( 100,30));
FilteringOn.SetRoundness(10);
FilteringOn.SetLineWidth(epaisseur_ligne_fader);
if(ocvfilter_is_on==1)
{
FilteringOn.Draw(CouleurFader);
Set_Filtering_Image();
}
petitchiffre.Print("IMAGE FILTER",WindowVideoX+190,WindowVideoY+frame_video_y+170);
FilteringOn.DrawOutline(CouleurLigne);
/////////
Rect ClearMode(Vec2D(WindowVideoX+300, WindowVideoY+frame_video_y+150),Vec2D(60,30));
 ClearMode.SetRoundness(7.5);
 ClearMode.SetLineWidth(epaisseur_ligne_fader);
 ClearMode.Draw(CouleurFond);

if(tracker_clearmode==1){ClearMode.Draw(CouleurFader);}

ClearMode.DrawOutline(CouleurLigne);
petitchiffre.Print("CLEAR",WindowVideoX+310,WindowVideoY+frame_video_y+170);

//presets zones
petitchiffre.Print("PRESETS:",WindowVideoX+30,WindowVideoY+frame_video_y+360);
for (int ct=0;ct<5;ct++)
{
Rect DockingTracker(Vec2D(WindowVideoX+20+(ct*70), WindowVideoY+frame_video_y+370), Vec2D ( 60,30));
DockingTracker.SetRoundness(10);
DockingTracker.SetLineWidth(epaisseur_ligne_fader);

if(tracking_dock_selected==ct)
{
DockingTracker.Draw(CouleurFader);
}
DockingTracker.DrawOutline(CouleurLigne);
if( Midi_Faders_Affectation_Type!=0)
{
if(mouse_x>WindowVideoX+20+(ct*70) && mouse_x<WindowVideoX+80+(ct*70) && mouse_y>WindowVideoY+frame_video_y+370 && mouse_y<WindowVideoY+frame_video_y+400)
{
DockingTracker.DrawOutline(CouleurBlind);
}
}

sprintf(chif_ttr,"%d",ct+1);
petitchiffre.Print(chif_ttr,WindowVideoX+40+(ct*70),WindowVideoY+frame_video_y+385);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//boutons de mode
//tracking zones
petitchiffre.Print("ROI editing:",WindowVideoX+30,WindowVideoY+frame_video_y+300);
//boutons de mode pour editer / deplacer les 12 trackers

Rect EditTrack(Vec2D (WindowVideoX+30, WindowVideoY+frame_video_y+310 ), Vec2D (60,30));
EditTrack.SetRoundness(7.5);
EditTrack.SetLineWidth(epaisseur_ligne_fader);
Rect MoveTrack(Vec2D (WindowVideoX+110, WindowVideoY+frame_video_y+310 ), Vec2D (60,30));
MoveTrack.SetRoundness(7.5);
MoveTrack.SetLineWidth(epaisseur_ligne_fader);

EditTrack.DrawOutline(CouleurLigne);
MoveTrack.DrawOutline(CouleurLigne);


EditTrack.DrawOutline(CouleurLigne);
if(edit_tracker==1)
{
ocvfilter_is_on=0;
EditTrack.Draw(CouleurBlind);
EditTrack.DrawOutline(CouleurFader);
}

MoveTrack.DrawOutline(CouleurLigne);
if(move_tracker==1)
{
ocvfilter_is_on=0;
MoveTrack.Draw(CouleurFader);
MoveTrack.DrawOutline(CouleurBlind);
}

petitchiffre.Print("SIZE",videoX+45,videoY+frame_video_y+327);
petitchiffre.Print("MOVE",videoX+120,videoY+frame_video_y+327);



//INDEX DECAY TRACKER
Rect DecaySlider( Vec2D(videoX+190+index_decay_tracker,videoY+frame_video_y+310),Vec2D(20,30));
DecaySlider.SetRoundness(5);

Rect BackSliderDecay( Vec2D(videoX+190,videoY+frame_video_y+310),Vec2D(147,30));
BackSliderDecay.SetRoundness(7.5);
BackSliderDecay.DrawOutline(CouleurLigne.WithAlpha(0.5));

Line(Vec2D(videoX+200,videoY+frame_video_y+325),Vec2D(videoX+327,videoY+frame_video_y+325)).Draw(CouleurLigne);
DecaySlider.Draw(CouleurFond);

if(mouse_x>=videoX+180 && mouse_x<=videoX+347 && mouse_y>videoY+frame_video_y+310 && mouse_y<videoY+frame_video_y+340)
{

if( Midi_Faders_Affectation_Type!=0)//config midi
{
BackSliderDecay.DrawOutline(CouleurBlind);
}
}
petitchiffre.Print("DECAY",videoX+200,videoY+frame_video_y+300);
petitchiffre.Print(ol::ToString(index_decay_tracker),videoX+250,videoY+frame_video_y+300);
DecaySlider.DrawOutline(CouleurLigne);

Circle DMidiOut(videoX+365,videoY+frame_video_y+350, 10);//box du fader
DMidiOut.SetLineWidth(epaisseur_ligne_fader);
//liaison visuelle au fader du cercle midi out
Line (Vec2D(videoX+337,videoY+frame_video_y+330),Vec2D( videoX+352,videoY+frame_video_y+330)).Draw(CouleurLigne);
Line (Vec2D( videoX+352,videoY+frame_video_y+330),Vec2D( videoX+367,videoY+frame_video_y+350)).Draw(CouleurLigne);

DMidiOut.Draw(CouleurFond);
if(midi_send_out[498]==1)
{
DMidiOut.Draw(CouleurBlind);
}
DMidiOut.DrawOutline(CouleurLigne);

raccrochage_midi_visuel_horizontal (videoX+200,videoY+frame_video_y+310, 498,127,30);

//AFFECT MODE POUR DOCKS
Rect AffectVideoTo( Vec2D(videoX+(frame_video_y/2)-25,videoY+frame_video_y+417),Vec2D(130,30));
AffectVideoTo.SetRoundness(15);
AffectVideoTo.SetLineWidth(epaisseur_ligne_fader);

 if (index_affect_video_tracking_to_dock==1){AffectVideoTo.Draw(CouleurFader);}
AffectVideoTo.DrawOutline(CouleurLigne);

petitchiffre.Print("AFFECT TO DOCK",videoX+(frame_video_y/2)-10, videoY+frame_video_y+437);


return(0);
}
