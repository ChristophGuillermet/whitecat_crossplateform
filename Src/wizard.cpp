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

* \file wizard.cpp
* \brief {GUI fonctions for wizard }
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   GUI fonctions pour la fenêtre wizard, il s'agit d'un outil permettant de faire des changement, copier coler, changement d'etat etc.. dans toutes les mémoires de la conduite ou partielement
*
*   GUI fonctions for the wizard window, a tool to change parameter easly in all memories or group of memories
*
**/


int clear_wizard_store_ch_in()
{
//la grande ligne non splitée
for (int p=0;p<2160;p++)
{tmp_wizbuffer[p]=' ';}

for (int ly=0;ly<36;ly++)
{
show_buff_wizIN[ly][72]=' ';
strcpy(show_buff_wizIN[ly],"");
for (int by=0;by<73;by++)
{
show_buff_wizIN[ly][by]=' ';
}

}
for (int w=1;w<513;w++)
{
wizard_buffer_in[w]=0;
}
number_inchannels=0;
position_ligne_wizard_out=1;
index_main_clear=0;
return(0);
}

int clear_wizard_store_ch_out()
{
//la grande ligne non splitée
for (int p=0;p<2160;p++)
{tmp_wizbuffer[p]=' ';}

for (int ly=0;ly<36;ly++)
{
show_buff_wizOUT[ly][72]=' ';
strcpy(show_buff_wizOUT[ly],"");
for (int by=0;by<73;by++)
{
show_buff_wizOUT[ly][by]=' ';
}

}
for (int w=1;w<513;w++)
{
wizard_buffer_out[w]=0;
}
number_outchannels=0;
position_ligne_wizard_out=0;
return(0);
}

int wizard_store_channel_in()
{
number_inchannels=0;
clear_wizard_store_ch_in();

strcpy( tmp_wizbuffer,"");


for (int w=1;w<513;w++)
{
wizard_buffer_in[w]=Selected_Channel[w];
}

char tmpw[6];
for (int w=1;w<513;w++)
{
if(wizard_buffer_in[w]==1)
{
sprintf(tmpw,"%d-", w);
strcat(tmp_wizbuffer, tmpw);
number_inchannels++;
}
}

for (int ly=0;ly<36;ly++)
{
strcpy(show_buff_wizIN[ly],"");
for (int by=0;by<71;by++)
{
show_buff_wizIN[ly][by]=tmp_wizbuffer[(ly*71)+by];
}
show_buff_wizIN[ly][72]='\0';
}

for (int ci=1;ci<514;ci++)
{Selected_Channel[ci]=0;}

last_ch_selected=0;
index_level_attribue=0;

index_do_dock=0;
return(0);
}

int wizard_store_channel_out()
{
number_outchannels=0;
clear_wizard_store_ch_out();
for (int w=1;w<513;w++)
{
wizard_buffer_out[w]=Selected_Channel[w];
}
strcpy( tmp_wizbuffer,"");
char tmpw[6];
for (int w=1;w<513;w++)
{
if(wizard_buffer_out[w]==1)
{
sprintf(tmpw,"%d-", w);
strcat(tmp_wizbuffer, tmpw);
number_outchannels++;
}
}

for (int ly=0;ly<36;ly++)
{
strcpy(show_buff_wizOUT[ly],"");
for (int by=0;by<71;by++)
{
show_buff_wizOUT[ly][by]=tmp_wizbuffer[(ly*71)+by];
}
show_buff_wizOUT[ly][72]='\0';
}

for (int ci=1;ci<513;ci++)
{Selected_Channel[ci]=0;}
last_ch_selected=0;
index_level_attribue=0;

index_do_dock=0;
return(0);
}




