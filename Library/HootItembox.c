#include "MainInclude.h" 

/*README:
CALL IN INITIAL SETUP: //////////////////////////////////////////////////////////////////////////
	change_ib_crash_col();

MOVE INTO BUILD: ////////////////////////////////////////////////////////////////////////////////
	//ITEMBOX
	.org 0x10C5D0 //in 802A2F34 display_object2
	JAL display_itembox_hack
	.org 0x10C5E0
	JAL display_itembox_hack

	.org 0x10C5C0 //in 802A2F34 display_object2
	JAL display_fake_itembox_hack

	.org 0x10CC40 //in 802A3548 object_strategy
	JAL move_itembox_hook
	.org 0x10CC60
	JAL move_fake_itembox_hook
	.org 0x10CC50
	JAL move_special_itembox_hook

	.org 0x10830C // in 8029EC88 add_object_buffer <- called when objects set
	JAL set_object_buffer_hook

MOVE INTO BUILD IF YOU WANT TO TO REMOVE THE MENU ITEMBOX CURSOR: ////////////////////////////////
	//REMOVE ITEMBOX MENU CURSOR
	.org 0x0A29A4 //in ?
	NOP
	.org 0x0A2B04 //in ?
	NOP
	.org 0x0A38D8 //in ?
	NOP
	.org 0x0A5120 //in ?
	NOP
	.org 0x0A6320 //in ?
	NOP
	.org 0x0A6C0C //in ?
	NOP
	.org 0x0A6F10 //in ?
	NOP
	.org 0x0A7280 //in ?
	NOP
	
COMPILE ERROR?
	#define G_CCMUX_3	3 
	#define G_CCMUX_4	4
	#define G_ACMUX_3       3 
	#define G_ACMUX_4       4

*/

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   DEFINES                                              //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

    #define G_CCMUX_3	3 
	#define G_CCMUX_4	4
	#define G_ACMUX_3   3 
	#define G_ACMUX_4   4

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   VARS                                                 //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

float ib_blender_scale = 4.0f;//0.003f;

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   TEXTURES                                             //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

