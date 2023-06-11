#include "MakePotential.h"
#include "HeapQueue.h"

namespace Algorizm
{
	void Algorizm::MakePotential::initQueue(QUEUE_T* queue)//queue�̏�����
	{
		queue->head = 0;
		queue->tail = 0;
	}

	void Algorizm::MakePotential::pushQueue_walk(QUEUE_T* queue, POS input)//queue��push
	{
		//1�f�[�^���f�[�^�̍Ō���̈���Ɋi�[
		queue->pos[queue->tail] = input;
		//2�f�[�^�̍Ō��������Ɉړ�
		queue->tail = queue->tail + 1;
		//3����V�t�g
		if (queue->tail == MAX_QUEUE_NUM)
		{
			queue->tail = 0;
		}
		//4�L���[�����t�Ȃ牽�������Ɋ֐��I��
		if (queue->tail == queue->head)
		{
			return;
		}
	}

	POS Algorizm::MakePotential::popQueue_walk(QUEUE_T* queue)//queue��pop
	{
		POS ret = { 0,0 };

		//1�L���[����Ȃ牽�������ɏI��
		if (queue->tail == queue->head)
		{
			ret.x = 65535;
			return ret;
		}
		//2�f�[�^�̍őO�񂩂�f�[�^���擾
		ret = queue->pos[queue->head];
		//3�f�[�^�̍őO�����O�ɂ��炷
		queue->head = queue->head + 1;
		//4����V�t�g
		if (queue->head == MAX_QUEUE_NUM)
		{
			queue->head = 0;
		}
		//5�擾�����f�[�^��ԋp
		return ret;
	}

