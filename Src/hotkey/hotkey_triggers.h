/*-------------------------------------------------------------------------------------------------------------
                                 |
          CWWWWWWWW              | Copyright (C) 2009-2016  Christoph Guillermet
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

* \file hotkey_triggers.h
* \brief {Declaration of global functions of White Cat - global for hotkeys management}
* \author Rui Serge Azevedo Brooks from Christoph Guillermet's original sources
* \version {1.0.0}
* \date {01/02/2015}

 White Cat - hotkey

*   Déclaration des méthodes des raccourcis clavier de White Cat
*
*
*/

#ifndef WHC_HOTKEY_FCT_H
#define WHC_HOTKEY_FCT_H

void do_bang_trigger(int banger_number) ;
void hk_trigger_01_save() ;
void hk_trigger_02_save_and_quit() ;
void hk_trigger_03_quit() ;
void hk_trigger_04_snapshot_close_windows() ;
void hk_trigger_05_snapshot_open_windows() ;
void hk_trigger_06_cycle_forward_open_windows() ;
void hk_trigger_07_cycle_backward_open_windows() ;
void hk_trigger_08_open_forward_solo_windows() ;
void hk_trigger_09_open_backward_solo_windows() ;
void hk_trigger_10_Store_mode() ;
void hk_trigger_11_Modify_mode() ;
void hk_trigger_12_Report_mode() ;
void hk_trigger_13_Clear_mode() ;
void hk_trigger_14_Name() ;
void hk_trigger_15_Time() ;
void hk_trigger_16_Trichromy() ;
void hk_trigger_17_Video_Tracking() ;
void hk_trigger_18_CueList() ;
void hk_trigger_19_Faders() ;
void hk_trigger_20_MiniFaders() ;
void hk_trigger_21_Banger() ;
void hk_trigger_22_Blind_mode() ;
void hk_trigger_23_CFG_Menu() ;
void hk_trigger_24_Chasers() ;
void hk_trigger_25_Mover() ;
void hk_trigger_26_selectedAllChannels() ;
void hk_trigger_27_unselectedChannels() ;
void hk_trigger_28_movingSelectionLeft() ;
void hk_trigger_29_movingSelectionRight() ;
void hk_trigger_30_fullLevel() ;
void hk_trigger_31_levelToZero() ;
void hk_trigger_32_plusPercentForTheSelection() ;
void hk_trigger_33_minusPercentForTheSelection() ;
void hk_trigger_34_Check_Channel_left() ;
void hk_trigger_35_Check_Channel_right() ;
void hk_trigger_36_Copy_to_the_Clipboard_Select_channels() ;
void hk_trigger_37_Paste_channels_from_clipboard() ;
void hk_trigger_38_Get_Import_channels_from_a_memory() ;
void hk_trigger_39_Memory_recording_deleting___Create_or_over_record_a_memory_number() ;
void hk_trigger_40_Memory_recording_deleting___Create_memory_adding_the_faders() ;
void hk_trigger_41_Memory_recording_deleting___Delete_memory() ;
void hk_trigger_42_Memory_recording_deleting___Over_record_on_stage_or_blind() ;
void hk_trigger_43_Memory_recording_deleting___Over_record_on_stage_or_blind_with_faders() ;
void hk_trigger_44_Memory_recording_deleting___Reload_a_memory() ;
void hk_trigger_45_Memory_recording_deleting___Reload_a_deleted_mem() ;
void hk_trigger_46_GET_level_of_selected_channels_from_memory() ;
void hk_trigger_47_Navigating_thru_memories___Previous_mem_on_stage() ;
void hk_trigger_48_Navigating_thru_memories___Next_mem_on_stage() ;
void hk_trigger_49_Navigating_thru_memories___Previous_mem_on_preset() ;
void hk_trigger_50_Navigating_thru_memories___Next_mem_on_preset() ;
void hk_trigger_51_Crossfade_GO_PAUSE() ;
void hk_trigger_52_Crossfade_GO_BACK() ;
void hk_trigger_53_Crossfade_DOUBLE_GO() ;
void hk_trigger_54_Patch() ;
void hk_trigger_55_Numpad() ;
void hk_trigger_56_Dimmers_selection___select_all_dimmers() ;
void hk_trigger_57_Dimmers_selection___unselect_all_dimmers() ;
void hk_trigger_58_Check_Dimmer___left() ;
void hk_trigger_59_Check_Dimmer___right() ;
void hk_trigger_60_Select_Presets_1() ;
void hk_trigger_61_Select_Presets_2() ;
void hk_trigger_62_Select_Presets_3() ;
void hk_trigger_63_Select_Presets_4() ;
void hk_trigger_64_Select_Presets_5() ;
void hk_trigger_65_Select_Presets_6() ;
void hk_trigger_66_Select_roi_1() ;
void hk_trigger_67_Select_roi_2() ;
void hk_trigger_68_Select_roi_3() ;
void hk_trigger_69_Select_roi_4() ;
void hk_trigger_70_Select_roi_5() ;
void hk_trigger_71_Select_roi_6() ;
void hk_trigger_72_Select_roi_7() ;
void hk_trigger_73_Select_roi_8() ;
void hk_trigger_74_Select_roi_9() ;
void hk_trigger_75_Select_roi_10() ;
void hk_trigger_76_Select_roi_11() ;
void hk_trigger_77_Select_roi_12() ;
void hk_trigger_78_Bang_01() ;
void hk_trigger_79_Bang_02() ;
void hk_trigger_80_Bang_03() ;
void hk_trigger_81_Bang_04() ;
void hk_trigger_82_Bang_05() ;
void hk_trigger_83_Bang_06() ;
void hk_trigger_84_Bang_07() ;
void hk_trigger_85_Bang_08() ;
void hk_trigger_86_Bang_09() ;
void hk_trigger_87_Bang_10() ;
void hk_trigger_88_Bang_11() ;
void hk_trigger_89_Bang_12() ;
void hk_trigger_90_Bang_13() ;
void hk_trigger_91_Bang_14() ;
void hk_trigger_92_Bang_15() ;
void hk_trigger_93_Bang_16() ;
void hk_trigger_94_Bang_17() ;
void hk_trigger_95_Bang_18() ;
void hk_trigger_96_Bang_19() ;
void hk_trigger_97_Bang_20() ;
void hk_trigger_98_Bang_21() ;
void hk_trigger_99_Bang_22() ;
void hk_trigger_100_Bang_23() ;
void hk_trigger_101_Bang_24() ;
void hk_trigger_102_Bang_25() ;
void hk_trigger_103_Bang_26() ;
void hk_trigger_104_Bang_27() ;
void hk_trigger_105_Bang_28() ;
void hk_trigger_106_Bang_29() ;
void hk_trigger_107_Bang_30() ;
void hk_trigger_108_Bang_31() ;
void hk_trigger_109_Bang_32() ;
void hk_trigger_110_Bang_33() ;
void hk_trigger_111_Bang_34() ;
void hk_trigger_112_Bang_35() ;
void hk_trigger_113_Bang_36() ;
void hk_trigger_114_Bang_37() ;
void hk_trigger_115_Bang_38() ;
void hk_trigger_116_Bang_39() ;
void hk_trigger_117_Bang_40() ;
void hk_trigger_118_Bang_41() ;
void hk_trigger_119_Bang_42() ;
void hk_trigger_120_Bang_43() ;
void hk_trigger_121_Bang_44() ;
void hk_trigger_122_Bang_45() ;
void hk_trigger_123_Bang_46() ;
void hk_trigger_124_Bang_47() ;
void hk_trigger_125_Bang_48() ;
void hk_trigger_126_Bang_49() ;
void hk_trigger_127_Bang_50() ;
void hk_trigger_128_Bang_51() ;
void hk_trigger_129_Bang_52() ;
void hk_trigger_130_Bang_53() ;
void hk_trigger_131_Bang_54() ;
void hk_trigger_132_Bang_55() ;
void hk_trigger_133_Bang_56() ;
void hk_trigger_134_Bang_57() ;
void hk_trigger_135_Bang_58() ;
void hk_trigger_136_Bang_59() ;
void hk_trigger_137_Bang_60() ;
void hk_trigger_138_Bang_61() ;
void hk_trigger_139_Bang_62() ;
void hk_trigger_140_Bang_63() ;
void hk_trigger_141_Bang_64() ;
void hk_trigger_142_Bang_65() ;
void hk_trigger_143_Bang_66() ;
void hk_trigger_144_Bang_67() ;
void hk_trigger_145_Bang_68() ;
void hk_trigger_146_Bang_69() ;
void hk_trigger_147_Bang_70() ;
void hk_trigger_148_Bang_71() ;
void hk_trigger_149_Bang_72() ;
void hk_trigger_150_Bang_73() ;
void hk_trigger_151_Bang_74() ;
void hk_trigger_152_Bang_75() ;
void hk_trigger_153_Bang_76() ;
void hk_trigger_154_Bang_77() ;
void hk_trigger_155_Bang_78() ;
void hk_trigger_156_Bang_79() ;
void hk_trigger_157_Bang_80() ;
void hk_trigger_158_Bang_81() ;
void hk_trigger_159_Bang_82() ;
void hk_trigger_160_Bang_83() ;
void hk_trigger_161_Bang_84() ;
void hk_trigger_162_Bang_85() ;
void hk_trigger_163_Bang_86() ;
void hk_trigger_164_Bang_87() ;
void hk_trigger_165_Bang_88() ;
void hk_trigger_166_Bang_89() ;
void hk_trigger_167_Bang_90() ;
void hk_trigger_168_Bang_91() ;
void hk_trigger_169_Bang_92() ;
void hk_trigger_170_Bang_93() ;
void hk_trigger_171_Bang_94() ;
void hk_trigger_172_Bang_95() ;
void hk_trigger_173_Bang_96() ;
void hk_trigger_174_Bang_97() ;
void hk_trigger_175_Bang_98() ;
void hk_trigger_176_Bang_99() ;
void hk_trigger_177_Bang_100() ;
void hk_trigger_178_Bang_101() ;
void hk_trigger_179_Bang_102() ;
void hk_trigger_180_Bang_103() ;
void hk_trigger_181_Bang_104() ;
void hk_trigger_182_Bang_105() ;
void hk_trigger_183_Bang_106() ;
void hk_trigger_184_Bang_107() ;
void hk_trigger_185_Bang_108() ;
void hk_trigger_186_Bang_109() ;
void hk_trigger_187_Bang_110() ;
void hk_trigger_188_Bang_111() ;
void hk_trigger_189_Bang_112() ;
void hk_trigger_190_Bang_113() ;
void hk_trigger_191_Bang_114() ;
void hk_trigger_192_Bang_115() ;
void hk_trigger_193_Bang_116() ;
void hk_trigger_194_Bang_117() ;
void hk_trigger_195_Bang_118() ;
void hk_trigger_196_Bang_119() ;
void hk_trigger_197_Bang_120() ;
void hk_trigger_198_Bang_121() ;
void hk_trigger_199_Bang_122() ;
void hk_trigger_200_Bang_123() ;
void hk_trigger_201_Bang_124() ;
void hk_trigger_202_Bang_125() ;
void hk_trigger_203_Bang_126() ;
void hk_trigger_204_Bang_127() ;
void hk_trigger_205_Bang_128() ;
void hk_trigger_206_Bang_129() ;
void hk_trigger_207_Bang_130() ;
void hk_trigger_208_Bang_131() ;
void hk_trigger_209_Bang_132() ;
void hk_trigger_210_Bang_133() ;
void hk_trigger_211_Bang_134() ;
void hk_trigger_212_Bang_135() ;
void hk_trigger_213_Bang_136() ;
void hk_trigger_214_Bang_137() ;
void hk_trigger_215_Bang_138() ;
void hk_trigger_216_Bang_139() ;
void hk_trigger_217_Bang_140() ;
void hk_trigger_218_Bang_141() ;
void hk_trigger_219_Bang_142() ;
void hk_trigger_220_Bang_143() ;
void hk_trigger_221_Bang_144() ;
void hk_trigger_222_Bang_145() ;
void hk_trigger_223_Bang_146() ;
void hk_trigger_224_Bang_147() ;
void hk_trigger_225_Bang_148() ;
void hk_trigger_226_Bang_149() ;
void hk_trigger_227_Bang_150() ;
void hk_trigger_228_Bang_151() ;
void hk_trigger_229_Bang_152() ;
void hk_trigger_230_Bang_153() ;
void hk_trigger_231_Bang_154() ;
void hk_trigger_232_Bang_155() ;
void hk_trigger_233_Bang_156() ;
void hk_trigger_234_Bang_157() ;
void hk_trigger_235_Bang_158() ;
void hk_trigger_236_Bang_159() ;
void hk_trigger_237_Bang_160() ;
void hk_trigger_238_Bang_161() ;
void hk_trigger_239_Bang_162() ;
void hk_trigger_240_Bang_163() ;
void hk_trigger_241_Bang_164() ;
void hk_trigger_242_Bang_165() ;
void hk_trigger_243_Bang_166() ;
void hk_trigger_244_Bang_167() ;
void hk_trigger_245_Bang_168() ;
void hk_trigger_246_Bang_169() ;
void hk_trigger_247_Bang_170() ;
void hk_trigger_248_Bang_171() ;
void hk_trigger_249_Bang_172() ;
void hk_trigger_250_Bang_173() ;
void hk_trigger_251_Bang_174() ;
void hk_trigger_252_Bang_175() ;
void hk_trigger_253_Bang_176() ;
void hk_trigger_254_Bang_177() ;
void hk_trigger_255_Bang_178() ;
void hk_trigger_256_Bang_179() ;
void hk_trigger_257_Bang_180() ;
void hk_trigger_258_Bang_181() ;
void hk_trigger_259_Bang_182() ;
void hk_trigger_260_Bang_183() ;
void hk_trigger_261_Bang_184() ;
void hk_trigger_262_Bang_185() ;
void hk_trigger_263_Bang_186() ;
void hk_trigger_264_Bang_187() ;
void hk_trigger_265_Bang_188() ;
void hk_trigger_266_Bang_189() ;
void hk_trigger_267_Bang_190() ;
void hk_trigger_268_Bang_191() ;
void hk_trigger_269_Bang_192() ;
void hk_trigger_270_Bang_193() ;
void hk_trigger_271_Bang_194() ;
void hk_trigger_272_Bang_195() ;
void hk_trigger_273_Bang_196() ;
void hk_trigger_274_Bang_197() ;
void hk_trigger_275_Bang_198() ;
void hk_trigger_276_Bang_199() ;
void hk_trigger_277_Bang_200() ;
void hk_trigger_278_Bang_201() ;
void hk_trigger_279_Bang_202() ;
void hk_trigger_280_Bang_203() ;
void hk_trigger_281_Bang_204() ;
void hk_trigger_282_Bang_205() ;
void hk_trigger_283_Bang_206() ;
void hk_trigger_284_Bang_207() ;
void hk_trigger_285_Bang_208() ;
void hk_trigger_286_Bang_209() ;
void hk_trigger_287_Bang_210() ;
void hk_trigger_288_Bang_211() ;
void hk_trigger_289_Bang_212() ;
void hk_trigger_290_Bang_213() ;
void hk_trigger_291_Bang_214() ;
void hk_trigger_292_Bang_215() ;
void hk_trigger_293_Bang_216() ;
void hk_trigger_294_Bang_217() ;
void hk_trigger_295_Bang_218() ;
void hk_trigger_296_Bang_219() ;
void hk_trigger_297_Bang_220() ;
void hk_trigger_298_Bang_221() ;
void hk_trigger_299_Bang_222() ;
void hk_trigger_300_Bang_223() ;
void hk_trigger_301_Bang_224() ;
void hk_trigger_302_Bang_225() ;
void hk_trigger_303_Bang_226() ;
void hk_trigger_304_Bang_227() ;
void hk_trigger_305_Bang_228() ;
void hk_trigger_306_Bang_229() ;
void hk_trigger_307_Bang_230() ;
void hk_trigger_308_Bang_231() ;
void hk_trigger_309_Bang_232() ;
void hk_trigger_310_Bang_233() ;
void hk_trigger_311_Bang_234() ;
void hk_trigger_312_Bang_235() ;
void hk_trigger_313_Bang_236() ;
void hk_trigger_314_Bang_237() ;
void hk_trigger_315_Bang_238() ;
void hk_trigger_316_Bang_239() ;
void hk_trigger_317_Bang_240() ;
void hk_trigger_318_Bang_241() ;
void hk_trigger_319_Bang_242() ;
void hk_trigger_320_Bang_243() ;
void hk_trigger_321_Bang_244() ;
void hk_trigger_322_Bang_245() ;
void hk_trigger_323_Bang_246() ;
void hk_trigger_324_Bang_247() ;
void hk_trigger_325_Bang_248() ;
void hk_trigger_326_Bang_249() ;
void hk_trigger_327_Bang_250() ;
void hk_trigger_328_Bang_251() ;
void hk_trigger_329_Bang_252() ;
void hk_trigger_330_Bang_253() ;
void hk_trigger_331_Bang_254() ;
void hk_trigger_332_Bang_255() ;
//
void whc_hotkeys_init(std::string user_dir_file, std::string ressources_dir_file) ;

#endif // WHC_HOTKEY_FCT_H
