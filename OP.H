#define OK 1
#define ERROR 0
#define MAXSIZE 64
typedef int datatype;
//������ṹ��
typedef struct
{
	char OPname;  //�洢�����
	int inOP;     //�洢ջ�ڼ���
	int outOP;    //�洢ջ�⼶��
}OP;
//����������ջ
typedef struct
{
	datatype data[MAXSIZE];
	int top;
}SeqStack;
//���������ջ
typedef struct
{
	char data[MAXSIZE];
	int top;
}charStack;