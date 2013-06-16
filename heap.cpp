#include <stdlib.h>
#include <iostream>
//#include <assert.h>
using namespace std;
class heap
{
    typedef int DataType;
	private:
        int mSize;
        int mMaxsize;
        DataType * mData;
        bool mBig;
        bool mHasData;
        int left(int index)
        {
            return 2*index;
        }
        int right(int index)
        {
            return 2*index+1;
        }
        int parent(int index)
        {
            return index/2;
        }
        void swap(int i,int j)
        {
            DataType temp;
            temp = mData[i];
            mData[i] = mData[j];
            mData[j] = temp;
        }
        bool bigger(int i, int j)
        {
            if(mBig) return mData[i] > mData[j];
            else return mData[i] < mData[j];
        }
		void myAssert(bool flag)
		{
			//assert(flag);
		}
    public:
        heap(int maxsize,bool big)
        {
            myAssert(maxsize > 0);
            mMaxsize = maxsize;
            mBig = big;
            mHasData = true;
            mData = new DataType[maxsize+1]; //mData[0] is not used
            mSize = 0;
        }
        heap(DataType * data,int size,bool big)
        {
            myAssert(data!=NULL && size > 0);
            mMaxsize = size;
            mBig = big;
            mHasData = false;
            mData = data;
            mSize = size;
            build();
        }
        ~heap()
        {
            if(mHasData)delete[]mData;
        }
        void heapify(int index)
        {
            int l = left(index),r = right(index);
            int largest = index;
            if(l<=mSize && bigger(l,largest))
            {
                largest = l;
            }
            if(r<=mSize && bigger(r,largest))
            {
                largest = r;
            }
            if(index != largest)
            {
                swap(index,largest);
                heapify(largest);
            }
        }
        void build()
        {
            for(int i= mSize/2; i >=1;--i)
            {
                heapify(i);
            }
        }
        void sort()
        {
            for(int i= mSize; i >= 2; i--)
            {
                swap(1,i);
                mSize--;
                heapify(1);
            }
            mSize = 0;
        }
        DataType top()
        {
            myAssert(mSize >= 1);
            return mData[mSize];
        }
        DataType pop()
        {
            myAssert(mSize >= 1);
            DataType data = mData[1];
            mData[1] = mData[mSize];
            mSize--;
            heapify(1);
            return data;
        }
        void insert(DataType number)
        {
            myAssert(mSize<mMaxsize);
            mSize++;
            mData[mSize] = number;
            int i = mSize;
            while(i > 1 && bigger(i,parent(i)))
            {
                swap(i,parent(i));
                i = parent(i);
            }
        }
};
int main(int argc,char **argv)
{
    int a[101];
	bool flag = false;
    for(int i = 1; i<=100;++i) a[i] =rand()% 1000;
    heap myHeap = heap(a,100,false);
    myHeap.sort();
	flag = true;
	int temp;
	cout << "test 1..." << endl;
    for(int i = 1; i<=100; ++i)
	{
		//cout << a[i] << endl;
		if(i > 1 && a[i-1] < a[i]) flag = false;
	}
	if(flag) cout <<"test1(build and sort) Passed" << endl;
	else cout <<"test1(build and sort) Failed" << endl;
	cout << "test 2..." << endl;
	heap tHeap2 = heap(100,false);
	for(int i = 1; i<=100;++i) tHeap2.insert(rand()%1000);
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
	if(flag) cout <<"test2(insert and pop) Passed" << endl;
	else cout <<"test2(insert and pop Failed" << endl;

    return 0;
}
