extern void TASK_init(TASK* ap);                                    //�^�X�N�̏�����
extern TASK* search_sprite(void);                                   //�^�X�N�������ɗ]���Ă���ꏊ��T��
extern void TASK_end(TASK* ap);                                     //�^�X�N�̏I��
extern TASK* TASK_start(FUNC func, char name[256]);                 //�^�X�N�J�n���ȗ�����������
extern void TASK_func_exec(void);