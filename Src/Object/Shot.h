#pragma once
#include "../Object/Actor.h"

class Shot : public Actor
{

public:

	// �v���C���[�摜�̑�����
	static constexpr int PLAYER_IMAGE_NUM = 4;

	Shot();
	~Shot();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	// �v���C���[�摜
	int* playerImg_;


	void Move() override;

};

