#include "DxLib.h"
#include <ctime>
#include<vector>
#include"Game.h"
#include"skydome.h"
#include"map.h"
#include"Obstacle.h"
#include"player.h"
#include"Camera.h"
#include"plane.h"
#include"HitChecker.h"

enum STATE
{
	STATE_TITLE,		// タイトル.
	STATE_READY,        //準備
	STATE_GAME,			// ゲーム中.
	STATE_END,
	STATE_CLEAR,		// クリア.
	STATE_GAMEOVER,		// ゲームオーバー.
};
/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	srand(static_cast<unsigned int>(time(NULL)));  // ランダムシードを設定

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う

	int gameStatus = STATE_TITLE;
	const int ObstructNum = 6;
	int NowState = 0;
	int Clearflg = 0;
	bool end = false;
	
	//BGM初期化
	int title = LoadSoundMem("BGM/title/title.mp3");
	int play = LoadSoundMem("BGM/game/game.mp3");
	int gameover = LoadSoundMem("BGM/end/gameover.mp3");
	int click = LoadSoundMem("BGM/click.mp3");
	int clear = LoadSoundMem("BGM/clear/clear.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, title);
	ChangeVolumeSoundMem(255 * 50 / 100, play);
	ChangeVolumeSoundMem(255 * 50 / 100, gameover);
	ChangeVolumeSoundMem(255 * 50 / 100, clear);

	// ********** フォントのロード **********
	LPCSTR font_path = "data/font.otf"; // 読み込むフォントファイルのパス
	//// フォントの変更
	ChangeFont("New Tegomin", DX_CHARSET_DEFAULT);
	// 生成
	GameState* game = new GameState();
	Camera* camera = new Camera();
	Player* player = new Player();
	Skydome* skydome = new Skydome();
	Map* map = new Map();
	HitChecker* hitcheck[ObstructNum];
	Plane* plane = new Plane();
	Obstacle* obstacle[ObstructNum];
	//ObstructNumの回数障害物作成
	for (int i = 0; i < ObstructNum; i++)
	{
		hitcheck[i] = new HitChecker();
		obstacle[i] = new Obstacle();
		obstacle[i]->Init();//障害物の初期化
	}
	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;

	bool debugPauseFlag = false;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// ぼたんおしたら
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// ぼたんおしたら
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//タイトル画面
			if (gameStatus == STATE_TITLE)
			{

				StopSoundMem(clear);

				PlaySoundMem(title, DX_PLAYTYPE_LOOP, false);
				map->Titile();
				skydome->SkydomeTitle();
				camera->GameTitle(map->GetPos());
				ClearDrawScreen();
				skydome->SkydomeDraw();
				map->Draw();
				game->GameTitle();
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(click, DX_PLAYTYPE_BACK, true);
					WaitTimer(200);
					ClearDrawScreen();
					//ゲーム状態変化
					gameStatus = STATE_READY;
				}
			}

			if (gameStatus == STATE_READY)
			{
				map->Init();
				skydome->SkydomeUpdate();
				camera->Update(player->GetPos());
				ClearDrawScreen();
				skydome->SkydomeDraw();
				map->Draw();
				game->GameReady();

				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(click, DX_PLAYTYPE_BACK, true);
					StopSoundMem(title);
					ClearDrawScreen();
					//ゲーム状態変化
					gameStatus = STATE_GAME;
				}
			}

			//ゲーム中
			if (gameStatus == STATE_GAME)
			{
				PlaySoundMem(play, DX_PLAYTYPE_LOOP, false);
				frameTime = GetNowHiPerformanceCount();
				// プレイヤー制御.
				player->Update();
				//飛行機の制御
				plane->Update(player->GetPos());
				//カメラの制御
				camera->Update(player->GetPos());
				//スカイドーム制御
				skydome->SkydomeUpdate();
				//クリアしているか確認
				Clearflg = game->GameUpdate(player->GetPos());
				for (int i = 0; i < ObstructNum; i++)
				{
					if (obstacle[i]->GetIsActive() == false)//isActiveがfalseの時落ちる座標などをランダム生成
					{
						obstacle[i]->Fall(player->GetPos());
					}
				}
				for (int i = 0; i < ObstructNum; i++)
				{
					if (obstacle[i]->GetIsActive() == true)//isActiveがtrueの時落下
					{
						obstacle[i]->Update();
						game->ComboUpdate(hitcheck[i]->GetDistance());
						//チェックがTRUEならゲームオーバー
						if (hitcheck[i]->Check(player->GetPos(), obstacle[i]->GetPos()))
						{
							NowState = hitcheck[i]->DeadJudge(player->GetPos(), obstacle[i]->GetPos());
						}
					}
				}

				// 画面を初期化する
				ClearDrawScreen();

				// 描画
				skydome->SkydomeDraw();
				map->Draw();
				player->Draw();
				plane->Draw();
				for (int i = 0; i < ObstructNum; i++)
				{
					obstacle[i]->Draw();
				}
				game->Draw();
				if (NowState == true)
				{
					gameStatus = STATE_END;
				}
				if (Clearflg == true)
				{
					for (int i = 0; i < 255; ++i) // フラッシュを段階的に加える
					{
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, i); // アルファ値を変更
						DrawBox(0, 0, 1980, 1080, GetColor(255, 255, 255), TRUE); // 画面全体を白くする
						ScreenFlip(); // 画面更新
					}
					gameStatus = STATE_CLEAR;
				}
			}

			if (gameStatus == STATE_END)
			{
				StopSoundMem(play);

				//効果音
				PlaySoundMem(gameover, DX_PLAYTYPE_LOOP, false);

				end = player->ClearUpdate();
				plane->Update(player->GetPos());
				camera->Update(player->GetPos());
				skydome->SkydomeUpdate();
				ClearDrawScreen();
				skydome->SkydomeDraw();
				map->Draw();
				player->ClearDraw();
				if (end == true)
				{
					gameStatus = STATE_CLEAR;
				}
			}

			if (gameStatus == STATE_CLEAR)
			{
				StopSoundMem(gameover);
				StopSoundMem(play);

				StopSoundMem(clear);
				PlaySoundMem(clear, DX_PLAYTYPE_LOOP, false);

				NowState = 0;
				Clearflg = 0;
				game->Init();
				skydome->SkydomeTitle();
				plane->GameClear();
				ClearDrawScreen();
				skydome->SkydomeDraw();
				plane->Draw();
				game->DrawClear();
				camera->GameClear(plane->GetPos());
				if (CheckHitKey(KEY_INPUT_RETURN))
				{
					plane->Init();
					map->Init();
					for (int i = 0; i < ObstructNum; i++)
					{
						hitcheck[i]->Init();
						obstacle[i]->Init();//障害物の初期化
					}
					//プレイヤーの位置の初期化
					player->Init();
					//ゲーム状態変化
					gameStatus = STATE_TITLE;
				}
			}

			// 裏画面の内容を表画面に反映させる
			ScreenFlip();

			// 雑に60fps固定
			while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
		}
	}

	// 後始末
	delete(player);
	delete(camera);
	delete(map);
	for (size_t i = 0; i < ObstructNum; i++)
	{
		delete(obstacle[i]);
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}