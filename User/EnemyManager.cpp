#include"EnemyManager.h"
#include"player.h"

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::Initialize() {
	origin = new Transform();
	origin->Initialize();
	
	//�p�[�e�B�N������
	DamageParticle = std::make_unique<ParticleManager>();
	DamageParticle.get()->Initialize();
	DamageParticle->LoadTexture("doge.png");
	DamageParticle->Update();

}

void EnemyManager::creatEnemy(int round) {
	//�O�̂��߃��X�g�̑|��
	enemys_.clear();

	//�G�̓ǂݍ���
	if (round == 0) {
		{
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize({ 0,0,7 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		}
	}else if (round == 1) {
		{
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize({ -3,0,5 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		} {
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize({ 3,0,5 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		}
	}
}


void EnemyManager::Update() {
	//�G�����Ȃ��Ƃ����_�ɍU��
	player_->SetEnemyPos(origin);

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

	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		float damage = 0;
		//�G�ƃv���C���[�U���Փ�
		if (player_->CheckAttack2Enemy(enemy->GetWorldPosition(), damage)) {
			enemy->OnColision(damage);	
			isEffFlag = 1;
		}
		//�G�ƃo�f�B�̏Փ�
		if (player_->wolf_->CheckAttack2Enemy(enemy->GetWorldPosition(), damage)) {
			enemy->OnColision(damage);
		}

		enemy->Update();
	}

}

void EnemyManager::Draw() {
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw();
	}

}

void EnemyManager::EffUpdate()
{
	//�p�[�e�B�N���͈�
	for (int i = 0; i < 20; i++) {
		//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 0.1f;
		const float rnd_pos2 = 10.0f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos2 - rnd_pos2 / 2.0f;

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
		DamageParticle->Add(60, pos, vel, acc, 1.0f, 0.0f);

		DamageParticle->Update();
	}

}

void EnemyManager::EffDraw()
{
	if (isEffFlag == 1) {
		// 3D�I�u�N�W�F�N�g�̕`��
		DamageParticle->Draw();
	}
}


bool EnemyManager::IsAllEnemyDead() {
	bool result = false;

	if (enemys_.size() == 0) {
		result = true;
	}

	return result;
}