u64 ib_beta_Itembox64x2_ci4[] = {
	0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0111111111111111, 0x1111111111111110, 0x0111111111111111, 0x1111111111111110, 
	0x0122222222222222, 0x2222222222222210, 0x0122222222222222, 0x2222222222222210, 0x0122222222222222, 0x2222222222222210, 0x0122222222222222, 0x2222222222222210, 
	0x0122222222334566, 0x6655442222222210, 0x0122222222223789, 0x9987332222222210, 0x01222222223a5566, 0x6666542222222210, 0x0122222222219999, 0x9999972222222210, 
	0x0122222223566656, 0x5566664422222210, 0x0122222222899999, 0x9999997322222210, 0x0122222233666655, 0x4556665422222210, 0x012222222a999977, 0xa789999a22222210, 
	0x0122222245665422, 0x2233666622222210, 0x0122222238999722, 0x222a999822222210, 0x0122222245665422, 0x2233566622222210, 0x01222222a9998222, 0x2222899932222210, 
	0x012222224566a322, 0x2222566633222210, 0x0122222279991222, 0x22227999a2222210, 0x0122222245664322, 0x2222566633222210, 0x01222222a9997222, 0x22228999b2222210, 
	0x012222223a552222, 0x2244666622222210, 0x0122222231082222, 0x223a999922222210, 0x0122222233342222, 0x2245666522222210, 0x0122222233332222, 0x2279999722222210, 
	0x0122222222222222, 0x456666a322222210, 0x0122222222222222, 0x3899991222222210, 0x0122222222222223, 0x5566653322222210, 0x012222222222222b, 0x8999973222222210, 
	0x0122222222222245, 0x6655322222222210, 0x0122222222222238, 0x9998a22222222210, 0x0122222222222245, 0x6654222222222210, 0x01222222222222a9, 0x9983222222222210, 
	0x0122222222222255, 0x6643222222222210, 0x0122222222222279, 0x9912222222222210, 0x0122222222222245, 0x6633222222222210, 0x01222222222222a9, 0x99a2222222222210, 
	0x012222222222223a, 0x5522222222222210, 0x0122222222222231, 0x9822222222222210, 0x0122222222222233, 0x4322222222222210, 0x012222222222223b, 0x3322222222222210, 
	0x0122222222222233, 0x4423222222222210, 0x0122222222222222, 0x3322222222222210, 0x012222222222223a, 0x5532222222222210, 0x01222222222222b8, 0x08a3222222222210, 
	0x0122222222222266, 0x6654222222222210, 0x0122222222222289, 0x9993222222222210, 0x0122222222222266, 0x6654222222222210, 0x0122222222222299, 0x999a222222222210, 
	0x0122222222222255, 0x6653222222222210, 0x0122222222222289, 0x9903222222222210, 0x0122222222222245, 0x6633222222222210, 0x01222222222222a8, 0x99a2222222232210, 
	0x0122222222222222, 0x2222222222222210, 0x0122222222222222, 0x2222222222222210, 0x0122222222222222, 0x2222222222222210, 0x0122222222222222, 0x2222222222222210, 
	0x0111111111111111, 0x1111111111111110, 0x0111111111111111, 0x1111111111111110, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
	0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0111111111111111, 0x1111111111111110, 0x0000000000000000, 0x0000000000000000, 
	0x0122222222222222, 0x2222222222222210, 0x0000000000000000, 0x0000000000000000, 0x0122222222222222, 0x2222222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x012222222222cdee, 0xeeefbb2222222210, 0x0000000000000000, 0x0000000000000000, 0x012222222221eeee, 0xeeeeed2222222210, 0x0000000000000000, 0x0000000000000000, 
	0x0122222222feeeee, 0xeeeeeefb22222210, 0x0000000000000000, 0x0000000000000000, 0x012222222deeeefd, 0xcdfeeeec22222210, 0x0000000000000000, 0x0000000000000000, 
	0x01222222bfeeed22, 0x222ceeef22222210, 0x0000000000000000, 0x0000000000000000, 0x01222222ceeefb22, 0x2222feeeb2222210, 0x0000000000000000, 0x0000000000000000, 
	0x01222222deeed222, 0x2222feeeb2222210, 0x0000000000000000, 0x0000000000000000, 0x01222222deeed222, 0x2222feeeb2222210, 0x0000000000000000, 0x0000000000000000, 
	0x0122222221ef3222, 0x22bceeee22222210, 0x0000000000000000, 0x0000000000000000, 0x0122222222bb2222, 0x22deeeef22222210, 0x0000000000000000, 0x0000000000000000, 
	0x0122222222222222, 0xbfeeee1222222210, 0x0000000000000000, 0x0000000000000000, 0x012222222222222b, 0xfeeeef2222222210, 0x0000000000000000, 0x0000000000000000, 
	0x01222222222222bf, 0xeeefb22222222210, 0x0000000000000000, 0x0000000000000000, 0x01222222222222ce, 0xeeeb222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x01222222222222de, 0xeed2222222222210, 0x0000000000000000, 0x0000000000000000, 0x01222222222222de, 0xeeb2222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x01222222222222b1, 0xef32222222222210, 0x0000000000000000, 0x0000000000000000, 0x012222222222222b, 0x3b22222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x0122222222222222, 0xbb22222222222210, 0x0000000000000000, 0x0000000000000000, 0x01222222222222c1, 0xefc2222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x01222222222222fe, 0xeeeb222222222210, 0x0000000000000000, 0x0000000000000000, 0x01222222222222ee, 0xeeec222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x01222222222222fe, 0xee0b222222222210, 0x0000000000000000, 0x0000000000000000, 0x01222222222222cf, 0xeeb2222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x0122222222222222, 0x2222222222222210, 0x0000000000000000, 0x0000000000000000, 0x0122222222222222, 0x2222222222222210, 0x0000000000000000, 0x0000000000000000, 
	0x0111111111111111, 0x1111111111111110, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
	
};

