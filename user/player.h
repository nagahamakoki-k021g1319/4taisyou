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
	void Move();
	void Rota();
	
	void Attack();

	void Draw();

	void OnCollision();

	void SetEnemyPos(Transform* enemyPos) { enemyPos_ = enemyPos; };

	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);
	
	////ワールド座標を取得
	Vector3 GetWorldPosition();

	float GetHp() { return hp; };
	float GetUnion() { return specialMeter; };

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	//プレイヤー
	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;
	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	//ステータス
	const int defaultHp = 100;
	int hp;
	bool isLive = true;
	//ガード
	Model* guardModel = nullptr;
	bool isGuard;
	const int guardMax = 100;
	int GuardDurability;
	//回避
	Model* dodgeModel = nullptr;
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;
	//弱攻撃

	//合体
	Model* unionModel = nullptr;
	float specialMeter;
	bool isUnion;
	//バディ
	int selectBuddy;
	Wolf* wolf_ = nullptr;
	Gorilla* gorilla_ = nullptr;

	//敵
	Transform* enemyPos_ = nullptr;
public:
};