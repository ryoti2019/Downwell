#pragma once
#include "../Object/Actor.h"

class Shot : public Actor
{

public:

	Shot();
	~Shot();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

};

