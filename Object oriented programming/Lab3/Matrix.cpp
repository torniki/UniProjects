#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <time.h>
#include <string>
#include "Matrix.h"

namespace Mine 
{
	unsigned Matrix::IDS = 0;

	//Конструкторы и деструктор
	Matrix::Matrix() 
	{
		this->m = NULL;
		this->n = NULL;
		data = nullptr;
		global_id = ++IDS;

	#ifdef _DEBUG
		std::cout << "+Matrix " << global_id << std::endl;
	#endif
	}
	
	Matrix::Matrix(unsigned int  m) : Matrix(m, m) {}

	Matrix::Matrix(unsigned int  m, unsigned int n) : Matrix() 
	{
		if (m != 0 && n != 0) {
			this->m = m;
			this->n = n;
			data = new double[m * n]();

			for (unsigned int i = 0; i < m * n; i++) {
				data[i] = (double)rand() / (double)RAND_MAX * 100;
			}
		}
	}

	Matrix::Matrix(unsigned int  m, unsigned int n, double(*myfunc)(unsigned int i, unsigned int j)) :Matrix(m, n) 
	{
		for (unsigned int i = 0; i < m; i++) {
			for (unsigned int j = 0; j < n; j++) {
				data[i * n + j] = myfunc(i, j);
			}
		}
	}
	Matrix::Matrix(unsigned int m, unsigned int n, double* data) :Matrix(m, n) 
	{
		if (data != nullptr)
		{
			std::copy(data, data + (m * n), this->data);
		}
		else throw "Data is empty!";
	}
	Matrix::Matrix(const Matrix& other) :Matrix() 
	{
		if (!other.isNULL()) 
		{
			*this = other;
		#ifdef _DEBUG
			std::cout << "COPY CONSTRUCTOR. Matrix  " << other.global_id << " = " << global_id << std::endl;
		#endif
		}
		else throw "ERROR IN COPY CONSTRUCTOR! Matrix " + std::to_string(global_id) + " = " + std::to_string(other.global_id);
	}
	
	Matrix::Matrix(Matrix&& other) noexcept :m(0), n(0), data(nullptr) 
	{
		*this = std::move(other);
		global_id = ++IDS;
		#ifdef _DEBUG
			std::cout << "MOVE CONSTRUCTOR. Matrix  " << other.global_id << " -> " << global_id << std::endl;
		#endif
	}
	Matrix::~Matrix() 
	{
		delete[] data;
		#ifdef _DEBUG
			std::cout << /*"\033[A\033[K"  <<*/ "\n-Matrix " << global_id /*<< "\033[B\r"*/ << std::endl;
		#endif
	}

	Matrix& Matrix::Transpose() 
	{
		double* temp = new double[m * n]();
		std::copy(data, data + (m * n), temp);

		for (unsigned int i = 0; i < m; i++) 
		{
			for (unsigned int j = 0; j < n; j++)
				data[j * m + i] = temp[i * n + j];
		}

		std::swap(m, n);
		delete[] temp;
		return*this;
	}
	
	Matrix Matrix::GetTranspose() 
	{
		Matrix matr_temp;
		matr_temp.data = new double[m * n]();
		std::copy(data, data + (m * n), matr_temp.data);

		matr_temp.m = this->m;
		matr_temp.n = this->n;

		for (unsigned int i = 0; i < m; i++) 
		{
			for (unsigned int j = 0; j < n; j++)
				matr_temp.data[j * m + i] = data[i * n + j];
		}
		return matr_temp;
	}

	//Перегрузка операторов префиксной формы
	Matrix& Matrix::operator=(const Matrix& other) 
	{
		if (!other.isNULL() && other.m != 0 && other.n != 0) 
		{
			if (!this->sum(other) || !(this->m == other.n && this->n == other.m)) 
			{
				if (this->data != nullptr)
					delete[] this->data;

				this->m = other.m;
				this->n = other.n;

				data = new double[other.m * other.n];
			}
			std::copy(other.data, other.data + (n * m), this->data);
			return *this;
		}
		else throw "ERROR IN = OPERATOR! Matrix " + std::to_string(global_id) + " += " + std::to_string(other.global_id);
	}

	Matrix& Matrix::operator=(Matrix&& other) noexcept 
	{
		std::swap(m, other.m);
		std::swap(n, other.n);
		std::swap(data, other.data);
		return *this;
	}
	
	Matrix& Matrix::operator+=(const Matrix& other) 
	{
		if (this->sum(other) && !this->isNULL() && !other.isNULL()) 
		{
			for (unsigned int i = 0; i < m * n; i++) 
			{
				data[i] += other.data[i];
			}
			return *this;
		}
		else throw "ERROR IN += OPERATOR! Matrix " + std::to_string(global_id) + " += " + std::to_string(other.global_id);
	}

	Matrix& Matrix::operator-=(const Matrix& other) 
	{
		if (this->sum(other) && !this->isNULL() && !other.isNULL()) 
		{
			for (unsigned int i = 0; i < m * n; i++) {
				data[i] -= other.data[i];
			}
			return *this;
		}
		else throw "ERROR IN -= OPERATOR! Matrix " + std::to_string(global_id) + " -= " + std::to_string(other.global_id);
	}

