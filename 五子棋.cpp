#include <stdio.h>
#include <stdlib.h>
  // �����㹻�������
int qipan[50][50]={0},xx,yy;

  // ����ʵ�����������
void qipan_bianli()
{
	for (xx=5;xx<=19;xx++)
	{
		for (yy=5;yy<=19;yy++)
		{
			if (qipan[xx][yy] == 0)
				printf("|%c|",'*');
			if (qipan[xx][yy] == 1)
				printf("|%c|",'o');
			if (qipan[xx][yy] == 100)
				printf("|%c|",'x');
		}
		printf("\n");
	}
}

  //  �����ͬʱ��������Ϊ���ı����˸���λ�Ƿ�����ʤ������
void qipan_shuru()
{
	int zhongzhi=1,x,y;
	qipan_bianli();
	while(zhongzhi)
	{
		printf("������x��y������ֵ\n");
		scanf("%d %d",&x,&y);
		if (x==100 && y==100)
			break;
		else if (x<1 || y<1 || y>15 || x>15)
		{
			printf("����ˣ���������\n");
			qipan_shuru();				
		}
		printf("���������ӵ�ֵ,1�ǰ��ӣ�100�Ǻ���\n");
		scanf("%d",&qipan[y+4][x+4]);
		if (qipan[y+4][x+4] != 0 && qipan[y+4][x+4] != 1 && qipan[y+4][x+4] != 100)
		{
			printf("����ˣ���������\n");
			qipan[y+4][x+4]=0;
		}
		
		// ���Ǽ����ӵ�
		if ((qipan[y+4][x+4]+qipan[y+4][x+5]+qipan[y+4][x+6]+qipan[y+4][x+7]+qipan[y+4][x+8]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+4][x+3]+qipan[y+4][x+2]+qipan[y+4][x+1]+qipan[y+4][x]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+4]+qipan[y+6][x+4]+qipan[y+7][x+4]+qipan[y+8][x+4]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+4]+qipan[y+2][x+4]+qipan[y+1][x+4]+qipan[y][x+4]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		// �����ĸ������������ĸ���λ���


		// ������б������
		if ((qipan[y+4][x+4]+qipan[y+5][x+5]+qipan[y+6][x+6]+qipan[y+7][x+7]+qipan[y+8][x+8]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+5]+qipan[y+2][x+6]+qipan[y+1][x+7]+qipan[y][x+8]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+3]+qipan[y+6][x+2]+qipan[y+7][x+1]+qipan[y+8][x]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+3]+qipan[y+2][x+2]+qipan[y+1][x+1]+qipan[y][x]) == 5)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}

		// ���Ǽ����ӵ�
		if ((qipan[y+4][x+4]+qipan[y+4][x+5]+qipan[y+4][x+6]+qipan[y+4][x+7]+qipan[y+4][x+8]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+4][x+3]+qipan[y+4][x+2]+qipan[y+4][x+1]+qipan[y+4][x]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+4]+qipan[y+6][x+4]+qipan[y+7][x+4]+qipan[y+8][x+4]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+4]+qipan[y+2][x+4]+qipan[y+1][x+4]+qipan[y][x+4]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		// �����ĸ������������ĸ���λ���


		// ������б������
		if ((qipan[y+4][x+4]+qipan[y+5][x+5]+qipan[y+6][x+6]+qipan[y+7][x+7]+qipan[y+8][x+8]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+5]+qipan[y+2][x+6]+qipan[y+1][x+7]+qipan[y][x+8]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+3]+qipan[y+6][x+2]+qipan[y+7][x+1]+qipan[y+8][x]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+3]+qipan[y+2][x+2]+qipan[y+1][x+1]+qipan[y][x]) == 500)
		{
			printf("����Ӯ��\n");qipan_bianli();break;
		}
		qipan_bianli();
	}
}

void main()
{
	qipan_shuru();
	printf("�����ˣ�\n");
	system("pause");// ���Ƿ�ֹ�齨��.exe����������ֱ���˳���Windowsϵͳ���õĹ��ܡ�
}

