#include <iostream>

using namespace std;

void print(int interations,int key) 
{ 
	if(interations<0)
		cout<<"NOT FOUND"<<" "<<-interations<<endl;
	else 
		cout<<key<<" "<<interations<<endl;
}
int BinarySearch(int a[],int left,int right,int key)
{
	int mid;
	int iterations=0;
	while(left<=right)
	{
		iterations++;
		mid=(right-left+1)/2+left;
		if(a[mid]==key)	
			return iterations;
		if(a[mid]>key)
			right=mid-1;
		else 
			left=mid+1;
	}

	//iterations++;
	return -iterations;
}
void doCase() 
{
	int n,key,interations;
	cin >> n; 
	int* a=new int[n];
	for (int i=0; i<n;i++)  
		cin >> a[i];
	cin>>key;
	interations=BinarySearch(a,0,n-1,key);
	print(interations,key);
	delete [] a;
}

int main() {
	char garbage[]={0};
	int numCases;
	cin >> garbage >> numCases;
	for (int c=1; c <= numCases; c++)
    doCase();
}

