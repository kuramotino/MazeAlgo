#include "ResetObj.h"

void ResetObj::SetObj(Map* bumap, MiceStatus* bustatus, IssueCommand* buissue, MiceObj* bumiceobj, ButtonMgr* bubmgr)
{
	map = bumap;
	status = bustatus;
	issue = buissue;
	miceobj = bumiceobj;
	bmgr = bubmgr;
}

void ResetObj::PollingStop()
{
	if (bmgr->RetisStop())
	{
		map->Init_Row_Column();
		status->InitStatus();
		issue->Init();
		miceobj->Initialize();
	}
}