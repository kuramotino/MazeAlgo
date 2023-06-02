#pragma once
//壁情報を変更するボタン
#include "BaseButton.h"

class WallButton : public BaseButton
{
private:
    int button_width = 40;//ボタンの横の大きさ
    int button_height = 16;//ボタンの縦の大きさ

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
};


