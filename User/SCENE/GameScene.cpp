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
	delete mainCamera;
	delete camera1;
	delete camera2;
	delete camera3;
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
	delete sord3UI;
	delete srr;
	delete srl;
	delete sru;
	delete srd;
	delete std3;
	delete std2;
	delete std1;
	delete stdgo;
	delete stdgo2;
	delete pauseBg;

	delete buttomx;
	delete buttomy;
	delete buttomb;

	delete option2;
	delete option3; 
	delete option4; 
	delete option5;
	delete optionco;

	delete mouse;
	delete markPointer;
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
	mainCamera = new Camera(WinApp::window_width, WinApp::window_height);
	camera1 = new Camera(WinApp::window_width, WinApp::window_height);
	camera2 = new Camera(WinApp::window_width, WinApp::window_height);
	camera3 = new Camera(WinApp::window_width, WinApp::window_height);

	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

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
	player_->Initialize(dxCommon,input);
	player_->SetCamera(mainCamera);

	//エネミー
	enemyManager_ = new EnemyManager();
	enemyManager_->Initialize(dxCommon);
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

	buttomx = new Sprite();
	buttomx->Initialize(spriteCommon);
	buttomx->SetPozition({ 0,0 });
	buttomx->SetSize({ 1280.0f, 720.0f });

	buttomy = new Sprite();
	buttomy->Initialize(spriteCommon);
	buttomy->SetPozition({ 0,0 });
	buttomy->SetSize({ 1280.0f, 720.0f });

	buttomb = new Sprite();
	buttomb->Initialize(spriteCommon);
	buttomb->SetPozition({ 0,0 });
	buttomb->SetSize({ 1280.0f, 720.0f });

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

	sord3UI = new Sprite();
	sord3UI->Initialize(spriteCommon);
	sord3UI->SetPozition({ 0,0 });
	sord3UI->SetSize({ 1280,720 });

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

	std3 = new Sprite();
	std3->Initialize(spriteCommon);
	std3->SetPozition({ 0,0 });
	std3->SetSize({ 1280,720 });

	std2 = new Sprite();
	std2->Initialize(spriteCommon);
	std2->SetPozition({ 0,0 });
	std2->SetSize({ 1280,720 });

	std1 = new Sprite();
	std1->Initialize(spriteCommon);
	std1->SetPozition({ 0,0 });
	std1->SetSize({ 1280,720 });

	stdgo = new Sprite();
	stdgo->Initialize(spriteCommon);
	stdgo->SetPozition({ 0,0 });
	stdgo->SetSize({ 1280,720 });

	stdgo2 = new Sprite();
	stdgo2->Initialize(spriteCommon);
	stdgo2->SetPozition({ 0,0 });
	stdgo2->SetSize({ 1280,720 });

	pauseBg = new Sprite();
	pauseBg->Initialize(spriteCommon);
	pauseBg->SetPozition({ 0,0 });
	pauseBg->SetSize({ 1280,720 });

	optionPic = new Sprite();
	optionPic->Initialize(spriteCommon);
	optionPic->SetPozition({ 0,0 });
	optionPic->SetSize({ 1280,720 });

	option2 = new Sprite();
	option2->Initialize(spriteCommon);
	option2->SetPozition({ 0,0 });
	option2->SetSize({ 1280,720 });

	option3 = new Sprite();
	option3->Initialize(spriteCommon);
	option3->SetPozition({ 0,0 });
	option3->SetSize({ 1280,720 });

	option4 = new Sprite();
	option4->Initialize(spriteCommon);
	option4->SetPozition({ 0,0 });
	option4->SetSize({ 1280,720 });

	option5 = new Sprite();
	option5->Initialize(spriteCommon);
	option5->SetPozition({ 0,0 });
	option5->SetSize({ 1280,720 });

	optionco = new Sprite();
	optionco->Initialize(spriteCommon);
	optionco->SetPozition({ 0,0 });
	optionco->SetSize({ 1280,720 });


	Sensitivity = 10;

	mouse = new Sprite();
	mouse->Initialize(spriteCommon);
	mousePosition = mouse->GetPosition();
	mousePosition.x = Sensitivity * 24.35 + 460;
	player_->SetSensitivity(Sensitivity);
	mousePosition.y = 486.0f;
	mouse->SetPozition(mousePosition);
	mouse->SetSize({ 33,35 });

	markPointer = new Sprite();
	markPointer->Initialize(spriteCommon);
	mapoPosition = markPointer->GetPosition();
	mapoPosition.x = Sensitivity * 24.35 + 460;
	player_->SetSensitivity(Sensitivity);
	mapoPosition.y = 486.0f;
	markPointer->SetPozition(mapoPosition);
	markPointer->SetSize({ 33,35 });


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
	spriteCommon->LoadTexture(6, "tuto2.png");
	selectPic->SetTextureIndex(6);
	spriteCommon->LoadTexture(7, "clear.png");
	clearPic->SetTextureIndex(7);
	spriteCommon->LoadTexture(8, "gameover.png");
	gameoverPic->SetTextureIndex(8);
	spriteCommon->LoadTexture(9, "tutoframe1.png");
	sordUI->SetTextureIndex(9);
	spriteCommon->LoadTexture(10, "tutoframe2.png");
	sord2UI->SetTextureIndex(10);
	spriteCommon->LoadTexture(26, "tutoframe3.png");
	sord3UI->SetTextureIndex(26);
	spriteCommon->LoadTexture(11, "srr1.png");
	srr->SetTextureIndex(11);
	spriteCommon->LoadTexture(12, "srl1.png");
	srl->SetTextureIndex(12);
	spriteCommon->LoadTexture(13, "sru.png");
	sru->SetTextureIndex(13);
	spriteCommon->LoadTexture(14, "srd.png");
	srd->SetTextureIndex(14);
	spriteCommon->LoadTexture(15, "mpGauge.png");
	mpGauge->SetTextureIndex(15);
	
	spriteCommon->LoadTexture(16, "std3.png");
	std3->SetTextureIndex(16);
	spriteCommon->LoadTexture(17, "std2.png");
	std2->SetTextureIndex(17);
	spriteCommon->LoadTexture(18, "std1.png");
	std1->SetTextureIndex(18);
	spriteCommon->LoadTexture(19, "stdgo.png");
	stdgo->SetTextureIndex(19);
	spriteCommon->LoadTexture(20, "stdgo2.png");
	stdgo2->SetTextureIndex(20);

	//ポーズ画面
	spriteCommon->LoadTexture(21, "asedt1.png");
	pauseBg->SetTextureIndex(21);

	//オプション画面
	spriteCommon->LoadTexture(22, "option1.png");
	optionPic->SetTextureIndex(22);

	spriteCommon->LoadTexture(23, "botomx.png");
	buttomx->SetTextureIndex(23);
	spriteCommon->LoadTexture(24, "botomy.png");
	buttomy->SetTextureIndex(24);
	spriteCommon->LoadTexture(25, "botomb.png");
	buttomb->SetTextureIndex(25);

	spriteCommon->LoadTexture(27, "option2.png");
	option2->SetTextureIndex(27);
	spriteCommon->LoadTexture(28, "option3.png");
	option3->SetTextureIndex(28);
	spriteCommon->LoadTexture(29, "option4.png");
	option4->SetTextureIndex(29);
	spriteCommon->LoadTexture(30, "option5.png");
	option5->SetTextureIndex(30);
	
	spriteCommon->LoadTexture(31, "optionco2.png");
	optionco->SetTextureIndex(31);

	spriteCommon->LoadTexture(32, "markpoint.png");
	mouse->SetTextureIndex(32);

	spriteCommon->LoadTexture(33, "markpoint.png");
	markPointer->SetTextureIndex(33);

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("tit.wav");
	audio->LoadWave("bb.wav");
	audio->LoadWave("serect.wav");
	audio->LoadWave("open.wav");
	audio->LoadWave("clear.wav");
	audio->LoadWave("over.wav");

	Reset();
}

