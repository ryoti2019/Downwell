#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "Wall.h"

void Wall::Init(const Vector2F& pos)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::MAP_CHIP).handleIds_;
	actorType_ = ActorType::WALL;
	Actor::Init(pos);
}

void Wall::Update()
{
}

void Wall::Draw()
{
}

void Wall::Release()
{
}