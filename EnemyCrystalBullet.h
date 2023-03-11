#pragma once
#include "Object3d.h"
#include <memory>
#include <list>

class EnemyCrystalBullet {
public:
	~EnemyCrystalBullet();

	///< summary>
	///初期化
	///</summary>
	void Initialize(int num);

	///< summary>
	///更新
	///</summary>
	void CrystalBAttack();

	///< summary>
	///更新
	///</summary>
	void Update();

	///< summary>
	///描画
	///</summary>
	void Draw();

	void SetPos(Vector3 pos) { crystalObj_->wtf.position = pos; };

private:

	////-----------///
	Model* crystalModel_ = nullptr;
	Object3d* crystalObj_ = nullptr;
	//召喚して飛ばすまでの時間とフラグ
	int crystalTimer;
	bool isLive = false;

	//////////////////////////////

	int bulletNum;

};

