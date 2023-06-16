#include "ResetObj.h"

void ResetObj::SetObj(Map* bumap, MiceStatus* bustatus, IssueCommand* buissue, MiceObj* bumiceobj, ButtonMgr* bubmgr, MakePotential* bupotential ,DebugView* buview)
{
	map = bumap;
	status = bustatus;
	issue = buissue;
	miceobj = bumiceobj;
	bmgr = bubmgr;
	potential = bupotential;
	view = buview;
}

void ResetObj::PollingStop()
{
	if (bmgr->RetisStop())
	{
		map->Init_Row_Column();
		status->InitStatus();
		issue->Init();
		miceobj->Initialize();
		potential->init_knowmap();
		view->Initialize();
	}
}