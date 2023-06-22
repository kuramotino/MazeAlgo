#include "Command.h"

Command::Command()
{

}

Command::Command(enum command_type type)
{
	switch (type)
	{
	case Stra:
		bu_tar_v = 5;//4目標終端速度
		bu_tar_x = 34;//1マス34pixel(移動量xかy)
		isTurn = false;//turnかどうか
		isSenkai = false;
		break;

	case Right_sla:
		bu_tar_x = 90;//90°
		isTurn = true;
		TRFL = true;
		isSenkai = false;
		sla_time = 15;//slalomにかかるフレーム数
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Left_sla:
		bu_tar_x = 90;//90°
		isTurn = true;
		TRFL = false;
		isSenkai = false;
		sla_time = 15;//slalomにかかるフレーム数
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

	case Right_Diag_in45:
		bu_tar_x = 45;
		isTurn = true;
		TRFL = true;
		isSenkai = false;
		isDiag_in45 = true;
		sla_time = 15;
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Left_Diag_in45:
		bu_tar_x = 45;
		isTurn = true;
		TRFL = false;
		isSenkai = false;
		isDiag_in45 = true;
		sla_time = 15;
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Right_Diag_out45:
		bu_tar_x = 45;
		isTurn = true;
		TRFL = true;
		isSenkai = false;
		isDiag_out45 = true;
		sla_time = 15;
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Left_Diag_out45:
		bu_tar_x = 45;
		isTurn = true;
		TRFL = false;
		isSenkai = false;
		isDiag_out45 = true;
		sla_time = 15;
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Right_Diag_in135:
		break;

	case Left_Diag_in135:
		break;

	case Right_Diag_out135:
		break;

	case Left_Diag_out135:
		break;

	case Right_V90:
		break;

	case Left_V90:
		break;

	case Right_OO90:
		bu_tar_x = 90;//90°
		isTurn = true;
		TRFL = true;
		isSenkai = false;
		isOO90 = true;
		sla_time = 10;//slalomにかかるフレーム数
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Left_OO90:
		bu_tar_x = 90;//90°
		isTurn = true;
		TRFL = false;
		isSenkai = false;
		isOO90 = true;
		sla_time = 10;//slalomにかかるフレーム数
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Right_OO180:
		bu_tar_x = 180;//90°
		isTurn = true;
		TRFL = true;
		isSenkai = false;
		isOO180 = true;
		sla_time = 12;//slalomにかかるフレーム数
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Left_OO180:
		bu_tar_x = 180;//90°
		isTurn = true;
		TRFL = false;
		isSenkai = false;
		isOO180 = true;
		sla_time = 12;//slalomにかかるフレーム数
		bu_tar_v = bu_tar_x / sla_time;
		break;

	case Harf_Stra:
		bu_tar_v = 7;//4目標終端速度
		bu_tar_x = 17;//1マス34pixel(移動量xかy)
		isTurn = false;//turnかどうか
		isSenkai = false;
		break;
	}
}