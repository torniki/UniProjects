#include <iostream>
#include <fstream>

using namespace std;

const int maxV = 1000;
int GR[maxV][maxV];

//алгоритм Флойда-Уоршелла
void Floyd(int D[][maxV], int V)
{
	int k;
	for (int i = 0; i < V; i++) 
		D[i][i] = 0;
		for (k = 0; k < V; k++)
			for (int i = 0; i < V; i++)
				for (int j = 0; j < V; j++)
					if (D[i][k] && D[k][j] && i != j)
						if (D[i][k] + D[k][j] < D[i][j] || D[i][j] == 0)
							D[i][j] = D[i][k] + D[k][j];

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++) cout << D[i][j] << "\t";
		cout << endl;
	}
}
//главная функция
int main()
{
	setlocale(LC_ALL, "Rus");
	int ch;
	cout << "Выберите способ ввода\n1.Считать с файла\n2.Ввести вручную\n";
	cin >> ch;
	if (ch == 1) 
	{
		ifstream Filein("graphFloyd.txt");  // открываем поток для чтения из файла
		Filein >> ch;
		while (Filein) 
		{
			int i, j;                  
			Filein >> i >> j;
			Filein >> GR[i][j];
			cout << "GR[" << i + 1 << "][" << j + 1 << "] > " << GR[i][j]<<endl;
		}
		cout << "Матрица кратчайших путей:" << endl;
		Floyd(GR, ch);
	}
	else if (ch == 2) 
	{
		cout << "Количество вершин в графе > "; cin >> ch;
		cout << "Введите матрицу весов ребер:\n";
		for (int i = 0; i < ch; i++)
			for (int j = 0; j < ch; j++)
			{
				cout << "GR[" << i + 1 << "][" << j + 1 << "] > ";
				cin >> GR[i][j];
			}
		cout << "Матрица кратчайших путей:" << endl;
		Floyd(GR, ch);
	}
	system("pause");
	return 0;
}