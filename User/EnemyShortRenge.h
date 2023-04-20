#pragma once
#include "Object3d.h"
#include "Collision.h"

class EnemyShortRenge {
public:
	~EnemyShortRenge();

	///< summary>
	///
	///</summary>
	void Initialize(Model* model_);

	///< summary>
	///
	///</summary>
	void ShortAttack();

	///< summary>
	///
	///</summary>
	void Update(Vector3 playerPos, Object3d* enemy);

	///< summary>
	///
	///</summary>
	void Draw();

	void OnCollision();

	void PlayerVec();

	void ResetAttack();

	bool GetCollision();

	void ResetAttackColl();

private:
	Collision* coll = nullptr;
	Object3d* obj_ = nullptr;

	Object3d* attackRenge = nullptr;

	Vector3 playerLen;
	Vector3 playerPos;

	float enemySpeed = 0.5f;

	bool attackHit = false;
	bool isAttack = false;
	int isAttackTime = 10;
	int attackAccumulate = 50;
	bool hitAttck = false;
	bool hitOne = false;
public:
};