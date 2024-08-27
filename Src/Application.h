#pragma once
#include <string>

class Application
{

public:

	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y = 720;

	// �f�[�^�p�X�֘A
	//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_MUSIC;
	//-------------------------------------------

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance();

	// �ÓI�C���X�^���X�̎擾
	static Application& GetInstance();

	// ������
	void Init();

	// �Q�[�����[�v�̊J�n
	void Run();

	// ���\�[�X�̔j��
	void Destroy();

	// �����������^���s�̔���
	bool IsInitFail() const;

	// ��������^���s�̔���
	bool IsReleaseFail() const;

private:

	// �ÓI�C���X�^���X
	static Application* instance_;

	// ���������s
	bool isInitFail_;

	// ������s
	bool isReleaseFail_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Application();

	// �R�s�[�R���X�g���N�^�����l
	Application(const Application&);

	// �f�X�g���N�^�����l
	~Application() = default;

};

