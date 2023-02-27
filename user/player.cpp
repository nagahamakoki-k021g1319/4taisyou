#include"player.h"

Player::Player() {
}

Player::~Player() {
	delete view_;
	delete bodyModel_;
	delete bodyObj_;
}

void Player::Initialize() {
	view_ = new View();

	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
}

void Player::Update() {

	bodyObj_->Update(view_);
}


void Player::Draw() {
	bodyObj_->Draw();
}