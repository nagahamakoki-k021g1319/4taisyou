#pragma once
#include"Enemy.h"

class Player;

class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();

	void Initialize();

	void Update();
	
	void Draw();

	void EffUpdate();
	void EffDraw();

	void creatEnemy(int round);

	void SetPlayer(Player* player) { player_ = player; };

	bool IsAllEnemyDead();


private:
	Transform* origin = nullptr;

	Player* player_ = nullptr;

	std::list<std::unique_ptr<Enemy>> enemys_;

	//パーティクルクラスの初期化 
	std::unique_ptr<ParticleManager> DamageParticle;
	//当たった時のエフェクト発生
	int isEffFlag = 0;
	int EffTimer = 0;

};