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

	// 真ん中に表示するための
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

	// ステージ
	int stageMap_[MAP_MAX_Y_SIZE][MAP_MAX_X_SIZE];

	// 文字列の分割
	static std::vector<std::string> Split(std::string line, char delimiter);

	// CSVデータの読み込み
	void LoadCsvData();

	// マップ番号の確認
	void CheckMapNo(int no);

};