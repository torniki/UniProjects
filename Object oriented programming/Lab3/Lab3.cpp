#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include "Matrix.h"
#include <time.h>
#include <string>

using namespace std;
using namespace Mine;

int myFirstFunc(unsigned int i, unsigned int j) {
	return i + j;
}

int mySecondFunc(unsigned int i) {
	return i * 3;
}

int main()
{
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "rus");

	double* temp = new double[6]{ 1, 2, 3, 4, 5, 6 };

	Matrix m(3, 3);
	cout << setw(10) << m;
	Matrix m1 = m.GetTranspose();
	cout << setw(10) << m1;
	Vector v(3);
	cout << v;
	v.GetType()
	Vector v1(5);
	Vector v2(5);
	Vector c;
	c = v1 + v2;
	cout << c;

	v = v1;
	cout << v;
	Vector v1(3);
	cout << v1;

	cout << v.GetType();



	v = (Matrix)v;
	cout << "\t" << v.GetType() << endl;
	v += m;
	cout << v;
	v[1] += 5;

	v1 = m1;
	cout << v1;

	Vector v1(std::move(v));//Вызывается конструктор копирования для матрицы?!?!?!?!
	cout << v1;

	Vector v2(3);
	cout << v2.GetType() << endl;
	cout << v2;
	v2 += m;
	cout << v2.GetType() << endl;
	cout << v2;

	return 0;
}

