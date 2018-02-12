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
	PLAYER.x = 128;						//�v���[���[�̍ŏ���x�ʒu
	PLAYER.y = 0;						//�v���[���[�̍ŏ���y�ʒu
	PLAYER.vx = 0;						//�ړ��ʂ͍ŏ���0
	PLAYER.vy = 0;						//�ړ��ʂ͍ŏ���0
	PLAYER.JUMPFLAG = 0;				//�W�����v��=0�A�W�����v�s��=1�A���p����ł͓�i�W�����v���H
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
	/*-----���݂̍��W�����ۑ�-----*/
	int tx = PLAYER.x;				//tx�Ɍ��݂̃v���[���[��x���W����
	int ty = PLAYER.y;				//ty�Ɍ��݂̃v���[���[��y���W����

									/*-----�L�[�{�[�h���͎�t-----*/
	if (CheckHitKey(KEY_INPUT_UP) != 0)
		Angle -= PI / 180;
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)
		Angle += PI / 180;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0 && CheckHitKey(KEY_INPUT_LSHIFT) != 0) {		//���������ꂽ��
		PLAYER.vx -= PLAYER_MOVESPEED/2;				//���̈ړ���(x���ɕ��̕���)�𑝂₷
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) != 0) {			//���������ꂽ��
		PLAYER.vx -= PLAYER_MOVESPEED;				//���̈ړ���(x���ɕ��̕���)�𑝂₷
		PLAYER.status = LEFT;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) != 0 && CheckHitKey(KEY_INPUT_LSHIFT) != 0) {		//�E�������ꂽ��
		PLAYER.vx += PLAYER_MOVESPEED/2;				//�E�̈ړ���(x���ɐ��̕���)�𑝂₷
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {		//�E�������ꂽ��
		PLAYER.vx += PLAYER_MOVESPEED;				//�E�̈ړ���(x���ɐ��̕���)�𑝂₷
		PLAYER.status = RIGHT;
	}
	else
		PLAYER.vx = 0;								//������ĂȂ��΁A�ړ���0

	if (CheckHitKey(KEY_INPUT_Z) != 0 && PLAYER.JUMPFLAG == 0) {		//Z�L�[��������āA���A�W�����v������Ȃ����
		PLAYER.vy -= PLAYER_JUMPPOWER;								//��̈ړ���(y���ɕ��̕���)�𑝂₷
		PLAYER.JUMPFLAG = 1;										//�W�����v�t���O�ϐ���1�ɂ��āA���n���Ă��Ȃ����Ƃ�m�点��
	}
	else if (PLAYER.JUMPFLAG == 1)									//���n���Ă��Ȃ����
		PLAYER.vy += PLAYER_GRAVITY;								//y���̐��̕����ɏd�͂�������
	if (PLAYER.vy > CHIPSIZE)										//y�������̈ړ��ʂ��}�b�v�`�b�v�̑傫���𒴂�����
		PLAYER.vy = 32;												//�ړ��X�s�[�h����


																	/*-----�}�b�v�Ƃ̏Փ˂�␳����-----*/

																	/*Y�������̊m�F*/
	ty += PLAYER.vy;			//���ړ�
								//���ォ�E�オ�ǂɐG��Ă�����(�����Ԃ�������)
	if (CheckMap(tx + 1, ty + 1, 1) == 1 || CheckMap(tx + CHIPSIZE - 1, ty + 1, 1) == 1) {
		PLAYER.y = ty / CHIPSIZE * CHIPSIZE + CHIPSIZE;		//�ʒu�𐳂���PLAYER.y�ɑ��
		PLAYER.vy = 0;									//�ړ��ʂ�0��
		PLAYER.JUMPFLAG = 1;							//���n���Ă��Ȃ����Ƃ�m�点��
	}
	//�������E�����ǂɐG��Ă�����(���n������)
	else if (CheckMap(tx + 1, ty + CHIPSIZE - 1, 1) == 1 || CheckMap(tx + CHIPSIZE - 1, ty + CHIPSIZE - 1, 1) == 1) {
		PLAYER.y = ty / CHIPSIZE * CHIPSIZE;				//�ʒu�𐳂���PLAYER.y�ɑ��
		PLAYER.vy = 0;									//�ړ��ʂ�0��
		PLAYER.JUMPFLAG = 0;							//���n���Ă��邱�Ƃ�m�点��
	}
	//�㉺���ǂ��ɂ��G��Ă��Ȃ����(���n���Ă��Ȃ����)
	else {
		PLAYER.y = ty;									//���ړ������l�����̂܂܎g��
		PLAYER.JUMPFLAG = 1;							//���n���Ă��Ȃ����Ƃ�m�点��
	}
	ty = PLAYER.y;				//ty�ɐV�����l�����Ȃ���


								/*X�������̊m�F*/
	tx += PLAYER.vx;			//���ړ�
								//���ォ�������ǂɐG��Ă�����(���̕ǂɂԂ�������)
	if (CheckMap(tx + 1, ty + 1, 1) == 1 || CheckMap(tx + 1, ty + CHIPSIZE - 1, 1) == 1) {
		PLAYER.x = tx / CHIPSIZE * CHIPSIZE + CHIPSIZE;	//�ʒu�𐳂���PLAYER.x�ɑ��
	}
	//�E�ォ�E�����ǂɐG��Ă�����(�E�̕ǂɂԂ�������)
	else if (CheckMap(tx + CHIPSIZE - 1, ty + 1, 1) == 1 || CheckMap(tx + CHIPSIZE - 1, ty + CHIPSIZE - 1, 1) == 1) {
		PLAYER.x = tx / CHIPSIZE * CHIPSIZE;				//�ʒu�𐳂���PLAYER.x�ɑ��
	}
	//���E���ǂ��ɂ��G��Ă��Ȃ����
	else {
		PLAYER.x = tx;			//���ړ������l�����̂܂܎g��
	}
	PLAYER.vx = 0;				//x�������̈ړ��ʂ͈�U0�ɂ���
}

