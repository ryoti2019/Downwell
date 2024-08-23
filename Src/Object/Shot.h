#pragma once
#include "../Object/Actor.h"

class Shot : public Actor
{

public:

	// プレイヤー画像の総枚数
	static constexpr int PLAYER_IMAGE_NUM = 4;

	Shot();
	~Shot();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	// プレイヤー画像
	int* playerImg_;


	void Move() override;

};

