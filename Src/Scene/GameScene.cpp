#include <DxLib.h>
#include "../Manager/ActorManager.h"
#include "GameScene.h"
#include "../Object/Player.h"
#include "../Object/Shot.h"

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

	actorManager_->CreateActor<Player>();
	
	// 弾の生成
	actorManager_->CreateActor<Shot>();

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
