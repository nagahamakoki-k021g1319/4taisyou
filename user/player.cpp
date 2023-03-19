#include"player.h"

Player::Player() {
}

Player::~Player() {
	delete bodyObj_;
	delete bodyModel_;
	delete guardModel;
	delete dodgeModel;
	delete unionModel;
	delete wolf_;
	delete gorilla_;
}

void Player::Initialize(Input* input) {
	input_ = input;

	//プレイヤー設定
	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
	bodyObj_->wtf.position = { 0,-3,8 };

	//ガード設定
	guardModel = Model::LoadFromOBJ("guard");
	GuardDurability = guardMax;
	isGuard = false;

	//回避設定
	dodgeModel = Model::LoadFromOBJ("dodge");
	dodgeTimer = dodgeLimit;
	isDodge = false;

	//合体設定
	unionModel = Model::LoadFromOBJ("wolfUnion");
	specialMeter = 95;
	isUnion = false;


	//バディ
	selectBuddy = 0;
	wolf_ = new Wolf();
	wolf_->Initialize();
	wolf_->SetPlayerWtf(&bodyObj_->wtf);

	gorilla_ = new Gorilla();
	gorilla_->Initialize();
	gorilla_->SetPlayerWtf(&bodyObj_->wtf);

}

void Player::Attack() {

	//バディ指示
	if (input_->PushKey(DIK_LSHIFT) || input_->ButtonInput(LT)) {
		if (input_->PushKey(DIK_1) || input_->ButtonInput(B)) {
			//近距離
			if (selectBuddy == 0) {
				wolf_->Attack(enemyPos_, 1);
			}else if (selectBuddy == 1) {
				gorilla_->ShortRange();
			}else if (selectBuddy == 2) {

			}
		}else if (input_->PushKey(DIK_2) || input_->ButtonInput(A)) {
			//遠距離
			if (selectBuddy == 0) {
				wolf_->Attack(enemyPos_, 2);
			}
			else if (selectBuddy == 1) {
				gorilla_->LongRange();
			}
			else if (selectBuddy == 2) {

			}
		}else if (input_->PushKey(DIK_3) || input_->ButtonInput(Y)) {
			//溜め近距離
			if (selectBuddy == 0) {
				wolf_->Attack(enemyPos_, 3);
			}
			else if (selectBuddy == 1) {
				gorilla_->ChargeShortRange();
			}
			else if (selectBuddy == 2) {

			}
		}else if (input_->PushKey(DIK_4) || input_->ButtonInput(X)) {
			//溜め遠距離
			if (selectBuddy == 0) {
				wolf_->Attack(enemyPos_, 4);
			}
			else if (selectBuddy == 1) {
				gorilla_->ChargeLongRange();
			}
			else if (selectBuddy == 2) {

			}
		}
	}
	//本体攻撃
	else{
		//ガード
		if (input_->PushKey(DIK_1) || input_->ButtonInput(Y)) {
			//ガードの発生
			if (isGuard == false) {
				isGuard = true;
				bodyObj_->SetModel(guardModel);
			}

			//時間経過で耐久地消耗
			if (GuardDurability > 0) {
				GuardDurability--;
			}
			//ガード割れ
			else if (GuardDurability <= 0) {
				isGuard = false;
				bodyObj_->SetModel(bodyModel_);
			}
		}
		else {
			//ガード解除
			if (isGuard) {
				isGuard = false;
				bodyObj_->SetModel(bodyModel_);
			}
			//ガードの耐久回復
			if (GuardDurability < guardMax) {
				GuardDurability++;
			}
		}

		//回避
		if (input_->TriggerKey(DIK_2) || input_->ButtonInput(A)) {
			//回避発生
			if (isDodge==false) {
				isDodge = true;
				dodgeTimer = dodgeLimit;
				bodyObj_->SetModel(dodgeModel);
			}
		}


		//弱攻撃
		if (input_->PushKey(DIK_3) || input_->ButtonInput(B)) {

		}

		//合体
		if (input_->PushKey(DIK_4) || input_->ButtonInput(X)) {
			//合体発生
			if (specialMeter >= 100) {
				isUnion = true;
				bodyObj_->SetModel(unionModel);
			}
		}
	}

	//回避更新
	if (isDodge) {
		dodgeTimer--;
		if (dodgeTimer < 0) {
			isDodge = false;
			bodyObj_->SetModel(bodyModel_);
		}
	}

	//合体更新
	if (isUnion) {
		//メーター減少
		specialMeter -= 1;
		//0以下で強制解除
		if (specialMeter < 0) {
			isUnion = false;
			bodyObj_->SetModel(bodyModel_);
		}
	}

}

void Player::OnCollision() {
	//ガード時
	if (isGuard) {
		if (GuardDurability > 0) {
			//攻撃によって減る量変えたい
			GuardDurability--;
		}
	}
	//回避時
	else if(isDodge) {
		specialMeter += 1;

	}
	//通常時
	else{
		hp--;
	}
}

void Player::Rota() {
	if (input_->StickInput(L_UP)) {
		bodyObj_->wtf.rotation.y = 0;
	}
	if (input_->StickInput(L_DOWN)) {
		bodyObj_->wtf.rotation.y = PI;
	}
	if (input_->StickInput(L_LEFT)) {
		bodyObj_->wtf.rotation.y = PI * 3 / 2;
	}
	if (input_->StickInput(L_RIGHT)) {
		bodyObj_->wtf.rotation.y = PI / 2;
	}

}

void Player::Move() {

}


void Player::Update(Transform* cam) {
	if (input_->TriggerKey(DIK_Q)) {
		if (--selectBuddy < 0) {
			selectBuddy = 2;
		}
	}else if (input_->TriggerKey(DIK_E)) {
		if (++selectBuddy > 2) {
			selectBuddy = 0;
		}
	}

	Rota();
	Move();
	Attack();
	
	bodyObj_->Update(cam);
	wolf_->Update();
	gorilla_->Update();
}


void Player::Draw() {
	bodyObj_->Draw();

	if (isUnion == false) {
		if (selectBuddy == 0) {
			wolf_->Draw();
		}
		else if (selectBuddy == 1) {
		gorilla_->Draw();
		}
		else if (selectBuddy == 2) {

		}
	}
}

Vector3 Player::bVelocity(Vector3& velocity,Transform& worldTransform)
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