#include "PolStr.h"
#include "solution.h"
#include<math.h>
	//Функции поиска корня:
using namespace std;

solution::solution(double a, double b, double eps){};
double Dichotomy(char* polstr, double a, double b, double eps) 
	{
		double c;
		while ((b - a) / 2 > eps) {
			c = (a + b) / 2;
			if ((EvalPolStr(polstr, a) * EvalPolStr(polstr, c)) > 0) a = c;
			else b = c;
		}
		return c;
	}

double Chord(char* polstr, double a, double b, double eps) 
	{
		double c;
		while ((b - a) / 2 > eps) {
			c = a - (EvalPolStr(polstr, a) / ((EvalPolStr(polstr, b) - (EvalPolStr(polstr, a)) * (b - a));
			if ((EvalPolStr(polstr, a) * EvalPolStr(polstr, c)) > 0) a = c;
			else b = c;
		}
		return c;
	}

void GoldS(char* polstr, double a, double b, double eps) 
	{
		double x1, x2; // Точки, делящие текущий отрезок в отношении золотого сечения
		const double goldconst = (sqrt(5) + 1) / 2;
		while (fabs(b - a) > eps) {
			x1 = a + (b - a) / goldconst;
			x2 = a + (b - a) / (goldconst* goldconst);
			if (EvalPolStr(polstr, x1) <= EvalPolStr(polstr, x2)) // Условие для поиска максимума
				a = x1;
			else
				b = x2;
		} // Выполняем, пока не достигнем заданной точности
		//cout << "(" << (a + b) / 2 << ", " << f((a + b) / 2) << ")\n";
	}

void Newton(char* polstr, double a, double b, double eps)
{
	double xa = EvalPolStr(polstr, a);
	double xb = EvalPolStr(polstr, b);
	double x0,xNext;

	int c = a - xa / (xb - xa) * (b - a);
	if (EvalPolStr(polstr, a)*EvalPolStr(polstr, c) <= 0)
	{
		x0 = a;
	}
	else
		x0 = b;
	do
	{

	} while ();
}

void Combo(char*, double a, double b, double eps){}

void Itera(char*, double a, double b, double eps)
{

}