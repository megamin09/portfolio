extern void Texture_Load(SINT32 tex_no, SINT8 tex_name[256]);       //テクスチャのキャッシュを作成
extern void Texture_Release(SINT32 tex_no);                         //テクスチャの解放
extern void TEX_get_size(TASK* ap, FLOAT* x, FLOAT* y);             //テクスチャの大きさを取得
extern SINT32 HIT_rect_check(TASK* ap, FLOAT x, FLOAT y);           //点と四角の当たり判定を簡略化