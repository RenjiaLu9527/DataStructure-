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

typedef struct LNode{
	ElemType elem;//������
	struct LNode * next;//ָ����

}LNode,*LinkList;

/************************************************************************
								����



************************************************************************/
//��ʼ��
void InitLinkList(LinkList &L)//����ָ�붨�� &����
{
	L = (LNode *)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);//����ʧ�� �˳�

	L->next = NULL;
}
//����
void CreateLinkList(LinkList &L,int n)
{
	//���� n���ڵ�
	LNode * p;
	int i;
	
	for(i = n;i>0;--i)
	{
		p = (LNode *)malloc(sizeof(LNode));//
		scanf("%s %s %s",p->elem.name,p->elem.id,p->elem.job);

		p->next = L->next;
		L->next = p;
	}
}
//��ʾ
void DisplayLinkList(LinkList L)
{
	LNode * p;
	for(p = L->next;p;p=p->next)
		printf("%8s %8s %8s\n",p->elem.name,p->elem.id,p->elem.job);

}

//����Ų���
LNode * GetElem_L(LinkList L,int i)
{
	//i Ϊ��i���ڵ㣬��1 ��ʼ����
	LNode * p;
	int j=1;//
	p = L->next;
	if(i==0) return L;

	while(p && j<i){p = p->next; j++;}

	if(j == i) return p;//�� i ��Ԫ�ش��ڣ�������
	else return NULL;//������

}
//��ֵ����
int locateelem(LinkList L,ElemType x)
{
	LNode * p;
	int i=1;
	p=L->next;//��һ���ڵ�(ͷ�ڵ㲻��)
	int compareElem(ElemType e1,ElemType x);//��������

	while(p && (compareElem(p->elem,x)!=1)) {++i,p=p->next;}

	if(p!=NULL) return i;
	else return 0;

}
//����
int LinkListInsert_L(LinkList &L,int i,ElemType x)
{
	void copyElem(ElemType &s,ElemType &x);//��������
	LNode * p,* s;
	p = GetElem_L(L,i);//�� i ��Ԫ��֮�������Ԫ��p
	if(!p) return ERROR;

	s = (LNode *)malloc(sizeof(LNode));
	if(!s) return ERROR;

	copyElem(s->elem,x);//����data

	s->next = p->next;
	p->next = s;
	return OK;

}
//ɾ��
int LinkListDelete_L(LinkList &L,int i)
{
	//i Ϊ �ڼ��� �ڵ� ����˼
	LNode *p,*q;
	p = GetElem_L(L,i-1);//ȡ����ɾ��ǰһ���ڵ�

	if(!p) return ERROR;//ɾ��λ�ò�����

	q = p->next;
	p->next = q->next;//

	free(q);
	return OK;
	 
}
//ɾ����������
void ClearLinkList(LinkList &L)
{
	LNode *p;
	while(L->next)
	{
		p=L->next;
		L->next = p->next;
		free(p);
	}
}

////
void copyElem(ElemType &s,ElemType &x)
{
	strcpy(s.name,(const char *)x.name);
	strcpy(s.id,(const char *)x.id);
	strcpy(s.job,(const char *)x.job);

}
int compareElem(ElemType e1,ElemType x)
{
	if(strcmp((const char*)e1.name,x.name) == 0 && strcmp((const char*)e1.id,x.id) == 0 && strcmp((const char*)e1.job,x.job) == 0)
	{
		return OK;//��ͬ

	}else
	{
		return ERROR;//��ͬ
	}
}
//

//
int main()
{
	int len,choose,i;
	 
	LinkList L;
	ElemType insert;

	InitLinkList(L);
	printf("--������Ҫ����˳�����: ");
	scanf("%d",&len);
	printf("--����������Ա���� \n����  ����  ְ��\n");
	CreateLinkList(L,len);

	printf("--��ʾ����Ա����Ϣ����\n����  ����  ְ��\n");
	DisplayLinkList(L);

	while(true)
	{
		printf("\n\n***********************************\n--�˵�--\n--�� 1 ����Ա����Ϣ\n--�� 2 ɾ��Ա����Ϣ\n--�� 3 ��ʾ����Ա����Ϣ\n--�� 4 ��������Ա������\n***********************************\n��ѡ��: ");
		scanf("%d",&choose);
		switch(choose){
		case 1:{
			printf("--����������Ա����\n����   ����   ְ��\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			printf(LinkListInsert_L(L,1,insert)==1?"--����ɹ�\n":"--����ʧ�� 001\n");// 
			break;
		}
		case 2:{
			printf("--��������Ҫɾ��Ա����\n����   ����   ְ��\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			int index = locateelem(L,insert);
			if(index>0)//��һ��Ԫ��λ��Ϊ 1
			{
				printf("\n�ɹ���ѯ��Ա����Ϣ--λ��:%2d\n",index);
				i =	LinkListDelete_L(L,index);//ɾ���� i ���ڵ�
				printf("%-16s\n",(i == 1?"\nɾ���ɹ�\n":"\nɾ��ʧ�� ����λ�ýű��Ƿ����\n"));
			}else
			{
				printf("\nδ��ѯ��Ա����Ϣ--λ��:%2d\n",index);
			}
			break;
			   }
		case 3:{
			printf("\nԱ����Ϣ����\n******************************************************\n");
				DisplayLinkList(L);
				printf("\n******************************************************\n");
				break;
			   }
		case 4:{
				
			    ClearLinkList(L);
				printf("\n******************�������� �������*******************\n");
				exit(OVERFLOW);
			   }
		default:printf("\n��������ȷ��ѡ��: ");

		}
 
			printf("#####�����������..#####");
			getchar();
			getchar();
			printf("\n-------------------���Ƿָ���---------------------------\n");
			printf("-------------------�ָ�������---------------------------\n");
			printf("-------------------�ָ�������---------------------------\n");
	}

	return 0;
}