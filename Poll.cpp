#include "Poll.h"
#include "DxLib.h"


void Poll::Initialize()
{
	Handle = LoadGraph("D:/お絵描き/mouse/pollimg.png"); // 画像をロード
	DrawRotaGraph(x, y, 1, lot, Handle, TRUE); // データハンドルを使って画像を描画
}

void Poll::Update()
{
	
}

void Poll::Draw()
{
	
	DrawRotaGraph(x, y, 1, lot, Handle, TRUE); // データハンドルを使って画像を描画
	
}

void Poll::Finalize()
{

}