#include <locale.h>
#include <iostream>
#include "PolStr.h"

using namespace std;

int main()
{
	char function[] = "x*x + 1"; // �������� �������
	// ������ �� �������� x^2+1? ������ ��� ����� �������� ��� ���������� �����������. ���� ����� ���������� ����������� �������, �.�. �����������
	// ������� f(x)^g(x), �� � ������ ���� ����������� �������� �������� ������� f(x). ��������������, ���� ������ ������� ����� ��������� ��������,
	// ������� ���� ������ 0, �� ���������� ���������� �������������� �������. ������� ������� x^2+1 ����� ����������� ���������, � �� ����������� -
	// ������ � ��� ������, ���� �������� x �������������
	char *polstr = CreatePolStr(function, 0); // ����������� � �������� ������ (������ �������� = 0 ��������, ��� �������� ������� ���������)

	setlocale(LC_ALL, "russian");
	cout << "������� f(x) = " << function << endl;

	if (Error != ERR_OK)
	{
		cout << "������: " << Error << endl;
	}
	else
	{
		cout << "�������� �������� ������: " << polstr << endl;

		for (double x = -3; x <= 3; x += 1)
		{
			cout << "f(" << x << ") = " << EvalPolStr(polstr, x) << endl; // ��������� �������� �������, � ����� ������ � ������ �����������
			cout << "f'(" << x << ") = " << EvalPolStr(polstr, x, 1) << endl;
			cout << "f''(" << x << ") = " << EvalPolStr(polstr, x, 2) << endl;
		}

		delete[] polstr; // ������� CreatePolStr �������� ������������ ������, � ����� ����������
	}

	char function2[] = "x1*x2 + sin(x1) + cos(x2)"; // ������� ���������� ���������
	polstr = CreatePolStr(function2, 2); // ���������, ��� � ������� 2 ���������
	cout << endl << "������� f(x) = " << function2 << endl;

	if (Error != ERR_OK)
	{
		cout << "������: " << Error << endl;
	}
	else
	{
		double x[] = { 1, 1 };
		cout << "�������� �������� ������: " << polstr << endl;
		cout << "f(" << x[0] << "," << x[1] << ") = " << EvalPolStr(polstr, x) << endl; // ��������� �������� ������� � ����� x
		cout << "df/dx1|(" << x[0] << "," << x[1] << ") = " << EvalPolStr(polstr, x, 1, 1) << endl; // ��������� �������� ������� ����������� df/dx1 � ����� x
		cout << "df/dx2|(" << x[0] << "," << x[1] << ") = " << EvalPolStr(polstr, x, 1, 2) << endl; // ��������� �������� ������� ����������� df/dx2 � ����� x

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
