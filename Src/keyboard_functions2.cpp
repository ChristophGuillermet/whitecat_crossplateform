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

* \file keyboard_functions2.cpp
* \brief {Core fonctions for keyboard entry}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions core pour gérer les entrées clavier dans whitecat
*
*   Core fonctions for keyboard input in whitecat
*
 **/

int generation_Tableau_noms_clavier_FR()
{
sprintf(list_keyname[0],"PGDN");
sprintf(list_keyname[1],"UP");
sprintf(list_keyname[2],"DOWN");
sprintf(list_keyname[3],"ENTER");
sprintf(list_keyname[4],"ENTER_PAD");
sprintf(list_keyname[5],"PLUS");
sprintf(list_keyname[6],"PLUS_PAD");
sprintf(list_keyname[7],"MINUS");
sprintf(list_keyname[8],"MINUS_PAD");
sprintf(list_keyname[9],"ESC");
sprintf(list_keyname[10],"TAB");

sprintf(list_keyname[11],"SPACE");
sprintf(list_keyname[12],"A");//Q
sprintf(list_keyname[13],"B");
sprintf(list_keyname[14],"C");
sprintf(list_keyname[15],"D");
sprintf(list_keyname[16],"E");
sprintf(list_keyname[17],"F");
sprintf(list_keyname[18],"G");
sprintf(list_keyname[19],"H");
sprintf(list_keyname[20],"I");
sprintf(list_keyname[21],"J");
sprintf(list_keyname[22],"K");
sprintf(list_keyname[23],"L");
sprintf(list_keyname[24],"N");
sprintf(list_keyname[25],"O");
sprintf(list_keyname[26],"Q");//A
sprintf(list_keyname[27],"R");
sprintf(list_keyname[28],"S");
sprintf(list_keyname[29],"T");
sprintf(list_keyname[30],"U");
sprintf(list_keyname[31],"V");
sprintf(list_keyname[32],"W");//Z
sprintf(list_keyname[33],"X");
sprintf(list_keyname[34],"Y");
sprintf(list_keyname[35],"Z");//w
sprintf(list_keyname[36],"LEFT");
sprintf(list_keyname[37],"RIGHT");
sprintf(list_keyname[38],"M");//semicolomn
sprintf(list_keyname[39],"P");
return(0);
}



///////////////////////////////////////////////////////////////////////////////

int check_channel_minus()
{
int vv=0;
int circ=0;
int prevcirc=0;
switch (ClassicalChannelView)
{
case 0: //VIEWS
for(int v=0;v<nbre_de_vues_circuits; v++)
{
if(Channel_View_MODE[v]==1 && check_presence_of_any_channel_in_A_view(v)==1)
{
vv=v;
break;
}
}


for(int ck=channel_number_in_View[vv];ck>=0;ck--)
{
circ=Channel_View_ROUTING[vv][ck];
    if(Selected_Channel[circ]==1)
    {
    bufferSaisie[circ]=0;
    Selected_Channel[circ]=0;
    if(ck>0)
    {
    prevcirc=Channel_View_ROUTING[vv][ck-1];
    }
    else
    {
    bool gotit=0;
    for(int i=vv-1;i>0;i--)
    {
    if(Channel_View_MODE[i]==1)
    {prevcirc= detect_last_activ_channel_in_activ_view(i);gotit=1;break;}
    if(gotit==1){break;}
    }
    }
    if(prevcirc==0){prevcirc=circ;}
    Selected_Channel[prevcirc]=1;
    bufferSaisie[prevcirc]=check_channel_level;
    last_ch_selected=prevcirc;
    break;
    }

        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==prevcirc){Dimmers_selected[dop]=1;}
        }
        }


}




add_channel_selection_to_layers_plot();

break;
case 1:
for(int ck=1;ck<513;ck++)
    {
    if(Selected_Channel[ck]==1 && ck>1)
    {
    bufferSaisie[ck]=0;
    Selected_Channel[ck]=0;

    Selected_Channel[ck-1]=1;
    bufferSaisie[ck-1]=check_channel_level;

        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==(ck-1)){Dimmers_selected[dop]=1;}
        }
        }
        last_ch_selected=ck-1;
    break;
    }
    }
add_channel_selection_to_layers_plot();
break;
default: break;
}


return(0);
}


int check_channel_plus()
{
int vv=0;
int circ=0;
int nextcirc=0;
switch (ClassicalChannelView)
{
case 0: //VIEWS
for(int v=0;v<nbre_de_vues_circuits; v++)
{
if(Channel_View_MODE[v]==1 && check_presence_of_any_channel_in_A_view(v)==1)
{
vv=v;
break;
}
}


for(int ck=0;ck<=channel_number_in_View[vv];ck++)
{
circ=Channel_View_ROUTING[vv][ck];
    if(Selected_Channel[circ]==1)
    {
    bufferSaisie[circ]=0;
    Selected_Channel[circ]=0;
    if(ck+1!=channel_number_in_View[vv])
    {
    nextcirc=Channel_View_ROUTING[vv][ck+1];
    }
    else
   {
    bool gotit=0;
    for(int i=vv+1;i<nbre_de_vues_circuits;i++)
    {
    if(Channel_View_MODE[i]==1)
    {nextcirc= Channel_View_ROUTING[i][0];
    gotit=1;
    break;}
    if(gotit==1){break;}
    }
    }

    if(nextcirc==0){nextcirc=circ;}
    Selected_Channel[nextcirc]=1;
    bufferSaisie[nextcirc]=check_channel_level;
    last_ch_selected=nextcirc;
    break;
    }



        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==nextcirc){Dimmers_selected[dop]=1;}
        }
        }


}




