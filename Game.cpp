#include"DxLib.h"
#include <vector>
#include"Game.h"

GameState::GameState()
{
	Start = LoadGraph("data/texture/title/Enter.png");
	Title = LoadGraph("data/texture/title/Title.png");
	ScoreBord = LoadGraph("data/texture/title/clear.png");
	Controller= LoadGraph("data/texture/title/setumei.png");
	ScoreGraph = LoadGraph("data/texture/game/Score .png");
	TimerHandle = LoadGraph("data/texture/game/Timer.png");
	Rainbow[0] = GetColor(255, 0, 0);
	Rainbow[1] = GetColor(255, 150, 0);
	Rainbow[2] = GetColor(255, 240, 0);
	Rainbow[3] = GetColor(0, 135, 0);
	Rainbow[4] = GetColor(0, 145, 255);
	Rainbow[5] = GetColor(0, 0, 0);
	Rainbow[6] = GetColor(128, 128, 128);
	Rainbow[7] = GetColor(255, 255, 255);
	TitleColor = GetColor(254, 250, 224);
	Countpos = VGet(1600, 720, 0);
	GameClearTime = 0;
	resultpos = 1600;
	RainbowCount = 0;
	FrameCount = 0;
	EndTime = 30;
	Score = 0;
	Clear = false;
}

GameState::~GameState()
{}

void GameState::Init()
{
	GameClearTime = 0;
	elapsedTime = 0;
	GameCount = 0;
	EndTime = 30;
}

void GameState::GameTitle()
{
	++FrameCount;
	Score = 0;
	resultpos = 1600;
	Clear = false;
	SetFontSize(95);
	DrawGraph(240, 170, Title, true);
	DrawGraph(270, 670, Start, true);
	DrawFormatString(370, 160, TitleColor, "ESCAPE BUILDING");
	SetFontSize(70);
	DrawFormatString(500, 670, Rainbow[RainbowCount], "START SPACE KEY");
	if (FrameCount >= 30)
	{
		FrameCount = 0;
		++RainbowCount;
	}
	if (RainbowCount == 4)
	{
		RainbowCount = 2;
	}
}

void GameState::GameReady()
{
	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 200, 1600, 800, Rainbow[5], TRUE);
	DrawBox(0, 210, 1600, 220, Rainbow[4], TRUE);
	DrawBox(0, 780, 1600, 790, Rainbow[4], TRUE);

	// 描画モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(150, 400, Controller, true);
	SetFontSize(50);
	DrawFormatString(600, 270, Rainbow[7], "　　チュートリアル\n\n操作方法:←と→キー\n障害物を避ける度に得点が増えていく\nただし当たるとGAMEOVER");
	DrawFormatString(600, 670, Rainbow[4], "START SPACE KEY");
}

bool GameState::GameUpdate(const VECTOR& playerpos)
{
	GameCount++;
	Clear = false;

	if (playerpos.x >= 5.97f && playerpos.x <= 6.0f)
	{
		PlaySoundMem(goal, DX_PLAYTYPE_BACK, false);

		Score=Score+1000;
	}
	if (HighScore <= Score)
	{
		HighScore = Score;
	}
	if (CheckHitKey(KEY_INPUT_L))
	{
		elapsedTime = 90;
	}
	//1秒の観測
	if (GameCount >= 90)
	{
		GameCount = 0;
		elapsedTime++;

		if (elapsedTime >= EndTime)
		{
			elapsedTime = 0;
			Clear = true;
		}
	}
	return Clear;
}

void GameState::ComboUpdate(float Distance)
{
	if (Distance < 0.3&&Distance>0.28)
	{
		TimePlus();
		EndTime++;
	}
}

void GameState::TimePlus()
{
	SetFontSize(100);
	DrawFormatString(650, 500, Rainbow[7], "1 SecUP", false);
}

void GameState::DrawScore()
{
	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	DrawBox(0, 0, 1900, 150, GetColor(0, 0, 0), TRUE);
	// 描画モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(650, 610, TimerHandle, true);
	DrawGraph(600, 40, ScoreGraph, true);
	SetFontSize(50);
	DrawFormatString(700, 600, Rainbow[7], "TIME %d", EndTime - elapsedTime, false);
	DrawFormatString(650, 40, Rainbow[7], "SCORE %d", Score, false);
}

void GameState::Draw()
{
	if (EndTime >= 5 && EndTime <= 10)
	{
		if (Countpos.x >= 600)
		{
			Countpos.x-=3;
		}
		// 例：透明度50%の白色の四角形を描画する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 700, 1600, 800, GetColor(0, 0, 0), TRUE);
		// 描画モードを元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(Countpos.x, Countpos.y, Rainbow[4], "残り10秒 ");
	}
	else
	{
		Countpos.x = 1600;
	}

	DrawScore();

}

void GameState::DrawClear()
{
	if (resultpos >= 830)
	{
		resultpos-=5;
	}
	++FrameCount;
	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(690, 180, 1550, 780, Rainbow[5], TRUE);
	// 描画モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(700, 190, ScoreBord, true);
	SetFontSize(70);
	DrawFormatString(1000, 280, Rainbow[7], "RESULT", false);
	DrawFormatString(900, 470, Rainbow[1], "HighSCORE%d", HighScore, false);
	SetFontSize(88);
	DrawFormatString(resultpos, 370, Rainbow[2], "YOURSCORE%d", Score, false);
	SetFontSize(50);
	DrawFormatString(950, 650, Rainbow[RainbowCount], "TITLE ENTER KEY");
	if (FrameCount >= 20)
	{
		FrameCount = 0;
		++RainbowCount;
	}
	if (RainbowCount == 4)
	{
		RainbowCount = 2;
	}
}
