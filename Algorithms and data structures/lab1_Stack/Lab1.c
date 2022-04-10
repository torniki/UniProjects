#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#define SIZE 100
char Stack[SIZE];
int t;

void init(); // ������������� �����
void Push(int); // �������� � ����
int Pop(); // ������� �� �����
int Top(); // �������� �������� �������� �������� �����
int IsEmpty();

int main()
{
    setlocale(0,"rus");
    int i=0;
    char *s={'A','+','(','4','5','-','F','(','X',')','*','(','B','-','C',')',')','\0'};
    init();
    printf("a\n");
    while(s+i!='\0')
    {
        if(s+i=='(')
        {
            Push(i);
            break;
        }

        printf("%c",s+i);
        i++;
    }
    printf("������� ������ ������:",Pop());
    return 0;
}

void init() // ������������� �����
{
    t = -1;
}
 void Push(int a) // �������� � ����
 {
    if(t==SIZE) // �������� �� ������� ��������� �������� � ������ ����
    {
        printf("������� ��������� �������� � ������ ����");
        exit(EXIT_FAILURE);
    }
    else
    {
        t = t+1;
        Stack[t] = a;
    }
}
int Pop() // ������� �� �����
{
    if(t == -1) // �������� �� ������� ������� ������� �� ������� �����
    {
        printf("������� ������ �� ������� �����");
        exit(EXIT_FAILURE);
    }
    else
    {
        int val = 0;
        val = Stack[t];
        t = t-1;
        return(val);
    }
}
int Top() // �������� �������� �������� �������� �����
{
    return(Stack[t]);
}
int IsEmpty() // ���������, �������� �� ���� ������
{
    if(t == -1)
        return(1);
    else
        return(0);
}
