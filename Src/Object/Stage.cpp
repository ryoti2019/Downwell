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

	// ���N���X����g�������^�փL���X�g����
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULL�`�F�b�N
	if (!gameScene) return;

	// �A�N�^�[�}�l�[�W���[���擾
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	LoadCsvData();

	Vector2F pos = { 0.0f,0.0f };

	// �X�e�[�W�𐶐�
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

	// �ϒ��z��̕Ԃ�l������
	std::vector <std::string> result;

	// string���t�@�C���X�g���[���ɕϊ�
	std::istringstream stream(line);

	// �ǂݍ��񂾕�������i�[����p�ϐ�
	std::string field;

	// stream�����Ԃɓǂݍ���
	// ��R�����Ŏw�肳�ꂽ�����܂ł��Q�����ɕԂ�
	while (getline(stream, field, delimiter))
	{
		// �ϔz��ɒǉ�
		result.push_back(field);
	}

	// ��: line "aaa,bbb,ccc"
	//     ��result

	return result;

}

void Stage::LoadCsvData()
{

	std::ifstream ifs = std::ifstream("Data/Csv/map.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_Y_SIZE; y++)
	{
		for (int x = 0; x < MAP_MAX_X_SIZE; x++)
		{
			stageMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			stageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::CheckMapNo(int no)
{

	// ���N���X����g�������^�փL���X�g����
	std::shared_ptr<GameScene> gameScene =
		std::dynamic_pointer_cast<GameScene>(SceneManager::GetInstance().GetNowScene());

	// NULL�`�F�b�N
	if (!gameScene) return;

	// �A�N�^�[�}�l�[�W���[���擾
	std::shared_ptr<ActorManager> actorManager = gameScene->GetActorManager();

	switch (no)
	{
	case -1:
		break;
	case 0:
		// �v���C���[�𐶐�
		actorManager->CreateActor<Player>();
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		// �v���C���[�𐶐�
		actorManager->CreateActor<Wall>();
		break;
	case 4:
		break;
	case 5:
		break;
	}

}