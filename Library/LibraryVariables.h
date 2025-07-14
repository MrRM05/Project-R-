#include "MainInclude.h"

extern uint GlobalAddressA, GlobalAddressB, GlobalAddressC, GlobalAddressD;
extern int GlobalIntA, GlobalIntB, GlobalIntC, GlobalIntD;
extern int64     GlobalInt64;
extern uint64    GlobalUInt64;
extern unsigned int GlobalUIntA, GlobalUIntB;
extern int MenuIntA, MenuIntB, MenuIntC, MenuIntD;
extern float GlobalFloatA, GlobalFloatB, GlobalFloatC, GlobalFloatD;
extern char GlobalCharA,GlobalCharB,GlobalCharC,GlobalCharD,GlobalCharE,GlobalFrameChar;

extern short GlobalShortA, GlobalShortB, GlobalShortC, GlobalShortD;
extern unsigned short GlobalUShortA, GlobalUShortB;
extern bool GlobalBoolA, GlobalBoolB, GlobalBoolC, GlobalBoolD;
extern unsigned long FreeSpaceAddress;
extern short GlobalShortA, GlobalShortB;
extern bool GlobalBoolA, GlobalBoolB, GlobalBoolC, GlobalBoolD;
extern int LoopValue;

extern bool ConsolePlatform, EmulatorPlatform, TempoBool, StopSwop;
// extern bool CustomWaterHeight[];
// extern short CloudCourseID, Snow3DCourseID; 
// extern char CloudCourseValue, Snow3DCourseValue, WeatherCourseValue, PADCourseValue;

extern short MenuPosition[2];
extern int wholeNumber;
extern int decimalNumber;
extern int printOffsetA, printOffsetB, printOffsetC, printOffsetD;
extern int minutes;
extern int seconds;

// extern float DebugPosition[3];
// extern Object *GlobalObjectA, *GlobalObjectB;
// //extern OKRAMHeader OverKartRAMHeader;

// extern float ZeroVector[3];

// extern struct POSXY PlayerSelectPositions[];
// extern struct PlayerTextureTable SelectNamePlateTable;
// extern struct PlayerTextureTable SelectPortraitTable[9];
// extern struct ObjBlock GlobalMenuHUD[32];
// extern struct Stats GlobalStat;
extern float GlobalWeight[];
extern struct Player GlobalPlayer[];
extern struct Screen GlobalScreen[];

extern struct Controller *GlobalController[];
//extern struct Screen *GlobalScreen[];
extern struct Camera *GlobalCamera[];
extern short *GlobalPath[];
extern long *GlobalLap[];
extern struct Lakitu *GlobalLakitu[];
extern struct AnmObject_Lakitu AnimatedLakituStruct[];
extern struct AnmObject g_DynamicObjects[];
extern struct FaceStruct CourseFaceStruct[];
extern struct PlayerState *GlobalPlayerState[];  
extern char *GlobalLightning[];
extern struct Skycolor *GlobalSkycolor[];
extern struct Playercolor *GlobalPlayercolor[];





// //MarioKart3D Variables
// extern int CoinCount;
// extern float AffineMatrix[4][4];
// extern float AffineMatrix2[4][4];
// extern float objectPosition[3];
// extern float objectVelocity[3];
// extern short objectAngle[3];
// extern short objectIndex;
// //
// //
// //extern struct OKEngine EngineClass[3][3];

// extern short EngineSpeed[3][3];
// extern short AccelerationCurve[3][10];
// extern short SteerAngle[3];
// extern short SteerValue[3];
// extern short PowerBand[3];
// extern short EnginePowerDownRT[3][15];
// extern short EnginePowerDownFT[3][15];


// extern char MenuBackup,MenuChanged,MenuTimer;
// extern char MenuFlash[4];
// extern char MenuProgress[4];

// extern char PlayerCharacterSelect[4];
// extern char PlayerShowStats[4];
// extern char PlayerEngineSelect[4];
// extern char PlayerSteerSelect[4];
// extern struct PlayerTextureTable BackupNamePlateTable;
// extern struct PlayerTextureTable BackupPortraitTable[9];


// //Mario Kart Stats
// extern char StatsID;
// //
// //





