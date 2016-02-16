#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SizeMismatch {
private:
	int line;
public:
	SizeMismatch(int lineNum) : line(lineNum) {}
	friend ostream& operator <<(ostream& s, SizeMismatch e) {
		return s << "Size mismatch at line: " << e.line << "\n";
	}
};

class Matrix {
private:
	double* x;
	int rows, cols;
public:
	Matrix(int rows, int cols) : rows(rows), cols(cols) {
		x = new double[rows*cols];
		for (int i = 0; i < rows*cols; i++)
			x[i] = 0;
	}
	Matrix(ifstream& f) {
		f >> rows >> cols;
		x = new double[rows*cols];
		for (int i = 0; i < rows*cols; i++)
			f >> x[i];
	}
	~Matrix() {
		delete[] x;
	}
	Matrix(const Matrix& orig) {
		rows = orig.rows;
		cols = orig.cols;
		x = new double[rows*cols];
		for (int i = 0; i < rows*cols; i++)
			x[i] = orig.x[i];
	}
	Matrix& operator =(const Matrix& orig)
	{/*
		if (this != &orig)
		{
			delete[] x;
			rows = orig.rows;
			cols = orig.cols;
			x = new double[rows*cols];
			for (int i = 0; i < rows*cols; i++)
				x[i] = orig.x[i];
		}
		return *this;
		*/
	}
	int getRows() const 
	{ 
		return rows;
	}
	int getCols() const 
	{ 
		return cols; 
	}

	friend Matrix operator +(const Matrix& a, const Matrix& b) {
		if (a.rows != b.rows || a.cols != b.cols)
			throw SizeMismatch(__LINE__);
		Matrix res(a.rows, a.cols);
		for (int i = 0; i < a.cols * a.rows; i++)
		{
			res.x[i] = a.x[i] + b.x[i];
		}
		return res;
	}

	friend Matrix operator *(const Matrix& a, const Matrix& b) 
	{
		if (a.cols != b.rows)
			throw SizeMismatch(__LINE__);
		Matrix res(a.rows, b.cols);
		for (int i = 0; i <a.rows; i++)
		{
			for (int j = 0; j < b.cols; ++j)
			{
				double sum = 0;
				for (int k = 0; k < a.cols; ++k)
				{
					sum += a(i, k) * b(k, j);
				}
				res(i, j) = sum;
			}
		}
		return res;
	}


	void solve(double x[], double B[]) {
		if (rows != cols)
			throw SizeMismatch(__LINE__);
		Matrix t = *this;
		for (int r = 0; r < rows; r++)
		{
			// find maximum row
			double max = t(r, r);
			int maxR = r;
			for (int r1 = r + 1; r1 < rows; ++r1)
			{
				if (t(r1, r) > max)
				{
					maxR = r1;
					max = t(r1, r);
				}
			}
			// swap maxR and r row
			if (r != maxR)
			{
				double temp;
				for (int c = 0; c < cols; c++)
				{
					temp = t(r, c);
					t(r, c) = t(maxR, c);
					t(maxR, c) = temp;
				}
				temp = B[r];
				B[r] = B[maxR];
				B[maxR] = temp;

			}
			// eliminate elements

			double e = t(r, r);
			if (e == 0)
				throw SizeMismatch(__LINE__);
			for (int r1 = r + 1; r1 < rows; r1++)
			{
				double ratio = t(r1, r) / e;
				t(r1, r) = 0;
				for (int c = r1; c < cols; ++c)
				{
					t(r1, c) -= ratio * t(r, c);
				}
				B[r1] -= ratio *B[r];
			}

		}

		// get the answer from bottom to top
		for (int i = rows - 1; i >= 0; --i)
		{
			for (int j = i + 1; j < cols; j++)
			{
				B[i] -= t(i, j)*B[j];
			}
			x[i] = B[i] / t(i, i);
			B[i] = B[i] / t(i, i);
		}

	}
	double& operator ()(int i, int j) {
		return x[i * cols + j];
	}
	
	double operator ()(int i, int j) const {
		return x[i * cols + j];
	}
	
	friend ostream& operator <<(ostream& s, const Matrix& m) {
		for (int i = 0; i < m.rows; i++) {
			for (int j = 0; j < m.cols; j++)
				s << m(i, j) << ' ';
			s << endl;
		}
		return s;
	}
};

void doCase(ifstream& f) {
	try {
		Matrix m1(f);
		cout << m1 << endl;
		Matrix m2(f);
		cout << m2 << endl;
		Matrix m3 = m1 + m2;
		cout << m3 << endl;
		Matrix m4 = m1 * m2;
		cout << m4 << endl;
		Matrix A(f);
		cout << A << endl;
		int n = A.getRows();
		double* B = new double[n];
		for (int i = 0; i < n; i++)
			f >> B[i];
		double* x = new double[n];
		A.solve(x, B);
		for (int i = 0; i < n; i++)
			cout << x[i] << ' ';
		cout << endl;
		delete[] x;
		delete[] B;

	}
	catch (const SizeMismatch& e) {
		cout << e << endl;
	}
}


int main() {
	ifstream f("hw4ainp.dat");
	string garbage;
	int numCases;
	f >> garbage >> numCases;
	for (int i = 1; i <= numCases; i++)
		doCase(f);
}
