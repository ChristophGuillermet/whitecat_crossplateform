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

* \file plot.cpp
* \brief {Plot global and import export fonctions}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions globales et d'import export du plan de feux dans whitecat
*
*   Plot of lights global fonctions and import export
*
**/

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
            isSomeone=true; // we've found a directory!
            bool index_check_is_supported=0;
            for(int a=0;a<strlen(f.name);a++)
           {
           if( f.name[a]=='.')
           {
                if(
                (f.name[a+1]=='j' &&  f.name[a+2]=='p' &&  f.name[a+3]=='g')
                || (f.name[a+1]=='b' &&  f.name[a+2]=='m' &&  f.name[a+3]=='p')
                || (f.name[a+1]=='t' &&  f.name[a+2]=='g' &&  f.name[a+3]=='a')
                || (f.name[a+1]=='p' &&  f.name[a+2]=='n' &&  f.name[a+3]=='g')
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

int substract_channel_selection_to_layers_plot()
{
int tmp_ch=0;
for(int l=0;l<4;l++)
{
for(int i=1;i<=nbre_symbols_on_plot[l];i++)
{
tmp_ch=symbol_channel_is[l][i];
if(Selected_Channel[tmp_ch]==0)
{
symbol_is_selected[l][i]= 0;
}
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
if(symbol_is_selected[calc][i]==1)
{
Patch[(symbol_dimmer_is[calc][i])] =symbol_channel_is[calc][i];
}
}

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

int clear_symbol_slot(int calc, int s)
{
symbol_type[calc][s]=1;
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
//relatif_plot_xy[4][nbre_symbol_per_layer][4][2];//calc / Symbols / Famille / X Y
for(int opt=0;opt<4;opt++)
{
relatif_plot_xy[calc][s][opt][0]=0;
relatif_plot_xy[calc][s][opt][1]=0;
}
return(0);
}

int clear_calc(int calc)
{
for(int i=0;i<nbre_symbol_per_layer;i++)
{
clear_symbol_slot(calc,i);
}
nbre_symbols_on_plot[calc]=0;
return(0);
}

int add_a_symbol_to_plot(int plot_calc_number_is)
{

nbre_symbols_on_plot[plot_calc_number_is]++;
clear_symbol_slot(plot_calc_number_is,nbre_symbols_on_plot[plot_calc_number_is]);
if(nbre_symbols_on_plot[plot_calc_number_is]>126){nbre_symbols_on_plot[plot_calc_number_is]=126;}
pos_symbol[plot_calc_number_is][nbre_symbols_on_plot[plot_calc_number_is]][0]=(plot_window_x_size/2)-x_plot+(nbre_symbols_on_plot[plot_calc_number_is]*2);
pos_symbol[plot_calc_number_is][nbre_symbols_on_plot[plot_calc_number_is]][1]=(plot_window_y_size/2)-y_plot+(nbre_symbols_on_plot[plot_calc_number_is]*2);
angle_symbol[plot_calc_number_is][nbre_symbols_on_plot[plot_calc_number_is]]=0;
symbol_type[plot_calc_number_is][(nbre_symbols_on_plot[plot_calc_number_is])]=symbol_selected_type;

reset_symbols_selected(view_plot_calc_number_is);
symbol_is_selected[plot_calc_number_is][(nbre_symbols_on_plot[plot_calc_number_is])]=1;
last_selected_symbol_is=nbre_symbols_on_plot[plot_calc_number_is];
return(0);
}

int duplicate_selected_symbols(int calc)
{


return(0);
}

int snapshot_calc(int calc)
{
for(int s=1;s<nbre_symbol_per_layer;s++)
{
snapshot_symbol_type[s]=symbol_type[calc][s];
snapshot_symbol_is_selected[s]=symbol_is_selected[calc][s];
snapshot_angle_symbol[s]=angle_symbol[calc][s];
snapshot_pos_symbol[s][0]=pos_symbol[calc][s][0];
snapshot_pos_symbol[s][1]=pos_symbol[calc][s][1];
snapshot_symbol_channel_is[s]=symbol_channel_is[calc][s];
snapshot_symbol_dimmer_is[s]=symbol_dimmer_is[calc][s];
for(int opt=0;opt<4;opt++)
{
snapshot_gelat[s][opt]=gelat[calc][s][opt];
snapshot_gelat_family[s][opt]=gelat_family[calc][s][opt];
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
for(int opt=0;opt<4;opt++)
{
gelat[calc][empty][opt]=snapshot_gelat[filled][opt];
gelat_family[calc][empty][opt]=snapshot_gelat_family[filled][opt];
relatif_plot_xy[calc][empty][opt][0]=snapshot_relatif_plot_xy[filled][opt][0];
relatif_plot_xy[calc][empty][opt][1]=snapshot_relatif_plot_xy[filled][opt][1];
}
return(0);
}

int rearrange_plan(int calc)
{
for(int s=1; s<nbre_symbol_per_layer;s++)
{
if(snapshot_symbol_is_selected[s]==1)
{
for(int sz=s;sz<nbre_symbol_per_layer;sz++)
{
if(snapshot_symbol_is_selected[sz]==0)
{
copy_symbol_to_emply_slot(calc,s,sz);
break;
}
}
}
}
return(0);
}

int delete_selected_symbols(int calc)
{
snapshot_calc(calc);
int nbre_symb_to_delete=0;
for(int i=1;i<=nbre_symbols_on_plot[calc];i++)
{
if(symbol_is_selected[calc][i]==1)
{
nbre_symb_to_delete++;
clear_symbol_slot(calc,i);
}
}

//rearrangement
rearrange_plan(calc);
nbre_symbols_on_plot[calc]-=nbre_symb_to_delete;
if(nbre_symbols_on_plot[calc]<0){nbre_symbols_on_plot[calc]=0;}
last_selected_symbol_is=0;
return(0);
}

int add_selected_symbols_to_calc(int calc)
{
for(int i=1;i<nbre_symbol_per_layer;i++)
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
return(0);
}


int exchange_symbol_position(int calc,int pos_source, int pos_dest)
{
copy_symbol_to_emply_slot(calc, pos_dest, pos_source);
copy_symbol_to_emply_slot(calc, pos_source, pos_dest);
return(0);
}

int send_symbols_from_calc_to_calc(int calc_source,int calc_dest)
{
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
}
}
return(0);
}


int position_on_top(int calc)
{
delete_selected_symbols(calc);
add_selected_symbols_to_calc(calc);
return(0);
}


int store_relativ_xy_position_of_activ_calc(int calc)
{
for(int i=1;i<nbre_symbol_per_layer;i++)
{
temp_relatif_plot_xy_array[i][0]=relatif_plot_xy[calc][i][adjust_xy_type][0];
temp_relatif_plot_xy_array[i][1]=relatif_plot_xy[calc][i][adjust_xy_type][1];
}
return(0);
}

int check_select_deselect_symbol(int posx, int posy)
{
int previous_calc_selection=view_plot_calc_number_is;
for(int calc=0;calc<4;calc++)
{
if(show_calc_number[calc]==1)
{
for(int i=1;i<= nbre_symbols_on_plot[calc];i++)
{
if(mouse_x>posx+pos_symbol[calc][i][0]-(20*size_symbol[(symbol_type[calc][i])]) && mouse_x<posx+pos_symbol[calc][i][0]+(20*size_symbol[(symbol_type[calc][i])])
&& mouse_y>posy+pos_symbol[calc][i][1]-(20*size_symbol[(symbol_type[calc][i])]) && mouse_y<posy+pos_symbol[calc][i][1]+(20*size_symbol[(symbol_type[calc][i])]))
{
symbol_is_selected[calc][i]=toggle(symbol_is_selected[calc][i]);
view_plot_calc_number_is=calc;
if(symbol_is_selected[calc][i]==1)
{
last_selected_symbol_is=i;
symbol_selected_type=symbol_type[calc][i];
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
if(index_text_auto_close==1){substract_a_window(W_NAME);}
 return(0);
}


int draw_channel_of_symbol( int calc, int symb, int plotx, int ploty)
{
int rayon=15;
 Circle ChannelProp(Vec2D(plotx,ploty),rayon);
 switch( symbol_is_selected[calc][symb])
 {
 case 0:
 ChannelProp.Draw(CouleurPlotFill);
 break;
 case 1:
 ChannelProp.Draw(CouleurLigne);
 break;
 }
 ChannelProp.DrawOutline(CouleurPlotLine);
 if(symbol_channel_is[calc][symb]<10)
 {
 petitchiffrenoir.Print(ol::ToString(symbol_channel_is[calc][symb] ), (int)(plotx),(int)(ploty+(rayon/4)));
 }
 else if(symbol_channel_is[calc][symb]>=10 && symbol_channel_is[calc][symb]<100)
 {
 petitchiffrenoir.Print(ol::ToString(symbol_channel_is[calc][symb] ), (int)(plotx-(rayon/1.7)),(int)(ploty+(rayon/4)));
 }
 else
 {
  petitchiffrenoir.Print(ol::ToString(symbol_channel_is[calc][symb] ), plotx-(rayon/2),ploty+(rayon/4));
 }
 return(0);
}

int draw_gels_of_a_symbol(int calc, int symb, int plotx, int ploty)
{
for(int i=0;i<3;i++)
{
if(plot_show_options[i+2]==1 && gelat[calc][symb][i]!=0 )
{
switch(gelat_family[calc][symb][i])
{
case 0:
sprintf(temp_plot_info,"L.%d",gelat[calc][symb][i]);
break;
case 1:
sprintf(temp_plot_info,"R.%d",gelat[calc][symb][i]);
break;
case 2:
sprintf(temp_plot_info,"G.%d",gelat[calc][symb][i]);
break;
case 3:
sprintf(temp_plot_info,"A.%d",gelat[calc][symb][i]);
break;
default:
sprintf(temp_plot_info,"");
break;
}
petitchiffrenoir.Print(temp_plot_info,plotx+10,(int)(ploty+(i*10)));
}
}
 return(0);
}

int plot_draw_symbol_pc( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=40.0*size_symbol;

Circle lentille(Vec2D(plotx,ploty),taille_x);
lentille.RotateBy(-angle_pc*6.5);
lentille.SetRadius(taille_x/2);
lentille.DrawSlice(CouleurPlotLine,0, PI);

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.DrawOutline(CouleurPlotLine);
carcasse.Draw(CouleurPlotFill);
lentille.SetRadius((taille_x/2)-(4*size_symbol));
lentille.Draw(CouleurPlotFill);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
lentille.Draw(CouleurLigne);
}


if( symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{

if(plot_show_options[0]==1)
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],
(int)(ploty-(taille_x*2)-10)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]);

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}

}


 return(0);
}

int plot_draw_symbol_fresnel( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol , int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=40.0*size_symbol;

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2)-(5.0*size_symbol),ploty-(5*size_symbol)));
carcasse.Add(Vec2D(plotx+(taille_x/2)-(10.0*size_symbol),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2)-(15.0*size_symbol),ploty-(5*size_symbol)));
carcasse.Add(Vec2D(plotx+(taille_x/2)-(20.0*size_symbol),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2)-(25.0*size_symbol),ploty-(5*size_symbol)));
carcasse.Add(Vec2D(plotx+(taille_x/2)-(30.0*size_symbol),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2)-(35.0*size_symbol),ploty-(5*size_symbol)));

carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.Draw(CouleurPlotFill);
carcasse.DrawOutline(CouleurPlotLine);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
}

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_x*2)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));
if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,
plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}

}


