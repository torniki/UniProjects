#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "matrix.h"
#include <vector>
#include <math.h>

using std::scientific;
using std::fixed;
using namespace std;
using namespace mtr;

matrix frobeniusM(const matrix&, matrix&, matrix&, size_t);
void getMatr(const matrix, matrix&, size_t, size_t, size_t);
double deter(const matrix&, size_t);
double f(const vector<double>&, double, size_t);
double check_eigen(const matrix&, double, size_t);
vector<double> check_vec(const matrix&, const matrix&, const vector<double>&, double, size_t);
vector<double> mult(const matrix&, const vector<double>&, size_t);
vector<double> eigen(const matrix&, vector<double>&, size_t);
vector<double> eigenVec(double, const matrix&, size_t);


int main() {
	setlocale(LC_ALL, "RUS");
	std::ofstream fout("output.txt", std::ios_base::goodbit);
	fout.close();
	ifstream fin("input.txt");
	size_t
		type,
		len;

	fin >> type >> len;

	matrix
		origin(len), 
		e(len, true),
		frab(len),
		s(len, true), 
		s1(len, true);

	vector<double> 
		own, x;

	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++)
			fin >> origin[i][j];

	fin.close();

	switch (type)
	{
		case 1: {
			vector <double>
				arr = eigen(frobeniusM(origin, s, s1, len), own, len);
			ofstream fout("output.txt", ios_base::app);
			for (size_t i = 0; i < own.size(); i++)
			{
				fout 
					<< i + 1 << " eigenvalue: "
					<< fixed << own[i]
					<< "\n\n";


				fout 
					<< "eigenvalue check: "
					<< scientific << check_eigen(origin, own[i], len)
					<< "\n\n";

				fout
					<< "eigenvalue multiplicity: "
					<< fixed << (int)arr[i] << "\n\n";


				fout << "_______________________________\n\n";
			}
			fout.close();
			break;
		}
		case 2: {
			vector<double>
				res,
				arr = eigen(frobeniusM(origin, s, s1, len), own, len);
			ofstream fout("output.txt", ios_base::app);

			for (size_t i = 0; i < own.size(); i++) {
				x = eigenVec(own[i], s, len);
				res = check_vec(origin, e, x, own[i], len);

				fout << "\t\t\t\t\teigenvector " << i + 1 << ":\n";
				for (unsigned i = 0; i < x.size(); i++)
					fout << fixed << x[i] << "\t ";
				fout << "\n\n";

				fout << "eigenvector check: ";
				for (unsigned i = 0; i < res.size(); i++)
					fout << scientific << res[i] << "\t ";
				
				fout << "\n\n";
				
				fout
					<< "eigenvector multiplicity: "
					<< fixed << (int)arr[i] << "\n\n"
					<< "_______________________________\n\n";
			}
			break;
		}
		default:
			break;
	}

	return 0;
}


matrix frobeniusM(const matrix& origin, matrix& s, matrix& s1, size_t len) {
	matrix
		E(len, true),
		m(len), m1(len),
		cp = origin;

	for (int k = len - 2; k > -1; k--) {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				if (i != k) {
					m[i][j] = E[i][j];
					m1[i][j] = E[i][j];
					continue;
				}
				if (j != k) {
					m[k][j] = (cp[k + 1][j] / cp[k + 1][k]) * (-1);
					m1[k][j] = cp[k + 1][j];
					continue;
				}
				m[k][k] = 1 / cp[k + 1][k];
				m1[k][j] = cp[k + 1][j];
			}
		}
		s = s * m;
		s1 = m1 * s1;
		cp = cp * m;
		cp = m1 * cp;
	}
	ofstream fout("output.txt", ios_base::app);
	fout << "\t\t\t\tfrobenius matrix:\n";
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			fout << setw(10) << fixed << cp[i][j] << "\t ";
		}
		fout << endl;
	}
	fout << "\n\n";
	fout << "_________________________________\n\n";
	fout.close();
	return cp;
}

