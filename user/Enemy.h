#pragma once

#include "EnemyBullet.h"
#include "EnemyCrystalBullet.h"
#include "Input.h"

class Player;
#include "Collision.h"

class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(Input* input);
	void Update();
	void Draw();

	void SetPlayer(Player* player) { player_ = player; };

	/*/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { enemyObj_->wtf.position = pos; };

	/// <summary>
	/// 大きさ
	/// </summary>
	/// <param name="pos"></param>
	void SetScale(Vector3 scale) { enemyObj_->wtf.scale = scale; };*/

	//行動フェーズ
	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
		ReLeave,  //再離脱する
	};

private:
	Player* player_ = nullptr;
	Collision coll;

	Object3d* enemyObj_ = nullptr;
	std::list<std::unique_ptr<Object3d>> enemyListObjs_;

	Model* enemyModel_ = nullptr;
	
	

	Input* input_ = nullptr;

	//フェーズ
	Phase phase_ = Phase::Approach;




	//敵の攻撃系統

	////-----ダガーファンネル------///
	std::list<std::unique_ptr<EnemyBullet>> enemyBulletObjs_;
	Model* enemyBulletModel_ = nullptr;
	int enemyAttackTimer = 0;
	//////////////////////////////

	////-----順番に弾が飛んでくる攻撃------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> enemyCBObjs_;
	Model* enemyCBModel_ = nullptr;
	int enemyAttackTimer2 = 0;
	///////////////////////////////////

	int enemyResetTimer = 0;


};
