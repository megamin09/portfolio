//------------------------------------------------------------
//  計算関係の関数まとめ
//------------------------------------------------------------

#include "../../flame_main/flame_include.h"
#include "../game_include.h"


//-------------------------------------------------------------------
//    基準値を選ぶ
//-------------------------------------------------------------------
SINT32 select_pivot(SINT32* array, SINT32 begin, SINT32 end)
{
    return array[(begin + end) / 2];  // 中央の要素を基準値とする
}

//-------------------------------------------------------------------
//	データのソート
//	クイックソート
//  array       データ
//  data_min    最小値
//  data_max    最大値
//  type        0 = 小さい順　1 = 大きい順
//-------------------------------------------------------------------
void CALCULATION_sort(SINT32* array, SINT32 data_min, SINT32 data_max, SINT32 type)
{
    SINT32 pivot = select_pivot(array, data_min, data_max);
    SINT32 i = data_min;
    SINT32 j = data_max;

    while (1) {

        if (type)
        {
            while (array[i] > pivot) { ++i; }  // 基準値以上の値が見つかるまで右方向へ進めていく
            while (array[j] < pivot) { --j; }  // 基準値以下の値が見つかるまで左方向へ進めていく
        }
        else
        {
            while (array[i] < pivot) { ++i; }  // 基準値以上の値が見つかるまで右方向へ進めていく
            while (array[j] > pivot) { --j; }  // 基準値以下の値が見つかるまで左方向へ進めていく
        }

        if (i >= j) { break; }  // 左右から進めてきたiとjがぶつかったらループを終える

        // 基準値の位置よりも左側にあり、基準値よりも大きい値 (array[i]) と、
        // 基準値の位置よりも右側にあり、基準値よりも小さい値 (array[j]) の
        // 位置関係を交換する。
        SWAP(SINT32, array[i], array[j]);

        // 次回に備えて、注目点をずらす
        i++;
        j--;
    }


    // 基準値の位置より左側に要素が２つ以上あれば、
    // その部分についてクイックソートを再帰させる
    if (i - data_min >= 2) {
        CALCULATION_sort(array, data_min, i - 1, type);
    }

    // 基準値の位置より右側に要素が２つ以上あれば、
    // その部分についてクイックソートを再帰させる
    if (data_max - j >= 2) {
        CALCULATION_sort(array, j + 1, data_max, type);
    }
}

//-------------------------------------------------------------------
//  大きい順から何番目の値を取得するか
//  array       データの配列
//  get_max     大きい順から何番目を取得するか
//-------------------------------------------------------------------
SINT32 CALCULATION_max_get(SINT32 array[], SINT32 get_max)
{
    SINT32 data[sizeof( array )];
    
    memcpy( data, array, sizeof( array ) * sizeof( SINT32 ) );
  
    CALCULATION_sort( data, 0, sizeof( array ) - 1, 1 );
    return data[get_max];
}
