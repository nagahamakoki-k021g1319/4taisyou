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
	delete mpGauge;
	delete unionGauge;
	delete titlePic;
	delete selectPic;
	delete clearPic;
	delete gameoverPic;
	delete floor;
	delete skydome;
	delete sordUI;
	delete sord2UI;
	delete srr;
	delete srl;
	delete sru;
	delete srd;
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

	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	floorMD = Model::LoadFromOBJ("floor");
	floor = Object3d::Create();
	floor->SetModel(floorMD);
	floor->wtf.position = (Vector3{ 0, -10, 0 });

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	fieldMD = Model::LoadFromOBJ("field");
	field = Object3d::Create();
	field->SetModel(fieldMD);
	field->wtf.scale = (Vector3{ 2, 2, 2 });

	//プレイヤー
	player_ = new Player();
	player_->Initialize(input);
	player_->SetCamera(camera);

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
	hpPosition = hpGauge->GetPosition();
	hpGauge->SetPozition(hpPosition);
	hpGauge->SetSize({ 1280.0f, 720.0f });

	mpGauge = new Sprite();
	mpGauge->Initialize(spriteCommon);
	mpPosition = mpGauge->GetPosition();
	mpGauge->SetPozition(mpPosition);
	mpGauge->SetSize({ 1280.0f, 720.0f });

	unionGauge = new Sprite();
	unionGauge->Initialize(spriteCommon);
	unionGauge->SetPozition({ 0,0 });
	unionScale = unionGauge->GetPosition();
	unionScale.x = 1280.0f;
	unionScale.y = 720.0f;
	unionGauge->SetSize(unionScale);

	//ゲームフロー
	scene = Scene::Title;
	stage = 0;

	titlePic = new Sprite();
	titlePic->Initialize(spriteCommon);
	titlePic->SetPozition({ 0,0 });
	titlePic->SetSize({ 1280,720 });

	selectPic = new Sprite();
	selectPic->Initialize(spriteCommon);
	selectPic->SetPozition({ 0,0 });
	selectPic->SetSize({ 1280,720 });

	clearPic = new Sprite();
	clearPic->Initialize(spriteCommon);
	clearPic->SetPozition({ 0,0 });
	clearPic->SetSize({ 1280,720 });

	gameoverPic = new Sprite();
	gameoverPic->Initialize(spriteCommon);
	gameoverPic->SetPozition({ 0,0 });
	gameoverPic->SetSize({ 1280,720 });

	sordUI = new Sprite();
	sordUI->Initialize(spriteCommon);
	sordUI->SetPozition({ 0,0 });
	sordUI->SetSize({ 1280,720 });

	sord2UI = new Sprite();
	sord2UI->Initialize(spriteCommon);
	sord2UI->SetPozition({ 0,0 });
	sord2UI->SetSize({ 1280,720 });

	srr = new Sprite();
	srr->Initialize(spriteCommon);
	srrPosition = srr->GetPosition();
	srr->SetPozition(srrPosition);
	srr->SetSize({ 1280.0f, 720.0f });

	srl = new Sprite();
	srl->Initialize(spriteCommon);
	srlPosition = srl->GetPosition();
	srl->SetPozition(srlPosition);
	srl->SetSize({ 1280.0f, 720.0f });

	sru = new Sprite();
	sru->Initialize(spriteCommon);
	sruPosition = sru->GetPosition();
	sru->SetPozition(sruPosition);
	sru->SetSize({ 1280.0f, 720.0f });

	srd = new Sprite();
	srd->Initialize(spriteCommon);
	srdPosition = srd->GetPosition();
	srd->SetPozition(srdPosition);
	srd->SetSize({ 1280.0f, 720.0f });

	
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
	spriteCommon->LoadTexture(5, "title.png");
	titlePic->SetTextureIndex(5);
	spriteCommon->LoadTexture(6, "select.png");
	selectPic->SetTextureIndex(6);
	spriteCommon->LoadTexture(7, "clear.png");
	clearPic->SetTextureIndex(7);
	spriteCommon->LoadTexture(8, "gameover.png");
	gameoverPic->SetTextureIndex(8);
	spriteCommon->LoadTexture(9, "migi.png");
	sordUI->SetTextureIndex(9);
	spriteCommon->LoadTexture(10, "migi2.png");
	sord2UI->SetTextureIndex(10);
	spriteCommon->LoadTexture(11, "srr.png");
	srr->SetTextureIndex(11);
	spriteCommon->LoadTexture(12, "srl.png");
	srl->SetTextureIndex(12);
	spriteCommon->LoadTexture(13, "sru.png");
	sru->SetTextureIndex(13);
	spriteCommon->LoadTexture(14, "srd.png");
	srd->SetTextureIndex(14);
	spriteCommon->LoadTexture(15, "mpGauge.png");
	mpGauge->SetTextureIndex(15);

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("tit.wav");
	audio->LoadWave("bb.wav");
	audio->LoadWave("serect.wav");
	audio->LoadWave("open.wav");

	Reset();
}

