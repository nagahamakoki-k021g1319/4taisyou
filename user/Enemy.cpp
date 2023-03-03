#include"Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete enemyObj_;
	delete enemyModel_;
	delete enemyBulletModel_;
}

void Enemy::Initialize() {
	enemyModel_ = Model::LoadFromOBJ("as");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = { 0,3,5 };

	// ダガーファンネル
	enemyBulletModel_ = Model::LoadFromOBJ("as2");
	
	for (int i = 0; i < 5; i++) {
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(30 + 30 * i);
		newBullet->SetPos({ -6.0f + 3.0f * i,1.0f,8.0f });
		enemyBulletObjs_.push_back(std::move(newBullet));
	}
	




}

void Enemy::Update() {
	enemyObj_->Update();
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBulletObjs_){
		bullet->Update();

	}
	switch (phase_) {
	case Phase::Approach:
		//enemyObj_->wtf.position.z -= 0.1;
		////規定の位置に到達したら離脱
		//if (enemyObj_->wtf.position.z < -5.0f) {
		//	phase_ = Phase::Leave;
		//}
		


		break;
	case Phase::Leave:
		/*enemyObj_->wtf.position.x -= 0.1;
		if (enemyObj_->wtf.position.x < -6.0f) {
			phase_ = Phase::ReLeave;
		}*/
		break;
	case Phase::ReLeave:
		/*enemyObj_->wtf.position.x += 0.1;*/
		break;
	}
	


}


void Enemy::Draw() {
	enemyObj_->Draw();
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBulletObjs_) {
		bullet->Draw();
	}
	switch (phase_) {
	case Phase::Approach:
		
		break;
	case Phase::Leave:
		break;

	case Phase::ReLeave:
		break;
	}


}

