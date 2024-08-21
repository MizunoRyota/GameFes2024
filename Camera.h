#pragma once

class Player;
class Plane;
/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
	Camera();							// �R���X�g���N�^.
	~Camera();							// �f�X�g���N�^.
	void Init();
	void Update(const VECTOR playerpos);	// �X�V.
	void GameTitle(const VECTOR& mappos);
	void GameClear(const VECTOR& planepos);

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }

private:
	float zoom;
	VECTOR	pos;			// �|�W�V����.
	VECTOR targtpos;
};
