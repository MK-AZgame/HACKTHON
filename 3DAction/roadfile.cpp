//================================================================
//
//					�t�@�C���ǂݍ���
//					AUTHOR:�z�{���V
//
//================================================================
#include <stdio.h>
#include "roadfileh.h"
#include "player.h"

//�}�N����`
ROADFILE g_roadFile;
//================================================================
//				�t�@�C���ǂݍ��݊֐�
//================================================================
void RoadFile(char *pfilename,int nRoadFileNum)
{
	FILE *fp;											//�t�@�C���|�C���^
	Player *pPlayer = GetPlayer();						//�v���C���[���̎擾

	//�t�@�C�����J��
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//����
		//������̓ǂݍ���
		fscanf(fp, "%s", &g_roadFile.roadName);

		if (strcmp(&g_roadFile.roadName, "NUM_MODEL"))
		{//�ǂݍ��񂾕�����"NUM_MODEL"��������
			fscanf(fp, "%d", &g_roadFile.nMaxRoad);
			for(int nCntRoad = 0;nCntRoad < g_roadFile.nMaxRoad;nCntRoad++)
			{
				//fscanf(fp, "%s", );
			}
		}

		//�t�@�C�������
		fclose(fp);
	}
	else
	{//���s
	}
}