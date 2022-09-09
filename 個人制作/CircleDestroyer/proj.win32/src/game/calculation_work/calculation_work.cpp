//------------------------------------------------------------
//  �v�Z�֌W�̊֐��܂Ƃ�
//------------------------------------------------------------

#include "../../flame_main/flame_include.h"
#include "../game_include.h"


//-------------------------------------------------------------------
//    ��l��I��
//-------------------------------------------------------------------
SINT32 select_pivot(SINT32* array, SINT32 begin, SINT32 end)
{
    return array[(begin + end) / 2];  // �����̗v�f����l�Ƃ���
}

//-------------------------------------------------------------------
//	�f�[�^�̃\�[�g
//	�N�C�b�N�\�[�g
//  array       �f�[�^
//  data_min    �ŏ��l
//  data_max    �ő�l
//  type        0 = ���������@1 = �傫����
//-------------------------------------------------------------------
void CALCULATION_sort(SINT32* array, SINT32 data_min, SINT32 data_max, SINT32 type)
{
    SINT32 pivot = select_pivot(array, data_min, data_max);
    SINT32 i = data_min;
    SINT32 j = data_max;

    while (1) {

        if (type)
        {
            while (array[i] > pivot) { ++i; }  // ��l�ȏ�̒l��������܂ŉE�����֐i�߂Ă���
            while (array[j] < pivot) { --j; }  // ��l�ȉ��̒l��������܂ō������֐i�߂Ă���
        }
        else
        {
            while (array[i] < pivot) { ++i; }  // ��l�ȏ�̒l��������܂ŉE�����֐i�߂Ă���
            while (array[j] > pivot) { --j; }  // ��l�ȉ��̒l��������܂ō������֐i�߂Ă���
        }

        if (i >= j) { break; }  // ���E����i�߂Ă���i��j���Ԃ������烋�[�v���I����

        // ��l�̈ʒu���������ɂ���A��l�����傫���l (array[i]) �ƁA
        // ��l�̈ʒu�����E���ɂ���A��l�����������l (array[j]) ��
        // �ʒu�֌W����������B
        SWAP(SINT32, array[i], array[j]);

        // ����ɔ����āA���ړ_�����炷
        i++;
        j--;
    }


    // ��l�̈ʒu��荶���ɗv�f���Q�ȏ゠��΁A
    // ���̕����ɂ��ăN�C�b�N�\�[�g���ċA������
    if (i - data_min >= 2) {
        CALCULATION_sort(array, data_min, i - 1, type);
    }

    // ��l�̈ʒu���E���ɗv�f���Q�ȏ゠��΁A
    // ���̕����ɂ��ăN�C�b�N�\�[�g���ċA������
    if (data_max - j >= 2) {
        CALCULATION_sort(array, j + 1, data_max, type);
    }
}

//-------------------------------------------------------------------
//  �傫�������牽�Ԗڂ̒l���擾���邩
//  array       �f�[�^�̔z��
//  get_max     �傫�������牽�Ԗڂ��擾���邩
//-------------------------------------------------------------------
SINT32 CALCULATION_max_get(SINT32 array[], SINT32 get_max)
{
    SINT32 data[sizeof( array )];
    
    memcpy( data, array, sizeof( array ) * sizeof( SINT32 ) );
  
    CALCULATION_sort( data, 0, sizeof( array ) - 1, 1 );
    return data[get_max];
}
