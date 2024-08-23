#pragma once
#include "../Common/Vector2F.h"

enum class ActorType {
	PLAYER,
	SHOT,
	ENEMY,
	STAGE
};

enum class DIR {
	UP = 1,
	DOWN = -1,
	LEFT = 1,
	RIGHT = -1
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

	bool GetIsActive() const { return isActive_; }

	void SetIsActive(bool isActive) { isActive_ = isActive; }

	const Vector2F& GetPos() const { return pos_; }

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

	// 移動量
	float movePow_;

	// HP
	int hp_;

	// オブジェクトと衝突しているか
	bool isHitObject_;

	// 床と衝突しているか
	bool isHitFloor_;

	// アクターの種類
	ActorType actorType_;

	// アクティブ状態かどうか
	bool isActive_;

#pragma endregion

#pragma region アニメーション

	// アニメーションカウンタ
	int animCnt_;

	// アニメーション番号
	int animIdx_;

#pragma endregion

	// 移動
	virtual void Move(void);

	// 衝突判定
	virtual void Collision(void);

	// 生きているかどうか
	bool IsAlive(void);

};