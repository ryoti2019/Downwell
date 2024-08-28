#pragma once
#include <memory>
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
	static void CreateInstance();

	// インスタンスの取得
	static SceneManager& GetInstance() { return *instance_; };

	void Init();
	void Update(const float deltaTime);
	void Draw();

	// リソースの破棄
	void Destroy();

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID() { return sceneId_; };

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

	// ゲームパッドで操作するためのフラグ
	bool isGamePad_;

	// 操作説明のフラグ
	bool isOperation_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager();
	// コピーコンストラクタも同様
	SceneManager(const SceneManager&);
	// デストラクタも同様
	~SceneManager() = default;

};