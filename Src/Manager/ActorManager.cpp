#include "ActorManager.h"
#include "../Object/Actor.h"

ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
}

void ActorManager::Init()
{
	actor_ = std::make_unique<Actor>();
	actor_->Init();
}

void ActorManager::Update()
{
	actor_->Update();
}

void ActorManager::Draw()
{
	actor_->Draw();
}

void ActorManager::Release()
{
	actor_->Release();
}