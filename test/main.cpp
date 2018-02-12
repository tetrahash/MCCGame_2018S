#include "Header.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(WIN_X, WIN_Y, 32);				//ウインドウサイズを設定
	ChangeWindowMode(true);						//ウインドウモードに変更
	if (DxLib_Init() != 0)						//DXライブラリ初期化処理
		return -1;								//異常が起きたときは強制終了
	GameScreen = MakeScreen(1280, 960);
	LoadImages();
	GameInit();
	//
	while (ProcessMessage() == 0 && ScreenFlip() == 0) {

		KeyUpdate();
		switch (Scene) {
		//case 0:Title(); break;
		case 1:GameMain(); break;
		//case 2:GameMenu(); break;
		default:break;
		}
	}
}

