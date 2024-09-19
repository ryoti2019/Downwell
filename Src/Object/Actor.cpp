#include <DxLib.h>
#include "Actor.h"

void Actor::Init(const Vector2F& pos)
{

#pragma region オブジェクトの情報

	SetPos(pos);
	size_ = { 0.0f,0.0f };
	speed_ = 10.0f;
	hp_ = 0;
	isHitFoot_ = false;
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

void Actor::OnCollision()
{
}

void Actor::Draw()
{
	DrawRotaGraphF(pos_.x, pos_.y, imgExtRate_, imgAngle_, img_[animIdx_], true, turnXFlag_, turnYFlag_);
	DrawBoxAA(pos_.x - 3.0f, pos_.y - 3.0f, pos_.x + 3.0f, pos_.y + 3.0f, 0xff0000, true);
	DrawBoxAA(pos_.x - (size_.x / 2) - 3.0f, pos_.y + (size_.y / 2) - 3.0f,
			  pos_.x - (size_.x / 2) + 3.0f, pos_.y + (size_.y / 2) + 3.0f, 0xff0000, true);
	DrawBoxAA(pos_.x + (size_.x / 2) - 3.0f, pos_.y + (size_.y / 2) - 3.0f,
			  pos_.x + (size_.x / 2) + 3.0f, pos_.y + (size_.y / 2) + 3.0f, 0xff0000, true);
	DrawBoxAA(colPos_.x - 3, colPos_.y - 3, colPos_.x + 3, colPos_.y + 3, 0x00ff00, true);
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