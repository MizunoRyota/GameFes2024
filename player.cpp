#include "Player.h"
#include"plane.h"
// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Player::Speed = static_cast<float>(10000.0 / 65.0 / 65.0 / 65.0);
const float Player::Scale = 0.006f;		// �X�P�[��

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	// �R�c���f���̓ǂݍ���
	modelHandle[0] = MV1LoadModel("data/model/player/player.mv1");
	modelHandle[1] = MV1LoadModel("data/model/player/Jumping.mv1");
	modelHandle[2] = MV1LoadModel("data/model/player/Dying.mv1");
	AttachIndex[0] = MV1AttachAnim(modelHandle[0], 0, -1, FALSE);
	AttachIndex[1] = MV1AttachAnim(modelHandle[1], 0, -1, FALSE);
	AttachIndex[2] = MV1AttachAnim(modelHandle[2], 0, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	AnimTime = MV1GetAttachAnimTotalTime(modelHandle[0], AttachIndex[0]);
	GoalAnimTime = MV1GetAttachAnimTotalTime(modelHandle[1], AttachIndex[1]);
	EndAnimTime = MV1GetAttachAnimTotalTime(modelHandle[2], AttachIndex[2]);

	TotalTime = MV1GetAttachAnimTotalTime(modelHandle[0], AttachIndex[0]);
	TotalGoalTime = MV1GetAttachAnimTotalTime(modelHandle[1], AttachIndex[1]);
	TotalEndTime = MV1GetAttachAnimTotalTime(modelHandle[2], AttachIndex[2]);
	// �Đ����Ԃ̏�����
	PlayTime = 0.0f;
	GoalPlayTime = 0.0f;
	EndPlayTime = 0.0f;
	MV1SetRotationXYZ(modelHandle[1], VGet(0.0f, -90.0f, 0.0f));

	pos = VGet(-2, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle[0]);
}

void Player::Init()
{
	// �Đ����Ԃ̏�����
	PlayTime = 0.0f;
	pos = VGet(-2, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update()
{
	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �Đ����Ԃ�i�߂�
	PlayTime += 0.6f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (PlayTime >= TotalTime)
	{
		PlayTime = 0.0f;
	}

	// �P���ɕ����]��
	dir = VGet(0, 0, 0);

	if (Key & PAD_INPUT_RIGHT)
	{
		dir = VAdd(dir, VGet(1, 0, 0));
		// ��]
		MV1SetRotationXYZ(modelHandle[0], VGet(0.0f, -89.5f, 0.0f));
	}
	else if (Key & PAD_INPUT_LEFT)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
		// ��]
		MV1SetRotationXYZ(modelHandle[0], VGet(0.0f, 89.5f, 0.0f));
	}

	// �[�����Z����
	if (VSquareSize(dir) > 0)
	{
		// ���K��
		dir = VNorm(dir);
	}

	// �|�W�V�������X�V.
	velocity = VScale(dir, Speed);
	pos = VAdd(pos, velocity);

	// �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}

	Hit = VGet(pos.x, pos.y, pos.z);

	if (pos.x >= 5.95f)
	{
		// �Đ����Ԃ�i�߂�
		GoalPlayTime += 0.6f;
		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (GoalPlayTime >= TotalGoalTime)
		{
			GoalPlayTime = 0.0f;
			//3d���f���̃A�j���[�V�����̃Z�b�g
			MV1SetAttachAnimTime(modelHandle[1], AttachIndex[1], GoalPlayTime);
			pos.x = -2;
		}
	}
	else if (pos.x < -2)
	{
		pos.x = -2;
	}
	// 3D���f���̃X�P�[������
	MV1SetScale(modelHandle[0], VGet(Scale, Scale, Scale));
	MV1SetScale(modelHandle[1], VGet(Scale, Scale, Scale));

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle[0], pos);
	MV1SetPosition(modelHandle[1], pos);

	//3d���f���̃A�j���[�V�����̃Z�b�g
	MV1SetAttachAnimTime(modelHandle[0], AttachIndex[0], PlayTime);
	MV1SetAttachAnimTime(modelHandle[1], AttachIndex[1], GoalPlayTime);

}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{

	if (pos.x >= 5.95)
	{
		// �R�c���f���̕`��
		MV1DrawModel(modelHandle[1]);
	}
	else if (pos.x>=-2.0)
	{
		// �R�c���f���̕`��
		MV1DrawModel(modelHandle[0]);
	}
}

bool Player::ClearUpdate()
{
	bool end = false;
	// �Đ����Ԃ�i�߂�
	EndPlayTime += 0.6f;
	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (EndPlayTime >= TotalEndTime)
	{
		EndPlayTime = 0.0f;
		end = true;
		//3d���f���̃A�j���[�V�����̃Z�b�g
		MV1SetAttachAnimTime(modelHandle[1], AttachIndex[1], GoalPlayTime);
	}

	// 3D���f���̃X�P�[������
	MV1SetScale(modelHandle[2], VGet(Scale, Scale, Scale));

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle[2], pos);

	//3d���f���̃A�j���[�V�����̃Z�b�g
	MV1SetAttachAnimTime(modelHandle[2], AttachIndex[2], EndPlayTime);

	return end;
}

void Player::ClearDraw()
{
	MV1DrawModel(modelHandle[2]);
}