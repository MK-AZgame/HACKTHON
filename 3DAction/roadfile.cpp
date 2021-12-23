//================================================================
//
//					ファイル読み込み
//					AUTHOR:越本愛彪
//
//================================================================
#include <stdio.h>
#include "roadfileh.h"
#include "player.h"

//マクロ定義
ROADFILE g_roadFile;
//================================================================
//				ファイル読み込み関数
//================================================================
void RoadFile(char *pfilename,int nRoadFileNum)
{
	FILE *fp;											//ファイルポインタ
	Player *pPlayer = GetPlayer();						//プレイヤー情報の取得

	//ファイルを開く
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//成功
		//文字列の読み込み
		fscanf(fp, "%s", &g_roadFile.roadName);

		if (strcmp(&g_roadFile.roadName, "NUM_MODEL"))
		{//読み込んだ文字列が"NUM_MODEL"だった時
			fscanf(fp, "%d", &g_roadFile.nMaxRoad);
			for(int nCntRoad = 0;nCntRoad < g_roadFile.nMaxRoad;nCntRoad++)
			{
				//fscanf(fp, "%s", );
			}
		}

		//ファイルを閉じる
		fclose(fp);
	}
	else
	{//失敗
	}
}