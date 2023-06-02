#include "ButtonMgr.h"
#include "WallButton.h"
#include "Mouse.h"
#include "Poll.h"
#include "WallResetButton.h"
#include "StartPauseButton.h"
#include "StopButton.h"

void ButtonMgr::Initialize()
{
	myResetWall = (BaseButton*)new WallResetButton;
	myResetWall->SetEventer(this);
	myResetWall->SetPosButton(600, 500, 0);
	myResetWall->Initialize();

	myStartPauseButton = (BaseButton*)new StartPauseButton;
	myStartPauseButton->SetEventer(this);
	myStartPauseButton->SetPosButton(600, 300, 0);
	myStartPauseButton->Initialize();

	myStopButton = (BaseButton*)new StopButton;
	myStopButton->SetEventer(this);
	myStopButton->SetPosButton(600, 150, 0);
	myStopButton->Initialize();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			myWallColume[i][j] = (BaseButton*)new WallButton;
			myWallColume[i][j]->SetEventer(this);
			myWallColume[i][j]->SetPosButton(zero_x + dx + dx * i, zero_y + dy / 2 + dy * j, 3.14 / 2);
			myWallColume[i][j]->Initialize();
			if (i == 0 && j == 0)
			{
				myWallColume[i][j]->SetKitiBool(false);
			}

			myWallRow[i][j] = (BaseButton*)new WallButton;
			myWallRow[i][j]->SetEventer(this);
			myWallRow[i][j]->SetPosButton(zero_x + dx/2 + dx * j, zero_y + dy + dy * i, 0);
			myWallRow[i][j]->Initialize();
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			myKitiWallColume[i][j] = (BaseButton*)new WallButton;
			myKitiWallColume[i][j]->SetPosButton(zero_x + dx * 16 * i, zero_y + dy / 2 + dy * j, 3.14 / 2);
			myKitiWallColume[i][j]->SetKitiBool(false);
			myKitiWallColume[i][j]->Initialize();

			myKitiWallRow[i][j] = (BaseButton*)new WallButton;
			myKitiWallRow[i][j]->SetPosButton(zero_x + dx / 2 + dx * j, zero_y + dy * 16 * i, 0);
			myKitiWallRow[i][j]->SetKitiBool(false);
			myKitiWallRow[i][j]->Initialize();
		}
	}
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			myPoll[i][j] = (BaseButton*)new Poll;
			myPoll[i][j]->SetPosButton(zero_x + dx_poll * i, zero_y + dy_poll * j, 0);
			myPoll[i][j]->SetKitiBool(false);
			myPoll[i][j]->Initialize();
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (i == 0 && j == 0)
			{
				myInput->SetRowColume(i, j, 1, false);
				myInput->SetRowColume(i, j, 0, true);
			}
			else
			{
				myInput->SetRowColume(i, j, 0, false);
				myInput->SetRowColume(i, j, 0, true);
			}
		}
	}
}

void ButtonMgr::Update()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			myWallColume[i][j]->Update();
			myWallRow[i][j]->Update();
		}
	}
	Mouse::getInstance()->update();
	myResetWall->Update();
	myStartPauseButton->Update();
	myStopButton->Update();
}

void ButtonMgr::Draw()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			myWallColume[i][j]->Draw();
			myWallRow[i][j]->Draw();
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			myKitiWallColume[i][j]->Draw();
			myKitiWallRow[i][j]->Draw();
		}
	}
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			myPoll[i][j]->Draw();
		}
	}
	myResetWall->Draw();
	myStartPauseButton->Draw();
	myStopButton->Draw();
}

void ButtonMgr::Finalize()
{

}

void ButtonMgr::OnClick(UI::ButtonType type)
{
	if (type == UI::Wall_Button)
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (i == 0 && j == 0)
				{
					myInput->SetRowColume(i, j, 1, false);
					int ro_on = myWallRow[i][j]->RetOn();
					myInput->SetRowColume(i, j, ro_on, true);
				}
				else
				{
					int co_on = myWallColume[i][j]->RetOn();
					int ro_on = myWallRow[i][j]->RetOn();
					myInput->SetRowColume(i, j, co_on, false);
					myInput->SetRowColume(i, j, ro_on, true);
				}
			}
		}
	}
	else if (type == UI::Wall_Reset)
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (i == 0 && j == 0)
				{
					myInput->SetRowColume(i, j, 1, false);
					myInput->SetRowColume(i, j, 0, true);
				}
				else
				{
					myInput->SetRowColume(i, j, 0, false);
					myInput->SetRowColume(i, j, 0, true);
				}
				myWallColume[i][j]->Set_On_Button(true);
				myWallRow[i][j]->Set_On_Button(true);
			}
		}
	}
	else if (type == UI::Wall_StartPause)
	{
		isPause = !isPause;
	}
	else if (type == UI::StopInit)
	{
		isPushStop = true;
	}
}

void ButtonMgr::SetInput(InputData* buinput)
{
	myInput = buinput;
}

bool ButtonMgr::RetisPause()
{
	return isPause;
}

bool ButtonMgr::RetisStop()
{
	if (isPushStop)
	{
		isPushStop = false;
		return true;
	}
	return isPushStop;
}