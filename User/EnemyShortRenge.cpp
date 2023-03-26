#include "EnemyShortRenge.h"

EnemyShortRenge::~EnemyShortRenge()
{
}

void EnemyShortRenge::Initialize(Model* model_)
{
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	attackRenge = Object3d::Create();
	attackRenge->SetModel(model_);

	obj_->wtf.position = { 0.0f,0.0f,10.0f };
}

void EnemyShortRenge::ShortAttack()
{
	isAttackTime--;
	if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f)) {
		OnCollision();
	}
	else if (coll->CircleCollision(Vector3{ obj_->wtf.position.x + (playerLen.x * 2), obj_->wtf.position.y + playerLen.y + 2.0f, obj_->wtf.position.z + (playerLen.z * 2) }, playerPos, 1.0f, 1.0f)) {
		OnCollision();
	}
	if (isAttackTime <= 0) {
		isAttack == false;
	}
}


void EnemyShortRenge::Update()
{
	obj_->Update();
	attackRenge->Update();
	if (isAttack == false) {
		if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f)) {
			isAttackTime = 3;
			isAttack = true;
		}
		else if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f) == false) {
			obj_->wtf.position += playerLen;
		}
	}
	if (isAttack) {
		ShortAttack();
	}
	attackRenge->wtf.position = obj_->wtf.position + (playerLen * 2);
}

void EnemyShortRenge::Draw()
{
	obj_->Draw();
	if (isAttack) {
		if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f)==false) {
			attackRenge->Draw();
		}
		
	}

}

void EnemyShortRenge::OnCollision()
{

}

void EnemyShortRenge::PlayerVec(Vector3 pos)
{

	playerPos = pos;

	playerLen = playerPos - obj_->wtf.position;
	playerLen.nomalize();
	playerLen *= enemySpeed;

}
