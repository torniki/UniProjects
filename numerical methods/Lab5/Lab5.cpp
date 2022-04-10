#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PolStr.h"
#include "matrix.h"
#include <vector>

using namespace std;


namespace mtr
{
	class polynom {
	
		char
			* form;
		size_t 
			Type, n;
		
		string
			poly_type, data_list;
	public:	
		double m;
		vector<double>
			x, y, res_value, bounds;
	
	
		polynom() {
			ifstream fin("input.txt");
			fin >> Type >> n
				>> poly_type;
			if (poly_type == "uneven") {
				double item;
				
				fin.ignore(1, '\n');
				while (fin.peek() != '\n') {
					fin >> item;
					x.push_back(item);
					if (fin.eof())
						break;
				}

				fin.ignore(1, '\n');
				while (fin.peek() != '\n') {
					fin >> item;
					y.push_back(item);
					if (fin.eof())
						break;
				}

				fin.ignore(1, '\n');
				fin >> m;

				fin.ignore(1, '\n');
				while (fin.peek() != '\n') {
					fin >> item;
					res_value.push_back(item);
					if (fin.eof())
						break;
				}

				fin.ignore(1, '\n');
				fin >> data_list;

				fin.ignore(1, '\n');
				if (data_list == "true") {
					char func[64];
					fin >> func;
					form = CreatePolStr(func, 0);
				}
			}
			if (poly_type == "even") {
				double item;
					
				fin.ignore(1, '\n');
				while (fin.peek() != '\n') {
					fin >> item;
					bounds.push_back(item);
					if (fin.eof())
						break;
				}
				
				fin.ignore(1, '\n');
				while (fin.peek() != '\n') {
				
					fin >> item;
					y.push_back(item);
					
					if (fin.eof()) 
						break;
					
				}
				fin.ignore(1, '\n');
				fin >> m;
									fin.ignore(1, '\n');
				while (fin.peek() != '\n') {
					fin >> item;
					res_value.push_back(item);
					if (fin.eof())
						break;
				}
				fin.ignore(1, '\n');
				fin >> data_list;
				if (data_list == "true") {
					char func[64];
					fin >> func;
					form = CreatePolStr(func, 0);
				}
			}	
		}
		
		mtr::matrix find_diff() {
			mtr::matrix div_difference(n + 1);
			for (int i = 0; i < n + 1; i++)
				div_difference[i][0] = y[i];
			size_t n = this->n;

			if (poly_type == "uneven") {
				for (int k = 1; k < this->n + 1; k++) {
					for (int i = 0; i < n; i++)
						div_difference[i][k] = (div_difference[i + 1][k - 1] - div_difference[i][k - 1]) /
						(x[i + k] - x[i]);
					n--;
				}
			}
			else {
				for (int k = 1; k < this->n + 1; k++) {
					for (int i = 0; i < n; i++)
						div_difference[i][k] = (div_difference[i + 1][k - 1] - div_difference[i][k - 1]);
					n--;
				}
			}
			return div_difference;
		}

		double f(double arg, double der) {
			return EvalPolStr(form, arg, der);
		}
		
		void write(vector<double> obj) {
			ofstream fout("output.txt", ios_base::app);
			fout << "[" << setw(5);
			for (auto item : obj)
				fout << item << setw(7);
			fout << "]\n\n";
		}


		size_t type() { return Type;}

