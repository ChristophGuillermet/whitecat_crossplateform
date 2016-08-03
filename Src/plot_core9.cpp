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

* \file plot_core9.cpp
* \brief {Plot Core fonctions}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions Core de la fenêtre plot
*
*   Core fonctions for the plot window
*
**/

#define drawStippleLine(x1,y1,x2,y2)  glBegin(GL_LINES);  glVertex2f ((x1),(y1)); glVertex2f ((x2),(y2)); glEnd();

int do_a_screen_capture()
{
Bitmap MySnapshot( SCREEN_W, SCREEN_H);
MySnapshot.CopyFromScreen( 0, 0 );
MySnapshot.Save( "mysnapshot.png" );
 return(0);
}

int do_plot_screen_capture(char capturename[25])
{
int thex=0;
int they=0;
int thesix=0;
int thesiy=0;

if(index_menus_lighting_plot==3)
{
  thex=x_plot;
  they=y_plot+position_plan_y;
  thesix=plot_window_x_size;
  thesiy=plot_window_y_size-position_plan_y;
}
else
{
  thex=x_plot+position_plan_x;
  they=y_plot+position_plan_y ;
  thesix=plot_window_x_size-position_plan_x;
  thesiy=plot_window_y_size-position_plan_y;
}

if (thesix> SCREEN_W){thesix=SCREEN_W;}
if(thesiy> SCREEN_H){thesiy=SCREEN_H;}

Bitmap MySnapshot(thesix , thesiy);
MySnapshot.CopyFromScreen( thex, they);
//si l image est plus loin que la carte graphique: bordure noire...

char tmmm[256];
//sprintf(tmmm,"import_export/plot/%s.png",capturename);
sprintf(tmmm,"import_export/plot/%s.jpg",capturename);
MySnapshot.Save( tmmm );


return(0);
}



int right_click_on_plot()
{
if(mouse_R_button==1 && mouse_R_released==0)
{

if(index_click_inside_plot==0 && index_move_plot_view_port==1    )
{
//prise de position
plot_original_mouse_x=mouse_x;
plot_original_mouse_y=mouse_y;
previous_plot_view_port_x=plot_view_port_x;
previous_plot_view_port_y=plot_view_port_y;
index_click_inside_plot=1;
}
else if (index_click_inside_plot==1 && index_move_plot_view_port==1 )
{
plot_facteur_move_x=mouse_x-plot_original_mouse_x;
plot_facteur_move_y=mouse_y-plot_original_mouse_y;
plot_view_port_x=previous_plot_view_port_x+plot_facteur_move_x;
plot_view_port_y=previous_plot_view_port_y+plot_facteur_move_y;
}

}
 return(0);
}


int plot_reset_list_gelat()
{


for(int num=0;num<3;num++)//3 slots de gelat par symbol
{
for(int t=0;t<1000;t++)
{
for(int s=0;s<127;s++)
{
tmp_gel_list[num][t][s]=0;
}
strcpy(Geo[t],"");
}
}

nbre_ligne_pour_gelats=0;
 return(0);
}




int plot_reset_list_appareils()
{
nbre_symbols_differents_sur_plot=0;
for (int i=0;i<nbre_symbol_per_layer;i++)
{
plot_list_appareils[i]=0;
plot_show_typ_appareil[i]=0;
}

plot_reset_list_gelat();
 return(0);
}



int plot_generate_gels_list()
{

plot_reset_list_gelat();
//sab 02/03/2014 unused var int pos_sym=0;
for(int c=0;c<4;c++)
{
if( show_calc_number[c]==1)
{
for(int s=1;s<=nbre_symbols_on_plot[c];s++)
{
for(int g=0;g<3;g++)//3 slots de gelat par symbol
{
//christoph 30/03/14 correction bug comptage gélatine
if( gelat[c][s][g]!=0 && gelat_family[c][s][g]<5) //si une gelat non zero et inférieure à la marque 0 à 4 pour ne pas déborder du tableau
{
tmp_gel_list[gelat_family[c][s][g]][(gelat[c][s][g])][(symbol_type[c][s])]++;
}
}
}
}
}

//creation de la liste

char GelTyp[12];
nbre_ligne_pour_gelats=0;
int index_geo=0;

for(int g=0;g<nbre_gelats_manufact;g++)
{
for(int t=1;t<1000;t++)//3 slots de gelat par symbol
{
for(int s=0;s<127;s++)
{
if(tmp_gel_list[g][t][s]!=0)
{
switch(g)
{
case 0:
     sprintf(GelTyp,"Lee");
break;
case 1:
     sprintf(GelTyp,"Rosco");
break;
case 2:
     sprintf(GelTyp,"GamColor");
break;
case 3:
     sprintf(GelTyp,"Apollo");
break;
default:
     sprintf(GelTyp," ");
break;
}
sprintf(Geo[index_geo]," %s %d x %d %s",GelTyp, t , tmp_gel_list[g][t][s],symbol_nickname[s]);
index_geo++;
}
}

}

}

 nbre_ligne_pour_gelats=index_geo;
 return(0);
}


int plot_generate_appareils_list()
{
plot_reset_list_appareils();
for(int l=0;l<4;l++)
{
if(show_calc_number[l]==1)
{
for (int i=0;i<=nbre_symbols_on_plot[l];i++)
{
plot_show_typ_appareil[(symbol_type[l][i])]=1;
plot_list_appareils[(symbol_type[l][i])]++;
}
}
}

//pour calcul nbre de colonnes dans plot
int addx=0;
for (int i=0;i<127;i++)
{
if( plot_show_typ_appareil[i]==1)
{
index_list_appareils_pour_la_legende[addx]=i;
addx++;
nbre_symbols_differents_sur_plot++;
}
}


plot_generate_gels_list();
 return(0);
}


int scan_planfolder()//plot
{
    struct al_ffblk f;
    bool isSomeone;
    int nrbe_de_fichiers=0;
    sprintf(rep,"%s\\plans\\",mondirectory);
    chdir(rep);

    if(!al_findfirst("*.*",&f,-1))
    {
            while(!al_findnext(&f))
            {
            //christoph 19/12/14
            int f_name_len = strlen(f.name);
            isSomeone=true; // we've found a directory!
            bool index_check_is_supported=0;
            //christoph 20/06/2015 unsigned int
            for(int a=0;a<f_name_len;a++)
           {
           if( f.name[a]=='.' && a<=f_name_len-3)
           {
                if(
                (f.name[a+1]=='j' &&  f.name[a+2]=='p' &&  f.name[a+3]=='g')
                || (f.name[a+1]=='b' &&  f.name[a+2]=='m' &&  f.name[a+3]=='p')
                || (f.name[a+1]=='t' &&  f.name[a+2]=='g' &&  f.name[a+3]=='a')
                || (f.name[a+1]=='p' &&  f.name[a+2]=='n' &&  f.name[a+3]=='g')
                || (f.name[a+1]=='J' &&  f.name[a+2]=='P' &&  f.name[a+3]=='G')
                || (f.name[a+1]=='B' &&  f.name[a+2]=='M' &&  f.name[a+3]=='P')
                || (f.name[a+1]=='T' &&  f.name[a+2]=='G' &&  f.name[a+3]=='A')
                || (f.name[a+1]=='P' &&  f.name[a+2]=='N' &&  f.name[a+3]=='G')
                )
           {index_check_is_supported=1; break;}
           }
           }


            if(isSomeone && nrbe_de_fichiers<127 && index_check_is_supported==1 )
            {
  		    sprintf(list_import_plans[nrbe_de_fichiers],f.name);
		    nrbe_de_fichiers++;
            }
            }

    }
    al_findclose(&f);
//REROLL
sprintf(rep,"%s\\",mondirectory);
chdir (rep);
return(0);
}


int add_channel_selection_to_layers_plot()
{
int tmp_ch=0;
for(int l=0;l<4;l++)
{
for(int i=1;i<=nbre_symbols_on_plot[l];i++)
{
tmp_ch=symbol_channel_is[l][i];
if(Selected_Channel[tmp_ch]==1)
{
symbol_is_selected[l][i]= 1;
}
}
}
return(0);
}


int change_shape_type(int shapetype)
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_type[i]=shapetype;}
}
return(0);
}

int group_ungroup_selected_shapes()
{
bool index_there_is_a_group=0;
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){if(shape_groups[i]!=0) index_there_is_a_group=1;break;}
}

switch(index_there_is_a_group)
{
case 0://creation group
number_of_shapes_groups++;
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_groups[i]=number_of_shapes_groups;}
}
break;
case 1://deselection group
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_groups[i]=0;}
}
number_of_shapes_groups--;
if(number_of_shapes_groups<0){number_of_shapes_groups=0;}
break;
default: break;
}
return(0);
}

int refresh_opening_angle(float openingangle)//arc case 9
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1 && shape_type[i]==9){shape_attributes[i][4]=openingangle;}
}
 return(0);
}

int affect_angle_to_shapes(float a)
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_attributes[i][1]=a*6.5;}
}

 return(0);
}

int affect_polygon_nbr_of_corners(int brches)
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_attributes[i][2]=(float)brches;}
}

 return(0);
}

int clear_shape_slot(int s)
{
shape_selected[s]=0;
shape_type[s]=0;
shape_attributes[s][0]=10.0;//size G
shape_attributes[s][1]=0.0;//angle rot
shape_attributes[s][2]=1.0;//size x
shape_attributes[s][3]=10.0;//size y
shape_attributes[s][4]=0.1;//opening angle
for(int i=0;i<4;i++)
{
shape_position[s][i]=0;//pour les lignes
}
strcpy(shape_legend_name[s],"");
shape_legend_name[s][24]='\0';
shape_relativ_position_legend_name[s][0]=0;
shape_relativ_position_legend_name[s][1]=0;
shape_color_type[s]=0;
shape_selected[s]=0;
shape_groups[s]=0;

 return(0);
}

int unselect_all_shapes()
{
 for(int i=0;i<nbre_symbol_per_layer-1;i++)
 {
  shape_selected[i]=0;
 }
 return(0);
}

int affect_size_to_shape(float size)
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_attributes[i][0]=general_shape_size_to_apply;}
}
return(0);
}

int affect_font_to_texts(int ftt )
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_attributes[i][2]=(float)ftt;}
}
return(0);
}

int affect_color_pattern_to_shape(int colorpattern)
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_color_type[i]=colorpattern;}
}
 return(0);
}

int affect_size_to_rect(float sizex, float sizey)
{

for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){shape_attributes[i][2]=sizex;shape_attributes[i][3]=sizey;}
}


 return(0);
}



int copy_shape_to_emply_slot(int empty, int filled)
{
shape_selected[empty]=snap_shape_selected[filled];
shape_type[empty]=snap_shape_type[filled];
shape_attributes[empty][0]=snap_shape_attributes[filled][0];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[empty][1]=snap_shape_attributes[filled][1];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[empty][2]=snap_shape_attributes[filled][2];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[empty][3]=snap_shape_attributes[filled][3];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[empty][4]=snap_shape_attributes[filled][4];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_position[empty][0]=snap_shape_position[filled][0];//pour les lignes
shape_position[empty][1]=snap_shape_position[filled][1];
shape_position[empty][2]=snap_shape_position[filled][2];
shape_position[empty][3]=snap_shape_position[filled][3];
sprintf(shape_legend_name[empty],snap_shape_legend_name[filled]);
shape_relativ_position_legend_name[empty][0]=snap_shape_relativ_position_legend_name[filled][0];
shape_relativ_position_legend_name[empty][1]=snap_shape_relativ_position_legend_name[filled][1];
shape_color_type[empty]=snap_shape_color_type[filled];
shape_groups[empty]=snap_shape_groups[filled];

return(0);
}






int rearrange_shapes()
{
for(int s=1; s<nbre_shapes_on_plot;s++)
{
if(snap_shape_selected[s]==1)
{
for(int sz=s;sz<=nbre_shapes_on_plot;sz++)
{
if(snap_shape_selected[sz]==0)
{
copy_shape_to_emply_slot(s,sz);
//break; enlevé pour permettre destruction sans virer un shape en dernier de la liste
}
}
}
}
return(0);
}

int snapshot_shapes()
{
for(int i=1;i<nbre_symbol_per_layer;i++)
{
snap_shape_selected[i]=shape_selected[i];
snap_shape_type[i]=shape_type[i];
snap_shape_attributes[i][0]=shape_attributes[i][0];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
snap_shape_attributes[i][1]=shape_attributes[i][1];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
snap_shape_attributes[i][2]=shape_attributes[i][2];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
snap_shape_attributes[i][3]=shape_attributes[i][3];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
snap_shape_attributes[i][4]=shape_attributes[i][4];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
snap_shape_position[i][0]=shape_position[i][0];//pour les lignes
snap_shape_position[i][1]=shape_position[i][1];
snap_shape_position[i][2]=shape_position[i][2];
snap_shape_position[i][3]=shape_position[i][3];
sprintf(snap_shape_legend_name[i],shape_legend_name[i]);
snap_shape_relativ_position_legend_name[i][0]=shape_relativ_position_legend_name[i][0];
snap_shape_relativ_position_legend_name[i][1]=shape_relativ_position_legend_name[i][1];
snap_shape_color_type[i]=shape_color_type[i];
snap_shape_groups[i]=shape_groups[i];
}

 return(0);
}