return(0);
}


int plot_draw_symbol_decoupe_1(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=80.0*size_symbol;

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty-(taille_y/2)));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));

Poly fenetre;
fenetre.Add(Vec2D(plotx-(taille_x/2),ploty+(12*size_symbol)));
fenetre.Add(Vec2D(plotx+(taille_x/2),ploty+(17*size_symbol)));
fenetre.SetPivot(Vec2D(plotx,ploty));
fenetre.RotateBy(angle_pc*(6.5));

Poly poignee;
poignee.Add(Vec2D(plotx-(12*size_symbol),ploty+(taille_y/2)));
poignee.Add(Vec2D(plotx-(12*size_symbol),ploty+(taille_y/2)+(8*size_symbol)));
poignee.Add(Vec2D(plotx+(12*size_symbol),ploty+(taille_y/2)+(8*size_symbol)));
poignee.Add(Vec2D(plotx+(12*size_symbol),ploty+(taille_y/2)));
poignee.SetPivot(Vec2D(plotx,ploty));
poignee.RotateBy(angle_pc*(6.5));


carcasse.Draw(CouleurPlotFill);
poignee.Draw(CouleurPlotFill);
if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
poignee.Draw(CouleurLigne);
}
poignee.DrawOutline(CouleurPlotLine);
carcasse.DrawOutline(CouleurPlotLine);
fenetre.DrawOutline(CouleurPlotLine);

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+100-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,
plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
return(0);
}

int plot_draw_symbol_decoupe_2(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=80.0*size_symbol;

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty-(taille_y/2)));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));

Poly fenetre;
fenetre.Add(Vec2D(plotx-(taille_x/2),ploty+(12*size_symbol)));
fenetre.Add(Vec2D(plotx+(taille_x/2),ploty+(17*size_symbol)));
fenetre.SetPivot(Vec2D(plotx,ploty));
fenetre.RotateBy(angle_pc*(6.5));

Poly poignee;
poignee.Add(Vec2D(plotx-(12*size_symbol),ploty+(taille_y/2)));
poignee.Add(Vec2D(plotx-(12*size_symbol),ploty+(taille_y/2)+(8*size_symbol)));
poignee.Add(Vec2D(plotx+(12*size_symbol),ploty+(taille_y/2)+(8*size_symbol)));
poignee.Add(Vec2D(plotx+(12*size_symbol),ploty+(taille_y/2)));
poignee.SetPivot(Vec2D(plotx,ploty));
poignee.RotateBy(angle_pc*(6.5));


Poly foc;
foc.Add(Vec2D(plotx-(taille_x/2)+(10*size_symbol),ploty-(10*size_symbol)));
foc.Add(Vec2D(plotx+(taille_x/2)-(10*size_symbol),ploty-(10*size_symbol)));
foc.Add(Vec2D(plotx,ploty-(taille_x/2)-(10*size_symbol)));


foc.SetPivot(Vec2D(plotx,ploty));
foc.RotateBy(angle_pc*(6.5));



carcasse.Draw(CouleurPlotFill);
poignee.Draw(CouleurPlotFill);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
poignee.Draw(CouleurLigne);
}
carcasse.DrawOutline(CouleurPlotLine);
poignee.DrawOutline(CouleurPlotLine);
fenetre.DrawOutline(CouleurPlotLine);

foc.DrawOutline(CouleurPlotLine);

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+100-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,
plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
return(0);
}


int plot_draw_symbol_decoupe_3(int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=80.0*size_symbol;

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty-(taille_y/2)));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));

Poly fenetre;
fenetre.Add(Vec2D(plotx-(taille_x/2),ploty+(12*size_symbol)));
fenetre.Add(Vec2D(plotx+(taille_x/2),ploty+(17*size_symbol)));
fenetre.SetPivot(Vec2D(plotx,ploty));
fenetre.RotateBy(angle_pc*(6.5));

Poly poignee;
poignee.Add(Vec2D(plotx-(12*size_symbol),ploty+(taille_y/2)));
poignee.Add(Vec2D(plotx-(12*size_symbol),ploty+(taille_y/2)+(8*size_symbol)));
poignee.Add(Vec2D(plotx+(12*size_symbol),ploty+(taille_y/2)+(8*size_symbol)));
poignee.Add(Vec2D(plotx+(12*size_symbol),ploty+(taille_y/2)));
poignee.SetPivot(Vec2D(plotx,ploty));
poignee.RotateBy(angle_pc*(6.5));


Poly foc;
foc.Add(Vec2D(plotx-(taille_x/2)+(10*size_symbol),ploty-(25*size_symbol)));
foc.Add(Vec2D(plotx+(taille_x/2)-(10*size_symbol),ploty-(25*size_symbol)));
foc.Add(Vec2D(plotx+(taille_x/2)-(10*size_symbol),ploty-(10*size_symbol)));
foc.Add(Vec2D(plotx-(taille_x/2)+(10*size_symbol),ploty-(10*size_symbol)));
foc.SetPivot(Vec2D(plotx,ploty));
foc.RotateBy(angle_pc*(6.5));


carcasse.Draw(CouleurPlotFill);
poignee.Draw(CouleurPlotFill);
if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
poignee.Draw(CouleurLigne);
}
carcasse.DrawOutline(CouleurPlotLine);
poignee.DrawOutline(CouleurPlotLine);
fenetre.DrawOutline(CouleurPlotLine);
foc.DrawOutline(CouleurPlotLine);

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+100-(taille_y/2))+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]);

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
return(0);
}

int plot_draw_symbol_Par_1( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=40.0*size_symbol;

Circle lentille(Vec2D(plotx,ploty),taille_x);
lentille.RotateBy(-angle_pc*6.5);
lentille.SetRadius(taille_x/2);
lentille.DrawSlice(CouleurPlotLine,0, PI);

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx,ploty+(taille_y)));

carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));

carcasse.Draw(CouleurPlotFill);



carcasse.DrawOutline(CouleurPlotLine);
lentille.SetRadius((taille_x/2)-(4*size_symbol));
lentille.Draw(CouleurPlotFill);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
lentille.Draw(CouleurLigne);
}

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y*1.5)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2))+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]);

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
 return(0);
}



int plot_draw_symbol_Par_2( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=40.0*size_symbol;

Circle lentille(Vec2D(plotx,ploty),taille_x);
lentille.RotateBy(-angle_pc*6.5);
lentille.SetRadius(taille_x/2);
lentille.DrawSlice(CouleurPlotLine,0, PI);

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx,ploty+(taille_y)));

carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.DrawOutline(CouleurPlotLine);
carcasse.Draw(CouleurPlotFill);

lentille.SetRadius((taille_x/2)-(8*size_symbol));
lentille.Draw(CouleurPlotFill);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
lentille.Draw(CouleurLigne);
}


if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y*1.5)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
 return(0);
}


int plot_draw_symbol_Par_3( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=40.0*size_symbol;

Circle lentille(Vec2D(plotx,ploty),taille_x);
lentille.RotateBy(-angle_pc*6.5);
lentille.SetRadius(taille_x/2);
lentille.DrawSlice(CouleurPlotLine,0, PI);

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx,ploty+(taille_y)));

carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.DrawOutline(CouleurPlotLine);
carcasse.Draw(CouleurPlotFill);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
}

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y*1.5)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
 return(0);
}


