#include "GravityManager.h"

GravityManager* GravityManager::instance_ = nullptr;

void GravityManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GravityManager();
	}
}

float GravityManager::AddGravity(float jumpPow)
{
	// 現在のジャンプ力に重力を加える
	float pow = jumpPow + GRAVITY;
	return pow;
}

GravityManager::GravityManager(void)
{
}

GravityManager::GravityManager(const GravityManager&)
{
}