add_channel_selection_to_layers_plot();
break;
case 1:
    for(int ck=1;ck<512;ck++)
    {
    if(Selected_Channel[ck]==1)
    {
    bufferSaisie[ck]=0;
    Selected_Channel[ck]=0;

    Selected_Channel[ck+1]=1;
    bufferSaisie[ck+1]=check_channel_level;

        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==(ck+1)){Dimmers_selected[dop]=1;}
        }
        }
        last_ch_selected=ck+1;
    break;
    }
    }

add_channel_selection_to_layers_plot();
break;
default: break;
}
return(0);
}


int select_channel_minus()
{
int vv=0;
int circ=0;
int prevcirc=0;
switch (ClassicalChannelView)
{
case 0: //VIEWS
for(int v=0;v<nbre_de_vues_circuits; v++)
{
if(Channel_View_MODE[v]==1 && check_presence_of_any_channel_in_A_view(v)==1)
{
vv=v;
break;
}
}

for(int ck=channel_number_in_View[vv];ck>=0;ck--)
{
circ=Channel_View_ROUTING[vv][ck];
    if(Selected_Channel[circ]==1)
    {
    Selected_Channel[circ]=0;
    if(ck>0)
    {
    prevcirc=Channel_View_ROUTING[vv][ck-1];
    }
    else
    {
    bool gotit=0;
    for(int i=vv-1;i>0;i--)
    {
    if(Channel_View_MODE[i]==1)
    {prevcirc= detect_last_activ_channel_in_activ_view(i);gotit=1;break;}
    if(gotit==1){break;}
    }
    }
    if(prevcirc==0){prevcirc=circ;}
    Selected_Channel[prevcirc]=1;
    last_ch_selected=prevcirc;
    break;
    }


        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==prevcirc){Dimmers_selected[dop]=1;}
        }
        }


}




add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();

break;
case 1:
for(int ck=1;ck<513;ck++)
    {
    if(Selected_Channel[ck]==1 && ck>1)
    {
    Selected_Channel[ck]=0;

    Selected_Channel[ck-1]=1;

        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==(ck-1)){Dimmers_selected[dop]=1;}
        }
        }
        last_ch_selected=ck-1;
    break;
    }
    }
add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();
break;
default: break;
}

 return(0);
}

int select_channel_plus()
{

int vv=0;
int circ=0;
int nextcirc=0;
switch (ClassicalChannelView)
{
case 0: //VIEWS
for(int v=0;v<nbre_de_vues_circuits; v++)
{
if(Channel_View_MODE[v]==1 && check_presence_of_any_channel_in_A_view(v)==1)
{
vv=v;
break;
}
}


for(int ck=0;ck<=channel_number_in_View[vv];ck++)
{
circ=Channel_View_ROUTING[vv][ck];
    if(Selected_Channel[circ]==1)
    {
    Selected_Channel[circ]=0;
    if(ck+1!=channel_number_in_View[vv])
    {
    nextcirc=Channel_View_ROUTING[vv][ck+1];
    }
    else
   {
    bool gotit=0;
    for(int i=vv+1;i<nbre_de_vues_circuits;i++)
    {
    if(Channel_View_MODE[i]==1)
    {nextcirc= Channel_View_ROUTING[i][0];
    gotit=1;
    break;}
    if(gotit==1){break;}
    }
    }

    if(nextcirc==0){nextcirc=circ;}
    Selected_Channel[nextcirc]=1;
    last_ch_selected=nextcirc;
    break;
    }

        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==nextcirc){Dimmers_selected[dop]=1;}
        }
        }


}




add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();
break;
case 1:
    for(int ck=1;ck<512;ck++)
    {
    if(Selected_Channel[ck]==1)
    {
    Selected_Channel[ck]=0;

    Selected_Channel[ck+1]=1;

        if(index_patch_window==1)
        {
        patch_unselect_all_dimmers();
        for(int dop=0;dop<513;dop++)
        {
        if(Patch[dop]==(ck+1)){Dimmers_selected[dop]=1;}
        }
        }
        last_ch_selected=ck+1;
    break;
    }
    }

add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();
break;
default: break;
}
return(0);
}

