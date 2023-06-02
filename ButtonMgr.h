#pragma once
#include "SimTask.h"
#include "OnClickEventer.h"
#include "InputData.h"
#include "BaseButton.h"

//Buttonの配置，表示非表示，ボタンが押されたかどうかを監視するクラス
class ButtonMgr : public SimTask,OnClickEventer
{
    BaseButton* myWallColume[15][16];//壁ボタンのポインタ，左の添え字が行，右が列
    BaseButton* myWallRow[15][16];//壁ボタンのポインタ，左の添え字が列，右が行
    BaseButton* myKitiWallColume[2][16];//既知壁のポインタ，左の添え字0左，1右
    BaseButton* myKitiWallRow[2][16];//既知壁のポインタ，左の添え字0下，1上
    BaseButton* myPoll[17][17];//柱のポインタ
    BaseButton* myResetWall;//壁リセットボタンのポインタ
    BaseButton* myStartPauseButton;//スタート/ポーズボタンのポインタ
    BaseButton* myStopButton;//ストップボタンのポインタ

    InputData* myInput;//InputDataのポインタ

    float zero_x = 30;//壁を置く0点座標
    float zero_y = 30;//壁を置く0点座標
    float dx = 34;//壁と壁の間隔
    float dy = 34;//壁と壁の間隔
    float dx_poll = 34;//柱と柱の間隔
    float dy_poll = 34;//柱と柱の間隔
    bool isPause = true;//Pause状態かどうか
    bool isPushStop = false;//ストップボタンが押されたかどうか


public:
    void Initialize();     
    void Finalize();    
    void Update();   
    void Draw();
    void OnClick(UI:: ButtonType type);//ボタンが押されたときに呼ばれる関数，OnClickEventerをoverride
    void SetInput(InputData* buinput);
    bool RetisPause();
    bool RetisStop();
};
