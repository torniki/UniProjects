#pragma once
#include <iostream>
#include <string>
#include "Matrix.h"
namespace Torniki
{
	class Vector : public Matrix 
	{
	public:
		Vector();
		Vector(unsigned int m);
		Vector(unsigned int m, double(*myfunc)(unsigned int i));
		Vector(unsigned int m, double* data);
		~Vector() override;

		Vector(const Matrix& other);
		Vector(Matrix&& other);
		Vector& operator=(const Matrix& other);
		Vector& operator=(Matrix&& other);
		Vector& operator+=(const Matrix& other);
		Vector& operator-=(const Matrix& other);
		Vector& operator*=(const Matrix& other);
		Vector& operator*=(double k);
		double& operator[](unsigned int ind);
		double const operator[](unsigned int ind) const;

		double Module() const;
		std::string GetType() const override;
		Vector& Mult_on_scal(double scal);
		Vector& Normalization();
		friend double MultScal(const Vector& a, const Vector& b);
		friend Vector Mult(const Vector& a, const Vector& b);
		friend double Cosinus(const Vector& a, const Vector& b);
		friend double Sinus(const Vector& a, const Vector& b);
	};
}