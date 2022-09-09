#include "flame_include.h"

#define SWAP(type,a,b) { type work = a; a = b; b = work; }


/*
    基準値を選ぶ
*/
SINT32 select_pivot(PRI_DATA* array, SINT32 begin, SINT32 end)
{
    return array[(begin + end) / 2].pri;  // 中央の要素を基準値とする
}


void quick_sort(PRI_DATA* array, SINT32 begin, SINT32 end)
{
    SINT32 pivot = select_pivot(array, begin, end);
    SINT32 i = begin;
    SINT32 j = end;

    while (1) {
        while (array[i].pri < pivot) { ++i; }  // 基準値以上の値が見つかるまで右方向へ進めていく
        while (array[j].pri > pivot) { --j; }  // 基準値以下の値が見つかるまで左方向へ進めていく

        if (i >= j) { break; }  // 左右から進めてきたiとjがぶつかったらループを終える

        // 基準値の位置よりも左側にあり、基準値よりも大きい値 (array[i]) と、
        // 基準値の位置よりも右側にあり、基準値よりも小さい値 (array[j]) の
        // 位置関係を交換する。
        SWAP(PRI_DATA, array[i], array[j]);

        // 次回に備えて、注目点をずらす
        i++;
        j--;
    }


    // 基準値の位置より左側に要素が２つ以上あれば、
    // その部分についてクイックソートを再帰させる
    if (i - begin >= 2) {
        quick_sort(array, begin, i - 1);
    }

    // 基準値の位置より右側に要素が２つ以上あれば、
    // その部分についてクイックソートを再帰させる
    if (end - j >= 2) {
        quick_sort(array, j + 1, end);
    }
}

void SORT_main_start(PRI_DATA *data)
{
	//クイックソート
	/*quick_sort( data, 0, 9 );*/
    quick_sort( data, 0, DATA_MAX - 1 );
}