int plot_draw_symbol_Par_4( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=40.0*size_symbol;

Circle lentille(Vec2D(plotx,ploty),taille_x);
lentille.RotateBy(-angle_pc*6.5);
lentille.SetRadius(taille_x/2);
lentille.DrawSlice(CouleurPlotLine,0, PI);

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx,ploty+(taille_y)));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.Draw(CouleurPlotLine);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
lentille.DrawSlice(CouleurLigne,0, PI);
}

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y*1.5)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));


draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,
plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}

}
 return(0);
}



int plot_draw_symbol_Horiziode_assym( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=60.0*size_symbol;
float taille_y=40.0*size_symbol;

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y/2)));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.Draw(CouleurPlotFill);
if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
}
carcasse.DrawOutline(CouleurPlotLine);

Poly lampe;
lampe.Add(Vec2D(plotx-(taille_x/2)+(10*size_symbol),ploty+(taille_y/2)-(10*size_symbol)));
lampe.Add(Vec2D(plotx+(taille_x/2)-(10*size_symbol),ploty+(taille_y/2)-(10*size_symbol)));
lampe.Add(Vec2D(plotx+(taille_x/2)-(10*size_symbol),ploty+(taille_y/2)-(8*size_symbol)));
lampe.Add(Vec2D(plotx-(taille_x/2)+(10*size_symbol),ploty+(taille_y/2)-(8*size_symbol)));
lampe.SetPivot(Vec2D(plotx,ploty));
lampe.RotateBy(angle_pc*(6.5));
lampe.Draw(CouleurPlotLine);

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2))+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]);

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,
plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
 return(0);
}

int plot_draw_symbol_Horiziode_sym( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=60.0*size_symbol;
float taille_y=40.0*size_symbol;

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y/2)));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.Draw(CouleurPlotFill);
if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
}
carcasse.DrawOutline(CouleurPlotLine);

Poly lampe;
lampe.Add(Vec2D(plotx-(taille_x/2)+(10*size_symbol),ploty));
lampe.Add(Vec2D(plotx+(taille_x/2)-(10*size_symbol),ploty));

lampe.Add(Vec2D(plotx+(taille_x/2)-(10*size_symbol),ploty+(2*size_symbol)));
lampe.Add(Vec2D(plotx-(taille_x/2)+(10*size_symbol),ploty+(2*size_symbol)));
lampe.SetPivot(Vec2D(plotx,ploty));
lampe.RotateBy(angle_pc*(6.5));
lampe.Draw(CouleurPlotLine);

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
 return(0);
}

int plot_draw_symbol_BT( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=40.0*size_symbol;
float taille_y=40.0*size_symbol;


Circle lentille(Vec2D(plotx,ploty),taille_x);
lentille.RotateBy(-angle_pc*6.5);
lentille.SetRadius(taille_x);
lentille.DrawSlice(CouleurPlotLine,0, PI);

Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));

carcasse.Draw(CouleurPlotLine);
lentille.SetRadius((taille_x)-(4*size_symbol));
lentille.DrawSlice(CouleurPlotLine,0,PI);

if( symbol_is_selected[plot_calc_number_is][num_symbol]==1)
{
carcasse.Draw(CouleurLigne);
carcasse.DrawOutline(CouleurPlotLine);
lentille.DrawSlice(CouleurLigne,0,PI);
}


if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y*1.5)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2)+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]));

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
 return(0);
}

int plot_draw_symbol_rampe_brabo( int plotx, int ploty, float size_symbol, float  angle_pc, int num_symbol, int plot_calc_number_is)
{
float taille_x=80.0*size_symbol;
float taille_y=20.0*size_symbol;


Poly carcasse;
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty-(taille_y/2)));
carcasse.Add(Vec2D(plotx-(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty+(taille_y/2)));
carcasse.Add(Vec2D(plotx+(taille_x/2),ploty-(taille_y/2)));
carcasse.SetPivot(Vec2D(plotx,ploty));
carcasse.RotateBy(angle_pc*(6.5));
carcasse.Draw(CouleurPlotLine);

if(symbol_channel_is[plot_calc_number_is][num_symbol]!=0 && num_symbol>0)
{
if(plot_show_options[0]==1 )
draw_channel_of_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][0][0],(int)(ploty-(taille_y)+relatif_plot_xy[plot_calc_number_is][num_symbol][0][1]));

if(plot_show_options[1]==1 )
petitchiffrenoir.Print(descriptif_projecteurs[(symbol_channel_is[plot_calc_number_is][num_symbol])],
plotx-50+relatif_plot_xy[plot_calc_number_is][num_symbol][1][0],(int)(ploty+50-(taille_y/2))+relatif_plot_xy[plot_calc_number_is][num_symbol][1][1]);

draw_gels_of_a_symbol(plot_calc_number_is,num_symbol,
plotx+relatif_plot_xy[plot_calc_number_is][num_symbol][2][0],ploty+relatif_plot_xy[plot_calc_number_is][num_symbol][2][1]);

if(plot_show_options[5]==1 && symbol_dimmer_is[plot_calc_number_is][num_symbol]!=0 )
{
sprintf(temp_plot_info,"d:%d",symbol_dimmer_is[plot_calc_number_is][num_symbol]);
petitchiffrenoir.Print(temp_plot_info,plotx+10+relatif_plot_xy[plot_calc_number_is][num_symbol][3][0],(int)(ploty+(taille_y+20)+relatif_plot_xy[plot_calc_number_is][num_symbol][3][1]));
}
}
return(0);
}



//////////////////////MENUS/////////////////////////////////////////////////////

