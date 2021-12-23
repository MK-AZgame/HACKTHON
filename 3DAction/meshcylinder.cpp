//========================================================
//
//					���b�V��(�~��)
//					AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "meshcylinder.h"
#include "input.h"

//�}�N����`
#define MESHCYLINDER_X_BLOCK		(30)															//X�����̃u���b�N��
#define MESHCYLINDER_Z_BLOCK	    (10)															//Z�����̃u���b�N��
#define MESHCYLINDER_VEREX_NUM		((MESHCYLINDER_X_BLOCK + 1) * (MESHCYLINDER_Z_BLOCK + 1))		//���_��
#define MESHCYLINDER_INDEX_NUM		((MESHCYLINDER_X_BLOCK + 1) * 2 * MESHCYLINDER_Z_BLOCK + (MESHCYLINDER_Z_BLOCK - 1) * ((MESHCYLINDER_X_BLOCK * MESHCYLINDER_X_BLOCK) - 2))
																									//�C���f�b�N�X��
#define MESHCYLINDER_PRIMITIVE_NUM (MESHCYLINDER_X_BLOCK * MESHCYLINDER_Z_BLOCK * 2 + (MESHCYLINDER_Z_BLOCK - 1) * ((MESHCYLINDER_X_BLOCK * MESHCYLINDER_X_BLOCK) - 2))
																									//�v���~�e�B�u��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;												//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;													//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;												//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshCylinder;																		//�ʒu
D3DXVECTOR3 g_rotMeshCylinder;																		//����
D3DXMATRIX  g_mtxWorldMeshCylinder;																	//���[���h�}�g���b�N�X

//========================================================
//				���b�V���t�B�[���h����������
//========================================================
void InitMeshCylinder(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Cylinder003.jpg", &g_pTextureMeshCylinder);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHCYLINDER_VEREX_NUM, 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̊e���̐ݒ�
	for (int nCntVtx = 0; nCntVtx < MESHCYLINDER_Z_BLOCK + 1; nCntVtx++)
	{
		for (int nCntVtxX = 0; nCntVtxX < MESHCYLINDER_X_BLOCK + 1; nCntVtxX++)
		{
			float rot = ((D3DX_PI * 2.0f) / MESHCYLINDER_X_BLOCK) * nCntVtxX;

			//���_�ʒu�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-cosf(rot) * 10.0f,nCntVtx * 100.0f, sinf(rot) * 10.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e���_�̖@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(pVtx[0].pos.x, 0.0f,pVtx[0].pos.z);

			//���K��
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntVtxX), 0.0f + (1.0f * nCntVtx));

			pVtx++;
		}
	}

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//���_�C���f�b�N�X�̐ݒ�
	for (int nCntIdxZ = 0; nCntIdxZ < MESHCYLINDER_Z_BLOCK; nCntIdxZ++)
	{
		for (int nCntIdxX = 0; nCntIdxX < MESHCYLINDER_X_BLOCK + 1; nCntIdxX++)
		{
			pIdx[0] = nCntIdxX + (nCntIdxZ * (MESHCYLINDER_X_BLOCK + 1)) + (MESHCYLINDER_X_BLOCK + 1);
			pIdx[1] = nCntIdxX + (nCntIdxZ * (MESHCYLINDER_X_BLOCK + 1));

			pIdx += 2;																				//pIdx�������炷
		}

		//�k�ރ|���S���̐ݒ�
		if (nCntIdxZ < (MESHCYLINDER_Z_BLOCK - 1))
		{
			pIdx[0] = pIdx[-1];																		//�ЂƂO�̃f�[�^�̒��g������
			pIdx[1] = ((MESHCYLINDER_X_BLOCK + 1) * (nCntIdxZ + MESHCYLINDER_X_BLOCK));

			pIdx += 2;																				//pIdx�������炷
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshCylinder->Unlock();
}

//========================================================
//				���b�V���t�B�[���h�I������
//========================================================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@���
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//========================================================
//				���b�V���t�B�[���h�X�V����
//========================================================
void UpdataMeshCylinder(void)
{

}

//========================================================
//				���b�V���t�B�[���h�`�揈��
//========================================================
void DrawMeshCylinder(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//�v���~�e�B�u�̎��
		0,																				//�`�悷��ŏ��̃C���f�b�N�X
		0,																				//�C���f�b�N�X�ŏ��l
		MESHCYLINDER_VEREX_NUM,															//���_�̐�
		0,																				//�C���f�b�N�X�̍ŏ��̐�
		MESHCYLINDER_INDEX_NUM);														//�v���~�e�B�u(�|���S��)��

	pDevice->SetTexture(0, NULL);
}