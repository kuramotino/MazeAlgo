#pragma once
#include "MiceStatus.h"
using namespace Algorizm;

//�Ǐ���ʒu����ۊǂ���N���X
class InputData
{
	int SimRow[15];//�V�~�����[�^�ɃZ�b�g���ꂽ�Ǐ��
	int SimColume[15];//�V�~�����[�^�ɃZ�b�g���ꂽ�Ǐ��
public:
	int kabe_inf[3];//���ƑO�ƉE�̕ǂ̗L��

public:
	void SetRowColume(int i,int j,int on,bool isRow);
	void UpData_kabe_inf(int x, int y, enum Dir dir);
};
