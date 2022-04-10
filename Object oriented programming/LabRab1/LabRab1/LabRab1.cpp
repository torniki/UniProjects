#include <iostream.h>
#include <vcl.h>
#include <conio.h>

class vect {
public:
	vect(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0); //Êîíñòðóêòîð
	vect operator+(const vect&) const;   //Ñëîæåíèå
	vect operator-(const vect&) const;//Âû÷èòàíèå
	void print() const;//Ïå÷àòü
private:
	int a, b, c, d, e, f;
};
//Êîíñòðóêòîð:
vect::vect(int a1, int b1, int c1, int d1, int e1, int f1)
{
	a = a1;
	b = b1;
	c = c1;
	d = d1;
	e = e1;
	f = f1;
}
//Ïåðåãðóæåííàÿ îïåðàöèÿ ñëîæåíèÿ:
vect vect::operator+(const vect& operand2) const
{
	vect sum;
	sum.a = a + operand2.a;
	sum.b = b + operand2.b;
	sum.c = c + operand2.c;
	sum.d = d + operand2.d;
	sum.e = e + operand2.e;
	sum.f = f + operand2.f;
	return sum;
}
//Ïåðåãðóæåííàÿ îïåðàöèÿ âû÷èòàíèÿ:
vect vect::operator-(const vect& operand2) const
{
	vect diff;
	diff.a = a - operand2.a;
	diff.b = b - operand2.b;
	diff.c = c - operand2.c;
	diff.d = d - operand2.d;
	diff.e = e - operand2.e;
	diff.f = f - operand2.f;
	return diff;
}
//Ïå÷àòü îáúåêòà â âèäå (a,b,c,d,e,f)
void vect::print() const
{
	std::cout << '(' << a << ", " << b << ", " << c << ", " << d << ", " << e << ", " << e << ')';
}
int main(int argc, char* argv[])
{
	vect x(4, 6, 7, 8, 3, 5), y(4, 3, 2, 1, 7, 1);
	vect z;
	std::cout << "\n Vector 1:   ";
	x.print();
	std::cout << "\n Vector 2:   ";
	y.print();
	z = x + y;
	std::cout << "\n Slozhenie:   ";
	z.print();
	z = x - y;
	std::cout << "\n Vichitanie:  ";
	z.print();
	getch();
	return 0;
}