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

//近距離
void Wolf::ShortRange() {
	
	{//攻撃状態になる時必要
		isAttack = true;
		bodyObj_->wtf = *playerWtf;
	}
	

}

//溜め近距離
void Wolf::ChargeShortRange() {

}

//遠距離
void Wolf::LongRange() {

	{//攻撃が終わってくっつく時に必要
		isAttack = false;
		bodyObj_->wtf.Initialize();
		bodyObj_->wtf.position = defaultPos;
	}


}

//溜め遠距離
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

//向いてる方向にvelocityを変換する
Vector3 Wolf::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//内積
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