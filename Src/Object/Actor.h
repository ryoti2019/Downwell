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

	// �����Ă��邩�ǂ���
	const bool GetIsAlive() const { return isAlive_; };

protected:

#pragma region �I�u�W�F�N�g�̏��

	// ���W
	Vector2F pos_;

	// �ړ�����W
	Vector2F movedPos_;

	// ����
	Vector2F dir_;

	// �X�s�[�h
	float speed_;

	// �ړ���
	float movePow_;

	// HP
	int hp_;

	// �I�u�W�F�N�g�ƏՓ˂��Ă��邩
	bool isHitObject_;

	// ���ƏՓ˂��Ă��邩
	bool isHitFloor_;

	// �A�N�^�[�̎��
	ActorType actorType_;

	// �����Ă��邩�ǂ���
	bool isAlive_;

	// �摜
	int* img_;

#pragma endregion

#pragma region �A�j���[�V����

	// �A�j���[�V�����J�E���^
	int animCnt_;

	// �A�j���[�V�����ԍ�
	int animIdx_;

#pragma endregion

	// �ړ�
	virtual void Move();

	// �Փ˔���
	virtual void Collision();

	const std::shared_ptr<Actor>& GetThis() { return shared_from_this(); }

private:

	// �A�N�e�B�u��Ԃ��ǂ���
	bool isActive_;

};