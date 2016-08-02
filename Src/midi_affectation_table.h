//MIDI TABLE AFFECTATIONS TO HAVE A QUICK LOOK AT ADRESSES BEFORE WIMMING INSIDE MIDI_13.CPP FILE
//PLEASE GIVE SIGNALEMENT OF MIDI NEW ADRESS ALSO IN THIS FILE
/*
//laucnhpad:
Hex  Decimal  Colour  Brightness
 0Ch  12  Off  Off
 0Dh  13  Red  Low
 0Fh  15  Red  Full
 1Dh  29  Amber  Low
 3Fh  63  Amber  Full
 3Eh  62  Yellow  Full
 1Ch  28  Green  Low
 3Ch  60  Green  Full
alues for flashing LEDs are:
Hex  Decimal  Colour  Brightness
 0Bh  11  Red  Full
 3Bh  59  Amber  Full
 3Ah  58  Yellow  Full
 38h  56  Green  Full


///////FADERS///////
0-47 les 48 faders
48->96 dock -
97->145 docks +
146->194 Lock
/////LFO/////////
196->244 lfo speed
245->293 up lfo
294->342 down lfo
343->391 saw lfo
392->440 cycle dock minus
441->489 cycle dock plus
499->547 aller retour lfo
////SEQUENCIEL/////

491: fader X1
492: fader X2
493: fader sequenciel speed
494: goback
495: go
496: double go

//Trichro:
497: roue de couleur
498: decay tracking

//boutons de commandes ALL AT ZERO DES FADERS
548: all faders off
549: all speed at 64
550: all lock off
551: all lfo off
552: all loop off
553: all off
554: all midi out off
555: RECALL

//
556 -> 604 // receive midi in do action on Faders ( F1 F2 F3 F4 F5)

//
605->614 // lock preset call

//
615 grand master

//Audioplayers
616 -> 619  niveau
620 -> 623  Pan
624 -> 627 Pitch
628 -> 631 Play
632 -> 635 Seek to 0
636 -> 639 General Loop
640 -> 643 Backward
644 -> 647 Forward
648 -> 651 Set In
652 -> 655 Set Out
656 -> 659 Cue On Off
660 -> 663 Seek cue

//Num Pad
664: midi level relativ/absolute
665: Pad Enter
666: Pad +
667: Pad -
668: Pad Up
669: Pad down
670: Pad 0
671: Pad 1
672: Pad 2
673: Pad 3
674: Pad 4
675: Pad 5
676: Pad 6
677: Pad 7
678: Pad 8
679: Pad 9
680: Pad Point
681: Pad Esc
682: Pad ALL
683: Pad Inv
684: Pad To

//rajout faders
685 -> 733 SetSTop faders

//////Banger
734: Bang It !
735 -> 740: les bangs solos
741 : banger page -
742: banger page +

/////appel grandes fonctions
743 : dock
744: modify
745: report
746! clear
747: name
748: time
749: trichro
750: trakcking
751: seq
752: fader
753: banger
754: blind
755: cfg menu
756: audio player
757: quit

//commandes fenetre time
758: roue de temps
759: bouton switch temps
760: din
761: in
762: dout
763: out
764: affect
765: chrono
766: reset chrono

767: Move fader space latéral only

//suite sequenciel
768: create new mem
769: delete mem
770: stage minus
771: stage plus
772: preset minus
773: preset plus


//Midi minifaders controls
774: previous selection
775: next selection
776: select
777: unselect
778: flash
779: lock
780: loop
781: LFO up
782: LFO down
783: Lfo Saw
784: All dock looped
785: All at 0
786: Set pos
787: To Prev Dock mode
788: to next dock mode
789: up and down mode
790: sel prev dock
791: sel next dock
792: NA
794 -> 801 preset minifaders
//suite des fonctions individuelles de chaque fader
802->850 Loop a Fader One
851->899 Loop a Fader All
900-> 948 Flash a Fader
//Suite trichromie
949->956 Dock colors à choisir
//suite tracking video
957-> 968 trackspace ( video)
969-> 973 presets video

//chaser selected:
974 Chaser -
975 Chaser +
976 view track Up
977 view track down
978 Play
979 Seek
980 Loop

981 Forward
982 backward
983 aller retour
984 All
985 Inv
986 Off
987 -> 990 P1 à P4
991-> 993 Operator Up Stay Down
994 T join / T Std
995 Beg Point
996 End Point
997 Pos Timeline
998 -> 1022 ON OFF tracks
1023 -> 1047 Level tracks
1048 -> 1112 Launchpad sur cases Chasers 8*8
1113 Minus Lchpad Pos
1114 Plus Lchpad Pos

1115 -> 1163 Faders: Play embeded chaser
1164 -> 1212 Faders: Seek to beg embeded chaser
1213 -> 1264 Faders: Loop embeded chaser

1265 1266 iCatPage - +
1267 ->1274 iCatpage Num
1275 icat Oreintation
1276 icat refresh page construction

1277 MidiMute

1278 -> 1325 autolauch chaser embeded ( 48 faders)

1326 tap tempo
1327 rec tap tempo
1328 tap send to chaser

//rajout commandes fenetres
1329 wizard window
1330 save window
1331 patch window
1332 list
1333 direct ch
1334 view
1335 freeze
1336 minifaders window
1337 chaser window
1338 numeric pad
1339 mover window
1340 grider window
1341 iCat builder
1342 help window

1343+128 les 128 bangers

sur les 4 gridplayers
1472->1475 on off des view des grid players
1476->1479 minus grid selection
1480->1483 plus grid selection
1484->1487 minus step selection
1488->1491 plus step selection
1492->1495 Play
1496->1499 Seek
1500->1503 Autostop
1504->1507 Slave on off
1508->1511 Speed
1512->1515 Goto ON (macro)
1516->1519 Count ON (macro)
1520->1523 SeekPos ON (macro)
1524->1527 StopPlay ON (macro)
1528->1531 GridCall par midi 0-127= 1-128
1532->1535 StepCall par midi plage *127
1536->1539 StepCall par midi plage unités +127
1540 on/off asservissement speed sequenciel sur gridplayer 1

1541 do exclude channels from GM
1542 do hipass mode

1543->1590 change fader fx mode
1591 auto reset crossfade speed
1592 group fader function assignation

1593 Midi send midi out faders

1594 Plot window call

1595 Show Levels
1596 Show Levels from faders

1597 Plot List Up
1598 Plot List Down
1599 Plot List CC
1600 Plot List ADD

1601 rotate
1602 Dub
1603 Delete
1604 Send To

1605 Layer 1
1606 Layer 2
1607 Layer 3
1608 Layer 4

1609 Toggle mode Layer

1610 Attrib edit CH
1611 Attrib edit Name
1611 Attrib edit Gels
1613 Attrib edit Dim
1614 Attrib edit Notes

1615 > 1623 inclut Preset Attributes



1624: Channel Handle

1625: midi affectation

1626: MENUS calls

1627: Fader Barre UP DOWN


1628 à 43 sélection des channels view

1644 Classical 512 channel view

1645 GOTO Sequenciel

1646 à 1651 les 6 presets de draw
1652 Draw mode
1653 à 1655 les niveaux de pression, tilt et ghost
1656 continuous GPL
1657 erase drawing selected
1658 Brush type

1659 fenetre draw
1660 midi X draw
1661 midi Y draw

1662 Echo window
1663 > 1685 les echo presets
1686 > 1690 les 5 actions midi de bounce etc
1691 et 1692 prev next chan
1693 > 1695 les 3 sliders de paramétrages global
1696  le bouton de mode d edition ( level ground)


1700 > MOVER ET PARAMS DEJA AFFECTES DANS ICAT


1800 > 1804 player audio autoload
1805 > 1808 player audio autostop
1809 > 1812 player load file num
1813 > 1816 player prev track
1817 > 1820 player next track
1821 > 1824 seek to end

//Christoph Touch_OSC remote control implementation for NUMPAD
1825 > check minus or check dimmer minus if false shift ONE
1826 > check plus or check dimmerplus if false shift ONE
1827 > at full
1828 > at zero

//WAVE Window
1829 > window WAVE in menu


1830 > 1893  arduino analogic on/off

1894: midi clock level
1895 > 1921 midiclock preset

1912 > 1959 DamperFader ON Off
1960 > 2007 DamperFader decay
2008 > 2055 DamperFader Mode
2056 > 2113 DamperFader Dt

//WAVE
2114 > Decay for wave
2115 > Dt for Wave
2116 > MODE damper for WAVE
2117 > Slider for Wave controler
*/
