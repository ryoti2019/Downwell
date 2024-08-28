#pragma once
#include "../Object/Actor.h"

class Shot : public Actor
{

public:

	// �e�摜�̑�����
	static constexpr int SHOT_IMAGE_NUM = 5;

	// �e�摜�̉��̑�����
	static constexpr int SHOT_IMAGE_X_NUM = 5;

	// �e�摜�̉��T�C�Y
	static constexpr int SHOT_IMAGE_X_SIZE = 32;

	// �e�摜�̏c�T�C�Y
	static constexpr int SHOT_IMAGE_Y_SIZE = 64;

	// ��������
	static constexpr float ALIVE_TIME = 5.0f;

	// �e�̑��x
	static constexpr float SHOT_SPEED = 5.0f;

	Shot();
	~Shot();

	void Init(const Vector2F& pos) override;
	void Update(const float deltaTime) override;
	void Draw() override;
	void Release() override;

private:

	// �v���C���[�摜
	int* shotImg_;

	// �������Ԃ̃J�E���^
	float aliveCnt_;

	void Move(const float deltaTime) override;

};