int Box_mem_to_mem(int xb, int yb)
{

///////////////SUR TOUTE LA CONDUITE OU DE MEM A MEM //////////////////////////

Rect Allmem(Vec2D((xb+270),(yb+170)), Vec2D( 50,20));
Allmem.SetRoundness(7.5);
Allmem.SetLineWidth(triple_epaisseur_ligne_fader);
Allmem.Draw(CouleurFond.WithAlpha(0.5));
petitchiffre.Print("On ALL the memories",xb+325,yb+180);

Rect Frommem(Vec2D((xb+270),(yb+205)), Vec2D( 50,20));
Frommem.SetRoundness(7.5);
Frommem.SetLineWidth(triple_epaisseur_ligne_fader);
Frommem.Draw(CouleurFond.WithAlpha(0.5));
petitchiffre.Print("From memory",xb+325,yb+220);
petitchiffre.Print("To memory",xb+325,yb+255);


switch(wizard_amplitude_is_global)
{
case 0:
Frommem.Draw(CouleurFader);
break;
case 1:
Allmem.Draw(CouleurFader);
break;
default: break;
}

if(window_focus_id==W_WIZARD && mouse_x>xb+270 && mouse_x<xb+320 )
{
if(mouse_y>yb+170 && mouse_y<yb+190)//wizard global
{
if(mouse_button==1 && mouse_released==0)
{
wizard_amplitude_is_global=1;
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
wizard_calcul_nbre_de_mem();
mouse_released=0;
}
}
if(mouse_y>yb+205 && mouse_y<yb+225 && window_focus_id==921)//wizard mem to mem
{
if(mouse_button==1 && mouse_released==0)
{
wizard_amplitude_is_global=0;
wizard_calcul_nbre_de_mem();
mouse_released=0;
}
}
}

//FROM TO
char mem_wiz_tmp[7];

Rect wiz_fromMem(Vec2D(xb+410,yb+200), Vec2D( 60,30));
wiz_fromMem.SetRoundness(7.5);
wiz_fromMem.Draw(CouleurFond.WithAlpha(0.5));

sprintf(mem_wiz_tmp,"%d.%d",wizard_from_mem/10,wizard_from_mem%10);
petitchiffre.Print(mem_wiz_tmp,xb+425,yb+220);

Rect wiz_toMem(Vec2D(xb+410,yb+235), Vec2D( 60,30));
wiz_toMem.SetRoundness(7.5);
wiz_toMem.Draw(CouleurFond.WithAlpha(0.5));

sprintf(mem_wiz_tmp,"%d.%d",wizard_to_mem/10,wizard_to_mem%10);
petitchiffre.Print(mem_wiz_tmp,xb+425,yb+255);


if(wizard_amplitude_is_global==0)
{
if(window_focus_id==W_WIZARD && mouse_x>xb+410 && mouse_x<xb+470 )
{
//from
if( mouse_y>yb+200 && mouse_y<yb+230)
{
wiz_fromMem.DrawOutline(CouleurLigne);

if(mouse_button==1 && mouse_released==0)
{
int tempentry=(int)(10*atof(numeric));
reset_numeric_entry();
if(tempentry>=0.0 && tempentry<10000)
{
wizard_from_mem=tempentry;
wizard_calcul_nbre_de_mem();
}
else {sprintf(string_Last_Order,">>Wrong entry : a Mem is from 0.0 to 999.9!");}
mouse_released=1;
}
}
//to
if( mouse_y>yb+235 && mouse_y<yb+265 && window_focus_id==921)
{
wiz_toMem.DrawOutline(CouleurLigne);

if(mouse_button==1 && mouse_released==0)
{
int tempentry=(int)(10*atof(numeric));
reset_numeric_entry();
if(tempentry>=0.0 && tempentry<10000)
{
wizard_to_mem=tempentry;
wizard_calcul_nbre_de_mem();
}
else {sprintf(string_Last_Order,">>Wrong entry : a Mem is from 0.0 to 999.9!");}
mouse_released=1;
}
}
}
}
 return(0);
}

