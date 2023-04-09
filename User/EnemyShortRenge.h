#pragma once
#include "Object3d.h"
#include "Collision.h"

class EnemyShortRenge {
public:
	~EnemyShortRenge();

	///< summary>
	///初期化
	///</summary>
	void Initialize(Model* model_);

	///< summary>
	///更新
	///</summary>
	void ShortAttack();

	///< summary>
	///更新
	///</summary>
	void Update(Vector3 playerPos,Object3d* enemy);

	///< summary>
	///描画
	///</summary>
	void Draw();

	void OnCollision();

	void PlayerVec();

	void ResetAttack();

private:
	Collision* coll = nullptr;
	Object3d* obj_ = nullptr;

	Object3d* attackRenge = nullptr;
	
	Vector3 playerLen;
	Vector3 playerPos;

	float enemySpeed = 1.0f;

	bool attackHit = false;
	bool isAttack = false;
	int isAttackTime = 10;
	int attackAccumulate = 20;
public:
};