int CheckMap(int x, int y, int map) {
	//�}�b�v����������Ƃ��́A�����ŕ��򂵂Ďg���ĂˁB
	if (x <= 0)
		return 1;
	if (y <= 0)
		return 1;
	if (map == 1)
		return MAP1[y / CHIPSIZE][x / CHIPSIZE];		//�Y���ӏ��̃}�b�v�f�[�^��Ԃ�(1�͕ǁA0�͋�)
}


void DrawCurrentScreen()
{
	int x, y;			//�؂��镔���̍���̍��W���i�[����B
	if (Buf[KEY_INPUT_C] != 0)
		pinch++;
	if (Buf[KEY_INPUT_V] != 0)
		pinch = 0;

	x = PLAYER.x + CHIPSIZE / 2 - (WIN_X + pinch) / 2;				//�W���j�[�N����ʒ����ɗ���悤��X���W���w��
	y = PLAYER.y + CHIPSIZE / 2 - (WIN_Y + pinch) / 2;				//�W���j�[�N����ʒ����ɗ���悤��Y���W���w��

															//�͂ݏo���h�~
	if (x < 0)			//����0����(�������]���Ă���)�ꍇ
		x = 0;			//0��艺�ɂ͂������Ȃ�
	if (y < 0)			//�オ0����(�㑤���]���Ă���)�ꍇ
		y = 0;			//0��艺�ɂ͂������Ȃ�
	if (x>640)			//����640���傫��(�E�����]���Ă���)�ꍇ
		x = 640;		//640���傫�����Ȃ�
	if (y>480)			//�オ480���傫��(�������]���Ă���)�ꍇ
		y = 480;		//480���傫�����Ȃ�

	SetDrawScreen(DX_SCREEN_BACK);

	ClearDrawScreen();

	DrawRectExtendGraph(0, 0, WIN_X, WIN_Y, x, y, WIN_X + pinch, WIN_Y + pinch, GameScreen, 1);		//�؂����ĕ`��


	DrawExtendGraph(0, 0, WIN_X, WIN_Y, TmpScreen, 1);
	DrawFormatString(0, 0, WHITE, "%dx:%dy:%d", Buf[KEY_INPUT_C], x, y);
}