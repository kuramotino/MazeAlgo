#include "DebugView.h"
#include "DxLib.h"
#include "Mouse.h"

void DebugView::Initialize()
{
	isDrawDist = true;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			distview[i][j].x = dist_zero_x + dist_interval * i;
			distview[i][j].y = Mouse::getInstance()->WindowHeight - (dist_zero_y + dist_interval * j);
			distview[i][j].dist = my_potential->RetDist(i, j);
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			row_nodeview[i][j].dist = (my_potential->RetSaitanNode(i, j, true))->cost;
			row_nodeview[i][j].x = zero_x + dx / 2 + dx * j;
			row_nodeview[i][j].y = Mouse::getInstance()->WindowHeight - (zero_y + dy + dy * i);
			row_nodeview[i][j].isNoWall = (my_potential->RetSaitanNode(i, j, true))->isNoWall;

			column_nodeview[i][j].dist = (my_potential->RetSaitanNode(i, j, false))->cost;
			column_nodeview[i][j].x = zero_x + dx + dx * i;
			column_nodeview[i][j].y = Mouse::getInstance()->WindowHeight - (zero_y + dy / 2 + dy * j);
			column_nodeview[i][j].isNoWall = (my_potential->RetSaitanNode(i, j, false))->isNoWall;
		}
	}
}

void DebugView::Update()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			distview[i][j].dist = my_potential->RetDist(i, j);
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			row_nodeview[i][j].dist = (my_potential->RetSaitanNode(i, j, true))->cost;
			row_nodeview[i][j].isNoWall = (my_potential->RetSaitanNode(i, j, true))->isNoWall;
			column_nodeview[i][j].dist = (my_potential->RetSaitanNode(i, j, false))->cost;
			column_nodeview[i][j].isNoWall = (my_potential->RetSaitanNode(i, j, false))->isNoWall;
		}
	}

	int x, y;
	Dir dir;
	my_status->RetPos(&x, &y, &dir);
	posview.pos_x = x;
	posview.pos_y = y;
	posview.micevec = dir;
}

void DebugView::Draw()
{
	int White = GetColor(255, 255, 255);
	if (isDrawDist)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (distview[i][j].dist / 1000 != 0)
				{
					DrawFormatString(distview[i][j].x - charsize - charsize / 2, distview[i][j].y, White, "%d", distview[i][j].dist);
				}
				else if (distview[i][j].dist / 100 != 0)
				{
					DrawFormatString(distview[i][j].x - charsize, distview[i][j].y, White, "%d", distview[i][j].dist);
				}
				else if (distview[i][j].dist / 10 != 0)
				{
					DrawFormatString(distview[i][j].x - charsize / 2, distview[i][j].y, White, "%d", distview[i][j].dist);
				}
				else
				{
					DrawFormatString(distview[i][j].x, distview[i][j].y, White, "%d", distview[i][j].dist);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (row_nodeview[i][j].isNoWall)
				{
					if (row_nodeview[i][j].dist / 10000 != 0)
					{
						DrawFormatString(row_nodeview[i][j].x - 2 * charsize, row_nodeview[i][j].y, White, "%d", row_nodeview[i][j].dist);
					}
					else if (row_nodeview[i][j].dist / 1000 != 0)
					{
						DrawFormatString(row_nodeview[i][j].x - charsize - charsize / 2, row_nodeview[i][j].y, White, "%d", row_nodeview[i][j].dist);
					}
					else if (row_nodeview[i][j].dist / 100 != 0)
					{
						DrawFormatString(row_nodeview[i][j].x - charsize, row_nodeview[i][j].y, White, "%d", row_nodeview[i][j].dist);
					}
					else if (row_nodeview[i][j].dist / 10 != 0)
					{
						DrawFormatString(row_nodeview[i][j].x - charsize / 2, row_nodeview[i][j].y, White, "%d", row_nodeview[i][j].dist);
					}
					else
					{
						DrawFormatString(row_nodeview[i][j].x, row_nodeview[i][j].y, White, "%d", row_nodeview[i][j].dist);
					}
				}

				if (column_nodeview[i][j].isNoWall)
				{
					if (column_nodeview[i][j].dist / 10000 != 0)
					{
						DrawFormatString(column_nodeview[i][j].x - 2 * charsize, column_nodeview[i][j].y, White, "%d", column_nodeview[i][j].dist);
					}
					else if (column_nodeview[i][j].dist / 1000 != 0)
					{
						DrawFormatString(column_nodeview[i][j].x - charsize - charsize / 2, column_nodeview[i][j].y, White, "%d", column_nodeview[i][j].dist);
					}
					else if (column_nodeview[i][j].dist / 100 != 0)
					{
						DrawFormatString(column_nodeview[i][j].x - charsize, column_nodeview[i][j].y, White, "%d", column_nodeview[i][j].dist);
					}
					else if (column_nodeview[i][j].dist / 10 != 0)
					{
						DrawFormatString(column_nodeview[i][j].x - charsize / 2, column_nodeview[i][j].y, White, "%d", column_nodeview[i][j].dist);
					}
					else
					{
						DrawFormatString(column_nodeview[i][j].x, column_nodeview[i][j].y, White, "%d", column_nodeview[i][j].dist);
					}
				}
			}
		}
	}
	DrawFormatString(pos_zero_x, pos_zero_y, White, "x=%d", posview.pos_x);
	DrawFormatString(pos_zero_x+pos_interval, pos_zero_y, White, "y=%d", posview.pos_y);
	switch (posview.micevec)
	{
	case North:
		DrawFormatString(pos_zero_x + pos_interval * 2, pos_zero_y, White, "N", posview.micevec);
		break;

	case East:
		DrawFormatString(pos_zero_x + pos_interval * 2, pos_zero_y, White, "E", posview.micevec);
		break;

	case South:
		DrawFormatString(pos_zero_x + pos_interval * 2, pos_zero_y, White, "S", posview.micevec);
		break;

	case West:
		DrawFormatString(pos_zero_x + pos_interval * 2, pos_zero_y, White, "W", posview.micevec);
		break;
	}
}

void DebugView::Finalize()
{

}

void DebugView::SetPotential(MakePotential* bu_potential)
{
	my_potential = bu_potential;
}

void DebugView::SetStatus(MiceStatus* bu_status)
{
	my_status = bu_status;
}