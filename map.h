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
	int		mapHandle;	// ���f���n���h��.
	VECTOR	pos;			// �|�W�V����.
	static const float Scale;
};

