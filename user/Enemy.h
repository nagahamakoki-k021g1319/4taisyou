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

private:
	View* view_ = nullptr;

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;


};
