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


	// ���N���X����g�������^�փL���X�g����
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULL�`�F�b�N
	if (!gameScene) return;

	// �R���W�����}�l�[�W���[���擾
	std::shared_ptr<CollisionManager> collsionManager = gameScene->GetCollisionManager();

	// �A�N�^�[�}�l�[�W���[���擾
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	// �A�N�e�B�u�ȃA�N�^�[�������Փ˔���̊Ǘ��N���X�ɓo�^
	collsionManager->Register(GetThis());

}

void Wall::Update(const float deltaTime)
{
}

void Wall::Release()
{
}