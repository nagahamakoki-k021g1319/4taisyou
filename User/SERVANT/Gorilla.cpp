#include"Gorilla.h"

Gorilla::Gorilla() {
}

Gorilla::~Gorilla() {
	delete bodyObj_;
	delete bodyModel_;
}

void Gorilla::Initialize() {
	bodyModel_ = Model::LoadFromOBJ("gorilla");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
	bodyObj_->wtf.position = defaultPos;
	isAttack = false;
}

//ί£
void Gorilla::ShortRange() {

	
}

//­ίί£
void Gorilla::ChargeShortRange() {

}

//£
void Gorilla::LongRange() {

	isAttack = true;

}

//­ί£
void Gorilla::ChargeLongRange() {


}

void Gorilla::Move() {
	if (isAttack =true) {
		bodyObj_->Update();
	}
	else {
		bodyObj_->Update(playerWtf);

	}
}

void Gorilla::Update() {
	Move();

}


void Gorilla::Draw() {
	bodyObj_->Draw();
}

//ό’ΔιϋόΙvelocityπΟ··ι
Vector3 Gorilla::bVelocity(Vector3& velocity, Transform& worldTransform)
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