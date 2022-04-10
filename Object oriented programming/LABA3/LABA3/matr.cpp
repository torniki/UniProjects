#include "matr.h"
#include<iostream>
#include <string>
#include <iomanip>
#include<conio.h>

	unsigned IDS = 0;

	Matrix::Matrix(int r, int c, double(*gen)(unsigned int i, unsigned int j))
	{
		if (r == 0 || c == 0)
		{
			mtr_id = ++IDS;
			this->rows = NULL;
			this->cols = NULL;
			mtr = nullptr;

			std::cout << "Вызвался конструктор и создался объект " << mtr_id << std::endl;
		}
		else
		{
			mtr_id = ++IDS;
			this->rows = r;
			this->cols = c;
			mtr = new double[r * c];

			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
					mtr[i * c + j] = gen(i, j);
			}
			std::cout << "Вызвался конструктор и создался объект " << mtr_id << std::endl;
		}

	}

	Matrix::Matrix(int r, int c)
	{
		if (r == 0 || c == 0)
		{
			mtr_id = ++IDS;
			this->rows = NULL;
			this->cols = NULL;
			mtr = nullptr;

			std::cout << "Вызвался конструктор и создался объект " << mtr_id << std::endl;
		}
		else
		{
			mtr_id = ++IDS;
			this->rows = r;
			this->cols = c;
			mtr = new double[r * c];

			fill(r, c, mtr);
			std::cout << "Вызвался конструктор и создался объект " << mtr_id << std::endl;
		}

	}

	Matrix::Matrix(int s)
	{
		if (s == 0)
		{
			mtr_id = ++IDS;
			this->rows = NULL;
			this->cols = NULL;
			mtr = nullptr;

			std::cout << "Вызвался конструктор и создался объект " << mtr_id << std::endl;
		}
		else
		{
			mtr_id = ++IDS;
			this->rows = s;
			this->cols = s;
			mtr = new double[s * s];
			fill(s, s, mtr);
			std::cout << "Вызвался конструктор и создался объект " << mtr_id << std::endl;
		}
	}

	Matrix::~Matrix()
	{
		delete[] this->mtr;
		std::cout << "Вызвался деструктор и удалился объект " << mtr_id << std::endl;
		mtr_id = --IDS;
	}

	Matrix::Matrix(const Matrix& other)
	{
		mtr_id = ++IDS;
		this->rows = other.rows;
		this->cols = other.cols;
		this->mtr = new double[this->rows * this->cols];

		for (int i = 0; i < (this->rows * this->cols); i++)
		{
			this->mtr[i] = other.mtr[i];
		}

		std::cout << "Вызвался конструктор и скопировался объект " << mtr_id << std::endl;
	}

	Matrix::Matrix(Matrix&& other)
		:rows(0), cols(0), mtr(nullptr)
	{
		std::swap(rows, other.rows);
		std::swap(cols, other.cols);
		std::swap(mtr, other.mtr);
		mtr_id = ++IDS;
		std::cout << "Вызван конструктор перемещения, объект с номером " << other.mtr_id << " перемещен в объект " << mtr_id << std::endl;
	}


	void Matrix::print() const
	{
		std::cout << "\n" << std::endl;
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->cols; j++)
				std::cout << this->mtr[i * this->cols + j] << " ";
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	int Matrix::CheckForSum(const Matrix a) const
	{
		return ((this->rows == a.rows) && (this->cols == a.cols));
	}

	int Matrix::CheckForMult(const Matrix a) const
	{
		return this->rows == a.cols;
	}

	double Matrix::MtrMax() const
	{
		if (!this->isNULL()) {
			double a = mtr[0];
			for (int i = 1; i < this->rows * this->cols; i++)
				if (this->mtr[i] > a)
					a = this->mtr[i];
			return a;
		}
		else
			throw "Матрица пуста";
	}

	double Matrix::MtrMin() const
	{
		if (!this->isNULL()) {
			double a = mtr[0];
			for (int i = 1; i < this->rows * this->cols; i++)
				if (this->mtr[i] < a)
					a = this->mtr[i];
			return a;
		}
		else
			throw "Матрица пуста";
	}

	bool Matrix::isNULL() const
	{
		return mtr == nullptr;
	}

	Matrix& Matrix::operator=(const Matrix& other)
	{
		if (this->mtr != nullptr)
			delete[] this->mtr;

		this->rows = other.rows;
		this->cols = other.cols;

		this->mtr = new double[this->rows * this->cols];

		for (int i = 0; i < (this->rows * this->cols); i++)
		{
			this->mtr[i] = other.mtr[i];
		}

		return *this;
	}

	Matrix& Matrix::operator=(Matrix&& other)
	{
		std::swap(rows, other.rows);
		std::swap(cols, other.cols);
		std::swap(mtr, other.mtr);
		return *this;
	}

	Matrix& Matrix::operator+=(const Matrix& other)
	{
		if (this->CheckForSum(other))
		{
			for (int i = 0; i < (this->rows * this->cols); i++)
			{
				this->mtr[i] += other.mtr[i];
			}
		}
		else
			throw "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя складывать!";
	}

	Matrix& Matrix::operator-=(const Matrix& other)
	{
		if (this->CheckForSum(other))
		{
			for (int i = 0; i < (this->rows * this->cols); i++)
			{
				this->mtr[i] -= other.mtr[i];
			}
			return *this;
		}
		else
			throw "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя вычитать!";
	}

	Matrix& Matrix::operator*=(const int k)
	{
		if (!this->isNULL()) {
			for (int i = 0; i < (this->rows * this->cols); i++)
			{
				this->mtr[i] *= k;
			}
			return *this;
		}
		else
			throw "Ошибка! Матрица с номером " + std::to_string(mtr_id) + "пуста!";
	}

	Matrix& Matrix::operator*=(const Matrix& other)
	{

		if (CheckForMult(other) && !this->isNULL() && !other.isNULL()) {
			int k = 0;
			double* New = new double[this->rows * other.cols];
			for (int i = 0; i < rows * other.cols; i++)
				New[i] = 0.0;
			for (int i = 0; i < this->rows; ++i)
			{
				for (int j = 0; j < other.cols; ++j)
				{
					for (int k = 0; k < this->cols; ++k)
						New[i * other.cols + j] += (mtr[i * this->cols + k] * other.mtr[k * other.cols + j]);
				}
			}

			delete[] this->mtr;
			cols = other.cols;
			mtr = New;
			return *this;
		}
		else
			throw "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя умножать!";
	}

	std::ostream& operator<<(std::ostream& out, const Matrix& other)
	{
		if (!other.isNULL())
		{
			int pl = out.width();
			if (pl == 0)
				pl = 8;
			for (int i = 0; i < other.rows; i++) {
				for (int j = 0; j < other.cols; j++)
					out << std::setw(pl) << other.mtr[i * other.cols + j];
				out << "\n";
			}
			out << "\n";
			return out;
		}
		else
			throw "Ошибка! Матрица с номером " + std::to_string(other.mtr_id) + "пуста!";
	}

	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		return Matrix(a) += b;
	}

	Matrix operator-(const Matrix& a, const Matrix& b)
	{
		return Matrix(a) -= b;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		return Matrix(a) *= b;
	}

	Matrix operator*(const Matrix& a, double k)
	{
		return Matrix(a) -= k;
	}

	Matrix::MatrixRow Matrix::operator[](int ind)
	{
		if (ind <= cols + 1 && ind >= 1)
			return MatrixRow(this, ind - 1);
		else
			throw "Ошибка! Выход за границы матрицы объектом с номером " + std::to_string(mtr_id);;
	}

	const Matrix::MatrixRow Matrix::operator[](int ind) const {
		if (ind <= cols && ind >= 0)
			return MatrixRow(this, ind - 1);
		else
			throw "Ошибка! Выход за границы матрицы объектом с номером " + std::to_string(mtr_id);
	}

	Matrix::MatrixRow::MatrixRow(const Matrix* other, unsigned R)
	{
		r = other->rows;
		c = other->cols;
		this->R = R;
		this->mtr = other->mtr;
	}

	double& Matrix::MatrixRow::operator[](int ind)
	{
		if (ind <= c + 1 && ind >= 1)
			return mtr[R * c + ind - 1];
		else
			throw "Ошибка! Выход за границы матрицы текущим элементом! ";
	}

	double const Matrix::MatrixRow::operator[](int ind) const
	{
		if (ind <= c + 1 && ind >= 1)
			return mtr[R * c + ind - 1];
		else
			throw "Ошибка! Выход за границы матрицы текущим элементом!";
	}

	void fill(int r, int c, double* mtr)
	{
		for (int i = 0; i < r * c; i++)
			mtr[i] = rand()%10;
	}
	double gen(int i, int j)
	{
		return i + j;
	}