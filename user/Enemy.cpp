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

	// �_�K�[�t�@���l��
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	//���Ԃɒe�����ł���U��
	enemyCBModel_ = Model::LoadFromOBJ("boll");
	

}

void Enemy::Update() {
	//���Ńv���C���[�Ɉʒu���n��
	player_->SetEnemyPos(&enemyObj_->wtf);

	enemyObj_->Update();
	
	if (input_->ButtonInput(RT)) {
		input_->ShakeController(1.0f, 10.0f);
	}
	if (input_->StickInput(L_LEFT)){
		input_->ShakeController(1.0f, 10.0f);
	}

	std::unique_ptr<Object3d> newEnemyObjs_ = std::make_unique<Object3d>();
	newEnemyObjs_->Initialize();
	newEnemyObjs_->SetModel(enemyModel_);
	newEnemyObjs_->wtf.position = { -3,3,10 };
	enemyListObjs_.push_back(std::move(newEnemyObjs_));
	enemyListObjs_.remove_if([](std::unique_ptr<Object3d>& newEnemyObjs_) { return newEnemyObjs_->IsDead(); });
	for (std::unique_ptr<Object3d>& newEnemyObjs_ : enemyListObjs_) {
		newEnemyObjs_->Update();
	}



	switch (phase_) {
	case Phase::Approach:
		enemyResetTimer = 0;
		enemyAttackTimer++;
		if (enemyAttackTimer >= 450) {
			phase_ = Phase::Leave;
		}


		//�U������܂ňړ�
		if (enemyAttackTimer >= 0 && enemyAttackTimer <=9) {
			enemyObj_->wtf.position.z += 0.1f;
		}
		//�U������܂ňړ�
		if (enemyAttackTimer >= 150 && enemyAttackTimer <= 190) {
			enemyObj_->wtf.position.z += 0.05f;
			enemyObj_->wtf.position.x += 0.1f;
		}

		//�_�K�[�t�@���l����b���ōU��������
		if (enemyAttackTimer == 10) {
			for (int i = 0; i < 5; i++) {
				std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
				newBullet->Initialize(20 + 20 * i, enemyBulletModel_);
				newBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f + 2.0f * i,enemyObj_->wtf.position.y - 2.0f,enemyObj_->wtf.position.z + 8.0f });
				newBullet->SetScale({ 0.5f,0.5f, 0.5f});
				enemyBulletObjs_.push_back(std::move(newBullet));
				enemyBulletObjs_.remove_if([](std::unique_ptr<EnemyBullet>& newBullet) { return newBullet->IsDead(); });
			}
		}
		else if (enemyAttackTimer == 200) {
			for (int i = 0; i < 5; i++) {
				std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
				newBullet->Initialize(20 + 20 * i, enemyBulletModel_);
				newBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f + 2.0f * i,enemyObj_->wtf.position.y - 2.0f,enemyObj_->wtf.position.z + 8.0f });
				newBullet->SetScale({ 0.5f,0.5f, 0.5f });
				enemyBulletObjs_.push_back(std::move(newBullet));
				enemyBulletObjs_.remove_if([](std::unique_ptr<EnemyBullet>& newBullet) { return newBullet->IsDead(); });
			}
		}
		else if (enemyAttackTimer == 250) {
			for (int i = 0; i < 5; i++) {
				std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
				newBullet->Initialize(20 + 20 * i, enemyBulletModel_);
				newBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f + 2.0f * i,enemyObj_->wtf.position.y - 2.0f,enemyObj_->wtf.position.z + 8.0f });
				newBullet->SetScale({ 0.5f,0.5f, 0.5f });
				enemyBulletObjs_.push_back(std::move(newBullet));
				enemyBulletObjs_.remove_if([](std::unique_ptr<EnemyBullet>& newBullet) { return newBullet->IsDead(); });
			}
		}

		for (std::unique_ptr<EnemyBullet>& bullet : enemyBulletObjs_) {
			bullet->Update();

		}

		break;
	case Phase::Leave:
		
		enemyAttackTimer2++;
		if (enemyAttackTimer2 >= 300) {
			phase_ = Phase::ReLeave;
		}
		
		//�U������܂ňړ�
		if (enemyAttackTimer2 >= 0 && enemyAttackTimer2 <= 9) {
			enemyObj_->wtf.position.z -= 0.05f;
			enemyObj_->wtf.position.x -= 0.1f;
		}
		//���ԂɍU������e��b���ōU��������
		if (enemyAttackTimer2 == 10) {
			for (int i = 0; i < 2; i++) {
				std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
				newCrystalBullet->Initialize(i, enemyCBModel_);
				newCrystalBullet->SetPos({ enemyObj_->wtf.position.x -2.0f + 4.0f * i,enemyObj_->wtf.position.y - 3.0f,enemyObj_->wtf.position.z +15.0f });
				newCrystalBullet->Vec(player_->GetWorldPosition());
				enemyCBObjs_.push_back(std::move(newCrystalBullet));
			}
			std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
			newCrystalBullet->Initialize(2, enemyCBModel_);
			newCrystalBullet->SetPos({ enemyObj_->wtf.position.x -4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
			newCrystalBullet->Vec(player_->GetWorldPosition());
			enemyCBObjs_.push_back(std::move(newCrystalBullet));

			std::unique_ptr<EnemyCrystalBullet> newCrystalBullet2 = std::make_unique<EnemyCrystalBullet>();
			newCrystalBullet2->Initialize(3, enemyCBModel_);
			newCrystalBullet2->SetPos({ enemyObj_->wtf.position.x + 4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
			newCrystalBullet2->Vec(player_->GetWorldPosition());
			enemyCBObjs_.push_back(std::move(newCrystalBullet2));

			std::unique_ptr<EnemyCrystalBullet> newCrystalBullet3 = std::make_unique<EnemyCrystalBullet>();
			newCrystalBullet3->Initialize(4, enemyCBModel_);
			newCrystalBullet3->SetPos({ enemyObj_->wtf.position.x,enemyObj_->wtf.position.y + 4.0f,enemyObj_->wtf.position.z + 15.0f });
			newCrystalBullet3->Vec(player_->GetWorldPosition());
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
	for (std::unique_ptr<Object3d>& newEnemyObjs_ : enemyListObjs_) {
		newEnemyObjs_->Draw();

	}

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

