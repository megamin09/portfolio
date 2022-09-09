//-----------------------------------------------------------------------------
//							デバッグ関係
//														programed by N-KAITO
//-----------------------------------------------------------------------------

#include    "../flame_include.h"

SINT32 debug_box[2][30] = {
    { 0xcf, 0xbc, 0xce, 0xc6, 0xfe, 0xff },
    { 0x00 },
};

//-----------------------------------------------------------------------------
//  デバッグシステムの表示
//-----------------------------------------------------------------------------
void DEBUG_system_change(void)
{
    SINT32 task_text[10];
    SINT32 task_num = task_amount - 1;
    SINT32 number = 10000;
    SINT32 work;
    SINT32 loop1;

    for (loop1 = 0; debug_box[0][loop1] != 0xff; loop1++)
    {
        debug_box[1][loop1] = debug_box[0][loop1];
    }

    do
    {
        work = task_num / number;
        debug_box[1][loop1] = work + FONT_NO_0;
        task_num %= number;
        number /= 10;
        loop1++;
    } while (number > 0);

    debug_box[1][loop1] = 0xfd;
    loop1++;

    debug_box[1][loop1] = 0xc1;     //  F
    loop1++;
    debug_box[1][loop1] = 0xcb;     //  P
    loop1++;
    debug_box[1][loop1] = 0xce;     //  S
    loop1++;

    debug_box[1][loop1] = 0xfe;
    loop1++;
    debug_box[1][loop1] = 0xfe;
    loop1++;

    task_num = freame;
    number = 1000;

    do
    {
        work = task_num / number;
        debug_box[1][loop1] = work + FONT_NO_0;
        task_num %= number;
        number /= 10;
        loop1++;
    } while (number > 0);

    debug_box[1][loop1] = 0xff;
}

void DEBUG_system_exec(TASK* ap)
{
    DEBUG_system_change();
}

void DEBUG_system_start(void)
{
    TASK* ap;

    DEBUG_system_change();
    ap = font_pop_start(DEBUG_system_exec, WINDOW_WIDTH - 300.0f, WINDOW_HEIGHT - 100.0f, 0.7f, 1.0f, 1.0f, debug_box[1]);
    ap->pri = 1000;

}