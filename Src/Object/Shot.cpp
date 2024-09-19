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

	Actor::Init(pos);
	size_ = { SHOT_IMAGE_X_SIZE,SHOT_IMAGE_Y_SIZE };
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::SHOT).handleIds_;

	actorType_ = ActorType::SHOT;
	isAlive_ = false;
	speed_ = SHOT_SPEED;

	animCnt_ = 0.0f;
	aliveCnt_ = 0.0f;
	imgExtRate_ = 2.0f;
	
}

void Shot::Update(const float deltaTime)
{

	Move(deltaTime);

	if (aliveCnt_ >= ALIVE_TIME)
	{
		SetIsActive(false);
	}

	aliveCnt_ += deltaTime;

	animIdx_ = (animCnt_ / 10) % SHOT_IMAGE_NUM;
	animCnt_++;

}

void Shot::Release()
{
}

void Shot::Move(const float deltaTime)
{
	Vector2F movePow = Vector2F::vectorDown * speed_;
	Vector2F resultPos = GetPos();
	resultPos += movePow;
	SetPos(resultPos);
}
