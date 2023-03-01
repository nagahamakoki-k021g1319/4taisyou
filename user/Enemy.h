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

	//行動フェーズ
	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
		ReLeave,  //再離脱する
	};

private:
	View* view_ = nullptr;

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;

	//フェーズ
	Phase phase_ = Phase::Approach;
};
