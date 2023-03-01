#pragma once
#include"Object3d.h"


class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize();
	void SetView(View* view) { this->view_ = view; };
	void Update();
	void Draw();

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
		ReLeave,  //�ė��E����
	};

private:
	View* view_ = nullptr;

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
};