//SharedFunctions
extern long dataLength; //
extern int *targetAddress;
extern int *sourceAddress;
extern int *tempPointer;
extern long *graphPointer;
extern int *tkmPoint;
extern int RSPNumber;
extern int RSPOffset;
extern char *hex;
//

// //Stock Names
// extern char *stockCourseNames[];
// extern char *stockCharacterNames[];

// //Custom Levels


// //Main

// //extern struct OKObject OKObjectArray[];
extern short hsLabel, raceStatus, startupSwitch, courseSwapped;
// extern bool scrollLock;
// extern int currentHeaderAddress;
// extern short CoinPositions[8][3]; //8 Coins XYZ

// extern short FireParticlePositions[8][3];


// extern short gpCourseIndex, HotSwapID, hsGP, gpTimeCheck, courseValue;
// extern float gpTotalTime;


// extern int VersionNumber;
// extern char MenuButtonHeld, ButtonHeld, ButtonTimer, AudioLanguage;

// //
// //


// //CustomLevels
// extern int ScrollValues[32][2];





#define 	BTN_A		0x8000 
#define 	BTN_B		0x4000 
#define 	BTN_Z		0x2000 
#define 	BTN_START	0x1000 
#define 	BTN_DUP		0x0800 
#define 	BTN_DDOWN	0x0400 
#define 	BTN_DLEFT	0x0200 
#define 	BTN_DRIGHT	0x0100 
#define 	BTN_L		0x0020 
#define 	BTN_R		0x0010 
#define 	BTN_CUP		0x0008 
#define 	BTN_CDOWN	0x0004 
#define 	BTN_CLEFT	0x0002 
#define 	BTN_CRIGHT	0x0001

//GP SCENE AFTER RACE
#define DP_SORT_TIME 5

//GP POINTS
#define KSEQ_GPP_INIT	0
#define KSEQ_GPP_NAMEOFF 12 //8
#define KSEQ_GPP_NAMEON	13  //9

//Course
#define  MARIO_RW   0 
#define  CHOCO_MT   1 
#define  BOWSER_CA  2 
#define  BANSHEE_BW	3 
#define  YOSHI_VA	4 
#define  FRAPPE_SL	5 
#define  KOOPA_BE	6 
#define  ROYAL_RW	7 
#define  LUIGI_RW	8 
#define  MOOMOO_FA	9 
#define  TOAD_TP	10 
#define  KALI_DE	11 
#define  SHERB_LA	12 
#define  RAINBOW_RD	13 
#define  WARIO_ST	14 
#define  BLOCK_FO	15 
#define  SKY_SK	  	16 
#define  DOUBLE_DE	17 
#define  DK_JP	  	18 
#define  BIG_DO	  	19 
#define  TROPHY_CE	20 

#define KO_GSEL_LOGO	10
#define KO_GSEL_1P	(KO_GSEL_LOGO+1)
#define KO_GSEL_2P	(KO_GSEL_LOGO+2)
#define KO_GSEL_3P	(KO_GSEL_LOGO+3)
#define KO_GSEL_4P	(KO_GSEL_LOGO+4)
#define KO_GSEL_OK	(KO_GSEL_LOGO+5)
#define KO_GSEL_OPTION	16
#define KO_GSEL_DATA	17
#define KO_GSEL_50CC	(10+8)
#define KO_GSEL_100CC	(10+9)
#define KO_GSEL_150CC	(10+10)
#define KO_GSEL_PRO	(10+11)

#define KO_CHECKER_FLAG	251

#define KO_PSEL_LOGO	42
#define KO_PSEL_MA	43
#define KO_PSEL_LU	44
#define KO_PSEL_PE	45
#define KO_PSEL_KI	46
#define KO_PSEL_YO	47
#define KO_PSEL_KA	48
#define KO_PSEL_WA	49
#define KO_PSEL_KU	50
#define KO_PSEL_OK	51
#define KO_PSEL_1P	52
#define KO_PSEL_2P	53
#define KO_PSEL_3P	54
#define KO_PSEL_4P	55

