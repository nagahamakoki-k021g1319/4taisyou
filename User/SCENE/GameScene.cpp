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
	delete enemyManager_;

	delete UI;
	delete buttomPng1;
	delete buttomPng2;
	delete hpGauge;
	delete unionGauge;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
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

	camWtf.Initialize();
	camWtf.position = { 0.0f, 3.0f, -8.0f };

	targetWtf.Initialize();
	targetWtf.position = { 0.0f,0.0f,targetDistance };

	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);


	//プレイヤー
	player_ = new Player();
	player_->Initialize(input);

	//エネミー
	enemyManager_ = new EnemyManager();
	enemyManager_->Initialize();
	enemyManager_->SetPlayer(player_);


	//UI
	UI = new Sprite();
	UI->Initialize(spriteCommon);
	UI->SetPozition({ 0,0 });
	UI->SetSize({1280.0f, 720.0f});

	buttomPng1 = new Sprite();
	buttomPng1->Initialize(spriteCommon);
	buttomPng1->SetPozition({ 0,0 });
	buttomPng1->SetSize({ 1280.0f, 720.0f });

	buttomPng2 = new Sprite();
	buttomPng2->Initialize(spriteCommon);
	buttomPng2->SetPozition({ 0,0 });
	buttomPng2->SetSize({ 1280.0f, 720.0f });

	hpGauge = new Sprite();
	hpGauge->Initialize(spriteCommon);
	hpGauge->SetPozition({ 0,0 });
	hpGauge->SetSize({ 1280.0f, 720.0f });

	unionGauge = new Sprite();
	unionGauge->Initialize(spriteCommon);
	unionGauge->SetPozition({ 0,0 });
	unionGauge->SetSize({ 1280.0f, 720.0f });

	spriteCommon->LoadTexture(0, "UI.png");
	UI->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "buttom1.png");
	buttomPng1->SetTextureIndex(1);
	spriteCommon->LoadTexture(2, "buttom2.png");
	buttomPng2->SetTextureIndex(2);
	spriteCommon->LoadTexture(3, "hpGauge.png");
	hpGauge->SetTextureIndex(3);
	spriteCommon->LoadTexture(4, "unionGauge.png");
	unionGauge->SetTextureIndex(4);

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	
	//仮で敵のラウンド切り替え
	if (input->TriggerKey(DIK_P)) {
		enemyManager_->creatEnemy(0);
	}else if (input->TriggerKey(DIK_O)) {
		enemyManager_->creatEnemy(1);
	}


	CamUpdate();
	enemyManager_->Update();
	player_->Update(&camWtf);


	//hpGaugeのxを(-400 + player.GeHp() * 4)動かしたい
	//unionGaugeのxを(-200 + player.GetUnion() * 2)動かしたい

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
	enemyManager_->Draw();


	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());


	//// 3Dオブクジェクトの描画


	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();

	UI->Draw();
	if (input->ButtonInput(LT)) {
		buttomPng2->Draw();
	}else {
		buttomPng1->Draw();
	}
	hpGauge->Draw();
	unionGauge->Draw();
}


void GameScene::CamMove() {
	//カメラの移動
	Vector3 eyeVelocity = { 0,0,0 };

	//入力
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

	//移動ベクトルを向いてる方向に合わせる
	eyeVelocity = bVelocity(eyeVelocity, camWtf);

	//更新
	camWtf.position += eyeVelocity;
}

void GameScene::CamRota() {
	//視点移動

	//左右
	Vector3 theta;
	if (input->StickInput(R_LEFT)) {
		theta.y = -camRotaSpeed;
	}else if (input->StickInput(R_RIGHT)) {
		theta.y = camRotaSpeed;
	}
	camWtf.rotation += theta;

	//上下
	if (input->StickInput(R_UP)) {
		targetTheta += camRotaSpeed;
	}else if (input->StickInput(R_DOWN)) {
		targetTheta += -camRotaSpeed;
	}
	
	//角度制限
	if (targetTheta < -PI / 5 * 2) {//下の制限
		targetTheta = -PI / 5 * 2;
	}else if (targetTheta > PI / 3) { //上の制限
		targetTheta = PI / 3;
	}
	
	//視点は一定の距離
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
	//y方向の制限
	if (targetWtf.matWorld.m[3][1] < 0) {
		targetWtf.matWorld.m[3][1] = 0;
	}
	camera->SetTarget({ targetWtf.matWorld.m[3][0],targetWtf.matWorld.m[3][1] ,targetWtf.matWorld.m[3][2] });

	camera->Update();
}


Vector3 GameScene::bVelocity(Vector3& velocity, Transform& worldTransform)
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