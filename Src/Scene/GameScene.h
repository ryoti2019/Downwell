#pragma once
#include <memory>
#include <vector>
#include "../Scene/SceneBase.h"
class ActorManager;
class CollisionManager;
class Stage;

class GameScene : public SceneBase
{

public:

	// コンストラクタ
	GameScene() = default;

	// デストラクタ
	~GameScene() = default;

	void Init() override;
	void Update(const float deltaTime) override;
	void Draw() override;
	void Release() override;

	const std::shared_ptr<ActorManager>& GetActorManager() const { return actorManager_; }

	const std::shared_ptr<CollisionManager>& GetCollisionManager() const { return collisionManager_; }

	const std::shared_ptr<Stage>& GetStage() const { return stage_; }

private:

	// アクターの管理クラス
	std::shared_ptr<ActorManager> actorManager_;

	// 衝突判定の管理クラス
	std::shared_ptr<CollisionManager> collisionManager_;

	// ステージ
	std::shared_ptr<Stage> stage_;

};