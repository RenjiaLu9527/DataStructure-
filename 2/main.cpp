#include<stdio.h>
#include<stdlib.h>
#include<String.h>

#define ElemType char
 

#define OVERFLOW 0 
#define ERROR 0
#define OK 1

 
typedef struct node{
	ElemType data;
	struct node * next;
}StackNode,*LinkStack;


//置空栈 初始化
void InitStack(LinkStack &top)
{
	top = NULL;
}
//判栈空
int StackEmpty(LinkStack top)
{
	if(top == NULL) return OK;
	else return ERROR;
}
//入栈
int Push(LinkStack &top,ElemType x)
{
	StackNode *s;//LinkStack s;的区别?????
	s = (StackNode *)malloc(sizeof(StackNode));

	if(!s) exit(OVERFLOW);

	s->data = x;
	s->next=top;
	top = s;

	return OK;
}
//出栈
int Pop(LinkStack &top,ElemType &x)
{	
	StackNode *p;
	if(top == NULL) return ERROR;
	else 
	{
		x = top->data;
		p = top;
		top = top->next;

		free(p);
		return OK;
	}
}
//`
ElemType GetTop(LinkStack s)
{	
   

	if(s)
		return s->data;
	return ERROR;
}
//
int matching(char exp[],LinkStack &s)
{
	int state = 1;// 0-出现单个 )]时退出函数  1-
	int i=0;
	char e;

	//LinkStack ps = &s;
	while(i < int(strlen(exp)) && state)
	{
		switch(exp[i])
		{
		case '[':{}
		case '{':{}
		case '(':
			{
				Push(s,exp[i]);//入栈
				i++;
				break;
			}
		case ')':
			{
				if(!StackEmpty(s) && GetTop(s) == '(')
				{
					Pop(s,e);//出栈
					i++;
				}else
				{
					state = 0;
				}
				break;
			}
		case '}':
			{
				if(!StackEmpty(s) && GetTop(s) == '{')
				{
					Pop(s,e);//出栈
					i++;
				}else
				{
					state = 0;
				}
				break;
			}
		case ']':
			{
				if(!StackEmpty(s) && GetTop(s) == '[')
				{
					Pop(s,e);//出栈
					i++;
				}else
				{
					state = 0;
				}
				break;
			}
		}
	}

	if(state && StackEmpty(s))
		return OK;
	return ERROR;
}
///////////////////////////MAIN FUNCTION/////////////////////////////
int main()
{
	char num[1024];
 

	StackNode *top;//栈顶指针
	InitStack(top);

	printf("请输入 待测字符串\n");
	scanf("%s",num);

	if(OK == matching(num,top))
	{
		printf("\n--您输入的符号匹配 成功\n");
	}else
	{
		printf("\n--您输入的符号匹配 失败\n");
	}

	

	return 0;
}