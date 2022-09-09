#include "../../flame_main/flame_include.h"
#include "../game_include.h"


SINT32 result_string[3][255] = 
{
	{ 0xce, 0xbe, 0xca, 0xcd, 0xc0, 0xff },
	{ 0x32, 0x21, 0x2f, 0x2e, 0x5a, 0x9b, 0x5b, 0x0b, 0x12, 0x5a, 0x4c, 0x5e, 0x75, 0x15, 0x22, 0x40, 0x2a, 0xff },
	{ 0xc3, 0xc4, 0xc2, 0xc3, 0xfe, 0xce, 0xbe, 0xca, 0xcd, 0xc0, 0xff },
};


//-------------------------------------------------------------------
//	resultのメイン画面の描画
//-------------------------------------------------------------------
void RESULT_main_exec( TASK *ap )
{
	if (ap->child[0]->base_color[0][0] + 3 < 255)
	{
		ap->child[0]->base_color[0][0] += 3;
		ap->child[3]->base_color[0][0] += 3;
	}
	else
	{
		ap->child[0]->base_color[0][0] = 255;
		ap->child[3]->base_color[0][0] = 255;
	}

	ap->work1[X]++;
	if (ap->work1[X] / 60 > 2)
	{
		ap->child[0]->pos[X] -= ( ap->child[0]->pos[X] - (WINDOW_WIDTH / 2.0f - 500.0f) ) / 20.0f;
		ap->child[3]->pos[X] -= (ap->child[3]->pos[X] - (WINDOW_WIDTH / 2.0f - 800.0f)) / 20.0f;
		ap->child[1]->work1[X] += ( ap->work1[Y] - ap->child[1]->work1[X] ) / 10.0f + (ap->work1[Y] - ap->child[1]->work1[X]) % 10;
		ap->child[1]->base_color[0][0] += 5;
		ap->child[4]->base_color[0][0] += 5;
		ap->child[2]->base_color[0][0] += 5;
		if (ap->child[1]->base_color[0][0] >= 255)
		{
			ap->child[1]->base_color[0][0] = 255;
			ap->child[2]->base_color[0][0] = 255;
			ap->child[4]->base_color[0][0] = 255;
		}
		if (TOUCH_TRG())
		{
			game_type = TITLE_START;
			TASK_end( ap->child[0] );
			TASK_end( ap->child[1] );
			TASK_end( ap->child[2] );
			TASK_end( ap->child[3] );
			TASK_end( ap->child[4] );
			TASK_end( ap );
			return;
		}
	}
}


void RESULT_main_pop(void)
{
	TASK *ap;
	
	ap = TASK_start(RESULT_main_exec, "resultの表示");
	ap->task_type = TASK_TYPE_PRG;
	ap->child[0] = font_pop_start( NULL, WINDOW_WIDTH / 2.0f - 300.0f, WINDOW_HEIGHT / 2.0f, 3.0f, 1.0f, 1.0f, result_string[0] );
	ap->child[1] = font_pop_number( NULL, WINDOW_WIDTH / 2.0f + 500.0f, WINDOW_HEIGHT / 2.0f, 3.0f, 0 );
	ap->child[2] = font_pop_start(NULL, WINDOW_WIDTH / 2.0f - 700.0f, WINDOW_HEIGHT / 2.0f + 300.0f, 2.0f, 1.0f, 1.0f, result_string[1]);
	ap->child[3] = font_pop_start(NULL, WINDOW_WIDTH / 2.0f - 500.0f, WINDOW_HEIGHT / 2.0f - 300.0f, 3.0f, 0.8f, 1.0f, result_string[2]);
	ap->child[4] = font_pop_number(NULL, WINDOW_WIDTH / 2.0f + 500.0f, WINDOW_HEIGHT / 2.0f - 300.0f, 3.0f, high_score);
	ap->child[0]->base_color[0][0] = 0;
	ap->child[1]->base_color[0][0] = 0;
	ap->child[2]->base_color[0][0] = 0;
	ap->child[3]->base_color[0][0] = 0;
	ap->child[3]->base_color[0][1] = 255;
	ap->child[3]->base_color[0][2] = 142;
	ap->child[3]->base_color[0][3] = 0;
	ap->child[4]->base_color[0][0] = 0;
	ap->work1[X] = 0;					//カウント
	ap->work1[Y] = ( 60 * 200 - system_sec * 5.0f) - mis_num * 500.0f;
	

	if (ap->work1[Y] <= 0 )
	{
		ap->work1[Y] = 0;
	}

	if (high_score < ap->work1[Y])
	{
		ap->child[4]->work1[X] = ap->work1[Y];
		ap->child[4]->base_color[0][1] = 255;
		ap->child[4]->base_color[0][2] = 142;
		ap->child[4]->base_color[0][3] = 0;
		high_score = ap->work1[Y];
	}
	DATA_save(DATA_SAVE, &high_score);
}


//-------------------------------------------------------------------
//	リザルトのメインルーチン
//-------------------------------------------------------------------
void RESULT_main_routine( void )
{
	switch (game_type2)
	{
		case 0:
			//グラフィックの読み込みや初期化
			game_type2++;
			break;

		case 1:
			//メインの描画
			RESULT_main_pop();
			game_type2++;
			break;
	}
}