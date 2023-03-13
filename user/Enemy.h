#pragma once

#include "EnemyBullet.h"
#include "EnemyCrystalBullet.h"
#include "Input.h"

class Player;

class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(Input* input);
	void Update();
	void Draw();

	void SetPlayer(Player* player) { player_ = player; };

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
		ReLeave,  //�ė��E����
	};

private:
	Player* player_ = nullptr;

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;

	Input* input_ = nullptr;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	//�G�̍U���n��

	////-----�_�K�[�t�@���l��------///
	std::list<std::unique_ptr<EnemyBullet>> enemyBulletObjs_;
	Model* enemyBulletModel_ = nullptr;
	int enemyAttackTimer = 0;
	//////////////////////////////

	////-----���Ԃɒe�����ł���U��------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> enemyCBObjs_;
	Model* enemyCBModel_ = nullptr;

	int enemyAttackTimer2 = 0;
	///////////////////////////////////

	int enemyResetTimer = 0;


};
