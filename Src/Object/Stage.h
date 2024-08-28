#pragma once
#include <unordered_map>


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

enum class ActorType;

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

	// �^�񒆂ɕ\�����邽�߂�
	static constexpr float OFFEST_POS = 416.0f;

	const std::unordered_map<int, ActorType> ConvertToActorType =
	{
		{-1, ActorType::NONE},
		{0, ActorType::PLAYER},
		{1, ActorType::ENEMY},
		{2, ActorType::ENEMY2},
		{3, ActorType::WALL},
		{4, ActorType::BREAK_BLOCK},
		{5, ActorType::SCAFFOLD}
	};

	Stage() = default;
	~Stage() = default;

	void Init();
	void Update();
	void Draw();
	void Release();

private:

	// �X�e�[�W
	int stageMap_[MAP_MAX_Y_SIZE][MAP_MAX_X_SIZE];

	// ������̕���
	static std::vector<std::string> Split(std::string line, char delimiter);

	// CSV�f�[�^�̓ǂݍ���
	void LoadCsvData();

	// �}�b�v�ԍ��̊m�F
	void CheckMapNo(int no);

};