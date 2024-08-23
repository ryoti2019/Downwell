#pragma once
#include <memory>
#include <chrono>
class SceneBase;
class ActorManager;
class GameScene;

class SceneManager
{

public:

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME,
		GAMEOVER,
	};

	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void) { return *instance_; };

	void Init(void);
	void Update(void);
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID(void) { return sceneId_; };

	// デルタタイムの取得
	float GetDeltaTime(void) const { return deltaTime_; };

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// 今のシーンを取得
	std::shared_ptr<SceneBase> GetNowScene() {return scene_;};

private:

	// 静的インスタンス
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// 各種シーン
	std::shared_ptr<SceneBase> scene_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// ゲームパッドで操作するためのフラグ
	bool isGamePad_;

	// 操作説明のフラグ
	bool isOperation_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager&);
	// デストラクタも同様
	~SceneManager(void) = default;

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

};