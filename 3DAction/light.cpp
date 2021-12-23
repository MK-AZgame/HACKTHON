//========================================================
//
//						���C�g
//					AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "light.h"

//�}�N����`
#define MAX_LIGHT (3)							//���C�g�̍ő吔

//�O���[�o���ϐ�
D3DLIGHT9 g_aLight[MAX_LIGHT];					//���C�g�����i�[

//========================================================
//					���C�g����������
//========================================================
void InitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];				//���C�g�����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&g_aLight[0], sizeof(g_aLight));

	////���C�g1
	//���C�g�̎�ސݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 0.8f, 0.7f, 1.0f);

	//���C�g�̕������w��
	vecDir[0] = D3DXVECTOR3(1.57f, -0.6f, -0.9f);

	//���K������
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	g_aLight[0].Direction = vecDir[0];

	//���C�g��ݒ肷��
	pDevice->SetLight(0,&g_aLight[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	////���C�g2
	//���C�g�̎�ސݒ�
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	g_aLight[1].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

	//���C�g�̕������w��
	vecDir[1] = D3DXVECTOR3(0.6f, 1.0f, -1.57f);

	//���K������
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);
	g_aLight[1].Direction = vecDir[1];

	//���C�g��ݒ肷��
	pDevice->SetLight(1, &g_aLight[1]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);

	////���C�g3
	//���C�g�̎�ސݒ�
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	g_aLight[2].Diffuse = D3DXCOLOR(0.6f, 0.4f, 0.3f, 1.0f);

	//���C�g�̕������w��
	vecDir[2] = D3DXVECTOR3(-1.57f, -0.2f, 0.9f);

	//���K������
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);
	g_aLight[2].Direction = vecDir[2];

	//���C�g��ݒ肷��
	pDevice->SetLight(2, &g_aLight[2]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(2, TRUE);
}

//========================================================
//					���C�g�I������
//========================================================
void UninitLight()
{

}

//========================================================
//					���C�g�X�V����
//========================================================
void UpdataLight()
{

}