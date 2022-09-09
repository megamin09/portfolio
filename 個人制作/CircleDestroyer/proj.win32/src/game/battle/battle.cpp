#include "../../flame_main/flame_include.h"
#include "../game_include.h"

//画面の区画わけ
RECT_4_FLOAT battle_map[4];
FLOAT float_random[4];
SINT32 get_flag = -1, get_point = 9999;
SINT32 point_num[4];
SINT32 next_point;
SINT32 system_sec, mis_num;

SINT32 odai_string_data[2][2] = 
{
	{ 100, 100 },
};

PARTS_RECT obje_rect[] = 
{
	{ 384, 0, 256, 256, 256 / 2, 256 / 2 },
};

//--------------------------------------------------------
//　数字の桁数を返す
//--------------------------------------------------------
SINT32 NUM_digit(SINT32 num)
{
	SINT32 digit = 0;	//桁数
	SINT32 loop1 = 10;

	do
	{
		num /= loop1;
		digit++;
	}while( num > 0 );

	return digit;

}

//--------------------------------------------------------
//	サークルのエフェクト
//	type	サークルのエフェクトの種類
//--------------------------------------------------------
void BATTLE_get_effect_exec(TASK* ap)
{
	switch (ap->work1[X])
	{
		case 0:
			ap->scale[X] += 0.3f;
			ap->scale[Y] += 0.3f;
			if (ap->scale[X] > 5.0f)
				ap->work1[X] = 1;
			break;

		case 1:
			ap->scale[X] += 0.2f;
			ap->scale[Y] += 0.2f;
			ap->base_color[0][0] -= 5;
			if( ap->scale[X] > 15.0f || ap->base_color[0][0] < 0 )
			{
				TASK_end( ap );
				return;
			}
			break;
	}
}

void BATTLE_get_effect_start(FLOAT x, FLOAT y, SINT32 type)
{
	TASK *ap;
		
	ap = TASK_start(BATTLE_get_effect_exec, "獲得したエッフェクト");
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->scale[X] = 0.0f;
	ap->scale[Y] = 0.0f;
	ap->work1[X] = 0;
	ap->tex_no = TEXTURE_OBJ;
	ap->uv_rect = obje_rect;
	ap->anime_no = 0;
	
	switch (type)
	{
		case 0:
			ap->base_color[0][1] = 26;
			ap->base_color[0][2] = 140;
			ap->base_color[0][3] = 225;
			break;

		case 1:
			ap->base_color[0][1] = 234;
			ap->base_color[0][2] = 23;
			ap->base_color[0][3] = 40;
			break;
	}

	ap->blend_type = BLEND_ADD;
	ap->pri = 100;
}

//--------------------------------------------------------
//	画面をランダムに4つに分ける
//	現状4つランダムな値を与えたら出来そう
//--------------------------------------------------------
void BATTLE_split(void)
{
	
	float_random[0] = random( 200.0f, WINDOW_WIDTH / 2.0f );
	float_random[1] = random( 200.0f, WINDOW_HEIGHT / 2.0f );
	float_random[2] = random( 200.0f, WINDOW_HEIGHT / 2.0f );
	float_random[3] = random( 200.0f, WINDOW_WIDTH / 2.0f );
	
	float_random[0] = WINDOW_WIDTH / 2;
	float_random[1] = WINDOW_HEIGHT / 2;
	float_random[2] = WINDOW_HEIGHT / 2;
	float_random[3] = WINDOW_WIDTH / 2;

	battle_map[0].x      = 0.0f;
	battle_map[0].y      = 0.0f;
	battle_map[0].width  = float_random[0];
	battle_map[0].height = float_random[1];
	
	battle_map[1].x = battle_map[0].width;
	battle_map[1].y = 0;
	battle_map[1].width = WINDOW_WIDTH;
	battle_map[1].height = float_random[2];
	
	battle_map[2].x = 0.0f;
	battle_map[2].y = battle_map[0].height;
	battle_map[2].width = float_random[3];
	battle_map[2].height = WINDOW_HEIGHT;
	
	battle_map[3].x = battle_map[2].width;
	battle_map[3].y = battle_map[1].height;
	battle_map[3].width = WINDOW_WIDTH;
	battle_map[3].height = WINDOW_HEIGHT;
}


