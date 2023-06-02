#pragma once
#include "BaseButton.h"
//壁情報や位置情報を保管するクラス
class Poll : public BaseButton
{
private:
    int button_width = 4;//ボタンの横の大きさ
    int button_height = 4;//ボタンの縦の大きさ

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
};
