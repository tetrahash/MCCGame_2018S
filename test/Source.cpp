#include <math.h>
#include "DxLib.h"
#define PI 3.141592654

char Buf[256];

int KeyUpdate() {
	char tmp[256];
	GetHitKeyStateAll(tmp);
	for (int i = 0; i < 256; i++) {
		if (tmp[i] == 1) {
			Buf[i]++;
		}
		else {
			Buf[i] = 0;
		}
	}
}

enum {
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_GAMEMENU,
};


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	int count = 0;
	int HitcountA = SCENE_TITLE;
	int HitcountB = 0;


	int Cirno[24];
	LoadDivGraph("img/cc8_cirno.png", 24, 6, 4, 32, 48, Cirno);
	int AKM = LoadGraph("img/52px-Icon_weapon_AK47_2.png");
	int Hit = LoadGraph("img/bakuha1.png");
	int Target = LoadGraph("img/target.png");

	int ban = LoadSoundMem("se/gun.ogg");
	int banse = LoadSoundMem("se/gunse.ogg");
	int reload = LoadSoundMem("se/reload.ogg");
	int empty = LoadSoundMem("se/empty.ogg");
	int bullet = 20;
	double Angle = PI / 4;


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		KeyUpdate();
		unsigned int Cr = GetColor(255, 255, 255);
		DrawBox(0, 0, 700, 700, Cr, true);
		DrawFormatString(10, 10, 0, "のこり%d発", bullet);
		DrawFormatString(10, 30, 0, "上段ヒット数%d：下段ヒット数%d", HitcountA,HitcountB);

		if (Buf[KEY_INPUT_RIGHT] != 0) {
			count += 3;
		}
		if (Buf[KEY_INPUT_LEFT] != 0) {
			count -= 3;
		}
		if (Buf[KEY_INPUT_UP] != 0) {
			Angle -= PI / 180;
		}
		if (Buf[KEY_INPUT_DOWN] != 0) {
			Angle += PI / 180;
		}
		if (Buf[KEY_INPUT_Z] == SCENE_GAME && bullet > 0) {
			bullet--;
			PlaySoundMem(ban, DX_PLAYTYPE_BACK);
			PlaySoundMem(banse, DX_PLAYTYPE_BACK);
			int Hity = (tan(Angle - PI / 4) * (600 - count));
			DrawRotaGraph(600, 425 + Hity, 0.2, 0, Hit, true);
			if (425 + Hity > 90 && 425 + Hity < 110) {
				HitcountA++;
			}
			if (425 + Hity > 415 && 425 + Hity < 435) {
				HitcountB++;
			}
		}
		else if (Buf[KEY_INPUT_Z] == SCENE_GAME) {
			PlaySoundMem(empty, DX_PLAYTYPE_BACK);
		}
		if (Buf[KEY_INPUT_C] != 0 && Buf[KEY_INPUT_C] % 2 == 0 && bullet > 0) {
			bullet--;
			PlaySoundMem(ban, DX_PLAYTYPE_BACK);
			PlaySoundMem(banse, DX_PLAYTYPE_BACK);
			int Hity = (tan(Angle - PI / 4) * (600 - count));
			DrawRotaGraph(600, 425 + Hity, 0.2, 0, Hit, true);
			if (425 + Hity > 90 && 425 + Hity < 110) {
				HitcountA++;
			}
			if (425 + Hity > 415 && 425 + Hity < 435) {
				HitcountB++;
			}
			Angle += (GetRand(8) - 4)*PI / 180;
		}
		else if (Buf[KEY_INPUT_C] == 2) {
			PlaySoundMem(empty, DX_PLAYTYPE_BACK);
		}

		if (Buf[KEY_INPUT_X] == 1 && bullet == 0) {
			PlaySoundMem(reload, DX_PLAYTYPE_BACK);
			bullet = 50;
		}
			
		if (count / 20 % 2 == 0) {
			DrawGraph(count, 400, Cirno[13], true);
			DrawRotaGraph(count + 22, 428, 0.7, Angle, AKM, true);
		}
		else {
			DrawGraph(count, 400, Cirno[14], true);
			DrawRotaGraph(count + 22, 425, 0.7, Angle, AKM, true);
		}


		DrawLine(0, 400 + 38, 700, 400 + 38, 0);
		DrawLine(600, 0, 600, 700, true);
		DrawRotaGraph(600, 100, 0.1, 0, Target, true);
		DrawRotaGraph(600, 425, 0.1, 0, Target, true);
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

