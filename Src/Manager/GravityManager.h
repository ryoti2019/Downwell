#pragma once
#include "../Common/Vector2F.h"

class GravityManager
{

public:

	// 重力
	static constexpr float GRAVITY = 4.0f;

	// 明示的にインステンスを生成する
	static void CreateInstance();

	// 静的インスタンスの取得
	static GravityManager& GetInstance() { return *instance_; };

	float AddGravity(float jumpPow);

private:

	// 静的インスタンス
	static GravityManager* instance_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	GravityManager();
	// コピーコンストラクタも同様
	GravityManager(const GravityManager&);
	// デストラクタも同様
	~GravityManager() = default;

};

