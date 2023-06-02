#pragma once

#include "Singleton.h"

class Mouse : public Singleton<Mouse> {

    Mouse();
    friend Singleton< Mouse >;

public:
    static constexpr int LEFT_CLICK = 0;
    static constexpr int RIGHT_CLICK = 1;

    int WindowHeight = 600;

    bool update();	//�X�V
    int getPressingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾
    int getReleasingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾
    int getX() { return _x; }
    int getY() { return _y; }
    bool isClicked(int keyCode);//keyCode�̃L�[���N���b�N���ꂽ�u�Ԃ��ǂ����𔻒肷��
    bool isOnPointer(int zero_x, int zero_y, int end_x, int end_y);//�|�C���^���w�肵���̈���ɂ��邩�ǂ����𔻒肷��֐�

private:
    static constexpr int KEY_NUM = 8;	//�L�[����
    int _x, _y;
    int _buttonPressingCount[KEY_NUM];//������J�E���^
    int _buttonReleasingCount[KEY_NUM];//������J�E���^

    bool isAvailableCode(int keyCode);//keyCode���L���ȃL�[�ԍ����₤

};