#include "Command.h"

Command::Command()
{

}

Command::Command(enum command_type type)
{
	switch (type)
	{
	case Stra:
		bu_tar_v = 5;//4�ڕW�I�[���x
		bu_tar_x = 34;//1�}�X34pixel(�ړ���x��y)
		isTurn = false;//turn���ǂ���
		isSenkai = false;
		break;

	case Right_sla:
		bu_tar_x = 90;//90��
		isTurn = true;
		TRFL = true;
		isSenkai = false;
		sla_time = 15;//slalom�ɂ�����t���[����
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Left_sla:
		bu_tar_x = 90;//90��
		isTurn = true;
		TRFL = false;
		isSenkai = false;
		sla_time = 15;//slalom�ɂ�����t���[����
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Right_sen:
		bu_tar_x = 180;
		isTurn = false;
		TRFL = true;
		isSenkai = true;
		sla_time = 15;
		bu_tar_v = bu_tar_x / sla_time;
		break;
	}
}