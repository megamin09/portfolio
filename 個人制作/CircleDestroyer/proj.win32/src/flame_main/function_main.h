#ifndef function_main_SCENE_H__

#define function_main_SCENE_H__


#include "work_custom.h"

#define DATA_MAX        10000               //タスクの最大容量

//---------------------------------------------------------------------
//  構造体関係
//---------------------------------------------------------------------

//画面タッチ情報
typedef struct
{
    int touch_type; //タッチした状態を記録　0:タッチしてない or 終了　1:始めにタッチした　2:スワイプ状態
    int touch_time; //タッチしているフレーム数をカウント　タッチ終了命令が出たらリセット
    float touch_x, touch_y;
}TOUCH_POS;

//ポリゴン描画用の構造体
typedef struct
{
    float x;
    float y;
    float z;
    float u;
    float v;
}PARTS_PORY;

//短径の情報系
typedef struct
{
    float x, y, width, height, senter_x, senter_y;
}PARTS_RECT;

typedef struct
{
    int pri;
    int task_no;
}PRI_DATA;

//---------------------------------------------------------------------
//　外部変数定義
//---------------------------------------------------------------------
extern cocos2d::Texture2D* tex[DATA_MAX];
extern TOUCH_POS touch;
extern TASK func_box[DATA_MAX];
extern PRI_DATA pri_box[DATA_MAX];
extern PARTS_PORY poly_data[4];
extern SINT32 task_amount, freame;
extern SINT8 str[256];
extern cocos2d::UserDefault* userdefault;
extern SINT32 func_no;

//---------------------------------------------------------------------
//　外部関数定義
//---------------------------------------------------------------------
extern void DEBUG_system_start(void);                               //デバッグの文字の表示


class function_main : public cocos2d::Scene
{

public:

    virtual bool init();

    static cocos2d::Scene* createScene();

    //ここでマイフレームレンダーに描画命令を渡す
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);
    void DRAW_init_set(void);

    /*void Key_Event_Down(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void Key_Event_Up(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);*/

    /*void DATA_save( void );*/

    /*cocos2d::Label* label1;*/
    //クラスのポインタ化
    cocos2d::CCShaderCache* ccshadercache;
    cocos2d::Director* director;
    cocos2d::GLProgram* glprogram;
    cocos2d::CCDirector* ccdirector;

    //画像のキャッシュ
    cocos2d::TextureCache* cache = cocos2d::Director::getInstance()->getTextureCache();

    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

    void update(FLOAT delta);

    CREATE_FUNC(function_main);

};


#endif /* defined(__Scene__function_main__) */