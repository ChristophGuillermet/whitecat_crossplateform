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

* \file patch_core.cpp
* \brief {DMX patch core}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonction Core pour le patch dmx
*
*   Core fonction for the dmx patch
*
**/

int do_curve_affectation()
{
for(int k=0;k<513;k++)
{
if(Dimmers_selected[k]==1)
{curves[k]=curve_selected;}
}
return(0);
}

int load_curve_in_temp_curve()
{
index_curve_spline_level=the_curve_spline_level[curve_selected];   //pixels de l editeur    le float est recalculé dans la boucle
return(0);
}

int check_dimmer_minus_override()
{
if(index_patch_overide==1)
{
for(int ck=1;ck<513;ck++)
{
if(Dimmers_selected[ck]==1)
        {
        if (ck>1)
        {
        Dimmers_selected[ck]=0;
        Dimmers_selected[ck-1]=1;
        patch_overide[ck]=0;
        patch_overide[ck-1]=1;
        }
        break;

}
}
}
 return(0);
}

int check_dimmer_plus_override()
{
if(index_patch_overide==1)
{
for(int ck=1;ck<513;ck++)
{
if(Dimmers_selected[ck]==1)
        {
        if (ck<513)
        {
        Dimmers_selected[ck]=0;
        Dimmers_selected[ck+1]=1;
        patch_overide[ck]=0;
        patch_overide[ck+1]=1;
        }
        break;
}
}
}

 return(0);
}



int do_logical_menu_curve(int XCurv, int YCurv)
{

if(mouse_x>(XCurv+30) && mouse_x<(XCurv+30+50) && mouse_y>(YCurv+10) && mouse_y<(YCurv+10+20))
{
index_enable_curve_editing=toggle(index_enable_curve_editing);
mouse_released=1;
}


for(int l=0;l<4;l++)
{
for (int curvenumber=0;curvenumber<4;curvenumber++)
{

if(mouse_x>(XCurv+20+(curvenumber*70)) && mouse_x<(XCurv+20+(curvenumber*70)+60) && mouse_y>(YCurv+370+(30*l)) && mouse_y<(YCurv+370+(30*l))+20)
{

  curve_selected=curvenumber+(l*4);

 //courbe droite
 if(index_reset_curve==1 && index_enable_curve_editing==1 && index_square_curve==0 && index_fluo_curve==0 && index_preheat_curve==0)
 {
 build_default_curve(curve_selected);
 index_reset_curve=0;
 mouse_released=1;
 }
 //courbe TV
 else if (index_square_curve==1 &&  index_enable_curve_editing==1 && index_reset_curve==0 && index_fluo_curve==0 && index_preheat_curve==0)
 {
 build_square_curve(curve_selected);
 index_square_curve=0;
  mouse_released=1;
 }
 //courbe preheat
 else if (index_preheat_curve==1 && index_enable_curve_editing==1 && index_square_curve==0 && index_reset_curve==0 && index_fluo_curve==0  )
 {
 build_preheat_curve(curve_selected);
 index_preheat_curve=0;
  mouse_released=1;
 }
 //courbe fluo
 else if (index_fluo_curve==1 && index_enable_curve_editing==1 && index_square_curve==0 && index_reset_curve==0 && index_preheat_curve==0)
 {
 build_fluo_curve(curve_selected);
 index_fluo_curve=0;
  mouse_released=1;
 }

else if(index_reset_curve==0 && index_square_curve==0 && index_fluo_curve==0 && index_preheat_curve==0 && mouse_released==0)//selection du curve
 {
 load_curve_in_temp_curve();
 mouse_released=1;
 }
}

}
}

// CHOIX PRESET DE CURVE///////////////////////////////////////////////////////////////////

for (int act=0;act<4;act++)
{
///ACTIONS
if(mouse_x>(XCurv+20+(act*70)) && mouse_x<(XCurv+20+(act*70)+60) && mouse_y>(YCurv+510) && mouse_y<(YCurv+510)+20)
{
switch(act)
{
case 0:
if(index_reset_curve==0){dessafect_index_curves();index_reset_curve=1; }
else if (index_reset_curve==1){index_reset_curve=0; }
break;
case 1:
if(index_square_curve==0){dessafect_index_curves();index_square_curve=1;}
else if (index_square_curve==1){index_square_curve=0; }
break;
case 2:
if(index_preheat_curve==0){dessafect_index_curves();index_preheat_curve=1; }
else if (index_preheat_curve==1){index_preheat_curve=0; }
break;
case 3:
if(index_fluo_curve==0){dessafect_index_curves();index_fluo_curve=1; }
else if (index_fluo_curve==1){index_fluo_curve=0; }
break;
default: break;
}
mouse_released=1;
}

}
/////////////////////AFFECTATION AUX DIMERS SELECTIONNES///////////////////////////

if(mouse_x>XCurv+65 && mouse_x<XCurv+65+200 && mouse_y>YCurv+560 && mouse_y<YCurv+560+30)
{
do_curve_affectation();
patch_unselect_all_dimmers();
sprintf(string_Last_Order,">>Affected Curve  %d to Dimmer", curve_selected);
mouse_released=1;
}

return(0);
}



