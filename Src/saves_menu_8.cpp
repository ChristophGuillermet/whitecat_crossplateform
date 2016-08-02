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

* \file saves_menu_8.cpp
* \brief {GUI window of save and load menu}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   GUI fonctions pour la fenêtre save menu
*
*   GUI window of save and load menu
*
**/

int scan_savesfolder()
{
    struct al_ffblk f;
    bool isDir;
    int nbre_de_shows=0;
    sprintf(rep,"%s\\saves",mondirectory);
    chdir(rep);

    if(!al_findfirst("*.*",&f,-1))
    {

            while(!al_findnext(&f))
            {
            int f_name_len = strlen(f.name);
            isDir=true;
            // check if it's a dir or a file
            for( int a=0;a<f_name_len;a++)
            {
                if(f.name[a]=='.')
                {
                    isDir=false;
                    break;
                }
            }
            // we've found a directory!
            if(isDir)
            {
		    sprintf(list_save_files[nbre_de_shows],f.name);
		    nbre_de_shows++;
            }
            }
    }
    al_findclose(&f);
//reroll
sprintf(rep,"%s\\",mondirectory);
chdir (rep);
return(0);
}

//sab 02/03/2014 int scan_importfolder(char *subdir)
void scan_importfolder(const char* subdir)
{
for(int i=0;i<127;i++)
{
 strcpy(list_import_files[i],"");
}

    struct al_ffblk f;
    bool isSomeone;
    int nrbe_de_fichiers=0;
    sprintf(rep,"%s\\import_export\\%s",mondirectory,subdir);
    chdir(rep);

    if(!al_findfirst("*.*",&f,-1))
    {
            while(!al_findnext(&f))
            {
            isSomeone=true;


            // we've found a directory!
            if(isSomeone && nrbe_de_fichiers<127)
            {
		    sprintf(list_import_files[nrbe_de_fichiers],f.name);
		    nrbe_de_fichiers++;
            }
            }
    }
    al_findclose(&f);
//REROLL
sprintf(rep,"%s\\",mondirectory);
chdir (rep);
//sab 02/03/2014 return(0);
}


int choose_personnal_preset_binary_save_load(int xs,int ys)
{
petitchiffre.Print("Personnal Presets:",xs-15,ys-15);
for(int i=0;i<4;i++)
{
Rect Carre(Vec2D(xs+(20*i),ys),Vec2D(10,10));
switch(i)
{
case 0:
Carre.Draw(CouleurBlind);
break;
case 1:
Carre.Draw(CouleurBleuProcedure);
break;
case 2:
Carre.Draw(CouleurGreen);
break;
case 3:
Carre.Draw(CouleurYellowFgroup);
break;
default: break;
}
Carre.DrawOutline(CouleurLigne.WithAlpha(0.5));

}
 return(0);
}


int do_logical_choose_personnal_preset_binary_save_load(int xs,int ys)
{
for(int i=0;i<4;i++)
{
if(window_focus_id==W_SAVE && mouse_button==1 && mouse_released==0 && mouse_x>=xs+(20*i) && mouse_x<=xs+(20*i)+10 && mouse_y>=ys && mouse_y<=ys+10)
{
mouse_released=1;

if(index_do_dock==1)
{
for(int p=0;p<80;p++)
{
preset_specify_who_to_save_load[p][i]=specify_who_to_save_load[p];
}
index_do_dock=0;
sprintf(string_Last_Order,"Recorded Personnal Save-Load Preset %d",i+1);
}

else if(index_main_clear==1)
{
for(int p=0;p<80;p++)
{
preset_specify_who_to_save_load[p][i]=0;
}
index_main_clear=0;
sprintf(string_Last_Order,"Cleared Personnal Save-Load Preset %d",i+1);
}

else
{
for(int p=0;p<80;p++)
{
specify_who_to_save_load[p]=preset_specify_who_to_save_load[p][i];
}
index_save_global_is=0;
sprintf(string_Last_Order,"Called Personnal Save-Load Preset %d",i+1);
}

}
}
 return(0);
}


