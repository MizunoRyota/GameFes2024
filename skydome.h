#pragma once
#include <vector>
#include<DxLib.h>

class Skydome
{
public:
	Skydome();
	~Skydome();
	void SkydomeUpdate();
	void SkydomeTitle();
	void SkydomeDraw();
private:
	int SkydomeModel;
	VECTOR pos;
	VECTOR	dir;			// ‰ñ“]•ûŒü.
	int Key;
};