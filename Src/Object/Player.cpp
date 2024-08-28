#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/ActorManager.h"
#include "../Manager/CollisionManager.h"
#include "../Application.h"
#include "../Scene/GameScene.h"
#include "Player.h"
#include "Shot.h"

Player::Player()
{
	// ���N���X����g�������^�փL���X�g����
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULL�`�F�b�N
	if (!gameScene) return;

	// �A�N�^�[�}�l�[�W���[���擾
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	// �e�𐶐�
	for (int i = 0; i < 50; i++)
	{
		actorManager->CreateActor<Shot>();
	}
}

Player::~Player()
{
}

void Player::Init(const Vector2F& pos)
{

	Actor::Init(pos);

#pragma region �A�j���[�V����

	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IDLE).handleIds_;
	imgExtRate_ = 2.0;
	turnXFlag_ = true;

#pragma endregion

#pragma region �I�u�W�F�N�g�̏�����

	movedPos_ = pos_;
	size_ = { PLAYER_IMAGE_SIZE * static_cast<float>(imgExtRate_),PLAYER_IMAGE_SIZE * static_cast<float>(imgExtRate_) };
	speed_ = 50.0f;
	hp_ = 10;
	actorType_ = ActorType::PLAYER;
	isJump_ = false;
	cntJumpInput_ = INPUT_JUMP_FRAME;
	isPutJumpKey_;
	jumpPow_ = 0.0f;
	isCanShot_ = false;
	isDoingShot_ = false;
	coolTime_ = 0.0f;
	isHitLR_ = false;

#pragma endregion

	// ���N���X����g�������^�փL���X�g����
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULL�`�F�b�N
	if (!gameScene) return;

	// �R���W�����}�l�[�W���[���擾
	std::shared_ptr<CollisionManager> collsionManager = gameScene->GetCollisionManager();

	// �A�N�^�[�}�l�[�W���[���擾
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	// �Փ˔���̊Ǘ��N���X�ɓo�^
	collsionManager->Register(GetThis());

}

void Player::Update(const float deltaTime)
{

	// �����̓����蔻��
	CollisionStage();

	// �ړ�����
	Move(deltaTime);

	// �W�����v����
	ProcessJump();

	// �W�����v
	Jump();

	// �d��
	jumpPow_ = GravityManager::GetInstance().AddGravity(jumpPow_);

	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE) && isCanShot_ && coolTime_ <= 0.0f)
	{
		ShotAttack(deltaTime);
		coolTime_ = SHOT_COOL_TIME;
		isDoingShot_ = true;
	}
	else if(!isCanShot_)
	{
		isDoingShot_ = false;
	}

	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE) && isDoingShot_ && jumpPow_ >= 0.0f)
	{
		jumpPow_ = 0.0f;
	}

	coolTime_ -= deltaTime;

	animIdx_ = (animCnt_ / 10) % PLAYER_IMAGE_NUM;
	animCnt_++;

}

void Player::Release()
{
}

void Player::Move(const float deltaTime)
{

	if (InputManager::GetInstance().IsNew(KEY_INPUT_A))
	{
		dir_.x = (int)DIR::LEFT;
		movePow_ = dir_.x * speed_ * deltaTime;
		movedPos_.x += movePow_;
		turnXFlag_ = true;
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_D))
	{
		dir_.x = (int)DIR::RIGHT;
		movePow_ = dir_.x * speed_ * deltaTime;
		movedPos_.x += movePow_;
		turnXFlag_ = false;
	}

	movePow_ = 0.0f;
}

void Player::Jump()
{
	movedPos_.y += jumpPow_;
}

void Player::ProcessJump()
{

	// �n�ʂɒ��n���Ă���Ƃ��W�����v�ł���
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) && !isJump_)
	{
 		isJump_ = true;
		isPutJumpKey_ = true;
	}

	// ���͎��Ԃɉ����ăW�����v�ʂ�ύX����
	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE) &&
		cntJumpInput_ < INPUT_JUMP_FRAME && isPutJumpKey_)
	{

		cntJumpInput_++;

		// �W�����v�͂ɕ��z���Z
 		float pow = jumpPow_ - (MAX_JUMP_POW / static_cast<float>(INPUT_JUMP_FRAME));
   		SetJumpPow(pow);

	}

	// 2�i�W�����v���֎~����
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_SPACE))
	{
		// �W�����v�{�^���𗣂��ꂽ��
		cntJumpInput_ = INPUT_JUMP_FRAME;
		isCanShot_ = true;
	}

}

void Player::SetJumpPow(float pow)
{

	// �W�����v�͂�ݒ�
	jumpPow_ = pow;

	// �d�͂�������߂���̂�h��
	if (jumpPow_ > MAX_JUMP_POW)
	{
		jumpPow_ = MAX_JUMP_POW;
	}

}

void Player::ShotAttack(const float deltaTime)
{

	// ���N���X����g�������^�փL���X�g����
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULL�`�F�b�N
	if (!gameScene) return;

	// �A�N�^�[�}�l�[�W���[���擾
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

  	std::shared_ptr<Actor> shot = actorManager->ActiveData(ActorType::SHOT,{pos_.x,pos_.y + 32.0f});

  	shot->Update(deltaTime);

}

void Player::CollisionStage()
{

	// �ڒn����(�����̏Փ˔���)
	if (isHit_)
	{

		movedPos_.y = pos_.y;

		// �n�ʂɂ����̂ŃW�����v�����Z�b�g
		isJump_ = false;
		SetJumpPow(0.0f);

		// �ڒn������W�����v�J�E���^�����ɖ߂�
		cntJumpInput_ = 0;

		// �W�����v�L�[�̉�������
		isPutJumpKey_ = false;

		// �e�͑łĂȂ�
		isCanShot_ = false;

	}
	// �󒆔���
	else
	{

		pos_.y = movedPos_.y;

		// �ڒn���Ă��Ȃ��̂ŁA�W�����v����ɂ���
		isJump_ = true;

	}

	if (isHitLR_)
	{

		movedPos_.x = pos_.x;
	}
	else
	{
		pos_.x = movedPos_.x;
	}

}
