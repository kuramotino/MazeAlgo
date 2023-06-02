#include "StopButton.h"
#include "DxLib.h"
#include "Mouse.h"

void StopButton::Initialize()
{

}

void StopButton::Update()
{
	if (isButton && isVisible)
	{
		isSelected = Mouse::getInstance()->isOnPointer(x, -1 * (y - Mouse::getInstance()->WindowHeight) - button_height / 2, x + button_width / 2, -1 * (y - Mouse::getInstance()->WindowHeight) + button_height / 2);

		isOnClick = Mouse::getInstance()->isClicked(Mouse::getInstance()->LEFT_CLICK);
		if (isOnClick && isSelected)
		{
			isOnButton = !isOnButton;
			myEventer->OnClick(UI::StopInit);
		}
	}
}

void StopButton::Draw()
{
	int Red = GetColor(255, 0, 0);
	DrawFormatString(x, y, Red, "Stop", x, y);
}

void StopButton::Finalize()
{

}