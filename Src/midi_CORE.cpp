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

* \file midi_CORE.cpp
* \brief {midi Core}
* \author Christoph Guillermet
* \version {0.8.8?8}
* \date {09/03/2016}

 White Cat {- categorie} {- sous categorie {- sous categorie}}

*   Fonctions core du la gestion midi
*
*   Midi Core fonctions
*
**/

//pour midi


pascal void MSALARMAPI ReceiveEvents(short r);
pascal void MSALARMAPI ReceivePolling ( long date, short r, long a, long b, long c);


MidiName	AppliName = "WhiteCat";
/////////////////////////////////////////////////////////////////////////////////
int midi_init_sepecial_case_key_on()
{
for(int i=0;i<48;i++)//faders
{
midi_needs_no_key_on_key_off[900+i]=1;
}
return(0);
}




int InitTblLibEv() {
  int i;

  for (i=0;i<255;i++) strcpy(TblLibEv[i],"");

  strcpy(TblLibEv[typeNote],		 "Note        ");
  strcpy(TblLibEv[typeKeyOn],		 "Key On      ");
  strcpy(TblLibEv[typeKeyOff],		 "Key Off     ");
  strcpy(TblLibEv[typeKeyPress],	 "Key Press   ");
  strcpy(TblLibEv[typeCtrlChange],	 "Ctrl Change ");
  strcpy(TblLibEv[typeProgChange],	 "Prog Change ");
  strcpy(TblLibEv[typeChanPress],	 "Chan Press  ");
  strcpy(TblLibEv[typePitchWheel],	 "Pitch Wheel ");
  strcpy(TblLibEv[typeSongPos],	 	 "SongPos     ");
  strcpy(TblLibEv[typeSongSel],	 	 "SongSel     ");
  strcpy(TblLibEv[typeClock],		 "Clock       ");
  strcpy(TblLibEv[typeStart],		 "Start       ");
  strcpy(TblLibEv[typeContinue],	 "Continue    ");
  strcpy(TblLibEv[typeStop],		 "Stop        ");
  strcpy(TblLibEv[typeTune],		 "Tune        ");
  strcpy(TblLibEv[typeActiveSens],	 "Active Sens.");
  strcpy(TblLibEv[typeReset],		 "Reset       ");
  strcpy(TblLibEv[typeSysEx],		 "System Excl.");
  strcpy(TblLibEv[typeStream],		 "Stream      ");
  strcpy(TblLibEv[typePrivate],	 	 "Private     ");
  strcpy(TblLibEv[typeProcess],	  	 "Process     ");
  strcpy(TblLibEv[typeDProcess],	 "DProcess    ");
  strcpy(TblLibEv[typeQuarterFrame], "QuarterFrame");
  strcpy(TblLibEv[typeCtrl14b],	 	 "Ctrl 14bits ");
  strcpy(TblLibEv[typeNonRegParam],  "NonRegParam.");
  strcpy(TblLibEv[typeRegParam],	 "Reg Param   ");
  strcpy(TblLibEv[typeSeqNum],		 "Seq Number  ");


  strcpy(TblLibEv[typeTextual],	 	 "Text        ");

  strcpy(TblLibEv[typeCopyright],	 "Copyright   ");
  strcpy(TblLibEv[typeSeqName],	 	 "Seq Name    ");
  strcpy(TblLibEv[typeInstrName],	 "Instr Name  ");
  strcpy(TblLibEv[typeLyric],		 "Lyric       ");
  strcpy(TblLibEv[typeMarker],		 "Marker      ");
  strcpy(TblLibEv[typeCuePoint],	 "CuePoint    ");
  strcpy(TblLibEv[typeChanPrefix],	 "Chan Prefix ");
  strcpy(TblLibEv[typePortPrefix],	 "Port Prefix ");
  strcpy(TblLibEv[typeEndTrack],	 "End Track   ");
  strcpy(TblLibEv[typeTempo],		 "Tempo       ");
  strcpy(TblLibEv[typeSMPTEOffset],  "SMPTE Offset");
  strcpy(TblLibEv[typeTimeSign],	 "Time Sign.  ");
  strcpy(TblLibEv[typeKeySign],	 	 "Key Sign.   ");
  strcpy(TblLibEv[typeSpecific],	 "Specific    ");
  strcpy(TblLibEv[typeReserved],	 "Reserved    ");
  strcpy(TblLibEv[typeDead],		 "Dead        ");
return(0);
}

