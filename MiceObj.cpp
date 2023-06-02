#include "MiceObj.h"
#include "DxLib.h"
#include "Mouse.h"
#include "Command.h"
#include "math.h"

void MiceObj::Initialize()
{
	Handle = LoadGraph("D:/お絵描き/mouse/mouse.png"); // 画像をロード
	DrawRotaGraph(pos_x, Mouse::getInstance()->WindowHeight-pos_y, 1, -1*lot/180*acos(-1), Handle, TRUE); // データハンドルを使って画像を描画
	pos_x = 47;
	pos_y = 30;
	lot = 0;
	isKasokuEnd = true;
}

void MiceObj::Update()
{
	daikei();
}

void MiceObj::Draw()
{
	DrawRotaGraph(pos_x, Mouse::getInstance()->WindowHeight-pos_y, 1, -1*lot/180*acos(-1), Handle, TRUE); // データハンドルを使って画像を描画
}

void MiceObj::Finalize()
{
	
}

void MiceObj::SetDaikei(Command cm)
{
	my_cm = cm;
	isKasokuEnd = false;
	tar_x = cm.bu_tar_x;
	now_v = cm.bu_tar_v;
	first_pos_x = pos_x;
	first_pos_y = pos_y;
	first_lot = lot;
	sla_t = 0;
	if (cm.isTurn)
	{
		float bu_tar_x = (cm.TRFL) ? -1*tar_x : tar_x;
		x2 = first_pos_x + 17 * cos((first_lot + 90) / 180 * acos(-1));
		y2 = first_pos_y + 17 * sin((first_lot + 90) / 180 * acos(-1));
		x3 = x2 + 17 * cos((first_lot + bu_tar_x + 90) / 180 * acos(-1));
		y3 = y2 + 17 * sin((first_lot + bu_tar_x + 90) / 180 * acos(-1));
		sla_t = 0;
	}
}

void MiceObj::daikei()//台形加速を行う
{
	if (isKasokuEnd == false && !my_cm.isTurn && !my_cm.isSenkai)//直進
	{
		if (fabs((double)pos_x-(double)first_pos_x)<(double)tar_x && fabs((double)pos_y-(double)first_pos_y)<(double)tar_x)//2定速区間
		{
			pos_x += now_v * cos((lot + 90) / 180 * acos(-1));
		    pos_y += now_v * sin((lot + 90) / 180 * acos(-1));
		}
		else
		{
			pos_x = first_pos_x + tar_x * cos((lot + 90) / 180 * acos(-1));
			pos_y = first_pos_y + tar_x * sin((lot + 90) / 180 * acos(-1));
			isKasokuEnd = true;
		}
	}
	else if (isKasokuEnd == false && !my_cm.isSenkai)//スラローム
	{
		if (sla_t <= 1)
		{
			lot += (my_cm.TRFL) ? -1 * now_v : now_v;
			pos_x = (1 - sla_t) * (1 - sla_t) * first_pos_x + 2 * (1 - sla_t) * sla_t * x2 + sla_t * sla_t * x3;
			pos_y = (1 - sla_t) * (1 - sla_t) * first_pos_y + 2 * (1 - sla_t) * sla_t * y2 + sla_t * sla_t * y3;
			sla_t += 1/my_cm.sla_time;
		}
		else
		{
			float bu_tar_x = (my_cm.TRFL) ? -1*tar_x : tar_x;
			lot = first_lot + bu_tar_x;
			pos_x = x3;
			pos_y = y3;
			isKasokuEnd = true;
		}
	}
	else if (isKasokuEnd == false)//超信地旋回
	{
		if (sla_t <= 1)
		{
			lot += (my_cm.TRFL) ? -1 * now_v : now_v;
			sla_t += 1 / my_cm.sla_time;
		}
		else
		{
			float bu_tar_x = (my_cm.TRFL) ? -1 * tar_x : tar_x;
			lot = first_lot + bu_tar_x;
			isKasokuEnd = true;
		}
	}

}

bool MiceObj::RetisKasoku()
{
	return isKasokuEnd;
}