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

	// �v���C���[�̉摜�T�C�Y
	static constexpr int PLAYER_IMAGE_SIZE = 32;

	//	�W�����v�L�[���͂��󂯕t����t���[����
	static constexpr int INPUT_JUMP_FRAME = 6;

	// �ő�W�����v��
	static constexpr float MAX_JUMP_POW = 50.0f;

	Player();

	~Player() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	// �v���C���[�摜
	int* playerImg_;

	// �W�����v���Ă��邩
	bool isJump_;

	// �W�����v�̓��͎���
	float cntJumpInput_;

	// �W�����v�L�[�̉�������
	bool isPutJumpKey_;

	// �W�����v��
	float jumpPow_;

	// �e���łĂ邩
	bool isShot_;

	void Move() override;

	void Jump();

	void ProcessJump();

	void SetJumpPow(float pow);

	void CollisionFoot();

	void ShotAttack();

};

