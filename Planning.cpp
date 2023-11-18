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
		
		//1����ʒu(x,y)�ɂ���Ƃ��̑O�㍶�E�̕������擾
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

		//2�ŏ��̕���������

		//3�O���E��������
		int sort[4];
		sort[0] = front_dist;
		sort[1] = right_dist;
		sort[2] = left_dist;
		sort[3] = back_dist;

		my_map->isLFRKnowWall(&isLWall, &isFWall, &isRWall, x, y, MiceVec);

		//4�ǂɑj�܂ꂽ���������O
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

		//5�ŏ��l������
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

		//6setnum�ɕύX
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
					isEndAdatiSearch = true;
					my_potential->SetKnowMap((goal_pos + i)->x, (goal_pos + i)->y);//�ʒux,y�����m���ɂ���
					break;
				}
			}
		}
		return ret;
	}

	void Algorizm::Planning::SetObj(MiceStatus* status, MakePotential* potential, Map* map)//�K�v�ȃI�u�W�F�N�g���Z�b�g����֐�
	{
		my_status = status;
		my_potential = potential;
		my_map = map;
	}

	void Algorizm::Planning::UpDataVecPos(enum Vec vec)//���ɐi�ތ���(���C�E�C�O�C��)����C���̈ʒu�C�������X�V����֐�
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

	void Algorizm::Planning::SetReturn(bool isreturn)//�߂�T���t���O���Z�b�g����֐�
	{
		isReturn = isreturn;
	}

	bool Algorizm::Planning::RetReturn()//�߂�T���t���O��Ԃ��֐�
	{
		return isReturn;
	}

	void Algorizm::Planning::SetTansakuEnd(bool istansakuend)
	{
		isTansakuEnd = istansakuend;
	}

	bool Algorizm::Planning::RetTansakuEnd()//�T���I���t���O��Ԃ��֐�
	{
		return isTansakuEnd;
	}

	enum Vec Algorizm::Planning::s_dijkstra(int goal_size, POS* goal_pos)
	{
		NODE node;
		NODE pre_node;
		int pre_x, pre_y;
		my_potential->search_dijkstra(goal_size, goal_pos);//���݂̃m�[�h���X�V����
		my_status->RetPos(&x, &y, &MiceVec);
		node = my_potential->ret_search_node(x, y);
		pre_node = *(node.pre_node);
		pre_x = pre_node.pos_x;
		pre_y = pre_node.pos_y;


		//1����ʒu(x,y)�ɂȂ����Ă���m�[�h�̍��W���玟�ɐi�ތ���������
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

		UpDataVecPos(ret);//���ɐi�ތ�������ʒu�ƌ������X�V

		for (int i = 0; i < goal_size; i++)//�S�[�����W�ɓ��B���Ă�����T���I��
		{
			//isTansakuEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			//if (isTansakuEnd)
			//{
				//break;
			//}

			isTentativeTansakuEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			if (isTentativeTansakuEnd)
			{
				if ((goal_pos + i)->x == 0 && (goal_pos + i)->y == 0)
				{
					isTansakuEnd = true;
				}
				my_potential->SetKnowMap((goal_pos + i)->x, (goal_pos + i)->y);//�ʒux,y�����m���ɂ���
				break;
			}
		}
		return ret;
	}

	enum Vec Algorizm::Planning::z_dijkstra()//�S�ʒT�����s���֐�
	{
		if (isTentativeTansakuEnd)//���̃S�[���ɂ��ǂ蒅������C���̃S�[����ݒ肷��
		{
			//goal���W��ݒ肷��
			set_goal_pos();
			isTentativeTansakuEnd = false;
		}

		int pre_x;
		int pre_y;
		enum Dir pre_vec;
		my_status->RetPos(&pre_x, &pre_y, &pre_vec);
		
		enum Vec ret_num;
		my_potential->search_dijkstra(1, &Tentative_goal_pos);//�����}�b�v�C�Ǐ��̍X�V

		int now_pos_dist = my_potential->RetDist(pre_x, pre_y);

		if (now_pos_dist == 999)//goal���ǂ���Ă�����goal��ύX����
		{
			BlockIsopos();
			set_goal_pos();
			ret_num = Back;
			UpDataVecPos(ret_num);
		}
		else
		{
			//ret_num = s_dijkstra(1, &Tentative_goal_pos);//�����}�b�v�C�ʒu�����C�Ǐ��̍X�V

			NODE node;
			NODE pre_node;
			int pre_x, pre_y;
			int bux;
			int buy;
			enum Dir bu_vec;
			my_status->RetPos(&bux, &buy, &bu_vec);
			node = my_potential->ret_search_node(bux, buy);
			pre_node = *(node.pre_node);
			pre_x = pre_node.pos_x;
			pre_y = pre_node.pos_y;


			//1����ʒu(x,y)�ɂȂ����Ă���m�[�h�̍��W���玟�ɐi�ތ���������
			if (bu_vec == North)
			{
				ret_num = (buy + 1 == pre_y) ? Front : ((bux + 1 == pre_x) ? Right : ((bux - 1 == pre_x) ? Left : Back));
			}
			else if (bu_vec == East)
			{
				ret_num = (bux + 1 == pre_x) ? Front : ((buy - 1 == pre_y) ? Right : ((buy + 1 == pre_y) ? Left : Back));
			}
			else if (bu_vec == South)
			{
				ret_num = (buy - 1 == pre_y) ? Front : ((bux - 1 == pre_x) ? Right : ((bux + 1 == pre_x) ? Left : Back));
			}
			else if (bu_vec == West)
			{
				ret_num = (bux - 1 == pre_x) ? Front : ((buy + 1 == pre_y) ? Right : ((buy - 1 == pre_y) ? Left : Back));
			}

			UpDataVecPos(ret_num);//���ɐi�ތ�������ʒu�ƌ������X�V

			for (int i = 0; i < 1; i++)//�S�[�����W�ɓ��B���Ă�����T���I��
			{
				isTentativeTansakuEnd = my_status->GoalCheck(1, Tentative_goal_pos.x, Tentative_goal_pos.y);
				if (isTentativeTansakuEnd)
				{
					if (Tentative_goal_pos.x == 0 && Tentative_goal_pos.y == 0)
					{
						isTansakuEnd = true;
					}
					my_potential->SetKnowMap(Tentative_goal_pos.x, Tentative_goal_pos.y);//�ʒux,y�����m���ɂ���
					break;
				}
			}
		}

		return ret_num;
	}

	void Algorizm::Planning::set_goal_pos()//���݂̍��W����ł��߂����m����goal�ɐݒ肷��֐�
	{
		POS bu_pos = { 255,255 };
		int goal_len = 0;//0�S�[���ւ̋���
		int pre_goal_len = 512;
		int n_x;
		int n_y;
		enum Dir n_vec;
		my_status->RetPos(&n_x, &n_y, &n_vec);

		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (my_potential->RetKnowMap(i, j) == 0)//0���̋�悪���m��ԂȂ�
				{
					goal_len = (n_x - i) * (n_x - i) + (n_y - j) * (n_y - j);
					if (goal_len < pre_goal_len)
					{
						pre_goal_len = goal_len;
						bu_pos.x = i;
						bu_pos.y = j;
					}
				}
			}
		}
		Tentative_goal_pos = bu_pos;

		if (bu_pos.x == 255 || bu_pos.y == 255)//1���̃S�[����������Ȃ��Ȃ�X�^�[�g�n�_���S�[���ɂ���
		{
			Tentative_goal_pos = { 0,0 };
		}
	}

	enum Vec  Algorizm::Planning::search_unknown_dijkstra(int goal_size, POS* goal_pos)//�ŒZ�o�H��̖��m��Ԃ�T���ɍs���T���Ŏ��̍s����Ԃ��֐�
	{
		my_map->MapDecide();//�Ǐ��̍X�V�̂ݐ�ɍs��

		int pre_x;
		int pre_y;
		enum Dir pre_vec;
		enum Vec ret_num;
		my_status->RetPos(&pre_x, &pre_y, &pre_vec);
		my_potential->updata_knowmap(pre_x, pre_y);//���m��Ԃ̍X�V

		if (isEndAdatiSearch)
		{
			isEndAdatiSearch = false;
			ret_num = Back;
			UpDataVecPos(ret_num);
			return ret_num;
		}

		if (isTentativeTansakuEnd)//���̃S�[���ɂ��ǂ蒅������C���̃S�[����ݒ肷��
		{
			//goal���W��ݒ肷��
			//search_unknown_set_goal_pos(goal_size, goal_pos);
			search_unknown_pop_goal_pos();
			isTentativeTansakuEnd = false;
		}

		
		//my_potential->search_dijkstra(1, &Tentative_goal_pos);//�����}�b�v�C�Ǐ��̍X�V
		my_potential->DecideDist(1, &Tentative_goal_pos);//�����}�b�v�̍X�V

		int now_pos_dist = my_potential->RetDist(pre_x, pre_y);

		if (now_pos_dist == 255)//goal���ǂ���Ă�����goal��ύX����
		{
			BlockIsopos();
			ret_num = Back;
			UpDataVecPos(ret_num);
		}
		else
		{
			my_status->RetPos(&x, &y, &MiceVec);

			front_dist = 255;
			back_dist = 255;
			left_dist = 255;
			right_dist = 255;

			//1����ʒu(x,y)�ɂ���Ƃ��̑O�㍶�E�̕������擾
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

			//2�ŏ��̕���������

			//3�O���E��������
			int sort[4];
			sort[0] = front_dist;
			sort[1] = right_dist;
			sort[2] = left_dist;
			sort[3] = back_dist;

			my_map->isLFRKnowWall(&isLWall, &isFWall, &isRWall, x, y, MiceVec);

			//4�ǂɑj�܂ꂽ���������O
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

			//5�ŏ��l������
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

			//6setnum�ɕύX
			ret_num = (num == 0) ? Front : ((num == 1) ? Right : ((num == 2) ? Left : Back));

			UpDataVecPos(ret_num);//���ɐi�ތ�������ʒu�ƌ������X�V

			for (int i = 0; i < 1; i++)//�S�[�����W�ɓ��B���Ă�����T���I��
			{
				isTentativeTansakuEnd = my_status->GoalCheck(1, Tentative_goal_pos.x, Tentative_goal_pos.y);
				if (isTentativeTansakuEnd)
				{
					if (Tentative_goal_pos.x == 0 && Tentative_goal_pos.y == 0)
					{
						isTansakuEnd = true;
					}
					my_potential->SetKnowMap(Tentative_goal_pos.x, Tentative_goal_pos.y);//�ʒux,y�����m���ɂ���
					break;
				}
			}
		}

		return ret_num;
	}

	void Algorizm::Planning::search_unknown_set_goal_pos(int goal_size, POS* goal_pos)//�ŒZ�o�H�̖��m��Ԃ�T���֐�
	{
		int buf_x = 0;
		int buf_y = 0;
		enum Dir buf_MiceVec = North;
		my_status->RetPos(&buf_x, &buf_y, &buf_MiceVec);//�}�E�X�̏�Ԃ��o�b�N�A�b�v����

		MiceInit();//�}�E�X�̏�Ԃ�������

		bool isGoal = false;
		int bu_pass = 0;
		pass_unknown_pos = { 255,255 };
		my_potential->saitan_dijkstra(goal_size, goal_pos);

		my_potential->initStack(&stack);//�X�^�b�N�̏�����

		while (1)
		{
			bu_pass = saitan_dijkstra(goal_size, goal_pos, false);//���̍s���𓾂�

			my_status->RetPos(&x, &y, &MiceVec);

			if (my_potential->RetKnowMap(x, y) == 0)//�ʒux,y�����m��ԂȂ�
			{
				pass_unknown_pos = { x,y };
				my_potential->pushStack_walk(&stack, pass_unknown_pos);//���m��Ԃ��X�^�b�N��push����
			}

			isGoal = RetIsSimEnd();
			if (isGoal)
			{
				break;
			}
		}

		my_status->SetPos(buf_x, buf_y, buf_MiceVec);//�}�E�X�̏�Ԃ����Ƃɖ߂�

		if (pass_unknown_pos.x == 255 || pass_unknown_pos.y == 255)//1�ŒZ�o�H��ɖ��m��Ԃ�������Ȃ��Ȃ�X�^�[�g�n�_���S�[���ɂ���
		{
			Tentative_goal_pos = { 0,0 };
		}
		else
		{
			Tentative_goal_pos = pass_unknown_pos;//1�ŒZ�o�H��̖��m��Ԃ��S�[���ɂ���
		}
	}

	void Algorizm::Planning::search_unknown_pop_goal_pos()//�X�^�b�N���玟�̃S�[����pop����֐�
	{
		while (1)
		{
			Tentative_goal_pos = my_potential->popStack_walk(&stack);

			if (Tentative_goal_pos.x == 65535)//1�X�^�b�N����̏ꍇ
			{
				Tentative_goal_pos = { 0,0 };
				break;
			}

			if (my_potential->RetKnowMap(Tentative_goal_pos.x, Tentative_goal_pos.y) == 0)//�ʒux,y�����m��ԂȂ�
			{
				break;
			}
		}
	}

	void Algorizm::Planning::BlockIsopos()//�Ǘ������Ԃ��֐�
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (my_potential->RetDist(i, j) != 255)
				{
					my_potential->SetKnowMap(i, j);//�ʒui,j�����m���ɂ���
				}
			}
		}
	}

	int Algorizm::Planning::saitan_dijkstra(int goal_size, POS* goal_pos, bool isMakePotential)
	{
		NODE node = { 999,true,0,0,0,NN,false,false };
		int pre_x, pre_y;
		if (isMakePotential)
		{
			my_potential->saitan_dijkstra(goal_size, goal_pos);//���݂̃m�[�h���X�V����
		}
		my_status->RetPos(&x, &y, &MiceVec);
		
		if (MiceVec == North)
		{
			node = *(my_potential->RetSaitanNode(y - 1, x, true));
		}
		else if (MiceVec == East)
		{
			node = *(my_potential->RetSaitanNode(x - 1, y, false));
		}
		else if (MiceVec == South)
		{
			node = *(my_potential->RetSaitanNode(y, x, true));
		}
		else if (MiceVec == West)
		{
			node = *(my_potential->RetSaitanNode(x, y, false));
		}


		//pre_node = *(node.pre_node);
		//pre_x = pre_node.pos_x;
		//pre_y = pre_node.pos_y;


		//1����ʒu(x,y)�ɂȂ����Ă���m�[�h�̍��W���玟�ɐi�ތ���������
		if (MiceVec == North)
		{
			ret = (node.node_dir == NW) ? Left : ((node.node_dir == NE) ? Right : Front);
		}
		else if (MiceVec == East)
		{
			ret = (node.node_dir == NE) ? Left : ((node.node_dir == SE) ? Right : Front);
		}
		else if (MiceVec == South)
		{
			ret = (node.node_dir == SE) ? Left : ((node.node_dir == SW) ? Right : Front);
		}
		else if (MiceVec == West)
		{
			ret = (node.node_dir == SW) ? Left : ((node.node_dir == NW) ? Right : Front);
		}

		UpDataVecPos(ret);//���ɐi�ތ�������ʒu�ƌ������X�V

		for (int i = 0; i < goal_size; i++)//�S�[�����W�ɓ��B���Ă�����T���I��
		{
			isSimEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			if (isSimEnd)
			{
				break;
			}
		}
		int nextpass = (ret == Left) ? -2 : ((ret == Right) ? -3 : 2);
		return nextpass;
	}

	void Algorizm::Planning::BlockWall()
	{
		my_potential->BlockKnowWall();
	}

	void Algorizm::Planning::MiceInit()//�@�̂̈ʒu����������������
	{
		my_status->InitStatus();
	}

	bool Algorizm::Planning::RetIsSimEnd()
	{
		return isSimEnd;
	}

}