int delete_selected_shapes()
{
snapshot_shapes();
int nbre_shapes_to_delete=0;
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
nbre_shapes_to_delete++;
clear_shape_slot(i);
rearrange_shapes();
snap_shape_selected[i]=0;
}
}



nbre_shapes_on_plot-=nbre_shapes_to_delete;
if(nbre_shapes_on_plot<0){nbre_shapes_on_plot=0;}

return(0);
}

int refresh_view_shape_params(int sh)
{
shape_selected_type=shape_type[sh];
general_shape_size_to_apply=shape_attributes[sh][0];
angle_shape_selected=shape_attributes[sh][1]/6.5;
if(shape_type[sh]>=0 && shape_type[sh]<7)
{
color_pattern_selected=shape_color_type[sh];
}
else if (shape_type[sh]==7)
{
shape_rect_size_x=shape_attributes[sh][2];
shape_rect_size_y=shape_attributes[sh][3];
color_pattern_selected=shape_color_type[sh];
}
else if(shape_type[sh]==8)//cercle
{
color_pattern_selected=shape_color_type[sh];
}
else if(shape_type[sh]==9)//arc
{
opening_angle_selected=shape_attributes[sh][4];
color_pattern_selected=shape_color_type[sh];
}
else if(shape_type[sh]==10)//polygo
{
nbre_branches_polygon=(int)shape_attributes[sh][2];
color_pattern_selected=shape_color_type[sh];
}
sprintf(temp_shape_legend_name,shape_legend_name[sh]);
return(0);
}



int check_select_deselect_shape(int posx, int posy)
{

for(int i=nbre_shapes_on_plot+1;i>0 ;i--)
{
if(mouse_x>posx+shape_position[i][0]-10 && mouse_x<posx+shape_position[i][0]+10
&& mouse_y>posy+shape_position[i][1]-10 && mouse_y<posy+shape_position[i][1]+10)
{
shape_selected[i]=toggle(shape_selected[i]);handle_selected_for_line_editing=0;

if(shape_selected[i]==1)
{
index_last_shape_selected=i;
if(index_type==1)
{
sprintf(numeric,shape_legend_name[i]);
numeric_postext=24;
}
}
//groups
if(shape_groups[index_last_shape_selected]!=0)
{
for(int gr=0;gr<nbre_shapes_on_plot+1 ;gr++)
{
if(shape_groups[gr]==shape_groups[index_last_shape_selected])
{shape_selected[gr]=shape_selected[index_last_shape_selected];}
}
}
mouse_released=1;
refresh_view_shape_params(i);
break;
}
if(shape_type[i]<7 && mouse_x>posx+shape_position[i][2]-10 && mouse_x<posx+shape_position[i][2]+10
&& mouse_y>posy+shape_position[i][3]-10 && mouse_y<posy+shape_position[i][3]+10   )
{

handle_selected_for_line_editing=1;
shape_selected[i]=1;
editing_shape_line_number=i;
index_last_shape_selected=i;
break;
}
}


return(0);
}

int store_plot_position_of_shapes()
{
for(int i=1;i<= nbre_shapes_on_plot;i++)
{
stored_plot_shape_position[i][0]=shape_position[i][0];
stored_plot_shape_position[i][1]=shape_position[i][1];
stored_plot_shape_position[i][2]=shape_position[i][2];
stored_plot_shape_position[i][3]=shape_position[i][3];
}
 return(0);
}

int add_shape_to_plot(int shapetype)
{
if(nbre_shapes_on_plot<126)
{
nbre_shapes_on_plot++;
clear_shape_slot(nbre_shapes_on_plot);
unselect_all_shapes();

shape_position[nbre_shapes_on_plot][0]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x;
shape_position[nbre_shapes_on_plot][1]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;

shape_attributes[nbre_shapes_on_plot][0]=general_shape_size_to_apply;
shape_attributes[nbre_shapes_on_plot][1]= angle_shape_selected;

switch(shapetype)
{
case 0://curtain
shape_position[nbre_shapes_on_plot][2]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x+100;
shape_position[nbre_shapes_on_plot][3]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 1://line
shape_position[nbre_shapes_on_plot][2]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x+100;
shape_position[nbre_shapes_on_plot][3]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 2://stline
shape_position[nbre_shapes_on_plot][2]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x+100;
shape_position[nbre_shapes_on_plot][3]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 3://stline
shape_position[nbre_shapes_on_plot][2]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x+100;
shape_position[nbre_shapes_on_plot][3]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 4://stline
shape_position[nbre_shapes_on_plot][2]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x+100;
shape_position[nbre_shapes_on_plot][3]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 5://stline
shape_position[nbre_shapes_on_plot][2]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x+100;
shape_position[nbre_shapes_on_plot][3]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 6://stline
shape_position[nbre_shapes_on_plot][2]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x+100;
shape_position[nbre_shapes_on_plot][3]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 7://rectangle
shape_attributes[nbre_shapes_on_plot][2]= shape_rect_size_x;
shape_attributes[nbre_shapes_on_plot][3]= shape_rect_size_y;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 8://plot_draw_circle(int plotx1, int ploty1, float sizeshape,  float alphashape,   int colorpattern, bool isselected)
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 9://plot_draw_slice(int plotx1, int ploty1, float sizeshape, float opening_angle, float shaperotation, float alphashape,   int colorpattern, bool isselected)
shape_attributes[nbre_shapes_on_plot][4]=opening_angle_selected;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 10://polygon
shape_attributes[nbre_shapes_on_plot][2]=nbre_branches_polygon;
shape_color_type[nbre_shapes_on_plot]= color_pattern_selected;
break;
case 11://(int plotx,int ploty, float fontsize,int fonttype,  char *text,float alphatext, bool isselected)
shape_attributes[nbre_shapes_on_plot][2]=fonttype_selected;
sprintf(shape_legend_name[nbre_shapes_on_plot],temp_shape_legend_name);
shape_legend_name[nbre_shapes_on_plot][24]='\0';
break;
default:
break;
}

shape_type[nbre_shapes_on_plot]=shapetype;
shape_selected[nbre_shapes_on_plot]=1;
shape_groups[nbre_shapes_on_plot]=0;
index_last_shape_selected=nbre_shapes_on_plot;
sprintf(shape_legend_name[nbre_shapes_on_plot],temp_shape_legend_name);

}
 return(0);
}


int exchange_shape_position(int pos_source, int pos_dest)
{
copy_shape_to_emply_slot( pos_dest, pos_source);
copy_shape_to_emply_slot( pos_source, pos_dest);
return(0);
}

int position_down_selected_shapes()
{
snapshot_shapes();
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1 && i>1)
{
exchange_shape_position(i, i-1);
}
}
return(0);
}





int add_selected_shapes()
{
for(int i=1;i<nbre_symbol_per_layer;i++)
{
if( snap_shape_selected[i]==1 )
{
if( nbre_shapes_on_plot<nbre_symbol_per_layer-1)
{
copy_shape_to_emply_slot(nbre_shapes_on_plot,i);
nbre_shapes_on_plot++;
}
}
}

return(0);
}


int position_on_top_selected_shapes()
{
/*
delete_selected_shapes();
add_selected_shapes();
*/
snapshot_shapes();
for(int i=1;i<nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
exchange_shape_position(i,nbre_shapes_on_plot);
break;
}
}
return(0);
}


int  search_affect_first_dimmer_to_symbole(int calc, int symb)
{
for(int i=0;i<513;i++)
{
if(Patch[i]==symbol_channel_is[calc][symb])
{
symbol_dimmer_is[calc][symb]=i;
break;
}
}

return(0);
}

int reset_symbols_selected(int calc)
{
for (int i=0;i<nbre_symbol_per_layer;i++)
{
 symbol_is_selected[calc][i]=0;
}
 return(0);
}

int change_symbol_type(int calc, int typ)
{
for (int i=0;i<nbre_symbol_per_layer;i++)
{
 if(symbol_is_selected[calc][i]==1){symbol_type[calc][i]=typ;}
}

return(0);
}

int repatch_from_plot(int calc)
{
for(int i=1;i<=nbre_symbols_on_plot[calc];i++)
{
if(symbol_channel_is[calc][i]>0)
{
Patch[(symbol_dimmer_is[calc][i])]=symbol_channel_is[calc][i];
}
}
 generate_channel_view_list_from_patched_circuits();
return(0);
}

int store_plot_position_of_activ_calc(int calc)
{
for(int i=1;i<= nbre_symbols_on_plot[calc];i++)
{
stored_plot_position[i][0]=pos_symbol[calc][i][0];
stored_plot_position[i][1]=pos_symbol[calc][i][1];
}
return(0);
}



int clear_grouped_to_symbols(int calc, int s)
{

    for(int i=0;i<nbre_symbol_per_layer;i++)
    {
    if(symbol_is_linked_to[calc][i]==s)
    {
    symbol_is_linked_to[calc][i]=0;
    }
    }

return(0);
}



int clear_symbol_slot(int calc, int s)
{
symbol_type[calc][s]=999;//999 hors liste
symbol_is_selected[calc][s]=0;
angle_symbol[calc][s]=0.0;
pos_symbol[calc][s][0]=0;
pos_symbol[calc][s][1]=0;
stored_plot_position[s][0]=0;
stored_plot_position[s][1]=0;
symbol_channel_is[calc][s]=0;
symbol_dimmer_is[calc][s]=0;
gelat[calc][s][0]=0;
gelat[calc][s][1]=0;
gelat[calc][s][2]=0;
gelat_family[calc][s][0]=0;
gelat_family[calc][s][1]=0;
gelat_family[calc][s][2]=0;
symbol_is_linked_to[calc][s]=0;
for(int opt=0;opt<5;opt++)
{
relatif_plot_xy[calc][s][opt][0]=0;
relatif_plot_xy[calc][s][opt][1]=0;
}
for(int n=0;n<4;n++)
{
strcpy(symbol_note[calc][s][n],"");
}

clear_grouped_to_symbols(calc, s);
return(0);
}


int recount_symbols_on_calc(int calc)
{

int index=0;

for(int st=0;st<nbre_symbol_per_layer;st++)
{
if(symbol_type[calc][st]!=999)
{
index++;
}
}
nbre_symbols_on_plot[calc]=index;
 return(0);
}

int clear_calc(int calc)
{
for(int i=0;i<nbre_symbol_per_layer;i++)
{
clear_symbol_slot(calc,i);
}
recount_symbols_on_calc( calc);
plot_generate_appareils_list();
return(0);
}

int add_a_symbol_to_plot(int plot_calc_number_is)
{

nbre_symbols_on_plot[plot_calc_number_is]++;
clear_symbol_slot(plot_calc_number_is,nbre_symbols_on_plot[plot_calc_number_is]);
if(nbre_symbols_on_plot[plot_calc_number_is]>126){nbre_symbols_on_plot[plot_calc_number_is]=126;}
pos_symbol[plot_calc_number_is][nbre_symbols_on_plot[plot_calc_number_is]][0]=
((plot_window_x_size-position_plan_x)/2)-plot_view_port_x;
pos_symbol[plot_calc_number_is][nbre_symbols_on_plot[plot_calc_number_is]][1]=
((plot_window_y_size-position_plan_y)/2)-plot_view_port_y;
symbol_type[plot_calc_number_is][(nbre_symbols_on_plot[plot_calc_number_is])]=symbol_selected_type;
angle_symbol[plot_calc_number_is][(nbre_symbols_on_plot[plot_calc_number_is])]=angle_projo_selectionne;
reset_symbols_selected(view_plot_calc_number_is);
symbol_is_selected[plot_calc_number_is][(nbre_symbols_on_plot[plot_calc_number_is])]=1;
last_selected_symbol_is=nbre_symbols_on_plot[plot_calc_number_is];
plot_generate_appareils_list();
return(0);
}

