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
	for (auto& data : actorData_)
	{
		// auto�ł͂Ȃ��A������^���͂��̌^���ŏ���
		// �O��const�����邱�ƂŁAActor�̔�������������̂��~�߂�
		// �S�o�C�g�ȏ゠����̂́u&�v�����邱�ƂŁA�S�o�C�g�ɂȂ�̂Őߖ�ł���
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Update();
		}
	}
}

void ActorManager::Draw()
{
	for (auto& data : actorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Draw();
		}
	}
}

void ActorManager::Release()
{
	for (auto& data : actorData_)
	{
		for (const std::shared_ptr<Actor>& actor : data.second)
		{
			actor->Release();
		}
	}
}

std::vector<std::shared_ptr<Actor>> ActorManager::GetActorData()
{
	for (auto& data : actorData_)
	{
		return data.second;
	}
}