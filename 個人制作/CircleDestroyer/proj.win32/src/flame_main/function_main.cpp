#include "flame_include.h"
#include "../proj.win32/src/game/game_main.h"

//------------------------------------------------------------

//ネームスペース関係


//cocos2d-x関係の命令を受け取れるように
USING_NS_CC;
//サウンド関係の命令を使えるように
using namespace experimental;

//------------------------------------------------------------


SINT32 task_amount = 0;
SINT32 freame = 0, freame_count;
FLOAT freame_time = 0.0f;
SINT32 func_no;

Texture2D* tex[DATA_MAX];
TASK func_box[DATA_MAX];
PRI_DATA pri_box[DATA_MAX];
TOUCH_POS touch;
cocos2d::UserDefault* userdefault;

//ポリゴンの座標データ
PARTS_PORY poly_data[4]
{
    { -97.5f, -135.0f, 0.0f, 0.0f, 1.0f },  //左下
    { -97.5f,  135.0f, 0.0f, 0.0f, 0.0f },  //左上
    {  97.5f, -135.0f, 0.0f, 1.0f, 1.0f },  //右下
    {  97.5f,  135.0f, 0.0f, 1.0f, 0.0f },  //右上
};

//----------------------------------------------------------------
//  乱数生成
//----------------------------------------------------------------
void RANDOM_get_int(SINT32 min, SINT32 max)
{
    
}

//----------------------------------------------------------------
//  function_mainという基盤となるシーンを作る
//----------------------------------------------------------------
Scene* function_main::createScene()
{
    auto sprite = function_main::create();

    return sprite;
}

//----------------------------------------------------------------
// 「INIT」初期化
//----------------------------------------------------------------
bool function_main::init()
{
    //レイヤーの初期化
    if (!Scene::init())
    {
        return false;
    }

    //タスクBOXの中身とテクスチャBOXを初期化
    memset(func_box, 0, sizeof(func_box));
    memset(tex, 0, sizeof(tex));

    //現在タッチしている座標のリセット
    //とりあえず画面中央とする
    touch.touch_x = WINDOW_WIDTH / 2.0f;
    touch.touch_y = WINDOW_HEIGHT / 2.0f;

    //タスクのプライオリティをとりあえず9999で初期化
    for (SINT32 loop1 = 0; loop1 < DATA_MAX; loop1++)
    {
        func_box[loop1].pri = 99999;
        pri_box[loop1].pri = 99999;
    }

    // シェーダーをセット
    CCGLProgram* pProgram = ccshadercache->sharedShaderCache()->programForKey(glprogram->SHADER_NAME_POSITION_TEXTURE_COLOR);
    this->setShaderProgram(pProgram);

    //データセーブのインスタンスをポインタに格納
    userdefault = cocos2d::UserDefault::getInstance();

    //画面タッチ情報を受け取る関数の設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(function_main::onTouchBegan, this);  //画面にタッチした瞬間
    listener->onTouchMoved = CC_CALLBACK_2(function_main::onTouchMoved, this);  //画面にタッチしてスライドさせている時
    listener->onTouchEnded = CC_CALLBACK_2(function_main::onTouchEnded, this);  //画面から指を話したとき
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    //auto keyfunc = EventListenerKeyboard::create();
    //keyfunc->onKeyPressed = CC_CALLBACK_2(function_main::Key_Event_Down, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(keyfunc, this);

    //auto keyfunc2 = EventListenerKeyboard::create();
    //keyfunc2->onKeyReleased = CC_CALLBACK_2(function_main::Key_Event_Up, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(keyfunc2, this);

    //これはデバッグ情報のFPSとタスクの数を出力する者なのでリリースのときには消す
    Texture_Load(DATA_MAX - 1, "font/alphabet.png");
    Texture_Load(DATA_MAX - 2, "font/font.png");
    DEBUG_system_start();

    //1秒間に60回呼び出すupdate関数の設定
    this->scheduleUpdate();

    //成功したことを返す
    return true;

}

//----------------------------------------------------------------
//  描画部
//  現状プライオリティの種類が少なければ少ないほど高速に動く
//  ただ、このやり方では限界があるのでタスクBOXのソートを見直す必要あり
//----------------------------------------------------------------
void function_main::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    /*quickSort_main(0, DATA_MAX);*/
    SORT_main_start( pri_box );
    function_main::DRAW_init_set();

    for (SINT32 loop1 = 0; loop1 < DATA_MAX; loop1++)
    {
        if (func_box[pri_box[loop1].task_no].use_flag != false && func_box[pri_box[loop1].task_no].task_type == TASK_TYPE_GRP)
        {
            if (func_box[pri_box[loop1].task_no].drawfunc != NULL)
            {
                func_box[pri_box[loop1].task_no].drawfunc(&func_box[pri_box[loop1].task_no]);
            }

            else
            {
                DRAW_default_func(&func_box[pri_box[loop1].task_no]);
            }
        }
    }

    /*while (now_pri < next_pri)
    {
        before_pri = now_pri;
        now_pri = next_pri;
        next_pri = 9999;
        for (SINT32 loop1 = 0; loop1 < DATA_MAX; loop1++)
        {
            if (draw_data[loop1].pri == now_pri)
            {
                if (draw_data[loop1].drawfunc != NULL)
                {
                    draw_data[loop1].drawfunc(&draw_data[loop1]);
                }

                else
                {
                    DRAW_default_func(&draw_data[loop1]);
                }
            }
            else
            {
                if (now_pri < draw_data[loop1].pri && next_pri >= draw_data[loop1].pri || draw_data[loop1].pri > before_pri && next_pri >= draw_data[loop1].pri)
                {
                    next_pri = draw_data[loop1].pri;
                }
            }
            task_loop++;
        }
    }
    task_loop = task_loop;*/
}

//----------------------------------------------------------------
//  1秒間に60回とおるメインルーチンの代わりとなるもの
//----------------------------------------------------------------
void function_main::update(FLOAT delta)
{
    //if (KEY_Inkey_TRG(DIK_ESCAPE))
    //{
    //    Director::getInstance()->end();
    //}

    TOUCH_count();
    game_start();
    /*KEY_count();*/

    TASK_func_exec();

    freame_time += delta;
    freame_count++;
    if (freame_time > 1.0f)
    {
        freame = freame_count;
        freame_count = 0;
        freame_time -= 1.0f;
    }

}




