#include "../library/MainInclude.h"
#include "../library/HootItembox.c"

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   INFO                                                 //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////
//#define DEBUG

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   INITIAL BOOT                                         //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void InitialSetup(void) //RUNS ONCE AT BOOT
{

	//Game Select
	for (int i=0; i<4; i++) //Don't show menu rest
	{
		*(uint*) (0x8019bf80 + 4*i) = 0;
		*(uint*) (0x8019c034 + 4*i) = 0;
		*(uint*) (0x8019c084 + 4*i) = 0;
	}
		
	for (int i=0; i<10; i++)
		*(uint*) (0x8019bfd0 + 4*i) = 0;

	*(uint*) 0x800A9DE0	= 0; //Nop move selected after select
	*(uint*) 0x800A7E3C = 0; //NOP move others after selected

	*(uint*) 0x800F2B60 = 0; //Max game mode entries
	
	*(uint*) 0x800A7EB4 = 0; //Pic anim
	*(uint*) 0x800A7E84 = 0; //Pic move

	//Player Select
	*(uint*) 0x800A01D4 = 0; //Name plates
	*(uint*) 0x800A7EF8 = 0; //Nop move out anim

	//MAP Select
	uint mapTextsMonk[4*6] = //FORMAT 0x02004C8C: {1, 0, gTextureTitleLuigiRaceway,     140, 18, 157, 112, 0x0, 0}
	{
		0x00010000, 0x0B002500, 0x008C0012, 0x009D0070,
		0x00000000, 0x00010000, 0x0B002A00, 0x008C0012,
		0x009D0084, 0x00000000, 0x00010000, 0x0B005000,
		0x008C0012, 0x009D0098, 0x00000000, 0x00010000,
		0x0B003400, 0x008C0012, 0x009D00AC, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
	};

	for (int i=0; i<4*6; i++)
	{
		*(uint*) (0x8019C55C + i*0x4) = mapTextsMonk[i];
	}
	uint mapPic1[11] = //FORMAT 0x02004C64: {0, 0, gCoursePreviewMarioRaceway, 128, 78, 23, 112, 0x1e3d, 0},
	{
		0x00000000, 0x0A0779E8, 0x0080004E, 0x00000000,
		0x31570000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000
	};

	uint mapPic2[11] = 
	{
		0x00000000, 0x0A07AB40, 0x0080004E, 0x00000000,
		0x2A240000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000
	};

	uint mapPic3[11] = 
	{
		0x00000000, 0x0A0903F0, 0x0080004E, 0x00000000,
		0x25C70000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000
	};

	uint mapPic4[11] = 
	{
		0x00000000, 0x0A080644, 0x0080004E, 0x00000000,
		0x26AD0000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000
	};

	for (int i=0; i<11; i++)
	{
		*(uint*) (0x8019953C + i*0x4) = mapPic1[i];
		*(uint*) (0x80199564 + i*0x4) = mapPic2[i];
		*(uint*) (0x801994EC + i*0x4) = mapPic3[i];
		*(uint*) (0x801995B4 + i*0x4) = mapPic4[i];
	}

	startupSwitch = 35;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   GRAND PRIX                                           //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////


void initial_game_hack (void) //8003D080,code,initial_game
{
    imageinit();

    if (sequence_mode == 5) {result_pos();} 
	else 
	{
		reset_pos();
	}
	
    if (demo_flag == 0) 
	{
        switch (screen_mode) 
		{
            case FULL_SCREEN:
                switch (g_gameMode) 
				{
                    case GP:
						initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 8, 0);			
						break;

                    case TT:
                        initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], grid_z[7], GlobalPlayer[0].direction[1], 1, 0);
                        break;

                    default:
                        initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 10, 0);
                        break;
                }
                break;

            case RIGHT_LEFT_SCREEN:
            case UP_DOWN_SCREEN:
                switch (g_gameMode) 
				{
                    case GP:
                        initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 1, 0);
                        initial_camera(GlobalPlayer[1].position[0], GlobalPlayer[1].position[1], GlobalPlayer[1].position[2], GlobalPlayer[1].direction[1], 1, 1);
                        break;

                    case BA:
                        initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 9, 0);
                        initial_camera(GlobalPlayer[1].position[0], GlobalPlayer[1].position[1], GlobalPlayer[1].position[2], GlobalPlayer[1].direction[1], 9, 1);
                        break;

                    default:
                        initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 1, 0);
                        initial_camera(GlobalPlayer[1].position[0], GlobalPlayer[1].position[1], GlobalPlayer[1].position[2], GlobalPlayer[1].direction[1], 1, 1);
                        break;
                }
                break;

            case FOUR_PARTS_SCREEN:
                if (g_gameMode == BA) 
				{
                    initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 9, 0);
                    initial_camera(GlobalPlayer[1].position[0], GlobalPlayer[1].position[1], GlobalPlayer[1].position[2], GlobalPlayer[1].direction[1], 9, 1);
                    initial_camera(GlobalPlayer[2].position[0], GlobalPlayer[2].position[1], GlobalPlayer[2].position[2], GlobalPlayer[2].direction[1], 9, 2);
                    if (g_playerCount == 4) 
					{
					initial_camera(GlobalPlayer[3].position[0], GlobalPlayer[3].position[1], GlobalPlayer[3].position[2], GlobalPlayer[3].direction[1], 9, 3);
					}
                } 
				else 
				{
                    initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 1, 0);
                    initial_camera(GlobalPlayer[1].position[0], GlobalPlayer[1].position[1], GlobalPlayer[1].position[2], GlobalPlayer[1].direction[1], 1, 1);
                    initial_camera(GlobalPlayer[2].position[0], GlobalPlayer[2].position[1], GlobalPlayer[2].position[2], GlobalPlayer[2].direction[1], 1, 2);
                    if (g_playerCount == 4) 
					{
                    initial_camera(GlobalPlayer[3].position[0], GlobalPlayer[3].position[1], GlobalPlayer[3].position[2], GlobalPlayer[3].direction[1], 1, 3);
                    }
                }
                break;
        }
    } else 
	{
        switch (screen_mode) 
		{
            case 0:
                initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 3, 0);
                break;

            case 1:
            case 2:
                initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 3, 0);
                initial_camera(GlobalPlayer[1].position[0], GlobalPlayer[1].position[1], GlobalPlayer[1].position[2], GlobalPlayer[1].direction[1], 3, 1);
                break;

            case 3:
                initial_camera(GlobalPlayer[0].position[0], GlobalPlayer[0].position[1], GlobalPlayer[0].position[2], GlobalPlayer[0].direction[1], 3, 0);
                initial_camera(GlobalPlayer[1].position[0], GlobalPlayer[1].position[1], GlobalPlayer[1].position[2], GlobalPlayer[1].direction[1], 3, 1);
                initial_camera(GlobalPlayer[2].position[0], GlobalPlayer[2].position[1], GlobalPlayer[2].position[2], GlobalPlayer[2].direction[1], 3, 2);
                initial_camera(GlobalPlayer[3].position[0], GlobalPlayer[3].position[1], GlobalPlayer[3].position[2], GlobalPlayer[3].direction[1], 3, 3);
                break;
        }
    }

    
	
	switch (screen_mode) 
	{
        case 0:
            init_draw(&GlobalPlayer[0], camera1, 0, 0);
            init_draw(&GlobalPlayer[1], camera1, 1, 0);
            init_draw(&GlobalPlayer[2], camera1, 2, 0);
            init_draw(&GlobalPlayer[3], camera1, 3, 0);
            init_draw(&GlobalPlayer[4], camera1, 4, 0);
            init_draw(&GlobalPlayer[5], camera1, 5, 0);
            init_draw(&GlobalPlayer[6], camera1, 6, 0);
            init_draw(&GlobalPlayer[7], camera1, 7, 0);
			/*if(g_gameMode == GP)
			{
				init_draw(&GlobalPlayer[0], camera2, 0, 1);
				init_draw(&GlobalPlayer[1], camera2, 1, 1);
				init_draw(&GlobalPlayer[2], camera2, 2, 1);
				init_draw(&GlobalPlayer[3], camera2, 3, 1);
				init_draw(&GlobalPlayer[4], camera2, 4, 1);
				init_draw(&GlobalPlayer[5], camera2, 5, 1);
				init_draw(&GlobalPlayer[6], camera2, 6, 1);
				init_draw(&GlobalPlayer[7], camera2, 7, 1);
			}*/
            break;

        case 1:
        case 2:
            init_draw(&GlobalPlayer[0], camera1, 0, 0);
            init_draw(&GlobalPlayer[1], camera1, 1, 0);
            init_draw(&GlobalPlayer[2], camera1, 2, 0);
            init_draw(&GlobalPlayer[3], camera1, 3, 0);
            init_draw(&GlobalPlayer[4], camera1, 4, 0);
            init_draw(&GlobalPlayer[5], camera1, 5, 0);
            init_draw(&GlobalPlayer[6], camera1, 6, 0);
            init_draw(&GlobalPlayer[7], camera1, 7, 0);
            init_draw(&GlobalPlayer[0], camera2, 0, 1);
            init_draw(&GlobalPlayer[1], camera2, 1, 1);
            init_draw(&GlobalPlayer[2], camera2, 2, 1);
            init_draw(&GlobalPlayer[3], camera2, 3, 1);
            init_draw(&GlobalPlayer[4], camera2, 4, 1);
            init_draw(&GlobalPlayer[5], camera2, 5, 1);
            init_draw(&GlobalPlayer[6], camera2, 6, 1);
            init_draw(&GlobalPlayer[7], camera2, 7, 1);
            break;

        case 3:
			init_draw(&GlobalPlayer[0], camera1, 0, 0); //player / cameras camera1
			init_draw(&GlobalPlayer[1], camera1, 1, 0);
			init_draw(&GlobalPlayer[2], camera1, 2, 0);
			init_draw(&GlobalPlayer[3], camera1, 3, 0);
			init_draw(&GlobalPlayer[0], camera2, 0, 1);
			init_draw(&GlobalPlayer[1], camera2, 1, 1);
			init_draw(&GlobalPlayer[2], camera2, 2, 1);
			init_draw(&GlobalPlayer[3], camera2, 3, 1);
			init_draw(&GlobalPlayer[0], camera3, 0, 2);
			init_draw(&GlobalPlayer[1], camera3, 1, 2);
			init_draw(&GlobalPlayer[2], camera3, 2, 2);
			init_draw(&GlobalPlayer[3], camera3, 3, 2);
			init_draw(&GlobalPlayer[0], camera4, 0, 3);
			init_draw(&GlobalPlayer[1], camera4, 1, 3);
			init_draw(&GlobalPlayer[2], camera4, 2, 3);
			init_draw(&GlobalPlayer[3], camera4, 3, 3);
            break;
    }
}

