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

* \file patch_visu.cpp
* \brief {DMX patch GUI}
* \author Christoph Guillermet
* \version {0.8.6.3}
* \date {12/02/2015}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonction GUI pour la fenêtre patch dmx
*
*   GUI fonction for the dmx patch window
*
**/

int menu_curve(int XCurv, int YCurv)
{
Rect CurveSpace( Vec2D((XCurv),(YCurv)),Vec2D(315,600));
CurveSpace.SetRoundness(15);
CurveSpace.SetLineWidth(triple_epaisseur_ligne_fader);
CurveSpace.Draw(CouleurFond);
if(window_focus_id==W_PATCH)
{
CurveSpace.DrawOutline(CouleurFader);
}
else
{
CurveSpace.DrawOutline(CouleurLigne);
}

neuro.Print("CURVES",XCurv+210,YCurv+30);

Rect CurveEditEnable( Vec2D((XCurv+30),(YCurv+10)),Vec2D(50,20));
CurveEditEnable.SetRoundness(7.5);


if(index_enable_curve_editing==1)
{
CurveEditEnable.Draw(CouleurFader);
}
CurveEditEnable.DrawOutline(CouleurLigne);
petitchiffre.Print("edit",XCurv+40 ,YCurv+22);

//Grille
Rect CurveEditSpace( Vec2D((XCurv+30),(YCurv+50)),Vec2D(255,255));
CurveEditSpace.SetRoundness(7.5);
CurveEditSpace.Draw(CouleurFond);
CurveEditSpace.DrawOutline(CouleurFond);

for (int l=1;l<=25;l++)
{
Line( Vec2D( XCurv+30+(l*10), YCurv+50 ), Vec2D( XCurv+30+(l*10),YCurv+305)).Draw(CouleurLigne.WithAlpha(0.2));
Line( Vec2D( XCurv+30, YCurv+50+(l*10) ), Vec2D( XCurv+285,YCurv+50+(l*10))).Draw(CouleurLigne.WithAlpha(0.2));
}



Rect CurveSplineRatio( Vec2D((XCurv+30),(YCurv+330)),Vec2D(255,25));
CurveSplineRatio.SetRoundness(7.5);
CurveSplineRatio.SetLineWidth(epaisseur_ligne_fader);
Rect CurveSplineLevel( Vec2D((XCurv+30),(YCurv+330)),Vec2D(index_curve_spline_level,25));
CurveSplineLevel.SetRoundness(7.5);
CurveSplineLevel.SetLineWidth(epaisseur_ligne_fader);

CurveSplineLevel.Draw(CouleurSurvol);
CurveSplineRatio.DrawOutline(CouleurLigne);

petitchiffre.Print(ol::ToString(index_curve_spline_level),XCurv+157,YCurv+340);
petitchiffre.Print(ol::ToString(curve_spline_level),XCurv+157,YCurv+350);



//le calcul du SPLINE A GARDER DANS LA FENETRE SINON PLANTAGE///////////////////

curve_spline_level=(((float)index_curve_spline_level)/127)-1;
if( window_focus_id==W_PATCH && index_enable_curve_editing==1 && mouse_x>=XCurv+30 && mouse_x<=XCurv+285 && mouse_y>YCurv+330 && mouse_y<YCurv+355 && mouse_button==1)
{
index_curve_spline_level=mouse_x-(XCurv+30);
the_curve_spline_level[curve_selected]=index_curve_spline_level;
write_curve();
}

///////////////////////////////////////////////////////////////////////////////
Rect Curve(Vec2D(XCurv,YCurv),Vec2D(60,20));
Curve.SetRoundness(7.5);
Curve.SetLineWidth(epaisseur_ligne_fader);

for(int l=0;l<4;l++)
{
for (int curvenumber=0;curvenumber<4;curvenumber++)
{
Curve.MoveTo(Vec2D((XCurv+20+(curvenumber*70)),(YCurv+370+(30*l))));
if(curve_selected==curvenumber+(l*4)){ Curve.Draw(CouleurBlind);}
petitchiffre.Print(ol::ToString(1+curvenumber+(l*4)),XCurv+50+(curvenumber*70),YCurv+385+(30*l));
Curve.DrawOutline(CouleurLigne);
}
}

/////////////////////// AFFICHAGE et MANIPS SPLINES//////////////////////////////////////////

SplineCurve();
if(window_focus_id==W_PATCH && mouse_x>=(XCurv+30)&& mouse_x<=(XCurv+285) && mouse_y>=(YCurv+50) && mouse_y<=(YCurv+305))
{
 if(dmx_view==1)
 {
 petitchiffrerouge.Print(ol::ToString((YCurv+305)-mouse_y),mouse_x-25,mouse_y-15);
 petitchiffre.Print(ol::ToString(mouse_x-(XCurv+30)),mouse_x+10,mouse_y-15);
 }
 else if( dmx_view==0)
 {
 petitchiffrerouge.Print(ol::ToString((int)(((YCurv+305)-mouse_y)/2.55)),mouse_x-25,mouse_y-15);
 petitchiffre.Print(ol::ToString((int)((mouse_x-(XCurv+30))/2.55)),mouse_x+10,mouse_y-15);
 }
}
//PRESET DE CURVE///////////////////////////////////////////////////////////////////
petitchiffre.Print("Presets to curve :",XCurv+20,YCurv+500);
Rect ActToCurve(Vec2D(XCurv,YCurv),Vec2D(60,20));
ActToCurve.SetRoundness(7.5);
ActToCurve.SetLineWidth(epaisseur_ligne_fader);
for (int act=0;act<4;act++)
{
ActToCurve.MoveTo( Vec2D( (XCurv+20+(act*70)) , (YCurv+510) ) );

/////////////////////////////
////////////INFOS DES ACTIONS
switch(act)
{
case 0:
if (index_reset_curve==1){ActToCurve.Draw(CouleurBlind);}
petitchiffre.Print("linear",XCurv+30+(act*70),YCurv+525);
break;
case 1:
if (index_square_curve==1){ActToCurve.Draw(CouleurBlind);}
petitchiffre.Print("square",XCurv+20+(act*70)+5,YCurv+525);
break;
case 2:
if (index_preheat_curve==1){ActToCurve.Draw(CouleurBlind);}
petitchiffre.Print("preheat",XCurv+20+(act*70)+1,YCurv+525);
break;
case 3:
if (index_fluo_curve==1){ActToCurve.Draw(CouleurBlind);}
petitchiffre.Print("fluo.",XCurv+20+(act*70)+15,YCurv+525);
break;
default: break;
}
ActToCurve.DrawOutline(CouleurLigne);
}
/////////////////////AFFECTATION AUX DIMERS SELECTIONNES///////////////////////////
Rect AffectCurveTo( Vec2D(XCurv+65,(YCurv+560)),Vec2D(200,30));
AffectCurveTo.SetRoundness(15);
AffectCurveTo.SetLineWidth(epaisseur_ligne_fader);

AffectCurveTo.DrawOutline(CouleurLigne);
petitchiffre.Print("AFFECT CURVE TO",XCurv+90, YCurv+572);
petitchiffre.Print("SELECTED DIMMERS",XCurv+90, YCurv+585);
return(0);
}



