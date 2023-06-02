#include <DxLib.h>
#include "Mouse.h"

Mouse::Mouse() : _buttonPressingCount(), _buttonReleasingCount(), _x(), _y() {
}

//�X�V
bool Mouse::update() {
    int nowButtonState = GetMouseInput();
    GetMousePoint(&_x, &_y);
    _y = WindowHeight - _y;
    for (int i = 0; i < KEY_NUM; i++) {
        if ((nowButtonState >> i) & 1) {            //i�Ԃ̃{�^����������Ă�����
            if (_buttonReleasingCount[i] > 0) {//������J�E���^��0���傫�����
                _buttonReleasingCount[i] = 0;   //0�ɖ߂�
            }
            _buttonPressingCount[i]++;          //������J�E���^�𑝂₷
        }
        else {                             //i�Ԃ̃L�[��������Ă�����
            if (_buttonPressingCount[i] > 0) { //������J�E���^��0���傫�����
                _buttonPressingCount[i] = 0;    //0�ɖ߂�
            }
            _buttonReleasingCount[i]++;         //������J�E���^�𑝂₷
        }
    }
    return true;
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::getPressingCount(int keyCode) {
    if (!isAvailableCode(keyCode)) {
        return -1;
    }
    return _buttonPressingCount[keyCode];
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::getReleasingCount(int keyCode) {
    if (!isAvailableCode(keyCode)) {
        return -1;
    }
    return _buttonReleasingCount[keyCode];
}

//keyCode���L���Ȓl���`�F�b�N����
bool Mouse::isAvailableCode(int keyCode) {
    if (!(0 <= keyCode && keyCode < KEY_NUM)) {
        return false;
    }
    return true;
}
bool Mouse::isClicked(int keyCode)//keyCode�̃L�[���N���b�N���ꂽ�u�Ԃ��ǂ����𔻒肷��
{
    if (getPressingCount(keyCode) == 1)
    {
        return true;
    }
    return false;
}
bool Mouse::isOnPointer(int zero_x, int zero_y, int end_x, int end_y)//�|�C���^���w�肵���̈���ɂ��邩�ǂ����𔻒肷��֐�
{
    if (zero_x < _x && _x < end_x && zero_y < _y && _y < end_y)
    {
        return true;
    }
    return false;
}
