#define STRING_MAX_DATA 256

#define FONT_NO_0 0xaf
#define FONT_NO_1 0xb0
#define FONT_NO_2 0xb1
#define FONT_NO_3 0xb2
#define FONT_NO_4 0xb3
#define FONT_NO_5 0xb4
#define FONT_NO_6 0xb5
#define FONT_NO_7 0xb6
#define FONT_NO_8 0xb7
#define FONT_NO_9 0xb8

//extern void font_test_exec(TASK* ap);
extern TASK* font_pop_start(FUNC prg_point, FLOAT point_x, FLOAT point_y, FLOAT font_size, FLOAT font_interval_x, FLOAT font_interval_y, SINT32* string);
extern TASK* font_pop_number(FUNC prg_point, FLOAT point_x, FLOAT point_y, FLOAT font_size, SINT32 number);
extern void font_pop_default(FLOAT point_x, FLOAT point_y, FLOAT font_size,  SINT32* string);