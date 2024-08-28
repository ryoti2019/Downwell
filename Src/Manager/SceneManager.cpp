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

	// 初期シーンの設定
	DoChangeScene(SCENE_ID::TITLE);

	// ゲームパッドを使うときtrue
	isGamePad_ = false;

	// 操作説明のフラグ
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

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();

	// 描画
	scene_->Draw();

}

void SceneManager::Destroy()
{
	delete instance_;
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
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

	// リソースの解放
	ResourceManager::GetInstance().Release();

	// シーンを変更する
	sceneId_ = sceneId;

	// 現在のシーンを解放
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
