.n64
.open "ROM\Mario Kart 64 (U) [!].z64", "ROM\ProjectR.z64", 0

.definelabel PAYLOAD_ROM, 		filesize("ROM\Mario Kart 64 (U) [!].z64")
.definelabel PAYLOAD_RAM, 		0x80400000
.definelabel DMA_FUNC,    		0x80001158
.definelabel RAM_END,           org(EndRAMData)
.definelabel DMA_MAX_LENGTH,    org(EndRAMData) - org(StartRAMData)
.definelabel Printf, 			0x800D6420
.defineLabel romReader,         0xB0000000
.defineLabel rgba16Items,       0x00D00000
.defineLabel mio0buffer,        0x80300000
.defineLabel mio0Cache,         0x805A0000
.defineLabel P1MDItemBankID,    0x80165F58
.defineLabel g_playerCount2,     0x800EC538
.defineLabel g_RNG2,            0x800DC54F

.align 0x10
.include "..\library\GameVariables\NTSC\GameOffsets.asm"
.align 0x10
.include "..\library\OKHeader.asm"
//.align 0x10
//.include "..\library\GameVariables\NTSC\StatsOffsets.asm"
//.align 0x10
//.include "..\library\GameVariables\NTSC\OKAssembly.asm"
//.align 0x10
//.include "Header.asm"


///////////////////////////////////////////////////////////////////////////////////////////////////
//MARK: - ROM CHANGES:                                                                           //
//MARK: -                                   -SEO                                                 //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
//seohaine item stuff
.align 0x10
.org rgba16Items
.incbin "...\CORE\Data\blackBox.bin"         // 0
.incbin "...\CORE\Data\banana.bin"           // 1
.incbin "...\CORE\Data\bananaBunch.bin"      // 2
.incbin "...\CORE\Data\greenShell.bin"       // 3
.incbin "...\CORE\Data\tripleGreenShell.bin" // 4
.incbin "...\CORE\Data\redShell.bin"         // 5
.incbin "...\CORE\Data\tripleRedShells.bin"  // 6
.incbin "...\CORE\Data\blueShell.bin"        // 7
.incbin "...\CORE\Data\lightning.bin"        // 8
.incbin "...\CORE\Data\MK64RfakeItem.bin"                       // 9
.incbin "...\CORE\Data\star.bin"             // a
.incbin "...\CORE\Data\boo.bin"              // b
.incbin "...\CORE\Data\MK64Rmushroom.bin"                       // c
.incbin "...\CORE\Data\MK64RdoubleMushroom.bin"                 // d
.incbin "...\CORE\Data\MK64RtripleMushroom.bin"                 // e
.incbin "...\CORE\Data\MK64RgoldMushroom.bin"                   // f
.incbin "...\CORE\Data\MK64Rfeather.bin"                        // 10

//MIO1 flag END FILE for MULT MIO0 decoder
.ascii "MIO1"




.org 0xE50F0 // 0x800E44F0 item gfx f3dex display table
.word 0x805A0000,0x805A0A00,0x805A1400,0x805A1E00
.word 0x805A2800,0x805A3200,0x805A3C00,0x805A4600
.word 0x805A5000,0x805A5A00,0x805A6400,0x805A6E00
.word 0x805A7800,0x805A8200,0x805A8C00,0x805A9600
.word 0x805AA000

.org 0x4F2A4 // 0x8004E6A4 item palette index
or r0, r0, r0

.org 0x4F2AC // 0x8004E6AC rgba 16 sprite func.
jal 0x8004CC54
ori a1, r0, 0x20

//#ITEM ROULETTER SEQUENCER AND TIMER
.org 0x7C1A4 // 0x8007B5A4 roulette speed 1
addiu t9, r0, 0x0001
addiu t0, r0, 0x0001 //roulette sequence 1

.org 0x7C1D0 // 0x8007B5D0 roulette speed 2
addiu t6, r0, 0x0004
addiu t1, r0, 0x0001 // roulette sequence 2

.org 0x7C1FC // 0x8007B5FC roulette speed 3
addiu t2, r0, 0x0005
addiu t3, r0, 0x0001 // roulette sequence 3


.org 0x4F270 // 0x8004E670 black box keep
or r0, r0, r0



//seohaine hooks
.org 0x73B18 // 0x80072F18
J CustomRoulette
nop
nop

.org 0x11C764 // 0x802B3154
J NewItemsFlags

.org 0x7C244 // 0x8007B644
J ItemsRNG
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   -HOOT                                                //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

