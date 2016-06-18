#include<stdio.h>
#include<stdlib.h>
//宏定义（对两个关键字的比较约定）


/*
*   线性探测再散列    
*   di = cxi  =1,2,3,…m-1 最简单的情况c=1

*/
//对数值型关键字
#define   EQ(a,b)    ((a)== (b))
#define   LT(a,b)    ((a)<(b))
#define   LQ(a,b)    ((a)<=(b))
//对字符串型关键字(参见课本71页定义)
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
	int modnum = 11;//可调
	return (k%modnum);
}
void collision(int &p,int c)
{
	int i=1;//增量，可调节
	p = (c * i);//?>?>?> 不取余溢出？
}
//查询///////////////////////////////
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


//插入////////////////////////////
Status InsertHash(HashTable &H,ElemType e)
{
	int c,p,CLLSN;
	c=0;
	CLLSN=H.sizeindex;
	if(SearchHash(H,e.key,p,c))
	{
		return DUOLICATE;//冲突发生
	}
	else if(c < CLLSN)//冲突上限
	{
		H.elem[p] = e;
		++H.count;
		return OK;
	}
	else
	{
		//失败
		return UNSUCCESS;
	}

}
//创建
Status CreateHashTable(HashTable &H)
{

	int num,len=11,i=0;
	ElemType e;
	H.count=0;//题目设定
	H.sizeindex=11;//题目设定
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
//显示哈希表
void ShowHashTable(HashTable H)
{
	printf("显示哈希表\n");
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
	printf("请输入哈希表数据 int\n");
	CreateHashTable(H);


	printf("请输入希望查找的哈希表数据 int\n");
	scanf("%d",&num);
	//SearchHash(HashTable H,KeyType k,int &p,int &c)
		printf("查找结果: %s \n",(SearchHash(H,num,p,c)==OK?"存在":"不存在"));
	return 0;
}