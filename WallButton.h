#pragma once
//�Ǐ���ύX����{�^��
#include "BaseButton.h"

class WallButton : public BaseButton
{
private:
    int button_width = 40;//�{�^���̉��̑傫��
    int button_height = 16;//�{�^���̏c�̑傫��

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
};


