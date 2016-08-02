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

* \file dmx_sunlite.cpp
* \brief {fonctions for the sunlite dmx interfaces}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions pour controller les interfaces dmx sunlite
*
*   Fonctions for the sunlite dmx interfaces
*
 **/

////////////////////SUNLITE///////////////////////////
#include <_DasHard.h>

extern "C"
{
//SIUDI 6C Dashard2006 Sunlite
typedef int (CALLBACK * DasUsbCommand)(int command, int param, unsigned char *bloc );
}

// pointeur de la fonction USBDMX2
//LP_DASHARDCOMMAND lp_DasHardCommand = NULL;

//le pointeur sunlite 2006
DasUsbCommand dasusbcommand = NULL;
HMODULE hLibSunlite = NULL;
unsigned char DmxBlockSunlite[512];
unsigned char dmxbackup_sunlite[512];
unsigned char dmxINsunlite[512];

int sunlite_version_number=0;
int sunlite_serial_number=0;


int open_sunlite()
{
//chargement dll
  hLibSunlite = LoadLibrary("DasHard2006.dll");
 if (hLibSunlite == NULL)
 {
     sprintf(string_display_dmx_params,"Impossible to load sunlite DLL");
 }

 dasusbcommand = (DasUsbCommand) GetProcAddress(hLibSunlite, "DasUsbCommand");
 if (dasusbcommand == NULL)
 {
    sprintf(string_display_dmx_params,"Impossible to Get ProcAdress DASHARD");
  }
//open device

   int iReto=dasusbcommand(DHC_INIT,0,NULL);//init
   if( iReto>0){	sprintf(string_display_dmx_params,"Init Sunlite DLL version %d=Ok", iReto);}

   iReto = dasusbcommand(DHC_OPEN,0,NULL);
  		 	    if (iReto == 0)
    	    	{
    	    	sprintf(string_display_dmx_params,"Impossible to to open interface, is it PLUGGED ? Error: %d", iReto);
                }
                else if(iReto==1)
                {
                sprintf(string_display_dmx_params,"Sunlite open=Ok");
                }
   sunlite_version_number=dasusbcommand(DHC_VERSION,0,NULL);
   sunlite_serial_number=dasusbcommand(DHC_SERIAL,0,NULL);
   if (sunlite_serial_number>150001 && sunlite_serial_number<150001+100000)
   {
   sprintf(string_sunlite_is,"SIDUI-8C interface");
   index_is_siudi_8C=1;
   }
   else if (sunlite_serial_number>562173952 && sunlite_serial_number<562173952+100000){sprintf(string_sunlite_is,"SIDUI-5C interface");}
   else  if (sunlite_serial_number>61865984 && sunlite_serial_number<61865984+100000){sprintf(string_sunlite_is,"SIDUI-6C interface");}


 return(0);
}

int close_sunlite()
{
 //fermeture device
 if (dasusbcommand != NULL)
         {
              int iReto=dasusbcommand(DHC_CLOSE,0,0);
              switch(iReto)
              {
              case 1:
              sprintf(string_display_dmx_params,"Sunlite close=Ok");
              break;
              case -2:
              sprintf(string_display_dmx_params,"Sunlite close=No / Device not open");
              break;
              case -1:
              sprintf(string_display_dmx_params,"Sunlite close=No / Error Command");
              break;
              default: break;
              }

              dasusbcommand(DHC_EXIT,0,NULL);
              sprintf(string_display_dmx_params,"Sunlite close dll access=Ok");
         }

 //déchargement dll
 if (hLibSunlite != NULL)
     {     FreeLibrary(hLibSunlite);
        hLibSunlite = NULL;
     }

sprintf(string_display_dmx_params,">>Sunlite closed");
 return(0);
}



int sunlite_send_data()
{
do_send_dmx_on_change_siudi=0;
for(int z=0;z<512;z++)
       {
       DmxBlockSunlite[z]=DmxBlock[z+1];
       //au cas ou 5C ou 6C ont besoin de tempo
       if(index_is_siudi_8C==0 && DmxBlockSunlite[z]!=dmxbackup_sunlite[z])
       {  do_send_dmx_on_change_siudi=1;}
       }

if (dasusbcommand >0)
       { dasusbcommand(DHC_DMXOUT,512,DmxBlockSunlite);  }
 return(0);
}


int Receive_sunlite_dmxIN()
{
if(dasusbcommand >0 && index_quit==0 && index_allow_sunlite_dmxIN==1)
{
//int Reto=dasusbcommand(DHC_DMX2IN,512,dmxINsunlite);
for (int p=0;p<512;p++)
{
 dmxIN[p+2]=dmxINsunlite[p];   //ok +2 fonctionne tres bien de 1 à 512 compris
}
}
return(0);
}

int reset_dmx_out()
{
dasusbcommand(DHC_DMXOUTOFF,0,0);
 return(0);
}

