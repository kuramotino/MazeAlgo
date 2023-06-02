#include "WallButton.h"
#include "DxLib.h"
#include "Mouse.h"
using namespace UI;

void WallButton::Initialize()
{
	Handle = LoadGraph("wall.png"); // 画像をロード
	DrawRotaGraph(x, y, 1, lot, Handle, TRUE); // データハンドルを使って画像を描画
}

void WallButton::Update()
{
	if (isButton && isVisible)
	{
		if (lot == 0)
		{
			isSelected = Mouse::getInstance()->isOnPointer(x - button_width / 2, -1*(y-Mouse::getInstance()->WindowHeight) - button_height / 2, x + button_width / 2, -1 * (y - Mouse::getInstance()->WindowHeight) + button_height / 2);
		}
		else
		{
			isSelected = Mouse::getInstance()->isOnPointer(x - button_height / 2, -1 * (y - Mouse::getInstance()->WindowHeight) - button_width / 2, x + button_height / 2, -1 * (y - Mouse::getInstance()->WindowHeight) + button_width / 2);
		}

		isOnClick = Mouse::getInstance()->isClicked(Mouse::getInstance()->LEFT_CLICK);
		if (isOnClick && isSelected)
		{
			isOnButton = !isOnButton;
			myEventer->OnClick(Wall_Button);
		}
	}
}

void WallButton::Draw()
{
	if ((!isOnButton && isButton) || !isButton)
	{
		DrawRotaGraph(x, y, 1, lot, Handle, TRUE); // データハンドルを使って画像を描画
	}
}

void WallButton::Finalize()
{

}