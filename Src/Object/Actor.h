#pragma once
#include "../Common/Vector2F.h"

enum class ActorType {
	PLAYER,
	ENEMY,
	STAGE
};

class Actor
{
public:

	Actor(void);

	virtual ~Actor(void);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	int GetHP() const { return hp_; }

	void DecreaseHP(int hp);

	ActorType GetActorType() const { return actorType_; }

protected:

#pragma region オブジェクトの情報

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

	// アクターの種類
	ActorType actorType_;

#pragma endregion

#pragma region アニメーション

	// アニメーションカウンタ
	int animCnt_;

#pragma endregion

	// 移動
	virtual void Move(void);

	// 衝突判定
	virtual void Collision(void);

	// 生きているかどうか
	bool IsAlive(void);

};