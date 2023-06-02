#include "DxLib.h"
#include "ButtonMgr.h"
#include "InputData.h"
#include "MiceMgr.h"
#include "InitAlgo.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (SetGraphMode(800, 600, 32) == -1) { return -1; }// 画面解像度変更

	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
    //MiceMgr miceMgr;
    //miceMgr.Initialize();
    InitAlgo();

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//画面更新 & メッセージ処理 & 画面消去

        //miceMgr.Update();  //更新
        //miceMgr.Draw();    //描画
        UpDataAlgo();
    }

    //miceMgr.Finalize();

    DxLib_End(); // DXライブラリ終了処理
    return 0;
}
