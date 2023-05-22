#pragma once
#include "Object3d.h"
#include <memory>
#include <list>
#include "Sprite.h"

class EnemyBullet {
public:
	~EnemyBullet();

	///< summary>
	///初期化
	///</summary>
	void Initialize(int timer, Model* model_);
	
	///< summary>
	///更新
	///</summary>
	void DaggerFAttack();

	///< summary>
	///更新
	///</summary>
	void Update();

	///< summary>
	///描画
	///</summary>
	void Draw();

	///< summary>
	/// ui描画
	///</summary>
	void UIDraw();

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { obj_->wtf.position = pos; };

	/// <summary>
	/// 大きさ
	/// </summary>
	/// <param name="pos"></param>
	void SetScale(Vector3 scale) { obj_->wtf.scale = scale; };
  
	Vector3 GetPos() { return obj_->wtf.position; };

	bool IsDead() const {if (isLive) { return false; }else { return true; }};

	void OnCollision();

private:
	////-----ダガーファンネル------///
	Object3d* obj_ = nullptr;
	//召喚して飛ばすまでの時間とフラグ
	int daggerTimer;
	bool isLive = false;
	int shotTimer;
	float EnemyBulletSpeed = 0.2;
	//////////////////////////////

	//攻撃する前のわかりやすいエッフェクト
	Sprite* CdUI = nullptr;
	Sprite* CdUI1 = nullptr;
	Sprite* CdUI2 = nullptr;

public:
	bool isPop = false;
};
