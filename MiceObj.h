#pragma once
#include "SimTask.h"
#include "Command.h"

class MiceObj : public SimTask
{
    float pos_x = 47;
    float pos_y = 30;
    float first_pos_x = 0;
    float first_pos_y = 0;
    float first_lot = 0;
    float tar_x = 0;
    float lot = 0;
    float now_v = 0;
    float x2 = 0;//slalom�̒��ԓ_
    float y2 = 0;
    float x3 = 0;//slalom�̏I�_
    float y3 = 0;
    float sla_t = 0;//�ϐ�t(0<t<1)
    int Handle = 0;//�摜�̃f�[�^�n���h��
    bool isKasokuEnd = true;//�������I��������ǂ���
   

    Command my_cm;

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
    void SetDaikei(Command cm);
    void daikei();//��`�������s��
    bool RetisKasoku();//�����t���O��Ԃ�
};
