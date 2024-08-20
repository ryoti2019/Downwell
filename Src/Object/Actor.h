#pragma once
#include "../Common/Vector2F.h"

class Actor
{
public:

	enum class DIR
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Actor(void);

	virtual ~Actor(void);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	virtual void GetHP(void);
	virtual void DecreaseHP(int hp);

protected:

#pragma region オブジェクトの座標や衝突判定

	// 座標
	Vector2F pos_;

	// 移動後座標
	Vector2F movedPos_;

	// 方向
	Vector2F dir_;

	// スピード
	float speed_;

	// HP
	int hp_;

	// オブジェクトと衝突しているか
	bool isHitObject_;

	// ステージと衝突しているか
	bool isHitStage_;

#pragma endregion

	// アニメーション

	// 移動
	virtual void Move(void);

	// 衝突判定
	virtual void Collision(void);

	// 生きているかどうか
	bool IsAlive(void);

};