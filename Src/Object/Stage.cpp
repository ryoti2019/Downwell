#include <DxLib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ActorManager.h"
#include "../Application.h"
#include "../Scene/GameScene.h"
#include "../Object/Player.h"
#include "../Object/Shot.h"
#include "../Object/Wall.h"
#include "Stage.h"

void Stage::Init()
{

	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	LoadCsvData();

	Vector2F pos = { 0.0f,0.0f };

	// ステージを生成
	for (int y = 0; y < MAP_MAX_Y_SIZE; y++)
	{
		for (int x = 0; x < MAP_MAX_X_SIZE; x++)
		{
			auto mapNo = ConvertToActorType.find(stageMap_[y][x]);
			CheckMapNo(mapNo->first);
			pos = { static_cast<float>(x) * STAGE_IMAGE_SIZE + OFFEST_POS, static_cast<float>(y) * STAGE_IMAGE_SIZE + 50.0f/* + (MAP_MAX_Y_SIZE * OFFSET_Y)*/ };
			actorManager->ActiveData(mapNo->second, pos);
		}
	}

}

void Stage::Update()
{
}

void Stage::Draw()
{
}

void Stage::Release()
{
}

std::vector<std::string> Stage::Split(std::string line, char delimiter)
{

	// 可変長配列の返り値を準備
	std::vector <std::string> result;

	// stringをファイルストリームに変換
	std::istringstream stream(line);

	// 読み込んだ文字列を格納する用変数
	std::string field;

	// streamを順番に読み込み
	// 第３引数で指定された文字までを第２引数に返す
	while (getline(stream, field, delimiter))
	{
		// 可変配列に追加
		result.push_back(field);
	}

	// 例: line "aaa,bbb,ccc"
	//     ⇒result

	return result;

}

void Stage::LoadCsvData()
{

	std::ifstream ifs = std::ifstream("Data/Csv/map.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_Y_SIZE; y++)
	{
		for (int x = 0; x < MAP_MAX_X_SIZE; x++)
		{
			stageMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			stageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::CheckMapNo(int no)
{

	// 基底クラスから使いたい型へキャストする
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULLチェック
	if (!gameScene) return;

	// アクターマネージャーを取得
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	switch (no)
	{
	case -1:
		break;
	case 0:
		// プレイヤーを生成
		actorManager->CreateActor<Player>();
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		// プレイヤーを生成
		actorManager->CreateActor<Wall>();
		break;
	case 4:
		break;
	case 5:
		break;
	}

}