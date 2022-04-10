#include <iostream>
#include <complex.h>
#include <math.h>
#include "vector.h"
#include <string>

using namespace lab_vect;
inline void sep()
{
	std::cout << "- - - - -\n";
}
int main()
{
	setlocale(LC_ALL, "rus");

	vector A, B;
	A.set_x(1).set_y(2).set_z(5);
	std::cout << "Введите вектора A и B для вашей проверки:";

	std::cin >> A;
	std::cin >> B;
	sep();
	std::cout << "\n" << "sub Вектор C = " << sub(A,B) << std::endl;
	sep();
	std::cout << "\n" << "add Вектор C = " << add(A, B) << std::endl;
	sep();
	system("pause");

	void menu1();
	void elm_menu();
	void func_menu();
	int get_variant(int);
	//

		//проверка работоспособности функций
			//получения нового вектора

	vector C;
	double ans;
	int variant;
	do
	{
		menu1();

		variant = get_variant(3);
		switch (variant) {
		case 1: // проверка функций-элементов классов

			do {
				elm_menu();

				variant = get_variant(6);
				switch (variant) {
				case 1: { //Конструкторы
					std::cout << "конструктор по умолчанию: ";
					vector def_con;
					std::cout << "конструктор c параметром: ";
					vector param_con(1, 2, 3);
					std::cout << "конструктор копирования: ";
					vector copy_con(param_con);
					system("pause");
					break;
				}
				case 2: { // доступ к элементам вектора (чтение/запись)
					std::cout << "\nПроверка чтения элемента класса:\n\n"
						<< "объявляю переменную X, Y, Z для вывода"
						<< " из эл-та А";
					double x = A.get_x();
					double y = A.get_y();
					double z = A.get_z();
					std::cout << "\nРезультат:"
						<< "\nX= " << x
						<< "\nY= " << y
						<< "\nZ= " << z;
					std::cout << "\n\nТеперь проверим изменение элемента класса:\n\n"
						<< "Объявим Vect test с параметрами X= -1, Y= 2, Z= 3";
					vector test(-1, 2, 3);
					test.set_XYZ(3, 5, 8);

					std::cout << "\nИзменим значение X на 3, Y на 5, а Z на 8\n"
						<< "Результат:\n"
						<< "\nX = " << test.get_x()
						<< "\nY = " << test.get_y()
						<< "\nZ = " << test.get_z()
						<< std::endl;
					system("pause");
					break;
				}

				case 3: { // модуль вектора
					std::cout << "Получим модуль вектора А";
					std::cout << "Результат: "
						<< "|Test| = " << A.mod() << std::endl; ;
					system("pause");
					break;
				}

				case 4: { // умножение на скаляр
					std::cout << "Умножим вектор B на 3";
					B.scal(3);
					std::cout << "Результат:\n"
						<< "\nX= " << B.get_x()
						<< "\nY= " << B.get_y()
						<< "\nZ= " << B.get_z()
						<< std::endl;
					system("pause");
					break;
				}
				case 5: { // нормирование меткора
					std::cout << "Получим вектор test с параметрами (1, 5, -9)";
					vector test(1, 5, -9);
					std::cout << "Ответ: " << test.GetNorm();
					system("pause");
					break;
				}
				case 6: { // перегрузка операторов
					std::cout << "\nДля моего класса заданы 3 перегрузки для операторов:";
					std::cout << "\n =  для присваивания, \n<<  для вывода, \n>>  для ввода";
					std::cout << "\n\n Пример:\n";
					std::cout << "Объявим объект Test c параметрами (-9, -3, 6)";
					vector test(-9, -3, 6);
					std::cout << "\nВыведем значения test при помощи cout:\n"
						<< "Test = " << test;
					std::cout << "\n\nТеперь проверим перегрузку для ввода\n"
						<< "Введите ваш вектор test1:\n";
					vector test1;
					std::cin >> test1;
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());
					std::cout << "\nВыведем его значение: " << test1 << "\n\n"
						<< "И проверим последнюю перегрузку оператора - присваивание.\n\n";
					std::cout << "Заменим значения объекта Test на значение объекта Test1" << std::endl;
					test = test1;
					std::cout << "test = " << test << std::endl;
					system("pause");
					break;
				}
				}
			} while (variant != 0);

			variant = 9;
			break;

		case 2: // проверка внешних функций
			do {
				func_menu();

				variant = get_variant(7);

				switch (variant) {
				case 1: { // сумма

					std::cout << "\nПолучаем сумму векторов A и B\n"
						<< "в виде нового вектора C" << std::endl;
					C = add(A, B);
					std::cout << "Результат работы:\n" << "Вектор C = " << C << std::endl;
					system("pause");
					break;
				}

				case 2: { // разность
					std::cout << "\nПолучаем разность векторов A и B\n"
						<< "в виде нового вектора C" << std::endl;
					C = sub(A, B);
					std::cout << "Результат работы:\n" << "Вектор C = " << C << std::endl;
					system("pause");
					break;
				}

				case 3: { // векторное произведение
					std::cout << "получаем вектоное произведение векторов A и B\n"
						<< "в виде нового вектора C" << std::endl;
					C = multiply(A, B);
					std::cout << "Результат работы:\n" << "Вектор C = " << C << std::endl;
					system("pause");
					break;
				}

				case 4: { // скалярное произведение
					std::cout << "получаем скалярное произведение векторов A и B\n" << std::endl;
					ans = vect_scal(A, B);
					std::cout << "Результат работы: " << ans << std::endl;
					system("pause");
					break;
				}

				case 5: { // синус угла между A и B
					std::cout << "получаем синус угла между векторами A и B в виде" << std::endl;
					ans = vect_sin(A, B);
					std::cout << "Результат работы:" << ans << std::endl;
					system("pause");
					break;
				}

				case 6: { // косинус угла между A и B
					std::cout << "получаем косинус угла между векторами A и B в виде" << std::endl;
					ans = vect_cos(A, B);
					std::cout << "Результат работы:" << ans << std::endl;
					system("pause");
					break;
				}

				case 7: { // угол в градусах между A и B
					std::cout << "получаем величину угла между векторами A и B в виде" << std::endl;
					ans = agel(A, B);
					std::cout << "Результат работы:" << ans << std::endl;
					system("pause");
					break;
				}

				}
			} while (variant != 0);
			variant = 9;
			break;
		case 3:
		{
			system("cls");
			std::cout << "Введите новые значения:\n"
				<< "Для вектора A:";
			std::cin >> A;
			std::cout << "Для вектора B:";
			std::cin >> B;

			//Всё та же самая очистка
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());

			break;
		}
		}

	} while (variant != 0);

}

