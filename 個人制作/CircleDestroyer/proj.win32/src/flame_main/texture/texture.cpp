//-----------------------------------------------------------------------------
//							�T�E���h�֌W
//														programed by N-KAITO
//-----------------------------------------------------------------------------

#include    "../flame_include.h"

//----------------------------------------------------------------
//�@�e�N�X�`���̃L���b�V��
//----------------------------------------------------------------
void Texture_Load(SINT32 tex_no, SINT8 tex_name[256])
{
    tex[tex_no] = cocos2d::Director::getInstance()->getTextureCache()->addImage(tex_name);
}

//----------------------------------------------------------------
//  �e�N�X�`���̉��
//----------------------------------------------------------------
void Texture_Release(SINT32 tex_no)
{
    cocos2d::Director::getInstance()->getTextureCache()->removeTexture(tex[tex_no]);
    //tex[tex_no] = 0;
}

//----------------------------------------------------------------
// ���݂̃e�N�X�`���̑傫�����擾
//----------------------------------------------------------------
void TEX_get_size(TASK* ap, FLOAT* x, FLOAT* y)
{
    PARTS_RECT* rect = &ap->uv_rect[ap->anime_no];

    //�摜�̑傫�����擾
    //�X�}�z�̉�ʃT�C�Y�ɂ���đ傫�����ς�邽�ߒ���
    Vec2 tex_percent = Vec2(rect->width / tex[ap->tex_no]->getPixelsWide(), rect->height / tex[ap->tex_no]->getPixelsHigh());
    Vec2 tex_size = Vec2(rect->width * tex_percent, rect->height * tex_percent);
    tex_size = Vec2(tex[ap->tex_no]->getContentSize().width * tex_percent.x / 2, tex[ap->tex_no]->getContentSize().height * tex_percent.y / 2);

    *x = tex_size.x * ap->scale[X];
    *y = tex_size.y * ap->scale[Y];
}

//----------------------------------------------------------------
//  �l�p�`�̓����蔻��
//----------------------------------------------------------------
SINT32 HIT_rect_check(TASK* ap, FLOAT x, FLOAT y)
{
    Vec2 tex_size;

    TEX_get_size(ap, &tex_size.x, &tex_size.y);

    //X���W�̓����蔻��
    if (ap->pos[X] + tex_size.x >= x && ap->pos[X] - tex_size.x <= x)
    {
        //Y���W�̓����蔻��
        if (ap->pos[Y] + tex_size.y >= y && ap->pos[Y] - tex_size.y <= y)
        {
            return 1;
        }
    }
    return 0;
}