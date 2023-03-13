#include"Wolf.h"

Wolf::Wolf() {
}

Wolf::~Wolf() {
	delete bodyObj_;
	delete bodyModel_;
}

void Wolf::Initialize() {
	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
	bodyObj_->wtf.position = defaultPos;
	isAttack = false;
}

//ί£
void Wolf::ShortRange() {

	float ShortSpeed = 2.0f;
	len = enemylen;
	enemylen *= ShortSpeed;


	if (coll.CircleCollision(bodyObj_->wtf.position + len, enemyWtf->position, 2.0f, 2.0f)) {
		Hit();
		isAttack = false;
		bodyObj_->wtf.Initialize();
		bodyObj_->wtf.position = defaultPos;
	}
	else
	{
		bodyObj_->wtf.position += enemylen;
	}
}

//­ίί£
void Wolf::ChargeShortRange() {
	float ShortSpeed = 2.0f;
	len = enemylen;
	enemylen *= ShortSpeed;

	continueAttack--;

	if (coll.CircleCollision(bodyObj_->wtf.position, enemyWtf->position, 2.0f, 2.0f)) {
		if (continueAttack <= 0) {
			Hit();
			continueAttack = 20;
			hitCount++;
		}

	}
	else
	{
		bodyObj_->wtf.position += enemylen;
	}
	if (hitCount >= 3) {
		isAttack = false;
		bodyObj_->wtf.Initialize();
		bodyObj_->wtf.position = defaultPos;
		hitCount = 0;
		continueAttack = 0;
	}

}

//£
void Wolf::LongRange() {

	float ShortSpeed = 5.0f;

	if (longTime == 0) {
		len = enemylen;
		len *= ShortSpeed;
	}

	continueAttack--;
	longTime++;


	if (coll.CircleCollision(bodyObj_->wtf.position, enemyWtf->position, 3.0f, 3.0f)) {
		if (continueAttack <= 0) {
			Hit();
			continueAttack = 20;
		}
	}
	bodyObj_->wtf.position += len;

	if (longTime >= 10) {
		isAttack = false;
		bodyObj_->wtf.Initialize();
		bodyObj_->wtf.position = defaultPos;
		hitCount = 0;
		continueAttack = 0;
		longTime = 0;
	}
}

//­ί£
void Wolf::ChargeLongRange() {
	float ShortSpeed = 5.0f;

	if (longTime == 0) {
		len = enemylen;
		len *= ShortSpeed;
	}
	continueAttack--;
	longTime++;
	if (coll.CircleCollision(bodyObj_->wtf.position, enemyWtf->position, 3.0f, 3.0f)) {
		if (continueAttack <= 0) {
			Hit();
			continueAttack = 5;
			hitCount++;
			longTime = -10;
		}
	}
	bodyObj_->wtf.position += len;

	if (hitCount >= 2) {
		isAttack = false;
		bodyObj_->wtf.Initialize();
		bodyObj_->wtf.position = defaultPos;
		hitCount = 0;
		continueAttack = 0;
		longTime = 0;
	}

}

void Wolf::Attack(Transform* enemyTransform, int attackNmb)
{
	enemyWtf = enemyTransform;

	enemylen = enemyWtf->position - bodyObj_->wtf.position;
	enemylen.nomalize();
	coolTIme--;
	if (coolTIme <= 0) {
		if (isAttack == false) {
			{
				isAttack = true;
				attackNmb_ = attackNmb;
				coolTIme = 10;
			}
		}
	}
}

void Wolf::Move() {
	//if (isAttack) {
	bodyObj_->Update();
	//}
	//else {
	//	bodyObj_->Update(playerWtf);
	//}
}

void Wolf::Update() {
	if (isAttack == true) {
		if (attackNmb_ == 1) {
			ShortRange();
		}
		else if (attackNmb_ == 2) {
			ChargeShortRange();
		}
		else if (attackNmb_ == 3) {
			LongRange();
		}
		else if (attackNmb_ == 4) {
			ChargeLongRange();
		}
	}
	Move();
}


void Wolf::Draw() {
	bodyObj_->Draw();
}

//ό’ΔιϋόΙvelocityπΟ··ι
Vector3 Wolf::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//ΰΟ
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}

void Wolf::Hit()
{

}
