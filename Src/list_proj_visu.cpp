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

* \file list_proj_visu.cpp
* \brief {spot list and channels macro GUI}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions GUI pour gérer la fenêtre du menu list des projos et channels macro
*
*   GUI fonctions for window of the spot list menu and macro channels
*
 **/

int Channel_macros_visu(int xlist, int ylist)
{

Line(Vec2D(xlist,ylist),Vec2D(xlist+300,ylist)).Draw(CouleurLigne.WithAlpha(0.5));
char titlemacro[36];
sprintf(titlemacro,"Channel Macro / CHANNEL %d",last_ch_selected );
petitchiffre.Print(titlemacro,xlist,ylist+15);
if(last_ch_selected!=0)
{
for(int i=0;i<nbre_macros_per_channel;i++)
{
//comportement
Rect condition_B(Vec2D(xlist, ylist+25+(25*i)),Vec2D(80,20));
condition_B.SetRoundness(4);
condition_B.Draw(CouleurBleuProcedure.WithAlpha(0.5));
if(mouse_x>xlist && mouse_x<xlist+80 && mouse_y>ylist+25+(25*i) && mouse_y<ylist+45+(25*i) && window_focus_id==914)
{
condition_B.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
switch(channel_macro_reaction[last_ch_selected][i])
{
case 0:
sprintf(titlemacro,"-");
break;
case 1:
sprintf(titlemacro,"        >=");
break;
case 2:
sprintf(titlemacro,"        > ");
break;
case 3:
sprintf(titlemacro,"        ==");
break;
case 4:
sprintf(titlemacro,"        !=");
break;
case 5:
sprintf(titlemacro,"        <=");
break;
case 6:
sprintf(titlemacro,"        <");
break;
case 7:
sprintf(titlemacro,"    Follow");
break;
case 8:
sprintf(titlemacro,"Follow Inv.");
break;
default:
break;
}
petitchiffre.Print(titlemacro,xlist+5, ylist+38+(25*i));

//valeur 1
Rect lev_B(Vec2D(xlist+90, ylist+25+(25*i)),Vec2D(40,20));
lev_B.SetRoundness(4);
lev_B.Draw(CouleurBleuProcedure.WithAlpha(0.5));

switch (dmx_view)
{
case 0:
if(channel_macro_reaction[last_ch_selected][i]<7)
{sprintf(titlemacro,"%d", (int) (((float)(channel_macro_val[last_ch_selected][i][0]) /2.55)));}
else
{
sprintf(titlemacro,"%d",channel_macro_val[last_ch_selected][i][0]);
}
break;
case 1:
sprintf(titlemacro,"%d",channel_macro_val[last_ch_selected][i][0]);
break;
default: break;
}
petitchiffre.Print(titlemacro,xlist+95, ylist+38+(25*i));
if(mouse_x>xlist+90 && mouse_x<xlist+130 && mouse_y>ylist+25+(25*i) && mouse_y<ylist+45+(25*i) && window_focus_id==914)
{
lev_B.DrawOutline(CouleurLigne.WithAlpha(0.5));
}

//action
Rect action_B(Vec2D(xlist+140, ylist+25+(25*i)),Vec2D(80,20));
action_B.SetRoundness(4);
action_B.Draw(CouleurBleuProcedure.WithAlpha(0.5));
if(mouse_x>xlist+140 && mouse_x<xlist+220 && mouse_y>ylist+25+(25*i) && mouse_y<ylist+45+(25*i)&& window_focus_id==914)
{
action_B.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
switch(channel_macro_action[last_ch_selected][i])
{
case 0:
sprintf(titlemacro,"-");
break;
case 1:
sprintf(titlemacro,"Bang Banger");
break;
case 2:
sprintf(titlemacro,"Load Audio");
break;
case 3:
sprintf(titlemacro,"Play A.Pl");
break;
case 4:
sprintf(titlemacro,"Stop A.Pl");
break;
case 5:
sprintf(titlemacro,"Seek A.Pl");
break;
case 6:
sprintf(titlemacro,"Loop ON A.Pl");
break;
case 7:
sprintf(titlemacro,"Loop OFF A.Pl");
break;
case 8:
sprintf(titlemacro,"Volume A.Pl");
break;
case 9:
sprintf(titlemacro,"Pan A.Pl");
break;
case 10:
sprintf(titlemacro,"Pitch A.Pl");
break;
case 11:
sprintf(titlemacro, "MidiCh15 CC");
break;
case 12:
sprintf(titlemacro, "MidiCh15 KOn");
break;
case 13:
sprintf(titlemacro, "MidiCh15 KOff");
break;
case 14:
sprintf(titlemacro, "Fader Level");
break;
case 15:
sprintf(titlemacro, "FaderLFOSpeed");
break;
case 16:
sprintf(titlemacro, "Ch>Fader Num");
break;
case 17:
//sab 02/03/2014  sprintf(titlemacro, "Ch>Stage %");
strcpy(titlemacro, "Ch>Stage %");
break;
default:
break;
}
petitchiffre.Print(titlemacro,xlist+145, ylist+35+(25*i));

//valeur 2
Rect Vaction_B(Vec2D(xlist+230, ylist+25+(25*i)),Vec2D(40,20));
Vaction_B.SetRoundness(4);
Vaction_B.Draw(CouleurBleuProcedure.WithAlpha(0.5));
sprintf(titlemacro,"%d",channel_macro_val[last_ch_selected][i][1]);
petitchiffre.Print(titlemacro,xlist+235, ylist+38+(25*i));
if(mouse_x>xlist+230 && mouse_x<xlist+270 && mouse_y>ylist+25+(25*i) && mouse_y<ylist+45+(25*i) && window_focus_id==914)
{
Vaction_B.DrawOutline(CouleurLigne.WithAlpha(0.5));
}

//on off de la macro
Rect onoff_B(Vec2D(xlist+280, ylist+25+(25*i)),Vec2D(35,20));
onoff_B.SetRoundness(4);
onoff_B.Draw(CouleurBleuProcedure.WithAlpha(0.5));

switch( macro_channel_on[last_ch_selected][i])
{
case 0:
sprintf(titlemacro,"/Off");
break;
case 1:
onoff_B.Draw(CouleurBlind);
sprintf(titlemacro,"/On");
break;
default: break;
}
petitchiffre.Print(titlemacro,xlist+285, ylist+38+(25*i));
if(mouse_x>xlist+280 && mouse_x<xlist+315 && mouse_y>ylist+25+(25*i) && mouse_y<ylist+45+(25*i) && window_focus_id==914)
{
onoff_B.DrawOutline(CouleurLigne.WithAlpha(0.5));
}
}


}//fin si circuit != de 0
 return(0);
}


int liste_projecteurs(int xlist,int ylist)
{
Rect Box_list(Vec2D(xlist, ylist), Vec2D( 350,600));
Box_list.SetRoundness(15);
Box_list.SetLineWidth(triple_epaisseur_ligne_fader);
Box_list.Draw(CouleurFond);
if(window_focus_id==914)
{
Box_list.DrawOutline(CouleurFader);
}
else
{
Box_list.DrawOutline(CouleurLigne);
}

neuro.Print( "Spotlights list",(xlist+120), (ylist+30));

//Edit box
Rect EditList(Vec2D(xlist+290,ylist+16),Vec2D(50,20));
EditList.SetRoundness(7.5);
EditList.SetLineWidth(epaisseur_ligne_fader);

if(index_edit_listproj==1){EditList.Draw(CouleurFader);}

//+ minus debug
//Plus Minus buttons
Rect MinusPosList(Vec2D(xlist+290,ylist+51),Vec2D(50,20));
MinusPosList.SetRoundness(7.5);
MinusPosList.SetLineWidth(epaisseur_ligne_fader);
Rect PlusPosList(Vec2D(xlist+290,ylist+81),Vec2D(50,20));
PlusPosList.SetRoundness(7.5);
PlusPosList.SetLineWidth(epaisseur_ligne_fader);

for(int co=1;co<List_view_nbre_channels;co++)
{
if(co+line_list_is<513)
{
Rect NameList(Vec2D((xlist+60)-5,(ylist+35+(25*co))),Vec2D(185,23));
NameList.SetRoundness(7.5);
float leveldraw=0.0;
if(bufferSequenciel[co+line_list_is]>bufferFaders[co+line_list_is])
{
leveldraw=((float)(bufferSequenciel[co+line_list_is]))/255;
NameList.Draw(CouleurNiveau.WithAlpha(leveldraw));
}
else if(bufferSequenciel[co+line_list_is]<=bufferFaders[co+line_list_is])
{
leveldraw=((float)(bufferFaders[co+line_list_is]))/255;
NameList.Draw(CouleurFader.WithAlpha(leveldraw));
}
if(Selected_Channel[co+line_list_is]==1)
{
NameList.DrawOutline(CouleurLigne);
}
sprintf(listnum,"Ch. %d :",co+line_list_is);
petitchiffre.Print( listnum,(xlist+10), (ylist+50+(25*co)));

if(dmx_view==1)
{
int leveltoshowis;
if(bufferSequenciel[co+line_list_is]>=bufferFaders[co+line_list_is])
{
  leveltoshowis= bufferSequenciel[co+line_list_is];
}
if(bufferFaders[co+line_list_is]>bufferSequenciel[co+line_list_is])
{
  leveltoshowis= bufferFaders[co+line_list_is];
}
if(leveltoshowis>0)
{
petitpetitchiffre.Print( ol::ToString(leveltoshowis), (xlist+245),(ylist+50+(25*co)));
}
}
else if(dmx_view==0)
{
int leveltoshowis;
if(bufferSequenciel[co+line_list_is]>=bufferFaders[co+line_list_is])
{
    leveltoshowis=(int)(((float)(bufferSequenciel[co+line_list_is])/2.55));
}
if(bufferFaders[co+line_list_is]>bufferSequenciel[co+line_list_is])
{
    leveltoshowis=(int)(((float)(bufferFaders[co+line_list_is])/2.55));
}
if(leveltoshowis>0)
{
petitpetitchiffre.Print( ol::ToString(leveltoshowis), (xlist+245),(ylist+50+(25*co)));
}
}
petitchiffre.Print( descriptif_projecteurs[co+line_list_is],(xlist+60), (ylist+50+(25*co)));
}
}


Rect Curseur_ScrollList(Vec2D(xlist+270,ylist+139+(line_list_is/2)),Vec2D(70,20));
Curseur_ScrollList.SetRoundness(5);
Curseur_ScrollList.DrawOutline(CouleurFader);

EditList.DrawOutline(CouleurLigne);
MinusPosList.DrawOutline(CouleurLigne);
PlusPosList.DrawOutline(CouleurLigne);
petitchiffre.Print("edit",xlist+300, ylist+30);
petitchiffre.Print("line -",xlist+300, ylist+65);
petitchiffre.Print("line +",xlist+300, ylist+95);



//ascenceur
Line(Vec2D(xlist+280,ylist+145),Vec2D(xlist+280,ylist+394)).Draw(CouleurLigne);

Line(Vec2D(xlist+280,ylist+145),Vec2D(xlist+285,ylist+145)).Draw(CouleurLigne);
petitpetitchiffre.Print( "  1 -48" ,xlist+285,ylist+147);
Line(Vec2D(xlist+280,ylist+174),Vec2D(xlist+285,ylist+174)).Draw(CouleurLigne);
petitpetitchiffre.Print( " 49 -96",xlist+285,ylist+176);
Line(Vec2D(xlist+280,ylist+198),Vec2D(xlist+285,ylist+198)).Draw(CouleurLigne);
petitpetitchiffre.Print( " 97-144" ,xlist+285,ylist+200);
Line(Vec2D(xlist+280,ylist+222),Vec2D(xlist+285,ylist+222)).Draw(CouleurLigne);
petitpetitchiffre.Print( "145-192" ,xlist+285,ylist+224);
Line(Vec2D(xlist+280,ylist+246),Vec2D(xlist+285,ylist+246)).Draw(CouleurLigne);
petitpetitchiffre.Print( "193-240" ,xlist+285,ylist+248);
Line(Vec2D(xlist+280,ylist+270),Vec2D(xlist+285,ylist+270)).Draw(CouleurLigne);
petitpetitchiffre.Print( "241-288" ,xlist+285,ylist+272);
Line(Vec2D(xlist+280,ylist+293),Vec2D(xlist+285,ylist+293)).Draw(CouleurLigne);
petitpetitchiffre.Print( "289-336" ,xlist+285,ylist+295);
Line(Vec2D(xlist+280,ylist+316),Vec2D(xlist+285,ylist+316)).Draw(CouleurLigne);
petitpetitchiffre.Print( "337-384" ,xlist+285,ylist+319);
Line(Vec2D(xlist+280,ylist+339),Vec2D(xlist+285,ylist+339)).Draw(CouleurLigne);
petitpetitchiffre.Print( "385-432" ,xlist+285,ylist+341);
Line(Vec2D(xlist+280,ylist+370),Vec2D(xlist+285,ylist+370)).Draw(CouleurLigne);
petitpetitchiffre.Print( "433-480" ,xlist+285,ylist+372);
Line(Vec2D(xlist+280,ylist+394),Vec2D(xlist+285,ylist+394)).Draw(CouleurLigne);
petitpetitchiffre.Print( "  ->512" ,xlist+285,ylist+396);


Channel_macros_visu(xlist+10,ylist+470);

 return(0);
}
