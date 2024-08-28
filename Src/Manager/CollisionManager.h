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
	void Update();

	void Register(const std::shared_ptr<Actor>& actor);

	const std::unordered_map<ActorType, std::vector<float>> sizePos =
	{
		{ActorType::PLAYER,{0,32,0,32}},
		{ActorType::WALL,{0,32,0,32}}
	};

private:

	// すべてのアクターの衝突判定をまとめたデータ
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> collisionActorData_;

	bool isHitLR_;

	bool IsCollisionRectCenter(const Vector2F& centerPos1, const Vector2F& size1,
							   const Vector2F& centerPos2, const Vector2F& size2);

	bool IsCollisionRect(const Vector2F& stPos1, const Vector2F& edPos1,
						 const Vector2F& stPos2, const Vector2F& edPos2);

};

