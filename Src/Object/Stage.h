#pragma once
#include "../Object/Actor.h"

int stage1[10][10] = 
{
	{1,1,1,1,0,0,1,1,1,1},
	{1,1,0,0,0,0,0,0,1,1},
	{}

}

class Stage
{

public:

	// �}�b�v�摜�̑�����
	static constexpr int STAGE_IMAGE_NUM = 3;

	// �}�b�v�摜�̉��̑�����
	static constexpr int STAGE_IMAGE_X_NUM = 3;

	// �}�b�v�摜�T�C�Y
	static constexpr int STAGE_IMAGE_SIZE = 32;

	Stage();
	~Stage();

	void Init();
	void Update();
	void Draw();
	void Release();

private:



};