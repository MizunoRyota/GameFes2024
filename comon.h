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
	STATE_TITLE,		// タイトル.
	STATE_GAME,			// ゲーム中.
	STATE_CLEAR,		// クリア.
	STATE_GAMEOVER,		// ゲームオーバー.
};