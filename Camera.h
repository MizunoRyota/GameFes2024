#pragma once

class Player;
class Plane;
/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	Camera();							// コンストラクタ.
	~Camera();							// デストラクタ.
	void Init();
	void Update(const VECTOR playerpos);	// 更新.
	void GameTitle(const VECTOR& mappos);
	void GameClear(const VECTOR& planepos);

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }

private:
	float zoom;
	VECTOR	pos;			// ポジション.
	VECTOR targtpos;
};