int duplicate_selected_symbols(int calc)
{
int compteur=0;
int new_position=0;
//sab 02/03/2014 unused var int difference=0;// pour dub du link to

for(int i=0;i<=nbre_symbols_on_plot[calc];i++)
{
if( symbol_is_selected[calc][i]==1)
{
 compteur++;
 new_position=nbre_symbols_on_plot[calc]+compteur;
 if(new_position<127)
 {
 symbol_type[calc][new_position]=symbol_type[calc][i];
 symbol_is_selected[calc][new_position]=symbol_is_selected[calc][i];
 angle_symbol[calc][new_position]=angle_symbol[calc][i];
 pos_symbol[calc][new_position][0]=pos_symbol[calc][i][0]+10;
 pos_symbol[calc][new_position][1]=pos_symbol[calc][i][1]+10;
 symbol_channel_is[calc][new_position]=symbol_channel_is[calc][i];

 for(int opt=0;opt<3;opt++)//aout 2016 était 5
 {
 gelat[calc][new_position][opt]=gelat[calc][i][opt];
 gelat_family[calc][new_position][opt]=gelat_family[calc][i][opt];
 }
  for(int opt=0;opt<5;opt++)
 {
 relatif_plot_xy[calc][new_position][opt][0]=relatif_plot_xy[calc][i][opt][0];
 relatif_plot_xy[calc][new_position][opt][1]=relatif_plot_xy[calc][i][opt][1];
 }
 symbol_channel_is[calc][new_position]=symbol_channel_is[calc][i];
 symbol_dimmer_is[calc][new_position]=0;                       //PAS LES DIMMERS SINON SOUCI D AFFECTATION AVEC LE PATCH
 }
 else {break;}
 symbol_is_selected[calc][i]=0;
}
}
nbre_symbols_on_plot[calc]+=compteur;
if(nbre_symbols_on_plot[calc]>127){nbre_symbols_on_plot[calc]=127;}//rajout aout 2016
last_selected_symbol_is=nbre_symbols_on_plot[calc];
plot_generate_appareils_list();

return(0);
}

int snapshot_calc(int calc)
{
for(int s=1;s<=nbre_symbols_on_plot[calc];s++)
{
snapshot_symbol_type[s]=symbol_type[calc][s];
snapshot_symbol_is_selected[s]=symbol_is_selected[calc][s];
snapshot_angle_symbol[s]=angle_symbol[calc][s];
snapshot_pos_symbol[s][0]=pos_symbol[calc][s][0];
snapshot_pos_symbol[s][1]=pos_symbol[calc][s][1];
snapshot_symbol_channel_is[s]=symbol_channel_is[calc][s];
snapshot_symbol_dimmer_is[s]=symbol_dimmer_is[calc][s];
snapshot_symbol_is_linked_to[s]=symbol_is_linked_to[calc][s];
for(int n=0;n<4;n++)
{
sprintf(snapshot_symbol_note[s][n],symbol_note[calc][s][n]);
}
for(int ge=0;ge<3;ge++)
{
snapshot_gelat[s][ge]=gelat[calc][s][ge];
snapshot_gelat_family[s][ge]=gelat_family[calc][s][ge];
}
for(int opt=0;opt<5;opt++)
{
snapshot_relatif_plot_xy[s][opt][0]=relatif_plot_xy[calc][s][opt][0];
snapshot_relatif_plot_xy[s][opt][1]=relatif_plot_xy[calc][s][opt][1];
}
}
return(0);
}


int copy_symbol_to_emply_slot(int calc, int empty, int filled)
{

symbol_type[calc][empty]=snapshot_symbol_type[filled];
symbol_is_selected[calc][empty]=snapshot_symbol_is_selected[filled];
angle_symbol[calc][empty]=snapshot_angle_symbol[filled];
pos_symbol[calc][empty][0]=snapshot_pos_symbol[filled][0];
pos_symbol[calc][empty][1]=snapshot_pos_symbol[filled][1];
symbol_channel_is[calc][empty]=snapshot_symbol_channel_is[filled];
symbol_dimmer_is[calc][empty]=snapshot_symbol_dimmer_is[filled];

//groups difference
if(snapshot_symbol_is_linked_to[filled]!=0)
{
symbol_is_linked_to[calc][empty]=snapshot_symbol_is_linked_to[filled]-(filled-empty);
}

for(int ge=0;ge<3;ge++)
{
gelat[calc][empty][ge]=snapshot_gelat[filled][ge];
gelat_family[calc][empty][ge]=snapshot_gelat_family[filled][ge];
}
for(int opt=0;opt<5;opt++)
{
relatif_plot_xy[calc][empty][opt][0]=snapshot_relatif_plot_xy[filled][opt][0];
relatif_plot_xy[calc][empty][opt][1]=snapshot_relatif_plot_xy[filled][opt][1];
}
symbol_channel_is[calc][empty]=snapshot_symbol_channel_is[filled];
for(int n=0;n<4;n++)
{
sprintf(symbol_note[calc][empty][n],snapshot_symbol_note[filled][n]);
}
return(0);
}




int reorder_plan(int the_calc)
{
for(int s=1;s<=nbre_symbols_on_plot[the_calc];s++)
{
//sab 02/03/2014 unused var int index_to_fill=0;
if(symbol_type[the_calc][s]==999)
{
for(int yu=s;yu<=nbre_symbols_on_plot[the_calc];yu++)
{
if(symbol_type[the_calc][yu]!=999)
{
copy_symbol_to_emply_slot(the_calc,s,yu);//(int calc, int empty, int filled)
clear_symbol_slot(the_calc,yu);
break;
}

}
}

}

 return(0);
}

int delete_selected_symbols(int calc)
{


for(int i=1;i<=nbre_symbols_on_plot[calc];i++)//garder 0 pour nettoyage des symboles et output gelats ok
{
if(symbol_is_selected[calc][i]==1)
{
clear_symbol_slot(calc,i);
if(index_build_patch_from_plot==1)
{
Patch[(symbol_dimmer_is[calc][i])]=0;
}
}
}

reorder_plan(calc);
recount_symbols_on_calc(calc);
last_selected_symbol_is=0;

return(0);
}

int add_selected_symbols_to_calc(int calc)
{
for(int i=1;i<=nbre_symbol_per_layer;i++)
{
if( snapshot_symbol_is_selected[i]==1 )
{
if( nbre_symbols_on_plot[calc]<nbre_symbol_per_layer-1)
{
nbre_symbols_on_plot[calc]++;
copy_symbol_to_emply_slot(calc,nbre_symbols_on_plot[calc],i);
}
}
}
plot_generate_appareils_list();
return(0);
}


int exchange_symbol_position(int calc,int pos_source, int pos_dest)
{


int source_link_to=snapshot_symbol_is_linked_to[pos_source];
int dest_link_to=snapshot_symbol_is_linked_to[pos_dest];

copy_symbol_to_emply_slot(calc, pos_dest, pos_source);//(int calc, int empty, int filled)
copy_symbol_to_emply_slot(calc, pos_source, pos_dest);

symbol_is_linked_to[calc][pos_dest]=source_link_to;
symbol_is_linked_to[calc][pos_source]=dest_link_to;



snapshot_calc(calc);
return(0);
}

int send_symbols_from_calc_to_calc(int calc_source,int calc_dest)
{
snapshot_calc(calc_source);

delete_selected_symbols(calc_source);
add_selected_symbols_to_calc(calc_dest);

reset_symbols_selected(calc_dest);
return(0);
}

int position_down_selected_symbols(int calc)
{
snapshot_calc(calc);
for(int i=1;i<nbre_symbol_per_layer;i++)
{
if(symbol_is_selected[calc][i]==1 && i>1)
{
exchange_symbol_position(calc,i, i-1);
symbol_is_linked_to[calc][i]=0;
}
}

return(0);
}


int position_on_top(int calc)
{
snapshot_calc(calc);
for(int i=1;i<=nbre_symbol_per_layer;i++)
{
if(symbol_is_selected[calc][i]==1 && i<=nbre_symbols_on_plot[calc])
{
exchange_symbol_position(calc,i,nbre_symbols_on_plot[calc]);
symbol_is_linked_to[calc][i]=0;
}
}
return(0);
}

int group_symbols_selected(int calc)
{

bool do_ungroup=0;
 for(int i=1;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
if( symbol_is_linked_to[calc][i]>0){ do_ungroup=1;break;}
}
}

 if(do_ungroup==1)
 {
 for(int i=1;i<= nbre_symbols_on_plot[calc];i++)
 {
 if(symbol_is_selected[calc][i]==1)
 {
 symbol_is_linked_to[calc][i]=0;
 }
 }
 }

else
{
int leading_symbol=0;
int leading_channel=0;// le premier symbole trouvé est celui qui permet le groupe
for(int i=1;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1 && symbol_channel_is[calc][i]>0)
{
if(leading_channel==0){
leading_symbol=i;
leading_channel=symbol_channel_is[calc][i];
}
break;
}
}
//affectation du group
for(int i=leading_symbol+1;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1 && symbol_channel_is[calc][i]==leading_channel)
{
symbol_is_linked_to[calc][i]=leading_symbol;
}
}
//fin groupage
}
return(0);
}


int duplicate_selected_shapes()
{

int compteur=0;
int new_position=0;
for(int i=0;i<=nbre_shapes_on_plot;i++)
{
if( shape_selected[i]==1)
{
 compteur++;
 new_position=nbre_shapes_on_plot+compteur;
 if(new_position<127)
 {
shape_selected[new_position]=shape_selected[i];
shape_type[new_position]=shape_type[i];
shape_attributes[new_position][0]=shape_attributes[i][0];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[new_position][1]=shape_attributes[i][1];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[new_position][2]=shape_attributes[i][2];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[new_position][3]=shape_attributes[i][3];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_attributes[new_position][4]=shape_attributes[i][4];//size angle et accessoires 0= general size 1= rotation 2 size x 3 size y 4 oepning angle
shape_position[new_position][0]=shape_position[i][0]+2;//pour les lignes
shape_position[new_position][1]=shape_position[i][1]+2;
shape_position[new_position][2]=shape_position[i][2]+2;
shape_position[new_position][3]=shape_position[i][3]+2;
sprintf(shape_legend_name[new_position],shape_legend_name[i]);
shape_legend_name[nbre_shapes_on_plot][24]='\0';
shape_relativ_position_legend_name[new_position][0]=shape_relativ_position_legend_name[i][0];
shape_relativ_position_legend_name[new_position][1]=shape_relativ_position_legend_name[i][1];
shape_color_type[new_position]=shape_color_type[i];
 }
 else {break;}
 shape_selected[i]=0;
}
}
nbre_shapes_on_plot+=compteur;
return(0);
}

int store_relativ_xy_position_of_activ_calc(int calc)
{
for(int i=1;i<nbre_symbol_per_layer;i++)
{
for (int t=0;t<5;t++)
{
temp_relatif_plot_xy_array[i][t][0]=relatif_plot_xy[calc][i][t][0];
temp_relatif_plot_xy_array[i][t][1]=relatif_plot_xy[calc][i][t][1];
}
}
return(0);
}

int store_relativ_xy_position_of_shape()
{
for(int i=1;i<nbre_shapes_on_plot;i++)
{
temp_shape_relativ_position_legend_name[i][0]=shape_relativ_position_legend_name[i][0];
temp_shape_relativ_position_legend_name[i][1]=shape_relativ_position_legend_name[i][1];
}
return(0);
}



int check_select_deselect_symbol(int posx, int posy)
{
int previous_calc_selection=view_plot_calc_number_is;
int is_manipulated=0;
int second_round=0;
for(int calc=0;calc<4;calc++)
{
if(show_calc_number[calc]==1)
{
for(int i=nbre_symbols_on_plot[calc]+1;i>0 ;i--)
{
if(mouse_x>posx+pos_symbol[calc][i][0]-10 && mouse_x<posx+pos_symbol[calc][i][0]+10
&& mouse_y>posy+pos_symbol[calc][i][1]-10 && mouse_y<posy+pos_symbol[calc][i][1]+10)
{
symbol_is_selected[calc][i]=toggle(symbol_is_selected[calc][i]);
view_plot_calc_number_is=calc;
is_manipulated=i;
if(symbol_is_selected[calc][i]==1)
{
last_selected_symbol_is=i;
symbol_selected_type=symbol_type[calc][i];
last_ch_selected=symbol_channel_is[calc][i];
}

//selection déselection channels
if((symbol_channel_is[calc][i])!=0)
{
Selected_Channel[(symbol_channel_is[calc][i])]=symbol_is_selected[calc][i];
}
//check group
for(int gr=1;gr<=nbre_symbols_on_plot[calc] ;gr++)
{
if(symbol_channel_is[calc][gr]!=0 && symbol_channel_is[calc][gr]==symbol_channel_is[calc][is_manipulated] )//ismanipulated si déselection
{
if( symbol_is_linked_to[calc][gr]==is_manipulated || symbol_is_linked_to[calc][is_manipulated ]==gr )
{
symbol_is_selected[calc][gr]=symbol_is_selected[calc][is_manipulated];
second_round=gr;
}
//check other grouped
for (int g=1;g<=nbre_symbols_on_plot[calc];g++)
{
if(symbol_channel_is[calc][g]!=0 && symbol_channel_is[calc][g]==symbol_channel_is[calc][is_manipulated] &&  symbol_is_linked_to[calc][g]!=0 && ( symbol_is_linked_to[calc][g]==is_manipulated || symbol_is_linked_to[calc][g ]==second_round ) )
{symbol_is_selected[calc][g]=symbol_is_selected[calc][is_manipulated];}
}
}
}

mouse_released=1;
break;
}
}
}
}


if(view_plot_calc_number_is!=previous_calc_selection)
{reset_symbols_selected(previous_calc_selection);}



return(0);
}

