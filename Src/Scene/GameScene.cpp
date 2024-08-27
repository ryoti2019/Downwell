#include <DxLib.h>
#include "../Manager/ActorManager.h"
#include "../Manager/CollisionManager.h"
#include "../Application.h"
#include "GameScene.h"
#include "../Object/Stage.h"

void GameScene::Init(void)
{

	// �A�N�^�[�Ǘ��N���X
	actorManager_ = std::make_shared<ActorManager>();
	actorManager_->Init();
	
	// �Փ˔���Ǘ��N���X
	collisionManager_ = std::make_shared<CollisionManager>();
	collisionManager_->Init();

	// �X�e�[�W�𐶐�
	stage_ = std::make_unique<Stage>();
	stage_->Init();

}

void GameScene::Update(void)
{

	actorManager_->Update();

	stage_->Update();

}

void GameScene::Draw(void)
{

	actorManager_->Draw();

	stage_->Draw();

	DrawFormatString(0, 0, 0xff0000, "GameScene");

}

void GameScene::Release(void)
{

	actorManager_->Release();

	stage_->Release();

}