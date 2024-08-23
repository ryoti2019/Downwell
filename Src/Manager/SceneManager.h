#pragma once
#include <memory>
#include <chrono>
class SceneBase;
class ActorManager;
class GameScene;

class SceneManager
{

public:

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME,
		GAMEOVER,
	};

	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static SceneManager& GetInstance(void) { return *instance_; };

	void Init(void);
	void Update(void);
	void Draw(void);

	// ���\�[�X�̔j��
	void Destroy(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void) { return sceneId_; };

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const { return deltaTime_; };

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// ���̃V�[�����擾
	std::shared_ptr<SceneBase> GetNowScene() {return scene_;};

private:

	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �e��V�[��
	std::shared_ptr<SceneBase> scene_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// �Q�[���p�b�h�ő��삷�邽�߂̃t���O
	bool isGamePad_;

	// ��������̃t���O
	bool isOperation_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	// �R�s�[�R���X�g���N�^�����l
	SceneManager(const SceneManager&);
	// �f�X�g���N�^�����l
	~SceneManager(void) = default;

	// �f���^�^�C�������Z�b�g����
	void ResetDeltaTime(void);

};