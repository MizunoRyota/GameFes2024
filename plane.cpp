#include"DxLib.h"
#include"plane.h"
#include "Player.h"
Plane::Plane()
{
    planeHandle[0] = MV1LoadModel("data/model/map/plane.mv1");
    planeHandle[1] = MV1LoadModel("data/model/map/plane.mv1");
    pos = VGet(8, 0, 0);
    MV1SetPosition(planeHandle[1], pos);
    Getpos = VGet(0, 0, 0);
}

Plane::~Plane()
{
    MV1DeleteModel(planeHandle[0]);
    MV1DeleteModel(planeHandle[1]);
}

void Plane::Init()
{
    pos = VGet(8, 0, 0);
    MV1SetRotationXYZ(planeHandle[1], VGet(0.0f, 0.0f, 0.0f));
    MV1SetPosition(planeHandle[0], pos);
    MV1SetPosition(planeHandle[1], pos);
}

void Plane::Update(const VECTOR playerpos)
{
    Clear = false;
    if (playerpos.x <= 5.95f&&playerpos.x>=-2.0f)
    {
        pos.y += 0.03f;
        pos.z += 0.12f;
    }
    else
    {
        pos.x = 8;
        pos.y = 0;
        pos.z = 0;
    }
    MV1SetPosition(planeHandle[0], pos);
}

void Plane::GameClear()
{
    Clear = true;
    if (pos.x != -3&&pos.z!=-2)
    {
        pos.y = 1.5;
        pos.x = -3;
        pos.z = -2;
        MV1SetRotationXYZ(planeHandle[1], VGet(0.0f, 89.5f, 0.0f));
    }
    if (vertical == false)
    {
        pos.y += 0.0015;
    }
    else
    {
        pos.y -= 0.0015;
    }

    if (pos.y < 0)
    {
        vertical = false;
    }
    else if (pos.y > 1)
    {
        vertical = true;
    }

    MV1SetPosition(planeHandle[1], pos);
}

void Plane::Draw()
{
    if (Clear == false)
    {
        MV1DrawModel(planeHandle[0]);
    }
    MV1DrawModel(planeHandle[1]);
}