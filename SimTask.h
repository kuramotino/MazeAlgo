#pragma once
//���H�V�~�����[�^�̃N���X�B�V�~�����[�^�̃��W���[���͂��ׂĂ���SimTask�N���X���p������B
class SimTask {
public:
    virtual void Initialize();     //�����������͎������Ă����Ȃ��Ă�����
    virtual void Finalize();     //�I�������͎������Ă����Ȃ��Ă�����
    virtual void Update();   //�X�V�����͕K���p����Ŏ�������
    virtual void Draw();   //�`�揈���͕K���p����Ŏ�������
};
