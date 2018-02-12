#ifndef DEF_HEADER_H

#define DEF_HEADER_H


#include "DxLib.h"
#include <math.h>

/*-----マクロ定義-----*/
#define MAP_X 40						//マップのX方向のチップの数を指定
#define MAP_Y 30						//マップのY方向のチップの数を指定
#define CHIPSIZE 32						//マップチップのサイズを指定
#define WIN_X 640						//ウインドウのX軸方向の大きさ
#define WIN_Y 480						//ウインドウのY軸方向の大きさ

#define PLAYER_MOVESPEED 5				//プレーヤーの移動速度を指定
#define PLAYER_JUMPPOWER 20				//プレーヤーのジャンプ力を指定
#define PLAYER_GRAVITY 2				//プレーヤーの重力を指定

#define WHITE GetColor(255,255,255)		//白を定義
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