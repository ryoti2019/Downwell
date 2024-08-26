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

	// activeActorData_に非アクティブ状態のものがあれば
	// deactiveActorData_に格納する
	int num = 0;
	for (auto& data : activeActorData_)
	{
		num = 0;
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			if (actor && !actor->GetIsActive())
			{
				// 非アクティブになったものを格納
				DeactiveData(actor);

				// 非アクティブになったものを削除
				data.second.erase(data.second.begin() += num);
			}
			num++;
		}
	}

	for (auto& data : activeActorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Update();
		}
	}
}

void ActorManager::Draw()
{
	for (auto& data : activeActorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Draw();
		}
	}
}

void ActorManager::Release()
{
	for (auto& data : activeActorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Release();
		}
	}
}

std::shared_ptr<Actor> ActorManager::ActiveData(const ActorType type, const Vector2F& pos)
{

	// 中身が0の場合は、NULLを返す
	if (deactiveActorData_[type].size() == 0)return nullptr;

	// deactiveActorData_の中にすでに同じ型が生成されているかチェックする
	auto deactorElem = deactiveActorData_.find(type);

	// 生成されていない場合は、NULLを返す
	if (deactorElem == deactiveActorData_.end()) return nullptr;

	// deactiveActorData_の先頭部分を削除してactiveActorData_に格納する
	
	// deactiveActorData_の先頭部分
	std::shared_ptr<Actor> active = deactiveActorData_[type].front();

	// deactiveActorData_の先頭部分を削除
	deactiveActorData_[type].erase(deactiveActorData_[type].begin());

	// アクティブ状態にする
	active->Init(pos);
	active->SetIsActive(true);

	// activeActorData_に格納
 	activeActorData_[type].emplace_back(active);

	// アクティブ状態になったものを返す
	return active;

}

void ActorManager::DeactiveData(const std::shared_ptr<Actor>& actor)
{

	ActorType type = actor->GetActorType();

	// activeActorData_の中にすでに同じ型が生成されているかチェックする
	auto actorElem = activeActorData_.find(type);

	// 生成されていない場合は、NULLを返す
	if (actorElem == activeActorData_.end()) return;

	// activeActorData_の先頭部分を削除してdeactiveActorData_に格納する

	// activeActorData_に格納
	deactiveActorData_[type].emplace_back(actor);

}