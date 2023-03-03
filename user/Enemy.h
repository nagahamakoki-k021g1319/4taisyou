#pragma once
#include"Object3d.h"


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
	Object3d* enemyBulletObj[5] = { 0 };
	Model* enemyBulletModel[5] = { 0 };
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int daggerTimer = 0;
	//////////////////////////////




};
