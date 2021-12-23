//========================================================
//
//						弾
//				AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "bullet.h"
#include "input.h"
#include "effect.h"
#include "meshfield.h"

//マクロ定義
#define MAX_BULLET  (128)										//弾の最大数
#define BULLET_SIZE (5.0f)										//弾のサイズ
#define BULLET_LIFE (50)										//弾の寿命

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;											//位置
	D3DXVECTOR3 move;											//移動量
	D3DXMATRIX  mtxWorld;										//ワールドマトリックス
	int nLife;													//寿命
	bool bUse;													//使用しているかどうか
}Bullet;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturebullet = NULL;						//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbullet = NULL;				//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];									//弾の情報

//==================================================
//					弾の初期化処理
//==================================================
void Initbullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/bullet000.png", &g_pTexturebullet);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = BULLET_LIFE;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffbullet, NULL);

	VERTEX_3D *pVtx = NULL;										//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	
	//頂点座標をアンロック
	g_pVtxBuffbullet->Unlock();
}

//==================================================
//					弾の終了処理
//==================================================
void Uninitbullet(void)
{
	//テクスチャの破棄
	if (g_pTexturebullet != NULL)
	{
		g_pTexturebullet->Release();
		g_pTexturebullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffbullet != NULL)
	{
		g_pVtxBuffbullet->Release();
		g_pVtxBuffbullet = NULL;
	}


}

//==================================================
//					弾の更新処理
//==================================================
void Updatabullet(void)
{
	int nCntBullet;

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			g_aBullet[nCntBullet].nLife--;

			//ライフがなくなったらbUseをfalseに
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			//壁にぶつかったら弾のbUseをfalseに
			if (g_aBullet[nCntBullet].pos.x - 10.0f <= -MESHFIELD_SIZE * 2 ||
				g_aBullet[nCntBullet].pos.x + 10.0f >= MESHFIELD_SIZE * 2 ||
				g_aBullet[nCntBullet].pos.z - 10.0f <= -MESHFIELD_SIZE * 2 ||
				g_aBullet[nCntBullet].pos.z + 10.0f >= MESHFIELD_SIZE * 2)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			//エフェクトを呼び出す
			SetEffect(g_aBullet[nCntBullet].pos);
		}

		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffbullet->Unlock();
}

//==================================================
//				弾の描画処理
//==================================================
void Drawbullet(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zバッファ法の有効化
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffbullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturebullet);

			//αテストを有効
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//ビルボードの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);

			//αテストを無効に戻す
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}

	//Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファ法を有効に戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//カメラを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}

//==================================================
//					弾の設定処理
//==================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	VERTEX_3D *pVtx;
	int nCntBullet;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;					//位置
			g_aBullet[nCntBullet].move = move * 10.0f;			//移動量
			g_aBullet[nCntBullet].nLife = BULLET_LIFE;			//弾の寿命

			g_aBullet[nCntBullet].bUse = true;					//bUseをtrueに
			break;
		}
		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffbullet->Unlock();
}