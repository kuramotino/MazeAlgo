#pragma once
#include "MiceStatus.h"
#include "InputData.h"
#include "Map.h"

namespace Algorizm
{
	enum Vec { Left, Front, Right, Back, Stop };
	class Map
	{
		int Row[15];//����ō��̓Y�����������牽��ڂ��A�r�b�g�������牽�Ԗڂ�
		int Column[15];//����ō��̓Y�����������牽��ڂ��A�r�b�g�������牽�Ԗڂ�
		int M_Row[15];//����ō��̓Y�����������牽��ڂ��A�r�b�g�������牽�Ԗڂ�
		int M_Column[15];//����ō��̓Y�����������牽��ڂ��A�r�b�g�������牽�Ԗڂ�
		int currentWall[3];//���݂̍��C�O�C�E�̕ǂ̗L��
		int current_x;
		int current_y;
		enum Dir current_vec;
		InputData* my_input;
		MiceStatus* my_status;

	public:
		void Init_Row_Column(void);//�Ǐ�������������֐�
		void Updata_current(void);//InputData����ǂ̗L�����CMiceStatus����ʒu�����𓾂�
		void MapDecide(void);//�}�b�v�����X�V����֐�
		int isKnowWall(int x,int y,Dir wall_dir);//�ʒux,y��wall_dir�����̕ǂ̗L����Ԃ��֐�
		void isLFRKnowWall(int* l, int* f, int* r, int x, int y, enum Dir dir);//�ʒux,y,����dir�̂Ƃ��̍��ƑO�ƉE�̕ǂ̗L���𒲂ׂ�֐�
		void SetInputStatus(InputData* input, MiceStatus* status);//Input��MiceStatus�̃I�u�W�F�N�g���Z�b�g����
		void RetPos(int* x, int* y);
		bool isExistRowColumn(int x, int y, bool isRow);
		void BlockWall(int x, int y);//����ʒu�̕ǂ��ӂ����֐�
	};
}
