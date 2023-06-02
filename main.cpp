#include "DxLib.h"
#include "ButtonMgr.h"
#include "InputData.h"
#include "MiceMgr.h"
#include "InitAlgo.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (SetGraphMode(800, 600, 32) == -1) { return -1; }// ��ʉ𑜓x�ύX

	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
    //MiceMgr miceMgr;
    //miceMgr.Initialize();
    InitAlgo();

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

        //miceMgr.Update();  //�X�V
        //miceMgr.Draw();    //�`��
        UpDataAlgo();
    }

    //miceMgr.Finalize();

    DxLib_End(); // DX���C�u�����I������
    return 0;
}
