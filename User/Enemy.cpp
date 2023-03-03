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

	// ダガーファンネル
	for (int i = 0; i < 5; i++) {
		enemyBulletModel[i] = Model::LoadFromOBJ("boll");
	}
	for (int i = 0; i < 5; i++) {
		enemyBulletObj[i] = Object3d::Create();
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			enemyBulletObj[i]->SetModel(enemyBulletModel[j]);
		}
	}
	enemyBulletObj[0]->wtf.position = { -8,1,5 };
	enemyBulletObj[1]->wtf.position = { -4,1,5 };
	enemyBulletObj[2]->wtf.position = { 0,1,5 };
	enemyBulletObj[3]->wtf.position = { 4,1,5 };
	enemyBulletObj[4]->wtf.position = { 8,1,5 };


}

void Enemy::Update() {
	enemyObj_->Update();
	for (int i = 0; i < 5; i++) {
		enemyBulletObj[i]->Update();
	}
	switch (phase_) {
	case Phase::Approach:
		//enemyObj_->wtf.position.z -= 0.1;
		////規定の位置に到達したら離脱
		//if (enemyObj_->wtf.position.z < -5.0f) {
		//	phase_ = Phase::Leave;
		//}
		daggerTimer++;
		if (daggerTimer >= 50) {
			daggerTimer = 50;
			for (int i = 0; i < 5; i++) {
				enemyBulletObj[i]->wtf.position.z -= 1.0;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (enemyBulletObj[i]->wtf.position.z < -50.0f) {
				enemyBulletObj[i]->wtf.position.z - -50.0f;
				phase_ = Phase::Leave;
			}
		}







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

	switch (phase_) {
	case Phase::Approach:
		if (daggerTimer >= 1 && daggerTimer <= 10) {
			enemyBulletObj[0]->Draw();
		}
		else if (daggerTimer >= 11 && daggerTimer <= 20) {
			enemyBulletObj[0]->Draw();
			enemyBulletObj[1]->Draw();
		}
		else if (daggerTimer >= 21 && daggerTimer <= 30) {
			enemyBulletObj[0]->Draw();
			enemyBulletObj[1]->Draw();
			enemyBulletObj[2]->Draw();
		}
		else if (daggerTimer >= 31 && daggerTimer <= 40) {
			enemyBulletObj[0]->Draw();
			enemyBulletObj[1]->Draw();
			enemyBulletObj[2]->Draw();
			enemyBulletObj[3]->Draw();
		}
		else if (daggerTimer >= 41 && daggerTimer <= 50) {
			enemyBulletObj[0]->Draw();
			enemyBulletObj[1]->Draw();
			enemyBulletObj[2]->Draw();
			enemyBulletObj[3]->Draw();
			enemyBulletObj[4]->Draw();
		}
		break;
	case Phase::Leave:
		break;

	case Phase::ReLeave:
		break;
	}


}