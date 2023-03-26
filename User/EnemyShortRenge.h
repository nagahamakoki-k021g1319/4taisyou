#pragma once
#include "Object3d.h"
#include "Collision.h"

class EnemyShortRenge {
public:
	~EnemyShortRenge();

	///< summary>
	///������
	///</summary>
	void Initialize(Model* model_);

	///< summary>
	///�X�V
	///</summary>
	void ShortAttack();

	///< summary>
	///�X�V
	///</summary>
	void Update();

	///< summary>
	///�`��
	///</summary>
	void Draw();

	void OnCollision();

	void PlayerVec(Vector3 pos);

private:
	Collision* coll = nullptr;
	Object3d* obj_ = nullptr;

	Object3d* attackRenge = nullptr;
	
	Vector3 playerLen;
	Vector3 playerPos;

	float enemySpeed = 2.0f;

	bool attackHit = false;
	bool isAttack = false;
	int isAttackTime = 0;
public:
};