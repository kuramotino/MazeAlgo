#include "StartPauseButton.h"
#include "DxLib.h"
#include "Mouse.h"

void StartPauseButton::Initialize()
{

}

void StartPauseButton::Update()
{
	if (isButton && isVisible)
	{
		isSelected = Mouse::getInstance()->isOnPointer(x, -1 * (y - Mouse::getInstance()->WindowHeight) - button_height / 2, x + button_width / 2, -1 * (y - Mouse::getInstance()->WindowHeight) + button_height / 2);

		isOnClick = Mouse::getInstance()->isClicked(Mouse::getInstance()->LEFT_CLICK);
		if (isOnClick && isSelected)
		{
			isOnButton = !isOnButton;
			myEventer->OnClick(UI::Wall_StartPause);
		}
	}
}

void StartPauseButton::Draw()
{
	int Red = GetColor(255, 0, 0);
	DrawFormatString(x, y, Red, "Start/Pause", x, y);
}

void StartPauseButton::Finalize()
{

}