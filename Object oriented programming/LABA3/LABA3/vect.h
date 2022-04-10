#pragma once
#include <iostream>
#include "matr.h"

	class vector :public Matrix
	{
	private:
		static unsigned IDS;
		unsigned vct_id;
		double* vct;
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
		Vector(int r, int c, double(*gen)(unsigned int i, unsigned int j));
		Vector(int s = 3);
		~Vector();
		Vector(int r, int c);
		Vector(const Vector& other);
		Vector(Vector&& other);

		
	};

	