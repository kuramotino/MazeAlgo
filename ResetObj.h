#pragma once
#include "Map.h"
#include "MiceStatus.h"
#include "IssueCommand.h"
#include "MiceObj.h"
#include "ButtonMgr.h"
#include "MakePotential.h"
#include "DebugView.h"

class ResetObj
{
	Map* map;
	MiceStatus* status;
	IssueCommand* issue;
	MiceObj* miceobj;
	ButtonMgr* bmgr;
	MakePotential* potential;
	DebugView* view;

public: 
	void SetObj(Map* bumap, MiceStatus* bustatus, IssueCommand* buissue, MiceObj* bumiceobj, ButtonMgr* bubmgr, MakePotential* bupotential, DebugView* buview);
	void PollingStop();
};