void GameScene::Reset() {
	player_->Reset();

	camera1->SetEye({ 0, 1, 6 });
	camera1->SetTarget({ 0,3,0 });
	camera2->SetEye({ -4, 4, 4 });
	camera2->SetTarget({ 0,3,0 });
	camera3->SetEye({ 4, 4, 4 });
	camera3->SetTarget({ 0,3,0 });

	actionStopTimer = actionStopLimit;
	isActionStop = true;
	player_->isActionStop = isActionStop;
	enemyManager_->isActionStop = isActionStop;

	enemyManager_->EffTimer = 0;
	enemyManager_->isEffFlag = 0;
	enemyManager_->EffFireTimer = 0;
	enemyManager_->isEffFireFlag = 0;

	player_->EffTimer = 0;
	player_->isEffFlag = 0;

	player_->EffHealTimer = 0;
	player_->isEffHealFlag = 0;

	isPause = false;


}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	switch (scene)
	{
	case Scene::Title:
		soundCheckFlag3 = 0;
		soundCheckFlag4 = 0;
		
		mapoPosition.x = Sensitivity * 24.35 + 460;
		markPointer->SetPozition(mapoPosition);
		//感度更新
		player_->SetSensitivity(Sensitivity);
		mousePosition.x = Sensitivity * 24.35 + 460;
		mouse->SetPozition(mousePosition);
		//感度更新
		player_->SetSensitivity(Sensitivity);

		//シーン切り替え
		if (input->PButtonTrigger(B) || input->TriggerKey(DIK_SPACE)) {
			selectMode = 0;
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

		
		
		break;
	case Scene::Select:
		sruPosition.x -= 80.0f;
		sruPosition.y -= 10.0f;
		sru->SetPozition(sruPosition);

		srdPosition.x += 80.0f;
		srdPosition.y += 10.0f;
		srd->SetPozition(srdPosition);

		//0.ゲームプレイ、1.オプション、2.タイトルへ
		if (input->LeftStickInput()) {
			if (input->PStickTrigger(L_LEFT)) {
				pSourceVoice[2] = audio->PlayWave("serect.wav");
				pSourceVoice[2]->SetVolume(0.6f);
				selectMode = 1;

			}else if(input->PStickTrigger(L_RIGHT)) {
				pSourceVoice[2] = audio->PlayWave("serect.wav");
				pSourceVoice[2]->SetVolume(0.6f);
				selectMode = 2;
			}else if (input->PStickTrigger(L_UP)) {
				pSourceVoice[2] = audio->PlayWave("serect.wav");
				pSourceVoice[2]->SetVolume(0.6f);
				selectMode = 0;
			}else if (input->PStickTrigger(L_DOWN)) {
				pSourceVoice[2] = audio->PlayWave("serect.wav");
				pSourceVoice[2]->SetVolume(0.6f);
				selectMode = 1;
			}
		}

		if (input->PButtonTrigger(B)) {
			if (selectMode == 0) {
				//ゲームプレイ
				enemyManager_->creatEnemy(stage);
				Reset();
				pSourceVoice[4] = audio->PlayWave("open.wav");
				pSourceVoice[4]->SetVolume(0.4f);
				scene = Scene::Play;
			}else if (selectMode == 1) {
				//オプション

				pSourceVoice[3] = audio->PlayWave("open.wav");
				pSourceVoice[3]->SetVolume(0.4f);

				selecOtption = 0;

				scene = Scene::Option;
			}else if (selectMode == 2) {
				//タイトルへ
				pSourceVoice[3] = audio->PlayWave("open.wav");
				pSourceVoice[3]->SetVolume(0.4f);
		
				srd->SetPozition(srdPosition);
				scene = Scene::Title;
			}
		}

		break;
	case Scene::Play:
		mapoPosition.x = Sensitivity * 24.35 + 460;
		markPointer->SetPozition(mapoPosition);
		//感度更新
		player_->SetSensitivity(Sensitivity);
		mousePosition.x = Sensitivity * 24.35 + 460;
		mouse->SetPozition(mousePosition);
		//感度更新
		player_->SetSensitivity(Sensitivity);
		//ポーズ切り替え
		if (input->PButtonTrigger(START)) {
			if (isPause == false) {
				pauseSelect = 0;
				isActionStop = true;
				player_->isActionStop = isActionStop;
				enemyManager_->isActionStop = isActionStop;
				isPause = true;
			}else {
				isActionStop = false;
				keycon = false;
				player_->isActionStop = isActionStop;
				enemyManager_->isActionStop = isActionStop;
				isPause = false;
			}
		}if (isPause) {
			//ポーズ画面
			if (keycon == false) {
				if (input->LeftStickInput()) {
					//選択切り替え
					if (input->PStickTrigger(L_UP)) {
						pauseSelect--;
						if (pauseSelect < 0) {
							pauseSelect = 3;
						}
					}
					else if (input->PStickTrigger(L_DOWN)) {
						pauseSelect++;
						if (pauseSelect > 3) {
							pauseSelect = 0;
						}
					}
				}
				//決定
				if (input->PButtonTrigger(B)) {
					if (pauseSelect == 0) {
						//再開
						isPause = false;
					}
					else if (pauseSelect == 1) {
						//リセット
						enemyManager_->creatEnemy(stage);
						Reset();
						scene = Scene::Play;
					}
					else if (pauseSelect == 2) {
						//キーコン
						selecOtption = 0;
						keycon = true;
					}
					else if (pauseSelect == 3) {
						//タイトルへ
						pSourceVoice[1]->Stop();
						soundCheckFlag2 = 0;
						scene = Scene::Title;
					}
				}
			}else if (keycon == true) {
				isChangeSensitivity = true;
				//キーコン
				if (isChangeSensitivity) {
					//感度変更
					if (input->LeftStickInput()) {
						float add = 0.1;
						if (input->StickInput(L_LEFT)) {
							Sensitivity -= add;
						}
						else if (input->StickInput(L_RIGHT)) {
							Sensitivity += add;
							
						}
						if (Sensitivity <= 0.01) {
							Sensitivity = 0.01;
						}
						else if (Sensitivity >= 20.0) {
							Sensitivity = 20.0;
						}
						mapoPosition.x = Sensitivity * 24.35 + 460;
						markPointer->SetPozition(mapoPosition);

						mousePosition.x = Sensitivity * 24.35 + 460;
						mouse->SetPozition(mousePosition);
						//感度更新
						player_->SetSensitivity(Sensitivity);
					}

					if (input->PButtonTrigger(A)) {
						selecOtption = 1;
					}
					if (selecOtption == 1) {
						//ポーズ画面へ戻る
						pauseSelect = 0;
						keycon = false;
					}

				}
				
			}
		}else {
			//ゲーム画面
			actionStopTimer--;
			camera1->Update();
			camera2->Update();
			camera3->Update();
			if (actionStopTimer > 60 * 2) {
				camera1->SetEye(camera1->GetEye() + Vector3{ 0, 0.05f, 0 });
				ParticleManager::SetCamera(camera1);
				Object3d::SetCamera(camera1);
				FBXObject3d::SetCamera(camera1);
			}
			else if (actionStopTimer > 60 * 1) {
				camera2->SetEye(camera2->GetEye() + Vector3{ 0.05f, 0, 0 });
				ParticleManager::SetCamera(camera2);
				Object3d::SetCamera(camera2);
				FBXObject3d::SetCamera(camera2);
			}
			else if (actionStopTimer > 0) {
				camera3->SetEye(camera3->GetEye() + Vector3{ -0.05f, 0, 0 });
				ParticleManager::SetCamera(camera3);
				Object3d::SetCamera(camera3);
				FBXObject3d::SetCamera(camera3);
			}
			else if (actionStopTimer <= 0) {
				ParticleManager::SetCamera(mainCamera);
				Object3d::SetCamera(mainCamera);
				FBXObject3d::SetCamera(mainCamera);
				isActionStop = false;
				player_->isActionStop = isActionStop;
				enemyManager_->isActionStop = isActionStop;
			}

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

			srrPosition.x -= 80.0f;
			srr->SetPozition(srrPosition);

			srlPosition.x += 80.0f;
			srl->SetPozition(srlPosition);

			if (enemyManager_->isHitStop) {
				hitStopTimer--;
				if (hitStopTimer < 0) {
					enemyManager_->isHitStop = false;
				}
			}
			else {
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
			}
			else if (enemyManager_->IsAllEnemyDead()) {
				scene = Scene::Clear;
			}
		}
		break;
	case Scene::Clear:
		pSourceVoice[1]->Stop();
		soundCheckFlag2 = 0;
		
		//音声再生
		if (soundCheckFlag3 == 0) {
			//音声再生

			pSourceVoice[5] = audio->PlayWave("clear.wav");
			pSourceVoice[5]->SetVolume(0.3f);
			soundCheckFlag3 = 1;
		}
		
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
		//音声再生
		if (soundCheckFlag4 == 0) {
			//音声再生
			pSourceVoice[6] = audio->PlayWave("over.wav");
			pSourceVoice[6]->SetVolume(0.3f);
			soundCheckFlag4 = 1;
		}
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Title;
			pSourceVoice[2] = audio->PlayWave("serect.wav");
			pSourceVoice[2]->SetVolume(0.6f);
		}
		break;
	case Scene::Option:
		isChangeSensitivity = true;
		
		if (isChangeSensitivity) {
			//感度変更
			if (input->LeftStickInput()) {
				float add = 0.1;
				if (input->StickInput(L_LEFT)) {
					Sensitivity -= add;
				}else if (input->StickInput(L_RIGHT)) {
					Sensitivity += add;
				}
				if (Sensitivity <= 0.01) {
					Sensitivity = 0.01;
				}
				else if (Sensitivity >= 20.0) {
					Sensitivity = 20.0;
				}

				mousePosition.x = Sensitivity * 24.35 + 460;
				mouse->SetPozition(mousePosition);

				mapoPosition.x = Sensitivity * 24.35 + 460;
				markPointer->SetPozition(mapoPosition);
				//感度更新
				player_->SetSensitivity(Sensitivity);
			}

			//オプション画面操作
			if (input->PButtonTrigger(A)) {
				//セレクト画面へ戻る
				pSourceVoice[3] = audio->PlayWave("open.wav");
				pSourceVoice[3]->SetVolume(0.4f);
				scene = Scene::Select;
			}
		}
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

	//// パーティクル UI FBX スプライト描画
	switch (scene)
	{
	case Scene::Title:
		titlePic->Draw();

		break;
	case Scene::Select:
		selectPic->Draw();
		
		//ステージ選択わかりやすく
		if (selectMode == 0) {sord3UI->Draw();}
		else if (selectMode == 1) { sord2UI->Draw(); }
		else if (selectMode == 2) { sordUI->Draw(); }

		
		sru->Draw();
		srd->Draw();
		break;
	case Scene::Play:
		
		player_->FbxDraw();
		enemyManager_->FbxDraw();

		// パーティクル描画前処理
	/*	ParticleManager::PreDraw(dxCommon->GetCommandList());*/
		player_->EffDraw();
		enemyManager_->EffDraw();
		//// パーティクル描画後処理
		//ParticleManager::PostDraw();
		
		UI->Draw();
		if (isPause == false) {
			if (input->ButtonInput(X)) {
				buttomx->Draw();
			}

			if (input->ButtonInput(Y)) {
				buttomy->Draw();
			}
			if (input->ButtonInput(B)) {
				buttomb->Draw();
			}
		}
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

		//カウントダウン
		if (actionStopTimer > 60 * 2) {
			std3->Draw();
		}else if (actionStopTimer > 60 * 1) {
			std2->Draw();
		}else if (actionStopTimer > 0) {
			std1->Draw();
		}else if (actionStopTimer > -20) {
			stdgo->Draw();
		}else if (actionStopTimer > -35) {
			stdgo2->Draw();
		}

		if (isPause) {
			//ポーズ画面
			if (keycon == false) {
				pauseBg->Draw();
				if (pauseSelect == 0) {
					//再開
					option2->Draw();
				}
				else if (pauseSelect == 1) {
					//再開
					option3->Draw();
				}
				else if (pauseSelect == 2) {
					//再開
					option4->Draw();
				}
				else if (pauseSelect == 3) {
					//再開
					option5->Draw();
				}
			}else if (keycon == true) {
				optionco->Draw();
				markPointer->Draw();
			}

			

		}

		break;
	case Scene::Clear:
		clearPic->Draw();

		break;
	case Scene::Gameover:
		gameoverPic->Draw();

		break;
	case Scene::Option:
		optionPic->Draw();
		mouse->Draw();

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