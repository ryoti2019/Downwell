#pragma once
#include <memory>
#include "../Scene/SceneBase.h"
class ActorManager;
//class Player;

class GameScene : public SceneBase
{

public:

	// �R���X�g���N�^
	GameScene();

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// �A�N�^�[�̊Ǘ��N���X
	std::shared_ptr<ActorManager> actorManager_;

};