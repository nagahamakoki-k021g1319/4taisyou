#include "GameScene.h"


/// <summary>
	/// �R���X�g�N���^
	/// </summary>
GameScene::GameScene() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene() {
	delete spriteCommon;
	delete camera;
	delete player_;
	delete enemy_;
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// null�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	camWtf.Initialize();
	camWtf.position = {0.0f, 3.0f, -8.0f};

	targetWtf.Initialize();
	targetWtf.position = { 0.0f,0.0f,targetDistance };

	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);


	//�v���C���[
	player_ = new Player();
	player_->Initialize(input);

	//�G�l�~�[
	enemy_ = new Enemy();
	enemy_->Initialize(input);
	enemy_->SetPlayer(player_);

}

/// <summary>
/// ���t���[������
/// </summary>
void GameScene::Update() {

	CamUpdate();
	//player_->Update();
	enemy_->Update();
	

}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw() {

	/// <summary>
	/// 3D�I�u�W�F�N�g�̕`��
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>
	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	

	//// 3D�I�u�N�W�F�N�g�̕`��
	player_->Draw();
	enemy_->Draw();


	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// 3D�I�u�W�F�N�g�`��O����
	ParticleManager::PreDraw(dxCommon->GetCommandList());


	//// 3D�I�u�N�W�F�N�g�̕`��


	// 3D�I�u�W�F�N�g�`��㏈��
	ParticleManager::PostDraw();

}


void GameScene::CamMove() {
	//�J�����̈ړ�
	Vector3 eyeVelocity = { 0,0,0 };

	//����
	if (input->StickInput(L_UP)) {
		eyeVelocity.z = camMoveSpeed;
	}else if (input->StickInput(L_DOWN)) {
		eyeVelocity.z = -camMoveSpeed;
	}
	if (input->StickInput(L_LEFT)) {
		eyeVelocity.x = -camMoveSpeed;
	}else if (input->StickInput(L_RIGHT)) {
		eyeVelocity.x = camMoveSpeed;
	}

	//�ړ��x�N�g���������Ă�����ɍ��킹��
	eyeVelocity = bVelocity(eyeVelocity, camWtf);

	//�X�V
	camWtf.position += eyeVelocity;
}


void GameScene::CamRota() {
	//���_�ړ�

	//���E
	Vector3 theta;
	if (input->StickInput(R_LEFT)) {
		theta.y = -camRotaSpeed;
	}else if (input->StickInput(R_RIGHT)) {
		theta.y = camRotaSpeed;
	}
	camWtf.rotation += theta;

	//�㉺
	if (input->StickInput(R_UP)) {
		targetTheta += camRotaSpeed;
	}else if (input->StickInput(R_DOWN)) {
		targetTheta += -camRotaSpeed;
	}
	
	//�p�x����
	if (targetTheta < -PI / 5 * 2) {//���̐���
		targetTheta = -PI / 5 * 2;
	}else if (targetTheta > PI / 3) { //��̐���
		targetTheta = PI / 3;
	}
	
	//���_�͈��̋���
	targetWtf.position.z = cos(targetTheta) * targetDistance;
	targetWtf.position.y = sin(targetTheta) * targetDistance;
}

void GameScene::CamUpdate() {
	CamMove();
	CamRota();

	camWtf.UpdateMat();

	camera->SetEye(camWtf.position);

	targetWtf.UpdateMat();
	targetWtf.matWorld *= camWtf.matWorld;
	//y�����̐���
	if (targetWtf.matWorld.m[3][1] < 0) {
		targetWtf.matWorld.m[3][1] = 0;
	}
	camera->SetTarget({ targetWtf.matWorld.m[3][0],targetWtf.matWorld.m[3][1] ,targetWtf.matWorld.m[3][2] });

	camera->Update();
}


Vector3 GameScene::bVelocity(Vector3& velocity, Transform& worldTransform)
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