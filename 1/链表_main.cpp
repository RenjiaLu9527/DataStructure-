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
	ElemType elem;//数据域
	struct LNode * next;//指针域

}LNode,*LinkList;

/************************************************************************
								链表



************************************************************************/
//初始化
void InitLinkList(LinkList &L)//？？指针定义 &引用
{
	L = (LNode *)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);//创建失败 退出

	L->next = NULL;
}
//创建
void CreateLinkList(LinkList &L,int n)
{
	//逆序 n个节点
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
//显示
void DisplayLinkList(LinkList L)
{
	LNode * p;
	for(p = L->next;p;p=p->next)
		printf("%8s %8s %8s\n",p->elem.name,p->elem.id,p->elem.job);

}

//按序号查找
LNode * GetElem_L(LinkList L,int i)
{
	//i 为第i个节点，从1 开始计数
	LNode * p;
	int j=1;//
	p = L->next;
	if(i==0) return L;

	while(p && j<i){p = p->next; j++;}

	if(j == i) return p;//第 i 个元素存在，并返回
	else return NULL;//不存在

}
//按值查找
int locateelem(LinkList L,ElemType x)
{
	LNode * p;
	int i=1;
	p=L->next;//第一个节点(头节点不算)
	int compareElem(ElemType e1,ElemType x);//函数声明

	while(p && (compareElem(p->elem,x)!=1)) {++i,p=p->next;}

	if(p!=NULL) return i;
	else return 0;

}
//插入
int LinkListInsert_L(LinkList &L,int i,ElemType x)
{
	void copyElem(ElemType &s,ElemType &x);//声明函数
	LNode * p,* s;
	p = GetElem_L(L,i);//第 i 个元素之后插入新元素p
	if(!p) return ERROR;

	s = (LNode *)malloc(sizeof(LNode));
	if(!s) return ERROR;

	copyElem(s->elem,x);//复制data

	s->next = p->next;
	p->next = s;
	return OK;

}
//删除
int LinkListDelete_L(LinkList &L,int i)
{
	//i 为 第几个 节点 的意思
	LNode *p,*q;
	p = GetElem_L(L,i-1);//取出待删除前一个节点

	if(!p) return ERROR;//删除位置不合理

	q = p->next;
	p->next = q->next;//

	free(q);
	return OK;
	 
}
//删除链表数据
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
		return OK;//相同

	}else
	{
		return ERROR;//不同
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
	printf("--请输入要创建顺序表长度: ");
	scanf("%d",&len);
	printf("--请依次输入员工的 \n姓名  工号  职务\n");
	CreateLinkList(L,len);

	printf("--显示所有员工信息如下\n姓名  工号  职务\n");
	DisplayLinkList(L);

	while(true)
	{
		printf("\n\n***********************************\n--菜单--\n--· 1 插入员工信息\n--· 2 删除员工信息\n--· 3 显示所有员工信息\n--· 4 销毁所有员工数据\n***********************************\n请选择: ");
		scanf("%d",&choose);
		switch(choose){
		case 1:{
			printf("--请依次输入员工的\n姓名   工号   职务\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			printf(LinkListInsert_L(L,1,insert)==1?"--存入成功\n":"--存入失败 001\n");// 
			break;
		}
		case 2:{
			printf("--请输入需要删除员工的\n姓名   工号   职务\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			int index = locateelem(L,insert);
			if(index>0)//第一个元素位置为 1
			{
				printf("\n成功查询到员工信息--位置:%2d\n",index);
				i =	LinkListDelete_L(L,index);//删除第 i 个节点
				printf("%-16s\n",(i == 1?"\n删除成功\n":"\n删除失败 请检查位置脚标是否合理\n"));
			}else
			{
				printf("\n未查询到员工信息--位置:%2d\n",index);
			}
			break;
			   }
		case 3:{
			printf("\n员工信息如下\n******************************************************\n");
				DisplayLinkList(L);
				printf("\n******************************************************\n");
				break;
			   }
		case 4:{
				
			    ClearLinkList(L);
				printf("\n******************数据销毁 程序结束*******************\n");
				exit(OVERFLOW);
			   }
		default:printf("\n请输入正确的选项: ");

		}
 
			printf("#####按任意键继续..#####");
			getchar();
			getchar();
			printf("\n-------------------我是分割线---------------------------\n");
			printf("-------------------分割线我是---------------------------\n");
			printf("-------------------分割线是我---------------------------\n");
	}

	return 0;
}