////////////////////////////////////Fonctions clavier déplacées en fonction indépendantes pour mapping/////////////////////////
int key_switch_window_up()
{
//solo des fenetres
if (key_shifts & KB_CTRL_FLAG || index_false_control==1) //appel une par une

{
pos_focus_window=window_focus_id;
substract_a_window(pos_focus_window);
if(pos_focus_window<900){pos_focus_window=899;}
pos_focus_window++;
if(pos_focus_window>max_window_identity_is){pos_focus_window=900;}
add_a_window(pos_focus_window);
}

else//passage dune fenetre à l autre
{
index_to_navigate_between_window++;
nbre_fenetre_actives=check_nbre_opened_windows();
if(index_to_navigate_between_window>=nbre_fenetre_actives+1){index_to_navigate_between_window=0;}
if(window_opened[index_to_navigate_between_window]>0)
{
window_bring_to_front(window_opened[index_to_navigate_between_window]);
}
else {window_bring_to_front(window_opened[0]);   }
}
 return(0);
}
int key_switch_window_down()
{
//solo des fenetres
if (key_shifts & KB_CTRL_FLAG || index_false_control==1) //appel une par une

{
pos_focus_window=window_focus_id;
substract_a_window(pos_focus_window);
pos_focus_window--;
if(pos_focus_window<900){pos_focus_window=max_window_identity_is;}
if(pos_focus_window>max_window_identity_is){pos_focus_window=900;}
add_a_window(pos_focus_window);
}

else//passage dune fenetre à l autre
{
index_to_navigate_between_window--;
nbre_fenetre_actives=check_nbre_opened_windows();
if(index_to_navigate_between_window<1){index_to_navigate_between_window=nbre_fenetre_actives+1;}
window_bring_to_front(window_opened[index_to_navigate_between_window]);
}
 return(0);
}
////////////////////////////////////////////////////////////////////////////////
int key_affectation()
{
if ((key_shifts & KB_SHIFT_FLAG  || index_false_shift==1) && index_patch_window==1)
{
if(numeric_postext>0)//attribution directe
{
iddim=atoi(numeric);
if(iddim<513 && iddim!=0)
{
Dimmers_selected[iddim]=1;
}
last_dim_selected=iddim;
reset_numeric_entry();
numeric_postext=0;
}

for(int i=0;i<513;i++)
{
if(Dimmers_selected[i]==1)
{
Patch[i]=last_ch_selected;

if(index_build_patch_from_plot==1)
{
for (int l=0;l<4;l++)
{
for(int u=1;u<=nbre_symbols_on_plot[l];u++)
{
//reaffectations frappes clavier
if  ( symbol_is_selected[l][u] == 1 &&  symbol_channel_is[l][u] == last_ch_selected  )
     {symbol_dimmer_is[l][u]= iddim;}
}
}
}

}
}



generate_channel_view_list_from_patched_circuits();
if(index_patch_affect_is_done==1)//reset de ma string de control
{
strcpy(string_monitor_patch,"");
index_patch_affect_is_done=0;
}



char tmp_str_ch[4];
sprintf(tmp_str_ch,"%d",last_ch_selected);
strcat(string_monitor_patch," To Ch:");
strcat(string_monitor_patch,tmp_str_ch);
index_patch_affect_is_done=1;
patch_unselect_all_dimmers();
for (int ci=1;ci<514;ci++)
{Selected_Channel[ci]=0;}
last_ch_selected=0;
}
else if (key_shifts & KB_CTRL_FLAG || index_false_control==1)
{
sprintf(string_Last_Order,">> Setted Time");
read_time_string_entry();
}

else{
if(index_ask_confirm==0)
{
if(index_type==0)
{

//affectation d un niveau a la selection
bool detect_selectch_on=0;
for(int chk_ch=1;chk_ch<514;chk_ch++)
{
if (Selected_Channel[chk_ch]==1){detect_selectch_on=1;}
}
if(detect_selectch_on==1)
{
int chlevelis=0;
if(dmx_view==0)
{
if(atof(numeric)>0)
{
chlevelis=(int)((atof(numeric) *2.55) +1);// + 1 pour arrondir le pourcentage lors de la conversion % -> dmx
}
else {chlevelis=0;}
}
else if (dmx_view==1)
{chlevelis= atol(numeric);}

if(chlevelis>255){chlevelis=255;}
if(chlevelis<0){chlevelis=0;}

 for (int ci=1;ci<514;ci++)
 {
 switch(index_do_hipass)
 {
 case 0://normal
 if(Selected_Channel[ci]==1 && index_blind==0)    {bufferSaisie[ci]=chlevelis;}
 else if(Selected_Channel[ci]==1  && index_blind==1)    {bufferBlind[ci]=chlevelis;}
 break;
 case 1://mode hipass faders
 if(Selected_Channel[ci]==1)
 {
  FaderManipulating=highest_level_comes_from_fader[ci]-1;
  if(DockTypeIs[FaderManipulating][dock_used_by_fader_is[FaderManipulating]]==0)//pas les contenus dynamiques, juste les circuits enregistrés on the fly
  {
   FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][ci]  =chlevelis;
  }

}
break;
default: break;
 }
 }
switch(dmx_view)
{
case 0:
sprintf(string_Last_Order,">> Selection AT %d",(int)(chlevelis/2.55));
break;
case 1:
sprintf(string_Last_Order,">> Selection AT %d", chlevelis);
break;
default: break;
}
reset_numeric_entry();
index_level_attribue=1;
}
}
}
else if(index_ask_confirm==1)
{

  operations_confirmation();

  reset_index_actions();
  reset_indexs_confirmation();

  substract_a_window(W_ASKCONFIRM);
  window_focus_id=previous_window_focus_id;

}
}
 return(0);
}
////////////////////////////////////////////////////////////////////////////////
int key_add_ch()
{
if ((key_shifts & KB_SHIFT_FLAG  || index_false_shift==1) && index_patch_window==1)
{
iddim=atol(numeric);

if(index_patch_affect_is_done==1)//reset de ma string de control
{
strcpy(string_monitor_patch,"");
index_patch_affect_is_done=0;
}

if( iddim>0 &&  iddim<513)
{
Dimmers_selected[iddim]=1;
last_dim_selected= iddim;
strcat(string_monitor_patch,"D.");
strncat(string_monitor_patch,numeric,numeric_postext);
strcat(string_monitor_patch,"+");
numeric_postext=0;
reset_numeric_entry();
set_patch_scroll( iddim);
}
}
else
{
if(index_type==0)
{

idchannel=atol(numeric);
if(index_level_attribue==1)//deselection si un niveau a ete attribue
             {
              for (int ci=1;ci<514;ci++)
             {Selected_Channel[ci]=0;}
             last_ch_selected=0;
             index_level_attribue=0;
             substract_channel_selection_to_layers_plot();
             }
if(idchannel>0 && idchannel<513)
{
switch (ClassicalChannelView)
{
case 0:
if(check_presence_of_a_channel_in_views(idchannel)==1)
{
Selected_Channel[idchannel]=1;
last_ch_selected=idchannel;
numeric_postext=0;
reset_numeric_entry();
set_channel_scroll(last_ch_selected);
add_channel_selection_to_layers_plot();
}
else if(check_presence_of_a_channel_in_views(idchannel)==0)
{
sprintf(string_Last_Order,"This Channel is not in an activ View");
numeric_postext=0;
reset_numeric_entry();
}
break;
case 1:
Selected_Channel[idchannel]=1;
last_ch_selected=idchannel;
numeric_postext=0;
reset_numeric_entry();
set_channel_scroll(last_ch_selected);
add_channel_selection_to_layers_plot();
break;
default: break;
}


}
}
}
 return(0);
}

