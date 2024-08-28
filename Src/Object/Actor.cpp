#include <DxLib.h>
#include "Actor.h"

void Actor::Init(const Vector2F& pos)
{

#pragma region オブジェクトの情報

	SetPos(pos);
	movedPos_ = { 0.0f,0.0f };
	size_ = { 0.0f,0.0f };
	dir_ = { 0.0f,0.0f };
	speed_ = 10.0f;
	movePow_ = 0.0f;
	hp_ = 0;
	isHit_ = false;
	actorType_ = ActorType::MAX;
	isAlive_ = true;
	isActive_ = false;

#pragma endregion

#pragma region アニメーション

	img_ = 0;
	imgExtRate_ = 1.0;
	imgAngle_ = 0.0;
	turnXFlag_ = false;
	turnYFlag_ = false;
	animCnt_ = 0;
	animIdx_ = 0;

#pragma endregion
}

void Actor::Create(const Vector2F& pos)
{



}

void Actor::Update(const float deltaTime)
{
}

void Actor::Draw()
{
	DrawRotaGraphF(pos_.x, pos_.y, imgExtRate_, imgAngle_, img_[animIdx_], true, turnXFlag_, turnYFlag_);
	DrawBoxAA(pos_.x - 3.0f, pos_.y - 3.0f, pos_.x + 3.0f, pos_.y + 3.0f, 0xff0000, true);
}

void Actor::DrawMap()
{
}

void Actor::Release()
{
}

void Actor::Move(const float deltaTime)
{
}

void Actor::Collision()
{
}