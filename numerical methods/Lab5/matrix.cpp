#define _USE_MATH_DEFINES
#include <iostream>
#include <time.h>
#include <new>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <float.h>
#include "matrix.h"
	// Я не помню что здесь не нужно
	// так что не трогаю
using namespace std;

namespace mtr
{
	int matrix::_STATIC = 0;
	#pragma region Конструкторы и деструкторы
	matrix::matrix(unsigned n, unsigned m) : _LEN_N(n), _LEN_M(m), _ID(++_STATIC) {
		if (n == 0 || m == 0) { _MATRIX = nullptr; _LEN_N = 0; _LEN_M = 0; } // исключение
		else {
			_MATRIX = new double[_LEN_N * _LEN_M]();				// Выделаю память
		}
	} 
	matrix::matrix(unsigned n) : matrix(n, n) {
	//Для квадратной матрицы
	}
	matrix::matrix() : matrix(0) {
	//Конструктор по умолчанию
	} 
	// Принимает готовую матрицу
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
		_ROW(R* obj->_LEN_N), //Конструктор строки для обычных переменных
		_MATRIX(obj)
	{}
	matrix::matrixRow::matrixRow(const matrix* obj, unsigned R) :
		_ROW(R * obj->_LEN_N),//Конструктор строки для константных переменных
		_MATRIX(obj)
	{}
	matrix::matrix(unsigned n, unsigned m, martrix_func user_func) : matrix(n, m)
	{				// заполнение матрицы пользовательской функцией
		for (unsigned r = 0; r < m; r++)
			for (unsigned c = 0; c < n; c++)
				_MATRIX[_LEN_N * r + c] = user_func(m, n, r, c); 
	}
	matrix::matrix(unsigned nm, martrix_func user_func) : matrix(nm)
	{ //Аналогично предыдущему
		for (unsigned r = 0; r < nm; r++)
			for (unsigned c = 0; c < nm; c++)
				_MATRIX[_LEN_N * r + c] = user_func(nm, nm, r, c);
	}
	matrix::matrix(const matrix& obj) : _ID(++_STATIC), _LEN_M(obj._LEN_M), _LEN_N(obj._LEN_N) {
		try {			//Копирующий
		_MATRIX = new double[_LEN_M * _LEN_N]; //Объявляем и выделяем память на матрицу 

		for (unsigned i = 0; i < _LEN_M * _LEN_N; i++) //копируем в нашу матрицу
			_MATRIX[i] = obj._MATRIX[i];
		}
		catch (bad_alloc e) { //	Отлавливаем ошибку с выделением памяти
			std::cout << e.what() << std::endl;
		}
	}
	matrix::matrix(matrix&& obj) //Перемещающий
		:	_LEN_M(obj._LEN_M),		// Если кратко, то этот конструктор 
			_LEN_N(obj._LEN_N),		// Забираем память у объекта
			_MATRIX(obj._MATRIX),	// Переданного как параметр
			_ID(++_STATIC) {
		obj._MATRIX = nullptr;
	}
	matrix::~matrix() { //Деструктор	
		delete[] _MATRIX; }

#pragma endregion
	#pragma region Функции
	// максимального элемента матрицы
	double matrix::max_el() const {
		double max = DBL_MIN;							// Кароч, эта штука тип константная переменная
		if (_LEN_M == 0 || _LEN_N == 0 || _MATRIX == nullptr)
			throw "Matrix is empty";
														// DBL_MIN - минимальное значение double
		for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	//В цикле ищет максимальный элемент
			if (max < _MATRIX[i])						// Если находит значение, к-е больше max
				max = _MATRIX[i];						// то заносим в max значение _MATRIX[i]
		return max;									//возвращаем
	}
	// минимального элемента матрицы
	double matrix::min_el() const {
		double min = DBL_MAX; // DBL_MAX - максимальное значение Double
		if (_LEN_M == 0 || _LEN_N == 0 || _MATRIX == nullptr)
			throw "Matrix is empty";
		for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)
			if (min > _MATRIX[i])
				min = _MATRIX[i];
		return min;
	}

	// проверку возможности сложения двух матриц
	bool matrix::check_sub(const matrix& obj) const {
			// Так как функция типа bool, то результат этого логического уравнения будет либо True, либо False
			// Сделано в угоду краткости записи
		return this->_LEN_M == obj._LEN_M && this->_LEN_N == obj._LEN_N;
	}
	// проверку возможности умножения двух матриц;
	bool matrix::check_mul(const matrix& obj) const {
			//Аналонично предыдущей
		return this->_LEN_M == obj._LEN_N; // она не коммутативна, поменяй
	}
#pragma endregion

