#include"Enemy.h"
#include"player.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete enemyObj_;
	delete enemyModel_;
	delete enemyAttack1Obj_;
	delete enemyAttack1Model_;
	delete enemyAttack2Obj_;
	delete enemyAttack2Model_;
	delete enemyAttack3Obj_;
	delete enemyAttack3Model_;
	delete enemyAttack4Obj_;
	delete enemyAttack4Model_;
	delete enemyAttack5Obj_;
	delete enemyAttack5Model_;
	delete enemyAttack6Obj_;
	delete enemyAttack6Model_;
	delete daggerBulletModel_;
	daggerBullets_.clear();
	delete enemyCBModel_;
	crystalBullets_.clear();
	delete shortRenge;
	delete explosion;
}

void Enemy::Initialize(Vector3 pos) {
	enemyModel_ = Model::LoadFromOBJ("enemy");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = pos;

	enemyAttack1Model_ = Model::LoadFromOBJ("enemyattack1");
	enemyAttack1Obj_ = Object3d::Create();
	enemyAttack1Obj_->SetModel(enemyAttack1Model_);
	enemyAttack1Obj_->wtf.position = pos;
		
	enemyAttack2Model_ = Model::LoadFromOBJ("enemyattack2");
	enemyAttack2Obj_ = Object3d::Create();
	enemyAttack2Obj_->SetModel(enemyAttack2Model_);
	enemyAttack2Obj_->wtf.position = pos;
		
	enemyAttack3Model_ = Model::LoadFromOBJ("enemyattack3");
	enemyAttack3Obj_ = Object3d::Create();
	enemyAttack3Obj_->SetModel(enemyAttack3Model_);
	enemyAttack3Obj_->wtf.position = pos;
		
	enemyAttack4Model_ = Model::LoadFromOBJ("enemyattack4");
	enemyAttack4Obj_ = Object3d::Create();
	enemyAttack4Obj_->SetModel(enemyAttack4Model_);
	enemyAttack4Obj_->wtf.position = pos;
		 
	enemyAttack5Model_ = Model::LoadFromOBJ("enemyattack5");
	enemyAttack5Obj_ = Object3d::Create();
	enemyAttack5Obj_->SetModel(enemyAttack5Model_);
	enemyAttack5Obj_->wtf.position = pos;
		
	enemyAttack6Model_ = Model::LoadFromOBJ("enemyattack6");
	enemyAttack6Obj_ = Object3d::Create();
	enemyAttack6Obj_->SetModel(enemyAttack6Model_);
	enemyAttack6Obj_->wtf.position = pos;
	// ダガーファンネル
	daggerBulletModel_ = Model::LoadFromOBJ("boll");
	//順番に弾が飛んでくる攻撃
	enemyCBModel_ = Model::LoadFromOBJ("boll");


	shortRenge = new EnemyShortRenge();
	shortRenge->Initialize(enemyCBModel_);

	explosion = new EnemyExplosionAttack();
	explosion->Initialize(enemyCBModel_);


}

