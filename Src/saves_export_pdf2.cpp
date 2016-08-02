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

* \file saves_export_pdf2.cpp
* \brief {import and export the show in PDF}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions d'import export PDF pour garder une sauvegarde de la conduite en papier
*
*   Import and export the show in PDF to keep a save of the show in a paper format
*
**/


#include <setjmp.h>
#include "hpdf.h"
int max_ligne_pdf=52;
    char header_export[256];
    char little_header[48];//pour patch
    const char *page_title = importfile_name;
    HPDF_Doc  pdf;
    char fname[128];
    HPDF_Page page;
    HPDF_Font def_font;
    HPDF_REAL tw;
    HPDF_REAL height;
    HPDF_REAL width;
    HPDF_REAL debut_lignes;
int num_page_pdf=1;
jmp_buf env;

HPDF_Image  an_image_to_print_1;
HPDF_Image  an_image_to_print_2;
HPDF_Image  an_image_to_print_3;
HPDF_Image  an_image_to_print_4;
HPDF_Image  an_image_to_print_5;
HPDF_Image  an_image_to_print_6
;
#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    sprintf (string_Last_Order,"ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

const char *font_list[] = {
    "Courier",
    "Courier-Bold",
    "Courier-Oblique",
    "Courier-BoldOblique",
    "Helvetica",
    "Helvetica-Bold",
    "Helvetica-Oblique",
    "Helvetica-BoldOblique",
    "Times-Roman",
    "Times-Bold",
    "Times-Italic",
    "Times-BoldItalic",
    "Symbol",
    "ZapfDingbats",
    NULL
};



//////////////////VARIABLE MISE EN PAGE////////////////////////////////////////

HPDF_REAL cmptline_pdf=0;
HPDF_REAL position_ligne1= 50;
///////////////////////////////////////////////////////////////////////////////

void draw_numpage(HPDF_Page page, float x, float y,  const char *str_numpage)
{

HPDF_Page_BeginText (page);
HPDF_Page_TextOut (page, x,y ,str_numpage);
HPDF_Page_EndText (page);
}


int verification_fin_de_page()
{
if(cmptline_pdf>max_ligne_pdf)
{
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
HPDF_Page_SetRGBStroke (page, 0.0, 0.5, 0.5);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");
}

 return(0);
}


void draw_fleche_link  (HPDF_Page    page,
            float        x,
            float        y)
{

    HPDF_Page_MoveTo (page, x, y -10);
    HPDF_Page_LineTo (page, x+10, y - 10);
    HPDF_Page_MoveTo (page, x+10 , y - 10);
    HPDF_Page_LineTo (page, x+10, y -18 );
    HPDF_Page_MoveTo (page, x+10 , y - 18);
    HPDF_Page_LineTo (page, x+6, y -14 );
    HPDF_Page_MoveTo (page, x+10 , y - 18);
    HPDF_Page_LineTo (page, x+14, y -14 );
    HPDF_Page_Stroke (page);


}

void draw_title  (HPDF_Page    page,
            float        x,
            float        y,
            const char  *label)
{
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x, y - 10);
    HPDF_Page_ShowText (page, label);
    HPDF_Page_EndText (page);

    HPDF_Page_MoveTo (page, x, y - 12);
    HPDF_Page_LineTo (page, x + 600, y - 12);
    HPDF_Page_Stroke (page);
    cmptline_pdf++;
    cmptline_pdf++;
    verification_fin_de_page();
}

void draw_info  (HPDF_Page    page,
            float        x,
            float        y,
            const char  *label)
{
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x, y - 10);
    HPDF_Page_ShowText (page, label);
    HPDF_Page_EndText (page);

  //  HPDF_Page_Stroke (page);
}




void draw_section (HPDF_Page    page,
             float       x,
             float       y,
             const char  *label, float R, float G, float B)
{

HPDF_Page_SetLineWidth (page, 30);//epaisseur
HPDF_Page_SetRGBStroke (page, R, G, B);//couleur ligne
HPDF_Page_SetLineCap (page, HPDF_ROUND_END);
HPDF_Page_SetFontAndSize (page, def_font, 25);

    HPDF_Page_MoveTo (page, x , y );
    HPDF_Page_LineTo (page, x+500, y );
    HPDF_Page_Stroke (page);
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x, y-7);
    HPDF_Page_ShowText (page, label);
    HPDF_Page_EndText (page);

HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_SetLineWidth (page, 1);//epaisseur
HPDF_Page_SetRGBStroke (page, 0.0, 0.5, 0.5);//couleur ligne
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}

void saut_de_page()
{
//Saut de page
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
HPDF_Page_SetRGBStroke (page, 0.5, 0.5, 0.5);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");
}

bool check_there_is_someone_in_grid(int grd)
{
bool answer=0;
for (int st=0;st<1024;st++)
{
for(int c=0;c<513;c++)
{
if(grid_levels[grd][st][c]>0){ answer=1;break;}
}
}
return(answer);
}





int pdf_draw_little_gridplayer(HPDF_REAL xx, HPDF_REAL yy)
{
//grille
//lignes
for(int l=0;l<=grider_nb_row;l++ )
     {
        HPDF_Page_MoveTo (page, xx, yy-(l*6));
        HPDF_Page_LineTo (page, xx+(grider_nb_col*6), yy-(l*6));
        HPDF_Page_Stroke (page);
    }
//colonnes
    for(int col=0;col<=grider_nb_col;col++ )
     {
        HPDF_Page_MoveTo (page, xx+(col*6), yy);
        HPDF_Page_LineTo (page, xx+(col*6), yy-(grider_nb_row*6));
        HPDF_Page_Stroke (page);
    }

return(0);
}


int pdf_draw_channels_on_grid(HPDF_REAL xx, HPDF_REAL yy, int gr, int ste)
{


HPDF_Page_SetFontAndSize (page, def_font, 4);


float colRr, colGg, colBb;
int the_ch=0;
//sab 02/03/2014 unused var bool print_level=false;
HPDF_REAL xp=0;
HPDF_REAL yp=0;

for(int ligne=0;ligne<grider_nb_row;ligne++)
{
for(int col=0;col<grider_nb_col;col++)
{
the_ch=((ligne*grider_nb_col)+col);

if(grid_levels[gr][ste][the_ch]!=0)
{


//sab 02/03/2014 unused var print_level=false;

//couleurs
if(grid_levels[gr][ste][the_ch]==255)
{
colRr=1.0; colGg=0.5; colBb=0.0;  //sab 02/03/2014 unused var print_level=false;
}
else
{
colRr=0.0; colGg=1.0; colBb=0.0;   //sab 02/03/2014 unused var  print_level=true;
}
xp=xx+(col*6);
yp=yy- (ligne*6);

//Si pas toute la syntaxe d impression ca fait merder

HPDF_Page_SetRGBFill (page,colRr, colGg, colBb);//couleur remplissage
HPDF_Page_SetRGBStroke (page, colRr, colGg, colBb);//couleur ligne
HPDF_Page_Rectangle  (page, xp, yp-6, 6,6);
HPDF_Page_FillStroke (page);
HPDF_Page_SetRGBFill (page,0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_SetRGBStroke (page, 0.5, 0.5, 0.5);//couleur ligne



if(grid_levels[gr][ste][the_ch]!=255)
{


switch(dmx_view)
{
case 0:
sprintf(header_export,"%d",(int)((float)(grid_levels[gr][ste][the_ch])/2.55) );
break;
case 1:
sprintf(header_export,"%d",grid_levels[gr][ste][the_ch] );
break;
default: break;
}
draw_info(page,xx+(col*6)+1 ,yy-(ligne*6)+5,header_export);
}

}



}
}

return(0);
}



int pdf_draw_infos_of_step(HPDF_REAL xx, HPDF_REAL yy,int grd,int stp)
{
HPDF_Page_SetFontAndSize (page, def_font,6);

char the_in[12];
char the_out[12];

char the_delay_in[12];
char the_delay_out[12];

strcpy(header_export,"");//nettoyage pour les temps

affichage_time_format(grid_times[grd][stp][1]);//in
sprintf(the_in,string_conversion_timeis);
affichage_time_format(grid_times[grd][stp][3]);//out
sprintf(the_out,string_conversion_timeis);
affichage_time_format(grid_times[grd][stp][0]);//din
sprintf(the_delay_in,string_conversion_timeis);
affichage_time_format(grid_times[grd][stp][2]);//dout
sprintf(the_delay_out,string_conversion_timeis);

if(grid_times[grd][stp][0]>0){sprintf(header_export,"d. %s",the_delay_in);}
strcat(header_export," IN ");
strcat(header_export,the_in);
draw_info(page,xx ,yy-6,header_export);
strcpy(header_export,"");

if(grid_times[grd][stp][2]>0){sprintf(header_export,"d. %s",the_delay_out);}
strcat(header_export," OUT ");
strcat(header_export,the_out);
draw_info(page,xx ,yy-12,header_export);
strcpy(header_export,"");

if(grid_goto[grd][stp][0]!=-1 || grid_goto[grd][stp][1]!=-1)
{
sprintf(header_export,"Goto:  %d - %d",grid_goto[grd][stp][0]+1, grid_goto[grd][stp][1]+1 );
draw_info(page,xx ,yy-18,header_export);
}


if(grid_count[grd][stp]!=0)
{
sprintf(header_export,"Count: %d",grid_count[grd][stp]+1 );
draw_info(page,xx ,yy-24,header_export);
}


if(grid_seekpos[grd][stp]!=-1)
{
sprintf(header_export,"Seek: %d",grid_seekpos[grd][stp]+1 );
draw_info(page,xx ,yy-30,header_export);
}

if(grid_stoplay[grd][stp]==1)
{
sprintf(header_export,"[ STOP PLAY ]" );
draw_info(page,xx ,yy-36,header_export);
}
return(0);
}

int draw_pdf_gridayer_state( int grd)
{
sprintf(header_export,"GRIDPLAYER %d:   ",grd+1 );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Contains Grid: %d Actual Step is: %d",index_grider_selected[grd]+1,index_grider_step_is[grd]+1 );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Is Playing: %d Seek Pos is: %d AutoStop Mode is: %d",grider_is_playing[grd],index_grider_seek_pos[grd]+1,grider_autostopmode[grd] );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Macros: Goto Mode: %d CountMode: %d SeekTo Mode: %d StopPlay Mode: %d",grider_goto_mode[grd],grider_count_mode[grd],grider_seekto_mode[grd],grider_stoplay_mode[grd] );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Speed is slaved: %d Speed Level: %d ",grid_player_slave[grd],grid_crossfade_speed[grd] );
if(grd==0){
char tmp[32];
sprintf(tmp,"CuelistSpeed is linked: %d",index_link_speed_crossfade_to_gpl1);
strcat(header_export,tmp);
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
cmptline_pdf++;
return(0);
}




int draw_pdf_grid(int grd, HPDF_REAL xx, HPDF_REAL yy)
{


bool steps_to_write[1024];

for(int stp=0;stp<1023;stp++)
{
steps_to_write[stp]=0;//init
for(int c=0;c<512;c++)
{
if(grid_levels[grd][stp][c]>0){steps_to_write[stp]=1;}
}
}

HPDF_REAL nbre_de_grille_par_largeur=(width-20)/((grider_nb_col*6)+10);

int step_enieme=0;
HPDF_REAL interspace_largeur=0;
HPDF_REAL interspace_hauteur=0;

for(int stp=0;stp<1023;stp++)
{
if(steps_to_write[stp]==1 || (stp>0 && steps_to_write[stp-1]==1) || (stp<1022 && steps_to_write[stp+1]==1) )
{
//GRILLE
//lignes
interspace_largeur= step_enieme*((grider_nb_col*6)+10);

HPDF_Page_SetFontAndSize (page, def_font, 6);

sprintf(header_export,"Step: %d",stp+1 );
draw_info(page,xx+interspace_largeur ,yy-interspace_hauteur+12,header_export);

pdf_draw_channels_on_grid(xx+interspace_largeur,yy-interspace_hauteur,grd, stp);
pdf_draw_little_gridplayer(xx+interspace_largeur,yy-interspace_hauteur);
pdf_draw_infos_of_step(xx+interspace_largeur,yy-interspace_hauteur-(6*grider_nb_row-6),grd, stp);
step_enieme++;
if(step_enieme>nbre_de_grille_par_largeur-1  )
{
interspace_hauteur+=((grider_nb_row*6)+60);
step_enieme=0;
//verif fin de page
if((yy-interspace_hauteur)<((grider_nb_row*6)+60))
{
 saut_de_page();
 interspace_hauteur=0;
}

}


}
}



HPDF_Page_SetFontAndSize (page, def_font, 10);

 return(0);
}

int draw_pdf_echo_config()
{
for(int pr=0;pr<24;pr++)
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.4, 0.9);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");


sprintf(header_export,"Echo Preset: %d",pr +1);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

sprintf(header_export,"Pointing Fader: %d",echo_pointing_fader_num[pr] );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();

switch(echo_is_echo_mode[pr])
{
case 0:
sprintf(header_export,"Echo Mode is /OFF ");
break;
case 1:
sprintf(header_export,"Echo Mode is /ON ");
break;
default: break;
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();


switch(echo_channel_manipulate_mode[pr])
{
case 0:
sprintf(header_export,"ChanMode is CH/LEVEL");
break;
case 1:
sprintf(header_export,"ChanMode is CH/GROUND");
break;
default: break;
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();

sprintf(header_export,"Channel position is: %d ",echo_grid_channel_position[pr]+1 );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();

sprintf(header_export,"Gravity: %.2f     Mass: %.2f     Energy:%.2f ",
echo_global_params[pr][0],echo_global_params[pr][1],echo_global_params[pr][2] );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();



}
return(0);
}

int draw_pdf_draw_config()
{

for(int pr=0;pr<6;pr++)
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.7, 0.7);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");


sprintf(header_export,"Draw Matrix: %d",pr +1);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

sprintf(header_export,"Col: %d Row: %d",draw_preset_parameters[pr][0],draw_preset_parameters[pr][1] );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

switch(draw_mode[pr])
{
case 0:
sprintf(header_export,"Draw MODE: DRAW ( Additiv )");
break;
case 1:
sprintf(header_export,"Draw MODE: ERASE ( Soustractiv )");
break;
case 2:
sprintf(header_export,"Draw MODE: SOLO");
break;
case 3:
sprintf(header_export,"Draw MODE: GHOST");
break;
default:
break;
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

switch(draw_brush_type[pr])
{
case 0:
sprintf(header_export,"DOT brush selected");
break;
case 1:
sprintf(header_export,"GRIDPLAYER selected");
break;
default:
break;
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
//dessin des affectations:


//GRILLE
HPDF_Page_SetLineWidth (page, 0.25);
HPDF_Page_SetGrayStroke (page, 0.5);
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage

recalculate_draw_sizes(pr);

HPDF_REAL larg=draw_largeur_case[pr]/1.2;
HPDF_REAL haut=draw_hauteur_case[pr]/1.2;

    for(int lych=0;lych<=draw_preset_parameters[pr][1];lych++ )
     {
        HPDF_Page_MoveTo (page, 100, debut_lignes -(position_ligne1+(cmptline_pdf*12))-(lych*haut));
        HPDF_Page_LineTo (page, 100+(larg*draw_preset_parameters[pr][0]), debut_lignes -(position_ligne1+(cmptline_pdf*12))-(lych*haut));
        HPDF_Page_Stroke (page);
    }
  /* verticales */
    for(int lxch=0;lxch<=draw_preset_parameters[pr][0];lxch++ )
     {
        HPDF_Page_MoveTo (page, 100+(lxch*larg), debut_lignes -(position_ligne1+(cmptline_pdf*12)));
        HPDF_Page_LineTo (page, 100+(lxch*larg), debut_lignes -(position_ligne1+(cmptline_pdf*12)+(draw_preset_parameters[pr][1]*haut)));
        HPDF_Page_Stroke (page);
    }


//previsu niveau laissé à l'enregistrement

int the_ch=0;
float val=0.0;
HPDF_REAL xp=0;
HPDF_REAL yp=0;

for(int ligne=0;ligne<draw_preset_parameters[pr][1];ligne++)
{
for(int col=0;col<draw_preset_parameters[pr][0];col++)
{
the_ch=((ligne*draw_preset_parameters[pr][0])+col);

if(draw_preset_levels[pr][the_ch]!=0)
{

xp=100+(col*larg);
yp=debut_lignes -(position_ligne1+(cmptline_pdf*12))-(ligne*haut);
val=( draw_preset_levels[pr][the_ch]+0.2) ;//(+0.2 pour le noir);
//Si pas toute la syntaxe d impression ca fait merder

HPDF_Page_SetRGBFill (page,val*0.2,val*0.7,val*0.7);//couleur remplissage
HPDF_Page_Rectangle  (page, xp, yp-haut, larg,haut);
HPDF_Page_FillStroke (page);
HPDF_Page_SetRGBFill (page,0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_SetRGBStroke (page, 0.5, 0.5, 0.5);//couleur ligne

}
}
}
//remise a plat couleur

HPDF_Page_SetLineWidth (page, 0.25);
HPDF_Page_SetGrayStroke (page, 0.5);
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage


//sab 02/03/2014 unused var int dr_ch=0;
HPDF_Page_SetFontAndSize (page, def_font, 4);
for(int l=0;l<draw_preset_parameters[pr][1];l++)
{
for(int co=0;co<draw_preset_parameters[pr][0];co++)
{
sprintf(header_export,"%d",draw_preset_channel_routing[pr][co+(l*draw_preset_parameters[pr][0])] );
draw_info(page, 104+(larg*co), debut_lignes -(position_ligne1+(cmptline_pdf*12))-(l*haut),header_export);
}
}
HPDF_Page_SetFontAndSize (page, def_font, 10);

//fin du récap circuit
saut_de_page();
}

return(0);
}

int draw_pdf_grid_players_config()
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.5, 0.0);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");


