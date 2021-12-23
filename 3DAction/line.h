//========================================================
//
//					�f�o�b�O���C��
//					AUTHOR:�z�{���V
//
//========================================================
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//���C���\����
typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 rot;										//����
	bool bUse;												//�g�p���Ă��邩�ǂ���
	D3DXMATRIX mtxWorld;									//���[���h�}�g���b�N�X
} Line;

void InitLine(void);										//���C���̏���������
void UninitLine(void);										//���C���̏I������
void UpdataLine(void);										//���C���̍X�V����
void DrawLine(void);										//���C���̕`�揈��
void SetLine(D3DXVECTOR3 pos,D3DXVECTOR3 rot,
				D3DXVECTOR3 startPos,D3DXVECTOR3 endPos);	//���C���̐ݒ菈��

#endif
