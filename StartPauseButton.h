#pragma once
#include "BaseButton.h"

class StartPauseButton : public BaseButton
{
private:
	int button_width = 100;//�{�^���̉��̑傫��
	int button_height = 50;//�{�^���̏c�̑傫��

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};