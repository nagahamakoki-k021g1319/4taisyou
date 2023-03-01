#include"player.h"

Player::Player() {
}

Player::~Player() {
	delete bodyObj_;
}

void Player::Initialize(Input* input) {
	input_ = input;

	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
}


void Player::Rota() {
	Vector3 theta;

	if (input_->PushKey(DIK_E)) {
		theta.y += +rotaSpeed_;
	}
	else if (input_->PushKey(DIK_Q)) {
		theta.y += -rotaSpeed_;
	}

	bodyObj_->wtf.rotation += theta;
}

void Player::Move() {
	Vector3 velocity = { 0,0,0 };

	if (input_->PushKey(DIK_W)) {
		velocity.z = moveSpeed_;
	}else if (input_->PushKey(DIK_S)) {
		velocity.z = -moveSpeed_;
	}
	if (input_->PushKey(DIK_D)) {
		velocity.x = moveSpeed_;
	}else if (input_->PushKey(DIK_A)) {
		velocity.x = -moveSpeed_;
	}

	velocity = bVelocity(velocity, bodyObj_->wtf);

	bodyObj_->wtf.position += velocity;

}

void Player::Update() {
	Rota();
	Move();
	bodyObj_->Update();
}


void Player::Draw() {
	bodyObj_->Draw();
}

Vector3 Player::bVelocity(Vector3& velocity,Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//����
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}