#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// �����ļ����ģ��
void jiance(FILE *f)
{
	printf("���ڼ��.........\n");
	char xuanze;
	f = fopen("library.dat","r");
	if(f == NULL)
	{
		printf("�ļ����ܲ����ڣ��Ƿ񴴽���");
		printf("����y/n \n");
		xuanze=getchar();
		switch(xuanze)
		{
		case 'Y':
		case 'y':f = fopen("library.dat","w");fclose(f);printf("�ļ���ʼ���ɹ���\n");break;
		case 'N':
		case 'n':printf("�����˳�����......\n");exit(0);break;
		default :printf("δ֪����\n");break;
		} 
	}
	else
	{
		printf("�ļ��򿪳ɹ���\n");
	}
	fclose(f);
}

// ����һ���ṹ�壬��������ͼ������
struct Bookslist{
	int bianhao;
	char booksname[30];
	double price;
};


// ���ṹ��д������
struct Bookslist *Create(Bookslist *h)
{
	int boosk_bianhao;
	char boosk_name[50],ch[4]="end";
	double boosk_price;
	h = NULL;
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	printf("\n�������鼮���\n");
	scanf("%d", &boosk_bianhao);
	getchar();
	printf("�������鼮����\n");
	scanf("%s", &boosk_name);
	getchar();
	printf("�������鼮�۸�\n");
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
// �����������ģ�飬�����ǽ��ж���ļ�д�������ģ��
void file_more_write(FILE *f, struct Bookslist *h)
{
	char ch[4] = "end";
	printf("���Ϊ-1 �� ����Ϊ end �� �۸�Ϊ-1�����˳�\n����Ѿ���������¼��\n");
	while(1)
	{	
		h = Create(h);
		if(h->bianhao < -1)
		{
				printf("��Ų���Ϊ������ӦΪ������\n");
				break;
		}
		if(h->price < -1)
		{
			printf("�۸�ӦΪ����С��\n");
			break;
		}
		if(h->bianhao == -1 || strcmp(h->booksname, ch) == 0 ||h->price == -1)
			break;
		// ������Ƿ��ظ�
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
	������δ�������bug��
	while(!feof)��ȡ�ļ�������һ�ж�����
	���Զ�������޸�
	*/
	while(!feof(f))
	{
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		stop_more_read++;
	}
	rewind(f);
	printf("���\t\t����\t\t\t\t�۸�\n");
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
			printf("�Ѿ����ڸñ��\n");
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
	printf("���\t\t����\t\t\t\t�۸�\n");
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
		printf("δ��ѯ���ñ�ż��������Ϣ\n");
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
			printf("�Ѿ��ҵ��ñ��\n");
			info_exist++;
			break;
		}
	}
	fclose(f);
	if(info_exist != 1)
	{
		printf("û���ҵ��ñ��\n");
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
		printf("ɾ���ɹ�!\n");
	else
		printf("ɾ��ʧ��!\n");
	if(rename(file_namenew,file_nameold) == 0)
		printf("ɾ���ɹ�!\n");
	else
		printf("ɾ��ʧ��!\n");	
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
			printf("�������±��\n");
			scanf("%d", &h->bianhao);
			getchar();
			printf("����������\n");
			scanf("%s", &h->booksname);
			getchar();
			printf("������۸�\n");
			scanf("%f", &h->price);
			getchar();
			fwrite(h, sizeof(struct Bookslist), 1, fffp);
		}
		file_write_position++;
	}
	fclose(f);
	fclose(fffp);
	if(remove(file_nameold) == 0)
	    printf("�޸ĳɹ�!\n");
	   else
	    printf("�޸�ʧ��!\n");
    if(rename(file_namenew,file_nameold) == 0)
    	printf("�޸ĳɹ�!\n");
    else
	    printf("�޸�ʧ��!\n");	
}

// ���ǲ˵�ģ�飬����ѡ������Ҫ�Ĳ���(�������ģ�鼯����һ�𣬷������)
void caidan(FILE *f, struct Bookslist *h)
{
	printf("������ָ��:\n");
	int ch;
	scanf("%d", &ch);
	switch(ch)
	{
	case -1:printf("�����˳�����\n");exit(0);break;
	case 0:system("cls");caidan(f, h);break;
	case 1:
		{
			printf("-1:�˳�����\t0:��յ�ǰҳ����Ϣ\t1:ָ�����\t2:д���ļ�\t3:��ȡ�ļ�\t4:����ĳ����ŵ�ȫ����Ϣ\n");
			printf(" 5:ɾ��ĳ����ŵ�ȫ����Ϣ\t\t6:�޸�ĳ����ŵ�ȫ����Ϣ\n");
			caidan(f, h);break;
		}
	case 2:file_more_write(f, h);caidan(f, h);break;
	case 3:read_file(f);caidan(f, h);break;
	case 4:printf("��������Ҫ��ѯ���鼮���\n");select_something_bianhao(f);caidan(f, h);break;
	case 5:printf("��������Ҫɾ���ı��\n");remove_bianhaxingxi(f, h);caidan(f, h);break;
	case 6:printf("��������Ҫ�޸ĵı��\n");changed_bianhaoxingxi(f, h);caidan(f, h);break;
	default :printf("δ��ѯ��������\n");caidan(f, h);break;
	}
}

int main()
{
	// һ��Ҫ��ʼ������Ȼ����־��棡
	FILE *fp=NULL;
	struct Bookslist *books;
	books = NULL;

	jiance(fp);

	printf("����1��ָ�����\n");
	caidan(fp, books);
	
	// ��ֹ�����Զ��ر�
	system("pause");
	return 0;
}

