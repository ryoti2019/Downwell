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

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = std::make_unique<TitleScene>();
	scene_->Init();

	isSceneChanging_ = false;

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	// 初期シーンの設定
	DoChangeScene(SCENE_ID::TITLE);

	// ゲームパッドを使うときtrue
	isGamePad_ = false;

	// 操作説明のフラグ
	isOperation_ = true;

}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	if (!isSceneChanging_)
	{
		scene_->Update();
	}

	// ゲームシーンとゲームオーバーシーンのみ更新する
	if (sceneId_ == SCENE_ID::GAME || sceneId_ == SCENE_ID::GAMEOVER)
	{
		actorManager_->Update();
	}

}

void SceneManager::Draw(void)
{

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();

	// 描画
	scene_->Draw();

	// ゲームシーンとゲームオーバーシーンのみ描画する
	if (sceneId_ == SCENE_ID::GAME || sceneId_ == SCENE_ID::GAMEOVER)
	{
		actorManager_->Draw();
	}

}

void SceneManager::Destroy(void)
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

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	return 1.0f / 60.0f;
	//return deltaTime_;
}

bool SceneManager::GetGamePad(void)
{
	return isGamePad_;
}

void SceneManager::SetGamePad(bool isPad)
{
	isGamePad_ = isPad;
}

bool SceneManager::GetIsOperation(void)
{
	return isOperation_;
}

void SceneManager::SetIsOperation(bool isOp)
{
	isOperation_ = isOp;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;

	isSceneChanging_ = false;

	// デルタタイム
	deltaTime_ = 1.0f / 60.0f;

}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
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
		actorManager_ = std::make_unique<ActorManager>();
		actorManager_->Init();
		break;
	}

	scene_->Init();

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}