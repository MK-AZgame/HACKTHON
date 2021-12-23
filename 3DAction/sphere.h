//========================================================
//
//					メッシュ(球)
//					AUTHOR:越本愛彪
//
//========================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

//マクロ定義
#define SPHERE_SIZE (50.0f)				//球の一ポリゴンのサイズ

//プロトタイプ宣言
void InitSphere(void);					//球初期化処理
void UninitSphere(void);				//球終了処理
void UpdataSphere(void);				//球更新処理
void DrawSphere(void);					//球描画処理

#endif 

