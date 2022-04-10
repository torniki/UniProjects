#include <iostream>
#include <fstream>
#include <string>
#include "PolStr.h"
#include <vector>

using namespace std;

double F(const char*, double, unsigned);
void method_rect(int, int, double, double, vector<double>&, int, vector<double>&, const char*, double, bool);
void method_trapez(int, int, double, double, vector<double>&, int, vector<double>&, const char*, double);
void method_Simpson(int, int, double, double, vector<double>&, int, vector<double>&, const char*, double);
void method_Cheb(int, int, double, double, const char*);
void Print_in_file(int, double, double, int, int, bool);

int main()
{
	int m, g = 0, n, s = 0;
	double a = 0, b = 0, e = -1, temp;
	char equation[128];
	char* equation_str = nullptr;
	vector<double> X, Y;

	std::ofstream fout("Result.txt", std::ios_base::goodbit);
	fout.close();

	std::ifstream fin("MyFile.txt"); //Чтение из файла

	fin >> m; //Формула интегрирования

	if (m != 5)
		fin >> g; //Сетка: 1-равномерная, 2-неравномерная, 3-динамическая

	fin >> n; //Количество интервалов интегрирования

	if (m == 4 && n % 2 != 0)
	{
		std::string Error = "В формуле Симпсона количество интервалов интегрирования должно быть кратно двум.\n";
		throw Error;
	}

	if (m == 5 || g != 2) //Границы отрезка	
	{
		fin >> a;
		fin >> b;
	}

	if (g == 2)
	{
		for (int i = 0; i < n + 1; i++)
		{
			fin >> temp;
			X.push_back(temp); //Узлы сетки
		}
	}

	if (g != 3 && m != 5) //Функция: 1-табличная, 2-аналитическая
		fin >> s;
	else
		s = 2;

	if (s == 1)
	{
		for (int i = 0; i < n + 1; i++)
		{
			fin >> temp;
			Y.push_back(temp); //Значения функции в узлах сетки
		}
	}

	if (s == 2)
	{
		fin >> equation;
		equation_str = CreatePolStr(equation, 0); //Аналитическое выражение для функции
	}

	if (g == 3) //Точность вычисления интеграла на динамической сетке
		fin >> e;

	fin.close();

	switch (m)
	{
	case 1:
		method_rect(g, n, a, b, X, s, Y, equation_str, e, true);
		break;
	case 2:
		method_rect(g, n, a, b, X, s, Y, equation_str, e, false);
		break;
	case 3:
		method_trapez(g, n, a, b, X, s, Y, equation_str, e);
		break;
	case 4:
		method_Simpson(g, n, a, b, X, s, Y, equation_str, e);
		break;
	case 5:
		method_Cheb(m, n, a, b, equation_str);
		break;
	}
	delete[] equation_str;

	return 0;
}

