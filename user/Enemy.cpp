#include"Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete enemyObj_;
}

void Enemy::Initialize() {
	enemyModel_ = Model::LoadFromOBJ("as");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = { 0,3,5 };

}

void Enemy::Update() {
	enemyObj_->Update();
	switch (phase_) {
	case Phase::Approach:
		enemyObj_->wtf.position.z -= 0.1;
		//�K��̈ʒu�ɓ��B�����痣�E
		if (enemyObj_->wtf.position.z < -5.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		enemyObj_->wtf.position.x -= 0.1;
		if (enemyObj_->wtf.position.x < -6.0f) {
			phase_ = Phase::ReLeave;
		}
		break;
	case Phase::ReLeave:
		enemyObj_->wtf.position.x += 0.1;
		break;
	}
	


}


void Enemy::Draw() {
	enemyObj_->Draw();
}