int fenetre_wizard(int xb,int yb)
{

Rect wiz_backg(Vec2D(xb,yb), Vec2D( 480,420));
wiz_backg.SetRoundness(15);
wiz_backg.SetLineWidth(triple_epaisseur_ligne_fader);
wiz_backg.Draw(CouleurBleuProcedure);
if(window_focus_id==921)
{
wiz_backg.DrawOutline(CouleurFader);
}
else
{
 wiz_backg.DrawOutline(CouleurLigne);
}

/////////////////////////////////////////////////////////
Rect wiz_ch2(Vec2D(xb+10,(yb+270)), Vec2D( 460,100));
wiz_ch2.SetRoundness(15);
wiz_ch2.Draw(CouleurFond.WithAlpha(0.5));
//num ligne
petitpetitchiffrerouge.Print(ol::ToString(position_ligne_wizard_out+1),(xb+450), (yb+320));
//////////////////UP DOWN LINE  BOX/////////////////////
Circle LineUp(Vec2D(xb+450,yb+290),12);
LineUp.Draw(CouleurFond);
Circle LineDown(Vec2D(xb+450,yb+350),12);
LineDown.Draw(CouleurFond);
if(window_focus_id==W_WIZARD && mouse_x>xb+438 && mouse_x<xb+462)
{
if(mouse_y>yb+278 && mouse_y<yb+302)
{
LineUp.Draw(CouleurSurvol);
if(mouse_button==1)
{
LineUp.Draw(CouleurFader);
if(position_ligne_wizard_out>0){position_ligne_wizard_out--;}
}
}
else if(mouse_y>yb+338 && mouse_y<yb+362)
{
LineDown.Draw(CouleurSurvol);
if(mouse_button==1)
{
LineDown.Draw(CouleurFader);
if(position_ligne_wizard_out<36){position_ligne_wizard_out++;}
}
}
}
petitchiffre.Print("-",xb+447,yb+293);
petitchiffre.Print("+",xb+446,yb+353);
LineUp.DrawOutline(CouleurLigne);
LineDown.DrawOutline(CouleurLigne);
///////////////////////////////////////////////////////////////////////////////

Rect wiz_mode(Vec2D(xb+105,yb+3), Vec2D( 130,30));
wiz_mode.SetRoundness(15);
wiz_mode.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_WIZARD && mouse_x>xb+105 && mouse_x<xb+235 && mouse_y>yb+3 && mouse_y<yb+33)
{
 wiz_mode.Draw(CouleurFader);
if(mouse_button==1 && mouse_released==0)
{
 index_wizard_ch_mode=toggle(index_wizard_ch_mode);
 mouse_released=1;
}
}
wiz_mode.DrawOutline(CouleurLigne);

if(index_wizard_ch_mode==0)
{
//wizard mem
neuro.Print( "Wizard MEM",(xb+110), (yb+25));
///////MEM TO MEM////////////////////////////////////////////////////////////
Box_mem_to_mem(xb,yb-110);
char templim[32];

for (int li=0;li<7;li++)
{
    Rect domact(Vec2D((xb+20),(yb+60+(li*30))), Vec2D( 50,20));
    domact.SetRoundness(7.5);
    domact.Draw(CouleurFond.WithAlpha(0.5));
    if(window_focus_id==W_WIZARD && mouse_x>xb+20 && mouse_x<xb+70 && mouse_y>yb+60+(li*30) && mouse_y<yb+80+(li*30) )
    {
                     if(mouse_button==1 && mouse_released==0)
                     {
                     wizard_action_mem=li;
                     mouse_released=1;
                     }
    }
if(wizard_action_mem==li){domact.Draw(CouleurFader); }

switch (li)
{
case 0:
     sprintf(templim,"Rebuild Numerical Order ");
break;
case 1:
     sprintf(templim,"Insert Memories");
break;
case 2:
     sprintf(templim,"Delete Memories");
break;
case 3:
     sprintf(templim,"Move memories");
break;
case 4:
     sprintf(templim,"Inspect a deleted Memory");
break;
case 5:
     sprintf(templim,"Restore deleted Memories");
break;
case 6:
     sprintf(templim,"Reset to default Time");
break;
default: break;
}
petitchiffre.Print(templim,xb+80,yb+75+(li*30));
}


char tmp_str_m[36];
sprintf(tmp_str_m,"Number of memories: %d",nbre_de_mems_manipulees);
petitchiffre.Print(tmp_str_m,xb+270,yb+30);
////LES OPTIONS


switch(wizard_action_mem)
{
case 0://REBUILD
     petitchiffre.Print("Rebuild Mode:", xb+270 , yb+180);
     Line(Vec2D( xb+270 , yb+190),Vec2D( xb+370 , yb+190)).Draw(CouleurLigne);
     for(int mod=0;mod<3;mod++)
     {
     Rect choose_mode_rebuild(Vec2D((xb+300),(yb+200+(wizard_action_mem*30)+(mod*20))), Vec2D( 30,15));
     choose_mode_rebuild.SetRoundness(5);
     choose_mode_rebuild.SetLineWidth(epaisseur_ligne_fader);
     choose_mode_rebuild.Draw(CouleurFond.WithAlpha(0.5));
     switch (mod)
     {
     case 0:
     petitchiffre.Print("0.2 /0.3 / 0.4 ...", xb+360 , yb+210+(wizard_action_mem*30)+(mod*20));
     break;
     case 1:
     petitchiffre.Print("2 /3 /4 ...", xb+360 , yb+210+(wizard_action_mem*30)+(mod*20));
     break;
     case 2:
     petitchiffre.Print("20 /30 /40 ...", xb+360 , yb+210+(wizard_action_mem*30)+(mod*20));
     break;
     default: break;
     }
     if(mod==mode_rebuild){choose_mode_rebuild.DrawOutline(CouleurLevel); }
     if(window_focus_id==W_WIZARD &&mouse_x>xb+300 && mouse_x<xb+330 && mouse_y> yb+200+(wizard_action_mem*30)+(mod*20) && mouse_y<yb+215+(wizard_action_mem*30)+(mod*20))
     {
     //sab 02/03/2014 IMPACT if(mouse_button=1 && mouse_released==0)
     if(mouse_button==1 && mouse_released==0)
     {
     mode_rebuild=mod;
     mouse_released=1;
     }
     }
     }
break;
case 1://INSERT MEMS
petitchiffre.Print("Number of Memories to insert", xb+270 , yb+180);
     Line(Vec2D( xb+270 , yb+190),Vec2D( xb+370 , yb+190)).Draw(CouleurLigne);
break;
case 3://deplacer
petitchiffre.Print("Move to place:", xb+270 , yb+180);
Line(Vec2D( xb+270 , yb+190),Vec2D( xb+370 , yb+190)).Draw(CouleurLigne);
break;
case 4://inspection
petitchiffre.Print("Mem to inspekt:", xb+270 , yb+180);
Line(Vec2D( xb+270 , yb+190),Vec2D( xb+370 , yb+190)).Draw(CouleurLigne);
petitchiffre.Print("Mem contains  :",(xb+20), (yb+285));
for(int ly=0;ly<5;ly++)
{
petitpetitchiffre.Print(show_buff_wizOUT[ly+position_ligne_wizard_out],(xb+30), (yb+300)+(ly*15));
}
break;
default:
break;
}
//variable generale de manipulation : 1=Insert nombre de memoires  3= move memories to position  4= inspektion mem detruite
if(wizard_action_mem==1 || wizard_action_mem==3 || wizard_action_mem==4)
{
     Rect act_mem(Vec2D((xb+410),(yb+190)), Vec2D( 60,30));
     act_mem.SetRoundness(5);
     act_mem.SetLineWidth(epaisseur_ligne_fader);
     act_mem.Draw(CouleurFond.WithAlpha(0.5));

     if(window_focus_id==W_WIZARD && mouse_x> xb+410 && mouse_x<xb+470 && mouse_y> yb+190 && mouse_y<yb+210)
     {
     act_mem.DrawOutline(CouleurLevel);
     if(mouse_button==1 && mouse_released==0)
     {
     variable_wizard_mem=(int)(atof(numeric)*10);
     reset_numeric_entry();
     mouse_released=1;
     }
     }
     char tmp_sh_m[8];
     sprintf(tmp_sh_m,"%d.%d",variable_wizard_mem/10,variable_wizard_mem%10);
     petitchiffre.Print(tmp_sh_m,  xb+430, yb+ 210);
}

//fin mems
}

