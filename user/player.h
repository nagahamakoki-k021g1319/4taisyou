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
	
	////���[���h���W���擾
	Vector3 GetWorldPosition();

	float GetHp() { return hp; };
	float GetUnion() { return specialMeter; };

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	//�v���C���[
	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;
	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	//�X�e�[�^�X
	const int defaultHp = 100;
	int hp;
	bool isLive = true;
	//�K�[�h
	Model* guardModel = nullptr;
	bool isGuard;
	const int guardMax = 100;
	int GuardDurability;
	//���
	Model* dodgeModel = nullptr;
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;
	//��U��

	//����
	Model* unionModel = nullptr;
	float specialMeter;
	bool isUnion;

	//�G
	Transform* enemyPos_ = nullptr;
public:
	//�o�f�B
	int selectBuddy;
	Wolf* wolf_ = nullptr;
	Gorilla* gorilla_ = nullptr;
};