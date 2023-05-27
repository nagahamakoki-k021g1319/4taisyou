#include"player.h"

Player::Player() {

}

Player::~Player() {
	delete wolf_;

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;
	delete fbxDashObject3d_;
	delete fbxDashModel_;
	delete fbxWeak1Object3d_;
	delete fbxWeak1Model_;
	delete fbxWeak2Object3d_;
	delete fbxWeak2Model_;
	delete fbxWeak3Object3d_;
	delete fbxWeak3Model_;
	delete fbxWeak4Object3d_;
	delete fbxWeak4Model_;
	delete fbxRollObject3d_;
	delete fbxRollModel_;
	delete fbxWalkObject3d_;
	delete fbxWalkModel_;
	delete fbxStrongObject3d_;
	delete fbxStrongModel_;
}

void Player::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("stand");
	fbxRollModel_ = FbxLoader::GetInstance()->LoadModelFromFile("roll");
	fbxWalkModel_ = FbxLoader::GetInstance()->LoadModelFromFile("walk");
	fbxDashModel_ = FbxLoader::GetInstance()->LoadModelFromFile("dash");
	fbxWeak1Model_ = FbxLoader::GetInstance()->LoadModelFromFile("weakAttack1");
	fbxWeak2Model_ = FbxLoader::GetInstance()->LoadModelFromFile("weakAttack2");
	fbxWeak3Model_ = FbxLoader::GetInstance()->LoadModelFromFile("weakAttack3");
	fbxWeak4Model_ = FbxLoader::GetInstance()->LoadModelFromFile("weakAttack4");
	fbxStrongModel_ = FbxLoader::GetInstance()->LoadModelFromFile("strongAttack");
	fbxMeraModel_ = FbxLoader::GetInstance()->LoadModelFromFile("mera");
	fbxHealModel_ = FbxLoader::GetInstance()->LoadModelFromFile("heal");
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->PlayAnimation();
	//回避
	fbxRollObject3d_ = new FBXObject3d;
	fbxRollObject3d_->Initialize();
	fbxRollObject3d_->SetModel(fbxRollModel_);
	fbxRollObject3d_->PlayAnimation();
	//歩き
	fbxWalkObject3d_ = new FBXObject3d;
	fbxWalkObject3d_->Initialize();
	fbxWalkObject3d_->SetModel(fbxWalkModel_);
	fbxWalkObject3d_->PlayAnimation();
	//走る
	fbxDashObject3d_ = new FBXObject3d;
	fbxDashObject3d_->Initialize();
	fbxDashObject3d_->SetModel(fbxDashModel_);
	fbxDashObject3d_->PlayAnimation();
	//弱攻撃1
	fbxWeak1Object3d_ = new FBXObject3d;
	fbxWeak1Object3d_->Initialize();
	fbxWeak1Object3d_->SetModel(fbxWeak1Model_);
	fbxWeak1Object3d_->PlayAnimation();
	//弱攻撃2
	fbxWeak2Object3d_ = new FBXObject3d;
	fbxWeak2Object3d_->Initialize();
	fbxWeak2Object3d_->SetModel(fbxWeak2Model_);
	fbxWeak2Object3d_->PlayAnimation();
	//弱攻撃3
	fbxWeak3Object3d_ = new FBXObject3d;
	fbxWeak3Object3d_->Initialize();
	fbxWeak3Object3d_->SetModel(fbxWeak3Model_);
	fbxWeak3Object3d_->PlayAnimation();
	//弱攻撃4
	fbxWeak4Object3d_ = new FBXObject3d;
	fbxWeak4Object3d_->Initialize();
	fbxWeak4Object3d_->SetModel(fbxWeak4Model_);
	fbxWeak4Object3d_->PlayAnimation();
	//強攻撃
	fbxStrongObject3d_ = new FBXObject3d;
	fbxStrongObject3d_->Initialize();
	fbxStrongObject3d_->SetModel(fbxStrongModel_);
	fbxStrongObject3d_->PlayAnimation();
	//メラ
	fbxMeraObject3d_ = new FBXObject3d;
	fbxMeraObject3d_->Initialize();
	fbxMeraObject3d_->SetModel(fbxStrongModel_);
	fbxMeraObject3d_->PlayAnimation();
	//回復
	fbxHealObject3d_ = new FBXObject3d;
	fbxHealObject3d_->Initialize();
	fbxHealObject3d_->SetModel(fbxStrongModel_);
	fbxHealObject3d_->PlayAnimation();

	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();

	particleHealManager = std::make_unique<ParticleManager>();
	particleHealManager.get()->Initialize();
	particleHealManager->LoadTexture("hill.png");
	particleHealManager->Update();

	particleHiHealManager = std::make_unique<ParticleManager>();
	particleHiHealManager.get()->Initialize();
	particleHiHealManager->LoadTexture("hihill.png");
	particleHiHealManager->Update();

	//バディ
	wolf_ = new Wolf();
	wolf_->Initialize();
	wolf_->SetPlayerWtf(&fbxObject3d_->wtf);

	audio = new Audio();
	sensitivity = 1;

	Reset();
}

