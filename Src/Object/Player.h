#pragma once
#include <memory>
#include <vector>
#include "../Object/Actor.h"

class ActorManager;

class Player : public Actor
{
public:

	// プレイヤー画像の総枚数
	static constexpr int PLAYER_IMAGE_NUM = 4;

	// プレイヤー画像の横の総枚数
	static constexpr int PLAYER_IMAGE_X_NUM = 4;

	// プレイヤーの画像サイズ
	static constexpr int PLAYER_IMAGE_SIZE = 32;

	//	ジャンプキー入力を受け付けるフレーム数
	static constexpr int INPUT_JUMP_FRAME = 6;

	// 最大ジャンプ力
	static constexpr float MAX_JUMP_POW = 50.0f;

	Player();

	~Player() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	// プレイヤー画像
	int* playerImg_;

	// ジャンプしているか
	bool isJump_;

	// ジャンプの入力時間
	float cntJumpInput_;

	// ジャンプキーの押下判定
	bool isPutJumpKey_;

	// ジャンプ力
	float jumpPow_;

	// 弾が打てるか
	bool isShot_;

	void Move() override;

	void Jump();

	void ProcessJump();

	void SetJumpPow(float pow);

	void CollisionFoot();

	void ShotAttack();

};

