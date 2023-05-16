#include"player.h"

Player::Player() {

}

Player::~Player() {
	delete bodyObj_;
	delete bodyModel_;
	delete dash1Obj_;
	delete dash1Model_;
	delete dash2Obj_;
	delete dash2Model_;
	delete dash3Obj_;
	delete dash3Model_;
	delete dash4Obj_;
	delete dash4Model_;
	delete attack1Obj_;
	delete attack1Model_;
	delete attack2Obj_;
	delete attack2Model_;
	delete attack3Obj_;
	delete attack3Model_;
	delete attack4Obj_;
	delete attack4Model_;

	delete wolf_;

	delete debugObj_;
	delete debugModel_;

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;

}

void Player::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();

	// カメラ生成
	camera = new Camera(1280, 720);
	FBXObject3d::SetCamera(camera);

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("playerRun");
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->SetScale({ 0.01,0.01,0.01 });
	fbxObject3d_->SetPosition({ 0,0,40 });
	fbxObject3d_->PlayAnimation();

	//プレイヤー設定
	bodyModel_ = Model::LoadFromOBJ("player");
	bodyObj_ = Object3d::Create();
	bodyObj_->SetModel(bodyModel_);

	dash1Model_ = Model::LoadFromOBJ("Ldash1");
	dash1Obj_ = Object3d::Create();
	dash1Obj_->SetModel(dash1Model_);

	dash2Model_ = Model::LoadFromOBJ("Ldash2");
	dash2Obj_ = Object3d::Create();
	dash2Obj_->SetModel(dash2Model_);

	dash3Model_ = Model::LoadFromOBJ("Rdash1");
	dash3Obj_ = Object3d::Create();
	dash3Obj_->SetModel(dash3Model_);

	dash4Model_ = Model::LoadFromOBJ("Rdash2");
	dash4Obj_ = Object3d::Create();
	dash4Obj_->SetModel(dash4Model_);

	attack1Model_ = Model::LoadFromOBJ("attack1");
	attack1Obj_ = Object3d::Create();
	attack1Obj_->SetModel(attack1Model_);
	
	attack2Model_ = Model::LoadFromOBJ("attack2");
	attack2Obj_ = Object3d::Create();
	attack2Obj_->SetModel(attack2Model_);
	
	attack3Model_ = Model::LoadFromOBJ("attack3");
	attack3Obj_ = Object3d::Create();
	attack3Obj_->SetModel(attack3Model_);
	
	attack4Model_ = Model::LoadFromOBJ("attack4");
	attack4Obj_ = Object3d::Create();
	attack4Obj_->SetModel(attack4Model_);


	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();

	//バディ
	wolf_ = new Wolf();
	wolf_->Initialize();
	wolf_->SetPlayerWtf(&bodyObj_->wtf);

	//デバッグ用
	debugModel_ = Model::LoadFromOBJ("boll");
	debugObj_ = Object3d::Create();
	debugObj_->wtf.scale.x = 2;
	debugObj_->wtf.scale.y = 2;
	debugObj_->wtf.scale.z = 2;
	debugObj_->SetModel(debugModel_);

	audio = new Audio();

	Reset();
}

void Player::Reset() {
	camTransForm->Initialize();
	eyePos = { 0.0f, 3.0f, -8.0f };
	targetPos = { 0.0f,0.0f,targetDistance };

	bodyObj_->wtf.Initialize();

	dash1Obj_->wtf.Initialize();

	dash2Obj_->wtf.Initialize();

	dash3Obj_->wtf.Initialize();

	dash4Obj_->wtf.Initialize();

	attack1Obj_->wtf.Initialize();
	
	attack2Obj_->wtf.Initialize();
	
	attack3Obj_->wtf.Initialize();
	
	attack4Obj_->wtf.Initialize();

	hp = defaultHp;
	isAction = 0;
	isLive = true;
	isAttackFin = false;
	nextAttack = false;

	//弱攻撃
	lightAttackLPos = { 0,0,3 };
	//何回めの連撃か
	lightAttackCount = 0;
	//攻撃の当たり判定の有無
	isLightAttack = false;
	lightAttackTimer = 60;


	//弱攻撃
	heavyAttackLPos = { 0,0,5 };
	//何回めの連撃か
	heavyAttackCount = 0;
	//攻撃の当たり判定の有無
	isHeavyAttack = false;
	heavyAttackTimer = 60;

	//��ʃV�F�C�N
	isCamShake = false;
	camShakeTimer = camShakeLimit;

	//回避設定
	dodgeTimer = dodgeLimit;
	isDodge = false;


	audio->Initialize();
	audio->LoadWave("col.wav");
	audio->LoadWave("kaihi.wav");

	objRotaTimer = 0;

	//MP関連
	mp = 100;

}

