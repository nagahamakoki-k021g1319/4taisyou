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
	void Initialize(int num);

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
	Model* crystalModel_ = nullptr;
	Object3d* crystalObj_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int crystalTimer;
	bool isLive = false;

	//////////////////////////////

	int bulletNum;

};