void check_finish_race_hack(void) //MRW: 1/3 CHOCO: 1/2 MOO: 0/1 BAN: 3/2
{
	switch (cup_select)
	{
		case 0: //Moo -> Ban
			cup_select = 3;
			circuit_select = 2;
			*(uchar*) 0x800DC544 = 3; //cup_number = 3;
			break;

		case 1:
			if (circuit_select == 3) //MRW -> Choco
			{
				cup_select = 1;
				circuit_select = 2;
				*(uchar*) 0x800DC544 = 1; //cup_number = 1;
			}
			else //Choco -> Moo
			{
				cup_select = 0;
				circuit_select = 1;	
				*(uchar*) 0x800DC544 = 2; //cup_number = 2;
			}
			break;
		
		default: //Ban -> return
			next_sequence_mode = GAMESELECTSEQUENCE;
			cup_number = 0;
			return;
	}

	next_sequence_mode = RACESEQUENCE;
}

void make_rank_hack(void)
{
    int reverse[] = {7,6,5,4,3,2,1,0};
    int inorder[] = {0,1,2,3,4,5,6,7};

	if (((cup_number == 0) && (retry_count == 0)) || (demo_flag == 1) || (title_mode == 0x40)) //OG: circuit_select
		for (int i = 0; i < 8; i++) 
			kartrank[i] = reverse[i];
	else 
		for (int i = 0; i < 8; i++) 
			kartrank[i] = inorder[ogawa_rank[i]];//GlobalPlayer[i].rank;//rank_to_num[i]; //spC[ogawa_rank[i]]; //801643B8,u32,ogawa_rank
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   CONTROLLERS                                          //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void gselControler_hook(DecompController *controller, ushort arg1) 
{
    if (gsel_mode == 7)
		gsel_mode = 3;
	
	if (GlobalController[4]->ButtonPressed &BTN_L) return;
	if (GlobalController[4]->ButtonPressed &BTN_R) return;

	if ((GlobalController[4]->ButtonPressed &BTN_A) && (gsel_mode == 3))
	{
		gsel_mode = 5;
		playSound(0x49008001); //Select
		return;
	}

	if ((GlobalController[4]->ButtonPressed &BTN_B) && (gsel_mode == 5))
	{
		gsel_mode = 3;
		playSound(0x49008002); //Return
		return;
	}

	if ((GlobalController[4]->ButtonPressed &BTN_B) && (gsel_mode == 6))
	{
		gsel_mode = 5;
		GlobalController[4]->ButtonPressed = 0;
		playSound(0x49008002); //Return
		return;
	}

	gselControler(controller, arg1);
}

void mselControler_hook (OSContPad *pad,ushort i, ushort newbutton)
{	
	// Custom flash rect map select var: *(uchar*) 0x800E720C
	cup_number = 0;
	
	if (msel_mode == 2)
	{
		if (g_gameMode == VS && (i == 0))
		{
			if (GlobalController[4]->ButtonPressed &BTN_B)
				SetFadeOut_b();

			if (cup_select == 1 && circuit_select == 3) //MRW: 1/3 CHOCO: 1/2 MOO: 0/1 BAN: 3/2
			{
				if (GlobalController[4]->AnalogPressed &ANA_DOWN)
				{
					cup_select = 1;  
					circuit_select = 2;
					*(uchar*) 0x800E720C = 1;
					return;
				}	
			}
			else if (cup_select == 1 && circuit_select == 2)
			{
				if (GlobalController[4]->AnalogPressed &ANA_DOWN)
				{
					cup_select = 0;  
					circuit_select = 1;
					*(uchar*) 0x800E720C = 2;
					return;
				}	

				if (GlobalController[4]->AnalogPressed &ANA_UP)
				{
					cup_select = 1;  
					circuit_select = 3;
					*(uchar*) 0x800E720C = 0;
					return;
				}	
			}
			else if (cup_select == 0 && circuit_select == 1)
			{
				if (GlobalController[4]->AnalogPressed &ANA_DOWN)
				{
					cup_select = 3;  
					circuit_select = 2;
					*(uchar*) 0x800E720C = 3;
					return;
				}	

				if (GlobalController[4]->AnalogPressed &ANA_UP)
				{
					cup_select = 1;  
					circuit_select = 2;
					*(uchar*) 0x800E720C = 1;
					return;
				}	
			}
			else if (cup_select == 3 && circuit_select == 2)
			{
				if (GlobalController[4]->AnalogPressed &ANA_UP)
				{
					cup_select = 0;  
					circuit_select = 1;
					*(uchar*) 0x800E720C = 2;
					return;
				}	
			}

			if (cup_select == 0 && circuit_select == 0)
			{
				cup_select = 1;
				circuit_select = 3;
				*(uchar*) 0x800E720C = 0;
			}
		}	
	}
	else if (msel_mode == 1)
	{
		if (g_gameMode == VS)
		{
			msel_mode = 2;
			return;
		}
		else
		{
			cup_select = 1;
			circuit_select = 3;
		}
	}
	
	mselControler(pad,i,newbutton);


	// loadFont();
	// printStringNumber(50,40,"msel",msel_mode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   GP RESULTS                                           //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

char raceClassString[][8] = {"50(","100(","150(","200("};

void DispOB_result_point_hack(ObjBlock *ptr)
{
	char ranking_name[8];
	
	char let[8];
	int i,c,check,dx;
	int l_1,l_2;
	float mul1;

	if (ptr->pattern == KSEQ_GPP_INIT)
		return;
	if (ptr->pattern <= KSEQ_GPP_NAMEOFF)
	{
		for (i = 0;i < 8;i++)
			ranking_name[i] = GlobalPlayer[rank_to_num[i]].kart;
	}
	else
	{
		SortDPRanking(ranking_name);
		SortDPRanking(d_points_rank);

	}

	SetPalette(4);
	SetWord2_a(ptr->disp_x+20,-ptr->disp_y+25,"driver's points",0,0.8,0.8);
	SetPalette(5);
	SetWord2_a(ptr->disp_x+49,-ptr->disp_y+40,"round  ",0,0.7,0.7);

	switch (g_courseID) //OG: kawano_itoa circuit_select
	{
		case BANSHEE_BW:
			kawano_itoa(4,let); 
			break;

		case MOOMOO_FA:
			kawano_itoa(3,let); 
			break;

		case CHOCO_MT:
			kawano_itoa(2,let); 
			break;
		
		default:
			kawano_itoa(1,let); 
			break;
	}

	SetWord2_a(ptr->disp_x+92,-ptr->disp_y+40,let+1,0,0.7,0.7);
	
for (i = 0;i < 4;i++){
		switch(ptr->pattern){
		case KSEQ_GPP_NAMEOFF:
		case KSEQ_GPP_NAMEON:
			if (i*DP_SORT_TIME < ptr->work1)
				check = 1;
			else
				check = 0;
			break;
		default:
			check = 0;
			break;
		}
		if (check)
			continue;

		if (ptr->pattern <= KSEQ_GPP_NAMEOFF){
			check = rank_to_num[i];
			dx = 0;
		}
		else{
			check = name_to_num[(uchar) ranking_name[i]];
			dx = 13;
		}
		if (check < players)
			c = frame_counter % 3;
		else
			c = 3;
		SetPalette(c);
		ResultSub_point(ptr,ptr->disp_x+dx+28,-ptr->disp_y+56+i*16,
						ranking_name[i],i,ranking_name);
	}
	for (i = 4;i < 8;i++){
		switch(ptr->pattern){
		case KSEQ_GPP_NAMEOFF:
		case KSEQ_GPP_NAMEON:
			if (i*DP_SORT_TIME < ptr->work1)
				check = 1;
			else
				check = 0;
			break;
		default:
			check = 0;
			break;
		}
		if (check)
			continue;

		if (ptr->pattern <= KSEQ_GPP_NAMEOFF)
			check = rank_to_num[i];
		else
			check = name_to_num[(uchar) ranking_name[i]];
		if (check < players)
			c = frame_counter % 3;
		else
			c = 3;
		SetPalette(c);
		ResultSub_point(ptr,190-ptr->disp_x,ptr->disp_y+90+i*16,
					   ranking_name[i],i,ranking_name);
	}
	mul1 = 0.6;
	SetPalette(5);

	l_1 = (GetWordLength("Grand Prix")+8)*mul1/2; //mul1 3F19999A
	l_2 = (GetWordLength(raceClassString[race_level])+8)*mul1/2; //l_2 = (GetWordLength(class_name[race_level])+8)*mul1/2;

	SetWord3_ac(230-l_2-ptr->disp_x,ptr->disp_y+225,"Grand Prix",0,mul1,mul1);
	SetWord3_ac(230+l_1-ptr->disp_x,ptr->disp_y+225,raceClassString[race_level],0,mul1,mul1);
}

void DispOB_result_time_hack (ObjBlock *ptr)
{
	char ranking_name[8];
	char let[8];
	int i,c;
	int l_1,l_2;
	float mul1;

	for (i = 0;i < 8;i++)
	{
		ranking_name[i] = GlobalPlayer[rank_to_num[i]].kart;
	}

	SetPalette(4);
	SetWord2_a(ptr->disp_x+30,ptr->disp_y+25,"results",0,1.0,1.0);
	SetPalette(5);
	SetWord2_a(ptr->disp_x+44,ptr->disp_y+40,"round  ",0,0.7,0.7);

	switch (g_courseID)  //OG: kawano_itoa circuit_select
	{
		case BANSHEE_BW:
			kawano_itoa(4,let);
			break;

		case MOOMOO_FA:
			kawano_itoa(3,let); 
			break;

		case CHOCO_MT:
			kawano_itoa(2,let); 
			break;
		
		default:
			kawano_itoa(1,let);
			break;
	}
	
	SetWord2_a(ptr->disp_x+87,ptr->disp_y+40,let+1,0,0.7,0.7);

	for (i = 0;i < 4;i++)
	{
		if (rank_to_num[i] < players)
			c = frame_counter % 3; 
		else
			c = 3;
		SetPalette(c);
		ResultSub_time(ptr->disp_x+10,ptr->disp_y+56+i*16,
					   ranking_name[i],i);
	}

	for (i = 4;i < 8;i++)
	{
		if (rank_to_num[i] < players)
			c = frame_counter % 3;
		else
			c = 3;
		SetPalette(c);
		ResultSub_time(181-ptr->disp_x,ptr->disp_y+90+i*16,
					   ranking_name[i],i);
	}

	mul1 = 0.6;
	SetPalette(5);

	l_1 = (GetWordLength("Grand Prix")+8)*mul1/2;
	l_2 = (GetWordLength(raceClassString[race_level])+8)*mul1/2; 

	SetWord3_ac(245-l_2-ptr->disp_x,ptr->disp_y+225,"Grand Prix",0,mul1,mul1);

	SetWord3_ac(245+l_1-ptr->disp_x,ptr->disp_y+225,
				raceClassString[race_level],
				0,mul1,mul1);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   PAUSE                                                  //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void DispOB_pause_gp_hack(ObjBlock *ptr)
{
	POSXY *pos_ptr;
	float mul1;
	int l_1,l_2;
	int i;
	Screen *scr_ptr;
	int x,y,w,h;
	
	scr_ptr = &GlobalScreen[pause_flag-1];

	x = scr_ptr->posx;
	y = scr_ptr->posy;
	w = scr_ptr->width/2;
	h = scr_ptr->height/2;
	GraphPtr = FillRect1ColorF(GraphPtr,
								x - w,y - h,x + w,y + h,
								0,0,0,140);

	pos_ptr = &gp_pause_message_positions[race_screen_mode*4 + pause_flag-1];

	mul1 = 1.0;
	l_1 = (GetWordLength("grand prix")*mul1+10)/2;
	l_2 = (GetWordLength(class_name[race_level])*mul1+10)/2;
	SetPalette(3);
	SetWord3_ac(160-l_2,pos_ptr->y-50,"grand prix",
				0,mul1,mul1);
	SetPalette(3);
	SetWord3_ac(160+l_1,pos_ptr->y-50,class_name[race_level],
				0,mul1,mul1);
	SetPalette(3);
	SetWord3_ac(160,pos_ptr->y-30,
				circuit_name_j[map_number_chart[cup_select][circuit_select]],
				0,mul1,mul1);
	

	mul1 = 0.75;
	for (i = 0;i < 2;i++){
		SetCursorMessageColor(ptr->pattern - 31,i,3);
		SetWord2_a(pos_ptr->x,pos_ptr->y+i*13,
				   ta_result_select_j[i*4],0,mul1,mul1);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   HUD                                                  //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

int lpsel_cursor_positionZ[][2] = { //800E7108
	{ 24, 63},
	{ 93, 63},
	{162, 63},
	{231, 63},
	{ 24,135},
	{ 93,135},
	{162,135},
	{231,135}
};

// POSXY lmsel_circuit_position[] = {
// 	{157,112},{296,129},
// 	{157,136},{296,153},
// 	{157,160},{296,177},
// 	{157,184},{296,201}
// };

// POSXY msel_bestbox_default_position[] = {
// 	{ -150, 59},
// 	{ 370, 59},
// };

// POSXY msel_bestbox_target_position[] = {
// 	{ 23, 59},
// 	{ 297-MSEL_BESTBOX_X, 59},
// };

// POSXY msel_cupbox_position[] = {
// 	{ 23, 59},
// 	{ 93, 59},
// 	{162, 59},
// 	{232, 59}
// };

// POSXY msel_map4box_position[] = {
// 	{ 23, 112},
// 	{ 87, 112},
// 	{ 23, 151},
// 	{ 87, 151}
// };

void DOB_msel_anime_map2_hook (ObjBlock *ptr)// 0x800AB290
{
	if (*(uchar*) 0x8018EE09 < 1)
		DOB_msel_anime_map2(ptr);
}
void DOB_msel_name_hook (ObjBlock *ptr)// 0x800AB260
{
	if (*(uchar*) 0x8018EE09 < 1)
		DOB_msel_name(ptr);
}

void DispOBJBlock_hook (ObjBlock *ptr)
{  
	int num = 0;

	switch (ptr->kind)
	{
		//Don't show:
		case KO_CHECKER_FLAG: 
		
		case KO_GSEL_OPTION: 
		case KO_GSEL_DATA: 
		case KO_GSEL_PRO:

		case KO_MSEL_LEVEL: 
		case KO_MSEL_KCUP: 
		case KO_MSEL_FCUP: 
		case KO_MSEL_SCUP: 
		case KO_MSEL_SPCUP: 	
		case KO_MSEL_BRECORD:
		case KO_MSEL_BLAP:
		case KO_MSEL_CUP:

		case KO_GAME_CUP:
		case KO_GAME_CIRCUIT:
		case KO_GAME_CUT_UD:
			return;

		//Edit:
		case KO_GSEL_LOGO: 
			ptr->disp_x = 0x0000003D;
			ptr->disp_y = 0x00000011;
			break;
		case KO_GSEL_1P:                               
		case KO_GSEL_2P:                               
		case KO_GSEL_3P:                               
		case KO_GSEL_4P:   
			ptr->disp_x = 0x00000015 + ((ptr->kind - KO_GSEL_1P) * 0x47); //0000005C 000000A3 000000EA
			ptr->disp_y = 0x0000003E;
			break;
		case KO_GSEL_50CC:
		case KO_GSEL_100CC:
		case KO_GSEL_150CC:
			ptr->disp_x = 21 + ((g_playerCount -1) * 71);

			if (gsel_mode > 4)
				ptr->disp_y = 145 + ((ptr->kind - KO_GSEL_50CC) * 18);
			else 
				ptr->disp_y = -200;
			break;
		case KO_GSEL_OK: 
			ptr->disp_x = 21;
			ptr->disp_y = 208;

			if (gsel_mode > 3)
				ptr->work1 = 0;
			else 
				ptr->work1 = 0x20;
			break;
		
		case KO_PSEL_MA: 
		case KO_PSEL_LU:
		case KO_PSEL_PE:
		case KO_PSEL_KI:
		case KO_PSEL_YO:
		case KO_PSEL_KA:
		case KO_PSEL_WA:
		case KO_PSEL_KU:
			num = ptr->kind - KO_PSEL_MA;
			ptr->disp_x = lpsel_cursor_positionZ[num][0];
			ptr->disp_y = lpsel_cursor_positionZ[num][1];
			break;

		
		case KO_PSEL_OK: 
			ptr->disp_x = -240;
			ptr->disp_y = 6;

			if (psel_mode > 1)
				ptr->work1 = 0;
			else 
				ptr->work1 = 0x20;

			cup_select = 0;  
			circuit_select = 0;
			cup_number = 0;
			break;
		
		case KO_MSEL_MAP1:
		case KO_MSEL_MAP2:
		case KO_MSEL_MAP3:
		case KO_MSEL_MAP4:
			break;

		case KO_MSEL_OK: 

			//lmsel_circuit_position 0x800E7208
			//msel_map4box_position 0x800E7168

			ptr->disp_x = -240;
			ptr->disp_y = 0;

			if (msel_mode == 3)
				ptr->work1 = 0;
			else 
				ptr->work1 = 0x20;
			break;

		default:
			break;
	}

	DispOBJBlock(ptr); 
}

extern void DisplayLapHook (int player) 
{
	kwsprite32x16  (g_hudStruct[player].cx, g_hudStruct[player].cy, (ushort*) 0x0D00AD58); //LAP
	kwsprite32x16  (g_hudStruct[player].cx+28, g_hudStruct[player].cy, lap_list[(uchar) g_hudStruct[player].lapcnt]);
}

extern void ChangeLapTimeTexturesHook (int player) 
{
	if (g_hudStruct[player].tptr2) 
	{
		kwsprite_xlu (g_hudStruct[player].tx[1]-19,g_hudStruct[player].ty+8,128,(ushort*)0x0D00BD58,32,16,32,16); //TOTAL
  		kwprintlaptime_xlu  (g_hudStruct[player].tx[1],g_hudStruct[player].ty,128,g_hudStruct[player].totaltime);

		kwsprite_xlu (g_hudStruct[player].tx[1]-19,g_hudStruct[player].ty+8+16,128,(ushort*)0x0D00C158,32,16,32,16); //TIME
  		kwprintlaptime_xlu  (g_hudStruct[player].tx[1],g_hudStruct[player].ty+16,128,g_hudStruct[player].laptime);
	}

	if (g_hudStruct[player].tptr3) 
	{
		 kwsprite_xlu (g_hudStruct[player].tx[2]-19,g_hudStruct[player].ty+8,80,(ushort*)0x0D00BD58,32,16,32,16); //TOTAL
		 kwprintlaptime_xlu (g_hudStruct[player].tx[2],g_hudStruct[player].ty,80,g_hudStruct[player].totaltime);

		 kwsprite_xlu (g_hudStruct[player].tx[2]-19,g_hudStruct[player].ty+8+16,80,(ushort*)0x0D00C158,32,16,32,16); //TIME
		 kwprintlaptime_xlu (g_hudStruct[player].tx[2],g_hudStruct[player].ty+16,80,g_hudStruct[player].laptime);
	}

  	if (g_hudStruct[player].cptr2) 
	{
		kwsprite_xlu  (g_hudStruct[player].cx2,g_hudStruct[player].cy,128,(ushort*)0x0D00AD58,32,16,32,16); //LAP
		kwsprite_xlu  (g_hudStruct[player].cx2+28,g_hudStruct[player].cy,128,lap_list[(uchar) g_hudStruct[player].lapcnt],32,16,32,16);
	}

    if (g_hudStruct[player].cptr3) 
	{
		kwsprite_xlu  (g_hudStruct[player].cx3,g_hudStruct[player].cy,80,(ushort*)0x0D00AD58,32,16,32,16); //LAP
		kwsprite_xlu  (g_hudStruct[player].cx3+28,g_hudStruct[player].cy,80,lap_list[(uchar) g_hudStruct[player].lapcnt],32,16,32,16);
	}
}

extern void DisplayTimeHook (int player)
{
	if ((g_gameMode != 2) && (g_gameMode != 3)) 
	{
		if (g_hudStruct[player].goal == kwgoalcnt) //RACE FINISHED
		{
			if (replay_flag == 0)
			{
				//LAP Time (1,2,3)
				for (int i=0;i <3;i++) 
				{
					if (kwbestlap[i] == 0) //NEW LAP RECORD
					{
						kwprintlaptime (g_hudStruct[player].tx[i+1],g_hudStruct[player].ty+i*16,g_hudStruct[player].laptimebuf[i]);
					}
					else 
					{
						kwprintlaptime_flash (g_hudStruct[player].tx[i+1],g_hudStruct[player].ty+i*16,g_hudStruct[player].laptimebuf[i]);
					}
				}

				//Total Time
		       	kwsprite32x16  (g_hudStruct[player].tx[4]-19,g_hudStruct[player].ty+48+8,(ushort*)0x0D00BD58); //TOTAL

				if (kwbesttotalsw) //NEW TOTAL RECORD
				{
	       	       	kwprintlaptime_flash (g_hudStruct[player].tx[4],g_hudStruct[player].ty+48,g_hudStruct[player].totaltime);
		       	}
				else 
				{
					kwprintlaptime (g_hudStruct[player].tx[4],g_hudStruct[player].ty+48,g_hudStruct[player].totaltime);
				}
			}
		}
		else //RACING
		{
			//Normal Time
			if (g_hudStruct[player].flashtm == 0)
			{
				kwsprite32x16  (g_hudStruct[player].tx[0]-19,g_hudStruct[player].ty+8,(ushort*)0x0D00BD58); //TOTAL
       	       	kwprintlaptime (g_hudStruct[player].tx[0],g_hudStruct[player].ty,g_hudStruct[player].totaltime);

				kwsprite32x16  (g_hudStruct[player].tx[0]-19,g_hudStruct[player].ty+8+16,(ushort*)0x0D00C158); //TIME
       	       	kwprintlaptime (g_hudStruct[player].tx[0],g_hudStruct[player].ty+16,g_hudStruct[player].laptime - g_hudStruct[player].gettime);
			}
			//LAP Time
       		else 
			{
			  	kwsprite32x16  (g_hudStruct[player].tx[0]-19,g_hudStruct[player].ty+8,(ushort*)0x0D00BD58); //TOTAL
				kwsprite32x16  (g_hudStruct[player].tx[0]-19,g_hudStruct[player].ty+8+16,(ushort*)0x0D00AD58); //LAP

				kwprintlaptime (g_hudStruct[player].tx[0],g_hudStruct[player].ty,g_hudStruct[player].totaltime);

				if (kwbestlapsw) //NEW LAP RECORD
				{
					kwprintlaptime_flash (g_hudStruct[player].tx[0],g_hudStruct[player].ty+16,g_hudStruct[player].laptimebuf[g_GameLapTable[player]-1]);
				}
				else 
				{
					kwprintlaptime (g_hudStruct[player].tx[0],g_hudStruct[player].ty+16,g_hudStruct[player].laptimebuf[g_GameLapTable[player]-1]);
		       	}
	       	}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   HUD ANIMS                                            //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void kwcheck_opening_start_HOOK (void)
{
    kwcheck_opening_start(); 

	if(g_playerCount == 1) //SET LAP & TIME X POSI
	{
		g_hudStruct[0].tx[0] = 0xE4;
		g_hudStruct[0].tx[1] = 0xE4;
		g_hudStruct[0].tx[2] = 0xE4;
		g_hudStruct[0].cx = 0x53;
		g_hudStruct[0].cx2 = 0x53;
		g_hudStruct[0].cx3 = 0x53;
		g_hudStruct[0].mx = 0x106;
		g_hudStruct[0].my = 0xb6;
	}

	switch (g_screenSplitA) //SET ITEMBOX POSI
	{
		case 0: 
			g_hudStruct[0].addiy = 0x40;
			break;
		case 1: 
			g_hudStruct[0].addix = 0x80;
			g_hudStruct[1].addix = 0x80;
			break;
		case 2: 
			g_hudStruct[0].addix = 0x80;
			g_hudStruct[1].addix = -0x80;
			break;
		case 3: 
			g_hudStruct[0].addix = 0x80;
			g_hudStruct[2].addix = 0x80;
			g_hudStruct[1].addix = -0x80;
			g_hudStruct[3].addix = -0x80;
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   HUD ITEMBOX                                          //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

extern void kwdisplay_itembox_hack (int player) 
{
	int num = itemboxallocptr[player];

	//if (g_hudAnimStruct[num].anmptr > 1) 
	if(kwscreen_enable)
	{
		kwsprite40x32_ci8(g_hudStruct[player].ix+g_hudStruct[player].addix,g_hudStruct[player].iy+g_hudStruct[player].addiy,g_hudAnimStruct[num].texaddr,g_hudAnimStruct[num].indexaddr);
	}
}

extern void kwdisplay_itemboxs_hack (int player) 
{
	int num = itemboxallocptr[player];

	//if (g_hudAnimStruct[num].anmptr > 1) 
	if(kwscreen_enable)
	{
	  	kwtexture2D_ci8_bl(g_hudStruct[player].ix+g_hudStruct[player].addix,g_hudStruct[player].iy+g_hudStruct[player].addiy,0,g_hudStruct[player].is,g_hudAnimStruct[num].texaddr,g_hudAnimStruct[num].indexaddr,(Vtx*) 0x0D005C30,40,32,40,32);
	}
}


int itemMax = 16;

void kwanm_roulette_HACK(int num) 
{
    int ZpressedFlag;

    ZpressedFlag = 0;
    if ((GlobalController[num]->ButtonPressed & BTN_Z) != 0){ZpressedFlag = 1;}
    if (UnknFlagShroomsTT != 0) {kwanm_start(itemboxallocptr[num], 0);}

    switch (g_hudAnimStruct[itemboxallocptr[num]].anmptr) 
    {
    case 1:
        kwanm_roulette_init(itemboxallocptr[num], num);
        break;
    case 2:
		kwanm_next(itemboxallocptr[num]);
        break;
    case 3:
		kwanm_forward(itemboxallocptr[num], 1, itemMax, 1, 2, 2);
        break;
    case 4:
        kwanm_forward(itemboxallocptr[num], 1, 6, 1, 8, 1);
        break;
    case 5:
        kwanm_forward(itemboxallocptr[num], 1, 4, 1, 0x10, 1);
        break;
    case 6:
        g_hudAnimStruct[itemboxallocptr[num]].anmnum = kwanm_randomitem(itemboxallocptr[num], num);
        g_hudAnimStruct[itemboxallocptr[num]].timer = 8;
        g_hudAnimStruct[itemboxallocptr[num]].chartptr = 2;
        kwanm_next(itemboxallocptr[num]);
        NaPlyLevelStop((uchar) num, 0x100FE1C);
        NaPlyLevelStart((uchar) num, 0x100FE47);
        break;
    case 7:
        kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0, 8, 0xA); 
        break;
    case 9:
		kwanm_clrevflag(itemboxallocptr[num], 4);
        kwchart_off(itemboxallocptr[num]);
        g_hudAnimStruct[itemboxallocptr[num]].anmnum = 0;
        kwanm_next(itemboxallocptr[num]);
        break;
    case 10:
        kwanm_wait(itemboxallocptr[num], 0x14);
        break;
    case 11:
        kwanm_next(itemboxallocptr[num]);
        break;
    case 12:
        /*kwanm_finish(itemboxallocptr[num]);*/
        break;
    case 20:
		if (g_hudAnimStruct[itemboxallocptr[num]].input == 0xB) 
		{
            kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0, 8, 0xA);
        } 
		else 
		{
            kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0xB, 8, 0xA);
        }
        break;
    case 21:
        kwanm_jump(itemboxallocptr[num], 8);
        g_hudAnimStruct[itemboxallocptr[num]].chartptr = 2;
        break;
    case 30:
        if (g_hudAnimStruct[itemboxallocptr[num]].input == 0xB) 
        {
            kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0, 8, 0xA);
        } else 
        {
            kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0xB, 8, 0xA);
        }
        break;
    case 31:
        kwanm_jump(itemboxallocptr[num], 9);
        break;
    case 40:
        if (g_hudAnimStruct[itemboxallocptr[num]].input == 0xD) 
        {
            kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0xE, 8, 0xA);
        } else {
            kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0xD, 8, 0xA);
        }
        break;
    case 41:
        kwanm_jump(itemboxallocptr[num], 8);
        break;
    case 50:
        kwanm_swap(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input, 0, 8, 0x64);
        break;
    }

    if (kwanm_bitcheckevflag(itemboxallocptr[num], 2) != 0) 
    {
        if (g_hudAnimStruct[itemboxallocptr[num]].spstep == 0) 
		{
            kwanm_useditem(num);
        } else 
        {
            g_hudAnimStruct[itemboxallocptr[num]].spstep = g_hudAnimStruct[itemboxallocptr[num]].spstep -1;
        }
    }
    if (g_hudAnimStruct[itemboxallocptr[num]].timer >= 0) 
    {
        if (g_hudAnimStruct[itemboxallocptr[num]].timer > 0) 
        {
            g_hudAnimStruct[itemboxallocptr[num]].timer = g_hudAnimStruct[itemboxallocptr[num]].timer - 1;
        } 
		else 
        {
            if (g_hudAnimStruct[itemboxallocptr[num]].chartptr != 1) 
            {
                if (g_hudAnimStruct[itemboxallocptr[num]].chartptr != 2) 
                {
                    if (g_hudAnimStruct[itemboxallocptr[num]].chartptr != 3) 
                    {

                    } 
					else if (g_hudAnimStruct[itemboxallocptr[num]].output == 0) 
                    {
                        if (kwanm_bitoffcheckevflag(itemboxallocptr[num], 1) != 0) 
                        {
                            if (g_hudAnimStruct[itemboxallocptr[num]].input == 0xB) 
                            {
                                if (kwsteal_item(itemboxallocptr[num], num) != 0) 
                                {
                                    kwanm_jump(itemboxallocptr[num], 0x14);
                                    g_hudAnimStruct[itemboxallocptr[num]].chartptr = 0;
                                } 
								else 
								{
                                    kwanm_jump(itemboxallocptr[num], 9);
                                }
                            } 
                            else if ((g_hudAnimStruct[itemboxallocptr[num]].input == 0xD) || (g_hudAnimStruct[itemboxallocptr[num]].input == 0xE)) 
                            {
                                g_hudAnimStruct[itemboxallocptr[num]].input  = g_hudAnimStruct[itemboxallocptr[num]].input - 1;
                                kwanm_setoutput(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input);
                                g_hudAnimStruct[itemboxallocptr[num]].chartptr = 3;
                                kwanm_jump(itemboxallocptr[num], 0x28);
                            } 
							else 
							{
                                kwanm_jump(itemboxallocptr[num], 9);
                            }
                        } 
						else 
						{
                            kwanm_clrevflag(itemboxallocptr[num], 1);
                            kwanm_jump(itemboxallocptr[num], 0x1E);
                            g_hudAnimStruct[itemboxallocptr[num]].chartptr = 0;
                        }
                    }
                } 
				else 
                {
                    kwanm_setoutput(itemboxallocptr[num], g_hudAnimStruct[itemboxallocptr[num]].input);
                    g_hudAnimStruct[itemboxallocptr[num]].chartptr = 3;
                }
            } 
            else if (ZpressedFlag != 0) 
            {
                kwchart_off(itemboxallocptr[num]);
                kwanm_jump(itemboxallocptr[num], 6);
            }
        } 
    }

	if(g_hudAnimStruct[itemboxallocptr[num]].anmnum < 0x10) //standard items
	{
		g_hudAnimStruct[itemboxallocptr[num]].texaddr = (ushort*) itemboxtbl_pal[(uchar) g_hudAnimStruct[itemboxallocptr[num]].anmnum];
    	g_hudAnimStruct[itemboxallocptr[num]].indexaddr = (uchar*) itemboxtbl_idx[(uchar) g_hudAnimStruct[itemboxallocptr[num]].anmnum];
	}
	else //custom items
	{
		if(g_hudAnimStruct[itemboxallocptr[num]].anmnum == 0x10) //feather
		{
			g_hudAnimStruct[itemboxallocptr[num]].texaddr = (ushort*) &ItemFeatherPal;
    		g_hudAnimStruct[itemboxallocptr[num]].indexaddr = (uchar*) &ItemFeatherTex;
		}
	}
    
    GlobalPlayer[num].item = g_hudAnimStruct[itemboxallocptr[num]].output;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   ITEM PROBABILITIES                                   //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

uchar kwgetitem_sub_HACK(short rank, short pflag) //ITEM DECIDE FOR PLAYER
{
	ushort decision;

	int itemProbs[18][15] =
    {   
/*								     
		 1  2  3  4  5  6  7  8  9  A  B  C  E  F  10  
		 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -- 
		 B  B  G  G  R  R  B  T  F  S  G  M  M  M  F  
		 A  A  S  S  S  S  S  H  A  T  H  U  U  U  E   
		 N  N  H  H  H  H  H  U  K  A  O  S  S  S  A    
 		 A  A  E  E  E  E  E  N  E  R  S  H  H  H  T   
		 N  N  L  L  L  L  L  D        T           H    
		 A  A  L  L  L  L  L  E  I           3  G  E   
		    S     S     S     R  B              O  R  
													   Mode Rank
*/		{30,05,30,05,05,00,00,00,10,00,05,10,00,00,00},//GP 1st
		{00,05,05,10,15,20,00,05,05,05,05,05,15,05,00},//GP 2nd
		{00,00,00,10,20,20,00,05,00,10,00,05,20,10,00},//GP 3rd
		{00,00,00,00,15,20,05,10,00,15,00,05,20,10,00},//GP 4th
		{00,00,00,00,10,20,05,10,00,15,00,05,25,10,00},//GP 5th
		{00,00,00,00,00,20,10,15,00,20,00,00,25,10,00},//GP 6th
		{00,00,00,00,00,20,10,20,00,30,00,00,05,10,05},//GP 7th TripleShroom -5 / Feather +5
		{00,00,00,00,00,20,15,20,00,30,00,00,00,10,05},//GP 8th TripleShroom -5 / Feather +5
		//////////////////////////////////////////////
        {25,10,30,05,05,00,00,00,10,00,05,10,00,00,00},//VS2 1st
		{00,05,00,05,05,15,05,15,00,15,00,00,15,20,00},//VS2 2nd
		//////////////////////////////////////////////
		{35,05,30,00,05,00,00,00,10,00,05,10,00,00,00},//VS3 1st
		{05,05,00,10,15,15,00,05,05,05,05,05,20,05,00},//VS3 2nd
		{00,00,00,00,10,20,10,15,00,15,00,00,15,10,05},//VS3 3rd TripleShroom -5 / Feather +5
		//////////////////////////////////////////////
		{35,05,30,00,05,00,00,00,10,00,05,10,00,00,00},//VS4 1st
		{05,05,05,10,15,15,00,00,05,05,05,05,25,00,00},//VS4 2nd
		{00,05,00,05,10,15,05,10,05,10,00,05,20,05,05},//VS4 3rd TripleShroom -5 / Feather +5
		{00,00,00,00,00,20,10,15,00,20,00,00,20,10,05},//VS4 4th TripleShroom -5 / Feather +5
		/////////////////////////////////////////////
		{10,05,05,20,20,00,00,00,15,20,05,00,00,00,00} //BA

		//RM05: CHANGE ITEM PROBABILITES ABOVE
		//sum of numbers in each line has to be 100 (%)!!!
	};

	//choose correct array line for mode & players
	short tempRank = 0;

	switch(g_gameMode)
	{
		case VS: 
				 if (g_playerCount == 2) tempRank = rank+8;
			else if (g_playerCount == 3) tempRank = rank+10;
			else if (g_playerCount == 4) tempRank = rank+13;
			break;
		case BA: 
			tempRank = rank+17;
			break;
		default: tempRank = rank;
	}

	//Create array with summarized probabilities of itemProbs array
	static ushort sum[15];

	for(int k = 0; k<15; k++) sum[k] = 0; //zero 
	for(int i = 0; i < 15; i++) //number of available different items i
	{
		for(int j = 0; j <= i; j++) //sum of array elements j lte as current item i
		{
			sum[i] = sum[i] + itemProbs[tempRank][j];
		}
	}

	//decide which item to choose
	float rand = (float) MakeRandom(); //generate random number 1-100
	rand = (rand/65536.0f)*100;
	ushort number = (ushort) rand + 1;
	GlobalCharA = number;

	     if(number <= sum[0])  decision = 1; //Banana
	else if(number <= sum[1])  decision = 2; //Bananas
	else if(number <= sum[2])  decision = 3; //GShell
	else if(number <= sum[3])  decision = 4; //GShells
	else if(number <= sum[4])  decision = 5; //RShell
	else if(number <= sum[5])  decision = 6; //RShells
	else if(number <= sum[6])  decision = 7; //BShell
	else if(number <= sum[7])  decision = 8; //Thunder
	else if(number <= sum[8])  decision = 9; //Fake IB
	else if(number <= sum[9])  decision = 10; //Star
	else if(number <= sum[10]) decision = 11; //Ghost
	else if(number <= sum[11]) decision = 12; //Mushroom
									   		  //13 empty cause it's 2 mushrooms
	else if(number <= sum[12]) decision = 14; //3 Mushrooms
	else if(number <= sum[13]) decision = 15; //Gold Mushroom
	else if(number <= sum[14]) decision = 16; //Feather
	else 					   decision = 1;  
	
	return((uchar) decision);
}

void execute_item_hook (Player *car)
{
	int num=car-&GlobalPlayer[0];

	if(car->item == 0x0010) //feather
	{
		car->weapon=car->weapon|USE_FEATHER;
		kwanm_useditem(num);
	}	
	else
	{
		execute_item(car);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
//MARK: -                                   OVERKART HOOKS                                       //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

void startRace() //RUNS ONCE AT RACE START
{

}

void endRace() //RUNS ONCE AT RACE END
{

}

void gameCode(void) //RUNS DURING WHOLE RACE
{	
	if (g_gameMode == GP && g_playerCount == 1)
	{
		if (*(uint*) 0x80164A28 == 1) //cam opening flag
			*(uint*) 0x80164A28 = 2;

		if (g_startingIndicator == 1) //cam mode
			*(ushort*) 0x80152300 = 1;
	}

	// loadFont();
	// printStringNumber(10,10,"debug", GlobalCharA);
}

void allRun(void) //RUNS ALL THE TIME (CANNOT PRINT ETC.)
{
	if (startupSwitch != 35)
	{
		InitialSetup();
	}
}

void TitleMenuHandler() //RUNS DURING TITLE SCREEN
{
	titleDemo = 0;
}

void PrintMenuFunction() //RUNS DURING MENU SCREENS
{		
	#ifdef DEBUG
	
	loadFont();
	printStringNumber(0,0,"GlobA: ",GlobalIntA);
	printStringNumber(0,10,"GlobB: ",GlobalIntB);

	if(GlobalController[4]->ButtonPressed &BTN_DLEFT)
		GlobalIntA--;
	if(GlobalController[4]->ButtonPressed &BTN_DRIGHT)
		GlobalIntA++;

	if(GlobalController[4]->ButtonPressed &BTN_DUP)
		GlobalIntB--;
	if(GlobalController[4]->ButtonPressed &BTN_DDOWN)
		GlobalIntB++;

	#endif
}

void DrawStuff() 
{

}