int affect_angle_to_symbols(int plot_calc_number_is,float angle_is)
{
 for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[plot_calc_number_is][i]==1)
{
angle_symbol[view_plot_calc_number_is][i]= angle_is;
}
}
return(0);
}

int edit_symbol_name()
{
sprintf(symbol_nickname[symbol_selected_type],numeric);
reset_numeric_entry();numeric_postext=0;
if(index_text_auto_close==1){index_type=0;}
 return(0);
}


int edit_shape_name()
{
sprintf(temp_shape_legend_name,numeric);
temp_shape_legend_name[24]='\0';
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1){sprintf(shape_legend_name[i],temp_shape_legend_name);}
}
reset_numeric_entry();
numeric_postext=0;
if(index_text_auto_close==1){index_type=0;}
return(0);
}

int plot_align_x(int calc)
{
int the_value=9999;
for(int i=0;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
if(pos_symbol[calc][i][0]<the_value)
{
the_value=pos_symbol[calc][i][0];
}
}
}

for(int i=0;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
pos_symbol[calc][i][0]=the_value;
}
}

 return(0);
}

int plot_align_y(int calc)
{

int the_value=9999;
for(int i=0;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
if(pos_symbol[calc][i][1]<the_value)
{
the_value=pos_symbol[calc][i][1];
}
}
}

for(int i=0;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
pos_symbol[calc][i][1]=the_value;
}
}
 return(0);
}

int plot_ventilate_x(int calc)
{
//si souci de ventilation parce que les symboles pas les uns après les autres. il faudrait faire un tableau intermédiaire où stocker les données et redistribuer après
int the_highest_value=0;
int the_lowest_value=0;
int the_value=0;
int the_count=0;
int index_low_value=0;
int index_high_value=0;

for(int i=1;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
if(the_count==0)
{
the_highest_value=pos_symbol[calc][1][0];
the_lowest_value=pos_symbol[calc][1][0];
}
the_count++;
the_value=pos_symbol[calc][i][0];

if(the_value>= the_highest_value)
{the_highest_value=the_value;index_high_value=i;}
else if(the_value<=the_lowest_value)
{the_lowest_value=the_value;index_low_value=i;}
}
}
if(the_lowest_value>the_highest_value)
{
the_lowest_value=return_lowest(the_lowest_value,the_highest_value);
the_highest_value=return_highest(the_lowest_value,the_highest_value);
}

int the_frac=(int)((float)(the_highest_value-the_lowest_value)/(the_count));//debut fin = 1+1
the_count=0;

for(int i=0;i<=nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1 && i!=index_low_value && i!=index_high_value)
{
the_count++;
pos_symbol[calc][i][0]=(int)(the_lowest_value+(the_frac*the_count));
}
}


return(0);
}

int plot_ventilate_y(int calc)
{


int the_highest_value=0;
int the_lowest_value=0;
int the_value=0;
int the_count=0;
int index_low_value=0;
int index_high_value=0;

for(int i=1;i<= nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
if(the_count==0)
{
the_highest_value=pos_symbol[calc][1][1];
the_lowest_value=pos_symbol[calc][1][1];
}
the_count++;
the_value=pos_symbol[calc][i][1];

if(the_value>= the_highest_value)
{the_highest_value=the_value;index_high_value=i;}
else if(the_value<=the_lowest_value)
{the_lowest_value=the_value;index_low_value=i;}
}
}

if(the_lowest_value>the_highest_value)
{
the_lowest_value=return_lowest(the_lowest_value,the_highest_value);
the_highest_value=return_highest(the_lowest_value,the_highest_value);
}

int the_frac=(int)(((float)(the_highest_value-the_lowest_value))/(the_count));
the_count=0;
for(int i=0;i<=nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1 && i!=index_low_value && i!=index_high_value)
{
the_count++;
pos_symbol[calc][i][1]=(the_lowest_value+(the_frac*the_count));
}
}


 return(0);
}







int plot_shapes_align_x()
{
int the_value=9999;
for(int i=0;i<= nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
if(shape_position[i][0]<the_value)
{
the_value=shape_position[i][0];
}
}
}

int longueur_trait=0;
bool way_negativ=0;

for(int i=0;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
if(shape_type[i]<7)
{
if(shape_position[i][0]>shape_position[i][2])
{
longueur_trait=shape_position[i][0]-shape_position[i][2];way_negativ=1;
}
else
{longueur_trait=shape_position[i][2]-shape_position[i][0]; }
}

shape_position[i][0]=the_value;

if(shape_type[i]<7)
{
if(way_negativ==1)
{ shape_position[i][2]=shape_position[i][0]-longueur_trait;}
else {shape_position[i][2]=shape_position[i][0]+longueur_trait; }
}
}
}

 return(0);
}

int plot_shapes_align_y()
{

int the_value=9999;
for(int i=0;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
if(shape_position[i][1]<the_value)
{
the_value=shape_position[i][1];
}
}
}

int longueur_trait=0;
bool way_negativ=0;

for(int i=0;i<= nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{

if(shape_type[i]<7)
{
if(shape_position[i][1]>shape_position[i][3])
{
longueur_trait=shape_position[i][1]-shape_position[i][3];way_negativ=1;
}
else
{longueur_trait=shape_position[i][3]-shape_position[i][1]; }
}


shape_position[i][1]=the_value;

if(shape_type[i]<7)
{
if(way_negativ==1)
{ shape_position[i][3]=shape_position[i][1]-longueur_trait;}
else {shape_position[i][3]=shape_position[i][1]+longueur_trait; }
}



}
}
 return(0);
}

int plot_shapes_ventilate_x()
{

int the_highest_value=0;
int the_lowest_value=0;
int the_value=0;
int the_count=0;


for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
if(the_count==0)
{
the_highest_value=shape_position[1][0];
the_lowest_value=shape_position[1][0];
}
the_count++;


the_value=shape_position[i][0];

if(the_value>= the_highest_value)
{the_highest_value=the_value;}
else if(the_value<=the_lowest_value)
{the_lowest_value=the_value;}
}
}



int the_frac=(int)(((float)(the_highest_value-the_lowest_value))/the_count);
the_count=0;


int longueur_trait=0;
bool way_negativ=0;

for(int i=0;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
if(shape_type[i]<7)
{
if(shape_position[i][0]>shape_position[i][2])
{
longueur_trait=shape_position[i][0]-shape_position[i][2];way_negativ=1;
}
else
{longueur_trait=shape_position[i][2]-shape_position[i][0]; }
}


the_count++;
shape_position[i][0]=the_lowest_value+(the_frac*the_count);


if(shape_type[i]<7)
{
if(way_negativ==1)
{ shape_position[i][2]=shape_position[i][0]-longueur_trait;}
else {shape_position[i][2]=shape_position[i][0]+longueur_trait; }
}

}
}


return(0);
}



int plot_shapes_ventilate_y()
{
int the_highest_value=0;
int the_lowest_value=0;
int the_value=0;
int the_count=0;

int longueur_trait=0;
bool way_negativ=0;

for(int i=1;i<= nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{
if(the_count==0)
{
the_highest_value=shape_position[1][1];
the_lowest_value=shape_position[1][1];
}
the_count++;
the_value=shape_position[i][1];

if(the_value>= the_highest_value)
{the_highest_value=the_value;}
else if(the_value<=the_lowest_value)
{the_lowest_value=the_value;}
}
}

int the_frac=(int)(((float)(the_highest_value-the_lowest_value))/the_count);
the_count=0;
for(int i=0;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1)
{

if(shape_type[i]<7)
{
if(shape_position[i][1]>shape_position[i][3])
{
longueur_trait=shape_position[i][1]-shape_position[i][3];way_negativ=1;
}
else
{longueur_trait=shape_position[i][3]-shape_position[i][1]; }
}

the_count++;
shape_position[i][1]=the_lowest_value+(the_frac*the_count);


if(shape_type[i]<7)
{
if(way_negativ==1)
{ shape_position[i][3]=shape_position[i][1]-longueur_trait;}
else {shape_position[i][3]=shape_position[i][1]+longueur_trait; }
}



}
}


 return(0);
}




int logical_plot_symbol_list(int plotx, int ploty)
{


if(window_focus_id==W_PLOT && mouse_button==1 && mouse_released==0 && index_click_inside_relativ_xy==0)
{

//selection du symbol
if( mouse_x>plotx+12 && mouse_x<plotx+28)
{
 if(mouse_y>ploty+36 && mouse_y<ploty+50) //UP
 {
 if( Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1597,Midi_Faders_Affectation_Mode);
 }
 else
 {
 symbol_selected_type++;
 if(symbol_selected_type>max_symbol_type){symbol_selected_type=0;}
 if(index_edit_light_plot==1){change_symbol_type(view_plot_calc_number_is,symbol_selected_type);}
  }
   mouse_released=1;
 }
 else if(  mouse_y>ploty+69 && mouse_y<ploty+83) //DOWN
 {
 if(Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1598,Midi_Faders_Affectation_Mode);
 }
 else
 {
  symbol_selected_type--;
  if(symbol_selected_type<0){symbol_selected_type=max_symbol_type;}
  if(index_edit_light_plot==1){change_symbol_type(view_plot_calc_number_is,symbol_selected_type);}
 }
  mouse_released=1;
 }

}
//slider
if( mouse_x>=plotx+3 && mouse_x<=plotx+8 && mouse_y>=ploty+26 && mouse_y<ploty+30+70)
{
if(Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1599,Midi_Faders_Affectation_Mode);
 mouse_released=1;
 }
 else
 {
set_mouse_range(plotx+3,ploty+26 , plotx+8, ploty+30+70);//pour pas deborder
symbol_selected_type= 127-((mouse_y-(ploty+30))*2);
if(symbol_selected_type<0){symbol_selected_type=0;}
else if(symbol_selected_type>126){symbol_selected_type=126;}
}
}

//EDIT MODE SYMBOL
if(mouse_x>plotx+40 && mouse_x<plotx+40+105 && mouse_y>ploty+80 && mouse_y<ploty+80+20)
{
index_edit_symbol_plot=toggle(index_edit_symbol_plot);
mouse_released=1;
}
//ADD A SYMBOL TO PLAN
if(mouse_x>plotx+40 && mouse_x<plotx+40+80 && mouse_y>ploty+110 && mouse_y<ploty+110+20)
{
 if(Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1600,Midi_Faders_Affectation_Mode);
 }
 else
 {
 add_a_symbol_to_plot(view_plot_calc_number_is);
 }
 mouse_released=1;
}



//edition de la taille du symbol
if(index_edit_symbol_plot==1 )
{

if( mouse_x>=plotx+10 && mouse_x<=plotx+10+185 && mouse_y>ploty+5 && mouse_y<ploty+5+20 && index_type==1)
{
edit_symbol_name();
plot_generate_appareils_list();
mouse_released=1;
}
else if( mouse_x>=plotx+50 && mouse_x<=plotx+50+50+5 && mouse_y>ploty+40 && mouse_y<ploty+40+10)
{
global_symbol_size=((float)(mouse_x-(plotx+50)))/25;
if(global_symbol_size<0.1){global_symbol_size=0.1;}
if (global_symbol_size>2.0){global_symbol_size=2.0;}
}
else if( mouse_x>=plotx+50 && mouse_x<=plotx+50+50+5 && mouse_y>ploty+65 && mouse_y<ploty+65+10)
{
size_symbol[symbol_selected_type]=((float)(mouse_x-(plotx+50)))/50;
if(size_symbol[symbol_selected_type]<0.1){size_symbol[symbol_selected_type]=0.2;}
if (size_symbol[symbol_selected_type]>1.0){size_symbol[symbol_selected_type]=1.0;}
}
}


//select id
if(mouse_x>plotx+130 && mouse_x<plotx+130+65 && mouse_y>ploty+105 && mouse_y<ploty+105+28)
{
symbol_id_to_select=atoi(numeric);
if(symbol_id_to_select>nbre_symbols_on_plot[view_plot_calc_number_is]){symbol_id_to_select=nbre_symbols_on_plot[view_plot_calc_number_is];}
reset_numeric_entry();
numeric_postext=0;
if(symbol_id_to_select>0)
{
symbol_is_selected[view_plot_calc_number_is][symbol_id_to_select]=1;
}
mouse_released=1;
}
//fin focus window
}
 return(0);
}

