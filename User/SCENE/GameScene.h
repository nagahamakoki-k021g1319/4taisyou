#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <string>
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"

#include "Matrix4.h"
#include "Camera.h"

#include "ParticleManager.h"

#include"Player.h"
#include"EnemyManager.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �ÓI�����o�ϐ�
	//static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	void Reset();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };


private: // �����o�ϐ� (�Œ�)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


private:	//�����o�ϐ�
	const float PI = 3.141592;

	//�J����
	Camera* camera = nullptr;

	//�v���C���[
	Player* player_ = nullptr;

	//�G�l�~�[
	EnemyManager* enemyManager_ = nullptr;
	const int hitStopLimit = 10;
	int hitStopTimer = hitStopLimit;

	//�w�i�⏰
	Object3d* floor = nullptr;
	Model* floorMD = nullptr;
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
	Object3d* field = nullptr;
	Model* fieldMD = nullptr;

	//UI
	Sprite* UI = nullptr;
	Sprite* buttomPng1 = nullptr;
	Sprite* buttomPng2 = nullptr;
	Sprite* hpGauge = nullptr;
	Vector2 hpPosition;
	Sprite* mpGauge = nullptr;
	Vector2 mpPosition;
	Sprite* unionGauge = nullptr;
	Vector2 unionScale;
	Sprite* avoidUI = nullptr;
	Vector3 avoidScale;
	Sprite* sordUI = nullptr;
	Sprite* sord2UI = nullptr;

	Sprite* srr = nullptr;
	Vector2 srrPosition;
	Sprite* srl = nullptr;
	Vector2 srlPosition;
	Sprite* sru = nullptr;
	Vector2 sruPosition;
	Sprite* srd = nullptr;
	Vector2 srdPosition;

	//�Q�[���t���[
	enum class Scene
	{
			Title,
			Select,
			Play,
			Clear,
			Gameover,
	};
	Scene scene;
	int stage;
	//�J�~���O�X�[���p�t���O
	int cmsoon = 0;
	Sprite* titlePic;
	Sprite* selectPic;
	Sprite* clearPic;
	Sprite* gameoverPic;

	//�U������O�̂킩��₷���G�b�t�F�N�g(�Ȃ����G�Ɏ��������Ȃ�)
	Sprite* CdUI = nullptr;
	Sprite* CdUI1 = nullptr;
	Sprite* CdUI2 = nullptr;
	int  CdTimer = 0;
	int  isCdFlag = 0;

	//���֌W�܂Ƃ�
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;
	
	//�퓬�J�n��
	bool isActionStop;
	int actionStopTimer;
	const int actionStopLimit = 4 * 60;
};