#include "EnemyCrystalBullet.h"

EnemyCrystalBullet::~EnemyCrystalBullet() {
	delete crystalObj_;
	delete crystalModel_;
}

void EnemyCrystalBullet::Initialize(int num) {
	//‡”Ô‚É”ò‚ñ‚Å‚­‚éUŒ‚
	crystalModel_ = Model::LoadFromOBJ("boll");
	crystalObj_->SetModel(crystalModel_);
	crystalObj_ = Object3d::Create();

	isLive = true;
	bulletNum = num;

}

void EnemyCrystalBullet::CrystalBAttack() {
	if (isLive) {
		crystalObj_->wtf.position.z -= 0.1;
		if (bulletNum == 2) {
			crystalObj_->wtf.position.y -= 0.1;
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
