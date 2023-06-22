#pragma once
#include "SimTask.h"
#include "Command.h"

class MiceObj : public SimTask
{
    float pos_x = 47;//初期位置47
    float pos_y = 30;//初期位置30
    float first_pos_x = 0;//0
    float first_pos_y = 0;//0
    float first_lot = 0;
    float tar_x = 0;
    float lot = 0;
    float now_v = 0;
    float x2 = 0;//slalomの中間点
    float y2 = 0;
    float x3 = 0;//slalomの終点
    float y3 = 0;
    float sla_t = 0;//変数t(0<t<1)
    int Handle = 0;//画像のデータハンドル
    bool isKasokuEnd = true;//加速が終わったかどうか
   

    Command my_cm;

    float bu_x1_2;
    float bu_y1_2;
    float bu_x2_3;
    float bu_y2_3;
    bool bu_TRFL = false;

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
    void SetDaikei(Command cm);
    void daikei();//台形加速を行う
    bool RetisKasoku();//加速フラグを返す
};
