#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;

double Func(double x) {
    return x*x*x*x - 12*x*x*x + 47*x*x - 60*x;
}

//равномерный поиск

void EvenSearch()
{
    double a = 0.0, x_min, y_min;
    double b = M_PI / 4.0;
    int N = 100;
    double* x = new double[N];
    for (int i = 0; i < N; i++)
    {
        x[i] = a + (i * ((b - a) / (N + 1)));
        if (i == 0) {
            x_min = x[i];
            y_min = Func(x[i]);
        }
        else if (Func(x[i]) <= y_min) {
            y_min = Func(x[i]);
            x_min = x[i];
        }
    }
    cout << "x_min= " << x_min << "\ny_min= " << y_min;
}

//дихотомия

void Dichotomy()
{
    double a = -5.0, b = 5.0, e = 0.001, l = 0.002, k, y_k, f_yk, z_k, f_zk, L = 1;
    k = 0;
    while (L > l)
    {
        y_k = (a + b - e) / 2;
        f_yk = Func(y_k);
        z_k = (a + b + e) / 2;
        f_zk = Func(z_k);
        if (f_yk <= f_zk)
            b = z_k;
        else
            a = y_k;
        L = abs(b - a);
    }
    cout << "min_x = " << (a + b) / 2 << "\nmin_y = " << Func((a + b) / 2);
}

int main() 
{
    setlocale(0,"rus");
    cout << "Равномерный поиск:\n";
    EvenSearch();
    cout << "\nДихотомия:\n";
    Dichotomy();
}
