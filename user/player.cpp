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
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	camera->SetEye({ 0.0f,3.0f,-8.0f });
	camera->SetTarget({ 0,3,0 });
	Object3d::SetCamera(camera);

	//プレイヤー設定
	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);

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
	if (input_->PushKey(DIK_LSHIFT)) {
		if (input_->PushKey(DIK_1)) {
			//近距離
			if (selectBuddy == 0) {
				wolf_->Attack(enemyPos_, 1);
			}else if (selectBuddy == 1) {
				gorilla_->ShortRange();
			}else if (selectBuddy == 2) {

			}
		}else if (input_->PushKey(DIK_2)) {
			//遠距離
			if (selectBuddy == 0) {
				wolf_->Attack(enemyPos_, 2);
			}
			else if (selectBuddy == 1) {
				gorilla_->LongRange();
			}
			else if (selectBuddy == 2) {

			}
		}else if (input_->PushKey(DIK_3)) {
			//溜め近距離
			if (selectBuddy == 0) {
				wolf_->Attack(enemyPos_, 3);
			}
			else if (selectBuddy == 1) {
				gorilla_->ChargeShortRange();
			}
			else if (selectBuddy == 2) {

			}
		}else if (input_->PushKey(DIK_4)) {
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
		if (input_->PushKey(DIK_1)) {
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
		if (input_->TriggerKey(DIK_2)) {
			//回避発生
			if (isDodge==false) {
				isDodge = true;
				dodgeTimer = dodgeLimit;
				bodyObj_->SetModel(dodgeModel);
			}
		}


		//弱攻撃
		if (input_->PushKey(DIK_3)) {

		}

		//合体
		if (input_->PushKey(DIK_4)) {
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
	Vector3 theta;
	Vector3 camTheta;

	if (input_->PushKey(DIK_D)) {
		theta.y = rotaSpeed_;
	}
	else if (input_->PushKey(DIK_A)) {
		theta.y = -rotaSpeed_;
	}

	bodyObj_->wtf.rotation += theta;

	if (input_->PushKey(DIK_W)) {
		camTheta.y = rotaSpeed_;
	}
	else if (input_->PushKey(DIK_S)) {
		camTheta.y = -rotaSpeed_;
	}

	camera->SetTarget(camera->GetTarget() + camTheta);
}

void Player::Move() {
	Vector3 velocity = { 0,0,0 };

	if (input_->PushKey(DIK_UPARROW)) {
		velocity.z = moveSpeed_;
	}else if (input_->PushKey(DIK_DOWNARROW)) {
		velocity.z = -moveSpeed_;
	}
	if (input_->PushKey(DIK_RIGHTARROW)) {
		velocity.x = moveSpeed_;
	}else if (input_->PushKey(DIK_LEFTARROW)) {
		velocity.x = -moveSpeed_;
	}

	velocity = bVelocity(velocity, bodyObj_->wtf);

	bodyObj_->wtf.position += velocity;
	camera->SetTarget(camera->GetTarget() + velocity);

}


void Player::Update() {
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
	
	bodyObj_->UpdateMat();
	camera->Update(bodyObj_->wtf);
	bodyObj_->Update();
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

Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分
	worldPos.x = bodyObj_->wtf.position.x;
	worldPos.y = bodyObj_->wtf.position.y;
	worldPos.z = bodyObj_->wtf.position.z;


	return worldPos;
}
