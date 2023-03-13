#pragma once
#include "Object3d.h"
#include <memory>
#include <list>

class EnemyBullet {
public:
	~EnemyBullet();

	///< summary>
	///������
	///</summary>
	void Initialize(int timer, Model* model_);

	
	///< summary>
	///�X�V
	///</summary>
	void DaggerFAttack();

	///< summary>
	///�X�V
	///</summary>
	void Update();

	///< summary>
	///�`��
	///</summary>
	void Draw();

	void SetPos(Vector3 pos) { obj_->wtf.position = pos; };
	Vector3 GetPos() { return obj_->wtf.position; };



private:

	////-----�_�K�[�t�@���l��------///
	Object3d* obj_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int daggerTimer;
	bool isLive = false;
	int shotTimer;
	//////////////////////////////

};
