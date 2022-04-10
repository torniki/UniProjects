#include <iostream>
#include <math.h>
#include "Matrix.h"
#include <time.h>
#include "windows.h"
#include <iomanip>

using namespace gromax;


double gen(unsigned int i, unsigned int j) {
	return i+j;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "ru");
	int k = 2; // ��������� ��������
	Matrix a(3, 3);
	Matrix b(3, 3);
	std::cout << b;
	b *= a;
	std::cout << b;
	std::cout << a.CheckForSum(b) << "\n";
	std::cout << a.CheckForMult(b) << "\n";
	a.print();
	std::cout << "����������� ��������:" << a.MtrMin() << "\n";
	b.print();
	std::cout << "������������ ��������:" << b.MtrMax() << "\n";
	Matrix h(std::move(b));
	std::cout << h;
	Matrix c(3, 3, gen);

	std::cout << std::setw(5) << c;
}