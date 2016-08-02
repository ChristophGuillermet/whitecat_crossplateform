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

* \file wizard_operations.cpp
* \brief {GUI fonctions for wizard }
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Core fonctions pour la fenêtre wizard, il s'agit d'un outil permettant de faire des changement, copier coler, changement d'etat etc.. dans toutes les mémoires de la conduite ou partielement
*
*   Core fonctions for the wizard window, a tool to change parameter easly in all memories or group of memories
*
**/

int wizard_detect_unused_channels(int wizard_from_mem, int wizard_to_mem)
{
bool used_channel[514];
for(int look=wizard_from_mem;look<=wizard_to_mem;look++)
{
if(MemoiresExistantes[look]==1)
{
for (int l=1;l<514;l++)
{
if(Memoires[look][l]>0)
{
used_channel[l]=1;
}
}
}
}
//report sur selection
for(int l=1;l<514;l++)
{
Selected_Channel[l]=1-used_channel[l];
}

return(0);
}


int wizard_calcul_nbre_de_mem()
{
   nbre_de_mems_manipulees=0;
   for(int memo=wizard_from_mem;memo<=wizard_to_mem;memo++)
   {
   if(MemoiresExistantes[memo]==1){nbre_de_mems_manipulees++;}
   }
 return(0);
}

int wizard_calcul_nbre_de_mem_deleted()
{
   nbre_de_mems_manipulees=0;
   for(int memo=wizard_from_mem;memo<=wizard_to_mem;memo++)
   {
   if(MemoiresDetruites[memo]==1){nbre_de_mems_manipulees++;}
   }

return(0);
}



int wizard_rebuild(int facteur_memoires)
{
int mem_p=wizard_from_mem;

for(int look=wizard_from_mem;look<=wizard_to_mem;look++)
{
if(Wiz_MemoiresExistantes[look]==1)
{
MemoiresExistantes[mem_p]=Wiz_MemoiresExistantes[look];
for(int cho=0;cho<513;cho++)
{Memoires[mem_p][cho]=Wiz_Memoires[look][cho];}
for(int t=0;t<4;t++)
{Times_Memoires[mem_p][t]=Wiz_Times_Memoires[look][t];}
Links_Memoires[mem_p]=Wiz_Links_Memoires[look];
Banger_Memoire[mem_p]=Wiz_Banger_Memoire[look];
sprintf(descriptif_memoires[mem_p],Wiz_descriptif_memoires[look]);
sprintf(annotation_memoires[mem_p],Wiz_annotation_memoires[look]);

Wiz_MemoiresExistantes[look]=0;
mem_p+=facteur_memoires;
}

}
position_onstage=wizard_from_mem;
refresh_mem_onstage(position_onstage);
detect_mem_before_one();
detect_mem_preset();
refresh_mem_onpreset(position_preset);

 return(0);
}


int wizard_clear_transfert_array()
{
for(int pm=wizard_from_mem;pm<=wizard_to_mem;pm++)
{
Wiz_MemoiresExistantes[pm]=0;
for(int cho=0;cho<513;cho++)
{
Wiz_Memoires[pm][cho]=0;
}
Wiz_Times_Memoires[pm][0]=0.0;
Wiz_Times_Memoires[pm][1]=0.0;
Wiz_Times_Memoires[pm][2]=0.0;
Wiz_Times_Memoires[pm][3]=0.0;
Wiz_Links_Memoires[pm]=0;
Wiz_Banger_Memoire[pm]=0;
strcpy(Wiz_descriptif_memoires[pm],"");
strcpy(Wiz_annotation_memoires[pm],"");
Wiz_descriptif_memoires[pm][24]='\0';
Wiz_annotation_memoires[pm][24]='\0';
}
 return(0);
}

int wizard_clear_mem_original()
{
for(int pm=wizard_from_mem;pm<=wizard_to_mem;pm++)
{
MemoiresExistantes[pm]=0;
for(int cho=0;cho<513;cho++)
{
Memoires[pm][cho]=0;
}
Times_Memoires[pm][0]=0.0;
Times_Memoires[pm][1]=0.0;
Times_Memoires[pm][2]=0.0;
Times_Memoires[pm][3]=0.0;
Links_Memoires[pm]=0;
Banger_Memoire[pm]=0;
strcpy(descriptif_memoires[pm],"");
descriptif_memoires[pm][24]='\0';
strcpy(annotation_memoires[pm],"");
annotation_memoires[pm][24]='\0';
}
 return(0);
}

