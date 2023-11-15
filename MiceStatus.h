#pragma once

namespace Algorizm
{
	enum Dir {North,East,South,West};
	class MiceStatus
	{
		int PosX = 0;
		int PosY = 1;
		enum Dir MiceVec=North;//�@�̂̌���(0����A1���E�A2�����A3����)
		enum Dir PreMiceVec=North;//�O��̋@�̂̌���

	public:
		void InitStatus();//�}�E�X�̏�Ԃ�����������֐�
		void VecDecide(bool isRight);//�������ߊ֐�
		void PosDecide(void);//�ʒu���ߊ֐�
		bool GoalCheck(int goal_size, int x, int y);//�S�[���������ǂ����𔻒肷��֐�
		void RetPos(int* x, int* y, enum Dir* dir);
		void SetPos(int x, int y, enum Dir dir);
	};
}