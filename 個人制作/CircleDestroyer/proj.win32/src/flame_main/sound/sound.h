extern SINT32 SOUND_start(SINT8* file_name, bool loop, FLOAT vol);  //音の再生
extern void SOUND_stop(SINT32 audio_no);                            //音の停止
extern void SOUND_init(void);                                       //音関係のデータの初期化