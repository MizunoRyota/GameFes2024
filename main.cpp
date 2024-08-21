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
	STATE_TITLE,		// �^�C�g��.
	STATE_READY,        //����
	STATE_GAME,			// �Q�[����.
	STATE_END,
	STATE_CLEAR,		// �N���A.
	STATE_GAMEOVER,		// �Q�[���I�[�o�[.
};
/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	srand(static_cast<unsigned int>(time(NULL)));  // �����_���V�[�h��ݒ�

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// ��ʃ��[�h�̃Z�b�g
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	SetDrawScreen(DX_SCREEN_BACK);	// ����ʂ�`��Ώۂɂ���
	SetUseZBufferFlag(TRUE);		// �y�o�b�t�@���g�p����
	SetWriteZBufferFlag(TRUE);		// �y�o�b�t�@�ւ̏������݂��s��
	SetUseBackCulling(TRUE);		// �o�b�N�J�����O���s��

	int gameStatus = STATE_TITLE;
	const int ObstructNum = 6;
	int NowState = 0;
	int Clearflg = 0;
	bool end = false;
	
	//BGM������
	int title = LoadSoundMem("BGM/title/title.mp3");
	int play = LoadSoundMem("BGM/game/game.mp3");
	int gameover = LoadSoundMem("BGM/end/gameover.mp3");
	int click = LoadSoundMem("BGM/click.mp3");
	int clear = LoadSoundMem("BGM/clear/clear.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, title);
	ChangeVolumeSoundMem(255 * 50 / 100, play);
	ChangeVolumeSoundMem(255 * 50 / 100, gameover);
	ChangeVolumeSoundMem(255 * 50 / 100, clear);

	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "data/font.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	//// �t�H���g�̕ύX
	ChangeFont("New Tegomin", DX_CHARSET_DEFAULT);
	// ����
	GameState* game = new GameState();
	Camera* camera = new Camera();
	Player* player = new Player();
	Skydome* skydome = new Skydome();
	Map* map = new Map();
	HitChecker* hitcheck[ObstructNum];
	Plane* plane = new Plane();
	Obstacle* obstacle[ObstructNum];
	//ObstructNum�̉񐔏�Q���쐬
	for (int i = 0; i < ObstructNum; i++)
	{
		hitcheck[i] = new HitChecker();
		obstacle[i] = new Obstacle();
		obstacle[i]->Init();//��Q���̏�����
	}
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;

	bool debugPauseFlag = false;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// �ڂ��񂨂�����
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// �ڂ��񂨂�����
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//�^�C�g�����
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
					//�Q�[����ԕω�
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
					//�Q�[����ԕω�
					gameStatus = STATE_GAME;
				}
			}

			//�Q�[����
			if (gameStatus == STATE_GAME)
			{
				PlaySoundMem(play, DX_PLAYTYPE_LOOP, false);
				frameTime = GetNowHiPerformanceCount();
				// �v���C���[����.
				player->Update();
				//��s�@�̐���
				plane->Update(player->GetPos());
				//�J�����̐���
				camera->Update(player->GetPos());
				//�X�J�C�h�[������
				skydome->SkydomeUpdate();
				//�N���A���Ă��邩�m�F
				Clearflg = game->GameUpdate(player->GetPos());
				for (int i = 0; i < ObstructNum; i++)
				{
					if (obstacle[i]->GetIsActive() == false)//isActive��false�̎���������W�Ȃǂ������_������
					{
						obstacle[i]->Fall(player->GetPos());
					}
				}
				for (int i = 0; i < ObstructNum; i++)
				{
					if (obstacle[i]->GetIsActive() == true)//isActive��true�̎�����
					{
						obstacle[i]->Update();
						game->ComboUpdate(hitcheck[i]->GetDistance());
						//�`�F�b�N��TRUE�Ȃ�Q�[���I�[�o�[
						if (hitcheck[i]->Check(player->GetPos(), obstacle[i]->GetPos()))
						{
							NowState = hitcheck[i]->DeadJudge(player->GetPos(), obstacle[i]->GetPos());
						}
					}
				}

				// ��ʂ�����������
				ClearDrawScreen();

				// �`��
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
					for (int i = 0; i < 255; ++i) // �t���b�V����i�K�I�ɉ�����
					{
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, i); // �A���t�@�l��ύX
						DrawBox(0, 0, 1980, 1080, GetColor(255, 255, 255), TRUE); // ��ʑS�̂𔒂�����
						ScreenFlip(); // ��ʍX�V
					}
					gameStatus = STATE_CLEAR;
				}
			}

			if (gameStatus == STATE_END)
			{
				StopSoundMem(play);

				//���ʉ�
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
						obstacle[i]->Init();//��Q���̏�����
					}
					//�v���C���[�̈ʒu�̏�����
					player->Init();
					//�Q�[����ԕω�
					gameStatus = STATE_TITLE;
				}
			}

			// ����ʂ̓��e��\��ʂɔ��f������
			ScreenFlip();

			// �G��60fps�Œ�
			while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
		}
	}

	// ��n��
	delete(player);
	delete(camera);
	delete(map);
	for (size_t i = 0; i < ObstructNum; i++)
	{
		delete(obstacle[i]);
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}