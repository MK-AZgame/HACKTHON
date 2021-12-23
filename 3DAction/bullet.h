//========================================================
//
//							弾
//					AUTHOR:越本愛彪
//
//========================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//プロトタイプ宣言
void Initbullet(void);								//弾の初期化
void Uninitbullet(void);							//弾の終了
void Updatabullet(void);							//弾の更新
void Drawbullet(void);								//弾の描画
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//弾の設定

#endif
