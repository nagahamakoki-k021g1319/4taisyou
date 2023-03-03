#pragma once
#include "Object3d.h"
#include <memory>
#include <list>

class EnemyBullet {
public:
	///< summary>
	///初期化
	///</summary>
	void Initialize(int timer);

	///< summary>
	///更新
	///</summary>
	void Update();

	///< summary>
	///描画
	///</summary>
	void Draw();

	void SetPos(Vector3 pos) { obj_->wtf.position = pos; };

private:



	////-----ダガーファンネル------///
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
	//召喚して飛ばすまでの時間とフラグ
	int daggerTimer;
	bool isLive = false;
	int shotTimer;
	//////////////////////////////
	


};