int check_import_type()
{

if(index_is_saving==0)
{
if(strcmp(importfile_name,"ascii")==0){scan_importfolder("ascii");}
else if(strcmp(importfile_name,"pdf")==0){scan_importfolder("pdf");}
else if(strcmp(importfile_name,"plot")==0  ){scan_importfolder("plot");}
else if(strcmp(importfile_name,"schwz")==0){scan_importfolder("schwz");index_export_choice=1;isSchwz=1;}//christoph 16/06/14 debug perte fonctionnalité import whitecat
else if(strcmp(importfile_name,"..")==0){scan_importfolder("");line_import=0;}
else
{
//christoph 19/12/14
int f_name_len = strlen(importfile_name);
            // check if it's a dir or a file
          for(int a=0;a<f_name_len;a++)
          {
           if( importfile_name[a]=='.')
           {
                if((importfile_name[a+1]=='a' &&  importfile_name[a+2]=='s' &&  importfile_name[a+3]=='c')
                || (importfile_name[a+1]=='A' &&  importfile_name[a+2]=='S' &&  importfile_name[a+3]=='C')
                || (importfile_name[a+1]=='t' &&  importfile_name[a+2]=='x' &&  importfile_name[a+3]=='t')
                || (importfile_name[a+1]=='T' &&  importfile_name[a+2]=='X' &&  importfile_name[a+3]=='T')
                )
                {
                    isSchwz=0; isPdf=0; isAlq=0;
                    isASCII=1;index_export_choice=0;
                    sprintf(string_typeexport_view,">> ascii file");
                    scan_importfolder("ascii");
                    break;
                }

                if((importfile_name[a+1]=='a' &&  importfile_name[a+2]=='l' &&  importfile_name[a+3]=='q')
                || (importfile_name[a+1]=='A' &&  importfile_name[a+2]=='L' &&  importfile_name[a+3]=='Q'))
                {
                    isSchwz=0;  isPdf=0;
                    isASCII=0; isAlq=1;index_export_choice=2;
                    sprintf(string_typeexport_view,">> ascii alq file");
                    scan_importfolder("ascii");
                    break;
                }

                if((importfile_name[a+1]=='p' &&  importfile_name[a+2]=='d' &&  importfile_name[a+3]=='f')
                ||(importfile_name[a+1]=='P' &&  importfile_name[a+2]=='D' &&  importfile_name[a+3]=='F'))
                {   isSchwz=0;  isASCII=0; isAlq=0;
                    isPdf=1;index_export_choice=3;
                    sprintf(string_typeexport_view,">> PDF file");
                    scan_importfolder("pdf");
                    break;
                }


                else
                {
                isASCII=0; isPdf=0; isAlq=0; isSchwz=1;index_export_choice=1;
                sprintf(string_typeexport_view,">> schwartzpeter");
                scan_importfolder("schwz");
                }

           }
    }
}
}


return(0);
}



//sab 02/03/2014 int deroule_repertoire_export_import(int xrep, int yrep, char name_of_rep[25])
void deroule_repertoire_export_import(int xrep, int yrep, const std::string label)
{
//christoph 19/12/14 substr(0,25)>substr(0,24);
//const std::string name_of_rep = label.substr(0,24);
//////////////////////LISTE DOSSIERS ETC///////////////////////////////////////
petitchiffre.Print("Content of import_export folder:",xrep+10,yrep+170);
Rect BackDeroule(Vec2D(xrep,yrep+155),Vec2D(245,185));
BackDeroule.SetRoundness(15);
BackDeroule.Draw(CouleurConfig.WithAlpha(0.7));

for (int y=0;y<8;y++)
{
Rect OverFile(Vec2D(xrep+5,(yrep+185+(y*20)-10)),Vec2D(200,20));
OverFile.SetRoundness(7.5);

//affichage qui est selectionné
if(strcmp(importfile_name,list_import_files[importfile_selected])==0 && (importfile_selected==(y+line_import)))
{OverFile.Draw(CouleurFond.WithAlpha(0.5));}


if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+155 && mouse_y>(yrep+175+(y*20)) && mouse_y<(yrep+190+(y*20)))
{
OverFile.DrawOutline(CouleurLigne);
}
petitpetitchiffre.Print(list_import_files[line_import+y],xrep+10,yrep+185+(y*20));

 //fin des 8 lignes
}



//nom fichier save laod
Rect FrameSelected(Vec2D(xrep+5,yrep+347),Vec2D(240,30));
FrameSelected.SetRoundness(7.5);
FrameSelected.Draw(CouleurConfig);



//selection depuis chaine de caracteres pour export plot


if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+5+200 && mouse_y>yrep+347 && mouse_y<yrep+367)
{
FrameSelected.DrawOutline(CouleurLigne);
}




FrameSelected.SetLineWidth(epaisseur_ligne_fader);
FrameSelected.DrawOutline(CouleurLigne.WithAlpha(alpha_blinker));
petitchiffre.Print(importfile_name,xrep+10,yrep+365);
petitpetitchiffre.Print(string_typeexport_view,xrep+150,yrep+375);

