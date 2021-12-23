//========================================================
//
//					���b�V��(�~��)
//					AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "sphere.h"
#include "input.h"

//�}�N����`
#define SPHERE_X_BLOCK		(30)														//X�����̃u���b�N��
#define SPHERE_Y_BLOCK		(30)														//Y�����̕�����
#define SPHERE_Z_BLOCK	    (10)														//Z�����̃u���b�N��
#define SPHERE_VEREX_NUM	((SPHERE_X_BLOCK + 1) * (SPHERE_Y_BLOCK + 1))				//���_��
#define SPHERE_INDEX_NUM	((SPHERE_X_BLOCK + 1) * 2 * SPHERE_Y_BLOCK + (SPHERE_Y_BLOCK - 1) * ((SPHERE_X_BLOCK * SPHERE_X_BLOCK) - 2))
																						//�C���f�b�N�X��
#define SPHERE_PRIMITIVE_NUM (SPHERE_X_BLOCK * SPHERE_Z_BLOCK * 2 + (SPHERE_Z_BLOCK - 1) * ((SPHERE_X_BLOCK * SPHERE_X_BLOCK) - 2))
																						//�v���~�e�B�u��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;										//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSphere = NULL;												//���̃e�N�X�`��
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;											//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posSphere;																//�ʒu
D3DXVECTOR3 g_rotSphere;																//����
D3DXMATRIX  g_mtxWorldSphere;															//���[���h�}�g���b�N�X

//========================================================
//				������������
//========================================================
void InitSphere(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Cylinder003.jpg", &g_pTextureSphere);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPHERE_VEREX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * SPHERE_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphere,
		NULL);

	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̊e���̐ݒ�
	for (int nCntVtx = 0; nCntVtx <= SPHERE_Y_BLOCK; nCntVtx++)
	{
		for (int nCntVtxX = 0; nCntVtxX < SPHERE_X_BLOCK + 1; nCntVtxX++)
		{
			float rot = ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK) * nCntVtxX;					//X�EZ���W�̐ݒ�Ŏg��
			float rotz = (D3DX_PI / SPHERE_Y_BLOCK) * nCntVtx;							//���a
			
			//���_�ʒu�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-cosf(rot) * cosf(rotz) * SPHERE_SIZE, sinf(rotz) * SPHERE_SIZE + 50.0f, sinf(rot) * cosf(rotz) * SPHERE_SIZE);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e���_�̖@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(pVtx[0].pos.x, pVtx[0].pos.y, pVtx[0].pos.z);

			//���K��
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntVtxX), 0.0f + (1.0f * nCntVtx));

			pVtx++;
		}
	}

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	//���_�C���f�b�N�X�̐ݒ�
	for (int nCntIdxZ = 0; nCntIdxZ < SPHERE_Y_BLOCK; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < SPHERE_X_BLOCK + 1; nCntIdxX++)
		{
			pIdx[0] = nCntIdxX + (nCntIdxZ * (SPHERE_X_BLOCK + 1)) + (SPHERE_X_BLOCK + 1);
			pIdx[1] = nCntIdxX + (nCntIdxZ * (SPHERE_X_BLOCK + 1));

			pIdx += 2;																	//pIdx�������炷
		}

		//�k�ރ|���S���̐ݒ�
		if (nCntIdxZ < (SPHERE_Y_BLOCK - 1))
		{
			pIdx[0] = pIdx[-1];															//�ЂƂO�̃f�[�^�̒��g������
			pIdx[1] = ((SPHERE_X_BLOCK + 1) * (nCntIdxZ + SPHERE_X_BLOCK));

			pIdx += 2;																	//pIdx�������炷
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffSphere->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSphere->Unlock();
}

//========================================================
//				���I������
//========================================================
void UninitSphere(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSphere != NULL)
	{
		g_pTextureSphere->Release();
		g_pTextureSphere = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffSphere != NULL)
	{
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}

	//�C���f�b�N�X�o�b�t�@���
	if (g_pIdxBuffSphere != NULL)
	{
		g_pIdxBuffSphere->Release();
		g_pIdxBuffSphere = NULL;
	}
}

//========================================================
//				���X�V����
//========================================================
void UpdataSphere(void)
{

}

//========================================================
//				���`�揈��
//========================================================
void DrawSphere(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldSphere);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotSphere.y, g_rotSphere.x, g_rotSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posSphere.x, g_posSphere.y, g_posSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSphere);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffSphere);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSphere);

	//���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//�v���~�e�B�u�̎��
		0,																				//�`�悷��ŏ��̃C���f�b�N�X
		0,																				//�C���f�b�N�X�ŏ��l
		SPHERE_VEREX_NUM,																//���_�̐�
		0,																				//�C���f�b�N�X�̍ŏ��̐�
		SPHERE_INDEX_NUM);																//�v���~�e�B�u(�|���S��)��

	pDevice->SetTexture(0, NULL);
}