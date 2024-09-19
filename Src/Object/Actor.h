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

	// �����Ă��邩�ǂ���
	const bool GetIsAlive() const { return isAlive_; };

	const Vector2F& GetSize() const { return size_; };

	void SetIsHitFoot(const bool hit) { isHitFoot_ = hit; };

	void SetIsHitLR(const bool hit) { isHitLR_ = hit; };

	const std::vector<Vector2F>& GetCollisionPosList() const{ return collisionPosList_; };

protected:

#pragma region �I�u�W�F�N�g�̏��

	// �摜�T�C�Y
	Vector2F size_;

	// �X�s�[�h
	float speed_;

	// HP
	int hp_;

	// ���n���Ă��邩
	bool isHitFoot_;

	// �E���̕ǂɓ������Ă��邩
	bool isHitLR_;

	// �A�N�^�[�̎��
	ActorType actorType_;

	// �����Ă��邩�ǂ���
	bool isAlive_;

	const std::vector<Vector2F> collisionPosList_ =
	{
		{-size_.x / 2,-size_.y / 2},{-size_.x / 2,-size_.y / 2},{-size_.x / 2,-size_.y / 2},{-size_.x / 2,-size_.y / 2}
	};

#pragma endregion

#pragma region �A�j���[�V����

	// �摜
	int* img_;

	// �摜�̊g�嗦
	double imgExtRate_;

	// �摜�̊p�x
	double imgAngle_;

	// �摜�̏㉺�̔��]
	bool turnXFlag_;

	// �摜�̍��E�̔��]
	bool turnYFlag_;

	// �A�j���[�V�����J�E���^
	int animCnt_;

	// �A�j���[�V�����ԍ�
	int animIdx_;

#pragma endregion

	// �ړ�
	virtual void Move(const float deltaTime);

	const std::shared_ptr<Actor>& GetThis() { return shared_from_this(); }

private:

	// ���W
	Vector2F pos_;

	// �Փˍ��W
	Vector2F colPos_;

	// �Փ˃T�C�Y
	Vector2F colSize_;

	// �A�N�e�B�u��Ԃ��ǂ���
	bool isActive_;

};