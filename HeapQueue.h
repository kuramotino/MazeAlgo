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
		NODE DAT[MAX_HEAP_NUM];//ノード配列,1から使用する
		int now_node_num = 0;//現在キューに入っているノード数

	public:
		void up_heap(int root, int tail);//根だけが条件を満たさないヒープを再構築する関数
		void construction_heap();//ヒープを再構築する関数
		void push_heap(NODE node);//ヒープにプッシュする関数
		NODE pop_heap();//ヒープからポップする関数
	};
}
