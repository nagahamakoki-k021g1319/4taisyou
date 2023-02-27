#pragma once
#include"Object3d.h"


class Player {
	

public:
	Player();

	~Player();

	void Initialize();
	void SetView(View* view) { this->view_ = view; };
	void Update();
	void Draw();
	
private:
	View* view_ = nullptr;

	Object3d* bodyObj_ = nullptr;
	Model* bodyModel_ = nullptr;


};