#ifndef DEF_HEADER_H

#define DEF_HEADER_H


#include "DxLib.h"
#include <math.h>

/*-----�}�N����`-----*/
#define MAP_X 40						//�}�b�v��X�����̃`�b�v�̐����w��
#define MAP_Y 30						//�}�b�v��Y�����̃`�b�v�̐����w��
#define CHIPSIZE 32						//�}�b�v�`�b�v�̃T�C�Y���w��
#define WIN_X 640						//�E�C���h�E��X�������̑傫��
#define WIN_Y 480						//�E�C���h�E��Y�������̑傫��

#define PLAYER_MOVESPEED 5				//�v���[���[�̈ړ����x���w��
#define PLAYER_JUMPPOWER 20				//�v���[���[�̃W�����v�͂��w��
#define PLAYER_GRAVITY 2				//�v���[���[�̏d�͂��w��

#define WHITE GetColor(255,255,255)		//�����`
#define PI 3.141592654
#define Range 1000

typedef enum {
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_GAMEMENU,
} SCENE;

typedef enum {
	RIGHT,
	LEFT,
	UP,
	DOWN,
	RIGHT_STOP,
	LEFT_STOP,
} Status;

class Character {
public:
	int x, y;
	int vx, vy;
	int JUMPFLAG;
	int status;
};

extern Character PLAYER;

extern int Scene;
extern int GameScreen;
extern int MAP1[MAP_Y][MAP_X];


//void Title();
void GameMain();
//void GameMenu();
void LoadImages();
void GameInit();
int KeyUpdate();
void DrawCurrentScreen();
void DrawPlayer();
void DrawWall();
void ReloadPlayer();
int CheckMap(int, int, int);

#endif