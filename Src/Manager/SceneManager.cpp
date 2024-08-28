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

	// �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);

	// �Q�[���p�b�h���g���Ƃ�true
	isGamePad_ = false;

	// ��������̃t���O
	isOperation_ = true;

}

void SceneManager::Update(const float deltaTime)
{

	if (scene_ == nullptr)
	{
		return;
	}

	if (!isSceneChanging_)
	{
		scene_->Update(deltaTime);
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

	waitSceneId_ = SCENE_ID::NONE;

}
