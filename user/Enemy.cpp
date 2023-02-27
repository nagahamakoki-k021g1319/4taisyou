#include"Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete view_;
	delete enemyModel_;
	delete enemyObj_;
}

void Enemy::Initialize() {
	view_ = new View();

	enemyModel_ = Model::LoadFromOBJ("as");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = { 0,5,0 };

}

void Enemy::Update() {
	enemyObj_->Update(view_);
}


void Enemy::Draw() {
	enemyObj_->Draw();
}