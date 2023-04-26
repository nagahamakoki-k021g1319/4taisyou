#pragma once
#include"Object3d.h"
#include "Input.h"

#include"Wolf.h"

#include "Gorilla.h"
#include "ParticleManager.h"
#include "Audio.h"


class Player {


public:
	Player();
	~Player();

	void Initialize(Input* input);
	void Reset();

	void Update(Transform* cam);
	void Rota();

	void Attack();

	void Draw();
	void EffUpdate();
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
	bool GetIsDodge() { return isDodge; };
	Vector3 GetCamShake() { return camShakeVec; };
	Vector3 GetMoveBack();
	bool GetIsAttackFin() { return isAttackFin; };

	Vector3 GetDodgeMoveVec() { return dodgeMoveVec; };

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

	int EffTimer = 0;
	int isEffFlag = 0;

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	Collision col;
	Audio* audio = nullptr;
	//プレイヤー
	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;
	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	//プレイヤーの移動
	Model* dash1Model_ = nullptr;
	Object3d* dash1Obj_ = nullptr;

	Model* dash2Model_ = nullptr;
	Object3d* dash2Obj_ = nullptr;

	Model* dash3Model_ = nullptr;
	Object3d* dash3Obj_ = nullptr;

	Model* dash4Model_ = nullptr;
	Object3d* dash4Obj_ = nullptr;

	//プレイヤーの移動
	Model* attack1Model_ = nullptr;
	Object3d* attack1Obj_ = nullptr;

	Model* attack2Model_ = nullptr;
	Object3d* attack2Obj_ = nullptr;

	Model* attack3Model_ = nullptr;
	Object3d* attack3Obj_ = nullptr;

	Model* attack4Model_ = nullptr;
	Object3d* attack4Obj_ = nullptr;
	//ステータス
	const int defaultHp = 100;
	int hp;
	bool isLive = true;
	bool isAttackFin;
	bool nextAttack;

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
	const int dodgeLimit = 20;
	int dodgeTimer;
	//回避後硬直時間
	const int dodgeStun = 8;
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
	std::unique_ptr<ParticleManager> particleManager;
	//ワールド座標を入れる変数
	Vector3 worldPos;
	
	
	//デバッグ用
	Model* debugModel_ = nullptr;
	Object3d* debugObj_ = nullptr;

	//音関係まとめ
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;


public:
	int isAction;
	//バディ
	Wolf* wolf_ = nullptr;
};