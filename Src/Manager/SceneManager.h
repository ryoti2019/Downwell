#pragma once
#include <memory>
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
	static void CreateInstance();

	// �C���X�^���X�̎擾
	static SceneManager& GetInstance() { return *instance_; };

	void Init();
	void Update(const float deltaTime);
	void Draw();

	// ���\�[�X�̔j��
	void Destroy();

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID() { return sceneId_; };

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

	// �Q�[���p�b�h�ő��삷�邽�߂̃t���O
	bool isGamePad_;

	// ��������̃t���O
	bool isOperation_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager();
	// �R�s�[�R���X�g���N�^�����l
	SceneManager(const SceneManager&);
	// �f�X�g���N�^�����l
	~SceneManager() = default;

};