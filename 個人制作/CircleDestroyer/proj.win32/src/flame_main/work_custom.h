//-----------------------------------------------------------------------------
//�ϐ��^��`
//-----------------------------------------------------------------------------
#define	SINT64	long long
#define	SINT32	int
#define	SINT16	short int
#define	SINT8	char
#define	CHAR	char

#define	UINT64	unsigned long long 
#define	UINT32	unsigned int
#define	UINT16	unsigned short int
#define	UINT8	unsigned char

//#define	ANGLE	unsigned  short int	
//#define	ANGLE	int	
#define	ANGLE	int
#define	FLOAT	float
#define	DOUBLE	double

//---------------------------------------------------------------------
//  �萔��`
//---------------------------------------------------------------------
#define WINDOW_WIDTH   (FLOAT)cocos2d::Director::getInstance()->getVisibleSize().width
#define WINDOW_HEIGHT  (FLOAT)cocos2d::Director::getInstance()->getVisibleSize().height

#define DATA_SAVE       1   //�f�[�^�̃Z�[�u
#define DATA_LOAD       2   //�f�[�^�̃��[�h
#define DATA_INIT       3   //�f�[�^�̏�����

//�������̎�ށB
#define	BLEND_NORMAL		0				//�ʏ퍇��
#define	BLEND_ADD			10				//���Z������
#define	BLEND_SUB			30				//���Z������
#define	BLEND_MULTIPLE		40
#define	BLEND_NEG			50				//�l�K�e�B�u���]

#define TASK_TYPE_GRP		0				//�O���t�B�b�N�\���^�C�v
#define TASK_TYPE_PRG		1				//�^�X�N�𔭐������邾���̃^�C�v


//pos�w�W�p
#define	PX					0				//pos�w�W�px
#define	PY					1				//pos�w�W�py
#define	PZ					2				//pos�w�W�pz
#define	PP					3				//pos�w�W�pp->�v���C�I���e�B
#define	X					PX				//pos�w�W�px
#define	Y					PY				//pos�w�W�py
#define	Z					PZ				//pos�w�W�pz
#define	P					PP				//pos�w�W�pp->�v���C�I���e�B
#define	D					4
#define	E					5

//���W�n�f�[�^��
#define	XYZ					3				//���W�n�B
#define	XYZP				5				//���W�n�{�v���C�I���e�B
#define	XYZPD				5				//���W�n�{�v���C�I���e�B+���ۂ̕`��depth
#define	XYZPDE				6				//
#define	A_DATA				5				//�A�j���f�[�^�n

#define CHILD_MAX           9               //�q�̍ő�l

//---------------------------------------------------------------------
//  typedef�֘A
//---------------------------------------------------------------------
typedef struct FUNC_CUE TASK;
typedef void (*FUNC)(TASK*);

