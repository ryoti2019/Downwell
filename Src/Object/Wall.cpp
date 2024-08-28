#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/SceneManager.h"
#include "../Scene/GameScene.h"
#include "Wall.h"

void Wall::Init(const Vector2F& pos)
{	

	Actor::Init(pos);
	size_ = { WALL_IMAGE_SIZE,WALL_IMAGE_SIZE };
	animIdx_ = 3;

	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::MAP_CHIP).handleIds_;
	actorType_ = ActorType::WALL;


	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// コリジョンマネージャーを取得
	std::shared_ptr<CollisionManager> collsionManager = gameScene->GetCollisionManager();

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	// アクティブなアクターだけを衝突判定の管理クラスに登録
	collsionManager->Register(GetThis());

}

void Wall::Update(const float deltaTime)
{
}

void Wall::Release()
{
}