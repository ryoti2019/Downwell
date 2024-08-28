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

	// collisionActorData_�̒��ɂ��łɓ����^����������Ă��邩�`�F�b�N����
	auto collisionElem = collisionActorData_.find(actor->GetActorType());

	// ��������Ă��Ȃ��ꍇ�́A�V����vector�z��̔�����肻�̒��ɗv�f�����Ă���
	if (collisionElem == collisionActorData_.end())
	{
		std::vector<std::shared_ptr<Actor>> data;
		data.emplace_back(actor);
		collisionActorData_.emplace(actor->GetActorType(), data);
	}
	// ��������Ă���ꍇ�͂��łɂ��锠�̒��ɗv�f�����Ă���
	else
	{
		collisionElem->second.emplace_back(actor);
	}

}

bool CollisionManager::IsCollisionRectCenter(const Vector2F& centerPos1, const Vector2F& size1, const Vector2F& centerPos2, const Vector2F& size2)
{

	// ��`1(������W�A�E�����W)
	Vector2F stPos1 = centerPos1;
	Vector2F edPos1 = centerPos1;
	Vector2F hSize1 = { size1.x / 2, size1.y / 2 };

	stPos1.x -= hSize1.x;
	stPos1.y -= hSize1.y;
	edPos1.x += hSize1.x;
	edPos1.y += hSize1.y;

	// ��`�Q(������W�A�E�����W)
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

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (IsCollisionRect(stPos1, edPos1, stPos2, edPos2))
	{
		return true;
	}
	return false;

}

bool CollisionManager::IsCollisionRect(const Vector2F& stPos1, const Vector2F& edPos1, const Vector2F& stPos2, const Vector2F& edPos2)
{

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (stPos1.x < edPos2.x
		&& stPos2.x < edPos1.x
		&& stPos1.y < edPos2.y
		&& stPos2.y < edPos1.y)
	{
		return true;
	}
	return false;

}