int plot_symbol_list(int plotx,int ploty)
{

Rect PlotSymbList(Vec2D(plotx,ploty),Vec2D(205,140));
PlotSymbList.SetRoundness(rondeur_fader);
PlotSymbList.DrawOutline(CouleurPlotLine.WithAlpha(0.4));

Rect UnderName(Vec2D(plotx+10,ploty+5),Vec2D(185,20));
UnderName.SetRoundness(rondeur_fader/3);
switch(index_edit_symbol_plot)
{
case 0:
UnderName.Draw(CouleurPlotLine.WithAlpha(0.4));
break;
case 1:
UnderName.Draw(CouleurSurvol);
break;
}
UnderName.DrawOutline(CouleurPlotLine.WithAlpha(0.4));
petitchiffrenoir.Print(symbol_nickname[symbol_selected_type],plotx+12,ploty+18);
//up
Line(Vec2D(plotx+12,ploty+50),Vec2D(plotx+28,ploty+50)).Draw(CouleurNoir);
Line(Vec2D(plotx+12,ploty+50),Vec2D(plotx+20,ploty+36)).Draw(CouleurNoir);
Line(Vec2D(plotx+28,ploty+50),Vec2D(plotx+20,ploty+36)).Draw(CouleurNoir);
//down
Line(Vec2D(plotx+12,ploty+69),Vec2D(plotx+28,ploty+69)).Draw(CouleurNoir);
Line(Vec2D(plotx+12,ploty+69),Vec2D(plotx+20,ploty+83)).Draw(CouleurNoir);
Line(Vec2D(plotx+28,ploty+69),Vec2D(plotx+20,ploty+83)).Draw(CouleurNoir);
petitchiffrenoir.Print(ol::ToString(symbol_selected_type),plotx+13,ploty+62);


//slider size symbol

petitchiffrenoir.Print("Symbol Size",plotx+45,ploty+42);
petitchiffrenoir.Print(ol::ToString(size_symbol[symbol_selected_type]),plotx+108,ploty+63);
Rect symbol_sizer_frame(Vec2D(plotx+50,ploty+55),Vec2D(50,10));
Rect symbol_sizer_level(Vec2D(plotx+50,ploty+55),Vec2D(50.0*size_symbol[symbol_selected_type],10));
switch(index_edit_symbol_plot)
{
case 0:
symbol_sizer_level.Draw(CouleurPlotLine.WithAlpha(0.4));
break;
case 1:
symbol_sizer_level.Draw(CouleurFader);
break;
}
symbol_sizer_frame.DrawOutline(CouleurPlotLine);

Rect edit_symbol_frame(Vec2D(plotx+40,ploty+80),Vec2D(105,20));
edit_symbol_frame.SetRoundness(rondeur_fader/3);
edit_symbol_frame.Draw(CouleurBlind.WithAlpha(index_edit_symbol_plot));
edit_symbol_frame.DrawOutline(CouleurPlotLine);
petitchiffrenoir.Print("Edit the Symbol",plotx+45,ploty+92);

Rect add_symbol_frame(Vec2D(plotx+40,ploty+110),Vec2D(80,20));
add_symbol_frame.SetRoundness(rondeur_fader/3);
add_symbol_frame.DrawOutline(CouleurPlotLine);
petitchiffrenoir.Print("Add To Plot",plotx+45,ploty+122);
petitchiffrenoir.Print(ol::ToString(nbre_symbols_on_plot[view_plot_calc_number_is]),plotx+15,ploty+122);


//affichage symbole
switch(symbol_selected_type)
{
case 0:     //PC 500 ou 650
plot_draw_symbol_pc(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 1:     //PC 1kw
plot_draw_symbol_pc(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 2:     //PC2kw
plot_draw_symbol_pc(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 3:    //fresnel 1kw
plot_draw_symbol_fresnel(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 4:    //fresnel 2kw
plot_draw_symbol_fresnel(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 5:    //fresnel 5kw
plot_draw_symbol_fresnel(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 6: //dec 1kw longue
plot_draw_symbol_decoupe_1(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 7: //dec 1kw mid
plot_draw_symbol_decoupe_2(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 8: //dec 1kw wide
plot_draw_symbol_decoupe_3(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 9: //dec 2kw
plot_draw_symbol_decoupe_1(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 10: //dec 2kw
plot_draw_symbol_decoupe_2(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 11: //dec 2kw
plot_draw_symbol_decoupe_3(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 12: //PAR CP60
plot_draw_symbol_Par_1(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 13: //PAR CP61
plot_draw_symbol_Par_2(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 14: //PAR CP62
plot_draw_symbol_Par_3(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 15: //PAR CP95
plot_draw_symbol_Par_4(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 16://par 56 CP60
plot_draw_symbol_Par_1(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 17://par 56 CP61
plot_draw_symbol_Par_2(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 18://par 56 CP62
 plot_draw_symbol_Par_3(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 19://Par 36
plot_draw_symbol_Par_4(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 20://par 20
plot_draw_symbol_Par_3(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 21://par 16
plot_draw_symbol_Par_1(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 22://horiziode assymetrique
plot_draw_symbol_Horiziode_assym(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 23://horiziode symetrique
plot_draw_symbol_Horiziode_sym(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 24://hallogene de chantier
plot_draw_symbol_Horiziode_sym(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 25://BT250w
plot_draw_symbol_BT(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 26://BT500W
plot_draw_symbol_BT(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
case 27://rampe brabo
plot_draw_symbol_rampe_brabo(plotx+160, ploty+75 , size_symbol[symbol_selected_type], 0, 0, 0);
break;
default:
break;
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
 symbol_selected_type++;
 if(symbol_selected_type>max_symbol_type){symbol_selected_type=0;}
 if(index_edit_light_plot==1){change_symbol_type(view_plot_calc_number_is,symbol_selected_type);}
   mouse_released=1;
 }
 else if(  mouse_y>ploty+69 && mouse_y<ploty+83) //DOWN
 {
  symbol_selected_type--;
  if(symbol_selected_type<0){symbol_selected_type=max_symbol_type;}
  if(index_edit_light_plot==1){change_symbol_type(view_plot_calc_number_is,symbol_selected_type);}
  mouse_released=1;
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
add_a_symbol_to_plot(view_plot_calc_number_is);
mouse_released=1;
}



//edition de la taille du symbol
if(index_edit_symbol_plot==1 )
{

if( mouse_x>=plotx+10 && mouse_x<=plotx+10+185 && mouse_y>ploty+5 && mouse_y<ploty+5+20 && index_type==1)
{
edit_symbol_name();
mouse_released=1;
}
else if( mouse_x>=plotx+50 && mouse_x<=plotx+50+50+5 && mouse_y>ploty+55 && mouse_y<ploty+55+10)
{
size_symbol[symbol_selected_type]=((float)(mouse_x-(plotx+50)))/50;
if(size_symbol[symbol_selected_type]<0.1){size_symbol[symbol_selected_type]=0.2;}
if (size_symbol[symbol_selected_type]>1){size_symbol[symbol_selected_type]=1.0;}
}
}
//fin focus window
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
for (int l=0;l<7;l++)
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
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{symbol_channel_is[view_plot_calc_number_is][i]= tnum;  }
}
}
reset_numeric_entry();
numeric_postext=0;
mouse_released=1;
}
break;
case 1: //"LIST:");plotx+20,ploty+65+(20*l)));
if(index_type==1 && mouse_x>plotx+20 && mouse_x<plotx+20+175 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=0;
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
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
if(index_text_auto_close==1){substract_a_window(W_NAME);}
mouse_released=1;
}
break;
case 2://"GEL 1:");
if(mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
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
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat_family[view_plot_calc_number_is][i][0]++;
if(gelat_family[view_plot_calc_number_is][i][0]>nbre_gelats_manufact){gelat_family[view_plot_calc_number_is][i][0]=0;}
}
}
mouse_released=1;
}
break;
case 3: //"GEL 2:");
if(mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat[view_plot_calc_number_is][i][1]= tnum;
}
reset_numeric_entry();
numeric_postext=0;
}
mouse_released=1;
}
else if(mouse_x>plotx+130 && mouse_x<plotx+130+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat_family[view_plot_calc_number_is][i][1]++;
if(gelat_family[view_plot_calc_number_is][i][1]>nbre_gelats_manufact){gelat_family[view_plot_calc_number_is][i][1]=0;}
}
}
mouse_released=1;
}
break;
case 4: //"GEL 3:");
if(mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
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
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
gelat_family[view_plot_calc_number_is][i][2]++;
if(gelat_family[view_plot_calc_number_is][i][2]>nbre_gelats_manufact){gelat_family[view_plot_calc_number_is][i][2]=0;}
}
}
mouse_released=1;
}
break;
case 5: //"DIMMER:");
if(mouse_x>plotx+100 && mouse_x<plotx+100+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18)
{
int tnum=atoi(numeric);
if(tnum>=0 && tnum<=512)
{
for(int i=1;i<nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1)
{
symbol_dimmer_is[view_plot_calc_number_is][i]= tnum;
}
}
}
reset_numeric_entry();
numeric_postext=0;
if(index_build_patch_from_plot==1)
{
repatch_from_plot(view_plot_calc_number_is);
}
mouse_released=1;
}
break;
default:
break;
}
}

//choix des  relatifs xy
for(int i=0;i<4;i++)
{
if(index_click_inside_relativ_xy==0 && mouse_x>plotx+5 && mouse_x<plotx+5+10 && mouse_y>ploty+220+(20*i) &&  mouse_y<ploty+220+(20*i)+10)
{
if(adjust_xy_type==i)
{
adjust_xy_type=999;//desaffectation
index_edit_relativ_xy=0;
}
else
{
adjust_xy_type=i;
index_edit_relativ_xy=1;
}
mouse_released=1;
}
}


//repatch en direct
if(mouse_x>plotx+20 && mouse_x<plotx+20+175 && mouse_y>ploty+300 && mouse_y<ploty+300+18)
{
index_build_patch_from_plot=toggle(index_build_patch_from_plot);
mouse_released=1;
}
}


//edition des relatifs dans la zone de tarcking
if( mouse_x > plotx+110 && mouse_x<plotx+110+70 && mouse_y>ploty+210 && mouse_y<ploty+210+70)
{

if(index_main_clear==1)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1 )
{
 relatif_plot_xy[view_plot_calc_number_is][i][adjust_xy_type][0]=0;
 relatif_plot_xy[view_plot_calc_number_is][i][adjust_xy_type][1]=0;
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
temp_relativ_mouse_x=mouse_x;
temp_relativ_mouse_y=mouse_y;
store_relativ_xy_position_of_activ_calc(view_plot_calc_number_is);
}
else if (index_click_inside_relativ_xy==1 && mouse_button==1 && mouse_released==0 && adjust_xy_type<4)
{
//set_mouse_range(plotx+110,plotx+210, 70, 70);
rlativ_xm=mouse_x-(plotx+110+35);
rlativ_ym=mouse_y-(ploty+210+35);

for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1 )
{
 relatif_plot_xy[view_plot_calc_number_is][i][adjust_xy_type][0]=temp_relatif_plot_xy_array[i][0]+ rlativ_xm;
 relatif_plot_xy[view_plot_calc_number_is][i][adjust_xy_type][1]=temp_relatif_plot_xy_array[i][1]+ rlativ_ym;
}
}
}
}
}

}
 return(0);
}

int symbol_edition_options(int plotx, int ploty)
{
char TextPlot[25];

Rect PlotOptionsEdit_Little(Vec2D(plotx,ploty),Vec2D(50,18));
PlotOptionsEdit_Little.SetRoundness(rondeur_fader/5);
Rect PlotOptionsEdit_Long(Vec2D(plotx,ploty),Vec2D(175,18));
PlotOptionsEdit_Long.SetRoundness(rondeur_fader/5);
Rect PlotOptionView(Vec2D(plotx,ploty+70), Vec2D(10,10));

char gelat_marque[25];

//properties
for (int l=0;l<7;l++)
{
PlotOptionView.MoveTo(Vec2D(plotx+5,ploty+70+(20*l)));
PlotOptionView.DrawOutline(CouleurPlotLine);
switch(l)
{
case 0:
sprintf(TextPlot,"CHANNEL");
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+100,ploty+65+(20*l)));
PlotOptionsEdit_Little.Draw(CouleurPlotLine.WithAlpha(0.2));
petitchiffrenoir.Print(ol::ToString(symbol_channel_is[view_plot_calc_number_is][last_selected_symbol_is]),plotx+105,ploty+78+(20*l));

if(index_edit_light_plot==1 && mouse_x>plotx+100 && mouse_x<plotx+100+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18 )
{
PlotOptionsEdit_Little.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
break;
case 1:
sprintf(TextPlot,"");
PlotOptionsEdit_Long.MoveTo(Vec2D(plotx+20,ploty+65+(20*l)));
PlotOptionsEdit_Long.Draw(CouleurPlotLine.WithAlpha(0.2));
petitchiffrenoir.Print( descriptif_projecteurs[(symbol_channel_is[view_plot_calc_number_is][last_selected_symbol_is])],plotx+25,ploty+78+(20*l));
if(index_edit_light_plot==1 && mouse_x>plotx+20 && mouse_x<plotx+20+175 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18 )
{
PlotOptionsEdit_Long.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
break;
case 2:
sprintf(TextPlot,"GEL 1:");
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+70,ploty+65+(20*l)));
PlotOptionsEdit_Little.Draw(CouleurPlotLine.WithAlpha(0.2));
petitchiffrenoir.Print(ol::ToString(gelat[view_plot_calc_number_is][last_selected_symbol_is][0]),plotx+75,ploty+78+(20*l));
if(index_edit_light_plot==1 && mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18 )
{
PlotOptionsEdit_Little.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+130,ploty+65+(20*l)));
switch(gelat_family[view_plot_calc_number_is][last_selected_symbol_is][0])
{
case 0:
sprintf(gelat_marque,"Lee");
PlotOptionsEdit_Little.Draw(CouleurBleuProcedure.WithAlpha(0.5));
break;
case 1:
sprintf(gelat_marque,"Rosco");
PlotOptionsEdit_Little.Draw(CouleurBlind.WithAlpha(0.5));
break;
case 2:
sprintf(gelat_marque,"GamCol.");
PlotOptionsEdit_Little.Draw(CouleurGreen.WithAlpha(0.5));
break;
case 3:
sprintf(gelat_marque,"Apollo");
PlotOptionsEdit_Little.Draw(CouleurSelection.WithAlpha(0.5));
break;
default:
break;
}
petitchiffrenoir.Print(gelat_marque,plotx+135,ploty+78+(20*l));
break;
case 3:
sprintf(TextPlot,"GEL 2:");
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+70,ploty+65+(20*l)));
PlotOptionsEdit_Little.Draw(CouleurPlotLine.WithAlpha(0.2));
petitchiffrenoir.Print(ol::ToString(gelat[view_plot_calc_number_is][last_selected_symbol_is][1]),plotx+75,ploty+78+(20*l));
if(index_edit_light_plot==1 && mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18 )
{
PlotOptionsEdit_Little.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+130,ploty+65+(20*l)));
switch(gelat_family[view_plot_calc_number_is][last_selected_symbol_is][1])
{
case 0:
sprintf(gelat_marque,"Lee");
PlotOptionsEdit_Little.Draw(CouleurBleuProcedure.WithAlpha(0.5));
break;
case 1:
sprintf(gelat_marque,"Rosco");
PlotOptionsEdit_Little.Draw(CouleurBlind.WithAlpha(0.5));
break;
case 2:
sprintf(gelat_marque,"GamCol.");
PlotOptionsEdit_Little.Draw(CouleurGreen.WithAlpha(0.5));
break;
case 3:
sprintf(gelat_marque,"Apollo");
PlotOptionsEdit_Little.Draw(CouleurSelection.WithAlpha(0.5));
break;
default:
break;
}
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+130,ploty+65+(20*l)));
petitchiffrenoir.Print(gelat_marque,plotx+135,ploty+78+(20*l));
break;
case 4:
sprintf(TextPlot,"GEL 3:");
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+70,ploty+65+(20*l)));
PlotOptionsEdit_Little.Draw(CouleurPlotLine.WithAlpha(0.2));
petitchiffrenoir.Print(ol::ToString(gelat[view_plot_calc_number_is][last_selected_symbol_is][2]),plotx+75,ploty+78+(20*l));
if(index_edit_light_plot==1 && mouse_x>plotx+70 && mouse_x<plotx+70+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18 )
{
PlotOptionsEdit_Little.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+130,ploty+65+(20*l)));
switch(gelat_family[view_plot_calc_number_is][last_selected_symbol_is][2])
{
case 0:
sprintf(gelat_marque,"Lee");
PlotOptionsEdit_Little.Draw(CouleurBleuProcedure.WithAlpha(0.5));
break;
case 1:
sprintf(gelat_marque,"Rosco");
PlotOptionsEdit_Little.Draw(CouleurBlind.WithAlpha(0.5));
break;
case 2:
sprintf(gelat_marque,"GamCol.");
PlotOptionsEdit_Little.Draw(CouleurGreen.WithAlpha(0.5));
break;
case 3:
sprintf(gelat_marque,"Apollo");
PlotOptionsEdit_Little.Draw(CouleurSelection.WithAlpha(0.5));
break;
default:
break;
}
petitchiffrenoir.Print(gelat_marque,plotx+135,ploty+78+(20*l));
break;
case 5:
sprintf(TextPlot,"DIMMER:");
PlotOptionsEdit_Little.MoveTo(Vec2D(plotx+100,ploty+65+(20*l)));
PlotOptionsEdit_Little.Draw(CouleurPlotLine.WithAlpha(0.2));
if(index_edit_light_plot==1 && mouse_x>plotx+100 && mouse_x<plotx+100+50 && mouse_y>ploty+65+(20*l) && mouse_y<ploty+65+(20*l)+18 )
{
PlotOptionsEdit_Little.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
petitchiffrenoir.Print(ol::ToString(symbol_dimmer_is[view_plot_calc_number_is][last_selected_symbol_is]),plotx+105,ploty+78+(20*l));
break;
case 6:
sprintf(TextPlot,"SHOW SYMBOL ID");
break;
default:
sprintf(TextPlot,"-");
break;
}
PlotOptionView.Draw(CouleurPlotLine.WithAlpha(plot_show_options[l]));
petitchiffrenoir.Print(TextPlot,plotx+25,ploty+78+(20*l));
}


