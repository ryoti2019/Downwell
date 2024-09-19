#pragma once
#include <unordered_map>
#include <string>
#include "../Object/Actor.h"

class CollisionManager
{

private:

	struct collisionChannnelInfo
	{
		ActorType type1;
		ActorType type2;
		bool isCorrectPos;
	};

	const std::vector<collisionChannnelInfo> collisionChannelList_ =
	{
		{{ActorType::PLAYER,ActorType::ENEMY,false},
		{ActorType::PLAYER,ActorType::ENEMY2,false},
		{ActorType::PLAYER,ActorType::WALL,true},
		{ActorType::PLAYER,ActorType::BREAK_BLOCK,true},
		{ActorType::PLAYER,ActorType::SHOT,false},
		{ActorType::ENEMY,ActorType::WALL,true},
		{ActorType::ENEMY,ActorType::BREAK_BLOCK,true},
		{ActorType::ENEMY,ActorType::SHOT,false},
		{ActorType::ENEMY2,ActorType::WALL,true},
		{ActorType::ENEMY2,ActorType::BREAK_BLOCK,true},
		{ActorType::ENEMY2,ActorType::SHOT,false},
		{ActorType::WALL,ActorType::SHOT,false},
		{ActorType::BREAK_BLOCK,ActorType::SHOT,false}}
	};

public:

	CollisionManager() = default;
	~CollisionManager() = default;

	void Init();
	void Update();

	void Register(const std::shared_ptr<Actor>& actor);

private:

	// すべてのアクターの衝突判定をまとめたデータ
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> collisionActorData_;

	void CollisionCheck();

	bool IsCollisionRectCenter(const Vector2F& minPos1, const Vector2F& maxPos1,
		const Vector2F& minPos2, const Vector2F& maxPos2);

	bool IsCollisionRect(const Vector2F& stPos1, const Vector2F& edPos1,
						 const Vector2F& stPos2, const Vector2F& edPos2);

	Vector2F CollisionDir(Vector2F& centerPos1, Vector2F& centerPos2);

};

