#pragma once

namespace lab_vect
{
	class vector
	{
	private:
		int _ID;
		static int _STATIC;
		double x, y, z; // вектора

	public:
		vector(); // конструткор по умолчанию
		vector(double x, double y, double z); // с параметром
		vector(const vector& obj); // конструкор копироваиня
		~vector(); // деструктор

		//доступ к элементам вектора (чтение/запись)

			// получение
		double get_x() const;
		double get_y() const;
		double get_z() const;

		// изменение
		vector& set_XYZ(double x, double y, double z);
		vector& set_x(double x);
		vector& set_y(double y);
		vector& set_z(double z);

		//
		vector GetNorm() const; // получение нормированного вектора
		vector& toNorm();		//Нормирование самого вектора
		double mod() const; // модуль вектора
		vector& scal(double num); // умножение на скаляр

	//Перегрузка операторов
		friend std::ostream& operator<< (std::ostream& out, const vector& vect);
		friend std::istream& operator>> (std::istream& in, vector& vect);

		vector& operator= (const vector& obj);
	};

	// получение нового вектора C:
	vector add(const vector&, const vector&);//		1) сложение	(C = A + B);
	vector sub(const vector&, const vector&);//		2) вычитание(C = A – B);
	vector multiply(const vector&, const vector&);//	3) векторное произведение(С = A * B);

	//б) с получением скалярных величин:
	double vect_scal(const vector&, const vector&);//1) скалярного произведения двух векторов;

	//2) косинуса и синуса угла между двумя векторами;
		//2.1 косинус угла между векторами
	double vect_cos(const vector&, const vector&);

	//2.2 синус угла между векторами
	double vect_sin(const vector&, const vector&);

	//3) величины угла в градусах между векторами в пределах [0º, 180º].
	double agel(const vector&, const vector&);

}
