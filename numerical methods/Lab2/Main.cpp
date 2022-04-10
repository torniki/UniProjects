#include <iostream>
#include <fstream>
#include <iomanip>
#include "Metods.h"

double scalar(double* fobj, double* sobj, size_t len) {
    double ans = 0;
    for (size_t j = 0; j < len; j++) {
        ans += fobj[j] * sobj[j];
    }
    return ans;
}
using namespace std;

int main()
{
    double scalar(double*, double*, size_t);
    size_t len, type;
    ifstream fin("input.txt");
    double** slay;
    double* B_mass;

#pragma region ввод

    if (!fin.is_open()) {
        cout << "Out of File!" << endl;
        return -1;
    }
    else {
        fin >> type >> len;
        slay = new double* [len];
        B_mass = new double[len];
        for (int i = 0; i < len; i++)
            slay[i] = new double[len]();

        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++) {
                fin >> slay[i][j];
                if (j == len - 1)  fin >> B_mass[i];
            }
    }
    fin.close();
#pragma endregion
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++)
            cout << setw(5) << slay[i][j];
        cout << setw(5) << B_mass[i] << endl;
    }

    ofstream fout("output.txt");
    double* ans = metods::orto(slay, B_mass, len);
    double* s_ans = metods::iter(slay, B_mass, len, 0.001);
    double* wtf = metods::miter(slay, B_mass, len);
    cout << "-------------------------------------------" << endl;
    for (int i = 0; i < len; i++)
        cout << "\t" << s_ans[i];
    cout << endl << "-------------------------------------------" << endl;
    for (int i = 0; i < len; i++)
        cout << "\t" << wtf[i];
    cout << endl << "-------------------------------------------" << endl;
    fout << "Вектор решения: (";
    for (int i = 0; i < len; i++) {
        fout << setw(3) << ans[i];
    }
    fout << ")";
    double** rev_ans = new double* [len];
    cout << endl;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            B_mass[j] = slay[j][i];
        }
        rev_ans[i] = metods::orto(slay, B_mass, len);
        for (int j = 0; j < len; j++)
            cout << "\t" << rev_ans[i][j];
        cout << endl;
    }

    for (int i = 0; i < len; i++)
        cout << setw(5) << ans[i];
}

//#include <iostream>
//#include <fstream>
//#include <math.h>
//#include <string>
//#include <Windows.h>
//#include <vector>
//#include "Matrix.h"
//
//using namespace std;
//using namespace Torniki;
//
//size_t len;
//vector<size_t>* adj;
//void ReadD() 
//{
//    ifstream FileIn("Input.txt");
//    FileIn >> len;
//    adj = new vector<size_t>[len];
//    size_t i = 0;
//    int tmp = 0;
//    while (!FileIn.eof() && len - 1 != i)
//    {
//        FileIn >> i;
//        while (FileIn.peek() != '\n')
//        {
//            FileIn >> tmp;
//            adj[i].push_back(tmp);
//            if (FileIn.eof())
//                break;
//        }
//    }
//}
//
///*double* gauss(Matrix& a, Vector& y, int n)
//{
//    double* x, max;
//    int k, index;
//    const double eps = 0.00001;  // точность
//    x = new double[n];
//    k = 0;
//    while (k < n)
//    {
//        // Поиск строки с максимальным a[i][k]
//        max = abs(a[k][k]);
//        index = k;
//        for (int i = k + 1; i < n; i++)
//        {
//            if (abs(a[i][k]) > max)
//            {
//                max = abs(a[i][k]);
//                index = i;
//            }
//        }
//        // Перестановка строк
//        if (max < eps)
//        {
//            // нет ненулевых диагональных элементов
//            cout << "Решение получить невозможно из-за нулевого столбца ";
//            cout << index << " матрицы A" << endl;
//            return 0;
//        }
//        for (int j = 0; j < n; j++)
//        {
//            double temp = a[k][j];
//            a[k][j] = a[index][j];
//            a[index][j] = temp;
//        }
//        double temp = y[k];
//        y[k] = y[index];
//        y[index] = temp;
//        // Нормализация уравнений
//        for (int i = k; i < n; i++)
//        {
//            double temp = a[i][k];
//            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
//            for (int j = 0; j < n; j++)
//                a[i][j] = a[i][j] / temp;
//            y[i] = y[i] / temp;
//            if (i == k)  continue; // уравнение не вычитать само из себя
//            for (int j = 0; j < n; j++)
//                a[i][j] = a[i][j] - a[k][j];
//            y[i] = y[i] - y[k];
//        }
//        k++;
//    }
//    // обратная подстановка
//    for (k = n - 1; k >= 0; k--)
//    {
//        x[k] = y[k];
//        for (int i = 0; i < k; i++)
//            y[i] = y[i] - a[i][k] * x[k];
//    }
//    return x;
//}*/
//
//int main()
//{
//    setlocale(LC_ALL, "Rus");
//    int n; //номер метода 
//    double eps = 0; // границы отрезка
//    string f;
//    double e = 0;   // возвращаемая погрешность
//
//    ofstream FileOut("Output.txt"); ///создание файла для записи данных (выходной файл)
//    ifstream FileIn("Input.txt");   ///создание файла для считывания данных (входной файл)
//    if (!FileIn.is_open())  ///если не получилось открыть файл
//    {
//        cout << "Error with open file! File not found!";
//        return 1;   ///завершаем программу с выводом ошибки
//    }
//
//    Matrix mtr;
//
//    ReadD();
//    cout << "Система уравнений:" ;
//    for (int i=0;i<len;i++) 
//    {
//
//    }
//    
//    
//    FileIn.close();
//    
//    
//
//    FileOut.close(); ///закрытие выходного файла
//    //delete[] fun;
//
//    return 0;
//}