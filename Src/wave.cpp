

int fenetre_wave_menus(int x_menus,int y_menus)
{

Rect waveWBack(Vec2D(x_menus,y_menus),Vec2D(size_x_wave_menus,size_y_wave_menus));
waveWBack.SetRoundness(15);
waveWBack.SetLineWidth(triple_epaisseur_ligne_fader);
waveWBack.Draw(CouleurFond);

neuro.Print("WAVE",x_menus+100, y_menus+32);

if(window_focus_id==W_WAVE)
{
waveWBack.DrawOutline(CouleurFader);
}
else
{
waveWBack.DrawOutline(CouleurLigne);
}


//Clear buffer données où états stockés et set état to 0
Rect ClearBuffer(Vec2D(x_menus+200,y_menus+15),Vec2D(60,20));
ClearBuffer.SetRoundness(4.5);


if(window_focus_id==W_WAVE && index_main_clear==1
   && mouse_x>x_menus+200 && mouse_x<x_menus+260 && mouse_y>y_menus+15 && mouse_y<y_menus+35)
{
   ClearBuffer.Draw(CouleurFader);
   if(mouse_button==1 && mouse_released==0)
      {
      clear_wave_buffer();
      clear_wave_slots();
      index_main_clear=0;
      mouse_released=1;
      }
}

ClearBuffer.Draw(CouleurBleu2);
ClearBuffer.DrawOutline(CouleurLigne.WithAlpha(0.3));
petitchiffre.Print("Buffer",x_menus+210,y_menus+28);


//affect to dock
Rect AffToDk(Vec2D(x_menus+275,y_menus+10),Vec2D(60,30));
AffToDk.SetRoundness(4.5);
if(index_affect_wave_to_dock==1)
{
AffToDk.Draw(CouleurBlind.WithAlpha(alpha_blinker));
}
AffToDk.DrawOutline(CouleurLigne.WithAlpha(0.3));
petitchiffre.Print("Affect",x_menus+285,y_menus+23);
petitchiffre.Print("To Dock",x_menus+282,y_menus+33);

if(window_focus_id==W_WAVE && mouse_button==1 && mouse_released==0
   && mouse_x>x_menus+275 && mouse_x<x_menus+335 && mouse_y>y_menus+10 && mouse_y<y_menus+40)
{
if(index_affect_wave_to_dock==0){index_affect_wave_to_dock=1;}
else{index_affect_wave_to_dock=0;}
index_do_dock=index_affect_wave_to_dock;
mouse_released=1;
}



//Slots
petitchiffre.Print("WAVE",x_menus+15,y_menus+60);
Rect SlotFrame(Vec2D(0,0),Vec2D(6,25));
for(int i=0; i<26; i++)
{
 SlotFrame.MoveTo(Vec2D(x_menus+15+(i*10),y_menus+80));
 SlotFrame.Draw(CouleurBleu2);
 int val_=25* Wave_Dampered[i].getvalue_dampered();
 Rect SlotValue(Vec2D(x_menus+15+(i*10),y_menus+105-val_) ,Vec2D(6, (val_)));
 SlotValue.Draw(CouleurBleu6);
 SlotFrame.DrawOutline(CouleurLigne.WithAlpha(0.3));
 if(window_focus_id==W_WAVE)
 {
    if(mouse_x>=x_menus+15+(i*10) && mouse_x<=x_menus+15+(i*10)+6 && mouse_y>=y_menus+80 && mouse_y<=y_menus+80+25)
    {
    petitchiffre.Print(ol::ToString(channel_slots[wave_channel_preset_selected][i]),x_menus+15+(i*10),y_menus+70);
    Line(Vec2D(x_menus+15+(i*10),y_menus+70),Vec2D(x_menus+15+(i*10),y_menus+79)).Draw(CouleurLigne.WithAlpha(0.7));
    if(mouse_button==1 && mouse_released==0)
        {
        if(numeric_postext>0 && index_do_dock==1)//attribuer le cicuit clavier
            {
            int ch__=atoi(numeric);
            if(ch__>0 && ch__<512)
            {
                channel_slots[wave_channel_preset_selected][i]=ch__;
            }
            reset_numeric_entry();
            mouse_released=1;
            }
        else //souris dessine
            {
                Wave_Dampered[i].set_target_val(255*(1.0-(((float)(mouse_y-(y_menus+80)))/25)));
            }
            if(index_main_clear==1)
            {
               channel_slots[wave_channel_preset_selected][i]=0;
            }
        }
    }

 }
}

//PLAY

play_button_view(x_menus+290,y_menus+80,wave_play_state);
seek_button_view(x_menus+320,y_menus+80,0);

if(window_focus_id==W_WAVE)//WAVE BUTTONS PLAY
{
    if(mouse_button==1 && mouse_released==0)
    {
        if(mouse_x>x_menus+290 && mouse_x<x_menus+310 && mouse_y>y_menus+80 && mouse_y<y_menus+100)
        {
            wave_play_state=toggle(wave_play_state);
            mouse_released=1;
        }
          if(mouse_x>x_menus+320 && mouse_x<x_menus+340 && mouse_y>y_menus+80 && mouse_y<y_menus+100)
        {
            seek_button_view(x_menus+320,y_menus+80,1);
            seek_to_beg_wave();
            mouse_released=1;
        }
    }
}


Rect BPMF(Vec2D(x_menus+290,y_menus+120),Vec2D(50,20));
BPMF.SetRoundness(4.5);
BPMF.Draw(CouleurBleu2);
BPMF.DrawOutline(CouleurLigne.WithAlpha(0.5));
petitchiffre.Print(ol::ToString(BPM_WAVE_RATE),x_menus+300,y_menus+135);
minichiffre.Print("BPM",x_menus+325,y_menus+143);

if(window_focus_id==W_WAVE)
{
    if(mouse_x>x_menus+290 && mouse_x<x_menus+340 && mouse_y>y_menus+120 && mouse_y<y_menus+140)
    {
        if(mouse_button==1 && mouse_released==0)
        {
            int newBPM=atoi(numeric);
            if(newBPM>0 && newBPM<= 6000)
            {
                mouse_released=1;
                BPM_WAVE_RATE=newBPM;
                install_int_ex(ticker_WAVE ,BPM_TO_TIMER(BPM_WAVE_RATE));
                reset_numeric_entry();

            }
        }
    }
}

//curseur
Rect WaverControlFrame(Vec2D(x_menus+15,y_menus+120),Vec2D(256,8));
WaverControlFrame.DrawOutline(CouleurLigne.WithAlpha(0.3));

Rect WaverControlSlider(Vec2D(x_menus+15+(waver_control*10),y_menus+120),Vec2D(6,10));
WaverControlSlider.Draw(CouleurFader);
if(window_focus_id==W_WAVE)
{


if( Midi_Faders_Affectation_Type!=0  && mouse_x>=x_menus+15 && mouse_x<=x_menus+266 && mouse_y>=y_menus+120 && mouse_y<=y_menus+128)
{
 WaverControlFrame.DrawOutline(CouleurBlind);
}



    if(mouse_button==1 && mouse_x>=x_menus+15 && mouse_x<=x_menus+266 && mouse_y>=y_menus+120 && mouse_y<=y_menus+128)
    {
    set_mouse_range(x_menus+15, y_menus+120, x_menus+266, y_menus+128);

     if( Midi_Faders_Affectation_Type!=0 && mouse_released==0)
        {
        attribute_midi_solo_affectation(2117,Midi_Faders_Affectation_Mode);
        mouse_released=1;
        }
        else
        {
        waver_control=(mouse_x-(x_menus+15))/10 ;
        midi_levels[2117]=(mouse_x-(x_menus+15))/2;
        wave_calculations();
        }
    }
 }



//presets de circuits

Rect PChan(Vec2D(0,0),Vec2D(10,10));
for (int i=0;i<4;i++)
{
    PChan.MoveTo(Vec2D(x_menus+285+(i*15),y_menus+50));
    if(i==wave_channel_preset_selected){PChan.Draw(CouleurFader);}
    PChan.DrawOutline(CouleurLigne.WithAlpha(0.2));
    if(window_focus_id==W_WAVE)
    {
        if(mouse_button==1 && mouse_released==0 && mouse_x>x_menus+285+(i*15) && mouse_x<x_menus+295+(i*15)
           && mouse_y>y_menus+50 && mouse_y<y_menus+60)
        {

        if(index_main_clear==1)
        {
         for(int i=0;i<26;i++)
         {
             channel_slots[wave_channel_preset_selected][i]=0;
         }
         index_main_clear=0;
        }
        else
        {
        wave_channel_preset_selected=i;
        }
        mouse_released=1;

        }
    }
}
///////////////////Damper params

Rect Lev(Vec2D(x_menus+200, y_menus+255),Vec2D( 127*(Wave_Dampered[0].getdecay()),12 ));
Rect Flev(Vec2D(x_menus+200, y_menus+255),Vec2D( 127,12 ));
Lev.Draw(CouleurBleu2);
Flev.DrawOutline(CouleurLigne.WithAlpha(0.5));
minichiffregris.Print("Decay",x_menus+205,y_menus+264);
int f=127*Wave_Dampered[0].getdecay();
petitpetitchiffregris.Print(ol::ToString(f),x_menus+235,y_menus+264);

Rect levDt(Vec2D(x_menus+200, y_menus+275),Vec2D( 127*(Wave_Dampered[0].getdt()*10),12 ));
Rect FDt(Vec2D(x_menus+200, y_menus+275),Vec2D( 127,12 ));
levDt.Draw(CouleurBleu2);
FDt.DrawOutline(CouleurLigne.WithAlpha(0.5));
minichiffregris.Print("Delta",x_menus+205,y_menus+283);
f=127*Wave_Dampered[0].getdt()*10;
petitpetitchiffregris.Print(ol::ToString(f),x_menus+235,y_menus+283);


Rect Mod(Vec2D(x_menus+307, y_menus+240),Vec2D( 20,10 ));
Mod.Draw(CouleurBleu2);
Mod.DrawOutline(CouleurLigne.WithAlpha(0.5));
minichiffregris.Print(ol::ToString(Wave_Dampered[0].getdampermode()),x_menus+316,y_menus+248);


button_midi_out_visu(x_menus+20,y_menus+275,2114);//All midi for wave!!!
if(window_focus_id==W_WAVE)
{

//Damper midi out
if( mouse_button==1 && mouse_released==0)
{
    button_midi_out_core(x_menus+20,y_menus+275,2114);//All midi for wave!!!
    midi_send_out[2115]=midi_send_out[2114];
    midi_send_out[2117]=midi_send_out[2114];


}
}

//LOGIQUE DES DAMPERS SETS
if(window_focus_id==W_WAVE)
{

//DECAY CONSTANT OF DAMPER
if( mouse_x>x_menus+200 && mouse_x<=x_menus+327 && mouse_y>y_menus+255 && mouse_y<y_menus+267)
{

if( Midi_Faders_Affectation_Type!=0)
{
 Flev.DrawOutline(CouleurBlind);
}

if( mouse_button==1 )
{
if( Midi_Faders_Affectation_Type!=0 && mouse_released==0)
{
attribute_midi_solo_affectation(2114,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
    set_mouse_range(x_menus+200, y_menus+255, x_menus+327, y_menus+267);
    for(int i=0;i<26;i++)
    {
    Wave_Dampered[i].set_damper_decay(1.0-(((float)(x_menus+327-mouse_x))/127));
    }
    midi_levels[2114]=127-(x_menus+327-mouse_x);
    index_send_midi_out[2114]=1;
}
}
if( Midi_Faders_Affectation_Type!=0)
{
//midi report
 switch(miditable[0][2114])
 {
  case 0:
  sprintf(thetypinfo,"Note");
  break;
  case 1:
  sprintf(thetypinfo,"Key On");
  break;
  case 2:
  sprintf(thetypinfo,"Key Off");
  break;
  case 4:
  sprintf(thetypinfo,"Ctrl Change");
  break;
  default: break;
}
  sprintf(string_last_midi_id,"Wave Decay is Ch: %d Pitch: %d Type: %s", miditable[1][2114],miditable[2][2114],thetypinfo);
}

}

//DT CONSTANT OF DAMPER
if( mouse_x>x_menus+200 && mouse_x<=x_menus+327 && mouse_y>y_menus+275 && mouse_y<y_menus+287)
{
if( Midi_Faders_Affectation_Type!=0)
{
 FDt.DrawOutline(CouleurBlind);
}
if( mouse_button==1 )
{
if( Midi_Faders_Affectation_Type!=0 && mouse_released==0)
{
attribute_midi_solo_affectation(2115,Midi_Faders_Affectation_Mode);
mouse_released=1;
}
else
{
    set_mouse_range(x_menus+200, y_menus+275, x_menus+327, y_menus+287);
    for(int i=0;i<26;i++)
    {
    Wave_Dampered[i].set_damper_dt((1.0-(((float)(x_menus+327-mouse_x))/127))/10);
    }
    midi_levels[2115]=127-(x_menus+327-mouse_x);
    index_send_midi_out[2115]=1;
}
}
if( Midi_Faders_Affectation_Type!=0)
{
//midi report
 switch(miditable[0][2115])
 {
  case 0:
  sprintf(thetypinfo,"Note");
  break;
  case 1:
  sprintf(thetypinfo,"Key On");
  break;
  case 2:
  sprintf(thetypinfo,"Key Off");
  break;
  case 4:
  sprintf(thetypinfo,"Ctrl Change");
  break;
  default: break;
}
  sprintf(string_last_midi_id,"Wave DT is Ch: %d Pitch: %d Type: %s", miditable[1][2115],miditable[2][2115],thetypinfo);
}

}


//Damper mode
if( mouse_x>x_menus+307 && mouse_x<x_menus+327 && mouse_y>y_menus+240 && mouse_y<y_menus+250)
{
if( Midi_Faders_Affectation_Type!=0)
{
 Mod.DrawOutline(CouleurBlind);
}
if(mouse_button==1 && mouse_released==0)
{
if( Midi_Faders_Affectation_Type!=0 )
{
attribute_midi_solo_affectation(2116,Midi_Faders_Affectation_Mode);}
else
{
    Wave_Dampered[0].set_damper_mode(Wave_Dampered[0].getdampermode()+1);
    int u=Wave_Dampered[0].getdampermode();
    for(int i=1;i<26;i++)
    {
    Wave_Dampered[i].set_damper_mode(u);
    }
    mouse_released=1;
}
}
if( Midi_Faders_Affectation_Type!=0)
{
//midi report
 switch(miditable[0][2116])
 {
  case 0:
  sprintf(thetypinfo,"Note");
  break;
  case 1:
  sprintf(thetypinfo,"Key On");
  break;
  case 2:
  sprintf(thetypinfo,"Key Off");
  break;
  case 4:
  sprintf(thetypinfo,"Ctrl Change");
  break;
  default: break;
}
  sprintf(string_last_midi_id,"WAVE Damper Mode is Ch: %d Pitch: %d Type: %s", miditable[1][2116],miditable[2][2116],thetypinfo);
}
}



}



//modèle de pinceau

petitchiffre.Print("BRUSH",x_menus+15,y_menus+150);
Rect SlotLeadFrame(Vec2D(0,0),Vec2D(6,6));

for(int i=0; i<26; i++)
{
 SlotFrame.MoveTo(Vec2D(x_menus+15+(i*10),y_menus+170));
 Rect SlotValue(Vec2D(x_menus+15+(i*10),y_menus+195-( brush_slots[brush_selected][i]*25)) ,Vec2D(6, ( 25*brush_slots[brush_selected][i])));
 SlotValue.Draw(CouleurBlind.WithAlpha(0.5));
 SlotFrame.DrawOutline(CouleurLigne.WithAlpha(0.3));
 SlotLeadFrame.MoveTo(Vec2D(x_menus+15+(i*10),y_menus+210));
 if(lead_brush_reading[brush_selected]==i){SlotLeadFrame.Draw(CouleurFader);}
 SlotLeadFrame.DrawOutline(CouleurLigne.WithAlpha(0.3));



 if(window_focus_id==W_WAVE)
 {
    if(mouse_x>=x_menus+15+(i*10) && mouse_x<=x_menus+15+(i*10)+6 )
    {
        //affichage levels inside brush
        if( mouse_y>=y_menus+170 && mouse_y<=y_menus+170+25)
        {
            switch(dmx_view)
            {
            case 0:
                 petitchiffre.Print(ol::ToString((int)(brush_slots[brush_selected][i]*100)),x_menus+15+(i*10),y_menus+160);
            break;
            case 1:
                 petitchiffre.Print(ol::ToString((int)(brush_slots[brush_selected][i]*255)),x_menus+15+(i*10),y_menus+160);
            break;
            }
            Line(Vec2D(x_menus+15+(i*10),y_menus+160),Vec2D(x_menus+15+(i*10),y_menus+169)).Draw(CouleurLigne.WithAlpha(0.7));



        }

    if(mouse_button==1 && mouse_released==0)
        {
            if(numeric_postext>0 && index_do_dock==1)//attribuer le niveau au clavier
            {
            int lev_=atoi(numeric);
            switch(dmx_view)
            {
            case 0:
            if(lev_>=0 && lev_<=100)
            {
              brush_slots[brush_selected][i]=((float)lev_)/100.0;
              set_new_values_in_wave();
            }
            break;
            case 1:
            if(lev_>=0 && lev_<=255)
            {
              brush_slots[brush_selected][i]=((float)lev_)/255.0;
              set_new_values_in_wave();
            }
            break;
            }
            reset_numeric_entry();
            mouse_released=1;
            }
        else //souris dessine
            {
            //drawing de la brush
            if( mouse_y>=y_menus+170 && mouse_y<=y_menus+170+25)
            {
            //25= size of the slot
            brush_slots[brush_selected][i]=1.0-(((float)(mouse_y-(y_menus+170)))/25);
            }
            //selecting ofset to report the brush on waver control position
            else if( mouse_y>=y_menus+210 && mouse_y<=y_menus+216)
            {

            lead_brush_reading[brush_selected]=i;
            if(previous_lead_brush_reading[brush_selected]!=lead_brush_reading[brush_selected])
            {
            set_new_values_in_wave();previous_lead_brush_reading[brush_selected]=lead_brush_reading[brush_selected];}
            }
            }

        }
    }
    //sélection du lead (report du brush sur le curseur)
 }

}

//lead brush reading: endroit de la palette qui est lu et impacté en position de curseur



//presets de brushs

Rect PBrush(Vec2D(0,0),Vec2D(10,10));
for (int i=0;i<4;i++)
{
    PBrush.MoveTo(Vec2D(x_menus+285+(i*15),y_menus+206));
    if(i==brush_selected){PBrush.Draw(CouleurBlind.WithAlpha(0.5));}
    PBrush.DrawOutline(CouleurLigne.WithAlpha(0.2));
    if(window_focus_id==W_WAVE)
    {
        if(mouse_button==1 && mouse_released==0 && mouse_x>x_menus+285+(i*15) && mouse_x<x_menus+295+(i*15)
           && mouse_y>y_menus+206 && mouse_y<y_menus+216)
        {

        if(index_main_clear==1)
        {
         for(int i=0;i<26;i++)
         {
             brush_slots[brush_selected][i]=0.0;
         }
         index_main_clear=0;
        }
        else
        {
        brush_selected=i;
        }
        mouse_released=1;

        }
    }
}


return(0);
}


int do_logical_fenetre_wave_menus(int x_menus,int y_menus)
{


return(0);
}