int logical_plot_shape_list(int plotx, int ploty)
{


if(window_focus_id==W_PLOT && mouse_button==1 && mouse_released==0 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0)
{

//selection du shape
if( mouse_x>plotx+12 && mouse_x<plotx+28)
{
 if(mouse_y>ploty+36 && mouse_y<ploty+50) //UP
 {
 if( Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1597,Midi_Faders_Affectation_Mode);
 }
 else
 {
 shape_selected_type++;
 if(shape_selected_type>max_shape_type){shape_selected_type=0;}
    if(index_edit_light_plot==1){change_shape_type(shape_selected_type);}
    refresh_shape_factors(shape_selected_type);
 }
   mouse_released=1;
 }
 else if(  mouse_y>ploty+69 && mouse_y<ploty+83) //DOWN
 {
 if(Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1598,Midi_Faders_Affectation_Mode);
 }
 else
 {
  shape_selected_type--;
  if(shape_selected_type<0){shape_selected_type=max_shape_type;}
   if(index_edit_light_plot==1){change_shape_type(shape_selected_type);}
   refresh_shape_factors(shape_selected_type);
  }
  mouse_released=1;
 }
}

//sliderploty+30+(64-(shape_selected_type*6)))

//slider
if( mouse_x>=plotx+3 && mouse_x<=plotx+8 && mouse_y>=ploty+26 && mouse_y<ploty+30+70)
{

if(Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1599,Midi_Faders_Affectation_Mode);
 mouse_released=1;
 }
 else
 {
set_mouse_range(plotx+3,ploty+26 , plotx+8, ploty+30+70);//pour pas deborder
shape_selected_type= (64-(mouse_y-(ploty+30)))/6;
if(shape_selected_type<0){shape_selected_type=0;}
else if(shape_selected_type>max_shape_type){shape_selected_type=max_shape_type;}
 }
}

//ADD SYMBOL
if( mouse_x>plotx+40 && mouse_x<plotx+40+80 && mouse_y>ploty+110 && mouse_y<ploty+110+20)
{

 if(Midi_Faders_Affectation_Type!=0)
 {
 attribute_midi_solo_affectation(1600,Midi_Faders_Affectation_Mode);
 }
 else
 {
 add_shape_to_plot(shape_selected_type);
 }
mouse_released=1;
}
//select id
if(mouse_x>plotx+130 && mouse_x<plotx+130+65 && mouse_y>ploty+105 && mouse_y<ploty+105+28)
{
shape_id_to_select=atoi(numeric);
if(shape_id_to_select>nbre_shapes_on_plot){shape_id_to_select=nbre_shapes_on_plot;}
reset_numeric_entry();
numeric_postext=0;
if(shape_id_to_select>0)
{
shape_selected[shape_id_to_select]=1;
index_last_shape_selected=shape_id_to_select;
if(shape_groups[index_last_shape_selected]!=0)
{
for(int gr=0;gr<nbre_shapes_on_plot+1 ;gr++)
{
if(shape_groups[gr]==shape_groups[index_last_shape_selected])
{shape_selected[gr]=shape_selected[index_last_shape_selected];}
}
}



}
mouse_released=1;
}

//fin focus window

}
 return(0);
}



int logical_shape_edition(int plotx, int ploty)
{

if(window_focus_id==W_PLOT && mouse_button==1 && index_edit_light_plot==1 )
{

//rotation
if(mouse_x>=plotx+10 && mouse_x<=plotx+10+100+5 && mouse_y>ploty+40 && mouse_y<ploty+40+10 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0 && index_click_inside_relativ_xy==0)
{
if(mouse_released==0 &&  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1601,Midi_Faders_Affectation_Mode);
 mouse_released=1;
}
else
{
angle_shape_selected=((float)(mouse_x-(plotx+10)))/100;
if(angle_shape_selected<0.0){angle_shape_selected=0.0;}
if (angle_shape_selected>1.0){angle_shape_selected=1.0;}
affect_angle_to_shapes(angle_shape_selected);
}
}

//entree rotation Rect OverRot(Vec2D(plotx+76,ploty+22),Vec2D(60,15));
if(mouse_x>plotx+76 && mouse_x<plotx+76+60 && mouse_y>ploty+22 && mouse_y<ploty+22+15 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0 && index_click_inside_relativ_xy==0 && mouse_released==0)
{
float numof=atof(numeric);
angle_shape_selected=numof;
if(angle_shape_selected<0.0){angle_shape_selected=0.0;}
else if(angle_shape_selected>1.0){angle_shape_selected=1.0;}
affect_angle_to_shapes(angle_shape_selected);
mouse_released=1;
reset_numeric_entry();
numeric_postext=0;
}

//pre rotations
for(int l=0;l<3;l++)
{
for(int c=0;c<3;c++)
{
int pos2=(l*3) + c;
if( mouse_x>plotx+140+(c*15) && mouse_x<plotx+140+(c*15)+10 && mouse_y>ploty+10+(l*15) && mouse_y<ploty+10+(l*15)+10 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0)
{
switch(pos2)
{
case 0:
     angle_shape_selected=0.12;
break;
case 1:
    angle_shape_selected=0.0;
break;
case 2:
    angle_shape_selected=0.84;
break;
case 3:
     angle_shape_selected=0.24;
break;
case 4:
    //nothing
break;
case 5:
     angle_shape_selected=0.725;
break;
case 6:
     angle_shape_selected=0.36;
break;
case 7:
     angle_shape_selected=0.485;
break;
case 8:
     angle_shape_selected=0.59;
break;
default:
break;
}
affect_angle_to_shapes(angle_shape_selected); mouse_released=1;
}
}
}


//actions
for(int c=0;c<3;c++)
{
for(int l=0;l<2;l++)
{
if(mouse_x>plotx+5+(c*65) && mouse_x<plotx+5+(c*65)+60 && mouse_y>ploty+60+(l*20) && mouse_y<ploty+60+18+(l*20)
&& mouse_button==1 && mouse_released==0  && index_click_inside_relativ_xy==0 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0 )
{
switch(c+(l*3))
{
case 0://"Dub",plotx+20+(c*65),ploty+82+(l*20));
if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1602,Midi_Faders_Affectation_Mode);
}
else
{
duplicate_selected_shapes();
}
break;
case 1://"Delete",plotx+10+(c*65),ploty+82+(l*20));
if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1603,Midi_Faders_Affectation_Mode);
}
else
{
delete_selected_shapes();
}
break;
case 2://petitchiffre.Print("UnSelect",plotx+7+(c*65),ploty+72+(l*20));
if( Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1604,Midi_Faders_Affectation_Mode);
}
else
{
unselect_all_shapes();
}
break;
case 3://petitchiffre.Print("Down",plotx+15+(c*65),ploty+72+(l*20));
position_down_selected_shapes();
break;
case 4://petitchiffre.Print("Top",plotx+22+(c*65),ploty+72+(l*20));
position_on_top_selected_shapes();
break;
case 5://petitchiffre.Print("Grp/unGr.",plotx+7+(c*65),ploty+72+(l*20));
group_ungroup_selected_shapes();
break;
default:
break;
}
mouse_released=1;
}
}
}


//alignements
for(int c=0;c<4;c++)
{
if(window_focus_id==W_PLOT && index_edit_light_plot==1 && index_click_inside_relativ_xy==0
&& index_adjusting_shape_x==0 && index_adjusting_shape_y==0
&& mouse_button==1 && mouse_released==0
&& mouse_x>plotx+10+(c*45)&&mouse_x<plotx+10+(c*45)+40 && mouse_y>ploty+110 && mouse_y<ploty+110+18)
{
switch(c)
{
case 0://align x
plot_shapes_align_x();
break;
case 1://align y
plot_shapes_align_y();
break;
case 2://ventilation x
plot_shapes_ventilate_x();
break;
case 3://ventilation y
plot_shapes_ventilate_y();
break;
default:
break;
}
mouse_released=1;
}
}

//SIZE Du shape
if( mouse_x>=plotx+10 && mouse_x<=plotx+10+150+5 && mouse_y>ploty+155 && mouse_y<ploty+155+10 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0)
{
general_shape_size_to_apply=((float)(mouse_x-(plotx+10)));
if(general_shape_size_to_apply<0.5){general_shape_size_to_apply=0.5;}
else if(general_shape_size_to_apply>100.0){general_shape_size_to_apply=100.0;}
affect_size_to_shape(general_shape_size_to_apply);
}

if( mouse_released==0 && mouse_x>=plotx+126 && mouse_x<=plotx+126+70 && mouse_y>ploty+136 && mouse_y<ploty+136+15 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0)
{
float numo=atof(numeric);
general_shape_size_to_apply=numo;
if(general_shape_size_to_apply<0.5){general_shape_size_to_apply=0.5;}
else if(general_shape_size_to_apply>100.0){general_shape_size_to_apply=100.0;}
affect_size_to_shape(general_shape_size_to_apply);
 reset_numeric_entry();
 numeric_postext=0;
 mouse_released=1;
}
//color pattern
if( ( shape_selected_type>=0 && shape_selected_type<11 ) && mouse_released==0 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0 &&
mouse_x>plotx+10 && mouse_x<plotx+10+45 && mouse_y>ploty+190 && mouse_y<ploty+190+20)
{
color_pattern_selected++;
if(shape_selected_type>7 && color_pattern_selected>3){color_pattern_selected=0;}
else { if(color_pattern_selected>4){color_pattern_selected=0;}}
affect_color_pattern_to_shape(color_pattern_selected);
mouse_released=1;
}

if( shape_selected_type==7 && mouse_released==0  && index_click_inside_relativ_xy==0)//rectangle
{ //rectangle: x
if (mouse_x>=plotx+10 && mouse_x<plotx+10+45 && mouse_y>ploty+230 && mouse_y<ploty+230+20)
{
 if(numeric_postext>0)
 {
 float numo=atof(numeric);
 shape_rect_size_x=numo;
 reset_numeric_entry();
 numeric_postext=0;
 affect_size_to_rect(shape_rect_size_x,shape_rect_size_y);
 mouse_released=1;
 }
 else
 {
  index_adjusting_shape_x=1;
  temp_shape_rect_size_x=shape_rect_size_x;
 }
}//rectangle y
else if(mouse_x>=plotx+100 && mouse_x<plotx+100+45 && mouse_y>ploty+230 && mouse_y<ploty+230+20)
{
 if(numeric_postext>0)
 {
 float numo=atof(numeric);
 shape_rect_size_y=numo;
 reset_numeric_entry();
 numeric_postext=0;
 affect_size_to_rect(shape_rect_size_x,shape_rect_size_y);
 mouse_released=1;
 }
 else
 {
 index_adjusting_shape_y=1;
 temp_shape_rect_size_y=shape_rect_size_y;
 }
}
}
//angle de l arc opening angle
if( shape_selected_type==9 && mouse_released==0 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0 &&
mouse_x>=plotx && mouse_x<plotx+5+190 && mouse_y>ploty+240 && mouse_y<ploty+240+10)
{
opening_angle_selected=((float)(mouse_x-plotx))/180;
if(opening_angle_selected<0.0){opening_angle_selected=0.001;}
else if(opening_angle_selected>1.0){opening_angle_selected=1.0;}
refresh_opening_angle(opening_angle_selected);
}



if( shape_selected_type==10 && mouse_released==0 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0 &&
mouse_x>=plotx+10 && mouse_x<plotx+10+45 && mouse_y>ploty+230 && mouse_y<ploty+230+20)
{
nbre_branches_polygon=atoi(numeric);
reset_numeric_entry();
numeric_postext=0;
if(nbre_branches_polygon<3){nbre_branches_polygon=3;}
else if(nbre_branches_polygon>20){nbre_branches_polygon=20;}
affect_polygon_nbr_of_corners(nbre_branches_polygon);
mouse_released=1;
}

else if( shape_selected_type==11&& mouse_released==0 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0 &&
mouse_x>=plotx+10 && mouse_x<plotx+10+45 && mouse_y>ploty+230 && mouse_y<ploty+230+20)
{
if(numeric_postext>0)
{
fonttype_selected=atoi(numeric);
reset_numeric_entry();
numeric_postext=0;
if(fonttype_selected<0){fonttype_selected=0;}
else if(fonttype_selected>13){fonttype_selected=10;}
}
else
{
fonttype_selected++;
if(fonttype_selected>13){fonttype_selected=0;}
}
affect_font_to_texts(fonttype_selected);
mouse_released=1;
}

