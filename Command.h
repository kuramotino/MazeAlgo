#pragma once

enum command_type { Stra, Left_sla, Right_sla, Left_sen, Right_sen, Stra_Back, Left_f_off, Left_b_off, Mid_Stra, Stop, Fail_Stop, Break_Stop };

class Command
{
public:
	float bu_tar_v = 0;//���x
	float bu_tar_x = 0;//�ړ���
	bool isTurn = false;//turn���ǂ���
	bool TRFL = true;//�E������
	bool isSenkai = false;//���M�n����
	float sla_time = 0;//slalom�ɂ����鎞��
	

public:
	Command();
	Command(enum command_type type);//Command�̃R���X�g���N�^
};