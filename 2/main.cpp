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


//�ÿ�ջ ��ʼ��
void InitStack(LinkStack &top)
{
	top = NULL;
}
//��ջ��
int StackEmpty(LinkStack top)
{
	if(top == NULL) return OK;
	else return ERROR;
}
//��ջ
int Push(LinkStack &top,ElemType x)
{
	StackNode *s;//LinkStack s;������?????
	s = (StackNode *)malloc(sizeof(StackNode));

	if(!s) exit(OVERFLOW);

	s->data = x;
	s->next=top;
	top = s;

	return OK;
}
//��ջ
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
	int state = 1;// 0-���ֵ��� )]ʱ�˳�����  1-
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
				Push(s,exp[i]);//��ջ
				i++;
				break;
			}
		case ')':
			{
				if(!StackEmpty(s) && GetTop(s) == '(')
				{
					Pop(s,e);//��ջ
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
					Pop(s,e);//��ջ
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
					Pop(s,e);//��ջ
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
 

	StackNode *top;//ջ��ָ��
	InitStack(top);

	printf("������ �����ַ���\n");
	scanf("%s",num);

	if(OK == matching(num,top))
	{
		printf("\n--������ķ���ƥ�� �ɹ�\n");
	}else
	{
		printf("\n--������ķ���ƥ�� ʧ��\n");
	}

	

	return 0;
}