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
}

void Player::Initialize(Input* input) {
	input_ = input;

	//�v���C���[�ݒ�
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

	//�p�[�e�B�N������
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();

	//�o�f�B
	wolf_ = new Wolf();
	wolf_->Initialize();
	wolf_->SetPlayerWtf(&bodyObj_->wtf);

	//�f�o�b�O�p
	debugModel_ = Model::LoadFromOBJ("boll");
	debugObj_ = Object3d::Create();
	debugObj_->SetModel(debugModel_);

	Reset();
}

void Player::Reset() {
	bodyObj_->wtf.Initialize();
	bodyObj_->wtf.position = { 0,-3,8 };

	dash1Obj_->wtf.Initialize();
	dash1Obj_->wtf.position = { 0,-3,8 };

	dash2Obj_->wtf.Initialize();
	dash2Obj_->wtf.position = { 0,-3,8 };

	dash3Obj_->wtf.Initialize();
	dash3Obj_->wtf.position = { 0,-3,8 };

	dash4Obj_->wtf.Initialize();
	dash4Obj_->wtf.position = { 0,-3,8 };

	attack1Obj_->wtf.Initialize();
	attack1Obj_->wtf.position = { 0,-3,8 };
	
	attack2Obj_->wtf.Initialize();
	attack2Obj_->wtf.position = { 0,-3,8 };
	
	attack3Obj_->wtf.Initialize();
	attack3Obj_->wtf.position = { 0,-3,8 };
	
	attack4Obj_->wtf.Initialize();
	attack4Obj_->wtf.position = { 0,-3,8 };

	hp = defaultHp;
	isAction = 0;
	isLive = true;
	isAttackFin = false;
	nextAttack = false;

	//��U��
	lightAttackLPos = { 0,0,3 };
	//����߂̘A����
	lightAttackCount = 0;
	//�U���̓����蔻��̗L��
	isLightAttack = false;
	lightAttackTimer = 60;


	//��U��
	heavyAttackLPos = { 0,0,5 };
	//����߂̘A����
	heavyAttackCount = 0;
	//�U���̓����蔻��̗L��
	isHeavyAttack = false;
	heavyAttackTimer = 60;


	//���ݒ�
	dodgeTimer = dodgeLimit;
	isDodge = false;

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("kouka.wav");

	objRotaTimer = 0;

}