void Player::Reset() {
	camTransForm->Initialize();
	eyePos = { 0.0f, 3.0f, -8.0f };
	targetPos = { 0.0f,0.0f,targetDistance };
	
	fbxObject3d_->Initialize();
	fbxRollObject3d_->Initialize();
	fbxWalkObject3d_->Initialize();
	fbxDashObject3d_->Initialize();
	fbxWeak1Object3d_->Initialize();
	fbxWeak2Object3d_->Initialize();
	fbxWeak3Object3d_->Initialize();
	fbxWeak4Object3d_->Initialize();
	fbxStrongObject3d_->Initialize();
	fbxMeraObject3d_->Initialize();
	fbxHealObject3d_->Initialize();

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

	centerPos = { 0,2,0 };
	isActionStop = true;

}

void Player::Attack() {
	if (isAction == 0) {
		//バディ指示
		if (input_->PushKey(DIK_LSHIFT) || input_->ButtonInput(LT)) {
			if (input_->PushKey(DIK_1) || input_->PButtonTrigger(B)) {
				//メラ
				if (mp >= bulletMp) {
					isAction = 4;
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
					isEffHiHealFlag = 1;
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
					isEffHealFlag = 1;
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
				fbxWeak1Object3d_->PlayAnimation();
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
	//メラ
	else if (isAction = 4) {
		isAction = 0;
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
		fbxObject3d_->wtf.position += velocity;
		fbxWalkObject3d_->wtf.position += velocity;
		fbxRollObject3d_->wtf.position += velocity;
		fbxDashObject3d_->wtf.position += velocity;
		fbxStrongObject3d_->wtf.position += velocity;
		fbxWeak1Object3d_->wtf.position += velocity;
		fbxWeak2Object3d_->wtf.position += velocity;
		fbxWeak3Object3d_->wtf.position += velocity;
		fbxWeak4Object3d_->wtf.position += velocity;
		fbxMeraObject3d_->wtf.position += velocity;
		fbxHealObject3d_->wtf.position += velocity;
		
	}
}

void Player::Rota() {
	if (isAction == 0) {
		if (input_->LeftStickInput()) {
			Vector2 stickVec = input_->GetLeftStickVec();

			float theta = atan2(stickVec.x, stickVec.y);

			fbxObject3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxWalkObject3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxWeak1Object3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxWeak2Object3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxWeak3Object3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxWeak4Object3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxRollObject3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxDashObject3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxStrongObject3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxMeraObject3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			fbxHealObject3d_->wtf.rotation.y = theta + camTransForm->rotation.y;
			
		}
	}
}

void Player::camUpdate() {
	camTransForm->position = fbxObject3d_->wtf.position;
	//視点移動
	//左右
	Vector3 theta;
	if (input_->StickInput(R_LEFT)) {
		theta.y = -camRotaSpeed * sensitivity;
	}
	else if (input_->StickInput(R_RIGHT)) {
		theta.y = camRotaSpeed * sensitivity;
	}
	camTransForm->rotation += theta;

	//上下
	if (input_->StickInput(R_UP)) {
		targetTheta += camRotaSpeed * sensitivity;
	}
	else if (input_->StickInput(R_DOWN)) {
		targetTheta += -camRotaSpeed * sensitivity;
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
	if (isActionStop == false) {

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

		//ダメージエフェクト
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

		//回復エフェクト
		if (isEffHealFlag == 1) {
			EffHealTimer++;
		}
		if (EffHealTimer <= 10 && EffHealTimer >= 1) {
			EffHealUpdate();
		}
		if (EffHealTimer >= 11) {
			isEffHealFlag = 0;
			EffHealTimer = 0;
		}
		//回復エフェクト(大)
		if (isEffHiHealFlag == 1) {
			EffHiHealTimer++;
		}
		if (EffHiHealTimer <= 10 && EffHiHealTimer >= 1) {
			EffHiHealUpdate();
		}
		if (EffHiHealTimer >= 11) {
			isEffHiHealFlag = 0;
			EffHiHealTimer = 0;
		}

		//��ʃV�F�C�N
		if (isCamShake == true) {
			camShakeTimer--;
			if (camShakeTimer <= camShakeLimit && camShakeTimer > camShakeLimit * 3 / 4) {
				camShakeVec.y += 0.05f;
				camShakeVec.z += 0.05f;
			}
			else if (camShakeTimer <= camShakeLimit * 3 / 4 && camShakeTimer > camShakeLimit * 2 / 4) {
				camShakeVec.y -= 0.05f;
				camShakeVec.z -= 0.05f;
			}
			else if (camShakeTimer <= camShakeLimit * 2 / 4 && camShakeTimer > camShakeLimit * 1 / 4) {
				camShakeVec.y += 0.05f;
				camShakeVec.z += 0.05f;
			}
			else if (camShakeTimer <= camShakeLimit * 1 / 4 && camShakeTimer > 0) {
				camShakeVec.y -= 0.05f;
				camShakeVec.z -= 0.05f;
			}
			else if (camShakeTimer <= 0) {
				isCamShake = false;
				camShakeVec = { 0,0,0 };
			}
		}

		MpUpdate(mpRegen);
	}


	if (isLive) {
		if (isAction == 0) {
			if (isEffHealFlag) {
				fbxHealObject3d_->Update();
			}else if (isEffHiHealFlag) {
				fbxHealObject3d_->Update();
			}else if (input_->LeftStickInput()) {
				if (isActionStop == false) {
					if (input_->ButtonInput(RT)) {
						//ダッシュ
						fbxDashObject3d_->Update();
					}else {
						//歩き
						fbxWalkObject3d_->Update();
					}
				}else {
					//待機
					fbxObject3d_->Update();
				}
			}else {
				//待機
				fbxObject3d_->Update();
			}
		}else if (isAction == 1) {
			//弱攻撃
			if (lightAttackCount == 0) {
				fbxWeak1Object3d_->Update();
			}else if (lightAttackCount == 1) {
				fbxWeak2Object3d_->Update();
			}else if (lightAttackCount == 2) {
				fbxWeak3Object3d_->Update();
			}else if (lightAttackCount == 3) {
				fbxWeak4Object3d_->Update();
			}
		}else if (isAction == 2) {
			//強攻撃
			if (heavyAttackCount == 0) {
				fbxStrongObject3d_->Update();
			}else if (heavyAttackCount == 1) {
				//1撃目と同じFBXになってる
				fbxStrongObject3d_->Update();
			}
		}else if (isAction == 3) {
			//回避
			fbxRollObject3d_->Update();
		}else if (isAction == 4) {
			//メラ
			fbxMeraObject3d_->Update();
		}
	}

	wolf_->Update(enemyPos_);
}

void Player::Draw() {
	if (isLive) {

		wolf_->Draw();
	}
}

void Player::FbxDraw(){
	if (isLive) {
		if (isAction == 0) {
			if (isEffHealFlag) {
				fbxHealObject3d_->Draw(dxCommon->GetCommandList());
			}else if (isEffHiHealFlag) {
				fbxHealObject3d_->Draw(dxCommon->GetCommandList());
			}else if (input_->LeftStickInput()) {
				if (isActionStop == false) {
					if (input_->ButtonInput(RT)) {
						//ダッシュ
						fbxDashObject3d_->Draw(dxCommon->GetCommandList());
					}else {
						//歩き
						fbxWalkObject3d_->Draw(dxCommon->GetCommandList());
					}
				}else {
					//待機
					fbxObject3d_->Draw(dxCommon->GetCommandList());
				}
			}else {
				//待機
				fbxObject3d_->Draw(dxCommon->GetCommandList());
			}		
		}else if (isAction == 1) {
			//弱攻撃
			if (lightAttackCount == 0) {
				fbxWeak1Object3d_->Draw(dxCommon->GetCommandList());
			}else if (lightAttackCount == 1) {
				fbxWeak2Object3d_->Draw(dxCommon->GetCommandList());
			}else if (lightAttackCount == 2) {
				fbxWeak3Object3d_->Draw(dxCommon->GetCommandList());
			}else if (lightAttackCount == 3) {
				fbxWeak4Object3d_->Draw(dxCommon->GetCommandList());
			}
		}else if (isAction == 2) {
			//強攻撃
			if (heavyAttackCount == 0) {
				fbxStrongObject3d_->Draw(dxCommon->GetCommandList());
			}else if (heavyAttackCount == 1) {
				//1撃目と同じFBXになってる
				fbxStrongObject3d_->Draw(dxCommon->GetCommandList());
			}
		}else if (isAction == 3) {
			//回避
			fbxRollObject3d_->Draw(dxCommon->GetCommandList());
		}else if (isAction == 4) {
			//メラ
			fbxMeraObject3d_->Draw(dxCommon->GetCommandList());
		}
	}
}

//ダメージエフェクト
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

//回復エフェクト
void Player::EffHealUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 2; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos += GetWorldPosition();
		pos.y += 1.0f;
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.000001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		particleHealManager->Add(60, pos, vel, acc, 0.3f, 0.0f);

		particleHealManager->Update();
	}

}

void Player::EffHiHealUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 2; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 5.0f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos += GetWorldPosition();
		pos.y += 1.0f;
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		particleHiHealManager->Add(60, pos, vel, acc, 0.3f, 0.0f);

		particleHiHealManager->Update();
	}

}

void Player::EffDraw()
{
	//ダメージエフェクト
	if (isEffFlag == 1) {
		// 3Dオブクジェクトの描画
		particleManager->Draw();
	}

	//回復エフェクト
	if (isEffHealFlag == 1) {
		// 3Dオブクジェクトの描画
		particleHealManager->Draw();
	}

	//回復エフェクト(大)
	if (isEffHiHealFlag == 1) {
		// 3Dオブクジェクトの描画
		particleHiHealManager->Draw();
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

Vector3 Player::GetWorldPosition(){
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

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
		moveBack += { 0, 0, -0.2 };
		moveBack = bVelocity(moveBack, fbxObject3d_->wtf);
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
				fbxWeak2Object3d_->PlayAnimation();
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
			lightAttackWPos = lightAttackLPos * fbxObject3d_->wtf.matWorld;
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
				fbxWeak3Object3d_->PlayAnimation();
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
			lightAttackWPos = lightAttackLPos * fbxObject3d_->wtf.matWorld;
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
				fbxWeak4Object3d_->PlayAnimation();
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
			lightAttackWPos = lightAttackLPos * fbxObject3d_->wtf.matWorld;
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
			lightAttackWPos = lightAttackLPos * fbxObject3d_->wtf.matWorld;
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
			heavyAttackWPos = heavyAttackLPos * fbxObject3d_->wtf.matWorld;
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
			heavyAttackWPos = heavyAttackLPos * fbxObject3d_->wtf.matWorld;
		}
	}
}

void Player::Dodge() {
	dodgeTimer--;

	if (dodgeTimer > dodgeStun) {
		//回避時
		//移動速度変更
		dodgeMoveVec = dodgeMoveVecNomal;

	}
	else if (dodgeTimer > 0) {
		//硬直
		dodgeMoveVec = { 0,0,0 };

	}
	else if (dodgeTimer <= 0) {
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