#include "EnemyShortRenge.h"

EnemyShortRenge::~EnemyShortRenge()
{
	delete attackRenge;
}

void EnemyShortRenge::Initialize(FBXObject3d* obj)
{
	obj_ = obj;

	attackRenge = obj;
	attackRenge->wtf.scale = { 2.0f,2.0f,2.0f };

	obj_->wtf.position = { 0.0f,0.0f,10.0f };
}

void EnemyShortRenge::ShortAttack()
{
	attackAccumulate--;

	if (attackAccumulate <= 0) {
		if (hitAttck == false) {
			isAttackTime--;
			OnCollision();
		}
	}
}


void EnemyShortRenge::Update(Vector3 PlayerPos, FBXObject3d* enemy, Object3d* obj2)
{
	obj2_ = obj2;
	obj_ = enemy;
	playerPos = PlayerPos;
	if (hitOne == false) {
		if (isAttack == false) {
			PlayerVec();
			if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f)) {
				isAttackTime = 3;
				isAttack = true;
			}
			else if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 1.0f, 1.0f) == false) {
				obj_->wtf.position += playerLen;
				obj2_->wtf.position += playerLen;
			}
		}
		if (isAttack) {
			ShortAttack();
		}
	}
	attackRenge->wtf.position = obj_->wtf.position + (playerLen * 2);
	obj_->Update();
	obj2_->Update();
	attackRenge->Update();
	enemy = obj_;
	obj2 = obj2_;
}

void EnemyShortRenge::Draw(ID3D12GraphicsCommandList* command)
{

	obj_->Draw(command);

}

void EnemyShortRenge::OnCollision()
{


	if (isAttack == true) {

		if (coll->CircleCollision(obj_->wtf.position + (playerLen * 2), playerPos, 2.0f, 2.0f)) {
			hitAttck = true;
			hitOne = true;
		}
		else if (coll->CircleCollision(Vector3{ obj_->wtf.position.x + (playerLen.x * 2), obj_->wtf.position.y + playerLen.y + 2.0f, obj_->wtf.position.z + (playerLen.z * 2) }, playerPos, 2.0f, 2.0f)) {
			hitAttck = true;
			hitOne = true;
		}
	}

}

void EnemyShortRenge::PlayerVec()
{



	playerLen = playerPos - obj_->wtf.position;
	playerLen.nomalize();
	playerLen *= enemySpeed;

}

void EnemyShortRenge::ResetAttack()
{
	isAttack = false;
	attackAccumulate = 50;
	isAttackTime = 10;
	hitAttck = false;
	hitOne = false;
}

bool EnemyShortRenge::GetCollision()
{
	return hitAttck;
}

void EnemyShortRenge::ResetAttackColl()
{
	hitAttck = false;
}