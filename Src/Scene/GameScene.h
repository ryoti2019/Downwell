#pragma once
#include <memory>
#include <vector>
#include "../Scene/SceneBase.h"
class ActorManager;
class Stage;

class GameScene : public SceneBase
{

public:

	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	std::shared_ptr<ActorManager> GetActorManager() const {return actorManager_;}

private:

	// アクターの管理クラス
	std::shared_ptr<ActorManager> actorManager_;

	// ステージ
	std::vector<std::unique_ptr<Stage>> stage_;

};