int wizard_delete_mem()
{
for(int pm=wizard_from_mem;pm<=wizard_to_mem;pm++)
{
MemoiresExistantes[pm]=0;
MemoiresDetruites[pm]=1;
}
 return(0);
}


int wizard_restore_mem()
{
for(int pm=wizard_from_mem;pm<=wizard_to_mem;pm++)
{
if(MemoiresDetruites[pm]==1){MemoiresExistantes[pm]=1;MemoiresDetruites[pm]=0;}
}
 return(0);
}

int wizard_copy_mem()
{
wizard_clear_transfert_array();
for(int pm=wizard_from_mem;pm<=wizard_to_mem;pm++)
{
Wiz_MemoiresExistantes[pm]=MemoiresExistantes[pm];
for(int cho=0;cho<513;cho++)
{
Wiz_Memoires[pm][cho]=Memoires[pm][cho];
}
for(int t=0;t<4;t++)
{
Wiz_Times_Memoires[pm][t]=Times_Memoires[pm][t];
}
Wiz_Links_Memoires[pm]=Links_Memoires[pm];
Wiz_Banger_Memoire[pm]=Banger_Memoire[pm];
sprintf(Wiz_descriptif_memoires[pm],descriptif_memoires[pm]);
sprintf(Wiz_annotation_memoires[pm],annotation_memoires[pm]);
}
 return(0);
}

int wizard_inspekt_mem()
{
strcpy(tmp_wizbuffer,"");
char tmpw[8];

for (int w=1;w<513;w++)
{
if(Memoires[variable_wizard_mem][w]>0)
{
switch(dmx_view)
{
case 0:
sprintf(tmpw,"%d=%d ",w,(int)((float)Memoires[variable_wizard_mem][w]/2.55));
break;
case 1:
sprintf(tmpw,"%d=%d ",w,Memoires[variable_wizard_mem][w]);
break;
default: break;
}
strcat(tmp_wizbuffer, tmpw);
}
}

//splittage chaine caracters
for (int ly=0;ly<36;ly++)
{
strcpy(show_buff_wizOUT[ly],"");
for (int by=0;by<71;by++)
{
show_buff_wizOUT[ly][by]=tmp_wizbuffer[(ly*71)+by];
}
show_buff_wizOUT[ly][72]='\0';
}


return(0);
}

int wizard_insert_mems()
{
//nettoyage dans conduite des memoires en position d insertion
for(int pm=wizard_from_mem;pm<=wizard_from_mem+variable_wizard_mem;pm++)
{
MemoiresExistantes[pm]=0;
for(int cho=0;cho<513;cho++)
{
Memoires[pm][cho]=0;
}
Times_Memoires[pm][0]=0.0;
Times_Memoires[pm][1]=0.0;
Times_Memoires[pm][2]=0.0;
Times_Memoires[pm][3]=0.0;
Links_Memoires[pm]=0;
Banger_Memoire[pm]=0;
strcpy(descriptif_memoires[pm],"");
descriptif_memoires[pm][24]='\0';
strcpy(annotation_memoires[pm],"");
annotation_memoires[pm][24]='\0';
}
//recopie

for(int look=wizard_from_mem;look<=wizard_to_mem;look++)
{
if(Wiz_MemoiresExistantes[look]==1 && look+variable_wizard_mem<10000)
{
MemoiresExistantes[look+variable_wizard_mem]=Wiz_MemoiresExistantes[look];
for(int cho=0;cho<513;cho++)
{Memoires[look+variable_wizard_mem][cho]=Wiz_Memoires[look][cho];}
for(int t=0;t<4;t++)
{Times_Memoires[look+variable_wizard_mem][t]=Wiz_Times_Memoires[look][t];}
Links_Memoires[look+variable_wizard_mem]=Wiz_Links_Memoires[look];
Banger_Memoire[look+variable_wizard_mem]=Wiz_Banger_Memoire[look];
sprintf(descriptif_memoires[look+variable_wizard_mem],Wiz_descriptif_memoires[look]);
sprintf(annotation_memoires[look+variable_wizard_mem],Wiz_annotation_memoires[look]);
Wiz_MemoiresExistantes[look]=0;
}
}
position_onstage=wizard_from_mem;
refresh_mem_onstage(position_onstage);
detect_mem_before_one();
detect_mem_preset();
refresh_mem_onpreset(position_preset);


return(0);
}


