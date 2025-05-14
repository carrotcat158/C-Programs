#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// 这是文件检测模块
void 检测(FILE *f)
{
	printf("正在检测.........\n");
	char 选择;
	f = fopen("library.dat","r");
	if(f == NULL)
	{
		printf("文件可能不存在！是否创建？");
		printf("输入y/n \n");
		选择=getchar();
		switch(选择)
		{
		case 'Y':
		case 'y':f = fopen("library.dat","w");fclose(f);printf("文件初始化成功！\n");break;
		case 'N':
		case 'n':printf("正在退出程序......\n");exit(0);break;
		default :printf("未知命令\n");break;
		} 
	}
	else
	{
		printf("文件打开成功！\n");
	}
	fclose(f);
}

// 创建一个结构体，用来输入图书数据
struct Bookslist{
	int 编号;
	char 书名[30];
	double 价格;
};


// 给结构体写入内容
struct Bookslist *Create(Bookslist *h)
{
	int 书籍编号;
	char 书籍名称[50],ch[4]="end";
	double 书籍价格;
	h = NULL;
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	printf("\n请输入书籍编号\n");
	scanf("%d", &书籍编号);
	getchar();
	printf("请输入书籍名称\n");
	scanf("%s", &书籍名称);
	getchar();
	printf("请输入书籍价格\n");
	scanf("%lf", &书籍价格);
	getchar();
	h->编号 = 书籍编号;
	strcpy(h->书名,书籍名称);
	h->价格 = 书籍价格;
	return h;
};

void 写入文件(FILE *f, struct Bookslist *h)
{
	f = fopen("library.dat","a+");
	fwrite(h, sizeof(struct Bookslist), 1, f);
	free(h);
	fclose(f);
}

int 查找书籍编号(FILE *f, struct Bookslist *h);
// 结合上面两个模块，下面是进行多次文件写入操作的模块
void 文件的多次写入操作(FILE *f, struct Bookslist *h)
{
	char ch[4] = "end";
	printf("编号为-1 或 书名为 end 或 价格为-1，会退出\n编号已经存在则不能录入\n");
	while(1)
	{	
		h = Create(h);
		if(h->编号 < -1)
		{
				printf("编号不能为负数，应为正整数\n");
				break;
		}
		if(h->价格 < -1)
		{
			printf("价格应为正的小数\n");
			break;
		}
		if(h->编号 == -1 || strcmp(h->书名, ch) == 0 ||h->价格 == -1)
			break;
		// 检查编号是否重复
		if(查找书籍编号(f, h) == -1)
			break;
		写入文件(f, h);
	}
}


void 读取文件(FILE *f)
{
	f = fopen("library.dat","r");
	int 防止多读 = 0;
	struct Bookslist temp1;
	/*
	下面这段代码是修bug的
	while(!feof)读取文件会把最后一行读两遍
	所以对其进行修复
	*/
	while(!feof(f))
	{
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		防止多读++;
	}
	rewind(f);
	printf("编号\t\t书名\t\t\t\t价格\n");
	while(防止多读-1)
	{
		防止多读--;
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		printf("%-10d\t%-30s\t%.2f\n",temp1.编号, temp1.书名, temp1.价格);
	}
	fclose(f);
}

int 查找书籍编号(FILE *f, struct Bookslist *h)
{
	f = fopen("library.dat","r");
	int 防止多读 = 0;
	struct Bookslist temp1;
	while(!feof(f))
	{
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		防止多读++;
	}
	rewind(f);
	while(防止多读-1)
	{
		防止多读--;
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		if(temp1.编号 == h->编号)
		{
			printf("已经存在该编号\n");
			return -1;
		}
	}
	fclose(f);
	return temp1.编号;
}

void 查找某个编号的全部信息(FILE *f)
{
	int 编号, 判断是否查到 = 0;
	scanf("%d", &编号);
	f = fopen("library.dat","r");
	int 防止多读 = 0;
	struct Bookslist temp2;
	while(!feof(f))
	{
		fread(&temp2, sizeof(struct Bookslist), 1, f);
		防止多读++;
	}
	rewind(f);
	printf("编号\t\t书名\t\t\t\t价格\n");
	while(防止多读-1)
	{
		防止多读--;
		fread(&temp2, sizeof(struct Bookslist), 1, f);
		if(temp2.编号 == 编号)
		{
				printf("%-10d\t%-30s\t%.2f\n",temp2.编号, temp2.书名, temp2.价格);
				判断是否查到++;
		}
	}
	if(判断是否查到 == 0)
		printf("未查询到该编号及其相关信息\n");
	fclose(f);
}

