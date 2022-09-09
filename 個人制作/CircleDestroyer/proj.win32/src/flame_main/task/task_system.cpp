//-----------------------------------------------------------------------------
//							�^�X�N�Ǘ��֌W
//														programed by N-KAITO
//-----------------------------------------------------------------------------

#include    "../flame_include.h"


//----------------------------------------------------------------
//  �^�X�N�̏�����
//----------------------------------------------------------------
void TASK_init(TASK* ap)
{
    memset(ap, 0, sizeof(TASK));

    ap->use_flag = true;
    ap->tex_no = 0;
    ap->pos[X] = 0.0f;
    ap->pos[Y] = 0.0f;
    ap->pos[Z] = 1.0f;
    ap->scale[X] = 1.0f;
    ap->scale[Y] = 1.0f;
    ap->scale[Z] = 1.0f;
    ap->base_color[0][0] = 255;
    ap->base_color[0][1] = 255;
    ap->base_color[0][2] = 255;
    ap->base_color[0][3] = 255;
}


//----------------------------------------------------------------
// �^�X�N�������ɗ]���Ă���ꏊ��T��
//----------------------------------------------------------------
TASK* search_sprite(void)
{
    SINT32 loop1 = 0;

    for (loop1 = 0; loop1 < DATA_MAX; loop1++)
    {
        if (func_box[loop1].use_flag != true)
        {
            TASK_init(&func_box[loop1]);
            func_box[loop1].task_no = loop1;
            return &func_box[loop1];
        }
    }

    return NULL;
}

//----------------------------------------------------------------
//  �^�X�N�𐶐����ĊJ�n������
//----------------------------------------------------------------
TASK* TASK_start(FUNC func, char name[256])
{
    TASK* ap = search_sprite();

    if (ap != NULL)
    {
        ap->func = func;
        strcpy(ap->name, name);
        task_amount++;
        return ap;
    }

    return NULL;
}

//----------------------------------------------------------------
//  �^�X�N�̍폜
//----------------------------------------------------------------
void TASK_end(TASK* ap)
{
    SINT32 loop1;
    SINT32 sprite_no = ap->task_no;

    //function�֘A�̃f���[�g    
    /*for (loop1 = sprite_no; loop1 < DATA_MAX; loop1++)
    {
        if (func_box[loop1].use_flag)
        {
            func_box[loop1] = func_box[loop1 + 1];
            func_box[loop1].task_no = loop1;
        }
        else
        {
            func_box[loop1 - 1] = func_box[loop1];
            break;
        }
    }*/

    memset(&func_box[sprite_no], 0, sizeof(TASK));
    func_box[sprite_no].pri = 99999;
    task_amount--;
}




//----------------------------------------------------------------
//  �^�X�N�̎��s
//----------------------------------------------------------------
void TASK_func_exec(void)
{
    for (func_no = 0; func_no < DATA_MAX; func_no++)
    {
        if (func_box[func_no].use_flag != false)
        {
            if (func_box[func_no].func != NULL)
                func_box[func_no].func(&func_box[func_no]);
        }
        pri_box[func_no].pri = func_box[func_no].pri;
        pri_box[func_no].task_no = func_no;
    }
}