int wizard_move_mems()
{
//backup de la conduite en entier
wizard_clear_transfert_array();

//sab 02/03/2014 set but not used bool Wiz_backup_exist_second[10000];
for(int pm=0;pm<10000;pm++)
{
Wiz_MemoiresExistantes[pm]=MemoiresExistantes[pm];
//sab 02/03/2014 set but not used Wiz_backup_exist_second[pm]=MemoiresExistantes[pm];
for(int cho=0;cho<513;cho++)
{
Wiz_Memoires[pm][cho]=Memoires[pm][cho];
}
for(int t=0;t<4;t++)
{
Wiz_Times_Memoires[pm][t]=Times_Memoires[pm][t];
}
Wiz_Links_Memoires[pm]=Links_Memoires[pm];
Wiz_Banger_Memoire[pm]=Banger_Memoire[pm];
sprintf(Wiz_descriptif_memoires[pm],descriptif_memoires[pm]);
sprintf(Wiz_annotation_memoires[pm],annotation_memoires[pm]);
}

//effacement de l existence de ces memoires
for(int pm=wizard_from_mem;pm<=wizard_to_mem;pm++)
{
MemoiresExistantes[pm]=0;
for(int cho=0;cho<513;cho++)
{
Memoires[pm][cho]=0;
}
Times_Memoires[pm][0]=0.0;
Times_Memoires[pm][1]=0.0;
Times_Memoires[pm][2]=0.0;
Times_Memoires[pm][3]=0.0;
Links_Memoires[pm]=0;
Banger_Memoire[pm]=0;
strcpy(descriptif_memoires[pm],"");
descriptif_memoires[pm][24]='\0';
strcpy(annotation_memoires[pm],"");
annotation_memoires[pm][24]='\0';
}

//recopie des memoires à insérer
int index_mem=0;
int fin_des_memoires=0;
for(int look=wizard_from_mem;look<=wizard_to_mem;look++)
{
if((variable_wizard_mem+index_mem)<10000)
{
MemoiresExistantes[variable_wizard_mem+index_mem]=Wiz_MemoiresExistantes[look];
for(int cho=0;cho<513;cho++)
{Memoires[variable_wizard_mem+index_mem][cho]=Wiz_Memoires[look][cho];}
for(int t=0;t<4;t++)
{Times_Memoires[variable_wizard_mem+index_mem][t]=Wiz_Times_Memoires[look][t];}
Links_Memoires[variable_wizard_mem+index_mem]=Wiz_Links_Memoires[look];
Banger_Memoire[variable_wizard_mem+index_mem]=Wiz_Banger_Memoire[look];
sprintf(descriptif_memoires[variable_wizard_mem+index_mem],Wiz_descriptif_memoires[look]);
sprintf(annotation_memoires[variable_wizard_mem+index_mem],Wiz_annotation_memoires[look]);
index_mem++;
fin_des_memoires=variable_wizard_mem+index_mem;
}
}
//le recopiage et decalage du reste
//arrondissage index_mem pour garder la logique du numérotage des .
index_mem/=10;
index_mem+=1;
index_mem*=10;
////////////////////////////////////////////
for(int look=fin_des_memoires;look<10000;look++)
{
if((look-index_mem)>0)
{
MemoiresExistantes[look]=Wiz_MemoiresExistantes[look-index_mem];
for(int cho=0;cho<513;cho++)
{Memoires[look][cho]=Wiz_Memoires[look-index_mem][cho];}
for(int t=0;t<4;t++)
{Times_Memoires[look][t]=Wiz_Times_Memoires[look-index_mem][t];}
Links_Memoires[look]=Wiz_Links_Memoires[look-index_mem];
Banger_Memoire[look]=Wiz_Banger_Memoire[look-index_mem];
sprintf(descriptif_memoires[look],Wiz_descriptif_memoires[look-index_mem]);
sprintf(annotation_memoires[look],Wiz_annotation_memoires[look-index_mem]);
}
}

position_onstage=variable_wizard_mem;
refresh_mem_onstage(position_onstage);
detect_mem_before_one();
detect_mem_preset();
refresh_mem_onpreset(position_preset);

return(0);
}

