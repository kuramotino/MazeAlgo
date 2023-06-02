#pragma once
#define MAX_QUEUE_NUM 50
#include "Map.h"

namespace Algorizm
{
	//pos_queue構造体
	typedef struct POS_QUEUE
	{
		int x;
		int y;
	}POS;

	//queue構造体
	typedef struct QUEUE
	{
		int head;//データの最前列
		int tail;//データの最後尾
		POS pos[MAX_QUEUE_NUM];//pushされているデータ
	}QUEUE_T;

	class MakePotential
	{
		int DistMap[16][16] = {255};
		Map* map;

	public:
		void initQueue(QUEUE_T* queue);//queueの初期化
		void pushQueue_walk(QUEUE_T* queue, POS input);//queueのpush
		POS popQueue_walk(QUEUE_T* queue);//queueのpop
		void Init_Dist(void);//歩数マップの初期化を行う関数
		void DecideDist(int goal_size,POS* goal_pos);//歩数マップの更新を行う関数
		int RetDist(int x, int y);//歩数マップの値を返す関数
		void SetMap(Map* bu_map);//マップのセットを行う関数
	};
}
