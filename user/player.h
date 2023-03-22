#pragma once
#include"Object3d.h"
#include "Input.h"

#include"Wolf.h"

#include "Gorilla.h"

class Player {
	

public:
	Player();
	~Player();

	void Initialize(Input* input);
	
	void Update(Transform* cam);
	void Rota();
	
	void Attack();

	void Draw();

	void OnCollision();

	void SetEnemyPos(Transform* enemyPos) { enemyPos_ = enemyPos; };

	void LightAttack();
	void HeavyAttack();
	void Dodge();

	bool CheckAttack2Enemy(Vector3 enemyPos, float& damage);


	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);
	
	////ワールド座標を取得
	Vector3 GetWorldPosition();

	float GetHp() { return hp; };

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	Collision col;
	//プレイヤー
	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;
	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	//ステータス
	const int defaultHp = 100;
	int hp;
	bool isLive = true;

	//弱攻撃
	//斬撃の位置
	Vector3 lightAttackCol;
	//何回めの連撃か
	int lightAttackCount;
	//一回の攻撃全体の時間
	float lightAttackLimit[4] = { 60,60,60,60 };
	float lightAttackTimer;
	//攻撃の当たり判定の有無
	bool isLightAttack;
	//判定が出始める時間
	float lightAttackPopTime[4] = { 40,40,40,40 };
	//次の連撃への入力受付開始時間
	float lightAttackInput[4] = { 30,10,30,30 };



	//強攻撃


	//回避
	Model* dodgeModel = nullptr;
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;
	Vector3 dodgeMoveVec;

	//敵
	Transform* enemyPos_ = nullptr;


	//デバッグ用
	Model* debugModel_ = nullptr;
	Object3d* debugObj_ = nullptr;


public:
	int isAction;
	//バディ
	Wolf* wolf_ = nullptr;
};