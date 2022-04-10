#pragma once
#include <iostream>

using namespace std;

template <class T>
class Matrix
{
private:
	int rows, cols;
	T* pMatrix;

public:
	Matrix(int Rows, int Cols)
	{
		rows = Rows;
		cols = Cols;

		pMatrix = new T[rows * cols];
	}
	Matrix(int Size)
	{
		rows = Size;
		cols = Size;

		pMatrix = new T[rows * cols];
	}
	Matrix(const Matrix& matrix) 
	{
		rows = matrix.rows;
		cols = matrix.cols;

		pMatrix = new T[rows * cols];

		for (int i = 0; i < rows * cols; i++) 
		{
			pMatrix = matrix.pMatrix[i];
		}
		~Matrix() 
		{
			delete[] pMatrix;
		}
	}

};