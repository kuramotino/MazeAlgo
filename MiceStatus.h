#pragma once

namespace Algorizm
{
	enum Dir {North,East,South,West};
	class MiceStatus
	{
		int PosX = 0;
		int PosY = 1;
		enum Dir MiceVec=North;//機体の向き(0が上、1が右、2が下、3が左)
		enum Dir PreMiceVec=North;//前回の機体の向き

	public:
		void InitStatus();//マウスの状態を初期化する関数
		void VecDecide(bool isRight);//向き決め関数
		void PosDecide(void);//位置決め関数
		bool GoalCheck(int goal_size, int x, int y);//ゴールしたかどうかを判定する関数
		void RetPos(int* x, int* y, enum Dir* dir);
		void SetPos(int x, int y, enum Dir dir);
	};
}