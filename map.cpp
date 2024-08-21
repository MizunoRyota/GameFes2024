#include<vector>
#include "DxLib.h"
#include "Map.h"

const float Map::Scale = 0.3f;		// スケール
Map::Map()
{
    mapHandle = MV1LoadModel("data/model/map/field.mv1");

    pos = VGet(-5.6, 0, 0);

    MV1SetRotationXYZ(mapHandle, VGet(0.0f, -89.5f, 0.0f));
    // ３Dモデルのポジション設定
    MV1SetPosition(mapHandle, pos);
}

Map::~Map()
{}

void Map::Titile()
{
    pos.y -= 0.001;
    if (pos.y>=-0.001)
    {
        pos.y = 0;
    }
    MV1SetRotationXYZ(mapHandle, VGet(0.0f, pos.y, 0.0f));
    MV1SetScale(mapHandle, VGet(Scale+0.3 , Scale+0.3 , Scale+0.3 ));
    // ３Dモデルのポジション設定
    MV1SetPosition(mapHandle, pos);
}

void Map::Init()
{
    // 3Dモデルのスケール決定
    pos = VGet(-5.6, 0, 0);
    MV1SetScale(mapHandle, VGet(Scale + 0.7, Scale + 0.5, Scale + 0.7));
    MV1SetRotationXYZ(mapHandle, VGet(0.0f, -89.5f, 0.0f));
    // ３Dモデルのポジション設定
    MV1SetPosition(mapHandle, pos);
}

void Map::Draw()
{
    MV1DrawModel(mapHandle);
}