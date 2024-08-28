#pragma once
#include <memory>
#include <vector>
#include "../Object/Actor.h"

class ActorManager;

class Player : public Actor
{
public:

	// �v���C���[�摜�̑�����
	static constexpr int PLAYER_IMAGE_NUM = 4;

	// �v���C���[�摜�̉��̑�����
	static constexpr int PLAYER_IMAGE_X_NUM = 4;

	// �v���C���[�摜�T�C�Y
	static constexpr int PLAYER_IMAGE_SIZE = 32;

	//	�W�����v�L�[���͂��󂯕t����t���[����
	static constexpr int INPUT_JUMP_FRAME = 6;

	// �ő�W�����v��
	static constexpr float MAX_JUMP_POW = 30.0f;

	// �e��łĂ�܂ł̃N�[���^�C��
	static constexpr float SHOT_COOL_TIME = 0.1f;

	Player();

	~Player() override;

	void Init(const Vector2F& pos) override;
	void Update(const float deltaTime) override;
	void Release() override;

	void SetIshitLR(const bool hit) { isHitLR_ = hit; };

private:

	// �W�����v���Ă��邩
	bool isJump_;

	// �W�����v�̓��͎���
	float cntJumpInput_;

	// �W�����v�L�[�̉�������
	bool isPutJumpKey_;

	// �W�����v��
	float jumpPow_;

	// �e���łĂ邩
	bool isCanShot_;

	// �e��ł��Ă��邩
	bool isDoingShot_;

	// �e��ł܂ł̃N�[���^�C���J�E���^
	float coolTime_;

	// �E���̕ǂɓ������Ă��邩
	bool isHitLR_;

	void Move(const float deltaTime) override;

	void Jump();

	void ProcessJump();

	void SetJumpPow(float pow);

	void ShotAttack(const float deltaTime);

	void CollisionStage();

};

