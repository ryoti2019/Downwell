#include "ActorManager.h"
#include "../Object/Player.h"

ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
}

void ActorManager::Init()
{
	for (auto& data : actorData_)
	{
		for (auto& actor : data.second)
		{
			actor->Init();
		}
	}
}

void ActorManager::Update()
{
	for (auto& data : actorData_)
	{
		for (auto& actor : data.second)
		{
			actor->Update();
		}
	}
}

void ActorManager::Draw()
{
	for (auto& data : actorData_)
	{
		for (auto& actor : data.second)
		{
			actor->Draw();
		}
	}
}

void ActorManager::Release()
{
	for (auto& data : actorData_)
	{
		for (auto& actor : data.second)
		{
			actor->Release();
		}
	}
}

std::vector<std::shared_ptr<Actor>> ActorManager::GetActorData()
{
	for (auto& data : actorData_)
	{
		return data.second;
	}
}