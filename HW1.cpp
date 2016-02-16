#include <iostream>
using namespace std;

void Qsort(int a[], int low, int high)
{
	if(low>=high)
		return;
	int i=low,j=high,pivot=(a[i]+a[j])/2;	
	while(i<=j)
	{
		while(j>low&&a[j]>pivot)
			j--;
		
		while(i<high&&a[i]<=pivot)
			i++;
		if (i < j)
		{
			swap(a[i],a[j]);
			i++;
			j--;
		}
		else if(i==j)
			j--;
	}
	if (j - low >= 1)
		Qsort(a, low, j);
	if (high - i >= 1)
		Qsort(a, i, high);
}

int main()
{
	char s[256]={0};
	int cases;
	cin >> s >>cases;	
	int *numlist = new int[cases];
	int **a = new int*[cases];	
	for (int i = 0; i < cases; i++)
	{
		int num;
		cin >> num;
		numlist[i] = num;
		a[i] = new int[num];
		for (int j = 0; j < num; j++)
		{
			cin >> a[i][j];
		}
	}
	cout << "The sequence is: " <<endl;
	for (int i = 0; i < cases; ++i)
	{
		Qsort(a[i], 0, numlist[i] - 1);
		for (int j = 0; j < numlist[i]; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
