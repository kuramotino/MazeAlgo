#include "InputData.h"

void InputData::SetRowColume(int i,int j,int on,bool isRow)
{
	if (isRow)
	{
		if (on == 1)
		{
			SimRow[i] = SimRow[i] | (1 << j);
		}
		else
		{
			SimRow[i] = SimRow[i] & (~(1 << j));
		}
	}
	else
	{
		if (on == 1)
		{
			SimColume[i] = SimColume[i] | (1 << j);
		}
		else
		{
			SimColume[i] = SimColume[i] & (~(1 << j));
		}
	}
}

void InputData::UpData_kabe_inf(int x, int y, enum Dir dir)
{
	switch (dir)
	{
	case North:
		if (x != 0)
		{
			kabe_inf[0] = (SimColume[x - 1] & (1 << y)) >> y;
		}
		else
		{
			kabe_inf[0] = 1;
		}
		if (x != 15)
		{
			kabe_inf[2] = (SimColume[x] & (1 << y)) >> y;
		}
		else
		{
			kabe_inf[2] = 1;
		}
		if (y != 15)
		{
			kabe_inf[1] = (SimRow[y] & (1 << x)) >> x;
		}
		else
		{
			kabe_inf[1] = 1;
		}
		break;
		
	case East:
		if (x != 15)
		{
			kabe_inf[1] = (SimColume[x] & (1 << y)) >> y;
		}
		else
		{
			kabe_inf[1] = 1;
		}
		if (y != 0)
		{
			kabe_inf[2] = (SimRow[y - 1] & (1 << x)) >> x;
		}
		else
		{
			kabe_inf[2] = 1;
		}
		if (y != 15)
		{
			kabe_inf[0] = (SimRow[y] & (1 << x)) >> x;
		}
		else
		{
			kabe_inf[0] = 1;
		}
		break;

	case South:
		if (x != 0)
		{
			kabe_inf[2] = (SimColume[x - 1] & (1 << y)) >> y;
		}
		else
		{
			kabe_inf[2] = 1;
		}
		if (x != 15)
		{
			kabe_inf[0] = (SimColume[x] & (1 << y)) >> y;
		}
		else
		{
			kabe_inf[0] = 1;
		}
		if (y != 0)
		{
			kabe_inf[1] = (SimRow[y - 1] & (1 << x)) >> x;
		}
		else
		{
			kabe_inf[1] = 1;
		}
		break;

	case West:
		if (x != 0)
		{
			kabe_inf[1] = (SimColume[x - 1] & (1 << y)) >> y;
		}
		else
		{
			kabe_inf[1] = 1;
		}
		if (y != 0)
		{
			kabe_inf[0] = (SimRow[y - 1] & (1 << x)) >> x;
		}
		else
		{
			kabe_inf[0] = 1;
		}
		if (y != 15)
		{
			kabe_inf[2] = (SimRow[y] & (1 << x)) >> x;
		}
		else
		{
			kabe_inf[2] = 1;
		}
		break;
	}
}