int do_logical_PatchBox(int XChan, int YChan, float scroll_chan)
{

//scroll
if(mouse_x>=XChan+340 && mouse_x<=XChan+430 && mouse_y>YChan+50 && mouse_y<YChan+250)
{
scroller_patch=mouse_y-(YChan+50);
}


for (int o=0;o<9;o++)
{

 if(mouse_x>XChan+345 && mouse_x<XChan+435 && mouse_y>YChan+290+(o*30) &&  mouse_y<YChan+310+(o*30)  )
 {
switch(o)
{
 case 0:
 patch_unselect_all_dimmers();
 break;
 case 1:
 index_affect_patch=toggle(index_affect_patch);
 break;
 case 2:
 patch_select_all_dimmers();
 break;
 case 3:
 index_do_clear_patch=1;
 index_ask_confirm=1;
 break;
 case 4:
 index_do_default_patch=1;
 index_ask_confirm=1;
 break;
 case 5:
 index_menu_curve=toggle(index_menu_curve);
 break;
 case 6:
 index_patch_overide=toggle(index_patch_overide);
 reset_check_grada_overide_dimmers();
 break;
 case 7:
 index_build_patch_from_plot=toggle(index_build_patch_from_plot);
 break;
 case 8:
 index_show_first_dim=toggle(index_show_first_dim);
 break;
 default:
 break;
}
 mouse_released=1;
}

}


int maxchan_per_ligne=7;
int grad=0;
for (int l=0;l<86;l++)
{
if(l==85){maxchan_per_ligne=3;} //derniere ligne à 512

for (int c=1; c<maxchan_per_ligne;c++)
{
//over dimmer
if(mouse_x>(XChan + (45*c)-10) && mouse_x<(XChan + (45*c)+35) && mouse_y>YChan+50 && mouse_y>(YChan+90+(l*60) - (int)(scroller_patch* scroll_chan)) && mouse_y<(YChan+90+(l*60)+40 - (int)(scroller_patch* scroll_chan)))
{
grad=c+(l*6);
if(Dimmers_selected[grad]==0)
{
Dimmers_selected[grad]=1;
}
else if(Dimmers_selected[grad]==1)
{
Dimmers_selected[grad]=0;
}
if(index_affect_patch==1)//affectation manuelle à la souris
{
Patch[grad]=last_ch_selected;
sprintf(string_Last_Order,">> Dimmer %d affected to Channel %d",grad, last_ch_selected);
sprintf(string_monitor_patch,">> Dimmer %d affected to Channel %d",grad, last_ch_selected);
patch_unselect_all_dimmers();
for (int ci=1;ci<514;ci++)
{Selected_Channel[ci]=0;}
index_type=0;index_level_attribue=0;
index_affect_patch=0;
}
generate_channel_view_list_from_patched_circuits();
mouse_released=1;
}


}
}

return(0);
}