	void Algorizm::MakePotential::Init_Dist(void)//�����}�b�v�̏��������s���֐�
	{
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				DistMap[x][y] = 255;
			}
		}
	}

	void Algorizm::MakePotential::DecideDist(int goal_size, POS* goal_pos)//�C�ӂ̃S�[�����W�ɑ΂��ĕ����}�b�v�X�V���s���֐�
	{
		map->MapDecide();//�Ǐ��̍X�V
		int now_x;
		int now_y;
		map->RetPos(&now_x, &now_y);
		updata_knowmap(now_x, now_y);//���m��Ԃ̍X�V
		Init_Dist();//�����}�b�v�̏�����

		QUEUE_T queue;
		POS bupos;
		initQueue(&queue);//1�L���[��������

		for (int i = 0; i < goal_size; i++)
		{
			DistMap[(goal_pos+i)->x][(goal_pos+i)->y] = 0;//goal���W��0�ɂ���
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			pushQueue_walk(&queue, bupos);//goal���W���X�^�b�N��push����
		}

		int currnet_step = 0;

		while (1)
		{
			bupos = popQueue_walk(&queue);//�L���[������W��pop����
			int x = bupos.x;
			int y = bupos.y;

			if (x == 65535)//�L���[����Ȃ̂Ɏ��o�����Ƃ�����break;
			{
				break;
			}
			if (DistMap[x][y] == currnet_step + 1)//pop�������W�̕���������count�Ȃ猻�݂̃J�E���g��++
			{
				currnet_step++;
			}
			if (currnet_step == 254)
			{
				break;
			}

			//Pop���ꂽ���W�̎��ӏ󋵂̊m�F
			if (DistMap[x][y] == currnet_step)
			{
				if (x != 15 && DistMap[x + 1][y] == 255 && map->isKnowWall(x,y,East) == 0)//1�E�[�łȂ��A�T���ς݂łȂ��A�E�ǂȂ��̂Ƃ�
				{
					DistMap[x + 1][y] = currnet_step + 1;
					bupos.x = x + 1;
					bupos.y = y;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
				if (x != 0 && DistMap[x - 1][y] == 255 && map->isKnowWall(x, y, West) == 0)//2���[�łȂ��A�T���ς݂łȂ��A���ǂȂ��̂Ƃ�
				{
					DistMap[x - 1][y] = currnet_step + 1;
					bupos.x = x - 1;
					bupos.y = y;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
				if (y != 15 && DistMap[x][y + 1] == 255 && map->isKnowWall(x, y, North) == 0)//3��[�łȂ��A�T���ς݂łȂ��A��ǂȂ��̂Ƃ�
				{
					DistMap[x][y + 1] = currnet_step + 1;
					bupos.x = x;
					bupos.y = y + 1;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
				if (y != 0 && DistMap[x][y - 1] == 255 && map->isKnowWall(x, y, South) == 0)//3���[�łȂ��A�T���ς݂łȂ��A���ǂȂ��̂Ƃ�
				{
					DistMap[x][y - 1] = currnet_step + 1;
					bupos.x = x;
					bupos.y = y - 1;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
			}
		}
	}

	int Algorizm::MakePotential::RetDist(int x, int y)
	{
		return DistMap[x][y];
	}

	void Algorizm::MakePotential::SetMap(Map* bu_map)//�}�b�v�̃Z�b�g���s���֐�
	{
		map = bu_map;
	}

	void Algorizm::MakePotential::updata_knowmap(int x, int y)//���m��Ԃ̍X�V�C�Ǐ��擾��ɌĂ΂��
	{
		isKnowMap[x] = isKnowMap[x] | (1 << y);
		if (x != 0)
		{
			int sum_west = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_west += map->isKnowWall(x - 1, y, (Dir)i);
			}
			isKnowMap[x - 1] = (sum_west >= 3) ? isKnowMap[x - 1] | (1 << y) : isKnowMap[x - 1];
		}
		if (x != 15)
		{
			int sum_east = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_east+=map->isKnowWall(x + 1, y, (Dir)i);
			}
			isKnowMap[x + 1] = (sum_east >= 3) ? isKnowMap[x + 1] | (1 << y) : isKnowMap[x + 1];
		}
		if (y != 0)
		{
			int sum_south = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_south+=map->isKnowWall(x, y - 1, (Dir)i);
			}
			isKnowMap[x] = (sum_south >= 3) ? isKnowMap[x] | (1 << y - 1) : isKnowMap[x];
		}
		if (y != 15)
		{
			int sum_north = 0;
			for (int i = 0; i < 4; i++)
			{
				sum_north+=map->isKnowWall(x, y + 1, (Dir)i);
			}
			isKnowMap[x] = (sum_north >= 3) ? isKnowMap[x] | (1 << y + 1) : isKnowMap[x];
		}
	}

	void Algorizm::MakePotential::init_knowmap()
	{
		for (int i = 0; i < 16; i++)
		{
			isKnowMap[i] = 0;
		}
	}

	void Algorizm::MakePotential::search_dijkstra(int goal_size,POS* goal_pos)
	{
		map->MapDecide();//�Ǐ��̍X�V
		int now_x;
		int now_y;
		map->RetPos(&now_x, &now_y);
		updata_knowmap(now_x, now_y);//���m��Ԃ̍X�V
		//Init_Dist();//�����}�b�v�̏�����
		init_search_node();//�m�[�h�̏�����

		POS bupos = { 0,0 };//�V���Ɋm�肵���m�[�h�̍��W
		NODE new_confirm_node;//�V���Ɋm�肵���m�[�h

		heap.init_heap();//1�L���[��������

		for (int i = 0; i < goal_size; i++)
		{
			DistMap[(goal_pos + i)->x][(goal_pos + i)->y] = 0;//goal���W��0�ɂ���
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			search_node[bupos.x][bupos.y].cost = 0;//�X�^�[�g�m�[�h�̃R�X�g��0�ɂ���
			search_node[bupos.x][bupos.y].isConfirm = true;//�X�^�[�g�m�[�h���m�肳����
			new_confirm_node = search_node[bupos.x][bupos.y];//�X�^�[�g�m�[�h��V���Ɋm�肵���m�[�h�Ƃ���
		}
		bool isFirst = true;
		int x = bupos.x;
		int y = bupos.y;

		while (heap.ret_node_num() != 0 || isFirst)
		{
			if (!isFirst)
			{
				if (heap.ret_node_num() != 0)
				{
					new_confirm_node = heap.pop_heap();//�D��x�t���L���[����ŏ��̃R�X�g�����m�[�h�����o��
					bupos.x = new_confirm_node.pos_x;//�m�肵���m�[�h�̍��W���i�[����
					bupos.y = new_confirm_node.pos_y;//�m�肵���m�[�h�̍��W���i�[����
					x = bupos.x;
					y = bupos.y;
					new_confirm_node.isConfirm = true;//�m�[�h���m�肳����
					search_node[bupos.x][bupos.y] = new_confirm_node;
					DistMap[x][y] = new_confirm_node.cost;
				}
			}
			else
			{
				isFirst = false;
			}

			int edge_cost = ((isKnowMap[x] & (1 << y)) == (1 << y)) ? search_edge_kiti : search_edge_miti;
			//Pop���ꂽ���W�̎��ӏ󋵂̊m�F
			if (x != 15 && map->isKnowWall(x, y, East) == 0)//1�E�[�łȂ��A�E�ǂȂ��̂Ƃ�
			{
				if (search_node[x + 1][y].cost > search_node[x][y].cost + edge_cost && !search_node[x + 1][y].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x + 1][y].cost = search_node[x][y].cost + edge_cost;
					search_node[x + 1][y].pre_node = &search_node[x][y];
					DistMap[x + 1][y] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x + 1][y].isConfirm)
				{
					heap.push_heap(search_node[x + 1][y]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x + 1][y] = search_node[x + 1][y].cost;
				}
			}
			if (x != 0 && map->isKnowWall(x, y, West) == 0)//2���[�łȂ��A���ǂȂ��̂Ƃ�
			{
				if (search_node[x - 1][y].cost > search_node[x][y].cost + edge_cost && !search_node[x - 1][y].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x - 1][y].cost = search_node[x][y].cost + edge_cost;
					search_node[x - 1][y].pre_node = &search_node[x][y];
					DistMap[x - 1][y] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x - 1][y].isConfirm)
				{
					heap.push_heap(search_node[x - 1][y]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x - 1][y] = search_node[x - 1][y].cost;
				}
			}
			if (y != 15 && map->isKnowWall(x, y, North) == 0)//3��[�łȂ��A��ǂȂ��̂Ƃ�
			{
				if (search_node[x][y + 1].cost > search_node[x][y].cost + edge_cost && !search_node[x][y + 1].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x][y + 1].cost = search_node[x][y].cost + edge_cost;
					search_node[x][y + 1].pre_node = &search_node[x][y];
					DistMap[x][y + 1] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x][y + 1].isConfirm)
				{
					heap.push_heap(search_node[x][y + 1]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x][y + 1] = search_node[x][y + 1].cost;
				}
			}
			if (y != 0 && map->isKnowWall(x, y, South) == 0)//3���[�łȂ��A���ǂȂ��̂Ƃ�
			{
				if (search_node[x][y - 1].cost > search_node[x][y].cost + edge_cost && !search_node[x][y - 1].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x][y - 1].cost = search_node[x][y].cost + edge_cost;
					search_node[x][y - 1].pre_node = &search_node[x][y];
					DistMap[x][y - 1] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x][y - 1].isConfirm)
				{
					heap.push_heap(search_node[x][y - 1]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x][y - 1] = search_node[x][y - 1].cost;
				}
			}
		}
	}

	void Algorizm::MakePotential::init_search_node()
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				search_node[i][j].cost = 999;
				search_node[i][j].isConfirm = false;
				search_node[i][j].pos_x = i;
				search_node[i][j].pos_y = j;
				search_node[i][j].pre_node = &search_node[i][j];
			}
		}
	}

	NODE Algorizm::MakePotential::ret_search_node(int x, int y)//����ʒux,y�ɂ�����m�[�h��Ԃ��֐�
	{
		return search_node[x][y];
	}

}