int key_minus_ch()
{
if ((key_shifts & KB_SHIFT_FLAG  || index_false_shift==1) && index_patch_window==1)
{
iddim=atol(numeric);

if(iddim>0 && iddim<513)
{
Dimmers_selected[iddim]=0;
strcat(string_monitor_patch,"D.");
strncat(string_monitor_patch,numeric,numeric_postext);
strcat(string_monitor_patch,"-");
numeric_postext=0;
reset_numeric_entry();
set_patch_scroll(iddim);
}
}
else{
if(index_type==0)
{
idchannel=atol(numeric);
if(idchannel>0 && idchannel<513)
{
switch (ClassicalChannelView)
{
case 0:
if(check_presence_of_a_channel_in_views(idchannel)==1)
{
Selected_Channel[idchannel]=0;
//last_ch_selected=idchannel;
numeric_postext=0;
reset_numeric_entry();
set_channel_scroll(last_ch_selected);
substract_channel_selection_to_layers_plot();
}
else if(check_presence_of_a_channel_in_views(idchannel)==0)
{
sprintf(string_Last_Order,"This Channel is not in an activ View");
numeric_postext=0;
reset_numeric_entry();
}
break;
case 1:
Selected_Channel[idchannel]=0;
//last_ch_selected=idchannel;
numeric_postext=0;
reset_numeric_entry();
set_channel_scroll(last_ch_selected);
substract_channel_selection_to_layers_plot();
break;
default: break;
}


}
}
}
 return(0);
}

