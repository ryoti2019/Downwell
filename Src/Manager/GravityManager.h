#pragma once
#include "../Common/Vector2F.h"

class GravityManager
{

public:

	// �d��
	static constexpr float GRAVITY = 4.0f;

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance();

	// �ÓI�C���X�^���X�̎擾
	static GravityManager& GetInstance() { return *instance_; };

	float AddGravity(float jumpPow);

private:

	// �ÓI�C���X�^���X
	static GravityManager* instance_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	GravityManager();
	// �R�s�[�R���X�g���N�^�����l
	GravityManager(const GravityManager&);
	// �f�X�g���N�^�����l
	~GravityManager() = default;

};