///////////////WIZARD CHANNEL PAGE///////////////////////////////////////////////
else if(index_wizard_ch_mode==1)
{
//wizard chann
neuro.Print( " Wizard  CH",(xb+110), (yb+25));
//
Rect detect_ch(Vec2D(xb+415,yb+10), Vec2D( 50,20));
detect_ch.SetRoundness(6);
detect_ch.Draw(CouleurFond.WithAlpha(0.5));
detect_ch.DrawOutline(CouleurBlanc.WithAlpha(0.5));
petitchiffre.Print("Select unused Channels",(xb+260), (yb+25));
if(window_focus_id==W_WIZARD  && mouse_x>xb+415 && mouse_x<xb+465 && mouse_y>yb+10 && mouse_y<yb+30 && mouse_released==0)
{
detect_ch.Draw(CouleurFader);
if(mouse_button==1 && mouse_released==0)
{
for (int l=1; l<514; l++)
{
     Selected_Channel[l]=0;
}

wizard_detect_unused_channels(wizard_from_mem, wizard_to_mem);
mouse_released=1;
}
}


///////MEM TO MEM////////////////////////////////////////////////////////////
Box_mem_to_mem(xb,yb);
//SELECTED CHANNEL BOX
Rect wiz_ch(Vec2D(xb+10,yb+40), Vec2D( 460,100));
wiz_ch.SetRoundness(15);
wiz_ch.Draw(CouleurFond.WithAlpha(0.5));
petitchiffre.Print("Selected Channels:   /",(xb+20), (yb+55));
petitchiffre.Print(ol::ToString(number_inchannels),(xb+170), (yb+55));
for(int ly=0;ly<5;ly++)
{
petitpetitchiffre.Print(show_buff_wizIN[ly+position_ligne_wizard_in],(xb+30), (yb+75)+(ly*15));
}
if(window_focus_id==W_WIZARD &&(index_do_dock==1 || index_main_clear==1 ) && mouse_x>xb+10 && mouse_x<xb+470 && mouse_y>yb+40 && mouse_y<yb+140 )
{
wiz_ch.DrawOutline(CouleurBlind);
if(mouse_button==1 && mouse_released==0)
{
if(index_do_dock==1)
{
wizard_store_channel_in();
}
else if(index_main_clear==1)
{
clear_wizard_store_ch_in();   index_main_clear=0;
}
mouse_released=1;
}
}
//////////////////UP DOWN LINE SEL CHAN /////////////////////
Circle LineUpO(Vec2D(xb+450,yb+60),12);
LineUpO.Draw(CouleurFond);
Circle LineDownO(Vec2D(xb+450,yb+120),12);
LineDownO.Draw(CouleurFond);
//num ligne
petitpetitchiffrerouge.Print(ol::ToString(position_ligne_wizard_in+1),(xb+450), (yb+110));
if(window_focus_id==W_WIZARD && mouse_x>xb+438 && mouse_x<xb+462)
{
if(mouse_y>yb+48 && mouse_y<yb+72)
{
LineUpO.Draw(CouleurSurvol);
if(mouse_button==1)
{
LineUpO.Draw(CouleurFader);
if(position_ligne_wizard_in>0){position_ligne_wizard_in--;}
}
}
else if(mouse_y>yb+108 && mouse_y<yb+132)
{
LineDownO.Draw(CouleurSurvol);
if(mouse_button==1)
{
LineDownO.Draw(CouleurFader);
if(position_ligne_wizard_in<36){position_ligne_wizard_in++;}
}
}
}
petitchiffre.Print("-",xb+447,yb+63);
petitchiffre.Print("+",xb+446,yb+123);
LineUpO.DrawOutline(CouleurLigne);
LineDownO.DrawOutline(CouleurLigne);

//EXHCAHNGE BOX////////////////////////////////////////////////////////////////
if(wizard_action==3 || wizard_action==4)
{

petitchiffre.Print("To Channels:   /",(xb+20), (yb+285));
petitchiffre.Print(ol::ToString(number_outchannels),(xb+170), (yb+285));
for(int ly=0;ly<5;ly++)
{
petitpetitchiffre.Print(show_buff_wizOUT[ly+position_ligne_wizard_out],(xb+30), (yb+300)+(ly*15));
}
if(window_focus_id==W_WIZARD && (index_do_dock==1 || index_main_clear==1) && mouse_x>xb+10 && mouse_x<xb+470 && mouse_y>yb+270 && mouse_y<yb+370 )
{
wiz_ch2.DrawOutline(CouleurBlind);
if(mouse_button==1 && mouse_released==0)
{
 if(index_do_dock==1)
{
wizard_store_channel_out();
}
else if(index_main_clear==1)
{
 clear_wizard_store_ch_out();    index_main_clear=0;
}
mouse_released=1;
}
}


//warning
if(wizard_action==3 && number_inchannels!=number_outchannels && number_outchannels!=0 && number_inchannels!=0  )
{
 Rect avertissement(Vec2D((xb+180), yb),Vec2D(300,40));
 avertissement.SetRoundness(7.5);
 avertissement.Draw(CouleurBlind.WithAlpha(alpha_blinker));
 petitpetitchiffre.Print("Number of channels are different: all exchanged chan. ",(xb+185), (yb+15));
 petitpetitchiffre.Print("will be set at last chan. level in selection !",(xb+185),(yb+35));

}
}



//////////////////////ACTIONS TYPE//////////////////////////////////////////////


char templi[24];
for (int li=0;li<4;li++)
{
Rect doact(Vec2D((xb+20),(yb+150+(li*30))), Vec2D( 50,20));
doact.SetRoundness(7.5);
doact.Draw(CouleurFond.WithAlpha(0.5));
if(window_focus_id==W_WIZARD && mouse_x>xb+20 && mouse_x<xb+70 && mouse_y>yb+150+(li*30) && mouse_y<yb+170+(li*30) )
{
if(mouse_button==1 && mouse_released==0)
{
wizard_action=li;
mouse_released=1;
}
}
if(wizard_action==li){doact.Draw(CouleurFader); }
switch (li)
{
case 0:
sprintf(templi,"Set at");
break;
case 1:
sprintf(templi,"Add from");
break;
case 2:
sprintf(templi,"Reduce from");
break;
case 3:
sprintf(templi,"Replace");
break;
default: break;
}
petitchiffre.Print(templi,xb+80,yb+165+(li*30));
}

//horizontales
Line(Vec2D(xb+150,yb+165),Vec2D(xb+220,yb+165)).Draw(CouleurLigne);
Line(Vec2D(xb+160,yb+195),Vec2D(xb+190,yb+195)).Draw(CouleurLigne);
Line(Vec2D(xb+180,yb+225),Vec2D(xb+220,yb+225)).Draw(CouleurLigne);
//verticales
Line(Vec2D(xb+220,yb+165),Vec2D(xb+220,yb+180)).Draw(CouleurLigne);
Line(Vec2D(xb+220,yb+225),Vec2D(xb+220,yb+210)).Draw(CouleurLigne);


////////////LEVEL BOX//////////////////////////////////////////////////////////

Rect levlTo(Vec2D((xb+190),(yb+180)), Vec2D( 60,30));
levlTo.SetRoundness(7.5);
levlTo.Draw(CouleurFond.WithAlpha(0.5));

if(window_focus_id==W_WIZARD && mouse_x>xb+190 && mouse_x<xb+250 && mouse_y>yb+180 && mouse_y<yb+210)
{
levlTo.DrawOutline(CouleurLigne);
if(mouse_button==1 && mouse_released==0)
{
wizard_level_is=atoi(numeric);
mouse_released=1;
reset_numeric_entry();
switch(dmx_view)
{
case 0:
if(wizard_level_is>100){wizard_level_is=100;}
else if (wizard_level_is<0){wizard_level_is=0;}
break;
case 1:
if(wizard_level_is>255){wizard_level_is=255;}
else if (wizard_level_is<0){wizard_level_is=0;}
break;
default: break;
}
}
}
petitchiffre.Print(ol::ToString(wizard_level_is),xb+213,yb+199);






////////////////SWAP BOX///////////////////////////////////////////////////////////
Rect swap(Vec2D((xb+170),(yb+240)), Vec2D( 50,20));
swap.SetRoundness(7.5);
swap.Draw(CouleurFond.WithAlpha(0.5));
if(wizard_action==4){swap.Draw(CouleurFader); }
petitchiffre.Print("Swap",xb+230,yb+255);

if(window_focus_id==W_WIZARD && mouse_x>xb+170 && mouse_x<xb+220 && mouse_y>yb+240 && mouse_y<yb+260)
{
if(mouse_button==1 && mouse_released==0)
{
wizard_action=4;
mouse_released=1;
}
}

}