void Enemy::Update() {

	{//仮でプレイヤーとのやり取り
		player_->SetEnemyPos(&enemyObj_->wtf);
	}
	AttackDistance();

	enemyObj_->Update();

	enemyAttack1Obj_->Update();
	enemyAttack2Obj_->Update();
	enemyAttack3Obj_->Update();
	enemyAttack4Obj_->Update();
	enemyAttack5Obj_->Update();
	enemyAttack6Obj_->Update();


	//各種球更新
	//ダガーバレット
	daggerBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });
	for (std::unique_ptr<EnemyBullet>& bullet : daggerBullets_) {
		bullet->Update();
		if (bullet->isPop) {
			//仮でプレイヤーとのやり取り
			if (coll.CircleCollision(player_->GetWorldPosition(), bullet->GetPos(), 1.0f, 1.0f)) {
				player_->OnCollision();
				bullet->OnCollision();
			}
		}
	}
	//クリスタルバレット
	crystalBullets_.remove_if([](std::unique_ptr<EnemyCrystalBullet>& bullet) { return bullet->IsDead(); });
	for (std::unique_ptr<EnemyCrystalBullet>& bullet : crystalBullets_) {
		bullet->Update();
		{//仮でプレイヤーとのやり取り
			if (coll.CircleCollision(player_->GetWorldPosition(), bullet->GetWorldPosition(), 2.0f, 2.0f)) {
				player_->OnCollision();
				bullet->OnCollision();
			}
		}
	}
	if (shortRenge->GetCollision()) {
		player_->OnCollision();
		shortRenge->ResetAttackColl();
	}

	if (explosion->GetCollision()) {
		player_->OnCollision();
		explosion->ResetHit();
	}

	attackInterval--;

	switch (phase_) {
	case Phase::Approach:
		enemyResetTimer = 0;
		enemyAttackTimer++;

		//フェーズ移行
		if (enemyAttackTimer >= 450) {
			phase_ = Phase::ReLeave;
			numberOfAttacks++;
			AttackInterval();
		}


			//攻撃するまで移動
			if (enemyAttackTimer >= 0 && enemyAttackTimer <= 9) {
				enemyObj_->wtf.position.z += 0.1f;

				enemyAttack1Obj_->wtf.position.z += 0.1f;
				enemyAttack2Obj_->wtf.position.z += 0.1f;
				enemyAttack3Obj_->wtf.position.z += 0.1f;
				enemyAttack4Obj_->wtf.position.z += 0.1f;
				enemyAttack5Obj_->wtf.position.z += 0.1f;
				enemyAttack6Obj_->wtf.position.z += 0.1f;
			}
			//攻撃するまで移動
			if (enemyAttackTimer >= 150 && enemyAttackTimer <= 190) {
				enemyObj_->wtf.position.z += 0.05f;
				enemyObj_->wtf.position.x += 0.1f;

				enemyAttack1Obj_->wtf.position.z += 0.05f;
				enemyAttack1Obj_->wtf.position.x += 0.1f;

				enemyAttack2Obj_->wtf.position.z += 0.05f;
				enemyAttack2Obj_->wtf.position.x += 0.1f;

				enemyAttack3Obj_->wtf.position.z += 0.05f;
				enemyAttack3Obj_->wtf.position.x += 0.1f;

				enemyAttack4Obj_->wtf.position.z += 0.05f;
				enemyAttack4Obj_->wtf.position.x += 0.1f;

				enemyAttack5Obj_->wtf.position.z += 0.05f;
				enemyAttack5Obj_->wtf.position.x += 0.1f;

				enemyAttack6Obj_->wtf.position.z += 0.05f;
				enemyAttack6Obj_->wtf.position.x += 0.1f;
			}

		//ダガーファンネルを秒数で攻撃させる
		if (enemyAttackTimer == 10 || enemyAttackTimer == 200 || enemyAttackTimer == 250) {
			CreatDaggerBullet(5);
		}


		break;
	case Phase::Leave:

		enemyAttackTimer2++;
		if (enemyAttackTimer2 >= 300) {
			phase_ = Phase::ReLeave;
			numberOfAttacks++;
			AttackInterval();
		}


			//攻撃するまで移動
			if (enemyAttackTimer2 >= 0 && enemyAttackTimer2 <= 9) {
				enemyObj_->wtf.position.z -= 0.05f;
				enemyObj_->wtf.position.x -= 0.1f;

				enemyAttack1Obj_->wtf.position.z -= 0.05f;
				enemyAttack1Obj_->wtf.position.x -= 0.1f;

				enemyAttack2Obj_->wtf.position.z -= 0.05f;
				enemyAttack2Obj_->wtf.position.x -= 0.1f;

				enemyAttack3Obj_->wtf.position.z -= 0.05f;
				enemyAttack3Obj_->wtf.position.x -= 0.1f;
				
				enemyAttack4Obj_->wtf.position.z -= 0.05f;
				enemyAttack4Obj_->wtf.position.x -= 0.1f;
				
				enemyAttack5Obj_->wtf.position.z -= 0.05f;
				enemyAttack5Obj_->wtf.position.x -= 0.1f;
				
				enemyAttack6Obj_->wtf.position.z -= 0.05f;
				enemyAttack6Obj_->wtf.position.x -= 0.1f;

			}
			//順番に攻撃する弾を秒数で攻撃させる
			if (enemyAttackTimer2 == 10) {
				CreatCrystalBullet();
			}


		break;
	case Phase::ReLeave:
		//enemyResetTimer++;
		//if (enemyResetTimer >= 50) {
		//	phase_ = Phase::Random;
		//}
		if (attackInterval <= 0) {
			enemyAttackTimer = 0;
			enemyAttackTimer2 = 0;
			enemyAttackTimer3 = 0;
			enemyAttackTimer4 = 0;
			//近距離
			if (AttckNmb == 1) {
				if (randomAttck <= 5) {
					phase_ = Phase::Approach;
				}
				else if (1 <= randomAttck <= 10) {
					phase_ = Phase::Leave;
				}
				else if (9 <= randomAttck) {
					phase_ = Phase::ShortAttack;
				}
			}
			//中距離
			else if (AttckNmb == 2) {
				if (randomAttck <= 4) {
					phase_ = Phase::Leave;
				}
				else if (5 <= randomAttck <= 7) {
					phase_ = Phase::ShortAttack;
				}
				else if (8 <= randomAttck <= 9) {
					phase_ = Phase::Approach;
				}
				else if (randomAttck == 10) {
					phase_ = Phase::Explosion;
				}
			}
			//遠距離
			else if (AttckNmb == 3) {
				if (randomAttck <= 4) {
					phase_ = Phase::ShortAttack;
				}
				else if (5 <= randomAttck <= 6) {
					phase_ = Phase::Approach;
				}
				else if (7 <= randomAttck<=8) {
					phase_ = Phase::Leave;
				}
				else if (9 <= randomAttck) {
					phase_ = Phase::Explosion;
				}
			}
		break;
	case Phase::Explosion:
		enemyAttackTimer4++;
		explosion->Update(player_->GetWorldPosition(), enemyObj_);
		if (enemyAttackTimer4 >= 350) {
			explosion->ResetColl();
			numberOfAttacks++;
			AttackInterval();
			phase_ = Phase::ReLeave;
		}
		break;
		case Phase::ShortAttack:
			enemyAttackTimer3++;
			shortRenge->Update(player_->GetWorldPosition(), enemyObj_);
			shortRenge->Update(player_->GetWorldPosition(), enemyAttack1Obj_);
			shortRenge->Update(player_->GetWorldPosition(), enemyAttack2Obj_);
			shortRenge->Update(player_->GetWorldPosition(), enemyAttack3Obj_);
			shortRenge->Update(player_->GetWorldPosition(), enemyAttack4Obj_);
			shortRenge->Update(player_->GetWorldPosition(), enemyAttack5Obj_);
			shortRenge->Update(player_->GetWorldPosition(), enemyAttack6Obj_);
			if (enemyAttackTimer3 >= 120) {
				shortRenge->ResetAttack();
				numberOfAttacks++;
				AttackInterval();
				phase_ = Phase::ReLeave;
			}

			break;
      }
	}
	if (numberOfAttacks >= 3) {
		AttckNmb = 0;
		numberOfAttacks = 0;
	}

}

