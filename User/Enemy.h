#pragma once
#include "EnemyBullet.h"
#include "EnemyCrystalBullet.h"
#include "EnemyShortRenge.h"
#include "EnemyExplosionAttack.h"

class Player;
#include "Collision.h"
#include "ParticleManager.h"

class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(Vector3 pos);
	void Update();
	void Draw();

	void SetPlayer(Player* player) { player_ = player; };

	void CreatDaggerBullet(int bulletNum);

	void CreatCrystalBullet();

	bool IsDead() const { if (isLive) { return false; } else { return true; } };

	void OnColision(int damage);


	void AttackDistance();

	void ResetHit2player() { isHitPlayer = false; };

	void AttackInterval();

	void playerDirection();

	void playerDirectionToCorrect();

	void EnemyProvisional();

	void EnemyAttackSter(float maxSterSize, float time, float rotationSpeed);

	////���[���h���W���擾
	Vector3 GetWorldPosition();

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
		ReLeave,  //�ė��E����
		ShortAttack,	//�U��
		Explosion,		//�є�
	};

private:
	Player* player_ = nullptr;
	Collision coll;

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;
	//�U����obj
	Object3d* enemyAttack1Obj_ = nullptr;
	Model* enemyAttack1Model_ = nullptr;
	Object3d* enemyAttack2Obj_ = nullptr;
	Model* enemyAttack2Model_ = nullptr;
	Object3d* enemyAttack3Obj_ = nullptr;
	Model* enemyAttack3Model_ = nullptr;
	Object3d* enemyAttack4Obj_ = nullptr;
	Model* enemyAttack4Model_ = nullptr;
	Object3d* enemyAttack5Obj_ = nullptr;
	Model* enemyAttack5Model_ = nullptr;
	Object3d* enemyAttack6Obj_ = nullptr;
	Model* enemyAttack6Model_ = nullptr;

	bool isLive = true;
	const int hpMax = 30;
	int hp = hpMax;

	EnemyBullet* enemyBullet = nullptr;

	//���G����
	bool isHitPlayer;
	bool isHitWolf;

	//�t�F�[�Y
	Phase phase_ = Phase::ReLeave;

	//�G�̍U���n��
	////-----�_�K�[�t�@���l��------///
	std::list<std::unique_ptr<EnemyBullet>> daggerBullets_;
	Model* daggerBulletModel_ = nullptr;
	int enemyAttackTimer = 0;
	//////////////////////////////

	////-----���Ԃɒe�����ł���U��------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> crystalBullets_;
	Model* enemyCBModel_ = nullptr;
	int enemyAttackTimer2 = 0;
	///////////////////////////////////

	////-----�ߐڍU��-----////
	EnemyShortRenge* shortRenge = nullptr;
	int enemyAttackTimer3 = 0;
	/////////////////////////

	////-----�����U��-----////
	EnemyExplosionAttack* explosion = nullptr;
	int enemyAttackTimer4 = 0;
	/////////////////////////

	////-----�����ŕς��U��-----////
	int enemyRandomAttack = 0;
	////////////////////////////

	////-----�����_���ɍU�����@��ς���-----////
	int AttckNmb = 0;
	int randomAttck = 0;
	int numberOfAttacks = 0;
	////////////////////////////

	int attackInterval = 180;

	int enemyResetTimer = 0;

	//OBJ��ύX������
	int enemyAttackRoteTimer = 0;

	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> DamageParticle;

	float playerBeforeAngle = 0;
	float playerAngle = 0;
	float playerAngleNmb = 0;
	float PI = 3.141592;
	float playerVecSpeed;
	float anglePI = 0;

	//�G�̉��z�̋����W
	Object3d* enemyProvisional[5];

	Vector3 playerVector = {};
	Vector2 playerBeforVec = {};
	float enemyDot = 0;

	//�G�̍U���O���o
	Object3d* enemyAttackOmen;
	Model* enemySter;
	bool isEnemyAttackOmen = false;
	float omenTime = 0;
	float omenSize = 0;
	float omenMaxTime = 20.0f;
	float omenMaxSize = 3.0f;
	float omenRotSpeed = 20 * (PI / 180);

public:
	bool isActionStop;
};
