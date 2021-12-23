//========================================================
//
//					�G�t�F�N�g
//					AUTHOR:�z�{���V
//
//========================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�G�t�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 rot;										//����
	float fRadius;											//���a
	D3DXCOLOR	col;										//�F
	D3DXMATRIX mtxWorld;									//���[���h�}�g���b�N�X
	int nLife;												//�G�t�F�N�g�̎���
	bool bUse;												//�g���Ă��邩�ǂ���
} Effect;

//�v���g�^�C�v�錾
void InitEffect(void);										//�G�t�F�N�g����������
void UninitEffect(void);									//�G�t�F�N�g�I������
void UpdataEffect(void);									//�G�t�F�N�g�X�V����
void DrawEffect(void);										//�G�t�F�N�g�`�揈��
void SetEffect(D3DXVECTOR3 pos);							//�G�t�F�N�g�̐ݒ菈��

#endif 