// Арифметика
	#pragma region Операторы +=, -=, *=
	//matrix += matrix
	matrix& matrix::operator+= (const matrix& obj) {
		if (check_sub(obj))
		{
			for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	// Грубо говоря, просто складываем
				_MATRIX[i] += obj._MATRIX[i];
			return *this;									//И возвращаем
		}													// Но если не подходит для складывания
															// То вызывается исключение
															// Оно говорит что ты накосячил)
		else throw "operator+= : Matrix(" + std::to_string(_ID) + ") += Matrix(" + std::to_string(obj._ID) + ")  : different size";
	}
	//matrix -= matrix
	matrix& matrix::operator-= (const matrix& obj) {
		if (check_sub(obj))
		{
			for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	// Обычное вычетание, ничего сложного
				_MATRIX[i] -= obj._MATRIX[i];
			return *this;
		}													// Всё так же говорит, что ты накосячил)
		else throw "operator-= : Matrix(" + std::to_string(_ID) + "), Matrix(" + std::to_string(obj._ID) + ")  : different size";
	}
	// matrix *= matrix
	matrix& matrix::operator*= (const matrix& obj) {
		if (check_mul(obj))
		{
				// Если не пояснять, то это обычный алгоритм для перемножения матрицы
				// Поверь, он работает
														
			double* _BUF = new double[this->_LEN_M * obj._LEN_N]();											// Выделяем память
			for (unsigned i = 0; i < this->_LEN_M; i++)														// Цикл от 0 до кол-во строк объекта, который умножаем
				for (unsigned j = 0; j < obj._LEN_N; j++) {													// Цикл от 0 до кол-во столбцев объекта, на который умнажаем		
					for (unsigned k = 0; k < this->_LEN_N; k++)												// Цикл от 0 до кол-во столбцев объекта, который умножаем
						_BUF[i * obj._LEN_N + j] += _MATRIX[i * k + k] * obj._MATRIX[k * obj._LEN_N + j];   // А это формула для ячейки объекта в матрици
				}
			delete[] _MATRIX;																				// Очистка матрицы
			_MATRIX = _BUF;																					// Копируем _BUF в _MATRIX
			_LEN_N = obj._LEN_N;																			// тут думаю понятно
			return *this;																					// Возвращаем
		}																									// Ну а следующее, если будет нужно, скажет что здесь что-то не так
		else throw "operator*= : Matrix(" + std::to_string(_ID) + "), Matrix(" + std::to_string(obj._ID) + ")  : different size";
		
	}
	//matrix *= double
	matrix& matrix::operator*= (const double num) {
		if (_MATRIX != nullptr) {							// Если матрица не пустая
			for (unsigned i = 0; i < _LEN_N * _LEN_M; i++)	// Выполняем цикл
				_MATRIX[i] *= num;							// Который умножает на число
			return *this;
		}													//Исключение
		else throw "operator*= : Matrix(" + std::to_string(_ID) + ") : different size";
	}
#pragma endregion	
	#pragma region Операторы +, -, *
	// matrix + matrix
	matrix operator+ (const matrix& obj_1, const matrix& obj_2) {
		if (obj_1.check_sub(obj_2))			//Это очень гениальная штука
			return matrix(obj_1) += obj_2;	//Кароч, тут я делаю obj_1 неудаляемым(чтоб я мог передать его, иначе будет потеря памяти) после выполнения этой операции и к нему я прибавляю obj_2
		else throw "operator+ : Matrix(" + std::to_string(obj_1._ID) + "), Matrix(" + std::to_string(obj_2._ID) + ")  : different size";
	}
	//matrix - matrix
	matrix operator- (const matrix& obj_1, const matrix& obj_2) {
		if (obj_1.check_sub(obj_2))
			return matrix(obj_1) -= obj_2;	//Та же тема
											//Исключение
		else throw "operator- : Matrix(" + std::to_string(obj_1._ID) + "), Matrix(" + std::to_string(obj_2._ID) + ")  : different size";
	}
	//matrix * matrix
	matrix operator* (const matrix& obj_1, const matrix& obj_2) {
		if (obj_1.check_mul(obj_2))
			return matrix(obj_1) *= obj_2;	//Та же тема
											//Исключение
		else throw "operator* : Matrix(" + std::to_string(obj_1._ID) + "), Matrix(" + std::to_string(obj_2._ID) + ")  : different size";;
	}
	//matrix * double
	matrix operator* (const matrix& obj, const double num) {
		if (obj._MATRIX != nullptr)
			return matrix(obj) *= num;		//Аналогично
		else throw "operator* : Matrix(" + std::to_string(obj._ID) + "), Num(" + std::to_string(num) + ")  : different size";
	}
	//double * matrix
	matrix operator* (const double num, const matrix& obj) {
		//Это для коммутативности 
		return obj * num; }
#pragma endregion

//Остальные операторы
	#pragma region Присваивание, перемещение и вывод
	matrix& matrix::operator= (const matrix& obj) {
		if (this == &obj)													//Проверка на самокопирование
			return *this;

		_LEN_M = obj._LEN_M;
		_LEN_N = obj._LEN_N;
		if (!check_mul(obj) || !check_sub(obj)) {
			delete[]_MATRIX;												//Удаляем прошлую матрицу
			_MATRIX = new double[_LEN_M * _LEN_N];							//Выделяем память
		}
		std::copy(obj._MATRIX, obj._MATRIX + _LEN_M * _LEN_N, _MATRIX);		//Копируем матрицу obj в _MATRIX
		return *this;														//Возвращаем
	}

//перемещения
	matrix& matrix::operator= (matrix&& obj) {
		
		if (this == &obj)				//Проверка на самокопирование
			return *this;

		delete[] _MATRIX;				//Удаляем
		_MATRIX = nullptr;				//Объявляем нулевым объеквтом
		
		std::swap(_LEN_M,obj._LEN_M);	//Эти функции меняют местами их сначения
		std::swap(_LEN_N, obj._LEN_N);
		std::swap(_MATRIX, obj._MATRIX);

		return *this;					//Возвращаем
	}
	// cout << matrix
	std::ostream& operator<<(std::ostream& out, const matrix& obj)
	{			//Здесь красивый вывод
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
	#pragma region Индексация
		//Индексация для обычных объектов
	double& matrix::matrixRow::operator[](unsigned IND) { return _MATRIX->_MATRIX[_ROW + IND]; }
	matrix::matrixRow matrix::operator[](unsigned IND) { return matrixRow(this, IND); }
		
		//Индексация для константных объектов
	const matrix::matrixRow matrix::operator[](unsigned IND) const { return matrixRow(this, IND); }
	double matrix::matrixRow::operator[](unsigned IND) const { return _MATRIX->_MATRIX[_ROW + IND]; }
	#pragma endregion
}