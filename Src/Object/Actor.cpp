#include "Actor.h"

Actor::Actor(void)
{
}

Actor::~Actor(void)
{
}

void Actor::Init(void)
{
}

void Actor::Update(void)
{
}

void Actor::Draw(void)
{
}

void Actor::Release(void)
{
}

void Actor::GetHP(void)
{
}

void Actor::DecreaseHP(int hp)
{
	hp_ -= hp;
}

void Actor::Move(void)
{
}

void Actor::Collision(void)
{
}

bool Actor::IsAlive(void)
{

	// HP��0�ȉ��ɂȂ����玀��ł��锻��
	if (hp_ <= 0)
	{
		return false;
	}

	return true;

}
