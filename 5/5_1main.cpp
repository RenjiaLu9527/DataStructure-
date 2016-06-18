#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//宏定义（对两个关键字的比较约定）
//对数值型关键字
#define   EQ(a,b)    ((a)== (b))
#define   LT(a,b)    ((a)<(b))
#define   LQ(a,b)    ((a)<=(b))
//对字符串型关键字(参见课本71页定义)
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

typedef struct TElemType //数据结构
{
	KeyType key;//键值
}TElemType;

// 结点结构
typedef struct BiTNode{
    struct BiTNode  *lchild, *rchild;	// 左右孩子指针 
	TElemType data;//数据
} BiTNode, *BiTree;


Status SearchBST (BiTree T, KeyType key,BiTree f, BiTree &p ) 
{
           // 在根指针 T 所指二叉排序树中递归地查找其
            // 关键字等于 key 的数据元素，若查找成功，
           // 则返回指针 p 所指该数据元素的结点，并返回
            // 函数值为 TRUE; 	
	if (!T)
	{ 
		p = f;  return FALSE; 
	}  // 查找不成功
	else if (EQ(key, T->data.key) )
    {
		p = T;  return OK; 
	}  // 查找成功
	else  if ( LT(key, T->data.key) )
		SearchBST (T->lchild, key, T, p );  
                              // 在左子树中继续查找
	else
		SearchBST (T->rchild, key, T, p ); 
                             // 在右子树中继续查找
	return FALSE;
} // SearchBST


//插入 二叉排序树
Status InsertBST(BiTree &T, TElemType e) 
{            // 当二叉排序树中不存在关键字等于 e.key 的
             // 数据元素时，插入元素值为 e 的结点，并返
             // 回 TRUE; 否则，不进行插入并返回FALSE
	 
	BiTree p,s;
    if (!SearchBST(T,e.key,NULL,p))
    {
	    s = (BiTree) malloc (sizeof (BiTNode));                             // 为新结点分配空间
	    s->data = e;  
	    s->lchild = s->rchild = NULL;  
	    if  ( !p )  T = s;            // 插入 s 为新的根结点
	
	    else if( LT(e.key, p->data.key))
		   p->lchild = s;          // 插入 *s 为 *p 的左孩子
	    else  
		   p->rchild = s;     // 插入 *s 为 *p 的右孩子
	    return OK;           // 插入成功
    }
    else 
	   return FALSE;
} // Insert BST


//中序遍历 [递归]
void InOrderTraverse(BiTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);//左孩子
		printf("%d ",T->data);//访问当前节点
		InOrderTraverse(T->rchild);//右孩子
	}
} 
//中序遍历 end

int main()
{
	int i,rsult=0;

	TElemType num;
	BiTree T = NULL;// = (BiTree) malloc (sizeof (BiTNode));                
	
	printf("请输入数据总数\n");
	scanf("%d",&i);
	printf("请输入 [一串整数] 构成一棵二叉排序树(空格分开,#结束)\n");

	
	for(;i>0;i--)
	{	
		scanf("%d",&num.key);
	
		rsult = InsertBST(T,num); 
		printf("#插入二叉排序树 【%s】\n",rsult==OK?"成功":"失败");
		//输入一个数 插入一个
	}
	//中序遍历
	printf("\n中序遍历\n");
	InOrderTraverse(T);

	printf("\n程序结束\n");
	free(T);
	return 0;
}