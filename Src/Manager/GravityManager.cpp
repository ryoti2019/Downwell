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
	// ���݂̃W�����v�͂ɏd�͂�������
	float pow = jumpPow + GRAVITY;
	return pow;
}

GravityManager::GravityManager(void)
{
}

GravityManager::GravityManager(const GravityManager&)
{
}
