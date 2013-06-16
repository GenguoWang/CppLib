#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iomanip>
#include <ctime>
#include <set>
#include <vector>
#include <queue>
using namespace std;
#define fcin cin
#define fcout cout
const int SIZE = 10000000;
void qsort(int left,int right,int * a)
{
	if(left >= right) return;
	int l = left, r = right,temp;
	while(l < r)
	{
		while(l < r && a[l] <= a[r])l++;
		temp = a[l];a[l] = a[r];a[r] = temp;
		while(l < r && a[l] <= a[r])r--;
		temp = a[l];a[l] = a[r];a[r] = temp;
	}
	qsort(left,l-1,a);
	qsort(l+1,right,a);
}
void testSort()
{
	vector<int> arry;
	vector<int> vec(SIZE);
	for(int i=0; i < SIZE; ++i)
	{
		arry.push_back(rand());
	}
	unsigned int begin = clock();
	sort(arry.begin(),arry.end());
	unsigned int end = clock();
	int old = 0;
	for(vector<int>::iterator it = arry.begin(); it != arry.end(); ++it)
	{
		if(*it < old) cout << "error" << endl;
		old = *it;
	}
	cout << "vector :" << end - begin << endl;
	int *arr = new int[SIZE];
	for(int i=0; i < SIZE; ++i)
	{
		arr[i] = rand();
	}
	begin = clock();
	qsort(0,SIZE-1,arr);
	end = clock();
	old = 0;
	for(int i=0; i < SIZE; ++i)
	{
		if(arr[i] < old) cout << "error" << endl;
		old = arr[i];
	}
	cout << "array :" << end - begin << endl;
	delete [] arr;
 

}

void testPQ()
{
	std::priority_queue<int,vector<int>,greater<int> > pq;
	unsigned int begin = clock();
	for(int i=0; i < SIZE; ++i)
	{
		pq.push(rand());
	}
	unsigned int mid = clock();
	cout << "pq push:" << mid - begin << endl;
	int old = 0x7fffffff,temp;
	cout << old << endl;
	for(int i=0; i < SIZE; ++i)
	{
		temp = pq.top();
		pq.pop();
		if(temp > old) cout << temp << endl;
		old = temp;
	}
	unsigned int end = clock();
	cout << "pq pop:" << end - mid << endl;
	pq
	//pq.//pq.pop();
	//pop_heap(
}
int main(int argc,int * argv)
{
	//ifstream fcin("a.in");
	//ofstream fcout("a.out");
	testSort();
	testPQ();
   return 0;
}