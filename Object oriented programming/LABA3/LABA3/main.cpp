#include<iostream>
#include "matr.h"
#include "vect.h"
int main()
{
	Matrix vector;// ���������� �������
	std::cout << vector.getType();// ��������� ���� v1 � ������� Vector
	Matrix& m1 = vector;// ������ ������� � �������
	std::cout << m1.getType();
};