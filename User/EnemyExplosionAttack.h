#pragma once
#include "Object3d.h"
#include "Collision.h"

class EnemyExplosionAttack
{
public:
	EnemyExplosionAttack();
	~EnemyExplosionAttack();

	void Initialize(Model* model_);

	void Update(Vector3 PlayerPos, Object3d* enemy);

	void Draw();

	void Explosion();

	void OnCollision();

	void PlayerVec();

	void ResetColl();

	bool GetCollision();

	void ResetHit();

private:
	Collision* coll = nullptr;
	Object3d* obj_ = nullptr;

	Object3d* earthExplosion[10] = { nullptr };

	Vector3 playerLen;
	Vector3 playerPos;

	float collRand = 1.0f;
	float enemySpeed = 0.5f;
	int rengeTimer = 0;
	int explosionNmb = 0;
	bool attackHits = false;
	
	bool attackHit[10] = { false };
	bool isAttack[10] = { false };
	int isAttackTime = 10;
	int attackAccumulate = 50;
	bool hitAttck = false;
	bool hitOne = false;
};
