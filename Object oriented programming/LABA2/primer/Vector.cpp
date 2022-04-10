#include <iostream>
#include <iomanip>

#include "Vector.h"



namespace some
{
	#pragma region Construction

	/*static*/ size_t Vector::ID_COUNTER = 0;

	Vector::Vector(size_t size, double* data)
	{
		m_id = ID_COUNTER++;
		std::cout << " + Vector " << m_id << std::endl;

		// Создание NULL-объекта
		if (size == 0)
		{
			m_size = 0;
			m_data = nullptr;
			return;
		}

		m_size = size;

		// Если копировать нечего, то создаем массив нулей
		if (data == nullptr)
		{
			m_data = new double[size]();
			return;
		}

		// Создаем массив мусора и копируем данные из data
		m_data = new double[size];
		std::copy(data, data + size, m_data);
	}

	Vector::Vector(size_t size, init_func init_func) : Vector(size) // ': Vector(size)' - это вызов делегирующего конструктора
	{
		double* dt = m_data;

		for (size_t i = 0; i < size; i++)
		{
			*dt++ = init_func(i);
		}
	}



	Vector::~Vector()
	{
		std::cout << " - Matrix " << m_id << std::endl;

		if (m_data == nullptr) return;

		delete[] m_data;
		m_data = nullptr;
		m_size = 0;
	}

	#pragma endregion
	
	#pragma region Formatted Output

	/*private*/ std::streamsize Vector::STREAM_WIDTH = 8;

	/*static*/ std::streamsize Vector::getStreamWidth()
	{
		return STREAM_WIDTH;
	}

	/*static*/ void Vector::setStreamWidth(std::streamsize width)
	{
		STREAM_WIDTH = width;
	}

	/*static*/ void Vector::resetStreamWidth()
	{
		STREAM_WIDTH = 8;
	}

	/*friend*/ std::ostream& operator<< (std::ostream& os, const Vector& vec)
	{
		auto width = os.width();
		if (width == 0) width = Vector::STREAM_WIDTH;

		os << std::setw(0) << " >> Vector " << vec.m_id << " :\n\n";

		if (vec.m_data == nullptr)
		{
			os << "\tNULL\n\n";
			return os;
		}

		double* dt = vec.m_data;
		double* dt_end = dt + vec.m_size;

		while (dt < dt_end)
		{
			os << std::setw(width) << *dt++;
		}

		return os << std::endl << std::endl;
	}

	#pragma endregion
}