//MAP NAMES:
.org 0x0A1254 //Result pts
JAL DispOB_result_point_hack
.org 0x0A1244 //result time
JAL DispOB_result_time_hack
.org 0x0A1274 //Don't show map name 3p GP
NOP 
.org 0x0A57A0 //Pause menu GP
JAL DispOB_pause_gp_hack

//ITEMBOX:
.org 0x10830C // in 8029EC88 add_object_buffer <- called when objects set
JAL set_object_buffer_hook
.org 0x10C5D0 //in 802A2F34 display_object2
JAL display_itembox_hack
.org 0x10C5E0
JAL display_itembox_hack
//FAKE ITEMBOX:
.org 0x10C5C0 //in 802A2F34 display_object2
JAL display_fake_itembox_hack
.org 0x10CC60
JAL move_fake_itembox_hook
.org 0x10A974 //fix fake ib growth override in move itembox
B 0x10A9FC
    
//GP Intro: 
//Hook initial_game JALS in initial funcs
.org 0x125204 //in initialize_sequence
JAL initial_game_hack
.org 0x003738 //in initial_race_sequence
JAL initial_game_hack
    //result call
.org 0x125204//in initial_result_sequence
JAL initial_game_hack   

.org 0x0297BC //no init drive-in
B	0x0297EC

.org 0x03AEBC //correct positions
li    $at, 0x00000000
.org 0x03AF04 
li    $at, 0x00000000
.org 0x03AF58
li    $at, 0x00000000
.org 0x03AFB0 
li    $at, 0x00000000
.org 0x03B008
li    $at, 0x00000000
.org 0x03B060 
li    $at, 0x00000000
.org 0x03B0B8 
li    $at, 0x00000000
.org 0x03B110 
li    $at, 0x00000000

//Racestart circuit_level -> cupnumber fix
.org 0x03AB74 //mario GP 1
lui   $t6, hi(0x800DC544)
lb    $t6, lo(0x800DC544)($t6)
.org 0x03B624 //mario GP 2
lui   $t6, hi(0x800DC544)
lb    $t6, lo(0x800DC544)($t6)
.org 0x03AA04 //make init line-up
lui   $t5, hi(0x800DC544)
.org 0x03AA4C
lb    $t5, lo(0x800DC544)($t5)
.org 0x03AA04 //Make rank every time
lui   $t5, hi(0x800DC544)
.org 0x03AA4C
lb    $t5, lo(0x800DC544)($t5)

//GP FINISH NEXT MAP DECIDE
.org 0x0F8230 //in finish_zoom
JAL check_finish_race_hack


//TSEL:
.org 0x0A8964 //in doOBJBlock | disable r-button show time
B 0x0A897C

.org 0x0A04C8 //Static press start
NOP
.org 0x0A04E4
NOP

//GSEL:
.org 0x0B10D8 //GSel Controller
JAL gselControler_hook

.org 0x0A8DE4 //Object HUD elements   
JAL DispOBJBlock_hook

//MSEL:
.org 0xe7e08 //backlight pos
.word 0x009D0070, 0x00000000, 0x01280081, 0x00000000
.word 0x009D0084, 0x00000000, 0x01280095, 0x00000000
.word 0x009D0098, 0x00000000, 0x012800A9, 0x00000000
.word 0x009D00AC, 0x00000000, 0x012800BD, 0x00000000

.org 0x0B1108 //in 800B0350 UpdateController
JAL mselControler_hook

// .org 0x0A8B74 //map tex change
// NOP
// .org 0x0A8B94
// NOP
.org 0x0A8B94
JAL DOB_msel_anime_map2_hook
.org 0x0A8B74
JAL DOB_msel_name_hook

//CUSTOM flash rectangle vs map select var
.org 0x0A9730
LUI	S6, 0x800E
.org 0x0A9744
ADDIU	S6, S6, 0x720C
//same for maps
.org 0x0ABF80
LUI	V0, 0x800E
.org 0x0ABF8C
ADDIU	V0, V0, 0x720C


//HUD:

//CHARACTER PANEL IN GP
.org 0x050EAC
.word 0x3C01C110 //MOVE RANK NUMBER

//LAP
.org 0x059BEC
JAL DisplayLapHook
.org 0x05A0D0
JAL DisplayLapHook
.org 0x059BF4
JAL ChangeLapTimeTexturesHook

//TIME
.org 0x059BE4
JAL DisplayTimeHook
.org 0x059F78
JAL DisplayTimeHook
.org 0x05A010
JAL DisplayTimeHook
.org 0x05A0C8
JAL DisplayTimeHook

//ITEM ROULETTE
.org 0x07C7A4 //kwchart_itemboxanm JAL kwanm_roulette
JAL kwanm_roulette_HACK