//--------------------------------------------------------
//	分割された画面に収まるようなサイズにする
//--------------------------------------------------------
void BATTLE_balls_resize(TASK* ap, SINT32 map_no)
{
	Vec2 max_scale;
	Vec2 tex_size;

	TEX_get_size( ap, &tex_size.x, &tex_size.y );
	max_scale.x = (battle_map[map_no].width - battle_map[map_no].x)  /  ( tex_size.x * 2.0f );
	max_scale.y = (battle_map[map_no].height - battle_map[map_no].y) /  ( tex_size.y * 2.0f );
	
	if (max_scale.x > max_scale.y)
	{
		ap->scale[X] = max_scale.y;
		ap->scale[Y] = max_scale.y;
	}
	else
	{
		ap->scale[X] = max_scale.x;
		ap->scale[Y] = max_scale.x;
	}
	
	ap->scale[X] = random<FLOAT>( 0.8f, ap->scale[X] );
	ap->scale[Y] = ap->scale[X];

	TEX_get_size( ap, &tex_size.x, &tex_size.y );

	ap->pos[X] = random<FLOAT>(battle_map[map_no].x + tex_size.x, battle_map[map_no].width - tex_size.x );
	ap->pos[Y] = random<FLOAT>(battle_map[map_no].y + tex_size.y, battle_map[map_no].height - tex_size.y );

	//点数の座標
	SINT32 digit = NUM_digit( ap->child[0]->work1[X] );
	if (digit % 3 <= 0)
	{
		digit = 0;
	}
	ap->child[0]->pos[X] = ap->pos[X] - (24.0f * ( digit / 2 ));
	ap->child[0]->pos[Y] = ap->pos[Y];
	
	SINT32 work, work2;
	work = ap->child[0]->work1[X];
	work2 = 0;	

	while (1)
	{
		work /= 10;
		work2++;
		if (work <= 0)
		{
			ap->child[0]->pos[X] += work2 / 2 * 48.0f;
			break;
		}
	}
}


//--------------------------------------------------------
//	共通の実行部
//--------------------------------------------------------
void BATTLE_ball_exec(TASK* ap)
{
	
	if (ap->base_color[0][0] != 255)
	{
		if (ap->base_color[0][0] + 5 >= 255)
		{
			ap->base_color[0][0] = 250;
		}
		ap->base_color[0][0] += 5;
		ap->child[0]->base_color[0][0] = ap->base_color[0][0];
	}


	if (TOUCH_TRG())
	{
		if (HIT_rect_check(ap, touch.touch_x, touch.touch_y))
		{
			if (point_num[get_count] == ap->child[0]->work1[X])
			{
				SOUND_start( "sound/se_get.mp3", false, 0.5f );
				BATTLE_get_effect_start(ap->pos[X], ap->pos[Y], 0);
				TASK_end(ap->child[0]);
				TASK_end(ap);
				get_flag = 1;
				get_count++;
				return;
			}
			else
			{
				BATTLE_get_effect_start(ap->pos[X], ap->pos[Y], 1);
				mis_num++;
			}
		}
	}
}

//--------------------------------------------------------
//	バトルボールの表示
//--------------------------------------------------------
void BATTLE_ball_start(void)
{
	TASK *ap, *ap2, *ap3, *ap4;

	point_num[0] = random(0, 100);
	point_num[1] = random(0, 100);
	point_num[2] = random(0, 100);
	point_num[3] = random(0, 100);

	get_point = 9999;

	BATTLE_split();
	ap = TASK_start( BATTLE_ball_exec, "なんかボールの表示" );
	ap->child[0] = font_pop_number( NULL, ap->pos[X], ap->pos[Y], 1.0f, point_num[0]);
	ap->base_color[0][0] = 0;
	ap->child[0]->base_color[0][0] = 0;
	ap->tex_no = TEXTURE_OBJ;
	ap->uv_rect = obje_rect;
	ap->anime_no = 0;
	BATTLE_balls_resize( ap, 0 );

	ap2 = TASK_start(BATTLE_ball_exec, "なんかボールの表示");
	ap2->child[0] = font_pop_number(NULL, ap->pos[X], ap->pos[Y], 1.0f, point_num[1]);
	ap2->base_color[0][0] = 0;
	ap2->child[0]->base_color[0][0] = 0;
	ap2->tex_no = TEXTURE_OBJ;
	ap2->uv_rect = obje_rect;
	ap2->anime_no = 0;
	BATTLE_balls_resize(ap2, 1);

	ap3 = TASK_start(BATTLE_ball_exec, "なんかボールの表示");
	ap3->child[0] = font_pop_number(NULL, ap->pos[X], ap->pos[Y], 1.0f, point_num[2]);
	ap3->base_color[0][0] = 0;
	ap3->child[0]->base_color[0][0] = 0;
	ap3->tex_no = TEXTURE_OBJ;
	ap3->uv_rect = obje_rect;
	ap3->anime_no = 0;
	BATTLE_balls_resize(ap3, 2);

	ap4 = TASK_start(BATTLE_ball_exec, "なんかボールの表示");
	ap4->child[0] = font_pop_number(NULL, ap->pos[X], ap->pos[Y], 1.0f, point_num[3]);
	ap4->base_color[0][0] = 0;
	ap4->child[0]->base_color[0][0] = 0;
	ap4->tex_no = TEXTURE_OBJ;
	ap4->uv_rect = obje_rect;
	ap4->anime_no = 0;
	BATTLE_balls_resize(ap4, 3);
	
}

