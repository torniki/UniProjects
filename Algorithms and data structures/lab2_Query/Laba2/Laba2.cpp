#include <iostream>
#include <stdio.h>

using namespace std;

/*Объявление главной структуры*/
struct QueueNode
{
    int Data;
    QueueNode *next; // Указатель на следующий элемент очереди 
};

QueueNode *head; // Указатель на голову очереди
QueueNode *tail; // Указатель на хвост очереди

int kol = 0; //Количество элементов

void Init();                    /*Функция, которая создает очередь*/
void Input(int);         /*Функция, которая добавляет элемент в конец*/
int output();

/*Функция, которая создает очередь*/
void init()
{
	head = NULL;
	tail = NULL;
}
void EnQueue(int x)
{
	QueueNode *temp;
	temp = new QueueNode;
	temp->Data = x;
	temp->next = NULL;
	if (head == NULL)
		head = temp;
	else
		tail->next = temp;
	tail = temp;
}
int DeQueue()
{
	int val;
	QueueNode *p;
	p = new QueueNode;
	p = head;
	val = head->Data;
	head = p->next;
	if (head == NULL)
		head = NULL;
	delete p;
	return(val);
}


/*Главная функция*/
int main()
{
    setlocale(LC_ALL, "rus");
	int k=0;
	init();
	while (k>0)
		EnQueue(k=rand()%20-10);
	printf("Введено число %d\n", DeQueue());
	printf("Введено число %d\n", DeQueue());
	printf("Введено число %d\n", DeQueue());
	printf("Введено число %d\n", DeQueue());
	printf("Введено число %d\n", DeQueue());    
	return 0;
}