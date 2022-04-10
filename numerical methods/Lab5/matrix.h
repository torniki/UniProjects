#pragma once

namespace mtr {
	class matrix
	{
	private:
		//Все переменные
	#pragma region Переменные
			

		class matrixRow;
		unsigned _LEN_N; // Кол-во столбцев
		unsigned _LEN_M; // Кол-во строк
		unsigned _ID;	 // Номер объекта
		static int _STATIC; // Для счёта номера объекта
		double* _MATRIX; // Наша матрица
#pragma endregion

		// Сам класс нужен для работы operator[] 
		// и 
		// работы индексации типа matrix obj[i][j]
	#pragma region Класс для индексации
		class matrixRow {
		private:
			const matrix* _MATRIX;
			unsigned _ROW;

		public:
				// Для случаев с простыми объектами
			matrixRow(matrix* obj, unsigned R);		
			double& operator[](unsigned);

				//Для случаев с константными объекстами
			matrixRow(const matrix* obj, unsigned R);
			double operator[](unsigned) const;
		};
#pragma endregion
	public: 
		typedef double(*martrix_func)(unsigned m, unsigned n, unsigned ROW, unsigned COL); //Это для функций
		//Конструкторы
	#pragma region Конструкторы и деструкторы	
		matrix();							// По умолчанию				
		matrix(unsigned);					// Квадратная матрица			
		matrix(unsigned col, unsigned row);	// прямоугольная		
		matrix(matrix&&);					// перемещение	
		matrix(const matrix& obj);			// копирование				
		//Принимает готовую матрицу как параметр
		matrix(unsigned, double*);
		matrix(unsigned, unsigned, double*);
		//С пользовательской функцией
		matrix(unsigned col, unsigned row, martrix_func user_func);
		matrix(unsigned nm, martrix_func user_func);
		~matrix();							// деструктор
	#pragma endregion

		//функции-элемента класса
	#pragma region Функции
		bool check_sub(const matrix&) const;	// проверку возможности умножения двух матриц;
		bool check_mul(const matrix&) const;	// проверку возможности сложения двух матриц
		double max_el() const;	// максимального элемента матрицы
		double min_el() const;	// минимального элемента матрицы
	#pragma endregion

		//перегрузка операторов-элементов
	#pragma region Другие операторы
		matrixRow operator[] (unsigned IND);
		const matrixRow operator[] (unsigned IND) const;

		//вывод
		friend	std::ostream &operator<< (std::ostream& out, const matrix& obj);
#pragma endregion

		//Операторы сложения с равно
	#pragma region Операторы +=, -=, *=, =
		matrix& operator=  (const matrix&);
		matrix& operator=  (matrix&&);

		matrix& operator+= (const matrix&);
		matrix& operator-= (const matrix&);
		matrix& operator*= (const matrix&);
		matrix& operator*= (const double);
	#pragma endregion

			//Обычные операторы
	#pragma region Операторы +, -, *
friend	matrix operator+ (const matrix&, const matrix&);
friend	matrix operator- (const matrix&, const matrix&);
friend	matrix operator* (const matrix&, const matrix&);
friend	matrix operator* (const matrix&, const double);
friend	matrix operator* (const double, const matrix&);
#pragma endregion
	};
}