#pragma once

#include "EnemyBullet.h"
#include "EnemyCrystalBullet.h"
#include "Input.h"

class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(Input* input);
	void Update();
	void Draw();

	//行動フェーズ
	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
		ReLeave,  //再離脱する
	};

private:

	Object3d* enemyObj_ = nullptr;
	Model* enemyModel_ = nullptr;

	Input* input_ = nullptr;

	//フェーズ
	Phase phase_ = Phase::Approach;

	//敵の攻撃系統

	////-----ダガーファンネル------///
	std::list<std::unique_ptr<EnemyBullet>> enemyBulletObjs_;
	Model* enemyBulletModel_ = nullptr;
	//召喚して飛ばすまでの時間とフラグ
	int daggerTimer = 0;
	//////////////////////////////

	////-----順番に弾が飛んでくる攻撃------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> enemyCBObjs_;
	Model* enemyCBModel_ = nullptr;
	//召喚して飛ばすまでの時間とフラグ
	int crystalTimer = 0;
	///////////////////////////////////


};
