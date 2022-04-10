#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int n;                          // количество вершин в орграфе

// !!! Освободить динамическую память
vector<int>* adj;               // список смежности
vector<bool> used;              // пройденные и не пройденные вершины

// функция обхода в глубину
void dfs(int a) {
    // если вершину уже проходили, то функцию не вызываем
    if (used[a]) {
        return;
    }
    used[a] = true;             // маркируем вершину как пройденную
    cout << a << " -> ";        // выводим вершину

    // обход всех вершин смежных с вершиной v   
    for (int i = 0; i < adj[a].size(); i++) 
    {
        int b = adj[a][i];
        dfs(b);                 // рекурсивный обход от вершины a, смежной с вершиной b
    }
}




int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    // чтение данных из файла
    ifstream Filein("graph.txt");  // открываем поток для чтения из файла graph.txt
    Filein >> n;                   // считываем количество вершин
    adj = new vector<int>[n];   //инициализируем список смежности размерности n
    cout << "Кол-во вершин:\n" << n << endl << endl;
    cout << "Список рёбер: " << endl;
    //считываем граф из файла
    while (Filein) {
        int a, b;               // инициализируем переменные        
        Filein >> a >> b;          // считываем из файла значения вершин
        cout << a << " " << b << endl;
        // добавляем ребра a и b в граф

        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    used.assign(n, false);
    cout << "\nСтягивающее дерево: ";
    for (int a = 0; a < n; a++) 
    {
        dfs(a);
    }
    delete[] adj;
    return 0;
}
//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//using namespace std;
//
//int n;                      
//vector<int>* adj;               
//vector<bool> used;              
//
//
//void dfs(int a) {
//  
//	used[a] = true;
//	cout << a << "->";
//    for (int i = 0; i < adj[a].size(); i++) {
//		if (used[i] == false && adj[a][i] == 1)
//			dfs(i);
//    }
//}
//
//void ReadFile(string f)
//{
//	ifstream files(f);
//	int value;
//	int k;
//
//	if (!files.is_open())
//	{
//		cout << "Can't open the file!";
//	}
//	else
//	{
//		files >> value;
//		for (int i = 0; i < value; i++)
//			for (int j = 0; j < value; j++)
//			{
//				files >> k;
//				adj[i][j] = k;
//			}
//	}
//	files.close();
//}
//
//int main()
//{
//    ReadFile("graph.txt");
//	dfs(0);
//}