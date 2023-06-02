#include "MiceMgr.h"
#include "Command.h"

void MiceMgr::Initialize()
{
	buttonMgr.SetInput(&input);
	buttonMgr.Initialize();
	miceObj.Initialize();
}

void MiceMgr::Update()
{
	buttonMgr.Update();
	if (!buttonMgr.RetisPause())
	{
		miceObj.Update();
	}
}

void MiceMgr::Draw()
{
	buttonMgr.Draw();
	miceObj.Draw();
}

void MiceMgr::Finalize()
{
	buttonMgr.Finalize();
	miceObj.Finalize();
}

void MiceMgr::SetAct(enum command_type type)
{
	if (miceObj.RetisKasoku() == true)
	{
		Command cm(type);
		miceObj.SetDaikei(cm);
	}
	isKasokuEnd = miceObj.RetisKasoku();
}

bool MiceMgr::RetKasokuEnd()
{
	return miceObj.RetisKasoku();
}

bool MiceMgr::RetStartPause()
{
	return buttonMgr.RetisPause();
}