void Player::Attack() {
	if (isAction == 0) {
		//バディ指示
		if (input_->PushKey(DIK_LSHIFT) || input_->ButtonInput(LT)) {
			if (input_->PushKey(DIK_1) || input_->PButtonTrigger(B)) {
				//弾を前方に出す
				if (mp >= bulletMp) {
					wolf_->Attack(1, GetWorldPosition());
					mp -= bulletMp;
				}
			}
			else if (input_->PushKey(DIK_2) || input_->PButtonTrigger(A)) {
			}
			else if (input_->PushKey(DIK_3) || input_->PButtonTrigger(Y)) {
				//大回復
				if (mp >= megaHealMp) {
					mp -= megaHealMp;
					hp += megaHeal;
					if (hp > 100) {
						hp = 100;
					}
				}
			}
			else if (input_->PushKey(DIK_4) || input_->PButtonTrigger(X)) {
				//小回復
				if (mp >= healMp) {
					mp -= healMp;
					hp += heal;
					if (hp > 100) {
						hp = 100;
					}
				}
			}
		}
		//本体攻撃入力
		else {
			//弱攻撃
			if (input_->PushKey(DIK_4) || input_->PButtonTrigger(X)) {
				isAction = 1;
				lightAttackCount = 0;
				lightAttackTimer = lightAttackLimit[0];
				isAttackFin = false;
			}
			//強攻撃
			if (input_->PushKey(DIK_1) || input_->PButtonTrigger(Y)) {
				isAction = 2;
				heavyAttackCount = 0;
				heavyAttackTimer = heavyAttackLimit[0];
				isAttackFin = false;
			}
			//回避
			if (input_->PushKey(DIK_3) || input_->PButtonTrigger(B)) {
				if (input_->LeftStickInput()) {
					isAction = 3;
					isDodge = true;
					dodgeTimer = dodgeLimit;
					Vector2 stickVec = input_->GetLeftStickVec();
					dodgeMoveVec = { stickVec.x,0,stickVec.y };
					dodgeMoveVecNomal = dodgeMoveVec.nomalize();
				}
			}
			//null
			if (input_->TriggerKey(DIK_2) || input_->PButtonTrigger(A)) {
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
	else if (isAction == 3) {
		Dodge();
	}
}

void Player::OnCollision() {
	if (isInvincible == false) {
		//回避時
		if (isDodge) {
			pSourceVoice[1] = audio->PlayWave("kaihi.wav");
			pSourceVoice[1]->SetVolume(0.7f);
		}
		//通常時
		else {
			hp -= 10;
			isEffFlag = 1;
			pSourceVoice[0] = audio->PlayWave("col.wav");
			isInvincible = true;
			invincibleTimer = invincibleLimit;

			isCamShake = true;
			camShakeTimer = camShakeLimit;

			if (hp < 0) {
				isLive = false;
			}
		}
	}
}

void Player::Move() {
	if (input_->LeftStickInput()) {
		//移動量
		Vector3 velocity = { 0,0,0 };

		//移動速度
		float speed = camMoveSpeed;

		if (input_->ButtonInput(RT)) {
			if (mp > dashMP) {
				speed = dashSpeed;
				MpUpdate(-dashMP);
			}
		}

		//通常移動
		if (isAction == 0) {
			//入力
			Vector2 stickVec = input_->GetLeftStickVec();

			velocity.x = stickVec.x;
			velocity.z = stickVec.y;

			velocity = velocity.nomalize();

			velocity *= speed;
		}
		//回避時移動
		else if (isAction == 3) {
			velocity = GetDodgeMoveVec();

		}

		//移動ベクトルを向いてる方向に合わせる
		velocity = bVelocity(velocity, *camTransForm);

		Vector3 pos = GetWorldPosition();
		Vector3 newPos = pos + velocity;

		if (newPos.x > 50) {
			velocity.x = 50 - pos.x;
		}
		else if (newPos.x < -50) {
			velocity.x = -50 - pos.x;
		}

		if (newPos.z > 50) {
			velocity.z = 50 - pos.z;
		}
		else if (newPos.z < -50) {
			velocity.z = -50 - pos.z;
		}

		//更新
		bodyObj_->wtf.position += velocity;
		dash1Obj_->wtf.position += velocity;
		dash2Obj_->wtf.position += velocity;
		dash3Obj_->wtf.position += velocity;
		dash4Obj_->wtf.position += velocity;
		attack1Obj_->wtf.position += velocity;
		attack2Obj_->wtf.position += velocity;
		attack3Obj_->wtf.position += velocity;
		attack4Obj_->wtf.position += velocity;
	}
}

void Player::Rota() {
	if (isAction == 0) {
		if (input_->LeftStickInput()) {
			Vector2 stickVec = input_->GetLeftStickVec();

			float theta = atan2(stickVec.x, stickVec.y);

			bodyObj_->wtf.rotation.y = theta+camTransForm->rotation.y;

			dash1Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

			dash2Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

			dash3Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

			dash4Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

			attack1Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

			attack2Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

			attack3Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

			attack4Obj_->wtf.rotation.y = theta + camTransForm->rotation.y;

		}
	}
}

void Player::camUpdate() {
	camTransForm->position = bodyObj_->wtf.position;
	//視点移動
	//左右
	Vector3 theta;
	if (input_->StickInput(R_LEFT)) {
		theta.y = -camRotaSpeed;
	}else if (input_->StickInput(R_RIGHT)) {
		theta.y = camRotaSpeed;
	}
	camTransForm->rotation += theta;

	//上下
	if (input_->StickInput(R_UP)) {
		targetTheta += camRotaSpeed;
	}
	else if (input_->StickInput(R_DOWN)) {
		targetTheta += -camRotaSpeed;
	}

	//角度制限
	if (targetTheta < -PI / 5 * 2) {//下の制限
		targetTheta = -PI / 5 * 2;
	}
	else if (targetTheta > PI / 3) { //上の制限
		targetTheta = PI / 3;
	}

	//視点は一定の距離
	targetPos.z = cos(targetTheta) * targetDistance;
	targetPos.y = sin(targetTheta) * targetDistance;

	targetPos += GetCamShake();


	camTransForm->UpdateMat();

	camera->SetEye(eyePos * camTransForm->matWorld);
	camera->SetTarget(targetPos * camTransForm->matWorld);

	camera->Update();
}

void Player::Update() {
	if (isInvincible) {
		invincibleTimer--;
		if (invincibleTimer < 0) {
			isInvincible = false;
		}
	}

	Rota();
	Move();

	camUpdate();

	Attack();

	if (isEffFlag == 1) {
		EffTimer++;
	}
	if (EffTimer <= 10 && EffTimer >= 1) {
		EffUpdate();
	}
	if (EffTimer >= 11) {
		isEffFlag = 0;
		EffTimer = 0;
	}

	//��ʃV�F�C�N
	if (isCamShake == true) {
		camShakeTimer--;
		if (camShakeTimer <= camShakeLimit && camShakeTimer > camShakeLimit * 3 / 4) {
			camShakeVec.y += 0.05f;
			camShakeVec.z += 0.05f;
		}else if (camShakeTimer <= camShakeLimit * 3 / 4 && camShakeTimer > camShakeLimit * 2 / 4) {
			camShakeVec.y -= 0.05f;
			camShakeVec.z -= 0.05f;
		}else if (camShakeTimer <= camShakeLimit * 2 / 4 && camShakeTimer > camShakeLimit * 1 / 4) {
			camShakeVec.y += 0.05f;
			camShakeVec.z += 0.05f;
		}else if (camShakeTimer <= camShakeLimit * 1 / 4 && camShakeTimer > 0) {
			camShakeVec.y -= 0.05f;
			camShakeVec.z -= 0.05f;
		}else if (camShakeTimer <= 0) {
			isCamShake = false;
			camShakeVec = { 0,0,0 };
		}
	}
	bodyObj_->Update();
	dash1Obj_->Update();
	dash2Obj_->Update();
	dash3Obj_->Update();
	dash4Obj_->Update();
	attack1Obj_->Update();
	attack2Obj_->Update();
	attack3Obj_->Update();
	attack4Obj_->Update();

	fbxObject3d_->Update();

	wolf_->Update(enemyPos_);
	MpUpdate(mpRegen);
	

	debugObj_->Update();
}

void Player::Draw() {
	if (isLive) {
		
		//弱攻撃のモーション
		if (input_->PButtonTrigger(X) || input_->PButtonTrigger(Y)) {

			attackFlag = 1;
		}
		if (attackFlag == 1) {
			objAttackTimer--;

			if (objAttackTimer >= 12 && objAttackTimer <= 16) {
				attack1Obj_->Draw();
			}
			else if (objAttackTimer >= 8 && objAttackTimer <= 11) {
				attack2Obj_->Draw();
			}
			else if (objAttackTimer >= 4 && objAttackTimer <= 7) {
				attack3Obj_->Draw();
			}
			else if (objAttackTimer >= 0 && objAttackTimer <= 3) {
				attack4Obj_->Draw();
			}
			if (objAttackTimer <= 0) {
				attackFlag = 0;
				objAttackTimer = 16;
			}
		}
		if (attackFlag == 0) {
			//移動のモーション
			if (input_->LeftStickInput()) {

				objRotaTimer--;
				if (objRotaTimer >= 25 && objRotaTimer <= 30) {
					dash1Obj_->Draw();
				}
				else if (objRotaTimer >= 20 && objRotaTimer <= 24) {
					dash2Obj_->Draw();
				}
				else if (objRotaTimer >= 15 && objRotaTimer <= 19) {
					dash3Obj_->Draw();
				}
				else if (objRotaTimer >= 10 && objRotaTimer <= 14) {
					dash4Obj_->Draw();
				}
				else if (objRotaTimer >= 5 && objRotaTimer <= 9) {
					dash3Obj_->Draw();
				}
				else if (objRotaTimer >= 0 && objRotaTimer <= 4) {
					dash2Obj_->Draw();
				}

				if (objRotaTimer <= 0) {
					objRotaTimer = 30;
				}
			}
			else {
				if (attackFlag == 0) {
					bodyObj_->Draw();
				}

				objRotaTimer = 0;
			}
		}

		

		wolf_->Draw();

		////デバッグ用
		//if (isLightAttack) {
		//	debugObj_->Draw();
		//}
		//if (isHeavyAttack) {
		//	debugObj_->Draw();
		//}
	}
}

void Player::FbxDraw()
{
	fbxObject3d_->Draw(dxCommon->GetCommandList());
}

void Player::EffUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos += GetWorldPosition();
		pos.y += 1.0f;
		//速度
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		particleManager->Add(60, pos, vel, acc, 1.0f, 0.0f);

		particleManager->Update();
	}

}

void Player::EffDraw()
{
	if (isEffFlag == 1) {
		// 3Dオブクジェクトの描画
		particleManager->Draw();
	}

}

Vector3 Player::bVelocity(Vector3& velocity, Transform& worldTransform)
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
			if (col.CircleCollisionXZ(lightAttackWPos, enemyPos, 0.5f, 1.0f)) {
				damage = 3;
				MpUpdate(lightMpPuls);
				return true;
			}
		}
	}

	//強攻撃
	else if (isAction == 2) {
		//当たり判定が出てるか
		if (isHeavyAttack) {
			//当たり判定
			if (col.CircleCollisionXZ(heavyAttackWPos, enemyPos, 1.0f, 1.0f)) {
				damage = 7;
				MpUpdate(heavyMpPuls);
				return true;
			}
		}
	}

	return false;

	return false;
}

