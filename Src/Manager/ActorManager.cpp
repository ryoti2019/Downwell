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
}

void ActorManager::Update()
{
	for (auto& data : actorData_)
	{
		// autoではなく、分かる型名はその型名で書く
		// 前にconstをつけることで、Actorの箱を書き換えるのを止める
		// ４バイト以上あるものは「&」をつけることで、４バイトになるので節約できる
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Update();
		}
	}
}

void ActorManager::Draw()
{
	for (auto& data : actorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Draw();
		}
	}
}

void ActorManager::Release()
{
	for (auto& data : actorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
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