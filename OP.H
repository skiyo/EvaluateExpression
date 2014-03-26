#define OK 1
#define ERROR 0
#define MAXSIZE 64
typedef int datatype;
//运算符结构体
typedef struct
{
	char OPname;  //存储运算符
	int inOP;     //存储栈内级别
	int outOP;    //存储栈外级别
}OP;
//定义运算数栈
typedef struct
{
	datatype data[MAXSIZE];
	int top;
}SeqStack;
//定义运算符栈
typedef struct
{
	char data[MAXSIZE];
	int top;
}charStack;