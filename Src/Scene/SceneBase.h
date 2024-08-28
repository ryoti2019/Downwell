#pragma once

class SceneBase
{

public:

	// �R���X�g���N�^
	SceneBase();

	// �f�X�g���N�^
	virtual ~SceneBase() = 0;

	// ����������
	virtual void Init() = 0;

	// �X�V�X�e�b�v
	virtual void Update(const float deltaTime) = 0;

	// �`�揈��
	virtual void Draw() = 0;

	// �������
	virtual void Release() = 0;

};