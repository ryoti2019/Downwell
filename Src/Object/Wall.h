#pragma once
#include "../Object/Actor.h"

class Wall : public Actor
{

public:

	// �}�b�v�摜�̑�����
	static constexpr int WALL_IMAGE_NUM = 3;

	// �}�b�v�摜�̉��̑�����
	static constexpr int WALL_IMAGE_X_NUM = 3;

	// �}�b�v�摜�T�C�Y
	static constexpr int WALL_IMAGE_SIZE = 32;

	// �}�b�v�̉��T�C�Y
	static constexpr int MAP_MAX_X_SIZE = 14;

	// �}�b�v�̏c�T�C�Y
	static constexpr int MAP_MAX_Y_SIZE = 20;

	Wall() = default;
	~Wall() = default;

	void Init(const Vector2F& pos)override;
	void Update(const float deltaTime)override;
	void Release()override;

private:

};

