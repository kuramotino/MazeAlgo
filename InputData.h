#pragma once
#include "MiceStatus.h"
using namespace Algorizm;

//壁情報や位置情報を保管するクラス
class InputData
{
	int SimRow[15];//シミュレータにセットされた壁情報
	int SimColume[15];//シミュレータにセットされた壁情報
public:
	int kabe_inf[3];//左と前と右の壁の有無

public:
	void SetRowColume(int i,int j,int on,bool isRow);
	void UpData_kabe_inf(int x, int y, enum Dir dir);
};
