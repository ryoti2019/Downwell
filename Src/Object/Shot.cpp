#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::Init(const Vector2F& pos)
{

	shotImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::SHOT).handleIds_;

	actorType_ = ActorType::SHOT;
	isAlive_ = false;
	speed_ = SHOT_SPEED;

	animCnt_ = 0.0f;
	aliveCnt_ = 0.0f;

	pos_ = { 0.0f,0.0f };

	Actor::Init(pos);

}

void Shot::Update()
{

	Move();

	if (aliveCnt_ >= ALIVE_TIME)
	{
		SetIsActive(false);
	}

	aliveCnt_ += SceneManager::GetInstance().GetDeltaTime();
	
}

void Shot::Draw()
{
	animIdx_ = (animCnt_ / 10) % SHOT_IMAGE_NUM;

	// ’e‚Ì•`‰æ
	if (GetIsActive())
	{
		DrawRotaGraph(pos_.x, pos_.y, 2.0, 0.0, shotImg_[animIdx_], true);
	}

	animCnt_++;
}

void Shot::Release()
{
}

void Shot::Move()
{
	movePow_ = speed_* (int)DIR::DOWN;
	pos_.y += movePow_;
}
