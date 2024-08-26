#pragma once
#include "../Object/Actor.h"

class Wall : public Actor
{

public:

	Wall();
	~Wall();

	void Init(const Vector2F& pos)override;
	void Update()override;
	void Draw()override;
	void Release()override;

private:

};

