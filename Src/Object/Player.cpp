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

	size_ = {PLAYER_COLLISION_X_SIZE * static_cast<float>(imgExtRate_),PLAYER_IMAGE_SIZE * static_cast<float>(imgExtRate_) };
	speed_ = 100.0f;
	hp_ = 10;
	jumpPow_ = 0.0f;
	actorType_ = ActorType::PLAYER;
	isJump_ = false;
	cntJumpInput_ = INPUT_JUMP_FRAME;
	isPutJumpKey_;
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

	//ProcessJump();

	//Jump();

	//jumpPow_ = GravityManager::GetInstance().AddGravity(jumpPow_);

	if (InputManager::GetInstance().IsNew(KEY_INPUT_Q) && isCanShot_ && coolTime_ <= 0.0f)
	{
		ShotAttack(deltaTime);
		coolTime_ = SHOT_COOL_TIME;
		isDoingShot_ = true;
	}
	else if(!isCanShot_)
	{
		isDoingShot_ = false;
	}

	coolTime_ -= deltaTime;

	animIdx_ = (animCnt_ / 10) % PLAYER_IMAGE_NUM;
	animCnt_++;

}

void Player::OnCollision()
{
	isHitFoot_ = true;
}

void Player::Release()
{
}

void Player::Move(const float deltaTime)
{

	Vector2F resultPos = GetPos();
	Vector2F movePow = { 0.0f,0.0f };

	// ���ړ�
	if (InputManager::GetInstance().IsNew(KEY_INPUT_A))
	{
		movePow = Vector2F::vectorLeft * (speed_ * deltaTime);
		resultPos += movePow;
		turnXFlag_ = true;
	}
	// �E�ړ�
	if (InputManager::GetInstance().IsNew(KEY_INPUT_D))
	{
		movePow = Vector2F::vectorRight * (speed_ * deltaTime);
		resultPos += movePow;
		turnXFlag_ = false;
	}

	if (!isHitFoot_)
	{
		jumpPow_ = GravityManager::GetInstance().AddGravity(jumpPow_);
	}

	// �n�ʂɒ��n���Ă���Ƃ��W�����v�ł���
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_Q) && !isJump_)
	{
		isJump_ = true;
		isPutJumpKey_ = true;
		isHitFoot_ = false;
	}

	// ���͎��Ԃɉ����ăW�����v�ʂ�ύX����
	if (InputManager::GetInstance().IsNew(KEY_INPUT_Q) &&
		cntJumpInput_ < INPUT_JUMP_FRAME && isPutJumpKey_)
	{

		cntJumpInput_++;

		// �W�����v�͂ɕ��z���Z
		float pow = jumpPow_ - (MAX_JUMP_POW / static_cast<float>(INPUT_JUMP_FRAME));

		SetJumpPow(pow);

	}

	// 2�i�W�����v���֎~����
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_Q))
	{
		// �W�����v�{�^���𗣂��ꂽ��
		cntJumpInput_ = INPUT_JUMP_FRAME;
		isCanShot_ = true;
	}

	if (InputManager::GetInstance().IsNew(KEY_INPUT_Q) && isDoingShot_ && jumpPow_ >= 0.0f)
	{
		SetJumpPow(0.0f);
	}

	resultPos.y += jumpPow_;

	SetPos(resultPos);

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

  	std::shared_ptr<Actor> shot = actorManager->ActiveData(ActorType::SHOT,{GetPos().x,GetPos().y + 32.0f});

  	shot->Update(deltaTime);

}

void Player::CollisionStage()
{

	//Vector2F playerPos = GetPos();
	//Vector2F playerSize = GetSize();
	//Vector2F colPos = GetColPos();
	//Vector2F colSize = GetColSize();
	//float playerLeftPosX = playerPos.x - playerSize.x / 2;
	//float playerRightPosX = playerPos.x + playerSize.x / 2;
	//float colLeftPosX = colPos.x - colSize.x / 2;
	//float colRightPosX = colPos.x + colSize.x / 2;
	//Vector2F vec = colPos - playerPos;
	//vec.Normalize();
	//if (!isHitFoot_ || (playerLeftPosX < colRightPosX || playerRightPosX > colLeftPosX))
	//{
	//	jumpPow_ = GravityManager::GetInstance().AddGravity(jumpPow_);
	//	SetJumpPow(jumpPow_);
	//	//isHitFoot_ = false;
	//}

	// �ڒn����(�����̏Փ˔���)
	if (isHitFoot_)
	{

		// �n�ʂɂ����̂ŃW�����v�����Z�b�g
		isJump_ = false;

		//SetJumpPow(0.0f);

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

void Player::SetJumpPow(float pow)
{
	// �W�����v�͂�ݒ�
	jumpPow_ = pow;

	// �d�͂������肷����̂�h��
	if (jumpPow_ > MAX_JUMP_POW)
	{
		jumpPow_ = MAX_JUMP_POW;
	}
}
