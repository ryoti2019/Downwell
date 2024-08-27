#pragma once
#include <memory>
#include "../Common/Vector2F.h"

enum class ActorType {
	PLAYER,
	SHOT,
	ENEMY,
	WALL,
};

enum class DIR {
	UP = -1,
	DOWN = 1,
	LEFT = -1,
	RIGHT = 1
};

class Actor : public std::enable_shared_from_this<Actor>
{
public:

	Actor() = default;

	virtual ~Actor() = default;

	virtual void Init(const Vector2F& pos);
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	int GetHP() const { return hp_; }

	void DecreaseHP(int hp) { hp_ -= hp; };

	const ActorType GetActorType() const { return actorType_; }

	const bool GetIsActive() const { return isActive_; }

	void SetIsActive(bool isActive) { isActive_ = isActive; }

	const Vector2F& GetPos() const { return pos_; }

	void SetPos(Vector2F pos) { pos_ = pos; };

	// 生きているかどうか
	const bool GetIsAlive() const { return isAlive_; };

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

	// 生きているかどうか
	bool isAlive_;

	// 画像
	int* img_;

#pragma endregion

#pragma region アニメーション

	// アニメーションカウンタ
	int animCnt_;

	// アニメーション番号
	int animIdx_;

#pragma endregion

	// 移動
	virtual void Move();

	// 衝突判定
	virtual void Collision();

	const std::shared_ptr<Actor>& GetThis() { return shared_from_this(); }

private:

	// アクティブ状態かどうか
	bool isActive_;

};