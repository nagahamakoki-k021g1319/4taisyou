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

//‹ß‹——£
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

//—­‚ß‹ß‹——£
void Wolf::ChargeShortRange() {
	float ShortSpeed = 2.0f;
	len = enemylen;
	enemylen *= ShortSpeed;
	
	continueAttack--;

	if (coll.CircleCollision(bodyObj_->wtf.position, enemyWtf->position, 2.0f, 2.0f)) {
		if (continueAttack >= 0) {
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
	}

}

//‰“‹——£
void Wolf::LongRange() {

	float ShortSpeed = 10.0f;
	
	
	continueAttack--;
	longTime++;
	if (longTime == 0) {
		len = enemylen;
		len *= ShortSpeed;
	}

	if (coll.CircleCollision(bodyObj_->wtf.position, enemyWtf->position, 3.0f, 3.0f)) {
		if (continueAttack >= 0) {
			Hit();
			continueAttack = 20;
		}
	}
	bodyObj_->wtf.position += len;

	if (longTime >= 60) {
		isAttack = false;
		bodyObj_->wtf.Initialize();
		bodyObj_->wtf.position = defaultPos;
		longTime = 0;
	}
}

//—­‚ß‰“‹——£
void Wolf::ChargeLongRange() {
	float ShortSpeed = 10.0f;

	if (longTime == 0) {
		len = enemylen;
		len *= ShortSpeed;
	}

	if (coll.CircleCollision(bodyObj_->wtf.position, enemyWtf->position, 3.0f, 3.0f)) {
		if (continueAttack >= 0) {
			Hit();
			continueAttack = 20;
		}
	}
	bodyObj_->wtf.position += len;

	if (longTime >= 20) {
		hitCount++;
		longTime = 0;
	}
	if (hitCount >= 3) {
		isAttack = false;
		bodyObj_->wtf.Initialize();
		bodyObj_->wtf.position = defaultPos;
		hitCount = 0;
	}

}

void Wolf::Attack(Transform* enemyTransform, int attackNmb)
{
	enemyWtf = enemyTransform;

	enemylen = enemyWtf->position - bodyObj_->wtf.position;
	enemylen.nomalize();

	if (isAttack == false) {
		{
			isAttack = true;
			attackNmb_ = attackNmb;
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

//Œü‚¢‚Ä‚é•ûŒü‚Évelocity‚ğ•ÏŠ·‚·‚é
Vector3 Wolf::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//“àÏ
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
