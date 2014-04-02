#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>
using namespace std;
namespace kingo
{
template<typename DataType,typename ContainType=vector<DataType>,typename CompType=less<DataType> >
class heap
{
	private:
        ContainType data;
        const int INVALID_INDEX;
        vector<int> dataIndex;
        vector<int> invertIndex;
        int currentIndex;
        int size;
        CompType compare;
        int left(int index) { return 2*index; }
        int right(int index) { return 2*index+1; }
        int parent(int index) { return index/2; }
        int getNewIndex()
        {
            ++currentIndex;
            return currentIndex;
        }
        void swap(int i,int j)
        {
            DataType temp;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            int pi = invertIndex[i];
            int pj = invertIndex[j];
            int tempIndex = dataIndex[pi];
            dataIndex[pi] = dataIndex[pj];
            dataIndex[pj] = tempIndex;
            tempIndex = invertIndex[i];
            invertIndex[i] = invertIndex[j];
            invertIndex[j] = tempIndex;
        }
		void myAssert(bool flag)
		{
			//assert(flag);
		}
        void heapify(int index)
        {
            int l = left(index),r = right(index);
            int theIndexOfUpper = index;
            if(l<=size && compare(data[l],data[theIndexOfUpper]))
            {
                theIndexOfUpper = l;
            }
            if(r<=size && compare(data[r],data[theIndexOfUpper]))
            {
                theIndexOfUpper = r;
            }
            if(index != theIndexOfUpper)
            {
                swap(index,theIndexOfUpper);
                heapify(theIndexOfUpper);
            }
        }
        bool isAvaibleIndex(int index)
        {
            return index>=0 && index < data.size();
        }
        void initEmptyHeap()
        {
            size = 0;
            currentIndex = 0;
            DataType zeroPos;
            data.push_back(zeroPos);
            dataIndex.push_back(0);
            invertIndex.push_back(0);
        }
        int addData(const DataType& newData)
        {
            int thisIndex;
            size++;
            if(isAvaibleIndex(size))
            {
                data[size] = newData;
                dataIndex.push_back(size);
                thisIndex = dataIndex.size()-1;
                invertIndex[size] = thisIndex;
            }
            else
            {
                data.push_back(newData);   
                dataIndex.push_back(size);
                thisIndex = dataIndex.size()-1;
                invertIndex.push_back(thisIndex);
            }
            return dataIndex.size()-1;
        }
    public:
        heap():INVALID_INDEX(-1)
        {
            initEmptyHeap();
        }
        template<typename iterator>
        heap(iterator begin,iterator end):INVALID_INDEX(-1)
        {
            initEmptyHeap();
            while(begin != end)
            {
                addData(*begin);
                ++begin;
            }
            build();
        }
        ~heap()
        {
        }
        void build()
        {
            for(int i= size/2; i >=1;--i)
            {
                heapify(i);
            }
        }
        void sort()
        {
            for(int i= size; i >= 2; i--)
            {
                swap(1,i);
                size--;
                heapify(1);
            }
            size = 0;
        }
        DataType top()
        {
            myAssert(size >= 1);
            return data[1];
        }
        DataType pop()
        {
            myAssert(size >= 1);
            DataType topData = data[1];
            swap(1,size);
            dataIndex[invertIndex[size]] = INVALID_INDEX;
            invertIndex[size] = INVALID_INDEX;
            size--;
            heapify(1);
            return topData;
        }
        int push(DataType newData)
        {
            int thisIndex = addData(newData);
            int i = size;
            while(i > 1 && compare(data[i],data[parent(i)]))
            {
                swap(i,parent(i));
                i = parent(i);
            }
            return thisIndex;
        }
        ContainType& getData()
        {
            return data;
        }
        DataType getByIndex(int index)
        {
            myAssert(index>=1 && index <dataIndex.size());
            int pos = dataIndex[index];
            myAssert(pos>=1 && pos <= size);
            return data[pos];
        }
        bool isIndexValid(int index)
        {
            if(index>=1 && index < dataIndex.size() && dataIndex[index] != INVALID_INDEX)
            {
                return true;
            }
            else return false;
        }
};
}

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
int main(int argc,char **argv)
{
    testSortofHeap();
    testIndex();
    return 0;
}
