#include"DxLib.h"
#include"player.h"
#include"Obstacle.h"
#include"HitChecker.h"

HitChecker::HitChecker()
{
   deadgudge=false;
   PlayerRadius = 0.07;
   ObstacleRadius = 0.07;

}
HitChecker::~HitChecker()
{}

void HitChecker::Init()
{
    deadgudge = false;
}

bool HitChecker::Check( const VECTOR& player, const VECTOR& obs)
{
    dx = player.x - obs.x;
    dy = player.y - obs.y;
    dz = player.z - obs.z;

    PlayerCircle = VGet(player.x, player.y+0.3, player.z);
    ObstacleCircle = VGet(obs.x, obs.y, obs.z);
    Length = PlayerRadius + ObstacleRadius;
    Distance= dx * dx + dy * dy + dz * dz;

    DrawFormatString(100, 100, GetColor(255, 0, 0), "%d", deadgudge);

    return Distance <= (Length);
}

bool HitChecker::DeadJudge(const VECTOR& player, const VECTOR& obs)
{

    DrawSphere3D(obs, ObstacleRadius, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), true);

    DrawSphere3D(PlayerCircle, PlayerRadius, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), true);

    deadgudge = true;

    return deadgudge;
}