petitpetitchiffre.Print("Name must have extension: ",xrep+250,yrep+170 );
petitchiffre.Print("Ascii: .asc .txt or .alq",xrep+250,yrep+185 );
petitchiffre.Print("PDF: .pdf",xrep+250,yrep+200 );
petitpetitchiffre.Print("Schwarzpeter: no extension",xrep+250,yrep+215 );

//////////////////UP DOWN LINE IMPORT/////////////////////
Circle LineUp(Vec2D(xrep+220,yrep+200),12);
LineUp.Draw(CouleurFond);
Circle LineDown(Vec2D(xrep+220,yrep+310),12);
LineDown.Draw(CouleurFond);
if(window_focus_id==W_SAVE && mouse_x>xrep+208 && mouse_x<xrep+232)
{
if(mouse_y>yrep+188 && mouse_y<yrep+212)
{
LineUp.Draw(CouleurSurvol);
}
else if(window_focus_id==W_SAVE && mouse_y>yrep+298 && mouse_y<yrep+322)
{
LineDown.Draw(CouleurSurvol);
}
}
petitchiffre.Print("-",xrep+216,yrep+205);
petitchiffre.Print("+",xrep+216,yrep+315);
LineUp.DrawOutline(CouleurLigne);
LineDown.DrawOutline(CouleurLigne);


/////////////////////////////SAVE LOAD && CONDITIONS////////////////////////////////
switch (index_export_choice)
{
case 0://ascii
enable_export=1;
enable_import=1;
break;
case 1://schwz
enable_export=0;
enable_import=1;
break;
case 2://alq
enable_export=0;
enable_import=1;
break;
case 3://pdf
enable_export=1;
enable_import=0;
break;
default: break;
}
////////////////////////////////////////////////////////////////////////////////
if(enable_export==1)
{
Rect SaveExport(Vec2D(xrep+40,yrep+390),Vec2D(70,30));
SaveExport.SetRoundness(7.5);
if(window_focus_id==W_SAVE && mouse_x>xrep+40 && mouse_x<xrep+110 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
SaveExport.Draw(CouleurSurvol);
}
petitchiffre.Print("SAVE",xrep+55,yrep+410);
SaveExport.DrawOutline(CouleurLigne);
}
////////////////////////////////////////////////////////////////////////////////
if(enable_import==1)
{
Rect LoadExport(Vec2D(xrep+140,yrep+390),Vec2D(70,30));
LoadExport.SetRoundness(7.5);
if(window_focus_id==W_SAVE && mouse_x>xrep+140 && mouse_x<xrep+210 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
LoadExport.Draw(CouleurSurvol);
}
petitchiffre.Print("LOAD",xrep+155,yrep+410);
LoadExport.DrawOutline(CouleurLigne);
}
//sab 02/03/2014 return(0);
}


//sab 02/03/2014 -> void -> std::string
void do_logical_deroule_repertoire_export_import(int xrep, int yrep, const std::string label)
{
//christoph 19/12/14 substr(0,25)>substr(0,24);
const std::string name_of_rep 		= label.substr (0,24);
//////////////////////LISTE DOSSIERS ETC///////////////////////////////////////

for (int y=0;y<8;y++)
{


if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+155 && mouse_y>(yrep+175+(y*20)) && mouse_y<(yrep+190+(y*20)))
{

if(mouse_button==1 && mouse_released==0)
{
importfile_selected=(y+line_import);
if(y+line_import<127)
{sprintf(importfile_name,list_import_files[importfile_selected]);  }
check_import_type();
mouse_released=1;
}
}

 //fin des 8 lignes
}



//selection depuis chaine de caracteres pour export plot


if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+205 && mouse_y>yrep+347 && mouse_y<yrep+367)
{

if(mouse_button==1 && mouse_released==0 && index_type==1 )
{
for (int tt=0;tt<24;tt++)
{
importfile_name[tt]=numeric[tt];
}
reset_numeric_entry();
index_type=0;
check_import_type();
mouse_released=1;
}
}




//////////////////UP DOWN LINE IMPORT/////////////////////

if(window_focus_id==W_SAVE && mouse_x>xrep+208 && mouse_x<xrep+232)
{
if(mouse_y>yrep+188 && mouse_y<yrep+212)
{

if(mouse_button==1)
{
if(line_import>0){line_import--;}
mouse_released=1;
}
}
else if(window_focus_id==W_SAVE && mouse_y>yrep+298 && mouse_y<yrep+322)
{

if(mouse_button==1)
{
if(line_import<127){line_import++;}
mouse_released=1;
}
}
}


