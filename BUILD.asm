.n64
.open "ROM\Mario Kart 64 (U) [!].z64", "ROM\ProjectR.z64", 0

.definelabel PAYLOAD_ROM, 		  filesize("ROM\Mario Kart 64 (U) [!].z64")
.definelabel PAYLOAD_RAM, 		  0x80400000
.definelabel DMA_FUNC,    		  0x80001158
.definelabel RAM_END,           org(EndRAMData)
.definelabel DMA_MAX_LENGTH,    org(EndRAMData) - org(StartRAMData)
.definelabel Printf, 			      0x800D6420
.defineLabel romReader,         0xB0000000
.defineLabel rgba16Items,       0x00D00000
.defineLabel mio0buffer,        0x80300000
.defineLabel mio0Cache,         0x805A0000

.include "..\library\GameVariables\NTSC\GameOffsets.asm"
.include "..\library\GameVariables\NTSC\StatsOffsets.asm"
.include "..\library\GameVariables\NTSC\OKAssembly.asm"
.include "Header.asm"



//seohaine item stuff
.align 0x10
.org rgba16Items
.incbin "mk64_ItemBlast\RBA16\compressed\blackBox.bin"         // 0
.incbin "mk64_ItemBlast\RBA16\compressed\banana.bin"           // 1
.incbin "mk64_ItemBlast\RBA16\compressed\bananaBunch.bin"      // 2
.incbin "mk64_ItemBlast\RBA16\compressed\greenShell.bin"       // 3
.incbin "mk64_ItemBlast\RBA16\compressed\tripleGreenShell.bin" // 4
.incbin "mk64_ItemBlast\RBA16\compressed\redShell.bin"         // 5
.incbin "mk64_ItemBlast\RBA16\compressed\tripleRedShells.bin"  // 6
.incbin "mk64_ItemBlast\RBA16\compressed\blueShell.bin"        // 7
.incbin "mk64_ItemBlast\RBA16\compressed\lightning.bin"        // 8
.incbin "mk64R\RGBA16\MK64RfakeItem.bin"                       // 9
.incbin "mk64_ItemBlast\RBA16\compressed\star.bin"             // a
.incbin "mk64_ItemBlast\RBA16\compressed\boo.bin"              // b
.incbin "mk64R\RGBA16\MK64Rmushroom.bin"                       // c
.incbin "mk64R\RGBA16\MK64RdoubleMushroom.bin"                 // d
.incbin "mk64R\RGBA16\MK64RtripleMushroom.bin"                 // e
.incbin "mk64R\RGBA16\MK64RgoldMushroom.bin"                   // f
.incbin "mk64R\RGBA16\MK64Rfeather.bin"                        // 10

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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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



.align 0x10
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


//seohaine roulette
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


.include "LibraryLight.asm"


.align 0x10
.importobj "Main.o"
.align 0x10
EndRAMData:




.headersize 0
.close
