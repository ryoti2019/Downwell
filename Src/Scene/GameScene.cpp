#include <DxLib.h>
#include "../Manager/ActorManager.h"
#include "../Application.h"
#include "GameScene.h"
#include "../Object/Player.h"
#include "../Object/Shot.h"
#include "../Object/Stage.h"

GameScene::GameScene()
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	// アクター管理クラス
	actorManager_ = std::make_shared<ActorManager>();
	actorManager_->Init();

	// プレイヤーを生成
	actorManager_->CreateActor<Player>();
	actorManager_->ActiveData(ActorType::PLAYER, { Application::SCREEN_SIZE_X / 2,0 });

	// 弾を生成
	for (int i = 0; i < 50; i++)
	{
		actorManager_->CreateActor<Shot>();
	}

	stage_.emplace_back();

	for (auto& stage : stage_)
	{
		stage = std::make_unique<Stage>();
	}

}

void GameScene::Update(void)
{
	actorManager_->Update();
}

void GameScene::Draw(void)
{

	actorManager_->Draw();

	DrawFormatString(0, 0, 0xff0000, "GameScene");

}

void GameScene::Release(void)
{
	actorManager_->Release();
}