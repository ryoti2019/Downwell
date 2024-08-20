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

#pragma region �I�u�W�F�N�g�̍��W��Փ˔���

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

#pragma endregion

	// �A�j���[�V����

	// �ړ�
	virtual void Move(void);

	// �Փ˔���
	virtual void Collision(void);

	// �����Ă��邩�ǂ���
	bool IsAlive(void);

};