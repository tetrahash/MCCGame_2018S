#include "Header.h"

void GameMain() {

	SetDrawScreen(GameScreen);
	ClearDrawScreen();

	ReloadPlayer();

	DrawWall();
	DrawPlayer();

	DrawCurrentScreen();
}