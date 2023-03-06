#include "EnemyBullet.h"

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

void EnemyBullet::Update()
{
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
	obj_->Update();
}

void EnemyBullet::Draw(){
	if (isLive) {
		obj_->Draw();
	}
}