u64 ib_beta_Itembox64x2_ci4_pal_rgba16[] = {
	0xc6316b5b00012043, 0x6803b0d1f0137b43, 0xbd09f6c751c90945, 0x02cd13531fab159f, 
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   VERTEX                                               //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

Vtx ib_beta_Cube_mesh_vtx_0[24] = {
	{{{1, 1, -1},0, {1010, 1012},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1, 1, -1},0, {-11, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1, 1, 1},0, {-15, 2028},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1, 1, 1},0, {1006, 2032},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1, -1, 1},0, {1021, -17},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{1, 1, 1},0, {-18, -13},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-1, 1, 1},0, {-15, 1024},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-1, -1, 1},0, {1025, 1020},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-1, -1, 1},0, {994, -16},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, 1, 1},0, {997, 1025},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, 1, -1},0, {2038, 1021},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, -1, -1},0, {2035, -19},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, -1, -1},0, {-17, 2033},{0x0, 0x81, 0x0, 0xFF}}},
	{{{1, -1, -1},0, {1022, 2033},{0x0, 0x81, 0x0, 0xFF}}},
	{{{1, -1, 1},0, {1022, 995},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-1, -1, 1},0, {-17, 995},{0x0, 0x81, 0x0, 0xFF}}},
	{{{1, -1, -1},0, {2036, 1007},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{1, 1, -1},0, {2033, -18},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{1, 1, 1},0, {1006, -15},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{1, -1, 1},0, {1009, 1010},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-1, -1, -1},0, {-14, 1015},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-1, 1, -1},0, {1026, 1015},{0x0, 0x0, 0x81, 0xFF}}},
	{{{1, 1, -1},0, {1026, -11},{0x0, 0x0, 0x81, 0xFF}}},
	{{{1, -1, -1},0, {-14, -11},{0x0, 0x0, 0x81, 0xFF}}},
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   TRIS (DRAW COMMAND)                                  //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

Gfx ib_beta_Cube_mesh_tri_0[] = {
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};

//////////////////////////////////////

Gfx ib_beta_Cube_mesh_tri_0_Part1[] = {
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList()
};

Gfx ib_beta_Cube_mesh_tri_0_Part2[] = {
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 4, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList()
};

Gfx ib_beta_Cube_mesh_tri_0_Part3[] = {
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 8, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList()
};

Gfx ib_beta_Cube_mesh_tri_0_Part4[] = {
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 12, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList()
};

Gfx ib_beta_Cube_mesh_tri_0_Part5[] = {
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 16, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList()
};

Gfx ib_beta_Cube_mesh_tri_0_Part6[] = {
	gsSPVertex(ib_beta_Cube_mesh_vtx_0 + 20, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList()
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   MESH & MATERIAL                                      //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

Gfx mat_ib_beta_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ib_beta_Itembox64x2_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 15),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, ib_beta_Itembox64x2_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 512),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPEndDisplayList(),
};

