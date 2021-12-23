//========================================================
//
//						�J����
//					AUTHOR:�z�{���V
//
//========================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//�O���[�o���ϐ�
int g_nCntTime;								//�v���C���[�������Ă��Ȃ����ԁi�ҋ@���ԁj�̉��Z�p
Camera g_camera;							//�J�������

//========================================================
//					�J��������������
//========================================================
void InitCamera(void)
{
	//���_�E�����_�E�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f,100.0f,-100.0f);
	g_camera.posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z) + 
		(g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x));
}

//========================================================
//					�J�����I������
//========================================================
void UninitCamera(void)
{

}

//========================================================
//					�J�����X�V����
//========================================================
void UpdataCamera(void)
{
	Player *pPlayer = GetPlayer();

	//if(GetKeyboardTrigger(DIK_F2))
	{
		//�J�����̒Ǐ]����
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

	//���_�̉�]
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

	//�����_�̉�]
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

	//�J�����̈ړ�
	if (GetKeyboardPress(DIK_W) == true)
	{//�O
		g_camera.posV.x += sinf(g_camera.rot.y) * 1.5f;
		g_camera.posV.z += cosf(g_camera.rot.y) * 1.5f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//��
		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.5f;
		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.5f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//��
		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * -0.5f)) * 1.5f;
		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * -0.5f)) * 1.5f;
	
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//�E
		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.5f;
		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * 1.5f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//�J������]�̐��K��
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
//					�J�����ݒ菈��
//========================================================
void SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);
		
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(60.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//========================================================
//				�J���������擾
//========================================================
Camera *GetCamera(void)
{
	return &g_camera;
}
