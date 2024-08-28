#include "CollisionManager.h"
#include "../Common/Vector2F.h"

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{

	const auto& playerData = collisionActorData_.find(ActorType::PLAYER);
	const auto& wallData = collisionActorData_.find(ActorType::WALL);
	if (playerData == collisionActorData_.end())return;
	if (wallData == collisionActorData_.end())return;

	for (const std::shared_ptr<Actor>& player : playerData->second)
	{
		for (const std::shared_ptr<Actor>& wall : wallData->second)
		{
			Vector2F pos1 = player->GetPos();
			Vector2F pos2 = wall->GetPos();
			Vector2F size1 = player->GetSize();
			Vector2F size2 = wall->GetSize();
			if (IsCollisionRectCenter(pos1,size1,pos2,size2))
			{
				player->SetIsHit(true);
				player->SetPos(player->GetPos());
				player->SetIsHit(isHitLR_);
				break;
			}
			else
			{
				player->SetIsHit(false);
			}
		}
	}

	isHitLR_ = false;

}

void CollisionManager::Register(const std::shared_ptr<Actor>& actor)
{

	// collisionActorData_の中にすでに同じ型が生成されているかチェックする
	auto collisionElem = collisionActorData_.find(actor->GetActorType());

	// 生成されていない場合は、新しくvector配列の箱を作りその中に要素を入れていく
	if (collisionElem == collisionActorData_.end())
	{
		std::vector<std::shared_ptr<Actor>> data;
		data.emplace_back(actor);
		collisionActorData_.emplace(actor->GetActorType(), data);
	}
	// 生成されている場合はすでにある箱の中に要素を入れていく
	else
	{
		collisionElem->second.emplace_back(actor);
	}

}

bool CollisionManager::IsCollisionRectCenter(const Vector2F& centerPos1, const Vector2F& size1, const Vector2F& centerPos2, const Vector2F& size2)
{

	// 矩形1(左上座標、右下座標)
	Vector2F stPos1 = centerPos1;
	Vector2F edPos1 = centerPos1;
	Vector2F hSize1 = { size1.x / 2, size1.y / 2 };

	stPos1.x -= hSize1.x;
	stPos1.y -= hSize1.y;
	edPos1.x += hSize1.x;
	edPos1.y += hSize1.y;

	// 矩形２(左上座標、右下座標)
	Vector2F stPos2 = centerPos2;
	Vector2F edPos2 = centerPos2;
	Vector2F hSize2 = { size2.x / 2, size2.y / 2 };

	stPos2.x -= hSize2.x;
	stPos2.y -= hSize2.y;
	edPos2.x += hSize2.x;
	edPos2.y += hSize2.y;

	if(stPos1.x < edPos2.x && stPos2.x < edPos1.x)
	{
		isHitLR_ = true;
	}

	// 矩形同士の衝突判定
	// 矩形１の左よりも、矩形２の右が大きい
	// 矩形２の左よりも、矩形１の右が大きい
	if (IsCollisionRect(stPos1, edPos1, stPos2, edPos2))
	{
		return true;
	}
	return false;

}

bool CollisionManager::IsCollisionRect(const Vector2F& stPos1, const Vector2F& edPos1, const Vector2F& stPos2, const Vector2F& edPos2)
{

	// 矩形同士の衝突判定
	// 矩形１の左よりも、矩形２の右が大きい
	// 矩形２の左よりも、矩形１の右が大きい
	if (stPos1.x < edPos2.x
		&& stPos2.x < edPos1.x
		&& stPos1.y < edPos2.y
		&& stPos2.y < edPos1.y)
	{
		return true;
	}
	return false;

}