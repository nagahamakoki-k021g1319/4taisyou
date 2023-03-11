#include"Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete enemyObj_;
	delete enemyModel_;
	delete enemyBulletModel_;
	enemyBulletObjs_.clear();
	
}

void Enemy::Initialize(Input* input) {
	input_ = input;

	enemyModel_ = Model::LoadFromOBJ("as");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = { 0,3,5 };

	// É_ÉKÅ[ÉtÉ@ÉìÉlÉã
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	for (int i = 0; i < 5; i++) {
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(30 + 30 * i);
		newBullet->SetPos({ -6.0f + 3.0f * i,1.0f,8.0f });
		enemyBulletObjs_.push_back(std::move(newBullet));
	}
	
	//èáî‘Ç…íeÇ™îÚÇÒÇ≈Ç≠ÇÈçUåÇ
	enemyCBModel_ = Model::LoadFromOBJ("boll");
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
		newCrystalBullet->Initialize(i);
		newCrystalBullet->SetPos({  -2.0f + 4.0f * i,1.0f,15.0f });
		enemyCBObjs_.push_back(std::move(newCrystalBullet));
	}

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet->Initialize(2);
	newCrystalBullet->SetPos({ -3.0f,4.0f,15.0f });
	enemyCBObjs_.push_back(std::move(newCrystalBullet));
	
	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet2 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet2->Initialize(3);
	newCrystalBullet2->SetPos({ 3.0f,4.0f,15.0f });
	enemyCBObjs_.push_back(std::move(newCrystalBullet2));

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet3 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet3->Initialize(4);
	newCrystalBullet3->SetPos({ 0.0f,6.0f,15.0f });
	enemyCBObjs_.push_back(std::move(newCrystalBullet3));

}

void Enemy::Update() {
	enemyObj_->Update();
	
	switch (phase_) {
	case Phase::Approach:
		//enemyObj_->wtf.position.z -= 0.1;
		////ãKíËÇÃà íuÇ…ìûíBÇµÇΩÇÁó£íE
		//if (enemyObj_->wtf.position.z < -5.0f) {
		//	phase_ = Phase::Leave;
		//}

		if (input_->PushKey(DIK_Z)) {
			phase_ = Phase::Leave;
		}
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBulletObjs_) {
			bullet->Update();

		}

		break;
	case Phase::Leave:
		/*enemyObj_->wtf.position.x -= 0.1;
		if (enemyObj_->wtf.position.x < -6.0f) {
			phase_ = Phase::ReLeave;
		}*/
		for (std::unique_ptr<EnemyCrystalBullet>& crystalBullet : enemyCBObjs_) {
			crystalBullet->Update();

		}

		break;
	case Phase::ReLeave:
		/*enemyObj_->wtf.position.x += 0.1;*/
		break;
	}
	


}


void Enemy::Draw() {
	enemyObj_->Draw();

	switch (phase_) {
	case Phase::Approach:
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBulletObjs_) {
			bullet->Draw();
		}
		break;
	case Phase::Leave:
		for (std::unique_ptr<EnemyCrystalBullet>& crystalBullet : enemyCBObjs_) {
			crystalBullet->Draw();

		}

		break;

	case Phase::ReLeave:
		break;
	}


}

