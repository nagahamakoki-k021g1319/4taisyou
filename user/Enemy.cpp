#include"Enemy.h"
#include"player.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete enemyObj_;
	delete enemyModel_;
	delete enemyBulletModel_;
	enemyBulletObjs_.clear();
	delete enemyCBModel_;
	enemyCBObjs_.clear();
}

void Enemy::Initialize(Input* input) {
	input_ = input;

	enemyModel_ = Model::LoadFromOBJ("as");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = { 0,3,5 };

	// ダガーファンネル
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	
	
	//順番に弾が飛んでくる攻撃
	enemyCBModel_ = Model::LoadFromOBJ("boll");
	

}

void Enemy::Update() {

	{//仮でプレイヤーとのやり取り
		player_->SetEnemyPos(&enemyObj_->wtf);
	}


	enemyObj_->Update();
	
	switch (phase_) {
	case Phase::Approach:
		enemyResetTimer = 0;
		enemyAttackTimer++;
		if (enemyAttackTimer >= 450) {
			phase_ = Phase::Leave;
		}
		if (enemyAttackTimer == 10) {
			for (int i = 0; i < 5; i++) {
				std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
				newBullet->Initialize(20 + 20 * i, enemyBulletModel_);
				newBullet->SetPos({ -6.0f + 3.0f * i,1.0f,8.0f });
				enemyBulletObjs_.push_back(std::move(newBullet));
			}
		}
		else if (enemyAttackTimer == 200) {
			for (int i = 0; i < 5; i++) {
				std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
				newBullet->Initialize(20 + 20 * i, enemyBulletModel_);
				newBullet->SetPos({ -6.0f + 3.0f * i,1.0f,8.0f });
				enemyBulletObjs_.push_back(std::move(newBullet));
			}
		}
		else if (enemyAttackTimer == 250) {
			for (int i = 0; i < 5; i++) {
				std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
				newBullet->Initialize(20 + 20 * i, enemyBulletModel_);
				newBullet->SetPos({ -6.0f + 3.0f * i,1.0f,8.0f });
				enemyBulletObjs_.push_back(std::move(newBullet));
			}
		}

		for (std::unique_ptr<EnemyBullet>& bullet : enemyBulletObjs_) {
			bullet->Update();

			{//仮でプレイヤーとのやり取り
				if (coll.CircleCollision(player_->GetPos(), bullet->GetPos(), 2.0f, 2.0f)) {
					player_->OnCollision();

				}
			}
		}

		break;
	case Phase::Leave:
		
		enemyAttackTimer2++;
		if (enemyAttackTimer2 >= 300) {
			phase_ = Phase::ReLeave;
		}
		if (enemyAttackTimer2 == 10) {
			for (int i = 0; i < 2; i++) {
				std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
				newCrystalBullet->Initialize(i, enemyCBModel_);
				newCrystalBullet->SetPos({ -2.0f + 4.0f * i,1.0f,15.0f });
				enemyCBObjs_.push_back(std::move(newCrystalBullet));
			}
			std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
			newCrystalBullet->Initialize(2, enemyCBModel_);
			newCrystalBullet->SetPos({ -3.0f,4.0f,15.0f });
			enemyCBObjs_.push_back(std::move(newCrystalBullet));

			std::unique_ptr<EnemyCrystalBullet> newCrystalBullet2 = std::make_unique<EnemyCrystalBullet>();
			newCrystalBullet2->Initialize(3, enemyCBModel_);
			newCrystalBullet2->SetPos({ 3.0f,4.0f,15.0f });
			enemyCBObjs_.push_back(std::move(newCrystalBullet2));

			std::unique_ptr<EnemyCrystalBullet> newCrystalBullet3 = std::make_unique<EnemyCrystalBullet>();
			newCrystalBullet3->Initialize(4, enemyCBModel_);
			newCrystalBullet3->SetPos({ 0.0f,6.0f,15.0f });
			enemyCBObjs_.push_back(std::move(newCrystalBullet3));
		}

		for (std::unique_ptr<EnemyCrystalBullet>& crystalBullet : enemyCBObjs_) {
			crystalBullet->Update();

		}

		break;
	case Phase::ReLeave:
		enemyResetTimer++;
		if (enemyResetTimer >= 50) {
			phase_ = Phase::Approach;
		}
		enemyAttackTimer = 0;
		enemyAttackTimer2 = 0;
		



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

