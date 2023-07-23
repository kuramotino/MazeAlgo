#include "InitAlgo.h"
#include "DebugView.h"
#include "Pass_Generator.h"

namespace Algorizm
{
	void IssueCommand::Init()
	{
		isStart = false;
		isStop = false;
		isStopSenkai = false;
		Stopcnt = 0;
		isSetPass = false;
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
			if (Stopcnt == 0)
			{
				my_micemgr->SetAct(Stra);
			}
			else if (Stopcnt == 1)
			{
				my_micemgr->SetAct(Right_sen);
			}

			if (Stopcnt == 1)
			{
				isStopSenkai = true;
			}
			Stopcnt++;
		}
	}

	void IssueCommand::Saitan()
	{
		if (my_micemgr->RetKasokuEnd() == true && isStopSenkai && !isSetPass)
		{
			debugview.isDrawDist = false;//斜めの歩数マップを表示させる(シミュレータでのみ呼ぶ)
			my_pass->M_Pass(4, goal_pos);//passの生成
			my_plan->MiceInit();
			my_pass->InitPassCount();
			isSetPass = true;
		}
		else if (my_micemgr->RetKasokuEnd() == true && isStopSenkai && isSetPass)
		{
			int nextpass = 0;
			nextpass = my_pass->DecodePass();
			if (nextpass != 0 && my_micemgr->RetKasokuEnd() == true && !my_micemgr->RetStartPause())
			{
				if (nextpass > 0)
				{
					my_micemgr->SetAct(Harf_Stra, nextpass);
				}
				else if (nextpass == -2)
				{
					my_micemgr->SetAct(Left_sla);
				}
				else if (nextpass == -3)
				{
					my_micemgr->SetAct(Right_sla);
				}
				else if (nextpass == -4)
				{
					my_micemgr->SetAct(Left_OO180);
				}
				else if (nextpass == -6)
				{
					my_micemgr->SetAct(Right_OO180);
				}
				else if (nextpass == -5)
				{
					my_micemgr->SetAct(Left_OO90);
				}
				else if (nextpass == -7)
				{
					my_micemgr->SetAct(Right_OO90);
				}
				else if (nextpass == -8)
				{
					my_micemgr->SetAct(Left_Diag_in45);
				}
				else if (nextpass == -9)
				{
					my_micemgr->SetAct(Right_Diag_in45);
				}
				else if (nextpass == -10)
				{
					my_micemgr->SetAct(Left_Diag_in135);
				}
				else if (nextpass == -11)
				{
					my_micemgr->SetAct(Right_Diag_in135);
				}
				else if (nextpass == -12)
				{
					my_micemgr->SetAct(Left_Diag_out45);
				}
				else if (nextpass == -13)
				{
					my_micemgr->SetAct(Right_Diag_out45);
				}
				else if (nextpass == -14)
				{
					my_micemgr->SetAct(Left_Diag_out135);
				}
				else if (nextpass == -15)
				{
					my_micemgr->SetAct(Right_Diag_out135);
				}
				else if (nextpass == -16)
				{
					my_micemgr->SetAct(Left_V90);
				}
				else if (nextpass == -17)
				{
					my_micemgr->SetAct(Right_V90);
				}
				else if (nextpass == -100)
				{
					my_micemgr->SetAct(Diag_Stra);
				}
			}
		}
	}

	void IssueCommand::SetPlanMgr(Planning* plan,MiceMgr* bu_mgr)
	{
		my_plan = plan;
		my_micemgr = bu_mgr;
	}

	void IssueCommand::SetPassGene(Pass_Generator* bu_pass)
	{
		my_pass = bu_pass;
	}

	void IssueCommand::TestAct()//動作のテストを行う関数
	{
		if (!isStart)
		{
			//my_micemgr->SetAct(Stra);
			//my_micemgr->SetAct(Right_sla);
			//my_micemgr->SetAct(Right_sen);


			isStart = true;
		}
		if (my_micemgr->RetKasokuEnd() == true && isStart && !my_micemgr->RetStartPause() && (!isOneShot || !oneshot_flag))
		{
			if (cnt == 0)
			{
				//my_micemgr->SetAct(Right_Diag_out45);
				//my_micemgr->SetAct(Right_OO90);
				//my_micemgr->SetAct(Left_Diag_out135);
			}
			else if (cnt == 1)
			{
				//my_micemgr->SetAct(Diag_Stra);
				my_micemgr->SetAct(Right_V90);
				//my_micemgr->SetAct(Left_Diag_out45);
				//my_micemgr->SetAct(Right_Diag_in135);
			}
			else if (cnt == 2)
			{
				//my_micemgr->SetAct(Diag_Stra);
				//my_micemgr->SetAct(Left_Diag_out45);
				//my_micemgr->SetAct(Left_V90);
			}
			cnt++;
			if (cnt == 3)
			{
				oneshot_flag = true;
			}
			
		}
	}

}