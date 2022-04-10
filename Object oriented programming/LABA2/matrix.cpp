#include <iostream>
#include <iomanip>
#include <math.h>
#include "matrix.h"
#include <string>


namespace gromax
{
	unsigned matrix::IDS = 0;

	matrix::matrix(int r, int c, double(*gen)(unsigned int i, unsigned int j))
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

	matrix::matrix(int r, int c)
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

	matrix::matrix(int s)
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

	matrix::~matrix()
	{
		delete[] this->mtr;
		std::cout << "Вызвался деструктор и удалился объект " << mtr_id << std::endl;
		mtr_id = --IDS;
	}

	matrix::matrix(const matrix& other)
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

	matrix::matrix(matrix&& other)
		:rows(0), cols(0), mtr(nullptr)
	{
		std::swap(rows, other.rows);
		std::swap(cols, other.cols);
		std::swap(mtr, other.mtr);
		mtr_id = ++IDS;
		std::cout << "Вызван конструктор перемещения, объект с номером " << other.mtr_id << " перемещен в объект " << mtr_id << std::endl;
	}


	void matrix::print() const
	{
		std::cout << "\n" << std::endl;
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->cols; j++)
				std::cout << this->mtr[i * this->cols + j] << " ";
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	int matrix::CheckForSum(const matrix a) const
	{
		return ((this->rows == a.rows) && (this->cols == a.cols));
	}

	int matrix::CheckForMult(const matrix a) const
	{
		return this->rows == a.cols;
	}

	double matrix::MtrMax() const
	{
		if (!this->isNULL()) {
			double a = mtr[0];
			for (int i = 1; i < this->rows * this->cols; i++)
				if (this->mtr[i] > a)
					a = this->mtr[i];
			return a;
		}
		else
		{
			std::string errMSG = "Нельзя найти минимальный элемент, так как матрица пуста";
			throw errMSG;
		}
	}

	double matrix::MtrMin() const
	{
		if (!this->isNULL()) {
			double a = mtr[0];
			for (int i = 1; i < this->rows * this->cols; i++)
				if (this->mtr[i] < a)
					a = this->mtr[i];
			return a;
		}
		else
		{
			std::string errMSG = "Нельзя найти минимальный элемент, так как матрица пуста";
			throw errMSG;
		}
	}

	bool matrix::isNULL() const
	{
		return mtr == nullptr;
	}

	matrix& matrix::operator=(const matrix& other)
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

	matrix& matrix::operator=(matrix&& other)
	{
		std::swap(rows, other.rows);
		std::swap(cols, other.cols);
		std::swap(mtr, other.mtr);
		return *this;
	}

	matrix& matrix::operator+=(const matrix& other)
	{
		if (this->CheckForSum(other))
		{
			for (int i = 0; i < (this->rows * this->cols); i++)
			{
				this->mtr[i] += other.mtr[i];
			}
		}
		else
		{
			std::string errMSG = "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя складывать!";
			throw errMSG;
		}
	}

	matrix& matrix::operator-=(const matrix& other)
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
		{
			std::string errMSG = "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя вычитать!";
			throw errMSG;
		}
	}

	matrix& matrix::operator*=(const int k)
	{
		if (!this->isNULL()) {
			for (int i = 0; i < (this->rows * this->cols); i++)
			{
				this->mtr[i] *= k;
			}
			return *this;
		}
		else {
			std::string errMSG = "Ошибка! Матрица с номером " + std::to_string(mtr_id) + "пуста!";
			throw errMSG;
		}
	}

	matrix& matrix::operator*=(const matrix& other)
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
		{
			std::string errMSG = "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя умножать!";
			throw errMSG;
		}
	}

	std::ostream& operator<<(std::ostream& out, const matrix& other)
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
		{
			std::string errMSG = "Ошибка! Матрица с номером " + std::to_string(other.mtr_id) + "пуста!";
			throw errMSG;
		}
	}

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
		return matrix(a) -= k;
	}

	matrix::matrixRow matrix::operator[](int ind)
	{
		if (ind <= cols + 1 && ind >= 1)
			return matrixRow(this, ind - 1);
		else {
			std::string errMSG = "Ошибка! Выход за границы матрицы объектом с номером " + std::to_string(mtr_id);
			throw errMSG;
		}
	}

	const matrix::matrixRow matrix::operator[](int ind) const {
		if (ind <= cols && ind >= 0)
			return matrixRow(this, ind - 1);
		else {
			std::string errMSG = "Ошибка! Выход за границы матрицы объектом с номером " + std::to_string(mtr_id);
			throw errMSG;
		}
	}

	matrix::matrixRow::matrixRow(const matrix* other, unsigned R)
	{
		r = other->rows;
		c = other->cols;
		this->R = R;
		this->mtr = other->mtr;
	}

	double& matrix::matrixRow::operator[](int ind)
	{
		if (ind <= c + 1 && ind >= 1)
			return mtr[R * c + ind - 1];
		else {
			std::string errMSG = "Ошибка! Выход за границы матрицы текущим элементом! ";
			throw errMSG;
		}
	}

	double const matrix::matrixRow::operator[](int ind) const
	{
		if (ind <= c + 1 && ind >= 1)
			return mtr[R * c + ind - 1];
		else {
			std::string errMSG = "Ошибка! Выход за границы матрицы текущим элементом!";
			throw errMSG;
		}
	}

	void fill(int r, int c, double* mtr)
	{

		for (int i = 0; i < r * c; i++)
			mtr[i] = 1.0 + 98.0 * rand() / (double)RAND_MAX;
	}
	double gen(int i, int j)
	{
		return i + j;
	}
}