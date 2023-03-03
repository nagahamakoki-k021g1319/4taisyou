#pragma once

#include"EnemyBullet.h"

class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize();
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

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	//�G�̍U���n��

	////-----�_�K�[�t�@���l��------///
	std::list<std::unique_ptr<EnemyBullet>> enemyBulletObjs_;
	Model* enemyBulletModel_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int daggerTimer = 0;
	//////////////////////////////




};
