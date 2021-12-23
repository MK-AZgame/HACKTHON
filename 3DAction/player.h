//========================================================
//
//					プレイヤー
//					AUTHOR:越本愛彪
//
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 posOld;					//前回の位置
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 rotDest;				//目的の向き
} Player;

//モデル構造体
typedef struct
{
	LPD3DXMESH pMesh;					//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;				//頂点バッファへのポインタ
	DWORD nNumMat;						
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 pos;					//パーツの位置
	D3DXVECTOR3 rot;					//パーツの向き
	int ParentIdx;						//親の番号
}ModelParts;


//プロトタイプ宣言
void InitPlayer(void);					//プレイヤーの初期化処理
void UninitPlayer(void);				//プレイヤーの終了処理
void UpdataPlayer(void);				//プレイヤーの更新処理
void DrawPlayer(void);					//プレイヤーの描画処理
void CollisionObject(void);				//オブジェクト（モデル）との当たり判定
Player *GetPlayer(void);				//プレイヤーの情報の取得

#endif