strcpy(header_export,"Channels Configuration Grid:" );
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);



sprintf(header_export,"Starting Channel: %d",grider_begin_channel_is );
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
cmptline_pdf++;

sprintf(header_export,"On save your 4 GridPlayers were in this state:" );
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for(int i=0;i<4;i++)
{
draw_pdf_gridayer_state(i);
}



sprintf(header_export,"GridPlayer Channel Routing:" );
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);


//GRILLE
HPDF_Page_SetLineWidth (page, 0.25);
HPDF_Page_SetGrayStroke (page, 0.5);
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage


    /* horizontales */
    for(int lych=0;lych<=grider_nb_row;lych++ )
     {
        HPDF_Page_MoveTo (page, 100, debut_lignes -(position_ligne1+(cmptline_pdf*12))-(lych*16));
        HPDF_Page_LineTo (page, 100+(16*grider_nb_col), debut_lignes -(position_ligne1+(cmptline_pdf*12))-(lych*16));
        HPDF_Page_Stroke (page);
    }
  /* verticales */
    for(int lxch=0;lxch<=grider_nb_col;lxch++ )
     {
        HPDF_Page_MoveTo (page, 100+(lxch*16), debut_lignes -(position_ligne1+(cmptline_pdf*12)));
        HPDF_Page_LineTo (page, 100+(lxch*16), debut_lignes -(position_ligne1+(cmptline_pdf*12)+(grider_nb_row*16)));
        HPDF_Page_Stroke (page);
    }


//sab 02/03/2014 unused var int dr_ch=0;
HPDF_Page_SetFontAndSize (page, def_font, 7);
for(int l=0;l<grider_nb_row;l++)
{
for(int co=0;co<grider_nb_col;co++)
{
sprintf(header_export,"%d",grider_begin_channel_is+(l*grider_nb_col)+co);
draw_info(page, 104+(16*co), debut_lignes -(position_ligne1+(cmptline_pdf*12))-(l*16),header_export);
}
}
HPDF_Page_SetFontAndSize (page, def_font, 10);

//fin du récap circuit
cmptline_pdf+=grider_nb_row;


//Saut de page
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
HPDF_Page_SetRGBStroke (page, 0.5, 0.5, 0.5);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");

//
for(int gd=0;gd<127;gd++)
{
if(check_there_is_someone_in_grid(gd)==1)
{
sprintf(header_export,"Grid number %d: %s",gd+1,grider_name[gd]);
draw_title(page, 120, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
draw_pdf_grid(gd,20,debut_lignes -(position_ligne1 +(cmptline_pdf*12)));
saut_de_page();
}

}

return(0);
}

int draw_pdf_chaser(int chaser_num, HPDF_Page    page)
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.5, 0.0);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");

