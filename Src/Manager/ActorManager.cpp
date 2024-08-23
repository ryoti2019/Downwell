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
	for (auto& data : deactiveActorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Update();
		}
	}
}

void ActorManager::Draw()
{
	for (auto& data : deactiveActorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Draw();
		}
	}
}

void ActorManager::Release()
{
	for (auto& data : deactiveActorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Release();
		}
	}
}

std::shared_ptr<Actor> ActorManager::ActivateData(const ActorType type)
{
	// actorDataの中にすでに同じ型が生成されているかチェックする
	auto deactorElem = deactiveActorData_.find(type);

	if (deactorElem == deactiveActorData_.end()) return nullptr; 
	//if (actorElem == activeActorData_.end())
	//{
	//}
	const int a = 1;

	const std::vector<std::shared_ptr<Actor>>& deactiveData = deactiveActorData_[type];
	std::vector<std::shared_ptr<Actor>> activeData = activeActorData_[type];

	std::shared_ptr<Actor> active = deactiveData.front();
	deactiveActorData_[type].erase(deactiveActorData_[type].begin());

	active->SetIsActive(true);

 	activeActorData_[type].emplace_back(active);

	return active;

}