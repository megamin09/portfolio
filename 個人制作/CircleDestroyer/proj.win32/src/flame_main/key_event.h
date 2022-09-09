
//----------------------------------------------------------------
//　構造体定義
//----------------------------------------------------------------
typedef struct
{
	bool use_flag;
	SINT32 count;
}KEY_DATA;


//----------------------------------------------------------------
//　変数や定数定義
//----------------------------------------------------------------
#define	KEYNUM					256				//キーボードのボタン情報の数

extern KEY_DATA key_box[KEYNUM];


//----------------------------------------------------------------
//	関数
//----------------------------------------------------------------
//extern void KEY_count(void);
//extern SINT32 KEY_Inkey_DAT( SINT32 key_number );
//extern SINT32 KEY_Inkey_TRG(SINT32 key_number);
extern SINT32 TOUCH_TRG(void);                                      //タッチ瞬間かどうかの判定
extern void TOUCH_count(void);										//タッチした時間のカウント


//----------------------------------------------------------------
//	Cocoss2d-xでのキーコード
//----------------------------------------------------------------
#define KEY_ESCAPE					6
#define KEY_LEFT_ARROW				26
#define KEY_RIGHT_ARROW				27
#define KEY_UP_ARROW				28
#define KEY_DOWN_ARROW				29
#define KEY_F1						47
#define KEY_F2						48
#define KEY_F3						49
#define KEY_F4						50
#define KEY_F5						51
#define KEY_F6						52
#define KEY_F7						53
#define KEY_F8						54
#define KEY_F9						55
#define KEY_F10						56
#define KEY_F11						57
#define KEY_F12						58
#define KEY_0						76
#define KEY_1						77
#define KEY_2						78
#define KEY_3						79
#define KEY_4						80
#define KEY_5						81
#define KEY_6						82
#define KEY_7						83
#define KEY_8						84
#define KEY_9						85
#define KEY_A						124
#define KEY_B						125
#define KEY_C						126
#define KEY_D						127
#define KEY_E						128
#define KEY_F						129
#define KEY_G						130
#define KEY_H						131
#define KEY_I						132
#define KEY_J						133
#define KEY_K						134
#define KEY_L						135
#define KEY_M						136
#define KEY_N						137
#define KEY_O						138
#define KEY_P						139
#define KEY_Q						140
#define KEY_R						141
#define KEY_S						142
#define KEY_T						143
#define KEY_U						144
#define KEY_V						145
#define KEY_W						146
#define KEY_X						147
#define KEY_Y						148
#define KEY_Z						149
#define KEY_ENTER					164

//----------------------------------------------------------------
//	SystemOZでのキーコード
//----------------------------------------------------------------
#define DIK_ESCAPE          KEY_ESCAPE
#define DIK_1               KEY_1
#define DIK_2               KEY_2
#define DIK_3               KEY_3
#define DIK_4               KEY_4
#define DIK_5               KEY_5
#define DIK_6               KEY_6
#define DIK_7               KEY_7
#define DIK_8               KEY_8
#define DIK_9               KEY_9
#define DIK_0               KEY_O
#define DIK_Q               KEY_Q
#define DIK_W               KEY_W
#define DIK_E               KEY_E
#define DIK_R               KEY_R
#define DIK_T               KEY_T
#define DIK_Y               KEY_Y
#define DIK_U               KEY_U
#define DIK_I               KEY_I
#define DIK_O               KEY_O
#define DIK_P               KEY_P
#define DIK_RETURN          KEY_ENTER    /* Enter on main keyboard */
#define DIK_A               KEY_A  
#define DIK_S               KEY_S  
#define DIK_D               KEY_D  
#define DIK_F               KEY_F  
#define DIK_G               KEY_G  
#define DIK_H               KEY_H  
#define DIK_J               KEY_J  
#define DIK_K               KEY_K  
#define DIK_L               KEY_L  
#define DIK_Z               KEY_Z  
#define DIK_X               KEY_X  
#define DIK_C               KEY_C  
#define DIK_V               KEY_V  
#define DIK_B               KEY_B  
#define DIK_N               KEY_N  
#define DIK_M               KEY_M  
#define DIK_F1              KEY_F1 
#define DIK_F2              KEY_F2 
#define DIK_F3              KEY_F3 
#define DIK_F4              KEY_F4 
#define DIK_F5              KEY_F5 
#define DIK_F6              KEY_F6 
#define DIK_F7              KEY_F7 
#define DIK_F8              KEY_F8 
#define DIK_F9              KEY_F9 
#define DIK_F10             KEY_F10
#define DIK_F11             KEY_F11
#define DIK_F12             KEY_F12
#define DIK_F13             KEY_F13    /*                     (NEC PC98) */
#define DIK_F14             KEY_F14    /*                     (NEC PC98) */
#define DIK_F15             KEY_F15    /*                     (NEC PC98) */
#define DIK_UP              KEY_UP_ARROW	    /* UpArrow on arrow keypad */
#define DIK_LEFT            KEY_LEFT_ARROW	    /* LeftArrow on arrow keypad */
#define DIK_RIGHT           KEY_RIGHT_ARROW	    /* RightArrow on arrow keypad */
#define DIK_DOWN            KEY_DOWN_ARROW	    /* DownArrow on arrow keypad */


