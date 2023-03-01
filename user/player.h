#pragma once
#include"Object3d.h"
#include "Input.h"


class Player {
	

public:
	Player();
	~Player();

	void Initialize(Input* input);
	
	void Update();
	void Move();
	void Rota();
	
	void Draw();

	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);

private:
	const float PI = 3.141592;

	Input* input_ = nullptr;

	Object3d* bodyObj_ = nullptr;
	Model* bodyModel_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

};