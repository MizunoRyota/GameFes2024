#include "Player.h"
#include"plane.h"
// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::Speed = static_cast<float>(10000.0 / 65.0 / 65.0 / 65.0);
const float Player::Scale = 0.006f;		// スケール

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	// ３Ｄモデルの読み込み
	modelHandle[0] = MV1LoadModel("data/model/player/player.mv1");
	modelHandle[1] = MV1LoadModel("data/model/player/Jumping.mv1");
	modelHandle[2] = MV1LoadModel("data/model/player/Dying.mv1");
	AttachIndex[0] = MV1AttachAnim(modelHandle[0], 0, -1, FALSE);
	AttachIndex[1] = MV1AttachAnim(modelHandle[1], 0, -1, FALSE);
	AttachIndex[2] = MV1AttachAnim(modelHandle[2], 0, -1, FALSE);

	// アタッチしたアニメーションの総再生時間を取得する
	AnimTime = MV1GetAttachAnimTotalTime(modelHandle[0], AttachIndex[0]);
	GoalAnimTime = MV1GetAttachAnimTotalTime(modelHandle[1], AttachIndex[1]);
	EndAnimTime = MV1GetAttachAnimTotalTime(modelHandle[2], AttachIndex[2]);

	TotalTime = MV1GetAttachAnimTotalTime(modelHandle[0], AttachIndex[0]);
	TotalGoalTime = MV1GetAttachAnimTotalTime(modelHandle[1], AttachIndex[1]);
	TotalEndTime = MV1GetAttachAnimTotalTime(modelHandle[2], AttachIndex[2]);
	// 再生時間の初期化
	PlayTime = 0.0f;
	GoalPlayTime = 0.0f;
	EndPlayTime = 0.0f;
	MV1SetRotationXYZ(modelHandle[1], VGet(0.0f, -90.0f, 0.0f));

	pos = VGet(-2, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);

}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle[0]);
}

void Player::Init()
{
	// 再生時間の初期化
	PlayTime = 0.0f;
	pos = VGet(-2, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 再生時間を進める
	PlayTime += 0.6f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (PlayTime >= TotalTime)
	{
		PlayTime = 0.0f;
	}

	// 単純に方向転換
	dir = VGet(0, 0, 0);

	if (Key & PAD_INPUT_RIGHT)
	{
		dir = VAdd(dir, VGet(1, 0, 0));
		// 回転
		MV1SetRotationXYZ(modelHandle[0], VGet(0.0f, -89.5f, 0.0f));
	}
	else if (Key & PAD_INPUT_LEFT)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
		// 回転
		MV1SetRotationXYZ(modelHandle[0], VGet(0.0f, 89.5f, 0.0f));
	}

	// ゼロ除算避け
	if (VSquareSize(dir) > 0)
	{
		// 正規化
		dir = VNorm(dir);
	}

	// ポジションを更新.
	velocity = VScale(dir, Speed);
	pos = VAdd(pos, velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}

	Hit = VGet(pos.x, pos.y, pos.z);

	if (pos.x >= 5.95f)
	{
		// 再生時間を進める
		GoalPlayTime += 0.6f;
		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (GoalPlayTime >= TotalGoalTime)
		{
			GoalPlayTime = 0.0f;
			//3dモデルのアニメーションのセット
			MV1SetAttachAnimTime(modelHandle[1], AttachIndex[1], GoalPlayTime);
			pos.x = -2;
		}
	}
	else if (pos.x < -2)
	{
		pos.x = -2;
	}
	// 3Dモデルのスケール決定
	MV1SetScale(modelHandle[0], VGet(Scale, Scale, Scale));
	MV1SetScale(modelHandle[1], VGet(Scale, Scale, Scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle[0], pos);
	MV1SetPosition(modelHandle[1], pos);

	//3dモデルのアニメーションのセット
	MV1SetAttachAnimTime(modelHandle[0], AttachIndex[0], PlayTime);
	MV1SetAttachAnimTime(modelHandle[1], AttachIndex[1], GoalPlayTime);

}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{

	if (pos.x >= 5.95)
	{
		// ３Ｄモデルの描画
		MV1DrawModel(modelHandle[1]);
	}
	else if (pos.x>=-2.0)
	{
		// ３Ｄモデルの描画
		MV1DrawModel(modelHandle[0]);
	}
}

bool Player::ClearUpdate()
{
	bool end = false;
	// 再生時間を進める
	EndPlayTime += 0.6f;
	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (EndPlayTime >= TotalEndTime)
	{
		EndPlayTime = 0.0f;
		end = true;
		//3dモデルのアニメーションのセット
		MV1SetAttachAnimTime(modelHandle[1], AttachIndex[1], GoalPlayTime);
	}

	// 3Dモデルのスケール決定
	MV1SetScale(modelHandle[2], VGet(Scale, Scale, Scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle[2], pos);

	//3dモデルのアニメーションのセット
	MV1SetAttachAnimTime(modelHandle[2], AttachIndex[2], EndPlayTime);

	return end;
}

void Player::ClearDraw()
{
	MV1DrawModel(modelHandle[2]);
}