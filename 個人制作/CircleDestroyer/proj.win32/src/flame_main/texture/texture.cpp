//-----------------------------------------------------------------------------
//							サウンド関係
//														programed by N-KAITO
//-----------------------------------------------------------------------------

#include    "../flame_include.h"

//----------------------------------------------------------------
//　テクスチャのキャッシュ
//----------------------------------------------------------------
void Texture_Load(SINT32 tex_no, SINT8 tex_name[256])
{
    tex[tex_no] = cocos2d::Director::getInstance()->getTextureCache()->addImage(tex_name);
}

//----------------------------------------------------------------
//  テクスチャの解放
//----------------------------------------------------------------
void Texture_Release(SINT32 tex_no)
{
    cocos2d::Director::getInstance()->getTextureCache()->removeTexture(tex[tex_no]);
    //tex[tex_no] = 0;
}

//----------------------------------------------------------------
// 現在のテクスチャの大きさを取得
//----------------------------------------------------------------
void TEX_get_size(TASK* ap, FLOAT* x, FLOAT* y)
{
    PARTS_RECT* rect = &ap->uv_rect[ap->anime_no];

    //画像の大きさを取得
    //スマホの画面サイズによって大きさが変わるため調整
    Vec2 tex_percent = Vec2(rect->width / tex[ap->tex_no]->getPixelsWide(), rect->height / tex[ap->tex_no]->getPixelsHigh());
    Vec2 tex_size = Vec2(rect->width * tex_percent, rect->height * tex_percent);
    tex_size = Vec2(tex[ap->tex_no]->getContentSize().width * tex_percent.x / 2, tex[ap->tex_no]->getContentSize().height * tex_percent.y / 2);

    *x = tex_size.x * ap->scale[X];
    *y = tex_size.y * ap->scale[Y];
}

//----------------------------------------------------------------
//  四角形の当たり判定
//----------------------------------------------------------------
SINT32 HIT_rect_check(TASK* ap, FLOAT x, FLOAT y)
{
    Vec2 tex_size;

    TEX_get_size(ap, &tex_size.x, &tex_size.y);

    //X座標の当たり判定
    if (ap->pos[X] + tex_size.x >= x && ap->pos[X] - tex_size.x <= x)
    {
        //Y座標の当たり判定
        if (ap->pos[Y] + tex_size.y >= y && ap->pos[Y] - tex_size.y <= y)
        {
            return 1;
        }
    }
    return 0;
}