void Enemy::CreatDaggerBullet(int bulletNum) {
	for (int i = 0; i < bulletNum; i++) {
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(20 + 20 * i, daggerBulletModel_);
		newBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f + 2.0f * i,enemyObj_->wtf.position.y,enemyObj_->wtf.position.z + 8.0f });
		newBullet->SetScale({ 0.5f,0.5f, 0.5f });
		daggerBullets_.push_back(std::move(newBullet));
	}
}

void Enemy::CreatCrystalBullet() {
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
		newCrystalBullet->Initialize(i, enemyCBModel_);
		newCrystalBullet->SetPos({ enemyObj_->wtf.position.x - 2.0f + 4.0f * i,enemyObj_->wtf.position.y - 3.0f,enemyObj_->wtf.position.z + 15.0f });
		newCrystalBullet->Vec(player_->GetWorldPosition());
		crystalBullets_.push_back(std::move(newCrystalBullet));
	}

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet->Initialize(2, enemyCBModel_);
	newCrystalBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet));

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet2 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet2->Initialize(3, enemyCBModel_);
	newCrystalBullet2->SetPos({ enemyObj_->wtf.position.x + 4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet2->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet2));

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet3 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet3->Initialize(4, enemyCBModel_);
	newCrystalBullet3->SetPos({ enemyObj_->wtf.position.x,enemyObj_->wtf.position.y + 4.0f,enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet3->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet3));
}

