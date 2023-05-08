#include "EnemyExplosionAttack.h"

EnemyExplosionAttack::EnemyExplosionAttack()
{
}

EnemyExplosionAttack::~EnemyExplosionAttack()
{
	for (int i = 0; i < 10; i++)
	{
		delete earthExplosion[i];
	}
}

void EnemyExplosionAttack::Initialize(Model* model_)
{
	for (int i = 0; i < 10; i++) {
		earthExplosion[i] = Object3d::Create();
		earthExplosion[i]->SetModel(model_);
	}


}

void EnemyExplosionAttack::Update(Vector3 PlayerPos, Object3d* enemy)
{
	obj_ = enemy;
	playerPos = PlayerPos;
	PlayerVec();
	rengeTimer++;
	int Timer = rengeTimer % 30 + 1;
	if (Timer == 30) {
		if (rengeTimer <= 301) {
			explosionNmb++;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (attackHit[i] == false) {
			if (isAttack[i] == false) {
				earthExplosion[i]->wtf.position = { obj_->wtf.position + (playerLen * ((collRand * 7) * (i + 1))) };
				isAttack[i] = true;
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		earthExplosion[i]->Update();
	}
	OnCollision();
}

void EnemyExplosionAttack::Draw()
{
	for (int i = 0; i < explosionNmb; i++) {
		if (isAttack[i] == true) {
			earthExplosion[i]->Draw();
		}
	}
}

void EnemyExplosionAttack::Explosion()
{
}

void EnemyExplosionAttack::OnCollision()
{

	for (int i = 0; i < explosionNmb; i++) {
		if (coll->CircleCollision(playerPos, earthExplosion[i]->wtf.position, collRand, collRand)) {
			if (isAttack[i] == true) {
				if (attackHit[i] == false) {
					attackHit[i] = true;
					isAttack[i] = false;
					attackHits = true;
				}
			}
		}
	}
}

void EnemyExplosionAttack::PlayerVec()
{
	playerLen = playerPos - obj_->wtf.position;
	playerLen.nomalize();
}

void EnemyExplosionAttack::ResetColl()
{
	for (int i = 0; i < 10; i++) {
		attackHit[i] = false;
		isAttack[i] = false;
	}
	rengeTimer = 0;
	explosionNmb = 0;
	attackHits = false;
}

bool EnemyExplosionAttack::GetCollision()
{
	return attackHits;
}

void EnemyExplosionAttack::ResetHit()
{
	attackHits = false;
}
