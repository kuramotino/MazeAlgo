#pragma once
#include "Map.h"
#include "MiceStatus.h"
#include "MakePotential.h"
#include "Planning.h"
#include "IssueCommand.h"
#include "InputData.h"
#include "MiceMgr.h"
#include "DebugView.h"
#include "ResetObj.h"

extern Algorizm::Map map_obj;
extern Algorizm::MakePotential potential_obj;
extern Algorizm::MiceStatus status_obj;
extern Algorizm::Planning plan_obj;
extern Algorizm::IssueCommand issue_obj;
extern MiceMgr mgr;
extern DebugView debugview;
extern ResetObj resetobj;

void InitAlgo();
void UpDataAlgo();
