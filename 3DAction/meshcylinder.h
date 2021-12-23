//========================================================
//
//					メッシュ(円柱)
//					AUTHOR:越本愛彪
//
//========================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//マクロ定義
#define MESHCYLINDER_SIZE (100.0f)			//メッシュのサイズ

//プロトタイプ宣言
void InitMeshCylinder(void);				//ポリゴン初期化処理
void UninitMeshCylinder(void);				//ポリゴン終了処理
void UpdataMeshCylinder(void);				//ポリゴン更新処理
void DrawMeshCylinder(void);				//ポリゴン描画処理

#endif 
