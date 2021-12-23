//========================================================
//
//					�v���C���[
//					AUTHOR:�z�{���V
//
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 posOld;					//�O��̈ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 rotDest;				//�ړI�̌���
} Player;

//���f���\����
typedef struct
{
	LPD3DXMESH pMesh;					//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;				//���_�o�b�t�@�ւ̃|�C���^
	DWORD nNumMat;						
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;					//�p�[�c�̈ʒu
	D3DXVECTOR3 rot;					//�p�[�c�̌���
	int ParentIdx;						//�e�̔ԍ�
}ModelParts;


//�v���g�^�C�v�錾
void InitPlayer(void);					//�v���C���[�̏���������
void UninitPlayer(void);				//�v���C���[�̏I������
void UpdataPlayer(void);				//�v���C���[�̍X�V����
void DrawPlayer(void);					//�v���C���[�̕`�揈��
void CollisionObject(void);				//�I�u�W�F�N�g�i���f���j�Ƃ̓����蔻��
Player *GetPlayer(void);				//�v���C���[�̏��̎擾

#endif