.org 0x059BC8 //ITEMBOX BIG
JAL kwdisplay_itembox_hack
.org 0x059FD8
JAL kwdisplay_itembox_hack
.org 0x05A070
JAL kwdisplay_itembox_hack
.org 0x05A0D8
JAL kwdisplay_itembox_hack

.org 0x05A290 //ITEMBOX SMALL
JAL kwdisplay_itemboxs_hack

.org 0x05A908 //responsible for hud at racesatart
JAL kwcheck_opening_start_HOOK
.org 0x05B5D8 //HUD ANIM P1
nop

//ITEM DECIDE PLAYER            //RM05: COMMENT IN WHEN ITEM PROBABILITES DONE!
.org 0x07BB60 
JAL kwgetitem_sub_HACK

//EXECUTE ITEM
.org 0x11C890
JAL execute_item_hook

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   -OVERKART                                            //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

//original hook placement
.org 0x34BC //RAM address 0x800028BC
J GlobalCustomCode
NOP

//title screen hook
.org 0x957D0 //RAM address 0x80094BD0
J CustomCodeTitleScreen
NOP

.org 0x2B30
J PrintMenuHook
NOP

//1p
.org 0x2214
J race1P
NOP

//2p
.org 0x269C
J race2P
NOP

.org 0x24F4
J race2PLR
NOP

//mp
.org 0x28F8
J raceMP
NOP

.org 0x17EC //RAM address 0x80000BEC
LUI a0, 0x8040 //RAM address
LUI a1, hi(PAYLOAD_ROM)
ADDIU a1, a1, lo(PAYLOAD_ROM) //DMA from ROM address 0x00C00000
LUI a2, hi(DMA_MAX_LENGTH)
JAL DMA_FUNC
ADDIU a2, lo(DMA_MAX_LENGTH)
J OriginalBootFunction
NOP


.org 0x10CB44
J FreeDraw

.headersize PAYLOAD_RAM - PAYLOAD_ROM
.org PAYLOAD_RAM



















StartRAMData:

///////////////////////////////////////////////////////////////////////////////////////////////////
//MARK: - RAM CHANGES                                                                            //
//MARK: -                                   -OVERKART                                            //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

.align 0x10
OriginalBootFunction: //we overwrite this when DMAing our code therefore, make sure it gets ran or the game wont boot
LUI    T6, 0x8030
LUI    AT, 0x1FFF
ORI    AT, AT, 0xFFFF
ADDIU t6, t6, 0x9F80
AND t7, t6, at
LUI at, 0x8015
J 0x800012AC //jump back to where execution should be on boot
SW t7, 0x02B4 (at)

/*
.align 0x10                                                                               //SEO EDIT
OriginalBootFunction: //we overwrite this when DMAing our code
//therefore, make sure it gets ran or the game wont boot

//seohaine multifile params...                                                          
lui t0, hi(romReader)
lui a1, hi(rgba16Items)
addu a1, t0, a1    // rom MIO0 files init
lui a0, hi(mio0buffer)  // ram MIO0 buffer
lui a2, hi(mio0Cache)   // ram cache
jal multMIO0Decoder  // MULT MIO0 DECODER
ori a3, r0, 0x0010     // # items

LUI    T6, 0x8030
LUI    AT, 0x1FFF
ORI    AT, AT, 0xFFFF
ADDIU t6, t6, 0x9F80
AND t7, t6, at
LUI at, 0x8015
J 0x800012AC //jump back to where execution should be on boot
SW t7, 0x02B4 (at)
*/



.align 0x10
CustomCodeTitleScreen:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp)
JAL	0x80095574 //run what we overwrote with our hook
NOP
JAL TitleMenuHandler
NOP
LW ra, 0x001C (sp)
ADDIU sp, sp, 0x20
J 0x80094BD8 //jump back to where we were
NOP
NOP

.align 0x10
GlobalCustomCode:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL allRun
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
J 0x8000286C //tells the game where to jump back to, dont remove
NOP


.align 0x10
race1P:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL gameCode
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
LUI a0, 0x800E
LHU a0, 0xC520 (a0)
LUI a1, 0x800E
J 0x8000161C
NOP

.align 0x10
race2P:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL gameCode
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
LUI t3, 0x800E
LW t3, 0xC5E8 (t3)
J 0x80001AA4
NOP

.align 0x10
race2PLR:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL gameCode
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
LUI t3, 0x800E
LW t3, 0xC5E8 (t3)
J 0x800018FC
NOP


