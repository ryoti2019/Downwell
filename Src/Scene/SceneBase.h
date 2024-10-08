#pragma once

class SceneBase
{

public:

	// コンストラクタ
	SceneBase();

	// デストラクタ
	virtual ~SceneBase() = 0;

	// 初期化処理
	virtual void Init() = 0;

	// 更新ステップ
	virtual void Update(const float deltaTime) = 0;

	// 描画処理
	virtual void Draw() = 0;

	// 解放処理
	virtual void Release() = 0;

};