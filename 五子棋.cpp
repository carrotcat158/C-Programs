#include <stdio.h>
#include <stdlib.h>
  // 建立足够大的棋盘
int qipan[50][50]={0},xx,yy;

  // 遍历实际下棋的棋盘
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

  //  下棋的同时，以棋子为中心遍历八个方位是否满足胜利条件
void qipan_shuru()
{
	int zhongzhi=1,x,y;
	qipan_bianli();
	while(zhongzhi)
	{
		printf("请输入x，y的坐标值\n");
		scanf("%d %d",&x,&y);
		if (x==100 && y==100)
			break;
		else if (x<1 || y<1 || y>15 || x>15)
		{
			printf("输错了，重新输入\n");
			qipan_shuru();				
		}
		printf("请输入棋子的值,1是白子，100是黑子\n");
		scanf("%d",&qipan[y+4][x+4]);
		if (qipan[y+4][x+4] != 0 && qipan[y+4][x+4] != 1 && qipan[y+4][x+4] != 100)
		{
			printf("输错了，重新输入\n");
			qipan[y+4][x+4]=0;
		}
		
		// 这是检测白子的
		if ((qipan[y+4][x+4]+qipan[y+4][x+5]+qipan[y+4][x+6]+qipan[y+4][x+7]+qipan[y+4][x+8]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+4][x+3]+qipan[y+4][x+2]+qipan[y+4][x+1]+qipan[y+4][x]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+4]+qipan[y+6][x+4]+qipan[y+7][x+4]+qipan[y+8][x+4]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+4]+qipan[y+2][x+4]+qipan[y+1][x+4]+qipan[y][x+4]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}
		// 以上四个是上下左右四个方位检测


		// 以下是斜方向检测
		if ((qipan[y+4][x+4]+qipan[y+5][x+5]+qipan[y+6][x+6]+qipan[y+7][x+7]+qipan[y+8][x+8]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+5]+qipan[y+2][x+6]+qipan[y+1][x+7]+qipan[y][x+8]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+3]+qipan[y+6][x+2]+qipan[y+7][x+1]+qipan[y+8][x]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+3]+qipan[y+2][x+2]+qipan[y+1][x+1]+qipan[y][x]) == 5)
		{
			printf("白子赢了\n");qipan_bianli();break;
		}

		// 这是检测黑子的
		if ((qipan[y+4][x+4]+qipan[y+4][x+5]+qipan[y+4][x+6]+qipan[y+4][x+7]+qipan[y+4][x+8]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+4][x+3]+qipan[y+4][x+2]+qipan[y+4][x+1]+qipan[y+4][x]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+4]+qipan[y+6][x+4]+qipan[y+7][x+4]+qipan[y+8][x+4]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+4]+qipan[y+2][x+4]+qipan[y+1][x+4]+qipan[y][x+4]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		// 以上四个是上下左右四个方位检测


		// 以下是斜方向检测
		if ((qipan[y+4][x+4]+qipan[y+5][x+5]+qipan[y+6][x+6]+qipan[y+7][x+7]+qipan[y+8][x+8]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+5]+qipan[y+2][x+6]+qipan[y+1][x+7]+qipan[y][x+8]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+5][x+3]+qipan[y+6][x+2]+qipan[y+7][x+1]+qipan[y+8][x]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		if ((qipan[y+4][x+4]+qipan[y+3][x+3]+qipan[y+2][x+2]+qipan[y+1][x+1]+qipan[y][x]) == 500)
		{
			printf("黑子赢了\n");qipan_bianli();break;
		}
		qipan_bianli();
	}
}

void main()
{
	qipan_shuru();
	printf("结束了！\n");
	system("pause");// 这是防止组建的.exe程序运行完直接退出，Windows系统调用的功能。
}

