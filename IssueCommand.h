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
		void Init();//ó‘Ô‚ğ‰Šú‰»‚·‚éŠÖ”
		void Tansaku();//’Tõ‚ğs‚¤ŠÖ”
		void Saitan();//Å’Z‚ğs‚¤ŠÖ”
		void SetPlanMgr(Planning* plan,MiceMgr* bu_mgr);
	};
}
