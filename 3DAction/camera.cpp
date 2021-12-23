//========================================================
//
//						カメラ
//					AUTHOR:越本愛彪
//
//========================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//グローバル変数
int g_nCntTime;								//プレイヤーが動いていない時間（待機時間）の加算用
Camera g_camera;							//カメラ情報

//========================================================
//					カメラ初期化処理
//========================================================
void InitCamera(void)
{
	//視点・注視点・上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f,100.0f,-100.0f);
	g_camera.posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z) + 
		(g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x));
}

//========================================================
//					カメラ終了処理
//========================================================
void UninitCamera(void)
{

}

//========================================================
//					カメラ更新処理
//========================================================
void UpdataCamera(void)
{
	Player *pPlayer = GetPlayer();

	//if(GetKeyboardTrigger(DIK_F2))
	{
		//カメラの追従処理
		g_camera.posRDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * 10.0f;
		g_camera.posRDest.y = pPlayer->pos.y;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * 10.0f;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 1.0f;
		g_camera.posVDest.y = pPlayer->pos.y;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 1.0f;

		g_camera.posR += (g_camera.posRDest - g_camera.posR) * 0.1f;
		g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.1f;
		g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * 0.1f;
	}

	//視点の回転
	if (GetKeyboardPress(DIK_R) == true)
	{
		g_camera.rot.y -= 0.05f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_F) == true)
	{
		g_camera.rot.y += 0.05f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//注視点の回転
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.y -= 0.05f;
		/*g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;*/
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.y += 0.05f;
	/*	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;*/
	}

	//カメラの移動
	if (GetKeyboardPress(DIK_W) == true)
	{//前
		g_camera.posV.x += sinf(g_camera.rot.y) * 1.5f;
		g_camera.posV.z += cosf(g_camera.rot.y) * 1.5f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//後
		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.5f;
		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.5f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//左
		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * -0.5f)) * 1.5f;
		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * -0.5f)) * 1.5f;
	
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//右
		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.5f;
		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.5f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//カメラ回転の正規化
	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}

	if (g_camera.rotDest.y - g_camera.rot.y > D3DX_PI)
	{
		g_camera.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rotDest.y - g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rotDest.y += D3DX_PI * 2.0f;
	}

}

//========================================================
//					カメラ設定処理
//========================================================
void SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);
		
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(60.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//========================================================
//				カメラ情報を取得
//========================================================
Camera *GetCamera(void)
{
	return &g_camera;
}
