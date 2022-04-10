#include <locale.h>
#include <iostream>
#include "PolStr.h"

using namespace std;

int main()
{
	char function[] = "x*x + 1"; // Исходная функция
	// Почему не написать x^2+1? Потому что будут проблемы при вычислении производной. Если брать обобщенную производную степени, т.е. производную
	// функции f(x)^g(x), то в записи этой производной появится логарифм функции f(x). Соответственно, если данная функция будет принимать значения,
	// меньшие либо равные 0, то вычисления завершатся математической ошибкой. Поэтому функция x^2+1 будет вычисляться правильно, а ее производные -
	// только в том случае, если аргумент x положительный
	char *polstr = CreatePolStr(function, 0); // Преобразуем в польскую строку (второй параметр = 0 означает, что аргумент функции скалярный)

	setlocale(LC_ALL, "russian");
	cout << "Функция f(x) = " << function << endl;

	if (Error != ERR_OK)
	{
		cout << "Ошибка: " << Error << endl;
	}
	else
	{
		cout << "Обратная польская запись: " << polstr << endl;

		for (double x = -3; x <= 3; x += 1)
		{
			cout << "f(" << x << ") = " << EvalPolStr(polstr, x) << endl; // Вычисляем значение функции, а также первой и второй производной
			cout << "f'(" << x << ") = " << EvalPolStr(polstr, x, 1) << endl;
			cout << "f''(" << x << ") = " << EvalPolStr(polstr, x, 2) << endl;
		}

		delete[] polstr; // Функция CreatePolStr выделяет динамическую память, её нужно освободить
	}

	char function2[] = "x1*x2 + sin(x1) + cos(x2)"; // Функция векторного аргумента
	polstr = CreatePolStr(function2, 2); // Указываем, что у функции 2 аргумента
	cout << endl << "Функция f(x) = " << function2 << endl;

	if (Error != ERR_OK)
	{
		cout << "Ошибка: " << Error << endl;
	}
	else
	{
		double x[] = { 1, 1 };
		cout << "Обратная польская запись: " << polstr << endl;
		cout << "f(" << x[0] << "," << x[1] << ") = " << EvalPolStr(polstr, x) << endl; // Вычисляем значение функции в точке x
		cout << "df/dx1|(" << x[0] << "," << x[1] << ") = " << EvalPolStr(polstr, x, 1, 1) << endl; // Вычисляем значение частной производной df/dx1 в точке x
		cout << "df/dx2|(" << x[0] << "," << x[1] << ") = " << EvalPolStr(polstr, x, 1, 2) << endl; // Вычисляем значение частной производной df/dx2 в точке x

		//for (double x = -3; x <= 3; x += 1)
		//{
		//	cout << "f(" << x << ") = " << EvalPolStr(polstr, x) << endl;
		//	cout << "f'(" << x << ") = " << EvalPolStr(polstr, x, 1) << endl;
		//	cout << "f''(" << x << ") = " << EvalPolStr(polstr, x, 2) << endl;
		//}

		delete[] polstr;
	}

	system("pause");
	return 0;
}
