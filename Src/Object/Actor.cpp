#include <DxLib.h>
#include "Actor.h"

void Actor::Init(const Vector2F& pos)
{
	SetPos(pos);
}

void Actor::Update()
{
}

void Actor::Draw()
{
	DrawGraph(pos_.x, pos_.y, img_[], true);
}

void Actor::Release()
{
}

void Actor::Move()
{
}

void Actor::Collision()
{
}