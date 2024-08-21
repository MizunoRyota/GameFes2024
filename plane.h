#pragma once

class Player;

class Plane
{
public:
	Plane();
	~Plane();
	const VECTOR& GetPos() const { return pos; }
	void Init();
	void Update(const VECTOR playerpos);
	void GameClear();
	void Draw();
private:
	bool vertical = false;
	bool Clear = false;
	VECTOR pos;
	VECTOR Getpos;
	int planeHandle[2];//îÚçsã@ÉÇÉfÉã
};
