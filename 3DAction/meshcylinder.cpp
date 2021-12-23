//========================================================
//
//					メッシュ(円柱)
//					AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "meshcylinder.h"
#include "input.h"

//マクロ定義
#define MESHCYLINDER_X_BLOCK		(30)															//X方向のブロック数
#define MESHCYLINDER_Z_BLOCK	    (10)															//Z方向のブロック数
#define MESHCYLINDER_VEREX_NUM		((MESHCYLINDER_X_BLOCK + 1) * (MESHCYLINDER_Z_BLOCK + 1))		//頂点数
#define MESHCYLINDER_INDEX_NUM		((MESHCYLINDER_X_BLOCK + 1) * 2 * MESHCYLINDER_Z_BLOCK + (MESHCYLINDER_Z_BLOCK - 1) * ((MESHCYLINDER_X_BLOCK * MESHCYLINDER_X_BLOCK) - 2))
																									//インデックス数
#define MESHCYLINDER_PRIMITIVE_NUM (MESHCYLINDER_X_BLOCK * MESHCYLINDER_Z_BLOCK * 2 + (MESHCYLINDER_Z_BLOCK - 1) * ((MESHCYLINDER_X_BLOCK * MESHCYLINDER_X_BLOCK) - 2))
																									//プリミティブ数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;												//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;													//メッシュフィールドのテクスチャ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;												//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshCylinder;																		//位置
D3DXVECTOR3 g_rotMeshCylinder;																		//向き
D3DXMATRIX  g_mtxWorldMeshCylinder;																	//ワールドマトリックス

//========================================================
//				メッシュフィールド初期化処理
//========================================================
void InitMeshCylinder(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Cylinder003.jpg", &g_pTextureMeshCylinder);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHCYLINDER_VEREX_NUM, 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の各情報の設定
	for (int nCntVtx = 0; nCntVtx < MESHCYLINDER_Z_BLOCK + 1; nCntVtx++)
	{
		for (int nCntVtxX = 0; nCntVtxX < MESHCYLINDER_X_BLOCK + 1; nCntVtxX++)
		{
			float rot = ((D3DX_PI * 2.0f) / MESHCYLINDER_X_BLOCK) * nCntVtxX;

			//頂点位置の設定
			pVtx[0].pos = D3DXVECTOR3(-cosf(rot) * 10.0f,nCntVtx * 100.0f, sinf(rot) * 10.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//各頂点の法線の設定
			pVtx[0].nor = D3DXVECTOR3(pVtx[0].pos.x, 0.0f,pVtx[0].pos.z);

			//正規化
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntVtxX), 0.0f + (1.0f * nCntVtx));

			pVtx++;
		}
	}

	//インデックスバッファをロック
	WORD *pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//頂点インデックスの設定
	for (int nCntIdxZ = 0; nCntIdxZ < MESHCYLINDER_Z_BLOCK; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < MESHCYLINDER_X_BLOCK + 1; nCntIdxX++)
		{
			pIdx[0] = nCntIdxX + (nCntIdxZ * (MESHCYLINDER_X_BLOCK + 1)) + (MESHCYLINDER_X_BLOCK + 1);
			pIdx[1] = nCntIdxX + (nCntIdxZ * (MESHCYLINDER_X_BLOCK + 1));

			pIdx += 2;																				//pIdxを二個分ずらす
		}

		//縮退ポリゴンの設定
		if (nCntIdxZ < (MESHCYLINDER_Z_BLOCK - 1))
		{
			pIdx[0] = pIdx[-1];																		//ひとつ前のデータの中身を入れる
			pIdx[1] = ((MESHCYLINDER_X_BLOCK + 1) * (nCntIdxZ + MESHCYLINDER_X_BLOCK));

			pIdx += 2;																				//pIdxを二個分ずらす
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshCylinder->Unlock();

	//頂点バッファのアンロック
	g_pVtxBuffMeshCylinder->Unlock();
}

//========================================================
//				メッシュフィールド終了処理
//========================================================
void UninitMeshCylinder(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//インデックスバッファ解放
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//========================================================
//				メッシュフィールド更新処理
//========================================================
void UpdataMeshCylinder(void)
{

}

//========================================================
//				メッシュフィールド描画処理
//========================================================
void DrawMeshCylinder(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//プリミティブの種類
		0,																				//描画する最初のインデックス
		0,																				//インデックス最小値
		MESHCYLINDER_VEREX_NUM,															//頂点の数
		0,																				//インデックスの最初の数
		MESHCYLINDER_INDEX_NUM);														//プリミティブ(ポリゴン)数

	pDevice->SetTexture(0, NULL);
}