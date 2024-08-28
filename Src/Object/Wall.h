#pragma once
#include "../Object/Actor.h"

class Wall : public Actor
{

public:

	// マップ画像の総枚数
	static constexpr int WALL_IMAGE_NUM = 3;

	// マップ画像の横の総枚数
	static constexpr int WALL_IMAGE_X_NUM = 3;

	// マップ画像サイズ
	static constexpr int WALL_IMAGE_SIZE = 32;

	// マップの横サイズ
	static constexpr int MAP_MAX_X_SIZE = 14;

	// マップの縦サイズ
	static constexpr int MAP_MAX_Y_SIZE = 20;

	Wall() = default;
	~Wall() = default;

	void Init(const Vector2F& pos)override;
	void Update(const float deltaTime)override;
	void Release()override;

private:

};

