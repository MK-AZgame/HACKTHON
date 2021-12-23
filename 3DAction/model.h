//========================================================
//
//						���f��
//					AUTHOR:�z�{���V
//
//========================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//�}�N����`
#define MAX_MODEL (1)				//���f���̍ő吔

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;				//���f���̈ʒu
	D3DXVECTOR3 rot;				//���f���̊p�x
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin, vtxMax;		//���f���̒��_�̍ő�l�E�ŏ��l
}MODEL;

//�v���g�^�C�v�錾
void InitModel(void);				//���f������������
void UninitModel(void);				//���f���I������
void UpdataModel(void);				//���f���X�V����
void DrawModel(void);				//���f���`�揈��
MODEL *GetModel(void);				//���f���̏����擾���鏈��

#endif