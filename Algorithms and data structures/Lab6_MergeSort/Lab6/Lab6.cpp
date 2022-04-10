#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

// Функция сортировки слиянием
int comp = 0;

void mergeSort(int* a, int l, int r)
{
    if (l == r) return; // границы сомкнулись
    int mid = (l + r) / 2; // определяем середину последовательности
    // и рекурсивно вызываем функцию сортировки для каждой половины
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    int i = l;  // начало первого пути
    int j = mid + 1; // начало второго пути
   
    // !!! Освободить динамическую память

    int* tmp = (int*)malloc(r * sizeof(int)); // дополнительный массив
    for (int step = 0; step < r - l + 1; step++) // для всех элементов дополнительного массива
    {
        // записываем в формируемую последовательность меньший из элементов двух путей
        // или остаток первого пути если j > r
        if ((j > r) || ((i <= mid) && (a[i] < a[j])))
        {
            comp += 1;
            tmp[step] = a[i];
            i++;
        }
        else
        {
            comp += 1;
            tmp[step] = a[j];
            j++;
        }
    }
    // переписываем сформированную последовательность в исходный массив
    for (int step = 0; step < r - l + 1; step++)
        a[l + step] = tmp[step];
}

int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    srand(static_cast<unsigned int>(time(0)));

    ifstream FileIn("Numbers.txt");
    int* a = nullptr;
    int Size = 0;
    // Заполняем массив
    for(int x; FileIn >> x;)
    {
        ++Size;

        int* array_failsafe = a;
        a = static_cast<int*>(realloc(a, sizeof(x) * Size));
        if (a == nullptr)
        {
            std::cerr << "realloc() failed!" << std::endl;
            free(array_failsafe);
            return EXIT_FAILURE;
        }
        a[Size - 1] = x;
    }
    for (int i = 0; i < Size; ++i)
    {
        if (i % 10 == 0)
            cout << endl;
        std::cout << a[i] << " ";
    }
    cout << endl<<endl;
    FileIn.close();
    comp = 0;
    mergeSort(a, 0, Size-1); // вызываем функцию сортировки
    // Выводим отсортированный массив
    
    // !!! Выводить результат и в файл тоже (либо только в файл)

    // !!! Обобщить код так, чтобы не было дублирований (т.е. чтобы и считывание\сортировка файла из 100 чисел и эти же действия с файлом из 1000 чисел производились одним участком кода)
    ofstream Out("NumbOut.txt");
    for (int i = 0; i < Size; ++i)
    {
        Out << a[i];
        Out << endl;
        if (i % 10 == 0)
            cout << endl;
        std::cout << a[i] << " ";
    }
    Out.close();
    free(a);
    cout << endl;
    cout << "\nКол-во сравнений:" << comp << endl;
    system("pause");
    return 0;
}