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
	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	// 弾を生成
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

#pragma region アニメーション

	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IDLE).handleIds_;
	imgExtRate_ = 2.0;
	turnXFlag_ = true;

#pragma endregion

#pragma region オブジェクトの初期化

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

	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// コリジョンマネージャーを取得
	std::shared_ptr<CollisionManager> collsionManager = gameScene->GetCollisionManager();

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	// 衝突判定の管理クラスに登録
	collsionManager->Register(GetThis());

}

void Player::Update(const float deltaTime)
{

	// 足元の当たり判定
	CollisionStage();

	// 移動処理
	Move(deltaTime);

	// ジャンプ操作
	ProcessJump();

	// ジャンプ
	Jump();

	// 重力
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

	// 地面に着地しているときジャンプできる
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) && !isJump_)
	{
 		isJump_ = true;
		isPutJumpKey_ = true;
	}

	// 入力時間に応じてジャンプ量を変更する
	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE) &&
		cntJumpInput_ < INPUT_JUMP_FRAME && isPutJumpKey_)
	{

		cntJumpInput_++;

		// ジャンプ力に分配加算
 		float pow = jumpPow_ - (MAX_JUMP_POW / static_cast<float>(INPUT_JUMP_FRAME));
   		SetJumpPow(pow);

	}

	// 2段ジャンプを禁止する
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_SPACE))
	{
		// ジャンプボタンを離された時
		cntJumpInput_ = INPUT_JUMP_FRAME;
		isCanShot_ = true;
	}

}

void Player::SetJumpPow(float pow)
{

	// ジャンプ力を設定
	jumpPow_ = pow;

	// 重力がかかり過ぎるのを防ぐ
	if (jumpPow_ > MAX_JUMP_POW)
	{
		jumpPow_ = MAX_JUMP_POW;
	}

}

void Player::ShotAttack(const float deltaTime)
{

	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

  	std::shared_ptr<Actor> shot = actorManager->ActiveData(ActorType::SHOT,{pos_.x,pos_.y + 32.0f});

  	shot->Update(deltaTime);

}

void Player::CollisionStage()
{

	// 接地判定(足元の衝突判定)
	if (isHit_)
	{

		movedPos_.y = pos_.y;

		// 地面についたのでジャンプをリセット
		isJump_ = false;
		SetJumpPow(0.0f);

		// 接地したらジャンプカウンタを元に戻す
		cntJumpInput_ = 0;

		// ジャンプキーの押下判定
		isPutJumpKey_ = false;

		// 弾は打てない
		isCanShot_ = false;

	}
	// 空中判定
	else
	{

		pos_.y = movedPos_.y;

		// 接地していないので、ジャンプ判定にする
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
