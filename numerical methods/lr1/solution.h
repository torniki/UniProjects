class solution
{
private:
	double a, b, eps;
public:
	solution(double a, double b, double eps);
	//Функции поиска корня:
	//дихотомия
	void Dichotomy(char*, double a, double b, double eps);
	//хорды
	void Chord(char*, double a, double b, double eps);
	//золотой дождь
	void GoldS(char*, double a, double b, double eps);
	//метод ньютона
	void Newton(char*, double a, double b, double eps);
	//комбинированный 
	void Combo(char*, double a, double b, double eps);
	//итераций
	void Itera(char*, double a, double b, double eps);
};