void Player::Attack() {
	if (isAction == 0) {
		//�o�f�B�w��
		if (input_->PushKey(DIK_LSHIFT) || input_->ButtonInput(LT)) {
			if (input_->PushKey(DIK_1) || input_->PButtonTrigger(B)) {
				//�ߋ���
				wolf_->Attack(1, GetWorldPosition());

			}
			else if (input_->PushKey(DIK_2) || input_->PButtonTrigger(A)) {
				//������
				wolf_->Attack(2, GetWorldPosition());

			}
			else if (input_->PushKey(DIK_3) || input_->PButtonTrigger(Y)) {
				//���ߋߋ���
				wolf_->Attack(3, GetWorldPosition());

			}
			else if (input_->PushKey(DIK_4) || input_->PButtonTrigger(X)) {
				//���߉�����
				wolf_->Attack(4, GetWorldPosition());
			}
		}
		//�{�̍U������
		else {
			//��U��
			if (input_->PushKey(DIK_4) || input_->PButtonTrigger(X)) {
				isAction = 1;
				lightAttackCount = 0;
				lightAttackTimer = lightAttackLimit[0];
				isAttackFin = false;
			}
			//���U��
			if (input_->PushKey(DIK_1) || input_->PButtonTrigger(Y)) {
				isAction = 2;
				heavyAttackCount = 0;
				heavyAttackTimer = heavyAttackLimit[0];
				isAttackFin = false;
			}
			//���
			if (input_->PushKey(DIK_3) || input_->ButtonInput(B)) {
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

	//�U���X�V
	//��U��
	else if (isAction == 1) {
		LightAttack();
	}
	//���U��
	else if (isAction == 2) {
		HeavyAttack();
	}
	//���
	else if (isAction == 3) {
		Dodge();
	}
}

void Player::OnCollision() {
	if (isInvincible == false) {
		//�����
		if (isDodge) {

		}
		//�ʏ펞
		else {
			hp -= 10;
			isEffFlag = 1;
			pSourceVoice[0] = audio->PlayWave("kouka.wav");
			pSourceVoice[0]->SetVolume(0.1f);
			isInvincible = true;
			invincibleTimer = invincibleLimit;

			if (hp < 0) {
				isLive = false;
			}
		}
	}
}

void Player::Rota() {
	if (isAction == 0) {
		if (input_->LeftStickInput()) {
			Vector2 stickVec = input_->GetLeftStickVec();

			float theta = atan2(stickVec.x, stickVec.y);

			bodyObj_->wtf.rotation.y = theta;

			dash1Obj_->wtf.rotation.y = theta;

			dash2Obj_->wtf.rotation.y = theta;

			dash3Obj_->wtf.rotation.y = theta;

			dash4Obj_->wtf.rotation.y = theta;

			attack1Obj_->wtf.rotation.y = theta;

			attack2Obj_->wtf.rotation.y = theta;

			attack3Obj_->wtf.rotation.y = theta;

			attack4Obj_->wtf.rotation.y = theta;

		}
	}
}

void Player::Update(Transform* cam) {
	if (isInvincible) {
		invincibleTimer--;
		if (invincibleTimer < 0) {
			isInvincible = false;
		}
	}

	Rota();
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


	bodyObj_->Update(cam);
	dash1Obj_->Update(cam);
	dash2Obj_->Update(cam);
	dash3Obj_->Update(cam);
	dash4Obj_->Update(cam);
	attack1Obj_->Update(cam);
	attack2Obj_->Update(cam);
	attack3Obj_->Update(cam);
	attack4Obj_->Update(cam);
	wolf_->Update(enemyPos_);

	debugObj_->Update();
}

void Player::Draw() {
	if (isLive) {
		
		//��U���̃��[�V����
		if (input_->PushKey(DIK_3) || input_->PButtonTrigger(X)) {

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
			//�ړ��̃��[�V����
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

		//�f�o�b�O�p
		if (isLightAttack) {
			debugObj_->Draw();
		}
		if (isHeavyAttack) {
			debugObj_->Draw();
		}
	}
}

void Player::EffUpdate()
{
	//�p�[�e�B�N���͈�
	for (int i = 0; i < 20; i++) {
		//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos += GetWorldPosition();
		//���x
		//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//�ǉ�
		particleManager->Add(60, pos, vel, acc, 1.0f, 0.0f);

		particleManager->Update();
	}

}

void Player::EffDraw()
{
	if (isEffFlag == 1) {
		// 3D�I�u�N�W�F�N�g�̕`��
		particleManager->Draw();
	}

}

Vector3 Player::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//����
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
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ�����
	worldPos.x = bodyObj_->wtf.matWorld.m[3][0];
	worldPos.y = bodyObj_->wtf.matWorld.m[3][1];
	worldPos.z = bodyObj_->wtf.matWorld.m[3][2];


	return worldPos;
}

bool Player::CheckAttack2Enemy(Vector3 enemyPos, float& damage) {
	//��U��
	if (isAction == 1) {
		//�����蔻�肪�o�Ă邩
		if (isLightAttack) {
			//�����蔻��
			if (col.CircleCollisionXZ(lightAttackWPos, enemyPos, 0.5f, 1.0f)) {
				damage = 3;
				return true;
			}
		}
	}

	//���U��
	else if (isAction == 2) {
		//�����蔻�肪�o�Ă邩
		if (isHeavyAttack) {
			//�����蔻��
			if (col.CircleCollisionXZ(heavyAttackWPos, enemyPos, 1.0f, 1.0f)) {
				damage = 7;
				return true;
			}
		}
	}

	return false;
}

void Player::LightAttack() {
	lightAttackTimer--;

	//1����
	if (lightAttackCount == 0) {
		//�����蔻��̏o��
		if (lightAttackTimer <= lightAttackPopTime[0] && lightAttackTimer > lightAttackDeathTime[0]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//�����蔻��̏����A�d��
		else if (lightAttackTimer <= lightAttackDeathTime[0] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//�U���̏I��
		else if (lightAttackTimer <= 0) {
			if (nextAttack) {
				//���̎a���ݒ�
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

		//�����蔻��̈ړ�
		if (isLightAttack) {
			//�ړ�
			lightAttackLPos = { 0.5f,0,2.0f };
			//�X�V
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}

		//���̎a������
		if (input_->PButtonTrigger(X)) {
			//���͎�t����
			if (lightAttackTimer < lightAttackInput[lightAttackCount] && lightAttackTimer > 0) {
				//���̎a���ݒ�
				nextAttack = true;
			}
		}
	}
	//2����
	else if (lightAttackCount == 1) {
		//�����蔻��̏o��
		if (lightAttackTimer <= lightAttackPopTime[1] && lightAttackTimer > lightAttackDeathTime[1]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//�����蔻��̏����A�d��
		else if (lightAttackTimer <= lightAttackDeathTime[1] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//�U���̏I��
		else if (lightAttackTimer <= 0) {
			if (nextAttack) {
				//���̎a���ݒ�
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

		//�����蔻��̈ړ�
		if (isLightAttack) {
			//�ړ�
			lightAttackLPos = { -0.5f,0,2.0f };
			//�X�V
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}

		//���̎a������
		if (input_->PButtonTrigger(X)) {
			//���͎�t����
			if (lightAttackTimer < lightAttackInput[lightAttackCount] && lightAttackTimer > 0) {
				//���̎a���ݒ�
				nextAttack = true;
			}
		}
	}
	//3����
	else if (lightAttackCount == 2) {
		//�����蔻��̏o��
		if (lightAttackTimer <= lightAttackPopTime[2] && lightAttackTimer > lightAttackDeathTime[2]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//�����蔻��̏����A�d��
		else if (lightAttackTimer <= lightAttackDeathTime[2] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//�U���̏I��
		else if (lightAttackTimer <= 0) {
			if (nextAttack) {
				//���̎a���ݒ�
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

		//�����蔻��̈ړ�
		if (isLightAttack) {
			//�ړ�
			lightAttackLPos = { 0.5f,0,2.0f };
			//�X�V
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}

		//���̎a������
		if (input_->PButtonTrigger(X)) {
			//���͎�t����
			if (lightAttackTimer < lightAttackInput[lightAttackCount] && lightAttackTimer > 0) {
				//���̎a���ݒ�
				nextAttack = true;
			}
		}
	}
	//4����
	else if (lightAttackCount == 3) {
		//�����蔻��̏o��
		if (lightAttackTimer <= lightAttackPopTime[0] && lightAttackTimer > lightAttackDeathTime[0]) {
			isLightAttack = true;
			isAttackFin = false;
		}
		//�����蔻��̏����A�d��
		else if (lightAttackTimer <= lightAttackDeathTime[0] && lightAttackTimer > 0) {
			isLightAttack = false;
		}
		//�U���̏I��
		else if (lightAttackTimer <= 0) {
			isAction = 0;
			isAttackFin = true;
			nextAttack = false;
		}

		//�����蔻��̈ړ�
		if (isLightAttack) {
			//�ړ�
			lightAttackLPos = { 0,0,4.0f };
			//�X�V
			lightAttackWPos = lightAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = lightAttackWPos;
		}
	}
}

void Player::HeavyAttack() {
	heavyAttackTimer--;

	//1����
	if (heavyAttackCount == 0) {
		//�����蔻��̏o��
		if (heavyAttackTimer <= heavyAttackPopTime[0] && heavyAttackTimer > heavyAttackDeathTime[0]) {
			isHeavyAttack = true;
			isAttackFin = false;
		}
		//�����蔻��̏����A�d��
		else if (heavyAttackTimer <= heavyAttackDeathTime[0] && heavyAttackTimer > 0) {
			isHeavyAttack = false;
		}
		//�U���̏I��
		else if (heavyAttackTimer <= 0) {
			if (nextAttack) {
				//���̎a���ݒ�
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

		//�����蔻��̈ړ�
		if (isHeavyAttack) {
			//�ړ�
			heavyAttackLPos = { 0,0,4.0f };
			//�X�V
			heavyAttackWPos = heavyAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = heavyAttackWPos;
		}

		//���̎a������
		if (input_->PButtonTrigger(Y)) {
			//���͎�t����
			if (heavyAttackTimer < heavyAttackInput[heavyAttackCount] && heavyAttackTimer > 0) {
				//���̎a���ݒ�
				nextAttack = true;
			}
		}
	}
	//2����
	else if (heavyAttackCount == 1) {
		//�����蔻��̏o��
		if (heavyAttackTimer <= heavyAttackPopTime[1] && heavyAttackTimer > heavyAttackDeathTime[1]) {
			isHeavyAttack = true;
			isAttackFin = false;
		}
		//�����蔻��̏����A�d��
		else if (heavyAttackTimer <= heavyAttackDeathTime[1] && heavyAttackTimer > 0) {
			isHeavyAttack = false;
		}
		//�U���̏I��
		else if (heavyAttackTimer <= 0) {
			isAction = 0;
			isAttackFin = true;
			nextAttack = false;
		}

		//�����蔻��̈ړ�
		if (isHeavyAttack) {
			//�ړ�
			heavyAttackLPos = { 0,0,8.0f };
			//�X�V
			heavyAttackWPos = heavyAttackLPos * bodyObj_->wtf.matWorld;
			debugObj_->wtf.position = heavyAttackWPos;
		}
	}
}

void Player::Dodge() {
	dodgeTimer--;

	if (dodgeTimer > dodgeStun) {
		//�����
		//�ړ����x�ύX
		dodgeMoveVec = dodgeMoveVecNomal * (0.4f * pow((30 / dodgeLimit), 2));
	}
	else {
		//�d��
		isDodge = false;
		dodgeMoveVec = { 0,0,0 };
	}

	if (dodgeTimer < 0) {
		isAction = 0;
	}
}