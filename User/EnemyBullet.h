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

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { obj_->wtf.position = pos; };

	/// <summary>
	/// �傫��
	/// </summary>
	/// <param name="pos"></param>
	void SetScale(Vector3 scale) { obj_->wtf.scale = scale; };

	bool IsDead() const { return  isDead_; }


private:

	////-----�_�K�[�t�@���l��------///
	Object3d* obj_ = nullptr;
	//�������Ĕ�΂��܂ł̎��Ԃƃt���O
	int daggerTimer;
	bool isLive = false;
	bool isDead_ = false;
	int shotTimer;
	//////////////////////////////

};