int key_up()
{

switch(index_do_hipass)
{
case 0://mode normal

if(index_blind==0)
{

                  for (int tc=1;tc<514;tc++)
                  {
                  if (Selected_Channel[tc]==1)
                  {


                               if(index_crossfading==0)
                               {

                               if(dmx_view==1)
                               {
                               if(bufferSaisie[tc]+default_step_level<=255) { bufferSaisie[tc]+=default_step_level; }
                               }
                               else if(dmx_view==0)
                               {
                               if( (bufferSaisie[tc]+(unsigned char)(default_step_level*2.55))<=255)
                               {
                               bufferPourcentStepdefaultlevel[tc]=(int) (((float)(bufferSaisie[tc]) /2.55))+default_step_level;
                               bufferSaisie[tc]=1+(unsigned char)(bufferPourcentStepdefaultlevel[tc]*2.55);
                               }
                               else if(bufferSaisie[tc]==254){bufferSaisie[tc]=255;}
                               }

                               }

                               else//index crossfading =1
                               {
                               channel_level_mofification_while_crossfade[tc]+=1;
                               }

            }
            }

}

else if (index_blind==1)//blind
{

               for (int tb=1;tb<514;tb++)
               {
               if (Selected_Channel[tb]==1)
               {

                               if(dmx_view==1)
                               {
                               if(bufferBlind[tb]+default_step_level<=255) {bufferBlind[tb]+=default_step_level; }
                               }

                               else if(dmx_view==0)
                               {
                               if((bufferBlind[tb]+(unsigned char)(default_step_level*2.55))<=255)
                               {
                               bufferPourcentStepdefaultlevel[tb]=(int) (((float)(bufferBlind[tb]) /2.55))+default_step_level;
                               bufferBlind[tb]=1+(unsigned char)(bufferPourcentStepdefaultlevel[tb]*2.55);
                               }
                               else if(bufferBlind[tb]==254){bufferBlind[tb]=255;}
                               }


                 }
                 }
}

break;

///////////////
case 1://mode de modification discret des faders
for (int i=1;i<513;i++)
{

 if(Selected_Channel[i]==1)
 {

  FaderManipulating=highest_level_comes_from_fader[i]-1;
  if(DockTypeIs[FaderManipulating][dock_used_by_fader_is[FaderManipulating]]==0)//pas les contenus dynamiques, juste les circuits enregistrés on the fly
  {
  if(dmx_view==0)
  {

     if( (FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  +(unsigned char)(default_step_level*2.55))<=255)
       {
         bufferPourcentStepdefaultlevel[i]=(int) (((float)(FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  ) /2.55))+default_step_level;
         FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  =1+(unsigned char)(bufferPourcentStepdefaultlevel[i]*2.55);
        }
        else if(FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  ==254){FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  =255;}
  }
  else if (dmx_view==1)
       {
       if(FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i] +default_step_level<=255) { FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i] +=default_step_level; }
       }
  }

 }
}

break;
default: break;
}
index_level_attribue=1;//pour déselection lors prochain circuit piqué

 return(0);
}

int key_down()
{
switch(index_do_hipass)
{
case 0://mode normal


if(index_blind==0)
{
                  for (int tc=1;tc<514;tc++)
                  {
                  if (Selected_Channel[tc]==1 )
                  {

                     if(index_crossfading==0)
                     {
                                             if(dmx_view==1)
                                             {
                                             if(bufferSaisie[tc]-default_step_level>=0) { bufferSaisie[tc]-=default_step_level; }
                                             }
                                             else if(dmx_view==0)
                                             {
                                             if((bufferSaisie[tc]-(unsigned char)(default_step_level*2.55))>=0)
                                             {
                                             bufferPourcentStepdefaultlevel[tc]=(int) (((float)(bufferSaisie[tc]) /2.55))-default_step_level;
                                             bufferSaisie[tc]=1+(unsigned char)(bufferPourcentStepdefaultlevel[tc]*2.55);
                                             if( bufferSaisie[tc]==1){ bufferSaisie[tc]=0;}
                                             }
                                             }
                     }
                      else//crossfading
                      {channel_level_mofification_while_crossfade[tc]-=1;}

                  }
                  }
}

else if ( index_blind==1)
{
                  for (int tb=1;tb<514;tb++)
                  {
                  if (Selected_Channel[tb]==1 )
                  {
                                              if(dmx_view==1)
                                              {
                                              if(bufferBlind[tb]-default_step_level>0) {bufferBlind[tb]-=default_step_level; }
                                              }

                                              else if(dmx_view==0)
                                              {
                                              if((bufferBlind[tb]-(unsigned char)(default_step_level*2.55))>=0)
                                              {
                                              bufferPourcentStepdefaultlevel[tb]=(int) (((float)(bufferBlind[tb]) /2.55))-default_step_level;
                                              bufferBlind[tb]=1+(unsigned char)(bufferPourcentStepdefaultlevel[tb]*2.55);
                                              if( bufferBlind[tb]==1){ bufferBlind[tb]=0;}
                                              }
                                              }
                  }
                  }
}

break;
case 1://mode de modification discret des faders

for (int i=1;i<513;i++)
{
 if(Selected_Channel[i]==1)
 {
  FaderManipulating=highest_level_comes_from_fader[i]-1;
  if(DockTypeIs[FaderManipulating][dock_used_by_fader_is[FaderManipulating]]==0)//pas les contenus dynamiques, juste les circuits enregistrés on the fly
  {
  if(dmx_view==0)
  {

     if( (FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]-(unsigned char)(default_step_level*2.55))>=0)
       {
         bufferPourcentStepdefaultlevel[i]=(int) (((float)(FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  ) /2.55))-default_step_level;
         FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  =1+(unsigned char)(bufferPourcentStepdefaultlevel[i]*2.55);
        }
        else if(FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  ==1){FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i]  =0;}
  }
  else if (dmx_view==1)
       {
       if(FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i] -default_step_level>=0) { FaderDockContains[FaderManipulating][dock_used_by_fader_is[FaderManipulating]][i] -=default_step_level; }
       }
  }
 }
}

break;
default: break;
}

index_level_attribue=1;//pour déselection lors prochain circuit piqué dominique guesdon 10 aout 2010
return(0);
}



