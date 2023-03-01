#pragma once
#include"Object3d.h"


class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize();
	void Update();
	void Draw();

	//行動フェーズ
	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
		ReLeave,  //再離脱する
	};

private:

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;

	//フェーズ
	Phase phase_ = Phase::Approach;
};
