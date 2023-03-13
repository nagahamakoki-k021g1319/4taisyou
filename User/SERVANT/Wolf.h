#pragma once
#include"Object3d.h"
#include "Input.h"
#include "Collision.h"

class Wolf {


public:
	Wolf();
	~Wolf();

	void Initialize();

	void Move();
	void Update();

	//í èÌçUåÇ
	void ShortRange();
	void ChargeShortRange();
	void LongRange();
	void ChargeLongRange();

	void Attack(Transform* enemyTransform, int attackNmb);

	void Draw();

	void SetPlayerWtf(Transform* worldTransform) { playerWtf = worldTransform; };

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	void Hit();

private:
	const float PI = 3.141592;

	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;

	bool isAttack;
	int attackNmb_;

	Transform* playerWtf = nullptr;

	Transform* enemyWtf = nullptr;

	Vector3 defaultPos = { 3,2,0 };

	Vector3 enemylen;

	Collision coll;

	Vector3 len;

	int hitCount = 0;
	int continueAttack = 0;

	int longTime = 0;

	int coolTIme = 0;

public:
};