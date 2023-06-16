#pragma once
#include "SimTask.h"
#include "MakePotential.h"
#include "MiceStatus.h"

class DistView
{
public:
	int x;
	int y;
	int dist = 255;
};

class PosDirView
{
public:
	int pos_x;
	int pos_y;
	Dir micevec;
};

class NodeView
{
public:
	int x;
	int y;
	bool isNoWall;
	int dist = 999;
};

class DebugView : public SimTask
{
	DistView distview[16][16];
	PosDirView posview;
	NodeView row_nodeview[15][16];
	NodeView column_nodeview[15][16];
	MakePotential* my_potential;
	MiceStatus* my_status;
	int dist_zero_x = 42;
	int dist_zero_y = 55;
	int dist_interval = 34;
	int charsize = 8;
	int pos_zero_x = 600;
	int pos_zero_y = 500;
	int pos_interval = 30;
	int zero_x = 26;
	int zero_y = 38;
	int dx = 34;
	int dy = 34;
public:
	bool isDrawDist = true;

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void SetPotential(MakePotential* bu_potential);
	void SetStatus(MiceStatus* bu_status);
};