#pragma once
#include "MakePotential.h"
#define MAX_HEAP_NUM 50

namespace Algorizm
{
	typedef struct Search_Node
	{
		int cost;
		bool isConfirm;
		POS pos;
	}NODE;

	class HeapQueue
	{
		NODE DAT[MAX_HEAP_NUM];//�m�[�h�z��,1����g�p����
		int now_node_num = 0;//���݃L���[�ɓ����Ă���m�[�h��

	public:
		void up_heap(int root, int tail);//�������������𖞂����Ȃ��q�[�v���č\�z����֐�
		void construction_heap();//�q�[�v���č\�z����֐�
		void push_heap(NODE node);//�q�[�v�Ƀv�b�V������֐�
		NODE pop_heap();//�q�[�v����|�b�v����֐�
	};
}
