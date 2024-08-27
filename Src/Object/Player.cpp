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

	playerImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IDLE).handleIds_;
	actorType_ = ActorType::PLAYER;
	pos_ = { Application::SCREEN_SIZE_X / 2,0 };
	speed_ = 10.0f;
	animCnt_ = 0;

	// ジャンプしているか
	isJump_ = false;

	// 床と衝突しているかどうか
	isHitFloor_ = false;

	// ジャンプの入力時間
	cntJumpInput_ = INPUT_JUMP_FRAME;

	// ジャンプ力
	jumpPow_ = 0.0f;

	isCanShot_ = false;
	isDoingShot_ = false;

	coolTime_ = 0.0f;

	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// コリジョンマネージャーを取得
	std::shared_ptr<CollisionManager> collsionManager = gameScene->GetCollisionManager();

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	// アクティブなアクターだけを衝突判定の管理クラスに登録
	collsionManager->Register(GetThis());

	Actor::Init(pos);

}

void Player::Update()
{

	// 移動処理
	Move();

	// ジャンプ操作
	ProcessJump();

	// ジャンプ
	Jump();

	// 重力
	jumpPow_ = GravityManager::GetInstance().AddGravity(jumpPow_);

	// 足元の当たり判定
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

	// プレイヤーの描画
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

	// 接地判定(足元の衝突判定)
	if (isHitFloor_)
	{

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
		// 接地していないので、ジャンプ判定にする
		isJump_ = true;
	}

}

void Player::ShotAttack()
{

	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

  	std::shared_ptr<Actor> shot = actorManager->ActiveData(ActorType::SHOT,{pos_.x,pos_.y + 32.0f});

  	shot->Update();

}

void Player::CollisionStage()
{

}