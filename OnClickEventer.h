#pragma once
namespace UI
{
	typedef enum {
		Wall_Button,    //�{�^��
		Wall_Reset,		//Wall�����Z�b�g
		Wall_StartPause, //�X�^�[�g���|�[�Y����
		StopInit,		//�}�E�X��������Ԃɖ߂�
		Button_None,    //����
	} ButtonType;
};

//�{�^���������ꂽ�Ƃ��̏����̂��߂̃C���^�[�t�F�C�X�N���X
class OnClickEventer
{
	
public:
	virtual void OnClick(UI::ButtonType type);//�{�^���������ꂽ�Ƃ��ɌĂ΂��֐�
};
