#include<iostream>
#include "matr.h"
#include "vect.h"
int main()
{
	Matrix vector;// объ€вление вектора
	std::cout << vector.getType();// получение типа v1 в консоль Vector
	Matrix& m1 = vector;// апкаст вектора в матрицу
	std::cout << m1.getType();
};