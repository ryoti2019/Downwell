#pragma once
#include "../Scene/SceneBase.h"

class TitleScene : public SceneBase
{

public:

	// �R���X�g���N�^
	TitleScene();

	// �f�X�g���N�^
	~TitleScene();

	void Init() override;
	void Update(const float deltaTime) override;
	void Draw() override;
	void Release() override;

private:

};

