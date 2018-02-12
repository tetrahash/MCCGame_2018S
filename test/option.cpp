#include "Header.h"
char Buf[256];

int Cirno[24];
int Cirno_ude[24];
int AKMR,AKML, Hit, Target;

int ban, banse, empty, reload;

int Cullentstatus;
int count,count2;
double Angle;

int Scene = SCENE_GAME;
int GameScreen;
int TmpScreen;
Character PLAYER;
int pinch = 0;

void LoadImages() {

	LoadDivGraph("img/cc8_cirno.png", 24, 6, 4, 32, 48, Cirno);
	LoadDivGraph("img/cc8_cirno_ude.png", 24, 6, 4, 32, 48, Cirno_ude);
	AKMR = LoadGraph("img/52px-Icon_weapon_AK47_2.png");
	AKML = LoadGraph("img/52px-Icon_weapon_AK47.png");
	Hit = LoadGraph("img/bakuha1.png");
	Target = LoadGraph("img/target.png");

	ban = LoadSoundMem("se/gun.ogg");
	banse = LoadSoundMem("se/gunse.ogg");
	reload = LoadSoundMem("se/reload.ogg");
	empty = LoadSoundMem("se/empty.ogg");
}

void GameInit() {
	Angle = 0;
	PLAYER.x = 128;						//プレーヤーの最初のx位置
	PLAYER.y = 0;						//プレーヤーの最初のy位置
	PLAYER.vx = 0;						//移動量は最初は0
	PLAYER.vy = 0;						//移動量は最初は0
	PLAYER.JUMPFLAG = 0;				//ジャンプ可=0、ジャンプ不可=1、応用次第では二段ジャンプも？
}

void DrawWall() {
	DrawBox(0, 0, 1280, 960, GetColor(144, 215, 236), 1);

	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			if (MAP1[i][j] == 1) {
				DrawBox(j*CHIPSIZE, i*CHIPSIZE, (j + 1)*CHIPSIZE, (i + 1)*CHIPSIZE, GetColor(0, 0, 0), 1);
			}
		}
	}
}

void Shoot();
void DrawPlayerWalk();
int KeyAnyCheck();

void DrawPlayer() {
	count++;
	if (KeyAnyCheck()) {
		count2++;
		switch (count2 / 100 % 8) {
		case 0:DrawPlayerWalk(); break;
		case 1:DrawPlayerWalk(); break;
		case 2:
			if (count2 / 20 % 2 == 0) 
				DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[0], true);
			else 
				DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[1], true);
			break;
		case 3:
			if (count2 / 20 % 2 == 0)
				DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno_ude[0], true);
			else
				DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno_ude[1], true);
			break;
		case 4:
			if (count2 / 25 % 2 == 0)
				DrawGraph(PLAYER.x, PLAYER.y - 6, Cirno_ude[9], true);
			else
				DrawGraph(PLAYER.x, PLAYER.y - 6, Cirno_ude[3], true);
				break;
		case 5:
			if (count2 / 20 % 5 == 0)
				DrawGraph(PLAYER.x, PLAYER.y - 6 - (count2 % 100), Cirno[3], true);
			else if (count2 / 20 % 5 == 1)
				DrawGraph(PLAYER.x, PLAYER.y - 6 - (count2 % 100), Cirno[6], true);
			else if (count2 / 20 % 5 == 2)
				DrawGraph(PLAYER.x, PLAYER.y - 6 - (count2 % 100), Cirno[16], true);
			else if (count2 / 20 % 5 == 3)
				DrawGraph(PLAYER.x, PLAYER.y - 6 - (count2 % 100), Cirno[18], true);
			else if (count2 / 20 % 5 == 4)
				DrawGraph(PLAYER.x, PLAYER.y - 6 - (count2 % 100), Cirno[21], true);
			break;
		case 6:
			if (count2 / 20 % 5 == 0)
				DrawRotaGraph(PLAYER.x+16, PLAYER.y - 100 + 5*(count2 % 20)+24,  1.0f, PI, Cirno[18], true);
			else if (count2 / 20 % 5 == 1)
				DrawRotaGraph(PLAYER.x + 16, PLAYER.y + 5 + 24, 1.0f, PI, Cirno[18], true);
			else if (count2 / 20 % 5 == 2)
				DrawRotaGraph(PLAYER.x + 16, PLAYER.y + 0 + 24, 1.0f, PI, Cirno[18], true);
			else if (count2 / 20 % 5 == 3)
				DrawRotaGraph(PLAYER.x + 16, PLAYER.y + 5 + 24, 1.0f, PI, Cirno[18], true);
			else if (count2 / 20 % 5 == 4)
				DrawRotaGraph(PLAYER.x + 16, PLAYER.y + 5 - (count2/10 % 10) + 24, 1.0f, PI - (count2 % 20)*PI/20, Cirno[18], true);
			break;
		case 7:
			if (count2 / 10 % 2 == 0)
				DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[6], true);
			else
				DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[12], true);
			break;
		//case 8:
		//case 9:
		}
	}
	else {
		DrawPlayerWalk();
		count2 = 0;
	}

	if (CheckHitKey(KEY_INPUT_X) != 0)
		Shoot();
}

