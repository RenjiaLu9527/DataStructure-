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
	ElemType * elem;//线性表 数基地址
	int length;
	int listsize;

}SqList;

/************************************************************************
	顺序表



************************************************************************/
//初始化
void InitSqList(SqList &L)
{
	L.elem = (ElemType *)malloc(sizeof(ElemType)*List_Size);
	if(!L.elem)exit(OVERFLOW);//如果 为空,就输出overflow结束函数
	L.length = 0;
	L.listsize = List_Size;
}
//创建
void CreateSqList(SqList &L,int n)
{
	//创建 n 个元素的顺序表
	int i=0;
	for(i=0;i<n;i++)
	{
		scanf("%s %s %s",L.elem[i].name,L.elem[i].id,L.elem[i].job);//name id job
		L.length++;
	}
}
//***************************插入********************************
int SqListInsert(SqList &L,int i,ElemType x)
{
	int j;
	ElemType *p;
	if(i < 1 || i > L.length) return ERROR;

	if(L.length >= L.listsize)//储存空间已满--增加空间
	{
		//原先的内存大小后面没有足够的空闲空间用来分配，那么从堆中另外找一块newsize大小的内存,并把原来大小内存空间中的内容复制到newsize中
		p = (ElemType *)realloc(L.elem,sizeof(ElemType)*(L.listsize + ListIncrement));
		if(!p) exit(OVERFLOW);
		L.elem = p;
		L.listsize += ListIncrement;
	}

	for(j = L.length-1;j>=i-1;j--)L.elem[j+1] = L.elem[j];//元素依次后移一位

	L.elem[i-1] = x;//插入
	L.length++;//长度增加 
	return OK;//插入成功
}
//***************************删除*******************************
int SqListDelete(SqList &L,int i)
{
	int j;
	if(i<1 || i>L.length) return ERROR;

	for(j=i-1;j<L.length-1;j++) L.elem[j] = L.elem[j+1];//元素依次前移一位

	L.length--;
	return OK;
}
//显示
void DisplaySqList(SqList &L)
{
	int i;
	for(i=0;i<L.length;i++)
	{
		printf("--姓名:%8s --工号:%8s --职务:%8s .\n",L.elem[i].name,L.elem[i].id,L.elem[i].job);
	
	}
}
//查找
int LocatedElem(SqList L,ElemType x)
{
	int compare(ElemType e1,ElemType x);//声明函数
	int i=1;//strcmp(s1,s2) 当s1=s2时，返回值=0
	while(i<=L.length && compare(L.elem[i-1],x)!=1) i++;
	
	if(i<=L.length)
		return i;
	else 
		return ERROR;


}
//销毁
void DestorySqList(SqList &L)
{
	free(L.elem);//释放内存
}

/************************************************************************
                         顺序表 主函数



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
	printf("--顺序表 请输入要创建顺序表长度: ");
	scanf("%d",&len);
	printf("--请依次输入员工的 \n姓名  工号  职务\n");
	CreateSqList(L,len);

	printf("--显示所有员工信息如下\n姓名  工号  职务\n");
	DisplaySqList(L);

	while(true)
	{
		printf("\n\n***********************************\n--菜单--\n--· 1 插入员工信息\n--· 2 删除员工信息\n--· 3 显示所有员工信息\n--· 4 销毁所有员工数据\n***********************************\n请选择: ");
		scanf("%d",&choose);
		switch(choose){
		case 1:{
			printf("--请依次输入员工的\n姓名   工号   职务\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			printf(SqListInsert(L,L.length,insert)==1?"--存入成功\n":"--存入失败 001\n");//每次插入到最后的前面，为倒数第二
			break;
		}
		case 2:{
			printf("--请输入需要删除员工的\n姓名   工号   职务\n");
			scanf("%s %s %s",insert.name,insert.id,insert.job);//name id job
			i = LocatedElem(L,insert);
			if(i>0 && i<L.length+1)//第一个元素位置为 1
			{
				printf("\n成功查询到员工信息 -- 位置: %02d \n",i);
				i =	SqListDelete(L,i);
				printf("%-16s\n",(i == 1?"\n删除成功\n":"\n删除失败 请检查位置脚标是否合理\n"));
			}else
			{
				printf("\n未查询到员工信息 -- 位置: %02d \n",i);
			}
			break;
			   }
		case 3:{
			printf("\n员工信息如下\n******************************************************\n");
				DisplaySqList(L);
				printf("\n******************************************************\n");
				break;
			   }
		case 4:{
				
			    DestorySqList(L);
				printf("\n******************数据销毁 程序结束*******************\n");
				exit(OVERFLOW);
			   }
		default:printf("\n请输入正确的选项: ");

		}
 
			printf("\n#####按任意键继续..#####");
			getchar();
			getchar();
			printf("\n-------------------我是分割线---------------------------\n");
			printf("-------------------分割线我是---------------------------\n");
			printf("-------------------分割线是我---------------------------\n");
	}

	return 0;
}