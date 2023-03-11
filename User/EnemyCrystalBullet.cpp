#include "EnemyCrystalBullet.h"

EnemyCrystalBullet::~EnemyCrystalBullet() {
	delete crystalObj_;
	delete crystalModel_;
}

void EnemyCrystalBullet::Initialize(int num) {
	// ダガーファンネル
	crystalModel_ = Model::LoadFromOBJ("boll");
	crystalObj_ = Object3d::Create();
	crystalObj_->SetModel(crystalModel_);


	isLive = true;
	bulletNum = num;
	shotTimer = 180;
}

void EnemyCrystalBullet::CrystalBAttack() {
	
	shotTimer--;
	if (isLive) {
		if (bulletNum == 0 && shotTimer <= 150) {
			crystalObj_->wtf.position.x += 0.03;
			crystalObj_->wtf.position.y += 0.02;
			crystalObj_->wtf.position.z -= 0.4;
		}
		else if (bulletNum == 1 && shotTimer <= 120) {
			crystalObj_->wtf.position.x -= 0.03;
			crystalObj_->wtf.position.y += 0.02;
			crystalObj_->wtf.position.z -= 0.4;
		}
		else if (bulletNum == 2 && shotTimer <= 60) {
			crystalObj_->wtf.position.x += 0.05;
			crystalObj_->wtf.position.z -= 0.4;
		}
		else if (bulletNum == 3 && shotTimer <= 90) {
			crystalObj_->wtf.position.x -= 0.05;
			crystalObj_->wtf.position.z -= 0.4;
		}
		else if (bulletNum == 4 && shotTimer <= 30) {
			crystalObj_->wtf.position.y -= 0.05;
			crystalObj_->wtf.position.z -= 0.4;
		}
	}
	if (crystalObj_->wtf.position.z <= -30) {
		isLive = false;
	}
}

void EnemyCrystalBullet::Update(){
	CrystalBAttack();
	crystalObj_->Update();

}

void EnemyCrystalBullet::Draw(){
	if (isLive) {
		crystalObj_->Draw();
	}
}
