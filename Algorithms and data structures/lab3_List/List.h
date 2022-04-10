#pragma once


namespace Mine
{
    struct ListNode
    {
        int info;
        ListNode *next;
    };

	class List
	{
        public:
        List(); //Конструктор
        ~List(); //Деструктор

        int viewFirstItem() const;          //прочитать первый элемент списка
        int removeFirstItem();             //удалить первый элемент списка
        void insertionInFront(int value);   //добавить новый элемент в начало списка
        void insertionInFront(ListNode* &elem);//добавить существующий элемент в начало списка

        int viewLastItem() const;           //прочитать последний элемент списка
        int removeLastItem();              //удалить последний элемент списка
        void insertionInEnd(int value);     //добавить новый элемент в конец списка
        void insertionInEnd(ListNode* &elem); //добавить существующий элемент в конец списка

        void insertionByIndex(int value, int index);   //добавить новый элемент в список после элемента с индексом
        void insertionByIndex(ListNode* &elem, int index); //добавить существующий элемент в список после элемента с индексом
        int viewByIndex(int index) const;   //прочитать элемент списка по индексу
        int removeByIndex(int index); //удалить элемент списка по индексу

        bool isEmpty() const;               //проверить список на пустоту
        void PrintList() const;             //вывести содержимое списка на экран

        ListNode* getHead() const;
        ListNode* getTail() const;

        private:
        ListNode *Head;
        ListNode *Tail;
	};
}
