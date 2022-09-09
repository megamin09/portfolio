#include "flame_include.h"

////------------------------------------------------------------
//
////ネームスペース関係
//
//
////cocos2d-x関係の命令を受け取れるように
//USING_NS_CC;
//
////------------------------------------------------------------

//クラスのポインタ化
cocos2d::CCShaderCache* ccshadercache;
cocos2d::Director* director;
cocos2d::GLProgram* glprogram;
cocos2d::CCDirector* ccdirector;

void function_main::DRAW_init_set( void )
{
    // 深度テスト有効  
    //奥行情報を保持
    ccdirector->sharedDirector()->setDepthTest(true);
    // 頂点に座標とテクスチャUVのindex指定  
    ccGLEnableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD | GL::VERTEX_ATTRIB_FLAG_COLOR);
    //ccGLEnableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    // 設定したシェーダーを使用する  
    this->getShaderProgram()->use();

    // 行列の作成  
    kmMat4 matProjection;       //射影行列
    kmMat4 matView;             //ビュー行列
    kmMat4 matWVP;              //全体の情報を統括
    kmMat4 matTrans;            //位置座標の登録
    kmMat4 matScale;            //大きさの登録


    kmGLGetMatrix(KM_GL_PROJECTION, &matProjection);    // 射影行列を取得  
    kmGLGetMatrix(KM_GL_MODELVIEW, &matView);           // ビュー行列の取得  
    kmMat4Multiply(&matWVP, &matProjection, &matView);

    //作成したポリゴンの中心座標の指定
    kmMat4Translation(&matTrans, 0.0f, 0.0f, 1.0f);
    kmMat4Multiply(&matWVP, &matWVP, &matTrans);

    //作成したポリゴンの大きさをセット
    kmMat4Scaling(&matScale, 1.0f, 1.0f, 1.0f);
    kmMat4Multiply(&matWVP, &matWVP, &matScale);

    // 作成した行列をシェーダーに送る  
    GLuint matrixId = glGetUniformLocation(this->getShaderProgram()->getProgram(), glprogram->UNIFORM_NAME_MVP_MATRIX);
    this->getShaderProgram()->setUniformLocationWithMatrix4fv(matrixId, matWVP.m, 1);
}

void DRAW_default_func( TASK *ap )
{
    PARTS_RECT *rect = &ap->uv_rect[ap->anime_no];
    
    // テクスチャのバインド  
    GL::bindTexture2D(tex[ap->tex_no]->getName());

    // 頂点をセット  
    /*------------------------------------------------
    posに各頂点座標の設置位置
    ※上記で設定したポリゴンを中心座標を0として記述

    uvは全体画像のどの位置を使うか
    SystemOZでポリゴン描画する際に設定するuvと同じ

    今回はGL_TRIANGLE_STRIPという設定で行う
    ------------------------------------------------*/
    kmVec3 pos[4];
    kmVec2 uv[4];
    Color4B colors[4];

    //どの配列がポジションなのか、UVなのかを指定してあげる
    glVertexAttribPointer(glprogram->VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, pos);
    glVertexAttribPointer(glprogram->VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, uv);
    glVertexAttribPointer(glprogram->VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);

    //表示する元画像がどのぐらい圧縮されているか
    Vec2 tex_percent = Vec2(tex[ap->tex_no]->getContentSize().width / tex[ap->tex_no]->getPixelsWide(), tex[ap->tex_no]->getContentSize().height / tex[ap->tex_no]->getPixelsHigh());
    //表示されている画像の中心までのポイントを表示    
    Vec2 tex_point_height = Vec2((rect->width - rect->senter_x) * tex_percent.x, rect->senter_y * tex_percent.y);
    Vec2 tex_point_low    = Vec2(rect->senter_x * tex_percent.x, ( rect->height - rect->senter_y ) * tex_percent.y);
    tex_point_low.x *= -1.0f;
    tex_point_low.y *= -1.0f;
    tex_point_height.x *= ap->scale[X];
    tex_point_height.y *= ap->scale[Y];
    tex_point_low.x *= ap->scale[X];
    tex_point_low.y *= ap->scale[Y];
    Vec3 task_pos = ap->pos;
    
    task_pos.y = WINDOW_HEIGHT - task_pos.y;
    

    //頂点座標及びuvの定義
    kmVec3Fill(&pos[0], tex_point_low.x + task_pos.x, tex_point_low.y + task_pos.y, poly_data[0].z + task_pos.z);     //左下
    kmVec3Fill(&pos[1], tex_point_low.x + task_pos.x, tex_point_height.y + task_pos.y, poly_data[1].z + task_pos.z);     //左上
    kmVec3Fill(&pos[2], tex_point_height.x + task_pos.x, tex_point_low.y + task_pos.y, poly_data[2].z + task_pos.z);     //右下
    kmVec3Fill(&pos[3], tex_point_height.x + task_pos.x, tex_point_height.y + task_pos.y, poly_data[3].z + task_pos.z);     //右上

    auto tex_size = Vec2(tex[ap->tex_no]->getPixelsWide(), tex[ap->tex_no]->getPixelsHigh());   //縮小される前の画像の大きさを取得
    /*auto tex_size = Vec2(tex[func_box[func_no].tex_no]->getContentSize().width, tex[func_box[func_no].tex_no]->getContentSize().height);*/

    auto tex_size_x = Vec2(rect->x / tex_size.x, ( rect->x + rect->width  ) / tex_size.x);
    auto tex_size_y = Vec2(rect->y / tex_size.y, ( rect->y + rect->height ) / tex_size.y);

    kmVec2Fill(&uv[0], tex_size_x.x, tex_size_y.y);     //左下
    kmVec2Fill(&uv[1], tex_size_x.x, tex_size_y.x);     //左上
    kmVec2Fill(&uv[2], tex_size_x.y, tex_size_y.y);     //右下
    kmVec2Fill(&uv[3], tex_size_x.y, tex_size_y.x);     //右上

    colors[0] = Color4B( ap->base_color[0][1], ap->base_color[0][2], ap->base_color[0][3], ap->base_color[0][0] );
    colors[1] = Color4B( ap->base_color[0][1], ap->base_color[0][2], ap->base_color[0][3], ap->base_color[0][0] );
    colors[2] = Color4B( ap->base_color[0][1], ap->base_color[0][2], ap->base_color[0][3], ap->base_color[0][0] );
    colors[3] = Color4B( ap->base_color[0][1], ap->base_color[0][2], ap->base_color[0][3], ap->base_color[0][0] );


    /*glAlphaFunc(GL_GEQUAL, 0.0f);
    glEnable(GL_ALPHA_TEST);*/
    

    switch (ap->blend_type)
    {
        case BLEND_NORMAL:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;

        case BLEND_ADD:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;

        case BLEND_SUB:
            //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); // src = 1 固定
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); // src = 1 固定
            //glAlphaFunc(GL_GEQUAL, 1.0f);
            //glEnable(GL_ALPHA_TEST);
            break;

        case BLEND_MULTIPLE:
            break;

        case BLEND_NEG:
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
            break;
    }

    //renderに情報を渡す
    //DirectXのD3DPT_TRIANGLESTRIPはGL_TRIANGLE_STRIPに似ている
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

//void function_main::DRAW_set_spr(TASK* spr)
//{
//    function_main::DRAW_default_func(spr);                              
//}
//
//void DRAW_test(TASK* ap)
//{
//    function_main::DRAW_set_spr( ap );
//}