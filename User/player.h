#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"
#include "Wolf.h"

#include "Gorilla.h"
#include "ParticleManager.h"
#include "Audio.h"

#include "FBXModel.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"


class Player {
public:
	Player();
	~Player();

	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Reset();

	void Update();
	void Rota();
	void Move();
	void camUpdate();

	void Attack();

	void Draw();
	void FbxDraw();
	void EffUpdate();
	void EffHealUpdate();
	void EffHiHealUpdate();
	void EffDraw();

	void OnCollision();

	void SetEnemyPos(Transform* enemyPos) { enemyPos_ = enemyPos; };

	void LightAttack();
	void HeavyAttack();
	void Dodge();

	bool CheckAttack2Enemy(Vector3 enemyPos, float& damage);
	bool CheckBody2Enemy(Vector3 enemyPos);


	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	float GetHp() { return hp; };
	float GetMp() { return mp; };
	bool GetIsDodge() { return isDodge; };
	Vector3 GetCamShake() { return camShakeVec; };
	Vector3 GetMoveBack();
	bool GetIsAttackFin() { return isAttackFin; };
	Vector3 GetDodgeMoveVec() { return dodgeMoveVec; };
	void MpUpdate(float mp);

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) {wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

	int EffTimer = 0;
	int isEffFlag = 0;
	
	int EffHealTimer = 0;
	int isEffHealFlag = 0;
	
	int EffHiHealTimer = 0;
	int isEffHiHealFlag = 0;

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Collision col;
	Audio* audio = nullptr;
	//プレイヤー
	Transform wtf;
	//待機
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	//回避
	FBXModel* fbxRollModel_ = nullptr;
	FBXObject3d* fbxRollObject3d_ = nullptr;
	//歩き
	FBXModel* fbxWalkModel_ = nullptr;
	FBXObject3d* fbxWalkObject3d_ = nullptr;
	//走る
	FBXModel* fbxDashModel_ = nullptr;
	FBXObject3d* fbxDashObject3d_ = nullptr;
	//弱攻撃
	FBXModel* fbxWeak1Model_ = nullptr;
	FBXObject3d* fbxWeak1Object3d_ = nullptr;
	FBXModel* fbxWeak2Model_ = nullptr;
	FBXObject3d* fbxWeak2Object3d_ = nullptr;
	FBXModel* fbxWeak3Model_ = nullptr;
	FBXObject3d* fbxWeak3Object3d_ = nullptr;
	FBXModel* fbxWeak4Model_ = nullptr;
	FBXObject3d* fbxWeak4Object3d_ = nullptr;
	//強攻撃
	FBXModel* fbxStrongModel_ = nullptr;
	FBXObject3d* fbxStrongObject3d_ = nullptr;
	//回復
	FBXModel* fbxHealModel_ = nullptr;
	FBXObject3d* fbxHealObject3d_ = nullptr;
	//メラ
	FBXModel* fbxMeraModel_ = nullptr;
	FBXObject3d* fbxMeraObject3d_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;
	float camRotaSpeed = PI / 180;
	float dashSpeed = 0.4f;
	const float dashMP = 2.0f / 60.0f;

	//ステータス
	const int defaultHp = 100;
	int hp;
	bool isLive = true;
	bool isAttackFin;
	bool nextAttack;

	//MP関連
	float mp;
	const float mpRegen = 0.5f / 60.0f;
	const float mpPuls = 5;
	//小回復
	const int heal = defaultHp * 0.2;
	const int healMp = 20;
	//大回復
	const int megaHeal = defaultHp * 0.6;
	const int megaHealMp = 60;
	//MP攻撃
	const int bulletMp = 40;

	//無敵時間
	bool isInvincible;
	const float invincibleLimit = 15;
	float invincibleTimer = invincibleLimit;

	//画面シェイク
	bool isCamShake;
	const int camShakeLimit = 20;
	int camShakeTimer = camShakeLimit;
	Vector3 camShakeVec;
	Vector3 moveBack;

	//弱攻撃
	Vector3 lightAttackLPos;
	Vector3 lightAttackWPos;
	const float lightMpPuls = 3;
	//何回めの連撃か
	int lightAttackCount;
	//一回の攻撃全体の時間
	float lightAttackLimit[4] = { 17,18,20,30 };
	float lightAttackTimer;
	//攻撃の当たり判定の有無
	bool isLightAttack;
	//判定が出始める時間
	float lightAttackPopTime[4] = { 14,13,15,24 };
	//判定が消える時間
	float lightAttackDeathTime[4] = { 13,12,14,22 };
	//次の連撃への入力受付開始時間
	float lightAttackInput[4] = { 20,20,20,0 };

	//強攻撃
	Vector3 heavyAttackLPos;
	Vector3 heavyAttackWPos;
	const float heavyMpPuls = 8;
	//何回めの連撃か
	int heavyAttackCount;
	//一回の攻撃全体の時間
	float heavyAttackLimit[2] = { 30,30 };
	float heavyAttackTimer;
	//攻撃の当たり判定の有無
	bool isHeavyAttack;
	//判定が出始める時間
	float heavyAttackPopTime[2] = { 15,25 };
	//判定が消える時間
	float heavyAttackDeathTime[2] = { 12,22 };
	//次の連撃への入力受付開始時間
	float heavyAttackInput[2] = { 15,0 };

	//回避
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;
	//回避後硬直時間
	const int dodgeStun = 1;
	Vector3 dodgeMoveVec;
	Vector3 dodgeMoveVecNomal;

	//OBJ関係
	//移動した時のplayerOBJを変える
	int objRotaTimer;
	//攻撃した時のplayerOBJを変える
	int attackFlag = 0;
	int objAttackTimer;

	//敵
	Transform* enemyPos_ = nullptr;

	//パーティクルクラスの初期化 
	//ダメージ
	std::unique_ptr<ParticleManager> particleManager;
	//回復
	std::unique_ptr<ParticleManager> particleHealManager;
	std::unique_ptr<ParticleManager> particleHiHealManager;
	//ワールド座標を入れる変数
	Vector3 worldPos;

	//音関係まとめ
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;


public:
	bool isActionStop;
	int isAction;
	//バディ
	Wolf* wolf_ = nullptr;
};