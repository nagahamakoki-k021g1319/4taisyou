#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//�I�[�f�B�I���
	audio->Finalize();
	delete audio;
	delete player_;
	delete enemy_;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(gamescene);

	this->dxCommon = dxCommon;
	this->input = input;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	//�r���[
	{
		view = new View();
		view->Initialize();
		view->eye = { 0,3,-8 };
	}
	
	audio = new Audio();
	audio->Initialize();


	//�v���C���[
	player_ = new Player();
	player_->Initialize(input);
	//player_->SetView(view);

	//�G�l�~�[
	enemy_ = new Enemy();
	enemy_->Initialize();
	enemy_->SetView(view);
}


void GameScene::Update() {
	player_->Update();
	enemy_->Update();


}

void GameScene::Draw() {
	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	
	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>


	//3D�I�u�W�F�N�g�̕`��
	player_->Draw();
	enemy_->Draw();

	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

}

