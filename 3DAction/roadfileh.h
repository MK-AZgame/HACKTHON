//===============================================================
//
//				ファイル読み込み用ファイル
//					AUTHOR:越本愛彪
//
//===============================================================
#ifndef _ROADFILE_H_
#define _ROADFILE_H_

#include "main.h"

//ファイル読み込みの構造体
typedef struct
{
	char roadName;
	int  nMaxRoad;
} ROADFILE;

//読み込む情報の種類
typedef enum
{
	ROADTYPE_PLAYER = 0,
	ROADTYPE_MAX
} ROADTYPE;

//プロトタイプ宣言
void RoadFile(char *pfilename,ROADTYPE roadTypeNum,int nRoadFileNum);	//ファイル読み込み様関数

#endif