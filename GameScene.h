#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include <string>

#include "Matrix4.h"

#include "Transform.h"
#include "View.h"

#include "player.h"
#include "Enemy.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// カメラ関係
	View* view = nullptr;
	// 時間計測に必要なデータ
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;
	float elapsedTime = 0;

	// 補間で使うデータ
	// start -> end を 5[ｓ] で完了させる
	Vector3 p0, p1, p2, p3;
	float maxTime = 50.0f;
	float timeRate;
	float maxTimeRate;
	int cameraState = 0;

	Vector3 ai;

	//プレイヤー
	Player* player_ = nullptr;
	//エネミー
	Enemy* enemy_ = nullptr;
};

