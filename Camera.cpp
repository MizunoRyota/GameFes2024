#include "DxLib.h"
#include <vector>
#include "Map.h"
#include "Player.h"
#include"plane.h"
#include "Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);
    zoom = -6.5;
	pos = VGet(0, 0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	// 処理なし.
}

void Camera::Init()
{
    zoom = -6.5;
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update(const VECTOR playerpos)
{
    // TODO:z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
    // カメラに位置を反映.
 
    pos = VGet(playerpos.x, playerpos.y+1, playerpos.z + zoom);
    targtpos = VGet(playerpos.x, playerpos.y+1, playerpos.z);
    // lerpを使用して実装.
    // lerp(VECTOR a, VECTOR b, float t)は
    // answer = a + ((b-a) * t)
    // answer = start + ((end - start) * t)
    //VECTOR   targetPos = VGet(playerpos.x, playerpos.y+0.1, playerpos.z -5);     // b 
    //VECTOR   aimPos = VSub(targetPos, pos);              // (b-a)
    //VECTOR   scalsepos = VScale(aimPos, 0.5);         // ((b-a) * t)
    //pos = VAdd(pos, scalsepos);         // a + ((b-a) * t)
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}

void Camera::GameTitle(const VECTOR& mappos)
{
    zoom = -8;
    pos = VGet(mappos.x, mappos.y +7, mappos.z - zoom);
    targtpos = VGet(mappos.x, mappos.y+5, mappos.z);
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}


void Camera::GameClear(const VECTOR& planepos)
{
    pos = VGet(0, 0, 0+zoom);
    targtpos = VGet(planepos.x,planepos.y,planepos.z);
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}