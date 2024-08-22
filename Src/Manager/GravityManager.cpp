#include "GravityManager.h"

GravityManager* GravityManager::instance_ = nullptr;

void GravityManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GravityManager();
	}
}

GravityManager& GravityManager::GetInstance()
{
	return *instance_;
}

float GravityManager::AddGravity(float jumpPow)
{
	// Œ»İ‚ÌƒWƒƒƒ“ƒv—Í‚Éd—Í‚ğ‰Á‚¦‚é
	float pow = jumpPow + GRAVITY;
	return pow;
}

GravityManager::GravityManager(void)
{
}

GravityManager::GravityManager(const GravityManager&)
{
}
