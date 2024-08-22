#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "../Object/Actor.h"

class Actor;
class Player;
//class Enemy;
//class Stage;

enum class ActorType;

class ActorManager
{

public:

	ActorManager();
	~ActorManager();

	void Init();
	void Update();
	void Draw();
	void Release();
	
	template <typename actor>
	void CreateActor();

	std::vector<std::shared_ptr<Actor>> GetActorData();

private:

	// すべてのアクターをまとめたデータ
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> actorData_;

	//// プレイヤー
	//std::shared_ptr<Player> player_;

};

// テンプレートでActorの継承先の型に置き換えることができる
template<typename T>
inline void ActorManager::CreateActor()
{

	// この中でActorたちの実体をまとめて作る

	std::shared_ptr<Actor> actor = std::make_shared<T>();

	// ポインタを使うときはクラッシュしないようにNULLチェックを行うようにする
	if (!actor) return;

	actor->Init();

	// actorDataの中にすでに同じ型が生成されているかチェックする
	auto actorElem = actorData_.find(actor->GetActorType());

	// 生成されていない場合は、新しくvector配列の箱を作りその中に要素を入れていく
	if ( actorElem == actorData_.end())
	{
		std::vector<std::shared_ptr<Actor>> data;
		data.emplace_back(actor);
		actorData_.emplace(actor->GetActorType(), data);
	}
	// 生成されている場合はすでにある箱の中に要素を入れていく
	else
	{
		actorElem->second.emplace_back(actor);
	}

}