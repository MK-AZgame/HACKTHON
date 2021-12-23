//========================================================
//
//						�J����
//					AUTHOR:�z�{���V
//
//========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�J�����\����
typedef struct
{
	D3DXVECTOR3 posV;				//���_�̈ʒu
	D3DXVECTOR3 posR;				//�����_�̈ʒu
	D3DXVECTOR3 posVDest;			//���_�̖ړI�̈ʒu
	D3DXVECTOR3 posRDest;			//�����_�̖ړI�̈ʒu
	D3DXVECTOR3 vecU;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXMATRIX  mtxProjection;
	D3DXMATRIX  mtxView;
	float fDistance;				//����
} Camera;

//�v���g�^�C�v�錾
void InitCamera(void);				//�J��������������
void UninitCamera(void);			//�J�����I������
void UpdataCamera(void);			//�J�����X�V����
void SetCamera(void);				//�J�����ݒ菈��
Camera *GetCamera(void);

#endif