#define KO_MSEL_LEVEL	104
#define KO_MSEL_KCUP	83
#define KO_MSEL_FCUP	84
#define KO_MSEL_SCUP	85
#define KO_MSEL_SPCUP	86
#define KO_MSEL_OK	93
#define KO_MSEL_BRECORD	101
#define KO_MSEL_BLAP	102
#define KO_MSEL_CUP	103

#define KO_MSEL_MAP1	95
#define KO_MSEL_MAP2	(KO_MSEL_MAP1+1)
#define KO_MSEL_MAP3	(KO_MSEL_MAP1+2)
#define KO_MSEL_MAP4	(KO_MSEL_MAP1+3)

#define KO_MSEL_MAPMAN	100

//Analog
#define ANA_RIGHT       0x0100
#define ANA_LEFT        0x0200
#define ANA_DOWN        0x0400
#define ANA_UP          0x0800
#define ANA_UPRIGHT     0x0900
#define ANA_UPLEFT      0x0a00
#define ANA_DOWNRIGHT   0x0500
#define ANA_DOWNLEFT    0x0600

#define   TITLESEQUENCE   		0
#define   GAMESELECTSEQUENCE   	1
#define   KARTSELECTSEQUENCE   	2
#define   MAPSELECTSEQUENCE   	3
#define   RACESEQUENCE   		4
#define   RESULTSEQUENCE   		5 //TROPHY
#define   RECORDSEQUENCE   		6
#define   BOOTSEQUENCE   		7
#define   LOGOSEQUENCE   		8
#define   ENDINGSEQUENCE   		9 //Credits

#define KO_GAME_CUP	150
#define KO_GAME_CIRCUIT	(KO_GAME_CUP+1)
#define KO_GAME_CUT_UD	(KO_GAME_CUP+2)

//screen_mode
#define  FULL_SCREEN 		0
#define  UP_DOWN_SCREEN 	1
#define  RIGHT_LEFT_SCREEN 	2
#define  FOUR_PARTS_SCREEN 	3
#define  INITIALSCREEN   	0
#define  INITIALPLAYERNUMBER   2

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   DRAWING                                              //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

#define copymode	0
#define cycle1mode	1
#define cycle2mode	2

#define noflip 		0
#define xflip 		1
#define yflip 		2
#define xyflip 		3

#define	LOADNOPUSH	0
#define	LOADPUSH	1
#define	MULNOPUSH	2
#define	MULPUSH		3

/* Internal generalized combiner inputs */
#define COMBINED        0
#define TEXEL0          1
#define TEXEL1          2
#define PRIMITIVE       3
#define SHADE           4
#define ENVIRONMENT     5
#define CENTER          6
#define SCALE           7
#define COMBINED_ALPHA  8
#define TEXEL0_ALPHA    9
#define TEXEL1_ALPHA    10
#define PRIMITIVE_ALPHA 11
#define SHADE_ALPHA     12
#define ENV_ALPHA       13
#define LOD_FRACTION    14
#define PRIM_LOD_FRAC   15
#define NOISE           16
#define K4              17
#define K5              18
#define ONE             19
#define ZERO            20
#define UNKNOWN         21

#define	RM_TOMEI2(clk)					\
	AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP |	\
	FORCE_BL | ZMODE_XLU |CVG_X_ALPHA |					\
	GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


#define	RM_TOMEI1(clk)					\
	AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP |	\
	FORCE_BL | ZMODE_XLU |CVG_X_ALPHA |					\
	GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


#define	RM_TOMEI(clk)					\
	AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |		\
	CVG_X_ALPHA | FORCE_BL | \
	GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define IA_SURF(clk)					\
	AA_EN |Z_CMP | IM_RD | CVG_DST_CLAMP | FORCE_BL | ZMODE_XLU | CVG_X_ALPHA |\
	GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


#define	G_IA_SURF		IA_SURF(1)
#define	G_IA_SURF2		IA_SURF(2)

#define	G_RM_GOAST		RM_TOMEI(1)
#define	G_RM_GOAST2		RM_TOMEI(2)

#define	G_RM_GOAST_SURF		RM_TOMEI1(1)
#define	G_RM_GOAST_SURF2	RM_TOMEI1(2)

#define	G_RM_ZB_GOAST_SURF		RM_TOMEI2(1)
#define	G_RM_ZB_GOAST_SURF2	    RM_TOMEI2(2)

