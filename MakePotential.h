#pragma once
#define MAX_QUEUE_NUM 50
#include "Map.h"
#include "HeapQueue.h"

namespace Algorizm
{
	//pos_queue�\����
	typedef struct POS_QUEUE
	{
		int x;
		int y;
	}POS;

	//queue�\����
	typedef struct QUEUE
	{
		int head;//�f�[�^�̍őO��
		int tail;//�f�[�^�̍Ō��
		POS pos[MAX_QUEUE_NUM];//push����Ă���f�[�^
	}QUEUE_T;

	class MakePotential
	{
		int DistMap[16][16] = {255};
		int isKnowMap[16] = {0};//�����悪���m���ǂ����C(0�̂Ƃ����m�C1�̂Ƃ����m)
		NODE search_node[16][16];//�T���p�̃m�[�h
		HeapQueue heap;//�T���p�̃q�[�v
		int search_edge_miti = 1;//���m��Ԃ̃G�b�W�̏d��
		int search_edge_kiti = 5;//���m��Ԃ̃G�b�W�̏d��
		Map* map;

	public:
		void initQueue(QUEUE_T* queue);//queue�̏�����
		void pushQueue_walk(QUEUE_T* queue, POS input);//queue��push
		POS popQueue_walk(QUEUE_T* queue);//queue��pop
		void Init_Dist(void);//�����}�b�v�̏��������s���֐�
		void DecideDist(int goal_size,POS* goal_pos);//�����}�b�v�̍X�V���s���֐�
		void search_dijkstra(int goal_size, POS* goal_pos);//�T���_�C�N�X�g���@�̕����}�b�v�X�V���s���֐�
		int RetDist(int x, int y);//�����}�b�v�̒l��Ԃ��֐�
		void SetMap(Map* bu_map);//�}�b�v�̃Z�b�g���s���֐�
		void updata_knowmap(int x, int y);
		void init_knowmap();
		void init_search_node();
		NODE ret_search_node(int x, int y);//����ʒux,y�ɂ�����m�[�h��Ԃ��֐�
	};
}