if( mouse_released==0 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0  && index_click_inside_relativ_xy==0 &&
mouse_x>=plotx+5 && mouse_x<plotx+5+10 && mouse_y>ploty+260 && mouse_y<ploty+260+10)
{
index_show_shape_id=toggle(index_show_shape_id);
mouse_released=1;
}

if(index_adjusting_shape_x==1 && index_click_inside_relativ_xy==0)
{
//shape_rect_size_x=(temp_shape_rect_size_x)-(((float)(mouse_y-original_posy))/10);
affect_size_to_rect(shape_rect_size_x,shape_rect_size_y);
}
else if
(index_adjusting_shape_y==1  && index_click_inside_relativ_xy==0)
{
//shape_rect_size_y=(temp_shape_rect_size_y)-(((float)(mouse_y-original_posy))/10);
affect_size_to_rect(shape_rect_size_x,shape_rect_size_y);
}


if(index_type==1 && mouse_released==0 && index_click_inside_relativ_xy==0 && mouse_x>plotx+10 && mouse_x<plotx+10+175 && mouse_y>ploty+275 && mouse_y<ploty+275+18)
{
edit_shape_name();
mouse_released=1;
}

//edition des relatifs dans la zone de tarcking
if( mouse_released==0 && mouse_x > plotx+110 && mouse_x<plotx+110+70 && mouse_y>ploty+300 && mouse_y<ploty+300+70 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0 && index_click_inside_relativ_xy==0 )
{

if(index_main_clear==1)
{
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1 )
{
 shape_relativ_position_legend_name[i][0]=0;
 shape_relativ_position_legend_name[i][1]=0;
}
}
index_main_clear=0;
}

else
{
if(index_click_inside_relativ_xy==0 && mouse_released==0 )
{
//prise de position
index_click_inside_relativ_xy=1;
store_relativ_xy_position_of_shape();
}

}
}





//alpha shape

if(index_click_inside_relativ_xy==0 && mouse_x>plotx-5 && mouse_x<plotx+10+100 && mouse_y>ploty+380 && mouse_y<ploty+380+10 && index_adjusting_shape_x==0 && index_adjusting_shape_y==0 )
{
general_alpha_for_shape=((float)(mouse_x-plotx))/100;
if(general_alpha_for_shape<0){general_alpha_for_shape=0;}
else if(general_alpha_for_shape>1.0){general_alpha_for_shape=1.0;}
}

}



 return(0);
}


int logical_symbol_edition_options(int plotx, int ploty)
{
//actions sur les options
if(window_focus_id==W_PLOT && index_edit_light_plot==1 && mouse_button==1 && mouse_released==0)
{
if(  index_click_inside_relativ_xy==0)
{
for (int l=0;l<8;l++)
{
//on off des affichages
if(mouse_x>plotx+5 && mouse_x<plotx+5+10 && mouse_y>ploty+70+(20*l) && mouse_y<ploty+70+(20*l)+10)
{
plot_show_options[l]=toggle(plot_show_options[l]);
mouse_released=1;
}
//edition
switch(l)
{
case 0: //"CHANNEL");
if(mouse_x>plotx+100 && mouse_x<plotx+100+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
if(tnum>=0 && tnum<=512)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
Selected_Channel[(symbol_channel_is[view_plot_calc_number_is][i])]=0;
symbol_channel_is[view_plot_calc_number_is][i]= tnum;
Selected_Channel[tnum]=1;
last_ch_selected=tnum;
if(symbol_dimmer_is[view_plot_calc_number_is][i]==0)
{
search_affect_first_dimmer_to_symbole(view_plot_calc_number_is,i);
}
if(index_build_patch_from_plot==1 && symbol_dimmer_is[view_plot_calc_number_is][i]>0)
{
Patch[(symbol_dimmer_is[view_plot_calc_number_is][i])]=(symbol_channel_is[view_plot_calc_number_is][i]);
}
}
}
}
generate_channel_view_list_from_patched_circuits();
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}
break;
case 1: //"LIST:");plotx+20,ploty+65+(20*l)));
if(index_type==1 && mouse_x>plotx+20 && mouse_x<plotx+20+175 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=0;
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
tnum=i;
for(int tt=0;tt<24;tt++)
{
descriptif_projecteurs[(symbol_channel_is[view_plot_calc_number_is][tnum])][tt]=numeric[tt];
}
descriptif_projecteurs[(symbol_channel_is[view_plot_calc_number_is][tnum])][24]='\0';
}
}
reset_numeric_entry();
if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
}
break;
case 2://"GEL 1:");
if(mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat[view_plot_calc_number_is][i][0]= tnum;
}
}
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}
else if(mouse_x>plotx+130 && mouse_x<plotx+130+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat_family[view_plot_calc_number_is][i][0]++;
if(gelat_family[view_plot_calc_number_is][i][0]>nbre_gelats_manufact){gelat_family[view_plot_calc_number_is][i][0]=0;}

}
}
plot_generate_appareils_list();
mouse_released=1;
}
break;
case 3: //"GEL 2:");
if(mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat[view_plot_calc_number_is][i][1]= tnum;
}
reset_numeric_entry();
numeric_postext=0;
}
plot_generate_appareils_list();
mouse_released=1;
}
else if(mouse_x>plotx+130 && mouse_x<plotx+130+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat_family[view_plot_calc_number_is][i][1]++;
if(gelat_family[view_plot_calc_number_is][i][1]>nbre_gelats_manufact){gelat_family[view_plot_calc_number_is][i][1]=0;}
}
}
plot_generate_appareils_list();
mouse_released=1;
}
break;
case 4: //"GEL 3:");
if(mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat[view_plot_calc_number_is][i][2]= tnum;
}
reset_numeric_entry();
numeric_postext=0;
}
mouse_released=1;
}
else if(mouse_x>plotx+130 && mouse_x<plotx+130+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat_family[view_plot_calc_number_is][i][2]++;
if(gelat_family[view_plot_calc_number_is][i][2]>nbre_gelats_manufact){gelat_family[view_plot_calc_number_is][i][2]=0;}
}
}
plot_generate_appareils_list();
mouse_released=1;
}
break;
case 5: //"DIMMER:");
if(mouse_x>plotx+100 && mouse_x<plotx+100+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);

if(tnum>=0 && tnum<=512)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
int olddim=symbol_dimmer_is[view_plot_calc_number_is][i];
int the_symb=i;

if(index_build_patch_from_plot==1 )
{Patch[olddim]=0;} //depatch

for (int l=0;l<4;l++)
{
for(int u=1;u<=nbre_symbols_on_plot[l];u++)
{
if  (symbol_dimmer_is[l][u]== tnum && (symbol_channel_is[l][u] != symbol_channel_is[view_plot_calc_number_is][the_symb]) ) {symbol_dimmer_is[l][u]=0;}
}
}
//fin check des gradas affectés à d autres
symbol_dimmer_is[view_plot_calc_number_is][the_symb]= tnum;
}
}
}
reset_numeric_entry();
numeric_postext=0;


if(index_build_patch_from_plot==1)
{
if(tnum>=0) {repatch_from_plot(view_plot_calc_number_is);    }
}
mouse_released=1;
}
break;
default:
break;
}
}

//nOTES
if(mouse_x>plotx+5 && mouse_x<plotx+5+195 && index_type==1)
{
for(int n=0;n<4;n++)
{
if(mouse_y>ploty+225+(n*20) && mouse_y<ploty+225+(n*20)+18)
{
   for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
   {
   if(symbol_is_selected[view_plot_calc_number_is][i]==1)
   {
   sprintf(symbol_note[view_plot_calc_number_is][i][n],numeric);
   }
   }
sprintf(symbol_note[view_plot_calc_number_is][last_selected_symbol_is][n],numeric);
reset_numeric_entry();
numeric_postext=0;
if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
break;
}
}
}

// text size
if(mouse_x>plotx+150 && mouse_x<plotx+150+30 && mouse_y>ploty+210 && mouse_y<ploty+220 )
{
plot_name_text_size=toggle(plot_name_text_size);
mouse_released=1;
}
//choix des  relatifs xy
for(int i=0;i<5;i++)
{
if(index_click_inside_relativ_xy==0 && mouse_x>plotx+5 && mouse_x<plotx+5+10 && mouse_y>ploty+320+(20*i) &&  mouse_y<ploty+320+(20*i)+10)
{
if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1610+i,Midi_Faders_Affectation_Mode);
}
else
{
switch(mode_relatif_xy_solo)
{
case 0:
adjust_xy_type[i]=toggle(adjust_xy_type[i]);
break;
case 1:
for(int j=0;j<5;j++)
{adjust_xy_type[j]=0;}
adjust_xy_type[i]=1;
break;
default: break;
}
}
mouse_released=1;

}
}

//mode solo ou pas des relatifs xy
if(index_click_inside_relativ_xy==0 && mouse_x>plotx+75 && mouse_x<plotx+75+10 && mouse_y>ploty+350 &&  mouse_y<ploty+350+10)
{
mode_relatif_xy_solo=toggle(mode_relatif_xy_solo);
mouse_released=1;
}

//choix des presets ( 6)

for(int pr=0;pr<8;pr++)
{
if( mouse_x>plotx+30+(20*pr) && mouse_x<plotx+30+(20*pr)+10 && mouse_y>ploty+430 && mouse_y<ploty+430+10)
{
xyrelativ_preset=pr;

if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_to_control(1615+pr,Midi_Faders_Affectation_Type,Midi_Faders_Affectation_Mode);
}
else
{
if(index_main_clear==0)
{

if(index_do_dock==0 )
{affect_preset_xy_to_symbols(pr);}

else if(index_do_dock==1 )
{
record_preset_xy_from_symbol(pr);
reset_symbols_selected(view_plot_calc_number_is);
index_do_dock=0;
}
}
else
{
index_ask_clear_preset_relativ=1;
index_ask_confirm=1;
}
plot_light_preset_on_click[pr]=1.0;
last_xyrelativ_preset=pr;
}
xyrelativ_preset=999;

mouse_released=1;
break;
}
}
//repatch en direct
if( mouse_y>ploty+450 && mouse_y<ploty+450+18)
{
if(mouse_x>plotx+20 && mouse_x<plotx+20+100 )//rebuild on off
{
index_build_patch_from_plot=toggle(index_build_patch_from_plot);
}
else if(mouse_x>plotx+110 && mouse_x<plotx+110+85 )//reset patch
{
index_do_clear_all_the_patch=1;
index_ask_confirm=1;
}
mouse_released=1;
}
}


//edition des relatifs dans la zone de tarcking
if( mouse_x > plotx+110 && mouse_x<plotx+110+70 && mouse_y>ploty+310 && mouse_y<ploty+310+70)
{

if(index_main_clear==1)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1 )
{
for(int t=0;t<5;t++)
{
if(adjust_xy_type[t]==1)
{
 relatif_plot_xy[view_plot_calc_number_is][i][t][0]=0;
 relatif_plot_xy[view_plot_calc_number_is][i][t][1]=0;
}
}
}
}
index_main_clear=0;
}

else
{
if(index_click_inside_relativ_xy==0 && mouse_released==0 )
{
//prise de position
index_click_inside_relativ_xy=1;
store_relativ_xy_position_of_activ_calc(view_plot_calc_number_is);
}

}
}

}
 return(0);
}


int logical_plot_symbol_edition(int plotx, int ploty)
{

if(window_focus_id==W_PLOT && mouse_button==1 && mouse_released==0 && index_click_inside_relativ_xy==0)
{
//rotation
if( mouse_x>=plotx+10 && mouse_x<=plotx+10+100+5 && mouse_y>ploty+40 && mouse_y<ploty+40+10)
{

if(mouse_released==0 &&  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1601,Midi_Faders_Affectation_Mode);
 mouse_released=1;
}
else
{
angle_projo_selectionne=((float)(mouse_x-(plotx+10)))/100;
if(angle_projo_selectionne<0.0){angle_projo_selectionne=0.0;}
if (angle_projo_selectionne>1.0){angle_projo_selectionne=1.0;}
affect_angle_to_symbols(view_plot_calc_number_is,angle_projo_selectionne);
}
}

//entree rotation
if(mouse_x>plotx+76 && mouse_x<plotx+76+60 && mouse_y>ploty+22 && mouse_y<ploty+22+15 && index_click_inside_relativ_xy==0 && mouse_released==0)
{
float numof=atof(numeric);
angle_projo_selectionne=numof;
if(angle_projo_selectionne<0.0){angle_projo_selectionne=0.0;}
else if(angle_projo_selectionne>1.0){angle_projo_selectionne=1.0;}
affect_angle_to_symbols(view_plot_calc_number_is,angle_projo_selectionne);
mouse_released=1;
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}

//pre rotations
for(int l=0;l<3;l++)
{
for(int c=0;c<3;c++)
{
int pos2=(l*3) + c;
if( mouse_x>plotx+140+(c*15) && mouse_x<plotx+140+(c*15)+10 && mouse_y>ploty+10+(l*15) && mouse_y<ploty+10+(l*15)+10 )
{
switch(pos2)
{
case 0:
     angle_projo_selectionne=0.12;
break;
case 1:
     angle_projo_selectionne=0.0;
break;
case 2:
     angle_projo_selectionne=0.84;
break;
case 3:
     angle_projo_selectionne=0.242;
break;
case 4:
    //nothing
break;
case 5:
     angle_projo_selectionne=0.725;
break;
case 6:
     angle_projo_selectionne=0.36;
break;
case 7:
     angle_projo_selectionne=0.483;
break;
case 8:
     angle_projo_selectionne=0.605;
break;
default:
break;
}
affect_angle_to_symbols(view_plot_calc_number_is,angle_projo_selectionne); mouse_released=1;
}
}
}



}