//int relatifs xy
petitchiffrenoir.Print("Adjust XY",plotx+115,ploty+215);
for(int i=0;i<4;i++)
{
PlotOptionView.MoveTo(Vec2D(plotx+5,ploty+220+(20*i)));
if(adjust_xy_type==i)
{
PlotOptionView.Draw(CouleurPlotLine);
}
PlotOptionView.DrawOutline(CouleurPlotLine.WithAlpha(0.5));
switch(i)
{
case 0:
sprintf(TextPlot,"Channel");
break;
case 1:
sprintf(TextPlot,"Name");
break;
case 2:
sprintf(TextPlot,"Gels");
break;
case 3:
sprintf(TextPlot,"Dimmer");
break;
default:
sprintf(TextPlot,"-");
break;
}
petitchiffrenoir.Print(TextPlot,plotx+25,ploty+228+(20*i));
}

Rect AeraDrawAdjust(Vec2D(plotx+110,ploty+220),Vec2D(70,70));
AeraDrawAdjust.DrawOutline(CouleurPlotLine.WithAlpha(0.3));
Rect AeraTemoin(Vec2D(plotx+140+rlativ_xm,ploty+250+rlativ_ym),Vec2D(10,10));
if(index_click_inside_relativ_xy==1 )
{
AeraDrawAdjust.SetLineWidth(2.0);
AeraDrawAdjust.DrawOutline(CouleurFader);

}
if(index_edit_relativ_xy==1)
{
AeraDrawAdjust.Draw(CouleurBlind.WithAlpha(0.3));
AeraTemoin.Draw(CouleurPlotLine.WithAlpha(0.5));
sprintf(TextPlot,"%d . %d",rlativ_xm,rlativ_ym);
petitchiffrenoir.Print(TextPlot,plotx+130,ploty+260);
}

//repatch directly
PlotOptionsEdit_Long.MoveTo(Vec2D(plotx+5,ploty+300));
PlotOptionsEdit_Long.Draw(CouleurPlotLine.WithAlpha(0.5));
PlotOptionsEdit_Long.Draw(CouleurBlind.WithAlpha(index_build_patch_from_plot));
petitchiffrenoir.Print("Direct Re-Patch",plotx+50,ploty+313);

 return(0);
}











