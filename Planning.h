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
		MiceStatus* my_status;
		MakePotential* my_potential;
		Map* my_map;

	public:
		enum Vec Adati(int goal_size, POS* goal_pos);//足立法に則って次の行動を返す関数
		void SetObj(MiceStatus* status, MakePotential* potential, Map* map);//必要なオブジェクトをセットする関数
		void UpDataVecPos(enum Vec vec);//次に進む向き(左，右，前，後)から，次の位置，向きを更新する関数
		void SetReturn(bool isreturn);//戻り探索フラグをセットする関数
		bool RetReturn();//戻り探索フラグを返す関数
		void SetTansakuEnd(bool istansakuend);//探索終了フラグをセットする関数
		bool RetTansakuEnd();//探索終了フラグを返す関数
	};
}