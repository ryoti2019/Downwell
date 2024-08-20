#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "Player.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init(void)
{
	playerImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IDLE).handleIds_;
}

void Player::Update(void)
{

	// ˆÚ“®ˆ—
	Move();

}

void Player::Draw(void)
{

}

void Player::Release(void)
{
}

void Player::Move(void)
{

	if (InputManager::GetInstance().IsNew(KEY_INPUT_A))
	{
		dir_.x = -1.0f;
		speed_ = 10.0f;
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_D))
	{
		dir_.x = 1.0f;
		speed_ = 10.0f;
	}

	pos_.x = dir_.x * speed_;

}

void Player::Jump(void)
{
}