int plot_symbol_edition(int plotx,int ploty)
{
Rect PlotSymbEd(Vec2D(plotx,ploty),Vec2D(200,380));
PlotSymbEd.SetRoundness(rondeur_fader);
PlotSymbEd.DrawOutline(CouleurPlotLine.WithAlpha(0.4));
petitchiffrenoir.Print("SELECTED SYMBOLS:",plotx+10,ploty+15);
Line(Vec2D(plotx+10,ploty+20),Vec2D(plotx+130,ploty+20)).Draw(CouleurPlotLine);

//rotation
petitchiffrenoir.Print("Rotate",plotx+10,ploty+33);
petitchiffrenoir.Print(ol::ToString(angle_projo_selectionne),plotx+80,ploty+33);
Rect RotateFrame(Vec2D(plotx+10,ploty+40),Vec2D(100,10));
Rect RotateLevel(Vec2D(plotx+10,ploty+40),Vec2D((angle_projo_selectionne*100),10));
RotateLevel.Draw(CouleurGreen);
RotateFrame.DrawOutline(CouleurPlotLine);

Rect AnglePos(Vec2D(-10,-10),Vec2D(10,10));

for(int l=0;l<3;l++)
{
for(int c=0;c<3;c++)
{
int pos=(l*3) + c;
AnglePos.MoveTo(Vec2D(plotx+140+(c*15),ploty+10+(l*15)));
AnglePos.DrawOutline(CouleurPlotLine.WithAlpha(0.5));
if( mouse_x>plotx+140+(c*15) && mouse_x<plotx+140+(c*15)+10 && mouse_y>ploty+10+(l*15) && mouse_y<ploty+10+(l*15)+10 )
{
AnglePos.Draw(CouleurFader);
}
}
}
AnglePos.MoveTo(Vec2D(plotx+140+15,ploty+10+15));
AnglePos.Draw(CouleurPlotFill);
AnglePos.DrawOutline(CouleurPlotFill);


Rect MySymbAction(Vec2D(plotx, ploty+70),Vec2D(60,18));
MySymbAction.SetRoundness(rondeur_fader/3);

for(int c=0;c<3;c++)
{
for(int l=0;l<2;l++)
{
MySymbAction.MoveTo(Vec2D(plotx+5+(c*65),ploty+70+(l*20)));
MySymbAction.Draw(CouleurPlotLine.WithAlpha(0.5));
if(window_focus_id==W_PLOT && index_edit_light_plot==1 && index_click_inside_relativ_xy==0
&& mouse_x>plotx+5+(c*65) && mouse_x<plotx+5+(c*65)+60 && mouse_y>ploty+70+(l*20) && mouse_y<ploty+70+(l*20)+18)
{
MySymbAction.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
switch(c+(l*3))
{
case 0:
petitchiffre.Print("Dub",plotx+20+(c*65),ploty+82+(l*20));
break;
case 1:
petitchiffre.Print("Delete",plotx+10+(c*65),ploty+82+(l*20));
break;
case 2:
MySymbAction.Draw(CouleurFader.WithAlpha(index_plot_send_to_mode));
petitchiffre.Print("SendTo",plotx+10+(c*65),ploty+82+(l*20));
break;
case 3:
petitchiffre.Print("Down",plotx+15+(c*65),ploty+82+(l*20));
break;
case 4:
petitchiffre.Print("Top",plotx+22+(c*65),ploty+82+(l*20));
break;
case 5:
petitchiffre.Print("UnSelect",plotx+7+(c*65),ploty+82+(l*20));
break;
default:
break;
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
angle_projo_selectionne=((float)(mouse_x-(plotx+10)))/100;
if(angle_projo_selectionne<0.0){angle_projo_selectionne=0.0;}
if (angle_projo_selectionne>1.0){angle_projo_selectionne=1.0;}
affect_angle_to_symbols(view_plot_calc_number_is,angle_projo_selectionne);
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
     angle_projo_selectionne=0.24;
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
     angle_projo_selectionne=0.485;
break;
case 8:
     angle_projo_selectionne=0.59;
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
if(window_focus_id==W_PLOT
   && index_edit_light_plot==1
   && index_click_inside_relativ_xy==0
&& mouse_x>plotx+5+(c*65) && mouse_x<plotx+5+(c*65)+60 && mouse_y>ploty+70+(l*20) && mouse_y<ploty+70+(l*20)+18
&& mouse_button==1 && mouse_released==0)
{
switch(c+(l*3))
{
case 0://"Dub",plotx+20+(c*65),ploty+82+(l*20));
duplicate_selected_symbols(view_plot_calc_number_is);
break;
case 1://"Delete",plotx+10+(c*65),ploty+82+(l*20));
delete_selected_symbols(view_plot_calc_number_is);
break;
case 2://"SendTo"
index_plot_send_to_mode=toggle(index_plot_send_to_mode);
break;
case 3://"Down"
position_down_selected_symbols(view_plot_calc_number_is);
break;
case 4://"Top"
position_on_top(view_plot_calc_number_is);
break;
case 5://"Unselect"
reset_symbols_selected(view_plot_calc_number_is);
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

int plot_menu_bar(int plotx, int ploty)
{
Rect edit_frame(Vec2D(plotx,ploty),Vec2D(35,20));
edit_frame.SetRoundness(rondeur_fader/3);
edit_frame.Draw(CouleurBlind.WithAlpha(index_edit_light_plot));
edit_frame.DrawOutline(CouleurPlotLine);
petitchiffrenoir.Print("Edit",plotx+5,ploty+12);

Rect LayerNum(Vec2D(plotx+45,ploty),Vec2D(10,10));
for(int i=0;i<4;i++)
{
LayerNum.MoveTo(Vec2D(plotx+45+(i*15),ploty-5));
LayerNum.DrawOutline(CouleurPlotLine);
if(show_calc_number[i]==1)
{LayerNum.Draw(CouleurFader);}
LayerNum.MoveTo(Vec2D(plotx+45+(i*15),ploty+10));
if(view_plot_calc_number_is==i)
{LayerNum.Draw(CouleurPlotLine);}
LayerNum.DrawOutline(CouleurLigne.WithAlpha(0.3));
}


Rect MenuBarIs(Vec2D(plotx+130,ploty-5),Vec2D(100,25));
MenuBarIs.SetRoundness(rondeur_fader/2);
MenuBarIs.Draw(CouleurPlotLine);

switch(index_menus_lighting_plot)
{
case 0:
     petitchiffre.Print("LEGEND",plotx+165,ploty+10);
break;
case 1:
     petitchiffre.Print("SYMBOLS",plotx+150,ploty+10);
break;
case 2:
     petitchiffre.Print("BACKGROUND",plotx+140,ploty+10);
break;
default:
break;
}

char temp_h[64];
switch(index_move_plot_view_port)
{

case 0:
sprintf(temp_h,"ViewPort is: X %d Y %d",plot_view_port_x, plot_view_port_y);
break;
case 1:
sprintf(temp_h,"Moving ViewPort: X %d Y %d",plot_view_port_x, plot_view_port_y);
break;
}
petitchiffrenoir.Print(temp_h, plotx+240,ploty+10);

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
if(index_main_clear==0 && index_plot_send_to_mode==0)
{
show_calc_number[i]=toggle(show_calc_number[i]);mouse_released=1;
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
index_plot_send_to_mode=0;
plot_layer_selected=0;
}
}
else if(mouse_y>ploty+10 && mouse_y<ploty+20)
{
reset_symbols_selected(view_plot_calc_number_is);index_click_inside_plot=0;
view_plot_calc_number_is=i;show_calc_number[i]=1;
}
mouse_released=1;
}

}

//menus modes
if(mouse_x>plotx+130 && mouse_x<plotx+130+100 && mouse_y>ploty-5 && mouse_y<ploty-5+25)
{
index_menus_lighting_plot++;
if(index_menus_lighting_plot>2){index_menus_lighting_plot=0;}
mouse_released=1;
}
}
return(0);
}



//sab 02/03/2014  int deroule_repertoire_plans(int xrep, int yrep, char name_of_rep[25])
void deroule_repertoire_plans(int xrep, int yrep, const std::string label)
{
const std::string name_of_rep = label.substr(0,25);
//////////////////////LISTE DOSSIERS ETC///////////////////////////////////////
Canvas::SetClipping( xrep,yrep,xrep+230,yrep+175);

Rect BackDeroule(Vec2D(xrep,yrep+155),Vec2D(210,185));
BackDeroule.SetRoundness(rondeur_fader/3);
BackDeroule.Draw(CouleurPlotLine.WithAlpha(0.4));
petitchiffre.Print("Plans folder (.jpg .bmp .png .tga)",xrep+10,yrep+170);
for (int y=0;y<8;y++)
{
Rect OverFile(Vec2D(xrep+5,(yrep+185+(y*20)-10)),Vec2D(180,20));
OverFile.SetRoundness(rondeur_fader/2);
//affichage qui est selectionné
if(strcmp( Name_of_plane_is,list_import_plans[importplan_selected])==0 && (importplan_selected==(y+line_importplan)))
{OverFile.Draw(CouleurFond.WithAlpha(0.5));}

if( index_editing_theatre_plan==0 && mouse_x>xrep+5 && mouse_x<xrep+5+150 && mouse_y>(yrep+185+(y*20)-10) && mouse_y<(yrep+185+(y*20)+5))
{
OverFile.DrawOutline(CouleurLigne);
}

petitchiffrenoir.Print(list_import_plans[line_importplan+y],xrep+10,yrep+187+(y*20));
}


//////////////////UP DOWN LINE IMPORT/////////////////////
Circle LineUp(Vec2D(xrep+190,yrep+200),12);
LineUp.Draw(CouleurFond);
Circle LineDown(Vec2D(xrep+190,yrep+310),12);
LineDown.Draw(CouleurFond);
if(mouse_x>xrep+190-12 && mouse_x<xrep+190+12)
{
if(mouse_y>yrep+180-12 && mouse_y<yrep+200+12)
{
LineUp.Draw(CouleurSurvol);
}
else if(mouse_y>yrep+290-12 && mouse_y<yrep+310+12)
{
LineDown.Draw(CouleurSurvol);
}
}
petitchiffre.Print("-",xrep+186,yrep+205);
petitchiffre.Print("+",xrep+186,yrep+315);
LineUp.DrawOutline(CouleurLigne);
LineDown.DrawOutline(CouleurLigne);

Canvas::DisableClipping();

Rect BoutonRescan(Vec2D(xrep+150,yrep+345),Vec2D(60,20));
BoutonRescan.SetRoundness(rondeur_fader/4);
BoutonRescan.Draw(CouleurPlotLine.WithAlpha(0.6));
petitchiffre.Print("Rescan !",xrep+155,yrep+357);

if( index_editing_theatre_plan==0 && mouse_x>xrep+150 && mouse_x<xrep+150+60 && mouse_y>(yrep+345) && mouse_y<(yrep+345+20))
{
BoutonRescan.DrawOutline(CouleurLigne);
}

//sab 02/03/2014 return(0);
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
sprintf(Name_of_plane_is,list_import_plans[importplan_selected]);
mouse_released=1;
load_plan_of_theatre(Name_of_plane_is);
}
}

}


//////////////////UP DOWN LINE IMPORT/////////////////////
Circle LineUp(Vec2D(xrep+190,yrep+200),12);
LineUp.Draw(CouleurFond);
Circle LineDown(Vec2D(xrep+190,yrep+310),12);
LineDown.Draw(CouleurFond);
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


int menu_plan(int plotx, int ploty)
{

petitchiffrenoir.Print("BACKGROUND:",plotx+10,ploty+15);
Line(Vec2D(plotx+10,ploty+20),Vec2D(plotx+130,ploty+20)).Draw(CouleurPlotLine);


petitchiffrenoir.Print("Theatre Plot:",plotx+5,ploty+40);

Rect PlotSymbList(Vec2D(plotx,ploty),Vec2D(205,220));
PlotSymbList.SetRoundness(rondeur_fader);
PlotSymbList.DrawOutline(CouleurPlotLine.WithAlpha(0.4));

Rect UnderName(Vec2D(plotx+5,ploty+50),Vec2D(190,20));
UnderName.SetRoundness(rondeur_fader/3);
UnderName.Draw(CouleurPlotLine);
Canvas::SetClipping( plotx+5,ploty+50,plotx+5+190,ploty+50+20);
petitchiffre.Print(Name_of_plane_is,plotx+10,ploty+63);
Canvas::DisableClipping();

char coodr[8];
Rect GridBGSelector(Vec2D(plotx+40,ploty+145),Vec2D(40,20));
GridBGSelector.SetRoundness(3.0);
for(int i=0;i<4;i++)
{

GridBGSelector.MoveTo(Vec2D(plotx+5+(50*i),ploty+90));
GridBGSelector.Draw(CouleurPlotLine.WithAlpha(0.3));

if(mouse_x>plotx+5+(50*i) && mouse_x<plotx+5+(50*i)+45 && mouse_y>ploty+90 && mouse_y<ploty+90+20)
{GridBGSelector.DrawOutline(CouleurLigne.WithAlpha(0.3));}

if(i+1==editing_plan_data_type)
{
GridBGSelector.Draw(CouleurFader);
}
switch(i)
{
case 0:
petitchiffrenoir.Print("X",plotx+20+(50*i),ploty+85);
sprintf(coodr,"%d",position_relative_plan_theatre[0]);
break;
case 1:
petitchiffrenoir.Print("Y",plotx+20+(50*i),ploty+85);
sprintf(coodr,"%d",position_relative_plan_theatre[1]);
break;
case 2:
petitchiffrenoir.Print("Scale X",plotx+5+(50*i),ploty+85);
sprintf(coodr,"%d",taille_relative_plan_theatre[0]);
break;
case 3:
petitchiffrenoir.Print("Scale Y",plotx+5+(50*i),ploty+85);
sprintf(coodr,"%d",taille_relative_plan_theatre[1]);
break;
default:
break;
}
petitchiffrenoir.Print(coodr, plotx+15+(50*i), ploty+102);
}


//rotation
petitchiffrenoir.Print("Rotate",plotx+5,ploty+133);
petitchiffrenoir.Print(ol::ToString(orientation_plan_theatre),plotx+80,ploty+133);
Rect AlphaFrame(Vec2D(plotx+5,ploty+140),Vec2D(100,10));
Rect AlphaLevel(Vec2D(plotx+5,ploty+140),Vec2D((orientation_plan_theatre*100),10));
AlphaLevel.Draw(CouleurGreen);
AlphaFrame.DrawOutline(CouleurPlotLine);


Rect AnglePos(Vec2D(-10,-10),Vec2D(10,10));

for(int l=0;l<3;l++)
{
for(int c=0;c<3;c++)
{
int pos=(l*3) + c;
AnglePos.MoveTo(Vec2D(plotx+140+(c*15),ploty+125+(l*15)));
AnglePos.DrawOutline(CouleurPlotLine.WithAlpha(0.5));
if( mouse_x>plotx+140+(c*15) && mouse_x<plotx+140+(c*15)+10 && mouse_y>ploty+125+(l*15) && mouse_y<ploty+125+(l*15)+10 )
{
AnglePos.Draw(CouleurFader);
}
}
}
AnglePos.MoveTo(Vec2D(plotx+140+15,ploty+125+15));
AnglePos.Draw(CouleurPlotFill);
AnglePos.DrawOutline(CouleurPlotFill);


//alpha plan
petitchiffrenoir.Print("Alpha",plotx+5,ploty+170);
petitchiffrenoir.Print(ol::ToString(alpha_plan),plotx+80,ploty+170);
Rect RotateFrame(Vec2D(plotx+5,ploty+180),Vec2D(100,10));
Rect RotateLevel(Vec2D(plotx+5,ploty+180),Vec2D((alpha_plan*100),10));
RotateLevel.Draw(CouleurPlotLine);
RotateFrame.DrawOutline(CouleurPlotLine);



petitchiffrenoir.Print("Grid:",plotx+5,ploty+210);
GridBGSelector.MoveTo(Vec2D(plotx+40,ploty+195));

GridBGSelector.Draw(CouleurPlotLine.WithAlpha(0.3));
petitchiffrenoir.Print(ol::ToString(plot_quadrillage_size),plotx+50,ploty+210);


//liste des plans
deroule_repertoire_plans(plotx-5,ploty+80,"Plans");


//taille de la fenetre

Rect PlotSize(Vec2D(plotx,ploty+450),Vec2D(205,65));
PlotSize.SetRoundness(rondeur_fader/2);
PlotSize.DrawOutline(CouleurPlotLine.WithAlpha(0.4));

petitchiffrenoir.Print("Plot Window:",plotx+10,ploty+465);

GridBGSelector.MoveTo(Vec2D(plotx+5,ploty+480));
GridBGSelector.Draw(CouleurPlotLine.WithAlpha(0.3));
petitchiffrenoir.Print("Size X",plotx+7,ploty+478);
if(mouse_x>plotx+5 && mouse_x<plotx+5+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
GridBGSelector.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
if(editing_plot_sizex==1){GridBGSelector.Draw(CouleurFader);}
petitchiffrenoir.Print(ol::ToString(plot_window_x_size),plotx+10,ploty+493);


GridBGSelector.MoveTo(Vec2D(plotx+5+50,ploty+480));
GridBGSelector.Draw(CouleurPlotLine.WithAlpha(0.3));
petitchiffrenoir.Print("Size Y",plotx+7+50,ploty+478);
if(mouse_x>plotx+5+50 && mouse_x<plotx+5+50+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
GridBGSelector.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
if(editing_plot_sizey==1){GridBGSelector.Draw(CouleurFader);}
petitchiffrenoir.Print(ol::ToString(plot_window_y_size),plotx+10+50,ploty+493);


 return(0);
}

int logical_menu_plan(int plotx, int ploty)
{

if(window_focus_id==W_PLOT && index_edit_light_plot==1 && editing_plot_sizex==0 && editing_plot_sizey==0 && mouse_button==1 && mouse_released==0 && index_click_inside_relativ_xy==0 && index_click_inside_plot==0)
{

//grille taille
if(index_editing_theatre_plan==0 && mouse_x>plotx+40 && mouse_x<plotx+40+40 && mouse_y>ploty+195 && mouse_y<ploty+195+20)
{
plot_quadrillage_size+=25;
if(plot_quadrillage_size>100){plot_quadrillage_size=0;}
mouse_released=1;
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
taille_relative_plan_theatre[0]=int(numo);
break;
case 3:
taille_relative_plan_theatre[1]=int(numo);
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
  }
}

}

}
  if(index_edit_light_plot==1 && index_editing_theatre_plan==1 && editing_plot_sizex==0 && editing_plot_sizey==0 && index_click_inside_relativ_xy==0 && index_click_inside_plot==0  )
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
   break;
   case 4:
   taille_relative_plan_theatre[1]=old_taille_relative_plan_theatre[1]-moving_plan_relativ_y;
   break;
   default:
   break;
   }
}


