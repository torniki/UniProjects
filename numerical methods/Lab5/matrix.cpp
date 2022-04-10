#define _USE_MATH_DEFINES
#include <iostream>
#include <time.h>
#include <new>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <float.h>
#include "matrix.h"
	// � �� ����� ��� ����� �� �����
	// ��� ��� �� ������
using namespace std;

namespace mtr
{
	int matrix::_STATIC = 0;
	#pragma region ������������ � �����������
	matrix::matrix(unsigned n, unsigned m) : _LEN_N(n), _LEN_M(m), _ID(++_STATIC) {
		if (n == 0 || m == 0) { _MATRIX = nullptr; _LEN_N = 0; _LEN_M = 0; } // ����������
		else {
			_MATRIX = new double[_LEN_N * _LEN_M]();				// ������� ������
		}
	} 
	matrix::matrix(unsigned n) : matrix(n, n) {
	//��� ���������� �������
	}
	matrix::matrix() : matrix(0) {
	//����������� �� ���������
	} 
	// ��������� ������� �������
	matrix::matrix(unsigned nm, double* matrix) : matrix(nm) {
		for (unsigned i = 0; i < nm * nm; i++) _MATRIX[i] = matrix[i];
		if (nm == 0) { 
			_MATRIX = nullptr; _LEN_M = 0; _LEN_N = 0;
		}
	}
	matrix::matrix(unsigned n, unsigned m, double* matrix): matrix(n, m) {
		for (unsigned i = 0; i < m * n; i++) _MATRIX[i] = matrix[i];
		if (n == 0 || m == 0) { 

			_MATRIX = nullptr; _LEN_M = 0; _LEN_N = 0; 
		}
	}
	matrix::matrixRow::matrixRow(matrix* obj, unsigned R) :
		_ROW(R* obj->_LEN_N), //����������� ������ ��� ������� ����������
		_MATRIX(obj)
	{}
	matrix::matrixRow::matrixRow(const matrix* obj, unsigned R) :
		_ROW(R * obj->_LEN_N),//����������� ������ ��� ����������� ����������
		_MATRIX(obj)
	{}
	matrix::matrix(unsigned n, unsigned m, martrix_func user_func) : matrix(n, m)
	{				// ���������� ������� ���������������� ��������
		for (unsigned r = 0; r < m; r++)
			for (unsigned c = 0; c < n; c++)
				_MATRIX[_LEN_N * r + c] = user_func(m, n, r, c); 
	}
	matrix::matrix(unsigned nm, martrix_func user_func) : matrix(nm)
	{ //���������� �����������
		for (unsigned r = 0; r < nm; r++)
			for (unsigned c = 0; c < nm; c++)
				_MATRIX[_LEN_N * r + c] = user_func(nm, nm, r, c);
	}
	matrix::matrix(const matrix& obj) : _ID(++_STATIC), _LEN_M(obj._LEN_M), _LEN_N(obj._LEN_N) {
		try {			//����������
		_MATRIX = new double[_LEN_M * _LEN_N]; //��������� � �������� ������ �� ������� 

		for (unsigned i = 0; i < _LEN_M * _LEN_N; i++) //�������� � ���� �������
			_MATRIX[i] = obj._MATRIX[i];
		}
		catch (bad_alloc e) { //	����������� ������ � ���������� ������
			std::cout << e.what() << std::endl;
		}
	}
	matrix::matrix(matrix&& obj) //������������
		:	_LEN_M(obj._LEN_M),		// ���� ������, �� ���� ����������� 
			_LEN_N(obj._LEN_N),		// �������� ������ � �������
			_MATRIX(obj._MATRIX),	// ����������� ��� ��������
			_ID(++_STATIC) {
		obj._MATRIX = nullptr;
	}
	matrix::~matrix() { //����������	
		delete[] _MATRIX; }

#pragma endregion
	#pragma region �������
	// ������������� �������� �������
	double matrix::max_el() const {
		double max = DBL_MIN;							// �����, ��� ����� ��� ����������� ����������
		if (_LEN_M == 0 || _LEN_N == 0 || _MATRIX == nullptr)
			throw "Matrix is empty";
														// DBL_MIN - ����������� �������� double
		for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	//� ����� ���� ������������ �������
			if (max < _MATRIX[i])						// ���� ������� ��������, �-� ������ max
				max = _MATRIX[i];						// �� ������� � max �������� _MATRIX[i]
		return max;									//����������
	}
	// ������������ �������� �������
	double matrix::min_el() const {
		double min = DBL_MAX; // DBL_MAX - ������������ �������� Double
		if (_LEN_M == 0 || _LEN_N == 0 || _MATRIX == nullptr)
			throw "Matrix is empty";
		for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)
			if (min > _MATRIX[i])
				min = _MATRIX[i];
		return min;
	}

	// �������� ����������� �������� ���� ������
	bool matrix::check_sub(const matrix& obj) const {
			// ��� ��� ������� ���� bool, �� ��������� ����� ����������� ��������� ����� ���� True, ���� False
			// ������� � ����� ��������� ������
		return this->_LEN_M == obj._LEN_M && this->_LEN_N == obj._LEN_N;
	}
	// �������� ����������� ��������� ���� ������;
	bool matrix::check_mul(const matrix& obj) const {
			//���������� ����������
		return this->_LEN_M == obj._LEN_N; // ��� �� ������������, �������
	}
