#include "DxLib.h"
#include <vector>
#include "Map.h"
#include "Player.h"
#include"plane.h"
#include "Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);
    zoom = -6.5;
	pos = VGet(0, 0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	// �����Ȃ�.
}

void Camera::Init()
{
    zoom = -6.5;
}

/// <summary>
/// �X�V
/// </summary>
void Camera::Update(const VECTOR playerpos)
{
    // TODO:z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
    // �J�����Ɉʒu�𔽉f.
 
    pos = VGet(playerpos.x, playerpos.y+1, playerpos.z + zoom);
    targtpos = VGet(playerpos.x, playerpos.y+1, playerpos.z);
    // lerp���g�p���Ď���.
    // lerp(VECTOR a, VECTOR b, float t)��
    // answer = a + ((b-a) * t)
    // answer = start + ((end - start) * t)
    //VECTOR   targetPos = VGet(playerpos.x, playerpos.y+0.1, playerpos.z -5);     // b 
    //VECTOR   aimPos = VSub(targetPos, pos);              // (b-a)
    //VECTOR   scalsepos = VScale(aimPos, 0.5);         // ((b-a) * t)
    //pos = VAdd(pos, scalsepos);         // a + ((b-a) * t)
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}

void Camera::GameTitle(const VECTOR& mappos)
{
    zoom = -8;
    pos = VGet(mappos.x, mappos.y +7, mappos.z - zoom);
    targtpos = VGet(mappos.x, mappos.y+5, mappos.z);
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}


void Camera::GameClear(const VECTOR& planepos)
{
    pos = VGet(0, 0, 0+zoom);
    targtpos = VGet(planepos.x,planepos.y,planepos.z);
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}