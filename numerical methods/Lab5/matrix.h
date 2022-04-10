#pragma once

namespace mtr {
	class matrix
	{
	private:
		//��� ����������
	#pragma region ����������
			

		class matrixRow;
		unsigned _LEN_N; // ���-�� ��������
		unsigned _LEN_M; // ���-�� �����
		unsigned _ID;	 // ����� �������
		static int _STATIC; // ��� ����� ������ �������
		double* _MATRIX; // ���� �������
#pragma endregion

		// ��� ����� ����� ��� ������ operator[] 
		// � 
		// ������ ���������� ���� matrix obj[i][j]
	#pragma region ����� ��� ����������
		class matrixRow {
		private:
			const matrix* _MATRIX;
			unsigned _ROW;

		public:
				// ��� ������� � �������� ���������
			matrixRow(matrix* obj, unsigned R);		
			double& operator[](unsigned);

				//��� ������� � ������������ ����������
			matrixRow(const matrix* obj, unsigned R);
			double operator[](unsigned) const;
		};
#pragma endregion
	public: 
		typedef double(*martrix_func)(unsigned m, unsigned n, unsigned ROW, unsigned COL); //��� ��� �������
		//������������
	#pragma region ������������ � �����������	
		matrix();							// �� ���������				
		matrix(unsigned);					// ���������� �������			
		matrix(unsigned col, unsigned row);	// �������������		
		matrix(matrix&&);					// �����������	
		matrix(const matrix& obj);			// �����������				
		//��������� ������� ������� ��� ��������
		matrix(unsigned, double*);
		matrix(unsigned, unsigned, double*);
		//� ���������������� ��������
		matrix(unsigned col, unsigned row, martrix_func user_func);
		matrix(unsigned nm, martrix_func user_func);
		~matrix();							// ����������
	#pragma endregion

		//�������-�������� ������
	#pragma region �������
		bool check_sub(const matrix&) const;	// �������� ����������� ��������� ���� ������;
		bool check_mul(const matrix&) const;	// �������� ����������� �������� ���� ������
		double max_el() const;	// ������������� �������� �������
		double min_el() const;	// ������������ �������� �������
	#pragma endregion

		//���������� ����������-���������
	#pragma region ������ ���������
		matrixRow operator[] (unsigned IND);
		const matrixRow operator[] (unsigned IND) const;

		//�����
		friend	std::ostream &operator<< (std::ostream& out, const matrix& obj);
#pragma endregion

		//��������� �������� � �����
	#pragma region ��������� +=, -=, *=, =
		matrix& operator=  (const matrix&);
		matrix& operator=  (matrix&&);

		matrix& operator+= (const matrix&);
		matrix& operator-= (const matrix&);
		matrix& operator*= (const matrix&);
		matrix& operator*= (const double);
	#pragma endregion

			//������� ���������
	#pragma region ��������� +, -, *
friend	matrix operator+ (const matrix&, const matrix&);
friend	matrix operator- (const matrix&, const matrix&);
friend	matrix operator* (const matrix&, const matrix&);
friend	matrix operator* (const matrix&, const double);
friend	matrix operator* (const double, const matrix&);
#pragma endregion
	};
}