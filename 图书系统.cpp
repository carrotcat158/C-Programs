#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// �����ļ����ģ��
void ���(FILE *f)
{
	printf("���ڼ��.........\n");
	char ѡ��;
	f = fopen("library.dat","r");
	if(f == NULL)
	{
		printf("�ļ����ܲ����ڣ��Ƿ񴴽���");
		printf("����y/n \n");
		ѡ��=getchar();
		switch(ѡ��)
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
	int ���;
	char ����[30];
	double �۸�;
};


// ���ṹ��д������
struct Bookslist *Create(Bookslist *h)
{
	int �鼮���;
	char �鼮����[50],ch[4]="end";
	double �鼮�۸�;
	h = NULL;
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	printf("\n�������鼮���\n");
	scanf("%d", &�鼮���);
	getchar();
	printf("�������鼮����\n");
	scanf("%s", &�鼮����);
	getchar();
	printf("�������鼮�۸�\n");
	scanf("%lf", &�鼮�۸�);
	getchar();
	h->��� = �鼮���;
	strcpy(h->����,�鼮����);
	h->�۸� = �鼮�۸�;
	return h;
};

void д���ļ�(FILE *f, struct Bookslist *h)
{
	f = fopen("library.dat","a+");
	fwrite(h, sizeof(struct Bookslist), 1, f);
	free(h);
	fclose(f);
}

int �����鼮���(FILE *f, struct Bookslist *h);
// �����������ģ�飬�����ǽ��ж���ļ�д�������ģ��
void �ļ��Ķ��д�����(FILE *f, struct Bookslist *h)
{
	char ch[4] = "end";
	printf("���Ϊ-1 �� ����Ϊ end �� �۸�Ϊ-1�����˳�\n����Ѿ���������¼��\n");
	while(1)
	{	
		h = Create(h);
		if(h->��� < -1)
		{
				printf("��Ų���Ϊ������ӦΪ������\n");
				break;
		}
		if(h->�۸� < -1)
		{
			printf("�۸�ӦΪ����С��\n");
			break;
		}
		if(h->��� == -1 || strcmp(h->����, ch) == 0 ||h->�۸� == -1)
			break;
		// ������Ƿ��ظ�
		if(�����鼮���(f, h) == -1)
			break;
		д���ļ�(f, h);
	}
}


void ��ȡ�ļ�(FILE *f)
{
	f = fopen("library.dat","r");
	int ��ֹ��� = 0;
	struct Bookslist temp1;
	/*
	������δ�������bug��
	while(!feof)��ȡ�ļ�������һ�ж�����
	���Զ�������޸�
	*/
	while(!feof(f))
	{
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		��ֹ���++;
	}
	rewind(f);
	printf("���\t\t����\t\t\t\t�۸�\n");
	while(��ֹ���-1)
	{
		��ֹ���--;
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		printf("%-10d\t%-30s\t%.2f\n",temp1.���, temp1.����, temp1.�۸�);
	}
	fclose(f);
}

int �����鼮���(FILE *f, struct Bookslist *h)
{
	f = fopen("library.dat","r");
	int ��ֹ��� = 0;
	struct Bookslist temp1;
	while(!feof(f))
	{
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		��ֹ���++;
	}
	rewind(f);
	while(��ֹ���-1)
	{
		��ֹ���--;
		fread(&temp1, sizeof(struct Bookslist), 1, f);
		if(temp1.��� == h->���)
		{
			printf("�Ѿ����ڸñ��\n");
			return -1;
		}
	}
	fclose(f);
	return temp1.���;
}

void ����ĳ����ŵ�ȫ����Ϣ(FILE *f)
{
	int ���, �ж��Ƿ�鵽 = 0;
	scanf("%d", &���);
	f = fopen("library.dat","r");
	int ��ֹ��� = 0;
	struct Bookslist temp2;
	while(!feof(f))
	{
		fread(&temp2, sizeof(struct Bookslist), 1, f);
		��ֹ���++;
	}
	rewind(f);
	printf("���\t\t����\t\t\t\t�۸�\n");
	while(��ֹ���-1)
	{
		��ֹ���--;
		fread(&temp2, sizeof(struct Bookslist), 1, f);
		if(temp2.��� == ���)
		{
				printf("%-10d\t%-30s\t%.2f\n",temp2.���, temp2.����, temp2.�۸�);
				�ж��Ƿ�鵽++;
		}
	}
	if(�ж��Ƿ�鵽 == 0)
		printf("δ��ѯ���ñ�ż��������Ϣ\n");
	fclose(f);
}

int �жϱ���Ƿ����(FILE *f, struct Bookslist *h)
{
	int λ�� = 0;
	int �жϴ��� = 0;
	f = fopen("library.dat","r");
	int ��ֹ��� = 0;
	struct Bookslist temp3;
	while(!feof(f))
	{
		fread(&temp3, sizeof(struct Bookslist), 1, f);
		��ֹ���++;
	}
	rewind(f);
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	scanf("%d",&h->���);
	while(��ֹ���-1)
	{
		��ֹ���--;
		λ��++;
		fread(&temp3, sizeof(struct Bookslist), 1, f);
		if(temp3.��� == h->���)
		{
			printf("�Ѿ��ҵ��ñ��\n");
			�жϴ���++;
			break;
		}
	}
	fclose(f);
	if(�жϴ��� != 1)
	{
		printf("û���ҵ��ñ��\n");
		return 0;
	}
	else
		return λ��;
	free(h);
}

int ��ȡ�ļ�����(FILE *f)
{
	f = fopen("library.dat","r");
	int ��ֹ��� = 0;
	struct Bookslist temp4;

	while(!feof(f))
	{
		fread(&temp4, sizeof(struct Bookslist), 1, f);
		��ֹ���++;
	}
	fclose(f);
	int ���� = ��ֹ��� - 1;
	return ����;
}

void ɾ��ĳ����ŵ�ȫ����Ϣ(FILE *f, struct Bookslist *h)
{
	FILE *ffp;
	char �ļ�����new[15] ="library1.dat";
	char �ļ�����old[15] = "library.dat";
	f = fopen("library.dat", "r");
	ffp = fopen("library1.dat","a+");
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	int ���λ��,�ļ�д��λ�� = 1, ���� = ��ȡ�ļ�����(f);
	���λ�� = �жϱ���Ƿ����(f, h);
	while(����)
	{
		����--;
		fread(h, sizeof(struct Bookslist), 1, f);
		if(�ļ�д��λ�� != ���λ��)
			fwrite(h, sizeof(struct Bookslist), 1, ffp);	
		�ļ�д��λ��++;
	}
	fclose(f);
	fclose(ffp);
	if(remove(�ļ�����old) == 0)
		printf("ɾ���ɹ�!\n");
	else
		printf("ɾ��ʧ��!\n");
	if(rename(�ļ�����new,�ļ�����old) == 0)
		printf("ɾ���ɹ�!\n");
	else
		printf("ɾ��ʧ��!\n");	
	free(h);
}

void �޸�ĳ����ŵ�ȫ����Ϣ(FILE *f, struct Bookslist *h)
{
	FILE *fffp;
	char �ļ�����new[15] ="library1.dat";
	char �ļ�����old[15] = "library.dat";
	f = fopen("library.dat", "r");
	fffp = fopen("library1.dat","a+");
	h = (struct Bookslist*)malloc(sizeof(struct Bookslist));
	int ���λ��,�ļ�д��λ�� = 1, ���� = ��ȡ�ļ�����(f);
	���λ�� = �жϱ���Ƿ����(f, h);
	while(����)
	{
		����--;
		fread(h, sizeof(struct Bookslist), 1, f);
		if(�ļ�д��λ�� != ���λ��)
			fwrite(h, sizeof(struct Bookslist), 1, fffp);
		else
		{
			printf("�������±��\n");
			scanf("%d", &h->���);
			getchar();
			printf("����������\n");
			scanf("%s", &h->����);
			getchar();
			printf("������۸�\n");
			scanf("%f", &h->�۸�);
			getchar();
			fwrite(h, sizeof(struct Bookslist), 1, fffp);
		}
		�ļ�д��λ��++;
	}
	fclose(f);
	fclose(fffp);
	if(remove(�ļ�����old) == 0)
	    printf("�޸ĳɹ�!\n");
	   else
	    printf("�޸�ʧ��!\n");
    if(rename(�ļ�����new,�ļ�����old) == 0)
    	printf("�޸ĳɹ�!\n");
    else
	    printf("�޸�ʧ��!\n");	
}

// ���ǲ˵�ģ�飬����ѡ������Ҫ�Ĳ���(�������ģ�鼯����һ�𣬷������)
void �˵�(FILE *f, struct Bookslist *h)
{
	printf("������ָ��:\n");
	int ch;
	scanf("%d", &ch);
	switch(ch)
	{
	case -1:printf("�����˳�����\n");exit(0);break;
	case 0:system("cls");�˵�(f, h);break;
	case 1:
		{
			printf("-1:�˳�����\t0:��յ�ǰҳ����Ϣ\t1:ָ�����\t2:д���ļ�\t3:��ȡ�ļ�\t4:����ĳ����ŵ�ȫ����Ϣ\n");
			printf(" 5:ɾ��ĳ����ŵ�ȫ����Ϣ\t\t6:�޸�ĳ����ŵ�ȫ����Ϣ\n");
			�˵�(f, h);break;
		}
	case 2:�ļ��Ķ��д�����(f, h);�˵�(f, h);break;
	case 3:��ȡ�ļ�(f);�˵�(f, h);break;
	case 4:printf("��������Ҫ��ѯ���鼮���\n");����ĳ����ŵ�ȫ����Ϣ(f);�˵�(f, h);break;
	case 5:printf("��������Ҫɾ���ı��\n");ɾ��ĳ����ŵ�ȫ����Ϣ(f, h);�˵�(f, h);break;
	case 6:printf("��������Ҫ�޸ĵı��\n");�޸�ĳ����ŵ�ȫ����Ϣ(f, h);�˵�(f, h);break;
	default :printf("δ��ѯ��������\n");�˵�(f, h);break;
	}
}

void main()
{
	// һ��Ҫ��ʼ������Ȼ����־��棡
	FILE *fp=NULL;
	struct Bookslist *books;
	books = NULL;

	���(fp);

	printf("����1��ָ�����\n");
	�˵�(fp, books);
	
	// ��ֹ�����Զ��ر�
	system("pause");
}

