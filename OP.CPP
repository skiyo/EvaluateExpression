#define OPNUM 8
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "OP.h"
char c[50];  //存储输入的字符串
//--------------------以下为栈的操作-----------------------//
//--------------------运算数栈-----------------------//
//初始化栈
SeqStack *Init_SeqStack()
{
	SeqStack *s;
	s = (SeqStack *)malloc(sizeof(SeqStack));
    s->top = -1; 
	return s;
}
//判断空栈
int Empty_SeqStack(SeqStack *s)
{
   if (s->top==-1)
   return 1;
   else  return 0;
}  
//入栈
int Push_SeqStack (SeqStack *s,datatype x)
{
    if (s->top==MAXSIZE-1) return 0;
    else 
	{
		s->top++;
        s->data[s->top]=x;
		return 1;
	}
}
//出栈
int Pop_SeqStack(SeqStack *s,datatype *x)
{
    if (Empty_SeqStack(s))  return 0;
    else 
	{
		*x=s->data[s->top];
		s->top--;
		return 1;
	}
}
//取栈顶元素
datatype GetTop(SeqStack *s)
{
    if (Empty_SeqStack(s))  
		return 0;
    else
		return (s->data[s->top]);
}
//--------------------运算符栈-----------------------//
//初始化栈
charStack *Init_charStack()
{
	charStack *s;
	s = (charStack *)malloc(sizeof(charStack));
    s->top = -1; 
	return s;
}
//判断空栈
int Empty_charStack(charStack *s)
{
   if (s->top==-1)
   return 1;
   else  return 0;
}  
//入栈
int Push_charStack (charStack *s,char x)
{
    if (s->top==MAXSIZE-1) return 0;
    else 
	{
		s->top++;
        s->data[s->top]=x;
		return 1;
	}
}
//出栈
int Pop_charStack(charStack *s,char *x)
{
    if (Empty_charStack(s))  return 0;
    else 
	{
		*x=s->data[s->top];
		s->top--;
		return 1;
	}
}
//取栈顶元素
char GetcharTop(charStack *s)
{
    if (Empty_charStack(s))  
		return 0;
    else
		return (s->data[s->top]);
}

//----------------定义运算符数组-----------------//

OP OPPree[OPNUM] = 
{
	{'+',3,2},
	{'-',3,2},
	{'*',5,4},
	{'/',5,4},
	{'^',7,6},
	{'(',1,8},
	{')',0,1},
	{'#',-1,-1}
};
//-----------------判断是否为运算符-------------------//
int In(char x)
{
	int i;
	for(i=0;i<=OPNUM;i++)  //搜索数组中内容
	{
		if (x==OPPree[i].OPname) return 1;  //是运算符返回1
	}
	return 0;  //不是运算符返回0
}

//-----------------判断优先级------------------------//
char Precede(char x,char c)
{
	int i,inlev;
	for(i=0;i<=OPNUM;i++)
	{
		if (x==OPPree[i].OPname) 
			break;
	}                                 //搜索 x 的下标
	inlev = OPPree[i].inOP;
	for(i=0;i<=OPNUM;i++)
	{
		if (c==OPPree[i].OPname) break;
	}  //搜索 c 的下标
	if (inlev < OPPree[i].outOP) return '<';  //比较 x 的栈内级别和 c 的栈外级别
	else if (inlev > OPPree[i].outOP) return '>';
	else return '=';
}

//-------------------计算函数-------------------------//
int Operate(int a,char x,int b)
{
	switch (x)
	{
		case '+' : return (a+b);break;
		case '-' : return (a-b);break;
		case '*' : return (a*b);break;
		case '/' :
				if (b==0) return ERROR;
				return (a/b);
				break;
		case '^' : return ((int)pow(a,b));break;
		default : return ERROR;
	}
}

//-----------------中缀表达式运算实现函数----------------------//
int EvaluateExpression()
{
	int i=0;
	datatype a,b;
	char x,theta;
	charStack *OPTR;
    SeqStack *OPND;
	OPTR = Init_charStack();  //运算符栈
	Push_charStack(OPTR, '#');
	OPND = Init_SeqStack();  //运算数栈
	while(c[i] != '\0')
	{
		if (!In(c[i]))  //如果不是运算符
		{
			Push_SeqStack(OPND,c[i]-'0');  //入运算数栈
			i++;
		}
		else
			switch(Precede(GetcharTop(OPTR),c[i]))  //如果是运算符,取栈顶元素的栈内级别跟栈外元素的栈外级别比较
		{
			case '<' :
					Push_charStack(OPTR,c[i]);  //小于则入符号栈
					i++;
					break;
			case '=' :
					Pop_charStack(OPTR,&x);  //等于则出栈
					i++;
					break;
			case '>' :
					Pop_charStack(OPTR, &theta);
					Pop_SeqStack(OPND,&b);
					Pop_SeqStack(OPND,&a);  //两个运算数跟一个运算符出栈,进行运算
					Push_SeqStack(OPND,Operate(a,char(theta),b));
					break;
		}
	}
	return GetTop(OPND);
}

//-----------------中缀表达式转换后缀表达式----------------------//
void change(char a[],char s[])
{
	int i=0,j=0;
	char temp;
	charStack *OPTR;
	OPTR = Init_charStack();
	Push_charStack(OPTR, '#');
	while(a[i]!='\0')
	{
		if (!In(a[i]))  //如果不是运算符
		{
			s[j]=a[i];
			j++;
			i++;  //直接输入到后缀表达式
			continue;
		}
		else
			switch(Precede(GetcharTop(OPTR),a[i]))
		{
			case '<' :
					Push_charStack(OPTR,a[i]);  //当栈内级别小于栈外级别的时候入栈
					i++;
					break;
			case '>' :
					while(Precede(GetcharTop(OPTR),a[i])=='>')  //当栈顶元素大于栈外元素
					{
						Pop_charStack(OPTR, &temp);  //栈顶元素出栈
						s[j]=temp;
						j++;
						temp=GetcharTop(OPTR);  //取栈顶元素继续比较
					}
					break;
			case '=':
					Pop_charStack(OPTR, &temp); //等于就出栈
					i++;
		}
	}
	s[j]='\0';
}

//-----------------后缀表达式运算实现函数----------------------//
int HZcalc(	char s[])  
{
	int i=0;
	datatype a,b;
	SeqStack *OPND;
	OPND = Init_SeqStack();  //运算数栈
	while(s[i] != '\0')
	{
		if (!In(s[i])) 
		{
			Push_SeqStack(OPND,s[i]-'0');  //不是运算符就入运算数栈
			i++;
		}
		else
		{
			Pop_SeqStack(OPND,&b);
			Pop_SeqStack(OPND,&a);  //取栈顶两个元素做运算
			Push_SeqStack(OPND,Operate(a,s[i],b));  //运算后把结果入栈
			i++;
		}
	}
	return GetTop(OPND);
}
	


void main()
{
	int i;
	printf("\n");
	printf(" 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	printf(" ■           请输入表达式，以“#”结束！        ■\n");
	printf(" 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	printf("\n");
	printf(" ");
	gets(c);
	printf("\n");
    i=EvaluateExpression();
	char s[50];
    change(c,s);
	printf(" 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	printf("              中缀表达式求值结果为：%d\n",i);
    printf("              后缀表达式为：");
    puts(s);
	i = HZcalc(s);
	printf("              后缀表达式求值结果为：%d\n",i);
	printf(" 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	printf("\n");
	printf(" 按任意键结束！");
	getchar();
}

