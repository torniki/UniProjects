#include <iostream>
#include <cmath>
#include <time.h>
#include "matrix.h"
#include <string>
#include <iomanip>

using namespace std;

namespace mtr
{
	unsigned matrix::IDS = 0;

	//Конструкторы и деструктор
	matrix::matrix() : matrix(0)
	{
	}

	matrix::matrix(unsigned  n) : matrix(n, n)
	{
	}

	matrix::matrix(unsigned  n, bool value)
	{
		if (n == 0)
		{
			this->n = NULL;
			this->m = NULL;
			array = nullptr;
		}
		else
		{
			this->n = n;
			this->m = n;
			array = new double[n * m];
			for (int i = 0; i < n * n; i++)
			{
				array[i] = 0;
			}
			if (value == true)
				for (int i = 0; i < n; i++)
				{
					array[i * n + i] = 1;
				}
		}
		matr_id = ++IDS;
	}

	matrix::matrix(unsigned  n, unsigned m)
	{
		if (n == 0 || m == 0)
		{
			this->n = NULL;
			this->m = NULL;
			array = nullptr;
		}
		else
		{
			this->n = n;
			this->m = m;
			array = new double[n * m];
			init();
		}

		matr_id = ++IDS;

#ifdef _DEBUG
		cout << "\nКонструктор для иницализации матрицы: " << matr_id << endl;
#endif
	}

	matrix::matrix(unsigned nm, double* matr) : matrix(nm, nm, matr)
	{
	}

	matrix::matrix(unsigned n, unsigned m, double* matr)
	{
		if (n == 0 || m == 0)
		{
			this->n = 0;
			this->m = 0;
			array = nullptr;
		}
		else
		{
			this->n = n;
			this->m = m;
			array = matr;
		}
		matr_id = ++IDS;
#ifdef _DEBUG
		cout << "\nКонструктор с заданными параметрами: " << matr_id << endl;
#endif
	}

	matrix::matrix(unsigned n, unsigned m, UserFuncMtr user_func) : matrix(n, m)
	{
		for (unsigned r = 0; r < n; r++)
			for (unsigned c = 0; c < m; c++)
				array[this->n * r + c] = user_func(n, m, r, c);
#ifdef _DEBUG
		cout << "\nКонструктор с заданными параметрами: " << matr_id << endl;
#endif
	}
	matrix::matrix(unsigned nm, UserFuncMtr user_func) : matrix(nm, nm, user_func)
	{

	}

	matrix::matrix(const matrix& other)
	{
		n = other.n;
		m = other.m;
		array = new double[other.n * other.m];
		for (unsigned i = 0; i < other.n * other.m; i++)
			array[i] = other.array[i];
		matr_id = ++IDS;

#ifdef _DEBUG
		cout << "\nКонструктор копирования: " << matr_id << endl;
#endif
	}

	matrix::matrix(matrix&& other) : n(0), m(0), array(nullptr)
	{
		swap(n, other.n);
		swap(m, other.m);
		swap(array, other.array);
		matr_id = ++IDS;
#ifdef _DEBUG
		cout << "Вызван конструктор перемещения, объект с номером " << other.matr_id << " перемещен в объект " << matr_id << endl;
#endif
	}

	matrix::~matrix()
	{
		delete[] array;
		array = nullptr;
#ifdef _DEBUG
		cout << "\nДеструктор сработал,удалена матрица: " << matr_id << endl;
#endif
	}

	/////////////////////////////

	//Вывод, заполнение, копирование, перемещение
	std::ostream& operator<<(std::ostream& out, const matrix& other) //Поток данных
	{
		if (other.isNULL())
		{
			int matrWidth = out.width();
			for (unsigned i = 0; i < other.n; i++) {
				for (unsigned j = 0; j < other.m; j++)
					out << setw(matrWidth) << other.array[i * other.m + j];
				out << "\n";
			}
			out << "\n";
			return out;
		}
		else
		{
			string errMSG = "Исключение! Матрица с номером " + std::to_string(other.matr_id) + "пуста!";
			throw errMSG;
		}
	}

	matrix& matrix::init() //Заполнение случайными числами
	{
		for (unsigned i = 0; i < n * m; i++)
			array[i] = 0;

		return *this;
	}

	matrix& matrix::operator=(const matrix& other)
	{
		if (this == &other)		//Проверка на самокопирование
			return *this;

		if (array != nullptr)
		{
			delete[] array;
			array = nullptr;
		}

		n = other.n;
		m = other.m;

		array = new double[n * m];

		for (unsigned i = 0; i < n * m; i++)
			array[i] = other.array[i];

		return *this;
	}

	matrix& matrix::operator=(matrix&& other)
	{
		if (this == &other)		//Проверка на самокопирование
			return *this;

		delete[] array;
		array = nullptr;

		swap(n, other.n);
		swap(m, other.m);
		swap(array, other.array);
		return *this;
	}

	//Перегрузка операторов префиксной формы
	matrix& matrix::operator+=(const matrix& other)
	{
		if (sum(other) && isNULL() && other.isNULL())
		{
			for (unsigned i = 0; i < n * m; i++)
			{
				array[i] += other.array[i];
			}
			return *this;
		}
		else
		{
			string errMSG = "Исключение! Матрицы с номерами " + to_string(matr_id) + " и " + to_string(other.matr_id) + " нельзя складывать! (матрицы пусты, или разного размера)";
			throw errMSG;
		}
	}

