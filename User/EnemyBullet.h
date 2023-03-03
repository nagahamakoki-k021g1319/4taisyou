#pragma once
#include "Object3d.h"
#include <memory>
#include <list>

class EnemyBullet {
public:
	///< summary>
	///������
	///</summary>
	void Initialize(int timer);

	///< summary>
	///�X�V
	///</summary>
	void Update();

	///< summary>
	///�`��
	///</summary>
	void Draw();

	void SetPos(Vector3 pos) { obj_->wtf.position = pos; };

private:



	////-----�_�K�[�t�@���l��------///
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int daggerTimer;
	bool isLive = false;
	int shotTimer;
	//////////////////////////////
	


};