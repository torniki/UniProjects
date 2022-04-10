#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include <Windows.h>
#include "PolStr.h"

using namespace std;

//метод дихотомии

double dix(char* fun, double a, double b, double eps, double& e)
{

    e = (b - a) / 2;
    double  c = a + e,
        fa = EvalPolStr(fun, a, 0),
        fc = EvalPolStr(fun, c, 0);
    do
    {
        e /= 2;
        if (fa * fc <= 0)
        {
            c -= e;
        }
        else
        {
            c += e;
            fa = fc;
        }
        fc = EvalPolStr(fun, c, 0);
    } while (e >= eps || fabs(fc) >= eps);

    return c;
}

//метод хорд
double chord(char* fun, double a, double b, double eps, double& e)
{
    double  fa = EvalPolStr(fun, a, 0),
        fb = EvalPolStr(fun, b, 0),
        x0,
        fx0;

    do
    {
        x0 = a - ((fa * (b - a)) / (fb - fa));
        fx0 = EvalPolStr(fun, x0, 0);
        if ((fa * fx0) <= 0)
        {
            e = fabs(x0 - b);
            b = x0;
            fb = fx0;
        }
        else
        {
            e = fabs(x0 - a);
            a = x0;
            fa = fx0;
        }
    } while (e >= eps || fabs(fx0) >= eps);

    return x0;
}

//метод Ньютона
double newton(char* fun, double a, double b, double eps, double& e)
{
    //выбор начальной точки
    double c = b, fc = EvalPolStr(fun, c, 0), fcp = EvalPolStr(fun, c, 2);
    if (fc * fcp <= 0) { c = a; fc = EvalPolStr(fun, c, 0); }
    //нахождение корня
    fcp = EvalPolStr(fun, c, 1);
    double x = c;
    do
    {
        c = x;
        x = c - fc / fcp;
        fcp = EvalPolStr(fun, x, 1);
        fc = EvalPolStr(fun, x, 0);
    } while (fabs(x - c) >= eps || fabs(fc) >= eps);

    e = fabs(c - x);
    return x;
}

//метод Золотого сечения
double golden_s(char* fun, double a, double b, double eps, double& e)
{
    double fa = EvalPolStr(fun, a, 0); //значения ф-ции
    double rez = 0; //текущее значение
    double frez = EvalPolStr(fun, rez, 0);
    double g = (sqrt(5.0) + 1) / 2;
    double d = a + (b - a) / g, c = a + b - d; //точки, разбивающие интервал
    double fd = EvalPolStr(fun, d, 0),
        fc = EvalPolStr(fun, c, 0);
    //вычислить fa, fc, fd
    do
    {
        if (fa * fd <= 0)
        {
            b = d;
            d = c;
            fd = fc;
            c = a + b - d;
            fc = EvalPolStr(fun, c, 0);
        }
        else
        {
            a = c;
            fa = fc;
            c = d;
            fc = fd;
            d = a + (b - a) / g;
            fd = EvalPolStr(fun, d, 0);
        }
        rez = (b + a) / 2;
        frez = EvalPolStr(fun, rez, 0);
    } while ((b - a) / 2 >= eps || fabs(frez) >= eps);

    e = (b - a) / 2;
    return rez;
}

//Комбинированный метод
double comb(char* fun, double a, double b, double eps, double& e)
{
    double fa;//  EvalPolStr(fun, a, 0); //значения ф-ции
    double fb;//  EvalPolStr(fun, b, 0);
    double rez; //текущее значение
    double frez;//  EvalPolStr(fun, rez, 0);

    do
    {
        fa = EvalPolStr(fun, a, 0);
        fb = EvalPolStr(fun, b, 0);
        if (fa * EvalPolStr(fun, a, 2) > 0)
        {
            b = a - fa * (b - a) / (fb - fa);
            a = a - fa / EvalPolStr(fun, a, 1);
        }
        else
        {
            a = a - fa * (b - a) / (fb - fa);
            b = b - fb / EvalPolStr(fun, b, 1);
        }
        rez = (a + b) / 2;
        frez = EvalPolStr(fun, rez, 0);
        e = (b - a) / 2;
    } while (e >= eps || fabs(frez) >= eps);

    return rez;
}