//rotation plan
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && mouse_x>=plotx+10 && mouse_x<=plotx+10+100+5 && mouse_y>ploty+140 && mouse_y<ploty+140+10)
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
if( index_editing_theatre_plan==0 &&  mouse_x>plotx+140+(c*15) && mouse_x<plotx+140+(c*15)+10 && mouse_y>ploty+125+(l*15) && mouse_y<ploty+125+(l*15)+10 )
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
if(index_edit_light_plot==1 &&  index_editing_theatre_plan==0 && editing_plot_sizex==0 && editing_plot_sizey==0 && mouse_x>=plotx+10 && mouse_x<=plotx+10+100+5 && mouse_y>ploty+180 && mouse_y<ploty+180+10)
{
alpha_plan=((float)(mouse_x-(plotx+10)))/100;
if(alpha_plan<0.0){alpha_plan=0.0;}
if (alpha_plan>1.0){alpha_plan=1.0;}
}

logical_deroule_repertoire_plans(plotx-5,ploty+80);


//edition taille fenetre plot
if(mouse_x>plotx+5 && mouse_x<plotx+5+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
if(numeric_postext>0)
{
plot_window_x_size=atol(numeric);
if(plot_window_x_size<700){plot_window_x_size=700;}
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

if(mouse_x>plotx+5+50 && mouse_x<plotx+5+50+40 && mouse_y>ploty+480 && mouse_y<ploty+480+20)
{
if(numeric_postext>0)
{
plot_window_y_size=atol(numeric);
if(plot_window_y_size<600){plot_window_y_size=600;}
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
//sorti du mouse_button
if(editing_plot_sizex==1)
{
moving_size_relativ_x=mouse_y-original_posy;
plot_window_x_size=old_plot_sizex-(moving_size_relativ_x*10);
if(plot_window_x_size<700){plot_window_x_size=700;}
}
if(editing_plot_sizey==1)
{
moving_size_relativ_y=mouse_y-original_posy;
plot_window_y_size=old_plot_sizey-(moving_size_relativ_y*10);
if(plot_window_y_size<600){plot_window_y_size=600;}
}
 return(0);
}

int plot_draw_plan_grid(int plotx, int ploty)
{
if(plot_quadrillage_size!=0)
{
plot_nbre_col=(plot_window_x_size-position_plan_x)/plot_quadrillage_size;
plot_nbre_lin=(plot_window_y_size-position_plan_y)/plot_quadrillage_size;
for(int i=0;i<=plot_nbre_col;i++)
{
Line
(Vec2D(plotx+(i*plot_quadrillage_size),ploty),Vec2D(plotx+(i*plot_quadrillage_size),ploty+(plot_window_y_size-position_plan_y))).Draw(CouleurPlotLine);
}
for(int i=0;i<=plot_nbre_lin;i++)
{
Line
(Vec2D(plotx,ploty+(i*plot_quadrillage_size)),Vec2D(plotx+(plot_window_x_size-position_plan_x),ploty+(i*plot_quadrillage_size))).Draw(CouleurPlotLine);
}
}
return(0);
}



int plot_draw_plan(int plotx, int ploty, int plot_calc_number_is)
{

for(int i=1;i<=nbre_symbols_on_plot[plot_calc_number_is];i++)
{
//affichage symbole
switch(symbol_type[plot_calc_number_is][i])
{
case 0:     //PC 500 ou 650
plot_draw_symbol_pc(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 1:     //PC 1kw
plot_draw_symbol_pc(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 2:     //PC2kw
plot_draw_symbol_pc(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i],i, plot_calc_number_is);
break;
case 3:    //fresnel 1kw
plot_draw_symbol_fresnel(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 4:    //fresnel 2kw
plot_draw_symbol_fresnel(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1],size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 5:    //fresnel 5kw
plot_draw_symbol_fresnel(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 6: //dec 1kw longue
plot_draw_symbol_decoupe_1(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1],size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 7: //dec 1kw mid
plot_draw_symbol_decoupe_2(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1],size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 8: //dec 1kw wide
plot_draw_symbol_decoupe_3(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1],size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 9: //dec 2kw
plot_draw_symbol_decoupe_1(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1],size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 10: //dec 2kw
plot_draw_symbol_decoupe_2(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 11: //dec 2kw
plot_draw_symbol_decoupe_3(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 12: //PAR CP60
plot_draw_symbol_Par_1(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 13: //PAR CP61
plot_draw_symbol_Par_2(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 14: //PAR CP62
plot_draw_symbol_Par_3(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 15: //PAR CP95
plot_draw_symbol_Par_4(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1],size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 16://par 56 CP60
plot_draw_symbol_Par_1(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1],size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 17://par 56 CP61
plot_draw_symbol_Par_2(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 18://par 56 CP62
 plot_draw_symbol_Par_3(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 19://Par 36
plot_draw_symbol_Par_4(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 20://par 20
plot_draw_symbol_Par_3(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 21://par 16
plot_draw_symbol_Par_1(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 22://horiziode assymetrique
plot_draw_symbol_Horiziode_assym(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 23://horiziode symetrique
plot_draw_symbol_Horiziode_sym(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 24://hallogene de chantier
plot_draw_symbol_Horiziode_sym(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 25://BT250w
plot_draw_symbol_BT(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 26://BT500W
plot_draw_symbol_BT(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
case 27://rampe brabo
plot_draw_symbol_rampe_brabo(plotx+pos_symbol[plot_calc_number_is][i][0], ploty+pos_symbol[plot_calc_number_is][i][1], size_symbol[(symbol_type[plot_calc_number_is][i])],  angle_symbol[plot_calc_number_is][i], i, plot_calc_number_is);
break;
default:
break;
}
if( index_edit_light_plot==1)//visualition du centre projo
{
Line(Vec2D(plotx+pos_symbol[plot_calc_number_is][i][0]-5,ploty+pos_symbol[plot_calc_number_is][i][1]-5),Vec2D(plotx+pos_symbol[plot_calc_number_is][i][0]+5,ploty+pos_symbol[plot_calc_number_is][i][1]+5)).Draw(CouleurBlind);
Line(Vec2D(plotx+pos_symbol[plot_calc_number_is][i][0]+5,ploty+pos_symbol[plot_calc_number_is][i][1]-5),Vec2D(plotx+pos_symbol[plot_calc_number_is][i][0]-5,ploty+pos_symbol[plot_calc_number_is][i][1]+5)).Draw(CouleurBlind);
if(plot_show_options[6]==1){petitchiffrenoir.Print(ol::ToString(i),plotx+pos_symbol[plot_calc_number_is][i][0],ploty+pos_symbol[plot_calc_number_is][i][1]);}//show ID

}

}



return(0);
}

int plot_draw_plan_bitmap(int xplot, int yplot, float alphaplan)
{

LightPlanBitmapMain.BlitTransformed(xplot+position_relative_plan_theatre[0], yplot+position_relative_plan_theatre[1],taille_relative_plan_theatre[0],taille_relative_plan_theatre[1],orientation_plan_theatre*6.5,alphaplan);

return(0);
}

int Plot_window(int plotx, int ploty)
{

Rect PlotPanel(Vec2D(plotx,  ploty), Vec2D( plot_window_x_size,plot_window_y_size));
PlotPanel.SetRoundness(rondeur_fader);
PlotPanel.SetLineWidth(epaisseur_ligne_fader*3);
PlotPanel.Draw(CouleurPlotFill);
if(window_focus_id==W_PLOT)
{
PlotPanel.DrawOutline(CouleurFader);
}
else {PlotPanel.DrawOutline(CouleurLigne); }
neuro.Print("LIGHT PLOT",plotx+100,ploty+30);



plot_menu_bar(plotx+230,ploty+10);//menus generaux de plot
logical_plot_menu_bare(plotx+230,ploty+10);

switch(index_menus_lighting_plot)
{
case 0://légende
break;
case 1://symbols
plot_symbol_list(plotx+10, ploty+50);//selecteur symbol
logical_plot_symbol_list(plotx+10, ploty+50);
plot_symbol_edition(plotx+10, ploty+200);//editeur de symbol
logical_plot_symbol_edition(plotx+10, ploty+200);//editeur de symbol
symbol_edition_options(plotx+10,ploty+255);
logical_symbol_edition_options(plotx+10, ploty+255);
break;
case 2://plan
menu_plan(plotx+10, ploty+50);
logical_menu_plan(plotx+10, ploty+50);
break;
default:
break;
}
Canvas::SetClipping( plotx+position_plan_x,ploty+position_plan_y,plot_window_x_size-position_plan_x,plot_window_y_size-position_plan_y);
plot_draw_plan_bitmap(plotx+position_plan_x,ploty+position_plan_y, alpha_plan);
plot_draw_plan_grid(plotx+position_plan_x,ploty+position_plan_y);
for(int i=0;i<4;i++)
{
if(show_calc_number[i]==1)
{
plot_draw_plan(plotx+position_plan_x,ploty+position_plan_y,i);
}
}
Canvas::DisableClipping();


//CALCUL MOVE PROJOS
//LOGIC TO PUT IN CORE
if(window_focus_id==W_PLOT && index_edit_light_plot==1 && index_click_inside_relativ_xy==0
&& mouse_x> plotx+position_plan_x && mouse_x<plotx+position_plan_x+plot_window_x_size
&& mouse_y> ploty+position_plan_y && mouse_y<ploty+position_plan_y+plot_window_y_size )
{
if(index_click_inside_plot==0 && mouse_button==1 && mouse_released==0 )
{
//prise de position
index_click_inside_plot=1;
plot_original_mouse_x=mouse_x;
plot_original_mouse_y=mouse_y;

check_select_deselect_symbol(plotx+position_plan_x,ploty+position_plan_y);
store_plot_position_of_activ_calc(view_plot_calc_number_is);
previous_plot_view_port_x=plot_view_port_x;
previous_plot_view_port_y=plot_view_port_y;
}
else if (index_click_inside_plot==1 && mouse_button==1 && mouse_released==0  )
{
plot_facteur_move_x=mouse_x-plot_original_mouse_x;
plot_facteur_move_y=mouse_y-plot_original_mouse_y;
if(index_move_plot_view_port==0)
{
for(int i=1;i<=nbre_symbols_on_plot[view_plot_calc_number_is];i++)
{
if(symbol_is_selected[view_plot_calc_number_is][i]==1 )
{
pos_symbol[view_plot_calc_number_is][i][0]=stored_plot_position[i][0]+ plot_facteur_move_x;
pos_symbol[view_plot_calc_number_is][i][1]=stored_plot_position[i][1]+ plot_facteur_move_y;
}
}
}
else if(index_move_plot_view_port==1)
{
plot_view_port_x=previous_plot_view_port_x+plot_facteur_move_x;
plot_view_port_y=previous_plot_view_port_y+plot_facteur_move_x;
}
}
}
return(0);
}
