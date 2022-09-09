//-----------------------------------------------------------------------------
//                
//							データの保存
//														programed by N-KAITO
//-----------------------------------------------------------------------------

#include    "../flame_include.h"

//----------------------------------------------------------------
//  データのセーブ関連
//----------------------------------------------------------------
void DATA_save(SINT32 type, SINT32* data)
{

    if (data == NULL)
    {
        return;
    }

    switch (type)
    {
    case 0:
        return;
        break;

    case DATA_SAVE:
        //データのセーブ
        userdefault->setIntegerForKey("save", *data);
        break;

    case DATA_LOAD:
        //データのロード
        //セーブデータがない場合0が返ってくる
        *data = userdefault->getIntegerForKey("save", 0);
        /**data = (SINT32)userdefault->getDataForKey("save");*/
        break;

    case DATA_INIT:
        *data = 0;
        break;

    }
}