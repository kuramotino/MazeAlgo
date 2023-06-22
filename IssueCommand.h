#pragma once
#include "Planning.h"
#include "MiceMgr.h"
#include "Pass_Generator.h"

namespace Algorizm
{
	class IssueCommand
	{
		Planning* my_plan;
		MiceMgr* my_micemgr;
		Pass_Generator* my_pass;
		POS goal_pos[4] = { {7,7},{7,8},{8,7},{8,8} };
		POS start_pos[1] = { {0,0} };
		enum Vec nextVec;
		bool isStart = false;
		bool isStop = false;
		bool isStopSenkai = false;
		bool isSetPass = false;

		bool isOneShot = true;//��x�݂̂�(sim�̂�)
		bool oneshot_flag = false;
		int cnt = 0;

	public:
		void Init();//��Ԃ�����������֐�
		void Tansaku();//�T�����s���֐�
		void Saitan();//�ŒZ���s���֐�
		void SetPlanMgr(Planning* plan,MiceMgr* bu_mgr);
		void SetPassGene(Pass_Generator* bu_pass);
		void TestAct();//����̃e�X�g���s���֐�
	};
}