////////////////////////////////////////////////////////////////////////////////
if(enable_export==1)
{
if(window_focus_id==W_SAVE && mouse_x>xrep+40 && mouse_x<xrep+110 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
if(mouse_button==1 && mouse_released==0)
{
index_do_export=1;
index_ask_confirm=1;
mouse_released=1;
}
}
}
////////////////////////////////////////////////////////////////////////////////
if(enable_import==1)
{
if(window_focus_id==W_SAVE && mouse_x>xrep+140 && mouse_x<xrep+210 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
if(mouse_button==1 && mouse_released==0)
{
index_do_import=1;
index_ask_confirm=1;
mouse_released=1;
}
}
}
//sab 02/03/2014 return(0);
}
//sab 02/03/2014 int deroule_repertoire_classical_save(int xrep, int yrep, char name_of_rep[25])
void deroule_repertoire_classical_save(int xrep, int yrep, const std::string label)
{
//christoph 19/12/14 substr(0,25)>substr(0,24);
const std::string name_of_rep = label.substr(0,24);
//////////////////////LISTE DOSSIERS ETC///////////////////////////////////////
petitchiffre.Print("Content of SAVES folder:",xrep+10,yrep+170);
Rect BackDeroule(Vec2D(xrep,yrep+155),Vec2D(245,185));
BackDeroule.SetRoundness(15);
BackDeroule.Draw(CouleurConfig.WithAlpha(0.7));

for (int y=0;y<8;y++)
{
Rect OverFile(Vec2D(xrep+5,(yrep+185+(y*20)-10)),Vec2D(200,20));
OverFile.SetRoundness(7.5);
//affichage quiest selectionné
if(strcmp(savefile_name,list_save_files[savefile_selected])==0 && (savefile_selected==(y+line_save)))
{OverFile.Draw(CouleurFond.WithAlpha(0.5));}

if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+155 && mouse_y>(yrep+175+(y*20)) && mouse_y<(yrep+190+(y*20)))
{
OverFile.DrawOutline(CouleurLigne);
}

petitpetitchiffre.Print(list_save_files[line_save+y],xrep+10,yrep+185+(y*20));
}
//nom du spectacle
Rect FrameSelected(Vec2D(xrep+5,yrep+347),Vec2D(240,30));
FrameSelected.SetRoundness(7.5);
FrameSelected.Draw(CouleurConfig);
if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+245 && mouse_y>yrep+347 && mouse_y<yrep+377)
{
FrameSelected.DrawOutline(CouleurLigne);
}
FrameSelected.SetLineWidth(epaisseur_ligne_fader);
FrameSelected.DrawOutline(CouleurLigne.WithAlpha(alpha_blinker));
petitchiffre.Print(savefile_name,xrep+10,yrep+365);
//////////////////UP DOWN LINE save/////////////////////
Circle LineUp(Vec2D(xrep+220,yrep+200),12);
LineUp.Draw(CouleurFond);
Circle LineDown(Vec2D(xrep+220,yrep+310),12);
LineDown.Draw(CouleurFond);
if(window_focus_id==W_SAVE && mouse_x>xrep+208 && mouse_x<xrep+232)
{
if(mouse_y>yrep+188 && mouse_y<yrep+212)
{
LineUp.Draw(CouleurSurvol);
}
else if(mouse_y>yrep+298 && mouse_y<yrep+322)
{
LineDown.Draw(CouleurSurvol);
}
}
petitchiffre.Print("-",xrep+216,yrep+205);
petitchiffre.Print("+",xrep+216,yrep+315);
LineUp.DrawOutline(CouleurLigne);
LineDown.DrawOutline(CouleurLigne);
///////////////////////////////////////////////////////////////////////////////
Rect SaveB(Vec2D(xrep+40,yrep+390),Vec2D(70,30));
SaveB.SetRoundness(7.5);
if(window_focus_id==W_SAVE && mouse_x>xrep+40 && mouse_x<xrep+110 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
SaveB.Draw(CouleurSurvol);
}
petitchiffre.Print("SAVE",xrep+55,yrep+410);
SaveB.DrawOutline(CouleurLigne);

////////////////////////////////////////////////////////////////////////////////

