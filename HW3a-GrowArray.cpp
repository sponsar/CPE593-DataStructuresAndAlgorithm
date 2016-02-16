//
//  main.cpp
//  test1
//
//  Created by »Æ ÐÅÒ¢ on 14-10-2.
//  Copyright (c) 2014Äê »Æ ÐÅÒ¢. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

class GrowArray {
private:
	int* x;
	int size;
public:
	GrowArray() {
		x = NULL;
		size = 0;
	}

	~GrowArray() {
		delete[] x;
	}

	GrowArray(const GrowArray& orig) {
		size = orig.size;
		x = new int[size];
		for (int i = 0; i < size; i++)
			x[i] = orig.x[i];
	}
	GrowArray& operator =(const GrowArray& orig) {
		if (this != &orig) {
			delete[] x;
			size = orig.size;
			x = new int[size];
			for (int i = 0; i < size; i++)
				x[i] = orig.x[i];
		}
		return *this;
	}

	void addFirst(int e) {
		int* temp = x;
		x = new int[size + 1];
		x[0] = e;
		for (int i = 1; i < size + 1; i++)
			x[i] = temp[i - 1];
		delete[] temp;
		size++;
	}

	void addLast(int e){
		int* temp = x;
		x = new int[size + 1];
		for (int i = 0; i < size; i++)
			x[i] = temp[i];
		x[size] = e;
		delete[] temp;
		size++;
	}
	// we will cheat and not delete the memory
	// we will live with one cell unused...
	// potential problem:
	// GrowArray a(1000000);
	// for (int i = 0; i < 10; i++)
	//   a.deleteFirst()
	void deleteFirst() {
		if (size == 0)
			return;
		for (int i = 0; i < size - 1; i++)
			x[i] = x[i + 1];
		size--;
	}

	void deleteLast() {
		if (size == 0)
			// DO SOMETHING!!! THIS IS BAD!!!
			return;
		size--;
	}
	void clear() {
		size = 0;
	}
	int get(int pos) {
		if (pos >= size)
			throw "BAD SIZE";
		return x[pos];
	}

	void set(int pos, int e) {
		if (pos >= size)
			throw "BAD SIZE";
		x[pos] = e;
	}


	friend ostream& operator <<(ostream& s, const GrowArray& a) {
		for (int i = 0; i < a.size; i++)
			s << a.x[i] << ' ';
		return s;
	}

};
void doCase(int N, int M, int P)
{
	if (M + P >= N)
	{
		cout << "nothing left!" << endl;
		return;
	}
	GrowArray a;
	for (int i = 1; i <= N; i++)
		a.addLast(i);
	for (int i = 0; i<M; i++)
		a.deleteLast();
	for (int i = 0; i<P; i++)
		a.deleteFirst();
	cout << a << endl;
	return;
}
int main() 
{
	ifstream inf("hw3ainp.dat");
	char garbage[1024] = { 0 };
	int numCases, N, M, P;
	inf >> garbage >> numCases;
	for (int i = 0; i < numCases; i++)
	{
		inf >> N >> M >> P;
		doCase(N, M, P);
	}
	inf.close();
	
}















