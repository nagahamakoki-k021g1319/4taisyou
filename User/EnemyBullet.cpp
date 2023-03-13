#include "EnemyBullet.h"

EnemyBullet::~EnemyBullet() {
	delete obj_;
	delete model_;
}


void EnemyBullet::Initialize(int timer)
{
	// ダガーファンネル
	model_ = Model::LoadFromOBJ("boll");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);


	daggerTimer = timer;
	isLive = false;
	shotTimer = 180;

	
}

void EnemyBullet::DaggerFAttack(){
	//表示まで
	daggerTimer--;
	if (daggerTimer < 0) {
		isLive = true;
	}

	shotTimer--;

	if (isLive) {
		if (shotTimer <= 0) {
			obj_->wtf.position.z -= 0.1;
		}
	}
	if (obj_->wtf.position.z <= -30) {
		isLive = false;
	}
}

void EnemyBullet::Update(){

	DaggerFAttack();

	obj_->Update();
	

}

void EnemyBullet::Draw(){
	if (isLive) {
		obj_->Draw();
	}
	
}
