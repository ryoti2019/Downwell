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

	// �����Ă��邩�ǂ���
	const bool GetIsAlive() const { return isAlive_; };

	const Vector2F& GetSize() const { return size_; };

	void SetIsHit(const bool hit) { isHit_ = hit; };

	const Vector2F& GetMovedPos() const { return movedPos_; };

	void SetMovedPos(const Vector2F& movedPos) { movedPos_ = movedPos; };

protected:

#pragma region �I�u�W�F�N�g�̏��

	// ���W
	Vector2F pos_;

	// �ړ�����W
	Vector2F movedPos_;

	// �摜�T�C�Y
	Vector2F size_;

	// ����
	Vector2F dir_;

	// �X�s�[�h
	float speed_;

	// �ړ���
	float movePow_;

	// HP
	int hp_;

	// �Փ˂��Ă��邩
	bool isHit_;

	// �A�N�^�[�̎��
	ActorType actorType_;

	// �����Ă��邩�ǂ���
	bool isAlive_;

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

	// �Փ˔���
	virtual void Collision();

	const std::shared_ptr<Actor>& GetThis() { return shared_from_this(); }

private:

	// �A�N�e�B�u��Ԃ��ǂ���
	bool isActive_;

};