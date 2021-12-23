//========================================================
//
//						モデル
//					AUTHOR:越本愛彪
//
//========================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//マクロ定義
#define MAX_MODEL (1)				//モデルの最大数

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;				//モデルの位置
	D3DXVECTOR3 rot;				//モデルの角度
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	D3DXVECTOR3 vtxMin, vtxMax;		//モデルの頂点の最大値・最小値
}MODEL;

//プロトタイプ宣言
void InitModel(void);				//モデル初期化処理
void UninitModel(void);				//モデル終了処理
void UpdataModel(void);				//モデル更新処理
void DrawModel(void);				//モデル描画処理
MODEL *GetModel(void);				//モデルの情報を取得する処理

#endif