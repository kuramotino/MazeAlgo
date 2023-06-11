#include "MakePotential.h"
#include "HeapQueue.h"

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

	void Algorizm::MakePotential::search_dijkstra(int goal_size,POS* goal_pos)
	{
		map->MapDecide();//壁情報の更新
		int now_x;
		int now_y;
		map->RetPos(&now_x, &now_y);
		updata_knowmap(now_x, now_y);//既知区間の更新
		//Init_Dist();//歩数マップの初期化
		init_search_node();//ノードの初期化

		POS bupos = { 0,0 };//新たに確定したノードの座標
		NODE new_confirm_node;//新たに確定したノード

		heap.init_heap();//1キューを初期化

		for (int i = 0; i < goal_size; i++)
		{
			DistMap[(goal_pos + i)->x][(goal_pos + i)->y] = 0;//goal座標を0にする
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			search_node[bupos.x][bupos.y].cost = 0;//スタートノードのコストを0にする
			search_node[bupos.x][bupos.y].isConfirm = true;//スタートノードを確定させる
			new_confirm_node = search_node[bupos.x][bupos.y];//スタートノードを新たに確定したノードとする
		}
		bool isFirst = true;
		int x = bupos.x;
		int y = bupos.y;

		while (heap.ret_node_num() != 0 || isFirst)
		{
			if (!isFirst)
			{
				if (heap.ret_node_num() != 0)
				{
					new_confirm_node = heap.pop_heap();//優先度付きキューから最小のコストを持つノードを取り出す
					bupos.x = new_confirm_node.pos_x;//確定したノードの座標を格納する
					bupos.y = new_confirm_node.pos_y;//確定したノードの座標を格納する
					x = bupos.x;
					y = bupos.y;
					new_confirm_node.isConfirm = true;//ノードを確定させる
					search_node[bupos.x][bupos.y] = new_confirm_node;
					DistMap[x][y] = new_confirm_node.cost;
				}
			}
			else
			{
				isFirst = false;
			}

			int edge_cost = ((isKnowMap[x] & (1 << y)) == (1 << y)) ? search_edge_kiti : search_edge_miti;
			//Popされた座標の周辺状況の確認
			if (x != 15 && map->isKnowWall(x, y, East) == 0)//1右端でなく、右壁なしのとき
			{
				if (search_node[x + 1][y].cost > search_node[x][y].cost + edge_cost && !search_node[x + 1][y].isConfirm)//確定したノードにつながっているノードのコストの更新
				{
					search_node[x + 1][y].cost = search_node[x][y].cost + edge_cost;
					search_node[x + 1][y].pre_node = &search_node[x][y];
					DistMap[x + 1][y] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x + 1][y].isConfirm)
				{
					heap.push_heap(search_node[x + 1][y]);//確定したノードにつながっているノードをキューにプッシュする
					DistMap[x + 1][y] = search_node[x + 1][y].cost;
				}
			}
			if (x != 0 && map->isKnowWall(x, y, West) == 0)//2左端でなく、左壁なしのとき
			{
				if (search_node[x - 1][y].cost > search_node[x][y].cost + edge_cost && !search_node[x - 1][y].isConfirm)//確定したノードにつながっているノードのコストの更新
				{
					search_node[x - 1][y].cost = search_node[x][y].cost + edge_cost;
					search_node[x - 1][y].pre_node = &search_node[x][y];
					DistMap[x - 1][y] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x - 1][y].isConfirm)
				{
					heap.push_heap(search_node[x - 1][y]);//確定したノードにつながっているノードをキューにプッシュする
					DistMap[x - 1][y] = search_node[x - 1][y].cost;
				}
			}
			if (y != 15 && map->isKnowWall(x, y, North) == 0)//3上端でなく、上壁なしのとき
			{
				if (search_node[x][y + 1].cost > search_node[x][y].cost + edge_cost && !search_node[x][y + 1].isConfirm)//確定したノードにつながっているノードのコストの更新
				{
					search_node[x][y + 1].cost = search_node[x][y].cost + edge_cost;
					search_node[x][y + 1].pre_node = &search_node[x][y];
					DistMap[x][y + 1] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x][y + 1].isConfirm)
				{
					heap.push_heap(search_node[x][y + 1]);//確定したノードにつながっているノードをキューにプッシュする
					DistMap[x][y + 1] = search_node[x][y + 1].cost;
				}
			}
			if (y != 0 && map->isKnowWall(x, y, South) == 0)//3下端でなく、下壁なしのとき
			{
				if (search_node[x][y - 1].cost > search_node[x][y].cost + edge_cost && !search_node[x][y - 1].isConfirm)//確定したノードにつながっているノードのコストの更新
				{
					search_node[x][y - 1].cost = search_node[x][y].cost + edge_cost;
					search_node[x][y - 1].pre_node = &search_node[x][y];
					DistMap[x][y - 1] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x][y - 1].isConfirm)
				{
					heap.push_heap(search_node[x][y - 1]);//確定したノードにつながっているノードをキューにプッシュする
					DistMap[x][y - 1] = search_node[x][y - 1].cost;
				}
			}
		}
	}

	void Algorizm::MakePotential::init_search_node()
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				search_node[i][j].cost = 999;
				search_node[i][j].isConfirm = false;
				search_node[i][j].pos_x = i;
				search_node[i][j].pos_y = j;
				search_node[i][j].pre_node = &search_node[i][j];
			}
		}
	}

	NODE Algorizm::MakePotential::ret_search_node(int x, int y)//ある位置x,yにおけるノードを返す関数
	{
		return search_node[x][y];
	}

}