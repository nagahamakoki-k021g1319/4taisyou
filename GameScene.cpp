#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//オーディオ解放
	audio->Finalize();
	delete audio;
	delete player_;
	delete enemy_;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(gamescene);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	//ビュー
	{
		view = new View();
		view->Initialize();
		view->eye = { 0,3,-8 };
	}
	
	audio = new Audio();
	audio->Initialize();


	//プレイヤー
	player_ = new Player();
	player_->Initialize(input);
	//player_->SetView(view);

	//エネミー
	enemy_ = new Enemy();
	enemy_->Initialize();
	enemy_->SetView(view);
}


void GameScene::Update() {
	player_->Update();
	enemy_->Update();


}

void GameScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>


	//3Dオブジェクトの描画
	player_->Draw();
	enemy_->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

}

