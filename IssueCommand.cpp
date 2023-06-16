#include "InitAlgo.h"
#include "DebugView.h"

namespace Algorizm
{
	void IssueCommand::Init()
	{
		isStart = false;
		isStop = false;
		isStopSenkai = false;
		my_plan->SetReturn(false);
		my_plan->SetTansakuEnd(false);
	}

	void IssueCommand::Tansaku()
	{
		if (!isStart)
		{
			my_micemgr->SetAct(Stra);
			isStart = true;
		}
		if (my_micemgr->RetKasokuEnd()==true && !isStop && isStart && !my_micemgr->RetStartPause())
		{
			//nextVec = (!my_plan->RetReturn()) ? my_plan->Adati(4, goal_pos) : my_plan->Adati(1, start_pos);
			nextVec = (!my_plan->RetReturn()) ? my_plan->Adati(4, goal_pos) : my_plan->s_dijkstra(1, start_pos);
			switch (nextVec)
			{
			case Left:
				my_micemgr->SetAct(Left_sla);
				break;

			case Front:
				my_micemgr->SetAct(Stra);
				break;

			case Right:
				my_micemgr->SetAct(Right_sla);
				break;

			case Back:
				my_micemgr->SetAct(Right_sen);
				break;
			}
			isStop = my_plan->RetTansakuEnd();
		}
		if (my_micemgr->RetKasokuEnd() == true && isStop && !isStopSenkai && !my_micemgr->RetStartPause())
		{
			my_micemgr->SetAct(Right_sen);
			isStopSenkai = true;
		}
	}

	void IssueCommand::Saitan()
	{
		if (my_micemgr->RetKasokuEnd() == true && isStopSenkai)
		{
			debugview.isDrawDist = false;
			my_plan->BlockWall();
			int nextpass = my_plan->saitan_dijkstra(4, goal_pos);
		}
	}

	void IssueCommand::SetPlanMgr(Planning* plan,MiceMgr* bu_mgr)
	{
		my_plan = plan;
		my_micemgr = bu_mgr;
	}
}