#include "DebugView.h"
#include "DxLib.h"
#include "Mouse.h"

void DebugView::Initialize()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			distview[i][j].x = dist_zero_x + dist_interval * i;
			distview[i][j].y = Mouse::getInstance()->WindowHeight - (dist_zero_y + dist_interval * j);
			distview[i][j].dist = my_potential->RetDist(i, j);
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
				DrawFormatString(distview[i][j].x-charsize, distview[i][j].y, White, "%d", distview[i][j].dist);
			}
			else if (distview[i][j].dist / 10 != 0)
			{
				DrawFormatString(distview[i][j].x-charsize/2, distview[i][j].y, White, "%d", distview[i][j].dist);
			}
			else
			{
				DrawFormatString(distview[i][j].x, distview[i][j].y, White, "%d", distview[i][j].dist);
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