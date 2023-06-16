#pragma once
#define MAX_HEAP_NUM 255

namespace Algorizm
{
	enum saitan_node_dir { NN, NE, EE, SE, SS, SW, WW, NW };

	typedef struct Search_Node
	{
		int cost;
		bool isConfirm;
		int pos_x;
		int pos_y;
		Search_Node* pre_node;
		saitan_node_dir node_dir;
		bool isNoWall;
		bool isRow;
	}NODE;

	class HeapQueue
	{
		NODE DAT[MAX_HEAP_NUM];//ノード配列,1から使用する
		int now_node_num = 0;//現在キューに入っているノード数

	public:
		void init_heap();//ヒープを初期化する関数
		void up_heap(int root, int tail);//根だけが条件を満たさないヒープを再構築する関数
		void construction_heap();//ヒープを再構築する関数
		void push_heap(NODE node);//ヒープにプッシュする関数
		NODE pop_heap();//ヒープからポップする関数
		int ret_node_num();//現在キューに入っているノード数を返す関数
	};
}
