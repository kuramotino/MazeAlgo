#include "MakePotential.h"

namespace Algorizm
{
	void Algorizm::MakePotential::initQueue(QUEUE_T* queue)//queueの初期化
	{
		queue->head = 0;
		queue->tail = 0;
	}

	void Algorizm::MakePotential::pushQueue_walk(QUEUE_T* queue, POS input)//queueのpush
	{
		//1データをデータの最後尾の一つ後ろに格納
		queue->pos[queue->tail] = input;
		//2データの最後尾を一つ後ろに移動
		queue->tail = queue->tail + 1;
		//3巡回シフト
		if (queue->tail == MAX_QUEUE_NUM)
		{
			queue->tail = 0;
		}
		//4キューが満杯なら何もせずに関数終了
		if (queue->tail == queue->head)
		{
			return;
		}
	}

	POS Algorizm::MakePotential::popQueue_walk(QUEUE_T* queue)//queueのpop
	{
		POS ret = { 0,0 };

		//1キューが空なら何もせずに終了
		if (queue->tail == queue->head)
		{
			ret.x = 65535;
			return ret;
		}
		//2データの最前列からデータを取得
		ret = queue->pos[queue->head];
		//3データの最前列を一つ前にずらす
		queue->head = queue->head + 1;
		//4巡回シフト
		if (queue->head == MAX_QUEUE_NUM)
		{
			queue->head = 0;
		}
		//5取得したデータを返却
		return ret;
	}

	void Algorizm::MakePotential::Init_Dist(void)//歩数マップの初期化を行う関数
	{
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				DistMap[x][y] = 255;
			}
		}
	}

	void Algorizm::MakePotential::DecideDist(int goal_size, POS* goal_pos)//任意のゴール座標に対して歩数マップ更新を行う関数
	{
		map->MapDecide();//壁情報の更新
		int now_x;
		int now_y;
		map->RetPos(&now_x, &now_y);
		updata_knowmap(now_x, now_y);//既知区間の更新
		Init_Dist();//歩数マップの初期化

		QUEUE_T queue;
		POS bupos;
		initQueue(&queue);//1キューを初期化

		for (int i = 0; i < goal_size; i++)
		{
			DistMap[(goal_pos+i)->x][(goal_pos+i)->y] = 0;//goal座標を0にする
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			pushQueue_walk(&queue, bupos);//goal座標をスタックにpushする
		}

		int currnet_step = 0;

		while (1)
		{
			bupos = popQueue_walk(&queue);//キューから座標をpopする
			int x = bupos.x;
			int y = bupos.y;

			if (x == 65535)//キューが空なのに取り出そうとしたらbreak;
			{
				break;
			}
			if (DistMap[x][y] == currnet_step + 1)//popした座標の歩数が次のcountなら現在のカウントを++
			{
				currnet_step++;
			}
			if (currnet_step == 254)
			{
				break;
			}

			//Popされた座標の周辺状況の確認
			if (DistMap[x][y] == currnet_step)
			{
				if (x != 15 && DistMap[x + 1][y] == 255 && map->isKnowWall(x,y,East) == 0)//1右端でなく、探索済みでなく、右壁なしのとき
				{
					DistMap[x + 1][y] = currnet_step + 1;
					bupos.x = x + 1;
					bupos.y = y;
					pushQueue_walk(&queue, bupos);//代入した座標をキューにpushする
				}
				if (x != 0 && DistMap[x - 1][y] == 255 && map->isKnowWall(x, y, West) == 0)//2左端でなく、探索済みでなく、左壁なしのとき
				{
					DistMap[x - 1][y] = currnet_step + 1;
					bupos.x = x - 1;
					bupos.y = y;
					pushQueue_walk(&queue, bupos);//代入した座標をキューにpushする
				}
				if (y != 15 && DistMap[x][y + 1] == 255 && map->isKnowWall(x, y, North) == 0)//3上端でなく、探索済みでなく、上壁なしのとき
				{
					DistMap[x][y + 1] = currnet_step + 1;
					bupos.x = x;
					bupos.y = y + 1;
					pushQueue_walk(&queue, bupos);//代入した座標をキューにpushする
				}
				if (y != 0 && DistMap[x][y - 1] == 255 && map->isKnowWall(x, y, South) == 0)//3下端でなく、探索済みでなく、下壁なしのとき
				{
					DistMap[x][y - 1] = currnet_step + 1;
					bupos.x = x;
					bupos.y = y - 1;
					pushQueue_walk(&queue, bupos);//代入した座標をキューにpushする
				}
			}
		}
	}

	int Algorizm::MakePotential::RetDist(int x, int y)
	{
		return DistMap[x][y];
	}

	void Algorizm::MakePotential::SetMap(Map* bu_map)//マップのセットを行う関数
	{
		map = bu_map;
	}

	void Algorizm::MakePotential::updata_knowmap(int x, int y)//既知区間の更新，壁情報取得後に呼ばれる
	{
		isKnowMap[x] = isKnowMap[x] | (1 << y);
		if (x != 0)
		{
			int sum_west = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_west += map->isKnowWall(x - 1, y, (Dir)i);
			}
			isKnowMap[x - 1] = (sum_west >= 3) ? isKnowMap[x - 1] | (1 << y) : isKnowMap[x - 1];
		}
		if (x != 15)
		{
			int sum_east = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_east+=map->isKnowWall(x + 1, y, (Dir)i);
			}
			isKnowMap[x + 1] = (sum_east >= 3) ? isKnowMap[x + 1] | (1 << y) : isKnowMap[x + 1];
		}
		if (y != 0)
		{
			int sum_south = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_south+=map->isKnowWall(x, y - 1, (Dir)i);
			}
			isKnowMap[x] = (sum_south >= 3) ? isKnowMap[x] | (1 << y - 1) : isKnowMap[x];
		}
		if (y != 15)
		{
			int sum_north = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_north+=map->isKnowWall(x, y + 1, (Dir)i);
			}
			isKnowMap[x] = (sum_north >= 3) ? isKnowMap[x] | (1 << y + 1) : isKnowMap[x];
		}
	}

	void Algorizm::MakePotential::init_knowmap()
	{
		for (int i = 0; i < 16; i++)
		{
			isKnowMap[i] = 0;
		}
	}

	void Algorizm::MakePotential::search_dijkstra(int goal_size, POS* goal_pos)
	{

	}
}