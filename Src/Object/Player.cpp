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

	playerImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IDLE).handleIds_;
	actorType_ = ActorType::PLAYER;
	pos_ = { Application::SCREEN_SIZE_X / 2,0 };
	speed_ = 10.0f;
	animCnt_ = 0;

	// �W�����v���Ă��邩
	isJump_ = false;

	// ���ƏՓ˂��Ă��邩�ǂ���
	isHitFloor_ = false;

	// �W�����v�̓��͎���
	cntJumpInput_ = INPUT_JUMP_FRAME;

	// �W�����v��
	jumpPow_ = 0.0f;

	isCanShot_ = false;
	isDoingShot_ = false;

	coolTime_ = 0.0f;

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

	Actor::Init(pos);

}

void Player::Update()
{

	// �ړ�����
	Move();

	// �W�����v����
	ProcessJump();

	// �W�����v
	Jump();

	// �d��
	jumpPow_ = GravityManager::GetInstance().AddGravity(jumpPow_);

	// �����̓����蔻��
	CollisionFoot();

	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE) && isCanShot_ && coolTime_ <= 0.0f)
	{
		ShotAttack();
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

	coolTime_ -= SceneManager::GetInstance().GetDeltaTime();

}

void Player::Draw()
{

	animIdx_ = (animCnt_ / 10) % PLAYER_IMAGE_NUM;

	// �v���C���[�̕`��
	if (dir_.x == (float)DIR::RIGHT)
	{
		DrawRotaGraph(pos_.x, pos_.y, 2.0, 0.0, playerImg_[animIdx_], true);
	}
	else
	{
		DrawRotaGraph(pos_.x, pos_.y, 2.0, 0.0, playerImg_[animIdx_], true, true);
	}

	animCnt_++;

}

void Player::Release()
{
}

void Player::Move()
{

	if (InputManager::GetInstance().IsNew(KEY_INPUT_A))
	{
		dir_.x = (int)DIR::LEFT;
		speed_ = 10.0f;
		movePow_ = dir_.x * speed_;
		pos_.x += movePow_;
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_D))
	{
		dir_.x = (int)DIR::RIGHT;
		speed_ = 10.0f;
		movePow_ = dir_.x * speed_;
		pos_.x += movePow_;
	}

	movePow_ = 0.0f;
}

void Player::Jump()
{
	pos_.y += jumpPow_;
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

void Player::CollisionFoot(void)
{

	if (pos_.y >= Application::SCREEN_SIZE_Y / 2)
	{
		isHitFloor_ = true;
		pos_.y = Application::SCREEN_SIZE_Y / 2;
	}
	else
	{
		isHitFloor_ = false;
	}

	// �ڒn����(�����̏Փ˔���)
	if (isHitFloor_)
	{

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
		// �ڒn���Ă��Ȃ��̂ŁA�W�����v����ɂ���
		isJump_ = true;
	}

}

void Player::ShotAttack()
{

	// ���N���X����g�������^�փL���X�g����
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULL�`�F�b�N
	if (!gameScene) return;

	// �A�N�^�[�}�l�[�W���[���擾
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

  	std::shared_ptr<Actor> shot = actorManager->ActiveData(ActorType::SHOT,{pos_.x,pos_.y + 32.0f});

  	shot->Update();

}

void Player::CollisionStage()
{

}