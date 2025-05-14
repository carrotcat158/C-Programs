#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// 这是文件检测模块
void jiance(FILE *f)
{
	printf("正在检测.........\n");
	char xuanze;
	f = fopen("library.dat","r");
	if(f == NULL)
	{
		printf("文件可能不存在！是否创建？");
		printf("输入y/n \n");
		xuanze=getchar();
		switch(xuanze)
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
	int bianhao;
	char booksname[30];
	double price;
};


// 给结构体写入内容
struct Bookslist *Create(Bookslist *h)
{
	int boosk_bianhao;
	char boosk_name[50],ch[4]="end";
	double boosk_price;
	h = NULL;
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	printf("\n请输入书籍编号\n");
	scanf("%d", &boosk_bianhao);
	getchar();
	printf("请输入书籍名称\n");
	scanf("%s", &boosk_name);
	getchar();
	printf("请输入书籍价格\n");
	scanf("%lf", &boosk_price);
	getchar();
	h->bianhao = boosk_bianhao;
	strcpy(h->booksname,boosk_name);
	h->price = boosk_price;
	return h;
};

void write_file(FILE *f, struct Bookslist *h)
{
	f = fopen("library.dat","a+");
	fwrite(h, sizeof(struct Bookslist), 1, f);
	free(h);
	fclose(f);
}

int select_books_bianhao(FILE *f, struct Bookslist *h);
// 结合上面两个模块，下面是进行多次文件写入操作的模块
void file_more_write(FILE *f, struct Bookslist *h)
{
	char ch[4] = "end";
	printf("编号为-1 或 书名为 end 或 价格为-1，会退出\n编号已经存在则不能录入\n");
	while(1)
	{	
		h = Create(h);
		if(h->bianhao < -1)
		{
				printf("编号不能为负数，应为正整数\n");
				break;
		}
		if(h->price < -1)
		{
			printf("价格应为正的小数\n");
			break;
		}
		if(h->bianhao == -1 || strcmp(h->booksname, ch) == 0 ||h->price == -1)
			break;
		// 检查编号是否重复
		if(select_books_bianhao(f, h) == -1)
			break;
		write_file(f, h);
	}
}


void read_file(FILE *f)
{
	f = fopen("library.dat","r");
	int stop_more_read = 0;
	struct Bookslist temp1;
	/*
	下面这段代码是修bug的
	while(!feof)读取文件会把最后一行读两遍
	所以对其进行修复
	*/
	while(!feof(f))
	{
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		stop_more_read++;
	}
	rewind(f);
	printf("编号\t\t书名\t\t\t\t价格\n");
	while(stop_more_read-1)
	{
		stop_more_read--;
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		printf("%-10d\t%-30s\t%.2f\n",temp1.bianhao, temp1.booksname, temp1.price);
	}
	fclose(f);
}

int select_books_bianhao(FILE *f, struct Bookslist *h)
{
	f = fopen("library.dat","r");
	int stop_more_read = 0;
	struct Bookslist temp1;
	while(!feof(f))
	{
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		stop_more_read++;
	}
	rewind(f);
	while(stop_more_read-1)
	{
		stop_more_read--;
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		if(temp1.bianhao == h->bianhao)
		{
			printf("已经存在该编号\n");
			return -1;
		}
	}
	fclose(f);
	return temp1.bianhao;
}

void select_something_bianhao(FILE *f)
{
	int bianhao, info_selected = 0;
	scanf("%d", &bianhao);
	f = fopen("library.dat","r");
	int stop_more_read = 0;
	struct Bookslist temp2;
	while(!feof(f))
	{
		fread(&temp2, sizeof(struct Bookslist), 1, f);
		stop_more_read++;
	}
	rewind(f);
	printf("编号\t\t书名\t\t\t\t价格\n");
	while(stop_more_read-1)
	{
		stop_more_read--;
		fread(&temp2, sizeof(struct Bookslist), 1, f);
		if(temp2.bianhao == bianhao)
		{
				printf("%-10d\t%-30s\t%.2f\n",temp2.bianhao, temp2.booksname, temp2.price);
				info_selected++;
		}
	}
	if(info_selected == 0)
		printf("未查询到该编号及其相关信息\n");
	fclose(f);
}

int info_bianhao_exist(FILE *f, struct Bookslist *h)
{
	int position = 0;
	int info_exist = 0;
	f = fopen("library.dat","r");
	int stop_more_read = 0;
	struct Bookslist temp3;
	while(!feof(f))
	{
		fread(&temp3, sizeof(struct Bookslist), 1, f);
		stop_more_read++;
	}
	rewind(f);
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	scanf("%d",&h->bianhao);
	while(stop_more_read-1)
	{
		stop_more_read--;
		position++;
		fread(&temp3, sizeof(struct Bookslist), 1, f);
		if(temp3.bianhao == h->bianhao)
		{
			printf("已经找到该编号\n");
			info_exist++;
			break;
		}
	}
	fclose(f);
	if(info_exist != 1)
	{
		printf("没有找到该编号\n");
		return 0;
	}
	else
		return position;
	free(h);
}

int read_file_lines(FILE *f)
{
	f = fopen("library.dat","r");
	int stop_more_read = 0;
	struct Bookslist temp4;

	while(!feof(f))
	{
		fread(&temp4, sizeof(struct Bookslist), 1, f);
		stop_more_read++;
	}
	fclose(f);
	int lines = stop_more_read - 1;
	return lines;
}

void remove_bianhaxingxi(FILE *f, struct Bookslist *h)
{
	FILE *ffp;
	char file_namenew[15] ="library1.dat";
	char file_nameold[15] = "library.dat";
	f = fopen("library.dat", "r");
	ffp = fopen("library1.dat","a+");
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	int bianhao_position,file_write_position = 1, lines = read_file_lines(f);
	bianhao_position = info_bianhao_exist(f, h);
	while(lines)
	{
		lines--;
		fread(h, sizeof(struct Bookslist), 1, f);
		if(file_write_position != bianhao_position)
			fwrite(h, sizeof(struct Bookslist), 1, ffp);	
		file_write_position++;
	}
	fclose(f);
	fclose(ffp);
	if(remove(file_nameold) == 0)
		printf("删除成功!\n");
	else
		printf("删除失败!\n");
	if(rename(file_namenew,file_nameold) == 0)
		printf("删除成功!\n");
	else
		printf("删除失败!\n");	
	free(h);
}

void changed_bianhaoxingxi(FILE *f, struct Bookslist *h)
{
	FILE *fffp;
	char file_namenew[15] ="library1.dat";
	char file_nameold[15] = "library.dat";
	f = fopen("library.dat", "r");
	fffp = fopen("library1.dat","a+");
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	int bianhao_position,file_write_position = 1, lines = read_file_lines(f);
	bianhao_position = info_bianhao_exist(f, h);
	while(lines)
	{
		lines--;
		fread(h, sizeof(struct Bookslist), 1, f);
		if(file_write_position != bianhao_position)
			fwrite(h, sizeof(struct Bookslist), 1, fffp);
		else
		{
			printf("请输入新编号\n");
			scanf("%d", &h->bianhao);
			getchar();
			printf("请输入书名\n");
			scanf("%s", &h->booksname);
			getchar();
			printf("请输入价格\n");
			scanf("%f", &h->price);
			getchar();
			fwrite(h, sizeof(struct Bookslist), 1, fffp);
		}
		file_write_position++;
	}
	fclose(f);
	fclose(fffp);
	if(remove(file_nameold) == 0)
	    printf("修改成功!\n");
	   else
	    printf("修改失败!\n");
    if(rename(file_namenew,file_nameold) == 0)
    	printf("修改成功!\n");
    else
	    printf("修改失败!\n");	
}

// 这是菜单模块，用来选择你需要的操作(将上面的模块集中在一起，方便调用)
void caidan(FILE *f, struct Bookslist *h)
{
	printf("请输入指令:\n");
	int ch;
	scanf("%d", &ch);
	switch(ch)
	{
	case -1:printf("正在退出程序\n");exit(0);break;
	case 0:system("cls");caidan(f, h);break;
	case 1:
		{
			printf("-1:退出程序\t0:清空当前页面信息\t1:指令介绍\t2:写入文件\t3:读取文件\t4:查找某个编号的全部信息\n");
			printf(" 5:删除某个编号的全部信息\t\t6:修改某个编号的全部信息\n");
			caidan(f, h);break;
		}
	case 2:file_more_write(f, h);caidan(f, h);break;
	case 3:read_file(f);caidan(f, h);break;
	case 4:printf("请输入你要查询的书籍编号\n");select_something_bianhao(f);caidan(f, h);break;
	case 5:printf("请输入你要删除的编号\n");remove_bianhaxingxi(f, h);caidan(f, h);break;
	case 6:printf("请输入你要修改的编号\n");changed_bianhaoxingxi(f, h);caidan(f, h);break;
	default :printf("未查询到该命令\n");caidan(f, h);break;
	}
}

int main()
{
	// 一定要初始化，不然会出现警告！
	FILE *fp=NULL;
	struct Bookslist *books;
	books = NULL;

	jiance(fp);

	printf("输入1打开指令介绍\n");
	caidan(fp, books);
	
	// 防止程序自动关闭
	system("pause");
	return 0;
}

