#pragma once
#pragma once
#include "Object3d.h"
#include <memory>
#include <list>

class EnemyCrystalBullet {
public:
	~EnemyCrystalBullet();

	///< summary>
	///������
	///</summary>
	void Initialize(int num, Model* crystalModel_);

	///< summary>
	///�X�V
	///</summary>
	void CrystalBAttack();

	///< summary>
	///�X�V
	///</summary>
	void Update();

	///< summary>
	///�`��
	///</summary>
	void Draw();

	void SetPos(Vector3 pos) { crystalObj_->wtf.position = pos; };

private:

	////-----------///
	Object3d* crystalObj_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int crystalTimer;
	bool isLive = false;
	int shotTimer;
	//////////////////////////////

	int bulletNum;

};

