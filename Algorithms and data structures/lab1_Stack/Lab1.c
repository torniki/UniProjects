#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#define SIZE 100
char Stack[SIZE];
int t;

void init(); // инициализация стека
void Push(int); // положить в стек
int Pop(); // забрать из стека
int Top(); // получить значение верхнего элемента стека
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
    printf("Позиция первой скобки:",Pop());
    return 0;
}

void init() // инициализация стека
{
    t = -1;
}
 void Push(int a) // положить в стек
 {
    if(t==SIZE) // проверка на попытку занесения элемента в полный стек
    {
        printf("Попытка занесения значения в полный стек");
        exit(EXIT_FAILURE);
    }
    else
    {
        t = t+1;
        Stack[t] = a;
    }
}
int Pop() // забрать из стека
{
    if(t == -1) // проверка на попытку забрать элемент из пустого стека
    {
        printf("Попытка чтения из пустого стека");
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
int Top() // получить значение верхнего элемента стека
{
    return(Stack[t]);
}
int IsEmpty() // проверить, является ли стек пустым
{
    if(t == -1)
        return(1);
    else
        return(0);
}