Gfx mat_revert_ib_beta_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx ib_beta_Cube_mesh[] = {
	gsSPDisplayList(mat_ib_beta_f3d_material),
	gsSPDisplayList(ib_beta_Cube_mesh_tri_0),
	gsSPDisplayList(mat_revert_ib_beta_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};


//////////////////////////////////////

Gfx ib_beta_Cube_mesh_Part1[] = {
	gsSPDisplayList(mat_ib_beta_f3d_material),
	gsSPDisplayList(ib_beta_Cube_mesh_tri_0_Part1),
	gsSPDisplayList(mat_revert_ib_beta_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

Gfx ib_beta_Cube_mesh_Part2[] = {
	gsSPDisplayList(mat_ib_beta_f3d_material),
	gsSPDisplayList(ib_beta_Cube_mesh_tri_0_Part2),
	gsSPDisplayList(mat_revert_ib_beta_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

Gfx ib_beta_Cube_mesh_Part3[] = {
	gsSPDisplayList(mat_ib_beta_f3d_material),
	gsSPDisplayList(ib_beta_Cube_mesh_tri_0_Part3),
	gsSPDisplayList(mat_revert_ib_beta_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

Gfx ib_beta_Cube_mesh_Part4[] = {
	gsSPDisplayList(mat_ib_beta_f3d_material),
	gsSPDisplayList(ib_beta_Cube_mesh_tri_0_Part4),
	gsSPDisplayList(mat_revert_ib_beta_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

Gfx ib_beta_Cube_mesh_Part5[] = {
	gsSPDisplayList(mat_ib_beta_f3d_material),
	gsSPDisplayList(ib_beta_Cube_mesh_tri_0_Part5),
	gsSPDisplayList(mat_revert_ib_beta_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

Gfx ib_beta_Cube_mesh_Part6[] = {
	gsSPDisplayList(mat_ib_beta_f3d_material),
	gsSPDisplayList(ib_beta_Cube_mesh_tri_0_Part6),
	gsSPDisplayList(mat_revert_ib_beta_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   MOVEMENT                                             //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void set_object_buffer_hook (Object *obj,FVector pos,SVector angle,FVector velo,short category)
{
	set_object_buffer(obj,pos,angle,velo,category);

	if(category == FAKEIBOX)
	{
		obj->fparam = 0.35f*ib_blender_scale; //OG: D_802B95F4 0.35f
	}
}

void move_itembox_hook(Object *obj)
{
	if(obj->sparam!=3) move_itembox(obj);


    // if(!SaveGame.Set.Hud.Itembox) return;

	// obj->angle[0] = 0;		//OG: obj->angle[0]+=deg1*1;
	// 						//OG: obj->angle[1]-=deg1*2; 182*2=364 0x16C
	// obj->angle[2] = 0;		//OG: obj->angle[2]+=deg1*1;
}

float ibY;

void move_fake_itembox_hook (Object *obj)
{
	float   dd,dx,dy,dz;
	
	move_fake_itembox(obj);


	switch(obj->sparam)
	{
	case 0: //Y POS FIX
			dx = GlobalPlayer[(int)obj->velocity[0]].position[0] - obj->position[0];
			dy = GlobalPlayer[(int)obj->velocity[0]].position[1] - obj->position[1];
			dz = GlobalPlayer[(int)obj->velocity[0]].position[2] - obj->position[2];
			dd = Sqrtf(dx*dx+dy*dy+dz*dz)/10.0f;
			dy /= dd;	
			obj->position[1] = GlobalPlayer[(int)obj->velocity[0]].position[1] - dy -4.0f;//(dy*obj->fparam) -5.0f;//ibY;// -2.5f;//OG: -dy -1.0f;
			
			//RADIUS FIX
			obj->radius=5.5f*0.35f;
			break; 
	case 1: //SCALE AFTER DROP FIX
			if(obj->fparam < 1.0f*ib_blender_scale)
			{
				obj->fparam += 0.05f;	
				///obj->position[1] += obj->fparam;
			}	   	   
 			else if(obj->fparam > 1.0f*ib_blender_scale)	   
			{
				//obj->position[1] -= obj->fparam;
				obj->fparam = 1.0f*ib_blender_scale;
				//obj->position[1] += obj->fparam;
			}

			//RADIUS FIX
			obj->radius=5.5f*1.0f;
			break;
	}

	//ROTATION
	// obj->angle[0] = 0; 				//OG: obj->angle[0]-=deg1*1;
	// obj->angle[1] -= 0x16C + 0x16C;	//OG: obj->angle[1]+=deg1*2; 182*2=364 0x16C
	// obj->angle[2] = 0;				//OG: obj->angle[2]-=deg1*1;

	// loadFont();
	// printFloat(30,30,ibY);
	// printFloat(30,40,obj->fparam);
	// printFloat(30,50,obj->position[1]);

	// if (GlobalController[4]->ButtonPressed &BTN_DUP)
	// 	ibY += 0.5f;
	// if (GlobalController[4]->ButtonPressed &BTN_DDOWN)
	// 	ibY -= 0.5f;

	// if (GlobalController[4]->ButtonPressed &BTN_DRIGHT)
	// 	obj->position[1] += 0.5f;
	// if (GlobalController[4]->ButtonPressed &BTN_DLEFT)
	// 	obj->position[1] -= 0.5f;
}

void move_special_itembox_hook(Object *obj)
{
	move_special_itembox(obj);
	

    // if(!SaveGame.Set.Hud.Itembox) return;

	// obj->angle[0] = 0;		//OG: obj->angle[0]+=deg1*1;
	// 						//OG: obj->angle[1]-=deg1*2; 
	// obj->angle[2] = 0;  	//OG: obj->angle[2]+=deg1*1;    
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   ITEMBOX CRUSH ANIM                                   //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void change_ib_crash_col(void) //USE OG TRIS FOR CRASH ANIM (THIS WILL CHANGE THE MENU CURSOR TOO!)
{
	// switch(SaveGame.Set.Hud.Itembox)
    //     {
    //         case 1:
    //             for(int i=0, j=0; i<24; ) //DYE WITH 2 ALTERNATING COLORS
    //             {
    //                 *(uint*)(0x801A16B4 + i*0x10) = 0xFFFF0099;
    //                 *(uint*)(0x801A16E4 + i*0x10) = 0x99990099;

    //                 if(j == 2){j=0, i+=4;}
    //                 else{i++; j++;}
    //             }
    //             break;

    //         default: //OG
    //             *(uint*)(0x801A16B4) = 0x0000FF99;
    //             *(uint*)(0x801A16C4) = 0x00FFFF99;
    //             *(uint*)(0x801A16D4) = 0x00FF0099;
    //             *(uint*)(0x801A16E4) = 0x00FFFF99;
    //             *(uint*)(0x801A16F4) = 0xFF820099;

    //             *(uint*)(0x801A1704) = 0x00FF0099;
    //             *(uint*)(0x801A1714) = 0xFF820099;
    //             *(uint*)(0x801A1724) = 0xFFFF0099;
    //             *(uint*)(0x801A1734) = 0x00FF0099;
    //             *(uint*)(0x801A1744) = 0xFFFF0099;

    //             *(uint*)(0x801A1754) = 0x0000FF99;
    //             *(uint*)(0x801A1764) = 0x00FF0099;
    //             *(uint*)(0x801A1774) = 0x0000FF99;
    //             *(uint*)(0x801A1784) = 0xFFFF0099;
    //             *(uint*)(0x801A1794) = 0xFF000499;

    //             *(uint*)(0x801A17A4) = 0x00FFFF99;
    //             *(uint*)(0x801A17B4) = 0x0000FF99;
    //             *(uint*)(0x801A17C4) = 0xFF000499;
    //             *(uint*)(0x801A17D4) = 0xFF820099;
    //             *(uint*)(0x801A17E4) = 0x00FFFF99;

    //             *(uint*)(0x801A17F4) = 0xFF000499;
    //             *(uint*)(0x801A1804) = 0xFFFF0099;
    //             *(uint*)(0x801A1814) = 0xFF820099;
    //             *(uint*)(0x801A1824) = 0xFF000499;
    //             break;
    //     }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   DRAWING                                              //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void display_fake_itembox_hack (Camera *camera,Object *obj)
{
	SVector   angle; 
	FVector   vct;
	AffineMtx aff;
	AffineMtx aff2;
	float pp,pp2,scale;
    float distance;
	//FVector     kageposition;
	//SVector     kageangle;

	distance=check_display_range(camera->camera_pos,obj->position,camera->camera_direction[1],50*50,screen_view_angle[camera-camera1],1000*1000);
  	if(distance<0) {out_of_screen(camera,obj); return;}

	if(obj->position[1]>((float)maximum_y)+800.0f) {out_of_screen(camera,obj); return;} // 
	if(obj->position[1]<((float)minimum_y)-800.0f) {out_of_screen(camera,obj); return;} // 

  	on_screen(camera,obj);

  	//HATENA	
	angle[0]=0;            
	angle[1]=obj->angle[1];
	angle[2]=0;            

	create_modeling_matrix(aff,obj->position,angle);
	scaling_matrix(aff,obj->fparam);

	if(obj->sparam!=2)
	{
		if((obj->sparam != 0) && (distance<100000)) //CLOSE VIEW
		{
	     	/*kageangle[0]=0; //CAN BE USED BUT DOESN'T LOOK THAT GOOD ON STEEP TERRAIN ATM 
	     	kageangle[1]=obj->angle[1];
	     	kageangle[2]=0;
	     	kageposition[0]=obj->position[0];
	     	kageposition[1]=obj->position[1] - (8.3f); //FINETUNE
	     	kageposition[2]=obj->position[2];
		    create_modeling_matrix(aff,kageposition,kageangle);
			scaling_matrix(aff,obj->fparam);
		    if(set_matrix(aff,LOADNOPUSH)==FALSE)  return;
      	   	gSPDisplayList(GraphPtr++, ibshadow_Gem_mesh); //gfx_itemboxshadow */

			/*kageangle[0]=0;
			kageangle[1]=obj->angle[1]*2;
			kageangle[2]=0;
			kageposition[0]=obj->position[0];
	     	kageposition[1]=obj->position[1];
			kageposition[2]=obj->position[2];
		    create_modeling_matrix(aff,kageposition,kageangle);
			//scaling_matrix(aff,obj->fparam);
		    if(set_matrix(aff,LOADNOPUSH)==FALSE)  return;
			gSPDisplayList(GraphPtr++, gfx_itemboxshadow);//itembox_grp_hatena*/
		}
		
		create_modeling_matrix(aff,obj->position,obj->angle);
		scaling_matrix(aff,obj->fparam);
		if(set_matrix(aff,LOADNOPUSH)==FALSE)  return;
		gSPClearGeometryMode(GraphPtr++,G_LIGHTING);
		gDPSetCombineMode(GraphPtr++,G_CC_MODULATERGB, G_CC_MODULATERGB);
		
		// 	if(((obj->angle[1])<deg15)&&((obj->angle[1])>0))
		// {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
		// else if(((obj->angle[1])>deg1*150)&&((obj->angle[1])<deg1*165))
		// {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
		// else if(((obj->angle[1])>deg1*80)&&((obj->angle[1])<deg1*95))
		// {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
		// else if(((obj->angle[1])>deg1*280)&&((obj->angle[1])<deg1*295))
		// {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
		// else
		// {
		// 	gDPSetBlendMask(GraphPtr++,0xff);
		// 	gDPSetRenderMode(GraphPtr++,G_RM_ZB_CLD_SURF,G_RM_ZB_CLD_SURF2);
		// }

		gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
			  
    	    gSPSetGeometryMode(GraphPtr++,G_ZBUFFER);
			gSPDisplayList(GraphPtr++, &ib_beta_Cube_mesh); //itembox_grp_box

	}
	else //explosion	
	{
		    gSPClearGeometryMode(GraphPtr++,G_LIGHTING);
            gSPClearGeometryMode(GraphPtr++, G_CULL_BACK);
            
			//gDPSetBlendMask(GraphPtr++,0xff);
				gDPSetCombineMode(GraphPtr++,G_CC_MODULATERGB, G_CC_MODULATERGB);

            pp=(float)obj->counter;
			pp2=(float)obj->counter;
			//pp=(float) (obj->counter / 2);
			//pp2=(float) (obj->counter / 2);

            create_modeling_matrix(aff,obj->position,obj->angle);
            if(pp<10.0f) scale=ib_blender_scale;
            else		 scale=ib_blender_scale-(pp-10.0f)*0.2f;//*0.5f;
            scaling_matrix(aff,scale);
            
            //if(obj->counter&01)
            //{gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
            //else
            //{gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_XLU_INTER,G_RM_AA_ZB_XLU_INTER);}
				gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
				gSPSetGeometryMode(GraphPtr++,G_ZBUFFER);

            vct[0]=0.0f*pp2;
            vct[1]=2.0f*pp2;
            vct[2]=0.0f*pp2;//1.0f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part2);							    		     		         
            vct[0]=0.0f*pp2;//0.8f*pp2;
            vct[1]=2.3f*pp2;
            vct[2]=0.0f*pp2;//0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part5);							    		     		         
            vct[0]=0.0f*pp2;//0.8f*pp2;
            vct[1]=1.2f*pp2;
            vct[2]=0.0f*pp2;//-0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part3);							    		     		         
        
            if(!(obj->counter&01))
            {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
            else
            {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_XLU_INTER,G_RM_AA_ZB_XLU_INTER);}
        
            vct[0]=0.0f*pp2;
            vct[1]=1.8f*pp2;
            vct[2]=0.0f*pp2;//-1.0f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part6);							    		     		         
            vct[0]=0.0f*pp2;//-0.8f*pp2;
            vct[1]=0.6f*pp2;
            vct[2]=0.0f*pp2;//-0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part1);							    		     		         
            vct[0]=0.0f*pp2;//-0.8f*pp2;
            vct[1]=2.0f*pp2;
            vct[2]=0.0f*pp2;//0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part4);			

            gSPSetGeometryMode(GraphPtr++, G_CULL_BACK);
	}
}

void display_itembox_hack (Camera *camera,Object *obj)
{
	FVector     vct;
	FVector     kageposition;
	SVector     kageangle;
	float       pp,pp2,scale;
	float 		aff[4][4];
	float 		aff2[4][4];
    float       distance;

  	distance = check_display_range(camera->camera_pos,obj->position,camera->camera_direction[1],0,screen_view_angle[camera-camera1],2000*2000);
  
  	if(distance<0) return;
  	if(distance>600000) return;

		if((obj->sparam==2)&&(distance<100000)) //CLOSE VIEW
		{
	     	kageangle[0]=0;
	     	kageangle[1]=obj->angle[1];
	     	kageangle[2]=0;
	     	kageposition[0]=obj->position[0];
	     	kageposition[1]=obj->fparam+2.0f;
	     	kageposition[2]=obj->position[2];
		    create_modeling_matrix(aff,kageposition,kageangle);
			//ScalingMatrix(aff, ib_blender_scale);
		    if(set_matrix(aff,LOADNOPUSH)==FALSE)  return;
      	   	gSPDisplayList(GraphPtr++, gfx_itemboxshadow); //gfx_itemboxshadow

			// kageangle[1]=obj->angle[1]*2;
	     	// kageposition[1]=obj->position[1];
		    // create_modeling_matrix(aff,kageposition,kageangle);
			// ScalingMatrix(aff, ib_blender_scale);
		    // if(set_matrix(aff,LOADNOPUSH)==FALSE)  return;
			// gSPDisplayList(GraphPtr++, ibhatena_Gem_mesh);//itembox_grp_hatena
		}

		// if(obj->sparam==5) //FOR SPECIAL IB
        // {
		//     create_modeling_matrix(aff,obj->position,obj->angle);
		// 	ScalingMatrix(aff, ib_blender_scale);
		//     if(set_matrix(aff,LOADNOPUSH)==FALSE)  return;
		//     gSPDisplayList(GraphPtr++, ibhatena_Gem_mesh);//itembox_grp_hatena
		// }

		if(obj->sparam!=3)
		{
			 create_modeling_matrix(aff,obj->position,obj->angle);
			 ScalingMatrix(aff, ib_blender_scale);
		    if(set_matrix(aff,LOADNOPUSH)==FALSE)  return;
    	    gSPClearGeometryMode(GraphPtr++,G_LIGHTING);
    	    gDPSetCombineMode(GraphPtr++,G_CC_MODULATERGB, G_CC_MODULATERGB);
  	        
			//   if(((obj->angle[1])<deg15)&&((obj->angle[1])>0))
	        // {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
  	        // else if(((obj->angle[1])>deg1*150)&&((obj->angle[1])<deg1*165))
	        // {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
  	        // else if(((obj->angle[1])>deg1*80)&&((obj->angle[1])<deg1*95))
	        // {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
  	        // else if(((obj->angle[1])>deg1*280)&&((obj->angle[1])<deg1*295))
	        // {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
	        // else
            // {
       	    //     gDPSetBlendMask(GraphPtr++,0xff);
 	        //     gDPSetRenderMode(GraphPtr++,G_RM_ZB_CLD_SURF,G_RM_ZB_CLD_SURF2);
  	        // }
			gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
			  
    	    gSPSetGeometryMode(GraphPtr++,G_ZBUFFER);
			gSPDisplayList(GraphPtr++, &ib_beta_Cube_mesh); //itembox_grp_box
		}
		else
		{
            gSPClearGeometryMode(GraphPtr++,G_LIGHTING);
            gSPClearGeometryMode(GraphPtr++, G_CULL_BACK);
            
			//gDPSetBlendMask(GraphPtr++,0xff);
				gDPSetCombineMode(GraphPtr++,G_CC_MODULATERGB, G_CC_MODULATERGB);

            pp=(float)obj->counter;
			pp2=(float)obj->counter;
			//pp=(float) (obj->counter / 2);
			//pp2=(float) (obj->counter / 2);

            create_modeling_matrix(aff,obj->position,obj->angle);
            if(pp<10.0f) scale=ib_blender_scale;
            else		 scale=ib_blender_scale-(pp-10.0f)*0.2f;//*0.5f;
            scaling_matrix(aff,scale);
            
            //if(obj->counter&01)
            //{gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
            //else
            //{gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_XLU_INTER,G_RM_AA_ZB_XLU_INTER);}
				gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
				gSPSetGeometryMode(GraphPtr++,G_ZBUFFER);

            vct[0]=0.0f*pp2;
            vct[1]=2.0f*pp2;
            vct[2]=0.0f*pp2;//1.0f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part2);							    		     		         
            vct[0]=0.0f*pp2;//0.8f*pp2;
            vct[1]=2.3f*pp2;
            vct[2]=0.0f*pp2;//0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part5);							    		     		         
            vct[0]=0.0f*pp2;//0.8f*pp2;
            vct[1]=1.2f*pp2;
            vct[2]=0.0f*pp2;//-0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part3);							    		     		         
        
            if(!(obj->counter&01))
            {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);}
            else
            {gDPSetRenderMode(GraphPtr++,G_RM_AA_ZB_XLU_INTER,G_RM_AA_ZB_XLU_INTER);}
        
            vct[0]=0.0f*pp2;
            vct[1]=1.8f*pp2;
            vct[2]=0.0f*pp2;//-1.0f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part6);							    		     		         
            vct[0]=0.0f*pp2;//-0.8f*pp2;
            vct[1]=0.6f*pp2;
            vct[2]=0.0f*pp2;//-0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part1);							    		     		         
            vct[0]=0.0f*pp2;//-0.8f*pp2;
            vct[1]=2.0f*pp2;
            vct[2]=0.0f*pp2;//0.5f*pp2;
            translate_matrix(aff,aff2,vct);
            if(set_matrix(aff2,LOADNOPUSH)==FALSE)  return;
            gSPDisplayList(GraphPtr++, ib_beta_Cube_mesh_Part4);			

            gSPSetGeometryMode(GraphPtr++, G_CULL_BACK);
		}

	gSPTexture(GraphPtr++,65535, 65535,0, 0, 1);
}