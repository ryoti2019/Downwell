#pragma once
#include <memory>
#include <vector>
#include "../Object/Actor.h"

class Player : public Actor
{
public:

	static constexpr int IMAGE_NUM = 4;

	Player(void);

	~Player(void) override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	std::vector<std::shared_ptr<Player>> GetPlayer();

private:

	// ƒvƒŒƒCƒ„[‰æ‘œ
	int* playerImg_;

	void Move(void) override;

	void Jump(void);




};