int key_unselect_ch()
{
reset_numeric_entry();

//if ((key_shifts & KB_SHIFT_FLAG  || index_false_shift==1))
if(key[KEY_LSHIFT]|| index_false_shift==1)
{
             if( index_patch_window==1 && index_ask_confirm==0)
             {
             patch_unselect_all_dimmers();
             strcpy(string_monitor_patch,"");
             index_patch_affect_is_done=0;
             }
}


else
{

             for (int ci=1;ci<514;ci++)
             {Selected_Channel[ci]=0;}
             last_ch_selected=0;
             index_type=0;index_level_attribue=0;
             substract_channel_selection_to_layers_plot();
//18/06/2015 christoph
             if(window_focus_id==W_PLOT )
             {
                if(index_menus_lighting_plot==1) unselect_all_shapes();
                else if( index_menus_lighting_plot==2 || index_menus_lighting_plot==4)
                {
                    for(int i=0;i<4;i++)
                    {
                         reset_symbols_selected(i);
                    }
                }
              }


             if(index_ask_confirm==1)
             {
             reset_indexs_confirmation();
             reset_index_actions();
             substract_a_window(W_ASKCONFIRM);
             window_focus_id=previous_window_focus_id;
             add_a_window(window_focus_id);
             }
}

return(0);
}

int key_thruth()
{


            if ((key_shifts & KB_SHIFT_FLAG  || index_false_shift==1) && index_patch_window==1)
            {
            iddim=atol(numeric);
            int previous_dim_selected=last_dim_selected;
            last_dim_selected=iddim;
            if(iddim>0 && iddim<513)
            {
            if(previous_dim_selected<last_dim_selected)
            {
            for (int cit=previous_dim_selected;cit<=last_dim_selected;cit++)
            {
            Dimmers_selected[cit]=1;
            }
            }
            if (previous_dim_selected>last_dim_selected)
            {
             for (int cit=last_dim_selected;cit<=previous_dim_selected;cit++)
             {
                 Dimmers_selected[cit]=1;
             }
            }

            if(strcmp(string_monitor_patch,"")!=0)
            {
            char * pch;
            pch = strstr(string_monitor_patch, " TO ");
            if(pch!=0){strcpy(string_monitor_patch,"");}
            else
            {
            strcat(string_monitor_patch," TO ");
            strcat(string_monitor_patch,"D.");
            strncat(string_monitor_patch,numeric,numeric_postext);
            strcat(string_monitor_patch," ");
            numeric_postext=0;
            reset_numeric_entry();
            }
            }
            }
            }

           else //selection circuits
           {
           idchannel=atol(numeric);
           previous_ch_selected=last_ch_selected;
           if(idchannel>0 && idchannel<513)
           {
           switch (ClassicalChannelView)
           {
           case 0:
           if(check_presence_of_a_channel_in_views(idchannel)==1)
           {
           Selected_Channel[idchannel]=1;
           last_ch_selected=idchannel;
           numeric_postext=0;
           reset_numeric_entry();
           }
           else if(check_presence_of_a_channel_in_views(idchannel)==0)
           {
           sprintf(string_Last_Order,"This Channel is not in an activ View");
           numeric_postext=0;
           reset_numeric_entry();
           }

            if(previous_ch_selected<last_ch_selected)
            {
            for (int cit=previous_ch_selected;cit<=last_ch_selected;cit++)
            {if(check_presence_of_a_channel_in_views(cit)==1){Selected_Channel[cit]=1;}}
            }
            if (previous_ch_selected>last_ch_selected)
            {
             for (int cit=last_ch_selected;cit<=previous_ch_selected;cit++)  {if(check_presence_of_a_channel_in_views(cit)==1){Selected_Channel[cit]=1;}}
             }
           break;
           case 1:

           Selected_Channel[idchannel]=1;
           last_ch_selected=idchannel;
           numeric_postext=0;
           reset_numeric_entry();

            if(previous_ch_selected<last_ch_selected)
            {
            for (int cit=previous_ch_selected;cit<=last_ch_selected;cit++)
            {Selected_Channel[cit]=1;}
            }
            if (previous_ch_selected>last_ch_selected)
            {
             for (int cit=last_ch_selected;cit<=previous_ch_selected;cit++)  {Selected_Channel[cit]=1;}
             }
           break;
           default: break;
           }

           }

            add_channel_selection_to_layers_plot();
            sprintf(string_Last_Order,">> Selected from Ch %d to Ch %d", previous_ch_selected, last_ch_selected);
            }
 return(0);
}


int key_go()
{
   if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
             {
             do_go_back_function();
             int banger_back_is=Banger_Memoire[position_preset]-1;
             do_go_back_bang(banger_back_is);
             }
             else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
             {
             do_double_go_function();
             do_send_bang();
             }
             else
             {
             do_go_function();
             do_send_bang();
             }
 return(0);
}

int key_presetvideo(int preset)
{
 if( index_video_window==1) {tracking_dock_selected=preset;}//les banques de tracking cam
 return(0);
}

