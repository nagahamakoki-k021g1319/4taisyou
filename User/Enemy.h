#pragma once
#include "DirectXCommon.h"
#include "EnemyBullet.h"
#include "EnemyCrystalBullet.h"
#include "EnemyShortRenge.h"
#include "EnemyExplosionAttack.h"
#include "Audio.h"

class Player;
#include "Collision.h"
#include "ParticleManager.h"

#include "FBXModel.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"
 
class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(DirectXCommon* dxCommon, Vector3 pos);
	void Update();
	void Draw();
	void FbxDraw();

	void SetPlayer(Player* player) { player_ = player; };

	void CreatDaggerBullet(int bulletNum);

	void CreatCrystalBullet();

	bool IsDead() const { if (isLive) { return false; } else { return true; } };

	void OnColision(int damage);


	void AttackDistance();

	void ResetHit2player() { isHitPlayer = false; };

	void AttackInterval();

	void playerDirection();

	void playerDirectionToCorrect();

	void EnemyProvisional();

	void EnemyAttackSter(float maxSterSize, float time, float rotationSpeed);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	//行動フェーズ
	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
		ReLeave,  //再離脱する
		ShortAttack,	//攻撃
		Explosion,		//獏発
	};

	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	DirectXCommon* dxCommon = nullptr;
	Player* player_ = nullptr;
	Collision coll;


	//待機
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	//横一列
	FBXModel* fbxBesideModel_ = nullptr;
	FBXObject3d* fbxBesideObject3d_ = nullptr;
	//ファンネル
	FBXModel* fbxFanneruModel_ = nullptr;
	FBXObject3d* fbxFanneruObject3d_ = nullptr;
	//移動
	FBXModel* fbxMoveModel_ = nullptr;
	FBXObject3d* fbxMoveObject3d_ = nullptr;
	//突進
	FBXModel* fbxRushModel_ = nullptr;
	FBXObject3d* fbxRushObject3d_ = nullptr;



	Audio* audio = nullptr;


	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;
	//攻撃のobj
	Object3d* enemyAttack1Obj_ = nullptr;
	Model* enemyAttack1Model_ = nullptr;
	Object3d* enemyAttack2Obj_ = nullptr;
	Model* enemyAttack2Model_ = nullptr;
	Object3d* enemyAttack3Obj_ = nullptr;
	Model* enemyAttack3Model_ = nullptr;
	Object3d* enemyAttack4Obj_ = nullptr;
	Model* enemyAttack4Model_ = nullptr;
	Object3d* enemyAttack5Obj_ = nullptr;
	Model* enemyAttack5Model_ = nullptr;
	Object3d* enemyAttack6Obj_ = nullptr;
	Model* enemyAttack6Model_ = nullptr;

	bool isLive = true;
	const int hpMax = 500;
	int hp = hpMax;

	EnemyBullet* enemyBullet = nullptr;

	//無敵時間
	bool isHitPlayer;
	bool isHitWolf;

	//フェーズ
	Phase phase_ = Phase::ReLeave;

	//敵の攻撃系統
	////-----ダガーファンネル------///
	std::list<std::unique_ptr<EnemyBullet>> daggerBullets_;
	Model* daggerBulletModel_ = nullptr;

	Model* homingBulletModel_ = nullptr;
	int enemyAttackTimer = 0;
	//////////////////////////////

	////-----順番に弾が飛んでくる攻撃------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> crystalBullets_;
	Model* enemyCBModel_ = nullptr;
	int enemyAttackTimer2 = 0;
	///////////////////////////////////

	////-----近接攻撃-----////
	EnemyShortRenge* shortRenge = nullptr;
	int enemyAttackTimer3 = 0;
	/////////////////////////

	////-----爆発攻撃-----////
	EnemyExplosionAttack* explosion = nullptr;
	int enemyAttackTimer4 = 0;
	/////////////////////////

	////-----距離で変わる攻撃-----////
	int enemyRandomAttack = 0;
	////////////////////////////

	////-----ランダムに攻撃方法を変える-----////
	int AttckNmb = 0;
	int randomAttck = 0;
	int numberOfAttacks = 0;
	////////////////////////////

	int attackInterval = 180;

	int enemyResetTimer = 0;

	//OBJを変更させる
	int enemyAttackRoteTimer = 0;

	//パーティクル
	std::unique_ptr<ParticleManager> DamageParticle;

	float playerBeforeAngle = 0;
	float playerAngle = 0;
	float playerAngleNmb = 0;
	float PI = 3.141592;
	float playerVecSpeed;
	float anglePI = 0;

	//敵の仮想の球座標
	Object3d* enemyProvisional[5];

	Vector3 playerVector = {};
	Vector2 playerBeforVec = {};
	float enemyDot = 0;

	//敵の攻撃前演出
	Object3d* enemyAttackOmen;
	Model* enemySter;
	bool isEnemyAttackOmen = false;
	float omenTime = 0;
	float omenSize = 0;
	float omenMaxTime = 20.0f;
	float omenMaxSize = 3.0f;
	float omenRotSpeed = 20 * (PI / 180);

public:
	bool isActionStop;
};