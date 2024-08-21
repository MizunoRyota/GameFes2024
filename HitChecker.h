#pragma once

class Obstacle;

class Player;

class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    void Init();
    bool Check(const VECTOR& player, const VECTOR& obs);
    bool DeadJudge(const VECTOR& player, const VECTOR& obs);
    const float& GetDistance() const { return Distance; }
private:
    VECTOR Hitpoint, HitLine1, HitLine2;
    VECTOR ObstacleCircle;
    VECTOR PlayerCircle;
    bool deadgudge;
    float ObstacleRadius;
    float PlayerRadius;
    float dx, dy, dz;
    float Distance;
    float Length;
};