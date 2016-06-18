#include "stdio.h"
#include "stdlib.h"
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef char TElemType;
typedef int Status;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

 
Status CreateBiTree(BiTree &T){//创建二叉树
	char ch;
	scanf("%c",&ch);
	if(ch=='#')
		T=NULL;
	else{
		if(!(T=(BiTree)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

void visit(TElemType c){//访问节点
	printf("%c\n",c);
}

void Preorder(BiTree T){//先序遍历
	if(T){
		visit(T->data);
		Preorder(T->lchild);
		Preorder(T->rchild);
	}
}

void Inorder(BiTree T){//中序遍历
	if(T){
		Inorder(T->lchild);
		visit(T->data);
		Inorder(T->rchild);
	}
}

void Postorder(BiTree T){//后序遍历
	if(T){
		Postorder(T->lchild);
		Postorder(T->rchild);
		visit(T->data);
	}
}
 


typedef struct{
	BiTNode stack[MAXSIZE];  
	int  top;
}Stack;

void Initstack(Stack* &s){
	s->top=-1;
}

Status Push(Stack* &s, BiTree x){
	if (s->top>=MAXSIZE-1)
		return ERROR;       //栈满，上溢
    else{
		s->top++;
        s->stack[s->top]=*x;
        return OK;
	}
}

BiTree Pop(Stack* &s)
{ 
	if (s->top<0)
		return ERROR;       //栈空，下溢
	else 
		s->top--;
	return &s->stack[s->top+1];
}  

Status StackEmpty(Stack* s){
	if (s->top<0)
		return 1;
    else
		return 0;
} 

BiTNode* GoFarLeft(BiTree T, Stack *S){
	if(!T)return NULL;
    while (T->lchild ){//找到最左下的结点
		Push(S, T);
		T = T->lchild;
	}
	return T;
}

void Inorder_I(BiTree T, void (*visit)(TElemType& e)){// 中序遍历二叉树的非递归算法
	Stack *S;
	Initstack(S);
    BiTree t = GoFarLeft(T, S);            // 找到最左下的结点
	while(t){
		visit(t->data);
		if (t->rchild)
			t = GoFarLeft(t->rchild, S);
		else if ( !StackEmpty(S))    // 栈不空时退栈
			t = Pop(S);
		else  
			t = NULL;        // 栈空表明遍历结束
    }
}

void translevel(BiTree b)           //按层次遍历
  {  struct node
         { BiTree vec[MAXSIZE];
           int f,r; 
        } q;
      q.f=0;
      q.r=0;
	  if (b!=NULL) printf("%d",b->data);
     q.vec[q.r]=b;                        //结点指针进入队列
     q.r=q.r+1;
	 while (q.f<q.r)               //队列不为空
	 { b=q.vec[q.f];   q.f=q.f+1;   //队头出队列
     if (b->lchild!=NULL)       //输出左孩子，并入队列
       {  printf("%d",b->lchild->data); 
           q.vec[q.r]=b->lchild;
           q.r=q.r+1;
       }
	 if  (b->rchild!=NULL)      //输出右孩子，并入队列
       { printf("%d",b->rchild->data);
          q.vec[q.r]=b->rchild;
          q.r=q.r+1;
       }//if
   }//while
}

void CountLeaf(BiTree T,int &count){//求叶子结点数
	if(T){
		if((!T->lchild)&&(!T->rchild))
			count++;
		CountLeaf(T->lchild,count);
		CountLeaf(T->rchild,count);
	}
}

int Depth(BiTree T ){//求二叉树的深度
	int depthval,depthLeft,depthRight;
	if(!T) depthval=0;
	else{
		depthLeft = Depth(T->lchild);
		depthRight = Depth(T->rchild);
		if(depthLeft>depthRight)
			depthval = 1+depthLeft;
		else 
			depthval = 1+depthRight;
	}
	return depthval;
}








/////////////////树

typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

//队列存储结构及操作
typedef struct QNode 
{
	CSTree data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct 
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
//构造空队列
Status InitQueue(LinkQueue &Q) 
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
//销毁队列
Status DestoryQueue(LinkQueue &Q) 
{
	while (Q.front) 
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}
//入队列
Status EnQueue(LinkQueue &Q, CSTree e) 
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) 
		exit(OVERFLOW);
	p->data = e; p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK; 
}
//出队列
Status DeQueue(LinkQueue &Q, CSTree &e) 
{
	QueuePtr p;
	if (Q.front == Q.rear) 
		return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) 
		Q.rear = Q.front;
	free(p);
	return OK;
}
//读队头
Status GetHead(LinkQueue &Q, CSTree &e) 
{
	QueuePtr p;
	if (Q.front == Q.rear) 
		return ERROR;
	p = Q.front->next;
	e = p->data;
	return OK;
}
//建立树的孩子，兄弟链表结点
CSTree GetTreeNode(TElemType e) 
{
	CSTree p;
	p = (CSTree)malloc(sizeof(CSNode));
	if (!p) 
		exit(OVERFLOW);
	p->data = e;
	p->firstchild = NULL;
	p->nextsibling = NULL;
	return p;
}
 //建立树的孩子，兄弟链表
Status CreatTree(CSTree &T) 
{
	char first = ' ', second = ' ';
	int result = 0;
	LinkQueue Q;
	CSTree p, s, r;
	InitQueue(Q);
	T = NULL;
	for(scanf("%c%c", &first, &second);
	second != '#';
	result = scanf("%c%c", &first, &second)) 
	{
		p = GetTreeNode(second);
		EnQueue(Q, p);
		if (first == '#') 
			T = p;
		else
		{
			GetHead(Q,s);
			while (s->data != first)
			{
				DeQueue(Q,s);
				GetHead(Q,s);
			}
			if (!(s->firstchild)) 
			{
				s->firstchild = p;
				r = p;
			}
			else
			{
				r->nextsibling = p;
				r =p;
			}
		}
	}
	return OK;
}
 //求树的深度
int TreeDepth(CSTree T) 
{
	int h1, h2;
	if (!T)
		return 0;
	else
	{
		h1 = TreeDepth(T->firstchild);
		h2 = TreeDepth(T->nextsibling);
		return(((h1+1)>h2)?(h1+1):h2);
	}
}

void main(){
	BiTree T;
	int s=0,d;
/*	printf("\n 输入二叉树的节点:\n"); 
	CreateBiTree(T);
	printf("\n 先序遍历结果:\n"); 
	Preorder(T); 
	printf("\n");
 
	printf("\n 中序遍历结果:\n"); 
	Inorder(T);
	printf("\n");
 
	printf("\n 后序遍历结果:\n"); 
	Postorder(T);
	printf("\n");
 */

//树的深度
	CountLeaf(T,s);
	d=Depth(T);
	printf("\n 树的深度=%d\n",d);
	while (getchar() != '\n'); 
	CSTree T2;
	printf("输入树的节点：");
	CreatTree(T2);
	printf("\n");
	printf("树的深度:");
	printf("%d", TreeDepth(T2));
	printf("\n");
}