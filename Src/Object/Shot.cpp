#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::Init()
{

	playerImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IDLE).handleIds_;

	actorType_ = ActorType::SHOT;
	isActive_ = false;

	animCnt_ = 0;

	pos_ = { 0.0f,0.0f };
}

void Shot::Update()
{
	if (isActive_)
	{
		Move();
	}
}

void Shot::Draw()
{
	animIdx_ = (animCnt_ / 10) % PLAYER_IMAGE_NUM;

	// ÉvÉåÉCÉÑÅ[ÇÃï`âÊ
	if (isActive_)
	{
		DrawRotaGraph(pos_.x, pos_.y, 2.0, 0.0, playerImg_[animIdx_], true);
	}

	animCnt_++;
}

void Shot::Release()
{
}

void Shot::Move()
{
	pos_.y++;
}