		vector<double> f() {
			vector<double> root;

			if (poly_type == "uneven") {
				matrix div_diff = find_diff();
				for (auto item : res_value) {
					double
						fi = 1,
						result = 0;
					for (int i = 0; i < n + 1; i++) {
						result += div_diff[0][i] * fi;
						fi *= (item - x[i]);
					}
					root.push_back(result);
				}
			}
			else {
				double h = (bounds[1] - bounds[0]) / n;
				vector<double> q;
				for (auto item : res_value) q.push_back((item - bounds[0]) / h);
				matrix div_diff = find_diff();

				for (auto item : q) {
					double result = 0,
						fi = 1, fact = 1;
					for (int i = 0; i < n + 1; i++) {
						if (i != 0)
							fact *= i;
						result += (div_diff[0][i] / fact) * fi;
						fi *= (item - i);
					}
					root.push_back(result);
				}

			}
			if (type() == 0)
				write(root);
			return root;
		}
		vector<double> df(){
			vector<double> root;

			if (poly_type == "uneven") {
				matrix div_diff = find_diff();
				for (auto item : res_value) {
					double 
						result = 0,
						summ = 0;
					for (int i = 1; i < n + 1; i++) {
						summ = 0;
						for (int j = 0; j < i; j++) {
							double mult = 1;
							for (int k = 0; k < i; k++) {
								if (k != j)
									mult *= item - x[k];
							}
							summ += mult;
						}
						result += div_diff[0][i] * summ;
					}
					root.push_back(result);
				}

			}
			else {
				double h = (bounds[1] - bounds[0]) / n;
				vector<double> q;
				for (auto item : res_value) q.push_back((item - bounds[0]) / h);
				matrix div_diff = find_diff();

				for (auto item : q) {
					double result = 0,
						summ = 0, fact = 1;
					for (int i = 1; i < n + 1; i++) {
						fact *= i;
						summ = 0;
						for (int j = 0; j < i; j++) {
							double mult = 1;
							for (int k = 0; k < i; k++) {
								if (k != j)
									mult *= item - k;
								

							}
							summ += mult;
						}
						result += div_diff[0][i] / fact * summ;
					}
					root.push_back(result / h);
				}
			}
			if (type() == 1)
				write(root);
			return root;
		}
		
		vector<double> ddf(){
			vector<double> root;
			
			if (poly_type == "uneven") {
				matrix div_diff = find_diff();

				for (auto item : res_value) {
					double result = 0,
						summ = 0, temp_sum = 0;
					for (int i = 2; i < n + 1; i++) {
						summ = 0;
						for (int j = 0; j < i; j++) {
							temp_sum = 0;
							for (int k = 0; k < i; k++) {
								double mult = 0;
								if (k != j) {
									for (int l = 0; l < i; l++)
										if (l != j && l != k)
											mult *= item - x[l];
									temp_sum += mult;
								}
							}
							summ += temp_sum;
						}
						result += div_diff[0][i] * summ;
					}
					root.push_back(result);
				}
			}
			else {
				double h = (bounds[1] - bounds[0]) / n;
				vector<double> q;
				for (auto item : res_value) q.push_back((item - bounds[0]) / h);
				matrix div_diff = find_diff();

				for (auto item : q) {
					double result = 0,
						summ = 0, temp_sum = 0,
						fact = 1;
					for (double i = 2; i < n + 1; i++) {
						fact *= i;
						summ = 0;
						for (double j = 0; j < i; j++) {
							temp_sum = 0;
							for (double k = 0; k < i; k++) {
								double mult = 1;
								if (k != j) {
									for (double l = 0; l < i; l++)
										if (l != j && l != k)
											mult *= item - l;
									temp_sum += mult;
								}
							}
							summ += temp_sum;
						}
						double div = div_diff[0][i];
						result += div_diff[0][i] * summ / fact;
					}
					root.push_back(result / pow(h, 2));

				}
			}
			if (type() == 2)
				write(root);
			return root;
		}
	};
}

int main()
{
	ofstream fout("output.txt", ios_base::goodbit);
	fout.close();
	ifstream fin("input.txt");
	mtr::polynom p;
	
	
	switch (p.type()) {
	case 0:
	{
		ofstream fout("output.txt", ios_base::app);
		vector<double> 
			result = p.f(), err;
		double errn = 0, errt = 0;
		for (auto item : p.res_value) {
			err.push_back(p.f(item, 0));
		}
		
		
		break;
		};
	case 1: {
		

		break;
	};
	case 2: {
		

		break;
	};
	}

}
