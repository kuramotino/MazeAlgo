#pragma once
#include "SimTask.h"
#include "OnClickEventer.h"
#include "InputData.h"
#include "BaseButton.h"

//Button�̔z�u�C�\����\���C�{�^���������ꂽ���ǂ������Ď�����N���X
class ButtonMgr : public SimTask,OnClickEventer
{
    BaseButton* myWallColume[15][16];//�ǃ{�^���̃|�C���^�C���̓Y�������s�C�E����
    BaseButton* myWallRow[15][16];//�ǃ{�^���̃|�C���^�C���̓Y��������C�E���s
    BaseButton* myKitiWallColume[2][16];//���m�ǂ̃|�C���^�C���̓Y����0���C1�E
    BaseButton* myKitiWallRow[2][16];//���m�ǂ̃|�C���^�C���̓Y����0���C1��
    BaseButton* myPoll[17][17];//���̃|�C���^
    BaseButton* myResetWall;//�ǃ��Z�b�g�{�^���̃|�C���^
    BaseButton* myStartPauseButton;//�X�^�[�g/�|�[�Y�{�^���̃|�C���^
    BaseButton* myStopButton;//�X�g�b�v�{�^���̃|�C���^

    InputData* myInput;//InputData�̃|�C���^

    float zero_x = 30;//�ǂ�u��0�_���W
    float zero_y = 30;//�ǂ�u��0�_���W
    float dx = 34;//�ǂƕǂ̊Ԋu
    float dy = 34;//�ǂƕǂ̊Ԋu
    float dx_poll = 34;//���ƒ��̊Ԋu
    float dy_poll = 34;//���ƒ��̊Ԋu
    bool isPause = true;//Pause��Ԃ��ǂ���
    bool isPushStop = false;//�X�g�b�v�{�^���������ꂽ���ǂ���


public:
    void Initialize();     
    void Finalize();    
    void Update();   
    void Draw();
    void OnClick(UI:: ButtonType type);//�{�^���������ꂽ�Ƃ��ɌĂ΂��֐��COnClickEventer��override
    void SetInput(InputData* buinput);
    bool RetisPause();
    bool RetisStop();
};