void DrawPlayerWalk() {

	if (PLAYER.status == RIGHT) {
		if (count / 20 % 2 == 0) {
			DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[13], true);
			DrawRotaGraph(PLAYER.x + 22, PLAYER.y + 15, 0.7, Angle + PI / 4, AKMR, true);
		}
		else {
			DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[14], true);
			DrawRotaGraph(PLAYER.x + 22, PLAYER.y + 18, 0.7, Angle + PI / 4, AKMR, true);
		}
	}
	else if (PLAYER.status == LEFT) {
		if (count / 20 % 2 == 0) {
			DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[7], true);
			DrawRotaGraph(PLAYER.x + 10, PLAYER.y + 15, 0.7, -(Angle + PI / 4), AKML, true);
		}
		else {
			DrawGraph(PLAYER.x, PLAYER.y - 10, Cirno[8], true);
			DrawRotaGraph(PLAYER.x + 10, PLAYER.y + 18, 0.7, -(Angle + PI / 4), AKML, true);
		}
	}
}

void Shoot() {
	int x, y;
	int i = 0;
	PlaySoundMem(ban, DX_PLAYTYPE_BACK);
	PlaySoundMem(banse, DX_PLAYTYPE_BACK);
	if (PLAYER.status == RIGHT) {
		while (i < Range) {
			x = PLAYER.x + i;
			y = PLAYER.y + 25 + i * tan(Angle);
			if (CheckMap(x, y, 1) == 1) {
				DrawRotaGraph(x - 2, y, 0.2, 0, Hit, true);
				i = Range;
			}
			i++;
		}
	}
	else if (PLAYER.status == LEFT) {
		while (i < Range) {
			x = PLAYER.x - i;
			y = PLAYER.y + 25 - i * tan(-Angle);
			if (CheckMap(x, y, 1) == 1) {
				DrawRotaGraph(x + 2, y, 0.2, 0, Hit, true);
				i = Range;
			}
			i++;
		}
	}
}

int KeyAnyCheck() {
	char tmp[256];
	GetHitKeyStateAll(tmp);
	for (int i = 0; i < 256; i++) {
		if (tmp[i] == 1) {
			return 0;
		}
	}
	return 1;
}

int KeyUpdate() {
	char tmp[256];
	GetHitKeyStateAll(tmp);
	for (int i = 0; i < 256; i++) {
		if (tmp[i] == 1) {
			if (Buf[i] != 127)
			Buf[i]++;
		}
		else {
			Buf[i] = 0;
		}
	}
	return 0;
}

