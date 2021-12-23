//========================================================
//
//					�f�o�b�O���C��
//					AUTHOR:�z�{���V
//
//========================================================
#include "line.h"
#include "model.h"

//�}�N����`
#define MAX_LINE (12 * MAX_MODEL)				//���C���̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;	//���C���̒��_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureLine = NULL;		//���C���̃e�N�X�`���ւ̃|�C���^
Line g_aLine[MAX_LINE];							//���C���̏��̊i�[

//========================================================
//					���C������������
//========================================================
void InitLine(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		//���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 2;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffLine->Unlock();
}

//========================================================
//					���C���I������
//========================================================
void UninitLine(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureLine != NULL)
	{
		g_pTextureLine->Release();
		g_pTextureLine = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//========================================================
//					���C���X�V����
//========================================================
void UpdataLine(void)
{

}

//========================================================
//					���C���`�揈��
//========================================================
void DrawLine(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLine);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLine[nCntLine].rot.y, g_aLine[nCntLine].rot.x, g_aLine[nCntLine].rot.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���C���̕`��
			pDevice->DrawPrimitive(D3DPT_LINELIST, 2 * nCntLine, 1);
		}
	}

	//�J������L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}

//========================================================
//					���C���̐ݒ菈��
//========================================================
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == false)
		{
			g_aLine[nCntLine].pos = pos;		//�\���̂�pos���Ɉ�������
			g_aLine[nCntLine].rot = rot;		//�\���̂�rot���Ɉ�������

			//���_���W�̐ݒ�
			pVtx[0].pos = startPos;				//���C���̎n�_
			pVtx[1].pos = endPos;				//���C���̏I�_

			g_aLine[nCntLine].bUse = true;		//���C����bUse��true��
			break;
		}
		pVtx += 2;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffLine->Unlock();
}