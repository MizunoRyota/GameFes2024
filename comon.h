#pragma once
#include"Game.h"
#include"skydome.h"
#include"map.h"
#include"Obstacle.h"
#include"player.h"
#include"Camera.h"
#include"HitChecker.h"
enum STATE
{
	STATE_TITLE,		// �^�C�g��.
	STATE_GAME,			// �Q�[����.
	STATE_CLEAR,		// �N���A.
	STATE_GAMEOVER,		// �Q�[���I�[�o�[.
};