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

	// �A�N�e�B�u��Ԃ��ǂ���
	bool isActive_;

#pragma endregion

#pragma region �A�j���[�V����

	// �A�j���[�V�����J�E���^
	int animCnt_;

	// �A�j���[�V�����ԍ�
	int animIdx_;

#pragma endregion

	// �ړ�
	virtual void Move(void);

	// �Փ˔���
	virtual void Collision(void);

	// �����Ă��邩�ǂ���
	bool IsAlive(void);

};