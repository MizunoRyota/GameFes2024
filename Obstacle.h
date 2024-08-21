#pragma once
#include "DxLib.h"

class Player;
class Game;

class Obstacle {
public:
    Obstacle();
    ~Obstacle();
    void Init();
    void Fall(const VECTOR playerpos);
    void Falled(const VECTOR playerpos);
    void Update();
    void GetTime(Player player );
    const bool& GetIsActive() const { return isActive; }
    const VECTOR& GetPos() const { return pos; }
    void Draw();
private:
    VECTOR pos;
    VECTOR Dengerpos;
    VECTOR Toppos;
    VECTOR Bottompos;
    static const float Scale;
    bool isActive;
    int DengerHandle;
    int obsHandle;
    int SphereCr;
    int Cr;
    float speed;
    float radius;

};
