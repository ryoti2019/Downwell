#pragma once
#include <memory>
#include <chrono>
class SceneBase;
class ActorManager;

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
	static SceneManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Draw(void);

	// ���\�[�X�̔j��
	void Destroy(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;

	// �Q�[���p�b�h�ő��삷��t���O���擾����
	bool GetGamePad(void);

	// �Q�[���p�b�h�ő��삷��t���O���擾����
	void SetGamePad(bool isPad);

	// ��������̃t���O�̎擾
	bool GetIsOperation(void);

	// ��������̃t���O�̎擾
	void SetIsOperation(bool isOp);

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

private:

	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �e��V�[��
	std::unique_ptr<SceneBase> scene_;

	// �A�N�^�[
	std::unique_ptr<ActorManager> actorManager_;

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