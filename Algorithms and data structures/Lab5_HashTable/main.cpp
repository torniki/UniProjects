#include <iostream>
#include "HashTable.h"
#include <fstream>
#include <ctime>

using namespace std;
using namespace Mine;

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(static_cast<unsigned int>(time(0)));
    HashTable a;

    ofstream Gen;
    Gen.open("Input.txt");
    for (int i = 0; i < 15; i++)
    {
        Gen << rand() % 100;
        Gen << "\n";
    }
    Gen.close();

    ifstream FileIn("Input.txt");
    int rNum;
    while (!FileIn.eof())
    {
        FileIn >> rNum;
        a.push(rNum);
    }
    ///считали числа из файла в хеш таблицу

    a.print();

    int searchValue;
    cin >> searchValue;
    a.itemSearch(searchValue);
    cin >> searchValue;
    a.itemSearch(searchValue);
    return 0;
}
