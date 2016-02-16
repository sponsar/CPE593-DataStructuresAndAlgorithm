#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
using namespace std;

double fa(double x) { return x*x; }
double fb(double x) {
	double x2 = x*x;
	return x2*x2*x;
}
double fc(double x) { return exp(-x*x)*x; }

typedef double(*FuncOneVar)(double x);
map<string, FuncOneVar> functionMap;

double trapezoidal(FuncOneVar f, double a, double b, double eps)
{
	double h = b - a;
	double A = (f(a) + f(b)) * h / 2;
	double A_next;
	double e;
	int n = 2;
	do
	{
		A_next = A / 2;
		for (int i = 0; i < n/2; i++)
		{
			double x = ((i * 2 + 1) * h / n) + a;
			A_next += f(x) * h / n ;
		}
		n *= 2;
		e = fabs(A_next - A);
		A = A_next;
	} while (e > eps );
	return A;
}

void doCase() {
	string functionName;
	double a, b, eps;
	cin >> functionName >> a >> b >> eps;
	FuncOneVar f = functionMap[functionName];
	double result = trapezoidal(f, a, b, eps);
	cout << fixed << a << "   " << fixed << b << "   " << result << endl;
}

int main() {
	functionMap["fa"] = fa;
	functionMap["fb"] = fb;
	functionMap["fc"] = fc;
	string garbage;
	int numCases;
	cin >> garbage >> numCases;
	for (int c = 1; c <= numCases; c++)
		doCase();

}

