#pragma once
#include "SimTask.h"
#include "OnClickEventer.h"

//���ׂẴ{�^���̊��N���X
class BaseButton : public SimTask
{
protected:
    OnClickEventer* myEventer;//�{�^���������̏����̃C���^�[�t�F�C�X
    float x = 0;
    float y = 0;
    float lot = 0;
    int Handle = 0;//�摜�̃f�[�^�n���h��
    bool isButton = true;//�������Ƃ̂ł���{�^�����ǂ���
    bool isVisible = true;//�{�^�����\������Ă��邩
    bool isOnClick = false;//�N���b�N���ꂽ��Ԃ��ǂ���
    bool isOnButton = true;//�{�^�����������On�ɂȂ��Ă��邩�ǂ���
    bool isSelected = false;//�{�^�����I������Ă��邩�ǂ���

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
    void SetEventer(OnClickEventer* eventer);//OnClickEventer���Z�b�g����֐��CButtonMgr�ɌĂ΂��
    void SetPosButton(float x,float y,float lot);//�{�^���̈ʒu�ƌ������Z�b�g����֐��CButtonMgr�ɌĂ΂��
    void SetKitiBool(bool buisKiti);
    int RetOn();//�ǂ̂���Ȃ���Ԃ��֐�
    void Set_On_Button(bool buisButtonOn);//�{�^���̃I���C�I�t���Z�b�g����֐�
};