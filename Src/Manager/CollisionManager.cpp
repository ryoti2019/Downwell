#include "CollisionManager.h"

void CollisionManager::Init()
{
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