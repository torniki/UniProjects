#include <iostream>
#include <math.h>

using namespace std;

double Func(double x) {
	return x * x - 9 * x + 14;
	//y=x^2-9x+14
	//y=x^(2*x-5)
}

//Функции поиска корня:
double Dichotomy(double (*f)(double), double a, double b, double eps) {
	double c,xa;
	while ((b - a) / 2 > eps) {
		c = (a + b) / 2;
		xa = f(a);
		if ((f(a) * f(c)) > 0) a = c;
		else b = c;
	}
	return c;
}
double Chord(double (*f)(double), double a, double b, double eps) {
	double c,xa,xb;
	while (fabs(b-a) > eps) {
		xa = f(a);
		xb = f(b);
		c = a-( xa / ( xb-xa ) * ( b - a ) );
		if ((xa * f(c)) > 0) a = c;
		else b = c;
	}
	return c;
}
void GoldS(double (*f)(double), double a, double b, double eps) {
	double x1, x2,xa,xb; // Точки, делящие текущий отрезок в отношении золотого сечения
	const double goldconst = (sqrt(5) + 1) / 2;
	while (fabs(b - a) > eps) {
		x1 = a + (b - a) / goldconst;
		x2 = a + (b - a) / (goldconst* goldconst);
		if (x2 - a = b - x1)
		{
			if (f(a) * f(x1) <= 0) // Условие для поиска максимума
				b = x1;
			else
				a = x2;
		}
	} // Выполняем, пока не достигнем заданной точности
	cout << "(" << (a + b) / 2 << ", " << f((a + b) / 2) << ")\n";
}
int main() {
	setlocale(LC_ALL, "rus");
	//Интервал, погрешность и корень:
	double a, b, eps, x;
	cout << "Интервал: ";
	cin >> a;
	cin >> b;
	//Проверка корректности интервала:
	
	cout << "Погрешность: ";
	cin >> eps;
	//Поиск решения:
	x = Dichotomy(Func, a, b, eps);
	cout << "Метод дихотомии x = " << x << endl;
	x = Chord(Func, a, b, eps);
	cout << "Метод хорд x = " << x << endl;
	GoldS(Func, a, b, eps);
	return 0;
}	

