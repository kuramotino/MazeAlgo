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

int BaseButton::RetOn()//�ǂ̂���Ȃ���Ԃ��֐�
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

void BaseButton::Set_On_Button(bool buisButtonOn)//�{�^���̃I���C�I�t���Z�b�g����֐�
{
	isOnButton = buisButtonOn;
}