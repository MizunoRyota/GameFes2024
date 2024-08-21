#pragma once

class Player;
class Obstacle;

class GameState
{
public:
	GameState();
	~GameState();
	const int & GetTime() const { return elapsedTime; }
	void Init();
	void GameTitle();
	void GameReady();
	bool GameUpdate(const VECTOR &playerpos);
	void ComboUpdate(float Length);
	void TimePlus();
	void DrawClear();
	void DrawScore();
	void Draw();
private:
	LONGLONG NowGameCount;
	VECTOR Countpos;
	int GameClearTime;
	int resultpos;
	int Clear;
	int Rainbow[8];
	int TitleColor;
	int RainbowCount;
	int FrameCount;
	int Title;
	int TimerHandle;
	int EscapeHandle;
	int EndTime;
	int Controller;
	int ScoreGraph;
	int TimeGraph;
	int Start;
	int StartCount;
	int GameCount = 0;
	int elapsedTime = 0;
	int Score;
	int HighScore;
	int ScoreBord;
	int goal = LoadSoundMem("BGM/game/goal.mp3");
};

