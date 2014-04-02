#include "heap.h"
#include <iostream>
#include <assert.h>
using namespace std;
void testSortofHeap()
{
	int temp;
	bool flag = false;
    int a[101];
    for(int i = 1; i<=100;++i) a[i] =rand()% 1000;
    kingo::heap<int,vector<int>, less<int> > myHeap(a+1,a+101);
    vector<int> &data = myHeap.getData();
    myHeap.sort();
	flag = true;
	cout << "test 1..." << endl;
    for(int i = 1; i<=100; ++i)
	{
		if(i > 1 && data[i-1] < data[i]) flag = false;
	}
	if(flag) cout <<"test1(build and sort) Passed" << endl;
	else cout <<"test1(build and sort) Failed" << endl;
    assert(flag);
	cout << "test 2..." << endl;
	kingo::heap<int> tHeap2;
    tHeap2.build();
    int index10,value10;
	for(int i = 1; i<=100;++i)
    {
        if(i==10)
        {
            value10 = rand()%1000;
            index10 = tHeap2.push(value10);
            cout << "index" << index10 <<" old value:" << value10 << " now value:" << tHeap2.getByIndex(index10) << endl;
            
        }else
        {
            tHeap2.push(rand()%1000);   
        }
    }
    cout << "index" << index10 <<" old value:" << value10 << " now value:" << tHeap2.getByIndex(index10) << endl;
	temp = 0;
	int pop;
	flag = true;
	for(int i = 1; i <= 100; ++i)
	{
		pop = tHeap2.pop();
		if(temp > pop) flag = false;
		temp = pop;
		//cout << pop << endl;
	}
    cout << "index" << index10 <<" old value:" << value10 << " now value:" << tHeap2.getByIndex(index10) << endl;
	if(flag) cout <<"test2(insert and pop) Passed" << endl;
	else cout <<"test2(insert and pop Failed" << endl;
    assert(flag);
}
void testIndex()
{
    kingo::heap<int> testHeap;
    int index,index2;
    testHeap.push(1);
    testHeap.push(2);
    testHeap.push(3);
    index = testHeap.push(4);
    testHeap.push(5);
    assert(testHeap.getByIndex(index) == 4);
    testHeap.pop();
    assert(testHeap.getByIndex(index) == 4);
    testHeap.push(10);
    assert(testHeap.getByIndex(index) == 4);
    testHeap.push(7);
    assert(testHeap.getByIndex(index) == 4);
    testHeap.pop();
    testHeap.pop();
    testHeap.pop();
    testHeap.pop();
    assert(!testHeap.isIndexValid(index));
    testHeap.push(3);
    index = testHeap.push(6);
    testHeap.push(8);
    assert(testHeap.getByIndex(index) == 6);
}
void testChange()
{
    kingo::heap<int> testHeap;
    testHeap.push(2);
    testHeap.push(3);
    testHeap.push(5);
    int index = testHeap.push(8);
    testHeap.change(index,1);
    assert(testHeap.top() == 1);
    testHeap.change(index,6);
    cout << testHeap.top() << endl;
    assert(testHeap.top() == 2);
}
int main(int argc,char **argv)
{
    testSortofHeap();
    testIndex();
    testChange();
    return 0;
}

