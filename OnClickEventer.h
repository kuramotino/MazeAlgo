#pragma once
namespace UI
{
	typedef enum {
		Wall_Button,    //ボタン
		Wall_Reset,		//Wallをリセット
		Wall_StartPause, //スタートかポーズする
		StopInit,		//マウスを初期状態に戻す
		Button_None,    //無し
	} ButtonType;
};

//ボタンが押されたときの処理のためのインターフェイスクラス
class OnClickEventer
{
	
public:
	virtual void OnClick(UI::ButtonType type);//ボタンが押されたときに呼ばれる関数
};