int wizard_reset_to_default_time()
{
for(int pm=wizard_from_mem;pm<=wizard_to_mem;pm++)
{
if(MemoiresExistantes[pm]==1)
{
Times_Memoires[pm][0]=0.0;
Times_Memoires[pm][2]=0.0;
Times_Memoires[pm][1]=default_time;//0=DIN 1=IN 2=DOUT 3=OUT
Times_Memoires[pm][3]=default_time;
}
}

return(0);
}



///////////////////////////////////////////////////////////////////////////////
int do_wizard_mem()
{
if(wizard_amplitude_is_global==1)
{
bool firstmem=0;
for(int m=0;m<10000;m++)
{
if(MemoiresExistantes[m]==1 && firstmem==0)
{
firstmem=1;
wizard_from_mem=m;
}
if(MemoiresExistantes[m]==1 && firstmem!=0)
{
wizard_to_mem=m;
}
}
}

switch(wizard_action_mem) // 0 rebuild numerical order / 1 insert me / 2 del mem / 3 move mem /
//4 inspekt delmem / 5 restore del mem / 6 set times / 7 reset times, links, bangers /
{
   case 0:// 0 rebuild numerical order
   wizard_copy_mem();
   wizard_calcul_nbre_de_mem();
   wizard_clear_mem_original();
   switch(mode_rebuild)
   {
   case 0:
   wizard_rebuild(1);
   break;
   case 1:
   wizard_rebuild(10);
   break;
   case 2:
   wizard_rebuild(100);
   break;
   default: break;
   }
   break;
   case 1:// 1 insert mem
   wizard_to_mem=9999;
   wizard_copy_mem();
   wizard_calcul_nbre_de_mem();
   wizard_clear_mem_original();
   wizard_insert_mems();
   break;
   case 2:// 2 del mem
   wizard_calcul_nbre_de_mem();
   wizard_delete_mem();
   break;
   case 3:// 3 move mem
   wizard_calcul_nbre_de_mem();
   wizard_move_mems();
   break;
   case 4://4 inspekt delmem
   wizard_inspekt_mem();
   break;
   case 5:// 5 restore del mem
   wizard_calcul_nbre_de_mem_deleted();
   wizard_restore_mem();
   break;
   case 6:// 6 reset times
   wizard_reset_to_default_time();
   break;
   default: break;
}

return(0);
}



