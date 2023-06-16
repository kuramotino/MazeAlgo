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
			isKnowMap[x] = (sum_south >= 3) ? isKnowMap[x] | (1 << (y - 1)) : isKnowMap[x];
		}
		if (y != 15)
		{
			int sum_north = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_north+=map->isKnowWall(x, y + 1, (Dir)i);
			}
			isKnowMap[x] = (sum_north >= 3) ? isKnowMap[x] | (1 << (y + 1)) : isKnowMap[x];
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
			heap.push_heap(search_node[bupos.x][bupos.y]);//スタートノードをキューにプッシュする
		}
		int x = bupos.x;
		int y = bupos.y;

		while (heap.ret_node_num() != 0)
		{
			if (heap.ret_node_num() != 0)
			{
				new_confirm_node = heap.pop_heap();//優先度付きキューから最小のコストを持つノードを取り出す
				bupos.x = new_confirm_node.pos_x;//確定したノードの座標を格納する
				bupos.y = new_confirm_node.pos_y;//確定したノードの座標を格納する
				x = bupos.x;
				y = bupos.y;
				if (!search_node[x][y].isConfirm)
				{
					new_confirm_node.isConfirm = true;//ノードを確定させる
					search_node[bupos.x][bupos.y] = new_confirm_node;
					DistMap[x][y] = new_confirm_node.cost;
				}
				else
				{
					continue;
				}
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

	void Algorizm::MakePotential::init_saitan_node()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				saitan_node_row[i][j].cost = 999;
				saitan_node_row[i][j].isConfirm = false;
				saitan_node_row[i][j].pos_x = i;
				saitan_node_row[i][j].pos_y = j;
				saitan_node_row[i][j].pre_node = &search_node[i][j];
				saitan_node_row[i][j].isNoWall = !(map->isExistRowColumn(i, j, true));
				saitan_node_row[i][j].isRow = true;
				saitan_node_row[i][j].node_dir = NN;

				saitan_node_column[i][j].cost = 999;
				saitan_node_column[i][j].isConfirm = false;
				saitan_node_column[i][j].pos_x = i;
				saitan_node_column[i][j].pos_y = j;
				saitan_node_column[i][j].pre_node = &search_node[i][j];
				saitan_node_column[i][j].isNoWall = !(map->isExistRowColumn(i, j, false));
				saitan_node_column[i][j].isRow = false;
				saitan_node_column[i][j].node_dir = NN;
			}
		}
	}

	void Algorizm::MakePotential::saitan_dijkstra(int goal_size, POS* goal_pos)//最短用のダイクストラ法
	{
		//map->MapDecide();//壁情報の更新
		//int now_x;
		//int now_y;
		//map->RetPos(&now_x, &now_y);
		//updata_knowmap(now_x, now_y);//既知区間の更新
		init_saitan_node();//ノードの初期化

		POS bupos = { 0,0 };//新たに確定したノードの座標
		NODE new_confirm_node;//新たに確定したノード

		heap.init_heap();//1キューを初期化

		for (int i = 0; i < goal_size; i++)
		{
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			saitan_node_column[bupos.x][bupos.y].cost = 0;//スタートノードのコストを0にする
			if (saitan_node_column[bupos.x][bupos.y].isNoWall)
			{
				heap.push_heap(saitan_node_column[bupos.x][bupos.y]);//スタートノードをキューにプッシュする
			}

			saitan_node_row[bupos.y][bupos.x].cost = 0;//スタートノードのコストを0にする
			if (saitan_node_row[bupos.y][bupos.x].isNoWall)
			{
				heap.push_heap(saitan_node_row[bupos.y][bupos.x]);//スタートノードをキューにプッシュする
			}
		}
		bool isRow = false;
		int x = bupos.x;
		int y = bupos.y;

		while (heap.ret_node_num() != 0)
		{
			if (heap.ret_node_num() != 0)
			{
				new_confirm_node = heap.pop_heap();//優先度付きキューから最小のコストを持つノードを取り出す
				bupos.x = new_confirm_node.pos_x;//確定したノードの座標を格納する
				bupos.y = new_confirm_node.pos_y;//確定したノードの座標を格納する
				x = bupos.x;
				y = bupos.y;
				isRow = new_confirm_node.isRow;
				if (!((RetSaitanNode(x, y, isRow)->isConfirm)))
				{
					new_confirm_node.isConfirm = true;//ノードを確定させる
					*RetSaitanNode(x, y, isRow) = new_confirm_node;
				}
				else
				{
					continue;
				}
			}
			
			int edge_cost;
			saitan_node_dir pre_dir;
			//Popされた座標の周辺状況の確認
			if (RetSaitanNode(x, y, isRow)->isRow)//キューから取り出されたノードがRowのとき
			{
				if (RetSaitanNode(x + 1, y, true)->isNoWall)//北向きのとき
				{
					pre_dir = RetSaitanNode(x + 1, y, true)->node_dir;
					RetSaitanNode(x + 1, y, true)->node_dir = SS;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x + 1, y, true));
					SaitanPushNode(RetSaitanNode(x + 1, y, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y, x + 1, false)->isNoWall)//北東のとき
				{
					pre_dir = RetSaitanNode(y, x + 1, false)->node_dir;
					RetSaitanNode(y, x + 1, false)->node_dir = SW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x + 1, false));
					SaitanPushNode(RetSaitanNode(y, x + 1, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y, x, false)->isNoWall)//南東のとき
				{
					pre_dir = RetSaitanNode(y, x, false)->node_dir;
					RetSaitanNode(y, x, false)->node_dir = NW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x, false));
					SaitanPushNode(RetSaitanNode(y, x, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(x - 1, y, true)->isNoWall)//南のとき
				{
					pre_dir = RetSaitanNode(x - 1, y, true)->node_dir;
					RetSaitanNode(x - 1, y, true)->node_dir = NN;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x - 1, y, true));
					SaitanPushNode(RetSaitanNode(x - 1, y, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x, false)->isNoWall)//南西のとき
				{
					pre_dir = RetSaitanNode(y - 1, x, false)->node_dir;
					RetSaitanNode(y - 1, x, false)->node_dir = NE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x, false));
					SaitanPushNode(RetSaitanNode(y - 1, x, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x + 1, false)->isNoWall)//北西のとき
				{
					pre_dir = RetSaitanNode(y - 1, x + 1, false)->node_dir;
					RetSaitanNode(y - 1, x + 1, false)->node_dir = SE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x + 1, false));
					SaitanPushNode(RetSaitanNode(y - 1, x + 1, false), &new_confirm_node, edge_cost, pre_dir);
				}
			}
			else//キューから取り出されたノードがColumnのとき
			{
				if (RetSaitanNode(y, x + 1, true)->isNoWall)//北東のとき
				{
					pre_dir = RetSaitanNode(y, x + 1, true)->node_dir;
					RetSaitanNode(y, x + 1, true)->node_dir = SW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x + 1, true));
					SaitanPushNode(RetSaitanNode(y, x + 1, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(x + 1, y, false)->isNoWall)//東のとき
				{
					pre_dir = RetSaitanNode(x + 1, y, false)->node_dir;
					RetSaitanNode(x + 1, y, false)->node_dir = WW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x + 1, y, false));
					SaitanPushNode(RetSaitanNode(x + 1, y, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x + 1, true)->isNoWall)//南東のとき
				{
					pre_dir = RetSaitanNode(y - 1, x + 1, true)->node_dir;
					RetSaitanNode(y - 1, x + 1, true)->node_dir = NW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x + 1, true));
					SaitanPushNode(RetSaitanNode(y - 1, x + 1, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x, true)->isNoWall)//南西のとき
				{
					pre_dir = RetSaitanNode(y - 1, x, true)->node_dir;
					RetSaitanNode(y - 1, x, true)->node_dir = NE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x, true));
					SaitanPushNode(RetSaitanNode(y - 1, x, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(x - 1, y, false)->isNoWall)//西のとき
				{
					pre_dir = RetSaitanNode(x - 1, y, false)->node_dir;
					RetSaitanNode(x - 1, y, false)->node_dir = EE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x - 1, y, false));
					SaitanPushNode(RetSaitanNode(x - 1, y, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y, x, true)->isNoWall)//北西のとき
				{
					pre_dir = RetSaitanNode(y, x, true)->node_dir;
					RetSaitanNode(y, x, true)->node_dir = SE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x, true));
					SaitanPushNode(RetSaitanNode(y, x, true), &new_confirm_node, edge_cost, pre_dir);
				}
			}
		}
	}

	NODE* Algorizm::MakePotential::RetSaitanNode(int x, int y, bool isRow)//あるx,y,rowかcolumnか指定したときのノードを返す関数
	{
		no_conect_node.isNoWall = false;
		
		if (isRow)
		{
			if (x < 0 || x > 14 || y < 0 || y > 15)
			{
				return &(no_conect_node);//ノードがその位置に存在しない場合
			}
			return &(saitan_node_row[x][y]);
		}
		else
		{
			if (x < 0 || x > 14 || y < 0 || y > 15)
			{
				return &(no_conect_node);//ノードがその位置に存在しない場合
			}
			return &(saitan_node_column[x][y]);
		}
	}

	int Algorizm::MakePotential::CalEdgeCost(NODE* prenode, NODE* nownode)//あるノードに接続されたエッジのコストを計算する関数
	{
		int ret;
		saitan_node_dir pre_dir = prenode->node_dir;
		saitan_node_dir now_dir = nownode->node_dir;
		if (now_dir == NN || now_dir == EE || now_dir == SS || now_dir == WW)
		{
			ret = (now_dir == pre_dir) ? continue_st_edge_cost : strate_edge_cost;
		}
		else
		{
			ret = (now_dir == pre_dir) ? continue_dag_edge_cost : diagonal_edge_cost;
		}
		return ret;
	}

	void Algorizm::MakePotential::SaitanPushNode(NODE* node, NODE* new_node, int edge_cost, saitan_node_dir predir)//あるノードをプッシュする関数
	{
		if (node->cost > new_node->cost + edge_cost && !node->isConfirm)//確定したノードにつながっているノードのコストの更新
		{
			node->cost = new_node->cost + edge_cost;
			node->pre_node = new_node;
			heap.push_heap(*node);//確定したノードにつながっているノードをキューにプッシュする
		}
		else
		{
			node->node_dir = predir;
		}
	}

	void Algorizm::MakePotential::BlockKnowWall()//未知区間の壁をふさぐ関数
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if ((isKnowMap[i] & (1<<j)) != (1<<j))
				{
					map->BlockWall(i, j);
				}
			}
		}
	}
}