#include "Map.h"

namespace Algorizm
{
	void Algorizm::Map::Init_Row_Column()
	{
		for (int i = 0; i < 15; i++)
		{
			Row[i] = 0;
			Column[i] = 0;
			M_Row[i] = 0b1111111111111111;
			M_Column[i] = 0b1111111111111111;
		}
		Column[0] = 0b0000000000000001;
	}

	void Algorizm::Map::Updata_current()
	{
		my_status->RetPos(&current_x, &current_y, &current_vec);
		my_input->UpData_kabe_inf(current_x, current_y, current_vec);//これはシミュレータのときにのみ呼ぶ
		currentWall[Left] = my_input->kabe_inf[0];
		currentWall[Front] = my_input->kabe_inf[1];
		currentWall[Right] = my_input->kabe_inf[2];
	}

	void Algorizm::Map::MapDecide()
	{
		Updata_current();
		switch (current_vec)
		{
		case North:
			if (current_x != 0)
			{
				if (currentWall[Left] == 1)
				{
					Column[current_x - 1] = Column[current_x - 1] | (1 << current_y);
				}
				else
				{
					Column[current_x - 1] = Column[current_x - 1] & ~(1 << current_y);
				}
			}
			
			if (current_x != 15)
			{
				if (currentWall[Right] == 1)
				{
					Column[current_x] = Column[current_x] | (1 << current_y);
				}
				else
				{
					Column[current_x] = Column[current_x] & ~(1 << current_y);
				}
			}
			
			if (current_y != 15)
			{
				if (currentWall[Front] == 1)
				{
					Row[current_y] = Row[current_y] | (1 << current_x);
				}
				else
				{
					Row[current_y] = Row[current_y] & ~(1 << current_x);
				}
			}
			break;

		case East:
			if (current_x != 15)
			{
				if (currentWall[Front] == 1)
				{
					Column[current_x] = Column[current_x] | (1 << current_y);
				}
				else
				{
					Column[current_x] = Column[current_x] & ~(1 << current_y);
				}
			}

			if (current_y != 0)
			{
				if (currentWall[Right] == 1)
				{
					Row[current_y - 1] = Row[current_y - 1] | (1 << current_x);
				}
				else
				{
					Row[current_y - 1] = Row[current_y - 1] & ~(1 << current_x);
				}
			}

			if (current_y != 15)
			{
				if (currentWall[Left] == 1)
				{
					Row[current_y] = Row[current_y] | (1 << current_x);
				}
				else
				{
					Row[current_y] = Row[current_y] & ~(1 << current_x);
				}
			}
			break;

		case South:
			if (current_x != 0)
			{
				if (currentWall[Right] == 1)
				{
					Column[current_x - 1] = Column[current_x - 1] | (1 << current_y);
				}
				else
				{
					Column[current_x - 1] = Column[current_x - 1] & ~(1 << current_y);
				}
			}

			if (current_x != 15)
			{
				if (currentWall[Left] == 1)
				{
					Column[current_x] = Column[current_x] | (1 << current_y);
				}
				else
				{
					Column[current_x] = Column[current_x] & ~(1 << current_y);
				}
			}

			if (current_y != 0)
			{
				if (currentWall[Front] == 1)
				{
					Row[current_y - 1] = Row[current_y - 1] | (1 << current_x);
				}
				else
				{
					Row[current_y - 1] = Row[current_y - 1] & ~(1 << current_x);
				}
			}
			break;

		case West:
			if (current_x != 0)
			{
				if (currentWall[Front] == 1)
				{
					Column[current_x - 1] = Column[current_x - 1] | (1 << current_y);
				}
				else
				{
					Column[current_x - 1] = Column[current_x - 1] & ~(1 << current_y);
				}
			}

			if (current_y != 0)
			{
				if (currentWall[Left] == 1)
				{
					Row[current_y - 1] = Row[current_y - 1] | (1 << current_x);
				}
				else
				{
					Row[current_y - 1] = Row[current_y - 1] & ~(1 << current_x);
				}
			}

			if (current_y != 15)
			{
				if (currentWall[Right] == 1)
				{
					Row[current_y] = Row[current_y] | (1 << current_x);
				}
				else
				{
					Row[current_y] = Row[current_y] & ~(1 << current_x);
				}
			}
			break;
		}
	}

	int Algorizm::Map::isKnowWall(int x, int y,enum Dir wall_dir)
	{
		switch (wall_dir)
		{
		case North:
			
			return (y != 15) ? (Row[y] & (1 << x)) >> x : 1;
			
			break;

		case East:

			return (x != 15) ? (Column[x] & (1 << y)) >> y : 1;
			
			break;

		case South:
			
			return (y != 0) ? (Row[y - 1] & (1 << x)) >> x : 1;
			
			break;

		case West:
			
			return (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;
			
			break;
		}
	}

	void Algorizm::Map::isLFRKnowWall(int* l, int* f, int* r, int x, int y, enum Dir dir)
	{
		switch (dir)
		{
		case North:
			*l = (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;
			*f = (y != 15) ? (Row[y] & (1 << x)) >> x : 1;
			*r = (x != 15) ? (Column[x] & (1 << y)) >> y : 1;
			break;

		case East:
			*l = (y != 15) ? (Row[y] & (1 << x)) >> x : 1;
			*f = (x != 15) ? (Column[x] & (1 << y)) >> y : 1;
			*r = (y != 0) ? (Row[y-1] & (1 << x)) >> x : 1;
			break;

		case South:
			*l = (x != 15) ? (Column[x] & (1 << y)) >> y : 1;
			*f = (y != 0) ? (Row[y - 1] & (1 << x)) >> x : 1;
			*r = (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;
			break;

		case West:
			*l = (y != 0) ? (Row[y - 1] & (1 << x)) >> x : 1;
			*f = (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;
			*r = (y != 15) ? (Row[y] & (1 << x)) >> x : 1;
			break;
		}
	}

	void Algorizm::Map::SetInputStatus(InputData* input, MiceStatus* status)//InputとMiceStatusのオブジェクトをセットする
	{
		my_input = input;
		my_status = status;
	}

	void Algorizm::Map::RetPos(int* x, int* y)
	{
		int bu_x;
		int bu_y;
		Dir bu_dir;
		my_status->RetPos(&bu_x, &bu_y, &bu_dir);
		*x = bu_x;
		*y = bu_y;
	}

	bool Algorizm::Map::isExistRowColumn(int x, int y, bool isRow)
	{
		bool Ret;
		if (isRow)
		{
			Ret = ((Row[x] & (1 << y)) == (1 << y)) ? true : false;
		}
		else
		{
			Ret = ((Column[x] & (1 << y)) == (1 << y)) ? true : false;
		}
		return Ret;
	}

	void Algorizm::Map::BlockWall(int x, int y)//ある位置x,yの壁をすべてふさぐ関数
	{
		if (y != 0)
		{
			Row[y - 1] = (Row[y - 1] | (1 << x));
		}
		if (y != 15)
		{
			Row[y] = (Row[y] | (1 << x));
		}
		if (x != 0)
		{
			Column[x - 1] = (Column[x - 1] | (1 << y));
		}
		if (x != 15)
		{
			Column[x] = (Column[x] | (1 << y));
		}
	}
}