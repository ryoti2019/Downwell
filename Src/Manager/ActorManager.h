#pragma once
#include <memory>
class Actor;

class ActorManager
{
public:

	ActorManager(void);
	~ActorManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	std::unique_ptr<Actor> actor_;

};