.align 0x10
raceMP:
ADDIU sp, sp, -0x20
SW ra, 0x001C (sp) //push ra to the stack
NOP
JAL gameCode
NOP
LW ra, 0x001C (sp) //pop ra from the stack
ADDIU sp, sp, 0x20
LUI v0, 0x800E
LW v0, 0xC5E8 (v0)
J 0x80001D00
NOP

.align 0x10
PrintMenuHook:
JAL PrintMenuFunction
NOP
J 0x80001F64
LW ra, 0x14 (sp)

.align 0x10
FreeDraw:
JAL DrawStuff
NOP
LW ra, 0x24 (sp)
LW s0, 0x18 (sp)
LW s1, 0x1C (sp)
LW s2, 0x20 (sp)
JR ra
ADDIU sp, sp, 0x98

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   -HOOT                                                //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

.align 0x10

ItemFeatherTex:
.import "Data\\feather.ci8.png.RAW"
.align 0x10

ItemFeatherPal:
.import "Data\\feather.ci8.png.PALETTE"
.align 0x10

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   -SEO                                                 //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
//seohaine multifile decoder
.align 0x10
multMIO0Decoder:
addiu sp, sp, -0x20
sw ra, 0x1C (sp)
or s0, a1, r0
or s2, a0, r0
or s1, a2, r0
or s3, a3, r0
or t0, r0, r0
addiu s0, s0, 0x0004
@@decoderLoop:
ori s4, r0, 0x0004
lui at, 0x4D49
ori at, at, 0x4F30        //  MIO0 checker

addiu t1, at, 0x0001
@@MIO0Flag:
beql t0, t1,@@MIO1Flag      // custom MIO1 for determining file END
addiu s0, s0, 0x0004

lw t0, 0x0000 (s0)
addiu s0, s0, 0x0004
bnel t0, at,@@MIO0Flag
addiu s4, s4, 0x0004
@@MIO1Flag:
lui at, 0x0FFF
ori at, at, 0xFFFF       
and a1, s0, at        // removes 0B and convert to rom add.
addiu a1, a1, 0xFFFC
subu a1, a1, s4
or a0, s2, r0
jal DMA
or a2, s4, r0             // MIO0 length
or a0, s2, r0
jal decodeMIO0
or a1, s1, r0
or s1, a1, r0
bnez s3,@@decoderLoop
addiu s3, s3, 0xFFFF
lw ra, 0x1C (sp)
jr ra
addiu sp, sp, 0x20


//SEOHAINE roulette
.align 0x10
CustomRoulette:
lui t3, 0x8015
ori t3, t3, 0xAA40
bne t3, sp,@@itemFlag
sltiu at, t9, 0x0011
bnezl at,@@itemFlagCap
lw ra, 0x001C (sp)
@@returnFunc:
j 0x80072F24
nop
@@itemFlagCap:
@@defaultFlag:
j 0x80072F78
nop
@@itemFlag:
slt	at, a3, t9
beqzl at,@@defaultFlag
lw ra, 0x001C (sp)
beq r0, r0,@@returnFunc
nop


///SEO NEW ITEMS FLAGS///

.align 0x10
NewItemsFlags:
jal	0x800910E4
nop

addiu sp, sp, -0x20
sw ra, 0x1C (sp)
sw s6, 0x18 (sp)
sw s7, 0x14 (sp)
sw v0, 0x10 (sp)
sw v1, 0x0C (sp)
swc1 f0, 0x08 (sp)
swc1 f1, 0x04 (sp)



or s6, a1, r0     // push a1
or s7, a2, r0     // push a2
lui a1, hi (g_PlayerStructTable)
ori a1, a1, lo (g_PlayerStructTable)
jal playerVars
ori a2, r0, 0x0DD8
  
or a3, t6, r0    // t6 players item ram bank
or t5, t7, r0    // t7 players model bank  
or t3, t9, r0    // t9 players timer buffer

//PlayerFlag return stuff//
// v0 players struct
// v1 players controller
// t6 players item ram bank
// t7 players model bank
// t8 cpus item ram bank
// t9 players timer buffer
////////////////////////////
lhu t0, 0x0006 (v1)
andi t9, t0, 0x2000
beqz t9,@@ZbuttonFlag
lhu v0, 0x0000 (a0) // kart flag
andi t9, v0, 0x4000
beqz t9,@@cpuFlag
lhu a2, 0x0010 (a0)


addiu at, r0, 0x0010     // #feather ID
bne a2, at,@@featherFlag
ori t0, r0, 0x1000
sh t0, 0x000E (a0)      // jump 

sb r0, 0x0005 (a3)
beq r0, r0,@@featherEnd
@@featherFlag:

