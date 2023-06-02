#pragma once
#include "Map.h"
#include "MiceStatus.h"
#include "IssueCommand.h"
#include "MiceObj.h"
#include "ButtonMgr.h"

class ResetObj
{
	Map* map;
	MiceStatus* status;
	IssueCommand* issue;
	MiceObj* miceobj;
	ButtonMgr* bmgr;

public: 
	void SetObj(Map* bumap, MiceStatus* bustatus, IssueCommand* buissue, MiceObj* bumiceobj, ButtonMgr* bubmgr);
	void PollingStop();
};
