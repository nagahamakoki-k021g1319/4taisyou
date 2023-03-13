#pragma once
#include"Object3d.h"
#include "Input.h"

#include"Wolf.h"

#include "Gorilla.h"

class Player {
	

public:
	Player();
	~Player();

	void Initialize(Input* input);
	
	void Update();
	void Move();
	void Rota();
	
	void Attack();

	void Draw();

	Vector3 bVelocity(Vector3& velocity,Transform& worldTransform);

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;

	//プレイヤー
	Camera* camera = nullptr;

	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	//バディ
	int selectBuddy;

	Wolf* wolf_ = nullptr;
	Gorilla* gorilla_ = nullptr;

public:
};