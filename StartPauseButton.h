#pragma once
#include "BaseButton.h"

class StartPauseButton : public BaseButton
{
private:
	int button_width = 100;//ボタンの横の大きさ
	int button_height = 50;//ボタンの縦の大きさ

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};