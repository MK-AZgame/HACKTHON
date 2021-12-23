//========================================================
//
//						�r���{�[�h
//					AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "billboard.h"

//�}�N����`
#define BILLBOARD_SIZE (10)												//�r���{�[�h�̃T�C�Y
#define MAX_BILLBOARD (1)												//�r���{�[�h�̍ő吔

//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;													//�ʒu
	D3DXVECTOR3 rot;													//����
	D3DXMATRIX  mtxWorld;												//���[���h�}�g���b�N�X
} Billboard;

//�O���[�o���ϐ�	
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;						//�r���{�[�h�̒��_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;							//�r���{�[�h�̃e�N�X�`���̃|�C���^
Billboard g_aBillboard[MAX_BILLBOARD];									//�r���{�[�h�̏����i�[

//========================================================
//					�r���{�[�h����������
//========================================================
void InitBillboard(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/bullet000.png", &g_pTextureBillboard);

	//�r���{�[�h�̏��̏�����
	for (int nCntBill = 0; nCntBill < MAX_BILLBOARD; nCntBill++)
	{
		g_aBillboard[nCntBill].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);	//�ʒu�̏�����
		g_aBillboard[nCntBill].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL);

	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBill = 0; nCntBill < MAX_BILLBOARD; nCntBill++)
	{
		//�e���_�ʒu�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE, BILLBOARD_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE, BILLBOARD_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE, -BILLBOARD_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE, -BILLBOARD_SIZE, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//�e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

//========================================================
//					�r���{�[�h�I������
//========================================================
void UninitBillboard(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//========================================================
//					�r���{�[�h�X�V����
//========================================================
void UpdataBillboard(void)
{

}

//========================================================
//					�r���{�[�h�`�揈��
//========================================================
void DrawBillboard(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�o�b�t�@�@�̗L����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for (int nCntBill = 0; nCntBill < MAX_BILLBOARD; nCntBill++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBillboard[nCntBill].mtxWorld);

		D3DXMATRIX mtxView;
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�J�����̋t�s���ݒ�
		g_aBillboard[nCntBill].mtxWorld._11 = mtxView._11;
		g_aBillboard[nCntBill].mtxWorld._12 = mtxView._21;
		g_aBillboard[nCntBill].mtxWorld._13 = mtxView._31;
		g_aBillboard[nCntBill].mtxWorld._21 = mtxView._12;
		g_aBillboard[nCntBill].mtxWorld._22 = mtxView._22;
		g_aBillboard[nCntBill].mtxWorld._23 = mtxView._32;
		g_aBillboard[nCntBill].mtxWorld._31 = mtxView._13;
		g_aBillboard[nCntBill].mtxWorld._32 = mtxView._23;
		g_aBillboard[nCntBill].mtxWorld._33 = mtxView._33;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBill].pos.x, g_aBillboard[nCntBill].pos.y, g_aBillboard[nCntBill].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBill].mtxWorld, &g_aBillboard[nCntBill].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBill].mtxWorld);

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBillboard);

		//���e�X�g��L��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//�r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//���e�X�g�𖳌��ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	}

	//Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�@��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//�J������L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}