#pragma once
#define MAX_HEAP_NUM 255

namespace Algorizm
{
	typedef struct Search_Node
	{
		int cost;
		bool isConfirm;
		int pos_x;
		int pos_y;
		Search_Node* pre_node;
	}NODE;

	class HeapQueue
	{
		NODE DAT[MAX_HEAP_NUM];//�m�[�h�z��,1����g�p����
		int now_node_num = 0;//���݃L���[�ɓ����Ă���m�[�h��

	public:
		void init_heap();//�q�[�v������������֐�
		void up_heap(int root, int tail);//�������������𖞂����Ȃ��q�[�v���č\�z����֐�
		void construction_heap();//�q�[�v���č\�z����֐�
		void push_heap(NODE node);//�q�[�v�Ƀv�b�V������֐�
		NODE pop_heap();//�q�[�v����|�b�v����֐�
		int ret_node_num();//���݃L���[�ɓ����Ă���m�[�h����Ԃ��֐�
	};
}