	Matrix& Matrix::operator*=(const Matrix& other) 
	{
		if (this->mult(other) && !this->isNULL() && !other.isNULL()) 
		{
			double* temp = new double[this->m * other.n]();
			for (unsigned int i = 0; i < this->m; ++i) 
			{
				for (unsigned int j = 0; j < other.n; ++j) 
				{
					for (unsigned int k = 0; k < this->n; ++k)
						temp[i * other.n + j] += (data[i * this->n + k] * other.data[k * other.n + j]);
				}
			}
			delete[] this->data;
			n = other.n;
			data = temp;

			return *this;
		}
		else throw "ERROR IN *= OPERATOR! " + std::to_string(global_id) + " *= " + std::to_string(other.global_id);
	}
	Matrix& Matrix::operator*=(double k) 
	{
		if (!this->isNULL()) 
		{
			for (unsigned int i = 0; i < m * n; i++) 
			{
				data[i] *= k;
			}
			return *this;
		}
		else throw  "ERROR IN *= OPERATOR! " + std::to_string(global_id);
	}

	//Перегрузка операторов 
	Matrix operator+(const Matrix& a, const Matrix& b) 
	{
		return std::move(Matrix(a) += b);
	}
	
	Matrix operator-(const Matrix& a, const Matrix& b) 
	{
		return std::move(Matrix(a) -= b);
	}
	
	Matrix operator*(const Matrix& a, const Matrix& b) 
	{
		return std::move(Matrix(a) *= b);
	}
	
	Matrix operator*(const Matrix& a, double k) 
	{
		return std::move(Matrix(a) *= k);
	}
	
	std::ostream& operator<<(std::ostream& out, const Matrix& other) 
	{
		if (!other.isNULL()) 
		{
			int pl = out.width() == 0 ? 3 : out.width();
			int c = out.precision() == 6 ? 1 : out.precision(); // Все равно не работает!
			for (unsigned int i = 0; i < other.m; i++) 
			{
				for (unsigned int j = 0; j < other.n; j++)
					out << std::fixed << std::setprecision(c) << std::setw(pl) << other.data[i * other.n + j];
				out << "\n";
			}
			out << "\n";
			return out;
		}
		else throw "ERROR IN cout OPERATOR! " + std::to_string(other.global_id);
	}

	//Методы работы с матрицей
	bool Matrix::mult(const Matrix& other) const 
	{
		return this->n == other.m;
	}
	
	bool Matrix::sum(const Matrix& other) const 
	{
		return this->m == other.m && this->n == other.n;
	}
	
	bool Matrix::isNULL() const 
	{
		return data == nullptr;
	}
	
	double Matrix::max() const 
	{
		if (!this->isNULL()) 
		{
			double max = data[0];
			for (unsigned int i = 1; i < m * n; i++) 
			{
				if (max < data[i])
					max = data[i];
			}
			return max;
		}
		else throw  "ERROR IN max() FUNCTION " + std::to_string(global_id);
	}

	double  Matrix::min() const 
	{
		if (!this->isNULL()) 
		{
			double min = data[0];
			for (unsigned int i = 1; i < m * n; i++) 
			{
				if (min > data[i])
					min = data[i];
			}
			return min;
		}
		else throw  "ERROR IN min() FUNCTION" + std::to_string(global_id);
	}

	unsigned int Matrix::GetN() const
	{
		return this->n;
	}

	unsigned int Matrix::GetM() const
	{
		return this->m;
	}

	Matrix& Matrix::SetN(int n)
	{
		this->n = n;
		return *this;
	}

	Matrix& Matrix::SetM(int m)
	{
		this->m = m;
		return *this;
	}

	unsigned int Matrix::GetID() const
	{
		if (!this->isNULL()) 
		{
			return this->global_id;
		}
		else throw "ERROR IN GetID!";
	}

	std::string Matrix::GetType() const 
	{
		return std::string("Matrix ");
	}


	//Оператор индексирования
	Matrix::matrixRow Matrix::operator[](unsigned int ind) 
	{
		if (ind >= m) throw "ERROR IN [] OPERATOR! Matrix " + std::to_string(global_id);
		else return matrixRow(this, ind);
	}

	const Matrix::matrixRow Matrix::operator[](unsigned int ind) const 
	{
		if (ind >= m) throw "ERROR IN [] OPERATOR! Matrix " + std::to_string(global_id);
		else return matrixRow(this, ind);
	}

	Matrix::matrixRow::matrixRow(const Matrix* other, unsigned R) 
	{
		m = other->m;
		n = other->n;
		this->R = R;
		this->data = other->data;
		matr_id = other->global_id;
	}

	double& Matrix::matrixRow::operator[](unsigned int ind) 
	{
		if (ind >= n) throw "ERROR IN [] OPERATOR! Matrix " + std::to_string(matr_id);
		else return data[R * n + ind];
	}

	double const Matrix::matrixRow::operator[](unsigned int ind) const
	{
		if (ind >= n) throw "ERROR IN [] OPERATOR! Matrix " + std::to_string(matr_id);
		else return data[R * n + ind];
	}
};







