#pragma once
#include "MiceStatus.h"
#include "InputData.h"
#include "Map.h"

namespace Algorizm
{
	enum Vec { Left, Front, Right, Back, Stop };
	class Map
	{
		int Row[15];//横列で左の添え字が下から何列目か、ビットが左から何番目か
		int Column[15];//横列で左の添え字が左から何列目か、ビットが下から何番目か
		int M_Row[15];//横列で左の添え字が下から何列目か、ビットが左から何番目か
		int M_Column[15];//横列で左の添え字が左から何列目か、ビットが下から何番目か
		int currentWall[3];//現在の左，前，右の壁の有無
		int current_x;
		int current_y;
		enum Dir current_vec;
		InputData* my_input;
		MiceStatus* my_status;

	public:
		void Init_Row_Column(void);//壁情報を初期化する関数
		void Updata_current(void);//InputDataから壁の有無を，MiceStatusから位置向きを得る
		void MapDecide(void);//マップ情報を更新する関数
		int isKnowWall(int x,int y,Dir wall_dir);//位置x,yのwall_dir方向の壁の有無を返す関数
		void isLFRKnowWall(int* l, int* f, int* r, int x, int y, enum Dir dir);//位置x,y,向きdirのときの左と前と右の壁の有無を調べる関数
		void SetInputStatus(InputData* input, MiceStatus* status);//InputとMiceStatusのオブジェクトをセットする
		void RetPos(int* x, int* y);
		bool isExistRowColumn(int x, int y, bool isRow);
		void BlockWall(int x, int y);//ある位置の壁をふさぐ関数
	};
}
