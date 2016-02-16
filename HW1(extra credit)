#include<iostream>
#include<stdlib.h>//rand()
#include <time.h>//clock()
#include <fstream>//ofstream
#include<math.h>//pow()

using namespace std;

void RandomShuffling(int a[],int bits)
{
	int n=(int)pow(10.,bits);//length of array
	for(int i=0;i<n;i++)
	{
		int random=0;
		for(int j=0;j<bits;j++)
		{
			random+=(rand()%10)*(int)pow(10.,j);
		}
		a[i]=random;//from 0 to (10^n)-1
	}
}

void InsertSort(int a[],int low,int high)
{
	int i,j;
	int temp;
	for(i=low+1;i<=high;i++)
	{
		temp=a[i];
		j=i-1;
		while((j>=0)&&(a[j]>temp))
		{
			a[j+1]=a[j];
			j--;
		}
		if(j!=i-1)
		a[j+1]=temp;
	}
}

int SelectPivotMedianOfThree(int a[],int low,int high)  //use the median of three number in array as pivot to quicksort
{  
    int mid =low+((high-low)>>1);
    if (a[mid]>a[high])
        swap(a[mid],a[high]);  
    if (a[low]>a[high]) 
		swap(a[low],a[high]);    
    if (a[mid]>a[low])
        swap(a[mid],a[low]);    
    return a[low];  
}  

void Qsort(int a[],int low,int high,int k)
{
	if(low>=high)
		return;
	if(high-low+1<k) 
	{
		InsertSort(a,low,high);
		return;
	}
	
	int i=low;
	int j=high;
	int pivot=SelectPivotMedianOfThree(a,low,high);
	while(i<j)
	{
		while(i<j&&a[j]>=pivot)
			--j;
		a[i]=a[j];
		while(i<j&&a[i]<=pivot)
			++i;	
		a[j]=a[i];
	}
	a[i]=pivot;
	Qsort(a,low,i-1,k);
	Qsort(a,j+1,high,k);
}

void docase(int bits,int interval,int peak)
{
	ofstream outfile;
	outfile.open("result.txt",ios::out);
	clock_t start,finish;
	int n=(int)pow(10.,bits);
	int *a=new int[n];
	for (int k=2;k<=peak;k+=interval)
	{
		RandomShuffling(a, bits);
		start = clock();
		Qsort(a, 0, n-1, k);
		finish = clock();
		double duration=(double)(finish - start)/CLOCKS_PER_SEC;//use second as unit
		outfile<<k<<" : "<<duration<<endl;
		cout <<k<<" : "<<duration<<endl;
	}
	outfile.close();
	delete [] a;
	a=NULL;
	cout<<"end"<<endl;
}

int main()
{
	int bits=6;//10^bit
	int interval=5;
	int peak=250;
	docase(bits,interval,peak);
	return 0;
}
