//========================================================
//
//					メッシュ(円柱)
//					AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "sphere.h"
#include "input.h"

//マクロ定義
#define SPHERE_X_BLOCK		(30)														//X方向のブロック数
#define SPHERE_Y_BLOCK		(30)														//Y方向の分割数
#define SPHERE_Z_BLOCK	    (10)														//Z方向のブロック数
#define SPHERE_VEREX_NUM	((SPHERE_X_BLOCK + 1) * (SPHERE_Y_BLOCK + 1))				//頂点数
#define SPHERE_INDEX_NUM	((SPHERE_X_BLOCK + 1) * 2 * SPHERE_Y_BLOCK + (SPHERE_Y_BLOCK - 1) * ((SPHERE_X_BLOCK * SPHERE_X_BLOCK) - 2))
																						//インデックス数
#define SPHERE_PRIMITIVE_NUM (SPHERE_X_BLOCK * SPHERE_Z_BLOCK * 2 + (SPHERE_Z_BLOCK - 1) * ((SPHERE_X_BLOCK * SPHERE_X_BLOCK) - 2))
																						//プリミティブ数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;										//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSphere = NULL;												//球のテクスチャ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;											//インデックスバッファへのポインタ
D3DXVECTOR3 g_posSphere;																//位置
D3DXVECTOR3 g_rotSphere;																//向き
D3DXMATRIX  g_mtxWorldSphere;															//ワールドマトリックス

//========================================================
//				球初期化処理
//========================================================
void InitSphere(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Cylinder003.jpg", &g_pTextureSphere);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPHERE_VEREX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * SPHERE_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphere,
		NULL);

	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の各情報の設定
	for (int nCntVtx = 0; nCntVtx <= SPHERE_Y_BLOCK; nCntVtx++)
	{
		for (int nCntVtxX = 0; nCntVtxX < SPHERE_X_BLOCK + 1; nCntVtxX++)
		{
			float rot = ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK) * nCntVtxX;					//X・Z座標の設定で使う
			float rotz = (D3DX_PI / SPHERE_Y_BLOCK) * nCntVtx;							//半径
			
			//頂点位置の設定
			pVtx[0].pos = D3DXVECTOR3(-cosf(rot) * cosf(rotz) * SPHERE_SIZE, sinf(rotz) * SPHERE_SIZE + 50.0f, sinf(rot) * cosf(rotz) * SPHERE_SIZE);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//各頂点の法線の設定
			pVtx[0].nor = D3DXVECTOR3(pVtx[0].pos.x, pVtx[0].pos.y, pVtx[0].pos.z);

			//正規化
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntVtxX), 0.0f + (1.0f * nCntVtx));

			pVtx++;
		}
	}

	//インデックスバッファをロック
	WORD *pIdx;
	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	//頂点インデックスの設定
	for (int nCntIdxZ = 0; nCntIdxZ < SPHERE_Y_BLOCK; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < SPHERE_X_BLOCK + 1; nCntIdxX++)
		{
			pIdx[0] = nCntIdxX + (nCntIdxZ * (SPHERE_X_BLOCK + 1)) + (SPHERE_X_BLOCK + 1);
			pIdx[1] = nCntIdxX + (nCntIdxZ * (SPHERE_X_BLOCK + 1));

			pIdx += 2;																	//pIdxを二個分ずらす
		}

		//縮退ポリゴンの設定
		if (nCntIdxZ < (SPHERE_Y_BLOCK - 1))
		{
			pIdx[0] = pIdx[-1];															//ひとつ前のデータの中身を入れる
			pIdx[1] = ((SPHERE_X_BLOCK + 1) * (nCntIdxZ + SPHERE_X_BLOCK));

			pIdx += 2;																	//pIdxを二個分ずらす
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffSphere->Unlock();

	//頂点バッファのアンロック
	g_pVtxBuffSphere->Unlock();
}

//========================================================
//				球終了処理
//========================================================
void UninitSphere(void)
{
	//テクスチャの破棄
	if (g_pTextureSphere != NULL)
	{
		g_pTextureSphere->Release();
		g_pTextureSphere = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffSphere != NULL)
	{
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}

	//インデックスバッファ解放
	if (g_pIdxBuffSphere != NULL)
	{
		g_pIdxBuffSphere->Release();
		g_pIdxBuffSphere = NULL;
	}
}

//========================================================
//				球更新処理
//========================================================
void UpdataSphere(void)
{

}

//========================================================
//				球描画処理
//========================================================
void DrawSphere(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldSphere);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotSphere.y, g_rotSphere.x, g_rotSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posSphere.x, g_posSphere.y, g_posSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSphere);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffSphere);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSphere);

	//球の描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//プリミティブの種類
		0,																				//描画する最初のインデックス
		0,																				//インデックス最小値
		SPHERE_VEREX_NUM,																//頂点の数
		0,																				//インデックスの最初の数
		SPHERE_INDEX_NUM);																//プリミティブ(ポリゴン)数

	pDevice->SetTexture(0, NULL);
}