//--------------------------------------------------------
//	次に消す予定のポイントを格納
//--------------------------------------------------------
void NEXT_point_set(TASK* ap)
{
	SINT32 loop1, work;

	switch (ap->work1[Z])
	{
		case 0:
			//数字が大きい順に獲得
			work = 0;
			for (loop1 = 0; loop1 < 4; loop1++)
			{
				if (point_num[loop1] > work)
				{
					work = point_num[loop1];
				}
			}
			next_point = work;
			break;
	}
}


//--------------------------------------------------------
//	バトルのメイン画面
//--------------------------------------------------------
void BATTLE_main_pops(TASK *ap)

{
	BATTLE_split();
	BATTLE_ball_start();
	CALCULATION_sort( point_num, 0, 3, 1 );
}

//--------------------------------------------------------
// ポイントの集計
//--------------------------------------------------------
void BATTLE_end_drawfunc(TASK* ap)
{
	TASK spr;

	TASK_init( &spr );

	
}

void BATTLE_end_start(TASK* ap)
{
	TASK *ap2;

	ap = TASK_start( NULL, "集計結果の表示" );
	ap->drawfunc = BATTLE_end_drawfunc;
}


//--------------------------------------------------------
//	この面においての進行
//--------------------------------------------------------
void BATTLE_main_system_exec(TASK* ap)
{

	if (get_flag < 0)
	{
		if (ap->work1[P] > 3)
		{
			game_type2 = BATTLE_END;
			TASK_end( ap );
			return;
		}
		ap->work1[P]++;
		BATTLE_main_pops( ap );
		get_flag = 0;
	}

	if (get_count > 3)
	{
		get_count = 0;
		get_flag = -1;
	}
	system_sec++;
}

void BATTLE_main_system_start(void)
{
	TASK* ap;

	ap = TASK_start(BATTLE_main_system_exec, "メインとなるシステムタスク");
	ap->task_type = TASK_TYPE_PRG;
	ap->work1[X] = 9999;	//ゲットしたポイントを格納
	ap->work1[Y] = 0;		//ポイント加算判定
	ap->work1[Z] = 9999;	//お題の判定
	ap->work1[P] = 0;		//現在何もんめか

	//お題のセッティング
	ap->work1[Z] = random(0, 1);

/*
	work5 - 7は各モードのポイントを格納
	X - Pはこの時のポイント
	Dはこの時の選んだ場所
	Eはこの時のMODE
*/

	ap->work5[X] = 0;
	ap->work5[Y] = 0;
	ap->work5[Z] = 0;
	ap->work5[P] = 0;
	ap->work5[D] = 0;
	ap->work5[E] = 0;

	ap->work6[X] = 0;
	ap->work6[Y] = 0;
	ap->work6[Z] = 0;
	ap->work6[P] = 0;
	ap->work6[D] = 0;
	ap->work6[E] = 0;

	ap->work7[X] = 0;
	ap->work7[Y] = 0;
	ap->work7[Z] = 0;
	ap->work7[P] = 0;
	ap->work7[D] = 0;
	ap->work7[E] = 0;
}


//--------------------------------------------------------
//	バトル前のカウントスタート
//--------------------------------------------------------
void BATTLE_count_exec(TASK *ap)
{
	ap->work2[X]++;
	

	if (ap->base_color[0][0] + 30 >= 255)
	{
		ap->base_color[0][0] = 255;
	}
	else
	{
		ap->base_color[0][0] += 255 / 30;
	}

	if (ap->work2[X] >= 60)
	{
		ap->work2[X] = 0;
		ap->work1[X]--;
		ap->base_color[0][0] = 0;
	}

	if (ap->work1[X] <= 0)
	{
		game_type2 = BATTLE_START;
		TASK_end( ap );
		return;
	}
}

void BATTLE_count_start( void )
{
	TASK *ap;
	
	ap = font_pop_number( BATTLE_count_exec, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 3.0f, 3 );
	ap->base_color[0][0] = 0;
}

//--------------------------------------------------------
//	初期化したいものがあれば
//--------------------------------------------------------
void BATTLE_init(void)
{
	system_sec = 0;
	mis_num = 0;
}

//---------------------------------------------------------
//	バトルのメインルーチン
//---------------------------------------------------------
void BATTLE_main_routine(void)
{
	switch (game_type2)
	{
		case BATTLE_INIT:
			BATTLE_init();
			BATTLE_count_start();
			game_type2 = BATTLE_STANDBY;
			break;

		case BATTLE_START:
			BATTLE_main_system_start();
			game_type2 = BATTLE_STANDBY;
			break;

		case BATTLE_STANDBY:
			/*if (get_count > 3)
			{
				get_count = 0;
				get_flag = 0;
				game_type2 = BATTLE_START;
			}*/
			break;

		case BATTLE_END:
			game_type = GAME_END;
			break;
	}
}