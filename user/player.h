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
	void Rota();
	
	void Attack();

	void Draw();

	void OnCollision();

	void SetEnemyPos(Transform* enemyPos) { enemyPos_ = enemyPos; };

	void LightAttack();
	void HeavyAttack();
	void Dodge();

	bool CheckAttack2Enemy(Vector3 enemyPos, float& damage);


	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);
	
	////���[���h���W���擾
	Vector3 GetWorldPosition();

	float GetHp() { return hp; };

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	Collision col;
	//�v���C���[
	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;
	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	//�X�e�[�^�X
	const int defaultHp = 100;
	int hp;
	bool isLive = true;

	//��U��
	//�a���̈ʒu
	Vector3 lightAttackCol;
	//����߂̘A����
	int lightAttackCount;
	//���̍U���S�̂̎���
	float lightAttackLimit[4] = { 60,60,60,60 };
	float lightAttackTimer;
	//�U���̓����蔻��̗L��
	bool isLightAttack;
	//���肪�o�n�߂鎞��
	float lightAttackPopTime[4] = { 40,40,40,40 };
	//���̘A���ւ̓��͎�t�J�n����
	float lightAttackInput[4] = { 30,10,30,30 };



	//���U��


	//���
	Model* dodgeModel = nullptr;
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;
	Vector3 dodgeMoveVec;

	//�G
	Transform* enemyPos_ = nullptr;


	//�f�o�b�O�p
	Model* debugModel_ = nullptr;
	Object3d* debugObj_ = nullptr;


public:
	int isAction;
	//�o�f�B
	Wolf* wolf_ = nullptr;
};