int key_roi(int roi)
{
 //les aires de tracking cam
if( index_video_window==1)
{
tracking_spaces_on_off[tracking_dock_selected][roi]=toggle( tracking_spaces_on_off[tracking_dock_selected][roi]);
}
return(0);
}
int key_full()
{
if ((key_shifts & KB_SHIFT_FLAG || index_false_shift==1) && index_patch_window==1)
{patch_to_default_selected();}
else
{
           reset_numeric_entry();
           for (int ci=1;ci<514;ci++)
           {
           if(Selected_Channel[ci]==1 && index_blind==0)    {bufferSaisie[ci]=255;}
           else if(Selected_Channel[ci]==1  && index_blind==1)    {bufferBlind[ci]=255;}
           }
sprintf(string_Last_Order,">> Selection AT FULL");
index_level_attribue=1;//pour déselection lors prochain circuit piqué
}
 return(0);
}

int key_time_in()
{
           if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
           {
            // delay IN
             if(numeric_postext==0)
             {
             if(index_type_of_time_to_affect[0]==0){index_type_of_time_to_affect[0]=1;}
             else if(index_type_of_time_to_affect[0]==1){index_type_of_time_to_affect[0]=0;}
             }
             else //entree directe pour le preset
            {affect_time_entry_to_mem(0,position_preset);}
           }
           else {
            // IN
            if(numeric_postext==0)
           {
            if(index_type_of_time_to_affect[1]==0){index_type_of_time_to_affect[1]=1;}
            else if(index_type_of_time_to_affect[1]==1){index_type_of_time_to_affect[1]=0;}
            }
            else //entree directe pour le preset
            {affect_time_entry_to_mem(1,position_preset);}
           }
 return(0);
}

int key_time_out()
{
 if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
           {
             //delay OUT
           if(numeric_postext==0)
           {
           if(index_type_of_time_to_affect[2]==0){index_type_of_time_to_affect[2]=1;}
           else if(index_type_of_time_to_affect[2]==1){index_type_of_time_to_affect[2]=0;}
           }
           else
           //entree directe pour le preset
            {affect_time_entry_to_mem(2,position_preset);}
           }
           else
           {
           //OUT
            if(numeric_postext==0)
           {
           if(index_type_of_time_to_affect[3]==0){index_type_of_time_to_affect[3]=1;}
           else if(index_type_of_time_to_affect[3]==1){index_type_of_time_to_affect[3]=0;}
            }
            else//entree directe pour le preset
            {affect_time_entry_to_mem(3,position_preset);}
           }

 return(0);
}

int key_time_in_out()
{
           if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
           {
            //IN OUT SEL
             if(numeric_postext==0)
           {
           if(index_type_of_time_to_affect[0]==0 || index_type_of_time_to_affect[2]==0 )//Delay selection
           {index_type_of_time_to_affect[0]=1; index_type_of_time_to_affect[2]=1; }//delay in et out sélectionnés
            else if(index_type_of_time_to_affect[0]==1 || index_type_of_time_to_affect[2]==1 )//Delays déselection 18/12/14 christoph
            {index_type_of_time_to_affect[0]=0; index_type_of_time_to_affect[2]=0; }//0=DIN 1=IN 2=DOUT 3=OUT
            }
            else//entree directe pour le preset
            {
            affect_time_entry_to_mem(0,position_preset);
            Times_Memoires[position_preset][2]=Times_Memoires[position_preset][0];
            }
           }
           else
           {
           //IN OUT SEL

            if(numeric_postext==0)
            {
            if(index_type_of_time_to_affect[1]==0 || index_type_of_time_to_affect[3]==0 )
            {index_type_of_time_to_affect[1]=1; index_type_of_time_to_affect[3]=1; }
            else if(index_type_of_time_to_affect[1]==1 || index_type_of_time_to_affect[3]==1 )
            {index_type_of_time_to_affect[1]=0; index_type_of_time_to_affect[3]=0; }
            }
           else //entree directe pour le preset
            {
            affect_time_entry_to_mem(1,position_preset);
            Times_Memoires[position_preset][3]=Times_Memoires[position_preset][1];
            }

           }
 return(0);
}

int key_at_zero()
{
 if ((key_shifts & KB_SHIFT_FLAG || index_false_shift==1) && index_patch_window==1)
           {patch_clear_selected();}
 else{
           reset_numeric_entry();
           for (int ci=1;ci<514;ci++)
           {
           if(Selected_Channel[ci]==1 && index_blind==0)    {bufferSaisie[ci]=0;}
           else if(Selected_Channel[ci]==1  && index_blind==1)    {bufferBlind[ci]=0;}
           }
           sprintf(string_Last_Order,">> Selection AT ZERO");
           index_level_attribue=1;//pour déselection lors prochain circuit piqué
 }
 return(0);
}

