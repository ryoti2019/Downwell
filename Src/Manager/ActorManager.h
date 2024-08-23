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

	std::shared_ptr<Actor> ActivateData(const ActorType type);

private:

	// ���ׂẴA�N�^�[���܂Ƃ߂��f�[�^
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> activeActorData_;

	// ���ׂẴA�N�^�[���܂Ƃ߂��f�[�^
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> deactiveActorData_;

	//// �v���C���[
	//std::shared_ptr<Player> player_;

};

// �e���v���[�g��Actor�̌p����̌^�ɒu�������邱�Ƃ��ł���
template<typename T>
inline void ActorManager::CreateActor()
{

	// ���̒���Actor�����̎��̂��܂Ƃ߂č��

	std::shared_ptr<Actor> actor = std::make_shared<T>();

	// �|�C���^���g���Ƃ��̓N���b�V�����Ȃ��悤��NULL�`�F�b�N���s���悤�ɂ���
	if (!actor) return;

	actor->Init();

	// actorData�̒��ɂ��łɓ����^����������Ă��邩�`�F�b�N����
	auto actorElem = deactiveActorData_.find(actor->GetActorType());

	// ��������Ă��Ȃ��ꍇ�́A�V����vector�z��̔�����肻�̒��ɗv�f�����Ă���
	if (actorElem == deactiveActorData_.end())
	{
		std::vector<std::shared_ptr<Actor>> data;
		data.emplace_back(actor);
		deactiveActorData_.emplace(actor->GetActorType(), data);
	}
	// ��������Ă���ꍇ�͂��łɂ��锠�̒��ɗv�f�����Ă���
	else
	{
		actorElem->second.emplace_back(actor);
	}

}