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
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input){
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
	camera->SetEye({ 0.0f,5.0f,-10.0f });
	camera->SetTarget({ 0.0f,0.0f,0.0f });
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);


	//�v���C���[
	player_ = new Player();
	player_->Initialize(input);

	//�G�l�~�[
	enemy_ = new Enemy();
	enemy_->Initialize();

}

/// <summary>
/// ���t���[������
/// </summary>
void GameScene::Update() {

	camera->Update();
	player_->Update();
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