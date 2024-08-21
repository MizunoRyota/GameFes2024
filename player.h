#pragma once
#include "DxLib.h"
#include"map.h"

class HitChecker;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.
	void Init();
	void Update();			// 更新.
	bool ClearUpdate();
	void Draw();			// 描画.
	void ClearDraw();

	// モデルハンドルの取得.
	//int GetModelHandle() const { return modelHandle; }
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }

private:
	int modelHandle[3];	// モデルハンドル.
	float TotalTime, PlayTime;
	float TotalGoalTime, GoalPlayTime;
	float TotalEndTime, EndPlayTime;
	int AttachIndex[3];
	float AnimTime;
	float GoalAnimTime;
	float EndAnimTime;
	VECTOR	velocity;		// 移動力.
	VECTOR	pos;			// ポジション.
	VECTOR	dir;			// 回転方向.
	VECTOR Hit;
	// 静的定数.
	static const float Speed;
	static const float Scale;
};
