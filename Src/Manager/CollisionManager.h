#pragma once
#include <unordered_map>
#include <string>
#include "../Manager/ActorManager.h"
class Actor;

class CollisionManager
{

public:

	CollisionManager() = default;
	~CollisionManager() = default;

	void Init();

	void Register(const std::shared_ptr<Actor>& actor);

private:

	// すべてのアクターの衝突判定をまとめたデータ
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> collisionActorData_;

};

