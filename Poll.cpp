#include "Poll.h"
#include "DxLib.h"


void Poll::Initialize()
{
	Handle = LoadGraph("D:/���G�`��/mouse/pollimg.png"); // �摜�����[�h
	DrawRotaGraph(x, y, 1, lot, Handle, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
}

void Poll::Update()
{
	
}

void Poll::Draw()
{
	
	DrawRotaGraph(x, y, 1, lot, Handle, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
	
}

void Poll::Finalize()
{

}