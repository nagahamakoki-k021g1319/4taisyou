#pragma once
#include "Object3d.h"
#include "Collision.h"

class EnemyExplosionAttack
{
public:
	EnemyExplosionAttack();
	~EnemyExplosionAttack();

	void Update();

	void Draw();

	void Explosion();

	void OnCollision();

	void PlayerVec();

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
};
