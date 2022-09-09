#include "../flame_main/flame_include.h"
#include "game_include.h"



//---------------------------------------------------------------------
//　外部変数定義
//---------------------------------------------------------------------
SINT32 game_type = 0, game_type2 = 0, game_type3 = 0;
SINT32 get_count = 0;
SINT32 high_score = 0;


//---------------------------------------------------------------------
//	グラフィックの読み込み関係
//---------------------------------------------------------------------
void TEXTURE_game_load(void)
{
	Texture_Load( TEXTURE_OBJ, "effect_1.png" );
}


//---------------------------------------------------------------------
//	ゲームメインルーチン
//---------------------------------------------------------------------
void game_start( void )
{
	switch (game_type)
	{
		case GAME_INIT:
			TEXTURE_game_load();
			//DATA_save( DATA_LOAD, &high_score );
			game_type = TITLE_START;

			break;

		case TITLE_START:
			game_type2 = 0;
			game_type++;
			break;

		case TITLE_START + 1:
			TITLE_main_routine();
			break;

		case GAME_HOME:
			
			break;

		case GAME_START:
			game_type2 = 0;
			game_type++;
			break;

		case GAME_START + 1:
			BATTLE_main_routine();
			break;

		case GAME_END:
			game_type2 = 0;
			game_type++;
			break;
	
		case GAME_END + 1:
			RESULT_main_routine();
			break;

		case 200:
			SORT_main_start(0);
			break;

	}
}
