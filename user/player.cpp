#include"player.h"

Player::Player() {
}

Player::~Player() {
	delete bodyObj_;
}

void Player::Initialize(Input* input) {
	input_ = input;
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	camera->SetEye({ 0.0f,3.0f,-8.0f });
	Object3d::SetCamera(camera);

	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
}


void Player::Rota() {
	Vector3 theta;
	Vector3 camTheta;

	if (input_->PushKey(DIK_D)) {
		theta.y = rotaSpeed_;
	}
	else if (input_->PushKey(DIK_A)) {
		theta.y = -rotaSpeed_;
	}

	bodyObj_->wtf.rotation += theta;

	if (input_->PushKey(DIK_W)) {
		camTheta.y = rotaSpeed_;
	}
	else if (input_->PushKey(DIK_S)) {
		camTheta.y = -rotaSpeed_;
	}

	camera->SetTarget(camera->GetTarget() + camTheta);
}

void Player::Move() {
	Vector3 velocity = { 0,0,0 };

	if (input_->PushKey(DIK_UPARROW)) {
		velocity.z = moveSpeed_;
	}else if (input_->PushKey(DIK_DOWNARROW)) {
		velocity.z = -moveSpeed_;
	}
	if (input_->PushKey(DIK_RIGHTARROW)) {
		velocity.x = moveSpeed_;
	}else if (input_->PushKey(DIK_LEFTARROW)) {
		velocity.x = -moveSpeed_;
	}

	velocity = bVelocity(velocity, bodyObj_->wtf);

	bodyObj_->wtf.position += velocity;
	camera->SetTarget(camera->GetTarget() + velocity);

}

void Player::Update() {
	Rota();
	Move();
	bodyObj_->UpdateMat();
	camera->Update(bodyObj_->wtf);
	bodyObj_->Update();
}


void Player::Draw() {
	bodyObj_->Draw();
}

Vector3 Player::bVelocity(Vector3& velocity,Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//ì‡êœ
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