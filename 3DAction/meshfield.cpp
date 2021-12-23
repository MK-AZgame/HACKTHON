//========================================================
//
//					���b�V���t�B�[���h
//					AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "meshfield.h"
#include "input.h"

//�}�N����`
#define MESHFIELD_X_BLOCK		(4)														//X�����̃u���b�N��
#define MESHFIELD_Z_BLOCK	    (4)														//Y�����̃u���b�N��
#define MESHFIELD_VEREX_NUM		((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))		//���_��
#define MESHFIELD_INDEX_NUM		((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * ((MESHFIELD_X_BLOCK * MESHFIELD_X_BLOCK) - 2))
																						//�C���f�b�N�X��
#define MESHFIELD_PRIMITIVE_NUM (MESHFIELD_X_BLOCK * MESHFIELD_Z_BLOCK * 2 + (MESHFIELD_Z_BLOCK - 1) * ((MESHFIELD_X_BLOCK * MESHFIELD_X_BLOCK) - 2))
																						//�v���~�e�B�u��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;										//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;											//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;										//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshfield;																//�ʒu
D3DXVECTOR3 g_rotMeshfield;																//����
D3DXMATRIX  g_mtxWorldMeshfield;														//���[���h�}�g���b�N�X
int g_nDebugFlug;																		//��ʂ̕\���ݒ�̕ύX�p�iF1/F2�Ő؂�ւ��j
int g_nCntVtxNum;																		//pVtx�̃J�E���g�p

//========================================================
//				���b�V���t�B�[���h����������
//========================================================
void InitMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/field003.jpg", &g_pTextureMeshfield);

	//�O���[�o���ϐ��̏�����
	g_nDebugFlug = 0;
	g_nCntVtxNum = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VEREX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshfield, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX_NUM, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshfield, NULL);

	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̊e���̐ݒ�
	for (int nCntVtx = 0; nCntVtx < MESHFIELD_Z_BLOCK + 1; nCntVtx++)
	{
		for (int nCntVtxX = 0; nCntVtxX < MESHFIELD_X_BLOCK + 1; nCntVtxX++)
		{
			//���_�ʒu�̐ݒ�
			pVtx[g_nCntVtxNum].pos = D3DXVECTOR3(-((MESHFIELD_SIZE * MESHFIELD_X_BLOCK) / 2) + (MESHFIELD_SIZE * nCntVtxX), 0.0f, ((MESHFIELD_SIZE * MESHFIELD_Z_BLOCK) / 2) + (-MESHFIELD_SIZE * nCntVtx));

			//���_�J���[�̐ݒ�
			pVtx[g_nCntVtxNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e���_�̖@���̐ݒ�
			pVtx[g_nCntVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[g_nCntVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntVtxX), 0.0f + (1.0f * nCntVtx));

			g_nCntVtxNum++;																//pVtx��������ɐi�߂�
		}
	}
	
	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	//���_�C���f�b�N�X�̐ݒ�
	for (int nCntIdxZ = 0; nCntIdxZ < MESHFIELD_Z_BLOCK; nCntIdxZ++)
	{
		for (int nCntIdxX =0; nCntIdxX < MESHFIELD_X_BLOCK + 1; nCntIdxX++)
		{
			pIdx[0] = nCntIdxX + (nCntIdxZ * (MESHFIELD_X_BLOCK + 1)) + (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = nCntIdxX + (nCntIdxZ * (MESHFIELD_X_BLOCK + 1));

			pIdx += 2;																	//pIdx�������炷
		}

		//�k�ރ|���S���̐ݒ�
		if (nCntIdxZ < (MESHFIELD_Z_BLOCK - 1))
		{
			pIdx[0] = pIdx[-1];															//�ЂƂO�̃f�[�^�̒��g������
			pIdx[1] = ((MESHFIELD_X_BLOCK + 1) * (nCntIdxZ + MESHFIELD_X_BLOCK));

			pIdx += 2;																	//pIdx�������炷
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshfield->Unlock();
	
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshfield->Unlock();
}

//========================================================
//				���b�V���t�B�[���h�I������
//========================================================
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@���
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//========================================================
//				���b�V���t�B�[���h�X�V����
//========================================================
void UpdataMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//��ʕ\���̐ݒ�̕ύX
	if (GetKeyboardTrigger(DIK_F1))
	{//F1�L�[�����Ő؂�ւ�
		if (g_nDebugFlug == 0)
		{
			g_nDebugFlug = 1;
		}
		else if (g_nDebugFlug == 1)
		{
			g_nDebugFlug = 0;
		}
	}

	if (g_nDebugFlug == 1)
	{//���C���[�t���[���\��
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else if (g_nDebugFlug == 0)
	{//�ʏ�̕\��
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//========================================================
//				���b�V���t�B�[���h�`�揈��
//========================================================
void DrawMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshfield);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//�v���~�e�B�u�̎��
		0,																				//�`�悷��ŏ��̃C���f�b�N�X
		0,																				//�C���f�b�N�X�ŏ��l
		MESHFIELD_VEREX_NUM,															//���_�̐�
		0,																				//�C���f�b�N�X�̍ŏ��̐�
		MESHFIELD_INDEX_NUM);															//�v���~�e�B�u(�|���S��)��

	pDevice->SetTexture(0, NULL);
}