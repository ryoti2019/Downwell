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

	ActorManager() = default;
	~ActorManager() = default;

	void Init();
	void Update();
	void Draw();
	void Release();
	
	// Actor�̔h���N���X�̎��̂̍쐬
	template <typename actor>
	void CreateActor();

	// �A�N�e�B�u�ɂȂ������̂��i�[
	std::shared_ptr<Actor> ActiveData(const ActorType type, const Vector2F& pos);

	// ��A�N�e�B�u�ɂȂ������̂��i�[
	void DeactiveData(const std::shared_ptr<Actor>& actor);

	const auto& const GetActiveActorData() { return activeActorData_; };

private:

	// ���ׂẴA�N�^�[���܂Ƃ߂��f�[�^
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> activeActorData_;

	// ���ׂẴA�N�^�[���܂Ƃ߂��f�[�^
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> deactiveActorData_;

};

// �e���v���[�g��Actor�̌p����̌^�ɒu�������邱�Ƃ��ł���
template<typename T>
inline void ActorManager::CreateActor()
{

	// ���̒���Actor�����̎��̂��܂Ƃ߂č��

	std::shared_ptr<Actor> actor = std::make_shared<T>();

	// �|�C���^���g���Ƃ��̓N���b�V�����Ȃ��悤��NULL�`�F�b�N���s���悤�ɂ���
	if (!actor) return;

	const Vector2F pos = { 0.0f,0.0f };
	actor->Init(pos);

	// deactiveActorData_�̒��ɂ��łɓ����^����������Ă��邩�`�F�b�N����
	auto deactorElem = deactiveActorData_.find(actor->GetActorType());

	// ��������Ă��Ȃ��ꍇ�́A�V����vector�z��̔�����肻�̒��ɗv�f�����Ă���
	if (deactorElem == deactiveActorData_.end())
	{
		std::vector<std::shared_ptr<Actor>> data;
		data.emplace_back(actor);
		deactiveActorData_.emplace(actor->GetActorType(), data);
	}
	// ��������Ă���ꍇ�͂��łɂ��锠�̒��ɗv�f�����Ă���
	else
	{
		deactorElem->second.emplace_back(actor);
	}

}