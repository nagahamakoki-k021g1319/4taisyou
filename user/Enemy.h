#pragma once

#include "EnemyBullet.h"
#include "EnemyCrystalBullet.h"
#include "Input.h"

class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(Input* input);
	void Update();
	void Draw();

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
		ReLeave,  //�ė��E����
	};

private:

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;

	Input* input_ = nullptr;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	//�G�̍U���n��

	////-----�_�K�[�t�@���l��------///
	std::list<std::unique_ptr<EnemyBullet>> enemyBulletObjs_;
	Model* enemyBulletModel_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int daggerTimer = 0;
	//////////////////////////////

	////-----���Ԃɒe�����ł���U��------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> enemyCBObjs_;
	Model* enemyCBModel_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int crystalTimer = 0;
	///////////////////////////////////


};
