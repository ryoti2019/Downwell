#pragma once
#include <memory>
#include <vector>
#include "../Scene/SceneBase.h"
class ActorManager;
class Stage;

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

	std::shared_ptr<ActorManager> GetActorManager() const {return actorManager_;}

private:

	// �A�N�^�[�̊Ǘ��N���X
	std::shared_ptr<ActorManager> actorManager_;

	// �X�e�[�W
	std::vector<std::unique_ptr<Stage>> stage_;

};