//========================================================
//
//						入力
//					AUTHOR:越本愛彪
//========================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP = 0,				//上
	JOYKEY_DOWN,				//下
	JOYKEY_LEFT,				//左
	JOYKEY_RIGHT,				//右
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_L3,
	JOYKEY_R3,
	JOYKEY_L1,
	JOYKEY_R1,					//弾の発射
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX
} JOYKEY;

//プロトタイプ宣言
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdataJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool GetJoypadTrigger(JOYKEY key);
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdataKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

#endif