Rect LoadB(Vec2D(xrep+140,yrep+390),Vec2D(70,30));
LoadB.SetRoundness(7.5);
if(window_focus_id==W_SAVE && mouse_x>xrep+140 && mouse_x<xrep+210 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
LoadB.Draw(CouleurSurvol);
}
petitchiffre.Print("LOAD",xrep+155,yrep+410);
LoadB.DrawOutline(CouleurLigne);

////////////////////////////////////////////////////////////////////////////////

Rect ResetB(Vec2D(xrep+280,yrep+390),Vec2D(70,30));
ResetB.SetRoundness(7.5);

if(window_focus_id==W_SAVE && mouse_x>xrep+280 && mouse_x<xrep+350 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
ResetB.Draw(CouleurSurvol);
}
petitchiffre.Print("RESET",xrep+295,yrep+410);
ResetB.DrawOutline(CouleurLigne);


//sab 02/03/2014 return(0);
}


//sab 02/03/2014 int do_logical_deroule_repertoire_classical_save(int xrep, int yrep, char name_of_rep[25])
void do_logical_deroule_repertoire_classical_save(int xrep, int yrep, const std::string label)
{
//christoph 19/12/14 substr(0,25)>substr(0,24);
const std::string name_of_rep = label.substr(0,24);

for (int y=0;y<8;y++)
{


if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+155 && mouse_y>(yrep+175+(y*20)) && mouse_y<(yrep+190+(y*20)))
{

if(mouse_button==1 && mouse_released==0)
{
savefile_selected=(y+line_save);
sprintf(savefile_name,list_save_files[savefile_selected]);
mouse_released=1;
}
}

}
//nom du spectacle

if(window_focus_id==W_SAVE && mouse_x>xrep+5 && mouse_x<xrep+245 && mouse_y>yrep+347 && mouse_y<yrep+377)
{

if(mouse_button==1 && mouse_released==0 && index_type==1)
{

for (int tt=0;tt<24;tt++)
{
savefile_name[tt]=numeric[tt];
}
reset_numeric_entry();
index_type=0;
mouse_released=1;
}
}

if(window_focus_id==W_SAVE && mouse_x>xrep+208 && mouse_x<xrep+232)
{
if(mouse_y>yrep+188 && mouse_y<yrep+212)
{

if(mouse_button==1)
{

if(line_save>0){line_save--;}
mouse_released=1;
}
}
else if(mouse_y>yrep+298 && mouse_y<yrep+322)
{

if(mouse_button==1)
{

if(line_save<127){line_save++;}
mouse_released=1;
}
}
}
///////////////////////////////////////////////////////////////////////////////
//save button
if(window_focus_id==W_SAVE && mouse_x>xrep+40 && mouse_x<xrep+110 && mouse_y>yrep+390 && mouse_y<yrep+420)
{

if(mouse_button==1 && mouse_released==0)
{

if(strlen(savefile_name)==0){sprintf(savefile_name,"unnamed");}
index_do_saveshow=1;
index_ask_confirm=1;
mouse_released=1;
}
}

////////////////////////////////////////////////////////////////////////////////
//load button
if(window_focus_id==W_SAVE && mouse_x>xrep+140 && mouse_x<xrep+210 && mouse_y>yrep+390 && mouse_y<yrep+420)
{
if(mouse_button==1 && mouse_released==0)
{

if(strcmp(savefile_name,"")!=0)
{
index_do_loadshow=1;
index_ask_confirm=1;
}
mouse_released=1;
}
}

////////////////////////////////////////////////////////////////////////////////
//reset button

if(window_focus_id==W_SAVE && mouse_x>xrep+280 && mouse_x<xrep+350 && mouse_y>yrep+390 && mouse_y<yrep+420)
{

if(mouse_button==1 && mouse_released==0)
{
index_do_resetshow=1;
index_ask_confirm=1;
mouse_released=1;
}
}
//sab 02/03/2014 return(0);
}


