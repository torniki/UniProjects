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
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int n;                          // ���������� ������ � �������
vector<int>* adj;               // ������ ���������
vector<bool> used;              // ���������� � �� ���������� �������

// ������� ������ � �������
void dfs(int a) {
    // ���� ������� ��� ���������, �� ������� �� ��������
    if (used[a]) {
        return;
    }
    used[a] = true;             // ��������� ������� ��� ����������
    cout << a << " -> ";        // ������� �������

    // ����� ���� ������ ������� � �������� v   
    for (int i = 0; i < adj[a].size(); i++) {
        int b = adj[a][i];
        dfs(b);                 // ����������� ����� �� ������� a, ������� � �������� b
    }
}

// ������� ������ ������ �� �����
void readData() {

    ifstream fin("graph.txt");  // ��������� ����� ��� ������ �� ����� graph.txt
    fin >> n;                   // ��������� ���������� ������
    adj = new vector<int>[n];   //�������������� ������ ��������� ����������� n
    cout << "Kolichestvo vershin:\n" << n << endl << endl;
    cout << "Spisok reber: " << endl;
    //��������� ���� �� �����
    while (fin) {
        int a, b;               // �������������� ����������        
        fin >> a >> b;          // ��������� �� ����� �������� ������
        cout << a << " " << b << endl;
        // ��������� ����� a � b � ����

        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    used.assign(n, false);
}

int main()
{
    readData();
    cout << "\nStyagivayushee derevo: ";
    for (int a = 0; a < n; a++) {
        dfs(a);
    }
    return 0;
}
