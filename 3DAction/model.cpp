//========================================================
//
//						���f��
//					AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "line.h"

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshModel = NULL;	
LPD3DXBUFFER g_pBuffMatModel = NULL;
DWORD g_nNumMatModel = 0;
MODEL g_model;													//���f���̍\���̏����i�[

//========================================================
//					���f������������
//========================================================
void InitModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/Head000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	//�ʒu�E�����̏�����
	g_model.pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);				//�ʒu�̏�����
	g_model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏�����
	g_model.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_�̍ő�l�̏�����
	g_model.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);	//���_�̍ŏ��l�̏�����

	int nNumVtx;												//���f���̒��_���̕ۑ��p
	DWORD sizeFVF;												//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;												//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		////���_���W���r���ă��f���̍ő�E�ŏ��l���擾
		//�ŏ��l
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

		//�ő�l
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

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();
}

//========================================================
//					���f���I������
//========================================================
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//========================================================
//					���f���X�V����
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
//					���f���`�揈��
//========================================================
void DrawModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_model.mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model.rot.y, g_model.rot.x, g_model.rot.z);
	D3DXMatrixMultiply(&g_model.mtxWorld, &g_model.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_model.pos.x, g_model.pos.y, g_model.pos.z);
	D3DXMatrixMultiply(&g_model.mtxWorld, &g_model.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_model.mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}

//========================================================
//				���f���̏����擾���鏈��
//========================================================
MODEL *GetModel(void)
{
	return &g_model;
}