//actions
for(int c=0;c<3;c++)
{
for(int l=0;l<2;l++)
{
//MySymbAction.MoveTo(Vec2D(plotx+5+(c*65),ploty+70+(l*20)));
if(index_edit_light_plot==1 && index_click_inside_relativ_xy==0
&& mouse_x>plotx+5+(c*65) && mouse_x<plotx+5+(c*65)+60 && mouse_y>ploty+60+(l*20) && mouse_y<ploty+60+(l*20)+18
&& mouse_button==1 && mouse_released==0)
{
switch(c+(l*3))
{
case 0://"Dub",plotx+20+(c*65),ploty+82+(l*20));

if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1602,Midi_Faders_Affectation_Mode);
}
else
{
duplicate_selected_symbols(view_plot_calc_number_is);
}
break;
case 1://"Delete",plotx+10+(c*65),ploty+82+(l*20));



if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1603,Midi_Faders_Affectation_Mode);
}
else
{
snapshot_calc(view_plot_calc_number_is);
delete_selected_symbols(view_plot_calc_number_is);


plot_generate_appareils_list();
generate_channel_view_list_from_patched_circuits();


}
break;
case 2://"SendTo"
if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1604,Midi_Faders_Affectation_Mode);
}
else
{
index_plot_send_to_mode=toggle(index_plot_send_to_mode);
}
break;
case 3://"Down"
position_down_selected_symbols(view_plot_calc_number_is);
break;
case 4://"Top"
position_on_top(view_plot_calc_number_is);
break;
case 5://"Grp/ungroup"
group_symbols_selected(view_plot_calc_number_is);
break;
default:
break;
}
mouse_released=1;
}
}


//alignements
for(int c=0;c<4;c++)
{
if( index_edit_light_plot==1 && index_click_inside_relativ_xy==0
 && mouse_button==1 && mouse_released==0
&& mouse_x>plotx+10+(c*45)&&mouse_x<plotx+10+(c*45)+40 && mouse_y>ploty+110 && mouse_y<ploty+110+18)
{
switch(c)
{
case 0://align x
plot_align_x(view_plot_calc_number_is);
break;
case 1://align y
plot_align_y(view_plot_calc_number_is);
break;
case 2://ventilation x
plot_ventilate_x(view_plot_calc_number_is);
break;
case 3://ventilation y
plot_ventilate_y(view_plot_calc_number_is);
break;
default:
break;
}
mouse_released=1;
}
}



}


 return(0);
}

int logical_plot_menu_bare(int plotx,int ploty)
{

if(window_focus_id==W_PLOT && mouse_button==1 && mouse_released==0 && index_click_inside_relativ_xy==0 && index_click_inside_plot==0)
{
//selection edition layers
if(mouse_x>plotx && mouse_x<plotx+35 && mouse_y>ploty && mouse_y<ploty+20)
{
index_edit_light_plot=toggle(index_edit_light_plot);
mouse_released=1;
}
for(int i=0;i<4;i++)
{
if(mouse_x>plotx+45+(i*15) && mouse_x<plotx+45+(i*15)+10 )
{
if( mouse_y>ploty-5 && mouse_y<ploty+5)//vision
{
if( Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1605+i,Midi_Faders_Affectation_Mode);
}
else
{
if(index_main_clear==0 && index_plot_send_to_mode==0)
{
switch(plot_layer_mode)
{
case 0:
show_calc_number[i]=toggle(show_calc_number[i]);mouse_released=1;
break;
case 1:
for(int j=0;j<4;j++)
{
show_calc_number[j]=0;
}
show_calc_number[i]=1;
view_plot_calc_number_is=i;
mouse_released=1;
break;
default: break;
}
plot_generate_appareils_list();
}
else if(index_main_clear==1 && index_plot_send_to_mode==0)
{
plot_layer_selected=i;
index_ask_delete_symbols_on_calc=1;
index_ask_confirm=1;
}
else if(index_main_clear==0 && index_plot_send_to_mode==1)
{
plot_layer_selected=i;
send_symbols_from_calc_to_calc(view_plot_calc_number_is,plot_layer_selected)     ;
recount_symbols_on_calc(view_plot_calc_number_is);
//recount_symbols_on_calc(plot_layer_selected);
index_plot_send_to_mode=0;
plot_layer_selected=0;
plot_generate_appareils_list();
}
}
}
else if(mouse_y>ploty+10 && mouse_y<ploty+20)
{
reset_symbols_selected(view_plot_calc_number_is);index_click_inside_plot=0;
switch(plot_layer_mode)
{
case 0:
view_plot_calc_number_is=i;show_calc_number[i]=1;
break;
case 1:
for(int j=0;j<4;j++)
{
show_calc_number[j]=0;
}
show_calc_number[i]=1;
view_plot_calc_number_is=i;
mouse_released=1;
break;
default: break;
}
plot_generate_appareils_list();
}

mouse_released=1;
}


}

//menus modes
if(mouse_x>plotx+130 && mouse_x<plotx+130+100 && mouse_y>ploty-5 && mouse_y<ploty-5+25)
{
if(index_main_clear==0)
{
int previous_pos=index_menus_lighting_plot;
index_menus_lighting_plot++;

if(index_menus_lighting_plot>4){index_menus_lighting_plot=0;}
if(index_menus_lighting_plot>1){ plot_generate_appareils_list();}
if(index_menus_lighting_plot==3 )//legende
{
plot_correcteur_portx=plot_view_port_x;plot_correcteur_porty=plot_view_port_y;
}
if(index_menus_lighting_plot==4 )
{
plot_window_x_size-=position_plan_x;
if(plot_window_x_size<840){plot_window_x_size=840;}
position_plan_x=0;
}
if(previous_pos==4)
{
position_plan_x=230;
plot_window_x_size+=position_plan_x;
}
}
else//clear
{
index_ask_general_clear_on_plot=1;
index_ask_confirm=1;
}
mouse_released=1;
}

//viewport
if(mouse_x>plotx+240 && mouse_x<plotx+240+120 && mouse_y>ploty-5 && mouse_y<ploty-5+25)
{
if(index_main_clear==1)
{
 plot_view_port_x=0;plot_view_port_y=0;
}
else
{
  index_move_plot_view_port=toggle( index_move_plot_view_port);
  mouse_released=1;
}
mouse_released=1;
}

//layer edit mode solo ou multichouches
if(mouse_x>plotx+110 && mouse_x<plotx+110+10 && mouse_y>ploty+2 && mouse_y<ploty+2+10)
{
if(  Midi_Faders_Affectation_Type!=0)
{
 attribute_midi_solo_affectation(1609,Midi_Faders_Affectation_Mode);
}
else
{
plot_layer_mode=toggle(plot_layer_mode);
}
mouse_released=1;
}


//view levels from plot

command_button_logical(plotx+380,ploty-5,plot_index_show_levels,"SeeLevels","",1595,100);// int x, inty ,bool state, char *textedesc, int midiaffectation

command_button_logical(plotx+460,ploty-5,plot_index_show_levels_from_faders,"SeeFaders","",1596,101);// int x, inty ,bool state, char *textedesc, int midiaffectation

command_button_logical(plotx+540,ploty-5,index_blind,"Blind","",754,110);// int x, inty ,bool state, char *textedesc, int midiaffectation, int the command number

//export plot
if(index_menus_lighting_plot!=4)
{
if(mouse_x>plotx+620 && mouse_x<plotx+620+100 && mouse_y>ploty-5 && mouse_y<ploty-5+20 && mouse_x<plotx+plot_window_x_size)
{
index_do_a_plot_screen_capture=1;
index_show_button_export=1.0;
mouse_released=1;
}
if(index_type==1 && mouse_x>plotx+730 && mouse_x<plotx+730+220 && mouse_x<plotx+plot_window_x_size-position_plan_x && mouse_y>ploty-5 && mouse_y<ploty+15)
{
sprintf(plot_name_of_capture,numeric);
reset_numeric_entry();numeric_postext=0;
if(index_text_auto_close==1){index_type=0;}
mouse_released=1;
}
}

}
return(0);
}



int logical_deroule_repertoire_plans(int xrep, int yrep)
{

for (int y=0;y<8;y++)
{

if( index_editing_theatre_plan==0 && mouse_x>xrep+5 && mouse_x<xrep+5+150 && mouse_y>(yrep+185+(y*20)-10) && mouse_y<(yrep+185+(y*20)+5))
{
if(mouse_button==1 && mouse_released==0)
{
importplan_selected=y+line_importplan;
mouse_released=1;
sprintf(Name_of_plane_is,list_import_plans[importplan_selected]);


load_plan_of_theatre(Name_of_plane_is, 1);


alpha_plan=1.0;

}
}

}


//////////////////UP DOWN LINE IMPORT/////////////////////

if(mouse_x>xrep+190-12 && mouse_x<xrep+190+12)
{
if(mouse_y>yrep+180-12 && mouse_y<yrep+200+12)
{
if(mouse_button==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0)
{
if(line_importplan>0){line_importplan--;}
}
}
else if(mouse_y>yrep+290-12 && mouse_y<yrep+310+12)
{
if(mouse_button==1 &&  index_editing_theatre_plan==0)
{
if(line_importplan<127){line_importplan++;}
}
}
}

if( index_editing_theatre_plan==0 && mouse_x>xrep+150 && mouse_x<xrep+150+60 && mouse_y>(yrep+345) && mouse_y<(yrep+345+20)
 && editing_plot_sizex==0 && editing_plot_sizey==0)
{
if(mouse_button==1 && mouse_released==0)
{
scan_planfolder();
 mouse_released=1;
}
}

return(0);
}


