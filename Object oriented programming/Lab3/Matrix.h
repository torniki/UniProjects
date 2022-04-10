#pragma once
#include <iostream>
#include <string>

namespace Mine 
{
	class Vector;
	class Matrix 
	{
	friend Vector;
	protected:
		double* data;
		unsigned int m, n;
		unsigned global_id;
		static unsigned IDS;

		class matrixRow
		{
		public:
			matrixRow(const Matrix* other, unsigned R);
			double& operator[](unsigned int ind);
			double const operator[](unsigned int ind) const;

		private:
			unsigned m, n, R, matr_id;
			double* data;
		};

	public:
		Matrix();
		Matrix(unsigned int m);
		Matrix(unsigned int  m, unsigned int n);
		Matrix(unsigned int  m, unsigned  int n, double(*myfunc)(unsigned int i, unsigned int j));
		Matrix(unsigned int  m, unsigned int n, double* data);
		Matrix(const Matrix& other);
		Matrix(Matrix&& other) noexcept;
		virtual ~Matrix();

		matrixRow operator[](unsigned int ind);
		const matrixRow operator[](unsigned int ind) const;

		Matrix& Transpose();
		Matrix GetTranspose();
		Matrix& operator=(const Matrix& other);
		Matrix& operator=(Matrix&& other) noexcept;
		Matrix& operator+=(const Matrix& other);
		Matrix& operator-=(const Matrix& other);
		Matrix& operator*=(const Matrix& other);
		Matrix& operator*=(double k);
		friend Matrix operator+(const Matrix& a, const Matrix& b);
		friend Matrix operator-(const Matrix& a, const Matrix& b);
		friend Matrix operator*(const Matrix& a, const Matrix& b);
		friend Matrix operator*(const Matrix& a, double k);
		friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);

		bool mult(const Matrix& a) const;
		bool sum(const Matrix& a) const;
		bool isNULL() const;
		double max() const;
		double min() const;
		inline unsigned int GetID() const;
		inline unsigned int GetN() const;
		inline unsigned int GetM() const;
		Matrix& SetN(int n);
		Matrix& SetM(int m);
		virtual std::string GetType() const;
	};
}

