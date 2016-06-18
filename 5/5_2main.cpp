#include<stdio.h>
#include<stdlib.h>
//�궨�壨�������ؼ��ֵıȽ�Լ����


/*
*   ����̽����ɢ��    
*   di = cxi  =1,2,3,��m-1 ��򵥵����c=1

*/
//����ֵ�͹ؼ���
#define   EQ(a,b)    ((a)== (b))
#define   LT(a,b)    ((a)<(b))
#define   LQ(a,b)    ((a)<=(b))
//���ַ����͹ؼ���(�μ��α�71ҳ����)
//#define   EQ(a,b)  (! strcmp((a) , (b)))
//#define   LT(a,b)  (strcmp((a) , (b)) < 0)
//#define   LQ(a,b)  (strcmp((a) , (b)) <= 0)

#define SUCCESS 1
#define UNSUCCESS 0
#define DUOLICATE -1
#define NULLKEY -65536
#ifndef Status

#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW 0
typedef int KeyType;
//typedef int TElemType;
typedef int Status;
typedef int KeyType;
#endif

//int hashsize[]={-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536};
typedef struct{
	KeyType key;//

}ElemType;
typedef struct{
	ElemType * elem;
	int count;
	int sizeindex;
}HashTable;

int Hash(int k)
{
	int modnum = 11;//�ɵ�
	return (k%modnum);
}
void collision(int &p,int c)
{
	int i=1;//�������ɵ���
	p = (c * i);//?>?>?> ��ȡ�������
}
//��ѯ///////////////////////////////
Status SearchHash(HashTable H,KeyType k,int &p,int &c)
{
	p = Hash(k);//
	while(H.elem[p].key != NULLKEY && !EQ(k,H.elem[p].key))
	{
		collision(p,++c);
	}
	if(EQ(k,H.elem[p].key))
	{
		return OK;
	}else
	{
		return FALSE;
	}
}//end


//����////////////////////////////
Status InsertHash(HashTable &H,ElemType e)
{
	int c,p,CLLSN;
	c=0;
	CLLSN=H.sizeindex;
	if(SearchHash(H,e.key,p,c))
	{
		return DUOLICATE;//��ͻ����
	}
	else if(c < CLLSN)//��ͻ����
	{
		H.elem[p] = e;
		++H.count;
		return OK;
	}
	else
	{
		//ʧ��
		return UNSUCCESS;
	}

}
//����
Status CreateHashTable(HashTable &H)
{

	int num,len=11,i=0;
	ElemType e;
	H.count=0;//��Ŀ�趨
	H.sizeindex=11;//��Ŀ�趨
	H.elem=(ElemType *)malloc(sizeof(ElemType));
	for(;i<len*2;i++)
		H.elem[i].key=NULLKEY;
	while((--len)>=0)
	{
		scanf("%d",&num);
		e.key = num;

		InsertHash(H,e);
	}


	return OK;
}
//��ʾ��ϣ��
void ShowHashTable(HashTable H)
{
	printf("��ʾ��ϣ��\n");
	int i=0;
	for(;i<H.count;i++)
	{
		printf("%d ",H.elem[i]);
	}
	printf("\n");
}

int main()	
{
	int num,p,c;
	HashTable H;
	printf("�������ϣ������ int\n");
	CreateHashTable(H);


	printf("������ϣ�����ҵĹ�ϣ������ int\n");
	scanf("%d",&num);
	//SearchHash(HashTable H,KeyType k,int &p,int &c)
		printf("���ҽ��: %s \n",(SearchHash(H,num,p,c)==OK?"����":"������"));
	return 0;
}