////////////////////recharger depuis le disque dur////////////////////////////////////
Rect cancelit(Vec2D((xb+85),(yb+380)), Vec2D( 110,30));
cancelit.SetRoundness(15);
cancelit.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_WIZARD && mouse_x>xb+85 && mouse_x<xb+195 && mouse_y>yb+380 && mouse_y<yb+410 )
{
cancelit.Draw(CouleurFond.WithAlpha(0.5));
if(mouse_button==1 && mouse_released==0)
{
reset_indexs_confirmation();
index_wizard_do_reload_from_disk=1;
index_ask_confirm=1;
}
}

cancelit.DrawOutline(CouleurLigne);

petitchiffre.Print("Reload from disk",xb+90,yb+400);
////////////////////FAIRE L ACTION DEMANDEE////////////////////////////////////
Rect doit(Vec2D((xb+285),(yb+380)), Vec2D( 110,30));
doit.SetRoundness(15);
doit.SetLineWidth(epaisseur_ligne_fader);

if(window_focus_id==W_WIZARD && mouse_x>xb+285 && mouse_x<xb+395 && mouse_y>yb+380 && mouse_y<yb+410 )
{
doit.Draw(CouleurFond.WithAlpha(0.5));
if(mouse_button==1 && mouse_released==0)
{
reset_indexs_confirmation();
switch(index_wizard_ch_mode)
{
case 0:
index_do_wizard_mem=1;
break;
case 1:
index_do_wizard_ch=1;
break;
default: break;
}
index_ask_confirm=1;

}
}
doit.DrawOutline(CouleurLigne);

petitchiffre.Print("DO IT !",xb+320,yb+400);



return(0);
}
