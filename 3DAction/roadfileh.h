//===============================================================
//
//				�t�@�C���ǂݍ��ݗp�t�@�C��
//					AUTHOR:�z�{���V
//
//===============================================================
#ifndef _ROADFILE_H_
#define _ROADFILE_H_

#include "main.h"

//�t�@�C���ǂݍ��݂̍\����
typedef struct
{
	char roadName;
	int  nMaxRoad;
} ROADFILE;

//�ǂݍ��ޏ��̎��
typedef enum
{
	ROADTYPE_PLAYER = 0,
	ROADTYPE_MAX
} ROADTYPE;

//�v���g�^�C�v�錾
void RoadFile(char *pfilename,ROADTYPE roadTypeNum,int nRoadFileNum);	//�t�@�C���ǂݍ��ݗl�֐�

#endif