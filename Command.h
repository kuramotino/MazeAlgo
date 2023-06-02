#pragma once

enum command_type { Stra, Left_sla, Right_sla, Left_sen, Right_sen, Stra_Back, Left_f_off, Left_b_off, Mid_Stra, Stop, Fail_Stop, Break_Stop };

class Command
{
public:
	float bu_tar_v = 0;//速度
	float bu_tar_x = 0;//移動量
	bool isTurn = false;//turnかどうか
	bool TRFL = true;//右か左か
	bool isSenkai = false;//超信地旋回
	float sla_time = 0;//slalomにかかる時間
	

public:
	Command();
	Command(enum command_type type);//Commandのコンストラクタ
};