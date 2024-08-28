#pragma once
#include "../Object/Actor.h"

class Shot : public Actor
{

public:

	// 弾画像の総枚数
	static constexpr int SHOT_IMAGE_NUM = 5;

	// 弾画像の横の総枚数
	static constexpr int SHOT_IMAGE_X_NUM = 5;

	// 弾画像の横サイズ
	static constexpr int SHOT_IMAGE_X_SIZE = 32;

	// 弾画像の縦サイズ
	static constexpr int SHOT_IMAGE_Y_SIZE = 64;

	// 生存時間
	static constexpr float ALIVE_TIME = 5.0f;

	// 弾の速度
	static constexpr float SHOT_SPEED = 5.0f;

	Shot();
	~Shot();

	void Init(const Vector2F& pos) override;
	void Update(const float deltaTime) override;
	void Draw() override;
	void Release() override;

private:

	// プレイヤー画像
	int* shotImg_;

	// 生存時間のカウンタ
	float aliveCnt_;

	void Move(const float deltaTime) override;

};

