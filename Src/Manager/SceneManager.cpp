#include <chrono>
#include <DxLib.h>
#include "ResourceManager.h"
#include "SceneManager.h"
#include "../Scene/SceneBase.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Manager/ActorManager.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

void SceneManager::Init()
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = std::make_unique<TitleScene>();
	scene_->Init();

	isSceneChanging_ = false;

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	// �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);

	// �Q�[���p�b�h���g���Ƃ�true
	isGamePad_ = false;

	// ��������̃t���O
	isOperation_ = true;

}

void SceneManager::Update()
{

	if (scene_ == nullptr)
	{
		return;
	}

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	if (!isSceneChanging_)
	{
		scene_->Update();
	}

}

void SceneManager::Draw()
{

	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();

	// �`��
	scene_->Draw();

}

void SceneManager::Destroy()
{
	delete instance_;
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	isSceneChanging_ = true;

}

SceneManager::SceneManager()
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;

	isSceneChanging_ = false;

	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;

}

void SceneManager::ResetDeltaTime()
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	// ���\�[�X�̉��
	ResourceManager::GetInstance().Release();

	// �V�[����ύX����
	sceneId_ = sceneId;

	// ���݂̃V�[�������
	if (scene_ != nullptr)
	{
		scene_->Release();
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = std::make_unique<TitleScene>();
		break;
	case SCENE_ID::GAME:
		scene_ = std::make_unique<GameScene>();
		break;
	}

	scene_->Init();

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}