void Enemy::Draw() {
	//敵のモーション管理
	enemyAttackRoteTimer++;
	if (enemyAttackRoteTimer >= 125 && enemyAttackRoteTimer <= 145) {
		enemyAttack1Obj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 146 && enemyAttackRoteTimer <= 165) {
		enemyObj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 166 && enemyAttackRoteTimer <= 215) {
		enemyAttack2Obj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 230 && enemyAttackRoteTimer <= 250) {
		enemyAttack3Obj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 251 && enemyAttackRoteTimer <= 270) {
		enemyObj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 271 && enemyAttackRoteTimer <= 310) {
		enemyAttack4Obj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 330 && enemyAttackRoteTimer <= 340) {
		enemyAttack5Obj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 341 && enemyAttackRoteTimer <= 360) {
		enemyAttack6Obj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 380 && enemyAttackRoteTimer <= 400) {
		enemyAttack5Obj_->Draw();
	}
	else if (enemyAttackRoteTimer >= 401 && enemyAttackRoteTimer <= 420) {
		enemyAttack6Obj_->Draw();
	}
	else {
		enemyObj_->Draw();
	}
	if (enemyAttackRoteTimer >= 421) {
		enemyAttackRoteTimer = 0;
	}
	for (std::unique_ptr<EnemyBullet>& bullet : daggerBullets_) {
		bullet->Draw();
	}

	for (std::unique_ptr<EnemyCrystalBullet>& bullet : crystalBullets_) {
		bullet->Draw();
	}

	switch (phase_) {
	case Phase::Approach:

		break;
	case Phase::Leave:

		break;

	case Phase::ReLeave:
		break;
	case Phase::ShortAttack:
		shortRenge->Draw();
		break;
	case Phase::Explosion:
		explosion->Draw();
		break;
	}


}

void Enemy::AttackInterval()
{
	attackInterval = 250;

}

Vector3 Enemy::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分
	worldPos.x = enemyObj_->wtf.position.x;
	worldPos.y = enemyObj_->wtf.position.y;
	worldPos.z = enemyObj_->wtf.position.z;


	return worldPos;
}

void Enemy::OnColision(int damage) {
	//player
	if (isHitPlayer == false) {
		hp -= damage;
		if (hp <= 0) {
			isLive = false;
		}
		isHitPlayer = true;
	}

}

void Enemy::AttackDistance()
{
	Vector3 EnemyLength = GetWorldPosition() - player_->GetWorldPosition();
	float len = EnemyLength.length();
	randomAttck = rand() % 10 + 1;
	if (AttckNmb == 0) {
		if (len <= 20) {
			AttckNmb = 1;
		}
		else if (20 < len < 60) {
			AttckNmb = 2;
		}
		else if (len >= 60) {
			AttckNmb = 3;
		}
		numberOfAttacks = 0;
	}
}
