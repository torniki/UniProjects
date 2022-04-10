#include <fstream>
#include <iostream>
#include <ctime>
#include "List.h"

using namespace std;
using namespace Mine;

void moveNegativeToTheBeginning(List &SecondList, const List &FirstList)
{
    ListNode *h = FirstList.getHead();

    SecondList.insertionInEnd(h->info);
    while (h->next != NULL)
    {
        h = h->next;
        SecondList.insertionInEnd(h->info);
    }
    //����������� ������ ������ �� ������

    ListNode *pointer1 = SecondList.getHead();
    int i=0;
    while(pointer1->info<0)//�������� ������ ������������� �������� (���� ��� ����)
    {
        i++;
        pointer1 = pointer1->next;
    }

    while (pointer1->next != NULL)//������� ���������� ������������� �������� (���� ��� ����)
    {
        if(pointer1->next->info<0)
        {
            SecondList.insertionInFront(SecondList.removeByIndex(i+1));
        }
        else
        {
            pointer1=pointer1->next;
        }
        i++;
    }
}

int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
	srand(static_cast<unsigned int>(time(0)));

    List FirstList;

	ofstream Gen;
	Gen.open("Input.txt");
	for (int i = 0; i < 15; i++)
	{
		Gen << rand() % 20 - 10;
		Gen << "\n";
	}
	Gen.close();

    ifstream FileIn("Input.txt");
    int rNum;
    while (!FileIn.eof())
    {
        FileIn >> rNum;
        FirstList.insertionInEnd(rNum);
    }
    //������� ����� �� ����� � ������ ������


    List SecondList;
    moveNegativeToTheBeginning(SecondList, FirstList);

    cout<<"������ FirstList:\n";
    FirstList.PrintList();
    cout<<"������ SecondList:\n";
    SecondList.PrintList();
	system("pause");
    return 0;

}
