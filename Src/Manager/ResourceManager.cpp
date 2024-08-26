#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "../Object/Player.h"
#include "../Object/Shot.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	Resource res;

	// プレイヤーの待機アニメーション
	res = Resource(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Player/Idle.png",
		Player::PLAYER_IMAGE_X_NUM,1,Player::PLAYER_IMAGE_SIZE,Player::PLAYER_IMAGE_SIZE);
	resourcesMap_.emplace(SRC::PLAYER_IDLE, res);

	// 弾のアニメーション
	res = Resource(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Player/Shot.png",
		Shot::SHOT_IMAGE_X_NUM,1,Shot::SHOT_IMAGE_X_SIZE,Shot::SHOT_IMAGE_Y_SIZE);
	resourcesMap_.emplace(SRC::SHOT, res);


}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second->Release();
		delete p.second;
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	resourcesMap_.clear();
	delete instance_;
}

Resource ResourceManager::Load(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return Resource();
	}
	Resource ret = *res;
	return *res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res->handleId_);
	res->duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource* ResourceManager::_Load(SRC src)
{
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return nullptr;
	}

	rPair->second.Load();

	// 念のためコピーコンストラクタ
	Resource* ret = new Resource(rPair->second);
	loadedMap_.emplace(src, ret);

	return ret;
}