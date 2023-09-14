#pragma once
#define MAX_QUEUE_NUM 50
#include "Map.h"
#include "HeapQueue.h"

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
		int isKnowMap[16] = {0};//ある区画が既知がどうか，(0のとき未知，1のとき既知)
		NODE search_node[16][16];//探索用のノード
		HeapQueue heap;//探索用のヒープ
		int search_edge_miti = 1;//未知区間のエッジの重み
		int search_edge_kiti = 5;//既知区間のエッジの重み
		NODE saitan_node_column[15][16];//最短用のノード
		NODE saitan_node_row[15][16];//最短用のノード
		NODE no_conect_node;//繋がらないノード
		int strate_edge_cost = 7;//7
		int diagonal_edge_cost = 5;//5
		int continue_st_edge_cost = 3;//3
		int continue_dag_edge_cost = 3;//3
		Map* map;

	public:
		void initQueue(QUEUE_T* queue);//queueの初期化
		void pushQueue_walk(QUEUE_T* queue, POS input);//queueのpush
		POS popQueue_walk(QUEUE_T* queue);//queueのpop
		void Init_Dist(void);//歩数マップの初期化を行う関数
		void DecideDist(int goal_size,POS* goal_pos);//歩数マップの更新を行う関数
		void InitSerch_Dist(void);//歩数マップの初期化を行う関数
		void search_dijkstra(int goal_size, POS* goal_pos);//探索ダイクストラ法の歩数マップ更新を行う関数
		int RetDist(int x, int y);//歩数マップの値を返す関数
		void SetMap(Map* bu_map);//マップのセットを行う関数
		void updata_knowmap(int x, int y);
		void init_knowmap();
		void init_search_node();
		NODE ret_search_node(int x, int y);//ある位置x,yにおけるノードを返す関数
		void init_saitan_node();
		void saitan_dijkstra(int goal_size, POS* goal_pos);//最短ダイクストラ法の歩数マップ更新を行う関数
		NODE* RetSaitanNode(int x, int y, bool isRow);//あるx,y,rowかcolumnか指定したときのノードを返す関数
		int CalEdgeCost(NODE* prenode,NODE* nownode);//あるノードに接続されたエッジのコストを計算する関数
		void SaitanPushNode(NODE* node, NODE* new_node, int edge_cost, saitan_node_dir dir);//あるノードをプッシュする関数
		void BlockKnowWall();//未知区間の壁をふさぐ関数
		int RetKnowMap(int x, int y);//ある位置x,yが既知かどうかを返す関数
		void SetKnowMap(int x, int y);//ある位置x,yの既知区画を変更する関数
	};
}
