//---------------------------------------------------------------------
// �\���̒�`
//---------------------------------------------------------------------





//���C���ƂȂ�����L�^
struct FUNC_CUE
{
	/*void (* func)(FUNC_DATA );*/
	TASK* prev;								//�O�̃^�X�N�̃A�h���X
	TASK* next;								//���̃^�X�N�̃A�h���X
	FUNC func;								//���s���̊֐��A�h���X�����
	FUNC drawfunc;							//draw���߂��ʂɎ��������ꍇ�͊֐��̃A�h���X����
	SINT32 task_no;							//���̃^�X�N��NO
	SINT8 name[256];						//���̃^�X�N�̖��O
	bool use_flag;							//���̃^�X�N���g���Ă��邩�g���Ă��Ȃ����̃t���O
	FLOAT pos[XYZ];							//��΍��W
	FLOAT scale[XYZ];						//�摜�̑傫��
	SINT32 tex_no;							//�e�N�X�`��NO
	SINT32 pri;								//�`��D��x
	PARTS_RECT* uv_rect;					//��`���
	SINT32 anime_no;						//�A�j���[�V����NO

	SINT32 task_type;						//�^�X�N�̃^�C�v

	//�^���֘A���[�N
	//�^���֐������݂���킯�ł͂Ȃ��̂ŒP�Ȃ郏�[�N�Ƃ��Ă��g�p�\�B
	FLOAT	vec[XYZ];						//���x
	FLOAT	acc[XYZ];						//�����x
	FLOAT	cen[XYZ];						//
	SINT32	px[4];							//�ό`�X�v���C�g�\���p�B�S���_�̕\���Y���l
	SINT32	py[4];							//�������g�p����ɂ�grp_mode �� USE_PXY ���Z�b�g�B
	SINT32  direct_pos[2][4];			//�S���_�̍��W�𒼐ڃA�T�C�����čD���Ȍ`�ŕ\�����邽�߂̃��[�N
	FLOAT	keep[XYZ];						//�ړ��ړI�n�̍��W
	FLOAT	keep_spd;						//�ړI�n�ւ̃X�s�[�h					�V�X�e���ˑ�

	//��]�p���[�N
	//ang[Z]�̂݃X�v���C�g�`��ɉe����^����B
	ANGLE	ang[XYZ];						//�O���t�B�b�N�̉�]�p�x		
	ANGLE	ang_spd[XYZ];					//�O���t�B�b�N�̉�]�p�x		
	ANGLE	ang_acc[XYZ];					//�O���t�B�b�N�̉�]�p�x�̉����x		
	ANGLE	angle[XYZ];						//�p�x���[�N
	FLOAT	fang[XYZ];						//�p�x�i���W�A��	

	UINT8	blend_type;						//�������̎�ށB	

	TASK* child[CHILD_MAX];					//�q�̃^�X�N�̃A�h���X	

	SINT16 base_color[4][4];

	//�ėp���[�N
	//systemOZ�{�̂����؃A�N�Z�X����Ȃ����Ƃ��񑩂���Ă���

	SINT32	work1[XYZPDE];						//�ėp���[�N1	
	SINT32	work2[XYZPDE];						//�ėp���[�N2	
	SINT32	work3[XYZPDE];						//�ėp���[�N3	
	SINT32	work4[XYZPDE];						//�ėp���[�N4	
	SINT32	work5[XYZPDE];						//�ėp���[�N5	
	SINT32	work6[XYZPDE];						//�ėp���[�N6	
	SINT32	work7[XYZPDE];						//�ėp���[�N7	
	SINT32	work8[XYZPDE];						//�ėp���[�N8	
	SINT32	work9[XYZPDE];						//�ėp���[�N9	
	SINT32	workA[XYZPDE];						//�ėp���[�NA	
	SINT32	workB[XYZPDE];						//�ėp���[�NB	
	SINT32	workC[XYZPDE];						//�ėp���[�NC	
	SINT32	workD[XYZPDE];						//�ėp���[�ND	
	SINT32	workE[XYZPDE];						//�ėp���[�NE	
	SINT32	workF[XYZPDE];						//�ėp���[�NF	


	FLOAT	fwork1[XYZPDE];						//�ėp���[�N1	
	FLOAT	fwork2[XYZPDE];						//�ėp���[�N2	
	FLOAT	fwork3[XYZPDE];						//�ėp���[�N3	
	FLOAT	fwork4[XYZPDE];						//�ėp���[�N4	
	FLOAT	fwork5[XYZPDE];						//�ėp���[�N5	
	FLOAT	fwork6[XYZPDE];						//�ėp���[�N6	
	FLOAT	fwork7[XYZPDE];						//�ėp���[�N7	
	FLOAT	fwork8[XYZPDE];						//�ėp���[�N8	
	FLOAT	fwork9[XYZPDE];						//�ėp���[�N9	

	SINT32* work_p[XYZPDE];					//���[�N�|�C���^
	SINT8* work_pc_1[XYZPDE];					//���[�N�|�C���^8bit
	void* work_p_void[XYZPDE];

};

