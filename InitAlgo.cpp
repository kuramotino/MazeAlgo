#include "Map.h"
#include "MiceStatus.h"
#include "MakePotential.h"
#include "Planning.h"
#include "IssueCommand.h"
#include "InputData.h"
#include "MiceMgr.h"
#include "InitAlgo.h"
#include "DebugView.h"

Algorizm::Map map_obj;
Algorizm::MakePotential potential_obj;
Algorizm::MiceStatus status_obj;
Algorizm::Planning plan_obj;
Algorizm::IssueCommand issue_obj;
MiceMgr mgr;
DebugView debugview;
ResetObj resetobj;

void InitAlgo()
{
	mgr.Initialize();
	map_obj.SetInputStatus(&(mgr.input), &status_obj);
	map_obj.Init_Row_Column();
	potential_obj.SetMap(&map_obj);
	plan_obj.SetObj(&status_obj, &potential_obj, &map_obj);
	issue_obj.SetPlanMgr(&plan_obj,&mgr);
	debugview.SetPotential(&potential_obj);
	debugview.SetStatus(&status_obj);
	debugview.Initialize();
	resetobj.SetObj(&map_obj, &status_obj, &issue_obj, &(mgr.miceObj), &(mgr.buttonMgr), &potential_obj);
}

void UpDataAlgo()
{
	mgr.Update();
	mgr.Draw();
	issue_obj.Tansaku();
	debugview.Update();
	debugview.Draw();
	resetobj.PollingStop();
}