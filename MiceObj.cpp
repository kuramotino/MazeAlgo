#include "MiceObj.h"
#include "DxLib.h"
#include "Mouse.h"
#include "Command.h"
#include "math.h"

void MiceObj::Initialize()
{
	Handle = LoadGraph("D:/お絵描き/mouse/mouse.png"); // 画像をロード
	DrawRotaGraph(pos_x, Mouse::getInstance()->WindowHeight-pos_y, 1, -1*lot/180*acos(-1), Handle, TRUE); // データハンドルを使って画像を描画
	pos_x = 47;//47/300/251
	pos_y = 30;//30/300/319
	lot = 0;//0/-90
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
	float flot = first_lot + 90;
	float pi = acos(-1);
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
	if (cm.isOO90)
	{
		float bu_tar_x = (cm.TRFL) ? -1 * tar_x : tar_x;
		x2 = first_pos_x + 34 * cos((first_lot + 90) / 180 * acos(-1));
		y2 = first_pos_y + 34 * sin((first_lot + 90) / 180 * acos(-1));
		x3 = x2 + 34 * cos((first_lot + bu_tar_x + 90) / 180 * acos(-1));
		y3 = y2 + 34 * sin((first_lot + bu_tar_x + 90) / 180 * acos(-1));
		sla_t = 0;
	}
	else if (cm.isOO180)
	{
		int TrFl = (cm.TRFL) ? 1 : -1;
		x3 = first_pos_x + 34.0 * TrFl * sin((first_lot + tar_x - 90) / 180 * acos(-1));
		y3 = first_pos_y - 34.0 * TrFl * cos((first_lot + tar_x - 90) / 180 * acos(-1));
		x2 = (first_pos_x + x3) / 2;
		y2 = (first_pos_y + y3) / 2;
		x2 += 34 * cos((first_lot + 90) / 180 * acos(-1));
		y2 += 34 * sin((-1*first_lot + 90) / 180 * acos(-1));
		sla_t = 0;
	}
	else if (cm.isDiag_in45)
	{
		int TrFl = (cm.TRFL) ? -1 : 1;
		x2 = first_pos_x + 34 * cos(flot / 180.0 * pi);
		y2 = first_pos_y + 34 * sin(flot / 180.0 * pi);
		x3 = x2 + 17 * cos((flot + TrFl*90.0) / 180.0 * pi);
		y3 = y2 + 17 * sin((flot + TrFl*90.0) / 180.0 * pi);
		sla_t = 0;
	}
	else if (cm.isDiag_out45)
	{
		int TrFl = (cm.TRFL) ? -1 : 1;
		x2 = first_pos_x + 17 * cos((flot - TrFl*45.0) / 180.0 * pi);
		y2 = first_pos_y + 17 * sin((flot - TrFl*45.0) / 180.0 * pi);
		x3 = x2 + 34 * cos((flot + TrFl * 45.0) / 180.0 * pi);
		y3 = y2 + 34 * sin((flot + TrFl * 45.0) / 180.0 * pi);
		sla_t = 0;
	}
	else if (cm.isDiag_in135)
	{
		int TrFl = (cm.TRFL) ? -1 : 1;
		x2 = first_pos_x + 34 * cos(flot / 180.0 * pi);
		y2 = first_pos_y + 34 * sin(flot / 180.0 * pi);
		x3 = (first_pos_x + x2)/2 + 34 * cos((flot + TrFl * 90.0) / 180.0 * pi);
		y3 = (first_pos_y + y2)/2 + 34 * sin((flot + TrFl * 90.0) / 180.0 * pi);
		sla_t = 0;
	}
	else if (cm.isDiag_out135)
	{
		int TrFl = (cm.TRFL) ? -1 : 1;
		x2 = first_pos_x + 24 * cos(flot / 180.0 * pi) + 17.0 * cos((flot + TrFl * 45.0) / 180.0 * pi);
		y2 = first_pos_y + 24 * sin(flot / 180.0 * pi) + 17.0 * sin((flot + TrFl * 45.0) / 180.0 * pi);
		x3 = x2 + 34.0 * cos((flot + TrFl * 135.0) / 180.0 * pi);
		y3 = y2 + 34.0 * sin((flot + TrFl * 135.0) / 180.0 * pi);
		sla_t = 0;
	}
	else if (cm.isV90)
	{
		int TrFl = (cm.TRFL) ? -1 : 1;
		x3 = first_pos_x + 34 * cos((flot + TrFl * 45.0) / 180.0 * pi);
		y3 = first_pos_y + 34 * sin((flot + TrFl * 45.0) / 180.0 * pi);
		x2 = (first_pos_x + x3) / 2 + 34 * cos((flot - TrFl * 45.0) / 180.0 * pi);
		y2 = (first_pos_y + y3) / 2 + 34 * sin((flot - TrFl * 45.0) / 180.0 * pi);
		sla_t = 0;
	}
}

void MiceObj::daikei()//台形加速を行う
{
	if (isKasokuEnd == false && !my_cm.isTurn && !my_cm.isSenkai && !my_cm.isDiagStra)//直進
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
	else if (isKasokuEnd == false && !my_cm.isTurn && !my_cm.isSenkai)//斜め直進
	{
		if (fabs((double)pos_x - (double)first_pos_x) < (double)(tar_x/1.414) && fabs((double)pos_y - (double)first_pos_y) < (double)(tar_x/1.414))//2定速区間
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
			float bu_tar_x;
			bu_tar_x = (my_cm.TRFL) ? -1 * tar_x : tar_x;
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