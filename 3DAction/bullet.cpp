//========================================================
//
//						�e
//				AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "bullet.h"
#include "input.h"
#include "effect.h"
#include "meshfield.h"

//�}�N����`
#define MAX_BULLET  (128)										//�e�̍ő吔
#define BULLET_SIZE (5.0f)										//�e�̃T�C�Y
#define BULLET_LIFE (50)										//�e�̎���

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;											//�ʒu
	D3DXVECTOR3 move;											//�ړ���
	D3DXMATRIX  mtxWorld;										//���[���h�}�g���b�N�X
	int nLife;													//����
	bool bUse;													//�g�p���Ă��邩�ǂ���
}Bullet;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturebullet = NULL;						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbullet = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];									//�e�̏��

//==================================================
//					�e�̏���������
//==================================================
void Initbullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/bullet000.png", &g_pTexturebullet);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = BULLET_LIFE;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffbullet, NULL);

	VERTEX_3D *pVtx = NULL;										//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	
	//���_���W���A�����b�N
	g_pVtxBuffbullet->Unlock();
}

//==================================================
//					�e�̏I������
//==================================================
void Uninitbullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturebullet != NULL)
	{
		g_pTexturebullet->Release();
		g_pTexturebullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffbullet != NULL)
	{
		g_pVtxBuffbullet->Release();
		g_pVtxBuffbullet = NULL;
	}


}

//==================================================
//					�e�̍X�V����
//==================================================
void Updatabullet(void)
{
	int nCntBullet;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			g_aBullet[nCntBullet].nLife--;

			//���C�t���Ȃ��Ȃ�����bUse��false��
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			//�ǂɂԂ�������e��bUse��false��
			if (g_aBullet[nCntBullet].pos.x - 10.0f <= -MESHFIELD_SIZE * 2 ||
				g_aBullet[nCntBullet].pos.x + 10.0f >= MESHFIELD_SIZE * 2 ||
				g_aBullet[nCntBullet].pos.z - 10.0f <= -MESHFIELD_SIZE * 2 ||
				g_aBullet[nCntBullet].pos.z + 10.0f >= MESHFIELD_SIZE * 2)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			//�G�t�F�N�g���Ăяo��
			SetEffect(g_aBullet[nCntBullet].pos);
		}

		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffbullet->Unlock();
}

//==================================================
//				�e�̕`�揈��
//==================================================
void Drawbullet(void)
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

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffbullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturebullet);

			//���e�X�g��L��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//�r���{�[�h�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);

			//���e�X�g�𖳌��ɖ߂�
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}

	//Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�@��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//�J������L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}

//==================================================
//					�e�̐ݒ菈��
//==================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	VERTEX_3D *pVtx;
	int nCntBullet;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;					//�ʒu
			g_aBullet[nCntBullet].move = move * 10.0f;			//�ړ���
			g_aBullet[nCntBullet].nLife = BULLET_LIFE;			//�e�̎���

			g_aBullet[nCntBullet].bUse = true;					//bUse��true��
			break;
		}
		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffbullet->Unlock();
}