void getMatr(const matrix origin, matrix& sec, size_t i , size_t j , size_t len) {
	int
		li, lj,
		ri = 0, rj;
	for (li = 0; li < len - 1; li++) // проверка индекса строки
	{
		if (li == i)
			ri = 1;
		rj = 0;
		for (lj = 0; lj < len - 1; lj++) // проверка индекса столбца
		{
			if (lj == j)
				rj = 1;
			sec[li][lj] = origin[li + ri][lj + rj];
		}
	}
}

double deter(const matrix& origin, size_t len) {
	int
		j = 0,
		k = 1,
		n = len - 1;
	double
		d = 0;
	matrix
		p(len);

	if (len < 1)
		throw "Err!";
	if (len == 1) {
		d = origin[0][0];
		return d;
	}
	if (len == 2) {
		d = origin[0][0] * origin[1][1] - (origin[1][0] * origin[0][1]);
		return(d);
	}
	if (len > 2) {
		for (int i = 0; i < len; i++) {
			getMatr(origin, p, i, 0, len);
			d = d + k * origin[i][0] * deter(p, n);
			k = -k;
		}
	}
	return d;
}

double f(const vector<double>& pol, double cur, size_t len) {
	double res = 0;
	for (int i = 0; i < len + 1; i++)
		res += pol[i] * pow(cur, i);
	return res;
}

double check_eigen(const matrix& source, double own, size_t len) {
	matrix e(len, true);
	e *= own;
	return deter(source - e, len);
}

vector<double> check_vec(const matrix& source, const matrix& e, const vector<double>& x, double own, size_t len) {
	
	vector<double>
		result,
		arr = mult(source, x, len),
		sarr;

	for (size_t i = 0; i < (x.size()); i++)
		sarr.push_back(own * x[i]);

	for (size_t i = 0; i < (x.size()); i++)
		result.push_back(arr[i] - sarr[i]);

	return result;
}

vector<double> mult(const matrix& source, const vector<double>& y, size_t len) {
	
	vector<double> 
		res;
	double
		sum;
	for (size_t i = 0; i < len; i++) {
		sum = 0;
		for (size_t j = 0; j < len; j++)
			sum += source[i][j] * y[j];
		res.push_back(sum);
	}
	return res;

}

vector<double> eigen(const matrix& source, vector<double>& own, size_t len) {

	matrix 
		e(len, true);

	vector<double>
		pol,
		arr;

	double
		eps = 0.000001,
		left = -10,
		cur = left,
		right = 10,
		d = 0.0001,
		sum = 0;
	int 
		k;
	for (int i = 0; i < len; i++) {
		pol.push_back(source[0][len - i - 1]);
		if (len % 2 == 0)
			pol[i] *= -1;
	}
	if (len % 2 == 0)
		pol.push_back(-1);
	else
		pol.push_back(1);

	vector<double>
		tmp = pol;

	while (true) {
		double
			res = f(pol, cur, len);
		if (abs(res) < d) {
			double 
				temp = cur;
			while (abs(res) < d) {
				cur += eps;
				res = 0;
				res = f(pol, cur, len);
			}
			own.push_back((temp + cur) * 0.5);
			res = 0;
			while (abs(res) < d) {
				res = 0;
				vector<double>
					cp;

				for (size_t i = 0; i < (tmp.size() - 1); i++) 
					cp.push_back(tmp[i + 1] * ((double)i + 1));
				for (size_t i = 0; i < (cp.size() - 1); i++)
					res += cp[i] * pow(own[own.size() - 1], i);
				tmp = cp;
				k++;
			}
			arr.push_back(k);
			k = 0;
			d = 0.00001;
			tmp = pol;
			res = 0;
			for (size_t i = 0; i < arr.size(); i++)
				sum += arr[i];
		}
		if (sum == len)
			return arr;
		if (cur >= right)
			return arr;
		else cur += eps;
	}
}

vector<double> eigenVec(double own, const matrix& s, size_t len) {
	vector<double> 
		y;

	for (int i = len - 1; i > -1; i--)
		y.push_back(pow(own, i));
	y = mult(s, y, len);
	return y;
}