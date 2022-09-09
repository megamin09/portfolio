#include "flame_include.h"

KEY_DATA key_box[KEYNUM];

//----------------------------------------------------------------
//  画面をタッチした瞬間の処理
//----------------------------------------------------------------
bool function_main::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	Vec2 location = pTouch->getLocation();
	log("onTouchBegan:(%f, %f)", location.x, WINDOW_HEIGHT - location.y);

	touch.touch_type = 1;
	touch.touch_x = location.x;
	touch.touch_y = WINDOW_HEIGHT - location.y;

	return true;
}

//----------------------------------------------------------------
//  画面をタッチしてスライドさせている時の処理
//----------------------------------------------------------------
void function_main::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	Vec2 location = pTouch->getLocation();
	log("onTouchMoved:(%f, %f)", location.x, WINDOW_HEIGHT - location.y);

	touch.touch_type = 2;
	touch.touch_x = location.x;
	touch.touch_y = WINDOW_HEIGHT - location.y;
}

//----------------------------------------------------------------
//  画面から指を話したときの処理
//----------------------------------------------------------------
void function_main::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	Vec2 location = pTouch->getLocation();
	log("onTouchEnded:(%f, %f)", location.x, location.y);
	touch.touch_type = 0;
}

//void function_main::Key_Event_Down(EventKeyboard::KeyCode keyCode, Event* event)
//{
//	SINT32 code_key = (SINT32)keyCode;
//	key_box[code_key].use_flag = TRUE;
//}
//
//void function_main::Key_Event_Up(EventKeyboard::KeyCode keyCode, Event* event)
//{
//	SINT32 code_key = (SINT32)keyCode;
//	key_box[code_key].use_flag = FALSE;
//}
//
//void KEY_count(void)
//{
//	SINT32 loop1;
//
//	for (loop1 = 0; loop1 < KEYNUM; loop1++)
//	{
//		if (key_box[loop1].use_flag != FALSE)
//		{
//			key_box[loop1].count++;
//		}
//		else
//		{
//			key_box[loop1].count = 0;
//		}
//	}
//}
//
//SINT32 KEY_Inkey_DAT(SINT32 key_number)
//{
//	if (key_box[key_number].count != 0)
//	{
//		return key_box[key_number].count;
//	}
//	return FALSE;
//}
//
//SINT32 KEY_Inkey_TRG(SINT32 key_number)
//{
//	if (key_box[key_number].count != 0 && key_box[key_number].count <= 1)
//	{
//		return TRUE;
//	}
//	return FALSE;
//}

//---------------------------------------------------------------------
//  タッチしている時間の更新
//---------------------------------------------------------------------
void TOUCH_count(void)
{
	if (touch.touch_type != 0)
	{
		touch.touch_time++;
	}
	else
	{
		touch.touch_time = 0;
	}
}

//---------------------------------------------------------------------
//  1回だけタッチしたかしてないかチェック
//---------------------------------------------------------------------
SINT32 TOUCH_TRG(void)
{
	if (touch.touch_time > 0 && touch.touch_time <= 1)
	{
		return 1;
	}
	return 0;
}