double F(const char* obj, double item, unsigned der = 0) //Уравнения и диффуры
{
	return EvalPolStr(obj, item, der);
}
void method_rect(int g, int n, double a, double b, vector<double>& X, int s, vector<double>& Y, const char* equation_str, double e, bool is_Left)
{
	double I = 0, h, result = 0, S, eps = 1;
	int counter = 1;

	switch (g)
	{
	case 1: //Равномерная сетка
		h = (b - a) / n;

		if (is_Left) //Формула левосторонних прямоугольников
		{
			for (int i = 0; i < n; i++)
			{
				if (s == 1) //Табличная функция
					I += Y[i];
				else //Аналитическая функция
					I += F(equation_str, a + h * i);
			}
		}
		else //Формула правосторонних прямоугольников
		{
			for (int i = 0; i < n; i++)
			{
				if (s == 1) //Табличная функция
					I += Y[i+1];
				else //Аналитическая функция
					I += F(equation_str, a + h * (i+1));
			}
		}
		I *= h;
		break;
	case 2: //Неравномерная сетка
		if (is_Left) //Формула левосторонних прямоугольников
		{
			for (int i = 0; i < n; i++)
			{
				h = X[i + 1] - X[i];
				if (s == 1) //Табличная функция
					I += Y[i] * h;
				else //Аналитическая функция
					I += F(equation_str, X[i]) * h;
			}
		}
		else //Формула правосторонних прямоугольников
		{
			for (int i = 0; i < n; i++)
			{
				h = X[i + 1] - X[i];
				if (s == 1) //Табличная функция
					I += Y[i+1] * h;
				else //Аналитическая функция
					I += F(equation_str, X[i+1]) * h;
			}
		}
		break;
	case 3: //Динамическая сетка
		h = (b - a) / n;

		if (is_Left) //Формула левосторонних прямоугольников
		{
			for (double i = a; i <= b - h; i = i + h)
			{
				I += F(equation_str, i);
			}
		}
		else //Формула правосторонних прямоугольников
		{
			for (double i = a + h; i <= b; i = i + h)
			{
				I += F(equation_str, i);
			}
		}
		S = I;
		I *= h;

		while (e < eps)
        {
            h /= 2; //Дробление шага
			result = S;
			for (double i = a + h; i <= b - h; i = i + h * 2) //Вычисление интеграла на новых точках
            {
				result += F(equation_str, i);
            }
            S = result;
			result *= h;
            if (fabs(result) > e / 2) // Защита от деления на 0
				eps = fabs((result - I) / result);
            else 
				eps = fabs(result - I);
            I = result;
            counter++;
        } 
        break;
	}

	Print_in_file(1, I, eps, counter, g, is_Left);
}
void method_trapez(int g, int n, double a, double b, vector<double>& X, int s, vector<double>& Y, const char* equation_str, double e)
{
	double I = 0, h, eps = 1, result, S, temp;
	int counter = 1;
	switch (g)
	{
	case 1: //Равномерная сетка
		h = (b - a) / n;
		for (int i = 1; i < n; i++)
		{
			if (s == 1) //Табличная функция
				I += Y[i];
			else //Аналитическая функция
				I += F(equation_str, a + h * i);
		}
		I *= 2;
		if (s == 1) //Табличная функция
			I += Y[0] + Y[n];
		else //Аналитическая функция
			I += F(equation_str, a) + F(equation_str, b);

		I *= h / 2;
		break;
	case 2: //Неравномерная сетка
		for (int i = 0; i < n; i++)
		{
			if (s == 1) //Табличная функция
				I += (X[i + 1] - X[i]) * (Y[i] + Y[i + 1]);
			else //Аналитическая функция
				I += (X[i + 1] - X[i]) * (F(equation_str, X[i]) + F(equation_str, X[i + 1]));
		}
		I *= 0.5;
		break;
	case 3: //Динамическая сетка
		h = (b - a) / n;

		for (int i = 1; i < n; i++)
		{
			I += F(equation_str, a + h * i);
		}

		I *= 2;
		I += F(equation_str, a) + F(equation_str, b);
		S = I;
		I *= h / 2;

		while (e < eps)
		{
			h /= 2; //Дробление шага
			result = S;
			temp = 0;
			for (double i = a + h; i < b - h / 2; i = i + h * 2)
			{
				temp += F(equation_str, i);
			}
			result += 2 * temp;
			S = result;
			result *= h / 2;

			if (fabs(result) > e / 2)
				eps = fabs((result - I) / result); // Защита от деления на 0
			else
				eps = fabs(result - I);

			I = result;
			counter++;
		}
		break;
	}

	Print_in_file(2, I, eps, counter, g, true);
}
void method_Simpson(int g, int n, double a, double b, vector<double>& X, int s, vector<double>& Y, const char* equation_str, double e)
{
	double I = 0, temp = 0, result = 0, S = 0, S1 = 0, S2 = 0, S3 = 0, eps = 1;
	double hR = 0, hR_next = 0, yR = 0, yR_next = 0;
	int m = n / 2, counter = 1;
	double h;

	switch (g)
	{
	case 1: //Равномерная сетка
		h = (b - a) / n;
		if (s == 1) //Табличная функция
			I += Y[0] + Y[n];
		else //Аналитическая функция
			I += F(equation_str, a) + F(equation_str, b);

		for (int i = 0; i < m; i++)
		{
			if (s == 1) //Табличная функция
				S += Y[2 * i + 1];
			else //Аналитическая функция
				S += F(equation_str, a + h * (2.0 * i + 1));
		}
		S *= 4;
		I += S;

		for (int i = 1; i < m; i++)
		{
			if (s == 1) //Табличная функция
				S1 += Y[2 * i];
			else //Аналитическая функция
				S1 += F(equation_str, a + h * (2.0 * i));
		}
		S1 *= 2;
		I += S1;
		I *= h / 3;

		break;
	case 2: //Неравномерная сетка
		for (int i = 0; i < n/2; i++)
		{
			hR = X[i * 2 + 1] - X[i * 2];
			hR_next = X[i * 2 + 2] - X[i * 2 + 1];
			if (s == 1) //Табличная функция
			{
				temp += hR_next * (2 * hR - hR_next) * Y[i * 2];
				temp += pow((hR_next + hR), 2) * Y[i * 2 + 1];
				temp += hR * (2 * hR - hR) * Y[i * 2 + 2];
			}
			else //Аналитическая функция
			{
				yR_next = F(equation_str, X[i * 2 + 2]);
				temp += hR_next * (2 * hR - hR_next) * yR;
				temp += pow((hR_next + hR), 2) * F(equation_str, X[i * 2 + 1]);
				temp += hR * (2 * hR_next - hR) * yR_next;
				yR = yR_next;
			}
			temp *= (hR_next + hR) / (6 * hR_next * hR);
			I += temp;
			temp = 0;
		}
		break;
	case 3: //Динамическая сетка
		h = (b - a) / n;
		S1 += F(equation_str, a) + F(equation_str, b);
		for (int i = 0; i < m; i++)
		{
			S2 += F(equation_str, a + h * (2.0 * i + 1));
		}
		for (int i = 1; i < m; i++)
		{
			S3 += F(equation_str, a + h * (2.0 * i));
		}
		I += S1 + 4 * S2 + 2 * S3;
		I *= h / 3;

		while (e < eps)
		{
			h /= 2; //Дробление шага
			S3 += S2;
			S2 = 0;
			m *= 2;
			for (int i = 0; i < m; i++)
			{
				S2 += F(equation_str, a + h * (2.0 * i + 1));
			}
			result = S1 + 4 * S2 + 2 * S3;
			result *= h / 3; 

			if (fabs(result) > e / 2)
				eps = fabs((result - I) / result); // Защита от деления на 0
			else
				eps = fabs(result - I);

			I = result;
			counter++;
		}
		break;
	}

	Print_in_file(3, I, eps, counter, g, true);
}
void method_Cheb(int m, int n, double a, double b, const char* equation_str)
{
	if (n <= 1 || n == 8 || n >= 10)
	{
		std::string Error = "Некоректные входные данные для метода Чебышева";
		throw Error;
	}

	//double q[7][7];
	//double* q2[7];

	double** arr = new double* [7];
	for (int i = 0; i < 7-1; i++) // n < 8
	{
		arr[i] = new double[i + 2];
	}
	arr[6] = new double[9];// n = 9

	arr[0][0] = 0.577350;  //
	arr[0][1] = -0.577350; // n=2

	arr[1][0] = 0.707107;  //
	arr[1][1] = 0;		   // n=3
	arr[1][2] = -0.707107; //

	arr[2][0] = 0.794654;  //
	arr[2][1] = 0.187592;  //
	arr[2][2] = -0.187592; // n=4
	arr[2][3] = -0.794654; //

	arr[3][0] = 0.832498;  //
	arr[3][1] = 0.374541;  //
	arr[3][2] = 0;		   // n=5
	arr[3][3] = -0.374541; //
	arr[3][4] = -0.832498; //

	arr[4][0] = 0.866247;  //
	arr[4][1] = 0.422519;  //
	arr[4][2] = 0.266635;  //
	arr[4][3] = -0.266635; // n=6
	arr[4][4] = -0.422519; //
	arr[4][5] = -0.866247; //

	arr[5][0] = 0.883862;  //
	arr[5][1] = 0.529657;  //
	arr[5][2] = 0.323912;  //
	arr[5][3] = 0;		   // n=7
	arr[5][4] = -0.323912; //
	arr[5][5] = -0.529657; //
	arr[5][6] = -0.883862; //

	arr[6][0] = 0.911589;  //
	arr[6][1] = 0.601019;  //
	arr[6][2] = 0.528762;  //
	arr[6][3] = 0.167906;  //
	arr[6][4] = 0;         // n=9
	arr[6][5] = -0.167906; //
	arr[6][6] = -0.528762; //
	arr[6][7] = -0.601019; //
	arr[6][8] = -0.911589; //

	double I = 0;
	double X;
	for (int i = 0; i < n; i++)
	{
		if (n < 8)
		{
			X = (a + b) / 2 + ((b - a) / 2) * arr[n - 2][i];
			I += F(equation_str, X);
		}
		else
		{
			X = (a + b) / 2 + ((b - a) / 2) * arr[n - 3][i];
			I += F(equation_str, X);
		}
	}
	I *= ((b - a) / n);

	ofstream fout("Result.txt");
	fout << "\t\t\tМетод Чебышева:\n";
	fout << "Значение интеграла: " << I << "\n";
	fout << "Абсциссы точек интегрирования:\n";
	for (int i = 0; i < n; i++)
	{
		if (n < 8)
			fout << arr[n - 2][i] << "\t";
		else
			fout << arr[n - 3][i] << "\t";
	}
	fout.close();

	for (int i = 0; i < 7; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}
void Print_in_file(int m, double I, double eps, int counter, int g, bool is_Left)
{
	ofstream fout("Result.txt");

	switch (m)
	{
	case 1:
		if (is_Left)
			fout << "\t\t\tМетод левосторонних прямоугольников:\n";
		else
			fout << "\t\t\tМетод правосторонних прямоугольников:\n";
		break;
	case 2:
		fout << "\t\t\tМетод трапеций:\n";
		break;
	case 3:
		fout << "\t\t\tМетод Симпсона:\n";
		break;
	}

	fout << "Значение интеграла: " << I;
	if (g == 3)
	{
		fout << "\nКоличество итераций: " << counter;
		fout << "\nДостигнутая точность: " << eps;
	}
	fout.close();
}