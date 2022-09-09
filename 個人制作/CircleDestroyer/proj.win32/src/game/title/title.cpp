#include "../../flame_main/flame_include.h"
#include "../game_include.h"


SINT32 title_string[1][255] = 
{
	{ 0x32, 0x21, 0x2f, 0x2e, 0x5a, 0x9b, 0x5b, 0x0b, 0x12, 0x57, 0x5a, 0x30, 0x5e, 0xff },
};


//-------------------------------------------------------------------
//	タイトルのメイン実行
//-------------------------------------------------------------------
void TITLE_main_exec(TASK* ap)
{
	ap->child[0]->base_color[0][0] += 2;
	if (ap->child[0]->base_color[0][0] > 255)
	{
		ap->child[0]->base_color[0][0] = 255;
	}

	if (TOUCH_TRG())
	{
		game_type = GAME_START;
		TASK_end( ap->child[0] );
		TASK_end( ap );
		return;
	}
}

void TITLE_main_start(void)
{
	TASK *ap;
	
	ap = TASK_start( TITLE_main_exec, "タイトルのメイン表示" );
	ap->task_type = TASK_TYPE_PRG;
	ap->child[0] = font_pop_start( NULL, WINDOW_WIDTH / 2.0f - 550.0f, WINDOW_HEIGHT / 2.0f, 2.0f, 1.0f, 1.0f, title_string[0] );
	ap->child[0]->base_color[0][0] = 0;
}


//-------------------------------------------------------------------
//	タイトル画面の表示
//-------------------------------------------------------------------
void TITLE_main_routine(void)
{
	switch (game_type2)
	{
		case 0:
			TITLE_main_start();
			game_type2++;
			break;
	}
}