#pragma once
#include "MakePotential.h"
#include "Map.h"
#include "MiceStatus.h"

namespace Algorizm
{
	class Planning
	{
		int num;
		enum Vec ret;
		int x = 0;
		int y = 1;
		enum Dir MiceVec;
		int front_dist = 255;
		int back_dist = 255;
		int right_dist = 255;
		int left_dist = 255;
		int isLWall = 0;
		int isFWall = 0;
		int isRWall = 0;
		int min = 255;//0�ŏ��l
		bool isReturn = false;//�߂�T�����ǂ���
		bool isTansakuEnd = false;//�T�����I�����Ă��邩
		bool isSimEnd = false;//�o�H���o���I�����Ă��邩
		bool isTentativeTansakuEnd = true;//���̃S�[���ɒ��������ǂ���
		bool isEndAdatiSearch = false;//�����@�̒T�����I��������ォ�ǂ���
		POS Tentative_goal_pos = { 255,255 };//�ꎞ�I�ȃS�[�����W
		POS pass_unknown_pos = { 255,255 };//�p�X��̖��m���
		MiceStatus* my_status;
		MakePotential* my_potential;
		Map* my_map;
		STACK_T stack;//�ŒZ�o�H��̖��m��Ԃ��S�[���Ƃ��Ċi�[����X�^�b�N

	public:
		enum Vec Adati(int goal_size, POS* goal_pos);//�����@�ɑ����Ď��̍s����Ԃ��֐�
		enum Vec s_dijkstra(int goal_size, POS* goal_pos);//�_�C�N�X�g���@�ɑ����Ď��̍s����Ԃ��֐�
		enum Vec z_dijkstra();//�S�ʒT�����s���֐�
		void set_goal_pos();//goal��ݒ肷��֐�
		enum Vec search_unknown_dijkstra(int goal_size, POS* goal_pos);//�ŒZ�o�H��̖��m��Ԃ�T���ɍs���T���Ŏ��̍s����Ԃ��֐�
		void search_unknown_set_goal_pos(int goal_size, POS* goal_pos);//�ŒZ�o�H���v�Z���o�H��̖��m��Ԃ����ׂăX�^�b�N�ɂ���X�^�b�N���X�V����A���X�^�b�N����P��pop���A��������̃S�[���ɂ���
		void search_unknown_pop_goal_pos();//�X�^�b�N���玟�̃S�[����pop����֐�
		void BlockIsopos();//�Ǘ������Ԃ��֐�
		int saitan_dijkstra(int goal_size, POS* goal_pos, bool isMakePotential);//�΂߂̃_�C�N�X�g���@�ɑ����Ď��̍s����Ԃ��֐�
		void SetObj(MiceStatus* status, MakePotential* potential, Map* map);//�K�v�ȃI�u�W�F�N�g���Z�b�g����֐�
		void UpDataVecPos(enum Vec vec);//���ɐi�ތ���(���C�E�C�O�C��)����C���̈ʒu�C�������X�V����֐�
		void SetReturn(bool isreturn);//�߂�T���t���O���Z�b�g����֐�
		bool RetReturn();//�߂�T���t���O��Ԃ��֐�
		void SetTansakuEnd(bool istansakuend);//�T���I���t���O���Z�b�g����֐�
		bool RetTansakuEnd();//�T���I���t���O��Ԃ��֐�
		void BlockWall();//�ǂ��ӂ����֐�
		void MiceInit();//�@�̂̈ʒu����������������
		bool RetIsSimEnd();//�o�H���o���I�����Ă��邩�ǂ����̃t���O��Ԃ��֐�
	};
}