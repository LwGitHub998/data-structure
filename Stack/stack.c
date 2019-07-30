#include <stdio.h>
#include <windows.h>
#include <assert.h>
//顺序栈
#define MAXSIZE 10
typedef int SDataType;
typedef struct Stack
{
	SDataType array[MAXSIZE];
	int Top;
}Stack, *pStack;
enum revpol
{
	CH,
	NUM
};
typedef struct RevPol
{
	enum revpol type; //字符类型
	int data;//数据
}RevPol;
//初始化
void StackInit(pStack pstack)
{
	assert(pstack);
	pstack->Top = 0;
}
//压栈
void StackPush(pStack pstack, SDataType d)
{
	assert(pstack);
	if (MAXSIZE == pstack->Top)
	{
		return;
	}
	pstack->array[pstack->Top] = d;
	pstack->Top++;
}
//出栈
void StackPop(pStack pstack)
{
	assert(pstack);
	if (0 == pstack->Top)
	{
		return;
	}
	pstack->Top--;
}
//求有效元素个数
int StackSize(pStack pstack)
{
	assert(pstack);
	return pstack->Top;
}
//栈是否为空
int StackEmpty(pStack pstack)
{
	assert(pstack);
	return pstack->Top == 0;
}
//查看栈顶元素
int StackTop(pStack pstack)
{
	assert(pstack);
	if (0 == pstack->Top)
	{
		return -1;
	}
	return pstack->array[pstack->Top - 1];
}

//栈的应用

//括号匹配问题
//是不是括号
char IsItBrackets(char* str)
{
	if ('{' == *str || '(' == *str || '[' == *str)
	{
		return 'L';
	}
	if ('}' == *str || ')' == *str || ']' == *str)
	{
		return 'R';
	}
	return 'O';
}
//左右括号匹配
char RLBracketMatching(int top, char* str)
{
	if (('{' == top && '}' == *str) ||
		('(' == top && ')' == *str) ||
		('[' == top && ']' == *str))//匹配
	{
		return 'Y';
	}
	return 'N';
}
//判断函数
void MatchBrackets(pStack pstack, const char* str)
{
	char* cur = (char*)str;
	while (*cur != '\0')
	{
		if ('L' == IsItBrackets(cur))//左括号
		{
			StackPush(pstack,*cur);//压栈
		}
		else if ('R' == IsItBrackets(cur)) //右括号
		{
			int ret = StackEmpty(pstack);//栈是否为空
			if (ret == 1)
			{
				printf("右括号多于左括号\n");
				break;
			}
			int ret1 = StackTop(pstack);//查看栈顶元素
			char ch = RLBracketMatching(ret1, cur);
			if ('Y' == ch)//匹配
			{
				StackPop(pstack);//出栈
			}
			else//不匹配
			{
				printf("括号匹配次序不正确\n");
				//把栈变为空
				StackInit(pstack);
				break;
			}
		}
		cur++;
	}
	if (*cur == '\0')
	{
		if (StackEmpty(pstack))
		{
			printf("括号匹配正确\n");
		}
		else
		{
			printf("左括号多于右括号\n");
			//把栈变为空
			StackInit(pstack);
		}
	}
}

//逆波兰表达式
int RevPolNotation(pStack pstack, RevPol arr[])
{
	int i = 0;
	for (i = 0; i < 11; i++)
	{
		if (NUM == (arr + i)->type)//数字
		{
			StackPush(pstack, (arr + i)->data);
		}
		else if (CH == (arr + i)->type)//操作符
		{
			int numN = 0;//结果
			int numR = StackTop(pstack);//查看栈顶元素
			StackPop(pstack);//出栈
			int numL = StackTop(pstack);//查看栈顶元素
			StackPop(pstack);//出栈
			switch ((arr + i)->data)
			{
			case '+':
			{
						numN = numL + numR;
						StackPush(pstack, numN);
			}
				break;
			case '-':
			{
						numN = numL - numR;
						StackPush(pstack, numN);
			}
				break;
			case '*':
			{
						numN = numL * numR;
						StackPush(pstack, numN);
			}
				break;
			case '/':
			{
						numN = numL / numR;
						StackPush(pstack, numN);
			}
				break;
			}
		}
	}
	return StackTop(pstack);
	
}