/* ------------------------------------------------------------------------- */
pascal void InstallFilter( short refNum, MidiFilterPtr filter )
{
     	short i;

    if (!myFilter) return;
	for (i = 0 ; i < 256 ; i++ )
	{
	 	MidiAcceptType(myFilter,i,false);
		MidiAcceptPort(myFilter,i,true);
	}
	for (i = 0 ; i < 16 ; i++ ) MidiAcceptChan(myFilter,i,true);

	MidiAcceptType(myFilter,typeKeyOn, true);
	MidiAcceptType(myFilter,typeKeyOff, true);
	MidiAcceptType(myFilter,typeCtrlChange, true);
 	MidiAcceptType(myFilter,typePitchWheel, true);
 	MidiAcceptType(myFilter,typeProgChange, true);
 	//midi clock
/*  MidiAcceptType(myFilter,typeClock, true);
    MidiAcceptType(myFilter,typeQuarterFrame, true);
    MidiAcceptType(myFilter, typeStart, true);
    MidiAcceptType(myFilter, typeContinue, true);
    MidiAcceptType(myFilter, typeStop, true);*/
    //Notes off Note On pour Twister
    MidiAcceptType(myFilter,NoteOff , true);
    MidiAcceptType(myFilter,NoteOn , true);

	MidiSetFilter(refNum, myFilter);
}


/* ------------------------------------------------------------------------- */
//rajouts drivers

/*
#define MidiShareDrvRef		127

void  WakeUp(short r)
	{
		MidiConnect(MidiShareDrvRef, r, true);
		MidiConnect(r, MidiShareDrvRef, true);
	}

void  Sleep(short r)
	{
	}
*/

int InitMidi()
{
/*if ( !MidiShare())
{
sprintf (string_Last_Order,"MidiShare not available\n");
}
InitTblLibEv();

myRefNum = MidiOpen("WhiteCat"); //ouverture classique
*/
//driver nouveau code
/*		TDriverInfos infos = { "WhiteCat", 100, 0, { 0, 0 } };
		TDriverOperation op = { WakeUp, Sleep, {0, 0 } };
		myRefnum = MidiRegisterDriver(&infos, &op);*/

/*if (myRefNum < 0) {sprintf(string_Last_Order,"MidiOpen failed!");}


MidiSetRcvAlarm(myRefNum,ReceiveEvents);

MidiConnect(0, myRefNum, true);//in
MidiConnect(myRefNum,0,true);//out

myFilter = MidiNewFilter();
InstallFilter( myRefNum,myFilter ); //filtrage
*/
if ( !MidiShare())
{
sprintf (string_Last_Order,"MidiShare not available\n");
}
InitTblLibEv();
myRefNum = MidiOpen(AppliName);
if (myRefNum < 0) {sprintf(string_Last_Order,"MidiOpen failed!");}

MidiSetRcvAlarm(myRefNum,ReceiveEvents);
MidiConnect(0, myRefNum, true);//in
MidiConnect(myRefNum,0,true);//out
myFilter = MidiNewFilter();
InstallFilter( myRefNum,myFilter ); //filtrage


return(0);
}


int QuitMidi()
{
	MidiFreeFilter(myFilter);
	//midi driver
	//MidiUnregisterDriver(myRefnum);
	MidiClose(myRefNum);
	return ( 0);
}

