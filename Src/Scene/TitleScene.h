#pragma once
#include "../Scene/SceneBase.h"

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

};

