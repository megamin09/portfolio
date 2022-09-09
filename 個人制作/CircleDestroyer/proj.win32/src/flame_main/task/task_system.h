extern void TASK_init(TASK* ap);                                    //タスクの初期化
extern TASK* search_sprite(void);                                   //タスク生成時に余っている場所を探す
extern void TASK_end(TASK* ap);                                     //タスクの終了
extern TASK* TASK_start(FUNC func, char name[256]);                 //タスク開始を簡略化したもの
extern void TASK_func_exec(void);