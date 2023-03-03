#include"Wolf.h"

Wolf::Wolf() {
}

Wolf::~Wolf() {
	delete bodyObj_;
}

void Wolf::Initialize() {
	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
	bodyObj_->wtf.position = { 3,4,0 };
	isAttack = false;
}


void Wolf::ShortRange() {
	isAttack = true;
	bodyObj_->wtf = *playerWtf;
	
	

}

void Wolf::ChargeShortRange() {

}

void Wolf::LongRange() {
	isAttack = false;
	bodyObj_->wtf.Initialize();
	bodyObj_->wtf.position = defaultPos;

}

void Wolf::ChargeLongRange() {


}

void Wolf::Move() {
	if (isAttack) {
		bodyObj_->Update();
	}
	else {
		bodyObj_->Update(playerWtf);

	}
}

void Wolf::Update() {
	Move();

}


void Wolf::Draw() {
	bodyObj_->Draw();
}


Vector3 Wolf::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//ì‡êœ
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