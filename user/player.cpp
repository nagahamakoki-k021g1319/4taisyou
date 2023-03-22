#include"player.h"

Player::Player() {
}

Player::~Player() {
	delete bodyObj_;
	delete bodyModel_;
	delete dodgeModel;
	delete wolf_;

	delete debugObj_;
	delete debugModel_;
}

void Player::Initialize(Input* input) {
	input_ = input;

	//プレイヤー設定
	bodyModel_ = Model::LoadFromOBJ("as2");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);
	bodyObj_->wtf.position = { 0,-3,8 };
	hp = defaultHp;
	isAction = 0;

	//回避設定
	dodgeModel = Model::LoadFromOBJ("dodge");
	dodgeTimer = dodgeLimit;
	isDodge = false;

	//バディ
	wolf_ = new Wolf();
	wolf_->Initialize();
	wolf_->SetPlayerWtf(&bodyObj_->wtf);



	//デバッグ用
	debugModel_ = Model::LoadFromOBJ("boll");
	debugObj_ = Object3d::Create();
	debugObj_->SetModel(debugModel_);
}

void Player::Attack() {
	if (isAction == 0) {
		//バディ指示
		if (input_->PushKey(DIK_LSHIFT) || input_->ButtonInput(LT)) {
			if (input_->PushKey(DIK_1) || input_->ButtonInput(B)) {
				//近距離
				wolf_->Attack(1, GetWorldPosition());

			}
			else if (input_->PushKey(DIK_2) || input_->ButtonInput(A)) {
				//遠距離
				wolf_->Attack(2, GetWorldPosition());

			}
			else if (input_->PushKey(DIK_3) || input_->ButtonInput(Y)) {
				//溜め近距離
				wolf_->Attack(3, GetWorldPosition());

			}
			else if (input_->PushKey(DIK_4) || input_->ButtonInput(X)) {
				//溜め遠距離
				wolf_->Attack(4, GetWorldPosition());
			}
		}
		//本体攻撃入力
		else {
			//弱攻撃
			if (input_->PushKey(DIK_4) || input_->ButtonInput(X)) {
				isAction = 1;
				lightAttackCount = 0;
				lightAttackTimer = lightAttackLimit[0];
			}
			//強攻撃
			if (input_->PushKey(DIK_1) || input_->ButtonInput(Y)) {
				isAction = 2;
			}
			//回避
			if (input_->PushKey(DIK_3) || input_->ButtonInput(B)) {
				isAction = 3;
				////回避発生
				//if (input_->LeftStickInput()) {
				//	if (isDodge == false) {
				//		//回避スピード
				//		Vector2 stickVec = input_->GetLeftStickVec();
				//		dodgeMoveVec = { stickVec.x,0,stickVec.y };
				//	//	dodgeMoveVec = bVelocity(dodgeMoveVec, bodyObj_->wtf);

				//		isDodge = true;
				//		dodgeTimer = dodgeLimit;
				//		bodyObj_->SetModel(dodgeModel);
				//	}
				//}
			}
			//null
			if (input_->TriggerKey(DIK_2) || input_->ButtonInput(A)) {
			}
		}
	}

	//攻撃更新
	//弱攻撃
	else if (isAction == 1) {
		LightAttack();
	}
	//強攻撃
	else if (isAction == 2) {
		HeavyAttack();
	}
	//回避
	else if(isAction==3){
		Dodge();

		//if (isDodge) {
		//	dodgeTimer--;
		//	if (dodgeTimer < 0) {
		//		isDodge = false;
		//		bodyObj_->SetModel(bodyModel_);
		//	}
		//}
	}
}

void Player::OnCollision() {
	//回避時
	if(isDodge) {

	}
	//通常時
	else{
		hp -= 10;
		if (hp < 0) {
			isLive = false;
		}
	}
}

void Player::Rota() {
	if (isAction == 0) {
		if (input_->LeftStickInput()) {
			Vector2 stickVec = input_->GetLeftStickVec();

			float theta = atan2(stickVec.x, stickVec.y);

			bodyObj_->wtf.rotation.y = theta;
		}
	}
}

void Player::Update(Transform* cam) {
	Rota();
	Attack();
	
	bodyObj_->Update(cam);
	wolf_->Update(enemyPos_);

	debugObj_->Update();
}

void Player::Draw() {
	if (isLive) {
		bodyObj_->Draw();

		//デバッグ用
		if (isLightAttack) {
			debugObj_->Draw();
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
	worldPos.x = bodyObj_->wtf.matWorld.m[3][0];
	worldPos.y = bodyObj_->wtf.matWorld.m[3][1];
	worldPos.z = bodyObj_->wtf.matWorld.m[3][2];


	return worldPos;
}

bool Player::CheckAttack2Enemy(Vector3 enemyPos, float& damage) {
	//弱攻撃
	if (isAction == 1) {
		//当たり判定が出てるか
		if (isLightAttack) {
			//当たり判定
			if (col.CircleCollisionXZ(lightAttackCol, enemyPos, 1.0f, 1.0f)) {
				damage = 3;
				return true;
			}
		}
	}

	//強攻撃
	else if (isAction == 2) {


	}

	return false;
}

void Player::LightAttack() {
	
	lightAttackTimer--;
	//攻撃の終了
	if (lightAttackTimer <= 0) {
		isAction = 0;
		isLightAttack = false;
	}

	//1撃目
	if (lightAttackCount == 0) {
		//当たり判定の出現
		if (lightAttackTimer <= lightAttackPopTime[0] && lightAttackTimer > 0) {
			isLightAttack = true;
		}

		//当たり判定の移動
		lightAttackCol = GetWorldPosition();
		debugObj_->wtf.position = lightAttackCol;

		//次の斬撃入力
		if (input_->ButtonInput(X)) {
			//入力受付時間
			if (lightAttackTimer < lightAttackInput[lightAttackCount] && lightAttackTimer > 0) {
				//次の斬撃設定
				lightAttackCount++;
				lightAttackTimer = lightAttackLimit[lightAttackCount];
				isLightAttack = false;
			}
		}
	}
	//2撃目
	else if (lightAttackCount == 1) {


	}
	//3撃目
	else if (lightAttackCount == 2) {


	}
	//4撃目
	else if (lightAttackCount == 3) {


	}
}

void Player::HeavyAttack() {

}

void Player::Dodge() {


}