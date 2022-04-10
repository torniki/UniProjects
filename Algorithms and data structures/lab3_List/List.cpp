#include "List.h"
#include <iostream>

namespace Mine
{
    List::List()
    {
        Head =  NULL;
        Tail =  NULL;
    }
    List::~List()
    {
        while(Head!=NULL)
        {
            ListNode *p;
            p = Head;
            Head = Head->next;
            delete p;
        }
        Head = Tail = nullptr;
    }

    int List::viewFirstItem() const
    {
        if(isEmpty())
        {
            std::cout << "Попытка чтения из пустого списка"<< std::endl;
			throw "Попытка чтения из пустого списка";
        }
        return (Head->info);
    }

    int List::removeFirstItem()
    {
        if(isEmpty())
        {
            std::cout << "Попытка удаления из пустого списка"<< std::endl;
			throw "Попытка удаления из пустого списка";
        }
        int value = Head->info;
        ListNode *pointer = Head;
        Head = Head->next;
        delete pointer;
        return value;
    }

    void List::insertionInFront(int value)
    {
        ListNode *newNode; //создаём указатель на НОВУЮ запись
        newNode = new ListNode; //выделяем память
        newNode->info = value; //записываем информацию в новое поле
        if(isEmpty())
        {
            newNode->next = NULL;
            Head = Tail = newNode;
        }
        else
        {
            newNode->next = Head;
            Head = newNode;
        }
    }
    void List::insertionInFront(ListNode* &elem)
    {
        if(isEmpty())
        {
            elem->next = NULL;
            Head = Tail = elem;
        }
        else
        {
            elem->next = Head;
            Head = elem;
        }
    }

    int List::viewLastItem() const
    {
        if(isEmpty())
        {
            std::cout << "Попытка чтения из пустого списка"<< std::endl;
			throw "Попытка чтения из пустого списка";
        }
        return (Tail->info);
    }

    int List::removeLastItem()
    {
        if(isEmpty())
        {
            std::cout << "Попытка удаления из пустого списка"<< std::endl;
			throw "Попытка удаления из пустого списка";
        }
        int value = Tail->info;
        ListNode *pointer = Tail;
        ListNode *i = Head;
        while (i->next != Tail)
        {
            i = i->next;
        }
        i->next = NULL;
        Tail = i;
        delete pointer;
        return value;
    }

    void List::insertionInEnd(int value)
    {
        ListNode *newNode; //создаём указатель на НОВУЮ запись
        newNode = new ListNode; //выделяем память
        newNode->info = value; //записываем информацию в новое поле
        if(isEmpty())
        {
            newNode->next = NULL;
            Head = Tail = newNode;
        }
        else
        {
            newNode->next = NULL;
            Tail->next = newNode;
            Tail = newNode;
        }
    }
    void List::insertionInEnd(ListNode* &elem)
    {
        if(isEmpty())
        {
            elem->next = NULL;
            Head = Tail = elem;
        }
        else
        {
            elem->next = NULL;
            Tail->next = elem;
            Tail = elem;
        }
    }


    void List::insertionByIndex(int value, int index)
    {
        if(isEmpty())
        {
            std::cout << "Попытка поиска несуществующего элемента при записи по индексу"<< std::endl;
            throw "Попытка поиска несуществующего элемента при записи по индексу";
        }
        ListNode *p = Head;
        for(int i=0; i<index; i++)
        {
            if(p->next == NULL)
            {
                std::cout << "Попытка поиска несуществующего элемента при записи по индексу"<< std::endl;
                throw "Попытка поиска несуществующего элемента при записи по индексу";
            }
            p = p->next;
        }
        ListNode *newNode; //создаём указатель на НОВУЮ запись
        newNode = new ListNode; //выделяем память
        newNode->info = value; //записываем информацию в новое поле
        newNode->next = p->next;
        p->next = newNode;
    }
    void List::insertionByIndex(ListNode* &elem, int index)
    {
        if(isEmpty())
        {
            std::cout << "Попытка поиска несуществующего элемента при записи по индексу"<< std::endl;
            throw "Попытка поиска несуществующего элемента при записи по индексу";
        }
        ListNode *p = Head;
        for(int i=0; i<index; i++)
        {
            if(p->next == NULL)
            {
                std::cout << "Попытка поиска несуществующего элемента при записи по индексу"<< std::endl;
                throw "Попытка поиска несуществующего элемента при записи по индексу";
            }
            p = p->next;
        }
        elem->next = p->next;
        p->next = elem;
    }

    int List::viewByIndex(int index) const
    {
        if(isEmpty())
        {
            std::cout << "Попытка чтения из пустого списка"<< std::endl;
			throw "Попытка чтения из пустого списка";
        }
        ListNode *p = Head;
        for(int i=0; i<index; i++)
        {
            if(p->next == NULL)
            {
                std::cout << "Попытка чтения несуществующего элемента"<< std::endl;
                throw "Попытка чтения несуществующего элемента";
            }
            p = p->next;
        }
        return(p->info);
    }

    int List::removeByIndex(int index)
    {
        if(index<0)
        {
            std::cout << "Попытка удаления несуществующего элемента"<< std::endl;
			throw "Попытка удаления несуществующего элемента";
        }
        if(isEmpty())
        {
            std::cout << "Попытка удаления из пустого списка"<< std::endl;
			throw "Попытка удаления из пустого списка";
        }
        ListNode *pointer;
        if (index==0)
        {
            pointer = Head;
            Head = Head->next;
        }
        else
        {
            ListNode *p = Head;
            for(int i=0; i<index-1; i++)
            {
                if(p->next == NULL)
                {
                    std::cout << "Попытка поиска несуществующего элемента при удалении по индексу"<< std::endl;
                    throw "Попытка поиска несуществующего элемента при удалении по индексу";
                }
                p = p->next;
            }
            if(p->next == NULL)
            {
                std::cout << "Попытка чтения несуществующего элемента"<< std::endl;
                throw "Попытка чтения несуществующего элемента";
            }
            pointer = p->next;
            p->next=pointer->next;
        }
        return(pointer->info);
        delete pointer;
        pointer = nullptr;
    }


    bool List::isEmpty() const
    {
        return (Head == NULL);
    }
    void List::PrintList() const
    {
        ListNode *p = Head;
        while (p != NULL)
        {
            printf("%d; ", p->info);
            p = p->next;
        }
        printf("\n");
    }

    ListNode* List::getHead() const
    {
        return(Head);
    }
    ListNode* List::getTail() const
    {
        return(Tail);
    }
}
