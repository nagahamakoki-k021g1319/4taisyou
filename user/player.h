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
	
	void Update();
	void Move();
	void Rota();
	
	void Attack();

	void Draw();

	void OnCollision();

	void SetEnemyPos(Transform* enemyPos) { enemyPos_ = enemyPos; };
	Vector3 GetPos() { return bodyObj_->wtf.position; };

	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);
	
	////[hΐWπζΎ
	Vector3 GetWorldPosition();

	/// <summary>
	/// |WV
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;

	//γγ¬γ€γ€γΌ
	Camera* camera = nullptr;

	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;
	
	//γΉγγΌγΏγΉ
	const int defaultHp = 10;
	int hp;

	//γ¬γΌγ
	Model* guardModel = nullptr;
	bool isGuard;
	const int guardMax = 100;
	int GuardDurability;

	//ειΏ
	Model* dodgeModel = nullptr;
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;

	//εΌ±ζ»ζ

	

	//εδ½
	Model* unionModel = nullptr;
	float specialMeter;
	bool isUnion;

	//γγγ£
	int selectBuddy;
	Wolf* wolf_ = nullptr;
	Gorilla* gorilla_ = nullptr;
  
	//ζ΅
	Transform* enemyPos_ = nullptr;

public:


};