#include "CollisionManager.h"
#include "../Common/Vector2F.h"

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{

	CollisionCheck();

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

void CollisionManager::CollisionCheck()
{

	for (const collisionChannnelInfo& info : collisionChannelList_)
	{
		const auto& data1 = collisionActorData_.find(info.type1);
		const auto& data2 = collisionActorData_.find(info.type2);
		if (data1 == collisionActorData_.end())continue;
		if (data2 == collisionActorData_.end())continue;

		for (const std::shared_ptr<Actor>& actor1 : data1->second)
		{
			for (const std::shared_ptr<Actor>& actor2 : data2->second)
			{
				if (!actor1)return;
				if (!actor2)return;

				const Vector2F minPos1 = actor1->GetPos() - (actor1->GetSize() / 2);
				const Vector2F maxPos1 = actor1->GetPos() + (actor1->GetSize() / 2);
				const Vector2F minPos2 = actor2->GetPos() - (actor2->GetSize() / 2);
				const Vector2F maxPos2 = actor2->GetPos() + (actor2->GetSize() / 2);
				if (IsCollisionRectCenter(minPos1, maxPos1, minPos2, maxPos2))
				{
					const Vector2F centerPos1 = maxPos1 - (actor1->GetSize() / 2);
					const Vector2F centerPos2 = maxPos2 - (actor2->GetSize() / 2);
					Vector2F vec = centerPos1 - centerPos2;
					vec.Normalize();

					Vector2F subPos;
					
					if (vec.y >= 0.0f && info.isCorrectPos)
					{
						subPos.y = centerPos2.y - centerPos1.y;
						actor1->AddPos(subPos);
					}
					actor1->SetColPos(centerPos2);
					actor1->SetColSize(actor2->GetSize());
					actor1->OnCollision();
					actor2->OnCollision();

				}
			}
		}
	}

}

bool CollisionManager::IsCollisionRectCenter(const Vector2F& minPos1, const Vector2F& maxPos1, const Vector2F& minPos2, const Vector2F& maxPos2)
{

	if (maxPos1.y < minPos2.y || minPos1.y > maxPos2.y ||
		maxPos1.x < minPos2.x || minPos1.x > maxPos2.x)
	{
		return false;
	}

	return true;

	//// �V�����Փ˔���
	//for (int i = 0; i < 4; i++)
	//{
	//	if ((centerPos1.x - size1.x / 2) <= (centerPos2.x + list[i].x) <= (centerPos1.x + size1.x / 2) && 
	//		(centerPos1.y - size1.y / 2) <= (centerPos2.y + list[i].x) <= (centerPos1.y + size1.y / 2))
	//	{
	//		return true;
	//	}
	//}

	//return false;

	//// ��`1(������W�A�E�����W)
	//Vector2F stPos1 = centerPos1;
	//Vector2F edPos1 = centerPos1;
	//Vector2F hSize1 = { size1.x / 2, size1.y / 2 };

	//stPos1.x -= hSize1.x;
	//stPos1.y -= hSize1.y;
	//edPos1.x += hSize1.x;
	//edPos1.y += hSize1.y;

	//// ��`�Q(������W�A�E�����W)
	//Vector2F stPos2 = centerPos2;
	//Vector2F edPos2 = centerPos2;
	//Vector2F hSize2 = { size2.x / 2, size2.y / 2 };

	//stPos2.x -= hSize2.x;
	//stPos2.y -= hSize2.y;
	//edPos2.x += hSize2.x;
	//edPos2.y += hSize2.y;

	//// ��`���m�̏Փ˔���
	//// ��`�P�̍������A��`�Q�̉E���傫��
	//// ��`�Q�̍������A��`�P�̉E���傫��
	//if (IsCollisionRect(stPos1, edPos1, stPos2, edPos2))
	//{
	//	return true;
	//}
	//return false;

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

Vector2F CollisionManager::CollisionDir(Vector2F& centerPos1, Vector2F& centerPos2)
{
	return centerPos2 - centerPos1;
}