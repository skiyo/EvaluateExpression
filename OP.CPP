#define OPNUM 8
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "OP.h"
char c[50];  //�洢������ַ���
//--------------------����Ϊջ�Ĳ���-----------------------//
//--------------------������ջ-----------------------//
//��ʼ��ջ
SeqStack *Init_SeqStack()
{
	SeqStack *s;
	s = (SeqStack *)malloc(sizeof(SeqStack));
    s->top = -1; 
	return s;
}
//�жϿ�ջ
int Empty_SeqStack(SeqStack *s)
{
   if (s->top==-1)
   return 1;
   else  return 0;
}  
//��ջ
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
//��ջ
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
//ȡջ��Ԫ��
datatype GetTop(SeqStack *s)
{
    if (Empty_SeqStack(s))  
		return 0;
    else
		return (s->data[s->top]);
}
//--------------------�����ջ-----------------------//
//��ʼ��ջ
charStack *Init_charStack()
{
	charStack *s;
	s = (charStack *)malloc(sizeof(charStack));
    s->top = -1; 
	return s;
}
//�жϿ�ջ
int Empty_charStack(charStack *s)
{
   if (s->top==-1)
   return 1;
   else  return 0;
}  
//��ջ
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
//��ջ
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
//ȡջ��Ԫ��
char GetcharTop(charStack *s)
{
    if (Empty_charStack(s))  
		return 0;
    else
		return (s->data[s->top]);
}

//----------------�������������-----------------//

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
//-----------------�ж��Ƿ�Ϊ�����-------------------//
int In(char x)
{
	int i;
	for(i=0;i<=OPNUM;i++)  //��������������
	{
		if (x==OPPree[i].OPname) return 1;  //�����������1
	}
	return 0;  //�������������0
}

//-----------------�ж����ȼ�------------------------//
char Precede(char x,char c)
{
	int i,inlev;
	for(i=0;i<=OPNUM;i++)
	{
		if (x==OPPree[i].OPname) 
			break;
	}                                 //���� x ���±�
	inlev = OPPree[i].inOP;
	for(i=0;i<=OPNUM;i++)
	{
		if (c==OPPree[i].OPname) break;
	}  //���� c ���±�
	if (inlev < OPPree[i].outOP) return '<';  //�Ƚ� x ��ջ�ڼ���� c ��ջ�⼶��
	else if (inlev > OPPree[i].outOP) return '>';
	else return '=';
}

//-------------------���㺯��-------------------------//
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

//-----------------��׺����ʽ����ʵ�ֺ���----------------------//
int EvaluateExpression()
{
	int i=0;
	datatype a,b;
	char x,theta;
	charStack *OPTR;
    SeqStack *OPND;
	OPTR = Init_charStack();  //�����ջ
	Push_charStack(OPTR, '#');
	OPND = Init_SeqStack();  //������ջ
	while(c[i] != '\0')
	{
		if (!In(c[i]))  //������������
		{
			Push_SeqStack(OPND,c[i]-'0');  //��������ջ
			i++;
		}
		else
			switch(Precede(GetcharTop(OPTR),c[i]))  //����������,ȡջ��Ԫ�ص�ջ�ڼ����ջ��Ԫ�ص�ջ�⼶��Ƚ�
		{
			case '<' :
					Push_charStack(OPTR,c[i]);  //С���������ջ
					i++;
					break;
			case '=' :
					Pop_charStack(OPTR,&x);  //�������ջ
					i++;
					break;
			case '>' :
					Pop_charStack(OPTR, &theta);
					Pop_SeqStack(OPND,&b);
					Pop_SeqStack(OPND,&a);  //������������һ���������ջ,��������
					Push_SeqStack(OPND,Operate(a,char(theta),b));
					break;
		}
	}
	return GetTop(OPND);
}

//-----------------��׺����ʽת����׺����ʽ----------------------//
void change(char a[],char s[])
{
	int i=0,j=0;
	char temp;
	charStack *OPTR;
	OPTR = Init_charStack();
	Push_charStack(OPTR, '#');
	while(a[i]!='\0')
	{
		if (!In(a[i]))  //������������
		{
			s[j]=a[i];
			j++;
			i++;  //ֱ�����뵽��׺����ʽ
			continue;
		}
		else
			switch(Precede(GetcharTop(OPTR),a[i]))
		{
			case '<' :
					Push_charStack(OPTR,a[i]);  //��ջ�ڼ���С��ջ�⼶���ʱ����ջ
					i++;
					break;
			case '>' :
					while(Precede(GetcharTop(OPTR),a[i])=='>')  //��ջ��Ԫ�ش���ջ��Ԫ��
					{
						Pop_charStack(OPTR, &temp);  //ջ��Ԫ�س�ջ
						s[j]=temp;
						j++;
						temp=GetcharTop(OPTR);  //ȡջ��Ԫ�ؼ����Ƚ�
					}
					break;
			case '=':
					Pop_charStack(OPTR, &temp); //���ھͳ�ջ
					i++;
		}
	}
	s[j]='\0';
}

//-----------------��׺����ʽ����ʵ�ֺ���----------------------//
int HZcalc(	char s[])  
{
	int i=0;
	datatype a,b;
	SeqStack *OPND;
	OPND = Init_SeqStack();  //������ջ
	while(s[i] != '\0')
	{
		if (!In(s[i])) 
		{
			Push_SeqStack(OPND,s[i]-'0');  //�������������������ջ
			i++;
		}
		else
		{
			Pop_SeqStack(OPND,&b);
			Pop_SeqStack(OPND,&a);  //ȡջ������Ԫ��������
			Push_SeqStack(OPND,Operate(a,s[i],b));  //�����ѽ����ջ
			i++;
		}
	}
	return GetTop(OPND);
}
	


void main()
{
	int i;
	printf("\n");
	printf(" ��������������������������������������������������\n");
	printf(" ��           ���������ʽ���ԡ�#��������        ��\n");
	printf(" ��������������������������������������������������\n");
	printf("\n");
	printf(" ");
	gets(c);
	printf("\n");
    i=EvaluateExpression();
	char s[50];
    change(c,s);
	printf(" ��������������������������������������������������\n");
	printf("              ��׺����ʽ��ֵ���Ϊ��%d\n",i);
    printf("              ��׺����ʽΪ��");
    puts(s);
	i = HZcalc(s);
	printf("              ��׺����ʽ��ֵ���Ϊ��%d\n",i);
	printf(" ��������������������������������������������������\n");
	printf("\n");
	printf(" �������������");
	getchar();
}
