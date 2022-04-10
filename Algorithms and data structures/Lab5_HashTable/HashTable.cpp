#include "HashTable.h"
#include <iostream>
#include <cmath>

using namespace std;
namespace Mine
{
    HashTable::HashTable()
    {
    }

    void HashTable::push(int value)
    {
        arr[Hash(value)].insertionInEnd(value);
    }

    int HashTable::itemSearch (int key) const
    {
        cout<<"���� "<<key<<":";
        int numOfTry=0;
        int index = Hash(key);
        ListNode *curHead=arr[index].getHead();
        if(curHead==NULL)
        {
            cout<<"������: �������� ����� � ������� ���!\n";
            throw "�������� ����� � ������� ���";
        }
        while ((curHead->next!=NULL)&&(curHead->info!=key))
        {
            numOfTry++;
            curHead = curHead->next;
        }
        if(curHead->info!=key)
        {
            cout<<"������: �������� ����� � ������� ���!\n";
            throw "�������� ����� � ������� ���";
        }
        cout<<"\n�������:"<<index<<"; "<<numOfTry<<"\n���������� ����:"<<numOfTry+1<<endl;
        return index;
    }

    void HashTable::delItem (int key)
    {
        int secIndex=0;
        int index = Hash(key);
        ListNode *curHead=arr[index].getHead();
        if(curHead==NULL)
        {
            cout<<"������: ���������� ����� � ������� ���!\n";
            throw "���������� ����� � ������� ���";
        }
        while ((curHead->next!=NULL)&&(curHead->info!=key))
        {
            secIndex++;
            curHead = curHead->next;
        }
        if(curHead->info!=key)
        {
            cout<<"������: ���������� ����� � ������� ���!\n";
            throw "���������� ����� � ������� ���";
        }
        arr[index].removeByIndex(secIndex);
    }

    void HashTable::print() const
    {
        int numOfTry=0;
        ListNode *curHead;
        for (int i=0; i<this->LENGHT;i++)
        {
            curHead = arr[i].getHead();
            while (curHead!=NULL)
            {
                numOfTry++;
                cout<<curHead->info<<"\t";
                curHead=curHead->next;
            }
            cout<<endl;
        }
        cout<<"\n���������� ���� ��� ������: "<<numOfTry<<endl;
    }

    int HashTable::Hash(int value) const
    {
        return value%10;
    }
}
