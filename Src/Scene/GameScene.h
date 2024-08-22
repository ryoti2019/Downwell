#pragma once
#include <memory>
#include "../Scene/SceneBase.h"
class ActorManager;
//class Player;

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

private:

	// アクターの管理クラス
	std::shared_ptr<ActorManager> actorManager_;

};