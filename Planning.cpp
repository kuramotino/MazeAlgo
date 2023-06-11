#include "Planning.h"
#include "MiceStatus.h"

namespace Algorizm
{
	enum Vec Planning::Adati(int goal_size,POS* goal_pos)
	{
		my_potential->DecideDist(goal_size, goal_pos);
		my_status->RetPos(&x, &y, &MiceVec);

		front_dist = 255;
		back_dist = 255;
		left_dist = 255;
		right_dist = 255;
		
		//1ある位置(x,y)にいるときの前後左右の歩数を取得
		if (MiceVec == North)
		{
			if (y != 15)
			{
				front_dist = my_potential->RetDist(x, y + 1);
			}
			if (y != 0)
			{
				back_dist = my_potential->RetDist(x, y - 1);
			}
			if (x != 15)
			{
				right_dist = my_potential->RetDist(x + 1, y);
			}
			if (x != 0)
			{
				left_dist = my_potential->RetDist(x - 1, y);
			}
		}
		else if (MiceVec == East)
		{
			if (x != 15)
			{
				front_dist = my_potential->RetDist(x + 1, y);
			}
			if (x != 0)
			{
				back_dist = my_potential->RetDist(x - 1, y);
			}
			if (y != 0)
			{
				right_dist = my_potential->RetDist(x, y - 1);
			}
			if (y != 15)
			{
				left_dist = my_potential->RetDist(x, y + 1);
			}
		}
		else if (MiceVec == South)
		{
			if (y != 0)
			{
				front_dist = my_potential->RetDist(x, y - 1);
			}
			if (y != 15)
			{
				back_dist = my_potential->RetDist(x, y + 1);
			}
			if (x != 0)
			{
				right_dist = my_potential->RetDist(x - 1, y);
			}
			if (x != 15)
			{
				left_dist = my_potential->RetDist(x + 1, y);
			}
		}
		else if (MiceVec == West)
		{
			if (x != 0)
			{
				front_dist = my_potential->RetDist(x - 1, y);
			}
			if (x != 15)
			{
				back_dist = my_potential->RetDist(x + 1, y);
			}
			if (y != 15)
			{
				right_dist = my_potential->RetDist(x, y + 1);
			}
			if (y != 0)
			{
				left_dist = my_potential->RetDist(x, y - 1);
			}
		}

		//2最小の歩数を決定

		//3前→右→左→後
		int sort[4];
		sort[0] = front_dist;
		sort[1] = right_dist;
		sort[2] = left_dist;
		sort[3] = back_dist;

		my_map->isLFRKnowWall(&isLWall, &isFWall, &isRWall, x, y, MiceVec);

		//4壁に阻まれた歩数を除外
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				if (isFWall != 0)
				{
					sort[i] = 255;
				}
				break;

			case 1:
				if (isRWall != 0)
				{
					sort[i] = 255;
				}
				break;

			case 2:
				if (isLWall != 0)
				{
					sort[i] = 255;
				}
				break;

			case 3:

				break;
			}
		}

		//5最小値を決定
		num = 0;
		min = 255;
		for (int i = 0; i < 4; i++)
		{
			if (sort[i] < min)
			{
				min = sort[i];
				num = i;
			}
		}

		//6setnumに変更
		ret = (num == 0) ? Front : ((num == 1) ? Right : ((num == 2) ? Left : Back));

		UpDataVecPos(ret);
		for (int i = 0; i < goal_size; i++)
		{
			if (isReturn)
			{
				isTansakuEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
				if (isTansakuEnd)
				{
					break;
				}
			}
			else
			{
				isReturn = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
				if (isReturn)
				{
					break;
				}
			}
		}
		return ret;
	}

	void Algorizm::Planning::SetObj(MiceStatus* status, MakePotential* potential, Map* map)//必要なオブジェクトをセットする関数
	{
		my_status = status;
		my_potential = potential;
		my_map = map;
	}

	void Algorizm::Planning::UpDataVecPos(enum Vec vec)//次に進む向き(左，右，前，後)から，次の位置，向きを更新する関数
	{
		switch (vec)
		{
		case Left:
			my_status->VecDecide(false);
			my_status->PosDecide();
			break;

		case Front:
			my_status->PosDecide();
			break;

		case Right:
			my_status->VecDecide(true);
			my_status->PosDecide();
			break;

		case Back:
			my_status->VecDecide(false);
			my_status->VecDecide(false);
			my_status->PosDecide();
			break;
		}
	}

	void Algorizm::Planning::SetReturn(bool isreturn)//戻り探索フラグをセットする関数
	{
		isReturn = isreturn;
	}

	bool Algorizm::Planning::RetReturn()//戻り探索フラグを返す関数
	{
		return isReturn;
	}

	void Algorizm::Planning::SetTansakuEnd(bool istansakuend)
	{
		isTansakuEnd = istansakuend;
	}

	bool Algorizm::Planning::RetTansakuEnd()//探索終了フラグを返す関数
	{
		return isTansakuEnd;
	}

	enum Vec Algorizm::Planning::s_dijkstra(int goal_size, POS* goal_pos)
	{
		NODE node;
		NODE pre_node;
		int pre_x, pre_y;
		my_potential->search_dijkstra(goal_size, goal_pos);//現在のノードを更新する
		my_status->RetPos(&x, &y, &MiceVec);
		node = my_potential->ret_search_node(x, y);
		pre_node = *(node.pre_node);
		pre_x = pre_node.pos_x;
		pre_y = pre_node.pos_y;


		//1ある位置(x,y)につながっているノードの座標から次に進む向きを決定
		if (MiceVec == North)
		{
			ret = (y + 1 == pre_y) ? Front : ((x + 1 == pre_x) ? Right : ((x - 1 == pre_x) ? Left : Back));
		}
		else if (MiceVec == East)
		{
			ret = (x + 1 == pre_x) ? Front : ((y - 1 == pre_y) ? Right : ((y + 1 == pre_y) ? Left : Back));
		}
		else if (MiceVec == South)
		{
			ret = (y - 1 == pre_y) ? Front : ((x - 1 == pre_x) ? Right : ((x + 1 == pre_x) ? Left : Back));
		}
		else if (MiceVec == West)
		{
			ret = (x - 1 == pre_x) ? Front : ((y + 1 == pre_y) ? Right : ((y - 1 == pre_y) ? Left : Back));
		}

		UpDataVecPos(ret);//次に進む向きから位置と向きを更新

		for (int i = 0; i < goal_size; i++)//ゴール座標に到達していたら探索終了
		{
			isTansakuEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			if (isTansakuEnd)
			{
				break;
			}
		}
		return ret;
	}

}