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

	// マップ画像の総枚数
	static constexpr int STAGE_IMAGE_NUM = 3;

	// マップ画像の横の総枚数
	static constexpr int STAGE_IMAGE_X_NUM = 3;

	// マップ画像サイズ
	static constexpr int STAGE_IMAGE_SIZE = 32;

	Stage();
	~Stage();

	void Init();
	void Update();
	void Draw();
	void Release();

private:



};