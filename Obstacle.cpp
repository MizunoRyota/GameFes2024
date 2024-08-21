#include"Obstacle.h"
#include"player.h"
const int ObstacleNum = 10;
const float Obstacle::Scale = 0.005f;		// スケール

Obstacle::Obstacle()
{
    obsHandle = MV1LoadModel("data/model/map/pot.mv1");
    DengerHandle = MV1LoadModel("data/model/map/denger.mv1");
    speed = 0.1;
    pos = VGet(-5, 7, 0);
    radius = 0;
    SphereCr = GetColor(0, 0, 0);
    Cr = GetColor(0, 0, 255);
}

Obstacle::~Obstacle()
{}

void Obstacle::Init()
{
    MV1SetRotationXYZ(obsHandle, VGet(0.0f, 90.0f, 0.0f));
    MV1SetScale(obsHandle, VGet(Scale, Scale, Scale));
    MV1SetScale(DengerHandle, VGet(Scale, Scale, Scale));
    isActive = false;
}

void Obstacle::Fall(const VECTOR playerpos)
{
    if (isActive == false)
    {
        // 画面外に出たら再配置
        pos.y = 7;
        radius = 0;
        pos.x =  rand() % 7;  // 新しいX座標をランダムに設定
        if (pos.x >= 6)
        {
            pos.x = pos.x - 2;
        }
        pos.z = 0;
        isActive = true;
    }
}

void Obstacle::Update()
{

        speed = 0.11;
	
        speed = 0.12;
	
    if (isActive == true)
    {
        pos.y -= speed;  // 障害物が上から下に移動する
        radius += 0.005;
        if (pos.y < 0) {
            Obstacle::Init();
        }
    }
    Dengerpos = VGet(pos.x, 2, pos.z);
    Toppos = VGet(pos.x, -1, pos.z);
    Bottompos = VGet(pos.x, 0.001, pos.z);
}

void Obstacle::Draw() 
{
    MV1SetPosition(obsHandle, pos);
    MV1SetPosition(DengerHandle, Dengerpos);
    DrawCone3D(Toppos, Bottompos, radius, 8, SphereCr, SphereCr, TRUE);
    MV1DrawModel(obsHandle);
    MV1DrawModel(DengerHandle);
}