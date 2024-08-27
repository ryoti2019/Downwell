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

	ActorManager() = default;
	~ActorManager() = default;

	void Init();
	void Update();
	void Draw();
	void Release();
	
	// Actorの派生クラスの実体の作成
	template <typename actor>
	void CreateActor();

	// アクティブになったものを格納
	std::shared_ptr<Actor> ActiveData(const ActorType type, const Vector2F& pos);

	// 非アクティブになったものを格納
	void DeactiveData(const std::shared_ptr<Actor>& actor);

	const auto& const GetActiveActorData() { return activeActorData_; };

private:

	// すべてのアクターをまとめたデータ
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> activeActorData_;

	// すべてのアクターをまとめたデータ
	std::unordered_map<ActorType, std::vector<std::shared_ptr<Actor>>> deactiveActorData_;

};

// テンプレートでActorの継承先の型に置き換えることができる
template<typename T>
inline void ActorManager::CreateActor()
{

	// この中でActorたちの実体をまとめて作る

	std::shared_ptr<Actor> actor = std::make_shared<T>();

	// ポインタを使うときはクラッシュしないようにNULLチェックを行うようにする
	if (!actor) return;

	const Vector2F pos = { 0.0f,0.0f };
	actor->Init(pos);

	// deactiveActorData_の中にすでに同じ型が生成されているかチェックする
	auto deactorElem = deactiveActorData_.find(actor->GetActorType());

	// 生成されていない場合は、新しくvector配列の箱を作りその中に要素を入れていく
	if (deactorElem == deactiveActorData_.end())
	{
		std::vector<std::shared_ptr<Actor>> data;
		data.emplace_back(actor);
		deactiveActorData_.emplace(actor->GetActorType(), data);
	}
	// 生成されている場合はすでにある箱の中に要素を入れていく
	else
	{
		deactorElem->second.emplace_back(actor);
	}

}