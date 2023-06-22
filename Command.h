#pragma once

enum command_type {
	Stra, Left_sla, Right_sla, Left_sen, Right_sen, Stra_Back, Left_f_off, Left_b_off, Mid_Stra, Stop, Fail_Stop, Break_Stop,
	Right_Diag_in45, Left_Diag_in45, Right_Diag_out45, Left_Diag_out45, Right_Diag_in135, Left_Diag_in135, Right_Diag_out135, Left_Diag_out135, Right_V90, Left_V90,
	Right_OO90, Left_OO90, Right_OO180, Left_OO180, Harf_Stra,
};

class Command
{
public:
	float bu_tar_v = 0;//���x
	float bu_tar_x = 0;//�ړ���
	bool isTurn = false;//turn���ǂ���
	bool TRFL = true;//�E������
	bool isSenkai = false;//���M�n����
	float sla_time = 0;//slalom�ɂ����鎞��
	bool isDiag_in45 = false;
	bool isDiag_out45 = false;
	bool isDiag_in135 = false;
	bool isDiag_out135 = false;
	bool isV90 = false;
	bool isOO90 = false;
	bool isOO180 = false;

public:
	Command();
	Command(enum command_type type);//Command�̃R���X�g���N�^
};