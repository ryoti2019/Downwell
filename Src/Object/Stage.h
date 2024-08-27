#pragma once
#include "../Object/Actor.h"

//int stage1[10][10] =
//{
//	{1,1,1,1,0,0,1,1,1,1},
//	{1,1,0,0,0,0,0,0,1,1},
//	{1,1,0,0,0,0,0,0,1,1},
//};
//
//int stage2[10][10] =
//{
//	{1,1,1,1,0,0,1,1,1,1},
//	{1,1,0,0,0,0,0,0,1,1},
//	{1,1,0,0,0,0,0,0,1,1},
//};
//
//int stage3[10][10] =
//{
//	{1,1,1,1,0,0,1,1,1,1},
//	{1,1,0,0,0,0,0,0,1,1},
//	{1,1,0,0,0,0,0,0,1,1},
//};

enum class MAP_NO
{
	PLAYER,
	ENEMY,
	ENEMY2,
	WALL,
	BREAK_BLOCK,
	SCAFFOLD,
};

class Stage
{

public:

	// �}�b�v�摜�̑�����
	static constexpr int STAGE_IMAGE_NUM = 6;

	// �}�b�v�摜�̉��̑�����
	static constexpr int STAGE_IMAGE_X_NUM = 6;

	// �}�b�v�摜�T�C�Y
	static constexpr int STAGE_IMAGE_SIZE = 32;

	// �}�b�v�̉��T�C�Y
	static constexpr int MAP_MAX_X_SIZE = 14;

	// �}�b�v�̏c�T�C�Y
	static constexpr int MAP_MAX_Y_SIZE = 20;

	static constexpr int OFFSET_X = 10;
	static constexpr int OFFSET_Y = 10;

	Stage() = default;
	~Stage() = default;

	void Init();
	void Update();
	void Draw();
	void Release();

private:

	// �X�e�[�W
	int stageMap_[MAP_MAX_Y_SIZE][MAP_MAX_X_SIZE];

	// �}�b�v�ԍ�
	MAP_NO mapNo_;

	// ������̕���
	static std::vector<std::string> Split(std::string line, char delimiter);

	// CSV�f�[�^�̓ǂݍ���
	void LoadCsvData();

};