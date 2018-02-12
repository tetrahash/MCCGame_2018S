#include "Header.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(WIN_X, WIN_Y, 32);				//�E�C���h�E�T�C�Y��ݒ�
	ChangeWindowMode(true);						//�E�C���h�E���[�h�ɕύX
	if (DxLib_Init() != 0)						//DX���C�u��������������
		return -1;								//�ُ킪�N�����Ƃ��͋����I��
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