void menu1() { // основноен меню 
	system("cls");
	std::cout
		<< "Что вы хотите сделать?\n"
		<< "1: Проверить работу функций-элементов класса\n"
		<< "2: Проверить работу внешних функций\n"
		<< "3: Изменить значения векторов A и B\n"
		<< "\n0: Завершить программы\n"
		<< "\n>>";
}

void elm_menu() { // меню для фукций-элементов
	system("cls");
	std::cout
		<< "Выберите функцию-элемент для проверки:\n\n"
		<< "1: Конструкторы\n"
		<< "2: Доступ к эл-ам вектора\n"
		<< "3: Модуль вектора\n"
		<< "4: Умножение на скаляр\n"
		<< "5: нормирование вектора\n"
		<< "6: перегрузка операторов\n"
		<< "\n0: Выход в основное меню\n"
		<< "\n>>";
}

void func_menu() { // меню для вешних функций
	system("cls");
	std::cout
		<< "Выберите функцию для проверки:\n\n"
		<< "1: Сложить вектора a,b\n"
		<< "2: Вычесть вектора\n"
		<< "3: Векторно перемножить\n"
		<< "4: Получение скалярной велечины\n"
		<< "5: Найти синус угла между векторами\n"
		<< "6: Найти косинус угла между векторами\n"
		<< "7: Величина угла в градусах между векторами\n"
		<< "\n0: Выход в основное меню\n"
		<< "\n>>";
}

int get_variant(int count) { // защита от ненужных выриантов
	int variant;
	std::string s; // строка для считывания введённых данных
	getline(std::cin, s); // считываем строку

	// пока ввод некорректен, сообщаем об этом и просим повторить его
	while (sscanf_s(s.c_str(), "%d", &variant) != 1 || variant < -1 || variant > count) {
		std::cout << "Incorrect input. Try again: "; // выводим сообщение об ошибке
		getline(std::cin, s); // считываем строку повторно
	}

	return variant;
}
