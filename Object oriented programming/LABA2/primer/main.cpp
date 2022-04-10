#include <iostream>

using namespace std;

inline void sep(bool b = true)
{
	if (b) cout << endl;
	cout << " - - - - - - - - - - - - - - - \n\n";
}

inline void sep_title(const char* title, bool b = true)
{
	if (b) cout << endl;
	cout << " - - - - - - - - - - - - - - - \n" << " << " << title << " >>\n\n";
}

inline void new_line(int n = 1)
{
	for (int i = 0; i < n; i++) cout << endl;
}



#include "Vector.h"

using namespace some;

// Пример пользовательской функции,
// которая заполняет четные элементы '0', а нечетные - '1'
double init_01(size_t i)
{
	return i % 2;
}



int main()
{
	double data[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	Vector
		v0,             // Вызов конструктора без параметров, срабатывает Vector(0, nullptr)
		v1(8),          // Срабатывает Vector(8, nullptr)
		v2(8, data),    // Срабатывает Vector(8, data)
		v3(8, init_01); // Срабатывает Vector(8, init_func)

	// При этом если вручную отправлять вторым аргументом nullptr,
	// то возникает конфликт, т.к. есть:
	//
	// Vector(size_t, double*)
	// Vector(size_t, init_func)
	//
	// Оба этих конструктора принимают вторым аргументом указатели...
	//
	// Предполагается, что пользователь не будет проварачивать данный
	// случай для создания пустого вектора, а воспользвуется способом
	// как для v0 ну или явно задаст Vector(0);

	sep();

	Vector::setStreamWidth(4);

	cout << v0 << v1 << v2 << v3;

	sep(false);
}
