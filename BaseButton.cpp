#include "BaseButton.h"
#include "Mouse.h"

void BaseButton::Initialize()
{

}

void BaseButton::Update()
{
	
}

void BaseButton::Draw()
{

}

void BaseButton::Finalize()
{

}

void BaseButton::SetEventer(OnClickEventer* eventer)
{
	myEventer = eventer;
}

void BaseButton::SetPosButton(float bx, float by, float blot)
{
	x = bx;
	y = Mouse::getInstance()->WindowHeight-by;
	lot = blot;
}

void BaseButton::SetKitiBool(bool buisButton)
{
	isButton = buisButton;
}

int BaseButton::RetOn()//壁のあるなしを返す関数
{
	if (isOnButton)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void BaseButton::Set_On_Button(bool buisButtonOn)//ボタンのオン，オフをセットする関数
{
	isOnButton = buisButtonOn;
}