int 判断编号是否存在(FILE *f, struct Bookslist *h)
{
	int 位置 = 0;
	int 判断存在 = 0;
	f = fopen("library.dat","r");
	int 防止多读 = 0;
	struct Bookslist temp3;
	while(!feof(f))
	{
		fread(&temp3, sizeof(struct Bookslist), 1, f);
		防止多读++;
	}
	rewind(f);
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	scanf("%d",&h->编号);
	while(防止多读-1)
	{
		防止多读--;
		位置++;
		fread(&temp3, sizeof(struct Bookslist), 1, f);
		if(temp3.编号 == h->编号)
		{
			printf("已经找到该编号\n");
			判断存在++;
			break;
		}
	}
	fclose(f);
	if(判断存在 != 1)
	{
		printf("没有找到该编号\n");
		return 0;
	}
	else
		return 位置;
	free(h);
}

int 读取文件行数(FILE *f)
{
	f = fopen("library.dat","r");
	int 防止多读 = 0;
	struct Bookslist temp4;

	while(!feof(f))
	{
		fread(&temp4, sizeof(struct Bookslist), 1, f);
		防止多读++;
	}
	fclose(f);
	int 行数 = 防止多读 - 1;
	return 行数;
}

void 删除某个编号的全部信息(FILE *f, struct Bookslist *h)
{
	FILE *ffp;
	char 文件名称new[15] ="library1.dat";
	char 文件名称old[15] = "library.dat";
	f = fopen("library.dat", "r");
	ffp = fopen("library1.dat","a+");
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	int 编号位置,文件写入位置 = 1, 行数 = 读取文件行数(f);
	编号位置 = 判断编号是否存在(f, h);
	while(行数)
	{
		行数--;
		fread(h, sizeof(struct Bookslist), 1, f);
		if(文件写入位置 != 编号位置)
			fwrite(h, sizeof(struct Bookslist), 1, ffp);	
		文件写入位置++;
	}
	fclose(f);
	fclose(ffp);
	if(remove(文件名称old) == 0)
		printf("删除成功!\n");
	else
		printf("删除失败!\n");
	if(rename(文件名称new,文件名称old) == 0)
		printf("删除成功!\n");
	else
		printf("删除失败!\n");	
	free(h);
}

void 修改某个编号的全部信息(FILE *f, struct Bookslist *h)
{
	FILE *fffp;
	char 文件名称new[15] ="library1.dat";
	char 文件名称old[15] = "library.dat";
	f = fopen("library.dat", "r");
	fffp = fopen("library1.dat","a+");
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	int 编号位置,文件写入位置 = 1, 行数 = 读取文件行数(f);
	编号位置 = 判断编号是否存在(f, h);
	while(行数)
	{
		行数--;
		fread(h, sizeof(struct Bookslist), 1, f);
		if(文件写入位置 != 编号位置)
			fwrite(h, sizeof(struct Bookslist), 1, fffp);
		else
		{
			printf("请输入新编号\n");
			scanf("%d", &h->编号);
			getchar();
			printf("请输入书名\n");
			scanf("%s", &h->书名);
			getchar();
			printf("请输入价格\n");
			scanf("%f", &h->价格);
			getchar();
			fwrite(h, sizeof(struct Bookslist), 1, fffp);
		}
		文件写入位置++;
	}
	fclose(f);
	fclose(fffp);
	if(remove(文件名称old) == 0)
	    printf("修改成功!\n");
	   else
	    printf("修改失败!\n");
    if(rename(文件名称new,文件名称old) == 0)
    	printf("修改成功!\n");
    else
	    printf("修改失败!\n");	
}

// 这是菜单模块，用来选择你需要的操作(将上面的模块集中在一起，方便调用)
void 菜单(FILE *f, struct Bookslist *h)
{
	printf("请输入指令:\n");
	int ch;
	scanf("%d", &ch);
	switch(ch)
	{
	case -1:printf("正在退出程序\n");exit(0);break;
	case 0:system("cls");菜单(f, h);break;
	case 1:
		{
			printf("-1:退出程序\t0:清空当前页面信息\t1:指令介绍\t2:写入文件\t3:读取文件\t4:查找某个编号的全部信息\n");
			printf(" 5:删除某个编号的全部信息\t\t6:修改某个编号的全部信息\n");
			菜单(f, h);break;
		}
	case 2:文件的多次写入操作(f, h);菜单(f, h);break;
	case 3:读取文件(f);菜单(f, h);break;
	case 4:printf("请输入你要查询的书籍编号\n");查找某个编号的全部信息(f);菜单(f, h);break;
	case 5:printf("请输入你要删除的编号\n");删除某个编号的全部信息(f, h);菜单(f, h);break;
	case 6:printf("请输入你要修改的编号\n");修改某个编号的全部信息(f, h);菜单(f, h);break;
	default :printf("未查询到该命令\n");菜单(f, h);break;
	}
}

void main()
{
	// 一定要初始化，不然会出现警告！
	FILE *fp=NULL;
	struct Bookslist *books;
	books = NULL;

	检测(fp);

	printf("输入1打开指令介绍\n");
	菜单(fp, books);
	
	// 防止程序自动关闭
	system("pause");
}