@@ZbuttonFlag:
@@cpuFlag:
@@featherEnd:
lw ra, 0x1C (sp)
lw s6, 0x18 (sp)
lw s7, 0x14 (sp)
lw v0, 0x10 (sp)
lw v1, 0x0C (sp)
lwc1 f0, 0x08 (sp)
lwc1 f1, 0x04 (sp)
J 0x802B315C
addiu sp, sp, 0x20


///SEO ITEM RNG///

.align 0x10
ItemsRNG:
addiu sp, sp, -0x20
sw ra, 0x1C (sp)
sw a0, 0x10 (sp)
sb v0, 0x00D2 (t4)
lbu t2, 0x00A7 (t4)
addiu at, r0, 0x0006
bne t2, at,@@rouletteTimeFlag
lui a0, hi (g_RNG2)
lbu t0, lo (g_RNG2) (a0) //RNG seed val
addu t0, t0, v0
sltiu at, t0, 0x40
bnez at,@@featherRNG
sltiu at, t0, 0x55
beqz at,@@featherRNG
nop
ori v0, r0, 0x10
@@featherRNG:
sb v0, 0x00A3 (t4)
sb v0, 0x00D2 (t4)
@@rouletteTimeFlag:
lw a0, 0x10 (sp)
lw ra, 0x1C (sp)
J 0x8007B64C
addiu sp, sp, 0x20










/////SEO GLOBAL FUNCTIONS///////

.align 0x10
playerVars:
addiu sp, sp, -0x40
sw s0, 0x3C (sp)
sw s1, 0x38 (sp)
sw s2, 0x34 (sp)
sw s3, 0x30 (sp)
sw s4, 0x2C (sp)
sw s5, 0x28 (sp)
sw t0, 0x24 (sp)
sw t1, 0x20 (sp)
sw t2, 0x1C (sp)
sw t3, 0x18 (sp)
sw t4, 0x14 (sp)
sw t5, 0x10 (sp)
sw a0, 0x0C (sp)
sw a1, 0x08 (sp)
sw a2, 0x04 (sp)
sw at, 0x00 (sp)
lui s2, hi (g_CpuItemStructTable) 
ori s3, s2, 0x1EE8
ori s4, s2, lo (g_CpuItemStructTable) // 0x801642D8

lui s0, hi (g_playerCount2) // 0x800EC538
lbu s0, lo (g_playerCount2) (s0)
sltiu at, s0, 0x0003
beqzl at,@@gameModeFlag
addiu s2, s2, 0x01C0        // VS/BATTLE flag
@@gameModeFlag:

ori s2, s2, lo (P1MDItemBankID) //0x80165F58

lui s0, hi (g_PlayerStructTable) 
ori s1, s0, lo (g_PlayerInputTable) // 0x800F6910
ori s0, s0, lo (g_PlayerStructTable) // 0x800F6990

lui s5, 0x805F

or t0, r0, r0
or t1, r0, r0
or t2, r0, r0
or t3, r0, r0
or t4, r0, r0
or t5, r0, r0

@@playerVarsLoop:
addu v0, s0, t0     // v0 players struct
addu v1, s1, t1     // v1 players controller
addu t6, s2, t2     // t6 players item ram bank
addu t7, s3, t3     // t7 players model bank
addu t8, s4, t4     // t8 cpus item ram bank
addu t9, s5, t5     // t9 players timer buffer

addiu t0, t0, 0x0DD8
addiu t1, t1, 0x0010
addiu t2, t2, 0x0070
addiu t3, t3, 0x00E0
addiu t4, t4, 0x0010
addiu t5, t5, 0x0002

bne a0, a1,@@playerVarsLoop
addu a1, a1, a2
lw s0, 0x3C (sp)
lw s1, 0x38 (sp)
lw s2, 0x34 (sp)
lw s3, 0x30 (sp)
lw s4, 0x2C (sp)
lw s5, 0x28 (sp)
lw t0, 0x24 (sp)
lw t1, 0x20 (sp)
lw t2, 0x1C (sp)
lw t3, 0x18 (sp)
lw t4, 0x14 (sp)
lw t5, 0x10 (sp)
lw a0, 0x0C (sp)
lw a1, 0x08 (sp)
lw a2, 0x04 (sp)
lw at, 0x00 (sp)
jr ra
addiu sp, sp, 0x40




*/

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                     -FILES RAM                                         //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

.include "LibraryLight.asm"
.align 0x10
.importobj "Main.o"
.align 0x10







EndRAMData:
.headersize 0

///////////////////////////////////////////////////////////////////////////////////////////////////
//MARK: -FILES ROM                                                                               //
//MARK: -                                       HOOT                                             //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

.align 0x10



.close
