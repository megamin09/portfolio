#include "flame_include.h"

#define SWAP(type,a,b) { type work = a; a = b; b = work; }


/*
    ��l��I��
*/
SINT32 select_pivot(PRI_DATA* array, SINT32 begin, SINT32 end)
{
    return array[(begin + end) / 2].pri;  // �����̗v�f����l�Ƃ���
}


void quick_sort(PRI_DATA* array, SINT32 begin, SINT32 end)
{
    SINT32 pivot = select_pivot(array, begin, end);
    SINT32 i = begin;
    SINT32 j = end;

    while (1) {
        while (array[i].pri < pivot) { ++i; }  // ��l�ȏ�̒l��������܂ŉE�����֐i�߂Ă���
        while (array[j].pri > pivot) { --j; }  // ��l�ȉ��̒l��������܂ō������֐i�߂Ă���

        if (i >= j) { break; }  // ���E����i�߂Ă���i��j���Ԃ������烋�[�v���I����

        // ��l�̈ʒu���������ɂ���A��l�����傫���l (array[i]) �ƁA
        // ��l�̈ʒu�����E���ɂ���A��l�����������l (array[j]) ��
        // �ʒu�֌W����������B
        SWAP(PRI_DATA, array[i], array[j]);

        // ����ɔ����āA���ړ_�����炷
        i++;
        j--;
    }


    // ��l�̈ʒu��荶���ɗv�f���Q�ȏ゠��΁A
    // ���̕����ɂ��ăN�C�b�N�\�[�g���ċA������
    if (i - begin >= 2) {
        quick_sort(array, begin, i - 1);
    }

    // ��l�̈ʒu���E���ɗv�f���Q�ȏ゠��΁A
    // ���̕����ɂ��ăN�C�b�N�\�[�g���ċA������
    if (end - j >= 2) {
        quick_sort(array, j + 1, end);
    }
}

void SORT_main_start(PRI_DATA *data)
{
	//�N�C�b�N�\�[�g
	/*quick_sort( data, 0, 9 );*/
    quick_sort( data, 0, DATA_MAX - 1 );
}