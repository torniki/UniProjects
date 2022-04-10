#include <iostream>
#include <math.h>
#include "matrix.h"
#include <time.h>
#include "windows.h"
#include <iomanip>

using namespace gromax;


double gen(unsigned int i, unsigned int j) {
	return i + j;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "ru");
	int k = 2; // ��������� ��������
	matrix a(3, 3);
	matrix b(3, 3);
	std::cout << b;
	b *= a;
	std::cout << b;
	/*cout << a.CheckForSum(b) << endl;
	cout << a.CheckForMult(b) << endl;
	a.print();
	cout << "����������� ��������:" << a.MtrMin() << endl;
	b.print();
	cout << "������������ ��������:" << b.MtrMax() << endl;*/
	matrix h(std::move(b));
	std::cout << h;
	matrix c(3, 3, gen);

	std::cout << std::setw(5) << c;
}