void ReloadPlayer()
{
	/*-----現在の座標を仮保存-----*/
	int tx = PLAYER.x;				//txに現在のプレーヤーのx座標を代入
	int ty = PLAYER.y;				//tyに現在のプレーヤーのy座標を代入

									/*-----キーボード入力受付-----*/
	if (CheckHitKey(KEY_INPUT_UP) != 0)
		Angle -= PI / 180;
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)
		Angle += PI / 180;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0 && CheckHitKey(KEY_INPUT_LSHIFT) != 0) {		//左が押されたら
		PLAYER.vx -= PLAYER_MOVESPEED/2;				//左の移動量(x軸に負の方向)を増やす
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) != 0) {			//左が押されたら
		PLAYER.vx -= PLAYER_MOVESPEED;				//左の移動量(x軸に負の方向)を増やす
		PLAYER.status = LEFT;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) != 0 && CheckHitKey(KEY_INPUT_LSHIFT) != 0) {		//右が押されたら
		PLAYER.vx += PLAYER_MOVESPEED/2;				//右の移動量(x軸に正の方向)を増やす
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {		//右が押されたら
		PLAYER.vx += PLAYER_MOVESPEED;				//右の移動量(x軸に正の方向)を増やす
		PLAYER.status = RIGHT;
	}
	else
		PLAYER.vx = 0;								//押されてなけば、移動量0

	if (CheckHitKey(KEY_INPUT_Z) != 0 && PLAYER.JUMPFLAG == 0) {		//Zキーが押されて、かつ、ジャンプ中じゃなければ
		PLAYER.vy -= PLAYER_JUMPPOWER;								//上の移動量(y軸に負の方向)を増やす
		PLAYER.JUMPFLAG = 1;										//ジャンプフラグ変数を1にして、着地していないことを知らせる
	}
	else if (PLAYER.JUMPFLAG == 1)									//着地していなければ
		PLAYER.vy += PLAYER_GRAVITY;								//y軸の制の方向に重力をかける
	if (PLAYER.vy > CHIPSIZE)										//y軸方向の移動量がマップチップの大きさを超えたら
		PLAYER.vy = 32;												//移動スピード制限


																	/*-----マップとの衝突を補正する-----*/

																	/*Y軸方向の確認*/
	ty += PLAYER.vy;			//仮移動
								//左上か右上が壁に触れていたら(頭がぶつかったら)
	if (CheckMap(tx + 1, ty + 1, 1) == 1 || CheckMap(tx + CHIPSIZE - 1, ty + 1, 1) == 1) {
		PLAYER.y = ty / CHIPSIZE * CHIPSIZE + CHIPSIZE;		//位置を正してPLAYER.yに代入
		PLAYER.vy = 0;									//移動量を0に
		PLAYER.JUMPFLAG = 1;							//着地していないことを知らせる
	}
	//左下か右下が壁に触れていたら(着地したら)
	else if (CheckMap(tx + 1, ty + CHIPSIZE - 1, 1) == 1 || CheckMap(tx + CHIPSIZE - 1, ty + CHIPSIZE - 1, 1) == 1) {
		PLAYER.y = ty / CHIPSIZE * CHIPSIZE;				//位置を正してPLAYER.yに代入
		PLAYER.vy = 0;									//移動量を0に
		PLAYER.JUMPFLAG = 0;							//着地していることを知らせる
	}
	//上下がどこにも触れていなければ(着地していなければ)
	else {
		PLAYER.y = ty;									//仮移動した値をそのまま使う
		PLAYER.JUMPFLAG = 1;							//着地していないことを知らせる
	}
	ty = PLAYER.y;				//tyに新しい値を入れなおす


								/*X軸方向の確認*/
	tx += PLAYER.vx;			//仮移動
								//左上か左下が壁に触れていたら(左の壁にぶつかったら)
	if (CheckMap(tx + 1, ty + 1, 1) == 1 || CheckMap(tx + 1, ty + CHIPSIZE - 1, 1) == 1) {
		PLAYER.x = tx / CHIPSIZE * CHIPSIZE + CHIPSIZE;	//位置を正してPLAYER.xに代入
	}
	//右上か右下が壁に触れていたら(右の壁にぶつかったら)
	else if (CheckMap(tx + CHIPSIZE - 1, ty + 1, 1) == 1 || CheckMap(tx + CHIPSIZE - 1, ty + CHIPSIZE - 1, 1) == 1) {
		PLAYER.x = tx / CHIPSIZE * CHIPSIZE;				//位置を正してPLAYER.xに代入
	}
	//左右がどこにも触れていなければ
	else {
		PLAYER.x = tx;			//仮移動した値をそのまま使う
	}
	PLAYER.vx = 0;				//x軸方向の移動量は一旦0にする
}

int CheckMap(int x, int y, int map) {
	//マップが複数あるときは、ここで分岐して使ってね。
	if (x <= 0)
		return 1;
	if (y <= 0)
		return 1;
	if (map == 1)
		return MAP1[y / CHIPSIZE][x / CHIPSIZE];		//該当箇所のマップデータを返す(1は壁、0は空白)
}


void DrawCurrentScreen()
{
	int x, y;			//切り取る部分の左上の座標を格納する。
	if (Buf[KEY_INPUT_C] != 0)
		pinch++;
	if (Buf[KEY_INPUT_V] != 0)
		pinch = 0;

	x = PLAYER.x + CHIPSIZE / 2 - (WIN_X + pinch) / 2;				//ジョニー君が画面中央に来るようにX座標を指定
	y = PLAYER.y + CHIPSIZE / 2 - (WIN_Y + pinch) / 2;				//ジョニー君が画面中央に来るようにY座標を指定

															//はみ出し防止
	if (x < 0)			//左が0未満(左側が余っている)場合
		x = 0;			//0より下にはいかせない
	if (y < 0)			//上が0未満(上側が余っている)場合
		y = 0;			//0より下にはいかせない
	if (x>640)			//左が640より大きい(右側が余っている)場合
		x = 640;		//640より大きくしない
	if (y>480)			//上が480より大きい(下側が余っている)場合
		y = 480;		//480より大きくしない

	SetDrawScreen(DX_SCREEN_BACK);

	ClearDrawScreen();

	DrawRectExtendGraph(0, 0, WIN_X, WIN_Y, x, y, WIN_X + pinch, WIN_Y + pinch, GameScreen, 1);		//切り取って描画


	DrawExtendGraph(0, 0, WIN_X, WIN_Y, TmpScreen, 1);
	DrawFormatString(0, 0, WHITE, "%dx:%dy:%d", Buf[KEY_INPUT_C], x, y);
}