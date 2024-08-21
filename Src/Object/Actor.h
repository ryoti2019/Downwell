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

#pragma region �I�u�W�F�N�g�̏��

	// ���W
	Vector2F pos_;

	// �ړ�����W
	Vector2F movedPos_;

	// ����
	Vector2F dir_;

	// �X�s�[�h
	float speed_;

	// HP
	int hp_;

	// �I�u�W�F�N�g�ƏՓ˂��Ă��邩
	bool isHitObject_;

	// �X�e�[�W�ƏՓ˂��Ă��邩
	bool isHitStage_;

	// �A�N�^�[�̎��
	ActorType actorType_;

#pragma endregion

#pragma region �A�j���[�V����

	// �A�j���[�V�����J�E���^
	int animCnt_;

#pragma endregion

	// �ړ�
	virtual void Move(void);

	// �Փ˔���
	virtual void Collision(void);

	// �����Ă��邩�ǂ���
	bool IsAlive(void);

};