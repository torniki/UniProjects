#include <iostream>
#include <new>
using namespace std;

// ������������ ��������� ������ "�������"
template <typename Ochered>
class Queue
{
private:
	Ochered* p; // ������������ ������
	int count; // ���������� ��������� � �������

public:
	// ����������� �� ���������
	Queue()
	{
		count = 0; // ������� ������
	}

	// ����������� �����������
	Queue(const Queue& obj)
	{
		// ����������� obj � ������� ������
		count = obj.count;

		try {
			// ������� �������� ������ ��� p
			p = new Ochered[count];
			// ��������� ����������
			for (int i = 0; i < count; i++)
				p[i] = obj.p[i];
		}
		catch (bad_alloc e)
		{
			// ���� ������ �� ��������, �� ������� ����� ������
			cout << e.what() << endl;
			count = 0; // ������� ������ �������
		}
	}

	// �������� ������� � �������
	void push(Ochered item)
	{
		Ochered* p2; // �������� �������������� ���������
		p2 = p; // ������������� �������������� ��������� �� p

		try {
			// ������� �������� ����� �������� ������ ��� p, �� �� 1 ������
			p = new Ochered[count + 1];

			// ����������� ������ �� ������� �� ������� ��������� p2 (������ ������)
			// � �������, �� ������� ��������� p
			for (int i = 0; i < count; i++)
				p[i] = p2[i];

			// ����������� ��������� �������
			p[count] = item;

			// ��������� ���������� ��������� �� 1
			count++;

			// ���������� �������������� ���������� ������
			if (count > 1)
				delete[] p2;
		}
		catch (bad_alloc e)
		{
			// ���� ������ �� ��������
			cout << e.what() << endl; // ������� ��������� �� ������

			// ������� ������ ��������� �� p
			p = p2;
		}
	}

	// �������� ������ ������� �� �������
	Ochered pop()
	{
		if (count == 0)
			return 0;

		// ��������� �������, ������� ������������ �� �������
		Ochered item;

		item = p[0];

		// ������������ ����� ������� ������, ������� �� 1 ������
		try {
			Ochered* p2;

			// ������� �������� ���'���
			p2 = new Ochered[count - 1];

			count--; // ��������� ���������� ��������� � �������

			// p=>p2
			for (int i = 0; i < count; i++)
				p2[i] = p[i + 1]; // ���������� ��� ����� ������� ��������

			// ���������� �������, �� ������� ��������� p
			if (count > 0)
				delete[] p;

			// ������������� p �� p2
			p = p2;

			// ������� item
			return item;
		}
		catch (bad_alloc e)
		{
			// ���� ������ �� ����������, �� ������� 0
			cout << e.what() << endl;
			return 0;
		}
	}

	// ����������� ������� operator=(),
	// ��������� ������������ �������� ���� Queue
	Queue& operator=(const Queue& obj)
	{
		Ochered* p2; // ��������� �� �������������� ������

		try {
			// ������� �������� ����� ������� ������ ��� p2
			p2 = new Ochered[obj.count];

			// ���� ������ �������� �������,
			// ����� ����������� �������������� ���������� ������ ��� p
			if (count > 0)
				delete[] p;

			// ����������� obj � ������� ������
			p = p2; // ������������� p �� p2
			count = obj.count;

			// ��������� ����������
			for (int i = 0; i < count; i++)
				p[i] = obj.p[i];
		}
		catch (bad_alloc e)
		{
			// ���� ������ �� ����������, �� ������� ��������������� ���������
			cout << e.what() << endl;
		}
		return *this; // ������� ������� ������
	}

	// ����������
	~Queue()
	{
		if (count > 0)
			delete[] p;
	}

	// ����� ������ ������� �� ������� �� ��������� ���
	Ochered GetItem()
	{
		if (count > 0)
			return p[0];
		else
			return 0;
	}

	// ������� �������
	void clear()
	{
		if (count > 0)
		{
			delete[] p;
			count = 0;
		}
	}

	// �������� ������������� ��������� � �������
	bool IsEmpty()
	{
		return count == 0;
	}

	// ���������� ��������� � �������
	int GetN()
	{
		return count;
	}

	// �����, ��������� �������
	void print(const char* objName)
	{
		cout << "Object: " << objName << endl;
		for (int i = 0; i < count; i++)
			cout << p[i] << "\t";
		cout << endl;
		cout << "---------------------" << endl;
	}
};

int main()
{
	setlocale(0, "rus");
	Queue<int> Q1;
	int x;
	cout << "���� ������ � �������\n��� ��������� ������� ����� ������������� �����\n";
	while (1)
	{
		cin >> x;
		if (x < 0)
			break;
		Q1.push(x);
	}
	Q1.print("Q1");
	
	int d;
	d = Q1.GetItem();
	cout << "������ ������� � �������" << endl << "d = " << d << endl;

	Q1.print("Q1");
	
	system("pause");

	Q1.clear();
	if (Q1.IsEmpty())
		cout << "������� �������" << endl;
	else
		cout << "NO" << endl;
	return 0;
}