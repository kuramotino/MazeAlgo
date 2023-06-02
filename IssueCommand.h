#pragma once
#include "Planning.h"
#include "MiceMgr.h"

namespace Algorizm
{
	class IssueCommand
	{
		Planning* my_plan;
		MiceMgr* my_micemgr;
		POS goal_pos[4] = { {7,7},{7,8},{8,7},{8,8} };
		POS start_pos[1] = { {0,0} };
		enum Vec nextVec;
		bool isStart = false;
		bool isStop = false;

	public:
		void Init();//状態を初期化する関数
		void Tansaku();//探索を行う関数
		void Saitan();//最短を行う関数
		void SetPlanMgr(Planning* plan,MiceMgr* bu_mgr);
	};
}