// метод итераций
double iter(char* fun, double a, double b, double eps, double& e)
{
    double i = a;
    double fi, x0, x;
    double fa = EvalPolStr(fun, a, 0);
    double f1a = EvalPolStr(fun, a, 1);
    //double f2a = EvalPolStr(fun, a, 2);
    while (i < b)
    {
        i += eps;
        fi = EvalPolStr(fun, i, 1);
        if (fabs(fi) > fabs(f1a)) f1a = fi;
    }
    if (EvalPolStr(fun, a, 2) * fa > 0) x0 = a;
    else x0 = b;
    double fx0 = EvalPolStr(fun, x0, 0);
    do
    {
        x = x0;
        x0 -= fx0 / f1a;
        fx0 = EvalPolStr(fun, x, 0);
    } while (fabs(x - x0) > eps || fabs(fx0) > eps);

    e = fabs(x - x0);
    return x0;
}

int menu() {
    int n;
    cout << "Выбор метода\n1 - Дихотомия\n2 - Хорд\n3 - Ньютона\n4 - Золотого сечения\n5 - Комбинированный метод\n6 - Итераций\n7 - Выход\nВаш метод:";
    cin >> n;
   
    return n;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    int n; //номер метода 
    double a = 0, b = 0, eps = 0; // границы отрезка
    char f[30];
    double e = 0;   // возвращаемая погрешность

    ofstream FileOut("Output.txt"); ///создание файла для записи данных (выходной файл)
    ifstream FileIn("Input.txt");   ///создание файла для считывания данных (входной файл)
    if (!FileIn.is_open())  ///если не получилось открыть файл
    {
        cout << "Error with open file! File not found!";
        return 1;   ///завершаем программу с выводом ошибки
    }
    FileIn >> f;
    FileIn >> a;
    FileIn >> b;
    FileIn >> eps;
    FileIn.close();
    
    
    char* fun = CreatePolStr(f, 0);

    cout << "\n\n";

    int q = -floor(log10(eps));
    do {
        system("cls");
        cout << f << endl << a << endl << b << endl << eps << endl;
        n = menu();
    switch (n)
    {
    case 1:
        FileOut << "Метод дихотомии:\nx* = " << fixed << setprecision(q) << dix(fun, a, b, eps, e) << endl;
        FileOut << "f(x*) = " << EvalPolStr(fun, dix(fun, a, b, eps, e), 0);
        FileOut << "\nE* = " << scientific << e << endl;
        break;
    case 2:
        FileOut << "Метод хорд:\nx* = " << fixed << setprecision(q) << chord(fun, a, b, eps, e) << endl; //метод хорд
        FileOut << "f(x*) = " << EvalPolStr(fun, chord(fun, a, b, eps, e), 0);
        FileOut << "\nE* = " << scientific << e << endl;
        break;
    case 3:
        FileOut << "Метод Ньютона:\nx* = " << fixed << setprecision(q) << newton(fun, a, b, eps, e) << endl; //метод Ньютона
        FileOut << "f(x*) = " << EvalPolStr(fun, newton(fun, a, b, eps, e), 0);
        FileOut << "\nE* = " << scientific << e << endl;
        break;
    case 4:
        FileOut << "Метод Золотого сечения:\nx* = " << fixed << setprecision(q) << golden_s(fun, a, b, eps, e) << endl; //метод Ньютона
        FileOut << "f(x*) = " << EvalPolStr(fun, golden_s(fun, a, b, eps, e), 0);
        FileOut << "\nE* = " << scientific << e << endl;
        break;
    case 5:
        FileOut << "Комбинированный метод:\nx* = " << fixed << setprecision(q) << comb(fun, a, b, eps, e) << endl; //метод Ньютона
        FileOut << "f(x*) = " << EvalPolStr(fun, comb(fun, a, b, eps, e), 0);
        FileOut << "\nE* = " << scientific << e << endl;
        break;
    case 6:
        FileOut << "Метод итераций:\nx* = " << fixed << setprecision(q) << iter(fun, a, b, eps, e) << endl; //метод Ньютона
        FileOut << "f(x*) = " << EvalPolStr(fun, iter(fun, a, b, eps, e), 0);
        FileOut << "\nE* = " << scientific << e << endl;
        break;

    }
    system("pause");
    } while (n<7);

    FileOut.close(); ///закрытие выходного файла
    delete[] fun;

    return 0;
}
