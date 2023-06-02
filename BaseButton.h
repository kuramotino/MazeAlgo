#pragma once
#include "SimTask.h"
#include "OnClickEventer.h"

//すべてのボタンの基底クラス
class BaseButton : public SimTask
{
protected:
    OnClickEventer* myEventer;//ボタン押下時の処理のインターフェイス
    float x = 0;
    float y = 0;
    float lot = 0;
    int Handle = 0;//画像のデータハンドル
    bool isButton = true;//押すことのできるボタンかどうか
    bool isVisible = true;//ボタンが表示されているか
    bool isOnClick = false;//クリックされた状態かどうか
    bool isOnButton = true;//ボタンが押されてOnになっているかどうか
    bool isSelected = false;//ボタンが選択されているかどうか

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
    void SetEventer(OnClickEventer* eventer);//OnClickEventerをセットする関数，ButtonMgrに呼ばれる
    void SetPosButton(float x,float y,float lot);//ボタンの位置と向きをセットする関数，ButtonMgrに呼ばれる
    void SetKitiBool(bool buisKiti);
    int RetOn();//壁のあるなしを返す関数
    void Set_On_Button(bool buisButtonOn);//ボタンのオン，オフをセットする関数
};