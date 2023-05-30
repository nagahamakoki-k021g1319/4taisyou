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
/// ゲームシーン
/// </summary>
class GameScene
{
private: // 静的メンバ変数
	//static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	void Reset();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };


private: // メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


private:	//メンバ変数
	const float PI = 3.141592;

	//カメラ
	Camera* mainCamera = nullptr;
	Camera* camera1 = nullptr;
	Camera* camera2 = nullptr;
	Camera* camera3 = nullptr;

	//プレイヤー
	Player* player_ = nullptr;

	//エネミー
	EnemyManager* enemyManager_ = nullptr;
	const int hitStopLimit = 1;
	int hitStopTimer = hitStopLimit;

	//背景や床
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
	Sprite* buttomx = nullptr;
	Sprite* buttomy = nullptr;
	Sprite* buttomb = nullptr;
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
	Sprite* sord3UI = nullptr;

	Sprite* srr = nullptr;
	Vector2 srrPosition;
	Sprite* srl = nullptr;
	Vector2 srlPosition;
	Sprite* sru = nullptr;
	Vector2 sruPosition;
	Sprite* srd = nullptr;
	Vector2 srdPosition;

	Sprite* tutoframe1 = nullptr;
	Sprite* tutoframe2 = nullptr;
	Sprite* tutoframe3 = nullptr;

	Sprite* option2 = nullptr;
	Sprite* option3 = nullptr;
	Sprite* option4 = nullptr;
	Sprite* option5 = nullptr;

	Sprite* optionco = nullptr;
	
	Sprite* mouse = nullptr;
	Vector2 mousePosition;

	Sprite* markPointer = nullptr;
	Vector2 mapoPosition;

	//ゲームフロー
	enum class Scene
	{
			Title,
			Select,
			Play,
			Clear,
			Gameover,
			Option,
	};
	Scene scene;
	int stage;
	//カミングスーン用フラグ
	int cmsoon = 0;
	Sprite* titlePic;
	Sprite* selectPic;
	Sprite* clearPic;
	Sprite* gameoverPic;

	//選択画面
	int selectMode;

	//ポーズ画面
	bool isPause;
	bool keycon;
	int pauseSelect;
	Sprite* pauseBg;

	//オプション
	float Sensitivity;
	int selecOtption;
	bool isChangeSensitivity;
	Sprite* optionPic;

	//攻撃する前のわかりやすいエッフェクト(なぜか敵に持たせられない)
	Sprite* CdUI = nullptr;
	Sprite* CdUI1 = nullptr;
	Sprite* CdUI2 = nullptr;
	int  CdTimer = 0;
	int  isCdFlag = 0;

	//音関係まとめ
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;
	int soundCheckFlag3 = 0;
	int soundCheckFlag4 = 0;

	//戦闘開始時
	bool isActionStop;
	int actionStopTimer;
	const int actionStopLimit = 3 * 60;
	Sprite* std3 = nullptr;
	Sprite* std2 = nullptr;
	Sprite* std1 = nullptr;
	Sprite* stdgo = nullptr;
	Sprite* stdgo2 = nullptr;
};