#define K_NORMAL 0
#define K_CLEAR 1
#define K_GRAYPR 2
#define K_INTA 3
#define K_MODECAENV 4
#define K_AFONT 5

#define  deg360       65536
#define  deg0         0
#define  deg1         182
#define  deg2         deg1*2
#define  deg3         deg1*3
#define  deg4         deg1*4
#define  deg5         910
#define  deg6         deg1*6
#define  deg7         deg1*7
#define  deg8         deg1*8
#define  deg9         deg1*9
#define  deg10        1820
#define  deg15        1820+901
#define  deg20        3640
#define  deg30        5461
#define  deg40        7281
#define  deg45        8192
#define  deg50        9102
#define  deg60        10922
#define  deg70        12743
#define  deg80        14563
#define  deg90        16384
#define  deg100       18204
#define  deg110       20024
#define  deg120       21845
#define  deg130       23665
#define  deg135       24576
#define  deg140       25486
#define  deg150       27306
#define  deg160       29127
#define  deg170       30947
#define  deg180       32768
#define  deg190       34588
#define  deg200       36408
#define  deg210       38229
#define  deg220       40049
#define  deg225       40960
#define  deg230       41870
#define  deg240       43690
#define  deg250       45511
#define  deg260       47331
#define  deg270       49152
#define  deg280       50972
#define  deg290       52792
#define  deg300       54613
#define  deg310       56433
#define  deg315       57344
#define  deg320       58254
#define  deg330       60074
#define  deg340       61895
#define  deg350       63715

//Simple Object Category
#define IBOX   	   12
#define FAKEIBOX   13

