//-----------------------------------------------------------------------------
//変数型定義
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
//  定数定義
//---------------------------------------------------------------------
#define WINDOW_WIDTH   (FLOAT)cocos2d::Director::getInstance()->getVisibleSize().width
#define WINDOW_HEIGHT  (FLOAT)cocos2d::Director::getInstance()->getVisibleSize().height

#define DATA_SAVE       1   //データのセーブ
#define DATA_LOAD       2   //データのロード
#define DATA_INIT       3   //データの初期化

//半透明の種類。
#define	BLEND_NORMAL		0				//通常合成
#define	BLEND_ADD			10				//加算半透明
#define	BLEND_SUB			30				//減算半透明
#define	BLEND_MULTIPLE		40
#define	BLEND_NEG			50				//ネガティブ反転

#define TASK_TYPE_GRP		0				//グラフィック表示タイプ
#define TASK_TYPE_PRG		1				//タスクを発生させるだけのタイプ


//pos指標用
#define	PX					0				//pos指標用x
#define	PY					1				//pos指標用y
#define	PZ					2				//pos指標用z
#define	PP					3				//pos指標用p->プライオリティ
#define	X					PX				//pos指標用x
#define	Y					PY				//pos指標用y
#define	Z					PZ				//pos指標用z
#define	P					PP				//pos指標用p->プライオリティ
#define	D					4
#define	E					5

//座標系データ幅
#define	XYZ					3				//座標系。
#define	XYZP				5				//座標系＋プライオリティ
#define	XYZPD				5				//座標系＋プライオリティ+実際の描画depth
#define	XYZPDE				6				//
#define	A_DATA				5				//アニメデータ系

#define CHILD_MAX           9               //子の最大値

//---------------------------------------------------------------------
//  typedef関連
//---------------------------------------------------------------------
typedef struct FUNC_CUE TASK;
typedef void (*FUNC)(TASK*);