int PatchBox(int XChan, int YChan, float scroll_chan)
{
Rect PatchSpace( Vec2D((XChan),(YChan)),Vec2D(450,600));
PatchSpace.SetRoundness(15);
PatchSpace.SetLineWidth(triple_epaisseur_ligne_fader);
PatchSpace.Draw(CouleurFond);
if(window_focus_id==W_PATCH)
{
PatchSpace.DrawOutline(CouleurFader);
}
else
{
PatchSpace.DrawOutline(CouleurLigne);
}


//scroll
 Rect ScrollMyPatch(Vec2D(XChan+340,YChan+50+scroller_patch),Vec2D(90,20));
 ScrollMyPatch.SetRoundness(7.5);
 ScrollMyPatch.SetLineWidth(epaisseur_ligne_fader);
 ScrollMyPatch.DrawOutline(CouleurLigne);

Line( Vec2D( XChan+420, YChan+50 ), Vec2D( XChan+420,YChan+260)).Draw( CouleurLigne );

neuro.Print("DIMMERS",XChan+330,YChan+30);

Line( Vec2D( XChan+410, YChan+51+12 ), Vec2D( XChan+420,YChan+51+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+73+12 ), Vec2D( XChan+420,YChan+73+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+92+12 ), Vec2D( XChan+420,YChan+92+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+111+12 ), Vec2D( XChan+420,YChan+111+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+128+12 ), Vec2D( XChan+420,YChan+128+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+149+12 ), Vec2D( XChan+420,YChan+149+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+169+12 ), Vec2D( XChan+420,YChan+169+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+190+12 ), Vec2D( XChan+420,YChan+190+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+209+12 ), Vec2D( XChan+420,YChan+209+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+228+12 ), Vec2D( XChan+420,YChan+228+12)).Draw( CouleurLigne );
Line( Vec2D( XChan+410, YChan+247+12 ), Vec2D( XChan+420,YChan+247+12)).Draw( CouleurLigne );


petitpetitchiffre.Print("1-54",XChan+350,YChan+51+12);
petitpetitchiffre.Print("55-102",XChan+350,YChan+73+12);
petitpetitchiffre.Print("103-150",XChan+350,YChan+92+12);
petitpetitchiffre.Print("151-192",XChan+350,YChan+111+12);
petitpetitchiffre.Print("193-246",XChan+350,YChan+128+12);
petitpetitchiffre.Print("247-294",XChan+350,YChan+149+12);
petitpetitchiffre.Print("295-348",XChan+350,YChan+169+12);
petitpetitchiffre.Print("349-396",XChan+350,YChan+190+12);
petitpetitchiffre.Print("397-444",XChan+350,YChan+209+12);
petitpetitchiffre.Print("445-492",XChan+350,YChan+228+12);
petitpetitchiffre.Print("493-512",XChan+350,YChan+247+12);


 Rect SelectPatchAction(Vec2D(XChan+345,  YChan+320),Vec2D(90,20));
 SelectPatchAction.SetRoundness(7.5);
 SelectPatchAction.SetLineWidth(epaisseur_ligne_fader);
 if(index_affect_patch==1){SelectPatchAction.Draw(CouleurFader); }

 Rect SelectPatchActionCurv(Vec2D(XChan+345, YChan+440),Vec2D(90,20));
 SelectPatchActionCurv.SetRoundness(7.5);
 SelectPatchActionCurv.SetLineWidth(epaisseur_ligne_fader);
 if(index_menu_curve==1)  {SelectPatchActionCurv.Draw(CouleurFader);}

 Rect SelectPatchOverride(Vec2D(XChan+345, YChan+470),Vec2D(110,20));
 SelectPatchOverride.SetRoundness(7.5);
 SelectPatchOverride.SetLineWidth(epaisseur_ligne_fader);
 if(index_patch_overide==1)  {SelectPatchOverride.Draw(CouleurBlind.WithAlpha(alpha_blinker));}

SelectPatchOverride.MoveTo(Vec2D(XChan+345, YChan+500));
if(index_build_patch_from_plot==1){SelectPatchOverride.Draw(CouleurBlind);}

SelectPatchOverride.MoveTo(Vec2D(XChan+345, YChan+530));
if(index_show_first_dim==1){SelectPatchOverride.Draw(CouleurNiveau);}

petitchiffre.Print("Unselect",XChan+350,YChan+302);
petitchiffre.Print("Affect",XChan+350,YChan+332);
petitchiffre.Print("All",XChan+350,YChan+362);
petitchiffre.Print("Clear",XChan+350,YChan+392);
petitchiffre.Print("Default",XChan+350,YChan+422);
petitchiffre.Print("Curve",XChan+350,YChan+452);
petitchiffre.Print("Check Dimmers",XChan+350,YChan+482);
petitchiffre.Print("Link LightPlot",XChan+350,YChan+512);
petitchiffre.Print("Show 1st Dimmer",XChan+350,YChan+542);



Canvas::SetClipping(XChan+30,YChan+50,XChan+30+280,YChan+495);

Rect lignefond( Vec2D(XChan,YChan),Vec2D(280,25) );
lignefond.SetRoundness(5);
Rect DimIsSelected( Vec2D(XChan,YChan),Vec2D(40,55) );
DimIsSelected.SetRoundness(10);
DimIsSelected.SetLineWidth(epaisseur_ligne_fader);



int maxchan_per_ligne=7;
int grad=0;
for (int l=0;l<86;l++)
{
if(l==85){maxchan_per_ligne=3;} //derniere ligne à 512

lignefond.MoveTo( Vec2D(XChan+30,YChan+85+(l*60) - (int)(scroller_patch* scroll_chan)) );
lignefond.SetRoundness(5);
if(((YChan+100+(l*60) - (int)(scroller_patch* scroll_chan))>YChan+30)&&((YChan+90+(l*60) - (int)(scroller_patch* scroll_chan))<YChan+570))
{
lignefond.Draw(CouleurSurvol);
}

for (int c=1; c<maxchan_per_ligne;c++)
{

//on affiche et actionne que si les données sont dans la fenetre
if(((YChan+100+(l*60) - (int)(scroller_patch* scroll_chan))>YChan+30)&&((YChan+90+(l*60) - (int)(scroller_patch* scroll_chan))<YChan+570))
{
grad=c+(l*6);
//rect de selection
if(Dimmers_selected[grad]==1)
{
DimIsSelected.MoveTo( Vec2D(XChan-5+(45*c),YChan+85+(l*60) - (int)(scroller_patch* scroll_chan)));
DimIsSelected.Draw(CouleurFader);
DimIsSelected.DrawOutline(CouleurLigne);
}

petitchiffre.Print(ol::ToString(grad) ,(XChan + (45*c)),(YChan+100+(l*60) - (int)(scroller_patch* scroll_chan)),CENTER);
//num circuit
petitchiffre.Print(ol::ToString(Patch[(grad)]),(XChan + (45*c)),(YChan+120+(l*60) - (int)(scroller_patch* scroll_chan)),CENTER);
//num curve
petitpetitchiffre.Print(ol::ToString(curves[grad]+1),(XChan + (45*c))+5,(YChan+135+(l*60) - (int)(scroller_patch* scroll_chan)),CENTER);
}
}
}
Canvas::DisableClipping();

//////////////////FENETRE CURVES////////////////////////////////////////////////

if(index_menu_curve==1 )
{menu_curve(XChan+455,YChan);}

/////////////////////////////////////////////////////////////////////////////////
//bandeau masque ligne haut
Rect PatchSpacebandeau( Vec2D((XChan),(YChan)),Vec2D(320,55));
PatchSpacebandeau.SetRoundness(15);
PatchSpacebandeau.Draw(CouleurFond);


return(0);
}
