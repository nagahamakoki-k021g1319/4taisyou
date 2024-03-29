#include"EnemyManager.h"
#include"player.h"

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::Initialize(DirectXCommon* dxCommon) {
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;
	
	origin = new Transform();
	origin->Initialize();

	//パーティクル生成
	DamageParticle = std::make_unique<ParticleManager>();
	DamageParticle.get()->Initialize();
	DamageParticle->LoadTexture("doge.png");
	DamageParticle->Update();

	FireParticle = std::make_unique<ParticleManager>();
	FireParticle.get()->Initialize();
	FireParticle->LoadTexture("fire.png");
	FireParticle->Update();

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("slash.wav");
	audio->LoadWave("fire.wav");

	isActionStop = true;
}

void EnemyManager::creatEnemy(int round) {
	//念のためリストの掃除
	enemys_.clear();

	//敵の読み込み
	//ステージ1
	if (round == 0) {
		{
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize(dxCommon,{ 0,0,20 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		}
	}
	//ステージ2
	else if (round == 1) {
		{
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize(dxCommon,{ -3,0,5 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		} {
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize(dxCommon,{ 3,0,5 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		}
	}
}


void EnemyManager::Update() {
	//敵がいないとき原点に攻撃
	player_->SetEnemyPos(origin);


	if (isEffFlag == 1) {
		EffTimer++;
	}
	if (EffTimer <= 5 && EffTimer >= 1) {
		EffUpdate();
	}
	if (EffTimer >= 6) {
		isEffFlag = 0;
		EffTimer = 0;
	}

	if (isEffFireFlag == 1) {
		EffFireTimer++;
	}
	if (EffFireTimer <= 10 && EffFireTimer >= 1) {
		EffFireUpdate();
	}
	if (EffFireTimer >= 11) {
		isEffFireFlag = 0;
		EffFireTimer = 0;
	}

	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->isActionStop = isActionStop;
		if (isActionStop == false) {
			//敵の無敵時間解除
			if (player_->GetIsAttackFin()) {
				enemy->ResetHit2player();
			}

			//敵とプレイヤーの衝突
			if (player_->CheckBody2Enemy(enemy->GetWorldPosition())) {

			}

			float damage = 0;
			//敵とプレイヤー攻撃衝突
			if (player_->CheckAttack2Enemy(enemy->GetWorldPosition(), damage)) {
				enemy->OnColision(damage);
				pSourceVoice[0] = audio->PlayWave("slash.wav");
				pSourceVoice[0]->SetVolume(0.6f);
				isEffFlag = 1;

				isHitStop = true;
			}

			if (player_->wolf_->CheckAttack2Enemy(enemy->GetWorldPosition(), damage)) {
				enemy->OnColision(damage);
				pSourceVoice[1] = audio->PlayWave("fire.wav");
				pSourceVoice[1]->SetVolume(0.6f);
				isEffFireFlag = 1;
			}
		}
		enemy->Update();
	}

}

void EnemyManager::Draw() {
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw();
	}

}

void EnemyManager::FbxDraw()
{
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->FbxDraw();
	}
}

void EnemyManager::EffUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		for (std::unique_ptr<Enemy>& enemy : enemys_) {
			//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
			const float rnd_pos = 5.0f;
			Vector3 pos{};
			pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos += enemy->GetWorldPosition();
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
			DamageParticle->Add(60, pos, vel, acc, 1.0f, 0.0f);

			DamageParticle->Update();
		}
	}

}

void EnemyManager::EffFireUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		for (std::unique_ptr<Enemy>& enemy : enemys_) {
			//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
			const float rnd_pos = 5.0f;
			Vector3 pos{};
			pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos += enemy->GetWorldPosition();
			pos.y += 2.0f;
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
			FireParticle->Add(60, pos, vel, acc, 1.0f, 0.0f);

			FireParticle->Update();
		}
	}


}

void EnemyManager::EffDraw()
{
	if (isEffFlag == 1) {
		// 3Dオブクジェクトの描画
		DamageParticle->Draw();
	}

	if (isEffFireFlag == 1) {
		// 3Dオブクジェクトの描画
		FireParticle->Draw();
	}
}

bool EnemyManager::IsAllEnemyDead() {
	bool result = false;

	if (enemys_.size() == 0) {
		result = true;
	}

	return result;
}