	matrix& matrix::operator-=(const matrix& other)
	{
		if (sum(other) && isNULL() && other.isNULL())
		{
			for (unsigned i = 0; i < n * m; i++)
			{
				array[i] -= other.array[i];
			}
			return *this;
		}
		else
		{
			string errMSG = "Исключение! Матрицы с номерами " + to_string(matr_id) + " и " + to_string(other.matr_id) + " нельзя вычитать! (матрицы пусты, или разного размера)";
			throw errMSG;
		}
	}

	matrix& matrix::operator*=(const matrix& other)
	{
		if (isNULL() && other.isNULL())
		{
			if (mult(other))
			{
				double* temp = new double[n * other.m];
				for (unsigned i = 0; i < n * other.m; i++)
					temp[i] = 0.0;
				for (unsigned i = 0; i < n; ++i)
					for (unsigned j = 0; j < other.m; ++j)
						for (unsigned k = 0; k < m; ++k)
							temp[i * other.m + j] += (array[i * m + k] * other.array[k * other.m + j]);
				delete[] array;
				m = other.m;
				array = temp;

				return *this;
			}
			else
			{
				string errMSG = "Исключение! Матрицы с номерами " + to_string(matr_id) + " и " + to_string(other.matr_id) + " нельзя умножать! (не выполняется условие m == other.n)";
				throw errMSG;
			}
		}
		else
		{
			string errMSG = "Исключение! Матрицы с номерами " + to_string(matr_id) + " и " + to_string(other.matr_id) + " нельзя умножать! (матрицы пусты)";
			throw errMSG;
		}
	}

	matrix& matrix::operator*=(double k)
	{
		if (isNULL())
		{
			for (unsigned i = 0; i < n * m; i++)
			{
				array[i] *= k;
			}
			return *this;
		}
		else
		{
			string errMSG = "Исключение! Матрица с номером " + to_string(matr_id) + " пуста!";
			throw errMSG;
		}
	}

	matrix& matrix::Transpose()
	{
		double* matr_temp = new double[n * m];

		for (unsigned int i = 0; i < m; i++)
		{
			for (unsigned int j = 0; j < n; j++)
				matr_temp[j * m + i] = array[i * n + j];
		}

		delete[] array;
		array = matr_temp;
		swap(m, n);

		return *this;
	}

	//Перегрузка операторов
	matrix operator+(const matrix& a, const matrix& b)
	{
		return matrix(a) += b;
	}

	matrix operator-(const matrix& a, const matrix& b)
	{
		return matrix(a) -= b;
	}

	matrix operator*(const matrix& a, const matrix& b)
	{
		return matrix(a) *= b;
	}

	matrix operator*(const matrix& a, double k)
	{
		return matrix(a) *= k;
	}

	//Методы работы с матрицей (проверки и max, min)
	bool matrix::mult(const matrix& other) const
	{
		if (isNULL() && other.isNULL())
			return m == other.n;
		else
		{
			string errMSG = "Исключение! Матрицы с номерами " + to_string(matr_id) + " и " + to_string(other.matr_id) + " пусты!";
			throw errMSG;
		}
	}

	bool matrix::sum(const matrix& other) const
	{
		if (isNULL() && other.isNULL())
			return n == other.n && m == other.m;
		else
		{
			string errMSG = "Исключение! Матрицы с номерами " + to_string(matr_id) + " и " + to_string(other.matr_id) + " пусты!";
			throw errMSG;
		}
	}

	double matrix::max() const
	{
		if (isNULL())
		{
			double max = array[0];
			for (unsigned i = 1; i < n * m; i++)
				if (max < array[i])
					max = array[i];

			return max;
		}
		else
		{
			string errMSG = "Исключение! Матрица с номером " + to_string(matr_id) + " пуста!";
			throw errMSG;
		}
	}

	double matrix::min() const
	{
		if (isNULL())
		{
			double min = array[0];
			for (unsigned i = 1; i < n * m; i++)
				if (min > array[i])
					min = array[i];

			return min;
		}
		else
		{
			string errMSG = "Исключение! Матрица с номером " + to_string(matr_id) + " пуста!";
			throw errMSG;
		}
	}

	bool matrix::isNULL() const
	{
		return !(array == nullptr);
	}

	//Конструкторы строк для подкласса
	matrix::MatrixRow::MatrixRow(const matrix* other, unsigned Row)
	{
		n = other->n;
		m = other->m;
		this->Row = Row;
		this->MatrRow = other->array;
	}

	matrix::MatrixRow::MatrixRow(matrix* other, unsigned Row)
	{
		n = other->n;
		m = other->m;
		this->Row = Row;
		this->MatrRow = other->array;
	}

	//Оператор индексирования
	double& matrix::MatrixRow::operator[](unsigned index)
	{
		if (index <= m && index >= 0)
			return MatrRow[Row * m + index];
		else
		{
			string errMSG = "Исключение! Выход за границы матрицы";
			throw errMSG;
		}
	}

	double matrix::MatrixRow::operator[](unsigned index) const
	{
		if (index <= m && index >= 0)
			return MatrRow[Row * m + index];
		else
		{
			string errMSG = "Исключение! Выход за границы матрицы ";
			throw errMSG;
		}
	}

	matrix::MatrixRow matrix::operator[](unsigned index)
	{
		if (index <= m && index >= 0)
			return MatrixRow(this, index);
		else
		{
			string errMSG = "Исключение! Выход за границы матрицы " + to_string(matr_id);
			throw errMSG;
		}
	}

	const matrix::MatrixRow matrix::operator[](unsigned index) const {
		if (index <= m && index >= 0)
			return MatrixRow(this, index);
		else
		{
			string errMSG = "Исключение! Выход за границы матрицы " + to_string(matr_id);
			throw errMSG;
		}
	}
}