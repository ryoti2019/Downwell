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

	// マップ画像の総枚数
	static constexpr int STAGE_IMAGE_NUM = 6;

	// マップ画像の横の総枚数
	static constexpr int STAGE_IMAGE_X_NUM = 6;

	// マップ画像サイズ
	static constexpr int STAGE_IMAGE_SIZE = 32;

	// マップの横サイズ
	static constexpr int MAP_MAX_X_SIZE = 14;

	// マップの縦サイズ
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

	// ステージ
	int stageMap_[MAP_MAX_Y_SIZE][MAP_MAX_X_SIZE];

	// マップ番号
	MAP_NO mapNo_;

	// 文字列の分割
	static std::vector<std::string> Split(std::string line, char delimiter);

	// CSVデータの読み込み
	void LoadCsvData();

};