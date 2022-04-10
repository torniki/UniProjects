#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <ctime>


using namespace std;
using namespace Me;



int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    srand(static_cast<unsigned int>(time(0)));

    BinaryTree tree;

    cout << "Выберите режим: \n"
        <<"1)Cчитать числа из файла \n"
        <<"2)Ввести с клавиатуры\n"
        <<"3)Сгенерировать с помощью генератора случайных чисел\n"
        <<"Ваш выбор:";
    int n;
    cin >> n;

    if (n == 1) 
    {
        ifstream FileIn("Input.txt");
        int rNum;
        while (!FileIn.eof())
        {
            FileIn >> rNum;
            tree.addNode(rNum);
        }
        //считали числа из файла в дерево
    }
    else if (n == 2) 
    {
        cout << "Введите необходимое кол-во чисел: ";
        int num;
        cin >> num;
        cout << "Введите числа:\n";
        int info;
        for (int i = 0; i < num; i++) 
        {
            cin >> info;
            tree.addNode(info);
        }
    }
    else if (n == 3) 
    {
        int num;
        cout << "Введите необходимое кол-во чисел: ";
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            tree.addNode(rand() % 100); 
        }
    }
    
    tree.Print();
    tree.Count();
    cin >> n;
    cout << "\nГлубина:" << tree.getE(n) << endl;
}

