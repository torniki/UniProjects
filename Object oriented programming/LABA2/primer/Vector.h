#pragma once

namespace some
{

	class Vector
	{
	private:
		static size_t ID_COUNTER;
		size_t m_id;

		size_t m_size;
		double* m_data;

	public:
		// обратите внимание на присваивание значений аргументам при объявлении - это параметры по умолчанию
		explicit Vector(size_t size = 0, double* data = nullptr);

		typedef double(*init_func)(size_t i);

		Vector(size_t size, init_func init_func);

		~Vector();

	private:
		static std::streamsize STREAM_WIDTH;

	public:
		static std::streamsize getStreamWidth();
		static void            setStreamWidth(std::streamsize width);
		static void            resetStreamWidth();

		friend std::ostream& operator<< (std::ostream& os, const Vector& vec);
	};

}

