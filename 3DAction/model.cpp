//========================================================
//
//						モデル
//					AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "line.h"

//グローバル変数
LPD3DXMESH g_pMeshModel = NULL;	
LPD3DXBUFFER g_pBuffMatModel = NULL;
DWORD g_nNumMatModel = 0;
MODEL g_model;													//モデルの構造体情報を格納

//========================================================
//					モデル初期化処理
//========================================================
void InitModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/Head000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	//位置・向きの初期化
	g_model.pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);				//位置の初期化
	g_model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期化
	g_model.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//頂点の最大値の初期化
	g_model.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);	//頂点の最小値の初期化

	int nNumVtx;												//モデルの頂点数の保存用
	DWORD sizeFVF;												//頂点フォーマットのサイズ
	BYTE *pVtxBuff;												//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//頂点バッファのロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		////頂点座標を比較してモデルの最大・最小値を取得
		//最小値
		if (vtx.x <= g_model.vtxMin.x)
		{
			g_model.vtxMin.x = vtx.x;
		}

		if (vtx.y <= g_model.vtxMin.y)
		{
			g_model.vtxMin.y = vtx.y;
		}

		if (vtx.z <= g_model.vtxMin.z)
		{
			g_model.vtxMin.z = vtx.z;
		}

		//最大値
		if (vtx.x >= g_model.vtxMax.x)
		{
			g_model.vtxMax.x = vtx.x;
		}

		if (vtx.y >= g_model.vtxMax.y)
		{
			g_model.vtxMax.y = vtx.y;
		}

		if (vtx.z >= g_model.vtxMax.z)
		{
			g_model.vtxMax.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファをアンロック
	g_pMeshModel->UnlockVertexBuffer();
}

//========================================================
//					モデル終了処理
//========================================================
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//========================================================
//					モデル更新処理
//========================================================
void UpdataModel(void)
{
	if (GetKeyboardTrigger(DIK_F7))
	{
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z));
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z));
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z));
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z));
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMax.y, g_model.vtxMin.z));
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMax.y, g_model.vtxMin.z));
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMax.y, g_model.vtxMax.z));
		SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMax.y, g_model.vtxMax.z));
	}
}

//========================================================
//					モデル描画処理
//========================================================
void DrawModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_model.mtxWorld);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model.rot.y, g_model.rot.x, g_model.rot.z);
	D3DXMatrixMultiply(&g_model.mtxWorld, &g_model.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_model.pos.x, g_model.pos.y, g_model.pos.z);
	D3DXMatrixMultiply(&g_model.mtxWorld, &g_model.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_model.mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}

//========================================================
//				モデルの情報を取得する処理
//========================================================
MODEL *GetModel(void)
{
	return &g_model;
}
