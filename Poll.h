#pragma once
#include "BaseButton.h"
//�Ǐ���ʒu����ۊǂ���N���X
class Poll : public BaseButton
{
private:
    int button_width = 4;//�{�^���̉��̑傫��
    int button_height = 4;//�{�^���̏c�̑傫��

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
};
