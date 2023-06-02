#include <DxLib.h>
#include "Mouse.h"

Mouse::Mouse() : _buttonPressingCount(), _buttonReleasingCount(), _x(), _y() {
}

//更新
bool Mouse::update() {
    int nowButtonState = GetMouseInput();
    GetMousePoint(&_x, &_y);
    _y = WindowHeight - _y;
    for (int i = 0; i < KEY_NUM; i++) {
        if ((nowButtonState >> i) & 1) {            //i番のボタンが押されていたら
            if (_buttonReleasingCount[i] > 0) {//離されカウンタが0より大きければ
                _buttonReleasingCount[i] = 0;   //0に戻す
            }
            _buttonPressingCount[i]++;          //押されカウンタを増やす
        }
        else {                             //i番のキーが離されていたら
            if (_buttonPressingCount[i] > 0) { //押されカウンタが0より大きければ
                _buttonPressingCount[i] = 0;    //0に戻す
            }
            _buttonReleasingCount[i]++;         //離されカウンタを増やす
        }
    }
    return true;
}

//keyCodeのキーが押されているフレーム数を返す
int Mouse::getPressingCount(int keyCode) {
    if (!isAvailableCode(keyCode)) {
        return -1;
    }
    return _buttonPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int Mouse::getReleasingCount(int keyCode) {
    if (!isAvailableCode(keyCode)) {
        return -1;
    }
    return _buttonReleasingCount[keyCode];
}

//keyCodeが有効な値かチェックする
bool Mouse::isAvailableCode(int keyCode) {
    if (!(0 <= keyCode && keyCode < KEY_NUM)) {
        return false;
    }
    return true;
}
bool Mouse::isClicked(int keyCode)//keyCodeのキーがクリックされた瞬間かどうかを判定する
{
    if (getPressingCount(keyCode) == 1)
    {
        return true;
    }
    return false;
}
bool Mouse::isOnPointer(int zero_x, int zero_y, int end_x, int end_y)//ポインタが指定した領域内にあるかどうかを判定する関数
{
    if (zero_x < _x && _x < end_x && zero_y < _y && _y < end_y)
    {
        return true;
    }
    return false;
}
