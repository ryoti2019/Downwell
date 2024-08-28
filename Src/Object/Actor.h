#pragma once
#include <memory>
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
	virtual void Create(const Vector2F& pos);
	virtual void Update(const float deltaTime);
	virtual void Draw();
	virtual void DrawMap();
	virtual void Release();

	int GetHP() const { return hp_; }

	void DecreaseHP(int hp) { hp_ -= hp; };

	const ActorType GetActorType() const { return actorType_; }

	const bool GetIsActive() const { return isActive_; }

	void SetIsActive(const bool isActive) { isActive_ = isActive; }

	const Vector2F& GetPos() const { return pos_; }

	void SetPos(const Vector2F& pos) { pos_ = pos; };

	// 生きているかどうか
	const bool GetIsAlive() const { return isAlive_; };

	const Vector2F& GetSize() const { return size_; };

	void SetIsHit(const bool hit) { isHit_ = hit; };

	const Vector2F& GetMovedPos() const { return movedPos_; };

	void SetMovedPos(const Vector2F& movedPos) { movedPos_ = movedPos; };

protected:

#pragma region オブジェクトの情報

	// 座標
	Vector2F pos_;

	// 移動後座標
	Vector2F movedPos_;

	// 画像サイズ
	Vector2F size_;

	// 方向
	Vector2F dir_;

	// スピード
	float speed_;

	// 移動量
	float movePow_;

	// HP
	int hp_;

	// 衝突しているか
	bool isHit_;

	// アクターの種類
	ActorType actorType_;

	// 生きているかどうか
	bool isAlive_;

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

	// 衝突判定
	virtual void Collision();

	const std::shared_ptr<Actor>& GetThis() { return shared_from_this(); }

private:

	// アクティブ状態かどうか
	bool isActive_;

};