void GameScene::Reset() {
	player_->Reset();
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	switch (scene)
	{
	case Scene::Title:
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Select;
			pSourceVoice[3] = audio->PlayWave("open.wav");
			pSourceVoice[3]->SetVolume(0.4f);
		}

		//音声再生
		if (soundCheckFlag == 0) {
			//音声再生

			pSourceVoice[0] = audio->PlayWave("tit.wav");
			pSourceVoice[0]->SetVolume(0.1f);
			soundCheckFlag = 1;
		}

		sruPosition.x = 0.0f;
		sruPosition.y = 0.0f;
		sru->SetPozition(sruPosition);

		srdPosition.x = 0.0f;
		srdPosition.y = 0.0f;
		srd->SetPozition(srdPosition);
		
		srrPosition.x = 0.0f;
		srr->SetPozition(srrPosition);

		srlPosition.x = 0.0f;
		srl->SetPozition(srlPosition);

		enemyManager_->EffTimer = 0;
		enemyManager_->isEffFlag = 0;
		player_->EffTimer = 0;
		player_->isEffFlag = 0;
		
		break;
	case Scene::Select:
		sruPosition.x -= 50.0f;
		sruPosition.y -= 10.0f;
		sru->SetPozition(sruPosition);

		srdPosition.x += 50.0f;
		srdPosition.y += 10.0f;
		srd->SetPozition(srdPosition);
		//ステージの選択
		if(input->LeftStickInput()) {
			if (input->PStickTrigger(L_LEFT)) {
				//音声再生
				pSourceVoice[2] = audio->PlayWave("serect.wav");
				pSourceVoice[2]->SetVolume(0.6f);
				stage = 0;
			}else if (input->PStickTrigger(L_RIGHT)){
				//音声再生
				pSourceVoice[2] = audio->PlayWave("serect.wav");
				pSourceVoice[2]->SetVolume(0.6f);
				stage = 1;
			}
		}

		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			if (stage == 0) {
				enemyManager_->creatEnemy(stage);
				Reset();
				scene = Scene::Play;
				pSourceVoice[3] = audio->PlayWave("open.wav");
				pSourceVoice[3]->SetVolume(0.4f);
			}
		}
		break;
	case Scene::Play:
		pSourceVoice[0]->Stop();
		soundCheckFlag = 0;
		//音声再生
		if (soundCheckFlag2 == 0) {
			//音声再生
			pSourceVoice[1] = audio->PlayWave("bb.wav");
			pSourceVoice[1]->SetVolume(0.1f);
			soundCheckFlag2 = 1;
		}
		CdTimer++;
	
		srrPosition.x -= 30.0f;
		srr->SetPozition(srrPosition);
		
		srlPosition.x += 30.0f;
		srl->SetPozition(srlPosition);

		
		enemyManager_->Update();
		
		player_->Update();



		if (enemyManager_->isHitStop) {
			hitStopTimer--;
			if (hitStopTimer < 0) {
				enemyManager_->isHitStop = false;
			}
		}else{
			hitStopTimer = hitStopLimit;
			enemyManager_->Update();
			player_->Update();
		}

		hpGauge->SetPozition({ -400.0f + player_->GetHp() * 4 ,0 });
		mpGauge->SetPozition({ -300.0f + player_->GetMp() * 3,0 });
    

		floor->Update();
		skydome->Update();
		field->Update();

		//シーン切り替え
		if (player_->GetHp() < 0) {
			scene = Scene::Gameover;
		}else if (enemyManager_->IsAllEnemyDead()) {
			scene = Scene::Clear;
		}
		break;
	case Scene::Clear:
		pSourceVoice[1]->Stop();
		soundCheckFlag2 = 0;
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Title;
			pSourceVoice[2] = audio->PlayWave("serect.wav");
			pSourceVoice[2]->SetVolume(0.6f);
		}
		break;
	case Scene::Gameover:
		pSourceVoice[1]->Stop();
		soundCheckFlag2 = 0;
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Title;
			pSourceVoice[2] = audio->PlayWave("serect.wav");
			pSourceVoice[2]->SetVolume(0.6f);
		}
		break;
	}
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
	switch (scene)
	{
	case Scene::Title:

		break;
	case Scene::Play:
		
		player_->Draw();
		enemyManager_->Draw();
		
    
		floor->Draw();
		skydome->Draw();
		field->Draw();
		break;
	case Scene::Clear:


		break;
	case Scene::Gameover:


		break;
	}
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();


	//// パーティクル UI スプライト描画
	switch (scene)
	{
	case Scene::Title:
		titlePic->Draw();

		break;
	case Scene::Select:
		selectPic->Draw();
		
		//ステージ選択わかりやすく
		if (stage == 0) {sordUI->Draw();}
		else if (stage == 1) { sord2UI->Draw(); }

		
		sru->Draw();
		srd->Draw();
		break;
	case Scene::Play:
		
		// パーティクル描画前処理
	/*	ParticleManager::PreDraw(dxCommon->GetCommandList());*/
		player_->EffDraw();
		enemyManager_->EffDraw();
		//// パーティクル描画後処理
		//ParticleManager::PostDraw();
		
		UI->Draw();
		if (input->ButtonInput(LT)) {
			buttomPng2->Draw();
		}
		else {
			buttomPng1->Draw();
		}
		hpGauge->Draw();
		mpGauge->Draw();

		srr->Draw();
		srl->Draw();

		break;
	case Scene::Clear:
		clearPic->Draw();

		break;
	case Scene::Gameover:
		gameoverPic->Draw();

		break;
	}
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