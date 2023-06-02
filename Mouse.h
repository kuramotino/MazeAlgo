#pragma once

#include "Singleton.h"

class Mouse : public Singleton<Mouse> {

    Mouse();
    friend Singleton< Mouse >;

public:
    static constexpr int LEFT_CLICK = 0;
    static constexpr int RIGHT_CLICK = 1;

    int WindowHeight = 600;

    bool update();	//更新
    int getPressingCount(int keyCode);//keyCodeのキーが押されているフレーム数を取得
    int getReleasingCount(int keyCode);//keyCodeのキーが離されているフレーム数を取得
    int getX() { return _x; }
    int getY() { return _y; }
    bool isClicked(int keyCode);//keyCodeのキーがクリックされた瞬間かどうかを判定する
    bool isOnPointer(int zero_x, int zero_y, int end_x, int end_y);//ポインタが指定した領域内にあるかどうかを判定する関数

private:
    static constexpr int KEY_NUM = 8;	//キー総数
    int _x, _y;
    int _buttonPressingCount[KEY_NUM];//押されカウンタ
    int _buttonReleasingCount[KEY_NUM];//離されカウンタ

    bool isAvailableCode(int keyCode);//keyCodeが有効なキー番号か問う

};