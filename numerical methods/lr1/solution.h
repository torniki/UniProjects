class solution
{
private:
	double a, b, eps;
public:
	solution(double a, double b, double eps);
	//������� ������ �����:
	//���������
	void Dichotomy(char*, double a, double b, double eps);
	//�����
	void Chord(char*, double a, double b, double eps);
	//������� �����
	void GoldS(char*, double a, double b, double eps);
	//����� �������
	void Newton(char*, double a, double b, double eps);
	//��������������� 
	void Combo(char*, double a, double b, double eps);
	//��������
	void Itera(char*, double a, double b, double eps);
};