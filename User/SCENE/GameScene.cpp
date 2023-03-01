#include "GameScene.h"

/// <summary>
	/// コンストクラタ
	/// </summary>
GameScene::GameScene() {
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {
	delete spriteCommon;
	delete camera;
	delete player_;
	delete enemy_;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input){
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	camera->SetEye({ 0.0f,5.0f,-10.0f });
	camera->SetTarget({ 0.0f,0.0f,0.0f });
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);


	//プレイヤー
	player_ = new Player();
	player_->Initialize(input);

	//エネミー
	enemy_ = new Enemy();
	enemy_->Initialize();

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {

	camera->Update();
	player_->Update();
	enemy_->Update();

}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	/// <summary>
	/// 3Dオブジェクトの描画
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	

	//// 3Dオブクジェクトの描画
	player_->Draw();
	enemy_->Draw();


	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());


	//// 3Dオブクジェクトの描画


	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();

}