#ifndef function_main_SCENE_H__

#define function_main_SCENE_H__


#include "work_custom.h"

#define DATA_MAX        10000               //�^�X�N�̍ő�e��

//---------------------------------------------------------------------
//  �\���̊֌W
//---------------------------------------------------------------------

//��ʃ^�b�`���
typedef struct
{
    int touch_type; //�^�b�`������Ԃ��L�^�@0:�^�b�`���ĂȂ� or �I���@1:�n�߂Ƀ^�b�`�����@2:�X���C�v���
    int touch_time; //�^�b�`���Ă���t���[�������J�E���g�@�^�b�`�I�����߂��o���烊�Z�b�g
    float touch_x, touch_y;
}TOUCH_POS;

//�|���S���`��p�̍\����
typedef struct
{
    float x;
    float y;
    float z;
    float u;
    float v;
}PARTS_PORY;

//�Z�a�̏��n
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
//�@�O���ϐ���`
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
//�@�O���֐���`
//---------------------------------------------------------------------
extern void DEBUG_system_start(void);                               //�f�o�b�O�̕����̕\��


class function_main : public cocos2d::Scene
{

public:

    virtual bool init();

    static cocos2d::Scene* createScene();

    //�����Ń}�C�t���[�������_�[�ɕ`�施�߂�n��
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);
    void DRAW_init_set(void);

    /*void Key_Event_Down(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void Key_Event_Up(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);*/

    /*void DATA_save( void );*/

    /*cocos2d::Label* label1;*/
    //�N���X�̃|�C���^��
    cocos2d::CCShaderCache* ccshadercache;
    cocos2d::Director* director;
    cocos2d::GLProgram* glprogram;
    cocos2d::CCDirector* ccdirector;

    //�摜�̃L���b�V��
    cocos2d::TextureCache* cache = cocos2d::Director::getInstance()->getTextureCache();

    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

    void update(FLOAT delta);

    CREATE_FUNC(function_main);

};


#endif /* defined(__Scene__function_main__) */