#define flag_color  	    0x0D000000 //8019F940
#define fire_txt  	        0x0D000200
#define vtx_flag  	        0x0D001390
#define pylon  	            0x0D001750
#define pylon0  	        0x0D001780
#define pylon1  	        0x0D001798
#define pylon2  	        0x0D0017B0
#define pylon3  	        0x0D0017C8
#define pylon4  	        0x0D0017E0
#define pylon5  	        0x0D0017F8
#define pylon6  	        0x0D001810
#define pylon7  	        0x0D001828
#define gfx_flag_back  	    0x0D001B68
#define front_flag  	    0x0D001B90
#define back_flag           0x0D001BD8
#define front_fog_flag      0x0D001C20
#define back_fog_flag  	    0x0D001C88
#define itemboxshadow_v  	0x0D001CE8 //801A1628 shadow vertex
#define itembox2_v  	    0x0D001D28 //801A1668 question mark & itembox vertex
#define hatena_txt  	    0x0D001EE8 //801A1828 question mark txt
#define gfx_itemboxshadow  	0x0D002EE8 //801A2828 shadow draw commands
#define gyaku_v  	        0x0D002F40 //801A2880 question mark fake ib vertex
#define itembox_grp_gyaku_hatena  	0x0D002F80 //801A28C0 draw command question mark fake ib (if deleted draws like outside ib)
#define itembox_grp_hatena  	0x0D003008 //801A2948   draw command question mark (if deleted draws like outside ib)
#define itembox_grp_box  	0x0D003090 //801A29D0 draw command outside
#define itembox_obj_b4  	0x0D0030F8 //801A2A38 draw commands pieces
#define itembox_obj_b3  	0x0D003128 //801A2A68
#define itembox_obj_b2  	0x0D003158 //801A2A98
#define itembox_obj_b1  	0x0D003188 //801A2AC8
#define itembox_obj_b5  	0x0D0031B8 //801A2AF8
#define itembox_obj_b6  	0x0D0031E8 //801A2B28
#define itembox_obj_b7  	0x0D003218 //801A2B58
#define itembox_obj_b8  	0x0D003248 //801A2B88
#define itembox_grp_all  	0x0D003278 //801A2BB8
#define itembox_model  	    0x0D003288 //801A2BC8
#define banana_v  	        0x0D003298
#define banana2_v  	        0x0D0032E8
#define banana2_txt  	    0x0D003348
#define banana3_txt  	    0x0D003B48
#define gfx_banana2  	    0x0D004B48
#define gfx_banana3  	    0x0D004BD8
#define tree_color  	    0x0D004C68
#define gshellcolor  	    0x0D004E38
#define tshellcolor  	    0x0D005038
#define shell_v  	        0x0D005238
#define gfx_rshell  	    0x0D0052B8
#define gfx_gshell  	    0x0D005338
#define gfx_gshell_reverse  0x0D005368
#define surf_on  	        0x0D005398
#define texedge_on  	    0x0D0053B0
#define fog_on_surf  	    0x0D0053C8
#define fog_on_texedge  	0x0D0053F0
#define fog_off  	        0x0D005418
#define vtx_ktile4x4  	    0x0D005430
#define vtx_ktile8x8  	    0x0D005470
#define vtx_ktile8x16  	    0x0D0054B0
#define vtx_num8x16_ia  	0x0D0054F0
#define vtx_black8x16_ia  	0x0D005530
#define vtx_num8x160_ia  	0x0D005570
#define vtx_ktile12x12  	0x0D0055B0
#define vtx_ktile12x16  	0x0D0055F0
#define vtx_num12x16_ia  	0x0D005630
#define vtx_black12x16_ia  	0x0D005670
#define vtx_ktile12x160  	0x0D0056B0
#define vtx_num12x160_ia  	0x0D0056F0
#define vtx_num12x192_ia  	0x0D005730
#define vtx_ktile16x16  	0x0D005770
#define vtx_ktile16x16xflip  	0x0D0057B0
#define vtx_kage16x16   	0x0D0057F0
#define vtx_num16x16_ia  	0x0D005830
#define vtx_black16x16_ia  	0x0D005870
#define vtx_leaf16x16  	    0x0D0058B0
#define vtx_smoke1  	    0x0D0058E0
#define vtx_smoke2  	    0x0D005920
#define vtx_num16x160_ia  	0x0D005960
#define vtx_ktile20x20  	0x0D0059A0
#define vtx_ktile24x24  	0x0D0059E0
#define vtx_ktile24x48  	0x0D005A20
#define vtx_ktile28x28  	0x0D005A60
#define vtx_ktile32x16  	0x0D005AA0
#define vtx_ktile32x32  	0x0D005AE0
#define vtx_ktile32x32xflip  	0x0D005B20
#define vtx_kage32x32  	    0x0D005B60
#define vtx_ktriangle32x32  	0x0D005BA0
#define vtx_ktriangle32x32_light  	0x0D005BD0
#define vtx_dosuntriangle32x32_light  	0x0D005C00
#define vtx_ktile40x32  	0x0D005C30
#define vtx_ktile40x40  	0x0D005C70
#define vtx_num48x16_ia  	0x0D005CB0
#define vtx_black48x16_ia  	0x0D005CF0
#define vtx_ktile48x40  	0x0D005D30
#define vtx_ktile48x40xflip  	0x0D005D70
#define vtx_ktile48x40_bl_2  	0x0D005DB0
#define vtx_ktile48x48  	0x0D005E30
#define vtx_ktile56x72_bl  	0x0D005EB0
#define vtx_jgm_t56x72_bl  	0x0D005F30
#define vtx_ktile64x32  	0x0D005FB0
#define vtx_haritile64x32_ia  	0x0D005FF0
#define vtx_ktile64x64_ia  	0x0D006030
#define vtx_shade_black64x64  	0x0D006070
#define vtx_ktile64x64_bl  	0x0D0060B0
#define vtx_ktile64x64xflip_bl  	0x0D006130
#define vtx_ktile64x64t_bl  	0x0D0061B0
#define vtx_ktile64x64x_bl  	0x0D006230
#define vtx_ktile64x64_bl_mr  	0x0D0062B0
#define vtx_ktile64x64_cutx  	0x0D0062F0
#define vtx_ktile64x64_pt  	0x0D006370
#define vtx_ktile64x96_bl  	0x0D0063F0
#define vtx_ktile64x96_ia8_pt  	0x0D0064B0
#define vtx_ktile72x48  	0x0D006530
#define vtx_ktile72x48_bl_a  	0x0D0065B0
#define vtx_ktile72x48_bl_b  	0x0D006630
#define vtx_ktile72x48_bl_c  	0x0D0066B0
#define vtx_ktile72x56_bl  	0x0D006730
#define vtx_ktile80x48  	0x0D0067B0
#define vtx_ktile96x16  	0x0D006830
#define vtx_white112x32_ia8  	0x0D006870
#define vtx_black112x32_ia8  	0x0D0068B0
#define vtx_ktile128x64_ia  	0x0D0068F0
#define kwsetTriangle  	0x0D006930
#define kwsetTile  	0x0D006940
#define kwsettile8x8  	0x0D006950
#define kwsettile8x16  	0x0D006968
#define kwsettile16x16  	0x0D006980
#define kwsettile16x16xflip  	0x0D006998
#define kwsetkage16x16  	0x0D0069B0
#define kwsettile32x16  	0x0D0069C8
#define kwsettile32x32  	0x0D0069E0
#define kwsettile32x32xflip  	0x0D0069F8
#define kwsetkage32x32  	0x0D006A10
#define kwsetsmoke1  	0x0D006A28
#define kwsetsmoke2  	0x0D006A40
#define a4_shadow  	0x0D006A58
#define ia8_hole  	0x0D006AD8
#define ABCDpal  	0x0D006ED8
#define ABCDidx  	0x0D006EF8
#define kwdraw_init  	0x0D0076F8
#define kwpolygon_init_common  	0x0D007780
#define kwpolygon_init  	0x0D0077A0
#define kwpolygon_slight_init  	0x0D0077D0
#define kwpolygon_tex_flight_init  	0x0D0077F8
#define kwpolygon_tex_slight_init  	0x0D007828
#define kwpolygon_iceblock_init  	0x0D007850
#define kwpolygon_icekage_init  	0x0D007878
#define kwshade_init  	0x0D0078A0
#define kwshadeline_init  	0x0D0078D0
#define kwtexture_rgba_common  	0x0D0078F8
#define kwtexture_rgba_pt_init  	0x0D007928
#define kwtexture_rgba_bl_init  	0x0D007948
#define kwtexture_rgba_xlu_pt_init  	0x0D007968
#define kwtexture_rgba_aa_pt_init  	0x0D007988
#define kwtexture_rgba_aa_bl_init  	0x0D0079A8
#define kwtexture_rgba_aa_zb_bl_init  	0x0D0079C8
#define kwtexture_rgba_xlu_aa_zb_bl_init  	0x0D0079E8
#define kwtexture_ia_common  	0x0D007A08
#define kwtexture_ia_pt_init  	0x0D007A40
#define kwtexture_ia_bl_init  	0x0D007A60
#define kwtexture_ia_aa_pt_init  	0x0D007A80
#define kwtexture_ia_aa_bl_init  	0x0D007AA0
#define kwtexture_ia_zb_pt_init  	0x0D007AC0
#define kwtexture_ia_zb_bl_init  	0x0D007AE0
#define kwtexture_ia_aa_zb_bl_init  	0x0D007B00
#define kwdraw_kage  	0x0D007B20
#define kwdraw_kage2  	0x0D007B98
#define kwdraw_hole  	0x0D007C10
#define kwtexture_ci8_common  	0x0D007C88
#define kwtexture_ci8_pt_init  	0x0D007CB8
#define kwtexture_ci8_bl_init  	0x0D007CD8
#define kwtexture_ci8_av_init  	0x0D007CF8
#define kwtexture_ci8_aa_pt_init  	0x0D007D18
#define kwtexture_ci8_aa_bl_init  	0x0D007D38
#define kwtexture_ci8_zb_bl_init  	0x0D007D58
#define kwtexture_ci8_aa_zb_bl_init  	0x0D007D78
#define kwtexture_ci8_aa_zb_pt_init  	0x0D007D98
#define kwtexture_ci8_xlu_pt_init  	0x0D007DB8
#define kwtexture_ci8_xlu_bl_init  	0x0D007DD8
#define kwtexture_ci8_xlu_zb_pt_init  	0x0D007DF8
#define kwtexture_ci8_xlu_zb_bl_init  	0x0D007E18
#define kwtexture_ci8_xlu_aa_pt_init  	0x0D007E38
#define kwtexture_ci8_xlu_aa_bl_init  	0x0D007E58
#define kwtexture_ci8_xlu_aa_zb_pt_init  	0x0D007E78
#define kwtexture_ci8_xlu_aa_zb_bl_init  	0x0D007E98
#define kwsprite_finish  	0x0D007EB8
#define kwsprite_rgba_common  	0x0D007ED8
#define kwsprite_rgba_pt_init  	0x0D007EF8
#define kwsprite_rgba_bl_init  	0x0D007F18
#define kwsprite_rgba_xlu_pt_init  	0x0D007F38
#define kwsprite_rgba_xlu_bl_init  	0x0D007F58
#define kwsprite_rgba_aa_bl_init  	0x0D007F78
#define kwsprite_rgba_xlu_aa_bl_init  	0x0D007F98
#define kwsprite_ia_common  	0x0D007FB8
#define kwsprite_ia_pt_init  	0x0D007FE0
#define kwsprite_ia_bl_init  	0x0D008000
#define kwsprite_ci8_common  	0x0D008020
#define kwsprite_ci8_pt_init  	0x0D008040
#define kwsprite_ci8_bl_init  	0x0D008060
#define kwprint_init  	0x0D008080
#define kwchangecopymode  	0x0D008108
#define kwchange1cyclemode  	0x0D008120
#define kwchange2cyclemode  	0x0D008138
#define itemtbl_gp  	0x0D008150
#define itemtbl_egp  	0x0D008470
#define itemtbl_vs2  	0x0D008790
#define itemtbl_vs3  	0x0D008858
#define itemtbl_vs4  	0x0D008984
#define itemtbl_battle  	0x0D008B14
#define effect_vtx1_white  	0x0D008B78
#define vtx_sq1  	0x0D008BB8
#define vtx_sq2  	0x0D008BF8
#define vtx_sq3  	0x0D008C38
#define tri_set  	0x0D008C78
#define speffect_tex_RGBA_on  	0x0D008C90
#define speffect_toumei_RGBA_on  	0x0D008CD8
#define speffect_tex_RGBAgoast_on  	0x0D008D10
#define speffect_tex_RGBIA_on  	0x0D008D58
#define equip_disp  	0x0D008DA0
#define speffect_toumei_IA_before  	0x0D008DB8
#define speffect_toumei_IA16X16_after  	0x0D008DF8
#define speffect_toumei_IA32X32_after  	0x0D008E20
#define speffect_toumei1_IA32X32_after  	0x0D008E48
#define speffect_toumei2_IA32X32_after  	0x0D008E70
#define speffect_i_matrix  	0x0D008E98
#define act_pt_dummy  	0x0D008F18
#define act_pt_mario  	0x0D008F28
#define act_pt_dirt  	0x0D008F80
#define act_pt_castle  	0x0D008FB8
#define act_pt_obake  	0x0D009058
#define act_pt_maze  	0x0D0090B8
#define act_pt_snow  	0x0D0090F8
#define act_pt_beach  	0x0D009158
#define act_pt_peach  	0x0D009188
#define act_pt_luigi  	0x0D0091E8
#define act_pt_farm  	0x0D009210
#define act_pt_highway  	0x0D009238
#define act_pt_sabaku  	0x0D009260
#define act_pt_ice  	0x0D009280
#define act_pt_rainbow  	0x0D0092C8
#define act_pt_wario  	0x0D009310
#define act_pt_jungle  	0x0D0093C0
#define speed_straight_km  	0x0D009418
#define speed_curve_km  	0x0D009568
#define speed_biri_km  	0x0D0096B8
#define speed_out_km  	0x0D009808
#define spmeter  	0x0D009958
#define hari  	0x0D00A558
#define lap88moji  	0x0D00A958
#define lap88  	0x0D00AB58
#define lapmoji  	0x0D00AD58
#define lap1  	0x0D00B158
#define lap2  	0x0D00B558
#define lap3  	0x0D00B958
#define total  	0x0D00BD58
#define TIME  	0x0D00C158
#define TIME0123  	0x0D00C558
#define brank  	0x0D00D258
#define srank  	0x0D015258
#define orderpal  	0x0D017258
#define orderidx  	0x0D017458
#define numpal  	0x0D019458
#define numidx  	0x0D019658
#define num_spal  	0x0D019E58
#define num_sidx  	0x0D01A058
#define pframe  	0x0D01A2D8
#define pmapal  	0x0D01A4D8
#define plupal  	0x0D01A6D8
#define ppepal  	0x0D01A8D8
#define pkipal  	0x0D01AAD8
#define pyopal  	0x0D01ACD8
#define pdopal  	0x0D01AED8
#define pwapal  	0x0D01B0D8
#define pkupal  	0x0D01B2D8
#define pbombpal  	0x0D01B4D8
#define pmaidx  	0x0D01B6D8
#define pluidx  	0x0D01BAD8
#define ppeidx  	0x0D01BED8
#define pkiidx  	0x0D01C2D8
#define pyoidx  	0x0D01C6D8
#define pdoidx  	0x0D01CAD8
#define pwaidx  	0x0D01CED8
#define pkuidx  	0x0D01D2D8
#define pbombidx  	0x0D01D6D8
#define ib_nothingpal  	0x0D01DED8
#define ib_bananapal  	0x0D01E0D8
#define ib_bananaspal  	0x0D01E2D8
#define ib_msh1pal  	0x0D01E4D8
#define ib_msh2pal  	0x0D01E6D8
#define ib_msh3pal  	0x0D01E8D8
#define ib_mshcpal  	0x0D01EAD8
#define ib_shl_ppal  	0x0D01ECD8
#define ib_tellesapal  	0x0D01EED8
#define ib_shl_gpal  	0x0D01F0D8
#define ib_shls_gpal  	0x0D01F2D8
#define ib_shl_rpal  	0x0D01F4D8
#define ib_shls_rpal  	0x0D01F6D8
#define ib_starpal  	0x0D01F8D8
#define ib_thunderpal  	0x0D01FAD8
#define ib_imboxpal  	0x0D01FCD8
#define ib_nothingidx  	0x0D01FED8
#define ib_bananaidx  	0x0D0203D8
#define ib_bananasidx  	0x0D0208D8
#define ib_msh1idx  	0x0D020DD8
#define ib_msh2idx  	0x0D0212D8
#define ib_msh3idx  	0x0D0217D8
#define ib_mshcidx  	0x0D021CD8
#define ib_shl_pidx  	0x0D0221D8
#define ib_tellesaidx  	0x0D0226D8
#define ib_shl_gidx  	0x0D022BD8
#define ib_shls_gidx  	0x0D0230D8
#define ib_shl_ridx  	0x0D0235D8
#define ib_shls_ridx  	0x0D023AD8
#define ib_staridx  	0x0D023FD8
#define ib_thunderidx  	0x0D0244D8
#define ib_imboxidx  	0x0D0249D8
#define jgm_s1pal  	0x0D024ED8
#define jgm_s2pal  	0x0D0250D8
#define jgm_s3pal  	0x0D0252D8
#define jgm_gpal  	0x0D0254D8
#define jgm_l2pal  	0x0D0256D8
#define jgm_lfpal  	0x0D0258D8
#define jgm_rpal  	0x0D025AD8
#define jgm_tpal  	0x0D025CD8
#define ci8_signal_colpal  	0x0D025ED8
#define ci8_signal_index  	0x0D0260D8
#define rgba_happa  	0x0D028DD8
#define rgba_leaf  	0x0D0291D8
#define a4_snow  	0x0D0293D8
#define a8_smoke  	0x0D029458
#define bombkartidx  	0x0D029858
#define bombkartpal  	0x0D02A858
#define bombtire  	0x0D02AA58
#define spk  	0x0D02AC58
#define ko_fire  	0x0D02BC58
#define sline  	0x0D02CC58
#define markmario  	0x0D02CCD8
#define markluigi  	0x0D02CD58
#define markyoshi  	0x0D02CDD8
#define markkinopio  	0x0D02CE58
#define markdonkey  	0x0D02CED8
#define markwario  	0x0D02CF58
#define markpeach  	0x0D02CFD8
#define markkoopa  	0x0D02D058
#define markCOM  	0x0D02D0D8
