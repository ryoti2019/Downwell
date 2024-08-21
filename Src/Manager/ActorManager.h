#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "../Object/Actor.h"

class Actor;
class Player;
//class Enemy;
//class Stage;

enum class ActorType;

class ActorManager
{

public:

	ActorManager();
	~ActorManager();

	void Init();
	void Update();
	void Draw();
	void Release();
	
	template <typename actor>
	void CreateActor();

	std::vector<std::shared_ptr<Actor>> GetActorData();

private:

	// すべてのアクターをまとめたデータ
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> actorData_;

	//// プレイヤー
	//std::shared_ptr<Player> player_;

};

template<typename T>
inline void ActorManager::CreateActor()
{

	std::shared_ptr<Actor> actor = std::make_shared<T>();
	actor->Init();

	auto actorElem = actorData_.find(actor->GetActorType());
	if ( actorElem == actorData_.end())
	{
		std::vector<std::shared_ptr<Actor>> data;
		data.emplace_back(actor);
		actorData_.emplace(actor->GetActorType(), data);
	}
	else
	{
		actorElem->second.emplace_back(actor);
	}

}