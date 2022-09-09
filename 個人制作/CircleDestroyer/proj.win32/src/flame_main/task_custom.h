//---------------------------------------------------------------------
// 構造体定義
//---------------------------------------------------------------------





//メインとなる情報を記録
struct FUNC_CUE
{
	/*void (* func)(FUNC_DATA );*/
	TASK* prev;								//前のタスクのアドレス
	TASK* next;								//次のタスクのアドレス
	FUNC func;								//実行部の関数アドレス代入部
	FUNC drawfunc;							//draw命令を個別に持ちたい場合は関数のアドレスを代入
	SINT32 task_no;							//このタスクのNO
	SINT8 name[256];						//このタスクの名前
	bool use_flag;							//このタスクを使っているか使っていないかのフラグ
	FLOAT pos[XYZ];							//絶対座標
	FLOAT scale[XYZ];						//画像の大きさ
	SINT32 tex_no;							//テクスチャNO
	SINT32 pri;								//描画優先度
	PARTS_RECT* uv_rect;					//矩形情報
	SINT32 anime_no;						//アニメーションNO

	SINT32 task_type;						//タスクのタイプ

	//運動関連ワーク
	//運動関数が存在するわけではないので単なるワークとしても使用可能。
	FLOAT	vec[XYZ];						//速度
	FLOAT	acc[XYZ];						//加速度
	FLOAT	cen[XYZ];						//
	SINT32	px[4];							//変形スプライト表現用。４頂点の表示ズレ値
	SINT32	py[4];							//ここを使用するにはgrp_mode に USE_PXY をセット。
	SINT32  direct_pos[2][4];			//４頂点の座標を直接アサインして好きな形で表示するためのワーク
	FLOAT	keep[XYZ];						//移動目的地の座標
	FLOAT	keep_spd;						//目的地へのスピード					システム依存

	//回転角ワーク
	//ang[Z]のみスプライト描画に影響を与える。
	ANGLE	ang[XYZ];						//グラフィックの回転角度		
	ANGLE	ang_spd[XYZ];					//グラフィックの回転角度		
	ANGLE	ang_acc[XYZ];					//グラフィックの回転角度の加速度		
	ANGLE	angle[XYZ];						//角度ワーク
	FLOAT	fang[XYZ];						//角度（ラジアン	

	UINT8	blend_type;						//半透明の種類。	

	TASK* child[CHILD_MAX];					//子のタスクのアドレス	

	SINT16 base_color[4][4];

	//汎用ワーク
	//systemOZ本体から一切アクセスされないことが約束されている

	SINT32	work1[XYZPDE];						//汎用ワーク1	
	SINT32	work2[XYZPDE];						//汎用ワーク2	
	SINT32	work3[XYZPDE];						//汎用ワーク3	
	SINT32	work4[XYZPDE];						//汎用ワーク4	
	SINT32	work5[XYZPDE];						//汎用ワーク5	
	SINT32	work6[XYZPDE];						//汎用ワーク6	
	SINT32	work7[XYZPDE];						//汎用ワーク7	
	SINT32	work8[XYZPDE];						//汎用ワーク8	
	SINT32	work9[XYZPDE];						//汎用ワーク9	
	SINT32	workA[XYZPDE];						//汎用ワークA	
	SINT32	workB[XYZPDE];						//汎用ワークB	
	SINT32	workC[XYZPDE];						//汎用ワークC	
	SINT32	workD[XYZPDE];						//汎用ワークD	
	SINT32	workE[XYZPDE];						//汎用ワークE	
	SINT32	workF[XYZPDE];						//汎用ワークF	


	FLOAT	fwork1[XYZPDE];						//汎用ワーク1	
	FLOAT	fwork2[XYZPDE];						//汎用ワーク2	
	FLOAT	fwork3[XYZPDE];						//汎用ワーク3	
	FLOAT	fwork4[XYZPDE];						//汎用ワーク4	
	FLOAT	fwork5[XYZPDE];						//汎用ワーク5	
	FLOAT	fwork6[XYZPDE];						//汎用ワーク6	
	FLOAT	fwork7[XYZPDE];						//汎用ワーク7	
	FLOAT	fwork8[XYZPDE];						//汎用ワーク8	
	FLOAT	fwork9[XYZPDE];						//汎用ワーク9	

	SINT32* work_p[XYZPDE];					//ワークポインタ
	SINT8* work_pc_1[XYZPDE];					//ワークポインタ8bit
	void* work_p_void[XYZPDE];

};

