#pragma once
#include "MakePotential.h"
#include "Map.h"
#include "MiceStatus.h"

namespace Algorizm
{
	class Planning
	{
		int num;
		enum Vec ret;
		int x = 0;
		int y = 1;
		enum Dir MiceVec;
		int front_dist = 255;
		int back_dist = 255;
		int right_dist = 255;
		int left_dist = 255;
		int isLWall = 0;
		int isFWall = 0;
		int isRWall = 0;
		int min = 255;//0最小値
		bool isReturn = false;//戻り探索かどうか
		bool isTansakuEnd = false;//探索が終了しているか
		bool isSimEnd = false;//経路導出が終了しているか
		bool isTentativeTansakuEnd = true;//仮のゴールに着いたかどうか
		bool isEndAdatiSearch = false;//足立法の探索が終わった直後かどうか
		POS Tentative_goal_pos = { 255,255 };//一時的なゴール座標
		POS pass_unknown_pos = { 255,255 };//パス上の未知区画
		MiceStatus* my_status;
		MakePotential* my_potential;
		Map* my_map;
		STACK_T stack;//最短経路上の未知区間をゴールとして格納するスタック

	public:
		enum Vec Adati(int goal_size, POS* goal_pos);//足立法に則って次の行動を返す関数
		enum Vec s_dijkstra(int goal_size, POS* goal_pos);//ダイクストラ法に則って次の行動を返す関数
		enum Vec z_dijkstra();//全面探索を行う関数
		void set_goal_pos();//goalを設定する関数
		enum Vec search_unknown_dijkstra(int goal_size, POS* goal_pos);//最短経路上の未知区間を探しに行く探索で次の行動を返す関数
		void search_unknown_set_goal_pos(int goal_size, POS* goal_pos);//最短経路を計算し経路上の未知区間をすべてスタックにいれスタックを更新する、又スタックから１つpopし、それを次のゴールにする
		void search_unknown_pop_goal_pos();//スタックから次のゴールをpopする関数
		void BlockIsopos();//孤立区画をつぶす関数
		int saitan_dijkstra(int goal_size, POS* goal_pos, bool isMakePotential);//斜めのダイクストラ法に則って次の行動を返す関数
		void SetObj(MiceStatus* status, MakePotential* potential, Map* map);//必要なオブジェクトをセットする関数
		void UpDataVecPos(enum Vec vec);//次に進む向き(左，右，前，後)から，次の位置，向きを更新する関数
		void SetReturn(bool isreturn);//戻り探索フラグをセットする関数
		bool RetReturn();//戻り探索フラグを返す関数
		void SetTansakuEnd(bool istansakuend);//探索終了フラグをセットする関数
		bool RetTansakuEnd();//探索終了フラグを返す関数
		void BlockWall();//壁をふさぐ関数
		void MiceInit();//機体の位置向きを初期化する
		bool RetIsSimEnd();//経路導出が終了しているかどうかのフラグを返す関数
	};
}