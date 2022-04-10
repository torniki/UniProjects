#pragma once

namespace mtr
{
	class matrix
	{
	private:
		double* array;
		unsigned n, m;

		static unsigned IDS;
		unsigned matr_id;
		//Пользовательская функция
		typedef double(*UserFuncMtr)(unsigned n, unsigned m, unsigned r, unsigned c);

		class MatrixRow
		{
		public:
			MatrixRow(matrix* other, unsigned Row);
			MatrixRow(const matrix* other, unsigned Row);

			double& operator[](unsigned index);
			double operator[](unsigned index) const;

		private:
			unsigned n, m, Row;
			double* MatrRow;
		};
	public:

		MatrixRow operator[](unsigned index);

		const MatrixRow operator[](unsigned index) const;

		matrix();
		matrix(unsigned n);
		matrix(unsigned  n, bool value);
		matrix(unsigned  n, unsigned m);
		matrix(unsigned, double*);
		matrix(unsigned, unsigned, double*);
		matrix(unsigned n, unsigned m, UserFuncMtr user_func);
		matrix(unsigned nm, UserFuncMtr user_func);
		matrix(const matrix& other);
		matrix(matrix&& other);
		~matrix();

		friend std::ostream& operator<< (std::ostream& out, const matrix& matrix);

		matrix& init();

		matrix& operator=(const matrix& other);

		matrix& operator=(matrix&& other);

		matrix& operator+=(const matrix& other);

		matrix& operator-=(const matrix& other);

		matrix& operator*=(const matrix& other);

		matrix& operator*=(double k);

		matrix& Transpose();

		friend matrix operator+(const matrix& a, const matrix& b);

		friend matrix operator-(const matrix& a, const matrix& b);

		friend matrix operator*(const matrix& a, const matrix& b);

		friend matrix operator*(const matrix& a, double k);

		bool mult(const matrix& a) const;

		bool sum(const matrix& a) const;

		double max() const;

		double min() const;

		bool isNULL() const;
	};
}