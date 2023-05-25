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
	Camera* camera = nullptr;

	//プレイヤー
	Player* player_ = nullptr;

	//エネミー
	EnemyManager* enemyManager_ = nullptr;
	const int hitStopLimit = 10;
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

	//ゲームフロー
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
	//カミングスーン用フラグ
	int cmsoon = 0;
	Sprite* titlePic;
	Sprite* selectPic;
	Sprite* clearPic;
	Sprite* gameoverPic;

	//攻撃する前のわかりやすいエッフェクト(なぜか敵に持たせられない)
	Sprite* CdUI = nullptr;
	Sprite* CdUI1 = nullptr;
	Sprite* CdUI2 = nullptr;
	int  CdTimer = 0;
	int  isCdFlag = 0;

	//音関係まとめ
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;
};