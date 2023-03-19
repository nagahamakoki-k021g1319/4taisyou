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
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { enemyObj_->wtf.position = pos; };

	/// <summary>
	/// �傫��
	/// </summary>
	/// <param name="pos"></param>
	void SetScale(Vector3 scale) { enemyObj_->wtf.scale = scale; };*/

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
		ReLeave,  //�ė��E����
	};

private:
	Player* player_ = nullptr;
	Collision coll;

	Object3d* enemyObj_ = nullptr;
	std::list<std::unique_ptr<Object3d>> enemyListObjs_;

	Model* enemyModel_ = nullptr;
	
	

	Input* input_ = nullptr;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;




	//�G�̍U���n��

	////-----�_�K�[�t�@���l��------///
	std::list<std::unique_ptr<EnemyBullet>> enemyBulletObjs_;
	Model* enemyBulletModel_ = nullptr;
	int enemyAttackTimer = 0;
	//////////////////////////////

	////-----���Ԃɒe�����ł���U��------///
	std::list<std::unique_ptr<EnemyCrystalBullet>> enemyCBObjs_;
	Model* enemyCBModel_ = nullptr;
	int enemyAttackTimer2 = 0;
	///////////////////////////////////

	int enemyResetTimer = 0;


};
