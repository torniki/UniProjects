#include <iostream>
#include <string>
#include "Matrix.h"
#include "vector.h"

namespace Mine
{
	Vector::Vector() :Matrix() 
	{
		global_id = IDS;
	#ifdef _DEBUG
		std::cout << /*"\033[A\033[K" <<*/ "\n+Vector" << global_id /*<< "\033[B\r"*/ << std::endl;
	#endif
	}

	Vector::Vector(unsigned int m) :Matrix(m, 1) 
	{
		global_id = IDS;
	#ifdef _DEBUG
		std::cout << "\n+Vector " << global_id << std::endl;
	#endif
	}

	Vector::Vector(unsigned int m, double(*myfunc)(unsigned int i)) :Matrix(m, 1) 
	{
		for (unsigned int i = 0; i < m; i++)
			data[i] = myfunc(i);
		global_id = IDS;
	#ifdef _DEBUG
		std::cout << "\n+Vector " << global_id << std::endl;
	#endif
	}

	Vector::Vector(unsigned int m, double* data) :Matrix(m, 1) 
	{
		if (data != nullptr) {
			std::copy(data, data + (m * n), this->data);
		}
		else throw "Data is empty!";
	}

	Vector::Vector(const Matrix& other) : Matrix(other) 
	{
		if (n > 1) throw "ERROR IN COPY CONSTRUCTOR! Vector " + std::to_string(global_id);
		global_id = IDS;
	#ifdef _DEBUG
		std::cout << "COPY CONSTRUCTOR. Vector " << global_id << std::endl;
	#endif
	}

	Vector::Vector(Matrix&& other) : Matrix(std::move(other))
	{
		if (n > 1) throw "ERROR IN MOVE CONSTRUCTOR! Vector " + std::to_string(global_id);
		global_id = IDS;
	#ifdef _DEBUG
		std::cout << "MOVE CONSTRUCTOR " << global_id << std::endl;
	#endif
	}

	Vector::~Vector() 
	{
	#ifdef _DEBUG
		std::cout /*<< "\033[A\033[K" */ << "\n-Vector " << global_id /*<< "\033[B\r"*/ << std::endl;
	#endif
	}

	Vector& Vector::operator=(const Matrix& other) 
	{
		Matrix::operator=(other);
		return *this;
	}

	Vector& Vector::operator=(Matrix&& other) 
	{
		Matrix::operator=(std::move(other));
		return *this;
	}

	Vector& Vector::operator+=(const Matrix& other) 
	{
		Matrix::operator+=(other);
		return *this;
	}

	Vector& Vector::operator-=(const Matrix& other) 
	{
		Matrix::operator-=(other);
		return *this;
	}

	Vector& Vector::operator*=(const Matrix& other) 
	{
		Matrix::operator*=(other);
		return *this;
	}

	Vector& Vector::operator*=(double k) 
	{
		Matrix::operator*=(k);
		return *this;
	}

	double& Vector::operator[](unsigned int ind)
	{
		if (ind <= n && ind >= 0)
			return this->data[ind];
		else throw "ERROR IN [] OPERATOR! Vector " + std::to_string(global_id);
	}

	double const Vector::operator[](unsigned int ind) const
	{
		if (ind <= n && ind >= 0)
			return this->data[ind];
		else throw "ERROR IN [] OPERATOR! Vector " + std::to_string(global_id);
	}

	Vector& Vector::Mult_on_scal(double scal) 
	{
		if (!this->isNULL()) {
			for (unsigned int i = 0; i < m; i++)
				data[i] *= scal;
			return *this;
		}
		else throw "ERROR IN Mult_on_scal! Vector" + std::to_string(global_id);
	}

	Vector& Vector::Normalization() {
		if (!this->isNULL()) {
			double module = Module();
			for (unsigned int i = 0; i < m; i++)
				data[i] /= module;
			return *this;
		}
		else throw "ERROR IN Normalization! Vector " + std::to_string(global_id);
	}

	double Vector::Module() const {
		if (!this->isNULL()) {
			double result = 0;
			for (unsigned int i = 0; i < m; i++)
				result += data[i] * data[i];
			return sqrt(result);
		}
		else throw "ERROR IN Module! Vector " + std::to_string(global_id);
	}

	std::string Vector::GetType() const 
	{
		return std::string("Vector ");
	}

	Vector Mult(const Vector& a, const Vector& b) 
	{
		if (a.m > 3 || b.m > 3) throw "Error! Uncorrect size!";
		else {
			Vector temp;
			temp.data = new double[3];
			temp.data[0] = (a.data[1] * b.data[2]) - (a.data[2] * b.data[1]);
			temp.data[1] = (a.data[2] * b.data[0]) - (a.data[0] * b.data[2]);
			temp.data[2] = (a.data[0] * b.data[1]) - (a.data[1] * b.data[0]);
	
			temp.m = 3;
			temp.n = 1;

			return temp;
		}
	};

	double Cosinus(const Vector& a, const Vector& b) 
	{
		return  MultScal(a, b) / (a.Module() * b.Module());
	};
	double Sinus(const Vector& a, const Vector& b) 
	{
		return 1 - pow(Cosinus(a, b), 2);
	};
	double MultScal(const Vector& a, const Vector& b) 
	{
		if (!a.sum(b) && !a.isNULL() && !b.isNULL()) 
		{
			double result = 0;
			for (unsigned int i = 0; i < a.GetM(); i++)
				result += a.data[i] * b.data[i];
			return result;
		}
		else throw "ERROR IN MultScal! Vector " + std::to_string(a.GetID()) + " * " + std::to_string(b.GetID());
	}
	
	double Angle(const Vector& a, const Vector& b) 
	{
		return acos(MultScal(a, b) / (a.Module() * b.Module())) * 180 / M_PI;
	}
}