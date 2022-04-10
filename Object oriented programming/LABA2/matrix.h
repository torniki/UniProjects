#pragma once
#include <iostream>

namespace gromax
{
	class matrix
	{
	private:
		static unsigned IDS;
		unsigned mtr_id;
		double* mtr;
		int rows, cols;
		class matrixRow
		{
		public:
			matrixRow(const matrix* other, unsigned R);
			double& operator[](int ind);
			double const operator[](int ind) const;

		private:
			unsigned r, c, R;
			double* mtr;

		};
	public:
		matrix(int r, int c, double(*gen)(unsigned int i, unsigned int j));
		matrix(int s = 3);
		~matrix();
		matrix(int r, int c);
		matrix(const matrix& other);
		matrix(matrix&& other);
		void print() const;
		int CheckForSum(const matrix a) const;
		int CheckForMult(const matrix a) const;
		double MtrMax() const;
		double MtrMin() const;
		bool isNULL() const;
		matrixRow operator[](int ind);
		const matrixRow operator[](int ind) const;
		friend std::ostream& operator<< (std::ostream& out, const matrix& matrix);
		matrix& operator=(const matrix& other);
		matrix& operator=(matrix&& other);
		matrix& operator+=(const matrix& other);
		matrix& operator-=(const matrix& other);
		matrix& operator*=(const int k);
		matrix& operator*=(const matrix& other);
		friend matrix operator+(const matrix& a, const matrix& b);
		friend matrix operator-(const matrix& a, const matrix& b);
		friend matrix operator*(const matrix& a, const matrix& b);
		friend matrix operator*(const matrix& a, double k);
	};
	void fill(int r, int c, double* mtr);
}
