#pragma once
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Audio.h"

class Player;

class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();

	void Initialize(DirectXCommon* dxCommon);

	void Update();

	void Draw();
	void FbxDraw();

	void EffUpdate();
	void EffDraw();

	void creatEnemy(int round);

	void SetPlayer(Player* player) { player_ = player; };

	bool IsAllEnemyDead();

	int EffTimer = 0;
	int isEffFlag = 0;

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Transform* origin = nullptr;

	Player* player_ = nullptr;

	Enemy* enemy_ = nullptr;
	std::list<std::unique_ptr<Enemy>> enemys_;

	//パーティクル
	std::unique_ptr<ParticleManager> DamageParticle;


public:
	bool isHitStop;
	bool isActionStop;
};