#pragma endregion

// ����������
	#pragma region ��������� +=, -=, *=
	//matrix += matrix
	matrix& matrix::operator+= (const matrix& obj) {
		if (check_sub(obj))
		{
			for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	// ����� ������, ������ ����������
				_MATRIX[i] += obj._MATRIX[i];
			return *this;									//� ����������
		}													// �� ���� �� �������� ��� �����������
															// �� ���������� ����������
															// ��� ������� ��� �� ���������)
		else throw "operator+= : Matrix(" + std::to_string(_ID) + ") += Matrix(" + std::to_string(obj._ID) + ")  : different size";
	}
	//matrix -= matrix
	matrix& matrix::operator-= (const matrix& obj) {
		if (check_sub(obj))
		{
			for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	// ������� ���������, ������ ��������
				_MATRIX[i] -= obj._MATRIX[i];
			return *this;
		}													// �� ��� �� �������, ��� �� ���������)
		else throw "operator-= : Matrix(" + std::to_string(_ID) + "), Matrix(" + std::to_string(obj._ID) + ")  : different size";
	}
	// matrix *= matrix
	matrix& matrix::operator*= (const matrix& obj) {
		if (check_mul(obj))
		{
				// ���� �� ��������, �� ��� ������� �������� ��� ������������ �������
				// ������, �� ��������
														
			double* _BUF = new double[this->_LEN_M * obj._LEN_N]();											// �������� ������
			for (unsigned i = 0; i < this->_LEN_M; i++)														// ���� �� 0 �� ���-�� ����� �������, ������� ��������
				for (unsigned j = 0; j < obj._LEN_N; j++) {													// ���� �� 0 �� ���-�� �������� �������, �� ������� ��������		
					for (unsigned k = 0; k < this->_LEN_N; k++)												// ���� �� 0 �� ���-�� �������� �������, ������� ��������
						_BUF[i * obj._LEN_N + j] += _MATRIX[i * k + k] * obj._MATRIX[k * obj._LEN_N + j];   // � ��� ������� ��� ������ ������� � �������
				}
			delete[] _MATRIX;																				// ������� �������
			_MATRIX = _BUF;																					// �������� _BUF � _MATRIX
			_LEN_N = obj._LEN_N;																			// ��� ����� �������
			return *this;																					// ����������
		}																									// �� � ���������, ���� ����� �����, ������ ��� ����� ���-�� �� ���
		else throw "operator*= : Matrix(" + std::to_string(_ID) + "), Matrix(" + std::to_string(obj._ID) + ")  : different size";
		
	}
	//matrix *= double
	matrix& matrix::operator*= (const double num) {
		if (_MATRIX != nullptr) {							// ���� ������� �� ������
			for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	// ��������� ����
				_MATRIX[i] *= num;							// ������� �������� �� �����
			return *this;
		}													//����������
		else throw "operator*= : Matrix(" + std::to_string(_ID) + ") : different size";
	}
