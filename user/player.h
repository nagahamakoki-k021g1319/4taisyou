#pragma once
#include"Object3d.h"
#include "Input.h"

#include"Wolf.h"

class Player {
	

public:
	Player();
	~Player();

	void Initialize(Input* input);
	
	void Update();
	void Move();
	void Rota();
	
	void Attack();

	void Draw();

	void OnCollision();

	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;

	//プレイヤー
	Camera* camera = nullptr;

	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;
	
	//ステータス
	const int defaultHp = 10;
	int hp;

	
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


public:


};