int selecteur_PDF_save_solo_global(int xrep, int yrep)
{

char string_title_sav_spec[48];
for(int u=0;u<12;u++)
{
//ligne 1
Rect SavePin(Vec2D(xrep,yrep+(u*15)),Vec2D(10,10));
if(specify_who_to_save_PDF[u]==1){SavePin.Draw(CouleurFader); }

switch (u)
{
case 0:
sprintf(string_title_sav_spec,"MEMORIES");
break;
case 1:
sprintf(string_title_sav_spec,"CHANNEL VIEW");
break;
case 2:
sprintf(string_title_sav_spec,"CHANNELS from Plot and List");
break;
case 3:
sprintf(string_title_sav_spec,"PATCH: per CHANNELS view");
break;
case 4:
sprintf(string_title_sav_spec,"PATCH: per DIMMERS view");
break;
case 5:
sprintf(string_title_sav_spec,"BANGER");
break;
case 6:
sprintf(string_title_sav_spec,"AUDIO LIST OF FILES");
break;
case 7:
sprintf(string_title_sav_spec,"FADERS");
break;
case 8:
sprintf(string_title_sav_spec,"CHASERS");
break;
case 9:
sprintf(string_title_sav_spec,"TRICHROMY");
break;
case 10:
sprintf(string_title_sav_spec,"VIDEOTRACKING");
break;
case 11:
sprintf(string_title_sav_spec,"GRIDPLAYERS");
break;


default:
break;
}
petitpetitchiffre.Print(string_title_sav_spec,xrep+20,yrep+(u*15)+10);

SavePin.DrawOutline(CouleurLigne);
}


for(int u=0;u<12;u++)
{
//ligne 2
Rect SavePin(Vec2D(xrep+190,yrep+(u*15)),Vec2D(10,10));
if(specify_who_to_save_PDF[u+12]==1){SavePin.Draw(CouleurFader); }

switch (u)
{
case 0:
sprintf(string_title_sav_spec,"MOVER");
break;
case 1:
sprintf(string_title_sav_spec,"ECHO");
break;
case 2:
sprintf(string_title_sav_spec,"DRAW");
break;
case 9:
sprintf(string_title_sav_spec,"ARDUINO");
break;
case 10:
sprintf(string_title_sav_spec,"MIDI AFFECTATIONS");
break;
case 11:
sprintf(string_title_sav_spec,"iCAT PRESETS");
break;
default:
sprintf(string_title_sav_spec,"-");
break;
}
petitpetitchiffre.Print(string_title_sav_spec,xrep+210,yrep+(u*15)+10);

SavePin.DrawOutline(CouleurLigne);
}

 return(0);
}