#pragma endregion	
	#pragma region ��������� +, -, *
	// matrix + matrix
	matrix operator+ (const matrix& obj_1, const matrix& obj_2) {
		if (obj_1.check_sub(obj_2))			//��� ����� ���������� �����
			return matrix(obj_1) += obj_2;	//�����, ��� � ����� obj_1 �����������(���� � ��� �������� ���, ����� ����� ������ ������) ����� ���������� ���� �������� � � ���� � ��������� obj_2
		else throw "operator+ : Matrix(" + std::to_string(obj_1._ID) + "), Matrix(" + std::to_string(obj_2._ID) + ")  : different size";
	}
	//matrix - matrix
	matrix operator- (const matrix& obj_1, const matrix& obj_2) {
		if (obj_1.check_sub(obj_2))
			return matrix(obj_1) -= obj_2;	//�� �� ����
											//����������
		else throw "operator- : Matrix(" + std::to_string(obj_1._ID) + "), Matrix(" + std::to_string(obj_2._ID) + ")  : different size";
	}
	//matrix * matrix
	matrix operator* (const matrix& obj_1, const matrix& obj_2) {
		if (obj_1.check_mul(obj_2))
			return matrix(obj_1) *= obj_2;	//�� �� ����
											//����������
		else throw "operator* : Matrix(" + std::to_string(obj_1._ID) + "), Matrix(" + std::to_string(obj_2._ID) + ")  : different size";;
	}
	//matrix * double
	matrix operator* (const matrix& obj, const double num) {
		if (obj._MATRIX != nullptr)
			return matrix(obj) *= num;		//����������
		else throw "operator* : Matrix(" + std::to_string(obj._ID) + "), Num(" + std::to_string(num) + ")  : different size";
	}
	//double * matrix
	matrix operator* (const double num, const matrix& obj) {
		//��� ��� ��������������� 
		return obj * num; }
#pragma endregion

//��������� ���������
	#pragma region ������������, ����������� � �����
	matrix& matrix::operator= (const matrix& obj) {
		if (this == &obj)													//�������� �� ���������������
			return *this;

		_LEN_M = obj._LEN_M;
		_LEN_N = obj._LEN_N;
		if (!check_mul(obj) || !check_sub(obj)) {
			delete[]_MATRIX;												//������� ������� �������
			_MATRIX = new double[_LEN_M * _LEN_N];							//�������� ������
		}
		std::copy(obj._MATRIX, obj._MATRIX + _LEN_M * _LEN_N, _MATRIX);		//�������� ������� obj � _MATRIX
		return *this;														//����������
	}

//�����������
	matrix& matrix::operator= (matrix&& obj) {
		
		if (this == &obj)				//�������� �� ���������������
			return *this;

		delete[] _MATRIX;				//�������
		_MATRIX = nullptr;				//��������� ������� ���������
		
		std::swap(_LEN_M,obj._LEN_M);	//��� ������� ������ ������� �� ��������
		std::swap(_LEN_N, obj._LEN_N);
		std::swap(_MATRIX, obj._MATRIX);

		return *this;					//����������
	}
	// cout << matrix
	std::ostream& operator<<(std::ostream& out, const matrix& obj)
	{			//����� �������� �����
		size_t _Wide = out.width(); 
		if (_Wide == 0);
			_Wide = 10;
		out << setw(0) << ">> Matrix " << obj._ID << " :\n" << std::endl;
		for (unsigned i = 0; i < obj._LEN_N; i++) {
			for (unsigned j = 0; j < obj._LEN_M; j++)
				out << setw(_Wide) << obj._MATRIX[i * obj._LEN_N + j];
			out << "\n";
		}
		out << "\n";
		return out;
	}
#pragma endregion
	#pragma region ����������
		//���������� ��� ������� ��������
	double& matrix::matrixRow::operator[](unsigned IND) { return _MATRIX->_MATRIX[_ROW + IND]; }
	matrix::matrixRow matrix::operator[](unsigned IND) { return matrixRow(this, IND); }
		
		//���������� ��� ����������� ��������
	const matrix::matrixRow matrix::operator[](unsigned IND) const { return matrixRow(this, IND); }
	double matrix::matrixRow::operator[](unsigned IND) const { return _MATRIX->_MATRIX[_ROW + IND]; }
	#pragma endregion
}