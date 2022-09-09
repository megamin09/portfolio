#include "flame_include.h"

////------------------------------------------------------------
//
////�l�[���X�y�[�X�֌W
//
//
////cocos2d-x�֌W�̖��߂��󂯎���悤��
//USING_NS_CC;
//
////------------------------------------------------------------

//�N���X�̃|�C���^��
cocos2d::CCShaderCache* ccshadercache;
cocos2d::Director* director;
cocos2d::GLProgram* glprogram;
cocos2d::CCDirector* ccdirector;

void function_main::DRAW_init_set( void )
{
    // �[�x�e�X�g�L��  
    //���s����ێ�
    ccdirector->sharedDirector()->setDepthTest(true);
    // ���_�ɍ��W�ƃe�N�X�`��UV��index�w��  
    ccGLEnableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD | GL::VERTEX_ATTRIB_FLAG_COLOR);
    //ccGLEnableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    // �ݒ肵���V�F�[�_�[���g�p����  
    this->getShaderProgram()->use();

    // �s��̍쐬  
    kmMat4 matProjection;       //�ˉe�s��
    kmMat4 matView;             //�r���[�s��
    kmMat4 matWVP;              //�S�̂̏��𓝊�
    kmMat4 matTrans;            //�ʒu���W�̓o�^
    kmMat4 matScale;            //�傫���̓o�^


    kmGLGetMatrix(KM_GL_PROJECTION, &matProjection);    // �ˉe�s����擾  
    kmGLGetMatrix(KM_GL_MODELVIEW, &matView);           // �r���[�s��̎擾  
    kmMat4Multiply(&matWVP, &matProjection, &matView);

    //�쐬�����|���S���̒��S���W�̎w��
    kmMat4Translation(&matTrans, 0.0f, 0.0f, 1.0f);
    kmMat4Multiply(&matWVP, &matWVP, &matTrans);

    //�쐬�����|���S���̑傫�����Z�b�g
    kmMat4Scaling(&matScale, 1.0f, 1.0f, 1.0f);
    kmMat4Multiply(&matWVP, &matWVP, &matScale);

    // �쐬�����s����V�F�[�_�[�ɑ���  
    GLuint matrixId = glGetUniformLocation(this->getShaderProgram()->getProgram(), glprogram->UNIFORM_NAME_MVP_MATRIX);
    this->getShaderProgram()->setUniformLocationWithMatrix4fv(matrixId, matWVP.m, 1);
}

void DRAW_default_func( TASK *ap )
{
    PARTS_RECT *rect = &ap->uv_rect[ap->anime_no];
    
    // �e�N�X�`���̃o�C���h  
    GL::bindTexture2D(tex[ap->tex_no]->getName());

    // ���_���Z�b�g  
    /*------------------------------------------------
    pos�Ɋe���_���W�̐ݒu�ʒu
    ����L�Őݒ肵���|���S���𒆐S���W��0�Ƃ��ċL�q

    uv�͑S�̉摜�̂ǂ̈ʒu���g����
    SystemOZ�Ń|���S���`�悷��ۂɐݒ肷��uv�Ɠ���

    �����GL_TRIANGLE_STRIP�Ƃ����ݒ�ōs��
    ------------------------------------------------*/
    kmVec3 pos[4];
    kmVec2 uv[4];
    Color4B colors[4];

    //�ǂ̔z�񂪃|�W�V�����Ȃ̂��AUV�Ȃ̂����w�肵�Ă�����
    glVertexAttribPointer(glprogram->VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, pos);
    glVertexAttribPointer(glprogram->VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, uv);
    glVertexAttribPointer(glprogram->VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);

    //�\�����錳�摜���ǂ̂��炢���k����Ă��邩
    Vec2 tex_percent = Vec2(tex[ap->tex_no]->getContentSize().width / tex[ap->tex_no]->getPixelsWide(), tex[ap->tex_no]->getContentSize().height / tex[ap->tex_no]->getPixelsHigh());
    //�\������Ă���摜�̒��S�܂ł̃|�C���g��\��    
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
    

    //���_���W�y��uv�̒�`
    kmVec3Fill(&pos[0], tex_point_low.x + task_pos.x, tex_point_low.y + task_pos.y, poly_data[0].z + task_pos.z);     //����
    kmVec3Fill(&pos[1], tex_point_low.x + task_pos.x, tex_point_height.y + task_pos.y, poly_data[1].z + task_pos.z);     //����
    kmVec3Fill(&pos[2], tex_point_height.x + task_pos.x, tex_point_low.y + task_pos.y, poly_data[2].z + task_pos.z);     //�E��
    kmVec3Fill(&pos[3], tex_point_height.x + task_pos.x, tex_point_height.y + task_pos.y, poly_data[3].z + task_pos.z);     //�E��

    auto tex_size = Vec2(tex[ap->tex_no]->getPixelsWide(), tex[ap->tex_no]->getPixelsHigh());   //�k�������O�̉摜�̑傫�����擾
    /*auto tex_size = Vec2(tex[func_box[func_no].tex_no]->getContentSize().width, tex[func_box[func_no].tex_no]->getContentSize().height);*/

    auto tex_size_x = Vec2(rect->x / tex_size.x, ( rect->x + rect->width  ) / tex_size.x);
    auto tex_size_y = Vec2(rect->y / tex_size.y, ( rect->y + rect->height ) / tex_size.y);

    kmVec2Fill(&uv[0], tex_size_x.x, tex_size_y.y);     //����
    kmVec2Fill(&uv[1], tex_size_x.x, tex_size_y.x);     //����
    kmVec2Fill(&uv[2], tex_size_x.y, tex_size_y.y);     //�E��
    kmVec2Fill(&uv[3], tex_size_x.y, tex_size_y.x);     //�E��

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
            //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); // src = 1 �Œ�
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); // src = 1 �Œ�
            //glAlphaFunc(GL_GEQUAL, 1.0f);
            //glEnable(GL_ALPHA_TEST);
            break;

        case BLEND_MULTIPLE:
            break;

        case BLEND_NEG:
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
            break;
    }

    //render�ɏ���n��
    //DirectX��D3DPT_TRIANGLESTRIP��GL_TRIANGLE_STRIP�Ɏ��Ă���
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