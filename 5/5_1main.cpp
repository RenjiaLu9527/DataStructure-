#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//�궨�壨�������ؼ��ֵıȽ�Լ����
//����ֵ�͹ؼ���
#define   EQ(a,b)    ((a)== (b))
#define   LT(a,b)    ((a)<(b))
#define   LQ(a,b)    ((a)<=(b))
//���ַ����͹ؼ���(�μ��α�71ҳ����)
//#define   EQ(a,b)  (! strcmp((a) , (b)))
//#define   LT(a,b)  (strcmp((a) , (b)) < 0)
//#define   LQ(a,b)  (strcmp((a) , (b)) <= 0)


#ifndef Status


#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW 0
typedef int KeyType;
//typedef int TElemType;
typedef int Status;
#endif

typedef struct TElemType //���ݽṹ
{
	KeyType key;//��ֵ
}TElemType;

// ���ṹ
typedef struct BiTNode{
    struct BiTNode  *lchild, *rchild;	// ���Һ���ָ�� 
	TElemType data;//����
} BiTNode, *BiTree;


Status SearchBST (BiTree T, KeyType key,BiTree f, BiTree &p ) 
{
           // �ڸ�ָ�� T ��ָ�����������еݹ�ز�����
            // �ؼ��ֵ��� key ������Ԫ�أ������ҳɹ���
           // �򷵻�ָ�� p ��ָ������Ԫ�صĽ�㣬������
            // ����ֵΪ TRUE; 	
	if (!T)
	{ 
		p = f;  return FALSE; 
	}  // ���Ҳ��ɹ�
	else if (EQ(key, T->data.key) )
    {
		p = T;  return OK; 
	}  // ���ҳɹ�
	else  if ( LT(key, T->data.key) )
		SearchBST (T->lchild, key, T, p );  
                              // ���������м�������
	else
		SearchBST (T->rchild, key, T, p ); 
                             // ���������м�������
	return FALSE;
} // SearchBST


//���� ����������
Status InsertBST(BiTree &T, TElemType e) 
{            // �������������в����ڹؼ��ֵ��� e.key ��
             // ����Ԫ��ʱ������Ԫ��ֵΪ e �Ľ�㣬����
             // �� TRUE; ���򣬲����в��벢����FALSE
	 
	BiTree p,s;
    if (!SearchBST(T,e.key,NULL,p))
    {
	    s = (BiTree) malloc (sizeof (BiTNode));                             // Ϊ�½�����ռ�
	    s->data = e;  
	    s->lchild = s->rchild = NULL;  
	    if  ( !p )  T = s;            // ���� s Ϊ�µĸ����
	
	    else if( LT(e.key, p->data.key))
		   p->lchild = s;          // ���� *s Ϊ *p ������
	    else  
		   p->rchild = s;     // ���� *s Ϊ *p ���Һ���
	    return OK;           // ����ɹ�
    }
    else 
	   return FALSE;
} // Insert BST


//������� [�ݹ�]
void InOrderTraverse(BiTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);//����
		printf("%d ",T->data);//���ʵ�ǰ�ڵ�
		InOrderTraverse(T->rchild);//�Һ���
	}
} 
//������� end

int main()
{
	int i,rsult=0;

	TElemType num;
	BiTree T = NULL;// = (BiTree) malloc (sizeof (BiTNode));                
	
	printf("��������������\n");
	scanf("%d",&i);
	printf("������ [һ������] ����һ�ö���������(�ո�ֿ�,#����)\n");

	
	for(;i>0;i--)
	{	
		scanf("%d",&num.key);
	
		rsult = InsertBST(T,num); 
		printf("#������������� ��%s��\n",rsult==OK?"�ɹ�":"ʧ��");
		//����һ���� ����һ��
	}
	//�������
	printf("\n�������\n");
	InOrderTraverse(T);

	printf("\n�������\n");
	free(T);
	return 0;
}