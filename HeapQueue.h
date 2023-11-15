#pragma once
#define MAX_HEAP_NUM 255

namespace Algorizm
{
	enum saitan_node_dir { NN, NE, EE, SE, SS, SW, WW, NW };

	typedef struct Search_Node
	{
		int cost;//�m�[�h�̃R�X�g
		bool isConfirm;//�m�[�h���m�肵�Ă��邩�ǂ���
		int pos_x;//�m�[�h�̈ʒux
		int pos_y;//�m�[�h�̈ʒuy
		Search_Node* pre_node;//���g����ŒZ�o�H�Ɍq�����Ă���m�[�h�ւ̃|�C���^
		saitan_node_dir node_dir;//�ŒZ�o�H�Ɍq����m�[�h�ւ̕���
		bool isNoWall;//�ǂ����邩�ǂ���(true�Ńm�[�h���ӂ�����Ă��Ȃ��Cfalse�ŕǂɂӂ�����Ă���)
		bool isRow;//Row�m�[�h���ǂ���(true��row�Cfalse��column)
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
