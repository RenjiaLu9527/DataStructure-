#include<stdio.h>
#include<stdlib.h>
#include<String.h>


 
typedef struct{
 	char name[20];
	char id[20];
	char job[20];
}personInfo;

#define ElemType personInfo
#define List_Size 100
#define ListIncrement 10

#define OVERFLOW 0 
#define ERROR 0
#define OK 1

typedef struct{
	ElemType * elem;//���Ա� ������ַ
	int length;
	int listsize;

}SqList;

/************************************************************************
	˳���



************************************************************************/
//��ʼ��
void InitSqList(SqList &L)
{
	L.elem = (ElemType *)malloc(sizeof(ElemType)*List_Size);
	if(!L.elem)exit(OVERFLOW);//��� Ϊ��,�����overflow��������
	L.length = 0;
	L.listsize = List_Size;
}
//����
void CreateSqList(SqList &L,int n)
{
	//���� n ��Ԫ�ص�˳���
	int i=0;
	for(i=0;i<n;i++)
	{
		scanf("%s %s %s",L.elem[i].name,L.elem[i].id,L.elem[i].job);//name id job
		L.length++;
	}
}
//***************************����********************************
int SqListInsert(SqList &L,int i,ElemType x)
{
	int j;
	ElemType *p;
	if(i < 1 || i > L.length) return ERROR;

	if(L.length >= L.listsize)//����ռ�����--���ӿռ�
	{
		//ԭ�ȵ��ڴ��С����û���㹻�Ŀ��пռ��������䣬��ô�Ӷ���������һ��newsize��С���ڴ�,����ԭ����С�ڴ�ռ��е����ݸ��Ƶ�newsize��
		p = (ElemType *)realloc(L.elem,sizeof(ElemType)*(L.listsize + ListIncrement));
		if(!p) exit(OVERFLOW);
		L.elem = p;
		L.listsize += ListIncrement;
	}

	for(j = L.length-1;j>=i-1;j--)L.elem[j+1] = L.elem[j];//Ԫ�����κ���һλ

	L.elem[i-1] = x;//����
	L.length++;//�������� 
	return OK;//����ɹ�
}
//***************************ɾ��*******************************
int SqListDelete(SqList &L,int i)
{
	int j;
	if(i<1 || i>L.length) return ERROR;

	for(j=i-1;j<L.length-1;j++) L.elem[j] = L.elem[j+1];//Ԫ������ǰ��һλ

	L.length--;
	return OK;
}
//��ʾ
void DisplaySqList(SqList &L)
{
	int i;
	for(i=0;i<L.length;i++)
	{
		printf("--����:%8s --����:%8s --ְ��:%8s .\n",L.elem[i].name,L.elem[i].id,L.elem[i].job);
	
	}
}
//����
int LocatedElem(SqList L,ElemType x)
{
	int compare(ElemType e1,ElemType x);//��������
	int i=1;//strcmp(s1,s2) ��s1=s2ʱ������ֵ=0
	while(i<=L.length && compare(L.elem[i-1],x)!=1) i++;
	
	if(i<=L.length)
		return i;
	else 
		return ERROR;


}
//����
void DestorySqList(SqList &L)
{
	free(L.elem);//�ͷ��ڴ�
}

/************************************************************************
                         ˳��� ������



************************************************************************/
//
int compare(ElemType e1,ElemType x)
{
	if(strcmp((const char*)e1.name,x.name) == 0 && strcmp((const char*)e1.id,x.id) == 0 && strcmp((const char*)e1.job,x.job) == 0)
	{
		return OK;

	}else
	{
		return ERROR;	
	}
}
//
int main()
{
	int len,choose,i;
	//char name[20],id[20],job[20];
	SqList L;
	ElemType insert;

	InitSqList(L);
	printf("--˳��� ������Ҫ����˳�����: ");
	scanf("%d",&len);
	printf("--����������Ա���� \n����  ����  ְ��\n");
	CreateSqList(L,len);

	printf("--��ʾ����Ա����Ϣ����\n����  ����  ְ��\n");
	DisplaySqList(L);

	while(true)
	{
		printf("\n\n***********************************\n--�˵�--\n--�� 1 ����Ա����Ϣ\n--�� 2 ɾ��Ա����Ϣ\n--�� 3 ��ʾ����Ա����Ϣ\n--�� 4 ��������Ա������\n***********************************\n��ѡ��: ");
		scanf("%d",&choose);
		switch(choose){
		case 1:{
			printf("--����������Ա����\n����   ����   ְ��\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			printf(SqListInsert(L,L.length,insert)==1?"--����ɹ�\n":"--����ʧ�� 001\n");//ÿ�β��뵽����ǰ�棬Ϊ�����ڶ�
			break;
		}
		case 2:{
			printf("--��������Ҫɾ��Ա����\n����   ����   ְ��\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			i = LocatedElem(L,insert);
			if(i>0 && i<L.length+1)//��һ��Ԫ��λ��Ϊ 1
			{
				printf("\n�ɹ���ѯ��Ա����Ϣ -- λ��: %02d \n",i);
				i =	SqListDelete(L,i);
				printf("%-16s\n",(i == 1?"\nɾ���ɹ�\n":"\nɾ��ʧ�� ����λ�ýű��Ƿ����\n"));
			}else
			{
				printf("\nδ��ѯ��Ա����Ϣ -- λ��: %02d \n",i);
			}
			break;
			   }
		case 3:{
			printf("\nԱ����Ϣ����\n******************************************************\n");
				DisplaySqList(L);
				printf("\n******************************************************\n");
				break;
			   }
		case 4:{
				
			    DestorySqList(L);
				printf("\n******************�������� �������*******************\n");
				exit(OVERFLOW);
			   }
		default:printf("\n��������ȷ��ѡ��: ");

		}
 
			printf("\n#####�����������..#####");
			getchar();
			getchar();
			printf("\n-------------------���Ƿָ���---------------------------\n");
			printf("-------------------�ָ�������---------------------------\n");
			printf("-------------------�ָ�������---------------------------\n");
	}

	return 0;
}