int do_wizard_ch()
{
if(wizard_amplitude_is_global==1)
{
bool firstmem=0;
for(int m=0;m<10000;m++)
{
if(MemoiresExistantes[m]==1 && firstmem==0)
{
firstmem=1;
wizard_from_mem=m;
}
if(MemoiresExistantes[m]==1 && firstmem!=0)
{
wizard_to_mem=m;
}
}
}


switch(wizard_action) // 0 Set at level / 1 Add / 2 Reduce / 3 replace
{
case 0://Set at level
for(int m=wizard_from_mem;m<=wizard_to_mem;m++)
{
if(MemoiresExistantes[m]==1)
{
for(int co=1;co<512;co++)
{
if(wizard_buffer_in[co]==1)
{
switch(dmx_view)
{
case 0:
if(wizard_level_is>0)
{
Memoires[m][co]=(int)(((float)wizard_level_is)*2.55)+1;
}
else if(wizard_level_is==0)
{
Memoires[m][co]=0;
}
break;
case 1:
Memoires[m][co]=wizard_level_is;
break;
default: break;
}
}
}
}
}
break;
case 1://Add
for(int m=wizard_from_mem;m<=wizard_to_mem;m++)
{
if(MemoiresExistantes[m]==1)
{
for(int co=1;co<512;co++)
{
if(wizard_buffer_in[co]==1)
{
if(Memoires[m][co]>0)//on ne rajoute pas sur un circuit à 0%
{
switch(dmx_view)
{
case 0:
if(Memoires[m][co]+(int)((((float)wizard_level_is)*2.55)+1) <=255)
{
Memoires[m][co]+=(int)((((float)wizard_level_is)*2.55)+1);
}
else {Memoires[m][co]=255;}
break;
case 1:
if(Memoires[m][co]+wizard_level_is<=255)
{
Memoires[m][co]+=wizard_level_is;
}
else  {Memoires[m][co]=255;}
break;
default: break;
}
}
}
}
}
}
break;
case 2://Reduce
for(int m=wizard_from_mem;m<=wizard_to_mem;m++)
{
if(MemoiresExistantes[m]==1)
{
for(int co=1;co<512;co++)
{
if(wizard_buffer_in[co]==1)
{
if(Memoires[m][co]>0)//on ne retire pas sur un circuit à 0%
{
switch(dmx_view)
{
case 0:
if(Memoires[m][co]-(int)((((float)wizard_level_is)*2.55)+1)>=0)
{
Memoires[m][co]-=(int)((((float)wizard_level_is)*2.55)+1);
}
else {Memoires[m][co]=0;}
break;
case 1:
if(Memoires[m][co]-wizard_level_is>=0)
{
Memoires[m][co]-=wizard_level_is;
}
else {Memoires[m][co]=0;}
break;
default: break;
}
}
}
}
}
}
break;
case 3://Exchange Replace
unsigned char tmp_buff_wiz[514];
bool please_replace[514];

for(int m=wizard_from_mem;m<=wizard_to_mem;m++)
{
if(MemoiresExistantes[m]==1)
{
int index_replace=0;
//salve stocke
for(int co=1;co<513;co++)
{
//init
please_replace[co]=0;
tmp_buff_wiz[co]=0;

if(wizard_buffer_in[co]==1)
{
tmp_buff_wiz[co]=Memoires[m][co];
please_replace[co]=1;
Memoires[m][co]=0;
strcpy(descriptif_projecteurs[co],"");
}
}
//salve redistribue
int index_nbre_circuit=0;

for(int co=1;co<513;co++)
{
if(wizard_buffer_out[co]==1)
{
for(int p=index_replace;p<513;p++)
{
        if(number_inchannels==number_outchannels)
        {
                         if(please_replace[p]==1)
                         {
                         Memoires[m][co]=tmp_buff_wiz[p];
                         please_replace[p]=0;
                         break;
                         }
        }

        else if(number_inchannels<number_outchannels )
        {

                        if(please_replace[p]==1)
                        {
                        Memoires[m][co]=tmp_buff_wiz[p];
                        index_nbre_circuit++;
                        if(index_nbre_circuit<number_inchannels)
                        {
                        please_replace[p]=0;
                        break;
                        }
                        }
        }
}
}
}
}
}

//channel macros



break;
//SWAP
case 4:
//swap
bool swapIN[514];
bool swapOUT[514];
unsigned char tmp_buff_mem[514];
for(int m=wizard_from_mem;m<=wizard_to_mem;m++)
{
if(MemoiresExistantes[m]==1)
{
//salve recopie d exchange vers in
for(int co=1;co<513;co++)
{
tmp_buff_mem[co]=Memoires[m][co];
swapIN[co]=wizard_buffer_in[co];
swapOUT[co]=wizard_buffer_out[co];
}
for(int co=1;co<513;co++)
{
if(swapIN[co]==1)
{
for(int t=1;t<513;t++)
{
if(swapOUT[t]==1)
{
Memoires[m][co]=tmp_buff_mem[t];
swapOUT[t]=0;break;
}
}
}
}
//salve recopie de in vers out
for(int co=1;co<513;co++)
{
swapOUT[co]=wizard_buffer_out[co];
}
for(int co=1;co<513;co++)
{
if(swapOUT[co]==1)
{
for(int t=1;t<513;t++)
{
if(swapIN[t]==1)
{
Memoires[m][co]=tmp_buff_mem[t];
swapIN[t]=0;break;
}
}
}
}

}
}



break;
default: break;
}

refresh_stage();


 return(0);
}

