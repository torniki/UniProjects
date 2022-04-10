#pragma once
#include <iostream>
#include "vect.h"

	class Matrix
	{
	private:
		static unsigned IDS;
		unsigned mtr_id;
		double* mtr;
		int rows, cols;
		class MatrixRow
		{
		public:
			MatrixRow(const Matrix* other, unsigned R);
			double& operator[](int ind);
			double const operator[](int ind) const;

		private:
			unsigned r, c, R;
			double* mtr;

		};
	public:
		//конструкторы
		Matrix(int r, int c, double(*gen)(unsigned int i, unsigned int j));
		Matrix(int s = 3);
		~Matrix();
		Matrix(int r, int c);
		Matrix(const Matrix& other);
		Matrix(Matrix&& other);
		//функции
		void print() const;
		int CheckForSum(const Matrix a) const;
		int CheckForMult(const Matrix a) const;
		double MtrMax() const;
		double MtrMin() const;
		bool isNULL() const;
		//операторы
		MatrixRow operator[](int ind);
		const MatrixRow operator[](int ind) const;
		friend std::ostream& operator<< (std::ostream& out, const Matrix& Matrix);
		Matrix& operator =(const Matrix& other);
		Matrix& operator =(Matrix&& other);
		Matrix& operator +=(const Matrix& other);
		Matrix& operator -=(const Matrix& other);
		Matrix& operator *=(const int k);
		Matrix& operator *=(const Matrix& other);
		friend Matrix operator +(const Matrix& a, const Matrix& b);
		friend Matrix operator -(const Matrix& a, const Matrix& b);
		friend Matrix operator *(const Matrix& a, const Matrix& b);
		friend Matrix operator *(const Matrix& a, double k);
	};
	//функция заполнения
	void fill(int r, int c, double* mtr);