int do_logical_selecteur_PDF_save_solo_global(int xrep, int yrep)
{

for(int u=0;u<12;u++)
{
//ligne 1

if(window_focus_id==W_SAVE && mouse_x>xrep && mouse_x<xrep+10 && mouse_y>yrep+(u*15) && mouse_y<yrep+(u*15)+10)
{
if(mouse_button==1 && mouse_released==0)
{
specify_who_to_save_PDF[u]=toggle(specify_who_to_save_PDF[u]);
mouse_released=1;
}
}

//ligne 2
if(window_focus_id==W_SAVE && mouse_x>xrep+190 && mouse_x<xrep+200 && mouse_y>yrep+(u*15) && mouse_y<yrep+(u*15)+10)
{
if(mouse_button==1 && mouse_released==0)
{
specify_who_to_save_PDF[u+12]=toggle(specify_who_to_save_PDF[u+12]);
mouse_released=1;
}
}

}

 return(0);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int selecteur_binary_save_solo_global(int xrep, int yrep)
{
Rect SwitchGlobal(Vec2D(xrep+170,yrep-35),Vec2D(70,20));
SwitchGlobal.SetRoundness(7.5);


if(window_focus_id==W_SAVE && mouse_x>xrep+170 && mouse_x<xrep+240 && mouse_y>yrep-35 && mouse_y<yrep-15)
{
SwitchGlobal.Draw(CouleurSurvol);
}
switch (index_save_global_is)
{
case 0:
SwitchGlobal.Draw(CouleurBlind.WithAlpha(alpha_blinker));
petitchiffre.Print("CHOICE",xrep+180,yrep-20);
break;
case 1:
SwitchGlobal.Draw(CouleurFader);
petitchiffre.Print("GLOBAL",xrep+180,yrep-20);
break;
default: break;
}
SwitchGlobal.DrawOutline(CouleurLigne);


char string_title_sav_spec[48];
for(int u=0;u<12;u++)
{
//ligne 1
Rect SavePin(Vec2D(xrep,yrep+(u*15)),Vec2D(10,10));
if(specify_who_to_save_load[u]==1){SavePin.Draw(CouleurFader); }

switch (u)
{
case 0:
sprintf(string_title_sav_spec,"MEMORIES");
break;
case 1:
sprintf(string_title_sav_spec,"Mem.Times");
break;
case 2:
sprintf(string_title_sav_spec,"Mem.Links");
break;
case 3:
sprintf(string_title_sav_spec,"Mem.Bangers");
break;
case 4:
sprintf(string_title_sav_spec,"Mem.Man.Ratio");
break;
case 5:
sprintf(string_title_sav_spec,"Ch.List&Views");
break;
case 6:
sprintf(string_title_sav_spec,"Ch.DirectCH");
break;
case 7:
sprintf(string_title_sav_spec,"Ch.Freeze/Excl.");
break;
case 8:
sprintf(string_title_sav_spec,"Patch.Circuits");
break;
case 9:
sprintf(string_title_sav_spec,"Patch.LTP/HTP");
break;
case 10:
sprintf(string_title_sav_spec,"Patch.Curves");
break;
case 11:
sprintf(string_title_sav_spec,"BANGER");
break;
default: break;
}
petitpetitchiffre.Print(string_title_sav_spec,xrep+20,yrep+(u*15)+10);


SavePin.DrawOutline(CouleurLigne);

//ligne 2

Rect SavePinSnd(Vec2D(xrep+110,yrep+(u*15)),Vec2D(10,10));

if(specify_who_to_save_load[u+12]==1){SavePinSnd.Draw(CouleurFader); }

switch (u)
{
case 0:
sprintf(string_title_sav_spec,"FADERS.Content");
break;
case 1:
sprintf(string_title_sav_spec,"Faders.LFO/Times");
break;
case 2:
sprintf(string_title_sav_spec,"Faders.Curves");
break;
case 3:
sprintf(string_title_sav_spec,"MINIF.Prsts/Lcks");
break;
case 4:
sprintf(string_title_sav_spec,"CHASERS");
break;
case 5:
sprintf(string_title_sav_spec,"MIDI.Affectation");
break;
case 6:
sprintf(string_title_sav_spec,"Midi.Cheat");
break;
case 7:
sprintf(string_title_sav_spec,"TRICHROMY");
break;
case 8:
sprintf(string_title_sav_spec,"VIDEO-TRACKING");
break;
case 9:
sprintf(string_title_sav_spec,"ARDUINO");
break;
case 10:
sprintf(string_title_sav_spec,"AUDIO.Conf");
break;
case 11:
sprintf(string_title_sav_spec,"iCAT");
break;
default: break;
}
petitpetitchiffre.Print(string_title_sav_spec,xrep+130,yrep+(u*15)+10);

SavePinSnd.DrawOutline(CouleurLigne);





//ligne 3

Rect SavePinThrd(Vec2D(xrep+240,yrep+(u*15)),Vec2D(10,10));

if(specify_who_to_save_load[u+24]==1){SavePinThrd.Draw(CouleurFader); }

switch (u)
{
case 0:
sprintf(string_title_sav_spec,"Windows");
break;
case 1:
sprintf(string_title_sav_spec,"ColorProfile");
break;
case 2:
sprintf(string_title_sav_spec,"Keyboard.conf");
break;
case 3:
sprintf(string_title_sav_spec,"Indexes");
break;
case 4:
sprintf(string_title_sav_spec,"MOVER");
break;
case 5:
sprintf(string_title_sav_spec,"GRID");
break;
case 6:
sprintf(string_title_sav_spec,"GridPl1.CueList");
break;
case 7:
sprintf(string_title_sav_spec,"Light Plot");
break;
case 8:
sprintf(string_title_sav_spec,"DRAW");
break;
case 9:
sprintf(string_title_sav_spec,"ECHO");
break;
case 10:
sprintf(string_title_sav_spec,"WAVE");
break;
case 11:
sprintf(string_title_sav_spec,"Save Presets");
break;
default: break;
}
petitpetitchiffre.Print(string_title_sav_spec,xrep+260,yrep+(u*15)+10);


SavePinThrd.DrawOutline(CouleurLigne);

}

 return(0);
}

int do_logical_selecteur_binary_save_solo_global(int xrep, int yrep)
{

if(window_focus_id==W_SAVE && mouse_x>xrep+170 && mouse_x<xrep+240 && mouse_y>yrep-35 && mouse_y<yrep-15)
{

if(mouse_button==1 && mouse_released==0)
{

index_save_global_is=toggle(index_save_global_is);
if(index_save_global_is==1)
{
set_all_saves_indexes_at(1);
}
else // si mode choice, on efface tous les indexes
{
set_all_saves_indexes_at(0);
}
mouse_released=1;
}
}


for(int u=0;u<12;u++)
{
//ligne1
if(window_focus_id==W_SAVE && mouse_x>xrep && mouse_x<xrep+50 && mouse_y>yrep+(u*15) && mouse_y<yrep+(u*15)+15)
{
{
if(mouse_button==1 && mouse_released==0)
{
index_save_global_is=0;
specify_who_to_save_load[u]=toggle(specify_who_to_save_load[u]);
mouse_released=1;
}
}
}


//ligne 2

if(window_focus_id==W_SAVE && mouse_x>xrep+110 && mouse_x<xrep+120 && mouse_y>yrep+(u*15) && mouse_y<yrep+(u*15)+10)
{
{
if(mouse_button==1 && mouse_released==0)
{
index_save_global_is=0;
specify_who_to_save_load[u+12]=toggle(specify_who_to_save_load[u+12]);
mouse_released=1;
}
}
}


//ligne 3

if(window_focus_id==W_SAVE && mouse_x>xrep+240 && mouse_x<xrep+250 && mouse_y>yrep+(u*15) && mouse_y<yrep+(u*15)+10)
{
{
if(mouse_button==1 && mouse_released==0)
{
index_save_global_is=0;
specify_who_to_save_load[u+24]=toggle(specify_who_to_save_load[u+24]);
mouse_released=1;
}
}
}

}

 return(0);
}

int Save_Menu(int xsave, int ysave)
{
Rect backSave(Vec2D(xsave,ysave),Vec2D(420,520));
backSave.SetRoundness(15);
backSave.SetLineWidth(triple_epaisseur_ligne_fader);
backSave.Draw(CouleurFond);
backSave.DrawOutline(CouleurLigne);

if(window_focus_id==W_SAVE){backSave.DrawOutline(CouleurFader);}

neuro.Print("SAVE",xsave+110, ysave+30);


Rect TogBSav(Vec2D(xsave+310,ysave+15),Vec2D(100,20));
TogBSav.SetRoundness(5);
TogBSav.SetLineWidth(epaisseur_ligne_fader);



switch(index_save_mode_export_or_binary)
{
case 0:
petitchiffre.Print("  BINARY",xsave+325,ysave+30);
selecteur_binary_save_solo_global(xsave+30, ysave+50);
deroule_repertoire_classical_save(xsave+20, ysave+85, "saves");
choose_personnal_preset_binary_save_load(xsave+300, ysave+270);
break;
case 1:
TogBSav.Draw(CouleurSurvol);
petitchiffre.Print("IMP-EXPORT",xsave+325,ysave+30);
if(isPdf==1) {selecteur_PDF_save_solo_global(xsave+30, ysave+50);   }
deroule_repertoire_export_import(xsave+20, ysave+85, "import_export");
break;
default: break;
}
TogBSav.DrawOutline(CouleurLigne);

Rect ShowReport(Vec2D(xsave+300,ysave+430),Vec2D(70,25));
ShowReport.SetRoundness(5);
ShowReport.Draw(CouleurSurvol.WithAlpha(index_show_save_load_report));
ShowReport.DrawOutline(CouleurLigne);
petitchiffre.Print("Show",xsave+305,ysave+440);
petitchiffre.Print("Log",xsave+315,ysave+450);


return(0);
}


int do_logical_Save_Menu(int xsave, int ysave)
{

if(window_focus_id==W_SAVE && mouse_x>xsave+310 && mouse_x<xsave+410 && mouse_y>ysave+15 && mouse_y<ysave+35)
{
if(mouse_button==1 && mouse_released==0)
{
index_save_mode_export_or_binary=toggle(index_save_mode_export_or_binary);
mouse_released=1;
}
}



switch(index_save_mode_export_or_binary)
{
case 0:
do_logical_selecteur_binary_save_solo_global(xsave+30, ysave+50);
do_logical_deroule_repertoire_classical_save(xsave+20, ysave+85, "saves");
do_logical_choose_personnal_preset_binary_save_load(xsave+300, ysave+270);
break;
case 1:
if(isPdf==1) {do_logical_selecteur_PDF_save_solo_global(xsave+30, ysave+50);   }
do_logical_deroule_repertoire_export_import(xsave+20, ysave+85, "import_export");
break;
default: break;
}
if(window_focus_id==W_SAVE && mouse_x>xsave+300 && mouse_x<xsave+370 && mouse_y>ysave+430 && mouse_y<ysave+455)
{
if(mouse_button==1 && mouse_released==0)
{
index_show_save_load_report=toggle(index_show_save_load_report);
mouse_released=1;
there_is_change_on_show_save_state=1;
}

}

return(0);
}

