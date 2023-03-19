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
	Vector3 GetPos() { return bodyObj_->wtf.position; };

	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);
	
	////ƒ[ƒ‹ƒhÀ•W‚ğæ“¾
	Vector3 GetWorldPosition();

	/// <summary>
	/// ƒ|ƒWƒVƒ‡ƒ“
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;

	//ãƒ—ãƒ¬ã‚¤ãƒ¤ãƒ¼

	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;
	
	//ã‚¹ãƒ†ãƒ¼ã‚¿ã‚¹
	const int defaultHp = 10;
	int hp;

	//ã‚¬ãƒ¼ãƒ‰
	Model* guardModel = nullptr;
	bool isGuard;
	const int guardMax = 100;
	int GuardDurability;

	//å›é¿
	Model* dodgeModel = nullptr;
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;

	//å¼±æ”»æ’ƒ

	

	//åˆä½“
	Model* unionModel = nullptr;
	float specialMeter;
	bool isUnion;

	//ãƒãƒ‡ã‚£
	int selectBuddy;
	Wolf* wolf_ = nullptr;
	Gorilla* gorilla_ = nullptr;
  
	//æ•µ
	Transform* enemyPos_ = nullptr;

public:


};