bool Player::CheckBody2Enemy(Vector3 enemyPos) {
	if (col.CircleCollisionXZ(GetWorldPosition(), enemyPos, 1.0f, 1.0f)) {
		moveBack += { 0,0,-0.2 };
		moveBack = bVelocity(moveBack, bodyObj_->wtf);
		return true;
	}
	return false;
}

Vector3 Player::GetMoveBack() {
	Vector3 result = moveBack;
	moveBack = { 0,0,0 };
	return result;
}

void Player::LightAttack() {
	lightAttackTimer--;

	//1撃目
	if (lightAttackCount == 0) {
		//当たり判定の出現
		if (lightAttackTimer <= lightAttackPopTime[0] && lightAttackTimer > lightAttackDeathTime[0]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//当たり判定の消失、硬直
		else if (lightAttackTimer <= lightAttackDeathTime[0] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//攻撃の終了
		else if (lightAttackTimer <= 0) {
			if (nextAttack) {
				//次の斬撃設定
				lightAttackCount++;
				lightAttackTimer = lightAttackLimit[lightAttackCount];
				isLightAttack = false;
				isAttackFin = true;
				nextAttack = false;
			}
			else {
				isAction = 0;
				isAttackFin = true;
				nextAttack = false;
			}
		}

		//当たり判定の移動
		if (isLightAttack) {
			//移動
			lightAttackLPos = { 0.5f,0,2.0f };
			//更新
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}

		//次の斬撃入力
		if (input_->PButtonTrigger(X)) {
			//入力受付時間
			if (lightAttackTimer < lightAttackInput[lightAttackCount] && lightAttackTimer > 0) {
				//次の斬撃設定
				nextAttack = true;
			}
		}
	}
	//2撃目
	else if (lightAttackCount == 1) {
		//当たり判定の出現
		if (lightAttackTimer <= lightAttackPopTime[1] && lightAttackTimer > lightAttackDeathTime[1]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//当たり判定の消失、硬直
		else if (lightAttackTimer <= lightAttackDeathTime[1] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//攻撃の終了
		else if (lightAttackTimer <= 0) {
			if (nextAttack) {
				//次の斬撃設定
				lightAttackCount++;
				lightAttackTimer = lightAttackLimit[lightAttackCount];
				isLightAttack = false;
				isAttackFin = true;
				nextAttack = false;
			}
			else {
				isAction = 0;
				isAttackFin = true;
				nextAttack = false;
			}
		}

		//当たり判定の移動
		if (isLightAttack) {
			//移動
			lightAttackLPos = { -0.5f,0,2.0f };
			//更新
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}

		//次の斬撃入力
		if (input_->PButtonTrigger(X)) {
			//入力受付時間
			if (lightAttackTimer < lightAttackInput[lightAttackCount] && lightAttackTimer > 0) {
				//次の斬撃設定
				nextAttack = true;
			}
		}
	}
	//3撃目
	else if (lightAttackCount == 2) {
		//当たり判定の出現
		if (lightAttackTimer <= lightAttackPopTime[2] && lightAttackTimer > lightAttackDeathTime[2]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//当たり判定の消失、硬直
		else if (lightAttackTimer <= lightAttackDeathTime[2] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//攻撃の終了
		else if (lightAttackTimer <= 0) {
			if (nextAttack) {
				//次の斬撃設定
				lightAttackCount++;
				lightAttackTimer = lightAttackLimit[lightAttackCount];
				isLightAttack = false;
				isAttackFin = true;
				nextAttack = false;
			}
			else {
				isAction = 0;
				isAttackFin = true;
				nextAttack = false;
			}
		}

		//当たり判定の移動
		if (isLightAttack) {
			//移動
			lightAttackLPos = { 0.5f,0,2.0f };
			//更新
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}

		//次の斬撃入力
		if (input_->PButtonTrigger(X)) {
			//入力受付時間
			if (lightAttackTimer < lightAttackInput[lightAttackCount] && lightAttackTimer > 0) {
				//次の斬撃設定
				nextAttack = true;
			}
		}
	}
	//4撃目
	else if (lightAttackCount == 3) {
		//当たり判定の出現
		if (lightAttackTimer <= lightAttackPopTime[0] && lightAttackTimer > lightAttackDeathTime[0]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//当たり判定の消失、硬直
		else if (lightAttackTimer <= lightAttackDeathTime[0] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//攻撃の終了
		else if (lightAttackTimer <= 0) {
			isAction = 0;
			isAttackFin = true;
			nextAttack = false;
		}

		//当たり判定の移動
		if (isLightAttack) {
			//移動
			lightAttackLPos = { 0,0,4.0f };
			//更新
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}
	}
}

void Player::HeavyAttack() {
	heavyAttackTimer--;

	//1撃目
	if (heavyAttackCount == 0) {
		//当たり判定の出現
		if (heavyAttackTimer <= heavyAttackPopTime[0] && heavyAttackTimer > heavyAttackDeathTime[0]) {
			isHeavyAttack = true;
			isAttackFin = false;
		}
		//当たり判定の消失、硬直
		else if (heavyAttackTimer <= heavyAttackDeathTime[0] && heavyAttackTimer > 0) {
			isHeavyAttack = false;
		}
		//攻撃の終了
		else if (heavyAttackTimer <= 0) {
			if (nextAttack) {
				//次の斬撃設定
				heavyAttackCount++;
				heavyAttackTimer = heavyAttackLimit[heavyAttackCount];
				isHeavyAttack = false;
				isAttackFin = true;
				nextAttack = false;
			}
			else {
				isAction = 0;
				isAttackFin = true;
				nextAttack = false;
			}
		}

		//当たり判定の移動
		if (isHeavyAttack) {
			//移動
			heavyAttackLPos = { 0,0,4.0f };
			//更新
			heavyAttackWPos = heavyAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = heavyAttackWPos;
		}

		//次の斬撃入力
		if (input_->PButtonTrigger(Y)) {
			//入力受付時間
			if (heavyAttackTimer < heavyAttackInput[heavyAttackCount] && heavyAttackTimer > 0) {
				//次の斬撃設定
				nextAttack = true;
			}
		}
	}
	//2撃目
	else if (heavyAttackCount == 1) {
		//当たり判定の出現
		if (heavyAttackTimer <= heavyAttackPopTime[1] && heavyAttackTimer > heavyAttackDeathTime[1]) {
			isHeavyAttack = true;
			isAttackFin = false;
		}
		//当たり判定の消失、硬直
		else if (heavyAttackTimer <= heavyAttackDeathTime[1] && heavyAttackTimer > 0) {
			isHeavyAttack = false;
		}
		//攻撃の終了
		else if (heavyAttackTimer <= 0) {
			isAction = 0;
			isAttackFin = true;
			nextAttack = false;
		}

		//当たり判定の移動
		if (isHeavyAttack) {
			//移動
			heavyAttackLPos = { 0,0,8.0f };
			//更新
			heavyAttackWPos = heavyAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = heavyAttackWPos;
		}
	}
}

void Player::Dodge() {
	dodgeTimer--;

	if (dodgeTimer > dodgeStun) {
		//回避時
		//移動速度変更
		dodgeMoveVec = dodgeMoveVecNomal;
	
	}else if (dodgeTimer > 0) {
		//硬直
		dodgeMoveVec = { 0,0,0 };
	
	}else if (dodgeTimer <= 0) {
		isDodge = false;
		isAction = 0;
	}
}

void Player::MpUpdate(float mp) {
	this->mp += mp;
	if (this->mp > 100) {
		this->mp = 100;
	}
}