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

	// 左移動
	if (InputManager::GetInstance().IsNew(KEY_INPUT_A))
	{
		movePow = Vector2F::vectorLeft * (speed_ * deltaTime);
		resultPos += movePow;
		turnXFlag_ = true;
	}
	// 右移動
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

	// 地面に着地しているときジャンプできる
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_Q) && !isJump_)
	{
		isJump_ = true;
		isPutJumpKey_ = true;
		isHitFoot_ = false;
	}

	// 入力時間に応じてジャンプ量を変更する
	if (InputManager::GetInstance().IsNew(KEY_INPUT_Q) &&
		cntJumpInput_ < INPUT_JUMP_FRAME && isPutJumpKey_)
	{

		cntJumpInput_++;

		// ジャンプ力に分配加算
		float pow = jumpPow_ - (MAX_JUMP_POW / static_cast<float>(INPUT_JUMP_FRAME));

		SetJumpPow(pow);

	}

	// 2段ジャンプを禁止する
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_Q))
	{
		// ジャンプボタンを離された時
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

	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// アクターマネージャーを取得
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

	// 接地判定(足元の衝突判定)
	if (isHitFoot_)
	{

		// 地面についたのでジャンプをリセット
		isJump_ = false;

		//SetJumpPow(0.0f);

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

void Player::SetJumpPow(float pow)
{
	// ジャンプ力を設定
	jumpPow_ = pow;

	// 重力がかかりすぎるのを防ぐ
	if (jumpPow_ > MAX_JUMP_POW)
	{
		jumpPow_ = MAX_JUMP_POW;
	}
}
