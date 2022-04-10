#include <stdio.h>
#include <conio.h>

#include "polstr.h"

int main(void)
{
//	char  s1[1024] = "sin (- x2 * 5 + x1) + cos 3";
//	char  s1[1024] = "-sin(x2) + cos(-x1)";
//	char  s1[1024] = "-(+ x1)*(3 + 4)";
//	char  s1[1024] = "-2^x";
//	char  s1[1024] = "-(3*x)^(2*x)";
//	char  s1[1024] = "-sin(cos(x))";
	char  s1[1024] = "-cos(x + 3)";
	char *s2;
	textattr(LIGHTGRAY);
	clrscr();
	double val = 1.5;
//	double vals[] = {0, 0};
	unsigned der = 2;
	s2 = CreatePolStr(s1, 0);
	if(s2) {
		for(int d = 0; d <= der; d++) {
			printf("%s'%d = %g\n", s2, d, EvalPolStr(s2, val, d));
		}
		delete [] s2;
	}
	if(Error) printf("Error: %d.\n", Error);
	return 0;
}
