#pragma once
#include "SimTask.h"
#include "InputData.h"
#include "ButtonMgr.h"
#include "MiceObj.h"
#include "Command.h"

class MiceMgr : public SimTask
{
    bool isKasokuEnd = true;
public:
    InputData input;
    MiceObj miceObj;
    ButtonMgr buttonMgr;

public:
    void Initialize();
    void Finalize();
    void Update();
    void Draw();
    void SetAct(enum command_type type);
    bool RetKasokuEnd();
    bool RetStartPause();
};