sprintf(header_export,"CHASER %d",chaser_num+1 );
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Description: %s", chaser_name[chaser_num]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
char tmp_y[16];
//time
switch(chaser_time_mode[chaser_num])
{
case 0:
sprintf(tmp_y,"Time Standard");
break;
case 1:
sprintf(tmp_y,"TimeJoin");
break;
default: break;
}
sprintf(header_export,"Time Unit: %f Time Mode: %s ", time_unit[chaser_num], tmp_y);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
//WAY
switch(chaser_way[chaser_num])
{
case 0:
sprintf(tmp_y,"Forward Way");
break;
case 1:
sprintf(tmp_y,"Backward Way");
break;
default: break;
}
if(chaser_aller_retour[chaser_num]==1)
{sprintf(header_export,"%s , aller-retour mode", tmp_y);}
else
{sprintf(header_export, tmp_y);}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
//Play Loop
switch(chaser_is_playing[chaser_num])
{
case 0:
sprintf(tmp_y,"PLAY OFF");
break;
case 1:
sprintf(tmp_y,"PLAY ON");
break;
default: break;
}
if(chaser_is_in_loop[chaser_num]==1)
{sprintf(header_export,"%s , LOOP ON", tmp_y);}
else
{sprintf(header_export, tmp_y);}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
//relation speed au fader
sprintf(header_export,"Chaser last affectation: Fader %d Dock %d ", view_chaser_affected_to_fader[chaser_selected][0]+1,view_chaser_affected_to_fader[chaser_selected][1]+1);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
if(index_slave_chaser_to_accelerometre[chaser_num]==1)
{
sprintf(header_export,"Chaser LFO Slaviness: %.2f",chaser_slaviness[chaser_num]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
}
/////////REPORT GRAPHIQUE TABLEAU CHASER
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
for(int ind=0;ind<nbre_de_cases_par_track;ind++)
{
if( chaser_begin_step_is[chaser_num]==ind)
{
HPDF_Page_SetRGBFill (page, 1.0, 0.5, 0.0);//couleur remplissage
HPDF_Page_SetRGBStroke (page, 1.0, 0.5, 0.0);//couleur ligne
HPDF_Page_Rectangle  (page, 120+(ind*12),debut_lignes -(position_ligne1+(cmptline_pdf*12)), 12,12);
HPDF_Page_FillStroke (page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
}
if( chaser_end_step_is[chaser_num]==ind)
{
HPDF_Page_SetRGBFill (page, 1.0, 0.0, 0.0);//couleur remplissage
HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 0.0);//couleur ligne
HPDF_Page_Rectangle  (page, 120+(ind*12),debut_lignes -(position_ligne1+(2+cmptline_pdf*12)+24), 12,12);
HPDF_Page_FillStroke(page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
}
}
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
for(int ind=0;ind<nbre_de_cases_par_track;ind++)
{
sprintf(header_export,"%d", ind+1);
draw_info(page, 120+(ind*12),debut_lignes -(position_ligne1+(cmptline_pdf*12)),header_export);
}
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;

//remplissage encodage up down stay
for(int tr=0;tr<nbre_tracks_par_chaser;tr++)
{
for(int ind=0;ind<nbre_de_cases_par_track;ind++)
{
if( chaser_step_operation[chaser_num][tr][ind]!=0)//si quelquechosedans track
{
float colRt, colGt, colBt;
switch (chaser_step_operation[chaser_num][tr][ind])
{
case 1:
colRt=1.0; colGt=0.5; colBt=0.0;
break;
case 2:
colRt=0.0; colGt=1.0; colBt=0.0;
break;
case 3:
colRt=1.0; colGt=0.0; colBt=0.0;
break;
default: break;
}
HPDF_Page_SetRGBFill (page,colRt, colGt, colBt);//couleur remplissage
HPDF_Page_SetRGBStroke (page, colRt, colGt, colBt);//couleur ligne
HPDF_Page_Rectangle  (page, 120+(ind*12),debut_lignes -(position_ligne1+(cmptline_pdf*12)+12+(tr*12)), 12,12);
HPDF_Page_FillStroke (page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
}
}
}

//GRILLE
HPDF_Page_SetLineWidth (page, 0.25);
HPDF_Page_SetGrayStroke (page, 0.5);
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage
    /* horizontales */
    for(int lych=(int)cmptline_pdf;lych<=cmptline_pdf+nbre_tracks_par_chaser;lych++ )
     {
        HPDF_Page_MoveTo (page, 120, debut_lignes -(position_ligne1+(lych*12)));
        HPDF_Page_LineTo (page, 120+(12*nbre_de_cases_par_track), debut_lignes -(position_ligne1+(lych*12)));
        HPDF_Page_Stroke (page);
    }
  /* verticales */
    for(int lxch=0;lxch<=nbre_de_cases_par_track;lxch++ )
     {
        HPDF_Page_MoveTo (page, 120+(lxch*12), debut_lignes -(position_ligne1+(cmptline_pdf*12)-(4*12)));
        HPDF_Page_LineTo (page, 120+(lxch*12), debut_lignes -(position_ligne1+((cmptline_pdf+nbre_tracks_par_chaser)*12)));
        HPDF_Page_Stroke (page);
    }

char tmp_u[6];
for(int ly=0;ly<nbre_tracks_par_chaser;ly++)
{
switch( track_is_on[chaser_num][ly])
{
case 0:
sprintf(tmp_u,"OFF");
break;
case 1:
sprintf(tmp_u,"ON");
break;
default: break;
}
sprintf(header_export,"Tr:%d %s(%d)",ly+1,tmp_u,track_level[chaser_num][ly]);
draw_info(page, 40, debut_lignes -(position_ligne1 +(cmptline_pdf*12)+(ly*12)),header_export);
}

cmptline_pdf+=24;
cmptline_pdf++;
cmptline_pdf++;
//////////CONTENU DES TRACKS
int comptch=0;
bool there_is_someone_inside_this_track=0;
for(int t=0;t<nbre_tracks_par_chaser;t++)
{
there_is_someone_inside_this_track=0;
for(int c=1;c<513;c++)
{
if(TrackContains[chaser_num][t][c]!=0)
{
there_is_someone_inside_this_track=1;break;
}
}

if(there_is_someone_inside_this_track==1 && TrackTypeIs[chaser_num][t]==0)//si quelqu un dans piste et type de track CIRCUITS
{
sprintf(header_export,"Track: %d  / Description: %s",t+1,chaser_track_name[chaser_num][t]);
draw_title(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");
if(cmptline_pdf>max_ligne_pdf)
{
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
HPDF_Page_SetRGBStroke (page, 0.5, 0.5, 0.5);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");
}
comptch=0;
for(int c=1;c<513;c++)
{
if(TrackContains[chaser_num][t][c]!=0)
{
if(comptch==0){cmptline_pdf++; strcpy(header_export,"");}//retour ligne après 10 circuits

switch(dmx_view)
{
case 0:
sprintf(little_header,"%d=%d   ",c,(int)((float)(TrackContains[chaser_num][t][c])/2.55));
break;
case 1:
sprintf(little_header,"%d=%d   ",c,TrackContains[chaser_num][t][c]);
break;
default: break;
}
strcat(header_export,little_header);
comptch++;
if(comptch>10)
{
comptch=0;
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
if(cmptline_pdf>max_ligne_pdf)
{
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
HPDF_Page_SetRGBStroke (page, 0.8, 0.0, 0.0);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");
}
}
}
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
strcpy(header_export,"");
cmptline_pdf++;
}//fin si quelqu un dedans en mode circuits
else if( TrackTypeIs[chaser_num][t]==1)//si mémoire affectée à piste
{
sprintf(header_export,"Track: %d  / Description: %s",t+1,chaser_track_name[chaser_num][t]);
draw_title(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");
if(cmptline_pdf>max_ligne_pdf)
{
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
HPDF_Page_SetRGBStroke (page, 0.5, 0.5, 0.5);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");
}
cmptline_pdf++;
sprintf(header_export,"Contains Mem. %.1f",(float (TrackHasMem[chaser_num][t])/10));
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
strcpy(header_export,"");
cmptline_pdf++;
}
cmptline_pdf++;
}

cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
return(0);
}


int generate_list_midi_for_pdf()
{

sprintf(list_midi_affect[615],"Grand Master level");

sprintf(list_midi_affect[767],"Move Fader space");
//////////////////FADERS/////////////////////////////////////////////
for(int i=0;i<48;i++)
{
sprintf(list_midi_affect[i],"Level");
sprintf(list_midi_affect[i+48],"Dock -");
sprintf(list_midi_affect[i+96],"Dock +");
sprintf(list_midi_affect[i+146],"Lock");
sprintf(list_midi_affect[i+196],"Lfo speed");
sprintf(list_midi_affect[i+245],"Up");
sprintf(list_midi_affect[i+294],"Down");
sprintf(list_midi_affect[i+343],"Saw");
sprintf(list_midi_affect[i+392],"Cycle Dock -");
sprintf(list_midi_affect[i+441],"CycleDock +");
sprintf(list_midi_affect[i+499],"Cycle Up and Down");
sprintf(list_midi_affect[i+556],"Midi Do Action");
sprintf(list_midi_affect[i+685],"Set Stop Pos");
sprintf(list_midi_affect[i+802],"Loop One");
sprintf(list_midi_affect[i+851],"Loop All");
sprintf(list_midi_affect[i+900],"Flash");
sprintf(list_midi_affect[i+1115],"Embeded Play");
sprintf(list_midi_affect[i+1164],"Embeded Seek");
sprintf(list_midi_affect[i+1213],"Embeded Loop/Autostop");
sprintf(list_midi_affect[i+1278],"Embeded Autolaunch");
sprintf(list_midi_affect[i+1543],"FX Mode");
sprintf(list_midi_affect[i+1912],"Damper On/off");
sprintf(list_midi_affect[i+1960],"Damper Decay");
sprintf(list_midi_affect[i+2008],"Damper Mode");
sprintf(list_midi_affect[i+2056],"Damper Delta");
}
sprintf(list_midi_affect[767],"Faders Handle Horizontal");
sprintf(list_midi_affect[1627],"Faders Handle Vertical");
///////////////////MINIFADERS/////////////////////////////////////////
sprintf(list_midi_affect[145],"Select All");
sprintf(list_midi_affect[774],"Selection -");
sprintf(list_midi_affect[775],"Selection +");
sprintf(list_midi_affect[776],"Select");
sprintf(list_midi_affect[777],"Unselect");
sprintf(list_midi_affect[778],"FLASH");
sprintf(list_midi_affect[779],"LOCK");
sprintf(list_midi_affect[780],"LOOP");
sprintf(list_midi_affect[781],"UP");
sprintf(list_midi_affect[782],"DOWN");
sprintf(list_midi_affect[783],"SAW");
sprintf(list_midi_affect[784],"ALL LOOP");
sprintf(list_midi_affect[785],"At Zero");
sprintf(list_midi_affect[786],"Set StopPos");
sprintf(list_midi_affect[787],"To PrevDock");
sprintf(list_midi_affect[788],"To NextDock");
sprintf(list_midi_affect[789],"UPDOWN");
sprintf(list_midi_affect[790],"Select Dock-");
sprintf(list_midi_affect[791],"Select Dock+");
sprintf(list_midi_affect[792],"-");

sprintf(list_midi_affect[793],"NOTHING FREE");
for(int o=0;o<8;o++)
{
sprintf(list_midi_affect[o+794],"MiniFader Preset %d",o);
}

////////////////SEQUENCE//////////////////////////////////////////
sprintf(list_midi_affect[491],"Stage Fader");
sprintf(list_midi_affect[492],"Preset Fader");
sprintf(list_midi_affect[493],"Speed");
sprintf(list_midi_affect[494],"GO");
sprintf(list_midi_affect[495],"GO BACK");
sprintf(list_midi_affect[496],"DOUBLE GO");
sprintf(list_midi_affect[768],"Create New Mem");
sprintf(list_midi_affect[769],"Delete Mem");
sprintf(list_midi_affect[770],"Stage Minus");
sprintf(list_midi_affect[771],"Stage Plus");
sprintf(list_midi_affect[772],"Preset Minus");
sprintf(list_midi_affect[773],"Preset Plus");
sprintf(list_midi_affect[1591],"Autoreset Crossfade Speed");
sprintf(list_midi_affect[1645],"GOTO");
/////////////////////////ALL AT//////////////////////////////////////
sprintf(list_midi_affect[548],"Faders");
sprintf(list_midi_affect[549],"Speed");
sprintf(list_midi_affect[550],"Lock");
sprintf(list_midi_affect[551],"Lfo");
sprintf(list_midi_affect[552],"Loop");
sprintf(list_midi_affect[553],"All");
sprintf(list_midi_affect[554],"Midiout");
sprintf(list_midi_affect[555],"Recall");
///////////////////LOCK PRESETS//////////////////////////////////////
for(int o=0;o<8;o++)
{
sprintf(list_midi_affect[o+605],"Lock Preset %d",o);
}

///////////////AUDIO PLAYER///////////////////////////////////////////////////
for(int p=0;p<4;p++)
{
sprintf(list_midi_affect[616+p]," %d LEVEL",p+1);
sprintf(list_midi_affect[620+p]," %d Pan",p+1);
sprintf(list_midi_affect[624+p]," %d Pitch",p+1);
sprintf(list_midi_affect[628+p]," %d PLAY",p+1);
sprintf(list_midi_affect[632+p]," %d Seek To 0",p+1);
sprintf(list_midi_affect[636+p]," %d General Loop",p+1);
sprintf(list_midi_affect[640+p]," %d Backward",p+1);
sprintf(list_midi_affect[644+p]," %d Forward",p+1);
sprintf(list_midi_affect[648+p]," %d Set IN",p+1);
sprintf(list_midi_affect[652+p]," %d Set Out",p+1);
sprintf(list_midi_affect[656+p]," %d Cue On/Off",p+1);
sprintf(list_midi_affect[660+p]," %d Seek Cue",p+1);
sprintf(list_midi_affect[1800+p]," %d Autoload",p+1);
sprintf(list_midi_affect[1805+p]," %d Autostop",p+1);
sprintf(list_midi_affect[1809+p]," %d Loadfile num",p+1);
sprintf(list_midi_affect[1813+p]," %d Prev track",p+1);
sprintf(list_midi_affect[1817+p]," %d Next track",p+1);
sprintf(list_midi_affect[1821+p]," %d SeektoEnd",p+1);
}
///////////////NUMPAD/////////////////////////////////////////////////////
sprintf(list_midi_affect[664],"Midi Level Wheel");
sprintf(list_midi_affect[665],"ENTER");
sprintf(list_midi_affect[666],"+");
sprintf(list_midi_affect[667],"-");
sprintf(list_midi_affect[668],"Up");
sprintf(list_midi_affect[669],"Down");
sprintf(list_midi_affect[670],"0");
sprintf(list_midi_affect[671],"1");
sprintf(list_midi_affect[672],"2");
sprintf(list_midi_affect[673],"3");
sprintf(list_midi_affect[674],"4");
sprintf(list_midi_affect[675],"5");
sprintf(list_midi_affect[676],"6");
sprintf(list_midi_affect[677],"7");
sprintf(list_midi_affect[678],"8");
sprintf(list_midi_affect[679],"9");
sprintf(list_midi_affect[680],"Point");
sprintf(list_midi_affect[681],"Esc");
sprintf(list_midi_affect[682],"All");
sprintf(list_midi_affect[683],"Inv");
sprintf(list_midi_affect[684],"To");
sprintf(list_midi_affect[1825],"Check minus");
sprintf(list_midi_affect[1826],"Check plus");
sprintf(list_midi_affect[1827],"AtFull");
sprintf(list_midi_affect[1828],"AtZero");
/////////BANGER///////////////////////////////////////////////
sprintf(list_midi_affect[734],"Bang it !");
for(int bc=0;bc<6;bc++)
{
sprintf(list_midi_affect[735+bc],"Bang %d", bc+1);
}
sprintf(list_midi_affect[741],"Banger Page -");
sprintf(list_midi_affect[742],"Banger Page +");
for (int l=0;l<127;l++)
{
sprintf(list_midi_affect[1343+l],"Banger N°%d",l+1);
}
/////////////////GRANDES FONCTIONS///////////////////////////

sprintf(list_midi_affect[743],"DOCK F1");
sprintf(list_midi_affect[744],"MODIFY F2");
sprintf(list_midi_affect[745],"REPORT F3");
sprintf(list_midi_affect[746],"CLEAR F4");
sprintf(list_midi_affect[757],"QUIT");

/////////////////FENETRE TIME////////////////////////////////////
sprintf(list_midi_affect[758],"Time Wheel");
sprintf(list_midi_affect[759],"Switch Time Type");
sprintf(list_midi_affect[760],"Delay IN");
sprintf(list_midi_affect[761],"IN");
sprintf(list_midi_affect[762],"Delay OUT");
sprintf(list_midi_affect[763],"OUT");
sprintf(list_midi_affect[764],"Affect Time");
sprintf(list_midi_affect[765],"Chrono");
sprintf(list_midi_affect[766],"Reset Chrono");

//////////////////////TRICHROMY/////////////////////////////////
sprintf(list_midi_affect[497],"Thichromy Wheel");
for(int y=0;y<8;y++)
{sprintf(list_midi_affect[949+y],"Dock Color %d",y+1); }

//////////////////TRACKING VIDEO//////////////////////////////////

sprintf(list_midi_affect[498],"Tracking Decay Wheel");
for(int y=0;y<12;y++)
{sprintf(list_midi_affect[957+y],"ROI %d",y+1); }
for(int y=0;y<5;y++)
{sprintf(list_midi_affect[969+y],"Video Preset %d",y+1); }

////////////////////FENETRE CHASERS///////////////////////////////
sprintf(list_midi_affect[974],"Select Chaser -");
sprintf(list_midi_affect[975],"Select Chaser +");
sprintf(list_midi_affect[976],"View track up");
sprintf(list_midi_affect[977],"View track down");
sprintf(list_midi_affect[978],"Chaser Play");
sprintf(list_midi_affect[979],"Chaser Seek");
sprintf(list_midi_affect[980],"Chaser Loop");
sprintf(list_midi_affect[981],"Forward way");
sprintf(list_midi_affect[982],"Backward way");
sprintf(list_midi_affect[983],"Aller-Retour");
sprintf(list_midi_affect[984],"ON: ALL");
sprintf(list_midi_affect[985],"ON: INV");
sprintf(list_midi_affect[986],"ON: ALL OFF");
sprintf(list_midi_affect[987],"ON: Preset 1");
sprintf(list_midi_affect[988],"ON: Preset 2");
sprintf(list_midi_affect[989],"ON: Preset 3");
sprintf(list_midi_affect[990],"ON: Preset 4");
sprintf(list_midi_affect[991],"Operator UP");
sprintf(list_midi_affect[992],"Operator STAY");
sprintf(list_midi_affect[993],"Operator DOWN");
sprintf(list_midi_affect[994],"TIME MODE (Std / Join)");
sprintf(list_midi_affect[995],"Begin Step");
sprintf(list_midi_affect[996],"End Step");
sprintf(list_midi_affect[997],"On Timeline Step Position");
for (int ot=0;ot<nbre_tracks_par_chaser;ot++)
{
sprintf(list_midi_affect[998+ot],"ON Track %d",ot+1);
sprintf(list_midi_affect[1024+ot],"LEVEL Track %d",ot+1);
}
for (int yc=0;yc<8;yc++)
{
for(int yl=0;yl<8;yl++)
{
sprintf(list_midi_affect[1048+yl+(yc*8)],"Grid L.%d, Pos %d",yc+1, yl+1);
}
}
sprintf(list_midi_affect[1112],"NOTHING FREE");
sprintf(list_midi_affect[1113],"Grid Pos -");
sprintf(list_midi_affect[1114],"Grid Pos +");

//iCat/////////////////////////////////////////////////
sprintf(list_midi_affect[1265],"iCat Page -");
sprintf(list_midi_affect[1266],"iCat Page +");
for(int yl=0;yl<8;yl++)
{
sprintf(list_midi_affect[1267+yl],"Call iCat Page %d",yl+1);
}
sprintf(list_midi_affect[1275],"iCat Page Orientation");
sprintf(list_midi_affect[1276],"iCat Page Refresh");
//midi Mute
sprintf(list_midi_affect[1277],"MidiMute (Global)");

//COMMANDS///////////////////////////////////////////

sprintf(list_midi_affect[747],"Call Name window");
sprintf(list_midi_affect[748],"Call Time window");
sprintf(list_midi_affect[749],"Call Trichro window");
sprintf(list_midi_affect[750],"Call Tracking video");
sprintf(list_midi_affect[751],"Call Cue List");
sprintf(list_midi_affect[752],"Call Faders Window");
sprintf(list_midi_affect[753],"Call Banger window");
sprintf(list_midi_affect[754],"Blind mode");
sprintf(list_midi_affect[755],"Call CFG MENU");
sprintf(list_midi_affect[756],"Call Audio window");

sprintf(list_midi_affect[1329],"Call Wizard window");
sprintf(list_midi_affect[1330],"Call Save window");
sprintf(list_midi_affect[1331],"Call Patch window");
sprintf(list_midi_affect[1332],"Call List window");
sprintf(list_midi_affect[1333],"Direct CH mode");
sprintf(list_midi_affect[1334],"View mode");
sprintf(list_midi_affect[1335],"Freeze mode");
sprintf(list_midi_affect[1336],"Call Minifaders window");
sprintf(list_midi_affect[1337],"Call Chaser window");
sprintf(list_midi_affect[1338],"Call Numeric pad");
sprintf(list_midi_affect[1339],"Call Mover window");
sprintf(list_midi_affect[1340],"Call Grider window");
sprintf(list_midi_affect[1341],"Call iCat builder");
sprintf(list_midi_affect[1342],"Call Help window");
sprintf(list_midi_affect[1594],"Call Plot window");
sprintf(list_midi_affect[1659],"Call Draw window");
sprintf(list_midi_affect[1662],"Call Echo window");
sprintf(list_midi_affect[1829],"Call Bazookat window");
sprintf(list_midi_affect[1541],"Exclude CH. from GM");
sprintf(list_midi_affect[1542],"Hipass Mode");

sprintf(list_midi_affect[1592],"Fgroup Mode");

sprintf(list_midi_affect[1593],"Send MidiOut Faders");


sprintf(list_midi_affect[1625],"Midi Affectation");

sprintf(list_midi_affect[1626],"Call Menus Widow");

/////////////Gridplayers//////////////////////////////////////
for (int gl=0;gl<4;gl++)
{
sprintf(list_midi_affect[1472+gl],"On/Off View Gpl %d",gl+1);
sprintf(list_midi_affect[1476+gl],"Minus sel Gpl %d",gl+1);
sprintf(list_midi_affect[1480+gl],"Plus sel Gpl %d",gl+1);
sprintf(list_midi_affect[1484+gl],"Minus Step Gpl %d",gl+1);
sprintf(list_midi_affect[1488+gl],"Plus Step Gpl %d",gl+1);
sprintf(list_midi_affect[1492+gl],"Play Gpl %d",gl+1);
sprintf(list_midi_affect[1496+gl],"Seek Gpl %d",gl+1);
sprintf(list_midi_affect[1500+gl],"AutostopGpl %d",gl+1);
sprintf(list_midi_affect[1504+gl],"Slave Gpl %d",gl+1);
sprintf(list_midi_affect[1508+gl],"Speed Gpl %d",gl+1);
sprintf(list_midi_affect[1512+gl],"Goto ON Gpl %d",gl+1);
sprintf(list_midi_affect[1516+gl],"Count ON Gpl %d",gl+1);
sprintf(list_midi_affect[1520+gl],"SeekPos ON Gpl %d",gl+1);
sprintf(list_midi_affect[1524+gl],"StopPlay ON Gpl %d",gl+1);
sprintf(list_midi_affect[1528+gl],"GridCall Gpl %d",gl+1);
sprintf(list_midi_affect[1532+gl],"StepCallx7 Gpl %d",gl+1);
sprintf(list_midi_affect[1536+gl],"StepCall Gpl %d",gl+1);
}
sprintf(list_midi_affect[1540],"Slave Speed CueList Gpl1");

//PLOT///////////////////////////////////////////////////

sprintf(list_midi_affect[1595],"Show Levels");
sprintf(list_midi_affect[1596],"Show Levels from faders");
sprintf(list_midi_affect[1597],"Plot UP list");
sprintf(list_midi_affect[1598],"Plot DOWN list");
sprintf(list_midi_affect[1599],"Plot CC list");
sprintf(list_midi_affect[1600],"Plot ADD list");
sprintf(list_midi_affect[1601],"Rotate selected");
sprintf(list_midi_affect[1602],"DUB selected");
sprintf(list_midi_affect[1603],"Delete selected");
sprintf(list_midi_affect[1604],"SentTo/Grp selected");
sprintf(list_midi_affect[1605],"Select Layer 1");
sprintf(list_midi_affect[1606],"Select Layer 2");
sprintf(list_midi_affect[1607],"Select Layer 3");
sprintf(list_midi_affect[1608],"Select Layer 4");
sprintf(list_midi_affect[1609],"Layer MODE");
sprintf(list_midi_affect[1610],"Relativ xy CH");
sprintf(list_midi_affect[1611],"Relativ xy Name");
sprintf(list_midi_affect[1612],"Relativ xy Gels");
sprintf(list_midi_affect[1613],"Relativ xy Dim");
sprintf(list_midi_affect[1614],"Relativ xy Notes");
for(int pr=0;pr<8;pr++)
{
sprintf(list_midi_affect[1615+pr],"Relativ Preset %d", pr+1);
}
//channels///////////////////////////////////////////////////

sprintf(list_midi_affect[1624],"Channel Handle Bar");
sprintf(list_midi_affect[1644],"Classical CH View");
for(int pr=0;pr<16;pr++)
{
sprintf(list_midi_affect[1628+pr],"Channel View %d", pr+1);
}

///////////////DRAW/////////////////////////////////////
sprintf(list_midi_affect[1658],"Brush Type");
for(int pr=0;pr<6;pr++)
{
sprintf(list_midi_affect[1646+pr],"Draw Matrix %d", pr+1);
}

sprintf(list_midi_affect[1652],"Draw Mode");
sprintf(list_midi_affect[1653],"Brush Pressure");
sprintf(list_midi_affect[1654],"Brush Angle");

sprintf(list_midi_affect[1655],"Ghost Level");
sprintf(list_midi_affect[1656],"Continuous GPL");

sprintf(list_midi_affect[1660],"Draw MidiX");
sprintf(list_midi_affect[1661],"Draw MidiY");

////////ECHO ///////////////////////////////////////////
for(int pr=0;pr<24;pr++)
{
sprintf(list_midi_affect[1663+pr],"Echo Preset %d", pr+1);
}
sprintf(list_midi_affect[1686],"ECHO MODE");
sprintf(list_midi_affect[1687],"SNAP FADER");
sprintf(list_midi_affect[1688],"BOUNCE");
sprintf(list_midi_affect[1689],"SNAP KILL & BOUNCE");
sprintf(list_midi_affect[1690],"RECALL FADER");

sprintf(list_midi_affect[1691],"Previous Chan");
sprintf(list_midi_affect[1692],"Next Chan");
sprintf(list_midi_affect[1693],"Gravity");
sprintf(list_midi_affect[1694],"Mass");
sprintf(list_midi_affect[1695],"Energy");
sprintf(list_midi_affect[1696],"ChanMode");

/////////ARDUINO/////////////////////////////////////
for (int i=0;i<63;i++)
{
  sprintf(list_midi_affect[1830+i],"Arduino analog in %d ON/OFF",i);
}

//////////MIDI CLOCK/////////////////////////////////
sprintf(list_midi_affect[1894],"MidiClock Level");
for (int i=0;i<16;i++)
{
 sprintf(list_midi_affect[1895+i],"MidiClock Speed_%d", i+1);
}

return(0);
}

int print_ch_macro( int cp)
{

//macro
for(int m=0; m<4;m++)
{
if(channel_macro_reaction[cp][m]!=0)
{
char titlemacro[8];
char titlemacro2[24];
char titlemacro3[8];
switch(channel_macro_reaction[cp][m])
{
case 0:
sprintf(titlemacro,"-");
break;
case 1:
sprintf(titlemacro,">=");
break;
case 2:
sprintf(titlemacro,">");
break;
case 3:
sprintf(titlemacro,"==");
break;
case 4:
sprintf(titlemacro,"!=");
break;
case 5:
sprintf(titlemacro,"<=");
break;
case 6:
sprintf(titlemacro,"<");
break;
case 7:
sprintf(titlemacro,"Follow");
break;
default:
break;
}
switch(channel_macro_action[cp][m])
{
case 0:
sprintf(titlemacro2,"-");
break;
case 1:
sprintf(titlemacro2,"Bang Banger");
break;
case 2:
sprintf(titlemacro2,"Load Audio");
break;
case 3:
sprintf(titlemacro2,"Play A.Pl");
break;
case 4:
sprintf(titlemacro2,"Stop A.Pl");
break;
case 5:
sprintf(titlemacro2,"Seek A.Pl");
break;
case 6:
sprintf(titlemacro2,"Loop ON A.Pl");
break;
case 7:
sprintf(titlemacro2,"Loop OFF A.Pl");
break;
case 8:
sprintf(titlemacro2,"Volume A.Pl");
break;
case 9:
sprintf(titlemacro2,"Pan A.Pl");
break;
case 10:
sprintf(titlemacro2,"Pitch A.Pl");
break;
case 11:
sprintf(titlemacro2, "Midi Ch15 CC");
break;
case 12:
sprintf(titlemacro2, "Midi Ch15 KOn");
break;
case 13:
sprintf(titlemacro2, "Midi Ch15 KOff");
break;
default:
break;
}
switch(macro_channel_on[cp][m])
{
case 0:
sprintf(titlemacro3,"Off");
break;
case 1:
sprintf(titlemacro3,"ON");
break;
default: break;
}
sprintf(header_export,"Macro %d: %s / %d / %s / %d / %s\n",m+1,titlemacro,channel_macro_val[cp][m][0],titlemacro2,channel_macro_val[cp][m][1],titlemacro3);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
}
verification_fin_de_page();
}

return(0);
}


int print_ch_from_plot( int ch)
{

char gellist[72];
char gely[24];

for(int c=0;c<4;c++)
{
for (int s=1;s<=nbre_symbols_on_plot[c];s++)
{
if(symbol_channel_is[c][s]==ch)//report des symboles correspondant au circuit
{
strcpy(gellist,"");
strcpy(gely,"");
for(int g=0;g<3;g++)//3 slots de gelat par symbol
{
if( gelat[c][s][g]!=0)//si une gelat non zero
{


switch(gelat_family[c][s][g])
{
case 0:
sprintf(gely," Lee %d", gelat[c][s][g]);
break;
case 1:
sprintf(gely," Rosco %d", gelat[c][s][g]);
break;
case 2:
sprintf(gely," GamC. %d", gelat[c][s][g]);
break;
case 3:
sprintf(gely," Apollo %d", gelat[c][s][g]);
break;
default:
strcpy(gely,"");
break;
}
strcat(gellist,gely);
strcpy(gely,"");
}
}
sprintf(header_export,"%s %s \n",symbol_nickname[ ( symbol_type[c][s] ) ],gellist);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
strcpy(gellist,"");
strcpy(header_export,"");
for(int no=0;no<4;no++)
{
if(strcmp(symbol_note[c][s][no],"")!=0)
{
sprintf(header_export,"Note %d:  %s",no+1,symbol_note[c][s][no]);
draw_info(page, 130, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");
}
}
}
}
}
 return(0);
}

int print_midi_command(int idMidi)
{
char typ_temp[16];
switch(miditable[0][idMidi])
  {
  case 0: sprintf(typ_temp,"Note");break;
  case 1: sprintf(typ_temp,"Key On");break;
  case 2: sprintf(typ_temp,"Key Off");break;
  case 4: sprintf(typ_temp,"Ctrl Change");break;
  default: sprintf(typ_temp,"-");break;
  break;
  }
sprintf(header_export, " %s: %s Chan %d Pitch %d \n",list_midi_affect[idMidi],typ_temp, miditable[1][idMidi],miditable[2][idMidi]);
if(miditable[1][idMidi]!=999)
{
draw_info(page, 120, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
}
return(0);
}







int draw_pdf_icat_preset(int prst)
{
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
HPDF_Page_SetFontAndSize (page, def_font,10);
HPDF_Page_SetRGBStroke (page, 0.0,0.6,0.8);//couleur ligne
sprintf(header_export,"iCAT preset %d", prst+1);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

//recalcul rapport à l orientation et au format
switch(surface_type)
{
case 0://iPOD
   if(iCat_preset_orientation[prst]==0)
   {
    L_tablier_iCat=160;H_tablier_iCat=240;
   }
   else {L_tablier_iCat=240;H_tablier_iCat=160;}
break;
case 1://iPAD
   if(iCat_preset_orientation[prst]==0)
   {
    L_tablier_iCat=384;H_tablier_iCat=512;
   }
   else {
   L_tablier_iCat=512;H_tablier_iCat=384;
   }
break;
default:
break;
}

HPDF_REAL xx=40;
HPDF_REAL yy=debut_lignes -(position_ligne1+(cmptline_pdf*12))-H_tablier_iCat;


//tablier GUI
HPDF_Page_SetRGBFill (page, 1.0, 1.0, 1.0);//couleur remplissage
HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 0.0);//couleur ligne
HPDF_Page_Rectangle  (page, xx,yy,L_tablier_iCat,H_tablier_iCat);
HPDF_Page_FillStroke (page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne

HPDF_Page_SetFontAndSize (page, def_font,6);
HPDF_Page_SetRGBFill (page, 1.0, 1.0, 1.0);//couleur remplissage
//dessin sliders
if(iCat_nbre_de_sliders[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_sliders[prst]+1;sl++)
{
//vertical
          if(iCat_orientation_slider[prst][sl]==0)
                          {l_sl=iCatSlidersizeX; h_sl=iCatSlidersizeY;}
                          //horizontal
          else
                 { l_sl=iCatSlidersizeY;h_sl=iCatSlidersizeX;}
//affichage si dans tablier
if(iCat_pos_slider[prst][sl][0]<L_tablier_iCat &&  iCat_pos_slider[prst][sl][1]<H_tablier_iCat)
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_Rectangle  (page,
                      xx+iCat_pos_slider[prst][sl][0],
                      yy+( H_tablier_iCat - (iCat_pos_slider[prst][sl][1]+ ((h_sl*ratio_iCat_slider[prst][sl])/2) )),
                      (l_sl*ratio_iCat_slider[prst][sl])/2,
                      (h_sl*ratio_iCat_slider[prst][sl])/2);//la size est divisee par 2
HPDF_Page_Stroke (page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage
sprintf(header_export,"Sld.%d",sl);
draw_info(page,xx+iCat_pos_slider[prst][sl][0],yy+15+( H_tablier_iCat - (iCat_pos_slider[prst][sl][1]+ ((h_sl*ratio_iCat_slider[prst][sl])/2) )),header_export);
}

}
}

//dessin boutons
if(iCat_nbre_de_boutons[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_boutons[prst]+1;sl++)
{
//affichage si dans tablier
if(iCat_pos_bouton[prst][sl][0]<L_tablier_iCat &&  iCat_pos_bouton[prst][sl][1]<H_tablier_iCat)
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_Rectangle  (page,
                      xx+iCat_pos_bouton[prst][sl][0],
                      yy+( H_tablier_iCat - (iCat_pos_bouton[prst][sl][1]+ (largueur_bouton*ratio_iCat_button[prst][sl])/2) ),
                      (largueur_bouton*ratio_iCat_button[prst][sl])/2,
                      ((largueur_bouton*ratio_iCat_button[prst][sl])/2));
HPDF_Page_Stroke (page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage
sprintf(header_export,"Bt.%d",sl);
draw_info(page,xx+iCat_pos_bouton[prst][sl][0],yy+15+( H_tablier_iCat - (iCat_pos_bouton[prst][sl][1]+ ((largueur_bouton*ratio_iCat_button[prst][sl])/2) )),header_export);
}

}
}


//dessin strings
if(iCat_nbre_de_strings[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_strings[prst]+1;sl++)
{
//affichage si dans tablier
if(iCat_pos_string[prst][sl][0]<L_tablier_iCat &&  iCat_pos_string[prst][sl][1]<H_tablier_iCat)
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_Rectangle  (page,
                      xx+iCat_pos_string[prst][sl][0],
                      yy+( H_tablier_iCat - (iCat_pos_string[prst][sl][1]+ (hauteur_string*ratio_iCat_string[prst][sl])/2) ),
                      (largeur_string*ratio_iCat_string[prst][sl])/2,
                      ((hauteur_string*ratio_iCat_string[prst][sl])/2));
HPDF_Page_Stroke (page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage
sprintf(header_export,"Str.%d",sl);
draw_info(page,xx+iCat_pos_string[prst][sl][0],yy+15+( H_tablier_iCat - (iCat_pos_string[prst][sl][1]+ ((hauteur_string*ratio_iCat_string[prst][sl])/2) )),header_export);
}

}
}

//dessin tracking zones
if(iCat_nbre_de_tracking_zone[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_tracking_zone[prst]+1;sl++)
{
//affichage si dans tablier
if(iCat_pos_trackzone[prst][sl][0]<L_tablier_iCat &&  iCat_pos_trackzone[prst][sl][1]<H_tablier_iCat)
{

HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_Rectangle  (page,
                      xx+iCat_pos_trackzone[prst][sl][0],
                      yy+( H_tablier_iCat - (iCat_pos_trackzone[prst][sl][1]+ (largeur_trackzone*ratio_iCat_trackzone[prst][sl])/2) ),
                      (largeur_trackzone*ratio_iCat_trackzone[prst][sl])/2,
                      ((largeur_trackzone*ratio_iCat_trackzone[prst][sl])/2));
HPDF_Page_Stroke (page);
HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);//couleur ligne
HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);//couleur remplissage
sprintf(header_export,"TrckZ.%d",sl);
draw_info(page,xx+iCat_pos_trackzone[prst][sl][0],yy+15+( H_tablier_iCat - (iCat_pos_trackzone[prst][sl][1]+ ((largeur_trackzone*ratio_iCat_trackzone[prst][sl])/2) )),header_export);
}

}
}




////DESCRIPTIONS

cmptline_pdf+=(( H_tablier_iCat/12)+2);
//SLIDERS
cmptline_pdf++;
if(iCat_nbre_de_sliders[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_sliders[prst]+1;sl++)
{
sprintf(header_export,"Slider %d = ",sl);
char tmpf[34];
switch(iCat_affectation_slider_type_is[prst][sl])
{
case 0://desafected
sprintf(tmpf,"-");
break;
case 1: //faders  lvl
sprintf(tmpf,"Fader Level: %d",iCat_affectation_slider_value_is[prst][sl]);
break;
case 2://faders speeed
sprintf(tmpf,"Fader Speed: %d",iCat_affectation_slider_value_is[prst][sl]);
break;
case 3://sequenciel
sprintf(tmpf,"Sequences: %d",iCat_affectation_slider_value_is[prst][sl]);
break;
case 4://grand master
sprintf(tmpf,"GrandMaster");
break;
case 5://level wheel
sprintf(tmpf,"Level Wheel");
break;
case 6://mover
sprintf(tmpf,"Mover Params %d",iCat_affectation_slider_value_is[prst][sl]);
break;
default:
sprintf(tmpf,"-");
break;
}
strcat(header_export,tmpf);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
HPDF_Page_SetFontAndSize (page, def_font,10);
verification_fin_de_page();
HPDF_Page_SetFontAndSize (page, def_font,6);
}
}



//BOUTONS
if(iCat_nbre_de_boutons[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_boutons[prst]+1;sl++)
{
sprintf(header_export,"Button %d = ",sl);
char tmpf[34];
switch(iCat_affectation_bouton_type_is[prst][sl])
{
case 0://desafected
sprintf(tmpf,"-");
break;
case 1: //faders
sprintf(tmpf,"Faders: ");
break;
case 2://mini faders
sprintf(tmpf,"MiniFaders: ");
break;
case 3://sequenciel
sprintf(tmpf,"Sequences: ");
break;
case 4://emulate
sprintf(tmpf,"Emulate Kbd: ");
break;
case 5: //Bangers
sprintf(tmpf,"Bangers:");
break;
case 6: //iCat menus
sprintf(tmpf,"iCat navigation: ");
break;
default:
break;
}
strcat(header_export,tmpf);


switch(iCat_affectation_bouton_type_is[prst][sl])
{
case 1: //faders
switch(iCat_affectation_bouton_action_is[prst][sl])
     {

      case 1: //fader up
      sprintf(tmpf,"UP %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 2://fader down
      sprintf(tmpf,"DOWN %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 3://Fader saw
      sprintf(tmpf,"SAW %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 4:
      sprintf(tmpf,"ToPREVDock %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 5:
      sprintf(tmpf,"ToNEXTDock %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 6:
      sprintf(tmpf,"Up/Down %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 7:
      sprintf(tmpf,"LOCK %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 8:
      sprintf(tmpf,"FLASH %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;

      case 9:
      sprintf(tmpf,"L/Unloop dock %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 10:
      sprintf(tmpf,"L/Unloop all %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 11:
      sprintf(tmpf,"Play embedded %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 12:
      sprintf(tmpf,"Seek embedded %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 13:
      sprintf(tmpf,"Loop embedded %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      default:
      sprintf(tmpf,"-");
      break;
      }
      //fin faders
break;
case 2://minifaders

     switch(iCat_affectation_bouton_action_is[prst][sl])
     {
     case 0://desafected
      sprintf(tmpf,"-");
      break;
      case 1: //fader up
      sprintf(tmpf,"UP");
      break;
      case 2://fader down
      sprintf(tmpf,"DOWN");
      break;
      case 3://Fader saw
      sprintf(tmpf,"SAW");
      break;
      case 4:
      sprintf(tmpf,"ToPREVDock");
      break;
      case 5:
      sprintf(tmpf,"ToNEXTDock");
      break;
      case 6:
      sprintf(tmpf,"Up/Down");
      break;
      case 7:
      sprintf(tmpf,"LOCK");
      break;
      case 8:
      sprintf(tmpf,"FLASH");
      break;
      case 9:
      sprintf(tmpf,"L/Unloop dock");
      break;
      case 10:
      sprintf(tmpf,"L/Unloop all");
      break;
      case 11:
      sprintf(tmpf,"Dock -");
      break;
      case 12:
      sprintf(tmpf,"Dock +");
      break;
      case 13:
      sprintf(tmpf,"Play embedded");
      break;
      case 14:
      sprintf(tmpf,"All at 0");
      break;
      case 15:
      sprintf(tmpf,"SetPos");
      break;
      case 16:
      sprintf(tmpf,"Select MF %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 17:
      sprintf(tmpf,"UnSelect All MF");
      break;
      case 18:
      sprintf(tmpf,"Select All MF");
      break;
      case 19:
      sprintf(tmpf,"Select MF Pst %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 20:
      sprintf(tmpf,"Select Lock %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      default:
      break;
      }//fin minifaders
break;

case 3://sequences
switch(iCat_affectation_bouton_action_is[prst][sl])
     {
     case 0://desafected
      sprintf(tmpf,"-");
      break;
      case 1:
      sprintf(tmpf,"GO");
      break;
      case 2:
      sprintf(tmpf,"GO BACK");
      break;
      case 3://Fader saw
      sprintf(tmpf,"JUMP");
      break;
      case 4:
      sprintf(tmpf,"STAGE -");
      break;
      case 5:
      sprintf(tmpf,"STAGE +");
      break;
      case 6:
      sprintf(tmpf,"PRESET -");
      break;
      case 7:
      sprintf(tmpf,"PRESET +");
      break;
      case 8:
      sprintf(tmpf,"GOTO");
      break;

default:
sprintf(tmpf,"-");
break;
}
break;
//fin sequences
case 4://emulate
     switch(iCat_affectation_bouton_action_is[prst][sl])
     {
      case 0:
      sprintf(tmpf,"0");
      break;
      case 1:
      sprintf(tmpf,"1");
      break;
      case 2:
      sprintf(tmpf,"2");
      break;
      case 3:
      sprintf(tmpf,"3");
      break;
      case 4:
      sprintf(tmpf,"4");
      break;
      case 5:
      sprintf(tmpf,"5");
      break;
      case 6:
      sprintf(tmpf,"6");
      break;
      case 7:
      sprintf(tmpf,"7");
      break;
      case 8:
      sprintf(tmpf,"8");
      break;
      case 9:
      sprintf(tmpf,"9");
      break;
      case 10:
      sprintf(tmpf,".");
      break;
      case 11:
      sprintf(tmpf,"PLUS");
      break;
      case 12:
      sprintf(tmpf,"MINUS");
      break;
      case 13:
      sprintf(tmpf,"ALL");
      break;
      case 14:
      sprintf(tmpf,"INV");
      break;
      case 15:
      sprintf(tmpf,"TAB");
      break;
      case 16:
      sprintf(tmpf,"ESC");
      break;
      case 17:
      sprintf(tmpf,"ENT");
      break;
      case 18://FULL
      sprintf(tmpf,"/100");
      break;
      case 19://a ZERO
      sprintf(tmpf,"/0");
      break;
      case 20://backspace
      sprintf(tmpf,"BCKSP");
      break;
      case 21://DEL
      sprintf(tmpf,"DEL");
      break;
      case 22://arrow Up
      sprintf(tmpf,"UP");
      break;
      case 23://arrow down
      sprintf(tmpf,"DOWN");
      break;
      case 24://arrow left
      sprintf(tmpf,"LEFT");
      break;
      case 25://arrow right
      sprintf(tmpf,"RIGHT");
      break;
      case 26:
      sprintf(tmpf,"F1");
      break;
      case 27:
      sprintf(tmpf,"F2");
      break;
      case 28:
      sprintf(tmpf,"F3");
      break;
      case 29:
      sprintf(tmpf,"F4");
      break;
      case 30:
      sprintf(tmpf,"F11");
      break;
      case 31:
      sprintf(tmpf,"F12");
      break;
      case 32:
      sprintf(tmpf,"SHFT");
      break;
      case 33:
      sprintf(tmpf,"CTRL");
      break;
      default:
      sprintf(tmpf,"-");
      break;
     }

break;
//fin emulate
case 5://banger
switch(iCat_affectation_bouton_action_is[prst][sl])
     {
      case 0:
      sprintf(tmpf,"-");
      break;
      case 1:
      sprintf(tmpf,"Bang Solo %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      default: break;
      }
break;
case 6://icat commandes
      switch(iCat_affectation_bouton_action_is[prst][sl])
     {
      case 0:
      sprintf(tmpf,"-");
      break;
      case 1:
      sprintf(tmpf,"Page -");
      break;
      case 2:
      sprintf(tmpf,"Page +");
      break;
      case 3:
      sprintf(tmpf,"Page Num: %d",iCat_affectation_bouton_value_is[prst][sl]);
      break;
      case 4:
      sprintf(tmpf,"Refresh Page");
      break;
      case 5:
      sprintf(tmpf,"Page Orientation");
      break;
      default:
      sprintf(tmpf,"-");
      break;
      }
break;
//fin icat commandes
default:
sprintf(tmpf,"-");
break;
}

strcat(header_export,tmpf);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
HPDF_Page_SetFontAndSize (page, def_font,10);
verification_fin_de_page();
HPDF_Page_SetFontAndSize (page, def_font,6);
}
}

///STRINGS
cmptline_pdf++;
if(iCat_nbre_de_strings[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_strings[prst]+1;sl++)
{
sprintf(header_export,"String %d = ",sl);
char tmpf[34];

switch(iCat_affectation_string_type_is[prst][sl])
{
case 0://desafected
sprintf(tmpf,"-");
break;
case 1: //Feedback
sprintf(tmpf,"Feedback:");
break;
case 2: //sequenciel
sprintf(tmpf,"Sequences:");
break;
default:
  sprintf(tmpf,"-");
break;
}
strcat(header_export,tmpf);

switch(iCat_affectation_string_type_is[prst][sl])
{
case 0://desafected
sprintf(tmpf,"-");
break;
case 1: //Feedback

     switch(iCat_affectation_string_action_is[prst][sl])
     {
     case 0://desafected
      sprintf(tmpf,"-");
      break;
      case 1: //input
      sprintf(tmpf,"Input");
      break;
      case 2://last ch
      sprintf(tmpf,"Last CH.");
      break;
      case 3://dimmers
      sprintf(tmpf,"DIM.");
      break;
      case 4://last order
      sprintf(tmpf,"Last Order");
      break;
      case 5:
      sprintf(tmpf,"Confirm");
      break;
      default:
      sprintf(tmpf,"-");
      break;
      }

break;
//fin feedback

case 2://sequences
    switch(iCat_affectation_string_action_is[prst][sl])
     {
     case 0://desafected
      sprintf(tmpf,"-");
      break;
      case 1: //X1
      sprintf(tmpf,"Stage");
      break;
      case 2://X2
      sprintf(tmpf,"Preset");
      break;
      case 3://Before 1
      sprintf(tmpf,"Mem. Before 1");
      break;
      case 4://Mem +
      sprintf(tmpf,"Mem. After 1");
      break;
      default:
      sprintf(tmpf,"-");
      break;
      }
break; //fin  stringsequences
default:
      sprintf(tmpf,"-");
break;
}

strcat(header_export,tmpf);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
HPDF_Page_SetFontAndSize (page, def_font,10);
verification_fin_de_page();
HPDF_Page_SetFontAndSize (page, def_font,6);
}
}
///TRACkING ZONE
cmptline_pdf++;
if(iCat_nbre_de_tracking_zone[prst]>0)
{
for(int sl=1;sl<iCat_nbre_de_tracking_zone[prst]+1;sl++)
{
sprintf(header_export,"TrackingZone %d = ",sl);
char tmpf[34];

switch(iCat_trackzone_type_is[prst][sl] )//mover
{
case 0://desafected
sprintf(tmpf,"-");
break;
case 1://mover
sprintf(tmpf,"Mover %d",iCat_trackzone_affectation_is[prst][sl]);
break;
default:
sprintf(tmpf,"-");
break;
}
strcat(header_export,tmpf);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
HPDF_Page_SetFontAndSize (page, def_font,10);
verification_fin_de_page();
HPDF_Page_SetFontAndSize (page, def_font,6);
}
}
saut_de_page();




return(0);
}















int do_pdf_export()
{
index_is_saving=1;
int comptch=0;
cmptline_pdf=0;

sprintf(rep,"%s\\import_export\\pdf\\",mondirectory);
chdir(rep);
//////////////



    strcpy (fname, importfile_name);

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        sprintf (string_Last_Order,"error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }


    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);


/* Add a new page object. */
num_page_pdf=1;
page= HPDF_AddPage (pdf);
height = HPDF_Page_GetHeight (page);
width = HPDF_Page_GetWidth (page);

/* Print the lines of the page. */
    HPDF_Page_SetLineWidth (page, 1);
    HPDF_Page_Rectangle (page, 0, 0, width , height );
    HPDF_Page_Stroke (page);

/* Print the title of the page */
    def_font = HPDF_GetFont (pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize (page, def_font, 13);
    tw = HPDF_Page_TextWidth (page, page_title);
    HPDF_Page_BeginText (page);
    HPDF_Page_TextOut (page, 50, height - 30, page_title);
    HPDF_Page_EndText (page);

debut_lignes=(height -30);
//sab 02/03/2014 unused var HPDF_REAL nbre_de_lignes_pdf=(height -30)/10;

/* header logiciel */
    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, def_font, 10);
    sprintf(header_export,"Export PDF from WHITECAT Lighting Board. %s",versionis);
    HPDF_Page_TextOut (page, 50, debut_lignes - 20,header_export);
    HPDF_Page_EndText (page);
    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, def_font, 10);
    sprintf(header_export,"http://www.le-chat-noir-numerique.fr");
    HPDF_Page_TextOut (page, 50, debut_lignes - 30,header_export);
    HPDF_Page_EndText (page);
//logo



//page 1
    sprintf(header_export,"page %d", num_page_pdf);
    draw_numpage(page,width/2,20,header_export);
    position_ligne1= 50;
////////////////////////////////////////////////////////////////////////////////
////////MEMOIRES////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///MEMOIRES//////////////////////////////////

if(specify_who_to_save_PDF[0]==1)
{
draw_section (page, 100,debut_lignes -70 , "Memories", 1.0,0.0,0.0);

for(int m=0;m<10000;m++)
{
if(MemoiresExistantes[m]==1)
{
comptch=0;
sprintf(header_export,"Mem %d.%d", (m/10),(m%10));
if(MemoiresExclues[m]==1){strcat(header_export, " >>>>> [ MEMORY IS EXCLUDED from CueList ]");}
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

sprintf(header_export,"%s %s", descriptif_memoires[m], annotation_memoires[m]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
cmptline_pdf++;
 ////0=DIN  1=IN 2=DOUT 3=OUT
sprintf(header_export,"Stage: d:%.1f  OUT: %.1f  | Memory: d:%.1f  IN: %.1f", Times_Memoires[m][2], Times_Memoires[m][3],Times_Memoires[m][0],Times_Memoires[m][1]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean pour la boucle
if(Links_Memoires[m]==1)
{
strcpy(header_export,"Link to next Mem ");
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
draw_fleche_link( page, 70, debut_lignes -(position_ligne1 +(cmptline_pdf*12))+10);
cmptline_pdf++;
}
strcpy(header_export,"");//clean pour la boucle
if(Banger_Memoire[m]!=0)
{
sprintf(header_export,"Banger %d     - %s",Banger_Memoire[m],bangers_name[(Banger_Memoire[m])-1]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
}
strcpy(header_export,"");//clean pour la boucle
for(int c=1;c<513;c++)
{
if(Memoires[m][c]>0)
{
if(comptch==0){cmptline_pdf++; strcpy(header_export,"");}//retour ligne après 10 circuits
sprintf(little_header,"%d=%d   ",c,(int)((float)(Memoires[m][c])/2.55));
strcat(header_export,little_header);
comptch++;
if(comptch>10)
{
comptch=0;
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
}
}
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);//fin de la recherche
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");//clean pour la boucle
}
strcpy(header_export,"");//clean pour la boucle
}

////////////////////SEPARATION GRANDE PARTIE////////////////////////////////////
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
//fin block mems
}



//////////////////CHANNEL VIEW/////////////////////////////////////////////////
if(specify_who_to_save_PDF[1]==1)
{

draw_section (page, 100,debut_lignes -70 , "Channel Views", 0.0,0.0,0.7);

for(int v=0;v<16;v++)
{
if(channel_number_in_View[v]>0)
{
cmptline_pdf++;
cmptline_pdf++;

verification_fin_de_page();

sprintf(header_export,"Channel View %d [%d]: %s", v+1,channel_number_in_View[v],channel_view_Name[v]);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");
for(int chm=0;chm<513;chm++)
{

if(check_presence_of_A_channel_in_A_view(v,chm)==1)
{

 if(comptch==0){cmptline_pdf++; strcpy(header_export,"");}//retour ligne après 10 circuits
 if(chm<100)  {sprintf(little_header,"%d  -  ",chm);}
 else {sprintf(little_header,"%d - ",chm);}
 strcat(header_export,little_header);
 comptch++;
 if(comptch>18)
 {
 comptch=0;
 draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
 cmptline_pdf++;
 verification_fin_de_page();
 }

}

}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);//fin de la recherche
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");//clean pour la boucle
comptch=0;
}
strcpy(header_export,"");

//fin vues
}



cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
//FIN BLOCK CHANNEL VIEW
}


///////////////////////////////////////////////////////////////////////////////
////////////////LISTE couplée à PLOT //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

if(specify_who_to_save_PDF[2]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Channels: Plot + List ", 0.5,0.0,1.0);

//detection des listes de circuits
for(int cp=1;cp<513;cp++)
{
if(check_channel_is_patched(cp)==1)
{
sprintf(header_export,"Ch.%d : %s\n",cp,descriptif_projecteurs[cp]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
print_ch_from_plot(cp);
cmptline_pdf++;
verification_fin_de_page();
print_ch_macro(cp);
cmptline_pdf++;
verification_fin_de_page();
}
}
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
//fin bloc


}

///////////////////////////////////////////////////////////////////////////////
////////////////PATCH//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[3]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Patch per channels", 1.0,0.0,0.0);

int cmptdim=0;
strcpy(header_export,"");

bool someone_ISpatched=0;
for(int circ=1;circ<513;circ++)
{

sprintf(header_export,"Channel %d -> Dim.",circ);
    for (int cpatch=1; cpatch<513; cpatch++)
    {
    if(Patch[cpatch]==circ)
    {
    someone_ISpatched=1;
    sprintf(little_header," %d [%d] -",cpatch, curves[cpatch]+1);
    strcat(header_export,little_header);
    cmptdim++;
    if(cmptdim>7)
        {
        cmptdim=0;
        draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
        strcpy(header_export,"");
        cmptline_pdf++;
        verification_fin_de_page();
        }
    }
    }
if(someone_ISpatched==1)
{
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
cmptdim=0;
}
strcpy(header_export,"");
someone_ISpatched=0;
cmptdim=0;
}
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}

if(specify_who_to_save_PDF[4]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Patch per dimmers", 1.0,0.0,0.0);

int cmptdim=0;
for (int cpatch=1; cpatch<513; cpatch++)
{
if(cmptdim==0){cmptline_pdf++; strcpy(header_export,"");}//retour ligne après 10 circuits
sprintf(little_header,"Dim.%d=Ch.%d [%d]    ",cpatch, Patch[cpatch], curves[cpatch]+1);
strcat(header_export,little_header);
cmptdim++;
if(cmptdim>4)
{
cmptdim=0;
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");
}
}

cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}
///////////////////////////////////////////////////////////////////////////////
/////////////////////////BANGER////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[5]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Banger", 1.0,0.0,0.0);

strcpy(header_export,"");
//////////////////Procedure bangers//////////////////////////////////////
bool there_is_someone_in_banger=0;
char header_banger_action[64];
char header_banger_typ[64];
for(int f=0;f<127;f++)
{
for(int bgtest=0;bgtest<6;bgtest++)
{
if(bangers_type[f][bgtest]!=0){there_is_someone_in_banger=1;break;}
}
if(there_is_someone_in_banger==1)
{
sprintf(header_export,"Banger %d / %s",f+1, bangers_name[f]);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");//clean
for(int bg=0;bg<6;bg++)
{
//affichage genres types
switch(bangers_type[f][bg])
{
case 0:
     sprintf(header_banger_typ,"-");
     sprintf(header_banger_action,"-");
break;
case 1:
     sprintf(header_banger_typ,"Faders");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"Lock");
     break;
     case 1:
     sprintf(header_banger_action,"Up");
     break;
     case 2:
     sprintf(header_banger_action,"Down");
     break;
     case 3:
     sprintf(header_banger_action,"Saw");
     break;
     case 4:
     sprintf(header_banger_action,"To Prev.Dock");
     break;
     case 5:
     sprintf(header_banger_action,"To Next Dock");
     break;
     case 6:
     sprintf(header_banger_action,"Up/Down loop");
     break;
     case 7:
     sprintf(header_banger_action,"Set Dock Looped");
     break;
     case 8:
     sprintf(header_banger_action,"Set All Looped");
     break;
     case 9:
     sprintf(header_banger_action,"Set Dock Is");
     break;
     case 10:
     sprintf(header_banger_action,"Set LFO at");
     break;
     case 11:
     sprintf(header_banger_action,"Set Fader at");
     break;
     case 12:
     sprintf(header_banger_action,"SetStopPos at");
     break;
     case 13:
     sprintf(header_banger_action,"StopPos ON/OFF");
     break;
     case 14:
     sprintf(header_banger_action,"Paste to Seq.");
     break;
     case 15:
     sprintf(header_banger_action,"Fader MidiOut");
     break;
     case 16:
     sprintf(header_banger_action,"ALL  : Faders at 0");
     break;
     case 17:
     sprintf(header_banger_action,"ALL  : Speed at 0");
     break;
     case 18:
     sprintf(header_banger_action,"ALL  : Lock at 0");
     break;
     case 19:
     sprintf(header_banger_action,"ALL  : LFO at 0");
     break;
     case 20:
     sprintf(header_banger_action,"ALL  : Loop at 0");
     break;
     case 21:
     sprintf(header_banger_action,"ALL  : All at 0");
     break;
     case 22:
     sprintf(header_banger_action,"ALL  : MidiOut at 0");
     break;
     case 23:
     sprintf(header_banger_action,"ALL : RECALL");
     break;
     case 24:
     sprintf(header_banger_action,"Lock Preset");
     break;
     break;
     case 25:
     sprintf(header_banger_action,"Fader: Set Curve");
     break;
     case 26:
     sprintf(header_banger_action,"Fader: LoadChaser");
     break;
     case 27:
     sprintf(header_banger_action,"Fader: PlayChaser");
     break;
     case 28:
     sprintf(header_banger_action,"Fader: SeekChaser");
     break;
     case 29:
     sprintf(header_banger_action,"Fader: LoopChaser");
     break;
     case 30:
     sprintf(header_banger_action,"Fader: Autol.Chaser");
     break;
     case 31:
     sprintf(header_banger_action,"Fader: Set DCH.");
     break;
     case 32:
     sprintf(header_banger_action,"Fader: SetCH Full");
     break;
     case 33:
     sprintf(header_banger_action,"Fader: SetCH 0");
     break;
     case 34:
     sprintf(header_banger_action,"Damper On/Off");
     break;
     case 35:
     sprintf(header_banger_action,"Damper SetDecay");
     break;
     case 36:
     sprintf(header_banger_action,"Damper SetDelta");
     break;
     case 37:
     sprintf(header_banger_action,"Damper Mode");
     break;
     default:
     break;
     }
break;
case 2:
     sprintf(header_banger_typ,"Send Midi");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"Key-On V:127");
     break;
     case 1:
     sprintf(header_banger_action,"Key-On V:0");
     break;
     case 2:
     sprintf(header_banger_action,"Key-Off V:127");
     break;
     case 3:
     sprintf(header_banger_action,"Ctrl-Change V:127");
     break;
     case 4:
     sprintf(header_banger_action,"Ctrl-Change V:0");
     break;
     case 5:
     sprintf(header_banger_action,"Ctrl-Change Ch:0");
     break;
     case 6:
     sprintf(header_banger_action,"Ctrl-Change Ch:1");
     break;
     case 7:
     sprintf(header_banger_action,"Ctrl-Change Ch:2");
     break;
     case 8:
     sprintf(header_banger_action,"Ctrl-Change Ch:3");
     break;
     case 9:
     sprintf(header_banger_action,"Ctrl-Change Ch:4");
     break;
     case 10:
     sprintf(header_banger_action,"Ctrl-Change Ch:5");
     break;
     case 11:
     sprintf(header_banger_action,"Ctrl-Change Ch:6");
     break;
     case 12:
     sprintf(header_banger_action,"Ctrl-Change Ch:7");
     break;
     case 13:
     sprintf(header_banger_action,"Ctrl-Change Ch:8");
     break;
     case 14:
     sprintf(header_banger_action,"Ctrl-Change Ch:9");
     break;
     case 15:
     sprintf(header_banger_action,"Ctrl-Change Ch:10");
     break;
     case 16:
     sprintf(header_banger_action,"Ctrl-Change Ch:11");
     break;
     case 17:
     sprintf(header_banger_action,"Ctrl-Change Ch:12");
     break;
     case 18:
     sprintf(header_banger_action,"Ctrl-Change Ch:13");
     break;
     case 19:
     sprintf(header_banger_action,"Ctrl-Change Ch:14");
     break;
     case 20:
     sprintf(header_banger_action,"Ctrl-Change Ch:15");
     break;
     case 21:
     sprintf(header_banger_action,"Set Faders/Sp Out");
     break;
     case 22:
     sprintf(header_banger_action,"Set ChasersTr Out");
     break;
     case 23:
     sprintf(header_banger_action,"Re-emit ALL Out");
     break;
     case 24:
     sprintf(header_banger_action,"MidiClock ON");
     break;
     case 25:
     sprintf(header_banger_action,"MidiClock OFF");
     break;
     case 26:
     sprintf(header_banger_action,"MidiClock RATE");
     break;
     case 27:
     sprintf(header_banger_action,"Msg START");
     break;
     case 28:
     sprintf(header_banger_action,"Msg STOP");
     break;
     case 29:
     sprintf(header_banger_action,"Msg CONTINUE");
     break;
     default:
     break;
     }
break;
case 3:
     sprintf(header_banger_typ,"Windows");
     switch(bangers_action[f][bg])
     {
       case 1:
     sprintf(header_banger_action,"Sequences");
     break;
     case 2:
     sprintf(header_banger_action,"Fader space");
     break;
     case 3:
     sprintf(header_banger_action,"MiniFaders");
     break;
     case 4:
     sprintf(header_banger_action,"Banger");
     break;
     case 5:
     sprintf(header_banger_action,"Audio Players");
     break;
     case 6:
     sprintf(header_banger_action,"Time Window");
     break;
     case 7:
     sprintf(header_banger_action,"Plot Window");
     break;
     case 8:
     sprintf(header_banger_action,"List Window");
     break;
     case 9:
     sprintf(header_banger_action,"Trichromy");
     break;
     case 10:
     sprintf(header_banger_action,"Video-tracking");
     break;
     case 11:
     sprintf(header_banger_action,"Chasers Window");
     break;
     case 12:
     sprintf(header_banger_action,"GridPlayers");
     break;
     case 13:
     sprintf(header_banger_action,"Draw Window");
     break;
     case 14:
     sprintf(header_banger_action,"Echo Window");
     break;
     case 15:
     sprintf(header_banger_action,"Mover Window");
     break;
     case 16:
     sprintf(header_banger_action,"NumPad Window");
     break;
     case 17:
     sprintf(header_banger_action,"CFG MENU");
     break;
     case 18:
     sprintf(header_banger_action,"iCAT Builder");
     break;
     default:
     sprintf(header_banger_action,"-");
     break;
     }
break;
case 4:
     sprintf(header_banger_typ,"Alarm");
     sprintf(header_banger_action,string_alarm[index_banger_selected]);
break;
case 5:
     sprintf(header_banger_typ,"AudioPlayers");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"Clear Player");
     break;
     case 1:
     sprintf(header_banger_action,"Load in Player");
     break;
     case 2:
     sprintf(header_banger_action,"SetPlay Player");
     break;
     case 3:
     sprintf(header_banger_action,"Load & Play");
     break;
     case 4:
     sprintf(header_banger_action,"SetLoop Player");
     break;
     case 5:
     sprintf(header_banger_action,"Seek Player");
     break;
     case 6:
     sprintf(header_banger_action,"SetVolume Player");
     break;
     case 7:
     sprintf(header_banger_action,"Set Cue Player");
     break;
     case 8:
     sprintf(header_banger_action,"Seek to CueIn Pl.");
     break;
     case 9:
     sprintf(header_banger_action,"SetPan Player");
     break;
     case 10:
     sprintf(header_banger_action,"SetPitch Player");
     break;
     case 11:
     sprintf(header_banger_action,"SetMidiOut Player");
     break;
     default:
     break;
     }
break;

case 6:
     sprintf(header_banger_typ,"Sequences");
     switch(bangers_action[f][bg])
     {
      case 0://stage jump
      sprintf(header_banger_action,"SetMem onStage");
      break;
      case 1://preset jump
      sprintf(header_banger_action,"SetMem onPreset");
      break;
      case 2://set Speed
      sprintf(header_banger_action,"SetSpeed at");
      break;
      case 3://Set Link
      sprintf(header_banger_action,"SetLink On");
      break;
      case 4://Set Banger
      sprintf(header_banger_action,"SetBanger On");
      break;
      case 5://refresh
      sprintf(header_banger_action,"Reload Stage");
      break;
      case 6://refresh
      sprintf(header_banger_action,"Reload Preset");
      break;
      case 7://refresh
      sprintf(header_banger_action,"GO");
      break;
      case 8://set Blind
      sprintf(header_banger_action,"Set Blind");
      break;
      default:
      break;
     }

break;

case 7:
     sprintf(header_banger_typ,"Chasers");
     switch(bangers_action[f][bg])
     {
      case 0://call num chaser
      sprintf(header_banger_action,"Ch.Sel. Is");
      break;
      case 1://play chaser
      sprintf(header_banger_action,"Play");
      break;
      case 2://seek chaser
      sprintf(header_banger_action,"Seek");
      break;
      case 3://loop chaser
      sprintf(header_banger_action,"Loop");
      break;
      case 4://way chaser
      sprintf(header_banger_action,"Way");
      break;
      case 5://aller retour chaser
      sprintf(header_banger_action,"Aller-Retour");
      break;
      case 6://timemode
      sprintf(header_banger_action,"Time Mode");
      break;
      case 7://slaviness
      sprintf(header_banger_action,"Slave");
      break;
      case 8://Beg P
      sprintf(header_banger_action,"Set Beg Point");
      break;
      case 9://End P
      sprintf(header_banger_action,"Set End Point");
      break;
      case 10://Position
      sprintf(header_banger_action,"Set Position");
      break;
      case 11://toggle track
      sprintf(header_banger_action,"Toggle Track");
      break;
      case 12://ALL ON OFF
      sprintf(header_banger_action,"ALL ON");
      break;
      case 13://INV ON OFF
      sprintf(header_banger_action,"ON INV");
      break;
      case 14://ALL OFF
      sprintf(header_banger_action,"ALL OFF");
      break;
      case 15://call preset
      sprintf(header_banger_action,"ON Preset");
      break;
      case 16://level track
      sprintf(header_banger_action,"Ch.Sel. Level Track");
      break;
      default:
      break;
      }
break;
case 8:
     sprintf(header_banger_typ,"MiniFaders");
     switch(bangers_action[f][bg])
     {
      case 0:
      sprintf(header_banger_action,"Select Num.");
      break;
      case 1:
      sprintf(header_banger_action,"Select All");
      break;
      case 2:
      sprintf(header_banger_action,"Sel. Flash");
      break;
      case 3:
      sprintf(header_banger_action,"Sel. Tog.Lock");
      break;
      case 4:
      sprintf(header_banger_action,"Sel. Tog.Loop");
      break;
      case 5:
      sprintf(header_banger_action,"Sel. Tog.Up");
      break;
      case 6:
      sprintf(header_banger_action,"Sel. Tog.Down");
      break;
      case 7:
      sprintf(header_banger_action,"Sel. Tog.Saw");
      break;
      case 8:
      sprintf(header_banger_action,"Sel. Tog. AllLoop");
      break;
      case 9:
      sprintf(header_banger_action,"Sel. AllAt");
      break;
      case 10:
      sprintf(header_banger_action,"Sel. Tog.StopPos.");
      break;
      case 11:
      sprintf(header_banger_action,"Sel. ToPrev");
      break;
      case 12:
      sprintf(header_banger_action,"Sel. ToNext");
      break;
      case 13:
      sprintf(header_banger_action,"Sel. Tog.Up/Down");
      break;
      case 14:
      sprintf(header_banger_action,"Sel. Dock -");
      break;
      case 15:
      sprintf(header_banger_action,"Sel. Dock +");
      break;
      case 16:
      sprintf(header_banger_action,"Sel. PlayChaser");
      break;
      case 17:
      sprintf(header_banger_action,"Minifader Preset");
      break;
      default:
      break;
      }
break;
case 9:
     sprintf(header_banger_typ,"iCat");
     switch(bangers_action[f][bg])
     {
      case 0:
      sprintf(header_banger_action,"Select Page Num");
      break;
      case 1:
      sprintf(header_banger_action,"Select Page -");
      break;
      case 2:
      sprintf(header_banger_action,"Select Page +");
      break;
      case 3:
      sprintf(header_banger_action,"Refresh Page");
      break;
      case 4:
      sprintf(header_banger_action,"Toggle Orientation");
      break;
      default:
      break;
      }
break;
case 10: //chrono
    sprintf(header_banger_typ,"Chrono");
     switch(bangers_action[f][bg])
     {
      case 0:
      sprintf(header_banger_action,"Clear Chrono");
      break;
      case 1:
      sprintf(header_banger_action,"Play Chrono");
      break;
      case 2:
      sprintf(header_banger_action,"Set Chrono Page");
      break;
      default:
      break;
      }
break;
case 11://set channel
    sprintf(header_banger_typ,"SetChannel");
     switch(bangers_action[f][bg])
     {
      case 0:
      sprintf(header_banger_action,"/100 Set At");
      break;
      case 1:
      sprintf(header_banger_action,"/100 Set +");
      break;
      case 2:
      sprintf(header_banger_action,"/100 Set -");
      break;
      case 3:
      sprintf(header_banger_action,"/255 Set At");
      break;
      case 4:
      sprintf(header_banger_action,"/255 Set +");
      break;
      case 5:
      sprintf(header_banger_action,"/255 Set -");
      break;
      case 6:
      sprintf(header_banger_action,"Macro ON");
      break;
      case 7:
      sprintf(header_banger_action,"Macro OFF");
      break;
           case 8:
      sprintf(header_banger_action,"FromTo Macro1 ON");
      break;
      case 9:
      sprintf(header_banger_action,"FromTo Macro2 ON");
      break;
      case 10:
      sprintf(header_banger_action,"FromTo Macro3 ON");
      break;
      case 11:
      sprintf(header_banger_action,"FromTo Macro4 ON");
      break;
      case 12:
      sprintf(header_banger_action,"FromTo Macro1 OFF");
      break;
      case 13:
      sprintf(header_banger_action,"FromTo Macro2 OFF");
      break;
      case 14:
      sprintf(header_banger_action,"FromTo Macro3 OFF");
      break;
      case 15:
      sprintf(header_banger_action,"FromTo Macro4 OFF");
      break;
      default:
      break;
      }
break;

case 12://set banger
     sprintf(header_banger_typ,"SetBanger");
     switch(bangers_action[f][bg])
     {
      case 0:
      sprintf(header_banger_action,"On/Off");
      break;
      case 1:
      sprintf(header_banger_action,"RollBack");
      break;
      case 2:
      sprintf(header_banger_action,"Loop ON");
      break;
      case 3:
      sprintf(header_banger_action,"Loop OFF");
      break;
      default:
      break;
      }

break;


case 13://midi mute
     sprintf(header_banger_typ,"MidiMute");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"[GLOBAL]");
     break;
     case 1:
     sprintf(header_banger_action,"GrandMaster");
     break;
     case 2:
     sprintf(header_banger_action,"Fader");
     break;
     case 3:
     sprintf(header_banger_action,"LFO");
     break;
     case 4:
     sprintf(header_banger_action,"Sequences");
     break;
     case 5:
     sprintf(header_banger_action,"Trichromy");
     break;
     case 6:
     sprintf(header_banger_action,"VideoTracking");
     break;
     case 7:
     sprintf(header_banger_action,"Audio Level");
     break;
     case 8:
     sprintf(header_banger_action,"Audio Pan");
     break;
     case 9:
     sprintf(header_banger_action,"Audio Pitch");
     break;

     default:
     break;
     }
case 14://Grid
sprintf(header_banger_typ,"GridPlayer");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"1-Load&Play");
     break;
     case 1:
     sprintf(header_banger_action,"2-Load&Play");
     break;
     case 2:
     sprintf(header_banger_action,"3-Load&Play");
     break;
     case 3:
     sprintf(header_banger_action,"4-Load&Play"); //grid step
     break;
     case 4:
     sprintf(header_banger_action,"1-Stop&Load");    //grid step
     break;
     case 5:
     sprintf(header_banger_action,"2-Stop&Load");
     break;
     case 6:
     sprintf(header_banger_action,"3-Stop&Load");
     break;
     case 7:
     sprintf(header_banger_action,"4-Stop&Load");
     break;
     case 8:
     sprintf(header_banger_action,"Play/Pause");   //Player ON/OFF
     break;
     case 9:
     sprintf(header_banger_action,"Seek");     //bang
     break;
     case 10:
     sprintf(header_banger_action,"Autostop");
     break;
     case 11:
     sprintf(header_banger_action,"Macro Goto");
     break;
     case 12:
     sprintf(header_banger_action,"Macro Seek");
     break;
     case 13:
     sprintf(header_banger_action,"Macro StopPlay");
     break;
     case 14:
     sprintf(header_banger_action,"Set Seek");     //player seek
     break;
     case 15:
     sprintf(header_banger_action,"Set Accel."); //player 0-127
     break;
     case 16:
     sprintf(header_banger_action,"Set Slave"); //player ON/OFF
     break;
     case 17:
     sprintf(header_banger_action,"SnapFader"); //player ON/OFF
     break;
     case 18:
     sprintf(header_banger_action,"Next Step"); //GPL STP
     break;
     case 19:
     sprintf(header_banger_action,"Previous Step"); //GPL Stp
     break;
     case 20:
     sprintf(header_banger_action,"Goto=SeekStep"); //Goto position take seek step reference
     break;
     case 21:
     sprintf(header_banger_action,"Def.as SeekSt."); //Actual step is define as seekstep
     break;
     case 22:
     sprintf(header_banger_action,"Clear SeekSteps!"); //clear all seek steps
     break;
     case 23:
     sprintf(header_banger_action,"Clear Grid in GPL !!!"); //clear all grid
     break;
     default:
     break;
     }
break;
case 15://Hardware
sprintf(header_banger_typ,"Hardware");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"Arduino ON/Off");
     break;
     case 1:
     sprintf(header_banger_action,"Arduino Baudrate");
     break;
     case 2:
     sprintf(header_banger_action,"Analog input ON");
     break;
     default:
     break;
     }
break;
case 16://emulate KBD
sprintf(header_banger_typ,"Emulate Kbd");
 switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"Kbd A");
     break;
     case 1:
     sprintf(header_banger_action,"Kbd B");
     break;
     case 2:
     sprintf(header_banger_action,"Kbd C");
     break;
     case 3:
     sprintf(header_banger_action,"Kbd D");
     break;
      case 4:
     sprintf(header_banger_action,"Kbd E");
     break;
      case 5:
     sprintf(header_banger_action,"Kbd F");
     break;
      case 6:
     sprintf(header_banger_action,"Kbd G");
     break;
      case 7:
     sprintf(header_banger_action,"Kbd H");
     break;
      case 8:
     sprintf(header_banger_action,"Kbd I");
     break;
      case 9:
     sprintf(header_banger_action,"Kbd J");
     break;
      case 10:
     sprintf(header_banger_action,"Kbd K");
     break;
      case 11:
     sprintf(header_banger_action,"Kbd L");
     break;
      case 12:
     sprintf(header_banger_action,"Kbd M");
     break;
      case 13:
     sprintf(header_banger_action,"Kbd N");
     break;
      case 14:
     sprintf(header_banger_action,"Kbd O");
     break;
      case 15:
     sprintf(header_banger_action,"Kbd P");
     break;
      case 16:
     sprintf(header_banger_action,"Kbd Q");
     break;
      case 17:
     sprintf(header_banger_action,"Kbd R");
     break;
      case 18:
     sprintf(header_banger_action,"Kbd S");
     break;
      case 19:
     sprintf(header_banger_action,"Kbd T");
     break;
      case 20:
     sprintf(header_banger_action,"Kbd U");
     break;
      case 21:
     sprintf(header_banger_action,"Kbd V");
     break;
      case 22:
     sprintf(header_banger_action,"Kbd W");
     break;
      case 23:
     sprintf(header_banger_action,"Kbd X");
     break;
      case 24:
     sprintf(header_banger_action,"Kbd Y");
     break;
      case 25:
     sprintf(header_banger_action,"Kbd Z");
     break;

     case 26:
     sprintf(header_banger_action,"Kbd SPACE");
     break;

     case 27:
     sprintf(header_banger_action,"Kbd DOT");
     break;

      case 28:
     sprintf(header_banger_action,"Kbd 0");
     break;
      case 29:
     sprintf(header_banger_action,"Kbd 1");
     break;
      case 30:
     sprintf(header_banger_action,"Kbd 2");
     break;
      case 31:
     sprintf(header_banger_action,"Kbd 3");
     break;
      case 32:
     sprintf(header_banger_action,"Kbd 4");
     break;
      case 33:
     sprintf(header_banger_action,"Kbd 5");
     break;
      case 34:
     sprintf(header_banger_action,"Kbd 6");
     break;
      case 35:
     sprintf(header_banger_action,"Kbd 7");
     break;
      case 36:
     sprintf(header_banger_action,"Kbd 8");
     break;
      case 37:
     sprintf(header_banger_action,"Kbd 9");
     break;

      case 38:
     sprintf(header_banger_action,"Kbd SHIFT");
     break;
      case 39:
     sprintf(header_banger_action,"Kbd CTRL");
     break;
      case 40:
     sprintf(header_banger_action,"Kbd ESC");
     break;
      case 41:
     sprintf(header_banger_action,"Kbd F1");
     break;
      case 42:
     sprintf(header_banger_action,"Kbd F2");
     break;
      case 43:
     sprintf(header_banger_action,"Kbd F3");
     break;
      case 44:
     sprintf(header_banger_action,"Kbd F4");
     break;
     case 45:
     sprintf(header_banger_action,"Kbd F5");
     break;
     case 46:
     sprintf(header_banger_action,"Kbd F6");
     break;
     case 47:
     sprintf(header_banger_action,"Kbd F7");
     break;
     case 48:
     sprintf(header_banger_action,"Kbd F8");
     break;
     case 49:
     sprintf(header_banger_action,"Kbd F9");
     break;
     case 50:
     sprintf(header_banger_action,"Kbd F10");
     break;
     case 51:
     sprintf(header_banger_action,"Kbd F11");
     break;
     case 52:
     sprintf(header_banger_action,"Kbd F12");
     break;
     case 53:
     sprintf(header_banger_action,"Kbd ENTER");
     break;
     case 54:
     sprintf(header_banger_action,"Kbd Bcksp");
     break;
     case 55:
     sprintf(header_banger_action,"Kbd Tab");
     break;
     case 56:
     sprintf(header_banger_action,"Kbd PLUS");
     break;
     case 57:
     sprintf(header_banger_action,"Kbd MINUS");
     break;
     case 58:
     sprintf(header_banger_action,"Kbd Arrow LEFT");
     break;
     case 59:
     sprintf(header_banger_action,"Kbd Arrow RIGHT");
     break;
     case 60:
     sprintf(header_banger_action,"Kbd Arrow UP");
     break;
     case 61:
     sprintf(header_banger_action,"Kbd Arrow DOWN");
     break;
     case 62:
     sprintf(header_banger_action,"Kbd Arrow DEL");
     break;
     default:
     break;
     }
break;
case 17:
sprintf(header_banger_typ,"Draw");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"Select Matrix");
     break;
     case 1:
     sprintf(header_banger_action,"Set Brush");
     break;
     case 2:
     sprintf(header_banger_action,"Set DrawMode");
     break;
     case 3:
     sprintf(header_banger_action,"Set Pressure");
     break;
     case 4:
     sprintf(header_banger_action,"Set Damper");
     break;
     case 5:
     sprintf(header_banger_action,"Set Ghost");
     break;
     case 6:
     sprintf(header_banger_action,"Set GPL");
     break;
     case 7:
     sprintf(header_banger_action,"Set Offset");
     break;
     case 8:
     sprintf(header_banger_action,"Clear Drawing");
     break;
     case 9:
     sprintf(header_banger_action,"Snap Fader");
     break;
     case 10:
     sprintf(header_banger_action,"Snap GridPl.");
     break;
     default:
     sprintf(header_banger_action,"-");
     break;
     }
break;
case 18:
sprintf(header_banger_typ,"Echo");
     switch(bangers_action[f][bg])
     {
     case 0:
     sprintf(header_banger_action,"Select Echo");
     break;
     case 1:
     sprintf(header_banger_action,"S.Set Fader");
     break;
     case 2:
     sprintf(header_banger_action,"S.ChanMode ");
     break;
     case 3:
     sprintf(header_banger_action,"S.SetChan /255");
     break;
     case 4:
     sprintf(header_banger_action,"S.SetChan /100");
     break;
     case 5:
     sprintf(header_banger_action,"S.Echo Mode");
     break;
     case 6:
     sprintf(header_banger_action,"S.SnapFader");
     break;
     case 7:
     sprintf(header_banger_action,"S.Bounce !");
     break;
     case 8:
     sprintf(header_banger_action,"S. S-K-B !");
     break;
     case 9:
     sprintf(header_banger_action,"S.BackFader");
     break;
     case 10:
     sprintf(header_banger_action,"S.SetGravity");
     break;
     case 11:
     sprintf(header_banger_action,"S.SetMass");
     break;
     case 12:
     sprintf(header_banger_action,"S.SetEnergy");
     break;
     case 13:
     sprintf(header_banger_action,"S.SetChanPos");
     break;
     case 14:
     sprintf(header_banger_action,"E.EchoMode");
     break;
     case 15:
     sprintf(header_banger_action,"E.SetFader");
     break;
     case 16:
     sprintf(header_banger_action,"E.SnapFader");
     break;
     case 17:
     sprintf(header_banger_action,"E.Bounce !");
     break;
     case 18:
     sprintf(header_banger_action,"E. S-K-B !");
     break;
     case 19:
     sprintf(header_banger_action,"E.BackFader");
     break;
     case 20:
     sprintf(header_banger_action,"E.ChanMode");
     break;
     case 21:
     sprintf(header_banger_action,"E.SetGravity");
     break;
     case 22:
     sprintf(header_banger_action,"E.SetMass");
     break;
     case 23:
     sprintf(header_banger_action,"E.SetEnergy");
     break;
     case 24:
     sprintf(header_banger_action,"E.SetChanPos");
     break;
     case 25:
     sprintf(header_banger_action,"E.ClearEcho");
     break;
     default:
     sprintf(header_banger_action,"-");
     break;
     }
break;


default:
break;
}
if(bangers_type[f][bg]!=0)//si il y a un type d evenement dedans
{
sprintf(header_export,"Event %d : %s",bg+1,header_banger_typ);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
draw_info(page, 220, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_banger_action);
sprintf(header_export,"Val 1: %d",bangers_params[f][bg][0]);
draw_info(page, 320, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
sprintf(header_export,"Val 2: %d",bangers_params[f][bg][1]);
draw_info(page, 400, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
sprintf(header_export,"delay: %.1f",bangers_delay[f][bg]);
draw_info(page, 500, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
}
verification_fin_de_page();
}
}
there_is_someone_in_banger=0;//pour check des autres bangers
strcpy(header_export,"");
strcpy(header_banger_action,"");
strcpy(header_banger_typ,"");
}
//////////FIN BLOCK BANGER//////////////////////////////////////////////////
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}
///////////////////////////////////////////////////////////////////////////////
/////////////////////////AUDIO////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[6]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Audio folder", 0.0, 0.0,1.0);


sprintf(header_export,"Content of /audio/%s",audio_folder);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for(int u=1;u<127;u++)
{
if(strcmp(list_audio_files[u],"")!=0)
{
 sprintf(header_export,"-%d : %s",u,list_audio_files[u]);


 if(audiofile_cue_in_out_pos[u][0]!=0 || audiofile_cue_in_out_pos[u][1]!=0)
 {
 sprintf(little_header,"  |  CueIn: %.1f CueOut: %.1f",(((float)audiofile_cue_in_out_pos[u][0])/44100),(((float)audiofile_cue_in_out_pos[u][1])/44100));
 strcat(header_export,little_header);
 }
 draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
 cmptline_pdf++;
verification_fin_de_page();
}
}

//fin audio block//////////////////////////////////////////////////////////////
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}
//////////////////Procedure bangers//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////////////FADERS////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[7]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Faders", 1.0,0.6,0.0);

bool there_is_someone_in_fader=0;
//////////////////Procedure sur faders//////////////////////////////////////
for(int f=0;f<48;f++)
{
there_is_someone_in_fader=0;
//test si dock dedans ou pas
for(int d=0;d<6;d++)
{
if(DockTypeIs[f][d]!=9)
{there_is_someone_in_fader=1;break;}
}
if(there_is_someone_in_fader==1)
{
sprintf(header_export,"FADER %d ",f+1);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");//clean
///////////////////////////paramétrages actuels du fader/////////////////////////////////
sprintf(header_export,"Curve [%d] ",FaderCurves[f]+1);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"LFO: Speed: %d  Mode: ",lfo_speed[f]);

//damper
int dc= 127*Fader_dampered[f].getdecay();
int ddt=127*Fader_dampered[f].getdt();
int md=Fader_dampered[f].getdampermode();
switch(fader_damper_is_on[f])
{
case 0:
sprintf(header_export,"Damper OFF/ D:%d D:%d Mode:%d",  dc,ddt,md);
break;
case 1:
sprintf(header_export,"Damper ON/ D:%d D:%d Mode:%d",  dc,ddt,md);
break;
default: break;
}
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

if(lfo_mode_is[f]!=0)
{
switch(lfo_mode_is[f])
{
case 1:
strcat(header_export," up ");
break;
case 2:
strcat(header_export," down ");
break;
default: break;
}
}
else if(lfo_cycle_is_on[f]==1)
{
strcat(header_export," saw ");
}
else
{
strcat(header_export," - ");
}
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Cycling docks : ");
if(lfo_do_next_step[f][0]==1)
{
strcat(header_export," to Previous dock");
}
else if(lfo_do_next_step[f][1]==1)
{
strcat(header_export," to Next dock");
}
if(lfo_cycle_steps[f]==1)
{
strcat(header_export," | Cycling Previous-Next");
}
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
if(LevelStopPos[f]!=0)
{
sprintf(header_export,"Stop position:  %d  ",(int)(((float)LevelStopPos[f])/2.55));
switch(ActionnateStopOn[f])
{
case 1:
strcat(header_export,"is ON");
break;
default: break;
}
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

}


if(autolaunch[f]==1)
{
 sprintf(header_export,"Autolaunch ON  ");
 draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
 cmptline_pdf++;
}



//DOCK SELECTED
for(int piu=0;piu<6;piu++)
{
if(DockIsSelected[f][piu]==1)
{
sprintf(header_export,"Dock selected: %d",piu+1);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
break;
}
}
cmptline_pdf++;
verification_fin_de_page();
strcpy(header_export,"");//clean
cmptline_pdf++;
///////////////////////////////////////////////////////////////////////////////
for(int d=0;d<6;d++)
{
if(DockTypeIs[f][d]!=9)//dock pas vide
{

comptch=0;
sprintf(header_export,"Dock %d: ", d+1);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
sprintf(header_export,"- %s",DockName[f][d]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"dIn:%.1f  IN: %.1f  | dOUT:%.1f  OUT: %.1f", time_per_dock[f][d][0],time_per_dock[f][d][1],time_per_dock[f][d][2],time_per_dock[f][d][3]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
if(is_dock_for_lfo_selected[f][d]==1)
{
strcpy(header_export,"Dock Loop ON");
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
}
strcpy(header_export,"");//clean
cmptline_pdf++;

switch(DockTypeIs[f][d])
{
case 0://channels
for(int c=1;c<513;c++)
{
if(FaderDockContains[f][d][c]>0)
{
if(comptch==0)
{
cmptline_pdf++;
strcpy(header_export,"");
}//retour ligne après 10 circuits

sprintf(little_header,"%d=%d   ",c,(int)((float)(FaderDockContains[f][d][c])/2.55));
strcat(header_export,little_header);
comptch++;
if(comptch>10)
{
comptch=0;
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
verification_fin_de_page();
}
}
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
break;

case 1://trichro
for (int fo=0;fo<8;fo++)
{
if(colorpreset_linked_to_dock[fo][0]==f)
{
if(colorpreset_linked_to_dock[fo][1]==d)
{
sprintf(header_export,"Trichromy preset %d \n",fo+1);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
}
}
}
break;

case 2://art net
strcpy(header_export,"");//clean
sprintf(header_export,"Art-Net Sub 0, Universe %d ",DockNetIs[f][d]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;

case 3://dmx in
strcpy(header_export,"");//clean
cmptline_pdf++;
strcpy(header_export,"Dmx-IN ");
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;

case 4://video
strcpy(header_export,"");//clean
cmptline_pdf++;
strcpy(header_export,"Video-tracking ");
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;


case 5://mems
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Memory: %d.%d ",DockHasMem[f][d]/10,DockHasMem[f][d]%10);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

strcpy(header_export,"");//clean
break;

case 6://audio volume
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Audio Volume Player %d  ",DockHasAudioVolume[f][d]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

strcpy(header_export,"");//clean
break;

case 7://audio pan
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Audio Pan Player %d  ",DockHasAudioPan[f][d]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;

case 8://audio pitch
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Audio Pitch Player %d  ",DockHasAudioPitch[f][d]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

strcpy(header_export,"");//clean
break;
/*
 case 9://no content
 petitchiffre.Print("-",x+((cmptfader*espacement)+(largeur+37)+15),  y +15+ (dd*40));
 break;*/

case 10://direct chan
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Direct Channel : %d",FaderDirectChan[f][d]);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;

case 11://fx
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Chaser : %d",ChaserAffectedToDck[f][d]+1);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;

case 12://grid
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"GridPlayer : %d",faders_dock_grid_affectation[f][d]+1);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;

case 13://fgroup
strcpy(header_export,"");//clean
cmptline_pdf++;
strcpy(header_export,"Fgroup containing faders:");
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
for(int ifo=0;ifo<48;ifo++)
{
if(fgroup[f][d][ifo]==1){strcat(header_export," %d -");}
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
break;

case 14://mover
strcpy(header_export,"");//clean
cmptline_pdf++;
strcpy(header_export,"Mover");
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;

case 15: //Draw
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Draw %d",(DrawAffectedToDck[f][d]+1));
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;
case 16: //echo
strcpy(header_export,"");//clean
cmptline_pdf++;
sprintf(header_export,"Echo %d",(echo_affected_to_dock[f][d]+1));
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
strcpy(header_export,"");//clean
break;
default:
break;
} //fin du switch case dock
cmptline_pdf++; //separateur de dock
}
}
}
}
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}
////////////////////////////////////////////////////////////////////////////////
//////////////////////CHASERS///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[8]==1)
{
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
draw_section (page, 100,debut_lignes -70 , "Chasers",0.0,0.5,0.0);

bool there_is_someone_in_chaser=0;
for(int i=0;i<128;i++)
{
there_is_someone_in_chaser=0;
for(int tr=0;tr<24;tr++)
{
for(int c=1;c<513;c++)
{
 if(TrackContains[i][tr][c]!=0){there_is_someone_in_chaser=1; break;}
}
}
if(there_is_someone_in_chaser==1)
{
sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
draw_pdf_chaser(i, page);
}
}

sprintf(header_export,"page %d", num_page_pdf);
draw_numpage(page,width/2,20,header_export);
page=HPDF_AddPage(pdf);cmptline_pdf=0;
num_page_pdf++;
HPDF_Page_SetRGBStroke (page, 0.0, 0.5, 0.5);//couleur ligne
HPDF_Page_BeginText (page);
HPDF_Page_SetFontAndSize (page, def_font, 10);
HPDF_Page_EndText (page);
strcpy(header_export,"");

}


//////////////////////////////////////////////////////////////////////////////
/////////////////////////Trichro///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[9]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Trichromy",0.5,0.6,0.0);

bool there_is_someone_in_color_preset=0;
for (int t=0;t<8;t++)
{
there_is_someone_in_color_preset=0;
//test de savoir si circuits affectes
for(int col=0;col<4;col++)
{
for(int circ=1;circ<513;circ++)
{
if(dock_color_channels[t][col][circ]!=0)
{
there_is_someone_in_color_preset=1;break;
}
}
}
if(there_is_someone_in_color_preset==1)
{
//titre trichro/quadri
switch(dock_color_type[t])
{
case 0:
sprintf(header_export,"Color Preset %d in Trichromy Mode",t+1);
break;
case 1:
sprintf(header_export,"Color Preset %d in Quadrichromy Mode",t+1);
break;
default: break;
}
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
///////
verification_fin_de_page();
switch(dock_color_type[t])
{
case 0:
sprintf(header_export,"Actual Color is: R=%d G=%d B=%d",picker_trichro[t][0],picker_trichro[t][1],picker_trichro[t][2]);
break;
case 1:
sprintf(header_export,"Actual Color is: R=%d G=%d B=%d Y=%d",picker_trichro[t][0],picker_trichro[t][1],picker_trichro[t][2],picker_trichro[t][3]);
break;
default: break;
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

for(int col=0;col<4;col++)
{
comptch=0;

switch (col)
{
case 0:
sprintf(header_export,"RED: ");
break;
case 1:
sprintf(header_export,"GREEN: ");
break;
case 2:
sprintf(header_export,"BLUE: ");
break;
case 3:
sprintf(header_export,"YELLOW: ");
break;
default: break;
}

for(int circ=1;circ<513;circ++)
{
if(dock_color_channels[t][col][circ]!=0)
{
//retour ligne
sprintf(little_header,"%d   - ",circ);
strcat(header_export,little_header);
comptch++;
if(comptch>12)
{
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
comptch=0;
strcpy(little_header,"");
strcpy(header_export,"");
}
}
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
}
}
cmptline_pdf++;
verification_fin_de_page();

}
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}
//////////////////////////////////////////////////////////////////////////////
/////////////////////////Tracking///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[10]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "Tracking Video",0.6,0.6,0.0);

sprintf(header_export,"Settings:");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Camera Video Size: %d x %d      - FPS: %d",video_size_x,video_size_y,fps_video_rate);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Image mode:");
if (flip_image==1) {strcat(header_export,"Flip ON / ");} else  {strcat(header_export,"Flip OFF / ");}
if (threshold_on==1) {sprintf(little_header,"Threshold ON : %d / ",threshold_level);} else  {sprintf(little_header,"Threshold OFF / ");}
strcat(header_export,little_header);
if (erode_mode==1) {sprintf(little_header,"Erode ON : %d / ",erode_level);} else  {sprintf(little_header,"Erode OFF / ");}
strcat(header_export,little_header);
if (blur_on==1) {strcat(header_export,"Blur ON / ");} else  {strcat(header_export,"Blur OFF / ");}
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

sprintf(header_export,"Background suppression: ");
if(ocv_calcul_mode==0){sprintf(little_header,"SNAP ON , div factor: %d ",div_facteur);}
else {sprintf(little_header,"SNAP OFF ( normal threshold capture)");}
strcat(header_export,little_header);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Decay position: %d",index_decay_tracker);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

cmptline_pdf++;
verification_fin_de_page();
bool there_is_a_roi_preset_affected=0;


bool test_there_is_a_channel=0;

for(int trk=0;trk<6;trk++)
{
sprintf(header_export,"Video Preset %d:",trk);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
for (int pr=0;pr<12;pr++)
{
//test de l affectation d un circuit à la ROI
there_is_a_roi_preset_affected=0;
for (int prp=0;prp<12;prp++)
{
for(int circ=1;circ<512;circ++)
{
if(tracking_contents[trk][prp][circ]!=0)
{
 there_is_a_roi_preset_affected=1; break;
}
}
}

if(there_is_a_roi_preset_affected==1)
{
test_there_is_a_channel=0;
sprintf(header_export,"Roi %d :  X: %d Y: %d  - Size X: %d Size Y: %d ",pr+1,tracking_coordonates[trk][pr][0],tracking_coordonates[trk][pr][1],tracking_coordonates[trk][pr][2],tracking_coordonates[trk][pr][3]);
draw_info(page, 120, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
sprintf(header_export,"Chan: ");
cmptline_pdf++;
cmptline_pdf++;
for(int circ=1;circ<512;circ++)
{
if(tracking_contents[trk][pr][circ]!=0)
{
test_there_is_a_channel=1;
sprintf(little_header,"%d   - ",circ);
strcat(header_export,little_header);
comptch++;
if(comptch>12)
{
draw_info(page, 120, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();
comptch=0;
strcpy(little_header,"");
strcpy(header_export,"");
}
}
}
if(test_there_is_a_channel==1)
{
draw_info(page, 120, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
cmptline_pdf++;
}

verification_fin_de_page();
}
}
}
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}
////GRIDPLAYERS ////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[11]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "GRIDPLAYERS",0.2,0.9,0.0);


draw_pdf_grid_players_config();
verification_fin_de_page();
}
////MOVER
if(specify_who_to_save_PDF[12]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "MOVER",0.6,0.0,0.6);
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}
///ECHO
if(specify_who_to_save_PDF[13]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "ECHO",0.0,0.4,0.9);
draw_pdf_echo_config();
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();
}

///DRAW
if(specify_who_to_save_PDF[14]==1)
{
saut_de_page();
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "DRAW",0.0,0.9,0.8);
cmptline_pdf++;
cmptline_pdf++;
draw_pdf_draw_config();
verification_fin_de_page();
}




////////////////////////////////////////////////////////////////////////////////
///////////////////////ARDUINO//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
if(specify_who_to_save_PDF[21]==1)
{
draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "ARDUINO",0.0,0.8,0.8);


sprintf(header_export,"Settings:");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Device on COM: %d - BaudRate: %d - Request Rate: %d",arduino_com0,arduino_baud_rate0,ARDUINO_RATE);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Parameters: ");
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Last I/O: %d Last ANALOG: %d",arduino_max_digital,arduino_max_analog);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
cmptline_pdf++;

sprintf(header_export,"I/O affectation:");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;


for(int i=2;i<=arduino_max_digital;i++)
{
switch(arduino_digital_type[i])
{
case 0://desafected
sprintf(header_export,"%d: -",i);
break;
case 1://input
sprintf(header_export,"%d: Input",i);
break;
case 2://PUL UP
sprintf(header_export,"%d:Pull Up",i);
break;
case 3://output
sprintf(header_export,"%d:Output",i);
break;
case 4://pwm
sprintf(header_export,"%d:PWM",i);
break;
case 5://servo
sprintf(header_export,"%d:SERVO",i);
break;
case 6://HF out
sprintf(header_export,"%d:HF OUT",i);
break;
case 7://HF in
sprintf(header_export,"%d:HF IN",i);
break;
default:
break;
}

if(arduino_digital_type[i]==1)//si de la famille des inputs
{
switch(arduino_digital_function_input[i][0])
{
case 0://desafected
strcat(header_export,"-");
break;
case 1: //fader up
sprintf(little_header,"Fader %d UP", arduino_digital_function_input[i][1]);
break;
case 2://fader down
sprintf(little_header,"Fader: %d DOWN", arduino_digital_function_input[i][1]);
break;
case 3://Fader saw
sprintf(little_header,"Fader: %d SAW", arduino_digital_function_input[i][1]);
break;
case 4:
sprintf(little_header,"Fader: %d ToPREVDock", arduino_digital_function_input[i][1]);
break;
case 5:
sprintf(little_header,"Fader: %d ToNEXTDock", arduino_digital_function_input[i][1]);
break;
case 6:
sprintf(little_header,"Fader: %d Up/Down", arduino_digital_function_input[i][1]);
break;
case 7:
sprintf(little_header,"Fader: %d LOCK", arduino_digital_function_input[i][1]);
break;
case 8:
sprintf(little_header,"Fader: %d FLASH", arduino_digital_function_input[i][1]);
break;
case 9:
sprintf(little_header,"Fader: %d All at 0", arduino_digital_function_input[i][1]);
break;
case 10:
sprintf(little_header,"Fader: %d L/Unloop dock", arduino_digital_function_input[i][1]);
break;
case 11:
sprintf(little_header,"Fader: %d L/Unloop all", arduino_digital_function_input[i][1]);
break;
case 12:
sprintf(little_header,"Seq: GO");
break;
case 13:
sprintf(little_header,"Seq: GO BACK");
break;
case 14:
sprintf(little_header,"Seq: JUMP");
break;
case 15:
sprintf(little_header,"Seq: SHIFT-W");
break;
case 16:
sprintf(little_header,"Seq: SHIFT-X");
break;
case 17:
sprintf(little_header,"As Key-On CH0 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 18:
sprintf(little_header,"As Key-On CH1 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 19:
sprintf(little_header,"As Key-On CH2 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 20:
sprintf(little_header,"As Key-On CH3 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 21:
sprintf(little_header,"As Key-On CH4 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 22:
sprintf(little_header,"As Key-On CH5 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 23:
sprintf(little_header,"As Key-On CH6 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 24:
sprintf(little_header,"As Key-On CH7 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 25:
sprintf(little_header,"As Key-On CH8 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 26:
sprintf(little_header,"As Key-On CH9 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 27:
sprintf(little_header,"As Key-On CH10 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 28:
sprintf(little_header,"As Key-On CH11 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 29:
sprintf(little_header,"As Key-On CH12 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 30:
sprintf(little_header,"As Key-On CH13 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 31:
sprintf(little_header,"As Key-On CH14 Pitch %d", arduino_digital_function_input[i][1]);
break;
case 32:
sprintf(little_header,"As Key-On CH15 Pitch %d", arduino_digital_function_input[i][1]);
break;
default:
break;
}
strcat(header_export,little_header);
}


if(arduino_digital_type[i]==2)//si de la famille des Outputs
{
switch(arduino_digital_function_output[i][0])
{
case 0://desafected
sprintf(little_header,"-");
break;
case 1: //relié à un circuit
sprintf(little_header,"Channel %d >10", arduino_digital_function_output[i][1]);
break;
case 2://relié à un fader
sprintf(little_header,"Fader %d >10", arduino_digital_function_output[i][1]);
break;
default: break;
}
strcat(header_export,little_header);
}

if(arduino_digital_type[i]==3)//si de la famille pwm
{
switch(arduino_digital_function_output[i][0])
{
case 0://desafected
sprintf(little_header,"-");
break;
case 1: //relié à un circuit
sprintf(little_header,"Channel %d >10", arduino_digital_function_output[i][1]);
break;
case 2://relié à un fader
sprintf(little_header,"Fader %d >10", arduino_digital_function_output[i][1]);
break;
default: break;
}
strcat(header_export,little_header);
}


draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

verification_fin_de_page();
//fin serie IO
}

cmptline_pdf++;

sprintf(header_export,"Analog affectation:");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
verification_fin_de_page();


for(int i=0;i<=arduino_max_analog;i++)
{
strcpy(header_export,"");
switch(arduino_analog_function_input[i])
{
case 0://desafected
sprintf(little_header,"-");
break;
case 1: //faders  lvl
sprintf(little_header,"Fader %d Level",arduino_analog_attribution_input[i]+1);
break;
case 2://faders speeed
sprintf(little_header,"Fader %d Speed",arduino_analog_attribution_input[i]+1);
break;
case 3://master
sprintf(little_header,"Grand Master");
break;
case 4://seq scene et preset et vitesse
sprintf(little_header,"Sequence: %d",arduino_analog_attribution_input[i]+1);
break;
case 5://relié à Draw
sprintf(little_header,"Draw X1");
break;
case 6://relié à Draw
sprintf(little_header,"Draw X2");
break;
case 7://relié à Draw
sprintf(little_header,"Draw Y1");
break;
case 8://relié à Draw
sprintf(little_header,"Draw Y2");
break;
case 9://Midi CH0
sprintf(little_header,"As CC CH0 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 10://Midi CH1
sprintf(little_header,"As CC CH1 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 11://Midi CH2
sprintf(little_header,"As CC CH2 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 12://Midi CH3
sprintf(little_header,"As CC CH3 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 13://Midi CH4
sprintf(little_header,"As CC CH4 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 14://Midi CH5
sprintf(little_header,"As CC CH5 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 15://Midi CH6
sprintf(little_header,"As CC CH6 Picth %d",arduino_analog_attribution_input[i]);
break;
case 16://Midi CH7
sprintf(little_header,"As CC CH7 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 17://Midi CH8
sprintf(little_header,"As CC CH8 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 18://Midi CH9
sprintf(little_header,"As CC CH9 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 19://Midi CH10
sprintf(little_header,"As CC CH10 Picth %d",arduino_analog_attribution_input[i]);
break;
case 20://Midi CH11
sprintf(little_header,"As CC CH11 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 21://Midi CH12
sprintf(little_header,"As CC CH12 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 22://Midi CH13
sprintf(little_header,"As CC CH13 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 23://Midi CH14
sprintf(little_header,"As CC CH14 Pitch %d",arduino_analog_attribution_input[i]);
break;
case 24://Midi CH15
sprintf(little_header,"As CC CH15 Pitch %d",arduino_analog_attribution_input[i]);
break;
default:
break;
}

strcat(header_export,little_header);
draw_info(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

verification_fin_de_page();
}
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////EXPORT MIDI////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

if(specify_who_to_save_PDF[22]==1)
{
generate_list_midi_for_pdf();


draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "MIDI AFFECTATIONS",1.0,0.0,0.0);

sprintf(header_export,"GRAND MASTER");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

print_midi_command(615);

sprintf(header_export,"MOVE FADER SPACE");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

print_midi_command(767);
print_midi_command(1627);

for(int i=0;i<48;i++)
{
sprintf(header_export,"FADER %d",i+1);
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
print_midi_command(i);
print_midi_command(i+48);
print_midi_command(i+97);
print_midi_command(i+146);
print_midi_command(i+196);
print_midi_command(i+245);
print_midi_command(i+294);
print_midi_command(i+343);
print_midi_command(i+392);
print_midi_command(i+441);
print_midi_command(i+499);
print_midi_command(i+556);
print_midi_command(i+685);
print_midi_command(i+802);
print_midi_command(i+851);
print_midi_command(i+900);
print_midi_command(i+1115);
print_midi_command(i+1164);
print_midi_command(i+1213);
print_midi_command(i+1278);
print_midi_command(i+1543);
print_midi_command(i+1912);
print_midi_command(i+1960);
print_midi_command(i+2008);
print_midi_command(i+2056);

}

sprintf(header_export,"MINIFADERS");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
print_midi_command(145);
for(int i=0;i<28;i++)
{
if(i+774!=793)
{
print_midi_command(i+774);
}
}
verification_fin_de_page();
sprintf(header_export,"CUELIST");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
for(int i=0;i<6;i++)
{
print_midi_command(i+491);
}
for(int i=0;i<6;i++)
{
print_midi_command(i+768);
}
print_midi_command(1591);
print_midi_command(1645);

verification_fin_de_page();

sprintf(header_export,"ALL AT ZERO");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
for(int i=0;i<8;i++)
{
print_midi_command(i+548);
}
verification_fin_de_page();


sprintf(header_export,"LOCK PRESETS");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
for(int i=0;i<8;i++)
{
print_midi_command(i+605);
}
verification_fin_de_page();

sprintf(header_export,"AUDIO PLAYERS");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for(int i=0;i<48;i++)
{
print_midi_command(i+616);
}
for(int i=0;i<4;i++)
{
 print_midi_command(i+1800);
}
for(int i=0;i<4;i++)
{
 print_midi_command(i+1805);
}
for(int i=0;i<4;i++)
{
 print_midi_command(i+1809);
}
for(int i=0;i<4;i++)
{
 print_midi_command(i+1813);
}
for(int i=0;i<4;i++)
{
 print_midi_command(i+1817);
}
for(int i=0;i<4;i++)
{
 print_midi_command(i+1821);
}
verification_fin_de_page();

sprintf(header_export,"NUMPAD");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for(int i=0;i<21;i++)
{
print_midi_command(i+491);
}

print_midi_command(1825);
print_midi_command(1826);
print_midi_command(1827);
print_midi_command(1828);
verification_fin_de_page();

sprintf(header_export,"BANGER WINDOW");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for(int i=0;i<9;i++)
{
print_midi_command(i+734);
}

verification_fin_de_page();

sprintf(header_export,"BANGERS SOLOS");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for (int l=0;l<127;l++)
{
print_midi_command(l+1343);
}

verification_fin_de_page();

sprintf(header_export,"FUNCTIONS");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for(int i=0;i<6;i++)
{
print_midi_command(i+743);

}

//fenetres
for(int i=0;i<11;i++)
{print_midi_command(i+747);}

for(int i=0;i<14;i++)
{
print_midi_command(i+1329);
}

print_midi_command(757);
print_midi_command(1625);//send midi out faders
print_midi_command(1592);//fgroup
print_midi_command(1593);//hipass
print_midi_command(1626);//menus
print_midi_command(1277);//midi mute
print_midi_command(1594);//PLOT
print_midi_command(1659);//DRAW
print_midi_command(1662);//ECHO
print_midi_command(1829);//Bazookat
print_midi_command(1541);//exclude
print_midi_command(1542);//hipass
verification_fin_de_page();

sprintf(header_export,"MIDICLOCK");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

print_midi_command(1894);//Midi clock level
for(int i=0;i<16;i++)
{
print_midi_command(i+1895);
}
verification_fin_de_page();


sprintf(header_export,"TIME");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
for(int i=0;i<9;i++)
{
print_midi_command(i+758);
}
verification_fin_de_page();

sprintf(header_export,"TRICHROMY");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
print_midi_command(497);

for(int i=0;i<8;i++)
{
print_midi_command(i+949);
}
verification_fin_de_page();

sprintf(header_export,"TRACKING VIDEO");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
print_midi_command(498);
for(int i=0;i<17;i++)
{
print_midi_command(i+957);
}

sprintf(header_export,"CHASERS WINDOW");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
for (int yu=0;yu<141;yu++)
{
print_midi_command(yu+974);
}
verification_fin_de_page();

cmptline_pdf++;
sprintf(header_export,"ARDUINO ANALOG IN : ");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
for (int yu=0;yu<63;yu++)
{
print_midi_command(yu+1830);
}
verification_fin_de_page();

verification_fin_de_page();

sprintf(header_export,"Fantastick-iCat");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);


for (int yu=0;yu<12;yu++)
{
print_midi_command(yu+1265);
}
verification_fin_de_page();

sprintf(header_export,"DRAW WINDOW");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for (int yu=0;yu<14;yu++)
{
print_midi_command(yu+1646);
}
print_midi_command(1660);
print_midi_command(1661);
verification_fin_de_page();

sprintf(header_export,"ECHO WINDOW");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

for (int yu=0;yu<35;yu++)
{
print_midi_command(yu+1663);
}

cmptline_pdf++;
cmptline_pdf++;
cmptline_pdf++;
verification_fin_de_page();


}

///////////////////////////////////////////////////////////////////////////////
/////////////EXPORT ICAT ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

if(specify_who_to_save_PDF[23]==1)
{
if(cmptline_pdf>20){saut_de_page();}//pour fenetre de tracage

draw_section (page, 100,debut_lignes -(position_ligne1 +(cmptline_pdf*12)), "FantaStick-iCat Interface Builder",0.0,0.6,0.8);
cmptline_pdf++;
cmptline_pdf++;

verification_fin_de_page();

sprintf(header_export,"iCAT-Fantastick parameters:");
draw_title(page, 50, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);

sprintf(header_export,"WhiteCat use adapter: %s", IP_fantastick);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"iOS device network adress is: %s", specified_fs_ip);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"UDP PORTS: Server (IN) : %d Client (OUT): %d",  serveurport_iCat, clientport_iCat);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
sprintf(header_export,"Data sending iteration: %d",  nbre_d_envois_de_l_info);
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;
switch(surface_type)
{
case 0:
sprintf(header_export,"Working space: iPhone");
break;
case 1:
sprintf(header_export,"Working space: iPad");
break;
default:
break;
}
draw_info(page, 100, debut_lignes -(position_ligne1 +(cmptline_pdf*12)),header_export);
cmptline_pdf++;

for(int pr=0;pr<8;pr++)
{
draw_pdf_icat_preset(pr);
}



}



////////////////////////////////////////////////////////////////////////////////
/////////FIN PDF////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

 // derniere page, marquage
sprintf(header_export,"page %d", num_page_pdf);
HPDF_Page_SetFontAndSize (page, def_font, 10);
draw_numpage(page,width/2,20,header_export);

HPDF_SaveToFile (pdf, fname);

/* clean up */
HPDF_Free (pdf);





//REROLL//////
sprintf(rep,"%s\\",mondirectory);
chdir (rep);
index_is_saving=0;
return(0);
}