int key_select_inv()
{
switch (ClassicalChannelView)
{
case 0:

if(index_blind==0)
           {
           for (int ci=1;ci<514;ci++)
           {
           if( check_presence_of_a_channel_in_views(ci)==1)
           {
           if(bufferSequenciel[ci]>0 && Selected_Channel[ci]==1 )    {Selected_Channel[ci]=0;}
           else if (bufferSequenciel[ci]>0 && Selected_Channel[ci]==0)    {Selected_Channel[ci]=1;}
           }
           }
           }
           else if(index_blind==1)
           {
           for (int ci=1;ci<514;ci++)
           {
           if( check_presence_of_a_channel_in_views(ci)==1)
           {
           if(bufferBlind[ci]>0 && Selected_Channel[ci]==1)    {Selected_Channel[ci]=0;}
           else if (bufferBlind[ci]>0 && Selected_Channel[ci]==0)    {Selected_Channel[ci]=1;}
           }
           }
           }
           sprintf(string_Last_Order,">> Selected All lighting channels non selected ( INV )");


break;
case 1:
if(index_blind==0)
           {
           for (int ci=1;ci<514;ci++)
           {
           if(bufferSequenciel[ci]>0 && Selected_Channel[ci]==1)    {Selected_Channel[ci]=0;}
           else if (bufferSequenciel[ci]>0 && Selected_Channel[ci]==0)    {Selected_Channel[ci]=1;}
           }
           add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();
           }
           else if(index_blind==1)
           {
           for (int ci=1;ci<514;ci++)
           {
           if(bufferBlind[ci]>0 && Selected_Channel[ci]==1)    {Selected_Channel[ci]=0;}
           else if (bufferBlind[ci]>0 && Selected_Channel[ci]==0)    {Selected_Channel[ci]=1;}
           }
           }
           sprintf(string_Last_Order,">> Selected All lighting channels non selected ( INV )");
add_channel_selection_to_layers_plot();
break;
default: break;
}



 return(0);
}

int key_backward()
{
           if (key_shifts & KB_CTRL_FLAG || index_false_control==1)
           {
           if(index_go==0 && index_go_back==0 && index_pause==0)
           {
           position_onstage=mem_before_one;
           }
           else {index_go=0;index_pause=0; index_go_back=0;}
           refresh_mem_onstage(position_onstage);
           detect_mem_before_one();
           detect_mem_preset();
           refresh_mem_onpreset(position_preset);
           niveauX1=255; niveauX2=0;
           refresh_banger_wx();
           refresh_integrated_gridplayer1();
           reset_modified_levels_in_crossfade();
           }
           else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
           {
           index_go=0;index_pause=0; index_go_back=0;
           detect_mem_preset_previous();
           refresh_mem_onpreset(position_preset);
           niveauX2=0;
           }
           strcpy(string_time_left_is,"");
           someone_changed_in_sequences=1;//icat
return(0);
}

int key_forward()
{
  if (key_shifts & KB_CTRL_FLAG || index_false_control==1)
           {
           if(index_go==0 && index_go_back==0 && index_pause==0)
           {
           position_onstage=position_preset;
           }
            else {index_go=0;index_pause=0; index_go_back=0;}
           refresh_mem_onstage(position_onstage);
           detect_mem_before_one();
           detect_mem_preset();
           refresh_mem_onpreset(position_preset);
           niveauX1=255; niveauX2=0;
           refresh_banger_wx();
           refresh_integrated_gridplayer1();
           reset_modified_levels_in_crossfade();
           }
           else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
           {
           index_go=0;index_pause=0; index_go_back=0;
           detect_next_preset();
           refresh_mem_onpreset(position_preset);
           niveauX2=0;
           }
           strcpy(string_time_left_is,"");
           someone_changed_in_sequences=1;//icat
 return(0);
}


int key_select_all()
{
 if ((key_shifts & KB_SHIFT_FLAG  || index_false_shift==1)&& index_patch_window==1)
             {patch_select_all_dimmers();}
          else{
             if(index_blind==0)
             {
             for (int ci=1;ci<514;ci++)
             {
             if(bufferSequenciel[ci]==0)    {Selected_Channel[ci]=0;}
             else if (bufferSequenciel[ci]>0)    {Selected_Channel[ci]=1;}
             }
             }
             if(index_blind==1)
             {
             for (int ci=1;ci<514;ci++)
             {
             if(bufferBlind[ci]==0)    {Selected_Channel[ci]=0;}
             else if (bufferBlind[ci]>0)    {Selected_Channel[ci]=1;}
             }
             }
             add_channel_selection_to_layers_plot();
             sprintf(string_Last_Order,">> Selected All lighting channels ");
           }
 return(0);
}

int key_left()
{
       if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
       {
       check_channel_minus();
       add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();
       }
       else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
       {check_dimmer_minus_override();}
       else
       {select_channel_minus();}

 return(0);
}

int key_right()
{
if (key_shifts & KB_CTRL_FLAG || index_false_control==1)
       {
       check_channel_plus();
       add_channel_selection_to_layers_plot();substract_channel_selection_to_layers_plot();
       }
       else if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
       {check_dimmer_plus_override();}
        else
       {select_channel_plus(); }
 return(0);
}

int key_printscreen()
{
if (key_shifts & KB_SHIFT_FLAG || index_false_shift==1)
{
snapshot_windows();
close_all_windows();
}
else if (key_shifts & KB_CTRL_FLAG  || index_false_control==1)
{
recall_windows();
}
return(0);
}
