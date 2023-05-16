#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"
#include "Wolf.h"

#include "Gorilla.h"
#include "ParticleManager.h"
#include "Audio.h"

#include "FBXModel.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"


class Player {


public:
	Player();
	~Player();

	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Reset();

	void Update();
	void Rota();
	void Move();
	void camUpdate();

	void Attack();

	void Draw();
	void FbxDraw();
	void EffUpdate();
	void EffDraw();

	void OnCollision();

	void SetEnemyPos(Transform* enemyPos) { enemyPos_ = enemyPos; };

	void LightAttack();
	void HeavyAttack();
	void Dodge();

	bool CheckAttack2Enemy(Vector3 enemyPos, float& damage);
	bool CheckBody2Enemy(Vector3 enemyPos);


	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////���[���h���W���擾
	Vector3 GetWorldPosition();

	float GetHp() { return hp; };
	float GetMp() { return mp; };
	bool GetIsDodge() { return isDodge; };
	Vector3 GetCamShake() { return camShakeVec; };
	Vector3 GetMoveBack();
	bool GetIsAttackFin() { return isAttackFin; };
	Vector3 GetDodgeMoveVec() { return dodgeMoveVec; };
	void MpUpdate(float mp);

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { bodyObj_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

	int EffTimer = 0;
	int isEffFlag = 0;

public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Collision col;
	Audio* audio = nullptr;
	//�v���C���[
	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;

	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;
	float camRotaSpeed = PI / 180;
	float dashSpeed = 0.4f;
	const float dashMP = 3.0f / 60.0f;

	//�v���C���[�̈ړ�
	Model* dash1Model_ = nullptr;
	Object3d* dash1Obj_ = nullptr;

	Model* dash2Model_ = nullptr;
	Object3d* dash2Obj_ = nullptr;

	Model* dash3Model_ = nullptr;
	Object3d* dash3Obj_ = nullptr;

	Model* dash4Model_ = nullptr;
	Object3d* dash4Obj_ = nullptr;

	//�v���C���[�̈ړ�
	Model* attack1Model_ = nullptr;
	Object3d* attack1Obj_ = nullptr;

	Model* attack2Model_ = nullptr;
	Object3d* attack2Obj_ = nullptr;

	Model* attack3Model_ = nullptr;
	Object3d* attack3Obj_ = nullptr;

	Model* attack4Model_ = nullptr;
	Object3d* attack4Obj_ = nullptr;
	//�X�e�[�^�X
	const int defaultHp = 100;
	int hp;
	bool isLive = true;
	bool isAttackFin;
	bool nextAttack;

	//MP�֘A
	float mp;
	const float mpRegen = 0.5f / 60.0f;
	const float mpPuls = 5;
	//����
	const int heal = defaultHp * 0.2;
	const int healMp = 20;
	//���
	const int megaHeal = defaultHp * 0.6;
	const int megaHealMp = 60;
	//MP�U��
	const int bulletMp = 40;

	//���G����
	bool isInvincible;
	const float invincibleLimit = 15;
	float invincibleTimer = invincibleLimit;

	//��ʃV�F�C�N
	bool isCamShake;
	const int camShakeLimit = 20;
	int camShakeTimer = camShakeLimit;
	Vector3 camShakeVec;
	Vector3 moveBack;

	//��U��
	Vector3 lightAttackLPos;
	Vector3 lightAttackWPos;
	const float lightMpPuls = 3;
	//����߂̘A����
	int lightAttackCount;
	//���̍U���S�̂̎���
	float lightAttackLimit[4] = { 17,18,20,30 };
	float lightAttackTimer;
	//�U���̓����蔻��̗L��
	bool isLightAttack;
	//���肪�o�n�߂鎞��
	float lightAttackPopTime[4] = { 14,13,15,24 };
	//���肪�����鎞��
	float lightAttackDeathTime[4] = { 13,12,14,22 };
	//���̘A���ւ̓��͎�t�J�n����
	float lightAttackInput[4] = { 20,20,20,0 };

	//���U��
	Vector3 heavyAttackLPos;
	Vector3 heavyAttackWPos;
	const float heavyMpPuls = 8;
	//����߂̘A����
	int heavyAttackCount;
	//���̍U���S�̂̎���
	float heavyAttackLimit[2] = { 30,30 };
	float heavyAttackTimer;
	//�U���̓����蔻��̗L��
	bool isHeavyAttack;
	//���肪�o�n�߂鎞��
	float heavyAttackPopTime[2] = { 15,25 };
	//���肪�����鎞��
	float heavyAttackDeathTime[2] = { 12,22 };
	//���̘A���ւ̓��͎�t�J�n����
	float heavyAttackInput[2] = { 15,0 };

	//���
	bool isDodge;
	const int dodgeLimit = 60;
	int dodgeTimer;
	//�����d������
	const int dodgeStun = 1;
	Vector3 dodgeMoveVec;
	Vector3 dodgeMoveVecNomal;

	//OBJ�֌W
	//�ړ���������playerOBJ��ς���
	int objRotaTimer;
	//�U����������playerOBJ��ς���
	int attackFlag = 0;
	int objAttackTimer;

	//�G
	Transform* enemyPos_ = nullptr;

	//�p�[�e�B�N���N���X�̏����� 
	std::unique_ptr<ParticleManager> particleManager;
	//���[���h���W������ϐ�
	Vector3 worldPos;
	
	
	//�f�o�b�O�p
	Model* debugModel_ = nullptr;
	Object3d* debugObj_ = nullptr;

	//���֌W�܂Ƃ�
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;


public:
	int isAction;
	//�o�f�B
	Wolf* wolf_ = nullptr;
};