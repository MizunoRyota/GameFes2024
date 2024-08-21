#pragma once
#include <vector>
#include"DxLib.h"
class Map
{
public:
	Map();
	~Map();

	void Titile();
	void Init();
	void Draw();
	const VECTOR& GetPos() const { return pos; }
private:
	int		mapHandle;	// モデルハンドル.
	VECTOR	pos;			// ポジション.
	static const float Scale;
};

