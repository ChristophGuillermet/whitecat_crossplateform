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

* \file dmx_functions_13.cpp
* \brief {global fonctions for all interfaces and artnet}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {6/04/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonction global d'écriture du dmx vers toutes les interfaces et l'arnet, gère aussi l'écriture direct du signal dmx par le processeur du pc, envoyer vers l'enttec open via les drivers D2XX
*
*   Global fonctions to write the dmx to the diferente interface and artnet, write too directly the dmx signal from the PC CPU to be send to the enttec open dmx via the D2XX drivers
*
 **/

#include <odmxusb.cpp>
#include <odmxusb.h>
Open_USB_DMX *pUsbDmx = NULL;
unsigned char DmxBlockEnttecOpen[513];
unsigned char dmxIN[514];//etait 513 aout 2016
#include <dmx_enttec_pro.cpp>
#include <dmx_sunlite.cpp>

//REFONTE AVRIL 2016 DU SYSTEME DE NOMBRES D'INTERFACES EN PERMETTANT UN ENVOI EN SIMULTANNE SUR PLUSIEURS INYTERFACES

int Init_A_specific_dmx_interface(int i)
{
switch(i)
{
            case 1:
            initialisation_client_artnet();
            ConstructArtPoll();
            ConstructArtPollReply();
            //ArtPolling message ArtPoll
            nbrbytessended=sendto(sockartnet, ArtPollBuffer,sizeof( ArtPollBuffer),0,(SOCKADDR*)&sinS,sinsize);
             //ArtNet
            ArtDmx();
            nbrbytessended=sendto(sockartnet, ArtDmxBuffer,sizeof( ArtDmxBuffer),0,(SOCKADDR*)&sinS,sinsize);
            index_init_dmx_ok[i]=1;
            break;

            case 2:
            pUsbDmx = new Open_USB_DMX();
            if (pUsbDmx == NULL)//creation class
                {  sprintf(string_display_dmx_params,"Impossible to load DLL");	return(0);}
                sprintf(string_display_dmx_params,"Pointer Created");
                rest(100);
            if (pUsbDmx != NULL)
                   {
                          int iRet;
                          iRet = pUsbDmx->open_dmx_devices();
                          sprintf(string_display_dmx_params,"Enttec Open Dmx return :%d",iRet);
                          if (iRet==0)
                          { sprintf(string_display_dmx_params,"Impossible to open interface, is it PLUGGED ?");
                            return(0);
                          }
                          index_init_dmx_ok[i]=1;
                           for(int ko=0;ko<513;ko++)
                           {
                           DmxBlockEnttecOpen[ko]=DmxBlock[ko+1];
                           }
                          pUsbDmx->send_dmx_packet(DmxBlockEnttecOpen);

                    }
                 else {
                      sprintf(string_display_dmx_params,"Interface Opened !");
                      index_init_dmx_ok[i]=1;
                  }
            break;

            case 3:
            //VCOM
            Detect_EnttecProOut();
            Open_EnttecProOut();
            break;

            case 4:
            //sunlite
            open_sunlite();
            index_init_dmx_ok[i]=1;
            break;

            default:
            break;
        }

return(0);
}


int Init_dmx_interface()
{
for(int i=0;i<NB_INTERFACES;i++)
{
    if(do_DMX_out[i]==1)
    {
     Init_A_specific_dmx_interface(i);
    }
}
return(0);
}

////////////////////////////////////////////////////////////////////////////////

int Close_A_specific_dmx_interface(int i)
{
    switch(i)
        {
        //art-net
         case 1:
              fermeture_client_artnet();
              index_init_dmx_ok[i]=0;
         break;
         //enttec Open
         case 2:
         if (pUsbDmx != NULL)
                {
                pUsbDmx->close_dmx_devices();
                }
                sprintf(string_display_dmx_params,"Interface Closed");
                rest(100);
         if (pUsbDmx != NULL)//destruction classe
            {	delete pUsbDmx;
                pUsbDmx = NULL;
                sprintf(string_display_dmx_params,"Pointer Deleted");
            }
            index_init_dmx_ok[i]=0;
         break;
         //enttec PRO
         case 3:
         //VCOM
         Close_EnttecProOut();
         index_init_dmx_ok[i]=0;
         //FTDI_ClosePort();
         break;
         //sunlite
         case 4:
         close_sunlite();
         index_init_dmx_ok[i]=0;
         break;
         default:
         break;
         }

    return(0);
}



int Close_dmx_interface()
{
for(int i=0;i<NB_INTERFACES;i++)
{
    if(do_DMX_out[i]==1)
    {
     Close_A_specific_dmx_interface(i);
    }
}

if (index_init_EnttecPROIN_ok==1){Close_ProIn();}
return(0);
}
////////////////////////////////////////////////////////////////////////////////
int check_if_dmx_change()
{
 for(int iop=0;iop<512;iop++)
 {
 if (artnet_backup[iop]!=DmxBlock[iop])
 {
 do_send_on_change=1;
 break;
 }
 }
 return(0);
}


int SendData_to_interface()
{
for(int i=0;i<NB_INTERFACES;i++)
{
    if(do_DMX_out[i]==1)
    {
    if(index_init_dmx_ok[i]==1 )
        {
        switch(i)
        {
          case 1:
          ArtDmx();
          check_if_dmx_change();
          if(do_send_on_change==1)
          {
          nbrbytessended=sendto(sockartnet, ArtDmxBuffer,sizeof( ArtDmxBuffer),0,(SOCKADDR*)&sinS,sinsize);
          do_send_on_change=0;
          for(int bup=0;bup<512;bup++)
          {artnet_backup[bup]=DmxBlock[bup];}
          }
          break;
          //enttec open
          case 2:
         for(int ko=0;ko<513;ko++)
         {
         DmxBlockEnttecOpen[ko]=DmxBlock[ko+1];
         }
            if (pUsbDmx!= NULL)
                {
                pUsbDmx->send_dmx_packet(DmxBlockEnttecOpen);
                }
          break;
         //enttec pro
         case 3:
         //VCOM
          Enttec_Pro_SendData(6, DmxBlock, sizeof(DmxBlock),NULL);
         break;
         //sunlite
         case 4:
         sunlite_send_data();
         break;
         default:
         break;
         }
        }
    }
}

 return(0);
}

////////////////////////////////////////////////////////////////////////////////
int Attribute_ArtNet(int aff, int ddok)
{
 if(DockIsSelected[aff][ddok]==1  && DockTypeIs[aff][ddok]==2)
 {
 for (int pp=0;pp<512;pp++)
 {
 FaderDockContains[aff][ddok][pp]=ArtNet_16xUniverse_Receiving[pp][DockNetIs[aff][ddok]];
 }

 }
return(0);
}




///////////////////////////////////////////////////////////////////////////////////


int refresh_modified_levels_in_crossfade()
{
for(int i=0;i<513;i++)
{
if(bufferSaisie[i]+channel_level_mofification_while_crossfade[i]>255){bufferSaisie[i]=255;}
else if(bufferSaisie[i]+channel_level_mofification_while_crossfade[i]<0){bufferSaisie[i]=0;}
else {bufferSaisie[i]+=channel_level_mofification_while_crossfade[i];}
}
reset_modified_levels_in_crossfade();
return(0);
}


int do_crossfade()
{

if(index_go==0 && index_pause==0 && index_go_back==0)
{
prepare_crossfade();
floatX1=niveauX1;
floatX2=niveauX2;
crossfade_done_time=0;
}

if(index_go==1 && index_pause==0)
{
crossfade_done_time++;
if(actual_time>(crossfade_start_time+crossfade_time_delay_out))
{
floatX1-=fraction_X1_out;
if(floatX1<0){floatX1=0.0;}
niveauX1=(int)floatX1;
crossfade_time_delay_out=0;
}
if(actual_time>(crossfade_start_time+crossfade_time_delay_in))
{
floatX2+=fraction_X2_in;
if(floatX2>255){floatX2=255;}
niveauX2=(int)floatX2;
crossfade_time_delay_in=0;
}
if(niveauX1==0 && niveauX2==255)
{

next_mem_crossfade_finished(position_preset);
refresh_modified_levels_in_crossfade();//modification fleches pdt crossfade
index_go=0;
if(index_auto_mute_cuelist_speed==1 && crossfade_speed!=64)
{is_raccrochage_midi_remote[493]=1; }
if(auto_reset_crossfade_speed_on_link==1 && (Links_Memoires[position_onstage]==0 || index_link_is_on==0 ))
{crossfade_speed=64;}

crossfade_done_time=0;
//sab 02/03/2014 sprintf(string_time_left_is,"");
strcpy(string_time_left_is,"");

if(index_link_speed_crossfade_to_gpl1==1)
{  grid_crossfade_speed[0]=crossfade_speed;
   midi_levels[1508]=crossfade_speed;
}
if(midi_send_out[491]==1){index_send_midi_out[491]=1;}//x1
if(midi_send_out[492]==1){index_send_midi_out[492]=1;}//x2
//auto go
if(Links_Memoires[position_onstage]==1 && index_link_is_on==1)
{
crossfade_start_time=actual_time;
prepare_crossfade();
floatX1=niveauX1;
floatX2=niveauX2;
index_go=1;
do_send_bang();
//integration du gridplayer 1
if(show_gridplayer_in_seq==1)
{
grid_in_preset[0][0]=index_grider_selected[0];
grid_in_preset[0][1]=set_from_seq_gridplayer1_next_step[position_preset]-1;
if( set_from_seq_gridplayer1_next_step[position_preset]!=-1
&& set_from_seq_gridplayer1_next_step[position_preset]!=index_grider_step_is[0])
{
gridder_prepare_cross(0,index_grider_selected[0],set_from_seq_gridplayer1_next_step[position_preset]-1);
grider_is_playing[0]=1;grid_crossfade_start_time[0]=actual_time;
}
}
}
}
}
if(index_go==1 || index_go_back==1)
{
if(midi_send_out[491]==1){index_send_midi_out[491]=1;}//x1
if(midi_send_out[492]==1){index_send_midi_out[492]=1;}//x2

}


return(0);
}



int do_goback()
{

if(index_go_back==1 && index_pause==0)
{
crossfade_done_time=0;
crossfade_time_delay_in=0;
crossfade_time_delay_out=0;

floatX1+=fraction_X1_out;
if(floatX1>255){floatX1=255.0;}
niveauX1=(int)floatX1;

floatX2-=fraction_X2_in;
if(floatX2<0){floatX2=0.0;}
niveauX2=(int)floatX2;

//integration du gridplayer 1
if(show_gridplayer_in_seq==1 && set_from_seq_gridplayer1_next_step[position_onstage]!=-1)
{
grider_is_playing[0]=0;
grid_floatX1[0]+=grid_fraction_X1_out[0];
if(grid_floatX1[0]>255.0){grid_floatX1[0]=255.0;}
grid_niveauX1[0]=(int)grid_floatX1[0];
grid_floatX2[0]-=grid_fraction_X2_in[0];
if(grid_floatX2[0]<0.0){grid_floatX2[0]=0.0;}
grid_niveauX2[0]=(int)grid_floatX2[0];
}

if(niveauX1==255 && niveauX2==0)
{
//sab 27/01/2015 deb
//Affichage du temps du crossfade en cours : l'affichage du temps restant, commence souvent à moins "quelque chose".
        //crossfade_done_time=0;
        crossfade_done_time--;
        //sab 27/01/2015 fin
strcpy(string_time_left_is,"");

index_go_back=0;
if(index_auto_mute_cuelist_speed==1 && crossfade_speed!=64)
{is_raccrochage_midi_remote[493]=1; }
crossfade_speed=64;
refresh_integrated_gridplayer1();
if(index_link_speed_crossfade_to_gpl1==1)
{  grid_crossfade_speed[0]=crossfade_speed;
   midi_levels[1508]=crossfade_speed;
}
}

}
return(0);
}


/////////////////////////////////////////////////////////////////////////////////
int prepare_lfos(int cmptfader, int dksel)
{
if(lfo_speed[cmptfader]<64)
{
fraction_lfo_in[cmptfader]= 255.0/ (time_per_dock[cmptfader][dksel][1]*(((float)BPS_RATE)*(64.0/lfo_speed[cmptfader])));
fraction_lfo_out[cmptfader]=  255.0/ (time_per_dock[cmptfader][dksel][3]*(((float)BPS_RATE)*(64.0/lfo_speed[cmptfader])));
time_delay_in[cmptfader]=(int)(time_per_dock[cmptfader][dksel][0]*(((float)BPS_RATE)*(64.0/lfo_speed[cmptfader])));
time_delay_out[cmptfader]=(int)(time_per_dock[cmptfader][dksel][0]*(((float)BPS_RATE)*(64.0/lfo_speed[cmptfader])));
}
else if(lfo_speed[cmptfader]==64)
{
fraction_lfo_in[cmptfader]= 255.0/ (time_per_dock[cmptfader][dksel][1]*BPS_RATE);
fraction_lfo_out[cmptfader]= 255.0/ (time_per_dock[cmptfader][dksel][3]*BPS_RATE);
time_delay_in[cmptfader]=(int) (time_per_dock[cmptfader][dksel][0]*BPS_RATE);
time_delay_out[cmptfader]=(int)(time_per_dock[cmptfader][dksel][2]*BPS_RATE);
}
else if(lfo_speed[cmptfader]>64)
{
fraction_lfo_in[cmptfader]= 255.0/ (time_per_dock[cmptfader][dksel][1]*(((float)BPS_RATE*3)/(lfo_speed[cmptfader]-62))); //-62 evite un passage de temps pas bon, cf curseur
fraction_lfo_out[cmptfader]=  255.0/ (time_per_dock[cmptfader][dksel][3]*(((float)BPS_RATE*3)/(lfo_speed[cmptfader]-62)));
time_delay_in[cmptfader]= (int) (time_per_dock[cmptfader][dksel][0]*(((float)BPS_RATE*3)/(lfo_speed[cmptfader]-62))); //-62 evite un passage de temps pas bon, cf curseur
time_delay_out[cmptfader]= (int) (time_per_dock[cmptfader][dksel][2]*(((float)BPS_RATE*3)/(lfo_speed[cmptfader]-62)));
}

return(0);
}


int do_lfos()
{
 for(int cmptfader=0; cmptfader<core_user_define_nb_faders; cmptfader++)
 {

 int dockis=detect_dock_used(cmptfader);
 prepare_lfos(cmptfader, dockis);
 index_lfoing[cmptfader]=0;//pour lock faisait bugguer le next step

 ////////////////////////////ONCE/////////////////////////////////////////////////////////////////
 if (is_dock_for_lfo_selected[cmptfader][ dockis]==0 && lfo_cycle_is_on[cmptfader]==0)//ONCE CASE
 {
 //up only once
 if(lfo_mode_is[cmptfader]==1 && actual_time>(start_time_for_delays[cmptfader]+time_delay_in[cmptfader]))
 {
 index_lfoing[cmptfader]=1;
 faders_in_float[cmptfader]+=fraction_lfo_in[cmptfader];
 if(faders_in_float[cmptfader]>255){faders_in_float[cmptfader]=255;}
 if(FaderIsFlash[cmptfader]==0)//tous calculs ok si pas de flash
 {
 //Fader[cmptfader]=int(faders_in_float[cmptfader]);
 fader_set_level(cmptfader,int(faders_in_float[cmptfader]));
 }

 lfo_running_is_upward[cmptfader]=1;
 if(faders_in_float[cmptfader]>=255)
 {
 lfo_mode_is[cmptfader]=0;faders_in_float[cmptfader]=255.0;
 }
 //ONSTOP UP LIMITE
 if( ActionnateStopOn[cmptfader]==1 && StopPosOn[cmptfader]==1 && (Fader[cmptfader]==LevelStopPos[cmptfader]
 || Fader[cmptfader]>LevelStopPos[cmptfader]) && FaderIsFlash[cmptfader]==0)
 {
  //Fader[cmptfader]=LevelStopPos[cmptfader];
  fader_set_level(cmptfader,LevelStopPos[cmptfader]);
  lfo_mode_is[cmptfader]=0;ActionnateStopOn[cmptfader]=0;
  }
 //report midi
 midi_levels[cmptfader]=(Fader[cmptfader]/2);
 if(midi_send_out[cmptfader]==1  )
 {index_send_midi_out[cmptfader]=1;}

 }

 //down only once
 else if(lfo_mode_is[cmptfader]==2 && actual_time>(start_time_for_delays[cmptfader]+time_delay_out[cmptfader]))
 {
 index_lfoing[cmptfader]=1;
 faders_in_float[cmptfader]-=fraction_lfo_out[cmptfader];
 if(faders_in_float[cmptfader]<0){faders_in_float[cmptfader]=0;}
 if(FaderIsFlash[cmptfader]==0)//tous calculs ok si pas de flash
 {
 //Fader[cmptfader]=int(faders_in_float[cmptfader]);
 fader_set_level(cmptfader,int(faders_in_float[cmptfader]));
 }

 lfo_running_is_upward[cmptfader]=0;
 if(faders_in_float[cmptfader]==0.0)
 {
 lfo_mode_is[cmptfader]=0;faders_in_float[cmptfader]=0.0;
 }
 //ONSTOP DOWN LIMITE
 if( ActionnateStopOn[cmptfader]==1 && StopPosOn[cmptfader]==1 && (Fader[cmptfader]==LevelStopPos[cmptfader]
 || Fader[cmptfader]<LevelStopPos[cmptfader]) && FaderIsFlash[cmptfader]==0)
 {
 //Fader[cmptfader]=LevelStopPos[cmptfader];
 fader_set_level(cmptfader,LevelStopPos[cmptfader]);
 lfo_mode_is[cmptfader]=0;ActionnateStopOn[cmptfader]=0;
 }
 //report midi
  midi_levels[cmptfader]=(Fader[cmptfader]/2);
 if(midi_send_out[cmptfader]==1  )
 {index_send_midi_out[cmptfader]=1;}


 }
 }
 ////////////////////////////////LOOP ON ONCE//////////////////////////////////////////////////////////////////
 if (is_dock_for_lfo_selected[cmptfader][ dockis]==1 && lfo_cycle_is_on[cmptfader]==0)//LOOP LFO ON ONE DOCK ONLY ( NO DOCK CYCLING)
 {
 //up On Fade IN only
 if(lfo_mode_is[cmptfader]==1 && actual_time>(start_time_for_delays[cmptfader]+time_delay_in[cmptfader]))
 {
 index_lfoing[cmptfader]=1;
 faders_in_float[cmptfader]+=fraction_lfo_in[cmptfader];
 if(faders_in_float[cmptfader]>255){faders_in_float[cmptfader]=255;}
 if(FaderIsFlash[cmptfader]==0)//tous calculs ok si pas de flash
 {
 //Fader[cmptfader]=int(faders_in_float[cmptfader]);
 fader_set_level(cmptfader,int(faders_in_float[cmptfader]));
 }

//ONSTOP est butee haute de la boucle
 if( ActionnateStopOn[cmptfader]==1 && StopPosOn[cmptfader]==1 && (Fader[cmptfader]==LevelStopPos[cmptfader] || Fader[cmptfader]>LevelStopPos[cmptfader])
 && FaderIsFlash[cmptfader]==0)
 {//Fader[cmptfader]=LevelStopPos[cmptfader];
 fader_set_level(cmptfader,LevelStopPos[cmptfader]);
 }
 //report midi
 midi_levels[cmptfader]=(Fader[cmptfader]/2);
 if(midi_send_out[cmptfader]==1  )
 {index_send_midi_out[cmptfader]=1;}

 lfo_running_is_upward[cmptfader]=1;
 if(faders_in_float[cmptfader]>=255)
 {
 start_time_for_delays[cmptfader]=actual_time;
 faders_in_float[cmptfader]=0.0;
 //Fader[cmptfader]=0;
 fader_set_level(cmptfader,0);
 }


 if(faders_in_float[cmptfader]==0.0)//renvoi next dock quand à 0 pos
 {
 if(lfo_do_next_step[cmptfader][1]==1)//down dock
 {
 for (int tt=0;tt<core_user_define_nb_docks;tt++)
  {
 if ( DockIsSelected[cmptfader][tt]==1)
  {
  DockIsSelected[cmptfader][tt]=0;
  if(tt<core_user_define_nb_docks-1){ DockIsSelected[cmptfader][tt+1]=1;break;}
  else if(tt==core_user_define_nb_docks-1){DockIsSelected[cmptfader][0]=1;break;}
  }
 }
 }
 else if(lfo_do_next_step[cmptfader][0]==1)//up dock
 {
 for (int tt=0;tt<core_user_define_nb_docks;tt++)
  {
 if ( DockIsSelected[cmptfader][tt]==1)
  {
  DockIsSelected[cmptfader][tt]=0;
  if(tt>0){ DockIsSelected[cmptfader][tt-1]=1;break;}
  else if(tt==0){DockIsSelected[cmptfader][core_user_define_nb_docks-1]=1;break;}
  }
 }
}
}
}
 //down On Fade OUT only
 else if(lfo_mode_is[cmptfader]==2 && actual_time>(start_time_for_delays[cmptfader]+time_delay_out[cmptfader]))
 {
 index_lfoing[cmptfader]=1;
 faders_in_float[cmptfader]-=fraction_lfo_out[cmptfader];
 if(faders_in_float[cmptfader]<0){faders_in_float[cmptfader]=0;}
 if(FaderIsFlash[cmptfader]==0)//tous calculs ok si pas de flash
 {
 //Fader[cmptfader]=int(faders_in_float[cmptfader]);
 fader_set_level(cmptfader,int(faders_in_float[cmptfader]));
 }

 //ONSTOP est plancher de la boucle
 if( ActionnateStopOn[cmptfader]==1 && StopPosOn[cmptfader]==1 && (Fader[cmptfader]==LevelStopPos[cmptfader]
 || Fader[cmptfader]<LevelStopPos[cmptfader]) && FaderIsFlash[cmptfader]==0)
 {
 //    Fader[cmptfader]=255;
   fader_set_level(cmptfader,255);
 }
  //report midi
 midi_levels[cmptfader]=(Fader[cmptfader]/2);
 if(midi_send_out[cmptfader]==1  )
 {index_send_midi_out[cmptfader]=1;}

 lfo_running_is_upward[cmptfader]=0;
 if(faders_in_float[cmptfader]==0.0)
 {
 //Fader[cmptfader]=255;
 fader_set_level(cmptfader,255);
 faders_in_float[cmptfader]=255.0;
 start_time_for_delays[cmptfader]=actual_time;
 if(lfo_do_next_step[cmptfader][1]==1)
 {
 for (int tt=0;tt<core_user_define_nb_docks;tt++)
  {
 if ( DockIsSelected[cmptfader][tt]==1)
  {
  DockIsSelected[cmptfader][tt]=0;
  if(tt<core_user_define_nb_docks-1){ DockIsSelected[cmptfader][tt+1]=1;break;}
  else if(tt==core_user_define_nb_docks-1){DockIsSelected[cmptfader][0]=1;break;}
  }
 }
 }
  if(lfo_do_next_step[cmptfader][0]==1)
 {
 for (int tt=0;tt<core_user_define_nb_docks;tt++)
  {
 if ( DockIsSelected[cmptfader][tt]==1)
  {
  DockIsSelected[cmptfader][tt]=0;
  if(tt>0){ DockIsSelected[cmptfader][tt-1]=1;break;}
  else if(tt==0){  DockIsSelected[cmptfader][core_user_define_nb_docks-1]=1;break;}
  }
 }
 }
 }
 }
 }
 /////////////////////CYCLING SMOOTH IN OUT/ SAW///////////////////////////
 if (lfo_cycle_is_on[cmptfader]==1 )//LOOP LFO ( CYCLING + TIMES)
 {

 index_lfoing[cmptfader]=1;
 //up way
 if(lfo_running_is_upward[cmptfader]==1 && actual_time>(start_time_for_delays[cmptfader]+time_delay_in[cmptfader]))
 {
 faders_in_float[cmptfader]+=fraction_lfo_in[cmptfader];
 if(faders_in_float[cmptfader]>255){faders_in_float[cmptfader]=255;}

 if(FaderIsFlash[cmptfader]==0)//tous calculs ok si pas de flash
 {
 //Fader[cmptfader]=int(faders_in_float[cmptfader]);
 fader_set_level(cmptfader,int(faders_in_float[cmptfader]));
 }

 //ONSTOP est plancher de la boucle
 if( ActionnateStopOn[cmptfader]==1 && StopPosOn[cmptfader]==1 && (Fader[cmptfader]==LevelStopPos[cmptfader] || Fader[cmptfader]<LevelStopPos[cmptfader])
 && FaderIsFlash[cmptfader]==0)
 { //Fader[cmptfader]=LevelStopPos[cmptfader];
 fader_set_level(cmptfader,LevelStopPos[cmptfader]);
 }
  //report midi
 midi_levels[cmptfader]=(Fader[cmptfader]/2);
 if(midi_send_out[cmptfader]==1  )
 {index_send_midi_out[cmptfader]=1;}
 lfo_running_is_upward[cmptfader]=1;
 if(faders_in_float[cmptfader]==255)
 {
 faders_in_float[cmptfader]=255.0;
 //Fader[cmptfader]=255;
 fader_set_level(cmptfader,255);
 start_time_for_delays[cmptfader]=actual_time;
 lfo_running_is_upward[cmptfader]=0;
 }
 }
 //down
 else if(lfo_running_is_upward[cmptfader]==0 && actual_time>(start_time_for_delays[cmptfader]+time_delay_out[cmptfader]))
 {
 faders_in_float[cmptfader]-=fraction_lfo_out[cmptfader];
 if(faders_in_float[cmptfader]<0){faders_in_float[cmptfader]=0;}
 if(FaderIsFlash[cmptfader]==0)//tous calculs ok si pas de flash
 {
 //Fader[cmptfader]=int(faders_in_float[cmptfader]);
 fader_set_level(cmptfader,int(faders_in_float[cmptfader]));
 }


 //ONSTOP est plancher de la boucle
 if( ActionnateStopOn[cmptfader]==1 && StopPosOn[cmptfader]==1 && (Fader[cmptfader]==LevelStopPos[cmptfader] || Fader[cmptfader]<LevelStopPos[cmptfader])
 && FaderIsFlash[cmptfader]==0)
 {
 //Fader[cmptfader]=LevelStopPos[cmptfader];
 fader_set_level(cmptfader,LevelStopPos[cmptfader]);
 }
 //report midi
 midi_levels[cmptfader]=(Fader[cmptfader]/2);
 if(midi_send_out[cmptfader]==1  )
 {index_send_midi_out[cmptfader]=1;}

 if(faders_in_float[cmptfader]==0.0)
 {
 faders_in_float[cmptfader]=0.0;
 if( ActionnateStopOn[cmptfader]==0 && FaderIsFlash[cmptfader]==0)
    {
    //Fader[cmptfader]=0;
    fader_set_level(cmptfader,0);
    }

 start_time_for_delays[cmptfader]=actual_time;
 prepare_lfos(cmptfader, dockis);
 lfo_running_is_upward[cmptfader]=1;

if (is_dock_for_lfo_selected[cmptfader][ dockis]==1 )
{
 if(lfo_do_next_step[cmptfader][1]==1)
 {
  start_time_for_delays[cmptfader]=actual_time;
 for (int tt=0;tt<core_user_define_nb_docks;tt++)
  {
 if ( DockIsSelected[cmptfader][tt]==1)
  {
  DockIsSelected[cmptfader][tt]=0;
  if(tt<core_user_define_nb_docks-1){ DockIsSelected[cmptfader][tt+1]=1;break;}
  else if(tt==core_user_define_nb_docks-1)
  {
  DockIsSelected[cmptfader][0]=1;   break;}
  }
 }
 }
 else if(lfo_do_next_step[cmptfader][0]==1)
 {
  start_time_for_delays[cmptfader]=actual_time;
 for (int tt=0;tt<core_user_define_nb_docks;tt++)
  {
 if ( DockIsSelected[cmptfader][tt]==1)
  {
  DockIsSelected[cmptfader][tt]=0;
  if(tt>0){ DockIsSelected[cmptfader][tt-1]=1;break;}
  else if(tt==0){DockIsSelected[cmptfader][core_user_define_nb_docks-1]=1;break;}
  }
 }
 }
}
//si pas bouclé, juste une sequence
else if(is_dock_for_lfo_selected[cmptfader][ dockis]==0)
{
 lfo_cycle_is_on[cmptfader]=0;

 }
 }
 }
 }
 if(index_lfoing[cmptfader]==1)
 {
 index_fader_is_manipulated[cmptfader]=1; //pour direct channel
  if(FaderLocked[cmptfader]==1 && LockFader_is_FullLevel[cmptfader]==1)//masterisation au lock des autres faders
 {
 DoLock(cmptfader,Fader[cmptfader]);//remasterisation des niveaux
 //changement du niveau de lock, si on l augmente au dessus de son niveau de lock stocké
 if(Fader[cmptfader]>StateOfFaderBeforeLock[cmptfader] && FaderIsFlash[cmptfader]==0){StateOfFaderBeforeLock[cmptfader]=Fader[cmptfader];}
 }
 }
 /////CYCLE NETX / PREVIOUS ///////////////
  if(lfo_cycle_steps[cmptfader]==1 && lfo_do_next_step[cmptfader][0]==1 && dockis==0)
  {
  lfo_do_next_step[cmptfader][0]=0;
  lfo_do_next_step[cmptfader][1]=1;
  }
  else   if(lfo_cycle_steps[cmptfader]==1 && lfo_do_next_step[cmptfader][1]==1 && dockis==core_user_define_nb_docks-1)
  {
  lfo_do_next_step[cmptfader][1]=0;
  lfo_do_next_step[cmptfader][0]=1;
  }
  ////////////////////////////////


}
 return(0);
}

//////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

int Merger_Faders()
{

 //merging des valeurs des faders en HTP
 int tmp_val=0;
 for (int h=0;h<513;h++)
 {
 bufferFaders[h]=0;
 channel_is_touched_by_fader_fx[h]=0;
 for(int cif=0;cif<core_user_define_nb_faders;cif++)
 {
 switch(fader_mode_with_buffers[cif])
 {
 case 0://HTP normal
 switch(fader_fx_route[cif])
 {
 case 0:
       bufferFaders[h]=Tmax(bufferFaders[h],FaderDoDmx[cif][h]);
 break;
 case 1:
      if(FaderDoDmx[cif][h]>0)
      {
      bufferSequenciel[h]=Tmax(bufferSequenciel[h],FaderDoDmx[cif][h]);
      channel_is_touched_by_fader_fx[h]=1;
      channel_is_touched_by_fader_number[h]=cif;
      channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
      }
 break;
 default: break;
 }
 break;
 case 1://Exclude rendering
 // rien ne se passe, ne sont pas reportés dans le buffer fader
 break;
 case 2://substract
  switch(fader_fx_route[cif])
 {
 case 0:
 tmp_val=bufferFaders[h]-FaderDoDmx[cif][h];
 if(tmp_val<0){tmp_val=0;}
 bufferFaders[h]=tmp_val;
 break;
 case 1:
 if(FaderDoDmx[cif][h]>0)
    {
       tmp_val=bufferSequenciel[h]-FaderDoDmx[cif][h];
       if(tmp_val<0){tmp_val=0;}
       bufferSequenciel[h]=tmp_val;
       channel_is_touched_by_fader_fx[h]=1;
       channel_is_touched_by_fader_number[h]=cif;
       channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
    }
 break;
 default: break;
 }
 break;
 case 3://add
 switch(fader_fx_route[cif])
 {
 case 0:
 if(FaderDoDmx[cif][h]>0)
 {
 tmp_val=bufferFaders[h]+FaderDoDmx[cif][h];
 if(tmp_val>255){tmp_val=255;}
 bufferFaders[h]=tmp_val;
 channel_is_touched_by_fader_fx[h]=1;
 channel_is_touched_by_fader_number[h]=cif;
 channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 break;
 case 1:
 if(FaderDoDmx[cif][h]>0)
 {
 tmp_val=bufferSequenciel[h]+FaderDoDmx[cif][h];
 if(tmp_val>255){tmp_val=255;}
 bufferSequenciel[h]=tmp_val;
 channel_is_touched_by_fader_fx[h]=1;
 channel_is_touched_by_fader_number[h]=cif;
 channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 break;
 default: break;
 }
 break;
 case 4: //screen
  switch(fader_fx_route[cif])
 {
 case 0:
 tmp_val=(int)((FaderDoDmx[cif][h]+bufferFaders[h])/2);
 if(tmp_val>255){tmp_val=255;}
 else if(tmp_val<0){tmp_val=0;}
 if(FaderDoDmx[cif][h]>0)
 {
 bufferFaders[h]=tmp_val;
 channel_is_touched_by_fader_fx[h]=1;
 channel_is_touched_by_fader_number[h]=cif;
 channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 break;
 case 1:
 tmp_val=(int)((FaderDoDmx[cif][h]+bufferSequenciel[h])/2);
 if(tmp_val>255){tmp_val=255;}
 else if(tmp_val<0){tmp_val=0;}
 if(FaderDoDmx[cif][h]>0)
 {
 bufferSequenciel[h]=tmp_val;
 channel_is_touched_by_fader_fx[h]=1;
 channel_is_touched_by_fader_number[h]=cif;
 channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 break;
 default: break;
 }
 break;
 case 5://exclusion
  switch(fader_fx_route[cif])
 {
 case 0:
 if(FaderDoDmx[cif][h]>0)
 {
 if(FaderDoDmx[cif][h]<bufferFaders[h])
 {
  tmp_val=bufferFaders[h]-FaderDoDmx[cif][h];
  if(tmp_val<0){tmp_val=0;}
  bufferFaders[h]=tmp_val;
  channel_is_touched_by_fader_fx[h]=1;
  channel_is_touched_by_fader_number[h]=cif;
  channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 else
 {
  tmp_val=FaderDoDmx[cif][h]-bufferFaders[h];
  if(tmp_val<0){tmp_val=0;}
  bufferFaders[h]=tmp_val;
  channel_is_touched_by_fader_fx[h]=1;
  channel_is_touched_by_fader_number[h]=cif;
  channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 }
 break;
 case 1:
 if(FaderDoDmx[cif][h]>0)
 {
 if(FaderDoDmx[cif][h]<bufferSequenciel[h])
 {
  tmp_val=bufferSequenciel[h]-FaderDoDmx[cif][h];
  if(tmp_val<0){tmp_val=0;}
  bufferSequenciel[h]=tmp_val;
  channel_is_touched_by_fader_fx[h]=1;
  channel_is_touched_by_fader_number[h]=cif;
  channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 else
 {
  tmp_val=FaderDoDmx[cif][h]-bufferSequenciel[h];
  if(tmp_val<0){tmp_val=0;}
  bufferSequenciel[h]=tmp_val;
  channel_is_touched_by_fader_fx[h]=1;
  channel_is_touched_by_fader_number[h]=cif;
  channel_is_touched_by_fader_type_fx[h]=fader_mode_with_buffers[cif];
 }
 }
 break;
 default: break;
}
 break;
 default:
 break;
 }
 }
 }



 return(0);
}

int calculs_etats_faders_et_contenus()
{
 calculation_on_faders_done=0;
////////////////////////LOCK
for (int f=0;f<core_user_define_nb_faders;f++)
 {
if(FaderLocked[f]==1 && LockFader_is_FullLevel[f]==1)//masterisation au lock des autres faders
{
locklevel=Fader[f];
DoLock(f,Fader[f]);//remasterisation des niveaux
}
/////////////////////////
if(FaderIsFlash[f]==1 && FaderIsFlashBefore[f]==0)
{
LevelFaderBeforeFlash[f]=Fader[f];
fader_set_level(f,255);
//Fader[f]=255;
//midi_levels[f]=127;
//index_fader_is_manipulated[f]=1;
FaderIsFlashBefore[f]= FaderIsFlash[f];
}
else if (FaderIsFlash[f]==0 && FaderIsFlashBefore[f]==1)
{
//Fader[f]=LevelFaderBeforeFlash[f];
fader_set_level(f,LevelFaderBeforeFlash[f]);
//midi_levels[f]=Fader[f]/2;
FaderIsFlashBefore[f]= FaderIsFlash[f];
//index_fader_is_manipulated[f]=1;
}

////////////////////////
//report des valeurs des docks aux faders
 for (int d=0;d<core_user_define_nb_docks;d++)
 {
        if (DockIsSelected[f][d]==1)
        {
        switch(DockTypeIs[f][d])
        {
         //artnet
          case 2:
          for (int pp=0;pp<513;pp++)
              {
             FaderDockContains[f][d][pp]=(int)ArtNet_16xUniverse_Receiving[pp][(DockNetIs[f][d])];
              }
          break;
          //DMX IN
         case 3:
          for (int ppin=0;ppin<512;ppin++)//etait 513 aout 2016
             {
             FaderDockContains[f][d][ppin]=(int)dmxIN[ppin+1];
             }
          break;
           //VIDEO TRACKING
         case 4:
          for (int ppin=0;ppin<513;ppin++)//était 514 aout 2016
             {
             FaderDockContains[f][d][ppin]=(int)buffer_tracker[ppin];
           }
           break;
            // MEMOIRES
          case 5:
             for (int ppin=0;ppin<513;ppin++)//était 514 aout 2016
             {
             FaderDockContains[f][d][ppin]=Memoires[(DockHasMem[f][d])][ppin];
             }
          break;
          case 6://report et controle des fadersAudio
          Control_Audio_thruth_faders(f,d,0);
          break;
          case 7://report et controle des fadersAudio
          Control_Audio_thruth_faders(f,d,1);
          break;
          case 8://report et controle des fadersAudio
          Control_Audio_thruth_faders(f,d,2);
          break;

          case 10://direct channeling remoting
          switch (index_fader_is_manipulated[f])
          {
          case 0:
          beforeloop_for_directch[f]=Fader[f];

          Fader[f]=bufferSequenciel[(FaderDirectChan[f][d])];


          if(Fader[f]==255){midi_levels[f]=127;} else { midi_levels[f]=(int)Fader[f]/2;}
          if( beforeloop_for_directch[f]!=Fader[f])
          {
          index_send_midi_out[f]=1;
          }
          break;
          case 1:
          bufferSaisie[(FaderDirectChan[f][d])]=(255- curve_report[(FaderCurves[f])][(Fader[f])]);//pour etre actif: buffer saisi
          index_fader_is_manipulated[f]=0;
          break;
          default: break;
          }
          break;

          case 11://chasers
           for (int ppin=1;ppin<513;ppin++)
             {
             FaderDockContains[f][d][ppin]=MergerBufferChasers[(ChaserAffectedToDck[f][d])][ppin];
             }
          break;
          case 12://grid
           for (int ppin=1;ppin<513;ppin++)
           {
             if(ppin<grider_begin_channel_is-1)
             {
              FaderDockContains[f][d][ppin]=0;//nettoyage à cause de l adressage   si chgt adresse faut nettoyer le buffer
              }
             if(ppin+grider_begin_channel_is-1<513)//eviter débordement hors des 513 circuits
             {
             FaderDockContains[f][d][ppin+grider_begin_channel_is-1]=buffer_gridder[(faders_dock_grid_affectation[f][d])][ppin-1];
             }
           }
          break;
          case 13://fgroup

          for (int ppin=1;ppin<513;ppin++)
              {FaderDockContains[f][d][ppin]=0;}

          for(int fg=0;fg<48;fg++)
          {
          if(fgroup[f][d][fg]==1)
          {
               for (int ppin=1;ppin<513;ppin++)
              {
              FaderDockContains[f][d][ppin]=Tmax(FaderDockContains[f][d][ppin],FaderDoDmx[fg][ppin]);
              }
          }
          }
          break;

          case 14://mover
           for (int ppin=1;ppin<513;ppin++)
           {
              FaderDockContains[f][d][ppin]=buffer_moving_head[ppin];
           }
          break;
          case 15://draw
        //  if(drawing_bitmap==0)
       //   {
          //calcul normal
           for (int ppin=1;ppin<513;ppin++)
           {
            FaderDockContains[f][d][ppin]=0;
           for(int p=0;p<500;p++)
           {
           if(draw_preset_channel_routing[(DrawAffectedToDck[f][d])][p]==ppin)
              {
              FaderDockContains[f][d][ppin]=int (255 * draw_preset_levels[(DrawAffectedToDck[f][d])][p] );
              }
           }
           }
         //  }
          break;
          case 16://echo
            for (int ppin=1;ppin<513;ppin++)
           {
            FaderDockContains[f][d][ppin]=int (255.0 * echo_levels[(echo_affected_to_dock[f][d])][0][ppin-1] );
           }
          break;
          case 17://Wave
            for (int ppin=1;ppin<513;ppin++)
           {
            FaderDockContains[f][d][ppin]= buffer_wave[ppin];
           }
          break;
          default:
          break;
          }

 //data normal

        for (int j=1;j<514;j++)
       {
        FaderDoDmx[f][j]=(int)(((float)(FaderDockContains[f][d][j])/255)  * (255- curve_report[(FaderCurves[f])][(Fader[f])]) );
      //avant curve:  FaderDoDmx[f][j]=(int)(((float)(FaderDockContains[f][d][j])/255)  * Fader[f]);
       }
 }
 }
 }
 calculation_on_faders_done=1;
 return(0);
}
////////////////////////////////////////////////////////////////////////////////
int Merger_Sequenciel()
{
for (int p=1;p<514;p++)
{
 if (bufferSaisie[p]==bufferBlind[p])
 {
  bufferSequenciel[p]=bufferBlind[p];
 }
 else if(bufferSaisie[p]>bufferBlind[p])
 {
 bufferSequenciel[p]=
 bufferBlind[p]+(unsigned char)(((float)(bufferSaisie[p]-bufferBlind[p])/255)*niveauX1);
 }
 else if(bufferSaisie[p]<bufferBlind[p])
 {
 bufferSequenciel[p]=
 bufferSaisie[p]+(unsigned char)(((float)(bufferBlind[p]-bufferSaisie[p])/255)*niveauX2);
 }
 if(index_crossfading==1 || index_pause==1)
 {
 if((bufferSequenciel[p]+ channel_level_mofification_while_crossfade[p]>=0) && (bufferSequenciel[p]+ channel_level_mofification_while_crossfade[p]<=255))
 {bufferSequenciel[p]+=channel_level_mofification_while_crossfade[p];}
 else if (bufferSequenciel[p]+ channel_level_mofification_while_crossfade[p]>255){bufferSequenciel[p]=255;}
 else if (bufferSequenciel[p]+ channel_level_mofification_while_crossfade[p]<0){bufferSequenciel[p]=0;}
 }
}
return(0);
}
////////////////////////////////////////////////////////////////////////////////
int Merger()
{
 //rafraichissement visuel, pour pb de synchro entre calculs et rapidité affichage mis en amont d une frame
 for (int i=1;i<514;i++)
 {
 buffer_affichage_valeurs_sequenciel[i]=bufferSequenciel[i];
 }

 if(core_do_calculations[1]==1)
 {
 Merger_Sequenciel();
 }
 if(core_do_calculations[0]==1)
 {
 calculs_etats_faders_et_contenus();//contenus fader par fader
 Merger_Faders();//buffer fader general
 }

 int circrootpatch=0;
 for (int i=1;i<514;i++)
 {
 switch(freeze_array[i])
 {
 case 0:
// MergerArray[i]=bufferSequenciel[i]>?bufferFaders[i];
 MergerArray[i]= Tmax (bufferSequenciel[i],bufferFaders[i]);
 //MASTER
 if(Channels_excluded_from_grand_master[i]==0)
 {
 MergerArray[i]=(int)(((float)(MergerArray[i])/255)*niveauGMaster);
 }
 break;
 case 1:
 MergerArray[i]=freeze_state[i];
 break;
 default: break;
 }

 //go et pause channel
 if(index_go==1 && index_pause==0 && go_channel_is>0 && go_channel_is<513)
 {
  bufferSequenciel[go_channel_is]=(unsigned char) (255* alpha_blinker);
  MergerArray[go_channel_is]=(unsigned char)(255* alpha_blinker);
 }

  if(index_go==1 && index_pause==1 && pause_channel_is>0 && pause_channel_is<513)
 {
  bufferSequenciel[pause_channel_is]=(unsigned char) (255* alpha_blinker);
  MergerArray[pause_channel_is]=(unsigned char)(255* alpha_blinker);
 }

 if(index_go==0 && index_pause==0 )
 {
 if(go_channel_is>0 && go_channel_is<513)
 {bufferSequenciel[go_channel_is]=0;
  MergerArray[go_channel_is]=0;}
 if(pause_channel_is>0 && pause_channel_is<513)
  {bufferSequenciel[pause_channel_is]=0;
  MergerArray[pause_channel_is]=0;}
 }

 //Patch
 circrootpatch=Patch[i];
 DmxBlockPatch[i]=(MergerArray[circrootpatch]);

 //Curve
 for(int courb=0;courb<16;courb++)
 {
 if(curves[i]==courb)
 {
 DmxBlock[i]=255-curve_report[courb][(DmxBlockPatch[i])];
 }
 }


 //check channel override la sortie
 if(index_patch_overide==1)
 {
 if(patch_overide[i]==1){DmxBlock[i]=dimmer_check_level;}//75%
 }

 }
 return(0);
}
////////////////////////////////////////////////////////////////////////////////
int load_dmx_conf()
{
for(int i=0;i<NB_INTERFACES;i++)
{
    do_DMX_out[i]=0;
}
FILE *cfg_file = NULL ;
char read_buff[ 512 ] ;

	cfg_file = fopen("user\\config_dmx.txt", "rt" );
	if( !cfg_file )
	{
	 printf("\nPb à ouverture de config_dmx.txt\n");
     return 1;
	}

    //premiere ligne les args
	if( !fgets( read_buff , sizeof( read_buff ) ,cfg_file ) )
	{
     sprintf(string_save_load_report[idf],"! config_dmx.txt");
     return 1;
	}

	fscanf( cfg_file , "%d / %d / %d / %d / %d / %d /\n" ,  &do_DMX_out[0],&do_DMX_out[1],&do_DMX_out[2],&do_DMX_out[3],&do_DMX_out[4],&do_DMX_out[5] );

	fclose( cfg_file );


return(0);
}



int Save_my_dmx_conf()
{

FILE *fp;
char rep_conf_dmx[1024];
sprintf(rep_conf_dmx,"%s\\user\\config_dmx.txt",mondirectory);
if((fp=fopen(rep_conf_dmx,"w")))
{
fprintf(fp,"#arguments: 1st line:  Unused / Art-Net / Enttec Open / Enttec Pro / Sunlite / Unused / Unused \n");
fprintf(fp,"%d / %d / %d / %d / %d / %d /\n",do_DMX_out[0],do_DMX_out[1],do_DMX_out[2],do_DMX_out[3],do_DMX_out[4],do_DMX_out[5]);
}
fclose(fp);
save_artnet_conf();

sprintf(string_Last_Order,">>Saved DMX configuration");
return(0);
}


int Receive_DMX_IN()
{
if(do_DMX_out[4]==1 ) //sunlite
{
Receive_sunlite_dmxIN();
}

else if (index_init_EnttecPROIN_ok==1 && do_DMX_out[4]==0)
{
//memset(dmxIN,0,513);
resIn=Enttec_Pro_ReceiveData(SET_DMX_RX_MODE,dmxIN,513); //etait en 513
if(resIn<0)
            {
            sprintf(string_Last_Order,"DMX IN from ENTTEC PRO  FAILED");
            }
 }

return(0);
}

