#pragma once
#include <memory>
#include <vector>
#include "../Common/Vector2F.h"

enum class ActorType {
	NONE = -1,
	PLAYER,
	SHOT,
	ENEMY,
	ENEMY2,
	WALL,
	BREAK_BLOCK,
	SCAFFOLD,
	MAX
};

class Actor : public std::enable_shared_from_this<Actor>
{
public:

	Actor() = default;

	virtual ~Actor() = default;

	virtual void Init(const Vector2F& pos);
	virtual void Create(const Vector2F& pos);
	virtual void Update(const float deltaTime);
	virtual void OnCollision();
	virtual void Draw();
	virtual void DrawMap();
	virtual void Release();

	int GetHP() const { return hp_; }

	void DecreaseHP(int hp) { hp_ -= hp; };

	const ActorType GetActorType() const { return actorType_; }

	const bool GetIsActive() const { return isActive_; }

	void SetIsActive(const bool isActive) { isActive_ = isActive; }

	virtual const Vector2F& GetPos() const { return pos_; }

	const void SetPos(const Vector2F& pos) { pos_ = pos; };

	const void AddPos(const Vector2F& pos) { pos_ += pos; };

	const void SubPos(const Vector2F& pos) { pos_ -= pos; };

	const Vector2F& GetColPos() const { return colPos_; };

	const void SetColPos(const Vector2F& pos) { colPos_ = pos; };

	const Vector2F& GetColSize() const { return colSize_; };

	const void SetColSize(const Vector2F& size) { colSize_ = size; };

	// 生きているかどうか
	const bool GetIsAlive() const { return isAlive_; };

	const Vector2F& GetSize() const { return size_; };

	void SetIsHitFoot(const bool hit) { isHitFoot_ = hit; };

	void SetIsHitLR(const bool hit) { isHitLR_ = hit; };

	const std::vector<Vector2F>& GetCollisionPosList() const{ return collisionPosList_; };

protected:

#pragma region オブジェクトの情報

	// 画像サイズ
	Vector2F size_;

	// スピード
	float speed_;

	// HP
	int hp_;

	// 着地しているか
	bool isHitFoot_;

	// 右左の壁に当たっているか
	bool isHitLR_;

	// アクターの種類
	ActorType actorType_;

	// 生きているかどうか
	bool isAlive_;

	const std::vector<Vector2F> collisionPosList_ =
	{
		{-size_.x / 2,-size_.y / 2},{-size_.x / 2,-size_.y / 2},{-size_.x / 2,-size_.y / 2},{-size_.x / 2,-size_.y / 2}
	};

#pragma endregion

#pragma region アニメーション

	// 画像
	int* img_;

	// 画像の拡大率
	double imgExtRate_;

	// 画像の角度
	double imgAngle_;

	// 画像の上下の反転
	bool turnXFlag_;

	// 画像の左右の反転
	bool turnYFlag_;

	// アニメーションカウンタ
	int animCnt_;

	// アニメーション番号
	int animIdx_;

#pragma endregion

	// 移動
	virtual void Move(const float deltaTime);

	const std::shared_ptr<Actor>& GetThis() { return shared_from_this(); }

private:

	// 座標
	Vector2F pos_;

	// 衝突座標
	Vector2F colPos_;

	// 衝突サイズ
	Vector2F colSize_;

	// アクティブ状態かどうか
	bool isActive_;

};