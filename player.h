#pragma once
#include "DxLib.h"
#include"map.h"

class HitChecker;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final
{
public:
	Player();				// �R���X�g���N�^.
	~Player();				// �f�X�g���N�^.
	void Init();
	void Update();			// �X�V.
	bool ClearUpdate();
	void Draw();			// �`��.
	void ClearDraw();

	// ���f���n���h���̎擾.
	//int GetModelHandle() const { return modelHandle; }
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetDir() const { return dir; }

private:
	int modelHandle[3];	// ���f���n���h��.
	float TotalTime, PlayTime;
	float TotalGoalTime, GoalPlayTime;
	float TotalEndTime, EndPlayTime;
	int AttachIndex[3];
	float AnimTime;
	float GoalAnimTime;
	float EndAnimTime;
	VECTOR	velocity;		// �ړ���.
	VECTOR	pos;			// �|�W�V����.
	VECTOR	dir;			// ��]����.
	VECTOR Hit;
	// �ÓI�萔.
	static const float Speed;
	static const float Scale;
};
