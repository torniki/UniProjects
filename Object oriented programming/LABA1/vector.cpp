#include <iostream>
#include "vector.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

namespace lab_vect
{
	int vector::_STATIC = 0;

	vector::vector() : x(0), y(0), z(0), _ID(++_STATIC) { // �� ���������
		std::cout << "\Constructor " << _ID << std::endl;
	}

	vector::vector(double x, double y, double z) : x(x), y(y), z(z), _ID(++_STATIC) // � ����������
	{
		std::cout << "\nConstuctor " << _ID << std::endl;
	}

	vector::vector(const vector& obj) : x(obj.x), y(obj.y), z(obj.z), _ID(++_STATIC) {
		// ����������� �����������
		std::cout << "\n------------------------CopyConstructor------------------------" << _ID << std::endl;
	}

	vector::~vector() { // ����������
		std::cout << "\nDestructor " << _ID << std::endl;
		// � ��������, ����� ������ �������, ������ �� ������. �� �������))
	}

	//������ � ��������� ������� (������/������)
		// ���������
	double vector::get_x()const { return x; };
	double vector::get_y()const { return y; };
	double vector::get_z()const { return z; };

	// ���������
	vector& vector::set_XYZ(double x, double y, double z) { this->x = x; this->y = y; this->z = z; return *this; };
	vector& vector::set_x(double x) { this->x = x; return *this; };
	vector& vector::set_y(double y) { this->y = y; return *this; };
	vector& vector::set_z(double z) { this->z = z; return *this; };

	//

	double vector::mod()const { // ������ �������
		return sqrt((x * x) + (y * y) + (z * z));
	}

	vector& vector::scal(double num) { // ��������� �� ������
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

	vector& vector::toNorm() {// ������������ �������
		double len = mod();
		x /= len;
		y /= len;
		z /= len;

		return *this;
	}

	vector vector::GetNorm() const { // ������� �������������� �������
		double len = mod();
		return vector(x / len, y / len, z / len);
	}

	//���������� ����������
	std::ostream& operator<< (std::ostream& out, const vector& vect) {
		// ��� ��� ������
		out << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
		return out;
	}

	std::istream& operator>> (std::istream& in, vector& vect) {
		// ��� ��� �����

		std::cout << "\nX= ";
		in >> vect.x;

		std::cout << "Y= ";
		in >> vect.y;

		std::cout << "Z= ";
		in >> vect.z;

		return in;
	}

	vector& vector::operator= (const vector& obj) {// ��� ��� ������������	

		//�������� �� ���������������
		if (this == &obj)
			return *this;

		// �����������
		x = obj.x;
		y = obj.y;
		z = obj.z;

		return *this;
	};

	vector add(const vector& obj1, const vector& obj2) {
		return vector(obj1.get_x() + obj2.get_x(),
			obj1.get_y() + obj2.get_y(),
			obj1.get_z() + obj2.get_z());
	}

	//���������
	vector sub(const vector& obj1, const vector& obj2) {

		vector res(obj1.get_x() - obj2.get_x(),
			obj1.get_y() - obj2.get_y(),
			obj1.get_z() - obj2.get_z());

		return res;
	}

	//��������� ������������
	vector multiply(const vector& obj1, const vector& obj2) {

		return vector(obj1.get_y() * obj2.get_z() - obj2.get_y() * obj1.get_z(),
			-1 * (obj1.get_x() * obj2.get_z() - obj2.get_x() * obj1.get_z()),
			obj1.get_x() * obj2.get_y() - obj2.get_x() * obj1.get_y());
	}

	//��������� ������������
	double vect_scal(const vector& obj1, const vector& obj2) {

		return (obj1.get_x() * obj2.get_x() +
			obj1.get_y() * obj2.get_y() +
			obj1.get_z() * obj2.get_z());
	}

	double vect_cos(const vector& obj1, const vector& obj2) {
		return vect_scal(obj1, obj2) / (obj1.mod() * obj2.mod());
	}

	double vect_sin(const vector& obj1, const vector& obj2) {
		return multiply(obj1, obj2).mod() / (obj1.mod() * obj2.mod());
	}

	double agel(const vector& obj1, const vector& obj2) {
		return atan2(multiply(obj1, obj2).mod(), vect_scal(obj1, obj2)) * 180 / M_PI;
	}
}