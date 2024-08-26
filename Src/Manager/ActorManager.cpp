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

	// activeActorData_�ɔ�A�N�e�B�u��Ԃ̂��̂������
	// deactiveActorData_�Ɋi�[����
	int num = 0;
	for (auto& data : activeActorData_)
	{
		num = 0;
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			if (actor && !actor->GetIsActive())
			{
				// ��A�N�e�B�u�ɂȂ������̂��i�[
				DeactiveData(actor);

				// ��A�N�e�B�u�ɂȂ������̂��폜
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

	// ���g��0�̏ꍇ�́ANULL��Ԃ�
	if (deactiveActorData_[type].size() == 0)return nullptr;

	// deactiveActorData_�̒��ɂ��łɓ����^����������Ă��邩�`�F�b�N����
	auto deactorElem = deactiveActorData_.find(type);

	// ��������Ă��Ȃ��ꍇ�́ANULL��Ԃ�
	if (deactorElem == deactiveActorData_.end()) return nullptr;

	// deactiveActorData_�̐擪�������폜����activeActorData_�Ɋi�[����
	
	// deactiveActorData_�̐擪����
	std::shared_ptr<Actor> active = deactiveActorData_[type].front();

	// deactiveActorData_�̐擪�������폜
	deactiveActorData_[type].erase(deactiveActorData_[type].begin());

	// �A�N�e�B�u��Ԃɂ���
	active->Init(pos);
	active->SetIsActive(true);

	// activeActorData_�Ɋi�[
 	activeActorData_[type].emplace_back(active);

	// �A�N�e�B�u��ԂɂȂ������̂�Ԃ�
	return active;

}

void ActorManager::DeactiveData(const std::shared_ptr<Actor>& actor)
{

	ActorType type = actor->GetActorType();

	// activeActorData_�̒��ɂ��łɓ����^����������Ă��邩�`�F�b�N����
	auto actorElem = activeActorData_.find(type);

	// ��������Ă��Ȃ��ꍇ�́ANULL��Ԃ�
	if (actorElem == activeActorData_.end()) return;

	// activeActorData_�̐擪�������폜����deactiveActorData_�Ɋi�[����

	// activeActorData_�Ɋi�[
	deactiveActorData_[type].emplace_back(actor);

}