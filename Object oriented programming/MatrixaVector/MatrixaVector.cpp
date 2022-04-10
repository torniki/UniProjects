#include "Matrix.H"
#include <iostream>

using namespace std;

int main()
{
    Matrix<int> A(2, 3);
    Matrix<double> B(3);
    Matrix<int> C = A;
    std::cout << "Hello World!\n";
    
    return 0;
}