int logical_menu_plan(int plotx, int ploty)
{

if(window_focus_id==W_PLOT && index_edit_light_plot==1 && editing_plot_sizex==0 && editing_plot_sizey==0 && mouse_button==1 && mouse_released==0 && index_click_inside_relativ_xy==0 && index_click_inside_plot==0 && plot_editing_color_background==0 && plot_editing_color_line==0)
{

//grille taille
if(index_editing_theatre_plan==0 )
{
if( mouse_x>plotx+40 && mouse_x<plotx+40+40 && mouse_y>ploty+195 && mouse_y<ploty+195+20)
{
plot_quadrillage_size+=25;
if(plot_quadrillage_size>200){plot_quadrillage_size=0;}
mouse_released=1;
}
if ( mouse_x>plotx+100 && mouse_x<plotx+100+40 && mouse_y>ploty+195 && mouse_y<ploty+195+20)
{
plot_grid_type=toggle(plot_grid_type);
mouse_released=1;
}
if ( mouse_x>plotx+145 && mouse_x<plotx+150+60 && mouse_y>ploty+200 && mouse_y<ploty+200+10)
{
alpha_grille=(float)(mouse_x-(plotx+150))/50;
if(alpha_grille<0.0){alpha_grille=0.0;}
if(alpha_grille>1.0){alpha_grille=1.0;}
}
}


for(int i=0;i<4;i++)
{
if(mouse_x>plotx+5+(50*i) && mouse_x<plotx+5+(50*i)+45 && mouse_y>ploty+90 && mouse_y<ploty+90+20)
{
if(numeric_postext>0)
{
float numo=atof(numeric);
switch(i)
{
case 0:
position_relative_plan_theatre[0]=int(numo);
break;
case 1:
position_relative_plan_theatre[1]=int(numo);
break;
case 2:
ratio_lock_plot_scale=(float)(taille_relative_plan_theatre[0])/(float)(taille_relative_plan_theatre[1]);
taille_relative_plan_theatre[0]=int(numo);
 if(lock_background_proportions==1)
   {
   taille_relative_plan_theatre[1]=(int)(((float)taille_relative_plan_theatre[0])/ratio_lock_plot_scale);
   }
break;
case 3:
ratio_lock_plot_scale=(float)(taille_relative_plan_theatre[0])/(float)(taille_relative_plan_theatre[1]);
taille_relative_plan_theatre[1]=int(numo);
 if(lock_background_proportions==1)
   {
   taille_relative_plan_theatre[0]=(int)(((float)taille_relative_plan_theatre[1])/ratio_lock_plot_scale);
   }
break;
default:
break;
}
editing_plan_data_type=i+1;
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}
else if(numeric_postext==0)//drag souris
{
  if( index_editing_theatre_plan==0)
  {
  index_editing_theatre_plan=1;
  editing_plan_data_type=i+1;
  old_position_relative_plan_theatre[0]=position_relative_plan_theatre[0];
  old_position_relative_plan_theatre[1]=position_relative_plan_theatre[1];
  old_taille_relative_plan_theatre[0]=taille_relative_plan_theatre[0];
  old_taille_relative_plan_theatre[1]=taille_relative_plan_theatre[1];
  ratio_lock_plot_scale=(float)(taille_relative_plan_theatre[0])/(float)(taille_relative_plan_theatre[1]);
  }
}

}

}
  if(index_edit_light_plot==1 && index_editing_theatre_plan==1 && editing_plot_sizex==0 && editing_plot_sizey==0 && index_click_inside_relativ_xy==0 && index_click_inside_plot==0 && plot_editing_color_background==0 && plot_editing_color_line==0 )
  {
   moving_plan_relativ_x=mouse_x-original_posx;
   moving_plan_relativ_y=mouse_y-original_posy;



   switch(editing_plan_data_type)//décalé de +1
   {
   case 1:
   position_relative_plan_theatre[0]=old_position_relative_plan_theatre[0]-moving_plan_relativ_y;
   break;
   case 2:
   position_relative_plan_theatre[1]=old_position_relative_plan_theatre[1]-moving_plan_relativ_y;
   break;
   case 3:
   taille_relative_plan_theatre[0]=old_taille_relative_plan_theatre[0]-moving_plan_relativ_y;
   if(lock_background_proportions==1)
   {
   taille_relative_plan_theatre[1]=(int)(((float)taille_relative_plan_theatre[0])/ratio_lock_plot_scale );
   }
   break;
   case 4:
   taille_relative_plan_theatre[1]=old_taille_relative_plan_theatre[1]-moving_plan_relativ_y;
   if(lock_background_proportions==1)
   {
   taille_relative_plan_theatre[0]=(int)(((float)taille_relative_plan_theatre[1])*ratio_lock_plot_scale);
   }
   break;
   default:
   break;
   }
}

//lock proportions
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && mouse_released==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0 && mouse_x>=plotx+5+141 && mouse_x<=plotx+5+141+8 && mouse_y>ploty+111 && mouse_y<ploty+111+8)
{
lock_background_proportions=toggle(lock_background_proportions);
mouse_released=1;
}
//rotation plan
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0 && mouse_x>=plotx+10 && mouse_x<=plotx+10+100+5 && mouse_y>ploty+140 && mouse_y<ploty+140+10)
{
orientation_plan_theatre=((float)(mouse_x-(plotx+10)))/100;
if(orientation_plan_theatre<0.0){orientation_plan_theatre=0.0;}
if (orientation_plan_theatre>1.0){orientation_plan_theatre=1.0;}
}
//pre rotations
for(int l=0;l<3;l++)
{
for(int c=0;c<3;c++)
{
int pos2=(l*3) + c;
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0
 &&  mouse_x>plotx+140+(c*15) && mouse_x<plotx+140+(c*15)+10 && mouse_y>ploty+125+(l*15) && mouse_y<ploty+125+(l*15)+10 )
{
switch(pos2)
{
case 0:
     orientation_plan_theatre=0.12;
break;
case 1:
     orientation_plan_theatre=0.0;
break;
case 2:
     orientation_plan_theatre=0.84;
break;
case 3:
     orientation_plan_theatre=0.24;
break;
case 4:
    //nothing
break;
case 5:
     orientation_plan_theatre=0.725;
break;
case 6:
     orientation_plan_theatre=0.36;
break;
case 7:
     orientation_plan_theatre=0.485;
break;
case 8:
     orientation_plan_theatre=0.59;
break;
default:
break;
}
mouse_released=1;
}
}
}

//alpha plan
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0  && mouse_x>=plotx+5 && mouse_x<=plotx+10+100+5 && mouse_y>ploty+180 && mouse_y<ploty+180+10)
{
alpha_plan=((float)(mouse_x-(plotx+10)))/100;
if(alpha_plan<0.0){alpha_plan=0.0;}
if (alpha_plan>1.0){alpha_plan=1.0;}
}

//logical_deroule_repertoire_plans(plotx-5,ploty+80);    sorti et mis dans boucle affichage pour rafraichissements images


//edition taille fenetre plot
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0  &&
mouse_x>plotx+5 && mouse_x<plotx+5+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
if(numeric_postext>0)
{
plot_window_x_size=atol(numeric);
if(plot_window_x_size<840){plot_window_x_size=840;}
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}
else if(numeric_postext==0)//drag souris
{
if(editing_plot_sizex==0)
{
editing_plot_sizex=1;
old_plot_sizex=plot_window_x_size;
}
}
}

if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0  &&
mouse_x>plotx+5+50 && mouse_x<plotx+5+50+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
if(numeric_postext>0)
{
plot_window_y_size=atol(numeric);
if(plot_window_y_size<plot_minimum_y_size){plot_window_y_size=plot_minimum_y_size;}
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}
else if(numeric_postext==0)//drag souris
{
if(editing_plot_sizey==0)
{
editing_plot_sizey=1;
old_plot_sizey=plot_window_y_size;
}
}
}
}

if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0
&& mouse_button==1 && mouse_x>plotx+5+100 && mouse_x<plotx+5+100+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
plot_editing_color_background=1;  plot_editing_color_line=0;
}
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && plot_editing_color_background==0 && plot_editing_color_line==0
&& mouse_button==1 && mouse_x>plotx+5+150 && mouse_x<plotx+5+150+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
plot_editing_color_line=1; plot_editing_color_background=0;
}

//sorti du mouse_button
if(editing_plot_sizex==1)
{
moving_size_relativ_x=mouse_y-original_posy;
plot_window_x_size=old_plot_sizex-(moving_size_relativ_x*10);
if(plot_window_x_size<840){plot_window_x_size=840;}
}
else if(editing_plot_sizey==1)
{
moving_size_relativ_y=mouse_y-original_posy;
plot_window_y_size=old_plot_sizey-(moving_size_relativ_y*10);
if(plot_window_y_size<plot_minimum_y_size){plot_window_y_size=plot_minimum_y_size;}
}

else if(plot_editing_color_background==1)
{
Color_plotfill=((float)(original_posy-mouse_y))/50;
if(Color_plotfill<0.0){Color_plotfill=0.0;}
Rgba TmpPlotColor (Color_plotfill,Color_plotfill,Color_plotfill);
CouleurPlotFill=TmpPlotColor;
}
else if(plot_editing_color_line==1)
{
Color_plotline=((float)(original_posy-mouse_y))/50;
if(Color_plotline<0.0){Color_plotline=0.0;}
Rgba TmpPlotColor (Color_plotline,Color_plotline,Color_plotline);
CouleurPlotLine=TmpPlotColor;
}
 return(0);
}




int do_logical_Plot_window(int plotx, int ploty)
{
if(window_focus_id==W_PLOT && mouse_x> plotx && mouse_x<plotx+plot_window_x_size && mouse_y>ploty && mouse_y<ploty + plot_window_y_size)
{
logical_plot_menu_bare(plotx+230,ploty+10);

switch(index_menus_lighting_plot)
{
case 0://plan
logical_menu_plan(plotx+10, ploty+50);
break;
case 1://shapes
logical_plot_shape_list(plotx+10, ploty+50);
logical_shape_edition(plotx+10, ploty+200);
break;
case 2://symbols
logical_plot_symbol_list(plotx+10, ploty+50);
logical_plot_symbol_edition(plotx+10, ploty+200);//editeur de symbol
logical_symbol_edition_options(plotx+10, ploty+275);
break;
case 3://légende
break;
case 4://plan seul
break;
default:
break;
}

//CALCUL MOVE ATTRIBUTS
if(index_click_inside_relativ_xy==1 && mouse_button==1 && mouse_released==0)
{
switch(index_menus_lighting_plot)
{
case 1://shapes
rlativ_xm=mouse_x-(plotx+110+35);
rlativ_ym=mouse_y-(ploty+485+35);
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1 )
{
 shape_relativ_position_legend_name[i][0]=temp_shape_relativ_position_legend_name[i][0]+ rlativ_xm;
 shape_relativ_position_legend_name[i][1]=temp_shape_relativ_position_legend_name[i][1]+ rlativ_ym;
}
}
break;
case 2://symbols
rlativ_xm=mouse_x-(plotx+110+35);
rlativ_ym=mouse_y-(ploty+585+35);
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1 )
{
for(int t=0;t<5;t++)
{
if(adjust_xy_type[t]==1)
{
 relatif_plot_xy[view_plot_calc_number_is][i][t][0]=temp_relatif_plot_xy_array[i][t][0]+ rlativ_xm;
 relatif_plot_xy[view_plot_calc_number_is][i][t][1]=temp_relatif_plot_xy_array[i][t][1]+ rlativ_ym;
}
}
}
}
break;
default:
break;
}
}

//editions
if(mouse_x> plotx+position_plan_x && mouse_x<plotx+position_plan_x+plot_window_x_size
&& mouse_y> ploty+position_plan_y && mouse_y<ploty+position_plan_y+plot_window_y_size )
{
if(index_click_inside_plot==0 && index_click_inside_relativ_xy==0 && mouse_button==1 && mouse_released==0 )
{
//prise de position
index_click_inside_plot=1;
plot_original_mouse_x=mouse_x;
plot_original_mouse_y=mouse_y;
switch(index_menus_lighting_plot)
{
case 0://bckgd
break;
case 1://shapes
check_select_deselect_shape(plotx+position_plan_x+plot_view_port_x,ploty+position_plan_y+plot_view_port_y);
store_plot_position_of_shapes();
break;
case 2://symbols
check_select_deselect_symbol(plotx+position_plan_x+plot_view_port_x,ploty+position_plan_y+plot_view_port_y);
store_plot_position_of_activ_calc(view_plot_calc_number_is);
break;
case 3://legend
break;
case 4://PLOT
check_select_deselect_symbol(plotx+position_plan_x+plot_view_port_x,ploty+position_plan_y+plot_view_port_y);
break;
default:
break;
}
previous_plot_view_port_x=plot_view_port_x;
previous_plot_view_port_y=plot_view_port_y;
}
else if (index_click_inside_plot==1 &&  index_click_inside_relativ_xy==0 && mouse_button==1 && mouse_released==0  )
{
plot_facteur_move_x=mouse_x-plot_original_mouse_x;
plot_facteur_move_y=mouse_y-plot_original_mouse_y;



if(index_move_plot_view_port==0 &&  index_edit_light_plot==1)
{
switch(index_menus_lighting_plot)
{
//case 0://bckgd
//break;
case 1://shapes
for(int i=1;i<=nbre_shapes_on_plot;i++)
{
if(shape_selected[i]==1 )
{
if(handle_selected_for_line_editing==0)
{
shape_position[i][0]=stored_plot_shape_position[i][0]+ plot_facteur_move_x ;
shape_position[i][1]=stored_plot_shape_position[i][1]+ plot_facteur_move_y ;
if(shape_type[i]<7)//lignes
{
shape_position[i][2]=stored_plot_shape_position[i][2]+ plot_facteur_move_x ;
shape_position[i][3]=stored_plot_shape_position[i][3]+ plot_facteur_move_y ;
}
}
else if(handle_selected_for_line_editing==1 && shape_selected[editing_shape_line_number]==1)
{
shape_position[editing_shape_line_number][2]=stored_plot_shape_position[editing_shape_line_number][2]+ plot_facteur_move_x;
shape_position[editing_shape_line_number][3]=stored_plot_shape_position[editing_shape_line_number][3]+ plot_facteur_move_y ;
}
}
}
break;
case 2://symbols
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1 )
{
pos_symbol[view_plot_calc_number_is][i][0]=stored_plot_position[i][0]+ plot_facteur_move_x ;
pos_symbol[view_plot_calc_number_is][i][1]=stored_plot_position[i][1]+ plot_facteur_move_y ;
}
}
break;
case 3://legend

break;
default:
break;
}
}
else if(index_move_plot_view_port==1)
{
plot_view_port_x=previous_plot_view_port_x+plot_facteur_move_x;
plot_view_port_y=previous_plot_view_port_y+plot_facteur_move_y;
}
}
}


}
return(0);
}
